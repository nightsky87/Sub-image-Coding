#include "SiCComTU.h"

void tuForward(stuStruct &stu, ChromaSub chromaSub)
{
	// Process the luma components
	tuForward(stu.hscu->scbLuma, CU_SIZE / 8, CU_SIZE, 4);
	tuForward(stu.vscu->scbLuma, CU_SIZE, CU_SIZE / 8, 4);

	// Process the chroma components
	if (chromaSub == CHROMA_444)
	{
		tuForward(stu.hscu->scbChroma1, CU_SIZE / 8, CU_SIZE, 4);
		tuForward(stu.hscu->scbChroma2, CU_SIZE / 8, CU_SIZE, 4);
		tuForward(stu.vscu->scbChroma1, CU_SIZE, CU_SIZE / 8, 4);
		tuForward(stu.vscu->scbChroma2, CU_SIZE, CU_SIZE / 8, 4);
	}
	else if (chromaSub == CHROMA_420)
	{
		tuForward(stu.hscu->scbChroma1, CU_SIZE / 16, CU_SIZE / 2, 4);
		tuForward(stu.hscu->scbChroma2, CU_SIZE / 16, CU_SIZE / 2, 4);
		tuForward(stu.vscu->scbChroma1, CU_SIZE / 2, CU_SIZE / 16, 4);
		tuForward(stu.vscu->scbChroma2, CU_SIZE / 2, CU_SIZE / 16, 4);
	}
}

void tuForward(rtuStruct &rtu, ChromaSub chromaSub)
{
#if !USE_8x8_RTB
	const u8 dctSize = 7;
#else
	const u8 dctSize = 8;
#endif
	// Process the luma component
	tuForward(rtu.rtbLuma, CU_SIZE, CU_SIZE, dctSize);

	// Process the chroma components
	if (chromaSub == CHROMA_444)
	{
		tuForward(rtu.rtbChroma1, CU_SIZE, CU_SIZE, dctSize);
		tuForward(rtu.rtbChroma2, CU_SIZE, CU_SIZE, dctSize);
	}
	else if (chromaSub == CHROMA_420)
	{
		tuForward(rtu.rtbChroma1, CU_SIZE / 2, CU_SIZE / 2, dctSize);
		tuForward(rtu.rtbChroma2, CU_SIZE / 2, CU_SIZE / 2, dctSize);
	}
}

void tuForward(s16 *tb, u8 width, u8 height, u8 size)
{
	static s32 v0, v1, v2, v3, v4, v5, v6, v7;

	if (size == 4)
	{
		// Perform the horizontal pass of the 4-point even-odd DCT
		for (u8 y = 0; y < height; y++)
		{
			for (u8 x = 0; x < width; x += 4)
			{
				v0 = (s32)tb[y * CU_SIZE + x + 0] + (s32)tb[y * CU_SIZE + x + 3];
				v1 = (s32)tb[y * CU_SIZE + x + 1] + (s32)tb[y * CU_SIZE + x + 2];
				v2 = (s32)tb[y * CU_SIZE + x + 2] - (s32)tb[y * CU_SIZE + x + 1];
				v3 = (s32)tb[y * CU_SIZE + x + 3] - (s32)tb[y * CU_SIZE + x + 0];
				tb[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1)) >> 1);
				tb[y * CU_SIZE + x + 1] = coeffCast((-36 * v2 - 83 * v3) >> 1);
				tb[y * CU_SIZE + x + 2] = coeffCast((64 * (v0 - v1)) >> 1);
			tb[y * CU_SIZE + x + 3] = coeffCast((83 * v2 - 36 * v3) >> 1);
			}
		}

		// Perform the vertical pass of the 4-point even-odd DCT
		for (u8 y = 0; y < height; y += 4)
		{
			for (u8 x = 0; x < width; x++)
			{
				v0 = (s32)tb[(y + 0) * CU_SIZE + x] + (s32)tb[(y + 3) * CU_SIZE + x];
				v1 = (s32)tb[(y + 1) * CU_SIZE + x] + (s32)tb[(y + 2) * CU_SIZE + x];
				v2 = (s32)tb[(y + 2) * CU_SIZE + x] - (s32)tb[(y + 1) * CU_SIZE + x];
				v3 = (s32)tb[(y + 3) * CU_SIZE + x] - (s32)tb[(y + 0) * CU_SIZE + x];
				tb[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1)) >> 8);
				tb[(y + 1) * CU_SIZE + x] = coeffCast((-36 * v2 - 83 * v3) >> 8);
				tb[(y + 2) * CU_SIZE + x] = coeffCast((64 * (v0 - v1)) >> 8);
				tb[(y + 3) * CU_SIZE + x] = coeffCast((83 * v2 - 36 * v3) >> 8);
			}
		}
	}
