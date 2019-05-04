ifndef $(CONFIG)
CONFIG = Size
endif

$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

OUTPUT = Test
SOURCEDIR = Code
CSOURCEFILES = hello.c
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(CONFIG)/, $(COBJECTFILES))

LD = cl65
LDFLAGS = -t apple2 -L ../Engine/Build/$(CONFIG)
CC = cl65 -c
CFLAGS = -t apple2 -I Build/$(CONFIG) -I ../Engine/Code/Include
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
	D:\Apple\AppleWin1.27.5.0\Applewin.exe -d1 $(CURDIR)/Build/$(CONFIG)/$(OUTPUT).dsk

.PHONY: clean
clean:
	if exist Build/$(CONFIG)/. rmdir /S /Q Build\$(CONFIG)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build
	if exist ../Engine/Build/$(CONFIG)/. $(MAKE) CONFIG=$(CONFIG) clean -C ../Engine

prebuild: | Build/$(CONFIG)/.
	$(MAKE) CONFIG=$(CONFIG) -C ../Engine

Build/$(CONFIG)/$(OUTPUT): $(COBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(COBJECTS) Engine.lib

$(COBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)

Build/$(CONFIG)/$(OUTPUT).dsk: Build/$(CONFIG)/$(OUTPUT) | Build/$(CONFIG)/.
	bzip2 -c -d ..\Resource\blank.dsk.bz2 > Build/$(CONFIG)/$(OUTPUT).dsk
	java -jar D:\Apple\AppleCommander-win64-1.4.0.jar -n Build/$(CONFIG)/$(OUTPUT).dsk $(OUTPUT)
	java -jar D:\Apple\AppleCommander-win64-1.4.0.jar -p Build/$(CONFIG)/$(OUTPUT).dsk startup.system sys < D:\cc65\target\apple2\util\loader.system
	java -jar D:\Apple\AppleCommander-win64-1.4.0.jar -as Build/$(CONFIG)/$(OUTPUT).dsk startup < Build/$(CONFIG)/$(OUTPUT)
