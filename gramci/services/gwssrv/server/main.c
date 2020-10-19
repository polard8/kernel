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




// pertence a esse projeto, nao eh a biblioteca.
#include <gws.h>


//
// == Gramado Network Protocol ===============================
//

// Standard. (First version)
#define GNP_WID        0
#define GNP_MESSAGE    1
#define GNP_LONG1      2
#define GNP_LONG2      3
// #extension
#define GNP_LONG3      4
#define GNP_LONG4      5
#define GNP_LONG5      6
#define GNP_LONG6      7
//#body
#define GNP_BODY_OFFSET    16
// ...



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


int connection_status = 0;



// Window.
// See: window.h
//struct gws_window_d  *__bg_window;
//struct gws_window_d  *__taskbar_window; 
//struct gws_window_d  *__taskbar_button; 
// ...


//
// == Mouse ++ =======================================================
//


int MOUSE_WINDOW = -1;


// i8042 mouse status bit.
#define MOUSE_LEFT_BTN    0x01
#define MOUSE_RIGHT_BTN   0x02
#define MOUSE_MIDDLE_BTN  0x04
#define MOUSE_X_SIGN      0x10
#define MOUSE_Y_SIGN      0x20
//#define MOUSE_X_OVERFLOW  0x40
//#define MOUSE_Y_OVERFLOW  0x80

// Generic PS/2 Mouse Packet Bits
#define  MOUSE_LEFT_BUTTON    0x01
#define  MOUSE_RIGHT_BUTTON   0x02
#define  MOUSE_MIDDLE_BUTTON  0x04
#define  MOUSE_X_DATA_SIGN    0x10
#define  MOUSE_Y_DATA_SIGN    0x20
#define  MOUSE_X_OVERFLOW     0x40
#define  MOUSE_Y_OVERFLOW     0x80

long mouse_x = 0;
long mouse_y = 0;

char mouse_packet_data = 0;
char mouse_packet_x = 0;
char mouse_packet_y = 0;
char mouse_packet_scroll = 0;

char saved_mouse_x =0;
char saved_mouse_y =0;


//Estado dos botões do mouse
int mouse_buttom_1; 
int mouse_buttom_2;
int mouse_buttom_3;

//Estado anterior dos botões do mouse.
int old_mouse_buttom_1; 
int old_mouse_buttom_2;
int old_mouse_buttom_3;

//se ouve alguma modificação no estado 
//dos botões.
int mouse_button_action;


//=============================
//mouse control

// habilitar e desabilitar o mouse.
// usada pelos aplicativos.
int ps2_mouse_status;

int ps2_mouse_has_wheel;

//1= pressionado 0=liberado
int ps2_button_pressed;

int ps2_mouse_moving;
int ps2_mouse_drag_status;
//int ps2_mouse_drop_status;

int window_mouse_over;

//
// == prototypes ===================================
//



void update_mouse (void);
void parse_data_packet ( char data, char x, char y);
int top_at ( int x, int y );
int mouse_scan_windows (void);


/*
 * =====================================================
 * update_mouse:
 *     Updates the mouse position.
 */


void update_mouse (void){

//======== X ==========
// Testando o sinal de x.
// Do the x pos first.

//pega o delta x
//testa o sinal para x
do_x:

    if ( mouse_packet_data & MOUSE_X_SIGN ) 
    {
        goto x_neg;
    }


//Caso x seja positivo.
x_pos:

    mouse_x += mouse_packet_x;
    goto do_y;


//Caso x seja negativo.
x_neg:

    mouse_x -= ( ~mouse_packet_x + 1 );

    if (mouse_x > 0)
    {
        goto do_y;
    }
    mouse_x = 0;
 
 
//======== Y ==========
// Testando o sinal de x. 
// Do the same for y position.

//Pega o delta y.
//Testa o sinal para y.
do_y:

    if ( mouse_packet_data & MOUSE_Y_SIGN )
    {
        goto y_neg;
    }

//Caso y seja positivo.
y_pos:

    mouse_y -= mouse_packet_y;

    if ( mouse_y > 0 )
    {
        goto quit;
    }

    mouse_y = 0;
    goto quit;

//Caso y seja negativo. 
y_neg:

    mouse_y += ( ~mouse_packet_y + 1 );

// Quit
quit:
    return;
}