#if !USE_8x8_RTB
	else if (size == 7)
	{
		// Perform the horizontal pass of the 7-point even-odd DCT
		for (u8 y = 0; y < height; y++)
		{
			if (y % 8 == 7)
				continue;

			for (u8 x = 0; x < width; x += 8)
			{
				v0 = (s32)tb[y * CU_SIZE + x + 0] + (s32)tb[y * CU_SIZE + x + 6];
				v1 = (s32)tb[y * CU_SIZE + x + 1] + (s32)tb[y * CU_SIZE + x + 5];
				v2 = (s32)tb[y * CU_SIZE + x + 2] + (s32)tb[y * CU_SIZE + x + 4];
				v3 = (s32)tb[y * CU_SIZE + x + 3];
				v4 = (s32)tb[y * CU_SIZE + x + 4] - (s32)tb[y * CU_SIZE + x + 2];
				v5 = (s32)tb[y * CU_SIZE + x + 5] - (s32)tb[y * CU_SIZE + x + 1];
				v6 = (s32)tb[y * CU_SIZE + x + 6] - (s32)tb[y * CU_SIZE + x + 0];
				tb[y * CU_SIZE + x + 0] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 3);
				tb[y * CU_SIZE + x + 1] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 3);
				tb[y * CU_SIZE + x + 2] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 3);
				tb[y * CU_SIZE + x + 3] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 3);
				tb[y * CU_SIZE + x + 4] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 3);
				tb[y * CU_SIZE + x + 5] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 3);
				tb[y * CU_SIZE + x + 6] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 3);
			}
		}
		
		// Perform the vertical pass of the 7-point even-odd DCT
		for (u8 y = 0; y < height; y += 8)
		{
			for (u8 x = 0; x < width; x++)
			{
				if (x % 8 == 7)
					continue;

				v0 = (s32)tb[(y + 0) * CU_SIZE + x] + (s32)tb[(y + 6) * CU_SIZE + x];
				v1 = (s32)tb[(y + 1) * CU_SIZE + x] + (s32)tb[(y + 5) * CU_SIZE + x];
				v2 = (s32)tb[(y + 2) * CU_SIZE + x] + (s32)tb[(y + 4) * CU_SIZE + x];
				v3 = (s32)tb[(y + 3) * CU_SIZE + x];
				v4 = (s32)tb[(y + 4) * CU_SIZE + x] - (s32)tb[(y + 2) * CU_SIZE + x];
				v5 = (s32)tb[(y + 5) * CU_SIZE + x] - (s32)tb[(y + 1) * CU_SIZE + x];
				v6 = (s32)tb[(y + 6) * CU_SIZE + x] - (s32)tb[(y + 0) * CU_SIZE + x];
				tb[(y + 0) * CU_SIZE + x] = coeffCast((137 * (v0 + v1 + v2 + v3)) >> 10);
				tb[(y + 1) * CU_SIZE + x] = coeffCast((-84 * v4 - 151 * v5 - 189 * v6) >> 10);
				tb[(y + 2) * CU_SIZE + x] = coeffCast((175 * v0 + 43 * v1 - 121 * v2 - 194 * v3) >> 10);
				tb[(y + 3) * CU_SIZE + x] = coeffCast((189 * v4 + 84 * v5 - 151 * v6) >> 10);
				tb[(y + 4) * CU_SIZE + x] = coeffCast((121 * v0 - 175 * v1 - 43 * v2 + 194 * v3) >> 10);
				tb[(y + 5) * CU_SIZE + x] = coeffCast((-151 * v4 + 189 * v5 - 84 * v6) >> 10);
				tb[(y + 6) * CU_SIZE + x] = coeffCast((43 * v0 - 121 * v1 + 175 * v2 - 194 * v3) >> 10);
			}
		}
	}
