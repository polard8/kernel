/*
 *  #todo: 
 * 
 *  Building a small network library.
 *  See: net.c in gdeshell/
 * 
 */


/*
// (ETHERNET + ARP)
uint8_t __libnet_arp_packet[] = {

    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  // eth dest (broadcast)
    0x52, 0x54, 0x00, 0x12, 0x34, 0x56,  // eth source  ??? o nic sabe
    0x08, 0x06,                          // eth type 
    0x00, 0x01,  // ARP htype 
    0x08, 0x00,  // ARP ptype 
    0x06,        // ARP hlen 
    0x04,        // ARP plen 
    0x00, 0x01,  // ARP opcode: ARP_REQUEST 
    0x52, 0x54, 0x00, 0x12, 0x34, 0x56,  // ARP hsrc 
    192, 189, 1, 112,                    // ARP psrc  gramado 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ARP hdst 
    192, 168, 1, 100,                    // ARP pdst alguem 
};
*/

//unsigned char host_mac_address[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/*
void 
libnet_print_ethernet_header ( 
    const unsigned char *Buffer, 
    int Size );
void 
libnet_print_ethernet_header ( 
    const unsigned char *Buffer, 
    int Size )
{
	// #todo
	// Usar a estrutura da rtl.
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
*/

/*
void libnet_print_arp_header ( char *arp_buffer );
void libnet_print_arp_header ( char *arp_buffer )
{}
*/

/*
void libnet_print_ipv4_header ( char *ipv4_buffer );
void libnet_print_ipv4_header ( char *ipv4_buffer )
{}
*/

/*
void libnet_print_udp_header ( char *udp_buffer )
void libnet_print_udp_header ( char *udp_buffer )
{}
*/

/*
void print_tcp_header ( char *tcp_buffer );
void print_tcp_header ( char *tcp_buffer )
{}
*/


// libnet_decode_buffer:
// Decode a buffer with a network packet.

/*
int libnet_decode_buffer ( unsigned long buffer_address );
int libnet_decode_buffer ( unsigned long buffer_address )
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

           //#test
           //notificando ...(ok funcionou.)
           //network_procedure ( NULL, 3000, 0,0 ); 

           //printf("[PAYLOAD]: %s\n", &buf[51] );
                       
           //printf("[PAYLOAD]:\n");
           //for(i=54; i< 200; i++)
           //{
           //    c = buf[i];
           //    printf("%c",c);
           //}
           
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
            if ( IgnoreARP == TRUE ){ return 0; }

            printf ("[0x0806]: ARP received\n");

            print_arp_header ((char *)buffer_address + ETHERNET_HEADER_LENGHT );
                   
            //printf("\nARP ");
            //do_arp ((unsigned long) buffer_address );
            //refresh_screen ();
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

            //refresh_screen ();
        
            //printf ("IPv6 ");
            //do_ipv6 ( (unsigned long) buffer_address );
            //refresh_screen ();
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

*/



















