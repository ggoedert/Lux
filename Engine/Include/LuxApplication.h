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

typedef bool (*LoadApplication)();
typedef void (*PreVBlank)();

class (Application,
    byte machine;       // the type of Apple II
    byte romlevel;      // which revision of the machine
    byte memory;        // how much memory (up to 128K)
);
#ifdef __CC65__
void Application_Play(char *name, word version, LoadApplication loadApplication);
#else
bool Application_Start(char *name, word version, LoadApplication loadApplication);
bool Application_Step(PreVBlank preVBlank);
void Application_Stop();
#endif
#ifdef _DEBUG
void Application_Quit();
#endif
extern Application application;
extern char *Application_name;         // application name
extern word Application_version;       // application version number
#ifdef NDEBUG
#define Application_isPlaying true     // in release return always in play mode
#else
extern byte Application_isPlaying;     // return true if in play mode
#endif

#endif
