#Make file
#Use 'make testspi' to generage testgpio binary to be tested on board.

include ../../properties.mk

SRCS=$(wildcard *.c)
ALLOBJS=$(patsubst %.c,target/%.o,$(SRCS))
ALL=target/

CFLAGS+= -I../include -D_REENTRANT
CFLAGS+= -I../../../../kernel/linux-3.2.0/arch/arm/include/asm

LDFLAGS+= -L../target -luart -lgpio



#all:$(ALLOBJS)

#target/cli: $(ALLOBJS)
#	@echo "LD $@"
#	@echo "	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) "
#	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

testspi: uart_init.o
	@echo "@$(CC) $(CFLAGS) -g uart_init.c -o testuart $(LDFLAGS)"
	@$(CC) $(CFLAGS) -g uart_init.c -o testuart $(LDFLAGS)


testclean:
	rm -rf *.o 
	rm -rf testuart
	

include ../../common.mk
