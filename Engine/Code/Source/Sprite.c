#include <string.h>

#include "LuxSprite.h"

#include "LuxDebug.h"
virtual_table_type(Object) virtual_table_instance(Sprite_Object) = {
    (Object_Delete_Type)Sprite_Delete
};
class_default_implementations(Sprite, (word id, byte *texture2D), (id, texture2D),
    (
        int size;
        byte halfWidth, height;
        byte x, y, packet;
        byte *source, *dest;
        byte a, b, c, d, e, f, g, z, *put, count;
        bool flag;

        Asset_Constructor(&this->Asset, typeof_Sprite, id, &virtual_table_instance(Sprite_Object));

        halfWidth = *texture2D++/2;
        this->width = halfWidth*2;
        height = *texture2D++;
        this->height = height;
        packet = halfWidth/7*4;
        if (halfWidth%7)
            packet+=2;
        size = packet*2*height;
        this->data = malloc(size);

        // rasters are split between auxiliary memory and main memory
        source = texture2D;
        dest = this->data;
        for (y=0; y<height; ++y) {
            put = dest;
            count = 0;
            flag = false;//good
            for (x=0; x<halfWidth; ++x) {
                ++count;
                if (count == 4) {
                    a = source[x-3]>>4;
                    b = source[x-3]&0xf;
                    c = source[x-2]>>4;
                    d = source[x-2]&0xf;
                    e = source[x-1]>>4;
                    f = source[x-1]&0xf;
                    g = source[x]>>4;
                    z = source[x]&0xf;
                    flag = true;
                }
                else if (count == 7) {
                    a = z;
                    b = source[x-2]>>4;
                    c = source[x-2]&0xf;
                    d = source[x-1]>>4;
                    e = source[x-1]&0xf;
                    f = source[x]>>4;
                    g = source[x]&0xf;
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
                x = halfWidth-count;
                a = source[x]>>4;
                b = source[x++]&0xf;
                put[0] = (b<<4)|a;
                if (x<halfWidth) {
                    c = source[x]>>4;
                    d = source[x++]&0xf;
                }
                else {
                    c = 0;
                    d = 0;
                }
                put[packet+0] = (d<<5)|(c<<1)|(b>>3);
                if (x<halfWidth) {
                    e = source[x]>>4;
                    f = source[x++]&0xf;
                }
                else {
                    e = 0;
                    f = 0;
                }
                put[1] = (f<<6)|(e<<2)|(d>>2);
                if (x<halfWidth) {
                    g = source[x]>>4;
                    z = source[x++]&0xf;
                }
                else {
                    g = 0;
                    z = 0;
                }
                put[packet+1] = (g<<3)|(f>>1);
            }

            dest += packet*2;
            source += halfWidth;
        }
    ),
    (
        free(this->data);
        Asset_Destructor(&this->Asset);
    )
)
