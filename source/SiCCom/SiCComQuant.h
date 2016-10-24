#ifndef SIC_COM_QUANT_H
#define SIC_COM_QUANT_H

#include "ComDef.h"

void stuQuantConst(stuStruct stu, u16 qp);
void stuDequantConst(stuStruct stu, u16 qp);
void rtuQuantConst(rtuStruct rtu, u16 qp);
void rtuDequantConst(rtuStruct rtu, u16 qp);

s16 coeffCast(float val);

#endif
