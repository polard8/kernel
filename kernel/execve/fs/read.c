/*
 * File: fs/read.c 
 *
 * Descrição:
 *     Rotinas de leitura
 *     As rotinas na biblioteca C devem chamar essas funções.
 *
 * History:
 *    2015 - Created by Fred nora.
 *    2016~2018 - Revision.
 *    ...
 */
 
 
/*
 #todo: 
     Usar estruturas para gerenciar partição, FAT e Root dir.
 #obs: 
     Cada partição deve ter uma estrutura.
 precisamos checar na estrutura o status da FAT e do 
 diretório raiz, para não carregálos repetidas vezes.
 */ 
 
 
#include <kernel.h>


/*
 ************************************************
 * read_fntos:
 *     rotina interna de support.
 *     isso deve ir para bibliotecas depois.
 *     não tem protótipo ainda.
 * Credits: Luiz Felipe
 */
 
void read_fntos ( char *name ){
	
    int  i, ns = 0;
    char ext[4];
	
	ext[0] = 0;
	ext[1] = 0;
	ext[2] = 0;
	ext[3] = 0;
	
    //const char ext[4];
	
    //Transforma em maiúscula enquanto não achar um ponto.
	
	while ( *name && *name != '.' )
	{
        if ( *name >= 'a' && *name <= 'z' )
            *name -= 0x20;

        name++;
        ns++;
    };

    // Aqui name[0] é o ponto.
	// Então constrói a extensão.
	
	for ( i=0; i < 3 && name[i+1]; i++ )
	{
		//Transforma uma letra da extensão em maiúscula.
        
		//if (name[i+1] >= 'a' && name[i+1] <= 'z')
        //    name[i+1] -= 0x20;

        //ext[i] = name[i+1];
    
	
	    //#testando
	    //Se não for letra então não colocamos no buffer de extensão;
		if (name[i+1] >= 'a' && name[i+1] <= 'z')
		{
			name[i+1] -= 0x20;
		    ext[i] = name[i+1];
		}
	};

	//Acrescentamos ' ' até completarmos as oito letras do nome.
	
    while (ns < 8)
	{	
        *name++ = ' ';
        ns++;
    };

	//Acrescentamos a extensão
	
    for (i=0; i < 3; i++)
        *name++ = ext[i];

    *name = '\0';
}
	
	
/*
 ***********************
 * fatClustToSect:
 *     Calcula qual é o setor inicial de um dado cluster.
 *     Informações para o calculo: 
 *     ~ Número do cluster.
 *     ~ Número de setores por cluster.
 *     ~ Lba inicial da area de dados.
 */	
 
unsigned long 
fatClustToSect ( unsigned short cluster, 
                 unsigned long spc, 
				 unsigned long first_data_sector )
{
    unsigned long C = (unsigned long) cluster;

	C -= 2;
	
	//@todo: Check limits.
	
	return (unsigned long) (C * spc) + first_data_sector;
};


/*
 *************************************************************
 * fatLoadCluster:
 *     Carrega um cluster.
 *     Argumentos:
 *         setor   ~ Primeiro setor do cluster.
 *         address ~ Endereço do primeiro setor do cluster.
 *         spc     ~ Número de setores por cluster.
 * Começa do primeiro setor do cluster.
 */
 
void 
fatLoadCluster ( unsigned long sector, 
                 unsigned long address, 
				 unsigned long spc )
{
	unsigned long i;
	
	for ( i=0; i < spc; i++ ){
		
        read_lba ( address, sector + i );
		address = address +512; 
	}
};


/*
 *****************************************************************
 * read_lba:
 *     Carrega um um setor na memória, dado o LBA.
 *     Obs: Talvez essa rotina tenha que ter algum retorno no caso de falhas.
 */
 
void read_lba ( unsigned long address, unsigned long lba ){
	
 	//taskswitch_lock();
	//scheduler_lock();	          	
	
    switch (fatbits){
		
	    case 32:
	        //Nothing.	    
            return;
			break;		
			
	    case 16:
		    //hdd.c
	        my_read_hd_sector ( address, lba, 0, 0 );	    
            return;
			break;		
			
	    case 12:
	        //Nothing.	    
            return;
			break;

        default:
		    //@todo: 
			// Precisamos fazer alguma coisa se essa variável for 
			// um valor inválido.
		    //return;
            break;		
	};	
	
	//scheduler_unlock();
	//taskswitch_unlock();
}


