/*
 * File: fs\write.c 
 *
 * Descrição: 
 *     Rotinas de gravação. em disco
 *
 * Obs:
 *    As rotinas na biblioteca C devem chamar essas funções.
 * Histórico:
 *    Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *    Versão 1.0: 2016 - Revisão.
 *    ...
 */
 
 
#include <kernel.h>


extern void reset_ide0();

/*
 * fatWriteCluster:
 *     Salva um cluster no disco.
 *
 * Argumentos:
 *   setor   ~ Primeiro setor do cluster.
 *   address ~ Endereço do primeiro setor do cluster.
 *   spc     ~ Número de setores por cluster.
 */

//int fatWriteCluster( unsigned long sector, 
//                     unsigned long address, 
//	  				   int spc )
					  
void fatWriteCluster( unsigned long sector, 
                      unsigned long address, 
					  unsigned long spc )
{
	unsigned long i;

	//Começa do primeiro setor do cluster.
	for( i=0; i < spc; i++ )
	{
        write_lba( address, sector + i );
		address = address +512; 
	};
	
	//...
	
done:
    //return (int) 0;	
	return;
};


/*
 * write_lba:
 *     Grava um setor no disco dado o lba.
 *     fsWriteLba
 */
//int write_lba( unsigned long address, unsigned long lba ) 
void write_lba( unsigned long address, unsigned long lba )
{    
    //@todo: Check limits.
	
	// ?? onde está fatbits ??
	
    switch(fatbits)
    {
	    case 32:
			printf("fs-write-write_lba: fat32 not supported. \n");
			goto fail;
			break;		
			
	    case 16:
            my_write_hd_sector( address, lba, 0, 0 );
            goto done;			
			break;		
			
	    case 12:
			printf("fs-write-write_lba: fat12 not supported. \n");
			goto fail;	    
			break;

        default:
			printf("fs-write-write_lba: Unknow fat fs. \n");
			goto fail;		    
            break;		
	};

    // Nothing.	
	
fail:
    refresh_screen();	
done:
    return;
};


/*
 **************************************************
 * fsSaveFile:
 *     Salva um arquivo.
 *     Por enquanto no diretório raiz.
 * @todo: A biblioteca C pode chamar essa funçao.
 */
 
	//@todo: Número máximo de entradas na lista de clusters. Quantas?
    #define  fat_range_max 4096  //128;  	
	//lista de clusters
	unsigned short list[fat_range_max];
 
