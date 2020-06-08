obj-m+=netlink_kernel.o

KERNEL_DIR=/lib/modules/$(shell uname -r)/build

all: uninstall build install

build:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

install:
	-sudo insmod netlink_kernel.ko

uninstall:
	-sudo rmmod netlink_kernel
