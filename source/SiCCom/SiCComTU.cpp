#include "SiCComTU.h"

void stuForward(stuStruct stu)
{
	vstuForward(stu.vscu);
	hstuForward(stu.hscu);
}

void stuInverse(stuStruct stu)
{
	vstuInverse(stu.vscu);
	hstuInverse(stu.hscu);
}

void vstuForward(scuStruct *scu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[y * CU_SIZE + x + 0] + (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			v1 = (s32)scu->scbLuma[y * CU_SIZE + x + 1] + (s32)scu->scbLuma[y * CU_SIZE + x + 2];
			v2 = (s32)scu->scbLuma[y * CU_SIZE + x + 2] - (s32)scu->scbLuma[y * CU_SIZE + x + 1];
			v3 = (s32)scu->scbLuma[y * CU_SIZE + x + 3] - (s32)scu->scbLuma[y * CU_SIZE + x + 0];
			scu->scbLuma[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);

			// Perform the first chroma transform
			v0 = (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 0] + (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 3];
			v1 = (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 1] + (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 2];
			v2 = (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 2] - (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 1];
			v3 = (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 3] - (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 0];
			scu->scbChroma1[y * CU_SIZE / 2 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbChroma1[y * CU_SIZE / 2 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbChroma1[y * CU_SIZE / 2 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbChroma1[y * CU_SIZE / 2 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);

			// Perform the second chroma transform
			v0 = (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 0] + (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 3];
			v1 = (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 1] + (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 2];
			v2 = (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 2] - (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 1];
			v3 = (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 3] - (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 0];
			scu->scbChroma2[y * CU_SIZE / 2 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbChroma2[y * CU_SIZE / 2 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbChroma2[y * CU_SIZE / 2 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbChroma2[y * CU_SIZE / 2 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[y * CU_SIZE + x + 0] + (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			v1 = (s32)scu->scbLuma[y * CU_SIZE + x + 1] + (s32)scu->scbLuma[y * CU_SIZE + x + 2];
			v2 = (s32)scu->scbLuma[y * CU_SIZE + x + 2] - (s32)scu->scbLuma[y * CU_SIZE + x + 1];
			v3 = (s32)scu->scbLuma[y * CU_SIZE + x + 3] - (s32)scu->scbLuma[y * CU_SIZE + x + 0];
			scu->scbLuma[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[y * CU_SIZE + x + 0] + (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			v1 = (s32)scu->scbLuma[y * CU_SIZE + x + 1] + (s32)scu->scbLuma[y * CU_SIZE + x + 2];
			v2 = (s32)scu->scbLuma[y * CU_SIZE + x + 2] - (s32)scu->scbLuma[y * CU_SIZE + x + 1];
			v3 = (s32)scu->scbLuma[y * CU_SIZE + x + 3] - (s32)scu->scbLuma[y * CU_SIZE + x + 0];
			scu->scbLuma[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbLuma[y * CU_SIZE + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[(y + 0) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			v1 = (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE + x];
			v2 = (s32)scu->scbLuma[(y + 2) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 1) * CU_SIZE + x];
			v3 = (s32)scu->scbLuma[(y + 3) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 0) * CU_SIZE + x];
			scu->scbLuma[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbLuma[(y + 2) * CU_SIZE + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbLuma[(y + 3) * CU_SIZE + x] = coeffCast((83 * v2 - 36 * v3) >> 8);

			// Perform the first chroma transform
			v0 = (s32)scu->scbChroma1[(y + 0) * CU_SIZE / 2 + x] + (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 2 + x];
			v1 = (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 2 + x] + (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 2 + x];
			v2 = (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 2 + x] - (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 2 + x];
			v3 = (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 2 + x] - (s32)scu->scbChroma1[(y + 0) * CU_SIZE / 2 + x];
			scu->scbChroma1[(y + 0) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbChroma1[(y + 1) * CU_SIZE / 2 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbChroma1[(y + 2) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbChroma1[(y + 3) * CU_SIZE / 2 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);

			// Perform the second chroma transform
			v0 = (s32)scu->scbChroma2[(y + 0) * CU_SIZE / 2 + x] + (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 2 + x];
			v1 = (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 2 + x] + (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 2 + x];
			v2 = (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 2 + x] - (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 2 + x];
			v3 = (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 2 + x] - (s32)scu->scbChroma2[(y + 0) * CU_SIZE / 2 + x];
			scu->scbChroma2[(y + 0) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbChroma2[(y + 1) * CU_SIZE / 2 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbChroma2[(y + 2) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbChroma2[(y + 3) * CU_SIZE / 2 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[(y + 0) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			v1 = (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE + x];
			v2 = (s32)scu->scbLuma[(y + 2) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 1) * CU_SIZE + x];
			v3 = (s32)scu->scbLuma[(y + 3) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 0) * CU_SIZE + x];
			scu->scbLuma[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbLuma[(y + 2) * CU_SIZE + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbLuma[(y + 3) * CU_SIZE + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[(y + 0) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			v1 = (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE + x];
			v2 = (s32)scu->scbLuma[(y + 2) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 1) * CU_SIZE + x];
			v3 = (s32)scu->scbLuma[(y + 3) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 0) * CU_SIZE + x];
			scu->scbLuma[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbLuma[(y + 2) * CU_SIZE + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbLuma[(y + 3) * CU_SIZE + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
		}
	}
}

void vstuInverse(scuStruct *scu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[y * CU_SIZE + x + 0] + (s32)scu->scbLuma[y * CU_SIZE + x + 2]);
			v1 = 64 * ((s32)scu->scbLuma[y * CU_SIZE + x + 0] - (s32)scu->scbLuma[y * CU_SIZE + x + 2]);
			v2 = -36 * (s32)scu->scbLuma[y * CU_SIZE + x + 1] + 83 * (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			v3 = -83 * (s32)scu->scbLuma[y * CU_SIZE + x + 1] - 36 * (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			scu->scbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 3] = coeffCast((v0 + v3) >> 7);

			// Perform the first chroma transform
			v0 = 64 * ((s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 0] + (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 2]);
			v1 = 64 * ((s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 0] - (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 2]);
			v2 = -36 * (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 1] + 83 * (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 3];
			v3 = -83 * (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 1] - 36 * (s32)scu->scbChroma1[y * CU_SIZE / 2 + x + 3];
			scu->scbChroma1[y * CU_SIZE / 2 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbChroma1[y * CU_SIZE / 2 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbChroma1[y * CU_SIZE / 2 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbChroma1[y * CU_SIZE / 2 + x + 3] = coeffCast((v0 + v3) >> 7);

			// Perform the second chroma transform
			v0 = 64 * ((s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 0] + (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 2]);
			v1 = 64 * ((s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 0] - (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 2]);
			v2 = -36 * (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 1] + 83 * (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 3];
			v3 = -83 * (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 1] - 36 * (s32)scu->scbChroma2[y * CU_SIZE / 2 + x + 3];
			scu->scbChroma2[y * CU_SIZE / 2 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbChroma2[y * CU_SIZE / 2 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbChroma2[y * CU_SIZE / 2 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbChroma2[y * CU_SIZE / 2 + x + 3] = coeffCast((v0 + v3) >> 7);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[y * CU_SIZE + x + 0] + (s32)scu->scbLuma[y * CU_SIZE + x + 2]);
			v1 = 64 * ((s32)scu->scbLuma[y * CU_SIZE + x + 0] - (s32)scu->scbLuma[y * CU_SIZE + x + 2]);
			v2 = -36 * (s32)scu->scbLuma[y * CU_SIZE + x + 1] + 83 * (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			v3 = -83 * (s32)scu->scbLuma[y * CU_SIZE + x + 1] - 36 * (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			scu->scbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 3] = coeffCast((v0 + v3) >> 7);
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[y * CU_SIZE + x + 0] + (s32)scu->scbLuma[y * CU_SIZE + x + 2]);
			v1 = 64 * ((s32)scu->scbLuma[y * CU_SIZE + x + 0] - (s32)scu->scbLuma[y * CU_SIZE + x + 2]);
			v2 = -36 * (s32)scu->scbLuma[y * CU_SIZE + x + 1] + 83 * (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			v3 = -83 * (s32)scu->scbLuma[y * CU_SIZE + x + 1] - 36 * (s32)scu->scbLuma[y * CU_SIZE + x + 3];
			scu->scbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbLuma[y * CU_SIZE + x + 3] = coeffCast((v0 + v3) >> 7);
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 16; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE + x]);
			v1 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 2) * CU_SIZE + x]);
			v2 = -36 * (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] + 83 * (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			v3 = -83 * (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] - 36 * (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			scu->scbLuma[(y + 0) * CU_SIZE + x] = pixelCast((v0 - v3) >> 12);
			scu->scbLuma[(y + 1) * CU_SIZE + x] = pixelCast((v1 - v2) >> 12);
			scu->scbLuma[(y + 2) * CU_SIZE + x] = pixelCast((v1 + v2) >> 12);
			scu->scbLuma[(y + 3) * CU_SIZE + x] = pixelCast((v0 + v3) >> 12);

			// Perform the first chroma transform
			v0 = 64 * ((s32)scu->scbChroma1[(y + 0) * CU_SIZE / 2 + x] + (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 2 + x]);
			v1 = 64 * ((s32)scu->scbChroma1[(y + 0) * CU_SIZE / 2 + x] - (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 2 + x]);
			v2 = -36 * (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 2 + x] + 83 * (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 2 + x];
			v3 = -83 * (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 2 + x] - 36 * (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 2 + x];
			scu->scbChroma1[(y + 0) * CU_SIZE / 2 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbChroma1[(y + 1) * CU_SIZE / 2 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbChroma1[(y + 2) * CU_SIZE / 2 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbChroma1[(y + 3) * CU_SIZE / 2 + x] = pixelCast((v0 + v3) >> 12);

			// Perform the second chroma transform
			v0 = 64 * ((s32)scu->scbChroma2[(y + 0) * CU_SIZE / 2 + x] + (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 2 + x]);
			v1 = 64 * ((s32)scu->scbChroma2[(y + 0) * CU_SIZE / 2 + x] - (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 2 + x]);
			v2 = -36 * (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 2 + x] + 83 * (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 2 + x];
			v3 = -83 * (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 2 + x] - 36 * (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 2 + x];
			scu->scbChroma2[(y + 0) * CU_SIZE / 2 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbChroma2[(y + 1) * CU_SIZE / 2 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbChroma2[(y + 2) * CU_SIZE / 2 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbChroma2[(y + 3) * CU_SIZE / 2 + x] = pixelCast((v0 + v3) >> 12);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE + x]);
			v1 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 2) * CU_SIZE + x]);
			v2 = -36 * (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] + 83 * (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			v3 = -83 * (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] - 36 * (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			scu->scbLuma[(y + 0) * CU_SIZE + x] = pixelCast((v0 - v3) >> 12);
			scu->scbLuma[(y + 1) * CU_SIZE + x] = pixelCast((v1 - v2) >> 12);
			scu->scbLuma[(y + 2) * CU_SIZE + x] = pixelCast((v1 + v2) >> 12);
			scu->scbLuma[(y + 3) * CU_SIZE + x] = pixelCast((v0 + v3) >> 12);
		}
	}
	for (u8 y = CU_SIZE / 16; y < CU_SIZE / 8; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE + x]);
			v1 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE + x] - (s32)scu->scbLuma[(y + 2) * CU_SIZE + x]);
			v2 = -36 * (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] + 83 * (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			v3 = -83 * (s32)scu->scbLuma[(y + 1) * CU_SIZE + x] - 36 * (s32)scu->scbLuma[(y + 3) * CU_SIZE + x];
			scu->scbLuma[(y + 0) * CU_SIZE + x] = pixelCast((v0 - v3) >> 12);
			scu->scbLuma[(y + 1) * CU_SIZE + x] = pixelCast((v1 - v2) >> 12);
			scu->scbLuma[(y + 2) * CU_SIZE + x] = pixelCast((v1 + v2) >> 12);
			scu->scbLuma[(y + 3) * CU_SIZE + x] = pixelCast((v0 + v3) >> 12);
		}
	}
}

void hstuForward(scuStruct *scu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			v1 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2];
			v2 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1];
			v3 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0];
			scu->scbLuma[y * CU_SIZE / 8 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);

			// Perform the first chroma transform
			v0 = (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 0] + (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 3];
			v1 = (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 1] + (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 2];
			v2 = (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 2] - (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 1];
			v3 = (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 3] - (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 0];
			scu->scbChroma1[y * CU_SIZE / 16 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbChroma1[y * CU_SIZE / 16 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbChroma1[y * CU_SIZE / 16 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbChroma1[y * CU_SIZE / 16 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);

			// Perform the second chroma transform
			v0 = (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 0] + (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 3];
			v1 = (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 1] + (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 2];
			v2 = (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 2] - (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 1];
			v3 = (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 3] - (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 0];
			scu->scbChroma2[y * CU_SIZE / 16 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbChroma2[y * CU_SIZE / 16 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbChroma2[y * CU_SIZE / 16 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbChroma2[y * CU_SIZE / 16 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			v1 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2];
			v2 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1];
			v3 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0];
			scu->scbLuma[y * CU_SIZE / 8 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			v1 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2];
			v2 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1];
			v3 = (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0];
			scu->scbLuma[y * CU_SIZE / 8 + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			scu->scbLuma[y * CU_SIZE / 8 + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x++)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			v1 = (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x];
			v2 = (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x];
			v3 = (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x];
			scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);

			// Perform the first chroma transform
			v0 = (s32)scu->scbChroma1[(y + 0) * CU_SIZE / 16 + x] + (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 16 + x];
			v1 = (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 16 + x] + (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 16 + x];
			v2 = (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 16 + x] - (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 16 + x];
			v3 = (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 16 + x] - (s32)scu->scbChroma1[(y + 0) * CU_SIZE / 16 + x];
			scu->scbChroma1[(y + 0) * CU_SIZE / 16 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbChroma1[(y + 1) * CU_SIZE / 16 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbChroma1[(y + 2) * CU_SIZE / 16 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbChroma1[(y + 3) * CU_SIZE / 16 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);

			// Perform the second chroma transform
			v0 = (s32)scu->scbChroma2[(y + 0) * CU_SIZE / 16 + x] + (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 16 + x];
			v1 = (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 16 + x] + (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 16 + x];
			v2 = (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 16 + x] - (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 16 + x];
			v3 = (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 16 + x] - (s32)scu->scbChroma2[(y + 0) * CU_SIZE / 16 + x];
			scu->scbChroma2[(y + 0) * CU_SIZE / 16 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbChroma2[(y + 1) * CU_SIZE / 16 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbChroma2[(y + 2) * CU_SIZE / 16 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbChroma2[(y + 3) * CU_SIZE / 16 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			v1 = (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x];
			v2 = (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x];
			v3 = (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x];
			scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = (s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			v1 = (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x];
			v2 = (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x];
			v3 = (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x];
			scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] = coeffCast((64 * (v0 + v1)) >> 8);
			scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
			scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] = coeffCast((64 * (v0 - v1)) >> 8);
			scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
		}
	}
}

void hstuInverse(scuStruct *scu)
{
	static s32 v0, v1, v2, v3;

	// Perform the horizontal pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2]);
			v1 = 64 * ((s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2]);
			v2 = -36 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] + 83 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			v3 = -83 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] - 36 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			scu->scbLuma[y * CU_SIZE / 8 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 3] = coeffCast((v0 + v3) >> 7);

			// Perform the first chroma transform
			v0 = 64 * ((s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 0] + (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 2]);
			v1 = 64 * ((s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 0] - (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 2]);
			v2 = -36 * (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 1] + 83 * (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 3];
			v3 = -83 * (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 1] - 36 * (s32)scu->scbChroma1[y * CU_SIZE / 16 + x + 3];
			scu->scbChroma1[y * CU_SIZE / 16 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbChroma1[y * CU_SIZE / 16 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbChroma1[y * CU_SIZE / 16 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbChroma1[y * CU_SIZE / 16 + x + 3] = coeffCast((v0 + v3) >> 7);

			// Perform the second chroma transform
			v0 = 64 * ((s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 0] + (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 2]);
			v1 = 64 * ((s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 0] - (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 2]);
			v2 = -36 * (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 1] + 83 * (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 3];
			v3 = -83 * (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 1] - 36 * (s32)scu->scbChroma2[y * CU_SIZE / 16 + x + 3];
			scu->scbChroma2[y * CU_SIZE / 16 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbChroma2[y * CU_SIZE / 16 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbChroma2[y * CU_SIZE / 16 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbChroma2[y * CU_SIZE / 16 + x + 3] = coeffCast((v0 + v3) >> 7);
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2]);
			v1 = 64 * ((s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2]);
			v2 = -36 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] + 83 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			v3 = -83 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] - 36 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			scu->scbLuma[y * CU_SIZE / 8 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 3] = coeffCast((v0 + v3) >> 7);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x += 4)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] + (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2]);
			v1 = 64 * ((s32)scu->scbLuma[y * CU_SIZE / 8 + x + 0] - (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 2]);
			v2 = -36 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] + 83 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			v3 = -83 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 1] - 36 * (s32)scu->scbLuma[y * CU_SIZE / 8 + x + 3];
			scu->scbLuma[y * CU_SIZE / 8 + x + 0] = coeffCast((v0 - v3) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 1] = coeffCast((v1 - v2) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 2] = coeffCast((v1 + v2) >> 7);
			scu->scbLuma[y * CU_SIZE / 8 + x + 3] = coeffCast((v0 + v3) >> 7);
		}
	}

	// Perform the vertical pass of the 4-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 16; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x]);
			v1 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x]);
			v2 = -36 * (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] + 83 * (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			v3 = -83 * (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] - 36 * (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] = pixelCast((v0 + v3) >> 12);

			// Perform the first chroma transform
			v0 = 64 * ((s32)scu->scbChroma1[(y + 0) * CU_SIZE / 16 + x] + (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 16 + x]);
			v1 = 64 * ((s32)scu->scbChroma1[(y + 0) * CU_SIZE / 16 + x] - (s32)scu->scbChroma1[(y + 2) * CU_SIZE / 16 + x]);
			v2 = -36 * (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 16 + x] + 83 * (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 16 + x];
			v3 = -83 * (s32)scu->scbChroma1[(y + 1) * CU_SIZE / 16 + x] - 36 * (s32)scu->scbChroma1[(y + 3) * CU_SIZE / 16 + x];
			scu->scbChroma1[(y + 0) * CU_SIZE / 16 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbChroma1[(y + 1) * CU_SIZE / 16 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbChroma1[(y + 2) * CU_SIZE / 16 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbChroma1[(y + 3) * CU_SIZE / 16 + x] = pixelCast((v0 + v3) >> 12);

			// Perform the second chroma transform
			v0 = 64 * ((s32)scu->scbChroma2[(y + 0) * CU_SIZE / 16 + x] + (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 16 + x]);
			v1 = 64 * ((s32)scu->scbChroma2[(y + 0) * CU_SIZE / 16 + x] - (s32)scu->scbChroma2[(y + 2) * CU_SIZE / 16 + x]);
			v2 = -36 * (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 16 + x] + 83 * (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 16 + x];
			v3 = -83 * (s32)scu->scbChroma2[(y + 1) * CU_SIZE / 16 + x] - 36 * (s32)scu->scbChroma2[(y + 3) * CU_SIZE / 16 + x];
			scu->scbChroma2[(y + 0) * CU_SIZE / 16 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbChroma2[(y + 1) * CU_SIZE / 16 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbChroma2[(y + 2) * CU_SIZE / 16 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbChroma2[(y + 3) * CU_SIZE / 16 + x] = pixelCast((v0 + v3) >> 12);
		}
		for (u8 x = CU_SIZE / 16; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x]);
			v1 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x]);
			v2 = -36 * (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] + 83 * (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			v3 = -83 * (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] - 36 * (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] = pixelCast((v0 + v3) >> 12);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 4)
	{
		for (u8 x = 0; x < CU_SIZE / 8; x++)
		{
			// Perform the luma transform
			v0 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] + (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x]);
			v1 = 64 * ((s32)scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] - (s32)scu->scbLuma[(y + 2) * CU_SIZE / 8 + x]);
			v2 = -36 * (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] + 83 * (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			v3 = -83 * (s32)scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] - 36 * (s32)scu->scbLuma[(y + 3) * CU_SIZE / 8 + x];
			scu->scbLuma[(y + 0) * CU_SIZE / 8 + x] = pixelCast((v0 - v3) >> 12);
			scu->scbLuma[(y + 1) * CU_SIZE / 8 + x] = pixelCast((v1 - v2) >> 12);
			scu->scbLuma[(y + 2) * CU_SIZE / 8 + x] = pixelCast((v1 + v2) >> 12);
			scu->scbLuma[(y + 3) * CU_SIZE / 8 + x] = pixelCast((v0 + v3) >> 12);
		}
	}
}

#ifndef USE_8x8_RTB
void rtuForward(rtuStruct rtu)
{
	static s32 v0, v1, v2, v3, v4, v5, v6;

	// Perform the horizontal pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		if (y % 8 == 7)
			continue;

		for (u8 x = 0; x < CU_SIZE / 2; x += 8)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v2 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 4];
			v3 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 3];
			v4 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 2];
			v5 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 1];
			v6 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 6] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 0];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 3);

			// Perform the first chroma transform
			v0 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v1 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5];
			v2 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4];
			v3 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3];
			v4 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2];
			v5 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1];
			v6 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0];
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 3);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 3);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 3);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 3);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 3);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 3);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 3);

			// Perform the second chroma transform
			v0 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v1 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5];
			v2 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4];
			v3 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3];
			v4 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2];
			v5 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1];
			v6 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0];
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 3);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 3);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 3);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 3);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 3);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 3);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 3);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v2 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 4];
			v3 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 3];
			v4 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 2];
			v5 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 1];
			v6 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 6] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 0];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 3);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		if (y % 8 == 7)
			continue;

		for (u8 x = 0; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v2 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 4];
			v3 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 3];
			v4 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 2];
			v5 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 1];
			v6 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 6] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 0];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 3);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 3);
		}
	}

	// Perform the vertical pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			if (x % 8 == 7)
				continue;

			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v2 = (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x];
			v3 = (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x];
			v4 = (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x];
			v5 = (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x];
			v6 = (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 10);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 10);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 10);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 10);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 10);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 10);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 10);

			// Perform the first chroma transform
			v0 = (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v1 = (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x];
			v2 = (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x];
			v3 = (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x];
			v4 = (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x];
			v5 = (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x];
			v6 = (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x];
			rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 10);
			rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 10);
			rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 10);
			rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 10);
			rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 10);
			rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 10);
			rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 10);

			// Perform the second chroma transform
			v0 = (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v1 = (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x];
			v2 = (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x];
			v3 = (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x];
			v4 = (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x];
			v5 = (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x];
			v6 = (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x];
			rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 10);
			rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 10);
			rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 10);
			rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 10);
			rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 10);
			rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 10);
			rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 10);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			if (x % 8 == 7)
				continue;

			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v2 = (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x];
			v3 = (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x];
			v4 = (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x];
			v5 = (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x];
			v6 = (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 10);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 10);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 10);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 10);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 10);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 10);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 10);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			if (x % 8 == 7)
				continue;

			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v2 = (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x];
			v3 = (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x];
			v4 = (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x];
			v5 = (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x];
			v6 = (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 10);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 10);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 10);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 10);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 10);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 10);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 10);
		}
	}
}

