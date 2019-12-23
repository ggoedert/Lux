#ifndef LUX_TIME_H
#define LUX_TIME_H

#include "LuxTypes.h"
#include "LuxFloat.h"

extern word Time_clock;
extern word Time_deltaClock;
void Time_Update(void);        // This is automatically called, but should also be manually called inside long functions, to properly detect hardware clock updates
Float Time_ToTime(word clock);

#endif
