ifndef $(CONFIG)
CONFIG = Size
endif

$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

ifneq (,$(findstring FLOAT,$(OPTIONS)))
FLOAT = defined
else
FLOAT =
endif

OUTPUT = Engine.lib
SOURCEDIR = Code/Source
ASOURCEFILES = Apple2Id.s Vaporlock.s
AOBJECTFILES = $(ASOURCEFILES:.s=.o)
AOBJECTS = $(addprefix Build/$(CONFIG)/, $(AOBJECTFILES))
CSOURCEFILES = IO.c String.c Debug.c QualitySettings.c Object.c Storage.c Resources.c Camera.c Time.c Collection.c List.c Stack.c Screen.c Vector2.c Asset.c Sprite.c Component.c Transform.c Renderer.c SpriteRenderer.c Behaviour.c CustomBehaviour.c GameObject.c SceneManager.c Scene.c Application.c
ifdef FLOAT
CSOURCEFILES += Float.c
endif
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(CONFIG)/, $(COBJECTFILES))

AR = ar65
ARFLAGS = a
AS = ca65
ASFLAGS = -t apple2
CC = cl65 -c
CFLAGS = -t apple2 -I Code/Include
ifdef FLOAT
CFLAGS += -D FLOAT
endif
ifeq ($(CONFIG), Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG), Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG), Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: Build/$(CONFIG)/$(OUTPUT)

.PHONY: clean
clean:
	if exist Build/$(CONFIG)/. rmdir /S /Q Build\$(CONFIG)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build

Build/$(CONFIG)/$(OUTPUT): $(AOBJECTS) $(COBJECTS)
	$(AR) $(ARFLAGS) $@ $(AOBJECTS) $(COBJECTS)

$(AOBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.s | Build/$(CONFIG)/.
	$(AS) $(ASFLAGS) -o $@ $<

$(COBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | Build/$(CONFIG)/.
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)
