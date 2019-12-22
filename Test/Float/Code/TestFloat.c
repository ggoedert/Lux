#include "LuxEngine.h"

void loadApplication(void);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Run("TestFloat", 1, loadApplication);
}

void loadApplication() {
    Float frameTime;
    char buffer[FLOAT_MAX_STRING_SIZE];

    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Screen_SetResolution(TEXT, false, false);

    Debug_Log("%u bytes free.", _heapmemavail());
    Debug_Log("$%08lx", Float_pi);
    Debug_Log("$%08lx", (Float)FLOATC_I(30));
    frameTime = Float_Div(Float_one, FLOATC_I(30));
    Debug_Log("$%08lx", frameTime);
    Float_ToString(frameTime, buffer, 5);
    Debug_Log("Float (1/30) = %s", buffer);
}
