#include <conio.h>
#include <stdio.h>

#define LUX_DEFINE_GLOBALS

#include "LuxEngine.h"
#include "Apple2Id.h"

void lux_Init(char* name, int version) {
    //lux_Screen_Init();
    GetApple2Id((Apple2Id*)&lux_Application);
    lux_Application.name = name;
    lux_Application.version = version;
}

void lux_ClrScr() {
	clrscr();
}

void lux_Echo(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
