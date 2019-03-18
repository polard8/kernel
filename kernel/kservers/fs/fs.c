/*
 * File: fs/fs.c 
 *
 * Descrição:
 *    Arquivo principal do file system manager.
 *    Módulo em kernel mode, incluido no kernel base. 
 *    
 *    *IMPORTANTE: A idéia principal é que esse módulo de o suporte ao acesso 
 * a qualquer sistema de arquivo suportado, esteja ele em user mode ou em 
 * kernel mode.
 *
 *    Arquivo principal do módulo fs do executive do kernel..
 *    Gerenciador de arquivos do kernel.
 *    Na verdade o Kernel não tem atribuições de carregar arquivos. Mas
 * ele ofereçe serviços básicos que podem ser chamados pelos aplicativos.
 *
 * Objetivo:
 *    Ofereçer operações nos sistemas de arquivos suportados pelo kernel.
 *    Esse gerenciador chama as funções em kernel mode do sistema de arquivos
 * interno e chama as serviços oferecidos pelos drivers em user mode.
 *
 *    Os drivers em user mode podem oferecer acesso à sistemas de arquivos
 * variados.
 *
 *   Ao kernel, compete as funções básicas de operações com hardware.
 *   O sistema de arquivos suportado pelo kernel é fat16.
 *   Continua ...
 *
 * Observação: 
 *    Os valores das estruturas do sistema de arquivos podem ser salvos 
 * em um registro.
 *    No registro pode ter um registro das operações efetuadas 
 * no sistema de arquivo.
 *   Continua ...
 *   
 * History: 
 *    2015 - Created by Fred Nora.
 *    2016 - Revision.
 *    2019 - fred, pwd and cd support.
 *    ...
 */
 

#include <kernel.h>



//Variáveis internas.
//int fsStatus;
//int fsError;
//...


int fsCheckELFFile ( unsigned long address ){
	
	unsigned char *buffer = (unsigned char *) address;
	
	//.ELF
	if ( buffer[0] != 0x7F ||
		 buffer[1] != 0x45 ||
		 buffer[2] != 0x4C ||
		 buffer[3] != 0x46 )
	{
		printf("fsCheckELFFile: Sig \n");
		//goto fail;
	    return 1;
	}
	
	//Continua...
	
	return 0;
}




// Checando a validade de arquivos binários no formato PE.
// #bugbug: Isso não deve ficar no kernel, pois PE é proprietário.
// Nem usaremos PE no futuro.

int fsCheckPEFile ( unsigned long address ){
	
	unsigned char *buffer = (unsigned char *) address;
	
	//i386
	if ( buffer[0] != 0x4C || buffer[1] != 0x01 )
	{
		printf("fsCheckPEFile: Sig \n");
		//goto fail;
		return 1;
	}
	
	//i486
	
	//Continua...
	
	return 0;
}


/*
 *********************************
 * fsListFiles:
 *     Lista os arquivos em um diretório, dados os índices de disco, 
 * volume e diretório.
 */	

void 
fsListFiles ( int disk_id, 
              int volume_id, 
              int directory_id )
{
	printf ("fsListFiles: disk={%d} vol={%d} dir={%d}\n", 
	    disk_id, volume_id, directory_id );

	// @todo: Checar mais limites.
	
	if ( disk_id == -1 || 
	     volume_id == -1 || 
		 directory_id == -1 )
	{
		goto fail;	
	}
	
	// Show!
	// Se o diretório selecionado é o diretório raiz do VFS.
	
	if ( current_disk == 0 && 
	     current_volume == 0 &&
		 current_directory == 0 )
	{
	    vfsListFiles();
        goto done;		
	};
	
	// @todo: Suportar outros diretórios.
	// ...
	
	goto done;
	
fail:
    printf("fail\n");
done:	
	refresh_screen();
	return;
};


/*
 * fsCreateVFS:
 * 
 * #bugbug: 
 * Isso está errado, agora temos rotinas de vfs em vfs.c
 * CRIANDO O DIRETÓRIO RAIZ DO VFS BASEADO EM STREAMS **
 * criando o diretório '/vfs'
 */

void fsCreateVFS (){
	// #suspenso.
}


/*
int fsIsFAT12();
int fsIsFAT12()
{
   //testa o tipo de fat.
    return 0;
};
*/


/*
int fsIsFAT16();
int fsIsFAT16()
{
    //testa o tipo de fat.
    return 0;
};
*/


/*
int fsIsFAT32();
int fsIsFAT32()
{
    //testa o tipo de fat.
    return 0;
};
*/


/*
 **********************
 * fsList
 *     comando 'dir'.
 *     Listando arquivos em um diretório dado o nome. */

