/*
 * File: gws.c
 * gws - client-side library for gws window server.
 * gws is a window server running in ring3, and this is
 * a library used by the apps.
 */
// mvc:
// The user send requests to the controller
// to access the data inside the model layer.
// The user get the responses in the View layer
// where its able to visualize the information.
// " Think of the MVC pattern as a restaurant 
// with the Models being the cooks, 
// Views being the customers, and 
// Controllers being the waiters."
// #todo:
// gws_refresh_rectangle
// gws_refresh_char
// ...
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
#include <sys/socket.h>
#include <rtl/gramado.h>
// libgws
#include "include/connect.h"
#include "include/gws.h"


// globals
// version support.

/*
struct libgws_version_d
{
    unsigned long majorVersion;
    unsigned long minorVersion;
    // ...
};
*/

// Version
struct libgws_version_d  libgwsVersion;
// Display
struct gws_display_d *libgwsCurrentDisplay;
// Event
struct gws_event_d *CurrentEvent;

// #todo
// + draw line
// ...

// Strings
// #todo: Use 'const char *'.
char *title_when_no_title = "Window";

// #test
// Tentando deixar o buffer aqui e aproveitar em mais funções.
// #??
// Podemos ter um buffer de request dentro da estrutura de display.
// Isso é melhor que um buffer global solto,
// Dessa forma cada display pode ter seus próprios buffers.
// #todo:
// Talvez um socket deva ter pelo menos o tamanho de um pacote de rede.
// Para assim enviarmos pacotes de rede usando a infraestrutura de socket.
// Mas por enquanto estamos usando a infraestrutura de sockets
// para transportamos mensagens de 512 bytes, contendo o protocolo
// desse sistema de janelas.

static char __gws_message_buffer[512];

//
// == prototyes (internals) =========================
//

// == Get window info ==========================
static int __gws_get_window_info_request( int fd, int wid );
static struct gws_window_info_d *__gws_get_window_info_response(
    int fd,
    struct gws_window_info_d *window_info );

// == Get next event ==========================
static int __gws_get_next_event_request(int fd);
static struct gws_event_d *__gws_get_next_event_response ( 
    int fd, 
    struct gws_event_d *event );

// == Change window position ==================
static int 
__gws_change_window_position_request ( 
    int fd, int window, unsigned long x, unsigned long y );
static int __gws_change_window_position_reponse( int fd );

// == Resize window ==========================
static int 
__gws_resize_window_request ( 
    int fd, int window, unsigned long w, unsigned long h );
static int __gws_resize_window_reponse(int fd);

// == Redraw window ==========================
static int 
__gws_redraw_window_request( int fd, int window, unsigned long flags );
static int __gws_redraw_window_reponse(int fd);

// == Refresh Window ==========================
static int __gws_refresh_window_request( int fd, int window );
static int __gws_refresh_window_reponse(int fd);

// == Create Window ==========================
static int 
__gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned int bg_color,
    unsigned long type,
    unsigned long style,
    unsigned long parent,
    char *name );
static int __gws_createwindow_response(int fd);

// == refresh rectangle
static int 
__gws_refresh_rectangle_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height );
static int __gws_refresh_rectangle_response(int fd);

// == Draw Char ==========================
static int 
__gws_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned int color,
    unsigned int ch );
static int __gws_drawchar_response(int fd);

// == Draw text ==========================
static int 
__gws_drawtext_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    char *string );
static int __gws_drawtext_response(int fd);



static int 
__gws_clone_and_execute_request (
    int fd,
    unsigned long arg1,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4,
    char *string );
static int __gws_clone_and_execute_response(int fd);


// == ... ==========================


//
// == Functions ====================
//

// System call.
// System interrupt.
    
void *gws_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    unsigned long ReturnValue=0;
    asm volatile ( " int %1 \n"
                 : "=a"(ReturnValue)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );
    return (void *) ReturnValue; 
}


// Debug via serial port. (COM1)
void gws_debug_print(char *string)
{
    if ( (void*) string == NULL ){ return; }
    if ( *string == 0 ){
        return;
    }
    gws_system_call ( 
        289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}


//=============================================

// Initialize the library.
int gws_initialize_library(void)
{
    pid_t ws_pid = -1;    // PID do window server.

    ws_pid = (pid_t) gws_initialize_connection();
    if (ws_pid < 0){
        gws_debug_print("gws_initialize_library: [fail] ws_pid\n");
        return (int) -1;
    }

// #todo:
// #importante
// We need to alloc memory to the CurrentEvent struct.
// So we need the libc support. 
// Check the compilation and include the libc. ???

    //CurrentEvent = (void *) malloc(sizeof(struct gws_event_d));

    return 0;
    // return (int) ws_pid;
}



//
// == Helper functions ============================
//



// ==============================================================

// == get window info request ==========================
// Let's get some information about the given window.
// Send request:
// Setup the parameters and
// write the data into the file.

static int __gws_get_window_info_request( int fd, int wid )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0]; 
    int n_writes = 0; 

    gws_debug_print ("__gws_get_window_info_request: wr\n");

// window id.
    message_buffer[0] = wid;
// Message code.
    message_buffer[1] = GWS_GetWindowInfo;
// libgws signature.
    message_buffer[2] = (unsigned long) 1234;
    message_buffer[3] = (unsigned long) 5678;
    //...

    if (fd<0){
        return (int) -1;
    }
    if (wid<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes <= 0){
        return (int) -1;
    }

    return (int) n_writes; 
}


// get window info response ===================
static struct gws_window_info_d *__gws_get_window_info_response(
    int fd,
    struct gws_window_info_d *window_info )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];

// #importante
// As informações devem ficar aqui até que o cliente pegue.
// Um ponteiro será devolvido para ele.

    ssize_t n_reads=0;

    int wid=0;
    int msg_code=0;
    int sig1=0;
    int sig2=0;

    if ( (void*) window_info == NULL )
    {
        return NULL;
    }

    // fail
    window_info->used = FALSE;
    window_info->magic = 0;

// read

    if (fd<0){
        return NULL;
    }

    n_reads = 
        (ssize_t) recv ( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    if (n_reads <= 0)
    { 
        //
        return (struct gws_window_info_d *) window_info;
    }

// The msg packet

    int msg = (int)  message_buffer[1];
    msg = (msg & 0xFFFF);

    switch (msg){

    // ok, that is what we need.
    case GWS_SERVER_PACKET_TYPE_REPLY:
        goto process_response;
        break;

    // fail
    case GWS_SERVER_PACKET_TYPE_EVENT:
    case GWS_SERVER_PACKET_TYPE_REQUEST:
    case GWS_SERVER_PACKET_TYPE_ERROR:
    default:
        goto fail;
        break; 
    };

// Put the message info into the structure.
process_response:

// the header
    wid      = (int)           message_buffer[0];  // window id
    msg_code = (int)           message_buffer[1];  // message code: (It is an EVENT)
    sig1     = (unsigned long) message_buffer[2];  // Signature 1: 1234
    sig2     = (unsigned long) message_buffer[3];  // Signature 2: 5678

    if ( sig1 != 1234 ){
        //debug_print ("__gws_get_window_info_response: sig1 fail\n");
        goto fail;
    }

    if ( sig2 != 5678 ){
        //debug_print ("__gws_get_window_info_response: sig2 fail\n");
        goto fail;
    }

// data field

// OK
// The data field
    if ( msg_code == GWS_SERVER_PACKET_TYPE_REPLY )
    {
        //printf("__gws_get_next_event_response: WE GOT THE DATA\n");
    
        window_info->wid   = (int) message_buffer[4];  // wid
        window_info->pwid  = (int) message_buffer[5];  // parent wid
        window_info->type  = (int) message_buffer[6];  // window type

        // window
        window_info->left   = (unsigned long) message_buffer[7];   // left 
        window_info->top    = (unsigned long) message_buffer[8];   // top
        window_info->width  = (unsigned long) message_buffer[9];   // width
        window_info->height = (unsigned long) message_buffer[10];  // height

        //#debug
        //printf("libgws: l=%d t=%d w=%d h=%d\n",
            //window_info->left, 
            //window_info->top, 
            //window_info->width, 
            //window_info->height );

        // limits
        window_info->right  = (unsigned long) message_buffer[11];  // right
        window_info->bottom = (unsigned long) message_buffer[12];  // bottom

        // client area rectangle
        window_info->cr_left   = (unsigned long) message_buffer[13];  // cr left 
        window_info->cr_top    = (unsigned long) message_buffer[14];  // cr top
        window_info->cr_width  = (unsigned long) message_buffer[15];  // cr width
        window_info->cr_height = (unsigned long) message_buffer[16];  // cr height

        // border
        window_info->border_width = (unsigned long) message_buffer[17];  // border width

        // The app will need this thing.
        window_info->used = TRUE;
        window_info->magic = 1234;

        // #debug
        //printf ("::: wid=%d msg=%d l1=%d l2=%d \n",
            //window_info->wid, window_info->msg, window_info->long1, window_info->long2 );

        // ok, we got it.
        return (struct gws_window_info_d *) window_info;
    }

// fall to fail field

fail:
    return NULL;
}



