include ../properties.mk
 
SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/libgpio.so

CFLAGS+=-I./include -fPIC
 
#LDFLAGS+= -L../../packages/_install/lib -lssl -lcrypto -lpthread 

install: $(ALL)
	@mkdir -p _install/lib
	@cp $(ALL) _install/lib

all: $(ALLOBJS) $(ALL) install

$(ALL): $(ALLOBJS)
	@echo "LD $@"
	@$(CC) $(CFLAGS) -shared -Wl,-soname,libgpio.so -o $@ $^ $

include ../common.mk
