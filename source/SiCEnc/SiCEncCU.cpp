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
	static cuStruct cu = { cbLuma, cbChroma1, cbChroma2 };
	static scuStruct hscu = { hscbLuma, hscbChroma1, hscbChroma2 };
	static scuStruct vscu = { vscbLuma, vscbChroma1, vscbChroma2 };

	// Copy pixels to the CU and the SCUs
	copyToCU(img, width, height, &cu, param.chromaSub);
	copyToSCU(&cu, &hscu, &vscu);

	// Copy the reference pixels
	memcpy(cbResLuma, cbLuma, cbNumPix * sizeof(s16));
	memcpy(cbResChroma1, cbChroma1, cbNumPix * sizeof(s16));
	memcpy(cbResChroma2, cbChroma2, cbNumPix * sizeof(s16));

	// Define the sub-image transform unit (STU)
	static stuStruct stu = { &vscu, &hscu };

	// Apply the forward DCT to the STU
	tuForward(&stu, param.chromaSub);

	//// Quantize the STU
	//stuQuantConst(stu, param.q1);
	////stuEnc(stu);
	//stuDequantConst(stu, param.q1);

	// Apply the inverse DCT to the sub-images
	tuInverse(&stu, param.chromaSub);

	// Copy back the reconstructed pixels
	copyFromSCU(&cu, &hscu, &vscu);

	// Define the prediction unit (PU)
	static u8 pbModeLuma[cbNumPix / 64];
	static u8 pbModeChroma[cbNumPix / 64];
	static ScanDir scanLuma[cbNumPix / 64];
	static ScanDir scanChroma[cbNumPix / 64];
	static puStruct pu = { &cu, pbModeLuma, pbModeChroma, scanLuma, scanChroma };

	//// Find the optimal predictors and apply to the PU
	//predSearch(pu);
	//puEnc(pu);

	//// Calculate the residual
	//for (u16 i = 0; i < cbNumPix / 4; i++)
	//{
	//	cbResLuma[i] -= cbLuma[i];
	//	cbResChroma1[i] -= cbChroma1[i];
	//	cbResChroma2[i] -= cbChroma2[i];
	//}
	//for (u16 i = cbNumPix / 4; i < cbNumPix; i++)
	//{
	//	cbResLuma[i] -= cbLuma[i];
	//}

	//// Transform the residual
	//static rtuStruct rtu = { cbResLuma, cbResChroma1, cbResChroma2, scanLuma, scanChroma };
	//rtuForward(rtu);
	//rtuQuantConst(rtu, param.q2);

	////rtuEnc(rtu);

	//rtuDequantConst(rtu, param.q2);
	//rtuInverse(rtu);

	//// Reconstruct the CU
	//for (u16 y = 0; y < CU_SIZE / 2; y++)
	//{
	//	for (u16 x = 0; x < CU_SIZE / 2; x++)
	//	{
	//		cbLuma[CU_SIZE * y + x] += cbResLuma[CU_SIZE * y + x];
	//		cbChroma1[CU_SIZE / 2 * y + x] += cbResChroma1[CU_SIZE / 2 * y + x];
	//		cbChroma2[CU_SIZE / 2 * y + x] += cbResChroma2[CU_SIZE / 2 * y + x];
	//	}
	//	for (u16 x = CU_SIZE / 2; x < CU_SIZE; x++)
	//	{
	//		cbLuma[CU_SIZE * y + x] += cbResLuma[CU_SIZE * y + x];
	//	}
	//}
	//for (u16 y = CU_SIZE / 2; y < CU_SIZE; y++)
	//{
	//	for (u16 x = 0; x < CU_SIZE; x++)
	//	{
	//		cbLuma[CU_SIZE * y + x] += cbResLuma[CU_SIZE * y + x];
	//	}
	//}

	// Copy pixels to the image
	copyFromCU(img, width, height, &cu, param.chromaSub);
}

void copyToCU(s16 *img, u16 width, u16 height, cuStruct *cu, ChromaSub chromaSub)
{
	// Calculate the channel offset
	const u32 chOffset = width * height;

	// Copy luma pixels to the CBs and the SCBs
	for (u8 y = 0; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			cu->cbLuma[CU_SIZE * y + x] = img[width * y + x];
		}
	}

	// Copy chroma pixels to the CBs and the SCBs
	if (chromaSub == CHROMA_444)
	{
		for (u8 y = 0; y < CU_SIZE; y++)
		{
			for (u8 x = 0; x < CU_SIZE; x++)
			{
				cu->cbChroma1[CU_SIZE * y + x] = img[width * y + x + chOffset];
				cu->cbChroma2[CU_SIZE * y + x] = img[width * y + x + 2 * chOffset];
			}
		}
	}
	else if (chromaSub == CHROMA_420)
	{
		for (u8 y = 0; y < CU_SIZE; y += 2)
		{
			for (u8 x = 0; x < CU_SIZE; x += 2)
			{
				cu->cbChroma1[CU_SIZE * (y / 2) + x / 2] = (img[width * y + x + chOffset] + img[width * y + x + 1+ chOffset] + img[width * (y + 1) + x + chOffset] + img[width * (y + 1) + x + 1 + chOffset] + 2) / 4;
				cu->cbChroma2[CU_SIZE * (y / 2) + x / 2] = (img[width * y + x + 2 * chOffset] + img[width * y + x + 1 + 2 * chOffset] + img[width * (y + 1) + x + 2 * chOffset] + img[width * (y + 1) + x + 1 + 2 * chOffset] + 2) / 4;
			}
		}
	}
}

