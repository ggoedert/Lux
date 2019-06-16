#ifndef LUX_APPLICATION_H
#define LUX_APPLICATION_H

#include "LuxDefs.h"

// version of the lux engine (major<<16)+minor
#define luxVersion 0x0001

// machine types
enum {
    IIplain=1,  // Apple II
    IIplus,     // Apple II+
    IIIem,      // Apple /// in emulation mode
    IIe,        // Apple IIe
    IIc,        // Apple IIc
    IIeCard     // Apple IIe Card for the Macintosh LC
};

class(Lux_Application) {
    byte machine;       // the type of Apple II
    byte romlevel;      // which revision of the machine
    byte memory;        // how much memory (up to 128K)
    char* name;         // application name
    int version;        // application version number
};

LUX_EXTERN Lux_Application lux_Application;

#endif
