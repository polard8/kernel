/*
 * File: include\execve\dd\sm\disk\volume.h
 *
 * Descrição:
 *     Gerenciador de volumes.
 *     Header para o Volume Manager.
 *     Gerência de volumes.
 *
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2018 - Some new structures.
 */

 
#define VOLUME_COUNT_MAX 16





/*
 *****************************************************
 * volume_type_t:
 *     Enumerando os tipos de volume.
 *
 */
typedef enum {
	
	VOLUME_TYPE_NULL,            // Null. 
	
	// Partição em disco físico.
	VOLUME_TYPE_DISK_PARTITION,  

	// Partição em disco físico.
	VOLUME_TYPE_VIRTUAL_DISK_PARTITION,  

    // Arquivo.
	// Um pequeno arquivo qualquer. Não tem MBR.
	// Esse foi carregado de algum disco.
	VOLUME_TYPE_FILE,           
	
	// Buffer.
	// Um pequeno buffer qualquer. Não tem MBR.
	// Obs: Esse não foi carregado de disco nenhum.
	// O volume 0, será desse tipo. (conductor://)
	VOLUME_TYPE_BUFFER
	
	//...
	
}volume_type_t;




/*
 ******************************************************
 * volumeinfo_d
 *
 * Volume info struct.
 * @todo: deve existir algum padrão para isso.
 */
struct volumeinfo_d
{
	object_type_t objectType;
	object_class_t objectClass;
		
    //
	// Volume info.
	//
	
	int id;  
	
	int used; 
	int magic; 
	
	char *name; 
	

	
	int flag;
	int error;
	
	//
	// File System Type
	//
	
	int file_system_type;
	
	
	//
	// VBR info. 
	//
	
    struct vbr_d *vbr;
	unsigned long Signature;   
	
	//
	// Hidden Sectors. (Quantos setores reservados antes da fat).
	//
	
    unsigned long HiddenSectors;	
	
	//
	// FATs.
	//
	int cFAT;  
	unsigned long szFAT;

	
	//
	// ROOT.
	//
	unsigned long szROOT;
	
	
	
//
	// Hidden Sectors. (Quantos setores reservados antes da fat, ou do vbr da primeira partição.).
	//
	
    //unsigned long HiddenSectors;	
	
    //
    // FAT.
    //
	
	//unsigned long FatType;              //FAT12, FAT16, FAT32, FATX16 or FATX32.	
    //unsigned long FatSectorStart;       //Starting sector of 1st FAT table.
    //unsigned long ActiveFatSectorStart; //Starting sector of active FAT table.
    //unsigned long NumberOfFats;         //Number of FAT tables.
    //unsigned long SectorsPerFat;        //Sectors per FAT table.

	
    //
	// ROOT.
	//
    //unsigned long RootDirSectorStart;   //Starting sector of the root directory (non-fat32).
    //unsigned long RootDirSectors;       //Number of sectors of the root directory (non-fat32).
   // unsigned long RootDirStartCluster;  //Starting cluster number of the root directory (fat32 only).

	//
	// DATA AREA.
	//
	//unsigned long DataSectorStart;      //Starting sector of the data area.
	
};


/*
 * volume_d:
 *     Estrutura para acesso rápido a volumes.
 *     Deve ser simples e com poucos elementos.
 */
struct volume_d
{ 
	object_type_t objectType;
	object_class_t objectClass;
	
	volume_type_t volumeType;
	
	int id;
	
	int used;
	int magic;
	
	//label
	char *name;
	
	//pathname
	char *cmd;
	
	//string usada no path para identificar o disco.
	//isso não existe.
    char path_string[32];  

    struct volumeinfo_d *volume_info;	
	
	struct disk_d *disk;
	
	struct volume_d *next;
};
struct volume_d VOLUMES[32];



void volumeShowCurrentVolume();
void *volume_get_volume_handle( int number );
void *volume_get_current_volume_info();
int volumeShowVolumeInfo( int descriptor );
int volume_init();


//
// End.
//

