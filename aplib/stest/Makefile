CC=gcc
SYSROOT=/home/shree/idubb
INCLUDES=-I${SYSROOT}/appfw -I${SYSROOT}/halfw -I${SYSROOT}/aplib -I${SYSROOT}/common
LIB_PATH=-L${SYSROOT}/lib
#LIBS=-lpthread -ljansson
CFLAGS=-Wall -static -L

all: 
	$(CC) $(INCLUDES) $(CFLAGS) $(LIB_PATH) $(LIBS) ../dblog.c udp_client.c -ljansson -lpthread -o udp_client

clean:
	rm -rf udp_client

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


