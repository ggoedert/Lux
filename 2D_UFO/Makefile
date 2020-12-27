ifndef $(CONFIG)
CONFIG = Size
endif

$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

APPLEWIN = C:\Apple\AppleWin\Applewin.exe -no-printscreen-key
APPLECOMMANDER = C:\Apple\AppleCommander-win64-1.5.0.jar
LOADER_SYSTEM = C:\cc65\target\apple2\util\loader.system

DISKLABEL = TWODUFO
OUTPUT = 2D_UFO
SOURCEDIR = Assets
ASOURCEFILES = HGR.s
AOBJECTFILES = $(ASOURCEFILES:.s=.o)
AOBJECTS = $(addprefix Build/$(CONFIG)/, $(AOBJECTFILES))
CSOURCEFILES = 2D_UFOApplication.c Assets.c MainScene.c PlayerControllerBehaviour.c
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(CONFIG)/, $(COBJECTFILES))
ENGINELIB = ../Engine/Build/$(CONFIG)/Engine.lib

LD = cl65
LDFLAGS = -m Build/$(CONFIG)/$(OUTPUT).map -t apple2 -C apple2-hgr.cfg
AS = ca65
ASFLAGS = -t apple2
CC = cl65 -c
CFLAGS = -t apple2 -I ../Engine/Code/Include
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
	if exist ../Engine/Build/$(CONFIG)/. $(MAKE) CONFIG=$(CONFIG) clean -C ../Engine

prebuild: | Build/$(CONFIG)/.
	$(MAKE) CONFIG=$(CONFIG) -C ../Engine

Build/$(CONFIG)/$(OUTPUT): $(AOBJECTS) $(COBJECTS) $(ENGINELIB)
	$(LD) $(LDFLAGS) -o $@ $(AOBJECTS) $(COBJECTS) $(ENGINELIB)

$(AOBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.s | prebuild
	$(AS) $(ASFLAGS) -o $@ $<

$(COBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)

Build/$(CONFIG)/$(OUTPUT).dsk: Build/$(CONFIG)/$(OUTPUT) | Build/$(CONFIG)/.
	bzip2 -c -d ..\Resource\blank.dsk.bz2 > Build/$(CONFIG)/$(OUTPUT).dsk
	java -jar $(APPLECOMMANDER) -n Build/$(CONFIG)/$(OUTPUT).dsk $(DISKLABEL)
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUT).dsk startup.system sys < $(LOADER_SYSTEM)
	java -jar $(APPLECOMMANDER) -as Build/$(CONFIG)/$(OUTPUT).dsk startup < Build/$(CONFIG)/$(OUTPUT)
