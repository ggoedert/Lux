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
void toaux(word dest, word src, word count) {
}

void fromaux(word dest, word src, word count) {
}
#endif
