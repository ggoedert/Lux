#ifndef ASSETS_H
#define ASSETS_H

#define UFO 0xdbea // String_GetHashCode16("UFO")

derived_class (Assets, Storage,
    EMPTY
);
class_default_prototypes(Assets, VOID);
byte *Assets_Load(word);

extern Assets assets;

#endif
