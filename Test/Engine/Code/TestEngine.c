#include <stdlib.h>
#include <string.h>

#include <apple2.h>

#include "LuxEngine.h"

#include <peekpoke.h>//@@need major cleanup@@ ??delthis??

void loadApplication(void);

//main.c
void main() {
    _heapadd(0x300, 0xcf);
    _heapadd(0x800, 0x1800);
    lux_Run("TestEngine", 1, loadApplication);
}

void loadApplication() {
    if (lux_Application.memory > 48)
        _heapadd(0xd000, 0x1000);
	lux_Debug_SetMode(DEBUG_MODE_CONSOLE);
    lux_Screen_SetResolution(HGR, true, true);
    /*char *ptr=(char *)0x2000;
    char col = 0x0;
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);*/
    /* while (ptr<(char*)0x4000) {
        *ptr = 0xff;
        ptr++;
        col++;
    }*/
	lux_Debug_Log("%u bytes free.", _heapmemavail());

    //should keep track if we are really in DHGR
    //should do some scheduling function with stack with graphics commands that write to screen during vsync or something
    //and also calls gameobject type updates

#define CLR80COL  0xC000    // disable 80-column store
#define SET80COL  0xC001    // enable 80-column store
#define TXTPAGE1  0xC054    // switch in page 1
#define TXTPAGE2  0xC055    // switch in page 2
    memset((void*)0x2000, 0xff, 0x2000);
    POKE(SET80COL, 0);
    POKE(TXTPAGE2, 0);
    memset((void*)0x2000, 0xff, 0x2000);
    POKE(TXTPAGE1, 0);
    POKE(CLR80COL, 0);
}
