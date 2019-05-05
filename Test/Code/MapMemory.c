#include <stdlib.h>

#include <lEngine.h>

#include "MapMemory.h"

#define BMS 4 //memory block management size 
#define _1KBLK (1024-BMS)

void DoMapMemoryTest() {
    char* ptr = (char*)0xffff;
    char* lowptr = (char*)0xffff;
    char* initptr = (char*)0xffff;
    char* expect_ptr = (char*)0xffff;
    short asize;

    LuxEcho("* Start Map Memory Test *\n");

    while(1) {
        ptr = malloc(_1KBLK);
        if (!ptr)
            break;
        ptr -= BMS;

        if (ptr != expect_ptr) {
            if (initptr != (char*)0xffff)
                LuxEcho("%04x-%04x\n", initptr, expect_ptr-1);
            initptr = ptr;
        }
        if (((int)ptr)&0x3ff) {
            asize = 0x400-(((int)ptr)&0x3ff)-BMS;
            expect_ptr = ((int)malloc(asize))+asize;
        }
        else
            expect_ptr = ptr+1024;

        /*if (lowptr == ((void*) 0xffff))
            LuxEcho("%04x\n", ptr);
        if (ptr < lowptr)
            lowptr = ptr;*/
    }
    LuxEcho("%04x-%04x\n", initptr, expect_ptr-1);
    //LuxEcho("%04x\n", lowptr);
	
    LuxEcho("* End Map Memory Test *\n");
}
