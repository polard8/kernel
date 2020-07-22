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
int serviceDrawChar(void);
int serviceDrawText(void);
int serviceDrawButton (void); //??
// ...


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
 ****************************
 * handle_request:
 * 
 * 
 */

// internal.
// Messages sended via socket.
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
        gde_debug_print ("gwssrv: handle_request fd\n");
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
        debug_print ("gwssrv: [TEST] INPUT request !!! \n");

        // Pegar o input!

        // Get message from kernel.
        gde_enter_critical_section();
        gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section();
        
        //message_buffer[1] = SERVER_PACKET_TYPE_EVENT;
        send ( fd, __buffer, sizeof(__buffer), 0 );
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
     
    //gde_debug_print ("Sending response ...\n");  

__again:

    // #debug:

    gde_debug_print ("gwssrv: Sending response ...\n");
    
                
    // Primeiros longs do buffer.
    message_buffer[0] = next_response[0];         // Window ID.
    message_buffer[1] = SERVER_PACKET_TYPE_REPLY; // next_response[1] 
    message_buffer[2] = next_response[2];         // Return value (long1)
    message_buffer[3] = next_response[3];         // Return value (long2)

    //# it works.
    char *m = (char *) (&__buffer[0] + 16);
    sprintf( m, "gwssrv: This is a response from GWS!\n");


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
    for(c=0; c<32; c++)
        next_response[c] = 0;

    gde_debug_print ("gwssrv: Response sent\n");  
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
    gde_enter_critical_section();
    gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
    gde_exit_critical_section();

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
            gde_debug_print("gwssrv: gwsProcedure 8080\n");
            service_drain_input();
            break;

        case MSG_SYSKEYUP:
            switch ( long1)
            {
                // #debug
                case VK_F1:
                    gde_debug_print("gwssrv: gwsProcedure VK_F1 Connection ON\n");
                    connection_status = 1;
                    //gde_reboot ();
                    break;
                    
                // #debug
                // mostrar informações sobre o socket 
                // do gws.    
                case VK_F2:
                    gde_debug_print("gwssrv: gwsProcedure VK_F2 Connection OFF\n");
                    connection_status = 0;
                    //my_pid = (int) getpid();
                    //gramado_system_call (7008,my_pid,0,0);
                    break;

                case VK_F3:
                    gde_debug_print ("gwssrv: F3\n");
                    bmpDisplayBMP (0,0,0); //#todo: test.
                    break;

                // #test
                // Die.
                case VK_F4:
                    gde_debug_print ("gwssrv: F4 [EXIT] Exiting the server ...\n");
                    running = 0;
                    break;

                // ...
                  
                // Enviar a mensagem para o processo associado
                // com a janela que tem o foco de entrada.
                default:
                    gde_debug_print ("gwssrv: MSG_SYSKEYUP\n");
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
            
            gde_debug_print ("gwssrv: MSG_KEYDOWN\n");
            break;

        // Hello!
        case 1000:
            gde_debug_print ("gwssrv: Message number 1000\n");
            
            // Draw text inside a window.
            // #bugbug: O window server não tem esse ponteiro de janela.
            // ele até aceitaria um handle.
            dtextDrawText ( (struct gws_window_d *) __mywindow,
                long1, long2, COLOR_GREEN,
                "gwssrv: Hello friend. This is the Window Server!" );
                
            gws_show_backbuffer ();
            break;


        // Create Window.
        // Usará o buffer global
        // case MSG_CREATE_WINDOW:
        case 1001:
            serviceCreateWindow (); 
            break; 

        // backbuffer putpixel
        case 1002:
            servicepixelBackBufferPutpixel(); //pixel
            break;

        // backbuffer draw horizontal line
        case 1003:
            servicelineBackbufferDrawHorizontalLine();
            break;
    
        //Draw char
        case 1004:
            gde_debug_print ("gwssrv: Message number 1004\n");
            serviceDrawChar();
                       
            //dtextDrawText ( (struct gws_window_d *) __mywindow,
                //100, 100, COLOR_GREEN, "DRAW CHAR" );
            //gws_show_backbuffer();
           break;

        // Draw text
        case 1005:
           //#todo: tem que testar isso!!!
           gde_debug_print ("gwssrv: Message number 1005\n");
           serviceDrawText();
           break;
    
        // ...
               
        // backbuffer putpixel. (again)
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

        // ...


        // Disconnect.
        // showdown.
        // Um cliente quer se desconectar.
        case 2010:
            gde_debug_print ("gwssrv: [2010] Disconnect\n");
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
            gde_debug_print ("gwssrv: Default message number\n");
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

    gde_debug_print ("gwssrv: create_background\n");


    __bg_window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                         1, 1, "gwssrv-bg",  
                                         0, 0, w, h,   
                                         gui->screen, 0, 
                                         COLOR_BACKGROUND, COLOR_BACKGROUND );    


    if ( (void *) __bg_window == NULL ){
        gde_debug_print ("gwssrv: __bg_window fail\n");  
        return;
    }
    
    //#todo: register
}


