/*
 * File: main.c 
 *
 * General purpose application.
 *     SHELL.BIN é um aplicativo de próposito geral. Desenvolvido como 
 * ferramenta do desenvolvedor para prover varios tipos de testes de recursos do sistema.
 *
 * Ok, isso é um program do tipo 'janela', o pequeno terminal 
 * que roda em uma janela filha será gerenciado pelo próprio aplicativo.
 * Isso é diferente de um programa feito para rodar em um terminal, onde o kernel 
 * gerenciará a janela usada pelo programa. 
 *
 * Podemos usar esse terminal na janela filha para interpretar linguagem basic.
 *
 * Descrição:
 * Shell do sistema. (SHELL.BIN)
 * Arquivo principal do Shell.
 * É um aplicativo de 32bit em user mode. 
 * P3 - Processos em ring3, User Mode.
 * O Programa recebe comandos do usuário e envia os comandos para o núcleo 
 * através de chamadas ao sistema. 
 *
 * (@todo: envio de mensagens) A idéia é que cada comando chame um processo 
 * diferente, mas existem serviços internos que o próprio Shell ofereçe
 * fazendo uso dos recursos do Kernel ou próprios.
 *     	
 * É o console, um terminal virtual em user mode.    
 *
 * Obs: O Shell é o aplicativo apropriado para o desenvolvedor criar e testar 
 * as chamadas ao Kernel via interrupção e para ver as mensagens do compilador.
 *      O programa que executa aplicações em lote deve enviar os outputs para 
 * a tela do Shell. 
 *
 * Obs: O entry point está em head.s
 *      @todo: Não usar o arquivo head em assembly efeito de portabilidade.
 * Obs: O prompt e cursor estão definidos em stdio.h
 *
 * * IMPORTANTE: O FOCO DO INTERPRETADOR DE COMANDOS DO SHELL APP DEVE SER
 * A GERÊNCIA DE ARQUIVOS E DISPOSITIVOS DE ARMAZENAMENTO, EM SEGUNDO LUGAR
 * A GERENCIA DOS RECURSOS DO SISTEMA, POIS ISSO É ATRIBUIÇÃO DO APP TASKMAN.
 *
 *
 * Histórico:
 *     Versão 1.0, 2016 -  Esse arquivo foi criado por Fred Nora.
 *     //...
 */

/*
 Como o kernel envia mensagens para o terminal em user mode?
 
 The mechanism for delivering messages to the console is implemented by the 
 printk function, defined in kernel/printk.c. 
 The function uses vsprintf (defined in lib/vsprintf.c) to create a message 
 string, places the string in the circular buffer of kernel messages and 
 passes it to all active console devices if the priority of the message is 
 less than console_loglevel. 
*/ 
 
 
//
// Includes.
// 

#include "api.h"
#include "types.h"
#include "stddef.h"   
#include "stdio.h"   
#include "stdlib.h"  
#include "string.h"
#include "shell.h"
#include "globals.h"


//Sendo assim, o shell poderia abrir no ambiente de logon.
char *username;
char *password; 

//#define DEFAULT_WINDOW_TITLE "Shell"

//
// Variáveis internas.
//

int shellStatus;
int shellError;


//
// Input flags.
//


int ShellFlag = 0;

#define SHELLFLAG_NULL 0
#define SHELLFLAG_COMMANDLINE 1
#define SHELLFLAG_SCRIPT 2
#define SHELLFLAG_HELP 3
#define SHELLFLAG_VERSION 4
#define SHELLFLAG_USAGE 5
#define SHELLFLAG_TOPBAR 6
//...


//
// Protótipos para funções internas.
//


unsigned long shellProcedure( struct window_d *window, 
                              int msg, 
							  unsigned long long1, 
							  unsigned long long2 );
							  
							  
unsigned long shellTopbarProcedure( struct window_d *window, 
                                    int msg, 
							        unsigned long long1, 
							        unsigned long long2 );
							  

 
 
 
/*
 *****************************************************************
 * GramadoMain: 
 *     Função principal.
 *     The Application Entry Point.
 *
 * @todo:
 *    +Checar argumentos.
 *    +Criar a janela do TERMINAL. (Ok).
 *    +Enviar mensagem de texto para ele. (Ok).
 *    +Configurar procedimento de janela.
 *    +Definir a janela que é área do cliente.
 *    +Carregar um arquivo na área de cliente.
 *    +Testar outros recursos do Kernel.
 *    +Testar as chamadas para pegar informções sobre o proesso.
 *    +...
 *
 *  
 *  ## O SHELL É UM APLICATIVO DO TIPO JANELA DEVE TER UM MAIN DO TIPO JANELA ##
 *
 * Obs: Esses argumentos podem ser um padrão.
 */

