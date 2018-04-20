
//vfs.h 

// header do gerenciador de sistema de arquivos virtual.
// O vfs é uma abstração que uniformiza o acesso aos arquivos ...
// serão usadas as estruturas de 'directory entry' e 'inode' do ext2. 
// 


#define VHS_DIR_ROOT  '/root'  
#define VHS_DIR_BOOT  '/root/boot' // boot files
#define VHS_DIR_BIN   '/root/bin'  // binary programs.
#define VHS_DIR_DEV   '/root/dev'  // i/o devices.
#define VHS_DIR_ETC   '/root/etc'  // misc
#define VHS_DIR_LIB   '/root/lib'  // libraries
#define VHS_DIR_OBJECTS   '/root/objects'  // gerenciador de objetos.
#define VHS_DIR_TMP   '/root/tmp'  // tmp
#define VHS_DIR_USER  '/root/user' // users
#define VHS_DIR_DEFAULTUSER  '/root/user/default' // default user
//...  

// Ex: 
//
// /root
// /root/bin
// /root/user/fred
// /root/dev/hd0
//
//



#define EXT2_NAME_LEN 255
#define VFS_NAME_LEN 255


/*
 *********************************************************************
 * The new version of the directory entry.  Since EXT2 structures are
 * stored in intel byte order, and the name_len field could never be
 * bigger than 255 chars, it's safe to reclaim the extra byte for the
 * file_type field.
 */
typedef struct ext2_dir_entry_d ext2_dir_entry_t;
struct ext2_dir_entry_d 
{
	unsigned int   inode;     /* Inode number */
	unsigned short rec_len;   /* Directory entry length */
	unsigned char  name_len;  /* Name length */
	unsigned char  file_type;
	char           name[EXT2_NAME_LEN];    /* File name, up to EXT2_NAME_LEN */
};

#define ext2_dir_entry_d vfs_dir_entry_d
#define ext2_dir_entry_t vfs_dir_entry_t


#define VFS_MAX_ENTRIES 512

unsigned long directory_entry_list[VFS_MAX_ENTRIES];


/*
 *********************************************************************
 * Structure of an inode on the disk
 */
 
typedef struct ext2_inode_d ext2_inode_t;
struct ext2_inode_d 
{
	unsigned short i_mode;        /* File mode */
	
	/* Use 0 as the user id for the assignment. */
	unsigned short i_uid;         /* Low 16 bits of Owner Uid */
	
	unsigned int   i_size;        /* Size in bytes */
	
	/* You don't need to set access time for the assignment. */
	unsigned int   i_atime;       /* Access time */
	
	unsigned int   i_ctime;       /* Creation time */
	
	/* You don't need to set modification time for the assignment. */
	unsigned int   i_mtime;       /* Modification time */
	
	/* d_time must be set when appropriate */
	unsigned int   i_dtime;       /* Deletion Time */
	
	/* Use 0 as the group id for the assignment. */
	unsigned short i_gid;         /* Low 16 bits of Group Id */
	
	unsigned short i_links_count; /* Links count */
	
	unsigned int   i_blocks;      /* Blocks count IN DISK SECTORS*/
	
	/* You can ignore flags for the assignment. */
	unsigned int   i_flags;       /* File flags */
	
	/* You should set it to 0. */
	unsigned int   osd1;          /* OS dependent 1 */
	
	unsigned int   i_block[15];   /* Pointers to blocks */
	
	/* You should use generation number 0 for the assignment. */
	unsigned int   i_generation;  /* File version (for NFS) */
	
	/* The following fields should be 0 for the assignment.  */
	unsigned int   i_file_acl;    /* File ACL */
	unsigned int   i_dir_acl;     /* Directory ACL */
	unsigned int   i_faddr;       /* Fragment address */
	unsigned int   extra[3];
};

#define ext2_inode_d vfs_inode_d 
#define ext2_inode_t vfs_inode_t



#define VFS_MAX_INODES 512

unsigned long inode_list[VFS_MAX_INODES];

//
// SOBRE OS TIPOS DE ARQUIVOS:
// PODEMOS LEVAR EM CONSIDERAÇÃO OS TIPOS DE OBJETOS USADOS EM GRAMADO.
// 


typedef enum {
	VFSStatusNull,
	VFSStatusInitialized,
	VFSStatusLocked,
    //...	
}vfs_status_t;





//
// estrutura da token que o processo precisa ter
// para acessar o vfs.
// a token vai indicar quais as permissões de acesso 
// que o processo tem.
//
typedef struct vfs_token_d vfs_token_t;
struct vfs_token_d
{
	int used;
	int magic;
	
	int type;
	
	struct process_d *process;
	
	// ...
	
};


//
// vfs info
//

typedef struct vfs_info_d vfs_info_t;
struct vfs_info_d
{
	//@todo:
	//object support.
	
	
	//vaildando a estrutura.
	int used;
	int magic;
	
	//Qual o status do vfs.
	//não queremos que alguma parte do sistema 
	//começe usá-lo antes de estar devidamente montado.
	vfs_status_t status;
	
	//Nome amigável do sistema de arquivos virtual.
    char *name;
	
	//string com descrição sobre o vfs.
	char *description;
	
	//Uma string que explique para o desenvolvedor 
	//ou para o usuário o funcionamento de um sistema de arquivos virtual.
	//e exple fundamentos da navegação nos diretórios.
	char *help_string;
	
	//um arquivo de informações sobre o vfs.
	//FILE *vfs_info_file;

    //
	// Um dos discos será o disco do sistema.
	// Esse disco vai ter duas partições principais,
	// uma delas é a partição de boot e a outra é a 
	// partição do sistema, onde fica o sistema operacional.
	//
	
	//
	// @todo
	// ponteiro para informações sobre o disco do sistema.
	// onde ficam a partição de boot e o sistema operacional.
	//struct disk_d *system_disk;
	
	//informações sobre a partição de boot.
	//struct volume_d *boot_volume;	
	
	//informações sobre o volume do sistema
	// onde fica o sistema operacional.
	//struct volume_d *system_volume;	
	
	//int number_of_volumes;
	
	//obs: temos lista de discos e lista de volumes.
	
	
	//
	// permissões ...
	//
	
	//@todo:

	
	//...
	
	
	//unsigned long filesList[?];
	
		
    // diretório raiz.    
    struct dir_d *vfs;  	
};

//Assim mesmo sem ponteiro.
struct vfs_info_d VFS_INFO;

//
// O sistema de arquivos virtual sendo tratado como se fosse 
// apenas um diretório comum, mas que não está em nenhum disco.
// e as entradas terão estruturas que lidam com streams.
//

// O diretório raiz será montado nesse endereço.
struct dir_d *vfs;  



void vfsInit();
