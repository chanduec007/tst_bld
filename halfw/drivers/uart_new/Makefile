include ../properties.mk
 
SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/libuart.so

CFLAGS+=-I./include -fPIC
 
LDFLAGS+=

install: $(ALL)
	@mkdir -p _install/lib
	@cp $(ALL) _install/lib

all: $(ALLOBJS) $(ALL) install

$(ALL): $(ALLOBJS)
	@mkdir -p _target
	@echo "LD $@"
	@$(CC) $(CFLAGS) -shared -Wl,-soname,libuart.so -o $@ $^ $

include ../common.mk

