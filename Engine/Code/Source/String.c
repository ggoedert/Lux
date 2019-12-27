#include "LuxString.h"

byte String_GetHashCode8(char *string) {
    byte sum = 0;
    while (*string)
        sum = (sum + *string++) % 255;
    return sum;
}

word String_GetHashCode16(char *string) {
    word sum1 = 0;
    word sum2 = 0;
    while (*string)
    {
        sum1 = (sum1 + *string++) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return (sum2 << 8) | sum1;
}
