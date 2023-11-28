
// network.c
// Network layer. (IP)
// Transport layer. (TCP/UDP/...)

#include <kernel.h>


// Local
static struct network_initialization_d  NetworkInitialization;

// Status do driver de network
// 0 - uninitialized
// 1 - initialized
//static int __network_is_initialized = FALSE;

// Are we online?
// Do we already have an valid IP?
//static int __network_is_online = FALSE;

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


static void __initialize_ws_info(pid_t pid);
static void __maximize_ws_priority(pid_t pid);

// ====================================================


// Setup WindowServerInfo global structure.
static void __initialize_ws_info(pid_t pid)
{
    struct process_d *p;
    struct thread_d *t;
    pid_t current_process = -1;

    //debug_print ("__initialize_ws_info:\n");

// Maybe we can just emit an error message and return.
    if (WindowServerInfo.initialized == TRUE){
        panic("__initialize_ws_info: The ws is already running\n");
    }
    WindowServerInfo.initialized = FALSE;

// -----------------
// PID
// Get process pointer.
    if (pid < 0 || pid >= PROCESS_COUNT_MAX){
        return;
    }
    current_process = (pid_t) get_current_process();
    if (pid != current_process){
        panic("__initialize_ws_info: pid != current_process\n");
    }
    p = (struct process_d *) processList[pid];
    if ((void*) p == NULL){
        return;
    }
    if (p->magic != 1234){
        return;
    }
    WindowServerInfo.pid = (pid_t) pid;

// -----------------
// TID
// The control thread.
    t = (struct thread_d *) p->control;
    if ((void*) t == NULL){
        return;
    }
    if (t->magic != 1234){
        return;
    }
    WindowServerInfo.tid = (tid_t) t->tid;

// ----------------
// Process Personality
    p->personality = (int) PERSONALITY_GRAMADO_AMAZING;
    WindowServerInfo.pid_personality = (int) PERSONALITY_GRAMADO_AMAZING;

// ----------------
// The environment.
// The display server.
    p->env_subsystem = GramadoSubsystem;

// ----------------
// GID
// Update the group that this process belongs to.
    p->gid = (gid_t) GID_DISPLAY_SERVER;
    p->rgid = (gid_t) GID_DISPLAY_SERVER;  // real
    p->egid = (gid_t) GID_DISPLAY_SERVER;  // effective
    p->sgid = (gid_t) GID_DISPLAY_SERVER;  // saved

    WindowServerInfo.initialized = TRUE;
}


// #test
// Changing the window server's quantum. 
// The purpose here is boosting it when it is trying to register itself.
// class 1: Normal threads.
static void __maximize_ws_priority(pid_t pid)
{
    struct process_d *p;
    struct thread_d *t;

    unsigned long ProcessType         = PROCESS_TYPE_SYSTEM;
    unsigned long ProcessBasePriority = PRIORITY_SYSTEM_THRESHOLD;
    unsigned long ProcessPriority     = PRIORITY_MAX;

    unsigned long ThreadType         = ProcessType;
    unsigned long ThreadBasePriority = ProcessBasePriority;
    unsigned long ThreadPriority     = ProcessPriority;

    pid_t current_process = (pid_t) get_current_process();

    if (pid<=0 || pid >= PROCESS_COUNT_MAX){
        return;
    }
    if (pid != current_process){
        debug_print ("__maximize_ws_priority: pid != current_process\n");
        panic       ("__maximize_ws_priority: pid != current_process\n");
    }

// process
    p = (struct process_d *) processList[pid];
    if ((void*)p==NULL)
        return;
    if (p->used!=TRUE)
        return;
    if (p->magic!=1234)
        return;

    p->type = ProcessType;

    p->base_priority = ProcessBasePriority;
    p->priority      = ProcessPriority;

// thread
    t = (struct thread_d *) p->control;
    if ( (void*) t == NULL ){ return; }
    if ( t->magic != 1234 ) { return; }

    t->type = ThreadType;

    t->base_priority = ThreadBasePriority;
    t->priority      = ThreadPriority;

// see: ps/sched.h
    t->quantum = QUANTUM_MAX;
}

