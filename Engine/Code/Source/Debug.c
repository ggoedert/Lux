#include <stdio.h>

#include "LuxEngine.h"

#ifdef NDEBUG
byte lux_Debug_mode = 0x0;
#else
byte lux_Debug_mode = DEBUG_MODE_CONSOLE;
#endif

void lux_Debug_SetMode(byte mode) {
    lux_Debug_mode = mode;
}

void lux_Debug_Log(const char* format, ...) {
    FILE* logFile;
    va_list args;
    if (lux_Debug_mode) {
        va_start(args, format);
        if (lux_Debug_mode&DEBUG_MODE_CONSOLE) {
            printf("\n");
            vprintf(format, args);
        }
        if (lux_Debug_mode&DEBUG_MODE_FILE) {
            logFile = fopen("Lux.log", "a");
            vfprintf(logFile, format, args);
            fputc('\n', logFile);
            fclose(logFile);
        }
        va_end(args);
    }
}
