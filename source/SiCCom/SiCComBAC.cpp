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

	// Determine the index of the last significant coefficient in the STB
	s8 lastSig = 15;
	while (stbOrd[lastSig] == 0 && lastSig >= 0)
		lastSig--;

	// Bypass the block coding if no significant coefficients are found
	if (lastSig < 0)
	{
		EncodeDecision(ctxBase + CTX_STB_CODE_BLOCK_OFFSET, 0);
		return;
	}
	EncodeDecision(ctxBase + CTX_STB_CODE_BLOCK_OFFSET, 1);

	// Signal the the position of the last significant coefficient using TU binarization
	for (u8 i = 0; i < lastSig / 4; i++)
	{
		EncodeDecision(ctxBase + CTX_STB_LAST_SIG_COARSE_OFFSET, 1);
	}
	EncodeDecision(ctxBase + CTX_STB_LAST_SIG_COARSE_OFFSET, 0);
	for (u8 i = 0; i < lastSig % 4; i++)
	{
		EncodeDecision(ctxBase + CTX_STB_LAST_SIG_FINE_OFFSET, 1);
	}
	EncodeDecision(ctxBase + CTX_STB_LAST_SIG_FINE_OFFSET, 0);

	// Signal the significance map
	u8 numSig = 0;
	s16 coeffVal[16];
	for (u8 i = 0; i <= lastSig; i++)
	{
		if (stbOrd[i] == 0)
		{
			EncodeDecision(ctxBase + CTX_STB_SIG_FLAG_OFFSET + i, 0);
		}
		else
		{
			EncodeDecision(ctxBase + CTX_STB_SIG_FLAG_OFFSET + i, 1);
			coeffVal[numSig] = stbOrd[i];
			numSig++;
		}
	}

	// Signal if the absolute coefficient is greater than 1
	for (u8 i = 0; i < numSig; i++)
	{
		s16 coeffAbs = coeffVal[i] < 0 ? -coeffVal[i] : coeffVal[i];

		if (coeffAbs > 1)
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_1_OFFSET, 1);
		}
		else
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_1_OFFSET, 0);
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
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_2_OFFSET, 1);
			coeffVal[i] = coeffVal[i] < 0 ? coeffVal[i] + 2 : coeffVal[i] - 2;
		}
		else if (coeffAbs == 2)
		{
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_2_OFFSET, 0);
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
				EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_LEVEL_OFFSET, 1);
			EncodeDecision(ctxBase + CTX_STB_ABS_COEFF_LEVEL_OFFSET, 0);

			for (s8 j = msb - 1; j >= 0; j--)
				EncodeBypass((coeffAbs >> j) & 1);

			EncodeBypass((u8)(coeffVal[i] < 0));
		}
	}
}

void puEnc(puStruct pu)
{
	puEncLuma(pu);
	puEncChroma(pu);
}

