#ifndef COMDEF_H
#define COMDEF_H

#define CU_SIZE 64
#define USE_8x8_RTB 1

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef signed char		s8;
typedef signed short	s16;
typedef signed long		s32;

enum Component
{
	COMPONENT_LUMA,
	COMPONENT_CHROMA
};

enum ChromaSub
{
	CHROMA_444,
	CHROMA_420,
	CHROMA_400
};

enum ScanDir
{
	SCAN_VERT,
	SCAN_HORZ,
	SCAN_DIAG
};

enum PredType
{
	TYPE_UNI,
	TYPE_LINEAR,
	TYPE_BILINEAR
};

struct paramStruct
{
	u16 q1;
	u16 q2;
	ChromaSub chromaSub;
};

struct cuStruct
{
	s16 *cbLuma;
	s16 *cbChroma1;
	s16 *cbChroma2;

	u8 width;
	u8 height;
	u8 stride;
	ChromaSub chromaSub;

	cuStruct& operator-(cuStruct &rhs)
	{
		for (u16 i = 0; i < this->width * this->height; i++)
		{
			this->cbLuma[i] -= rhs.cbLuma[i];
			this->cbChroma1[i] -= rhs.cbChroma1[i];
			this->cbChroma2[i] -= rhs.cbChroma2[i];
		}

		return *this;
	}

	cuStruct& operator+(cuStruct &rhs)
	{
		for (u16 i = 0; i < this->width * this->height; i++)
		{
			this->cbLuma[i] += rhs.cbLuma[i];
			this->cbChroma1[i] += rhs.cbChroma1[i];
			this->cbChroma2[i] += rhs.cbChroma2[i];
		}

		return *this;
	}
};

struct scuStruct
{
	s16 *scbLuma;
	s16 *scbChroma1;
	s16 *scbChroma2;

	u8 width;
	u8 height;
	u8 stride;
	ChromaSub chromaSub;
};

struct stuStruct
{
	scuStruct *vscu;
	scuStruct *hscu;

	u8 width;
	u8 height;
	u8 stride;
	ChromaSub chromaSub;
};

struct puStruct
{
	cuStruct *cu;
	u8 *modeLuma;
	u8 *modeChroma;
	ScanDir *scanLuma;
	ScanDir *scanChroma;

	u8 width;
	u8 height;
	u8 stride;
	ChromaSub chromaSub;
};

struct rtuStruct
{
	s16 *rtbLuma;
	s16 *rtbChroma1;
	s16 *rtbChroma2;
	ScanDir *scanLuma;
	ScanDir *scanChroma;

	u8 width;
	u8 height;
	u8 stride;
	ChromaSub chromaSub;
};

#endif