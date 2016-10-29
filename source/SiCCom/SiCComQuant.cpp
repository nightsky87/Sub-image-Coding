#include "SiCComQuant.h"

void quantConst(stuStruct *stu, u16 qp)
{
	const u16 scbNumPix = CU_SIZE * CU_SIZE / 8;

	// Quantize all coefficients of the STBs with the same factor
	for (u16 i = 0; i < scbNumPix; i++)
	{
		stu->hscu->scbLuma[i] = (s16)((float)stu->hscu->scbLuma[i] / qp + 0.5);
		stu->hscu->scbChroma1[i] = (s16)((float)stu->hscu->scbChroma1[i] / qp + 0.5);
		stu->hscu->scbChroma2[i] = (s16)((float)stu->hscu->scbChroma2[i] / qp + 0.5);

		stu->vscu->scbLuma[i] = (s16)((float)stu->vscu->scbLuma[i] / qp + 0.5);
		stu->vscu->scbChroma1[i] = (s16)((float)stu->vscu->scbChroma1[i] / qp + 0.5);
		stu->vscu->scbChroma2[i] = (s16)((float)stu->vscu->scbChroma2[i] / qp + 0.5);
	}
}

void quantConst(rtuStruct rtu, u16 qp)
{
	// Quantize all coefficients of the RTBs with the same factor
	for (u8 y = 0; y < CU_SIZE; y++)
	{
#ifndef USE_8x8_RTB
		if (y % 8 == 7)
			continue;
#endif
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = coeffCast((float)rtu.rtbLuma[CU_SIZE * y + x] / qp + 0.5);
			rtu.rtbChroma1[CU_SIZE * y + x] = coeffCast((float)rtu.rtbChroma1[CU_SIZE * y + x] / qp + 0.5);
			rtu.rtbChroma2[CU_SIZE * y + x] = coeffCast((float)rtu.rtbChroma2[CU_SIZE * y + x] / qp + 0.5);

#ifndef USE_8x8_RTB
			if (x % 8 == 7)
				continue;
#endif
		}
	}
}

void dequantConst(stuStruct *stu, u16 qp)
{
	const u16 scbNumPix = CU_SIZE * CU_SIZE / 8;

	// Dequantize all coefficients of the STBs with the same factor
	for (u16 i = 0; i < scbNumPix; i++)
	{
		stu->hscu->scbLuma[i] = coeffCast((float)stu->hscu->scbLuma[i] * qp + 0.5);
		stu->hscu->scbChroma1[i] = coeffCast((float)stu->hscu->scbChroma1[i] * qp + 0.5);
		stu->hscu->scbChroma2[i] = coeffCast((float)stu->hscu->scbChroma2[i] * qp + 0.5);

		stu->vscu->scbLuma[i] = coeffCast((float)stu->vscu->scbLuma[i] * qp + 0.5);
		stu->vscu->scbChroma1[i] = coeffCast((float)stu->vscu->scbChroma1[i] * qp + 0.5);
		stu->vscu->scbChroma2[i] = coeffCast((float)stu->vscu->scbChroma2[i] * qp + 0.5);
	}
}


void dequantConst(rtuStruct rtu, u16 qp)
{
	// Quantize all coefficients of the RTBs with the same factor
	for (u8 y = 0; y < CU_SIZE; y++)
	{
#ifndef USE_8x8_RTB
		if (y % 8 == 7)
			continue;
#endif
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = coeffCast((float)rtu.rtbLuma[CU_SIZE * y + x] * qp + 0.5);
			rtu.rtbChroma1[CU_SIZE * y + x] = coeffCast((float)rtu.rtbChroma1[CU_SIZE * y + x] * qp + 0.5);
			rtu.rtbChroma2[CU_SIZE * y + x] = coeffCast((float)rtu.rtbChroma2[CU_SIZE * y + x] * qp + 0.5);

#ifndef USE_8x8_RTB
			if (x % 8 == 7)
				continue;
#endif
		}
	}
}

s16 coeffCast(float val)
{
	return ((val < -32768) ? -32768 : ((val > 32767) ? 32767 : val));
}
