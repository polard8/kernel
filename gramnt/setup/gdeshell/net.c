/*
 * File: net.c 
 *     Network support for gdeshell.
 */


#include "shell.h"


// (ETHERNET + ARP)
uint8_t test_packet[] = 
{
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  /* eth dest (broadcast) */
    0x52, 0x54, 0x00, 0x12, 0x34, 0x56,  /* eth source  ??? o nic sabe*/
    0x08, 0x06,                          /* eth type */
    0x00, 0x01,  /* ARP htype */
    0x08, 0x00,  /* ARP ptype */
    0x06,        /* ARP hlen */
    0x04,        /* ARP plen */
    0x00, 0x01,  /* ARP opcode: ARP_REQUEST */
    0x52, 0x54, 0x00, 0x12, 0x34, 0x56,  /* ARP hsrc */
    192, 189, 1, 112,                    /* ARP psrc  gramado */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* ARP hdst */
    192, 168, 1, 100,                    /* ARP pdst alguem */
};



// Temporary. 
// We need a system function to get this number.


/*    
	uint8_t host_mac_address[6];
	host_mac_address[0] = (uint8_t) 0x12;
	host_mac_address[1] = (uint8_t) 0x32;
	host_mac_address[2] = (uint8_t) 0x12;
	host_mac_address[3] = (uint8_t) 0x32;
	host_mac_address[4] = (uint8_t) 0x12;
	host_mac_address[5] = (uint8_t) 0x32;
*/


