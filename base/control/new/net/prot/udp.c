
// udp.c

#include <kernel.h>


#define __UDP_PACKE_SIZE  ETHERNET_HEADER_LENGHT +\
IP_HEADER_LENGHT +\
UDP_HEADER_LENGHT + 512  

char udp_packet[__UDP_PACKE_SIZE];
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
    if (dport == 34884)
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

    network_send_udp( 
        __udp_gramado_default_ipv4,   // scr ip
        __udp_target_default_ipv4,    // dst ip
        __udp_target_mac,             // dst mac
        message,                      // msg
        34884 );                      // target port
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

// ethernet, ipv4, udp.
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
    eh->type = (uint16_t) ToNetByteOrder16 (ETH_TYPE_ARP);
// ...

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
    ipv4->v_hl = 0x45;       // 8 bit
    ipv4->ip_tos    = 0x00;  // 8 bit

// 16 bit
    ipv4->ip_len = (IP_HEADER_LENGHT + UDP_HEADER_LENGHT + 512);

    ipv4->ip_id = 0x0100;    // 16 bit 

//>>>>
// #importante
// Existem varios protocolos para ip.
// TCP=0x6 UDP=0x11
//default protocol: UDP
//#define IPV4_PROT_UDP 0x11
    ipv4->ip_off = 0x0000;  //16 bit
    
    ipv4->ip_ttl = 0x40;              //8bit
    ipv4->ip_p = 0x11;    //IPV4_PROT_UDP;  // 8bit
    //ipv4->ip_sum                      // 16bit

//>>>>
    memcpy ( 
        (void *) ipv4->ip_src.s_addr, 
        (const void *) &source_ip[0], 
        4 );

//>>>>
    memcpy ( 
        (void *) ipv4->ip_dst.s_addr, 
        (const void *) &target_ip[0], 
        4 );




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

    udp->uh_sport = 20;  //FTP-DATA File Transfer
    udp->uh_dport = 20;  //FTP-DATA File Transfer


// Length
// This field specifies the length in bytes of the UDP header and UDP data. 
//This field specifies the length in bytes of the UDP header and UDP data. 
//The minimum length is 8 bytes, the length of the header. 
    udp->uh_ulen = (UDP_HEADER_LENGHT + 512); 

// Checksum
// #remember:
// When UDP runs over IPv4, 
// the checksum is computed using a "pseudo header" 
// that contains some of the same information from the real IPv4 header.
    udp->uh_sum = 0; //#todo

//
// == # BUFFER # =====
//

// ??
// Quem?
// Estamos pegando o offset que nos levar� ao endere�o do buffer.
// Usaremos esse offset logo abaixo.
// Pegamos esse offset na estrutura do controlador nic intel.

    //uint16_t old = currentNIC->tx_cur;

// Copiando o pacote no buffer.
// Pegando o endere�o virtual do buffer na estrutura do controlador 
// nic intel. Para isso usamos o offset obtido logo acima.

    //unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];
      unsigned char *buffer = (unsigned char *) udp_packet;

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
    for ( j=0; j<ETHERNET_HEADER_LENGHT; j++ ){
        buffer[j] = src_ethernet[j];
    };

//Step2
//copia o ipv4
    for ( j=0; j<IP_HEADER_LENGHT; j++ ){
        buffer[j + ETHERNET_HEADER_LENGHT] = src_ipv4[j];
    };

//Step3
//copia o udp
    for ( j=0; j<UDP_HEADER_LENGHT; j++ ){
        buffer[j + ETHERNET_HEADER_LENGHT +IP_HEADER_LENGHT] = src_udp[j];
    };

//Step4
//copia o xxxdata
    for ( j=0; j<32; j++ ){
        buffer[j + ETHERNET_HEADER_LENGHT + IP_HEADER_LENGHT + UDP_HEADER_LENGHT] = 
            data[j];
    };


// lenght:
// Vamos configurar na estrutura do nic intel o tamanho do pacote.
// Lenght de um pacote ipv4.
// ethernet header, ipv4 header, udp header, data.
    //unsigned int lenght = __UDP_PACKE_SIZE;
    


// send
    e1000_send( currentNIC, __UDP_PACKE_SIZE, buffer );


//cmd
    //currentNIC->legacy_tx_descs[old].cmd = 0x1B;
//status
    //currentNIC->legacy_tx_descs[old].status = 0;
// Current TX.
// Qual � o buffer atual para transmiss�o.
    //currentNIC->tx_cur = ( currentNIC->tx_cur + 1 ) % 8;

//
// ==== # SEND # ======
//

// #importante: 
// Diga ao controlador qual � o �ndice do descritor a ser usado para  
// transmitir dados.
// TDH	= 0x3810,    /* Tx Descriptor Head */
// TDT	= 0x3818,    /* Tx Descriptor Tail */

	// *( (volatile unsigned int *)(currentNIC->mem_base + 0x3810)) = 0;
   // *( (volatile unsigned int *)(currentNIC->mem_base + 0x3818)) = currentNIC->tx_cur;

// #debug
// Colocamos essa mensagem antes de entrarmos no while.
// Pois precisamos implementar algum contador no while para n�o
// ficarmos preso nele pra sempre.
    //printf ("network_SendIPV4_UDP: Sending UDP/IP. *debug *while\n");
    //refresh_screen ();

// #perigo:
// Status.
// Checamos o status do buffer old pra ver se ele foi enviado.
// Fica travado aqui at� que seja enviado?
// Poderia ter um timemout?.

    //int t;
    //for (t=0; t< 25000;t++)
   // {
     //    if ( (currentNIC->legacy_tx_descs[old].status & 0xFF) == 1 )
       //  {
         //     printf ("Ok");
           //   debug_print ("network_SendIPV4_UDP: done\n");
             // return 0;
         //}
    //}

    //#todo
    //while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
    //{
        // Nothing.
    //};
        
    //printf (">>>> fail timeout\n");
    //debug_print ("network_SendIPV4_UDP: timeout\n");
    //debug_print ("network_SendIPV4_UDP: done\n");

// done:
    printf("Done\n");
    return 0;
fail:
    printf("Fail\n");
    return -1;
}