unsigned long fsSaveFile( unsigned char *file_name, 
                          unsigned long file_size, 
						  unsigned long file_address )  
{
    unsigned short *root = (unsigned short *) VOLUME1_ROOTDIR_ADDRESS;
    unsigned short *fat  = (unsigned short *) VOLUME1_FAT_ADDRESS;
	
    unsigned long i; //deslocamento procurando espaço livre
    unsigned long j; //deslocamento salvando cluster number
    unsigned long c; //Deslocamento na fat ?
    unsigned long endereco;
    

   
    endereco = file_address;
	
	char Entry[32];	//fat16 entry
	
	
	printf("fsSaveFile:\n"); 
	
    //Carrega root e fat.
	
	printf("Loading root..\n"); 
	fs_load_rootdirEx();
	
	printf("loading FAT..\n");
	fs_load_fatEx();
	
	//#debug
	refresh_screen();
	
    
    j = 0;  //Deslocamento na lista, tem que ser zero.
    c = 0;  //Deslocamaento na fat ?
    i = 0;  //Contagem de entradas na fat. Começa do 32 e vai ate muito ... ???

    //procurando cluster livre na fat.
    while(i < fat_range_max)
    {
        //procurando cluster livre na fat.
        //@todo:isso poderia ser uma função.		
        if(fat[c] == 0)
        {
            //encontrado todos os espaços livres que o arquivo precisa.
            if(file_size == 0)
			{
                list[j] = (unsigned short) 0xfff8; //marca o fim         
                goto save_file;
            };    
            
            //salva um endereço livre
            //salvamos um índice na fat dentro da lista			
            list[j] = (unsigned short) c;   
            j++;   //incrementa a lisa

			//decrementa o tamanho do arquivo!
            file_size--;                   
        };
        
        c++; //incrementa o deslocamento na fat. 
        i++; //incrementa a quantidade de busca.
    }; 
  
fail:  
   printf("fsSaveFile: fail - Max entries !");
   refresh_screen();
   while(1){
	   asm("hlt");
   }
   
 
/*
 * Salva o arquivo.
 *     O arquivo tem na lista todos os clusters que ele precisa.
 */  
save_file:

    //#debug
    printf("fsSaveFile: save_file: \n"); 
	 refresh_screen();
  
    i = 0;        //incio da lista
    j = 512*4;    //??max

    
    unsigned short first;
    unsigned short next;
    unsigned short sector;
    
    first = list[i];
    
    
    //
    // salva no diretorio raiz o nome e o primeiro cluster
    //
    //corrige deslocamento.
    // salva_nome(file_name, first); 
 	
	Entry[0] = 'S';
	Entry[1] = 'A';
	Entry[2] = 'V';
	Entry[3] = 'E';
	Entry[4] = 'T';
	Entry[5] = 'E';
	Entry[6] = 'S';
	Entry[7] = 'T';
	
	Entry[8]  = 'T';
	Entry[9]  = 'X';
	Entry[10] = 'T';
	
	Entry[11] = 0x20;
	Entry[12] = 0;
	Entry[13] = 0x3a;
	Entry[14] = 0x27;
	Entry[15] = 0xb6;
	
	Entry[16] = 0xb8;
	Entry[17] = 0x4c;
	Entry[18] = 0xb8;
	Entry[19] = 0x4c;
	Entry[20] = 0;
	Entry[21] = 0;
	Entry[22] = 0xa8;
	Entry[23] = 0x49;
	Entry[24] = 0xb7;
	Entry[25] = 0x4c;
	Entry[26] = 0xaf;
	Entry[27] = 0x05;
	Entry[28] = 0x7a;
	Entry[29] = 0x02;
	Entry[30] = 0;
	Entry[31] = 0;

	
	
	
	// Copia o nome para dentro da entrada do diretório.
	//Obs: #bugbug O numerod a entrada é um teste.
	memcpy( &root[24*16], Entry, 32 );
	
	int xx = ((24*16) +13);
    root[xx] = first;	//*PRIMEIRO SETOR
	
	
	//#debug
	printf("fsSaveFile: reset and while\n"); 
    refresh_screen();
	reset_ide0();
	 
	i=0; 
	while(1)
    {            
         //pega um conteúdo da lista.
        next = list[i];
        
        //salva a trilha indicada pela lista
        // salva_trilha( next, endereco);
        //save_file( 0, endereco, next, 8);
        
        
        //encontrada a assinatura na lista!
        if( next == 0xfff8)
        {
            next = list[i-1];
            fat[next] = 0xfff8;  
            goto done;         
        }else{

            //não é assinatura ainda
			
            //-0x60 = é uma correção por causa valor do tipo (unsigned long)!!
            
			
			//grava na fat o endereço do próximo cluster
            fat[next] = list[i];
            
            //grava - aqui next esta certo!!!
			printf("write_lba\n");
            refresh_screen();
            write_lba( endereco, next);
            
            endereco += 512; 
        }; 
         
         //proximo valor da lista
         i++;
		 
        //limite #test #bugbug
        if(i > 16){
		    goto fail2;       	
		}		
    };
    
	
fail2:	
   // MessageBox("nao encontra assinatura na lista!");
printf("fatseg3: no sig\n");
 refresh_screen();
fatseg3: 
    asm("hlt");
	goto fatseg3;

done:  

    //#debug
    printf("fsSaveFile: reset save root and fat \n");      
    refresh_screen();
	
	reset_ide0();
		
		
    printf("write_lba\n");      
    refresh_screen();		
    //@todo: devemos salvar o root dir.
    write_lba( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA);
    
    printf("write_lba\n");      
    refresh_screen();		
	
	write_lba( VOLUME1_ROOTDIR_ADDRESS + 0x200, VOLUME1_ROOTDIR_LBA + 1);
    //write_lba( VOLUME1_ROOTDIR_ADDRESS + 0x400, VOLUME1_ROOTDIR_LBA + 2);
    //write_lba( VOLUME1_ROOTDIR_ADDRESS + 0x600, VOLUME1_ROOTDIR_LBA + 3);

	//........
	
    printf("write_lba\n");      
    refresh_screen();		
	
    //#bugbug: Devemos salvar ela toda.	
    //salva 4 setores da fat!       
    write_lba( VOLUME1_FAT_ADDRESS, VOLUME1_FAT_LBA);

    printf("write_lba\n");      
    refresh_screen();		
    
	write_lba( VOLUME1_FAT_ADDRESS + 0x200, VOLUME1_FAT_LBA + 1);
    
	//write_lba( VOLUME1_FAT_ADDRESS + 0x400, VOLUME1_FAT_LBA + 2);
    //write_lba( VOLUME1_FAT_ADDRESS + 0x600, VOLUME1_FAT_LBA + 3);

	
    //#debug
    printf("fsSaveFile: done  \n"); 
    refresh_screen();	
    
	return 0;
};



/*
 * fs_save_rootdir:
 *     Salva o diretório raiz no disco.
 *     @todo: Identificar parâmetros do sistema de arquivos atual.
 */
void fs_save_rootdir()
{
	return;
};


/*
 * fs_save_dir:
 *     Salva um diretório.
 */
void fs_save_dir(unsigned long id)
{
	return;
};



/*
 * fs_save_entry_on_root:
 *     Salva uma entrada do diretório raiz, dada
 * a id da estrutura do arquivo.
 * @todo: Checa os parametros do sistema de arquivos e 
 * salva a entrada no diretorio raiz.
 */
void fs_save_entry_on_root(unsigned long eid)
{
    return;
};


void fs_save_structure()
{   
	return;
};

//
// End.
//
