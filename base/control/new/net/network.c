
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
    printf("SendARP:\n");
    refresh_screen();

    struct ether_header *eh;
    struct ether_arp *h;
    int i=0;

    if ( (void*) currentNIC == NULL ){
        printf ("SendARP: currentNIC fail\n");
        return;
    }

// Source IP.
// Configurando a estrutura do dispositivo.
// #bugbug
// Estamos configurando a estrutura do dispositivo
// Esse não é o momento de fazermos isso.
// 192.168.1.112
// ip do gramado.
    currentNIC->ip_address[0] = source_ip[0];  //192;
    currentNIC->ip_address[1] = source_ip[1];  //168;
    currentNIC->ip_address[2] = source_ip[2];  //1;
    currentNIC->ip_address[3] = source_ip[3];  //112;
    //...

//==============================================
// # ethernet header #
//

    eh = (void *) kmalloc( sizeof(struct ether_header) );
    if ( (void *) eh == NULL){
        printf ("SendARP: eh struct fail\n");
        return;
    }else{
		// Coloca na estrutura do ethernet header os seguintes valores: 
		// > endere�o mac da origem.
		// > endere�o mac do destion.
		// O endere�o mac da origem est� na estrutura do controlador nic intel. 
		// O endere�o mac do destino foi passado via argumento.
        for ( i=0; i<6; i++){
            eh->src[i] = currentNIC->mac_address[i];    // source
            eh->dst[i] = target_mac[i];                 // dest. 
        };
        eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);
        //...
    };



//==============================================
// # arp header #
//
    h = (void *) kmalloc ( sizeof(struct  ether_arp) );
    if ( (void *) h == NULL){
        printf ("SendARP: struct h fail");
        return;
    }else{
		// Hardware type (HTYPE)   (00 01)
		// Protocol type (PTYPE)   (08 00)
		// Hardware address length (MAC)
		// Protocol address length (IP)
        h->type = 0x0100;
        h->proto = 0x0008;
        h->hlen = 6;
        h->plen = 4;
		// Operation (OPER) (dois bytes invertidos)
        //invalid operation
        if (op != ARP_OPC_REQUEST && op != ARP_OPC_REPLY ){
            //#debug
            panic ("SendARP: invalid operation");
        }
        h->op = ToNetByteOrder16(op);        
        //h->op = ToNetByteOrder16(ARP_OPC_REPLY);
        //h->op = ToNetByteOrder16(ARP_OPC_REQUEST);

		// mac
		// Configurando na estrutura de arp o endere�o mac de origem e destino.
		// sender mac
		// target mac
		// O endere�o mac de origem pegamos na estrutura no nic intel.
		// O endere�o mac de destino foi passado via argumento.
        for ( i=0; i<6; i++ ){
            h->arp_sha[i] = currentNIC->mac_address[i]; 
            h->arp_tha[i] = target_mac[i]; 
        };

		// ip
		// Configurando na estrutura de arp o endere�o do ip de origem e 
		// o ip de destino.
		// sender ip
		// target ip
		// Os endere�os foram passados via argumento.
        for ( i=0; i<4; i++ ){
            h->arp_spa[i] = source_ip[i]; 
            h->arp_tpa[i] = target_ip[i]; 
        };
        //...
    };

	//==================================
	//#debug
	//show arp
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
// === # BUFFER # =====
//

// ??
// Quem?
// Estamos pegando o offset que nos levar ao endere�o do buffer.
// Usaremos esse offset logo abaixo.
// Pegamos esse offset na estrutura do controlador nic intel.
    uint16_t old = currentNIC->tx_cur;
// Copiando o pacote no buffer.
// Pegando o endere�o virtual do buffer na estrutura do controlador 
// nic intel. Para isso usamos o offset obtido logo acima.
    unsigned char *buffer = 
        (unsigned char *) currentNIC->tx_descs_virt[old];

// #importante:
// Preparando ponteiros para manipularmos as estruturas usadas no pacote.
    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp = (unsigned char *) h;

//
// Copy.
//

// Copiando as estruturas para o buffer.
// >Copiando o header ethernet.
// >Copiando o arp logo ap�s do header ethernet.

// ethernet, arp.
    for (i=0; i<14;i++){ buffer[i]      = src_ethernet[i]; };
    for (i=0; i<28;i++){ buffer[i + 14] = src_arp[i]; };

// lenght:
// Vamos configurar na estrutura do nic intel o tamanho do pacote.
// Ethernet frame length = ethernet header (MAC + MAC + ethernet type) + ethernet data (ARP header)
// O comprimento deve ser o tamanho do header ethernet + o tamanho do header arp.
// 14 + 28;
    currentNIC->legacy_tx_descs[old].length = 
        ( ETHERNET_HEADER_LENGHT + ARP_HEADER_LENGHT );

	//??
	//cso
	//currentNIC->legacy_tx_descs[0].cso

	//??
	//cmd ok
	//currentNIC->legacy_tx_descs[0].cmd = TDESC_CMD_IFCS | TDESC_CMD_RS | TDESC_CMD_EOP;
	//currentNIC->legacy_tx_descs[0].cmd = TDESC_EOP | TDESC_RS; //intel code


// cmd
    currentNIC->legacy_tx_descs[old].cmd = 0x1B;
// status
    currentNIC->legacy_tx_descs[old].status = 0;
// Current TX.
// Qual � o buffer atual para transmiss�o.
    currentNIC->tx_cur = ( currentNIC->tx_cur + 1 ) % 8;

	//css
	//currentNIC->legacy_tx_descs[0].css

	//??
	//special ?
	//currentNIC->legacy_tx_descs[0].special

//
// ==== # SEND # ======
//

// #importante: 
// Diga ao controlador qual é o índice do descritor a ser usado 
// para transmitir dados.
// TDH	= 0x3810,    /* Tx Descriptor Head */
// TDT	= 0x3818,    /* Tx Descriptor Tail */

    // *( (volatile unsigned int *)(currentNIC->mem_base + 0x3810)) = 0;
    *( (volatile unsigned int *)(currentNIC->mem_base + 0x3818)) = currentNIC->tx_cur;

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

    int t=0;
    for (t=0; t< 25000;t++)
    {
         if ( (currentNIC->legacy_tx_descs[old].status & 0xFF) == 1 )
         {
              debug_print ("SendARP: done [timeout]\n");
              //printf ("Ok");
              return;
         }
    };

    //#todo
    /*
    while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
    {
        // Nothing.
    };
    */

    //debug_print ("SendARP: fail timeout.\n");    
    //debug_print ("SendARP: done\n");
    //printf (">>>> fail timeout.\n");

    printf("SendARP: done\n");
    refresh_screen();
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
    target_ip_address[3] = 88; //105;//111; 

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

