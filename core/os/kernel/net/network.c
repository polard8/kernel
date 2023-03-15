
// network.c
// Network layer. (IP)
// Transport layer. (TCP/UDP/...)

#include <kernel.h>

// Status do driver de network
// 0 - uninitialized
// 1 - initialized
static int network_status=FALSE; 

// Are we online?
// Do we already have an valid IP?
static int __is_online = FALSE;

// Essa flag poderia ir para dentro da estrutura acima,
int ____network_late_flag=0;

// Status para notificações.
// Podemos ou não notificar os processo sobre os eventos de rede.
// O shell vai habilitar essa notificação no momento em que
// envia um stream para mensagens de texto.
int notification_status=FALSE;

// Usado por esse módulo.
file *____network_file;

// See: network.h
struct network_buffer_d  NETWORK_BUFFER;

struct host_info_d *HostInfo;
struct network_info_d *CurrentNetwork;

char *default_network_name_string = "default-network-name";
char *default_network_version_string = "0.0.0";

// Target MAC.
unsigned char __saved_gateway_mac[6];


// ====================================================

void 
network_fill_mac(
    unsigned char *to, 
    unsigned char *from )
{
    register long i=0;

    if ( (void*) to == NULL )
        return;
    if ( (void*) from == NULL )
        return;

    for (i=0; i<6; i++)
    {
        to[i] = from[i];
    };
}


void 
network_fill_ipv4(
    unsigned char *to,
    unsigned char *from )
{
    register long i=0;

    if ( (void*) to == NULL )
        return;
    if ( (void*) from == NULL )
        return;

    for (i=0; i < 4; i++)
    {
        to[i] = from[i];
    };
}

void 
network_fill_ipv6(
    unsigned char *to,
    unsigned char *from )
{
    register long i=0;

    if ( (void*) to == NULL )
        return;
    if ( (void*) from == NULL )
        return;

    for (i=0; i < 6; i++)
    {
        to[i] = from[i];
    };
}




// Credits: Sirius OS.
unsigned short 
net_checksum(
    const unsigned char *phdr, 
    int phdr_len, 
    const unsigned char *start, 
    const unsigned char *end)
{
    unsigned int checksum = 0;
    unsigned int len = phdr_len;
    unsigned short *p = (unsigned short *) phdr;

    if (!phdr) 
        goto no;

// acc
// Pseudo Head
    while (len > 1) {
        checksum += *p++;
        len -= 2;
    };

no:
    len = end - start;
    p = (unsigned short *) start;
    while (len > 1) {
        checksum += *p++;
        len -= 2;
    };

    if (len != 0) {
        checksum += *(unsigned char *) p;
    }

    checksum = (checksum & 0xffff) + (checksum >> 16);
    checksum += (checksum >> 16);

    unsigned short final = ~checksum;

    return ToNetByteOrder16(final);
}




// Test, called by the kernel console.
void testNIC(void)
{
    // #debug
    printf("testNIC:\n");
    refresh_screen();

    network_send_arp_request();
    //network_test_udp();

// ...

    e1000_show_info();

    // #debug
    printf("testNIC: done\n");
    refresh_screen();
}

