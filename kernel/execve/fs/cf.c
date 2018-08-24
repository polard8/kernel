/*
 * File: fs\cf.c 
 *
 * Descrição: 
 *     Create File.
 *     Rotinas criação de arquivos.
 * Histórico:
 *    Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *    Versão 1.0: 2016 - Revisão.
 *    ...
 */
 
 
#include <kernel.h>


/*
 * fs_create_dir:
 *     Cria um diretório.
 */
unsigned long fs_create_dir( char *name, unsigned long id )
{
	return 1;
	//return fs_create_file( name, id ); 
};


/*
 *****************************************************
 * fs_create_file:
 *     Cria um arquivo.
 */
int fs_create_file ( char *name ){
	
    unsigned long fat_entry;
    unsigned long dir_entry;
	unsigned long size = 1;
	
	// FAT STUFFS.
	
	// Encontra uma entrada vazia na FAT.
	//fat_entry = fs_find_empty_entry(?);
	
	
	// Testar antes a validade da entrada.
	if ( fat_entry == 0 ){
	    printf("fs_create_file error: FatEntry={%d}\n", fat_entry);
		goto fail;
	}
			
	//Erro 1 - Não há mais entradas vazias na FAT.
	if ( fat_entry == FAT_ERRO_1 ){
		printf("fs_create_file error: FAT_ERRO_1, No more empty entries\n");
		goto fail;
	}
		
	//
	if ( fat_entry < 0 || fat_entry > 1024 ){
	    printf("fs_create_file error: FAT entry limits\n");
		goto fail;
	};
			
	// Marca na entrada da FAT como fim de arquivo. (size=1).
	fs_set_fat_entry( fat_entry, 0x0000FFF8 );
	
	
	// ROOT STUFFS.
	
	//#bugbug
	//Procura uma entrada vazia no diretório.
	//@todo:
	//dir_entry = findEmptyDirectoryEntry( ?, ?);
	
    if ( dir_entry == 0 ){
        printf("fs_create_file: No empty entry on this directoty\n");
        goto fail;		
	}
  		 
	if ( dir_entry < 0 || dir_entry > 64 ){
        printf("fs_create_file: Dir entry limits\n");
        goto fail;		
	}
	
	//Cria a entrada no diretório
	//fs_create_entry( name, id, dir_entry, fat_entry, size ); 
	
	//@todo:
	//fs_save_entry_on_root(i);

	//Continua...
		
done:
    printf("fs_create_file: Done FatEntry={%d} DirEntry={%d}\n",
	    fat_entry, dir_entry );
		
    return (int) 0;
	
fail:   
	return (int) 1;
};

	
void fs_create_entry( char *name,            //nome do arquivo
                     unsigned long id,       //id do diretorio
					 unsigned long eid,      //id da entrada de diretorio
					 unsigned long cluster,  //numero do cluster inicial na fat
					 unsigned long size )    //tamanho do arquivo.
					                         //continua
{
    return;
};   



void fs_create_name( char *name, unsigned long id,unsigned long eid)
{
    return;
};   




/*
 * create_system_folders:
 *     Cria pastas do sistema.
 * 
 *     @todo: Isso deve ir para aplicativo de instalação.
 *
 */
void create_system_folders()
{
	return;
};


//
// End.
//

