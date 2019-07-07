#include <stdlib.h>
#include <string.h>

#include <apple2.h>

#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include <peekpoke.h>//@@need major cleanup@@ ??delthis??

void loadApplication(void);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Run("TestEngine", 1, loadApplication);
}

void loadApplication() {
    Scene *miniGameScene;
    
    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Screen_SetResolution(HGR, true, true);

    miniGameScene = SceneManager_CreateScene("MiniGame");

    /*byte *ptr=(byte *)0x2000;
    byte col = 0x0;
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.machine: %u", application.machine);*/
    /* while (ptr<(byte *)0x4000) {
        *ptr = 0xff;
        ptr++;
        col++;
    }*/
    Debug_Log("%u bytes free.", _heapmemavail());

    //should keep track if we are really in DHGR
    //should do some scheduling function with stack with graphics commands that write to screen during vsync or something
    //and also calls gameobject type updates

#define CLR80COL  0xC000    // disable 80-column store
#define SET80COL  0xC001    // enable 80-column store
#define TXTPAGE1  0xC054    // switch in page 1
#define TXTPAGE2  0xC055    // switch in page 2

    if (application.machine >= IIe) {
        POKE(TXTPAGE1, 0);
        POKE(CLR80COL, 0);
    }
    memset((void *)0x2000, 0xff, 0x2000);
    if (application.machine >= IIe) {
        POKE(SET80COL, 0);
        POKE(TXTPAGE2, 0);
        memset((void *)0x2000, 0xff, 0x2000);
    }
}
