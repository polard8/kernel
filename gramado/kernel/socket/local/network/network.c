/*
 * File: sci/net/network.c
 *     
 *     Network sopport. 
 *     Ring 0, kernel base.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */

// See:
// https://wiki.osdev.org/Network_Stack
// https://wiki.osdev.org/Intel_Ethernet_i217


/*
uint16_t switch_endian16(uint16_t nb)
{
    return (nb>>8) | (nb<<8);
}
   
uint_t switch_endian32(uint_t nb)
{
       return ((nb>>24)&0xff)      |
              ((nb<<8)&0xff0000)   |
              ((nb>>8)&0xff00)     |
              ((nb<<24)&0xff000000);
}  
*/


/*
 @todo:
 Network packet
 Network topology
 Network links
 Network nodes
 Network interfaces
 Repeaters and hubs
 Bridges
 Switches
 Routers
 Firewalls
 Common layouts
 Overlay network
 Communications protocols
 IEEE 802
 Ethernet
 Wireless LAN
 Internet Protocol Suite
 Asynchronous Transfer Mode
 Personal area network
 Local area network
 Home area network
 Storage area network
 Backbone network
 Wide area network
 Enterprise private network
 Virtual private network
 Intranet
 Extranet
 Internetwork
 Internet
 Darknet
 Routing
 Network service *
 service protocol
 Network security
*/



#include <kernel.h>


// Status do driver de network
// 0 - uninitialized
// 1 - initialized

int network_status;   


// Status para notificações.
// Podemos ou não notificar os processo sobre os eventos de rede.
// O shell vai habilitar essa notificação no momento em que
// envia um stream para mensagens de texto.

int notification_status; 



// Usado por esse módulo.
file *____network_file;




// Colocar um buffer numa lista de buffers.
// Vamos copiar o pacote para alguma fila de buffers.
// A rotina de decodificar o pacote pegará o
// pacote em alguma fila de buffers.
// len: 
//     Tamanho do pacote. Temos que considerar limites.
// buffer:
//     Endereço do pacote.
// Copiamos se o comprimento está no limite.

int network_buffer_in( void *buffer, int len )
{
    void *dst_buffer;
    int tail = NETWORK_BUFFER.receive_tail;

    //circula.
    NETWORK_BUFFER.receive_tail++;
    if (NETWORK_BUFFER.receive_tail >= 32)
        NETWORK_BUFFER.receive_tail=0;

	// #todo
	// MTU: maximim transmition unit.
	// For ethernet is 1500 bytes.
	
    //printf ("network_buffer_in: buffer_len %d\n",len);
    //refresh_screen();


    if(len>1500)
        return -1;
        
    if(tail<0)
        return -1;
        
    // Pega o destination buffer.
    if (tail<32){
        dst_buffer = NETWORK_BUFFER.receive_buffer[tail];
       
       if((void*)dst_buffer!= NULL)
           memcpy( dst_buffer, buffer, len);        
    
        //printf("network_buffer_in: ok\n");
        //refresh_screen();
        return 0;//ok
    }

   return -1;
}


int ns_get_buffer(void *ubuf, int size)
{
    void *src_buffer;
    //temos que pegar do head. primeiro da fila.
    int head = NETWORK_BUFFER.receive_head;

    //circula.
    NETWORK_BUFFER.receive_head++;
    if (NETWORK_BUFFER.receive_head >= 32)
        NETWORK_BUFFER.receive_head=0;
        
    if(head<32){
        src_buffer = NETWORK_BUFFER.receive_buffer[head];
    
        if((void*)ubuf== NULL){
            printf("ns_get_buffer: ubuf fail\n");
            refresh_screen();        
            return -1;
        }
        
        if((void*)src_buffer== NULL){
            printf("ns_get_buffer: src_buffer fail\n");
            refresh_screen();        
            return -1;
        }

        //do kernel para user mode.
        if((void*)ubuf!= NULL)
            memcpy( ubuf, src_buffer, size);        

        //printf("ns_get_buffer: ok\n");
        //refresh_screen();
        return 0;//ok
    }

    return -1;
}


// Retirar um buffer de uma lista de buffers.
// O gns chamará essa rotina e copiará um buffer
// para ring3, onde chamará as rotinas de protocolo.
int network_buffer_out (void)
{
    return -1;
}


/*
//o ns envia um buffer pra ser enviado para rede.
int ns_set_buffer(void *ubuf, int size)
{
    return -1;
}
*/


/*
 ************************************
 * network_procedure:
 *     Dialog.
 */
 
// Dialog with this module.

