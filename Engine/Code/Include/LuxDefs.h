#ifndef LUX_DEFS_H
#define LUX_DEFS_H

#include <stddef.h>
#include <stdlib.h>

// new style null pointer
#define nullptr NULL

// true/false definitions
#define true 1
#define false 0

// type aliases
typedef char bool;
typedef unsigned char byte;
typedef unsigned int word;

// struct/class helper macros
#define REM_ENCLOSE_(...) __VA_ARGS__
#define REM_ENCLOSE(...) REM_ENCLOSE_ __VA_ARGS__
#define NONE REM_ENCLOSE(())
#define virtual_table(T) const struct T##_vtable
#define virtual_table_instance(T) g_##T##_vtable

#define class(T, ...)        \
    typedef struct T T;      \
    struct T { __VA_ARGS__ }

#define derived_class(T, B, ...)  \
    typedef struct T T;           \
    struct T { B B; __VA_ARGS__ }

#define virtual_class(T, D, VT)                            \
    typedef struct T T;                                    \
    typedef struct T##_vtable T##_vtable;                  \
    struct T { const T##_vtable *vtable; REM_ENCLOSE(D) }; \
    struct T##_vtable { REM_ENCLOSE(VT) }

#define derived_virtual_class(T, B, D, VT)                      \
    typedef struct T T;                                         \
    typedef struct T##_vtable T##_vtable;                       \
    struct T { B B; const T##_vtable *vtable; REM_ENCLOSE(D) }; \
    struct T##_vtable { REM_ENCLOSE(VT) }

#define class_constructor_prototype(T, ...)         void T##_Constructor(T *this, __VA_ARGS__)
#define class_constructor_implementation(T, A, ...) void T##_Constructor(T *this, REM_ENCLOSE(A)) { __VA_ARGS__ }
#define class_destructor_prototype(T)               void T##_Destructor(T *this)
#define class_destructor_implementation(T, ...)     void T##_Destructor(T *this) { __VA_ARGS__ }

#define class_new_prototype(T, ...)        T *T##_New(__VA_ARGS__)
#define class_new_implementation(T, AD, A) T *T##_New(REM_ENCLOSE(AD)) { T *this = (T *)malloc(sizeof(T)); if (this) T##_Constructor(this, REM_ENCLOSE(A)); return this; }
#define class_delete_prototype(T)          void T##_Delete(T *this)
#define class_delete_implementation(T)     void T##_Delete(T *this) { T##_Destructor(this); free(this); }

#define class_constructor_destructor_prototypes(T, ...) \
    class_constructor_prototype(T, __VA_ARGS__);        \
    class_destructor_prototype(T)

#define class_constructor_destructor_implementations(T, A, CI, DI) \
    class_constructor_implementation(T, A, REM_ENCLOSE(CI))        \
    class_destructor_implementation(T, REM_ENCLOSE(DI))

#define class_new_delete_prototypes(T, ...) \
    class_new_prototype(T, __VA_ARGS__);    \
    class_delete_prototype(T)

#define class_new_delete_implementations(T, ...) \
    class_new_implementation(T, __VA_ARGS__)     \
    class_delete_implementation(T)

#define class_default_prototypes(T, ...)                     \
    class_constructor_destructor_prototypes(T, __VA_ARGS__); \
    class_new_delete_prototypes(T, __VA_ARGS__)

#define class_default_implementations(T, AD, A, CI, DI)         \
    class_constructor_destructor_implementations(T, AD, CI, DI) \
    class_new_delete_implementations(T, AD, A)

#define class_simple_default_implementations(T, B, A)  \
    class_default_implementations(T, (NONE), (NONE),   \
        (                                              \
            B##_Constructor(&this->B, REM_ENCLOSE(A)); \
        ),                                             \
        (                                              \
            B##_Destructor(&this->B);                  \
        )                                              \
    )

// extern macro for defining globals
#ifndef LUX_DEFINE_GLOBALS
#ifndef LUX_EXTERN
#define LUX_EXTERN extern
#endif
#else
#ifndef LUX_EXTERN
#define LUX_EXTERN
#endif
#endif

// declare macro for defining globals
#ifndef LUX_DEFINE_GLOBALS
#ifndef LUX_DECLARE
#define LUX_DECLARE(TYPE, NAME, VALUE) extern TYPE NAME
#endif
#else
#ifndef LUX_DECLARE
#define LUX_DECLARE(TYPE, NAME, VALUE) TYPE NAME = VALUE
#endif
#endif

#endif
