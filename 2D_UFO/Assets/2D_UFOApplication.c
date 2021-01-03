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
    Assets_Constructor(&assets, NONE);
    Application_Play("2D UFO", 1, loadApplication);
    Screen_SetResolution(TEXT, false, false);
    Debug_Dequeue();
    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Debug_Log("%u bytes free.", _heapmemavail());
    while(true);
}

void loadApplication() {
    int memAvail;
    if (application.machine < IIe) {
        printf("\nApple IIe not detected!");
        while(true);
    }
    memAvail = _heapmemavail();
    Debug_SetMode(DEBUG_MODE_QUEUE);
    Debug_Log("%u bytes free.", memAvail);
    Resources_AddStorage(&assets.Storage);
    Camera_backgroundColor = green;
    Screen_SetResolution(HGR, true, false);
    SceneManager_LoadScene(MainScene_Load);
}
