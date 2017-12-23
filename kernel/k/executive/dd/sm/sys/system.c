/*
 * sm - System Management -  Esse é o console do sistema.
 * Seu objetivo principal é receber os comandos de gerenciamento,
 * enviados por usuários atráves de dispositivos de interface humana. 
 *
 * Note duas coisas importantes aqui: 
 * o 'console' é a interface de administração do sistema, e é ele é 
 * acessado através de um emulador de terminais utilizando-se drivers TTY.
 *
 * File: system.c
 *
 * Obs: CADA CLASSE PODE TER UMA BIBLIOTECA EM USER MODE.
 *      UM UMA INTERRUPÇÃO PRÓPRIA EX: system1(....).
 *
 * Sugestões para nomes de bibliotecas em user mode:
 * ================================================
 * ramlib.o  - Classe Ram. 
 * iocpulib.o - Classe Io.Cpu
 * iodmalib.o - Classe Io.Dma
 * dunblocked.o - Classe Devices.Unblocked
 * dblocked.o - Classe Devices.Blocked
 * things.o - Classe .Things.
 *
 * Ambiente:
 *     /executive/sm/sys/system.c
 *     Kernel base. Ring0.
 *
 * Descrição:
 *     Arquivo principal do módulo de gerenciamento do sistema.
 *     Esse módulo está em kernel mode, no kernel base.
 *     Rotinas de gerenciamento do sistema.
 *
 * Obs: Pode-se aprender muito com a comunidade opensource(linux), principalmente
 *      nas questões que apresentam maior dificuldade, dadas as obstruções
 *      impostas pela indústria mainstream, como gerenciamento de energia
 *      protocolos e barramentos.
 *
 * Obs:
 *     Sobre a sondagem de dispositivos nos barramentos do sistema:
 *     Sondar os dispositivos seguindo a ordem de velocidade, so mais veloz
 *     para o menos veloz, exemplo: CPU, Memória, PCIE, South Bridge, Super IO ...
 *
 * @todo:
 *     Criar um serviço, (servidor), em user mode que configure o sistema. As 
 * aplicações e utilitários em user mode poderão usar esse serviço. Obs: O servidor
 * em user mode poderá chamar serviços oferecidos por esse módulo aqui.
 * 
 * @todo: AS ROTINAS DE CLASSES NO COMEÇO DESSE MÓDULO DEVEM EXECUTAR SOMENTE
 *        DEPOIS DE UMA CHECAGEM DE PERMISSÕES. PERMISSÕES DE NÍVEL. UM PROCESSO
 *        DEVE TER A MESMA PERMISSÃO DE NÍVEL DO SERVIÇO QUE ELE DESEJA. (K0~K5).
 *
 * In this file:
 *     +Strings padronizadas e definitivas. Para uso interno.
 *     +systemShowDevicesInfo
 *     +systemCreateSystemMenuBar
 *     +systemStartUp - Rotinas de inicialização do sistema.  
 *     +systemSetupVersion
 *     +system_dispatch_to_procedure - Chama o procedimento atual.
 *     +SystemMenu
 *     +SystemMenuProcedure
 *     +systemReboot
 *     +systemShutdown
 *
 * Histórico:
 *    Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *    Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas. 
 *    //...
 */

 
#include <kernel.h>


//
// Informações herdadas do boot.
//


extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

 
//Variáveis internas.
//int systemStatus;
//int systemError;
//... 


/*
    Sobre os diretórios e arquivos do sistema:
    Os nomes dos diretórios e arquivos do sistema ficarão aqui
	como forma de registro oficial. os módulos poderão reproduzir
	o nome presente aqui ou poderão solicitar um ponteiro para o nome.
	@todo: funções aqui nesse arquivo retornarão o ponteiro para o nome de arquivo
	desejado.
	...
 */
 
/*
 *     **** Diretórios do sistema. ****  obs:(8.3)
 *
 * * Obs: O esquema de diretórios ainda esta em fase de planejamento.
 */

//Geral para todas as versoes do sistema operacional 
static char *systemPathNameRoot      = "/root";               //Raiz.
static char *systemPathNameSDK       = "/root/sdk";           //*SDK. 
static char *systemPathNameBoot      = "/root/boot";          //Boot. 
static char *systemPathNameDevices   = "/root/devices";       //Devices. 
static char *systemPathNameUsers     = "/root/users";         //Usuários.
static char *systemPathNameApps      = "/root/apps";          //Aplicações.
static char *systemPathNameTemp      = "/root/temp";          //Arquivos temporários.
static char *systemPathNameDownloads = "/root/dl";            //Arquivos temporários.
static char *systemPathNameTrash     = "/root/trash";         //Lixeira. 
//...

//OSs: versoes. 
static char *systemPathNameOS1 = "/root/os";   //OS1. Principal (atual)
static char *systemPathNameOS2 = "/root/os1";  //OS2.
static char *systemPathNameOS3 = "/root/os2";  //OS3.
static char *systemPathNameOS4 = "/root/os3";  //OS4.
//...
 
//Diretórios do sistema principal. 
static char *systemPathNameOS1Boot           = "/root/os/boot";            //boot.
static char *systemPathNameOS1BootFont       = "/root/os/boot/font";       //boot font.
static char *systemPathNameOS1System         = "/root/os/system";          //* Diretório do sistema.
static char *systemPathNameOS1SystemFont     = "/root/os/system/font";            //fontes do sistema.
static char *systemPathNameOS1SystemDrivers  = "/root/os/system/drivers";  //Drivers do sistema.
static char *systemPathNameOS1SystemSecurity = "/root/os/system/security";    //Fontes sistema.
//...


/*
 * Arquivos do sistema:
 *     os principais arquivos do sistema, padronizados e nunca mudarão.
 *
 */

//alguns são provisórios nessa fase de desenvolvimento. 
static char *systemInitFilePathName = "/root/INIT.TXT";  //"/root/init.txt";
static char *systemLogFilePathName  = "/root/log.txt";
//static char *systemInitFilePathName = "/root/log.txt";
//static char *systemInitFilePathName = "/root/log.txt";
//static char *systemInitFilePathName = "/root/log.txt";
//static char *systemInitFilePathName = "/root/log.txt";
static char *systemSwapFilePathName      = "/root/swap";  //'Arquivo' de paginação.
//... 

//Listas.
//unsigned long systemFileListX[128];
//unsigned long systemFileListXX[128];


//Informações sobre a memória do sistema
//não uasr ponteiro.
//struct memory_info_d systemMemoryInfo;



/*
 * Classes:
 *     O que segue são as funções principais do Kernel. São seis rotinas 
 * chamadoras de serviços.
 * 
 * @todo: Esse esquema de rotians de serviços organizadas em classe precisa 
 * ser replicado para outros sistemas, mesmo em user mode.
 *
 * 1) systemRam
 * 2) systemIoCpu
 * 2) systemIoDma
 * 3) systemDevicesUnblocked
 * 3) systemDevicesBlocked
 * 4) systemThings
 *
 * Obs: *** ESSAS CLASSES SERÃO A PRINCIPAL PORTA DE ENTRADA PARA OS UTILITÁRIOS. ***
 *
 */

 
