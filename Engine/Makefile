ifndef ROOTDIR
ROOTDIR = $(CURDIR)
endif
$(info ROOTDIR set to $(ROOTDIR))

ifndef CONFIG
CONFIG = Size
endif
$(info CONFIG set to $(CONFIG))
ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

ifdef OPTIONS
$(info OPTIONS set to $(OPTIONS))
else
$(info OPTIONS not set)
endif

OUTPUTDIR = Engine
OUTPUT = Engine.lib
ASOURCEFILES = Apple2Id.s Vaporlock.s
AOBJECTFILES = $(ASOURCEFILES:.s=.o)
AOBJECTS = $(addprefix $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/, $(AOBJECTFILES))
CSOURCEFILES = IO.c String.c Debug.c QualitySettings.c Object.c Camera.c Time.c Collection.c List.c Stack.c Screen.c Vector2.c Sprite.c Component.c Transform.c Renderer.c SpriteRenderer.c Behaviour.c CustomBehaviour.c GameObject.c SceneManager.c Scene.c Application.c
ifneq ($(findstring FLOAT, $(OPTIONS)),)
CSOURCEFILES += Float.c
endif
DEPENDFILES = $(CSOURCEFILES:.c=.d)
DEPENDS = $(addprefix $(ROOTDIR)/Build/Depends/$(OUTPUTDIR)/, $(DEPENDFILES))
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/, $(COBJECTFILES))

AR = ar65
ARFLAGS = a
AS = ca65
ASFLAGS = -t apple2
CC = cl65 -c
CFLAGS = -t apple2 -I Include
ifneq ($(findstring FLOAT, $(OPTIONS)),)
CFLAGS += -D FLOAT
endif
ifeq ($(CONFIG), Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG), Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG), Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT)

.PHONY: clean
clean:
	if exist $(ROOTDIR)/Build/Depends/. rmdir /S /Q $(ROOTDIR)\Build\Depends
	if exist $(ROOTDIR)/Build/$(CONFIG)/. rmdir /S /Q $(ROOTDIR)\Build\$(CONFIG)
	if exist $(ROOTDIR)/Build/. dir /b $(ROOTDIR)\Build | >nul find /v "" || rmdir /S /Q $(ROOTDIR)\Build

$(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/$(OUTPUT): $(AOBJECTS) $(COBJECTS)
	$(AR) $(ARFLAGS) $@ $(AOBJECTS) $(COBJECTS)

$(AOBJECTS): $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/%.o : Source/%.s | $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(AS) $(ASFLAGS) -o $@ $<

$(COBJECTS): $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/%.o : Source/%.c | $(ROOTDIR)/Build/Depends/$(OUTPUTDIR)/. $(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/.
	$(CC) $(CFLAGS) --create-dep $(ROOTDIR)/Build/Depends/$(OUTPUTDIR)/$*.d -o $@ $<

$(ROOTDIR)/Build/.:
	mkdir $(subst /,\,$(ROOTDIR))\Build

$(ROOTDIR)/Build/Depends/.: | $(ROOTDIR)/Build/.
	mkdir $(subst /,\,$(ROOTDIR))\Build\Depends

$(ROOTDIR)/Build/Depends/$(OUTPUTDIR)/.: | $(ROOTDIR)/Build/Depends/.
	mkdir $(subst /,\,$(ROOTDIR))\Build\Depends\$(OUTPUTDIR)

$(ROOTDIR)/Build/$(CONFIG)/.: | $(ROOTDIR)/Build/.
	mkdir $(subst /,\,$(ROOTDIR))\Build\$(CONFIG)

$(ROOTDIR)/Build/$(CONFIG)/$(OUTPUTDIR)/.: | $(ROOTDIR)/Build/$(CONFIG)/.
	mkdir $(subst /,\,$(ROOTDIR))\Build\$(CONFIG)\$(OUTPUTDIR)

include $(wildcard $(DEPENDS))
