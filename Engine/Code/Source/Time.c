#include "Time.h"

#include "LuxTime.h"

#define Float_oneOverThirty ((Float)0x00000888)

Float time, frameTime, deltaTime;

Float Time_frameTime_Get() {
    return deltaTime;
}

void Time_Init() {
    time = Float_zero;
    frameTime = Float_zero;
    deltaTime = Float_zero;
}

void Time_Update() {
    if (frameTime == Float_zero)
        frameTime = Float_oneOverThirty;
}

void Time_Run() {
    deltaTime = frameTime;
    frameTime = Float_zero;
    time = Float_Add(time, deltaTime);
}
