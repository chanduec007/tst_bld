#Make file
#Use 'make testspi' to generage testgpio binary to be tested on board.

include ../../properties.mk

SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/

CFLAGS+= -I../include -D_REENTRANT
CFLAGS+= -I../../../../kernel/linux-3.2.0/arch/arm/include/asm

LDFLAGS+= -L../target -lspi



#all:$(ALLOBJS)

#target/cli: $(ALLOBJS)
#	@echo "LD $@"
#	@echo "	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) "
#	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

testspi: spi-test.o
	@echo "@$(CC) $(CFLAGS) -g spi.c spi-test.c -o testspi $(LDFLAGS)"
	@$(CC) $(CFLAGS) -g spi.c spi-test.c -o testspi $(LDFLAGS)


testclean:
	rm -rf *.o 
	rm -rf testspi
	

include ../../common.mk