void create_taskbar (void)
{
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();

    //
    // Bar
    //

    gde_debug_print ("gwssrv: create_taskbar:\n");

    __taskbar_window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                               1, 1, "gwssrv-taskbar",  
                                               0, 0, w, 40,   
                                               gui->screen, 0, 
                                               xCOLOR_GRAY1, xCOLOR_GRAY1 );
    
    if ( (void *) __taskbar_window == NULL ){
        gde_debug_print ("gwssrv: __taskbar_window fail\n");  
    }
    //#todo: register

    //
    // Button
    //
    
    // #test
    // Create button.

    gde_debug_print ("gwssrv: Create the button on task bar\n");

    __taskbar_button = (struct gws_window_d *) createwCreateWindow ( WT_BUTTON, 
                                               1, 1, "button",  
                                               2, 2, 100, 36,   
                                               __taskbar_window, 0, 
                                               xCOLOR_GRAY1, GWS_COLOR_BUTTONFACE3 );
    
    if ( (void *) __taskbar_button == NULL ){
        gde_debug_print ("gwssrv: task bar button fail\n");  
    }
    //#todo: register

    /*
    gws_draw_button ("Button 1", 1, 1, 1, 
        __taskbar_window->left +2, 
        __taskbar_window->top  +2, 
        100, 36, GWS_COLOR_BUTTONFACE3 );
    */
}

void xxx_test_load_icon(void);
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


void xxx_test_load_bmp(void);
void xxx_test_load_bmp(void)
{
    //
    // =======================================
    //
    
    //#todo
    //Trying to load and show a bmp file.
    
    char *bmp_buffer;
    //char *file_name = "FOLDER  BMP";
    char file_name[] = "FOLDER  BMP";
    //char file_name[] = "terminal.bmp";
    bmp_buffer = (char *) malloc(1024*128);
    if ( (void *) bmp_buffer == NULL )
        printf ("gwssrv: xxx_test_load_bmp bmp_buffer fail\n");
    
    // ?? Onde fica o heap usado por esse malloc ??
    printf ("gwssrv: xxx_test_load_bmp bmp_buffer = %x\n", bmp_buffer);
  
    //stdio_fntos ( (char *) file_name ); //não precisa
    
    // #bugbug
    // Essa rotina pode NÃO ter usado o
    // diretório de páginas do aplicativo.
    // Portando o endereço que indicamos e pertence ao
    // heap do aplicativo não é acessível ao kernel, pois
    // o kernel usou seu próprio diretório de páginas.
    // A solução seria essa rotina trocar o diretório de páginas
    // provisóriamente.
    // Outra solução seria ustilizarmos outras rotinas 
    // de carregamento de arquivo.
    

    // #bugbug
    // essa rotina não carrega no buffer.

    int r=-1;
    
    /*
    r = gramado_system_call ( SYSTEMCALL_READ_FILE, 
        (unsigned long) file_name,   //name 
        (unsigned long) 0,           //flags
        (unsigned long) 0);          //mode
    */

    //if(r<0)
        //printf("gwssrv: r fail\n");
    
    // #test
    // [FAIL]
    void *buf;
    buf = (void*) gramado_system_call ( 9000, 
                       (unsigned long) file_name,   //name 
                       (unsigned long) 0,           
                       (unsigned long) 0);          

    if((void*)buf ==NULL){
        printf("gwssrv: buf fail\n");
        return;
    }

    bmp_buffer = buf;

    //#test
    if ( bmp_buffer[0] != 'B' || bmp_buffer[1] != 'M' )
    {
        printf (">>>> %c %c\n",&bmp_buffer[0],&bmp_buffer[1]);
        gde_debug_print ("gwssrv: xxx_test_load_bmp SIG FAIL \n");
        //return;
        
        printf("xxx_test_load_bmp: *hang1\n");
        //#debug
        gws_show_backbuffer();
        while(1);
    }

          
    bmpDisplayBMP ((char *) bmp_buffer, (unsigned long) 80, (unsigned long) 80);    
    //gde_display_bmp((char *)bmp_buffer, (unsigned long) 80, (unsigned long) 80);

     printf("xxx_test_load_bmp: *hang2\n");
     //#debug
     gws_show_backbuffer();
     while(1);
    

    /*
     //ok isso funciona.
    pixelBackBufferPutpixel ( (unsigned long) COLOR_RED, 
         (unsigned long) 100, 
         (unsigned long) 100 );

    pixelBackBufferPutpixel ( (unsigned long) COLOR_RED, 
         (unsigned long) 102, 
         (unsigned long) 100 );

    pixelBackBufferPutpixel ( (unsigned long) COLOR_RED, 
         (unsigned long) 104, 
         (unsigned long) 100 );
    */
    
    //
    // =======================================
    //
}

