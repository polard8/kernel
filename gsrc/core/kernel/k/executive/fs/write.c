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

//interna
//procura uma entrada vazia no diretório 
int findEmptyDirectoryEntry( unsigned long dir_address, int number_of_entries )
{
	unsigned char *dir = (unsigned char *) dir_address;
	
	
	int i;
	int j=0;
	
	for( i=0; i<number_of_entries; ++i )
	{
		if( dir[j] == 0 )
		{
			return (int) i;
		}
		
		//próxima entrada.
		j = j+32;
	}
	
fail:	
	return (int) (-1);
}


//rotina interna de support.
//isso deve ir para bibliotecas depois.
//não tem protótipo ainda.
// Credits: Luiz Felipe

void write_fntos(char *name)
{
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];
	
    //transforma em maiúscula
	while(*name && *name != '.')
	{
        if(*name >= 'a' && *name <= 'z')
            *name -= 0x20;

        name++;
        ns++;
		
		// ##bugbug: E se não encontrarmos o ponto??
    }

    // aqui name[0] é o ponto.
	// então constroi a extensão.
	for(i=0; i < 3 && name[i+1]; i++)
	{
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    }

    while(ns < 8){
        *name++ = ' ';
        ns++;
    }

    for(i=0; i < 3; i++)
        *name++ = ext[i];

    *name = '\0';
};

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
 *************************************************
 * write_lba:
 *     Grava um setor no disco dado o lba.
 *     
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
		    //hdd.c
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
#define  fat_range_max 4096  

//lista de clusters
unsigned short list[fat_range_max];
 
