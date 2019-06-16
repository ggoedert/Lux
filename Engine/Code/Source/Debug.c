
#include <stdio.h>

#include "LuxEngine.h"

#ifndef _DEBUG
byte lux_Debug_mode = 0x0;
#else
byte lux_Debug_mode = DEBUG_CONSOLE;
#endif

void lux_Debug_Set(byte mode) {
    lux_Debug_mode = mode;
}

void lux_Debug_Log(const char* format, ...) {
    FILE* logFile;
    if (lux_Debug_mode) {
        va_list args;
        va_start(args, format);
        if (lux_Debug_mode&DEBUG_CONSOLE) {
            vprintf(format, args);
            printf("\n");
        }
        if (lux_Debug_mode&DEBUG_FILE) {
            logFile = fopen("Lux.log", "a");
            vfprintf(logFile, format, args);
            fprintf(logFile, "\n");
            fclose(logFile);
        }
        va_end(args);
    }
}
