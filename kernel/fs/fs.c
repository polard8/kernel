

#include <kernel.h>


//
// == Cluster list =================================================
//

// Lista de clusters.
// Isso permite salvar um arquivo com 32 mil clusters ??
// #todo: Em que momento essa lista foi inicializada??

// #bugbug: 
// This list has 32 KB size.

// #bugbug
// Checar se essa 'e a quantidade limite de 
// entradas que podemos acessar na fat.
// Ou e' apenas o limite da lista.

//#define  CLUSTERS_TO_SAVE_MAX    (8*1024) //#bugbug
#define  CLUSTERS_TO_SAVE_MAX    (32*1024)

unsigned short fat16ClustersToSave[CLUSTERS_TO_SAVE_MAX];

// ========================================





//get free slots in the file_table[]
int get_free_slots_in_the_file_table(void)
{
    file *tmp;
    int i=0;

    for (i=0; i<NUMBER_OF_FILES; i++)
    {
        tmp = (void*) file_table[i];
        
        // Nenhum file descritor está usando essa estrutura.
        if (tmp->used  == TRUE && 
            tmp->magic == 1234 && 
            tmp->fd_counter == 0)
        { 
            return (int) i; 
        }
    };

    return -1;
}


//get free slots in the inode_table[]
int get_free_slots_in_the_inode_table(void)
{
    struct inode_d *tmp;
    int i=0;

    
    for (i=0; i<32; i++)
    {
        tmp = (void*) inode_table[i];
        
        // Se nenhum descritor de estrutura de arquivo 
        // está usando essa estrutura inode.
        if (tmp->used  == TRUE && 
            tmp->magic == 1234 && 
            tmp->filestruct_counter == 0)
        { 
            return (int) i; 
        }
    }

    return -1;
}

// credits: hoppy os.
// from 8.3
// not tested yet.
void 
from_FAT_name (
    char *src, 
    char *dst )
{

    int i=0;
    int j=0;
    int k=0;


    // #todo: debug messages.
    
    if ( (void *) src == NULL ){ return; }
    if ( (void *) dst == NULL ){ return; }

    if (*src == 0){ return;}
    if (*dst == 0){ return;}


    // dirty
    // pra saber o tamanho do nome exluindo os espaços.
    for (j=7; j >= 0 && src[j] == 0x20; j--)
    {
    };
    
    k=0;
    
    // j eh o tamanho do nome calculado anteriormente.
    // copia esse nome.
    for( i=0; i<=j; i++ )
    {
        dst[k++] = src[i];
    }
    
    
    if (*src != '.')
    {
        dst[k++] = '.';
    }
    
    // dirty.
    // pra saber o tamanho da extensao, excluindo os espaços.
    for (j=10; j>=8 && src[j]==0x20; j--)
    {
    };
    
    //
    if (j==7) {
    
        if (k==1){
           dst[k]=0;
        } else {

            if (dst[0]=='.'){
                dst[k]=0;
            }else{
                dst[k-1]=0;
            };
        };
    
    } else {
        
        for (i=8; i<=j; i++)
        {
            dst[k++] = src[i];
        };
        
        dst[k++] = 0;
    };
}

// credits: hoppy os.
// to 8.3
// not tested yet.
void 
to_FAT_name (
    char *src,
    char *dst )
{
    int i=0;
    char *ptr;


    // Parent directory
    if ( !strcmp(src,"..") ) {
        strcpy(dst,src);
        i=2;
    
    // Current directory
    } else if (!strcmp(src,".")) {
        strcpy(dst,src);
        i=1;
    
    // Regular file.
    } else {
        
        ptr = src;

        i=0;
        
        // Começamos com o nome.
        while (i<8 && *ptr && *ptr != '.') 
        {
            dst[i++] = *ptr++;
        };
        
        // Completa com ' ' ate 8.
        while (i<8){ dst[i++] = 0x20; };
        
        if (*ptr == '.') { ptr++; }
        
        // Agora a extensao
        while (i<11 && *ptr){
            dst[i++] = *ptr++;
        };
    };

    // Completa com espaço ate o fim.
    // 'i' indica o offset de onde devemos começar.
    // Isso tambem vai completar com espaço quando a extensao
    // tiver menos que 3 chars.

    while (i<11){ dst[i++] = 0x20; };
}

/*
 * get_filesystem_type:
 *     Pega o tipo de sistema de arquivos.
 *     ?? #bugbug: De qual volume ??  
 */

int get_filesystem_type (void)
{
    return (int) g_currentvolume_filesystem_type;
}

/*
 * set_filesystem_type:
 *     Configura o tipo de sistema de arquivo.
 *     ?? #bugbug: De qual volume ?? 
 */

void set_filesystem_type (int type)
{
    g_currentvolume_filesystem_type = (int) type;
}

// Credits: Sirius OS.
unsigned long fs_count_path_levels (unsigned char *path)
{
    unsigned long Counter=0;
    int Max = (80*25);   //25 lines.
    
    register int i=0;


    if ( (void*) path == NULL ){  return 0;  }

    if ( *path == 0 ){  return 0;  }


    for ( i=0; i < Max; ++i )
    {
        if (path[i] == '/') { Counter++; }
        if (path[i] == '\0'){ break; }
    };

    return (unsigned long) Counter;
}

/*
 * get_file:
 *     Get the pointer given the index in file_table[].
 */
// na lista de arquivos do kernel.
void *get_file (int Index)
{
	//Limits.
	//@todo: max.

    if (Index < 0)
    {
        // ?? todo: message
        return NULL;
    }

    return (void *) file_table[Index];
}


/*
 * set_file:
 *     Put the pointer in the list, given the index.
 */
// na lista de arquivos do kernel.
void set_file ( void *file, int Index )
{

    if (Index < 0){
        // ?? todo: message
        return;
    }

	// #todo:
	// Limite m�ximo da lista.

	// Structure.

    if ( (void *) file == NULL )
    {
        // ?? todo: message
        return;
    }

	// Include pointer in the list.


     file_table[Index] = (unsigned long) file;
}    


// Called by init() in init.c
int fsInit (void)
{
    //#todo

    int slot = -1;


    debug_print ("fsInit: [TODO]\n");
    
    // Undefined fs!
    set_filesystem_type(FS_TYPE_NULL);


    //
    // Initialize fat16 support for the system's volume.
    //

    // #todo: 
    // Devemos checar o tipo da partiçao de boot. 
    // Se nao aqui, depois!

    // #todo
    fat16Init();


//
// == fileList =========================
//

	// Agora inicialzamos as stream 4 e 5.
	// As anteriores foram inicializadas em stdio,
	// pois s�o o fluxo padr�o.

//
// == volume1_rootdir =========================================== 
//

    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if (slot<0 || slot >= NUMBER_OF_FILES){
        panic("fsInit: slot");
    }
    volume1_rootdir = (file *) file_table[slot];
    volume1_rootdir->filetable_index = slot;

    if ( (void *) volume1_rootdir == NULL ){
        panic ("fsInit: volume1_rootdir \n");
    } else {
        volume1_rootdir->used  = TRUE;
        volume1_rootdir->magic = 1234;
        volume1_rootdir->____object = ObjectTypeVolume;

        volume1_rootdir->_base = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir->_p    = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir->_cnt = (32 * 512);
        volume1_rootdir->_file = 0;
        volume1_rootdir->_tmpfname = "VOLUME1 VOL";
        volume1_rootdir->fd_counter = 1;

        // #bugbug: 
        // Validade da estrutura.
        
        // ...
        // inode support.
        // pega slot em inode_table[] 
        slot = get_free_slots_in_the_inode_table();
        if (slot<0 || slot >=32){
            panic("fsInit: volume1_rootdir inode slot");
        }
        volume1_rootdir->inode = (struct inode_d *) inode_table[slot];
        volume1_rootdir->inodetable_index = slot;
        if ( (void*) volume1_rootdir->inode == NULL ){
            panic("fsInit: volume1_rootdir inode struct");
        }
        volume1_rootdir->inode->filestruct_counter = 1;  //inicialize
        memcpy ( 
            (void*) volume1_rootdir->inode->path, 
            (const void*) volume1_rootdir->_tmpfname, 
            sizeof( volume1_rootdir->inode->path ) );
        // ... 

        // File that represents the system volume.
        storage->__file = volume1_rootdir; 
    };



//
// == volume2_rootdir =========================================== 
//
    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if (slot<0 || slot >= NUMBER_OF_FILES){
        panic("fsInit: slot");
    }
    volume2_rootdir = (file *) file_table[slot];
    volume2_rootdir->filetable_index = slot;

    if ( (void *) volume2_rootdir == NULL ){
        panic ("fsInit: volume2_rootdir\n");
    }else{
        volume2_rootdir->used  = TRUE;
        volume2_rootdir->magic = 1234;
        volume2_rootdir->____object = ObjectTypeVolume;
 
        volume2_rootdir->_base = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir->_p    = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir->_cnt = (32 * 512);  // #bugbug: Check this size.
        volume2_rootdir->_file = 0;          // ?
        volume2_rootdir->_tmpfname = "VOLUME2 VOL";
        volume2_rootdir->fd_counter = 1;

        // ...
        // inode support.
        // pega slot em inode_table[] 
        slot = get_free_slots_in_the_inode_table();
        if (slot<0 || slot >= 32){
            panic("fsInit: volume2_rootdir inode slot");
        }
        volume2_rootdir->inode = (struct inode_d *) inode_table[slot];
        volume2_rootdir->inodetable_index = slot;
        if ( (void*) volume2_rootdir->inode == NULL ){
            panic("fsInit: volume2_rootdir inode struct");
        }
        volume2_rootdir->inode->filestruct_counter = 1;  //inicialize
        memcpy ( 
            (void*)       volume2_rootdir->inode->path, 
            (const void*) volume2_rootdir->_tmpfname, 
            sizeof(       volume2_rootdir->inode->path ) );
        // ... 
    };


//
// == pipe_gramadocore_init_execve ================================ 
//

	//
	// ## Inicializando os pipes usados em execve ## 
	//

	//gramado core init execve 
	
	//aloca memoria para a estrutura.
    pipe_gramadocore_init_execve = (file *) kmalloc ( sizeof(file) );

    if ( (void *) pipe_gramadocore_init_execve == NULL ){
        panic ("fsInit: pipe_gramadocore_init_execve\n");
    }else{

        // Aloca memória para o buffer.
        // #todo: Define this variable in the top of the body.
        // #bugbug: Chech this size.
        unsigned long pipe0base = (unsigned long) kmalloc (512);

        if ( (void *) pipe0base == NULL ){
            panic ("fsInit: pipe0base\n");
        }

        pipe_gramadocore_init_execve->used  = TRUE;
        pipe_gramadocore_init_execve->magic = 1234;

        pipe_gramadocore_init_execve->_base = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_p    = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_cnt  = 512;  // #bugbug: Check this size.
        pipe_gramadocore_init_execve->_file = 0;    // ??
        pipe_gramadocore_init_execve->_tmpfname = "pipe0";

        // #todo
        //fileList[ ? ] = (unsigned long) pipe_gramadocore_init_execve;

        // 0
        Pipes[0] = (unsigned long) pipe_gramadocore_init_execve;
    };




    // Initialize directory facility structures.
    
    init_directory_facilities();

    // CWD Structure.
    // Inicializa o pwd support.

    fsInitializeWorkingDiretoryString();

    // Target dir struct
    // Inicializa a estrutura de suporte ao target dir.

    fsInitTargetDir(VOLUME1_ROOTDIR_ADDRESS,"/");

// done:
    debug_print ("fsInit: done\n");
    return 0;
}


