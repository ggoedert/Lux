#include <string.h>

#include "LuxSprite.h"

class_default_implementations(Sprite, (byte *texture2D), (texture2D),
    (
        byte halfWidth;
        byte xo, yo, packet;
        byte *source, *spriteData;
        byte a, b, c, d, e, f, g, z, *put, count;
        bool flag;
        byte yb;

        this->width = *texture2D++;
        this->height = *texture2D++;

        halfWidth = this->width/2;
        packet = halfWidth/7*4;
        if (halfWidth%7)
            packet+=2;
        this->data = malloc(packet*2*this->height);

        // rasters are split between auxiliary memory and main memory
        source = texture2D;
        for (yo=0; yo<this->height; ++yo) {

            yb = yo/8;
            spriteData = this->data+(packet*2*yo);

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
                if (flag) {
                    put[0] = (b<<4)|a;
                    put[packet+0] = (d<<5)|(c<<1)|(b>>3);
                    put[1] = (f<<6)|(e<<2)|(d>>2);
                    put[packet+1] = (g<<3)|(f>>1);
                    put += 2;
                    flag = false;
                }
            }
            count = halfWidth%7;
            if (count) {
                xo = halfWidth-count;
                a = source[xo]>>4;
                b = source[xo++]&0xf;
                put[0] = (b<<4)|a;

                if (xo<halfWidth) {
                    c = source[xo]>>4;
                    d = source[xo++]&0xf;
                }
                put[packet+0] = (d<<5)|(c<<1)|(b>>3);

                if (xo<halfWidth) {
                    e = source[xo]>>4;
                    f = source[xo++]&0xf;
                }
                put[1] = (f<<6)|(e<<2)|(d>>2);

                if (xo<halfWidth) {
                    g = source[xo]>>4;
                    z = source[xo++]&0xf;
                }
                put[packet+1] = (g<<3)|(f>>1);
            }

            source += halfWidth;
        }
    ),
    (
        free(this->data);
    )
)
