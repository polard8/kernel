

#ifndef __OBJECT_H
#define __OBJECT_H    1

/*
 ***********************************************
 * struct object_d:
 *     Object controle ...
 *     Estrutura para controle de objetos.
 *     Isso deve ficar no início de cada estrutura 
 *     para controlar a utilização do objeto por parte 
 * dos processos e threads.
 * 
 */

struct object_d 
{
    // haha !!
    // Objeto do tipo objeto.
    object_type_t objectType;
    object_class_t objectClass;


    int id; 
 
    int used;  
    int magic; 


    char *path;             // '/root/user/(name)'
    char __objectname[64];    // HOSTNAME_BUFFER_SIZE
    size_t objectName_len;    // len 
  

    //Lista de processos que possuem o objeto.
    int pidList[32];
    int pidCount;
    int currentPID;
   
 
    //endereços
    unsigned long obj_address;
    unsigned long obj_procedure;

    // Status do objeto.

    int token; //algum processo 'pegou' o objeto e esta usando.

    int task_id; //id da tarefa que pegou o processo.


	//int signaled;
	//struct process_d *waitListHead;
	
	//channel	
    //process
	//thread
	//window
	
	//continua...
};

// ??
// Repensar isso.
// #bugbug: Muito espaço. (#todo: deprecated this)
//struct object_d objects_km[256+1];  //objetos em kernel mode.
//struct object_d objects_um[256+1];  //objetos em user mode. 
//struct object_d objects_gui[256+1]; //objetos gráficos. 


// Se o gerenciador de recursos foi inicializado.
int g_object_manager_status;

//id do objeto atual
int g_current_object;

//id da lista ao qual o objeto atual pertence.
// object_km, object_um, object_gui. 
int g_current_list;


//
// prototypes ==========
//



#endif    



