/*
 * File: xproc.c
 *
 *
 * History:
 *     2015 - Created by Fred Nora.
 */ 


#include <kernel.h>


extern unsigned long key_status;
extern unsigned long escape_status;
extern unsigned long tab_status;
extern unsigned long winkey_status; 
extern unsigned long ctrl_status;
extern unsigned long alt_status;
extern unsigned long shift_status;
extern unsigned long capslock_status;
extern unsigned long numlock_status;
extern unsigned long scrolllock_status;


//
// Variáveis internas.
//

//unsigned long procedureCurrentProcedure;
//...

//
// Protótipos de funções internas.
//

//Realiza testes diferentes usando o procedimento do sistema.

void procedureMakeTests (void);
void procedureLinkDriverTest (void);    // testando linkar um driver ao sistema operacional
void procedureWindowWithFocusTest (void);
void procedureGrid (void);


void xxxtestSHELLServer (void);
void xxxtestlibcSTDOUT (void);
void xxxtestlibc (void);
void procTestF6 (void);



// #wm
// Test
// Tentando mover a janela com o foco.
unsigned long ___xxx;
unsigned long ___yyy;
void test_move_window (void)
{

    struct window_d  *w;


    w = (struct window_d *) windowList[window_with_focus];
    //w = (struct window_d *) windowList[active_window];

   //___xxx = ___xxx + 5;
   //___yyy = ___yyy + 5;

   ___xxx = w->left + 5;
   ___yyy = w->top + 5;

    w->left = ___xxx;
    w->top  = ___yyy;

    save_window ( (struct window_d *) w );

    replace_window ( (struct window_d *) w, ___xxx, ___yyy);
    
    refresh_rectangle2 ( 
        (w->left +5), (w->top +5), 
        w->width, w->height, 
        (unsigned long) FRONTBUFFER_ADDRESS, 
        (unsigned long) BACKBUFFER_ADDRESS);

    show_saved_window ( (struct window_d *) w );

    //show_window_rect ( (struct window_d *) w );
    
    //coloca uma parte grande do buffer de salvamento no lfb.
    //refresh_rectangle2 ( 0, 0, 800, 600, FRONTBUFFER_ADDRESS, SavedRect->buffer_address);
    //refresh_rectangle2 ( w->left +5, w->top +5, w->width, w->height, 
      //  (unsigned long) FRONTBUFFER_ADDRESS, 
       // (unsigned long) SavedRect->buffer_address);


    //#debug
    //refresh_screen();
}

// #wm
void test_move_window_2 (void)
{
    int i=0;

    for (i=0; i<10; i++){
        test_move_window();
    }
}



/*
 * XPROC_SEND_MESSAGE
 *     Envia uma mensagem para a thread de controle da janela 
 * com o foco de entrada.
 */

int 
XPROC_SEND_MESSAGE ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    struct thread_d  *t;
    struct window_d  *w;


	//
	// ## window ##
	//

	// #importante
	// +Pegamos a janela com o foco de entrada, pois ela 
	// será um elemento da mensagem.
	// Mas enviaremos a mensagem para a fila da thread atual.

    // #todo 
    // Mensagem de erro.

    if (window_with_focus < 0){
        return -1;
    }

    // window

    w = (void *) windowList[window_with_focus];

    if ( (void *) w == NULL ){
        panic ("XPROC_SEND_MESSAGE: w\n");
    }else{
        if ( w->used != TRUE || w->magic != 1234 ){
            panic ("XPROC_SEND_MESSAGE: w validation\n");
        }

        // thread
        // Pegamos a thread de input associada com a janela 
        // que tem o foco de entrada.

        t = (void *) w->control;

        if ( (void *) t == NULL ){
            panic ("XPROC_SEND_MESSAGE: t\n");
        }

        if ( t->used != 1 || t->magic != 1234 ){
            panic ("XPROC_SEND_MESSAGE: t validation \n");
        }

		//#importante:
		//??
		
		//a janela com o foco de entrada deve receber input de teclado.
		//então a mensagem vai para a thread associada com a janela com o foco de 
		//entrada.
		//#importante: a rotina que seta o foco deverá fazer essa associação,
		//o aplicativo chama a rotina de setar o foco em uma janela, 
		//o foco será setado nessa janela e a thread atual será associada 
		//a essa janela que está recebendo o foco.
		
		//??
		//ja o input de mouse deve ir para a thread de qualquer janela.

        // Kernel single event.

        t->ke_window = window;
        t->ke_msg    = (int) msg;
        t->ke_long1  = (unsigned long) long1;
        t->ke_long2  = (unsigned long) long2;

        t->ke_newmessageFlag = TRUE;
    };

    return 0;
}

