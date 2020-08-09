/*
 * File: init.h
 *
 * Descrição:
 *     Header da rotina de inicialização de partes básicas do sistema.
 *
 * Versão 1.0, 2015.
 */


/*
 * initialization_d:
 *     Estrutura para gerenciamento da inicialização do sistema.
 *     @todo: Mudar nome para initialization_d initialization_t. 
 */ 
typedef struct initialization_d initialization_t;
struct initialization_d
{
    //Fases do kernel.
    int phase1; 
	int phase2;
	int phase3;
	
	//Componentes principais.
	int hal;
	int microkernel;
	int executive;
	//int gramado;  //@todo: Esse ainda não foi implementado.
	
	//...
}; 
initialization_t Initialization;    //Obs: Não usando ponteiro.

 
//
// Protótipos.
// 


/*
 * init_architecture_dependent:
 *     Inicializa módulos que dependem da arquitetura da máquina.
 */

int init_architecture_dependent (void);


/*
 * init_architecture_independent:
 *     Inicializa módulos que são independentes da arquitetura da máquina.
 */    

int init_architecture_independent (void);


/*
 * init_globals:
 *     Inicializa globais do sistema.
 */     

void init_globals (void);


/*
 * init:
 *     Inicialização de partes básicas do sistema.
 */ 

int init (void);


//
// End.
//

