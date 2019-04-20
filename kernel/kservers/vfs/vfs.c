/*
 * File: fs\vfs.c
 *
 *     Virtual File System
 *     Sistema de arquivos virtual gerenciado pelo kernel base.
 *
 * 2018 - Created by Fred Nora.
 */


#include <kernel.h>


/*
 * vfsInit:
 *     Initializing VFS.
 *     #todo: esse retorno tem que ser int.
 */
 
//int vfsInit (){ 

void vfsInit (void){
	
	int i;
	
	// Inicializando a estrutura do VFS.

#ifdef KERNEL_VERBOSE	
	printf("Initilizing VFS..\n");
#endif	
	
	storage->vfs = malloc ( sizeof(struct vfs_d) );
	
	if ( (void *) storage->vfs == NULL )
	{
		panic ("vfsInit: storage->vfs");
	}else{
		
		
	    storage->vfs->used = 1;
	    storage->vfs->magic = 1234;
	
	    storage->vfs->status = VFSStatusInitialized;
	    storage->vfs->name = "VFS NAME";
	    storage->vfs->description = "VIRTUAL FILE SYSTEM";
	    storage->vfs->help_string = "Virtual File System help string @todo";
	
	    // ## root dir address  ##
	    storage->vfs->rootdir_address = (unsigned long) malloc ( VFS_ROOTDIR_NUMBER_OF_ENTRIES * VFS_ROOTDIR_ENTRY_SIZE );
	
	    if ( storage->vfs->rootdir_address = 0 ){
		
	        panic ("vfsInit: storage->vfs->rootdir_address\n");	
	    }
		
	
	};	
	
	//
	// ## STREAM ##
	//
	
	//foi definido em stdio.h
	//FILE *vfs;
	
	vfs = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) vfs == NULL )
	{
		panic ("vfsInit: vfs fail");
	}else{
		
        storage->vfs->stream = vfs;			
		
	    //#bugbug:
	    //#todo:
	    //Checar antes a validade dessa estrutura.
	
	    vfs->_base = (char *) storage->vfs->rootdir_address;
	    vfs->_ptr = stdin->_base;
	    vfs->_cnt = ( VFS_ROOTDIR_NUMBER_OF_ENTRIES * VFS_ROOTDIR_ENTRY_SIZE );
	    vfs->_file = 0; //?
	    vfs->_tmpfname = "vfs-stream";
	
	    Streams[3] = (unsigned long) vfs;
	};
	

	//  selecionando o primeiro diretório,
	// que deve ser o volume do vfs
	current_directory = 0;
	
	// #importante
	// É possivel fazer mais inicializações.
	
#ifdef KERNEL_VERBOSE
	printf("VFS Initialized\n");
#endif	
	
};


/*
 *******************************************
 * vfs_show_handle_list:
 *     Mostrar os elementos da lista de handles do VFS. 
 */

void vfs_show_handle_list (void){
	
	int i;
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
	
	refresh_screen();
};


/*
 ***********************************
 * vfsShowVFSInfo:
 *     Monstrando informações sobre VFS.
 */
void vfsShowVFSInfo (void){
	
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
};


//lista os nomes dos arquivos no diretório raiz do vfs.
void vfsListFiles (void){
	
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
	
	refresh_screen();
}

//
// End.
//

