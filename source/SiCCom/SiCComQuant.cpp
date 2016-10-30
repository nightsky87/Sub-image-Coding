#include "SiCComQuant.h"

void quantConst(stuStruct &stu, u16 qp)
{
	// Quantize all coefficients of the STBs with the same factor
	for (u8 y = 0; y < stu.hscu->height; y++)
	{
		for (u8 x = 0; x < stu.hscu->width; x++)
		{
			stu.hscu->scbLuma[stu.hscu->stride * y + x] = (s16)((float)stu.hscu->scbLuma[stu.hscu->stride * y + x] / qp + 0.5);
			stu.hscu->scbChroma1[stu.hscu->stride * y + x] = (s16)((float)stu.hscu->scbChroma1[stu.hscu->stride * y + x] / qp + 0.5);
			stu.hscu->scbChroma2[stu.hscu->stride * y + x] = (s16)((float)stu.hscu->scbChroma2[stu.hscu->stride * y + x] / qp + 0.5);
		}
	}
	for (u8 y = 0; y < stu.vscu->height; y++)
	{
		for (u8 x = 0; x < stu.vscu->width; x++)
		{
			stu.vscu->scbLuma[stu.vscu->stride * y + x] = (s16)((float)stu.vscu->scbLuma[stu.vscu->stride * y + x] / qp + 0.5);
			stu.vscu->scbChroma1[stu.vscu->stride * y + x] = (s16)((float)stu.vscu->scbChroma1[stu.vscu->stride * y + x] / qp + 0.5);
			stu.vscu->scbChroma2[stu.vscu->stride * y + x] = (s16)((float)stu.vscu->scbChroma2[stu.vscu->stride * y + x] / qp + 0.5);
		}
	}
}

void quantConst(rtuStruct &rtu, u16 qp)
{
	// Quantize all coefficients of the RTBs with the same factor
	for (u8 y = 0; y < rtu.height; y++)
	{
#if !USE_8x8_RTB
		if (y % 8 == 7)
			continue;
#endif
		for (u8 x = 0; x < rtu.width; x++)
		{
			rtu.rtbLuma[rtu.stride * y + x] = coeffCast((float)rtu.rtbLuma[rtu.stride * y + x] / qp + 0.5);
			rtu.rtbChroma1[rtu.stride * y + x] = coeffCast((float)rtu.rtbChroma1[rtu.stride * y + x] / qp + 0.5);
			rtu.rtbChroma2[rtu.stride * y + x] = coeffCast((float)rtu.rtbChroma2[rtu.stride * y + x] / qp + 0.5);

#if !USE_8x8_RTB
			if (x % 8 == 7)
				continue;
#endif
		}
	}
}

void dequantConst(stuStruct &stu, u16 qp)
{
	// Dequantize all coefficients of the STBs with the same factor
	for (u8 y = 0; y < stu.hscu->height; y++)
	{
		for (u8 x = 0; x < stu.hscu->width; x++)
		{
			stu.hscu->scbLuma[stu.hscu->stride * y + x] = (s16)((float)stu.hscu->scbLuma[stu.hscu->stride * y + x] * qp + 0.5);
			stu.hscu->scbChroma1[stu.hscu->stride * y + x] = (s16)((float)stu.hscu->scbChroma1[stu.hscu->stride * y + x] * qp + 0.5);
			stu.hscu->scbChroma2[stu.hscu->stride * y + x] = (s16)((float)stu.hscu->scbChroma2[stu.hscu->stride * y + x] * qp + 0.5);
		}
	}
	for (u8 y = 0; y < stu.vscu->height; y++)
	{
		for (u8 x = 0; x < stu.vscu->width; x++)
		{
			stu.vscu->scbLuma[stu.vscu->stride * y + x] = (s16)((float)stu.vscu->scbLuma[stu.vscu->stride * y + x] * qp + 0.5);
			stu.vscu->scbChroma1[stu.vscu->stride * y + x] = (s16)((float)stu.vscu->scbChroma1[stu.vscu->stride * y + x] * qp + 0.5);
			stu.vscu->scbChroma2[stu.vscu->stride * y + x] = (s16)((float)stu.vscu->scbChroma2[stu.vscu->stride * y + x] * qp + 0.5);
		}
	}
}


void dequantConst(rtuStruct &rtu, u16 qp)
{
	// Dequantize all coefficients of the RTBs with the same factor
	for (u8 y = 0; y < rtu.height; y++)
	{
#if !USE_8x8_RTB
		if (y % 8 == 7)
			continue;
#endif
		for (u8 x = 0; x < rtu.width; x++)
		{
			rtu.rtbLuma[rtu.stride * y + x] = coeffCast((float)rtu.rtbLuma[rtu.stride * y + x] * qp + 0.5);
			rtu.rtbChroma1[rtu.stride * y + x] = coeffCast((float)rtu.rtbChroma1[rtu.stride * y + x] * qp + 0.5);
			rtu.rtbChroma2[rtu.stride * y + x] = coeffCast((float)rtu.rtbChroma2[rtu.stride * y + x] * qp + 0.5);

#if !USE_8x8_RTB
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
