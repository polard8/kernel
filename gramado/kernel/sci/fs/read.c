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


//#define read_ToUpper(C) ((((C) >= 'a') && ((C) <= 'z')) ? (C) - 'a' + 'A' : (C))
//#define read_Minimum(X,Y) ((X) < (Y) ? (X) : (Y))
//#define read_Maximum(X,Y) ((X) < (Y) ? (Y) : (X))



/*
 ************************************************
 * read_fntos:
 *     rotina interna de support.
 *     isso deve ir para bibliotecas depois.
 *     não tem protótipo ainda.
 *     Credits: Luiz Felipe 
 */
 
 // #bugbug
 // Isso modifica a string lá em ring3.
 // prejudicando uma segunda chamada com a mesma string
 // pois já virá formatada.
 
void read_fntos ( char *name ){

    int  i, ns = 0;
    char ext[4];

    ext[0] = 0;
    ext[1] = 0;
    ext[2] = 0;
    ext[3] = 0;


    // Transforma em maiúscula enquanto não achar um ponto.
    // #bugbug: E se a string já vier maiúscula teremos problemas.

    //while ( *name && *name != '.' )
    while ( *name && *name != '.' )     // # testing
    {
        if ( *name >= 'a' && *name <= 'z' )
            *name -= 0x20;

        name++;
        ns++;
    };

 
    if ( name[0] == '\0' && ns <= 8 )
    {
        ext[0] = 'B';
        ext[1] = 'I';
        ext[2] = 'N';
        ext[3] = '\0';        
        goto _complete; //completa nome.
    }

    //if ( name[0] == '.' && ns < 8 )

    // Aqui name[0] é o ponto.
    // Então constrói a extensão colocando
    // as letras na extensão.

    for ( i=0; i < 3 && name[i+1]; i++ )
    {
		//Transforma uma letra da extensão em maiúscula.
 
        //if (name[i+1] >= 'a' && name[i+1] <= 'z')
        //    name[i+1] -= 0x20;

        //ext[i] = name[i+1];
    

        //#testando
        //Se não for letra então não colocamos no buffer de extensão;
        if ( name[i+1] >= 'a' && name[i+1] <= 'z' )
        {
            name[i+1] -= 0x20;

            ext[i] = name[i+1];
        }
    };


// Acrescentamos ' ' até completarmos as oito letras do nome.
_complete:

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
fatClustToSect ( 
    unsigned short cluster, 
    unsigned long spc, 
    unsigned long first_data_sector )
{
    unsigned long C = (unsigned long) cluster;

    C -= 2;

	// #todo: 
	// Check limits.

    return (unsigned long) (C * spc) + first_data_sector;
}


/*
 ******************************************
 * fatLoadCluster:
 *     Carrega um cluster.
 *     Argumentos:
 *         setor   ~ Primeiro setor do cluster.
 *         address ~ Endereço do primeiro setor do cluster.
 *         spc     ~ Número de setores por cluster.
 * Começa do primeiro setor do cluster.
 */
 
void 
fatLoadCluster ( 
    unsigned long sector, 
    unsigned long address, 
    unsigned long spc )
{
    unsigned long i=0;

    for ( i=0; i < spc; i++ ){
        read_lba ( address, sector + i );
        address = (address +512); 
    };
}


/*
 *****************************************************************
 * read_lba:
 *     Carrega um um setor na memória, dado o LBA.
 *     Obs: 
 *     Talvez essa rotina tenha que ter algum retorno no caso de falhas. 
 */
 
void read_lba ( unsigned long address, unsigned long lba ){


    // #todo
    // Fazer algum filtro de argumentos ??

    // See: volume.h
    switch (g_currentvolume_fatbits){

        case 32:
            debug_print ("read_lba: FAT32 not supported\n");
            return;
            break;

        case 16:
           // hdd.c
            my_read_hd_sector ( address, lba, 0, 0 );
            return;
            break;

        // Nothing.
        case 12:
            debug_print ("read_lba: FAT12 not supported\n");
            return;
            break;

        default:
            debug_print ("read_lba: g_currentvolume_fatbits not supported\n");
            break;
    };
}


/**
 * @brief Breaks a path
 * 
 * @details Parses the path pointed to by @p pathname extracting the first
 *          path-part from it. The path-part is stored in the array pointed to
 *          by @p filename.
 * 
 * @param pathname Path that shall be broken.
 * @param filename Array where the first path-part should be save.
 * 
 * @returns Upon successful completion, a pointer to the second path-part is 
 *          returned, so a new call to this function can be made to parse the
 *          remainder of the path. Upon failure, a #NULL pointer is returned 
 *          instead.
 */
 
 
/* 
// Credits: Penna.
const char *break_path (const char *pathname, char *filename); 
const char *break_path (const char *pathname, char *filename)
{

    char *p2;          // Write pointer. 
    const char *p1;    // Read pointer.  


	p1 = pathname;
	p2 = filename;
	
	//Skip those. 
	while (*p1 == '/')
		p1++;
	
	//Get file name.
	while ((*p1 != '\0') && (*p1 != '/'))
	{
		//File name too long. 
		if ((p2 - filename) > NAME_MAX)
			return (NULL);
		
		*p2++ = *p1++;
	}
	
	*p2 = '\0';
	
	return (p1);
}
*/


// #todo
// Caregar um arquivo na memoria e retornar seu inode.
// ? registrar a estrutura de inode na inode_table[] ?
// ? registrar a estrutura de arquivo na file_table[] ?
struct inode_d *fs_load_file (char *pathname)
{
    struct inode_d *inode;


    debug_print ("fs_load_file: [TODO] It's a work in progress\n");

    inode = (struct inode_d *) kmalloc( sizeof(struct inode_d) );
    if( (void*) inode == NULL ){
        debug_print ("fs_load_file: [FAIL] inode\n");
        return (struct inode_d *) 0;

    }else{
        
        //inode->id ?
        inode->used = 1;
        inode->magic = 1234;
        
        //todo: copiar em path
        //inode->path[]
        
        inode->uid = current_user;
        inode->gid = current_group;
        
        //inode->____object (todo: inode structure)
        
        
        inode->isfat16 = 0;
        inode->fat16_dirent.FileSize = 0;
        //...
        
        inode->size_in_bytes = 0;
        
        //...
        
        inode->next = NULL;
    };


    return (struct inode_d *) 0;
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


// #obs
// Rotina específica para FAT16.
// Podemos mudar o nome para fsFat16LoadFile().
// Ou fs_Fat16_SFN_LoadFile()



// IN: ?? #todo: Descrever os argumentos de entrada.
// OUT: 
//    1=fail 
//    0=ok.

unsigned long 
fsLoadFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    unsigned char *file_name, 
    unsigned long file_address,
    unsigned long buffer_limit )
{

    // #bugbug
    // Se estamos considerando o endereço de quanquer diretorio
    // entao devemos considerar o numero de entradas nesse dado
    // diretorio.

	// #bugbug
	// We have a buffer but we don't know the buffer size.
	// It can overflow when loading a file on it.
	// We need a buffer structure to handle the max allowed.


    int i=0;
    int Status;  //??

    int SavedDirEntry = 0;
    unsigned short next=0;
    
    // #todo: 
    // Rever. Número máximo de entradas.
    
    unsigned long MaxEntries = (unsigned long) dir_entries;
    
    // #bugbug: 
    // Esse eh o numero de entradas no diretorio raiz.
    MaxEntries = 512;      
    
    
    
    unsigned long BufferLimit = (unsigned long) buffer_limit;
    
    
    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.

    char tmpName[13];
    
    size_t FileNameSize = 0;

    //int IsDirectory;

    // Cluster inicial
    unsigned short cluster=0; 

    // ?? 
    // Primeiro setor do cluster.
    unsigned long S=0;  

    // Usado junto com o endereço do arquivo.
    unsigned long SectorSize=0;

    int Spc=0;

    // Updating fat address and __dir address.

    unsigned short *  fat = (unsigned short *) fat_address;
    unsigned short *__dir = (unsigned short *) dir_address;



    //
    // Initialize variables.
    //


    /*
    if (____IsCdRom) {
        SectorSize = 2048;
    } else {
        SectorSize = SECTOR_SIZE;
    }
    */

    SectorSize = SECTOR_SIZE;
    // ...


    // DIR
    // Não carregaremos mais um diretório nesse momento
    // usaremos o endereço passado por argumento.
    // Esperamos que nesse endereço tenha um diretório carregado.

//load_DIR:
    debug_print ("fsLoadFile:\n");
    
    if ( MaxEntries == 0 ){
        panic("fsLoadFile: MaxEntries\n");
    }

    if ( MaxEntries > 512 ){
        panic("fsLoadFile: MaxEntries limits\n");
    }
    

    if ( BufferLimit == 0 ){
        panic("fsLoadFile: [FAIL] BufferLimit fail\n");
    }

    // limite maximo de uma imagem de processo.
    if ( BufferLimit > (512*4096) ){
        panic("fsLoadFile: [FAIL] BufferLimit\n");
    }
    
    
   
   

    // File system structure.
    // + Checa se é válida a estrutura do sistema de arquivos.
    // + Pega a quantidade de setores por cluster.
    // + Pega o tamanho do diretório raiz. Ou seja, pega o número 
    //    máximo de entradas.
    // ...

    if ( (void *) root == NULL )
    {
        panic ("fsLoadFile: No root file system.\n");

    }else{

        // #todo
        // Check if the root is initialized.
        //if (root->used != 1 || root->magic != 1234){
        //    panic ("fsLoadFile: validation");
        //}

        Spc = root->spc;
        if (Spc <= 0){ panic ("fsLoadFile: Spc\n"); }

        // Max entries 
        // Número de entradas no rootdir.
        // #bugbug: 
        // Devemos ver o número de entradas no diretório corrente.

        //max = root->rootdir_entries;
        if (MaxEntries <= 0){ panic ("fsLoadFile: max root entries \n"); }

        // ...
    };


	// Continua ... 
	// Pegar mais informações sobre o sistema de arquivos.
	// Busca simples pelo arquivo no diretório raiz.
	// #todo: 
	// Essa busca pode ser uma rotina mais sofisticada. Uma função auxiliar.
	// Primero caractere da entrada:
	// 0 = entrada vazia.
	// $ = entrada de arquivo deletado.
	// outros ...
	// ATENÇÃO:
	// Na verdade a variável 'root' é do tipo short.
	 


    //
    // file name
    //
    
    // #todo
    // Ponteiro inválido para o nome do arquivo.
    // if ( (void *) file_name == NULL ){
    //    return 1;
    // }
    
    
    // Se o path começa com / então é absoluto.
    // Devemos começar pelo diretório raiz.
    //if ( *file_name == '/' )
    //{
        //Absolute = 1;
        //file_name++;



    //while (*file_name == '/')
        //file_name++;
        

    
    //#debug
    //vamos mostrar a string.
    //printf ("fsLoadFile: file_name={%s}\n", file_name);


    // name size.
    // Se o tamanho da string falhar, vamos ajustar.

    FileNameSize = (size_t) strlen (file_name); 

    if ( FileNameSize > 11 ){
         printf ("fsLoadFile: [FAIL] name size %d\n", FileNameSize ); 
         FileNameSize = 11;
         //return 1; //fail
    }
    
    
    //
    // File size.
    //
    
    // Pegar o tamanho do arquivo e comparar com o limite do buffer.
    // #bugbug: Essa rotina s'o pega o tamanho dos arquivos que
    // estao no diretorio raiz.
    
    unsigned long FileSize = 0;
    
    FileSize = fsRootDirGetFileSize( (unsigned char *) file_name );
    if(FileSize==0){
        debug_print ("fsLoadFile: [FIXME] FileSize fail\n");
    }


    // Comparando nosso tamanho obtido com o tamanho do buffer.
    // Como a rotina de pegar o tamanho so pega no diretorio raiz
    // por enquanto, entao vamos apenas emitir um alerta que 
    // o tamanho do arquivo eh maior que o buffer, servira para debug.
    // Isso porque em todas as tentativas de pegar o tamanho do arquivo
    // fora do root, retornara 0.
    
    //#todo
    //Precisamos usar as estruturas de diretorio e as estruturas de buffer.

    if ( FileSize > BufferLimit )
    {
        debug_print ("fsLoadFile: [=========== BUGBUG =============] Buffer Overflow!\n");
    }


    
    // We are opening the root dir.
    //if ( file_name[0] == '/' && size == 1 )
    //{
    //}
    
    
    //
    // Search dirent.
    //



	//
	// Compare.
	//

    // #bugbug
    // #todo:
    // Para a variável 'max' estamos considerando o número de
    // entradas no diretório raiz. Mas precisamos considerar
    // o número de entradas no diretório atual.
    // >> Para isso vamos precisar de uma estrutura de diretório
    // >> talvez a mesma usada em arquivos. (FILE)


    // Descrição da rotina:
    // Procura o arquivo no diretório raiz.
    // Se a entrada não for vazia.
    // Copia o nome e termina incluindo o char '0'.
    // Compara 'n' caracteres do nome desejado, 
    // com o nome encontrado na entrada atual.
    // Se for encontrado o nome, então salvamos o número da entreda.
    // Cada entrada tem 16 words.
    // (32/2) próxima entrada! (16 words) 512 vezes!
    
    i=0; 
    while ( i < MaxEntries )
    {
        if ( __dir[z] != 0 )
        {
            memcpy ( tmpName, &__dir[z], FileNameSize );
            tmpName[FileNameSize] = 0;

            Status = strncmp( file_name, tmpName, FileNameSize );

            if ( Status == 0 ){ SavedDirEntry = i; goto __found; }
        }; 
        z += 16;    
        i++;        
    }; 


    // Not found.
    // Sai do while. 
    // O arquivo não foi encontrado.
    // O arquivo não foi encontrado.

//notFound:
    debug_print ("fsLoadFile: file not found\n");
    printf      ("fsLoadFile 1: %s not found\n", file_name );  
    goto fail;


    // Found.
    // O arquivo foi encontrado.

__found:

    // #debug
    // printf ("file FOUND!\n");
    // refresh_screen();
    // while(1){}
    
    
    //
    // Cluster.
    //

    // Get the initial cluster. 
    // Check cluster Limits.
    // (word). 
    // (0x1A/2) = 13.
    // Checar se 'cluster' está fora dos limites.
    // +São 256 entradas de FAT por setor. 
    // +São 64 setores por FAT. 
    // Isso varia de acordo com o tamanho do disco.
    // O número máximo do cluster nesse caso é (256*64).
    // #todo
    // Na verdade os dois primeiros clusters estão indisponíveis.


    cluster = __dir[ z+13 ];

    if ( cluster <= 0 || cluster > 0xFFF0 )
    {
        debug_print ("fsLoadFile: Cluster limits\n");
        printf      ("fsLoadFile: Cluster limits %x \n", cluster );
        goto fail;
    }



    // FAT
    // Carrega fat na memória.
    // #bugbug: 
    // Não devemos carregar a FAT na memória toda vez que 
    // formos carregar um arquivo. 
    // Talvez ela deva ficar sempre na memória.
    // Precisamos de estruturas para volumes que nos dê esse 
    // tipo de informação

//loadFAT:

    fs_load_fat();


    // Load clusters.
    // Carregar o arquivo, cluster por cluster.
    // #todo: 
    // Por enquanto, um cluster é igual à um setor, 512 bytes.
    // Loop de entradas na FAT.
    // #todo: 
    // Esse loop é provisório, while pode ser problema.
    
    // #todo
    // Tabela temporária para salvar os números dos clusters
    // usados pelo arquivo.
    // ?? Qual será o tamanho dessa tabela ??
    //unsigned short tmp_table[1024];
    
    //#todo: Use while()
    
    // #todo
    // Create a helper function like this one.
    // int fsReadClusterChain ( char *file_address, short first_cluster, char *fat_address ){}


    //
    // == Load cluster chain ===================================
    //

__loop_next_entry:

    // #todo
    // Esse while é para o caso de termos mais de um setor por cluster.
    // Mas não é nosso caso até o momento.

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


    // #todo
    // Poderia ter uma versão dessa função para ler
    // um dado número de setores consecutivos.


    // #todo
    // #importante
    // Esse é o momento em que vamos registrar na estrutura de arquivos
    // quais foram os clusters usados pelo arquivo, para assim podermos
    // salvar somente somente os setores modificados e não sempre o 
    // arquivo todo.
    // >> Mas não temos a estrutura de arquivos no momento.
    // Mesmo assim, talvez ja possomos salvar os números dos clusters
    // em uma tabela temporária.
    
    //tmp_table[tmp_table_index] = cluster;
    //tmp_table_index++;
    
    //
    // Read LBA.
    //

    read_lba ( file_address, VOLUME1_DATAAREA_LBA + cluster -2 ); 


    // Caution!
    // Increment buffer base address.
    // Pega o próximo cluster na FAT.
    // Configura o cluster atual.
    // Ver se o cluster carregado era o último cluster do arquivo.
    // Vai para próxima entrada na FAT.

    file_address = (unsigned long) (file_address + SectorSize); 

    next = (unsigned short) fat[cluster];

    cluster = (unsigned short) next;

    // ?? done
    // ?? message  
    // salvar a tabela na estrutura de arquivo.
    // Onde está a estrutura de arquivos ??
    // Em que momento ela é criada ?
    // #bugbug: tem arquivo carregado pelo kernel
    // sem ter sido registrado na estrutura do processo kernel.

    if ( cluster == 0xFFFF || cluster == 0xFFF8 ){ return (unsigned long) 0; }

    goto __loop_next_entry;

    // Fail

fail:
    debug_print("fsLoadFile: [FAIL] \n");
    printf     ("fsLoadFile: [FAIL] file={%s}\n", file_name );
    refresh_screen ();
    return (unsigned long) 1;
}



/*
 ****************************************
 * fs_load_fat:
 *    Carrega a fat na memória.
 *    Sistema de arquivos fat16.
 *    ? qual disco ?
 *    ? qual volume ? 
 *    #obs: Essa rotina poderia carregar a fat do volume atual do 
 * disco atual. É só checar na estrutura.
 *
 * current disk, current volume, fat status.
 *
 * + Se o status da fat para o vulume atual indicar que 
 * ela já está carregada, então não precisamos carregar novamente.
 */

// #todo
// Precisamos de uma estrutura com as informações sobre
// a FAT atual.

void fs_load_fat(void){

    unsigned long i=0;
    unsigned long b=0;


	// #bugbug 
	// Estamos atribuindo um tamanho, mas tem que calcular.
	// Salvo engano o tamanho é 246 setores.
    unsigned long szFat = 128;


    debug_print ("fs_load_fat:\n");

	//#todo:
	//+checar qual é o disco atual.
	//+checar qual é o volume atual.
	//+checar o status da FAT. Talvez ela já esteja na memória.
	//obs: a estrutura deve informar onde está a fat do volume,
	//caso ja esteja na memória.
	//obs: padronizaremos alguns endereços, e alocaremos outros.

    //
    // Check cache state.
    //
    
    // Se ja está na memória, então não precisamos carregar novamente.
    if (fat_cache_loaded==CACHE_LOADED){
         debug_print("fs_load_fat: FAT cache already loaded!\n");
         return;
    }


	// Carregar fat na memória.
    for ( i=0; i < szFat; i++ ){
        
        my_read_hd_sector ( 
            VOLUME1_FAT_ADDRESS + b, 
            VOLUME1_FAT_LBA + i, 
            0, 
            0 );

        // Incrementa buffer para o próximo setor.
        b = (b +512);    
    };
    
    // Changing the status
    fat_cache_loaded = CACHE_LOADED;
}


/*
 ***********************************************************
 * load_sequential_directory:
 *    Carrega um diretorio sequencial diretório na memória,
 * dados o endereço, o lba inicial e o número de setores.
 */

// #bugbug
// Aqui estamos falando de uma sequência de setores.
// Isso serve para carregar o diretório raiz em fat16.
// Mas nao server para carregar subdiretorios.

int
__load_sequential_sectors ( 
    unsigned long address, 
    unsigned long lba, 
    unsigned long sectors )
{
    unsigned long i=0;
    unsigned long b=0;


    debug_print ("load_directory:\n");
    
    for ( i=0; i < sectors; i++ ){
        my_read_hd_sector ( address + b, lba + i, 0, 0 );
        b = (b +512);    
    };
    
    return 0;
}



// Load metafile
void 
fs_load_metafile (
    unsigned long buffer, 
    unsigned long first_lba, 
    unsigned long size )
{

    debug_print ("fs_load_metafile:\n");
    
    if (buffer == 0)
        return;

    if ( size == 0 )
        return;
    
   
    __load_sequential_sectors ( 
        buffer, 
        first_lba, 
        size );
}



/*
 ****************************** 
 * fs_load_rootdir:
 * 
 */

// Carrega o diretório raiz.
// address, lba, number of sectors.

// #todo
// Precisamos de uma estrutura com as informações sobre
// o diretório raiz atual.

void fs_load_rootdir (void)
{
    debug_print ("fs_load_rootdir:\n");
    
    __load_sequential_sectors ( 
        VOLUME1_ROOTDIR_ADDRESS, 
        VOLUME1_ROOTDIR_LBA, 
        32 );
}


/*
 ***************************** 
 * fsGetFileSize: 
 * 
 */

// #bugbug: Isso dá problemas na máquina real.
// Essa rotina é chamada pela função fopen, por isso precisamos dela.
// Pega o tamanho de um arquivo que está no diretório raiz.
// #todo: 
// Podemos alterar para pegar de um arquivo que esteja no diretório alvo.

// #todo:
// Antes de carregar um arquivo o sistema de arquivos
// precisa preencher uma estrutura com informações sobre ele. 
// se já existir um registro é melhor.

// #bugbug
// Estamos com problemas na string do nome.

// #bubug
// Only on rootdir.

unsigned long fsRootDirGetFileSize ( unsigned char *file_name ){

    unsigned long FileSize=0;
    
    int i=0;
    unsigned long max = 64;    //?? @todo: rever. Número máximo de entradas.
    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.

    // #bugbug
    // Estamos com problemas na string do nome.
 
    char NameX[13];
    int CmpStatus = (-1);

    int Spc=0;

	// #importante:
	// Poderíamos usar malloc ou alocador de páginas ??
	// #todo: 
	// Devemos carregar o diretório alvo.

    unsigned short *Dir = (unsigned short *) VOLUME1_ROOTDIR_ADDRESS;

	// #todo: Devemos carregar o diretório atual.
	//unsigned long current_dir_address = (unsigned long) Newpage();
    //#todo: devemos checar se o endereço é válido.
	//unsigned short *current_dir = (unsigned short *) current_dir_address;	
	// #todo: 
	// devemos chamar uma função que carregue um diretório no endereço passado 
	//via argumento.
    //...
	
	// Lock ??.
	
	//taskswitch_lock();
	//scheduler_lock();	
		
		
	//	
	// ## ROOT ##
    //
    
    
//loadRoot:
	
	//Carrega o diretório raiz na memória.
	
//#ifdef KERNEL_VERBOSE	
	//printf ("fsRootDirGetFileSize: Loading root..\n"); 
//#endif	
	
	//#bugbug
    //pega o tamanho de um arquivo que está no diretório raiz.
    //#todo: 
    //podemos alterar para pegar de um arquivo que esteja no diretório alvo.	


	// Carregando o diretório raiz.
    fs_load_rootdir();
    //__load_sequential_sectors ( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );

	
	//#todo:
	//precisamos na verdade carregarmos o diretório corrente.
	
	// Continua ... 
	// Pegar mais informações sobre o sistema de arquivos.
	
	//#obs
	//Checa se é válida a estrutura do sistema de arquivos.
    //A intenção é obtermos a quantidade de entradas no diretório raiz.
	//#bugbug: Mas isso deveria ser feito para o diretório atual.

    //
    // == root filesystem structure ===============================
    //


    if ( (void *) root == NULL )
    {
        panic ("fsRootDirGetFileSize: [FAIL] No root file system!\n");

    }else{

        // Setores por cluster.
        Spc = root->spc;
        if (Spc <= 0){ panic ("fsRootDirGetFileSize: [FAIL] Spc\n"); }

        // Max entries ~ Número de entradas no rootdir.
        // #bugbug: 
        // Devemos ver o número de entradas no diretório alvo.

        max = root->rootdir_entries;
        if (max <= 0){ panic ("fsRootDirGetFileSize: [FAIL] max root entries\n"); }

        // More?! 
        // ...
    };


    //
    // file name
    //
    
    //#debug
    //vamos mostrar a string.
    //printf ("fsGetFileSize: file_name={%s}\n", file_name);
	
	//Busca simples pelo arquivo no diretório raiz.
	//todo: Essa busca pode ser uma rotina mais sofisticada. 
	//Uma função auxiliar.

	//Primero caractere da entrada:
	//0 = entrada vazia.
	//$ = entrada de arquivo deletado.
	//outros ...
	//ATENÇÃO:
    //Na verdade a variável 'root' é do tipo short.	 



	// Procura o arquivo no diretório raiz.
	
//search_file:

    //
    // file name limit.
    //

    size_t szFileName = (size_t) strlen (file_name); 
    
    // o tamanho da string falhou
    //vamos ajustar.
    if ( szFileName > 11 )
    {
        printf ("fsGetFileSize: [FIXME] name size fail %d\n",
        szFileName );   
        szFileName = 11;
    }

    // Compare.
    // Copia o nome e termina incluindo o char 0.
    // Compara 11 caracteres do nome desejado, 
    // com o nome encontrado na entrada atual.

    i=0; 

    while ( i < max )
    {
        // Se a entrada não for vazia.
        if ( Dir[z] != 0 )
        {
            memcpy ( NameX, &Dir[z], szFileName );
            NameX[szFileName] = 0;

            CmpStatus = strncmp ( file_name, NameX, szFileName );

            if ( CmpStatus == 0 ){ goto found; }
            // Nothing.
        }; 

        // Next entry.
        // (32/2)  (16 words) 512 times!

        z += 16;    
        i++;        
    }; 

    // Not found!

    printf ("fsGetFileSize: %s not found\n", file_name );
    printf ("fsGetFileSize: %s not found\n", NameX );

fail:

    printf ("fsGetFileSize: file={%s}\n", file_name );
    refresh_screen ();
    return (unsigned long) 0;

    // Found!

found:

    // #debug
    // printf("arquivo encontrado\n");
    // refresh_screen();
    // while(1){}

    // #debug
    // Pegando o tamanho do arquivo.
    // Offsets: 28 29 30 31

    FileSize = *(unsigned long*) (VOLUME1_ROOTDIR_ADDRESS + (z*2) + 28 );
	
	//printf ("%d \n" , root[ z+14 ]);
	//printf ("%d \n" , root[ z+15 ]);
	//printf ("done: FileSize=%d \n" , FileSize);
	
	//#debug
	//refresh_screen();
	//while(1){ asm("hlt"); }

    //#debug
    printf ("fsGetFileSize: FileSize=%d \n" , FileSize );
    refresh_screen ();

    return (unsigned long) FileSize;
}


//
// End.
//