unsigned char host_mac_address[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//u8 src_MAC[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//u8 dst_MAC[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//u8 dst_broadcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//u8 src_IP[4] = {0, 0, 0, 0};
//u8 src_SN[4] = {0, 0, 0, 0};
//u8 src_GW[4] = {0, 0, 0, 0};
//u8 dst_IP[4] = {0, 0, 0, 0};




/*
 *************************************************
 * Envia um pacote ARP.
 * IN: 
 *   source_ip.  (It's in the layer 3 of the OSI model. network layer)
 *   target_ip.  (It's in the layer 3 of the OSI model. network layer)
 *   target_mac. (It's in the layer 2 of the OSI model. data link layer)
 */


void 
__SendARP ( 
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6] )
{

    struct gdeshell_ether_header  *eh;
    struct gdeshell_ether_arp     *h;  

    int i=0;
      
    //==============================================
    // # ethernet header #
    //

    eh = (void *) malloc ( sizeof(struct gdeshell_ether_header ) );

    if ( (void *) eh == NULL)
    {
        printf ("__SendARP: [FAIL] eh struct\n");
        return;

    }else{

		// Coloca na estrutura do ethernet header os seguintes valores: 
		// > endereço mac da origem.
		// > endereço mac do destion.
		// O endereço mac da origem está na estrutura do controlador nic intel. 
		// O endereço mac do destino foi passado via argumento.

        for( i=0; i<6; i++)
        {
            //eh->src[i] = currentNIC->mac_address[i];    // source
            eh->dst[i] = target_mac[i];                 // dest. 
        };

        eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);

		//...
    };


    //==============================================
    // # arp header #
    //

    h = (void *) malloc ( sizeof(struct  gdeshell_ether_arp) );

    if ( (void *) h == NULL)
    {
        printf ("__SendARP: [FAIL] h struct");
        return;

    }else{

		// Hardware type (HTYPE)   (00 01)
		// Protocol type (PTYPE)   (08 00)
		// Hardware address length (MAC)
		// Protocol address length (IP)

        h->type  = 0x0100;
        h->proto = 0x0008;
        h->hlen  = 6;
        h->plen  = 4;


		// Operation (OPER) (dois bytes invertidos)

        //h->op = ToNetByteOrder16(ARP_OPC_REPLY);
        h->op = ToNetByteOrder16(ARP_OPC_REQUEST);

// mac
		// Configurando na estrutura de arp o endereço mac de origem e destino.
		// sender mac
		// target mac
		// O endereço mac de origem pegamos na estrutura no nic intel.
		// O endereço mac de destino foi passado via argumento.

       //#todo: pegar o mec do host.
        for ( i=0; i<6; i++ ){
            h->arp_sha[i] = host_mac_address[i];
            h->arp_tha[i] = target_mac[i]; 
        };


	// ip
		// Configurando na estrutura de arp o endereço do ip de origem e 
		// o ip de destino.
		// sender ip
		// target ip
		// Os endereços foram passados via argumento.

        for ( i=0; i<4; i++ ){
            h->arp_spa[i] = source_ip[i]; 
            h->arp_tpa[i] = target_ip[i]; 
        };

        //...
    };
  
    //==================================
    // #debug
    // show arp

    printf ("\n\n");
    printf ("[arp]\n\n");
    printf ("type={%x} proto={%x} hlen={%d} plen={%d} op={%x} \n", 
        h->type, h->proto, h->hlen, h->plen, h->op );

    printf ("\n sender: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_sha[i]); }
    printf("\n sender: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_spa[i]); }
    printf("\n target: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_tha[i]); }
    printf("\n target: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_tpa[i]); }
    printf ("\n\n");

    //==================================



    //
    // Copiando o pacote no buffer.
    //

    unsigned char *buffer;
    
    buffer = (unsigned char *) malloc(512);
    
    if ( (void*) buffer == NULL )
    {
        printf ("__SendARP: [FAIL] buffer\n");
        return;
    }


    // #importante:
    // Preparando ponteiros para manipularmos as estruturas usadas no pacote.

    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp      = (unsigned char *) h;



    //
	// Copy.
	//

	// Copiando as estruturas para o buffer.
	// >Copiando o header ethernet.
	// >Copiando o arp logo após do header ethernet.

	// ethernet, arp.
    for (i=0; i<14;i++){ buffer[i]      = src_ethernet[i]; };
    for (i=0; i<28;i++){ buffer[i + 14] = src_arp[i]; };
	
	
// lenght:
	// Vamos configurar na estrutura do nic intel o tamanho do pacote.
	// Ethernet frame length = ethernet header (MAC + MAC + ethernet type) + ethernet data (ARP header)
	// O comprimento deve ser o tamanho do header ethernet + o tamanho do header arp.
	// 14 + 28;

    //currentNIC->legacy_tx_descs[old].length = ( ETHERNET_HEADER_LENGHT + ARP_HEADER_LENGHT );


    printf ("done\n");
}



// Testing ARP.
// Sending arp.
void __shellTestARP (void){

    printf ("\n\n ==== gdeshell: __shellTestARP ==== \n\n"); 

    // Source
    uint8_t source_ip_address[4];
    source_ip_address[0] = 192;
    source_ip_address[1] = 168;
    source_ip_address[2] = 1;   
    source_ip_address[3] = 112; 

    // Target.
    uint8_t target_ip_address[4];
    target_ip_address[0] = 192;
    target_ip_address[1] = 168;
    target_ip_address[2] = 1; 
    target_ip_address[3] = 1; //111; 

    // Broadcast.
	uint8_t target_mac_address[6];
	target_mac_address[0] = 0xFF;
	target_mac_address[1] = 0xFF;
	target_mac_address[2] = 0xFF;
	target_mac_address[3] = 0xFF;
	target_mac_address[4] = 0xFF;
	target_mac_address[5] = 0xFF;


   __SendARP ( source_ip_address, 
       target_ip_address, target_mac_address );
}



void network_initialize (void)
{
    debug_print("network_initialize:\n");
    printf     ("network_initialize: Initializing the ring0 network manager...\n");
    gramado_system_call (968,0,0,0);
}




void gdeshell_send_packet( unsigned long packet_buffer )
{
    gramado_system_call( 891, 
            (unsigned long) packet_buffer,   //buf
            (unsigned long) 1500,            //len
            0);

}



void 
print_ethernet_header ( 
    const unsigned char *Buffer, 
    int Size )
{
    struct gdeshell_ether_header *eth = (struct gdeshell_ether_header *) Buffer;

    printf("\n");
    printf ("Ethernet Header\n");

    // Destination
    printf ("   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", 
        eth->dst[0] , 
        eth->dst[1] , 
        eth->dst[2] , 
        eth->dst[3] , 
        eth->dst[4] , 
        eth->dst[5] );
    
    // Source
    printf ("   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", 
        eth->src[0] , 
        eth->src[1] , 
        eth->src[2] , 
        eth->src[3] , 
        eth->src[4] , 
        eth->src[5] );
    
    // Protocol type.
    // ARP, IP ... ?
    printf ("   |-Protocol            : %u \n",
        (unsigned short)eth->type);
}


/*
 ***************** 
 * gdeshell_decode_buffer:
 *     Decode a buffer with a network packet.
 */

int 
gdeshell_decode_buffer ( unsigned long buffer_address )
{

    // The ethernet header.
    struct gdeshell_ether_header *eh;
    
    //See: net/  and netinet/
    //struct ether_header *__eth;
    //struct arphdr       *__arp; 
    //struct ip           *__ip;
    //struct tcphdr       *__tcp;
    //struct udphdr       *__udp;
    // ...


    //#debug
    debug_print ("gdeshell_decode_buffer:\n");
    //printf ("network_decode_buffer:\n");


    if ( buffer_address == 0 )
    {
        printf ("gdeshell_decode_buffer: [FAIL] null buffer address\n");
        return -1;
    }

	//
	// == Ethernet header =============================
	//

	//ethernet header
    //eh = (void *) &buffer[0];
    
    eh = (void *) buffer_address;

    if ( (void *) eh == NULL )
    {
        printf ("gdeshell_decode_buffer: [FAIL] Ethernet header\n");
        return -1;

    }else{


        //
        // Print
        //

        print_ethernet_header ( 
            (const unsigned char*) buffer_address, 1500 );

        //printf("type={%x} ",eh->type);
    };


    // #importante
    // Provavelmente o buffer seja enviado para um
    // servidor de protocolos.
    // Um servidor só para todos os protocolos.
    // See: 
    // https://en.wikipedia.org/wiki/EtherType
    // http://www.networksorcery.com/enp/protocol/802/ethertypes.htm
    // https://www.iana.org/assignments/ieee-802-numbers/ieee-802-numbers.xhtml
    // ...

    // Ethertype
    // See: https://en.wikipedia.org/wiki/EtherType
    // 0x0800 	Internet Protocol version 4 (IPv4) 
    // 0x0806 	Address Resolution Protocol (ARP) 
    // ... 

    
    uint16_t Type = gdeshell_FromNetByteOrder16(eh->type);
    
    switch ( (uint16_t) Type)
    {
        // ::: IPV4
        // 0x0800	Internet Protocol version 4 (IPv4)
        // Ok como test vamos notificar o processo atual
        // de que recebemos um pacote ipv4
        
        case 0x0800:
            printf ("[0x0800]: IPV4 received.\n");
           
           //#test
           //notificando ...(ok funcionou.)
           //network_procedure ( NULL, 3000, 0,0 ); 
           
           // #debug
           //printf("todo: Internet Protocol version 4 (IPv4)\n");
           //printf("IPv4 ");
           //do_ipv4 ( (unsigned long) buffer_address );
           //refresh_screen ();
           return 0;
           break;

        //::: ARP
        //0x0806	Address Resolution Protocol (ARP)
        //#todo: devemos chamar uma rotina para tratamento de ARP e n�o
        //fazermos tudo aqui. kkk.
        case 0x0806:
            printf ("[0x0806]: ARP received\n");
            //refresh_screen ();
                   
            //printf("\nARP ");
            //do_arp ((unsigned long) buffer_address );
            //refresh_screen ();
            return 0;
            break;
            
        //::: SNMP
        // Simple Network Management Protocol.
        case 0x814C:
            printf ("[0x814C]: SNMP received\n");
            return 0;
            break;
            
        
            
        //::: IPV6
        //0x86DD	Internet Protocol Version 6 (IPv6)
        case 0x86DD:
            printf ("[0x86DD]: IPV6 received\n");
            //refresh_screen ();
        
            //printf ("IPv6 ");
            //do_ipv6 ( (unsigned long) buffer_address );
            //refresh_screen ();
            return 0;
            break;

        //:::PPP
        //Point-to-Point Protocol.
        case 0x880B:
            printf ("[0x880B]: SNMP received\n");
            return 0;
            break;

        // 0x8863 PPPoE, PPP Over Ethernet (Discovery Stage).
        // 0x8864 PPPoE, PPP Over Ethernet (PPP Session Stage).

        //::: DEFAULT
        // Error: Default package type.
        default:
            printf ("[0x%x]: protocol received\n",Type);
            return 0;
            break;
    }


    return -1;
}

/*
 **************************** 
 * network_test_buffer:
 *     Loop to read the buffers.
 *     Called by the builting command "network"
 */

void network_test_buffer(void)
{
    char buf[4096];
    int i=0;

    debug_print("network_test_buffer:\n");
    printf("\n");
    printf("\n");
    printf("=========================\n");
    printf("network_test_buffer: [LOOP] Reading the buffers in ring3\n");
    
    
    for (i=0; i<4096; i++)
        buf[i] = 0;

    //
    // Loop.
    //

    // Get the packet.
    // Decode the buffer.

    while (1)
    {
        // IN: Service, buffer, lenght, nothing.
        gramado_system_call( 890, 
            (unsigned long) &buf[0], (unsigned long) 1500, 0);

        //printf("[begin]%s[end]\n",buf);

        gdeshell_decode_buffer((unsigned long) &buf[0]);
        
        //#test: OK. o led indica que esta enviando.
        //envia um pacote
        //gdeshell_send_packet();
    };
    
    //Exit
    
    debug_print("network_test_buffer: Done\n");
    printf     ("network_test_buffer: Done\n");
}


/*
 ************************************** 
 * shellSocketTest: 
 * 
 */

//rotina de testes de socket

void shellSocketTest (void){

	//#todo: isso precisa ser um porteiro de estrutura.
	void *ClientHandle;
	
	unsigned long iplong=0;
	unsigned long port=0; //short
	
	unsigned char ip[4];
	
    printf("\n");
    printf("shellSocketTest: Testing socket stuff ...\n");

	
	//
	// Creating socket
	//
	
	
	// Queremos nos conectar com o host 192.168.1.100, na porta 8000.
	//#todo: mudar para 127.0.0.1:8000
	//um servidor pode ser criado para ouvir essa porta.


    printf ("Creating client socket ...\n");
    ClientHandle = (void *) system_call ( 160, 
	                            (unsigned long) 0xC0A80164,  // ip 192.168.1.100
	                            (unsigned long) 8000,        // porta 8000
	                            (unsigned long) 0x22C3 );    // ??

    //printf ("Updating socket ...\n");
    //system_call ( 163, 
	//    (unsigned long) socketHandle, 
	//    (unsigned long) 0xC0A80165, 
	//    (unsigned long) 0x22C2 );


	//
	// Check socket info.
	//


    printf ("Getting ip from socket ...\n");
    iplong = (unsigned long) system_call ( 161, 
	                             (unsigned long) ClientHandle, 
	                             (unsigned long) ClientHandle, 
	                             (unsigned long) ClientHandle );
	
    printf ("Getting port from socket ...\n");
    port = (unsigned long) system_call ( 162, 
	                           (unsigned long) ClientHandle, 
	                           (unsigned long) ClientHandle, 
	                           (unsigned long) ClientHandle );

	//
	// Output
	//

    unsigned long tmp = 0;

	tmp = iplong;
	ip[3] = (char) ( tmp & 0x000000FF ); 

	tmp = iplong;
	tmp = (tmp >> 8);
	ip[2] = (char) ( tmp & 0x000000FF );

	tmp = iplong;
	tmp = (tmp >> 16);
	ip[1] = (char) ( tmp & 0x000000FF );

	tmp = iplong;
	tmp = (tmp >> 24);
	ip[0] = (char) ( tmp & 0x000000FF );


    printf ("\n");
    printf ("Socket: ( %d.%d.%d.%d:%d )\n", 
        ip[0], ip[1], ip[2], ip[3], port );
	//printf("iplong=%x\n",iplong);
    printf ("Done\n");
}



//
// End.
//




