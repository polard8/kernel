/*
 * File: storage/disk.h 
 *
 * Descrição:
 *     Gerenciador de discos. 
 *     Header para rotinas de operação com discos.
 *
 * Obs: 
 *     Part of hal.
 *
 * 2015 - Created by Fred Nora
 * 2018 - IDE controller support by Nelson Cole.
 *
 */
 
 
 
#define DISK_COUNT_MAX 1024    //8

#define DISK_BYTES_PER_SECTOR  512 
//#define DISK_BYTES_PER_SECTOR 4096 
 
 
// MBR support.
#define  BS_JmpBoot       0  /* x86 jump instruction (3-byte) */
#define  BS_OEMName       2  /* OEM name (8-byte) */
#define  BPB_BytsPerSec  11  /* Sector size [byte] (WORD) */
#define  BPB_SecPerClus  13  /* Cluster size [sector] (BYTE) */
#define  BPB_RsvdSecCnt  14  /* Size of reserved area [sector] (WORD) */
#define  BPB_NumFATs     16  /* Number of FATs (BYTE) */
#define  BPB_RootEntCnt  17  /* Size of root directory area for FAT [entry] (WORD) */
#define  BPB_TotSec16    19  /* Volume size (16-bit) [sector] (WORD) */
#define  BPB_Media       21  /* Media descriptor byte (BYTE) */
#define  BPB_FATSz16     22  /* FAT size (16-bit) [sector] (WORD) */
#define  BPB_SecPerTrk   24  /* Number of sectors per track for int13h [sector] (WORD) */
#define  BPB_NumHeads    26  /* Number of heads for int13h (WORD) */
#define  BPB_HiddSec     28  /* Volume offset from top of the drive (DWORD) */
#define  BPB_TotSec32    32  /* Volume size (32-bit) [sector] (DWORD) */
#define  BS_DrvNum       36  /* Physical drive number for int13h (BYTE) */
#define  BS_NTres        37  /* WindowsNT error flag (BYTE) */
#define  BS_BootSig      38  /* Extended boot signature (BYTE) */
#define  BS_VolID        39  /* Volume serial number (DWORD) */
#define  BS_VolLab       42  /* Volume label string (8-byte) */
#define  BS_FilSysType   50  /* Filesystem type string (8-byte) */
#define  BS_BootCode     62  /* Boot code (448-byte) */
#define  BS_55AA         510  /* Signature word (WORD) */
#define  MBR_Table       446  /* MBR: Offset of partition table in the MBR */ 




//#define  PARTITION_ACTIVE_FLAG    0x80

 
//macro
//#define CYLMAX(c)  ((c) > 1023 ? 1023 : (c))  


// disco atual ??
int g_spc;               //sectors per cluster.(spc é variável.)



/*
 *****************************************************
 * disk_type_t:
 *     Enumerando os tipos de disk.
 */
 
typedef enum {

    DISK_TYPE_NULL,        	
    DISK_TYPE_PATA,
    DISK_TYPE_PATAPI,
    DISK_TYPE_SATA,
    DISK_TYPE_SATAPI
    //...

}disk_type_t;



// #Obs:
// Um disco pode ser físico ou virtual.
// Um disco virtual também pode ter muitos volumes virtuais.

typedef enum {

    DISK_CLASS_NULL,
    DISK_CLASS_PHYSICAL,
    DISK_CLASS_VIRTUAL

}disk_class_t;






/*
 * mbr_d:
 *     ? para obter informações sobre o disco.
 *     Porém devemos ter um boot block mais completo.
 */ 

// #bugbug
// É desnecessário ter isso dentro do kernel.
// Deletar.

struct mbr_d
{

/*
	//jmp code (3 bytes)
	
	//os name 
	//Sistem info. 
    char OEM_ID[5];  //"NORA "
    char VERSION[3]; //"1.0"
	
	//bpb 
	  
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
	char VolumeLabel[11];           // db "FREDNORA8MB"
	char SystemID[8];               // db "FAT16   "		
	
	//PointerTable
	//unsigned short SystemName;
	//unsigned short SystemVersion;
	//unsigned short SystemBPB;
	//unsigned short SystemSignature;
	
	//Partition Table
	//unsigned long p0[3];
	//unsigned long p1[3];
	//unsigned long p2[3];
	//unsigned long p3[3];
	
	//Signature.
	unsigned short Signature;
*/
}; 
struct mbr_d *mbr; 



/*
 * partition_table_d:
 *     Structure for partition table.
 */ 
struct partition_table_d
{    
    unsigned char boot_indicator; //80h active
    unsigned char start_chs[3];
    unsigned char partition_type;
    unsigned char end_chs[3];
    unsigned long start_sector;
    unsigned long partition_size; //in sectors.
};
struct partition_table_d *partition; 



//As informações na partition table apresentadas na forma de 'char'.  
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
struct partition_table_chars_d *partition_chars; 







/*
 ***************************************************
 * disk_d:
 *     Estrutura para acesso rápido a discos.
 *     Deve ser simples e com poucos elementos.
 */

struct disk_d
{ 
    object_type_t objectType;
    object_class_t objectClass;

    disk_type_t diskType;
    disk_class_t diskClass;

    int used;
    int magic;


    int id;                 // ID na lista de discos.
    char boot_disk_number;  // ID herado do boot block.


    //#todo
    // se está funcionando ... se está inicializado ...
    //int status;
    
    //#todo
    // que tipo de operação esta sendo realizada. ou nenhuma.
    // se ele está ocupoado o escretor terá que esperar.
    //int state;

    // Qual processo está usando.
    pid_t pid;


    // #todo
    // contador de processos usando o disco

	// Ponteiro para o nome do disco,
    // Talvez não precise ser um ponteiro, pode ser um array.
    char *name;  


    uint8_t channel;
    uint8_t dev_num;
    
    // Mais: bpb.
    // ...

    struct disk_d *next;
};

struct disk_d *____boot____disk;


// Disk list.
// Essa lista é preenchida pelo driver de IDE.

unsigned long diskList[DISK_COUNT_MAX];



//show info for all disks in the list.
void disk_show_info (void);


void diskShowCurrentDiskInfo (void);

int diskShowDiskInfo ( int descriptor );

void *disk_get_disk_handle( int number );

void *disk_get_current_disk_info (void);

int disk_init (void);

//*teste de operação com disco.
void init_test_disk (void);   

int get_ide_disk_info ( int port, unsigned long buffer, int master );

void show_ideports_info (void);


//
// End.
//

