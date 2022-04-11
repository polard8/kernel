
// GWSSRV.BIN
// This is a ring0 display server and window manager.
// It has the same PID of the kernel, 0.
// #todo: 
// We need a fancy name for this project,
// not only 'gws'.

/*
 * File: main.c
 *    Main file for the Gramado Window Server.
 *    History:
 *        2020 - Created by Fred Nora.
 */

// See:
// Transformations
// http://math.hws.edu/graphicsbook/c2/s3.html
// See:
// https://wiki.osdev.org/Graphics_stack
// https://wayland-book.com/introduction/high-level-design.html
// ...
// See:
// x window system core protocol
// https://en.wikipedia.org/wiki/X_Window_System_core_protocol
// ...
// See:
// https://www.x.org/wiki/Releases/History/
// hostname:D.S
// [host]:<display>[.screen]
// [host]:<display>.[screen]
// main.c
// Arquivo principal do gws.
// As funções começam com o nome do módulo
// para que em client side começem com gws_

/*
See: https://wiki.osdev.org/Graphics_stack

    > Application Layer
    > Interoperation Layers
        +Desktop Management Layer
        +Window Management Layer 
    > Presentation Layers
        +Compositing Layer
        +Widget Toolkit Layer
        +Rendering Layer 
    > Display Layers
        +Device Driver Layer
        +Hardware Layer 

*/


// This file is part of this project.
// It is NOT a library.

#include "gws.h"


#define VERSION  "0.1"
#define VERSION_MAJOR  0
#define VERSION_MINOR  1

// Gramado Network Protocol 

// #standard
#define GNP_WID        0
#define GNP_MESSAGE    1
#define GNP_LONG1      2
#define GNP_LONG2      3
// #extension
#define GNP_LONG3      4
#define GNP_LONG4      5
#define GNP_LONG5      6
#define GNP_LONG6      7
// #body
#define GNP_BODY_OFFSET    16
// ...

// #test
#define MSG_OFFSET_SHORTSTRING  64
#define SHORTSTRING_SIZE        64
#define MSG_OFFSET_LONGSTRING  128
#define LONGSTRING_SIZE        256
// ...

static int IsAcceptingConnections = FALSE;
static int IsTimeToQuit = FALSE;
static int NoReply = FALSE;
static int Notify_PongClient=FALSE;
static int ____saved_server_fd = -1;
static int ____saved_wm_magic_pid = -1;  // ?? The wm sends us its pid
static int __saved_sync_id = -1;
static int connection_status = 0;
static int running = FALSE;


// =========================
// h:d.s
char *hostName;
char *displayNum;
char *screenNum;


//
// == Prototypes ============================================
//

static int on_execute(void);

// Get client's request from socket.
static void dispacher(int fd);

static int
gwsProcedure (
    int client_fd,
    struct gws_window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 );

static int initGraphics(void);
static void initBackground(void);
static void initClientSupport(void);
static void initClientStruct( struct gws_client_d *c );

//====================
// prototypes

// Line
static
int servicelineBackbufferDrawHorizontalLine (void);

// Char
// See> char.c
static
int serviceDrawChar(void);

// Text
static
int serviceDrawText(void);

// Rectangle
static
int serviceRefreshRectangle(void);

// Window
// See: window.c
static
int serviceCreateWindow (int client_fd);

static
int serviceChangeWindowPosition(void);

static
int serviceResizeWindow(void);

static
int serviceRedrawWindow(void);

static
int serviceRefreshWindow(void);

// Button
static
int serviceDrawButton (void); 


// When a client send us an event
static
int serviceClientEvent(void);

// When a client get the next event 
// from it's own queue.
static
int serviceNextEvent(void);

// See: main.c
static
int serviceAsyncCommand (void);

static
void serviceExitGWS(void);

static
int servicePutClientMessage(void);

static
int serviceGetClientMessage(void);

// See: main.c
static int serviceGetWindowInfo(void);

//====================



//
// ==============================================================
//

// Print a simple string in the serial port.
void gwssrv_debug_print (char *string)
{
    //if( (void*) string == NULL ){ return; }
    //if(*string == 0){ return; }

    gramado_system_call ( 289,
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}


// #bugbug
// For now we can't use this function in ring0, I guess.
int gwssrv_clone_and_execute ( char *name )
{
    
    if ( (void*) name == NULL ){ 
        printf ("gwssrv_clone_and_execute: [FAIL] name\n");
        return -1; 
    }
    
    if (*name == 0){ 
        printf ("gwssrv_clone_and_execute: [FAIL] *name\n");
        return -1; 
    }

    // #deprecated
    // return (int) gramado_system_call ( 900, (unsigned long) name, 0, 0 );
    
    // #todo
    // Use this one.
    return (int) sc82 ( 900, (unsigned long) name, 0, 0 );
}


// #todo
// We can use the rtl.
unsigned long gwssrv_get_system_metrics (int index)
{

    //if (index<0){
        //gde_debug_print ("gswsrv_get_system_metrics: fail\n");
        //return 0;
    //}
    //#define	SYSTEMCALL_GETSYSTEMMETRICS  250 

   return (unsigned long) gramado_system_call ( 250, 
                               (unsigned long) index, 
                               (unsigned long) index, 
                               (unsigned long) index );
}



// enter critical section
// close the gate
void gwssrv_enter_critical_section (void)
{
    int S=0;

    // Pega o valor do spinlock principal.
    // Se deixou de ser 0 então posso entrar.
    // Se ainda for 0, continuo no while.
    // TRUE = OPEN.
    // FALSE = CLOSED.
    // yield thread if closed.

    while (1){
        S = (int) gramado_system_call ( 226, 0, 0, 0 );

        if ( S == 1 ){ goto done; }
        
        //yield thread.
        //gramado_system_call (265,0,0,0); 
        sc82 (265,0,0,0);
    };

    // Close the gate. turn FALSE.
done:
    gramado_system_call ( 227, 0, 0, 0 );
    return;
}


// exit critical section
// open the gate.
void gwssrv_exit_critical_section (void)
{
    gramado_system_call ( 228, 0, 0, 0 );
}




//
// =============================================================
//


//??
// Quando um cliente tenta se desconectar.
/*
// internal
void client_shutdown (int fd);
void client_shutdown (int fd)
{
	//remove client
	//deallocate resources.
}
*/


//?? Die after to handle a request.
// no multiple requests.
/*
void client_die(int fd);
void client_die(int fd)
{
    client_shutdown(fd);
}
*/


// ??
/*
int client_start(int fd);
int client_start(int fd)
{
    return -1;//todo
}
*/



/*
int client_send_error_response(int fd);
int client_send_error_response(int fd)
{
    return -1;//todo
}
*/


// Getting the server pid.
/*
int get_server_pid();
int get_server_pid()
{
    return (int) ... ; //#todo
}
*/

// getting the client id
/*
int get_client_id();
int get_client_id()
{
    return (int) ... ; //#todo
}
*/


// setting the client id
/*
void set_client_id ( int id );
void set_client_id ( int id )
{
	//#todo
    //____client_id = id;
}
*/


/*
int
__WriteToClient ( 
    struct gws_client_d *who, 
    char *buf, 
    int count );
int
__WriteToClient ( 
    struct gws_client_d *who, 
    char *buf, 
    int count )
{
    return -1;
}
*/


/*
int WriteToClient (int fd);
int WriteToClient (int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_writes = 0;    // For responses.
 
    char *m = (char *) (&__buffer[0] + 16);
    sprintf( m, "gwssrv: This is a response from GWS!\n");

    // Primeiros longs do buffer.
    message_buffer[0] = next_response[0];         // Window ID.
    message_buffer[1] = SERVER_PACKET_TYPE_REPLY; // next_response[1] 
    message_buffer[2] = next_response[2];         // Return value (long1)
    message_buffer[3] = next_response[3];         // Return value (long2)

    if (fd<0)
        return 0;

   // #bugbug
   // How many times ?
   
__again:

    // #todo:
    // while(1){...}
    
    gwssrv_debug_print ("gwssrv: Sending response ...\n");

    //
    // Send
    //

    n_writes = write ( fd, __buffer, sizeof(__buffer) );
    //n_writes = send ( fd, __buffer, sizeof(__buffer), 0 );
    
    if (n_writes<=0){
        gwssrv_yield();
        goto __again;
    }


    // Cleaning
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;

    // Cleaning
    int c=0;
    for(c=0; c<32; c++)  //todo: 512
        next_response[c] = 0;

    gwssrv_debug_print ("gwssrv: Response sent\n");  
    
    return (int) n_writes;
}
*/


// Worker
// There is a vetor with values for the next response.
// Called by dispatcher().
// IN:
// fd, 1=REPLY | 2=EVENT | 3=ERROR
int __send_response(int fd, int type)
{
// Reusing the same buffer from the request.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];

    int n_writes = 0;  // For responses.

    int Status=0;

    //gwssrv_debug_print ("Sending response ...\n");  

//# it works.
    char *m = (char *) (&__buffer[0] + 16);
    sprintf( m, "~ Response from gwssrv \n");

//
// Primeiros longs do buffer.
//

// 0:
// wid
    message_buffer[0] = (unsigned long) next_response[0];  //wid


// 1:
// Type of reply.

    switch(type){
    case 1:  // normal reply
        message_buffer[1] = SERVER_PACKET_TYPE_REPLY;
        break;
    case 2:  // event
        message_buffer[1] = SERVER_PACKET_TYPE_EVENT;
        break;
    case 3:  // error
        message_buffer[1] = SERVER_PACKET_TYPE_ERROR;
        break;
    default:  // error
        message_buffer[1] = SERVER_PACKET_TYPE_ERROR;
        break;
    };

// 2 and 3:
// Signature in some cases.
// Can we deliver values here?
    message_buffer[2] = (unsigned long) next_response[2];  // long1
    message_buffer[3] = (unsigned long) next_response[3];  // long2


// 4,5,6,7  \./
// Data.
    message_buffer[4] = (unsigned long) next_response[4];
    message_buffer[5] = (unsigned long) next_response[5];
    message_buffer[6] = (unsigned long) next_response[6];
    message_buffer[7] = (unsigned long) next_response[7];

// 8,9,10,11  \o/
// Data.
    message_buffer[8]  = (unsigned long) next_response[8];
    message_buffer[9]  = (unsigned long) next_response[9];
    message_buffer[10] = (unsigned long) next_response[10];
    message_buffer[11] = (unsigned long) next_response[11];

// 12,13,14,15  \O/
// Data.
    message_buffer[12] = (unsigned long) next_response[12];
    message_buffer[13] = (unsigned long) next_response[13];
    message_buffer[14] = (unsigned long) next_response[14];
    message_buffer[15] = (unsigned long) next_response[15];


// more
    message_buffer[16] = (unsigned long) next_response[16];
    message_buffer[17] = (unsigned long) next_response[17];
    message_buffer[18] = (unsigned long) next_response[18];
    message_buffer[19] = (unsigned long) next_response[19];

    // ...

//__again:

//
// == Response ============================
//

    gwssrv_debug_print ("__send_response: Sending response ...\n");

    // #todo:
    // while(1){...}

    /*
    // Is current client connected.
    if (currentClient->is_connected == 0)
    {
        // [FAIL] Not connected.
        // close?
    }
    */


    if(fd<0 || fd>31){
        Status = -1;
        goto exit2;
    }

//
// Send
//

//nao podemos escrever em nosso proprio socket.
    if( fd == ____saved_server_fd )
    {
        printf("__send_response: fd == ____saved_server_fd\n");
        printf("The server can't write on your own socket\n");
        while(1){}
    }


    if( fd != 31 )
    {
        printf("__send_response: fd != 31\n");
        while(1){}
    }

// Write

    n_writes = write ( fd, __buffer, sizeof(__buffer) );
    //n_writes = send ( fd, __buffer, sizeof(__buffer), 0 );

// Cleaning
// Limpa se a resposta der certo ou se der errado.

    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;
    register int b=0;
    for (b=0; b<MSG_BUFFER_SIZE; ++b){
        __buffer[b] = 0;
    };

// Cleaning
// 32. #todo 512.

    register int c=0;
    for (c=0; c<NEXTRESPONSE_BUFFER_SIZE; ++c){
        next_response[c] = 0;
    };

// No. We couldn't send a response.
// O que acontece se nao conseguirmos enviar uma resposta?
// Certamente o cliente tentara ler e tera problemas.
// Deveriamos fechar a conexao?
// Deveriamos enviar um alerta
    
    if (n_writes<=0){
        gwssrv_debug_print ("__send_response: response fail\n");
        printf             ("__send_response: Couldn't send reply\n");
        //close(fd);
        Status=-1;
        goto exit2;
    }

// YES, We sent a response.
    if (n_writes>0){
        gwssrv_debug_print ("__send_response: Response sent\n");
        Status=0;
        goto exit0;
    }

// ??

exit2:
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;
    message_buffer[4] = 0;
    message_buffer[5] = 0;
exit1:
    gwssrv_yield();

// Sync. Set response.
exit0:
    rtl_set_global_sync( __saved_sync_id, SYNC_REQUEST_SET_ACTION, ACTION_REPLY );
    return (int) Status;
}


// Vamos criar a thread do compositor.
// No momento ela ficara apenas fazendo
// flush dos retângulos ...
// mas no futuro ela poderá copiar as janelas
// de seus buffers individuais para o backbuffer e ao fim
// fazer flush do backbuffer inteiro.

void Compositor_Thread(void)
{
    // #debug
    printf ("f\n");

    wmRefreshDirtyRectangles();
}






/*
 ****************************
 * dispacher:
 *
 */

// internal.
// Messages sent via socket.
// obs: read and write use the buffer '__buffer'
// in the top of this file.

// #todo:
// No loop precisamos de accept() read() e write();
// Get client's request from socket.

static void dispacher(int fd)
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];

    int n_reads  = 0;  // For requests.

    int Status=-1;
    int SendErrorResponse=FALSE;

