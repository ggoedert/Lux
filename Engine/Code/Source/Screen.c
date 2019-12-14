#include <string.h>
#include <conio.h> 
#include <peekpoke.h> 

#include "Screen.h"

#include "LuxApplication.h"
#include "LuxScreen.h"

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

#define STARTSOU  0x003C
#define ENDSOU    0x003E
#define DEST      0x0042
#define AUXMOVE   0xC311    // C=0 Aux->Main, C=1 Main->Aux 
#define MOVE      0xFE2C    // Main<->Main, *MUST* set Y=0 prior! 

void auxmove(word start, word end, word dest) {
    POKE(STARTSOU, start);
    POKE(ENDSOU, end);
    POKE(DEST, dest);
    asm("sec");
    asm("jsr %w", AUXMOVE);
}

void Screen_Init() {
    if (application.machine < IIe)
        Screen_resolutions_Length = 5;
    else
        Screen_resolutions_Length = 10;
    memset((void *)0x0400, 0xA0, 0x0400);
    memset((void *)0x2000, 0x00, 0x2000);
    if (application.machine >= IIe) {
        POKE(SET80COL, 0);
        POKE(TXTPAGE2, 0);
        memset((void *)0x0400, 0xA0, 0x0400);
        POKE(TXTPAGE1, 0);
        POKE(CLR80COL, 0);
        auxmove(0x2000, 0x3FFF, 0x2000);
    }
    gotoy(22);
}

void Screen_resolutions_Get(Resolution **screen_resolutions) {
    *screen_resolutions = malloc(sizeof(Resolution)*Screen_resolutions_Length);
    (*screen_resolutions)[0].mode = TEXT;
    (*screen_resolutions)[0].doubleRes = false;
    (*screen_resolutions)[0].mixed = false;
    (*screen_resolutions)[1].mode = GR;
    (*screen_resolutions)[1].doubleRes = false;
    (*screen_resolutions)[1].mixed = false;
    (*screen_resolutions)[2].mode = GR;
    (*screen_resolutions)[2].doubleRes = false;
    (*screen_resolutions)[2].mixed = true;
    (*screen_resolutions)[3].mode = HGR;
    (*screen_resolutions)[3].doubleRes = false;
    (*screen_resolutions)[3].mixed = false;
    (*screen_resolutions)[4].mode = HGR;
    (*screen_resolutions)[4].doubleRes = false;
    (*screen_resolutions)[4].mixed = true;
    if (application.machine >= IIe) {
        (*screen_resolutions)[5].mode = TEXT;
        (*screen_resolutions)[5].doubleRes = true;
        (*screen_resolutions)[5].mixed = false;
        (*screen_resolutions)[6].mode = GR;
        (*screen_resolutions)[6].doubleRes = true;
        (*screen_resolutions)[6].mixed = false;
        (*screen_resolutions)[7].mode = GR;
        (*screen_resolutions)[7].doubleRes = true;
        (*screen_resolutions)[7].mixed = true;
        (*screen_resolutions)[8].mode = HGR;
        (*screen_resolutions)[8].doubleRes = true;
        (*screen_resolutions)[8].mixed = false;
        (*screen_resolutions)[9].mode = HGR;
        (*screen_resolutions)[9].doubleRes = true;
        (*screen_resolutions)[9].mixed = true;
    }
}

void Screen_SetResolution(byte mode, bool doubleRes, bool mixed) {
    switch(mode) {
        case TEXT:
            POKE(CLRHIRES, 0);
            POKE(SETTEXT, 0);
            if (application.machine >= IIe) {
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
            if (application.machine >= IIe) {
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
            if (application.machine >= IIe) {
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
