/*
 * File: fs\read.c 
 *
 * Descrição:
 *     Rotinas de leitura
 *
 * Obs:
 *    As rotinas na biblioteca C devem chamar essas funções.
 * Histórico:
 *    Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *    Versão 1.0: 2016 - Revisão.
 *    ...
 */
 
 
#include <kernel.h>

    /*
	 * Teste: Funcionou, leu um arquivo.
	printf("*teste ...\n");
	refresh_screen();
	unsigned long buf[32];
	printf("Loading ...\n");
	carregar_arquivo("FREDFILETXT",(unsigned long) buf);
	printf("Showing ...\n");
    printf("%s\n",buf);  			
	printf("*done.");
	refresh_screen();
	while(1){}
	*/



	
/*
 * fatClustToSect:
 *     Calcula qual é o setor inicial de um dado cluster.
 *     Informações para o calculo: 
 *     ~ Número do cluster.
 *     ~ Número de setores por cluster.
 *     ~ Lba inicial da area de dados.
 */	
unsigned long fatClustToSect(unsigned short cluster, 
                             unsigned long spc, 
							 unsigned long first_data_sector )
{
    unsigned long C = (unsigned long) cluster;

	C -= 2;
	
	//@todo: Check limits.

done:	
	return (unsigned long) (C * spc) + first_data_sector;
};


/*
 * fatLoadCluster:
 *     Carrega um cluster.
 *     Argumentos:
 *         setor   ~ Primeiro setor do cluster.
 *         address ~ Endereço do primeiro setor do cluster.
 *         spc     ~ Número de setores por cluster.
 */
void fatLoadCluster(unsigned long sector, unsigned long address, unsigned long spc)
{
	unsigned long i;

	//Começa do primeiro setor do cluster.	
	for( i = 0; i < spc; i++){
        read_lba( address, sector + i );
		address = address +512; 
	};
done:
	return;
};


/*
 * read_lba:
 *     Carrega um um setor na memória, dado o LBA.
 *     fsReadLBA(..)
 *     Obs: Talvez essa rotina tenha que ter algum retorno no caso de falhas.
 */
void read_lba( unsigned long address, unsigned long lba)
{
    //Obs: 'fatbits' é uma variável global??
	
 	//taskswitch_lock();
	//scheduler_lock();	          	
	
    switch(fatbits)
    {
	    case 32:
	        //Nothing.	    
            return;
			break;		
			
	    case 16:
	        my_read_hd_sector( address, lba, 0, 0);	    
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
		    return;
            break;		
	};	
	
	//scheduler_unlock();
	//taskswitch_unlock();
	
done:
	return;
};


/*
 * fsLoadFile:
 *    Carrega um arquivo na memória dado o nome e o endereço.
 *    Apenas FAT16.
 *
 *  @todo: 
 *      Deve-se alocar memória dinamicamente para o root dir e para a fat
 *  caso eles não estejam carregados e não tenham seus endereços salvos.
 *   Obs:   Pode existir uma estrutura pra dizer se o root dir e fat estão 
 * carregados na memória e qual o endereço o tipo o tamanho etc.
 *
 */