unsigned long 
network_procedure ( 
    struct window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    struct process_d *__process;

	//printf ("network_procedure:\n");
	
	//
	// #todo
	//
	
	//Testar a validade dos ponteiros.

    __process = (struct process_d *) processList[current_process];

    if ( (void *) __process == NULL )
        return 0;

    
    switch (msg)
    {

        // 1000 - Notification ?
        // O processo em ring3 envia a stream para mensagens de texto.
        // Nesse momento vamos habilitar a notificação de processos.
        // IN: long1 tem o descritor na lista de arquivos 
        // abertos do processo.
        case 1000:
            notification_status = 1;
            if ( notification_status != 1 ){ break; }
 
            // #todo:
            // Pra que esse arquivo vai ser usado mesmo ?
            ____network_file = (file *) __process->Objects[long1];
              
            if ( (void *) ____network_file == NULL ){ 
                printf ("network_procedure: ____network_file fail\n"); 
                refresh_screen();
                break; 
            }
            // Mensagem.
           __process->control->window  = NULL;
           __process->control->msg     = (int) MSG_AF_INET;    //Temos uma mensagem. 
           __process->control->long1   = (unsigned long) 0;
           __process->control->long2   = (unsigned long) 0;
           __process->control->newmessageFlag = 1;

            // pty_send_message_to_thread ( (unsigned long) msg_buffer, (int) t->tid );  
            //network_status = ; //apto a
            break;

        //>long1 tem o descritor na lista de arquivos abertos do processo.
        case 2000:
            notification_status = 1;
            if ( notification_status != 1 ){ break; }
            
            ____network_file = (file *) __process->Objects[long1]; 
            if ( (void *) ____network_file == NULL ){ 
                printf ("network_procedure: ____network_file fail\n"); 
                refresh_screen();
                break;   
            }

            k_ftell (____network_file);
            sprintf( (char *) ____network_file->_base, "Hello friend!\n");
            //memcpy ( (void *), (const void *), (size_t) );

           __process->control->window = NULL;
           __process->control->msg = (int) MSG_NET_DATA_IN;  //temos uma mensagem. 
           __process->control->long1 = (unsigned long) long1;  
           __process->control->long2 = (unsigned long) long2;  
           __process->control->newmessageFlag = 1;
           break;

		//send ARP packet
		//O processo controi um pacote e envia o buffer em long1.
		//copiamos o conte�do do buffer par ao buffer usado pelo driver.    
		//case 2001:
		    //break;
		    
		//send UDP/IP packet
		//O processo controi um pacote e envia o buffer em long1.
		//copiamos o conte�do do buffer par ao buffer usado pelo driver.    
		//case 2001:
		    //break;

		//send TCP/IP packet
		//O processo controi um pacote e envia o buffer em long1.
		//copiamos o conte�do do buffer par ao buffer usado pelo driver.    
		//case 2001:
		    //break;
		    
		//notificando o processo atual de que recebemos um ipv4
		////notificando ...(ok funcionou.)
		//reaproveitando um soquete se a conec��o est� estabelecida.
        case 3000:
            if ( notification_status != 1 ){ break; }

            ____network_file = (file *) __process->Objects[long1]; 
            if ( (void *) ____network_file == NULL ){ 
                printf ("network_procedure: ____network_file fail\n"); 
                refresh_screen();
                break;   
            }

            k_ftell (____network_file); 
            //rewind(____network_file); 

            sprintf( (char *) ____network_file->_base, 
                "Hello process. We've got your ipv4 packet!\n");
            //memcpy ( (void *), (const void *), (size_t) );
            __process->control->window = NULL;
            __process->control->msg = (int) MSG_NETWORK_NOTIFY_PROCESS;   
            __process->control->long1 = (unsigned long) long1; 
            __process->control->long2 = (unsigned long) long2; 
            __process->control->newmessageFlag = 1;
            break;

   
		//#todo    
		// notificando o app em ring3 que ele tem dados em 
		// seu buffer previamente configurado por ele.
		// MSG_ = 1444
        case 4000:
            break;

        //...
    } 


	//printf ("network_procedure: done\n");
	//refresh_screen();
    return (unsigned long ) 0;
}




void networkSetstatus (int status){

    if ( status < 0 || status > 1 )
        return;

    network_status = (int) status;
}


int networkGetStatus (void)
{
    return (int) network_status;
}


/*
 **********************************************************
 * networkInit:
 *     It only initializes the some network structures. Not the 
 * adapters.
 */ 

int networkInit (void){


    debug_print ("networkInit:\n");
    
    // #importante
    // Essa é a flag que indica que a última inicialização foi feita.
    // Aquela chamada por processos inicializadores em ring3.
    // Com essa flag acionada o handler do nic poderá
    // decodificar o buffer, caso contrário deve ignorar.
    ____network_late_flag=0;
    
    
    //
    // buffers
    //
    void *nbuffer;
    int i=0;
    
    //receive buffers,
    for(i=0;i<32;i++)
    {
        nbuffer = (void*) newPage();
        if((void *)nbuffer == NULL)
            panic("networkInit: receive nbuffer");
    
        NETWORK_BUFFER.receive_buffer[i] = (unsigned long) nbuffer;
    }
    NETWORK_BUFFER.receive_tail =0;
    NETWORK_BUFFER.receive_head =0;
    

    //send buffers,
    for(i=0;i<8;i++)
    {
        nbuffer = (void*) newPage();
        if((void *)nbuffer == NULL)
            panic("networkInit: send nbuffer");
    
        NETWORK_BUFFER.send_buffer[i] = (unsigned long) nbuffer;
    }
    NETWORK_BUFFER.send_tail =0;
    NETWORK_BUFFER.send_head =0;


    // Status.
    networkSetstatus (0);


	// Host info struct. 
	// See: host.h

    HostInfo = (struct host_info_d *) kmalloc ( sizeof( struct host_info_d ) ); 

    if ( (void *) HostInfo == NULL ){
        panic ("networkInit: HostInfo");

    }else{

        // #todo object header

        HostInfo->used = 1;
        HostInfo->magic = 1234;

        //HostInfo->__hostname =
        HostInfo->hostName_len = (size_t) HOSTNAME_BUFFER_SIZE;

        HostInfo->hostVersion = NULL;

        HostInfo->hostVersionMajor = 0;
        HostInfo->hostVersionMinor = 0; 
        HostInfo->hostVersionRevision = 0;
        HostInfo->hostArchitecture = 0; 

        // ...
    };


	// Criando socket para local host porta 80;
	// Localhost (127.0.0.1):80 
	// Configurando soquete atual.

    LocalHostHTTPSocket = (struct socket_d *) create_socket (0,0);  

    //if ( (void *) LocalHostHTTPSocket == NULL )
        //return -1;


    CurrentSocket = (struct socket_d *) LocalHostHTTPSocket;

	// ...


    socket_init();


	// Status
    networkSetstatus (1);


    debug_print ("networkInit: done\n");
    
    return 0;
}