#else
	else if (size == 8)
	{
		// Perform the horizontal pass of the 8-point even-odd DCT
		for (u8 y = 0; y < height; y++)
		{
			for (u8 x = 0; x < width; x += 8)
			{
				v0 = (s32)tb[y * CU_SIZE + x + 0] + (s32)tb[y * CU_SIZE + x + 7];
				v1 = (s32)tb[y * CU_SIZE + x + 1] + (s32)tb[y * CU_SIZE + x + 6];
				v2 = (s32)tb[y * CU_SIZE + x + 2] + (s32)tb[y * CU_SIZE + x + 5];
				v3 = (s32)tb[y * CU_SIZE + x + 3] + (s32)tb[y * CU_SIZE + x + 4];
				v4 = (s32)tb[y * CU_SIZE + x + 4] - (s32)tb[y * CU_SIZE + x + 3];
				v5 = (s32)tb[y * CU_SIZE + x + 5] - (s32)tb[y * CU_SIZE + x + 2];
				v6 = (s32)tb[y * CU_SIZE + x + 6] - (s32)tb[y * CU_SIZE + x + 1];
				v7 = (s32)tb[y * CU_SIZE + x + 7] - (s32)tb[y * CU_SIZE + x + 0];
				tb[y * CU_SIZE + x + 0] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 2);
				tb[y * CU_SIZE + x + 1] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 2);
				tb[y * CU_SIZE + x + 2] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 2);
				tb[y * CU_SIZE + x + 3] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 2);
				tb[y * CU_SIZE + x + 4] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 2);
				tb[y * CU_SIZE + x + 5] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 2);
				tb[y * CU_SIZE + x + 6] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 2);
				tb[y * CU_SIZE + x + 7] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 2);
			}
		}

		// Perform the vertical pass of the 8-point even-odd DCT
		for (u8 y = 0; y < height; y += 8)
		{
			for (u8 x = 0; x < width; x++)
			{
				v0 = (s32)tb[(y + 0) * CU_SIZE + x] + (s32)tb[(y + 7) * CU_SIZE + x];
				v1 = (s32)tb[(y + 1) * CU_SIZE + x] + (s32)tb[(y + 6) * CU_SIZE + x];
				v2 = (s32)tb[(y + 2) * CU_SIZE + x] + (s32)tb[(y + 5) * CU_SIZE + x];
				v3 = (s32)tb[(y + 3) * CU_SIZE + x] + (s32)tb[(y + 4) * CU_SIZE + x];
				v4 = (s32)tb[(y + 4) * CU_SIZE + x] - (s32)tb[(y + 3) * CU_SIZE + x];
				v5 = (s32)tb[(y + 5) * CU_SIZE + x] - (s32)tb[(y + 2) * CU_SIZE + x];
				v6 = (s32)tb[(y + 6) * CU_SIZE + x] - (s32)tb[(y + 1) * CU_SIZE + x];
				v7 = (s32)tb[(y + 7) * CU_SIZE + x] - (s32)tb[(y + 0) * CU_SIZE + x];
				tb[(y + 0) * CU_SIZE + x] = coeffCast((64 * (v0 + v1 + v2 + v3)) >> 9);
				tb[(y + 1) * CU_SIZE + x] = coeffCast((-18 * v4 - 50 * v5 - 75 * v6 - 89 * v7) >> 9);
				tb[(y + 2) * CU_SIZE + x] = coeffCast((83 * (v0 - v3) + 36 * (v1 - v2)) >> 9);
				tb[(y + 3) * CU_SIZE + x] = coeffCast((50 * v4 + 89 * v5 + 18 * v6 - 75 * v7) >> 9);
				tb[(y + 4) * CU_SIZE + x] = coeffCast((64 * (v0 - v1 - v2 + v3)) >> 9);
				tb[(y + 5) * CU_SIZE + x] = coeffCast((-75 * v4 - 18 * v5 + 89 * v6 - 50 * v7) >> 9);
				tb[(y + 6) * CU_SIZE + x] = coeffCast((36 * (v0 - v3) - 83 * (v1 - v2)) >> 9);
				tb[(y + 7) * CU_SIZE + x] = coeffCast((89 * v4 - 75 * v5 + 50 * v6 - 18 * v7) >> 9);
			}
		}
	}
#endif
}

