#ifndef LUX_ENGINE_H
#define LUX_ENGINE_H

#include "LuxApplication.h"
#include "LuxDebug.h"
#include "LuxScreen.h"

typedef void (*LoadApplication)(void);

void lux_Run(char* name, int version, LoadApplication loadApplication);

#endif