// ==============================================================

// == get next event ==========================
// Send request:
// Setup the parameters and
// write the data into the file.

static int __gws_get_next_event_request(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;

    //gws_debug_print ("__gws_get_next_event_request: wr\n");

// window id.
    message_buffer[0] = 0; 
// Message code
    message_buffer[1] = GWS_GetNextEvent;  
    message_buffer[2] = 0;
    message_buffer[3] = 0;
    //...

    if(fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
        return (int) -1;
    }

    return (int) n_writes;
}


static struct gws_event_d *__gws_get_next_event_response ( 
    int fd, 
    struct gws_event_d *event )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];

// #importante
// As informações devem ficar aqui até que o
// cliente pegue.
// Um ponteiro será devolvido para ele.

    ssize_t n_reads=0;

    //gws_debug_print ("__gws_get_next_event_response: rd\n"); 

// crazy fail
    if( (void*) event == NULL ){
        return NULL;
    }

    if (fd<0){
        return NULL;
    }

// Read

    n_reads = 
        (ssize_t) recv ( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    if (n_reads <= 0)
    { 
        printf ("__gws_get_next_event_response: Read 0 bytes\n"); 
        event->type = 0;
        event->used = FALSE;
        event->magic = 0;
        return (struct gws_event_d *) event;
    }

//
// The msg packet
//

    int msg = (int)  message_buffer[1];
    msg = (msg & 0xFFFF);

    switch (msg){

    case GWS_SERVER_PACKET_TYPE_EVENT:
        goto process_event;
        break;

    case GWS_SERVER_PACKET_TYPE_REPLY:
    case GWS_SERVER_PACKET_TYPE_REQUEST:
    case GWS_SERVER_PACKET_TYPE_ERROR:
    default:
        //printf ("__gws_get_next_event_response: Invalid msg code\n"); 
        event->type = 0;
        event->used = FALSE;
        event->magic = 0;
        return (struct gws_event_d *) event;
        break; 
    };

// crazy fail
    printf ("__gws_get_next_event_response: crazy fail\n"); 
    event->type = 0;
    event->used = FALSE;
    event->magic = 0;

    return (struct gws_event_d *) event;

// The header
    int wid=0;
    int msg_code=0;
    unsigned long sig1=0;
    unsigned long sig2=0;

process_event:

// Get the message sent by the server.

    //printf ("libgws: $\n");

    wid      = (int)           message_buffer[0];  // window id
    msg_code = (int)           message_buffer[1];  // message code: (It is an EVENT)
    sig1     = (unsigned long) message_buffer[2];  // Signature 1: 1234
    sig2     = (unsigned long) message_buffer[3];  // Signature 2: 5678

    // #data
    // A informação esta nos campos 4, 5,6 e 7.

// Checks
// #todo: 
// Check if it is a REPLY message.

    if ( msg_code != GWS_SERVER_PACKET_TYPE_EVENT ){
        debug_print ("__gws_get_next_event_response: msg_code fail\n");
        goto fail0;
    }

    if ( sig1 != 1234 ){
        debug_print ("__gws_get_next_event_response: sig1 fail\n");
        goto fail0;
    }

    if ( sig2 != 5678 ){
        debug_print ("__gws_get_next_event_response: sig2 fail\n");
        goto fail0;
    }

// The event properly.

    event->used = FALSE;
    event->magic = 0;

// OK

    if ( msg_code == GWS_SERVER_PACKET_TYPE_EVENT )
    {
        //printf("__gws_get_next_event_response: WE GOT AN EVENT\n");
    
        event->window = (int) message_buffer[4];            // window id
        event->type   = (int) message_buffer[5];            // message code
        event->long1  = (unsigned long) message_buffer[6];  // long1
        event->long2  = (unsigned long) message_buffer[7];  // long2

        event->window = (int) ( event->window & 0xFFFF );
        event->type   = (int) ( event->type & 0xFFFF );

        event->used = TRUE;
        event->magic = 1234;

        // #debug
        //printf ("::: wid=%d msg=%d l1=%d l2=%d \n",
            //event->wid, event->msg, event->long1, event->long2 );

        return (struct gws_event_d *) event;
    }

fail0:
    event->type = 0;
    event->used = FALSE;
    event->magic = 0;
    return NULL;
}


//=========

static int __gws_refresh_window_request( int fd, int window )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    //char *name = "Window name 1";

    gws_debug_print ("__gws_refresh_window_request: wr\n");


    message_buffer[0] = window; 
// Message code
    message_buffer[1] = GWS_RefreshWindow;
    message_buffer[2] = 0;
    message_buffer[3] = 0;
    //...

    if (fd<0){
        return (int) -1;
    }
    if (window<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
            return (int) -1;
    }

    return (int) n_writes;
}


static int __gws_refresh_window_reponse(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

    if (fd<0){
        return (int) -1;
    }

// Read

    n_reads = 
        (ssize_t) recv ( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    if (n_reads <= 0){
        return (int) -1;
    }

// The msg packet
// Get the message sent by the server.

    int msg   = (int) message_buffer[1];
    int value = (int) message_buffer[2];

    switch (msg){
    // Reply!
    case GWS_SERVER_PACKET_TYPE_REPLY:
        return (int) value;
        break;
    case GWS_SERVER_PACKET_TYPE_REQUEST:
    case GWS_SERVER_PACKET_TYPE_EVENT:
    case GWS_SERVER_PACKET_TYPE_ERROR:
    default:
        return (int) -1;
        break; 
    };
//fail:
    return (int) -1;
}


static int 
__gws_redraw_window_request ( 
    int fd, 
    int window, 
    unsigned long flags )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    //char *name = "Window name 1";

    gws_debug_print ("__gws_redraw_window_request: wr\n");

// Window ID
    message_buffer[0] = window;
// Message code
    message_buffer[1] = GWS_RedrawWindow;
// Flags
    message_buffer[2] = (unsigned long) flags;
    message_buffer[3] = 0;
    //...

    if (fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
        return (int) -1;
    }

    return (int) n_writes;
}

