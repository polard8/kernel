/*
 * File: fs/vfs.c
 *
 *     Virtual File System
 *     Sistema de arquivos virtual gerenciado pelo kernel base.
 *
 *    2018 - Created by Fred Nora.
 */


#include <kernel.h>


/*
 *********************************************
 * vfsInit:
 *     Initializing VFS.
 */

int vfsInit (void)
{
    int i=0;
    int slot = -1;
    size_t Size=0;

    debug_print ("vfsInit: [FIXME]\n");

    // Inicializando a estrutura do VFS.

#ifdef KERNEL_VERBOSE
    printf("Initilizing VFS..\n");
#endif

    if ( (void*) storage == NULL ){
        panic ("vfsInit: [FAIL] storage\n");
    }


    // storage->vfs 

    storage->vfs = kmalloc ( sizeof(struct vfs_d) );

    if ( (void *) storage->vfs == NULL ){
        panic ("vfsInit: [FAIL] storage->vfs\n");
    }else{
        // todo: object 
        
        storage->vfs->used = 1;
        storage->vfs->magic = 1234;

        storage->vfs->status = VFSStatusInitialized;
        storage->vfs->name        = "VFS Name";
        storage->vfs->description = "Virtual File System";
        storage->vfs->help_string = "[TODO] VFS help string";

        // root dir address
        
        Size = (size_t) ( VFS_ROOTDIR_NUMBER_OF_ENTRIES * VFS_ROOTDIR_ENTRY_SIZE );
        
        if ( Size <= 0 )
            panic ("vfsInit: Size\n");
            
        storage->vfs->rootdir_address = (unsigned long) kmalloc(Size);

        if ( (void *) storage->vfs->rootdir_address == NULL )
        {
            panic ("vfsInit: storage->vfs->rootdir_address\n");
        }
 
        // ...
    };

	//
	// file ?
	//

    // vfs foi definido em stdio.h

    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if (slot<0 || slot >= NUMBER_OF_FILES)
    {
        panic ("vfsInit: No more file slots\n");
    }


    // vfs ??
    // Is it a file structure ?

    vfs = file_table[slot];

    if ( (void*) vfs == NULL )
    {
        panic ("vfsInit: [FAIL] vfs\n");
    }

    
    vfs->filetable_index = slot;

    // #bugbug: 
    // Não usar o termo 'stream'.
    
    storage->vfs->_file = vfs;

    vfs->used = 1;
    vfs->magic = 1234;
    vfs->____object = ObjectTypeFileSystem;

    // sync 

    // Can not read/write a file like this.
    vfs->sync.can_read = FALSE;
    vfs->sync.can_write = FALSE;
    vfs->sync.can_execute = FALSE;

    vfs->sync.can_accept = FALSE; 
    vfs->sync.can_connect = FALSE;

    // buffer.
    
    // Why we need a buffer?
    // The buffer is the directory itself.

    vfs->_base = (unsigned char *) storage->vfs->rootdir_address;
    vfs->_p = vfs->_base;

    vfs->_cnt = Size;
    //vfs->_cnt = ( VFS_ROOTDIR_NUMBER_OF_ENTRIES * VFS_ROOTDIR_ENTRY_SIZE );
        

    // #todo:
    // This is gonna be the fd when 
    // some process opening the file system.

    vfs->_file = -1;


    vfs->_tmpfname = "VFS1    VFS";
    vfs->fd_counter =1;
  
    // ...
    // inode support.
    // pega slot em inode_table[] 

    slot = get_free_slots_in_the_inode_table();
    if (slot<0 || slot >=32)
    {
        panic ("vfsInit: No more inode slots\n");
    }
    
    // inode.
    
    vfs->inode = inode_table[slot];
    vfs->inodetable_index = slot;
    
    if ( (void*) vfs->inode == NULL )
    {
        panic ("vfsInit: inode struct \n");
    }
    vfs->inode->filestruct_counter = 1;  //inicialize
    
    // copy name.
    memcpy ( 
        (void*)        vfs->inode->path, 
        (const void*)  vfs->_tmpfname, 
        sizeof( vfs->inode->path ) );
        
    // ... 

    // #bugbug
    // Selecionando o primeiro diretório,
    // que deve ser o volume do vfs
    
    current_directory = 0;


	// #importante
	// É possivel fazer mais inicializações.


#ifdef KERNEL_VERBOSE
    printf("VFS Initialized\n");
#endif

    debug_print("vfsInit: done\n");

    // ok
    return 0;
}



/*
 *******************************************
 * vfs_show_handle_list:
 *     Mostrar os elementos da lista de handles do VFS. 
 */