int fsList ( const char *dir_name ){
	
	printf("fsList:\n");
	
	if ( current_target_dir.current_dir_address == 0 )
	{
		printf("current_target_dir.current_dir_address fail, reseting\n");
		refresh_screen();
		current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS; 
	}
	
	if ( dir_name == 0 )
	{
		dir_name = current_target_dir.name;
		
		if ( dir_name == 0 )
		{
		    printf("current_target_dir.name fail\n");			
		}
	}
 
	// name, dir address, number of entries
	
	fsFAT16ListFiles ( (const char *) dir_name,         
		    (unsigned short *) current_target_dir.current_dir_address, 256 );	
	
	return 0;
}


/*
 * fsFAT16ListFiles:
 *     Mostra os nomes dos arquivos de um diretório.
 *     Sistema de arquivos fat16.
 *
 * IN:
 *     dir_address = Ponteiro para um endereço de memória 
 *                   onde foi carregado o diretório. */
 
void 
fsFAT16ListFiles ( const char *dir_name, 
                   unsigned short *dir_address, 
                   int number_of_entries )
{
	// #todo: 
	// O número de entradas é maior no diretório raiz.(512 ?)
	
    int i = 0;
	int max = number_of_entries;         // Número máximo de entradas.
    
	unsigned long j = 0;  // Deslocamento
	
	unsigned short *DirBaseAddress = (unsigned short *) dir_address;
	
	
	if ( number_of_entries <= 0 ){
		return;
	}
	
	//#debug
	//printf("\n");
	printf("fsFAT16ListFiles: Listing names in [%s]\n\n", dir_name );
	
    
	// Mostra.
	i=0; 
	while (i < max)
	{
		// Diferente de vazio.
		if ( DirBaseAddress[j] != 0 ){
			
			//O problema é a terminação da string '\0'
			printf ("%s\n", &DirBaseAddress[j] );
        } 
		
		//(32/2) próxima entrada! (16 words) 512 vezes!
        j += 16;    
        ++i;        
    }; 
	
	//...
	
	//printf ("Done\n");	
	refresh_screen();
}


/*
 * KeLoadFile:
 *     Carraga um arquivo na memória.
 *     @todo: Ke_ não é o certo, pois ke é chamadas 
 *            à rotinas externas. 
 *
 * #bugbug a estrutura de canal será usada para troca 
 * de mensagens S|----|S
 */
int 
KeLoadFile ( struct channel_d *channel, 
            unsigned char *file_name, 
			unsigned long file_address )
{
	return -1;  //#bugbug ??
}


/*
 * get_file:
 *     Obtêm o ponteiro da estrutura do arquivo, dado seu id.
 *     Com um índice da lista de arquivos, a função retorna o ponteiro da
 *     estrutura do arquivo. */
 
// void *get_stream (int Index)

void *get_file (int Index){
	
	//Limits.	
	//@todo: max.
	if(Index < 0){
	    return NULL;
	};
	
    return (void *) Streams[Index];
}


/*
 * set_file:
 *     Coloca na lista de arquivos o ponteiro de estrutura,
 * dado seu id. */
 
//void set_stream ( void *stream, int Index ){ 

void set_file ( void *file, int Index ){
	
	if (Index < 0){
	    return;
	}
	
	// #todo:
	// Limite máximo da lista.
	
    // Structure.
	
	if( (void *) file == NULL )
	{
		return;
	}	
	
	// Include pointer in the list.
	
	Streams[Index] = (unsigned long) file;
}


void fs_test_fat_vector (){
	//Ainda não implementada.
}


unsigned long fs_get_fat_entry (unsigned long n){
	
    //Ainda não implementada.	
    return 0; 
}
											 

void fs_set_fat_entry ( unsigned long n, unsigned long value ){
	
    //Ainda não implementada.	
}


void fs_put_list_on_fat (){
	
	//Ainda não implementada.
}


void fs_set_structures (){
	
	//Ainda não implementada.
}


void fs_set_entry ( unsigned long id, unsigned long eid ){
	//suspensa
}


void fs_get_entry ( unsigned long id, unsigned long eid ){
	//suspensa
}


void fs_show_dir_entry ( unsigned long id, unsigned long eid ){
    //Ainda não implementada.	
}


void fs_show_dir (unsigned long id){	
	//Ainda não implementada.
}


//confere clusers de um diretorio.
unsigned long fs_check_cluster (unsigned long id){
	//Ainda não implementada.
	return 0; 
}


/*
 * fs_check_fat:
 *     Check FAT. */
unsigned long fs_check_fat (){
	
	//Ainda não implementada.
	return 1; 
}


void fs_show_entry ( unsigned long id, unsigned long eid ){	
	//Ainda não implementada.
}