static int __gws_redraw_window_reponse(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// Waiting for response.
// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

// #todo
// Podemos checar antes se o fd 
// representa um objeto que permite leitura.
// Pode nem ser possível.
// Mas como sabemos que é um soquete,
// então sabemos que é possível ler.
// #caution
// Waiting for response.
// We can stay here for ever.

    if (fd<0){
        return (int) -1;
    }

response_loop:

    n_reads = 
        (ssize_t) recv ( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    //if (n_reads<=0){
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("__gws_redraw_window_reponse: recv fail.\n");
        printf          ("__gws_redraw_window_reponse: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }

// The msg index.
// Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        // Reply!
        case GWS_SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST:
        case GWS_SERVER_PACKET_TYPE_EVENT:
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

// Process reply.
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

// Process an event.
process_event:
    //gws_debug_print ("__gws_redraw_window_reponse: We got an event\n"); 
    return 0;
}


static int 
__gws_change_window_position_request ( 
    int fd, 
    int window, 
    unsigned long x, 
    unsigned long y )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    //char *name = "Window name 1";

    gws_debug_print ("__gws_change_window_position_request: wr\n");

    message_buffer[0] = (unsigned long) (window & 0xFFFFFFFF);
// Message code
    message_buffer[1] = GWS_ChangeWindowPosition;
    message_buffer[2] = (unsigned long) x;
    message_buffer[3] = (unsigned long) y;
    //...

    if (fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd,
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
        return (int) -1;
    }

    return (int) n_writes;
}

static int __gws_change_window_position_reponse(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// Waiting for response. ==================

// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

    //gws_debug_print ("__gws_change_window_position_reponse: Waiting ...\n");      

    //int y=0;
    //for(y=0; y<15; y++)
        //gws_yield();   // See: libgws/

// #todo
// Podemos checar antes se o fd 
// representa um objeto que permite leitura.
// Pode nem ser possível.
// Mas como sabemos que é um soquete,
// então sabemos que é possível ler.
// #caution
// Waiting for response.
// We can stay here for ever.

    if (fd<0){
        return (int) -1;
    }

response_loop:

    n_reads = 
        (ssize_t) recv( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        //gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("__gws_change_window_position_reponse: recv fail.\n");
        printf          ("__gws_change_window_position_reponse: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }

// The msg index.
// Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        // Reply!
        case GWS_SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST: 
        case GWS_SERVER_PACKET_TYPE_EVENT:
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

// Process reply
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

    return (int) message_buffer[0];

// Process an event.
process_event:
    //gws_debug_print ("__gws_change_window_position_reponse: We got an event\n"); 
    return 0;
}

// ======================================================

static int 
__gws_resize_window_request ( 
    int fd, 
    int window, 
    unsigned long w, 
    unsigned long h )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    //char *name = "Window name 1";

    gws_debug_print ("__gws_resize_window_request: wr\n");

    message_buffer[0] = window;
// Message code
    message_buffer[1] = GWS_ResizeWindow;

    message_buffer[2] = w;
    message_buffer[3] = h;
    // ...

    if (fd<0){
        return (int) -1;
    }

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
        return (int) -1;
    }

    return (int) n_writes;
}

static int __gws_resize_window_reponse(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// Waiting for response.
// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

    //gws_debug_print ("__gws_resize_window_reponse: Waiting ...\n");      

    //int y=0;
    //for(y=0; y<15; y++)
        //gws_yield();   // See: libgws/

// #todo
// Podemos checar antes se o fd 
// representa um objeto que permite leitura.
// Pode nem ser possível.
// Mas como sabemos que é um soquete,
// então sabemos que é possível ler.

    // gws_debug_print ("__gws_resize_window_reponse: rd\n");

// #caution
// Waiting for response.
// We can stay here for ever.

    if (fd<0){
        return (int) -1;
    }

response_loop:

    n_reads = 
        (ssize_t) recv( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        //gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("__gws_resize_window_reponse: recv fail.\n");
        printf          ("__gws_resize_window_reponse: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }

// The msg index.
// Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        // Reply!
        case GWS_SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST:
        case GWS_SERVER_PACKET_TYPE_EVENT:
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

// Process reply.
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

// Process an event.
process_event:
    // gws_debug_print ("__gws_resize_window_reponse: We got an event\n"); 
    return 0;
}

//
// =============================
//

// == rectangle ========

//
// =============================
//

// ================================================

static int 
__gws_refresh_rectangle_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height )
{
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    //char *name = "Window name 1";

    gws_debug_print ("__gws_refresh_rectangle_request: wr\n");


    message_buffer[0] = (unsigned long) 0;
// Message code
    message_buffer[1] = (unsigned long) GWS_RefreshRectangle;

    message_buffer[2] = (unsigned long) 0;
    message_buffer[3] = (unsigned long) 0;

    message_buffer[4] = (unsigned long) (left   & 0xFFFF); 
    message_buffer[5] = (unsigned long) (top    & 0xFFFF); 
    message_buffer[6] = (unsigned long) (width  & 0xFFFF); 
    message_buffer[7] = (unsigned long) (height & 0xFFFF ); 

    //message_buffer[?] = (unsigned long) 0; 
    // ...

    if (fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
        return (int) -1;
    }

    return (int) n_writes;
}

// Response
// A sincronização nos diz que já temos um reply.
static int __gws_refresh_rectangle_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// A sincronização nos diz que já temos um reply.
    //int y=0;
    //for(y=0; y<15; y++){ gws_yield(); };

    //gws_debug_print ("__gws_refresh_rectangle_response: rd\n");      

    if (fd<0){
        return (int) -1;
    }

// Read

    n_reads = 
        (ssize_t) recv( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    if (n_reads <= 0){
        return (int) -1;
    }

//
// The msg index.
//
    // Get the message sended by the server.

    int msg   = (int) message_buffer[1];
    int value = (int) message_buffer[2];

    switch (msg){

        // Reply
        case GWS_SERVER_PACKET_TYPE_REPLY:
            return (int) value;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST:
        case GWS_SERVER_PACKET_TYPE_EVENT:
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

//fail:
    return -1;
}

// ================================================

static int 
__gws_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned int color,
    unsigned int ch )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    //char *name = "Window name 1";

    //gws_debug_print ("__gws_drawchar_request: wr\n");      

    message_buffer[0] = (unsigned long) 0;
// Message code
    message_buffer[1] = (unsigned long) GWS_DrawChar;

    message_buffer[2] = (unsigned long) 0;
    message_buffer[3] = (unsigned long) 0;

    message_buffer[4] = (unsigned long) window_id;
    message_buffer[5] = (unsigned long) (left & 0xFFFF); 
    message_buffer[6] = (unsigned long) (top  & 0xFFFF); 
    message_buffer[7] = (unsigned long) (color & 0xFFFFFFFF); 

// The 'char'.
    message_buffer[8] = (unsigned long) ( ch & 0xFF );
    // ...

    if (fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
        return (int) -1;
    }

    return (int) n_writes;
}

// Response
// A sincronização nos diz que já temos um reply.
static int __gws_drawchar_response(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// A sincronização nos diz que já temos um reply.

    //int y=0;
    //for(y=0; y<15; y++){ gws_yield(); };

    //gws_debug_print ("__gws_drawchar_response: rd\n");      

    if (fd<0){
        return (int) -1;
    }

// Read

    n_reads = 
        (ssize_t) recv( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    if (n_reads <= 0){
        return (int) -1;
    }

// The msg index.
// Get the message sended by the server.

    int msg   = (int) message_buffer[1];
    int value = (int) message_buffer[2];

    switch (msg){

        // Reply
        case GWS_SERVER_PACKET_TYPE_REPLY:
            return (int) value;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST:
        case GWS_SERVER_PACKET_TYPE_EVENT:
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

//fail:
    return -1;
}


//
// Draw text ======
//

static int 
__gws_drawtext_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    char *string )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    //unsigned long *string_buffer = (unsigned long *) &__gws_message_buffer[128];
    int n_writes = 0;

    //gws_debug_print ("gws_drawtext_request: wr\n");

    message_buffer[0] = 0;
// Message code
    message_buffer[1] = GWS_DrawText;

    message_buffer[2] = 0;
    message_buffer[3] = 0;

    message_buffer[4] = window_id;
    message_buffer[5] = left; 
    message_buffer[6] = top; 
    message_buffer[7] = color;

// String support

    char buf[256];
    int i=0;
    int string_off=8;
    
    // Fill the string buffer
    for (i=0; i<250; i++)
    {
        message_buffer[string_off] = *string;
        string_off++; 
        string++;
    };
    message_buffer[string_off] = 0;


    if (fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
            return (int) -1;
    }
       
    return (int) n_writes;
}

// response
static int __gws_drawtext_response(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// Waiting for response.
// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

    //gws_debug_print ("gws_drawtext_response: Waiting ...\n");      

    //int y=0;
    //for (y=0; y<15; y++){
        //gws_yield();
    //};

// #todo
// Podemos checar antes se o fd 
// representa um objeto que permite leitura.
// Pode nem ser possível.
// Mas como sabemos que é um soquete,
// então sabemos que é possível ler.

    // #debug
    // gws_debug_print ("gws_drawtext_response: rd\n");

    // #caution
    // Waiting for response.
    // We can stay here for ever.

    if (fd<0){
        return (int) -1;
    }

response_loop:

    n_reads = 
        (ssize_t) recv(
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        //gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("gws_drawtext_response: recv fail.\n");
        printf          ("gws_drawtext_response: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        return -1;
        //exit (1);
    }

// The msg index.
// Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        // Reply!
        case GWS_SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST:
        case GWS_SERVER_PACKET_TYPE_EVENT:            
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

// Process reply
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

    return (int) message_buffer[0];

// Process an event.
process_event:
    //gws_debug_print ("gws_drawtext_response: We got an event\n"); 
    return 0;
}


// ==================================

// Clone and execute request.

static int 
__gws_clone_and_execute_request (
    int fd,
    unsigned long arg1,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4,
    char *string )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    //unsigned long *string_buffer = (unsigned long *) &__gws_message_buffer[128];
    int n_writes = 0;

    gws_debug_print ("__gws_clone_and_execute_request: wr\n");

    message_buffer[0] = 0;

// Message code
    message_buffer[1] = 9099;

    message_buffer[2] = 0;
    message_buffer[3] = 0;

    message_buffer[4] = (unsigned long) arg1;
    message_buffer[5] = (unsigned long) arg2; 
    message_buffer[6] = (unsigned long) arg3; 
    message_buffer[7] = (unsigned long) arg4; 


// String support

    char buf[256];
    int i=0;
    int string_off=8;
    
    // Fill the string buffer.
    for (i=0; i<250; i++)
    {
        message_buffer[string_off] = *string;
        string_off++;
        string++;
    };
    message_buffer[string_off] = 0;

    if (fd<0){
        return (int) -1;
    }

// Write

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes<=0){
            return (int) -1;
    }

    return (int) n_writes;
}

