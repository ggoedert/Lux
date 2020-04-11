#ifndef LUX_STORAGE_H
#define LUX_STORAGE_H

#include "LuxTypes.h"
#include "LuxCollections.h"

/*class (Something,
    byte type;
    byte id;
);*/

virtual_class (Storage,
    (
        NONE
    ),
    (
        byte (*Load)(word id);
        void (*Optimize)(void);
    )
);
typedef byte (*Storage_Load_Type)(word);
typedef void (*Storage_Optimize_Type)(void);
class_default_prototypes(Storage, virtual_table_type(Storage) *vtable);

#endif
