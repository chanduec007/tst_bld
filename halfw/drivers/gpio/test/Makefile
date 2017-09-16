#Make file
#Use 'make testgpio' to generage testgpio binary to be tested on board.

include ../../properties.mk

SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/

CFLAGS+= -I../include -D_REENTRANT
CFLAGS+= -I../../../../kernel/linux-3.2.0/arch/arm/include/asm

LDFLAGS+=-L../target -lgpio


#all:$(ALLOBJS)

#target/cli: $(ALLOBJS)
#	@echo "LD $@"
#	@echo "	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) "
#	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

testgpio: gpio-test.o
	@echo "@$(CC) $(CFLAGS) -g gpio-test.c -o testgpio $(LDFLAGS)"
	@$(CC) $(CFLAGS) -g gpio-test.c -o testgpio $(LDFLAGS)

testClean:
	rm -rf *.o 
	rm -rf testgpio
	

include ../../common.mk
