/*
 * File: sys/socket.h
 * 
 */

// Core socket functions and data structures.
// See:
// https://en.wikipedia.org/wiki/Berkeley_sockets

#ifndef _SOCKET_H
#define _SOCKET_H


#include <stddef.h>
#include <netinet/in.h>  


/* 
 *  ** Sock types  ** 
 */
 
/*
       SOCK_STREAM     Provides sequenced, reliable, two-way, connection-
                       based byte streams.  An out-of-band data transmission
                       mechanism may be supported.

       SOCK_DGRAM      Supports datagrams (connectionless, unreliable
                       messages of a fixed maximum length).

       SOCK_SEQPACKET  Provides a sequenced, reliable, two-way connection-
                       based data transmission path for datagrams of fixed
                       maximum length; a consumer is required to read an
                       entire packet with each input system call.

       SOCK_RAW        Provides raw network protocol access.

       SOCK_RDM        Provides a reliable datagram layer that does not
                       guarantee ordering.

       SOCK_PACKET     Obsolete and should not be used in new programs;
*/

#define SOCK_STREAM       1     /* stream (connection) socket	*/
#define SOCK_DGRAM        2     /* datagram (conn.less) socket	*/
#define SOCK_RAW          3     /* raw socket			        */
#define SOCK_RDM          4     /* reliably-delivered message	*/
#define SOCK_SEQPACKET    5     /* sequential packet socket	*/ /* sequenced packet stream */
#define SOCK_DCCP       6
// ...
#define SOCK_PACKET       10    /* linux specified 		    */
#define SOCK_GRAMADO_MSG  8000  /* window, msg, long1, long2 */
#define SOCK_MAX            (SOCK_GRAMADO_MSG+1)


//=========
/* Supported address families. */

#define AF_UNSPEC     0
#define AF_UNIX       1     /* Unix domain sockets 		*/
#define AF_LOCAL      1     /* POSIX name for AF_UNIX	*/
#define AF_INET       2     /* Internet IP Protocol 	*/
#define AF_AX25       3     /* Amateur Radio AX.25 		*/
#define AF_IPX        4     /* Novell IPX 			*/
#define AF_APPLETALK  5     /* AppleTalk DDP 		*/
#define AF_NETROM     6     /* Amateur Radio NET/ROM 	*/
#define AF_BRIDGE     7     /* Multiprotocol bridge 	*/
#define AF_ATMPVC     8     /* ATM PVCs			*/
#define AF_X25        9     /* Reserved for X.25 project 	*/
#define AF_INET6      10    /* IP version 6			*/
#define AF_ROSE       11    /* Amateur Radio X.25 PLP	*/
#define AF_DECnet     12    /* Reserved for DECnet project	*/
#define AF_NETBEUI    13    /* Reserved for 802.2LLC project*/
#define AF_SECURITY   14    /* Security callback pseudo AF */
#define AF_KEY        15    /* PF_KEY key management API */
#define AF_NETLINK    16
#define AF_ROUTE      AF_NETLINK    /* Alias to emulate 4.4BSD */
#define AF_PACKET     17            /* Packet family		*/
#define AF_ASH        18            /* Ash				*/
#define AF_ECONET     19            /* Acorn Econet			*/
#define AF_ATMSVC     20            /* ATM SVCs			*/
#define AF_SNA        22            /* Linux SNA Project (nutters!) */
#define AF_IRDA       23            /* IRDA sockets			*/
#define AF_PPPOX      24            /* PPPoX sockets		*/
#define AF_WANPIPE    25            /* Wanpipe API Sockets */
#define AF_LLC        26            /* Linux LLC			*/
#define AF_TIPC       30            /* TIPC sockets			*/
#define AF_BLUETOOTH  31            /* Bluetooth sockets 		*/
#define AF_IUCV       32            /* IUCV sockets			*/
#define AF_RXRPC      33            /* RxRPC sockets 		*/
#define AF_RS232      35            /* Serial socket (NEW!) */
#define AF_GRAMADO    8000
#define AF_MAX        AF_GRAMADO  //#todo

/*
 * Definitions for network related sysctl, CTL_NET.
 *
 * Second level is protocol family.
 * Third level is protocol number.
 *
 * Further levels are defined by the individual families below.
 */
