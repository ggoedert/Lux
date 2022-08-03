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
#include "LuxCollections.h"

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

// Compact version of the hgr base table, used to accelerate hgr line address calculation, slightly slower but 8 times smaller then the full table
static word hgrBase[] = {
    0x2000, 0x2080, 0x2100, 0x2180, 0x2200, 0x2280, 0x2300, 0x2380,
    0x2028, 0x20A8, 0x2128, 0x21A8, 0x2228, 0x22A8, 0x2328, 0x23A8,
    0x2050, 0x20D0, 0x2150, 0x21D0, 0x2250, 0x22D0, 0x2350, 0x23D0
};

class (Segment,
    byte start, packet;
    byte *data;
);
List lines[192];

void Screen_Init() {
    int index;
#ifdef __CC65__
    byte *ptr;

    if (application.machine < IIe)
        Screen_resolutions_Length = 5;
    else
        Screen_resolutions_Length = 10;
    Screen_currentResolution = Screen_resolutions[0];
    for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
        memset(MEMORY(ptr), 0xA0, 0x78);
    memset((void *)MEMORY(0x2000), 0x00, 0x2000);
    if (application.machine >= IIe) {
        FASTPOKE(SET80COL);
        FASTPOKE(TXTPAGE2);
        for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
            memset(MEMORY(ptr), 0xA0, 0x78);
        FASTPOKE(TXTPAGE1);
        FASTPOKE(CLR80COL);
        toaux(0x2000, MEMORY(0x2000), 0x2000);
    }
    if (application.machine != IIe) // this is not needed on the IIe
        VaporlockSetup();
    gotoy(-1);
#else
    Screen_resolutions_Length = 10;
    memoryMain = calloc(0xFFFF, sizeof(byte));
    memoryAux = calloc(0xFFFF, sizeof(byte));
#endif

    for (index = 0; index<192; ++index)
        List_Constructor(lines+index, sizeof(Segment));
}

#ifndef __CC65__
void Screen_Finalize() {
    int i, y2;
    for (y2=0; y2<192; ++y2) {
        if (lines[y2].count) {
            for (i=0; i<lines[y2].count; ++i) {
                free(List_ItemPtr(lines+y2, Segment, i)->data);
            }
        }
        List_Destructor(lines+y2);
    }
}
#endif

