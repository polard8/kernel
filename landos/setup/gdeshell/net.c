/*
 * File: net.c 
 *     Network support for gdeshell.
 */


#include "gdeshell.h"


// (ETHERNET + ARP)
uint8_t test_packet[] = {

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
    uint8_t src_ip[4],
    uint8_t dst_ip[4],
    uint8_t src_mac[6],
    uint8_t dst_mac[6] )
{

    struct gdeshell_ether_header  *eh;  // ethernet header.
    struct gdeshell_ether_arp     *h;   // arp header.
    int i=0;
    unsigned char *buffer;

    //==============================================
    // # ethernet header #

	// Coloca na estrutura do ethernet header os seguintes valores: 
	// > endereço mac da origem.
	// > endereço mac do destion.
	// O endereço mac da origem está na estrutura do controlador nic intel. 
	// O endereço mac do destino foi passado via argumento.

    eh = (void *) malloc ( sizeof(struct gdeshell_ether_header ) );

    if ( (void *) eh == NULL){
        printf ("__SendARP: [FAIL] eh struct\n");
        return;
    }else{

        for( i=0; i<6; i++)
        {
            eh->src[i] = src_mac[i];     // src mac
            eh->dst[i] = dst_mac[i];     // dst mac
        };

        eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);

        // ...
    };


    //==============================================
    // # arp header #
    //

    // Hardware type (HTYPE)   (00 01)
    // Protocol type (PTYPE)   (08 00)
    // Hardware address length (MAC)
    // Protocol address length (IP)
    // Operation (OPER) (dois bytes invertidos)
    
    // mac
    //#todo: pegar o mec do host.
    // Configurando na estrutura de arp o endereço mac de origem e destino.
    // sender mac
    // target mac
    // O endereço mac de origem pegamos na estrutura no nic intel.
    // O endereço mac de destino foi passado via argumento.

    // ip
    // Configurando na estrutura de arp o endereço do ip de origem e 
    // o ip de destino.
    // sender ip
    // target ip
    // Os endereços foram passados via argumento.

    h = (void *) malloc ( sizeof(struct  gdeshell_ether_arp) );

    if ( (void *) h == NULL){
        printf ("__SendARP: [FAIL] h struct\n");
        return;
    }else{
 
        h->type  = 1;      // 0x0100;  // 1      ?? #bugbug order ??
        h->proto = 0x800;  // 0x0008;  // 0x800  ?? #bugbug order ??
        h->hlen  = 6;      // mac size.
        h->plen  = 4;      // ip size.
        h->op = ToNetByteOrder16(ARP_OPC_REQUEST);
        //h->op = ToNetByteOrder16(ARP_OPC_REPLY);

        for ( i=0; i<6; i++ )
        {
            h->arp_sha[i] = src_mac[i];
            h->arp_tha[i] = dst_mac[i]; 
        };

        for ( i=0; i<4; i++ )
        {
            h->arp_spa[i] = src_ip[i]; 
            h->arp_tpa[i] = dst_ip[i]; 
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

    if ((h->type  != 1)      ||  /* ethernet */
        (h->proto != 0x800)  ||  /* IPv4 */
        (h->hlen  != 6)      ||  /* 6-byte MAC */
        (h->plen  != 4))         /* 4-byte protocol address */
    {
        printf ("__SendARP: [FAIL]\n");
        return;
    }

    // sender
    printf ("\n sender: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_sha[i]); }
    printf ("\n sender: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_spa[i]); }
    
    // target
    printf ("\n target: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_tha[i]); }
    printf ("\n target: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_tpa[i]); }
    printf ("\n\n");

    //==================================


    //
    // Copiando o pacote no buffer.
    //

    // #bugbug: standard size ??
    
    buffer = (unsigned char *) malloc(512);
    
    if ( (void*) buffer == NULL ){
        printf ("__SendARP: [FAIL] buffer\n");
        return;
    }


    // #importante:
    // Preparando ponteiros para manipularmos as estruturas usadas no pacote.

    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp      = (unsigned char *) h;


    //
    // Copy
    //

	// Copiando as estruturas para o buffer.
	// >Copiando o header ethernet.
	// >Copiando o arp logo após do header ethernet.

    // ethernet, arp.
    for (i=0; i<14; i++){ buffer[i]      = src_ethernet[i]; };
    for (i=0; i<28; i++){ buffer[i + 14] = src_arp[i];      };


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
void __shellTestARP (void)
{
    printf ("\n");
    printf ("==== gdeshell: __shellTestARP ==== \n"); 

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
    target_ip_address[3] = 88; //100;

    // source mac #bugbug
    uint8_t source_mac_address[6];
    source_mac_address[0] = 0x00;
    source_mac_address[1] = 0x00;
    source_mac_address[2] = 0x00;
    source_mac_address[3] = 0x00;
    source_mac_address[4] = 0x00;
    source_mac_address[5] = 0x00;

    // Broadcast.
    uint8_t target_mac_address[6];
    target_mac_address[0] = 0xFF;
    target_mac_address[1] = 0xFF;
    target_mac_address[2] = 0xFF;
    target_mac_address[3] = 0xFF;
    target_mac_address[4] = 0xFF;
    target_mac_address[5] = 0xFF;

   //#bugbug
   __SendARP ( 
       source_ip_address,  target_ip_address, 
       source_mac_address, target_mac_address );
}


/*
 *************************** 
 * network_initialize:
 * 
 */

void network_initialize (void)
{
    debug_print("network_initialize:\n");

    // Initialize network support.

    printf ("network_initialize: Initializing the ring0 network manager...\n");
    gramado_system_call (968,0,0,0);

    // Send ARP packet.

    printf ("network_initialize: Sending arp\n");
    __shellTestARP();
}



/*
 ***************** 
 * network
 * 
 */
 
// Initialize ring0 network support.
// Reading the buffers sent by the kernel.

void network(void)
{
    printf("gdeshell-network: Testing network support.\n");

    // Initializing.
    network_initialize();
    
    // Input loop:
    // Getting some input from the driver
    // and decoding some packets.
    network_loop();
    
    // Not reached!
}


/*
 *********************************** 
 * gdeshell_send_packet:
 * 
 *     Send a packet to the nic driver.
 */
 
// Send packet.
// O conteudo nao eh analizado.
// Apenas passamos para o driver de nic um buffer e o comando
// de enviar.
// O driver de nic devera usar as informaçoes do buffer
// para saber o destino. 
// Se o pacote for invalido, ele apenas derruba.

void gdeshell_send_packet ( unsigned long packet_buffer )
{
    if (packet_buffer == 0){ return; };

    gramado_system_call ( 
        891, 
        (unsigned long) packet_buffer,  // buf
        (unsigned long) 1500,           // len
        0 );
}


void 
print_ethernet_header ( 
    const unsigned char *Buffer, 
    int Size )
{
    struct gdeshell_ether_header *eth = (struct gdeshell_ether_header *) Buffer;

    printf("\n");
    printf("Ethernet Header\n");


    if ( (void*) eth == NULL )
        return;

    // Destination MAC
    // Source MAC
    // Protocol type.

    printf ("   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", 
        eth->dst[0], eth->dst[1], eth->dst[2], 
        eth->dst[3], eth->dst[4], eth->dst[5] );

    printf ("   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", 
        eth->src[0], eth->src[1], eth->src[2], 
        eth->src[3], eth->src[4], eth->src[5] );
 
    printf ("   |-Ethertype           : %x \n",
        (unsigned short) eth->type);
}


void print_arp_header ( char *arp_buffer )
{
    // O header ARP começa depois do header de ethernet.
    //struct gdeshell_ether_arp *h = (struct gdeshell_ether_arp *) (Buffer + ETHERNET_HEADER_LENGHT);
    struct gdeshell_ether_arp *h = (struct gdeshell_ether_arp *) arp_buffer;
    int i=0;

    // Filter

    if ( (void*) arp_buffer == NULL ){
        printf ("print_arp_header: [FAIL] Buffer\n");
        return;
    }

    //==================================
    // #debug
    // show arp

    printf ("\n\n");
    printf ("[arp]\n\n");
    printf ("type={%x} proto={%x} hlen={%d} plen={%d} op={%x} \n", 
        h->type, h->proto, h->hlen, h->plen, h->op );

    // sender
    printf ("\n sender: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_sha[i]); }
    printf ("\n sender: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_spa[i]); }
    
    // target
    printf ("\n target: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_tha[i]); }
    printf ("\n target: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_tpa[i]); }

    // Se enviaram o request para o ip do gramado.
    // 192.168.1.112
    if ( h->arp_tpa[0] == 192 &&
         h->arp_tpa[1] == 168 &&
         h->arp_tpa[2] == 1   &&
         h->arp_tpa[3] == 112 )
    {
        printf ("  ==  MY IP ==  ");
    }

    printf ("\n\n");

    //==================================
}

void print_ipv4_header ( char *ipv4_buffer )
{
    char *buf     = (char *) ipv4_buffer;
    //char *payload = (char *) ipv4_buffer + ?;

    char Version_IHL = 0;
    unsigned int Version = 0;
    unsigned int Lenght = 0;

    //int PayloadBaseOffset = 20;
    //int PayloadOffsetMultiplier = 0;
    int PayloadOffset = 0;    

    // pega versao e lenght
    Version_IHL = (char) buf[0];
 
    
    Version = (unsigned int) (Version_IHL >> 4) & 0xf;
    Lenght  = (unsigned int) (Version_IHL     ) & 0xf;
    
    // Because an IPv4 header is a minimum of 20 bytes in size, 
    // the smallest value of the IHL field is 5.
    // With a maximum IHL value of 0xF, 
    // the maximum size of the IPv4 header, 
    // including options, is 60 bytes (15 x 4).
    // 20 de header + 40 de options

    // Nunca menor que 5.
    if ( Lenght < 5 ){ Lenght = 5; }

    if ( Lenght > 0xF ){ 
        printf ("Invalid IHL\n");
        return;
    }

    PayloadOffset = (int)( 4 * Lenght );

    //protocol
    char Protocol_char = 0;
    int Protocol = 0;

    Protocol_char = (char) buf[9];  
    Protocol = (int) Protocol_char;

    //printf ("ipv4: Ver=%d ihl=%d Protocol=%d PayloadOffset=%d\n",
    //    Version,
    //    Lenght,
    //    Protocol,
    //    PayloadOffset );

    printf ("ipv4: Ver=%d Protocol=%d \n",
        Version, Protocol );
    
    //
    // Protocol
    //

    if ( Protocol == 6 ){
        //printf ("TCP: \n");
        print_tcp_header( (char *) &buf[PayloadOffset] );
        return;
    }
    
    if ( Protocol == 17 ){
        //printf ("UDP: \n");
        print_udp_header( (char *) &buf[PayloadOffset] );
        return;
    }
} 


void print_udp_header ( char *udp_buffer )
{
    char *buf = (char *) udp_buffer;
    unsigned short *buf16 = (unsigned short *) udp_buffer;

    unsigned short SourcePort=0;
    unsigned short DestinationPort=0;

    int payloadOffset = 8;

    SourcePort      = (unsigned short) buf16[0]; //primeira short
    DestinationPort = (unsigned short) buf16[1]; //segunda short

    SourcePort      = gdeshell_FromNetByteOrder16(SourcePort);
    DestinationPort = gdeshell_FromNetByteOrder16(DestinationPort);

    printf ("udp: s={%x} d={%x} \n", 
        SourcePort, DestinationPort);


    // Drop
    //if ( DestinationPort != 34884 ){
    //    return;
    //}


    // #todo
    // check the destination por in the second short.

    buf[payloadOffset + 150] = 0;  //finaliza a string


    // 34884 em decimal.
    // 4488 no header.
    // 8844 convertido.

    if ( DestinationPort == 34884 ){
        printf("[PAYLOAD UDP 34884]: %s\n", &buf[payloadOffset] );
    }

    if ( DestinationPort == 80 ){
        printf("[PAYLOAD UDP 80]: %s\n", &buf[payloadOffset] );
    }
}


void print_tcp_header ( char *tcp_buffer )
{
    char *buf  = (char *) tcp_buffer;

    unsigned short *buf16 = (unsigned short *) tcp_buffer;
    unsigned long *buf32 = (unsigned long *) tcp_buffer;

    unsigned short SourcePort=0;
    unsigned short DestinationPort=0;


    SourcePort      = (unsigned short) buf16[0]; //segunda short
    DestinationPort = (unsigned short) buf16[1]; //segunda short


    SourcePort      = gdeshell_FromNetByteOrder16(SourcePort);
    DestinationPort = gdeshell_FromNetByteOrder16(DestinationPort);

    // #debug: it works
    printf ("tcp: s={%x} d={%x} \n", 
        SourcePort, DestinationPort);

    // Drop
    //if ( DestinationPort != 34884 ){
    //    return;
    //}


    //#debug
    //return;
    


    unsigned long SequenceNumber=0;
    SequenceNumber = (unsigned long) buf32[1];  // segunda long

    char Data8 = 0;
    unsigned int Lenght = 0;
    int PayloadOffset = 0;    

    // lenght e reservado
    Data8 = (char) buf[12];
    Lenght = (unsigned int) (Data8 >> 4) & 0xf;

    
    // Because an IPv4 header is a minimum of 20 bytes in size, 
    // the smallest value of the IHL field is 5.
    // With a maximum IHL value of 0xF, 
    // the maximum size of the IPv4 header, 
    // including options, is 60 bytes (15 x 4).
    // 20 de header + 40 de options

    // Nunca menor que 5.
    if ( Lenght < 5 ){ Lenght = 5; }

    if ( Lenght > 0xF ){ 
        printf ("Invalid len\n");
        return;
    }

    PayloadOffset = (int)( 4 * Lenght );

    //printf ("tcp: len=%d PayloadOffset=%d \n", Lenght, PayloadOffset );

   
    //printf ("Sequence Number = {%d}\n",SequenceNumber);
   
    //
    // payload
    //
    
    // #todo: segment size?
    // The default TCP Maximum Segment Size is 536?
    // Maximum segment size = 1460 bytes ?
    
    // limit
    buf[PayloadOffset + 32] = 0;


    // gramado
    if (DestinationPort == 34884 ){
        printf ("[PAYLOAD TCP 34884]: %s\n", &buf[PayloadOffset]);
    }
    
    if (DestinationPort == 80 ){
        printf ("[PAYLOAD TCP 80]: %s\n", &buf[PayloadOffset]);
    }
} 



/*
 ***************** 
 * network_decode_buffer:
 * 
 *     Decode a buffer with a network packet.
 */

int network_decode_buffer ( unsigned long buffer_address )
{

    int ShowEthernetHeader = FALSE;

    int IgnoreARP = TRUE;
    int IgnoreIPV4 = FALSE;
    int IgnoreSNMP = TRUE;
    int IgnoreIPV6 = TRUE;
    int IgnorePPP = TRUE;


    // The ethernet header.
    struct gdeshell_ether_header *eh;
    uint16_t Type=0;
    
    //See: net/  and netinet/
    //struct ether_header *__eth;
    //struct arphdr       *__arp; 
    //struct ip           *__ip;
    //struct tcphdr       *__tcp;
    //struct udphdr       *__udp;
    // ...


    //#debug
    debug_print ("network_decode_buffer:\n");
    //printf ("network_decode_buffer:\n");

    if ( buffer_address == 0 ){
        printf ("network_decode_buffer: [FAIL] buffer_address\n");
        return -1;
    }

	//
	// == Ethernet header =============================
	//

	//ethernet header
    //eh = (void *) &buffer[0];
    
    eh = (void *) buffer_address;

    if ( (void *) eh == NULL ){
        printf ("network_decode_buffer: [FAIL] Ethernet header\n");
        return -1;
    }else{

        // Print ethernet header.
        if(ShowEthernetHeader == TRUE){
            print_ethernet_header ( 
                (const unsigned char*) buffer_address, 
                1500 );
        }
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

    int i=0;
    int c;
    char *buf     = (char *) buffer_address;
    //char *payload = (char *) buffer_address + 54;

    Type = gdeshell_FromNetByteOrder16(eh->type);
    
    switch ( (uint16_t) Type ){

        // ::: IPV4
        // 0x0800	Internet Protocol version 4 (IPv4)
        // Ok como test vamos notificar o processo atual
        // de que recebemos um pacote ipv4
        
        case 0x0800:
            if ( IgnoreIPV4 == TRUE ){ return 0; }
            // printf ("[0x0800]: IPV4 received\n");
            print_ipv4_header ( (char *) buffer_address + ETHERNET_HEADER_LENGHT );
            return 0;
            break;

        //::: ARP
        //0x0806	Address Resolution Protocol (ARP)
        //#todo: devemos chamar uma rotina para tratamento de ARP e n�o
        //fazermos tudo aqui. kkk.
        case 0x0806:
            if ( IgnoreARP == TRUE ){ return 0; }
            //printf ("[0x0806]: ARP received\n");
            print_arp_header ((char *)buffer_address + ETHERNET_HEADER_LENGHT );
            return 0;
            break;

        //::: SNMP
        // Simple Network Management Protocol.
        case 0x814C:
            if ( IgnoreSNMP == TRUE ){ return 0; }
            printf ("[0x814C]: SNMP received\n");
            return 0;
            break;

        //::: IPV6
        //0x86DD	Internet Protocol Version 6 (IPv6)
        case 0x86DD:
            if ( IgnoreIPV6 == TRUE ){ return 0; }
            printf ("[0x86DD]: IPV6 received\n");
            return 0;
            break;

        //:::PPP
        //Point-to-Point Protocol.
        case 0x880B:
            if ( IgnorePPP == TRUE ){ return 0; }
            printf ("[0x880B]: PPP received\n");
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
 * network_loop:
 * 
 *     Loop to read the buffers.
 *     Called by the builting command "network"
 */

void network_loop(void)
{

    // #bugbug
    // We don't need this big buffer here.
    // Maybe it is time to dynalloc a new one.

    char buf[4096];

    int i=0;

    debug_print("network_loop:\n");

    printf("\n");
    printf("=========================\n");
    printf("network_loop: [LOOP] Reading the buffers in ring3\n");
    printf("\n");
    
    for (i=0; i<4096; i++){
        buf[i] = 0;
    };

    //
    // == Loop ======================================
    //

    // + Get the packet.
    // + Decode the buffer.
    // + ...

    int msgStatus = FALSE;

    while (TRUE){

        msgStatus = FALSE;
        
        // IN: Service, buffer, lenght, nothing.
        msgStatus = gramado_system_call ( 
                        890, 
                        (unsigned long) &buf[0], 
                        (unsigned long) 1500, 
                        0 );


        if (msgStatus == FALSE){
            //printf("Status FALSE\n");
        }

        if (msgStatus == TRUE){
            //printf("Status TRUE\n");
            network_decode_buffer ((unsigned long) &buf[0]);
            
            //for (i=0; i<4096; i++){  buf[i] = 0;  };
            for (i=0; i<128; i++){  buf[i] = 0;  };
        }

        //#test: OK. o led indica que esta enviando.
        //envia um pacote
        //gdeshell_send_packet();
    
        // #todo:
        // Maybe we can exit this loop.
    };

    // Not reached.
    debug_print("network_loop: Done\n");
    printf     ("network_loop: Done\n");
}


void net_socket_test1(void)
{
    int socket_fd = -1;
    char message[32];

    debug_print("=============================\n");
    debug_print("net_socket_test1:\n");

    printf("\n");
    printf("net_socket_test1: socket(), send() and recv()\n");

    //printf("Creating...\n");

    socket_fd = (int) socket ( 
                          (int) AF_INET, 
                          (int) SOCK_STREAM, 
                          (int) 0 );

    if ( socket_fd <= 0 )
    {
        printf("Couldn't create\n");
        return;
    }

    printf ("socket_fd:  %d\n",socket_fd);

    // Write message in the buffer.
    
    sprintf ( message, "Magic string");


    // #bugbug
    // PF ao testar na maquina real.

    // request 4000: Passando o pid do sender via argumento.
    // ring0: f->sync.sender See; socket.c in the kernel.
    ioctl ( socket_fd, 4000, getpid() );
    //sc82 (4,socket_fd,4000,getpid());

    //getting the sender.
    //pra checar se a rotina acima funcionou.
    
    // #bugbug
    // Realmente o salvamento nao funciona.
    // O problema esta nos segmentos de dados.
    // Do mesmo modo nao conseguiremos configurar 'termios'.
    
    int sender;
    sender = ioctl ( socket_fd, 4001, 0 );
    //sender = sc82 (4,socket_fd,4001,0);
    printf ("SENDER {%d} \n",sender);

    // Send the message.
    
    send (socket_fd , message , strlen(message) , 0 ); 

    // Setup buffer for error message.

    sprintf( message, "=FAIL=");

    recv (socket_fd, (void *) &message[0], 5, 0 );
    
    // finalize.
    message[9] = 0;
    
    printf("Message:{%s}\n",message);

    printf("net_socket_test1: done\n");

    debug_print("net_socket_test1: done\n");
}


//
// End.
//




