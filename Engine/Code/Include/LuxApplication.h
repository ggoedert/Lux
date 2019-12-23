#ifndef LUX_APPLICATION_H
#define LUX_APPLICATION_H

#include "LuxTypes.h"

// version of the lux engine
#define luxVersionMajor     0x00
#define luxVersionMinor     0x01
#define luxVersion          ((luxVersionMajor<<8)+luxVersionMinor)

// machine types
enum {
    IIplain=1,  // Apple II
    IIplus,     // Apple II+
    IIIem,      // Apple /// in emulation mode
    IIe,        // Apple IIe
    IIc,        // Apple IIc
    IIeCard     // Apple IIe Card for the Macintosh LC
};

typedef void (*LoadApplication)(void);

class (Application,
    byte machine;       // the type of Apple II
    byte romlevel;      // which revision of the machine
    byte memory;        // how much memory (up to 128K)
    char *name;         // application name
    word version;       // application version number
);
void Application_Run(char *name, word version, LoadApplication loadApplication);
extern Application application;

#endif
