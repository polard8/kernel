/*
 * File: execve/sci/gde_serv.c 
 *
 *       (SCI) = SYSTEM CALL INTERFACE
 *
 * Esse é o arquivo principal da sci.
 *
 *       GERENCIA OS SERVIÇOS OFERECIDOS PELAS INTERFACES /sys.h E /system.h.   
 *
 * Obs: Todas as rotinas chmadas por esse módulo devem vir apenas das interfaces
 * /sys.h e /system.h.
 *
 *
 * In this file:
 *   + services (main function)
 *   + servicesPutChar
 *   + services_send_message_to_thread
 *   + serviceCreateWindow
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     2017 - Revision.
 *     //...
 */


#include <kernel.h>


//
// Constantes internas.
//

//#BUGBUG
// Esse máximo de serviços para a interrupção 200 não existirá mais.
// um número grande de serviços poderá ser atendido por essa interupção,
// esses 255 serviços são os serviços que serão atendidos em kernel mode
// aqui no kernel base.
#define SERVICE_NUMBER_MAX 255


//
// Variáveis internas.
//

//int servicesStatus;
//int servicesError;
//...

// Create Window support.
int cwFlag;                //flag (alerta que os argumentos estão disponíveis)
unsigned long cwArg1;      //WindowType
unsigned long cwArg2;      //WindowStatus
unsigned long cwArg3;      //WindowView
char *cwArg4;              //WindowName
unsigned long cwArg5;      //WindowX
unsigned long cwArg6;      //WindowY
unsigned long cwArg7;      //WindowWidth
unsigned long cwArg8;      //WindowHeight
struct window_d * cwArg9;  //gui->screen Parent window
int  cwArg10;               // desktopID 
unsigned long cwArg11;     // WindowClientAreaColor
unsigned long cwArg12;     // WindowColor




/*
 * gde_services:
 *     Rotina que atende os pedidos feitos pelos aplicativos em user mode 
 *     via int 200. Ou ainda o kernel pode chamar essa rotina diretamente.
 *     São vários serviços.
 *
 *
 * Obs: 
 * TODOS OS SERVIÇOS DESSA ROTINA PODEM CHAMAR ROTINAS DE CLASSES 'system.x.x'.
 *
 * @todo: 
 *    Pode haver algum tipo de autorização para essa rotina.
 *    Ou ainda, autorização por grupo de serviços. Sendo os serviços
 *    de i/o os de maior privilégio.
 *
 *    +Identificar o processo que fez a chamada e i/o e
 *    configurar a variável que identifica esse processo.
 *    'caller_process_id' É uma variávem encapsulada em process.c
 *    'set_caller_process_id(int pid)' configura a variável.
 *
 *    Uma chamada como OpenDevice pode liberar o acesso
 *    para um determinado processo e CloseDevice cancela o acesso.  
 * 
 *    @todo: O Nome da função, para pertencer à essa pasta, deveria ser:
 *           servicesSystemServices(....).
 *
 *@todo: *importante: Essa rotina deve identificar quem está chamando, PID TID.
 *
 *
 * *IMPORTANTE:
 *  DEPENDEND DO NÚMERO DO SERVIÇO ELE PODERÁ SER TRATADO EM OUTRO ARQUIVO
 *  E NÃO NO KERNEL BASE.
 */

