/*
 * File: fs/search.c 
 * 
 * Descrição:
 *     Rotinas de procura de arquivos, nomes...
 *
 * History:
 *    2015 - Created by Fred Nora.
 *    2016 - Revision.
 *    ...
 */


#include <kernel.h>


/*
 **********************************************************************
 * KiSearchFile:
 *    Procura por um arquivo, dado o endereço do diretório, com o diretório 
 * já carregado na memória.
 *
 *   file_name: Nome do arquivo.
 *     address: Endereço na memória onde o diretório está.
 *
 * #todo: 
 *    Atender à especificações do sistemas de arquivos, como:
 *    +Tamanho do cluster
 *    +Tamanho do disco
 *    +Tipo de sistema de arquivos. 
 *    +...
 */ 

// #todo
// We need to search in the file table first of all.
// The structure found there will give us the inode structure pointer.

// IN:
// File name. "1234578XYZ"
// Address of the directory.

// OUT:
// 1 = Found.

int 
KiSearchFile ( 
    unsigned char *file_name, 
    unsigned long address )
{

    int Status = -1;

    unsigned long i = 0;                  // Deslocamento do dir. 
    unsigned long j = 0;                  // Deslocamento no nome.
    unsigned long NumberOfEntries = 512;  // Número máximo de entradas no diretório.
    // O número de entradas poderia ser passado via argumento.

    char NameX[13];


	// Buffer.
	// #importante: 
	// O endereço do diretório foi passado via argumento.

    char *dir = (char *) address;


    // Invalid first char.

    if ( file_name[0] == '/' || file_name[0] == 0 ){
        printf ("KiSearchFile: Invalid first char\n");
        goto fail;
    }


    // Address Limits:
    // Endereço de memória onde o diretório está.
    
    if (address == 0){
        printf ("KiSearchFile: Invalid dir address\n");
        goto fail;
    }

    
    //
    // Search.
    //


    for ( i=0; i < NumberOfEntries; i++ )
    {
        // FAT_DIRECTORY_ENTRY_FREE
        if ( dir[j] == (char) 0xE5 ){ j += 0x20; continue; }

        // diretório atual ou diretório pai.
        // '.' ou '..'
        if ( dir[j] == '.' ){ j += 0x20; continue; }

        //#TODO
        //pegar o tamanho da string para determinar o quanto comparar.

        // Entrada normal. Diferente de zero.
        if ( dir[j] != 0 )
        {

			// Copia o nome e termina incluindo o char 0.
			memcpy( NameX, &dir[j], 11 );
			NameX[11] = 0;

            Status = (int) strncmp ( file_name, NameX, 11 );

            // Found!
            if (Status == 0){ return 1; }
            
            //Nothing.
        };   
		
		//Próxima entrada. Repete 512 vezes.
        j += 0x20;              
    };



	// Fail!

fail:
    printf ("KiSearchFile: File not found\n");
    return (int) -1;
}


/*
 **********************************************************************
 * fsSearchFile:
 *    Procura por um arquivo no diretório raiz de uma partição.
 *    Com o diretório raiz já carregado na memória.
 *
 * @todo: 
 *    Atender à especificações diferentes de sistemas de arquivos, como:
 *    +Tamanho do cluster
 *    +Tamanho do disco
 *    +Tipo de sistema de arquivos. (nao por enquanto)
 *    +...
 */

//int fsSearchFile( const char *name ) 

int fsSearchFile (unsigned char *file_name){

    int Status = 1;
    unsigned long i = 0;
    unsigned long j = 0;                  //Deslocamento do rootdir. 
    unsigned long NumberOfEntries = 512;  //Número máximo de entradas em fat16.
	//...

    char NameX[13];
    char *dir = (char *) VOLUME1_ROOTDIR_ADDRESS;    //rootDir->address;



    //#obs
    // Não procura um nome começado com '/'
    if ( file_name[0] == '/' || file_name[0] == 0 )
    {
        goto fail;
    }

 
    //Obs:
    //0x00      Entry never used
    //0xe5      File is deleted
    //0x2e      (A ".") Directory


	//Compare.
    for ( i=0; i < NumberOfEntries; i++ )
    {
        // FAT_DIRECTORY_ENTRY_FREE
        if ( dir[j] == (char) 0xE5 ){ j += 0x20; continue; }

		// diretório atual ou diretório pai.
		// '.' ou '..'
        if ( dir[j] == '.' ){ j += 0x20; continue; }

        //#TODO
        //pegar o tamanho da string para determinar o quanto comparar.


		// Entrada normal. Diferente de zero.
        if ( dir[j] != 0 )
        {
			// Copia o nome e termina incluindo o char 0.
			memcpy ( NameX, &dir[j], 11 );
			NameX[11] = 0;
			
            Status = (int) strncmp ( file_name, NameX, 11 );

            if (Status == 0){ goto done; }

			//Nothing.
        };  

		//Próxima entrada. Repete 512 vezes.
        j += 0x20;  
    };


	//More?!
	
fail:
    Status = (int) 1;
    printf ("fsSearchFile: File not found\n");


done:
    return (int) Status;
}