int init_directory_facilities(void)
{

    // '/'
    directory_facility_RootDir.dir_address = VOLUME1_ROOTDIR_ADDRESS;
    directory_facility_RootDir.dir_name[0] = '/';
    directory_facility_RootDir.dir_name[1] = 0;
    directory_facility_RootDir.name_size = 1;
    directory_facility_RootDir.initialized = TRUE;

    // EFI/
    directory_facility_EFIDir.dir_address = 0;
    directory_facility_EFIDir.dir_name[0] = 0;
    directory_facility_EFIDir.name_size = 0;
    directory_facility_EFIDir.initialized = FALSE;

    // GRAMADO/
    directory_facility_GramadoDir.dir_address = 0;
    directory_facility_GramadoDir.dir_name[0] = 0;
    directory_facility_GramadoDir.name_size = 0;
    directory_facility_GramadoDir.initialized = FALSE;

    // PROGRAMS/
    directory_facility_ProgramsDir.dir_address = 0;
    directory_facility_ProgramsDir.dir_name[0] = 0;
    directory_facility_ProgramsDir.name_size = 0;
    directory_facility_ProgramsDir.initialized = FALSE;


    // UBASE/
    directory_facility_ubaseDir.dir_address = 0;
    directory_facility_ubaseDir.dir_name[0] = 0;
    directory_facility_ubaseDir.name_size = 0;
    directory_facility_ubaseDir.initialized = FALSE;

    // USERS/
    directory_facility_usersDir.dir_address = 0;
    directory_facility_usersDir.dir_name[0] = 0;
    directory_facility_usersDir.name_size = 0;
    directory_facility_usersDir.initialized = FALSE;


    // ok
    return 0;
}


// Called by fsInit.
int fat16Init (void)
{
    debug_print ("fat16Init: [TODO]\n");

    fat_cache_loaded = CACHE_NOT_LOADED;
    fat_cache_saved  = CACHE_NOT_SAVED;

    set_filesystem_type (FS_TYPE_FAT16);

    // Structures and fat.

    // #todo
    fs_init_structures();
    fs_init_fat();

// done
    debug_print ("fat16Init: done\n");
    return 0;
}

void fs_init_structures (void)
{
    int Type=0;

    debug_print ("fs_init_structures: [TODO]\n");

//
// The root file system.
//
    
    // "/"
    debug_print ("fs_init_structures: root\n");

    root = (void *) kmalloc ( sizeof(struct filesystem_d) );

    if ( (void *) root == NULL ){
        panic ("fs_init_structures: Couldn't create the root structure.\n");
    }else{
        root->objectType  = ObjectTypeFileSystem;
        root->objectClass = ObjectClassKernelObjects;
        root->used  = TRUE;
        root->magic = 1234;

        // pointer
        
        root->name = (char *) ____root_name;
        
        
        //
        // #todo #bugbug   volume_vfs  ??
        //
        
        // Se o volume do vfs ainda não foi criado 
        // então não podemos prosseguir.
        //if ( (void *) volume_vfs == NULL )
        //{
        //    debug_print("fs_init_structures: [FAIL] volume_vfs not initialized");
        //    panic      ("fs_init_structures: [FAIL] volume_vfs not initialized");
        //}
        //volume_vfs->fs = root;
        
        
        storage->fs = root;
        //...
    };


//
// Type
// 
    // #bugbug: 
    // Em qual disco e volume pegamos o tipo de sistema de arquivos?
    debug_print ("fs_init_structures: Type\n");


    Type = (int) get_filesystem_type();

    if ( Type <= 0 ){
        panic ("fs_init_structures: [PANIC] Type");
    }else{
        root->type = (int) Type;
    };

    switch (Type){

        case FS_TYPE_FAT16:

            // Disk stuff.
            // spc - Sectors per cluster.
            root->spc = (int) VOLUME1_SPC;
            //root->spc = (int) get_spc(); 
            

            // Rootdir, Fat and data area.
            // #bugbug: Specific for fat16.
            root->rootdir_address = VOLUME1_ROOTDIR_ADDRESS;
            root->rootdir_lba     = VOLUME1_ROOTDIR_LBA;
            root->fat_address     = VOLUME1_FAT_ADDRESS;
            root->fat_lba         = VOLUME1_FAT_LBA;
            root->dataarea_lba    = VOLUME1_DATAAREA_LBA;
            //filesystem->dataarea_address = ??;
 
            // Root dir.
            
            // Number of entries in the root dir.
            // #bugbug: Specific for fat16.
            root->dir_entries = FAT16_ROOT_ENTRIES;
            
            // Size of the entry in bytes.
            // #bugbug: Specific for fat16.
            root->entry_size = FAT16_ENTRY_SIZE;
       
            // ...
            break;

        // Nothing for now.
        case FS_TYPE_EXT2:
            panic ("fs_init_structures: [PANIC] FS_TYPE_EXT2 not supported");
            break;

        //...

        // Nothing for now.
        default:
            panic ("fs_init_structures: [PANIC] default Type");
            break;
    };
    
    // Done.
}

void fs_init_fat (void)
{
    debug_print ("fs_init_fat: [TODO]\n");

    // The root file system structure.
    // "/"

    if ( (void *) root == NULL ){
        panic ("fs_init_fat: No root file system!\n");
    }


//
// fat
//
    
    fat = (void *) kmalloc ( sizeof(struct fat_d) );

    if ( (void *) fat == NULL ){
        panic ("fs_init_fat: No fat struture \n");
    }else{

        // Info.
        fat->address = root->fat_address; 
        fat->type    = root->type;

        // Continua ...

        // #todo
        // Check this values.

        if ( fat->address == 0 )
            panic ("fs_init_fat: fat address \n");

        // is it int ?
        if ( fat->type <= 0 )
            panic ("fs_init_fat: fat type \n");
    };


	// #bugbug
	// N�o fizemos nada com a estrutura 'fat'
	// tem que passar esse ponteiro para algum lugar.

	// Continua a inicializa��o da fat.

}


// #todo: use int return.
void file_close (file *_file)
{
    debug_print("file_close: todo\n");

    if ( (void*) _file == NULL )
        return;
}

size_t file_get_len(file *_file)
{
    debug_print("file_get_len: todo\n");

    if ( (void*) _file == NULL )
        return -1;

    return (size_t) -1;
}

//OUT: inode structure.
struct inode_d *file_inode (file *f)
{
    if ( (void *)f==NULL )
    {
        return (struct inode_d *) 0;
    }

    return (struct inode_d *) f->inode;
}

int file_truncate ( file *_file, size_t len)
{
    debug_print("file_truncate: todo\n");

    if ( (void*) _file == NULL )
        return -1;

    if(len<0)
        return -1;

    return -1;
}



// Check the signature in a elf header.
// OUT:
// 0 = OK. #todo: Isso poderia ser '1'.
// < 0 Means error.

// #todo
// We can do the same for some other types.
// Use TRUE or FALSE.

// #todo
// Isso deve ir para um módulo responsável pelo formato elf
// e começar com elfXXXX()

int fsCheckELFFile ( unsigned long address )
{
    return (int) elfCheckSignature(address);
}


/*
 ****************************************
 * fsFAT16ListFiles:
 *     Mostra os nomes dos arquivos de um diret�rio.
 *     Sistema de arquivos fat16.
 *
 * IN:
 *     dir_address = Ponteiro para um endere�o de mem�ria 
 *                   onde foi carregado o diret�rio. 
 */

void 
fsFAT16ListFiles ( 
    const char     *dir_name, 
    unsigned short *dir_address, 
    int            number_of_entries )
{

    // iterator
    int i=0;

    // offset
    int j=0;  
    
    // Max number of entries.
    int max = number_of_entries;

    char NameString[ 12 ];  //8.3

    // Buffer.
    unsigned short *shortBuffer = (unsigned short *) dir_address;
    unsigned char  *charBuffer  = (unsigned char *)  dir_address;

    if ( (void *) dir_name == NULL )
    {
        printf ("fsFAT16ListFiles: [FAIL] dir_name\n");
        goto fail;
    }

    if ( *dir_name == 0 )
    {
        printf ("fsFAT16ListFiles: [FAIL] *dir_name\n");
        goto fail;
    }

    // banner message.

    // #bugbug
    // Missing string finalization.
        
    // printf ("fsFAT16ListFiles: Listing names in [%s]\n\n", 
    //        dir_name );
            
    // Number of entries.

    if ( number_of_entries <= 0 ){
        debug_print ("fsFAT16ListFiles: [FAIL] number_of_entries\n");
        goto fail;
    }

    // #bugbug
    // Number of entries.

    if ( number_of_entries >= 512 )
    {
        debug_print ("fsFAT16ListFiles: [FAIL] number_of_entries is too big\n");
        goto fail;
    }


    // Show 'max' entries in the directory.

    i=0; 
    j=0;
    while (i < max)
    {
        // Not invalid and not free.
        if ( charBuffer[j] != FAT_DIRECTORY_ENTRY_LAST &&
             charBuffer[j] != FAT_DIRECTORY_ENTRY_FREE )
        {
             // #bugbug
             
             memcpy( 
                 (char*) NameString, 
                 (const char *) &charBuffer[j],
                 11 );
             
             NameString[11] = 0;  //finalize string
             
             printf ("%s\n", NameString );
        } 

        // (32/2) proxima entrada! 
        // (16 words) 512 vezes!
 
        //j += 16;  //short buffer  
          j += 32;  //char buffer
        
        i++;  
    }; 

    // ...
 
    goto done;

fail:
    printk ("fsFAT16ListFiles: fail\n");
done:
    refresh_screen();
}



/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diret�rio de trabalho.
 * Essa eh a string que ser� mostrada antes do prompt.
 * 'pwd'> 
 */

