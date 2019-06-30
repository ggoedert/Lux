ifndef $(CONFIG)
CONFIG = Speed
endif

$(info CONFIG set to $(CONFIG))

ifeq (,$(filter $(CONFIG), Debug Size Speed))
$(error Unknown CONFIG $(CONFIG), set either to Debug, Size or Speed. Omit to default to Size)
endif

OUTPUT = MakeOverlayConfig.exe
SOURCEDIR = Code
CPPSOURCEFILES = MakeOverlayConfig.cpp
CPPOBJECTFILES = $(CPPSOURCEFILES:.cpp=.o)
CPPOBJECTS = $(addprefix Build/$(CONFIG)/, $(CPPOBJECTFILES))

LD = gcc
LDFLAGS = 
CC = gcc -c
CFLAGS = 
ifeq ($(CONFIG), Debug)
CFLAGS += -D _DEBUG -g
else ifeq ($(CONFIG), Size)
CFLAGS += -D NDEBUG -Os
else ifeq ($(CONFIG), Speed)
CFLAGS += -D NDEBUG -O3
endif

all: Build/$(CONFIG)/$(OUTPUT)

.PHONY: clean
clean:
	if exist Build/$(CONFIG)/. rmdir /S /Q Build\$(CONFIG)
	if exist Build/. dir /b Build | >nul find /v "" || rmdir /S /Q Build

Build/$(CONFIG)/$(OUTPUT): $(CPPOBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(CPPOBJECTS)
ifneq ($(CONFIG), Debug)
	strip $@
endif

$(CPPOBJECTS): Build/$(CONFIG)/%.o : $(SOURCEDIR)/%.cpp | Build/$(CONFIG)/.
	$(CC) $(CFLAGS) -o $@ $<

Build/.:
	mkdir Build

Build/$(CONFIG)/.: | Build/.
	mkdir Build\$(CONFIG)
