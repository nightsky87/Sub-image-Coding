#ifndef SIC_COM_BAC_H
#define SIC_COM_BAC_H

#include "ComDef.h"
#include "SiCComBACCore.h"
#include "SiCComBACContexts.h"
#include <cstring>

void stuEnc(stuStruct &stu, ChromaSub chromaSub);

void vstbEnc(scuStruct *scu, ChromaSub chromaSub);
void hstbEnc(scuStruct *scu, ChromaSub chromaSub);
void stbEnc(s16 *stb, Component comp, ScanDir dir);

void puEnc(puStruct pu);
void puEncLuma(puStruct pu);
void puEncChroma(puStruct pu);
void puEncDir(u8 mode);
void puEncType(u8 mode);

void rtuEnc(rtuStruct rtu);
void rtbEnc(s16 *rtb, Component comp, ScanDir dir);

void stuDec(stuStruct stu);

void vstbDec(scuStruct *scu);
void hstbDec(scuStruct *scu);
void stbDec(s16 *stb, Component comp, ScanDir dir);

void puDec(puStruct pu);
void puDecLuma(puStruct pu);
void puDecChroma(puStruct pu);
u8 puDecDir();
u8 puDecType();

void rtuDec(rtuStruct rtu);
void rtbDec(s16 *rtb, Component comp, ScanDir dir);

#endif
