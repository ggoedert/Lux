#include <string.h>

#include "LuxSprite.h"

#include "LuxDebug.h"
virtual_table_type(Object) virtual_table_instance(Sprite_Object) = {
    (Object_Delete_Type)Sprite_Delete
};
class_default_implementations(Sprite, (word id, byte *texture2D), (id, texture2D),
    (
        int size;
        byte width, height;
        byte x=0, y=0;
        byte y2, packet, yb;
        byte *source, *dest;
        bool flag;
        byte a, b, c, d, e, f, g, z, *put, col, count;

        Asset_Constructor(&this->Asset, typeof_Sprite, id, &virtual_table_instance(Sprite_Object));

        width = *texture2D++;
        this->width = width;
        height = *texture2D++;
        this->height = height;

        y2 = y+height;
        packet = width/7*4;
        if (width%7)
            packet+=2;
        size = packet*2*this->height;
        this->data = malloc(size);

        // rasters are split between auxiliary memory and main memory
        source = texture2D;
        dest = this->data;
        while (y < y2) {
            put = dest;
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

            yb = y/8;
            dest += packet*2;
            source += width;
            ++y;
        }
    ),
    (
        free(this->data);
        Asset_Destructor(&this->Asset);
    )
)