// #todo:
// No loop precisamos de accept() read() e write();
//#atenção:
// A função accept vai retornar o descritor do 
// socket que usaremos ... por isso poderemos fecha-lo
// para assim obtermos um novo da próxima vez.

    //gwssrv_debug_print ("dispacher: \n");

    // Fail, cleaning.
    if (fd<0){
        gwssrv_debug_print ("dispacher: fd\n");
        goto exit2;
    }


//__loop:

//
// == Request ============================
//

// Requests may generate replies, events, and errors;
// Request packets are numbered sequentially by the server 
// as soon as it receives them.
// See:
// https://en.wikipedia.org/wiki/Round-trip_delay
// If the request is (XNextEvent), so the reply will be the event.

    /*
    // Is current client connected.
    if (currentClient->is_connected == 0)
    {
        // [FAIL] Not connected.
        // close?
    }
    */

// #important
// We can handle only requests.
// Drop it!

    int value = rtl_get_global_sync( __saved_sync_id, SYNC_REQUEST_GET_ACTION );
    if ( value != ACTION_REQUEST ){
        goto exit2;
    }

// #todo
// Devemos escrever em nosso próprio
// socket e o kernel copia??
// o kernel copia para aquele arquivo ao qual esse estivere conectado.
// olhando em accept[0]
// Precisamos fechar o client e yield se a leitura der errado?

//
// Recv
//


//nao podemos escrever em nosso proprio socket.
    if( fd == ____saved_server_fd )
    {
        printf("dispacher: fd == ____saved_server_fd\n");
        printf("The server can't read on your own socket\n");
        while(1){}
    }

    if( fd != 31 )
    {
        printf("dispacher: fd != 31\n");
        while(1){}
    }


    n_reads = read ( fd, __buffer, sizeof(__buffer) );
    if (n_reads <= 0){
        gwssrv_debug_print ("dispacher: read fail\n");
        goto exit2;
    }

//
// == Processing the request =============================
//

// Invalid request. 
// Clean and yield.

    if (message_buffer[1] == 0 ){
        gwssrv_debug_print ("dispacher: Invalid request\n");
        goto exit2;
    }

// Um cliente solicitou um evento.
// Vamos sinalizar o tipo de resposta que temos que enviar,
// caso nenhum erro aconteça.

    int doSendEvent = FALSE;
    if ( message_buffer[1] == GWS_GetNextEvent )
    {
        doSendEvent = TRUE;  // The response is an EVENT, not a REPLY.
    }


// Process request.
// Do the service.

    debug_print ("dispacher: Process request\n");

// OUT
// <0 : error 

    Status = gwsProcedure (
       (int) fd,
       (struct gws_window_d *) message_buffer[0], 
       (int)                   message_buffer[1],  // msg code
       (unsigned long)         message_buffer[2], 
       (unsigned long)         message_buffer[3] );

// Como o serviço não pode ser prestado corretamente.
// Então logo abaixo mandaremos uma resposta de erro
// e não uma resposta normal.

    if(Status < 0){
         SendErrorResponse = TRUE;
    }

//
// == Sending reply ==========
//

// Alguns requests não exigem resposta.
// Como é o caso das mensagens assíncronas.
// Entao precisamos modificar a flag de sincronizaçao.
// que ainda deve estar sinalizando um request.
// #todo
// O problema é que temos que conferir
// na biblioteca client-side se o cliente espera ou não
// por uma resposta para um dado tipo de mensagens.
// No momento todos os requests esperam por reposta?

    if (NoReply == TRUE){
        rtl_set_global_sync( 
            __saved_sync_id, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
        goto exit0;
    }


//
// == reponse ================
//

// IN:
// fd, 1=REPLY | 2=EVENT | 3=ERROR


// ==========================================
// ERROR: (3)
// Se o serviço não pode ser prestado corretamente.
// Error message.
    if( SendErrorResponse == TRUE )
        Status = (int) __send_response(fd,3);

// ==========================================
// EVENT: (2)
// Se o serviço foi prestado corretamente.
// Era uma solicitação de evento
// Event.
    if (doSendEvent == TRUE)
        Status = (int) __send_response(fd,2);

// ==========================================
// REPLY: (1)
// Se o serviço foi prestado corretamente.
// Era uma solicitação de serviço normal,
// então vamos enviar um reponse normal. Um REPLY.
// Normal reply.
    if (doSendEvent != TRUE)
        Status = (int) __send_response(fd,1);

// A mensagem foi enviada normalmente,
// Vamos sair normalmente.

    //if(Status >= 0)
        //goto exit0;

// Fall

exit2:
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;
    message_buffer[4] = 0;
    message_buffer[5] = 0;
exit1:
    //gwssrv_yield();
exit0:
    return;
}



/*
 //#test
void ____get_system_message( unsigned long buffer );
void ____get_system_message( unsigned long buffer )
{
    // Get message.
    gwssrv_enter_critical_section();
    gramado_system_call ( 111,
            (unsigned long) buffer,
            (unsigned long) buffer,
            (unsigned long) buffer );
    gwssrv_exit_critical_section();
}
*/


#define wsMSG_KEYDOWN     20
#define wsMSG_KEYUP       21
#define wsMSG_SYSKEYDOWN  22
#define wsMSG_SYSKEYUP    23

#define wsVK_F1    0x3B  //59    // No DOS é 0x170.  
#define wsVK_F2    0x3C  //60 
#define wsVK_F3    0x3D  //61 
#define wsVK_F4    0x3E  //62 


#define wsVK_RETURN    0x1C
#define wsVK_TAB       0x0F

#define wsCOLOR_BLACK    0x000000
#define wsCOLOR_GRAY     0x808080 



int 
wsInputProcedure ( 
    struct gws_window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    switch (msg)
    {
        // 20 = MSG_KEYDOWN
        case wsMSG_KEYDOWN:
            switch (long1)
            {

                // [Enter] - Finalize the command line and compare.
                case wsVK_RETURN:
                    input('\0');
                    //shellCompare();
                    //asm("int $3");
                    goto done;
                    break; 

                case wsVK_TAB: 
                    printf("\t");
                    goto done; 
                    break;

                // keyboard arrows
                case 0x48: printf ("UP   \n"); goto done; break;
                case 0x4B: printf ("LEFT \n"); goto done; break;
                case 0x4D: printf ("RIGHT\n"); goto done; break;
                case 0x50: printf ("DOWN \n"); goto done; break;

                case 0x47: 
                    printf ("HOME\n");
                    goto done; 
                    break;
                    
                case 0x4F: 
                    printf ("END \n"); 
                    goto done; 
                    break;

                //pageup pagedown
                case 0x49: printf ("PAGEUP   \n"); goto done; break;
                case 0x51: printf ("PAGEDOWN \n"); goto done; break;

                // insert delete
                case 0x52: printf ("INSERT\n"); goto done; break;
                case 0x53: printf ("DELETE\n"); goto done; break;

                default:
                    input ( (unsigned long) long1 );  
                    printf("%c",long1); fflush(stdout);
                    break;
            };
            break;

  // 22 = MSG_SYSKEYDOWN
        case wsMSG_SYSKEYDOWN:
            switch (long1)
            {
                case wsVK_F1: printf ("F1\n");  break;
                case wsVK_F2: printf ("F2\n");  break;
            };
            break;
    };

done:
    return 0;
}



/*
 **********************************
 * gwsProcedure:
 *     Main dialog.
 */

// Called by dispacher().

// #todo
// Dependendo do tipo de request, então construiremos
// a resposta ou prestatemos os serviço.
// Para cada tipo de request o servidor precisa construir
// uma resposta diferente.
// O request afeta os campos da mensagem.
// Esses campos estão em um buffer, mas poderiam estar
// em um arquivo json.
// Types:
// + Null: fail.
// + Identify: The server needs to identify itself.
// + Get all objects:
// + Set inspected object:
// + Set property: Probably setting a property of an object.
// + Disconnect:
// ...

// OUT
// <0 : error 

