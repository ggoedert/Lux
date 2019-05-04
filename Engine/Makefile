ifndef $(CONFIG)
CONFIG = Size
endif

$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

OUTPUT = Engine.lib
SOURCEDIR = Code/Source
CSOURCEFILES = Engine.c
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(CONFIG)/, $(COBJECTFILES))

AR = ar65
ARFLAGS = a
CC = cl65 -c
CFLAGS = -t apple2 -I Code/Include
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

Build/$(CONFIG)/$(OUTPUT): $(COBJECTS)
	$(AR) $(ARFLAGS) $@ $(COBJECTS)

$(COBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | Build/$(CONFIG)/.
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)
