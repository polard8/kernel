// sent ipv4 test


void testsentIPV4()
{

	//
	// ## ETH HEADER ## =============================
	//
	
	struct ether_header *eh;
	
	eh =  (void *) malloc ( sizeof(struct ether_header ) );
	if( (void*) eh == NULL)
	{
		printf("struct eh fail");
		die();
	}
	
	for( i=0; i<6; i++)
	{
		eh->dst[i] = target_mac_address[i];       //dest. ff ff...
		eh->src[i] = currentNIC->mac_address[i];  //source ok
	}	
	
	
	//#todo: mudar para ipv4
	//0x0800	Internet Protocol version 4 (IPv4)
	eh->type = (uint16_t) ToNetByteOrder16(0x0800);
	//eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);

	//==============================================
	// ## ipv4 ##
	//
	
	struct ipv4_header_d *ipv4;
	
	ipv4 = (void *) malloc ( sizeof(struct ipv4_header_d) );
	
	if( (void *) ipv4 == NULL)
	{
		printf("intel-sendTest: ipv4 fail");
		die();
	}else{

        // IPv4 common header
	    ipv4->Version_IHL = 0x45;
	    ipv4->DSCP_ECN = 0x00;
	    ipv4->Identification = 0x0100; //??
	    ipv4->Flags_FragmentOffset = 0x0000;
	    ipv4->TimeToLive = 0x40;
	    
		//default protocol: UDP
 	    //#define IPV4_PROT_UDP 0x11
		ipv4->Protocol = 0x11; //IPV4_PROT_UDP;
 	    
		memcpy ( (void*) &ipv4->SourceIPAddress[0],      (const void*) &source_ip_address[0], 4);
	    memcpy ( (void*) &ipv4->DestinationIPAddress[0], (const void*) &target_ip_address[0], 4);    	
	};

	

	//==============================================
	// ## udp ##
	//
	
	struct udp_header_d *udp;
	
	udp = (void *) malloc ( sizeof(udp_header_d) );
	if( (void *) udp == NULL)
	{
		printf("intel-sendTest: udp fail");
		die();
	}else{
    
	    udp->SourcePort = 0;   
        udp->DestinationPort = 0;
        udp->Length = 0;
        udp->Checksum = 0; 		
    };
	
	
	
	//==============================================
	// ## data ##
	//		
                
	char xxxdata[4];			       	
    xxxdata[0] = 1;
	xxxdata[1] = 2;
	xxxdata[2] = 3;
	xxxdata[3] = 4;
	
	

	
	//
	// ## buffer ##
	//
	
	//agora coloca tudo dentro do buffer
	int j;
	unsigned char data[34];
	unsigned char *dst = (unsigned char *) &data[0]; ///buffer grande
	unsigned char *src1 = (unsigned char *) eh;
	unsigned char *src2 = (unsigned char *) ipv4;	
	unsigned char *src3 = (unsigned char *) udp; //udp		
	unsigned char *src4 = (unsigned char *) xxxdata; //data	da mensagem udp	
	
		//copia o header ethernet
		for ( j=0; j<14; j++ )
		{
			dst[j] = src1[j];
		}
		
		//copia o ipv4
		for ( j=0; j<20; j++ )
		{
			dst[j + 14] = src2[j];
		}

		//copia o udp
		for ( j=0; j<8; j++ )
		{
			dst[j + 14 +20] = src3[j];
		}
		
		//copia o xxxdata
		for ( j=0; j<4; j++ )
		{
			dst[j + 14 +20 +4] = src4[j];
		}		
		
		
		
	
	//Enviando um pacote ipv4+outro pra algum lugar. 
	//eth header + ip + udp + data
    send_ipv4_packet ( (struct nic_info_d *) currentNIC, 14 + 20 + 8 + 4, &buffer[0] );
	
	//#debug
	printf("sending ipv4 (while)\n");
	refresh_screen();	
					   
	while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
	{
		//nothing
	}			
		
};