#ifndef LUX_DEFS_H
#define LUX_DEFS_H

#include <stddef.h>

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
