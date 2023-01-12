
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

unsigned char broadcast_mac[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
unsigned char gramado_default_ipv4[4] = { 192, 168, 1, 112 };
unsigned char target_default_ipv4[4]  = { 192, 168, 1, 8 };
unsigned char gateway_default_ipv4[4] = { 192, 168, 1, 1 };

// ====================================================

void 
network_send_arp( 
    int op,   //operation
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6] )
{
    struct ether_header *eh;
    struct ether_arp *h;
    register int i=0;

    // #debug
    printf("network_send_arp:\n");
    refresh_screen();

// The structure for the INtel NIC device.
    if ( (void*) currentNIC == NULL ){
        printf ("network_send_arp: currentNIC fail\n");
        goto fail;
    }

// A given IP number for Gramado.
// Saving it into the NIC structure.
// 192.168.1.112

    currentNIC->ip_address[0] = source_ip[0];  //192;
    currentNIC->ip_address[1] = source_ip[1];  //168;
    currentNIC->ip_address[2] = source_ip[2];  //1;
    currentNIC->ip_address[3] = source_ip[3];  //112;

//==============================================
// # ethernet header #
    eh = (void *) kmalloc( sizeof(struct ether_header) );
    if ( (void *) eh == NULL){
        printf ("network_send_arp: eh struct fail\n");
        goto fail;
    }
// MAC
// Save the source and the destination mac into the ethernet header.
// The destination mac came via argument.
    for ( i=0; i<ETH_ALEN; i++){
        eh->mac_src[i] = (uint8_t) currentNIC->mac_address[i];
        eh->mac_dst[i] = (uint8_t) target_mac[i];
    };
// TYPE
    eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);

//==============================================
// # arp header #
    h = (void *) kmalloc ( sizeof(struct  ether_arp) );
    if ( (void *) h == NULL ){
        printf ("network_send_arp: struct h fail");
        goto fail;
    }

//
// Header
// see: arp.h
//

// Hardware type (HTYPE)   (00 01)
    h->type = (uint16_t) 0x0100;
// Protocol type (PTYPE)   (08 00)
    h->proto = (uint16_t) 0x0008;
// Hardware address length (MAC)
    h->hlen = (uint8_t) ETH_ALEN;
// Protocol address length (IP)
    h->plen = (uint8_t) 4;
// Operation (OPER)
// We only have two valid operation codes.
    if ( op != ARP_OPC_REQUEST && 
         op != ARP_OPC_REPLY )
    {
        panic("network_send_arp: Invalid operation code\n");
    }
    h->op = (uint16_t) ToNetByteOrder16(op);  // Invert the two bytes.

//
// Addresses
//

// MAC addresses
// Hardware address
    for ( i=0; i<ETH_ALEN; i++ ){
        h->arp_sha[i] = (uint8_t) currentNIC->mac_address[i];  //my MAC
        h->arp_tha[i] = (uint8_t) target_mac[i]; 
    };
// IP addresses
// Protocol address
    for ( i=0; i<4; i++ ){
        h->arp_spa[i] = (uint8_t) source_ip[i]; 
        h->arp_tpa[i] = (uint8_t) target_ip[i]; 
    };

//==================================
// #debug
// show arp header.

/*
    printf("\n\n");
    printf("[arp]\n\n");
    printf("type={%x} proto={%x} hlen={%d} plen={%d} op={%x} \n", 
        h->type ,h->proto ,h->hlen ,h->plen ,h->op);
    printf("\n sender: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_sha[i]); }
    printf("\n sender: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_spa[i]); }
    printf("\n target: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_tha[i]); }
    printf("\n target: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_tpa[i]); }
    refresh_screen();
    while(1){}
*/
//==================================

//
// Buffer
//

// Set up the pointers for the copy.

// Offset do endereço do buffer.
// Estamos pegando o offset que nos leva ao endereço do buffer.
// Pegamos esse offset na estrutura do controlador nic intel.
// see: nicintel.h

