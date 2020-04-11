#ifndef ASSETS_H
#define ASSETS_H

#define UFO 0xdbea // String_GetHashCode16("UFO")

derived_class (Assets, Storage,
    NONE
);
class_default_prototypes(Assets, NONE);
byte *Assets_Load(word);
void Assets_Optimize(void);

extern Assets assets;

#endif
