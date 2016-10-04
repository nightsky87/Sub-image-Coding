#include "SiCEncCU.h"
#include "SiCComTU.h"
#include "SiCComQuant.h"
#include <cstring>

void SiCEncCU(cuStruct cu, u32 stride, paramStruct param)
{
	// Create a buffer for the coding blocks (CB) and the sub-image coding blocks (SCB)
	const u16 cbNumPix = CU_SIZE * CU_SIZE;
	static s16 cbLuma[cbNumPix];
	static s16 cbChroma1[cbNumPix >> 2];
	static s16 cbChroma2[cbNumPix >> 2];
	static s16 vscbLuma[cbNumPix >> 3];
	static s16 vscbChroma1[cbNumPix >> 5];
	static s16 vscbChroma2[cbNumPix >> 5];
	static s16 hscbLuma[cbNumPix >> 3];
	static s16 hscbChroma1[cbNumPix >> 5];
	static s16 hscbChroma2[cbNumPix >> 5];

	// Define the horizontal and vertical sub-coding units
	static cuStruct vscu = { vscbLuma, vscbChroma1, vscbChroma2 };
	static cuStruct hscu = { hscbLuma, hscbChroma1, hscbChroma2 };

	// Copy pixels to the CBs and the vertical SCBs
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		memcpy(&cbLuma[y * CU_SIZE], &cu.pLuma[y * stride], CU_SIZE * sizeof(s16));
		memcpy(&cbChroma1[y * CU_SIZE / 2], &cu.pChroma1[y * stride / 2], CU_SIZE * sizeof(s16) / 2);
		memcpy(&cbChroma2[y * CU_SIZE / 2], &cu.pChroma2[y * stride / 2], CU_SIZE * sizeof(s16) / 2);

		if (y % 8 == 7)
		{
			memcpy(&vscbLuma[(y >> 3) * CU_SIZE], &cu.pLuma[y * stride], CU_SIZE * sizeof(s16));
			memcpy(&vscbChroma1[(y >> 3) * CU_SIZE / 2], &cu.pChroma1[y * stride / 2], CU_SIZE * sizeof(s16) / 2);
			memcpy(&vscbChroma2[(y >> 3) * CU_SIZE / 2], &cu.pChroma2[y * stride / 2], CU_SIZE * sizeof(s16) / 2);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		memcpy(&cbLuma[y * CU_SIZE], &cu.pLuma[y * stride], CU_SIZE * sizeof(s16));

		if (y % 8 == 7)
		{
			memcpy(&vscbLuma[(y >> 3) * CU_SIZE], &cu.pLuma[y * stride], CU_SIZE * sizeof(s16));
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

	// Apply the forward DCT to the sub-images
	vstuForward(vscu);
	hstuForward(hscu);

	// Quantize the sub-image coefficients
	scuQuantConst(vscu, param.q1);
	scuQuantConst(hscu, param.q1);

	// INSERT CABAC ROUTINE HERE

	// Dequantize the sub-image coefficients
	scuDequantConst(vscu, param.q1);
	scuDequantConst(hscu, param.q1);

	// Apply the inverse DCT to the sub-images
	vstuInverse(vscu);
	hstuInverse(hscu);

	// Copy back the reconstructed vertical SCB pixels
	for (u8 y = 7; y < CU_SIZE / 2; y += 8)
	{
		memcpy(&cbLuma[y * CU_SIZE], &vscbLuma[(y >> 3) * CU_SIZE], CU_SIZE * sizeof(s16));
		memcpy(&cbChroma1[y * CU_SIZE / 2], &vscbChroma1[(y >> 3) * CU_SIZE / 2], CU_SIZE * sizeof(s16) / 2);
		memcpy(&cbChroma2[y * CU_SIZE / 2], &vscbChroma2[(y >> 3) * CU_SIZE / 2], CU_SIZE * sizeof(s16) / 2);
	}
	for (u8 y = CU_SIZE / 2 + 7; y < CU_SIZE; y++)
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
}