// IN:
// + frame base address
// + frame total size
int 
network_on_receiving ( 
    const unsigned char *frame, 
    ssize_t frame_size )
{
// + Handle ethernet header.
// + Call the handler for the given protocol.

    struct ether_header *eth = (struct ether_header *) frame;
    uint16_t Type=0;

// Drop it!
    if (network_status != TRUE)
    {
        //#debug
        //printf("Packet: Network is OFF\n");
        return -1;
    }

    if ( (void*) frame == NULL ){
        //printf("network_on_receiving: frame\n");
        goto fail;
    }

    // 1~8192
    if ( frame_size <= 0 || 
          frame_size > E1000_DEFAULT_BUFFER_SIZE )
    {
        //printf("network_on_receiving: frame_size\n");
        goto fail;
    }

//
// Option
//

// Push packet.
// Maybe we can simply pash the packet into the circular queue.
// Mayme we can change this queue and use a lined list.
// Or create a queue support. We still don't have this.
// Coloca em um dos buffers, 
// de onde os aplicativos podem pegar depois.
// see: network.c

    // #todo
    // We need a configuration flag here.
    // Telling that we need to push the packets into the queue
    // instead of processing them.

    //network_buffer_in ( (void *) buffer, (int) size );
    //return;
    
    // #debug
    //printf("\n");
    //printf("Ethernet Header\n");

    if ( (void*) eth == NULL ){
        goto fail;
    }

// #debug
// Destination MAC
// Source MAC
// Protocol type.

/*
    printf ("   |-Destination Address : %x-%x-%x-%x-%x-%x \n", 
        eth->dst[0], eth->dst[1], eth->dst[2], 
        eth->dst[3], eth->dst[4], eth->dst[5] );

    printf ("   |-Source Address      : %x-%x-%x-%x-%x-%x \n", 
        eth->src[0], eth->src[1], eth->src[2], 
        eth->src[3], eth->src[4], eth->src[5] );

    printf ("   |-Ethertype           : %x \n",
        (unsigned short) eth->type);
*/

    int Show=FALSE;
    Type = (uint16_t) FromNetByteOrder16(eth->type);

    switch (Type){
    case ETHERTYPE_IPv4:
        Show=TRUE;
        network_handle_ipv4( 
            (frame + ETHERNET_HEADER_LENGHT), 
            (frame_size - ETHERNET_HEADER_LENGHT)  );
        break;
    case ETHERTYPE_ARP:
        Show=TRUE;
        network_handle_arp( 
            (frame + ETHERNET_HEADER_LENGHT), 
            (frame_size - ETHERNET_HEADER_LENGHT)  );
        break;
    // ...
    //case ETHERTYPE_IPv6:
    default:
        // printf ("Default type\n");
        goto fail;
        break;
    };

    //if (Show){
    //    refresh_screen();
    //}

    return 0;
fail:
    return -1;
}


int 
network_on_sending ( 
    const unsigned char *frame, 
    ssize_t frame_size )
{
    if (network_status != TRUE)
        return -1;

    return -1;
}


// network_push_packet:
// in: (Do buffer indicado para o buffer tail)
// Isso é usado pelo driver de dispositivo
// pra salvar o conteúdo que veio da rede em
// um buffer que pode ser lido pelos aplicativos.
int 
network_push_packet( 
    void *src_buffer, 
    int len )
{
// Push packet.

    printf ("--------------------- >>>> PUSH\n");

    int tail=0;
    void *dst_buffer;

// Check args
    if ( (void*) src_buffer == NULL ){
        panic ("network_push_packet: src_buffer\n");
    }

// #todo
// Veja na configuração do dispositivo, que o buffer 
// configurado para o hardware é de 0x3000 bytes.
    if (len>1500){
        debug_print("network_push_packet: [FIXME] len\n");
        len = 1500;
        //return -1;
    }

    if (NETWORK_BUFFER.initialized != TRUE){
        panic ("network_push_packet: Shared buffers not initialized\n");
    }

    tail = (int) NETWORK_BUFFER.receive_tail;

    //circula.
    NETWORK_BUFFER.receive_tail++;
    if (NETWORK_BUFFER.receive_tail >= 32){
        NETWORK_BUFFER.receive_tail=0;
    }

// #todo
// MTU: maximim transmition unit.
// For ethernet is 1500 bytes.
    //printf ("network_buffer_in: buffer_len %d\n",len);
    //refresh_screen();

// Fail
// Limits.
    if (tail < 0 || tail >= 32)
    {
        //#debug
        panic ("network_push_packet: tail\n");
        return -1;
    }

// Check buffer status.
// Se o buffer está cheio é porque ele não foi consumido.
// Vamos sobrepor?
    int buffer_status = NETWORK_BUFFER.is_full[tail];
    if (buffer_status == TRUE)
    {
        // #bugbug
        // #todo: Podemos criar um contador de vezes que isso acontece.
        // Isso acontece frequentemente.
        // panic ("network_buffer_in: [TEST] Not responding ...\n");
        // printf ("network_buffer_in: [FIXME] Can't write. This buffer is full.\n");
        // refresh_screen();
    }

// Get the destination buffer.
    dst_buffer = (void*) NETWORK_BUFFER.buffers[tail];
// Copy
    if ((void*)dst_buffer != NULL)
    {
        memcpy( 
            dst_buffer,   // Data coes to the list.
            src_buffer,   // Data comes from the device. 
            len );        // Lenght.
    } 

// Avisamos que esse buffer está cheio.
    NETWORK_BUFFER.is_full[tail] = TRUE;

    //printf("network_buffer_in: ok\n");
    //refresh_screen();
    //return 0;  //ok
    return (int) len;

fail:
    return (int) -1;
}


