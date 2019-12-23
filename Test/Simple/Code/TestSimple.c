#include "LuxSystem.h"
#include "LuxEngine.h"

#include "Classes.h"
#include "MapMemory.h"

void loadApplication(void);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Run("Test", 42, loadApplication);
}

void loadApplication() {
    Debug_SetMode(DEBUG_MODE_CONSOLE|DEBUG_MODE_FILE);
    Screen_SetResolution(TEXT, false, false);

    Debug_Log("%u bytes free.", _heapmemavail());
    Debug_Log("");

    Debug_Log("luxVersion: %u", luxVersion);
    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.romlevel: %u",  application.romlevel);
    Debug_Log("application.memory: %u",  application.memory);
    Debug_Log("application.name: %s", application.name);
    Debug_Log("application.version: %u", application.version);
    Debug_Log("Screen_resolutions_Length: %hhu", Screen_resolutions_Length);
    Debug_Log("");

    //Debug_Log("String_GetHashCode(\"abcde\"): $%04x", String_GetHashCode("abcde"));
    //Debug_Log("String_GetHashCode(\"abcdef\"): $%04x", String_GetHashCode("abcdef"));
    //Debug_Log("String_GetHashCode(\"abcdefgh\"): $%04x", String_GetHashCode("abcdefgh"));
    Debug_Log("String_GetHashCode(\"Untitled\"): $%04x", String_GetHashCode("Untitled"));
    Debug_Log("String_GetHashCode(\"CustomBehaviour\"): $%04x", String_GetHashCode("CustomBehaviour"));
    Debug_Log("");

    DoClassesTest();
    Debug_Log("");
    
    //DoMapMemoryTest(); @this is not working@
    //Debug_Log("");

    Debug_Log("%u bytes free.", _heapmemavail());
    Debug_Log("end.");
}
