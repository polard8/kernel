
// search.c  

#include <kernel.h>  

/*
 **********************************************************************
 * search_in_dir:
 * 
 *    Procura por um arquivo, dado o endereço do diretório, 
 * com o diretório já carregado na memória.
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
search_in_dir ( 
    const char *file_name, 
    unsigned long dir_address )
{

    int Status = -1;

    unsigned long i = 0;                  // Deslocamento do dir. 
    unsigned long j = 0;                  // Deslocamento no nome.
    unsigned long NumberOfEntries = 512;  // Número máximo de entradas no diretório.
    // O número de entradas poderia ser passado via argumento.

    char NameX[13];
    
    // Copy here
    char NameBuffer[13];


	// Buffer.
	// #importante: 
	// O endereço do diretório foi passado via argumento.

    char *dir = (char *) dir_address;


    // #bugbug
    // Vamos checar o tamanho da string
    // Me parece que quando um nome tem extensão
    // com menos de três letras, então as últimas 
    // letras etão com '0' e não espaços.

    size_t stringSize = 0;


    debug_print ("search_in_dir: $\n");
    
    //
    // Copy file name
    //

    stringSize = strlen(file_name);
    printf ("Name size = {%d}\n",stringSize);


    strncpy (NameBuffer, file_name, stringSize);



    if (stringSize < 11 )
    {
        //while(stringSize<11)
        //{
        //    strcat(NameBuffer," ");
        //    stringSize++;
        //}
        //printf ("NameBuffer={%s}\n",NameBuffer);
            
            //#debug
        //refresh_screen();
            //while(1){}
    
        if (stringSize == 10)
        { 
            NameBuffer[10] = ' '; 
            stringSize=11;
        }
        
        if (stringSize ==  9)
        { 
            NameBuffer[10] = ' '; 
            NameBuffer[9]  = ' '; 
            stringSize=11;
        }
        
        if (stringSize ==  8)
        { 
            NameBuffer[10] = ' '; 
            NameBuffer[9]  = ' '; 
            NameBuffer[8]  = ' '; 
            stringSize=11;
        }
        
    }
    
    NameBuffer[11] = 0;    
    

    // hack hack
    if (stringSize != 11 ){
        printf ("search_in_dir: [ERROR] Wrong name size. {%d} \n", stringSize);
        goto fail;
    }


    if ( (void*) file_name == NULL ){
        printf ("search_in_dir: [ERROR] file_name\n");
        goto fail;
    }

    if ( *file_name == 0 ){
        printf ("search_in_dir: [ERROR] *file_name\n");
        goto fail;
    }

    if ( *file_name == '/' ){
        printf ("search_in_dir: [FIXME] absolute pathname not supported yet.\n");
        goto fail;
    }


    // Address Limits:
    // Endereço de memória onde o diretório está.
    
    if (dir_address == 0){
        printf ("search_in_dir: Invalid dir address\n");
        goto fail;
    }

    // Search

    for ( i=0; i < NumberOfEntries; i++ )
    {
        // FAT_DIRECTORY_ENTRY_FREE
        if ( dir[j] == (char) 0xE5 ){ j += 0x20; continue; }

        // diretório atual ou diretório pai.
        // '.' ou '..'
        if ( dir[j] == '.' )        { j += 0x20; continue; }

        //#TODO
        //pegar o tamanho da string para determinar o quanto comparar.

        // Entrada normal. Diferente de zero.
        // Copia o nome e termina incluindo o char 0.
        if ( dir[j] != 0 )
        {
            memcpy( NameX, &dir[j], 11 );
            NameX[11] = 0;

            //Status = (int) strncmp ( file_name, NameX, 11 );
            Status = (int) strncmp ( NameBuffer, NameX, 11 );
            
            // Found!
            if (Status == 0)
            {
                // #debug
                debug_print("search_in_dir: Found $\n");
                printf ("search_in_dir: Found\n"); 
                return (int) TRUE; 
            }

            //Nothing.
        }
        
        // Próxima entrada. Repete 512 vezes.
        j += 0x20;
    };

fail:
    debug_print("search_in_dir: Not found $\n");
    printf ("search_in_dir: File not found\n");
    // return FALSE;
    return (int) -1;
}


int search_in_root ( const char *file_name )
{

    if ( (void*) file_name == NULL ){
        debug_print ("search_in_root: [ERROR] file_name\n");
        return -1;
    }

    if ( *file_name == 0 ){
        debug_print ("search_in_root: [ERROR] *file_name\n");
        return -1;
    }

    // IN: filename, dir address
    return (int) search_in_dir ( file_name, VOLUME1_ROOTDIR_ADDRESS );
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
// Search in file_cluster_list[]

unsigned short fs_find_n_empty_entries ( int n )
{

    //
    // #fixme
    //

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

    // Finaliza a lista com uma assinatura.

    file_cluster_list[l] = 0xFFF8; 


// Retorna o primeiro da lista.
done:
    return (unsigned short) file_cluster_list[0];
fail:
    return (unsigned short) 0;
}

/*
 * findEmptyDirectoryEntry:
 * Procura uma entrada vazia no diretório 
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


    if ( dir_address == 0 )     { goto fail; }
    if ( number_of_entries < 0 ){ goto fail; }


    // The entry size is 32 bytes.

    for ( i=0; i<number_of_entries; i++ )
    {
        if ( dir[j] == 0 ){ return (int) i; }

        j = (j+32);
    };

fail:
    return (int) (-1);
}

/*
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

// #todo
// Include 'dir address' as parameter.

// only on root dir.

//int fsSearchFile( const char *name ) 
int fsSearchFile (const char *file_name)
{
    debug_print ("fsSearchFile:\n");
    
    // #todo
    // Well, here we can search on different places 
    // using search_in_dir(,);

    return (int) search_in_root(file_name);
}

/*
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


    if ( (void*) path == NULL ){
        debug_print("search_path_in_the_inode_table: [ERROR] path\n");
        return -1;
    }

    if (*path == 0){
        debug_print("search_path_in_the_inode_table: [ERROR] *path\n");
        return -1;
    }
 
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

//
// End.
//

