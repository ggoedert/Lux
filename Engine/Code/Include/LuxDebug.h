#ifndef LUX_DEBUG_H
#define LUX_DEBUG_H

#include "LuxTypes.h"

// debug modes
#define DEBUG_MODE_CONSOLE 0x1
#define DEBUG_MODE_FILE    0x2

void Debug_SetMode(byte mode);
void Debug_Log(const char *format, ...);

#endif
