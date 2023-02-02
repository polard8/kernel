
// udp.c

#include <kernel.h>


#define __UDP_PACKET_SIZE  ETHERNET_HEADER_LENGHT +\
IP_HEADER_LENGHT +\
UDP_HEADER_LENGHT + 512  

char udp_packet[__UDP_PACKET_SIZE];
char udp_payload[1024];

// source ip
unsigned char __udp_gramado_default_ipv4[4] = { 
    192, 168, 1, 112 
};
// destination ip (linux)
unsigned char __udp_target_default_ipv4[4]  = { 
    192, 168, 1, 8  //linux
};
// Target MAC.
unsigned char __udp_target_mac[6] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};

//---------------------

void 
network_handle_udp( 
    const unsigned char *buffer, 
    ssize_t size )
{
    struct udp_d *udp;

    printf("network_handle_ipv4: ==== UDP ====\n");

    udp = (struct udp_d *) buffer;
    if ( (void*) buffer == NULL )
        return;

    uint16_t sport = (uint16_t) FromNetByteOrder16(udp->uh_sport);
    uint16_t dport = (uint16_t) FromNetByteOrder16(udp->uh_dport);
    printf ("sp ={%d}\n",sport);
    printf ("dp ={%d}\n",dport);

    printf ("len={%d}\n",udp->uh_ulen);
    printf ("sum={%d}\n",udp->uh_sum);

    memset(udp_payload,0,sizeof(udp_payload));
    strncpy(
        udp_payload,
        (buffer + 6),
        512 );


// Don't print every message.
// Is it a valid port?
// Hang if the port is valid.
    if (dport == 34884 || dport == 11888)
    {
        printf ("MESSAGE={%s}\n",udp_payload);
        printf("udp: breakpoint\n");
        die();
    }
}

// -----------------

void network_test_udp(void)
{
    char message[512];
    memset(message,0,sizeof(message));
    sprintf(message,"Hello from Gramado to Gramado\n");
    uint16_t target_port = (uint16_t) FromNetByteOrder16(34884);

    network_send_udp( 
        __udp_gramado_default_ipv4,   // scr ip
        __udp_target_default_ipv4,    // dst ip
        __udp_target_mac,             // dst mac
        message,                      // msg
        target_port );                // target port
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
    char *data_buffer,
    unsigned short port )
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
// 192.168.1.112
// Not used?
    currentNIC->ip_address[0] = source_ip[0];  //192;
    currentNIC->ip_address[1] = source_ip[1];  //168;
    currentNIC->ip_address[2] = source_ip[2];  //1;
    currentNIC->ip_address[3] = source_ip[3];  //112;
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
        eh->mac_dst[i] = (uint8_t) currentNIC->mac_address[i];  // source 
        eh->mac_src[i] = (uint8_t) target_mac[i];               // dest
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
    ipv4->ip_tos = 0x00;  // 8 bit

// Total Length
// 16 bit
// This 16-bit field defines the entire packet size in bytes, 
// including header and data. 
// The minimum size is 20 bytes (header without data) and the maximum is 65,535 bytes. 
// ip header + udp header + data.
// #todo: Check if it is right?
// No payload do ip temos o (udp+data)
    unsigned short iplen = (IP_HEADER_LENGHT + UDP_HEADER_LENGHT + 512); 
    ipv4->ip_len = (unsigned short) ToNetByteOrder16(iplen);

// Identification
// ... identifying the group of fragments of a single IP datagram. 
// 16 bit
    //uint16_t ipv4count = 1; 
    //ipv4->ip_id = 0x0100;
    //ipv4->ip_id = (uint16_t) ToNetByteOrder16(ipv4count);
    ipv4->ip_id = 0;  // No fragmentation for now.

  //16 bit   //bits  0b01000;
    ipv4->ip_off = 0x0000;  //0x8

    ipv4->ip_ttl = 64; //0x40;  //8bit


// Protocol
// 8bit
// IPV4_PROT_UDP; 17 = udp.
//>>>>
// #importante
// Existem varios protocolos para ip.
// TCP=0x6 UDP=0x11
//default protocol: UDP
//#define IPV4_PROT_UDP 0x11
    ipv4->ip_p = 0x11;

// 16bit
    ipv4->ip_sum = 0;
/*
    uint32_t checksum = 0;
    checksum += 0x4500;
    checksum += length;
    checksum += ipv4count++;
    checksum += 0x4000;
    checksum += 0x4000 + protocol;
    checksum += ToNetByteOrder16((from >> 16) & 0xFFFF);
    checksum += ToNetByteOrder16(from & 0xFFFF); 
    checksum += ToNetByteOrder16((to >> 16) & 0xFFFF);
    checksum += ToNetByteOrder16(to & 0xFFFF);
    checksum = (checksum >> 16) + (checksum & 0xffff);
    checksum += (checksum >> 16);
    ipv4->ip_sum = ToNetByteOrder16((uint16_t) (~checksum));
*/

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

// UDP ports;
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

// src and dst ports
// Podemos usar o mesmo número de porta?
// Não para enviarmos dentro da mesma máquina.
    uint16_t UDP_PORT = 34884;
    udp->uh_sport = (uint16_t) ToNetByteOrder16(8888);
    udp->uh_dport = (uint16_t) ToNetByteOrder16(UDP_PORT);

// Length
// (UPD header + payload).
// This field specifies the length in bytes of the UDP header and UDP data. 
// The minimum length is 8 bytes, the length of the header. 
    uint16_t __udplen = (uint16_t) (UDP_HEADER_LENGHT + 512); 
    udp->uh_ulen = (uint16_t) ToNetByteOrder16(__udplen);

// Checksum
// #remember:
// When UDP runs over IPv4, 
// the checksum is computed using a "pseudo header" 
// that contains some of the same information from the real IPv4 header.
    udp->uh_sum = 0; //#todo



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
    for ( j=0; j<512; j++ ){
        frame[data_offset +j] = data[j];
    };

 
// ---------------------------------------
// send
// lenght:
// Vamos configurar na estrutura do nic intel o tamanho do pacote.
// Lenght de um pacote ipv4.
// ethernet header, ipv4 header, udp header, data.
// 14 + 20 + 6 + 512 = 552.
    size_t UDP_TOTAL_SIZE = 
               ( ETHERNET_HEADER_LENGHT +\
                 IP_HEADER_LENGHT +\
                 UDP_HEADER_LENGHT +\
                 512 );
// Send the frame.
// Via ip, enviaremos (udp+payload).
    
    // send via nic
    e1000_send( currentNIC, UDP_TOTAL_SIZE, frame );

    // send to myself.
    //network_handle_udp ( 
    //    frame + ETHERNET_HEADER_LENGHT + IP_HEADER_LENGHT ,
    //    UDP_HEADER_LENGHT + 512 );
        
    //#debug
    //refresh_screen();
    //while(1){}
    
    printf ("Done\n");
    refresh_screen();
    return 0;

fail:
    printf ("Fail\n");
    refresh_screen();
    return -1;
}

