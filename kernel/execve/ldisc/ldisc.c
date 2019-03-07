/*
 * File: unb\ldisc.c
 *
 * Descrição:
 *    Esse será o gerenciador de Line Discipline.
 *    Ficará dentro do kernel base e receberá as entradas 
 * dos dispositivos de caractere e enviará para as filas apropriadas.
 *    Por enquanto os scancodes de teclado são tratados e enviados 
 * para a fila de mensagem da janela apropriada. Principalmente a janela 
 * com o foco de entrada. 
 *
 */


#include <kernel.h>


/*
 * LINE_DISCIPLINE
 *     Uma disciplina de linha genérica, para mensagens de 
 * dispositivos de entrada diferentes.
 */

int 
LINE_DISCIPLINE ( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 )
{

	struct thread_d *t;		
	struct window_d *w;  
	
	//
	// ## window ##
	//
	
	// #importante
    // +Pegamos a janela com o foco de entrada, pois ela 
    // será um elemento da mensagem.	
	// Mas enviaremos a mensagem para a fila da thread atual.

	//#todo mensagem de erro.	
	
	if (window_with_focus < 0)
		return -1;
	
	w = (void *) windowList[window_with_focus];
	
	if ( (void *) w == NULL )
	{
		printf ("LINE_DISCIPLINE: w");
		die();
		
	}else{
		
		if ( w->used != 1 || w->magic != 1234 )
		{
			printf("LINE_DISCIPLINE: w validation");
			die();
		}		

		//
		// ## thread ##
		//
		
		//#importante:
		//Pegamos a thRead de input associada com a janela 
		//que tem o foco de entrada.
		
		t = (void *) w->control;
		
		if ( (void *) t == NULL )
		{
		    printf("LINE_DISCIPLINE: t");
		    die();			
		}
		
		if ( t->used != 1 || t->magic != 1234 )
		{
			printf("LINE_DISCIPLINE: t validation");
			die();
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
		
		t->window = window;
		t->msg = (int) msg;
		t->long1 = long1;
		t->long2 = long2;
		
		t->newmessageFlag = 1;
		
		
        //
		// system procedure
		//
		
		system_procedure ( window, (int) msg, 
		    (unsigned long) long1, (unsigned long) long2 );
		
	};	
 	
    return 0;	
}


/*
 ***************
 * KEYBOARD_LINE_DISCIPLINE
 *     Uma disciplina de linha apenas para as digitações de teclado.
 * Funciona como um filtro.
 * Obs: Essa é a rotina principal desse arquivo, todo o resto poderá 
 * encontrar um lugar melhor.
 */
	
int KEYBOARD_LINE_DISCIPLINE ( unsigned char SC ){
	
	struct thread_d *t;		
	struct window_d *w;  	
	
    //
    // Step 0 - Declarações de variáveis.
    //

    //Variáveis para tecla digitada.
    unsigned char scancode;
    unsigned char key;         //Tecla (uma parte do scancode).  
    unsigned long mensagem;    //arg2.	
    unsigned long ch;          //arg3 - (O caractere convertido para ascii).
    unsigned long status;      //arg4.  

    //
    // Step1 - Pegar o scancode.
    //

    //O driver pegou o scancode e passou para a disciplina de linha 
    //através de parâmetro.	
	
	scancode = SC;
	

	//Obs: Observe que daqui pra frente todas as rotinas poderiam estar
	//     em user mode.


	//Debug stuff.
    //Show the scancode if the flag is enabled.	
	if (scStatus == 1){
	    printf("{%d,%x}\n",scancode,scancode);
	};
	
	
    //
    // Step 2 - Tratar as mensagens.
    //

    //Se a tecla for (liberada).
	//Dá '0' se o bit de paridade for '0'.
    if( (scancode & LDISC_KEY_RELEASED) == 0 )
	{
	    key = scancode;
		key &= LDISC_KEY_MASK;    //Desativando o bit de paridade caso esteja ligado.

		//Configurando se é do sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		
		switch (key)
		{
			//Os primeiros 'case' é quando libera tecla do sistema.
			//O case 'default' é pra quando libera tecla que não é do sistema.
			
			//left Shift liberado.
			case VK_LSHIFT:
				shift_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;

			//Left Control liberado.			
			case VK_LCONTROL:
				ctrl_status = 0;
				mensagem = MSG_SYSKEYUP;
				break;

			//left Winkey liberada.
			case VK_LWIN:
			    winkey_status = 0;
                mensagem = MSG_SYSKEYUP;
				break;

			//Left Alt liberado.
            case VK_LMENU:
				alt_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;				
			
			//right winkey liberada.
			case VK_RWIN:
			    winkey_status = 0;
                mensagem = MSG_SYSKEYUP;
				break;

			//control menu.
			case VK_CONTROL_MENU:
			    //controlmenu_status = 0; //@todo
			    mensagem = MSG_SYSKEYUP;
			    break;

            //right control liberada.
			case VK_RCONTROL:
				ctrl_status = 0;
				mensagem = MSG_SYSKEYUP;
				break;
				
			//right Shift liberado.
			case VK_RSHIFT:
				shift_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;

			//Funções liberadas.
            case VK_F1:
            case VK_F2:
            case VK_F3:
            case VK_F4:
            case VK_F5:
            case VK_F6:
            case VK_F7:
            case VK_F8:
            case VK_F9:
            case VK_F10:
            case VK_F11:
            case VK_F12:
			    mensagem = MSG_SYSKEYUP;
			    break;


			//...
				
			//A tecla liberada NÃO é do sistema.
			default:
			    mensagem = MSG_KEYUP;
				break;
		};

		//Selecionando o char para os casos de tecla liberada.

        //Analiza: Se for do sistema usa o mapa de caracteres apropriado. 
   		if(mensagem == MSG_SYSKEYUP)
		{
			//Normal.
			ch = map_abnt2[key];
		};

		//Analiza: Se for tecla normal, pega o mapa de caracteres apropriado.
		if(mensagem == MSG_KEYUP)
		{
		    //checar os mudificadores para maiúscula.
		    //if(shift_status == 1 || capslock_status == 1)
			//{	
			//    ch = shift_abnt2[key];	
			//	goto done;
			//};
			
			//minúscula
			//Nenhuma tecla de modificação ligada.
			ch = map_abnt2[key];
			goto done;
			
            //Nothing.
		};
        //Nothing.
		goto done;
	};
	
	// * Tecla (pressionada) ...........	
	if( (scancode & LDISC_KEY_RELEASED) != 0 )
	{ 
		key = scancode;
		key &= LDISC_KEY_MASK; //Desativando o bit de paridade caso esteja ligado.

		//O Último bit é zero para key press.
		//Checando se é a tecla pressionada é o sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		
		switch (key)
		{
			//back space será tratado como tecla normal
			
			//@todo: tab,
            //?? tab será tratado como tecla normal por enquanto.
			
			//caps lock keydown
			case VK_CAPITAL:
			    //muda o status do capslock não importa o anterior.
				if (capslock_status == 0)
				{ 
				    capslock_status = 1; 
					mensagem = MSG_SYSKEYDOWN; 
					break; 
				};
				if (capslock_status == 1)
				{ 
				    capslock_status = 0; 
					mensagem = MSG_SYSKEYDOWN; 
					break; 
				};
				break; 

			//Left shift pressionada.
			case VK_LSHIFT:
			//case KEY_SHIFT:
				shift_status = 1;
				mensagem = MSG_SYSKEYDOWN;
			    break;

			//left control pressionada.
			case VK_LCONTROL:
			//case KEY_CTRL:
				ctrl_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;

			//Left Winkey pressionada.
			case VK_LWIN:
			    winkey_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;

            //left Alt pressionada.
            case VK_LMENU:
				alt_status = 1;
				mensagem = MSG_SYSKEYDOWN;
			    break;

			//@todo alt gr.	

			//Right Winkey pressionada.
			case VK_RWIN:
			    winkey_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;
			
            //@todo: Control menu.
            
			//Right control pressionada.
			case VK_RCONTROL:
				ctrl_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;

			//Right shift pressionada.
			case VK_RSHIFT:
				shift_status = 1;
				mensagem = MSG_SYSKEYDOWN;
			    break;


            case VK_F1:
            case VK_F2:
            case VK_F3:
            case VK_F4:
            case VK_F5:
            case VK_F6:
            case VK_F7:
            case VK_F8:
            case VK_F9:
            case VK_F10:
            case VK_F11:
            case VK_F12:
			    mensagem = MSG_SYSKEYDOWN;
			    break;


			//Num Lock.	
		    case VK_NUMLOCK:
			    //muda o status do numlock não importa o anterior.
				if(numlock_status == 0){
		            numlock_status = 1;
					mensagem = MSG_SYSKEYDOWN;
					break;
				};
				if(numlock_status == 1){ 
				    numlock_status = 0;
                    mensagem = MSG_SYSKEYDOWN; 					
					break; 
				};
			    break;
				
			//Scroll Lock.	
		    case VK_SCROLL:
			    //muda o status do numlock não importa o anterior.
				if(scrolllock_status == 0){
		            scrolllock_status = 1;
					mensagem = MSG_SYSKEYDOWN;
					break;
				};
				if(scrolllock_status == 1){ 
				    scrolllock_status = 0;
                    mensagem = MSG_SYSKEYDOWN; 					
					break; 
				};
			    break;

            //...

			//A tecla pressionada não é do sistema.
			default:
			    //printf("keyboard debug: default: MSG_KEYDOWN\n");
			    mensagem = MSG_KEYDOWN;
				break;
		};

		//uma tecla do sistema foi pressionada.
		if (mensagem == MSG_SYSKEYDOWN)
		{
			ch = map_abnt2[key];
            goto done;
		};

		//uma tecla normal foi pressionada.
		//mensagem de digitação.		
		//Se o shift ou o capslock estiverem acionados, ela vira maiúscula.
		//#bugbug: Como o shift  não funciona ainda, então vamos usar 
		//só o capslock como tecla de modificação da digitação por enquanto.
		if (mensagem == MSG_KEYDOWN)
		{
            //maiúsculas.			
			if (capslock_status == 1)
			{
			    ch = shift_abnt2[key];
			    goto done;
			}

			//minúsculas.
			if (capslock_status == 0)
			{
		        ch = map_abnt2[key];
			    goto done;
			};
			
            //Nothing.
		};
		
		//Nothing.
		goto done;
	};//fim do else

    //Nothing.
	
	// Para finalizar, vamos enviar a mensagem para fila certa.
done:

	/*
	 * Debug:
     *     No caso de modo texto.
	 *
	 * Coloca o scancode na tela
     * set_up_cursor(0,4);
	 * printf("       "); 	
     * set_up_cursor(0,4);
	 * printf("%d ",(unsigned char) (key & 0xff) );
     * Coloca o caractere na tela
	 * screen[76] = (char) ch;
	 * screen[77] = (char) 0x09;  //azul no preto
	 */


	//Debug:
	//Canto direito da primeira linha.
	//screen[76] = (char) ch;
	//screen[77] = (char) 0x09;    //Azul no preto.

	//
	// Control + Alt + Del.
	//

		//Opções:
		//@todo: Chamar a interface do sistema para reboot.
		//@todo: Opção chamar utilitário para gerenciador de tarefas.
		//@todo: Abre um desktop para operações com usuário, senha, logoff, gerenciador de tarefas.

		//Chamando o módulo /sm diretamente.
		//mas não é o driver de teclado que deve chamar o reboot.
		//o driver de teclado deve enviar o comando para o console, /sm,
		//e o console chama a rotina de reboot do teclado.
		//Uma mensagem de reboot pode ser enviada para o procedimento do sistema.
		//Pois o teclado envia mensagens e não trata as mensagens.
	
	    //Um driver não deve chamar rotinas de interface. como as rotians de serviço.	
		//A intenção é que essa mensagem chegue no procedimento do sistema.
		//Porem o sistema tambem deve saber quem está enviando esse pedido.@todo.
		//@todo: podemos O reboot pode ser feito através de um utilitário em user mode.
			
	
		//Uma opção aqui, é enviar para o aplicativo uma mensagem de reboot.
		//como o aplicativo não trata esse tipo de mensagem ele apenas reecaminha 
		//para o procedimentod e janelas do sistema.
	
		
		//system_procedure ...
		// @todo: Chamar o aplicativo REBOOT.BIN.
	
	if ( (ctrl_status == 1) && 
	     (alt_status == 1) && 
		 (ch == KEY_DELETE) )
	{
		gde_services ( SYS_REBOOT, 0, 0, 0 );
	}

	
	// Nesse momento temos duas opções:
	// Devemos saber se a janela com o foco de entrada é um terminal ou não ...
	// se ela for um terminal chamaremos o porcedimento de janelas de terminal 
	// se ela não for um terminal chamaremos o procedimento de janela de edit box. 
	// que é o procedimento de janela do sistema.
	// *IMPORTANTE: ENQUANTO O PROCEDIMENTO DE JANELA DO SISTEMA TIVER ATIVO,
	// MUITOS COMANDOS NÃO VÃO FUNCIONAR ATE QUE SAIAMOS DO MODO TERMINAL.
	
	// *importante:
	// Passamos a mensagem de teclado para o procedimento de janela do sistema.
	// que deverá passar chamar o procedimento de janela da janela com o focod eentrada.
		
	// *importante:
	// Quem é o 'first responder' para evento de teclado.
	// A janela com o foco de entrada é o first responder para 
	// eventos de teclado, mas não para todo tipo de envento.		

	
	// ## window ##
	
	// #importante
	// +Pegamos a janela com o foco de entrada, pois ela 
	// será um elemento da mensagem.	
	// Mas enviaremos a mensagem para a fila da thread atual.
	

	w = (void *) windowList[window_with_focus];
	
	if ( (void *) w == NULL )
	{
		printf("KEYBOARD_LINE_DISCIPLINE: w");
		die();
		
	}else{
			
		if ( w->used != 1 || w->magic != 1234 )
		{
			printf("KEYBOARD_LINE_DISCIPLINE: w validation");
			die();
		}		

		// ## thread ##
		
		//#importante:
		//Pegamos a thRead de input associada com a janela 
		//que tem o foco de entrada.
		
		t = (void *) w->control;
		
		if ( (void *) t == NULL )
		{
		    printf("KEYBOARD_LINE_DISCIPLINE: t");
		    die();			
		}
		
		if ( t->used != 1 || t->magic != 1234 )
		{
			printf("KEYBOARD_LINE_DISCIPLINE: t validation");
			die();
		}        
			
		//#importante:
		//??
		
		//a janela com o foco de entrada deve receber input de teclado.
		//então a mensagem vai para a thrad associada com a janela com o foco de 
		//entrada.
		//#importante: a rotina que seta o foco deverá fazer essa associação,
		//o aplicativo chama a rotina de setar o foco em uma janela, 
		//o foco será setado nessa janela e a thread atual será associada 
		//a essa janela que está recebendo o foco.
		
		//??
		//ja o input de mouse deve ir para a thread de qualquer janela.
		
		t->window = w;
		t->msg = (int) mensagem;
		t->long1 = ch;
		t->long2 = ch;
		
		t->newmessageFlag = 1;
		
		// Teclas para teste.
		// F5 F6 F7 F8
		// Teclas usadas exclusivamente pelo 
		// procedimento de janelas do sistema.
		// Os aplicativos não devem usar essas teclas por enquanto.
		// Então Essas teclas funcionarão mesmo que os aplicativos estejam com problema.
		
	    switch (mensagem)
		{
			case MSG_SYSKEYDOWN:  
			    switch (ch)
				{
					// Used on system procedure for tests.
					case VK_F5:	
					case VK_F6:	
					case VK_F7:	
					case VK_F8:	
		               
						system_procedure (  w, (int) mensagem, 
					        (unsigned long) ch, (unsigned long) ch );					
					    
						break;
				}
			break;
		};
	};	
 
    return (int) 0;
}


 
// Mouse #todo
// A entrada é um ponteiro para um buffer que contenha os 
// 3 chars usados pelo mouse.

int MOUSE_LINE_DISCIPLINE ( void *buffer ) {
	
	if ( (void *) buffer == NULL )
	    return (int) -1;
    
	unsigned char *chars = (unsigned char *) buffer;

	char char0 = (char) chars[0];
	char char1 = (char) chars[1];
	char char2 = (char) chars[2];
	char char3 = (char) chars[3];
	//...
	
	//
	// #todo
	//
	
    return (int) -1;   
}


//ldisc
//inicializando a fila de mensagens do sistema
//com ponteiros para estruturas de mensagens ...
//es estruturas serão reutilizáveis.
void initialize_system_message_queue (){
	
	struct message_d *m;
	
	int i;
	
	for ( i=0; i<SYSTEM_MESSAGE_QUEUE_MAX; i++ )
	{
		
		m = (void *) malloc ( sizeof(struct message_d) );
		
		if ( (void *) m == NULL )
		{
			printf("unblocked-ldisc-initialize_system_message_queue:");
			die();
		}else{
			
			m->objectType = ObjectTypeMessage;
			m->objectClass = ObjectClassKernelObjects;
		    m->used = 1;
			m->magic = 1234;
			m->empty = 1;
            system_message_queue[i] = (unsigned long) m;		
		}; 
	};
	
	system_message_write = 0;
	system_message_read = 0;
};







//
// End.
//

