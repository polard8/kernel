
// network.h

#ifndef ____NETWORK_H
#define ____NETWORK_H    1

// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 

// packet format
// Ethernet IPv4 TCP/UDP DATA FCS

// See: 
// https://en.wikipedia.org/wiki/EtherType
#define ETH_TYPE_IP    0x0800  
#define ETH_TYPE_IPV4  0x0800  
#define ETH_TYPE_ARP   0x0806
#define ETH_TYPE_IPV6  0x86DD
// ...


// little endian ?

#define ToNetByteOrder16(v)  ((v >> 8) | (v << 8))
#define ToNetByteOrder32(v)  (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))

#define FromNetByteOrder16(v) ((v >> 8) | (v << 8))
#define FromNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))


/*
// Device
// #test
struct network_device_d 
{
    int id;
	
	void *priv; //??

	char *dev_name;

    unsigned char ipv4_address[4];
    unsigned char mac_address[6];

	//virtual
	//Nope!
	//Void (*send)(PVoid, UIntPtr, PUInt8);
};
*/

struct network_buffer_d
{
    int receive_tail;
    int receive_head;
    unsigned long receive_buffer[32];

    // #test
    // O status de cada buffer, se ele está vazio ou não.
    int receive_status[32];

    int send_tail;
    int send_head;
    unsigned long send_buffer[8];

    // #test
    // O status de cada buffer, se ele está vazio ou não.
    int send_status[8];

    int initialized;
};

struct network_buffer_d  NETWORK_BUFFER;


/*
 * network_info_d:
 *     Estrutura de rede.
 */ 

struct network_info_d
{
    int used;
    int magic;
    int id;

    int networkIdentifier;  // Número identificador da rede.
    char *networkName;      // Nome da rede.
    char *networkVersion;   // String mostrando a versão. ex: (1.1.1234)
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
//struct network_info_d *Network;

// Essa flag poderia ir para dentro da estrutura acima,
int ____network_late_flag;


//
// == Prototypes ====================
//


int network_buffer_in( void *buffer, int len );
int network_buffer_out ( void *buffer, int len );
void networkSetstatus (int status);
int networkGetStatus (void);

// #fixme
int networkInit (void);



#endif  





