//opção. 
//void *GramadoMain( int argc, char *argv[], unsigned long address, int view )
int GramadoMain( int argc, 
                 char *argv[], 
				 unsigned long long1, 
				 unsigned long long2 )
{
	
	//
	// Obs: Esse não é um programa que roda em modo terminal,
	// ele na verdade cria um terminal dentro de uma janela filha.
	// isso pode servir para esse programa interpretar linguagem basic por exemplo.
	// os programas em modo terminal não criarão janelas e rodarão nas 
	// janelas de terminal cridas para eles pelo kernel.
	//
	
	//#debug
	//deixe o kernel usar essa janela para teste.
	//Obs: Não criaremos a janela principal desse programa 
	//para evitarmos erros com printf.
	
	/*
	 *Obs: Isso funcionou bem.
	apiBeginPaint();
	    MessageBox( 1, "SHELL.BIN","Initializing ...");
	apiEndPaint();
	
    refresh_screen();
	*/
	
	//chamando uma system call que ative a rotina de testes de 
	//escrita em janelas com o foco de entrada.
    //cancelada, acionaremos via procedimento de janela do sistema F12.
	//system_call( 222,0,0,0);
	//while(1){}	
	
	
	/*
	 * Uma boa ordem para os passos dessa rotina nos aplicativos  
	 * é: Step1=WindowClass, Step2=Window e Step3=Message.
	 */
	
	//@todo: Criar esse tipo de classe.
	//       Provavelmente deve coincidir com a estrutura presente
    //nas rotinas de gerenciamento de janela que estão em kernel mode.	
	//struct window_class_d *wc; 
	
	
	struct window_d *hWindow;        //janela do aplicativo.

	
	//struct message_d *m;

	
	int Status = 0;
	char *s;    //String	

	//...
	
	//@todo:
	//Podemos começar pegando o id do processo atual e 
	//melhorando a prioridade.
	
	
	// get current dir
	//pegamos o diretório atual.
	
	//get user dir
	//pegamos o diretório do usuário /root/user/(name)
	
	//set current dir
	//setamos para que o diretório do usuário seja o diretório atual.
	
	
	//
	// Isso configura alguns padrões do aplicativo.
	// Os argumentos tratados abaixo podem modificar esses padrões
	// Ex: Um argumento de entrada pode solicitar a troca de cor de fonte.
	//
	
	shellShell(); 	
	
	
	//#DEBUG
	//printf("S");
	//printf("Shell: testing strings \n");
	//shellSetCursor(8,8); 
	//printf("Shell: and cursor. \n");
	//refresh_screen();
	//while(1){}	
    
	
	//
	// Filtra a quantidade de argumentos.
	//
	
	// Se não há argumentos.
	if(argc < 1){
		//#bugbug sprintf ( ?? o que deve ficar no argumentop ?? ) 
        //sprintf( stderr->_base,"Starting Shell with no arguments...\n");	 //Test.	
	    goto noArgs; 
	};
	
	//if (argc <= 1){
    //    fprintf( stderr, "%s\n", usage ); //File??
    //    exit(1);
    //}
	
	//
	// Filtra o primeiro argumento no formato 'palavra'.
	//
	
    //if (!strcmp( argv[1], "-help" ))
	//{
    //    printf( "%s\n", usage );
    //    refresh_screen();
	//	exit(0);
    //}
    
	//if (!strcmp( argv[1], "-version" ))
	//{
        //printf( "%s\n", shellGetVersion() );
    //    refresh_screen();
	//	exit(0);
    //}	
	
	//
	// Outras opções de argumentos.
	//
	
	//Dependendo do argumento encontrado muda-se a flag.
    while(argc--) 
    {
        s = *++argv;
        if (*s == '-' || *s == '/') 
		{
            while(*++s) 
			{
                switch(*s) 
				{
					//Null
					case 0:
					    ShellFlag = SHELLFLAG_NULL; 
						break;
						
					
					// -c 
                    // Modo command line.					
					case 'c':
					    ShellFlag = SHELLFLAG_COMMANDLINE;
					    break;
	
					// -s 
					// Modo script.
					case 's':
					    ShellFlag = SHELLFLAG_SCRIPT;
						break;

					// -h 
                    // help					
                    case 'h':
					    ShellFlag = SHELLFLAG_HELP;
                        //if (!strcmp( argv[argc], "help" )){ ... };
						//if (!strcmp( argv[argc], "HELP" )){ ... };
						//...
                        break;

					// -v 
                    // version					
                    case 'v':
					    ShellFlag = SHELLFLAG_VERSION;
					    //if (!strcmp( argv[argc], "version" )){ ... };
						//if (!strcmp( argv[argc], "VERSION" )){ ... };
						//...
                        break;

                    // -u 
					// usage
					case 'u':
					    ShellFlag = SHELLFLAG_USAGE;
					    //if (!strcmp( argv[argc], "XXX" )){ ... };
                        break;

                    //...

                    default:    
						ShellFlag = SHELLFLAG_USAGE;
						//usage();
						break;
                };
            };
        
		}else{
			ShellFlag = SHELLFLAG_NULL;
			//usage();
			goto noArgs;   
        };
    };
	
	//Nothing.
	
noArgs:	
	

	
	//
	// @todo: Usar essa rotina para fazer testes de modo gráfico.
	//	
	
	//Debug:
	//while(1){};
	
	//
	// @todo: 
	//     Set priority.
	//     Set Window Station, Desktop ...
	//     ...
	//
	// @todo:
	//     Quando essa janela é criada ainda estamos no ambiente de Logon,
	// dentro do desktop de Logon. Não há problema nisso por enquanto,
	// pois poderemos utilizar os recursos do shell antes de habilitarmos
	// todos os recursos o ambiente do usuário. Porém será necessário, 
	// no futuro, executarmos o Shell no desktop do ambiente do usuário.
	//
	// @todo: 
	//     Precisamos de um ponteiro com a área de memória que representa
	// a área de trabalho do Shell.
	//     Precisamos de um ponteiro com a área de cliente da janela do Shell.
	//
    // @todo: 
	//     Buffers. Buffers pra linha e buffer pra arquivo.	
	//
	// @todo: 
	//     Essa janela aparece centralizada e pequena, evidenciando que os 
	// argumentos não foram passados corretamente, então o gerente de recursos 
	// gráficos usou dimensões default. Provavelmente o Kernel não os 
	// recepciona devidamente ainda.
	//
	// ...
	//
	
	
	
	//
    // Create Window.
	//
	
	//Debug:
	//printf("\n\n Starting Shell Version ");
	//printf(SHELL_VERSION);
	//refresh_screen();	
	
	//Debug:
	//while(1){}
	
	

		
	
	
	
	//
	// Step 2. Creating a window frame.
	//
	
	
		
	
	//
    // Não é necessário passar todos os argumentos de uma vez só.
	// Podemos realizar 3 ou 4 chamadas para construírmos a janela.
	// Essa rotina tem 12 argumentos mas ela poderá realizar 3 chamadas
	// ao sistema para passar todos os argumentos.
	//
	
	
	//
	// *Importante:
	//      A janela do shell será uma aba dentro da janela do navegador,
	// essa janela do navegador é gerenciada pelo kernel, mas não passa de uma moldura 
	// com abas.
	// >> o kernel ja sabe que o processo tem uma aba, então quando o processo 
	//tenta criar uma janela, a sua janela será criada dentro de sua aba.
	//
	
	//General purpose appplication  -  {} Developer version
	
	//@todo:
	//Criar essas funções na API.
	//unsigned long ScreenWidth = (unsigned long) APIGetScreenWidth();
	//unsigned long ScreenHeight = (unsigned long) APIGetScreenheight();
	
	
	//
	// Configurando o retângulo que deve ser usado pelo terminal.
	//
	
	//#bugbug 
	// esses valores são usados para construir a janela princpal.
	// o que desejamos são os valores do retângulo da área de cliente 
	// da janela principal.
	
	terminal_rect.left = shell_window_x;
	terminal_rect.top  = shell_window_y;
	terminal_rect.width = shellWindowWidth;
	terminal_rect.height = shellWindowHeight;
	
	apiBeginPaint();
	

    //
	// Criando a janela WT_OVERLAPPED.
	//
	
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1," {} SHELL.BIN ",
	                                   shell_window_x, shell_window_y, 
									   shellWindowWidth, shellWindowHeight,    
                                       0, 0, COLOR_BLACK, 0x83FCFF00 );	   
	if((void*) hWindow == NULL){	
		printf("Shell: Window fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	

	
	/*
	 Imprimindo o ponteiro para a estrutura da janela criada 
	 Estamos testando se o retorno está funcionando nesse caso.
	 */
	/* isso funcionou
	printf("Testing handle {%x}\n",hWindow);
	
	printf("Testing resize window\n");
	APIresize_window( hWindow, 640, 480);
	*/
	
	//#bugbug 
	//Não é possível configurar a estrutura de janela diretamente.

	
	//
	// ** criando a top bar.
	//
	
	//#bug bug
	//enterCriticalSection();    // * Enter Critical Section.
	//shellCreateTopBar();
	//exitCriticalSection();     // * Exit Critical section.	
	
	
	apiEndPaint();
	
	//
	// Funcionou setar o foco, e a mensagem foi para a janela certa.
	//
	
    //Registrar.
    APIRegisterWindow(hWindow);
	
    //Configurar como ativa.
    APISetActiveWindow(hWindow);
	
    //Setar foco.
	// *IMPORTANTE: 
	// É FUNDAMENTAL SETAR O FOCO, POIS O KERNEL DEPENDE DELE
	// PARA RETORNAR A MENSAGEM DA JANELA COM O FOCO DE ENTRADA.
	// Nesse momento o kernel configura as margens para o cursor 
	// dentro da janela.
	// @todo: O kernel deve reiniciar as variáveis de cursor 
	// dentro da janela também, pois cada janela tem uma configuração 
	// diferente de cursor.
    APISetFocus(hWindow);
	
	//#bugbug
	//janela usada para input de textos ...
	//o input de texto pode vir de várias fontes.
	//api_set_window_with_text_input(hWindow);
	
	//
	// ++ terminal ++
	//
	
	//definindo a janela como sendo uma janela de terminal.
	//isso faz com que as digitações tenham acesso ao procedimento de janela de terminal 
	//para essa janela e não apenas ao procedimento de janela do sistema.
	system_call( SYSTEMCALL_SETTERMINALWINDOW, 
	             (unsigned long) hWindow, 
				 (unsigned long) hWindow, 
				 (unsigned long) hWindow );
				 
				 
				 
	//salva ponteiro da janela principal. 
	shell_info.main_window = ( struct window_d* ) hWindow;			 
		
	
	//
	// @todo: Apenas registrar o procedimento dessa janela na sua estrutura no kernel..
    // 
	
	
	//
    // ...		
	//
	
	
	//
	// Init Shell:
	//     Inicializa variáveis, buffers e estruturas. Atualiza a tela.
	//
	
	
	
	enterCriticalSection();    // * Enter Critical Section.	
	Status = (int) shellInit(hWindow); 
	if(Status != 0){
		printf("[SHELL.BIN]: app_main: shellInit fail!");
		refresh_screen();
		while(1){};
		//exit(0);
	};
	exitCriticalSection();     // * Exit Critical section.		
	
	
	
	
    	
	
	
	//
	// Messages.
	//
	

    //printf("shellInit funcionou.\n");
	
	
	//g_cursor_x = 0;
	//g_cursor_y = 32;
	
	//system_call( SYSTEMCALL_DRAWTEXT, 
	//             shell_cursor_x,  
	//			   shell_cursor_y, 
	//			   (unsigned long) "Starting SHELL.BIN ... \n" );
	
	//system_call( SYSTEMCALL_DRAWTEXT, x,  y, (unsigned long) "$>_");		
	    
	//Printf Funcionando. (stdio.c)
	//printf("Shell printf test\n");   
	//printf_main();
		
	//Testing String 		
	//system_call( SYSTEMCALL_DRAWTEXT, 0,  0, (unsigned long) "/SHELL.BIN Testing strings...");
	//system_call( SYSTEMCALL_DRAWTEXT, 0, 20, (unsigned long) "Shell: 2 Testing strings...\n"); 
	//system_call( SYSTEMCALL_DRAWTEXT, 0, 40, (unsigned long) "Shell: 3 Testing strings...\n");

	//Refresh screen
	//system_call( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0);
	
	
	
	//@todo: Isso é um teste.
	//system("reboot");
	
	//
	// Podemos tentar criar um processo.
	//

 	


    //
	// Get message.
	//

	/*
	 * @todo: 
	 *     Entrar num loop, solicitando ao kernel possiveis mensagens
	 * deixadas no buffer de mensagens do PCB do processo shell.
	 * Obs: O kernel coloca na fila de mensagens do processo, mensagens
	 * provenientes não apenas do teclado, mas também de outras fontes.
	 * Então dessa forma, pode-se enviar mensagens de um processo para outro.
	 * *IMPORTANTE:Cabe a cada processo pegar as mensagens deixadas no buffer de mensagens 
	 * em seu PCB, atravez de uma chamada ao kernel.
	 */
    
    
	
	
	//
	// Por fim: Testar cursor e terminar.
	//

	//@todo: 0,0 não está na área de cliente.
	
	/*
	printf("Testing cursor ...\n");
    
	shellSetCursor(shellMaxColumns,shellMaxRows);  
	printf("C");
	shellSetCursor(shellMaxColumns-1,shellMaxRows-1);
	printf("U");
	shellSetCursor(shellMaxColumns-2,shellMaxRows-2);
	printf("R");
	shellSetCursor(shellMaxColumns-3,shellMaxRows-3);
	printf("S");
	shellSetCursor(shellMaxColumns-4,shellMaxRows-4);
	printf("O");
	shellSetCursor(shellMaxColumns-5,shellMaxRows-5);
	printf("R");
	shellSetCursor(shellMaxColumns-6,shellMaxRows-6);
	printf(":)");
	*/
	
	
//initializePrompt:
	
	//inicializa o prompt.	
	//shellPrompt();	
    //refresh_screen();	
	
//entrandoNoWhile:	
	//printf("SHELL: While...");
	//while(1){}
	
	//printf(SHELL_PROMPT);
	//refresh_screen();	
	
	
	//** hang.
	//printf("*Hang");
	//refresh_screen();
    //while(1){} 	
	
	//
	// **** Mensagens  ****
	//
	
	//printf("Tentando pegar mensagem enviada para o procedimento de janela.");
	//refresh_screen();
	
	//isso é um teste pegar um valor por vez não é a melhor opção.
	
	struct window_d *msg_Window;
	int msg_Message;
	void *msg_Long1;
	void *msg_Long2;
	
	//struct shell_message_d *msg;

        //
		// Get Message: 
		// Systemcall get message
		// Enviamos um ponteiro de estrutura de janela para que o Kernel possa 
		// pegar a mensagem que esta dentro da estrutura. Essa estrtura fica 
		// protegida no Kernel.
		//
		
		//
		// #bugbug: Na verdade essa rotina está pegando a mensagem na janela 
		// com o foco de entrada. esse argumento foi passado mas não foi usado.
		//
		
	while(1)
	{


		//  #bugbug SYSTEMCALL_GET_KEYBOARD_MESSAGE está pegando a mensagem de teclado,
		//          mas na verdade deveria apenas pegar a mensagem, sem se preocupar em 
		//          qual foi o dispositivo gerador do evento. ??!!
		

       apiBeginPaint();
	   
		//msg->window = (struct window_d *) system_call( SYSTEMCALL_GET_HWINDOW, 
 		msg_Window = (struct window_d *) system_call( SYSTEMCALL_GET_HWINDOW, 
		                              (unsigned long) hWindow,  
									  (unsigned long) hWindow, 
									  (unsigned long) hWindow );
									  
        //#bugbug ( Aqui devemos pegar a mensagem sem se preocupar em
		//identificar o dispositivo gerador do evento.
		//msg->msg = (int) system_call( SYSTEMCALL_GET_KEYBOARD_MESSAGE,
        msg_Message = (int) system_call( SYSTEMCALL_GET_KEYBOARD_MESSAGE, 		
		                              (unsigned long) hWindow,  
									  (unsigned long) hWindow, 
									  (unsigned long) hWindow );
									  
		 
		//msg->long1 = (unsigned long) system_call( SYSTEMCALL_GET_LONG1,
        msg_Long1 = (void*) system_call( SYSTEMCALL_GET_LONG1,		
		                             (unsigned long) hWindow, 
									 (unsigned long) hWindow, 
									 (unsigned long) hWindow );
									 
		 
		//msg->long2 = (unsigned long) system_call( SYSTEMCALL_GET_LONG2,
        msg_Long2 = (void*) system_call( SYSTEMCALL_GET_LONG2,		
		                             (unsigned long) hWindow, 
									 (unsigned long) hWindow, 
									 (unsigned long) hWindow );
									 
		apiEndPaint();
									 

        //
        // + PEGAMOS A MENSAGEM NA FILA DA JANELA COM O FOCO DE ENTRADA.
        //   ?? COMO DECIDIREMOS QUAL JANELA SERÁ AFETADA PELO PROCEDIMENTO 
        //	    QUE CHAMAREMOS AGORA ??
        //		
		
		// Send Message to procedure.
		
		//if( (int) msg->msg != 0 )
        if( (int) msg_Message != 0 )			
		{
            //
            // *IMPORTANTE:
			//  SE TEMOS UM HANDLE DE JANELA, SIGNIFICA QUE O PROCEDIMENTO PODE 
			//  AFETAR MAIS DE UMA JANELA. PORTANTO JANELAS FILHAS OU ATE MESMO JANELAS 
			//  CRIADAS PELO SISTEMA PODERÃO SER AFETADAS POR ESSE PROCEDIMENTO??
			//  @TODO: PASSAR O HANDLE DE JANELA PARA O PROCEDIMENTO.
            //			
		    
			if( ShellFlag == SHELLFLAG_TOPBAR )
			{
			
			    shellTopbarProcedure( (struct window_d *) msg_Window, 
			                (int) msg_Message, 
							(unsigned long) msg_Long1, 
							(unsigned long) msg_Long2 );			
			}else{
				
			    shellProcedure( (struct window_d *) msg_Window, 
			                (int) msg_Message, 
							(unsigned long) msg_Long1, 
							(unsigned long) msg_Long2 );

			};
			
		    //shellProcedure( msg->window, msg->msg, msg->long1, msg->long2 ); 
							
			//printf("Y-DEBUG: hwindow NULL\n"); //Deletar isso depois.
			//printf("Y-DEBUG: msg={%d}\n",msgTest); 
			//printf("Y-DEBUG: long1={%c}\n",long1); 
			//printf("Y-DEBUG: long2={%c}\n",long2); 
		};
		
		//Nothing.
	};
	
	
	//
	// Exit process.
	//
	
end:
    printf("shell loop fail!");
    refresh_screen();	
    while(1){}    //Hang.
    //MessageBox(...);	
	exit(0);  
	return (int) 0;
};


/*
 ***********************************************
 * shellProcedure:
 *     Procedimento de janela.
 *     LOCAL
 */
unsigned long 
shellProcedure( struct window_d *window, 
                int msg, 
				unsigned long long1, 
				unsigned long long2 )
{
    unsigned long input_ret;
    unsigned long compare_return;	
	
	
	//if( msg == COMMAND_INITIALIZE_SHELL ){
		//...
	//}
	
    switch(msg)
    {
		//Faz algumas inicializações de posicionamento e dimensões.
        //case MSG_INITDIALOG:
        //    break;

		//Torna a janela visível.
        //case MSG_SHOWWINDOW:
		//    break; 
		 
		case MSG_KEYDOWN:
            switch(long1)
            {
				// Null key.
				case 0:
				    return (unsigned long) 0;
				    break;
				
				// Enter.
				// Finaliza a string e compara.
				case VK_RETURN:
				    input('\0'); 
					shellCompare(window);
					goto done;
                    break; 					
                              
                // Mensagens de digitação.
				// Texto. Envia o caractere.
                // Imprime os caracteres normais na janela com o foco de 
				// entrada.
				// Enfilera os caracteres na string 'prompt[]' para depois 
				// ser comparada com outras strings.
                default:			   
				    
					// Coloca no stdin.
					input( (unsigned long) long1);      
                    
					// Coloca no stdout.
					shellInsertNextChar((char) long1);  
					
					// #importante: IMPRIMINDO.
					// Funcionando bem.
					printf("%c", (char) long1); 					
					goto done;
                    break;               
            };
        break;
		
		case MSG_KEYUP: 
		    // printf("%c", (char) 'u');
            // printf("%c", (char) long1);  			
		    break;
		
		//Não interceptaremos mensagens do sistema por enquanto.
		//As mensagens do sistema são interceptadas primeiro pelo procedimento 
		//do sistema.
		
		case MSG_SYSKEYDOWN:
		    switch(long1){
		        
				//help
				case VK_F1:
				    //MessageBox( 1, "Gramado Core - Shell","F1: HELP");
					//shell_gramado_core_init_execve( "TESTTESTBIN", 0, 0 );
					
					//testando formato amigável de string
					shell_gramado_core_init_execve( "testtest.bin", 0, 0 );
					break;
				
                //full screen
                //colocar em full screen somente a área de cliente. 				
		        case VK_F11:
				    MessageBox( 1, "Gramado Core - Shell","F11: FULL SCREEN");
					break;
					
				//...

			};
			break;
		
		//Obs:
		//essas teclas são tratadas pelo procedimento do sistema.
		//mas alguma tecla personalizada pode ser  tratada pelo aplicativo,
		//como o context menu [Application Key]
		case MSG_SYSKEYUP:
            switch(long1){
				
				//O MENU APPLICATION É O CONTEXT MENU.
				//
				case VK_APPS:
				    MessageBox( 1, "Gramado Core Shell:","Context Menu");
					break;
			}		
		    break;
		

        // Commands.		
		case MSG_COMMAND:
            switch(long1)
			{
				// Null.
				case 0:
				    MessageBox( 1, "Shell test","Testing MSG_COMMAND.NULL.");
				    break;
				
				// About.
				// Abre uma janela e oferece informações sobre o aplicativo.
				case CMD_ABOUT:
				    // Test.
				    MessageBox( 1, "Shell test","Testing MSG_COMMAND.CMD_ABOUT.");
				    break;
				
				//clicaram no botão
				case BN_CLICKED:
				    if(window == i1Window){
					     //@todo: abre o menu de aplicativos
					}
				    if(window == i2Window){
					   //@todo: abre o interpretador de comandos.
					}
					//#debug
					printf("  ** BN_CLICKED  **  \n");
				break;
				//...
				
				//default:
				//break;
			}
		    break; 		
		
		//Essa mensagem pode ser acionada clidando um botão.
		case MSG_CLOSE:
		    //??
		    //isso deve fechar qualquer janela que esteja usando esse procedimento.
			//pode ser uma janela filha ou ainda uma janela de dialogo criada pelo sistema.
			//??
		    printf("SHELL.BIN: MSG_CLOSE\n");
			
			//@todo: Criar essa função na api.
			//apiExitProcess(0);
			break;
		
		//Essa mensagem pode ser acionada clidando um botão.
		case MSG_DESTROY:
		    printf("SHELL.BIN: MSG_DESTROY\n");
		    break;
		
		//Quando a aplicativo em user mode chama o kernel para 
		//que o kernel crie uma janela, depois que o kernel criar a janela,
		//ele faz uma chamada ao procedimento de janela do aplicativo com a mensagem 
        //MSG_CREATE, se o aplicativo retornar -1, então a rotina em kernel mode que 
        //esta criando a janela, cancela a janela que está criando e retorn NULL.
        //		
		case MSG_CREATE:
		    printf("SHELL.BIN: MSG_CREATE\n");
		    break;
		
		case MSG_SETFOCUS:
		    APISetFocus(window);
			break;
			
		case MSG_KILLFOCUS:
            break;

		//isso pinta os elementos da área de cliente.	
        case MSG_PAINT:
            break;

		//@todo: isso ainda não existe na biblioteca. criar.	
        //case MSG_CLS:
            //limparemos o retãngulo da área de cliente,
			//mesmo que estejamos em full screen. 
		//	break;		
		
		//mudaremos o curso usando long1 e long2.
		//case MSG_SETCURSOR:
		//    break;
		
		//case MSG_HSCROLL:
		//    break;
		//case MSG_VSCROLL:
		//    break;
		
		
		//case MSG_FULLSCREEN:
		//    break;
		
		
		//case COMMAND_SET_WINDOW_SIZE:
		//    break;
		
		//case COMMAND_HIDE_WINDOW:
        //    break; 

		
		//#importante
		// os caracteres de controle encontrados na tabela ascii.
		//@todo: Essa mensagem precis ser criada, tanto no kernel 
		//quanto na API.
		//case MSG_ASCII_CONTROL_KEYS:
		//   switch(long1)
		//	{
	
		        //^A STX
                //case 1:
		        //    printf("^A");
                //    break;  		
	
		        //^B SOT
                //case 2:
		        //    printf("^B");
                //   break;  		
			
		        //^C ETX
                //case 3:
		        //    printf("^C");
		        //	shellPrompt();
                //    break;

		        //^D EOT
                //case 4:
		        //   printf("^D");
                //   break;

		        //^E ENQ
                //case 5:
		        //    printf("^E");
                //    break;  								
			
		        //^F ACK
                //case 6:
		        //    printf("^F");
                //    break;  					


		        //^G BEL
                //case 7:
		        //   printf("^G");
                //    break;  					
			
			
		        //^H BS
                //case 8:
                //    break;  								
			
		        //^I HT horizontal tab
                //case 9:
                //    break;  	

		        //^J LF
                //case 10:
                //    break;  			
			
						
		        //^K VT vertical tab
                //case 11:
                //    break;  	

		        //^L FF form feed
                //case 12:
                //    break;  	
			
			
		        //^M CR
                //case 13:
                //    break;  	
			

		        //^N SO
                //case 14:
                //    break;  				
		

		        //^O SI
                //case 15:
                //    break;


		        //^P DLE DATA LINK ESCAPE
                //case 16:
                //    break;  			
		
		
		        //^Q DC1 DEVICE CONTROL 1
                //case 17:
                //    break;  	
  			
			
		        //^R DC2 DEVICE CONTROL 2
                //case 18:
                //    break;

		        //^S DC3 DEVICE CONTROL 3
                //case 19:
                //    break;  			

		        //^T DC3 DEVICE CONTROL 4
                //case 20:
                //    break;  			
		
		
		        //^U NAK NEGATIVE ACKNOLEDGE
                //case 21:
                //    break;  			

		        //^V SYN SYNCHRONOUS IDLE
                //case 22:
                //    break;  			
		
		        //^W ETB END OF TRANSMISSION BLOCK
                //case 23:
                //    break;  			
		
		        //^X CAN CANCEL
                //case 24:
                //    break;  			

		
		        //^Y EM END OF MEDIUM
                //case 25:
                //    break;  			
		
		        //^Z SUB SUBSTITUTE
                //case 26:
                //    break;  			
		
		
		        //^[ ESC ESCAPE
                //case 27:
                //    break;  			
		
		        //^\ FS FILE SEPARATOR
                //case 28:
                //    break;  			
		
		        //^] GS GROUP SEPARATOR
                //case 29:
                //    break;  			
		
		        //^ RS RECORD SEPARATOR
                //case 30:
                //    break;  			
		
		
		        //_ US UNIT SEPARATOR
                //case 31:
                //    break;  			
		
		
		        //DELETE
                //case 127:
                //    break; 

        //    };		
		//    break;
			
		
		
		//Mensagem desconhecida.
		default:
		    //printf("shell procedure: mensagem desconhecida\n");
		    goto done;
		    break;	  
    };


    //
    // Nothing for now !
    //


//printf("Shell procedure\n");

	
	
done:
    //@todo: variavel que indica que estamos em modo gráfico.
	//if(VideoBlock.useGui == 1)
	//{
	    //Debug.
		//refresh_screen(); 
		//Obs: #bugbug perceba que o procedimento de janela do 
		//sistema também tem um refresh screen.
	//};	
	
	return (unsigned long) apiDefDialog(window,msg,long1,long2);
    //return (unsigned long) 0;	
};


/*
 * shellWaitCmd:
 *     Espera completar o comando com um [ENTER]. ##suspensa
 */
void shellWaitCmd()
{
	//
	// @todo: Cuidado com loop infinito.
	//
	
	//
	// Obs: Quem muda o status é o procedimento,
	//      quando recebe o retorno da função input:
	//
	
	
	//
	// Uma interrupção de teclado aciona o procedimento
	// do shell que atualiza o status.
	//
	
	
	
	//
	// BUG BUG :
    //
    //    Pra esse shell funcionar teria que habilita
    //    agora a interrupção de teclado e somente ela
    //    para que a interrupção de timer não bagunçe as
    //    coisas fazendo troca de contexto.
    //	
	//
	
	//asm("sti");    //@todo; Não habilitar!
	
    //Loop.  
	
    do{	 
		if( prompt_status == 1 ){
			prompt_status = 0;     
			return;
	    };
	
	}while(1);
	
exit:
    prompt_status = 0;
    return;	
};


/*
 **********************************************************
 * shellCompare:
 *     Compara comandos digitados com palavras chave.
 *     Compara a palavra em 'prompt[]' com outras e chama o serviço.
 * o enter foi o caractere digitado, vamos comparar palavras.
 *
 * Credits:
 * + Stephen Brennan - https://brennan.io/2015/01/16/write-a-shell-in-c/
 * + Frederico Lamberti Pissarra 
 * + Frederico Martins Nora (frednora)
 */
 
#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80
 
unsigned long shellCompare(struct window_d *window)
{
    unsigned long ret_value;
	
	// O input pode ser copiado aqui, então manipularemos essa variável.
	//char *FileName;
	
	//
	// ?? E se tivermos várias palavras na linha de comando ??
	//
		
    // Returns first token 
    //char *token = strtok(prompt, " -");
	
	//#debug
    //printf("shellCompare: Testing ...\n");
    //refresh_screen();	
   
    char *tokenList[TOKENLIST_MAX_DEFAULT];
    int i = 0;
	int token_count;
	
	
	// ?? what ?
    // first call returns pointer
	// to first part of user_input
	// separated by delim
	
    tokenList[0] = strtok( prompt, LSH_TOK_DELIM);
	
	
	//para o argumento atual
	//@todo: isso precisa ser limpado sempre.
	
	char *token;
	
	token = (char *) tokenList[0];
	
	i=0;                                  
    while( token != NULL )
	{
        // Coloca na lista.
        tokenList[i] = token;

		//#debug
		//Mostra
        //printf("shellCompare: %s \n", tokenList[i] );
        //refresh_screen();

		// Incrementa o índice da lista
        i++;
		
		token = strtok( NULL, LSH_TOK_DELIM );
		
		//salvando a contagem.
		token_count = i;
    }; 

	//Finalizando a lista.
    tokenList[i] = NULL;

	//#debug
    //printf("shellCompare: %s \n", tokenList[i] );
    //refresh_screen();	

	//#debug
    //printf("shellCompare: Test done!\n");
    //refresh_screen();	


	// Zerando o índice do tokenList
    i=0;	
   
    //printf("shellCompare: Testing ...\n");
    //refresh_screen();
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    //while(token != NULL)
    //{
    //    printf("%s\n", token);
	//	refresh_screen();
	//	token = strtok(NULL, " -");
    //}
	
		
		//do_command(argc, argv);
		goto do_command;	
	
	
do_command:	
    //nothing.	
do_compare:

    //
	// #Importante:
	// Devemos pegar os argumentos salvos na lista.
	// O primeiro argumento é o nome do aplicativo que deve ser executado
	// e os outros argumentos são argumentos que devem ser passados para 
	// o aplicativo a ser executado.
	//
	
	//
	// Talvez aqui devamos usar tokenList[0] e não prompt.
	//
	
    //@todo Criar sof links no vfs.
	//o vfs ficará no kernel base.
	//@todo: Criar chamadas ao vfs.
		
    // L1 RAM /objetcs   
	// (diretório raiz para os arquivos que são diretórios de objetos)
	// os objetos serão listador em um arquivo que nunca será salvo no disco.
	if( strncmp( prompt, "/objects", 6 ) == 0 )
	{
	    printf("info: Open object manager root dir ...\n");
        goto exit_cmp;
    };

	// L2 disk  /diretório raiz do sistema de arquivos.
	if( strncmp( prompt, "/", 5 ) == 0 )
	{
	    printf("info: Open file system root dir ...\n");
        goto exit_cmp;
    };

	// L3 LAN  // acesso a arquivos da lan
	//os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	if( strncmp( prompt, "/lan", 6 ) == 0 )
	{
	    printf("info: Open lan root dir ...\n");
        goto exit_cmp;
    };
 
	// L4 WAN   //acesso a arquivos da wan
	// os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	if( strncmp( prompt, "/wan", 6 ) == 0 )
	{
	    printf("info: Open wan root dir ...\n");
        goto exit_cmp;
    };
	
	
	//comentário
	// a linha é um comentário, podemos ignorar.
    if( strncmp( prompt, "//", 2 ) == 0 ){
		goto exit_cmp;
	};		
	
    //
	// Ordem alfabética.
	//
	

	
	//@todo
	//token
	//testando tokenList
	if( strncmp( prompt, "token", 5 ) == 0 )
    {
		printf("\nTesting tokenList ...\n");
		printf("\nTotal={%d}\n",token_count);
		printf("\n Comand = %s \n",tokenList[i]);
		refresh_screen();
		
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL ){
			goto exit_cmp;
		}else{
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i]);	
            
			if( strncmp( (char*) tokenList[i], "-a", 2 ) == 0 )
			{
			    printf("[OK] argumento %s selecionado.\n", tokenList[i]);
		    }
			//...
		};
		
		
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL ){
			goto exit_cmp;
		}else{
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i]);	
            
			if( strncmp( (char*) tokenList[i], "-b", 2 ) == 0 )
			{
			    printf("[OK] argumento %s selecionado.\n", tokenList[i]);
		    }
			//...
		};		
		
		
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL ){
			goto exit_cmp;
		}else{
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i]);	
            
			if( strncmp( (char*) tokenList[i], "-c", 2 ) == 0 )
			{
			    printf("[OK] argumento %s selecionado.\n", tokenList[i]);
		    }
			//...
		};		
		printf("\n");
		goto exit_cmp;
	};
    

    //
    // Início dos comandos.
    //
	
	//about 
	//isso é um teste.
	//mostra informações sobre o aplicativo usando 
	//um message box ou uma janela.
	if( strncmp( prompt, "about", 5 ) == 0 )
	{
		shellSendMessage( NULL, MSG_COMMAND, CMD_ABOUT, 0);
	    goto exit_cmp;
	}

	// Imprime a tabela ascii usando a fonte atual.
    // 128 chars.	
    if( strncmp( prompt, "ascii", 5 ) == 0 )
    {
		shellASCII();
		goto exit_cmp;
	}		
	
	// boot
	// ?? Boot info talvez.
	// ?? Talvez informações de boot ou configuração.
	if( strncmp( prompt, "boot", 4 ) == 0 )
	{
	    printf("~boot\n");
		//boot();
        goto exit_cmp;
    };
	
	// clear-screen-buffer
	if( strncmp( prompt, "clear-screen-buffer", 19 ) == 0 )
	{
		shellClearBuffer();
		goto exit_cmp;
	}	
	
	//close
	if( strncmp( prompt, "close", 5 ) == 0 )
	{
		shellSendMessage( NULL, MSG_CLOSE, 0, 0);
	    goto exit_cmp;
	}	
	
	
	
	//cd
	// change dir
	if( strncmp( prompt, "cd", 2 ) == 0 )
	{
	    goto exit_cmp;
	}		

	
    // cls
	// Clear the screen.
	if( strncmp( prompt, "cls", 3 ) == 0 )
	{
		//@todo
        shellClearScreen();
        shellSetCursor(0,0);
	    //shellPrompt();
        goto exit_cmp;
	};
	
	
	// copy
	if( strncmp( prompt, "copy", 4 ) == 0 )
	{
	    goto exit_cmp;
	}
	
	
	// date
	if( strncmp( prompt, "date", 4 ) == 0 )
	{
        goto exit_cmp;
    };	


	// del
	if( strncmp( prompt, "del", 3 ) == 0 )
	{
	    goto exit_cmp;
	}		
	
	
	// dir
	// Lista os arquivos no estilo DOS.
	if( strncmp( prompt, "dir", 3 ) == 0 )
	{
		//
		// @todo: get set disk id e directory id.
		//

        printf("~dir \n");		
        
		//#test 
		//173 Lista arquivos de um diretório, dado o número do disco,
        //o número do volume e o número do diretório,	
        system_call(173,0,0,0);		
		
		printf("~done\n");
        goto exit_cmp;
    };
	
	
	// echo
	// Echo de terminal.
    if( strncmp( prompt, "echo", 4 ) == 0 )
	{
		printf("%s\n",prompt[4]);
		//printf("%s\n",prompt);
		goto exit_cmp;
    };

	// editbox
	// Cria uma edibox.
    if( strncmp( prompt, "editbox", 7 ) == 0 )
	{
	    enterCriticalSection();    
	    shellCreateEditBox();
	    exitCriticalSection();    
		
		goto exit_cmp;
    };		
	
	
	// exit
	// Exit the application.
    if( strncmp( prompt, "exit", 4 ) == 0 )
	{
        printf("~exit\n");
		printf("Exiting shell process ...\n");
		refresh_screen();
		exit(0);
		goto exit_cmp;
    };
	
    //getpid
	if( strncmp( prompt, "getpid", 6 ) == 0 )
	{
	    shellShowPID();
        goto exit_cmp;
    };
	
    //getppid
	if( strncmp( prompt, "getppid", 7 ) == 0 )
	{
	    shellShowPPID();
        goto exit_cmp;
    };
	
	
    //getuid get user id
	if( strncmp( prompt, "getuid", 6 ) == 0 )
	{
	    shellShowUID();
        goto exit_cmp;
    };
	
	
    //getgid - get group id
	if( strncmp( prompt, "getgid", 6 ) == 0 )
	{
	    shellShowGID();
        goto exit_cmp;
    };
	
    //get-usersession
	if( strncmp( prompt, "get-usersession", 15 ) == 0 )
	{
	    shellShowUserSessionID();
        goto exit_cmp;
    };
	
	
    //get-windowstation
	if( strncmp( prompt, "get-windowstation", 17 ) == 0 )
	{
	    shellShowWindowStationID();
        goto exit_cmp;
    };
	
    //get-desktop
	if( strncmp( prompt, "get-desktop", 11 ) == 0 )
	{
	    shellShowDesktopID();
        goto exit_cmp;
    };

	
	// hd ??
	// hd info maybe.
    if( strncmp( prompt, "hd", 2 ) == 0 )
	{
	    printf("~hd\n");
        goto exit_cmp;
    };
	
	
	// help
	// ?
	// Mostra ajuda.
    if( strncmp( prompt, "help", 4 ) == 0 || 
	    strncmp( prompt, "?", 1 ) == 0 )
	{

		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			shellHelp();
			goto exit_cmp;
		}else{
		    //printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i]);	
            
			if( strncmp( (char*) tokenList[i], "-all", 4 ) == 0 )
			{   
				printf("Show all help topics.\n");
				shellHelp();
				goto exit_cmp;
			}
			
			if( strncmp( (char*) tokenList[i], "-min", 4 ) == 0 )
			{   
				printf("cls, help, exit ...\n");
				refresh_screen();
				//shellHelp();
				goto exit_cmp;
			}
			
			//...
		};
		
		//shellHelp();
		goto exit_cmp;
    };	
	
	
	// install	
    // ?? 
	if( strncmp( prompt, "install", 7 ) == 0 )
	{
	    printf("~install\n");
		//fs_install();
        goto exit_cmp;
    };
	
	
    // kernel-info
	if( strncmp( prompt, "kernel-info", 11 ) == 0 )
	{
	    shellShowKernelInfo();
        goto exit_cmp;
    };	
	
	
    // ls
	// lista arquivos no estilo unix.
	if( strncmp( prompt, "ls", 2 ) == 0 )
	{
		//@todo: Isso deve ser um aplicativo.
		printf("~ls\n");
        goto exit_cmp;
	};
	
	
    // mm-info
	if( strncmp( prompt, "mm-info", 7 ) == 0 )
	{
	    shellShowMemoryInfo();
        goto exit_cmp;
    };	
	
	
    // mm-kernelheap
	if( strncmp( prompt, "mm-kernelheap", 13 ) == 0 )
	{
	    shellShowKernelHeapPointer();
        goto exit_cmp;
    };

    // mm-processheap
	if( strncmp( prompt, "mm-processheap", 14 ) == 0 )
	{
	    shellShowProcessHeapPointer();
        goto exit_cmp;
    };

	// mov
	if( strncmp( prompt, "mov", 3 ) == 0 )
	{
	    goto exit_cmp;
	}		


    // metrics
	// Mostra algumas informações de métrica do sistema.
	if( strncmp( prompt, "metrics", 7 ) == 0 )
	{
		shellShowMetrics();
        goto exit_cmp;
	};	

	// new
	if( strncmp( prompt, "new", 3 ) == 0 )
	{
	    printf("~new - New file or directory\n");		
	    goto exit_cmp;
	}		
	
    
	// mbr
	// ?? Talvez mostrar informações sobre o mbr ou realizar testes.
    if( strncmp( prompt, "mbr", 3 ) == 0 )
	{
	    printf("~mbr\n");
		
		//#bugbug pagefault
		
		shellTestMBR();
		printf("done\n");
		goto exit_cmp;
    }; 
	
    // pci-info
	if( strncmp( prompt, "pci-info", 8 ) == 0 )
	{
	    shellShowPCIInfo();
        goto exit_cmp;
    };	
	
	// pwd - print working directory
	if( strncmp( prompt, "pwd", 3 ) == 0 )
	{
	    printf("~pwd - print working directory\n");
        system_call(170,0,0,0);		
	    goto exit_cmp;
	};		

	
    // reboot
    // @todo: Isso deverá ser um aplicativo.	
    if( strncmp( prompt, "reboot", 6 ) == 0 )
	{
	    printf("~reboot\n");
		system("reboot");
		goto exit_cmp;
    };
	
	// rename
	if( strncmp( prompt, "rename", 6 ) == 0 )
	{
        goto exit_cmp;
    };	
	
	
    // root
	// ??
    if( strncmp( prompt, "root", 4 ) == 0 )
	{
	    printf("~/root\n");
		//testa_root();
		goto exit_cmp;
    }; 

	
    // save
	if( strncmp( prompt, "save", 4 ) == 0 )
	{
	    printf("~save root\n");
        goto exit_cmp;
    };
	
	
	// service
	if( strncmp( prompt, "service", 7 ) == 0 )
	{
	    printf("~service - testa servicos do kernel:\n");
		//test_services();
        goto exit_cmp;
    };
	
	
	// show-screen-buffer
	if( strncmp( prompt, "show-screen-buffer", 18 ) == 0 )
	{
		shellShowScreenBuffer();
		goto exit_cmp;
	}

	

	
    // shellinfo
	// informações sobre o aplicativo.
	if( strncmp( prompt, "shellinfo", 9 ) == 0 )
	{
		
	    printf("~@todo: shell info.\n");
		shellShowInfo();
        goto exit_cmp;
    };	
	
	
    // shutdown
	if( strncmp( prompt, "shutdown", 8 ) == 0 )
	{
	    printf("~shutdown \n");
        goto exit_cmp;
    };	

	// slots
	if( strncmp( prompt, "slots", 5 ) == 0 )
	{
	    printf("~slots - mostra slots \n");
		//mostra_slots();
        goto exit_cmp;
    };
	
	
	// start
	// Inicia uma nova janela(instancia ??) para executar 
	// um programa ou comando desejado.
    if( strncmp( prompt, "start", 5 ) == 0 )
	{
		// Isso deve setar o foco na janela do shell.
		// ao mesmo tempo que reinicia o input para digitação 
		// e ajusta as margens do cursor. :)
		// Qualquer editbox precisa desse tipo de ajuste.
	    
		APISetFocus(window);
		//shellPrompt();
		printf("~start\n");
		
		goto exit_cmp;
    };

    // systeminfo
	// informações sobre o sistema.
	if( strncmp( prompt, "systeminfo", 10 ) == 0 )
	{
	    printf("~@todo: system info.\n");
		shellShowSystemInfo();
        goto exit_cmp;
    };	
	
	
    // t1 - Test file
	if( strncmp( prompt, "t1", 2 ) == 0 )
	{	
		// Carrega e exibe um arquivo.
		shellTestLoadFile();
		
		// teste.
		// Escreve no buffer de saída e mostra o buffer de saida.
		screen_buffer[0] = (char) 'F';
		screen_buffer[1] = 7;
		
        screen_buffer[2] = (char) 'N';	
        screen_buffer[3] = 7;
		
		screen_buffer[4] = (char) '\0';			
		screen_buffer[5] = 7;
		
		printf( (const char *) stdout->_base );
		
		printf("%s \n",stdout->_base);
		printf("%s \n",stdout->_tmpfname);
		printf("%d \n",stdout->_cnt);
		printf("%d \n",stdout->_bufsiz);
		printf("done \n");
		
        goto exit_cmp;
    };
	
	
	// t2 - Test bmp
	if( strncmp( prompt, "t2", 2 ) == 0 )
	{
		shellTestDisplayBMP();
        goto exit_cmp;
    };	
	
	
	// t3 - Test thread
	if( strncmp( prompt, "t3", 2 ) == 0 )
	{
	    shellTestThreads();
        goto exit_cmp;
    };
	
	// tasklist - Lista informações sobre os processos.
	if( strncmp( prompt, "tasklist", 8 ) == 0 )
	{
		shellTaskList();
        goto exit_cmp;
    };	
	
	// time
	if( strncmp( prompt, "time", 4 ) == 0 )
	{
        goto exit_cmp;
    };	
	
	
	// topbar
	// Cria uma top bar.
    if( strncmp( prompt, "topbar", 6 ) == 0 )
	{
	    enterCriticalSection();    
	    shellCreateTopBar();
	    exitCriticalSection();    
		
		goto exit_cmp;
    };			
	
	
	// tree
	// Desenha uma pequena árvore.
    if( strncmp( prompt, "tree", 4 ) == 0 )
	{
		shellTree();
		goto exit_cmp;
    };			
	
	
	// version
    if( strncmp( prompt, "version", 7 ) == 0 )
	{
	    printf("\n Gramado version %s \n", OS_VERSION );
        goto exit_cmp;
    };

	// window
    if( strncmp( prompt, "window", 6 ) == 0 )
	{
		shellShowWindowInfo();
        goto exit_cmp;
    };



 
 
    //
    // Se apertamos o enter e não encontramos um comando válido
    // então damos um aviso de comando inválido e reiniciamos o prompt 
    // na próxima linha.
    //
 
