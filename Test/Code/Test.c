#include <stdlib.h>

#include "LuxEngine.h"

#include "Classes.h"
#include "MapMemory.h"

//main.c
void main() {
    lux_Start("Test", 42);
	lux_Debug_Set(DEBUG_CONSOLE);
    lux_Screen_SetResolution(TEXT, false, false);

	lux_Debug_Log("%u bytes free.", _heapmemavail());
    lux_Debug_Log("");

    lux_Debug_Log("lux_Application.machine: %u", lux_Application.machine);
    lux_Debug_Log("lux_Application.romlevel: %u",  lux_Application.romlevel);
    lux_Debug_Log("lux_Application.memory: %u",  lux_Application.memory);
	lux_Debug_Log("lux_Application.name: %s", lux_Application.name);
	lux_Debug_Log("lux_Application.version: %d", lux_Application.version);
	lux_Debug_Log("lux_Screen_resolutions_Length: %d", lux_Screen_resolutions_Length);
    lux_Debug_Log("");

    DoClassesTest();
    lux_Debug_Log("");
    
    DoMapMemoryTest();
    lux_Debug_Log("");

	lux_Debug_Log("%u bytes free.", _heapmemavail());
	lux_Debug_Log("end.");
    while(true);
}
