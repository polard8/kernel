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

 
#define VOLUME_COUNT_MAX 1024



/*
 *****************************************************
 * volume_type_t:
 *     Enumerando os tipos de volume.
 */
typedef enum {
	
	VOLUME_TYPE_NULL,            
	
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
	
	struct disk_d *disk;
	
	struct volume_d *next;
};
struct volume_d *volume_vfs;             // volume 0
struct volume_d *volume_bootpartition;   // volume 1
struct volume_d *volume_systempartition; // volume 2
//#importante:
//Esses são os três volumes básicos do sistema 
//mesmo que o disco só tenha um volume, essas 
//estruturas vão existir.


//
// Lista de volumes.
//

unsigned long volumeList[VOLUME_COUNT_MAX];


void volumeShowCurrentVolumeInfo (void);

void *volume_get_volume_handle( int number );

void *volume_get_current_volume_info (void);

int volumeShowVolumeInfo( int descriptor );

int volume_init (void);


//
// End.
//

