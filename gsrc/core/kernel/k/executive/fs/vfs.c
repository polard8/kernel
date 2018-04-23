/*
 * File: fs\vfs.c
 *     Virtual File System
 *     Sistema de arquivos virtual gerenciado pelo kernel base.
 */


#include <kernel.h>



/*
 * vfsInit:
 *     Initializing VFS.
 *
 */
void vfsInit()
{
	int i;
	
	//
	// Inicializando a estrutura do VFS.
	//

#ifdef KERNEL_VERBOSE	
	printf("Initilizing VFS ... \n");
#endif	
	
	//Nosso objetivo é que tenha apenas uma estrutura 
	//para o VFS.
	
	//@todo: object stuff
	
	VFS_INFO.used = 1;
	VFS_INFO.magic = 1234;
	
	VFS_INFO.status = VFSStatusInitialized;
	
	VFS_INFO.name = "VFS NAME";
	VFS_INFO.description = "VIRTUAL FILE SYSTEM";
	VFS_INFO.help_string = "Virtual File System help string @todo.";
	VFS_INFO.vfs = NULL;  //Nenhum diretório aqui.
	
	//...
	
	
#ifdef KERNEL_VERBOSE	
	printf("Initilizing VFS lists ...\n");	
#endif	
	
	//
	// Inicializando a lista de handles usada pelo vfs.
	//
	
	for( i=0; i<VFS_HANDLE_MAX; i++){
		vfs_handle_list[i] = (unsigned long) 0;
	}

	
	//
	// Inicializando a lista de entradas de diretório usada pelo vfs.
	//
	
	for( i=0; i<VFS_MAX_ENTRIES; i++){
		directory_entry_list[i] = (unsigned long) 0;
	}
	
	
	
	//
	// Inicializando a lista de inodes usada pelo vfs.
	//
	
	for( i=0; i<VFS_MAX_INODES; i++){
		inode_list[i] = (unsigned long) 0;
	}
	
	
	//
	// Primeira entrada.
	//
	
	//
	// montando as três lista de objetos. 
	// /objectskm /objectsum /objectsgui
	//
	

	// inode 0.
	struct ext2_inode_d *i0;
	
	i0 = (void*) malloc( sizeof(struct ext2_inode_d) );
	if( (void*) i0 == NULL ){
		printf("fs-vfs-vfsInit: i0 fail");
		die();
	}else{
		
		
		i0->i_mode = 0;
		i0->i_uid = 0;
		i0->i_size = 0;
		i0->i_atime = 0;
		i0->i_ctime = 0;
		i0->i_mtime = 0;
		i0->i_dtime = 0;
		i0->i_gid = 0;
		i0->i_links_count = 0;
		i0->i_blocks = 0;
		i0->i_flags = 0;
		i0->osd1 = 0;
		//i0->i_block[15]
		i0->i_generation = 0;
		i0->i_file_acl = 0;
		i0->i_dir_acl = 0;
		i0->i_faddr = 0;
		//i0->extra[3]
		
		//...

    };	

	
	
	//directory entry 0.
	struct ext2_dir_entry_d *e0;
	
	e0 = (void*) malloc( sizeof( struct ext2_dir_entry_d ) );
	if( (void*) e0 == NULL ){
		printf("fs-vfs-vfsInit: e0 fail");
		die();
	}else{
		
		e0->inode = 0;
        e0->rec_len = 0;
        e0->name_len = 0;
        e0->file_type = 0;
        //e0->name[EXT2_NAME_LEN];
		
    };	
    
	
	// vfs handle 0.
	struct vfs_handle_d *h0;
	
	h0 = (void*) malloc( sizeof( struct vfs_handle_d ) );
	if( (void*) h0 == NULL ){
		printf("fs-vfs-vfsInit: h0 fail");
		die();
	}else{
	    
        h0->id = 0;		
		
		h0->used = 1;
		h0->magic = 1234;
		
		h0->status = 1;
		
		h0->name = "Kernel Mode Objects";
		
		//
		//h0->directory_entry = (struct ext2_dir_entry_d *) e0;
	};
	
	
	
	

	// inode 1.
	struct ext2_inode_d *i1;
	
	i1 = (void*) malloc( sizeof(struct ext2_inode_d) );
	if( (void*) i1 == NULL ){
		printf("fs-vfs-vfsInit: i1 fail");
		die();
	}else{
		
		
		i1->i_mode = 0;
		i1->i_uid = 0;
		i1->i_size = 0;
		i1->i_atime = 0;
		i1->i_ctime = 0;
		i1->i_mtime = 0;
		i1->i_dtime = 0;
		i1->i_gid = 0;
		i1->i_links_count = 0;
		i1->i_blocks = 0;
		i1->i_flags = 0;
		i1->osd1 = 0;
		//i1->i_block[15]
		i1->i_generation = 0;
		i1->i_file_acl = 0;
		i1->i_dir_acl = 0;
		i1->i_faddr = 0;
		//i1->extra[3]
		
		//...

    };	

	
	
	//directory entry 1.
	struct ext2_dir_entry_d *e1;
	
	e1 = (void*) malloc( sizeof( struct ext2_dir_entry_d ) );
	if( (void*) e1 == NULL ){
		printf("fs-vfs-vfsInit: e1 fail");
		die();
	}else{
		
		e1->inode = 0;
        e1->rec_len = 0;
        e1->name_len = 0;
        e1->file_type = 0;
        //e1->name[EXT2_NAME_LEN];
		
    };	
    
	
	// vfs handle 1.
	struct vfs_handle_d *h1;
	
	h1 = (void*) malloc( sizeof( struct vfs_handle_d ) );
	if( (void*) h1 == NULL ){
		printf("fs-vfs-vfsInit: h1 fail");
		die();
	}else{
	    
        h1->id = 0;		
		
		h1->used = 1;
		h1->magic = 1234;
		
		h1->status = 1;
		
		h1->name = "User Mode Objects";
		
		//
		//h1->directory_entry = (struct ext2_dir_entry_d *) e0;
	};
		
	
	
	
	// inode 2.
	struct ext2_inode_d *i2;
	
	i2 = (void*) malloc( sizeof(struct ext2_inode_d) );
	if( (void*) i2 == NULL ){
		printf("fs-vfs-vfsInit: i2 fail");
		die();
	}else{
		
		
		i2->i_mode = 0;
		i2->i_uid = 0;
		i2->i_size = 0;
		i2->i_atime = 0;
		i2->i_ctime = 0;
		i2->i_mtime = 0;
		i2->i_dtime = 0;
		i2->i_gid = 0;
		i2->i_links_count = 0;
		i2->i_blocks = 0;
		i2->i_flags = 0;
		i2->osd1 = 0;
		//i2->i_block[15]
		i2->i_generation = 0;
		i2->i_file_acl = 0;
		i2->i_dir_acl = 0;
		i2->i_faddr = 0;
		//i2->extra[3]
		
		//...

    };	

	
	
	//directory entry 2.
	struct ext2_dir_entry_d *e2;
	
	e2 = (void*) malloc( sizeof( struct ext2_dir_entry_d ) );
	if( (void*) e2 == NULL ){
		printf("fs-vfs-vfsInit: e2 fail");
		die();
	}else{
		
		e2->inode = 0;
        e2->rec_len = 0;
        e2->name_len = 0;
        e2->file_type = 0;
        //e2->name[EXT2_NAME_LEN];
		
    };	
    
	
	// vfs handle 2.
	struct vfs_handle_d *h2;
	
	h2 = (void*) malloc( sizeof( struct vfs_handle_d ) );
	if( (void*) h2 == NULL ){
		printf("fs-vfs-vfsInit: h2 fail");
		die();
	}else{
	    
        h2->id = 0;		
		
		h2->used = 1;
		h2->magic = 1234;
		
		h2->status = 1;
		
		h2->name = "GUI Objects";
		
		//
		//h2->directory_entry = (struct ext2_dir_entry_d *) e0;
	};
		
		
	
	// Colocando as três listas de objetos na lista de handles do vfs.
	vfs_handle_list[0] = (unsigned long) &objects_km[0];
	vfs_handle_list[1] = (unsigned long) &objects_um[0];
	vfs_handle_list[2] = (unsigned long) &objects_gui[0];
	
	
	
	
	//
	// Disco do sistema.
	//
	
	

	
	// inode.
	struct ext2_inode_d *system_disk_inode;
	
	system_disk_inode = (void*) malloc( sizeof(struct ext2_inode_d) );
	if( (void*) system_disk_inode == NULL ){
		printf("fs-vfs-vfsInit: system_disk_inode fail");
		die();
	}else{
		
		
		system_disk_inode->i_mode = 0;
		system_disk_inode->i_uid = 0;
		system_disk_inode->i_size = 0;
		system_disk_inode->i_atime = 0;
		system_disk_inode->i_ctime = 0;
		system_disk_inode->i_mtime = 0;
		system_disk_inode->i_dtime = 0;
		system_disk_inode->i_gid = 0;
		system_disk_inode->i_links_count = 0;
		system_disk_inode->i_blocks = 0;
		system_disk_inode->i_flags = 0;
		system_disk_inode->osd1 = 0;
		//system_disk_inode->i_block[15]
		system_disk_inode->i_generation = 0;
		system_disk_inode->i_file_acl = 0;
		system_disk_inode->i_dir_acl = 0;
		system_disk_inode->i_faddr = 0;
		//system_disk_inode->extra[3]
		
		//...

    };	

	
	
	//directory entry 2.
	struct ext2_dir_entry_d *system_disk_directory_entry;
	
	system_disk_directory_entry = (void*) malloc( sizeof( struct ext2_dir_entry_d ) );
	if( (void*) system_disk_directory_entry == NULL ){
		printf("fs-vfs-vfsInit: system_disk_directory_entry fail");
		die();
	}else{
		
		system_disk_directory_entry->inode = 0;
        system_disk_directory_entry->rec_len = 0;
        system_disk_directory_entry->name_len = 0;
        system_disk_directory_entry->file_type = 0;
        //system_disk_directory_entry->name[EXT2_NAME_LEN];
		
    };	
    
	
	// vfs handle 2.
	struct vfs_handle_d *system_disk_vfs_handle;
	
	system_disk_vfs_handle = (void*) malloc( sizeof( struct vfs_handle_d ) );
	if( (void*) system_disk_vfs_handle == NULL ){
		printf("fs-vfs-vfsInit: system_disk_vfs_handle fail");
		die();
	}else{
	    
        system_disk_vfs_handle->id = 0;		
		
		system_disk_vfs_handle->used = 1;
		system_disk_vfs_handle->magic = 1234;
		
		system_disk_vfs_handle->status = 1;
		
		system_disk_vfs_handle->name = "System Disk";
		
		//
		//system_disk_vfs_handle->directory_entry = (struct ext2_dir_entry_d *) e0;
	};
		
	

	//
	// #importante
	// É possivel fazer mais inicializações.
	//
	
#ifdef KERNEL_VERBOSE
	printf("VFS Initialized!\n");
#endif	
	
	return;
};


/*
 * vfs_show_handle_list:
 *     Mostrar os elementos da lista de handles do VFS. 
 */
void vfs_show_handle_list()
{
	int i;
	struct vfs_handle_d *h;
	
	printf("vfs_show_handle_list:\n\n");
	
	for( i=0; i<VFS_HANDLE_MAX; i++ )
	{
		h = (void*) vfs_handle_list[i];
		
		if( (void*) h != NULL )
        {
			if( h->used ==  1 && h->magic == 1234 ){
		        printf("%d = { %s }\n", h->id, h->name );		
			}
		}			
	};
	
	refresh_screen();
	return;
};



