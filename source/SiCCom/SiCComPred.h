#ifndef SIC_COM_PRED_H
#define SIC_COM_PRED_H

#include "ComDef.h"
#include <cstring>

void predPU(puStruct *pu);
void predLuma(puStruct *pu);
void predChroma(puStruct *pu);

void predSearch(puStruct *pu, ChromaSub chromaSub);
void predSearch(s16 *pb, ChromaSub chromaSub);
void predSearchChroma(puStruct *pu);

void predSearchBlock(s16 *pb, u8 *mode, ScanDir *scan);
void predSearchBlock(s16 *pbChroma1, s16 *pbChroma2, u8 *modeLuma, u8 *modeChroma, ScanDir *scan);
void predBlock(s16 *pb, u8 mode);
void predBlock(s16 *pb1, s16 *pb2, u8 *modeLuma, u8 modeChroma, ScanDir *scanChroma);

void predUPM(s16 *pb, u8 dir);
void predLPM(s16 *pb, u8 dir);
void predBPM(s16 *pb, u8 dir);
void predDC(s16 *pb);

u16 hadamardMetric(s16 *pbTrue, s16 *pbEst);


#endif