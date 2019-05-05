#include <stdlib.h>

#include <lEngine.h>

#include "Classes.h"
#include "MapMemory.h"

//main.c
void main() {
    LuxClrScr();
	LuxEcho("%u bytes free.\n", _heapmemavail());

    LuxEcho("\n");
    DoClassesTest();
    LuxEcho("\n");
    DoMapMemoryTest();
    LuxEcho("\n");

	LuxEcho("%u bytes free.\n", _heapmemavail());
	LuxEcho("end.");
    while(1);
}
