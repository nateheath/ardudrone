#Compile for AR.Drone ARM: make ARM=1

ifdef ARM
CC = arm-none-linux-gnueabi-gcc
TARGET = libioctl_arm.so
else
CC = gcc
TARGET = libioctl.so
endif

all:
	${CC} -shared -Wl,-soname,$(TARGET) -o $(TARGET) ioctl.c -lc -ldl
