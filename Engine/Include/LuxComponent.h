#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include "LuxObject.h"

#define component_constructor_prototype(T, ...)         void T##_Constructor(GameObject *gameObject, T *this, __VA_ARGS__)
#define component_constructor_implementation(T, A, ...) void T##_Constructor(GameObject *gameObject, T *this, REM_ENCLOSE(A)) { __VA_ARGS__ }
#define component_destructor_prototype(T)               void T##_Destructor(GameObject *gameObject, T *this)
#define component_destructor_implementation(T, ...)     void T##_Destructor(GameObject *gameObject, T *this) { __VA_ARGS__ }

#define component_new_prototype(T, ...)        T *T##_New(GameObject *gameObject, __VA_ARGS__)
#define component_new_implementation(T, AD, A) T *T##_New(GameObject *gameObject, REM_ENCLOSE(AD)) { T *this = (T *)malloc(sizeof(T)); if (this) T##_Constructor(gameObject, this, REM_ENCLOSE(A)); return this; }
#define component_delete_prototype(T)          void T##_Delete(GameObject *gameObject, T *this)
#define component_delete_implementation(T)     void T##_Delete(GameObject *gameObject, T *this) { T##_Destructor(gameObject, this); free(this); }

#define component_constructor_destructor_prototypes(T, ...) \
    component_constructor_prototype(T, __VA_ARGS__);        \
    component_destructor_prototype(T)

#define component_constructor_destructor_implementations(T, A, CI, DI) \
    component_constructor_implementation(T, A, REM_ENCLOSE(CI))        \
    component_destructor_implementation(T, REM_ENCLOSE(DI))

#define component_new_delete_prototypes(T, ...) \
    component_new_prototype(T, __VA_ARGS__);    \
    component_delete_prototype(T)

#define component_new_delete_implementations(T, AD, A) \
    component_new_implementation(T, AD, A)     \
    component_delete_implementation(T)

#define component_default_prototypes(T, ...)                     \
    component_constructor_destructor_prototypes(T, __VA_ARGS__); \
    component_new_delete_prototypes(T, __VA_ARGS__)

#define component_default_implementations(T, AD, A, CI, DI)         \
    component_constructor_destructor_implementations(T, AD, CI, DI) \
    component_new_delete_implementations(T, AD, A)

class_prototype(GameObject);
derived_virtual_class (Component, Object,
    (
        EMPTY
    ),
    (
        void (*Delete)(GameObject* gameObject, Component* this);
    )
);
typedef void (*Component_Delete_Type)(GameObject* gameObject, Component* this);
component_constructor_prototype(Component, byte type, virtual_table_type(Component)* vtable);

#endif
