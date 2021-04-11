#include <string.h>

#include "LuxSprite.h"

class_default_implementations(Sprite, (byte *texture2D), (texture2D),
    (
        byte mask = -1;//??????????????????

        byte halfWidth;
        byte xo, yo, packet;
        byte *source, *spriteData;
        byte a, b, c, d, e, f, g, z, *put, count;
        byte m, am, bm, cm, dm, em, fm, gm;
        bool flag;
        byte yb;

        this->width = *texture2D++;
        this->height = *texture2D++;

        halfWidth = this->width/2;
        packet = halfWidth/7*4;
        if (halfWidth%7)
            packet+=2;
        this->dest = malloc(packet*2*this->height);

        // rasters are split between auxiliary memory and main memory
        source = texture2D;
        for (yo=0; yo<this->height; ++yo) {

            yb = yo/8;
            spriteData = this->dest+(packet*2*yo);

            put = spriteData;
            count = 0;
            flag = false;//good
            for (xo=0; xo<halfWidth; ++xo) {
                ++count;
                if (count == 4) {
                    a = source[xo-3]>>4;
                    b = source[xo-3]&0xf;
                    c = source[xo-2]>>4;
                    d = source[xo-2]&0xf;
                    e = source[xo-1]>>4;
                    f = source[xo-1]&0xf;
                    g = source[xo]>>4;
                    z = source[xo]&0xf;
                    flag = true;
                }
                else if (count == 7) {
                    a = z;
                    b = source[xo-2]>>4;
                    c = source[xo-2]&0xf;
                    d = source[xo-1]>>4;
                    e = source[xo-1]&0xf;
                    f = source[xo]>>4;
                    g = source[xo]&0xf;
                    flag = true;
                    count = 0;
                }
                am = a!=mask?0xf:0x0;
                bm = b!=mask?0xf:0x0;
                cm = c!=mask?0xf:0x0;
                dm = d!=mask?0xf:0x0;
                em = e!=mask?0xf:0x0;
                fm = f!=mask?0xf:0x0;
                gm = g!=mask?0xf:0x0;
                if (flag) {
                    m = (bm<<4)|am;
                    put[0] &= ~m;
                    put[0] |= ((b<<4)|a)&m;
                    m = (dm<<5)|(cm<<1)|(bm>>3);
                    put[packet+0] &= ~m;
                    put[packet+0] |= ((d<<5)|(c<<1)|(b>>3))&m;
                    m = (fm<<6)|(em<<2)|(dm>>2);
                    put[1] &= ~m;
                    put[1] |= ((f<<6)|(e<<2)|(d>>2))&m;
                    m = (gm<<3)|(fm>>1);
                    put[packet+1] &= ~m;
                    put[packet+1] |= ((g<<3)|(f>>1))&m;
                    put += 2;
                    flag = false;
                }
            }
            count = halfWidth%7;
            if (count) {
                xo = halfWidth-count;
                a = source[xo]>>4;
                b = source[xo++]&0xf;
                am = a!=mask?0xf:0x0;
                bm = b!=mask?0xf:0x0;
                m = (bm<<4)|am;
                put[0] &= ~m;
                put[0] |= ((b<<4)|a)&m;

                if (xo<halfWidth) {
                    c = source[xo]>>4;
                    d = source[xo++]&0xf;
                    cm = c!=mask?0xf:0x0;
                    dm = d!=mask?0xf:0x0;
                }
                else {
                    cm = 0x0;
                    dm = 0x0;
                }
                m = (dm<<5)|(cm<<1)|(bm>>3);
                put[packet+0] &= ~m;
                put[packet+0] |= ((d<<5)|(c<<1)|(b>>3))&m;

                if (xo<halfWidth) {
                    e = source[xo]>>4;
                    f = source[xo++]&0xf;
                    em = e!=mask?0xf:0x0;
                    fm = f!=mask?0xf:0x0;
                }
                else {
                    em = 0x0;
                    fm = 0x0;
                }
                m = (fm<<6)|(em<<2)|(dm>>2);
                put[1] &= ~m;
                put[1] |= ((f<<6)|(e<<2)|(d>>2))&m;

                if (xo<halfWidth) {
                    g = source[xo]>>4;
                    z = source[xo++]&0xf;
                    gm = g!=mask?0xf:0x0;
                }
                else
                    gm = 0x0;
                m = (gm<<3)|(fm>>1);
                put[packet+1] &= ~m;
                put[packet+1] |= ((g<<3)|(f>>1))&m;
            }

            source += halfWidth;
        }
    ),
    (
        free(this->dest);
    )
)
