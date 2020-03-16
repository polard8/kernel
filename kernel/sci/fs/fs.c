/*
 * File: fs/fs.c 
 *
 * Descri��o:
 *    Arquivo principal do file system manager.
 *    M�dulo em kernel mode, incluido no kernel base. 
 *    
 * IMPORTANTE: 
 * A id�ia principal � que esse m�dulo de o suporte ao acesso a qualquer 
 * sistema de arquivo suportado, esteja ele em user mode ou em kernel mode.
 *
 * Arquivo principal do m�dulo fs do executive do kernel..
 * Gerenciador de arquivos do kernel.
 * Na verdade o Kernel n�o tem atribui��es de carregar arquivos. Mas ele 
 * ofere�e servi�os b�sicos que podem ser chamados pelos aplicativos.
 *
 * Objetivo:
 * Ofere�er opera��es nos sistemas de arquivos suportados pelo kernel.
 * Esse gerenciador chama as fun��es em kernel mode do sistema de arquivos
 * interno e chama as servi�os oferecidos pelos drivers em user mode.
 *
 * Os drivers em user mode podem oferecer acesso � sistemas de arquivos
 * variados.
 *
 * Ao kernel, compete as fun��es b�sicas de opera��es com hardware.
 * O sistema de arquivos suportado pelo kernel � fat16.
 * Continua ...
 *
 * Observa��o: 
 *    Os valores das estruturas do sistema de arquivos podem ser salvos 
 * em um registro.
 *    No registro pode ter um registro das opera��es efetuadas 
 * no sistema de arquivo.
 *   Continua ...
 *   
 * History: 
 *    2015 - Created by Fred Nora.
 *    2016 - Revision.
 *    2019 - fred, pwd and cd support.
 *    ...
 */



// #todo
// A tabela de montagem guarda relação com os volumes existentes.
// Esses volumes podem ser de vários tipos.
// See: syssm/storage/storage.c

 

#include <kernel.h>


// Get free slot.
int fs_get_mounted_free_slot (void){

    int i;
    for (i=0; i<128; i++){
        if ( mountedList[i] == 0 )
            goto __ok;
    }

   //fail
    return (int) (-1);

__ok:
    return (int) i;
}




//IN: Índice na lista de volumes. volumeList[i].
int 
fs_mount_volume ( struct disk_d *d, 
                  struct volume_d *v,
                  char *name,
                  size_t len )
{

    struct mounted_d *m;
    int __slot = -1;
    int i;
    
    
    if ( (void *) name == NULL ){
        debug_print ("fs_mount_volume: name");
        return -1;
    }
    
    
    if (len<0 || len>63){
        debug_print ("fs_mount_volume: len");
        len = 8;
        //return -1;    
    }
    
    
    __slot = fs_get_mounted_free_slot();
    
    if (__slot < 0){
        debug_print ("fs_mount_volume: no more slots");
        panic ("fs_mount_volume: no more slots");
    }


    m = (struct mounted_d *) kmalloc ( sizeof(struct mounted_d) );

    if ( (void *) m == NULL ){
        panic ("fs_mount_volume: m");
    }else{

        m->id = __slot;
    
        m->used = 1;
        m->magic = 1234;

        m->disk = (struct disk_d *) d;
        m->volume = (struct volume_d *) v;
        
        
        m->mountedName_len = len;
    
        for (i=0; i<len; i++)
            m->__mountedname[i] = name[i];
            
        m->__mountedname[i+1] = 0;  
    
        if (__slot >= 128)
            panic("fs_mount_volume: __slot limits");

        mountedList[__slot] = (unsigned long) m;
    
        return 0;
    };


    return -1;
}


void fs_initialize_mounted_list(void)
{
   int i;
   for (i=0; i<128; i++)
       mountedList[i] = (unsigned long) 0;
   
   
   //Vamos montar os volumes criados em storage.c
   

   fs_mount_volume (____boot____disk, volume_bootpartition, "/", 1 );  //root
   fs_mount_volume (____boot____disk, volume_systempartition, "/data", 5 ); //system
   fs_mount_volume (NULL, volume_vfs, "/vfs", 4 );
}


void fs_show_mounted(int i)
{
    struct mounted_d *m;


    if(i<0)
        return;


    m = (struct mounted_d *) mountedList[i];

    if ( (void *) m == NULL ){
        return;

    }else{


        printf ("\n====================================\n");
        printf ("%d) %s\n",m->id,m->__mountedname);
        //printf ("fs_show_mounted: \n");
        //printf ("id %d\n",m->id);
        //printf ("used %d\n",m->used);
        //printf ("magic %d\n",m->magic);


        if ( (void *) m->disk != NULL )
            diskShowDiskInfo(m->disk->id);

        if ( (void *) m->volume != NULL )
            volumeShowVolumeInfo(m->volume->id);
        

        refresh_screen ();        
    };
}



