#include "SiCComBAC.h"
#include <cstdio>

void stuEnc(stuStruct stu)
{
	vstbEnc(stu.vscu);
	hstbEnc(stu.hscu);
}

void vstbEnc(scuStruct *scu)
{
	// Process the top row of luma STBs
	stbEnc(&scu->scbLuma[0], COMPONENT_LUMA, SCAN_VERT);
	for (u8 x = 4; x < CU_SIZE; x += 4)
	{
		s16 dcVal = scu->scbLuma[x];
		scu->scbLuma[x] = dcVal - scu->scbLuma[x - 4];
		stbEnc(&scu->scbLuma[x], COMPONENT_LUMA, SCAN_VERT);
		scu->scbLuma[x] = dcVal;
	}

	// Process the remaining rows of luma STBs
	for (u8 y = 4; y < CU_SIZE / 8; y += 4)
	{
		// Process the leftmost luma STB
		s16 dcVal = scu->scbLuma[CU_SIZE * y];
		scu->scbLuma[CU_SIZE * y] = dcVal - scu->scbLuma[CU_SIZE * (y - 4)];
		stbEnc(&scu->scbLuma[CU_SIZE * y], COMPONENT_LUMA, SCAN_VERT);
		scu->scbLuma[CU_SIZE * y] = dcVal;

		// Process the remaining luma STBs
		for (u8 x = 4; x < CU_SIZE; x += 4)
		{
			s16 dcVal = scu->scbLuma[CU_SIZE * y + x];
			scu->scbLuma[CU_SIZE * y + x] = dcVal - scu->scbLuma[CU_SIZE * y + x - 4];
			stbEnc(&scu->scbLuma[CU_SIZE * y + x], COMPONENT_LUMA, SCAN_VERT);
			scu->scbLuma[CU_SIZE * y + x] = dcVal;
		}
	}

	// Process the top row of chroma STBs
	stbEnc(&scu->scbChroma1[0], COMPONENT_CHROMA, SCAN_VERT);
	stbEnc(&scu->scbChroma2[0], COMPONENT_CHROMA, SCAN_VERT);
	for (u8 x = 4; x < CU_SIZE / 2; x += 4)
	{
		s16 dcVal = scu->scbChroma1[x];
		scu->scbChroma1[x] = dcVal - scu->scbChroma1[x - 4];
		stbEnc(&scu->scbChroma1[x], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma1[x] = dcVal;

		dcVal = scu->scbChroma2[x];
		scu->scbChroma2[x] = dcVal - scu->scbChroma2[x - 4];
		stbEnc(&scu->scbChroma2[x], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma2[x] = dcVal;
	}

#if CU_SIZE > 64
	// Process the remaining rows of the chroma STBs
	for (u8 y = 4; y < CU_SIZE / 16; y += 4)
	{
		// Process the leftmost chroma STB
		s16 dcVal = scu->scbChroma1[CU_SIZE / 2 * y];
		scu->scbChroma1[CU_SIZE / 2 * y] = dcVal - scu->scbChroma1[CU_SIZE / 2 * (y - 4)];
		stbEnc(&scu->scbChroma1[CU_SIZE / 2 * y], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma1[CU_SIZE / 2 * y] = dcVal;

		dcVal = scu->scbChroma2[CU_SIZE / 2 * y];
		scu->scbChroma2[CU_SIZE / 2 * y] = dcVal - scu->scbChroma2[CU_SIZE / 2 * (y - 4)];
		stbEnc(&scu->scbChroma2[CU_SIZE / 2 * y], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma2[CU_SIZE / 2 * y] = dcVal;

		// Process the remaining chroma STBs
		for (u8 x = 4; x < CU_SIZE; x += 4)
		{
			s16 dcVal = scu->scbChroma1[CU_SIZE / 2 * y + x];
			scu->scbChroma1[CU_SIZE / 2 * y + x] = dcVal - scu->scbChroma1[CU_SIZE / 2 * y + x - 4];
			stbEnc(&scu->scbChroma1[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, SCAN_VERT);
			scu->scbChroma1[CU_SIZE / 2 * y + x] = dcVal;

			dcVal = scu->scbChroma2[CU_SIZE / 2 * y + x];
			scu->scbChroma2[CU_SIZE / 2 * y + x] = dcVal - scu->scbChroma2[CU_SIZE / 2 * y + x - 4];
			stbEnc(&scu->scbChroma2[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, SCAN_VERT);
			scu->scbChroma2[CU_SIZE / 2 * y + x] = dcVal;
		}
	}
#endif
}

void hstbEnc(scuStruct *scu)
{
	// Process the left column of luma STBs
	stbEnc(&scu->scbLuma[0], COMPONENT_LUMA, SCAN_HORZ);
	for (u8 y = 4; y < CU_SIZE; y += 4)
	{
		s16 dcVal = scu->scbLuma[CU_SIZE / 8 * y];
		scu->scbLuma[CU_SIZE / 8 * y] = dcVal - scu->scbLuma[CU_SIZE / 8 * (y - 4)];
		stbEnc(&scu->scbLuma[CU_SIZE / 8 * y], COMPONENT_LUMA, SCAN_HORZ);
		scu->scbLuma[CU_SIZE / 8 * y] = dcVal;
	}

	// Process the remaining columns of luma STBs
	for (u8 x = 4; x < CU_SIZE / 8; x += 4)
	{
		// Process the top luma STB
		s16 dcVal = scu->scbLuma[x];
		scu->scbLuma[x] = dcVal - scu->scbLuma[x - 4];
		stbEnc(&scu->scbLuma[x], COMPONENT_LUMA, SCAN_HORZ);
		scu->scbLuma[x] = dcVal;

		// Process the remaining luma STBs
		for (u8 y = 4; y < CU_SIZE; y += 4)
		{
			s16 dcVal = scu->scbLuma[CU_SIZE / 8 * y + x];
			scu->scbLuma[CU_SIZE / 8 * y + x] = dcVal - scu->scbLuma[CU_SIZE / 8 * (y - 4) + x];
			stbEnc(&scu->scbLuma[CU_SIZE / 8 * y + x], COMPONENT_LUMA, SCAN_HORZ);
			scu->scbLuma[CU_SIZE / 8 * y + x] = dcVal;
		}
	}

	// Process the left column of chroma STBs
	stbEnc(&scu->scbChroma1[0], COMPONENT_CHROMA, SCAN_HORZ);
	stbEnc(&scu->scbChroma2[0], COMPONENT_CHROMA, SCAN_HORZ);
	for (u8 y = 4; y < CU_SIZE / 2; y += 4)
	{
		s16 dcVal = scu->scbChroma1[CU_SIZE / 16 * y];
		scu->scbChroma1[CU_SIZE / 16 * y] = dcVal - scu->scbChroma1[CU_SIZE / 16 * (y - 4)];
		stbEnc(&scu->scbChroma1[CU_SIZE / 16 * y], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma1[CU_SIZE / 16 * y] = dcVal;

		dcVal = scu->scbChroma2[CU_SIZE / 16 * y];
		scu->scbChroma2[CU_SIZE / 16 * y] = dcVal - scu->scbChroma2[CU_SIZE / 16 * (y - 4)];
		stbEnc(&scu->scbChroma2[CU_SIZE / 16 * y], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma2[CU_SIZE / 16 * y] = dcVal;
	}

#if CU_SIZE > 64
	// Process the remaining columns of the chroma STBs
	for (u8 x = 4; x < CU_SIZE / 16; x += 4)
	{
		// Process the top chroma STB
		s16 dcVal = scu->scbChroma1[x];
		scu->scbChroma1[x] = dcVal - scu->scbChroma1[x - 4];
		stbEnc(&scu->scbChroma1[x], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma1[x] = dcVal;

		dcVal = scu->scbChroma2[x];
		scu->scbChroma2[x] = dcVal - scu->scbChroma2[x - 4];
		stbEnc(&scu->scbChroma2[x], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma2[x] = dcVal;

		// Process the remaining chroma STBs
		for (u8 y = 4; y < CU_SIZE; y += 4)
		{
			s16 dcVal = scu->scbChroma1[CU_SIZE / 16 * y + x];
			scu->scbChroma1[CU_SIZE / 16 * y + x] = dcVal - scu->scbChroma1[CU_SIZE / 16 * (y - 4) + x];
			stbEnc(&scu->scbChroma1[CU_SIZE / 16 * y + x], COMPONENT_CHROMA, SCAN_HORZ);
			scu->scbChroma1[CU_SIZE / 16 * y + x] = dcVal;

			dcVal = scu->scbChroma2[CU_SIZE / 16 * y + x];
			scu->scbChroma2[CU_SIZE / 16 * y + x] = dcVal - scu->scbChroma2[CU_SIZE / 16 * (y - 4) + x];
			stbEnc(&scu->scbChroma2[CU_SIZE / 16 * y + x], COMPONENT_CHROMA, SCAN_HORZ);
			scu->scbChroma2[CU_SIZE / 16 * y + x] = dcVal;
		}
	}
#endif
}

void stbEnc(s16 *stb, component comp, scanDir dir)
{
	// Define the context offsets
	const u8 dirBase = (dir == SCAN_HORZ) ? CTX_HSTB_BASE : CTX_VSTB_BASE;
	const u8 ctxBase = (comp == COMPONENT_LUMA) ? (dirBase + CTX_STB_LUMA_OFFSET) : (dirBase + CTX_STB_CHROMA_OFFSET);
	const u8 stride = (dir == SCAN_HORZ) ? ((comp == COMPONENT_LUMA) ? (CU_SIZE / 8) : (CU_SIZE / 16)) : ((comp == COMPONENT_LUMA) ? CU_SIZE : (CU_SIZE / 2));

	// Create an ordered copy of the STB
	static s16 stbOrd[16];
	if (dir == SCAN_HORZ)
	{
		for (u8 y = 0; y < 4; y++)
		{
			memcpy(&stbOrd[4 * y], &stb[stride * y], 4 * sizeof(s16));
		}
	}
	else
	{
		for (u8 x = 0; x < 4; x++)
		{
			for (u8 y = 0; y < 4; y++)
			{
				stbOrd[4 * x + y] = stb[stride * y + x];
			}
		}
	}

	// Determine the number of significant coefficients in the STB
	u8 numSig = 0;
	static s16 coeffVal[16];
	for (u8 i = 0; i < 16; i++)
	{
		if (stbOrd[i] != 0)
		{
			coeffVal[numSig] = stbOrd[i];
			numSig++;
		}
	}

	// Signal the number of significant coefficients using TU binarization
	for (u8 i = 0; i < numSig; i++)
	{
		EncodeDecision(ctxBase + CTX_STB_NUM_SIG_OFFSET, 1);
	}
	EncodeDecision(ctxBase + CTX_STB_NUM_SIG_OFFSET, 0);

	// Signal the significance map
	u8 curSig = 0;
	for (u8 i = 0; i < 16; i++)
	{
		if (stbOrd[i] == 0)
		{
			EncodeDecision(ctxBase + CTX_STB_SIG_FLAG_OFFSET + i, 0);
		}
		else
		{
			EncodeDecision(ctxBase + CTX_STB_SIG_FLAG_OFFSET + i, 1);
			curSig++;
		}

		if (curSig == numSig)
			break;
	}

	// Signal if the absolute coefficient is greater than 1
	for (u8 i = 0; i < numSig; i++)
	{
		s16 coeffAbs = coeffVal[i] < 0 ? -coeffVal[i] : coeffVal[i];

		if (coeffAbs > 1)
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_1, 1);
		}
		else
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_1, 0);
			EncodeBypass((u8)(coeffVal[i] < 0));
			coeffVal[i] = 0;
		}
	}

	// Signal if the absolute coefficient is greater than 2
	for (u8 i = 0; i < numSig; i++)
	{
		s16 coeffAbs = coeffVal[i] < 0 ? -coeffVal[i] : coeffVal[i];

		if (coeffAbs > 2)
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_2, 1);
			coeffVal[i] = coeffVal[i] < 0 ? coeffVal[i] + 2 : coeffVal[i] - 2;
		}
		else
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_2, 0);
			EncodeBypass((u8)(coeffVal[i] < 0));
			coeffVal[i] = 0;
		}
	}

	// Signal the remaining coefficient level using Exp-Golomb coding
	for (u8 i = 0; i < numSig; i++)
	{
		s16 coeffAbs = coeffVal[i] < 0 ? -coeffVal[i] : coeffVal[i];

		if (coeffAbs > 0)
		{
			// Count the number of bits
			u8 msb = 15;
			while ((coeffAbs >> msb) == 0)
				msb--;

			for (u8 j = 0; j < msb; j++)
				EncodeBypass(0);

			for (s8 j = msb; j >= 0; j--)
				EncodeBypass((coeffAbs >> j) & 1);

			EncodeBypass((u8)(coeffVal[i] < 0));
		}
	}
}