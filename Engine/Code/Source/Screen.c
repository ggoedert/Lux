#include <stdlib.h>
#include <string.h>
#include <conio.h> 

#include <peekpoke.h> 

#include "LuxEngine.h"

#include "Screen.h"

#define CLR80COL  0xC000    // disable 80-column store
#define SET80COL  0xC001    // enable 80-column store
#define CLR80VID  0xC00C    // disable 80-column display mode
#define SET80VID  0xC00D    // enable 80-column display mode
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

#pragma optimize (push,off)
void maintoaux(unsigned src0, unsigned src1, unsigned dest0) {
    unsigned *src  = (unsigned *)0x3c;
    unsigned *dest = (unsigned *)0x42;
    src[0] = src0;
    src[1] = src1;
    dest[0] = dest0;
    asm("sec");
    asm("jsr $c311");
}
#pragma optimize (pop)

void lux_Screen_Init() {
    if (lux_Application.machine < IIe)
        lux_Screen_resolutions_Length = 5;
    else
        lux_Screen_resolutions_Length = 10;
    memset((void*)0x0400, 0xa0, 0x0400);
    memset((void*)0x2000, 0x00, 0x2000);
    if (lux_Application.machine >= IIe) {
        POKE(SET80COL, 0);
        POKE(TXTPAGE2, 0);
        memset((void*)0x0400, 0xa0, 0x0400);
        POKE(TXTPAGE1, 0);
        POKE(CLR80COL, 0);
        maintoaux(0x2000, 0x4000, 0x2000);
    }
    gotoy(22);
}

void lux_Screen_resolutions_Get(Lux_Resolution** lux_Screen_resolutions) {
    *lux_Screen_resolutions = malloc(sizeof(Lux_Resolution)*lux_Screen_resolutions_Length);
    (*lux_Screen_resolutions)[0].mode = TEXT;
    (*lux_Screen_resolutions)[0].doubleRes = false;
    (*lux_Screen_resolutions)[0].mixed = false;
    (*lux_Screen_resolutions)[1].mode = GR;
    (*lux_Screen_resolutions)[1].doubleRes = false;
    (*lux_Screen_resolutions)[1].mixed = false;
    (*lux_Screen_resolutions)[2].mode = GR;
    (*lux_Screen_resolutions)[2].doubleRes = false;
    (*lux_Screen_resolutions)[2].mixed = true;
    (*lux_Screen_resolutions)[3].mode = HGR;
    (*lux_Screen_resolutions)[3].doubleRes = false;
    (*lux_Screen_resolutions)[3].mixed = false;
    (*lux_Screen_resolutions)[4].mode = HGR;
    (*lux_Screen_resolutions)[4].doubleRes = false;
    (*lux_Screen_resolutions)[4].mixed = true;
    if (lux_Application.machine >= IIe) {
        (*lux_Screen_resolutions)[5].mode = TEXT;
        (*lux_Screen_resolutions)[5].doubleRes = true;
        (*lux_Screen_resolutions)[5].mixed = false;
        (*lux_Screen_resolutions)[6].mode = GR;
        (*lux_Screen_resolutions)[6].doubleRes = true;
        (*lux_Screen_resolutions)[6].mixed = false;
        (*lux_Screen_resolutions)[7].mode = GR;
        (*lux_Screen_resolutions)[7].doubleRes = true;
        (*lux_Screen_resolutions)[7].mixed = true;
        (*lux_Screen_resolutions)[8].mode = HGR;
        (*lux_Screen_resolutions)[8].doubleRes = true;
        (*lux_Screen_resolutions)[8].mixed = false;
        (*lux_Screen_resolutions)[9].mode = HGR;
        (*lux_Screen_resolutions)[9].doubleRes = true;
        (*lux_Screen_resolutions)[9].mixed = true;
    }
}

void lux_Screen_SetResolution(byte mode, bool doubleRes, bool mixed) {
    switch(mode) {
        case TEXT:
            POKE(CLRHIRES, 0);
            POKE(SETTEXT, 0);
            if (lux_Application.machine >= IIe) {
                POKE(SETIOUDIS, 0);
                POKE(CLRDHIRES, 0);
                if (doubleRes) {
                    POKE(SET80COL, 0);
                    POKE(SET80VID, 0);
                }
                else {
                    POKE(CLR80COL, 0);
                    POKE(CLR80VID, 0);
                }
            }
            POKE(CLRMIXED, 0);
            break;
        case GR:
            POKE(CLRHIRES, 0);
            POKE(CLRTEXT, 0);
            POKE(CLR80COL, 0);
            if (lux_Application.machine >= IIe) {
                POKE(SETIOUDIS, 0);
                if (doubleRes) {
                    POKE(SETDHIRES, 0);
                    POKE(SET80VID, 0);
                }
                else {
                    POKE(CLRDHIRES, 0);
                    POKE(CLR80VID, 0);
                }
            }
            if (!mixed)
                POKE(CLRMIXED, 0);
            else
                POKE(SETMIXED, 0);
            break;
        case HGR:
            POKE(SETHIRES, 0);
            POKE(CLRTEXT, 0);
            POKE(CLR80COL, 0);
            if (lux_Application.machine >= IIe) {
                POKE(SETIOUDIS, 0);
                if (doubleRes) {
                    POKE(SETDHIRES, 0);
                    POKE(SET80VID, 0);
                }
                else {
                    POKE(CLRDHIRES, 0);
                    POKE(CLR80VID, 0);
                }
            }
            if (!mixed)
                POKE(CLRMIXED, 0);
            else
                POKE(SETMIXED, 0);
            break;
    }
    POKE(TXTPAGE1, 0);
}