//mostra a lista de volumes montados.
void fs_show_mounted_list(void)
{
   int i;
   for (i=0; i<128; i++)
   {
       if( mountedList[i] != 0)
           fs_show_mounted(i);
   }
}







// na lista de arquivos do processo.
int fs_get_free_fd ( int pid )
{

    struct process_d *p;
    int __slot;


    //if (pid<0 || pid >= max????)
        //return -1;

    //
    // Process.
    //
  
    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL )
        return -1;

    if ( p->used != 1 || p->magic != 1234 )
        return -1;
        
        
    // Pick a free one.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){
             return (int) __slot;
         }
    };
 
     return -1;
}


/*
int vfs_root_mounted(void);
int vfs_root_mounted(void)
{
    return (root)?1:0;
}
*/



/*
int fs_file_seek (file *f, int pos);
int fs_file_seek (file *f, int pos)
{
    if( (void*) f == NULL )
        return -1;
        
    f->_w = 0;
    f->_r = 0;
    return 0;
}
*/


//Vari�veis internas.
//int fsStatus;
//int fsError;
//...


// #todo
/*
int fs_count_separators( const char *path);
int fs_count_separators( const char *path){

    size_t count = 0;
    int i;

    
    for (i=0; i < strlen(path); i++)
    {
        if (path[i] == '/')
        {
            count++;
        }
    };


    return (size_t) count;
}
*/


int fsCheckELFFile ( unsigned long address ){

    unsigned char *buffer = (unsigned char *) address;

	// #todo: Error message.
    //if ( (void *) address == NULL )
        //return -1;

    if ( buffer[0] != 0x7F ||
         buffer[1] != 0x45 ||
         buffer[2] != 0x4C ||
         buffer[3] != 0x46 )
    {
        printf ("fsCheckELFFile: Sig \n");
        return 1;
    }

	// Continua...


    return 0;
}




// Checando a validade de arquivos bin�rios no formato PE.
// #bugbug: Isso n�o deve ficar no kernel, pois PE � propriet�rio.
// Nem usaremos PE no futuro.

int fsCheckPEFile ( unsigned long address ){

    unsigned char *buffer = (unsigned char *) address;

	// #todo: Error message.
    //if ( (void *) address == NULL )
        //return -1;

	//i386
    if ( buffer[0] != 0x4C || buffer[1] != 0x01 )
    {
        printf ("fsCheckPEFile: Sig \n");
        return 1;
    }

	//i486

	//Continua...


    return 0;
}


/*
 *********************************
 * fsListFiles:
 *     Lista os arquivos em um diret�rio, dados os �ndices de disco, 
 * volume e diret�rio.
 */

