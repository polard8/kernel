
// udp.h
// User Datagram Protocol

#ifndef __NET_UDP_H
#define __NET_UDP_H    1

#define UDP_HEADER_LENGHT  8

// UDP datagram structure
// 4*2 = 8 bytes.
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


int
network_send_udp ( 
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6], 
    unsigned short source_port,
    unsigned short target_port,
    char *data_buffer,
    size_t data_lenght );

void network_save_mac( uint8_t mac[6] );
void 
network_test_udp0(
    uint8_t tmac[6], 
    uint8_t tip[4],
    unsigned short sport,
    unsigned short dport );
void network_test_udp(void);
void network_test_udp2(void);

#endif   