//response
static int __gws_clone_and_execute_response(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// Waiting for response.
// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

    //gws_debug_print ("__gws_clone_and_execute_response: Waiting ...\n");      

    //int y=0;
    //for (y=0; y<15; y++){
        //gws_yield();
    //};

    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.

    gws_debug_print ("__gws_clone_and_execute_response: rd\n");

    // #caution
    // Waiting for response.
    // We can stay here for ever.

    if (fd<0){
        return (int) -1;
    }

response_loop:

// Read

    n_reads = 
        (ssize_t) recv(
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        //gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("__gws_clone_and_execute_response: recv fail.\n");
        printf          ("__gws_clone_and_execute_response: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        return -1;
        //exit (1);
    }

// The msg index.
// Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        // Reply!
        case GWS_SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;

        case GWS_SERVER_PACKET_TYPE_REQUEST:
        case GWS_SERVER_PACKET_TYPE_EVENT:            
        case GWS_SERVER_PACKET_TYPE_ERROR:
        default:
            return -1;
            break; 
    };

// Process reply.
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

    return (int) message_buffer[0];

// Process an event.
process_event:
    // gws_debug_print ("__gws_clone_and_execute_response: We got an event\n"); 
    return 0;
}


// Request.
// #todo
// Describe all the parameter.
static int 
__gws_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned int bg_color,
    unsigned long type,
    unsigned long style,
    unsigned long parent,
    char *name )
{
    unsigned long *message_buffer = (unsigned long *) &__gws_message_buffer[0];
    int n_writes = 0;
    char *Name;

    int client_pid = (int) rtl_current_process();
    int client_tid = (int) rtl_current_thread();

    gws_debug_print ("__gws_createwindow_request: wr\n");


// window id
    message_buffer[0] = 0;
// message code
    message_buffer[1] = GWS_CreateWindow;
// lon1 and long2
    message_buffer[2] = 0;
    message_buffer[3] = 0;
// l,t,w,h
    message_buffer[4] = (unsigned long)(left   & 0xFFFF);
    message_buffer[5] = (unsigned long)(top    & 0xFFFF);
    message_buffer[6] = (unsigned long)(width  & 0xFFFF);
    message_buffer[7] = (unsigned long)(height & 0xFFFF);
// background color
    message_buffer[8] = (unsigned long)(bg_color & 0xFFFFFFFF);
// type
    message_buffer[9] = (unsigned long)(type & 0xFFFF);
// parent window id.
    message_buffer[10] = parent; 
// #test
// style
// 0x0001 maximized
// 0x0002 minimized
// 0x0004 fullscreen
// ...
    message_buffer[11] = style;
// Client pid
    message_buffer[12] = client_pid;
// Client tid
    message_buffer[13] = client_tid;

// ------

// Local pointer
    Name = name;
    if ( (void*) Name == NULL ){
        Name = title_when_no_title;
    }

// String support
// Set up the string starting in the offset '14'.

    char buf[256];
    int i=0;
    int string_off=14;
    for (i=0; i<250; i++){
        message_buffer[string_off] = *Name;
        string_off++; Name++;
    };
    message_buffer[string_off] = 0;

// ------

    if ( fd<0 ){
       return (int) -1;
    }

// Write
    
    n_writes = -1;

    n_writes = 
        (int) send ( 
                  fd, 
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if ( n_writes <= 0 ){
        return (int) -1;
    }

    return (int) n_writes;
}

// Response
// A sincronização nos diz que já temos um reply.
static int __gws_createwindow_response(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    ssize_t n_reads=0;

// Waiting for response.
// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

    // #debug
    //gws_debug_print ("__gws_createwindow_response: Waiting ...\n");

// Entramos nessa rotina depois da sincronização dizer que
// ja temos um reply.
// Então não precis esperar por respostas.

    //for (y=0; y<15; y++){  gws_yield();  };


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.

    gws_debug_print ("__gws_createwindow_response: rd\n");

    if (fd<0){
        return (int) -1;
    }

// Read

    n_reads = 
        (ssize_t) recv ( 
                      fd, 
                      __gws_message_buffer, 
                      sizeof(__gws_message_buffer), 
                      0 );

// #bugbug
// If we do not read the file, so the flag will not switch
// and we will not be able to write into the socket.

    if (n_reads <= 0){
        return (int) -1;
    }

//
// The response message
//

// Recebemos alguma coisa.
// A mesagem pode ser de vários tipos.
// A mensagem que esperamos nesse caso é GWS_SERVER_PACKET_TYPE_REPLY.
// Porque estamos esperando resposta de um request.

    int wid = (int) message_buffer[0];
    int msg = (int) message_buffer[1];

    switch (msg){

    // reply
    case GWS_SERVER_PACKET_TYPE_REPLY: 
        return (int) wid;
        break;

    // error
    case GWS_SERVER_PACKET_TYPE_REQUEST:
    case GWS_SERVER_PACKET_TYPE_EVENT:
    case GWS_SERVER_PACKET_TYPE_ERROR:
    default:
        return -1;
        break;
    };

fail:
    return -1;
}


//
// == Functions =======================================================
//



// Draw char.
int 
gws_draw_char (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    unsigned int ch )
{
    int Response=0;
    int Value=0;

    if (fd<0)    {return -1;}
    if (window<0){return -1;}

// Request
    //gws_debug_print("gws_draw_char: request\n");
    int req_status = -1;
    req_status = __gws_drawchar_request (
        (int) fd,             // fd
        (int) window,         // window id
        (unsigned long) x,    // left
        (unsigned long) y,    // top
        (unsigned int) (color & 0xFFFFFFFF),
        (unsigned int) (ch & 0xFF) );
    if(req_status<=0)
        return -1;
    rtl_set_file_sync( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );


// Response
// Waiting to read the response.
    //gws_debug_print("gws_draw_char: response\n");
    while (1){
        Value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return -1; }
        if (Value == ACTION_NULL )  { return -1; }  //no reponse. (syncronous)
        //gws_yield();
    };

// A sincronização nos diz que já temos um reply.
    Response = __gws_drawchar_response ((int) fd);  

    return (int) Response;
}


// Draw text.
int 
gws_draw_text (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    char *string )
{
    int response =0;
    int Value=0;

    if (fd<0){
        return (int) -1;
    }

    if (window<0){
        return (int) -1;
    }

// Request
// IN: fd, window, x, y, color, string
    int req_status = -1;
    req_status = 
        (int) __gws_drawtext_request (
                  (int) fd,
                  (int) window,
                  (unsigned long) x,
                  (unsigned long) y,
                  (unsigned long) (color & 0xFFFFFFFF),
                  (char *) string );
    if (req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );

// Response
// Waiting to read the response.
    //gws_debug_print("gws_draw_text: response\n");
    while (1){
        Value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return -1; }
        if (Value == ACTION_NULL )  { return -1; }  //no reponse. (syncronous)
        //gws_yield();
    };

    response = (int) __gws_drawtext_response (fd);

    return (int) response;
}


