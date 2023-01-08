
// network.c

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

// ====================================================

void 
SendARP( 
    int op,   //operation
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6] )
{
    struct ether_header *eh;
    struct ether_arp *h;
    register int i=0;

    // #debug
    printf("SendARP:\n");
    refresh_screen();

// The structure for the INtel NIC device.
    if ( (void*) currentNIC == NULL ){
        printf ("SendARP: currentNIC fail\n");
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
        printf ("SendARP: eh struct fail\n");
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
    if ( (void *) h == NULL){
        printf ("SendARP: struct h fail");
        return;
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
        panic("SendARP: Invalid operation code\n");
    }
    h->op = (uint16_t) ToNetByteOrder16(op);  // Invert the two bytes.

//
// Addresses
//

// MAC addresses
// Hardware address
    for ( i=0; i<ETH_ALEN; i++ ){
        h->arp_sha[i] = (uint8_t) currentNIC->mac_address[i]; 
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
        (unsigned char *) currentNIC->tx_descs_virt[buffer_index];
// Get the addresses for the headers.
    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp      = (unsigned char *) h;

//
// Copy
//

// Copy the ethernet header into the buffer.
// 14 bytes.
    for (i=0; i<ETHERNET_HEADER_LENGHT;i++)
    {
        buffer[i] = (unsigned char) src_ethernet[i];
    };
// Copy the arp header into the buffer.
// 28 bytes
// It starts right after the ethernet header.
    for (i=0; i<ARP_HEADER_LENGHT;i++)
    {
        buffer[ETHERNET_HEADER_LENGHT + i] = (unsigned char) src_arp[i]; 
    };

// ======================

// lenght:
// Vamos configurar na estrutura do nic intel o tamanho do pacote.
// Ethernet frame length: 
// O tamanho do header ethernet + o tamanho do header arp.
// ethernet header (MAC + MAC + ethernet type) + 
// ethernet data (ARP header)
// ( 14 + 28 );
// #bugbug:
// Is this the payload size.
    currentNIC->legacy_tx_descs[buffer_index].length = 
        (uint16_t) ( ETHERNET_HEADER_LENGHT + ARP_HEADER_LENGHT );
    //currentNIC->legacy_tx_descs[buffer_index].length = 
    //    (uint16_t) 8192;

// cso
// Checksum offset.
    //currentNIC->legacy_tx_descs[buffer_index].cso = ?;

// Primeiro zera o status,
// depois envia o comando.

// status
// status and reserved.
    currentNIC->legacy_tx_descs[buffer_index].status = (uint8_t) 0;


#define CMD_EOP  (1 << 0)  // End of Packet
#define CMD_IFCS (1 << 1)  // Insert FCS
#define CMD_IC   (1 << 2)  // Insert Checksum
#define CMD_RS   (1 << 3)  // Report Status
#define CMD_RPS  (1 << 4)  // Report Packet Sent
#define CMD_VLE  (1 << 6)  // VLAN Packet Enable
#define CMD_IDE  (1 << 7)  // Interrupt Delay Enable

// cmd
    currentNIC->legacy_tx_descs[buffer_index].cmd = 
        (uint8_t) 0x1B;
    //currentNIC->legacy_tx_descs[buffer_index].cmd = 
    //    (uint8_t) (CMD_EOP | CMD_IFCS | CMD_RS);
    //currentNIC->legacy_tx_descs[buffer_index].cmd = 
    //    (uint8_t) (TDESC_CMD_IFCS | TDESC_CMD_RS | TDESC_CMD_EOP);
    //currentNIC->legacy_tx_descs[buffer_index].cmd = 
    //    (uint8_t) (TDESC_EOP | TDESC_RS);  //intel code
    // CMD_EOP | CMD_IFCS | CMD_RS;

// css
// Checksum start
    //currentNIC->legacy_tx_descs[buffer_index].css = (uint8_t) 0;

// special
    //currentNIC->legacy_tx_descs[buffer_index].special = (uint16_t) 0;

// Update the current offset for the next transmission buffer.
// We have 8 transmission buffers.
    currentNIC->tx_cur = 
        (uint16_t) ( currentNIC->tx_cur + 1 ) % 8;

//
// Send
//

// #importante: 
// Diga ao controlador quais são os índices do descritor 
// a serem usado para transmitir dados.
// TDH = 0x3810,  /* Tx Descriptor Head */
// TDT = 0x3818,  /* Tx Descriptor Tail */
// ??
// #todo
// Por que estamos configurando somente o tail nesse momento?
// O offset é um valor de 16 bits.

    unsigned int head = (unsigned int) 0;  // The first one.
    unsigned int tail = (unsigned int) (currentNIC->tx_cur & 0xFFFF);  // The last one.

// TDH = 0x3810, Tx Descriptor Head.
    //*( (volatile unsigned int *)(currentNIC->registers_base_address + REG_TDH)) = 
    //    (unsigned int) head;

// TDT = 0x3818, Tx Descriptor Tail.
    *( (volatile unsigned int *)(currentNIC->registers_base_address + REG_TDT)) = 
        (unsigned int) tail;


// #debug
// Colocamos essa mensagem antes de entrarmos no while.
// Pois precisamos implementar algum contador no while para n�o
// ficarmos preso nele pra sempre.
    //debug_print ("SendARP: Sending broadcast ARP. *debug *while\n");
    //printf ("SendARP: Sending broadcast ARP. *debug *while\n");
    //refresh_screen ();

// #perigo:
// Status.
// Checamos o status do buffer old pra ver se ele foi enviado.
// Fica travado aqui at� que seja enviado?
// Poderia ter um timemout?.

// #todo
// This is a method for wating.
// Espera enquanto for 0.
// #bugbug: Isso pode esperar para sempre.
    
    /*
    while ( !(currentNIC->legacy_tx_descs[buffer_index].status & 0xFF) )
    {
        // Nothing.
    };
    */

/*
// Waiting using a timeout.
// Espera por um tempo pelo valor '1'.
    int t=0;
    int tmax = 5000000; //50000;
    uint8_t status = 0;
    for (t=0; t<tmax;t++)
    {
         // Get status
         status = (uint8_t) currentNIC->legacy_tx_descs[buffer_index].status;
         // Check if the status value is '1'.
         //if ( (status & 0xFF) == 1 )
         if ( (status & 0xFF) != 0 )
         {
              printf ("SendARP: [status ok] Done\n");
              refresh_screen();
              return;
         }
    };
    printf ("SendARP: [fail] Timeout\n");
    // goto fail;
*/

fail:
    refresh_screen();
    return;
}


// Test, called by the kernel console.
void testNIC(void)
{
    printf("testNIC:\n");
    refresh_screen();

    // Source = 192.168.1.112
    // Gramado.
    uint8_t source_ip_address[4];
    source_ip_address[0] = 192;
    source_ip_address[1] = 168;
    source_ip_address[2] = 1;   
    source_ip_address[3] = 112; 

    // Target = 192.168.1.111
    // Linux host.
    uint8_t target_ip_address[4];
    target_ip_address[0] = 192;
    target_ip_address[1] = 168;
    target_ip_address[2] = 1; 
    target_ip_address[3] = 8;  // Linux host machine.

    // MAC for broadcast.
    // 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF.
    uint8_t target_mac_address[6];
    target_mac_address[0] = 0xFF;
    target_mac_address[1] = 0xFF;
    target_mac_address[2] = 0xFF;
    target_mac_address[3] = 0xFF;
    target_mac_address[4] = 0xFF;
    target_mac_address[5] = 0xFF;


    SendARP( 
        ARP_OPC_REQUEST, 
        source_ip_address,   // src ip 
        target_ip_address,   // dst ip
        target_mac_address   // target mac
        );

    printf("testNIC: done\n");
    refresh_screen();
}

// handle ipv4 package
// Called by all the embedded nic device drivers.
void 
network_handle_ipv4( 
    const unsigned char *buffer, 
    ssize_t size )
{
    //printf("network_handle_ipv4: ==== IPV4 ====\n");

// Coloca em um dos buffers, 
// de onde os aplicativos podem pegar depois.
    network_buffer_in ( (void *) buffer, (int) size );
}

// handle arp package
// Called by all the embedded nic device drivers.
void 
network_handle_arp( 
    const unsigned char *buffer, 
    ssize_t size )
{
    //printf("network_handle_arp: ==== ARP ====\n");
}

// in: (Do buffer indicado para o buffer tail)
// Isso é usado pelo driver de dispositivo
// pra salvar o conteúdo que veio da rede em
// um buffer que pode ser lido pelos aplicativos.
int network_buffer_in( void *buffer, int len )
{
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

