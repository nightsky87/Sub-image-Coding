#ifndef SIC_COM_BAC_CORE_H
#define SIC_COM_BAC_CORE_H

#include "ComDef.h"
#include "SiCComBACContexts.h"
#include <cstring>
#include <cstdlib>

u16 rangeTabLPS(u8 pStateIdx, u8 qCodIRangeIdx);
u8 transIdxLPS(u8 pStateIdx);

void InitializeEncoder(u32 numBytes);
void EncodeDecision(u8 ctxIdx, u8 binVal);
void EncodeBypass(u8 binVal);
void EncodeTerminate();
void PutBit(u8 B);

#endif
