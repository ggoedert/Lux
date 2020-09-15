#include <stdbool.h>
#include <string.h>
#include <conio.h> 

#include "IO.h"
#include "Screen.h"
#include "Vaporlock.h"

#include "LuxApplication.h"
#include "LuxCamera.h"
#include "LuxScreen.h"
#include "LuxSprite.h"

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

// Table to translate a dhgr color to a similar hgr color
// * Two highest bits: page index
//   01 -> page 0
//   11 -> page 1
//   00 -> either page
//   10 -> either page
// * Two lowest bits: color index
byte dhgr2hgr[] = {
    0x00, 0x01, 0x02, 0x81, 0x00, 0x81, 0x02, 0x81, 0x82, 0x01, 0x81, 0x83, 0x82, 0x01, 0x02, 0x83
};

void Screen_Init() {
    byte *ptr;

    if (application.machine < IIe)
        Screen_resolutions_Length = 5;
    else
        Screen_resolutions_Length = 10;
    Screen_currentResolution = Screen_resolutions[0];
    for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
        memset(ptr, 0xA0, 0x78);
    memset((void *)0x2000, 0x00, 0x2000);
    if (application.machine >= IIe) {
        FASTPOKE(SET80COL);
        FASTPOKE(TXTPAGE2);
        for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
            memset(ptr, 0xA0, 0x78);
        FASTPOKE(TXTPAGE1);
        FASTPOKE(CLR80COL);
        toaux(0x2000, 0x2000, 0x2000);
    }
    if (application.machine != IIe) // this is not needed on the IIe
        VaporlockSetup();
    gotoy(-1);
}

void Screen_SetResolutionInternal() {
    switch(Screen_currentResolution.mode) {
        case TEXT:
            FASTPOKE(CLRHIRES);
            FASTPOKE(SETTEXT);
            if (application.machine >= IIe) {
                FASTPOKE(SETIOUDIS);
                FASTPOKE(CLRDHIRES);
                if (Screen_currentResolution.doubleRes) {
                    FASTPOKE(SET80COL);
                    FASTPOKE(SET80VID);
                }
                else {
                    FASTPOKE(CLR80COL);
                    FASTPOKE(CLR80VID);
                }
            }
            FASTPOKE(CLRMIXED);
            break;
        case GR:
            FASTPOKE(CLRHIRES);
            FASTPOKE(CLRTEXT);
            FASTPOKE(CLR80COL);
            if (application.machine >= IIe) {
                FASTPOKE(SETIOUDIS);
                if (Screen_currentResolution.doubleRes) {
                    FASTPOKE(SETDHIRES);
                    FASTPOKE(SET80VID);
                }
                else {
                    FASTPOKE(CLRDHIRES);
                    FASTPOKE(CLR80VID);
                }
            }
            if (!Screen_currentResolution.mixed)
                FASTPOKE(CLRMIXED);
            else
                FASTPOKE(SETMIXED);
            break;
        case HGR:
            FASTPOKE(SETHIRES);
            FASTPOKE(CLRTEXT);
            FASTPOKE(CLR80COL);
            if (application.machine >= IIe) {
                FASTPOKE(SETIOUDIS);
                if (Screen_currentResolution.doubleRes) {
                    FASTPOKE(SETDHIRES);
                    FASTPOKE(SET80VID);
                }
                else {
                    FASTPOKE(CLRDHIRES);
                    FASTPOKE(CLR80VID);
                }
            }
            if (!Screen_currentResolution.mixed)
                FASTPOKE(CLRMIXED);
            else
                FASTPOKE(SETMIXED);
            break;
    }
    FASTPOKE(TXTPAGE1);
}

