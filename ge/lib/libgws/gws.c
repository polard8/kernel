/*
 * File: gws.c
 * 
 *     gws - client-side library for gws window server.
 *     gws is a window server running in ring3, and this is
 *  a library used by the apps.
 *     
 */

// Devemos incluir o objeto gws.o nos aplicativos 
// para fazermos as chamadas ao servidor.


// #todo
// Connection support.
// O support para conexões deve ser uma bibliteca
// separada, pois assim os processos cliente podem usar essa
// biblioteca para se concetarem com outros servidores
// do mesmo tipo.



// rtl
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


//
// == prototyes (internals) ==========================================
//


// == Change window position ==========================
int 
__gws_change_window_position_request ( 
    int fd, int window, unsigned long x, unsigned long y );
int 
__gws_change_window_position_reponse ( int fd );



// == Resize window ==========================
int 
__gws_resize_window_request ( 
    int fd, int window, unsigned long w, unsigned long h );
int 
__gws_resize_window_reponse ( int fd );


// == Redraw window ==========================
int 
__gws_redraw_window_request ( int fd, int window, unsigned long flags );
int 
__gws_redraw_window_reponse ( int fd );


// == Refresh Window ==========================
int 
__gws_refresh_window_request ( int fd, int window );
int 
__gws_refresh_window_reponse ( int fd );


// == Create Window ==========================
int 
__gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color,
    unsigned long type,
    unsigned long parent,
    char *name );
int __gws_createwindow_response(int fd);




// == plot point ===============================================
int 
__gws_plot0_request (
    int fd,
    unsigned long x,
    unsigned long y,
    unsigned long z,
    unsigned long color );
int __gws_plot0_response (int fd);  



// == plot cube ======================================================
int __gws_plotcube_request ( int fd, struct gr_cube_d *cube );
int __gws_plotcube_response (int fd);



// == plot rectangle ======================================================
int __gws_plotrectangle_request ( int fd, struct gr_rectangle_d *rect );
int __gws_plotrectangle_response (int fd);




// == Draw Char ==========================
int 
__gws_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    unsigned long c );
int __gws_drawchar_response(int fd);


// == Draw text ==========================
int 
__gws_drawtext_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    char *string );
int __gws_drawtext_response(int fd);



// == ... ==========================



//
// == Functions ====================================================
//


// System call.
// System interrupt.
    
void *gws_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    int __Ret = 0;

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}


// Debug via serial port. (COM1)
void gws_debug_print (char *string)
{
    gws_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}


/*
 ******************************** 
 * gws_initialize_library:
 *     
 */

// Initialize the library.

int gws_initialize_library (void){

    // PID do window server.
    int wsPID = -1;
    

    wsPID = gws_initialize_connection();    

    if (wsPID < 0){
        gws_debug_print("gws_initialize_library: Fail\n");
        return -1;
    }

    // #todo:
    // #importante
    // We need to alloc memory to the CurrentEvent struct.
    // So we need the libc support. 
    // Check the compilation and include the libc. ???
    
    //CurrentEvent = (void *) malloc(sizeof(struct gws_event_d));
    

    return 0;
}



//
// == Helper functions ====================================================
//


int 
__gws_refresh_window_request ( int fd, int window )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.

    //char *name = "Window name 1";

    //
    // Send request.
    //

    // #debug
    gws_debug_print ("__gws_refresh_window_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = window;  // window. 
        message_buffer[1] = 1006;    // Refresh window
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}


int 
__gws_refresh_window_reponse ( int fd )
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
    gws_debug_print ("__gws_refresh_window_reponse: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_refresh_window_reponse: Reading ...\n"); 


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

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
        gws_debug_print ("__gws_refresh_window_reponse: recv fail.\n");
        printf          ("__gws_refresh_window_reponse: recv fail.\n");
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
            gws_debug_print ("__gws_refresh_window_reponse: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_refresh_window_reponse: We got an event\n"); 
    return 0;
}


