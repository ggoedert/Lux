#include <stdio.h>
#include <string.h>

#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"
#include "MainScene.h"

void loadApplication(void);

//main.c
void main() {
    Application_Play("2D UFO", 1, loadApplication);
    Screen_SetResolution(TEXT, false, false);
    Debug_Dequeue();
    Debug_SetMode(DEBUG_MODE_CONSOLE);
#ifdef __CC65__
    Debug_Log("%u bytes free.", _heapmemavail());
#endif
    while(true);
}

void loadApplication() {
#ifdef __CC65__
    int memAvail;
#endif
    if (application.machine < IIe) {
        printf("\nApple IIe not detected!");
        while(true);
    }
#ifdef __CC65__
    memAvail = _heapmemavail();
#endif
    Debug_SetMode(DEBUG_MODE_QUEUE);
#ifdef __CC65__
    Debug_Log("%u bytes free.", memAvail);
#endif
    Camera_backgroundColor = green;
    Screen_SetResolution(HGR, true, false);
    SceneManager_LoadScene(MainScene_Load);
}