void *gde_services ( unsigned long number, 
                     unsigned long arg2, 
                 unsigned long arg3, 
                 unsigned long arg4 )
{
	//
	// Declarações.
	//
	
    //Args. (strings)
	unsigned char *stringZ = (unsigned char *) arg2;
    unsigned char *stringZZ = (unsigned char *) arg3;	
	
	unsigned long *a2 = (unsigned long*) arg2;
	unsigned long *a3 = (unsigned long*) arg3;
	unsigned long *a4 = (unsigned long*) arg4;
	

	char *aa2 = (char *) arg2;
	char *aa3 = (char *) arg3;
	char *aa4 = (char *) arg4;

	
    char *tokenList[8];
	
	*tokenList = (char*) arg3;
	
	//Char and string support.
	char *argChar;
	unsigned char* argString;

	//Retorno.
	void* Ret;
	
	//Function(CreateWindow)
	//arg2 =Type
	//arg3=Status
	//arg4=Name
	
	//Window.
	unsigned long WindowType;      //Tipo de janela.
	unsigned long WindowStatus;    //Status, ativa ou não.
	unsigned long WindowRect;
	unsigned long WindowView;      //Min, max.
	char *WindowName;            
	
	//
	// Window stuffs:
	//
	
	int ActiveWindow;          //Current id.
	
	struct window_d *hWnd;
	//struct window_d *cWnd;     //Current window.
	//struct window_d *aWnd;     //Active Window. 	
	struct window_d *focusWnd;   //Janela com foco de entrada.
    struct window_d *NewWindow;  //Ponteiro para a janela criada pelo serviço.
	
	
	//void* kHWND;
	void* kMSG;
	//void* kLONG1;
	//void* kLONG2;
	//...
	
	//Para identificarmos qual processo e qual thread está chamando.
	//struct window_d *Thread;
	struct process_d *p;
	struct thread_d *t;
	
	
	//
	// Setup.
	//
	
	//Window.
	hWnd = (void*) arg2;


	// #todo: 
	// Antes de utililizar as dimensões da área de trabalho
	// vamos atribuir valores negligenciados para as dimensões.
	
	//Inicializando dimensões.
	//Obs: Emulando telas de celulares.
	// 320x480.
	// Terminal abaixo dos diálogos.
	unsigned long WindowX = (2*(800/20));  //100;   >          
	unsigned long WindowWidth  = 320;               
	
    unsigned long WindowY = (2*(600/20)); //100;   V                
    unsigned long WindowHeight = 480;  
	
	unsigned long WindowColor = COLOR_WINDOW;  
	unsigned long WindowClientAreaColor = COLOR_WINDOW;  

    struct rect_d *r;	
	
	
	// ## message support ##
	
	//o endereço do array passado pelo aplicativo
	//usaremos para enviar uma mensagem com 4 elementos.
	unsigned long *message_address = (unsigned long *) arg2;
	
	unsigned char SC;
	//struct window_d *wFocus;
	
	int desktopID;
	
	
	// *Importante: 
	// Checando se o esquema de cores está funcionando.
	
	if ( (void *) CurrentColorScheme == NULL )
	{
		printf("StatusBar: CurrentColorScheme");
		die();
	
	}else{
		
		if ( CurrentColorScheme->used != 1 || 
		     CurrentColorScheme->magic != 1234 )
		{
		    printf("StatusBar: CurrentColorScheme validation");
		    die();		
		};
		//Nothing.
	};	
	
	//Configurando cores.
	WindowColor = CurrentColorScheme->elements[csiWindowBackground];  
	WindowClientAreaColor = CurrentColorScheme->elements[csiWindow]; 	
	
	 
	desktopID = (int) get_current_desktop_id();		
	
	
	// #bug
	// Se a área de trabalho for válida, usaremos suas dimensões, 
	// caso não seja, temos um problema.
	
	if (gui->main == NULL)
	{
		panic ("services: gui->main");
	};		
	
	
	//
	// ## Create Window ##
	//
	
	// Serviço especial. Antes dos outros.
	if ( number == SYS_118 )
	{
	    return (void *) serviceCreateWindow ( (char *)  arg2 );
	}

	
	//#bugbug: estamos revendo isso, veja sci/gde
	// 7000 ~ 7999
	// Suporte as chamadas de socket da libc.
	// crts/klibc/socket.c
	
	/* #suspenso vamos mudar esse numeros e atender aqui mesmo
	if ( number >= 7000 && number < 8000 )
	{
		return (void *) socket_services ( (unsigned long) number, (unsigned long) arg2, 
						    (unsigned long) arg3, (unsigned long) arg4 );
	};
    */
	

	
	//
	// ## Switch ##
	//
	
	//Number.
	switch (number)
	{
	    //0 - Null, O processo pode ser malicioso.
	    case SYS_NULL: 
	        return NULL;
			break; 	   
		
		//Disco: 1,2,3,4
		
		//1 (i/o) Essa rotina pode ser usada por um driver em user mode.
		case SYS_READ_LBA: 
			sys_my_read_hd_sector ( (unsigned long) arg2 , (unsigned long) arg3, 0 , 0 ); 
			break;
			
		//2 (i/o) Essa rotina pode ser usada por um driver em user mode.
		case SYS_WRITE_LBA: 
			sys_my_write_hd_sector ( (unsigned long) arg2 , (unsigned long) arg3, 0 , 0 ); 
		    break;

		//3 fopen (i/o)
		//Carregar um arquivo, dado o nome e o endereço.
		//#obs: chamar rotinas de interface sys_ simplificam 
        //o atendimento às system calls.	
		// A funçao esta' em fs/fs.c	
		//IN: name. address
		case SYS_READ_FILE:
			
			//funciona, nao mexer nesse
		    //return (void *) sys_read_file ( (unsigned long) a2, (unsigned long) arg3 );
			
			//#importante: estamos usando esse.
			//testando novos recursos,
			return (void *) sys_read_file2 ( (unsigned long) a2, (unsigned long) arg3 );
				
			break;


		//4 (i/o)
		case SYS_WRITE_FILE:
		    taskswitch_lock();
	        scheduler_lock();	
		    
			sys_fsSaveFile ( (char *) message_address[0],         //name
			             (unsigned long) message_address[1],  //3, //@todo: size in sectors 
						 (unsigned long) message_address[2],  //255, //@todo: size in bytes
						 (char *) message_address[3],         //arg3,//address
						 (char) message_address[4] );         //,arg4 ); //flag
						
			scheduler_unlock();
	        taskswitch_unlock();
		    break;
			
		//Gráficos:5,6,7,8,9,10,11.
		
		//5 Vertical Sync.(Não sei se é necessário isso via interrupção.); 
        case SYS_VSYNC:
		    sys_vsync();       		
			break;
			
		// 6 - Put pixel. 
        // Coloca um pixel no backbuffer.
        // Isso pode ser usado por um servidor. 
        // cor, x, y, 0.		
        case SYS_BUFFER_PUTPIXEL:		
            sys_backbuffer_putpixel ( (unsigned long) a2, 
			    (unsigned long) a3, (unsigned long) a4, 0 );   		
			break;

		//7
		//desenha um char no backbuffer.
		//Obs: Esse funciona, não deletar. :)
		// (x,y,color,char)
		// (left+x, top+y,color,char)
		//devemos usar o left e o top da janela com foco de entrada.
        //
		// Obs: A biblioteca c99 em user mode usa essa chamada para pintar um caractere
		// quando implementa a função printf(.). Porém esse caractere é pintado
		// na janela com o foco de entrada. A intenção é que o carctere seja pintado 
		// na própria janela do aplicativo.
		// Outro caso é a digitação de caractere. Quando um caractere é
		// digitado desejamos que ele seja pintado na janela com o foco de entrada.
		//
		// ?? Quando um caractere é pintado em uma janela que não está com o foco 
		//    de entrada ?? ex: shells, logs ...
		//
		//Supondo que os aplicativos escreverão mais em terminal por enquanto 
		//a cor padrão de fonte será a cor de terminal.
		
		// #importante	
		// Aqui está pintando o caractere na janela com o foco de entrada.
		case SYS_BUFFER_DRAWCHAR:
			focusWnd = (void *) windowList[window_with_focus];
			if( (void *) focusWnd == NULL ){ 
			    break; 
			};
			
			//x, y, color, char.
			sys_my_buffer_char_blt( (unsigned long) (focusWnd->left + arg2),             
			                    (unsigned long) (focusWnd->top + arg3),              
								CurrentColorScheme->elements[csiTerminalFontColor],   
								(unsigned long) arg4 ); 								 
			break;

		//8 @todo: BugBug, aqui precisamos de 4 parâmetros.
        case SYS_BUFFER_DRAWLINE:
			sys_my_buffer_horizontal_line ( (unsigned long) a2, 
			    (unsigned long) a3, (unsigned long) a4, COLOR_WHITE ); 		
			break;

		//9 @todo: BugBug, aqui precisamos de 5 parâmetros.
        case SYS_BUFFER_DRAWRECT:
            sys_drawDataRectangle ( 0, (unsigned long) a2, (unsigned long) a3, 
				(unsigned long) a4, COLOR_WHITE );    		
			break;

		// 10 Create window.
        // # suspensa.
        case SYS_BUFFER_CREATEWINDOW: 
            return NULL;
			break;
			
		//11, Coloca o conteúdo do backbuffer no LFB.
        case SYS_REFRESHSCREEN: 
			sys_refresh_screen ();
			break;			
			
        //rede: 12,13,14,15	
			
			
		//i/o:  16,17,18,19	
			
		//open()
		//retorna um i'ndice na tabela de arquivos abertos do proceso atual.	
		case 16:
			//unistd.c
			//o tipo mode_t precisa de kernel/sys/types.h
			//pathname, flags, mode
			return ( void *) sys_open ( (const char *) arg2, (int) arg3, (mode_t)	arg4 );
			break;
			
		case 17:
			return (void *) sys_close ( (int) arg2 );
			break;
			

        //24-28 WINDOW SUPPORT		
        
		//24
		// window.c	
		case 24:
		    return (void *) sys_show_window_rect ( (struct window_d *) arg2 );
		    break;
	 
		//34	
        case SYS_VIDEO_SETCURSOR: 
			sys_set_up_cursor ( (unsigned long) arg2, (unsigned long) arg2);
			break;              

		//35 - Configura o procedimento da tarefa atual.
        case SYS_SETPROCEDURE:  
            g_next_proc = (unsigned long) arg2;		
            break;
			
		//36
        //O teclado envia essa mensagem para o procedimento ativo.
        case SYS_KSENDMESSAGE: 
		    g_nova_mensagem = 1; //existe uma nova mensagem.
            sys_system_dispatch_to_procedure( (struct window_d *) arg2, 
			                              (int) arg2, 
										  (unsigned long) arg4, 
										  (unsigned long) 0);			
            break;    
      
	
		//37 - Chama o procedimento procedimento default. 
		//@todo return.
		case SYS_CALLSYSTEMPROCEDURE: 
            sys_system_procedure (NULL,arg2,arg3,arg4);	
			//return (void *) system_procedure ( NULL, arg2, arg3, arg4 );	
            break;    
        
	
	    // ## CANCELADA! ##
        //42 Load bitmap 16x16.
		case SYS_LOADBMP16X16 :       
            return NULL;			
            break;


        // 45 Message Box. 
		// Cancelado. 
		// Message box fica na biblioteca em ring 3.	
        case SYS_MESSAGEBOX:		
            return NULL;
			break;
		
        //47, cancelada.		
		case SYS_BUFFER_CREATEWINDOWx:
			return NULL;
			break;
		
		//48, cancelada.
		case SYS_BUFFER_CREATEWINDOW1:
			return NULL;
			break;
		
		//49, cancelada.
		case SYS_BUFFER_CREATEWINDOW2:
			return NULL;
			break;	
			
		//50~59 Window suppot, manipulação de janelas	

		//50 resize window (handle,x,y)
		case SYS_BUFFER_RESIZEWINDOW:		
		    return (void *) sys_resize_window ( (struct window_d*) arg2, arg3, arg4);
		    break;
		
		//51 redraw window. (handle)
		case SYS_BUFFER_REDRAWWINDOW:
		    return (void *) sys_redraw_window ( (struct window_d*) arg2, arg3 );
		    break;
		
		//52  replace window. (handle,x,y)
		case SYS_BUFFER_REPLACEWINDOW:
		    return (void *) sys_replace_window ( (struct window_d*) arg2, arg3, arg4);
		    break;
		
		//53 maximize window 
		case SYS_BUFFER_MAXIMIZEWINDOW:
		    //(handle)
		    sys_MaximizeWindow ((struct window_d*) arg2);
		    break;
		
		//54 minimize window
		case SYS_BUFFER_MINIMIZEWINDOW:
		    //(handle)
		    sys_MinimizeWindow ( (struct window_d *) arg2);
		    break;
		
		//55 Get foreground window.
		case SYS_BUFFER_GETFOREGROUNDWINDOW:
		    return (void *) sys_windowGetForegroundWindow();
		    break;
		
		//56 set foreground window.
		case SYS_BUFFER_SETFOREGROUNDWINDOW:
		    return (void *) sys_windowSetForegroundWindow((struct window_d*) arg2);
		    break;
		
		
		//57.	
		case SYS_REGISTERWINDOW: 
			return (void *) sys_RegisterWindow ( (struct window_d *) hWnd );
			break;
			
		//58.	
		case SYS_CLOSEWINDOW: 
			sys_CloseWindow ( (struct window_d *) hWnd ); 							  
			break;
			
        //60
		case SYS_SETACTIVEWINDOW:			
			sys_set_active_window (hWnd);
			break;

        //61
		case SYS_GETACTIVEWINDOW:
            return (void *) sys_get_active_window();    //Id. (int).		
			break;

        //62
		case SYS_SETFOCUS: 
			sys_SetFocus ( (struct window_d *) hWnd ); 							  
			break;
			
        //63 id
		case SYS_GETFOCUS: 
		    return (void *) window_with_focus;  
			break;
			
        //64
		case SYS_KILLFOCUS:
			sys_KillFocus ( (struct window_d *) hWnd ); 							  
			break;

		//65	
		//putchar usando o cursor gerenciado pelo kernel.
		//a biblioteca em user mode, altera o cursor do kernel e 
		//usa essa rotina para imprimir.
		//obs: #importante: Como printf é uma função 
		//usada pelo terminal virtual, deve-se considerar as cores 
		//usadas no terminal virtual.
		//@todo: implementar a configuração de cores no terminal virtual 
		//usado pelo aplicativo.
		//obs: estamos improvisando as cores por enquanto.
		//
		// Obs: ?? Como faremos para pintar dentro da janela do terminal.
        // Obs: a rotina de configuração do terminal deverá ajustar 		
		// as margens usadas pela rotina de impressão de caracteres.
        // então nesse momento devemos considerar que as margens ja estão 
        // ajustadas.		

        // #importante:
		// putchar pertence a libc e todo o sistema tem obedecido 
		// a sua maneira de imprimir chars ... não podemos mudar 
		// putchar assim tão facilmente.
		// refresh_rectangle obedece os deslocamentos usados 
		// por putchar.
 		
		// Coloca um char usando o 'terminal mode' de stdio.
		// selecionado em _outbyte.
		// stdio_terminalmode_flag = não transparente.
		// Chama função interna.
		
		case SYS_PUTCHAR: 
			sys_servicesPutChar ( (int) arg2 );		
			break;

		//66 - reservado pra input de usuário.
		//case 66:
		//	break;

		//67- reservado pra input de usuário.	
		//case 67:
		//	break;

		//68- reservado pra input de mouse.	
		//case 68:		
		//	break;

		//	
		//69 - Driver de teclado enviando mensagem de digitação.	
		//     Não somente um driver, mas qualquer processo pode enviar
		// uma mensagem pra janela com o foco de entrada e chamar o procedimento.
		// >>>> Enviando para a classe certa.
        // arg2=msg, arg3=ch, arg4=ch 0		
		//
		case 69:
			printf("%c", arg3);
			sys_system_procedure( NULL, 
			                  (int) arg2, 
							  (unsigned long) arg3, 
							  (unsigned long) arg4 );
			
			sys_windowSendMessage( (unsigned long) NULL,
			                   (unsigned long) arg2,
							   (unsigned long) arg3,
							   (unsigned long) arg4 );
			break;
			
		//
        // ## EXIT ##
        //		
			
		// 70 - Exit. 
		// Criaremos um request que será atendido somente quando ouver uma 
		// interrupção de timer. Enquanto isso a thread deve esperar em um loop.	
		case SYS_EXIT:
			sys_create_request ( (unsigned long) 12, //number 
                 (int) 1,               //status 
                 (int) 0,               //timeout. 0=imediatamente.
				 (int) current_process, //target_pid
				 (int) current_thread,  //target_tid
                 NULL,                  //window 
                 (int) 0,               //msg  
                 (unsigned long) 0,     //long1  
                 (unsigned long) 0 );   //long2
			break;
		
        //71 		
		case SYS_FORK: 
		    return (void *) sys_do_fork_process ();
			break;	

		//72 - Create thread.	
        case SYS_CREATETHREAD:			
			return (void *) sys_create_thread ( 
			                NULL,             // w. station 
							NULL,             // desktop
							NULL,             // w.
							arg2,             // init eip
							arg3,             // init stack
							current_process,  // pid (determinado)(provisório).
							(char *) a4 );    // name
			break; 

		//73 - Create process.
        //@todo; Ok, nesse momento, precisamos saber qual é o processo pai do processo 
        //que iremos criar. Esse deve ser o processo atual ...  		
		// PPID = 0. Nesse momento todo processo criado será filho do processo número 0.
		// mas não é verdade. @tpdp: Precisamos que o aplicativo em user mode 
		// nos passe o número do processo pai, ou o proprio kernel identifica qual é o 
		//processo atual e determina que ele será o processo pai.        
		case SYS_CREATEPROCESS:
            return (void *) sys_create_process ( NULL, NULL, NULL, 
			                    arg2, arg3, 0, (char *) a4, 
								RING3, (unsigned long ) CreatePageDirectory() ); 		
            break;
			
		//80 Show current process info.
		//#todo: Mostrar em uma janela própria.
		//#todo: Devemos chamar uma função que mostre informações 
		//apenas do processo atual. 
		case SYS_CURRENTPROCESSINFO:
		    sys_show_currentprocess_info ();
		    break;
			
		//81
		//#bugbug Isso está retornando o ID do processo atual.
		//O que queremos é o ID do processo que está chamando
		case SYS_GETPPID: 
		    return (void *) sys_getppid ();
			break;
		
		//82
		//
		case SYS_SETPPID: 
			break;
			
			
		//83
        case SYS_WAIT4PID: 
            //schedi.c
			return (void *) sys_do_wait ((int *) arg2 );
			
			// TID, PID 		
			// TID é a thread atual.
			// PID veio via argumento.
			//block_for_a_reason ( (int) current_thread, (int) arg2 ); //suspenso
		    break;
			
		//85
		//#bugbug Isso está retornando o ID do processo pai do processo atual.
		//O que queremos é o ID do processo pai do processo que está chamando.
		case SYS_GETPID: 
		    return (void *) sys_getpid();
			break;
		
		//86
		//
		case SYS_SETPID: 
		    //
			break;
		
		//Down. 87
		case SYS_SEMAPHORE_DOWN:
		    return (void *) sys_Down ( (struct semaphore_d *) arg2);
		    break;
			
		//Testa se o processo é válido
        //se for válido retorna 1234		
		//testando...
		case SYS_88:   
            return (void *) sys_processTesting (arg2);			
			break;
			
		//Up. 89	
		case SYS_SEMAPHORE_UP:
		    return (void *) sys_Up ( (struct semaphore_d *) arg2 );
		    break;
		
		//90 Coletor de threads Zombie. (a tarefa idle pode chamar isso.)		
		case SYS_DEADTHREADCOLLECTOR: 
			sys_dead_thread_collector ();
			break;
			
		//94	
		//REAL (coloca a thread em standby para executar pela primeira vez.)
		// * MOVEMENT 1 (Initialized --> Standby).
		case SYS_STARTTHREAD:
		    t = (struct thread_d *) arg2;
            sys_SelectForExecution (t);    	
			break;		
			
	    //
        // 99,100,101,102 = Pegar nas filas os parâmetros hwnd, msg, long1, long2.
        //

        // *importante: 
		// #bugbug SYS_GETKEYBOARDMESSAGE (44) está pegando a mensagem de teclado,
		// mas na verdade deveria apenas pegar a mensagem, sem se preocupar em 
		// qual foi o dispositivo gerador do evento. ??!!

			
		// 99,  Pega 'hwnd' na fila da janela com o foco de entrada.
		case SYS_GETHWINDOW:
		    return NULL;
		    break;
			
		//#bugbug
		//****  Pega 'msg' na fila da janela com o foco de entrada.
		//Pegando a mensagem na fila da janela com o foco de entrada.
		case SYS_GETKEYBOARDMESSAGE:
			return (void *) sys_windowGetMessage ( (struct window_d *) WindowWithFocus );
			break;
			
		//****   Pega 'long1' na fila da janela com o foco de entrada.	
		case SYS_GETLONG1:
			return (void *) sys_windowGetLong1 ( (struct window_d *) WindowWithFocus );
			break;
			
		//****   Pega 'long2' na fila da janela com o foco de entrada.	
		case SYS_GETLONG2:
			return (void *) sys_windowGetLong2 ( (struct window_d *) WindowWithFocus );
			break;

 
		//103, SYS_RECEIVEMESSAGE	
        //Um processo consumidor solicita mensagem deixada em seu PCB.
        //Argumentos: serviço, produtor, consumidor, mensagem.		
        //@todo: 
		case SYS_RECEIVEMESSAGE:
			break;
			
		//104, SYS_SENDMESSAGE
		//Um processo produtor envia uma mensagem para o PCB de outr processo.
		//Argumentos: serviço, produtor, consumidor, mensagem.
		//@todo:		
		case SYS_SENDMESSAGE:			
			break;

			
		//110 Reboot.
        //(Teclado é legado, é desbloqueado)		
	    case SYS_REBOOT: 
			sys_systemReboot ();
			break;
			
		
		//
		// #### Get Message ####
		//
		
		// #importante:
		// Esse é o get message usado pelos aplicativos.
		// O aplicativo envia um endereço de array e devemos colocar 4 longs 
		// como mensagem.
		// Isso funcionou. 
		// Esse será o padrão até usarmos ponteiro para estrutura.
		
		// A intenção agora é pegar a mensagem na estrutura de thread atual.
		// Desse modo cada aplicativo, quando estiver rodando, pegará as 
        // suas mensagens em sua própria fila.  		
		// Se não houver mensagem na estrutura da thread, então tentaremos colocar alguma.
		// Vamos colocar alguma coisa do buffer de teclado.
			
		case 111:
		    if ( &message_address[0] == 0 )
			{
				printf ("services: 111, null pointer");
				die();
				
			}else{
				
			    t = (void *) threadList[current_thread];
			    
	            if ( (void *) t == NULL )
	            {
		           return NULL;
	            }
								
				if ( t->newmessageFlag != 1 )
				{
					SC = (unsigned char) get_scancode ();
	                KEYBOARD_LINE_DISCIPLINE ( SC );						
				}
	
				//pegando a mensagem.
			    
				//padrão
				message_address[0] = (unsigned long) t->window;
			    message_address[1] = (unsigned long) t->msg;
			    message_address[2] = (unsigned long) t->long1;
			    message_address[3] = (unsigned long) t->long2;
				
				//extra. Usado pelos servidores e drivers.
				message_address[4] = (unsigned long) t->long3;
				message_address[5] = (unsigned long) t->long4;
				message_address[6] = (unsigned long) t->long5;
				message_address[7] = (unsigned long) t->long6;
				//...	
                    
				//sinalizamos que a mensagem foi consumida.
				//#todo: nese momento a estrutura da thread também precisa ser limpa.
                t->newmessageFlag = 0; 					
				    
				//sinaliza que há mensagem
				return (void *) 1; 
				
			};
		    break;
		
		//Envia uma mensagem PAINT para o aplicativo atualizar a área de trabalho.
		case 113:
		    sys_windowUpdateWindow ( (struct window_d *) arg2 );
			break;
			
		// 114	
        // Envia uma mensagem para a thread atual.	
			
		case SYS_SENDWINDOWMESSAGE:
			// endereço do buffer da mensagem, tid.
			services_send_message_to_thread ( (unsigned long) &message_address[0], (int) current_thread );
		    break;
			
			
		// 115 - ## IMPORTANTE ## 
		// Usado por servidores do sistema para se comunicarem 
		// com o kernel.
		// >> magic 1234: Acoplar taskman.
		// >> magic 4321: Desacoplar taskman
		// >> magic 12345678: Pegar mensagem
		// #todo: Chamar uma função que trate o argumento com um switch.
		case 115:
		
			if ( arg3 == 1234 )
			{
				current_taskman_server = (int) arg4;
				//printf("115: acoplando ...\n");
				//refresh_screen();
                return NULL; 				
			}; 
			
			if ( arg3 == 1234 )
			{
				if( current_taskman_server == arg4 )
				{
				    current_taskman_server = (int) 0;
				    //printf("115: desacoplando ...\n");
				    //refresh_screen();
				    return NULL;
				} 
			};
			
			if ( arg3 == 12345678 )
			{
				if( current_taskman_server == arg4 )
				{
					if( gui->taskmanWindow->newmessageFlag == 0 )
					{
			            message_address[0] = (unsigned long) 0;
			            message_address[1] = (unsigned long) 0; //*importante: mensagem nula.
			            message_address[2] = (unsigned long) 0;
			            message_address[3] = (unsigned long) 0;
					    gui->taskmanWindow->newmessageFlag = 0;
                        return NULL;						
					}
					//se existe uma mensagem na janela do servidor taskman.
					if( gui->taskmanWindow->newmessageFlag == 1 )
					{
			            message_address[0] = (unsigned long) gui->taskmanWindow->msg_window;
			            message_address[1] = (unsigned long) gui->taskmanWindow->msg; 
			            message_address[2] = (unsigned long) gui->taskmanWindow->long1;
			            message_address[3] = (unsigned long) gui->taskmanWindow->long2;
					    gui->taskmanWindow->newmessageFlag = 0;
						return NULL;
					};
				};
			};
			break;
			
		//Envia uma mensagem de teste para o servidor taskman	
		case 116:
	        gui->taskmanWindow->msg_window = NULL;
		    gui->taskmanWindow->msg = (int) arg2;             //123; //123=temos uma mensagem. 
		    gui->taskmanWindow->long1 = (unsigned long) arg3;    //0;
		    gui->taskmanWindow->long2 = (unsigned long) arg4;    //0;
            gui->taskmanWindow->newmessageFlag = 1;				
		    break;
			
		//119
		case SYS_SELECTCOLORSCHEME:
		    return (void *) sys_windowSelectColorScheme ( (int) arg2 );
			break;
			
			
		//124	
		// defered system procedure call.
		// #todo: precisamos armazenasr os argumentos em algum lugar.
		case 124:
		    kernel_request = KR_DEFERED_SYSTEMPROCEDURE;
			break;
			
		//125	
		// system procedure call.
        case 125:
            return (void *) sys_system_procedure ( NULL, arg2, arg3, arg4 );
			break;	
			
		//126	
		case SYS_USERMODE_PORT_IN:
			//#bugbug
			//#todo: Tem que resolver as questões de privilégios.
			//bits, port
			return (void *) sys_portsx86_IN ( (int) arg2, (unsigned long) arg3 );
			break;
			
		//127	
		case SYS_USERMODE_PORT_OUT:
			//#bugbug
			//#todo: Tem que resolver as questões de privilégios.
			//bits, port, value
			sys_portsx86_OUT ( (int) arg2, (unsigned long) arg3, (unsigned long) arg4 );
			return NULL;
			break;
		
		//
		// 129, Um driver confirmando que foi inicializado.
		// Efetuaremos a rotina de ligação do driver com o sistema.
		// O sistema linka o driver com o sistema operacional.
	    //@todo: Essa rotina precisa ser aprimorada. Mas a chamada deve ser 
		// essa mesma.
		//
		case SYS_DRIVERINITIALIZED: 
		    return (void *) sys_systemLinkDriver(arg2,arg3,arg4); 
			break;
			
		//130
		case SYS_DRAWTEXT:
		    
			//@todo: Poderia pintar na janela atual.
			argString = (unsigned char *) arg4;
		    sys_draw_text ( (struct window_d *) message_address[0], //window
			    (unsigned long) message_address[1],  //x
				(unsigned long) message_address[2],  //y
				(unsigned long) message_address[3],   //color
				(unsigned char *) message_address[4] ); //string
			break;
			
		//131
		// Pintar o caractere especificamente na janela com o foco de entrada.          
		case SYS_BUFFER_DRAWCHAR_WWF: 
			focusWnd = (void *) windowList[window_with_focus];
			if ( (void *) focusWnd == NULL )
			{
			    break;	
			};
			
			sys_my_buffer_char_blt( (unsigned long) (arg2 + focusWnd->left), //x.
			                    (unsigned long) (arg3 + focusWnd->top),  //y.
								COLOR_BLACK,                             //color. 
								(unsigned long) arg4);                   //char.
    		break;
			
		case 132:
		    //#bugbug: pagefault
			//save_rect (  message_address[0],  message_address[1],  message_address[2],  message_address[3] );
			break;
			
        case 133: 		
		    //#bugbug: pagefault
			//show_saved_rect (  message_address[0],  message_address[1],  message_address[2],  message_address[3] );
			break; 
			
		// 134
		// Pegar informações sobre a área de cliente de uma janela;
		//#bugbug: temos que checar mais validade de estrutura.
		//obs: No começo dessa função, colocamos o arg3 como ponteiro para a3.
		//um buffer de longs.
		case 134:
				hWnd = (struct window_d *) arg3;

				if ( (void *) hWnd != NULL )
				{	
					a3[0] = (unsigned long) hWnd->rcClient->left;
					a3[1] = (unsigned long) hWnd->rcClient->top;     
					a3[2] = (unsigned long) hWnd->rcClient->width;
					a3[3] = (unsigned long) hWnd->rcClient->height;
					a3[4] = (unsigned long) hWnd->rcClient->bg_color;
				}
			break;
			

		// 135
		// Coloca caracteres na estrutura de terminal, para aplciativos pegarem
        case SYS_FEEDTERMINAL:
            //@todo:
			// Colocar o caractere enviado no argumento para 
			//a estrutura de terminal do terminal indicado no argumento.
			//terminalFeed( (int) arg2, (int) arg3 );
			
			//arg2 = número do terminal
			//arg3 = ch 
			//arg4 - ch 
			
			//terminal.h
			//teminalfeedCH = (char) arg3;
			//teminalfeedCHStatus = (int) 1;
		    break;	
			
		//136
		//fgetc
		case 136:
			return (void *) sys_fgetc ( (FILE *) arg2 );
			break;
			
		//137
		// Isso é usado pela biblioteca stdio em user mode
		// na função 'getchar()'
		// #bugbug: Está pegando caracteres extras às vezes.
		//#test
		//#bugbug: a partir de agora isso deve pegar mensagem na thread 
		//atual e não mais na janela com foco de entrada.			
        case SYS_GETCH:  
			
			return (void *) sys_thread_getchar();
			
			//#todo: podemos tentar pegar do stdin do processo atual.
			//return (void *) fgetc ( (FILE *) arg2 );
            break;

		//138 - get key state.	
		//#importante: 
		//#todo: isso precisa ir para a API.
        case 138:
		    return (void *) sys_keyboardGetKeyState ( (unsigned char) arg2 );
            break;		
			
		//139
        case SYS_GETSCANCODE:
		    return (void *) sys_get_scancode();
            break;		

        //140
        case SYS_SET_CURRENT_KEYBOARD_RESPONDER:
            sys_set_current_keyboard_responder(arg2);		
		    break;
			
		//141	
		case SYS_GET_CURRENT_KEYBOARD_RESPONDER:
		    return (void *) sys_get_current_keyboard_responder();
		    break;
			
		//142	
        case SYS_SET_CURRENT_MOUSE_RESPONDER:			
		    sys_set_current_mouse_responder(arg2);
			break;
			
		//143	
		case SYS_GET_CURRENT_MOUSE_RESPONDER:
		    return (void *) sys_get_current_mouse_responder();
			break;

			
		//144	
		//Pega o ponteiro da client area.	
		case SYS_GETCLIENTAREARECT:	
		    //#bugbug: pegamos o ponteiro mas não temos permissão para acessar a estrutura.
			return (void *) sys_getClientAreaRect();	
			break;
		
		//145
        //configura a client area	
        //@todo: O ponteiro para estrutura de retângulo é passado via argumento.		
		case SYS_SETCLIENTAREARECT:
			sys_setClientAreaRect ( arg2, arg3, arg4, 0);
            break;

		//146	
		//#bugbug: isso não parece seguro, precismos checar a validade da estrutura antes,
        //mas vai ficar assim por enquanto.					
		case 146:	
		    //return (void *) gwsScreenWindow(); //#todo
		    return (void *) gui->screen;
			break;
			
		//147	
		//#bugbug: isso não parece seguro, precismos checar a validade da estrutura antes,
        //mas vai ficar assim por enquanto.		
        case 147:
		    //return (void *) gwsMainWindow(); //#todo
			return (void *) gui->main;
			break;
			
		//create grid and itens.
		//n, view 
		case 148:
		    return (void *) sys_grid ( (struct window_d *) arg2, 
			                (int) arg3, (int) arg4 );
            break;		

        //test. menu.
		case 149:
            //essa é uma rotina de teste, qua chama várias funções.
			sys_MainMenu ( (struct window_d *) arg2 );		
            break;		
			
		//152 - get user id	
		case SYS_GETCURRENTUSERID:
		    return (void *) current_user;
			break;			
		
		//154 - get group id	
		case SYS_GETCURRENTGROUPID:
		    return (void *) current_group;
			break;
			
		// 167
        // SYS_GRAMADOCORE_INIT_EXECVE
        // executa um novo programa dentro do processo INIT 
		// do ambiente Gramado Core.	
        //
        // #importante:
        // os argumentos recebidos aqui precisam ir para ipc/spawn.c 
        // que serão enviados via registradores para o aplicativo.
        // Obs: Não adianta enviar ponteiros para o aplicativo, 
        // pois ele não pode pegar no kernel.	
		
		//167:
		//EXECUTA .BIN COM ENTRYPOINT EM 0x1000
		case SYS_GRAMADOCORE_INIT_EXECVE_BIN:
		    // Testar
			// execve.c
		    // Obs: É dever dessa rotina colocar a thread em estado standby,
			// onde ela fica selecionada para execussão.
			// pois um exit pode deixar o estado da thread reaproveitada 
			// de um jeito que não rode.
			return (void *) sys_executive_gramado_core_init_execve( 0,  //serviço 
			                (const char *) arg2,                //name
			                (const char *) arg3,                //(arg)(endereço da linha de comando)
							(const char *) arg4 );              //env
			break;
			
		//168
        //EXECUTA .EXE COM ENTRYPOINT EM 0x400		
		case SYS_GRAMADOCORE_INIT_EXECVE_EXE:
            //# cancelada ;;; substituir por alguma rotina de execução de formato binário como COFF;
			break;			
			
		//157 - get user session id	
		case SYS_GETCURRENTUSERSESSION:
		    return (void *) current_usersession;
			break;
			
        //158 - get window station id		
		case SYS_GETCURRENTWINDOWSTATION:	
		    return (void *) current_room; 
			break;	
			
		//159 - get desktop id
        case SYS_GETCURRENTDESKTOP:		
		    return (void *) current_desktop; 
			break;
			
		// 160
		// Criar um socket e retornar o ponteiro para a estrutura.
		// Gramado API socket support. (not libc)	
		case 160:
            return (void *) sys_create_socket ( (unsigned long) arg2, (unsigned short) arg3 );
			break;
			
		// 161
        // get socket IP
		// Gramado API socket support. (not libc)		
		case 161:
		    return (void *) sys_getSocketIP ( (struct socket_d *) arg2 );
            break;		

		// 162
        // get socket port		
		// Gramado API socket support. (not libc)	
		case 162:
		    return (void *) sys_getSocketPort( (struct socket_d *) arg2 );
            break;		
			
		// 163
        // update socket  
        // retorno 0=ok 1=fail		
        // Gramado API socket support. (not libc)	
		case 163:
            return (void *) sys_update_socket ( (struct socket_d *) arg2, (unsigned long) arg3, (unsigned short) arg4 );
			break;		

		//#todo: a chamada está no shell em net.c
		//netStream
        case 164:
            //IN: ( service, (unsigned long) stream, option, option )
			break;	

		//#todo: a chamada está no shell em net.c	
		//netSocket
        case 165:
            //IN: ( service, (unsigned long) socket, option, option );	
			break;

		//#todo: a chamada está no shell em net.c	
		//netBuffer
        case 166:
            //IN:  ( service, buffer_address, option, option );	
			break;		
			
		//170
        //pwd ...
        //Cada processo tem seu próprio pwd.
        //Essa rotina mostra o pathname usado pelo processo.	
		case SYS_PWD:
			sys_fs_print_process_pwd (current_process);
			break;	
		
		//171 - retorna o id do volume atual.
		case SYS_GETCURRENTVOLUMEID:
		    return (void *) current_volume;
            break;	

		//172 - configura o id do volume atual.
		//#bugbug: Estamos modificando, sem aplicar nenhum filtro.
		case SYS_SETCURRENTVOLUMEID:
		    current_volume = (int) arg2;
            break;	

		//173 Lista arquivos de um diretório, dado o número do disco,
        //o número do volume e o número do diretório,
        //args in: disk id, volume id, directory id		
        case SYS_LISTFILES:
            sys_fsListFiles ( arg2, arg3, arg4 );  
			break;
			
			
		//174
		case SYS_SEARCHFILE:
		    return (void *) sys_KiSearchFile ( (unsigned char *) arg2, 
                                (unsigned long) arg3 );
			break;
			
		//175
		// cd.
        //Atualiza o pathname na estrutura do processo atual.
        //Atualiza o pathname na string global.		
		case 175:
		    sys_fsUpdateWorkingDiretoryString ( (char *) arg2 );
            sys_fsLoadFileFromCurrentTargetDir ();
			break;
			
		//176	
        //Remove n nomes de diretório do pathname do processo indicado no argumento.
        //Copia o nome para a string global.
		case 176:	
		    sys_fs_pathname_backup ( current_process, (int) arg3 );
			break;
			
		//177
		//'dir'
		//comando dir no shell.
		//Listando arquivos em um diretório dado o nome.	
		case 177:
		    sys_fsList ( (const char *) arg2 );		
            break;

        case 178:
		    //#test
			//implementando esse serviço.
		    taskswitch_lock();
	        scheduler_lock();	
			//name , address.
            Ret = (void *) sys_fsGetFileSize ( (unsigned char *) arg2 ); 
			scheduler_unlock();
	        taskswitch_unlock();
			return (void *) Ret;		    
            break;		
			
		// # test #	
		// #bugbug: suspenso.
		// passando vetor de ponteiros.
		// executando um novo programa no processo init.
		//case 179:
		// contador, endereço.
		//    return (void*) execve_execute_on_init( (int) arg2, (const char *) arg3 );
        //    break;		

		//184
		//pega o endereço do heap do processo dado seu id.	
        case SYS_GETPROCESSHEAPPOINTER:
            return (void *) sys_GetProcessHeapStart ( (int) arg2 );
			break;	

		// feof	
		case 193:	
		    return (void *) sys_feof ( (FILE *) arg2 );
            break;
			
		//ferror	
		case 194:	
		    return (void *) sys_ferror ( (FILE *) arg2 );
            break;
			
		//fseek	
		case 195:	
		    return (void *) sys_fseek ( (FILE *) arg2, (long) arg3, (int) arg4 );
            break;
			
		//fputc	
		case 196:	
		    return (void *) sys_fputc ( (int) arg2 , (FILE *) arg3 );
            break;			
			
        //197
		//scroll de área de cliente de uma janela;
        case 197:
		    //essa é uma boa rotina, mas precisamos tabalhar nisso,
			//está dando page fault.
			//scroll_client_window ( (struct window_d *) arg2 );
            break; 		
			

		//199 - Garbage Collector.	
		//A ideia é que os utilitários de gerência de memória possam usar isso.
		case SYS_GC:
		    sys_gc ();
			//return (void *) gc (); 
		    break;
		
		//200 - Envia um sinal para um processo.	
		//argumentos (process handle, signal number).
		case SYS_SENDSIGNAL:
		    sys_signalSend ( (void *) a2, (int) arg3 );
		    break;
			
		//...

        //205
		//block for a reason.
        //bloqueamos uma thead por um dos motivos indicados em argumento.
        case SYS_GENERICWAIT:
		    //TID, reason.
            sys_block_for_a_reason ( (int) arg2, (int) arg3 );
			break;		
			
		//210
		case SYS_CREATETERMINAL: 
            break;
			
		//211
        case SYS_GETCURRENTTERMINAL:
            return (void *) current_terminal;
			break;
			
	    //212
        case SYS_SETCURRENTTERMINAL:
            current_terminal = (int) arg2;
			break;
			
		//213
        case SYS_GETTERMINALINPUTBUFFER:	
            return NULL;
			break;
			
		//214
        case SYS_SETTERMINALINPUTBUFFER:		
		    break;

		// 215
		// Get terminal window.	
		// retorna o ID.
		// O ID fica em terminal_window.
		case SYS_GETTERMINALWINDOW: 
			return (void *) sys_systemGetTerminalWindow(); 
			break;

		// 216
		// Set terminal window	
		// Configura qual vai ser a janela do terminal virtual. 
		// #obs: O refresh de stdout podera' ocorrer em ts.c
		// O ID fica em terminal_window.	
		case SYS_SETTERMINALWINDOW:	
		   sys_systemSetTerminalWindow ( (struct window_d *) arg2 );	
		   break;
		   
		//217
		case SYS_GETTERMINALRECT:
			return NULL; 
			break;

		//218
        //configura na estrutura do terminal corrente,
        //qual vai ser o retãngulo a ser usado. 		
		case SYS_SETTERMINALRECT:
		
		   //#bugbug: Pagefault.
		   
		    // Estamos usando default por falta de argumento.
            //systemSetTerminalRectangle( DEFAULT_TERMINAL_LEFT, 
			//                            DEFAULT_TERMINAL_TOP, 
			//							arg3, 
			//							arg4 );		
		    break;
			
		//219
        case SYS_DESTROYTERMINAL:
            break; 	


		// 222 - create timer.
		//args: window e ms e tipo
        case 222:
		    return (void *) sys_create_timer ( (struct window_d *) arg2, (unsigned long) arg3, (int) arg4 );
		    break;

		
        //223 - get sys time info.
        // informações variadas sobre o sys time.		
		case 223:
		    return (void *) sys_get_systime_info ( (int) arg2 );
            break;		
			
		//224 - get time	
		case SYS_GETTIME:	
		    return (void *) sys_get_time ();
			break;
			
		//225 - get date
		case SYS_GETDATE:
		    return (void *) sys_get_date ();
            break;		
			
			
		//Obs: @todo: poderia ser uma chamada para configurar o posicionamento 
        //e outra para configurar as dimensões.		
			
		//226 get
        case SYS_GET_KERNELSEMAPHORE:
            return (void *) __spinlock_ipc;
            break;
        
        //227 close critical section	
		case SYS_CLOSE_KERNELSEMAPHORE:
			__spinlock_ipc = 0;
			break;
			
		//228 open critical section
		case SYS_OPEN_KERNELSEMAPHORE:
		    __spinlock_ipc = 1;
            break;
			
			
		//232
		case 232:
			return (void *) sys_fclose ( (FILE *) arg2);
			break;
			
		//233
		case 233:
			return (void *) sys_fflush ( (FILE *) arg2);
			break;
			
		//234
		case 234:
			return (void *) sys_fprintf ( (FILE *) arg2, (const char *) arg3 );
			break;
			
		//235
		case 235:
			return (void *) sys_fputs ( (const char *) arg2, (FILE *) arg3 );
			break;
			
		//...
			
		//240
		case SYS_GETCURSORX:
		    return (void *) sys_get_cursor_x();
		    break;

		//241
		case SYS_GETCURSORY:
		    return (void *) sys_get_cursor_y();
		    break;
			
		//244 enable text cursor.	
		case 244:
		    sys_timerEnableTextCursor ();
		    //timerShowTextCursor = 1;
		    //gwsEnableTextCursor ();
            break;		
		
		//245 disable text cursor.
		case 245:
		    sys_timerDisableTextCursor ();
		    //timerShowTextCursor = 0;
		    //gwsDisableTextCursor ();
            break;		
			
		//246 ~ 249 reservado para libc support.	
			
		//246	
		//fopen()	
		case 246:
			//filename, mode.
			return (void *) sys_fopen ( (const char *) arg2, (const char *) arg3 );
			break;
			
		//reservado	
		//>>>pipe	
		case 247:
			//#todo: rotina provisória
			return (void *) sys_pipe ( (int *) arg2 ); 
			break;
			
		//reservado	
		case 248:
			return NULL;
			break;
			
		//reservado	
		case 249:
			return NULL;
			break;
			
			
			
		//Info. (250 ~ 255).
		
		//250
		//Get system metrics
		case SYS_GETSYSTEMMETRICS:
		    return (void *) sys_systemGetSystemMetrics ( (int) arg2 );
		    break;
		
		//251
		//Informações sobre o disco atual.
		case SYS_SHOWDISKINFO:
		    sys_diskShowCurrentDiskInfo();
			refresh_screen();
			break;

		//252
		//Informações sobre o volume atual.
		case SYS_SHOWVOLUMEINFO:
		    sys_volumeShowCurrentVolumeInfo();
			refresh_screen();
			break;
		
		//253
		case SYS_MEMORYINFO:
		    sys_memoryShowMemoryInfo();
			refresh_screen();
			break;
			
			
		//254 - Show PCI info.	
		case SYS_SHOWPCIINFO: 
			sys_systemShowDevicesInfo();
			refresh_screen();
			break;
			
		//255 - Mostra informações sobre o kernel.	
		case SYS_SHOWKERNELINFO: 
			sys_KiInformation ();
			//refresh_screen ();
			break;
			
		// @todo:
		// Need to check the system call ID to ensure it's valid 
		// If it s invalid, return ENOSYS Function not implemented error
		
		default:	
			printf ("services: Default {%d}\n", number );
			//#todo: retorno.
			//return NULL;
			break;
	};
	
	//Debug.
	//printf("SystemService={%d}\n",number);
    
	
	// * importante:
	//   Depois de esgotados os 'cases', vamos para a saída da função.

    //    No caso de um aplicativo ter chamado essa rotina, 
	// o retorno será para o ISR da int 0x80, feito em assembly.
    //    No caso do kernel ter chamado essa rotina, apenas retorna.
	
//Done.
done:
    //Debug.
    //printf("Done\n",number);
	//refresh_screen();
    return NULL;	
}