void tuInverse(stuStruct &stu, ChromaSub chromaSub)
{
	// Process the luma components
	tuInverse(stu.hscu->scbLuma, CU_SIZE / 8, CU_SIZE, 4);
	tuInverse(stu.vscu->scbLuma, CU_SIZE, CU_SIZE / 8, 4);

	// Process the chroma components
	if (chromaSub == CHROMA_444)
	{
		tuInverse(stu.hscu->scbChroma1, CU_SIZE / 8, CU_SIZE, 4);
		tuInverse(stu.hscu->scbChroma2, CU_SIZE / 8, CU_SIZE, 4);
		tuInverse(stu.vscu->scbChroma1, CU_SIZE, CU_SIZE / 8, 4);
		tuInverse(stu.vscu->scbChroma2, CU_SIZE, CU_SIZE / 8, 4);
	}
	else if (chromaSub == CHROMA_420)
	{
		tuInverse(stu.hscu->scbChroma1, CU_SIZE / 16, CU_SIZE / 2, 4);
		tuInverse(stu.hscu->scbChroma2, CU_SIZE / 16, CU_SIZE / 2, 4);
		tuInverse(stu.vscu->scbChroma1, CU_SIZE / 2, CU_SIZE / 16, 4);
		tuInverse(stu.vscu->scbChroma2, CU_SIZE / 2, CU_SIZE / 16, 4);
	}
}

void tuInverse(rtuStruct &rtu, ChromaSub chromaSub)
{
#if !USE_8x8_RTB
	const u8 dctSize = 7;
#else
	const u8 dctSize = 8;
#endif
	// Process the luma component
	tuInverse(rtu.rtbLuma, CU_SIZE, CU_SIZE, dctSize);

	// Process the chroma components
	if (chromaSub == CHROMA_444)
	{
		tuInverse(rtu.rtbChroma1, CU_SIZE, CU_SIZE, dctSize);
		tuInverse(rtu.rtbChroma2, CU_SIZE, CU_SIZE, dctSize);
	}
	else if (chromaSub == CHROMA_420)
	{
		tuInverse(rtu.rtbChroma1, CU_SIZE / 2, CU_SIZE / 2, dctSize);
		tuInverse(rtu.rtbChroma2, CU_SIZE / 2, CU_SIZE / 2, dctSize);
	}
}