// Deprecated
void xxxtestSHELLServer (void)
{
    panic ("xxxtestSHELLServer: deprecated\n");
}

// Deprecated
void xxxtestlibcSTDOUT (void)
{
    panic ("xxxtestlibcSTDOUT: deprecated\n");
}

// Deprecated
void xxxtestlibc (void)
{
    panic ("xxxtestlibc: deprecated\n");
}

// Useful
void procTestF6 (void)
{
    debug_print ("procTestF6: Nothing\n");
}


/*
 ****************************************
 * system_procedure:
 *     Procedimento de janela da janela com o foco de entrada ... (edit box.)
 *     Procedimento de janela default.
 *     
 * OBS: Existe uma relação grande entre control menus e o procedimento do
 * do sistema. Pois o procedimento do menu deve passar boa parte das mensagens
 * para serem tratadas pelo procedimento do sistema. 
 *
 * ?? QUAL JANELA É AFETADA POR ESSE PROCEDIMENTO ??
 *    É IMPORTANTE OBSERVAR O HANDLE DE JANELA PASSADO VIA ARGUMENTO.
 *
 * OBS: ESSE PROCEDIMENTO É INVOCADO POR 'ldisc.c' NA ROTINA LINEDISCIPLINE(..)
 *      POR ENQUANTO ESTÁ PASSANDO UM HANDLE DE JANELA NULO. 
 */

// #todo
// Vamos redirecionar as mensagens aqui.
// Cada uma para seu respectivo diálogo.

// ##
// Penso que alguns aplicativos do ambiente de Setup
// ainda chamem esse procedimento quando chamam o procedimento default.