//unsigned long fsLoadFile( unsigned char *name, unsigned long address) 
unsigned long fsLoadFile( unsigned char *file_name, unsigned long file_address)
{
    int Status;	
	
	int i;
    unsigned short next;

    unsigned short *root = (unsigned short *) FAT16_ROOTDIR_ADDRESS;
    unsigned long max = 64;    //Número máximo de entradas.
    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.
	char NameX[13];	

    unsigned short *fat  = (unsigned short *) FAT16_FAT_ADDRESS;
	unsigned short cluster;    //Cluster inicial

    //??	
	unsigned long S;  //Primeiro setor do cluster.
	int Spc;

    //...
	
	//
	// Lock ??.
	//
	
	//taskswitch_lock();
	//scheduler_lock();	
	
	//
	// Root dir.
	//

//loadRoot:
	
	//Carrega o diretório raiz na memória.
	printf("fsLoadFile: Loading root..\n"); 
	fs_load_rootdirEx();
	
	//Checa se é válida a estrutura do sistema de arquivos.
	if( (void*) filesystem == NULL )
	{
	    printf("fsLoadFile error: Struct.");
		refresh_screen();
		while(1){}
	}
	else
	{
	    //Setores por cluster.
	    Spc = filesystem->spc;
	    if(Spc <= 0){
	        printf("fsLoadFile error: Spc.");
		    refresh_screen();
		    while(1){}
	    };
	
	    //Max entries ~ Número de entradas no rootdir.
	    max = filesystem->rootdir_entries;	
	    if(max <= 0){
	        printf("fsLoadFile error: Root entries.");
		    refresh_screen();
		    while(1){}
	    };
		
	    //More?! 
	};
	
	
	//
	// Continua ... 
	// Pegar mais informações sobre o sistema de arquivos.
	//
	
	
    /*
	 * Busca simples pelo arquivo no diretório raiz.
	 *
	 * @todo: Essa busca pode ser uma rotina mais sofisticada. Uma função
	 * auxiliar.
	 *
	 */

    /*
	 * Primero caractere da entrada:
	 *   0 = entrada vazia.
	 *   $ = entrada de arquivo deletado.
	 *   outros ...
	 *
	 *  ATENÇÃO:
     *      Na verdade a variável 'root' é do tipo short.
     *		 
	 */
	 
	i = 0; 
	
	// Procura o arquivo no diretório raiz.
//search_file:
	
	//Compara.
	while(i < max)
	{
		if(root[z] != 0)
        {
			//Copia o nome e termina incluindo o char 0.
			memcpy( NameX, &root[z], 11);
			NameX[11] = 0;
			
            // Compara 11 caracteres do nome desejado, 
			// com o nome encontrado na entrada atual.
			Status = strncmp(file_name, NameX, 11);
            if(Status == 0){ goto found; };
			//Nothing.
        }; 
		
		//(32/2) próxima entrada! (16 words) 512 vezes!
        z += 16;    
        ++i;        
    }; 
	
	
	//
	// Sai do while. O arquivo não foi encontrado.
	//
	
notFound:
    printf("fsLoadFile: %s not found!\n",file_name);     
    goto fail;
found:
   // printf("arquivo encontrado\n");
   	
	//debug
    //refresh_screen();
	//while(1){}
	
    //Pega o cluster inicial. (word)
	cluster = root[ z+13 ];    //(0x1A/2) = 13.	
	
	
	
	/*
	 * Checar se cluster está fora dos limites.
	 * São 256 entradas de FAT por setor. 
	 * São 64 setores por FAT. 
	 * Isso varia de acordo com o tamanho do disco.
	 * O número máximo do cluster nesse caso é (256*64).
	 */
	 
	//Cluster Limits. 
	if( cluster <= 0 || cluster > (0xfff0) ){
	    printf("fsLoadFile error: Cluster limits {%x}!\n",cluster);
		goto fail;
	};	
	
	
//loadFAT:
	
    //Carrega fat na memória.
	printf("loading FAT..\n");	
	fs_load_fatEx();
	
    /*
     * Carregar o arquivo, cluster por cluster.
     * @todo: 
	 *     Por enquanto, um cluster é igual à um setor, 512 bytes.
     */
 
    //Debug:
    printf("Loading clusters..\n");
    //refresh_screen();

    //
	// Loop: 
	//     Loop de entradas na FAT.
    //     @todo: Esse loop é provisório, while pode ser problema.
	//
	
	
	//
	// Carregar o arquivo.
	//
	
//Loop.	
proxima_entrada:
	
	/*
	while(1)
	{	
	    //Calcula.
		//Primeiro setor do cluster. 
		S = fatClustToSect(cluster, Spc, FAT16_DATAAREA_LBA); 
		
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
	
	read_lba( file_address, FAT16_DATAAREA_LBA + cluster -2 ); 
	
	//Incrementa o buffer. +512;
	file_address = (unsigned long) file_address + 512; //SECTOR_SIZE;  	
	
	
	
	//Pega o próximo cluster na FAT.
	next = (unsigned short) fat[cluster];		
	
	
	//Configura o cluster atual.
	cluster = (unsigned short) next;	
	
	//Ver se o cluster carregado era o último cluster do arquivo.
	if(cluster == 0xFFFF || cluster == 0xFFF8){ goto done; };

	//
	// Loop: 
	// Vai para próxima entrada na FAT.
	//
	
	goto proxima_entrada;	
	//Nothing.
	
//Falha ao carregar o arquivo.
fail:
	//scheduler_unlock();
	//taskswitch_unlock();
    printf("fsLoadFile fail: file={%s}!\n",file_name);	
    refresh_screen();
	//taskswitch_unlock();
	return (unsigned long) 1;
//Done. 	
done:
    //printf("fsLoadFile: done\n");
	refresh_screen(); 
	//scheduler_unlock();
	//taskswitch_unlock();
	//taskswitch_unlock();
    return (unsigned long) 0;
};



/*
 * KiLoadRootDir:
 *    Carrega o diretório raiz na memória.
 */
void KiLoadRootDir(unsigned long address)
{
	unsigned long i;
	unsigned long b = 0;
	unsigned long szRoot = 32;    //32 setores.
	
	//Carregar root dir na memória.
	for( i=0; i < szRoot; i++){
	    read_lba( address + b, FAT16_ROOTDIR_LBA + i);    
		b = b+512;    //Incrementa buffer.
	};
done:	
    return;
};


/*
 * fs_load_rootdirEx:
 *    Carrega o diretório raiz na memória.
 */
void fs_load_rootdirEx()
{
	unsigned long i;
	unsigned long b = 0;
	unsigned long szRoot = 32;
	
	//Carregar root dir na memória.
	for( i=0; i < szRoot; i++){
	    read_lba( FAT16_ROOTDIR_ADDRESS + b, FAT16_ROOTDIR_LBA + i);    
		b = b+512;    //Incrementa buffer.
	};
done:	
    return;
};


/*
 * fs_load_fatEx:
 *    Carrega a fat na memória.
 */
void fs_load_fatEx()
{
	unsigned long i;
	unsigned long b = 0;
	unsigned long szFat = 64;    //64 Setores de tamanho.(@todo: variável global)
	
	//Carregar root dir na memória.
	for( i=0; i < szFat; i++){
	    read_lba( FAT16_FAT_ADDRESS + b, FAT16_FAT_LBA + i); 
		b = b+512;    //Incrementa buffer.
	};
done:	
    return;
};
 
//preenche o diretorio raiz com informações guardadas em disco. 
void fs_load_rootdir()
{
    fs_load_dir(0);	
	return;
}; 


//
// carrega um dado diretorio da lista de arquivos. dado o indice.
//
void fs_load_dir(unsigned long id)
{    	
	unsigned long i;
	unsigned long n = 0;
	unsigned long lba;
	
    struct dir_d *File;

	File = (void*) fileList[id];	
	if( (void*) File == NULL ){
	    printf("fs_load_dir fail: Struct.\n");
	    return;
	};
	
	
	if(File->address == 0){
	    printf("fs_load_dir: Null address.\n");
		return;
	};
	
	unsigned long buffer = (unsigned long) File->address;  
	
	//na inicialização so temos a lba inicial do diretorio raiz
	if(id == 0){
	    lba = FS_ROOTDIR_LBA;
	}else{
	    //lba = filesystem->dir[id].lba_inicial;
	};
	
	//64??
	for(i = 0; i < 64; i++)
	{
	    //lba inicial do root dir + deslocamento.
		read_lba( buffer, lba + n); 
		//read_lba( &filesystem->dir[lba], lba + n); 
 
	    //prennche a estrutura com os valores do buffer.
	    //o diretorio '0' é o diretorio raiz. 
		fs_set_entry(id,i);
		n++;
	};
	
done:	
	return;
};

//
// End.
//