unsigned long 
fs_get_entry_status ( unsigned long id, 
                      unsigned long eid )
{
	//Ainda não implementada.
	return 0; 
}


void 
fs_set_entry_status ( unsigned long id, 
                     unsigned long eid, 
					 unsigned long status )
{
	//Ainda não implementada.
}


/*
 *************
 * fsCheckMbrFile: (Essa rotina pode ser usada pra checar se o volume é fat.)
 *     Checamos um mbr carregado em algum endereço de memória.
 *
 *     Checa o registro do disco. (MBR). (disco do sistema).
 *
 *     Obs: O MBR desse sistema não tem o bpb no inicio do primeiro setor e 
 * sim no final do primeiro setor, antes da tabela de partições.
 *
 * Endereço da memória onde o MBR é carregado na inicialização. 0x00020000.   
 *
 * @todo: Talvez essa rotina pudesse fornecer o endereço do buffer como 
 * argumento.
 * @todo: O mbr do sisco do sistema precisa de uma estruura que 
 * coordene o acesso a ele.
 *
 * #todo: precisa colocar tudo na estrutura que está em fs.h
 */

//void fsCheckMBR(unsigned char* buffer)  //@todo

void fsCheckMbrFile ( unsigned char *buffer ){
	
	//#todo
	//mudar os argumentos para chamarmos as portas ide.
	
	int i;
	unsigned char *mbr = (unsigned char *) buffer; 	

	//setor 0.
	my_read_hd_sector ( (unsigned long) &mbr[0] , 0, 0 , 0 );  
	
	//message:
	printf("\n");
	printf("fsCheckMbrFile: testing MBR ...\n");
	
	// @todo:
	// Checar uma estrutura do mbr do disco do sistema,
	// para validar o acesso à ele.	
	
	// Check signature.
	if ( mbr[0x1FE] != 0x55 || mbr[0x1FF] != 0xAA )
	{	
	    printf("fsCheckMbrFile: Sig FAIL \n" );
        goto fail;		
	}
	
	//jmp
	printf ("JMP: [ %x ", mbr[ BS_JmpBoot + 0 ] );
	printf ("%x ", mbr[ BS_JmpBoot + 1 ] );
	printf ("%x ]\n", mbr[ BS_JmpBoot + 2 ] );
	
	
	//name

	printf("OS name: [ ");
	for ( i=0; i<8; i++ )
	{
	    printf("%c", mbr[ BS_OEMName + i ] );
	};
	printf(" ]\n");
	
	//...
	
	
	printf("Signature: [ %x %x ] \n" , mbr[0x1FE], mbr[0x1FF] );
	
	// Continua ...
    goto done;

	
fail:	
    printf("fail\n");	
done:
    printf("Done\n");
	refresh_screen();
	return;
}


/*
 * fsCheckVbr:
 *     Checa o registro de boot de um volume.
 *     Vai no endereço onde está armazenado o VBR do volume atual
 *     e confere as informações sobre o volume.
 */
void fsCheckVbrFile( unsigned char *buffer ){
	
	unsigned char *vbr = (unsigned char *) buffer; 

	// #todo:
	// Checar uma estrutura do mbr do disco do sistema, para validar o 
	// acesso à ele.	
	
	// Check signature.
	
	if ( vbr[0x1FE] != 0x55 || vbr[0x1FF] != 0xAA )
	{
	    printf("fsCheckVbrFile: Sig. Fail\n");
        goto fail;		
	}
	
	//
	// Continua ...
	//

    goto done;

fail:	
    printf("fsCheckVbrFile: fail\n");	
done:
    printf("Done\n");
	refresh_screen();
	return;
}



/*
 * fs_check_disk:
 *    Checa elementos do disco.
 *    Disco, Volume.
 *    Mbr. Vbr.
 * @todo: Mudar para fsCheckDisk().
 */

void fs_check_disk (){
	
    //printf("fs_check_disk: Initializing..\n");	
	//fsCheckMbrFile();
	//fsCheckVbrFile();
    //...	
    //printf("Done\n");
	//refresh_screen();	
}


/*
 **************************************************
 * MountShortFileName:
 *     This function parses a directory entry name 
 * which is in the form of "FILE   EXT" and puts it in Buffer 
 * in the form of "FILE.TXT".
 *
 * @todo fsMountShortFileName(...)
 */
 
void 
MountShortFileName ( char *buffer, 
                     struct dir_entry_d *entry )
{
    int i=0;
    
    // Get the file name.
    while (i < 8)
    {
        if ( entry->FileName[i] == ' '){
            break;
        }

        buffer[i] = entry->FileName[i];
        i++;
    }
 
