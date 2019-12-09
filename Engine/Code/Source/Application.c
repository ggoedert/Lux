#define LUX_DEFINE_GLOBALS

#include <stdlib.h>

#include "Apple2Id.h"
#include "Screen.h"
#include "SceneManager.h"

#include "LuxApplication.h"
#include "LuxScreen.h"
#include "LuxSceneManager.h"

void Application_Run(char *name, int version, LoadApplication loadApplication) {
    _heapadd((void *)0x300, 0xcf);

    GetApple2Id((Apple2Id *)&application);
    application.name = name;
    application.version = version;

    if (application.memory > 48)
        _heapadd((void *)0xd000, 0x1000);
    Screen_Init();
    SceneManager_Init();

    loadApplication();
    while(true)
        SceneManager_Run();
}