void rtuInverse(rtuStruct rtu)
{
	static s32 v0, v1, v2, v3, v4, v5, v6;

	// Perform the horizontal pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		if (y % 8 == 7)
			continue;

		for (u8 x = 0; x < CU_SIZE / 2; x += 8)
		{
			// Perform the luma transform
			v0 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v3 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v4 = 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v5 = 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] - 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v6 = 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast(v3 >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((v2 - v6) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((v1 - v5) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((v0 - v4) >> 10);

			// Perform the first chroma transform
			v0 = 137 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] + 175 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] + 121 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] + 43 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v1 = 137 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] + 43 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] - 175 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] - 121 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v2 = 137 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] - 121 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] - 43 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] + 175 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v3 = 137 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] - 194 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] + 194 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] - 194 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v4 = 189 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] + 151 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] + 84 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5];
			v5 = 151 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] - 84 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] - 189 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5];
			v6 = 84 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] - 189 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] + 151 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5];
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] = coeffCast((v0 + v4) >> 10);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] = coeffCast((v1 + v5) >> 10);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] = coeffCast((v2 + v6) >> 10);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] = coeffCast(v3 >> 10);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] = coeffCast((v2 - v6) >> 10);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] = coeffCast((v1 - v5) >> 10);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6] = coeffCast((v0 - v4) >> 10);

			// Perform the second chroma transform
			v0 = 137 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] + 175 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] + 121 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] + 43 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v1 = 137 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] + 43 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] - 175 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] - 121 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v2 = 137 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] - 121 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] - 43 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] + 175 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v3 = 137 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] - 194 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] + 194 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] - 194 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v4 = 189 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] + 151 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] + 84 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5];
			v5 = 151 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] - 84 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] - 189 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5];
			v6 = 84 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] - 189 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] + 151 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5];
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] = coeffCast((v0 + v4) >> 10);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] = coeffCast((v1 + v5) >> 10);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] = coeffCast((v2 + v6) >> 10);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] = coeffCast(v3 >> 10);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] = coeffCast((v2 - v6) >> 10);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] = coeffCast((v1 - v5) >> 10);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6] = coeffCast((v0 - v4) >> 10);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v3 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v4 = 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v5 = 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] - 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v6 = 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast(v3 >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((v2 - v6) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((v1 - v5) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((v0 - v4) >> 10);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		if (y % 8 == 7)
			continue;

		for (u8 x = 0; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 121 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 43 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 175 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v3 = 137 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 194 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v4 = 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v5 = 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] - 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v6 = 84 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 189 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 151 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast(v3 >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((v2 - v6) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((v1 - v5) >> 10);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((v0 - v4) >> 10);
		}
	}

	// Perform the vertical pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			if (x % 8 == 7)
				continue;

			// Perform the luma transform
			v0 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 175 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 121 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 43 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 43 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 175 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 121 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 121 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 43 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 175 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v3 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 194 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 194 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 194 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v4 = 189 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + 151 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 84 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v5 = 151 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 84 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] - 189 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v6 = 84 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 189 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 151 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = residualCast((v0 + v4) >> 11);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = residualCast((v1 + v5) >> 11);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = residualCast((v2 + v6) >> 11);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = residualCast(v3 >> 11);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = residualCast((v2 - v6) >> 11);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = residualCast((v1 - v5) >> 11);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = residualCast((v0 - v4) >> 11);

			// Perform the first chroma transform
			v0 = 137 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] + 175 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] + 121 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] + 43 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v1 = 137 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] + 43 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] - 175 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] - 121 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v2 = 137 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] - 121 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] - 43 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] + 175 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v3 = 137 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] - 194 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] + 194 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] - 194 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v4 = 189 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] + 151 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] + 84 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x];
			v5 = 151 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] - 84 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] - 189 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x];
			v6 = 84 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] - 189 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] + 151 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x];
			rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] = residualCast((v0 + v4) >> 11);
			rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] = residualCast((v1 + v5) >> 11);
			rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] = residualCast((v2 + v6) >> 11);
			rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] = residualCast(v3 >> 11);
			rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] = residualCast((v2 - v6) >> 11);
			rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] = residualCast((v1 - v5) >> 11);
			rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x] = residualCast((v0 - v4) >> 11);

			// Perform the second chroma transform
			v0 = 137 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] + 175 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] + 121 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] + 43 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v1 = 137 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] + 43 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] - 175 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] - 121 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v2 = 137 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] - 121 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] - 43 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] + 175 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v3 = 137 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] - 194 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] + 194 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] - 194 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v4 = 189 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] + 151 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] + 84 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x];
			v5 = 151 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] - 84 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] - 189 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x];
			v6 = 84 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] - 189 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] + 151 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x];
			rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] = residualCast((v0 + v4) >> 11);
			rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] = residualCast((v1 + v5) >> 11);
			rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] = residualCast((v2 + v6) >> 11);
			rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] = residualCast(v3 >> 11);
			rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] = residualCast((v2 - v6) >> 11);
			rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] = residualCast((v1 - v5) >> 11);
			rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x] = residualCast((v0 - v4) >> 11);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			if (x % 8 == 7)
				continue;

			// Perform the luma transform
			v0 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 175 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 121 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 43 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 43 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 175 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 121 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 121 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 43 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 175 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v3 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 194 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 194 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 194 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v4 = 189 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + 151 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 84 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v5 = 151 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 84 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] - 189 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v6 = 84 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 189 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 151 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = residualCast((v0 + v4) >> 11);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = residualCast((v1 + v5) >> 11);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = residualCast((v2 + v6) >> 11);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = residualCast(v3 >> 11);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = residualCast((v2 - v6) >> 11);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = residualCast((v1 - v5) >> 11);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = residualCast((v0 - v4) >> 11);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			if (x % 8 == 7)
				continue;

			// Perform the luma transform
			v0 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 175 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 121 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 43 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 43 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 175 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 121 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 121 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 43 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 175 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v3 = 137 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 194 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 194 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 194 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v4 = 189 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + 151 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 84 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v5 = 151 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 84 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] - 189 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v6 = 84 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 189 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 151 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = residualCast((v0 + v4) >> 11);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = residualCast((v1 + v5) >> 11);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = residualCast((v2 + v6) >> 11);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = residualCast(v3 >> 11);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = residualCast((v2 - v6) >> 11);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = residualCast((v1 - v5) >> 11);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = residualCast((v0 - v4) >> 11);
		}
	}
}
#else
void rtuForward(rtuStruct rtu)
{
	static s32 v0, v1, v2, v3, v4, v5, v6, v7;

	// Perform the horizontal pass of the 8-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 8)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v1 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v3 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 4];
			v4 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 3];
			v5 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 2];
			v6 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 6] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 1];
			v7 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 7] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 0];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 7] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 2);

			// Perform the first chroma transform
			v0 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7];
			v1 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v2 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5];
			v3 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] + (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4];
			v4 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3];
			v5 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2];
			v6 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1];
			v7 = (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7] - (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0];
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 2);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 2);

			// Perform the second chroma transform
			v0 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7];
			v1 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v2 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5];
			v3 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] + (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4];
			v4 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3];
			v5 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2];
			v6 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1];
			v7 = (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7] - (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0];
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 2);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 2);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v1 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v3 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 4];
			v4 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 3];
			v5 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 2];
			v6 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 6] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 1];
			v7 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 7] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 0];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 7] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 2);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v1 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 5];
			v3 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + (s32)rtu.rtbLuma[y * CU_SIZE + x + 4];
			v4 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 3];
			v5 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 2];
			v6 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 6] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 1];
			v7 = (s32)rtu.rtbLuma[y * CU_SIZE + x + 7] - (s32)rtu.rtbLuma[y * CU_SIZE + x + 0];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 2);
			rtu.rtbLuma[y * CU_SIZE + x + 7] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 2);
		}
	}

	// Perform the vertical pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v1 = (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v3 = (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x];
			v4 = (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x];
			v5 = (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x];
			v6 = (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x];
			v7 = (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 9);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 9);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 9);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 9);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 9);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 9);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 9);
			rtu.rtbLuma[(y + 7) * CU_SIZE + x] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 9);

			// Perform the first chroma transform
			v0 = (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x];
			v1 = (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v2 = (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x];
			v3 = (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x];
			v4 = (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x];
			v5 = (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x];
			v6 = (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x];
			v7 = (s32)rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x];
			rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 9);
			rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 9);
			rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 9);
			rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 9);
			rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 9);
			rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 9);
			rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 9);
			rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 9);

			// Perform the second chroma transform
			v0 = (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x];
			v1 = (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v2 = (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x];
			v3 = (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] + (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x];
			v4 = (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x];
			v5 = (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x];
			v6 = (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x];
			v7 = (s32)rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x] - (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x];
			rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 9);
			rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 9);
			rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 9);
			rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 9);
			rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 9);
			rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 9);
			rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 9);
			rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 9);

		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v1 = (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v3 = (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x];
			v4 = (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x];
			v5 = (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x];
			v6 = (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x];
			v7 = (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 9);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 9);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 9);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 9);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 9);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 9);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 9);
			rtu.rtbLuma[(y + 7) * CU_SIZE + x] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 9);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v1 = (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x];
			v3 = (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x];
			v4 = (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x];
			v5 = (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x];
			v6 = (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x];
			v7 = (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x] - (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 9);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 9);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 9);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 9);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 9);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 9);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 9);
			rtu.rtbLuma[(y + 7) * CU_SIZE + x] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 9);
		}
	}
}

