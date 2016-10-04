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
	unsigned char q1;
	unsigned char q2;
};

typedef struct cuStruct
{
	unsigned char *pLuma;
	unsigned char *pChroma1;
	unsigned char *pChroma2;
};

#endif