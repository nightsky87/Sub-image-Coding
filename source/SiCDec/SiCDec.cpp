#include "CImg.h"
#include "ComDef.h"
#include "SiCDecCU.h"
#include "SiCComBACCore.h"
#include <cmath>

using namespace cimg_library;

int main()
{
	u8 channels;
	u16 trueWidth, trueHeight;

	paramStruct param;

	// Read the bitstream to memory and initialize the decoding process
	ReadBitstream("test.sic", &trueWidth, &trueHeight, &channels, &param);
	InitializeDecoder();

	// Calculate the modulo-64 dimensions
	u16 width = trueWidth;
	u16 height = trueHeight;
	if (trueWidth % CU_SIZE)
		width = trueWidth + (CU_SIZE - (trueWidth % CU_SIZE));
	if (trueHeight % CU_SIZE)
		height = trueHeight + (CU_SIZE - (trueHeight % CU_SIZE));

	// Allocate space for the YCbCr values
	CImg<s16> Y(width, height);
	CImg<s16> Cb(width / 2, height / 2);
	CImg<s16> Cr(width / 2, height / 2);

	// Process each coding unit (CU)
	for (u32 y = 0; y < height; y += CU_SIZE)
	{
		for (u32 x = 0; x < width; x += CU_SIZE)
		{
			// Copy the CU pointers
			static cuStruct cu;
			cu.cbLuma = &Y(x, y);
			cu.cbChroma1 = &Cb(x / 2, y / 2);
			cu.cbChroma2 = &Cr(x / 2, y / 2);

			SiCDecCU(cu, width, param);
		}
	}

	// Terminate the encoding process and write to file
	DecodeTerminate();

	Cb.resize_doubleXY();
	Cr.resize_doubleXY();

	// Allocate space for the final image
	CImg<s16> img(width, height, 1, channels, 0);

	// Apply the JPEG YCbCr forward transform
	const u32 chOffset = width * height;
	for (u32 i = 0; i < chOffset; i++)
	{
		double r = round((double)Y(i) + 1.402 * (double)(Cr(i) - 128));
		double g = round((double)Y(i) - 0.344136 * (double)(Cb(i) - 128) - 0.714136 * (double)(Cr(i) - 128));
		double b = round((double)Y(i) + 1.772 * (double)(Cb(i) - 128));

		img(i) = (s16)((r < 0) ? 0 : ((r > 255) ? 255 : r));
		img(i + chOffset) = (s16)((g < 0) ? 0 : ((g > 255) ? 255 : g));
		img(i + 2 * chOffset) = (s16)((b < 0) ? 0 : ((b > 255) ? 255 : b));
	}

	CImg<s16> imgRef("../../../../images/Misc/lena_std.bmp");

	printf("%.4f\n", img.PSNR(imgRef, 255));
	img.display();

	return 0;
}
