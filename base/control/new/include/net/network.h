
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
    int initialized;
// Receive
    int receive_tail;
    int receive_head;
    unsigned long receive_buffer[32];
// O status de cada buffer, se ele está vazio ou não.
    int receive_status[32];
// Send
    int send_tail;
    int send_head;
    unsigned long send_buffer[8];
// O status de cada buffer, se ele está vazio ou não.
    int send_status[8];
};

// See: network.c
extern struct network_buffer_d  NETWORK_BUFFER;


/*
 * network_info_d:
 *     Estrutura de rede.
 */ 

struct network_info_d
{
    int used;
    int magic;

// Número identificador da rede.
    int id;

    int initialized;

// Strings

// Nome da rede.
    char *name_string;
    size_t name_string_size;
// String mostrando a versão. ex: (1.1.1234)
    char *version_string;
    size_t version_string_size;

// Values
    unsigned short version_major;
    unsigned short version_minor; 
    unsigned short version_revision;

//adaptador de rede.
    //struct intel_nic_info_d *nic_info;

    // struct user_info_d *user_info;
    struct host_info_d *host_info;
    //..

    struct network_info_d *next;
};
extern struct network_info_d *CurrentNetwork;

// Essa flag poderia ir para dentro da estrutura acima,
extern int ____network_late_flag;


//
// == Prototypes ====================
//
void 
network_send_arp( 
    int op,   //operation
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6] );


void network_send_arp_reply(void);
void network_send_arp_request(void);
void testNIC(void);

// Handle package.
void 
network_on_receiving ( 
    const unsigned char *buffer, 
    ssize_t size );

void 
network_handle_ipv4( 
    const unsigned char *buffer, 
    ssize_t size );

void 
network_handle_arp( 
    const unsigned char *buffer, 
    ssize_t size );


int network_buffer_in( void *buffer, int len );
int network_buffer_out( void *buffer, int len );
void networkSetstatus(int status);
int networkGetStatus(void);
// #fixme
int networkInit (void);

#endif    

