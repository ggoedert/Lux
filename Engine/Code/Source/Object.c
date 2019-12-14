#include "LuxObject.h"

class_default_implementations(Object, (word id), (id),
    (
        this->id = id;
    ),
    (
        NONE
    )
)