void tuInverse(s16 *tb, u8 width, u8 height, u8 size)
{
	static s32 v0, v1, v2, v3, v4, v5, v6, v7;

	if (size == 4)
	{
		// Perform the horizontal pass of the 4-point even-odd DCT
		for (u8 y = 0; y < height; y++)
		{
			for (u8 x = 0; x < width; x += 4)
			{
				v0 = 64 * ((s32)tb[y * CU_SIZE + x + 0] + (s32)tb[y * CU_SIZE + x + 2]);
				v1 = 64 * ((s32)tb[y * CU_SIZE + x + 0] - (s32)tb[y * CU_SIZE + x + 2]);
				v2 = -36 * (s32)tb[y * CU_SIZE + x + 1] + 83 * (s32)tb[y * CU_SIZE + x + 3];
				v3 = -83 * (s32)tb[y * CU_SIZE + x + 1] - 36 * (s32)tb[y * CU_SIZE + x + 3];
				tb[y * CU_SIZE + x + 0] = coeffCast((v0 - v3) >> 7);
				tb[y * CU_SIZE + x + 1] = coeffCast((v1 - v2) >> 7);
				tb[y * CU_SIZE + x + 2] = coeffCast((v1 + v2) >> 7);
				tb[y * CU_SIZE + x + 3] = coeffCast((v0 + v3) >> 7);
			}
		}

		// Perform the vertical pass of the 4-point even-odd DCT
		for (u8 y = 0; y < height; y += 4)
		{
			for (u8 x = 0; x < width; x++)
			{
				v0 = 64 * ((s32)tb[(y + 0) * CU_SIZE + x] + (s32)tb[(y + 2) * CU_SIZE + x]);
				v1 = 64 * ((s32)tb[(y + 0) * CU_SIZE + x] - (s32)tb[(y + 2) * CU_SIZE + x]);
				v2 = -36 * (s32)tb[(y + 1) * CU_SIZE + x] + 83 * (s32)tb[(y + 3) * CU_SIZE + x];
				v3 = -83 * (s32)tb[(y + 1) * CU_SIZE + x] - 36 * (s32)tb[(y + 3) * CU_SIZE + x];
				tb[(y + 0) * CU_SIZE + x] = pixelCast((v0 - v3) >> 12);
				tb[(y + 1) * CU_SIZE + x] = pixelCast((v1 - v2) >> 12);
				tb[(y + 2) * CU_SIZE + x] = pixelCast((v1 + v2) >> 12);
				tb[(y + 3) * CU_SIZE + x] = pixelCast((v0 + v3) >> 12);
			}
		}
	}
#if !USE_8x8_RTB
	else if (size == 7)
	{
		// Perform the horizontal pass of the 7-point even-odd DCT
		for (u8 y = 0; y < height; y++)
		{
			if (y % 8 == 7)
				continue;

			for (u8 x = 0; x < width; x += 8)
			{
				v0 = 137 * (s32)tb[y * CU_SIZE + x + 0] + 175 * (s32)tb[y * CU_SIZE + x + 2] + 121 * (s32)tb[y * CU_SIZE + x + 4] + 43 * (s32)tb[y * CU_SIZE + x + 6];
				v1 = 137 * (s32)tb[y * CU_SIZE + x + 0] + 43 * (s32)tb[y * CU_SIZE + x + 2] - 175 * (s32)tb[y * CU_SIZE + x + 4] - 121 * (s32)tb[y * CU_SIZE + x + 6];
				v2 = 137 * (s32)tb[y * CU_SIZE + x + 0] - 121 * (s32)tb[y * CU_SIZE + x + 2] - 43 * (s32)tb[y * CU_SIZE + x + 4] + 175 * (s32)tb[y * CU_SIZE + x + 6];
				v3 = 137 * (s32)tb[y * CU_SIZE + x + 0] - 194 * (s32)tb[y * CU_SIZE + x + 2] + 194 * (s32)tb[y * CU_SIZE + x + 4] - 194 * (s32)tb[y * CU_SIZE + x + 6];
				v4 = 189 * (s32)tb[y * CU_SIZE + x + 1] + 151 * (s32)tb[y * CU_SIZE + x + 3] + 84 * (s32)tb[y * CU_SIZE + x + 5];
				v5 = 151 * (s32)tb[y * CU_SIZE + x + 1] - 84 * (s32)tb[y * CU_SIZE + x + 3] - 189 * (s32)tb[y * CU_SIZE + x + 5];
				v6 = 84 * (s32)tb[y * CU_SIZE + x + 1] - 189 * (s32)tb[y * CU_SIZE + x + 3] + 151 * (s32)tb[y * CU_SIZE + x + 5];
				tb[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 10);
				tb[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 10);
				tb[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 10);
				tb[y * CU_SIZE + x + 3] = coeffCast(v3 >> 10);
				tb[y * CU_SIZE + x + 4] = coeffCast((v2 - v6) >> 10);
				tb[y * CU_SIZE + x + 5] = coeffCast((v1 - v5) >> 10);
				tb[y * CU_SIZE + x + 6] = coeffCast((v0 - v4) >> 10);
			}
		}

		// Perform the vertical pass of the 7-point even-odd DCT
		for (u8 y = 0; y < height; y += 8)
		{
			for (u8 x = 0; x < width; x++)
			{
				if (x % 8 == 7)
					continue;

				v0 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] + 83 * (s32)tb[(y + 2) * CU_SIZE + x] + 64 * (s32)tb[(y + 4) * CU_SIZE + x] + 36 * (s32)tb[(y + 6) * CU_SIZE + x];
				v1 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] + 36 * (s32)tb[(y + 2) * CU_SIZE + x] - 64 * (s32)tb[(y + 4) * CU_SIZE + x] - 83 * (s32)tb[(y + 6) * CU_SIZE + x];
				v2 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] - 36 * (s32)tb[(y + 2) * CU_SIZE + x] - 64 * (s32)tb[(y + 4) * CU_SIZE + x] + 83 * (s32)tb[(y + 6) * CU_SIZE + x];
				v3 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] - 83 * (s32)tb[(y + 2) * CU_SIZE + x] + 64 * (s32)tb[(y + 4) * CU_SIZE + x] - 36 * (s32)tb[(y + 6) * CU_SIZE + x];
				v4 = 89 * (s32)tb[(y + 1) * CU_SIZE + x] + 75 * (s32)tb[(y + 3) * CU_SIZE + x] + 50 * (s32)tb[(y + 5) * CU_SIZE + x] + 18 * (s32)tb[(y + 7) * CU_SIZE + x];
				v5 = 75 * (s32)tb[(y + 1) * CU_SIZE + x] - 18 * (s32)tb[(y + 3) * CU_SIZE + x] - 89 * (s32)tb[(y + 5) * CU_SIZE + x] - 50 * (s32)tb[(y + 7) * CU_SIZE + x];
				v6 = 50 * (s32)tb[(y + 1) * CU_SIZE + x] - 89 * (s32)tb[(y + 3) * CU_SIZE + x] + 18 * (s32)tb[(y + 5) * CU_SIZE + x] + 75 * (s32)tb[(y + 7) * CU_SIZE + x];
				v7 = 18 * (s32)tb[(y + 1) * CU_SIZE + x] - 50 * (s32)tb[(y + 3) * CU_SIZE + x] + 75 * (s32)tb[(y + 5) * CU_SIZE + x] - 89 * (s32)tb[(y + 7) * CU_SIZE + x];
				tb[(y + 0) * CU_SIZE + x] = coeffCast((v0 + v4) >> 12);
				tb[(y + 1) * CU_SIZE + x] = coeffCast((v1 + v5) >> 12);
				tb[(y + 2) * CU_SIZE + x] = coeffCast((v2 + v6) >> 12);
				tb[(y + 3) * CU_SIZE + x] = coeffCast((v3 + v7) >> 12);
				tb[(y + 4) * CU_SIZE + x] = coeffCast((v3 - v7) >> 12);
				tb[(y + 5) * CU_SIZE + x] = coeffCast((v2 - v6) >> 12);
				tb[(y + 6) * CU_SIZE + x] = coeffCast((v1 - v5) >> 12);
				tb[(y + 7) * CU_SIZE + x] = coeffCast((v0 - v4) >> 12);
			}
		}
	}
