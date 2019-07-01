#ifndef LUX_DEFS_H
#define LUX_DEFS_H

#include <stddef.h>

// new style null pointer
#define nullptr NULL

// true/false definitions
#define true 1
#define false 0

// bool/byte types
typedef char bool;
typedef unsigned char byte;

// struct/class helper macros
#define REM_ENCLOSE_(...) __VA_ARGS__
#define REM_ENCLOSE(...) REM_ENCLOSE_ __VA_ARGS__
#define virtual_table(C) const struct C##_vtable
#define virtual_table_instance(C) g_##C##_vtable

#define class(C, ...)        \
    typedef struct C C;      \
    struct C { __VA_ARGS__ }

#define virtual_class(C, V, VT)                            \
    typedef struct C C;                                    \
    typedef struct C##_vtable C##_vtable;                  \
    struct C { const C##_vtable* vtable; REM_ENCLOSE(V) }; \
    struct C##_vtable { REM_ENCLOSE(VT) }

#define derived_class(C, B, ...)  \
    typedef struct C C;           \
    struct C { B B; __VA_ARGS__ }

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