void fsInitializeWorkingDiretoryString (void)
{

    // #bugbug
    // We have some issues with string sizes.
    // Buffer overflow!

    // vamos contar o tamanho da string que estamos construindo.
    int string_count = 0;  
    
    //
    int string_size = 0;
    
    struct volume_d  *v;

    char volume_string[8];   


    debug_print ("fsInitializeWorkingDiretoryString:\n");

    // See: 
    // kernel/include/rtl/fs/fs.h

    CWD.initialized = FALSE;

    // volume string 
    
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

    sprintf ( CWD.path, FS_ROOT_STRING ); 

	//'/'
	// ## separador ##
    strcat ( CWD.path, FS_PATHNAME_SEPARATOR );


	//
	// volume root dir 
	//

    // #todo
    // Check overflow.

    if ( current_volume < 0 ){
        panic ("fsInitializeWorkingDiretoryString: current_volume\n");
    }


    v = (struct volume_d *) volumeList[current_volume];

    if ( (void *) v == NULL ){
        panic ("fsInitializeWorkingDiretoryString: v\n");
    }else{
        if ( v->used != TRUE || v->magic != 1234 ){
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

        // #bugbug
        // We need to finalize the string.
        // limit 32.
        // See: volume.h
        
        // path string na estrutura do volume.
        
        string_size = sizeof(current_volume_string);

        if (string_size >= 32){
            debug_print ("fsInitializeWorkingDiretoryString: [FIXME] string size\n"); 
            return;
        }
        
        // copy the string. limit 32 bytes.
        sprintf ( v->path_string, current_volume_string );
        
        // finalize.
        v->path_string[31] = 0;

        // #bugbug
        // What is the limit for this string ? 32 bytes.
        // See: rtl/fs/path.h and globals.h

        strcat ( CWD.path, v->path_string );
	    //strcat ( CWD.path, current_volume_string );
	    
        CWD.path[31] = 0;
    };

    // #bugbug
    // What is the limit for this string ? 32 bytes.
    // See: rtl/fs/path.h and globals.h

    // Separador

    strcat ( 
        CWD.path, 
        FS_PATHNAME_SEPARATOR );


    //
    // Size
    //

    // #test

    CWD.path[31] = 0;

    int size;
    size = strlen(CWD.path);

    if (size > 31)
        size = 31;

    CWD.size = size;

	//More ?...

    debug_print ("fsInitializeWorkingDiretoryString: done\n");

    // See: 
    // kernel/include/rtl/fs/fs.h

    CWD.initialized = TRUE;
}



/*
 ***************************
 * fsInitTargetDir:
 * 
 *     Para inicializarmos o sistema ja' com um alvo, 
 * no caso o root dir. 
 */

void fsInitTargetDir (unsigned long dir_address, char *name)
{
    int i=0;
    
    
    current_target_dir.used  = TRUE;
    current_target_dir.magic = 1234;

    for ( i=0; i<11; i++ ){
        current_target_dir.name[i] = '\0';
    };


    // Dir address
    
    if (dir_address == 0)
        panic("fsInitTargetDir: dir_address\n");

    //current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
    current_target_dir.current_dir_address = dir_address;

    // Dir name
    
    if ( (void*) name == NULL )
        panic("fsInitTargetDir: name\n");

    if (*name == 0)
        panic("fsInitTargetDir: *name\n");

    //current_target_dir.name[0] = '/';
    //current_target_dir.name[1] = 0;

    // Limits: Copy 8 bytes only
    for ( i=0; i<8; i++ ){
        current_target_dir.name[i] = name[i];
    };

// done:
    current_target_dir.initialized = TRUE;
}

/*
 **********************
 * fsList
 *     Ring 0 routine to list files.
 */

// #todo
// Use 'pathname'.

int fsList ( const char *dir_name )
{
    int Absolute = FALSE;
    int i=0;


    debug_print ("fsList:\n");

    // dir name.

    if ( (void *) dir_name == NULL ){
        debug_print ("fsList: [FAIL] dir_name\n");
        goto fail;
    }

    if ( *dir_name == 0 ){
        debug_print ("fsList: [FAIL] *dir_name\n");
        goto fail;
    }

    // copy
    for ( i=0; i<11; i++ ){
        current_target_dir.name[i] = dir_name[i];
    };
    current_target_dir.name[i] = '\0';


    if ( dir_name[0] == '[' && dir_name[1] == 0 )
    {
        debug_print ("fsList: root\n");
        Absolute = TRUE;

        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
        for ( i=0; i<11; i++ ){
            current_target_dir.name[i] = '\0';
        };
        current_target_dir.name[0] = '/';
        current_target_dir.name[1] = '\0'; 
    }


    // #bugbug
    // We are using the current directory address,
    // not the directory provide by the user.
    
    // #todo
    // Set up the current dir address, based on the
    // name provided by the user.

    //
    // == current_target_dir ====================
    //

    // directory address.
    
    if ( current_target_dir.current_dir_address == 0 )
    {
        debug_print ("fsList: [FAIL] current_target_dir.current_dir_address \n");
        goto fail;
    }
    
    // #bugbug
    // Missing string finalization.
    //printk ("fsList: current_target_dir.name = {%s}\n", current_target_dir.name);
    

    // Listing ...

    // IN:
    // name, dir address, number of entries;
    // No return value.

    fsFAT16ListFiles ( 
        (const char *)     current_target_dir.name,
        (unsigned short *) current_target_dir.current_dir_address, 
        256 );

    debug_print ("fsList: done\n");
    return 0;  

fail:
    debug_print ("fsList: fail\n");
    refresh_screen();
    return -1;
}

/*
 *********************************
 * fsListFiles:
 *     Lista os arquivos em um diret�rio, dados os �ndices de disco, 
 * volume e diret�rio.
 */

// #bugbug
// Do not list this in ring0.

void 
fsListFiles ( 
    int disk_id, 
    int volume_id, 
    int directory_id )
{

    // #todo: 
    // Checar mais limites.
    // Use this: if ( disk_id < 0 || volume_id < 0 || directory_id < 0 )

    if ( disk_id == -1 || volume_id == -1 || directory_id == -1 )
    {
        debug_print ("fsListFiles: [FAIL] parameters\n");
        goto fail;
    }

    printf ("fsListFiles: disk={%d} vol={%d} dir={%d}\n", 
        disk_id, volume_id, directory_id );

	// Show!
	// Se o diret�rio selecionado � o diret�rio raiz do VFS.

    if ( current_disk == 0 && current_volume == 0 && current_directory == 0 )
    {
        debug_print ("fsListFiles: [FIXME] current\n");
        
        //vfsListFiles ();
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
 ***************************** 
 * fsRootDirGetFileSize: 
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

unsigned long fsRootDirGetFileSize ( unsigned char *file_name )
{
    unsigned long FileSize=0;    // 64bit
    unsigned int intFileSize=0;  // 32bit
    
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


    debug_print ("fsRootDirGetFileSize: $\n");


    if ( (void*) file_name == NULL ){
        printk("fsRootDirGetFileSize: [ERROR] file_name\n");
        goto fail;
    }

    if (*file_name == 0){
        printk("fsRootDirGetFileSize: [ERROR] *file_name\n");
        goto fail;
    }

	
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


    // #bugbug
    // Estamos chamando isso toda vez que
    // tentamos abrir um arquivo.

    // Carregando o diretório raiz.
    fs_load_rootdir ( 
        VOLUME1_ROOTDIR_ADDRESS, 
        VOLUME1_ROOTDIR_LBA, 
        32 );


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


    if ( (void *) root == NULL ){
        panic ("fsRootDirGetFileSize: [FAIL] No root file system!\n");
    }else{

        // Setores por cluster.
        Spc = root->spc;
        if (Spc <= 0){ panic ("fsRootDirGetFileSize: [FAIL] spc\n"); }

        // Max entries ~ Número de entradas no rootdir.
        // #bugbug: 
        // Devemos ver o número de entradas no diretório alvo.

        max = root->dir_entries;
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
        printf ("fsRootDirGetFileSize: [FIXME] name size fail %d\n",
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

fail:

    if ( (void*) file_name != NULL ){
        printf ("fsRootDirGetFileSize: [FAIL] %s not found\n", file_name );
     }

    //if ( (void*) NameX != NULL )
        // printf ("fsRootDirGetFileSize: %s not found\n", NameX );

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

    //FileSize = *(unsigned long*) (VOLUME1_ROOTDIR_ADDRESS + (z*2) + 28 );
    intFileSize = *(unsigned int*) (VOLUME1_ROOTDIR_ADDRESS + (z*2) + 28 );

    FileSize = (unsigned long) intFileSize;

	//printf ("%d \n" , root[ z+14 ]);
	//printf ("%d \n" , root[ z+15 ]);
	//printf ("done: FileSize=%d \n" , FileSize);

	//#debug
	//refresh_screen();
	//while(1){ asm("hlt"); }

    // #debug
    // printf ("fsRootDirGetFileSize: FileSize=%d \n" , FileSize );
    // refresh_screen ();

    return (unsigned long) ( FileSize & 0x00000000FFFFFFFF );
}


/*
 **************
 * fsLoadFile:
 *    Carrega um arquivo na memória.
 * 
 * IN:
 *     fat_address  = FAT address.
 *     dir_addresss = Directory address.
 *     dir_entries  = Number of entries in the given directory.
 *     file_name    = File name.
 *     file_address = Where to load the file. The buffer.
 *     buffer_limit = Maximum buffer size.
 * 
 * OUT: 
 *    1=fail 
 *    0=ok.
 */

// #obs
// Rotina específica para FAT16.
// Podemos mudar o nome para fsFat16LoadFile().
// Ou fs_Fat16_SFN_LoadFile()

// #bugbug
// This routine is nor respecting the number of entries
// in the diretory. It is using the limit of the root dir
// for all the directories, 512 entries.

unsigned long 
fsLoadFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    const char *file_name, 
    unsigned long buffer,
    unsigned long buffer_limit )
{

    int Status=-1;
    int i=0;
    int SavedDirEntry = 0;
    unsigned short next=0;
    
    // #todo: 
    // Rever. Número máximo de entradas.
    // #bugbug: 
    // Esse eh o numero de entradas no diretorio raiz.

    unsigned long DirEntries = (unsigned long) dir_entries;
    unsigned long MaxEntries = (unsigned long) FAT16_ROOT_ENTRIES;

    // Where to load the file.
    unsigned long Buffer      = (unsigned long) buffer;
    unsigned long BufferLimit = (unsigned long) buffer_limit;

    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.

    char tmpName[13];
    
    size_t FileNameSize = 0;
    unsigned long FileSize = 0;

    //int IsDirectory;

    // Cluster inicial
    unsigned short cluster=0; 

    // ?? 
    // Primeiro setor do cluster.
    unsigned long S=0;  

    // Usado junto com o endereço do arquivo.
    unsigned long SectorSize=0;

    int Spc=0;


    // #debug:
    debug_print ("fsLoadFile:\n");
    //printf      ("fsLoadFile:\n");

    // Updating fat address and dir address.

    if ( fat_address == 0 ){
        panic("fsLoadFile: [FAIL] fat_address\n");
    }

    if ( dir_address == 0 ){
        panic("fsLoadFile: [FAIL] dir_address\n");
    }

    unsigned short *  fat = (unsigned short *) fat_address;
    unsigned short *__dir = (unsigned short *) dir_address;

    // #debug
    // We only support one address for now.
    if ( fat_address != VOLUME1_FAT_ADDRESS ){
        panic("fsLoadFile: [FIXME] Sorry. We only support ONE fat address for now!\n");
    }


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


    if ( DirEntries > MaxEntries )
    {
        panic ("fsLoadFile: [FAIL] DirEntries\n");
    }

    // #test
    // Used only for debug.
    
    if ( DirEntries < MaxEntries )
    {
        panic ("fsLoadFile: [DEBUG] DirEntries IS LESS THE 512\n");
    }


//load_DIR:

    if ( MaxEntries == 0 || MaxEntries > FAT16_ROOT_ENTRIES )
    {
        panic ("fsLoadFile: [FAIL] MaxEntries limits\n");
    }


    if ( BufferLimit == 0 ){
        panic("fsLoadFile: [FAIL] BufferLimit\n");
    }

    // limite maximo de uma imagem de processo.
    if ( BufferLimit > (512*4096) ){
        panic("fsLoadFile: [FAIL] BufferLimit\n");
    }

    // Root file system structure.
    // + Checa se é válida a estrutura do sistema de arquivos.
    // + Pega a quantidade de setores por cluster.
    // + Pega o tamanho do diretório raiz. Ou seja, pega o número 
    //    máximo de entradas.
    // ...

    if ( (void *) root == NULL ){
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


    // file name

    if ( (void *) file_name == NULL ){
        printf ("fsLoadFile: [FAIL] file_name\n");
        goto fail;
    }

    if ( *file_name == 0 ){
        printf ("fsLoadFile: [FAIL] *file_name\n");
        goto fail;
    }


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
    
    // #bugbug: 
    // Essa rotina so pega o tamanho dos arquivos que estao 
    // no diretorio raiz.
    // Comparando nosso tamanho obtido com o tamanho do buffer.
    // Como a rotina de pegar o tamanho so pega no diretorio raiz
    // por enquanto, entao vamos apenas emitir um alerta que 
    // o tamanho do arquivo eh maior que o buffer, servira para debug.
    // Isso porque em todas as tentativas de pegar o tamanho do arquivo
    // fora do root, retornara 0.
    // #todo
    // Precisamos usar as estruturas de diretorio e 
    // as estruturas de buffer.
    
    FileSize = (unsigned long) fsRootDirGetFileSize ( (unsigned char *) file_name );
    
    if (FileSize==0)
    {
        debug_print ("fsLoadFile: [FIXME] FileSize\n");
        printf      ("fsLoadFile: [FIXME] FileSize %d\n", FileSize);
        //goto fail;
    }

    //printf ("Antes: FileSize %d BufferLimit %d\n",
    //        FileSize, BufferLimit );

    //if ( FileSize > 4000 )
    if ( FileSize > BufferLimit )
    {
        debug_print ("fsLoadFile: [FAIL] Buffer Overflow\n");
             printf ("fsLoadFile: [FAIL] FileSize %d BufferLimit %d\n",
                 FileSize, BufferLimit );
        goto fail;
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

    //fs_load_fat(VOLUME1_FAT_ADDRESS,VOLUME1_FAT_LBA,128);
    fs_load_fat(VOLUME1_FAT_ADDRESS,VOLUME1_FAT_LBA,246);
    
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

    // #todo
    // Create some limits for 'Buffer'.
    // We can not load a file in the same address of the
    // base kernel or the rootdir ...
    // See: gva.h
    
    // #test
    // Protectng some core areas.
    // We can use a helper function for this validation.

    // fat
    if ( Buffer == VOLUME1_FAT_ADDRESS_VA ){
        panic("fsLoadFile: [FAIL] can not load at VOLUME1_FAT_ADDRESS_VA\n");
    }

    // rootdir
    if ( Buffer == VOLUME1_ROOTDIR_ADDRESS_VA ){
        panic("fsLoadFile: [FAIL] can not load at VOLUME1_ROOTDIR_ADDRESS_VA\n");
    }

    // base kernel
    if ( Buffer == KERNEL_IMAGE_BASE ){
        panic("fsLoadFile: [FAIL] can not load at KERNEL_IMAGE_BASE\n");
    }

    // lfb
    if ( Buffer == DEFAULT_LFB_VIRTUALADDRESS ){
        panic("fsLoadFile: [FAIL] can not load at DEFAULT_LFB_VIRTUALADDRESS\n");
    }

    // backbuffer
    if ( Buffer == DEFAULT_BACKBUFFER_VIRTUALADDRESS ){
        panic("fsLoadFile: [FAIL] can not load at DEFAULT_BACKBUFFER_VIRTUALADDRESS\n");
    }


    //
    // Read LBA.
    //

    // Caution!
    // Read lba.
    // Increment buffer base address.
    // Pega o próximo cluster na FAT.
    // Configura o cluster atual.
    // Ver se o cluster carregado era o último cluster do arquivo.
    // Vai para próxima entrada na FAT.


    read_lba ( 
        Buffer, 
        ( VOLUME1_DATAAREA_LBA + cluster -2 ) ); 

    Buffer = (unsigned long) (Buffer + SectorSize); 

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

// Not tested yet
unsigned long 
fsLoadFile2 ( 
    struct file_context_d *fc, 
    unsigned char *file_name )
{

    if ( (void*) fc == NULL ){
        debug_print("fsLoadFile2: fc\n"); 
        return 0;
    }

    if ( (void*) file_name == NULL ){
        debug_print("fsLoadFile2: file_name\n"); 
        return 0;
    }

    if (*file_name == 0){
        debug_print("fsLoadFile2: *file_name\n"); 
        return 0;
    }

    fc->file_name = file_name;
    
    return fsLoadFile ( 
               (unsigned long)   fc->fat_address,
               (unsigned long)   fc->dir_address,
               (int)             fc->dir_entries,
               (unsigned char *) fc->file_name, 
               (unsigned long)   fc->file_address,
               (unsigned long)   fc->buffer_limit );
}

/*
 ********************************
 * fsLoadFileFromCurrentTargetDir:
 * 
 *     Carrega o diretório que está configurado como 'target dir' 
 * em algum lugar qualquer da memória. 
 *     Usa-se a estrutura current_target_dir pra gerenciar isso.
 */

// #bugbug
// too much allocation.
// How many times this function is called ??
// 4KB each time ?

int fsLoadFileFromCurrentTargetDir (void)
{

    int Ret = -1;
    int i=0;
    unsigned long new_address = 0;


    debug_print ("fsLoadFileFromCurrentTargetDir: [FIXME] Loading dir \n");

	//#bugbug
	//Isso 'e um limite para o tamanho do arquivo (apenas dir).
	//precisamos expandir isso.
	//aqui no m'aquimo o arquivo pode ter 4kb.
	//acho ques estamos falando somente de diret'orio aqui.

    // #bugbug
    // too much allocation.
    // How many times this function is called ??
    // 4KB each time ?

    new_address = (unsigned long) kmalloc (4096);

    if ( new_address == 0 ){
        debug_print ("fsLoadFileFromCurrentTargetDir: new_address\n");
        return -1;
    }

    current_target_dir.current_dir_address = new_address;

    // ??
    // Se o endereço atual falhar, 
    // resetamos ele e retornamos.

    if ( current_target_dir.current_dir_address == 0 ){
        debug_print ("fsLoadFileFromCurrentTargetDir: [FAIL] invalid address\n");
        goto fail;
    }


	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) old_dir_addr=(%x) #debug \n",
	//    current_target_dir.name, current_target_dir.current_dir_address );


    //++
    //taskswitch_lock ();
    //scheduler_lock ();
    Ret = (int) fsLoadFile ( 
                    VOLUME1_FAT_ADDRESS,                       // fat cache address
                    current_target_dir.current_dir_address,    // src dir address 
                    FAT16_ROOT_ENTRIES, //#bugbug: Number of entries.          // number of entries.
                    (unsigned char *) current_target_dir.name,                 // file name 
                    (unsigned long)   current_target_dir.current_dir_address,  // file address
                    4096 );                                    // #bugbug buffer limit 4KB.
    //scheduler_unlock ();
    //taskswitch_unlock ();
    //--


	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) new_dir_addr=(%x) #debug \n",
	//   current_target_dir.name, current_target_dir.current_dir_address );


    debug_print ("fsLoadFileFromCurrentTargetDir: done\n");
    
    return (int) Ret;

fail:
        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
        for ( i=0; i<11; i++ ){
            current_target_dir.name[i] = '\0';
        };
        current_target_dir.name[0] = '/';
        current_target_dir.name[1] = '\0';
        return -1;
}


/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 * 
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global. 
 */ 

// Used by the service 175, cd command.

void fsUpdateWorkingDiretoryString ( char *string )
{
    struct process_d  *p;
    char *tmp;
    int i=0; 

    int string_size = 0;


    debug_print ("fsUpdateWorkingDiretoryString:\n"); 

    tmp = string;
    string_size = sizeof(string);


    // Initialized ?
    if ( CWD.initialized != TRUE )
    {
        debug_print ("fsUpdateWorkingDiretoryString: [FAIL] CWD not initialized\n"); 
        
        // #todo
        // Call the initialization routine.
        
        return;
    }

    // string

    if ( (void *) string == NULL ){
        debug_print ("fsUpdateWorkingDiretoryString: string\n"); 
        return;  
    }

    if (*string == 0){
        debug_print ("fsUpdateWorkingDiretoryString: *string\n"); 
        return;  
    }


    if (string_size <= 0){
        debug_print ("fsUpdateWorkingDiretoryString: [FAIL] string_size\n"); 
        return;  
    }

    // Current process.

    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");
    }else{
        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: p validation\n");
        }

        // Atualiza a string do processo atual. 
        // Concatenando.
        
        if ( (void *) string != NULL )
        {
            // #bugbug
            // We need to handle the string size limit.
            
            // Concatena string.
            strcat ( p->cwd_string, string );

            // Concatena separador.
            strcat ( p->cwd_string, FS_PATHNAME_SEPARATOR );

            // Atualiza a string global usando a string do 
            // processo atual.
            // #bugbug: nao precisamos disso ...
            // so precismos de cwd na estrutura de processo.
            
            // #importante
            // Respeitar o limite.
            
            for ( i=0; i<32; i++ )
            {
                CWD.path[i] = p->cwd_string[i];
            };
            CWD.path[31] = 0; //finaliza

            // #bugbug: rever isso.
            // Nome do diretório alvo atual.
            
            // nao precismos disso ...
            // ou usamos o cwd do processo ou
            // o diretorio raiz para paths absolutos.
            
            for ( i=0; i< 11; i++ )
            {
                current_target_dir.name[i] = *tmp;
                tmp++;
            };
            current_target_dir.name[11] = 0; //finaliza
        }
    };

    debug_print ("fsUpdateWorkingDiretoryString: done\n"); 
}

// helper function to handle fat cache status.
void fs_fat16_cache_not_saved(void)
{
    fat_cache_saved = CACHE_NOT_SAVED;
}

/*
 ************************************************
 * fs_fntos:
 *     
 *     'file name to string'.
 * 
 *     rotina interna de support.
 *     isso deve ir para bibliotecas depois.
 *     não tem protótipo ainda.
 * 
 * Created by: Luiz Felipe.
 * 2020 - Adapted by Fred Nora.
 */

 // #bugbug
 // Isso modifica a string lá em ring3.
 // prejudicando uma segunda chamada com a mesma string
 // pois já virá formatada.

// #bugbug
// const char * tornaria esse endereço em apenas leitura.

void fs_fntos ( char *name )
{
    int i  = 0;
    int ns = 0;

    char ext[4];
    ext[0] = 0;  ext[1] = 0;  ext[2] = 0;  ext[3] = 0;

    //#test

    if ( (void*) name == NULL ){ return; }

    if (*name == 0){ return; }


    // Transforma em maiúscula enquanto não achar um ponto.
    // #bugbug: E se a string já vier maiúscula teremos problemas.

    while ( *name && *name != '.' )
    {
        if ( *name >= 'a' && *name <= 'z' )
        {
            *name -= 0x20;
        }

        name++;
        ns++;
    };

    // #bugbug
    // Esse negócio de acrescentar a extensão
    // não é bom para todos os casos.

    if ( name[0] == '\0' && ns <= 8 )
    {
        ext[0] = 'B';  ext[1] = 'I';  ext[2] = 'N';  ext[3] = '\0';

        goto CompleteWithSpaces;
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

CompleteWithSpaces:

    while (ns < 8)
    {
        *name++ = ' ';
        ns++;
    };

    // Acrescentamos a extensão

    for (i=0; i < 3; i++){  *name++ = ext[i];  };

    // Finalizamos.

    *name = '\0';
}


// Pega um fd na lista de arquivos do processo, dado o PID.
// Objects[i]

int fs_get_free_fd_from_pid (int pid)
{
    struct process_d *p;
    int __slot=0;


    //#todo max
    if ( pid<0 ){
        debug_print ("fs_get_free_fd_from_pid: [FAIL] pid\n");
        return -1;
    }

    // #bugbug
    // Check limit

    //
    // Process.
    //
  
    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        debug_print ("fs_get_free_fd_from_pid: p\n");
        return -1;
    }

    if ( p->used != 1 || p->magic != 1234 ){
        debug_print ("fs_get_free_fd_from_pid: p validation\n");
        return -1;
    }
        
        
    // Pick a free one.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ return (int) __slot; }
    };
 
    return -1;
}

/*
 **************************************
 * fs_initialize_process_cwd:
 *     Cada processo deve inicialiar seus dados aqui. 
 */

// #todo:
// handle return value ...
// What functions is calling us?

int fs_initialize_process_cwd ( int pid, char *string )
{
    struct process_d *p;
    int i=0;


    if (pid<0){
        debug_print ("fs_initialize_process_cwd: pid\n");
        return 1;
    }

    // string

    if ( (void *) string == NULL ){
        panic ("fs_initialize_process_cwd: string\n");
        //return 1;
    }

    if (*string == 0){
        panic ("fs_initialize_process_cwd: *string\n");
        //return 1;
    }

    // Current process.

	// #importante
	// Vamos copiar a string para a estrutura do processo atual.

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_initialize_process_cwd: p\n");
    }else{
        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_initialize_process_cwd: validation\n");
        }

        // ?? fixed size.
        for ( i=0; i<32; i++ ){ p->cwd_string[i] = string[i]; }
        
        p->cwd_string[31] = 0; // finalizing 
    };

    return 0;
}

