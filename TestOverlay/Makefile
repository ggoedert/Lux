ifndef $(CONFIG)
CONFIG = Size
endif

$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

MAKEOVERLAYCONFIG = ..\MakeOverlayConfig\Build\Speed\MakeOverlayConfig.exe
APPLEWIN = C:\Apple\AppleWin\Applewin.exe
APPLECOMMANDER = C:\Apple\AppleCommander-win64-1.5.0.jar
LOADER_SYSTEM = C:\cc65\target\apple2\util\loader.system

OUTPUT = TestOverlay
SOURCEDIR = Code
AMAINSOURCEFILES =
AMAINOBJECTFILES = $(AMAINSOURCEFILES:.s=.o)
AMAINOBJECTS = $(addprefix Build/$(CONFIG)/, $(AMAINOBJECTFILES))
CMAINSOURCEFILES = TestOverlay.c
CMAINOBJECTFILES = $(CMAINSOURCEFILES:.c=.o)
CMAINOBJECTS = $(addprefix Build/$(CONFIG)/, $(CMAINOBJECTFILES))
CMENUSOURCEFILES = Menu.c
CMENUOBJECTFILES = $(CMENUSOURCEFILES:.c=.o)
CMENUOBJECTS = $(addprefix Build/$(CONFIG)/, $(CMENUOBJECTFILES))
CLEVEL1SOURCEFILES = Level1.c
CLEVEL1OBJECTFILES = $(CLEVEL1SOURCEFILES:.c=.o)
CLEVEL1OBJECTS = $(addprefix Build/$(CONFIG)/, $(CLEVEL1OBJECTFILES))
CLEVEL2SOURCEFILES = Level2.c
CLEVEL2OBJECTFILES = $(CLEVEL2SOURCEFILES:.c=.o)
CLEVEL2OBJECTS = $(addprefix Build/$(CONFIG)/, $(CLEVEL2OBJECTFILES))
AOBJECTS = $(AMAINOBJECTS) 
COBJECTS = $(CMAINOBJECTS) $(CMENUOBJECTS) $(CLEVEL1OBJECTS) $(CLEVEL2OBJECTS)

LD = cl65
LDFLAGS = -t apple2 -C $(OUTPUT).cfg
AS = ca65
ASFLAGS = -t apple2
CC = cl65 -c
CFLAGS = -t apple2 -I Build/$(CONFIG)
ifeq ($(CONFIG), Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG), Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG), Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: Build/$(CONFIG)/$(OUTPUT)

install: all | Build/$(CONFIG)/$(OUTPUT).dsk

.PHONY: run
run: install
	$(APPLEWIN) -d1 $(CURDIR)/Build/$(CONFIG)/$(OUTPUT).dsk

.PHONY: clean
clean:
	if exist Build/$(CONFIG)/. rmdir /S /Q Build\$(CONFIG)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build

prebuild: | Build/$(CONFIG)/.
	$(MAKE) CONFIG=Speed -C ../MakeOverlayConfig

Build/$(CONFIG)/$(OUTPUT): $(AOBJECTS) $(COBJECTS)
	$(MAKEOVERLAYCONFIG) -d Build/$(CONFIG)/$(OUTPUT) MENU LEVEL1 LEVEL2
	$(LD) $(LDFLAGS) -o $@ $(AOBJECTS) $(COBJECTS)
	$(MAKEOVERLAYCONFIG) -f Build/$(CONFIG)/$(OUTPUT) MENU LEVEL1 LEVEL2
	$(LD) $(LDFLAGS) -o $@ $(AOBJECTS) $(COBJECTS)

$(AOBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.s | prebuild
	$(AS) $(ASFLAGS) -o $@ $<

$(CMAINOBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) -o $@ $<

$(CMENUOBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) --code-name MENU -o $@ $<

$(CLEVEL1OBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) --code-name LEVEL1 -o $@ $<

$(CLEVEL2OBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) --code-name LEVEL2 -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)

Build/$(CONFIG)/$(OUTPUT).dsk: Build/$(CONFIG)/$(OUTPUT) | Build/$(CONFIG)/.
	bzip2 -c -d ..\Resource\blank.dsk.bz2 > Build/$(CONFIG)/$(OUTPUT).dsk
	java -jar $(APPLECOMMANDER) -n Build/$(CONFIG)/$(OUTPUT).dsk $(OUTPUT)
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUT).dsk startup.system sys < $(LOADER_SYSTEM)
	java -jar $(APPLECOMMANDER) -as Build/$(CONFIG)/$(OUTPUT).dsk startup < Build/$(CONFIG)/$(OUTPUT)
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUT).dsk menu.ovl bin < Build/$(CONFIG)/$(OUTPUT).1
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUT).dsk level1.ovl bin < Build/$(CONFIG)/$(OUTPUT).2
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUT).dsk level2.ovl bin < Build/$(CONFIG)/$(OUTPUT).3
