#ifndef LUX_CUSTOM_BEHAVIOUR_H
#define LUX_CUSTOM_BEHAVIOUR_H

#include "LuxGameObject.h"
#include "LuxBehaviour.h"

#define typeof_CustomBehaviour 0x26 // String_GetHashCode8("CustomBehaviour")

derived_virtual_class (CustomBehaviour, Behaviour,
    (
        EMPTY
    ),
    (
        void (*Start)(GameObject *gameObject, CustomBehaviour *this);
        void (*Update)(GameObject *gameObject, CustomBehaviour *this);
        void (*OnDestroy)(GameObject *gameObject, CustomBehaviour *this);
    )
);
typedef void (*CustomBehaviour_Start_Type)(GameObject *gameObject, CustomBehaviour *this);
typedef void (*CustomBehaviour_Update_Type)(GameObject *gameObject, CustomBehaviour *this);
typedef void (*CustomBehaviour_OnDestroy_Type)(GameObject *gameObject, CustomBehaviour *this);
void CustomBehaviour_Constructor(GameObject *gameObject, CustomBehaviour *this, virtual_table_type(Component) *component_vtable, virtual_table_type(CustomBehaviour) *customBehaviour_vtable);
void CustomBehaviour_Destructor(GameObject *gameObject, CustomBehaviour *this);

#define derived_custom_behaviour_class_default_prototypes(T) \
    void T##_Constructor(GameObject *gameObject, T *this);   \
    void T##_Destructor(GameObject *gameObject, T *this);    \
    T *T##_New(GameObject *gameObject);                      \
    void T##_Delete(GameObject *gameObject, T *this)

#define derived_custom_behaviour_class_default_implementations(T, S, U, OD)                                                                                    \
    virtual_table_type(Component) virtual_table_instance(T##_Component) = {                                                                                    \
        (Component_Delete_Type)T##_Delete                                                                                                                      \
    };                                                                                                                                                         \
    virtual_table_type(CustomBehaviour) virtual_table_instance(T##_CustomBehaviour) = {                                                                        \
        (CustomBehaviour_Start_Type)S,                                                                                                                         \
        (CustomBehaviour_Update_Type)U,                                                                                                                        \
        (CustomBehaviour_OnDestroy_Type)OD                                                                                                                     \
    };                                                                                                                                                         \
    void T##_Constructor(GameObject *gameObject, T *this) {                                                                                                    \
        CustomBehaviour_Constructor(gameObject, &this->CustomBehaviour, &virtual_table_instance(T##_Component), &virtual_table_instance(T##_CustomBehaviour)); \
    }                                                                                                                                                          \
    void T##_Destructor(GameObject *gameObject, T *this) { CustomBehaviour_Destructor(gameObject, &this->CustomBehaviour); }                                   \
    T *T##_New(GameObject *gameObject) { T *this = (T *)malloc(sizeof(T)); if (this) T##_Constructor(gameObject, this); return this; }                         \
    void T##_Delete(GameObject *gameObject, T *this) { T##_Destructor(gameObject, this); free(this); }

#endif