// #todo:
// Debug routine.
// It just shows some network info.

void show_network_info (void){

    printf ("show_network_info:\n");

    if ( network_status == 1 )
        printf ("Network initialized\n");


    if ( network_status == 0 )
        printf ("Network uninitialized\n");


    if ( (void *) HostInfo == NULL ){
        printf ("show_network_info: HostInfo");
        return;

    }else{

        // #todo: 
        printf ("IP %s ", HostInfo->hostIP );
        printf ("MAC %s\n", HostInfo->hostMAC );
        //...
    };


    // nic
    show_current_nic_info ();
}



/*
 ********************************************
 * show_current_nic_info:
 *     nic info
 */

void show_current_nic_info (void){

    printf ("show_current_nic_info:\n");

    // #bugbug
    // Essa estrutura est� falhando.

    if ( (void *) currentNIC ==  NULL ){
        printf ("show_current_nic_info: struct fail\n");
        return;

    }else{

        if ( currentNIC->used != 1 || currentNIC->magic != 1234 ){
            printf ("show_current_nic_info: validation fail\n");
            return;
        }

        if ( (void *) currentNIC->pci == NULL ){
            printf ("show_current_nic_info: pci struct fail\n");
            return;
        }

        // messages 
        printf ("NIC device info:\n");
        printf ("Vendor %x Device %x \n", 
            currentNIC->pci->Vendor, currentNIC->pci->Device );


        // BARs
        printf ("BAR0 %x\n", currentNIC->pci->BAR0 );
        printf ("BAR1 %x\n", currentNIC->pci->BAR1 );
        printf ("BAR2 %x\n", currentNIC->pci->BAR2 );
        printf ("BAR3 %x\n", currentNIC->pci->BAR3 );
        printf ("BAR4 %x\n", currentNIC->pci->BAR4 );
        printf ("BAR5 %x\n \n", currentNIC->pci->BAR5 );

		//
		// ## Device status ##
		//

		// Device status.
		// To test your mapping, try printing out the device status register 
		// (section 13.4.2). This is a 4 byte register that starts at byte 8 
		// of the register space. You should get 0x80080783, which indicates 
		// a full duplex link is up at 1000 MB/s, among other things.


        printf ("Device status %x \n", currentNIC->DeviceStatus );

        // Full duplex.0=half,1=full 
        if (currentNIC->DeviceStatus & 1){
            printf ("Full duplex \n");
        }

        // Link up.0=no,1=link 
        if (currentNIC->DeviceStatus & 2){
            printf ("link up \n");
        }

        // transmission paused
        if (currentNIC->DeviceStatus & 0x10){
            printf ("transmission paused\n");
        }

        // TBI mode 
        if (currentNIC->DeviceStatus & 0x20){
            printf ("TBI mode\n");
        }

        // Speed 1000Mb/s 
        if (currentNIC->DeviceStatus & 0x80){
            //currentNIC->speed #todo
            printf ("1000Mbs\n");
        }

        // MAC
        printf ("MAC %x %x %x %x %x %x \n", 
            currentNIC->mac_address[0], currentNIC->mac_address[1], 
            currentNIC->mac_address[2], currentNIC->mac_address[3], 
            currentNIC->mac_address[4], currentNIC->mac_address[5] );

        // IP
        printf ("IP %d %d %d %d \n", 
            currentNIC->ip_address[0], currentNIC->ip_address[1], 
            currentNIC->ip_address[2], currentNIC->ip_address[3] );

        // irq, shared INTA#
        printf ("int_line={%d} int_pin={%d}\n",
            currentNIC->pci->irq_line, currentNIC->pci->irq_pin ); 

        printf ("interrupt_count={%d}\n", currentNIC->interrupt_count );

        // ...

    };

	// ?? precisamos do refresh ?
	//refresh_screen ();
}


/*
 *********************************************
 * handle_ipv6:
 *     Manipular o pacote ipv6 recebido pelo handle do e1000. 
 * Ou por qualquer outro adaptador.
 */

//#todo
//ipv6 needs to have its own document.

int handle_ipv6 ( struct ipv6_header_d *header ){

    //debug_print ("handle_ipv6: Initializing ...\n");
    //printf("handle_ipv6: Initializing ...\n");

    if ( (void *) header == NULL ){
        printf ("handle_ipv6: header fail\n");
        return -1;

    }else{

        //printf("ver_tc_label=%x len=%d next_header=%x hop_limit=%d \n",
        //    header->ver_tc_label,
        //    header->len,
        //    header->next_header,
        //    header->hop_limit );

		//32bit
		//printf("ver=%d ", header->ver_tc_label & 0xF0000000 );
		//printf("tc=%d ", header->ver_tc_label  & 0x0FF00000 );
		//printf("label=%d ", header->ver_tc_label  & 0x000FFFFF );
	    
		//16bit
		//printf("len=%d ", header->len  & 0xFFFF );
		
		//8bit
		//printf("next=%d ", header->next_header & 0xFF );

		//8bit
		//printf("hop_limit=%d \n", header->hop_limit & 0xFF );
		
		//...

        return 0;
    };


    return 1;
}



/*
 * Network_test:
 *     Debug routine.
 *     Called by a ring3 process.
 */

void network_test(void)
{
    debug_print("network_test: \n");
    
    // Nic info.
    debug_print("network_test: Test NIC \n");
    testNIC();

    // Network info.
    debug_print("network_test: Show info\n");
    show_network_info();

    //Done.
    debug_print("network_test: done\n");
    refresh_screen();
    
    // 
    ____network_late_flag = 1;
}