void puEncLuma(puStruct pu)
{
	// Encode the top-left PB
	if (pu.modeLuma[0] == 0)
	{
		EncodeDecision(CTX_PB_LUMA_MODE_DC, 1);
	}
	else
	{
		EncodeDecision(CTX_PB_LUMA_MODE_DC, 0);

		puEncDir(pu.modeLuma[0]);
		puEncType(pu.modeLuma[0]);
	}

	// Encode the top-row PBs
	for (u8 x = 1; x < CU_SIZE / 8; x++)
	{
		if (pu.modeLuma[x] == 0)
		{
			EncodeDecision(CTX_PB_LUMA_MODE_DC, 1);
			continue;
		}
		EncodeDecision(CTX_PB_LUMA_MODE_DC, 0);

		if (pu.modeLuma[x - 1] != 0)
		{
			u8 dir = (pu.modeLuma[x] <= 16) ? (pu.modeLuma[x] - 1) : (pu.modeLuma[x] <= 24 ? (pu.modeLuma[x] - 17) : (pu.modeLuma[x] - 25));
			u8 dirSrc = (pu.modeLuma[x - 1] <= 16) ? (pu.modeLuma[x - 1] - 1) : (pu.modeLuma[x - 1] <= 24 ? (pu.modeLuma[x - 1] - 17) : (pu.modeLuma[x - 1] - 25));

			if (pu.modeLuma[x - 1] == pu.modeLuma[x])
			{
				EncodeDecision(CTX_PB_LUMA_COPY_MODE, 1);
			}
			else if (dirSrc == dir)
			{
				EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
				EncodeDecision(CTX_PB_LUMA_COPY_DIR, 1);
				puEncType(pu.modeLuma[x]);
			}
			else
			{
				EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
				EncodeDecision(CTX_PB_LUMA_COPY_DIR, 0);
				puEncDir(pu.modeLuma[x]);
				puEncType(pu.modeLuma[x]);
			}
		}
		else
		{
			puEncDir(pu.modeLuma[x]);
			puEncType(pu.modeLuma[x]);
		}
	}

	// Encode the remaining rows of PBs
	for (u8 y = 1; y < CU_SIZE / 8; y++)
	{
		// Encode the leftmost PB of each row
		if (pu.modeLuma[CU_SIZE / 8 * y] == 0)
		{
			EncodeDecision(CTX_PB_LUMA_MODE_DC, 1);
		}
		else
		{
			EncodeDecision(CTX_PB_LUMA_MODE_DC, 0);

			if (pu.modeLuma[CU_SIZE / 8 * (y - 1)] != 0)
			{
				u8 dir = (pu.modeLuma[CU_SIZE / 8 * y] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * y] - 1) : (pu.modeLuma[CU_SIZE / 8 * y] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * y] - 17) : (pu.modeLuma[CU_SIZE / 8 * y] - 25));
				u8 dirSrc = (pu.modeLuma[CU_SIZE / 8 * (y - 1)] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * (y - 1)] - 1) : (pu.modeLuma[CU_SIZE / 8 * (y - 1)] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * (y - 1)] - 17) : (pu.modeLuma[CU_SIZE / 8 * (y - 1)] - 25));

				if (pu.modeLuma[CU_SIZE / 8 * y] == pu.modeLuma[CU_SIZE / 8 * (y - 1)])
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 1);
				}
				else if (dir == dirSrc)
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 1);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y]);
				}
				else
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 0);
					puEncDir(pu.modeLuma[CU_SIZE / 8 * y]);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y]);
				}
			}
			else
			{
				puEncDir(pu.modeLuma[CU_SIZE / 8 * y]);
				puEncType(pu.modeLuma[CU_SIZE / 8 * y]);
			}
		}

		// Encode the remaining PBs of each row
		for (u8 x = 1; x < CU_SIZE / 8; x++)
		{
			if (pu.modeLuma[CU_SIZE / 8 * y + x] == 0)
			{
				EncodeDecision(CTX_PB_LUMA_MODE_DC, 1);
				continue;
			}
			EncodeDecision(CTX_PB_LUMA_MODE_DC, 0);

			u8 dir = (pu.modeLuma[CU_SIZE / 8 * y + x] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * y + x] - 1) : (pu.modeLuma[CU_SIZE / 8 * y + x] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * y + x] - 17) : (pu.modeLuma[CU_SIZE / 8 * y + x] - 25));
			u8 dirSrcLeft = (pu.modeLuma[CU_SIZE / 8 * y + x - 1] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * y + x - 1] - 1) : (pu.modeLuma[CU_SIZE / 8 * y + x - 1] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * y + x - 1] - 17) : (pu.modeLuma[CU_SIZE / 8 * y + x - 1] - 25));
			u8 dirSrcTop = (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] - 1) : (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] - 17) : (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] - 25));

			bool isDCLeft = (pu.modeLuma[CU_SIZE / 8 * y + x - 1] == 0);
			bool isDCTop = (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] == 0);

			if (!isDCLeft && !isDCTop)
			{
				if (pu.modeLuma[CU_SIZE / 8 * y + x] == pu.modeLuma[CU_SIZE / 8 * y + x - 1])
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 1);
					EncodeDecision(CTX_PB_LUMA_COPY_SOURCE, 0);
				}
				else if (pu.modeLuma[CU_SIZE / 8 * y + x] == pu.modeLuma[CU_SIZE / 8 * (y - 1) + x])
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 1);
					EncodeDecision(CTX_PB_LUMA_COPY_SOURCE, 1);
				}
				else if (dir == dirSrcLeft)
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 1);
					EncodeDecision(CTX_PB_LUMA_COPY_SOURCE, 0);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
				else if (dir == dirSrcTop)
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 1);
					EncodeDecision(CTX_PB_LUMA_COPY_SOURCE, 1);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
				else
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 0);
					puEncDir(pu.modeLuma[CU_SIZE / 8 * y + x]);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
			}
			else if (!isDCLeft && isDCTop)
			{
				if (pu.modeLuma[CU_SIZE / 8 * y + x] == pu.modeLuma[CU_SIZE / 8 * y + x - 1])
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 1);
				}
				else if (dir == dirSrcLeft)
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 1);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
				else
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 0);
					puEncDir(pu.modeLuma[CU_SIZE / 8 * y + x]);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
			}
			else if (isDCLeft && !isDCTop)
			{
				if (pu.modeLuma[CU_SIZE / 8 * y + x] == pu.modeLuma[CU_SIZE / 8 * (y - 1) + x])
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 1);
				}
				else if (dir == dirSrcTop)
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 1);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
				else
				{
					EncodeDecision(CTX_PB_LUMA_COPY_MODE, 0);
					EncodeDecision(CTX_PB_LUMA_COPY_DIR, 0);
					puEncDir(pu.modeLuma[CU_SIZE / 8 * y + x]);
					puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
				}
			}
			else
			{
				puEncDir(pu.modeLuma[CU_SIZE / 8 * y + x]);
				puEncType(pu.modeLuma[CU_SIZE / 8 * y + x]);
			}
		}
	}
}

