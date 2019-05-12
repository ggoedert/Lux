#include <stdlib.h>

#include <lDefs.h>
#include <lEngine.h>

#include "Classes.h"
#include "MapMemory.h"
#include "Apple2Id.h"

//main.c
void main() {
    LuxClrScr();
	LuxEcho("%u bytes free.\n", _heapmemavail());

    LuxEcho("\n");
    DoClassesTest();
    LuxEcho("\n");
    DoMapMemoryTest();
    LuxEcho("\n");
    DoApple2Id();
    LuxEcho("\n");

	LuxEcho("%u bytes free.\n", _heapmemavail());
	LuxEcho("end.");
    while(true);
}
