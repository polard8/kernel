

#define ETH_TYPE_IP   0x0800  
#define ETH_TYPE_ARP  0x0806
 
#define ARP_OPC_REQUEST  0x01
#define ARP_OPC_REPLY    0x02


//little endian
#define ToNetByteOrder16(v) ((v >> 8) | (v << 8))
#define ToNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))
#define FromNetByteOrder16(v) ((v >> 8) | (v << 8))
#define FromNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))




// Ethernet header length
#define ETHERNET_HEADER_LENGHT 14      

// ethernet header
struct gdeshell_ether_header {
	
	uint8_t dst[6];
	uint8_t src[6];
	uint16_t type;
	
} __attribute__((packed)); 


// ARP header length
#define ARP_HEADER_LENGHT 28      


// arp struct
struct  gdeshell_ether_arp {
	
    uint16_t type;  //Hardware type (HTYPE)
	uint16_t proto; //Protocol type (PTYPE)
	uint8_t hlen;   //Hardware address length 
	uint8_t plen;   //Protocol address length 
	uint16_t op;    //Operation (OPER)

   //#define ETH_ALEN 6 
	
	uint8_t arp_sha[6];    /* sender hardware address mac */
    uint8_t arp_spa[4];    /* sender protocol address ip */
	
    uint8_t arp_tha[6];    /* target hardware address mac*/
    uint8_t arp_tpa[4];    /* target protocol address ip*/
	
} __attribute__((packed)); 




void 
__SendARP ( uint8_t source_ip[4], 
          uint8_t target_ip[4], 
          uint8_t target_mac[6] );

void __shellTestARP (void);




