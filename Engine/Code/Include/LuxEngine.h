#ifndef LUX_ENGINE_H
#define LUX_ENGINE_H

#include "LuxClass.h"
#include "LuxApplication.h"
#include "LuxScreen.h"

void lux_ClrScr(void);
void lux_Echo(const char* format, ...);

void lux_Init(char* name, int version);

#endif
