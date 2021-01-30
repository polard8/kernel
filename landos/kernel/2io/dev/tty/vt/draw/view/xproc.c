/*
 * File: xproc.c
 *
 *     System Procedure.
 *
 * A qui ficarão todos os diálogos para conversar 
 * com os módulos do kernel base.
 * Eles serão chamados de 'dialog' ou 'procedure'. 
 *
 * O PROCEDIMENTO NUNCA DEVE SER TROCADO, SEMPRE SERÁ O PROCEDIMENTO DO SISTEMA
 * QUANDO HOUVER UMA MENSAGEM ENVIADA PARA OUTRO PROCEDIMENTO, A MENSAGEM DEVE SER
 * COLOCADA NA ESTRUTURA DA JANELA ATIVA E AVISAR A THREAD E O PROCESSO SOBRE A MENSAGEM.
 * A THREAD PRINCIPAL DO PROGRAMA PEGARÁ AMENSAGEM E PASARA PARA O SEU PROCEDIMENTO.
 *
 * Obs: As teclas de F1 à F5 poderiam testar rotinas referentes às camadas
 *      respectivas. F1 testa rotinas de K1 e asem por diante.
 *      As rotinas de K0 seriam testadas de outra forma.
 *
 * Descrição:
 *     Procedimento de janela default, em kernel mode.
 *     Trata mensagens de sistema, como WIN KEY.
 *     Todas as tarefas são tratadas por esse procedimento padrão, 
 *     ao menos que inicializem seu próprio procedimento, ou um mix das 
 * duas coisas.
 *
 * OBS: 
 *     procedure.c está em hal, porque recebe intervenções de hardware
 * não importando a arquitetura.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - 2018 New services.
 *     //...
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




//tentando mover a janela com o foco.
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



// ??
void xxxtestSHELLServer (void)
{
    debug_print ("xxxtestSHELLServer: deprecated\n");
}


// #IMPORTANTE
// REFRESH STDOUT
void xxxtestlibcSTDOUT (void)
{
    debug_print ("xxxtestlibcSTDOUT: deprecated\n");
}



//=========================================
//f5
//para testar recursos da libc.
void xxxtestlibc (void)
{
    debug_print ("xxxtestlibc: deprecated\n");
}
//====================================



// Write on lba 559
// ?? Testando rotina de write sector.
void procTestF6 (void)
{
    debug_print ("procTestF6: deprecated\n");
    return;
    
    /*
    void *address = (void *) kmalloc (1024);

    unsigned char *buffer = (unsigned char *) address;


    // write
    pio_rw_sector ( 
        (unsigned long) buffer, 
        (unsigned long) 559,    // ?? What is this lba ??? 
        (int) 0x30, 
        (int) g_current_ide_channel, 
        (int) g_current_ide_device );

	// #debug
	// printf("Signature: [ %x %x ] \n" , buffer[0x1FE], buffer[0x1FF] ); 
    */
}