#define NET_MAXID	AF_MAX


#define MAXHOSTNAMELEN	256


/* Protocol families, same as address families. */
#define PF_UNSPEC   AF_UNSPEC
#define PF_UNIX     AF_UNIX
#define PF_LOCAL    AF_LOCAL
#define PF_INET     AF_INET
#define PF_AX25     AF_AX25
#define PF_IPX      AF_IPX
#define PF_APPLETALK  AF_APPLETALK
#define	PF_NETROM   AF_NETROM
#define PF_BRIDGE   AF_BRIDGE
#define PF_ATMPVC   AF_ATMPVC
#define PF_X25      AF_X25
#define PF_INET6    AF_INET6
#define PF_ROSE     AF_ROSE
#define PF_DECnet   AF_DECnet
#define PF_NETBEUI  AF_NETBEUI
#define PF_SECURITY AF_SECURITY
#define PF_KEY      AF_KEY
#define PF_NETLINK  AF_NETLINK
#define PF_ROUTE    AF_ROUTE
#define PF_PACKET   AF_PACKET
#define PF_ASH      AF_ASH
#define PF_ECONET   AF_ECONET
#define PF_ATMSVC   AF_ATMSVC
#define PF_SNA      AF_SNA
#define PF_IRDA     AF_IRDA
#define PF_PPPOX    AF_PPPOX
#define PF_WANPIPE  AF_WANPIPE
#define PF_LLC      AF_LLC
#define PF_TIPC     AF_TIPC
#define PF_BLUETOOTH  AF_BLUETOOTH
#define PF_IUCV     AF_IUCV
#define PF_RXRPC    AF_RXRPC
#define PF_RS232    AF_RS232
#define PF_MAX      AF_MAX



/* Maximum queue length specifiable by listen().  */
//#define SOMAXCONN	128
#define SOMAXCONN    32



/* Flags we can use with send/ and recv. 
   Added those for 1003.1g not all are supported yet */
 
#define MSG_OOB        1
#define MSG_PEEK       2
#define MSG_DONTROUTE  4
#define MSG_TRYHARD    4     /* Synonym for MSG_DONTROUTE for DECnet */
#define MSG_CTRUNC     8
#define MSG_PROBE      0x10  /* Do not send. Only probe path f.e. for MTU */
#define MSG_TRUNC      0x20
#define MSG_DONTWAIT   0x40    /* Nonblocking io		 */
#define MSG_EOR        0x80    /* End of record */
#define MSG_WAITALL    0x100   /* Wait for a full request */
#define MSG_FIN        0x200
#define MSG_SYN        0x400
#define MSG_CONFIRM    0x800   /* Confirm path validity */
#define MSG_RST        0x1000
#define MSG_ERRQUEUE   0x2000  /* Fetch message from error queue */
#define MSG_NOSIGNAL   0x4000  /* Do not generate SIGPIPE */
#define MSG_MORE       0x8000  /* Sender will send more */
#define MSG_EOF        MSG_FIN

#if defined(CONFIG_COMPAT)
#define MSG_CMSG_COMPAT  0x80000000  /* This message needs 32 bit fixups */
#else
#define MSG_CMSG_COMPAT  0           /* We never have 32 bit fixups */
#endif



/* Setsockoptions(2) level. Thanks to BSD these must match IPPROTO_xxx */
#define SOL_IP		0
/* #define SOL_ICMP	1	No-no-no! Due to Linux :-) we cannot use SOL_ICMP=1 */
#define SOL_TCP		6
#define SOL_UDP		17
#define SOL_IPV6	41
#define SOL_ICMPV6	58
#define SOL_SCTP	132
#define SOL_UDPLITE	136     /* UDP-Lite (RFC 3828) */
#define SOL_RAW		255
#define SOL_IPX		256
#define SOL_AX25	257
#define SOL_ATALK	258
#define SOL_NETROM	259
#define SOL_ROSE	260
#define SOL_DECNET	261
#define	SOL_X25		262
#define SOL_PACKET	263
#define SOL_ATM		264	/* ATM layer (cell level) */
#define SOL_AAL		265	/* ATM Adaption Layer (packet level) */
#define SOL_IRDA        266
#define SOL_NETBEUI	267
#define SOL_LLC		268
#define SOL_DCCP	269
#define SOL_NETLINK	270
#define SOL_TIPC	271
#define SOL_RXRPC	272

