#include <stdbool.h>
#include <ctype.h>

#include "LuxFloat.h"

static const uint32_t scales[8] = {
    /* 5 decimals is enough for full Float precision */
    1, 10, 100, 1000, 10000, 100000, 100000, 100000
};

Float Float_Mul(Float value0, Float value1) {
    uint32_t _a = (value0 >= 0) ? value0 : (-value0);
    uint32_t _b = (value1 >= 0) ? value1 : (-value1);

    uint8_t va[4];
    uint8_t vb[4];

    uint32_t low = 0;
    uint32_t mid = 0;

    Float result;

    va[0] = _a;
    va[1] = (_a >> 8);
    va[2] = (_a >> 16);
    va[3] = (_a >> 24);
    vb[0] = _b;
    vb[1] = (_b >> 8);
    vb[2] = (_b >> 16);
    vb[3] = (_b >> 24);

    // Result column i depends on va[0..i] and vb[i..0]

#ifdef FIXMATH_OVERFLOW
    // i = 6
    if (va[3] && vb[3]) return Float_overflow;
#endif

// i = 5
    if (va[2] && vb[3]) mid += (uint16_t)va[2] * vb[3];
    if (va[3] && vb[2]) mid += (uint16_t)va[3] * vb[2];
    mid <<= 8;

    // i = 4
    if (va[1] && vb[3]) mid += (uint16_t)va[1] * vb[3];
    if (va[2] && vb[2]) mid += (uint16_t)va[2] * vb[2];
    if (va[3] && vb[1]) mid += (uint16_t)va[3] * vb[1];

#ifdef FIXMATH_OVERFLOW
    if (mid & 0xFF000000) return Float_overflow;
#endif
    mid <<= 8;

    // i = 3
    if (va[0] && vb[3]) mid += (uint16_t)va[0] * vb[3];
    if (va[1] && vb[2]) mid += (uint16_t)va[1] * vb[2];
    if (va[2] && vb[1]) mid += (uint16_t)va[2] * vb[1];
    if (va[3] && vb[0]) mid += (uint16_t)va[3] * vb[0];

#ifdef FIXMATH_OVERFLOW
    if (mid & 0xFF000000) return Float_overflow;
#endif
    mid <<= 8;

    // i = 2
    if (va[0] && vb[2]) mid += (uint16_t)va[0] * vb[2];
    if (va[1] && vb[1]) mid += (uint16_t)va[1] * vb[1];
    if (va[2] && vb[0]) mid += (uint16_t)va[2] * vb[0];

    // i = 1
    if (va[0] && vb[1]) low += (uint16_t)va[0] * vb[1];
    if (va[1] && vb[0]) low += (uint16_t)va[1] * vb[0];
    low <<= 8;

    // i = 0
    if (va[0] && vb[0]) low += (uint16_t)va[0] * vb[0];

#ifdef FIXMATH_ROUNDING
    low += 0x8000;
#endif
    mid += (low >> 16);

#ifdef FIXMATH_OVERFLOW
    if (mid & 0x80000000)
        return Float_overflow;
#endif

    result = mid;

    /* Figure out the sign of result */
    if ((value0 >= 0) != (value1 >= 0)) {
        result = -result;
    }

    return result;
}

Float Float_Div(Float value0, Float value1) {
    uint32_t remainder;
    uint32_t divider;
    uint32_t quotient;
    uint32_t bit;

    Float result;
    // This uses the basic binary restoring division algorithm.
    // It appears to be faster to do the whole division manually than
    // trying to compose value0 64-bit divide out of 32-bit divisions on
    // platforms without hardware divide.

    if (value1 == 0)
        return Float_minimum;

    remainder = (value0 >= 0) ? value0 : (-value0);
    divider = (value1 >= 0) ? value1 : (-value1);

    quotient = 0;
    bit = 0x10000;

    /* The algorithm requires D >= R */
    while (divider < remainder) {
        divider <<= 1;
        bit <<= 1;
    }

#ifdef FIXMATH_OVERFLOW
    if (!bit)
        return Float_overflow;
#endif

    if (divider & 0x80000000) {
        // Perform one step manually to avoid overflows later.
        // We know that divider's bottom bit is 0 here.
        if (remainder >= divider) {
            quotient |= bit;
            remainder -= divider;
        }
        divider >>= 1;
        bit >>= 1;
    }

    /* Main division loop */
    while (bit && remainder) {
        if (remainder >= divider) {
            quotient |= bit;
            remainder -= divider;
        }

        remainder <<= 1;
        bit >>= 1;
    }

#ifdef FIXMATH_ROUNDING
    if (remainder >= divider) {
        ++quotient;
    }
#endif

    result = quotient;

    /* Figure out the sign of result */
    if ((value0 ^ value1) & 0x80000000) {
#ifdef FIXMATH_OVERFLOW
        if (result == Float_minimum)
            return Float_overflow;
#endif

        result = -result;
    }

    return result;
}

static char *itoa_loop(char *buffer, uint32_t scale, uint32_t value, bool skip) {
    while (scale) {
        uint32_t digit = (value / scale);

        if (!skip || digit || scale == 1) {
            skip = false;
            *buffer++ = '0' + digit;
            value %= scale;
        }

        scale /= 10;
    }
    return buffer;
}

void Float_ToString(Float value, char *buffer, int decimals) {
    uint32_t intpart;
    uint32_t fracpart;
    uint32_t scale;
    uint32_t uvalue = (value >= 0) ? value : -value;
    if (value < 0)
        *buffer++ = '-';

    /* Separate the integer and decimal parts of the value */
    intpart = uvalue >> 16;
    fracpart = uvalue & 0xFFFF;
    scale = scales[decimals & 7];
    fracpart = Float_Mul(fracpart, scale);

    if (fracpart >= scale) {
        /* Handle carry from decimal part */
        ++intpart;
        fracpart -= scale;
    }

    /* Format integer part */
    buffer = itoa_loop(buffer, 10000, intpart, true);

    /* Format decimal part (if any) */
    if (scale != 1) {
        *buffer++ = '.';
        buffer = itoa_loop(buffer, scale / 10, fracpart, false);
    }

    *buffer = '\0';
}
