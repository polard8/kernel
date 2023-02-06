
// dhcp.h
// see:
// https://pt.m.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol

/*
discovery (descoberta)
offer (oferta)
request (pedido)
acknowledge (confirmação)
*/

#ifndef __DHCP_H
#define __DHCP_H    1


struct dhcp_info_d
{
// We have the info given to us by the server.
    int initialized;
    unsigned int host_ip;
    //...
};
// see: dhcp.c
extern struct dhcp_info_d dhcp_info;


// Message Types

#define DHCP_DISCOVER                   1
#define DHCP_OFFER                      2
#define DHCP_REQUEST                    3
#define DHCP_DECLINE                    4
#define DHCP_ACK                        5
#define DHCP_NAK                        6
#define DHCP_RELEASE                    7
#define DHCP_INFORM                     8

#define OPT_PAD                         0
#define OPT_SUBNET_MASK                 1
#define OPT_ROUTER                      3
#define OPT_DNS                         6
#define OPT_REQUESTED_IP_ADDR           50
#define OPT_LEASE_TIME                  51
#define OPT_DHCP_MESSAGE_TYPE           53
#define OPT_SERVER_ID                   54
#define OPT_PARAMETER_REQUEST           55
#define OPT_END                         255

/*
typedef struct __dhcp_header{
    unsigned char   op;
    unsigned char   htype;
    unsigned char   hlen;
    unsigned char   hops;
    unsigned int    xid;
    unsigned short  secs;   //timing
    unsigned short  flags; 
    unsigned int    ciaddr; // Client IP Address
    unsigned int    yiaddr; // Your IP Address
    unsigned int    siaddr; // Server IP Address
    unsigned int    giaddr; // Gateway IP Address switched by relay
    unsigned char   chaddr[16]; // Client Hardware Address
    unsigned char   sname [64];
    unsigned char   file [128];
    unsigned int    magic_cookie;
    unsigned char   options[312 - 4];
} __attribute__ ((packed)) dhcp_header_t;
*/

// dhcp header
struct dhcp_d
{
    unsigned char   op;
    unsigned char   htype;
    unsigned char   hlen;
    unsigned char   hops;
    unsigned int    xid;
    unsigned short  secs;   //timing
    unsigned short  flags; 
    unsigned int    ciaddr; // Client IP Address
    unsigned int    yiaddr; // Your IP Address
    unsigned int    siaddr; // Server IP Address
    unsigned int    giaddr; // Gateway IP Address switched by relay
    unsigned char   chaddr[16]; // Client Hardware Address
    unsigned char   sname [64];
    unsigned char   file [128];
    unsigned int    magic_cookie;
    unsigned char   options[312 - 4];
} __attribute__ ((packed));


void 
network_dhcp_send(
    struct dhcp_d *dhcp,
    int message_type, 
    unsigned short sport, 
    unsigned short dport );
int network_initialize_dhcp(void);

#endif    


