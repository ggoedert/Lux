#include "Time.h"

#include "LuxTime.h"

#define Float_oneOverThirty ((Float)0x00000888)

word Time_clock;
word Time_frameClock;
word Time_deltaClock;

void Time_Init() {
    Time_clock = 0;
    Time_frameClock = 0;
    Time_deltaClock = 0;
}

void Time_Update() {
    if (Time_frameClock == 0)
        Time_frameClock = 1;
}

void Time_Run() {
    Time_deltaClock = Time_frameClock;
    Time_frameClock = 0;
    Time_clock += Time_deltaClock;
}

#ifdef FLOAT
Float Time_ToTime(word clock) {
    return Float_Mul(FIXMATH_I(clock), Float_oneOverThirty);
}
#endif