void parse_data_packet ( char data, char x, char y)
{

    //if (fd<0) 
        //return;

	// A partir de agora já temos os três chars.
	// Colocando os três chars em variáveis globais.
	// Isso ficará assim caso não haja overflow.
    // acho que isso sera usado na rotina de update.
    
    mouse_packet_data = (char) data;    // Primeiro char
    mouse_packet_x    = (char) x;    // Segundo char.
    mouse_packet_y    = (char) y;    // Terceiro char.

	// Salvando o antigo antes de atualizar.
	// Para poder apagar daqui a pouco.
	// Atualizando.
    saved_mouse_x = mouse_x;
    saved_mouse_y = mouse_y;
    
    //
    // == Update mouse position ====================
    //
    
    update_mouse (); 
    
    // Agora vamos manipular os valores obtidos através da 
    // função de atualização dos valores.
    // A função de atualização atualizou os valores de
    // mouse_x e mouse_y.
    mouse_x = (mouse_x & 0x000003FF );
    mouse_y = (mouse_y & 0x000003FF );


    // Limits
    //if ( mouse_x < 1 ){ mouse_x = 1; }
    //if ( mouse_y < 1 ){ mouse_y = 1; }
    //if ( mouse_x > (SavedX-16) ){ mouse_x = (SavedX-16); }
    //if ( mouse_y > (SavedY-16) ){ mouse_y = (SavedY-16); }

    /*
    // Comparando o novo com o antigo, pra saber se o mouse se moveu.
    // #obs: Pra quem mandaremos a mensagem de moving ??
    if ( saved_mouse_x != mouse_x || saved_mouse_y != mouse_y )
    {
		// flag: o mouse está se movendo.
		// usaremos isso no keydown.
		// >> na hora de enviarmos uma mensagem de mouse se movendo
		// se o botão estiver pressionado então temos um drag (carregar.)
		// um release cancela o carregar.
		
        ps2_mouse_moving = 1;

       // draw

       // Apaga o antigo.
       // + Copia no LFB um retângulo do backbuffer 
       // para apagar o ponteiro antigo.
       refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );
                
       // Acende o novo.
       //+ Decodifica o mouse diretamente no LFB.
       // Copiar para o LFB o antigo retângulo  
       // para apagar o ponteiro que está no LFB.
       bmpDisplayMousePointerBMP ( mouseBMPBuffer, mouse_x, mouse_y );   
                         
    }else{
		
		// Não redesenhamos quando o evento for um click, sem movimento.
        ps2_mouse_moving = 0;
    }; 
    */


	//Apenas obtendo o estado dos botões.
    mouse_buttom_1 = 0;
    mouse_buttom_2 = 0;
    mouse_buttom_3 = 0;


	// ## LEFT ##
    if ( ( mouse_packet_data & MOUSE_LEFT_BUTTON ) == 0 )
    {
		//liberada.
        mouse_buttom_1 = 0;
        ps2_button_pressed = 0;
        
        //mudamos sempre que pressionar.
        //todo: mudaremos sempre que pressionar numa title bar.
        //refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );
        //bmpDisplayMousePointerBMP ( mouseBMPBuffer, mouse_x, mouse_y ); 

    }else if( ( mouse_packet_data & MOUSE_LEFT_BUTTON ) != 0 )
     {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
            mouse_buttom_1 = 1;
            mouse_buttom_2 = 0;
            mouse_buttom_3 = 0;
            ps2_button_pressed = 1;
            
            //mudamos sempre que pressionar.
            //todo: mudaremos sempre que pressionar numa title bar.
            //refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );
            //bmpDisplayMousePointerBMP ( appIconBuffer, mouse_x, mouse_y ); 
     };
     
     
     
	// ## RIGHT ##
    if ( ( mouse_packet_data & MOUSE_RIGHT_BUTTON ) == 0 )
    {
	    //liberada.
        mouse_buttom_2 = 0;
        ps2_button_pressed = 0;

    }else if( ( mouse_packet_data & MOUSE_RIGHT_BUTTON ) != 0 )
        {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
            mouse_buttom_1 = 0;
            mouse_buttom_2 = 1;
            mouse_buttom_3 = 0;
            ps2_button_pressed = 1;
        };

     
     
	// ## MIDDLE ##
    if ( ( mouse_packet_data & MOUSE_MIDDLE_BUTTON ) == 0 )
    {
	    //liberada.
        mouse_buttom_3 = 0;
        ps2_button_pressed = 0;

    }else if( ( mouse_packet_data & MOUSE_MIDDLE_BUTTON ) != 0 )
        {
	        //pressionada.
	        //Não tem como pressionar mais de um botão por vez.
	        mouse_buttom_1 = 0;
	        mouse_buttom_2 = 0;
	        mouse_buttom_3 = 1;
	        ps2_button_pressed = 1;
        };
   
     
	// ===
	// Confrontando o estado atual com o estado anterior para saber se ouve 
	// alguma alteração ou não.
	// 1 = ouve alteração.

    if ( mouse_buttom_1 != old_mouse_buttom_1 ||
         mouse_buttom_2 != old_mouse_buttom_2 ||
         mouse_buttom_3 != old_mouse_buttom_3 )
    {
        mouse_button_action = 1;

    }else{
        mouse_button_action = 0;
    };
    
    
    //#isso ainda eh um teste.
    old_mouse_buttom_1 = mouse_buttom_1;
    old_mouse_buttom_2 = mouse_buttom_2;
    old_mouse_buttom_3 = mouse_buttom_3;
}


