#include <conio.h>
#include <stdlib.h>

#include "LuxEngine.h"

#include "Screen.h"

void lux_Screen_Init() {
    if (lux_Application.machine < IIe)
        lux_Screen_resolutions_Length = 5;
    else
        lux_Screen_resolutions_Length = 10;
}

void lux_Screen_resolutions_Get(Lux_Resolution** lux_Screen_resolutions) {
    *lux_Screen_resolutions = malloc(sizeof(Lux_Resolution)*lux_Screen_resolutions_Length);
    (*lux_Screen_resolutions)[0].mode = TEXT;
    (*lux_Screen_resolutions)[0].mixed = false;
    (*lux_Screen_resolutions)[0].doubleRes = false;
    (*lux_Screen_resolutions)[1].mode = LGR;
    (*lux_Screen_resolutions)[1].mixed = false;
    (*lux_Screen_resolutions)[1].doubleRes = false;
    (*lux_Screen_resolutions)[2].mode = LGR;
    (*lux_Screen_resolutions)[2].mixed = true;
    (*lux_Screen_resolutions)[2].doubleRes = false;
    (*lux_Screen_resolutions)[3].mode = HGR;
    (*lux_Screen_resolutions)[3].mixed = false;
    (*lux_Screen_resolutions)[3].doubleRes = false;
    (*lux_Screen_resolutions)[4].mode = HGR;
    (*lux_Screen_resolutions)[4].mixed = true;
    (*lux_Screen_resolutions)[4].doubleRes = false;
    if (lux_Application.machine >= IIe) {
        (*lux_Screen_resolutions)[5].mode = TEXT;
        (*lux_Screen_resolutions)[5].mixed = false;
        (*lux_Screen_resolutions)[5].doubleRes = true;
        (*lux_Screen_resolutions)[6].mode = LGR;
        (*lux_Screen_resolutions)[6].mixed = false;
        (*lux_Screen_resolutions)[6].doubleRes = true;
        (*lux_Screen_resolutions)[7].mode = LGR;
        (*lux_Screen_resolutions)[7].mixed = true;
        (*lux_Screen_resolutions)[7].doubleRes = true;
        (*lux_Screen_resolutions)[8].mode = HGR;
        (*lux_Screen_resolutions)[8].mixed = false;
        (*lux_Screen_resolutions)[8].doubleRes = true;
        (*lux_Screen_resolutions)[9].mode = HGR;
        (*lux_Screen_resolutions)[9].mixed = true;
        (*lux_Screen_resolutions)[9].doubleRes = true;
    }
}

void lux_Screen_SetResolution(byte mode, bool mixed, bool doubleRes) {
	clrscr();
}
