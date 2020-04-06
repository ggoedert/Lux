#ifndef LUX_TRANSFORM_H
#define LUX_TRANSFORM_H

#include "LuxComponent.h"
#include "LuxVector2.h"

#define TransformType 0xbf // String_GetHashCode8("Transform")

derived_class (Transform, Component,
    Vector2 position;
);
class_default_prototypes(Transform, NONE);

#endif