/*
 **************** 
 * top_at: 
 * 
 */

// #todo
// z order not initialized yet.


// pega a janela que está mais ao topo da zorder e que
// corresponda às cordenadas do mouse.
// retorna window id

int top_at ( int x, int y )
{
    int z = 0;
    int wID = -1;
    struct gws_window_d *__last_found;
    struct gws_window_d *tmp;

  
    //max 1024 janelas.
    for ( z=0; z<ZORDER_MAX; z++ )
    {
        //pega a próxima na zorderlist;
        tmp = (struct gws_window_d *) zList[z];
        
        //check
        if ( (void *) tmp != NULL )
        {
            if ( tmp->used == 1 && tmp->magic == 1234 )
            {

                 // #importante
                 // Checando coordenadas.
                  if ( x > (tmp->left)  && 
                       x < (tmp->left + tmp->width)  && 
                       y > (tmp->top)  &&
                       y < (tmp->top + tmp->height)  )
                 {
					 //printf ("%d",z);
                      // salva essa.
                      __last_found = (struct gws_window_d *) tmp;
                 }
            }
        }

    };

__found:

    window_mouse_over = __last_found->id;

    return (int) __last_found->id;
}



int mouse_scan_windows (void)
{
    struct gws_window_d *Window;
    int wID = -1;

    wID = (int) top_at ( mouse_x, mouse_y );


    //================
    // -1 = Se não temos uma janela.
    if ( wID < -1 ) //( wID == -1 )
    { 
		//... 
    }

    //============================ 
    // Se estamos sobre uma janela válida.
    if ( wID >= 0 )  //if ( wID > -1 )
    { 
        Window = (struct gws_window_d *) windowList[wID];

        if ( (void *) Window == NULL ) { return -1; }
        if ( Window->used != 1 || Window->magic != 1234){ return -1; }

        //===============================================
        // ***Se houve mudança em relação ao estado anterior.
        // Nesse momento um drag pode terminar
        //if ( mouse_button_action == 1 )
        //{ ... }


        //===============================================
        // *** Se NÃO ouve alteração no estado dos botões, então apenas 
        // enviaremos a mensagem de movimento do mouse e sinalizamos 
        // qual é a janela que o mouse está em cima.
        // Não houve alteração no estado dos botões, mas o mouse
        // pode estar se movendo com o botão pressionado.
        //a não ser que quando pressionamos o botão ele envie várias
        //interrupções, igual no teclado.
        //if ( mouse_button_action == 0 )
        //{ ... }
        
    }



    return -1;
}



//
// == Mouse -- =======================================================
//


//
// Prototypes.
//

