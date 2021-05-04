#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char *command, *refFile;
    char tmpBuffer[256];
    FILE *outputFile;
    bool makeFull;
    struct stat st;
    int numberOverlay = 0, biggestOverlay = 0;
    
    if (argc < 3) {
        printf("The syntax of the command is incorrect.\n");
        return 1;
    }
    command = argv[1];
    if (('-' != command[0]) || (('d' != command[1]) && ('f' != command[1]))) {
        printf("The syntax of the command is incorrect.\n");
        return 1;
    }
    makeFull = ('f' == command[1]);
    refFile = argv[2];
    for (char *chPtr = strchr(refFile, '\\'); nullptr != chPtr; chPtr = strchr(chPtr, '\\'))
        *chPtr = '/';
    if (makeFull) {
        if (-1 == access(refFile, F_OK)) {
            printf("Missing destination reference file.\n");
            return 1;
        }
        while (true) {
            sprintf(tmpBuffer, "%s.%d", refFile, numberOverlay+1);
            if (-1 == access(tmpBuffer, F_OK))
                break;
            stat(tmpBuffer, &st);
            if (st.st_size > biggestOverlay)
                biggestOverlay = st.st_size;
            numberOverlay++;
        }
        if (argc < (3+numberOverlay)) {
            printf("Missing overlay names.\n");
            return 1;
        }
    }
    else
        numberOverlay = argc-3;
    sprintf(tmpBuffer, "%s.cfg", refFile);
    outputFile = fopen(tmpBuffer, "w");
    if (makeFull)
        printf("Making FULL overlay config for: %s, overlays: %d, output: %s\n", refFile, numberOverlay, tmpBuffer);
    else
        printf("Making DUMMY overlay config for: %s, overlays: %d, output: %s\n", refFile, numberOverlay, tmpBuffer);
    fprintf(outputFile, "FEATURES {\n");
    fprintf(outputFile, "    STARTADDRESS: default = $4000;\n");
    fprintf(outputFile, "}\n");
    fprintf(outputFile, "SYMBOLS {\n");
    fprintf(outputFile, "    __EXEHDR__:      type = import;\n");
    fprintf(outputFile, "    __FILETYPE__:    type = weak, value = $0006; # ProDOS file type\n");
    fprintf(outputFile, "    __STACKSIZE__:   type = weak, value = $0800; # 2k stack\n");
    fprintf(outputFile, "    __HIMEM__:       type = weak, value = $9600; # Presumed RAM end\n");
    fprintf(outputFile, "    __LCADDR__:      type = weak, value = $D400; # Behind quit code\n");
    fprintf(outputFile, "    __LCSIZE__:      type = weak, value = $0C00; # Rest of bank two\n");
    if (makeFull)
        fprintf(outputFile, "    __OVERLAYSIZE__: type = weak, value = $%04X; # biggest overlay size\n", biggestOverlay);
    fprintf(outputFile, "}\n");
    fprintf(outputFile, "MEMORY {\n");
    fprintf(outputFile, "    ZP:     file = \"\", define = yes, start = $0080,                size = $001A;\n");
    fprintf(outputFile, "    HEADER: file = %%O,               start = %%S - $003A,           size = $003A;\n");
    if (makeFull)
        fprintf(outputFile, "    MAIN:   file = %%O, define = yes, start = %%S + __OVERLAYSIZE__, size = __HIMEM__ - __OVERLAYSIZE__ - %%S;\n");
    else
        fprintf(outputFile, "    MAIN:   file = %%O, define = yes, start = %%S,                   size = __HIMEM__ - %%S;\n");
    fprintf(outputFile, "    BSS:    file = \"\",               start = __ONCE_RUN__,         size = __HIMEM__ - __STACKSIZE__ - __ONCE_RUN__;\n");
    fprintf(outputFile, "    LC:     file = \"\", define = yes, start = __LCADDR__,           size = __LCSIZE__;\n");
    for (int i=0; i<numberOverlay; i++) {
        if (makeFull)
            fprintf(outputFile, "    OVL%d:   file = \"%%O.%d\",           start = %%S,                   size = __OVERLAYSIZE__;\n", i+1, i+1);
        else
            fprintf(outputFile, "    OVL%d:   file = \"%%O.%d\",           start = %%S,                   size = __HIMEM__ - %%S;\n", i+1, i+1);
    }
    fprintf(outputFile, "}\n");
    fprintf(outputFile, "SEGMENTS {\n");
    fprintf(outputFile, "    ZEROPAGE: load = ZP,             type = zp;\n");
    fprintf(outputFile, "    EXEHDR:   load = HEADER,         type = ro,                optional = yes;\n");
    fprintf(outputFile, "    STARTUP:  load = MAIN,           type = ro,  define = yes;\n");
    fprintf(outputFile, "    LOWCODE:  load = MAIN,           type = ro,                optional = yes;\n");
    fprintf(outputFile, "    CODE:     load = MAIN,           type = ro;\n");
    fprintf(outputFile, "    RODATA:   load = MAIN,           type = ro;\n");
    fprintf(outputFile, "    DATA:     load = MAIN,           type = rw;\n");
    fprintf(outputFile, "    INIT:     load = MAIN,           type = rw;\n");
    fprintf(outputFile, "    ONCE:     load = MAIN,           type = ro,  define = yes;\n");
    fprintf(outputFile, "    LC:       load = MAIN, run = LC, type = ro,                optional = yes;\n");
    fprintf(outputFile, "    BSS:      load = BSS,            type = bss, define = yes;\n");
    for (int i=0; i<numberOverlay; i++)
        fprintf(outputFile, "    %s:%*sload = OVL%d,           type = ro,  define = yes, optional = yes;\n", argv[3+i], 9-strlen(argv[3+i]), "", i+1);
    fprintf(outputFile, "}\n");
    fprintf(outputFile, "FEATURES {\n");
    fprintf(outputFile, "    CONDES: type    = constructor,\n");
    fprintf(outputFile, "            label   = __CONSTRUCTOR_TABLE__,\n");
    fprintf(outputFile, "            count   = __CONSTRUCTOR_COUNT__,\n");
    fprintf(outputFile, "            segment = ONCE;\n");
    fprintf(outputFile, "    CONDES: type    = destructor,\n");
    fprintf(outputFile, "            label   = __DESTRUCTOR_TABLE__,\n");
    fprintf(outputFile, "            count   = __DESTRUCTOR_COUNT__,\n");
    fprintf(outputFile, "            segment = RODATA;\n");
    fprintf(outputFile, "    CONDES: type    = interruptor,\n");
    fprintf(outputFile, "            label   = __INTERRUPTOR_TABLE__,\n");
    fprintf(outputFile, "            count   = __INTERRUPTOR_COUNT__,\n");
    fprintf(outputFile, "            segment = RODATA,\n");
    fprintf(outputFile, "            import  = __CALLIRQ__;\n");
    fprintf(outputFile, "}\n");
    fclose(outputFile);
    return 0;
}
