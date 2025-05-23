#ifndef LUX_TRANSFORM_H
#define LUX_TRANSFORM_H

#include "LuxComponent.h"
#include "LuxVector2.h"

#define typeof_Transform 0xbf // String_GetHashCode8("Transform")

derived_class(Transform, Component,
    Vector2 position;
);
component_default_prototypes(Transform, VOID);

#endif
