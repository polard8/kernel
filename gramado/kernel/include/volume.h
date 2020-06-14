/*
 * File: storage/volume.h
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

char *current_volume_string;

// volume atual ??
// Tipo de sistema de arquivos, fat16, ext2 ...
int g_currentvolume_filesystem_type;   //use this one.


// volume atual do tipo fat???
// Se é fat32, 16, 12.
int g_currentvolume_fatbits;



/*
 *****************************************************
 * volume_type_t:
 *     Enumerando os tipos de volume.
 */

typedef enum {


    VOLUME_TYPE_NULL,            

    // Partição em disco físico.
    VOLUME_TYPE_DISK_PARTITION,  

    // Partição em disco virtual.
    VOLUME_TYPE_VIRTUAL_DISK_PARTITION,  

    // Arquivo.
    // Um arquivo qualquer. Sem formatação.
    VOLUME_TYPE_RAW,           

    // Buffer.
    // Um arquivo qualquer. Sem formatação.
    // Usado por banco de dados.
    VOLUME_TYPE_BUFFER,

    // Partição de swap.
    VOLUME_TYPE_SWAP

    //...

}volume_type_t;



/*
 * vbr_d:
 *     Structure for VBR parameters.
 */  

struct vbr_d
{
	//copiar mbr, é parecido;
}; 
struct vbr_d *vbr; 
 



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
    
    //filesystem_type_t filesystemType;

    int id;

    int used;
    int magic;

    
    //
    // strings
    //


    //label
    char *name;

    //pathname
    char *cmd;

    //string usada no path para identificar o disco.
    //isso não existe.
    char path_string[32];  



    // Se o volume tiver um sistema de arquivos.
    // See: fs.h
    struct filesystem_d *fs;



    struct disk_d *disk;

    struct volume_d *next;
};

struct volume_d *volume_vfs;             // volume 0
struct volume_d *volume_bootpartition;   // volume 1
struct volume_d *volume_systempartition; // volume 2
// ...



//#importante:
//Esses são os três volumes básicos do sistema 
//mesmo que o disco só tenha um volume, essas 
//estruturas vão existir.


//
// Lista de volumes.
//

unsigned long volumeList[VOLUME_COUNT_MAX];


//show info for all volumes in the list.
void volume_show_info (void);

void volumeShowCurrentVolumeInfo (void);

void *volume_get_volume_handle( int number );

void *volume_get_current_volume_info (void);

int volumeShowVolumeInfo( int descriptor );

int volume_init (void);


//
// End.
//

