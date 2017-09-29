/*
 * File: ram\dspace.h 
 * 
 * Disk Space.
 *      
 * Obs: O lugar natural desse disco seria na classe de dispositivos, certo ?
 *      Mas ficará aqui, porque tem uma grande realção com memória ram,
 *      pois são desses endereços de disco que sairão as páginas usadas nas contas
 * de páginas.  
 */

 
typedef enum {
	dspacetypeShared,
	dspacetypePersonal,
}dspace_type_t;


typedef struct dspace_d dspace_t;
struct dspace_d
{
	//Object.
	object_type_t objectType;
	object_class_t objectClass;
	
	int used;
	int magic;

	dspace_type_t type;
	
	char *name;  //Qual é o nome desse Disk Apace.
	FILE file;   //Qual arquivo é referente à esse espaço.
	//metafile??	
	
	//Endereço correspondente na memória ram.
	unsigned long virtual_address;
	unsigned long physical_address;
	
	//Tamanho em setores..
	unsigned long size;  	
	unsigned long sector_size;   //Tamanho de um setor dado em bytes
	
	
	//Lista de processos utilizando esse objeto.
	struct process_d *processListHead;
	//int processCount;	
	
	//...
	
	//navegação.
	struct dspace_d *next;
};
dspace_t *DSpace;
//...
