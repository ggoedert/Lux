#ifndef APPLE2ID_H
#define APPLE2ID_H

#include "LuxTypes.h"

class (Apple2Id,
    byte machine;  // the type of Apple II
    byte romlevel; // which revision of the machine
    byte memory;   // how much memory (up to 128K)
);

void GetApple2Id(Apple2Id *apple2Id);

#endif