int 
__gws_redraw_window_request ( int fd, int window, unsigned long flags )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.

    //char *name = "Window name 1";

    //
    // Send request.
    //

    // #debug
    gws_debug_print ("__gws_redraw_window_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = window;  // window. 
        message_buffer[1] = 1007;    // Redraw window
        message_buffer[2] = flags;
        message_buffer[3] = 0;
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}


int 
__gws_redraw_window_reponse ( int fd )
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
    gws_debug_print ("__gws_redraw_window_reponse: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_redraw_window_reponse: Reading ...\n");      

    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

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
        gws_debug_print ("__gws_redraw_window_reponse: recv fail.\n");
        printf          ("__gws_redraw_window_reponse: recv fail.\n");
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
            gws_debug_print ("__gws_redraw_window_reponse: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_redraw_window_reponse: We got an event\n"); 
    return 0;
}


int 
__gws_change_window_position_request ( 
    int fd, 
    int window, 
    unsigned long x, 
    unsigned long y )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.

    //char *name = "Window name 1";

    //
    // Send request.
    //

    // #debug
    gws_debug_print ("__gws_change_window_position_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = window;  // window. 
        message_buffer[1] = 1009;    // Refresh window
        message_buffer[2] = x;       // x
        message_buffer[3] = y;       // y
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd,
                        __gws_message_buffer, 
                        sizeof(__gws_message_buffer), 
                        0 );

        if (n_writes>0){ break; }
    }

    return 0; 
}



int 
__gws_change_window_position_reponse ( int fd )
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
    gws_debug_print ("__gws_change_window_position_reponse: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_change_window_position_reponse: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );
    
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
        gws_debug_print ("__gws_change_window_position_reponse: recv fail.\n");
        printf          ("__gws_change_window_position_reponse: recv fail.\n");
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
            gws_debug_print ("__gws_change_window_position_reponse: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_change_window_position_reponse: We got an event\n"); 
    return 0;
}



//
// ======================================================
//

int 
__gws_resize_window_request ( 
    int fd, 
    int window, 
    unsigned long w, 
    unsigned long h )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.

    //char *name = "Window name 1";

    //
    // Send request.
    //

    // #debug
    gws_debug_print ("__gws_resize_window_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = window;  // window. 
        message_buffer[1] = 1008;    // Resize window
        message_buffer[2] = w;       // x
        message_buffer[3] = h;       // y
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}



int 
__gws_resize_window_reponse ( int fd )
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
    gws_debug_print ("__gws_resize_window_reponse: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_resize_window_reponse: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );
    
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
        gws_debug_print ("__gws_resize_window_reponse: recv fail.\n");
        printf          ("__gws_resize_window_reponse: recv fail.\n");
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
            gws_debug_print ("__gws_resize_window_reponse: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_resize_window_reponse: We got an event\n"); 
    return 0;
}



//
// ====================================================================
//

int 
__gws_plot0_request (
    int fd,
    unsigned long x,
    unsigned long y,
    unsigned long z,
    unsigned long color )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.
    
    //char *name = "Window name 1";


    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gws_drawchar_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 2040;    // msg (plot point)
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        // ...
        
        // os argumentos para rotinas graficas começam em '10'.
        // Sempre começa com x,y,z e color ...
        
        message_buffer[10] = x;
        message_buffer[11] = y; 
        message_buffer[12] = z; 
        message_buffer[13] = color; 
        // ...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}


//response
int __gws_plot0_response (int fd)
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
    gws_debug_print ("__gws_plot0_response: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_plot0_response: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );
    
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
        gws_debug_print ("__gws_plot0_response: recv fail.\n");
        printf          ("__gws_plot0_response: recv fail.\n");
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
            gws_debug_print ("__gws_plot0_response: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_plot0_response: We got an event\n"); 
    return 0;
}


//
// =============================
//
//cube

