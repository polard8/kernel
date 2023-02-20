
// udp.c

#include <kernel.h>


/*
#define __UDP_PACKET_SIZE  ETHERNET_HEADER_LENGHT +\
IP_HEADER_LENGHT +\
UDP_HEADER_LENGHT + 512  
*/

//char udp_packet[__UDP_PACKET_SIZE];
static char udp_payload[1024];

// source ip
unsigned char __udp_gramado_default_ipv4[4] = { 
    192, 168, 1, 12 
};
// destination ip (linux)
unsigned char __udp_target_default_ipv4[4]  = { 
    192, 168, 1, 6  //linux
};
// Target MAC.
unsigned char __udp_target_mac[6] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};

unsigned char saved_mac[6] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};


//---------------------


// IN:
// buffer = udp header base address.
// size     = udp packet size. (header + data)
void 
network_handle_udp( 
    const unsigned char *buffer, 
    ssize_t size )
{
    struct udp_d *udp;
    udp = (struct udp_d *) buffer;

    if ( (void*) buffer == NULL ){
        printf("network_handle_ipv4: buffer\n");
        return;
    }

// The minimum size.
// Only the udp header.
    //if (size < UDP_HEADER_LENGHT){
    //    printf("network_handle_udp: size\n");
    //    return;
    //}


    uint16_t sport = (uint16_t) FromNetByteOrder16(udp->uh_sport);
    uint16_t dport = (uint16_t) FromNetByteOrder16(udp->uh_dport);

/*
    //#debug
    printf ("sp ={%d}\n",sport);
    printf ("dp ={%d}\n",dport);
    printf ("len={%d}\n",udp->uh_ulen);
    printf ("sum={%d}\n",udp->uh_sum);
*/


// Clean the payload local buffer.
    memset(udp_payload,0,sizeof(udp_payload));
// Create a local copy of the payload.
    strncpy(
        udp_payload,
        (buffer + UDP_HEADER_LENGHT),
        1020 );
    udp_payload[1021] = 0;

// Don't print every message.
// Is it a valid port?
// Hang if the port is valid.

    char *p;
    p = udp_payload;
    int mFlag=0;

// #test
// DHCP dialog
// Receiving Offer and Ack.
// Handle dhcp protocol.
    //if (dport == 68)
    if (dport == 68 || dport == 67)
    {
        printf("UDP: dport{%d}   #debug\n",dport);
        //die();
        network_handle_dhcp(
            (buffer + UDP_HEADER_LENGHT),
            (udp->uh_ulen - UDP_HEADER_LENGHT) );
        return;
    }

    if (dport == 34884 || dport == 11888)
    {
        printf ("UDP: Message{%s}\n", udp_payload );

        //printf("UDP: dport{%d}\n",dport);
        //printf (" '%s' \n",udp_payload);
        //die();

        // Parse message
        // #todo: Create a worker
        if ( p[0] == '#' && p[1] == '-')
        {
            if (p[2] == 'x'){
                printf("x command\n");
                //hal_reboot();
                die();
            }
        }
    }
}

// -----------------

void network_save_mac( uint8_t mac[6] )
{
    register int i=0;
    for (i=0; i<6; i++){
        saved_mac[i] = (uint8_t) mac[i];
    };
}


void network_test_udp(void)
{
    char message[512];
    memset(message,0,sizeof(message));
    sprintf(message,"Hello from Gramado to Linux\n");

    if (networkGetStatus() != TRUE)
       return;

    network_send_udp( 
        __udp_gramado_default_ipv4,   // scr ip
        __udp_target_default_ipv4,    // dst ip
        __udp_target_mac,             // dst mac
        34885,                  // source port
        34884,                  // dst port
        message,         //msg
         512 );              //msg lenght
}



