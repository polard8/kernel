/*
 * File: fs/read.c 
 *
 *     Low level routines to read data from the disk.
 * 
 * History:
 *    2015 - Created by Fred nora.
 *    2016~2018 - Revision.
 *    ...
 */


#include <kernel.h>

/*
 #todo: 
     Usar estruturas para gerenciar partição, FAT e Root dir.
 #obs: 
     Cada partição deve ter uma estrutura.
 precisamos checar na estrutura o status da FAT e do 
 diretório raiz, para não carregálos repetidas vezes.
 */ 


//#define read_ToUpper(C) ((((C) >= 'a') && ((C) <= 'z')) ? (C) - 'a' + 'A' : (C))
//#define read_Minimum(X,Y) ((X) < (Y) ? (X) : (Y))
//#define read_Maximum(X,Y) ((X) < (Y) ? (Y) : (X))


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

// #bugbug
// Essa rotina e' independente do sistema de arquivos.

void read_lba ( unsigned long address, unsigned long lba )
{
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
            debug_print ("read_lba: [FAIL] FAT12 not supported\n");
            return;
            break;

        default:
            debug_print ("read_lba: [FAIL] g_currentvolume_fatbits not supported\n");
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

void fs_load_fat(void)
{
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

    // Load the sectors in the memory.

    for ( i=0; i < szFat; i++ ){

        my_read_hd_sector ( 
            (VOLUME1_FAT_ADDRESS + b), 
            (VOLUME1_FAT_LBA + i), 
            0, 
            0 );

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

// #todo
// Create __read_sequential_sectors and __write_sequential_sectors

int
__load_sequential_sectors ( 
    unsigned long address, 
    unsigned long lba, 
    unsigned long sectors )
{
    unsigned long i=0;
    unsigned long b=0;


    debug_print ("__load_sequential_sectors:\n");
    
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
    
    if (buffer == 0){
        debug_print ("fs_load_metafile: [ERROR] buffer\n");
        return;
    }

    if ( size == 0 ){
        debug_print ("fs_load_metafile: [ERROR] size\n");
        return;
    }

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
// O ponteiro para essa estrutura sera salvo na estrutura de processo
// juntamente com o ponteiro da estrutura de cwd.

void fs_load_rootdir (void)
{
    debug_print ("fs_load_rootdir:\n");
    
    __load_sequential_sectors ( 
        VOLUME1_ROOTDIR_ADDRESS, 
        VOLUME1_ROOTDIR_LBA, 
        32 );
}



//
// End.
//