unsigned long 
system_procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ) 
{

    void *buff;

    int AltStatus=0;
    int CtrlStatus=0;
    int ShiftStatus=0;
    //...

    // Lidando com a janela com o foco de entrada.
    unsigned long left=0;
    unsigned long top=0;
    unsigned long width=0;
    unsigned long height=0;


	//janela de teste.
	struct window_d *xxxx;


	//debug!
	//printf("system_procedure: msg={%d} long1={%d}\n", msg, long1);  


	//usado no refresh_rectangle
	//unsigned long saveX, saveY;


	//Get status.
    AltStatus  = (int) get_alt_status(); 
    CtrlStatus = (int) get_ctrl_status();
    //ShiftStatus = (int) get_shift_status();
    //...


    if ( (void *) window == NULL ){
        panic ("system_procedure: window\n");
    }else{

	    // Configurando o cursor para ficar de acordo com a janela com o foco de entrda.

		// @todo:
		// Aqui deveríamos apenas pegar o ponteiro para a estrutura 
		// de cursor que pertence a janela com o foco de entrada.
	
	    //pegando as dimensões da janela com o foco de entrada.

		//left   = window->left;
	    //top    = window->top;
	    //width  = window->width;
	    //height = window->height;
	
	    //
		// simular valores aqui para teste ... como 80 25
		//
		
		//g_cursor_left   = (window->left/8);
		//g_cursor_top    = (window->top/8) + 4;   //Queremos o início da área de clente.
		
		//g_cursor_right  = g_cursor_left + (width/8);
		//g_cursor_bottom = g_cursor_top  + (height/8);

		//100
		//a linha deve ser grande.
		//A linha pode ser maior que a janela.
		//g_cursor_right  = (800/8);
		//g_cursor_bottom = (600/8);

		
		//if( g_cursor_right == 0 ){
		//	g_cursor_right = 1;
		//}
		
        //if( g_cursor_bottom == 0 ){
		//	g_cursor_bottom = 1;
		//}
		
		//cursor (0, mas com margem nova).
		//#bugbug ... isso reiniciaria o cursor a cada tecla pressionada.
		//g_cursor_x = g_cursor_left; 
		//g_cursor_y = g_cursor_top; 
	
	    //...
	};



    switch (msg){

        // Teclas de digitação.
        // Do not intercet this keys.
        case MSG_KEYDOWN:
            switch (long1){

                //case VK_RETURN: 
                //case VK_ESCAPE: 
                //case VK_TAB: 
                //case VK_BACK: 
                case VK_PAUSE: 
                default: 
                    goto done; 
                    break; 
            };
            break;

        //case MSG_KEYUP:
            //break;

        // Não usamos mais isso.
        // O kernel trata combinações de teclas em user/.
        case MSG_SYSKEYDOWN:     
            switch (long1){ 

                //case VK_F1:  
                //case VK_F2:  
                //case VK_F3:  
                //case VK_F4:
                //case VK_F5:  
                //case VK_F6:  
                //case VK_F7:  
                //case VK_F8:
                //case VK_F9:  
                //case VK_F10:  
                //case VK_F11:  
                case VK_F12:
                    break;

                // Nothing for now!
                //case VK_CAPITAL:
                //case VK_LMENU:
                //case VK_LCONTROL: 
                //case VK_LSHIFT:   
                //    break;


                // Num Lock.
                case VK_NUMLOCK:
                    if (numlock_status == 1){
                        keyboard_set_leds (LED_NUMLOCK);  
                        break;
                    }
                    break;


                // Scroll Lock.
                case VK_SCROLL:
                    if (scrolllock_status == 1){
                        keyboard_set_leds (LED_SCROLLLOCK);
                        break;
                    }
                    break;

                //case 31:
                //    break;

                default: 
                    break;
            };
        break;

        // Teclas do sistema.
        // O aplicativo pode deixar o sistema tratar esse tipo de tecla.

        case MSG_SYSKEYUP: 
            switch (long1)  
            {
                //case VK_LWIN:
                //case VK_RWIN:
                //    break;

                case VK_CONTROL_MENU:
                    break;

                default:
                    break;
            }; 
            break;

         // Deprecated
         //case MSG_DEVELOPER:
         //   break;


        default:
            break;
    };

done:
    return (unsigned long) 0;
}
 

/*
 ****************************************
 * SendMessage:
 *     Envia uma mensagem para o 
 * procedimento de janelas do sistema.
 */

unsigned long 
SendMessage ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    
    // ##
    // Sending the message to the init process.
    //__kgwm_initDialog (msg);
    
    // #todo: Maybe use this one.
    // return (unsigned long)  __kgwm_ps2kbd_procedure(window,msg,long1,long2);
    
    return (unsigned long) system_procedure(window,msg,long1,long2);
}


/*
 //#todo: Send message to and given thread.
unsigned long 
SendMessage2 (
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
unsigned long 
SendMessage2 (
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    return 0;
}
*/

/*
 //#todo: Send message to the control thread of the given process
unsigned long 
SendMessage3 (
    pid_t pid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
unsigned long 
SendMessage3 (
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    return 0;
}
*/


// Deprecated
void procedureLinkDriverTest (void)
{
    panic ("procedureLinkDriverTest: deprecated\n");
}

// Deprecated
void procedureMakeTests (void)
{
    panic ("procedureMakeTests: deprecated\n");
}

// Deprecated
void procedureWindowWithFocusTest (void)
{
    panic ("procedureWindowWithFocusTest: deprecated\n");
}

// Deprecated
void procedureGrid (void)
{
    panic ("procedureGrid: Deprecated\n");
}


//
// End.
//

