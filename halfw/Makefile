CC=gcc
SYSROOT=/home/shree/idubb/halfw
INCLUDES=-I${SYSROOT}/appfw -I${SYSROOT}/halfw -I${SYSROOT}/aplib -I${SYSROOT}/common
LIB_PATH=-L${SYSROOT}/lib
#LIBS=-lpthread -ljansson
CFLAGS=-Wall -fPIC -static -L

all: 
	$(CC) $(INCLUDES) $(CFLAGS) $(LIB_PATH) $(LIBS) -c -o bblib.o hal_bb.c
	ar -rcv libbblib.a bblib.o

clean:
	rm -rf bblib.o bblib.a

#all: $(CC) $(INCLUDES) ./halfw/hal_bb.c ./appfw/appmn.c ./appfw/jlibs.c ./aplib/dblog.c -ljansson -o test