/*
 **********************************************************
 * testNIC:
 *     Testando o funcionamento das rotinas do drivers.
 *     Isso bota ele pra funcionar depois de inicializado.
 */

// # IMPORTANTE
// Chamada por F6 no procedimento de janela do sistema.
// Subrotina chamada por rotinas de teste.
// Essa rotina aciona uma flag que (DESTRAVA) o handler da interrupção.

void testNIC (void){

    debug_print ("testNIC:\n");

    printf ("\n\n ==== TEST NIC ==== \n\n"); 

    //
    // Flag. (UNLOCK)
    //

    printf ("testNIC: Unlock interrupt handler \n");
    e1000_interrupt_flag = 1;

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
    target_ip_address[3] = 105;//111; 

    // MAC for broadcast.
    // 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF.
    uint8_t target_mac_address[6];
    target_mac_address[0] = 0xFF;
    target_mac_address[1] = 0xFF;
    target_mac_address[2] = 0xFF;
    target_mac_address[3] = 0xFF;
    target_mac_address[4] = 0xFF;
    target_mac_address[5] = 0xFF;

    //
    // #test
    //
    
	// Mudar network.
	// Tem que ter uma abstração que selecione o nic atual

    printf ("testNIC: Sending arp request \n");
    SendARP ( ARP_OPC_REQUEST, 
        source_ip_address, target_ip_address, 
        target_mac_address );


	//==============================================
	// ## data ##
	//

    char xxxdata[32];
    xxxdata[0] = 1;
    xxxdata[1] = 2;
    xxxdata[2] = 3;
    xxxdata[3] = 4;


	// #todo: 
	// testar isso;

    printf ("testNIC: Sending IPV4 \n");
    network_SendIPV4_UDP ( source_ip_address, target_ip_address, 
        target_mac_address, xxxdata, 20 );


	// Se tivermos informações para mostrar 
	// é sinal que a inicialização do kernel funcionou. 

	//printf("\n\n");
	//pciInfo ();

	//printf("\n\n");
    show_current_nic_info ();

    printf ("\n\n ====TEST DONE ==== \n\n"); 

    refresh_screen ();
}



/*
 ***************************************************************
 * SendIPV4: 
 *    Criando e enviando um pacote ipv4.  (UDP)
 * 
 * IN:
 *     source_ip. (It's in the layer 3 of the OSI model. network layer)
 *     target_ip. (It's in the layer 3 of the OSI model. network layer)
 *     target_mac. (It's in the layer 2 of the OSI model. data link layer)
 *     data. (The data we want to send via ipv4. 32 bytes)
 */

// #todo
// udp needs to have its own document.

// #todo
// Change the return type to 'int'. 

// #obs:
// UDP/IP
// UDP = 0x11 (ip protocol)

