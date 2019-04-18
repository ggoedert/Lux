ifndef $(TARGET)
TARGET = None
endif
ifndef $(CONFIG)
CONFIG = Size
endif

$(info TARGET set to $(TARGET))
$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(TARGET), Apple2 Apple2e))
$(error Unknown TARGET $(TARGET), set either to Apple2 or Apple2e)
endif

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

OUTPUT = Test
SOURCEDIR = Code
CSOURCEFILES = hello.c
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(TARGET)/$(CONFIG)/, $(COBJECTFILES))
ifeq ($(TARGET), Apple2)
SYSTEM = apple2
else ifeq ($(TARGET), Apple2e)
SYSTEM = apple2enh
endif

LD = cl65
LDFLAGS = -t $(SYSTEM) -L ../Engine/Build/$(TARGET)/$(CONFIG)
CC = cl65 -c
CFLAGS = -t $(SYSTEM) -I Build/$(TARGET)/$(CONFIG) -I ../Engine/Code/Include
ifeq ($(CONFIG), Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG), Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG), Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: Build/$(TARGET)/$(CONFIG)/$(OUTPUT)

install: all | Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk

.PHONY: run
run: install
	D:\Apple\AppleWin1.27.5.0\Applewin.exe -d1 $(CURDIR)/Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk

.PHONY: clean
clean:
	if exist Build/$(TARGET)/$(CONFIG)/. rmdir /S /Q Build\$(TARGET)\$(CONFIG)
	if exist Build/$(TARGET)/. dir /b Build\$(TARGET) | >nul find /v "" || rmdir /S /Q Build\$(TARGET)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build
	if exist ../Engine/Build/$(TARGET)/$(CONFIG)/. $(MAKE) TARGET=$(TARGET) CONFIG=$(CONFIG) clean -C ../Engine

prebuild: | Build/$(TARGET)/$(CONFIG)/.
	$(MAKE) TARGET=$(TARGET) CONFIG=$(CONFIG) -C ../Engine

Build/$(TARGET)/$(CONFIG)/$(OUTPUT): $(COBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(COBJECTS) Engine.lib

$(COBJECTS): Build/$(TARGET)/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | prebuild
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(TARGET)/.: | Build/.
	mkdir Build\$(TARGET)
	
Build/$(TARGET)/$(CONFIG)/.: | Build/$(TARGET)/.
	mkdir Build\$(TARGET)\$(CONFIG)

Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk: | Build/$(TARGET)/$(CONFIG)/.
	bzip2 -c -d ..\Resource\blank.dsk.bz2 > Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk
	java -jar D:\Apple\AppleCommander-win64-1.4.0.jar -n Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk $(OUTPUT)
	java -jar D:\Apple\AppleCommander-win64-1.4.0.jar -p Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk loader.system sys < D:\cc65\target\apple2\util\loader.system
	java -jar D:\Apple\AppleCommander-win64-1.4.0.jar -as Build/$(TARGET)/$(CONFIG)/$(OUTPUT).dsk loader < Build/$(TARGET)/$(CONFIG)/$(OUTPUT)
