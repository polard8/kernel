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
typedef struct volumeinfo_d volumeinfo_t; 
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
volumeinfo_t *volumeinfo_vfs;
volumeinfo_t *volumeinfo_bootpartition;
volumeinfo_t *volumeinfo_systempartition;
//...



/*
 * volume_d:
 *     Estrutura para acesso rápido a volumes.
 *     Deve ser simples e com poucos elementos.
 */
typedef struct volume_d volume_t; 
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

    struct volumeinfo_d *volume_info;	
	
	struct disk_d *disk;
	
	struct volume_d *next;
};
//@todo: Isso está bom, não mexer.
volume_t *volume_vfs;             // volume 0
volume_t *volume_bootpartition;   // volume 1
volume_t *volume_systempartition; // volume 2

// Observação o volume atual será uma variável global.  


//
// Lista de volumes.
//

unsigned long volumeList[VOLUME_COUNT_MAX];



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


void volumeShowCurrentVolume();
void *volume_get_volume_handle( int number );
void *volume_get_current_volume_info();
int volumeShowVolumeInfo( int descriptor );
int volume_init();


//
// End.
//