/*
 *****************************************************
 * fs_find_empty_entry:
 *     Encontrar uma entrada vazia na fat.
 *     @todo: Isso pe importante:
 */

	//@todo:
	//encontrar uma entrada vazia na fat.
	//fornecer o endereço da fat na memória.

unsigned short fs_find_empty_entry ( char *fat_address )
{
    debug_print ("fs_find_empty_entry: [TODO]\n");
    return (unsigned short) 0;
}


/*
 **************************************************************
 * findEmptyDirectoryEntry:
 * Procura uma entrada vazia no diretório 
 *
 * IN:
 *     Endereço do diretório e número máximo de entradas.
 */

int 
findEmptyDirectoryEntry ( 
    unsigned long dir_address, 
    int number_of_entries )
{
    int i=0;
    int j=0;
    unsigned char *dir = (unsigned char *) dir_address;


	// Filtrando limites.


    if ( dir_address == 0 )     { goto fail; }
    if ( number_of_entries < 0 ){ goto fail; }


    for ( i=0; i<number_of_entries; i++ )
    {
        if ( dir[j] == 0 ){ return (int) i; }

        // Next entry.
        j = (j+32);
    };


fail:
    return (int) (-1);
}


// #bugbug
// Not tested yet.
// OUT: index.
int search_path_in_the_inode_table( const char *path )
{

    struct inode_d *tmp_inode;
    
    int i=0;
    size_t PathSize = 0;
    int Status = -1;
    
    
    debug_print("search_path_in_the_inode_table: [FIXME] Not tested yet\n");
    
    PathSize = (size_t) strlen(path);
    
    for (i=0; i<32; i++)
    {
        if ( inode_table[i] != 0 )
        {
            tmp_inode = (struct inode_d *) inode_table[i];
            if( (void*) tmp_inode != NULL)
            {
                //#todo validation
                
                //#bugbug: types = (const char *)
                Status = strncmp( path, tmp_inode->path, PathSize );
                if ( Status == 0 ){ return (int) i; }; //ok
            }
        } 
    };
    
    return -1;
}



/*
 ***************************************************************
 * fs_find_n_empty_entries:
 *     Encontrar uma quantidade específica de entradas na fat.
 *     Pois um arquivo demanda uma ou várias entradas, 
 *  dependendo do tamanho.
 * @todo: Corrigir essa função, ela é importante.
 *  Obs: tem algo parecido na função que salva um arquivo.
 *  O retorno deve ser short, mesmo tipo do cluster.
 */

// #bugbug
// empty uninitialized.

unsigned short fs_find_n_empty_entries ( int n ){

    int i = 0;
    int l = 0;
    unsigned short empty = 0;

	// Limits.
    if ( n < 0 || n > 1024 ){ goto fail; }


	// Loop ~ Procurar uma quantidade de entradas vazias.
    for ( i=0; i < n; i++ )
    {
		//empty = (unsigned short) fs_find_empty_entry(?);
		
		// Preenche a lista de entradas vazias.	
        if ( empty != 0 && empty < 1024 )
        {
            file_cluster_list[l] = (unsigned short) empty;
            l++;
        
        }else{ goto fail; };

    };


	//Finaliza a lista com uma assinatura.
    file_cluster_list[l] = 0xFFF8; 


done:
    //Retorna o primeiro da lista.
    return (unsigned short) file_cluster_list[0];


fail:
    return (unsigned short) 0;
}



/*
 ***************************************************
 * fsSearchFileName:
 *     Procurar um nome de arquivo em uma pasta.
 *     No caso é o diretório raiz.
 */

//int fsSearchFileName( const char *name ) 

int fsSearchFileName (unsigned char *name)
{
    return (int) fsSearchFile (name);
}



//
// End.
//
