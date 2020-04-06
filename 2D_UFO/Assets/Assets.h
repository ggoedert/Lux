#ifndef ASSETS_H
#define ASSETS_H

#define UFO 0x0

class (Asset,
    word offset;
    word size;
);

Asset Assets[] = {
    {0, 100}
};

#endif
 