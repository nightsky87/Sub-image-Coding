#include "SiCComQuant.h"
#include <cmath>

void quantConst(cpStruct *cp, u16 qp)
{
	// Calculate the scaling factor
	double qStep = pow(2, ((double)qp - 4) / 6);

	// Quantize all coefficients with the same factor
	for (u8 y = 0; y < cp->height; y += 2)
	{
		for (u8 x = 0; x < cp->width; x += 2)
		{
			cp->pLuma[cp->width * y + x + 1] = (s16)round((double)cp->pLuma[cp->width * y + x + 1] / qStep);
			cp->pLuma[cp->width * (y + 1) + x] = (s16)round((double)cp->pLuma[cp->width * (y + 1) + x] / qStep);
			cp->pLuma[cp->width * (y + 1) + x + 1] = (s16)round((double)cp->pLuma[cp->width * (y + 1) + x + 1] / qStep);
		}
	}

	if (cp->chromaSub != CHROMA_400)
	{
		for (u8 y = 0; y < cp->height; y += 2)
		{
			for (u8 x = 0; x < cp->width; x += 2)
			{
				cp->pChroma1[cp->width * y + x + 1] = (s16)round((double)cp->pChroma1[cp->width * y + x + 1] / qStep);
				cp->pChroma1[cp->width * (y + 1) + x] = (s16)round((double)cp->pChroma1[cp->width * (y + 1) + x] / qStep);
				cp->pChroma1[cp->width * (y + 1) + x + 1] = (s16)round((double)cp->pChroma1[cp->width * (y + 1) + x + 1] / qStep);

				cp->pChroma2[cp->width * y + x + 1] = (s16)round((double)cp->pChroma2[cp->width * y + x + 1] / qStep);
				cp->pChroma2[cp->width * (y + 1) + x] = (s16)round((double)cp->pChroma2[cp->width * (y + 1) + x] / qStep);
				cp->pChroma2[cp->width * (y + 1) + x + 1] = (s16)round((double)cp->pChroma2[cp->width * (y + 1) + x + 1] / qStep);
			}
		}
	}
}

void dequantConst(cpStruct *cp, u16 qp)
{
	// Calculate the scaling factor
	double qStep = pow(2, ((double)qp - 4) / 6);

	// Quantize all coefficients with the same factor
	for (u8 y = 0; y < cp->height; y += 2)
	{
		for (u8 x = 0; x < cp->width; x += 2)
		{
			cp->pLuma[cp->width * y + x + 1] = coeffCast((double)cp->pLuma[cp->width * y + x + 1] * qStep);
			cp->pLuma[cp->width * (y + 1) + x] = coeffCast((double)cp->pLuma[cp->width * (y + 1) + x] * qStep);
			cp->pLuma[cp->width * (y + 1) + x + 1] = coeffCast((double)cp->pLuma[cp->width * (y + 1) + x + 1] * qStep);
		}
	}

	if (cp->chromaSub != CHROMA_400)
	{
		for (u8 y = 0; y < cp->height; y += 2)
		{
			for (u8 x = 0; x < cp->width; x += 2)
			{
				cp->pChroma1[cp->width * y + x + 1] = coeffCast((double)cp->pChroma1[cp->width * y + x + 1] * qStep);
				cp->pChroma1[cp->width * (y + 1) + x] = coeffCast((double)cp->pChroma1[cp->width * (y + 1) + x] * qStep);
				cp->pChroma1[cp->width * (y + 1) + x + 1] = coeffCast((double)cp->pChroma1[cp->width * (y + 1) + x + 1] * qStep);

				cp->pChroma2[cp->width * y + x + 1] = coeffCast((double)cp->pChroma2[cp->width * y + x + 1] * qStep + 0.5);
				cp->pChroma2[cp->width * (y + 1) + x] = coeffCast((double)cp->pChroma2[cp->width * (y + 1) + x] * qStep + 0.5);
				cp->pChroma2[cp->width * (y + 1) + x + 1] = coeffCast((double)cp->pChroma2[cp->width * (y + 1) + x + 1] * qStep);
			}
		}
	}
}

s16 coeffCast(double val)
{
	val = round(val);
	return (s16)((val < -32768) ? -32768 : ((val > 32767) ? 32767 : val));
}