int
network_SendIPV4_UDP ( 
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6], 
    uint8_t data[32],
    unsigned short port )
{
    int i=0;
    int j=0;


    // ethernet, ipv4, udp.
    struct ether_header   *eh;
    struct ipv4_header_d  *ipv4;
    struct udp_header_d   *udp;


	//
	// NIC Intel device structure.
	//

    if ( (void *) currentNIC == NULL ){
        debug_print ("network_SendIPV4_UDP: currentNIC fail\n");
        //printf ("network_SendIPV4_UDP: currentNIC fail\n");
        return (int) (-1);

    }else{

        // Configurando a estrutura do dispositivo.
        // 192.168.1.112
        currentNIC->ip_address[0] = source_ip[0];  //192;
        currentNIC->ip_address[1] = source_ip[1];  //168;
        currentNIC->ip_address[2] = source_ip[2];  //1;
        currentNIC->ip_address[3] = source_ip[3];  //112;
        //...
    };



	//==============================================
	// # ethernet header #
	//

    eh = (void *) kmalloc ( sizeof(struct ether_header ) );

    if ( (void *) eh == NULL){
        debug_print ("network_SendIPV4_UDP: eh fail");
        //printf ("network_SendIPV4_UDP: eh fail");
        return (int) (-1);

    }else{

		// Coloca na estrutura do ethernet header os seguintes valores: 
		// > endereço mac da origem.
		// > endereço mac do destion.
		// O endereço mac da origem está na estrutura do controlador nic intel. 
		// O endereço mac do destino foi passado via argumento.

        for ( i=0; i<6; i++ ){
            eh->src[i] = currentNIC->mac_address[i];    // source 
            eh->dst[i] = target_mac[i];                 // dest. 
        };

        eh->type = (uint16_t) ToNetByteOrder16 (ETH_TYPE_ARP);

		// ...
    };


	//==============================================
	// # ipv4 header #
	//

    ipv4 = (void *) kmalloc ( sizeof(struct ipv4_header_d) );

    if ( (void *) ipv4 == NULL){
        debug_print ("network_SendIPV4_UDP: ipv4 fail\n");
        //printf ("network_SendIPV4_UDP: ipv4 fail\n");
        return (int) (-1);

    }else{

        // IPv4 common header
        // See: ip.h
        
        //>>>>
        ipv4->Version_IHL = 0x45;     // 8 bit
        ipv4->DSCP_ECN    = 0x00;     // 8 bit
        //ipv4->TotalLength           // 16 bit   
        ipv4->Identification = 0x0100;  // 16 bit 
        
        //>>>>
		// #importante
		// Existem v�rios protocolos para ip.
		// TCP=0x6 UDP=0x11
		//default protocol: UDP
		//#define IPV4_PROT_UDP 0x11
        ipv4->Flags_FragmentOffset = 0x0000;  //8 bit
        ipv4->TimeToLive = 0x40;              //8bit
        ipv4->Protocol = 0x11;    //IPV4_PROT_UDP;  // 8bit
        //ipv4->HeaderChecksum                      // 16bit


        //>>>>
        memcpy ( (void *) &ipv4->SourceIPAddress[0], 
            (const void *) &source_ip[0], 4 );

        //>>>>
        memcpy ( (void *) &ipv4->DestinationIPAddress[0], 
            (const void *) &target_ip[0], 4 );
    };



	//==============================================
	// # udp header #
	//

    udp = (void *) kmalloc ( sizeof(struct udp_header_d) );

    if ( (void *) udp == NULL){
        printf ("network_SendIPV4_UDP: udp fail\n");
        return -1;

    }else{
		
		//
		// UDP ports;
		//
    
        // #todo
        // Essas portas podem ser passadas via argumento.
        // A porta de origem representa o processo cliente
        // A porta de destino representa o processo servidor.
        // Se o argumento passado for a estrutura (channel)
        // ent�o teremos muita informa��o.
 
        //20 FTP-DATA File Transfer [Default Data]
        //21 FTP File Transfer [Control]
        //23 TELNET Telnet
        //25 SMTP Simple Mail Transfer
        //37 TIME Time
        //69 TFTP Trivial File Transfer
        //79 FINGER Finger
        //110 POP3 Post Office Protocol v 3
        //123 NTP Network Time Protocol
        //143 IMAP2 Interim Mail Access Prot. v2
        //161 SNMP Simple Network Man. Prot.

    
        udp->SourcePort = 20;       //FTP-DATA File Transfer
        udp->DestinationPort = 20;  //FTP-DATA File Transfer
        //This field specifies the length in bytes of the UDP header and UDP data. 
        //The minimum length is 8 bytes, the length of the header. 
        udp->Length = (UDP_HEADER_LENGHT + 32); 
        udp->Checksum = 0; //#todo
    };


	//
	// ===== # BUFFER # =====
	//


	// ??
	// Quem?
	// Estamos pegando o offset que nos levar� ao endere�o do buffer.
	// Usaremos esse offset logo abaixo.
	// Pegamos esse offset na estrutura do controlador nic intel.

    uint16_t old = currentNIC->tx_cur;


	//
	// Copiando o pacote no buffer.
	//

	// Pegando o endere�o virtual do buffer na estrutura do controlador 
	// nic intel. Para isso usamos o offset obtido logo acima.

    unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];

	// #importante:
	// Preparando ponteiros para manipularmos as 
	// estruturas usadas no pacote.

    unsigned char *src_ethernet = (unsigned char *) eh; 
    unsigned char *src_ipv4     = (unsigned char *) ipv4; 
    unsigned char *src_udp      = (unsigned char *) udp; 


	//
	// Copy.
	//

	// Copiando as estruturas para o buffer.
	// >Step1) Copiando o header ethernet.
	// >Step2) Copiando o heder ipv4.
	// >Step3) Copiando o header udp.
	// >Step4) Copiando os dados.

	//Step1
	//copia o header ethernet
	
    for ( j=0; j<ETHERNET_HEADER_LENGHT; j++ )
    {
        buffer[j] = src_ethernet[j];
    };

	//Step2
	//copia o ipv4

    for ( j=0; j<IPV4_HEADER_LENGHT; j++ )
    {
        buffer[j + ETHERNET_HEADER_LENGHT] = src_ipv4[j];
    };

	//Step3
	//copia o udp
    for ( j=0; j<UDP_HEADER_LENGHT; j++ )
    {
        buffer[j + ETHERNET_HEADER_LENGHT +IPV4_HEADER_LENGHT] = src_udp[j];
    };

	//Step4
	//copia o xxxdata
    for ( j=0; j<32; j++ )
    {
        buffer[j + ETHERNET_HEADER_LENGHT + IPV4_HEADER_LENGHT + UDP_HEADER_LENGHT] = data[j];
    };



	// lenght:
	// Vamos configurar na estrutura do nic intel o tamanho do pacote.
	// Lenght de um pacote ipv4.
	// ethernet header, ipv4 header, udp header, data.

    currentNIC->legacy_tx_descs[old].length = ( ETHERNET_HEADER_LENGHT + 
                                                IPV4_HEADER_LENGHT + 
                                                UDP_HEADER_LENGHT + 
                                                32 );

	//cmd
    currentNIC->legacy_tx_descs[old].cmd = 0x1B;

	//status
    currentNIC->legacy_tx_descs[old].status = 0;

	// Current TX.
	// Qual � o buffer atual para transmiss�o.
    currentNIC->tx_cur = ( currentNIC->tx_cur + 1 ) % 8;



	//
	// ==== # SEND # ======
	//


	// #importante: 
	// Diga ao controlador qual � o �ndice do descritor a ser usado para  
	// transmitir dados.
	// TDH	= 0x3810,    /* Tx Descriptor Head */
	// TDT	= 0x3818,    /* Tx Descriptor Tail */

	// *( (volatile unsigned int *)(currentNIC->mem_base + 0x3810)) = 0;
    *( (volatile unsigned int *)(currentNIC->mem_base + 0x3818)) = currentNIC->tx_cur;



	// #debug
	// Colocamos essa mensagem antes de entrarmos no while.
	// Pois precisamos implementar algum contador no while para n�o
	// ficarmos preso nele pra sempre.

    printf ("network_SendIPV4_UDP: Sending UDP/IP. *debug *while\n");
    refresh_screen ();

	// #perigo:
	// Status.
	// Checamos o status do buffer old pra ver se ele foi enviado.
	// Fica travado aqui at� que seja enviado?
	// Poderia ter um timemout?.
	

    int t;
    for (t=0; t< 25000;t++)
    {
         if ( (currentNIC->legacy_tx_descs[old].status & 0xFF) == 1 )
         {
              printf ("Ok");
              debug_print ("network_SendIPV4_UDP: done\n");
              return 0;
         }
    }

    //#todo
    /*
    while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
    {
        // Nothing.
    };
    */    

    printf (">>>> fail timeout\n");
    debug_print ("network_SendIPV4_UDP: timeout\n");
    debug_print ("network_SendIPV4_UDP: done\n");
    
    return 0;
}


