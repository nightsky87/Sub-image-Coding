#include "SiCDecCU.h"

void SiCDecCU(cuStruct cu, u32 stride, paramStruct param)
{
	// Create a buffer for the coding blocks (CB) and the sub-image coding blocks (SCB)
	const u16 cbNumPix = CU_SIZE * CU_SIZE;
	static s16 cbLuma[cbNumPix], cbResLuma[cbNumPix];
	static s16 cbChroma1[cbNumPix >> 2], cbResChroma1[cbNumPix >> 2];
	static s16 cbChroma2[cbNumPix >> 2], cbResChroma2[cbNumPix >> 2];
	static s16 vscbLuma[cbNumPix >> 3];
	static s16 vscbChroma1[cbNumPix >> 5];
	static s16 vscbChroma2[cbNumPix >> 5];
	static s16 hscbLuma[cbNumPix >> 3];
	static s16 hscbChroma1[cbNumPix >> 5];
	static s16 hscbChroma2[cbNumPix >> 5];

	// Define the horizontal and vertical sub-coding units
	static scuStruct vscu = { vscbLuma, vscbChroma1, vscbChroma2 };
	static scuStruct hscu = { hscbLuma, hscbChroma1, hscbChroma2 };

	// Fill all components with zeros
	memset(cbLuma, 0, cbNumPix * sizeof(s16));
	memset(cbChroma1, 0, cbNumPix / 4 * sizeof(s16));
	memset(cbChroma2, 0, cbNumPix / 4 * sizeof(s16));
	memset(vscbLuma, 0, cbNumPix / 8 * sizeof(s16));
	memset(vscbChroma1, 0, cbNumPix / 32 * sizeof(s16));
	memset(vscbChroma2, 0, cbNumPix / 32 * sizeof(s16));
	memset(hscbLuma, 0, cbNumPix / 8 * sizeof(s16));
	memset(hscbChroma1, 0, cbNumPix / 32 * sizeof(s16));
	memset(hscbChroma2, 0, cbNumPix / 32 * sizeof(s16));

	// Decode the sub-image transform units (STUs)
	static stuStruct stu = { &vscu, &hscu };
	stuDec(stu);
	stuDequantConst(stu, param.q1);

	// Apply the inverse DCT to the sub-images
	stuInverse(stu);

	// Copy back the reconstructed vertical SCB pixels
	for (u8 y = 7; y < CU_SIZE / 2; y += 8)
	{
		memcpy(&cbLuma[y * CU_SIZE], &vscbLuma[(y >> 3) * CU_SIZE], CU_SIZE * sizeof(s16));
		memcpy(&cbChroma1[y * CU_SIZE / 2], &vscbChroma1[(y >> 3) * CU_SIZE / 2], CU_SIZE * sizeof(s16) / 2);
		memcpy(&cbChroma2[y * CU_SIZE / 2], &vscbChroma2[(y >> 3) * CU_SIZE / 2], CU_SIZE * sizeof(s16) / 2);
	}
	for (u8 y = CU_SIZE / 2 + 7; y < CU_SIZE; y += 8)
	{
		memcpy(&cbLuma[y * CU_SIZE], &vscbLuma[(y >> 3) * CU_SIZE], CU_SIZE * sizeof(s16));
	}

	// Copy back the reconstructed horizontal SCB pixels
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		if (y % 8 != 7)
		{
			for (u8 x = 7; x < CU_SIZE / 2; x += 8)
			{
				cbLuma[y * CU_SIZE + x] = hscbLuma[y * CU_SIZE / 8 + (x >> 3)];
				cbChroma1[y * CU_SIZE / 2 + x] = hscbChroma1[y * CU_SIZE / 16 + (x >> 3)];
				cbChroma2[y * CU_SIZE / 2 + x] = hscbChroma2[y * CU_SIZE / 16 + (x >> 3)];
			}
			for (u8 x = CU_SIZE / 2 + 7; x < CU_SIZE; x += 8)
			{
				cbLuma[y * CU_SIZE + x] = hscbLuma[y * CU_SIZE / 8 + (x >> 3)];
			}
		}
		else
		{
			for (u8 x = 7; x < CU_SIZE / 2; x += 8)
			{
				cbLuma[y * CU_SIZE + x] += hscbLuma[y * CU_SIZE / 8 + (x >> 3)];
				cbChroma1[y * CU_SIZE / 2 + x] += hscbChroma1[y * CU_SIZE / 16 + (x >> 3)];
				cbChroma2[y * CU_SIZE / 2 + x] += hscbChroma2[y * CU_SIZE / 16 + (x >> 3)];

				cbLuma[y * CU_SIZE + x] >>= 1;
				cbChroma1[y * CU_SIZE / 2 + x] >>= 1;
				cbChroma2[y * CU_SIZE / 2 + x] >>= 1;
			}
			for (u8 x = CU_SIZE / 2 + 7; x < CU_SIZE; x += 8)
			{
				cbLuma[y * CU_SIZE + x] += hscbLuma[y * CU_SIZE / 8 + (x >> 3)];
				cbLuma[y * CU_SIZE + x] >>= 1;
			}
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		if (y % 8 != 7)
		{
			for (u8 x = 7; x < CU_SIZE; x += 8)
			{
				cbLuma[y * CU_SIZE + x] = hscbLuma[y * CU_SIZE / 8 + (x >> 3)];
			}
		}
		else
		{
			for (u8 x = 7; x < CU_SIZE; x += 8)
			{
				cbLuma[y * CU_SIZE + x] += hscbLuma[y * CU_SIZE / 8 + (x >> 3)];
				cbLuma[y * CU_SIZE + x] >>= 1;
			}
		}
	}

	// Define the prediction unit (PU)
	static cuStruct thisCU = { cbLuma, cbChroma1, cbChroma2 };
	static u8 pbModeLuma[cbNumPix >> 6];
	static u8 pbModeChroma[cbNumPix >> 8];
	static scanDir scanLuma[cbNumPix >> 6];
	static scanDir scanChroma[cbNumPix >> 8];
	static puStruct pu = { &thisCU, pbModeLuma, pbModeChroma, scanLuma, scanChroma };

	// Decode the prediction modes and apply prediction
	puDec(pu);
	predPU(pu);

	// Decode and transform the residual
	static rtuStruct rtu = { cbResLuma, cbResChroma1, cbResChroma2, scanLuma, scanChroma };
	rtuDec(rtu);
	rtuDequantConst(rtu, param.q2);
	rtuInverse(rtu);

	// Reconstruct the CU
	for (u16 y = 0; y < CU_SIZE / 2; y++)
	{
		if (y % 8 == 7)
			continue;

		for (u16 x = 0; x < CU_SIZE / 2; x++)
		{
			if (x % 8 == 7)
				continue;

			cbLuma[CU_SIZE * y + x] += cbResLuma[CU_SIZE * y + x];
			cbChroma1[CU_SIZE / 2 * y + x] += cbResChroma1[CU_SIZE / 2 * y + x];
			cbChroma2[CU_SIZE / 2 * y + x] += cbResChroma2[CU_SIZE / 2 * y + x];
		}
		for (u16 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			if (x % 8 == 7)
				continue;

			cbLuma[CU_SIZE * y + x] += cbResLuma[CU_SIZE * y + x];
		}
	}
	for (u16 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		if (y % 8 == 7)
			continue;

		for (u16 x = 0; x < CU_SIZE; x++)
		{
			if (x % 8 == 7)
				continue;

			cbLuma[CU_SIZE * y + x] += cbResLuma[CU_SIZE * y + x];
		}
	}

	// Copy pixels to the image
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		memcpy(&cu.cbLuma[y * stride], &cbLuma[y * CU_SIZE], CU_SIZE * sizeof(s16));
		memcpy(&cu.cbChroma1[y * stride / 2], &cbChroma1[y * CU_SIZE / 2], CU_SIZE * sizeof(s16) / 2);
		memcpy(&cu.cbChroma2[y * stride / 2], &cbChroma2[y * CU_SIZE / 2], CU_SIZE * sizeof(s16) / 2);
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		memcpy(&cu.cbLuma[y * stride], &cbLuma[y * CU_SIZE], CU_SIZE * sizeof(s16));
	}
}