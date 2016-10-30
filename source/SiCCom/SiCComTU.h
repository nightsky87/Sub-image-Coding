#ifndef SIC_COM_TU_H
#define SIC_COM_TU_H

#include "ComDef.h"
#include <stdlib.h>

void tuForward(stuStruct &stu, ChromaSub chromaSub);
void tuForward(rtuStruct &rtu, ChromaSub chromaSub);
void tuForward(s16 *tb, u8 width, u8 height, u8 size);

void tuInverse(stuStruct &stu, ChromaSub chromaSub);
void tuInverse(rtuStruct &rtu, ChromaSub chromaSub);
void tuInverse(s16 *tb, u8 width, u8 height, u8 size);

s16 coeffCast(s32 val);
s16 pixelCast(s32 val);
s16 residualCast(s32 val);

#endif
