

#include "shell.h"

#include "net.h"


    //temporary. we need a system function to get this number.

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



//#todo
//Criar um pacote arp com ethernet e arp e enviar 
//o ponteiro do buffer para o kernel


void 
__SendARP ( uint8_t source_ip[4], 
          uint8_t target_ip[4], 
          uint8_t target_mac[6] )
{
     
    //
    // Enviar um pacote ARP.
    //



 // IN: 
 //    source_ip. (It's in the layer 3 of the OSI model. network layer)
 //    target_ip. (It's in the layer 3 of the OSI model. network layer)
 //    target_mac. (It's in the layer 2 of the OSI model. data link layer)
  
    int i=0;

    struct ether_header *eh;
    struct ether_arp *h;  
  
//==============================================
	// # ethernet header #
	//

    eh = (void *) malloc ( sizeof(struct ether_header ) );

    if ( (void *) eh == NULL)
    {
        printf ("shellTestARP: eh struct fail\n");
        return;
        //die ();

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

    h = (void *) malloc ( sizeof(struct  ether_arp) );

    if ( (void *) h == NULL)
    {
        printf ("shellTestARP: struct h fail");
        return;
        //die ();

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

        //h->op = ToNetByteOrder16(ARP_OPC_REPLY);
        h->op = ToNetByteOrder16(ARP_OPC_REQUEST);

// mac
		// Configurando na estrutura de arp o endereço mac de origem e destino.
		// sender mac
		// target mac
		// O endereço mac de origem pegamos na estrutura no nic intel.
		// O endereço mac de destino foi passado via argumento.

        for( i=0; i<6; i++)
        {
			//#todo: pegar o mec do host.
		   // h->arp_sha[i] = currentNIC->mac_address[i]; 
		    h->arp_sha[i] = host_mac_address[i];
		    h->arp_tha[i] = target_mac[i]; 
        };


	// ip
		// Configurando na estrutura de arp o endereço do ip de origem e 
		// o ip de destino.
		// sender ip
		// target ip
		// Os endereços foram passados via argumento.
		
        for ( i=0; i<4; i++)
        {
            h->arp_spa[i] = source_ip[i]; 
            h->arp_tpa[i] = target_ip[i]; 
        };

        //...
    };
  
   //==================================
	//#debug
	//show arp
	
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
	printf("\n\n");
	
	//==================================
	
//
	// Copiando o pacote no buffer.
	//

	// Pegando o endereço virtual do buffer na estrutura do controlador 
	// nic intel. Para isso usamos o offset obtido logo acima.

    //#todo
    //unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];
    //unsigned char *buffer = (unsigned char *) 0;
    unsigned char *buffer;
    
    buffer = (unsigned char *) malloc ( 512 );
    
    
	// #importante:
	// Preparando ponteiros para manipularmos as estruturas usadas no pacote.

    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp = (unsigned char *) h;


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




void __shellTestARP (){

    printf ("\n\n ============ shellTestARP ================= \n\n"); 

    uint8_t source_ip_address[4];
	source_ip_address[0] = 192;
	source_ip_address[1] = 168;
	source_ip_address[2] = 1;   
	source_ip_address[3] = 112; 

	uint8_t target_ip_address[4];
	target_ip_address[0] = 192;
	target_ip_address[1] = 168;
	target_ip_address[2] = 1; 
	target_ip_address[3] = 111; 
	
	uint8_t target_mac_address[6];
	target_mac_address[0] = 0xFF;
	target_mac_address[1] = 0xFF;
	target_mac_address[2] = 0xFF;
	target_mac_address[3] = 0xFF;
	target_mac_address[4] = 0xFF;
	target_mac_address[5] = 0xFF;


   __SendARP ( source_ip_address, target_ip_address, target_mac_address );

}












