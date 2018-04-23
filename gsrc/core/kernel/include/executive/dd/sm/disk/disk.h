/*
 * File: include\executive\dd\sm\disk\disk.h 
 *
 * Descrição:
 *     Gerenciador de discos. 
 *     Header para rotinas de operação com discos.
 *
 * Obs: 
 *     Part of hal.
 *
 *
 * Versão 1.0, 2015.
 */
 
 
 
#define DISK_COUNT_MAX 8
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
	// @todo #bugbug Aqui não deve ficar informações sobre volumes.
	// talvez um ponteiro para o volume principal e só isso.
	//
	
	
	
	//
	// Volume list.  x->Volumes[i].xxx
	//
	
	struct volumeinfo_d *Volumes; 
	
	//Navigation.
    struct diskinfo_d *next;	
};
diskinfo_t *CurrentDiskInfo; 
diskinfo_t *CurrentDisk;
diskinfo_t *diskinfo;
diskinfo_t *SystemDiskInfo;
//...


//
// Lita de discos
//

unsigned long diskList[DISK_COUNT_MAX];



void *disk_get_disk_handle( int number );
void *disk_get_current_disk_info();


int disk_init();
void init_test_disk();  //*teste de operação com disco. 


//
//fim.
//