void rtuInverse(rtuStruct rtu)
{
	static s32 v0, v1, v2, v3, v4, v5, v6, v7;

	// Perform the horizontal pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 8)
		{
			// Perform the luma transform
			v0 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v3 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v4 = 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] + 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v5 = 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v6 = 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v7 = 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((v3 + v7) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((v3 - v7) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((v2 - v6) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((v1 - v5) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 7] = coeffCast((v0 - v4) >> 7);

			// Perform the first chroma transform
			v0 = 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] + 83 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] + 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] + 36 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v1 = 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] + 36 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] - 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] - 83 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v2 = 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] - 36 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] - 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] + 83 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v3 = 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] - 83 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] + 64 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] - 36 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6];
			v4 = 89 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] + 75 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] + 50 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] + 18 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7];
			v5 = 75 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] - 18 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] - 89 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] - 50 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7];
			v6 = 50 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] - 89 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] + 18 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] + 75 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7];
			v7 = 18 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] - 50 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] + 75 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] - 89 * (s32)rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7];
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 0] = coeffCast((v0 + v4) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 1] = coeffCast((v1 + v5) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 2] = coeffCast((v2 + v6) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 3] = coeffCast((v3 + v7) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 4] = coeffCast((v3 - v7) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 5] = coeffCast((v2 - v6) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 6] = coeffCast((v1 - v5) >> 7);
			rtu.rtbChroma1[y * CU_SIZE / 2 + x + 7] = coeffCast((v0 - v4) >> 7);

			// Perform the second chroma transform
			v0 = 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] + 83 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] + 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] + 36 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v1 = 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] + 36 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] - 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] - 83 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v2 = 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] - 36 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] - 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] + 83 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v3 = 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] - 83 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] + 64 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] - 36 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6];
			v4 = 89 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] + 75 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] + 50 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] + 18 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7];
			v5 = 75 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] - 18 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] - 89 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] - 50 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7];
			v6 = 50 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] - 89 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] + 18 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] + 75 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7];
			v7 = 18 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] - 50 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] + 75 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] - 89 * (s32)rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7];
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 0] = coeffCast((v0 + v4) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 1] = coeffCast((v1 + v5) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 2] = coeffCast((v2 + v6) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 3] = coeffCast((v3 + v7) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 4] = coeffCast((v3 - v7) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 5] = coeffCast((v2 - v6) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 6] = coeffCast((v1 - v5) >> 7);
			rtu.rtbChroma2[y * CU_SIZE / 2 + x + 7] = coeffCast((v0 - v4) >> 7);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v3 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v4 = 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] + 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v5 = 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v6 = 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v7 = 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((v3 + v7) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((v3 - v7) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((v2 - v6) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((v1 - v5) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 7] = coeffCast((v0 - v4) >> 7);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x += 8)
		{
			// Perform the luma transform
			v0 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v1 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] + 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v2 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] - 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] + 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v3 = 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 0] - 83 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 2] + 64 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 4] - 36 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 6];
			v4 = 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] + 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v5 = 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v6 = 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			v7 = 18 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 1] - 50 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 3] + 75 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 5] - 89 * (s32)rtu.rtbLuma[y * CU_SIZE + x + 7];
			rtu.rtbLuma[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 3] = coeffCast((v3 + v7) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 4] = coeffCast((v3 - v7) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 5] = coeffCast((v2 - v6) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 6] = coeffCast((v1 - v5) >> 7);
			rtu.rtbLuma[y * CU_SIZE + x + 7] = coeffCast((v0 - v4) >> 7);
		}
	}

	// Perform the vertical pass of the 7-point even-odd DCT
	for (u8 y = 0; y < CU_SIZE / 2; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			// Perform the luma transform
			v0 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 83 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 36 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 36 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 83 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 36 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 83 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v3 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 83 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 36 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v4 = 89 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 50 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] + 18 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v5 = 75 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 18 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - 50 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v6 = 50 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 18 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v7 = 18 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 50 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((v0 + v4) >> 12);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((v1 + v5) >> 12);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((v2 + v6) >> 12);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((v3 + v7) >> 12);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((v3 - v7) >> 12);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((v2 - v6) >> 12);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((v1 - v5) >> 12);
			rtu.rtbLuma[(y + 7) * CU_SIZE + x] = coeffCast((v0 - v4) >> 12);

			// Perform the first chroma transform
			v0 = 64 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] + 83 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] + 64 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] + 36 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v1 = 64 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] + 36 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] - 64 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] - 83 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v2 = 64 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] - 36 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] - 64 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] + 83 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v3 = 64 * (s32)rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] - 83 * (s32)rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] + 64 * (s32)rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] - 36 * (s32)rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x];
			v4 = 89 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] + 75 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] + 50 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] + 18 * (s32)rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x];
			v5 = 75 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] - 18 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] - 89 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] - 50 * (s32)rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x];
			v6 = 50 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] - 89 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] + 18 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] + 75 * (s32)rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x];
			v7 = 18 * (s32)rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] - 50 * (s32)rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] + 75 * (s32)rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] - 89 * (s32)rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x];
			rtu.rtbChroma1[(y + 0) * CU_SIZE / 2 + x] = coeffCast((v0 + v4) >> 12);
			rtu.rtbChroma1[(y + 1) * CU_SIZE / 2 + x] = coeffCast((v1 + v5) >> 12);
			rtu.rtbChroma1[(y + 2) * CU_SIZE / 2 + x] = coeffCast((v2 + v6) >> 12);
			rtu.rtbChroma1[(y + 3) * CU_SIZE / 2 + x] = coeffCast((v3 + v7) >> 12);
			rtu.rtbChroma1[(y + 4) * CU_SIZE / 2 + x] = coeffCast((v3 - v7) >> 12);
			rtu.rtbChroma1[(y + 5) * CU_SIZE / 2 + x] = coeffCast((v2 - v6) >> 12);
			rtu.rtbChroma1[(y + 6) * CU_SIZE / 2 + x] = coeffCast((v1 - v5) >> 12);
			rtu.rtbChroma1[(y + 7) * CU_SIZE / 2 + x] = coeffCast((v0 - v4) >> 12);

			// Perform the second chroma transform
			v0 = 64 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] + 83 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] + 64 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] + 36 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v1 = 64 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] + 36 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] - 64 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] - 83 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v2 = 64 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] - 36 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] - 64 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] + 83 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v3 = 64 * (s32)rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] - 83 * (s32)rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] + 64 * (s32)rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] - 36 * (s32)rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x];
			v4 = 89 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] + 75 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] + 50 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] + 18 * (s32)rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x];
			v5 = 75 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] - 18 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] - 89 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] - 50 * (s32)rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x];
			v6 = 50 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] - 89 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] + 18 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] + 75 * (s32)rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x];
			v7 = 18 * (s32)rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] - 50 * (s32)rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] + 75 * (s32)rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] - 89 * (s32)rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x];
			rtu.rtbChroma2[(y + 0) * CU_SIZE / 2 + x] = coeffCast((v0 + v4) >> 12);
			rtu.rtbChroma2[(y + 1) * CU_SIZE / 2 + x] = coeffCast((v1 + v5) >> 12);
			rtu.rtbChroma2[(y + 2) * CU_SIZE / 2 + x] = coeffCast((v2 + v6) >> 12);
			rtu.rtbChroma2[(y + 3) * CU_SIZE / 2 + x] = coeffCast((v3 + v7) >> 12);
			rtu.rtbChroma2[(y + 4) * CU_SIZE / 2 + x] = coeffCast((v3 - v7) >> 12);
			rtu.rtbChroma2[(y + 5) * CU_SIZE / 2 + x] = coeffCast((v2 - v6) >> 12);
			rtu.rtbChroma2[(y + 6) * CU_SIZE / 2 + x] = coeffCast((v1 - v5) >> 12);
			rtu.rtbChroma2[(y + 7) * CU_SIZE / 2 + x] = coeffCast((v0 - v4) >> 12);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 83 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 36 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 36 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 83 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 36 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 83 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v3 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 83 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 36 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v4 = 89 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 50 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] + 18 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v5 = 75 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 18 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - 50 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v6 = 50 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 18 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v7 = 18 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 50 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((v0 + v4) >> 12);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((v1 + v5) >> 12);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((v2 + v6) >> 12);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((v3 + v7) >> 12);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((v3 - v7) >> 12);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((v2 - v6) >> 12);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((v1 - v5) >> 12);
			rtu.rtbLuma[(y + 7) * CU_SIZE + x] = coeffCast((v0 - v4) >> 12);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			// Perform the luma transform
			v0 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 83 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 36 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v1 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] + 36 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 83 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v2 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 36 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] - 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] + 83 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v3 = 64 * (s32)rtu.rtbLuma[(y + 0) * CU_SIZE + x] - 83 * (s32)rtu.rtbLuma[(y + 2) * CU_SIZE + x] + 64 * (s32)rtu.rtbLuma[(y + 4) * CU_SIZE + x] - 36 * (s32)rtu.rtbLuma[(y + 6) * CU_SIZE + x];
			v4 = 89 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 50 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] + 18 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v5 = 75 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 18 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - 50 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v6 = 50 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 18 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			v7 = 18 * (s32)rtu.rtbLuma[(y + 1) * CU_SIZE + x] - 50 * (s32)rtu.rtbLuma[(y + 3) * CU_SIZE + x] + 75 * (s32)rtu.rtbLuma[(y + 5) * CU_SIZE + x] - 89 * (s32)rtu.rtbLuma[(y + 7) * CU_SIZE + x];
			rtu.rtbLuma[(y + 0) * CU_SIZE + x] = coeffCast((v0 + v4) >> 12);
			rtu.rtbLuma[(y + 1) * CU_SIZE + x] = coeffCast((v1 + v5) >> 12);
			rtu.rtbLuma[(y + 2) * CU_SIZE + x] = coeffCast((v2 + v6) >> 12);
			rtu.rtbLuma[(y + 3) * CU_SIZE + x] = coeffCast((v3 + v7) >> 12);
			rtu.rtbLuma[(y + 4) * CU_SIZE + x] = coeffCast((v3 - v7) >> 12);
			rtu.rtbLuma[(y + 5) * CU_SIZE + x] = coeffCast((v2 - v6) >> 12);
			rtu.rtbLuma[(y + 6) * CU_SIZE + x] = coeffCast((v1 - v5) >> 12);
			rtu.rtbLuma[(y + 7) * CU_SIZE + x] = coeffCast((v0 - v4) >> 12);
		}
	}
}
#endif

s16 coeffCast(s32 val)
{
	return ((val < -32768) ? -32768 : ((val > 32767) ? 32767 : val));
}

s16 pixelCast(s32 val)
{
	return ((val < 0) ? 0 : ((val > 255) ? 255 : val));
}

s16 residualCast(s32 val)
{
	return ((val < -255) ? -255 : ((val > 255) ? 255 : val));
}