/*
 *********************************************************
 * fs_load_path:
 *     Carrega nesse endereço o arquivo que está nesse path.
 *     ??: O endereço pode ser ring3?
 */

// IN:
// @path:
//     Path de dois níveis, endereço onde carregar.
//     Ex: "/BIN/GDESHELL.BIN"
// @address:
//     Address to load the file.
//

// #bugbug
// Starts only on root dir.

// #ok
// Carregou um arquivo com 3 niveis.

// See:
// sys_load_path() and service 4004.

//    0 ---> ok.
// != 0 ---> fail

int 
fs_load_path ( 
    const char *path, 
    unsigned long address, 
    unsigned long buffer_size )
{

    // #todo
    // Work on that limit stuff.
    // We have the limit given by the argument,
    // that needs to be respected.
    // And we have the size of the root dir.
    
    unsigned long MaxEntries = FAT16_ROOT_ENTRIES;  //512


    int i=0;         // Deslocamento dentro do buffer.
    int level=0;
    int l=0;
    unsigned long n_levels = 0;
    
    // Fail. 
    // Usado na função que carrega o arquivo.
    int Ret = -1;    
        
    char buffer[12];
    unsigned char *p;


    // Onde carregaremos o diretório.
    void *__src_buffer;
    void *__dst_buffer;
    void *__file_buffer;


    // path

    if ( (void*) path == NULL ){
        panic ("fs_load_path: path\n"); 
    }

    if (*path == 0){
        panic ("fs_load_path: *path\n"); 
    }

    // Address
    if (address == 0){
        panic ("fs_load_path: address\n");
    }

    if (buffer_size == 0){
        panic ("fs_load_path: buffer_size\n");
    }


    // File buffer.
    __file_buffer = (void *) address;


    // Counting the levels.
    n_levels = fs_count_path_levels(path);
    
    if (n_levels==0){
        panic ("fs_load_path: n_levels\n");
    }
    
    printf ("fs_load_path: path with %d levels\n",n_levels);


    // Start with 0.
    level = 0;

    // Path provisório.
    p = path;


    // #bugbug
    // Overflow quando colocarmos um diretorio maior que
    // o buffer.

    // Primeiro src =  root address;
    __src_buffer = (void *) VOLUME1_ROOTDIR_ADDRESS;
    unsigned long limits = (512*32);

    
    // Not absolute   
    if ( p[0] != '/' ){
        panic ("fs_load_path: Not absolute pathname \n");
    }

    
    //
    // loop: Carregar n levels.
    //

    for (l=0; l<n_levels; l++)
    {

        printf ("\n[LEVEL %d]\n\n",l);
        
        // The level needs to start with '/', even the first one.
        if ( p[0] != '/' ){
            panic ("fs_load_path: All levels need to start with '/' \n");
        }
        
        //Skip the '/'.
        p++;  

        // Walk 13 chars in the same level.
        for ( i=0; i<12; i++ )
        {
            // #debug
            printf ("%c", (char) *p);

            // Copia o char para o buffer até que o char seja '/'
            // indicando inicio do próximo nível.
            
            buffer[i] = (char) *p;
            
            
            // O ponto deve aparecer no último nível.
            // caso contrário falhou
            if ( *p == '.' )
            {
                if ( l != (n_levels-1) ){
                    panic ("fs_load_path: Directory name with '.'\n");
                }
                
                // Se o ponto está além do limite permitido.
                //if (i>7){
                if (i>=7){
                    printf ("fs_load_path: '.' fail.\n");
                    panic ("Name size bigger than 8.\n");
                }
                
                // Se o ponto for antes do nono slot. OK.
                if (i<8)
                {
                     // Nome tem no máximo 8 chars.
                     // Completamos com espaço, pois queremos o formato:
                     // "FILE    123"
                     while (i<=7){ buffer[i] = ' '; i++; };

                     
                     // Skip the dot '.'.
                     // Yes it is a dot. See the IF statement above.
                     p++;
                     
                     // Add the extension.
                     while (i<=11)
                     {
                         buffer[i] = (char) *p;
                         i++;
                         p++;
                     } 
                       
                     // Finalize the string.
                     buffer[11] = 0;
                     
                     printf ("\n");
                     printf ("fs_load_path: This is the name {%s}\n",buffer);   
                }


                //
                // Load file.
                //
    
                // Como esse é o último, então vamos usar o endereço desejado pelo usuário.
                __dst_buffer = (void *) __file_buffer;
    
                if ( (void *) __dst_buffer == NULL ){
                    panic ("fs_load_path: __dir\n");
                }

                
                // #bugbug
                // Se o diretório for o diretório raiz
                // então não podemos sondr menos que 512 entradas.
                // #todo: Temos que considerar o número de entradas
                // exatos de um diretório.
                // Podemos ter um limite estabelecido pelo sistema.
                
                // IN: 
                // fat address, dir address, filename, file address.
                
                Ret = fsLoadFile ( 
                          (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                          (unsigned long) __src_buffer,         // dir address. onde procurar. 
                          (unsigned long) MaxEntries,          // #bugbug: Number of entries. 
                          (unsigned char *) buffer,             // nome 
                          (unsigned long) __dst_buffer,         // addr. Onde carregar.
                          limits );                             // tamanho do buffer onde carregar.             
                // ok.
                if ( Ret == 0 )
                {
                    printf ("Level %d loaded!\n\n",l);
                    
                    // #importante
                    // Esse nível tinha ponto, então deveria ser o último.
                    if ( l != (n_levels-1) )
                    {
                        printf ("fs_load_path: Directory name with '.'\n");
                        panic ("It needs to be the last level.\n");
                    }

                    // SUCCESS ?!!
                    debug_print ("fs_load_path: done\n");
                    return 0;

                }else{
                    panic ("fs_load_path: [FAIL] Loading level 0\n");
                };
            }


            // Se encontramos um indicador de próximo nível,
            // então esse nível não será considerado binário.
            // obs: 
            // Ao iniciar o for ele precisa encontrar esse mesmo char.
            
            if ( *p == '/' )
            {
                // Encontramos o indicador de proximo nivel,
                // o buffer ja tem chars que foram colocados um a um.
                // Nao encontramos ponto nesse nivel.
                // Vamos completar o nome do diretorio com espaços e finalizar.
                
                if (i<11)
                {
                    // Adicionando espaços.
                    // O formato desejado eh: "DIRXDIRX   "
                    // Nome do diretorio sem extensao.
                    while (i<=11)
                    { 
                        //o primeiro espaço deve retirar a barra colocada antes
                        buffer[i] = ' ';  
                        i++; 
                    }
                }
                
                // Finalize the string.
                buffer[11] = 0;
                
                printf ("\n");
                printf ("fs_load_path: This is the name {%s}\n",buffer);

                //
                // Load directory.
                //

                // #bugbug
                // E se o arquivo for maior que a area alocada.
                // Alocando memória para carregar o diretório.
                
                unsigned long BUGBUG_OVERFLOW = (512*32);
                limits = BUGBUG_OVERFLOW;
                
                __dst_buffer = (void *) kmalloc (    BUGBUG_OVERFLOW    ); 
    
                if ( (void *) __dst_buffer == NULL ){
                    panic ("fs_load_path: __dir\n");
                }
                          
                      //IN: fat address, dir address, filename, file address.
                Ret = fsLoadFile ( 
                          (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                          (unsigned long) __src_buffer,         // dir address. onde procurar.
                          MaxEntries,                           // #bugbug: Number of entries.  
                          (unsigned char *) buffer,             // nome que pegamos no path 
                          (unsigned long) __dst_buffer,         // onde carregar. 
                          limits );                             // tamanho do buffer onde carregar.
                          
                          
                // ok.
                if ( Ret == 0 )
                {
                    printf ("Level %d loaded!\n\n",l);
                    
                    // O endereço onde carregamos o arquivo desse nível
                    // será o endereço onde vamos procurar o arquivo do próximo nível.
                    __src_buffer = __dst_buffer;
                    
                    break;

                }else{
                    panic ("fs_load_path: [*FAIL] Loading level 0\n");
                };
            }


            // Avançamos o char se não foi '.', nem '/'.
            p++;
        };
    };   


fail:
    debug_print ("fs_load_path: Fail\n");
    printf      ("fs_load_path: Fail\n");
    refresh_screen();
    return (-1);
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

    struct process_d *p;
    int i=0;


    // CWD

    if ( CWD.initialized != TRUE ){
        printf ("fs_pathname_backup: [FAIL] CWD not initialized\n"); 
        return;
    } 


    // pid

    if ( pid<0 ){
        printf ("fs_pathname_backup: [FAIL] pid\n"); 
        return;
    }

    // n

    if (n<0) {  return;  }
    if (n==0){  return;  }

    // Process

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");
    }else{
        if ( p->used != TRUE || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: validation\n");
        }

        char *path = (char *) p->cwd_string;

        register char *s = path + strlen( path );
 
        if (*path){ s--; };

        while (n--)
        {
            while (*s == '/'){ s--; };
            while (*s != '/'){ s--; };

            *++s = '\0';
        };

        // Atualizando a string global.
        for ( i=0; i<32; i++ ){
            CWD.path[i] = p->cwd_string[i];
        };

        // Name.
        for ( i=0; i< 11; i++ ){
            current_target_dir.name[i] = '\0';
        };
    };
}

/*
 *********************************
 * fs_print_process_cwd
 *     Cada processo tem seu proprio pwd.
 *     Essa rotina mostra o pathname usado pelo processo. 
 */

// this is used by the pwd command. service 170.

int fs_print_process_cwd (int pid)
{
    struct process_d *p;


    debug_print ("fs_print_process_cwd:\n");
    printf      ("fs_print_process_cwd:\n");


    if (pid<0){
        debug_print ("fs_print_process_cwd: [FAIL] pid\n");
        return -1;
    }

    // Process

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_print_process_cwd: p\n");
    }else{
        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_print_process_cwd: validation\n");
        }

        // #bugbug
        // Is this element a pointer or a buffer ?
        // >>> This element is an array.
        
        if ( (void *) p->cwd_string != NULL )
        {
            //p->cwd_string[31] = 0;
            printf ("> PID=%d p->cwd_string {%s} \n", 
                p->pid, p->cwd_string);
        }

        // #bugbug
        // Is this element a pointer or a buffer ?

        if ( (void *) current_target_dir.name != NULL )
        {
            //current_target_dir.name[31] = 0;
            printf ("> PID=%d current_target_dir.name {%s} \n", 
                p->pid, current_target_dir.name);
        }

        refresh_screen();
        return 0;
    };

    debug_print ("fs_print_process_cwd: fail\n");   
    return -1;
}

