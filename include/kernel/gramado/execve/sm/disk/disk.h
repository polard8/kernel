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
 
 
 
#define DISK_COUNT_MAX 1024 //8



#define DISK_BYTES_PER_SECTOR 512 
//#define DISK_BYTES_PER_SECTOR 4096 
 
 
//macro
//#define CYLMAX(c)  ((c) > 1023 ? 1023 : (c))  


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
	
}disk_type_t;


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
	
	int id;
	
	int used;
	int magic;
	
	//Ponteiro para o nome do disco,
	//talvez não precise ser um ponteiro, pode ser um array.
	char *name;  
    
	struct disk_d *next;
};

//
// Lita de discos
//

unsigned long diskList[DISK_COUNT_MAX];



void diskShowCurrentDiskInfo();

int diskShowDiskInfo ( int descriptor );

void *disk_get_disk_handle( int number );
void *disk_get_current_disk_info();
int disk_init();
void init_test_disk();  //*teste de operação com disco. 

int get_ide_disk_info ( int port, unsigned long buffer, int master );
void show_ideports_info();
//
// End.
//

