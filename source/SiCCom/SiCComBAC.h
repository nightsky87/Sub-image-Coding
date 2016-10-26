#ifndef SIC_COM_BAC_H
#define SIC_COM_BAC_H

#include "ComDef.h"
#include "SiCComBACCore.h"
#include "SiCComBACContexts.h"
#include <cstring>

void stuEnc(stuStruct stu);

void vstbEnc(scuStruct *scu);
void hstbEnc(scuStruct *scu);
void stbEnc(s16 *stb, component comp, scanDir dir);

void puEnc(puStruct pu);
void puEncLuma(puStruct pu);
void puEncChroma(puStruct pu);
void puEncDir(u8 mode);
void puEncType(u8 mode);

void rtuEnc(rtuStruct rtu);
void rtbEnc(s16 *rtb, component comp, scanDir dir);

void stuDec(stuStruct stu);

void vstbDec(scuStruct *scu);
void hstbDec(scuStruct *scu);
void stbDec(s16 *stb, component comp, scanDir dir);

void puDec(puStruct pu);
void puDecLuma(puStruct pu);
void puDecChroma(puStruct pu);
u8 puDecDir();
u8 puDecType();

void rtuDec(rtuStruct rtu);
void rtbDec(s16 *rtb, component comp, scanDir dir);

#endif
