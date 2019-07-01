#include <stdio.h>

#include "LuxDebug.h"

#ifdef NDEBUG
byte debugMode = 0x0;
#else
byte debugMode = DEBUG_MODE_CONSOLE;
#endif

void Debug_SetMode(byte mode) {
    debugMode = mode;
}

void Debug_Log(const char* format, ...) {
    FILE* logFile;
    va_list args;
    if (debugMode) {
        va_start(args, format);
        if (debugMode&DEBUG_MODE_CONSOLE) {
            printf("\n");
            vprintf(format, args);
        }
        if (debugMode&DEBUG_MODE_FILE) {
            logFile = fopen("Lux.log", "a");
            vfprintf(logFile, format, args);
            fputc('\n', logFile);
            fclose(logFile);
        }
        va_end(args);
    }
}
