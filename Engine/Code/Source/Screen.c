#include <stdbool.h>
#include <string.h>
#include <conio.h> 

#include "IO.h"
#include "Screen.h"
#include "Vaporlock.h"

#include "LuxApplication.h"
#include "LuxCamera.h"
#include "LuxScreen.h"

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
void PutFragmentDHGR(byte *data, byte width, byte height, byte x, byte y) {
    byte y2 = y+height, packet = width/2, yb;
    byte *source = data, *dest;
    bool log=false;

    byte a, b, c, d, e, f, g, z, *put, col;
    byte blit[128], count;
    bool flag;
    packet = width/7*4;
    if (width%7)
        packet+=2;

    // rasters are split between auxiliary memory and main memory
    while (y < y2) {
        put = blit;
        count = 0;
        flag = false;//good
        for (col=0; col<width; ++col) {
            ++count;
            if (count == 4) {
                a = source[col-3]>>4;
                b = source[col-3]&0xf;
                c = source[col-2]>>4;
                d = source[col-2]&0xf;
                e = source[col-1]>>4;
                f = source[col-1]&0xf;
                g = source[col]>>4;
                z = source[col]&0xf;
                flag = true;
            }
            else if (count == 7) {
                a = z;
                b = source[col-2]>>4;
                c = source[col-2]&0xf;
                d = source[col-1]>>4;
                e = source[col-1]&0xf;
                f = source[col]>>4;
                g = source[col]&0xf;
                flag = true;
                count = 0;
            }
            if (flag) {
                put[0] = (b<<4)|a;
                put[packet+0] = (d<<5)|(c<<1)|(b>>3);
                put[1] = (f<<6)|(e<<2)|(d>>2);
                put[packet+1] = (g<<3)|(f>>1);
                put += 2;
                flag = false;
            }
        }
        count = width%7;
        if (count) {
            col = width-count;
            a = source[col]>>4;
            b = source[col++]&0xf;
            put[0] = (b<<4)|a;
            if (col<width) {
                c = source[col]>>4;
                d = source[col++]&0xf;
            }
            else {
                c = 0;
                d = 0;
            }
            put[packet+0] = (d<<5)|(c<<1)|(b>>3);
            if (col<width) {
                e = source[col]>>4;
                f = source[col++]&0xf;
            }
            else {
                e = 0;
                f = 0;
            }
            put[1] = (f<<6)|(e<<2)|(d>>2);
            if (col<width) {
                g = source[col]>>4;
                z = source[col++]&0xf;
            }
            else {
                g = 0;
                z = 0;
            }
            put[packet+1] = (g<<3)|(f>>1);
        }
        log=false;

        yb = y/8;
        dest = (byte *)((y%8)*0x400+(yb%8)*0x80+(yb/8)*0x28+(x/2)+0x2000);
        toaux((word)dest, (word)blit, packet);
        memcpy(dest, blit+packet, packet);
        source += width;
        ++y;
    }
}

void Screen_DrawSprite(byte *data, byte width, byte height, byte x, byte y) {
    if (Screen_currentResolution.doubleRes)
        PutFragmentDHGR(data, width, height, x, y);
}
