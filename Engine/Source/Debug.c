#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "LuxDebug.h"
#include "LuxQueue.h"

#ifdef NDEBUG
byte debugMode = 0x0;
#else
byte debugMode = DEBUG_MODE_CONSOLE;
#endif

Queue *logQueue = nullptr;

void Debug_SetMode(byte mode) {
    debugMode = mode;
    if (debugMode&DEBUG_MODE_QUEUE) {
        logQueue = Queue_New(sizeof(char *));
        Queue_Constructor(logQueue, sizeof(char *));
        Queue_SetCapacity(logQueue, 24);
    }
    else {
        if (logQueue)
            Queue_Delete(logQueue);
    }
}

void Debug_Log(const char *format, ...) {
    if (debugMode) {
#ifdef __CC65__
        __va_list args;
#else
        va_list args;
#endif
        char lineBuffer[80];
        va_start(args, format);
        vsnprintf(lineBuffer, 80, format, args);
        va_end(args);
        if (debugMode&DEBUG_MODE_CONSOLE)
            printf("\n%s", lineBuffer);
        if (debugMode&DEBUG_MODE_FILE) {
#ifdef __CC65__
            FILE *logFile = fopen("Lux.log", "a");
#else
            FILE* logFile;
            fopen_s(&logFile, "Lux.log", "a");
#endif
            fprintf(logFile, "%s\n", lineBuffer);
            fclose(logFile);
        }
        if (debugMode&DEBUG_MODE_QUEUE) {
            if (logQueue->count > 23) {
                free(Queue_Peek(logQueue, char *));
                Queue_Dequeue(logQueue);
            }
#ifdef __CC65__
            Queue_Enqueue(logQueue, char *, strdup(lineBuffer));
#else
            Queue_Enqueue(logQueue, char*, _strdup(lineBuffer));
#endif
        }
    }
}

void Debug_Dequeue() {
    if (debugMode&DEBUG_MODE_QUEUE) {
        while (logQueue->count) {
            char *line = Queue_Peek(logQueue, char *);
            Queue_Dequeue(logQueue);
            printf("\n%s", line);
            free(line);
        }
    }
}