    // Get extension.
    if ( (entry->FileName[8] != ' ') )
    {
        buffer[i++] = '.';
        buffer[i++] = (entry->FileName[ 8] == ' ') ? '\0' : entry->FileName[ 8];
        buffer[i++] = (entry->FileName[ 9] == ' ') ? '\0' : entry->FileName[ 9];
        buffer[i++] = (entry->FileName[10] == ' ') ? '\0' : entry->FileName[10];
    }
}


/*
 * set_spc:
 *     Configura spc, 'Sector Per Cluster' em variável global.
 *     ?? #bugbug: De qual disco ?? */
 
void set_spc (int spc){
	
    g_spc = (int) spc;
}


/*
 * get_spc:
 *     Pega spc, Sector Per Cluster.
 *     ?? #bugbug: De qual disco ?? */

int get_spc (){
	
    return (int) g_spc;
}


/*
 * get_filesystem_type:
 *     Pega o tipo de sistema de arquivos.
 *     ?? #bugbug: De qual volume ??  */

int get_filesystem_type (){
	
    return (int) g_filesystem_type;
}


/*
 * set_filesystem_type:
 *     Configura o tipo de sistema de arquivo.
 *     ?? #bugbug: De qual volume ?? */

void set_filesystem_type (int type){
		
    g_filesystem_type = (int) type;
}


/*
 ***********************************************
 * fs_init_fat:
 *     Inicializa a estrutura usada no sistema de arquivos.
 *     fsInitFat()
 *     ?? #bugbug: De qual volume ?? 
 */

void fs_init_fat (){
	
	// File system structure.
	
	if ( (void *) filesystem == NULL )
	{
	    printf("fs_init_fat error: filesystem\n");
	    return;
	}

	// FAT structure.
	
	fat = (void *) malloc ( sizeof(struct fat_d) );

	if ((void *) fat == NULL )
	{
	    printf("fs_init_fat error: fat\n");
	    return;

	}else{
		
	    // Info.
	    
		fat->address = filesystem->fat_address; 
	    fat->type = filesystem->type;
	    
		//Continua ...
	};
	
	// #bugbug
	// Não fizemos nada com a estrutura 'fat'
	// tem que passar esse ponteiro para algum lugar.
	
	// Continua a inicialização da fat.
}
	

/*
 ******************************************************
 * fs_init_structures:
 *     Inicializa a estrutura do sistema de arquivos.
 *     fsInitStructures
 */
 
void fs_init_structures (){
	
    int Type;
	
    filesystem = (void *) malloc ( sizeof(struct filesystem_d) );
	
	if ( (void *) filesystem == NULL )
	{
	    panic ("fs_init_structures: filesystem");
	}else{
		
	    storage->fs = filesystem;	
	};
		
	//Type.
	//#bugbug: 
    //Em qual dico e volume pegamos o tipo de sistema de arquivos.
	
	Type = (int) get_filesystem_type ();   
	
	if ( Type == 0 )
	{
	    printf("fs_init_structures error: Type");
        die();
	}else{
		
	    filesystem->type = (int) Type;	
	};
	
	
    switch (Type)
	{
	    case FS_TYPE_FAT16:
	        
			//Rootdir.
			filesystem->rootdir_address = VOLUME1_ROOTDIR_ADDRESS;
	        filesystem->rootdir_lba = VOLUME1_ROOTDIR_LBA;
	        
			//Fat.
			filesystem->fat_address = VOLUME1_FAT_ADDRESS;
	        filesystem->fat_lba = VOLUME1_FAT_LBA;
	        
			//Dataarea.
			//filesystem->dataarea_address = ??;
	        filesystem->dataarea_lba = VOLUME1_DATAAREA_LBA;
	        
			//sectors per cluster.
			filesystem->spc = (int) get_spc(); //variável
	        filesystem->rootdir_entries = FAT16_ROOT_ENTRIES;
	        filesystem->entry_size = FAT16_ENTRY_SIZE;
			
		    break;
			
	    case FS_TYPE_EXT2:
		    //nothing for now.
		break;
		
		//case FS_TYPE_EXT3: break;
		
        default:
		    //nothing for now.
            break;		
	};
}


/*
 ********************************************************
 * fsInit:
 *     Inicializa o file system manager.
 */
 
