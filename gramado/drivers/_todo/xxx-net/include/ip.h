/*
 * File: ip.h
 *
 * Descrição:
 *    IP protocol info.
 *
 *
 * Versão 1.0, 2016.
 */

 
 
/*
    Pilha de protocolos TCP/IP:
    ==========================

Camada de aplicação
BGP DHCP DNS FTP HTTP IMAP LDAP MGCP NNTP NTP 
POP ONC/RPC RTP RTSP RIP SIP SMTP SNMP SSH Telnet TLS/SSL XMPP outros...

Camada de transporte
TCP UDP DCCP SCTP RSVP outros...

Camada de interconexão
IP IPv4 IPv6 ICMP ICMPv6 ECN IGMP IPsec outros...

Camada de enlace
ARP NDP OSPF túneis... L2TP PPP MAC Ethernet DSL RDIS FDDI outros...

*/ 


/*
 Lightweight TCP/IP - um conjunto de códigos abertos projetado para sistemas embarcados.
 KA9Q NOS, a pilha e um conjunto de protocolos associados para sistemas de radio amador e 
 computadores pessoais conectados através de linhas seriais.
*/ 



// IPv4 header length
#define IPV4_HEADER_LENGHT 20    

#define UDP_HEADER_LENGHT 8    

//#define ETHERTYPE_IPv4 0x0800
//#define ETHERTYPE_IPv6 0x86DD


//
//  ## UDP  ##
//

//User Datagram Protocol (UDP)
typedef struct udp_header_d udp_header_t; 
struct udp_header_d 
{
    unsigned short SourcePort;
	unsigned short DestinationPort;
    unsigned short Length;
	unsigned short Checksum;	
};


//
//  ## IPV4 ##
//


//IPv4 Header Format
typedef struct ipv4_header_d ipv4_header_t; 
struct ipv4_header_d 
{	
	//Version	       //0-3    4bits
	//IHL	           //4-7    4bits  Internet Header Length
	/* Header version and length (dwords). */
	unsigned char Version_IHL;
	
	//DSCP	           //8-13   6bits  Differentiated Services Code Point 
	//ECN	           //14-15  2bits  Explicit Congestion Notification
	/* Service type. */
	//Type of Service.
	unsigned char DSCP_ECN; 
	
	//defines the entire packet size in bytes, including header and data.
	//The minimum size is 20 bytes (header without data) and the maximum is 65,535 bytes. 
	 /* Length of datagram (bytes). */
	//	IP packet length (both data and header). 
	unsigned short TotalLength;   //16-31  16bits
		
	//0-15  16bits	
	 /* Unique packet identification. */
	unsigned short Identification; 
	
	//flags
	//bit 0: Reserved; must be zero.
    //bit 1: Don't Fragment (DF)
    //bit 2: More Fragments (MF)
	
	//If the DF flag is set, and fragmentation is required to route the packet, 
	//then the packet is dropped.
	
	//Flags	                      //16-18   2bits
	//Fragment Offset             //19-31   14bits
	/* Flags; Fragment offset. */
	unsigned short Flags_FragmentOffset;
	
	//ttl. helps prevent datagrams from persisting (e.g. going in circles).
	//protocol. This field defines the protocol used in the data portion of the IP datagram.
	//error-checking of the header.
	/* Packet time to live (in network). */
	unsigned char TimeToLive;	   //0-7   8bits (TTL)
	
	 /* Upper level protocol (UDP, TCP). */
	unsigned char Protocol;	       //8-15  8bits
	
	/* IP header checksum. */
	unsigned short HeaderChecksum; //16-31 16bits
	
	
	//This field is the IPv4 address of the sender of the packet.
	//unsigned long SourceIPAddress; //0-31 32bits
	
	//This field is the IPv4 address of the receiver of the packet.
	//unsigned long DestinationIPAddress; //0-31 32bits
	
	uint8_t SourceIPAddress[4];
	uint8_t DestinationIPAddress[4];	
	
	//Options
};



//
//  ## IPV6 ##
//


//fixed header for ipv6.
/** IPv6 header */

struct ipv6_header_d 
{
    // Version (4 bits), Traffic class (8 bits), Flow label (20 bits) 
    uint32_t ver_tc_label;
    
	// Payload length, including any extension headers 
    uint16_t len;
    
	// Next header type 
    uint8_t next_header;
    
	// Hop limit 
    uint8_t hop_limit;
    
	// Source address 
    //struct in6_addr_src;
    
	// Destination address
    //struct in6_addr_dest;
	
} __attribute__ (( packed ));



// We need adapter info: like: name, description
//so não sei se informações sobre o adaptador deveria ficar nesse arquivos.


//send ipv4
void send_ipv4_packet ( struct intel_nic_info_d *dev, uint32_t len, uint8_t *data );
				   
				   
//
// End.
//