/* IPX options */
#define IPX_TYPE	1


/*
 * Socket creation flags
 */
//#if __BSD_VISIBLE
//#define	SOCK_CLOEXEC		0x8000	/* set FD_CLOEXEC */
//#define	SOCK_NONBLOCK		0x4000	/* set O_NONBLOCK */
//#ifdef _KERNEL
//#define	SOCK_NONBLOCK_INHERIT	0x2000	/* inherit O_NONBLOCK from listener */
//#endif
//#define	SOCK_DNS		0x1000	/* set SS_DNS */
//#endif /* __BSD_VISIBLE */


/*
 * Option flags per-socket.
 */
// credits: openbsd
#define	SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	SO_ACCEPTCONN	0x0002		/* socket has had listen() */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#define	SO_LINGER	0x0080		/* linger on close if data present */
// #define SO_DONTLINGER	~SO_LINGER
#define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */
#define	SO_REUSEPORT	0x0200		/* allow local address & port reuse */
#define SO_TIMESTAMP	0x0800		/* timestamp received dgram traffic */
#define SO_BINDANY	0x1000		/* allow bind to any address */
#define SO_ZEROIZE	0x2000		/* zero out all mbufs sent over socket */

/*
 * Additional options, not kept in so_options.
 */
// credits: openbsd
#define	SO_SNDBUF	0x1001		/* send buffer size */
#define	SO_RCVBUF	0x1002		/* receive buffer size */
#define	SO_SNDLOWAT	0x1003		/* send low-water mark */
#define	SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define	SO_SNDTIMEO	0x1005		/* send timeout */
#define	SO_RCVTIMEO	0x1006		/* receive timeout */
#define	SO_ERROR	0x1007		/* get error status and clear */
#define	SO_TYPE		0x1008		/* get socket type */
#define	SO_NETPROC	0x1020		/* multiplex; network processing */
#define	SO_RTABLE	0x1021		/* routing table to be used */
#define	SO_PEERCRED	0x1022		/* get connect-time credentials */
#define	SO_SPLICE	0x1023		/* splice data to other socket */
#define	SO_DOMAIN	0x1024		/* get socket domain */
#define	SO_PROTOCOL	0x1025		/* get socket protocol */



// #bugbug: Moved to 'in.h'
// See:
// https://man7.org/linux/man-pages/man7/ip.7.html
// Any IP address.
//#define  INADDR_ANY        (unsigned long) 0x00000000  
// Broadcast IP address.
//#define  INADDR_BROADCAST  (unsigned long) 0xffffffff  



/* 
 * Read using getsockopt() with SOL_SOCKET, SO_PEERCRED 
 */

struct sockpeercred 
{
    uid_t  uid;    /* effective user id */
    gid_t  gid;    /* effective group id */
    pid_t  pid;
};


/*
//Address to loopback in software to local host.  
#define	INADDR_LOOPBACK		0x7f000001	 127.0.0.1  
#define	IN_LOOPBACK(a)		((((long int) (a)) & 0xff000000) == 0x7f000000)
*/


typedef unsigned socklen_t;


/* Device structure */

typedef struct socket_context {

    struct socket_context *next, *prev;

    unsigned fd;
    int family;
    int type;
    int protocol;

} socket_t;


// not bsd.
struct sockaddr 
{
    //unsigned char   sa_len;
    unsigned short  sa_family;
    char            sa_data[14];
};


/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 * bsd
 */
struct sockproto 
{
    unsigned short sp_family;    // address family 
    unsigned short sp_protocol;  // protocol 
};


typedef struct
{
    char     *h_addr;
    unsigned  h_length;

}hostent;



/*
struct ucred {
    pid_t pid;
    uid_t uid;
    gid_t gid;
};
*/


/* Scatter/gather array items */
struct iovec 
{
    void   *iov_base;  /* Starting address */
    size_t  iov_len;   /* Number of bytes to transfer */
};


