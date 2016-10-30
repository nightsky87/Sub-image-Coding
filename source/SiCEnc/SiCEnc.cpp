#include "CImg.h"
#include "ComDef.h"
#include "SiCEncCU.h"
#include "SiCComBACCore.h"

#include <cassert>

using namespace cimg_library;

int main()
{
	// Load a test image
	CImg<s16> img("../../../../images/Misc/lena_std.bmp");

	// Determine the original dimensions
	u16 trueWidth = img.width();
	u16 trueHeight = img.height();
	u8 channels = img.spectrum();

	// Calculate the modulo-64 dimensions
	u16 width = trueWidth;
	u16 height = trueHeight;
	if (trueWidth % CU_SIZE)
		width = trueWidth + (CU_SIZE - (trueWidth % CU_SIZE));
	if (trueHeight % CU_SIZE)
		height = trueHeight + (CU_SIZE - (trueHeight % CU_SIZE));

	// Pad the image
	img.resize(width, height, 1, channels , 0, 1);

	// Manually define the parameters for now
	paramStruct param;
	param.q1 = 256;
	param.q2 = param.q1;
	param.chromaSub = CHROMA_400;

	// Automatically detect grayscale images
	if (channels == 1)
		param.chromaSub = CHROMA_400;

	if (param.chromaSub == CHROMA_444)
	{
		printf("Error: Chroma prediction not yet implemented\n");
		return -1;
	}

	// Apply the Rec. 601 YCbCr transform
	const u32 chOffset = width * height;
	if (channels == 3)
	{
		for (u32 i = 0; i < chOffset; i++)
		{
			double y = round(0.299 * (double)img(i) + 0.587 * (double)img(i + chOffset) + 0.114 * (double)img(i + 2 * chOffset));
			double cb = round(128 - 0.168736 * (double)img(i) - 0.331264 * (double)img(i + chOffset) + 0.5 * (double)img(i + 2 * chOffset));
			double cr = round(128 + 0.5 * (double)img(i) - 0.418688 * (double)img(i + chOffset) - 0.081312 * (double)img(i + 2 * chOffset));

			img(i) = (s16)((y < 0) ? 0 : ((y > 255) ? 255 : y));
			img(i + chOffset) = (s16)((cb < 0) ? 0 : ((cb > 255) ? 255 : cb));
			img(i + 2 * chOffset) = (s16)((cr < 0) ? 0 : ((cr > 255) ? 255 : cr));
		}
	}

	CImg<s16> imgRef = img;
	if (channels == 1 || param.chromaSub == CHROMA_400)
		imgRef.channel(0);

	// Initialize the arithmetic encoder with 8 bpp for grayscale images or 24 bpp for color images
	if (param.chromaSub == CHROMA_400)
		InitializeEncoder(8 * width * height);
	else
		InitializeEncoder(24 * width * height);

	// Process each coding unit (CU)
	for (u16 y = 0; y < height; y += CU_SIZE)
	{
		for (u16 x = 0; x < width; x += CU_SIZE)
		{
			SiCEncCU(&img(x, y), width, height, param);
		}
	}

	if (param.chromaSub == CHROMA_400)
		channels = 1;

	// Terminate the encoding process and write to file
	EncodeTerminate();
	WriteBitstream("../../SiCDec/SiCDec/test.sic", trueWidth, trueHeight, channels, param);

	if (channels == 1 || param.chromaSub == CHROMA_400)
		img.channel(0);

	printf("%.4f\n", img.PSNR(imgRef, 255));

	// Apply the JPEG YCbCr forward transform
	if (channels == 3)
	{
		if (param.chromaSub == CHROMA_400)
		{
			img = img.channel(0);
		}
		else
		{
			for (u32 i = 0; i < chOffset; i++)
			{
				double r = round((double)img(i) + 1.402 * (double)(img(i + 2 * chOffset) - 128));
				double g = round((double)img(i) - 0.344136 * (double)(img(i + chOffset) - 128) - 0.714136 * (double)(img(i + 2 * chOffset) - 128));
				double b = round((double)img(i) + 1.772 * (double)(img(i + chOffset) - 128));

				img(i) = (s16)((r < 0) ? 0 : ((r > 255) ? 255 : r));
				img(i + chOffset) = (s16)((g < 0) ? 0 : ((g > 255) ? 255 : g));
				img(i + 2 * chOffset) = (s16)((b < 0) ? 0 : ((b > 255) ? 255 : b));
			}
		}
	}
	img.display();

	return 0;
}