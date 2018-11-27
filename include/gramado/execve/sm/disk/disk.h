/*
 * File: include\execve\dd\sm\disk\disk.h 
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
 
 
 
#define DISK_COUNT_MAX 8
#define DISK_BYTES_PER_SECTOR 512 
//#define DISK_BYTES_PER_SECTOR 4096 
 
 
//macro
//#define CYLMAX(c)  ((c) > 1023 ? 1023 : (c))  



/*
 *****************************************************
 * disk_type_t:
 *     Enumerando os tipos de disk.
 *
 */
typedef enum {
	
	DISK_TYPE_NULL,            // Null. 
	
	DISK_TYPE_PATA,
	
	DISK_TYPE_PATAPI,
	
	DISK_TYPE_SATA,
	
	DISK_TYPE_SATAPI
	
}disk_type_t;


 
/*
 * diskinfo_d
 *
 * Disk info struct.
 *
 */ 
struct diskinfo_d
{ 
	object_type_t objectType;
	object_class_t objectClass;  
   
	
	//
	// Disk info.
	//
	
	int id;     
	
	int used;   
	int magic;  
	
	char *name; 
	
	
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
    //struct diskinfo_d *next;	
};

//diskinfo_t *diskinfo_conductor;
//diskinfo_t *CurrentDiskInfo; 
//diskinfo_t *CurrentDisk;
//diskinfo_t *diskinfo;
//diskinfo_t *SystemDiskInfo;
//...


/*
 * disk_d:
 *     Estrutura para acesso rápido a discos.
 *     Deve ser simples e com poucos elementos.
 */
struct disk_d
{ 
	object_type_t objectType;
	object_class_t objectClass;
	
	disk_type_t diskType;  // PATA  SATA ...
	
	int id;
	
	int used;
	int magic;
	
	//Ponteiro para o nome do disco,
	//talvez não precise ser um ponteiro, pode ser um array.
	char *name;  
	
	
	// informações com base na sondagem feita 
	// pelo driver de ide.
	
	//isso será válido se for um disco do controlador ide.
	//com isso é só checan na estrutura as informações do disco 
	//que está naquela porta.  ( ide_ports[i].xxx ) ...
	//#importante: checaremos todos os discos instalados,
	//... o bootloader terá que passar informações 
	//sobre o disco que ele fez o boot.
	//pois poderemos encontrar vários discos com uma partição ativa.
	//mas por enquanto vamos apenas criar uma estrutura de disco para cada 
	//disco encontrado.
	//então devemos seguir a seguinte ordem, primeiro detectamos os discos
	//da interface ide, e depois criamos uma estrutura de disco para 
	//cada disco encontrado.
	//então é na hora que encontramos o disco que inicializamos as estruturas 
	//de disco, sendo assim não podemos inicializar estruturas de disco, sem 
	//antes percebermos quais discos estão instalados.
	
	int current_ide_port;
	

    struct diskinfo_d *disk_info;	
	struct disk_d *next;
};
struct disk_d DISKS[32];


void diskShowCurrentDiskInfo();

int diskShowDiskInfo ( int descriptor );

void *disk_get_disk_handle( int number );
void *disk_get_current_disk_info();
int disk_init();
void init_test_disk();  //*teste de operação com disco. 



//
// End.
//