static int
gwsProcedure ( 
    int client_fd,
    struct gws_window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    int Status=0;  //ok
    int my_pid = -1;

    // #debug
    //debug_print ("gwssrv: gwsProcedure\n");
    
    //#debug
    //return 0;

    // See:
    // globals.h

    switch (msg){

    // If we received the message GWS_Quit and
    // there is no more windows, so quit the application.
    case GWS_Quit:
        if( windows_count == 0 ){
            IsTimeToQuit=TRUE;
        }
        break;

    //case GWS_KeyDown:
    //case GWS_KeyUp:
    //case GWS_SysKeyDown:
    //case GWS_SysKeyUp:
        //gwssrv_debug_print ("gwssrv: GWS_KeyDown\n");
        //#todo: Call a helper function to handle keyboard events.
        //break;

    // 20
    // Mensagens de digitação.
    //case GWS_KeyDown:
        //gwssrv_debug_print ("gwssrv: GWS_KeyDown\n");
        //break;

    // 21
    //case GWS_KeyUp:
        //gwssrv_debug_print ("gwssrv: GWS_KeyDown\n");
        //break;

    // 22
    //case GWS_SysKeyDown:
        //gwssrv_debug_print ("gwssrv: GWS_KeyDown\n");
        //break;

    // 23
    //case GWS_SysKeyUp:
        //gwssrv_debug_print ("gwssrv: GWS_SysKeyUp\n");
        //switch ( long1)
        //{
        //    case VK_F1:
        //        gwssrv_debug_print("gwssrv: gwsProcedure VK_F1 Connection ON\n");
        //        connection_status = 1;
        //        break;
        //    case VK_F2:
        //        gwssrv_debug_print("gwssrv: gwsProcedure VK_F2 Connection OFF\n");
        //        connection_status = 0;
        //        break;
        //    case VK_F3:
        //        gwssrv_debug_print ("gwssrv: F3\n");
        //        bmpDisplayBMP (0,0,0); //#todo: test.
        //        break;
        //    case VK_F4:
        //        gwssrv_debug_print ("gwssrv: F4 [EXIT] Exiting the server ...\n");
        //        running = 0;
        //        break;
            // ...
        //    default:
        //        gwssrv_debug_print ("gwssrv: MSG_SYSKEYUP\n");
        //        break;
        //}
        //break;

    // #todo
    // Isso poderia significar que existe uma estrutura
    // de request no mesmo estilo do X presente no
    // final do buffer de mensage, por exemplo
    // no offset 400
    // Mesma coisa aconteceria com as respostas.
    // A biblioteca client side pode conter um wrapper
    // com o protocolo X, colocando a estrutura de request 
    // do final do buffer da mensagem e sinalizar no header do
    // buffer que esse buffer contem uma mensagem que segue o
    // protocolo X.
    // #todo: Criar o arquivo Xproto.h ... xproto.h
    // GWS_X_Request:
         //break;

    // ===========================
    // Here starts the gws requests

    // Hello!
    // Draw text inside the root window.
    // screen_window = __root_window

    case GWS_Hello:
        gwssrv_debug_print ("gwssrv: Message number 1000\n");
        //#bugbug: Esse endereço de estrutura esta mudando para um valor
        //que nao podemos acessar em ring3.
        if ( (void*) gui->screen_window != NULL)
        {
            //if ( gui->screen->used == 1 && gui->screen->magic == 1234 ){
                dtextDrawText ( 
                    (struct gws_window_d *) gui->screen_window,
                    long1, long2, COLOR_GREEN,
                    "gwssrv: Hello friend. This is the Gramado Window Server!");
                
                gws_show_backbuffer();
            //}
        }
        NoReply = FALSE;   //The client-side library is waiting for response.
        break;

    // Create Window
    // Usará o buffer global
    // See: window.c
    case GWS_CreateWindow:
        gwssrv_debug_print ("gwssrv: [1001] serviceCreateWindow\n");
        serviceCreateWindow(client_fd);
        NoReply = FALSE;   // We need to return the window id.
        break; 

    // backbuffer putpixel
    case GWS_BackbufferPutPixel:
        servicepixelBackBufferPutpixel(); 
        NoReply = FALSE;    //The client-side library is waiting for response.
        break;

    // backbuffer draw horizontal line
    case GWS_DrawHorizontalLine:
        servicelineBackbufferDrawHorizontalLine();
        NoReply = FALSE;  //  //The client-side library is waiting for response.
        break;

    // Draw char
    // See: char.c
    case GWS_DrawChar:
        gwssrv_debug_print ("gwssrv: [1004] serviceDrawChar\n");
        serviceDrawChar();
        //NoReply = FALSE;  // asyncronous
        NoReply = TRUE;   // syncronous
        break;

    // Draw text
    // See: dtext.c
    case GWS_DrawText:
        gwssrv_debug_print ("gwssrv: [1005] serviceDrawText\n");
        serviceDrawText();
        //NoReply = FALSE;  //The client-side library is waiting for response.
        NoReply = TRUE;     // syncronous
        break;

    // Refresh window
    case GWS_RefreshWindow:
        gwssrv_debug_print ("gwssrv: [1006] serviceRefreshWindow\n");
        serviceRefreshWindow();
        //NoReply = FALSE;
        NoReply = TRUE;    // syncronous
        break;

     // Redraw window
     case GWS_RedrawWindow:
         gwssrv_debug_print ("gwssrv: [1007] serviceRedrawWindow\n");
         serviceRedrawWindow();
         //NoReply = FALSE;
         NoReply = TRUE;    // syncronous
         break;

    // Resize window
    case GWS_ResizeWindow:
        gwssrv_debug_print ("gwssrv: [1008] serviceResizeWindow\n");
        serviceResizeWindow();
        NoReply = FALSE;
        break;

    case GWS_ChangeWindowPosition:
        gwssrv_debug_print ("gwssrv: [1009] serviceChangeWindowPosition\n");
        serviceChangeWindowPosition();
        NoReply = FALSE;
        break;

    // ...

    // backbuffer putpixel. (again)
    // IN: Color, x, y
    case GWS_BackbufferPutPixel2:
        grBackBufferPutpixel ( 
            (unsigned long) COLOR_PINK, 
            (unsigned long) long1, 
            (unsigned long) long2 );
        NoReply = FALSE;
        break;

    // ...


    // Disconnect.
    // shutdown.
    // Um cliente quer se desconectar.
    case GWS_Disconnect:
        gwssrv_debug_print ("gwssrv: [2010] Disconnect\n");
        // DisconnectCurrentClient = TRUE;  // #todo
        // NoReply = TRUE;  // #todo
        break;


    // Refresh screen 
    // refresh screen using kgws service. 
    case GWS_RefreshScreen:
        gwssrv_debug_print ("gwssrv: [2020] gws_show_backbuffer\n");
        gws_show_backbuffer();
        //NoReply = FALSE;      // #todo
        break;




    // Refresh rectangle ... 
    // See: wm.c
    case GWS_RefreshRectangle:
        gwssrv_debug_print ("gwssrv: [2021] serviceRefreshRectangle\n");
        serviceRefreshRectangle();
        NoReply = FALSE;
        break;


    // ?? #bugbug: The client only sends requests.
    // GWS_GetSendEvent
    case 2030:
        gwssrv_debug_print ("gwssrv: [2030] serviceClientEvent\n");
        //serviceClientEvent();
        //NoReply = FALSE;  // #todo
        break;

// The server will return an event from the its client's event queue.
    case GWS_GetNextEvent:
        gwssrv_debug_print ("gwssrv: [2031] serviceNextEvent\n");
        serviceNextEvent();
        NoReply = FALSE; // Yes. We need a reply.
        break;

    // See: grprim.c
    case GWS_GrPlot0:  
        gwssrv_debug_print ("gwssrv: [2040] serviceGrPlot0\n");
        serviceGrPlot0();  
        NoReply = FALSE;
        break;

    // See: grprim.c
    case GWS_GrCubeZ:  
        gwssrv_debug_print ("gwssrv: [2041] serviceGrCubeZ\n");
        serviceGrCubeZ();  
        NoReply = FALSE;
        break;

    // See: grprim.c
    case GWS_GrRectangle:  
        gwssrv_debug_print ("gwssrv: [2042] serviceGrRectangle\n");
        serviceGrRectangle();  
        NoReply = FALSE;
        break;

    // #todo
    // Segue serviços graficos 3d.
    // ...

    // #test
    // async command: 
    case GWS_AsyncCommand:
        gwssrv_debug_print ("gwssrv: [2222] calling serviceAsyncCommand\n");
                  //printf ("gwssrv: [2222] calling serviceAsyncCommand\n");
        serviceAsyncCommand();
        NoReply = TRUE;         // Do not send a reply.
        break;

    case GWS_PutClientMessage:
        gwssrv_debug_print ("gwssrv: [GWS_PutClientMessage]\n");
        servicePutClientMessage();
        NoReply = TRUE;
        break;

    case GWS_GetClientMessage:
        gwssrv_debug_print ("gwssrv: [GWS_GetClientMessage]\n");
        serviceGetClientMessage();
        NoReply = FALSE;
        break;

// Let's get one event from the client's event queue.
// Send it as a response.
    case GWS_DrainInput:
        gwssrv_debug_print("gwssrv: gwsProcedure 8080\n");
        break;

    case GWS_GetWindowInfo:
        serviceGetWindowInfo();
        NoReply = FALSE;   // YES, send the response with the data.
        break;


    // ...

    default:
        gwssrv_debug_print ("gwssrv: Default message number\n");
        //printf ("msg=%d ",msg);
        // NoReply = TRUE; //#todo
        Status = -1;  // Not ok.
        break;
    }

//#todo ???
// NoReply = TRUE; 

//done:
    return (int) Status;
}


static void initBackground(void)
{
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();
    int WindowId = -1;

    gwssrv_debug_print ("gwssrv: initBackground\n");

    if ( w==0 || h==0 )
    {
        gwssrv_debug_print ("initBackground: w h\n");
        printf             ("initBackground: w h\n");
        exit(1);
    }


// The background window
// #todo
// Se estivermos em JAIL, podemos arriscar algum background melhor.
// Talvez alguma imagem.

    __root_window = 
        (struct gws_window_d *) CreateWindow ( 
            WT_SIMPLE, 
            0, //style
            1, //status 
            1, //view
            "RootWindow",  
            0, 0, w, h,   
            gui->screen_window, 0, 
            COLOR_BACKGROUND, COLOR_BACKGROUND );

    // #debug
    // asm ("int $3");

    if ( (void *) __root_window == NULL )
    {
        gwssrv_debug_print ("initBackground: __root_window\n"); 
        printf             ("initBackground: __root_window\n");
        exit(1);
    }

    if ( __root_window->used != TRUE || 
         __root_window->magic != 1234 )
    {
        gwssrv_debug_print ("initBackground: __root_window validation\n"); 
        printf             ("initBackground: __root_window validation\n");
        exit(1);
    }

// Register the window.
    WindowId = RegisterWindow(__root_window);
    if (WindowId<0){
        gwssrv_debug_print ("initBackground: Couldn't register window\n");
        printf             ("initBackground: Couldn't register window\n");
        exit(1);
    }

    //#debug
    //asm ("int $3");

// BMP
// Testing bmp.
// See:
// gramado/themes

    if (current_mode == GRAMADO_JAIL){
        gwssrv_display_system_icon ( 1, 8, 8 );
    }else{
        gwssrv_display_system_icon ( 2, 8, 8 );
    };

// See: 
// gws.c

    if (current_mode == GRAMADO_JAIL)
    {
        gwssrv_debug_print ("gwssrv: initBackground: Calling refresh_screen\n");
        //refresh_screen();
    }

    //gwssrv_debug_print ("gwssrv: initBackground: done\n");

// #debug
    //refresh_screen();
    //while(1){}
}



/*
 * initGraphics:
 *     Initialize the graphics support.
 */

// Initialize the window server infrastructure.
// The current display and the current screen.
// Initialize the 3d support.

