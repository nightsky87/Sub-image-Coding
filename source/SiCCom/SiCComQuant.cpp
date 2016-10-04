#include "SiCComQuant.h"

void scuQuantConst(cuStruct cu, u8 qp)
{
	const u16 scbNumPix = CU_SIZE * CU_SIZE / 8;

	// Quantize all coefficients with the same factor
	for (u16 i = 0; i < scbNumPix / 4; i++)
	{
		cu.pLuma[i] = (s16)((float)cu.pLuma[i] / qp + 0.5);
		cu.pChroma1[i] = (s16)((float)cu.pChroma1[i] / qp + 0.5);
		cu.pChroma2[i] = (s16)((float)cu.pChroma2[i] / qp + 0.5);
	}
	for (u16 i = scbNumPix / 4; i < scbNumPix; i++)
	{
		cu.pLuma[i] = (s16)((float)cu.pLuma[i] / qp + 0.5);
	}
}

void scuDequantConst(cuStruct cu, u8 qp)
{
	const u16 scbNumPix = CU_SIZE * CU_SIZE / 8;

	// Quantize all coefficients with the same factor
	for (u16 i = 0; i < scbNumPix / 4; i++)
	{
		cu.pLuma[i] = (s16)((float)cu.pLuma[i] * qp + 0.5);
		cu.pChroma1[i] = (s16)((float)cu.pChroma1[i] * qp + 0.5);
		cu.pChroma2[i] = (s16)((float)cu.pChroma2[i] * qp + 0.5);
	}
	for (u16 i = scbNumPix / 4; i < scbNumPix; i++)
	{
		cu.pLuma[i] = (s16)((float)cu.pLuma[i] * qp + 0.5);
	}
}