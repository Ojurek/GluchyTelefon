
#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#define NETLINK_USER 31

struct sock *netlink_sock=NULL;

static void netlink_recv_msg(struct sk_buff *socket_buffer){

/* used struct
struct sk_buff {
union {unnamed_union} 		/anonymous 
__u16 inner_transport_header	/Inner transport layer header (encapsulation) 
__u16 inner_network_header	/Network layer header (encapsulation) 
__u16 inner_mac_header		/Link layer header (encapsulation) 
__be16 protocol			/Packet protocol from driver 
__u16 transport_header		/Transport layer header 
__u16 network_header		/Network layer header 
__u16 mac_header		/Link layer header 
sk_buff_data_t tail		/Tail pointer 
sk_buff_data_t end		/End pointer 
unsigned char * head		/Head of buffer 
unsigned char * data	odwolanie	/Data head pointer 
unsigned int truesize		/Buffer size 
atomic_t users			/User count - see {datagram,tcp}.c 
};  

struct nlmsghdr {
 __u32 nlmsg_len;    / Length of message including header
 __u16 nlmsg_type;   / Type of message content
 __u16 nlmsg_flags;  / Additional flags
 __u32 nlmsg_seq;    / Sequence number
 __u32 nlmsg_pid; zastosowano   / Sender port ID
};
*/

	struct nlmsghdr *netlink_msg_hdr;
	int pid;
	struct sk_buff* socket_buffer_out;
	int msg_size;
	char *msg="netlink message";
	int res;

	printk("Entering: %s\n", __FUNCTION__);

	msg_size=strlen(msg);

	netlink_msg_hdr=(struct nlmsghdr*)(socket_buffer->data);

//void *nlmsg_data(struct nlmsghdr *nlh); -Return a pointer to the payload associated with the passed nlmsghdr. 
	printk(KERN_INFO "Netlink received msg payload:%s\n",(char*)nlmsg_data(netlink_msg_hdr));

	pid = netlink_msg_hdr->nlmsg_pid; //pid of sending process

/*
nlmsg_new() - Allocate a new netlink message
 * @payload: size of the message payload
 * @flags: the type of memory to allocate.
static inline struct sk_buff *nlmsg_new(size_t payload, gfp_t flags);
*/
	socket_buffer_out = nlmsg_new(msg_size,0);

	if(!socket_buffer_out){
	    printk(KERN_ERR "Failed to allocate new skb\n");
	    return;
	}
/*
nlmsg_put() - add a netlink message to an skb
 * @skb: socket buffer to store message in
 * @portid: netlink PORTID of requesting application
 * @seq: sequence number of message
 * @type: message type
 * @payload: length of message payload
 * @flags: message flags
static inline struct nlmsghdr *nlmsg_put(struct sk_buff *skb, u32 portid, u32 seq, int type, int payload, int flags);
*/
	netlink_msg_hdr=nlmsg_put(socket_buffer_out,0,0,NLMSG_DONE,msg_size,0);
  
//#define 	NETLINK_CB(skb)   (*(struct netlink_skb_parms*)&((skb)->cb))
	NETLINK_CB(socket_buffer_out).dst_group = 0; /* not in mcast group */

/*
nlmsg_data() - head of message payload
 * @nlh: netlink message header
static inline void *nlmsg_data(const struct nlmsghdr *nlh);
*/
	strncpy(nlmsg_data(netlink_msg_hdr),msg,msg_size);

/*
 * nlmsg_unicast - unicast a netlink message
 * @sk: netlink socket to spread message to
 * @skb: netlink message as socket buffer
 * @portid: netlink portid of the destination socket
static inline int nlmsg_unicast(struct sock *sk, struct sk_buff *skb, u32 portid);
 */
	res=nlmsg_unicast(netlink_sock,socket_buffer_out,pid);

	if(res<0){
	    printk(KERN_INFO "Error while sending bak to user\n");
	}
}

static int __init netlink_init(void) {

	printk("Entering: %s\n",__FUNCTION__);
	//This is for 3.6 kernels and above.
	struct netlink_kernel_cfg cfg = {
    		.input = netlink_recv_msg,
	};

	netlink_sock = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
//netlink_sock = netlink_kernel_create(&init_net, NETLINK_USER, 0, netlink_recv_msg,NULL,THIS_MODULE);
	if(!netlink_sock){
		printk(KERN_ALERT "Error creating netlink socket.\n");
    		return -10;
	}

	return 0;
}

static void __exit netlink_exit(void) {

	printk(KERN_INFO "Exiting netlink module\n");
	netlink_kernel_release(netlink_sock);
}

module_init(netlink_init); 
module_exit(netlink_exit);

MODULE_LICENSE("GPL");
