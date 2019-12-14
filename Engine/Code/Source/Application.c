#define LUX_DEFINE_GLOBALS

#include "Apple2Id.h"
#include "Screen.h"
#include "Scene.h"
#include "SceneManager.h"

#include "LuxApplication.h"
#include "LuxScreen.h"
#include "LuxSceneManagement.h"

void Application_Run(char *name, int version, LoadApplication loadApplication) {
    _heapadd((void *)0x300, 0xCF);

    GetApple2Id((Apple2Id *)&application);
    application.name = name;
    application.version = version;

    if (application.memory > 48)
        _heapadd((void *)0xD000, 0x1000);
    Screen_Init();
    SceneManager_Init();

    loadApplication();
    while(true)
        Scene_Run();
}
