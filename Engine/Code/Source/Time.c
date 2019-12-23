#include "Time.h"

#include "LuxTime.h"

#define Float_oneOverThirty ((Float)0x00000888)

word time, frameTime, deltaTime;

word Time_deltaClock_Get() {
    return deltaTime;
}

word Time_clock_Get() {
    return time;
}

void Time_Init() {
    time = 0;
    frameTime = 0;
    deltaTime = 0;
}

void Time_Update() {
    if (frameTime == 0)
        frameTime = 1;
}

void Time_Run() {
    deltaTime = frameTime;
    frameTime = 0;
    time += deltaTime;
}

Float Time_ToTime(word clock) {
    return Float_Mul(FIXMATH_I(clock), Float_oneOverThirty);
}
