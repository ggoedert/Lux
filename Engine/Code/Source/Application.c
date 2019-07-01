#define LUX_DEFINE_GLOBALS

#include <stdlib.h>

#include "Apple2Id.h"
#include "Screen.h"

#include "LuxApplication.h"
#include "LuxScreen.h"

void Application_Run(char* name, int version, LoadApplication loadApplication) {
    GetApple2Id((Apple2Id*)&application);
    application.name = name;
    application.version = version;

    _heapadd((void*)0x300, 0xcf);
    if (application.memory > 48)
        _heapadd((void*)0xd000, 0x1000);

    Screen_Init();

    loadApplication();

    while(true);
}
