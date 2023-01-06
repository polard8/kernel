
// arp.h

#ifndef ____ARP_H
#define ____ARP_H    1

// See: 
// https://en.wikipedia.org/wiki/Address_Resolution_Protocol

// Operation codes.
#define ARP_OPC_REQUEST  0x0001
#define ARP_OPC_REPLY    0x0002

// ARP header length
#define ARP_HEADER_LENGHT  28

// arp struct
struct ether_arp 
{

//====================
//Header

    uint16_t  type;   // Hardware type (HTYPE)
    uint16_t  proto;  // Protocol type (PTYPE)
    uint8_t   hlen;   // Hardware address length 
    uint8_t   plen;   // Protocol address length 
    uint16_t  op;     // Operation (OPER)

//====================
//Addresses

// src mac
    uint8_t arp_sha[ETH_ALEN];  // Sender Hardware Address, mac 
// src ip
    uint8_t arp_spa[4];         // Sender Protocol Address, ip 
// dst mac
    uint8_t arp_tha[ETH_ALEN];  // Target Hardware Address, mac
// dst ip
    uint8_t arp_tpa[4];         // Target Protocol Address, ip

} __attribute__((packed)); 


#endif    