// Get system message from the thread's queue.
void xxxHandleNextSystemMessage (void);
// Get client's request from socket.
void xxxHandleNextClientRequest (int fd);


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
 * xxxGetNextClientRequest:
 * 
 * 
 */

// internal.
// Messages sent via socket.
// obs: read and write use the buffer '__buffer'
// in the top of this file.

//#todo:
// No loop precisamos de accept() read() e write();
// Get client's request from socket.
void xxxHandleNextClientRequest (int fd){

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
        gwssrv_debug_print ("gwssrv: xxxHandleNextClientRequest fd\n");
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
    
    // Different kind of errors!
    
    // Precisamos fechar o client e yield.
    if (n_reads < 0) { gwssrv_yield(); return; }
    
    // Sem problemas, nao precisamos fechar o client.
    if (n_reads == 0){ gwssrv_yield(); return; }


    // Nesse momento lemos alguma coisa.   
 
    //
    // == Processing the request =============================
    //
 
    // Invalid request.
    if (message_buffer[1] == 0 )
    {
        gwssrv_debug_print ("xxxHandleNextClientRequest: Invalid request!\n");
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
        
        // 4567 = Raw mouse packet.
        if (message_buffer[1] == 4567 )
        {
            parse_data_packet( 
                (char) message_buffer[2],    //long1 data
                (char) message_buffer[3],    //long2 x
                (char) message_buffer[4] );  //long3 y
        
            // Processed mouse packet.
            // isso eh provisorio, a rotina de transformacao 
            // vai nos dar o estado dos botoes e mandaremos a mensagem correta
            //par ao cliente.
            message_buffer[1] = 4568; 
            message_buffer[2] = mouse_x;
            message_buffer[3] = mouse_y;
            
            //POINTER
            dtextDrawString(mouse_x, mouse_y,COLOR_BLUE, "T");
            //charBackbufferDrawcharTransparent ( mouse_x, mouse_y, COLOR_BLUE, "T" );
            gws_refresh_rectangle( mouse_x, mouse_y, 8, 8 );
        }

        debug_print("gwssrv: Sending response\n");
        
        n_writes = send ( fd, __buffer, sizeof(__buffer), 0 );
        
        if (n_writes<=0){
             debug_print ("gwssrv: [FAIL] Couldn't send response!\n"); 
        }
        message_buffer[1] = 0;
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
    //printf ("gws: xxxGetNextClientRequest: calling window procedure \n");
 
                
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
    sprintf( m, "~ Response from gwssrv \n");

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
    int b=0;
    for (b=0; b<MSG_BUFFER_SIZE; b++)
        __buffer[b] = 0;


    // Cleaning
    int c=0;
    for (c=0; c<NEXTRESPONSE_BUFFER_SIZE; c++)  //32. todo: 512
        next_response[c] = 0;


    gwssrv_debug_print ("gwssrv: Response sent\n");  
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

/*
 ********************************** 
 * xxxGetNextSystemMessage: 
 * 
 * 
 */

// internal
// System ipc messages. (It's like a signal)
// Get system message from the thread's queue.
void xxxHandleNextSystemMessage (void){
    
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
        // #bugbug: 
        // O window server não tem esse ponteiro de janela.
        // ele até aceitaria um handle.
        // #bugbug: Something is very wrong with this routine.
        //MSG_GWS_HELLO
        case 1000:
            gwssrv_debug_print ("gwssrv: Message number 1000\n");
            //#bugbug: Esse endereço de estrutura esta mudando para um valor
            //que nao podemos acessar em ring3.
            if ( (void*) gui->screen != NULL)
            {
                //if ( gui->screen->used == 1 && gui->screen->magic == 1234 ){
                    dtextDrawText ( (struct gws_window_d *) gui->screen,
                        long1, long2, COLOR_GREEN,
                       "gwssrv: Hello friend. This is the Gramado Window Server!");
                //}
            } 
            gws_show_backbuffer();
            break;


        // Create Window REQUEST!
        // Usará o buffer global
        // case MSG_CREATE_WINDOW:
        //MSG_GWS_CREATEWINDOW
        case 1001:
            gwssrv_debug_print ("gwssrv: [FIXME] Message number 1001\n");
            serviceCreateWindow();
            break; 

        // backbuffer putpixel
        //MSG_GWS_BACKBUFFERPUTPIXEL
        case 1002:
            servicepixelBackBufferPutpixel(); 
            break;

        // backbuffer draw horizontal line
        //MSG_GWS_BACKBUFFERHORIZONTALLINE
        case 1003:
            servicelineBackbufferDrawHorizontalLine();
            break;


        // Draw char
        // MSG_GWS_DRAWCHAR
        // See: char.c
        case 1004:
            gwssrv_debug_print ("gwssrv: Message number 1004\n");
            serviceDrawChar();
            break;


        // Draw text
        // MSG_GWS_DRAWTEXT
        // See: dtext.c
        case 1005:
           gwssrv_debug_print ("gwssrv: Message number 1005\n");
           serviceDrawText();
           break;


        // Refresh window
        //MSG_GWS_REFRESHWIDNOW
        case 1006:
           gwssrv_debug_print ("gwssrv: Message number 1006\n");
           serviceRefreshWindow();
           break;
           

        // Redraw window
        //MSG_GWS_REDRAWWINDOW
        case 1007:
           gwssrv_debug_print ("gwssrv: Message number 1007\n");
           serviceRedrawWindow();
           break;

        // Resize window
        //MSG_GWS_RESIZEWINDOW
        case 1008:
           gwssrv_debug_print ("gwssrv: Message number 1008\n");
           serviceResizeWindow();
           break;

        //MSG_GWS_CHANGEWINDOWPOSITION
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
        //MSG_GWS_SHUTDOWN
        case 2010:
            gwssrv_debug_print ("gwssrv: [2010] Disconnect\n");
            break;
            
        // Refresh screen 
        // refresh screen using kgws service. 
        //MSG_GWS_REFRESHSCREEN
        case 2020:
            gws_show_backbuffer();
            break;
             

        // Refresh rectangle ... 
        //MSG_GWS_REFRESHRECTANGLE
        case 2021:
            serviceRefreshRectangle();
            break;

        // When a client send us an event
        // MSG_GWS_CLIENTEVENT
        case 2030:
            gwssrv_debug_print ("gwssrv: [2030] serviceClientEvent\n");
            //serviceClientEvent();
            break;

        // When a client get the next event from it's own queue.
        // MSG_GWS_NEXTEVENT
        case 2031:
            gwssrv_debug_print ("gwssrv: [2031] serviceNextEvent\n");
            //serviceNextEvent();
            break;
        
        //MSG_GWS_PROTOCOL
        case 3000:
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
    int WindowId = -1;


    gwssrv_debug_print ("gwssrv: create_background\n");


    // bg window

    __bg_window = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                            1, 1, "gwssrv-bg",  
                                            0, 0, w, h,   
                                            gui->screen, 0, 
                                            COLOR_BACKGROUND, COLOR_BACKGROUND );    

    if ( (void *) __bg_window == NULL ){
        gwssrv_debug_print ("gwssrv: __bg_window fail\n");  
        printf ("gwssrv: __bg_window fail\n");
        exit(1);
        return;
    }


    WindowId = gwsRegisterWindow (__bg_window);

    if (WindowId<0){
        gwssrv_debug_print ("create_background: Couldn't register window\n");
        //return -1;
    }


    //__bg_window->dirty = 1;
    
    //xxxx_refresh();
    //while(1){}
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

 
    // Testing bmp.
    // See:
    gwssrv_display_system_icon ( 1, 8, 100);
    gwssrv_display_system_icon ( 2, 8, 120);
    gwssrv_display_system_icon ( 3, 8, 140);
    gwssrv_display_system_icon ( 4, 8, 160);
    //#debug breakpoint
    //while(1){}


    //
    // init lib
    //
    
    // See: grprim.c
    grInit();
    
    
    
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
       
    //See: window.c
    //create_main_menu();
  
    //gws services
    //gws_refresh_rectangle(0,0,400,400);
    //gws_show_window_rect(gui->screen);
    
    gws_show_backbuffer();              
    //while(1){}
       
    
        
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


// When a client send us an event
int serviceClientEvent(void)
{
    //O buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    unsigned long window =0;
    unsigned long msg    =0;
    unsigned long long1  =0;
    unsigned long long2  =0;


    //struct gws_client_d *client;
    //struct gws_window_d *hWindow;
    //struct gws_event_d  *event;
    //...


    window  = message_address[0]; 
    msg     = message_address[1]; 
    long1   = message_address[2]; 
    long2   = message_address[3]; 

    //z      = message_address[4]; 
    //z      = message_address[5]; 
    //z      = message_address[6]; 
    //z      = message_address[7]; 
    // ...

    // ...

    return -1;
}

// When a client get the next event from it's own queue.
int serviceNextEvent(void)
{
    //O buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    unsigned long window =0;
    unsigned long msg    =0;
    unsigned long long1  =0;
    unsigned long long2  =0;


    //struct gws_client_d *client;
    //struct gws_window_d *hWindow;
    //struct gws_event_d  *event;
    //...


    window  = message_address[0]; 
    msg     = message_address[1]; 
    long1   = message_address[2]; 
    long2   = message_address[3]; 

    //z      = message_address[4]; 
    //z      = message_address[5]; 
    //z      = message_address[6]; 
    //z      = message_address[7]; 
    // ...

    // ...

    return -1;
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

    //int Status = (-1);

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
    invalidate();
    invalidate_background();


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
        gwssrv_debug_print ("-----------------------\n");
        gwssrv_debug_print ("gwssrv: Initializing...\n");
        printf             ("gwssrv: Initializing...\n");
        
        
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
        listen(server_fd,5);

        // Draw !!!
        // Init gws infrastructure.
        // Let's create the traditional green background.

        InitGraphics();
        
        //See: line.c
        //test_draw_line();
        //test_draw_line2();//illusion
        //while(1){}
        

        // Calling child.
        //printf ("gwssrv: Calling child \n");  


        //gwssrv_clone_and_execute ("gws.bin");      // command gws.bin
        //gwssrv_clone_and_execute ("gwm.bin");      // window manager
        //gwssrv_clone_and_execute ("fileman.bin");  
        //gwssrv_clone_and_execute ("editor.bin");           
        //gwssrv_clone_and_execute ("terminal.bin");  
        //gwssrv_clone_and_execute ("browser.bin");
        gwssrv_clone_and_execute ("launch1.bin"); 
        //gwssrv_clone_and_execute ("s2.bin");      // shell  
        //gwssrv_clone_and_execute ("s3.bin");    // hello        
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
        //rectBackbufferDrawRectangle ( 200, 400, 100, 60, COLOR_YELLOW, 1 );


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
        
        //initialize frames counter,
        frames_count = 0;
        fps = 0;
        
        while (running == 1)
        {
            // Se tem ou não retângulos sujos.
            // #bugbug: Talvez isso seja trabalho do window manager.
            // mas ele teria que chamar o window server pra efetuar o refresh
            //dos retângulos.
            // See comp.c
            
            //See: window.c
            wm_process_windows();
            //wm_process_events(); //todo
            
            //if ( dirty == 1 )
            //{
            //    compositor();    //nothing for now.
            //    dirty = 0;
            //}

            //if (isTimeToQuit == 1) { break; };
         

            // Accept connection from a client. 

            // #ps: Actually, accept2 returns the fd of the server,
            // and write will copy from on socket to another.

            //newconn = accept ( curconn, 
            //              (struct sockaddr *) &gramsock, 
            //              (socklen_t *) addr_len );
            
            newconn = accept2 ( curconn, 
                          (struct sockaddr *) &gramsock, 
                          (socklen_t *) addr_len );
                          
            if (newconn < 0) {
                gwssrv_debug_print ("gwssrv: ERROR on Accepting\n");
                gwssrv_yield();
 
            // Request from the new connection
            }else{

                //mensagens de clientes.
                xxxHandleNextClientRequest (newconn);
                //xxxHandleNextClientRequest (curconn);

                //close ?
                //#bugbug: We can not close if we are using accept2.
                //shutdown(newconn, SHUT_RDWR);
                //shutdown(newconn, 0);         
                //close(newconn);
            };
        };


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
    // while(1){ xxxGetNextSystemMessage(); }

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








