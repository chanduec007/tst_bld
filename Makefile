CC=gcc
SYSROOT=/home/faregeo/chandu/HMI/idu15
INCLUDES=-I${SYSROOT}/appfw -I${SYSROOT}/halfw -I${SYSROOT}/aplib -I${SYSROOT}/common
LIB_PATH=-L${SYSROOT}/lib
#LIBS=-lpthread -ljansson
CFLAGS=-Wall -static -L

all: 
	$(CC) -Wall -fPIC -c -o bblib.o ./halfw/hal_bb.c
	#ar -rcv libbblib.a bblib.o
	$(CC) $(INCLUDES) $(CFLAGS) $(LIB_PATH) $(LIBS) ./appfw/appmn.c ./aplib/cserv.c ./appfw/jlibs.c ./aplib/dblog.c ./appfw/diags.c bblib.o -ljansson -lpthread -o btest

clean:
	rm -rf btest

#all: $(CC) $(INCLUDES) ./halfw/hal_bb.c ./appfw/appmn.c ./appfw/jlibs.c ./aplib/dblog.c -ljansson -o test

#
#CC=gcc
#SYSROOT=/home/shree/idubb
#INCLUDES=-I${SYSROOT}/appfw -I${SYSROOT}/halfw -I${SYSROOT}/aplib -I${SYSROOT}/common
#LIB_PATH=-L${SYSROOT}/lib
#LIBS=-lpthread -ljansson
#CFLAGS=-O2-g-Wall-mfloat-abi=hard
# all: 
	#$(CC) $(INCLUDES) $(CFLAGS) $(LIB_PATH) $(LIBS) ./halfw/hal_bb.c ./appfw/appmn.c ./appfw/jlibs.c ./aplib/dblog.c ./appfw/diags.c ./aplib/cserv.c -ljansson -lpthread -o btest


