#Make file
#Use 'make testi2c' to generage testgpio binary to be tested on board.

include ../../properties.mk

SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/

CFLAGS+= -I../include -D_REENTRANT
CFLAGS+= -I../../../../kernel/linux-3.2.0/arch/arm/include/asm

LDFLAGS+= -L../target -li2c



#all:$(ALLOBJS)

#target/cli: $(ALLOBJS)
#	@echo "LD $@"
#	@echo "	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) "
#	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

testi2c: i2c-test.o
	@echo "@$(CC) $(CFLAGS) -g i2c-test.c -o testi2c $(LDFLAGS)"
	@$(CC) $(CFLAGS) -g i2c-test.c -o testi2c $(LDFLAGS)


testclean:
	rm -rf *.o 
	rm -rf testi2c
	

include ../../common.mk
