#include <stddef.h>
#include <stdlib.h>

#include <lEngine.h>
#include <lApple2Id.h>

#include "Apple2Id.h"

void DoApple2Id() {
    Apple2Id apple2Id;

    LuxEcho("* Start Apple2 Id Test *\n");

    GetApple2Id(&apple2Id);
    LuxEcho("machine: %u\n", apple2Id.machine);
    LuxEcho("romlevel: %u\n",  apple2Id.romlevel);
    LuxEcho("memory: %u\n",  apple2Id.memory);

    LuxEcho("* End Apple2 Id Test *\n");
}
