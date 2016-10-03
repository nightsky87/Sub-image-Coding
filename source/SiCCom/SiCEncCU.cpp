#include "SiCEncCU.h"

void SiCEncCU(cuStruct cu, u32 width, u32 height, paramStruct param)
{
	const u16 cuNumPix = CU_SIZE * CU_SIZE;

	// Allocate space for the horizontal and vertical sub-images
	static cuStruct scuHorz, scuVert;
	scuHorz.pY = new u8[cuNumPix / 8];
	scuVert.pY = new u8[cuNumPix / 8];
	scuHorz.pY = new u8[cuNumPix / 8];
	cu.pY;
}