/*
 * serviceCreateWindow:
 *     Cria uma janela com base nos argumentos passados no buffer.
 */

unsigned long serviceCreateWindow ( char *message_buffer ){
	
	unsigned long *message_address = (unsigned long *) message_buffer;
	
	//Ponteiro para a janela criada pelo serviço.
    struct window_d *NewWindow;  
		
	cwArg1 = message_address[0];             // Type. 		
	cwArg2 = message_address[1];             // WindowStatus 
	cwArg3 = message_address[2];             // view
	cwArg4 = (char *) message_address[3];    // a4 Window name.
	cwArg5 = message_address[4];             // x
	cwArg6 = message_address[5];             // y
	cwArg7 = message_address[6];             // width
	cwArg8 = message_address[7];             // height
		
	//parent window.
	//message_address[8];
	//cwArg9 = gui->screen;  //@todo: O argumento arg4 está enviando parent window. 		
	cwArg9 = (struct window_d *) message_address[8];  //parent
		
	//onde?
	//message_address[9];
	//cwArg10 = arg4;  //desktop ID 		
		
	cwArg11 = message_address[10];    //cor da area de cliente.
	cwArg12 = message_address[11];    //cor da janela.	
	
	   //==========
	
	//Window.
	unsigned long WindowType;      //Tipo de janela.
	unsigned long WindowStatus;    //Status, ativa ou não.
	//unsigned long WindowRect;
	unsigned long WindowView;      //Min, max.
	char *WindowName;  
	
	unsigned long WindowX = (2*(800/20));  //100;   >          
	unsigned long WindowWidth  = 320;               
	
	unsigned long WindowY = (2*(600/20)); //100;   V                
	unsigned long WindowHeight = 480;  
	
	unsigned long WindowClientAreaColor = COLOR_WINDOW;  
	unsigned long WindowColor = COLOR_WINDOW;  
	
	
	//#todo: Checar a validade da esturtura,
	//WindowClientAreaColor = CurrentColorScheme->elements[csiWindow];  
	//WindowColor = CurrentColorScheme->elements[csiWindowBackground];  
	
	WindowType = cwArg1; 
	WindowStatus = cwArg2; 
	WindowView = cwArg3; 
	WindowName = (char *) cwArg4; 

	WindowX = cwArg5; 
	WindowY = cwArg6; 

	WindowWidth = cwArg7; 
	WindowHeight = cwArg8;

	//#todo
	//gui->screen  = cwArg9; 
	//desktopID = cwArg10; 

	WindowClientAreaColor = (unsigned long) cwArg11;  //Obs: A cor da área de cliente será escolhida pelo app.   
	WindowColor = (unsigned long) cwArg12;     


	struct thread_d *t;
	int desktopID;
	
	
	desktopID = (int) get_current_desktop_id ();	
	
    // Importante:
	// Nesse momento é fundamental saber qual é a parent window da janela que vamos criar 
	// pois a parent window terá as margens que nos guiam.
	// Essa parent window pode ser uma aba de navegador por exemplo.
	// >> O aplicativo deve enviar o ponteiro da janela mãe.
	
	//Criando uma janela, mas desconsiderando a estrutura rect_d passada por argumento.
	//@todo: #bugbug a estrutura rect_d apresenta problema quando passada por argumento
	//com um endereço da área de memória do app.
	
    NewWindow = (void *) CreateWindow ( WindowType, WindowStatus, 
	                        WindowView, WindowName, 
	                        WindowX, WindowY, WindowWidth, WindowHeight,									  
							cwArg9, desktopID, 
							(unsigned long) WindowClientAreaColor, 
							(unsigned long) WindowColor );
	
	if ( (void *) NewWindow == NULL )
	{ 
        //?? Mensagem.
	    //return NULL; 
		return 0;
		
	}else{	
        
		
		//se a janela foi criada com sucesso, podemos desativar a flag.
		//*importante, nesse momento precisamos desativar a flag.
		
		cwFlag = 0;                  
		
        // Obs: 
		// Quem solicitou a criação da janela pode estar em user mode
        // porém a estrutura da janela está em kernel mode. #bugbug
		// Obs:
		// Para preencher as informações da estrutura, a aplicação
		// pode enviar diversas chamadas, Se não enviar, serão considerados
		// os valores padrão referentes ao tipo de janela criada.
		// Cada tipo tem suas características e mesmo que o solicitante
		// não seja específico nos detalhes ele terá a janela do tipo que deseja.	
		
        //  
        //@todo: Pode-se refinar os parâmetros da janela na estrutura.
		//NewWindow->
		//...
		
		//@todo: Não registrar, quem criou que registre a janela.
		//RegisterWindow(NewWindow);
		
		// #importante
		// Se a tarefa atual está pintando, vamos melhorar a sua prioridade.
		// Possivelmente a thread de controle da janela é a thread atual.
		
		t = (void *) threadList[current_thread];
		
		set_thread_priority ( t, PRIORITY_HIGH4 );
		
		NewWindow->control = t;
		
		return (unsigned long) NewWindow;
	};	
}


