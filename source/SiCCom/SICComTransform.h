#ifndef SIC_COM_TRANSFORM_H
#define SIC_COM_TRANSFORM_H

#include "ComDef.h"
#include <stdlib.h>

void dct(cpStruct *cp);
void dct(s16 *tb, u8 width, u8 height);

void idct(cpStruct *cp);
void idct(s16 *tb, u8 width, u8 height);

#endif
