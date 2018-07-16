/*
 * File: execve\fs\fs.h 
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
 *     2015 - Revision.
 */
 
#define FS_PATHNAME_SEPARATOR "/"
#define FS_PATHNAME_TERMINATOR "\0"

#define FS_STRING_TERMINATOR "\0" 
//
// Volume support
//

//Volume list
#define FS_ROOT_STRING        "root:"
#define FS_VOLUMELIST_STRING  "root:"

//volumes
#define FS_UNKNOWNVOLUME_STRING "unknown-volume"
#define FS_VOLUME0_STRING "volume0"   //vfs
#define FS_VOLUME1_STRING "volume1"   //boot volume
#define FS_VOLUME2_STRING "volume2"   //system volume.

//...

char *current_volume_string;
//int current_volume_id; //DEFINIDO NO KERNEL.H COMO current_volume.



//
// pwd support
//


#define FS_UNKNOWNWORKINGDIRECTORY_ID (-1)
#define FS_VFSWORKINGDIRECTORY_ID     0
#define FS_BOOTWORKINGDIRECTORY_ID    1
#define FS_SYSTEMWORKINGDIRECTORY_ID  2


#define FS_VFSWORKINGDIRECTORY_STRING     "volume1"
#define FS_BOOTWORKINGDIRECTORY_STRING    "volume1"
#define FS_SYSTEMWORKINGDIRECTORY_STRING  "volume2"
#define FS_UNKNOWNWORKINGDIRECTORY_STRING "unknown-directory"

#define WORKINGDIRECTORY_STRING_MAX 32
// a stringo do diretório de trabalho.
char current_workingdiretory_string[WORKINGDIRECTORY_STRING_MAX];
int pwd_initialized;

 
//
// #BUGBUG
// #importante:
// lembrando que o kernel começa em 0x00100000
// @todo: Podemos encontrar um novo lugar para isso tudo.
// 
 
//
//  ## MBR SUPPORT  ##
//

#define MBR_LBA               0           // mbr
#define MBR_ADDRESS           0x00020000  //isso suja o bm? ou bl?

//
//  ## VBR SUPPORT  ##
//
       
#define VOLUME1_VBR_LBA       63
#define VOLUME2_VBR_LBA       32000
#define VOLUME1_VBR_ADDRESS   (0x00020000 + 0x200) 
#define VOLUME2_VBR_ADDRESS   (0x00020000 + 0x200) 

//
//  ## FAT1 SUPPORT  ##
//

#define VOLUME1_FAT_LBA       67 
#define VOLUME2_FAT_LBA       33000  
#define VOLUME1_FAT_ADDRESS   0x00030000 
#define VOLUME2_FAT_ADDRESS   0x00030000

//
//  ## FAT2 SUPPORT  ##
//

// Não usada !!

//
//  ## ROOT DIR SUPPORT  ##
//

#define VOLUME1_ROOTDIR_LBA     559
#define VOLUME2_ROOTDIR_LBA     34000
#define VOLUME1_ROOTDIR_ADDRESS 0x00070000 
#define VOLUME2_ROOTDIR_ADDRESS 0x00070000 
 
//
//  ##  DATA AREA SUPPORT  ##
//

#define VOLUME1_DATAAREA_LBA   591 
#define VOLUME2_DATAAREA_LBA   35000

//
// ============ Path support ======================
//

// Diretório raiz dos volumes principais.
#define FS_DIR_VFS    'root:/volume0'  // raiz do vfs
#define FS_DIR_BOOT   'root:/volume1'  // raiz do volume de boot
#define FS_DIR_SYSTEM 'root:/volume2'  // raiz do volume do sistema
//...

// Arquivos no volume de boot.
// Obs: O volume de boot só terá o diretório raiz.
#define FS_DIR_BM      'root:/volume1/BM.BIN'       // boot manager
#define FS_DIR_BL      'root:/volume1/BL.BIN'       // boot loader
#define FS_DIR_KERNEL  'root:/volume1/KERNEL.BIN'   // kernel
#define FS_DIR_INIT    'root:/volume1/INIT.BIN'     // init
#define FS_DIR_SHELL   'root:/volume1/SHELL.BIN'    // shell
#define FS_DIR_TASKMAN 'root:/volume1/TASKMAN.BIN'  // task manager
#define FS_DIR_INITTXT 'root:/volume1/INIT.TXT'     // init txt
//...  


