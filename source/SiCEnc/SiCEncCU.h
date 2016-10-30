#ifndef SIC_ENC_CU_H
#define SIC_ENC_CU_H

#include "ComDef.h"
#include "SiCComTU.h"
#include "SiCComQuant.h"
#include "SiCComPred.h"
#include "SiCComBAC.h"
#include <cstring>

void SiCEncCU(s16 *img, u16 width, u16 height, paramStruct param);

void copyToCU(s16 *img, u16 width, u16 height, cuStruct &cu, ChromaSub chromaSub);
void copyFromCU(s16 *img, u16 width, u16 height, cuStruct &cu, ChromaSub chromaSub);
void copyToSCU(cuStruct &cu, scuStruct &hscu, scuStruct &vscu);
void copyFromSCU(cuStruct &cu, scuStruct &hscu, scuStruct &vscu);

#endif