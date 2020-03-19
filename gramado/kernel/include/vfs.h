
//vfs.h 

// header do gerenciador de sistema de arquivos virtual.
// O vfs é uma abstração que uniformiza o acesso aos arquivos ...
// serão usadas as estruturas de 'directory entry' e 'inode' do ext2. 
// 


#ifndef ____VFS_H
#define ____VFS_H



//
//  ## VFS SUPPORT  ##
//

//
// O VFS só tem o diretótio raiz, nada mais.
// Seu endereço será alocado dinamicamente.
// Suas entradas serão construidas seguindo o padrão fat,
// Suas entradas apontaram para objetos, principalmetne streams.
//

#define VFS_ROOTDIR_NUMBER_OF_ENTRIES 128
#define VFS_ROOTDIR_ENTRY_SIZE 32 


#define VHS_DIR_ROOT         'root:' 
#define VHS_DIR_ETC          'root:/etc'  // misc
#define VHS_DIR_OBJECTS      'root:/objects'  // gerenciador de objetos.
#define VHS_DIR_TMP          'root:/tmp'      // tmp 
//...




// Ex: 
//
// /root
// /root/bin
// /root/user/fred
// /root/dev/hd0
//
//


// a entrada '/objects' vai apontar para a lista de ponteiros 
// para estruturas de objetos gerenciados pelo obect manager,
// podendo até mesmo abrir o object manager.
// essa entrada ligará a lista de objetos ao vfs.
// essa deve ser a primeira entrada e será montada logo na 
// inicialização do vfs.
// inclusive o vfs pode chamar a rotina de inicializaçao do object manager.
// incluive a sequência de montagem do vfs promoverá um pouco mais 
// de ordem na inicialização.
// mas o vfs não precisa montar a lista de objetos no object manager.
// somente ligar a lista de objetops ao vfs, sinalizando como não 
// inicializada.  
//



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




#define VFS_MAX_INODES 512

unsigned long inode_list[VFS_MAX_INODES];



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



#define VFS_MAX_ENTRIES 512

unsigned long directory_entry_list[VFS_MAX_ENTRIES];

/*****************************************************************/
#define VFS_HANDLE_MAX 512


// manipulador das entradas de diretório do vfs.
// Essa estrutura existe para termos informações extras 
// além das poucas oferecidadas por uma entrada de ext2 padrão.
typedef struct vfs_handle_d vfs_handle_t;
struct vfs_handle_d
{
	//id do handle.
    int id;

    int used;
    int magic;  //

	int status;
	

	// Nome do handle e não o nome do arquivo.
    // Isso servirá para efeito de exibução.
	//poderá ter quanquer tamanho.
    char *name;
	
	//Posso colocar aqui os identificadores 
	//de minha preferência.
	
	//Continua ...
	//...
	
	struct ext2_dir_entry_d *directory_entry; 	
};

unsigned long vfs_handle_list[VFS_HANDLE_MAX];




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
// vfs 
//

struct vfs_d
{
	//@todo:
	//object support.
	
	
	//vaildando a estrutura.
	int used;
	int magic;
	
	FILE *stream;
	
	//int file_descriptor; //3
	
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
	
	unsigned long rootdir_address;
	
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
    //struct dir_d *vfs;  	
}; 


void vfsInit (void);
void vfs_show_handle_list (void);
void vfsShowVFSInfo (void);
void vfsListFiles (void);



#endif    


