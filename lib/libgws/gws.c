/*
 * File: gws.c
 * 
 *     gws - client-side library for gws window server.
 *     gws is a window server running in ring3, and this is
 *  a library used by the apps.
 *     
 */


// Devemos incluir o objeto gws.o nos aplicativos para fazermos
// as chamadas ao servidor.


// #todo
// Connection support.
// O support para conexões deve ser uma bibliteca
// separada, pois assim os processos cliente podem usar essa
// biblioteca para se concetarem com outros servidores
// do mesmo tipo.



// libc03
#include <types.h>  
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <heap.h>   


// libgws
#include "include/connect.h"  
#include "include/gws.h"  



// System call.
void *
gws_system_call ( 
    unsigned long a, 
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


// Debug vai serial port. (COM1)
void gws_debug_print (char *string)
{
    gws_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}


// Initialize the library.
int gws_initialize_library (void)
{
    int status = -1;
    
    
    status = gws_initialize_connection();    

    if(status<0){
        gws_debug_print("gws_initialize_library: fail\n");
        return -1;
    }


    return 0;
}




// Services.
// IN: service number, ...
void *
gws_services ( 
    int service,
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
 ***********************
 * gws_send_message_to_process:
 *     Envia uma mensagem para a thread de controle de um dado processo.
 *     Dado o PID.
 */

// #obs
// Dá pra criar uma função semelhante, que use estrutura ao invés 
// de buffer.

int
gws_send_message_to_process ( 
    int pid, 
    int window, 
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
gws_send_message_to_thread ( 
    int tid, 
    int window, 
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
   //
}


// Talvez vamos retonar o descritor
// dado pelo servidor.
void *
gws_create_window ( 
    unsigned long type,        //1, Tipo de janela (popup,normal,...)
    unsigned long status,      //2, Estado da janela (ativa ou nao)
    unsigned long view,        //3, (min, max ...)
    char *windowname,          //4, Título.                          
    unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
    unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       //7, Largura da janela.
    unsigned long height,      //8, Altura da janela.
    int parentwindow,  //9, Endereço da estrutura da janela mãe.
    unsigned long onde,        //10, Ambiente.( Est� no desktop, barra, cliente ...)
    unsigned long clientcolor, //11, Cor da área de cliente
    unsigned long color )      //12, Color (bg) (para janela simples).
 
{

    int n_writes = 0;   // For sending requests.
    int n_reads = 0;    // For receiving responses.

    unsigned long buffer;



    buffer = (unsigned long) gws_get_message_buffer();

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) buffer;   

    int client_fd = -1;
    
    int s=-1;
    
    s = gws_get_connect_status();

    if (s != 1){
        gws_debug_print("gws_create_window: Not connected\n");
        return NULL;
    }
    
    
    client_fd = gws_get_client_fd();
    
    if (client_fd < 0){
        gws_debug_print("gws_create_window: client fd fail\n");
        return NULL;
    }

    
    while(1){

        //create window        
        
        // msg header.
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg
        message_buffer[2] = 0;       // long1 (Response)
        message_buffer[3] = 0;       // long2
        
        // Extra
        message_buffer[4] = x;       // x
        message_buffer[5] = y;       // y
        message_buffer[6] = width;   // w
        message_buffer[7] = height;  // h
        message_buffer[8] = color;   // color

        // ...

        n_writes = write ( client_fd, 
                       message_buffer, 
                       sizeof(message_buffer) );
                       
        //send(client_fd , hello , strlen(hello) , 0 ); 
       
        // Se foi possível enviar, então não tentaos novamente.
        if(n_writes>0)
           break;
    };
    
    // #todo
    // Read the response.
    
    
    __again:
    n_reads = read ( client_fd, message_buffer, sizeof(message_buffer) );
    // Não vamos insistir num arquivo vazio.
    if (n_reads<=0){
        gws_yield();
        goto __again;
    }
    
    // O que lemos não era uma resposta.
    // Isso não deveria acontecer.
    // Se a mensagem não é uma resposta, lemos novamente.
    if (message_buffer[1] != 4000){
        gws_yield();
        goto __again;
    }
    

    // The response is the long1in the header of the 
    // buffer.

    return (void *) message_buffer[2];   // The response.
}



// Yield thread.
void gws_yield (void)
{
    gws_system_call(265,0,0,0); 
}


//
// End.
//