static int initGraphics(void)
{
    int __init_status = -1;

    //debug_print("initGraphics\n");
    //printf("initGraphics: \n");

    window_server->graphics_initialization_status = FALSE;

// gwsInit
// Initialize the window server infrastructure.
// The current display and the current screen.
// It will create the root window.
// See: gws.c

    __init_status = gwsInit();
    if (__init_status != 0)
    {
        debug_print ("initGraphics: [PANIC] Couldn't initialize the graphics\n");
        printf      ("initGraphics: [PANIC] Couldn't initialize the graphics\n");
        goto fail;
        //exit(1);
    }

// Create root window.
// Create and update the taskbar window.

    initBackground();
    create_taskbar();
    wm_Update_TaskBar("Welcome!");


//#debug
    //gws_show_backbuffer();
    //while(1){}
//
// == checks ==============
//

// Check if we already have the root window.

    if ( (void*) __root_window == NULL )
    {
        gwssrv_debug_print ("initGraphics: [FAIL] root window doesn't exist\n");
        printf             ("initGraphics: [FAIL] root window doesn't exist\n");
        goto fail;
        //exit(1);
    }

//#debug
    //gws_show_backbuffer();
    //while(1){}

// Initialize the graphics support.
// Now we can use 3d routines.
// See: grprim.c
    
    //gwssrv_debug_print ("initGraphics: Calling grInit() \n");
    //printf ("initGraphics: Calling grInit() \n");
    grInit();


//#debug
    //gws_show_backbuffer();
    //while(1){}


    // #debug
    //gwssrv_debug_print ("initGraphics: :)\n");
    //printf ("initGraphics: :)\n");
    //asm("int $3");
    //while(1){}


//
// == demos ==================================
//

// Always run some demo if we are in JAIL mode.
// It's an animation in the initialization.
// Seleciona a animaçao.
// Nao deve travar, deve ter timeout.

    if (current_mode == GRAMADO_JAIL)
    {
         //demos_startup_animation(1);
         // ...
    }

    if (current_mode == GRAMADO_HOME)
    {
         //demos_startup_animation(2);  //fred0
         //demos_startup_animation(3);  //fred1
         //demos_startup_animation(4);  //fred2
         //demos_startup_animation(10);  //triangle
         //demos_startup_animation(13); //Terry's window
         //gwssrv_show_backbuffer();
         // ...
         //while(1){}
    }


//#debug
    //gws_show_backbuffer();
    //while(1){}

    // #debug
    //asm("int $3");

//
// == tests =================================================
//
 
    /*
     //testes com z positivo
    grPlot0(0, 4, 4,COLOR_RED);     // q1
    grPlot0(3, 4, 4,COLOR_RED);     // q1 afasta para q1
    grPlot0(90, 4, 4,COLOR_RED);     // q1 afasta para q1
    
    grPlot0(0, 4,-4,COLOR_GREEN);   // q2
    grPlot0(3, 4,-4,COLOR_GREEN);   // q2  afasta  para q1   
    grPlot0(90, 4,-4,COLOR_GREEN);   // q2  afasta  para q1    
    
    grPlot0(0,-4,-4,COLOR_BLUE);    // q3
    grPlot0(3,-4,-4,COLOR_BLUE);    // q3 afasta  para q1
    grPlot0(90,-4,-4,COLOR_BLUE);    // q3 afasta  para q1
    
    grPlot0(0,-4, 4,COLOR_YELLOW);  // q4 
    grPlot0(3,-4, 4,COLOR_YELLOW);  // q4 afasta  para q1
    grPlot0(90,-4, 4,COLOR_YELLOW);  // q4 afasta  para q1
    */


     /*
     //testes com z negativo
    grPlot0 ( 0, 4, 4,COLOR_RED);     // q1
    grPlot0 (-3, 4, 4,COLOR_RED);     // q1 afasta para q3
    grPlot0 (-9, 4, 4,COLOR_RED);     // q1 afasta para q3
    grPlot0 (-11, 4, 4,COLOR_RED);     // q1 afasta para q3
    

    grPlot0( 0, 4,-4,COLOR_GREEN);   // q2
    grPlot0(-3, 4,-4,COLOR_GREEN);   // q2  afasta  para q3   
    grPlot0(-9, 4,-4,COLOR_GREEN);   // q2  afasta  para q3    
    grPlot0(-11, 4,-4,COLOR_GREEN);   // q2  afasta  para q3    
    
    grPlot0( 0,-4,-4,COLOR_BLUE);    // q3
    grPlot0(-3,-4,-4,COLOR_BLUE);    // q3 afasta  para q3
    grPlot0(-9,-4,-4,COLOR_BLUE);    // q3 afasta  para q3
    grPlot0(-11,-4,-4,COLOR_BLUE);    // q3 afasta  para q3
    
    grPlot0( 0, -4, 4,COLOR_YELLOW);  // q4 
    grPlot0(-3, -4, 4,COLOR_YELLOW);  // q4 afasta  para q3
    grPlot0(-9, -4, 4,COLOR_YELLOW);  // q4 afasta  para q3
    grPlot0(-11, -4, 4,COLOR_YELLOW);  // q4 afasta  para q3
    */    

    /*
    int y=0;
    int x=0;
    int z=0;
   
    z=0;
    for( y=0; y<32; y++)
    {
        for( x=0; x<32; x++)
            grPlot0 ( z, x, y,COLOR_RED);
    
        z++;
    }

    z=0;
    for( y=0; y<32; y++)
    {
        for( x=0; x<32; x++)
            grPlot0 ( z, -x, -y,COLOR_BLUE);
    
        z--;
    }
    */


    //int i=0;
   
    /*
    for (i=0; i<4; i++)
    {    
       //ok
       plotCircle ( i*8, i*8, 100, COLOR_GREEN); 
    };
    */

    /*
    for (i=0; i<4; i++)
    {
       plotEllipseRect (
            i*8, i*8, 
            30, 220, 
            COLOR_BLUE);
    };
    */

    /*
    int i=0;
    for (i=0; i<5; i++)
    { 
       plotLine3d ( 
           2, 2, 0,     // vertex 1
           20, i*20, 0,
           COLOR_RED );
    };
    */

     // Lines.

     /*
     grPlot0 ( 0, 0, 40, COLOR_WHITE ); //MARCADOR
     plotLine3d ( 
         0,    0,  0,
         0,   40,  0,
         COLOR_RED );

     grPlot0 ( 0, 40, 0, COLOR_WHITE ); //MARCADOR
     plotLine3d ( 
         0,    0,  0,
         40,   0,  0,
         COLOR_GREEN );


     grPlot0 ( 0, -40, -40, COLOR_WHITE ); //MARCADOR
     plotLine3d ( 
         0,    0,  0,
         -40,  -40,  0,
         COLOR_BLUE );
     */

    //rectangle(
    //    8,8,
    //    80,80, COLOR_YELLOW );

 
    /*
    cube ( 
        15,25,25,35,    // back
        20,10,30,30,   // front
        COLOR_WHITE );
    */


    /*
    int i=0;
    for (i=0; i<5; i++){
    cubeZ ( 
        15,25,25,35,    // back
        20,10,30,30,   // front
        COLOR_WHITE, i*40 );
    };
    */
   
   
    //Terry's window
    //demoTerry();
    
    
    //noraDrawingStuff();
   
   
    //noraDrawingStuff3(-1);
    //noraDrawingStuff3(0);
    //noraDrawingStuff3(1);
 
 
    /*
    int i=0;
    for (i=0; i<100; i++){
            //noraDrawingStuff3 (i,i,0);
            noraDrawingStuff3 (-i,-i,0);
            //rectangle(8,8,i,i,COLOR_BLUE);
            //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
            //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
            //cool
            plotCircleZ ( -i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            //igual o de cima.
            //plotCircleZ ( -i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
            //plotEllipseRect ( i, i, i*5, i*5, COLOR_BLUE);
            //plotEllipseRectZ ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };
    */

 
    /*
    plotCharBackbufferDrawcharTransparentZ (  (8*0), 0, COLOR_RED, 'G', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*1), 0, COLOR_RED, 'R', 0 );   
    plotCharBackbufferDrawcharTransparentZ (  (8*2), 0, COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*3), 0, COLOR_RED, 'M', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*4), 0, COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*5), 0, COLOR_RED, 'D', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*6), 0, COLOR_RED, 'O', 0 );

    //plotCharBackbufferDrawcharTransparentZ (  0, (8*0),  COLOR_RED, 'G', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, (8*1),  COLOR_RED, 'R', 0 );   
    plotCharBackbufferDrawcharTransparentZ (  0, (8*2),  COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, (8*3),  COLOR_RED, 'M', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, (8*4),  COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, (8*5),  COLOR_RED, 'D', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, (8*6),  COLOR_RED, 'O', 0 );

    //plotCharBackbufferDrawcharTransparentZ (  -(8*0), 0, COLOR_RED, 'G', 0 );
    plotCharBackbufferDrawcharTransparentZ (  -(8*1), 0, COLOR_RED, 'R', 0 );   
    plotCharBackbufferDrawcharTransparentZ (  -(8*2), 0, COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  -(8*3), 0, COLOR_RED, 'M', 0 );
    plotCharBackbufferDrawcharTransparentZ (  -(8*4), 0, COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  -(8*5), 0, COLOR_RED, 'D', 0 );
    plotCharBackbufferDrawcharTransparentZ (  -(8*6), 0, COLOR_RED, 'O', 0 );

    //plotCharBackbufferDrawcharTransparentZ (  0, -(8*0),  COLOR_RED, 'G', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, -(8*1),  COLOR_RED, 'R', 0 );   
    plotCharBackbufferDrawcharTransparentZ (  0, -(8*2),  COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, -(8*3),  COLOR_RED, 'M', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, -(8*4),  COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, -(8*5),  COLOR_RED, 'D', 0 );
    plotCharBackbufferDrawcharTransparentZ (  0, -(8*6),  COLOR_RED, 'O', 0 );
    */

    //matrix_demo1();

    
    //plotLineRect4(8,8,80,80, COLOR_BLACK);  //ok. it works.
    //plotLineRectZ ( 8,8,0, 80,80,0, COLOR_BLACK);    //ok. it works.
    //plotLineRectZ ( 8,8,100, 80,80,100, COLOR_WHITE);    
   
    //testLines(8,8,80,80, COLOR_BLACK); //ok triangulo invertido.
    //testLinesZ ( 8,8,0, 80,80,0, COLOR_BLACK); //ok triangulo invertido.    
    //testLinesZ ( 8,8,100, 80,80,100, COLOR_WHITE);    //ok triangulo invertido.



    //plotCharBackbufferDrawcharTransparent ( 80, 80, COLOR_RED, 'X' );
    
    /*
    plotCharBackbufferDrawcharTransparentZ (  10,  10, COLOR_RED, 'G', -10 );
    plotCharBackbufferDrawcharTransparentZ (   0,   0, COLOR_RED, 'R', -10 );
    plotCharBackbufferDrawcharTransparentZ ( -10, -10, COLOR_RED, 'A', -10 );
    plotCharBackbufferDrawcharTransparentZ ( -20, -20, COLOR_RED, 'M', -10 );
    plotCharBackbufferDrawcharTransparentZ ( -30, -30, COLOR_RED, 'A', -10 );
    plotCharBackbufferDrawcharTransparentZ ( -40, -40, COLOR_RED, 'D', -10 );
    plotCharBackbufferDrawcharTransparentZ ( -50, -50, COLOR_RED, '0', -10 );
    */
       
    //See: wm.c
    //create_main_menu();
  
    //gws services
    //gws_refresh_rectangle(0,0,400,400);
    //gws_show_window_rect(gui->screen);
    
    
    //noraDrawingStuff3 (0,0,0);
   
    /* 
    cubeZ ( 
        0,     0,    100,     10,   // back
        0+40, 0-20, 100+40, 10-20,   // front
        COLOR_WHITE, 0 );
    
    cubeZ ( 
        0,     0,    100,     10,   // back
        0+40, 0-20, 100+40, 10-20,   // front
        COLOR_WHITE, 100 );
    */

    //ras_rectangleZ (
        //0+40, 0-20, 100+40, 10-20,
        //COLOR_WHITE, 0 ); 

    // inflate or deflate several times.
    // only jail.
    
    //cube_demo1();
    //cube_demo2();
    
    /* 
    // line
    plotQuadBezierSeg ( 
        0,  0, 0,    //x0, y0, z0, 
        40, 40, 0,   //x1, y1, z1,
       100, 20, 0,  //x2, y2, z2, 
       COLOR_WHITE );
   */
   
    
    //curveDemo();
    
    
    // fred demo ======
    
    //fredDemo0();
    //fredDemo1();
    //fredDemo2(); // $bootcastle
    //...


    /*
     //ok isso funcionou.
    struct gr_rectangle_d *rect;
    rect = (void *) malloc( sizeof( struct gr_rectangle_d ) );
    if ( (void*) rect != NULL )
    {

        rect->p[0].x = 0;
        rect->p[0].y = 20;
        rect->p[0].z = 0;
        rect->p[0].color = COLOR_PINK;
        
        rect->p[1].x = 20;
        rect->p[1].y = 20;
        rect->p[1].z = 0;
        rect->p[1].color = COLOR_PINK;
        
        rect->p[2].x = 20;
        rect->p[2].y = 0;
        rect->p[2].z = 0;
        rect->p[2].color = COLOR_PINK;
        
        rect->p[3].x = 0;
        rect->p[3].y = 0;
        rect->p[3].z = 0;
        rect->p[3].color = COLOR_PINK;
        
        // plot rectangle 
        rectangleZZ ( (struct gr_rectangle_d *) rect );
    }
    */
    
    /*
     //ok, it works
    plotCharBackbufferDrawcharTransparentZ (  (8*0), 0, COLOR_RED, 'G', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*1), 0, COLOR_RED, 'R', 0 );   
    plotCharBackbufferDrawcharTransparentZ (  (8*2), 0, COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*3), 0, COLOR_RED, 'M', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*4), 0, COLOR_RED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*5), 0, COLOR_RED, 'D', 0 );
    plotCharBackbufferDrawcharTransparentZ (  (8*6), 0, COLOR_RED, 'O', 0 );
    */
    

    //
    // Refresh
    //

    // #debug
    //asm("int $3");

// #bugbug
// Fail!!!
// See: gws.c

    //gws_show_backbuffer();

// invalidate the surface in ring0.
    invalidate_surface_retangle();

    // #debug
    //asm("int $3");

    // while(1){}



    // Change
    // Se encontrar o 0x80 muda para 0x50 caso contrario mude para 0x00
    //grDCMono ( CurrentDisplay, 0x80, 0x50, 0x00 );
 
    // Se encontrar 0x80 mude para 0x50.
    //grDCColorChg ( CurrentDisplay, 0x80, 0x50 );
  
    // filtro
    // atenuando
    //grDCColorChg ( CurrentDisplay, 0x80, 0x80 - 0x30 );
    //grDCColorChg ( CurrentDisplay, 0xC0, 0x80 - 0x30 );
    //grDCColorChg ( CurrentDisplay, 0xFF, 0x80 - 0x30 );
    //grDCColorChg ( CurrentDisplay, 0x00, 0x80 - 0x30 );
    //while(1){}

//done:
    window_server->graphics_initialization_status = TRUE;
    return 0;

fail:
    window_server->graphics_initialization_status = FALSE;
    return -1;
}