/*
 **************
 * fsLoadFile:
 *    Carrega um arquivo na memória dado o nome e o endereço.
 *    Apenas FAT16.
 *
 *  @todo: 
 *      Deve-se alocar memória dinamicamente para o root dir e 
 * para a fat caso eles não estejam carregados e não tenham seus 
 * endereços salvos.
 * Obs: Pode existir uma estrutura pra dizer se o root dir e fat estão 
 * carregados na memória e qual o endereço o tipo o tamanho etc.
 * + O argumento nome poderia ser const char* para compatibilidade 
 * com a libC.
 *
 * #obs: A fat deve estar o tempo todo na memória, mas precisamos carregar 
 * na memória o dretório atual para lermos um arquivo.
 * Essa função de leitura não precisa carregar a FAT toda vez que for chamada.
 * ela deve apenas checar se a fat está na memória através de uma flag.
 * Mas essa função precisa carregar o diretório atual na memória para 
 * procurar pelo nome indicado.
 * #bugbug: No momento estamos apenas procurando no diretório raiz, 
 * então devemos substituir o ponteiro *root por *current_dir.
 * IN:
 *     Endereço do diretório, 
 *     Nome do arquivo, 
 *     Endereço do arquivo.
 */

unsigned long 
fsLoadFile ( unsigned long fat_address,
			 unsigned long dir_address,
             unsigned char *file_name, 
             unsigned long file_address )			 
{
    int Status;		
	int i;
    unsigned short next;

    unsigned long max = 64;    //?? @todo: rever. Número máximo de entradas.
    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.
	char NameX[13];	           //??Nome. 

	unsigned short cluster;    //Cluster inicial

	//?? Primeiro setor do cluster.
	unsigned long S;  
	
	int Spc;
	
	// Updating fat address and root address.
	
	unsigned short *fat = (unsigned short *) fat_address;   
	unsigned short *root = (unsigned short *) dir_address;
	
	
	// Lock ??.
	
	//taskswitch_lock();
	//scheduler_lock();	
	
	// Root dir.

//loadRoot:
	
	//Carrega o diretório raiz na memória.
	
#ifdef KERNEL_VERBOSE	
	printf("fsLoadFile: Loading root..\n"); 
#endif	
	
	//#test
	//funcionou
	//carregando o diretório 
	//address, lba, number of sectors.
	
	load_directory ( dir_address, VOLUME1_ROOTDIR_LBA, 32 );
    //load_directory ( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );	
	
	//antigo.  
	//funciona
	//carregando o diretório raiz.
	//fs_load_rootdirEx ();
	
	//#todo:
	//precisamos na verdade carregarmos o diretório corrente.
	
	
	//Checa se é válida a estrutura do sistema de arquivos.
	
	if ( (void *) filesystem == NULL )
	{
	    printf("fs-read-fsLoadFile: filesystem\n");
		goto fail;
	
	}else{
		
	    //Setores por cluster.
	    Spc = filesystem->spc;
		
	    if (Spc <= 0)
		{
	        printf("fs-read-fsLoadFile: Spc\n");
		    goto fail;
	    };
	
	    //Max entries ~ Número de entradas no rootdir.
		//#bugbug: Devemos ver o número de entradas no diretório corrente.
	    max = filesystem->rootdir_entries;	
		
	    if (max <= 0)
		{
	        printf("fs-read-fsLoadFile: max\n");
			goto fail;
	    };
		
	    // More?! 
		// ...
	};
	
	// Continua ... 
	// Pegar mais informações sobre o sistema de arquivos.
	
	
    /*
	 * Busca simples pelo arquivo no diretório raiz.
	 *
	 * @todo: Essa busca pode ser uma rotina mais sofisticada. Uma função
	 * auxiliar.
	 */

    /*
	 * Primero caractere da entrada:
	 *   0 = entrada vazia.
	 *   $ = entrada de arquivo deletado.
	 *   outros ...
	 *
	 *  ATENÇÃO:
     *      Na verdade a variável 'root' é do tipo short.	 
	 */
	 
	i = 0; 
	
	// Procura o arquivo no diretório raiz.
	
//search_file:

    size_t size = (size_t) strlen (file_name); 
	
	//Compara.
	while ( i < max )
	{
		//Se a entrada não for vazia.
		if ( root[z] != 0 )
        {
			// Copia o nome e termina incluindo o char 0.
			memcpy( NameX, &root[z], size );
			NameX[size] = 0;
			
            // Compara 11 caracteres do nome desejado, 
			// com o nome encontrado na entrada atual.
			Status = strncmp ( file_name, NameX, size );
			
            if ( Status == 0 ){ 
			    goto found; 
			}
			// Nothing.
        }; 
		
		//(32/2) próxima entrada! (16 words) 512 vezes!
        z += 16;    
        i++;        
    }; 
	
	// Sai do while. O arquivo não foi encontrado.
	
    // O arquivo não foi encontrado.	
//notFound:
    printf ("fs-read-fsLoadFile: %s not found\n", file_name );  
    //printf ("fs-read-fsLoadFile: %s not found\n", NameX );
	//printf("root: %s ",root);	
    goto fail;
	
    // O arquivo foi encontrado.	
found:

    // #debug
    // printf("arquivo encontrado\n");
    // refresh_screen();
	// while(1){}
	
    //Pega o cluster inicial. (word)
	cluster = root[ z+13 ];    //(0x1A/2) = 13.	
	
	
	// Cluster Limits.
	// Checar se 'cluster' está fora dos limites.
	// +São 256 entradas de FAT por setor. 
	// +São 64 setores por FAT. 
	// Isso varia de acordo com o tamanho do disco.
	// O número máximo do cluster nesse caso é (256*64).
	
	if ( cluster <= 0 || cluster > 0xfff0 ){
		
	    printf("fs-read-fsLoadFile: Cluster limits %x \n", cluster );
		goto fail;
	}	
	
	
//loadFAT:
	
    //Carrega fat na memória.
	
#ifdef KERNEL_VERBOSE		
	printf("loading FAT..\n");
#endif 
	
	//=============================
	//#bugbug: 
	//Não devemos carregar a FAT na memória toda vez que 
	//formos carregar um arquivo. 
	//Talvez ela deva ficar sempre na memória.
	//precisamos de estruturas para volumes que nos dê esse tipo de informação
	
	fs_load_fatEx();
	
    // Carregar o arquivo, cluster por cluster.
    // @todo: Por enquanto, um cluster é igual à um setor, 512 bytes.
 
    //Debug:
#ifdef KERNEL_VERBOSE		
    printf ("Loading clusters..\n");
    //refresh_screen();
#endif

	// Loop: 
	//     Loop de entradas na FAT.
    //     @todo: Esse loop é provisório, while pode ser problema.
	
	//
	// Carregar o arquivo.
	//
	
//Loop.	
next_entry:
	
	/*
	while(1)
	{	
	    //Calcula.
		//Primeiro setor do cluster. 
		S = fatClustToSect(cluster, Spc, VOLUME1_DATAAREA_LBA); 
		
		//Carrega 'x' setores começando de S.
		fatLoadCluster( S, file_address, Spc);
		
		//Pegar o próximo cluster na FAT.
		//O cluster atual contém o número do próximo.
		cluster = fat[cluster];
		
		//Ver se o cluster carregado era o último.
	    if(cluster == 0xFFFF || cluster == 0xFFF8){ goto done; };
		//Nothing.
    };
	*/
	
	read_lba ( file_address, VOLUME1_DATAAREA_LBA + cluster -2 ); 
	
	//Incrementa o buffer. +512;
	//SECTOR_SIZE;
	file_address = (unsigned long) file_address + 512;    	
	
	
	//Pega o próximo cluster na FAT.
	next = (unsigned short) fat[cluster];		
	
	//Configura o cluster atual.
	cluster = (unsigned short) next;	
	
	//Ver se o cluster carregado era o último cluster do arquivo.
	if ( cluster == 0xFFFF || cluster == 0xFFF8 ){ 
	    goto done; 
	}

	// ## Loop ## 
	// Vai para próxima entrada na FAT.
	
	goto next_entry;
	
	//Nothing.
	
//Falha ao carregar o arquivo.
fail:
    printf ("fs-read-fsLoadFile fail: file={%s}\n", file_name );	
    refresh_screen ();
	return (unsigned long) 1;
	
//Done. 	
done:
    
	//#debug support
	//printf("fsLoadFile: done\n");
	//refresh_screen(); 
    
	return (unsigned long) 0;
};


