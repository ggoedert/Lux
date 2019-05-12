#ifndef L_APPLE2ID_H
#define L_APPLE2ID_H

typedef struct {
   unsigned char machine;  // the type of Apple II
   unsigned char romlevel; // which revision of the machine
   unsigned char memory;   // how much memory (up to 128K)
} Apple2Id;

void GetApple2Id(Apple2Id* apple2Id);
