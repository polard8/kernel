// aspace.h



typedef enum {

    aspacetypeShared,
    aspacetypePersonal,

}aspace_type_t;



typedef struct aspace_d aspace_t;
struct aspace_d
{
    //Obs: Essa estrutura é para qualquer região da
	//memória física. A outra estrutura mm_block é
	//apenas para gerenciar áreas de memória alocadas 
	//dentro do heap do kernel.

	object_type_t  objectType;
	object_class_t objectClass;

	int used;
	int magic;

	aspace_type_t type;
	
	char *name;  //Qual é o nome desse Address Apace.
	//file *_file;   //Qual arquivo é referente à esse espaço.
	//metafile??

	unsigned long virtual_address;
	unsigned long physical_address;
	unsigned long size;  //Tamanho em bytes.
	
	//...
	
	
	//
	// @todo: Informações sobre os processos que estão utilizando
	//        essa área de memória.
	//
	
	//Lista de processos utilizando esse objeto.
	struct process_d *processListHead;
	//int processCount;
	
	// propriedades da região.
	// permissões de leitura e escrita.
	//informações sobre todos os arquivos associados com a região.
	
	//
	// Deve-se encadear as regições de memória em um árvore,
	// de forma a facilitar o acesso.
	// Obs: Acho que a estrutura de contas em bancos
    // cumpre esse papel.	
	//
	
	//?? @questionamento: Uma conta poderia pertencer à mais de um banco
	// ou devemos indicar aqui à que banco essa conta pertence.
	//struct bank_d *bank;
	
	

	//navegação.
    struct aspace_d *next;
};
struct aspace_d *ASpace;
//aspace_t *ASpace;
//...