// network_pop_packet:
// out: (Do buffer head para o buffer indicado)
// Isso é usado pelos aplicativos
// para pegarem os conteúdos salvos nos buffers.
// Daí os aplicativos interpretam os protocolos.
int 
network_pop_packet ( 
    void *u_buffer,   // User buffer to get the data. 
    int len )         // Size.
{
// Pop packet.
// Circular queue. :)
// This is a service called only by the
// network server to get input from the
// queue filled by the NIC devices.
// It doesn't open any device to get data.

    //printf (" ---------- >>>> POP\n");

    int head=0;
    void *src_buffer;

    debug_print("network_pop_packet:\n");

// check args
    if ( (void*) u_buffer == NULL ){
        panic ("network_pop_packet: [FAIL] u_buffer\n");
    }

// #bugbug:
// Isso pode ser maior se considerarmos todos os headers.
// #todo
// Veja na configuração do dispositivo, que o buffer 
// configurado para o hardware é de 0x3000 bytes.
    if (len>1500){
        debug_print("network_pop_packet: [FIXME] len\n");
        len=1500;
        //return -1;
    }

    if (NETWORK_BUFFER.initialized != TRUE){
        panic ("network_pop_packet: Shared buffers not initialized\n");
    }

// Vamos pegar um numero de buffer para enviarmos o pacote.
// o kernel vai retirar do head ... 
// o que foi colocado pelo aplicativo em tail.
    head = (int) NETWORK_BUFFER.receive_head;

// circula.
    NETWORK_BUFFER.receive_head++;
    if (NETWORK_BUFFER.receive_head >= 32){
        NETWORK_BUFFER.receive_head=0;
    }

// #todo
// MTU: maximim transmition unit.
// For ethernet is 1500 bytes.
    //printf ("network_buffer_in: buffer_len %d\n",len);
    //refresh_screen();

    if (head<0 || head >= 32)
    {
        //#debug
        panic ("network_push_packet: head\n");
        return -1;
    }

// Is the buffer full?
    if ( NETWORK_BUFFER.is_full[head] != TRUE )
        return 0;

// Get the source buffer.
    src_buffer = (void*) NETWORK_BUFFER.buffers[head];
// Copy
    if ((void*)src_buffer != NULL)
    {
        memcpy( 
            u_buffer,   // User buffer to get the data. 
            src_buffer, // Where the buffer was stored in the list.
            len );      // Lenght.
    
        // Now this buffer is empty.
        NETWORK_BUFFER.is_full[head] = FALSE;
    }

    //printf("network_buffer_in: ok\n");
    //refresh_screen();
    //return 0;  //ok
    return (int) len;
    
fail:
   return (int) -1;
}

void networkSetStatus (int status)
{
    if ( status < 0 || status > 1 ){
        return;
    }
    network_status = (int) status;
}

int networkGetStatus (void)
{
    return (int) network_status;
}



void networkSetOnlineStatus(int status)
{
    if (status != TRUE && status != FALSE)
        return;
    __is_online = (int) status;
}


int networkGetOnlineStatus(void)
{
    return (int) __is_online;
}


void networkUpdateCounter(int the_counter)
{
// Update counter for the current network.
// 1=TX | 2=RX.

    if ( (void*) CurrentNetwork == NULL )
        return;
    if (CurrentNetwork->magic != 1234)
        return;

    if (the_counter == 1){
        CurrentNetwork->tx_counter++;
        return;
    }
    if (the_counter == 2){
        CurrentNetwork->rx_counter++;
        return;
    }
}

/*
 * networkInit: 
 * It only initializes some network structures. 
 * Not the adapters.
 * Initialize the buffers used by the NIC adapter.
 * Initialize HostInfo structure.
 * Create a default socket structure for localhost. 
 * CurrentSocket = LocalHostHTTPSocket
 */ 
// Called by I_init() in x64init.c.
// #fixme
// Provavelmente esse alocador ainda nao funciona.