void 
fsListFiles ( int disk_id, 
              int volume_id, 
              int directory_id )
{
	// @todo: Checar mais limites.

    if ( disk_id == -1 || volume_id == -1 || directory_id == -1 )
    {
        goto fail;
    }

    printf ("fsListFiles: disk={%d} vol={%d} dir={%d}\n", 
        disk_id, volume_id, directory_id );

	// Show!
	// Se o diret�rio selecionado � o diret�rio raiz do VFS.

    if ( current_disk == 0 && current_volume == 0 && current_directory == 0 )
    {
        vfsListFiles ();
        goto done;
    }

	// @todo: Suportar outros diret�rios.
	// ...

    goto done;


fail:
    printf ("fail\n");

done:
    refresh_screen ();
    return;
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
 **********************
 * fsList
 *     dir command support.
 *     #bugbug: We don't want this in the kernel.
 */

int fsList ( const char *dir_name ){

    printf ("fsList:\n");

    if ( current_target_dir.current_dir_address == 0 )
    {
        printf ("current_target_dir.current_dir_address fail, reseting\n");
        refresh_screen ();
        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS; 
    }

    if ( dir_name == 0 )
    {
        dir_name = current_target_dir.name;

        if ( dir_name == 0 ){
            printf ("current_target_dir.name fail\n");
        }
    }


	// name, dir address, number of entries

    fsFAT16ListFiles ( (const char *) dir_name,         
        (unsigned short *) current_target_dir.current_dir_address, 
        256 );


    return 0;
}


/*
 * fsFAT16ListFiles:
 *     Mostra os nomes dos arquivos de um diret�rio.
 *     Sistema de arquivos fat16.
 *
 * IN:
 *     dir_address = Ponteiro para um endere�o de mem�ria 
 *                   onde foi carregado o diret�rio. 
 */
 
void 
fsFAT16ListFiles ( const char *dir_name, 
                   unsigned short *dir_address, 
                   int number_of_entries )
{
	// #todo: 
	// O n�mero de entradas � maior no diret�rio raiz.(512 ?)

    int i = 0;
    int max = number_of_entries;         // N�mero m�ximo de entradas.

    unsigned long j = 0;  // Deslocamento

    unsigned short *DirBaseAddress = (unsigned short *) dir_address;



    if ( number_of_entries <= 0 ){
        return;
    }

    printf ("fsFAT16ListFiles: Listing names in [%s]\n\n", dir_name );

	// Mostra.

    i=0; 
    while (i < max)
    {
		// Diferente de vazio.
		if ( DirBaseAddress[j] != 0 )
		{
			//O problema � a termina��o da string '\0'
			printf ("%s\n", &DirBaseAddress[j] );
        } 
		
		//(32/2) pr�xima entrada! (16 words) 512 vezes!
        j += 16;  
        i++;  
    }; 


	//...
	
	//printf ("Done\n");
	refresh_screen();
}




/*
 * get_file:
 *     Get the pointer given the index in fileList[].
 */

void *get_file (int Index){
	
	//Limits.
	//@todo: max.

    if (Index < 0){
        return NULL;
    }

    return (void *) fileList[Index];
}


/*
 * set_file:
 *     Put the pointer in the list, given the index.
 */

void set_file ( void *file, int Index ){

    if (Index < 0)
    {
        return;
    }

	// #todo:
	// Limite m�ximo da lista.

	// Structure.

    if ( (void *) file == NULL )
    {
        return;
    }

	// Include pointer in the list.


     fileList[Index] = (unsigned long) file;
}


void fs_test_fat_vector (void)
{
    // Nothing for now.
}


unsigned long fs_get_fat_entry (unsigned long n)
{
    // Nothing for now.
    return 0; 
}


void fs_set_fat_entry ( unsigned long n, unsigned long value )
{
    // Nothing for now.
}



void fs_set_entry ( unsigned long id, unsigned long eid )
{
    // Nothing for now.
}


void fs_get_entry ( unsigned long id, unsigned long eid )
{
    // Nothing for now.
}


void fs_show_dir_entry ( unsigned long id, unsigned long eid )
{
    // Nothing for now.
}


void fs_show_dir (unsigned long id)
{
    // Nothing for now.
}


unsigned long fs_check_cluster (unsigned long id)
{
    // Nothing for now.
	return 0; 
}


/*
 * fs_check_fat:
 *     Check FAT. 
 */

unsigned long fs_check_fat (void)
{
    // Nothing for now.
	return 1; 
}


void fs_show_entry ( unsigned long id, unsigned long eid )
{
    // Nothing for now.
}


unsigned long 
fs_get_entry_status ( unsigned long id, 
                      unsigned long eid )
{
    // Nothing for now.
	return 0; 
}


void 
fs_set_entry_status ( unsigned long id, 
                      unsigned long eid, 
                      unsigned long status )
{
    // Nothing for now.
}


/*
 ***************************************************
 * fsCheckMbrFile: 
 *     Check mbr file, given a buffer.
 */

void fsCheckMbrFile ( unsigned char *buffer ){

	//#todo
	//mudar os argumentos para chamarmos as portas ide.

    unsigned char *mbr = (unsigned char *) buffer; 
    int i;

	//setor 0.
    my_read_hd_sector ( (unsigned long) &mbr[0] , 0, 0 , 0 ); 

	//message:
    //printf ("\n");
    printf ("fsCheckMbrFile: Testing MBR ...\n");

	// @todo:
	// Checar uma estrutura do mbr do disco do sistema,
	// para validar o acesso � ele.	

	// Check signature.
    if ( mbr[0x1FE] != 0x55 || mbr[0x1FF] != 0xAA )
    {
        printf ("fsCheckMbrFile: Sig FAIL \n" );
        goto fail;
    }

	//jmp
    printf ("JMP: [ %x ", mbr[ BS_JmpBoot + 0 ] );
    printf ("%x ", mbr[ BS_JmpBoot + 1 ] );
    printf ("%x ]\n", mbr[ BS_JmpBoot + 2 ] );


	//name
    printf ("OS name: [ ");
    for ( i=0; i<8; i++ )
    {
        printf ("%c", mbr[ BS_OEMName + i ] );
    };
    printf (" ]\n");


	//...


    printf ("Signature: [ %x %x ] \n" , mbr[0x1FE], mbr[0x1FF] );

	// Continua ...
    goto done;

fail:
    printf ("Fail\n");

done:
    printf ("Done\n");
    refresh_screen ();
    return;
}


/*
 * fsCheckVbr:
 *     Checa o registro de boot de um volume.
 *     Vai no endere�o onde est� armazenado o VBR do volume atual
 *     e confere as informa��es sobre o volume.
 */

void fsCheckVbrFile ( unsigned char *buffer ){

    unsigned char *vbr = (unsigned char *) buffer; 

	//#todo: check address validation.

	// #todo:
	// Checar uma estrutura do mbr do disco do sistema, para validar o 
	// acesso � ele.

	// Check signature.

    if ( vbr[0x1FE] != 0x55 || vbr[0x1FF] != 0xAA )
    {
        printf ("fsCheckVbrFile: Sig Fail\n");
        goto fail;
    }


	//
	// Continua ...
	//

    goto done;

fail:
    printf ("fsCheckVbrFile: fail\n");

done:
    printf ("Done\n");
    refresh_screen();
    return;
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
        if ( entry->FileName[i] == ' ')
        {
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
 *     Configura spc, 'Sector Per Cluster' em vari�vel global.
 *     ?? #bugbug: De qual disco ?? 
 */
 
void set_spc (int spc)
{
    g_spc = (int) spc;
}


/*
 * get_spc:
 *     Pega spc, Sector Per Cluster.
 *     ?? #bugbug: De qual disco ?? 
 */

int get_spc (void)
{
    return (int) g_spc;
}


/*
 * get_filesystem_type:
 *     Pega o tipo de sistema de arquivos.
 *     ?? #bugbug: De qual volume ??  
 */

int get_filesystem_type (void)
{
    return (int) g_filesystem_type;
}


/*
 * set_filesystem_type:
 *     Configura o tipo de sistema de arquivo.
 *     ?? #bugbug: De qual volume ?? 
 */

void set_filesystem_type (int type)
{
    g_filesystem_type = (int) type;
}


/*
 ***********************************************
 * fs_init_fat:
 *     Inicializa a estrutura usada no sistema de arquivos.
 *     fsInitFat()
 *     ?? #bugbug: De qual volume ?? 
 */

// #todo: Usar tipo 'int'.

void fs_init_fat (void){

    //
    // The root file system structure.
    //
    
    // "/"

    if ( (void *) root == NULL ){
        panic ("fs_init_fat: No root file system!\n");
    }


    //
    // FAT structure.
    //
    
    
    fat = (void *) kmalloc ( sizeof(struct fat_d) );

    if ( (void *) fat == NULL ){
        panic ("fs_init_fat: No fat struture \n");

    }else{

        // Info.
        fat->address = root->fat_address; 
        fat->type    = root->type;


        // Continua ...
    };


	// #bugbug
	// N�o fizemos nada com a estrutura 'fat'
	// tem que passar esse ponteiro para algum lugar.


	// Continua a inicializa��o da fat.
}


/*
 ******************************************************
 * fs_init_structures:
 *     Inicializa a estrutura do sistema de arquivos.
 *     fsInitStructures
 */

// #todo: Usar tipo 'int'.

void fs_init_structures (void){

    int Type = 0;

    //
    // The root file system.
    //
    
    // "/"

    root = (void *) kmalloc ( sizeof(struct filesystem_d) );

    if ( (void *) root == NULL ){
        panic ("fs_init_structures: Couldn't create the root structure.\n");

    }else{


        root->used = 1;
        root->magic = 1234;

        root->objectType = ObjectTypeFileSystem;
        root->objectClass = ObjectClassKernelObjects;
        
        
        root->name = (char *) ____root_name;
        
        
        // Se o volume do vfs ainda não foi criado 
        // então não podemos prosseguir.
        if ( (void *) volume_vfs == NULL ){
            debug_print("fs_init_structures: volume_vfs not initialized");
            panic("fs_init_structures: volume_vfs not initialized");
        }
        
        volume_vfs->fs = root;
        
        
        storage->fs = root;
        //...
    };



	//Type.
	//#bugbug: 
    //Em qual disco e volume pegamos o tipo de sistema de arquivos.

    Type = (int) get_filesystem_type ();   

    if ( Type == 0 ){
        panic ("fs_init_structures error: Type");

    }else{
            root->type = (int) Type;
    
    };


    switch (Type)
    {
        case FS_TYPE_FAT16:

			//Rootdir.
			root->rootdir_address = VOLUME1_ROOTDIR_ADDRESS;
	        root->rootdir_lba = VOLUME1_ROOTDIR_LBA;
	        
			//Fat.
			root->fat_address = VOLUME1_FAT_ADDRESS;
	        root->fat_lba = VOLUME1_FAT_LBA;
	        
			//Dataarea.
			//filesystem->dataarea_address = ??;
	        root->dataarea_lba = VOLUME1_DATAAREA_LBA;
	        
			//sectors per cluster.
			root->spc = (int) get_spc(); //vari�vel
	        root->rootdir_entries = FAT16_ROOT_ENTRIES;
	        root->entry_size = FAT16_ENTRY_SIZE;
            
            // ...

		    break;
			
	    case FS_TYPE_EXT2:
		    //nothing for now.
		    break;

        //...


        default:
		    //nothing for now.
            break;
    };
}




void fs_show_root_fs_info(void)
{

    printf ("\n");
    printf ("fs_show_root_fs_info:\n");

    if ( (void *) root == NULL ){
        printf ("No root structure\n");
        goto fail;
 
    }else{

        if ( root->used != 1 || root->magic != 1234 ){
             printf ("Validation fail\n");
             goto fail;
        }

        printf ("name = %s \n",root->name );
                
        printf ("Object type %d \n",root->objectType );
        printf ("Object class %d \n",root->objectClass );
        
        printf ("type = %d \n",root->type );
        printf ("Root dir entries %d \n",root->rootdir_entries );
        printf ("Entry size %d \n",root->entry_size );
        //printf ("",root-> );

        refresh_screen();
        return;
    }; 

fail:
    refresh_screen();
    return;
}

/*
 ********************************************************
 * fsInit:
 *     Inicializa o file system manager.
 */
 
int fsInit (void){


//#ifdef EXECVE_VERBOSE
   // printf ("fsInit: Initializing..\n");
//#endif 


    debug_print ("fsInit:\n");

	// Type - Configura o tipo de sistema de arquivos usado. 
	// No caso, (fat16).
	//
	// @todo: Deve-se checar o volume ativo e ver qual sistema de arquivos est�
	//        sendo usado, ent�o depois definir configurar o tipo.
	//        O sistema operacional pode salvar o tipo usado. Nesse caso 
	//        apenas checar se ouve altera��es nas configura��es de sistema de arquivos.
	//        O registro de configura��es de disco pode ser armazenado em arquivos de metadados.

    set_filesystem_type (FS_TYPE_FAT16);


	// SPC 
	// Configura o n�mero de setores por cluster.
	// Nesse caso, s�o (512 bytes por setor, um setor por cluster).

	set_spc (1);


	// ## initialize currents ##


	//selecionando disco, volume e diret�rio.
	//estamos resetando tudo e selecionando o diret�rio raiz 
	//do vfs ... mas na verdade o diret�rio selecionado 
	//deveria ser o diret�rio onde ficam a maioria dos aplicativos.
	//para que o usu�rio possa chamar o maior n�mero de apps usando 
	//apenas comandos simples.
	//#bugbug: isso deveria se passado pelo boot ??	


	//#bugbug: 
	//Deixaremos cada m�dulo inicializar sua vari�vel.
	//Mas aqui podemos zerar esses valores.
	
	//current_disk = 0;
	//current_volume = 0;   
	//current_directory = 0;

	// Structures and fat.

//#ifdef EXECVE_VERBOSE
	//printf("fsInit: Structures..\n");
//#endif

    fs_init_structures ();


//#ifdef EXECVE_VERBOSE
	//printf("fsInit: FAT..\n");
//#endif

    fs_init_fat ();


	//
	// ==================== ## fileList ## =========================
	//

	// Agora inicialzamos as stream 4 e 5.
	// As anteriores foram inicializadas em stdio,
	// pois s�o o fluxo padr�o.
	
	
	//
    //  ## volume 1 root dir  ##
	//
	
	
	//foi definido em stdio.h

    volume1_rootdir = (FILE *) kmalloc ( sizeof(FILE) );

    if ( (void *) volume1_rootdir == NULL )
    {
        panic ("fsInit: volume1_rootdir \n");

    } else {

        volume1_rootdir->used = 1;
        volume1_rootdir->magic = 1234;

        volume1_rootdir->_base = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir->_p = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir->_cnt = (32 * 512) ;
        volume1_rootdir->_file = 0; //?
        volume1_rootdir->_tmpfname = "volume1-stream";

        fileList[__KERNEL_STREAM_VOL1_ROOTDIR] = (unsigned long) volume1_rootdir;

        // #bugbug: 
        // Validade da estrutura.
        
        storage->__file = volume1_rootdir; 
    };



	//
	//  ## volume 2 root dir  ##
	//
	
	
	//foi definido em stdio.h
	//FILE *volume2_rootdir;

    volume2_rootdir = (FILE *) kmalloc ( sizeof(FILE) );

    if ( (void *) volume2_rootdir == NULL )
    {
        panic ("fsInit: volume2_rootdir\n");

    }else{

        volume2_rootdir->used = 1;
        volume2_rootdir->magic = 1234;

        volume2_rootdir->_base = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir->_p = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir->_cnt = (32 * 512) ;
        volume2_rootdir->_file = 0; //?
        volume2_rootdir->_tmpfname = "volume2-stream";

        fileList[__KERNEL_STREAM_VOL2_ROOTDIR] = (unsigned long) volume2_rootdir;
    };


	//
	// ## Inicializando os pipes usados em execve ## 
	//

	
	//gramado core init execve 
	
	//aloca mem�ria para a estrutura.
    pipe_gramadocore_init_execve = (FILE *) kmalloc ( sizeof(FILE) );
	
    if ( (void *) pipe_gramadocore_init_execve == NULL )
    {
        panic ("fsInit: pipe_gramadocore_init_execve\n");

    }else{

        //aloca mem�ria para o buffer.
        unsigned long pipe0base = (unsigned long) kmalloc (512);

        if ( (void *) pipe0base == NULL )
        {
            panic ("fsInit: pipe0base\n");
        }

        pipe_gramadocore_init_execve->used = 1;
        pipe_gramadocore_init_execve->magic = 1234;

        pipe_gramadocore_init_execve->_base = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_p = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_cnt  = 512;
        pipe_gramadocore_init_execve->_file = 0; //??
        pipe_gramadocore_init_execve->_tmpfname = "pipe0";
        
        
        // #todo
        //fileList[ ? ] = (unsigned long) pipe_gramadocore_init_execve;

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
    fsInitTargetDir ();

	//
	// @todo: Continua ...
	//


//done:

//#ifdef EXECVE_VERBOSE
    //printf("Done\n");
//#endif 

    return 0;
}


/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diret�rio de trabalho.
 * Essa � a string que ser� mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */
 
void fsInitializeWorkingDiretoryString (void){

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

    if ( (void *) v == NULL ){
        panic ("fsInitializeWorkingDiretoryString: v\n");

    }else{

        if ( v->used != 1 || v->magic != 1234 ){
            panic ("fsInitializeWorkingDiretoryString: validation\n");
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
        };


		//path string na estrutura do volume.
        sprintf ( v->path_string, current_volume_string );

	    //'volumeX'
        strcat ( current_workingdiretory_string, v->path_string );
	    //strcat ( current_workingdiretory_string, current_volume_string );
    };


	// ## separador ##
    strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );

	//More ?...
    pwd_initialized = 1;
}


/*
 ***************************
 * fsInitTargetDir:
 *     Para inicializarmos o sistema ja' com um alvo, no caso o root dir. 
 */

void fsInitTargetDir (void){
	
	current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
	//current_target_dir.name = ?;
}


/*
 **************************************
 * fs_initialize_process_pwd:
 *     Cada processo deve inicialiar seus dados aqui. 
 */

int fs_initialize_process_pwd ( int pid, char *string ){

    int i;
    struct process_d *p;

    if ( pwd_initialized == 0 ){
        panic ("fs_initialize_process_pwd: pwd not initialized\n"); 
    } 


    if (pid<0)
        return 1;


    if ( (void *) string == NULL )
        return 1; 


	// #importante
	// Vamos copiar a string para a estrutura do processo atual.

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL )
    {
        panic ("fs_initialize_process_pwd: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_initialize_process_pwd: validation\n");
        }

        for ( i=0; i<32; i++ ){
            p->pwd_string[i] = string[i];
        }
    };


    return 0;
}


/*
 * fs_print_process_pwd
 *     Cada processo tem seu pr�prio pwd.
 *     Essa rotina mostra o pathname usado pelo processo. 
 */

int fs_print_process_pwd (int pid){

    struct process_d *p;

    if ( pwd_initialized == 0 ){
        panic ("fs_print_process_pwd: pwd not initialized\n"); 
    }


    if (pid<0)
        return 1;


    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_print_process_pwd: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_print_process_pwd: validation\n");
        }

        printf ("\n PID=%d %s (%s) \n\n", p->pid, 
            p->pwd_string, current_target_dir.name );

        refresh_screen ();
        return 0;
    };


    //fail.
    return -1;
}


