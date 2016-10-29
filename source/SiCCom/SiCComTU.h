#ifndef SIC_COM_TU_H
#define SIC_COM_TU_H

#include "ComDef.h"
#include <stdlib.h>

void tuForward(stuStruct *stu, ChromaSub chromaSub);
void tuForward(s16 *stb, u8 width, u8 height);

void tuInverse(stuStruct *stu, ChromaSub chromaSub);
void tuInverse(s16 *stb, u8 width, u8 height);

void rtuForward(rtuStruct rtu);
void rtuInverse(rtuStruct rtu);

s16 coeffCast(s32 val);
s16 pixelCast(s32 val);
s16 residualCast(s32 val);

#endif
