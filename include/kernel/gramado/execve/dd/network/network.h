/*
 * File: network.h 
 *     header para o gerenciamento de rede.
 */


// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 


//packet format
// Ethernet IPv4 TCP/UDP DATA FCS



#define ETH_TYPE_IP   0x0800  
#define ETH_TYPE_ARP  0x0806
 
#define ARP_OPC_REQUEST  0x01
#define ARP_OPC_REPLY    0x02


//little endian
#define ToNetByteOrder16(v) ((v >> 8) | (v << 8))
#define ToNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))
#define FromNetByteOrder16(v) ((v >> 8) | (v << 8))
#define FromNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))


/*
 * network_info_d:
 *     Estrutura de rede.
 */ 

typedef struct network_info_d network_info_t;
struct network_info_d
{
    int id;
	
	int used;
	int magic;
	
	int networkIdentifier;  // Número identificador da rede.
	char *networkName;      // Nome da rede.
    char *networkVersion;   // string mostrando a versão. ex: (1.1.1234)
	unsigned short networkVersionMajor;
	unsigned short networkVersionMinor; 
	unsigned short networkVersionRevision;	
	
	//adaptador de rede.
	//struct intel_nic_info_d *nic;
	
	//user ??
	//struct user_info_d *networkUserinfo;
	
	//..
	
	struct network_info_d *next;
};



int networkInit();


void networkSetstatus (int status);
int networkGetStatus ();
void show_network_info ();


void show_current_nic_info ();


//manipular o pacote ipv6 recebido pelo handle do e1000.
int handle_ipv6 ( struct intel_nic_info_d *nic, struct ipv6_header_d *header );

void SendIPV4 ( uint8_t source_ip[4], uint8_t target_ip[4], uint8_t target_mac[6], uint8_t data[32] );
void SendARP ( uint8_t source_ip[4], uint8_t target_ip[4], uint8_t target_mac[6] );

void testNIC();


//
// End.
//

