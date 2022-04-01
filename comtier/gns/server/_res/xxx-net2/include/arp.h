
// ARP header length
#define ARP_HEADER_LENGHT 28      


// arp struct
struct  ether_arp {
	
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