// Initialize the client list.
// This is an array of connections.
// See: clients.h

static void initClientSupport(void)
{
    int i=0;

    gwssrv_debug_print ("initClientSupport:\n");

    for (i=0; i<CLIENT_COUNT_MAX; i++)
    {
        connections[i] = 0;
    };
 
 
//
// The current client
//

// #todo
// We need the information about the current client
// And we need a list of the connected clientes.

    //currentClient = (struct gws_client_d *) 0;
    currentClient = NULL;

//
// The server client
//

    serverClient = 
        (struct gws_client_d *) malloc ( sizeof( struct gws_client_d ) );
    
    if ( (void *) serverClient == NULL )
    {
        gwssrv_debug_print ("initClientSupport: [FATAL] Couldn't create serverClient\n");
        printf             ("initClientSupport: [FATAL] Couldn't create serverClient\n");
        exit(1);
    }

//
// ID = 0.
//
    serverClient->id = 0;

    serverClient->is_connected = FALSE;

// The fd of the server.
// Nothing for now.
    serverClient->fd = -1;

// The pid of the server.
    serverClient->pid = (pid_t) getpid();
// group.
    serverClient->gid = getgid();

// The server is not visible ... 

    serverClient->is_visible = FALSE;
    
    //serverClient->window = ?;
    
    // ...

    serverClient->used = TRUE;
    serverClient->magic = 1234;

// The first client.
    first_client = (struct gws_client_d *) serverClient;
    
    first_client->next = NULL;

// Save us in the list of connections.

    connections[SERVER_CLIENT_INDEX] = (unsigned long) serverClient;
}


static void initClientStruct( struct gws_client_d *c )
{
    register int i=0;

    if ( (void *) c == NULL ){
        gwssrv_debug_print("initClientStruct: [FAIL] c\n");
        return;
    }

// ID
// #todo
    c->id = -1;  //fail

//geometry
    c->l = 0;
    c->t = 0;
    c->w = 50;
    c->h = 50;

    c->is_connected = FALSE;
    c->fd  = -1;
    c->pid = -1;
    c->gid = -1;
    
    c->is_visible = FALSE;

// No tags yet.
    for(i=0; i<4; i++)
       c->tags[i] = FALSE;

//done:
    c->used = TRUE;
    c->magic = 1234;
}

/*
 //Send the message in the buffer to all the clients.
 //This is a great opportunity to shutdown the clients
 //if it is not connected.

void gwssrv_message_all_clients(void);
void gwssrv_message_all_clients(void)
{
}
*/


// When a client sent us an event
// ??? mas o cliente envia as coisas via request, ???
static
int serviceClientEvent(void)
{
    // The buffer is a global variable.
    //unsigned long *message_address = (unsigned long *) &__buffer[0];

    //return 0;  //ok
    return -1;
}


// When a client get the next event from it's own queue.
// The parameters 
// :::: Retira em head.
// Uma opção é enviaremos mensagens para 
// a fila na thread associada a essa janela.

static int serviceNextEvent (void)
{
    //#debug
    //debug_print("serviceNextEvent: suspended\n");
    //printf("serviceNextEvent\n");

// Window with focus.
    struct gws_window_d *w;
    
    w = (struct gws_window_d *) get_focus();
    if( (void*) w==NULL ){
        return -1;
    }

    //w->single_event.wid   = w->id;
    //w->single_event.msg   = 1000;  // >>>>>> EVENT TYPE <<<<<<<
    //w->single_event.long1 = 1;   // signature
    //w->single_event.long2 = 2;   // signature

// Building the next response.
// It will be sent in the socket loop.

//header
    next_response[0] = 0;  //
    next_response[1] = SERVER_PACKET_TYPE_EVENT;  //msg type
    next_response[2] = 1234;  //signature
    next_response[3] = 5678;  //signature

// Do we have a new event?
    if( w->single_event.has_event != TRUE )
    {
        next_response[5] = 0;  // Null event type.
        goto done;
    }

// the message packet.
    next_response[4] = w->single_event.wid;  // window
    next_response[5] = w->single_event.msg;  // >>>>>> EVENT TYPE <<<<<<<
    next_response[6] = w->single_event.long1;
    next_response[7] = w->single_event.long2;

done:
    w->single_event.has_event = FALSE;
    w->single_event.wid=0;
    w->single_event.msg = 0;
    w->single_event.long1 = 0;
    w->single_event.long2 = 0;
    return 0;
//fail:
    //return -1; // pra gerar resposta de erro
}


static int serviceGetWindowInfo(void)
{

    unsigned long *message_address = (unsigned long *) &__buffer[0];

    //#todo
    // Vamos pegar informações sobre
    // uma janela indicada no request.
    
    struct gws_window_d *w;

// ##
// Using the root window for testing purpose.

    //root window
    //int wid = __root_window->id;
    //w = (struct gws_window_d *) __root_window;

    //taskbar window
    //int wid = __taskbar_window->id;
    //w = (struct gws_window_d *) __taskbar_window;


    printf("serviceGetWindowInfo: :)\n");

    int wid = -1;
    int msg_code = -1;

// Get wid and message code.

    wid      = (int) message_address[0];  // window id 
    msg_code = (int) message_address[1];  // message code

    if(wid<0 || wid >= WINDOW_COUNT_MAX)
        return -1;

    if(msg_code != GWS_GetWindowInfo)
        return -1;

// Get window pointer.

    w = (struct gws_window_d *) windowList[wid];

    if( (void*) w == NULL )
        return -1;
    if(w->used!=TRUE)
        return -1;
    if(w->magic!=1234)
        return -1;

// Header
    next_response[0] = wid;  //
    next_response[1] = SERVER_PACKET_TYPE_REPLY;  //msg type
    next_response[2] = 1234;  //signature
    next_response[3] = 5678;  //signature

// Window
    next_response[7]  = (unsigned long) w->left;
    next_response[8]  = (unsigned long) w->top; 
    next_response[9]  = (unsigned long) w->width;
    next_response[10] = (unsigned long) w->height;

// Client rectangle.
    next_response[13] = (unsigned long) w->rcClient.left;
    next_response[14] = (unsigned long) w->rcClient.top; 
    next_response[15] = (unsigned long) w->rcClient.width;
    next_response[16] = (unsigned long) w->rcClient.height;

// #debug
    //printf("serviceGetWindowInfo: l=%d t=%d w=%d h=%d\n",
        //__root_window->left, 
        //__root_window->top, 
        //__root_window->width, 
        //__root_window->height );

    return 0;     //ok, send a reply response.
    //return -1;  //fail, send an error response.
}


// #todo
// Close all the clients and close the server.
static
void serviceExitGWS(void)
{
    printf ("serviceExitGWS: \n");
    
    // Kill all the clients.
    printf ("[TODO] Kill all the clients\n");

    // #todo
    // Deallocate resources used by the server.

    // Close the server.
    printf ("[TODO] Close all the clients\n");
    exit(0);
}

// #todo
// Now we put messages only in the window structure's message queue.
static
int servicePutClientMessage(void)
{
    debug_print("servicePutClientMessage: deprecated\n");
    return 0;
}


// #todo
// Now we get messages only in the window structure's message queue.
static
int serviceGetClientMessage(void)
{
    debug_print("serviceGetClientMessage: deprecated\n");
    return 0;
}


// Async request.
// No response.
// #bugbug: Esta travando.
static
int serviceAsyncCommand (void)
{
    //O buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    // int window_id=0;
    unsigned long message_id=0;
    unsigned long request_id=0;
    unsigned long subrequest_id=0;
    unsigned long data=0;

// Parameters
    // window_id  = message_address[0];
    message_id    = message_address[1];   // message code.
    request_id    = message_address[2]; 
    subrequest_id = message_address[3];
    data          = message_address[4];

    // ...

    gwssrv_debug_print ("serviceAsyncCommand:\n");

// Validate our message number.

    if (message_id != 2222)
    {
        gwssrv_debug_print ("serviceAsyncCommand: [ERROR] message_id\n");
                    printf ("serviceAsyncCommand: [ERROR] message_id\n");
        return (int) (-1);
    }

//
// id
//
    // #debug
    // printf ("serviceAsyncCommand: [request %d] \n", request_id);
 
    switch (request_id){

    // 1 =  Exit GWS
    // #todo:
    // Close all the clients and close the server.
    case 1:
        gwssrv_debug_print ("serviceAsyncCommand: [1]  Exit GWS\n");
        //printf ("serviceAsyncCommand: [request 1] Closing server\n");
        printf("serviceAsyncCommand: Exit GWS\n");
        serviceExitGWS();
        printf("serviceAsyncCommand: [FAIL] fail when closing the GWS\n");
        exit(0);
        break;

    case 2:
        gwssrv_debug_print ("serviceAsyncCommand: [2] \n");
        printf("PING\n");
        //Notify_CloseClient = TRUE;
        //Notify_PongClient = TRUE;
        //exit(0);
        return 0;
        break;

    case 3:
        gwssrv_debug_print ("serviceAsyncCommand: [3] hello\n");
        printf("HELLO\n");
        //exit(0);
        return 0;
        break;

    // Demos:
    // See: demos.c
    case 4:
        gwssrv_debug_print ("serviceAsyncCommand: [4] \n");
        if (current_mode == GRAMADO_JAIL)
        {
            gwssrv_debug_print("serviceAsyncCommand: [request 4] demo\n"); 
            demos_startup_animation(subrequest_id);
            gwssrv_show_backbuffer();
            return 0;
        }
        break;

    // Draw black rectangle.
    // #bugbug: trava ...
    //case 5:
       //gwssrv_debug_print ("serviceAsyncCommand: [5] \n");
       //if (current_mode == GRAMADO_JAIL)
       //{
           //rectBackbufferDrawRectangle ( 
           //    0, 0, 28, 8, COLOR_GREEN, TRUE,
           //    0 );  //rop_flags
           //return 0;
       //}
       //break;

    // Setup if we will show or not the 'fps window'.
    case 6:
        gwssrv_debug_print ("serviceAsyncCommand: [6] \n");
        if( subrequest_id == TRUE ){ show_fps_window = TRUE;  return 0; }
        if( subrequest_id != TRUE ){ show_fps_window = FALSE; return 0; }
        //show_fps_window = FALSE;
        break;


    // Register wm pid
    // #suspended: o wm fica no ws por enquanto.
    case 7:
        gwssrv_debug_print ("serviceAsyncCommand: [7] Register wm pid\n");
        //printf ("serviceAsyncCommand: [7] [BREAKPOINT] Register wm pid\n");
         ____saved_wm_magic_pid = (int) data;
        //exit(0);
        return 0;
        break;
 
    // 8
    // Window Manager requests. Power Trio.
    // As mensages aqui interessam somente ao window manager
    // que esta dentro do window server.
    case 8:
        gwssrv_debug_print ("serviceAsyncCommand: [8] \n");
        printf ("serviceAsyncCommand: [8] \n");
        if (subrequest_id = 1)
        {
            //exit(0);
        }
        break;

    case 9:
        gwssrv_debug_print ("serviceAsyncCommand: [9] \n");
        set_window_with_focus(data);
        break;


    // #test
    // drawing a rect using ring0 and ring3 routines.
    // TRUE = use kgws ; FALSE =  do not use kgws.
    case 10:
        gwssrv_debug_print ("serviceAsyncCommand: [10] \n");
                    printf ("serviceAsyncCommand: [10] \n");

        rectBackbufferDrawRectangle0(
            10, 10, 40, 40,
            COLOR_RED,
            TRUE,
            0,        // rop falgs
            FALSE );   // TRUE = use kgws. (kernel service)

        gws_refresh_rectangle(10, 10, 40, 40);
        return 0;
        
        break;

    case 11:
        wm_update_desktop(TRUE); //see: wm.c
        return 0;
        break;

    case 12:
        __switch_focus();
        return 0;
        break;

    case 13:
        invalidate_window_by_id(data);
        return 0;
        break;

    // ...

    // Set flag to quit the server.
    case 88:
        printf("88: IsTimeToQuit\n");
        IsTimeToQuit = TRUE;
        break;

    // Reboot the system via ws.
    case 89:
        printf("89: Reboot via ws\n");
        rtl_reboot();
        break;

    // ...

    default:
        gwssrv_debug_print ("serviceAsyncCommand: [ERROR] bad request\n");
                 // printf ("serviceAsyncCommand: [ERROR] bad request\n");
        // return -1;
        break;
    };

//fail:
    gwssrv_debug_print ("serviceAsyncCommand: FAIL\n");
    return (int)(-1);
}