void Screen_SetResolutionInternal() {
#ifdef __CC65__
    switch (Screen_currentResolution.mode) {
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
#endif
}

void Screen_Clear() {
    byte *ptr;
    int size, y2, i;

#ifdef __CC65__
    if ((Screen_currentResolution.mode != HGR) || Screen_currentResolution.mixed) {
        for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
            memset(MEMORY(ptr), 0xA0, 0x78);
        if ((application.machine >= IIe) && (Screen_currentResolution.doubleRes)) {
            FASTPOKE(SET80COL);
            FASTPOKE(TXTPAGE2);
            for (ptr=(byte *)0x0400; ptr<(byte *)0x0800; ptr+=0x80)
                memset(MEMORY(ptr), 0xA0, 0x78);
            FASTPOKE(TXTPAGE1);
            FASTPOKE(CLR80COL);
        }
    }
#endif
    if (Screen_currentResolution.mode == HGR) {
        if ((application.machine < IIe) || (!Screen_currentResolution.doubleRes)) {
            byte a = dhgr2hgr[Camera_backgroundColor];
            byte p = a&0x80;
            byte ci = a&0x3;
            byte b;
            a = p|((ci&0x1)<<6)|(ci<<4)|(ci<<2)|ci;
            b = p|(ci<<5)|(ci<<3)|(ci<<1)|(ci>>1);

            if (a==b)
                memset((void *)MEMORY(0x2000), a, 0x2000);
            else {
                ptr = (byte *)MEMORY(0x2000);
                *ptr++ = a;
                *ptr++ = b;
                do {
                    size = ptr-(byte *)MEMORY(0x2000);
                    memcpy(ptr, (byte *)MEMORY(0x2000), size);
                    ptr += size;
                } while (ptr<(byte *)MEMORY(0x4000));
            }
        }
        else {
            byte a, b, c, d;
            a = ((Camera_backgroundColor&0x7)<<4)|Camera_backgroundColor;
            b = ((Camera_backgroundColor&0x3)<<5)|(Camera_backgroundColor<<1)|(Camera_backgroundColor>>3);
            c = ((Camera_backgroundColor&0x1)<<6)|(Camera_backgroundColor<<2)|(Camera_backgroundColor>>2);
            d = (Camera_backgroundColor<<3)|(Camera_backgroundColor>>1);

            if ((a==b) && (a==c) && (a==d)) {
                memset((void *)MEMORY(0x2000), a, 0x2000);
                toaux(0x2000, MEMORY(0x2000), 0x2000);
            }
            else {
                ptr = (byte *)MEMORY(0x2000);
                *ptr++ = a;
                *ptr++ = c;
                do {
                    size = ptr-(byte *)MEMORY(0x2000);
                    memcpy(ptr, (byte *)MEMORY(0x2000), size);
                    ptr += size;
                } while (ptr<(byte *)MEMORY(0x4000));
                toaux(0x2000, MEMORY(0x2000), 0x2000);

                if ((a!=b) || (c!=d)) {
                    ptr = (byte *)MEMORY(0x2000);
                    *ptr++ = b;
                    *ptr++ = d;
                    do {
                        size = ptr-(byte *)MEMORY(0x2000);
                        memcpy(ptr, (byte *)MEMORY(0x2000), size);
                        ptr += size;
                    } while (ptr<(byte *)MEMORY(0x4000));
                }
            }
        }
    }
#ifdef __CC65__
    if (application.machine != IIe) // this is not needed on the IIe
        VaporlockSetup();
#endif

    for (y2=0; y2<192; ++y2) {
        if (lines[y2].count) {
            for (i=0; i<lines[y2].count; ++i) {
                free(List_ItemPtr(lines+y2, Segment, i)->data);
            }
        }
        List_Clear(lines+y2);
    }
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
    int y2, x2, packet, i;
    byte *screenData, *dest, *destx2;

#ifdef __CC65__
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
#endif

    for (y2=0; y2<192; ++y2) {
        if (lines[y2].count) {
            dest = (byte *)hgrBase[y2>>3]+(y2&7)*0x400;
            for (i=0; i<lines[y2].count; ++i) {
                x2 = List_ItemPtr(lines+y2, Segment, i)->start;
                packet = List_ItemPtr(lines+y2, Segment, i)->packet;
                screenData = List_ItemPtr(lines+y2, Segment, i)->data;

                destx2 = dest+x2;

                toaux((word)destx2, screenData, packet);
                memcpy(MEMORY(destx2), screenData+packet, packet);
                free(screenData);
            }
            List_Clear(lines+y2);
        }
    }
}

// simple putimage function for this demo
void PutFragmentDHGR(Sprite *sprite, byte mask, byte x, byte y) {
    byte halfWidth;
    byte y2, x2, packet;
    byte *dest, *spriteData, *screenData;
    Segment seg;

    halfWidth = sprite->width/2;
    packet = halfWidth/7*4;
    if (halfWidth%7)
        packet+=2;
    spriteData = sprite->data;

    x2 = x/7*2;
    for (y2=y; y2<(y+sprite->height); ++y2) {
        dest = (byte *)hgrBase[y2>>3]+(y2&7)*0x400+x2;

        //?mask?
        screenData = malloc(packet*2);
        fromaux(screenData, (word)dest, packet);
        memcpy(screenData+packet, MEMORY(dest), packet);
        seg.start = x2;
        seg.packet = packet;
        seg.data = screenData;
        List_Add(lines+y2, Segment, seg);
        //

        toaux((word)dest, spriteData, packet);
        memcpy(MEMORY(dest), spriteData+packet, packet);

        spriteData += packet*2;
    }
}

void Screen_DrawSprite(Sprite *sprite, byte mask, byte x, byte y) {

    /*
    sprite_id = find_sprite_id(sprite);
    invalidate_area = clean_area()
    if (sprite_id >= 0)
        invalidate_area_add(sprite_id_area(sprite_id))
    else
        sprite_id = create_sprite_id(sprite)
    invalidate_area_add(set_sprite_id_area(sprite_id, x, y))
    draw(invalidate_area_add)
    */

    if (Screen_currentResolution.doubleRes)
        PutFragmentDHGR(sprite, mask, x, y);
}