void Screen_Clear() {
    byte *ptr;
    int size;

    if ((Screen_currentResolution.mode != HGR) || Screen_currentResolution.mixed) {
        for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
            memset(ptr, 0xA0, 0x78);
        if ((application.machine >= IIe) && (Screen_currentResolution.doubleRes)) {
            FASTPOKE(SET80COL);
            FASTPOKE(TXTPAGE2);
            for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
                memset(ptr, 0xA0, 0x78);
            FASTPOKE(TXTPAGE1);
            FASTPOKE(CLR80COL);
        }
    }
    if (Screen_currentResolution.mode == HGR) {
        if ((application.machine < IIe) || (!Screen_currentResolution.doubleRes)) {
            byte a = dhgr2hgr[Camera_backgroundColor];
            byte p = a&0x80;
            byte ci = a&0x3;
            byte b;
            a = p|((ci&0x1)<<6)|(ci<<4)|(ci<<2)|ci;
            b = p|(ci<<5)|(ci<<3)|(ci<<1)|(ci>>1);
            
            if (a==b)
                memset((void *)0x2000, a, 0x2000);
            else {
                ptr = (byte *)0x2000;
                *ptr++ = a;
                *ptr++ = b;
                do {
                    size = ptr-(byte *)0x2000;
                    memcpy(ptr, (byte *)0x2000, size);
                    ptr += size;
                } while (ptr<(byte *)0x4000);
            }
        }
        else {
            byte a, b, c, d;
            a = ((Camera_backgroundColor&0x7)<<4)|Camera_backgroundColor;
            b = ((Camera_backgroundColor&0x3)<<5)|(Camera_backgroundColor<<1)|(Camera_backgroundColor>>3);
            c = ((Camera_backgroundColor&0x1)<<6)|(Camera_backgroundColor<<2)|(Camera_backgroundColor>>2);
            d = (Camera_backgroundColor<<3)|(Camera_backgroundColor>>1);
            
            if ((a==b) && (a==c) && (a==d)) {
                memset((void *)0x2000, a, 0x2000);
                toaux(0x2000, 0x2000, 0x2000);
            }
            else {
                ptr = (byte *)0x2000;
                *ptr++ = a;
                *ptr++ = c;
                do {
                    size = ptr-(byte *)0x2000;
                    memcpy(ptr, (byte *)0x2000, size);
                    ptr += size;
                } while (ptr<(byte *)0x4000);
                toaux(0x2000, 0x2000, 0x2000);
                
                if ((a!=b) || (c!=d)) {
                    ptr = (byte *)0x2000;
                    *ptr++ = b;
                    *ptr++ = d;
                    do {
                        size = ptr-(byte *)0x2000;
                        memcpy(ptr, (byte *)0x2000, size);
                        ptr += size;
                    } while (ptr<(byte *)0x4000);
                }
            }
        }
    }
    if (application.machine != IIe) // this is not needed on the IIe
        VaporlockSetup();
}

void Screen_SetResolution(byte mode, bool doubleRes, bool mixed) {
    int index;
    if (application.machine < IIe)
        doubleRes = false;
    for (index = 0; index<Screen_resolutions_Length; ++index) {
        if ((Screen_resolutions[index].mode == mode) && (Screen_resolutions[index].doubleRes == doubleRes) && (Screen_resolutions[index].mixed == mixed)) {
            Screen_currentResolution = Screen_resolutions[index];
            Screen_Clear();
            Screen_SetResolutionInternal();
            return;
        }
    }
}

void Screen_WaitVBlank() {
    if (application.machine == IIe) {          // this optimization only works on the IIe
        while ((PEEK(RDVBLBAR)&0x80)==0x0) {}  // if already inside a vblank, wait for it to end
        while ((PEEK(RDVBLBAR)&0x80)!=0x0) {}  // wait for a new vblank to start
    }
    else {
        bool setupScreen = (Screen_currentResolution.mode != HGR) || (Screen_currentResolution.doubleRes != false) || (Screen_currentResolution.mixed != false);
        if (setupScreen) {
            FASTPOKE(SETHIRES);
            FASTPOKE(CLRTEXT);
            FASTPOKE(CLR80COL);
            if (application.machine >= IIe) {
                FASTPOKE(SETIOUDIS);
                FASTPOKE(CLRDHIRES);
                FASTPOKE(CLR80VID);
            }
            FASTPOKE(CLRMIXED);
            FASTPOKE(TXTPAGE1);
        }
        Vaporlock();
        if (setupScreen)
            Screen_SetResolutionInternal();
    }
}

// simple putimage function for this demo, does not preserve the background
void PutFragmentDHGR(Sprite *sprite, byte x, byte y) {
    // rasters are split between auxiliary memory and main memory
    byte *source = sprite->data, *dest;
    byte packSize, y2 = y+sprite->height, yb;
    packSize = sprite->width/7*4;
    if (sprite->width%7)
        packSize+=2;
    while (y < y2) {
        yb = y/8;
        dest = (byte *)((y%8)*0x400+(yb%8)*0x80+(yb/8)*0x28+(x/2)+0x2000);
        toaux((word)dest, (word)source, packSize);
        memcpy(dest, source+packSize, packSize);
        source += 2*packSize;
        ++y;
    }
}

void Screen_DrawSprite(Sprite *sprite, byte x, byte y) {
    if (Screen_currentResolution.doubleRes)
        PutFragmentDHGR(sprite, x, y);
}