#else
	else if (size == 8)
	{
		// Perform the horizontal pass of the 8-point even-odd DCT
		for (u8 y = 0; y < height; y++)
		{
			for (u8 x = 0; x < width; x += 8)
			{
				v0 = 64 * (s32)tb[y * CU_SIZE + x + 0] + 83 * (s32)tb[y * CU_SIZE + x + 2] + 64 * (s32)tb[y * CU_SIZE + x + 4] + 36 * (s32)tb[y * CU_SIZE + x + 6];
				v1 = 64 * (s32)tb[y * CU_SIZE + x + 0] + 36 * (s32)tb[y * CU_SIZE + x + 2] - 64 * (s32)tb[y * CU_SIZE + x + 4] - 83 * (s32)tb[y * CU_SIZE + x + 6];
				v2 = 64 * (s32)tb[y * CU_SIZE + x + 0] - 36 * (s32)tb[y * CU_SIZE + x + 2] - 64 * (s32)tb[y * CU_SIZE + x + 4] + 83 * (s32)tb[y * CU_SIZE + x + 6];
				v3 = 64 * (s32)tb[y * CU_SIZE + x + 0] - 83 * (s32)tb[y * CU_SIZE + x + 2] + 64 * (s32)tb[y * CU_SIZE + x + 4] - 36 * (s32)tb[y * CU_SIZE + x + 6];
				v4 = 89 * (s32)tb[y * CU_SIZE + x + 1] + 75 * (s32)tb[y * CU_SIZE + x + 3] + 50 * (s32)tb[y * CU_SIZE + x + 5] + 18 * (s32)tb[y * CU_SIZE + x + 7];
				v5 = 75 * (s32)tb[y * CU_SIZE + x + 1] - 18 * (s32)tb[y * CU_SIZE + x + 3] - 89 * (s32)tb[y * CU_SIZE + x + 5] - 50 * (s32)tb[y * CU_SIZE + x + 7];
				v6 = 50 * (s32)tb[y * CU_SIZE + x + 1] - 89 * (s32)tb[y * CU_SIZE + x + 3] + 18 * (s32)tb[y * CU_SIZE + x + 5] + 75 * (s32)tb[y * CU_SIZE + x + 7];
				v7 = 18 * (s32)tb[y * CU_SIZE + x + 1] - 50 * (s32)tb[y * CU_SIZE + x + 3] + 75 * (s32)tb[y * CU_SIZE + x + 5] - 89 * (s32)tb[y * CU_SIZE + x + 7];
				tb[y * CU_SIZE + x + 0] = coeffCast((v0 + v4) >> 7);
				tb[y * CU_SIZE + x + 1] = coeffCast((v1 + v5) >> 7);
				tb[y * CU_SIZE + x + 2] = coeffCast((v2 + v6) >> 7);
				tb[y * CU_SIZE + x + 3] = coeffCast((v3 + v7) >> 7);
				tb[y * CU_SIZE + x + 4] = coeffCast((v3 - v7) >> 7);
				tb[y * CU_SIZE + x + 5] = coeffCast((v2 - v6) >> 7);
				tb[y * CU_SIZE + x + 6] = coeffCast((v1 - v5) >> 7);
				tb[y * CU_SIZE + x + 7] = coeffCast((v0 - v4) >> 7);
			}
		}

		// Perform the vertical pass of the 8-point even-odd DCT
		for (u8 y = 0; y < height; y += 8)
		{
			for (u8 x = 0; x < width; x++)
			{
				v0 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] + 83 * (s32)tb[(y + 2) * CU_SIZE + x] + 64 * (s32)tb[(y + 4) * CU_SIZE + x] + 36 * (s32)tb[(y + 6) * CU_SIZE + x];
				v1 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] + 36 * (s32)tb[(y + 2) * CU_SIZE + x] - 64 * (s32)tb[(y + 4) * CU_SIZE + x] - 83 * (s32)tb[(y + 6) * CU_SIZE + x];
				v2 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] - 36 * (s32)tb[(y + 2) * CU_SIZE + x] - 64 * (s32)tb[(y + 4) * CU_SIZE + x] + 83 * (s32)tb[(y + 6) * CU_SIZE + x];
				v3 = 64 * (s32)tb[(y + 0) * CU_SIZE + x] - 83 * (s32)tb[(y + 2) * CU_SIZE + x] + 64 * (s32)tb[(y + 4) * CU_SIZE + x] - 36 * (s32)tb[(y + 6) * CU_SIZE + x];
				v4 = 89 * (s32)tb[(y + 1) * CU_SIZE + x] + 75 * (s32)tb[(y + 3) * CU_SIZE + x] + 50 * (s32)tb[(y + 5) * CU_SIZE + x] + 18 * (s32)tb[(y + 7) * CU_SIZE + x];
				v5 = 75 * (s32)tb[(y + 1) * CU_SIZE + x] - 18 * (s32)tb[(y + 3) * CU_SIZE + x] - 89 * (s32)tb[(y + 5) * CU_SIZE + x] - 50 * (s32)tb[(y + 7) * CU_SIZE + x];
				v6 = 50 * (s32)tb[(y + 1) * CU_SIZE + x] - 89 * (s32)tb[(y + 3) * CU_SIZE + x] + 18 * (s32)tb[(y + 5) * CU_SIZE + x] + 75 * (s32)tb[(y + 7) * CU_SIZE + x];
				v7 = 18 * (s32)tb[(y + 1) * CU_SIZE + x] - 50 * (s32)tb[(y + 3) * CU_SIZE + x] + 75 * (s32)tb[(y + 5) * CU_SIZE + x] - 89 * (s32)tb[(y + 7) * CU_SIZE + x];
				tb[(y + 0) * CU_SIZE + x] = coeffCast((v0 + v4) >> 12);
				tb[(y + 1) * CU_SIZE + x] = coeffCast((v1 + v5) >> 12);
				tb[(y + 2) * CU_SIZE + x] = coeffCast((v2 + v6) >> 12);
				tb[(y + 3) * CU_SIZE + x] = coeffCast((v3 + v7) >> 12);
				tb[(y + 4) * CU_SIZE + x] = coeffCast((v3 - v7) >> 12);
				tb[(y + 5) * CU_SIZE + x] = coeffCast((v2 - v6) >> 12);
				tb[(y + 6) * CU_SIZE + x] = coeffCast((v1 - v5) >> 12);
				tb[(y + 7) * CU_SIZE + x] = coeffCast((v0 - v4) >> 12);
			}
		}
	}
#endif
}

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