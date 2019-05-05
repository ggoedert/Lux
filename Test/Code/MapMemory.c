#include <stddef.h>
#include <stdlib.h>

#include <lEngine.h>

#include "MapMemory.h"

#define BLK1K (0x400)           // 1k block size
#define BLKOH (0x4)             // block management overhead for memory blocks
#define RAWBLK1K (BLK1K-BLKOH)  // raw 1k sized memory block including memory management overhead

void DoMapMemoryTest() {
    char* ptr = (char*)NULL;
    char* initptr = (char*)NULL;
    char* expect_ptr = (char*)NULL;
    short misalign;

    LuxEcho("* Start Map Memory Test *\n");

    while(1) {
        ptr = malloc(RAWBLK1K);
        if (!ptr)
            break;
        ptr -= BLKOH;

        if (ptr != expect_ptr) {
            if (initptr != (char*)NULL)
                LuxEcho("%04x-%04x\n", initptr, expect_ptr-1);
            initptr = ptr;
        }
        misalign = ((int)ptr)&(BLK1K-1);
        if (misalign) {
            misalign = RAWBLK1K-misalign;
            expect_ptr = ((int)malloc(misalign))+misalign;
        }
        else
            expect_ptr = ptr+BLK1K;
    }
    LuxEcho("%04x-%04x\n", initptr, expect_ptr-1);
	
    LuxEcho("* End Map Memory Test *\n");
}
