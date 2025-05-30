#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define FAIRYWIDTH   20
#define FAIRYHEIGHT  27

unsigned char FAIRYPixelData[] = {
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x01, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x18, 0x20, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x00, 0x3c, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x46, 0x11, 0x40, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x7f, 0x1c, 0x40, 0x11, 0x0c,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x46, 0x14, 0x3b, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x7f, 0x48, 0x42, 0x11, 0x0c,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x46, 0x0a, 0x3b, 0x08, 0x62, 0x11, 0x44, 0x11, 0x44, 0x11, 0x7f, 0x49, 0x0f, 0x11, 0x40,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x14, 0x00, 0x08, 0x62, 0x11, 0x44, 0x11, 0x44, 0x11, 0x7d, 0x1c, 0x08, 0x11, 0x40,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x62, 0x1a, 0x3f, 0x08, 0x06, 0x11, 0x44, 0x11, 0x44, 0x11, 0x78, 0x68, 0x42, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x02, 0x1a, 0x11, 0x08, 0x06, 0x11, 0x44, 0x11, 0x44, 0x11, 0x54, 0x08, 0x42, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x3c, 0x00, 0x3f, 0x08, 0x20, 0x11, 0x44, 0x11, 0x44, 0x11, 0x00, 0x60, 0x42, 0x31, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x42, 0x5d, 0x37, 0x08, 0x20, 0x11, 0x44, 0x11, 0x44, 0x11, 0x6e, 0x35, 0x42, 0x31, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x01, 0x22, 0x20, 0x37, 0x18, 0x22, 0x11, 0x44, 0x11, 0x04, 0x11, 0x00, 0x75, 0x42, 0x00, 0x44,
    0x08, 0x22, 0x08, 0x62, 0x04, 0x22, 0x5a, 0x3d, 0x40, 0x22, 0x11, 0x44, 0x11, 0x78, 0x11, 0x44, 0x1b, 0x00, 0x08, 0x44,
    0x08, 0x22, 0x08, 0x62, 0x1f, 0x00, 0x5d, 0x02, 0x7a, 0x22, 0x11, 0x44, 0x11, 0x00, 0x10, 0x00, 0x5b, 0x6d, 0x03, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x44, 0x75, 0x5a, 0x02, 0x00, 0x22, 0x11, 0x44, 0x11, 0x44, 0x00, 0x6e, 0x5b, 0x00, 0x10, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x71, 0x75, 0x2a, 0x20, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x1f, 0x6e, 0x3b, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x68, 0x2d, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x00, 0x6e, 0x01, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x46, 0x2d, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x6e, 0x11, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x06, 0x2d, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x6d, 0x11, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x06, 0x2d, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x6a, 0x11, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x46, 0x1d, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x57, 0x10, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x40, 0x1d, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x03, 0x07, 0x10, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x3f, 0x1a, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x69, 0x42, 0x10, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x40, 0x11, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x01, 0x40, 0x10, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x03, 0x44, 0x11, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x03, 0x44, 0x11, 0x44, 0x11, 0x44,
    0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x08, 0x22, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44
};

#define FILE_RESERVED       0x00
#define FILE_LGR            0x01
#define FILE_SMALL_HGR      0x02
#define FILE_LWIDTH_HGR     0x03
#define FILE_LHEIGHT_HGR    0x04
#define FILE_LARGE_HGR      0x05
#define FILE_SMALL_DHGR     0x06
#define FILE_LWIDTH_DHGR    0x07
#define FILE_LHEIGHT_DHGR   0x08
#define FILE_LARGE_DHGR     0x09

typedef unsigned char byte;
typedef unsigned short word;

int main(int argc, char *argv[]) {

    /*for (y=0; y<FAIRYHEIGHT; y++)
        printf("0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x,\n",
            FAIRYPixelData[y*FAIRYWIDTH+ 0], FAIRYPixelData[y*FAIRYWIDTH+ 1], FAIRYPixelData[y*FAIRYWIDTH+ 2], FAIRYPixelData[y*FAIRYWIDTH+ 3], FAIRYPixelData[y*FAIRYWIDTH+ 4], FAIRYPixelData[y*FAIRYWIDTH+ 5], FAIRYPixelData[y*FAIRYWIDTH+ 6], FAIRYPixelData[y*FAIRYWIDTH+ 7], FAIRYPixelData[y*FAIRYWIDTH+ 8], FAIRYPixelData[y*FAIRYWIDTH+ 9],
            FAIRYPixelData[y*FAIRYWIDTH+10], FAIRYPixelData[y*FAIRYWIDTH+11], FAIRYPixelData[y*FAIRYWIDTH+12], FAIRYPixelData[y*FAIRYWIDTH+13], FAIRYPixelData[y*FAIRYWIDTH+14], FAIRYPixelData[y*FAIRYWIDTH+15], FAIRYPixelData[y*FAIRYWIDTH+16], FAIRYPixelData[y*FAIRYWIDTH+17], FAIRYPixelData[y*FAIRYWIDTH+18], FAIRYPixelData[y*FAIRYWIDTH+19]);*/

    char *command, *refFile;
    FILE *outputFile;
    
    if (argc < 3) {
        printf("The syntax of the command is incorrect.\n");
        return 1;
    }
    command = argv[1];
    if (('-' != command[0]) || ('c' != command[1])) {
        printf("The syntax of the command is incorrect.\n");
        return 1;
    }
    refFile = argv[2];
    for (char *chPtr = strchr(refFile, '\\'); nullptr != chPtr; chPtr = strchr(chPtr, '\\'))
        *chPtr = '/';
    outputFile = fopen(refFile, "wb");

    // <16bit>(count)[<16bit>(hash)<16bit>(finalsize)<16bit>(offset)...][<filename>(cstring)...][<file>(rawdata)...

    word w;
    w = 1;
    fwrite (&w, sizeof(word), 1, outputFile); //count
    w = 0;
    fwrite (&w, sizeof(word), 1, outputFile); //hash
    w = 20*27*sizeof(word);
    fwrite (&w, sizeof(word), 1, outputFile); //finalsize
    w = 4*sizeof(word);
    fwrite (&w, sizeof(word), 1, outputFile); //offset
    fwrite (FAIRYPixelData, sizeof(word), 20*27, outputFile); //rawdata

    fclose(outputFile);
    return 0;
}
