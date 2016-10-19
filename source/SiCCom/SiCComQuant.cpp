#include "SiCComQuant.h"

void stuQuantConst(stuStruct stu, u16 qp)
{
	const u16 scbNumPix = CU_SIZE * CU_SIZE / 8;

	// Quantize all coefficients of the STBs with the same factor
	for (u16 i = 0; i < scbNumPix / 4; i++)
	{
		stu.hscu->scbLuma[i] = (s16)((float)stu.hscu->scbLuma[i] / qp + 0.5);
		stu.hscu->scbChroma1[i] = (s16)((float)stu.hscu->scbChroma1[i] / qp + 0.5);
		stu.hscu->scbChroma2[i] = (s16)((float)stu.hscu->scbChroma2[i] / qp + 0.5);
		stu.vscu->scbLuma[i] = (s16)((float)stu.vscu->scbLuma[i] / qp + 0.5);
		stu.vscu->scbChroma1[i] = (s16)((float)stu.vscu->scbChroma1[i] / qp + 0.5);
		stu.vscu->scbChroma2[i] = (s16)((float)stu.vscu->scbChroma2[i] / qp + 0.5);
	}
	for (u16 i = scbNumPix / 4; i < scbNumPix; i++)
	{
		stu.hscu->scbLuma[i] = (s16)((float)stu.hscu->scbLuma[i] / qp + 0.5);
		stu.vscu->scbLuma[i] = (s16)((float)stu.vscu->scbLuma[i] / qp + 0.5);
	}
}

void stuDequantConst(stuStruct stu, u16 qp)
{
	const u16 scbNumPix = CU_SIZE * CU_SIZE / 8;

	// Dequantize all coefficients of the STBs with the same factor
	for (u16 i = 0; i < scbNumPix / 4; i++)
	{
		stu.hscu->scbLuma[i] = (s16)((float)stu.hscu->scbLuma[i] * qp + 0.5);
		stu.hscu->scbChroma1[i] = (s16)((float)stu.hscu->scbChroma1[i] * qp + 0.5);
		stu.hscu->scbChroma2[i] = (s16)((float)stu.hscu->scbChroma2[i] * qp + 0.5);
		stu.vscu->scbLuma[i] = (s16)((float)stu.vscu->scbLuma[i] * qp + 0.5);
		stu.vscu->scbChroma1[i] = (s16)((float)stu.vscu->scbChroma1[i] * qp + 0.5);
		stu.vscu->scbChroma2[i] = (s16)((float)stu.vscu->scbChroma2[i] * qp + 0.5);
	}
	for (u16 i = scbNumPix / 4; i < scbNumPix; i++)
	{
		stu.hscu->scbLuma[i] = (s16)((float)stu.hscu->scbLuma[i] * qp + 0.5);
		stu.vscu->scbLuma[i] = (s16)((float)stu.vscu->scbLuma[i] * qp + 0.5);
	}
}

void rtuQuantConst(rtuStruct rtu, u16 qp)
{
	// Quantize all coefficients of the RTBs with the same factor
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = (s16)((float)rtu.rtbLuma[CU_SIZE * y + x] / qp + 0.5);
			rtu.rtbChroma1[CU_SIZE / 2 * y + x] = (s16)((float)rtu.rtbChroma1[CU_SIZE / 2 * y + x] / qp + 0.5);
			rtu.rtbChroma2[CU_SIZE / 2 * y + x] = (s16)((float)rtu.rtbChroma2[CU_SIZE / 2 * y + x] / qp + 0.5);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = (s16)((float)rtu.rtbLuma[CU_SIZE * y + x] / qp + 0.5);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = (s16)((float)rtu.rtbLuma[CU_SIZE * y + x] / qp + 0.5);
		}
	}
}

void rtuDequantConst(rtuStruct rtu, u16 qp)
{
	// Dequantize all coefficients of the RTBs with the same factor
	for (u8 y = 0; y < CU_SIZE / 2; y++)
	{
		for (u8 x = 0; x < CU_SIZE / 2; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = (s16)((float)rtu.rtbLuma[CU_SIZE * y + x] * qp + 0.5);
			rtu.rtbChroma1[CU_SIZE / 2 * y + x] = (s16)((float)rtu.rtbChroma1[CU_SIZE / 2 * y + x] * qp + 0.5);
			rtu.rtbChroma2[CU_SIZE / 2 * y + x] = (s16)((float)rtu.rtbChroma2[CU_SIZE / 2 * y + x] * qp + 0.5);
		}
		for (u8 x = CU_SIZE / 2; x < CU_SIZE; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = (s16)((float)rtu.rtbLuma[CU_SIZE * y + x] * qp + 0.5);
		}
	}
	for (u8 y = CU_SIZE / 2; y < CU_SIZE; y++)
	{
		for (u8 x = 0; x < CU_SIZE; x++)
		{
			rtu.rtbLuma[CU_SIZE * y + x] = (s16)((float)rtu.rtbLuma[CU_SIZE * y + x] * qp + 0.5);
		}
	}
}