//
// 1) system.ram
//    São os serviços oferecidos pelo executive.
//    que lidam com a ram e não com os dispositivos de armazenamento.
//
void *systemRam( int number, 
                 unsigned long arg1,
		         unsigned long arg2,
		         unsigned long arg3,
		         unsigned long arg4 )
{
    //@todo: filtrar limites.	
	switch(number)
	{
		//Esse serviço é apenas retornar NULL.
		case 0: 
		    return systemNull(); 
			break;

		//Kernel info.
		case 1: sys_showkernelinfo(); break;

		//Despacha uma mensagem para o procedimento atual.
		case 2:
		    g_nova_mensagem = 1; //existe uma nova mensagem.
            system_dispatch_to_procedure( (struct window_d *) arg1, (int) arg2, (unsigned long) arg3, (unsigned long) arg4);
		break;
		
		//refresh screen (executive: ram| uigm/gui)
		case 3: refresh_screen(); break;
			
		//set up cr3. /ram/mm	
		case 4: SetCR3((unsigned long) arg1); break;
			
		//create page directory.	
		case 5:
		    //void *CreatePageDirectory(unsigned long directory_address);
		    return (void *) CreatePageDirectory((unsigned long) arg1);
            break; 

		//create page table.	
        case 6:
            //void *CreatePageTable( unsigned long directory_address, int offset, unsigned long page_address );
			return (void *) CreatePageTable( (unsigned long) arg1, (int) arg2, (unsigned long) arg3 );
            break;

		//show memory structs.	
        case 7:
		    show_memory_structs();
            break;		

		//Pega o heap pointer de um processo.	
        case 8:
		    //unsigned long get_process_heap_pointer(int pid);
			return (void *) get_process_heap_pointer((int) arg1);
            break;		

		//create channel.	
        case 9:
            //void *CreateChannel(struct d_process *OwnerProcess,
		    //		    struct d_thread *ClientThread,
		    //		    struct d_thread *ServerThread);
            return (void *)CreateChannel( (struct process_d *) arg1, (struct thread_d *) arg2, (struct thread_d *) arg3);
            break;
			
		//Destroy channel.	
        case 10:			
            //int DestroyChannel( struct channel_d *channel );
		    return (void *) DestroyChannel( (struct channel_d *) arg1 );
            break; 

		//Open channel.
		case 11:
            //int OpenChannel(struct channel_d *channel, 
            //struct d_process *OwnerProcess,
			//struct d_thread *ClientThread,
			//struct d_thread *ServerThread);
            return (void *) OpenChannel( (struct channel_d *) arg1, (struct process_d *) arg2, (struct thread_d *) arg3, (struct thread_d *) arg4);
		    break;
		
		//Close channel.
		case 12:
            //int CloseChannel(struct channel_d *channel);
			return (void *) CloseChannel( (struct channel_d *) arg1);
		    break;

		//Load file.
		case 13:
		    //@todo: Isso não pertence a essa categoria, pertence a classe devices.
			//unsigned long fsLoadFile( unsigned char *file_name, unsigned long file_address);
            return (void *) fsLoadFile( (unsigned char *) arg1, (unsigned long) arg2);		
            break;
		
		//Save file.
        case 14:
		    //@todo: Isso não pertence a essa categoria, pertence a classe devices.
		    //unsigned long fsSaveFile( unsigned char *file_name, 
            //                  unsigned long file_size, 
		    //				  unsigned long file_address );		
		    return (void *) fsSaveFile( (unsigned char *) arg1, (unsigned long) arg2, (unsigned long) arg3 );				    
			break;
		
		//Create user.
		case 15:
            //void *CreateUser(char *name, int type);
			return (void *) CreateUser( (char *) arg1, (int) arg2);
			break;
			
		//Set current user id.	
		case 16: SetCurrentUserId( (int) arg1); break;
	   
        //Get current user id.
		case 17:
		    //int GetCurrentUserId();
			return (void*) GetCurrentUserId();
			break;
			
		//Set current group id.	
		case 18: SetCurrentGroupId( (int) arg1); break;
		
		//Get current group id.
		case 19:
		    //int GetCurrentGroupId();
		    return (void*) GetCurrentGroupId();
		    break;
			
		//Show user info.
		case 20:
		    //ShowUserInfo(int user_id);
			ShowUserInfo( (int) arg1 );
			break;
			
        //Desktop support:
		case 21:
            return (void*) RegisterDesktop( (struct desktop_d *) arg1);  			
            break;
        case 22: set_current_desktop( (struct desktop_d *) arg1); break;
		
		case 23:
		    //void *get_current_desktop();
		    return (void *) get_current_desktop();
            break;

        case 24:		
		    //int get_current_desktop_id();
		    return (void*) get_current_desktop_id();
            break;

        case 25:		
		    //void *CreateDesktop(struct wstation_d *ws);
		    return (void *) CreateDesktop( (struct wstation_d *) arg1 );
            break;
		
		case 26:
		    //void set_current_menuwindow(struct desktop_d *desktop, struct window_d *window); 
 		    set_current_menuwindow( (struct desktop_d *) arg1, (struct window_d *) arg2); 
            break;
		
		case 27:
		    //void set_current_foreground(struct desktop_d *desktop, struct window_d *window); 
		    set_current_foreground( (struct desktop_d *) arg1, (struct window_d *) arg2); 
		    break;
		
		case 28:
		    //void set_current_messagewindow(struct desktop_d *desktop, struct window_d *window); 
		    set_current_messagewindow( (struct desktop_d *) arg1, (struct window_d *) arg2); 
		    break;
		
        case 29:
		    //void set_current_traywindow(struct desktop_d *desktop, struct window_d *window); 
		    set_current_traywindow( (struct desktop_d *) arg1, (struct window_d *) arg2); 
		    break;

		case 30:	
		    //void set_current_tooltipwindow(struct desktop_d *desktop, struct window_d *window); 
		    set_current_tooltipwindow( (struct desktop_d *) arg1, (struct window_d *) arg2);
            break;		

		case 31:
		    //void change_foreground(struct desktop_d *desktop);
            change_foreground( (struct desktop_d *) arg1);
            break;

		case 32:
		    //void set_current_sysMenu(struct desktop_d *desktop, struct menu_d *menu);
		    set_current_sysMenu( (struct desktop_d *) arg1, (struct menu_d *) arg2);
		    break;
		
		case 33:
		    //void set_current_dialogsysMenu(struct desktop_d *desktop, struct menu_d *menu);
		    set_current_dialogsysMenu( (struct desktop_d *) arg1, (struct menu_d *) arg2);
            break; 
		 
		case 34:
		    //void set_current_menuHScroll(struct desktop_d *desktop, struct menu_d *menu);
		    set_current_menuHScroll( (struct desktop_d *) arg1, (struct menu_d *) arg2);
		    break;
		
		case 35:
		    //void set_current_menuVScroll(struct desktop_d *desktop, struct menu_d *menu);
		    set_current_menuVScroll( (struct desktop_d *) arg1, (struct menu_d *) arg2);
            break;

        //Menu support:
		
        case 36:
		    // create_menu_item: Menus são verticais.
            //int create_menu_item(struct menu_d *menu, unsigned char *string, int status);
            return (void*) create_menu_item( (struct menu_d *) arg1, (unsigned char *) arg2, (int) arg3);
            break;        
		
		case 37:
            //void *create_menu( struct window_d *pwindow,    //Parent window. 
            //                   unsigned long iCount,        //Contagem de ítems. 
            //				   unsigned long sCount,        //Contagem de espaçadores.
            //				   int type,                    //Horizontal ou vertical.
            //				   int style );                 //Estilo.
            return (void *) create_menu( (struct window_d *) arg1,  //Parent window. 
                                         (unsigned long) arg2,      //Contagem de ítems. 
        				                 (unsigned long) arg3,      //Contagem de espaçadores.
        				                 (int) arg4,                //Horizontal ou vertical.
         				                 (int) 0);                  //Estilo.
			break;

        //User session suport:

        case 38:
		    //void *CreateUserSession(int userID); 
		    return (void *) CreateUserSession( (int) arg1); 
		    break;

		case 39:
            //void *get_current_user_session();
            return (void *) get_current_user_session();
			break;


        //Window support:

		//40
		//CreateWindow: Cria uma janela com base em um tipo.
		case 40:
           //void *CreateWindow( unsigned long type,  //1 - tipo de janela (popup ..normal ...)
           //unsigned long status,           //2  - estado da janela (ativa ou nao)
           //unsigned long view,             //3  - (min, max ...)
           //char* windowname,               //4  - titulo                                
           //unsigned long x,                //5  - deslocamento em relação às margens do desktop(sua instancia)        
           //unsigned long y,                //6  - idem
           //unsigned long width,            //7  - largura da janela  
           //unsigned long height,           //8  - altura
           //struct window_d *pWindow,       //9  - id da janela mae, se for zero, essa é a janela mae.
           //unsigned long onde,             //10 - (qual desktop)
           //unsigned long arg11,            //11 - ? reservado
           //unsigned long color             //12 - cor do bg (para janelas simples, tipo 1)
           //);

            return (void *) CreateWindow( (unsigned long) arg1,  //1 - tipo de janela (popup ..normal ...)
                                          (unsigned long) arg2,  //2  - estado da janela (ativa ou nao)
                                          (unsigned long) 0,     //3  - (min, max ...)
                                          (char*) arg3,          //4  - titulo                                
                                          (unsigned long) 0,     //5  - deslocamento em relação às margens do desktop(sua instancia)        
                                          (unsigned long) 0,     //6  - idem
                                          (unsigned long) 0,     //7  - largura da janela  
                                          (unsigned long) 0,     //8  - altura
                                          (struct window_d *) arg4,  //9  - id da janela mae, se for zero, essa é a janela mae.
                                          (unsigned long) 0,         //10 - (qual desktop)
                                          (unsigned long) 0,         //11 - ? reservado
                                          (unsigned long) 0          //12 - cor do bg (para janelas simples, tipo 1)
                                        );
			break;

		case 41:	
            //int RegisterWindow(struct window_d *window);
            return (void*) RegisterWindow( (struct window_d *) arg1);
			break;
			
		case 42: set_current_window( (struct window_d *) arg1); break;
			
		case 43:	
            //void *get_current_window();
            return (void *) get_current_window();
			break;
			
		case 44:	
            //int resize_window(struct window_d *window, unsigned long cx, unsigned long cy);		  
            return (void *) resize_window( (struct window_d *) arg1, (unsigned long) arg2, (unsigned long) arg3 );		  
            break;
			
		case 45:	
			//int replace_window(struct window_d *window, unsigned long x, unsigned long y);
			return (void *) replace_window( (struct window_d *) arg1, (unsigned long) arg2, (unsigned long) arg3 );
			break;

		//...
		
		case 46:	
            //int redraw_window(struct window_d *window);
            return (void*) redraw_window( (struct window_d *) arg1);
			break;

		case 47:
		    //int is_window_full(struct window_d *window);
		    return (void*) is_window_full( (struct window_d *) arg1);
			break;

		case 48:
		    //int is_window_maximized(struct window_d *window);
		    return (void*) is_window_maximized( (struct window_d *) arg1);
            break;
			
		case 49:
		    //int is_window_minimized(struct window_d *window);
		    return (void*) is_window_minimized( (struct window_d *) arg1);
			break;
			
		case 50:
		    //int get_active_window();
		    return (void*) get_active_window();
            break;
			
		//Window support.	
		case 51: set_active_window( (struct window_d *) arg1); break;
		case 52: change_active_window( (int) arg1); break;
		case 53: CloseWindow( (struct window_d *) arg1 ); break;
		case 54: DestroyWindow( (struct window_d *) arg1); break;
		case 55: CloseActiveWindow(); break;
		case 56: MinimizeWindow( (struct window_d *) arg1 ); break;
		case 57: MaximizeWindow( (struct window_d *) arg1 ); break;
		case 58: windowShowWindowList(); break;
		case 59: show_window_with_focus(); break;
		case 60: show_active_window(); break;
		case 61: refresh_screen(); break;
		case 62: windowSwitchFocus(); break;
		case 63: windowLock( (struct window_d *) arg1); break;
		case 64: windowUnlock( (struct window_d *) arg1); break;			
		
		case 65:
		    return (void*) windowCreateDedicatedBuffer( (struct window_d *) arg1);
			break;

        
		case 66:
			//void pixelPutPixelDedicatedWindowBuffer( struct window_d *window, 
            //                                         unsigned long x, 
            //										 unsigned long y, 
            //										 unsigned long color );

			pixelPutPixelDedicatedWindowBuffer( (struct window_d *) arg1, 
                                                (unsigned long) arg2, 
            								    (unsigned long) arg3, 
            									(unsigned long) arg4 );
			break;
         
		case 67: 
           //void pixelPutPixelWindowBuffer( void* buffer, 
           //                          unsigned long x, 
           //						  unsigned long y, 
           //						  unsigned long color );

           pixelPutPixelWindowBuffer( (void*) arg1, 
                                      (unsigned long) arg2, 
           						      (unsigned long) arg3, 
           						      (unsigned long) arg4 );
		   break;

        case 68:
            //void draw_text( struct window_d *window,
            //                unsigned long x,  
            //                unsigned long y,  
            //				unsigned long color, 
            //				unsigned char *string );

            draw_text( (struct window_d *) arg1,
                       (unsigned long) arg2,  
                       (unsigned long) arg3,  
            		   (unsigned long) COLOR_TEXT, 
            		   (unsigned char *) arg4 );
			break;


		//...
		
		//Background.
		case 69: backgroundDraw( (unsigned long) arg1); break;
		   
        case 70:
            //void *getClientAreaRect();
            return (void *) getClientAreaRect();
		    break;
			
		//Set focus on a window.	
        case 71: SetFocus( (struct window_d *) arg1 ); break;
			
		//Pega o id da janela com o foco de entrada.
        case 72: 
            return (void*) GetFocus();
			break;
			
		//Kill window focus.	
        case 73: KillFocus( (struct window_d *) arg1 ); break;
			
        case 74:
            //void MessageBox( struct window_d *parent_window, int type,char *title, char *string);
            MessageBox( (struct window_d *) arg1, (int) arg2, (char *) arg3, (char *) arg4);
			break;
			
        case 75:  
            //void DialogBox(struct window_d *parent_window, int type, char *title, char *string);
            DialogBox( (struct window_d *) arg1, (int) arg2, (char *) arg3, (char *) arg4);
			break;
			
        case 76:
            //void draw_button( struct window_d *window,
            //                  unsigned char *string, 
            //                  unsigned long type, 
            //                  unsigned long x, 
            //                  unsigned long y, 
            //                  unsigned long width, 
            //                  unsigned long height, 
            //                  unsigned long color);

            draw_button( (struct window_d *) arg1,
                         (unsigned char *) arg2, 
                         (unsigned long) arg3, 
                         (unsigned long) 0, 
                         (unsigned long) 0, 
                         (unsigned long) 0, 
                         (unsigned long) 0, 
                         (unsigned long) arg4);
		    break;
			
        case 77:
            //int StatusBar(struct window_d *window, unsigned char *string1, unsigned char *string2);
            return (void*) StatusBar( (struct window_d *) arg1, (unsigned char *) arg2, (unsigned char *) arg3);
            break;
			
        case 78: 
            //void *create_menubar(struct window_d *pwindow); 
            return (void *) create_menubar( (struct window_d *) arg1); 
            break;
			
        case 79:  
            //int create_menubar_item(struct menu_d *menu, unsigned char *string, int status);
            return (void*) create_menubar_item( (struct menu_d *) arg1, (unsigned char *) arg2, (int) arg3);
		    break;
		
        case 80:
            //int draw_menubar_item( struct window_d *window, unsigned char *string);
            //return (void*) draw_menubar_item( (struct window_d *) arg1, (unsigned char *) arg2);
            break;
			
     //Window station support: (desktop pools.)

	    case 81:
            //int RegisterWindowStation(struct wstation_d *ws);
            return (void*) RegisterWindowStation( (struct wstation_d *) arg1);
            break;
			
        case 82:
            //void set_current_windowstation(struct wstation_d *ws);
            set_current_windowstation( (struct wstation_d *) arg1);
            break;
			
        case 83:
            //void *get_current_windowstation();
            return (void *) get_current_windowstation();
		    break;
			
        case 84:
            //void *CreateWindowStation(struct usession_d *s);
            return (void *) CreateWindowStation( (struct usession_d *) arg1);
		    break;

        //mini-shell support: (minishel do kernel base.)

	    case 85: 
	        //int shellMain(int argc, char *argv[]);
	        //return (void*) shellMain( (int) arg1, (char *) arg2);
		    break;
			
        //cursor support:
    
	    case 86:
	        //void set_up_cursor(unsigned long x, unsigned long y);
	        set_up_cursor( (unsigned long) arg1, (unsigned long) arg2);
		    break;
			
	    case 87:
	        return (void*) get_cursor_x();
		    break;
			
	    case 88:
			return (void*) get_cursor_y();
            break;			
	
        // ss signal support:
    
	    case 89:
	        //int signalSend(struct process_d *process ,int signal);
	        return (void*) signalSend( (struct process_d *) arg1, (int) arg2);	
		    break;
			
		//...	
		
		default:
		    return systemNull(); 
		    break;
		
	};  //fim do switch.
	
done:
    return NULL;			   
};		   
 
 
//
// 2) system.io.cpu
//     serviços do microkernel referentes à cpu.
//     process, threads, cpu ... 
//     Especialmente transferencia RAM <--> Devices.
//
void *systemIoCpu( int number, 
                   unsigned long arg1,  
		           unsigned long arg2,  
		           unsigned long arg3,  
		           unsigned long arg4 )
{
    //
	
	switch(number)
	{
		case 0:
		    return systemNull(); 
			break;

		//Dead thread collector.
		case 1: sys_dead_thread_collector(); break;

		//Create process.	
		case 2:
		    //return (void *) create_process( NULL, NULL, NULL, arg2, arg3, 0, (char *) a4);
		    break;
		
		//Create thread.
		case 3:
		    //return (void*) create_thread( NULL, NULL, NULL, arg2, arg3, 0, (char *) a4);
		    break;
			
		//Fork	
		case 4:
		    return (void*) sys_fork();    //(id) retorno (int).
            break;


        //...			
		
        //Process support:

        case 5:
		//process_descriptor_t *create_process( struct wstation_d *window_station,
        //                               struct desktop_d  *desktop,
        //                               struct window_d *window,
        //                               unsigned long init_eip, 
        //                               unsigned long priority, 
	    //								int ppid, 
	    //								char *name);

        return (void*) create_process( (struct wstation_d *) 0,
                                       (struct desktop_d  *) 0,
                                       (struct window_d *) 0,
                                       (unsigned long) arg1, 
                                       (unsigned long) arg2, 
	    							   (int) arg3, 
	    							   (char *) arg4);
		break;

	

	    case 6:
	    //int processSendSignal(struct process_d *p, unsigned long signal);		
	    return (void*) processSendSignal( (struct process_d *) arg1, (unsigned long) arg2 );		
	    break;
	
	    case 7:
	    //unsigned long GetProcessDirectory(struct process_d *process);
	    return (void*) GetProcessDirectory( (struct process_d *) arg1);
	    break;
	
	    case 8:
	    //void SetProcessDirectory(struct process_d *process, unsigned long Address);		
	    SetProcessDirectory( (struct process_d *) arg1, (unsigned long) arg2 );		
	    break;
	
	    //Close all processes.
	    case 9: CloseAllProcesses(); break;
	
	    //?? Dead process collector. ??
        case 10: dead_task_collector(); break;
	
        //Exit process.	
	    case 11: exit_process( (int) arg1, (int) arg2); break;
	
	    //Set caller PID.
	    case 12: set_caller_process_id( (int) arg1 ); break;
	
	    case 13:
	    //int get_caller_process_id();	
	    return (void*) get_caller_process_id();		
	    break;
	
        //Semaphore support.
	    case 14: Down( (struct semaphore_d *) arg1); break;
	    case 15: Up( (struct semaphore_d *) arg1); break;
		
	    case 16:
	    //int init_semaphore(struct semaphore_d *s, unsigned int count); 
	    return (void*) init_semaphore( (struct semaphore_d *) arg1, (unsigned int) arg2); 
	    break;
		
	    //Semaphore support.	
	    case 17: semaphore_down( (struct semaphore_d *) arg1); break;
	    case 18: semaphore_up( (struct semaphore_d *) arg1); break;
		
	    case 19:
	    //void *create_semaphore(); 
	    return (void *) create_semaphore(); 
	    break;
		
	    //Semaphore support.			
	    case 20: delete_semaphore( (struct semaphore_d *) arg1); break;
	    case 21: open_semaphore( (struct semaphore_d *) arg1); break;
	    case 22: close_semaphore( (struct semaphore_d *) arg1); break;
		
        //Thread support.
        case 23: dead_thread_collector(); break;
	    case 24: exit_thread( (int) arg1); break;  //Torna zunbi uma thread.
	    case 25: kill_thread( (int) arg2); break;  //Destrói uma thread.
	
	    case 26:
	    //int GetCurrentThreadId();
	    return (void*) GetCurrentThreadId();
	    break;
	
	    //Select a thread for execution.
	    case 27: SelectForExecution( (struct thread_d *) arg1); break;
	
	    case 28:
	    //unsigned long GetThreadStackStart(struct thread_d *thread);
	    return (void *) GetThreadStackStart( (struct thread_d *) arg1);
	    break;
	
	    case 29:
	    //unsigned long GetThreadHeapStart(struct thread_d *thread);
	    return (void *) GetThreadHeapStart( (struct thread_d *) arg1);
	    break;
	
	    case 30:
	    //unsigned long GetThreadDirectory(struct thread_d *thread);
	    return (void *) GetThreadDirectory( (struct thread_d *) arg1);
	    break;
	
	    //?? Quem tem directory é o processo.
	    case 31:
	    //void SetThreadDirectory(struct thread_d *thread, unsigned long Address);
	    SetThreadDirectory( (struct thread_d *) arg1, (unsigned long) arg2);
	    break;
		
	    case 32:
	    //thread_descriptor_t *create_thread( struct wstation_d *window_station,
        //                                    struct desktop_d  *desktop,
        //                                    struct window_d *window,
        //                                    unsigned long init_eip, 
        //                                    unsigned long priority, 
        //									int pid, 
        //									char *name);
	    
		return (void*) create_thread( (struct wstation_d *) 0,
                                      (struct desktop_d  *) 0,
                                      (struct window_d *) 0,
                                      (unsigned long) arg1, 
                                      (unsigned long) arg2, 
 									  (int) arg3, 
									  (char *) arg4);
        break;


        case 33:
        //void *GetCurrentThread();
        return (void *) GetCurrentThread();
	    break;
	
	    case 34:
	    //void *FindReadyThread();
	    return (void *) FindReadyThread();
	    break;
	
	    case 35:
	    //int GetThreadState(struct thread_d *Thread);
	    return (void *) GetThreadState( (struct thread_d *) arg1);
	    break;
	
	    case 36:
	    //int GetThreadType(struct thread_d *Thread);
	    return (void *) GetThreadType( (struct thread_d *) arg1);
	    break;
	
	    //Dispatch a thread.
	    case 37: dispatch_thread( (struct thread_d *) arg1); break;
	
	    //Set thread priority.
	    case 38: set_thread_priority( (struct thread_d *) arg1, (unsigned long) arg2); break; 
	
	    //...
	
		default:
		    return systemNull();
		    break;
		
	}; //fim do switch.
	
done:
    return NULL;			   
};		   
 
 
//
// 2) system.io.dma
//    serviços do microkernel referentes à dma.
// //     Especialmente transferencia RAM <--> Devices.
//
void *systemIoDma( int number, 
                   unsigned long arg1,  
		           unsigned long arg2,  
		           unsigned long arg3,  
		           unsigned long arg4 )
{
    //	
	switch(number)
	{
		case 0: 
		    return systemNull();
			break;

		case 1:
		break;

		case 2:
		break;
		
		default:
		    return systemNull();
		    break;
		
	}; //fim do switch.
	
done:
    return NULL;			   
};		    

 
//
// 3) system.devices.unbloqued
//
// Interação com sipositivos de fácil acesso, principalmente os legados.
//
void *systemDevicesUnblocked( int number,
                              unsigned long arg1,
		                      unsigned long arg2,
		                      unsigned long arg3,
		                      unsigned long arg4 )
{
	struct window_d *wFocus;

    //
	
	switch(number)
	{
		case 0: 
		    return systemNull();
			break;
		
		case 1:
		   //
		break;

		//Reboot via teclado.
		case 2: 
		    sys_reboot(); 
			break;

       /*
        * Recebendo mensagem de digitação vinda do driver de teclado ou
		* de outro lugar.
        * Não é atribuição do driver de teclado saber o destino das mensagens.
		* O que ele faz é passar a mensagem para esse serviço. Essa rotina
		* dará o destino certo para a mensagem identificando qual é a janela
		* com o foco de entrada e colocando a mensagem na sua fila dentro
		* da estrutura.
        * Obs: Isso funcionou, não alterar esse esquema, nem aqui, nem
		* no driver.
        * @todo: Criar uma rotina pra isso.
		* arg1=msg,arg2=ch,arg3=ch,arg4=0.
		*/
   		case 3:
		    // Just for test. (Imprimeindo o caractere.) Em qual janela??
			printf("%c", arg2);

            //
			// Procedimento do sistema. 
			// (Para mensagens de digitação, e controles do sistema.)
			// Isso funcionou bem. Usar para teste.
			// *IMPORTANTE: O procedimento do sistema so interceptará O SYSTEM KEY DOWN.
			// DEIXANDO PARA A APLICAÇÃO AS OUTRAS MENSAGENS.
			// NESSA FASE DE DESENVOLVIMENTO, O PROCEDIMENTO DO SISTEMA TEM QUE INTERCEPTAR
			// ALGUMA COISA SENÃO FALTARÁ COMUNICAÇÃO.
			//
			system_procedure( NULL, 
			                  (int) arg1, 
							  (unsigned long) arg2, 
							  (unsigned long) arg3 );
			
			//
			// +Colocar a mensagem na estrutura da janela ativa. 
			// (Para mensagens de controle de janela, interceptadas pelo processo cliente).
			// +Fica por conta das aplicações sondarem se há mensagens na fila de mensagens
			// de sua janela, ou o processo poderá ser avisado sobre isso atravéz de um sinal.
			// +Os aplicativos devem deixar o sistema controlar as mensagens de digitação.
			// +O sistema imprime as digitações na área de cliente.
			//
			windowSendMessage( (unsigned long) arg1,
			                   (unsigned long) arg2,
							   (unsigned long) arg3,
							   (unsigned long) arg4 );

		    //
		    // Obs: *IMPORTANTE: 
			// O único procedimento que enviaremos mensagem é o procedimento 
			// do sistema. Os procedimentos de janela pegarão sua própria mensagem
            // na fila de mensagens ou serão alertados sobre a mensagem atravéz
            // de um sinal. 			
			//
			
			//
			// #bugbug: O procedimento de janela do sistema deve ser chamdo somente
			// depois que o procedimento de janela do processo retornar
			// Estamos chamando os dois procedimentos começando pelo procedimento 
			// do sistema.
			// * Importante: De toda forma eles interceptam mensagems diferentes.
			// As mensagens que são do sistema devem ser atendidas primeiro, por isso 
			//chamaremos o procedimento de janela do sistema antes que o processo solicite
			//alguma mensagem em sua estutura de janela.
			//
			
		    //Se for o procedimento padrão. 
	        //if( g_next_proc == (unsigned long) &system_procedure )
			//{
				//
				// O procedimento do sistema foi chamado com um 'call' porque está no kernel base.
				//
				
				//wFocus = (void *) WindowWithFocus;
				//janela=NULL,arg1=msg, arg2=ch,
			//	system_procedure( NULL, (int) arg1, (unsigned long) arg2, (unsigned long) arg3);
	        //};	
	        //Se NÃO for o procedimento padrão. 
	        //if( g_next_proc != (unsigned long) &system_procedure ){
		        //enviando a mensagem para a estrutura da janela com o foco de entrada.
		        //ao chamar a rotina ela encontra a janela com o foco de entrada.
		        //arg1=msg, arg2=ch, arg3=ch,
				//windowSendMessage((unsigned long) arg1, (unsigned long) arg2, (unsigned long) arg3, (unsigned long) arg4);		
		        
				//Chamando o procedimento.
				//@todo: Mas o ideal é nao chamar, ja que enviamos a mensagem para a estrutura.
			//	wFocus = (void *) WindowWithFocus;
			 //   if( (void*) wFocus != NULL )
			//	{
					//#bugbug @todo:
                    //Talvez um procedimento de janela em user mode não deva ser chamado.
					// o loop dentro do program em user mode, deve ver se se foi alertado
					// sobre a presença de uma mensagem, havendo uma mensagem, ele mesmo envia para
					//seu procedimento e em seguida retorna no loop. Assim continuamos
					//apenas com a thread principal do programa.
			//	    system_dispatch_to_procedure( wFocus, (int) arg1, (unsigned long) arg2, 0);
			//    };
				//
	        //};
			
        break;		
			

		//reservado para input de usuário.	
   		//case 4:
        //    break;		

		//reservado para input de usuário.
   		//case 5:
        //    break;		

		//reservado para input de usuário.
   		//case 6:
        //    break;		

		//reservado para input de usuário.
   		//case 7:
        //    break;		
			
	    //...

        //Port support: (não usar todas.) (algumas deveriam pertencer a classe io.)
        //Ports and instructions.

	    //case 8:
	    //int enable();
        //break;
	
	    //case 9:
	    //int disable(); //#bugbug perigoso.
        //break;
	
	    //case 10:
	    //int stopCpu();      
        //break; 
	
	    //case 11:
	    //int intReturn();
        //break;
	
	    //case 12:
	    //int farReturn();
        //break;
	
	    case 13: return (void *) getFlags( (int) arg1); break;
	
	    //case 14:
	    //int setFlags(int variable);
        //break;
	
	    case 15:
	    return (void*) kernelProcessorInPort8( (int) arg1, (int) arg2);
        break;
	
	    case 16:
	    return (void*) kernelProcessorOutPort8( (int) arg1, (int) arg2);
        break;
	
	    case 17:
	    return (void*) kernelProcessorInPort16( (int) arg1, (int) arg2);
        break;
	
	    case 18:
	    return (void*) kernelProcessorOutPort16( (int) arg1, (int) arg2);
        break;
	
	    case 19:
	    return (void*) kernelProcessorInPort32( (int) arg1, (int) arg2); 
        break;
	
	    case 20:
	    return (void*) kernelProcessorOutPort32( (int) arg1, (int) arg2);
        break;
	
	    //case 21:
	    //int Push(int value);
        //break;
	
	    //case 22:
	    //int Pop(int variable);
        //break;
	
	    //case 23:
	    //int pushRegs();
        //break;
	
	    //case 24:
	    //int popRegs();
        //break;
	
	    //case 25:
	    //int pushFlags();
        //break;
 
        //case 26:
	    //int popFlags();
        //break;
	
	    //case 27:
	    //int getStackPointer(int addr);
        //break;
	
	    //case 28:
	    //int setStackPointer(int addr);
        //break;
	
	    //Rotines.

	    //case 29:
	    //void init_cpu();
        //break;
	
	    case 30: return (void*) cpu_get_parameters(); break;
		
	    //case 31:	
	    //void get_cpu_intel_parameters();
        //break;
	
	    //case 32:	
	    //void get_cpu_amd_parameters();
        //break;
	
	    case 33: return (void*) KeTestCPU(); break;
	    case 34: show_cpu_intel_parameters(); break;

        // 
        // ide support: (hdd)
        //
	
	    //Write.
	    case 35:
		taskswitch_lock();
	    scheduler_lock();	
	    //void write_lba( unsigned long address, unsigned long lba);    //ide.
	    write_lba( (unsigned long) arg1, (unsigned long) arg2 );    //ide.
		scheduler_unlock();
	    taskswitch_unlock();			
        break;
	
	    //Read.
        case 36:
		taskswitch_lock();
	    scheduler_lock();	
        //address, lba
        read_lba( (unsigned long) arg1, (unsigned long) arg2);     //ide.
		scheduler_unlock();
	    taskswitch_unlock();			
        break;
	
	    //Read.
        case 37:
        my_read_hd_sector( (unsigned long) arg1, 
                           (unsigned long) arg2, 
						   (unsigned long) arg3, 
						   (unsigned long) arg4 );    
        break;

        //Write.
	    case 38:
        my_write_hd_sector( (unsigned long) arg1, 
                            (unsigned long) arg2, 
						    (unsigned long) arg3, 
						    (unsigned long) arg4 );    
        break;


	    //	
        //keyboard support:
        //
	
	    case 39: keyboard_set_leds( (char) arg1); break; //Set LEDs.
	    case 40: return (void*) get_alt_status(); break; //alt status.	
	    case 41: return (void*) get_ctrl_status(); break; //ctrl status.
	
	    //Input. (put in command buffer)
	    case 42: return (void*) input( (unsigned long) arg1); break;
		
	    //
        // 43,44,45,46 = Pegar nas filas os parâmetros hwnd, msg, long1, long2.
        //	
	
	    //msg.window
	    case 43:
	    //@todo: windowGetWindowPointer
        return NULL; //provisório.
		break;
	
	    //msg.msg Pega na fila de mensagens da janela com o foco de entrada.
	    case 44:
		    //O aplicativo passou um handle via argumento.
			// ?? mas esse handle é válido ??
	        return (void*) windowGetMessage( (struct window_d*) arg1 );
            break;
	
	    //msg.long1
	    case 45: 
		    //O aplicativo passou um handle via argumento.
			// ?? mas esse handle é válido ??
	        return (void*) windowGetLong1( (struct window_d*) arg1 );
		    break;
	
	    //msg.long2
	    case 46:
		    //O aplicativo passou um handle via argumento.
			// ?? mas esse handle é válido ??
	        return (void*) windowGetLong2( (struct window_d*) arg1 );
		    break;

	
	    //
        // cmos and rtc support:
        //
	
	    case 47: return (void*) read_cmos_bcd( (unsigned) arg1); break;
	    case 48: return (void*) get_time(); break; //time
	    case 49: return (void*) get_date(); break; //adte.
	
	    //Get total memory. 
	    case 50:
	    //return (void*) GetTotalMemory();
        break;
		
	    case 51: return (void*) get_cmos_info(); break;

	    //
        //screen support:
        //
	
	    case 52: return (void*) screenGetWidth(); break; //screen width.
	    case 53: return (void*) screenGetHeight(); break; //screen height.
	    case 54: screenRefresh(); break; //Refresh screen. (Backbuffer >> LFB.)
	
	    //
        // Video support:
        //
	
	    case 55: return (void*) videoGetMode(); break; 	//Get video mode.


        //...	
		
        default:
	        return systemNull();
			break;
		
	}; //Fim do switch.
	
	//... ??
	
done:
    return NULL;			   
};		   							  
 
 
//
// 3) system.devices.blocked
//
// Interação com dispositivos de difícil acesso, principalmente os modernos.
//
void *systemDevicesBlocked( int number, 
                            unsigned long arg1,  
		                    unsigned long arg2,  
		                    unsigned long arg3,  
		                    unsigned long arg4 )
{
    //	
	
	switch(number)
	{
		case 0: 
		    return systemNull();
			break;

		//Show PCI info.
		case 1: 
		    sys_showpciinfo(); 
			break;
	
	    //Shut down.
		case 2: 
		    systemShutdown(); 
			break;
			
		//mostra informações de dispositivos.	
		case 3:	
		    systemShowDevicesInfo(); 
			break;
			
		//...

	    //pci support:	
	
	
        //Read.

        case 4:    
	        //unsigned short pciConfigReadWord (unsigned char bus, 
            //                                  unsigned char slot, 
            //								  unsigned char func, 
            //								  unsigned char offset);

	        //return (void*) pciConfigReadWord ( (unsigned char) arg1, (unsigned char) arg2, (unsigned char) arg3, (unsigned char) arg4);
		    break;
		
        case 5:
	        //Offset 0.								  
            //unsigned short pciCheckVendor(unsigned char bus, unsigned char slot);
            //return (void*) pciCheckVendor( (unsigned char) arg1, (unsigned char) arg2);
		    break;
			
        case 6:
            //Offset 2.
            //unsigned short pciCheckDevice(unsigned char bus, unsigned char slot); 
            //return (void*) pciCheckDevice( (unsigned char) arg1, (unsigned char) arg2); 
		    break;
			
        case 7:
            //Offset 0x09.
            //unsigned char pciGetClassCode(unsigned char bus, unsigned char slot);
            //return (void*) pciGetClassCode( (unsigned char) arg1, (unsigned char) arg2);
		    break;
			
        case 8:
            //get BARs (vários offsets.)
            //unsigned long pciGetBAR(unsigned char bus, unsigned char slot, int number);
            //return (void*) pciGetBAR( (unsigned char) arg1, (unsigned char) arg2, (int) arg3);
		    break;
			
        //case 9:
           //pciGetInterruptLine: Get Interrupt Line, offset 0x3C.
           //break;
        
		case 10: 
            //unsigned char pciGetInterruptLine(unsigned char bus, unsigned char slot);		
            //return (void*) pciGetInterruptLine( (unsigned char) arg1, (unsigned char) arg2);		
            break;
	
        //ports support: (again)

	    case 11:
            //inline void koutportb(unsigned int port,unsigned int value);
            koutportb( (unsigned int) arg1, (unsigned int) arg2);
            break;
			
	    case 12:
            //inline unsigned char inportb(int port);
            //return (void*) inportb( (int) arg1);
			break;
			
	    case 13:
	        //int inport8(int port,int data); //fail
	        //int inport8(int port,int data); //fail
			break;
			
	    case 14:
	        //int outb(int port, int data);
	        outb( (int) arg1, (int) arg2);
			break;
			
	    case 15:
	       //int outport8(int port,int data);
	       outport8( (int) arg1, (int) arg2);
		   break;
		   
	    case 16:
	        //int inport16(int port,int data);
	        return (void*) inport16( (int) arg1 );
			break;
			
	    case 17:
	       //int outport16(int port,int data);
	       outport16( (int) arg1, (int) arg2);
           break;
		   
	    case 18:
	        //int inport32(int port,int data); 
	        return (void*) inport32( (int) arg1 ); 
			break;
			
		//Out port.	
	    case 19: outport32( (int) arg1, (int) arg2); break;
	    case 20: outportb( (int) arg1, (int) arg2); break;
			
	    case 21:
	        //inline unsigned long inportl(unsigned long port);
	        return (void*) inportl( (unsigned long) arg1 );
            break;
			
	    case 22: outportl( (unsigned long) arg1, (unsigned long) arg2); break;
	
		//..
		default:
		    return systemNull();
		    break;
		
	}; //fim do switch.
	
done:
    return NULL;			   
};

		   							
//
// 4) system.things
//
// Interação com dispositivos externos, principalmente os 
// os que enviam dados pela internet.
//
void *systemThings( int number, 
                    unsigned long arg1,  
		            unsigned long arg2,  
		            unsigned long arg3,  
		            unsigned long arg4 )
{
    //	
	switch(number)
	{
		case 0: 
		    return systemNull();
			break;

		case 1:
		break;

		case 2:
		break;
		
		default:
		    return systemNull();
		    break;
		
	}; //fim do switch.
	
done:
    return NULL;			   
};		   


