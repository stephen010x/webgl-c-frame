TARGET := bin
TEXTEN := wasm

TMPDIR := tmp
SRCDIR := src
BINDIR := bin


CC := emcc
CFLAGS := 
LFLAGS := -sOFFSCREEN_FRAMEBUFFER -sOFFSCREENCANVAS_SUPPORT -sFETCH
BFLAGS := -Wall -Wextra -Wpedantic -Wconversion -Wundef
BFLAGS := $(BFLAGS) -Wno-language-extension-token -Wno-gnu -std=gnu2x
BFLAGS := -Wno-format-security



DEFAULT := fast


GOAL := $(firstword $(MAKECMDGOALS))
GOAL := $(if $(GOAL),$(GOAL),$(DEFAULT))
# should grab all paths relative to makefile.
SRCS := $(shell find $(SRCDIR) -name "*.c")
ifneq ($(GOAL),clean)
	OBJS := $(SRCS:%.c=$(TMPDIR)/$(GOAL)/%.o)
	DEPS := $(SRCS:%.c=$(TMPDIR)/$(GOAL)/%.d)
endif
BINTARG := $(BINDIR)/$(TARGET)


#CURRENTDIR := $(shell pwd)


ifeq ($(OS),Windows_NT) 
    $(error Incompatable operating system)
else
    OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
    ifeq ($(OS),Linux)
    	LINUX := LINUX
    	BLFLAGS += -target *-*-linux-gnu
    	#MAKEOSFILE := make/linux.mk
    else
		$(error Incompatable operating system)
    endif
endif









###########################################
#                                         #
#      LINUX                              #
#                                         #
###########################################
ifdef LINUX



all: $(DEFAULT)
fast: _fast $(BINTARG).$(TEXTEN)
debug: _debug $(BINTARG).$(TEXTEN)
release: _release $(BINTARG).$(TEXTEN)
static: _static $(LIBTARG).a
dynamic: _dynamic $(LIBTARG).so


-include $(DEPS)


_fast:
	$(eval CFLAGS += -DDEBUG_MODE)
	$(eval BFLAGS += -g -O0)

_debug:
	$(eval CFLAGS += -DDEBUG_MODE)
	$(eval BFLAGS += -g -Og)

_release: _optimize

_optimize:
	$(eval LFLAGS += -Wl,--gc-sections -s -flto)
	$(eval BFLAGS += -Oz)


$(BINTARG).$(TEXTEN): $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(BFLAGS) $(LFLAGS) -o $@ -o $(basename $@).js $^

$(TMPDIR)/$(GOAL)/%.o: %.c $(TMPDIR)/$(GOAL)/%.d
	mkdir -p $(dir $@)
	$(CC) $(BFLAGS) $(CFLAGS) -c $< -o $@

$(TMPDIR)/$(GOAL)/%.d: %.c
	mkdir -p $(dir $@)
	$(CC) -MM -MT $(patsubst %.d,%.o,$@) -MF $@ -c $<



clean:
	rm -rf $(TMPDIR)
	rm -rf $(BINDIR)


endif





.PHONY: all fast debug release static dynamic clean test
.PHONY: _build _fast _debug _release _dynamic _static _optimize