int fsInit (){
	
#ifdef EXECVE_VERBOSE
    printf("fsInit: Initializing..\n");
#endif 
	
	debug_print("fsInit:\n");	
 
	// Type - Configura o tipo de sistema de arquivos usado. 
	// No caso, (fat16).
	//
	// @todo: Deve-se checar o volume ativo e ver qual sistema de arquivos está
	//        sendo usado, então depois definir configurar o tipo.
	//        O sistema operacional pode salvar o tipo usado. Nesse caso 
	//        apenas checar se ouve alterações nas configurações de sistema de arquivos.
	//        O registro de configurações de disco pode ser armazenado em arquivos de metadados.
	
	set_filesystem_type (FS_TYPE_FAT16);
	
	
	// SPC 
	// Configura o número de setores por cluster.
	// Nesse caso, são (512 bytes por setor, um setor por cluster).
	
	set_spc(1);
	

	// ## initialize currents ##


	//selecionando disco, volume e diretório.
	//estamos resetando tudo e selecionando o diretório raiz 
	//do vfs ... mas na verdade o diretório selecionado 
	//deveria ser o diretório onde ficam a maioria dos aplicativos.
	//para que o usuário possa chamar o maior número de apps usando 
	//apenas comandos simples.
	//#bugbug: isso deveria se passado pelo boot ??	


	//#bugbug: 
	//Deixaremos cada módulo inicializar sua variável.
	//Mas aqui podemos zerar esses valores.
	
	//current_disk = 0;
	//current_volume = 0;   
	//current_directory = 0;

	// Structures and fat.

#ifdef EXECVE_VERBOSE
	printf("fsInit: Structures..\n");
#endif
	
	fs_init_structures();
	

#ifdef EXECVE_VERBOSE
	printf("fsInit: FAT..\n");
#endif
	
	fs_init_fat();
	
	//
	// ==================== ## Streams ## =========================
	//

	// Agora inicialzamos as stream 4 e 5.
	// As anteriores foram inicializadas em stdio,
	// pois são o fluxo padrão.	
	
	
	//
    //  ## volume 1 root dir  ##
	//
	
	
	//foi definido em stdio.h
	//FILE *volume1_rootdir;
	
	volume1_rootdir = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) volume1_rootdir == NULL )
	{
	    printf("fsInit: volume1_rootdir");
	    die ();

	} else {

	    volume1_rootdir->_base = (char *) VOLUME1_ROOTDIR_ADDRESS;
	    volume1_rootdir->_ptr = (char *) VOLUME1_ROOTDIR_ADDRESS;
	    volume1_rootdir->_cnt = (32 * 512) ;
	    volume1_rootdir->_file = 0; //?
	    volume1_rootdir->_tmpfname = "volume1-stream";

	    Streams[4] = (unsigned long) volume1_rootdir;

	    storage->stream = volume1_rootdir; 		
	};


	//
	//  ## volume 2 root dir  ##
	//
	
	
	//foi definido em stdio.h
	//FILE *volume2_rootdir;

	volume2_rootdir = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) volume2_rootdir == NULL )
	{
	    printf("fsInit: volume2_rootdir");
	    die ();
	} else {
		
	    volume2_rootdir->_base = (char *) VOLUME2_ROOTDIR_ADDRESS;
	    volume2_rootdir->_ptr = (char *) VOLUME2_ROOTDIR_ADDRESS;
	    volume2_rootdir->_cnt = (32 * 512) ;
	    volume2_rootdir->_file = 0; //?
	    volume2_rootdir->_tmpfname = "volume2-stream";
	
	    Streams[5] = (unsigned long) volume2_rootdir;
	};
	
	
	//
	// ## Inicializando os pipes usados em execve ## 
	//
	
	
	//gramado core init execve 
	
	//aloca memória para a estrutura.
	pipe_gramadocore_init_execve = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) pipe_gramadocore_init_execve == NULL )
	{
		printf("fsInit: pipe_gramadocore_init_execve");
		die ();
	}else{
		
	
	    //aloca memória para o buffer.
	    unsigned long pipe0base = (unsigned long) malloc(512);
	    
		if ( (void *) pipe0base == NULL )
	    {
		    printf("fsInit: pipe0base");
		    die ();
	    }
	
	    pipe_gramadocore_init_execve->_base = (char *) pipe0base;
	    pipe_gramadocore_init_execve->_ptr  = (char *) pipe0base;
	    pipe_gramadocore_init_execve->_cnt  = 512;
	    pipe_gramadocore_init_execve->_file = 0; //??
	    pipe_gramadocore_init_execve->_tmpfname = "pipe0";
	
	    //0
	    Pipes[0] = (unsigned long) pipe_gramadocore_init_execve;			
	};	
	
	
	//
	// ## PWD ##
	//
	
	//inicializa p pwd support.
	fsInitializeWorkingDiretoryString ();
	
	//
	// ## target dir struct ##
	//	
	
	//inicializa a estrutura de suporte ao target dir.
	fsInitTargetDir();
	
	//
	// @todo: Continua ...
	//
	
//done:

#ifdef EXECVE_VERBOSE
    printf("Done\n");
#endif 

    return (int) 0;    	
}


/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */
 
