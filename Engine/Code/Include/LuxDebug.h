#ifndef LUX_DEBUG_H
#define LUX_DEBUG_H

// debug modes
#define DEBUG_MODE_CONSOLE 0x1
#define DEBUG_MODE_FILE    0x2

void lux_Debug_SetMode(byte mode);
void lux_Debug_Log(const char* format, ...);

#endif
