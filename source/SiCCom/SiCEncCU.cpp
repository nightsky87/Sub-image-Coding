#include "SiCEncCU.h"

void SiCEncCU(cuStruct cu, u32 stride, paramStruct param)
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

	// Copy pixels to the CBs and the vertical SCBs
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		memcpy(&cbLuma[y * CU_SIZE], &cu.cbLuma[y * stride], CU_SIZE * sizeof(s16));
		memcpy(&cbChroma1[y * CU_SIZE / 2], &cu.cbChroma1[y * stride / 2], CU_SIZE * sizeof(s16) / 2);
		memcpy(&cbChroma2[y * CU_SIZE / 2], &cu.cbChroma2[y * stride / 2], CU_SIZE * sizeof(s16) / 2);

		if (y % 8 == 7)
		{
			memcpy(&vscbLuma[(y >> 3) * CU_SIZE], &cu.cbLuma[y * stride], CU_SIZE * sizeof(s16));
			memcpy(&vscbChroma1[(y >> 3) * CU_SIZE / 2], &cu.cbChroma1[y * stride / 2], CU_SIZE * sizeof(s16) / 2);
			memcpy(&vscbChroma2[(y >> 3) * CU_SIZE / 2], &cu.cbChroma2[y * stride / 2], CU_SIZE * sizeof(s16) / 2);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		memcpy(&cbLuma[y * CU_SIZE], &cu.cbLuma[y * stride], CU_SIZE * sizeof(s16));

		if (y % 8 == 7)
		{
			memcpy(&vscbLuma[(y >> 3) * CU_SIZE], &cu.cbLuma[y * stride], CU_SIZE * sizeof(s16));
		}
	}

	// Copy pixels to the horizontal SCBs
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 7; x < CU_SIZE / 2; x += 8)
		{
			hscbLuma[y * CU_SIZE / 8 + (x >> 3)] = cbLuma[y * CU_SIZE + x];
			hscbChroma1[y * CU_SIZE / 16 + (x >> 3)] = cbChroma1[y * CU_SIZE / 2 + x];
			hscbChroma2[y * CU_SIZE / 16 + (x >> 3)] = cbChroma2[y * CU_SIZE / 2 + x];
		}
		for (u8 x = CU_SIZE / 2 + 7; x < CU_SIZE; x += 8)
		{
			hscbLuma[y * CU_SIZE / 8 + (x >> 3)] = cbLuma[y * CU_SIZE + x];
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 7; x < CU_SIZE; x += 8)
		{
			hscbLuma[y * CU_SIZE / 8 + (x >> 3)] = cbLuma[y * CU_SIZE + x];
		}
	}

	// Copy the reference pixels
	memcpy(cbResLuma, cbLuma, cbNumPix * sizeof(s16));
	memcpy(cbResChroma1, cbChroma1, cbNumPix / 4 * sizeof(s16));
	memcpy(cbResChroma2, cbChroma2, cbNumPix / 4 * sizeof(s16));

	// Define the sub-image transform unit (STU)
	static stuStruct stu = { &vscu, &hscu };

	// Apply the forward DCT to the STU
	stuForward(stu);

	// Quantize the STU
	stuQuantConst(stu, param.q1);

	// INSERT CABAC ROUTINE HERE

	// Dequantize the sub-image coefficients
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
	static puStruct pu = { &thisCU, pbModeLuma, pbModeChroma };

	// Find the optimal predictors and apply to the PU
	predSearch(pu);

	// INSERT CABAC ROUTINE HERE

	// Calculate the residual
	for (u16 i = 0; i < cbNumPix / 4; i++)
	{
		cbResLuma[i] -= cbLuma[i];
		cbResChroma1[i] -= cbChroma1[i];
		cbResChroma2[i] -= cbChroma2[i];
	}
	for (u16 i = cbNumPix / 4; i < cbNumPix; i++)
	{
		cbResLuma[i] -= cbLuma[i];
	}

	// Transform the residual
	static rtuStruct rtu = { cbResLuma, cbResChroma1, cbResChroma2 };
	rtuForward(rtu);
	rtuQuantConst(rtu, param.q2);

	// INSERT CABAC ROUTINE HERE

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