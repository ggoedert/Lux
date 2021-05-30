ifndef CONFIG
CONFIG = Size
endif
$(info CONFIG set to $(CONFIG))
ifeq ($(filter $(CONFIG),Debug Size Speed),)
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

APPLEWIN = C:\Apple\AppleWin\Applewin.exe -no-printscreen-key
APPLECOMMANDER = C:\Apple\AppleCommander-win64-1.5.0.jar
LOADER_SYSTEM = C:\cc65\target\apple2\util\loader.system

OUTPUT = Clipper
OUTPUTDIR = $(OUTPUT)
OUTPUTLABEL = $(OUTPUT)
ASOURCEFILES = $(wildcard *.s)
AOBJECTFILES = $(ASOURCEFILES:.s=.o)
AOBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(AOBJECTFILES))
CSOURCEFILES = $(wildcard *.c)
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(CONFIG)/$(OUTPUTDIR)/, $(COBJECTFILES))

LD = cl65
LDFLAGS = -t apple2enh --start-addr 0x4000
AS = ca65
ASFLAGS = -t apple2enh
CC = cl65 -c
CFLAGS = -t apple2enh
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
	if exist Build/$(CONFIG)/. rmdir /S /Q Build\$(CONFIG)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build

Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT): $(AOBJECTS) $(COBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(AOBJECTS) $(COBJECTS)

$(AOBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.s | Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(AS) $(ASFLAGS) -o $@ $<

$(COBJECTS): Build/$(CONFIG)/$(OUTPUTDIR)/%.o : %.c | Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(CC) $(CFLAGS) -o $@ $<

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
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk a2e.hi.tgi rel 0 < C:\cc65\target\apple2enh\drv\tgi\a2e.hi.tgi
	java -jar $(APPLECOMMANDER) -p Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk a2e.lo.tgi rel 0 < C:\cc65\target\apple2enh\drv\tgi\a2e.lo.tgi
	java -jar $(APPLECOMMANDER) -as Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT).dsk startup < Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT)