// Diretórios no volume do sistema. 
#define FS_DIR_BIN          'root:/volume2/bin'          // binary programs.
#define FS_DIR_DEV          'root:/volume2/dev'          // i/o devices.
#define FS_DIR_LIB          'root:/volume2/lib'          // libraries
#define FS_DIR_USER         'root:/volume2/user'         // users
#define FS_DIR_DEFAULTUSER  'root:/volume2/user/default' // default user


#define FS_MAX_NAME_LENGHT (8+3)   // Max name lenght.   8.3
#define PS1                '/'     // Primary path separator.
#define PS2                '\\'    // Alternate path separator.
//...
 
//
// Types. (@todo: Criar definições de tipos).
// 

#define FS_TYPE_VFS   1000  // Designativo genérico.  
#define FS_TYPE_GVFS  1001  // Gramado VFS.   
//...

#define FS_TYPE_FAT   2000  // Designativo genérico.
#define FS_TYPE_FAT12 2001 
#define FS_TYPE_FAT16 2002 
#define FS_TYPE_FAT32 2003 
//...

#define FS_TYPE_MINIXFS  3000  //Minix FS
#define FS_TYPE_EXT      3001
#define FS_TYPE_EXT2     3002
#define FS_TYPE_EXT3     3003
#define FS_TYPE_EXT4     3004
//... 
 
//... 
 


 
#define FAT16_ROOT_ENTRIES  512  //512 entradas no rootdir. 
#define FAT16_ENTRY_SIZE    32   //tamanho em bytes da entrada no root dir. 
 
#define INIT_SECTOR 20 //??

 
/*
 * FAT constants.
 */
 
#define FAT_ERRO_1 0xffff9  //nao ha entradas vazias. 
#define FAT_ERRO_2 0xffff8   
#define FAT_ERRO_3 0xffff7
#define FAT_ERRO_4 0xffff6

#define FAT_STATUS_1 0xffff5  // NAO ha mais entradas cheias.
#define FAT_STATUS_2 0xffff4
#define FAT_STATUS_3 0xffff3
#define FAT_STATUS_4 0xffff2


//primeiro char do nome do arquivo na entrada de diretorio
//no sistema de arquivos fat16.
#define ENTRY_NEVER_USED       0x00
#define ENTRY_FILE_IS_DELETED  0xE5 
#define ENTRY_DIRECTORY        0x2E 
//#define ENTRY_


//
//file atribute
//
#define FILE_ATTRIBUTE_READ_ONLY     0x01 
#define FILE_ATTRIBUTE_HIDDEN        0x02
#define FILE_ATTRIBUTE_SYSTEM        0x04
#define FILE_ATTRIBUTE_VOLUME_LABEL  0x08
#define FILE_ATTRIBUTE_DIRECTORY     0x10
#define FILE_ATTRIBUTE_ARCHIVE       0x20
#define FILE_ATTRIBUTE_UNUSED1       0x40
#define FILE_ATTRIBUTE_UNUSED2       0x80
 