palavra_nao_reservada:

    //
	// ## TEST ##
	//

    //
	// Se estamos aqui é porque o comando não corresponde a
	// nenhuma das palavras reservadas acima, então executaremos
	// presumindo ser um nome de aplicativo no formato 'test.bin'
	// Obs: Isso é um teste, o comando digitado ainda 
	// precisa de mais análises como as barras '/'
	//
	//

    //Presumindo ser um nome de aplicativo no formato 'test.bin'.
	//shell_gramado_core_init_execve( "testtest.bin", 0, 0 );
    shell_gramado_core_init_execve( (const char*) prompt, 0, 0 );
	goto exit_cmp;
	
    //shellParseFileName(); @todo
	
	// Se a apavra não é reservada, então talvez seja o nome de um app.
	// Procuraremos esse app no diretório corrente.
	//@todo: criar o ponteiro app_name
	//while( *app_name == ' ' )
    //    app_name++;

    //@todo: Criar função, argumentos e retorno.
    //app_return = shellExecute( app_name );
	
	//switch( app_return )
	//{
		//retorno null.
	//	case 0:
	//	    break;
			
		//@todo Criar os tipos de erro possíveis.	
	//	case xxx:
    //        break;

        //...
		
	//	default:
	//	    app_return = 0;
    //        break;		
	//};
	
	
	// set cursor ?
	
	// set current directory
	
	
	printf(" Unknown command!\n");
	printf("%s\n", prompt);
	shellPrompt();
	//Mostrando as strings da rotina de comparação.
	refresh_screen(); 	
	return (unsigned long) 1;
	
