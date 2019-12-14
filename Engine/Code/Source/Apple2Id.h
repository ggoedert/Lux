#ifndef APPLE2ID_H
#define APPLE2ID_H

#include "LuxDefs.h"

typedef struct {
    byte machine;  // the type of Apple II
    byte romlevel; // which revision of the machine
    byte memory;   // how much memory (up to 128K)
} Apple2Id;

void GetApple2Id(Apple2Id *apple2Id);
