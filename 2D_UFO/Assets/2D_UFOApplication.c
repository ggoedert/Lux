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
    Application_Run("2D UFO", 1, loadApplication);
}

void loadApplication() {
    Camera_backgroundColor = green;
    //Screen_SetResolution(HGR, false, false);
    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Screen_SetResolution(TEXT, false, false);
    SceneManager_LoadScene(MainScene_Load);
}