void puEncChroma(puStruct pu)
{
	// Determine the number of chroma PBs in the CU
	const u16 numChromaPB = CU_SIZE * CU_SIZE / 256;

	// Process each of the chroma modes
	for (u8 i = 0; i < numChromaPB; i++)
	{
		EncodeDecision(CTX_PB_CHROMA_SOURCE_MSB, (pu.modeChroma[i] >> 1) & 1);
		EncodeDecision(CTX_PB_CHROMA_SOURCE_LSB, pu.modeChroma[i] & 1);
	}
}

void puEncDir(u8 mode)
{
	u8 dir = (mode <= 16) ? (mode - 1) : (mode <= 24 ? (mode - 17) : (mode - 25));

	if (dir < 4)
	{
		// Directions 0 to 3 are used by UPM, LPM, and BPM
		EncodeBypass(0);
		EncodeBypass((dir >> 1) & 1);
		EncodeBypass(dir & 1);
	}
	else if (dir < 8)
	{
		// Directions 4 to 7 are used by UPM and LPM
		EncodeBypass(1);
		EncodeBypass(0);
		EncodeBypass((dir >> 1) & 1);
		EncodeBypass(dir & 1);
	}
	else
	{
		// Directions 8 to 15 are used only by UPM
		EncodeBypass(1);
		EncodeBypass(1);
		EncodeBypass((dir >> 2) & 1);
		EncodeBypass((dir >> 1) & 1);
		EncodeBypass(dir & 1);
	}
}

void puEncType(u8 mode)
{
	if (mode <= 16)
	{
		EncodeBypass(0);
	}
	else if (mode <= 24)
	{
		EncodeBypass(1);
		EncodeBypass(0);
	}
	else
	{
		EncodeBypass(1);
		EncodeBypass(1);
	}
}

void rtuEnc(rtuStruct rtu)
{
	// Process each luma residual transform block (RTB)
	for (u8 y = 0; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x += 8)
		{
			rtbEnc(&rtu.rtbLuma[CU_SIZE * y + x], COMPONENT_LUMA, rtu.scanLuma[CU_SIZE / 8 * (y / 8) + x / 8]);
		}
	}

	// Process each chroma residual transform block (RTB)
	for (u8 y = 0; y < CU_SIZE / 2; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 8)
		{
			rtbEnc(&rtu.rtbChroma1[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, rtu.scanChroma[CU_SIZE / 16 * (y / 8) + x / 8]);
			rtbEnc(&rtu.rtbChroma2[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, rtu.scanChroma[CU_SIZE / 16 * (y / 8) + x / 8]);
		}
	}
}

void rtbEnc(s16 *rtb, component comp, scanDir dir)
{
	// Define the context offsets
	const u8 stride = (comp == COMPONENT_LUMA) ? CU_SIZE : (CU_SIZE / 2);
	const u8 ctxBase = (comp == COMPONENT_LUMA) ? CTX_RTB_LUMA_BASE : CTX_RTB_CHROMA_BASE;

	// Create an ordered copy of the STB
	static s16 rtbOrd[49];
	if (dir == SCAN_HORZ)
	{
		for (u8 y = 0; y < 7; y++)
		{
			memcpy(&rtbOrd[7 * y], &rtb[stride * y], 7 * sizeof(s16));
		}
	}
	else
	//else if (dir == SCAN_VERT)
	{
		for (u8 x = 0; x < 7; x++)
		{
			for (u8 y = 0; y < 7; y++)
			{
				rtbOrd[7 * x + y] = rtb[stride * y + x];
			}
		}
	}
	//else
	//{
	//	u8 ind = 0;
	//	for (u8 i = 0; i < 7; i++)
	//	{
	//		u8 x = 0;
	//		for (s8 y = i; y >= 0; y--)
	//		{
	//			rtbOrd[ind] = rtb[stride * y + x];
	//			x++;
	//			ind++;
	//		}
	//	}
	//	for (u8 i = 1; i < 7; i++)
	//	{
	//		u8 y = 6;
	//		for (u8 x = i; x < 7; x++)
	//		{
	//			rtbOrd[ind] = rtb[stride * y + x];
	//			y--;
	//			ind++;
	//		}
	//	}
	//}

	// Determine the index of the last significant coefficient in the STB
	s8 lastSig = 48;
	while (rtbOrd[lastSig] == 0 && lastSig >= 0)
		lastSig--;

	// Bypass the block coding if no significant coefficients are found
	if (lastSig < 0)
	{
		EncodeDecision(ctxBase + CTX_RTB_CODE_BLOCK_OFFSET, 0);
		return;
	}
	EncodeDecision(ctxBase + CTX_RTB_CODE_BLOCK_OFFSET, 1);

	// Signal the the position of the last significant coefficient using TU binarization
	for (u8 i = 0; i < lastSig / 4; i++)
	{
		EncodeDecision(ctxBase + CTX_RTB_LAST_SIG_COARSE_OFFSET, 1);
	}
	EncodeDecision(ctxBase + CTX_RTB_LAST_SIG_COARSE_OFFSET, 0);
	for (u8 i = 0; i < lastSig % 4; i++)
	{
		EncodeDecision(ctxBase + CTX_RTB_LAST_SIG_FINE_OFFSET, 1);
	}
	EncodeDecision(ctxBase + CTX_RTB_LAST_SIG_FINE_OFFSET, 0);

	// Signal the significance map
	u8 numSig = 0;
	s16 coeffVal[49];
	for (u8 i = 0; i <= lastSig; i++)
	{
		if (rtbOrd[i] == 0)
		{
			EncodeDecision(ctxBase + CTX_RTB_SIG_FLAG_OFFSET + i, 0);
		}
		else
		{
			EncodeDecision(ctxBase + CTX_RTB_SIG_FLAG_OFFSET + i, 1);
			coeffVal[numSig] = rtbOrd[i];
			numSig++;
		}
	}

	// Signal if the absolute coefficient is greater than 1
	for (u8 i = 0; i < numSig; i++)
	{
		s16 coeffAbs = coeffVal[i] < 0 ? -coeffVal[i] : coeffVal[i];

		if (coeffAbs > 1)
		{
			EncodeDecision(ctxBase + CTX_RTB_ABS_COEFF_GREATER_1_OFFSET, 1);
		}
		else
		{
			EncodeDecision(ctxBase + CTX_RTB_ABS_COEFF_GREATER_1_OFFSET, 0);
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
			EncodeDecision(ctxBase + CTX_RTB_ABS_COEFF_GREATER_2_OFFSET, 1);
			coeffVal[i] = coeffVal[i] < 0 ? coeffVal[i] + 2 : coeffVal[i] - 2;
		}
		else if (coeffAbs == 2)
		{
			EncodeDecision(ctxBase + CTX_RTB_ABS_COEFF_GREATER_2_OFFSET, 0);
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
				EncodeDecision(ctxBase + CTX_RTB_ABS_COEFF_LEVEL_OFFSET, 1);
			EncodeDecision(ctxBase + CTX_RTB_ABS_COEFF_LEVEL_OFFSET, 0);

			for (s8 j = msb - 1; j >= 0; j--)
				EncodeBypass((coeffAbs >> j) & 1);

			EncodeBypass((u8)(coeffVal[i] < 0));
		}
	}
}

