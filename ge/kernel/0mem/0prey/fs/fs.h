/*
 * File: fs.h
 * 
 * 
 * 2015 - Created by Fred Nora.
 */


#ifndef ____FS_H
#define ____FS_H


// #order:
// defines, variables, structures, prototypes.


//
//    ====    Defines    ====
//


// Filesystem types.
#define  FS_TYPE_NULL   0
#define  FS_TYPE_GVFS   1000  // Gramado Virtual File System.
#define  FS_TYPE_VFS    1001
#define  FS_TYPE_FAT12  1002 
#define  FS_TYPE_FAT16  1003 
#define  FS_TYPE_FAT32  1004 
#define  FS_TYPE_EXT2   1005
// No more types. 



// deveria is para disk.h
#define SECTOR_SIZE    512  
//#define SECTOR_SIZE  4096  



//#define MBR_BOOTABLE        0x80
//#define MBR_SIGNATURE       0xAA55




// short.
//#define FS_I386_IMAGE  0x014C



// pwd support
#define  FS_VFSWORKINGDIRECTORY_ID      0
#define  FS_BOOTWORKINGDIRECTORY_ID     1
#define  FS_SYSTEMWORKINGDIRECTORY_ID   2
#define  FS_UNKNOWNWORKINGDIRECTORY_ID  (-1)



#define CACHE_SAVED        1
#define CACHE_NOT_SAVED    0

#define CACHE_LOADED        1
#define CACHE_NOT_LOADED    0


//
//  == Variables =================================
//


// Boot partition.
int fat_cache_saved;
int fat_cache_loaded;


// gcc -Wall Defined but not used!
static char *____root_name = "/";


//
// pwd
//


// A string do diretório de trabalho.
char current_workingdiretory_string[WORKINGDIRECTORY_STRING_MAX];
int pwd_initialized;


//
// == Search path ================================
//

// See:
// https://en.wikipedia.org/wiki/PATH_(variable)
// ...

// #importante
// + Quando uma função para eecutar uma programa é chamada
// o kernel deve tomar suas decisões sobre qual diretório
// procurar. Não é seguro obedecer o search path indicado pelo
// processo que chamou a função.
// Então o kernel pode começar procurando em /BIN/ e /USER/BIN/.
// O kernel só vai procurar no cwd se o pathname desejado começar
// explicitamente com "./". 


// Multics originated the idea of a search path. 
// The early Unix shell only looked for program names in /bin, 
// but by Version 3 Unix the directory was too large and /usr/bin, 
// and a search path, became part of the operating system.


//char search_path[?];
unsigned long search_path_dir_address;
unsigned long search_path_dir_entries;





// ?? - Contagem de diretórios.
//int dirCount;  


// List of clusters. 
// Usado na rotina de carregamento de arquivo.
unsigned short file_cluster_list[1024]; 




//
// == Structures ====================================
//


/*
 * 
 * Obs: Dentro do kernel base somente teremos primitivas
 *      Operações complexas devem ir para servidores utilitários.
 *
 * Descrição:
 *     Header para o File System Manager. (FSM)
 *     File system header for kernel file management.
 *     Inicialmente suporte ao sistema de arquivos FAT16.
 *     Posteriormente suporte aos sistemas FAT12, FAT32, EXT2.     
 *
 * History:
 *     2014 - Created by Fred Nora.
 */

//suporte ao diretório alvo que desejamos acessar.
//com base em um pathname passado via argumento.

struct target_dir_d
{
    int used;
    int magic;

	//ponteiro para a string do caminho
	//char *pwd_string;  
	
	//file name 8.3 (11 bytes;)
    char name[32];

    //onde esse direto'rio esta' carregado.
    unsigned long current_dir_address;

	//...
};

struct target_dir_d current_target_dir;
 
 
// links para arquivos ou diretórios 
// dentro do mesmo sistema de arquivos. 

struct hardlink_d
{
    int used;
    int magic;
	//..
};



// links para arquivos e diretórios em 
// volumes espalhados por vários discos. 
struct softlink_d
{
    int used;
    int magic;
	//..
};



struct fat_d
{
    unsigned long address;
    int type;
	//...
};

struct fat_d *fat;

 