void fsInitializeWorkingDiretoryString (){
	
	struct volume_d *v;
	
	// root:/volumeX
    char volume_string[8];   
	
	volume_string[0] = 'v';
	volume_string[1] = 'o';
	volume_string[2] = 'l';
	volume_string[3] = 'u';
	volume_string[4] = 'm';
	volume_string[5] = 'e';
	volume_string[6] = (char)( '1' + (char) current_volume - (char) 1 );
	volume_string[7] = '\0';

	//'root:'
	//  ## volume list ##
	//primeiro colocamos a string que indica a lista de volumes. 
	
    sprintf ( current_workingdiretory_string, FS_ROOT_STRING ); 

	//'/'
	// ## separador ##
	strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );

	//
	//  ## volume root dir ##	
	//

	v = (struct volume_d *) volumeList[current_volume];
	
	if ( (void *) v == NULL )
	{
		printf("fsInitializeWorkingDiretoryString: v\n");
		die();
		
	}else{
		
		if ( v->used != 1 || v->magic != 1234 )
		{
		    printf("fsInitializeWorkingDiretoryString: validation\n");
		    die();
		}

	    switch (v->id)
		{
			//case 0:
		        //global usada para string do nome do volume.
			//    current_volume_string = (char *) FS_VOLUME0_STRING;
			//    break;

			//case 1:
		        //global usada para string do nome do volume.
			//   current_volume_string = (char *) FS_VOLUME1_STRING;
			//   break;
			
			default:
		        //fail.
		        //printf("fsInitializeWorkingDiretoryString: default volume #todo\n");
		        //die();			    
			    current_volume_string = (char *) volume_string; 
				break;
		}


		//path string na estrutura do volume.
        sprintf ( v->path_string, current_volume_string ); 	

	    //'volumeX'
	    strcat ( current_workingdiretory_string, v->path_string );
	    //strcat ( current_workingdiretory_string, current_volume_string );		
	}
	

	// ## separador ##
	strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );	

	//More ?...
    pwd_initialized = 1;
}


/*
 ***************************
 * fsInitTargetDir:
 *     Para inicializarmos o sistema ja' com um alvo, no caso o root dir. */

void fsInitTargetDir (){
	
	current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
	//current_target_dir.name = ?;
}


/*
 **************************************
 * fs_initialize_process_pwd:
 *     Cada processo deve inicialiar seus dados aqui. */

int fs_initialize_process_pwd ( int pid, char *string ){
	
	int i;	
	struct process_d *p;
	
	if ( pwd_initialized == 0 )
	{
		printf ("fs_initialize_process_pwd: pwd not initialized\n"); 
		die();
	} 
	
	if (pid<0)
		return 1;	
		
    if ( (void *) string == NULL )
	    return 1;    
			
    //#importante
	//Vamos copiar a string para a estrutura do processo atual.
	
	p = (struct process_d *) processList[pid];
	
	if ( (void *) p == NULL )
	{
	    printf ("fs_initialize_process_pwd: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fs_initialize_process_pwd: validation\n");
	        die ();
	    }
		
	    for ( i=0; i<32; i++ )
	    {
	        p->pwd_string[i] = string[i];	
	    }
	};
	
    return 0;
}


/*
 * fs_print_process_pwd
 *     Cada processo tem seu próprio pwd.
 *     Essa rotina mostra o pathname usado pelo processo. */

int fs_print_process_pwd (int pid){
	
	struct process_d *p;
	
	if ( pwd_initialized == 0 )
	{
		printf("fs_print_process_pwd: pwd not initialized\n"); 
		die();
	} 	

	if (pid<0)
		return 1;	
	
	p = (struct process_d *) processList[pid];
	
	if ( (void *) p == NULL )
	{
	    printf("fs_print_process_pwd: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fs_print_process_pwd: validation\n");
	        die ();
	    }
		
		printf ("\n PID=%d %s (%s) \n\n", p->pid, p->pwd_string, 
			current_target_dir.name );
		
		
		refresh_screen();
		return 0;
	};
	
    //fail.
    return -1;	
}


/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global. */ 
 