//
// Outras ...
//


//Método interno..
void *systemNull(){
	return NULL;
};


/*
 * systemLinkDriver:
 *     Ligando um driver ao sistema operacional.
 */
void *systemLinkDriver( unsigned long arg1, 
                        unsigned long arg2, 
						unsigned long arg3 )
{
	MessageBox(gui->screen, 1, "systemLinkDriver:", "Linking a driver.." ); 
	//
done:
    refresh_screen();	
    return NULL; //@@todo: Inda não implementada.	
};


/*
 * systemShowDevicesInfo:
 *     Mostrar informações sobre o sistema, seguindo a ordem de
 *     velocidade dos dispositivos e barramentos.
 *
 *     Ex: CPU, Memória, PCIE (video), South Bridge, Super Io ...
 *     A Apresentação da sondágem pode ser feita em outra ordem,
 *     melhor que seja a ordem alfabética.
 */
void systemShowDevicesInfo()
{
	//
	//
	//
	
    //Título.
	printf("==== DEVICES: ==== \n\n");
    //...	
	
	//CPU Devices.
	printf("*** CPU Info *** \n\n");
	show_cpu_intel_parameters();
	//...
	
	//Memory Devices.
	printf("*** Memory Info *** \n\n");
	//...
	
	//PCIE Devices (Graphic cards)
	printf("*** Graphic Card Info *** \n\n");
	//...
	
	//PCI Devices.
	printf("*** PCI Devices *** \n\n");
	pciInfo();
	
	//Legacy ...
	printf("*** Legacy Devices Info *** \n\n");
	//...
	
	//
	// More ?!
	//
	
done:
    printf("done.\n");
	refresh_screen();
    return;
}; 
 