// pega o tail antigo.
    //unsigned long address = (currentNIC->registers_base_address + 0x3810); //head
    //unsigned long address = (currentNIC->registers_base_address + REG_TDT); // tail
    //unsigned int value32 = (uint16_t) *( (volatile unsigned int *) address );
    //currentNIC->tx_cur = (uint16_t) (value32 & 0xFFFF);
    uint16_t buffer_index = (uint16_t) currentNIC->tx_cur;

    //#debug
    //printf ("buffer_index {%d}\n",buffer_index);

// Get the buffer address based on its offset.
    unsigned char *buffer = 
        (unsigned char *) currentNIC->tx_buffers_virt[buffer_index];
// Get the addresses for the headers.
    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp      = (unsigned char *) h;


    if ((void*) buffer == NULL){
        printf("network_send_arp: buffer\n");
        goto fail;
    }

//
// Copy
//

// Copy the ethernet header into the buffer.
// 14 bytes.
    for (i=0; i<ETHERNET_HEADER_LENGHT; i++){
        buffer[i] = (unsigned char) src_ethernet[i];
    };
// Copy the arp header into the buffer.
// 28 bytes
// It starts right after the ethernet header.
    for (i=0; i<ARP_HEADER_LENGHT; i++){
        buffer[ETHERNET_HEADER_LENGHT + i] = (unsigned char) src_arp[i]; 
    };

// ======================
// Sending via e1000 api.

    e1000_send(
        currentNIC,
        ( ETHERNET_HEADER_LENGHT + ARP_HEADER_LENGHT ),
        buffer );

/*
    // not good.
    e1000_send(
        currentNIC,
        ( ARP_HEADER_LENGHT ),
        buffer );
*/

    refresh_screen();
    return;

fail:
    refresh_screen();
    return;
}





void network_send_arp_request(void)
{
// Send ARP request to a Linus host.
    network_send_arp( 
        ARP_OPC_REQUEST, 
        gramado_default_ipv4,  // src ip 
        target_default_ipv4,   // dst ip (Linux)
        broadcast_mac          // target mac
        );
}

void network_send_arp_reply(void)
{
// Send ARP request to a Linus host.

// #bugbug
// Sending reply to broadcast

    network_send_arp( 
        ARP_OPC_REPLY, 
        gramado_default_ipv4,  // src ip 
        target_default_ipv4,   // dst ip (Linux)
        broadcast_mac          // target mac
        );
}

// Test, called by the kernel console.
void testNIC(void)
{
    // #debug
    printf("testNIC:\n");
    refresh_screen();

    network_send_arp_request();
    
// ...

    e1000_show_info();

    // #debug
    printf("testNIC: done\n");
    refresh_screen();
}