/*
 ***************************************************************
 * SendARP:
 *     It sends a ARP packet.
 * 
 * IN: 
 *     op =  operation. request or reply
 *     source_ip. (It's in the layer 3 of the OSI model. network layer)
 *     target_ip. (It's in the layer 3 of the OSI model. network layer)
 *     target_mac. (It's in the layer 2 of the OSI model. data link layer)
 */

// #todo
// arp needs to have its own document.

// #todo
// Change the return type to 'int'. 

void 
SendARP ( int op,   //operation
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6] )
{

    struct ether_header *eh;
    struct ether_arp *h;
    int i=0;


    debug_print ("SendARP:\n");


    // nic device structure.

    if ( currentNIC == NULL ){
        printf ("SendARP: currentNIC fail\n");
        return;

    }else{

		// Source IP.
		// Configurando a estrutura do dispositivo.
		
		// #bugbug
		// Estamos configurando a estrutura do dispositivo
		// Esse não é o momento de fazermos isso.
		
        // 192.168.1.112
        currentNIC->ip_address[0] = source_ip[0];  //192;
        currentNIC->ip_address[1] = source_ip[1];  //168;
        currentNIC->ip_address[2] = source_ip[2];  //1;
        currentNIC->ip_address[3] = source_ip[3];  //112;

		//...
    };



	//==============================================
	// # ethernet header #
	//

    eh = (void *) kmalloc ( sizeof(struct ether_header ) );

    if ( (void *) eh == NULL){
        printf ("SendARP: eh struct fail\n");
        return;
 
    }else{

		// Coloca na estrutura do ethernet header os seguintes valores: 
		// > endere�o mac da origem.
		// > endere�o mac do destion.
		// O endere�o mac da origem est� na estrutura do controlador nic intel. 
		// O endere�o mac do destino foi passado via argumento.

        for( i=0; i<6; i++)
        {
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
        if (op != ARP_OPC_REQUEST && op != ARP_OPC_REPLY )
        {
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
	// ===== # BUFFER # =====
	//


	// ??
	// Quem?
	// Estamos pegando o offset que nos levar� ao endere�o do buffer.
	// Usaremos esse offset logo abaixo.
	// Pegamos esse offset na estrutura do controlador nic intel.

    uint16_t old = currentNIC->tx_cur;

	//
	// Copiando o pacote no buffer.
	//

	// Pegando o endere�o virtual do buffer na estrutura do controlador 
	// nic intel. Para isso usamos o offset obtido logo acima.

    unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];

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

    currentNIC->legacy_tx_descs[old].length = ( ETHERNET_HEADER_LENGHT + 
                                                ARP_HEADER_LENGHT );


	//??
	//cso
	//currentNIC->legacy_tx_descs[0].cso


	//??
	//cmd ok
	//currentNIC->legacy_tx_descs[0].cmd = TDESC_CMD_IFCS | TDESC_CMD_RS | TDESC_CMD_EOP;
	//currentNIC->legacy_tx_descs[0].cmd = TDESC_EOP | TDESC_RS; //intel code

	//cmd
    currentNIC->legacy_tx_descs[old].cmd = 0x1B;

	//status
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

    debug_print ("SendARP: Sending broadcast ARP. *debug *while\n");
    //printf ("SendARP: Sending broadcast ARP. *debug *while\n");
    //refresh_screen ();

	// #perigo:
	// Status.
	// Checamos o status do buffer old pra ver se ele foi enviado.
	// Fica travado aqui at� que seja enviado?
	// Poderia ter um timemout?.


    int t;
    for (t=0; t< 25000;t++)
    {
         if ( (currentNIC->legacy_tx_descs[old].status & 0xFF) == 1 )
         {
              debug_print ("SendARP: done [timeout]\n");
              //printf ("Ok");
              return;
         }
    }
    
    //#todo
    /*
    while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
    {
        // Nothing.
    };
    */
    

    debug_print ("SendARP: fail timeout.\n");    
    debug_print ("SendARP: done\n");
    
    //printf (">>>> fail timeout.\n");
}




/*
 **************************
 * network_driver_dialog: 
 *     Dialog for the network driver.
 */

// Essa rotina é chamada depois que o handler obtem 
// o endereço do buffer.

// IN:
// window = NULL.
// msg    = msg.
// long1  = buffer address.
// long1  = buffer address.

unsigned long 
network_driver_dialog ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ) 
{

	// #debug
    debug_print ("network_driver_dialog:\n");
    //printf ("network_driver_dialog:\n");


	// Vamos tratar as mensagens recebidas. Entre elas:
	// MSG_BUFFERFULL  - (O buffer est� cheio)
	//  x     -  Inicializar o servidor de rede.
	//  x     -  Finalizar o servidor de rede.
	//...


	//Structs.
    //isso deve ir para a rotina certa.
    //struct ipv6_header_d *ipv6_h;
    //struct ether_header *eh;
    //struct ether_arp *arp_h;
    //int i;


    switch (msg)
    {
        //case 0:
            //return 1;
            //break;

        // >>>> buffer full.
        // 
        case 8000:
            debug_print ("network_driver_dialog: 8000. buffer full\n");
            //printf ("buffer=%x\n", long1);
            // IN: buffer address.
            return (unsigned long) network_decode_buffer ( (unsigned long) long1 );
            break;

        //inicializar 
        case 8001:
            return 1;
            break;

        //finalizar
        case 8002:
            return 1;
            break;

        //send.
        //enviar um pacote que esta num buffer indicado em long1.
        //esse buffer pode ter sido enviado por algum processo ou biblioteca.
        //case 8003:
           // break;
           
           
        //#todo
        //enviar o buffer para o gns.   
        case 9000:
            return -1;
            break;


        default:
            return 1;
            break;
    };

    return 1;
}



/*
 *********************************************
 * network_decode_buffer:
 *     Decode the buffer and call routines for each protocol.
 */

// Essa rotina é chamada por network_driver_dialog
// para decodificar o que tem dentro do buffer.
// Ela deve chamar as rotinas de protocolo apropriadas.

 
// O que tem no buffer?
// Decodificando o protocolo encontrado no buffer.

// #importante:
// Vamos sondar o ethernet header para percebermos o tipo
// e redirecionarmos para a rotina apropriada.


int network_decode_buffer ( unsigned long buffer_address ){

    // Only the ethernet header.
    struct ether_header *eh;


    //#debug
    debug_print ("network_decode_buffer:\n");
    //printf ("network_decode_buffer:\n");


    if ( buffer_address == 0 ){
        printf ("network_decode_buffer: buffer\n");
        return 1;
    }
    
	//
	// ## eth header ##
	//
	
	//ethernet header
	//eh = (void *) &buffer[0];
    eh = (void *) buffer_address;

    if ( (void *) eh == NULL ){
        printf ("network_decode_buffer: eh\n");
        refresh_screen();
        return 1;

    }else{

        //printf("src: ");
        //for( i=0; i<6; i++)
        //	printf("%x ",eh->src[i]);

        //printf("dst: ");
        //for( i=0; i<6; i++)
        //	printf("%x ",eh->dst[i]);

        //printf("type={%x} ",eh->type);
    };


    // #importante
    // Provavelmente o buffer seja enviado para um
    // servidor de protocolos.
    // Um servidor só para todos os protocolos.
    // See: https://en.wikipedia.org/wiki/EtherType

    uint16_t type = FromNetByteOrder16(eh->type);
    
    switch ( (uint16_t) type)
    {


        // ::: IPV4
        // 0x0800	Internet Protocol version 4 (IPv4)
        // Ok como test vamos notificar o processo atual
        // de que recebemos um pacote ipv4
        case 0x0800:
        
           // #debug
            //printf ("IPV4 received\n");
            //refresh_screen ();
           
           //#test
           //notificando ...(ok funcionou.)
           network_procedure ( NULL, 3000, 0,0 ); 
           
           // #debug
           //printf("todo: Internet Protocol version 4 (IPv4)\n");
           //printf("IPv4 ");
           do_ipv4 ( (unsigned long) buffer_address );
           //refresh_screen ();
           return 0;
           break;

        //::: ARP
        //0x0806	Address Resolution Protocol (ARP)
        //#todo: devemos chamar uma rotina para tratamento de ARP e n�o
        //fazermos tudo aqui. kkk.
        case 0x0806:
            // #debug
            //printf ("ARP received\n");
            //refresh_screen ();
                   
            //printf("\nARP ");
            do_arp ((unsigned long) buffer_address );
            //refresh_screen ();
            return 0;
            break;
            
        //::: SNMP
        // Simple Network Management Protocol.
        case 0x814C:
            return 0;
            break;
            
        
            
        //::: IPV6
        //0x86DD	Internet Protocol Version 6 (IPv6)
        case 0x86DD:

            // #debug
            //printf ("IPV6 received\n");
            //refresh_screen ();
        
            //printf ("IPv6 ");
            do_ipv6 ( (unsigned long) buffer_address );
            //refresh_screen ();
            return 0;
            break;

        //:::PPP
        //Point-to-Point Protocol.
        case 0x880B:
            return 0;
            break;

        //0x8863	PPPoE, PPP Over Ethernet (Discovery Stage).
        //0x8864	PPPoE, PPP Over Ethernet (PPP Session Stage).

		//::: DEFAULT
        // Error: Default package type.
        default:

            // #debug
            //printf ("UNKNOWN received\n");
            //refresh_screen ();

            // #debug
            //printf("default ethernet type\n");
            //refresh_screen();
            return 0;
            break;

    }

    return 1;
}



// Decodificando um pacote ipv4.
// Precisamos olhar no pacote para sabermos qual � a porta
// para assim reenviarmos o pacote ao processo conectado a essa porta.
// #todo:
// Podemos alertar o gns.

int do_ipv4 ( unsigned long buffer )
{
    debug_print ("do_ipv4: [TODO]\n");
    printf("IPv4 \n");  
    refresh_screen();


    /*
    //#todo
    //Criar uma mensagem que o ns entenda.
    int msg_status = (int) ipc_send_to_ws ( (struct window_d *) 0, //null
                           (int) 1111, 
                           (unsigned long) 0,
                           (unsigned long) 0);
        
    // Se a mensagem foi enviada para o ws,
    // então podemos retornar.
    if ( msg_status == 0 ){
        debug_print ("do_ipv4: >>>> to ns\n");        
        return 0;
    }
    */

    return 0;
}


// Decodificando um pacote ipv6.
int do_ipv6 ( unsigned long buffer )
{
    debug_print ("do_ipv6: [TODO]\n");
    
    //printf ("do_ipv6\n");
    //printf("IPv6 \n");
    //ipv6_h = (void *) &buffer[14];

    //handle_ipv6 ( (struct intel_nic_info_d *) currentNIC, 
    //  (struct ipv6_header_d *) ipv6_h );

    /*
    //#todo
    //Criar uma mensagem que o ns entenda.
    int msg_status = (int) ipc_send_to_ws ( (struct window_d *) 0, //null
                           (int) 1111, 
                           (unsigned long) 0,
                           (unsigned long) 0);
        
    // Se a mensagem foi enviada para o ws,
    // então podemos retornar.
    if ( msg_status == 0 ){
        debug_print ("do_ipv4: >>>> to ns\n");        
        return 0;
    }
    */

    return 0;
}



/*
 ********************
 * do_arp:
 * 
 */
 
// Decodifica um pacote ARP.
// See:
// https://en.wikipedia.org/wiki/Address_Resolution_Protocol

int do_arp ( unsigned long buffer ){

    struct ether_header  *eh;
    struct ether_arp     *ah;
    
    int i=0;


    // #debug
    // printf ("do_arp: \n");
    debug_print ("do_arp: \n");
        
    eh = (struct ether_header *) (buffer + 0);
    ah = (struct ether_arp *)    (buffer + 14);
    
   
    // printf ("todo: Address Resolution Protocol (ARP) ");
  
    if ((void *) ah == NULL){
        debug_print ("do_arp: arp header struct\n");
        //printf()
        return 1;
    }
    
    
    //
    // Operation:
    // ARP_OPC_REPLY or ARP_OPC_REQUEST
    //

    if ( ah->op == ToNetByteOrder16(ARP_OPC_REPLY) ){
        goto __reply_received;
    }
    
    if ( ah->op == ToNetByteOrder16(ARP_OPC_REQUEST) ){
        goto __request_received;
    }

    // Fail:
    debug_print ("do_arp: Not valid operation\n");
    printf ("do_arp: Not valid operation\n");
    return -1;

//
// Reply received.
//

__reply_received:

    // Recebemos um reply.
    // Não faremos nada por enquanto.
    // Mas provavelmente nesse momento recebemos
    // alguma informação que solicitamos, como o MAC de um dispositivo.
    
    //#debug
    //printf ("\n ARP REPLY received \n");
    //refresh_screen();
        
    //#debug
    //printf("REPLY received\n");
    //printf("src: ");
    //for( i=0; i<4; i++)
    //    printf("%x ",arp_h->arp_spa[i]);
    //refresh_screen();

    return -1;
    

//
// Request received.
//

__request_received:

    // Recebemos um request.
    // Vamos responter.

    // #debug
    //printf ("\n ARP REQUEST received \n");
    //refresh_screen();

    //#debug
    
    /*
    printf ("\n ARP REQUEST received | ");
    for ( i=0; i<6; i++){ printf("%x ",eh->src[i]); };

    printf (" | ");
    for ( i=0; i<6; i++){ printf("%x ",eh->dst[i]); };

    printf (" | ");
    for ( i=0; i<4; i++){ printf("%d ",ah->arp_spa[i]); };

    printf (" | ");
    for ( i=0; i<4; i++){ printf("%d ",ah->arp_tpa[i]); };

    refresh_screen();
    */

	//cache
	//cada controlador tem seu cache.


    for ( i=0; i<32; i++ )
    {
        // livre.
        if ( currentNIC->arp_cache[i].used == 1 && 
             currentNIC->arp_cache[i].magic == 1234 )
        {

            // compara o ip
            if ( strncmp ( (char *) &currentNIC->arp_cache[i].ipv4_address[0], 
                               (char *) &ah->arp_spa[0], 
                                 4 ) == 0 )
            {
                memcpy ( (void *) &currentNIC->arp_cache[i].mac_address[0], 
                    (const void *) &eh->src[0], 
                     6 );

                // Sinaliza que está em uso.
                currentNIC->arp_cache[i].magic = 4321;
            }
        }
    };
    
    
    //#test
    //Tentando enviar um reply desse jeito.

    debug_print ("do_arp: Sending arp replay \n");
    //printf ("do_arp: Sending arp replay \n");
    //refresh_screen();
    SendARP ( ARP_OPC_REPLY, 
        &eh->dst[0],          //source_ip_address 
        &eh->src[0],          //target_ip_address
        &ah->arp_spa[0] );    //target_mac_address 


    /*
    // old way - (backup)
    // ??
    // vamos responder.
    // Pra isso precisamos saber o tamanho do buffer.
    // vamos rever isso pois n�o podemos mais consultar o controlador 
    // por enquanto.
         
    uint16_t arp_tx_old = currentNIC->tx_cur;
    uint32_t arp_tx_len = currentNIC->legacy_tx_descs[arp_tx_old].length;

    // Muda para REPLAY.
    ah->op = ToNetByteOrder16(ARP_OPC_REPLY);

    // Reenvia os mesmos dados, mas modificados para replay.
    // essa rotina vai copiar de um buffer para outro.
    
    //printf ("\n Sending ARP reply ...\n");
    //refresh_screen();


    // Send.
    
    E1000Send ( (void *) currentNIC, 
        (uint32_t) arp_tx_len, (uint8_t *) buffer );

    */


    //printf ("\n");
    //refresh_screen ();
    return 0;
}


/*
// ring3 oferece o buffer
// colocamos os valores.
int gethost ( char *name, int *ip );
int gethost ( char *name, int *ip )
{
    return -1;
}
*/



//
// End
//


