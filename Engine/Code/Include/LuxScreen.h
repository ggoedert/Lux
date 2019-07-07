#ifndef LUX_SCREEN_H
#define LUX_SCREEN_H

#include "LuxDefs.h"

// graphics modes
enum { TEXT, GR, HGR };

class (Resolution,
    byte mode;
    bool doubleRes;
    bool mixed;
);

LUX_EXTERN byte Screen_resolutions_Length;
void Screen_resolutions_Get(Resolution **screen_resolutions);
void Screen_SetResolution(byte mode, bool doubleRes, bool mixed);

#endif