/*
 * systemCreateSystemMenuBar:
 *     Cria a barra de menu do sistema.
 *
 *  @todo: 
 *      Essas informações devem ser repassadas para "struct system_d".
 *
 */  
void *systemCreateSystemMenuBar()
{
	struct window_d * hwBar;                //Barra.
	//Left: (Software).
	struct window_d * hwItemSystem;         //Item (System).
	struct window_d * hwItemApplications;   //Item (Applications).  
	struct window_d * hwItemWindow;         //Item (Window).
	//Right: (Hardware)
	struct window_d * hwItemMore;    //Abre uma bandeija ou menu com mais opções.(V).
	struct window_d * hwItemClock;   //relógio.	
	
	if(gui->screen == NULL){
		return NULL;
	};
	
	 //Cria a barra no topo da tela.
	if(gui->screen != NULL){
		hwBar = (void*) create_menubar(gui->screen);
	};
	
	//
	// Deve-se criar a janela que servirá de parent window 
	// para os popup menus que aparecerão quando clicar no item.
	// Obs: Não importa qual dos tres ítems foi clicado,	
	//      a janela popupmenu será a mesma, 
	//
	
	hwItemSystem = (void*) CreateWindow( 1, 0, VIEW_MINIMIZED, "SystemMenuBar", 
	                               0, 60, (800/4), (600-60), 
							       gui->screen, 0, 0, COLOR_GRAY ); 
	if( (void*) hwItemSystem == NULL )
	{
		printf("systemCreateSystemMenuBar error: Struct.\n");
		refresh_screen();
	    while(1){};
		//return NULL;	    
	}
	else
	{
		hwItemSystem = (void *) hwItemSystem;
		hwItemApplications = (void *) hwItemSystem;
		hwItemWindow = (void *) hwItemSystem;
	    RegisterWindow(hwItemSystem);
		RegisterWindow(hwItemApplications);
		RegisterWindow(hwItemWindow);
	};	
	
	
done:
	return (void*) hwBar;
}; 
 

