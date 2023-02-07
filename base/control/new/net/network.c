
// network.c
// Network layer. (IP)
// Transport layer. (TCP/UDP/...)

#include <kernel.h>

// Status do driver de network
// 0 - uninitialized
// 1 - initialized
int network_status=FALSE; 

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


// ====================================================

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


int 
network_on_receiving ( 
    const unsigned char *frame, 
    ssize_t size )
{
// Handle ethernet header.

    struct ether_header *eth = 
        (struct ether_header *) frame;
    uint16_t Type=0;

    if ( (void*) frame == NULL ){
        printf("network_on_receiving: frame\n");
        goto fail;
    }

    // 1~8192
    if (size <= 0 || size > E1000_DEFAULT_BUFFER_SIZE){
        printf("network_on_receiving: size\n");
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
        network_handle_ipv4( (frame + ETHERNET_HEADER_LENGHT), size );
        break;
    case ETHERTYPE_ARP:
        Show=TRUE;
        network_handle_arp( (frame + ETHERNET_HEADER_LENGHT), size );
        break;
    // ...
    //case ETHERTYPE_IPv6:
    default:
        // printf ("Default type\n");
        goto fail;
        break;
    };

    if (Show){
        refresh_screen();
    }

    return 0;
fail:
    return -1;
}


int 
network_on_sending ( 
    const unsigned char *frame, 
    ssize_t size )
{
    return -1;
}

// in: (Do buffer indicado para o buffer tail)
// Isso é usado pelo driver de dispositivo
// pra salvar o conteúdo que veio da rede em
// um buffer que pode ser lido pelos aplicativos.
int network_buffer_in( void *buffer, int len )
{
// Push packet.

    int tail=0;
    void *dst_buffer;

// Check args
    if ( (void*) buffer == NULL ){
        panic ("network_buffer_in: buffer\n");
    }

// #todo
// Veja na configuração do dispositivo, que o buffer 
// configurado para o hardware é de 0x3000 bytes.
    if (len>1500){
        debug_print("network_buffer_in: [FIXME] len\n");
        len = 1500;
        //return -1;
    }

    if (NETWORK_BUFFER.initialized != TRUE){
        panic ("network_buffer_in: Shared buffers not initialized\n");
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
    if (tail < 0 || tail >= 32){
        return -1;
    }

// Check buffer status.
// Se o buffer está cheio é porque ele não foi consumido.
// Vamos sobrepor?
    int buffer_status = NETWORK_BUFFER.receive_status[tail];
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
    dst_buffer = (void*) NETWORK_BUFFER.receive_buffer[tail];
// Copy
    if ((void*)dst_buffer != NULL){
        memcpy( dst_buffer, buffer, len);
    }

// Avisamos que esse buffer está cheio.
    NETWORK_BUFFER.receive_status[tail] = TRUE;

    //printf("network_buffer_in: ok\n");
    //refresh_screen();
    return 0;  //ok

fail:
    return (int) -1;
}


// out: (Do buffer head para o buffer indicado)
// Isso é usado pelos aplicativos
// para pegarem os conteúdos salvos nos buffers.
// Daí os aplicativos interpretam os protocolos.
int network_buffer_out ( void *buffer, int len )
{
// Pop packet.

    int head=0;
    void *src_buffer;

    debug_print("network_buffer_out:\n");

// check args
    if ( (void*) buffer == NULL ){
        panic ("network_buffer_out: [FAIL] buffer\n");
    }

// #bugbug:
// Isso pode ser maior se considerarmos todos os headers.
// #todo
// Veja na configuração do dispositivo, que o buffer 
// configurado para o hardware é de 0x3000 bytes.
    if (len>1500){
        debug_print("network_buffer_out: [FIXME] len\n");
        len=1500;
        //return -1;
    }

    if (NETWORK_BUFFER.initialized != TRUE){
        panic ("network_buffer_out: Shared buffers not initialized\n");
    }

// Vamos pegar um numero de buffer para enviarmos o pacote.
// o kernel vai retirar do head ... 
// o que foi colocado pelo aplicativo em tail.
    head = (int) NETWORK_BUFFER.send_head;

// circula.
    NETWORK_BUFFER.send_head++;
    if (NETWORK_BUFFER.send_head >= 8){
        NETWORK_BUFFER.send_head=0;
    }

// #todo
// MTU: maximim transmition unit.
// For ethernet is 1500 bytes.
    //printf ("network_buffer_in: buffer_len %d\n",len);
    //refresh_screen();

    if (head<0 || head >= 8){
        return -1;
    }

// Get the source buffer.
    src_buffer = (void*) NETWORK_BUFFER.send_buffer[head];
// Copy
    if ((void*)src_buffer != NULL){
        memcpy( buffer, src_buffer, len );
    }

    //printf("network_buffer_in: ok\n");
    //refresh_screen();
    return 0;  //ok
    
fail:
   return (int) -1;
}

void networkSetstatus (int status)
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

// Status
    networkSetstatus(FALSE);

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
    ni->id = 0;
    ni->version_major = 0x0000;
    ni->version_minor = 0x0000;
    ni->version_revision = 0x0000;
    
    // ...

    ni->name_string = (void*) default_network_name_string;
    ni->name_string_size = (size_t) strlen(default_network_name_string);

    ni->version_string = (void*) default_network_version_string;
    ni->version_string_size = (size_t) strlen(default_network_version_string);

    ni->next = NULL;
    ni->used = TRUE;
    ni->magic = 1234;
    ni->initialized = FALSE;
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
        NETWORK_BUFFER.receive_buffer[i] = (unsigned long) tmp_buffer_address;
        NETWORK_BUFFER.receive_status[i] = FALSE;  //EMPTY
    };
    NETWORK_BUFFER.receive_tail=0;
    NETWORK_BUFFER.receive_head=0;
// ========================================
// send buffers
    for (i=0; i<8; i++){
        tmp_buffer_address = (void*) newPage();
        if((void *)tmp_buffer_address == NULL){
            panic("networkInit: [FAIL] send tmp_buffer_address\n");
        }
        NETWORK_BUFFER.send_buffer[i] = (unsigned long) tmp_buffer_address;
        NETWORK_BUFFER.send_status[i] = FALSE;  //EMPTY 
    };
    NETWORK_BUFFER.send_tail=0;
    NETWORK_BUFFER.send_head=0;
// =====================================

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
    networkSetstatus(TRUE);

    return 0;
}

