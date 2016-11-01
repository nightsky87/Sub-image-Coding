#ifndef SIC_COM_QUANT_H
#define SIC_COM_QUANT_H

#include "ComDef.h"

void quantConst(cpStruct *cp, u16 qp);
void dequantConst(cpStruct *cp, u16 qp);

s16 coeffCast(double val);

#endif
