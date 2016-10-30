#include "SiCEncCU.h"

void SiCEncCU(s16 *img, u16 width, u16 height, paramStruct param)
{
	// Create a buffer for the coding blocks (CB) and the sub-image coding blocks (SCB)
	const u16 cbNumPix = CU_SIZE * CU_SIZE;

	static s16 cbLuma[cbNumPix], cbResLuma[cbNumPix];
	static s16 cbChroma1[cbNumPix], cbResChroma1[cbNumPix];
	static s16 cbChroma2[cbNumPix], cbResChroma2[cbNumPix];
	
	static s16 hscbLuma[cbNumPix / 8];
	static s16 hscbChroma1[cbNumPix / 8];
	static s16 hscbChroma2[cbNumPix / 8];

	static s16 vscbLuma[cbNumPix / 8];
	static s16 vscbChroma1[cbNumPix / 8];
	static s16 vscbChroma2[cbNumPix / 8];

	// Define the coding unit and the horizontal and vertical sub-coding units
	static cuStruct cu = { cbLuma, cbChroma1, cbChroma2, CU_SIZE, CU_SIZE, CU_SIZE, param.chromaSub };
	static scuStruct hscu = { hscbLuma, hscbChroma1, hscbChroma2, CU_SIZE / 8, CU_SIZE, CU_SIZE / 8, param.chromaSub };
	static scuStruct vscu = { vscbLuma, vscbChroma1, vscbChroma2, CU_SIZE, CU_SIZE / 8, CU_SIZE, param.chromaSub };

	// Copy pixels to the CU and the SCUs
	copyToCU(img, width, height, cu);
	copyToSCU(cu, hscu, vscu);

	// Copy the reference pixels
	memcpy(cbResLuma, cbLuma, cbNumPix * sizeof(s16));
	memcpy(cbResChroma1, cbChroma1, cbNumPix * sizeof(s16));
	memcpy(cbResChroma2, cbChroma2, cbNumPix * sizeof(s16));

	// Define the sub-image transform unit (STU)
	static stuStruct stu = { &vscu, &hscu, CU_SIZE, CU_SIZE, CU_SIZE, param.chromaSub };

	// Apply the forward DCT to the STU
	tuForward(stu);

	// Quantize the STU
	quantConst(stu, param.q1);
	stuEnc(stu);
	dequantConst(stu, param.q1);

	// Apply the inverse DCT to the sub-images
	tuInverse(stu);

	// Copy back the reconstructed pixels
	copyFromSCU(cu, hscu, vscu);

	// Define the prediction unit (PU)
	static u8 pbModeLuma[cbNumPix / 64];
	static u8 pbModeChroma[cbNumPix / 64];
	static ScanDir scanLuma[cbNumPix / 64];
	static ScanDir scanChroma[cbNumPix / 64];
	static puStruct pu = { &cu, pbModeLuma, pbModeChroma, scanLuma, scanChroma, CU_SIZE / 8, CU_SIZE / 8, CU_SIZE / 8, param.chromaSub };

	// Find the optimal predictors and apply to the PU
	predSearch(pu);
	puEnc(pu);

	// Calculate the residual
	static cuStruct cuRes = { cbResLuma, cbResChroma1, cbResChroma2, CU_SIZE, CU_SIZE, CU_SIZE, param.chromaSub };
	cuRes = cuRes - cu;

	// Transform the residual
	static rtuStruct rtu = { cbResLuma, cbResChroma1, cbResChroma2, scanLuma, scanChroma, CU_SIZE, CU_SIZE, CU_SIZE, param.chromaSub };
	tuForward(rtu);
	quantConst(rtu, param.q2);

	rtuEnc(rtu);

	dequantConst(rtu, param.q2);
	tuInverse(rtu);

	// Reconstruct the CU
	cu = cu + cuRes;

	// Copy pixels to the image
	copyFromCU(img, width, height, cu);
}

void copyToCU(s16 *img, u16 width, u16 height, cuStruct &cu)
{
	// Calculate the channel offset
	const u32 chOffset = width * height;

	// Copy luma pixels to the CBs and the SCBs
	for (u8 y = 0; y < cu.height; y++)
	{
		for (u8 x = 0; x < cu.width; x++)
		{
			cu.cbLuma[cu.stride * y + x] = img[width * y + x];
		}
	}

	// Copy chroma pixels to the CBs and the SCBs
	if (cu.chromaSub == CHROMA_444)
	{
		for (u8 y = 0; y < cu.height; y++)
		{
			for (u8 x = 0; x < cu.width; x++)
			{
				cu.cbChroma1[cu.stride * y + x] = img[width * y + x + chOffset];
				cu.cbChroma2[cu.stride * y + x] = img[width * y + x + 2 * chOffset];
			}
		}
	}
	else if (cu.chromaSub == CHROMA_420)
	{
		for (u8 y = 0; y < cu.height; y += 2)
		{
			for (u8 x = 0; x < cu.width; x += 2)
			{
				cu.cbChroma1[cu.stride * (y / 2) + x / 2] = (img[width * y + x + chOffset] + img[width * y + x + 1 + chOffset] + img[width * (y + 1) + x + chOffset] + img[width * (y + 1) + x + 1 + chOffset] + 2) / 4;
				cu.cbChroma2[cu.stride * (y / 2) + x / 2] = (img[width * y + x + 2 * chOffset] + img[width * y + x + 1 + 2 * chOffset] + img[width * (y + 1) + x + 2 * chOffset] + img[width * (y + 1) + x + 1 + 2 * chOffset] + 2) / 4;
			}
		}
	}
}

