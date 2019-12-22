#ifndef LUX_TIME_H
#define LUX_TIME_H

#include "LuxFloat.h"

Float Time_deltaTime_Get(void);
void Time_Update(void);         // This should be manually called inside long functions, to properly detect time updates based on video refresh polling

#endif
