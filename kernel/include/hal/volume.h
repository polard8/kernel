/*
 * Arquivo: volume.h
 *
 * Descrição:
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
	
};
volumeinfo_t *volumeinfo;
volumeinfo_t *CurrentVolume;
volumeinfo_t *SystemVolume;
//...


//@todo: Fazer uma lista de volumes.??!!

int volume_init();


//
//fim.
//