void fs_show_file_info (file *f)
{

    if ((void*)f==NULL)
    {
        debug_print("fs_show_file_info: fail\n");
        return;
    }

    if (f->used==1)
    {
        if ( (void*) f->_tmpfname != NULL )
        {
            printf ("Name={%s}\n",f->_tmpfname);
            //refresh_screen();
        }
    }
}


void fs_show_file_table(void)
{
    file *f;
    int i=0;


    printf ("\nfile_table:\n");
    
    for (i=0; i<32; i++)
    {
        f = (file*) file_table[i];
        
        if( (void*)f != NULL )
            fs_show_file_info(f);
    };

    refresh_screen();
}

void fs_show_inode_info (struct inode_d *i)
{
    if ( (void *) i == NULL )
    {
        debug_print("fs_show_inode_info: fail\n");
        return;
    }

    if (i->used == 1)
    {
        if ( (void*)i->path != NULL )
        {
            printf ("Name={%s}\n",i->path);
        }
    }  
}

void fs_show_inode_table(void)
{
    struct inode_d *inode;
    register int i=0;


    printf ("\n inode_table: \n");
    
    for (i=0; i<32; ++i)
    {
        inode = (struct inode_d *) inode_table[i];
        
        if ( (void*)inode != NULL )
        {
            if( inode->used == 1 && inode->magic == 1234 )
            {
                fs_show_inode_info(inode);
            }
        }
    };

    refresh_screen();
}

