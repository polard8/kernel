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




//#define ETHERTYPE_IPv4 0x0800
//#define ETHERTYPE_IPv6 0x86DD

 
/* 
typedef struct ip_string_d ip_string_t; 
struct ip_string_d
{
    char String[4 * 4];
};	
ip_string_t *ipString;
*/ 

typedef struct ip_address_d ip_address_t; 
struct ip_address_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//netid + hostid.
    unsigned long ip_address;
	//unsigned long ip_mask;
	
	int version;    //IPv4, IPv6.
	
	//Armazena os valores dos quatro bytes em decimal na forma de string com pontos.
	//char string[4*4]; 
};
ip_address_t *ip_address;
//...

//User Datagram Protocol (UDP)
typedef struct udp_header_d udp_header_t; 
struct udp_header_d 
{
    unsigned short SourcePort;
	unsigned short DestinationPort;
    unsigned short Length;
	unsigned short Checksum;	
};

//IPv4 Header Format
typedef struct ipv4_header_d ipv4_header_t; 
struct ipv4_header_d 
{
	//
	// * 32bits block **************
	//
	
	//Version	       //0-3    4bits
	//IHL	           //4-7    4bits  Internet Header Length
	unsigned char Version_IHL;
	
	//DSCP	           //8-13   6bits  Differentiated Services Code Point 
	//ECN	           //14-15  2bits  Explicit Congestion Notification
	unsigned char DSCP_ECN; 
	
	//defines the entire packet size in bytes, including header and data.
	//The minimum size is 20 bytes (header without data) and the maximum is 65,535 bytes. 
	unsigned short TotalLength;   //16-31  16bits
	
	//
	// * 32bits block *********************
	//
	
	unsigned short Identification; //0-15  16bits	
	
	//flags
	//bit 0: Reserved; must be zero.
    //bit 1: Don't Fragment (DF)
    //bit 2: More Fragments (MF)
	
	//If the DF flag is set, and fragmentation is required to route the packet, then the packet is dropped.
	
	//Flags	                      //16-18   2bits
	//Fragment Offset             //19-31   14bits
	unsigned short Flags_FragmentOffset;
	
	//
	// * 32bits block *******************
	//
	
	//ttl. helps prevent datagrams from persisting (e.g. going in circles).
	//protocol. This field defines the protocol used in the data portion of the IP datagram.
	//error-checking of the header.
	
	unsigned char TimeToLive;	   //0-7   8bits (TTL)
	unsigned char Protocol;	       //8-15  8bits
	unsigned short HeaderChecksum; //16-31 16bits
	
	//
	// * 32bits block ******************
	//
	
	//This field is the IPv4 address of the sender of the packet.
	unsigned long SourceIPAddress; //0-31 32bits
	
	//
	// * 32bits block ************
	//
	
	//This field is the IPv4 address of the receiver of the packet.
	unsigned long DestinationIPAddress; //0-31 32bits
	
	//Options
};

// We need adapter info: like: name, description
//so não sei se informações sobre o adaptador deveria ficar nesse arquivos.


//
// End.
//

