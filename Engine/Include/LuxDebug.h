#ifndef LUX_DEBUG_H
#define LUX_DEBUG_H

#include "LuxTypes.h"

// debug modes
#define DEBUG_MODE_CONSOLE 0x1
#define DEBUG_MODE_FILE    0x2
#define DEBUG_MODE_QUEUE   0x4

void Debug_SetMode(byte mode);
void Debug_Log(const char *format, ...);
void Debug_Dequeue();

#ifndef __CC65__
void (*System_PrintDebug)(char *lineBuffer);
#endif

#endif
