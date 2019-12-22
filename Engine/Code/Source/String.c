#include "LuxString.h"

word String_GetHashCode(char *string) {
    word sum1 = 0;
    word sum2 = 0;
    while (*string)
    {
        sum1 = (sum1 + *string++) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return (sum2 << 8) | sum1;
}