/*
 * systemCheck3TierArchitecture:
 * Checa o status dos serviços oferecidos nas 3 camadas.
 */
void systemCheck3TierArchitecture(){
    return; //@todo: Nothing for now.
};


/*
 * systemSetupVersion:
 *     Configurando os dados sobre versão.     
 */
void systemSetupVersion()
{
	//
	// Estrutura Version.
	//
	
    Version = (void*) malloc( sizeof(struct version_d) );
    if((void*) Version == NULL){	
	    printf("systemSetupVersion:");
		refresh_screen();
		while(1){};
	}else{	
        Version->Major = SYSTEM_VERSIONMAJOR;
		Version->Minor = SYSTEM_VERSIONMINOR;
		Version->Built = SYSTEM_VERSIONBUILT;
		Version->Revision = SYSTEM_VERSIONREVISION;
	};
	
	//
	// Estrutura VersionInfo.
	//
	
    VersionInfo = (void*) malloc( sizeof(struct version_info_d) );
    if((void*) VersionInfo == NULL)
	{	
	    printf("systemSetupVersion:");
		refresh_screen();
		while(1){};
	}
	else
	{
		if( (void*) Version != NULL  )
		{
            //VersionInfo->version = (void *) Version;
            //...VersionInfo->string = (char*) ...;
            //... 			
        };
		//...
	};
	
	
	//
	// Colocando na estrutura System se ela for válida.
	//
	
	if((void*) System != NULL)
	{
		if( System->used == 1 && System->magic == 1234 ){
			System->version      = (void *) Version;
			System->version_info = (void *) VersionInfo;
		};
		//Nothing
	};
	
	//More ?!
	
done:
    return;
};


