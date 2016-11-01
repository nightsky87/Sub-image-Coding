#ifndef SIC_ENC_CU_H
#define SIC_ENC_CU_H

#include "ComDef.h"
#include "SiCComPred.h"
#include "SiCComTransform.h"
#include "SiCComQuant.h"
//#include "SiCComBAC.h"
#include <cstring>

void SiCEncCU(s16 *img, u16 width, u16 height, paramStruct param);

void generateCP(s16 *img, u16 width, u16 height, cpStruct *cpLargest);
void sliceFilt(cpStruct *cp, u8 preserve);

#endif