#include <stdbool.h>
#include <string.h>
#include <conio.h> 
#include <peekpoke.h> 

#include "Screen.h"
#include "Vaporlock.h"

#include "LuxApplication.h"
#include "LuxScreen.h"

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

Resolution Screen_resolutions[] = {
    {TEXT, false, false},
    {GR, false, false},
    {GR, false, true},
    {HGR, false, false},
    {HGR, false, true},
    {TEXT, true, false},
    {GR, true, false},
    {GR, true, true},
    {HGR, true, false},
    {HGR, true, true}
};

byte Screen_resolutions_Length;

Resolution Screen_currentResolution;

void auxmove(word start, word end, word dest) {
    POKEW(STARTSOU, start);
    POKEW(ENDSOU, end);
    POKEW(DEST, dest);
    asm("sec");
    asm("jsr %w", AUXMOVE);
}

void Screen_Init() {
    if (application.machine < IIe)
        Screen_resolutions_Length = 5;
    else
        Screen_resolutions_Length = 10;
    Screen_currentResolution = Screen_resolutions[0];
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

void Screen_SetResolutionInternal() {
    switch(Screen_currentResolution.mode) {
        case TEXT:
            POKE(CLRHIRES, 0);
            POKE(SETTEXT, 0);
            if (application.machine >= IIe) {
                POKE(SETIOUDIS, 0);
                POKE(CLRDHIRES, 0);
                if (Screen_currentResolution.doubleRes) {
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
                if (Screen_currentResolution.doubleRes) {
                    POKE(SETDHIRES, 0);
                    POKE(SET80VID, 0);
                }
                else {
                    POKE(CLRDHIRES, 0);
                    POKE(CLR80VID, 0);
                }
            }
            if (!Screen_currentResolution.mixed)
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
                if (Screen_currentResolution.doubleRes) {
                    POKE(SETDHIRES, 0);
                    POKE(SET80VID, 0);
                }
                else {
                    POKE(CLRDHIRES, 0);
                    POKE(CLR80VID, 0);
                }
            }
            if (!Screen_currentResolution.mixed)
                POKE(CLRMIXED, 0);
            else
                POKE(SETMIXED, 0);
            break;
    }
    POKE(TXTPAGE1, 0);
}

void Screen_SetResolution(byte mode, bool doubleRes, bool mixed) {
    int index;
    for (index = 0; index<Screen_resolutions_Length; index++) {
        if ((Screen_resolutions[index].mode == mode) && (Screen_resolutions[index].doubleRes == doubleRes) && (Screen_resolutions[index].mixed == mixed)) {
            Screen_currentResolution = Screen_resolutions[index];
            Screen_SetResolutionInternal();
            VaporlockSetup();
            return;
        }
    }
}

void Screen_WaitVBlank() {
    if (application.machine == IIe) {          // this optimization only works on the original IIe
        while ((PEEK(RDVBLBAR)&0x80)==0x0) {}  // wait current vblank to end, if already inside it
        while ((PEEK(RDVBLBAR)&0x80)!=0x0) {}  // wait new vblank to start
    }
    else {
        bool setupScreen = (Screen_currentResolution.mode != HGR) || (Screen_currentResolution.doubleRes != false) || (Screen_currentResolution.mixed != false);
        if (setupScreen) {
            POKE(SETHIRES, 0);
            POKE(CLRTEXT, 0);
            POKE(CLR80COL, 0);
            if (application.machine >= IIe) {
                POKE(SETIOUDIS, 0);
                POKE(CLRDHIRES, 0);
                POKE(CLR80VID, 0);
            }
            POKE(CLRMIXED, 0);
            POKE(TXTPAGE1, 0);
        }
        Vaporlock();
        if (setupScreen)
            Screen_SetResolutionInternal();
    }
}
