#include <stdio.h>
#include <string.h>

#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"
#include "MainScene.h"

bool mainLoad();

#ifdef __CC65__
void main() {
    Application_Play("2D UFO", 1, mainLoad);
    Screen_SetResolution(TEXT, false, false);
    Debug_Dequeue();
    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Debug_Log("%u bytes free.", _heapmemavail());
    while (true);
}
#else
bool mainStart() {
    return Application_Start("2D UFO", 1, mainLoad);
}

bool mainStep() {
    return Application_Step();
}

void mainStop() {
    MainScene_Unload();
    Application_Stop();
    Debug_Dequeue();
}
#endif

bool mainLoad() {
#ifdef __CC65__
    int memAvail = _heapmemavail();
    Debug_SetMode(DEBUG_MODE_QUEUE);
#else
    Debug_SetMode(DEBUG_MODE_CONSOLE);
#endif
    if (application.machine < IIe) {
        Debug_Log("Apple IIe not detected!");
        return false;
    }
#ifdef __CC65__
    Debug_Log("%u bytes free.", memAvail);
#endif
    Camera_backgroundColor = green;
    Screen_SetResolution(HGR, true, false);
    SceneManager_LoadScene(MainScene_Load);
    return true;
}
