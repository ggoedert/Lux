space = $() $()
comma = ,

ifndef ROOTDIR
ROOTDIR = $(CURDIR)
endif
$(info ROOTDIR set to $(ROOTDIR))

ifndef CONFIG
CONFIG = Size
endif
$(info CONFIG set to $(CONFIG))
ifeq ($(filter $(CONFIG),Debug Size Speed),)
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

ifdef OPTIONS
$(info OPTIONS set to $(OPTIONS))
else
$(info OPTIONS not set)
endif
ifneq ($(filter FLOAT,$(subst $(comma),$(space),$(OPTIONS))),)
FLOAT = 1
endif

OUTPUT = Engine.lib
OUTPUTDIR = Engine
ASOURCEFILESALL = $(subst ../Source/,,$(wildcard ../Source/*.s))
ASOURCEFILES = $(ASOURCEFILESALL)
AOBJECTFILES = $(ASOURCEFILES:.s=.o)
AOBJECTS = $(addprefix $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/, $(AOBJECTFILES))
ADEPENDFILES = $(ASOURCEFILES:.s=.d)
ADEPENDS = $(addprefix $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/, $(ADEPENDFILES))
CSOURCEFILESALL = $(subst ../Source/,,$(wildcard ../Source/*.c))
ifdef FLOAT
CSOURCEFILESFLOAT = $(CSOURCEFILESALL)
else
CSOURCEFILESFLOAT = $(subst Float.c,,$(CSOURCEFILESALL))
endif
CSOURCEFILES = $(CSOURCEFILESFLOAT)
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/, $(COBJECTFILES))
CDEPENDFILES = $(CSOURCEFILES:.c=.d)
CDEPENDS = $(addprefix $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/, $(CDEPENDFILES))

AR = ar65
ARFLAGS = a
AS = ca65
ASFLAGS = -t apple2
CC = cl65 -c
CFLAGS = -t apple2 -I ../Include
ifdef FLOAT
CFLAGS += -D FLOAT
endif
ifeq ($(CONFIG),Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG),Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG),Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT)

.PHONY: clean
clean:
	if exist $(ROOTDIR)/Build/$(CONFIG)/. rmdir /S /Q $(subst /,\,$(ROOTDIR))\Build\$(CONFIG)
	if exist $(ROOTDIR)/Build/. dir /b $(subst /,\,$(ROOTDIR))\Build | >nul find /v "" || rmdir /S /Q $(subst /,\,$(ROOTDIR))\Build

$(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT): $(AOBJECTS) $(COBJECTS)
	$(AR) $(ARFLAGS) $@ $(AOBJECTS) $(COBJECTS)

$(AOBJECTS): $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/%.o : ../Source/%.s | $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(AS) $(ASFLAGS) --create-dep $(@:.o=.d) -o $@ $<

$(COBJECTS): $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/%.o : ../Source/%.c | $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(CC) $(CFLAGS) --create-dep $(@:.o=.d) -o $@ $<

$(ROOTDIR)/Build/.:
	mkdir $(subst /,\,$(ROOTDIR))\Build

$(ROOTDIR)/Build/$(CONFIG)/.: | $(ROOTDIR)/Build/.
	mkdir $(subst /,\,$(ROOTDIR))\Build\$(CONFIG)

$(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/.: | $(ROOTDIR)/Build/$(CONFIG)/.
	mkdir $(subst /,\,$(ROOTDIR))\Build\$(CONFIG)\$(OUTPUTDIR)

include $(wildcard $(ADEPENDS))
include $(wildcard $(CDEPENDS))
