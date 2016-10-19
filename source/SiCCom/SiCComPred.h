#ifndef SIC_COM_PRED_H
#define SIC_COM_PRED_H

#include "ComDef.h"
#include <cstring>

void predSearch(puStruct pu);
void predSearchLuma(puStruct pu);
void predSearchChroma(puStruct pu);

void predSearchBlock(s16 *pb, u8 *mode);
void predSearchBlock(s16 *pbChroma1, s16 *pbChroma2, u8 *modeLuma, u8 *modeChroma);
void predBlock(s16 *pb, u8 mode);

void predUPM(s16 *pb, u8 dir);
void predLPM(s16 *pb, u8 dir);
void predBPM(s16 *pb, u8 dir);
void predDC(s16 *pb);

u16 hadamardMetric(s16 *pbTrue, s16 *pbEst);


#endif