// Coloca um char usando o 'terminal mode' de stdio.
// selecionado em _outbyte.
// stdio_terminalmode_flag = não transparente.
// Chama função interna.

void servicesPutChar ( int c ){
	
	int cWidth = get_char_width ();
	int cHeight = get_char_height ();
	
	if ( cWidth == 0 || cHeight == 0 )
	{
		//#debug
		printf ("servicesPutChar: fail w h ");
		die();
	}
	
    stdio_terminalmode_flag = 1;  
	
	putchar ( (int) c );
	refresh_rectangle ( g_cursor_x * cWidth, g_cursor_y * cHeight, 
		cWidth, cHeight );
	
	stdio_terminalmode_flag = 0;  
}
 
 
// Envia uma mensagem para a thread atual.
// #todo: Isso deveria ir para o IPC.
void services_send_message_to_thread ( unsigned long msg_buffer, int tid )
{	
    unsigned long *buffer = (unsigned long *) msg_buffer;

	struct thread_d *t;
	
	//#importante
	//Temos que checar o endereço andes de acessá-lo.
	
	
	if ( tid < 0 || tid >= THREAD_COUNT_MAX )
	{
	    printf ("114: services_send_message_to_corrent_thread: Fail, tid \n");
		refresh_screen ();
		return;
	}
			
    if ( &buffer[0] == 0 )
	{
	    printf ("114: services_send_message_to_corrent_thread: Fail, null pointer\n");
		refresh_screen ();
		return;
		
	}else{
				
		t = (void *) threadList[tid];
				
	    if ( (void *) t != NULL )
        {
            if ( t->used == 1 && t->magic == 1234 )
			{					    
			    t->window = (struct window_d *) buffer[0];
			    t->msg = (int) buffer[1];
			    t->long1 = (unsigned long) buffer[2];
			    t->long2 = (unsigned long) buffer[3];
				
				//sinalizando que temos uma mensagem.
			    t->newmessageFlag = 1; 
			};
		};
	};	
}



//
// End.
//

