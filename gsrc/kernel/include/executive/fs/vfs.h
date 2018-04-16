
//vfs.h 

// header do gerenciador de sistema de arquivos virtual.
// O vfs é uma abstração que uniformiza o acesso aos arquivos ...


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


//
// O sistema de arquivos virtual sendo tratado como se fosse 
// apenas um diretório comum, mas que não está em nenhum disco.
// e as entradas terão estruturas que lidam com streams.
//

// O diretório raiz será montado nesse endereço.
struct dir_d *vfs;  


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
	//vaildando a estrutura.
	int used;
	int magic;
	
	//Qual o status do vfs.
	//não queremos que alguma parte do sistema 
	//começe usá-lo antes de estar devidamente montado.
	int Status;
	
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
	
		
    // diretório raiz.    
    struct dir_d *vfs;  	
};