/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global. 
 */ 
 
void fsUpdateWorkingDiretoryString ( char *string ){

    int i;    
    struct process_d *p;
    char *tmp;


    tmp = string;


    if ( pwd_initialized == 0 ){
        printf ("fsUpdateWorkingDiretoryString: pwd not initialized\n"); 
        return;
    }


    if ( (void *) string == NULL )
        return;  


    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: validation\n");
        }

        if ( (void *) string == NULL ){
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
            for ( i=0; i< 11; i++ ){
                current_target_dir.name[i] = *tmp;
                tmp++;
            }
        }
    }
}


/* 
 ************************************************
 * fs_pathname_backup:
 *     Remove n nomes de diret�rio do pathname do processo indicado no 
 * argumento.
 *     Copia o nome para a string global.
 *     Remove the last N directories from PATH.  
 *     Do not leave a blank path.
 *     PATH must contain enough space for MAXPATHLEN characters. 
 *     #obs: O PID costuma ser do processo atual mesmo. 
 *     Credits: bash 1.05 
 */
 
void fs_pathname_backup ( int pid, int n ){

    int i;
    struct process_d *p;


    if ( pwd_initialized == 0 ){
        printf ("fs_pathname_backup: pwd not initialized\n"); 
        return;
    } 


    if ( pid<0 ){
        printf ("fs_pathname_backup: PID\n"); 
        return;
    }


    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: validation\n");
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
    };
}



