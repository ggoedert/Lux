#include <conio.h>
#include <stdio.h>
#include "lEngine.h"

void LuxClrScr() {
	clrscr();
}

void LuxEcho(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
