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

OUTPUT = Engine.lib
SOURCEDIR = Code/Source
CSOURCEFILES = Engine.c
COBJECTFILES = $(CSOURCEFILES:.c=.o)
COBJECTS = $(addprefix Build/$(TARGET)/$(CONFIG)/, $(COBJECTFILES))
ifeq ($(TARGET), Apple2)
SYSTEM = apple2
else ifeq ($(TARGET), Apple2e)
SYSTEM = apple2enh
endif

AR = ar65
ARFLAGS = a
CC = cl65 -c
CFLAGS = -t $(SYSTEM) -I Code/Include
ifeq ($(CONFIG), Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG), Size)
CFLAGS += -D NDEBUG -Or
else ifeq ($(CONFIG), Speed)
CFLAGS += -D NDEBUG -Oris
endif

all: Build/$(TARGET)/$(CONFIG)/$(OUTPUT)

.PHONY: clean
clean:
	if exist Build/$(TARGET)/$(CONFIG)/. rmdir /S /Q Build\$(TARGET)\$(CONFIG)
	if exist Build/$(TARGET)/. dir /b Build\$(TARGET) | >nul find /v "" || rmdir /S /Q Build\$(TARGET)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build

Build/$(TARGET)/$(CONFIG)/$(OUTPUT): $(COBJECTS)
	$(AR) $(ARFLAGS) $@ $(COBJECTS)

$(COBJECTS): Build/$(TARGET)/$(CONFIG)/%.o : $(SOURCEDIR)/%.c | Build/$(TARGET)/$(CONFIG)/.
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(TARGET)/.: | Build/.
	mkdir Build\$(TARGET)
	
Build/$(TARGET)/$(CONFIG)/.: | Build/$(TARGET)/.
	mkdir Build\$(TARGET)\$(CONFIG)
