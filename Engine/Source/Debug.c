#include <stdio.h>
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
        va_list args;
        char lineBuffer[80];
        va_start(args, format);
        vsnprintf(lineBuffer, 80, format, args);
        va_end(args);
        if (debugMode&DEBUG_MODE_CONSOLE)
            printf("\n%s", lineBuffer);
        if (debugMode&DEBUG_MODE_FILE) {
            FILE *logFile = fopen("Lux.log", "a");
            fprintf(logFile, "%s\n", lineBuffer);
            fclose(logFile);
        }
        if (debugMode&DEBUG_MODE_QUEUE) {
            if (logQueue->count > 23) {
                free(Queue_Peek(logQueue, char *));
                Queue_Dequeue(logQueue);
            }
            Queue_Enqueue(logQueue, char *, strdup(lineBuffer));
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