// usada por open()
// tem que retornar o fd e colocar o ponteiro na lista de arquivos
// abertos.
// Carrega um arquivo do disco para a mem�ria.
// funcionou.

// #bugbug
// Na minha m�quina real, �s vezes d� problemas no tamanho do arquivo.


// #bugbug
// Estamos alocando mem�ria em ring para carregar o arquivo
// e depois estamos usando o buffer em ring3 passado pelo usu�rio.
// >>> vamos confiar no usu�rio e usarmos

int sys_read_file ( char *file_name,  int flags, mode_t mode )
{
    struct process_d *p;
    file *__file;
    
    int Status = -1;
    
    int __slot = -1;




    // Convertendo o formato do nome do arquivo.    
    // >>> "12345678XYZ"
    
    read_fntos ( (char *) file_name );


    // Searching for the file only on the root dir.

    Status = (int) KiSearchFile ( file_name, VOLUME1_ROOTDIR_ADDRESS );
    
    if (Status != 1){
         printf ("sys_read_file: File not found!\n");
         refresh_screen();
         return -1;
    }
    
    


    //
    // Process.
    //
  
    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL )
        return -1;

    if ( p->used != 1 || p->magic != 1234 )
        return -1;
        
        
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){
             goto __OK;
         }
    };
    
    // #todo
    // Esse limite pertence somente � um processo.
    // Poder�amos avisar que o processo n�o pode mais abrir arquivos
    // depois retornar.
    
    panic ("sys_read_file: No slots!\n");