int __gws_plotcube_request ( int fd, struct gr_cube_d *cube )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.
    
    //char *name = "Window name 1";


    if ( (void*) cube == NULL )
        return -1;


    //
    // Send request.
    //


    // #debug
    gws_debug_print ("__gws_plotcube_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 2041;    // msg (plot cube)
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        // ...
        
        // os argumentos para rotinas graficas começam em '10'.
        // Sempre começa com x,y,z e color ...
        
        // south
        message_buffer[10] = cube->p[0].x;
        message_buffer[11] = cube->p[0].y;
        message_buffer[12] = cube->p[0].z;
        message_buffer[13] = cube->p[0].color;

        message_buffer[14] = cube->p[1].x;
        message_buffer[15] = cube->p[1].y;
        message_buffer[16] = cube->p[1].z;
        message_buffer[17] = cube->p[1].color;

        message_buffer[18] = cube->p[2].x;
        message_buffer[19] = cube->p[2].y;
        message_buffer[20] = cube->p[2].z;
        message_buffer[21] = cube->p[2].color;

        message_buffer[22] = cube->p[3].x;
        message_buffer[23] = cube->p[3].y;
        message_buffer[24] = cube->p[3].z;
        message_buffer[25] = cube->p[3].color;

        // north
        message_buffer[26] = cube->p[4].x;
        message_buffer[27] = cube->p[4].y;
        message_buffer[28] = cube->p[4].z;
        message_buffer[29] = cube->p[4].color;

        message_buffer[30] = cube->p[5].x;
        message_buffer[31] = cube->p[5].y;
        message_buffer[32] = cube->p[5].z;
        message_buffer[33] = cube->p[5].color;

        message_buffer[34] = cube->p[6].x;
        message_buffer[35] = cube->p[6].y;
        message_buffer[36] = cube->p[6].z;
        message_buffer[37] = cube->p[6].color;

        message_buffer[38] = cube->p[7].x;
        message_buffer[39] = cube->p[7].y;
        message_buffer[40] = cube->p[7].z;
        message_buffer[41] = cube->p[7].color;

        // ...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}


//response
int __gws_plotcube_response (int fd)
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
    gws_debug_print ("__gws_plotcube_response: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_plotcube_response: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );
    
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
        gws_debug_print ("__gws_plotcube_response: recv fail.\n");
        printf          ("__gws_plotcube_response: recv fail.\n");
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
            gws_debug_print ("__gws_plotcube_response: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_plotcube_response: We got an event\n"); 
    return 0;
}



// == rectangle ====================================================================================


//
// =============================
//

int __gws_plotrectangle_request ( int fd, struct gr_rectangle_d *rect )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.
    
    //char *name = "Window name 1";


    if ( (void*) rect == NULL )
        return -1;


    //
    // Send request.
    //


    // #debug
    gws_debug_print ("__gws_plotrectangle_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 2042;    // msg (plot rectangle)
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        // ...
        
        // os argumentos para rotinas graficas começam em '10'.
        // Sempre começa com x,y,z e color ...
        
        // 0 1
        // 3 2  
        
        message_buffer[10] = rect->p[0].x;
        message_buffer[11] = rect->p[0].y;
        message_buffer[12] = rect->p[0].z;
        message_buffer[13] = rect->p[0].color;

        
        message_buffer[14] = rect->p[1].x;
        message_buffer[15] = rect->p[1].y;
        message_buffer[16] = rect->p[1].z;
        message_buffer[17] = rect->p[1].color;

        message_buffer[18] = rect->p[2].x;
        message_buffer[19] = rect->p[2].y;
        message_buffer[20] = rect->p[2].z;
        message_buffer[21] = rect->p[2].color;

        message_buffer[22] = rect->p[3].x;
        message_buffer[23] = rect->p[3].y;
        message_buffer[24] = rect->p[3].z;
        message_buffer[25] = rect->p[3].color;

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}


//response
int __gws_plotrectangle_response (int fd)
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
    gws_debug_print ("__gws_plotrectangle_response: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("__gws_plotrectangle_response: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );
    
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
        gws_debug_print ("__gws_plotrectangle_response: recv fail.\n");
        printf          ("__gws_plotrectangle_response: recv fail.\n");
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
            gws_debug_print ("__gws_plotrectangle_response: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("__gws_plotrectangle_response: We got an event\n"); 
    return 0;
}




//
// =======================
//

int 
__gws_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    unsigned long c )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.
    
    //char *name = "Window name 1";


    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gws_drawchar_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1004;    // Draw char.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        message_buffer[4] = window_id;
        message_buffer[5] = left; 
        message_buffer[6] = top; 
        message_buffer[7] = color; 
        message_buffer[8] = c;        // The 'char'.
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}