/*
 **************************************
 * dir_d:
 *     Estrutura para diretório de arquivo.
 *     #importante: 
 *     Entrada de diretório baseada em streams. 
 */

struct dir_d
{
    int id;

    int used;
    int magic;

    // #todo: Precisaremos dessas coisas.
    struct inode_d *inode;
    file *_file;

    pid_t pid;
    uid_t uid;
    gid_t gid;


    // número de bytes em uma entrada.
    int entry_size_in_bytes;

    //numero total de bytes no diretório.
    int totalentries_size_in_bytes;

    int number_of_entries;

    // Númetro máximo de arquivos em um diretório.
    int fileMax;

	// Número total de arquivos presentes no diretório.
    int fileTotal;

	//Endreço onde o arquivo foi carregado.
    unsigned long address;
   

    //flag, se esta ou nao na memoria.
    int inMemory;

    struct dir_d *next;
};



/*
 * filesystem_d:
 *     Informações sobre um sistema de arquivos.
 */

struct filesystem_d
{
    // Object info.

    object_type_t  objectType;
    object_class_t objectClass;

    //#todo:
    //int id;

    int used;
    int magic;

    int type;

    char *name;


    // Sectors per cluster.
    int spc; 


    // Number of entries in the root dir.
    //int rootdir_entries;
    int dir_entries;
    
    // Size of the entry in bytes.
    int entry_size; 

    //================    

    // #bugbug
    // Thats specific for fat16.
    // fat16.
    
    unsigned long rootdir_address;   //endereço do rootdir
    unsigned long rootdir_lba;       //lba
    unsigned long fat_address;       //endereço da fat  
    unsigned long fat_lba;           //lba
    unsigned long dataarea_address;  //endereço do inicio da area de dados.
    unsigned long dataarea_lba;      //lba

    //...
};

struct filesystem_d *root;
// ...



/*
 * file_access_d:
 *     Estrutura para os elementos necessários 
 *     para acessar um arquivo.
 */
 
struct file_access_d
{
    pid_t pid;
    uid_t uid;
    gid_t gid;

    //disk
    struct diskinfo_d *Disk;
    
    //volume
    struct volumeinfo_d *Volume;

    //filesystem
    struct filesystem_d *FileSystem;
    
       
    //directory
    struct dir_d *Directory;

    struct inode_d *inode;
    file *File;


    //flags
    //int flag;	

    // ...
    
    struct file_access_d *next;
};




//
// == Prototypes ================================================
//


void file_close (file *_file);
int file_truncate ( file *_file, size_t len);
size_t file_get_len(file *_file);



struct fat16_directory_entry_d *fs_new_fat16_directory_entry(void);


// Pega um fd na lista de arquivos do processo, dado o PID.
// Objects[i]
int fs_get_free_fd_from_pid (int pid);


// Atualiza a string do pwd na estrutura do processo. 
int fs_initialize_process_pwd ( int pid, char *string ); 

int fs_print_process_pwd ( int pid );



/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */

void fsInitializeWorkingDiretoryString (void); 


/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global.
 */

void fsUpdateWorkingDiretoryString ( char *string );


void sys_pwd(void);

void sys_cd_command( char *string);


/* 
 ************************************************
 * fs_pathname_backup:
 *     Remove n nomes de diretório do pathname do processo indicado 
 * no argumento.
 *     Copia o nome para a string global.
 *
 *     Remove the last N directories from PATH.  
 *     Do not leave a blank path.
 *     PATH must contain enough space for MAXPATHLEN characters. 
 *     #obs: O PID costuma ser do processo atual mesmo. 
 *
 * Credits: bash 1.05
 */

void fs_pathname_backup ( int pid, int n ); 




//
// load file in the ring0 buffer.
//

// usada por open();
// IN: name, flags, mode
int sys_read_file_from_disk ( char *file_name,  int flags, mode_t mode );


int
sys_write_file_to_disk ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag );


//
// Create
//

int fs_create_empty_file ( char *file_name, int type );
int fs_create_empty_directory ( char *dir_name, int type );

int sys_create_empty_file ( char *file_name );
int sys_create_empty_directory ( char *dir_name );



void 
fsFAT16ListFiles ( 
   const char *dir_name, 
   unsigned short *dir_address, 
   int number_of_entries );


void fs_init_structures (void);

void set_filesystem_type (int type);

