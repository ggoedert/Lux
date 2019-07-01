#include <stdlib.h>

#include "LuxEngine.h"

#include "Classes.h"
#include "MapMemory.h"

void loadApplication(void);

//main.c
void main() {
    Application_Run("Test", 42, loadApplication);
}

void loadApplication() {
	Debug_SetMode(DEBUG_MODE_CONSOLE|DEBUG_MODE_FILE);
    Screen_SetResolution(TEXT, false, false);

	Debug_Log("%u bytes free.", _heapmemavail());
    Debug_Log("");

    Debug_Log("application.machine: %u", application.machine);
    Debug_Log("application.romlevel: %u",  application.romlevel);
    Debug_Log("application.memory: %u",  application.memory);
	Debug_Log("application.name: %s", application.name);
	Debug_Log("application.version: %d", application.version);
	Debug_Log("Screen_resolutions_Length: %d", Screen_resolutions_Length);
    Debug_Log("");

    DoClassesTest();
    Debug_Log("");
    
    DoMapMemoryTest();
    Debug_Log("");

	Debug_Log("%u bytes free.", _heapmemavail());
	Debug_Log("end.");
}
