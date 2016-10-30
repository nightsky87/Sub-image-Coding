#ifndef SIC_COM_QUANT_H
#define SIC_COM_QUANT_H

#include "ComDef.h"

void quantConst(stuStruct &stu, u16 qp);
void quantConst(rtuStruct &rtu, u16 qp);

void dequantConst(stuStruct &stu, u16 qp);
void dequantConst(rtuStruct &rtu, u16 qp);

s16 coeffCast(float val);

#endif
