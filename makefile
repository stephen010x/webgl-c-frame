TARGET := bin
TEXTEN := wasm

TMPDIR := tmp
SRCDIR := src
BINDIR := bin


CC := emcc
CFLAGS := 
LFLAGS := -sOFFSCREEN_FRAMEBUFFER -sOFFSCREENCANVAS_SUPPORT 
# --proxy-to-worker -pthread
LFLAGS := $(LFLAGS) -sFETCH -pthread -sPTHREAD_POOL_SIZE=4
BFLAGS := -Wall -Wextra -Wpedantic -Wconversion -Wundef
BFLAGS := $(BFLAGS) -Wno-language-extension-token -Wno-gnu -std=gnu2x
BFLAGS := -Wno-format-security
#-sWASM=2



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
	$(eval BFLAGS += -g -O0 -gsource-map -sASSERTIONS=2 -sGL_DEBUG=1)

_debug:
	$(eval CFLAGS += -DDEBUG_MODE)
	$(eval BFLAGS += -g -Og -gsource-map -sASSERTIONS=2 -sGL_DEBUG=1)

_release: _optimize

# -Oz  ## smaller than -Os, but also slower
_optimize:
	$(eval LFLAGS += -Wl,--gc-sections -s -flto --closure 1 -sMODULARIZE)
	$(eval BFLAGS += -Os -g0)


$(BINTARG).$(TEXTEN): $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(BFLAGS) $(LFLAGS) -o $@ -o $(basename $@).js -o $(basename $@).html $^

$(TMPDIR)/$(GOAL)/%.o: %.c $(TMPDIR)/$(GOAL)/%.d
	mkdir -p $(dir $@)
	$(CC) $(BFLAGS) $(CFLAGS) -c $< -o $@

$(TMPDIR)/$(GOAL)/%.d: %.c
	mkdir -p $(dir $@)
	$(CC) -MM -MT $(patsubst %.d,%.o,$@) -MF $@ -c $<



clean:
	rm -rf $(TMPDIR)
	rm -rf $(BINDIR)

chrome:
	./serve.sh & google-chrome --enable-features=SharedArrayBuffer 0.0.0.0:8000


endif





.PHONY: all fast debug release static dynamic clean test chrome
.PHONY: _build _fast _debug _release _dynamic _static _optimize