/*
 * system_dispatch_to_procedure:
 *     Escolhe um procedimento de acordo com um status.
 * O teclado chama essa função, que envia a mensagem para 
 * o procedimento ativo.
 *
 * OBS: 
 * Por enquanto essa rotina só pode chamar o procedimento de janela
 * do kernel em ring 0. Para procedimentos de janela em ring 3
 * as mensagens serão salvas em filas na estrutura dos processos.
 *
 * Argumentos:
 *     +long param 2.
 *     +long param 1.
 *     +msg.
 *     +hwnd da janela ativa.
 *
 * classe: ram/sm
 */
int system_dispatch_to_procedure( struct window_d *window, 
                                  int msg, 
								  unsigned long long1, 
								  unsigned long long2)
{	
	asm(" pushl %0" :: "r" ((unsigned long) long2)  : "%esp"); 
    asm(" pushl %0" :: "r" ((unsigned long) long1)  : "%esp"); 
    asm(" pushl %0" :: "r" ((unsigned long) msg)    : "%esp");        
    asm(" pushl %0" :: "r" ((unsigned long) window) : "%esp"); 	 
    asm(" call *_g_next_proc ");    //Chama o xProc.
    asm(" pop %eax \n ");
	asm(" pop %eax \n ");
	asm(" pop %eax \n ");
	asm(" pop %eax \n ");	
   
	/*
	 * Status: 
	 *     A mensagem já foi enviada ao procedimento e processada por ele.
	 *     Então avisamos que não há mais mensagens.
	 *
     */
	g_nova_mensagem = 0;
	
done:	
	return (int) 0;
};   


/*
 * SystemMenu:
 * Cria o system menu para manipular a janela ativa. Control Menu.
 */
int SystemMenu()
{
    struct window_d *Current;    //Parent window.	
	struct window_d *hWindow;    //Menu window.
	
	//Tentativa de utilizar control menu não estando no modo gráafico.
	if(VideoBlock.useGui != 1)
	{
		//@todo: Notificar erro via modo texto.
	    return (int) 1;   
	};
	
    //
	// Usar a estrutura da Client Area.
	// A área da tela menos a área da barra de tarefas, ou barra de menu.
	//
	
	//
	// ?? desktop ?? Uma estrutura de janela , dentro da estrutura gui.
	//
	
	if( (void*) gui->desktop == NULL )
	{
		gui->desktop = (void*) gui->screen;
		
		//No Screen.
		if( (void*) gui->desktop == NULL ){
			return (int) 1; //erro.
		};		
	};

	//Set current.
	if( (void*) gui->desktop != NULL ){
        Current = (void*) gui->desktop;		
	};
	
	//No Current.
	if( (void*) Current == NULL ){
        return (int) 1;    //erro.
	};
	
	//
    // Cria o System Menu.
	// Envia uma parent window via argumento.
	// Retorna a janela criada para o menu.
    //	
	
    hWindow = (void *) create_menu(Current,4,0,0,0);
	
	//Se houve falha na criação da janela.
	if( (void *) hWindow == NULL ){
	    printf("SystemMenu error: Window Struct.\n");
		refresh_screen();
		while(1){}	
	};
	
	//Se houve falha na criação do menu.
	if( (void *) hWindow->defaultMenu == NULL ){
	    return (int) 1;
	}else{
		
		//Inicializa o array de menuítens.
	    initmenuArray( hWindow->defaultMenu, 4);

        //Cria os ítens.		
	    create_menu_item( hWindow->defaultMenu, "System menu item 1", 0);
        create_menu_item( hWindow->defaultMenu, "System menu item 2", 0);
	    create_menu_item( hWindow->defaultMenu, "System menu item 3", 0);
	    create_menu_item( hWindow->defaultMenu, "System menu item 4", 1);
		//...
	};
	//Nothing.
done: 
	SetProcedure( (unsigned long) &SystemMenuProcedure);	
	return (int) 0;
};


