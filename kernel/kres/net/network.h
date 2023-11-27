
// network.h

#ifndef __NET_NETWORK_H
#define __NET_NETWORK_H    1


#define ONLINE  TRUE
#define OFFLINE FALSE

// 8192
#define NETWORK_DEFAULT_BUFFER_SIZE  \
    E1000_DEFAULT_BUFFER_SIZE


// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 

// packet format
// Ethernet IPv4 TCP/UDP DATA FCS



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
    unsigned long buffers[32];
// O status de cada buffer, se ele está vazio ou não.
    int is_full[32];
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

// Gateway support.
    uint8_t gateway_ipv4[4];
    uint8_t gateway_mac[6];
    int gateway_initialized;

// Stats
// For all the NICs?
    unsigned long tx_counter;
    unsigned long rx_counter;

// The domain controller.
    //struct domain_d *domain_controller;

    struct network_info_d *next;
};
extern struct network_info_d *CurrentNetwork;

// Essa flag poderia ir para dentro da estrutura acima,
extern int ____network_late_flag;


//
// == Prototypes ====================
//


int 
network_register_ring3_display_server(
    struct zing_hook_d *zh,
    pid_t caller_pid );



void 
network_fill_mac(
    unsigned char *to, 
    unsigned char *from );
void 
network_fill_ipv4(
    unsigned char *to,
    unsigned char *from );
void 
network_fill_ipv6(
    unsigned char *to,
    unsigned char *from );


unsigned short 
net_checksum(
    const unsigned char *phdr, 
    int phdr_len, 
    const unsigned char *start, 
    const unsigned char *end);

void network_test_NIC(void);

void 
network_send_raw_packet (
    struct intel_nic_info_d *dev, 
    size_t frame_len, 
    const char *frame_address );


// Handle package.
int 
network_on_receiving ( 
    const unsigned char *frame, 
    ssize_t frame_size );


int 
network_on_sending ( 
    const unsigned char *frame, 
    ssize_t frame_size );



// Push and Pop data.
int network_push_packet( void *src_buffer, int len );
int network_pop_packet( void *u_buffer, int len );

void networkSetStatus(int status);
int networkGetStatus(void);

void networkSetOnlineStatus(int status);
int networkGetOnlineStatus(void);

void networkUpdateCounter(int the_counter);

// #fixme
int networkInit(void);

#endif    

