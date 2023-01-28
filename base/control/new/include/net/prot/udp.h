
// udp.h
// User Datagram Protocol

#ifndef __NET_UDP_H
#define __NET_UDP_H    1

// UDP datagram structure
// 4*2 = 6bytes.
struct udp_d
{

// Source port number
    uint16_t uh_sport;

// Destination port number
    uint16_t uh_dport;

// Length
// This field specifies the length in bytes of the UDP header and UDP data. 
    uint16_t uh_ulen;

// Checksum
// #remember:
// When UDP runs over IPv4, 
// the checksum is computed using a "pseudo header" 
// that contains some of the same information from the real IPv4 header.
    uint16_t uh_sum;
};

void 
network_handle_udp( 
    const unsigned char *buffer, 
    ssize_t size );

#endif   


