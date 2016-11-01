#ifndef SIC_COM_PRED_H
#define SIC_COM_PRED_H

#include "ComDef.h"
#include <cstring>

#define PRED_MODE_NN 8

void pred(cpStruct *cp);
void predLuma(cpStruct *cp);
void predChroma(cpStruct *cp);
void predChroma(cpStruct *cp, cpStruct *cpDiff);

void predBlock(s16 *pb, u8 stride, u8 mode);

void predDir(s16 *pb, u8 stride, u8 dir);
void predNN(s16 *pb, u8 stride);

void predSearch(cpStruct *cp);
u8 predSearchBlock(s16 *pb, u8 stride, s16 *pbTrue, u8 strideTrue);

u16 hadamardMetric(s16 *pb, u8 stride, s16 *pbTrue, u8 strideTrue);

//void predSearchBlock(s16 *pb, u8 *mode, ScanDir *scan);
//void predSearchBlock(s16 *pbChroma1, s16 *pbChroma2, u8 *modeLuma, u8 *modeChroma, ScanDir *scan);
//void predBlock(s16 *pb, u8 mode);
//void predBlock(s16 *pb1, s16 *pb2, u8 *modeLuma, u8 modeChroma, ScanDir *scanChroma);


//u16 hadamardMetric(s16 *pbTrue, s16 *pbEst);
//

#endif