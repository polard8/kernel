/*
 * File: ob/object.c
 *
 * Descrição:
 *   #importante: 
 *   O gerente de arquivos será o manipulador de arquivos usados pelo sistema 
 * de arquivos. Lembrando que o assim como no UNIX tudo é considerado um 
 * arquivo, aqui, tudo é considerado um objeto. Então o sistema de arquivos 
 * manipulará os objetos. Mas ele poderá chama-los de arquivos se quiser. 
 *
 *    Object manager, módulo do tipo MB - Módulos incluídos no Kernel Base.
 *
 * Arquivo principal do módulo sm\ob do executive.
 *    
 * Gerencia os recursos do sistema. Criando, abrindo, fechando objetos e 
 * concedendo ou negando o acesso a ele.
 *
 *    Para gerenciar o uso de um recurso o kernel faz utiliza semaforos, 
 * mutexes.
 * 
 * Ex: Um fs é um objeto, que tem seu channel pra receber mensagens e uma 
 * aplicação solicita alguma coisa do sistema de arquivos através de um 
 * canal de comunicação. O fs pode estar indisponível no momento. 
 * A aplicação cliente pode ser um cliente não valido.
 *
 * Obs: 
 * O object manager é o melhor lugar pra implantar rotinas de segurança.
 *
 * Claro que o Object Manager deve chamar as rotinas do módulo de segurança, 
 * mas o Object Manager receberá solicitações de usuários e processos para 
 * manipular objetos, então deve decidir se o usuário, grupo ou processo 
 * tem autorização para manipular o objeto.
 *
 * Obs: 
 * Uma estrutura de objeto deve conter indicações de que processo ou usuário 
 * está manipulando o objeto no momento. Também um número máximo de processos 
 * que pode ficar na fila para usar esse objeto. A fila decrementa e quando 
 * chegar a zero, esse objeto pode ser fechado, caso não seja um objeto físico, 
 * como no caso de discos.
 *
 *IMPORTANTE: 
 * Que ninguém duvide da importância do gerente de objetos. Pois os recursos 
 * do sistema são configurados como objetos, então para um processo ter acesso 
 * à algum recurso do sistema terá que solicitar o recurso ao gerente de objetos, 
 * que pode interagir com o sistema de segurança para ver se o processo ou 
 * usuário tem permissão para utilizar o recurso desejado. 
 *
 * @todo: 
 * Ainda há muito pra aprender sobre objetos e gerencia de objetos. 
 * Tendo em vista que o conceito de objetos para kernel mode em C e para 
 * User Mode com linguagem de alto nível é bem diferente.
 *
 * 2015 - Created by Fred Nora.
 */



#include <kernel.h>



/*
 *******************************************
 * init_object_manager:
 *     Inicializa o gerenciador de objetos.
 */

int init_object_manager (void)
{
    int Status = 0;


//#ifdef EXECVE_VERBOSE	
	//printf("Initializing Object Manager..\n");
//#endif	
    
    // ??
    g_current_object = 0;         //objeto numero 0
    g_current_list = 0;            //lista de objetos em kernel mode.



   // #todo: 
   // Initialize object List.

    //Inicializado.
	g_object_manager_status = 1;
	g_module_objectmanager_initialized = 1;
	
//#ifdef EXECVE_VERBOSE	
	//printf ("Done\n");
//#endif	


    return (int) Status;
}


//
// End.
//

