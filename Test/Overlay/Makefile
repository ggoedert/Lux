ifndef CONFIG
CONFIG = Size
endif
$(info CONFIG set to $(CONFIG))
ifeq ($(filter $(CONFIG),Debug Size Speed),)
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

MAKECONFIG = ..\..\Util\MakeConfig\Build\Speed\MakeConfig.exe
APPLEWIN = C:\Apple\AppleWin\Applewin.exe -no-printscreen-key
APPLECOMMANDER = C:\Apple\AppleCommander-win64-1.5.0.jar
LOADER_SYSTEM = C:\cc65\target\apple2\util\loader.system

OUTPUT = TestOverlay
OUTPUTDIR = $(OUTPUT)
OUTPUTLABEL = $(OUTPUT)
AMAINSOURCEFILES =
AMAINOBJECTFILES = $(AMAINSOURCEFILES:.s=.o)
AMAINOBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(AMAINOBJECTFILES))
CMAINSOURCEFILES = TestOverlay.c
CMAINOBJECTFILES = $(CMAINSOURCEFILES:.c=.o)
CMAINOBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(CMAINOBJECTFILES))
CMENUSOURCEFILES = Menu.c
CMENUOBJECTFILES = $(CMENUSOURCEFILES:.c=.o)
CMENUOBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(CMENUOBJECTFILES))
CLEVEL1SOURCEFILES = Level1.c
CLEVEL1OBJECTFILES = $(CLEVEL1SOURCEFILES:.c=.o)
CLEVEL1OBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(CLEVEL1OBJECTFILES))
CLEVEL2SOURCEFILES = Level2.c
CLEVEL2OBJECTFILES = $(CLEVEL2SOURCEFILES:.c=.o)
CLEVEL2OBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(CLEVEL2OBJECTFILES))
AOBJECTS = $(AMAINOBJECTS) 
COBJECTS = $(CMAINOBJECTS) $(CMENUOBJECTS) $(CLEVEL1OBJECTS) $(CLEVEL2OBJECTS)

LD = cl65
LDFLAGS = -t apple2 -C Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).cfg
AS = ca65
ASFLAGS = -t apple2
CC = cl65 -c
CFLAGS = -t apple2
ifeq ($(CONFIG),Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG),Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG),Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk | Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT)

run: all
	$(APPLEWIN) -d1 $(CURDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk

.PHONY: clean
clean:
	if exist Build/$(CONFIG)/$(OUTPUTDIR)/. rmdir /S /Q Build\$(CONFIG)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build

prebuild: | Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(MAKE) CONFIG=Speed -C ../../Util/MakeConfig

Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT): $(AOBJECTS) $(COBJECTS)
	$(MAKECONFIG) -d Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT) MENU LEVEL1 LEVEL2
	$(LD) $(LDFLAGS) -o $@ $(AOBJECTS) $(COBJECTS)
	$(MAKECONFIG) -f Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT) MENU LEVEL1 LEVEL2
	$(LD) $(LDFLAGS) -o $@ $(AOBJECTS) $(COBJECTS)

$(AOBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.s | prebuild
	$(AS) $(ASFLAGS) -o $@ $<

$(CMAINOBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.c | prebuild
	$(CC) $(CFLAGS) -o $@ $<

$(CMENUOBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.c | prebuild
	$(CC) $(CFLAGS) --code-name MENU -o $@ $<

$(CLEVEL1OBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.c | prebuild
	$(CC) $(CFLAGS) --code-name LEVEL1 -o $@ $<

$(CLEVEL2OBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.c | prebuild
	$(CC) $(CFLAGS) --code-name LEVEL2 -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)

Build/$(CONFIG)/$(OUTPUTDIR)/.: | Build/$(CONFIG)/.
	mkdir Build\$(CONFIG)\$(OUTPUTDIR)

Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk: Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT) | Build/$(CONFIG)/$(OUTPUTDIR)/.
	bzip2 -c -d ..\..\Resource\blank.dsk.bz2 > Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk
	java -jar $(APPLECOMMANDER) -n Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk $(OUTPUTLABEL)
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk startup.system sys < $(LOADER_SYSTEM)
	java -jar $(APPLECOMMANDER) -as Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk startup < Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT)
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk menu.ovl bin < Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).1
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk level1.ovl bin < Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).2
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk level2.ovl bin < Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).3
