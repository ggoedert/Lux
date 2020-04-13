#ifndef LUX_ASSET_H
#define LUX_ASSET_H

#include "LuxObject.h"

derived_class (Asset, Object,
    word id;
);
class_default_prototypes(Asset, byte type, word id, virtual_table_type(Object) *vtable);

#endif
