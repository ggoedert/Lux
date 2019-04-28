#ifndef L_CLASS_H
#define L_CLASS_H

#define REM_ENCLOSE_(...) __VA_ARGS__
#define REM_ENCLOSE(...) REM_ENCLOSE_ __VA_ARGS__

#define class(C) typedef struct C C; struct C

#define virtual_class(C, V, VT)                            \
    typedef struct C C;                                    \
    typedef struct C##_vtable C##_vtable;                  \
    struct C { const C##_vtable* vtable; REM_ENCLOSE(V) }; \
    struct C##_vtable { REM_ENCLOSE(VT) }

#define virtual_table(C) const struct C##_vtable

#define virtual_table_instance(C) g_##C##_vtable

#define derived_class(C, B, ...) \
    typedef struct C C;          \
    struct C { B B; __VA_ARGS__ }

#endif