void fsUpdateWorkingDiretoryString ( char *string ){
	
	int i;    
	struct process_d *p;
	
	char *tmp;
	
	tmp = string;

	
	if ( pwd_initialized == 0 )
	{
		printf("fsUpdateWorkingDiretoryString: pwd not initialized\n"); 
		return;
	}  	
	
    if ( (void *) string == NULL )
	    return;  
	
	p = (struct process_d *) processList[current_process];
	
	if ( (void *) p == NULL )
	{
	    printf ("fsUpdateWorkingDiretoryString: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fsUpdateWorkingDiretoryString: validation\n");
	        die ();
	    }
		
        if ( (void *) string == NULL )
	    {
			printf ("fsUpdateWorkingDiretoryString: string\n");
		    return;
	    
		} else {
			
			//#importante
			//Colocamos um novo nome no fim do path;
			//atualiza a string do processo atual.
			
		    strcat ( p->pwd_string, string );	

	        // ## separador ##
		    strcat ( p->pwd_string, FS_PATHNAME_SEPARATOR );				
		
	        //atualiza a string global.
			//usando a string do processo atual.
			
			for ( i=0; i<32; i++ )
			{
				current_workingdiretory_string[i] = p->pwd_string[i];	
			}
			
			//name
			
			for ( i=0; i< 11; i++ )
			{
				current_target_dir.name[i] = *tmp;
				tmp++;
			}
		}		
	}	
}


/* 
 ************************************************
 * fs_pathname_backup:
 *     Remove n nomes de diretório do pathname do processo indicado no 
 * argumento.
 *     Copia o nome para a string global.
 *     Remove the last N directories from PATH.  
 *     Do not leave a blank path.
 *     PATH must contain enough space for MAXPATHLEN characters. 
 *     #obs: O PID costuma ser do processo atual mesmo. 
 *     Credits: bash 1.05 */
 
void fs_pathname_backup ( int pid, int n ){
	
	int i;
	struct process_d *p;
		
	if ( pwd_initialized == 0 )
	{
		printf("fs_pathname_backup: pwd not initialized\n"); 
		return;
	}  

	if ( pid<0 ){
		printf("fs_pathname_backup: PID\n"); 
		return;
	}
	
	p = (struct process_d *) processList[pid];
	
	if ( (void *) p == NULL )
	{
	    printf("fsUpdateWorkingDiretoryString: p\n");
	    die ();
		
	}else{
		
	    if ( p->used != 1 || p->magic != 1234 )
	    {
	        printf("fsUpdateWorkingDiretoryString: validation\n");
	        die ();
	    }
		
        char *path = (char *) p->pwd_string;
	
        register char *s = path + strlen( path );
 
        if (*path)
            s--;

        while (n--)
        {
            while (*s == '/')
	            s--;

            while (*s != '/')
	            s--;

            *++s = '\0';
        };	
		
		//atualizando a string global.
		for ( i=0; i<32; i++ )
		{
			current_workingdiretory_string[i] = p->pwd_string[i];	
		}
		
		// name.
		
		for ( i=0; i< 11; i++ )
		{
			current_target_dir.name[i] = '\0';
		}
	}
}


/*
 * sys_read_file:
 *     Interface para carregar arquivo ou diretório.
 *     Essa rotina é chamada por services em services.c
 *     Essa rotina não é mais usara. (backup),
 *     Agora estamos usando sys_read_file2.
 *     #suspensa. #deletar;
 */

int sys_read_file ( unsigned long name, unsigned long address ){	
	//fail
    int Ret = -1;	
	
	
	//#bugbug
	//Estamos usando o diretório raiz.
	//a rotina sys_read_file2 carrega do diretório alvo.
	
    taskswitch_lock();
    scheduler_lock();			
    
	Ret = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS,  
				    VOLUME1_ROOTDIR_ADDRESS, 
	                (unsigned char *) name, 
					(unsigned long) address );    		
	
	scheduler_unlock();
    taskswitch_unlock();
	
	return (int) Ret;
			
fail:			
    return 1;	
}


/*
 **************************
 * sys_read_file2
 *     carrega do diretório alvo. */