// ========================================================
// clone and execute
//#todo: change arguments.
int 
gws_clone_and_execute2 (
    int fd, 
    unsigned long arg1,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4,
    char *string )
{
    int response=0;
    int Value=0;

    if (fd<0){
        return (int) -1;
    }

// Request
// IN: fd, window, x, y, color, string
    int req_status = -1;
    req_status = 
        (int) __gws_clone_and_execute_request (
                  (int) fd,
                  (unsigned long) arg1,
                  (unsigned long) arg2,
                  (unsigned long) arg3,
                  (unsigned long) arg4,
                  (char *) string );
    if(req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );

// Response
// Waiting to read the response.
    //gws_debug_print("gws_draw_text: response\n");
    while (1){
        Value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return -1; }
        if (Value == ACTION_NULL )  { return -1; }  //no reponse. (syncronous)
        //gws_yield();
    };

    response = 
        (int) __gws_clone_and_execute_response(fd);

    return (int) response;
}


/*
// #todo
// Services.
// This is a dialog with the library.
// We can use this for services just like initialization, shutdown ...
// IN: service number, ...
*/

void *gws_services ( 
    int service,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4 )
{
    // #todo
    return NULL;
}


/*
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
    unsigned long message_buffer[8];
    unsigned long Value=0;

    if ( pid<0 ){
        gws_debug_print ("gws_send_message_to_process: pid\n");
        return (int) (-1);
    }

// Window id
    message_buffer[0] = (unsigned long) window;
// Message code
    message_buffer[1] = (unsigned long) message;
// Data
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;

    message_buffer[4] = 0;  // this pid
    message_buffer[5] = 0;  // tid
    // ...

    Value = 
        (unsigned long) gws_system_call ( 
                            112, 
                            (unsigned long) &message_buffer[0], 
                            (unsigned long) pid, 
                            (unsigned long) pid );

// #todo
// Error message
    return (int) (Value & 0xF);
}


/*
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
    unsigned long message_buffer[8];
    unsigned long Value=0;

    if (tid<0){
        gws_debug_print ("gws_send_message_to_thread: tid\n");
        return (int) (-1);
    }

// Window ID
    message_buffer[0] = (unsigned long) window;
// Message code
    message_buffer[1] = (unsigned long) message;
// Data
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;

    message_buffer[4] = 0;  // this tid
    message_buffer[5] = 0;  // tid
    // ...

    Value = 
        (unsigned long) gws_system_call ( 
                            117, 
                            (unsigned long) &message_buffer[0], 
                            (unsigned long) tid, 
                            (unsigned long) tid );

// #todo
// Error message
    return (int) (Value & 0xF);
}

// gwssrv.bin has the permission for this job.
void gws_reboot(int fd)
{
    if(fd<0){
        return;
    }
    gws_async_command(fd,89,0,0);
}

void gws_update_desktop(int fd)
{
    if(fd<0){
        return;
    }
    gws_async_command(fd,11,0,0);
}



/*
// Se o window server entregar um evento ping,
// então respondemos com um evento pong.
// #todo: precisamos nos idntificar. Talvez nossa tid, talvez
// nosso pid, talvez a main_window ou a mesma janela
// indicada no evento.
void gws_pong(int fd);
void gws_pong(int fd)
{
    if(fd<0){
        return;
    }
    gws_async_command(fd,??,0,0);
}
*/


// Load a file using a pathname as an argument.
// #todo: Explain the return value.
int 
gws_load_path ( 
    char *path, 
    unsigned long buffer, 
    unsigned long buffer_len )
{
    unsigned long Value=0;

    if ( (void*) path == NULL ){
        return -1;
    }
    if ( *path == 0 ){
         return -1;
    }
    if ( buffer == 0 ){
        return -1;
    }
    if ( buffer_len == 0 ){
        return -1;
    }

// #todo
// Chame a rtl e não uma syscall.

    Value = 
        (unsigned long) gws_system_call ( 
                            4004, 
                            (unsigned long) path, 
                            (unsigned long) buffer, 
                            (unsigned long) buffer_len );

// #todo
// Error message.

    return (int) (Value & 0xF);
}


// Window position.
int 
gws_change_window_position ( 
    int fd, 
    int window, 
    unsigned long x, 
    unsigned long y )
{
    int Value=0;

    if (fd<0){
        return -1;
    }
    if (window<0){
        return -1;
    }

// Request
    int req_status = -1;
    req_status = (int) __gws_change_window_position_request(fd,window,x,y);
    if(req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync ( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );    

// Response
// Waiting to read the response.
    while (1){
        Value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return (int) -1; }
        //gws_yield();
    };
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
    int Value=0;

    if (fd<0){
        return (int) -1;
    }
    if (window<0){
        return (int) -1;
    }

// request
    int req_status=-1;
    req_status = (int) __gws_resize_window_request(fd,window,w,h);
    if (req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync ( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

// response
// Waiting to read the response.
    while (1){
        Value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return -1; }
        //gws_yield();
    };
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
    unsigned long Value=0;

    if (fd<0){
        return (int) -1;
    }
    if (window<0){
        return (int) -1;
    }

// #todo
// check the return values.

// Request
    int req_status = -1;
    req_status = (int) __gws_redraw_window_request (fd,window,flags);
    if (req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

// Response
// Waiting to read the response.
    while (TRUE){
        Value = (unsigned long) rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return -1; }
        if (Value == ACTION_NULL )  { return -1; }  //no reponse. (syncronous)
        //gws_yield();
    };
    __gws_redraw_window_reponse (fd);

    return 0;
}


// The server will return an event 
// from the its client's event queue.

struct gws_event_d *gws_get_next_event(
    int fd,
    struct gws_event_d *event )
{
    struct gws_event_d *e;
    unsigned long Value=0;

    if (fd<0){
        debug_print("gws_get_next_event: fd\n");
        return NULL;
    }

// Request
    int req_status = -1;
    req_status = (int) __gws_get_next_event_request(fd);
    if(req_status<=0){
        return NULL;
    }
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

// Response
// Waiting to read the response.
    while (TRUE){
        Value = (unsigned long) rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR )
        {
            return NULL; 
        }
    };
    e = (struct gws_event_d *) __gws_get_next_event_response (fd,event);

    if ( (void*) e == NULL ){
        debug_print("gws_get_next_event: fail\n");
    }

    return (struct gws_event_d *) e;
}


// The server will return the info about one given window.
struct gws_window_info_d *gws_query_window(
    int fd,
    int wid,
    struct gws_window_info_d *window_info )
{
    if(fd<0){
        return NULL;
    }
    if(wid<0){
        return NULL;
    }
    if( (void*) window_info == NULL ){
        return NULL;
    }

    return (struct gws_window_info_d *) gws_get_window_info(fd,wid,window_info);
} 


// The server will return the info about one given window.
struct gws_window_info_d *gws_get_window_info(
    int fd,
    int wid,
    struct gws_window_info_d *window_info ) 
{
    struct gws_window_info_d *wi;
    unsigned long Value=0;

    if (fd<0){
        debug_print("gws_get_window_info: fd\n");
        return NULL;
    }

// Request
    int req_status = -1;
    req_status = (int) __gws_get_window_info_request(fd,wid);
    if (req_status<=0){
        return NULL;
    }
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

// Response
// Waiting to read the response.
    while (TRUE){
        Value = (unsigned long) rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR )
        {
            return NULL; 
        }
    };

    wi = 
        (struct gws_window_info_d *) __gws_get_window_info_response( 
                                         fd, 
                                         window_info );

    if ( (void*) wi == NULL ){
        debug_print("gws_get_window_info: fail\n");
    }

    return (struct gws_window_info_d *) wi;
}

/*
 * gws_refresh_window:
 *     Refresh window.
 */
// #bugbug
// It is not working.
// The window server can not get the window number.