/*
 * SystemMenuProcedure:
 *     O procedimento do control menu principal.
 *     menu do sistema, manipula a janela ativa.
 *     ram /sm  
 */																
unsigned long SystemMenuProcedure( struct window_d *window, 
                                   int msg, 
								   unsigned long long1, 
								   unsigned long long2 ) 
{
    switch(msg)
	{
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:	
				   SetProcedure( (unsigned long) &system_procedure);						
				   break;
				   
                default:
				    //Nothing.
                    break; 
            };
        break;	
	
		case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {   
				//Restaturar janela	
				case VK_F1:
				    StatusBar( gui->screen, "Status Bar", "F1");
                    break;
					
				//Minimizar janela
                case VK_F2:
				    StatusBar( gui->screen, "Status Bar", "F2");
                    break;
					
				//Maximizar janela
                //case VK_F3:
                //    break;

				//fechar janela
                //case VK_F4:
                //    break;
					
			    //...
				
				default:
                    //Nothing.				
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
           //Nothing.		
        break;
		
		default:
		    //Nothing.
		    break;
	};
//Done.
done:
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
	return (unsigned long) 0;
};


/*
 * systemReboot:
 *     Interface de inicialização da parte de sistema para o processo de reboot.
 *     realiza rotinas de desligamento de sistema antes de chamar o reiniciamento de hardware.
 *     *IMPORTANTE: Um processo em user mode deve realizar as rotinas de desligamento.
 *     passar para o kernel somente depois de fechar todos os processos.
 *     Quando essa rotina checar os processos verá que não há mais nada pra fechar.
 *     se ainda tiver algum processo pra fechar, então essa rotina fecha, senão termina a rotina. 
 */
void systemReboot()
{
	int i;
	struct process_d *P;
	struct thread_d *T;
		
	struct window_d *hWnd;
	struct window_d *hWindow;	
	
	asm("cli");  // Me parece que desabilitar é uma opção.
	
	


	//Se não estivermos em modo gráfico, não há o que mostrar.	
    if(VideoBlock.useGui != 1){
	    return;	
	};
	
	
	//Parent window.
	if( (void*) gui->main == NULL){
	    return;
	};
	
	unsigned long left   = gui->main->left;
	unsigned long top    = gui->main->top;
	unsigned long width  = gui->main->width;
	unsigned long height = gui->main->height;	
	
		
	//@todo: Chamar método.	
	//Cursor.
	g_cursor_x = (left/8);
	g_cursor_y = (top/8); 
	//set_up_cursor(0,10);



//
	// @todo: Usar esquema de cores padrão.
	//
	
	if(VideoBlock.useGui == 1)
	{
		//Parent window.
	    if( (void*) gui->main == NULL){
	        return;
	    };
			
	    //Create.
	    hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "//KERNEL Reboot", 
	                                    left, top, width, height, 
			     				        gui->main, 0, KERNEL_WINDOW_DEFAULT_CLIENTCOLOR, KERNEL_WINDOW_DEFAULT_BGCOLOR ); 

	    if( (void*) hWindow == NULL){
	        printf("systemReboot:\n");
		    return;
        }else{
		    RegisterWindow(hWindow);
			set_active_window(hWindow);
			SetFocus(hWindow);
	    };										
		
		
		// Auterando as margens.
		// Essas margens são usadas pela função printf.
		// Obs: As medidas são feitas em números de caracteres.
		// Obs: @todo: Devemos usar aqui o retângulo da área de cliente,
		// e não as margens da janela.
		// A estrutura de janela deve nos oferecer os valores para a métrica do 
		// retângulo da área de cliente.
		// Obs: @todo:Acho que essa não é a forma correta de configurar isso. Uma 
		//rotina deveria perceber as dimensões da janela de do caractere e determinar
		//as margens.
		
		g_cursor_left   = (hWindow->left/8);
		g_cursor_top    = (hWindow->top/8) + 4;   //Queremos o início da área de clente.
		g_cursor_right  = g_cursor_left + (width/8);
		g_cursor_bottom = g_cursor_top  + (height/8);
		
		//cursor (0, mas com margem nova).
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
        
	    //
	    //@todo: Criar a interface. realizando configurações de sistema
	    // antes de chamar o hal.
	    // É apropriado deixar aqui as rotinas de desligamento do sistema
	    // ficando para hal a parte de hardware.
	    // +salvar arquivos de configuração.
	    // +salvar discos virtuais.
	    // ...
	    //
    
     	//...
	
        //
        // Coloca uma tela preta pra começar.
        //
	
        //Cls and Message.
	    //backgroundDraw(COLOR_BACKGROUND);
	    //StatusBar( gui->screen, "StatusBar: ", "Rebooting...");	
        //refresh_screen();

	
	    //@todo:
	    //block current task.
	    //close tasks
	    //...

        //
        //@todo: 
	    // +criar uma variavel global que especifique o tipo de reboot.
        // +criar um switch para efetuar os tipos de reboot.
	    // +criar rota de fuga para reboot abortado.
	    // +Identificar o uso da gui antes de apagar a tela.
	    //  modo grafico ou modo texto.
	    //

	
	    //
	    // Video.
	    //
	
        set_up_cursor(0,4);	            //O cursor deveria ficar na área do cliente.	
        set_up_text_color(0x0f, 0x09);  //isso é para modo texto. eu acho??
	    
		//init message.
		sleep(8000);
        printf("\n REBOOT:\n");	
	    printf("The computer will restart in seconds.\n");
	
	    //
	    // Scheduler stuffs.
	    //
	
	    sleep(8000);
	    printf("Locking Scheduler and taskswitch.\n");
	    scheduler_lock();
	    taskswitch_lock();
	
	
	    //
	    // File System stuffs. @todo
	    //
	
	    //
	    // Fechando processos que não foram fechados pelo shutdown em user mode.
	    // Obs: Todos os processos nesse momento ja deveriam estar terminados
	    // através de rotinas em user mode. Então checamos se falta algum e 
	    // caso haja, terminamos o processo.
	    // Obs: A rotina de fechar processo deve fechar as threads na ordem da lista encadeada.
	    //

	    sleep(8000);
	    printf("Terminating processes..\n");
		
		
		//
		// +Enviamos sinal para todas as threads bloquearem.
		// +desalocamos todos os recursos usados por elas.
		// +mandamos sinal para todas as thears fecharem.
		//
		
//blockingAllThreads:		
		//antes de terminarmos todos processos vamos boquear todas as threads.
	    //Começa do 1 para não fechar o kernel.
	    i = 1;
	
	    while(i < THREAD_COUNT_MAX)
	    {
            //Pega da lista.
		    T = (void *) threadList[i];
		    if(T != NULL)
			{
#ifdef KERNEL_VERBOSE				
		        //bloqueia a thread. 
		        printf("blocking thread TID={%d} ...\n",i);
		        //refresh_screen();
#endif
                if( T->used == 1 ){
                    T->state = BLOCKED; //?? ZOMBIE ??   
		            //block_thread(i, 0);
				}
		    };
		    i++;
	    };

//exitingAllProcesses:	
	    //Começa do 1 para não fechar o kernel.
	    i = 1;
	
	    while(i < PROCESS_COUNT_MAX)
	    {
            //Pega da lista.
		    P = (void *) processList[i];
		    if(P != NULL)
			{
#ifdef KERNEL_VERBOSE				
		        //Termina o processo. (>> TERMINATED)
		        printf("Killing Process PID={%d} ...\n",i);
		        //refresh_screen();
#endif
                if( P->used == 1 ){
		            exit_process(i, 0);
				}
		    };
		    i++;
	    };

	    // Final message.
	    sleep(8000);
	    printf("Rebooting..\n");
			
        SetFocus(hWindow);
	
		
		//voltando a margem normal a margem
		//?? isso não é necessário??
		g_cursor_left   = (left/8);    //0;
		g_cursor_top    = (top/8);        //0;
		g_cursor_right  = (width/8);   
		g_cursor_bottom = (height/8);  
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		


		StatusBar(hWindow,"Esc=EXIT","Enter=?");		
		//Nothing.
	};	   

 
	
	//Nothing.
	
done:
    refresh_screen();
	sleep(8*8000);
	MessageBox(gui->screen, 1, "systemReboot:","Rebooting..");
    refresh_screen();
	KiReboot();
hang: 
    while(1){}
};


/*
 * systemShutdown:
 *     Interface para shutdown.
 */ 
