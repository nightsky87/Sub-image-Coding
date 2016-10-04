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
	u8 q1;
	u8 q2;
};

typedef struct cuStruct
{
	s16 *pLuma;
	s16 *pChroma1;
	s16 *pChroma2;
};

#endif