/*
    IMAGE_FILE_MACHINE_I386 (0x14c)
        for Intel 80386 processor or better

    0x014d
        for Intel 80486 processor or better

    0x014e
        for Intel Pentium processor or better

    0x0160
        for R3000 (MIPS) processor, big endian

    IMAGE_FILE_MACHINE_R3000 (0x162)
        for R3000 (MIPS) processor, little endian

    IMAGE_FILE_MACHINE_R4000 (0x166)
        for R4000 (MIPS) processor, little endian

    IMAGE_FILE_MACHINE_R10000 (0x168)
        for R10000 (MIPS) processor, little endian

    IMAGE_FILE_MACHINE_ALPHA (0x184)
        for DEC Alpha AXP processor

    IMAGE_FILE_MACHINE_POWERPC (0x1F0)
        for IBM Power PC, little endian
		
// 1 byte aligned
struct PeHeader {
	uint32_t mMagic; // PE\0\0 or 0x00004550
	uint16_t mMachine;
	uint16_t mNumberOfSections;
	uint32_t mTimeDateStamp;
	uint32_t mPointerToSymbolTable;
	uint32_t mNumberOfSymbols;
	uint16_t mSizeOfOptionalHeader;
	uint16_t mCharacteristics;
}; 
 
// 1 byte aligned
struct Pe32OptionalHeader {
	uint16_t mMagic; // 0x010b - PE32, 0x020b - PE32+ (64 bit)
	uint8_t  mMajorLinkerVersion;
	uint8_t  mMinorLinkerVersion;
	uint32_t mSizeOfCode;
	uint32_t mSizeOfInitializedData;
	uint32_t mSizeOfUninitializedData;
	uint32_t mAddressOfEntryPoint;
	uint32_t mBaseOfCode;
	uint32_t mBaseOfData;
	uint32_t mImageBase;
	uint32_t mSectionAlignment;
	uint32_t mFileAlignment;
	uint16_t mMajorOperatingSystemVersion;
	uint16_t mMinorOperatingSystemVersion;
	uint16_t mMajorImageVersion;
	uint16_t mMinorImageVersion;
	uint16_t mMajorSubsystemVersion;
	uint16_t mMinorSubsystemVersion;
	uint32_t mWin32VersionValue;
	uint32_t mSizeOfImage;
	uint32_t mSizeOfHeaders;
	uint32_t mCheckSum;
	uint16_t mSubsystem;
	uint16_t mDllCharacteristics;
	uint32_t mSizeOfStackReserve;
	uint32_t mSizeOfStackCommit;
	uint32_t mSizeOfHeapReserve;
	uint32_t mSizeOfHeapCommit;
	uint32_t mLoaderFlags;
	uint32_t mNumberOfRvaAndSizes;
}; 
 
struct IMAGE_SECTION_HEADER { // size 40 bytes
	char[8]  mName;
	uint32_t mVirtualSize;
	uint32_t mVirtualAddress;
	uint32_t mSizeOfRawData;
	uint32_t mPointerToRawData;
	uint32_t mPointerToRawData;
	uint32_t mPointerToRealocations;
	uint32_t mPointerToLinenumbers;
	uint16_t mNumberOfRealocations;
	uint16_t mNumberOfLinenumbers;
	uint32_t mCharacteristics;
}; 
 
*/
 
 
 
//links para arquivos ou diretórios dentro do mesmo sistema de arquivos. 
typedef struct hardlink_d hardlink_t; 
struct hardlink_d
{
	int used;
	int magic;
	//..
	
};
 
//links para arquivos e diretórios em volumes espalhados por vários discos. 
typedef struct softlink_d softlink_t; 
struct softlink_d
{
	int used;
	int magic;
	//..
};
 
 
/*
 * mbr_d:
 *     Structure for MBR parameters.
 *
 */ 