unsigned long 
fsSaveFile( unsigned char *file_name, 
            unsigned long file_size, 
            char *file_address )  
{
    unsigned short *root = (unsigned short *) VOLUME1_ROOTDIR_ADDRESS;
    unsigned short *fat  = (unsigned short *) VOLUME1_FAT_ADDRESS;

    //unsigned long endereco = file_address;

    unsigned long i = 0; 
    unsigned long j = 0; //Deslocamento na lista, tem que ser zero.
    unsigned long c = 0; //Deslocamento na FAT.
	
    unsigned short first;
    unsigned short next;
    unsigned short sector;
    
	// #provisório.
	// Improvisando uma entrada do tipo fat16.
	char Entry[32];	

    //Mensagem.	
	printf("fsSaveFile:\n"); 
	
    //Carrega root e fat.
rootdir:
	printf("Loading root..\n"); 
	fs_load_rootdirEx();
	
fat:
	printf("loading FAT..\n");
	fs_load_fatEx();
	
	//#debug
	refresh_screen();
	
    
	// Procurando cluster livre na fat.
	// Nesse momento construimos uma lista de clusters livres.
SearchEmptyEntries:
    
	// #bugbug
	// Obs: Esse limite é improvisado.
    while( i < fat_range_max )
    {
        //procurando cluster livre na fat.
        //@todo:isso poderia ser uma função.		
        if(fat[c] == 0)
        {
            // Encontrado todos os espaços livres 
			// que o arquivo precisa.
            if(file_size == 0)
			{
				//Marca o fim.
                list[j] = (unsigned short) 0xfff8;          
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
  
out_of_range:  
   printf("fsSaveFile: out_of_range - Max entries !");
   refresh_screen();
   while(1){
	   asm("hlt");
   }
   
// Salva o arquivo.
//     O arquivo tem na lista todos os clusters 
// que ele precisa.

save_file:

    //#debug
    printf("fsSaveFile: save_file: \n"); 
	refresh_screen();
  
    // Início da lista.
    i = 0; 

	// #bugbug
	// Limite máximo improvisado.
    j = 512*4;    
 
    // Pegamos o primeiro da lista.
    first = list[i];
	
	printf("first={%x}\n",first);
    
    // #improvisando
	// #provisório
    // Salva no diretório raiz o nome e o 
	// primeiro cluster
    
    // @todo: Usar uma função.
	// poderá ser uma função interna.
    // salva_nome(file_name, first); 
 	
	//Entry[0] = 'S';
	//Entry[1] = 'A';
	//Entry[2] = 'V';
	//Entry[3] = 'E';
	//Entry[4] = 'T';
	//Entry[5] = 'E';
	//Entry[6] = 'S';
	//Entry[7] = 'T';
	//Entry[8]  = 'T';
	//Entry[9]  = 'X';
	//Entry[10] = 'T';
	
	Entry[0] = (char) file_name[0];
	Entry[1] = (char) file_name[1];
	Entry[2] = (char) file_name[2];
	Entry[3] = (char) file_name[3];
	Entry[4] = (char) file_name[4];
	Entry[5] = (char) file_name[5];
	Entry[6] = (char) file_name[6];
	Entry[7] = (char) file_name[7];
	Entry[8]  = (char) file_name[8];
	Entry[9]  = (char) file_name[9];
	Entry[10] = (char) file_name[10];
	
	
	Entry[11] = 0x20;  //atributo. 0x20=arquivo.  
	Entry[12] = 0;     //reservado.  
	
	//creation time 14 15 16
	Entry[13] = 0x08; 
	Entry[14] = 0x08; 
	Entry[15] = 0xb6;
	
	//creation date
	Entry[16] = 0xb8;
	Entry[17] = 0x4c;
	
	//acess date
	Entry[18] = 0xb8;
	Entry[19] = 0x4c;
	
	//first cluster. 0 para fat12 ou 16
	Entry[20] = 0;
	Entry[21] = 0;
	
	//modifield time
	Entry[22] = 0xa8;
	Entry[23] = 0x49;
	
	//modifiled date
	Entry[24] = 0xb7;
	Entry[25] = 0x4c;
	
	//first cluster low word.
	Entry[26] = (char) (first);        //0x1A
	Entry[27] = (char) (first >> 8);   //0x1B 
	
	//file size (bytes ??)
	Entry[28] = 0xff;
	Entry[29] = 0;
	Entry[30] = 0;
	Entry[31] = 0;

	
	//
	// root[]
	// #importante: root[] é um array de short.
	//
	
	// Copia o nome para dentro da entrada do diretório.
	// Obs: #bugbug O número da entrada é improvisado.
	// Temos que fazer um rotina que encontre uma entrada livre 
	// no diretório.
	
	// Obs: As entradas são de 32 bytes. Como root[] é um 
	// array de short então faremos um deslocamento de 16 shorts.
	//int xxxx_entryindex = 24;

	//address e número máximo de entradas.
	int xxxx_entryindex = (int) findEmptyDirectoryEntry( VOLUME1_ROOTDIR_ADDRESS,128);
	if(xxxx_entryindex == -1)
	{
		printf("No empty entry.\n");
		goto fail;
	}
	
	
	int xxxx_entrysize = 16;
	
	
	//Copia 32bytes.
	int xxxx = (int) ( xxxx_entryindex * xxxx_entrysize );
	memcpy( &root[xxxx], Entry, 32 );

	
resetIDE:

	//#debug
	printf("fsSaveFile: reset and while\n"); 
    refresh_screen();
	reset_ide0();
	
	
	//
	// ## Save ##
	//

	i=0; 
	
	//#debug 
	//improvisando um endereço válido
	unsigned long address = (unsigned long) file_address;
	
SavingFile:	

	while(1)
    {            
        //Pega um conteúdo da lista.
        next = list[i];
		
		printf("next={%x}\n",next);
                
        //encontrada a assinatura na lista!
        if( next == 0xfff8)
        {
            next = list[i-1];
            fat[next] = 0xfff8;  
            goto done;         
        }else{

            //não é assinatura ainda
			
			//grava na fat o endereço do próximo cluster
            fat[next] = list[i+1];
            
            //grava - aqui next esta certo!!!
			printf("write_lba\n");
            refresh_screen();
            write_lba( (unsigned long) address, VOLUME1_DATAAREA_LBA + next -2 );
            
            address += 512; 
        }; 
         
         //próximo valor da lista
        i++;
		 
        //limite #test #bugbug
		//limitando o tamanho do arquivo a 16 entradas.
        if(i > 16){
		    goto fail;       	
		}		
    };
    
	
fail:	
    printf("  ## FAIL ## \n");
    refresh_screen();
    return 1;

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
    
	
	
    printf("write_lba  ... tentando salvar fat\n");      
    refresh_screen();		

	
	int f;
    int off = 0;
    int lbaoff = 0;	
	for( f=0; f<8; f++ )
	{
	   //#bugbug:
       //pelo jeito a rotina de salvamento precisa de 
       //de um wait ... um sleep  ... eu checar a interrupção. 	   
       printf("write_lba n={%d} \n",f);      
       refresh_screen();		
	
	   write_lba( VOLUME1_FAT_ADDRESS + off, 
	              VOLUME1_FAT_LBA     + lbaoff );
				  
       off = off + 0x200;
       lbaoff = lbaoff + 1;	   
	}
	

    
	//write_lba( VOLUME1_FAT_ADDRESS + 0x200, VOLUME1_FAT_LBA + 1); 
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