void copyFromCU(s16 *img, u16 width, u16 height, cuStruct &cu)
{
	// Calculate the channel offset
	const u32 chOffset = width * height;

	// Copy luma pixels to the CBs and the SCBs
	for (u8 y = 0; y < cu.height; y++)
	{
		for (u8 x = 0; x < cu.width; x++)
		{
			img[width * y + x] = cu.cbLuma[cu.stride * y + x];
		}
	}

	// Copy chroma pixels to the CBs and the SCBs
	if (cu.chromaSub == CHROMA_444)
	{
		for (u8 y = 0; y < cu.height; y++)
		{
			for (u8 x = 0; x < cu.width; x++)
			{
				img[width * y + x + chOffset] = cu.cbChroma1[cu.stride * y + x];
				img[width * y + x + 2 * chOffset] = cu.cbChroma2[cu.stride * y + x];
			}
		}
	}
	else if (cu.chromaSub == CHROMA_420)
	{
		for (u8 y = 0; y < cu.height; y += 2)
		{
			for (u8 x = 0; x < cu.width; x += 2)
			{
				img[width * y + x + chOffset] = cu.cbChroma1[cu.stride * (y / 2) + x / 2];
				img[width * y + x + 1 + chOffset] = cu.cbChroma1[cu.stride * (y / 2) + x / 2];
				img[width * (y + 1) + x + chOffset] = cu.cbChroma1[cu.stride * (y / 2) + x / 2];
				img[width * (y + 1) + x + 1 + chOffset] = cu.cbChroma1[cu.stride * (y / 2) + x / 2];


				img[width * y + x + 2 * chOffset] = cu.cbChroma2[cu.stride * (y / 2) + x / 2];
				img[width * y + x + 1 + 2 * chOffset] = cu.cbChroma2[cu.stride * (y / 2) + x / 2];
				img[width * (y + 1) + x + 2 * chOffset] = cu.cbChroma2[cu.stride * (y / 2) + x / 2];
				img[width * (y + 1) + x + 1 + 2 * chOffset] = cu.cbChroma2[cu.stride * (y / 2) + x / 2];
			}
		}
	}
}

void copyToSCU(cuStruct &cu, scuStruct &hscu, scuStruct &vscu)
{
	// Copy pixels from the CU to the SCU
	for (u8 y = 7; y < cu.height; y += 8)
	{
		for (u8 x = 0; x < cu.width; x++)
		{
			hscu.scbLuma[hscu.stride * x + y / 8] = cu.cbLuma[cu.stride * x + y];
			hscu.scbChroma1[hscu.stride * x + y / 8] = cu.cbChroma1[cu.stride * x + y];
			hscu.scbChroma2[hscu.stride * x + y / 8] = cu.cbChroma2[cu.stride * x + y];

			vscu.scbLuma[vscu.stride * (y / 8) + x] = cu.cbLuma[cu.stride * y + x];
			vscu.scbChroma1[vscu.stride * (y / 8) + x] = cu.cbChroma1[cu.stride * y + x];
			vscu.scbChroma2[vscu.stride * (y / 8) + x] = cu.cbChroma2[cu.stride * y + x];
		}
	}
}

void copyFromSCU(cuStruct &cu, scuStruct &hscu, scuStruct &vscu)
{
	// Copy pixels from the CU to the SCU
	for (u8 y = 7; y < cu.height; y += 8)
	{
		for (u8 x = 0; x < cu.width; x++)
		{
			cu.cbLuma[cu.stride * x + y] = hscu.scbLuma[hscu.stride * x + y / 8];
			cu.cbChroma1[cu.stride * x + y] = hscu.scbChroma1[hscu.stride * x + y / 8];
			cu.cbChroma2[cu.stride * x + y] = hscu.scbChroma2[hscu.stride * x + y / 8];

			if (x % 8 < 7)
			{
				cu.cbLuma[cu.stride * y + x] = vscu.scbLuma[vscu.stride * (y / 8) + x];
				cu.cbChroma1[cu.stride * y + x] = vscu.scbChroma1[vscu.stride * (y / 8) + x];
				cu.cbChroma2[cu.stride * y + x] = vscu.scbChroma2[vscu.stride * (y / 8) + x];
			}
			else
			{
				cu.cbLuma[cu.stride * y + x] = (cu.cbLuma[cu.stride * y + x] + vscu.scbLuma[vscu.stride * (y / 8) + x] + 1) / 2;
				cu.cbChroma1[cu.stride * y + x] = (cu.cbChroma1[cu.stride * y + x] + vscu.scbChroma1[vscu.stride * (y / 8) + x] + 1) / 2;
				cu.cbChroma2[cu.stride * y + x] = (cu.cbChroma2[cu.stride * y + x] + vscu.scbChroma2[vscu.stride * (y / 8) + x] + 1) / 2;
			}
		}
	}
}
