/*
 * File: fs/write.c 
 *
 * Descrição: 
 *     Rotinas de gravação. em disco
 *
 * Obs:
 *    As rotinas na biblioteca C devem chamar essas funções.
 *
 * History:
 *    2015 - Created by Fred Nora.
 *    ...
 */


#include <kernel.h>


//extern void reset_ide0 (void);


/*
 ************************************
 * write_fntos
 *     Rotina interna de support.
 *     isso deve ir para bibliotecas depois.
 *     não tem protótipo ainda.
 *     Credits: Luiz Felipe 
 */

void write_fntos (char *name){

    int i=0; 
    int ns = 0;

    //const char ext[4];
    char ext[4];
    ext[0] = 0;
    ext[1] = 0;
    ext[2] = 0;
    ext[3] = 0;



    //Transforma em maiúscula enquanto não achar um ponto.

    while ( *name && *name != '.' )
    {
        if ( *name >= 'a' && *name <= 'z' )
        {
            *name -= 0x20;
        }

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

    for (i=0; i<3; i++)
    {
        *name++ = ext[i];
    };


    *name = '\0';
}



/*
 * fatWriteCluster:
 *     Salva um cluster no disco.
 *
 * Argumentos:
 *   setor   ~ Primeiro setor do cluster.
 *   address ~ Endereço do primeiro setor do cluster.
 *   spc     ~ Número de setores por cluster.
 */

	//Começa do primeiro setor do cluster.

//int fatWriteCluster ( unsigned long sector, 
//                      unsigned long address, 
//                      int spc )

void 
fatWriteCluster ( 
    unsigned long sector, 
    unsigned long address, 
    unsigned long spc )
{
    unsigned long i=0;


    for ( i=0; i < spc; i++ )
    {
        write_lba ( address, (sector + i) );
        address = (address +512); 
    };


    //...

    return;
    //return 0;  //#todo
}


/*
 *************************************************
 * write_lba:
 *     Grava um setor no disco dado o endereço do buffer e o lba. 
 */

//int write_lba ( unsigned long address, unsigned long lba ) 

void write_lba ( unsigned long address, unsigned long lba ){

	// #todo: 
	// Check lba limits.

    if (address == 0)
    {
        debug_print ("write_lba: Limits\n");
        goto fail;
    }


    // See: volume.h
    switch (g_currentvolume_fatbits)
    {
        case 32:
            printf ("write_lba: FAT32 not supported\n");
            goto fail;
            break;

        //See: hdd.c
        case 16:
            my_write_hd_sector ( address, lba, 0, 0 ); 
            return;
            break;

        case 12:
            printf ("write_lba: FAT12 not supported\n");
            goto fail;
            break;

        default:
            printf ("write_lba: g_currentvolume_fatbits NOT SUPPORTED\n");
            goto fail;
            break;
    };

    // Nothing.

fail:
    refresh_screen();
    return;
}


/*
 **************************************************
 * fsSaveFile:
 *     Salva um arquivo no disco.
 *     Somente no diretório raiz.
 */

// It was called by sys_write_file() in fs.c.
// It was called by sys_read_file when the file does not exist.


// #obs
// Isso salva um arquivo.
// Também poderia ser usado para criar um arquivo ou diretório ? 
 
// #todo: #test
// Número máximo de entradas na lista de clusters. 
// Quantas?
// A FAT tem 246 setores, 123 KB



//
// == Cluster list =================================================
//

// Lista de clusters.
// Isso permite salvar um arquivo com 32 mil clusters ??

#define  fat_range_max (1024*32)  

unsigned short list[fat_range_max];
 

// ======================================
// fsSaveFile:
//     Salva um arquivo. 
//     Onde? #todo vamos fornecer o endereço do diretorio.
// IN: 
// name, size in sectors, size in bytes, adress, flag. 
// OUT:


// #bugbug
// O nome nao esta ficando certo na entrada.

int
fsSaveFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{

    int Status = 0;

    unsigned long i = 0; 
    unsigned long j = 0;    // Deslocamento na lista, tem que ser zero.
    unsigned long c = 0;    // Deslocamento na FAT.

    unsigned short first=0;
    unsigned short next=0;
    unsigned short sector=0;

    // Directory entry buffer.
    char DirEntry[32];

    //Entry size in words.
    int EntrySize = 0;
    int Offset = 0;
    int FreeIndex = -1;


    // #debug:
    debug_print ("fsSaveFile:\n");
    printf      ("fsSaveFile:\n");


    // Updating fat address and dir address.
    
    if ( fat_address == 0 ){
        panic("fsSaveFile: [FAIL] fat_address\n");
    }

    if ( dir_address == 0 ){
        panic("fsSaveFile: [FAIL] dir_address\n");
    }

    unsigned short *fat   = (unsigned short *) fat_address; //VOLUME1_FAT_ADDRESS;
    unsigned short *__dir = (unsigned short *) dir_address; //VOLUME1_ROOTDIR_ADDRESS;


    // #debug
    // We only support one address for now.
    if ( fat_address != VOLUME1_FAT_ADDRESS ){
        panic("fsSaveFile: [FIXME] Sorry. We only support ONE fat address for now!\n");
    }


    if ( (void *) file_name == NULL )
    {
        debug_print ("fsSaveFile: [FIXME] No filename\n");
        printf      ("fsSaveFile: [FIXME] No filename\n"); 
        goto fail;
    }

    // #bugbug
    // Esse endereço eh valido ?
    
    printf ("name address = %x \n", &file_name );

    printf ("name    = %s \n", file_name ); 
    printf ("size    = %d \n", file_size );       // Size in sectors.
    printf ("nbytes  = %d \n", size_in_bytes );
    printf ("address = %x \n", file_address );
    printf ("flag    = %x \n", flag );
    printf ("entries = %d \n", dir_entries );

    if ( dir_entries == 0 || dir_entries > FAT16_ROOT_ENTRIES )
    {
        panic ("fsSaveFile: [FAIL] max dir entries");
    }


	// file_size
	// #todo: 
	// precisamos implementar um limite para o tamanho do arquivo,
	// principamente nessa fase de teste.

    // #bugbug
    // Limite provisorio
    if ( file_size > 16 )
    {
        debug_print ("fsSaveFile: [FIXME] Size in sectors\n");
        printf      ("fsSaveFile: [FIXME] Size in sectors = %d \n", 
            file_size ); 
        goto fail;
    }


    // Load root dir and FAT.
    fs_load_rootdir();
    fs_load_fat();



    // Procurando cluster livre na fat.
    // Nesse momento construimos uma lista de clusters livres.
    // #todo: 
    // Essa lista já devia existir e agora somente 
    // usaríamos.
    // #todo: Essa rotina poderia seruma helper function?


//SearchEmptyEntries:
 
	// #bugbug
	// Obs: Esse limite é improvisado.

    while ( i < fat_range_max )
    {
        //procurando cluster livre na fat.
        //@todo:isso poderia ser uma função.

        if (fat[c] == 0)
        {
            // Encontrado todos os espaços livres 
            // que o arquivo precisa.
            // Marca o fim.
            // #importante: 
            // Se der certo, saímos do loop.
            // #bugbug: Esse size deve ter um limite.
            // file_size = file size in sectors, (clusters??)
            if (file_size == 0)
            {
                list[j] = (unsigned short) 0xfff8; 
                goto save_file;
            }

            //salva um endereço livre
            //salvamos um índice na fat dentro da lista
            //incrementa a lista

            list[j] = (unsigned short) c;   
            j++; 

            // Decrementa o tamanho do arquivo!
            file_size--; 
        };

        c++;    // Incrementa o deslocamento na fat. 
        i++;    // Incrementa a quantidade de busca.
    }; 
 
 
    // Fail
    // Nossa busca por clusters livres dentro da fat não deu certo.
    // Provavelmente não encontramos uma quantidade sufciente.


out_of_range:  

    printf ("fsSaveFile: No free cluster \n");
    goto fail;


    // #debug
    //refresh_screen();
    //while(1){ asm("hlt"); }


// #importante:
// Deu certo. Encontramos na fat todos os clusters que o arquivo precisa.   
// Salva o arquivo.
// O arquivo tem na lista todos os clusters que ele precisa.

    //
    // Save!
    // 

save_file:

    //#debug
    //printf("fsSaveFile: save_file: \n"); 
    //refresh_screen();
  
    // Início da lista.
    i = 0; 

    //
    // Size limits.
    //

    // #bugbug
    // Limite máximo improvisado.
    // 2KB.

    j = (512*4);    
 
 
    // Pegamos o primeiro da lista.
    first = list[i];


	// #debug
	// printf("first={%x}\n",first);


    //
    // == Create directory entry ==================================
    //

    // Name/ext 8.3
    DirEntry[0]  = (char) file_name[0];
    DirEntry[1]  = (char) file_name[1];
    DirEntry[2]  = (char) file_name[2];
    DirEntry[3]  = (char) file_name[3];
    DirEntry[4]  = (char) file_name[4];
    DirEntry[5]  = (char) file_name[5];
    DirEntry[6]  = (char) file_name[6];
    DirEntry[7]  = (char) file_name[7];
    DirEntry[8]  = (char) file_name[8];
    DirEntry[9]  = (char) file_name[9];
    DirEntry[10] = (char) file_name[10];


    // Flag. (attributes ?)
    //====================
    // 0x01: read only
    // 0x02: hidden
    // 0x04: system
    // 0x08: volume label
    // 0x10: * Directory
    // 0x20: * Archive
 
    DirEntry[11] = flag; 

    // Reserved.
    DirEntry[12] = 0;       

    // Creation time. 14 15 16
    DirEntry[13] = 0x08; 
    DirEntry[14] = 0x08; 
    DirEntry[15] = 0xb6;

    // Creation date.
    DirEntry[16] = 0xb6;
    DirEntry[17] = 0x4c;

    // Access date.
    DirEntry[18] = 0xb8;
    DirEntry[19] = 0x4c;

	// ??
	// First cluster. 
	// 0 para fat12 ou 16
    DirEntry[20] = 0;
    DirEntry[21] = 0;

    // Modifield time.
    DirEntry[22] = 0xa8;
    DirEntry[23] = 0x49;

    // Modifield date.
    DirEntry[24] = 0xb8;
    DirEntry[25] = 0x4c;

    // First cluster. Low word.
    // 0x1A and 0x1B
    DirEntry[26] = (char) (first); 
    DirEntry[27] = (char) (first >> 8); 

    // size_in_bytes - File size in bytes.
    // 4 bytes: (28,29,30,31)

    DirEntry[28] = (char) size_in_bytes;   
    size_in_bytes = (size_in_bytes >> 8);
    DirEntry[29] = (char) size_in_bytes;
    size_in_bytes = (size_in_bytes >> 8);
    DirEntry[30] = (char) size_in_bytes;
    size_in_bytes = (size_in_bytes >> 8);
    DirEntry[31] = (char) size_in_bytes;


	// #importante:
	// Vamos encontrar uma entrada livre no diretório para
	// salvarmos o nome do arquivo.
	// Copia o nome para dentro da entrada do diretório.
	// Obs: As entradas são de 32 bytes. Como root[] é um 
	// array de short então faremos um deslocamento de 16 shorts.
	// root[]
	// #importante: root[] é um array de short.	
	// IN: 
	// Endereço do diretótio e número máximo de entradas.
	// #todo: 
	// Talvez possamos ampliar esse número para o máximo 
	// de entradas no diretório.
	// #bugbug: A quantidade de entrada depende to diretório.
	// See: search.c

    // IN: directory address, max number of entries.

    //FreeIndex = (int) findEmptyDirectoryEntry ( 
    //                      VOLUME1_ROOTDIR_ADDRESS, 
    //                      FAT16_ROOT_ENTRIES );
    
    FreeIndex = (int) findEmptyDirectoryEntry ( 
                          dir_address, 
                          dir_entries );

    if ( FreeIndex == -1 )
    {
        printf ("fsSaveFile: [FAIL] No empty entry\n");
        goto fail;
    }


    // 32/2 = 16 words.
    // Offset:
    // Deslocamento dentro do diretório.
    // representa o início da entrada que encontramos.
    // Encontramos multiplicando o índice da entrada pelo 
    // tamanho da entrada.
    // Copy entry into the root in the memory.
    // Copia 32 bytes.
 
    EntrySize = (FAT16_ENTRY_SIZE/2);
    Offset = (int) ( FreeIndex * EntrySize );

    // FAT16_DIRENTRY_SIZE = 32
    memcpy ( &__dir[Offset], DirEntry, 32 );

// reset
// Reiniciamos o controlador antes de usarmos.


//resetIDE:

	//#debug
	//printf("fsSaveFile: reset and while\n"); 
    //refresh_screen();

	//reset_ide0 ();
	
	// ## Save ##
    // Vamos ao salvamento propriamente dito.

    i=0; 

	//#debug 
	//improvisando um endereço válido

    unsigned long address = (unsigned long) file_address;


    //
    // Save!
    //
    
    // Saving the file into the disk.
    // Cluster by cluster.

//SavingFile:

    // Routine:
    // +Pega um conteúdo da lista.
    // +Encontrada a assinatura na lista!
    // ...

    // #bugbug
    // E se o primeiro for um marcador de fim de arquivo?

    //next = list[0];
    //if (next == 0xFFF8)
        //what??
    
    while (1)
    { 
        next = list[i];

        // #debug.
        printf ("next={%x}\n", next);

        if ( next == 0xFFF8 )
        {
            next = list[i-1];
            fat[next] = 0xFFF8; 
            goto do_save_dir_and_fat;    //goto done; 

        // Se não é assinatura ainda.
        }else{

            // Grava na fat o endereço do próximo cluster
            fat[next] = list[i+1];
 
            //#debug 
            //printf("write_lba\n");
            //refresh_screen();

            disk_ata_wait_irq ();

            //grava - aqui next esta certo!!!
            //write_lba ( (unsigned long) address, VOLUME1_DATAAREA_LBA + next -2 );
            my_write_hd_sector ( (unsigned long) address, 
                (unsigned long) ( VOLUME1_DATAAREA_LBA + next -2), 0, 0  );

            address += 512; 
        }; 

        //Próximo valor da lista.
        i++;

        // #bugbug
        // Limitando o tamanho do arquivo a 16 entradas.
        // Why??

        // #bugbug
        // Limite provisorio.
        if (i > 16)
        {
            debug_print ("fsSaveFile: [FIXME] write sectors limit\n");
            printf      ("fsSaveFile: [FIXME] write sectors limit\n");
            goto fail;
        }

        // ??
    };

    //
    // FAIL
    //

    debug_print ("fsSaveFile: Loop fail\n");
    goto fail;
   
    //
    // == done ========================================
    //

    // Saving rood dir and FAT.
    // Nesse momento já salvamos os clusters do arquivo.
    // OK. Funcionou no qemu.
    // #bugbug
    // Não vamos mais salvar a fat toda vez que salvarmos
    // um arquivo.
    // Vamos salvar a FAT apenas no fim da sessão.
    // Como ainda não temos shutdown, então vamos salvar 
    // quando chamarmos reboot.
    // #important
    // Updating the cache state.

do_save_dir_and_fat:

    debug_print ("fsSaveFile: [DEBUG] do_save_dir_and_fat\n");
    
    // Save root
    // #bugbug: We need to save a directory, not the root.

    //if ( dir_address == ROO...
    fs_save_rootdir();
    
    // Save FAT
    
    //fs_save_fat();
    fat_cache_saved = CACHE_NOT_SAVED;

    debug_print ("fsSaveFile: done\n");
    printf      ("fsSaveFile: done\n");
    refresh_screen();
    return 0;

    //
    // == fail ========================================
    //

fail:
    debug_print ("fsSaveFile: [FAIL]\n");
    printf      ("fsSaveFile: [FAIL]\n");
    refresh_screen ();
    return (int) 1;

}


/*
 * fs_save_rootdir:
 *     Salva o diretório raiz no disco.
 *     @todo: Identificar parâmetros do sistema de arquivos atual. 
 */

int fs_save_rootdir (void){

    int r=0;
    int roff=0;
    int rlbaoff=0;


    // #obs:
    // Não precisamos fazer isso o tempo todo.
    // Podemos apenas sinalizar que a sincronização está pendente.
    
    debug_print ("fs_save_rootdir:\n");
    printf ("Saving root..\n");
    refresh_screen ();



	// #bugbug: 
	// Precisamos saber o tamanho do root ... 
	// Precismos de estrututra de root


    for ( r=0; r<32; r++ )
    {
        // #debug
        //printf("write_lba n={%d} \n",r); 
        //refresh_screen();

        // Wait interrupt. Isso funcionou.
        // #bugbug
        // ?? Estamos esperando antes de gravarmos o próximo.
        // wait irq
        disk_ata_wait_irq ();

        // #bugbug: 
        // Não podemos determinar os valores. Precisamos de estruturas.

        my_write_hd_sector ( (unsigned long) ( VOLUME1_ROOTDIR_ADDRESS + roff), 
            (unsigned long) ( VOLUME1_ROOTDIR_LBA + rlbaoff ), 0, 0  );

        roff = (roff + 0x200);
        rlbaoff = (rlbaoff + 1);
        
        // ?? esperar
    };


    return 0;
}


int fs_save_fat (void){

    int f=0;
    int off=0;
    int lbaoff=0;



    debug_print ("fs_save_fat:\n");
    printf ("Saving fat..\n");
    refresh_screen ();



	// #bugbug: 
	// Precisamos saber o tamanho da fat ... 
	// Precismos de estrututra de fat
	//#obs: 
	// Estamos salvando 246 setores da FAT,


    for ( f=0; f<246; f++ )
    {
 
       //#debug
       //printf("write_lba n={%d} \n",f);  
       //refresh_screen();

        // Esperando antes do próximo.
        disk_ata_wait_irq ();


        my_write_hd_sector ( (unsigned long) ( VOLUME1_FAT_ADDRESS + off), 
            (unsigned long) ( VOLUME1_FAT_LBA + lbaoff ), 0, 0  );

        off = (off + 0x200);
        lbaoff = (lbaoff + 1);
        
        // esperar ??
    };


    // #debug
    debug_print ("fs_save_fat: Done\n");
    printf ("fs_save_fat: done\n"); 
    refresh_screen ();

    return 0;
}



/*
 * fs_save_dir:
 *     Salva um diretório.
 */

int
fs_save_dir ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{

    debug_print ("fs_save_dir: [TODO]\n");
    return -1;
    
    // #todo
    // Usar a função que salva arquivo.
    // Nunca testado.
    
    /*
    return (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES,
                    (char *) file_name,    
                    (unsigned long) file_size,       
                    (unsigned long) size_in_bytes,  
                    (char *) file_address,          
                    (char) flag );  
    */
}


int
fs_save_file ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{

    debug_print ("fs_save_file: [Testing]\n");
    return (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES, 
                    (char *) file_name,    
                    (unsigned long) file_size,       
                    (unsigned long) size_in_bytes,  
                    (char *) file_address,          
                    (char) flag );                  
}


/*
 * fs_save_entry_on_root:
 *     Salva uma entrada do diretório raiz, dado o id da estrutura do arquivo.
 * @todo: Checa os parametros do sistema de arquivos e 
 * salva a entrada no diretorio raiz.
 */

void fs_save_entry_on_root (unsigned long eid)
{
    //return;
}


//
// End.
//

