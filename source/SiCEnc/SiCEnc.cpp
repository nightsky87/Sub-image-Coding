#include "CImg.h"
#include "ComDef.h"
#include "SiCEncCU.h"
#include "SiCComBACCore.h"

#include <cassert>

using namespace cimg_library;

int main()
{
	// Load a test image
	CImg<s16> img("../../../../images/Misc/lena_gray.bmp");
	CImg<s16> imgRef = img;

	// Determine the original dimensions
	u32 trueWidth = img.width();
	u32 trueHeight = img.height();
	u8  channels = img.spectrum();

	// Calculate the modulo-64 dimensions
	u32 width = trueWidth;
	u32 height = trueHeight;
	if (trueWidth % CU_SIZE)
		width = trueWidth + (CU_SIZE - (trueWidth % CU_SIZE));
	if (trueHeight % CU_SIZE)
		height = trueHeight + (CU_SIZE - (trueHeight % CU_SIZE));

	// Pad the image
	img.resize(width, height, 1, channels , 0, 1);

	// Manually define the quantization parameters for now
	paramStruct param;
	param.q1 = 1;
	param.q2 = param.q1;
	param.isGray = channels == 1 ? true : false;
	param.chromaSubsample = true;

	// Allocate space for the YCbCr values
	CImg<s16> Y(width, height, 1, 1, 0);
	CImg<s16> Cb(width, height, 1, 1, 0);
	CImg<s16> Cr(width, height, 1, 1, 0);

	// Handle grayscale and color images separately
	const u32 chOffset = width * height;
	if (param.isGray)
	{
		Y = img;
	}
	else
	{
		// Apply the JPEG YCbCr forward transform
		for (u32 i = 0; i < chOffset; i++)
		{
			double y = round(0.299 * (double)img(i) + 0.587 * (double)img(i + chOffset) + 0.114 * (double)img(i + 2 * chOffset));
			double cb = round(128 - 0.168736 * (double)img(i) - 0.331264 * (double)img(i + chOffset) + 0.5 * (double)img(i + 2 * chOffset));
			double cr = round(128 + 0.5 * (double)img(i) - 0.418688 * (double)img(i + chOffset) - 0.081312 * (double)img(i + 2 * chOffset));

			Y(i) = (s16)((y < 0) ? 0 : ((y > 255) ? 255 : y));
			Cb(i) = (s16)((cb < 0) ? 0 : ((cb > 255) ? 255 : cb));
			Cr(i) = (s16)((cr < 0) ? 0 : ((cr > 255) ? 255 : cr));
		}

		// Check if the color channels are empty
		if (Cb.mean() == 128 && Cr.mean() == 128)
		{
			param.isGray = true;
		}
	}

	// Initialize the arithmetic encoder assuming 24 bits per pixel
	InitializeEncoder(24 * width * height);

	// Process each coding unit (CU)
	for (u32 y = 0; y < height; y += CU_SIZE)
	{
		for (u32 x = 0; x < width; x += CU_SIZE)
		{
			// Copy the CU pointers
			static cuStruct cu;
			cu.cbLuma = &Y(x, y);
			cu.cbChroma1 = &Cb(x, y);
			cu.cbChroma2 = &Cr(x, y);

			SiCEncCU(cu, width, param);
		}
	}

	// Terminate the encoding process and write to file
	EncodeTerminate();
	WriteBitstream("../../SiCDec/SiCDec/test.sic", trueWidth, trueHeight, channels, param);

	// Handle grayscale and color images separately
	if (param.isGray)
	{
		img.channel(1) = Y;
		img.channel(2) = Y;
		img.channel(3) = Y;
	}
	else
	{
		// Apply the JPEG YCbCr forward transform
		for (u32 i = 0; i < chOffset; i++)
		{
			double r = round((double)Y(i) + 1.402 * (double)(Cr(i) - 128));
			double g = round((double)Y(i) - 0.344136 * (double)(Cb(i) - 128) - 0.714136 * (double)(Cr(i) - 128));
			double b = round((double)Y(i) + 1.772 * (double)(Cb(i) - 128));

			img(i) = (s16)((r < 0) ? 0 : ((r > 255) ? 255 : r));
			img(i + chOffset) = (s16)((g < 0) ? 0 : ((g > 255) ? 255 : g));
			img(i + 2 * chOffset) = (s16)((b < 0) ? 0 : ((b > 255) ? 255 : b));
		}
	}

	printf("%.4f\n", img.PSNR(imgRef, 255));
	img.display();

	//system("PAUSE");
	return 0;
}