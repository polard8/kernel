/*
 * File: main.c
 * 
 *    Main file for the Gramado Window Server.
 * 
 *    History:
 *        2020 - Created by Fred Nora. 
 */

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


#include <sys/cdefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

//#include <api.h>

#include <gws.h>


//h:d.s
char *hostName;
char *displayNum;
char *screenNum;



int running = 0;
int ____saved_server_fd = -1;



// #test
#define MSG_OFFSET_SHORTSTRING  64
#define SHORTSTRING_SIZE        64
#define MSG_OFFSET_LONGSTRING  128
#define LONGSTRING_SIZE        256
// ...






int dirty_status = 0;
int connection_status = 0;


// Window.
struct gws_window_d *__bg_window;
struct gws_window_d *__taskbar_window; 
struct gws_window_d *__taskbar_button; 
struct gws_window_d *__mywindow;    // Generic, for tests.
// ...






//
// Prototypes.
//

int 
gwsProcedure ( 
    struct gws_window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


void InitGraphics(void);
void create_background (void);


void
gwssrv_init_client_support(void);
void init_client_struct ( struct gws_client_d *c );



void xxx_test_load_icon(void);




// ...



//
//===================================================================
//


void gwssrv_debug_print (char *string){

    gramado_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}


int gwssrv_clone_and_execute ( char *name )
{
    return (int) gramado_system_call ( 900, (unsigned long) name, 0, 0 );
}



unsigned long gwssrv_get_system_metrics (int index){

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



//P (Proberen) testar.
void gwssrv_enter_critical_section (void){

    int S=0;

    //#define	SYSTEMCALL_GET_KERNELSEMAPHORE    226
    //#define	SYSTEMCALL_CLOSE_KERNELSEMAPHORE  227

    // Pega o valor do spinlock principal.
    while (1){
        S = (int) gramado_system_call ( 226, //SYSTEMCALL_GET_KERNELSEMAPHORE, 
                      0, 0, 0 );
                      
		// Se deixou de ser 0 então posso entrar.
		// Se ainda for 0, continuo no while.
        if ( S == 1 ){ goto done; }
        
        //#wait
        gramado_system_call (265,0,0,0); //yield thread.
    };

    //Nothing

done:
    //Muda para zero para que ninguém entre.
    gramado_system_call ( 227, //SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 
        0, 0, 0 );
    return;
}


//V (Verhogen)incrementar.
void gwssrv_exit_critical_section (void)
{
	//#define	SYSTEMCALL_OPEN_KERNELSEMAPHORE   228
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    gramado_system_call ( 228, //SYSTEMCALL_OPEN_KERNELSEMAPHORE, 
        0, 0, 0 );
}



void gwssrv_show_backbuffer (void)
{
    // #todo
    // trocar o nome dessa systemcall.
    // refresh screen será associado à refresh all windows.
    
    //#define	SYSTEMCALL_REFRESHSCREEN        11
    
    gramado_system_call ( 11, //SYSTEMCALL_REFRESHSCREEN, 
        0, 0, 0 );
}




//
//===================================================================
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

    



/*
 ****************************
 * handle_request:
 * 
 * 
 */

// internal.
// Messages sent via socket.
// obs: read and write use the buffer '__buffer'
// in the top of this file.

//#todo:
// No loop precisamos de accept() read() e write();

//void handle_request (int fd);
void handle_request (int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_reads = 0;     // For requests.
    int n_writes = 0;    // For responses.

    //#todo:
    // No loop precisamos de accept() read() e write();

    //#atenção:
    // A função accept vai retornar o descritor do 
    // socket que usaremos ... por isso poderemos fecha-lo
    // para assim obtermos um novo da próxima vez.

    if (fd<0){
        gwssrv_debug_print ("gwssrv: handle_request fd\n");
        return;
    }


//__loop:

    // #todo
    // Devemos escrever em nosso próprio
    // socket e o kernel copia??
    // o kernel copia para aquele arquivo ao qual esse estivere conectado.
    // olhando em accept[0]

    //
    // Recv.
    //
    
    // Lê a mensagem e coloca no buffer.
    
    n_reads = read ( fd, __buffer, sizeof(__buffer) );
    //n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );

    if (n_reads <= 0){
        gwssrv_yield();
        return;
    }


    // Nesse momento lemos alguma coisa.   
 
    //debug_print ("gws: request found on its own socket \n");  
            
    // Mensagem inválida  
    if (message_buffer[1] == 0 ){
        // gwssrv_wait_message() //todo: use this one. 
        gwssrv_yield();
        return;
    }


    // #test
    // Input solicitado por um cliente
    // Isso deve acontecer quando o cliente chama alguma função
    // do tipo: gws_get_next_event() da libgws.
    // Em outro caso, no loop principal, esse servidor 
    // deve pegar os inputs vindos do sistema e colocar 
    // na fila de entrada do cliente com o foco de entrada.
    // o cliente com o foco de entrada possui a janela com 
    // o foco de entrada.
    
    if (message_buffer[1] == 369)
    {
        debug_print ("gwssrv: [TEST] 369 INPUT request !!! \n");

        // Pegar o input!

        // Get message from kernel.
        // #bugbug: Nesse momento podemos ficar enrroscados aqui.
        // na entrada da seção crítica.
        //gde_enter_critical_section();
        gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        //gde_exit_critical_section();
        
        //message_buffer[1] = SERVER_PACKET_TYPE_EVENT;

        debug_print("gwssrv: Sending response\n");
        
        n_writes = send ( fd, __buffer, sizeof(__buffer), 0 );
        
        if (n_writes<=0){
             debug_print ("gwssrv: [FAIL] Couldn't send response!\n"); 
        }
        debug_print("gwssrv: response sent\n");
        return;
    }


    debug_print ("gwssrv: Got a request!\n");
    debug_print ("gwssrv: Calling window procedure \n");
    
    
    // #todo.
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
    
    
                
    //#debug: para a máquina real.
    //printf ("gws: got a message!\n");
    //printf ("gws: handle_request: calling window procedure \n");
 
                
    // Realiza o serviço.
    gwsProcedure ( 
       (struct gws_window_d *) message_buffer[0], 
       (int)                   message_buffer[1], 
       (unsigned long)         message_buffer[2], 
       (unsigned long)         message_buffer[3] );


    // #todo
    // Se o request foi um request de evento,
    // significa que o cliente deseja receber o próximo evento da 
    // lista de eventos.
    // podemos passar mensagens recebidas pelo gws para o cliente.

    // ??
    // espera ate conseguir enviar a resposta.
    // o kernel precisa copiar para aquele conectado em accept[]

    //
    // Sending reply.
    // 
     
    //gwssrv_debug_print ("Sending response ...\n");  

    //# it works.
    char *m = (char *) (&__buffer[0] + 16);
    sprintf( m, "gwssrv: This is a response from GWS!\n");
    
    // Primeiros longs do buffer.
    message_buffer[0] = next_response[0];         // Window ID.
    message_buffer[1] = SERVER_PACKET_TYPE_REPLY; // next_response[1] 
    message_buffer[2] = next_response[2];         // Return value (long1)
    message_buffer[3] = next_response[3];         // Return value (long2)

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
}


/*
 ********************************** 
 * handle_ipc_message: 
 * 
 * 
 */

// internal
// System ipc messages. (It's like a signal)
//void handle_ipc_message (void);
void handle_ipc_message (void){
    
    unsigned long message_buffer[5];   


    // Get message.
    gwssrv_enter_critical_section();
    gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
    gwssrv_exit_critical_section();

    // No message
    if ( message_buffer[1] == 0 ){
        gramado_system_call (265,0,0,0);
        return;
    }

    // Send message to the window procedure.
    gwsProcedure ( (struct gws_window_d *) message_buffer[0], 
        (int) message_buffer[1], 
        (unsigned long) message_buffer[2], 
        (unsigned long) message_buffer[3] );

     message_buffer[0] = 0;
     message_buffer[1] = 0;
     message_buffer[2] = 0;
     message_buffer[3] = 0;
}


/*
 **********************************
 * gwsProcedure:
 *     Main dialog.
 * 
 */
 
int 
gwsProcedure ( 
    struct gws_window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    int my_pid = -1;


    // #debug
    debug_print ("gwssrv: gwsProcedure\n");
  
    switch (msg)
    {
        // Se o cliente enviar essa mensagem, significa
        // que ele quer que drenemos o input que o
        // ws recebe via mensagens tradicionais e passemos
        // pra ele via socket.
        case 8080:
            gwssrv_debug_print("gwssrv: gwsProcedure 8080\n");
            service_drain_input();
            break;

        case MSG_SYSKEYUP:
            switch ( long1)
            {
                // #debug
                case VK_F1:
                    gwssrv_debug_print("gwssrv: gwsProcedure VK_F1 Connection ON\n");
                    connection_status = 1;
                    //gde_reboot ();
                    break;
                    
                // #debug
                // mostrar informações sobre o socket 
                // do gws.    
                case VK_F2:
                    gwssrv_debug_print("gwssrv: gwsProcedure VK_F2 Connection OFF\n");
                    connection_status = 0;
                    //my_pid = (int) getpid();
                    //gramado_system_call (7008,my_pid,0,0);
                    break;

                case VK_F3:
                    gwssrv_debug_print ("gwssrv: F3\n");
                    bmpDisplayBMP (0,0,0); //#todo: test.
                    break;

                // #test
                // Die.
                case VK_F4:
                    gwssrv_debug_print ("gwssrv: F4 [EXIT] Exiting the server ...\n");
                    running = 0;
                    break;
                    
                    
                case VK_F9:
                    gwssrv_debug_print ("gwssrv: F9\n");
                    //gws_draw_text(
                    break;

                // ...
                  
                // Enviar a mensagem para o processo associado
                // com a janela que tem o foco de entrada.
                default:
                    gwssrv_debug_print ("gwssrv: MSG_SYSKEYUP\n");
                    break;
            }    
            break;

        // #test
        // Tentando receber uma mensagem de digitação.
        case MSG_KEYDOWN:
            
            //#bugbug: Isso está falhando.
            //mas o f1 funciona.
            //printf ("%c", (char) long1); 
            //gws_show_backbuffer ();
            
            gwssrv_debug_print ("gwssrv: MSG_KEYDOWN\n");
            break;

        // Hello!
        // Draw text inside a window.
        // #bugbug: O window server não tem esse ponteiro de janela.
        // ele até aceitaria um handle.
        case 1000:
            gwssrv_debug_print ("gwssrv: Message number 1000\n");
            dtextDrawText ( (struct gws_window_d *) __mywindow,
                long1, long2, COLOR_GREEN,
                "gwssrv: Hello friend. This is the Gramado Window Server!");
            gws_show_backbuffer();
            break;


        // Create Window REQUEST!
        // Usará o buffer global
        // case MSG_CREATE_WINDOW:
        case 1001:
            gwssrv_debug_print ("gwssrv: [FIXME] Message number 1001\n");
            serviceCreateWindow (); 
            break; 

        // backbuffer putpixel
        case 1002:
            servicepixelBackBufferPutpixel(); 
            break;

        // backbuffer draw horizontal line
        case 1003:
            servicelineBackbufferDrawHorizontalLine();
            break;
    
        // Draw char
        case 1004:
            gwssrv_debug_print ("gwssrv: Message number 1004\n");
            serviceDrawChar();
            break;

        // Draw text
        // #todo: tem que testar isso!!!
        case 1005:
           gwssrv_debug_print ("gwssrv: Message number 1005\n");
           serviceDrawText();
           break;

        // Refresh window
        case 1006:
           gwssrv_debug_print ("gwssrv: Message number 1006\n");
           serviceRefreshWindow();
           break;
           

        // Redraw window
        case 1007:
           gwssrv_debug_print ("gwssrv: Message number 1007\n");
           serviceRedrawWindow();
           break;

        // Resize window
        case 1008:
           gwssrv_debug_print ("gwssrv: Message number 1008\n");
           serviceResizeWindow();
           break;


        case 1009:
           gwssrv_debug_print ("gwssrv: Message number 1009\n");
           serviceChangeWindowPosition();
           break;

    
        // ...
               
        // backbuffer putpixel. (again)
        // IN: Color, x, y
        case 2000:
            pixelBackBufferPutpixel ( (unsigned long) COLOR_PINK,   
                (unsigned long) long1, (unsigned long) long2 );
            break;
 
 
        //case 2001: break;
        //case 2002: break;
        //case 2003: break;

        // ...


        // Disconnect.
        // shutdown.
        // Um cliente quer se desconectar.
        case 2010:
            gwssrv_debug_print ("gwssrv: [2010] Disconnect\n");
            break;
            
        // Refresh screen 
        // refresh screen using kgws service. 
        case 2020:
            gws_show_backbuffer();
            break;
             

        // Refresh rectangle ... 
        case 2021:
            serviceRefreshRectangle();
            break;

        // ...

        
        default:
            gwssrv_debug_print ("gwssrv: Default message number\n");
            //printf ("msg=%d ",msg);
            break;
    }


    // #todo: 
    // Call the system's window procedure.    
    // Rever esse retorno.
    //return (int) gde_system_procedure (window,msg,long1,long2);
    return 0;
}



void create_background (void)
{
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();


    gwssrv_debug_print ("gwssrv: create_background\n");

    __bg_window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                         1, 1, "gwssrv-bg",  
                                         0, 0, w, h,   
                                         gui->screen, 0, 
                                         COLOR_BACKGROUND, COLOR_BACKGROUND );    

    if ( (void *) __bg_window == NULL ){
        gwssrv_debug_print ("gwssrv: __bg_window fail\n");  
        return;
    }
    
    //#test
    int id = -1;
    id = gwsRegisterWindow ( __bg_window );

    if (id<0){
        gwssrv_debug_print ("create_background: Couldn't register window\n");
        //return -1;
    }
}



void xxx_test_load_icon(void)
{
	/*
    FILE *fp;
    char *buffer;
    
    buffer = (char *) malloc(128*1024);
    
    fp = fopen ("terminal.bmp", "r+" );

    int nreads = read ( fileno(fp), buffer, (128*1024) );

    bmpDisplayBMP ((char *) buffer, (unsigned long) 80, (unsigned long) 80);    

     gws_show_backbuffer();
     while(1);
     */
}




void InitGraphics(void){

    int __init_status = -1;


    debug_print("gwssrv: InitGraphics\n");
    
    __init_status = gwsInit();

    if (__init_status != 0){
        debug_print("gwssrv: InitGraphics [PANIC] Couldn't initialize the graphics\n");
        printf("gwssrv: InitGraphics [PANIC] Couldn't initialize the graphics\n");
        while(1);
    }


    if( (void*) gui->screen != NULL){
        dtextDrawText ( (struct gws_window_d *) gui->screen,
            200, 80, COLOR_RED, "gwssrv: Initializing graphics" );
    }

    
    create_background();


    // #test
    // Precisamos encontrar uma rotina de carregamento apropriada.
    //xxx_test_load_bmp(); //OK
    // xxx_test_load_icon();
    
    // OK.
    // Testando ...
    // Tentar carregar todos, falha!.
    //gwssrv_load_and_decode_small_icon ("bmp1.bmp",  4,4);
    //gwssrv_load_and_decode_small_icon ("file.bmp", 50,4);
    //gwssrv_load_and_decode_small_icon ("folder.bmp",100,4);
    //gwssrv_load_and_decode_small_icon ("terminal.bmp",150,4);
    gwssrv_load_and_decode_small_icon ("app.bmp", 4, 100);
    //gwssrv_load_and_decode_small_icon ("cursor.bmp",250,4);
    //gwssrv_load_and_decode_small_icon ("mouse.bmp",300,4);
    //gwssrv_load_and_decode_small_icon ("folder.bmp",350,4);
    //gwssrv_load_and_decode_small_icon ("folder.bmp",400,4);


    
    //gws services
    //gws_refresh_rectangle(0,0,400,400);
    //gws_show_window_rect(gui->screen);
    
    gws_show_backbuffer();            
    
    debug_print("gwssrv: InitGraphics done\n");
    //printf     ("gwssrv: InitGraphics done *hang\n");
    //while(1){}
}



void
gwssrv_init_client_support(void)
{
    int i=0;
    
    
    for(i=0; i<CLIENT_COUNT_MAX; i++)
        gwsClientList[i] = 0;
    
    
    currentClient = (struct gws_client_d *) 0;
    
    serverClient = (struct gws_client_d *) malloc ( sizeof( struct gws_client_d ) );
    if ( (void *) serverClient == NULL )
    {
        gwssrv_debug_print ("gwssrv_init_client_support: [FATAL] Couldn't create serverClient\n");
        printf             ("gwssrv_init_client_support: [FATAL] Couldn't create serverClient\n");
        exit(1);
    
    }else{
        
        serverClient->id = 0;
        serverClient->used = 1;
        serverClient->magic = 1234;
        
        serverClient->fd = -1;
        
        serverClient->pid = getpid();
        serverClient->gid = getgid();
        
        // ...
        
        // #todo
        // Limpar a fila de mensagens para esse cliente.
        
        for (i=0; i<32; i++)
        {
            serverClient->window_list[i] = 0;
            serverClient->msg_list[i]    = 0;
            serverClient->long1_list[i]  = 0;
            serverClient->long2_list[i]  = 0;
        };
        serverClient->tail_pos = 0;
        serverClient->head_pos = 0;
        
        // ...
        
        //gwsClientList[0] = (unsigned long) serverClient;
        gwsClientList[SERVER_CLIENT_INDEX] = (unsigned long) serverClient;
    };
}


void init_client_struct ( struct gws_client_d *c )
{
    int i=0;
    
    if ( (void*) c == NULL )
        return;
    
    c->id = -1;  //fail
    c->used = 1;
    c->magic = 1234;
    
    c->fd = -1;
    c->pid = -1;
    c->gid = -1;
 
    for (i=0; i<32; i++)
    {
        c->window_list[i] = 0;
        c->msg_list[i]    = 0;
        c->long1_list[i]  = 0;
        c->long2_list[i]  = 0;
    };
    c->tail_pos = 0;
    c->head_pos = 0;
}



/*
 ******************************
 * main: 
 *     + Initializes the gws infrastructure.
 *     + Create the background.
 *     + Create the taskbar.
 *     + Register window server as the current window server 
 *       for this desktop.
 *     + Create the server socket.
 *     + bind it.
 *     + Spawn a client process. (gwst.bin)
 *     + Enter in the main loop, waiting for some types of event.
 *          The possible events are: Reading messages from the kernel,
 *          or Reading our socket.
 *       In this moment we can send a response. It depends on the
 *           message found in the sockeck we readed.
 */

int main (int argc, char **argv){

    struct sockaddr gramsock;  //addr;
    gramsock.sa_family = AF_GRAMADO;
    gramsock.sa_data[0] = 'w';
    gramsock.sa_data[1] = 's';   
    
    int server_fd = -1; 
    int bind_status = -1;


    // Flag usada no loop.
    running = 1;
    
    int i=0;
    int _status = -1;

    int newconn = -1;
    int curconn = -1;


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


    // Activate the compositor.
    dirty_status = 1;




    //++
    //==================
    // Main loop!
    // This loop will make the server restart and
    // call the childs again.
    while(1)
    {
        // #todo:
        // Initialize all the OS dependent stuff.
        // ex: OsInit();

        // #debug
        // Initializing or reinitializing
        gwssrv_debug_print ("---------------------\n");
        gwssrv_debug_print ("gwssrv: Initializing...\n");
        printf ("gwssrv: Initializing... \n");
        
        
        // Inicializa a lista de clientes.
        gwssrv_init_client_support();

        // Register.
 
        // #bugbug
        // I don't know if we can register more than one time.
        // We can fix it!

        // Register.
        // Register window server as the current window server 
        // for this desktop.
        // #bugbug: Se tentarmos reiniciar o servidor, talvez
        // nao consigamos registrar novamente, pois ja tem um registrado.
        // Precisamos a opcao de desregistrar, para tentarmos 
        // mais de um window server.
        // See: connect.c
        _status = (int) register_ws();

        if (_status<0){
            gwssrv_debug_print ("gwssrv: Couldn't register the server \n");
            printf             ("gwssrv: Couldn't register the server \n");
            exit(1);
        }
        gwssrv_debug_print ("gwssrv: Registration ok \n");


        // #todo
        // Daqui pra frente é conexão com cliente.
        // Lembrando que o servidor vai se conectar à mais de um cliente.
        // ...
        
        // #todo
        // Aqui nos podemos criar vários sockets que serão usados
        // pelo servidor.
        //ex: CreateWellKnownSockets ();
    
        // #atenção
        // socket() bind() e listen() ficam antes do loop.

        //
        // Socket
        //

        // #debug
        printf ("gwssrv: Creating socket\n");

        server_fd = (int) socket(AF_GRAMADO, SOCK_STREAM, 0);

        if (server_fd<0)
        {
            gwssrv_debug_print ("gwssrv: [FATAL] Couldn't create the server socket\n");
            printf             ("gwssrv: [FATAL] Couldn't create the server socket\n");
            exit(1);
        }

        serverClient->fd    = server_fd;
        ____saved_server_fd = server_fd;
        

        //
        // bind
        // 
    
        // #debug
        printf ("gwssrv: bind\n");
 
        bind_status = bind ( server_fd, (struct sockaddr *) &gramsock, sizeof(gramsock) );

        if (bind_status<0)
        {
            gwssrv_debug_print ("gwssrv: [FATAL] Couldn't bind to the socket\n");
            printf             ("gwssrv: [FATAL] Couldn't bind to the socket\n");
            exit(1);
        }


        // #todo
        // It will setup how many connection the kernel
        // is able to have in the list.
        // 5 clients in the list.
        // listen(server_fd,5);

        // Draw !!!
        // Init gws infrastructure.
        // Let's create the traditional green background.

        InitGraphics();

        // Calling child.
        //printf ("gwssrv: Calling child \n");  

        //gwssrv_clone_and_execute ("gws.bin");  // command gws.bin
        gwssrv_clone_and_execute ("gwm.bin");    // window manager
        //gwssrv_clone_and_execute ("terminal.bin");  
        //gwssrv_clone_and_execute ("fileman.bin");  
        //gwssrv_clone_and_execute ("browser.bin"); 
        //gwssrv_clone_and_execute ("launch1.bin"); 
        //gwssrv_clone_and_execute ("s2.bin");    //#bugbug        
        //gwssrv_clone_and_execute ("s3.bin");    //#bugbug        
        // ...        


        //#test 
        /*
        //++
        struct gws_window_d *Window;
        Window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
            1, 1, "no-name",  10, 10, 100, 100,   
            gui->screen, 0, COLOR_PINK, COLOR_PINK ); 
        gws_show_window_rect(Window);
        //--
        */

        // #tests
        // Isso funciona.
        //pixelBackBufferPutpixel ( COLOR_RED,   100, 250 );
        //pixelBackBufferPutpixel ( COLOR_GREEN, 105, 250 );
        //pixelBackBufferPutpixel ( COLOR_BLUE,  110, 250 );
        //charBackbufferDrawcharTransparent ( 250,       250, COLOR_RED,   (unsigned long) 'R');
        //charBackbufferDrawcharTransparent ( 250 +8,    250, COLOR_GREEN, (unsigned long) 'G');
        //charBackbufferDrawcharTransparent ( 250 +8 +8, 250, COLOR_BLUE,  (unsigned long) 'B');
        //charBackbufferDrawchar ( 300, 300, (unsigned long) 'X', COLOR_YELLOW, COLOR_RED );
        //lineBackbufferDrawHorizontalLine ( 400, 88, 500, COLOR_PINK );
        //rectBackbufferDrawRectangle ( 200, 400, 100, 60, COLOR_YELLOW );


        // Wait
        // printf ("gwssrv: [FIXME] yield \n");
        for (i=0; i<11; i++)
            gwssrv_yield();
 
        //
        // =======================================
        //

        //
        // Loop
        //
     
        // #todo
        // Isso é um teste.
        // #atenção
        // socket() bind() e listen() ficam antes do loop.
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
    
    // loop:
        gwssrv_debug_print ("gwssrv: Entering main loop.\n");

        //#todo:
        // No loop precisamos de accept() read() e write();

        // + Compositor. (Redraw dirty rectangles)    
        // + Socket requests.
        // + Normal messages. (It's like signals.)
 
        //not used for now.
        connection_status = 1;

        //curconn = ____saved_server_fd;
        curconn = serverClient->fd;
        newconn = -1;

        // struct len. Used in accept().  
        socklen_t addr_len;
        addr_len = sizeof(gramsock);
    
        // #todo:
        // Precisamos criar uma fila de mensagens para o sistema
        // e uma fila de mensagens para cada aplicativo.
        // a fila de mensagem dos aplicativos poderá ficar
        // na estrutura de cliente, ja que cada cliente representa
        // um apps.
        // a fila do sistema é global.See: input.c
        // ntuser faz isso também. tem dois inputs,
        // um do sistema e outro dos apps.
    
        while (running == 1)
        {
            // Se tem ou não retângulos sujos.
            // #bugbug: Talvez isso seja trabalho do window manager.
            // mas ele teria que chamar o window server pra efetuar o refresh
            //dos retângulos.
            //if ( dirty_status == 1 )
                //compositor();
         
         
            //Accept actual connection from the client */
            newconn = accept ( curconn, 
                          (struct sockaddr *) &gramsock, 
                          (socklen_t *) addr_len );
                          
            if (newconn < 0) {
                gwssrv_debug_print ("gwssrv: ERROR on accept\n");
 
            // Request from the new connection
            }else{

                // current_connection = newconn;
                // What is the client for this connection?
                // Getting the struct pointer for the client with this fd.
                // currentClient = getClient(newconn);
                
                //mensagens de clientes.
                handle_request (newconn);
                //handle_request (curconn);
                // close??
                
                // We do not have a current client anymore.
                // We need to accept a new one.
                // The kernel will give us a new one from the list
                // of connections when we call accept().
                //currentClient = (struct gws_client_d *) 0;
                
                //mensagens de sistema.
                //afetarão a janela com o foco.
                //gwssrv_get_system_message();
            };
        };


        // #todo
        // Bom, nesse momento precisamos liberar os recursos
        // para que o loop reinicie o servidor.
        // 
        
        //close(____saved_server_fd);
        
        // ...
        
        //
        // =======================================
        //
  
    }; // Main loop
    //====================
    //--

    //
    // Exited
    //
    
    // Well, if we are here so we exited from the main loop.
    // The server will not call a client again.
    // All we can do is exit.

    // Messages from kernel.
    // It is a kind of signal.
    // ipc message loop
    // while(1){ handle_ipc_message(); }

    // Done.
    
    gwssrv_debug_print ("gwssrv: exited. \n");
    printf             ("gwssrv: exited. \n");
    
    // #todo
    // The kernel needs to react when the window server closes.
    // We can't live without it.
    
    // #debug
    // #bugbug:
    // Page fault  when exiting ... 
    
    // HANG
    while(1){ }

    //suspended.
    return 0; 
}




//yield thread.
void gwssrv_yield(void)
{
    gramado_system_call(265,0,0,0);
}








