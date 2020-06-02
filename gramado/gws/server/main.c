/*
 * File: main.c
 * 
 *    Main file for the Gramado Window Server.
 * 
 *    History:
 *        2020 - Created by Fred Nora. 
 */


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
#include <api.h>
#include <gws.h>



int running = 0;

int ____saved_server_fd = -1;

// O buffer para  as mensagens recebidas via socket.
char __buffer[512];   



int dirty_status = 0;
int connection_status = 0;


// Window.
struct gws_window_d *__bg_window;
struct gws_window_d *__taskbar_window; 
struct gws_window_d *__taskbar_button; 
struct gws_window_d *__mywindow;    // Generic, for tests.
// ...





// Esses valores serão enviados como 
// resposta ao serviço atual.
// Eles são configurados pelo dialogo na hora da 
// prestação do serviço.
// No início desse array fica o header.
unsigned long next_response[32];


// Prototypes.
void create_background (void);
void create_taskbar (void);
void gws_yield (void);

int 
gwsProcedure ( 
    struct gws_window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
 

int service_drain_input (void);
int serviceCreateWindow ( void );
int servicepixelBackBufferPutpixel (void);
int servicelineBackbufferDrawHorizontalLine (void);
int serviceDrawButton (void);
// ...


/*
// internal
void client_shutdown (int fd);
void client_shutdown (int fd)
{
	//remove client
	//deallocate resources.
}
*/


/*
void client_die(int fd);
void client_die(int fd)
{
    client_shutdown(fd);
}
*/


// internal.
// Messages sended via socket.
// obs: read and write use the buffer '__buffer'
// in the top of this file.

//void handle_request (int fd);
void handle_request (int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_reads = 0;     // For requests.
    int n_writes = 0;    // For responses.


    if (fd<0){
        gde_debug_print ("handle_request: fd\n");
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
    
    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );

    if (n_reads <= 0)
        return;



    // Nesse momento lemos alguma coisa.   
 
    //debug_print ("gws: request found on its own socket \n");  
            
    // Mensagem inválida  
    if (message_buffer[1] == 0 )
        return;


    // #test
    // Input solicitado.
    if (message_buffer[1] == 369)
    {
        debug_print ("gws: [TEST] INPUT request !!! \n");

        // Pegar o input!

        //gde_enter_critical_section ();
        //gramado_system_call ( 111,
        //    (unsigned long) &message_buffer[0],
        //    (unsigned long) &message_buffer[0],
        //    (unsigned long) &message_buffer[0] );
        //gde_exit_critical_section ();
        
        message_buffer[1] = SERVER_PACKET_TYPE_EVENT;
        send ( fd, __buffer, sizeof(__buffer), 0 );
        return;
    }


    debug_print ("gws: Got a request!\n");
    debug_print ("gws: Calling window procedure \n");
    
    
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
    gwsProcedure ( (struct gws_window_d *) message_buffer[0], 
       (int) message_buffer[1], 
       (unsigned long) message_buffer[2], 
       (unsigned long) message_buffer[3] );


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
     
    gde_debug_print ("Sending response ...\n");  

__again:

    // #debug:

    gde_debug_print ("Sending response ...\n");
        
    // #debug
    //sprintf (__buffer," ................. This is a response");
                
    // Primeiros longs do buffer.
    message_buffer[0] = next_response[0];         // Window ID.
    message_buffer[1] = SERVER_PACKET_TYPE_REPLY; // next_response[1] 
    message_buffer[2] = next_response[2];         // Return value (long1)
    message_buffer[3] = next_response[3];         // Return value (long2)

    //
    // Send
    //
 
    //n_writes = write ( fd, __buffer, sizeof(__buffer) );
    n_writes = send ( fd, __buffer, sizeof(__buffer), 0 );
    
    if (n_writes<=0)
        goto __again;


    // Cleaning
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;

    // Cleaning
    int c=0;
    for(c=0; c<32; c++)
        next_response[c] = 0;


    gde_debug_print ("Response sent\n");  
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

    gde_enter_critical_section ();
    gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
    gde_exit_critical_section ();

    // Se não tem mensagem.
    if ( message_buffer[1] == 0 )
         return;

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
    debug_print ("gwsProcedure:\n");
  
    switch (msg)
    {
        // Se o cliente enviar essa mensagem, significa
        // que ele quer que drenemos o input que o
        // ws recebe via mensagens tradicionais e passemos
        // pra ele via socket.
        case 8080:
            gde_debug_print("gwsProcedure: 8080\n");
            service_drain_input();
            break;

        case MSG_SYSKEYUP:
            switch ( long1)
            {
                // #debug
                case VK_F1:
                    gde_debug_print("gwsProcedure: VK_F1 Connection ON\n");
                    connection_status = 1;
                    //gde_reboot ();
                    break;
                    
                // #debug
                // mostrar informações sobre o socket 
                // do gws.    
                case VK_F2:
                    gde_debug_print("gwsProcedure: VK_F2 Connection OFF\n");
                    connection_status = 0;
                    //my_pid = (int) getpid();
                    //gramado_system_call (7008,my_pid,0,0);
                    break;

                case VK_F3:
                    gde_debug_print ("F3\n");
                    break;

                // #test
                // Die.
                case VK_F4:
                    gde_debug_print ("F4 [EXIT] Exiting the server ...\n");
                    running = 0;
                    break;

                // ...
                  
                // Enviar a mensagem para o processo associado
                // com a janela que tem o foco de entrada.
                default:
                    gde_debug_print ("gws: MSG_SYSKEYUP\n");
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
            
            gde_debug_print ("gws: MSG_KEYDOWN\n");
            break;

        case 1000:
        
            //draw text inside a window.
            dtextDrawText ( (struct gws_window_d *) __mywindow,
                60, 70, COLOR_GREEN,
                "Hello friend. This is the Window Server!" );
                
            //printf ("Hello friend! %d %d \r \n", long1, long2 );
            
             //#todo: send response.
            
             gws_show_backbuffer ();
             break;


        // Create Window.
        // Usará o buffer global
        // case MSG_CREATE_WINDOW:
        case 1001:
            serviceCreateWindow (); 
            break; 

        case 1002:
            servicepixelBackBufferPutpixel(); //pixel
            break;

        case 1003:
            servicelineBackbufferDrawHorizontalLine();
            break;
    
        // #todo ; 1004. draw button
        case 1004:
           serviceDrawButton();
           break;
    
        //
        // Testing some drawing routines.
        //
         
         
        // put pixel
        // IN: Color, x, y
        case 2000:
            pixelBackBufferPutpixel ( (unsigned long) COLOR_PINK,   
                (unsigned long) long1, (unsigned long) long2 );
            break;
 
        case 2001:
            break;
             
             
        case 2002:
            break;
             
             
        case 2003:
            break;


        // Refresh screen 
        // refresh screen using kgws service. 
        case 2020:
            gws_show_backbuffer ();
            break;
             

        // Refresh rectangle ... 
        case 2021:
            break;

        // ...
             
                
        default:
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

    gde_debug_print ("gws: create_background\n");


    __bg_window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                         1, 1, "gws-bg",  
                                         0, 0, w, h,   
                                         gui->screen, 0, 
                                         COLOR_BACKGROUND, COLOR_BACKGROUND );    


    if ( (void *) __bg_window == NULL ){
        gde_debug_print ("gws: __bg_window fail\n");  
    }
}


void create_taskbar (void)
{
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();

    //
    // Bar
    //

    gde_debug_print ("gws: create_taskbar:\n");

    __taskbar_window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                               1, 1, "gws-taskbar",  
                                               0, 0, w, 40,   
                                               gui->screen, 0, 
                                               xCOLOR_GRAY1, xCOLOR_GRAY1 );
    
    if ( (void *) __taskbar_window == NULL ){
        gde_debug_print ("gws: __taskbar_window fail\n");  
    }

    //
    // Button
    //
    
    // #test
    // Create button.

    gde_debug_print ("gws: Create the button on task bar\n");

    __taskbar_button = (struct gws_window_d *) createwCreateWindow ( WT_BUTTON, 
                                               1, 1, "button",  
                                               2, 2, 100, 36,   
                                               __taskbar_window, 0, 
                                               xCOLOR_GRAY1, GWS_COLOR_BUTTONFACE3 );
    
    if ( (void *) __taskbar_button == NULL ){
        gde_debug_print ("gws: task bar button fail\n");  
    }

    /*
    gws_draw_button ("Button 1", 1, 1, 1, 
        __taskbar_window->left +2, 
        __taskbar_window->top  +2, 
        100, 36, GWS_COLOR_BUTTONFACE3 );
    */
}



/*
 ******************************
 * main: 
 * 
 */

int main (int argc, char **argv){

    int i=0;
    int _status = -1;


    // Isso registra uma gramado port.
    // a porta do ws.
    // mas isso ja foi feito na rotina que registra o ws.
    // nunca testado.
    //gramado_system_call (7006, 11, getpid(), 0 );

    struct sockaddr addr;
    addr.sa_family = AF_GRAMADO;
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';   
    

    int server_fd = -1; 
    int bind_status = -1;
    

    // Flag usada no loop.
    running = 1;

    // Activate the compositor.
    dirty_status = 1;

    // #debug
    gde_debug_print ("---------------------\n");
    gde_debug_print ("gws: Initializing ...\n");
    printf ("gws: gws is alive !  \n");


    // Init gws infrastructure.
    gwsInit ();


    // Let's create the traditional green background.
    create_background();
    create_taskbar();
 

    // Register.
    // Register window server as the current window server 
    // for this desktop.
    // See: connect.c

    _status = (int) register_ws();

    if (_status<0){
        gde_debug_print ("gws: Couldn't register the server \n");
        printf ("gws: Couldn't register the server \n");
        exit (1);
    }
    gde_debug_print ("gws: Registration ok \n");



    // #todo
    // Daqui pra frente é conexão com cliente.
    // Lembrando que o servidor vai se conectar à mais de um cliente.
    // ...


    //
    // Socket
    //

    // #debug
    printf ("gws: Creating socket\n");

    server_fd = (int) socket(AF_GRAMADO, SOCK_STREAM, 0);
    
    if (server_fd<0){
        printf("gws: Couldn't create the server socket\n");
        exit(1);
    }
 
    ____saved_server_fd = server_fd;

 
    //
    // bind
    // 
 
    // #debug
    printf ("gws: bind\n");
 
    bind_status = bind ( server_fd, (struct sockaddr *) &addr, sizeof(addr) );

    if (bind_status<0){
        printf("gws: Couldn't bind to the socket\n");
        exit(1);
    }


    //
    // =======================================
    //


    //
    // Calling child.
    //

    dtextDrawText ( (struct gws_window_d *) gui->screen,
        8, 80, COLOR_RED, "gws: Calling child" );

    
    // #atenção: 
    // Na máquina real, isso mostrou a barra, 
    // mas não mostrou a string criada na janela gui->screen..
    gws_show_backbuffer ();


    printf ("gws: * Calling child \n");
    
    // #test
    // Nesse test, s2 usará socket para se conectar
    // AF_GRAMADO.


    // #important:
    // Calling a child.

    gde_clone_and_execute ("gwst.bin");  
    //gde_clone_and_execute ("s3.bin"); 
    // ...

 
    printf ("gws: * yield \n");

    for (i=0; i<11; i++)
        gws_yield ();


    //
    // =======================================
    //

// loop:

    gde_debug_print ("gws: Entering main loop.\n");


    // + Compositor. (Redraw dirty rectangles)    
    // + Socket requests.
    // + Normal messages. (It's like signals.)
 

    // while (1)
    while (running == 1)
    {
        // Pinta ou não.
        if ( dirty_status == 1 )
            compositor();

        // Status da conecção com os clientes.
        // Pega mensagens de seus clientes.
        // Presta vários serviços inclusive drenar input
        // via mensagens tradicionais e repassar via socket.
        if (connection_status == 1){
            handle_request (____saved_server_fd);

        // Conexão desligada.
        // Ela começa desligada.Ligamos com F1.
        // Pega mensagens como um aplicativo normal.
        }else{
            handle_ipc_message(); 
        };
    };


    //
    // =======================================
    //

    // Done.
    
    gde_debug_print ("gws: exited. \n");
    printf ("gws: exited. \n");
    
    // #todo
    // The kernel needs to react when the window server closes.
    // We can't live without it.
    
    // #debug
    // #bugbug:
    // Page fault  when exiting ... 
    while(1){
        // HANG
    }
    
    return 0; 
}


int service_drain_input (void)
{
    gde_debug_print ("gws: service_drain_input [TODO]\n");
    //handle_ipc_message();
    return -1;
}


// service: Create a window.
// It's a wrapper.
// Chamaremos a função que cria a janela
// com base nos argumentos que estão no buffer
// que é uma variável global nesse documento.

int serviceCreateWindow (void){

	// O buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];
        
    struct gws_window_d *__mywindow;

    unsigned long x, y, w, h, color;

    
    gde_debug_print("gws: serviceCreateWindow:\n");
    //printf ("serviceCreateWindow:\n");

    x=message_address[4];  //x
    y=message_address[5];  //y
    w=message_address[6];  //w
    h=message_address[7];  //h
    color = message_address[8];
 
 
    // #todo
    // type passed by message.

     __mywindow = (struct gws_window_d *) createwCreateWindow ( WT_OVERLAPPED, 
                                              1, 1, "No-Name",  
                                              x, y, w, h,   
                                              gui->screen, 0, 
                                              COLOR_PINK, color ); 

    if ( (void *) __mywindow == NULL ){
       gde_debug_print ("createwCreateWindow: fail\n");
       //return -1;
    }


    int id = -1;
    id = gwsRegisterWindow ( __mywindow );

    if (id<0){
        gde_debug_print ("serviceCreateWindow: Couldn't register window\n");
        //return -1;
    }
    
  
    // preparando a resposta.
    // Ela será enviada depois pelo loop de socket.
    next_response[0] = (unsigned long) id; //window
    next_response[1] = SERVER_PACKET_TYPE_REPLY; //msg 
    next_response[2] = 0;
    next_response[3] = 0;


    gws_show_backbuffer (); //for debug    
    return 0; //todo
}



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


int servicepixelBackBufferPutpixel(void)
{
	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    unsigned long x,y,color;
      
    x=message_address[4];  // x
    y=message_address[5];  // y
    color=message_address[6];  // color

    pixelBackBufferPutpixel ( color, x, y );


    gws_show_backbuffer (); // for debug
    return 0;
}





int servicelineBackbufferDrawHorizontalLine (void)
{

	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    //x1,y,x2, color
    unsigned long x1,y,x2,color;
      
    x1 = message_address[4];  // 
    y  = message_address[5];   // 
    x2 = message_address[6];  // 
    color = message_address[7];
   
   lineBackbufferDrawHorizontalLine ( x1, y, x2, color );


   gws_show_backbuffer (); // for debug   
   return 0;
}


int serviceDrawButton(void)
{
	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    unsigned long x,y,width,height;
      
    x      = message_address[4];  // 
    y      = message_address[5];  // 
    width  = message_address[6];  // 
    height = message_address[7];  //
    // ...


    gws_draw_button ("Label", 1,1,1, 
        x, y, width, height, GWS_COLOR_BUTTONFACE3 );


   gws_show_backbuffer (); // for debug   
   return 0;
}



void gws_yield(void){
	
    gramado_system_call (265,0,0,0); //yield thread.
}








