/*
 * File: microkernel.h
 *
 * Descrição:
 *     Rotinas exportadas pelo /executive para os outros 2 módulos do kernel base.
 *
 *     Header da módulo "/microkernel" dentro do kernel base.
 *     Apenas gerência de processos,threads, scheduler, semáforo, ipc ...
 *
 * @todo: 
 *     Os serviços oferecidos por esse módulo aparecerão aqui 
 *     começando por 'sys_'.
 *
 * Histórico:
 *     Version 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 */


int microkernelStatus; 
 
 
//
// Protótipos.
// 
 
//inicializa o microkernel do kernel.
int init_microkernel();

	
//
// End.
//