typedef struct mbr_d mbr_t; 
struct mbr_d
{
   /*
    //Código para realocação do mbr.
	char relocation_code[19];
	
	//Código do boot sector.
    char boot_code[400];
      
	//Sistem info. 
    char OEM_ID[4];  //"NORA "
    char VERSION[3]; //"1.0"
	  
    //Bpb.	
    unsigned short BytesPerSector;  // dw 512
	char SectorsPerCluster;         // db 1
	short ReservedSectors;          // dw 2
	char TotalFATs;                 // db 2
	short MaxRootEntries;           // dw 512         ;512 entradas de 32bytes=32 setores.
	short TotalSectorsSmall;        // dw 0
	char MediaDescriptor;           // db 0xF0
	short SectorsPerFAT;            // dw 64          ;64.      
	short SectorsPerTrack;          // dw 0           ;pegar via bios.     
	
	short NumHeads;                 // dw 0           ;pegar via bios.        
	long HiddenSectors;             // dd 0x00000000
	long TotalSectorsLarge;         // dd 0x00000000
	
	//;for extended.
	char DriveNumber;               // db 0x80        ;pegar via bios.
	char Flags;                     // db 0x00
	char bootSignature;             // db 0           ;Extended Boot Signature.
	long VolumeID;                  // dd 0x00000001
	char VolumeLabel[10];           // db "FREDNORA8MB"
	char SystemID[7];               // db "FAT16   "		
	
	//PointerTable
	unsigned short SystemName;
	unsigned short SystemVersion;
	unsigned short SystemBPB;
	unsigned short SystemSignature;
	
	//Partition Table
	unsigned long p0[3];
	unsigned long p1[3];
	unsigned long p2[3];
	unsigned long p3[3];
	
	//Signature.
	unsigned short Signature;	
	*/
}; 
mbr_t *mbr; 
//mbr_t *Mbr; 

 
/*
 * vbr_d:
 *     Structure for VBR parameters.
 *
 */  
typedef struct vbr_d vbr_t; 
struct vbr_d
{
	//copiar mbr, é parecido;
}; 
vbr_t *vbr; 
//vbr_t *Vbr; 
 
 

 
 
/*
 * fat_d:
 *     Fat 16.
 *
 */
 
typedef struct fat_d fat_t; 
struct fat_d
{
    unsigned long address;
	int type;
	//...
};
fat_t *fat;


/*
typedef struct findfile_d findfile_t;
struct findfile_d
{
	//char reserved[21];
	//char attrib;
	//unsigned short wr_time;
	//unsigned short wr_date;
	unsigned long size;
	char name[13];	
};
findfile_t *Findfile;
*/






/*
 * file_d:
 *     Estrutura para arquivo.
 */ 
typedef struct file_d file_t;
struct file_d
{
    //@todo: incluir informações extras sobre o arquivo.
	
	/*
	 * Endreço onde o arquivo foi carregado.
	 *
	 */
	unsigned long address;
	
    /*
	 * Um ponteiro pra estrutura da entrada atual.
	 */
	struct dir_entry_d *current;
};
//file_t *File;
//file_t *CurrentFile;
//...







/*
 * dir_d:
 *     Estrutura para diretório de arquivo.
 *     #importante: Entrada de diretório baseada em strams. 
 */
typedef struct dir_d dir_t;
struct dir_d
{
	//
	// @todo: Criar e organizar os elementos dessa estrutura.
	//
	
	int id;
	
	//
	int used;
	
	//
	int magic;
	
	// Parte principal da estrutura
	FILE *stream;
	
	//
    // @todo: Incluir informações extras sobre o diretório,
	//        como se está ou não carregado na memória, endereço,
	//        privilégios ...
	//
	
	//struct user_info_d *OwnerUser;	
	//struct process_d *OwnerProcess;
	
	
	// numero de bytes em uma entrada.
	int entry_size_in_bytes;
	
	//numero total de bytes no diretório.
	int totalentries_size_in_bytes;
	
    /*
     * Númetro máximo de arquivos em um diretório.
	 */
    int fileMax;

    /*
	 * Número total de arquivos presentes no diretório.
	 */   
    int fileTotal;
	
	/*
	 * Endreço onde o arquivo foi carregado.
	 *
	 */
	unsigned long address;
   
   /*
    * flag, se esta ou nao na memoria.
	*/
    int inMemory;
   
    /*
	 * Um ponteiro pra estrutura da entrada atual.
	 */
	struct dir_entry_d *current;
};

//@todo: seguir a lista usada em stdio.h presentes em Streams[]

struct dir_d *volume0RootDir;  //VFS.
struct dir_d *volume1RootDir;  //boot volume.
struct dir_d *volume2RootDir;  //system volume.
//...


//Diretório raiz.
struct dir_d *rootDir;      // 

