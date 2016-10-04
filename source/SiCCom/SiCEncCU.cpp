#include "SiCEncCU.h"
#include <cstring>

#include "CImg.h"
using namespace cimg_library;

void SiCEncCU(cuStruct cu, u32 stride, paramStruct param)
{
	// Create a buffer for the coding blocks (CB) and the sub-image coding blocks (SCB)
	const u16 cbNumPix = CU_SIZE * CU_SIZE;
	static u8 cbLuma[cbNumPix];
	static u8 cbChroma1[cbNumPix >> 2];
	static u8 cbChroma2[cbNumPix >> 2];
	static u8 vscbLuma[cbNumPix >> 3];
	static u8 vscbChroma1[cbNumPix >> 5];
	static u8 vscbChroma2[cbNumPix >> 5];
	static u8 hscbLuma[cbNumPix >> 3];
	static u8 hscbChroma1[cbNumPix >> 5];
	static u8 hscbChroma2[cbNumPix >> 5];

	// Define the horizontal and vertical sub-coding units
	static cuStruct vscu = { vscbLuma, vscbChroma1, vscbChroma2 };
	static cuStruct hscu = { hscbLuma, hscbChroma1, hscbChroma2 };

	// Copy pixels to the CBs
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		memcpy(&cbLuma[y * CU_SIZE], &cu.pLuma[y * stride], CU_SIZE * sizeof(u8));
		memcpy(&cbChroma1[y * CU_SIZE / 2], &cu.pChroma1[y * stride / 2], CU_SIZE * sizeof(u8) / 2);
		memcpy(&cbChroma2[y * CU_SIZE / 2], &cu.pChroma2[y * stride / 2], CU_SIZE * sizeof(u8) / 2);
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		memcpy(&cbLuma[y * CU_SIZE], &cu.pLuma[y * stride], CU_SIZE * sizeof(u8));
	}

	CImg<u8> Y(vscbLuma, CU_SIZE, CU_SIZE / 8);
	CImg<u8> Cb(vscbChroma1, CU_SIZE / 2, CU_SIZE / 16);
	CImg<u8> Cr(vscbChroma2, CU_SIZE / 2, CU_SIZE / 16);
	Cb.resize_doubleXY();
	Cr.resize_doubleXY();

	CImg<u8> Z(CU_SIZE, CU_SIZE / 8, 1, 3);
	for (u16 i = 0; i < cbNumPix / 8; i++)
	{
		float r = (float)Y(i) + 1.402 * ((float)Cr(i) - 128);
		float g = (float)Y(i) - 0.344136 * ((float)Cb(i) - 128) - 0.714136 * ((float)Cr(i) - 128);
		float b = (float)Y(i) + 1.772 * ((float)Cb(i) - 128);
		Z(i) = r < 0 ? 0 : (r > 255 ? 255 : r);
		Z(i + cbNumPix) = g < 0 ? 0 : (g > 255 ? 255 : g);
		Z(i + 2 * cbNumPix) = b < 0 ? 0 : (b > 255 ? 255 : b);
	}
	Z.display();
}