struct msghdr 
{
    void         *msg_name;       /* optional address */
    socklen_t     msg_namelen;    /* size of address */
    struct iovec *msg_iov;        /* scatter/gather array */
    size_t        msg_iovlen;     /* # elements in msg_iov */
    void         *msg_control;    /* ancillary data, see below */
    size_t        msg_controllen; /* ancillary data buffer len */
    int           msg_flags;      /* flags on received message */
};



//
// == Prototypes =======
//


// socket
//socket -	create an endpoint for communication
//4.4BSD, POSIX.1-2001.
//The SOCK_NONBLOCK and SOCK_CLOEXEC flags	are Linux-specific.
//socket()	 appeared in 4.2BSD.  It is generally portable to/from non-BSD
//systems supporting clones of the	BSD socket layer (including  System  V
//variants).
// comments credits: freebsd.org	 
// See: http://man7.org/linux/man-pages/man2/socket.2.html
//POSIX.1-2001, POSIX.1-2008, 4.4BSD.

// #example:
// tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
// udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
// raw_socket = socket(AF_INET, SOCK_RAW, protocol);

//int socket ( int family, int type, int protocol );
int socket ( int domain, int type, int protocol );


//socketpair - create a pair of connected sockets
// On success, zero is returned.  
// On error, -1 is returned, errno is set
// appropriately, and sv is left unchanged
//POSIX.1-2001, POSIX.1-2008, 4.4BSD. 
int socketpair (int domain, int type, int protocol, int sv[2]);

int 
bind ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen );


// listen -	listen for connections on a socket
// 4.4BSD,	POSIX.1-2001.	
// The  listen()  function	call first appeared in 4.2BSD.
int listen (int sockfd, int backlog);


int accept4 (int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags);

// alternative way
// Created by Fred Nora.
int accept2 (int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// accept
// #todo: standard unix-like
int accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int 
connect ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen );


/*
 * shutdown: 
 *     Shut down part of a full-duplex connection.
 */

//POSIX.1-2001, 
//4.4BSD (the shutdown() function call  first  appeared  in 4.2BSD).
int shutdown ( int sockfd, int how );



//send
//4.4BSD, SVr4, POSIX.1-2001.  These function calls appeared in 4.2BSD.
//POSIX.1-2001   describes	  only	 the   MSG_OOB	 and   MSG_EOR	flags.
//POSIX.1-2008 adds a specification  of  MSG_NOSIGNAL.   The  MSG_CONFIRM
//flag is a Linux extension.
// comments credits: freebsd.org
ssize_t send ( int sockfd, const void *buf, size_t len, int flags );

ssize_t 
sendto ( 
    int sockfd, 
    const void *buf, 
    size_t len, 
    int flags,
    const struct sockaddr *dest_addr, 
    socklen_t addrlen );

ssize_t sendmsg (int sockfd, const struct msghdr *msg, int flags);



//recv - receive a message from a socket
ssize_t recv ( int sockfd, void *buf, size_t len, int flags );

ssize_t 
recvfrom ( 
    int sockfd, 
    void *buf, 
    size_t len, 
    int flags,
    struct sockaddr *src_addr, 
    socklen_t *addrlen );

ssize_t recvmsg (int sockfd, struct msghdr *msg, int flags);


int 
getsockname (
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen );

int 
getpeername ( 
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen );



int getsockopt (int sockfd, int level, int optname, void *optval, socklen_t *optlen); 
int setsockopt (int sockfd, int level, int optname, const void *optval, socklen_t optlen);
int sendfd(int sockfd, int fd);
int recvfd(int sockfd);


/*
struct hostent *gethostbyaddr(
    const void *addr,
    socklen_t len, int type);
struct hostent *gethostbyaddr(
    const void *addr,
    socklen_t len, int type)
{
    return (struct hostent *) 0;
}
*/



//
// =========
//


int inet_aton(const char *cp, struct in_addr *inp);
in_addr_t inet_addr(const char *cp);


in_addr_t inet_network(const char *cp);

char *inet_ntoa ( struct in_addr in );

struct in_addr
inet_makeaddr(in_addr_t net, in_addr_t host);


in_addr_t
inet_lnaof(struct in_addr in);

in_addr_t
inet_netof(struct in_addr in);


#endif  //socket.h


//
// End.
//









