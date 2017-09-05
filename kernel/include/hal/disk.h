/*
 * Arquivo: disk.h 
 *
 * Descrição:
 *     Header para rotinas de operação com discos.
 *     Header para o Volume Manager.
 *
 * Obs: 
 *     Part of hal.
 *
 *
 * Versão 1.0, 2015.
 */
 
 
 
#define DISK_COUNT_MAX 16
#define DISK_BYTES_PER_SECTOR 512 
//#define DISK_BYTES_PER_SECTOR 4096 
 
 
//macro
//#define CYLMAX(c)  ((c) > 1023 ? 1023 : (c))  
 
/*
 * diskinfo_d
 *
 * Disk info struct.
 *
 */ 
typedef struct diskinfo_d diskinfo_t; 
struct diskinfo_d
{ 
	object_type_t objectType;
	object_class_t objectClass;  
    
	//callback /d
	
	//
	// Disk info.
	//
	
	int diskId;     //c
	int diskUsed;   //b
	int diskMagic;  //a
	char *diskName; //g, label
	
	
	//unsigned long flag;  //f
	//unsigned long error; //e
	
    unsigned long BytesPerSector;       //Number of bytes per sector.
    unsigned long SectorsPerCluster;    //Number of sectors per cluster.
	
	
	//
	// MBR info. 
	//
    
    struct mbr_d *mbr;
	struct partition_table_d *PartitionTable; 
    unsigned long PartitionNumber; 	// Partition Number. (Qual das 4 partições é a partição ativa.)
	unsigned long Signature;     
	
	
	//
	// Hidden Sectors. (Quantos setores reservados antes da fat, ou do vbr da primeira partição.).
	//
	
    unsigned long HiddenSectors;	
	
    //
    // FAT.
    //
	
	unsigned long FatType;              //FAT12, FAT16, FAT32, FATX16 or FATX32.	
    unsigned long FatSectorStart;       //Starting sector of 1st FAT table.
    unsigned long ActiveFatSectorStart; //Starting sector of active FAT table.
    unsigned long NumberOfFats;         //Number of FAT tables.
    unsigned long SectorsPerFat;        //Sectors per FAT table.

	
    //
	// ROOT.
	//
    unsigned long RootDirSectorStart;   //Starting sector of the root directory (non-fat32).
    unsigned long RootDirSectors;       //Number of sectors of the root directory (non-fat32).
    unsigned long RootDirStartCluster;  //Starting cluster number of the root directory (fat32 only).

	//
	// DATA AREA.
	//
	unsigned long DataSectorStart;      //Starting sector of the data area.
	
	//
	// Volume list.  x->Volumes[i].xxx
	//
	
	struct volumeinfo_d *Volumes; 
	
	//Navigation.
    struct diskinfo_d *next;	
};
diskinfo_t *diskinfo;
diskinfo_t *CurrentDiskInfo;
diskinfo_t *SystemDiskInfo;
//...


int disk_init();
void init_test_disk();  //*teste de operação com disco. 


//
//fim.
//

