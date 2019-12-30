#include "IO.h"

void auxmove(word start, word end, word dest) {
    POKEW(STARTSOU, start);
    POKEW(ENDSOU, end);
    POKEW(DEST, dest);
    asm("sec");
    asm("jsr %w", AUXMOVE);
}