__OK:

    __file = (file *) kmalloc ( sizeof(file) );
    
    if ( (void *) __file == NULL )
        return -1;
        
        
    if ( __slot < 0 || __slot >= 32 )
    {
        printf ("sys_read_file: Slot fail\n");
        refresh_screen();
        return -1;
    }
    
    __file->_file = __slot;
    
    
    __file->used = 1;
    __file->magic = 1234;
    
    //
    // buffer padr�o
    //
    
    __file->_base = (char *) kmalloc (BUFSIZ);
    
    if ( (void *) __file->_base == NULL )
    {
        printf ("sys_read_file: buffer fail\n");
        refresh_screen();
        return -1;
    }
    __file->_lbfsize = BUFSIZ;
    
    //
    // File size.
    //

    size_t s = (size_t) fsGetFileSize ( (unsigned char *) file_name );
    
    if (s < 0)
    {
        printf ("sys_read_file: File size fail\n");
        refresh_screen();
        return -1;
    }

    
    if ( s < __file->_lbfsize )
    {
        s = __file->_lbfsize;
    }

    // Se o arquivo for maior que buffer dispon�vel.
    // Podemos almentar o buffer.
    if (s > __file->_lbfsize)
    {
        // limite - 1MB.
        if (s > 1024*1024)
        {
            printf ("sys_read_file: File size out of limits\n");
            printf ("%d bytes \n",s);
            refresh_screen();
            return -1;
        }
        
        // Allocate new buffer.
        __file->_base = (char *) kmalloc (s);
        
        if ( (void *) __file->_base == NULL )
        {
            printf ("sys_read_file: Couldn't create a new buffer\n");
            refresh_screen();
            return -1;             
        }
        
        // temos um novo buffer size.
        __file->_lbfsize = (int) s;
    }

    // #paranoia.
    // Checando os limites novamente.
    
    // limits - 1MB
    if (s > 1024*1024){
        printf ("sys_read_file: File size out of limits\n");
        refresh_screen();
        return -1;
    }


    //limits?
    
    if ( (void *) __file->_base == NULL )
    {
        printf ("sys_read_file: buffer fail\n");
        refresh_screen();
        return -1;
    }
    
    
    __file->_p = __file->_base;
    

 
    Status = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                       VOLUME1_ROOTDIR_ADDRESS, 
                       file_name, 
                       (unsigned long) __file->_base );
   
    if ( Status != 0 )
        return -1;
        
        
    // salva o ponteiro.  
    // ja checamos fd.
    p->Objects[__slot] = (unsigned long) __file;
        
    
        
    //printf ("done\n");
    //refresh_screen();
          
    //
    // Done.
    // Vamos retornar o fd.
    // Pois essa rotina � usada por open();
    //      
          
    return (int) __file->_file;
}






