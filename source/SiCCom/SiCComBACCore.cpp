#include "SiCComBACCore.h"

static u8 *pByteCur = NULL;
static u8 *pBitstream = NULL;

static u8 bitPos;
static u8 byteBuffer;
static u8 bitsOutstanding;

static u16 ctx[NUM_TOTAL_CONTEXT];
static u16 mps[NUM_TOTAL_CONTEXT];
static u16 codILow = 0x000;
static u16 codIRange = 0x1FE;

u16 rangeTabLPS(u8 pStateIdx, u8 qCodIRangeIdx)
{
	static const u16 rangeTab[] = { \
		128, 176, 208, 240, 128, 167, 197, 227, 128, 158, 187, 216, 123,\
		150, 178, 205, 116, 142, 169, 195, 111, 135, 160, 185, 105, 128,\
		152, 175, 100, 122, 144, 166, 95, 116, 137, 158, 90, 110, 130,\
		150, 85, 104, 123, 142, 81, 99, 117, 135, 77, 94, 111, 128, 73,\
		89, 105, 122, 69, 85, 100, 116, 66, 80, 95, 110, 62, 76, 90, 104,\
		59, 72, 86, 99, 56, 69, 81, 94, 53, 65, 77, 89, 51, 62, 73, 85,\
		48, 59, 69, 80, 46, 56, 66, 76, 43, 53, 63, 72, 41, 50, 59, 69,\
		39, 48, 56, 65, 37, 45, 54, 62, 35, 43, 51, 59, 33, 41, 48, 56,\
		32, 39, 46, 53, 30, 37, 43, 50, 29, 35, 41, 48, 27, 33, 39, 45,\
		26, 31, 37, 43, 24, 30, 35, 41, 23, 28, 33, 39, 22, 27, 32, 37,\
		21, 26, 30, 35, 20, 24, 29, 33, 19, 23, 27, 31, 18, 22, 26, 30,\
		17, 21, 25, 28, 16, 20, 23, 27, 15, 19, 22, 25, 14, 18, 21, 24,\
		14, 17, 20, 23, 13, 16, 19, 22, 12, 15, 18, 21, 12, 14, 17, 20,\
		11, 14, 16, 19, 11, 13, 15, 18, 10, 12, 15, 17, 10, 12, 14, 16,\
		9, 11, 13, 15, 9, 11, 12, 14, 8, 10, 12, 14, 8, 9, 11, 13, 7, 9,\
		11, 12, 7, 9, 10, 12, 7, 8, 10, 11, 6, 8, 9, 11, 6, 7, 9, 10, 6,\
		7, 8, 9, 2, 2, 2, 2 };

	return rangeTab[(pStateIdx << 2) + qCodIRangeIdx];
}

u8 transIdxLPS(u8 pStateIdx)
{
	static const u8 transIdx[] = { \
		0, 0, 1, 2, 2, 4, 4, 5, 6, 7, 8, 9, 9, 11, 11, 12,\
		13, 13, 15, 15, 16, 16, 18, 18, 19, 19, 21, 21, 22, 22, 23, 24,\
		24, 25, 26, 26, 27, 27, 28, 29, 29, 30, 30, 30, 31, 32, 32, 33,\
		33, 33, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 63 };

	return transIdx[pStateIdx];
}

void InitializeEncoder(u32 numBytes)
{
	u16 i;

	// Clear out all contexts and most-probable symbols
	memset(ctx, 0, NUM_TOTAL_CONTEXT * sizeof(u16));
	memset(mps, 0, NUM_TOTAL_CONTEXT * sizeof(u16));

	// Initialize the arithmetic encoder
	codILow = 0x000;
	codIRange = 0x1FE;
	bitsOutstanding = 0;

	// Check if the bitstream has previously been allocated
	if (pBitstream != NULL)
		free(pBitstream);

	// Allocate a new bitsream
	pBitstream = (u8 *)malloc(numBytes);
	pByteCur = pBitstream;
}

void EncodeDecision(u8 ctxIdx, u8 binVal)
{
	u8 pStateIdx, qCodIRangeIdx, valMPS, codIRangeLPS;

	valMPS = mps[ctxIdx];
	pStateIdx = ctx[ctxIdx];
	qCodIRangeIdx = (codIRange >> 6) & 3;
	codIRangeLPS = rangeTabLPS(pStateIdx, qCodIRangeIdx);
	codIRange -= codIRangeLPS;

	if (binVal != valMPS)
	{
		codILow += codIRange;
		codIRange = codIRangeLPS;

		if (pStateIdx == 0)
			mps[ctxIdx] = 1 - valMPS;

		ctx[ctxIdx] = transIdxLPS(pStateIdx);
	}
	else
	{
		if (pStateIdx < 62)
			ctx[ctxIdx]++;
	}

	while (codIRange < 0x100)
	{
		if (codILow < 0x100)
		{
			PutBit(0);
		}
		else if (codILow >= 0x200)
		{
			PutBit(1);
			codILow -= 0x200;
		}
		else
		{
			bitsOutstanding++;
			codILow -= 0x100;
		}

		codIRange <<= 1;
		codILow <<= 1;
	}
}

void EncodeBypass(u8 binVal)
{
	codILow <<= 1;

	if (binVal != 0)
		codILow += codIRange;

	if (codILow >= 0x400)
	{
		PutBit(1);
		codILow -= 0x400;
	}
	else if (codILow < 0x200)
	{
		PutBit(0);
	}
	else
	{
		bitsOutstanding++;
		codILow -= 0x200;
	}
}

void EncodeTerminate()
{
	codIRange -= 2;
	codILow += codIRange;
	codIRange = 2;

	while (codIRange < 0x100)
	{
		if (codILow < 0x100)
		{
			PutBit(0);
		}
		else if (codILow >= 0x200)
		{
			PutBit(1);
			codILow -= 0x200;
		}
		else
		{
			bitsOutstanding++;
			codILow -= 0x100;
		}

		codIRange <<= 1;
		codILow <<= 1;
	}

	PutBit((codILow >> 9) & 1);
	PutBit((((codILow >> 7) & 3 | 1) >> 1) & 1);
	PutBit(((codILow >> 7) & 3 | 1) & 1);
}

//void OpenFileEnc(char* fName, u16 width, u16 height, u8 channels, u8 qp)
//{
//	if (fopen_s(&fh, fName, "wb"))
//		printf("Cannot create output file.\n");
//
//	fwrite(&width, sizeof(u16), 1, fh);
//	fwrite(&height, sizeof(u16), 1, fh);
//	fwrite(&channels, sizeof(u8), 1, fh);
//	fwrite(&qp, sizeof(u8), 1, fh);
//
//	bitPos = 7;
//	byteBuffer = 0;
//
//	InitializeEncoder();
//}
//
//void CloseFileEnc()
//{
//	if (bitPos < 7)
//		fputc(byteBuffer, fh);
//
//	fclose(fh);
//}

void PutBit(u8 B)
{
	byteBuffer |= (B << bitPos);
	if (bitPos == 0)
	{
		*pByteCur = byteBuffer;
		pByteCur++;

		bitPos = 8;
		byteBuffer = 0;
	}
	bitPos--;

	while (bitsOutstanding > 0)
	{
		byteBuffer |= ((1 - B) << bitPos);
		if (bitPos == 0)
		{
			*pByteCur = byteBuffer;
			pByteCur++;

			bitPos = 8;
			byteBuffer = 0;
		}
		bitPos--;
		bitsOutstanding--;
	}
}
