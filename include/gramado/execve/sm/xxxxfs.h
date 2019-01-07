/*
 * File: fs.h 
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
 * Versão 1.0 ~ 2014, 2015.
 */



/*
#define MAXPATH                 256     // Maximum filename length (including trailing zero)
#define MFSNAMELEN              16      // Length of fs type name

#define PS1                     '/'     // Primary path separator
#define PS2                     '\\'    // Alternate path separator
*/ 
 
//
// Types. (@todo: Criar definições de tipos).
// 
#define FS_TYPE_FAT16 1 
#define FS_TYPE_EXT2  2
 
 
/*
 * @todo: 
 *     Deixar espaço bastante par um kernel grande, 
 *     começando em 0x00100000
 */
 
#define FS_VBR_ADDRESS        0x001A0000 
#define FS_FAT_ADDRESS        0x001B0000 
#define FS_ROOTDIR_ADDRESS    0x001C0000 


//fat16
#define FAT16_VBR_ADDRESS     FS_VBR_ADDRESS
#define FAT16_FAT_ADDRESS     FS_FAT_ADDRESS
#define FAT16_ROOTDIR_ADDRESS FS_ROOTDIR_ADDRESS

//fat32
#define FAT32_VBR_ADDRESS     FS_VBR_ADDRESS
#define FAT32_FAT_ADDRESS     FS_FAT_ADDRESS
#define FAT32_ROOTDIR_ADDRESS FS_ROOTDIR_ADDRESS



/*
 * Referências para localização de VBR, FAT, ROOT, DATAAREA ...
 *
 * partição 0 - (8MB)
 *
 * vbr  - ?  ;134  (depende do tanto de setores reservados.)
 * fat1 - 136
 * fat2 - 200
 * root - 264
 * data - 296
 *
 */
#define FS_VBR_LBA       63   //134
#define FS_FAT_LBA       67   //136 
#define FS_ROOTDIR_LBA   559  //264
#define FS_DATAAREA_LBA  591  //296 

//mbr 
#define MBR_LBA  0
#define MBR_ADDRESS      0x00020000
#define FS_MBR_LBA       MBR_LBA
#define FS_MBR_ADDRESS   0x00020000

//Partição 0.
#define FAT16_VBR_LBA       FS_VBR_LBA 
#define FAT16_FAT_LBA       FS_FAT_LBA 
#define FAT16_ROOTDIR_LBA   FS_ROOTDIR_LBA
#define FAT16_DATAAREA_LBA  FS_DATAAREA_LBA 
 
//FAT32
#define FAT32_VBR_LBA       FS_VBR_LBA 
#define FAT32_FAT_LBA       FS_FAT_LBA 
#define FAT32_ROOTDIR_LBA   FS_ROOTDIR_LBA
#define FAT32_DATAAREA_LBA  FS_DATAAREA_LBA 
 
 
 
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
 * partition_table_d:
 *     Structure for partition table.
 *
 */ 
typedef struct partition_table_d partition_table_t; 
struct partition_table_d
{    
	unsigned char boot_indicator; //80h active
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    unsigned long start_sector;
    unsigned long partition_size; //in sectors.
	
};
partition_table_t *partition; 
//partition_table_t *PartitionTable; 


//As informações na partition table apresentadas na forma de 'char'. 
typedef struct partition_table_chars_d partition_table_chars_t; 
struct partition_table_chars_d
{ 
	unsigned char BootFlag;                // Bootable or not
    
	unsigned char StartingCHS0;            // Not used
    unsigned char StartingCHS1;            // Not used
    unsigned char StartingCHS2;            // Not used
    
	unsigned char PartitionType;            // 
    
	unsigned char EndingCHS0;              // Not used
    unsigned char EndingCHS1;              // Not used
    unsigned char EndingCHS2;              // Not used
    
	unsigned char StartingSector0;       // Hidden sectors
    unsigned char StartingSector1;
    unsigned char StartingSector2;
    unsigned char StartingSector3;
    
	unsigned char PartitionLength0;      // Sectors in this partition
    unsigned char PartitionLength1;
    unsigned char PartitionLength2;
    unsigned char PartitionLength3; 
};
partition_table_chars_t *partition_chars; 
//partition_table_chars_t *PartitionTableChars;
 
 
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
//fat_t *Fat;


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
typedef struct Fat16Entry_d Fat16Entry_t;
struct Fat16Entry_d 
{
    char           FileName[11];      // Filename + extension.
    unsigned char  Attr;              // File attributes.
    unsigned char  ReservedNT;        // Reserved for use by Windows NT.
    unsigned char  TimeInTenths;      // Millisecond stamp at file creation.
    unsigned short CreateTime;        // Time file was created.
    unsigned short CreateDate;        // Date file was created.
    unsigned short LastAccessDate;    // Date file was last accessed.
    unsigned short ClusterHigh;       // High word of this entry's start cluster.
    unsigned short Time;              // Time last modified.
    unsigned short Date;              // Date last modified.
    unsigned short ClusterLow;        // First cluster number low word.
    unsigned long  Size;              // File size. 
};
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
 * dir_entry_d:
 *     Entrada de diretório.
 *     @todo: Qual é o sistema de arquivos. ??!
 *     fat16

Structure of the Directory Entries
Offset	Size	 Description
  00h	8 bytes	 Filename
  08h	3 bytes	 Filename Extension
  0Bh	1 bytes	 Attribute Byte
  0Ch	1 bytes	 Reserved for Windows NT
  0Dh	1 bytes	 Creation - Millisecond stamp (actual 100th of a second)
  0Eh	2 bytes	 Creation Time
  10h	2 bytes	 Creation Date
  12h	2 bytes	 Last Access Date
  14h	2 bytes	 Reserved for FAT32
  16h	2 bytes	 Last Write Time
  18h	2 bytes	 Last Write Date
  1Ah	2 bytes	 Starting cluster
  1Ch	4 bytes	 File size in bytes
