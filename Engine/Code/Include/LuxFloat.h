#ifndef LUX_FLOAT_H
#define LUX_FLOAT_H

#include <stdint.h>

typedef int32_t Float;

#define FOUR_DIV_PI             ((Float)0x145F3)
#define MINUS_FOUR_DIV_PI2      ((Float)0xFFFF9840)
#define X4_CORRECTION_COMPONENT ((Float)0x399A)
#define PI_DIV_4                ((Float)0x0000C90F)
#define THREE_PI_DIV_4          ((Float)0x00025B2F)

#define Float_maximum  ((Float)0x7FFFFFFF)
#define Float_minimum  ((Float)0x80000000)
#define Float_overflow ((Float)0x80000000)

#define Float_pi   ((Float)205887)
#define Float_e    ((Float)178145)
#define Float_one  ((Float)0x00010000)
#define Float_zero ((Float)0x00000000)

#define FIXMATH_I(i) \
( \
    ( \
        (  (uint32_t)i ) \
        << (uint32_t)16 \
    ) \
)
#define FLOATC_I(i) \
( (Float) \
    ( \
      (( #i[0] ) == '-') \
        ? -FIXMATH_I((uint32_t)( ( (i) * -1) )) \
        : FIXMATH_I(i) \
    ) \
)

#define FLOAT_MAX_STRING_SIZE 13 // -32768.00000 including null terminator

#define Float_Add(value0, value1) ((Float)(((Float)value0) + ((Float)value1)))
#define Float_Sub(value0, value1) ((Float)(((Float)value0) - ((Float)value1)))
Float Float_Mul(Float value0, Float value1);
Float Float_Div(Float value0, Float value1);
void Float_ToString(Float value, char *buffer, int decimals);

#endif