//Principais.
struct dir_d *gbuildDir;    // "/gbuild"
struct dir_d *gdocsDir;     // "/gdocs"
struct dir_d *gramadoDir;   // "/gramado"
struct dir_d *gsdkDir;      // "/gsdk"
struct dir_d *gsrcDir;      // "/gsrc"

//Secundários.
struct dir_d *usersDir;     // "/users"
struct dir_d *cmdDir;       // "/cmd"
struct dir_d *tmpDir;       // "/tmp"
struct dir_d *downloadDir;  // "/download"
//...

//Diretório atual.
struct dir_d *currentDir;       // 


//
// @todo: Obs: Eu nem sei se essa listagem de diretórios deveria existir.
//             Talvez essa possa ser uma forma de estabelecer um padrão.
//             Pois ficará difícil mudar isso. Talvez essa rigidez 
//             ajude consolidar quais serão os diretórios e arquivos principail. 
//
 
 


 

/*
 * filesystem_d:
 *     Informações sobre o sistema de arquivos usado pelo sistema.
 *
 */
typedef struct filesystem_d filesystem_t; 
struct filesystem_d
{
    int type;
	
	unsigned long rootdir_address; //endereço do rootdir
    unsigned long rootdir_lba;     //lba
	
	unsigned long fat_address;     //endereço da fat  
	unsigned long fat_lba;      //lba
	
    unsigned long dataarea_address; //endereço do inicio da area de dados.
    unsigned long dataarea_lba;   //lba
	
	int spc; //Sectors per cluster.
    int rootdir_entries; //numero de entradas no rootdir.
	int entry_size;      //tamanho da entrada em bytes.
	
	//...
};
filesystem_t *filesystem;
//filesystem_t *FileSystem;
//filesystem_t *CurrentFileSystem;
//...


/*
 * file_access_d:
 *     Estrutura para os elementos necessários 
 *     para acessar um arquivo.
 *
 */
typedef struct file_access_d file_access_t; 
struct file_access_d
{
    //disk
	struct diskinfo_d *Disk;
    
	//volume
	struct volumeinfo_d *Volume;
	
	//filesystem
	struct filesystem_d *FileSystem;
    
	//directory
	struct dir_d *Directory;
	struct dir_entry_d *current;
	
	//file	
    struct file_d *File;
    struct _iobuf *FileInfo; //FILE (C99)	
	
	//flags
    //int flag;	
};
file_access_t *FileAccess;
 
 
 
/*
 * Contagem de diretórios.
 */
int dirCount;  



/*
 * Variables.
 */

 
 
/*
 * Suporte à lista de partições.
 * Volumes são partições, As partições podem estar em discos diferentes
 * ou podem ser volumes virtuais.
 * A lista armazena endereços das estruturas dos volumes.
 *
 */ 
//unsigned long volumeList[256];  //@todo: Diminuir o tamanho do buffer.
 
 
//Id da partição atual.(volume atual) 
int current_volume; 

/*
 * Tipo de sistema de arquivos, fat16, ext2 ...
 */
 
int g_file_system_type; //@todo: DELETAR.
int g_filesystem_type;   //use this one.
int g_spc;               //sectors per cluster.(spc é variável.)



// Se é fat32, 16, 12.
int fatbits;   



//list of clusters. 
unsigned short file_cluster_list[1024]; 




//
// ## Prototypes ##
//


/*
 * Initialization support.
 */
int fsInit();

void 
fsFAT16ListFiles( const char *dir_name, 
                  unsigned short *dir_address, 
				  int number_of_entries );

//MBR support.
void fsCheckMbrFile( unsigned char *buffer );

//VBR support.
void fsCheckVbrFile( unsigned char *buffer );


void fs_init_structures();
void set_filesystem_type(int type);
int get_filesystem_type();
void set_spc(int spc);
int get_spc();	
void fs_save_structure();
void fs_set_structures();
 


//
// FAT support.
//
 
void fsClearFat();   
void fs_init_fat();
void fs_put_list_on_fat();
void fs_apaga_fat();
void fs_load_fatEx();
unsigned long fs_get_fat_entry(unsigned long n);
void fs_set_fat_entry(unsigned long n, unsigned long value);
unsigned long fs_check_fat();
void fs_test_fat_vector();