void 
network_test_udp0(
    uint8_t tmac[6], 
    uint8_t tip[4],
    unsigned short sport,
    unsigned short dport )
{
    char message[512];
    memset(message,0,sizeof(message));
    sprintf(message,"Hello from Gramado to Linux\n");


    network_send_udp( 
        __udp_gramado_default_ipv4,   // scr ip
        tip,    // dst ip
        tmac,             // dst mac
        sport,                  // source port
        dport,                  // dst port
        message,         //msg
         512 );              //msg lenght
}

void network_test_udp2(void)
{
    network_test_udp0( 
        saved_mac,                                   // linux mac
        __udp_target_default_ipv4,    // linux ip
        34885,
        34884 );
}

// -----------------

/*
 * network_send_udp: 
 *    Criando e enviando um pacote ipv4.  (UDP)
 * IN:
 *     source_ip. (It's in the layer 3 of the OSI model. network layer)
 *     target_ip. (It's in the layer 3 of the OSI model. network layer)
 *     target_mac. (It's in the layer 2 of the OSI model. data link layer)
 *     data. (udp payload)
 */
// #todo
// udp needs to have its own document.
// #todo
// Change the return type to 'int'. 
// #obs:
// UDP/IP
// UDP = 0x11 (ip protocol)

// (Ethernet + IP + UDP)
int
network_send_udp ( 
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6], 
    unsigned short source_port,
    unsigned short target_port,
    char *data_buffer,
    size_t data_lenght )
{
    register int i=0;
    int j=0;

// BUffers:
// ethernet, ipv4, udp, data.
    struct ether_header  *eh;
    struct ip_d  *ipv4;
    struct udp_d  *udp;
    char *data = (char *) data_buffer;


    if ( (void*) data == NULL ){
        printf ("network_send_udp: Invalid data buffer\n");
        goto fail;
    }

// NIC Intel device structure.
    if ( (void *) currentNIC == NULL ){
        printf ("network_send_udp: currentNIC fail\n");
        goto fail;
    }

// Configurando a estrutura do dispositivo.
// 192.168.1.12
// Not used?
    currentNIC->ip_address[0] = source_ip[0];  //192;
    currentNIC->ip_address[1] = source_ip[1];  //168;
    currentNIC->ip_address[2] = source_ip[2];  //1;
    currentNIC->ip_address[3] = source_ip[3];  //12;
    //...

//==============================================
// # ethernet header #
//

    eh = (void *) kmalloc ( sizeof(struct ether_header ) );
    if ( (void *) eh == NULL){
        printf ("network_send_udp: eh fail\n");
        goto fail;
    }

// Coloca na estrutura do ethernet header os seguintes valores: 
// > endereço mac da origem.
// > endereço mac do destion.
// O endereço mac da origem está na estrutura do controlador nic intel. 
// O endereço mac do destino foi passado via argumento.

    for ( i=0; i<6; i++ ){
        eh->mac_src[i] = (uint8_t) currentNIC->mac_address[i];  // source 
        eh->mac_dst[i] = (uint8_t) target_mac[i];               // dest
    };
    eh->type = (uint16_t) ToNetByteOrder16 (ETH_TYPE_IP);

//==============================================
// # ipv4 header #
//
    ipv4 = (void *) kmalloc ( sizeof(struct ip_d) );
    if ( (void *) ipv4 == NULL){
        printf ("network_send_udp: ipv4 fail\n");
        goto fail;
    }

// IPv4 common header
// See: ip.h

//>>>>
    ipv4->v_hl = 0x45;    // 8 bit

// Type of service (8bits)
// - Differentiated Services Code Point (6bits)
// - Explicit Congestion Notification (2bits)
    ipv4->ip_tos = 0x00;  // 8 bit (0=Normal)


// IPV4 Length
// ip + (ip payload)
// 16 bit
// This 16-bit field defines the entire packet size in bytes, 
// including header and data. 
// The minimum size is 20 bytes (header without data) and the maximum is 65,535 bytes. 
// ip header + (udp header + data).
// #todo: Check if it is right?
// No payload do ip temos o (udp+data)
// O lenght do protocolo precisa conter o seu proprio header e o seu proprio payload.
    uint16_t xxxdata = (uint16_t) (data_lenght & 0xFFFF);
    uint16_t __ipheaderlen = IP_HEADER_LENGHT;
    uint16_t __ippayloadlen = (uint16_t) (UDP_HEADER_LENGHT +  xxxdata);
    uint16_t __iplen = (uint16_t) (__ipheaderlen + __ippayloadlen); 
    ipv4->ip_len = (uint16_t) ToNetByteOrder16(__iplen);

// Identification
// ... identifying the group of fragments of a single IP datagram. 
// 16 bit
    //uint16_t ipv4count = 1; 
    //ipv4->ip_id = 0x0100;
    //ipv4->ip_id = (uint16_t) ToNetByteOrder16(ipv4count);
    ipv4->ip_id = 0;  

// Flags (3bits) (Do we have fragments?)
// Fragment offset (13bits) (fragment position)
// Don't fragment for now.
 ipv4->ip_off = ToNetByteOrder16(0x4000); 

    ipv4->ip_ttl = 255;  //64; //0x40;  //8bit

// Protocol (8bit)
// 0x11 = UDP. (17)
    ipv4->ip_p = 0x11;

/*
// src ip
// #bugbug: Esta na ordem certa?
    memcpy ( 
        (void *) &ipv4->ip_src.s_addr, 
        (const void *) &source_ip[0], 
        4 );
    //ipv4->ip_src.s_addr = (unsigned int) ToNetByteOrder32(ipv4->ip_src.s_addr);

// dst ip
// #bugbug: Esta na ordem certa?
    memcpy ( 
        (void *) &ipv4->ip_dst.s_addr, 
        (const void *) &target_ip[0], 
        4 );
    //ipv4->ip_dst.s_addr = (unsigned int) ToNetByteOrder32(ipv4->ip_dst.s_addr);
    //printf ("ip %x\n", ipv4->ip_dst.s_addr);
*/

    unsigned char *spa = (unsigned char *) &ipv4->ip_src.s_addr;
    unsigned char *tpa = (unsigned char *) &ipv4->ip_dst.s_addr;
    int it=0;
    for ( it=0; it<4; it++ )
    {
        spa[it] = (uint8_t) source_ip[it]; 
        tpa[it] = (uint8_t) target_ip[it]; 
    };

//
// Checksum
//

    ipv4->ip_sum = 0;
    ipv4->ip_sum =
         (uint16_t)  net_checksum(
              0, 
              0,
              (const unsigned char *) ipv4, 
              (const unsigned char *) ipv4 + sizeof(struct ip_d));
    ipv4->ip_sum =
         (uint16_t) ToNetByteOrder16(ipv4->ip_sum);

    printf("ip_sum={%x} \n",ipv4->ip_sum);

    //printf ("size %d\n", sizeof (struct ip_d) );
    //refresh_screen();
    //while(1){}

//==============================================
// # udp header #
//

    udp = (void *) kmalloc ( sizeof(struct udp_d) );
    if ( (void *) udp == NULL){
        printf ("network_send_udp: udp fail\n");
        goto fail;
    }


// Ports
    udp->uh_sport = (uint16_t) ToNetByteOrder16(source_port);
    udp->uh_dport = (uint16_t) ToNetByteOrder16(target_port);

// UDP Length
// (UPD header + payload).
// This field specifies the length in bytes of the UDP header and UDP data. 
// The minimum length is 8 bytes, the length of the header. 
    uint16_t __udpheaderlen = UDP_HEADER_LENGHT;
    uint16_t __udppayloadlen = (uint16_t) (data_lenght & 0xFFFF);
    uint16_t __udplen = (uint16_t) (__udpheaderlen + __udppayloadlen); 
    udp->uh_ulen = (uint16_t) ToNetByteOrder16(__udplen);

// Checksum
// #remember:
// When UDP runs over IPv4, 
// the checksum is computed using a "pseudo header" 
// that contains some of the same information from the real IPv4 header.
// # UDP lets us set the checksum to 0 to ignore it?
    udp->uh_sum = 0;  //#todo

    //printf ("size %d\n", sizeof (struct  udp_d) );
    //refresh_screen();
    //while(1){}

//----------------------------------------------------------------------


//
// Buffer
//

// Let's call it 'frame'.
// Because we're sending a 'frame'.

// ??
// Quem?
// Estamos pegando o offset que nos levar� ao endere�o do buffer.
// Usaremos esse offset logo abaixo.
// Pegamos esse offset na estrutura do controlador nic intel.
// Copiando o pacote no buffer.
// Pegando o endere�o virtual do buffer na estrutura do controlador 
// nic intel. Para isso usamos o offset obtido logo acima.

    uint16_t buffer_index = (uint16_t) currentNIC->tx_cur;

// Get the buffer address based on its offset.
    unsigned char *frame = 
        (unsigned char *) currentNIC->tx_buffers_virt[buffer_index];

    //#debug
    //printf ("buffer_index {%d}\n",buffer_index);

// #importante:
// Preparando ponteiros para manipularmos as 
// estruturas usadas no pacote.

    unsigned char *src_ethernet = (unsigned char *) eh; 
    unsigned char *src_ipv4     = (unsigned char *) ipv4; 
    unsigned char *src_udp      = (unsigned char *) udp; 

//
// Copy
//

    if ( (void*) frame == NULL )
        panic("network_send_udp: frame\n");

// Copiando as estruturas para o buffer.
// >Step1) Copiando o header ethernet.
// >Step2) Copiando o heder ipv4.
// >Step3) Copiando o header udp.
// >Step4) Copiando os dados.

//Step1
//copia o header ethernet
    int eth_offset=0;
    for ( j=0; j<ETHERNET_HEADER_LENGHT; j++ )
    {
        frame[eth_offset +j] = src_ethernet[j];
    };

//Step2
//copia o ipv4
    int ipv4_offset = ETHERNET_HEADER_LENGHT;
    for ( j=0; j<IP_HEADER_LENGHT; j++ )
    {
        frame[ipv4_offset +j] = src_ipv4[j];
    };

//Step3
//copia o udp
    int udp_offset = ETHERNET_HEADER_LENGHT + IP_HEADER_LENGHT;
    for ( j=0; j<UDP_HEADER_LENGHT; j++ ){
        frame[udp_offset +j] = src_udp[j];
    };

//Step4
//copia o payload.
    int data_offset = 
            ( ETHERNET_HEADER_LENGHT +
              IP_HEADER_LENGHT +
              UDP_HEADER_LENGHT );
    for ( j=0; j<data_lenght; j++ ){
        frame[data_offset +j] = data[j];
    };

 
// ---------------------------------------
// send
// lenght:
// Vamos configurar na estrutura do nic intel o tamanho do pacote.
// Lenght de um pacote ipv4.
// ethernet header, ipv4 header, udp header, data.
// 14 + 20 + 6 + 512 = 552.
    size_t FRAME_SIZE = 
               ( ETHERNET_HEADER_LENGHT +\
                 IP_HEADER_LENGHT +\
                 UDP_HEADER_LENGHT +\
                 data_lenght );


// Send frame via NIC.
    e1000_send( currentNIC, FRAME_SIZE, frame );

// #debug
// Send frame to myself.
    //network_on_receiving(frame,FRAME_SIZE);
    //refresh_screen();
    //while(1){}
    
    printf ("Done\n");
    //refresh_screen();
    return 0;

fail:
    printf ("Fail\n");
    //refresh_screen();
    return -1;
}