/*
 ****************************************
 * fs_load_fatEx:
 *    Carrega a fat na memória.
 *    Sistema de arquivos fat16.
 *    ? qual disco ?
 *    ? qual volume ? 
 *    #obs: Essa rotina poderia carregar a fat do volume atual do 
 * disco atual. É só checar na estrutura.
 *
 * current disk, current volume, fat status.
 *
 * +se o status da fat para o vulume atual indicar que ela já está carregada,
 *  então não precisamos carregar novamente.
 */
void fs_load_fatEx (){
	
	unsigned long i;
	unsigned long b = 0;
	
	//#bugbug 
	//Estamos atribuindo um tamanho, mas tem que calcular.
	unsigned long szFat = 128;
	
	
	//#todo:
	//+checar qual é o disco atual.
	//+checar qual é o volume atual.
	//+checar o status da FAT. Talvez ela já esteja na memória.
	//obs: a estrutura deve informar onde está a fat do volume,
	//caso ja esteja na memória.
	//obs: padronizaremos alguns endereços, e alocaremos outros.
	
	//Carregar root dir na memória.
	for ( i=0; i < szFat; i++ )
	{
		my_read_hd_sector( VOLUME1_FAT_ADDRESS + b, VOLUME1_FAT_LBA + i, 0 , 0 );
		
		//Incrementa buffer.
		b = b+512;    
	};
};