FILE *sys_read_file2 ( unsigned long name, unsigned long address ){
	 
	 FILE *stream;
	
	 //alocando memoria para a estrutura.
	 stream = (FILE *) malloc ( sizeof(FILE) );
	
	 if ( (void *) stream == NULL )
	 {
	     return (FILE *) 0;
	 }else{
		
     	 //stream->_base = (char *) address;
		 //stream->_ptr = stream->_base;
		 //stream->_cnt = 0;
		 //stream->_flag = 0;
		 //...
		 
	     //printf("sys_read_file2: struct ok \n");
		 //printf("base=%x \n",stream->_base);
		 //printf("ptr=%x  \n",stream->_ptr);
		
	 };
	

	 //#importante, 
	 //A atualizaçao do nome é feita aqui.
	 
	//update name.
	 fsUpdateWorkingDiretoryString ( (char *) name );	
	 

	int Ret = -1;	
	int i;
	
	unsigned long new_address;
	  
	//#importante
	//temos que respeitar o endereço passaro pelo usu'ario.
	
	new_address =  address;

	
	if ( new_address == 0 )
	{
		printf("address fail\n");
		//return -1;
		return (FILE *) 0;
	}
	
	//#bugbug
	//tenta carregar o diret'orio que tem o endereço indicado aqui, 
	//se falhar carregue o root por enquanto.
	
	if ( current_target_dir.current_dir_address == 0 )
	{
	    printf("sys_read_file2: current_target_dir.current_dir_address fail \n");
		
		//reset.
		current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
		
		for ( i=0; i< 11; i++ )
		{
			current_target_dir.name[i] = '\0';
		}		
		
		//return -1;
		return (FILE *) 0;
	}
	
	//#debug
	//printf ("sys_read_file2: dir_name=(%s) dir_addr=(%x) #debug \n",
	//    current_target_dir.name, current_target_dir.current_dir_address );
	
	
	size_t s = (size_t) fsGetFileSize ( (unsigned char *) name );
	
	
		stream->_base = (char *) new_address;
		stream->_ptr  = (char *) new_address;	
	    stream->_cnt = s;
	
	    stream->_file = 0;
	    stream->_tmpfname = (char *) name;		
	
		
	     printf("sys_read_file2: struct ok \n");
		 printf("base=%x \n",stream->_base);
		 printf("ptr=%x  \n",stream->_ptr);
	
		
    taskswitch_lock();
    scheduler_lock();			
    
	Ret = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS,  
				    current_target_dir.current_dir_address,    //src dir address 
	                (unsigned char *) current_target_dir.name, 
					(unsigned long) new_address );    		   //dst dir address
	
	scheduler_unlock();
    taskswitch_unlock();
	
	//se o carregamento funcionou ou n~ao.
	
	if ( Ret == 0)
	{
		printf("sys_read_file2: done\n");

        current_target_dir.current_dir_address = new_address;
		return (FILE *) stream;
		
	}else{
	
		current_target_dir.current_dir_address = 0;
		//fclose(stream);
	    return (FILE *) 0;
	}
	
	return (FILE *) 0;
}


/*
 ********************************
 * fsLoadFileFromCurrentTargetDir:
 *     Carrega o diretório que está configurado como target dir 
 * em algum lugar qualquer da memória. */

int fsLoadFileFromCurrentTargetDir (){
	
	int Ret = -1;	
	int i;
	
	unsigned long new_address;
	
	//#bugbug
	//Isso 'e um limite para o tamanho do arquivo (apenas dir).
	//precisamos expandir isso.
	//aqui no m'aquimo o arquivo pode ter 4kb.
	//acho ques estamos falando somente de diret'orio aqui.	
	
	new_address = (unsigned long) malloc (4096);
	if ( new_address == 0 )
	{
		return -1;
	}
	
	//#bugbug
	//tenta carregar o diret'orio que tem o endereço indicado aqui, 
	//se falhar carregue o root por enquanto.
	
	if ( current_target_dir.current_dir_address == 0 )
	{
	    printf("fsLoadCurrentTargetDir current_target_dir.current_dir_address fail \n");
		
		//reset.
		current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
		
		for ( i=0; i< 11; i++ )
		{
			current_target_dir.name[i] = '\0';
		}		
		
		return -1;
	}
	
	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) old_dir_addr=(%x) #debug \n",
	//    current_target_dir.name, current_target_dir.current_dir_address );
	
		
    taskswitch_lock();
    scheduler_lock();			
    
	Ret = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS,  
				    current_target_dir.current_dir_address,    //src dir address 
	                (unsigned char *) current_target_dir.name, 
					(unsigned long) new_address );    		   //dst dir address
	
	scheduler_unlock();
    taskswitch_unlock();
	
	
	current_target_dir.current_dir_address = new_address;
	
	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) new_dir_addr=(%x) #debug \n",
	//   current_target_dir.name, current_target_dir.current_dir_address );
	
	return (int) Ret;
}



/*
 * sys_write_file:
 *     Interface para salvar arquivo ou diretório.
 *     Isso pode ser usado para criar um diretório ou copiar um diretório. */

int
sys_write_file ( char *file_name, 
                 unsigned long file_size,
                 unsigned long size_in_bytes,			
                 char *file_address,
                 char flag )  
{
	
	//#todo:
	//vamos fazer igual ao sys_read_file 
	//e criarmos opções ... se possível.
	
	int Ret = -1;
    
	taskswitch_lock();
	scheduler_lock();	
		    
	Ret = (int) fsSaveFile ( (char *) file_name,    //name
	                (unsigned long) file_size,      //3, //@todo: size in sectors 
				    (unsigned long) size_in_bytes,  //255, //@todo: size in bytes
				    (char *) file_address,          //arg3,//address
				    (char) flag );                  //,arg4 ); //flag
						
	scheduler_unlock();
	taskswitch_unlock();

    return Ret;	
}


//
// End.
//