/*
 * serviceCreateWindow:
 *
 *     Create a window.
 *     Service: GWS_CreateWindow.
 *     It's a wrapper.
 *     Chamaremos a função que cria a janela com base 
 * nos argumentos que estão no buffer, que é uma variável global 
 * nesse documento.
 *     Mostraremos a janela na tela ao fim dessa rotina.
 *     #todo: Mas poderíamos simplesmente marcar como 'dirty'.
 */

// Called by gwsProcedure in main.c

// #todo
// Receive the tid of the client in the request packet.
// Save it as an argument of the window structure.
static
int serviceCreateWindow (int client_fd)
{

// #test
// The structure for the standard request.

    gReq r;


    //loop
    register int i=0;

    // The buffer is a global variable.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    struct gws_window_d *Window;
    struct gws_window_d *Parent;
    int pw=0;

    int id = -1;

    // Arguments.
    unsigned long x=0;
    unsigned long y=0;
    unsigned long w=0;
    unsigned long h=0;
    unsigned int color=0;
    unsigned long type=0;


// Device context
    unsigned long deviceLeft   = 0;
    unsigned long deviceTop    = 0;
    unsigned long deviceWidth  = (__device_width  & 0xFFFF );
    unsigned long deviceHeight = (__device_height & 0xFFFF );


    // tid da control thread do cliente.
    int ClientPID = -1;
    int ClientTID = -1;


    gwssrv_debug_print ("serviceCreateWindow:\n");
    //printf ("serviceCreateWindow:\n");

//
// Get the arguments.
//


// The header.
// 0,1,2,3

    r.wid  = message_address[0];  // window id
    r.code = message_address[1];  // message code
    r.ul2  = message_address[2];  // data1
    r.ul3  = message_address[3];  // data2

// l,t,w,h

    r.ul4 = message_address[4];
    r.ul5 = message_address[5];
    r.ul6 = message_address[6];
    r.ul7 = message_address[7];

    x = (unsigned long) (r.ul4 & 0xFFFF);
    y = (unsigned long) (r.ul5 & 0xFFFF);
    w = (unsigned long) (r.ul6 & 0xFFFF);
    h = (unsigned long) (r.ul7 & 0xFFFF);

// Background color.
    r.ul8 = message_address[8];
    color = (unsigned int) (r.ul8 & 0x00FFFFFF );

// type
    r.ul9 = message_address[9];
    type = (unsigned long) (r.ul9 & 0xFFFF);


// Parent window ID.
    r.ul10 = message_address[10]; 
    pw = (int) (r.ul10 & 0xFFFF); 

//#test
    unsigned long my_style=0;
    r.ul11 = message_address[11];  
    my_style = (unsigned long) r.ul11;  // 8 bytes  

// Client pid
    r.ul12 = message_address[12];  // client pid
    ClientPID = (int) (r.ul12 & 0xFFFF);

// Client caller tid
    r.ul13 = message_address[13];  // client tid
    ClientTID = (int) (r.ul13 & 0xFFFF);

//========
// 14:
// This is the start of the string passed via message.
// Copy 256 bytes of given string.
// Do we ha a limit?

//++
// String support 
// Copiando para nossa estrutura local.
    int string_off = 14; 
    for (i=0; i<256; ++i)
    {
        r.data[i] = message_address[string_off];
        string_off++;
    };
    r.data[i] = 0;
//--

// ========================================

    // #debug
    //printf ("serviceCreateWindow: pid=%d tid=%d *breakpoint\n", 
    //    ClientPID, ClientTID );
    //while(1){}


//
// Purify
//
    x = (x & 0xFFFF);
    y = (y & 0xFFFF);
    w = (w & 0xFFFF);
    h = (h & 0xFFFF);

// Final Limits

    //if( x >= deviceWidth )
        //return -1;

    //if( y >= deviceHeight )
        //return -1;


    //#debug
    //printf("%s\n",name_buffer);
    //while(1){}

//===================

// Limits

    if (pw<0 || pw>=WINDOW_COUNT_MAX)
    {
        gwssrv_debug_print("serviceCreateWindow: parent window id fail\n");
        pw=0;
        exit(1);
    }

// Get parent window structure pointer.

    Parent = (struct gws_window_d *) windowList[pw];

// #bugbug
// Ajuste improvidsado

    if ( (void *) Parent == NULL )
    {
        gwssrv_debug_print ("serviceCreateWindow: parent window struct fail\n");
        
        
        // #bugbug
        // #todo: panic here.
        if ( (void*) gui == NULL )
        {
            gwssrv_debug_print ("serviceCreateWindow: gui fail\n");
            //exit(1);
        }
        
        //if ( (void*) gui != NULL ) )
        //{
        //    Parent = gui->screen_window;
        //}
        
        //  #bugbug
        //  This is a test.
        exit(1); 
    }

//
// Draw
//

// See:
// window.c

    Window = 
        (struct gws_window_d *) CreateWindow ( 
                                    type, 
                                    my_style,  // style
                                    1,         // status 
                                    1,         // view
                                    r.data,    // name
                                    x, y, w, h, 
                                    Parent, 0, 
                                    COLOR_PINK, color ); 

    if ( (void *) Window == NULL )
    {
       gwssrv_debug_print ("gwssrv: CreateWindow fail\n");
       next_response[1] = 0;
       return -1;
    }

// Register window
    id = RegisterWindow(Window);
    if (id<0){
        gwssrv_debug_print ("gwssrv: serviceCreateWindow Couldn't register window\n");
        next_response[1] = 0;  // msg code.
        return -1;
    }


//===============================================

//
// The client fd.
//

    Window->client_fd = (int) client_fd;



//
// Input queue
// 

// Initialized the input queue

/*
    // #deprecated ...
    // Enviaremos mensagens para a fila na thread
    // associada a essa janela.
    // Indicado em client_tid.

    //int i=0;
    for ( i=0; i<32; ++i )
    {
        Window->window_list[i] = 0;
        Window->msg_list[i]    = 0;
        Window->long1_list[i]  = 0;
        Window->long2_list[i]  = 0;
        Window->long3_list[i]  = 0;
        Window->long4_list[i]  = 0;
    };
    Window->head_pos = 0;
    Window->tail_pos = 0;
*/
//===============================================


//#test

// prepara o nome
    int name_len = strlen(Window->name);
    if(name_len > 32){ name_len = 32; }
    char w_name[64];
    sprintf(w_name,":: ");
    strncat(w_name, Window->name, name_len);
    w_name[63]=0;

// Coloca na fila
// #test: notifica na barra de tarefas

    int manage_status = -1;

    if(Window->type == WT_OVERLAPPED)
    {
        // adiciona na lista de janelas
        wm_add_window_into_the_list(Window);
        
        // associa a janela com uma estrutura de cliente.
        manage_status = wmManageWindow(Window);
        if(manage_status<0){
            printf("serviceCreateWindow: wmManageWindow fail\n");
            while(1){}
        }
        
        // atualiza a barra de tarefas,
        // notificando a criaçao dessa janela.
        wm_Update_TaskBar((char *) w_name);
    }


// #test
// Save the tid of the client.
    
    Window->client_pid = ClientPID;
    Window->client_tid = ClientTID;

//
// The client's fd.
//

// #todo
// We need to register the client's fd.
// It is gonna be used to send replies, just like
// input events.
    
    // Window->client_fd = ?;

// Building the next response.
// It will be sent in the socket loop.

    next_response[0] = (unsigned long) id;        // window
    next_response[1] = SERVER_PACKET_TYPE_REPLY;  // msg code
    next_response[2] = 0;
    next_response[3] = 0;

//
// Show
//

// Invalidate rectangle

// #todo: 
// We need a flag here. Came from parameters.

    // if( Show == TRUE )
    gws_show_window_rect(Window);

    // if( Show == FALSE )
    //Window->dirty = TRUE;

    gwssrv_debug_print ("serviceCreateWindow: done\n");

    return 0;
}

// Draw char.
// Service 1004.
static
int serviceDrawChar (void)
{
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    struct gws_window_d *window;
    int window_id = -1;
    unsigned long x=0;
    unsigned long y=0;
    unsigned long color=0;
    
    int __char=0;

    // #todo
    char *text_buffer; 
    
    unsigned char _string[4];


    // #debug
    gwssrv_debug_print ("serviceDrawChar: \n");


// Get message parameters.

    window_id = message_address[4];
    x         = message_address[5];
    y         = message_address[6]; 
    color     = message_address[7];
    unsigned long C = (unsigned long) message_address[8];
    //text_buffer =    //#todo
   

// Let's create a fake string.

   _string[0] = (unsigned char) C;
   _string[1] = (unsigned char) 0;

//
// Window ID
//

    // Limits
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        gwssrv_debug_print ("gwssrv: serviceDrawChar window_id\n");
        return -1;
    }

    //gwssrv_debug_print ("serviceDrawChar: get window pointer\n");

// Get the window structure given the id.
    window = (struct gws_window_d *) windowList[window_id];

    // #bugbug
    // O ponteiro eh nao nulo, mas esta numa regiao invalida.
    // why??
    
    //gwssrv_debug_print ("serviceDrawChar: [debug] cheching pointer validation\n");
    //printf ("[debug] window id      = %d \n",window_id);
    //printf ("[debug] window pointer = %x *hang\n",window);
    //while(1){}


// validations.

    if ( (void *) window == NULL ){
        gwssrv_debug_print ("gwssrv: serviceDrawChar window\n");
        return -1;
    }

    if ( window->used != TRUE || window->magic != 1234 ){
        gwssrv_debug_print ("gwssrv: serviceDrawChar validation\n");
        return -1;
    }

//
// Draw
//

// Let's draw the char 
// using the routine for drawing a string.
// See: dtext.c

    gwssrv_debug_print ("serviceDrawChar: Draw!\n");
    
    // Ok it is working
    dtextDrawText ( 
        (struct gws_window_d *) window,
        x, y, color, (unsigned char *) &_string[0] );

    //#test
    //It is working
    // Usando a janela screen por enquanto.
    //dtextDrawText ( (struct gws_window_d *) gui->screen,
        //x, y, color, (unsigned char *) &_string[0] );

    //It is working
    //charBackbufferDrawcharTransparent ( x, y, color, C );
    
//
// Refresh
//

// Refresh only the char.
// #todo:
// Maybe we can simply invalidar a small rectangle.
// Maybe we can have a flag telling us if we need 
// or not to refresh the char.

    //gws_show_backbuffer ();       // for debug   
    //gws_show_window_rect(window);   // something faster for now.
    //something faster.

    // x,y,w,h
    gws_refresh_rectangle ( 
        (window->left +x), 
        (window->top  +y), 
        8, 
        8 );

    gwssrv_debug_print ("gwssrv: serviceDrawChar done\n");

    return 0;
}



static
int serviceChangeWindowPosition(void)
{
	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d *window;
    int window_id = -1;
    
    unsigned long x = 0;
    unsigned long y = 0;


    // #debug
    gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition\n");


    // Get
    
    window_id = message_address[0];  //wid
    // msg
    x         = message_address[2];  
    y         = message_address[3];  


    //
    // Window ID
    //
   
    // Limits
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition window_id\n");
        return -1;
    }

    //#todo
    // Get the window structure given the id.
    window = (struct gws_window_d *) windowList[window_id];
   
    if ( (void *) window == NULL ){
        gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition window\n");
        return -1;
    }

    if ( window->used != TRUE || window->magic != 1234 ){
        gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition validation\n");
        return -1;
    }

    gwssrv_change_window_position ( 
        (struct gws_window_d *) window, 
        (unsigned long) x, 
        (unsigned long) y );

    return 0;
}


