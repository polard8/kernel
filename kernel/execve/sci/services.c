/*
 * File: execve\sci\services.c 
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
 *   + services: (public)
 *   + servicesChangeProcedure: (private)
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



//
// Protótipos de funções internas.
//

void servicesPutChar ( int c );
void servicesChangeProcedure();


//
//...
//

/*
 * services:
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
 *
 * 
 */
void *services( unsigned long number, 
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

	//
	// @todo: 
	//     Antes de utililizar as dimensões da área de trabalho
	//     vamos atribuir valores negligenciados para as dimensões.
	//
	
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
	
	// Se a área de trabalho for válida, usaremos suas dimensões, 
	// caso não seja, temos um problema.
	
	if (gui->main == NULL)
	{
		printf("services: main");
		die();
	};		
	
	// ## Limits. ## 
	// (Limites do número do serviço).
	
	// #bugbug
	// obs: Estamos checando se uma variável unsigned long é menor que zero.
	//     Isso  não é necessário.
	
	if ( number < 0 || number > SERVICE_NUMBER_MAX )
	{
	    return NULL;	
	};
	
	//
	// ## Create Window ##
	//
	
	// Serviço especial. Antes dos outros.
	if ( number == SYS_118 )
	{		
		//Aciona a flag.
	    //Se a flag tiver acionada, os argumentos usarão os valores 
	    //que foram configurados aqui.
		cwFlag  = 1234;
        
		cwArg1 = message_address[0];     //Type. 		
        cwArg2 = message_address[1];     //WindowStatus 
        cwArg3 = message_address[2];     //view
		
		cwArg4 = (char *) message_address[3];    //a4 Window name.
		
		cwArg5 = message_address[4]; //x
		cwArg6 = message_address[5]; //y
		cwArg7 = message_address[6]; //width
		cwArg8 = message_address[7]; //height
		
		//parent window.
		//message_address[8];
		//cwArg9 = gui->screen;  //@todo: O argumento arg4 está enviando parent window. 		
		cwArg9 = (struct window_d *) message_address[8];  //parent
		
		//onde?
		//message_address[9];
		//cwArg10 = arg4;  //desktop ID 		
		
		cwArg11 = message_address[10];    //cor da area de cliente.
		cwArg12 = message_address[11];    //cor da janela.
		
		goto do_create_window;		
	};
	

	//Number.
	switch (number)
	{
	    //0 - Null, O processo pode ser malicioso.
	    case SYS_NULL: 
	        systemRam(0,0,0,0,0); 
	        break; 	   
		
		//Disco: 1,2,3,4
		
		//1 (i/o) Essa rotina pode ser usada por um driver em user mode.
		case SYS_READ_LBA: 
		    //@todo: chamar hal
			//systemDevicesUnblocked(36,arg2,arg3,0,0); 
		    //read_lba( (unsigned long) arg2, (unsigned long) arg3 );
			my_read_hd_sector( (unsigned long) arg2 , (unsigned long) arg3, 0 , 0 ); 
			break;
			
		//2 (i/o) Essa rotina pode ser usada por um driver em user mode.
		case SYS_WRITE_LBA: 
		    //@todo: chamar hal
			//systemDevicesUnblocked(35,arg2,arg3,0,0); 
			//write_lba( (unsigned long) arg2, (unsigned long) arg3 );
			my_write_hd_sector( (unsigned long) arg2 , (unsigned long) arg3, 0 , 0 ); 
		    break;

		//3 fopen (i/o)
		case SYS_READ_FILE:
		    taskswitch_lock();
	        scheduler_lock();	
			//name , address.
            Ret = (void *) fsLoadFile ( (unsigned char *) a2, 
			                (unsigned long) arg3 );      
		    //fopen( const char *filename, const char *mode );
		    //??retorno ??? 1 = fail ; 0=ok.
			scheduler_unlock();
	        taskswitch_unlock();
			return (void *) Ret;
			break;

		//4 (i/o)
		case SYS_WRITE_FILE:
		    taskswitch_lock();
	        scheduler_lock();	
		    
			fsSaveFile ( (char *) message_address[0],         //name
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
			
		//6
		//Put pixel. 
        //Coloca um pixel no backbuffer.
        //Isso pode ser usado por um driver. 
        //cor,x,y,0		
        case SYS_BUFFER_PUTPIXEL:
            //my_buffer_put_pixel ( (unsigned long) a2, 
			//    (unsigned long) a3, (unsigned long) a4, 0 );   		
            backbuffer_putpixel ( (unsigned long) a2, 
			    (unsigned long) a3, (unsigned long) a4, 0 );   		
			break;

		//7
		//desenha um char no backbuffer.
		//Obs: Esse funciona, não deletar. :)
		// (x,y,color,char)
		// (left+x, top+y,color,char)
		//devemos usar o left e o top da janela com foco d3e entrada.
        //
		// Obs: A biblioteca c99 em user mode usa essa chamada para pintar um caractere
		// quando implementa a função printf(.). Porém esse caractere é pintado
		// na janela com o foco de entrada. A intenção é que o carctere seja pintado 
		// na própria janela do aplicativo.
		// Outro caso é a digitação de caractere. Quando um caractere é
		// digitado desejamos que ele seja pintado na janela com o foco de entrada.
		//
		// ?? Quando um carctere é pintado em uma janela que não está com o foco 
		//    de entrada ?? ex: shells, logs ...
		//
		//Supondo que os aplicativos escreverão mais em terminal por enquanto 
		//a cor padrão de fonte será a cor de terminal.
		//	
		// Aqui está pintando o caractere na janela com o foco de entrada.
		case SYS_BUFFER_DRAWCHAR:
			focusWnd = (void *) windowList[window_with_focus];
			if( (void *) focusWnd == NULL ){ 
			    break; 
			};
			
			my_buffer_char_blt( (unsigned long) (focusWnd->left + arg2),             //x.
			                    (unsigned long) (focusWnd->top + arg3),              //y.
								CurrentColorScheme->elements[csiTerminalFontColor],  //color. 
								(unsigned long) arg4); 								 //char.
			break;

		//8 @todo: BugBug, aqui precisamos de 4 parâmetros.
        case SYS_BUFFER_DRAWLINE:
			my_buffer_horizontal_line ( (unsigned long) a2, 
			    (unsigned long) a3, (unsigned long) a4, COLOR_WHITE ); 		
			break;

		//9 @todo: BugBug, aqui precisamos de 5 parâmetros.
        case SYS_BUFFER_DRAWRECT:
            drawDataRectangle( 0, (unsigned long) a2, (unsigned long) a3, 
				(unsigned long) a4, COLOR_WHITE );    		
			break;

		//10 Create window.
		// O argumento mais importante é o tipo.
		//Função principal na criação de janelas via systemcall
        case SYS_BUFFER_CREATEWINDOW: 
			cwArg1 = arg2;               //arg2 Type. 
            cwArg3 = arg3;               //arg3 view
			cwArg4 = (char *) a4;        //arg4 Window name.
			goto do_create_window;
            break;
			
			
		//11, Coloca o conteúdo do backbuffer no LFB.
        case SYS_REFRESHSCREEN: 
		    //systemRam ( 3, 0, 0, 0, 0 ); 
			refresh_screen ();
			break;			
			
        //rede: 12,13,14,15			
		//i/o:  16,17,18,19	
        //Outros: 20 até o fim.		

		//34	
        case SYS_VIDEO_SETCURSOR: 
		    systemRam(86,arg2,arg3,0,0); 
			//set_up_cursor( (unsigned long) arg2, (unsigned long) arg2);
			break;              

		//35 - Configura o procedimento da tarefa atual.
        case SYS_SETPROCEDURE:  
            g_next_proc = (unsigned long) arg2;		
            break;
			
		//36
        //O teclado envia essa mensagem para o procedimento ativo.
        case SYS_KSENDMESSAGE: 
            systemRam ( 2, (unsigned long) arg2, (unsigned long) arg3, 
			    (unsigned long) arg4, 0 ); 
            break;    
      
	
		//37 - Chama o procedimento procedimento default. @todo return.
		case SYS_CALLSYSTEMPROCEDURE: 
            system_procedure(NULL,arg2,arg3,arg4);	
            break;    
        
	
	    // ## CANCELADA! ##
        //42 Load bitmap 16x16.
		case SYS_LOADBMP16X16 :       
            return NULL;			
            break;


        //45 Message Box. 
        case SYS_MESSAGEBOX:		
            //MessageBox(gui->screen, 1, (char *) a3, (char *) a4 );        
            return NULL;
			break;
		
        //47, Create Window support.		
        //envia argumentos de controle.
		case SYS_BUFFER_CREATEWINDOWx:
		    //cwFlag  = 1234;  //Aciona a flag.
            //cwArg2  = arg2;  //WindowStatus 
			//cwArg11 = arg3;  //cor da area de cliente.
			//cwArg12 = arg4;  //cor da janela.
			return NULL;
			break;
		
		//48, Create Window support.
		//envia argumentos de posicionamento.
		case SYS_BUFFER_CREATEWINDOW1:
		    //cwArg5 = arg2;  //x
			//cwArg6 = arg3;  //y
			//cwArg9 = gui->screen;  //@todo: O argumento arg4 está enviando parent window.    
			return NULL;
			break;
		
		//49, Create Window support.
		//envia argumentos de dimensões.
		case SYS_BUFFER_CREATEWINDOW2:
		    //cwArg7 = arg2; //width
			//cwArg8 = arg3; //height
			//cwArg10 = arg4;  //desktop ID 
			return NULL;
			break;	
			
		//50~59 Window suppot, manipulação de janelas	

		//50 resize window (handle,x,y)
		case SYS_BUFFER_RESIZEWINDOW:		
		    return (void *) resize_window( (struct window_d*) arg2, arg3, arg4);
		    break;
		
		//51 redraw window. (handle)
		case SYS_BUFFER_REDRAWWINDOW:
		    return (void *) redraw_window ( (struct window_d*) arg2, arg3 );
		    break;
		
		//52  replace window. (handle,x,y)
		case SYS_BUFFER_REPLACEWINDOW:
		    return (void *) replace_window( (struct window_d*) arg2, arg3, arg4);
		    break;
		
		//53 maximize window 
		case SYS_BUFFER_MAXIMIZEWINDOW:
		    //(handle)
		    MaximizeWindow((struct window_d*) arg2);
		    break;
		
		//54 minimize window
		case SYS_BUFFER_MINIMIZEWINDOW:
		    //(handle)
		    MinimizeWindow( (struct window_d *) arg2);
		    break;
		
		//55 Get foreground window.
		case SYS_BUFFER_GETFOREGROUNDWINDOW:
		    return (void *) windowGetForegroundWindow();
		    break;
		
		//56 set foreground window.
		case SYS_BUFFER_SETFOREGROUNDWINDOW:
		    return (void *) windowSetForegroundWindow((struct window_d*) arg2);
		    break;
		
		
		//57.	
		case SYS_REGISTERWINDOW: 
		    systemRam(41,(unsigned long) hWnd,0,0,0); 
			break;
			
		//58.	
		case SYS_CLOSEWINDOW: 
		    systemRam(53,(unsigned long) hWnd,0,0,0); 
			break;
			
        //60
		case SYS_SETACTIVEWINDOW:			
			set_active_window(hWnd);
			break;

        //61
		case SYS_GETACTIVEWINDOW:
            return (void *) get_active_window();    //Id. (int).		
			break;

        //62
		case SYS_SETFOCUS: 
		    systemRam(71,(unsigned long) hWnd,0,0,0); 
			break;
			
        //63 id
		case SYS_GETFOCUS: 
		    return (void *) window_with_focus;  
			break;
			
        //64
		case SYS_KILLFOCUS:
            //KillFocus(window);		
		    systemRam(73,(unsigned long) hWnd,0,0,0); 
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
			servicesPutChar ( (int) arg2 );		
			break;

		//66 - reservado pra input de usuário.
		//case 66:
        //    systemDevicesUnblocked( (int)1, (unsigned long) arg1, 
		//       (unsigned long) arg2, (unsigned long) arg3, (unsigned long) arg4);  		
		//	break;

		//67- reservado pra input de usuário.	
		//case 67:
        //    systemDevicesUnblocked( (int)1, (unsigned long) arg1, 
		//        (unsigned long) arg2, (unsigned long) arg3, (unsigned long) arg4);  		
		//	break;

		//68- reservado pra input de mouse.	
		//case 68:
        //    systemDevicesUnblocked( (int)1, (unsigned long) arg1, 
		//        (unsigned long) arg2, (unsigned long) arg3, (unsigned long) arg4);  		
		//	break;

		//	
		//69 - Driver de teclado enviando mensagem de digitação.	
		//     Não somente um driver, mas qualquer processo pode enviar
		// uma mensagem pra janela com o foco de entrada e chamar o procedimento.
		// >>>> Enviando para a classe certa.
        // arg2=msg, arg3=ch, arg4=ch 0		
		//
		case 69:
			systemDevicesUnblocked ( (int) 3, (unsigned long) arg2, (unsigned long) 
			    arg3, (unsigned long) arg4, 0);  		
			break;
			
		//
        // ## EXIT ##
        //		
			
		// 70 - Exit. Torna zombie a thread atual.
        // Tornando zombie a thread atual se o argumento for 0.		
		// Na verdade tem muitos parametros de proteção pra levar em conta.
		// #todo: Podemos chamar uma rotina, que terá um switch que trate o argumento.
		// ex: do_sys_exit(arg2);
		// #obs: É isso que o aplicativo está chamando quando quer sair. Então 
		// se for a thread primária do aplicativo, então tem fechar tudo o que ele 
		// estiver usando.
		
		case SYS_EXIT:
			
			//0 = Estamos saindo de aplicativo normalmente, sem erros.
			if (arg2 == 0)
			{ 
			    sys_exit_thread (current_thread); 
				break; 
			}; 	 		
            
			//if(arg2 == 1){ sys_exit_process(arg3,arg4); break; };  //Process.
			
			//...
			
			break;
		
        //71 		
		case SYS_FORK: 
		    return (void *) do_fork_process ();
			break;	

		//72 - Create thread.	
        case SYS_CREATETHREAD:			
			return (void *) create_thread( 
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
            return (void *) create_process ( NULL, NULL, NULL, 
			                    arg2, arg3, 0, (char *) a4, 
								RING3, (unsigned long ) CreatePageDirectory() ); 		
            break;
			
		//80 Show current process info.
		//#todo: Mostrar em uma janela própria.
		//#todo: Devemos chamar uma função que mostre informações 
		//apenas do processo atual. 
		case SYS_CURRENTPROCESSINFO:
		    show_currentprocess_info ();
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
		    return (void *) Down ( (struct semaphore_d *) arg2);
		    break;
			
		//Testa se o processo é válido
        //se for válido retorna 1234		
		//testando...
		case SYS_88:   
            return (void *) processTesting (arg2);			
			break;
			
		//Up. 89	
		case SYS_SEMAPHORE_UP:
		    return (void *) Up ( (struct semaphore_d *) arg2 );
		    break;
		
		//90 Coletor de threads Zombie. (a tarefa idle pode chamar isso.)		
		case SYS_DEADTHREADCOLLECTOR: 
		    systemIoCpu ( 1, 0, 0, 0, 0 ); 
			break;
			
		//94	
		//REAL (coloca a thread em standby para executar pela primeira vez.)
		// * MOVEMENT 1 (Initialized --> Standby).
		case SYS_STARTTHREAD:
		    t = (struct thread_d *) arg2;
            SelectForExecution (t);    	
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
		    return (void *) systemDevicesUnblocked ( 43, 
			                    arg2, arg2, arg2, arg2 );
		    break;
			
		//#bugbug
		//**** 44, Pega 'msg' na fila da janela com o foco de entrada.
		//Pegando a mensagem na fila da janela com o foco de entrada.
		case SYS_GETKEYBOARDMESSAGE:
		    return (void *) systemDevicesUnblocked ( 44, 
			                    (unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus );
			break;
			
		//**** 45,  Pega 'long1' na fila da janela com o foco de entrada.	
		case SYS_GETLONG1:
		    return (void *) systemDevicesUnblocked ( 45, 
			                    (unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus );
			break;
			
		//**** 46,  Pega 'long2' na fila da janela com o foco de entrada.	
		case SYS_GETLONG2:
		    return (void *) systemDevicesUnblocked ( 46, 
			                    (unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus, 
								(unsigned long) WindowWithFocus);
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
			systemReboot();
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
		
		// #test
		// A intenção agora é pegar a mensagem na estrutura de thread atual.
		// Desse modo cada aplicativo, quando estiver rodando, pegará as 
        // suas mensagens em sua própria fila.  		
		
		case 111:
		    if ( &message_address[0] == 0 )
			{
				printf("111: null pointer");
				die();
				
			}else{
				
			    t = (void *) threadList[current_thread];
			    
				//#bugbug:
				//temos que checar a validade da janela.
				
	            if ( (void *) t == NULL )
	            {
		           return NULL;
	            }
				
				//se Não há mensagens.
				if( t->newmessageFlag != 1 )
				{
                    // Se não há mensagens na estrutura da janela,
					// então devemos alimentar a estrutura para
					// que da próxima vez exista alguma mensagem.
					// Nossas opções são o teclado, pois o próprio mouse 
					// alimentará por si só a estrutura da janela.
					
					//alimentando através de mensagens de teclado
			        
					//pega o sccancode.
					SC = (unsigned char) keybuffer[keybuffer_head];
					
					//renova a fila do teclado
		            keybuffer[keybuffer_head] = 0;
					keybuffer_head++;
					if ( keybuffer_head >= 128 ){ 
				        keybuffer_head = 0; };
			        
                    //isso coloca a mensagem na fila da thread atual.
	
	                KEYBOARD_LINE_DISCIPLINE ( SC );	
                    
					//LINE_DISCIPLINE chama uma função para colocar a mensagem 
					// na estrutua da janela com foco de entrada. 
					//#todo, mas agora deverá 
					//colocar na estrutura da thread atual.
					
					//sinalizando, mas acho que o ldisc já faz isso.
					//#importante: LINE_DISCIPLINE faz isso. 
					//t->newmessageFlag = 1;  					
			
			        return NULL; //sinaliza que não há mensagem 
				}
				
				if( t->newmessageFlag == 1 )
				{
	
					//pegando a mensagem.
			        message_address[0] = (unsigned long) t->window;
			        message_address[1] = (unsigned long) t->msg;
			        message_address[2] = (unsigned long) t->long1;
			        message_address[3] = (unsigned long) t->long2;
                    
					//sinalizamos que a mensagem foi consumida.
                    t->newmessageFlag = 0; 					
				    
					return (void *) 1; //sinaliza que há mensagem
				}
			};
		    break;
		
		//Envia uma mensagem PAINT para o aplicativo atualizar a área de trabalho.
		case 113:
		    windowUpdateWindow( (struct window_d *) arg2 );
			break;
			
		// 114	
        // ## ENVIA UMA MENSAGEM PARA UMA JANELA ##
		
		//enviar uma mensagem para a thread atual.
		//
		case SYS_SENDWINDOWMESSAGE:
		    if ( &message_address[0] == 0 )
			{
				printf("114: null pointer");
				die();
			}else{
				
				//hWnd = (struct window_d *) message_address[0];
				//hWnd = (void *) windowList[window_with_focus];
				t = (void *) threadList[current_thread];
				//if ( (void *) == NULL )
				//{
				//	return NULL;
				//}
				//temos que checar a validade.
				if ( (void *) t != NULL )
                {
                    if ( t->used == 1 && t->magic == 1234 ){					
				        
						t->window = (struct window_d *) message_address[0];
				        t->msg = (int) message_address[1];
				        t->long1 = (unsigned long) message_address[2];
				        t->long2 = (unsigned long) message_address[3];
				
				        //sinalizando que temos uma mensagem.
				        t->newmessageFlag = 1; 
					};
			    };
			};
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
		    return (void *) windowSelectColorScheme ( (int) arg2 );
			break;
		
		//
		// 129, Um driver confirmando que foi inicializado.
		// Efetuaremos a rotina de ligação do driver com o sistema.
		// O sistema linka o driver com o sistema operacional.
	    //@todo: Essa rotina precisa ser aprimorada. Mas a chamada deve ser 
		// essa mesma.
		//
		case SYS_DRIVERINITIALIZED: 
		    return (void *) systemLinkDriver(arg2,arg3,arg4); 
			break;
			
		//130
		case SYS_DRAWTEXT:
		    
			//@todo: Podeira pintar na janela atual.
			argString = (unsigned char *) arg4;
		    draw_text ( (struct window_d *) message_address[0], //window
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
			
			my_buffer_char_blt( (unsigned long) (arg2 + focusWnd->left), //x.
			                    (unsigned long) (arg3 + focusWnd->top),  //y.
								COLOR_BLACK,                             //color. 
								(unsigned long) arg4);                   //char.
    		break;
			
			
		//134
		//pegar informações sobre a área de cliente de uma janela;
		case 134:
		        hWnd = (struct window_d *) arg2;
                if ( (void *) hWnd != NULL )
                {	
                    //#bugbug: temos que checar mais validade de estrutura.
					
					//obs: No começo dessa função, colocamos o arg3 como ponteiro para a3.
					//um buffer de longs.
					
		    	    a3[0] = (unsigned long) hWnd->rcClient->left;
			        a3[1] = (unsigned long) hWnd->rcClient->top;     
			        a3[2] = (unsigned long) hWnd->rcClient->width;
			        a3[3] = (unsigned long) hWnd->rcClient->height;
					a3[4] = (unsigned long) hWnd->rcClient->bg_color;
					//...
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
			
		//137
		// Isso é usado pela biblioteca stdio em user mode
		// na função 'getchar()'
		// #bugbug: Não está pegando todos os caracteres digitados.
		// window.c
		
		//#test
		//#bugbug: a partir de agora isso deve pegar mensagem na thread 
		//atual e não mais na janela com foco de entrada.
        case SYS_GETCH:  
		    //return (void *) window_getch();
			return (void *) thread_getchar();
            break;

		//138 - get key state.	
        case 138:
		    return (void *) keyboardGetKeyState ( (unsigned char) arg2 );
            break;		
			
		//139
        case SYS_GETSCANCODE:
		    return (void *) get_scancode();
            break;		

        //140
        case SYS_SET_CURRENT_KEYBOARD_RESPONDER:
            set_current_keyboard_responder(arg2);		
		    break;
			
		//141	
		case SYS_GET_CURRENT_KEYBOARD_RESPONDER:
		    return (void *) get_current_keyboard_responder();
		    break;
			
		//142	
        case SYS_SET_CURRENT_MOUSE_RESPONDER:			
		    set_current_mouse_responder(arg2);
			break;
			
		//143	
		case SYS_GET_CURRENT_MOUSE_RESPONDER:
		    return (void *) get_current_mouse_responder();
			break;

			
		//144	
		//Pega o ponteiro da client area.	
		case SYS_GETCLIENTAREARECT:	
		    //#bugbug: pegamos o ponteiro mas não temos permissão para acessar a estrutura.
			return (void *) getClientAreaRect();	
			break;
		
		//145
        //configura a client area	
        //@todo: O ponteiro para estrutura de retângulo é passado via argumento.		
		case SYS_SETCLIENTAREARECT:
			setClientAreaRect ( arg2, arg3, arg4, 0);
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
		    return (void *) grid ( (struct window_d *) arg2, 
			                (int) arg3, (int) arg4 );
            break;		

        //test. menu.
		case 149:
            //essa é uma rotina de teste, qua chama várias funções.
			MainMenu ( (struct window_d *) arg2 );		
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
		
		case 167:
		    // Testar
			//executive.c
		    return (void *) executive_gramado_core_init_execve( 0,  //serviço 
			                (const char *) arg2,                //name
			                (const char *) arg3,                //(arg)(endereço da linha de comando)
							(const char *) arg4 );              //env
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
			
		//160
		//Criar um socket e retornar o ponteiro para a estrutura.
		case 160:
            return (void *) create_socket ( (unsigned long) arg2, (unsigned short) arg3 );
			break;
			
		//161
        //get socket IP		
		case 161:
		    return (void *) getSocketIP( (struct socket_d *) arg2 );
            break;		

		//162
        //get socket port		
		case 162:
		    return (void *) getSocketPort( (struct socket_d *) arg2 );
            break;		
			
		//163
        //update socket  
        //retorno 0=ok 1=fail		
        case 163:
            return (void *) update_socket ( (struct socket_d *) arg2, (unsigned long) arg3, (unsigned short) arg4 );
			break;		

        //case 164:
        //    break;		
			
		//170
        //pwd ...
        //?? mostra p pathname gerenciado pelo kernel 
        //para o diretório de trabalho.		
		case SYS_PWD:
			fs_print_process_pwd (current_process);
			//printf("\n %s \n\n", current_workingdiretory_string );
			//refresh_screen();
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
            fsListFiles ( arg2, arg3, arg4 );  
			break;
			
			
		//174
		case SYS_SEARCHFILE:
		    return (void *) KiSearchFile ( (unsigned char *) arg2, 
                                (unsigned long) arg3 );
			break;
			
		//175	
		//atualizar string no pathname do pwd. 
        //em argumento veio o que se deve acrescentar.		
		case 175:
		    fsUpdateWorkingDiretoryString ( (char *) arg2 );
			break;
			
		//176	
		//atualizar string no pathname do pwd. 
        //em argumento veio a quantidade de diretórios a se retirar.		
		//apaga n quantidade de nomes de diretórios 
		//começando do último.
		case 176:	
		    fs_pathname_backup ( current_process, (int) arg3 );
			break;
			
		//177
		//comando dir no shell.
		//Listando arquivos em um diretório dado o nome.	
		case 177:
		    fsList ( (const char *) arg2 );
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
            return (void *) GetProcessHeapStart ( (int) arg2 );
			break;		
			

		//199 - Garbage Collector.	
		//A ideia é que os utilitários de gerência de memória possam usar isso.
		case SYS_GC:
		    gc ();
			//return (void *) gc (); 
		    break;
		
		//200 - Envia um sinal para um processo.	
		//argumentos (process handle, signal number).
		case SYS_SENDSIGNAL:
		    signalSend ( (void *) a2, (int) arg3 );
		    break;
			
		//...	
			
		//210
		case SYS_CREATETERMINAL: 
            break;
		//211
        case SYS_GETCURRENTTERMINAL:
            return NULL;
			break;
			
	    //212
        case SYS_SETCURRENTTERMINAL:
            break;
			
		//213
        case SYS_GETTERMINALINPUTBUFFER:	
            return NULL;
			break;
			
		//214
        case SYS_SETTERMINALINPUTBUFFER:		
		    break;
			
		//215
		//retorna o ID.
		case SYS_GETTERMINALWINDOW: 
		    return (void *) systemGetTerminalWindow(); 
		    break;
			
		//216
        //configura qual vai ser a janela do terminal. 		
		case SYS_SETTERMINALWINDOW:	
		   systemSetTerminalWindow ( (struct window_d *) arg2 );	
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
		    return (void *) create_timer ( (struct window_d *) arg2, (unsigned long) arg3, (int) arg4 );
		    break;

		
        //223 - get sys time info.
        // informações variadas sobre o sys time.		
		case 223:
		    return (void *) get_systime_info ( (int) arg2 );
            break;		
			
		//224 - get time	
		case SYS_GETTIME:	
		    return (void *) get_time();
			break;
			
		//225 - get date
		case SYS_GETDATE:
		    return (void *) get_date();
            break;		
			
			
		//Obs: @todo: poderia ser uma chamada para configurar o posicionamento 
        //e outra para configurar as dimensões.		
			
		//226 get
        case SYS_GET_KERNELSEMAPHORE:
            return (void *) __ipc_kernel_spinlock;
            break;
        
        //227 close critical section	
		case SYS_CLOSE_KERNELSEMAPHORE:
		    __ipc_kernel_spinlock = 0;
			return;
			break;
			
		//228 open critical section
		case SYS_OPEN_KERNELSEMAPHORE:
		    __ipc_kernel_spinlock = 1;
			return;
            break;
			
		//240
		case SYS_GETCURSORX:
		    return (void *) get_cursor_x();
		    break;

		//241
		case SYS_GETCURSORY:
		    return (void *) get_cursor_y();
		    break;
			
		//244 enable text cursor.	
		case 244:
		    timerEnableTextCursor ();
		    //timerShowTextCursor = 1;
		    //gwsEnableTextCursor ();
            break;		
		
		//245 disable text cursor.
		case 245:
		    timerDisableTextCursor ();
		    //timerShowTextCursor = 0;
		    //gwsDisableTextCursor ();
            break;		
			
		//Info. (250 ~ 255).
		
		//250
		//Get system metrics
		case SYS_GETSYSTEMMETRICS:
		    return (void *) systemGetSystemMetrics ( (int) arg2 );
		    break;
		
		//251
		//Informações sobre o disco atual.
		case SYS_SHOWDISKINFO:
		    diskShowCurrentDiskInfo();
			refresh_screen();
			break;

		//252
		//Informações sobre o volume atual.
		case SYS_SHOWVOLUMEINFO:
		    volumeShowCurrentVolumeInfo();
			refresh_screen();
			break;
		
		//253
		case SYS_MEMORYINFO:
		    memoryShowMemoryInfo();
			refresh_screen();
			break;
			
			
		//254 - Show PCI info.	
		case SYS_SHOWPCIINFO: 
			systemShowDevicesInfo();
			refresh_screen();
			break;
			
		//255 - Mostra informações sobre o kernel.	
		case SYS_SHOWKERNELINFO: 
			KiInformation();
			refresh_screen();
			break;
			
		//
		// @todo:
		// Need to check the system call ID to ensure it’s valid…
		// If it’s invalid, return ENOSYS “Function not implemented” error
		//
		
		default:	
			printf ("services: Default {%d}\n", number );
			//#todo: retorno.
			//return NULL;
			break;
	};
	
	//Debug.
	//printf("SystemService={%d}\n",number);
    
	
	// * importante:
	//   Depois de esgotados os 'cases', saltamos para a saída da função.
	
	goto done;	

// * Aviso: #Importante.
//
// Juntando os argumentos para a função CreateWindow(.).
// Nesse caso, antes de chamarmos a função CreateWindow, vamos juntar
// todos os argumentos que ela precisa. Mas o que acontece é que
// estamos na rotina de serviços que o kernel oferece via API.
// Qual será a estratégia para conseguirmos os argumentos.
// >> Quando um aplicativo em user mode chamar CreateWindow, 
// a rotina da API deve fazer 4 system calls, as 3 primeiras passando 
// os argumentos e a última criando a janela.
// >> do_create_window: é acionada depois de passados todos os argumentos. 
	
	
//
// ## Create window ##
//

do_create_window:	
	
	//?? @TODO
	//if(WindowType >= 0 || WindowType <= 5){
	//	
	//}	
	
	// @todo: bugbug.
	// Obs: A parent window é 'gui->screen'. Talvez essa estrutura nem esteja 
    // inicializada ainda no ambiente de logon.
	// Obs: O usuário só pode criar janelas na área de trabalho do desktop atual.
    // @todo: A área de trabalho do desktop atual pode ser representada por
    // uma estrutura de retângulo na estrutura do desktop e/ou uma estrutura de
    // retângula na estrututra gui->.
    //      ...

	//
	// *Importante: Checando se o esquema de cores está funcionando.
	//
	
	if ( (void *) CurrentColorScheme == NULL )
	{
		printf("services: CurrentColorScheme");
		//refresh_screen();
		die ();
		
		//while(1){}
	
	}else{
		
		if ( CurrentColorScheme->used != 1 || 
		     CurrentColorScheme->magic != 1234 )
		{
		    
			printf("services: CurrentColorScheme validation");
		    //refresh_screen();
		    die();
			
			//while(1){}			
		};
		//Nothing.
	};
	
	//
	// Nesse momento estamos atribuindo a cor padrão de janelas 
	// para as janelas que criadas pelos aplicativos através de system calls.
	// Não há problema nisso por enquanto.
	//
	
	//
	// *Podemos aceitar as opções de cores passadas por argumento.
	//  principalmente a cor da área de cliente.
	//
	
	//*Importante
	//definimos as cores psdrão caso a flag esteja desligada.
	WindowColor = CurrentColorScheme->elements[csiWindowBackground];  
	WindowClientAreaColor = CurrentColorScheme->elements[csiWindow];  

	// * Primeira coisa a fazer é ver se os argumentos estão disponíveis.
	//   Vamos conferir a flag que indica que argumentos foram enviados 
	//   previamente.
	
	// Se a flag tiver acionada, os argumentos usarão os valores 
	// que foram previamente passados
	
	if (cwFlag == 1234)
	{		
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
		WindowColor = (unsigned long) cwArg12;            //a cor da janela escolhida pelo app. 
	};	
	

    //
    // Importante:
	// Nesse momento é fundamental saber qual é a parent window da janela que vamos criar 
	// pois a parent window terá as margens que nos guiam.
	// Essa parent window pode ser uma aba de navegador por exemplo.
	// >> O aplicativo deve enviar o ponteiro da janela mãe.
    //	
	
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
	    return NULL; 
		
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
		
		//
		// Se a tarefa atual está pintando, vamos melhorar a sua prioridade.
		//
		
		t = (void *) threadList[current_thread];
		
		set_thread_priority( t, PRIORITY_HIGH4);
		
	    return (void *) NewWindow; 
	};

//More ...
//xxx:
//yyy:
//zzz:

    //    No caso de um aplicativo ter chamado essa rotina, 
	// o retorno será para o ISR da int 200, feito em assembly.
    //    No caso do kernel ter chamado essa rotina, apenas retorna.
	
//Done.
done:
    //Debug.
    //printf("Done\n",number);
	//refresh_screen();
    return NULL;	
};


/*
 ** Essa é outra forma de implementar o handler de system call 
 ** Podemos usar em outra interrupção usda pela api.
 ** Credits: Nelson Cole.

#define SYSCALL_NUM 5

unsigned int num;


static void *syscall_table[] = {
	 write_clear,		// eax, 0   Limpar tela
	&write_char, 		// eax, 1   imprime um caracter na tela
	&write_string, 		// eax, 2   imprime uma string na tela
	&write_int,  		// eax, 3   imprime valor inteiro decimal na tela
	&write_hexa		// eax, 4   imprime volor inteiro hexadecimal na tela
};

void syscall_handler()
{
	__asm__ __volatile__("              \
	                      push %%eax;   \
	                      add $4, %%esp;\
	                      ":"=r"(num): );
						  
    if(num <= SYSCALL_NUM)
	{
        void *addr = syscall_table[num];

	    __asm__ __volatile__ ("               \
	                           push %%ebx;    \
	                           push %%ecx;    \
	                           push %%edx;    \
	                           call *%0;      \
	                           add $12, %%esp \
	                           "::"r"(addr));
	}else{
	    
		//set_color(4);
	    //printk("Invalid syscall: eax,%d INT 80\n",num);
	    //set_color(0xF);
    };

	return;
};
 */


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
		printf("servicesPutChar: fail w h ");
		die();
	}
	
    stdio_terminalmode_flag = 1;  
	
	putchar ( (int) c );
	refresh_rectangle ( g_cursor_x * cWidth, 
	                    g_cursor_y * cHeight, 
						cWidth, 
						cHeight );
	
	stdio_terminalmode_flag = 0;  

    //
	// Update cursor
	//
	/*
    //Limites para o número de caracteres numa linha.
    if ( g_cursor_x >= (g_cursor_right-1) )
	{
        g_cursor_x = g_cursor_left;
        g_cursor_y++;  
		
    }else{   
	
	    //
		// ## Incremento ##
		//
		
		// Apenas incrementa a coluna. 
        g_cursor_x++;                          
    };
    
	
	//Número máximo de linhas. (8 pixels por linha.)
    if( g_cursor_y >= g_cursor_bottom )  
    { 
	    scroll();
        g_cursor_y = g_cursor_bottom;
    };	
	*/

}; 
 
 
/*
 * servicesChangeProcedure:
 *     Função interna. 
 *     Atende a interrupção 201, mudando o procedimento de janela atual.
 *     @todo: Passar argumento via registrador. ??
 *     @todo: Outra função já esta fazendo isso, deletar essa.
 */
void servicesChangeProcedure (){
	
	//return;
};


//
// Fim.
//