int gws_refresh_window (int fd, int window )
{
    int value=0;

    if (fd<0)    { return (int) -1; }
    if (window<0){ return (int) -1; }

// Request
    int req_status=-1;
    req_status = (int) __gws_refresh_window_request(fd,window);
    if (req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

// Response
// Waiting to read the response.
    while (TRUE){
        value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        if (value == ACTION_REPLY ) { break; }
        if (value == ACTION_ERROR ) { return -1; }
        if (value == ACTION_NULL )  { return -1; }  //no reponse. (syncronous)
        //gws_yield();
    };

    return (int) __gws_refresh_window_reponse(fd);
}


int
gws_refresh_retangle ( 
    int fd,
    unsigned long left, 
    unsigned long top, 
    unsigned long width, 
    unsigned long height )
{
    int Response=0;
    int Value=0;

    if (fd<0){
        return (int) -1;
    }

// Request
    int req_status=-1;
    req_status = 
        (int) __gws_refresh_rectangle_request (
                  (int) fd,
                  (unsigned long) left, 
                  (unsigned long) top,
                  (unsigned long) width,
                  (unsigned long) height );

    if (req_status<=0){
        return (int) -1;
    }
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

// Response
// Waiting to read the response.
    //gws_debug_print("gws_refresh_retangle: response\n");
    while (1){
        Value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_REPLY ) { break; }
        if (Value == ACTION_ERROR ) { return -1; }
        if (Value == ACTION_NULL )  { return -1; }  //no reponse. (syncronous)
        //gws_yield();
    };

// A sincronização nos diz que já temos um reply.
    Response = 
        (int) __gws_refresh_rectangle_response (fd);  

    return (int) Response;
}


// Atualiza o retângulo da surface da thread.
void 
setup_surface_retangle ( 
    unsigned long left, 
    unsigned long top, 
    unsigned long width, 
    unsigned long height )
{
    unsigned long Buffer[5];
    
    Buffer[0] = (unsigned long) left;
    Buffer[1] = (unsigned long) top;
    Buffer[2] = (unsigned long) (width  & 0xFFFF);
    Buffer[3] = (unsigned long) (height & 0xFFFF);
    Buffer[4] = 0;

    gramado_system_call ( 
        892, (unsigned long) &Buffer[0], 0, 0 );
}


void invalidate_surface_retangle (void)
{
    gramado_system_call ( 893, 0, 0, 0 );
}

// Async.
void gws_invalidate_window(int fd,int wid)
{
    if(fd<0){
        return;
    }
    if(wid<0){
        return;
    }
    gws_async_command(fd,13,0,wid);
}


/*
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
    unsigned long style,       //10. style
    unsigned int clientcolor,  //11, Cor da área de cliente
    unsigned int color )       //12, Color (bg) (para janela simples).
{
    int value=0;
    int wid = -1;
    char *Name;

    gws_debug_print("gws_create_window:\n");

    if (fd<0){
        return (int) -1;
    }

//#bugbug: parentwindow?

    //#todo
    //Um argumento passa o display usado
    //o display aponta para o socket a ser usado
    //display->fd

    //#todo
    // use more arguments.


// Local pointer

    Name = windowname;
    if ( (void*) Name == NULL ){
        Name = title_when_no_title;
    }

// Request
    int req_status=-1;
    req_status = 
        (int) __gws_createwindow_request ( 
                  fd, x, y, width, height, 
                  color, type, style, parentwindow, Name );
    if (req_status<=0){
        return (int) -1;
    }

    //ok set the sync
    rtl_set_file_sync( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );


// Response
// Waiting to read the response.
// Return the index returned by the window server.
// ??
// E se o arquivo for fechado pelo sistema?
// Ficaremos aqui para sempre?

    while (1)
    {
        value = 
            (int) rtl_get_file_sync( 
                      fd, 
                      SYNC_REQUEST_GET_ACTION );

        //if (value == ACTION_REQUEST){ rtl_yield(); }
        if (value == ACTION_REPLY ) { break; }
        if (value == ACTION_ERROR ) { return -1; }
        //if (value == ACTION_NULL )  { return -1; }  // no reply
    };

// A sincronização nos diz que já temos um reply.
// Simply read the file.
    wid = (int) __gws_createwindow_response(fd); 

    return (int) wid;
}

// Yield current thread.
void gws_yield (void)
{
    sc82(265,0,0,0);
}

// Refresh the background and yield the current thread
void gws_refresh_yield (int fd)
{
    if (fd<0){ return; }
    gws_refresh_window (fd, -4);  //??: fd,window
    gws_yield();
}

// Refresh a given window and yield the current thread.
void gws_refresh_yield2 (int fd, int window)
{
    if (fd<0)    { return; }
    if (window<0){ return; }
    gws_refresh_window (fd, window);
    gws_yield();
}

void gws_yield_n_times(unsigned long n)
{
    int i=0;
    if (n == 0){
        n=1;
    }
    for (i=0; i<n; i++){
        gws_yield();
    };
}


/*
 * gws_create_thread:
 *     Create a thread.
 *     #todo: 
 *     Precisamos uma função que envie mais argumentos.
 *     Essa será uma rotina de baixo nível para pthreads.
 *     Use const char
 */
// OUT:
// Is it a pointer to the ring0 thread structure?

void *gws_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name )
{
    //#define	SYSTEMCALL_CREATETHREAD     72
    debug_print ("gws_create_thread:\n");

    if ( init_eip == 0 ){
        debug_print ("gws_create_thread: init_eip\n");
        return NULL;
    }
        
    if ( init_stack == 0 ){
        debug_print ("gws_create_thread: init_stack\n");
        return NULL;
    }

    if ( (void*) name == NULL ){
        debug_print ("gws_create_thread: name\n");
        return NULL;
    }

    if (*name == 0){
        debug_print ("gws_create_thread: *name\n");
        return NULL;
    }

// OUT:
// Is it a pointer to the ring0 thread structure?

    //SYSTEMCALL_CREATETHREAD,
    return (void *) gws_system_call ( 
                        72,  
                        init_eip, 
                        init_stack, 
                        (unsigned long) name );
}


/*
 * gws_start_thread:
 *     Coloca no estado standby para executar pela primeira vez
 */

void gws_start_thread (void *thread)
{
    //unsigned long ret_value=0;
    
    // #define	SYSTEMCALL_STARTTHREAD  94 

    debug_print ("gws_start_thread:\n");

    // Is it a pointer to the ring0 thread structure?

    if ( (void*) thread == NULL ){
        debug_print ("gws_start_thread: thread\n");
        return;
    }

    //SYSTEMCALL_STARTTHREAD,
    gramado_system_call ( 
        94,  
        (unsigned long) thread, 
        (unsigned long) thread, 
        (unsigned long) thread );
}


// Clone the current process and execute the clone.
// #todo: Use 'const char*'.
// OUT: ??

int gws_clone_and_execute (char *name)
{
    unsigned long Value=0;

    if ( (void*) name == NULL ){ 
        debug_print("gws_clone_and_execute: name\n");
        return (int) -1; 
    }
    if ( *name == 0 ){ 
        debug_print("gws_clone_and_execute: *name\n");
        return (int) -1; 
    }

    // #todo
    // Ret = (int) rtl_clone_and_execute(name);
    
    Value = 
        (unsigned long) sc82 ( 900, (unsigned long) name, 0, 0 );

// #todo
// Error message

    return (int) (Value & 0xF);
}

// Get system metrics.
unsigned long gws_get_system_metrics (int index)
{
    if (index<0){
        return 0;
    }
    return (unsigned long) rtl_get_system_metrics( (int) index );
}


// Enter critical section
// close the gate
// Pega o valor do spinlock principal.
// Se deixou de ser 0 então posso entrar.
// Se ainda for 0, continuo no while.
// Depois de entrar, fecha o portão.
// TRUE = OPEN.
// FALSE = CLOSED.
// yield thread if closed.

void gws_enter_critical_section (void)
{
    unsigned long GateStatus=0;  // Closed.
// Waiting the value 1.
    while (TRUE)
    {
        // Get the gate status.
        GateStatus = (unsigned long) gws_system_call ( 226, 0, 0, 0 );
        // Enter if the gate is open.
        if (GateStatus == 1){
            goto done;
        }
        //gws_yield();
    };
// Close the gate. turn FALSE.
done:
    gws_system_call ( 227, 0, 0, 0 );
    return;
}