static
int serviceResizeWindow(void)
{

	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d *window;
    int window_id = -1;
    
    unsigned long w = 0;
    unsigned long h = 0;


    // #debug
    gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition\n");

    // #todo
    // Check all the header.


    // Get
    
    window_id = message_address[0];  //wid
    // msg
    w         = message_address[2];  
    h         = message_address[3];  


    //
    // Window ID
    //
   
    // Limits
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition window_id\n");
        return -1;
    }

    //#todo
    // Get the window structure given the id.
    window = (struct gws_window_d *) windowList[window_id];
   
    if ( (void *) window == NULL ){
        gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition window\n");
        return -1;
    }
    
    if ( window->used != 1 || window->magic != 1234 ){
        gwssrv_debug_print ("gwssrv: serviceChangeWindowPosition validation\n");
        return -1;
    }

//do!

    gws_resize_window ( 
        (struct gws_window_d *) window, 
        (unsigned long) w, 
        (unsigned long) h );

    return 0;
}



// #bugbug
// Usaremos a função create window para desenhar botões.
// #deletar !!!
static
int serviceDrawButton(void)
{
    // Deprecated !!
    gwssrv_debug_print("serviceDrawButton: deprecated\n");
    printf            ("serviceDrawButton: deprecated\n");
    exit(1);
    return -1;
}


// Redraw window.
// It will invalidate the window, and it will need to be flushed
// into the frame buffer.
static
int serviceRedrawWindow (void)
{
    //O buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    struct gws_window_d *window;

    // parameters
    int window_id = -1;
    int msg_code  = 0;
    unsigned long flags = 0;


// #debug
    gwssrv_debug_print ("serviceRedrawWindow:\n");


// Get wid and flag.
    window_id  = message_address[0];  // window id 
    msg_code   = message_address[1];  // message code
    flags      = message_address[2];  // flags
    //??       = message_address[3];  // nothing 

    // #todo
    //  Not tested yet.
    //if ( msg_code <= 0 ){
    //    gwssrv_debug_print ("serviceRedrawWindow:\n");
    //    goto fail;
    //}


// Window ID

    window_id = (int) (window_id & 0xFFFF);
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        gwssrv_debug_print ("serviceRefreshWindow: [FAIL] window_id\n");
        goto fail;
    }

// Get the window structure given the id.

    window = (struct gws_window_d *) windowList[window_id];

    if ( (void *) window == NULL ){
        gwssrv_debug_print ("serviceRefreshWindow: [FAIL] window\n");
        goto fail;
    }

    if ( window->used != TRUE || window->magic != 1234 )
    {
        gwssrv_debug_print ("serviceRefreshWindow: [FAIL] window validation\n");
        goto fail;
    }

// Validate
    window->dirty = FALSE;

// Redraw

    redraw_window (
        (struct gws_window_d *) window, 
        (unsigned long) flags );

// Invalidate
    window->dirty = TRUE;

//done:
    return 0;

fail:
    return (int) (-1);
}


// 2021
// Flush a given area into the framebuffer.
static
int serviceRefreshRectangle (void)
{
	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    unsigned long left=0;
    unsigned long top=0;
    unsigned long width=0;
    unsigned long height=0;

// #todo
// Check all the header.

    unsigned long msg_code = message_address[1];
    if( msg_code != GWS_RefreshRectangle )
        return -1;

// #todo
// Check if the message code is right.

    left   = message_address[4];
    top    = message_address[5];
    width  = message_address[6];
    height = message_address[7];

    left   = (left   & 0xFFFF);
    top    = (top    & 0xFFFF);
    width  = (width  & 0xFFFF);
    height = (height & 0xFFFF);

// #todo
// Maybe we can test some limits here.

// Flush it into the framebuffer.
// See: rect.c
    gws_refresh_rectangle ( left, top, width, height );
    return 0;
}

// 1006
// Flush a given window into the backbuffer.
// #todo: Here we can simple mark this window as 'dirty'
// and let the compositor do its job.
static
int serviceRefreshWindow (void){

    unsigned long *message_address = (unsigned long *) &__buffer[0];

    struct gws_window_d *window;
    int window_id = -1;
    
    //unsigned long x;
    //unsigned long y;
    //unsigned long color;
    //int __char;
    //char *text_buffer;    // #todo


    // #debug
    gwssrv_debug_print ("serviceRefreshWindow:\n");


    // #todo
    // Check all the header.

    //
    // == Window ID ============================
    //

    // Get it
    window_id = (int) message_address[0];   
   
    // #extra
    // Special case.
    // Will be used in the ghost frame routines.
    
    if ( window_id == (-4) )
    {
        gwssrv_debug_print("serviceRefreshWindow:\n");  //debug
        gwssrv_debug_print("== R (extra) ==\n");  //debug
        refresh_device_screen();
        return 0;
    }

 
    // Limits
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        //printf("%d\n",window_id);
        gwssrv_debug_print ("serviceRefreshWindow: [FAIL] window_id\n");
        return -1;
    }

    //#todo
    // Get the window structure given the id.
    window = (struct gws_window_d *) windowList[window_id];
   
    if ( (void *) window == NULL ){
        gwssrv_debug_print ("serviceRefreshWindow: [FAIL] window\n");
        return -1;
    }
    
    if ( window->used != 1 || window->magic != 1234 ){
        gwssrv_debug_print ("serviceRefreshWindow: [FAIL] window validation\n");
        return -1;
    }



// #todo
// simply invalidate the window and let the compositor do its job.

    //invalidate_window(window);

//
// Flush
//

    gws_show_window_rect(window);
    
    return 0;
}


// Draw text.
// Service 1005
static
int serviceDrawText (void)
{

    // Global buffer.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d  *window;
    
    int window_id = -1;      // index 4
    unsigned long x;         // index 5
    unsigned long y;         // index 6
    unsigned long color;     // index 7


// Device context
    unsigned long deviceLeft   = 0;
    unsigned long deviceTop    = 0;
    unsigned long deviceWidth  = (__device_width  & 0xFFFF );
    unsigned long deviceHeight = (__device_height & 0xFFFF );


    // #debug
    gwssrv_debug_print ("gwssrv: serviceDrawText\n");


// Get values.

    window_id = (int)           message_address[4];
    x         = (unsigned long) message_address[5];
    y         = (unsigned long) message_address[6]; 
    color     = (unsigned long) message_address[7];


    window_id = (window_id & 0xFFFF);
    x         = (x         & 0xFFFF);
    y         = (y         & 0xFFFF);


    /*
    //size 256 bytes
    unsigned char *text_buffer = (unsigned char *) &message_address[MSG_OFFSET_LONGSTRING];  
   
    int s = sizeof(text_buffer);
   
    if(s<0 || s>= 256)
    {
        gwssrv_debug_print ("gwssrv: serviceDrawText [DEBUG]   SIZE \n");
        exit(1);
    }
    */


// Limits
// O texto começa fora dos limites da tela do dispositivo.

    //if( x >= deviceWidth )
        //return -1;

    //if( y >= deviceHeight )
        //return -1;


//
// == Draw ==========================================
//


    //#todo
    // Get the window structure given the id.
    //window = (struct gws_window_d *) windowList[window_id];
    
    //#test
    // Usando a janela screen por enquanto.

// ==================================
// Get string from message
// OK. string funcionou.

    unsigned char buf[256+1];
    int i=0;
    int string_off=8;
    for(i=0; i<256; i++)
    {
         buf[i] = message_address[string_off];
         string_off++;
    }
    buf[i] = 0;
// ==================================

//
// == Draw ===============================================
//
    
    //#todo
    //switch (alignment) {  ... }
    
    
    //dtextDrawText ( (struct gws_window_d *) gui->screen,
        //x, y, color, buf ); 


// ok
// Se a janela alvo tem um índice fora dos limites

    if ( window_id < 0 ){ return -1; }
    if ( window_id > WINDOW_COUNT_MAX )
        return -1;

// ok
// Se a janela alvo tem um índice dentro dos limites.

    if ( window_id > 0 && 
         window_id < WINDOW_COUNT_MAX )
    {
        window = (struct gws_window_d *) windowList[window_id];

        // Bad index. Invalid pointer.
        if ( (void*) window == NULL ){ return -1; }

        // Bad index. Invalid pointer.
        if (window->magic != 1234)   { return -1; }

        // Good window. Let's paint on it.
        dtextDrawText ( 
            (struct gws_window_d *) window,
            x, y, color, buf );

        // Flush the window into the framebuffer.
        // #todo: invalidate, not show.
        gws_show_window_rect(window);

        // ok
        return 0;
    }

crazy_fail:
    debug_print("serviceDrawText: [ERROR] crazy_fail\n");
    return -1;
}



// O buffer é uma global nesse documento.
static
int servicelineBackbufferDrawHorizontalLine (void)
{
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    // x1,y,x2,color
    unsigned long x1,y,x2,color;
      
    x1    = message_address[4];
    y     = message_address[5];
    x2    = message_address[6];
    color = message_address[7];

    grBackbufferDrawHorizontalLine ( x1, y, x2, (unsigned int) color );
    
    //gws_show_backbuffer(); // for debug   
    return 0;
}







//======================================

char *gwssrv_get_version(void)
{
    // ??
    return VERSION;
}


// The window server's main struture.
// See: gws.h
void __init_ws_structure(void)
{

// The window server's main struture.
// See: gws.h

    window_server = (struct gws_d *) malloc ( sizeof( struct gws_d) );

    if ( (void*) window_server == NULL )
    {
        gwssrv_debug_print("__init_ws_structure: [FAIL] window_server \n");
        printf            ("__init_ws_structure: [FAIL] window_server \n");
        exit(1);
    }

    memset( window_server, 0, sizeof(struct gws_d) );

// Version
    window_server->version_major = VERSION_MAJOR;
    window_server->version_minor = VERSION_MINOR;

    // strings
    // #todo: we need to finalize these strings?

// name
    sprintf( window_server->name, "Gramado Window Server" );
    strcat(window_server->name,"\0");

// edition name
    sprintf( window_server->edition_name, "Presence" );
    strcat(window_server->edition_name,"\0");

// version string
    sprintf( window_server->version_string, "0.1" );
    strcat(window_server->version_string,"\0");

// We need to register the server in the host system.
    window_server->registration_status = FALSE;

// graphics initialization status.
    window_server->graphics_initialization_status = FALSE;


// Se devemos ou não lançarmos o primeiro client.
// #todo: Pegaremos essa informação dos parâmetros.
    window_server->launch_first_client = TRUE;

// When to quit the window server.
    window_server->quit = FALSE;
    
 // #todo
    window_server->status = 0;
}



/*
 * on_execute: 
 *     + Initializes the gws infrastructure.
 *     + Create the background.
 *     + Create the taskbar.
 *     + Register window server as the current window server 
 *       for this desktop.
 *     + Create the server socket.
 *     + bind it.
 *     + Spawn a client process. (gwst.bin)
 *     + Enter in the main loop, waiting for some types of event.
 *       The possible events are: Reading messages from the kernel,
 *       or Reading our socket.
 *       In this moment we can send a response. It depends on the
 *       message found in the sockeck we readed.
 */

