
// xproc.h


#ifndef ____XPROC_H
#define ____XPROC_H


/*
 * XPROC_SEND_MESSAGE
 *     Envia uma mensagem para a thread de controle da janela 
 * com o foco de entrada.
 */

int 
XPROC_SEND_MESSAGE ( struct window_d *window, 
                     int msg, 
                     unsigned long long1, 
                     unsigned long long2 );


/*
 * system_procedure:
 *     O procedimento default do sistema.
 *     Obs: Essa rotina está em x/xproc.c.  
 */
 
unsigned long 
system_procedure ( struct window_d *window, 
                   int msg, 
                   unsigned long long1, 
                   unsigned long long2 );

#endif   

