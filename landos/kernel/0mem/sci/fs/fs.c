

#include <kernel.h>



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







