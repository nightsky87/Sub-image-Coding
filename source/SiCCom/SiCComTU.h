#ifndef SIC_COM_TU_H
#define SIC_COM_TU_H

#include "ComDef.h"
#include <stdlib.h>

void stuForward(stuStruct stu);
void stuInverse(stuStruct stu);

void vstuForward(scuStruct *scu);
void vstuInverse(scuStruct *scu);

void hstuForward(scuStruct *scu);
void hstuInverse(scuStruct *scu);

void rtuForward(rtuStruct rtu);
void rtuInverse(rtuStruct rtu);

s16 coeffCast(s32 val);
s16 pixelCast(s32 val);
s16 residualCast(s32 val);

#endif
