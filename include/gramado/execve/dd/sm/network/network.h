

//network.h  //header para o gerenciamento de rede.

// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 

//packet format
// Ethernet IPv4 TCP/UDP DATA FCS



 
//estrutura de rede
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
	
	//ip do gateway
	//struct ip_address_d *networkGatewayIP;
	
	//adaptador de rede.
	//struct nic_info_d *nic;
	
	//user ??
	//struct user_info_d *networkUserinfo;
	
	//..
	
	struct network_info_d *next;
};


int networkInit();

//
//fim
//

