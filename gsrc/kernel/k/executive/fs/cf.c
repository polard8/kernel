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
unsigned long fs_create_dir( char *name , unsigned long id)
{
	return fs_create_file( name, id); 
};


/*
 * fs_create_file:
 *     Cria um arquivo.
 */
unsigned long fs_create_file( char *name , unsigned long id)
{
    unsigned long fat_entry;
    unsigned long dir_entry;
	unsigned long size = 1;
	
	
	//
	// FAT STUFFS.
	//
	
	// Encontra uma entrada vazia na FAT.
	fat_entry = fs_find_empty_entry();
	
	
	// Testar antes a validade da entrada.
	if( fat_entry == 0 ){
	    printf("fs_create_file error: FatEntry={%d}\n", fat_entry);
		goto fail;
	};
			
	//Erro 1 - Não há mais entradas vazias na FAT.
	if( fat_entry == FAT_ERRO_1 ){
		printf("fs_create_file error: FAT_ERRO_1, No more empty entries!\n");
		goto fail;
	};
		
	//
	if( fat_entry < 0 || fat_entry > 1024 ){
	    printf("fs_create_file error: FAT entry limits!\n");
		goto fail;
	};
			
	// Marca na entrada da FAT como fim de arquivo. (size=1).
	fs_set_fat_entry( fat_entry, 0x0000FFF8 );
		
	
	//
	// ROOT STUFFS.
	//
	
	//Procura uma entrada vazia no diretório.
	dir_entry = fs_search_empty_entry(id);
	
    if( dir_entry == 0 ){
        printf("fs_create_file: No empty entry on this directoty!\n");
        goto fail;		
	};	
  		 
	if(dir_entry < 0 || dir_entry > 64){
        printf("fs_create_file: Directory entry limits!\n");
        goto fail;		
	};	
	
	//Cria a entrada no diretório
	fs_create_entry( name, id, dir_entry, fat_entry, size ); 
	
	
	//@todo:
	//fs_save_entry_on_root(i);

	//Continua...
		
done:
    printf("fs_create_file: Done! FatEntry={%d} DirectoryEntry={%d}\n",fat_entry,dir_entry);
    return (unsigned long) 0;
	
fail:   
	return (unsigned long) 1;
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



//
//salva_nome(.) - salva um nome no diretorio raiz dado o CLUSTER INICIAL
//
void salva_nome( unsigned char *file_name, unsigned long id, unsigned long eid, unsigned long cluster_inicial)
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

/*
    //
	// Aloca memória para as estruturas dos diretórios do sistema.
	//
	 	
	//rootDir
	rootDir = (void*) malloc( sizeof(struct d_dir)); 

	
	if( (void*) rootDir == NULL)
	{
	    printf("create_system_folders: nao foi possivel alocar memoria para rootDir!");
		refresh_screen();
		while(1){}
	};


	
	//bootDir
	bootDir = (void*) malloc( sizeof(struct d_dir)); 
	if( (void*) bootDir == NULL)
	{
	    printf("create_system_folders: nao foi possivel alocar memoria para bootDir!");
		refresh_screen();
		while(1){}
	};

	//systemDir
	systemDir = (void*) malloc( sizeof(struct d_dir)); 	
	if( (void*) systemDir == NULL)
	{
	    printf("create_system_folders: nao foi possivel alocar memoria para systemDir!");
		refresh_screen();
		while(1){}
	};

	//userDir
	userDir = (void*) malloc( sizeof(struct d_dir)); 	
	if( (void*) userDir == NULL)
	{
	    printf("create_system_folders: nao foi possivel alocar memoria para userDir!");
		refresh_screen();
		while(1){}
	};
	
	
	//
	// Coloca na lista.
	//
    fileList[0] = (unsigned long) rootDir;    
    fileList[1] = (unsigned long) bootDir;    
    fileList[2] = (unsigned long) systemDir;    
    fileList[3] = (unsigned long) userDir;    	
	
*/	
done:
    printf("done");	
	return;
};


//
// End.
//