exit_cmp:

	// Limpando a lista de argumentos.
	// Um array de ponteiros.
	
	for( i=0; i<TOKENLIST_MAX_DEFAULT; i++ ){
		tokenList[i] = NULL;
	};
	
	// Limpando o buffer de entrada
	
	shellPrompt();
	//Mostrando as strings da rotina de comparação.	
	refresh_screen(); 
    return (unsigned long) 0;
};


/*
 ******************************************
 * shellShell:
 *     Constructor.
 *     Não emite mensagens.
 */
void shellShell()
{
	int i=0;
	
	//
	// Internas.
	//
	
	//
	// Obs: Configurar cursor para tela pequena.
    // Screen 320x480.(Celular).
	// Client Area = (Altura - 24)
    //	
	
    shellStatus = 0;
    shellError = 0;
	
	//
	// Deve ser pequena, clara e centralizada.
	// Para ficar mais rápido.
	//
	
	//
	// Usar o get system metrics para pegar o tamanho da tela.
	//
	
	// Tamanho da tela.	
	//screen sizes
	shellScreenWidth  = apiGetSystemMetrics(1);
    shellScreenHeight = apiGetSystemMetrics(2); 	
	
	//Tamanho da janela do shell	
	shellWindowWidth = 640;
	shellWindowHeight = 480; 
	
	//window position
	shell_window_x = (unsigned long) ( (shellScreenWidth - shellWindowWidth)/2 );
	shell_window_y = (unsigned long) ( (shellScreenHeight - shellWindowHeight)/2 );   
	
    shellMaxColumns = DEFAULT_MAX_COLUMNS;  // 80; shellWindowWidth/8
    shellMaxRows    = DEFAULT_MAX_ROWS;     // 25; shellWindowHeight/8
 
    //...	

	//
	// Setup buffers.
	//
	
    // reiniciando as variáveis na estrutura do output
	stdout->_base = &screen_buffer[0];
	stdout->_ptr = stdout->_base;
	stdout->_cnt = PROMPT_MAX_DEFAULT;
	stdout->_file = 1;
	stdout->_tmpfname = "shell_stdout";
	//...	
	//
	// Obs:
	// shell_buffer[] = Aqui é o buffer de output. 
	// prompt[] - Aqui ficam as digitações. 
	//
	shellClearBuffer();

	
	//shellBufferMaxColumns = DEFAULT_BUFFER_MAX_COLUMNS;
	//shellBufferMaxRows    = DEFAULT_BUFFER_MAX_ROWS;
	
	//buffersize = (shellBufferMaxColumns * shellBufferMaxRows);
	

	
	//
	// @todo: E o fluxo padrão. Quem configurou os arquivos ???
	//        o kernel configuroru???
	//
	
	// Número máximo de colunas e linhas.
	g_columns = shellMaxColumns;  // 80;
	g_rows = shellMaxRows;        // 25;
    //...
	
	
	for( i=0; i<WORKINGDIRECTORY_STRING_MAX; i++ ){
		current_workingdiretory_string[i] = (char) '\0';
	};
	
    sprintf( current_workingdiretory_string, 
	         SHELL_UNKNOWNWORKINGDIRECTORY_STRING );    
	
	//...
	
done:

    ShellFlag = SHELLFLAG_COMMANDLINE;
	
    //#bugbug
	//Nossa referência é a moldura e não a área de cliente.
	//@todo:usar a área de cliente como referência
	//shellSetCursor(0,0);
    //shellSetCursor(0,4);
    
	//@todo
	//tentando posicionar o cursor dentro da janela
	//shellSetCursor( (shell_info.main_window->left/8) , (shell_info.main_window->top/8));	
	
	//shellPrompt();
    return;	
};