int 
network_register_ring3_display_server(
    struct zing_hook_d *zh,
    pid_t caller_pid )
{
// 513 - SYS_SET_WS_PID
// Syscall implementation.

    struct process_d *p;
    pid_t current_process = (pid_t) get_current_process();

// parameter:
    if ((void*) zh == NULL)
        goto fail;
    if (zh->magic != 1234)
        goto fail;

// parameter:
// Invalid caller.
    if (caller_pid != current_process){
        panic("network_register_ring3_display_server: caller_pid\n");
    }

//
// Process
// 
    if ( current_process < 0 ||
         current_process >= PROCESS_COUNT_MAX )
    {
        panic("network_register_ring3_display_server: current_process\n");
    }
    p = (struct process_d *) processList[current_process];
    if ((void*) p == NULL)
        panic("network_register_ring3_display_server: p\n");
    if (p->magic != 1234)
        panic("network_register_ring3_display_server: p magic\n");


// Register_ws_process(current_process);
    zh->__display_server_pid = (pid_t) current_process;

// #todo
// Maybe this method belongs to the sys_bind() routine.
    socket_set_gramado_port(
        GRAMADO_PORT_WS,
        (pid_t) current_process );

    __initialize_ws_info(current_process);
    __maximize_ws_priority(current_process);

// Setup c1/
// Change the foreground console.
    console_set_current_virtual_console(CONSOLE1);

// Setup the new layer for this process.
    p->_layer = (int) LAYER_ZING_DISPLAY_SERVER;

// #test
    struct thread_d *t;
    t = p->control;
    if ((void*) t == NULL)
        goto fail;
    if (t->magic != 1234)
        goto fail;

// #test
    t->pe_mode = PE_MODE_PERFORMANCE;

    return TRUE;

fail:
    return (int) -1;
}





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
void network_test_NIC(void)
{
    // #debug
    //printf("testNIC:\n");

    //network_send_arp_request();
    //network_test_udp();
    // ...

// Show NIC info.
    e1000_show_info();

    // #debug
    //printf("testNIC: done\n");
}

void 
network_send_raw_packet (
    struct intel_nic_info_d *dev, 
    size_t frame_len, 
    const char *frame_address ) 
{
    struct intel_nic_info_d *nic_intel;
    nic_intel = dev;

// dev
    if ((void*) nic_intel == NULL)
       return;
    if (nic_intel->magic != 1234)
        return;
// frame_len
    if (frame_len<0)
        return;
    if (frame_len > NETWORK_DEFAULT_BUFFER_SIZE)
        return;
// frame_address
    if ((void*) frame_address == NULL)
        return;
//
// Send
//

// #bugbug
// For now we only support the structure for intel devices.
    e1000_send( nic_intel, frame_len, frame_address );
}


// IN:
// + frame base address
// + frame total size
// Called by __e1000_on_receive() in e1000.c.
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
// Set this flag using the command "net-on" on terminal.bin.
    if (NetworkInitialization.initialized != TRUE)
    {
        //#debug
        //printf("Packet: Network is OFF\n");
        goto fail;
    }

