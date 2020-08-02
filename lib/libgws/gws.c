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


//
// prototyes (internals)
//


//
// == Create Window ==========================
//

int 
gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color,
    unsigned long type,
    unsigned long parent );
int gws_createwindow_response(int fd);


//
// == Draw Char ==========================
//


int 
gws_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    unsigned long c );
int gws_drawchar_response(int fd);


//
// == Draw text ==========================
//

int 
gws_drawtext_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    char *string );
int gws_drawtext_response(int fd);


//
// == ... ==========================
//




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
    
    
    // #todo:
    // #importante
    // We need to alloc memory to the CurrentEvent struct.
    // So we need the libc support. 
    // Check the compilation and include the libc. ???
    
    //CurrentEvent = (void *) malloc(sizeof(struct gws_event_d));
    

    return 0;
}

// #todo
// Criar a função gws_create_window usando as funções:
// gws_createwindow_request e gws_createwindow_response
//




    
int 
gws_drawchar_request (
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
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1004;    // Draw char.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = window_id;
        message_buffer[5] = left; 
        message_buffer[6] = top; 
        message_buffer[7] = color; 
        
        message_buffer[8] = c;   // The 'char'.

         
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



//response
int gws_drawchar_response(int fd)
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
    gws_debug_print ("gws_drawchar_response: Reading ...\n");      


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



// OK
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
    gws_drawchar_request (
        (int) fd,             // fd,
        (int) window,         // window id,
        (unsigned long) x,    // left,
        (unsigned long) y,    // top,
        (unsigned long) color,
        (unsigned long) c );

    gws_debug_print("gws_draw_char: response\n");
    response = gws_drawchar_response((int) fd);  

    gws_debug_print("gws_draw_char: done\n");
    return (int) response;
}


//
// Draw text ======
//

int 
gws_drawtext_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    char *string )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.



    //char *name = "Window name 1";

   

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gws_drawtext_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    int StringSize =0;

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1004;    // Draw char.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = window_id;
        message_buffer[5] = left; 
        message_buffer[6] = top; 
        message_buffer[7] = color; 
        
        //message_buffer[8] = c;   // The 'char'.

        //#test
        //Tentando colocar a string no buffer de mensagem
        // no offset certo.
        
        StringSize = sizeof( string );
        
        if( StringSize<0 || StringSize >= 256){
            gws_debug_print("gws_drawtext_request: StringSize fail\n");
            exit(1);
        }
        
        //#define MSG_OFFSET_LONGSTRING  128
        
        strncpy( 
            (char *) &message_buffer[128], 
            (const char *) string,
            StringSize );
        
        message_buffer[128 + StringSize] = 0; //finalizing
        
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



//response
int gws_drawtext_response(int fd)
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
    gws_debug_print ("gws_drawtext_response: Reading ...\n");      


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
    gws_drawtext_request (
        (int) fd,             // fd,
        (int) window,         // window id,
        (unsigned long) x,    // left,
        (unsigned long) y,    // top,
        (unsigned long) color,
        (char *) string );

    gws_debug_print("gws_draw_text: response\n");
    response = gws_drawtext_response((int) fd);  

    gws_debug_print("gws_draw_text: done\n");
    return (int) response;
}










int 
gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color,
    unsigned long type,
    unsigned long parent )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];   

    int n_writes = 0;   // For sending requests.


    //#todo: precisamos criar um buffer aqui e copiarmos em algum lugar...
    char *name = "Window";

   

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
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg. Create window REQUEST!
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = left;   //120;   //x
        message_buffer[5] = top;    //120;   //y
        message_buffer[6] = width;  //480;   //w
        message_buffer[7] = height; //320;   //h
        
        message_buffer[8] = bg_color;  //xCOLOR_GRAY2; 
        message_buffer[9] = type;      //WT_SIMPLE;  //todo: type
         
       //test
        message_buffer[10] = parent; 
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


//response
int gws_createwindow_response(int fd)
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
    gws_debug_print ("gwst: Waiting ...\n");      

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

    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("gws_create_window_response: recv fail.\n");
        printf ("gws_create_window_response: recv fail.\n");
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
            gws_debug_print ("gws_create_window_response: [FIXME] packet\n");
            goto response_loop;
            break;
            
        // reply
        case GWS_SERVER_PACKET_TYPE_REPLY: goto process_reply; break;
        
        // event
        case GWS_SERVER_PACKET_TYPE_EVENT: goto process_event; break;
            
        case GWS_SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("gws: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default: 
            gws_debug_print ("gws_create_window_response: [FIXME] default\n");
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
        x, y, width, height, color, type, parentwindow);
        
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
   gws_debug_print ("gws_reboot: [FIXME]\n");
   gws_system_call(110,0,0,0); 
   gws_debug_print ("gws_reboot: unexpected return\n");
   while (1){ asm("pause"); };
}


// Talvez vamos retonar o descritor
// dado pelo servidor.
int
gws_create_window ( 
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
    //Um argumento passa o display usado
    //o display aponta para o socket a ser usado
    //display->fd

    //#todo
    // use more arguments.
    gws_createwindow_request(fd, 
        x, y, width, height, color, type, parentwindow);
        
    int wid = (int) gws_createwindow_response(fd); 
    
    return (int) wid;
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


int gws_clone_and_execute ( char *name )
{
    return (int) gws_system_call ( 900, (unsigned long) name, 0, 0 );
}

unsigned long gws_get_system_metrics (int index){

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


// #bugbug
// isso deveria se chamar 'get next system message'.
// Porque o evento pegaremos do window server e não
// diretamente do kernel.
// Get next event
struct gws_event_d *gws_next_system_message(void)
{

    unsigned long message_buffer[5];   


    gws_debug_print("gws_next_system_message:[TODO]\n");

    
    if( (void *) CurrentEvent == NULL )
        return (struct gws_event_d *) 0;
    

    // get system message.
    // put the message into the event struct.

    //
    // Get system message.
    //
    
    gws_enter_critical_section();
    gws_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
    gws_exit_critical_section();

    // No message
    if ( message_buffer[1] == 0 ){
        gws_system_call (265,0,0,0);
        return;
    }

        
     //
     // put the message into the event struct.
     //
     
     CurrentEvent->wid   = message_buffer[0]; // window id
     CurrentEvent->msg   = message_buffer[1]; // msg (event type)
     CurrentEvent->long1 = message_buffer[2]; // long1
     CurrentEvent->long2 = message_buffer[3]; // long2
     // ...


     // clean the message buffer.
     message_buffer[0] = 0;
     message_buffer[1] = 0;
     message_buffer[2] = 0;
     message_buffer[3] = 0;
     //...

    return (struct gws_event_d *) CurrentEvent;
}



//P (Proberen) testar.
void gws_enter_critical_section (){

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
    //Muda para zero para que ninguém entre.
    gws_system_call ( 227,//SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 
        0, 0, 0 );
    return;
}


//V (Verhogen)incrementar.
void gws_exit_critical_section ()
{
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    gws_system_call ( 228,//SYSTEMCALL_OPEN_KERNELSEMAPHORE, 
       0, 0, 0 );
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


//
// End.
//