//internal
void InitGraphics(void)
{
    int __init_status = -1;
    
    debug_print("gwssrv: InitGraphics\n");
    
    __init_status = gwsInit();

    if(__init_status != 0)
    {
        debug_print("gwssrv: InitGraphics [PANIC] Couldn't initialize the graphics\n");
        printf("gwssrv: InitGraphics [PANIC] Couldn't initialize the graphics\n");
        while(1);
    }

    if( (void*) gui->screen != NULL){
        dtextDrawText ( (struct gws_window_d *) gui->screen,
            200, 80, COLOR_RED, "gwssrv: Initializing graphics" );
    }
    
    create_background();
    
    // #bugbug
    // The ws will not create the top bar.
    // The wm will create the top bar.
    // The ws will not create frames or controls.
    // The wm will create frames and controls.
    //create_taskbar();


    // #test
    // Precisamos encontrar uma rotina de carregamento apropriada.
    // xxx_test_load_bmp(); //[FAIL]
    // xxx_test_load_icon();
    
    //gws services
    //gws_refresh_rectangle(0,0,400,400);
    //gws_show_window_rect(gui->screen);
    
    gws_show_backbuffer();            
    
    debug_print("gwssrv: InitGraphics done\n");

    //#debug
        //while(1){};
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

    struct sockaddr addr;
    addr.sa_family = AF_GRAMADO;
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';   
    
    int server_fd = -1; 
    int bind_status = -1;


    // Flag usada no loop.
    running = 1;
    
    int i=0;
    int _status = -1;


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
        gde_debug_print ("---------------------\n");
        gde_debug_print ("gwssrv: Initializing...\n");
        printf ("gwssrv: Initializing... \n");


        // Register.
 
        // #bugbug
        // I don't know if we can register more than one time.
        // We can fix it!

        // Register.
        // Register window server as the current window server 
        // for this desktop.
        // See: connect.c
        _status = (int) register_ws();

        if (_status<0){
            gde_debug_print ("gwssrv: Couldn't register the server \n");
            printf ("gwssrv: Couldn't register the server \n");
            exit(1);
        }
        gde_debug_print ("gwssrv: Registration ok \n");


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

        if (server_fd<0){
            printf("gwssrv: Couldn't create the server socket\n");
            exit(1);
        }
        ____saved_server_fd = server_fd;



        //
        // bind
        // 
    
        // #debug
        printf ("gwssrv: bind\n");
 
        bind_status = bind ( server_fd, (struct sockaddr *) &addr, sizeof(addr) );

        if (bind_status<0){
            printf("gwssrv: Couldn't bind to the socket\n");
            exit(1);
        }



        //#todo
        //listen()
        
        
        //
        // Draw !!!
        //


        // Init gws infrastructure.
        // Let's create the traditional green background.
        
        InitGraphics();


        //
        // Calling child.
        //

        //printf ("gwssrv: Calling child \n");  

        //gde_clone_and_execute ("gws.bin");   
        gde_clone_and_execute ("terminal.bin");  
        //gde_clone_and_execute ("gwm.bin"); 
        //gde_clone_and_execute ("browser.bin"); 
        // ...        



        //
        // Wait
        //

        printf ("gwssrv: [FIXME] yield \n");
       
        for (i=0; i<11; i++)
            gwssrv_yield ();
 

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
        gde_debug_print ("gwssrv: Entering main loop.\n");

        //#todo:
        // No loop precisamos de accept() read() e write();

        // + Compositor. (Redraw dirty rectangles)    
        // + Socket requests.
        // + Normal messages. (It's like signals.)
 
        //not used for now.
        connection_status = 1;


        int newconn = -1;
        int curconn = ____saved_server_fd;
        
        socklen_t addr_len;
        addr_len = sizeof(addr);
    
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
            newconn = accept( curconn, 
                          (struct sockaddr *) &addr, 
                          (socklen_t *) addr_len );
                          
            if (newconn < 0) {
                gde_debug_print ("gwssrv: ERROR on accept\n");
 
            // Request from the new connection
            }else{

                //mensagens de clientes.
                handle_request (newconn);
                //handle_request (curconn);
                // close??
                
                //mensagens de sistema.
                //afetarão a janela com o foco.
                //gwssrv_get_system_message();
            };
        };


        // #todo
        // Bom, nesse momento precisamos liberar os recursos
        // para que o loop reinicie o servidor.
        
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
    
    gde_debug_print ("gwssrv: exited. \n");
    printf ("gwssrv: exited. \n");
    
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



