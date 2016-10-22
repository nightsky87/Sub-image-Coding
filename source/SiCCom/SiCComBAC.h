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

#endif
