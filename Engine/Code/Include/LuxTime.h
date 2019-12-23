#ifndef LUX_TIME_H
#define LUX_TIME_H

#include "LuxDefs.h"
#include "LuxFloat.h"

word Time_deltaClock_Get(void);
word Time_clock_Get(void);
void Time_Update(void);        // This is automatically called, but should also be manually called inside long functions, to properly detect hardware clock updates
Float Time_ToTime(word clock);

#endif
