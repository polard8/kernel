/*
 * File: ke.h
 *     Kernel External functions support.
 *     O objetivo é chamar rotinas que estão fora do kernel base.
 * As rotinas chamadas podem estar em servidores em user mode ou
 * em módulos em kernel mode.
 *
 * Histórico:
 *     Oct 2016 - Created.
 */


/*
 * Servers and Drivers:
 * ====================
 *
 * Chamadas aos módulos externos que estão em user mode.
 * São servers e drivers.
 * O Kernel pode chamá-los para uso próprio ou 
 * pode chamá-los para atender alguma solicitação
 * de cliente, que também está em user mode.
 * O Cliente chama solicida algum serviço de um Server
 * atravéz do kernel.
 *
 * @todo: Definir melhor o que deve ir para user modr e organizar.
 * por servidor por exemplo.
 */
 
#ifndef ____KE_H 
#define ____KE_H
 
//Informações sobre o kernel. módulo externo.
void KeInformation (void);   



#endif



//
// End.
//

