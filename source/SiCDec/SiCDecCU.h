#ifndef SIC_DEC_CU_H
#define SIC_DEC_CU_H

#include "ComDef.h"
#include "SiCComTU.h"
#include "SiCComQuant.h"
#include "SiCComPred.h"
#include "SiCComBAC.h"
#include <cstring>

void SiCDecCU(cuStruct cu, u32 stride, paramStruct param);

#endif