/*
 ***********************************************************
 * load_directory:
 *    Carrega o diretório na memória, dados o endereço, 
 * o lba inicial e o número de setores.
 */
 
void 
load_directory ( unsigned long address, 
                 unsigned long lba, 
				 unsigned long sectors )
{
	unsigned long i;
	unsigned long b = 0;
	
	for ( i=0; i < sectors; i++ )
	{
        my_read_hd_sector ( address + b, lba + i, 0, 0 );
		
		b = b+512;    
	}
};


/*
 ********************************************************
 * fs_load_rootdirEx:
 *    Carrega o diretório raiz na memória.
 *    Sistema de arquivos fat16.
 *    ? qual disco ?
 *    ? qual volume ? 
 *
 * #importante:
 * O tamanho do diretório raiz é padronizado.
 * mas é importante calcularmos o tamanho do diretório a ser carregado 
 * para podermos carregar outros diretórios.
 * O tamanho do diretório fica registrado em sua entrada e deve ser 
 * estar realcionado com o tanto de entradas no diretório.
 * Quando um diretório é criado, devemos colocar na sua entrada o tamanho 
 * do diretório.
 */
void fs_load_rootdirEx (){
	
	//#bugbug:
	//Não sabemos qual é o volume e qual é o disco atual.
	//precisamo consultar qual é o disco atual e qual 
	//é o volume atual.
	//na estrutura de volume deve ter a informação sobre 
	//qual é a lba do diretório raiz do volume.
	//Já o endereço pode ser padronizado para todos os volumes.	
	
	
	load_directory ( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );
	
	//#obs
	//deixaremos comentado aqui o jeito antigo, por enquanto.
	
	/*
	unsigned long i;
	unsigned long b = 0;
	unsigned long szRoot = 32;
	
	//Carregar root dir na memória.
	for ( i=0; i < szRoot; i++ )
	{
	    //read_lba( VOLUME1_ROOTDIR_ADDRESS + b, VOLUME1_ROOTDIR_LBA + i );
        my_read_hd_sector ( VOLUME1_ROOTDIR_ADDRESS + b, VOLUME1_ROOTDIR_LBA + i, 0, 0 );
		
		//Incrementa buffer.
		b = b+512;    
	};
	*/
};


void fs_load_rootdir (){
	
	//#bugbug:
	//Não sabemos qual é o volume e qual é o disco atual.
	//precisamo consultar qual é o disco atual e qual 
	//é o volume atual.
	//na estrutura de volume deve ter a informação sobre 
	//qual é a lba do diretório raiz do volume.
	//Já o endereço pode ser padronizado para todos os volumes.
	
    load_directory ( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );	
}; 


/*
 * fs_load_dir:
 *     Carrega um dado diretório da lista de arquivos, 
 * dado o índice da lista de streams do kernel.
 */
 
void fs_load_dir ( unsigned long id ){
	
	unsigned long i;
	unsigned long n = 0;
	unsigned long lba;
	
    FILE *f;
	
	
	//#todo:
	//+checar qual é o disco atual.
	//+checar qual é o volume atual.	
	

	f = (void *) Streams[id];	
	
	if ( (void *) f == NULL )
	{
	    printf("fs_load_dir fail: Struct\n");
	    return;
	}
	
	//??
	//Podemos pegar o nome do arquivo na estrutura 
	//a arregar ele com fopen.
	//f->name
};



//
// ==============================
//



