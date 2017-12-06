/*
 * File: server.c  
 * 
 * Descrição:
 *      Gerenciamento de servidores.
 *      Gerencia os processos servidores que estão em user mode.
 *      @todo: Essas são as rotinas de gerenciamento de servidores 
 * oferecida pelo kernel base, porém o gerenciador de servidores
 * poderá ser um utilitário em user mode, que poderá usar as rotinas
 * oferecidads aqui.
 *      O Kernel faz ponte entre Clientes em user mode e servidores
 *      em user mode. O cliente em user mode solicita ao kernel serviços
 *      oferecidos por servidores que estão em user mode.
 *
 *      O kernel estabelece essa conexão cliente/servidor
 *      atravéz de mensagens. via interrupção.
 *      a interrupção é a 200. e é tratada pelo arquivo services.c.
 *
 *      Um forma de trocar mensagens de dados é atravéz dos canais. 
 *
 * Versão 1.0, 2015, 2016. 
 */

/*
A basic set of servers for a general-purpose microkernel includes 
file system servers, 
device driver servers, 
networking servers, 
display servers, 
and user interface device servers.

The necessary servers are started at system startup and provide services, 
such as file, network, and device access, to ordinary application programs.

display server
timer server
int fs_server();
int mm_server();
int xx_server();
*/


#include <kernel.h>


/*
 * init_systemserver:
 *     System server supprt.
 */
int init_systemserver()
{
    return (int) 0;  //Ainda não implementada.
};

/*
int serverInit();
int serverInit()
{
	return (int) 0;
};
*/

//
// Fim.
//

