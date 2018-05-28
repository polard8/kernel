/*
 * File: fs\search.c 
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
 *    Procura por um arquivo, dado o endereço do diretório.
 *    Com o diretório já carregado na memória.
 *
 *   file_name: Nome do arquivo.
 *     address: Endereço na memória onde o diretório está.
 *
 * @todo: 
 *    Atender à especificações diferentes de sistemas de arquivos, como:
 *    +Tamanho do cluster
 *    +Tamanho do disco
 *    +Tipo de sistema de arquivos. 
 *    +...
 *
 */ 
int KiSearchFile( unsigned char *file_name, 
                  unsigned long address )
{
	int Status = 1;
    unsigned long i = 0;        // Deslocamento do dir. 
    unsigned long j = 0;        // Deslocamento no nome.
    unsigned long NumberOfEntries = 512;    // Número máximo de entradas no diretório.	
    
	char NameX[13];	
	
	// Buffer.
	char *dir = (char *) address;

	
	if(  file_name[0] == '/' || 
	     file_name[0] == 0 )
	{
		goto fail;
	};
	
	
    //
    // Address Limits:
	// Endereço de memória onde o diretório está.
    //
	
	if(address == 0){
	    return (int) 1;
	}; 	
	
	//Compare.
    for( i=0; i < NumberOfEntries; i++ )
	{
        // FAT_DIRECTORY_ENTRY_FREE
		if(  dir[j] == (char) 0xE5 )
        {
		    j += 0x20;
            continue;			
		}	

		// diretório atual ou diretório pai.
		// '.' ou '..'
		if(  dir[j] == '.' )
        {
		    j += 0x20;
            continue;			
		}	
		
		// Entrada normal. Diferente de zero.
        if( dir[j] != 0 )
		{
			
			// Copia o nome e termina incluindo o char 0.
			memcpy( NameX, &dir[j], 11 );
			NameX[11] = 0;
			
		    Status = (int) strncmp( file_name, NameX, 11 );
			if(Status == 0){ 
			    goto done; 
			}; 
        };   
		
		//Próxima entrada. Repete 512 vezes.
        j += 0x20;              
    };
	
	//
	// Fail!
	//
	
fail:
    Status = (int) 1;
    printf("fs-search-KiSearchFile: File not found!\n");       	
done:
    return (int) Status;
};



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
int fsSearchFile(unsigned char *file_name)
{
	int Status = 1;	
	unsigned long i = 0;
    unsigned long j = 0;        //Deslocamento do rootdir. 
    unsigned long NumberOfEntries = 512;    //Número máximo de entradas em fat16.
	//...
	
	char NameX[13];	
	char *dir = (char *) VOLUME1_ROOTDIR_ADDRESS; //rootDir->address;	
	
	 
	if(  file_name[0] == '/' || 
	     file_name[0] == 0 )
	{
		goto fail;
	};
	 
    
	//Obs:
    //0x00      Entry never used
    //0xe5      File is deleted
    //0x2e      (A ".") Directory
	
	//Compare.
    for( i=0; i < NumberOfEntries; i++ )
	{
        // FAT_DIRECTORY_ENTRY_FREE
		if(  dir[j] == (char) 0xE5 )
        {
		    j += 0x20;
            continue;			
		}	

		// diretório atual ou diretório pai.
		// '.' ou '..'
		if(  dir[j] == '.' )
        {
		    j += 0x20;
            continue;			
		}	
		
		// Entrada normal. Diferente de zero.
        if( dir[j] != 0 )
		{
			
			// Copia o nome e termina incluindo o char 0.
			memcpy( NameX, &dir[j], 11 );
			NameX[11] = 0;
			
		    Status = (int) strncmp( file_name, NameX, 11 );
			if(Status == 0){ 
			    goto done; 
			}; 
        };   
		
		//Próxima entrada. Repete 512 vezes.
        j += 0x20;              
    };
	
	//More?!
	
fail:
    Status = (int) 1;
    printf("fs-search-fsSearchFile: File not found!\n");       	  
done:
    return (int) Status;
};




/*
 *****************************************************
 * fs_find_empty_entry:
 *     Encontrar uma entrada vazia na fat.
 *     @todo: Isso pe importante:
 */
unsigned short 
fs_find_empty_entry( char *fat_address )
{
	//@todo:
	//encontrar uma entrada vazia na fat.
	//fornecer o endereço da fat na memória.
	return (unsigned short) 0;
};




/*
 **************************************************************
 * findEmptyDirectoryEntry:
 * Procura uma entrada vazia no diretório 
 *
 * IN:
 *     Endereço do diretório e número máximo de entradas.
 */
int 
findEmptyDirectoryEntry( unsigned long dir_address, 
                         int number_of_entries )
{
	int i;
	int j=0;	
	unsigned char *dir = (unsigned char *) dir_address;
	
	//
	// Filtrando limites.
	//
	
	if( dir_address == 0 ){
	    goto fail;	
	}
	
	if( number_of_entries < 0 ){
		goto fail;
	}
	
	
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
};


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
unsigned short 
fs_find_n_empty_entries( int n )
{
    int i;
	int l;
	unsigned short empty;
	
	// Limits.
	if( n < 0 || n > 1024 ){
	    goto fail;
	};
	
	// Loop ~ Procurar uma quantidade de entradas vazias.
	for( i=0; i < n; i++ )
	{	
		//empty = (unsigned short) fs_find_empty_entry(?);
		
		// Preenche a lista de entradas vazias.	
		if( empty != 0 && empty < 1024 )
		{
		    file_cluster_list[l] = (unsigned short) empty;
            l++;
		}else{
		    goto fail;
		};		
	};
		
	//Finaliza a lista com uma assinatura.
    file_cluster_list[l] = 0xFFF8;    
	
done:
    //Retorna o primeiro da lista.	
	return (unsigned short) file_cluster_list[0];
fail:	
    return (unsigned short) 0;
};


/*
 * fsSearchFileName:
 *     Procurar um nome de arquivo em uma pasta.
 *     No caso é o diretório raiz.
 */
//int fsSearchFileName( const char *name ) 
int fsSearchFileName(unsigned char *name)
{
    return (int) fsSearchFile(name);
};


//
// End.
//
