#ifndef __CC65__
#include <string.h>
#endif

#define IO_EXTERNAL
#include "IO.h"

#ifdef __CC65__
void toaux(word dest, word src, word count) {
    POKEW(STARTSOU, src);
    POKEW(ENDSOU, src+count-1);
    POKEW(DEST, dest);
    asm("sec");
    asm("jsr %w", AUXMOVE);
}

void fromaux(word dest, word src, word count) {
    POKEW(STARTSOU, src);
    POKEW(ENDSOU, src+count-1);
    POKEW(DEST, dest);
    asm("clc");
    asm("jsr %w", AUXMOVE);
}
#else
void toaux(word dest, byte *src, word count) {
    memcpy(memoryAux+dest, src, count);
}

void fromaux(byte *dest, word src, word count) {
    memcpy(dest, memoryAux+src, count);
}
#endif