void stuDec(stuStruct stu)
{
	vstbDec(stu.vscu);
	hstbDec(stu.hscu);
}

void vstbDec(scuStruct *scu)
{
	// Process the top row of luma STBs
	stbDec(&scu->scbLuma[0], COMPONENT_LUMA, SCAN_VERT);
	for (u8 x = 4; x < CU_SIZE; x += 4)
	{
		stbDec(&scu->scbLuma[x], COMPONENT_LUMA, SCAN_VERT);
		scu->scbLuma[x] += scu->scbLuma[x - 4];
	}

	// Process the remaining rows of luma STBs
	for (u8 y = 4; y < CU_SIZE / 8; y += 4)
	{
		// Process the leftmost luma STB
		stbDec(&scu->scbLuma[CU_SIZE * y], COMPONENT_LUMA, SCAN_VERT);
		scu->scbLuma[CU_SIZE * y] += scu->scbLuma[CU_SIZE * (y - 4)];

		// Process the remaining luma STBs
		for (u8 x = 4; x < CU_SIZE; x += 4)
		{
			stbDec(&scu->scbLuma[CU_SIZE * y + x], COMPONENT_LUMA, SCAN_VERT);
			scu->scbLuma[CU_SIZE * y + x] += scu->scbLuma[CU_SIZE * y + x - 4];
		}
	}

	// Process the top row of chroma STBs
	stbDec(&scu->scbChroma1[0], COMPONENT_CHROMA, SCAN_VERT);
	stbDec(&scu->scbChroma2[0], COMPONENT_CHROMA, SCAN_VERT);
	for (u8 x = 4; x < CU_SIZE / 2; x += 4)
	{
		stbDec(&scu->scbChroma1[x], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma1[x] += scu->scbChroma1[x - 4];

		stbDec(&scu->scbChroma2[x], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma2[x] += scu->scbChroma2[x - 4];
	}

#if CU_SIZE > 64
	// Process the remaining rows of the chroma STBs
	for (u8 y = 4; y < CU_SIZE / 16; y += 4)
	{
		// Process the leftmost chroma STB
		stbDec(&scu->scbChroma1[CU_SIZE / 2 * y], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma1[CU_SIZE / 2 * y] += scu->scbChroma1[CU_SIZE / 2 * (y - 4)];

		stbDec(&scu->scbChroma2[CU_SIZE / 2 * y], COMPONENT_CHROMA, SCAN_VERT);
		scu->scbChroma2[CU_SIZE / 2 * y] += scu->scbChroma2[CU_SIZE / 2 * (y - 4)];

		// Process the remaining chroma STBs
		for (u8 x = 4; x < CU_SIZE; x += 4)
		{
			stbDec(&scu->scbChroma1[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, SCAN_VERT);
			scu->scbChroma1[CU_SIZE / 2 * y + x] += scu->scbChroma1[CU_SIZE / 2 * y + x - 4];

			stbDec(&scu->scbChroma2[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, SCAN_VERT);
			scu->scbChroma2[CU_SIZE / 2 * y + x] += scu->scbChroma2[CU_SIZE / 2 * y + x - 4];
		}
	}
#endif
}

void hstbDec(scuStruct *scu)
{
	// Process the left column of luma STBs
	stbDec(&scu->scbLuma[0], COMPONENT_LUMA, SCAN_HORZ);
	for (u8 y = 4; y < CU_SIZE; y += 4)
	{
		stbDec(&scu->scbLuma[CU_SIZE / 8 * y], COMPONENT_LUMA, SCAN_HORZ);
		scu->scbLuma[CU_SIZE / 8 * y] += scu->scbLuma[CU_SIZE / 8 * (y - 4)];
	}

	// Process the remaining columns of luma STBs
	for (u8 x = 4; x < CU_SIZE / 8; x += 4)
	{
		// Process the top luma STB
		stbDec(&scu->scbLuma[x], COMPONENT_LUMA, SCAN_HORZ);
		scu->scbLuma[x] += scu->scbLuma[x - 4];

		// Process the remaining luma STBs
		for (u8 y = 4; y < CU_SIZE; y += 4)
		{
			stbDec(&scu->scbLuma[CU_SIZE / 8 * y + x], COMPONENT_LUMA, SCAN_HORZ);
			scu->scbLuma[CU_SIZE / 8 * y + x] += scu->scbLuma[CU_SIZE / 8 * (y - 4) + x];
		}
	}

	// Process the left column of chroma STBs
	stbDec(&scu->scbChroma1[0], COMPONENT_CHROMA, SCAN_HORZ);
	stbDec(&scu->scbChroma2[0], COMPONENT_CHROMA, SCAN_HORZ);
	for (u8 y = 4; y < CU_SIZE / 2; y += 4)
	{
		stbDec(&scu->scbChroma1[CU_SIZE / 16 * y], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma1[CU_SIZE / 16 * y] += scu->scbChroma1[CU_SIZE / 16 * (y - 4)];

		stbDec(&scu->scbChroma2[CU_SIZE / 16 * y], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma2[CU_SIZE / 16 * y] += scu->scbChroma2[CU_SIZE / 16 * (y - 4)];
	}

#if CU_SIZE > 64
	// Process the remaining columns of the chroma STBs
	for (u8 x = 4; x < CU_SIZE / 16; x += 4)
	{
		// Process the top chroma STB
		stbDec(&scu->scbChroma1[x], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma1[x] += scu->scbChroma1[x - 4];

		stbDec(&scu->scbChroma2[x], COMPONENT_CHROMA, SCAN_HORZ);
		scu->scbChroma2[x] += scu->scbChroma2[x - 4];

		// Process the remaining chroma STBs
		for (u8 y = 4; y < CU_SIZE; y += 4)
		{
			stbDec(&scu->scbChroma1[CU_SIZE / 16 * y + x], COMPONENT_CHROMA, SCAN_HORZ);
			scu->scbChroma1[CU_SIZE / 16 * y + x] += scu->scbChroma1[CU_SIZE / 16 * (y - 4) + x];

			stbDec(&scu->scbChroma2[CU_SIZE / 16 * y + x], COMPONENT_CHROMA, SCAN_HORZ);
			scu->scbChroma2[CU_SIZE / 16 * y + x] += scu->scbChroma2[CU_SIZE / 16 * (y - 4) + x];
		}
	}
#endif
}

void stbDec(s16 *stb, component comp, scanDir dir)
{
	// Define the context offsets
	const u8 dirBase = (dir == SCAN_HORZ) ? CTX_HSTB_BASE : CTX_VSTB_BASE;
	const u8 ctxBase = (comp == COMPONENT_LUMA) ? (dirBase + CTX_STB_LUMA_OFFSET) : (dirBase + CTX_STB_CHROMA_OFFSET);
	const u8 stride = (dir == SCAN_HORZ) ? ((comp == COMPONENT_LUMA) ? (CU_SIZE / 8) : (CU_SIZE / 16)) : ((comp == COMPONENT_LUMA) ? CU_SIZE : (CU_SIZE / 2));

	// Check if the block was coded
	if (!DecodeDecision(ctxBase + CTX_STB_CODE_BLOCK_OFFSET))
		return;

	// Decode the position of the last significant coefficient
	s8 lastSig = 0;
	while (DecodeDecision(ctxBase + CTX_STB_LAST_SIG_COARSE_OFFSET))
		lastSig += 4;

	while (DecodeDecision(ctxBase + CTX_STB_LAST_SIG_FINE_OFFSET))
		lastSig++;

	// Decode the significance map
	u8 numSig = 0;
	s16 sigMap[16];
	memset(sigMap, 0, 16 * sizeof(s16));
	for (u8 i = 0; i <= lastSig; i++)
	{
		sigMap[i] = DecodeDecision(ctxBase + CTX_STB_SIG_FLAG_OFFSET + i);

		if (sigMap[i] == 1)
			numSig++;
	}

	// Check if the absolute coefficient is greater than 1
	s16 coeffVal[16];
	for (u8 i = 0; i < numSig; i++)
	{
		if (!DecodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_1_OFFSET))
		{
			if (!DecodeBypass())
				coeffVal[i] = 1;
			else
				coeffVal[i] = -1;
		}
		else
		{
			coeffVal[i] = 0;
		}
	}

	// Check if the absolute coefficient is greater than 2
	for (u8 i = 0; i < numSig; i++)
	{
		if (coeffVal[i] == 0)
		{
			if (!DecodeDecision(ctxBase + CTX_STB_ABS_COEFF_GREATER_2_OFFSET))
			{
				if (!DecodeBypass())
					coeffVal[i] = 2;
				else
					coeffVal[i] = -2;
			}
		}
	}

	// Decode the remaining coefficient levels using Exp-Golomb coding
	for (u8 i = 0; i < numSig; i++)
	{
		if (coeffVal[i] == 0)
		{
			// Decode the EG0 prefix
			u8 msb = 0;
			while (DecodeDecision(ctxBase + CTX_STB_ABS_COEFF_LEVEL_OFFSET))
				msb++;

			// Decode the absolute coefficient value
			s16 coeffAbs = (1 << msb);
			for (s8 j = msb - 1; j >= 0; j--)
				coeffAbs |= (DecodeBypass() << j);

			if (!DecodeBypass())
				coeffVal[i] = coeffAbs + 2;
			else
				coeffVal[i] = -coeffAbs - 2;
		}
	}

	// Reorder the pixel and write to the STB
	if (dir == SCAN_HORZ)
	{
		u8 ind = 0;
		for (u8 y = 0; y < 4; y++)
		{
			for (u8 x = 0; x < 4; x++)
			{
				if (sigMap[4 * y + x])
				{
					stb[stride * y + x] = coeffVal[ind];
					ind++;
				}
			}
		}
	}
	else
	{
		u8 ind = 0;
		for (u8 x = 0; x < 4; x++)
		{
			for (u8 y = 0; y < 4; y++)
			{
				if (sigMap[4 * x + y])
				{
					stb[stride * y + x] = coeffVal[ind];
					ind++;
				}
			}
		}
	}
}

void puDec(puStruct pu)
{
	puDecLuma(pu);
	puDecChroma(pu);
}

void puDecLuma(puStruct pu)
{
	// Decode the top-left PB
	if (DecodeDecision(CTX_PB_LUMA_MODE_DC))
	{
		pu.modeLuma[0] = 0;
	}
	else
	{
		u8 dir = puDecDir();
		u8 type = puDecType();
		pu.modeLuma[0] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
	}

	// Decode the top-row PBs
	for (u8 x = 1; x < CU_SIZE / 8; x++)
	{
		if (DecodeDecision(CTX_PB_LUMA_MODE_DC))
		{
			pu.modeLuma[x] = 0;
			continue;
		}

		if (pu.modeLuma[x - 1] != 0)
		{
			u8 dirSrc = (pu.modeLuma[x - 1] <= 16) ? (pu.modeLuma[x - 1] - 1) : (pu.modeLuma[x - 1] <= 24 ? (pu.modeLuma[x - 1] - 17) : (pu.modeLuma[x - 1] - 25));

			if (DecodeDecision(CTX_PB_LUMA_COPY_MODE))
			{
				pu.modeLuma[x] = pu.modeLuma[x - 1];
			}
			else if (DecodeDecision(CTX_PB_LUMA_COPY_DIR))
			{
				u8 dir = dirSrc;
				u8 type = puDecType();
				pu.modeLuma[x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
			}
			else
			{
				u8 dir = puDecDir();
				u8 type = puDecType();
				pu.modeLuma[x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
			}
		}
		else
		{
			u8 dir = puDecDir();
			u8 type = puDecType();
			pu.modeLuma[x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
		}
	}

	// Decode the remaining rows of PBs
	for (u8 y = 1; y < CU_SIZE / 8; y++)
	{
		// Decode the leftmost PB of each row
		if (DecodeDecision(CTX_PB_LUMA_MODE_DC))
		{
			pu.modeLuma[CU_SIZE / 8 * y] = 0;
		}
		else
		{
			if (pu.modeLuma[CU_SIZE / 8 * (y - 1)] != 0)
			{

				if (DecodeDecision(CTX_PB_LUMA_COPY_MODE))
				{
					pu.modeLuma[CU_SIZE / 8 * y] = pu.modeLuma[CU_SIZE / 8 * (y - 1)];
				}
				else if (DecodeDecision(CTX_PB_LUMA_COPY_DIR))
				{
					u8 dir = (pu.modeLuma[CU_SIZE / 8 * (y - 1)] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * (y - 1)] - 1) : (pu.modeLuma[CU_SIZE / 8 * (y - 1)] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * (y - 1)] - 17) : (pu.modeLuma[CU_SIZE / 8 * (y - 1)] - 25));
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
				else
				{
					u8 dir = puDecDir();
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
			}
			else
			{
				u8 dir = puDecDir();
				u8 type = puDecType();
				pu.modeLuma[CU_SIZE / 8 * y] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
			}
		}

		// Decode the remaining PBs of each row
		for (u8 x = 1; x < CU_SIZE / 8; x++)
		{
			if (DecodeDecision(CTX_PB_LUMA_MODE_DC))
			{
				pu.modeLuma[CU_SIZE / 8 * y + x] = 0;
				continue;
			}

			u8 dirSrcLeft = (pu.modeLuma[CU_SIZE / 8 * y + x - 1] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * y + x - 1] - 1) : (pu.modeLuma[CU_SIZE / 8 * y + x - 1] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * y + x - 1] - 17) : (pu.modeLuma[CU_SIZE / 8 * y + x - 1] - 25));
			u8 dirSrcTop = (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] <= 16) ? (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] - 1) : (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] <= 24 ? (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] - 17) : (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] - 25));

			bool isDCLeft = (pu.modeLuma[CU_SIZE / 8 * y + x - 1] == 0);
			bool isDCTop = (pu.modeLuma[CU_SIZE / 8 * (y - 1) + x] == 0);

			if (!isDCLeft && !isDCTop)
			{
				if (DecodeDecision(CTX_PB_LUMA_COPY_MODE))
				{
					if (!DecodeDecision(CTX_PB_LUMA_COPY_SOURCE))
						pu.modeLuma[CU_SIZE / 8 * y + x] = pu.modeLuma[CU_SIZE / 8 * y + x - 1];
					else
						pu.modeLuma[CU_SIZE / 8 * y + x] = pu.modeLuma[CU_SIZE / 8 * (y - 1) + x];
				}
				else if (DecodeDecision(CTX_PB_LUMA_COPY_DIR))
				{
					u8 dir;
					if (!DecodeDecision(CTX_PB_LUMA_COPY_SOURCE))
						dir = dirSrcLeft;
					else
						dir = dirSrcTop;

					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
				else
				{
					u8 dir = puDecDir();
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
			}
			else if (!isDCLeft && isDCTop)
			{
				if (DecodeDecision(CTX_PB_LUMA_COPY_MODE))
				{
					pu.modeLuma[CU_SIZE / 8 * y + x] = pu.modeLuma[CU_SIZE / 8 * y + x - 1];
				}
				else if (DecodeDecision(CTX_PB_LUMA_COPY_DIR))
				{
					u8 dir = dirSrcLeft;
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
				else
				{
					u8 dir = puDecDir();
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
			}
			else if (isDCLeft && !isDCTop)
			{
				if (DecodeDecision(CTX_PB_LUMA_COPY_MODE))
				{
					pu.modeLuma[CU_SIZE / 8 * y + x] = pu.modeLuma[CU_SIZE / 8 * (y - 1) + x];
				}
				else if (DecodeDecision(CTX_PB_LUMA_COPY_DIR))
				{
					u8 dir = dirSrcTop;
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
				else
				{
					u8 dir = puDecDir();
					u8 type = puDecType();
					pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
				}
			}
			else
			{
				u8 dir = puDecDir();
				u8 type = puDecType();
				pu.modeLuma[CU_SIZE / 8 * y + x] = (type == 0) ? (dir + 1) : ((type == 1) ? dir + 17 : dir + 25);
			}
		}
	}
}

void puDecChroma(puStruct pu)
{
	// Determine the number of chroma PBs in the CU
	const u16 numChromaPB = CU_SIZE * CU_SIZE / 256;

	// Process each of the chroma modes
	for (u8 i = 0; i < numChromaPB; i++)
	{
		pu.modeChroma[i] = DecodeDecision(CTX_PB_CHROMA_SOURCE_MSB) << 1;
		pu.modeChroma[i] |= DecodeDecision(CTX_PB_CHROMA_SOURCE_LSB);
	}
}

u8 puDecDir()
{
	u8 dir;

	if (!DecodeBypass())
	{
		// Directions 0 to 3
		dir = DecodeBypass() << 1;
		dir |= DecodeBypass() ;
	}
	else if (!DecodeBypass())
	{
		// Directions 4 to 7
		dir = DecodeBypass() << 1;
		dir |= DecodeBypass();
		dir += 4;
	}
	else
	{
		// Directions 8 to 15
		dir = DecodeBypass() << 2;
		dir |= DecodeBypass() << 1;
		dir |= DecodeBypass();
		dir += 8;
	}

	return dir;
}

u8 puDecType()
{
	if (!DecodeBypass())
	{
		return 0;
	}
	else if (!DecodeBypass())
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void rtuDec(rtuStruct rtu)
{
	// Process each luma residual transform block (RTB)
	for (u8 y = 0; y < CU_SIZE; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE; x += 8)
		{
			rtbDec(&rtu.rtbLuma[CU_SIZE * y + x], COMPONENT_LUMA, rtu.scanLuma[CU_SIZE / 8 * (y / 8) + x / 8]);
		}
	}

	// Process each chroma residual transform block (RTB)
	for (u8 y = 0; y < CU_SIZE / 2; y += 8)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x += 8)
		{
			rtbDec(&rtu.rtbChroma1[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, rtu.scanChroma[CU_SIZE / 16 * (y / 8) + x / 8]);
			rtbDec(&rtu.rtbChroma2[CU_SIZE / 2 * y + x], COMPONENT_CHROMA, rtu.scanChroma[CU_SIZE / 16 * (y / 8) + x / 8]);
		}
	}
}

void rtbDec(s16 *rtb, component comp, scanDir dir)
{
	// Define the context offsets
	const u8 stride = (comp == COMPONENT_LUMA) ? CU_SIZE : (CU_SIZE / 2);
	const u8 ctxBase = (comp == COMPONENT_LUMA) ? CTX_RTB_LUMA_BASE : CTX_RTB_CHROMA_BASE;

	// Clear the RTB
	for (u8 y = 0; y < 7; y++)
	{
		memset(&rtb[stride * y], 0, 7 * sizeof(s16));
	}

	// Check if the block was coded
	if (!DecodeDecision(ctxBase + CTX_RTB_CODE_BLOCK_OFFSET))
		return;

	// Decode the position of the last significant coefficient
	s8 lastSig = 0;
	while (DecodeDecision(ctxBase + CTX_RTB_LAST_SIG_COARSE_OFFSET))
		lastSig += 4;

	while (DecodeDecision(ctxBase + CTX_RTB_LAST_SIG_FINE_OFFSET))
		lastSig++;

	// Decode the significance map
	u8 numSig = 0;
	s16 sigMap[49];
	memset(sigMap, 0, 49 * sizeof(s16));
	for (u8 i = 0; i <= lastSig; i++)
	{
		sigMap[i] = DecodeDecision(ctxBase + CTX_RTB_SIG_FLAG_OFFSET + i);

		if (sigMap[i] == 1)
			numSig++;
	}

	// Check if the absolute coefficient is greater than 1
	s16 coeffVal[49];
	for (u8 i = 0; i < numSig; i++)
	{
		if (!DecodeDecision(ctxBase + CTX_RTB_ABS_COEFF_GREATER_1_OFFSET))
		{
			if (!DecodeBypass())
				coeffVal[i] = 1;
			else
				coeffVal[i] = -1;
		}
		else
		{
			coeffVal[i] = 0;
		}
	}

	// Check if the absolute coefficient is greater than 2
	for (u8 i = 0; i < numSig; i++)
	{
		if (coeffVal[i] == 0)
		{
			if (!DecodeDecision(ctxBase + CTX_RTB_ABS_COEFF_GREATER_2_OFFSET))
			{
				if (!DecodeBypass())
					coeffVal[i] = 2;
				else
					coeffVal[i] = -2;
			}
		}
	}

	// Decode the remaining coefficient levels using Exp-Golomb coding
	for (u8 i = 0; i < numSig; i++)
	{
		if (coeffVal[i] == 0)
		{
			// Decode the EG0 prefix
			u8 msb = 0;
			while (DecodeDecision(ctxBase + CTX_RTB_ABS_COEFF_LEVEL_OFFSET))
				msb++;

			// Decode the absolute coefficient value
			s16 coeffAbs = (1 << msb);
			for (s8 j = msb - 1; j >= 0; j--)
				coeffAbs |= (DecodeBypass() << j);

			if (!DecodeBypass())
				coeffVal[i] = coeffAbs + 2;
			else
				coeffVal[i] = -coeffAbs - 2;
		}
	}

	// Reorder the pixel and write to the STB
	if (dir == SCAN_HORZ)
	{
		u8 ind = 0;
		for (u8 y = 0; y < 7; y++)
		{
			for (u8 x = 0; x < 7; x++)
			{
				if (sigMap[7 * y + x])
				{
					rtb[stride * y + x] = coeffVal[ind];
					ind++;
				}
			}
		}
	}
	else
	//else if (dir == SCAN_VERT)
	{
		u8 ind = 0;
		for (u8 x = 0; x < 4; x++)
		{
			for (u8 y = 0; y < 4; y++)
			{
				if (sigMap[7 * x + y])
				{
					rtb[stride * y + x] = coeffVal[ind];
					ind++;
				}
			}
		}
	}
	//else
	//{
	//	u8 ind = 0;
	//	u8 sigInd = 0;
	//	for (u8 i = 0; i < 7; i++)
	//	{
	//		u8 x = 0;
	//		for (s8 y = i; y >= 0; y--)
	//		{
	//			if (sigMap[sigInd])
	//			{
	//				rtb[stride * y + x] = coeffVal[ind];
	//				ind++;
	//			}
	//			sigInd++;
	//			x++;
	//		}
	//	}
	//	for (u8 i = 1; i < 7; i++)
	//	{
	//		u8 y = 6;
	//		for (u8 x = i; x < 7; x++)
	//		{
	//			if (sigMap[sigInd])
	//			{
	//				rtb[stride * y + x] = coeffVal[ind];
	//				ind++;
	//			}
	//			sigInd++;
	//			y--;
	//		}
	//	}
	//}
}