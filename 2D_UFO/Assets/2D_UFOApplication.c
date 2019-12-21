#include <string.h>
#include <peekpoke.h>//@@need major cleanup@@ ??delthis??

#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "MainScene.h"

void loadApplication(void);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Run("Roll A Ball", 1, loadApplication);
}

void loadApplication() {

    Debug_SetMode(DEBUG_MODE_CONSOLE);
    //Screen_SetResolution(HGR, true, true);
    Screen_SetResolution(TEXT, false, false);
    Debug_Log("%u bytes free", _heapmemavail());

    //***
    // @FIXME@ CODE BELOW SHOULD REFACTORED INTO THE LUX ENGINE AS SOMEKIND OF CLEAR FUNCTION (?ACEPTING A COLOR VALUE?)

    //should keep track if we are really in DHGR
    //should do some scheduling function with stack with graphics commands that write to screen during vsync or something
    //and also calls gameobject type updates

#define CLR80COL  0xC000    // disable 80-column store
#define SET80COL  0xC001    // enable 80-column store
#define TXTPAGE1  0xC054    // switch in page 1
#define TXTPAGE2  0xC055    // switch in page 2

    if (application.machine >= IIe) {
        POKE(CLR80COL, 0);
        POKE(TXTPAGE1, 0);
    }
    memset((void *)0x2000, 0xFF, 0x2000);
    if (application.machine >= IIe) {
        POKE(SET80COL, 0);
        POKE(TXTPAGE2, 0);
        memset((void *)0x2000, 0xFF, 0x2000);
    }

    if (application.machine >= IIe) {
        POKE(CLR80COL, 0);
        POKE(TXTPAGE1, 0);
    }
    //***

    SceneManager_LoadScene(MainScene_Load);
}
