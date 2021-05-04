#include "IO.h"

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