//response
int __gws_drawchar_response(int fd)
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
    gws_debug_print ("gws_drawchar_response: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("gws_drawchar_response: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );
    
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
        gws_debug_print ("gws_drawchar_response: recv fail.\n");
        printf          ("gws_drawchar_response: recv fail.\n");
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
            gws_debug_print ("gws_drawchar_response: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("gws_drawchar_response: We got an event\n"); 
    return 0;
}



//
// Draw text ======
//

int 
__gws_drawtext_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    char *string )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    //unsigned long *string_buffer = (unsigned long *) &__gws_message_buffer[128];   

    int n_writes = 0;   // For sending requests.


    
    //#test
    //Tentando colocar a string no buffer de mensagem
    // no offset certo.
    /*
    int StringSize =0;
            
    StringSize = sizeof( string );
        
    if( StringSize<0 || StringSize >= 256){
        gws_debug_print("gws_drawtext_request: StringSize fail\n");
        exit(1);
    }
        
   //#define MSG_OFFSET_LONGSTRING  128
        
    strncpy( 
       (char *) string_buffer, 
       (const char *) string,
       StringSize );
    
    sprintf(string_buffer,"Testing .........."); 
    string_buffer[0] = 'X';
    string_buffer[1] = 'X';
    string_buffer[StringSize+1] = 0; //finalizing
    */

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gws_drawtext_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)


    while (1){

        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1005;    // Draw text.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        message_buffer[4] = window_id;
        message_buffer[5] = left; 
        message_buffer[6] = top; 
        message_buffer[7] = color; 
        
        // OK funcionou string.
        char buf[256];
        int i=0;
        int string_off=8;
        for (i=0; i<250; i++)
        {
            message_buffer[string_off] = *string;
            string_off++; string++;
        }
        message_buffer[string_off] = 0;
        //message_buffer[256] = 0;


        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send ( fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}



//response
int __gws_drawtext_response(int fd)
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
    gws_debug_print ("gws_drawtext_response: Waiting ...\n");      

    int y=0;
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
    gws_debug_print ("gws_drawtext_response: Reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

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
        gws_debug_print ("gws_drawtext_response: recv fail.\n");
        printf          ("gws_drawtext_response: recv fail.\n");
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
            gws_debug_print ("gws_drawtext_response: SERVER_PACKET_TYPE_ERROR\n");
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
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("gws_drawtext_response: We got an event\n"); 
    return 0;
}


// Request.
int 
__gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color,
    unsigned long type,
    unsigned long parent,
    char *name )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.


    //#todo: precisamos criar um buffer aqui e copiarmos em algum lugar...
    //char *name = "label";


    //
    // Send request.
    //


    // #debug
    gws_debug_print ("libgws: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        message_buffer[0]  = 0;         // window. 
        message_buffer[1]  = 1001;      // msg. Create window REQUEST!
        message_buffer[2]  = 0;         //long1
        message_buffer[3]  = 0;         //long2
        message_buffer[4]  = left;
        message_buffer[5]  = top;
        message_buffer[6]  = width;
        message_buffer[7]  = height;
        message_buffer[8]  = bg_color;  //xCOLOR_GRAY2; 
        message_buffer[9]  = type;      //WT_SIMPLE;  //todo: type
        message_buffer[10] = parent; 
        //...

        //string support.
        char buf[256];
        int i=0;
        int string_off= 14; // 8;
        for(i=0; i<250; i++)
        {
            message_buffer[string_off] = *name; //#todo: Temos que receber esse ponteiro via argumento
            string_off++; name++;
        }
        message_buffer[string_off] = 0;

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, 
                       __gws_message_buffer, 
                       sizeof(__gws_message_buffer), 
                       0 );
       
        if(n_writes>0){ break; }
    }

    return 0; 
}