/*
 ********************************************************************
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

unsigned long 
system_procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ) 
{

	// #todo: 
	// importante:
	//        Não precisa dar refresh_screen para todos os casos.
	//        Cada caso é diferente ... 
	//        ?? Quem deve chamar esse refresh dos elentos gráficos ??
	//        O aplicativo ?? acionando a flag através de ShowWindow por exemplo??


	//debug!
	//printf("system_procedure: msg={%d} long1={%d}\n", msg, long1);  


    void *buff;

    int AltStatus=0;
    int CtrlStatus=0;
    int ShiftStatus=0;
    //...


	//usado no refresh_rectangle
	//unsigned long saveX, saveY;


	//Get status.
    AltStatus  = (int) get_alt_status(); 
    CtrlStatus = (int) get_ctrl_status();
    //ShiftStatus = (int) get_shift_status();
    //...

	// Lidando com a janela com o foco de entrada.
    unsigned long left=0;
    unsigned long top=0;
    unsigned long width=0;
    unsigned long height=0;


	//janela de teste.
	struct window_d *xxxx;
	
	//struct window_d *w;
	
	
	// #debug
	//return 0;
	

	//
	// Checamos se a janela com o focod e entrada é válida.
	//
	
	//#bugbug isso está errado ... devemos pegar a janela passada por argumento 
	//poi o line discipline selecionou a janela com o foco de entrada.
	
	//w = (void *) windowList[window_with_focus];
	
	// Window With Focus !
	//window é a janela com o foco de entrada, obtita pelo ldisc.c 
	//e passada via argumento.

    if ( (void *) window == NULL ){
        panic ("xproc-system_procedure: window");

    }else{

	    //
	    // Configurando o cursor para ficar de acordo com a janela com o foco de entrda.
	    //


		//
		// @todo:
		// Aqui deveríamos apenas pegar o ponteiro para a estrutura 
		// de cursor que pertence a janela com o foco de entrada.
		//
	
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
	
	


    //
    // ================= CUT HERE =============
    //

	// *importante:
	// Desejamos que as teclas de controle sejam tratadas por esse 
	// procedimento mesmo que a janela seja do tipo terminal ...
	// pois as teclas de comtrole permite trocarmos a jenala com 
	// o foco de entrada sem fecharmos o terminal.

 
    switch (msg){

        // Teclas de digitação.
        // O procedimento de janelas do sistema 
        // normalmente ignora as teclas de digitação.

        case MSG_KEYDOWN:
            switch (long1)
            {

				// O procedimento de janelas do sistema 
				// normalmente ignora as teclas de digitação.
                case VK_RETURN: goto done; break;

				// O procedimento de janelas do sistema 
				// normalmente ignora as teclas de digitação.
                case VK_ESCAPE: goto done; break;


				//Obs: 
				// Não deve ser preocupação do desenvolvedor de aplicação 
				//incrementar o cursor quando pressiona a seta.
				//por isso vou tratá las aqui.
				
				//# bugbug problemas no 'i'.
				
				//case VK_RIGHT:	
				//    g_cursor_x++;
				//	break;
				
				//case VK_LEFT:
				//    g_cursor_x--;
				//    break;
					
				//case VK_DOWN:
				//    g_cursor_y++;
				//    break;
					
				//case VK_UP:
				//    g_cursor_y--;
				//	break;


                case VK_TAB: 
                case VK_BACK: 
                case VK_PAUSE: 
                    goto done; 
                    break;

				// O procedimento de janelas do sistema 
				// normalmente ignora as teclas de digitação.
                default: 
                    goto done; 
                    break; 
            };
            break;


        // Teclas de digitação.
        // O procedimento de janelas do sistema 
        // normalmente ignora as teclas de digitação.

        //case MSG_KEYUP:
            //break;


        // Teclas do sistema.
        // O aplicativo pode deixar o sistema tratar esse tipo de tecla.
        // F1~F4  (usadas pelos aplicativos)
        // F5~F8  (* usados pelo sistema nessa fase do desenvolvimento)
        // F9~F12 (usadas pelos aplicativos)

        case MSG_SYSKEYDOWN:     
            switch (long1)
            { 

                // Usadas pelos aplicativos.
                case VK_F1:  case VK_F2:  case VK_F3:  case VK_F4:
                    break;

                // F1, F2, F3, F4
                // Os testes que estavam aqui foram pra outro lugar.
                // __local_ps2kbd_procedure()
                // See: dd/ws/ps2kbd.c 
                case VK_F5:  case VK_F6:  case VK_F7:  case VK_F8:
                    break;

                // Usadas pelos aplicativos.
                case VK_F9:  case VK_F10:  case VK_F11:  case VK_F12:
                    break;


                // Nothing for now!
                case VK_CAPITAL:
                case VK_LMENU:
                case VK_LCONTROL: 
                case VK_LSHIFT:   
                    break;


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

                // #test
                // mouse up
                case 31:
                    switch (long1)
                    {
                        // Button 1.
                        case 1:
                            if ( window == gui->screen ){
                                printf ("system_pocedure: Clicking on root screen\n");
                                refresh_screen ();
                            }
                            break;
                    };
                    break;
                
                default: 
                    break;
            };
        break;



        // Teclas do sistema.
        // O aplicativo pode deixar o sistema tratar esse tipo de tecla.

        case MSG_SYSKEYUP: 
            switch (long1)  
            {
                case VK_LWIN:
                case VK_RWIN:
                    if ( winkey_status == 0 )
                    {
                        //printf ("winkey\n");
                    }
                    break;

                // ??
                case VK_CONTROL_MENU:
                    break;

                default:
                    break;
            }; 
            break;



		// Dialogo especial:
		// Serve para funções provisórias usadas pelo desenvolvedor 
		// do sistema operacional.
        case MSG_DEVELOPER:
            switch(long1)
            {
				// Fechar message box em kernel mode.
                case 1:  CloseWindow (window);  break;
                
                //...
                
                default:
                    break;
            };
            break;

        //
        // Mouse.
        //

        // Vamos tratar aqui vários eventos de mouse.
        case 30:
        case 31:
            return (unsigned long) kgwm_mouse_dialog ( 
                                       window, msg, long1, long2 );
            break;

        default:
            break;
    };

done:
    return (unsigned long) 0;
}
 


/*
 ***************************************************
 * SendMessage:
 *     Envia uma mensagem para o procedimento de janelas do sistema.
 *     Ou seja do x-server. Em x/xproc.c
 */

