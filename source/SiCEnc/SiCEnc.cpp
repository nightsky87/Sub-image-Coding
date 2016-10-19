#include "CImg.h"
#include "ComDef.h"
#include "SiCEncCU.h"

#include <cassert>

using namespace cimg_library;

int main()
{
	// Load a test image
	CImg<u8> img("../../../../images/Kodak/kodim23.bmp");

	// Determine the original dimensions
	u32 trueWidth = img.width();
	u32 trueHeight = img.height();
	u8  channels = img.spectrum();

	// Ensure that a 3-channel image is being used
	if (channels != 3)
	{
		printf("Only RGB color images are supported.");
		return 1;
	}

	// Calculate the modulo-64 dimensions
	u32 width = trueWidth;
	u32 height = trueHeight;
	if (trueWidth % CU_SIZE)
		width = trueWidth + (CU_SIZE - (trueWidth % CU_SIZE));
	if (trueHeight % CU_SIZE)
		height = trueHeight + (CU_SIZE - (trueHeight % CU_SIZE));

	// Pad the image
	img.resize(width, height, 1, channels , 0, 1);

	// Manually define the parameters for now
	paramStruct param;
	param.q1 = 128;
	param.q2 = 128;

	// Allocate space for the YCbCr values
	CImg<s16> Y(width, height);
	CImg<s16> Cb(width, height);
	CImg<s16> Cr(width, height);

	// Apply the JPEG YCbCr forward transform
	const u32 chOffset = width * height;
	for (u32 i = 0; i < chOffset; i++)
	{
		float y  = roundf(0.299 * (float)img(i) + 0.587 * (float)img(i + chOffset) + 0.114 * (float)img(i + 2 * chOffset));
		float cb = roundf(128 - 0.168736 * (float)img(i) - 0.331264 * (float)img(i + chOffset) + 0.5 * (float)img(i + 2 * chOffset));
		float cr = roundf(128 + 0.5 * (float)img(i) - 0.418688 * (float)img(i + chOffset) - 0.081312 * (float)img(i + 2 * chOffset));

		Y(i) = (y < 0) ? 0 : ((y > 255) ? 255 : y);
		Cb(i) = (cb < 0) ? 0 : ((cb > 255) ? 255 : cb);
		Cr(i) = (cr < 0) ? 0 : ((cr > 255) ? 255 : cr);
	}

	// Downsample the chroma channels
	Cb.resize_halfXY();
	Cr.resize_halfXY();

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

			SiCEncCU(cu, width, param);
		}
	}

	Cb.resize_doubleXY();
	Cr.resize_doubleXY();

	// Apply the JPEG YCbCr forward transform
	for (u32 i = 0; i < chOffset; i++)
	{
		float r = round((float)Y(i) + 1.402 * (float)(Cr(i) - 128));
		float g = round((float)Y(i) - 0.344136 * (float)(Cb(i) - 128) - 0.714136 * (float)(Cr(i) - 128));
		float b = round((float)Y(i) + 1.772 * (float)(Cb(i) - 128));

		img(i) = (r < 0) ? 0 : ((r > 255) ? 255 : r);
		img(i + chOffset) = (g < 0) ? 0 : ((g > 255) ? 255 : g);
		img(i + 2 * chOffset) = (b < 0) ? 0 : ((b > 255) ? 255 : b);
	}
	img.display();

	//system("PAUSE");
	return 0;
}