void copyFromCU(s16 *img, u16 width, u16 height, cuStruct *cu, ChromaSub chromaSub)
{
	// Calculate the channel offset
	const u32 chOffset = width * height;

	// Copy luma pixels to the CBs and the SCBs
	for (u8 y = 0; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			img[width * y + x] = cu->cbLuma[CU_SIZE * y + x];
		}
	}

	// Copy chroma pixels to the CBs and the SCBs
	if (chromaSub == CHROMA_444)
	{
		for (u8 y = 0; y < CU_SIZE; y++)
		{
			for (u8 x = 0; x < CU_SIZE; x++)
			{
				img[width * y + x + chOffset] = cu->cbChroma1[CU_SIZE * y + x];
				img[width * y + x + 2 * chOffset] = cu->cbChroma2[CU_SIZE * y + x];
			}
		}
	}
	else if (chromaSub == CHROMA_420)
	{
		for (u8 y = 0; y < CU_SIZE; y += 2)
		{
			for (u8 x = 0; x < CU_SIZE; x += 2)
			{
				img[width * y + x + chOffset] = cu->cbChroma1[CU_SIZE * (y / 2) + x / 2];
				img[width * y + x + 1 + chOffset] = cu->cbChroma1[CU_SIZE * (y / 2) + x / 2];
				img[width * (y + 1) + x + chOffset] = cu->cbChroma1[CU_SIZE * (y / 2) + x / 2];
				img[width * (y + 1) + x + 1 + chOffset] = cu->cbChroma1[CU_SIZE * (y / 2) + x / 2];


				img[width * y + x + 2 * chOffset] = cu->cbChroma2[CU_SIZE * (y / 2) + x / 2];
				img[width * y + x + 1 + 2 * chOffset] = cu->cbChroma2[CU_SIZE * (y / 2) + x / 2];
				img[width * (y + 1) + x + 2 * chOffset] = cu->cbChroma2[CU_SIZE * (y / 2) + x / 2];
				img[width * (y + 1) + x + 1 + 2 * chOffset] = cu->cbChroma2[CU_SIZE * (y / 2) + x / 2];
			}
		}
	}
}

void copyToSCU(cuStruct *cu, scuStruct *hscu, scuStruct *vscu)
{
	// Copy pixels from the CU to the SCU
	for (u8 y = 7; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			hscu->scbLuma[CU_SIZE / 8 * x + y / 8] = cu->cbLuma[CU_SIZE * x + y];
			hscu->scbChroma1[CU_SIZE / 8 * x + y / 8] = cu->cbChroma1[CU_SIZE * x + y];
			hscu->scbChroma2[CU_SIZE / 8 * x + y / 8] = cu->cbChroma2[CU_SIZE * x + y];

			vscu->scbLuma[CU_SIZE * (y / 8) + x] = cu->cbLuma[CU_SIZE * y + x];
			vscu->scbChroma1[CU_SIZE * (y / 8) + x] = cu->cbChroma1[CU_SIZE * y + x];
			vscu->scbChroma2[CU_SIZE * (y / 8) + x] = cu->cbChroma2[CU_SIZE * y + x];
		}
	}
}

void copyFromSCU(cuStruct *cu, scuStruct *hscu, scuStruct *vscu)
{
	// Copy pixels from the CU to the SCU
	for (u8 y = 7; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			cu->cbLuma[CU_SIZE * x + y] = hscu->scbLuma[CU_SIZE / 8 * x + y / 8];
			cu->cbChroma1[CU_SIZE * x + y] = hscu->scbChroma1[CU_SIZE / 8 * x + y / 8];
			cu->cbChroma2[CU_SIZE * x + y] = hscu->scbChroma2[CU_SIZE / 8 * x + y / 8];

			if (x % 8 < 7)
			{
				cu->cbLuma[CU_SIZE * y + x] = vscu->scbLuma[CU_SIZE * (y / 8) + x];
				cu->cbChroma1[CU_SIZE * y + x] = vscu->scbChroma1[CU_SIZE * (y / 8) + x];
				cu->cbChroma2[CU_SIZE * y + x] = vscu->scbChroma2[CU_SIZE * (y / 8) + x];
			}
			else
			{
				cu->cbLuma[CU_SIZE * y + x] = (cu->cbLuma[CU_SIZE * y + x] + vscu->scbLuma[CU_SIZE * (y / 8) + x] + 1) / 2;
				cu->cbChroma1[CU_SIZE * y + x] = (cu->cbChroma1[CU_SIZE * y + x] + vscu->scbChroma1[CU_SIZE * (y / 8) + x] + 1) / 2;
				cu->cbChroma2[CU_SIZE * y + x] = (cu->cbChroma2[CU_SIZE * y + x] + vscu->scbChroma2[CU_SIZE * (y / 8) + x] + 1) / 2;
			}
		}
	}
}