void 
network_on_receiving ( 
    const unsigned char *buffer, 
    ssize_t size )
{
    struct ether_header *eth = 
        (struct ether_header *) buffer;
    uint16_t Type=0;

    if ( (void*) buffer == NULL ){
        return;
    }

    if (size <= 0){
        printf("network_on_receiving: size<=0\n");
        return;
    }
    // 8192
    if (size > E1000_DEFAULT_BUFFER_SIZE){
        printf("network_on_receiving: size>8192\n");
        return;
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
        return;
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


    Type = (uint16_t) FromNetByteOrder16(eth->type);

    switch (Type){
    case 0x0800:
        printf ("[0x0800]: IPV4 received\n");
        network_handle_ipv4(
            (buffer + ETHERNET_HEADER_LENGHT),
            size );
        break;
    case 0x0806:
        printf ("[0x0806]: ARP received\n");
        network_handle_arp(
            (buffer + ETHERNET_HEADER_LENGHT),
            size );
        break;
    case 0x814C:
        printf ("[0x814C]: SNMP received\n");
        break;
    case 0x86DD:
        printf ("[0x86DD]: IPV6 received\n");
        break;
    case 0x880B:
        printf ("[0x880B]: PPP received\n");
        break;
    default:
        printf ("Default type\n");
        break;
    };

    refresh_screen();
}





// handle ipv4 package
// Called by all the embedded nic device drivers.
// IN:
// buffer = The address after the ethernet header.
void 
network_handle_ipv4( 
    const unsigned char *buffer, 
    ssize_t size )
{
    struct ip_d *ip;
    ip = (struct ip_d *) buffer;

    printf("network_handle_ipv4: ==== IP ====\n");

    if ( (void*) ip == NULL ){
        printf("network_handle_ipv4: ip\n");
    }

    unsigned char *src_ipv4 = 
        (unsigned char *) &ip->ip_src.s_addr;
    unsigned char *dst_ipv4 = 
        (unsigned char *) &ip->ip_dst.s_addr;

// Show data.
// Bytes: Net-style.

    uint8_t v_hl = (uint8_t) ip->v_hl;
    uint8_t Version = (uint8_t) ((v_hl >> 4) & 0x0F);
    uint8_t Lenght  = (uint8_t) (v_hl & 0x0F);  // Header lenght. 5=20bytes.

    printf("IP Version: {%d}\n", Version);
    printf("Header lenght: {%d}\n", Lenght);

    if (Version!=4){
        printf("Not version 4\n");
        goto fail;
    }

// Total lenght (16bits)
// (IP + (TCP + data)) given in bytes.
// 20~65535
    printf("Total lenght: {%d}\n",ip->ip_len);

    if (ip->ip_len < 20 || ip->ip_len > 65535){
        //#debug
        panic("Bad total lenght\n");
    }

    printf("Protocol: {%x}\n",ip->ip_p);

    if (ip->ip_p == 1){
        printf("ICMP Protocol\n");
    }

// ---------------
// Not to me.
    if ( dst_ipv4[3] != 112 ||
         dst_ipv4[2] != 1 ||
         dst_ipv4[1] != 168 ||
         dst_ipv4[0] != 192 )
    {
        printf ("NOT TO ME!\n");
        goto fail; 
    }

// ---------------
// To me.
    printf ("TO ME!\n");
    //printf("Src IPV4: {%x}\n", ip->ip_src.s_addr);
    //printf("Dst IPV4: {%x}\n", ip->ip_dst.s_addr);
    // destination
    printf ("Src: 0={%d} | 1={%d} | 2={%d} | 3={%d}\n",
        src_ipv4[0], src_ipv4[1], src_ipv4[2], src_ipv4[3]);
    printf ("Dst: 0={%d} | 1={%d} | 2={%d} | 3={%d}\n",
        dst_ipv4[0], dst_ipv4[1], dst_ipv4[2], dst_ipv4[3]);

    // hang
    refresh_screen();
    while(1){}

fail:
    refresh_screen();
    return;
}

// handle arp package
// Called by all the embedded nic device drivers.
// IN:
// buffer = The address after the ethernet header.
void 
network_handle_arp( 
    const unsigned char *buffer, 
    ssize_t size )
{

    struct ether_arp *ar;
    ar = (struct ether_arp *) buffer;

    printf("network_handle_arp: ==== ARP ====\n");

    if ( (void*) ar == NULL ){
        printf("network_handle_arp: ar\n");
    }

// Show data.
// Bytes: Net-style.
    printf("Hardware type: {%x}\n",ar->type);
    printf("Protocol type: {%x}\n",ar->proto);
    printf("Hardware address lenght: {%x}\n",ar->hlen);
    printf("Protocol address lenght: {%x}\n",ar->plen);
    printf("op    {%x}\n",ar->op);

// Operation
    uint16_t op = (uint16_t) FromNetByteOrder16(ar->op);
    
    if (op==ARP_OPC_REQUEST){
        printf("This is REQUEST\n");
        //sending a reply, only for the linux host.  x.x.x.8
        //printf("Sending reply to linux host\n");
        //network_send_arp_reply();
    } else if (op==ARP_OPC_REPLY){
        printf("This is REPLY\n");
    };

    refresh_screen();
    return;

fail:
    refresh_screen();
    return;
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