*/
typedef struct dir_entry_d dir_entry_t; 
struct dir_entry_d
{
    char           FileName[11];      // Filename + extension.
    unsigned char  Attr;              // File attributes.
    unsigned char  ReservedNT;        // Reserved for use by Windows NT.
    unsigned char  TimeInTenths;      // Millisecond stamp at file creation.
    unsigned short CreateTime;        // Time file was created.
    unsigned short CreateDate;        // Date file was created.
    unsigned short LastAccessDate;    // Date file was last accessed.
    unsigned short ClusterHigh;       // High word of this entry's start cluster.
    unsigned short Time;              // Time last modified.
    unsigned short Date;              // Date last modified.
    unsigned short ClusterLow;        // First cluster number low word.
    unsigned long  Size;              // File size.
};
//dir_entry_t *DirectoryEntry; 
//dir_entry_t *SystemDirectoryEntry;
//dir_entry_t *TmpDirectoryEntry; 
//...





/*
 * dir_d:
 *     Estrutura para diretório de arquivo.
 *
 */
typedef struct dir_d dir_t;
struct dir_d
{
	//
    // @todo: Incluir informações extras sobre o diretório,
	//        como se está ou não carregado na memória, endereço,
	//        privilégios ...
	//
	
	//struct user_info_d *OwnerUser;	
	//struct process_d *OwnerProcess;
	
	
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

//Diretório raiz.
struct dir_d *rootDir;      // "/"

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
struct dir_d *currentDir;       // "/?"


//
// @todo: Obs: Eu nem sei se essa listagem de diretórios deveria existir.
//             Talvez essa possa ser uma forma de estabelecer um padrão.
//             Pois ficará difícil mudar isso. Talvez essa rigidez 
//             ajude consolidar quais serão os diretórios e arquivos principail. 
//
 
 
/*
 * Lista de endreços de estruturas de arquivos ou diretorios.
 *
 */
unsigned long fileList[32]; 


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
 
 
 

/*
 * Tipo de sistema de arquivos, fat16, ext2 ...
 */
 
int g_file_system_type; //@todo: DELETAR.
int g_filesystem_type;   //use this one.
int g_spc;               //sectors per cluster.(spc é variável.)



// Se é fat32, 16, 12.
int fatbits;    


/*
 * Initialization support.
 */
int fsInit();
void fsListFiles(unsigned short *dir);

//MBR support.
void fsCheckMbr();

//VBR support.
void fsCheckVbr();


void fs_init_structures();
void set_filesystem_type(int type);
int get_filesystem_type();
void set_spc(int spc);
int get_spc();	
void fs_save_structure();
void fs_set_structures();
 




/*
 * FAT support.
 */
void fsClearFat();   
void fs_init_fat();
void fs_put_list_on_fat();
void fs_apaga_fat();
void fs_load_fatEx();
unsigned long fs_get_fat_entry(unsigned long n);
void fs_set_fat_entry(unsigned long n, unsigned long value);
unsigned long fs_check_fat();
void fs_test_fat_vector();


/*
 * ROOT DIR support.
 */ 
void KiLoadRootDir(unsigned long address);
void fs_load_rootdir();
void fs_save_rootdir();
void fs_save_entry_on_root(unsigned long eid);
void fs_load_rootdirEx();
void limpa_root(); 


/*
 * File operations support.
 */
unsigned long fsLoadFile( unsigned char *file_name, unsigned long file_address); 
unsigned long fsSaveFile( unsigned char *file_name, 
                          unsigned long file_size, 
						  unsigned long file_address );
int fsSearchFile( unsigned char *file_name);
unsigned long fsSearchFileName( unsigned char *name);

int KiSearchFile( unsigned char *file_name, unsigned long address);
void create_system_folders();
void set_file( void *file, int Index);
void *get_file(int Index);
unsigned long fs_create_dir( char *name , unsigned long id);
unsigned long fs_create_file( char *name , unsigned long id);
void fs_create_entry( char *name, 
                      unsigned long id, 
					  unsigned long eid, 
					  unsigned long cluster, 
					  unsigned long size );
void fs_create_name( char *name, unsigned long id,unsigned long eid);
void fs_show_dir_entry(unsigned long id,unsigned long eid);
void fs_show_dir(unsigned long id);
unsigned long fs_search_empty_entry(unsigned long id);
void fs_set_entry(unsigned long id, unsigned long eid);
void fs_get_entry(unsigned long id, unsigned long eid);
void fs_load_dir(unsigned long id);
void fs_save_dir(unsigned long id);
void fs_set_entry_status(unsigned long id, unsigned long eid, unsigned long status);
unsigned long fs_get_entry_status(unsigned long id, unsigned long eid);
void fs_delete_entry(unsigned long id, unsigned long eid);



void fs_show_entry(unsigned long id, unsigned long eid);																			 
unsigned long fs_find_n_empty_entries(unsigned long n);
unsigned long fs_find_empty_entry();
unsigned long fs_check_cluster(unsigned long id);
unsigned long fs_find_not_empty_entry();

void salva_nome( unsigned char *file_name, 
                 unsigned long id, 
				 unsigned long eid, 
				 unsigned long cluster_inicial);//exec

unsigned long fatClustToSect(unsigned short cluster, unsigned long spc, unsigned long first_data_sector);
void fatLoadCluster(unsigned long sector, unsigned long address, unsigned long spc);
void fatWriteCluster(unsigned long sector, unsigned long address, unsigned long spc); 
void MountShortFileName(char *buffer, struct dir_entry_d *entry);
void fs_check_disk();

//
// End.
//