unsigned long 
SendMessage ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    return (unsigned long) system_procedure ( window, 
                               msg, long1, long2 );
}


/*
 * procedureLinkDriverTest:
 *     Testando linkar um driver ao sistema operacional.
 *     Obs: Essa rotina é um tipo de callout. Foi implementada usando um
 * iret, mas poderia bem ser um jmp.
 * Obs: Isse test  funcionou bem, implementar essa rotina definitivamente.
 */

// #cuidado
// rever isso.

void procedureLinkDriverTest (void)
{
	//
	// Saltando para a thread idle:
	//
	
	//
	// Obs: Estamos forçando. estamos atropelando o escalonamento
	// e thread e saltando para a thread idle para testar a nossa tentativa
	// de inicializar o processo idle tambem com driver, alem de ser um processo cliente.
	//
	
	//
	// estamos usando o mesmo método que saltamos para a thread idle pela primeira vez.
	//
	
	
	//
	// @todo: Poderiamos ter aqui opções de filtro, que faria a rotina falhar e retornar 
	// no caso de reprovar alguma coisa.
	//
	//goto: failReturn;


    printf("iret\n");

    asm volatile (" cli \n"   
                  " mov $0x23, %ax  \n" 
                  " mov %ax, %ds  \n"
                  " mov %ax, %es  \n"
                  " mov %ax, %fs  \n"
                  " mov %ax, %gs  \n"
                  " pushl $0x23            \n"    //ss.
                  " movl $0x0044FFF0, %eax \n"
                  " pushl %eax             \n"    //esp.
                  " pushl $0x3200          \n"    //eflags.
                  " pushl $0x1B            \n"    //cs.
                  " pushl $0x00401000      \n"    //eip. 

                  " mov $1234, %edx  \n"          //Obs: Acrescentamos essa flag.

                  " iret \n" );

    return;
}



// #cancelada
// Deletar isso. 
void procedureMakeTests (void)
{
    debug_print ("procedureMakeTests: Deprecated\n");
    // Nothing.
}


// ??
// Rever isso.
void procedureWindowWithFocusTest (void)
{
    debug_print ("procedureWindowWithFocusTest: Deprecated\n");
}



// ??
// #todo: deletar!

void procedureGrid (void)
{
    panic ("xproc-procedureGrid: Deprecated!");
}


//
// End.
//

