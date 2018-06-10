ifneq ($(KERNELRELEASE),)
obj-m := hello.o
else
obj-m := hello.o
#KERNELDIR ?= /lib/modules/$(shell uname -r) /build
KERNELDIR = /home/xb/A60/kernel
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
endif