// Response
int __gws_createwindow_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   
    int n_reads = 0;    // For receiving responses.
    int y=0;

    //
    // Waiting for response. ==================
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    gws_debug_print ("libgws: Waiting ...\n");      

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
    gws_debug_print ("libgws: reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("libgws: recv fail.\n");
        printf          ("libgws: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }

    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        gws_yield(); 
        goto response_loop;
    }



    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        case GWS_SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            gws_debug_print ("libgws: [FIXME] packet\n");
            goto response_loop;
            break;
            
        // reply
        case GWS_SERVER_PACKET_TYPE_REPLY: goto process_reply; break;
        
        // event
        case GWS_SERVER_PACKET_TYPE_EVENT: goto process_event; break;
            
        case GWS_SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("libgws: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default: 
            gws_debug_print ("libgws: [FIXME] default\n");
            goto response_loop; 
            break; 
    };

//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    //#debug importnate
    //printf ("gws: Window ID %d \n", message_buffer[0] );

    //OUT: wid
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("libgws: We got an event\n"); 
    return 0;
}


//
// == Functions =======================================================
//

//test
//plot a point
int 
gws_plot0 (
    int fd,
    unsigned long x,
    unsigned long y,
    unsigned long z,
    unsigned long color )
{
    //Maybe we will not have a response.
    //int Response=-1;

    __gws_plot0_request ( fd, x, y, z, color );
    __gws_plot0_response( fd );

    return 0;
}


//plot cube
int 
gws_plotcube (
    int fd,
    struct gr_cube_d *cube )
{
    
    if ( (void*) cube == NULL )
        return -1;
        
    __gws_plotcube_request  (fd, (struct gr_cube_d *) cube );
    __gws_plotcube_response (fd);
    return 0;
}




//plot rectangle
int 
gws_plotrectangle (
    int fd,
    struct gr_rectangle_d *rect )
{
    
    if ( (void*) rect == NULL )
        return -1;
        
    __gws_plotrectangle_request  (fd, (struct gr_rectangle_d *) rect );
    __gws_plotrectangle_response (fd);
    return 0;
}







// Draw char.
int 
gws_draw_char (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned long c )
{

    int response =0;

    gws_debug_print("gws_draw_char: request\n");
    __gws_drawchar_request (
        (int) fd,             // fd,
        (int) window,         // window id,
        (unsigned long) x,    // left,
        (unsigned long) y,    // top,
        (unsigned long) color,
        (unsigned long) c );

    // #todo
    // We realy need a response ?
    gws_debug_print("gws_draw_char: response\n");
    response = __gws_drawchar_response((int) fd);  

    gws_debug_print("gws_draw_char: done\n");
    return (int) response;
}


// Draw text.
int 
gws_draw_text (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    char *string )
{

    int response =0;

    gws_debug_print("gws_draw_text: request\n");
    __gws_drawtext_request (
        (int) fd,             // fd,
        (int) window,         // window id,
        (unsigned long) x,    // left,
        (unsigned long) y,    // top,
        (unsigned long) color,
        (char *) string );

    gws_debug_print("gws_draw_text: response\n");
    response = __gws_drawtext_response ((int) fd);  

    gws_debug_print("gws_draw_text: done\n");
    return (int) response;
}


// #bubgug
// This is a test.
// trying to create a window using the fd as an argument.
// #todo: This routine is redundant. Delete it.
// gws_create_window is doing the same. Is it?
int
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
    __gws_createwindow_request(fd, 
        x, y, width, height, color, type, parentwindow, windowname);
        
    int response = (int) __gws_createwindow_response(fd); 
    
    return (int) response;
}    