// exit critical section
// open the gate.
void gws_exit_critical_section (void)
{
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
// This a good thing when 
// creating a window manager as a client application.
struct gws_menu_d *gws_create_menu (
    int fd,
    int parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned int color )
{
    struct gws_menu_d  *menu;
    int window=0;

    // #
    // The synchronization is made when we call gws_create_window.


    if (fd<0){
        debug_print("gws_create_menu: [FAIL] fd\n");
        return (struct gws_menu_d *) 0;
    }

// #todo: Check parent validation
    if (parent<0){
    }

// #todo: 'count' limits.

// Menu

    menu = 
        (struct gws_menu_d *) malloc( sizeof(struct gws_menu_d) );

    if ( (void *) menu == NULL ){
        debug_print("gws_create_menu: [FAIL] menu\n");
        return (struct gws_menu_d *) 0;
    }

    // Offset related to the window
    menu->x = x;
    menu->y = y;

    // Dimensions
    menu->width  = width;
    menu->height = height;

    menu->color = (unsigned int) color;

    // ??
    // Are we selection am item
    menu->highlight = highlight;

    // Number of itens.
    menu->itens_count = count;

// Create menu window

    window = 
        (int) gws_create_window ( 
                  fd,
                  WT_SIMPLE, 1, 1, "Menu",
                  menu->x,  //Deslocamento em relação a janela mãe. 
                  menu->y,  //Deslocamento em relação a janela mãe. 
                  width, 
                  height,
                  parent, 0, color, color );

    if (window <= 0)
    { 
        debug_print("gws_create_menu: [FAIL] window\n");
        //free(menu);
        menu->window = 0;  //#bugbug !!!!
        return (struct gws_menu_d *) 0;
    }

// Saving 
// #bugbug
    menu->window = (int) window;
    menu->parent = (int) parent;

// Return the pointer.
    return (struct gws_menu_d *) menu;
}

// Create a menu item for a given valid menu.
// This a good thing when 
// creating a window manager as a client application.
struct gws_menu_item_d *gws_create_menu_item (
    int fd,
    char *label,
    int id,
    struct gws_menu_d *menu)
{
    struct gws_menu_item_d  *item;
    int window=0;    //menu item window

// #
// The synchronization is made when we call gws_create_window.

    if (fd<0){
        debug_print("gws_create_menu_item: [FAIL] fd\n");
        return (struct gws_menu_item_d *) 0;
    }

    if ( (void *) menu == NULL ){
        debug_print("gws_create_menu_item: [FAIL] menu\n");
        return (struct gws_menu_item_d *) 0;
    }

// create menu item.
    item = 
        (struct gws_menu_item_d *) malloc( sizeof(struct gws_menu_item_d) );

    if ( (void *) item == NULL ){
        debug_print("gws_create_menu_item: [FAIL] item\n");
        return (struct gws_menu_item_d *) 0;
    }

// Provisório

    if (id>5 || id>menu->itens_count)
    {
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
        window = 
            (int) gws_create_window ( 
                      fd,
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


// Expand a byte all over the long.
// #todo: This is valid only for 32bit 'unsigned int'
// We need to create another one for 8bytes long.
unsigned int gws_explode_byte_32 (unsigned char data)
{
    return (unsigned int) (data << 24 | data << 16 | data << 8 | data);
}


// Create empty file.
// #todo: Change parameter type to const char 
int gws_create_empty_file (char *file_name)
{

// #todo
// Use rtl, not a systemcall.

    unsigned long Value=0;


    if ( (void*) file_name == NULL ){
        debug_print("gws_create_empty_file: [FAIL] file_name\n");
        return (int) -1;
    }

    if ( *file_name == 0 ){
        debug_print("gws_create_empty_file: [FAIL] *file_name\n");
        return (int) -1;
    }

    Value = 
        (unsigned long) gramado_system_call ( 
                            43, 
                            (unsigned long) file_name, 
                            0, 
                            0 );

// #todo
// Error message.

    return (int) (Value & 0xF);
}


// Create empty directory.
// #todo: Change parameter type to const char 
int gws_create_empty_directory (char *dir_name)
{

// #todo
// Use rtl, not a systemcall.

    unsigned long Value=0;

    if ( (void*) dir_name == NULL ){
        debug_print("gws_create_empty_directory: [FAIL] dir_name\n");
        return (int)(-1);
    }

    if ( *dir_name == 0 ){
        debug_print("gws_create_empty_directory: [FAIL] *dir_name\n");
        return (int)(-1);
    }

// #todo
// Quais são os valores de retorno.
// TRUE or FALSE ?

    Value = 
        (unsigned long) gramado_system_call ( 
                            44, 
                            (unsigned long) dir_name, 
                            0, 
                            0 );

// #todo
// Error message

    return (int) (Value & 0xF);
}


// Set focus
// async request.
void gws_set_focus(int fd, int window)
{
    if (fd<0){
        return;
    }
    if (window<0){
        return;
    }
    // IN: fd, request, sub-request, data.
    gws_async_command( fd, 9, 0, window );
}

// Send async request.
// No response.
// #todo
// List some standard commands accepted by the ws.
// IN: 
// fd, request number, subrequest.
// #todo: We need a list of services we can all with this function.
void
gws_async_command ( 
    int fd, 
    unsigned long request,
    unsigned long sub_request,
    unsigned long data )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes=0;
    int Value=0;
    //char *name = "Window name 1";

    // #debug
    // gws_debug_print ("gws_async_command: send...\n"); 

// Enviamos um request para o servidor.
// Precisamos mesmo de um loop para isso?
// Write!
// Se foi possível enviar, então saimos do loop.  
// Nesse caso, corremos o risco de ficarmos presos
// caso não seja possível escrever.

// Window ID
    message_buffer[0] = 0;
// Message code. (2222?)
    message_buffer[1] = GWS_AsyncCommand;
// #todo: We need a list of services we can all with this function.
    message_buffer[2] = request;           // request
    message_buffer[3] = sub_request;       // sub request
// data
// #todo: We can deliver more data if we want.
    message_buffer[4] = data;  // data1
    // ...

    if (fd<0){
        debug_print("gws_async_command: fd\n");
        return;
    }

    n_writes = 
        (int) send ( 
                  fd,
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes <= 0){
         return;
    }

    rtl_set_file_sync ( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );

// No return.
    while (1)
    {
        Value = 
            (int) rtl_get_file_sync( 
                      fd, 
                      SYNC_REQUEST_GET_ACTION );

        // Essa é a sincronização esperada.
        // Não teremos uma resposta, mas precisamos
        // conferir a sincronização.
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_NULL )  { goto done; }
        if (Value == ACTION_ERROR ) { goto done; }
        
        //#debug
        gws_debug_print ("gws_async_command: Waiting sync flag\n"); 
    };
    
done:
    //gws_debug_print ("gws_async_command: done\n"); 
    return; 
}


void
gws_async_command2 ( 
    int fd, 
    unsigned long request,
    unsigned long sub_request,
    unsigned long data1,
    unsigned long data2,
    unsigned long data3,
    unsigned long data4 )
{
    unsigned long *message_buffer = 
        (unsigned long *) &__gws_message_buffer[0];
    int n_writes=0;
    int Value=0;
    //char *name = "Window name 1";

    // #debug
    // gws_debug_print ("gws_async_command2: send...\n"); 

// Enviamos um request para o servidor.
// Precisamos mesmo de um loop para isso?
// Write!
// Se foi possível enviar, então saimos do loop.  
// Nesse caso, corremos o risco de ficarmos presos
// caso não seja possível escrever.

// Window ID
    message_buffer[0] = 0;
// Message code. (2222?)
    message_buffer[1] = GWS_AsyncCommand;
// #todo: We need a list of services we can all with this function.
    message_buffer[2] = request;           // request
    message_buffer[3] = sub_request;       // sub request
// data
// #todo: We can deliver more data if we want.
    message_buffer[4] = (unsigned long) data1;  // data1
    message_buffer[5] = (unsigned long) data2;  // data2
    message_buffer[6] = (unsigned long) data3;  // data3
    message_buffer[7] = (unsigned long) data4;  // data4
    // ...

    if (fd<0){
        debug_print("gws_async_command2: fd\n");
        return;
    }

    n_writes = 
        (int) send ( 
                  fd,
                  __gws_message_buffer, 
                  sizeof(__gws_message_buffer), 
                  0 );

    if (n_writes <= 0){
         return;
    }

    rtl_set_file_sync ( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );

// No return.
    while (1)
    {
        Value = 
            (int) rtl_get_file_sync( 
                      fd, 
                      SYNC_REQUEST_GET_ACTION );

        // Essa é a sincronização esperada.
        // Não teremos uma resposta, mas precisamos
        // conferir a sincronização.
        //if (Value == ACTION_REQUEST){ rtl_yield(); }
        if (Value == ACTION_NULL )  { goto done; }
        if (Value == ACTION_ERROR ) { goto done; }
        
        //#debug
        gws_debug_print ("gws_async_command2: Waiting sync flag\n"); 
    };
    
done:
    //gws_debug_print ("gws_async_command2: done\n"); 
    return; 
}



// #test
// No response.
// Sending the wm's pid to the ws.
// Don't trust in method. There is no response.
// We can use this to broadcast.
void gws_send_wm_magic( int fd, int pid )
{
    if(fd<0) { return; }
    if(pid<0){ return; }
    gws_async_command(fd,7,0,pid);
}


// gws_open_display:
// + (1) Create the display structure.
// + (2) Create the socket file.
// + (3) Connect to the window server.
// IN: #todo: Explain it better.
// hostname:number.screen_number

struct gws_display_d *gws_open_display(char *display_name)
{
    struct gws_display_d *Display;

// ??
// O header está incluido?

    struct sockaddr_in  addr_in;

    addr_in.sin_family      = AF_INET;
    addr_in.sin_port        = __PORTS_WS;
    addr_in.sin_addr.s_addr = __IP(127,0,0,1); 

    int addrlen=0;
    addrlen = sizeof(addr_in);

    int client_fd = -1;

// (1)
// Create the display structure.

    Display = 
        (struct gws_display_d *) malloc( sizeof( struct gws_display_d ) );

    if ( (void*) Display == NULL ){
        printf ("gws_open_display: Couldn't create display\n");
        return NULL;
    }

// (2)
// Create the socket file.

    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("gws_open_display: Couldn't create socket\n");
       return NULL;
    }

// #todo: Colocar isso no fim da rotina.
    Display->used = TRUE;
    Display->magic = 1234;

    Display->fd        = client_fd;
    Display->lock      = FALSE;
    Display->connected = FALSE;
    // ...

    if ( (void*) display_name == NULL ){
        printf ("gws_open_display: [FAIL] display_name\n");
        return NULL;
    }

    if ( *display_name == 0 ){
        printf ("gws_open_display: [FAIL] *display_name\n");
        return NULL;
    }


// (3)
// Connect to the window server.

    while (TRUE){
        if (connect (client_fd, (void *) &addr_in, addrlen ) < 0){
            gws_debug_print("gws_open_display: Connection Failed \n");
            printf         ("gws_open_display: Connection Failed \n");
        }else{ break; };
    };

// Flag
    Display->connected = TRUE;

    //Display->used = TRUE;
    //Display->magic = 1234;

// Current display.
    gws_set_current_display(Display);

// Return the display structure pointer.
    return (struct gws_display_d *) Display;
}


void gws_close_display(struct gws_display_d *display)
{
    // #todo
    
    if ( (void*) display == NULL ){
        gws_debug_print("gws_close_display: display\n");
        return;
    }

    display->used = FALSE;
    display->magic = 0;

    // ??
    // close(display->fd);

    display = NULL;
}


// Change the current display for this library.
int gws_set_current_display(struct gws_display_d *display)
{
    if ( (void*) display == NULL ){
        return (int) -1;
    }

    if ( display->used != TRUE || 
         display->magic != 1234 )
    {
        return (int) -1;
    }

    libgwsCurrentDisplay = (struct gws_display_d *) display;

    return 0;
}

struct gws_display_d *gws_get_current_display(void)
{
    return (struct gws_display_d *) libgwsCurrentDisplay;
}


void gws_display_exit(struct gws_display_d *display)
{
    if ( (void*) display == NULL ){
        return;
    }

    if (display->magic!=1234){
        return;
    }

    display->running = FALSE;
}


/*
  // #todo
  // Send some pending requests.
void gws_flush_display ( struct gws_display_d *display );
void gws_flush_display ( struct gws_display_d *display )
{
}
*/



//test
struct gws_display_d *__ApplicationDisplay;
static int __ApplicationFD = -1;

int application_start(void)
{
    struct gws_display_d *Display;

// ============================
// Open display.
// IN: 
// hostname:number.screen_number

    Display = 
        (struct gws_display_d *) gws_open_display("display:name.0");

    if ( (void*) Display == NULL )
    {
        debug_print ("application_start: Couldn't open display\n");
        printf      ("application_start: Couldn't open display\n");
        //exit(1);
        goto fail;
    }

    if ( Display->fd <= 0 )
    {
        debug_print ("application_start: bad Display->fd\n");
        printf      ("application_start: bad Display->fd\n");
        //exit(1);
        goto fail;
    }

    __ApplicationDisplay = (struct gws_display_d *) Display;
    __ApplicationFD = (int) Display->fd;

// Return the socket for a
// connected client application

    //return (int) Display->fd;
    return (int) __ApplicationFD;

fail:
    __ApplicationDisplay = NULL;
    __ApplicationFD = -1;
    exit(1);
    return -1;
}

// #todo: gws_application_end()
void application_end(void)
{
    // #todo
    // Close the current display.
    exit(0);
}


int gws_enable_input_method(int method)
{
    if (method<0){
        return (int) -1;
    }

    switch (method){

    // Event queue in the current thread.
    case 1:
        gws_debug_print ("gws_enable_input_method: [1] \n");
        rtl_focus_on_this_thread();
        return 0;
        break;
    
    // ...
    
    default:
        gws_debug_print ("gws_enable_input_method: [FAIL] Invalid method\n");
        break;
    };
    
fail:
    return (int) -1;
}



// Default procedure.
// Call the window server.
// The purpose is sending commands to the window manager 
// that lives inside the window server. 
int 
gws_default_procedure (
    int fd, 
    int window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    gws_debug_print ("gws_default_procedure:\n");

    if (fd<0){
        return (int) (-1);
    }

    if (msg<0){
        return 0;
    }

    //
    // Messages
    //
    
    // Vamos mandar para o servidor algumas
    // mensagens que interessam ao window manager 
    // dentro do window server.
    
    // #todo
    // Algumas chamadas de sistema podem ficar aqui,
    // como client shutdown e coisas do tipo.
    // Some menu stuff?
    // Changes in the title bar... new text... redraw the bar.
    // + close window.
    // + F1: caso o aplicativo n~ao interceptou f1, mostraremos ajuda.
    // foco na janela ou ativar.
    // window position, window size.
    // Set cursor. (that text cursor.)
    // show window. (refresh)
    // sysmenu, control menu
    // copy global data.
    // Change UI state.
    
    switch (msg){

    // ...

    // Close process
    case MSG_CLOSE:
        // Para que o diálogo default feche o aplicativo,
        // esse parâmetro não pode ser '0'.
        // Se o kernel quiser fechar a aplicação, então tem que
        // colocar algum valor aqui.
        if (long1 != 0){
            exit(0);
        }
        return 0;
        break;


    // #bugbug
    // Nesse caso podemos ter duplicidade de tratamento,
    // com o aplicativo fazendo um tratamento antes desse.

    case MSG_SYSKEYDOWN:
        switch (long1){

            case VK_F1:
                //printf("gsw_default_procedure: #todo Help\n");
                return 0;
                break;

            case VK_F12:
                //printf("gsw_default_procedure: VK_F12\n");
                //gws_async_command(fd,8,1,1);
                return 0;
                break;
        };
        break;
        
        
    // Essa mensagem foi enviada pelo kernel.
    //case 11316:
        //printf("gsw_default_procedure: 11316\n");
        //exit(0);
        //gws_async_command(fd,8,1,1);
        //break;
    
    default:
        // printf("gsw_default_procedure: msg={%d}\n",msg);
        break;
    };
    
    // ...
    
    return 0;
}


//
// End.
//

