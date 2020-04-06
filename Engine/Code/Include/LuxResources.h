#ifndef LUX_RESOURCES_H
#define LUX_RESOURCES_H

#include "LuxTypes.h"

class (Resources,
    byte temp;
);
class_default_prototypes(Resources, NONE);
void *Resources_Load(word id);

#endif