void systemShutdown()
{
	 
	//@todo ...

	MessageBox(gui->screen, 1, "systemShutdown:","I's safe to turnoff your computer.");
	
	//Nothing.
	
done:		
	//systemShutdownViaAPM(); //@todo: usar essa.
	//KiShutdown(); //??
	//hal_shutdown();
hang:	
	while(1){}
};


/*
 * systemShutdownViaAPM:
 *     Desliga a máquina via APM.
 *     (Deve chamar uma rotina herdada do BM).
 */
void systemShutdownViaAPM()
{

   //
    // Obs: @todo:
	//     Existe uma rotina no BM que desliga a máquina via APM usando 
	// recursos do BIOS. A rotina começa em 32bit, assim podemos tentar herdar 
	// o ponteiro para a função.
    //
	//MessageBox(gui->screen, 1, "systemShutdown:","Turning off via APM ...");	

	
    //Chamar a função de 32 bit herdado do BM.
    //todo: usar iret.
	
	//Check limits.
	// O ponteiro herdado tem que ser um valor dentro do endereço onde 
	//roda o BM, que começa em 0x8000.
	//if(shutdown_address > 0x8000 && shutdown_address < 0x20000 ){
		
	//Pilha para iret.
    //asm("pushl %0" :: "r" ((unsigned long) 8)     : "%esp");    //cs.
    //asm("pushl %0" :: "r" ((unsigned long) shutdown_address)    : "%esp");    //eip.
	//asm("iret \n");    //Fly!	
		
	//};
	
hang:	
	while(1){}
};


/*
 * systemGetSystemMetric:
 *     Retorna um valor de medida de algum elemento do sistema.
 * usado pelas rotinas de criação e análise.
 * O argumento seleciona a variável global que será retornada.
 * Obs: Temos muitas variáveis globais com valores de demensões
 * de recurso do sistema. Essa rotina é um modo organizado de 
 * pegar os valores das variaveis globais relativas à medidas.
 * Obs: É muito apropriado essa função ficar no arquivo \sm\sys\system.c
 * Pois é a parte mais importante do módulo System Manegement".
 */
void *systemGetSystemMetric(int number)
{
	switch(number)
	{
		case SM_NULL:
		    return NULL;
			break;
			
		case SM_SCREENWIDTH:
            //pegar uma global
			break;
		
        case SM_SCREENHEIGHT:
            //pegar uma global
			break;
        
		//Essa é uma versão para o desenvolvedor??
        case SM_DEVELOPER_EDITION:
            if(gSystemEdition == SYSTEM_DEVELOPER_EDITION){
				return (void*) 1; //Sim, essa é uma versão para o desenvolvedor.
			}else{ return NULL; }; //Não, essa não é uma versão para o desenvolvedor.
		    break;
			
            //Continuar ... 			
		 	
		default:
		    return NULL;
	};
};


/*
 * systemGetSystemstatus:
 *     Retorna o valor de alguma variável global relativa 
 * apenas a status de algum elemento do sistema.
 * Obs: É muito apropriado essa função ficar no arquivo \sm\sys\system.c
 * Pois é a parte mais importante do módulo System Manegement".
 *
 */
void *systemGetSystemStatus(int number)
{
	switch(number)
	{
		case SS_NULL:
		    return NULL;
			break;
			
		case SS_LOGGED:
            return (void*) g_logged;
			break;
		
        case SS_USING_GUI:
            return (void*) g_useGUI;
			break;
        //Continuar ... 			
		 	
		default:
		    return NULL;
	};
};

/*
 * systemStartUp:
 *     Rotina de inicialização do sistema.
 *
 * Fase 1:
 *     Inicia elementos independentes da arquitetura.
 *	   + Inicia vídeo, cursor, monitor. 
 *       Somente o necessário para ver mensagens.
 * Fase 2:
 *     Inicia elementos dependentes da arquiterura.
 *	   + inicia elementos de I/O e elementos conservadores de dados.
 *	   + inicia runtime.
 *     + inicia hal, microkernel, executive.
 *     + Inicia as tarefas. (@todo: threads ou processos ?).
 * Fase 3:
 *     classe system.device.unblocked.
 *	   @todo: Inicializar dispositivos LPC/super io.
 *            Keyboard, mouse, TPM, parallel port, serial port, FDC. 
 * Fase 4:
 *     classe system.device.unblocked.
 *     @todo: Dispositivos PCI, ACPI ...
 *
 *     Continua ...
 *
 * 2015 - Created.
 * 2016 - Revisão.
 */
int systemStartUp()
{
    int Status = 0;

	KeInitPhase = 0;  //Set Kernel phase.    

    //
	// Antes de tudo: CLI, Video, runtime.
	//
	
	if(KeInitPhase != 0)
	{	
		//@todo: As mensagens do abort podem não funcionarem nesse caso.
		KiAbort();	
	}else{
		
	    //Disable interrupts, lock taskswitch and scheduler.	    
		asm("cli");	
	    taskswitch_lock();
	    scheduler_lock();
		
		//Set scheduler type. (Round Robin).
	    schedulerType = SCHEDULER_RR; 
		
	    
		//Obs: O video já foi inicializado em main.c.
				
		//
		// BANNER !
		//
		
        //Welcome message. (Poderia ser um banner.) 
		set_up_cursor(0,1);
		
#ifdef KERNEL_VERBOSE		
        printf("systemStartUp: Starting 32bit Kernel [%s]..\n",KERNEL_VERSION);
#endif		
		
#ifdef KERNEL_VERBOSE		
		//Avisar no caso de estarmos iniciando uma edição de desenvolvedor.
		if(gSystemEdition == SYSTEM_DEVELOPER_EDITION){
		    printf("systemStartUp: %s\n",developer_edition_string);
		};
#endif

#ifdef KERNEL_VERBOSE
		printf("systemStartUp: LFB={%x} X={%d} Y={%d} BPP={%d}\n",(unsigned long) SavedLFB
		                                                         ,(unsigned long) SavedX
																 ,(unsigned long) SavedY
																 ,(unsigned long) SavedBPP );
#endif

        //
        // RUNTIME !
        //		

#ifdef KERNEL_VERBOSE		
	    printf("systemStartUp: Initializing Runtime..\n");
#endif			
	    Status = (int) KiInitRuntime();
	    if(Status != 0){
	        printf("systemStartUp error: Runtime.\n");
		    KiAbort();
	    };		
        
        //
        // INIT ! 
        //  		
		
#ifdef KERNEL_VERBOSE
		//(inicializa as 4 fases.)
	    // Básico. ( Variáveis globais e estruturas ... ).
	    printf("systemStartUp: Initializing Basics..\n");
#endif		
        Status = (int) init(); 
	    if(Status != 0){
	        printf("systemStartUp error: Init.\n");
		    KiAbort();
	    };	
        //...	 
	};
	
	 
	
	//
	// System Version:
	//     Configurando a versão do sistema.
	//     
	//
	
	systemSetupVersion();
	
	//
	// Inicializa a edição do sistema.
	// Define um tipo de destinação para a versão do sistema operacional.
	//
	
    switch(SYSTEM_EDITION)
	{
		case SYSTEM_DEVELOPER_EDITION:
		    gSystemEdition = SYSTEM_DEVELOPER_EDITION; 
		    break;

		case SYSTEM_WORKSTATION_EDITION:
		    gSystemEdition = SYSTEM_WORKSTATION_EDITION;
		    break;

		case SYSTEM_SERVER_EDITION:
		    gSystemEdition = SYSTEM_SERVER_EDITION;
			break;

		case SYSTEM_IOT_EDITION:
		    gSystemEdition = SYSTEM_SERVER_EDITION;
			break;

        //...
        default:
		    gSystemEdition = 0;
            break; 		
	};
	
//
// Done: 
//     Completas as 3 fases de inicialização do sistema.
//     @todo: Na verdade serão mais fases..
//           as fases estão em init().
done:	
    //printf("systemStartUp: Done!\n");	
	//refresh_screen();	
	if(KeInitPhase != 3){ 
	    Status = (int) 1; 
	};
    return (int) Status;
};


/*
 * systemInit:
 *     Inicializando algumas variáveis.
 */
int systemInit()
{
	//Colocando na variável global, a opção selecionada manualmente pelo 
	//desenvolvedor.
    gSystemEdition = SYSTEM_EDITION;
    //...
	
	// Podemos fazer algumas inicializações antes de chamarmos 
	//a rotina de start up.
	
done:
    //Retornando para o kMain. em main.c.	
	return (int) systemStartUp();	
};


/*
 * systemSystem:
 *     Construtor.
 * Não tem valor de retorno, tem o mesmo nome que a classe.
 * Uma chamada à um construtor criaria uma estrutura com seu nome e 
 * o construtor pode inicializar alguma variável.
 */
void systemSystem(){
    gSystemStatus = 1;
};



/*
 * die:
 *     Função sem retorno. Aqui termina tudo.
 *      O sistema trava e não tem volta.
 */
void die()
{
    // Final message!	
	// Refresh.	
	// HALT.
	
    printf("* System Halted!");    //Bullet.  
	
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
halt:
	asm("hlt");   
	while(1){
		
	asm("cli");
	asm("hlt");                        //Halt system.
	
	};     	
};

//
// End.
//

