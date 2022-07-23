#include "..\Source\Apple2Id.h"

#include "LuxApplication.h"

void GetApple2Id(Apple2Id *apple2Id) {
    apple2Id->machine = IIe;
    apple2Id->romlevel = 0;
    apple2Id->memory = 128;
}
