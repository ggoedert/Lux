#ifndef LUX_SCREEN_H
#define LUX_SCREEN_H

#include <stdbool.h>

#include "LuxTypes.h"

// graphics modes
enum { TEXT, GR, HGR };

class (Resolution,
    byte mode;
    bool doubleRes;
    bool mixed;
);

extern Resolution Screen_currentResolution;
extern byte Screen_resolutions_Length;
void Screen_resolutions_Get(Resolution **screen_resolutions);
void Screen_SetResolution(byte mode, bool doubleRes, bool mixed);
void Screen_WaitVBlank(void);

#endif