//
// root dir support
//
   

void fs_load_rootdir();
void fs_save_rootdir();
void fs_save_entry_on_root(unsigned long eid);
void fs_load_rootdirEx();
void limpa_root(); 


//   Carrega o diretório na memória, dados o endereço, 
//o lba inicial e o número de setores.
void 
load_directory( unsigned long address, 
                unsigned long lba, 
				unsigned sectors );

//
// Read
//

// @todo:
// Mudar o retorno para int.
// Mudar file_name para char*.
// Mudar file_address para char*.
// usar o save file como exemplo.
unsigned long 
fsLoadFile( unsigned char *file_name, 
            unsigned long file_address ); 

//vai ficar assim.			
//int
//fsLoadFile( char *file_name, 
//            char *file_address ); 
			
			
//
// Write
//

int
fsSaveFile( char *file_name, 
            unsigned long file_size,
            unsigned long size_in_bytes, 			
		    char* file_address,
            char flag );


						  
int fsSearchFile( unsigned char *file_name);
int fsSearchFileName( unsigned char *name);

int KiSearchFile( unsigned char *file_name, unsigned long address);
void create_system_folders();
void set_file( void *file, int Index);
void *get_file(int Index);

unsigned long fs_create_dir( char *name , unsigned long id);

int fs_create_file( char *name );

void fs_create_entry( char *name, 
                      unsigned long id, 
					  unsigned long eid, 
					  unsigned long cluster, 
					  unsigned long size );
void fs_create_name( char *name, unsigned long id,unsigned long eid);
void fs_show_dir_entry(unsigned long id,unsigned long eid);
void fs_show_dir(unsigned long id);

void fs_set_entry(unsigned long id, unsigned long eid);
void fs_get_entry(unsigned long id, unsigned long eid);
void fs_load_dir(unsigned long id);
void fs_save_dir(unsigned long id);
void fs_set_entry_status(unsigned long id, unsigned long eid, unsigned long status);
unsigned long fs_get_entry_status(unsigned long id, unsigned long eid);
void fs_delete_entry(unsigned long id, unsigned long eid);



void fs_show_entry(unsigned long id, unsigned long eid);																			 

unsigned short 
fs_find_n_empty_entries( int n);

// #importante
// Encontrar uma entrada vazia na fat.
unsigned short 
fs_find_empty_entry( char *fat_address );

unsigned long fs_check_cluster(unsigned long id);
//unsigned long fs_find_not_empty_entry();

void salva_nome( unsigned char *file_name, 
                 unsigned long id, 
				 unsigned long eid, 
				 unsigned long cluster_inicial);//exec

unsigned long 
fatClustToSect( unsigned short cluster, 
                unsigned long spc, 
				unsigned long first_data_sector );

void fatLoadCluster( unsigned long sector, 
                     unsigned long address, 
					 unsigned long spc );
					 
void fatWriteCluster( unsigned long sector, 
                      unsigned long address, 
					  unsigned long spc );
					  
void 
MountShortFileName( char *buffer, 
                    struct dir_entry_d *entry );

void fs_check_disk();

void fsCreateVFS();

void fsListFiles( int disk_id, 
                  int volume_id, 
				  int directory_id );
				  
				  
				  
//interna
//procura uma entrada vazia no diretório 
int 
findEmptyDirectoryEntry( unsigned long dir_address, 
                         int number_of_entries );
				  
				  
//Modificador de string.
void read_fntos(char *name);
				  
				  
int fsCheckPEFile( unsigned long address );	





/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */
void 
fsInitializeWorkingDiretoryString(); 

/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */ 
void 
fsUpdateWorkingDiretoryString( char *string );

/* 
 Remove the last N directories from PATH.  
 Do not leave a blank path.
 PATH must contain enough space for MAXPATHLEN characters. 
 Credits: bash 1.05
 */
void 
fs_pathname_backup( char *path, int n ); 			  
				  
//
// End.
//