int service_drain_input (void)
{
    gde_debug_print ("gwssrv: service_drain_input [TODO]\n");
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

    unsigned long x, y, w, h, color, type;

    
    gde_debug_print("gwssrv: serviceCreateWindow:\n");
    //printf ("serviceCreateWindow:\n");

    x=message_address[4];  //x
    y=message_address[5];  //y
    w=message_address[6];  //w
    h=message_address[7];  //h
    color = message_address[8];
    type  = message_address[9];


    // #todo
    // type passed by message.

     //__mywindow = (struct gws_window_d *) createwCreateWindow ( WT_OVERLAPPED, 
     __mywindow = (struct gws_window_d *) createwCreateWindow ( type, 
                                              1, 1, "No-Name",  
                                              x, y, w, h,   
                                              gui->screen, 0, 
                                              COLOR_PINK, color ); 

    if ( (void *) __mywindow == NULL ){
       gde_debug_print ("gwssrv: createwCreateWindow fail\n");
       //return -1;
    }


    int id = -1;
    id = gwsRegisterWindow ( __mywindow );

    if (id<0){
        gde_debug_print ("gwssrv: serviceCreateWindow Couldn't register window\n");
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

   gws_show_backbuffer(); // for debug   
   return 0;
}


//todo
int serviceDrawChar(void)
{

	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d *window;
    int window_id = -1;
    unsigned long x;
    unsigned long y;
    unsigned long color;
    
    int __char;
    char *text_buffer;    // #todo


    // #debug
    gde_debug_print ("gwssrv: serviceDrawChar\n");


    // Get
    
    
    window_id = message_address[4];
    x         = message_address[5];
    y         = message_address[6]; 
    color     = message_address[7];
    unsigned long C = (unsigned long) message_address[8];
    //text_buffer =    //#todo
   
    //lets create a fake string.
    unsigned char _string[4];
   
   _string[0] = (unsigned char) C;
   _string[1] = (unsigned char) 0;   
   
    
    //
    // Window ID
    //
   
    // Limits
    if ( window_id < 0 || window_id >= WINDOW_COUNT_MAX ){
        gde_debug_print ("gwssrv: serviceDrawChar window_id\n");
        return -1;
    }

    //#todo
    // Get the window structure given the id.
    window = (struct gws_window_d *) windowList[window_id];
   
    if ( (void *) window == NULL ){
        gde_debug_print ("gwssrv: serviceDrawChar window\n");
        return -1;
    }
    
    if ( window->used != 1 || window->magic != 1234 ){
        gde_debug_print ("gwssrv: serviceDrawChar validation\n");
        return -1;
    }
    
    //
    // Draw
    //

    // Ok it is working
    dtextDrawText ( (struct gws_window_d *) window,
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
        
    //gws_show_backbuffer ();       // for debug   
    //gws_show_window_rect(window);   // something faster for now.
    //something faster.
    gws_refresh_rectangle ( 
        window->left +x, 
        window->top  +y, 
        8,   //char width 
        8 ); // char height 

    return 0;
}



int serviceDrawText(void)
{

	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d *window;
    int window_id = -1;
    unsigned long x;
    unsigned long y;
    unsigned long color;
    
    char *text_buffer;    // #todo


    // #debug
    gde_debug_print ("gwssrv: serviceDrawText\n");


    // Get
    
    
    window_id = message_address[4];
    x         = message_address[5];
    y         = message_address[6]; 
    color     = message_address[7];
    //text_buffer =    //#todo
   
   //
   // Draw
   //
   
    //#todo
    // Get the window structure given the id.
    //window = (struct gws_window_d *) windowList[window_id];
    
    //#test
    // Usando a janela screen por enquanto.
    dtextDrawText ( (struct gws_window_d *) gui->screen,
        x, y, color, 
        "text-test" );

   gws_show_backbuffer (); // for debug   
   
   return 0;
}


//#bugbug
// Usaremos a função create window para desenhar botões.
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


   gws_show_backbuffer(); // for debug   
   return 0;
}



void gwssrv_yield(void)
{
    gramado_system_call (265,0,0,0); //yield thread.
}