int networkInit (void)
{
    register int i=0;
    void *tmp_buffer_address;

    debug_print ("networkInit: [TODO] [FIXME]\n");

// The network is disabled.
    networkSetStatus(FALSE);

// We're offline.
    networkSetOnlineStatus(OFFLINE);

// =====================================================
// #importante
// Essa é a flag que indica que a última inicialização foi feita.
// Aquela chamada por processos inicializadores em ring3.
// Com essa flag acionada o handler do nic poderá
// decodificar o buffer, caso contrário deve ignorar.

    ____network_late_flag=0;


//======================================

    struct network_info_d *ni;
    ni = (void*) kmalloc( sizeof( struct network_info_d ) );
    if ( (void*) ni == NULL ){
        panic("networkInit: ni\n");
    }
    // Clear the structure,
    memset( ni, 0, sizeof (struct network_info_d) );
    ni->initialized = FALSE;
    ni->id = 0;
    ni->version_major = 0x0000;
    ni->version_minor = 0x0000;
    ni->version_revision = 0x0000;
    
    // ...

    ni->name_string = (void*) default_network_name_string;
    ni->name_string_size = (size_t) strlen(default_network_name_string);

    ni->version_string = (void*) default_network_version_string;
    ni->version_string_size = (size_t) strlen(default_network_version_string);

// Gateway info.
// Clear the info. (again)
    for (i=0; i<6; i++){
        ni->gateway_mac[i] = 0;
    };
    for (i=0; i<4; i++){
        ni->gateway_ipv4[i] = 0;
    };
    ni->gateway_initialized = FALSE;

// Counters.
    ni->tx_counter=0;
    ni->rx_counter=0;

    ni->next = NULL;
    ni->used = TRUE;
    ni->magic = 1234;
    
    // This structure is initialized.
    ni->initialized = TRUE;
    CurrentNetwork = (struct network_info_d *) ni;

//======================================

// buffers:
// We will create 32 buffers to receive data and
// 8 buffers to send data.

// #fixme
// Provavelmente esse alocador ainda nao funciona.

    NETWORK_BUFFER.initialized = FALSE;

// =====================================
// receive buffers
    for (i=0; i<32; i++){
        tmp_buffer_address = (void*) newPage();
        if ((void *)tmp_buffer_address == NULL){
            panic("networkInit: [FAIL] receive tmp_buffer_address\n");
        }
        NETWORK_BUFFER.buffers[i] = (unsigned long) tmp_buffer_address;
        NETWORK_BUFFER.is_full[i] = FALSE;  //EMPTY
    };
    NETWORK_BUFFER.receive_tail=0;
    NETWORK_BUFFER.receive_head=0;
// ========================================
// flag
    NETWORK_BUFFER.initialized = TRUE;

// =====================================
// Host info struct. 
// See: host.h
    debug_print ("networkInit: HostInfo \n");

    HostInfo = 
        (struct host_info_d *) kmalloc( sizeof( struct host_info_d ) ); 
    if ( (void *) HostInfo == NULL ){
        panic("networkInit: HostInfo\n");
    }

//
// hostname
//

    //HostInfo->__hostname[0] = 'h';
    //HostInfo->hostName_len = (size_t) HOST_NAME_MAX;

    sprintf(HostInfo->__hostname,"gramado");
    HostInfo->hostName_len = (size_t) strlen("gramado");
    if ( HostInfo->hostName_len >= HOST_NAME_MAX ){
        panic("networkInit: hostname\n");
    }

// Version
    HostInfo->hostVersion = NULL;
// #todo
// Call some helpers to get these values.
// Maybe the init process needs to setup these values.
// It's because these values are found in files.
    HostInfo->hostVersionMajor    = 0;
    HostInfo->hostVersionMinor    = 0; 
    HostInfo->hostVersionRevision = 0;
// #todo
// Where is this information?
    HostInfo->hostArchitecture = 0;
    HostInfo->used = TRUE;
    HostInfo->magic = 1234;

    CurrentNetwork->host_info = (void*) HostInfo;

// Socket
// Criando socket para local host porta 80;
// Localhost (127.0.0.1):80 
// Configurando soquete atual.

    debug_print ("networkInit: LocalHostHTTPSocket\n");

    LocalHostHTTPSocket = (struct socket_d *) create_socket_object();  
    if ( (void *) LocalHostHTTPSocket == NULL ){
        panic ("networkInit: Couldn't create LocalHostHTTPSocket\n");
    }
    CurrentSocket = (struct socket_d *) LocalHostHTTPSocket;

// Initializes the socket list.
    socket_init();

// Status
// #todo:
// Some ring3 process will set the status.
// Untill this, the network module will drop
// all the packets and will not send any packet.
// see: 
// network_on_receiving() and network_on_sending();

    //networkSetStatus(TRUE);

    return 0;
}