void vfs_show_handle_list (void)
{

/*
    int i=0;
    struct vfs_handle_d *h;


	printf("vfs_show_handle_list:\n\n");
	
	for ( i=0; i<VFS_HANDLE_MAX; i++ )
	{
		h = (void *) vfs_handle_list[i];
		
		if ( (void *) h != NULL )
        {
			if ( h->used ==  1 && h->magic == 1234 ){
				
				//#bugbug Cuidado.
		        //printf("%d = { %s }\n", h->id, h->name );		
			}
		}			
	};
*/

    printf("vfs_show_handle_list: [FIXME] use file_table[]\n");
	refresh_screen();
}


/*
 ***********************************
 * vfsShowVFSInfo:
 *     Monstrando informações sobre VFS.
 */
void vfsShowVFSInfo (void)
{

	/*
	
	int i;
	
	//#bugbug
	//@todo: Checar a validade da estrutura antes

	// Informações sobre a estrutura do sistema de arquivos.
	
	printf("\nfs-vfsShowVFSInfo:\n\n");	
	
	printf("VFS INFO:\n");
	
	printf("used={%d} magic={%d} ", VFS_INFO.used, VFS_INFO.magic);	
	printf("Status={%d} ", VFS_INFO.status);
	printf("name={%s} ", VFS_INFO.name);
	printf("description={%s} ", VFS_INFO.description);
	printf("helpString={%s} ", VFS_INFO.help_string);
	//printf("name={%x}\n",           VFS_INFO.vfs); 
    //...

	struct vfs_handle_d *Handle;	
	struct ext2_dir_entry_d *Entry;
	struct ext2_inode_d *INode;
	
	// Lista de handles 
	// manipuladores de arquivos presentes no diretório raiz do vfs.

	printf("VFS handles:\n");
	
	for ( i=0; i<VFS_HANDLE_MAX; i++)
	{
		Handle = (struct vfs_handle_d *) vfs_handle_list[i]; 
		
		if ( Handle != NULL )
		{
			printf("%d %d %d %d ", Handle->id, Handle->used, Handle->magic, Handle->status );
		    printf("dirEntry={%x}\n",Handle->directory_entry );
		}
	};		
	
    // Lista de entradas de diretório 

	printf("VFS ext2 entries:\n");
	
	for ( i=0; i<VFS_MAX_ENTRIES; i++)
	{
        Entry = (struct ext2_dir_entry_d *) directory_entry_list[i];
		
		if ( Entry != NULL )
		{
			//#bugbug Cuidado com o nome. #PF
			printf("inode={%d} dlen={%d} nlen={%d} fileType={%d} name={%s}\n", 
			    Entry->inode, 
				Entry->rec_len, 
				Entry->name_len, 
				Entry->file_type, 
				Entry->name );
		}

	};
	
	// Lista de inodes.

	printf("VFS ext2 inodes:\n");
	
	for ( i=0; i<VFS_MAX_INODES; i++)
	{
		INode = (struct ext2_inode_d *) inode_list[i];
		
		if ( INode != NULL )
		{
			printf("%d %d %d %d ", INode->i_mode, 
			    INode->i_uid, INode->i_size, INode->i_atime );
									
		    printf("%d %d %d %d ", INode->i_ctime, 
			    INode->i_mtime, INode->i_dtime, INode->i_gid );
									
			printf("%d %d %d %d ", INode->i_links_count, 
			    INode->i_blocks, INode->i_flags, INode->osd1 );
									
			printf("gen={%d} facl={%x} dacl={%x} fadd={%x}\n", 
			    INode->i_generation, INode->i_file_acl, 
				INode->i_dir_acl, INode->i_faddr );
			
			//...
		}
		
		//Nothing.
	};	
	
	*/
	
//done:	
   // printf("done\n");	
	//refresh_screen();
	//return;
}


//lista os nomes dos arquivos no diretório raiz do vfs.
void vfsListFiles (void)
{

/*
    int i;
    struct ext2_dir_entry_d *Entry;



	printf("\n");
	
	for ( i=0; i<VFS_MAX_ENTRIES; i++ )
	{
        Entry = (struct ext2_dir_entry_d *) directory_entry_list[i];
		
		if ( Entry != NULL ){
			
			printf ("inode={%d} fileType={%d} name={%s}\n", 
			    Entry->inode, Entry->file_type, (const char*) Entry->name );
		}
	};
*/

    printf ("vfsListFile: [FIXME] use file_table[]\n");
    
    refresh_screen();
}


/*
int vfs_root_mounted(void);
int vfs_root_mounted(void)
{
    return (root)?1:0;
}
*/


//
// End.
//

