#ifndef COMDEF_H
#define COMDEF_H

#define CU_SIZE 64

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef signed char		s8;
typedef signed short	s16;
typedef signed long		s32;

typedef struct paramStruct
{
	u16 q1;
	u16 q2;
};

typedef struct cuStruct
{
	s16 *cbLuma;
	s16 *cbChroma1;
	s16 *cbChroma2;
};

typedef struct scuStruct
{
	s16 *scbLuma;
	s16 *scbChroma1;
	s16 *scbChroma2;
};

typedef struct stuStruct
{
	scuStruct *vscu;
	scuStruct *hscu;
};

typedef struct puStruct
{
	cuStruct *cu;
	u8 *modeLuma;
	u8 *modeChroma;
};

typedef struct rtuStruct
{
	s16 *rtbLuma;
	s16 *rtbChroma1;
	s16 *rtbChroma2;
};

#endif