/*
 * File: volume.h
 *
 * Descrição:
 *     Gerenciador de volumes.
 *     Header para o Volume Manager.
 *     Gerência de volumes.
 *
 *
 * Versão 1.0, 2015.
 */

 
#define VOLUME_COUNT_MAX 16


/*
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
	
	//callback , d
	
    //
	// Volume info.
	//
	
	int volumeId;  //c
	int volumeUsed; //b
	int volumeMagic; //a
	char *volumeName;    //g, Label.
	
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
volumeinfo_t *volumeinfo;
volumeinfo_t *CurrentVolume;
volumeinfo_t *SystemVolume;
//...


//
// Lista de volumes.
//



unsigned long volumeList[VOLUME_COUNT_MAX];

//@todo: Fazer uma lista de volumes.??!!

int volume_init();


//
//fim.
//

