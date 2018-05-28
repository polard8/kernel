/*
 * File: sm\sys\signal.c
 *
 * Descrição:
 *     Signal Manager.
 *     Gerencial o uso de sinais.
 *
 * Versão: 1.0, 2016 - Created.
 */

/*
  Signal Manager: Gerencia os sinais recebidos e enviados pelos processos.
                 Os sinais enviados para o processo kernel serão atendidos
 na forma de requests. A rotina de request sinaliza os processo sobre a ocorrencia
 de eventos e toma deceisões relativas ao estado dos processos, se eles devem esperar
 ou proceguir etc...   
 
 Obs: Com sinais, os processo podem conversar um com o outro.

 Obs: Um sinal significa que rodará uma rotina específica de sinal que ativará
      um request do kernel além de rodar outros métodos.
      A variável Signal será interna aqui em signal.c, podendo ser manipulada
      somente por esse arquivo. Já as definições de sinal serão globais e públicas
      para que as aplicações possam utilizar sinais. O que não impede implementar
      sinais exclusivos para determnados módulos. (Isso parece ser muito legal:)).
      Para isso é só separa os sinais por grupos, um grupo para cada módulo,
      isso ajudaria a organizar os módulos por números além dar prioridade
      para alguns módulos.

 Os grupos de sinais:
 ===================
 Para simplificar usaremos apenas cinco grupos de sinais, são eles:

 0 - KernelSignal - Sinais usados pelo processo kernel e rotinas de muito privilégio.
 1 - HalSignal - Sinais utilizados pelo módilo /hal que lidam com hardware.
 2 - MicrokernelSignal - Sinais utilizados pelo módulo /microkernel. Atuam sobre processos e threads.
 3 - ExecutiveSignal - Sinais utilizados pelo móidulo /executive. Atuam sobre o sistema de uma forma geral.
 4 - UserSignal - Sinais utilizados pelos processos criados pelos usuários.

*/

#include <kernel.h>


/*
  @todo: (signals) 
  Interrupção de teclado.
  abort
  
  ...
  
 */



//
// Aqui degue uma definição interna dos números dos sinais que serão usados por cada grupo 
// de sinais.
//


//
//  0 - KernelSignal
//
#define KERNELSIGNAL_x 4000
//4000~4999
//...

//
// 1 - HalSignal
//
#define HALSIGNAL_x 3000
//3000~3999
//...

//
// 2 - MicrokernelSignal
//
#define MICROKERNELSIGNAL_x 2000
//2000~2999
//...

//
// 3 - ExecutiveSignal
//
#define EXECUTIVESIGNAL_x 1000
//1000~1999
//...

//
// 4 - UserSignal
//
#define USERSIGNAL_NULL 0
#define USERSIGNAL_KILLPROCESS 1
//0~999
//...


/*
enum signal_t {
	KernelSignal,  //0
	HalSignal,     //1
	MicrokernelSignal,  //3
	ExecutiveSignal,    //4
	UserSignal,         //5
};
*/


int Signal;



/*
 * signalSend:
 *     Envia um sinal para um processo.
 */
int signalSend( struct process_d *process, int signal )
{
	//SIGNAL_COUNT_MAX
	
	//Limit
    //if(signal >= 32){
	//	return 1;
	//}
	
	if(signal == 0){
		return 1;
	};
	
	//struct fail
	if( (void*) process == NULL ){
		return 1;
	}		
	
	//Ok
	if( (void*) process != NULL )
	{
		
		process->signal = (unsigned long) signal;
		return 0; 
	}
	
	//...
	
fail:
	return (int) 1;	
};


/*
 * signalInit:
 *     Inicialização do módulo de gerenciamento de sinais.
 *
 */
int signalInit()
{
    Signal = 0;	
	
	
done:	
	return (int) 0;
};


//
// Fim.
//

