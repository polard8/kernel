

// File: gws.c
// gws - client side

// Devemos incluir o objeto gws.o nos aplicativos para fazermos
// as chamadas ao servidor.


// #todo
// Connection support.
// O support para conexões deve ser uma bibliteca
// separada, pois assim os processos cliente podem usar essa
// biblioteca para se concetarem com outros servidores
// do mesmo tipo.



//libcore
#include <types.h>  
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <heap.h>   


//libgws
#include "include/gws.h"  


int __gws__desktop__id;
int __ws__pid;



// system call.
void *gws_system_call ( unsigned long a, 
                        unsigned long b, 
                        unsigned long c, 
                        unsigned long d )
{
    int __Ret = 0;

    //System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}


// Initialize the library.
int gws_initialize_library(void)
{

    // Pega o id do desktop atual.
    // ?? Ou o qual o processo pertence ??
    __gws__desktop__id = (int) gws_system_call (519,0,0,0);
   
    
    // Get ws PID for a given desktop
    __ws__pid = (int) gws_system_call ( 512,
                         (unsigned long) __gws__desktop__id,
                         (unsigned long) __gws__desktop__id,
                         (unsigned long) __gws__desktop__id );    
        
        
    
    if (__ws__pid<0)
        return -1;
        
        
        // Send message.
        // Envia uma mensagem pedindo para o ws emitir um hello!
        // msg = 1000;

        //vamos criar uma chamada semelhante a essa.

        // IN: PID, window, msg, long1, long2
        gws_send_message_to_process ( __ws__pid, 
            NULL, 1000, 0, 0 );  
    

        // put some pixel in this position.
        gws_send_message_to_process ( __ws__pid, 
            NULL, 2000, 40, 40 );  

        // refresh screen
        gws_send_message_to_process ( __ws__pid, 
            NULL, 2020, 0, 0 );     
        
    return 0;
}




// Services.
// IN: service number, ...
void *gws_services ( int service,
                     unsigned long arg2,
                     unsigned long arg3,
                     unsigned long arg4 )
{

   if (service<0)
       return NULL;


    switch (service)
    {
        // Say hello !
        case 1:
            
            break;
    };


    return NULL;
}



/*
 **********************************************************
 * gws_send_message_to_process:
 *     Envia uma mensagem para a thread de controle de um dado processo.
 *     Dado o PID.
 */

// #obs
// Dá pra criar uma função semelhante, que use estrutura ao invés 
// de buffer.

int
gws_send_message_to_process ( int pid, 
                              struct window_d *window, 
                              int message,
                              unsigned long long1,
                              unsigned long long2 )
{

    unsigned long message_buffer[5];


    if ( pid<0 )
        return -1;


    message_buffer[0] = (unsigned long) window;
    message_buffer[1] = (unsigned long) message;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;
    //...

    return (int) gws_system_call ( 112 , 
                    (unsigned long) &message_buffer[0], 
                    (unsigned long) pid, 
                    (unsigned long) pid );
}


/*
 *************************************
 * gws_send_message_to_thread:
 *     Envia uma mensagem para uma thread.
 */

int 
gws_send_message_to_thread ( int tid, 
                             struct window_d *window, 
                             int message,
                             unsigned long long1,
                             unsigned long long2 )
{

    unsigned long message_buffer[5];

    if (tid < 0)
        return -1;


    message_buffer[0] = (unsigned long) window;
    message_buffer[1] = (unsigned long) message;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;
    //...


    return (int) gws_system_call ( 117 , 
                     (unsigned long) &message_buffer[0], 
                     (unsigned long) tid, 
                     (unsigned long) tid );
}

void gws_reboot(void)
{
}


// Talvez vamos retonar o descritor
// dado pelo servidor.
void *gws_create_window ( unsigned long type,        //1, Tipo de janela (popup,normal,...)
                          unsigned long status,      //2, Estado da janela (ativa ou nao)
                          unsigned long view,        //3, (min, max ...)
                          char *windowname,          //4, Título.                          
                          unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
                          unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
                          unsigned long width,       //7, Largura da janela.
                          unsigned long height,      //8, Altura da janela.
                          struct window_d *pWindow,  //9, Endereço da estrutura da janela mãe.
                          unsigned long onde,        //10, Ambiente.( Est� no desktop, barra, cliente ...)
                          unsigned long clientcolor, //11, Cor da área de cliente
                          unsigned long color )      //12, Color (bg) (para janela simples).
 
{
    return NULL;
}



	

