#ifndef SCREEN_H
#define SCREEN_H

#ifdef __CC65__
#include <peekpoke.h>
#define FASTPOKE(addr) asm("sta %w", addr)
#endif

#include "LuxTypes.h"

#ifndef IO_EXTERNAL
#define IO_EXTERNAL extern
#endif

#ifdef __CC65__
#define MEMORY(a) a
#else
IO_EXTERNAL byte *memoryMain, *memoryAux;
#define MEMORY(a) (memoryMain+(int)a)
#endif

#define CLR80COL  0xC000    // disable 80-column store
#define SET80COL  0xC001    // enable 80-column store
#define CLR80VID  0xC00C    // disable 80-column display mode
#define SET80VID  0xC00D    // enable 80-column display mode
#define RDVBLBAR  0xC019    // not VBL (VBL signal low) on iie
#define CLRTEXT   0xC050    // disable text-only mode
#define SETTEXT   0xC051    // enable text-only mode
#define CLRMIXED  0xC052    // disable graphics/text mixed mode
#define SETMIXED  0xC053    // enable graphics/text mixed mode
#define TXTPAGE1  0xC054    // switch in page 1
#define TXTPAGE2  0xC055    // switch in page 2
#define CLRHIRES  0xC056    // disable hr graphics
#define SETHIRES  0xC057    // enable hr graphics
#define SETDHIRES 0xC05E    // turn on dhr graphics
#define CLRDHIRES 0xC05F    // turn off dhr graphics
#define SETIOUDIS 0xC07E    // turn on IOUDis access for addresses $C058 to $C05F
#define CLRIOUDIS 0xC07F    // turn off IOUDis access for addresses $C058 to $C05F

#define STARTSOU  0x003C
#define ENDSOU    0x003E
#define DEST      0x0042

#define AUXMOVE   0xC311    // C=0 Aux->Main, C=1 Main->Aux 
#define MOVE      0xFE2C    // Main<->Main, *MUST* set Y=0 prior! 

#ifdef __CC65__
void toaux(word dest, word src, word count);
void fromaux(word dest, word src, word count);
#else
void toaux(word dest, byte *src, word count);
void fromaux(byte *dest, word src, word count);
#endif

#endif
