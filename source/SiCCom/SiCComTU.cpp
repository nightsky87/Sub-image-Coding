#include "SiCComTU.h"

void vstuForward(cuStruct cu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v1 = (s32)cu.pLuma[y * CU_SIZE + x + 1] + (s32)cu.pLuma[y * CU_SIZE + x + 2];
			v2 = (s32)cu.pLuma[y * CU_SIZE + x + 2] - (s32)cu.pLuma[y * CU_SIZE + x + 1];
			v3 = (s32)cu.pLuma[y * CU_SIZE + x + 3] - (s32)cu.pLuma[y * CU_SIZE + x + 0];
			cu.pLuma[y * CU_SIZE + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pLuma[y * CU_SIZE + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pLuma[y * CU_SIZE + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pLuma[y * CU_SIZE + x + 3] = (83 * v2 - 36 * v3) >> 1;

			// Perform the first chroma transform
			v0 = (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 0] + (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 3];
			v1 = (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 1] + (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 2];
			v2 = (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 2] - (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 1];
			v3 = (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 3] - (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 0];
			cu.pChroma1[y * CU_SIZE / 2 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pChroma1[y * CU_SIZE / 2 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pChroma1[y * CU_SIZE / 2 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pChroma1[y * CU_SIZE / 2 + x + 3] = (83 * v2 - 36 * v3) >> 1;

			// Perform the second chroma transform
			v0 = (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 0] + (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 3];
			v1 = (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 1] + (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 2];
			v2 = (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 2] - (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 1];
			v3 = (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 3] - (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 0];
			cu.pChroma2[y * CU_SIZE / 2 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pChroma2[y * CU_SIZE / 2 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pChroma2[y * CU_SIZE / 2 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pChroma2[y * CU_SIZE / 2 + x + 3] = (83 * v2 - 36 * v3) >> 1;
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v1 = (s32)cu.pLuma[y * CU_SIZE + x + 1] + (s32)cu.pLuma[y * CU_SIZE + x + 2];
			v2 = (s32)cu.pLuma[y * CU_SIZE + x + 2] - (s32)cu.pLuma[y * CU_SIZE + x + 1];
			v3 = (s32)cu.pLuma[y * CU_SIZE + x + 3] - (s32)cu.pLuma[y * CU_SIZE + x + 0];
			cu.pLuma[y * CU_SIZE + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pLuma[y * CU_SIZE + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pLuma[y * CU_SIZE + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pLuma[y * CU_SIZE + x + 3] = (83 * v2 - 36 * v3) >> 1;
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v1 = (s32)cu.pLuma[y * CU_SIZE + x + 1] + (s32)cu.pLuma[y * CU_SIZE + x + 2];
			v2 = (s32)cu.pLuma[y * CU_SIZE + x + 2] - (s32)cu.pLuma[y * CU_SIZE + x + 1];
			v3 = (s32)cu.pLuma[y * CU_SIZE + x + 3] - (s32)cu.pLuma[y * CU_SIZE + x + 0];
			cu.pLuma[y * CU_SIZE + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pLuma[y * CU_SIZE + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pLuma[y * CU_SIZE + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pLuma[y * CU_SIZE + x + 3] = (83 * v2 - 36 * v3) >> 1;
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[(y + 0) * CU_SIZE + x] + (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			v1 = (s32)cu.pLuma[(y + 1) * CU_SIZE + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE + x];
			v2 = (s32)cu.pLuma[(y + 2) * CU_SIZE + x] - (s32)cu.pLuma[(y + 1) * CU_SIZE + x];
			v3 = (s32)cu.pLuma[(y + 3) * CU_SIZE + x] - (s32)cu.pLuma[(y + 0) * CU_SIZE + x];
			cu.pLuma[(y + 0) * CU_SIZE + x] = (64 * (v0 + v1)) >> 8;
			cu.pLuma[(y + 1) * CU_SIZE + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pLuma[(y + 2) * CU_SIZE + x] = (64 * (v0 - v1)) >> 8;
			cu.pLuma[(y + 3) * CU_SIZE + x] = (83 * v2 - 36 * v3) >> 8;

			// Perform the first chroma transform
			v0 = (s32)cu.pChroma1[(y + 0) * CU_SIZE / 2 + x] + (s32)cu.pChroma1[(y + 3) * CU_SIZE / 2 + x];
			v1 = (s32)cu.pChroma1[(y + 1) * CU_SIZE / 2 + x] + (s32)cu.pChroma1[(y + 2) * CU_SIZE / 2 + x];
			v2 = (s32)cu.pChroma1[(y + 2) * CU_SIZE / 2 + x] - (s32)cu.pChroma1[(y + 1) * CU_SIZE / 2 + x];
			v3 = (s32)cu.pChroma1[(y + 3) * CU_SIZE / 2 + x] - (s32)cu.pChroma1[(y + 0) * CU_SIZE / 2 + x];
			cu.pChroma1[(y + 0) * CU_SIZE / 2 + x] = (64 * (v0 + v1)) >> 8;
			cu.pChroma1[(y + 1) * CU_SIZE / 2 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pChroma1[(y + 2) * CU_SIZE / 2 + x] = (64 * (v0 - v1)) >> 8;
			cu.pChroma1[(y + 3) * CU_SIZE / 2 + x] = (83 * v2 - 36 * v3) >> 8;

			// Perform the second chroma transform
			v0 = (s32)cu.pChroma2[(y + 0) * CU_SIZE / 2 + x] + (s32)cu.pChroma2[(y + 3) * CU_SIZE / 2 + x];
			v1 = (s32)cu.pChroma2[(y + 1) * CU_SIZE / 2 + x] + (s32)cu.pChroma2[(y + 2) * CU_SIZE / 2 + x];
			v2 = (s32)cu.pChroma2[(y + 2) * CU_SIZE / 2 + x] - (s32)cu.pChroma2[(y + 1) * CU_SIZE / 2 + x];
			v3 = (s32)cu.pChroma2[(y + 3) * CU_SIZE / 2 + x] - (s32)cu.pChroma2[(y + 0) * CU_SIZE / 2 + x];
			cu.pChroma2[(y + 0) * CU_SIZE / 2 + x] = (64 * (v0 + v1)) >> 8;
			cu.pChroma2[(y + 1) * CU_SIZE / 2 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pChroma2[(y + 2) * CU_SIZE / 2 + x] = (64 * (v0 - v1)) >> 8;
			cu.pChroma2[(y + 3) * CU_SIZE / 2 + x] = (83 * v2 - 36 * v3) >> 8;
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[(y + 0) * CU_SIZE + x] + (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			v1 = (s32)cu.pLuma[(y + 1) * CU_SIZE + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE + x];
			v2 = (s32)cu.pLuma[(y + 2) * CU_SIZE + x] - (s32)cu.pLuma[(y + 1) * CU_SIZE + x];
			v3 = (s32)cu.pLuma[(y + 3) * CU_SIZE + x] - (s32)cu.pLuma[(y + 0) * CU_SIZE + x];
			cu.pLuma[(y + 0) * CU_SIZE + x] = (64 * (v0 + v1)) >> 8;
			cu.pLuma[(y + 1) * CU_SIZE + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pLuma[(y + 2) * CU_SIZE + x] = (64 * (v0 - v1)) >> 8;
			cu.pLuma[(y + 3) * CU_SIZE + x] = (83 * v2 - 36 * v3) >> 8;
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[(y + 0) * CU_SIZE + x] + (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			v1 = (s32)cu.pLuma[(y + 1) * CU_SIZE + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE + x];
			v2 = (s32)cu.pLuma[(y + 2) * CU_SIZE + x] - (s32)cu.pLuma[(y + 1) * CU_SIZE + x];
			v3 = (s32)cu.pLuma[(y + 3) * CU_SIZE + x] - (s32)cu.pLuma[(y + 0) * CU_SIZE + x];
			cu.pLuma[(y + 0) * CU_SIZE + x] = (64 * (v0 + v1)) >> 8;
			cu.pLuma[(y + 1) * CU_SIZE + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pLuma[(y + 2) * CU_SIZE + x] = (64 * (v0 - v1)) >> 8;
			cu.pLuma[(y + 3) * CU_SIZE + x] = (83 * v2 - 36 * v3) >> 8;
		}
	}
}

void vstuInverse(cuStruct cu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 2]);
			v1 = 64 * ((s32)cu.pLuma[y * CU_SIZE + x + 0] - (s32)cu.pLuma[y * CU_SIZE + x + 2]);
			v2 = -36 * (s32)cu.pLuma[y * CU_SIZE + x + 1] + 83 * (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v3 = -83 * (s32)cu.pLuma[y * CU_SIZE + x + 1] - 36 * (s32)cu.pLuma[y * CU_SIZE + x + 3];
			cu.pLuma[y * CU_SIZE + x + 0] = (v0 - v3) >> 7;
			cu.pLuma[y * CU_SIZE + x + 1] = (v1 - v2) >> 7;
			cu.pLuma[y * CU_SIZE + x + 2] = (v1 + v2) >> 7;
			cu.pLuma[y * CU_SIZE + x + 3] = (v0 + v3) >> 7;

			// Perform the first chroma transform
			v0 = 64 * ((s32)cu.pChroma1[y * CU_SIZE / 2 + x + 0] + (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 2]);
			v1 = 64 * ((s32)cu.pChroma1[y * CU_SIZE / 2 + x + 0] - (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 2]);
			v2 = -36 * (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 1] + 83 * (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 3];
			v3 = -83 * (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 1] - 36 * (s32)cu.pChroma1[y * CU_SIZE / 2 + x + 3];
			cu.pChroma1[y * CU_SIZE / 2 + x + 0] = (v0 - v3) >> 7;
			cu.pChroma1[y * CU_SIZE / 2 + x + 1] = (v1 - v2) >> 7;
			cu.pChroma1[y * CU_SIZE / 2 + x + 2] = (v1 + v2) >> 7;
			cu.pChroma1[y * CU_SIZE / 2 + x + 3] = (v0 + v3) >> 7;

			// Perform the second chroma transform
			v0 = 64 * ((s32)cu.pChroma2[y * CU_SIZE / 2 + x + 0] + (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 2]);
			v1 = 64 * ((s32)cu.pChroma2[y * CU_SIZE / 2 + x + 0] - (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 2]);
			v2 = -36 * (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 1] + 83 * (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 3];
			v3 = -83 * (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 1] - 36 * (s32)cu.pChroma2[y * CU_SIZE / 2 + x + 3];
			cu.pChroma2[y * CU_SIZE / 2 + x + 0] = (v0 - v3) >> 7;
			cu.pChroma2[y * CU_SIZE / 2 + x + 1] = (v1 - v2) >> 7;
			cu.pChroma2[y * CU_SIZE / 2 + x + 2] = (v1 + v2) >> 7;
			cu.pChroma2[y * CU_SIZE / 2 + x + 3] = (v0 + v3) >> 7;
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 2]);
			v1 = 64 * ((s32)cu.pLuma[y * CU_SIZE + x + 0] - (s32)cu.pLuma[y * CU_SIZE + x + 2]);
			v2 = -36 * (s32)cu.pLuma[y * CU_SIZE + x + 1] + 83 * (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v3 = -83 * (s32)cu.pLuma[y * CU_SIZE + x + 1] - 36 * (s32)cu.pLuma[y * CU_SIZE + x + 3];
			cu.pLuma[y * CU_SIZE + x + 0] = (v0 - v3) >> 7;
			cu.pLuma[y * CU_SIZE + x + 1] = (v1 - v2) >> 7;
			cu.pLuma[y * CU_SIZE + x + 2] = (v1 + v2) >> 7;
			cu.pLuma[y * CU_SIZE + x + 3] = (v0 + v3) >> 7;
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 2]);
			v1 = 64 * ((s32)cu.pLuma[y * CU_SIZE + x + 0] - (s32)cu.pLuma[y * CU_SIZE + x + 2]);
			v2 = -36 * (s32)cu.pLuma[y * CU_SIZE + x + 1] + 83 * (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v3 = -83 * (s32)cu.pLuma[y * CU_SIZE + x + 1] - 36 * (s32)cu.pLuma[y * CU_SIZE + x + 3];
			cu.pLuma[y * CU_SIZE + x + 0] = (v0 - v3) >> 7;
			cu.pLuma[y * CU_SIZE + x + 1] = (v1 - v2) >> 7;
			cu.pLuma[y * CU_SIZE + x + 2] = (v1 + v2) >> 7;
			cu.pLuma[y * CU_SIZE + x + 3] = (v0 + v3) >> 7;
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE + x]);
			v1 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE + x] - (s32)cu.pLuma[(y + 2) * CU_SIZE + x]);
			v2 = -36 * (s32)cu.pLuma[(y + 1) * CU_SIZE + x] + 83 * (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			v3 = -83 * (s32)cu.pLuma[(y + 1) * CU_SIZE + x] - 36 * (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			cu.pLuma[(y + 0) * CU_SIZE + x] = (v0 - v3) >> 12;
			cu.pLuma[(y + 1) * CU_SIZE + x] = (v1 - v2) >> 12;
			cu.pLuma[(y + 2) * CU_SIZE + x] = (v1 + v2) >> 12;
			cu.pLuma[(y + 3) * CU_SIZE + x] = (v0 + v3) >> 12;

			// Perform the first chroma transform
			v0 = 64 * ((s32)cu.pChroma1[(y + 0) * CU_SIZE / 2 + x] + (s32)cu.pChroma1[(y + 2) * CU_SIZE / 2 + x]);
			v1 = 64 * ((s32)cu.pChroma1[(y + 0) * CU_SIZE / 2 + x] - (s32)cu.pChroma1[(y + 2) * CU_SIZE / 2 + x]);
			v2 = -36 * (s32)cu.pChroma1[(y + 1) * CU_SIZE / 2 + x] + 83 * (s32)cu.pChroma1[(y + 3) * CU_SIZE / 2 + x];
			v3 = -83 * (s32)cu.pChroma1[(y + 1) * CU_SIZE / 2 + x] - 36 * (s32)cu.pChroma1[(y + 3) * CU_SIZE / 2 + x];
			cu.pChroma1[(y + 0) * CU_SIZE / 2 + x] = (v0 - v3) >> 12;
			cu.pChroma1[(y + 1) * CU_SIZE / 2 + x] = (v1 - v2) >> 12;
			cu.pChroma1[(y + 2) * CU_SIZE / 2 + x] = (v1 + v2) >> 12;
			cu.pChroma1[(y + 3) * CU_SIZE / 2 + x] = (v0 + v3) >> 12;

			// Perform the second chroma transform
			v0 = 64 * ((s32)cu.pChroma2[(y + 0) * CU_SIZE / 2 + x] + (s32)cu.pChroma2[(y + 2) * CU_SIZE / 2 + x]);
			v1 = 64 * ((s32)cu.pChroma2[(y + 0) * CU_SIZE / 2 + x] - (s32)cu.pChroma2[(y + 2) * CU_SIZE / 2 + x]);
			v2 = -36 * (s32)cu.pChroma2[(y + 1) * CU_SIZE / 2 + x] + 83 * (s32)cu.pChroma2[(y + 3) * CU_SIZE / 2 + x];
			v3 = -83 * (s32)cu.pChroma2[(y + 1) * CU_SIZE / 2 + x] - 36 * (s32)cu.pChroma2[(y + 3) * CU_SIZE / 2 + x];
			cu.pChroma2[(y + 0) * CU_SIZE / 2 + x] = (v0 - v3) >> 12;
			cu.pChroma2[(y + 1) * CU_SIZE / 2 + x] = (v1 - v2) >> 12;
			cu.pChroma2[(y + 2) * CU_SIZE / 2 + x] = (v1 + v2) >> 12;
			cu.pChroma2[(y + 3) * CU_SIZE / 2 + x] = (v0 + v3) >> 12;
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE + x]);
			v1 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE + x] - (s32)cu.pLuma[(y + 2) * CU_SIZE + x]);
			v2 = -36 * (s32)cu.pLuma[(y + 1) * CU_SIZE + x] + 83 * (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			v3 = -83 * (s32)cu.pLuma[(y + 1) * CU_SIZE + x] - 36 * (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			cu.pLuma[(y + 0) * CU_SIZE + x] = (v0 - v3) >> 12;
			cu.pLuma[(y + 1) * CU_SIZE + x] = (v1 - v2) >> 12;
			cu.pLuma[(y + 2) * CU_SIZE + x] = (v1 + v2) >> 12;
			cu.pLuma[(y + 3) * CU_SIZE + x] = (v0 + v3) >> 12;
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE + x]);
			v1 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE + x] - (s32)cu.pLuma[(y + 2) * CU_SIZE + x]);
			v2 = -36 * (s32)cu.pLuma[(y + 1) * CU_SIZE + x] + 83 * (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			v3 = -83 * (s32)cu.pLuma[(y + 1) * CU_SIZE + x] - 36 * (s32)cu.pLuma[(y + 3) * CU_SIZE + x];
			cu.pLuma[(y + 0) * CU_SIZE + x] = (v0 - v3) >> 12;
			cu.pLuma[(y + 1) * CU_SIZE + x] = (v1 - v2) >> 12;
			cu.pLuma[(y + 2) * CU_SIZE + x] = (v1 + v2) >> 12;
			cu.pLuma[(y + 3) * CU_SIZE + x] = (v0 + v3) >> 12;
		}
	}
}

void hstuForward(cuStruct cu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			v1 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2];
			v2 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1];
			v3 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 0];
			cu.pLuma[y * CU_SIZE / 8 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 3] = (83 * v2 - 36 * v3) >> 1;

			// Perform the first chroma transform
			v0 = (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 0] + (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 3];
			v1 = (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 1] + (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 2];
			v2 = (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 2] - (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 1];
			v3 = (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 3] - (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 0];
			cu.pChroma1[y * CU_SIZE / 16 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pChroma1[y * CU_SIZE / 16 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pChroma1[y * CU_SIZE / 16 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pChroma1[y * CU_SIZE / 16 + x + 3] = (83 * v2 - 36 * v3) >> 1;

			// Perform the second chroma transform
			v0 = (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 0] + (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 3];
			v1 = (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 1] + (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 2];
			v2 = (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 2] - (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 1];
			v3 = (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 3] - (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 0];
			cu.pChroma2[y * CU_SIZE / 16 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pChroma2[y * CU_SIZE / 16 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pChroma2[y * CU_SIZE / 16 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pChroma2[y * CU_SIZE / 16 + x + 3] = (83 * v2 - 36 * v3) >> 1;
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[y * CU_SIZE + x + 0] + (s32)cu.pLuma[y * CU_SIZE + x + 3];
			v1 = (s32)cu.pLuma[y * CU_SIZE + x + 1] + (s32)cu.pLuma[y * CU_SIZE + x + 2];
			v2 = (s32)cu.pLuma[y * CU_SIZE + x + 2] - (s32)cu.pLuma[y * CU_SIZE + x + 1];
			v3 = (s32)cu.pLuma[y * CU_SIZE + x + 3] - (s32)cu.pLuma[y * CU_SIZE + x + 0];
			cu.pLuma[y * CU_SIZE / 8 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 3] = (83 * v2 - 36 * v3) >> 1;
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			v1 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2];
			v2 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1];
			v3 = (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 0];
			cu.pLuma[y * CU_SIZE / 8 + x + 0] = (64 * (v0 + v1)) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 1] = (-36 * v2 - 83 * v3) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 2] = (64 * (v0 - v1)) >> 1;
			cu.pLuma[y * CU_SIZE / 8 + x + 3] = (83 * v2 - 36 * v3) >> 1;
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x++)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			v1 = (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x];
			v2 = (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x];
			v3 = (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x];
			cu.pLuma[(y + 0) * CU_SIZE / 8 + x] = (64 * (v0 + v1)) >> 8;
			cu.pLuma[(y + 1) * CU_SIZE / 8 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pLuma[(y + 2) * CU_SIZE / 8 + x] = (64 * (v0 - v1)) >> 8;
			cu.pLuma[(y + 3) * CU_SIZE / 8 + x] = (83 * v2 - 36 * v3) >> 8;

			// Perform the first chroma transform
			v0 = (s32)cu.pChroma1[(y + 0) * CU_SIZE / 16 + x] + (s32)cu.pChroma1[(y + 3) * CU_SIZE / 16 + x];
			v1 = (s32)cu.pChroma1[(y + 1) * CU_SIZE / 16 + x] + (s32)cu.pChroma1[(y + 2) * CU_SIZE / 16 + x];
			v2 = (s32)cu.pChroma1[(y + 2) * CU_SIZE / 16 + x] - (s32)cu.pChroma1[(y + 1) * CU_SIZE / 16 + x];
			v3 = (s32)cu.pChroma1[(y + 3) * CU_SIZE / 16 + x] - (s32)cu.pChroma1[(y + 0) * CU_SIZE / 16 + x];
			cu.pChroma1[(y + 0) * CU_SIZE / 16 + x] = (64 * (v0 + v1)) >> 8;
			cu.pChroma1[(y + 1) * CU_SIZE / 16 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pChroma1[(y + 2) * CU_SIZE / 16 + x] = (64 * (v0 - v1)) >> 8;
			cu.pChroma1[(y + 3) * CU_SIZE / 16 + x] = (83 * v2 - 36 * v3) >> 8;

			// Perform the second chroma transform
			v0 = (s32)cu.pChroma2[(y + 0) * CU_SIZE / 16 + x] + (s32)cu.pChroma2[(y + 3) * CU_SIZE / 16 + x];
			v1 = (s32)cu.pChroma2[(y + 1) * CU_SIZE / 16 + x] + (s32)cu.pChroma2[(y + 2) * CU_SIZE / 16 + x];
			v2 = (s32)cu.pChroma2[(y + 2) * CU_SIZE / 16 + x] - (s32)cu.pChroma2[(y + 1) * CU_SIZE / 16 + x];
			v3 = (s32)cu.pChroma2[(y + 3) * CU_SIZE / 16 + x] - (s32)cu.pChroma2[(y + 0) * CU_SIZE / 16 + x];
			cu.pChroma2[(y + 0) * CU_SIZE / 16 + x] = (64 * (v0 + v1)) >> 8;
			cu.pChroma2[(y + 1) * CU_SIZE / 16 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pChroma2[(y + 2) * CU_SIZE / 16 + x] = (64 * (v0 - v1)) >> 8;
			cu.pChroma2[(y + 3) * CU_SIZE / 16 + x] = (83 * v2 - 36 * v3) >> 8;
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			v1 = (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x];
			v2 = (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x];
			v3 = (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x];
			cu.pLuma[(y + 0) * CU_SIZE / 8 + x] = (64 * (v0 + v1)) >> 8;
			cu.pLuma[(y + 1) * CU_SIZE / 8 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pLuma[(y + 2) * CU_SIZE / 8 + x] = (64 * (v0 - v1)) >> 8;
			cu.pLuma[(y + 3) * CU_SIZE / 8 + x] = (83 * v2 - 36 * v3) >> 8;
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = (s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			v1 = (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x];
			v2 = (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x];
			v3 = (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x];
			cu.pLuma[(y + 0) * CU_SIZE / 8 + x] = (64 * (v0 + v1)) >> 8;
			cu.pLuma[(y + 1) * CU_SIZE / 8 + x] = (-36 * v2 - 83 * v3) >> 8;
			cu.pLuma[(y + 2) * CU_SIZE / 8 + x] = (64 * (v0 - v1)) >> 8;
			cu.pLuma[(y + 3) * CU_SIZE / 8 + x] = (83 * v2 - 36 * v3) >> 8;
		}
	}
}

void hstuInverse(cuStruct cu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2]);
			v1 = 64 * ((s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2]);
			v2 = -36 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] + 83 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			v3 = -83 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] - 36 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			cu.pLuma[y * CU_SIZE / 8 + x + 0] = (v0 - v3) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 1] = (v1 - v2) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 2] = (v1 + v2) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 3] = (v0 + v3) >> 7;

			// Perform the first chroma transform
			v0 = 64 * ((s32)cu.pChroma1[y * CU_SIZE / 16 + x + 0] + (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 2]);
			v1 = 64 * ((s32)cu.pChroma1[y * CU_SIZE / 16 + x + 0] - (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 2]);
			v2 = -36 * (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 1] + 83 * (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 3];
			v3 = -83 * (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 1] - 36 * (s32)cu.pChroma1[y * CU_SIZE / 16 + x + 3];
			cu.pChroma1[y * CU_SIZE / 16 + x + 0] = (v0 - v3) >> 7;
			cu.pChroma1[y * CU_SIZE / 16 + x + 1] = (v1 - v2) >> 7;
			cu.pChroma1[y * CU_SIZE / 16 + x + 2] = (v1 + v2) >> 7;
			cu.pChroma1[y * CU_SIZE / 16 + x + 3] = (v0 + v3) >> 7;

			// Perform the second chroma transform
			v0 = 64 * ((s32)cu.pChroma2[y * CU_SIZE / 16 + x + 0] + (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 2]);
			v1 = 64 * ((s32)cu.pChroma2[y * CU_SIZE / 16 + x + 0] - (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 2]);
			v2 = -36 * (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 1] + 83 * (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 3];
			v3 = -83 * (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 1] - 36 * (s32)cu.pChroma2[y * CU_SIZE / 16 + x + 3];
			cu.pChroma2[y * CU_SIZE / 16 + x + 0] = (v0 - v3) >> 7;
			cu.pChroma2[y * CU_SIZE / 16 + x + 1] = (v1 - v2) >> 7;
			cu.pChroma2[y * CU_SIZE / 16 + x + 2] = (v1 + v2) >> 7;
			cu.pChroma2[y * CU_SIZE / 16 + x + 3] = (v0 + v3) >> 7;
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2]);
			v1 = 64 * ((s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2]);
			v2 = -36 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] + 83 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			v3 = -83 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] - 36 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			cu.pLuma[y * CU_SIZE / 8 + x + 0] = (v0 - v3) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 1] = (v1 - v2) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 2] = (v1 + v2) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 3] = (v0 + v3) >> 7;
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] + (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2]);
			v1 = 64 * ((s32)cu.pLuma[y * CU_SIZE / 8 + x + 0] - (s32)cu.pLuma[y * CU_SIZE / 8 + x + 2]);
			v2 = -36 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] + 83 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			v3 = -83 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 1] - 36 * (s32)cu.pLuma[y * CU_SIZE / 8 + x + 3];
			cu.pLuma[y * CU_SIZE / 8 + x + 0] = (v0 - v3) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 1] = (v1 - v2) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 2] = (v1 + v2) >> 7;
			cu.pLuma[y * CU_SIZE / 8 + x + 3] = (v0 + v3) >> 7;
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x]);
			v1 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x]);
			v2 = -36 * (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] + 83 * (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			v3 = -83 * (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] - 36 * (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			cu.pLuma[(y + 0) * CU_SIZE / 8 + x] = (v0 - v3) >> 12;
			cu.pLuma[(y + 1) * CU_SIZE / 8 + x] = (v1 - v2) >> 12;
			cu.pLuma[(y + 2) * CU_SIZE / 8 + x] = (v1 + v2) >> 12;
			cu.pLuma[(y + 3) * CU_SIZE / 8 + x] = (v0 + v3) >> 12;

			// Perform the first chroma transform
			v0 = 64 * ((s32)cu.pChroma1[(y + 0) * CU_SIZE / 16 + x] + (s32)cu.pChroma1[(y + 2) * CU_SIZE / 16 + x]);
			v1 = 64 * ((s32)cu.pChroma1[(y + 0) * CU_SIZE / 16 + x] - (s32)cu.pChroma1[(y + 2) * CU_SIZE / 16 + x]);
			v2 = -36 * (s32)cu.pChroma1[(y + 1) * CU_SIZE / 16 + x] + 83 * (s32)cu.pChroma1[(y + 3) * CU_SIZE / 16 + x];
			v3 = -83 * (s32)cu.pChroma1[(y + 1) * CU_SIZE / 16 + x] - 36 * (s32)cu.pChroma1[(y + 3) * CU_SIZE / 16 + x];
			cu.pChroma1[(y + 0) * CU_SIZE / 16 + x] = (v0 - v3) >> 12;
			cu.pChroma1[(y + 1) * CU_SIZE / 16 + x] = (v1 - v2) >> 12;
			cu.pChroma1[(y + 2) * CU_SIZE / 16 + x] = (v1 + v2) >> 12;
			cu.pChroma1[(y + 3) * CU_SIZE / 16 + x] = (v0 + v3) >> 12;

			// Perform the second chroma transform
			v0 = 64 * ((s32)cu.pChroma2[(y + 0) * CU_SIZE / 16 + x] + (s32)cu.pChroma2[(y + 2) * CU_SIZE / 16 + x]);
			v1 = 64 * ((s32)cu.pChroma2[(y + 0) * CU_SIZE / 16 + x] - (s32)cu.pChroma2[(y + 2) * CU_SIZE / 16 + x]);
			v2 = -36 * (s32)cu.pChroma2[(y + 1) * CU_SIZE / 16 + x] + 83 * (s32)cu.pChroma2[(y + 3) * CU_SIZE / 16 + x];
			v3 = -83 * (s32)cu.pChroma2[(y + 1) * CU_SIZE / 16 + x] - 36 * (s32)cu.pChroma2[(y + 3) * CU_SIZE / 16 + x];
			cu.pChroma2[(y + 0) * CU_SIZE / 16 + x] = (v0 - v3) >> 12;
			cu.pChroma2[(y + 1) * CU_SIZE / 16 + x] = (v1 - v2) >> 12;
			cu.pChroma2[(y + 2) * CU_SIZE / 16 + x] = (v1 + v2) >> 12;
			cu.pChroma2[(y + 3) * CU_SIZE / 16 + x] = (v0 + v3) >> 12;
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x]);
			v1 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x]);
			v2 = -36 * (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] + 83 * (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			v3 = -83 * (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] - 36 * (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			cu.pLuma[(y + 0) * CU_SIZE / 8 + x] = (v0 - v3) >> 12;
			cu.pLuma[(y + 1) * CU_SIZE / 8 + x] = (v1 - v2) >> 12;
			cu.pLuma[(y + 2) * CU_SIZE / 8 + x] = (v1 + v2) >> 12;
			cu.pLuma[(y + 3) * CU_SIZE / 8 + x] = (v0 + v3) >> 12;
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x]);
			v1 = 64 * ((s32)cu.pLuma[(y + 0) * CU_SIZE / 8 + x] - (s32)cu.pLuma[(y + 2) * CU_SIZE / 8 + x]);
			v2 = -36 * (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] + 83 * (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			v3 = -83 * (s32)cu.pLuma[(y + 1) * CU_SIZE / 8 + x] - 36 * (s32)cu.pLuma[(y + 3) * CU_SIZE / 8 + x];
			cu.pLuma[(y + 0) * CU_SIZE / 8 + x] = (v0 - v3) >> 12;
			cu.pLuma[(y + 1) * CU_SIZE / 8 + x] = (v1 - v2) >> 12;
			cu.pLuma[(y + 2) * CU_SIZE / 8 + x] = (v1 + v2) >> 12;
			cu.pLuma[(y + 3) * CU_SIZE / 8 + x] = (v0 + v3) >> 12;
		}
	}
}

void rtuForward(cuStruct cu)
{

}

void rtuInverse(cuStruct cu)
{

}