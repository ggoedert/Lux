#ifndef LUX_SCREEN_H
#define LUX_SCREEN_H

#include "LuxTypes.h"

// graphics modes
enum { TEXT, GR, HGR };

class (Resolution,
    byte mode;
    bool doubleRes;
    bool mixed;
);

extern Resolution Screen_resolutions[];
extern byte Screen_resolutions_Length;
extern Resolution Screen_currentResolution;
#ifndef __CC65__
void Screen_Finalize();
#endif
void Screen_SetResolution(byte mode, bool doubleRes, bool mixed);
void Screen_Clear();

#endif