/*
 ********************************************************************
 * shellInit:
 *     Inicializa o Shell.  
 *
 *     #bugbug: 
 *     Essa rotina começa escrever na janela com o foco de entrada. Mas um 
 * outro aplicativo solicitou o foco de entrada e essa rotina esta terminando 
 * de escrever mas agora na janela do outro aplicativo.
 *
 * @todo: Inicializar globais e estruturas.
 *
 */
int shellInit( struct window_d *window )
{
	int PID;
	int PPID;
	int ActiveWindowId = 0;
	int WindowWithFocusId = 0;
	void *P;
	int CurrentVolumeID = 0;
	
	//
	// #bugbug:
    //     Esse ponteiro de estrutura está em kernel mode. 
	//     Não podemos usá-lo.
	//
	
	//stream status
	shell_info.stream_status = 0;
	
	
	//
	// Antes dessa função ser chamada, o foco foi setado 
	// na janela do aplicativo.
	// Test: Não mechemos no cursor nesse momento, deicharemos 
	// a função SetFocus configurar o curso.
	// Não mostraremos o prompt, somente depois dos testes de inicialização.
	//
	//
	
    //bugbug	
	//cursor
	//shellSetCursor(0,4);
	
	//pointer
	//shellPrompt();
    
	// message.
    //printf("shellInit: Running tests ...\n");	


	//
	// Window support.
	//

	// Testando a validade do ponteiro da janela.
	// #importante: A estrutura está em kernel mode 
	// e não podemos acessa-la.
	
	if( (void*) window == NULL ){
	    printf("shellInit: window fail.\n");    
	}else{
		
		// Nesse momento temos um ponteiro válido,
		// mas infelismente não podemos testar outros elementos 
		// da estrutura.
		
		APISetFocus( window );
		
		//
		// mensagens !!
		//
		
		printf("shellInit: Starting shell.bin ... \n");
		printf("shellInit: Running tests ...\n");	
	};
	
	
	//
	// Obtendo informações sobre a janela ativa.
	//
	
	//Active window
	ActiveWindowId = (int) APIGetActiveWindow();
	
	//valor de erro
	if( ActiveWindowId == (-1)){
	    printf("shellInit: ERROR getting Active window ID\n");	
	}	
	printf("ActiveWindowId={%d}\n", ActiveWindowId );

	
	//
	// Obtendo informações sobre a janela com o foco de entrada.
	//


	//
	// Focus.
	WindowWithFocusId = (int) APIGetFocus();
	
	//valor de erro
	if( WindowWithFocusId == (-1)){
	    printf("shellInit: ERROR getting Window With Focus ID\n");	
	}	
	printf("WindowWithFocusId={%d}\n", WindowWithFocusId );	
	
	
	//
	// Obetendo informações sobre linhas e colunas do shell.
	//
	
	
	//columns and rows
	printf("shellMaxColumns={%d} \n", shellMaxColumns );
	printf("shellMaxRows={%d} \n", shellMaxRows );	
		
	
	
	//
	// Process support.
	//
	
	//
	// @todo: 
	// Essa mensagem está aparecendo fora da área de trabalho do shell
	// pois ainda não temos um ponteiro para a memória que representa essa área.
	// Talvez as mensagens devessem ir para um buffer de linha antes de irem 
	// para a memória de vídeo.
	// #Impotante:
	// Devemos utilizar as configurações de terminal virtual, respeitar a estrutura 
	// de terminal, que indicará qual é a janela de terminal onde os caracteres 
	// devem ser escritos. Na verdade é um ponteiro para um retãngulo e não para 
	// uma janela. Obs: Esse retângulo do terminal deve esr configurável e uma rotina 
	// deve dar suporte a essa configuração.
	//
	
	//
	// @todo: 
	// O que tevemos fazer aqui é pegar informações sobre o processo Shell
	// e coloca-las na tela.
	//
	
	//
	// @todo: Criar na API uma rotina de inteface que use essa chamada.
	// ex: APIGetPID().
	//
	
	//PID = (int) APIGetPID();
	
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	if( PID == (-1)){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
	if( PPID == (-1)){
	    printf("ERROR getting PPID\n");	
	}
  
	printf("Starting SHELL.BIN ... PID={%d} PPID={%d} \n", PID, PPID );
	
	

	
	//
	// @todo: Criar processos processos:
	//     E.BIN, F.BIN, G.BIN, A.BIN, B.BIN, C.BIN, D.BIN
 	//     (Mermaids) Usados para testes.
	//

	printf("Creating processes ...\n");
	
	//D.:)
	P=(void*)apiCreateProcess(0x400000,PRIORITY_HIGH,"D");
	if((void*)P==NULL){printf("Fail creating process D :)\n");};
	//C.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_HIGH,"C");
	if((void*)P==NULL){printf("Fail creating process C.\n");};
	//B.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_HIGH,"B");
	if((void*)P==NULL){printf("Fail creating process B.\n");};
	//A.(Balance).
	P=(void*)apiCreateProcess(0x400000,PRIORITY_NORMAL,"A");	
	if((void*)P==NULL){printf("Fail creating process A.\n");};
	//G.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_LOW,"G");	
	if((void*)P==NULL){printf("Fail creating process G.\n");};
	//F.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_LOW,"F");
	if((void*)P==NULL){printf("Fail creating process F.\n");};
	//E.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_LOW,"E");	
	if((void*)P==NULL){printf("Fail creating process E :( \n");};
	
	printf("Created!\n");
	//...
	
	
	
	//
	//@todo: 
	// Devemos implementar uma rotina de inicialização dessas threads 
	// criadas através de chamadas ao sistema.
	//
	
	//printf("Initializing a thread...\n");
	//...
	
	//Testando bibliotecas.
	//printf("Testing libraries:\n");	
	
	//stdio.h
	//printf("Testing stdio:\n");
	//app_clear(0);  //Não fez nada.
    //...

	//stdlib.h
	printf("Testing stdlib:\n");
	
	//
	// *Importante:
	//     Isso inicializa o gerenciamento de memória oferecido pela 
	// biblioteca C99 em user mode. Coisas como inicializar o 'heap'
	// oferecido pela biblioteca.
	// Agora poderemos alocar memória dentro do heap oferecido pela biblioteca.
	//
	
//initRT:	
	//libcInitRT(); 
	
	//Obs: Sempre inicia com o mesmo número.
	int rand_value;
	rand_value = (int) rand();
	printf("RandValue1={%d}\n", rand_value);
	//rand_value = (int) rand();
	//printf("RandValue2={%d}\n", rand_value);
    //rand_value = (int) rand();
	//printf("RandValue3={%d}\n", rand_value);
	//...
	

	//stddef.h
	//printf("Testing stddef:\n");	
	
	//Testing COLUMNS
	
	//Testing ROWS
	
	
	//testando api.h
	//...
	
	
	//Funcionou...
	//sprintf( shell_buffer,"Testando String dentro do buffer\n");
	//printf("%s",shell_buffer);
	

	//
	// Get process info.
	//
	
	
	//
	// Get thread info.
	//
	

	
	//
	// Testing commands.
	//

	//Lib C.
	//libC. (stdlib.c)
	system("test");       
	system("ls");
	system("start");
	system("xxfailxx");
	//...
	
	//API.
	apiSystem("test");    
    apiSystem("ls");
	apiSystem("start");
	apiSystem("xxfailxx");
	//...
	
	//Ok funcionando ...
	//@todo: Testar outros comandos.
	//...
	
	
	//Testing message box.
	//MessageBox(3, "Shell message box","Testing message box...");
	
	//
	// @todo: Clear client area.
	//        System call redraw client area.
	
	
	//test: get current volume id.
	CurrentVolumeID = (int) system_call(171,0,0,0);		

	printf("The current volume id is %d\n",CurrentVolumeID);
	
	// setup ID.
	shellUpdateCurrentDirectoryID(SHELL_ROOTWORKINGDIRECTORY_ID);
	
	// updating the current working directory string.
	shellUpdateWorkingDiretoryString(SHELL_ROOTWORKINGDIRECTORY_ID);
	
	
done:
    //
	// Testing welcome message.
	//
	
	/*
	printf("...\n");
	test_operators();
	*/
	
	printf("...\n");
	printf("Welcome to Gramado Operating System.\n");
	printf("Done!");
	
	
	//
	// @todo:
	// Gerenciamento do heap do processo. ??
	//
	
	
	//
	// @todo:
	// Chamar rotinas da biblioteca que ofereçam informações sobre 
	// o heap oferecido pela biblioteca.
	// Obs: A rt foi inicializada logo acima.
    //	
	
	
    //heapTest:
    /*	
	printf("\n...\n");
	printf("Testing C99 RT ...\n");
	
	unsigned long hStart, hEnd, hPointer, hAvail;
	
	hStart   = (unsigned long) rtGetHeapStart();
	hEnd     = (unsigned long) rtGetHeapEnd();
	hPointer = (unsigned long) rtGetHeapPointer();
	hAvail   = (unsigned long) rtGetAvailableHeap();
	
	printf("heapStart{%x} heapEnd{%x} heapPointer{%x} heapAvailable={%x}\n", 
	     hStart, hEnd, hPointer, hAvail);
	
	// resultados do teste:
	// os valores parecem satisfatórios pois estão realmente dentro da área 
	// de memória do aplicativo.
	// @todo: Confirmar no memorymap gerado pelo compilador se essa área de memória 
	// é apropriada. #bugbug
	// observando o mmmap pelo jeito o compilador colocou o buffer do heap 
	// no bss do arquivo e do tamanho certo.
	// tudo indica que é saudável aumentar o tamanho do buffer usado pelo heap.
	//
	*/
	
	shellPrompt();
    refresh_screen();
	
    return (int) 0;
};


/*
 * shellSetCursor:
 *     Configurando o cursor. (stdio.h).
 *
 * @todo: Aqui quando definimos os valores o cursor no shell 
 * devemos considerar que a janela com o foco de entrada tambem tem um cursor...
 * Temos que atualizar o cursor da janela com foco de entrada se quizermos 
 * escrever corretamente dentro dela.
 * e isso se faz através de uma chamada ao kernel.
 */
void shellSetCursor(unsigned long x, unsigned long y)
{	
    //setando o cursor usado pelo kernel base.	
    apiSetCursor(x,y);
	
//Atualizando as variáveis globais usadas somente aqui no shell.
setGlobals:	
    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;	
	return;
};


/*
 *******************************************
 * shellThread:
 *     Um thread dentro para testes.
 */
void shellThread()
{
	// ?? Message Box ??
	
    printf("shellThread: This is a thread for test!\n");
    refresh_screen();
	
    while(1){	
	    //printf("$");
    }	
};


//help message
void shellHelp(){
    printf(help_banner);	
	return;
};

//drawing a tree
void shellTree(){
    printf(tree_banner);	
	return;
};

//
// C function to demonstrate the working of arithmetic operators
//#include <stdio.h>
int test_operators()
{
    int a = 9,b = 4, c;
    
	printf("Testing operators ...\n");
	
    c = a+b;
    printf("a+b = %d \n",c);

    c = a-b;
    printf("a-b = %d \n",c);
    
    c = a*b;
    printf("a*b = %d \n",c);
    
    c=a/b;
    printf("a/b = %d \n",c);
    
    c=a%b;
    printf("Remainder when a divided by b = %d \n",c);
    
    return 0;
};


/*
 ********************************************************************
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicialização de stdio, prompt foi definido como stdin->_base.
 */
void shellPrompt()
{	
	int i;
	
	//Linpando o buffer de entrada.
	for( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
		prompt[i] = (char) '\0';
	};
	
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_status = 0;
	prompt_max = PROMPT_MAX_DEFAULT;  

    printf("\n");	
	printf("%s/%s",current_workingdiretory_string ,SHELL_PROMPT );
	return;
};


/*
 * shellClearBuffer:
 *     Limpa o buffer da tela.
 */
void shellClearBuffer()
{
	int i;
	
	// Shell buffer.
	for( i=0; i<SCREEN_BUFFER_SIZE; i++){
		screen_buffer[i] = (char) '\0';
	}
	
	screen_buffer[0] = (char) '\0';
	screen_buffer[1] = 7;
	
    screen_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};



//Isso é só um teste.
void shellShowScreenBuffer()
{
	int i;
	int j = 0;
	
    shellClearScreen();
    shellSetCursor(0,0);	
	
	// Shell buffer.
	for( i=0; i<SCREEN_BUFFER_SIZE; i++)
	{
		
	    printf( "%c", screen_buffer[j] );
		j++; //ignora o atributo.
		j++;
	};	

    screen_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};


/*
 * shellTestLoadFile:
 *     Carrega um arquivo de texto no buffer e mostra na tela.
 */
void shellTestLoadFile()
{
	shellClearBuffer();
	shellClearScreen();
    shellSetCursor(0,0);
	shellPrompt();
	//@todo: reposicionar o cursor.
	
	//
	// *Testando carregar um arquivo.
	// Ok, isso funcionou.
	//
	
	int fRet;
	printf("...\n");
	printf("Testing buffer ... Loading file...\n");
	
	//A QUESTÃO DO TAMANHO PODE SER UM PROBLEMAS #BUGBUG ;... SUJANDO ALGUMA ÁREA DO SHELL
	fRet = (int) system_call( SYSTEMCALL_READ_FILE, 
	                          (unsigned long) init_file_name, 
					          (unsigned long) &screen_buffer[0], 
							  (unsigned long) &screen_buffer[0] );
							  
	printf("ret={%d}\n",fRet);
	
	printf("...\n\n");
	printf(&screen_buffer[0]);		
};


/*
 * shellTestThreads:
 *     Cria um thread e executa.
 *     #bugbug ...já funcionou uma vez.
 */
void shellTestThreads()
{
    void *T;	
	//
	// Obs: As threads criadas aqui etão sendo atribuídas ao processo PID=0.
	//      @todo: No kernel, quando criar uma thread ela deve ser atribuída
    //      ao processo que chamou a rotina de criação.	
	//
	printf("Creating threads...\n");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread1");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread2");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread3");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread4");
	//...
	
	//
	// Tentando executar um thread.
	//
	
	
	// *******************************
     //OBS: ISSO FUNCIONOU. ESTAMOS SUSPENDENDO PORQUE PRECISAMOS AUMENTAR O TAMANHO DO 
     //     HEAP USADO PELO PROCESSO PARA ALOCAÇÃO DINÂMICA, ELE NÃO TA DANDO CONTA 
     //     DE TODA A DEMANDA POR MEMÓRIA.		  
	
	//>>dessa vez pegaremos o retorno, que deve ser o ponteiro para a estrutura da thread.
	//>>chamaremos a systemcall que executa essa thread que temos o ponteiro da estrutura.
    void* ThreadTest1;	
	
	//#bugbug, não temos mais epapo no heap do preocesso para alocar memória 
	//pois gastamos o heap com a imagem bmp.
	//
	unsigned long *threadstack1;
	threadstack1 = (unsigned long *) malloc(30*1024);
	threadstack1 = ( threadstack1 + (30*1024) - 4 ); //Ajuste para o início da pilha.
	ThreadTest1  = (void*) apiCreateThread( (unsigned long)&shellThread, 
	                                        (unsigned long) threadstack1, 
										    "ThreadTest1" );
										   
	
	printf("shell: Tentando executar um thread ...\n");
	refresh_screen();
	
	if( (void*) ThreadTest1 == NULL ){
	    printf("shell: Tentando executar um thread FAIL NULL ...\n");	
	    refresh_screen();
		while(1){}
	}
	//Lá no kernel isso deve selecionar a thread para execussão colocando ela no estado standby
	apiStartThread(ThreadTest1);
	printf("shell: Tentando executar um thread [ok] hang...\n");
	refresh_screen();
	
	//while(1){}
	// **************************
	return;	
};