/*
 ********************************
 * fsLoadFileFromCurrentTargetDir:
 *     Carrega o diret�rio que est� configurado como target dir 
 * em algum lugar qualquer da mem�ria. 
 */

int fsLoadFileFromCurrentTargetDir (void){
	
	int Ret = -1;
	int i;
	
	unsigned long new_address;
	
	//#bugbug
	//Isso 'e um limite para o tamanho do arquivo (apenas dir).
	//precisamos expandir isso.
	//aqui no m'aquimo o arquivo pode ter 4kb.
	//acho ques estamos falando somente de diret'orio aqui.
	
	new_address = (unsigned long) kmalloc (4096);
	
	if ( new_address == 0 )
	{
		return -1;
	}
	
	//#bugbug
	//tenta carregar o diret'orio que tem o endere�o indicado aqui, 
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


    //++
    taskswitch_lock ();
    scheduler_lock ();

    Ret = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS,  
                    current_target_dir.current_dir_address,    //src dir address 
                    (unsigned char *) current_target_dir.name, 
                    (unsigned long) new_address );             //dst dir address

    scheduler_unlock ();
    taskswitch_unlock ();
    //--

    current_target_dir.current_dir_address = new_address;

	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) new_dir_addr=(%x) #debug \n",
	//   current_target_dir.name, current_target_dir.current_dir_address );


    return (int) Ret;
}



