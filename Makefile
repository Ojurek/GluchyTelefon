CHDEV = chdev
CC = gcc -pthread -g -Wpedantic -Wall -Werror -pedantic-errors

all: info uninstall build compile 

compile:
	$(CC) 1_konsola.c -o 1_konsola.o
	$(CC) 2_argument.c -o 2_argument.o
	$(CC) 3_pipe.c -o 3_pipe.o
	$(CC) 4_chrdev.c -o 4_chrdev.o
	$(CC) 5_netlink.c -o 5_netlink.o
	$(CC) 5_netlink_rec.c -o 5_netlink_rec.o

build:
	cd $(CHDEV) && $(MAKE) build
	cd $(CHDEV) ; sudo insmod jajko.ko

run:
	sudo ./1_konsola.o


clean:
	rm -rf *.o
	cd $(CHDEV) && $(MAKE) clean

uninstall:
	-sudo rmmod jajko
	
tcp:
	gcc 6_server.c -o server.o
	gcc 5_clientTCP.c -o client.o


info:
	echo "Program gluchy telefon do komunikacji w systemie linux"