/*
 * shellClearScreen:
 *     Limpar a tela do shell.
 */
void shellClearScreen()
{
	int lin, col;    

	// @todo:
	//system( "cls" ); // calls the cls command.
	
	//cursor.
	shellSetCursor(0,0);
	
	//
	// Tamanho da tela. 80x25
	//
	
	//linhas.
	for( lin=0; lin < 25; lin++)
	{
		col = 0;
		shellSetCursor(col,lin);
		
		//colunas.
		for( col=0; col < 80; col++)
		{
		    //@todo:
			printf("%c",' ');
	    }
	};
	
	shellSetCursor(0,0);
};


/*
 * shellRefreshScreen:
 *     Copia o conteúdo do buffer de output para a tela. (dentro da janela).
 *
 */
void shellRefreshScreen()
{
	int i;

	//cursor apontando par ao início da janela.
	//usado pelo printf.
	shellSetCursor(0,0);
	
	//o certo é copiar o buffer todo e a rotina printf faz o scroll
	
	//for( i=0; i < SCREEN_BUFFER_SIZE; i++)
	for( i=0; i < (80*25); i++)
	{
		printf("%c", stdout->_ptr[i]);
	};
	
    //shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};


/*
 * shellScroll:
 *     @todo:
 */
void shellScroll()
{
	int i;
	
	//cursor apontando par ao início da janela.
	shellSetCursor(0,0);
	
	// tamanho da tela.
	for( i = 0; i < ( 80*25 ); i++ )
	{
        //começa da segunda linha e copia a tela toda.
		printf("%c", stdout->_ptr[i+80]);
	};
	
    //screen_buffer_pos = 0;  //?? posição dentro do buffer do shell.		
};



static void save_cur(void)
{
	saved_x = screen_buffer_x;
	saved_y = screen_buffer_y;
};


static void restore_cur(void)
{
	x = saved_x;
	y = saved_y;
	//pos = origin + ( (y * columns + x) << 1 );
	screen_buffer_pos = origin + (screen_buffer_y * columns + screen_buffer_x);
};


static void lf(void)
{
	if (screen_buffer_y+1 < bottom) {
		screen_buffer_y++;
		screen_buffer_pos += columns;  //pos += columns<<1;
		return;
	}
	//scrup();
};


static void ri(void)
{
	if (screen_buffer_y>top) {
		screen_buffer_y--;
		screen_buffer_pos -= columns; //screen_buffer_pos -= columns<<1;
		return;
	}
	//scrdown();
};


static void cr(void)
{
	screen_buffer_pos -= screen_buffer_x; //pos -= x<<1;
	screen_buffer_x=0;
};


static void del(void)
{
	int i = (int) (screen_buffer_pos * 2);
	
	screen_buffer[i] = (char) '\0';
	screen_buffer[i +1] = 7;
};


//insere um caractere entro do buffer
void shellInsertCharXY(unsigned long x, unsigned long y, char c)
{
	unsigned long offset = (unsigned long) ((y*80) + x); 
	
	if(x>=80){
		return;
	}
	
	if(y>=25){
		return;
	}

	screen_buffer[offset*2] = (char) c;
	screen_buffer[ (offset*2)+1 ] = 7;
};


//insere um caractere no buffer de output 
//#bugbug, talvez o buffer seja stdout. 
void shellInsertCharPos(unsigned long offset, char c)
{
	unsigned long offsetMax = (unsigned long)(80*25); 
		
	if(offset >= offsetMax){
		return;
	}
	
	screen_buffer[offset*2] = (char) c;
	screen_buffer[ (offset*2)+1 ] = 7;
};


/*
//inserindo uma string em uma posição do buffer de saída.
void shellInsertStringPos( unsigned long offset, char *string );
void shellInsertStringPos( unsigned long offset, char *string )
{
    //@todo
};
*/

/*
 preenche todo o buffer de saída com char ou atributo
void shellFillOutputBuffer( char element, int element_type )
{
	
}
*/

//coloca um char na próxima posição do buffer
void shellInsertNextChar(char c)
{
	screen_buffer[ screen_buffer_pos*2 ] = (char) c;
	screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;
};


void shellInsertCR()
{
   screen_buffer[screen_buffer_pos*2 ] = (char) '\r';
   screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;   
};


void shellInsertLF()
{
    screen_buffer[ screen_buffer_pos*2 ] = (char) '\n';
    screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;	
};


void shellInsertNullTerminator()
{
    screen_buffer[ screen_buffer_pos*2 ] = (char) '\0';
    screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;	
};



/*
 * shellTestMBR:
 *     Testar a leitura de um setor do disco.
 *     Testaremos o setor do mbr.
 *
 */
void shellTestMBR()
{
	unsigned char buffer[512];
	
	enterCriticalSection(); 
	
	//message 
	printf("shellTestMBR: Initializing MBR test ...\n");
	
	//read sector
	system_call( SYSTEMCALL_READ_LBA, 
	             (unsigned long) &buffer[0],  //address 
				 (unsigned long) 0,           //lba
				 (unsigned long) 0);
				 
	
	exitCriticalSection();   
	
	//
	// exibe o conteúdo carregado.
	//
	
	//?? address #bugbug
	printf("%s",&buffer[0]);
	
	//
	// @todo: Sondar cada elemento do MBR para 
	// confirmar a presença.
	//
	
done:
	printf("done");
	refresh_screen(); //??
	return;
};



/*
 * move_to:
 *    Posicionamento dentro do buffer.
 */
void move_to( unsigned long x, unsigned long y )
{
	if( x > DEFAULT_BUFFER_MAX_COLUMNS ){
		return;
	}

	if( y > DEFAULT_BUFFER_MAX_ROWS ){
		return;
	}
	
	screen_buffer_x = x;
	screen_buffer_y = y;
	return;
};


//show shell info
void shellShowInfo()
{
	int PID, PPID;
	
	
    printf("shellShowInfo: Showing some infos ...\n");
	
	
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	if( PID == (-1)){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
	if( PPID == (-1)){
	    printf("ERROR getting PPID\n");	
	}
  
	printf("Process info: PID={%d} PPID={%d} \n", PID, PPID );
	
	
	printf("shellMaxColumns={%d} \n", shellMaxColumns );
	printf("shellMaxRows={%d} \n", shellMaxRows );	
	
};


//metrics
void shellShowMetrics()
{
	unsigned long screen_width;
	unsigned long screen_height;
	unsigned long cursor_width;
	unsigned long cursor_height;
	unsigned long mouse_pointer_width;
	unsigned long mouse_pointer_height;
	unsigned long char_width;
	unsigned long char_height;	
	//...

	screen_width         = apiGetSystemMetrics(1);
	screen_height        = apiGetSystemMetrics(2);
	cursor_width         = apiGetSystemMetrics(3);
	cursor_height        = apiGetSystemMetrics(4);
	mouse_pointer_width  = apiGetSystemMetrics(5);
	mouse_pointer_height = apiGetSystemMetrics(6);
	char_width           = apiGetSystemMetrics(7);
	char_height          = apiGetSystemMetrics(8);
	//...
	
	
	printf("shellShowMetrics:\n");
	printf("screenWidth={%d} screenHeight={%d}\n",screen_width,screen_height);
	printf("cursorWidth={%d} cursorHeight={%d}\n",cursor_width,cursor_height);
	printf("mousepointerWidth={%d} mousepointerHeight={%d}\n", 
	        mouse_pointer_width,mouse_pointer_height);
	printf("charWidth={%d} charHeight={%d}\n",char_width,char_height);	
	//...
	
	
done:	
    printf("Done\n");	
	return;
};

//show system info
void shellShowSystemInfo()
{
	int ActiveWindowId;
	int WindowWithFocusId;
	
	
	printf("shellShowSystemInfo:\n");
	
	//
	//Active
	ActiveWindowId = (int) APIGetActiveWindow();
	
	//valor de erro
	if( ActiveWindowId == (-1)){
	    printf("ERROR getting Active window ID\n");	
	}	
	printf("ActiveWindowId={%d}\n", ActiveWindowId );


	//
	// Focus.
	WindowWithFocusId = (int) APIGetFocus();
	
	//valor de erro
	if( WindowWithFocusId == (-1)){
	    printf("ERROR getting Window With Focus ID\n");	
	}	
	printf("WindowWithFocusId={%d}\n", WindowWithFocusId );	
	
};

//mostrar informações sobre janelas.
void shellShowWindowInfo()
{
	
	//
	// #bugbug.
	// Testando a estrutura de janela.
	// A janela foi criada pelo kernel e copiamos o ponteiro 
	// da estrutura para um ponteiro em user mode.
	// Podemos ter erros de memória com essas operações.
		
	printf("\n shell_info: \n");
		
	// esse printf funcionou.
	printf("mainWindow={%x}", shell_info.main_window );
		
	//#bugbug 
	//temos um problema aqui.
	// provavelmente o erro é por acessar um endereço que está 
	// em kernel mode.
	//if( shell_info.main_window->left > 0 && shell_info.main_window->top > 0  )
	//{
	//    shellSetCursor( (shell_info.main_window->left/8), (shell_info.main_window->top/8) );
	//}
		
		
	printf("\n terminal_rect: \n");	
    printf("l={%d} t={%d} w={%d} h={%d}\n", terminal_rect.left,
		                                    terminal_rect.top,
									  	    terminal_rect.width,
											terminal_rect.height );

													  
	//Obs: isso funcionou. setando o cursor.
	//if( terminal_rect.left > 0 && terminal_rect.top > 0 )
	//{											  
    //    shellSetCursor( (terminal_rect.left/8), (terminal_rect.top/8) );													  
	//};
		
    int wID;		
	wID = (int) system_call( SYSTEMCALL_GETTERMINALWINDOW, 0, 0, 0); 
	
	printf("\n current terminal: \n");
	printf("Windows ID for current terminal = {%d} \n", wID);
	
	//...
};


/*
 * shellASCII:
 *     Mostrar os caracteres da tabela ascii padrão.
 *     O padrão tem 128 chars.
 *     Obs: Na fonte ROM BIOS temos esse padrão.
 */
void shellASCII()
{
    unsigned char count;
	unsigned char standard_ascii_max = 128;
	
	
	printf("shellASCII:\n");
	
    for( count=0; count<standard_ascii_max; count++ )
    {
		printf(" %d - %c",count,count);
        if( count % 4 == 0 ){
            printf("\n");
		}
    };	
};


//??
//void shellSetScreenColors( ... ){}

//??
//void *shellGetTerminalWindow(){}

//void shellSetTerminalRectangle(....){}

//void *shellOpenTerminal(.){}



				  
unsigned long 
shellSendMessage( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 )
{
	return (unsigned long) shellProcedure( window, msg, long1, long2 );
};


//copia bytes	
void shell_memcpy_bytes( unsigned char *Dest, 
                         unsigned char *Source,
                         unsigned long Length )
{
    while(Length--)
        *Dest++ = *Source++;
}


/*
 * shell_write_to_screen:
 *     refresh de um retângulo ??    
 */
/* 
void shell_write_to_screen( struct shell_screen_d *screen, 
                            struct shell_rect_d *region )
{
    //@todo	
};
*/

/*
 * @todo: Criar rotina de saída do shell.
void shellExit(int code);
void shellExit(int code){
	exit(code);
}
*/


/*
void die(char * str);
void die(char * str)
{
	fprintf(stderr,"%s\n",str);
	exit(1);
}
*/

void shellUpdateWorkingDiretoryString( int id )
{
    switch(id)
    {
		// ROOT
		case 0:
	        sprintf( current_workingdiretory_string, 
	                 SHELL_ROOTWORKINGDIRECTORY_STRING ); 		
		    break;

		// BOOT	
		case 1:
	        sprintf( current_workingdiretory_string, 
	                 SHELL_BOOTWORKINGDIRECTORY_STRING ); 		
		    break;

		// SYSTEM	
		case 2:
	        sprintf( current_workingdiretory_string, 
	                 SHELL_SYSTEMWORKINGDIRECTORY_STRING ); 		
		    break;

		// UNKNOWN	
		default:
	        sprintf( current_workingdiretory_string, 
	                 SHELL_UNKNOWNWORKINGDIRECTORY_STRING ); 		
		    break;
	};
	
    return;
};


// atualiza a variável global para id de diretório atual de trabalho.
void shellUpdateCurrentDirectoryID( int id )
{
	g_current_workingdirectory_id = (id);
};


//lista informações sobre os processos.
void shellTaskList()
{
	// opções:
	// +podemos pedir para o kernel listar as informações.
	// +podemos solicitar as informações uma a uma.
	// Obs: A segunda opção é a mais trabalhosa, mas 
	// da oportunidade para testarmos as chamadas ao kernel e 
	// explorarmos as possibilidades que cada informação traz 
	// individualmente.
	//
	
	
	// testando posicionamento de strings
	
	unsigned long X, Y;
	int PID;

	//Pega o PID do processo atual.
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	
    //X = apiGetCursorX();
	Y = apiGetCursorY();
	
	Y++;
	X=0;
	shellSetCursor(X,Y);	
    printf("PID ");
	X=8;
	shellSetCursor(X,Y);
	printf("XXXXXXXX");
	
	Y++;
	X=0;
	shellSetCursor(X,Y);
    printf("====");
	X=8;
	shellSetCursor(X,Y);
	printf("========");

	Y++;
	X=0;
	shellSetCursor(X,Y);	
    printf("%d",PID);
	X=8;
	shellSetCursor(X,Y);
	printf("...");
	
    //...	
	
	
    return;	
};


void shellShowPID()
{
	printf("Current PID %d\n", 
	    (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0) );
}


void shellShowPPID()
{
	printf("Current PID %d\n", 
	    (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0) );
}


void shellShowUID()
{
	printf("Current UID %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTUSERID, 0, 0, 0) );
}


void shellShowGID()
{
	printf("Current GID %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTGROUPID, 0, 0, 0) );
}


void shellShowUserSessionID()
{
	printf("Current user session %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTUSERSESSION, 0, 0, 0) );
}


void shellShowWindowStationID()
{
	printf("Current window station %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTWINDOWSTATION, 0, 0, 0) );
}


void shellShowDesktopID()
{
	printf("Current desktop %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTDESKTOP, 0, 0, 0) );
}

void shellShowProcessHeapPointer()
{
	int id = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0); 
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, id, 0, 0);
	
	printf("Current Process heap pointer address %x\n", (unsigned long) heap_pointer);
};


void shellShowKernelHeapPointer()
{
	int id = 0;  //Id do processo kernel. 
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, id, 0, 0);
	
	printf("Current Process heap pointer address %x\n", (unsigned long) heap_pointer);
};


//mostrar informações gerais sobre a memória.
void shellShowMemoryInfo()
{
	system_call( SYSTEMCALL_MEMORYINFO, 0, 0, 0);
};

//mostrar informações gerais sobre a memória.
void shellShowPCIInfo()
{
    system_call( SYSTEMCALL_SHOWPCIINFO, 0, 0, 0);	
};

//mostrar informações gerais sobre a memória.
void shellShowKernelInfo()
{
	system_call( SYSTEMCALL_SHOWKERNELINFO, 0, 0, 0);
};



//rotina interna de support.
//isso deve ir para bibliotecas depois.
//não tem protótipo ainda.
//void shell_fntos(const char *name)
void shell_fntos(char *name)
{
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];
	
    //transforma em maiúscula
	while(*name && *name != '.')
	{
        if(*name >= 'a' && *name <= 'z')
            *name -= 0x20;

        name++;
        ns++;
    }

    // aqui name[0] é o ponto.
	// então constroi a extensão.
	for(i=0; i < 3 && name[i+1]; i++)
	{
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    }

    while(ns < 8){
        *name++ = ' ';
        ns++;
    }

    for(i=0; i < 3; i++)
        *name++ = ext[i];

    *name = '\0';
};


/*
 *******************************************************
 * shell_gramado_core_init_execve:
 *     gramado core specials execve SUPPORT
 *
 */									 
void shell_gramado_core_init_execve( const char *filename, 
                                     const char *argv[], 
                                     const char *envp[] )
{	
	
	//Ok funcionou.
	shell_fntos( (char *) filename);
	
	//const char* isso não foi testado.
	//shell_fntos(filename);


	//isso deve chamar gramado_core_init_execve() na api.
	
	//
	// 
	//
	//
	system_call( 167, 
	            (unsigned long) filename,
				(unsigned long) argv,
				(unsigned long) envp );
	
    /* No return */
};

