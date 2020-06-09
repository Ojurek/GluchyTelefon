// Program 5 - komunikacja przez netlink

#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NLINK_MSG_LEN 1024

int main() {
	
	char* received="Hello";
	int fd;
	struct sockaddr_nl src_addr;
	struct sockaddr_nl dest_addr;
	struct nlmsghdr *nlh;
	struct iovec iov;
	struct msghdr msg;
	
	fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
	printf("Inside send main\n");

	if (fd < 0) {
    	printf("Netlink socket creation failed.\n");
    	return -1;
	}

	memset(&src_addr, 0, sizeof(src_addr));

	src_addr.nl_family = AF_NETLINK;   //AF_NETLINK socket protocol
	src_addr.nl_pid = 1;               //application unique id
	src_addr.nl_groups = 0;            //send to multicast address 2

	bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

	nlh=(struct nlmsghdr *) malloc(NLMSG_SPACE(NLINK_MSG_LEN));
	memset(nlh, 0, NLMSG_SPACE(NLINK_MSG_LEN));
	nlh->nlmsg_len = NLMSG_SPACE(NLINK_MSG_LEN);   //netlink message length 
	nlh->nlmsg_pid = 1;                       //src application unique id
	nlh->nlmsg_flags = 0;

  	strcpy(NLMSG_DATA(nlh), received);   //copy the payload to be sent

	iov.iov_base = (void *)nlh;     //netlink message header base address
	iov.iov_len = nlh->nlmsg_len;   //netlink message length

	dest_addr.nl_family = AF_NETLINK; // protocol family
	dest_addr.nl_pid = 0;   //destination process id
	dest_addr.nl_groups = 0; 

	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	//send the message
	sleep(3);
	sendmsg(fd, &msg, 0);
	printf("Send message %s\n", (char *)NLMSG_DATA(nlh));

	close(fd); // close the socket
}
