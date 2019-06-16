#include <stdlib.h>

#include "LuxEngine.h"

#include "Classes.h"
#include "MapMemory.h"

//main.c
void main() {
    lux_Init("Test", 42);

    lux_ClrScr();
	lux_Echo("%u bytes free.\n", _heapmemavail());
    lux_Echo("\n");

    lux_Echo("lux_Application.machine: %u\n", lux_Application.machine);
    lux_Echo("lux_Application.romlevel: %u\n",  lux_Application.romlevel);
    lux_Echo("lux_Application.memory: %u\n",  lux_Application.memory);
	lux_Echo("lux_Application.name %s\n", lux_Application.name);
	lux_Echo("lux_Application.version %d\n", lux_Application.version);
    lux_Echo("\n");

    DoClassesTest();
    lux_Echo("\n");
    
    DoMapMemoryTest();
    lux_Echo("\n");

	lux_Echo("%u bytes free.\n", _heapmemavail());
	lux_Echo("end.");
    while(true);
}
