#include "LuxSystem.h"
#include "LuxEngine.h"

#include "Classes.h"
#include "MapMemory.h"

void loadApplication(void);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Play("Test", 42, loadApplication);
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
    Debug_Log("application.name: %s", Application_name);
    Debug_Log("application.version: %u",  Application_version);
    Debug_Log("Screen_resolutions_Length: %hhu", Screen_resolutions_Length);
    Debug_Log("");

    DoClassesTest();
    Debug_Log("");
    
    //DoMapMemoryTest(); @this is not working@
    //Debug_Log("");

    Debug_Log("String_GetHashCode16(\"abcde\"): $%04x", String_GetHashCode16("abcde"));
    Debug_Log("String_GetHashCode16(\"abcdef\"): $%04x", String_GetHashCode16("abcdef"));
    Debug_Log("String_GetHashCode16(\"abcdefgh\"): $%04x", String_GetHashCode16("abcdefgh"));
    Debug_Log("String_GetHashCode16(\"Untitled\"): $%04x", String_GetHashCode16("Untitled"));
    Debug_Log("");

    Debug_Log("String_GetHashCode8(\"abcde\"): $%02x", String_GetHashCode8("abcde"));
    Debug_Log("String_GetHashCode8(\"abcdef\"): $%02x", String_GetHashCode8("abcdef"));
    Debug_Log("String_GetHashCode8(\"abcdefgh\"): $%02x", String_GetHashCode8("abcdefgh"));
    Debug_Log("String_GetHashCode8(\"Untitled\"): $%02x", String_GetHashCode8("Untitled"));
    Debug_Log("String_GetHashCode8(\"CustomBehaviour\"): $%02x", String_GetHashCode8("CustomBehaviour"));
    Debug_Log("String_GetHashCode8(\"Renderer\"): $%02x", String_GetHashCode8("Renderer"));
    Debug_Log("String_GetHashCode8(\"Transform\"): $%02x", String_GetHashCode8("Transform"));
    Debug_Log("String_GetHashCode8(\"Texture2D\"): $%02x", String_GetHashCode16("Texture2D"));
    Debug_Log("");

    Debug_Log("%u bytes free.", _heapmemavail());
    Debug_Log("end.");
}