unsigned long fsGetFileSize ( unsigned char *file_name ){
	
    int Status;		
	int i;
    unsigned short next;
	
	unsigned long FileSize = 0;
	
    unsigned long max = 64;    //?? @todo: rever. Número máximo de entradas.
    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.
	char NameX[13];	           //??Nome. 

	// #importante:
	// Poderíamos usar malloc ou alocador de páginas ??	
    // A FAT permanece a mesma para a situaçãod e termos apenas uma partição.
	//mas se tivermos mai de uma partição também precisamos carregar a FAT 
	//da partição atual.
	//unsigned short *fat = (unsigned short *) VOLUME1_FAT_ADDRESS;
	unsigned short cluster;    //Cluster inicial

    //??	
	unsigned long S;  //Primeiro setor do cluster.
	int Spc;

	// #importante:
	// Poderíamos usar malloc ou alocador de páginas ??
	// #todo: Devemos carregar o diretório atual.
    unsigned short *root = (unsigned short *) VOLUME1_ROOTDIR_ADDRESS;

	// #todo: Devemos carregar o diretório atual.
	//unsigned long current_dir_address = (unsigned long) Newpage();
    //#todo: devemos checar se o endereço é válido.
	//unsigned short *current_dir = (unsigned short *) current_dir_address;	
	// #todo: devemos chamar uma função que carregue um diretório no endereço passado 
	//via argumento.
    //...
	
	// Lock ??.
	
	//taskswitch_lock();
	//scheduler_lock();	
		
	// Root dir.

//loadRoot:
	
	//Carrega o diretório raiz na memória.
	
#ifdef KERNEL_VERBOSE	
	printf("fsGetFileSize: Loading root..\n"); 
#endif	
	
	//carregando o diretório raiz.
	load_directory ( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );	
	//fs_load_rootdirEx ();
	
	//#todo:
	//precisamos na verdade carregarmos o diretório corrente.
		

	
	// Continua ... 
	// Pegar mais informações sobre o sistema de arquivos.
	
	//#obs
	//Checa se é válida a estrutura do sistema de arquivos.
    //A intenção é obtermos a quantidade de entradas no diretório raiz.
	//#bugbug: Mas isso deveria ser feito para o diretório atual.
	
	if ( (void *) filesystem == NULL )
	{
	    printf("fsGetFileSize: filesystem\n");
		goto fail;
	
	}else{
		
	    //Setores por cluster.
	    Spc = filesystem->spc;
		
	    if (Spc <= 0)
		{
	        printf("fsGetFileSize: Spc\n");
		    goto fail;
	    };
	
	    //Max entries ~ Número de entradas no rootdir.
		//#bugbug: Devemos ver o número de entradas no diretório corrente.
	    max = filesystem->rootdir_entries;	
		
	    if (max <= 0)
		{
	        printf("fsGetFileSize: max\n");
			goto fail;
	    };
		
	    // More?! 
		// ...
	};

	
	//Busca simples pelo arquivo no diretório raiz.
	//todo: Essa busca pode ser uma rotina mais sofisticada. 
	//Uma função auxiliar.

	//Primero caractere da entrada:
	//0 = entrada vazia.
	//$ = entrada de arquivo deletado.
	//outros ...
	//ATENÇÃO:
    //Na verdade a variável 'root' é do tipo short.	 

	i = 0; 
	
	// Procura o arquivo no diretório raiz.
	
//search_file:

    size_t size = (size_t) strlen (file_name); 
	
	//Compara.
	while ( i < max )
	{
		//Se a entrada não for vazia.
		if ( root[z] != 0 )
        {
			// Copia o nome e termina incluindo o char 0.
			memcpy( NameX, &root[z], size );
			NameX[size] = 0;
			
            // Compara 11 caracteres do nome desejado, 
			// com o nome encontrado na entrada atual.
			Status = strncmp ( file_name, NameX, size );
			
            if ( Status == 0 ){ 
			    goto found; 
			}
			// Nothing.
        }; 
		
		//(32/2) próxima entrada! (16 words) 512 vezes!
        z += 16;    
        i++;        
    }; 
	
	// Sai do while. O arquivo não foi encontrado.
	
    // O arquivo não foi encontrado.	
//notFound:
    printf ("fsGetFileSize: %s not found\n", file_name );  

//Falha ao carregar o arquivo.
fail:
    printf ("fsGetFileSize: file={%s}\n", file_name );	
    refresh_screen ();
	return (unsigned long) 0;
	
found:

    // #debug
    // printf("arquivo encontrado\n");
    // refresh_screen();
	// while(1){}
	
    //Pega o cluster inicial. (word)
	//cluster = root[ z+13 ];    //(0x1A/2) = 13.	
	
	//#debug
	//pegando o tamanho do arquivo.
    // 28 29 30 31

    FileSize = *(unsigned long*) (VOLUME1_ROOTDIR_ADDRESS + (z*2) + 28 );	
	
	//printf ("%d \n" , root[ z+14 ]);
	//printf ("%d \n" , root[ z+15 ]);
	//printf ("FileSize=%d \n" , FileSize);

	
	//#debug
	//refresh_screen();
	//while(1){
	//	asm("hlt");
	//}
	
	return (unsigned long) FileSize;
};


//
// =========
//

 
 
//
// End.
//

