/*
 * File: pc\ipc\ipc.c 
 *
 * Descrição:
 *     IPCM - Inter-Process Communication Manager.
 *     IPC - Inter-Process Communication.
 *     MB - Módulos incluídos no Kernel Base.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *
 * Atribuições:
 *     + Comunicação entre processos e threads.
 *     + Mensagens.
 *     + Área de tranferência.
 *     + Semáforos. (temos um módulo para isso).
 *       ...
 *
 * @todo: Criar estruturas.
 * Obs: Haverá troca de mensagens entre processos e o compartilhamento de dados.
 * Vários métodos serão usados, entre eles o uso da fila de mensagens na estrutura 
 * da janela do processo ou do processo ou da thread e o uso de áreas compartilhadas
 * de memórias.
 * Devemos considerar a sincronização de acesso aos recursos. Para isso esse módulo
 * deverá interagir com o gerente de objetos, que estrutura os acessos aos objetos
 * concedendo permissões e contabilidade de acessos e utilizadores.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


//
// Variáveis internas.
//

//int ipcmStatus;
//int ipcmError;
//...




/*
 Um processo cliente enviou uma systemcall para o kernel solicitando
 enviar uma mensagem curta para um procedimento de ipc de um processo.
 O kernel olhará ná estrutura do processo receptor qual é o endereço
 do procedimento de ipc do processo recptor e efetuará um iret
 para esse procedimento de ipc.
 O processo receptor deve enviar um systemcall de recebimento de
mensagem que foi enviado via procedimento de ipc. 
 */
void *ipcProcedure( unsigned long callback, 
                    unsigned long msg1, 
					unsigned long msg2, 
					unsigned long msg3, 
					unsigned long msg4, 
					unsigned long flag, 
					unsigned long error)
{
	//@todo:
    return NULL;						
};



/*
 Um processo cliente enviou uma systemcall para o kernel solicitando
 enviar uma mensagem curta para um procedimento de ipc de um processo.
 O kernel olhará ná estrutura do processo receptor qual é o endereço
 do procedimento de ipc do processo recptor e efetuará um iret
 para esse procedimento de ipc.
 O processo receptor deve enviar um systemcall de recebimento de
mensagem que foi enviado via procedimento de ipc. 
 */
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
					unsigned long ext5 )
{
	//@todo:
    return NULL;						
};


/*
 * ipc_dispatch_message:
 *    Despacha mensagens entre processos.
 *
 */						  
int ipc_dispatch_message( unsigned long a, 
                          unsigned long b, 
						  unsigned long c, 
						  unsigned long d)
{

    //
	// @todo: BugBug rever esse endereço.
	//

	//#bugbug: Rever esse endereço.
    // PA_1b8000 = VA_900000 (comunication area)
	unsigned long *int_args  = (unsigned long *) 0x001B8000; 

    //sinaliza que existe uma mensages esperando processamento.	
	int_args[0] = (unsigned long) 1;    //status.
	
	//int_args[1] = (unsigned long) t->.procedure; //next proceddure
	int_args[2] = (unsigned long) a;    //arg1.
	int_args[3] = (unsigned long) b;    //arg2 (msg).
	int_args[4] = (unsigned long) c;    //arg3  (ch).
	int_args[5] = (unsigned long) d;    //arg4.

//
// Done.
//
done:
    return (int) 0;
};



/*
 * init_ipc:
 *    Inicializa o ipc, 
 *    criando as áreas de tranferência usadas e 
 *    habilitando o ipc. 
 *
 */
void init_ipc()
{  
    return;    //Não implemantada ainda.
};


/*
 *Constructor.
int ipcmIpcm()
{};
*/

/*
int ipcmInit()
{};
*/



//
//fim.
//

