include ../properties.mk
 
SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/libi2c.so

CFLAGS+=-I./include -fPIC
 
LDFLAGS+=

install: $(ALL)
	@mkdir -p _install/lib
	@mkdir -p target
	@cp $(ALL) _install/lib

all: $(ALLOBJS) $(ALL) install

$(ALL): $(ALLOBJS)
	@mkdir -p target
	@echo "LD $@"
	@$(CC) $(CFLAGS) -shared -Wl,-soname,libi2c.so -o $@ $^ $

include ../common.mk

