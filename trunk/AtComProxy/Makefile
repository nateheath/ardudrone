#Compile for AR.Drone ARM: make ARM=1

ifdef ARM
CC      := arm-none-linux-gnueabi-gcc
TARGET  := atcomproxy_arm
else
CC      := gcc
TARGET  := atcomproxy
endif
SRCS    := atcomproxy.c
OBJS    := ${SRCS:.c=.o} 
DEPS    := ${SRCS:.c=.dep} 
XDEPS   := $(wildcard ${DEPS}) 

CCFLAGS = -std=gnu99 -O2 -Wall -Werror 
CCFLAGS+= -ggdb

.PHONY: all clean distclean 
all:: ${TARGET} 

ifneq (${XDEPS},) 
include ${XDEPS} 
endif 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS} 
	#strip $@

${OBJS}: %.o: %.c %.dep 
	${CC} ${CCFLAGS} -o $@ -c $< 

${DEPS}: %.dep: %.c Makefile 
	${CC} ${CCFLAGS} -MM $< > $@ 

clean:: 
	-rm -f *~ *.o ${TARGET} 

distclean:: clean