void fs_show_root_fs_info(void)
{

    printf ("\n");
    printf ("fs_show_root_fs_info:\n");


    // root fs structure.

    if ( (void *) root == NULL ){
        printf ("No root structure\n");
        goto fail;
    }else{

        if ( root->used != 1 || root->magic != 1234 ){
             printf ("Validation fail\n");
             goto fail;
        }

        printf ("name = %s \n",       root->name );
        printf ("Object type %d \n",  root->objectType );
        printf ("Object class %d \n", root->objectClass );
        printf ("type = %d \n",       root->type );
        printf ("Dir entries %d \n",  root->dir_entries );
        printf ("Entry size %d \n",   root->entry_size );
        // ...
        goto done;
    }; 

fail:
    printf("fail\n");
done:
    refresh_screen();
    return;
}

// sys_pwd -  Service 170.
void sys_pwd (void)
{
    // #todo: Check overflow.

    if ( current_process < 0 ){
        panic ("sys_pwd: [FAIL] current_process\n");
    }

    fs_print_process_cwd (current_process);
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
    const char *file_name, 
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
    //printf      ("fsSaveFile:\n");


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
        panic("fsSaveFile: [FIXME] We only support ONE fat address for now!\n");
    }


    if ( (void *) file_name == NULL )
    {
        debug_print ("fsSaveFile: [ERROR] file_name\n");
        printf      ("fsSaveFile: [ERROR] file_name\n"); 
        goto fail;
    }

    if ( *file_name == 0 )
    {
        debug_print ("fsSaveFile: [ERROR] *file_name\n");
        printf      ("fsSaveFile: [ERROR] *file_name\n"); 
        goto fail;
    }


    // #bugbug
    // Esse endereço eh valido ?
    
    /*
    printf ("name address = %x \n", &file_name );
    printf ("name    = %s \n", file_name ); 
    printf ("size    = %d \n", file_size );       // Size in sectors.
    printf ("nbytes  = %d \n", size_in_bytes );
    printf ("address = %x \n", file_address );
    printf ("flag    = %x \n", flag );
    printf ("entries = %d \n", dir_entries );
    */

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

    fs_load_rootdir( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );

    fs_load_fat(VOLUME1_FAT_ADDRESS,VOLUME1_FAT_LBA,246);


    // Procurando cluster livre na fat.
    // Nesse momento construimos uma lista de clusters livres.
    // #todo: 
    // Essa lista já devia existir e agora somente 
    // usaríamos.
    // #todo: Essa rotina poderia seruma helper function?


