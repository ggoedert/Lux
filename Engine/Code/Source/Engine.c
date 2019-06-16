#define LUX_DEFINE_GLOBALS

#include "LuxEngine.h"

#include "Apple2Id.h"
#include "Screen.h"

void lux_Start(char* name, int version) {
    GetApple2Id((Apple2Id*)&lux_Application);
    lux_Application.name = name;
    lux_Application.version = version;

    lux_Screen_Init();
}
