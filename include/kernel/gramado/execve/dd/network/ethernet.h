

// ethernet header
struct ether_header {
	
	uint8_t dst[6];
	uint8_t src[6];
	uint16_t type;
	
} __attribute__((packed)); 



