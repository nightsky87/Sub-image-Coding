#ifndef SIC_COM_TU_H
#define SIC_COM_TU_H

#include "ComDef.h"
#include <stdlib.h>

#if !USE_8x8_RTB
#define FORWARD_TRANSFORM_FUNTION dct7
#define INVERSE_TRANSFORM_FUNTION idct7
#else
#define FORWARD_TRANSFORM_FUNTION dct8
#define INVERSE_TRANSFORM_FUNTION idct8
#endif

void tuForward(stuStruct &stu);
void tuForward(rtuStruct &rtu);

void tuInverse(stuStruct &stu);
void tuInverse(rtuStruct &rtu);

void dct4(s16 *tb, u8 width, u8 height, u8 stride);
void dct7(s16 *tb, u8 width, u8 height, u8 stride);
void dct8(s16 *tb, u8 width, u8 height, u8 stride);

void idct4(s16 *tb, u8 width, u8 height, u8 stride);
void idct7(s16 *tb, u8 width, u8 height, u8 stride);
void idct8(s16 *tb, u8 width, u8 height, u8 stride);

s16 coeffCast(s32 val);
s16 pixelCast(s32 val);
s16 residualCast(s32 val);

#endif