static int on_execute(void)
{
    int flagUseClient = FALSE;
    //int flagUseClient = TRUE;

    // #debug flags
    int UseCompositor = TRUE;

    IsTimeToQuit = FALSE;
    IsAcceptingConnections = TRUE;

// =============

// #test
// Registrando handlers de input.
// usados como aceleradores de teclado e mouse.
// Dessa forma o console poder'a digitar diretamente 
// na janela com foco de entrada.
// Os parametros serao passados via memoria compartilhada.
// poderao ser longos ou pequenos.
// >>>>>>> ou ainda esses handler pode receber apenas algumas mensagens,
// principalmente as mensagens relativas ao window manager.
// It also enable the kernel for calling our compositor.
// See the callback in wm.c

// adiamos essa rotina
// assim o kernel somente chamara o ws quando as coisas
// estiverem inicializadas por aqui.

/*
    gramado_system_call( 
        101234, 
        (unsigned long) &wmHandler, 
        (unsigned long) &wmHandler, 
        (unsigned long) &wmHandler );
*/



// =============
    //gws_enable_transparence();
    gws_disable_transparence();

//==================
    struct sockaddr server_address;
    socklen_t addrlen;

    server_address.sa_family = AF_GRAMADO;
    server_address.sa_data[0] = 'w';
    server_address.sa_data[1] = 's';

    addrlen = sizeof(server_address);
//==================


    // files.
    int server_fd = -1; 
    int newconn = -1;
    int curconn = -1;
    
    int bind_status = -1;
    
    int i=0;
    int _status = -1;

// Window server structure
    __init_ws_structure();

// Window manager
    wmInitializeGlobals();
    __init_wm_structure();


// ===============

// Used in this file?
// Flag usada no loop.

    running = TRUE;

    /*
    FILE *input_fp;
    fflush(stdin);
    close(fileno(stdin));
    input_fp = fopen("kstdin.txt","r+");
    if( (void*) input_fp == NULL ){
        printf ("gwssrv: input_fp fail\n");
        exit(1);
    }
    */


    /*
    //#test
    char display[100];
    hostName    = "gramado";
    displayNum  = ":0";
    screenNum   = ".0";
    strcpy(display, hostName);
    strcat(display, displayNum);
    strcat(display, screenNum);
    printf("DISPLAY={%s}\n",display);
    while(1){}
    */

    char buf[32];
    int CanRead=-1;

// invalidate the frame.
// invalidate all the background.
// See: gws.c

    invalidate();
    invalidate_background();

// #todo:
// Initialize all the OS dependent stuff.
// ex: OsInit();

// #debug
    //gwssrv_debug_print ("-----------------------\n");
    gwssrv_debug_print ("GWSSRV.BIN: Initializing\n");
    // printf             ("gwssrv: Initializing...\n");

// Init clients support.
// Inicializa a lista de clientes.

    initClientSupport();

// #bugbug
// Essa estrutura nao esta sendo inicializada corretamente.
    
    if ( serverClient->used != TRUE || serverClient->magic != 1234 )
    {
         //asm ("int $3");
    } 


// Register.

// #bugbug
// I don't know if we can register more than one time.
        // We can fix it!

// Register.
// Register window server as the current window server 
// for this desktop.
// #bugbug: 
// Se tentarmos reiniciar o servidor, talvez
// nao consigamos registrar novamente, pois ja tem um registrado.
// Precisamos a opcao de desregistrar, para tentarmos 
// mais de um window server.
// See: connect.c

    _status = (int) register_ws();

    if (_status<0){
        gwssrv_debug_print ("gwssrv: Couldn't register the server \n");
        printf             ("gwssrv: Couldn't register the server \n");
        return -1;
        //exit(1);
    }
    gwssrv_debug_print ("gwssrv: Registration ok \n");
    window_server->registration_status = TRUE;


// #todo
// Daqui pra frente é conexão com cliente.
// Lembrando que o servidor vai se conectar à mais de um cliente.
// ...

// #todo
// Aqui nos podemos criar vários sockets que serão usados
// pelo servidor.
//ex: CreateWellKnownSockets ();


//
// Socket
//

// + Creating the socket for the server.
// + Saving the socket fd.

    // #debug
    //printf ("gwssrv: [1] socket()\n");

    server_fd = (int) socket (AF_GRAMADO, SOCK_STREAM, 0);
    if (server_fd<0){
        gwssrv_debug_print ("gwssrv: [FATAL] Couldn't create the server socket\n");
        printf             ("gwssrv: [FATAL] Couldn't create the server socket\n");
        return -1;
        //exit(1);
    }

// Global variable.
    ____saved_server_fd   = (int) server_fd;

// Window server structure.
    window_server->socket = (int) server_fd;

// The server itself has its own client structure.
    serverClient->fd      = (int) server_fd;

    // #debug
    //printf ("fd: %d\n", serverClient->fd);
    //while(1){}


//
// Bind
//

    // #debug
    //printf ("gwssrv: [2] bind()\n");

    bind_status = bind (
                      server_fd, 
                      (struct sockaddr *) &server_address, 
                      addrlen );

    if (bind_status<0){
        gwssrv_debug_print ("gwssrv: [FATAL] Couldn't bind to the socket\n");
        printf             ("gwssrv: [FATAL] Couldn't bind to the socket\n");
        return -1;
        //exit(1);
    }

    // #debug
    //printf ("fd: %d\n", serverClient->fd);
    //while(1){}

//
// Listen
//

// #todo
// It will setup how many connection the kernel
// is able to have in the list.
// 5 clients in the list.

    // #debug
    //printf ("gwssrv: [3] listen()\n");

// #bugbug
// Isso afeta a velocidade do sistema,
// pois com uma lista muito grande de clientes
// o servidor vai perder muito tempo no accept();
// Pois nosso accept() ainda eh pouco eficiente.

    //listen (server_fd,32);
    listen (server_fd,4);

    // #debug
    //printf ("fd: %d\n", serverClient->fd);
    //while(1){}

// Init Graphics
// Draw something.
// Init ws infrastructure.
// Initialize the '3D' graphics support.
// Let's create the standard green background.

    int graphics_status = -1;

    graphics_status = (int) initGraphics();
    if(graphics_status<0){
        printf("gwssrv: initGraphics failed\n");
        return -1;
        //while(1){}
        //exit(1);
    }


//
// The window manager
//

// ===============

    if( (void*) WindowManager.root == NULL )
    {
        gwssrv_debug_print("gwssrv: WindowManager.root fail\n");
                    printf("gwssrv: WindowManager.root fail\n");
        return -1;
        //exit(0);
    }

    if( (void*) WindowManager.taskbar == NULL )
    {
        gwssrv_debug_print("WindowManager.taskbar fail\n");
        printf("WindowManager.taskbar fail\n");
        return -1;
        //exit(0);
    }

// The working area.
    
    WindowManager.wa_left = 0;
    WindowManager.wa_top = 0;
    WindowManager.wa_width = WindowManager.root->width;
    WindowManager.wa_height =
        (WindowManager.root->height - WindowManager.taskbar->height);

    WindowManager.initialized =TRUE;

    //#debug
    //Not working
    /*
    printf ("wa: %d %d %d %d",
        WindowManager.wa_left,
        WindowManager.wa_top,
        WindowManager.wa_width,
        WindowManager.wa_height );
    */
// ===============

    //gws_show_backbuffer();
    //while(1){}

    // #debug
    //printf ("fd: %d\n", serverClient->fd);
    //while(1){}


//
// Child
//

    // Calling child.
    //printf ("gwssrv: Calling child \n"); 

    /*
    if ( window_server->launch_first_client == TRUE )
    {
        // #todo: Get the status.
        //rtl_clone_and_execute("gws.bin");
        //gwssrv_clone_and_execute ("gwm.bin");
        //gwssrv_clone_and_execute ("logon.bin");
    }
    */

    // #debug
    //printf ("fd: %d\n", serverClient->fd);
    //while(1){}


//
// Client
//

    if ( flagUseClient == TRUE )
    {
        //debug_print ("gwssrc: Calling client $\n");
        //rtl_clone_and_execute("terminal.bin");
    }


//
// =======================================
//

//
// Loop
//

// #todo
// Isso é um teste.
// #atenção
// Provavelmente precisamos de um loop
// contendo accept, read e write.
// Não presizamos criar o socket novamente,
// mas temos que refazer a conecção toda vez
// que enviarmos uma resposta.
// Então logo após enviarmos a resposta precisamos
// fechar o arquivo? Acabaria com o socket?
// #atenção:
// A função accept vai retornar o descritor do
// socket que usaremos ... por isso poderemos fecha-lo
// para assim obtermos um novo da próxima vez.


//#todo:
// No loop precisamos de accept() read() e write();

    // Not used for now.
    connection_status = 1;

    //curconn = serverClient->fd;
    newconn = -1;
 

// #important
// Here we are exporting some callback to the base kernel.
// This way the kernel is able to call this routine directly.
// It is possible because the window server and the base kernel
// are sharing the process structure and the same memory space.
// This is an unusual practice. :)

    gwssrv_debug_print ("gwssrv: Exporting callback\n");

    gramado_system_call( 
        101234, 
        (unsigned long) &wmHandler, 
        (unsigned long) &wmHandler, 
        (unsigned long) &wmHandler );


// ========================================================


/*
//
// Thread
//

// Vamos criar a thread do compositor.
// No momento ela ficara apenas fazendo
// flush dos retângulos ...
// mas no futuro ela poderá copiar as janelas
// de seus buffers individuais para o backbuffer e ao fim
// fazer flush do backbuffer inteiro.

// #bugbug
// O problema aqui é essa rotina ainda não cria
// threads em ring0 e o window server está em ring0.

    char tStack[4096];
    void *t;

// Create the thread.
// IN: 
// address, stack, name.
    t = (void *) rtl_create_thread(
                      &Compositor_Thread,
                      &tStack[4096], 
                      "Compositor" );

    if ( (void*) t == NULL )
    {
        printf ("gwssrv.bin: Couldn't create the compositor thread\n");
        exit(0);
    }
// Start the thread.
// Coloca ela em standby
    rtl_start_thread(t);
*/


// ========================================================

//
// Loop
//

// + Accept connection from a client.
// + Call the dispatcher to porcess the message.
// See:
// https://man7.org/linux/man-pages/man2/accept.2.html

    gwssrv_debug_print ("gwssrv: Entering main loop.\n");

    while (running == TRUE)
    {
        if (IsTimeToQuit == TRUE) { break; };

       // Accept
        newconn = accept ( 
                      ____saved_server_fd,
                      (struct sockaddr *) &server_address, 
                      (socklen_t *) addrlen );

        // Fail
        if (newconn <= 0){
            gwssrv_debug_print("gwssrv: accept returned FAIL\n");
        }

        // Dispatch
        if (IsAcceptingConnections == TRUE)
        {
            //gwssrv_debug_print("gwssrv: accept returned OK\n");
            if( newconn == ____saved_server_fd ){
                printf("GWSSRV.BIN: newconn == ____saved_server_fd\n");
                while(1){}
            }

            //#debug
            //if( newconn != 31 )
            //{
            //    printf("GWSSRV.BIN: newconn != 31\n");
            //    while(1){}
            //}

             // sys_accept() pega na fila e coloca em fd=31.
             if(newconn == 31){
                 dispacher(newconn);
             }
            
            //close(newconn);
        }

        // Not accpeting
        if (IsAcceptingConnections == FALSE){
            //close(newconn);
        }
    };
// =======================================

    if (IsTimeToQuit != TRUE){
        debug_print ("gwssrv: [ERROR] Invalid IsTimeToQuit\n");
    }

// #todo
// Now we will close the window server.  
// Free all the structure, one by one in cascade.
// See: 'gws' structure in gws.h
// We will call the kernel to unregister the window server.
// We will close all the sockets.
// ...

// Close the server's fd.
    if (server_fd>0){
        close(server_fd);
    }

// Teturn to main()
    return 0; 
}


// yield thread.
void gwssrv_yield(void)
{
    sc82(265,0,0,0);
}


void gwssrv_quit(void)
{
    IsTimeToQuit = TRUE;
}


// main: entry point
int main (int argc, char **argv)
{
    int Status=-1;

    // ##
    // Sincronizaçao provisoria.
    // Vamos precisar disso antes de tudo;
    // vamos pegar a que foi criada pelo primeiro cliente.
    // ele cria no começo da rotina.
    // Dai usaremos essa id por enquanto, pois o sistema so tem ela ainda.
    
    while(1)
    {
        __saved_sync_id = sc82 (10005,0,0,0);
        if( __saved_sync_id > 0 && __saved_sync_id < 1024 )
            break;
    };

    Status = on_execute();

    //0 = Time to quit.
    if(Status == 0)
    {
        gwssrv_debug_print ("GWSSRV.BIN: exit(0)\n");
        printf             ("GWSSRV.BIN: exit(0)\n");
        // #bugbug
        // The thread state didn't change.
        // We are still in RUNNING state.
        // It probably hang in the exit function.
        exit(0);
    }

// fail

// hang
// Page fault when exiting ... 
// #fixme

    gwssrv_debug_print ("GWSSRV.BIN: Hang on exit\n");
    printf             ("GWSSRV.BIN: Hang on exit\n");

    while(1)
    {
    };

// Not reached.
    return 0;
}


//
// End
//