// ??
// This is a dialog with the library.
// Services.
// IN: service number, ...
void *gws_services ( 
    int service,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4 )
{

    gws_debug_print("gws_services: [TODO]\n");

    if (service<0)
        return NULL;


    switch (service)
    {
        // Say hello !
        case 1:
            //?
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


    if ( pid<0 ){
        // msg?
        return -1;
    }


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

    if (tid < 0){
        //?msg
        return -1;
    }


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


void gws_reboot (void)
{
    //#todo
    gws_debug_print ("gws_reboot: [FIXME]\n");
    gws_system_call(110,0,0,0); 
    gws_debug_print ("gws_reboot: unexpected return\n");
    
    while (1){ asm("pause"); };
}



// Load a file using a pathname as an argument.
int 
gws_load_path ( 
    char *path, 
    unsigned long buffer, 
    unsigned long buffer_len )
{
    int status = -1;
    
     status = (int) gws_system_call ( 4004, 
                        (unsigned long) path, 
                        (unsigned long) buffer, 
                        (unsigned long) buffer_len );

    return (int) status;
}





// Window position.
int 
gws_change_window_position ( 
    int fd, 
    int window, 
    unsigned long x, 
    unsigned long y )
{
    __gws_change_window_position_request(fd,window,x,y);
    __gws_change_window_position_reponse(fd);
    return 0;
}



// Resize window.
int 
gws_resize_window( 
    int fd, 
    int window, 
    unsigned long w, 
    unsigned long h )
{
    __gws_resize_window_request(fd,window,w,h);
    __gws_resize_window_reponse(fd);
    return 0;
}



// Redraw window.
int 
gws_redraw_window (
   int fd, 
   int window, 
   unsigned long flags )
{
    __gws_redraw_window_request (fd,window,flags); 
    __gws_redraw_window_reponse (fd);
    return 0;
}



/*
 **************************************** 
 * gws_refresh_window:
 *     Refresh window.
 */

// #bugbug
// It is not working.
// The window server can not get the window number.

int gws_refresh_window (int fd, int window )
{
    __gws_refresh_window_request(fd,window);
    __gws_refresh_window_reponse(fd);
    return 0;
}



/*
 ************************************************** 
 * gws_create_window: 
 *     Create a window.
 *     Given it's type.
 */


// OUT: wid


int
gws_create_window ( 
    int fd,
    unsigned long type,        //1, Tipo de janela (popup,normal,...)
    unsigned long status,      //2, Estado da janela.
    unsigned long view,        //3, (min, max ...)
    char *windowname,          //4, Título.                          
    unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
    unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       //7, Largura da janela.
    unsigned long height,      //8, Altura da janela.
    int parentwindow,          //9, Endereço da estrutura da janela mãe.
    unsigned long onde,        //10, Ambiente.( Est� no desktop, barra, cliente ...)
    unsigned long clientcolor, //11, Cor da área de cliente
    unsigned long color )      //12, Color (bg) (para janela simples).
 
{
    int wid = -1;

    //#todo
    //Um argumento passa o display usado
    //o display aponta para o socket a ser usado
    //display->fd

    //#todo
    // use more arguments.


    // Request.
    __gws_createwindow_request ( fd, 
        x, y, width, height, 
        color, type, parentwindow, windowname);
    
    // Response
    wid = (int) __gws_createwindow_response(fd); 

    // Return the index returned by the window server.
    
    return (int) wid;
}


// Yield thread.
void gws_yield (void)
{
    gws_system_call (265,0,0,0); 
}

// refresh the background and yield the current thread
void gws_refresh_yield (int fd)
{
    //refresh background
    gws_refresh_window (fd, -4);  
    
    //yield
    gws_system_call (265,0,0,0); 
}


// refresh a given window and yield the current thread
void gws_refresh_yield2 (int fd, int window)
{
    gws_refresh_window (fd, window);
    gws_system_call (265,0,0,0); 
}



void gws_yield_n_times (unsigned long n)
{
    int i=0;
    for(i=0;i<n;i++)
        gws_system_call(265,0,0,0); 
}





// It's time to pay!
void gws_payment(void)
{

    gws_debug_print("==== PAYMENT ====\n");
        
    // o aplicativo salvou na biblioteca estatica o fd do window server.
    // entao agora pegamos o fd e efetuamos o refresh do background
    //e o yield da thread.
    // See: connect.c
    
    int fd = (int) gws_get_client_fd();
    
    if (fd<0){
        gws_debug_print("payment: fd\n");
        return;
    }
    
    gws_refresh_yield(fd);
}



/*
 **************************
 * gws_create_thread:
 *     Create a thread.
 *     #todo: 
 *     Precisamos uma função que envie mais argumentos.
 *     Essa será uma rotina de baixo nível para pthreads.
 */

void *gws_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name )
{
    //#define	SYSTEMCALL_CREATETHREAD     72
    debug_print ("gws_create_thread:\n");
    return (void *) gws_system_call ( 72, //SYSTEMCALL_CREATETHREAD, 
                        init_eip, 
                        init_stack, 
                        (unsigned long) name );
}




/*
 ****************************************************************
 * gws_start_thread:
 *     Coloca no estado standby para executar pela primeira vez
 */

void gws_start_thread (void *thread)
{
    // #define	SYSTEMCALL_STARTTHREAD  94 

    debug_print ("gws_start_thread:\n");
    gramado_system_call ( 94, //SYSTEMCALL_STARTTHREAD, 
        (unsigned long) thread, 
        (unsigned long) thread, 
        (unsigned long) thread );
}


// Clone the current and execute the clone.
int gws_clone_and_execute ( char *name )
{
    return (int) gws_system_call ( 900, (unsigned long) name, 0, 0 );
}


// Get system metrics.
unsigned long gws_get_system_metrics (int index)
{
    //if (index<0){
        //gde_debug_print ("gde_get_system_metrics: fail\n");
        //return 0;
    //}
    
    //#define	SYSTEMCALL_GETSYSTEMMETRICS  250
    
    return (unsigned long) gws_system_call ( 250, 
                               (unsigned long) index, 
                               (unsigned long) index, 
                               (unsigned long) index );
}



//P (Proberen) testar.
void gws_enter_critical_section (void){

//#define	SYSTEMCALL_GET_KERNELSEMAPHORE    226
//#define	SYSTEMCALL_CLOSE_KERNELSEMAPHORE  227
//#define	SYSTEMCALL_OPEN_KERNELSEMAPHORE   228

    int S=0;

    // Pega o valor do spinlock rpincipal.
    while (1){
        S = (int) gws_system_call ( 226,// SYSTEMCALL_GET_KERNELSEMAPHORE, 
                      0, 0, 0 );
                      
		// Se deixou de ser 0 então posso entrar.
		// Se ainda for 0, continuo no while.
        if ( S == 1 ){ goto done; }
        
        //#wait
        gws_system_call (265,0,0,0); //yield thread.
    };

    //Nothing

done:
    // Muda para zero para que ninguém entre.
    //SYSTEMCALL_CLOSE_KERNELSEMAPHORE,
    gws_system_call ( 227, 0, 0, 0 );
    return;
}


//V (Verhogen)incrementar.
void gws_exit_critical_section (void)
{
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    //SYSTEMCALL_OPEN_KERNELSEMAPHORE, 
    gws_system_call ( 228, 0, 0, 0 );
}


/*
//refresh raw rectangle
//refresh raw rectangle
int 
gws_refresh_rectangle(
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height);
int 
gws_refresh_rectangle(
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height)
{

   //todo
   //call request function (it uses 2021 service)
   //call response function
   return -1;
}
*/


// constructor
// Create the structure, given only a type.
/*
int gws_window ( int fd, int type );
int gws_window ( int fd, int type )
{
    int wid;
    wid = gws_create_window_socket (client_fd,
        WT_SIMPLE,1,1,"Browser",
        40, 40, 640, 480,
        0,0,COLOR_GRAY, COLOR_GRAY);

    return wid;
}
*/


// Create menu and return a pointer to a menu structure.
struct gws_menu_d *gws_create_menu (
    int fd,
    int parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned long color )
{

    struct gws_menu_d *menu;
    int window=0;

    menu = (struct gws_menu_d *) malloc( sizeof(struct gws_menu_d) );

    if ( (void *) menu == NULL )
    {
        // msg?
        return (struct gws_menu_d *) 0;
    }


    // Deslocamento em relação a janela mãe.
    menu->x = x;
    menu->y = y;
    menu->width  = width;
    menu->height = height;
    
    menu->color=color;
    menu->highlight = highlight;
    menu->itens_count = count;


    // Create menu window.

    window = gws_create_window ( fd,
                 WT_SIMPLE,1,1,"Menu",
                 menu->x,  //Deslocamento em relação a janela mãe. 
                 menu->y,  //Deslocamento em relação a janela mãe. 
                 width, 
                 height,
                 parent, 0, color, color );


    if (window<=0)
    { 
        // msg?
        //free(menu);
        menu->window = 0;  //#bugbug !!!!
        return (struct gws_menu_d *) 0;
    }

    //primeiro salva.
        
    menu->window = window; //bugbug
    menu->parent = parent;
    
    // Ok.
    // Return the pointer.
    
    return (struct gws_menu_d *) menu;
}


// Create a menu item for a given valid menu.
struct gws_menu_item_d *gws_create_menu_item (
    int fd,
    char *label,
    int id,
    struct gws_menu_d *menu)
{
    int window=0;    //menu item window
    
    struct gws_menu_item_d *item;
    
    // Check
    if ( (void *) menu == NULL )
    {
        // ? msg ?
        return (struct gws_menu_item_d *) 0;
    }
    
    //create menu item.
    item = (struct gws_menu_item_d *) malloc( sizeof(struct gws_menu_item_d) );

    if ( (void *) item == NULL )
    {
        // msg ?
        return (struct gws_menu_item_d *) 0;
    }


    // Provisório
    if (id>5 || id>menu->itens_count){
        // ? msg ?
        return (struct gws_menu_item_d *) 0;
    }

    item->id = id;

    item->width  = (menu->width -8);
    item->height = (menu->height / menu->itens_count);
    item->x = 4;
    item->y = (item->height*id);
    

    // Create a window for a menu item.

    if ( menu->window > 0 )
    {
        window = gws_create_window ( fd,
                     WT_BUTTON,1,1, label,
                     item->x, 
                     item->y, 
                     item->width, 
                     item->height,
                     menu->window,  // #bugbug 
                     0, COLOR_GRAY, COLOR_GRAY );
                     
        //debug
        //gws_draw_char (
            //fd, 
             //menu->window, // #bugbug
              //0,
              //0,
              //COLOR_RED,
              //'x');

         item->window = window;
    }

    // Return the pointer fot the menu item.
    return (struct gws_menu_item_d *) item;
}

// Expand a byt all over the long.
unsigned long gws_explode_byte (unsigned char data)
{
    return (unsigned long) (data << 24 | data << 16 | data << 8 | data);
}


// Create empty file.
int gws_create_empty_file ( char *file_name ){

    int __ret = 0;
    
    //gde_enter_critical_section();
    
    __ret = (int) gramado_system_call ( 43, 
                      (unsigned long) file_name, 0, 0);

    //gde_exit_critical_section();    
    
    return __ret;
}


// Create empty directory.
int gws_create_empty_directory ( char *dir_name ){

    int __ret=0;


    //gde_enter_critical_section();
    
    __ret = (int) gramado_system_call ( 44, 
                      (unsigned long) dir_name, 0, 0);

    //gde_exit_critical_section();    


    return (int) __ret;
}


//
// End.
//







