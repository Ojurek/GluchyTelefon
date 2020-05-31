obj-m+=jajko.o

KERNEL_DIR=/lib/modules/$(shell uname -r)/build

all: uninstall build install

build:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

install:
	-sudo insmod jajko.ko

uninstall:
	-sudo rmmod jajko