/*
 * sys_write_file:
 *     Interface para salvar arquivo ou diret�rio.
 *     Isso pode ser usado para criar um diret�rio ou copiar um diret�rio. 
 */

	//#todo:
	//vamos fazer igual ao sys_read_file 
	//e criarmos op��es ... se poss�vel.


// IN: name, size in sectors, size in bytes, adress, flag.

int
sys_write_file ( char *file_name, 
                 unsigned long file_size,
                 unsigned long size_in_bytes,
                 char *file_address,
                 char flag )  
{
    int Ret = -1;

    //++
    taskswitch_lock ();
    scheduler_lock ();

    Ret = (int) fsSaveFile ( (char *) file_name,    
                    (unsigned long) file_size,       
                    (unsigned long) size_in_bytes,  
                    (char *) file_address,          
                    (char) flag );                  

    scheduler_unlock ();
    taskswitch_unlock ();
    //--


    return Ret;
}


//
// Create
//


int fs_create_empty_file ( char *file_name, int type )
{

    file *f;
    
    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    int __ret;
    
    f = (file *) kmalloc( sizeof(size_in_bytes) );
    
    if( (void*) f == NULL )
        return -1;
        
    //f->type = type;
    // #todo: fd ...
    
    __ret = (int) fsSaveFile ( (char *) file_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x20 );  //0x20 = file.                  



    return __ret;
}

int sys_create_empty_file ( char *file_name )
{
    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    int __ret;
    
    __ret = (int) fsSaveFile ( (char *) file_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x20 );  //0x20 = file.                  



    return __ret;
}



int fs_create_empty_directory ( char *dir_name, int type )
{
    file *f;

    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    int __ret;
    
    f = (file *) kmalloc( sizeof(size_in_bytes) );
    
    if( (void*) f == NULL )
        return -1;
        
    //f->type = type;
    // #todo: fd ...
    
    __ret = (int) fsSaveFile ( (char *) dir_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x10 );  //0x10 = directory.                  



    return __ret;
}



int sys_create_empty_directory ( char *dir_name )
{
    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    int __ret;
    
    __ret = (int) fsSaveFile ( (char *) dir_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x10 );  //0x10 = directory.                  



    return __ret;
}







//#todo
//credits: Chicago OS.
/*
int fs_count_separations (char *path)
int fs_count_separations (char *path){

    int count = 0;

    int i;
    int __len = 0;


    __len = (int) strlen ( (const char *) path );
    
    for ( i=0; i < __len; i++ )
    {
		if (path[i] == '/')
		{
			count++;
		}
    };


    return (int) count;
}
*/


/*
int fat16_create_new_directory ( ... )
int fat16_create_new_directory ( ... )
{}
*/

/*
int fat16_create_new_file ( ... );
int fat16_create_new_file ( ... )
{}
*/



//
// End.
//

