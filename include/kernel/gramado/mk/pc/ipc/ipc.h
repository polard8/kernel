/*
 * File: ipc.h 
 *
 * Descrição:
 *     IPC - ( Inter-Process Comunication ).    
 *     Header do módulo IPC do microkernel.
 *
 * Ambiente:
 *     Kernel base.
 *
 * Obs:
 *     Tem áreas de memória que os processos podem compartilhar, e que o 
 * kernel pode compartilhar com os processos.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 */

 
typedef struct ipc_procedure_d ipc_procedure_t;
struct ipc_procedure_d
{
	//Object.
	object_type_t objectType;
	object_class_t objectClass;
	
	unsigned long callback;  //d (tiny)
	
	unsigned long msg1;   //c
	unsigned long msg2;   //b
	unsigned long msg3;   //a
	unsigned long msg4;   //g
	unsigned long flag;   //f
	unsigned long error;  //e (Cowgirl)
};
ipc_procedure_t *IpcProcedure;
//...


typedef struct ipc_procedureEx_d ipc_procedureEx_t;
struct ipc_procedureEx_d
{
	//Object.
	object_type_t objectType;
	object_class_t objectClass;	
	
	unsigned long callback;  //d (tiny)
	
	unsigned long msg1;   //c
	unsigned long msg2;   //b
	unsigned long msg3;   //a
	unsigned long msg4;   //g
	unsigned long flag;   //f
	unsigned long error;  //e (Cowgirl)
	
	//exts ...
	unsigned long ext1;  //d
	unsigned long ext2;  //c
	unsigned long ext3;  //b
	unsigned long ext4;  //a
	unsigned long ext5;  //g (Cowboy)
	
	//Monsters ... 
	//Não serão incluidos aqui, mas pertencem as outros estruturas
	//que se guiam por essa.
};
ipc_procedureEx_t *IpcProcedureEx;
//...
 
 
 
int ipcStatus; 


//
// Protótipos.
//

void *ipcProcedure( unsigned long callback, 
                    unsigned long msg1, 
					unsigned long msg2, 
					unsigned long msg3, 
					unsigned long msg4, 
					unsigned long flag, 
					unsigned long error);

void *ipcProcedureEx( unsigned long callback, 
                    unsigned long msg1, 
					unsigned long msg2, 
					unsigned long msg3, 
					unsigned long msg4, 
					unsigned long flag, 
					unsigned long error,
					unsigned long ext1,
					unsigned long ext2,
					unsigned long ext3,
					unsigned long ext4,
					unsigned long ext5 ); //Cowboy.


// inicializa o sistema de transferencia interprocessos.

void init_ipc (void);


//envia mensagens entreprocessos.

int 
ipc_dispatch_message ( unsigned long a, 
					   unsigned long b, 
					   unsigned long c, 
					   unsigned long d );



//
// End.
//

