// Program 5 - komunikacja przez netlink
//send

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
	
int result;	
char* received="Hello";
	int fd;
	struct sockaddr_nl src_addr;
	struct sockaddr_nl dest_addr;
	struct nlmsghdr *nlh;
	struct iovec iov;
	struct msghdr msg;
	
	fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
	printf("Inside send main\n");

	if (fd < 0) {
    	printf("Netlink socket creation failed.\n");
    	return -1;
	}

	memset(&src_addr, 0, sizeof(src_addr));

	src_addr.nl_family = AF_NETLINK;   //AF_NETLINK socket protocol
	src_addr.nl_pid = getpid();                //application unique id
	//src_addr.nl_groups = 0;          //send to multicast address 2

	result=bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

	printf("Result of bind = %i\n", result);

	nlh=(struct nlmsghdr *) malloc(NLMSG_SPACE(NLINK_MSG_LEN));
	memset(nlh, 0, NLMSG_SPACE(NLINK_MSG_LEN));
	nlh->nlmsg_len = NLMSG_SPACE(NLINK_MSG_LEN);   //netlink message length 
	nlh->nlmsg_pid = getpid();                       //src application unique id
	//nlh->nlmsg_flags = 0;

  	strcpy(NLMSG_DATA(nlh), received);   //copy the payload to be sent

	iov.iov_base = (void *)nlh;     //netlink message header base address
	iov.iov_len = nlh->nlmsg_len;   //netlink message length

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK; // protocol family
	dest_addr.nl_pid = 0;   //destination process id
	dest_addr.nl_groups = 0;

	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	printf("Listening to the MCAST address (3): %d\n", dest_addr.nl_groups);
while (1) {
	printf("Try send message %s\n", (char *)NLMSG_DATA(nlh));
	result=sendmsg(fd, &msg, 0);
	printf("Result of sendmsg = %i\n", result);
	
	sleep(3);
	printf("Try receive message\n");
    recvmsg(fd, &msg, 0);
	printf("After receive\n");

    printf("Received message: %s\n", (char*)NLMSG_DATA(nlh));
}
	close(fd); 
}
