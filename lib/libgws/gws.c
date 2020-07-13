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


// #test
// Tentando deixar o buffer aqui e aproveitar em mais funções.
char __gws_message_buffer[512];


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

// #todo
// Criar a função gws_create_window usando as funções:
// gws_createwindow_request e gws_createwindow_response
//


// create window support
int 
gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color );
int 
gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.



    char *name = "Window name 1";

   

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gwst: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = left; //120;   //x
        message_buffer[5] = top; //120;   //y
        message_buffer[6] = width; //480;   //w
        message_buffer[7] = height; //320;   //h
        
        message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, __gws_message_buffer, sizeof(__gws_message_buffer), 0);
       
        if(n_writes>0)
           break;
    }


    return 0; 
}




//create window support.
int gws_createwindow_response(int fd);
//response
int gws_createwindow_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   
    int n_reads = 0;    // For receiving responses.

    //
    // Waiting for response. ==================
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    gws_debug_print ("gwst: Waiting ...\n");      

    int y;
    for(y=0; y<15; y++)
        gws_yield();   // See: libgws/


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // read
    //

    // #debug
    gws_debug_print ("gwst: reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __gws_message_buffer, sizeof(__gws_message_buffer), 0 );
    
    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
         gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("gwst: recv fail.\n");
        printf ("gwst: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }


    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        case GWS_SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            goto response_loop;
            break;
            
        // Reply!
        case GWS_SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;
            
        case GWS_SERVER_PACKET_TYPE_EVENT:
            goto process_event;
            //goto response_loop;
            break;
            
        case GWS_SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("gws: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default:
            goto response_loop;
            break; 
    };

//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    gws_debug_print ("gws: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("gwst: bye\n"); 
    printf ("gws: Window ID %d \n", message_buffer[0] );
    //printf ("gwst: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("gws: We got an event\n"); 
    return 0;

}



// Talvez vamos retonar o descritor
// dado pelo servidor.
void *
gws_create_window_using_socket (
    int fd, 
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

    //#todo
    // use more arguments.
    gws_createwindow_request(fd, 
        x, y, width, height, color);
    gws_createwindow_response(fd); 
    
    return NULL;
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
   //#todo
   gws_debug_print ("gws_reboot: [TODO]\n");
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


/*
void gws_yield_n_times (unsigned long n);
void gws_yield_n_times (unsigned long n)
{
    int i=0;
    for(i=0;i<n;i++)
        gws_system_call(265,0,0,0); 
}
*/


//
// End.
//