int get_filesystem_type (void);


//#todo: spt in a given volume.
void set_spc(int spc);
int get_spc (void);
 


unsigned long path_count (unsigned char *path);
int load_path ( unsigned char *path, unsigned long address );
int sys_load_path ( unsigned char *path, unsigned long u_address );


//
// FAT support.
//
 
void fsClearFat (void);   
void fs_init_fat (void);

 
void fs_load_fat(void);



//Load metafile.
void 
fs_load_metafile (
    unsigned long buffer, 
    unsigned long first_lba, 
    unsigned long size );

// root dir support
void fs_load_rootdir (void);

int fs_save_rootdir (void);
int fs_save_fat (void);

void fs_save_entry_on_root(unsigned long eid);


// Carrega o diretório na memória, dados o endereço, 
// o lba inicial e o número de setores.

int
__load_sequential_sectors ( 
    unsigned long address, 
    unsigned long lba, 
    unsigned long sectors );



// #todo
// Caregar um arquivo na memoria e retornar seu inode.
// ? registrar a estrutura de inode na inode_table[] ?
// ? registrar a estrutura de arquivo na file_table[] ?
struct inode_d *fs_load_file (char *pathname);

//
// Read
//

// @todo:
// Mudar o retorno para int.
// Mudar file_name para char*.
// Mudar file_address para char*.
// usar o save file como exemplo.

// #test
// Vamos tentar a opção de carregarmos um arquivo de um dado diretório.
// O endereço do diretório será passado via argumento.

unsigned long 
fsLoadFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    unsigned char *file_name, 
    unsigned long file_address,
    unsigned long buffer_limit );


// #bugbug
// Get file size.
// Only on root dir!
unsigned long fsRootDirGetFileSize ( unsigned char *file_name );



//
// Write
//

int
fsSaveFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes, 
    char *file_address,
    char flag );



int fsSearchFile( unsigned char *file_name);
int fsSearchFileName( unsigned char *name);

int search_in_root ( char *filename );
int KiSearchFile( unsigned char *file_name, unsigned long address);


// manipulando a lista de arquivos do kernel.
void *get_file(int Index);
void set_file( void *file, int Index);

// manipulando a lista global de arquivos abertos pelos processos.
void *get_global_open_file (int Index);
void set_global_open_file ( void *file, int Index );


//info
void fs_show_file_info (file *f);
void fs_show_file_table(void);


int get_free_slots_in_the_file_table(void);


//
// Create
//

int fs_create_file( char *name );
unsigned long fs_create_dir ( char *name , unsigned long id);


void 
fs_create_entry ( 
    char *name, 
    unsigned long id, 
    unsigned long eid, 
    unsigned long cluster, 
    unsigned long size );


void fs_create_name( char *name, unsigned long id,unsigned long eid);



int
fs_save_dir ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag );  

int
fs_save_file ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag );  


void fs_delete_entry(unsigned long id, unsigned long eid);



unsigned short fs_find_n_empty_entries ( int n);

// #importante
// Encontrar uma entrada vazia na fat.
unsigned short fs_find_empty_entry ( char *fat_address );



unsigned long 
fatClustToSect ( 
    unsigned short cluster, 
    unsigned long spc, 
    unsigned long first_data_sector );


void 
fatLoadCluster ( 
    unsigned long sector, 
    unsigned long address, 
    unsigned long spc );


void 
fatWriteCluster ( 
    unsigned long sector, 
    unsigned long address, 
    unsigned long spc );


int fsList ( const char *dir_name );


void 
fsListFiles ( 
    int disk_id, 
    int volume_id, 
    int directory_id );



// Procura uma entrada vazia no diretório 
int 
findEmptyDirectoryEntry ( 
    unsigned long dir_address, 
    int number_of_entries );


// Modificador de string.
// Deixa tudo em maiúscula.
void read_fntos (char *name);

  
int fsCheckELFFile ( unsigned long address );

// MBR support.
void fsCheckMbrFile ( unsigned char *buffer );

// VBR support.
void fsCheckVbrFile ( unsigned char *buffer );


int fsLoadFileFromCurrentTargetDir (void);
void fsInitTargetDir (void);


void fs_show_root_fs_info(void);


// Initialization support.
int fsInit (void);


#endif    


//
// End.
//


