#ifndef COMDEF_H
#define COMDEF_H

#define CU_SIZE 64

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef signed char		s8;
typedef signed short	s16;
typedef signed long		s32;

enum component
{
	COMPONENT_LUMA,
	COMPONENT_CHROMA
};

enum scanDir
{
	SCAN_VERT,
	SCAN_HORZ,
	SCAN_DIAG
};

typedef struct
{
	u16 q1;
	u16 q2;
	bool isGray;
	bool chromaSubsample;
} paramStruct;

typedef struct
{
	s16 *cbLuma;
	s16 *cbChroma1;
	s16 *cbChroma2;
} cuStruct;

typedef struct
{
	s16 *scbLuma;
	s16 *scbChroma1;
	s16 *scbChroma2;
} scuStruct;

typedef struct 
{
	scuStruct *vscu;
	scuStruct *hscu;
} stuStruct;

typedef struct 
{
	cuStruct *cu;
	u8 *modeLuma;
	u8 *modeChroma;
	scanDir *scanLuma;
	scanDir *scanChroma;
} puStruct;

typedef struct 
{
	s16 *rtbLuma;
	s16 *rtbChroma1;
	s16 *rtbChroma2;
	scanDir *scanLuma;
	scanDir *scanChroma;
} rtuStruct;

#endif