//SearchEmptyEntries:
 
	// #bugbug
	// Obs: Esse limite é improvisado.

    while ( i < CLUSTERS_TO_SAVE_MAX )
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
                fat16ClustersToSave[j] = (unsigned short) 0xfff8; 
                goto save_file;
            }

            //salva um endereço livre
            //salvamos um índice na fat dentro da lista
            //incrementa a lista

            fat16ClustersToSave[j] = (unsigned short) c; 
            j++; 

            // Decrementa o tamanho do arquivo!
            file_size--; 
        };

        c++;    // Incrementa o deslocamento na fat. 
        i++;    // Incrementa a quantidade de busca.
    }; 

    // Fail
    // Nossa busca por clusters livres dentro da fat não deu certo.
    // Provavelmente não encontramos uma quantidade suficiente.

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
    first = fat16ClustersToSave[i];

	// #debug
	// printf("first={%x}\n",first);

    // Create directory entry
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
    DirEntry[13] = 0x08;  DirEntry[14] = 0x08;  DirEntry[15] = 0xb6;

    // Creation date.
    DirEntry[16] = 0xb6;  DirEntry[17] = 0x4c;

    // Access date.
    DirEntry[18] = 0xb8;  DirEntry[19] = 0x4c;

	// ??
	// First cluster. 
	// 0 para fat12 ou 16
    DirEntry[20] = 0;
    DirEntry[21] = 0;

    // Modifield time.
    DirEntry[22] = 0xa8;  DirEntry[23] = 0x49;

    // Modifield date.
    DirEntry[24] = 0xb8;  DirEntry[25] = 0x4c;

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


    // IN: 
    // directory address, max number of entries.
    
    FreeIndex = (int) findEmptyDirectoryEntry ( 
                          dir_address, 
                          dir_entries );

    if ( FreeIndex == -1 ){
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


    // Loop

    while (TRUE){
 
        // Pegamos o atual na lista.
        // Se ele eh o sinalizador de fim de lista, 
        // entao entao colocamos o sinalizador de fim de arquivo
        // no offset indicado pelo penultimo elemento da lista.
        
        next = fat16ClustersToSave[i];

        // #debug.
        printf ("fsSaveFile: [DEBUG] next={%x}\n", next);

        if ( next == 0xFFF8 ){

            next = fat16ClustersToSave[i-1];
            
            fat[next] = 0xFFF8;

            goto do_save_dir_and_fat;

        // Se não é assinatura ainda.
        }else{

            // #bugbug
            // Estamos usando isso sem nem mesmo checar seu valor.
            // precisamos de limtes aqui. Para evitarmos overflow.
            
            // Grava na fat o endereço do próximo cluster
            fat[next] = fat16ClustersToSave[i+1];
 
            //#debug 
            //printf("write_lba\n");
            //refresh_screen();

            disk_ata_wait_irq ();

            //grava - aqui next esta certo!!!
            //write_lba ( (unsigned long) address, VOLUME1_DATAAREA_LBA + next -2 );
            my_write_hd_sector ( 
                (unsigned long) address, 
                (unsigned long) ( VOLUME1_DATAAREA_LBA + next -2), 
                0, 
                0 );

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

    // IN: root dir address, root dir lba, root dir size in sectors.

    //if ( dir_address == ROO...
    fs_save_rootdir( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );

    // Sinalizando que o cache de fat precisa ser salvo.

    fs_fat16_cache_not_saved();

    debug_print ("fsSaveFile: done\n");
    printf      ("fsSaveFile: done\n");
    refresh_screen();
    return 0;

fail:
    debug_print ("fsSaveFile: [FAIL]\n");
    printf      ("fsSaveFile: [FAIL]\n");
    refresh_screen ();
    return (int) 1;

}

/*
 *****************************
 * sys_write_file_to_disk:
 *     Interface para salvar arquivo ou diretório.
 *     Isso pode ser usado para criar um diretório ou 
 * copiar um diretório. 
 */

// #todo:
// vamos fazer igual ao sys_read_file 
// e criarmos opções ... se possível.

// IN: 
// name, size in sectors, size in bytes, adress, flag.

int
sys_write_file_to_disk ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{
    int __ret = -1;

    debug_print ("sys_write_file_to_disk:\n");


    if ( (void*) file_name == NULL ){
        debug_print ("sys_write_file_to_disk: file_name\n");
        return -1;
    }

    if ( *file_name == 0 ){
        debug_print ("sys_write_file_to_disk: *file_name\n");
        return -1;
    }


    //++
    // See: sci/fs/write.c
    //taskswitch_lock ();
    //scheduler_lock ();

    __ret = (int) fsSaveFile ( 
                      VOLUME1_FAT_ADDRESS, 
                      VOLUME1_ROOTDIR_ADDRESS, 
                      FAT16_ROOT_ENTRIES,
                      (char *) file_name,    
                      (unsigned long) file_size,       
                      (unsigned long) size_in_bytes,  
                      (char *) file_address,          
                      (char) flag );                  

    //scheduler_unlock ();
    //taskswitch_unlock ();
    //--

    debug_print ("sys_write_file_to_disk: done\n");
    
    return (int) __ret;
}



/*
 ************************************* 
 * sys_read_file_from_disk: 
 * 
 *     This is called by sys_open() in sys.c
 */

// usada por open()
// tem que retornar o fd e colocar o ponteiro na lista de arquivos
// abertos.
// Carrega um arquivo do disco para a memoria.
// funcionou.

// #bugbug
// Na minha m�quina real, �s vezes d� problemas no tamanho do arquivo.

// #bugbug
// Estamos alocando mem�ria em ring para carregar o arquivo
// e depois estamos usando o buffer em ring3 passado pelo usu�rio.
// >>> vamos confiar no usu�rio e usarmos

// #bugbug
// precisamos colocar os arquivos também na lista
// global de arquivos abertos. file_table[]
// E na lista de inodes. inode_table[]
// See: fs.c

// #bugbug
// Nao seria o read() usado para ler um arquivo ja aberto ??
// sim. a rotina de suporte para read esta em sys_read e 
// nao chama essa aqui.
// essa aqui poderia ter outro nome, pois ela carrega um arquivo
// poderia chamar-se load.

int 
sys_read_file_from_disk ( 
    char *file_name, 
    int flags, 
    mode_t mode )
{
    int __ret = -1;

    file  *__file;
    size_t FileSize=-1;
    
    struct process_d *p;

    int __slot = -1;  // ofd.
    int Status = -1;

    void *buff;


    debug_print ("sys_read_file_from_disk: $\n");


    if ( (void*) file_name == NULL ){
        debug_print ("sys_read_file_from_disk: file_name\n");
        return -1;
    }

    if ( *file_name == 0 ){
        debug_print ("sys_read_file_from_disk: *file_name\n");
        return -1;
    }


    // Convertendo o formato do nome do arquivo.    
    // >>> "12345678XYZ"
    // #bugbug: Isso ja foi feito em ring3 por open().

    fs_fntos ( (char *) file_name );


    // #debug
    printf ("FILE={%s}\n",file_name);
    refresh_screen();

    // #bugbug
    // We need to search in the inode list. inode_table[]
    // If the file is found in the inode list, so we don't
    // need to load it again, just increment the counter.

    // #todo
    // fs_search_inode_table(file_name);

    // Searching for the file only on the root dir.

    Status = (int) search_in_dir ( file_name, VOLUME1_ROOTDIR_ADDRESS );

    // Quando não existe, tentamos criar.
    // #bugbug: Então 'cat' não deve chamar essa função.

    // found
    if (Status == TRUE)
    {
        debug_print("sys_read_file_from_disk: Found\n");
        refresh_screen();
        goto __go;
    }
    
    if (Status != TRUE)
    {
         //#debug
         printf ("sys_read_file_from_disk: [FIXME] File not found!\n");
         refresh_screen();
         
         // Create a new one.
         if (flags & O_CREAT)
         {
             debug_print ("sys_read_file_from_disk: [O_CREAT] Creating a new file\n"); 

             buff = (void*) kmalloc(1024);
             if ((void*)buff==NULL)
             {
                 debug_print("sys_read_file_from_disk: buff fail\n");
                 refresh_screen();
                 return -1; 
             }

             //++
             // See: sci/fs/write.c
             //taskswitch_lock ();
             //scheduler_lock ();

             __ret = (int) fsSaveFile ( 
                               VOLUME1_FAT_ADDRESS, 
                               VOLUME1_ROOTDIR_ADDRESS, 
                               FAT16_ROOT_ENTRIES, 
                              (char *) file_name, 
                              (unsigned long) 2,      // size in sectors 
                              (unsigned long) 1024,   // size in bytes  
                              (char *) buff,          // buffer ?
                              (char) 0x20 );          // flag 

              //scheduler_unlock ();
              //taskswitch_unlock ();
              //--
              
              // Ok
              if (__ret == 0)
              {
                  debug_print("sys_read_file_from_disk: Created new file\n");
                  refresh_screen();
                  goto __go;
              }
         }

         printf("sys_read_file_from_disk: [FIXME] Can't create new file\n");
         refresh_screen();
         return (int) (-1);
    }

__go:

    //
    // Process.
    //
  
    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print ("sys_read_file_from_disk: p\n");
        return -1;
    }

    if ( p->used != 1 || p->magic != 1234 ){
        debug_print ("sys_read_file_from_disk: validation\n");
        return -1;
    }
    
    
    // Procurando um slot livre.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ goto __OK; }
    };
    
    panic ("sys_read_file_from_disk: No slots!\n");

// Slot found.
__OK:

    if ( __slot < 0 || __slot >= 32 )
    {
        printf ("sys_read_file_from_disk: Slot fail\n");
        refresh_screen();
        return (int) (-1);
    }
 
    // Struct
    
    __file = (file *) kmalloc( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        printf ("sys_read_file_from_disk: __file\n");
        refresh_screen();
        return -1;
    }else{
        __file->used  = TRUE;
        __file->magic = 1234;
        __file->pid = (pid_t) current_process;
        __file->uid = (uid_t) current_user;
        __file->gid = (gid_t) current_group;

        
        // #bugbug [FIXME]
        // We need a type in read().

        // #bugbug
        // This function was called by sys_open, and open
        // is able to open any kind of file.
        // Why are we using this type here?
        
        __file->____object = ObjectTypeFile;

        // ==================
        
        // #todo #bubug
        // Permissoes:
        // As permissoes dependem do tipo de arquivo.
       
        // #bugbug: Let's do this for normal files for now.
        __file->sync.can_read  = TRUE;
        __file->sync.can_write = TRUE;

        __file->sync.action = ACTION_NULL;
        
        // ==================
  
        // #todo:
        // We need to get the name in the inode.
        //__file->_tmpfname = NULL;
 

        __file->_lbfsize = BUFSIZ;
        __file->_r = 0;
        __file->_w = 0;
        __file->_file = __slot;
        __file->fd_counter = 1; //inicializando. 


        // #todo
        // Se ele não foi encontrado na lista de inodes
        // e tivemos que carrega-lo do disco, então
        // precisamos colocar ele na lista de inodes.. inode_table[]
        // Atenção: O arquivo será carregado logo abaixo.
        
        // #todo
        // atualizar a tabela  global de arquivos. file_table[]
    };
    

    //
    // buffer
    //

    // buffer padrão
    // #bugbug: open chama isso. E se o arquivo for maior que o buffer ?
    // open() precisa alocar outro buffer.
        
    __file->_base = (char *) kmalloc(BUFSIZ);
    
    if ( (void *) __file->_base == NULL ){
        printf ("sys_read_file_from_disk: buffer fail\n");
        refresh_screen();
        return -1;
    }


    // #debug
    printf ("FILE_AGAIN={%s}\n",file_name);
    refresh_screen();
    
    // File size.
    // #bugbug: OUT: 'unsigned long'
    FileSize = (size_t) fsRootDirGetFileSize( (unsigned char *) file_name );
    
    if (FileSize <= 0){
        printf ("sys_read_file_from_disk: File size fail\n");
        refresh_screen();
        return (-1);
    }

    // Limits.
    if ( FileSize < __file->_lbfsize ){ FileSize = __file->_lbfsize; }

    // Limits.
    // Se o arquivo for maior que buffer dispon�vel.
    // Podemos almentar o buffer.
    if (FileSize > __file->_lbfsize)
    {
        // #bugbug: Provisório.
        // Limite - 1MB.
        if (FileSize > 1024*1024){
            printf ("sys_read_file_from_disk: File size out of limits\n");
            printf ("%d bytes \n",FileSize);
            refresh_screen();
            return (-1);
        }
        
        // Allocate new buffer.
        __file->_base = (char *) kmalloc(FileSize);
        
        if ( (void *) __file->_base == NULL ){
            printf ("sys_read_file_from_disk: Couldn't create a new buffer\n");
            refresh_screen();
            return -1;             
        }
 
        // Temos um novo buffer size.
        __file->_lbfsize = (int) FileSize;
    }

    // #paranoia.
    // Checando os limites novamente.
    // #bugbug: Provisório.
    // Limits - 1MB
    if (FileSize > 1024*1024){
        printf ("sys_read_file_from_disk: File size out of limits\n");
        refresh_screen();
        return -1;
    }

    // #paranoia.
    // Checando base novamente.
    if ( (void *) __file->_base == NULL ){
        printf ("sys_read_file_from_disk: buffer fail\n");
        refresh_screen();
        return -1;
    }

   // Pointer.
    __file->_p = __file->_base;
    
    //
    // Load.
    //
    
    // Carrega o arquivo na memória.
 
    Status = (int) fsLoadFile ( 
                       VOLUME1_FAT_ADDRESS, 
                       VOLUME1_ROOTDIR_ADDRESS, 
                       FAT16_ROOT_ENTRIES, //#bugbug: Number of entries.
                       file_name, 
                       (unsigned long) __file->_base,
                       __file->_lbfsize );

    if ( Status != 0 ){
        printf ("sys_read_file_from_disk: fsLoadFile fail\n");
        refresh_screen();
        return -1;
    }

    
    // #bugbug
    // Agora é a hora de atualizarmos as tabelas ....
    // Depois de carregarmos o arquivo.
    
     
    //
    // Pointer. (mode)
    //
    
    // Ajusta o ponteiro para depois do tamanho do arquivo.
    // Dependendo do modo.
    
    // See:
    // https://linux.die.net/man/2/open

           /*
           O_RDONLY        open for reading only
           O_WRONLY        open for writing only
           O_RDWR          open for reading and writing
           O_NONBLOCK      do not block on open or for data to become available
           O_APPEND        append on each write
           O_CREAT         create file if it does not exist
           O_TRUNC         truncate size to 0
           O_EXCL          error if O_CREAT and the file exists
           O_SHLOCK        atomically obtain a shared lock
           O_EXLOCK        atomically obtain an exclusive lock
           O_NOFOLLOW      do not follow symlinks
           O_SYMLINK       allow open of symlinks
           O_FSYNC         write will save into the disk. :)
           */
      
      // Saving into de disk ?
      // You can use the O_FSYNC open mode to make write always 
      // store the data to disk before returning;    
          
          
     // Default ???
       
       
    //if (mode == 0)
    //{
          debug_print ("sys_read_file_from_disk: default mode\n");
          __file->_p = __file->_base;
    //}


    // The file is opened in append mode. 
    // O offset fica no fim do arquivo.
    if ( mode & O_APPEND)        
    { 
        debug_print ("sys_read_file_from_disk: O_APPEND\n");
        //__file->_p = __file->_base + s;
    }

    if ( mode & O_ASYNC )        
    { 
         debug_print ("sys_read_file_from_disk: O_ASYNC\n");
    }

    /* 
    // Enable the close-on-exec flag for the new file descriptor.
    if ( mode & O_CLOEXEC )        
    { 
         debug_print ("sys_read_file: O_CLOEXEC\n");
    }
    */


    if ( mode & O_CREAT )        
    { 
         debug_print ("sys_read_file_from_disk: O_CREAT\n");
    }
        
             
    
    // #importante
    // Se não liberarmos para leitura então read()
    // não poderá ler.
    
    __file->_flags = (__file->_flags | __SRD);
        

    // Salva o ponteiro.  
    // Ja checamos fd.
    p->Objects[__slot] = (unsigned long) __file;


    //printf ("done\n");
    //refresh_screen();

// Done.
// Vamos retornar o fd.
// Pois essa rotina � usada por open();

    debug_print ("sys_read_file_from_disk: done\n");
                  
    return (int) __file->_file;
}

