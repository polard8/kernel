
// tcp.h 

#ifndef __NET_TCP_H
#define __NET_TCP_H    1

// Control flags:
#define TCP_ACK  16
#define TCP_PSH  8
#define TCP_RST  4
#define TCP_SYN  2
#define TCP_FIN  1

//#define	TH_FIN    0x01		/* Final: Set on the last segment */
//#define	TH_SYN    0x02		/* Synchronization: New conn with dst port */
//#define	TH_RST    0x04		/* Reset: Announce to peer conn terminated */
//#define	TH_PUSH   0x08		/* Push: Immediately send, don't buffer seg */
//#define	TH_ACK    0x10		/* Acknowledge: Part of connection establish */
//#define	TH_URG    0x20		/* Urgent: send special marked segment now */
//#define	TH_ECE    0x40		/* ECN Echo */
//#define	TH_CWR    0x80		/* Congestion Window Reduced */


// When sending
// without a payload:  
// with a payload: 

// size:
// By default, the max limit of a TCP packet is 64K or 65535 bytes.
// 1GB if you use window scaling (by left shifting the window size by 14).
// The maximum size of a TCP packet is 64K (65535 bytes). 
// Generally, the packet size gets restricted by the 
// Maximum Transmission Unit (MTU) of network resources.
// The MTU (Maximum Transmission Unit) for Ethernet, 
// for instance, is 1500 bytes. 

typedef uint32_t  tcp_seq;
typedef uint32_t  tcp_ack;

#define TCP_HEADER_LENGHT  20

struct tcp_d
{

// Ports:
// 16,16
    uint16_t th_sport;  // source port
    uint16_t th_dport;  // destination port

// 32,32
    tcp_seq th_seq;    /* sequence number */
    tcp_ack th_ack;    /* acknowledgement number */

// 4,6,6
// data offset (4) | reserved (6) | control_flags (6)
    uint16_t do_res_flags;

// 16
    uint16_t window_size;

// 16
    uint16_t checksum;

// 16
    uint16_t urgent_pointer;
// -------------
// Optional data: 0~40 bytes
};

// =====================================


void 
network_handle_tcp( 
    const unsigned char *buffer, 
    ssize_t size );

#endif    


