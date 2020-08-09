/*
 * File: ke.h
 * 
 *     Kernel External functions support.
 *     It's gonna be used to call functions that are not
 * inside the base kernel.
 * 
 * History:
 *     2016 - Created by Fred Nora.
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


    int dummy_kexxxx;

#endif



//
// End.
//