// ==============================
// Service 43
// See: fs_create_empty_file()
int sys_create_empty_file ( char *file_name )
{

    // file *f;

    int __ret = -1;

    // #bugbug: 
    // We need a buffer in another place.

    char buffer[512];
    int size_in_bytes     = 512;
    int number_of_sectors = 1;


    //#todo
    //the file structure.
    // file *f;

    debug_print ("sys_create_empty_file:\n");


    if ( (void*) file_name == NULL ){
        debug_print ("sys_create_empty_file: file_name\n");
        return -1;
    }

    if ( *file_name == 0 ){
        debug_print ("sys_create_empty_file: *file_name\n");
        return -1;
    }


    fs_fntos ( (char *) file_name );

    // 0x20 = file.
    // See: write.c
    __ret = (int) fsSaveFile ( 
                      VOLUME1_FAT_ADDRESS, 
                      VOLUME1_ROOTDIR_ADDRESS, 
                      FAT16_ROOT_ENTRIES,
                      (char *)         file_name,
                      (unsigned long)  number_of_sectors, 
                      (unsigned long)  size_in_bytes,  
                      (char *)         &buffer[0], 
                      (char)           0x20 ); 

    if (__ret<0){
        debug_print("sys_create_empty_file: fail\n");
        return -1;
    }
    
    // #todo
    // the file structure.

    return (int) __ret;
}

// ================================
// Service 44
// See: fs_create_empty_directory
int sys_create_empty_directory ( char *dir_name )
{
    int __ret=0;

    // #bugbug: 
    // We need a buffer in another place.

    char buffer[512];
    int size_in_bytes     = 512; 
    int number_of_sectors = 1;


    debug_print ("sys_create_empty_directory:\n");

    if ( (void*) dir_name == NULL ){
        debug_print ("sys_create_empty_directory: dir_name\n");
        return -1;
    }

    if ( *dir_name == 0 ){
        debug_print ("sys_create_empty_directory: *dir_name\n");
        return -1;
    }

    fs_fntos ( (char *) dir_name );


     // See: write.c
     // 0x10 = directory. 
    __ret = (int) fsSaveFile ( 
                      VOLUME1_FAT_ADDRESS, 
                      VOLUME1_ROOTDIR_ADDRESS, 
                      FAT16_ROOT_ENTRIES,
                      (char *)         dir_name,
                      (unsigned long)  number_of_sectors, 
                      (unsigned long)  size_in_bytes, 
                      (char *)         &buffer[0], 
                      (char)           0x10 ); 

    if (__ret<0){
        debug_print("sys_create_empty_directory: fail\n");
        return -1;
    }

    return (int) __ret;
}


void set_global_open_file ( void *file, int Index )
{

	// #todo:
	// Limite m�ximo da lista.

	// Structure.

    if ( (void *) file == NULL )
    {
        // ?? todo: message
        return;
    }


    if (Index < 0){
        // ?? todo: message
        return;
    }

	// Include pointer in the list.


     file_table[Index] = (unsigned long) file;
}

void *get_global_open_file (int Index){

	//Limits.
	//@todo: max. NUMBER_OF_FILES

    if (Index < 0){
        // ?? todo: message
        return NULL;
    }

    return (void *) file_table[Index];
}

/*
 *****************************
 *  sys_cd_command:
 * 
 */

// Service 175. cd command.

// #todo
// ou usamos o cwd do processo ou
// o diretorio raiz para paths absolutos.

void sys_cd_command ( const char *string )
{
    int i=0;

    if ( (void*) string == NULL ){
        debug_print("sys_cd_command: string\n");
        return;
    }

    if ( *string == 0 ){
        debug_print("sys_cd_command: *string\n");
        return;
    }


    // Reset global structure and cwd on process structure.


    // #bugbug
    // Talvez esse tipo de tratamento precise 
    // ser feito pelo próprio shell.

    if ( string[1] == 0 )
    {

        // $ cd /
        // We also need to clean the name in the process structure.
        if (string[0] == '/'){
            debug_print("sys_cd_command: reseting\n");
            
            //if ( directory_facility_RootDir.initialized == TRUE){
            //    fsInitTargetDir(
            //        directory_facility_RootDir.dir_address,
            //        directory_facility_RootDir.dir_name );
            //}

            fsInitTargetDir(VOLUME1_ROOTDIR_ADDRESS,"/");
            //#bugbug: invalid pid
            //fs_initialize_process_cwd ( current_directory, "/" );
            return;
        }

        // ...

        return;
    }

    // Atualiza na estrutura de processo.
    // Atualiza na estrutura global para diretorio alvo.

    fsUpdateWorkingDiretoryString( (char *) string );

    // Isso carrega o diretorio que agora 'e o diretorio alvo.
    fsLoadFileFromCurrentTargetDir();

    // ...
}


int __load_image( const char *filename, unsigned long image_va )
{
    int Status=-1;
    unsigned long dir_address = VOLUME1_ROOTDIR_ADDRESS;
    unsigned long dir_entries = FAT16_ROOT_ENTRIES;
    char *path;
    char *name;

    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (unsigned long) (512 * 4096);

    // para 32 entradas.
    // ????????
    unsigned long BUGBUG_OVERFLOW = ( 32*128 );


//
// Check parameters for image support
//

    // file_name
    if ( (void*) filename == NULL ){
        panic ("__load_image: [ERROR] filename\n");
    }
    if ( *filename == 0 ){
        panic ("__load_image: [ERROR] *filename\n");
    }
    path = filename;
    name = filename;
    if (path[0] == '.' && path[1] == '/')
    {
        debug_print ("__load_image: [FIXME] Can't execute from cwd \n");
        printf      ("__load_image: [FIXME] Can't execute from cwd \n");
        goto fail;
    }
    
//
// Loop
//

    // Search
    // Convertendo o formato do nome do arquivo.
    // >>> "12345678XYZ"
    // Procura o nome no diretório. 
    // Que em nosso caso ainda é o diretório raiz.

    // Convert and search.
    // Fail if it was not found.

__search:

    fs_fntos ( (char *) name );
    Status = (int) search_in_dir ( name, dir_address );
    if (Status == 1){ 
        goto __found; 
    }

    debug_print ("__load_image: [FAIL] File not found!\n");
    printf      ("__load_image: [FAIL] File not found!\n");
    goto fail;

// The file was found into the directory.
__found:

// ============================

    // [3]
    debug_print ("__load_image: [3] Loading the image.\n");
         printf ("__load_image: [3] Loading the image.\n");


    // Loading from rootdir?

    // >> Load file:
    // #importante: 
    // Carregando a imagem do processo filho.
    // Se o carregamento falhar, temos que abortar a clonagem,
    // caso contrário, executa a cópia da imagem do pai. ??
    // #bugbug: Essa rotina começou a falhar aqui. Convertendo 
    // num formato errado.
    // Movemos essa conversão para o início dessa função,
    // onde checaremos se o arquivo está no diretório.
    // #bugbug
    // Se isso não está funcionando direito e uma thread 
    // defeituosa fica remanescente quando digitamos um 
    // comando errado então vamos matar a thread e o processo.

    // #todo
    // Num ambiente 'mp' precisaremos de um lock aqui.

    //#debug
    //printf ("do_clone_execute_process: %s\n",filename);

    //unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (unsigned long) (512 * 4096);


    if ( dir_address == 0 ){
        panic("__load_image: dir_address\n");
    }

    if ( (void *) image_va == NULL ){
        panic("__load_image: image_va\n");
    }

    Status = (int) fsLoadFile ( 
                       VOLUME1_FAT_ADDRESS, 
                       (unsigned long) dir_address,  //#bugbug: This is only for the root dir.
                       (unsigned long) dir_entries,  //#bugbug: Number of entries. 
                       name, 
                       (unsigned long) image_va,
                       BUGBUG_IMAGE_SIZE_LIMIT );

    return Status;

fail:
    panic("__load_image: fail\n");
    return -1;
}



//
// End.
//



















































