// Frame validation

    if ((void*) frame == NULL){
        //printf("network_on_receiving: frame\n");
        goto fail;
    }
    // 1~8192
    if ( frame_size <= 0 || frame_size > E1000_DEFAULT_BUFFER_SIZE ){
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

// Ethernet header
    if ((void*) eth == NULL){
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


// Get ethernet type

    Type = (uint16_t) FromNetByteOrder16(eth->type);

// Handle the rthernet type
// See: ipv6.c, ipv4.c, arp.c.

    switch (Type){

    // #todo
    case ETHERTYPE_IPV6:
        // Drop it
        goto fail;
        break;

    case ETHERTYPE_IPV4:
        network_handle_ipv4( 
            (frame + ETHERNET_HEADER_LENGHT), 
            (frame_size - ETHERNET_HEADER_LENGHT) );
        break;

    case ETHERTYPE_ARP:
        network_handle_arp( 
            (frame + ETHERNET_HEADER_LENGHT), 
            (frame_size - ETHERNET_HEADER_LENGHT) );
        break;

    // ...

    default:
        // printf ("Default type\n");
        goto fail;
        break;
    };

// done:
    return 0;
fail:
    return (int) -1;
}


int 
network_on_sending ( 
    const unsigned char *frame, 
    ssize_t frame_size )
{
    if (NetworkInitialization.initialized != TRUE){
        return -1;
    }

//fail:
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
// #bugbug: 
// What kind of data we're pushing into these buffers?
// Is it the raw frame only? Or only UDP?

    void *dst_buffer;
    int tail=0;

    printf ("--------------------- >>>> PUSH\n");

// Check args
    if ((void*) src_buffer == NULL){
        panic("network_push_packet: src_buffer\n");
    }

// #todo
// Veja na configuração do dispositivo, que o buffer 
// configurado para o hardware é de 0x3000 bytes.
    if (len > 1500){
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

    //debug_print("network_pop_packet:\n");

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
    NetworkInitialization.initialized = (int) status;
}

int networkGetStatus (void)
{
    return (int) NetworkInitialization.initialized;
}

void networkSetOnlineStatus(int status)
{
    if (status != TRUE && status != FALSE)
        return;
    NetworkInitialization.is_online = (int) status;
}

int networkGetOnlineStatus(void)
{
    return (int) NetworkInitialization.is_online;
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

int networkInit(void)
{
// Initializing the network infrastructure.
// The purpose here is initialize all the components that is possible
// without aborting the kernel initialization.
// Maybe we can survice some failures here and re-initialize it later.

    register int i=0;
    void *tmp_buffer_address;

    PROGRESS("networkInit:\n");

//======================================
// Network initialization structure.


// Not initialized yet.
// The network is disabled
    networkSetStatus(NETWORK_NOT_INITIALIZED);
// We're offline
    networkSetOnlineStatus(NETWORK_OFFLINE);

// =====================================================
// #importante
// Essa é a flag que indica que a última inicialização foi feita.
// Aquela chamada por processos inicializadores em ring3.
// Com essa flag acionada o handler do nic poderá
// decodificar o buffer, caso contrário deve ignorar.

    ____network_late_flag=0;


//======================================
// Network info structure

    struct network_info_d *ni;
    ni = (void*) kmalloc( sizeof(struct network_info_d) );
    if ((void*) ni == NULL){
        printf("on ni\n");
        goto fail;
    }
    // Clear the structure
    memset( ni, 0, sizeof(struct network_info_d) );
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
    for (i=0; i<32; i++)
    {
        tmp_buffer_address = (void*) mmAllocPage();
        if ((void *)tmp_buffer_address == NULL)
        {
            printf("on tmp_buffer_address\n");
            goto fail;
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
    //debug_print ("networkInit: HostInfo\n");

    HostInfo = 
        (struct host_info_d *) kmalloc( sizeof(struct host_info_d) ); 
    if ((void *) HostInfo == NULL){
        printf("on HostInfo\n");
        goto fail;
    }

// #todo
// We need to grab the hostname from another place.
// Maybe from a configuration file.
// UTS_NODENAME ?

    //HostInfo->__hostname[0] = 'h';
    //HostInfo->hostName_len = (size_t) HOST_NAME_MAX;

    sprintf(HostInfo->__hostname,"gramado");
    HostInfo->hostName_len = (size_t) strlen("gramado");
    if ( HostInfo->hostName_len >= HOST_NAME_MAX )
    {
        printf("on hostname\n");
        goto fail;
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

    //debug_print ("networkInit: LocalHostHTTPSocket\n");

    LocalHostHTTPSocket = (struct socket_d *) create_socket_object();
    if ((void *) LocalHostHTTPSocket == NULL)
    {
        printf("on LocalHostHTTPSocket\n");
        goto fail;
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

// =====================================
// domain

//
// Create the domain structure.
//

// It describes the domain this node belongs to.

    struct domain_d *my_domain;
    my_domain = (void *) domain_create_domain(UTS_DOMAINNAME);
    if ((void*) my_domain == NULL)
    {
        printf("on my_domain\n");
        goto fail;
    }

// =====================================
// arp cache

// Initialize the ARP table
    arp_initialize_arp_table();

// ...

// done
    return 0;

fail:
    // #debug
    // For now we cant's fail on the network initialization.
    panic("networkInit: Fail\n");
    return (int) -1;
}

