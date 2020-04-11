#include "Apple2Id.h"
#include "QualitySettings.h"
#include "Screen.h"
#include "Time.h"
#include "Scene.h"

#include "LuxApplication.h"
#include "LuxQualitySettings.h"
#include "LuxResources.h"
#include "LuxScreen.h"
#include "LuxSceneManagement.h"

Application application;
char *Application_name = nullptr;
word Application_version = 0;
#ifdef _DEBUG
byte Application_isPlaying = false;
#endif

void Application_Play(char *name, word version, LoadApplication loadApplication) {
    _heapadd((void *)0x300, 0xCF);

    GetApple2Id((Apple2Id *)&application);
    Application_name = name;
    Application_version = version;

    if (application.memory > 48)
        _heapadd((void *)0xD000, 0x1000);
    QualitySettings_Init();
    Resources_Init();
    Screen_Init();
    Time_Init();
    Scene_Init();

#ifdef _DEBUG
    Application_isPlaying = true;
#endif

    loadApplication();
    while(Application_isPlaying) {
        Scene_Run();
        Time_Run();
        if (QualitySettings_vSync)
            Screen_WaitVBlank();
    }
}

#ifdef _DEBUG
void Application_Stop() {
    Scene_Finalize();
    Resources_Finalize();
    Application_isPlaying = false;
}
#endif
