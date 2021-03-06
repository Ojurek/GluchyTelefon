// Program 5 - komunikacja przez netlink
//receive

#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NLINK_MSG_LEN 1024
#define NETLINK_USER 31

int main() {
	
	//int received;
	int fd;
	struct sockaddr_nl src_addr;
	struct sockaddr_nl dest_addr;
	struct nlmsghdr *nlh;
	struct iovec iov;
	struct msghdr msg;
	
	fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
	printf("Inside receive main\n");

	if (fd < 0) {
    	printf("Netlink socket creation failed.\n");
    	return -1;
	}

	memset(&src_addr, 0, sizeof(src_addr));

	src_addr.nl_family = AF_NETLINK;   //AF_NETLINK socket protocol
	src_addr.nl_pid = 2;               //application unique id
	src_addr.nl_groups = 0;           //send to multicast address 2

	bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

	nlh=(struct nlmsghdr *) malloc(NLMSG_SPACE(NLINK_MSG_LEN));
	memset(nlh, 0, NLMSG_SPACE(NLINK_MSG_LEN));
	//nlh->nlmsg_len = NLMSG_SPACE(NLINK_MSG_LEN);   //netlink message length 
	//nlh->nlmsg_pid = 2;                     //src application unique id
	//nlh->nlmsg_flags = 0;

	iov.iov_base = (void *)nlh;     //netlink message header base address
	iov.iov_len = nlh->nlmsg_len;   //netlink message length

	dest_addr.nl_family = AF_NETLINK; // protocol family
	dest_addr.nl_pid = 2;   //destination process id
	dest_addr.nl_groups = 0; 

	msg.msg_name = (void *)&dest_addr;  //czy potrzebne??
	msg.msg_namelen = sizeof(dest_addr); //czy potrzebne??
	msg.msg_iov = &iov; //czy potrzebne??
	msg.msg_iovlen = 1; //czy potrzebne??

  	printf("Listening to the MCAST address (3): %d\n", src_addr.nl_groups);
while (1) {
	printf("Befor receive\n");
    recvmsg(fd, &msg, 0);
	printf("After receive\n");

    printf("Received message: %s\n", (char*)NLMSG_DATA(nlh));
  }

  close(fd);
}
