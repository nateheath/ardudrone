/*
Plug-in for ioctl() to prevent AR.Drone program.elf from changing the GPIO_127 pin.
This is to support loading module dwc_otg.ko for USB Host mode on AR.Drone.

Author: MAPGPS on
	http://www.ardrone-flyers.com/forum/viewforum.php?f=8
	http://www.rcgroups.com/forums/showthread.php?t=1335257
	https://projects.ardrone.org/projects/ardrone-api/boards
	http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1025
	http://bbs.5imx.com/bbs/viewthread.php?tid=415063
Initial: 2011.02.22
Updated: 2011.02.23

Compile:
arm-none-linux-gnueabi-gcc -shared -Wl,-soname,libioctl_arm.so -o libioctl_arm.so ioctl.c -lc -ldl

Usage:
export LD_PRELOAD=/data/video/libioctl_arm.so
kill -9 <PID of program.elf>
insmod /data/video/dwc_otg.ko
program.elf >/dev/null&
*/

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

enum gpio_mode {
	GPIO_INPUT = 0,		//Pin configured for input
	GPIO_OUTPUT_LOW,	//Pin configured for output with low level
	GPIO_OUTPUT_HIGH,	//Pin configured for output with high level
};

struct gpio_direction {
	int pin;
	enum gpio_mode mode;
};

#define GPIO_MAGIC	'p'
#define _IOC_WRITE	1U
#define _IOC_NRSHIFT	0
#define _IOC_NRBITS	8
#define _IOC_TYPEBITS	8
#define _IOC_SIZEBITS	14
#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)
#define _IOC(dir,type,nr,size) \
	(((dir)  << _IOC_DIRSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr)   << _IOC_NRSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))
#define _IOC_TYPECHECK(t)	(sizeof(t))
#define _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#define GPIO_DIRECTION		_IOW(GPIO_MAGIC, 0, struct gpio_direction)


int
ioctl(int fd, int request, unsigned char *argp)
{
	static void *handle = NULL;
	static int (*orig_ioctl)(int, int, char*);

	if (request == GPIO_DIRECTION) {		
		struct gpio_direction *gpio = (struct gpio_direction *)argp;
		fprintf(stderr, "ioctl(): GPIO PIN = %d\n", gpio->pin);

		if (gpio->pin == 127) {
			fprintf(stderr, "****** MAPGPS: Ignore GPIO_127\n");
			return 0;
		}
	}

	if (handle == NULL) {
		char *error;
		handle = dlopen("/lib/libc.so.6", RTLD_LAZY);
		if (!handle) {
			fputs(dlerror(), stderr);
			exit(EXIT_FAILURE);
		}
		orig_ioctl = dlsym(handle, "ioctl");
		if ((error = dlerror()) != NULL) {
			fprintf(stderr, "%s\n", error);
			exit(EXIT_FAILURE);
		}
	}
	
	return orig_ioctl(fd, request, argp);
}
