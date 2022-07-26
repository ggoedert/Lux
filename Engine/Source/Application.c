#include "Apple2Id.h"
#include "QualitySettings.h"
#include "Screen.h"
#include "Time.h"
#include "Scene.h"

#include "LuxApplication.h"
#include "LuxQualitySettings.h"
#include "LuxScreen.h"
#include "LuxSceneManagement.h"

Application application;
char *Application_name = nullptr;
word Application_version = 0;
#ifdef _DEBUG
byte Application_isPlaying = false;
#endif

#ifdef __CC65__
void Application_Play(char *name, word version, LoadApplication loadApplication) {
    _heapadd((void *)0x300, 0xCF);

    GetApple2Id((Apple2Id *)&application);
    Application_name = name;
    Application_version = version;

    if (application.memory > 48)
        _heapadd((void *)0xD000, 0x1000);
    QualitySettings_Init();
    Screen_Init();
    Time_Init();
    Scene_Init();

#ifdef _DEBUG
    Application_isPlaying = true;
#endif

    if (loadApplication()) {
        while (Application_isPlaying) {
            Scene_Run();
            Time_Run();
            if (QualitySettings_vSync)
                Screen_WaitVBlank();
        }
    }
}
#else
bool Application_Start(char *name, word version, LoadApplication loadApplication) {
    GetApple2Id((Apple2Id *)&application);
    Application_name = name;
    Application_version = version;

    QualitySettings_Init();
    Screen_Init();
    Time_Init();
    Scene_Init();

#ifdef _DEBUG
    Application_isPlaying = true;
#endif

    return loadApplication();
}

#ifndef __CC65__
void Application_Stop() {
    Screen_Finalize();
}
#endif

bool Application_Step() {
    Scene_Run();
    Time_Run();
    if (QualitySettings_vSync)
        Screen_WaitVBlank();
    return Application_isPlaying;
}
#endif

#ifdef _DEBUG
void Application_Quit() {
    Application_isPlaying = false;
}
#endif
