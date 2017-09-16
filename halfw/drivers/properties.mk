
.PHONY: uninstall distclean clean all install 

HOSTCC=gcc

ARCH=armv7a

export TI_SDK_PATH=/opt/ti-processor-sdk-linux-am335x-evm-03.02.00.05
export LINUX_DEVKIT_PATH=$(TI_SDK_PATH)/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/
export CROSS_COMPILE=/opt/ti-processor-sdk-linux-am335x-evm-03.02.00.05/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf-
TARGETHOST=arm-linux-gnueabihf-

BUILDHOST=$(shell uname -m)-pc-linux-gnu

CROSS:=$(LINUX_DEVKIT)$(TARGETHOST)-
CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++
AR=$(CROSS_COMPILE)ar
LD=$(CROSS_COMPILE)ld
RANLIB=$(CROSS_COMPILE)ranlib
STRIP=$(CROSS_COMPILE)strip

SDK_LIBS=$(LINUX_DEVKIT_PATH)/$(TARGETHOST)

TOOLDIR=/opt/hp/Sahara
SYSROOT=$(TOOLDIR)/$(TARGETHOST)/sysroot
DBGROOT=$(TOOLDIR)/$(TARGETHOST)/debug-root

CFLAGS=-g -O0
LDFLAGS=

