#ifndef LUX_SCREEN_H
#define LUX_SCREEN_H

#include "LuxDefs.h"

// graphics modes
enum { TEXT, GR, HGR };

class(Lux_Resolution) {
    byte mode;
    bool doubleRes;
    bool mixed;
};

LUX_EXTERN int lux_Screen_resolutions_Length;
void lux_Screen_resolutions_Get(Lux_Resolution** lux_Screen_resolutions);

void lux_Screen_SetResolution(byte mode, bool doubleRes, bool mixed);

#endif
