#ifndef LUX_DEFS_H
#define LUX_DEFS_H

#define true 1
#define false 0

typedef char bool;
typedef unsigned char byte;

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
