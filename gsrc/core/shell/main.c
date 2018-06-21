/*
 * File: main.c 
 *
 * GWM - Gramado Window manager.
 * deve se comunicar com o GWS, Gramado Window Server. /gramado
 * General purpose application.
 *
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
 * History:
 *     2016 - Created by Fred Nora.
 *     2018 - More commands.
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


#include "compiler.h"

//lib C
//Isso deveria estar em um mesmo lugar para todos 
//os aplicativos.
//ex: c:\gramado\branch\libc
#include "types.h"
#include "stddef.h"   
#include "stdio.h"   
#include "stdlib.h"  
#include "string.h"

#include "shell.h"
#include "globals.h"
#include "builtins.h"
#include "api.h"


//salvando ordem
//#include "api.h"
//#include "types.h"
//#include "stddef.h"   
//#include "stdio.h"   
//#include "stdlib.h"  
//#include "string.h"
//#include "shell.h"
//#include "globals.h"
//#include "builtins.h"


//inicialização silenciosa. Suprime alguns verboses.
int quiet = 0;	

//O shell está rodadndo.
int running = 1;

//o shell está executando um comando que 
//está emprimeiro plando.
int executing = 0;

int login_status = 0;

//Sendo assim, o shell poderia abrir no ambiente de logon.

char username[11];
char password[11];
//char sUsername[11];
//char sPassword[11];
//char *username;
//char *password; 

	

#ifndef PPROMPT
#define PPROMPT "shell\\$ "
#endif
char *primary_prompt = PPROMPT;

#ifndef SPROMPT
#define SPROMPT "shell> "
#endif
char *secondary_prompt = SPROMPT;

//O ambiente que o shell passa para 
//o comando que ele executou.
char **shell_environment;

//#define DEFAULT_WINDOW_TITLE "Shell"


//Se o shell vai ser usado para login.
//Obs: Uma variável no kernel guardo o id do processo 
//que fez login.
int login_shell = 0;

//Se for diferente de zero então esse shell é interativo.
//Se for zero ele pode apenas estar executando um script.
int interactive = 0;


/* The name of this shell, as taken from argv[2]. */
char *shell_name;

/*nome do arquivo de configuração*/
char *shell_config_file = "./shellcnf.txt";


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
#define SHELLFLAG_FEEDTERMINAL 7
#define SHELLFLAG_EXIT 8
//... 

/*
//argument buffer
char **argbuf;
int argbuf_length;
int argbuf_index;
*/

//
// Protótipos
//

void die(char * str);
void *
xmalloc( int size);
void error( char *msg, char *arg1, char *arg2 );
char *
concat( char *s1, char *s2, char *s3 );

//
// Internas.
//

static inline void pause(void) 
{ 
    asm volatile("pause" ::: "memory"); 
} 

/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static inline void rep_nop(void)
{
	__asm__ __volatile__("rep;nop": : :"memory");
}

#define cpu_relax()		rep_nop()

//
// Protótipos para funções internas.
//


// Procedimento de janela principal do aplicativo.
unsigned long 
shellProcedure( struct window_d *window, 
                int msg, 
 			    unsigned long long1, 
				unsigned long long2 );
				
				
//diálogo para alimentar o terminal usado pelos aplicativos.				
int feedterminalDialog( struct window_d *window, 
                      int msg, 
				      unsigned long long1, 
				      unsigned long long2 );
							  

// Procedimento de janela da topbar.							  
unsigned long 
shellTopbarProcedure( struct window_d *window, 
                      int msg, 
			          unsigned long long1, 
					  unsigned long long2 );
					  
 
 
void
quit( int status )
{
	running = 0;
} 
 
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
 *  ## O SHELL É UM APLICATIVO DO TIPO JANELA, 
 *     DEVE TER UM MAIN DO TIPO JANELA ##
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
	
	//char **internal;
	char *filename;
	register int i;
	//
	// Obs: Esse não é um programa que roda em modo terminal,
	// ele na verdade cria um terminal dentro de uma janela filha.
	// isso pode servir para esse programa interpretar linguagem 
	// basic por exemplo.
	// os programas em modo terminal não criarão janelas e rodarão nas 
	// janelas de terminal cridas para eles pelo kernel.
	//
	
	//#debug
	//deixe o kernel usar essa janela para teste.
	//Obs: Não criaremos a janela principal desse programa 
	//para evitarmos erros com printf.
	
 
	
	
	/*
	 * Uma boa ordem para os passos dessa rotina nos aplicativos  
	 * é: Step1=WindowClass, Step2=Window e Step3=Message.
	 */
	
	//@todo: Criar esse tipo de classe.
	//       Provavelmente deve coincidir com a estrutura presente
    //nas rotinas de gerenciamento de janela que estão em kernel mode.	
	//struct window_class_d *wc; 
	
	
	// A janela principal do aplicativo.
	struct window_d *hWindow;        
	
	//struct message_d *m;

	
	int Status = 0;
	//char *s;    //String	

	
	//
	// ## ARGS ##
	//
	
	//Ok isso funcionou.
	//Argumentos passados com sucesso do crt0 para o main.
	
	//printf("argc={%d}\n",argc);
	
	//printf("arg[0]={%s}\n",argv[0]);
	//printf("arg[1]={%s}\n",argv[1]);
	//printf("arg[2]={%s}\n",argv[2]);
	
	//
	// Filtra a quantidade de argumentos.
	//
	
	//goto noArgs; 
	
	//Não usar verbose nessa fase de tratar os argumentos
	//pois a janela ainda não foi inicializada.
	
	// Se não há argumentos.
	if(argc < 1)
	{
		//printf("No args !\n");
		//#Test.
        //fprintf( stderr,"Starting Shell with no arguments...\n");	 	
		die("No args!");
		
		goto noArgs; 
	}else{
		
		//argv[0] = Tipo de shell: interativo ou não
		//argv[1] = Tipo de uso: login ... outros ?? 
		
		//printf("Testing args ...\n");
		
	    if( strncmp( (char *) argv[0], "-interactive", 12 ) == 0 )
	    {
			interactive = 1;
            
            //printf("Initializing an interactive shell ...\n");
            //printf("arg[0]={%s}\n",argv[0]);			
        };

        //Se o shell foi iniciado com um arquivo de script para ser 
        //executado.
		//a Flag -f indica que o que segue é um arquivo de script.
        //if( strncmp( (char *) argv[0], "-f", 2 ) == 0 )
        //{
		//	goto dosh2;
		//}			
		
	    if( strncmp( (char *) argv[1], "-login", 6 ) == 0 )
	    {
			login_shell = 1;
			
			//printf("Initializing login ...\n");
            //printf("arg[1]={%s}\n",argv[1]);    
        };	
		
		//Nome passado viar argumento.
		//shell_name = (char*) argv[2];

        //...		
	};
	
	//Nothing.
	
noArgs:		
	
	
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
	
	// Com base nas informações obtidas no sistema.
	// verde 0x83FCFF
	// preto COLOR_BLACK
						
    //para flat os dois poem ser a mesma cor.
    //não completamente preto.	
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1," {} SHELL.BIN ",
	                      shell_window_x, shell_window_y, 
						  shellWindowWidth, shellWindowHeight,    
                           0, 0, SHELL_TERMINAL_COLOR2, SHELL_TERMINAL_COLOR2 );	   

	if((void*) hWindow == NULL){	
		die("shell.bin: hWindow fail");
	}
	
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
	
    // Registrar.
	// Configurar como ativa.
    // Setar foco.
	// *IMPORTANTE: 
	// É FUNDAMENTAL SETAR O FOCO, POIS O KERNEL DEPENDE DELE
	// PARA RETORNAR A MENSAGEM DA JANELA COM O FOCO DE ENTRADA.
	// Nesse momento o kernel configura as margens para o cursor 
	// dentro da janela.
	// @todo: O kernel deve reiniciar as variáveis de cursor 
	// dentro da janela também, pois cada janela tem uma configuração 
	// diferente de cursor.
	//
	// ?? Show Window !!
	// Precisamos mostrar a janela e não repintar 
	// a tela toda.
	//
	
    APIRegisterWindow(hWindow);
    APISetActiveWindow(hWindow);	
    APISetFocus(hWindow);	
	refresh_screen();
	
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
	
	enterCriticalSection();    	
	Status = (int) shellInit(hWindow); 
	if(Status != 0){
		die("[SHELL.BIN]: app_main: shellInit fail!");
	};
	exitCriticalSection();     		
	

	
	//
	//#importante:
	//Agora é a hora de pegar mensagens de input de teclado.
	//Mas se o shell não for interativo, então não pegaremos 
	//mensagens de input de teclado.
	//
	
	if( interactive != 1 )
	{
		//#debug
        printf("shell is not interactive.\n");
		goto skip_input;
	};
	
	
	//
	// ## Messages ##
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
		
	unsigned long message_buffer[5];	
		
Mainloop:
    
	// #### Test ####
	
	/* ## Nesse teste vamos enviar um ponteiro de array e 
	  pegarmos os 4 elementos da mensagem ## */
	
	while(running)
	{
		enterCriticalSection(); 
		system_call( 111,
		    (unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0] );
		exitCriticalSection(); 
			
		if(	message_buffer[1] != 0 )
		{
	        shellProcedure( (struct window_d *) message_buffer[0], 
		        (int) message_buffer[1], 
		        (unsigned long) message_buffer[2], 
		        (unsigned long) message_buffer[3] );
			
			//clear
			message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;	
        };				
	};
	
	
	
	switch(ShellFlag)
	{
	    // Sai do shell.
		case SHELLFLAG_EXIT:
		    goto end;
			break;

		//@todo:
        //opções ...
		
		// Sai do shell.	
        default:
            goto end;
			break;		
	};

	
	//
	// Pulamos a parte que pega mensgens de input de teclado 
	// porque esse shell não está configurado como interativo.
	//
	
//	
// # RunScript #	
//

skip_input:	

    shellExecuteThisScript(argv[3]);

	
	//
	// Exit process.
	//
	
end:

#ifdef SHELL_VERBOSE		
    printf("SHELL.BIN: exiting main() ...\n");
#endif 
	
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
	
	int q;
	
	
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
				    pause();
					pause();
					pause();
					pause();
					cpu_relax();
				    return (unsigned long) 0;
				    break;
				
				// Enter.
				// Finaliza a string e compara.
				case VK_RETURN:
				    input('\0'); 
					//input('\0');
					//input(0);
					//input(0);
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
		    switch(long1)
			{
		        
				//help
				case VK_F1:
				    //MessageBox( 1, "Gramado Core - Shell","F1: HELP");
					
				    //MessageBox( 1, "Gramado Core - Shell","F11: FULL SCREEN");
					
				    //APISetFocus(i1Window);
					//APIredraw_window(i1Window);
					//MessageBox( 1, "feedterminalDialog","F1: HELP");
				    //APISetFocus(i2Window);
					//APIredraw_window(i2Window);				
				    //MessageBox( 1, "MessageBox","F1: Testing apiDialog() ");
					
					printf("Chamando apiDialog: ...\n");
					q = (int) apiDialog("Pressione 'y' para Yes ou 'n' para No.\n");
					
					if( q == 1 ){ printf("Voce escolheu Yes \n");};
					if( q == 0 ){ printf("Voce escolheu No \n");};
					
					printf("apiDialog retornou.\n");
					
					//ShellFlag = SHELLFLAG_COMMANDLINE;						
					
					//testando formato amigável de string - ok
					//shell_gramado_core_init_execve( "testtest.bin", 0, 0 );
					break;
					
				//...
				
                //full screen
                //colocar em full screen somente a área de cliente. 				
		        case VK_F11:
				
					break;
					
				//...

			};
			break;
		
		//Obs:
		//essas teclas são tratadas pelo procedimento do sistema.
		//mas alguma tecla personalizada pode ser  tratada pelo aplicativo,
		//como o context menu [Application Key]
		case MSG_SYSKEYUP:
            switch(long1)
			{
				
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
			
		// MSG_MOUSEKEYDOWN	
		//#bugbug: a janela foi pintada duas vezes, não sabemos,
		//se dias mensagens foi enviada para o procedimento ou se 
		//a rotina de redraw foi chamada duas vezes ou ainda 
		//se apenas o refresh_rectangle foi chamado duas vezes.
		//obs: pode ser que dois botões estejam selecionados como clicados.
		//e o sistema enviou duas mensagens. Uma opção seria checarmos 
		// qual botão foi clicado, isso aparece em long1.
		case 30:
		    //printf("Down");
			if( long1 == 1 )
			{
                printf("button 1\n"); 				
                APISetFocus(window);
			    APIredraw_window(window,1);
			    //refresh_screen();
			}
			if( long1 == 2 )
			{
				printf("button 2\n");
			}
			if( long1 == 3 )
			{
				printf("button 3\n");
			}			
            break;

		// MSG_MOUSEKEYUP	
		case 31:
			if( long1 == 1 )
			{
                printf("up button 1\n"); 				
			}
			if( long1 == 2 )
			{
				printf("up button 2\n");
			}
			if( long1 == 3 )
			{
				printf("up button 3\n");
			}	
            break;	

		// MSG_MOUSEMOVE	
		case 32:
            //APISetFocus(window);
			//printf("m");
            break;	

		// MSG_MOUSEOVER	
		case 33:
            //APISetFocus(window);
			//printf("o");
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
        //essa mensagem é enviada para o aplicativo quando 
        //a função 'update window'	é chamada.	
        case MSG_PAINT:
            printf("SHELL.BIN: MSG_PAINT\n");
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
 ******************************
 * shellWaitCmd:
 *     Espera completar o comando 
 * com um [ENTER]. ##suspensa
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
 * + Frederico Martins Nora (frednora)
 */
 
#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80
 
unsigned long shellCompare(struct window_d *window)
{
    //char **stringarray1;
	char *tokenList[TOKENLIST_MAX_DEFAULT];
	char *token;
	int token_count;	
	int i = 0;

    unsigned long ret_value;
	int q;    //diálogo
	char *c;
	
    //?? é um pathname absoluto ou não. ??
	//Ok. isso funcionou.
    int absolute; 
	
  // Temos uma linha de comando em prompt[]
  // que é o stdin.  
NewCmdLine:	

    //#debug
	//printf("prompt:{%s}\n",prompt);
	
	c = prompt;
	
	//Se alguem pressiona [ENTER] com prompt vazio
	//dá page fault.
	//Isso cancela caso o buffer esteja vazio.
	
	//>(NULL)
	//[ENTER] finalizou a atring antes de ter digitado alguma coisa.
	if( *c == '\0' ){
	    goto exit_cmp;	
	}
	
	//>' '
	//Só faz o tratamento com while se for igual a ' '.
    if( *c == ' ' || *c == '\t' )
	{
        int j;		
        //#importante:
		//Aqui estamos tratando uma linha de comando inteira.
		
	    //enquanto c[] for diverente de ' ' c avança.
	    //isso elimina os espaços para c[]
	    j=0;
		while( *c == ' ' || *c == '\t' )
		{ 
	        
			//Limits
		    j++;
			if( j > 80 )
			{
			   //#debug
               //Isso significa que uma string 
			   //construida em prompt[] não foi 
			   //corretamente finalizada.
			   //ou algum problema no while anterior.
			   printf("#debug \n");				
			   printf(" ** while1 fail  **\n");	
			   while(1){}
			}
			
			//desrepeitamos o limite imposto pelo fim da string.
			//por isso temos que fazer a marcação exata do início 
			//da linha de comando e do fim da linha de comando.
			// |            |.......|        |
			// start       left   right     end
			
			c++; 
		}
		
		//se depois de eliminarmos os espaços encontrarmos
		//um '\0' de fim de string.
		//significa que o usuário digitou um monte de espaços
		//depois apertou enter.
		//não há mais o que fazer.
	    if( *c == '\0' ){
	        goto exit_cmp;	
	    }		
	    
		int line_rest = (80-j);
		
		//copia todo o resto da linha para o inpicio da linha.
        for( j=0; j<line_rest; j++ )
		{
			prompt[j] = c[j];
			
			//se enquanto estamos copiando,
			//ja copiamos o finalizador de string,
			//não precisamos copiar mais nada.
			if( *c == '\0' )
            {
				goto commandlineok;
			}				
		}
        
		//#bugbug
        //se estamos aqui é porque copiamos quase 80 chars.		
    };

commandlineok:	
    //#debug
	//printf("prompt:{%s}\n",prompt);	
	
    //>/
    //>.
    //>./
    //>..
    //>../
 

    absolute = absolute_pathname( (char*) prompt );
    if(absolute == 1)
	{
		// Aqui estamso invocando alguma coisa em um 
        // determinado diretório, pode ser o deretório raiz 
        // o próprio diretório, algo no próprio diretório,
        // o diretório pai ou algo no diretório pai. 		
		//printf("absolute pathname\n");
		goto check_directory;
	}else{
		
		// Aqui pode ser que começamos com o 
		// nome de um programa. Ex: >gcc
		// Obs: Se isso é um comando então 
		// podemos checar mais à frente novamente 
		// se o pathname é absoluto ou não.
		//printf("not absolute pathname\n");
	    goto this_directory;
	}
	

//precisamos checar em que diretório 
//o programa está.
//o comando tem um pathname absoluto ...
//Precisamos invocar esse programa 
//que está em um diretório apontado no pathname.
//ex: ../cmd 	
check_directory:
	
	
//O primeiro elemento da linha de comandos 
// é um comando simples	
// cd ..
this_directory:	
	
	//if( *prompt == (char) '\0' ){
	//    goto exit_cmp;	
	//}
	
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
   

	
	
	// ?? what ?
    // first call returns pointer
	// to first part of user_input
	// separated by delim
	
    //isso pega a primeira palavra digitada
	tokenList[0] = strtok( prompt, LSH_TOK_DELIM);
	
	
	//para o argumento atual
	//@todo: isso precisa ser limpado sempre.
	

	
	//salva a primeira palavra digitada.
	token = (char *) tokenList[0];
	
	i=0;                                  
    while( token != NULL )
	{
        // Coloca na lista.
        //salva a primeira palavra digitada.
		tokenList[i] = token;

		//#debug
		//Mostra
        //printf("shellCompare: %s \n", tokenList[i] );
        //refresh_screen();
		
		token = strtok( NULL, LSH_TOK_DELIM );
		
		// Incrementa o índice da lista
        i++;
		
		//salvando a contagem.
		token_count = i;
    }; 

	//Finalizando a lista.
    tokenList[i] = NULL;
	
	
	//
	//#importante:
	//nesse momento todos os argumentos estão certinhos no vetor.
	//já conferimos.
	//

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
	// ## identificadores de iniciação de linha ##
	//
	
	//Esses identificadores determinam o que 
	//se vai encontrar na linha. E não existe volta, 
	//o que o identificador determinou será obedecido.
	
	//
	// ## Lista de identificadores ligado a execussão ##
	//
	// (do)
	//
	// dobin - Execute programa .bin
	// dotry - Tenta executar qualquer extensão
	// Obs: Esses comandos efetuam goto 
	// dentro desse código, saltando diretamente 
	// para as rotinas executadoras de programas ou scripts.
	// Obs: O nome do progama está em tokenList[1] e os 
    // argumentos nos próximos tokenList.	
	//
	//

    if( strncmp( (char*) tokenList[0], "dobin", 5 ) == 0 )
    {
	    goto dobin;	
	}

    if( strncmp( (char*) tokenList[0], "dotry", 5 ) == 0 )		
    {
		goto dotry;
	} 
	
	//um comando no shell pede para executar um script
    if( strncmp( (char*) tokenList[0], "dosh", 4 ) == 0 )		
    {
		goto dosh;
	} 	


    //...

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
	//if( strncmp( prompt, "/objects", 6 ) == 0 )
	//{
	//    printf("info: Open object manager root dir ...\n");
    //    goto exit_cmp;
    //};

	// L2 disk  /diretório raiz do sistema de arquivos.
	//if( strncmp( prompt, "/", 5 ) == 0 )
	//{
	//    printf("info: Open file system root dir ...\n");
    //    goto exit_cmp;
    //};

	// L3 LAN  // acesso a arquivos da lan
	//os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	//if( strncmp( prompt, "/lan", 6 ) == 0 )
	//{
	//    printf("info: Open lan root dir ...\n");
    //    goto exit_cmp;
    //};
 
	// L4 WAN   //acesso a arquivos da wan
	// os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	//if( strncmp( prompt, "/wan", 6 ) == 0 )
	//{
	//    printf("info: Open wan root dir ...\n");
    //    goto exit_cmp;
    //};
	
	
	//comentário
	// a linha é um comentário, podemos ignorar.
    //if( strncmp( prompt, "//", 2 ) == 0 ){
	//	goto exit_cmp;
	//};		
	
    //
	// Ordem alfabética.
	//
	

	//token
	//testando tokenList
	//comando usado para testes de comando.
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
    //if( strncmp( prompt, "ascii", 5 ) == 0 )
    //{
		//shellASCII();
	//	goto exit_cmp;
	//}


	//bmp exemplo.bmp
    if( strncmp( prompt, "bmp", 3 ) == 0 )
	{
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("Error: No name!\n");
		}else{
			
			//@todo: podemos checar se o pathname é absoluto,
			//e onde se encontra o arquivo que queremos.
			shellDisplayBMP( (char*) tokenList[i] );
		};
		goto exit_cmp;
    };	
	
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


	// cd - Change dir.
	if( strncmp( prompt, "cd", 2 ) == 0 )
	{
		
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("cd error: no arg\n");
		}else{
			
			//#bugbug: não é possivel fazer isso por enquanto,
			//pois não estamos fazendo parse de char por char.
			//if( strncmp( (char*) tokenList[i], ".", 2 ) == 0 )
			//{}
				
			if( strncmp( (char*) tokenList[i], "..", 2 ) == 0 )
			{
				//Apaga o nome do último diretório.
			    shell_pathname_backup( current_workingdiretory_string, 1); 
                goto exit_cmp;				
		    }			
			
	        // updating the current working directory string.
	        shellUpdateWorkingDiretoryString( (char*) tokenList[i] );
			
			//@todo: podemos checar se o pathname é absoluto,
			//e onde se encontra o arquivo que queremos.
			//shellDisplayBMP( (char*) tokenList[i] );
		};		
		
		
		// o que segue o comando cd é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
		//cd_buitins();
	    goto exit_cmp;
	}		

    // cls - Clear the screen.
	if( strncmp( prompt, "cls", 3 ) == 0 ){
        cls_builtins();
        goto exit_cmp;
	};
	
	
	// color
	// color-scheme
	// Seleciona um dos 2 modos de cores padrão do sistema.
    if( strncmp( prompt, "color", 5 ) == 0 || 
	    strncmp( prompt, "color-scheme", 12 ) == 0 )
	{

		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("No args\n");
			goto exit_cmp;
		}else{
            
			//humility
			if( strncmp( (char*) tokenList[i], "-humility", 9 ) == 0 )
			{ 
		        printf("Selecting Humility color scheme\n"); 
                system_call(119, (unsigned long)1, (unsigned long)1, (unsigned long)1);
				printf("done\n");
                goto exit_cmp;				
			}
			
			//pride
			if( strncmp( (char*) tokenList[i], "-pride", 6 ) == 0 )
			{
				printf("Selecting Pride color scheme\n");
                system_call(119, (unsigned long)2, (unsigned long)2, (unsigned long)2);
                printf("done\n");
				goto exit_cmp;				
			}
			
			// Talvez haverão mais esquemas ...
			//...
		};
		goto exit_cmp;
    };		
	
	// copy
	if( strncmp( prompt, "copy", 4 ) == 0 )
	{
		// o que segue o comando copy são dois pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		copy_builtins();
	    goto exit_cmp;
	}
		
	// date
	if( strncmp( prompt, "date", 4 ) == 0 ){
		date_builtins();
        goto exit_cmp;
    };	

	// del
	if( strncmp( prompt, "del", 3 ) == 0 )
	{
		// o que segue o comando del é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		del_builtins();
	    goto exit_cmp;
	}		
	
	
	// dir - Lista os arquivos no estilo DOS.
	if( strncmp( prompt, "dir", 3 ) == 0 )
	{
		// o que segue o comando dir é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
        //se o pathname for null então o comando atua sobre o pwd		
		dir_builtins();
        goto exit_cmp;
    };
	
    // disk-info
	if( strncmp( prompt, "disk-info", 9 ) == 0 )
	{
	    shellShowDiskInfo();
        goto exit_cmp;
    };	
	
	
	// echo - Echo de terminal.
    if( strncmp( prompt, "echo", 4 ) == 0 )
	{
		echo_builtins(tokenList);
		goto exit_cmp;
    };

	
	// editbox
	// Cria uma edibox.
    // #teste: deletar.
	if( strncmp( prompt, "editbox", 7 ) == 0 )
	{
	    enterCriticalSection();    
	    shellCreateEditBox();
	    exitCriticalSection();    
		
		goto exit_cmp;
    };		
	
	// exec - Executa um programa fechando o shell.
    if( strncmp( prompt, "exec", 4 ) == 0 )
	{
		// o que segue o comando exec é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		exec_builtins();
		ShellFlag = SHELLFLAG_EXIT;
		goto exit_cmp;
    };	
	
	// exit - Exit the application.
    if( strncmp( prompt, "exit", 4 ) == 0 )
	{
		exit_builtins();
		ShellFlag = SHELLFLAG_EXIT;
		goto exit_cmp;
    };
	
    // fork - testando a função fork.
	if( strncmp( prompt, "fork", 4 ) == 0 )
	{
		int pidFORK = (int) fork();
        printf("PID={%d}\n",pidFORK);
        goto exit_cmp;
	};	
	
	
    // getpid
	if( strncmp( prompt, "getpid", 6 ) == 0 ){
	    getpid_builtins();
        goto exit_cmp;
    };
	
    // getppid
	if( strncmp( prompt, "getppid", 7 ) == 0 ){
	    getppid_builtins();
        goto exit_cmp;
    };
	
	
    // getuid - get user id
	if( strncmp( prompt, "getuid", 6 ) == 0 ){
	    getuid_builtins();
        goto exit_cmp;
    };
	
	
    // getgid - get group id
	if( strncmp( prompt, "getgid", 6 ) == 0 ){
	    getgid_builtins();
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
			help_builtins(1);
		}else{
            
			if( strncmp( (char*) tokenList[i], "-all", 4 ) == 0 )
			{ 
                help_builtins(1); 		
			}
			
			if( strncmp( (char*) tokenList[i], "-min", 4 ) == 0 )
			{
                help_builtins(2);				
			}
			
			//...
		};
		goto exit_cmp;
    };	
		
	
	// install	
    // ?? 
	if( strncmp( prompt, "install", 7 ) == 0 )
	{
		// o que segue o comando install é um pathname.
		//com o nome do aplicativo instalador
		//no fim do pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
        //o comando install colocará nos argumentos 
        //o indicativo que de que desejamos que 
        //o aplicativo executado seja um instalador.
        //por exemplo: -install-bin  -install-package -install-lib etc...
        //install.bin é um aplicativo. 
        //>install app.bin -install-bin		
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
	//isso será um programa.
	//if( strncmp( prompt, "ls", 2 ) == 0 )
	//{
		//@todo: Isso deve ser um aplicativo.
	//	printf("~ls\n");
    //    goto exit_cmp;
	//};


    // message-box
	//Testing message box.
	if( strncmp( prompt, "message-box", 11 ) == 0 )
	{
		//@todo:testar os 4 tipos 
	    MessageBox( 1, "Shell message box","Testing message box...");
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
		// o que segue o comando mov são dois pathnames.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
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
	if( strncmp( prompt, "pwd", 3 ) == 0 ){
		pwd_builtins();
	    goto exit_cmp;
	};		

	
    // reboot
    // @todo: Isso será um aplicativo. reboot.bin	
    if( strncmp( prompt, "reboot", 6 ) == 0 )
	{
	    //printf("~reboot\n");
		printf("Tem certeza que deseja reiniciar o sistema?\n");
		q = (int) apiDialog("Pressione 'y' para Yes ou 'n' para No.\n");
					
		if( q == 1 ){ 
		    printf("Rebooting...\n");
		    system("reboot"); 
		};
		//if( q == 0 ){ printf("Voce escolheu No \n");};
					
		//printf("apiDialog retornou.\n");		
		//system("reboot");
		goto exit_cmp;
    };
	
	// rename - reneme directory or file.
	if( strncmp( prompt, "rename", 6 ) == 0 )
	{
		// o que segue o comando rename são dois pathnames.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
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
		// o que segue o comando save é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
	    printf("~save root\n");
        goto exit_cmp;
    };
	
	
	// service
	//podemos tertar serviços do kernel 
	//enviando argumentos nulos.
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
	if( strncmp( prompt, "shell-info", 10 ) == 0 )
	{
		
	    printf("~@todo: shell info.\n");
		shellShowInfo();
        goto exit_cmp;
    };	
	
	
    // shutdown - isso será um programa. shutdown.bin
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
	//??#bugbug: O que isso deveria fazer ?? 
	//??reiniciar o shell ou iniciar um programa ??
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
	if( strncmp( prompt, "system-info", 11 ) == 0 )
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
		//screen_buffer[0] = (char) 'F';
		//screen_buffer[1] = 7;
		
        //screen_buffer[2] = (char) 'N';	
        //screen_buffer[3] = 7;
		
		//screen_buffer[4] = (char) '\0';			
		//screen_buffer[5] = 7;
		
		//printf( (const char *) stdout->_base );
		
		//printf("%s \n",stdout->_base);
		//printf("%s \n",stdout->_tmpfname);
		//printf("%d \n",stdout->_cnt);
		//printf("%d \n",stdout->_bufsiz);
		//printf("done \n");
		
        goto exit_cmp;
    };
	
	
	// t2 - Test bmp
	if( strncmp( prompt, "t2", 2 ) == 0 )
	{
		shellTestDisplayBMP();
        goto exit_cmp;
    };	
	
	
	// t3 - Test thread
	if( strncmp( prompt, "t3", 2 ) == 0 ||
        strncmp( prompt, "test-thread", 11 ) == 0	)
	{
	    shellTestThreads();
        goto exit_cmp;
    };
	
	FILE *f1;
	int ch_test;
	
	// t4 - testando fopen
	if( strncmp( prompt, "t4", 2 ) == 0 )
	{
		printf("\n t4: Open init.txt \n");
        
		f1 = fopen("init.txt","rb");  
        if( f1 == NULL )
		{
			printf("fopen fail\n");
		}else{
			printf("fopen ok\n");
		}
		
		//Isso mostra que o arquivo foi carregado corretamente 
		//na base esperada.
		//printf("Show f1->_base: %s\n",f1->_base);
		
		//printf("stream info:\n");
		//printf("f1->_base: %x\n",f1->_base);
		//printf("f1->_ptr: %x\n",f1->_ptr);
		//printf("f1->_cnt: %d\n",f1->_cnt);
		
		//
		// #bugbug ... o fgetc não lê na estrutura esperada.
		//
		printf("Testing fgetc ... \n\n");
		while(1)
		{
			//ch_test = (int) fgetc(f1);
			ch_test = (int) getc(f1); 
			if( ch_test == EOF )
			{
				printf("\n\n");
				printf("EOF reached :)\n\n");
				//printf("Show f1->_base: %s\n",f1->_base);
				goto exit_cmp;
			}else{
			    printf("%c", ch_test);	
			};
		};
		
		//fail.
		goto exit_cmp;
    };

	// t5 - ( save file )
	//Ok isso funcionou.
	if( strncmp( prompt, "t5", 2 ) == 0 )
	{
		printf("t5: tentando salvar um arquivo ...\n");
		char file_1[] = "t5: Arquivo \n escrito \n em \n user mode. \n";
		char file_1_name[] = "FILE1UM TXT";
		
		enterCriticalSection();
		system_call( 4,
		             (unsigned long) file_1_name, //nome
                     (unsigned long) file_1,      //endereço
                     (unsigned long) 0x20 );      //flag
		exitCriticalSection();
		printf("t5: done.\n");
		
		//...
        goto exit_cmp;
    };	


	// t6 - testando a api. rotina que salva arquivo. 
	//ok, isso funcionou.
	if( strncmp( prompt, "t6", 2 ) == 0 )	
	{
		printf("t6: tentando salvar um arquivo ...\n");
		char file_2[] = "t6: Arquivo \n escrito \n em \n user mode. \n";
		char file_2_name[] = "FILE2UM TXT";
		
        apiSaveFile( file_2_name,  //name 
                     0,            //number of sectors.
                     0,            //size in bytes			
                     file_2,       //address
                     0x20 );       //flag
        goto exit_cmp;					 
	};
	
	// tasklist - Lista informações sobre os processos.
	//isso será um programa tasklist.bin
	if( strncmp( prompt, "tasklist", 8 ) == 0 )
	{
		shellTaskList();
        goto exit_cmp;
    };	
	
	
    //test-taskman-server - testando servidor taskman
	if( strncmp( prompt, "test-taskman-server", 19 ) == 0 )
	{
        system_call( 116,0,0,0);
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
	    
		//Apenas inicialize. Continuaremos com o procedimento 
		//do shell e não o da barra,
		shellCreateTopBar(1);
	    
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
	//?? isso pode ser um programa
    if( strncmp( prompt, "version", 7 ) == 0 )
	{
	    printf("\n Gramado version %s \n", OS_VERSION );
        goto exit_cmp;
    };
	
    // volume-info
	if( strncmp( prompt, "volume-info", 11 ) == 0 )
	{
	    shellShowVolumeInfo();
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
	
	//fail.
	int Execve_Ret = 1;
	
    //unsigned long a1 = (unsigned long) tokenList[0];
	
	//char *a1 = tokenList[1];
	//char *a1 = tokenList[2];
	
	
doexec_first_command:

    //
	// ## TEST ##
	//

    //
	// #importante:
	// Se estamos aqui é porque o comando não corresponde a
	// nenhuma das palavras reservadas acima, então executaremos
	// presumindo ser um nome de aplicativo no formato 'test.bin'
	// >>> Mas esse comando pode ser o último elemento  
	//     de um pathname, então vamos checar se o pathname é 
	//     absoluto. Isso é a primeira coisa que podemos fazer.
	//
	
    absolute = absolute_pathname( (char*) tokenList[0] );
    if(absolute == 1)
	{
		// Aqui estamso invocando alguma coisa em um 
        // determinado diretório, pode ser o deretório raiz 
        // o próprio diretório, algo no próprio diretório,
        // o diretório pai ou algo no diretório pai. 		
		printf("doexec_first_command: absolute pathname\n");
		
		// eliminando ./ do pathname
		char *t = (char*) tokenList[0];
		
		if( *t == '.' )
		{
			t++;
		    if( *t == '/' )
			{
				t++;
				tokenList[0] = (char*) t;
			}
	    }	
	
	}else{
		
		// Aqui pode ser que começamos com o 
		// nome de um programa. Ex: >gcc
		// Obs: Se isso é um comando então 
		// podemos checar mais à frente novamente 
		// se o pathname é absoluto ou não.
		printf("doexec_first_command: not absolute pathname\n");
	}
	
	
	//
	// ## Executando um programa no formato ">test.bin"
	//
	
	
	
    //Presumindo ser um nome de aplicativo no formato 'test.bin'.
    //o token 0 é o nome do programa e o os próximos são argumenteos ..
	//dessa forma podemos enviar um comando e dois argumentos ...
	//?? Talvez devessemos enviar um ponteiro para um array de strings 
	// no último argumento. (argv) ou ainda um env
						 

    Execve_Ret = (int) shell_gramado_core_init_execve( 
	                       (const char*) tokenList[0], 
	                       (const char*) tokenList[1], 
						   (const char*) tokenList[2] );
						 
	// Ok, funcionou e o arquivo foi carregado,
	// mas demora para receber tempo de processamento.
	if( Execve_Ret == 0 )
	{
		//
		// ## WAIT ??
		//
		
		// Aqui temos uma decisão a tomar.
		// Se o aplicativo executou corretamente e esta em primeiro 
		// plano então devemos entrar em wait.
		// Se o aplicativo funcionou corretamente mas está em segundo 
		// plano então decemos continuar. 
		// Por enquanto estamos continuando e rodando concomitantemente.
		//
		
		//
		// # Stop running #
		//
		
		//Isso sai do loop de mensagens e 
		//sai do shell elegantemente.
		running = 0;
		
	    goto exit_cmp;	
	}else{
		// falhou. Significa que o serviço naõ conseguir encontrar 
		// o arquivo ou falhou o carregamento.
		printf("shell: execve fail\n");
		goto fail;
	};
	
	
	//
	// # dobin #
	//
	
	//vamos executar um programa .bin.
	//.bin é a extensão padrão.
	//executaremos o segundo comando, pois o primeiro é ~$dobin.
	//
dobin:

    if( is_bin( (char *) tokenList[1] ) != 1 )
	{
		printf("dobin: it's not a .bin filename.\n");
		printf("dobin: fail\n");
	};

    Execve_Ret = (int) shell_gramado_core_init_execve( 
	                       (const char*) tokenList[1], 
	                       (const char*) tokenList[2], 
						   (const char*) tokenList[3] );
						 
	// Ok, funcionou e o arquivo foi carregado,
	// mas demora para receber tempo de processamento.
	if( Execve_Ret == 0 )
	{
		//
		// ## WAIT ??
		//
		
		// Aqui temos uma decisão a tomar.
		// Se o aplicativo executou corretamente e esta em primeiro 
		// plano então devemos entrar em wait.
		// Se o aplicativo funcionou corretamente mas está em segundo 
		// plano então decemos continuar. 
		// Por enquanto estamos continuando e rodando concomitantemente.
		//
		
		//
		// # Stop running #
		//
		
		//Isso sai do loop de mensagens e 
		//sai do shell elegantemente.
		running = 0;
		
	    goto exit_cmp;	
	}else{
		// falhou. Significa que o serviço naõ conseguir encontrar 
		// o arquivo ou falhou o carregamento.
		printf("shell: execve fail\n");
		goto fail;
	};	
	
	
	
//tente executar um aplicativo com outra extensão.
//checaremos se é uma extensão das suportadas.	
dotry:
    	

    Execve_Ret = (int) shell_gramado_core_init_execve( 
	                       (const char*) tokenList[1], 
	                       (const char*) tokenList[2], 
						   (const char*) tokenList[3] );
						 
	// Ok, funcionou e o arquivo foi carregado,
	// mas demora para receber tempo de processamento.
	if( Execve_Ret == 0 )
	{
		//
		// ## WAIT ??
		//
		
		// Aqui temos uma decisão a tomar.
		// Se o aplicativo executou corretamente e esta em primeiro 
		// plano então devemos entrar em wait.
		// Se o aplicativo funcionou corretamente mas está em segundo 
		// plano então decemos continuar. 
		// Por enquanto estamos continuando e rodando concomitantemente.
		//
		
		//
		// # Stop running #
		//
		
		//Isso sai do loop de mensagens e 
		//sai do shell elegantemente.
		running = 0;		
		
	    goto exit_cmp;	
	}else{
		// falhou. Significa que o serviço naõ conseguir encontrar 
		// o arquivo ou falhou o carregamento.
		printf("shell: execve fail\n");
		goto fail;
	};		
	
	
	//
	// # Script #
	//
	
	//um comando no shell invoca a execussão de um script 
	//dado o nome via tokenList.
dosh:

    //
	// Vamos tentar colocar o arquivo de script no stdin 
	// que é onde fica o prompt. Então retornaremos no 
	// início dessa rotina mas agora com uma nova linha de comando.
	//
    //nothing for now.
	//o comando [0] é o 'dosh' o [1] é o nome do script.

    if( is_sh1( (char *) tokenList[1] ) != 1 )
	{
		printf("dosh: it's not a .sh1 filename.\n");
		printf("dosh: fail\n");
	};

    shellExecuteThisScript( tokenList[1] );	
	goto NewCmdLine;
	
	
//
//  ## Fail ##
//	
	
	
fail:	
    printf(" Unknown command!\n");
    ret_value=1;
	goto done;
	
//
// ## EXIT CMP ##
//	

exit_cmp:
    ret_value=0;	
done:
	// Limpando a lista de argumentos.
	// Um array de ponteiros.
	
	for( i=0; i<TOKENLIST_MAX_DEFAULT; i++ ){
		tokenList[i] = NULL;
	};
	shellPrompt();
	//Mostrando as strings da rotina de comparação.	
	refresh_screen();
    return (unsigned long) ret_value;
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
	
	
    shellStatus = 0;
    shellError = 0;
	
	//
	// Deve ser pequena, clara e centralizada.
	// Para ficar mais rápido.
	//
	
	//
	// #importante:
	// O aplicativo tem que confiar nas informações 
	// retornadas pelo sistema.
	//
	
	//
	// Usar o get system metrics para pegar o 
	// tamanho da tela.
	//
	
	//
	// ## Screen size ##
	//
	
	// Tamanho da tela.	
	shellScreenWidth = apiGetSystemMetrics(1);
    shellScreenHeight = apiGetSystemMetrics(2); 	

	//
	// ## Window size ##
	//
	
	//Tamanho da janela do shell	
	shellWindowWidth = ((shellScreenWidth/3) * 2);
	shellWindowHeight = ((shellScreenHeight/3) * 2); 
	
	
	//
	// ## cursor limits ##
	//	
	
	
	//window position
	//Isso está muito legal. Não mudar.
	shell_window_x = (unsigned long) ( (shellScreenWidth - shellWindowWidth)/2 );
	shell_window_y = (unsigned long) ( (shellScreenHeight - shellWindowHeight)/2 );   
	
	//limits.
    shellMaxColumns = (shellWindowWidth/8);   //DEFAULT_MAX_COLUMNS; 
    shellMaxRows = (shellWindowHeight/8);     //DEFAULT_MAX_ROWS;     
 
    //...	

	//
	// Setup buffers.
	//
	
	//
	// #inportante:
	// #bugbug: Não podemos deixar o stdout como screenbuffer 
	// pois no screen buffer os caracteres tem atributos ...
	// e no stdout podemos ter um arquivo normal ...
	//ou saída normal que servirá de entrada para  
	//outro processo.
    // reiniciando as variáveis na estrutura do output
	//
	
	//obs: Ao cancelarmos isso o std volta a ser 
	//o antigo e já configurado stdout.
	//stdout->_base = &screen_buffer[0];
	//stdout->_ptr = stdout->_base;
	//stdout->_cnt = PROMPT_MAX_DEFAULT;
	//stdout->_file = 1;
	//stdout->_tmpfname = "shell_stdout";
	
	//...	
	//
	// Obs:
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
	//int CurrentVolumeID = 0;
		
	char buffer[512];
	
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
		
		
#ifdef SHELL_VERBOSE		
		printf("shellInit: Starting shell.bin ... \n");
		printf("shellInit: Running tests ...\n");
#endif
		
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
	
#ifdef SHELL_VERBOSE			
	printf("ActiveWindowId={%d}\n", ActiveWindowId );
#endif
	
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
	
#ifdef SHELL_VERBOSE			
	printf("WindowWithFocusId={%d}\n", WindowWithFocusId );	
#endif
	
	//
	// Obetendo informações sobre linhas e colunas do shell.
	//
	
	
#ifdef SHELL_VERBOSE		
	//columns and rows
	printf("shellMaxColumns={%d} \n", shellMaxColumns );
	printf("shellMaxRows={%d} \n", shellMaxRows );	
#endif
	
	
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
  
    //Mensagem ...
	printf("Starting SHELL.BIN ... PID={%d} PPID={%d} \n", PID, PPID );
	
	
	//
	// @todo: Criar processos processos:
	//     E.BIN, F.BIN, G.BIN, A.BIN, B.BIN, C.BIN, D.BIN
 	//     (Mermaids) Usados para testes.
	//

#ifdef SHELL_VERBOSE			
	printf("Creating processes ...\n");
#endif	
	
	
	
#ifdef SHELL_VERBOSE			
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
#endif	
	
	
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
#ifdef SHELL_VERBOSE			
	printf("Testing stdlib:\n");
#endif
	
	//
	// *Importante:
	//     Isso inicializa o gerenciamento de memória oferecido pela 
	// biblioteca C99 em user mode. Coisas como inicializar o 'heap'
	// oferecido pela biblioteca.
	// Agora poderemos alocar memória dentro do heap oferecido pela biblioteca.
	//
	
//initRT:	
	//libcInitRT(); 
	
	
#ifdef SHELL_VERBOSE			
	//Obs: Sempre inicia com o mesmo número.
	int rand_value;
	rand_value = (int) rand();
	printf("RandValue1={%d}\n", rand_value);
	//rand_value = (int) rand();
	//printf("RandValue2={%d}\n", rand_value);
    //rand_value = (int) rand();
	//printf("RandValue3={%d}\n", rand_value);
	//...
#endif	

	//stddef.h
	//printf("Testing stddef:\n");	
	
	//Testing COLUMNS
	
	//Testing ROWS
	
	
	//testando api.h
	//...
	
	
	//Funcionou...
	//sprintf( buffer,"Testando String dentro do buffer\n");
	//printf("%s",buffer);
	

	//
	// Get process info.
	//
	
	
	//
	// Get thread info.
	//
	

	
	//
	// Testing commands.
	//
#ifdef SHELL_VERBOSE		
	//Lib C.
	//libC. (stdlib.c)
	system("test");       
	system("ls");
	system("start");
	system("xxfailxx");
	//...
#endif
	
	
#ifdef SHELL_VERBOSE			
	//API.
	apiSystem("test");    
    apiSystem("ls");
	apiSystem("start");
	apiSystem("xxfailxx");
	//...
#endif
	
	//Ok funcionando ...
	//@todo: Testar outros comandos.
	//...
	
	
	//Testing message box.
	//MessageBox(3, "Shell message box","Testing message box...");
	
	//
	// @todo: Clear client area.
	//        System call redraw client area.
	
	
	//
	// ## prompt string support ##
	//
	shellInitializeWorkingDiretoryString();

	
	
//
// Done.
//	
	
done:
    
	// Se o shell não for interativo não tem login.
	if(interactive == 1)
	{
		FILE *user_stream;
		
		user_stream = ( FILE* ) fopen("user.txt","w+");
		
		// Testing welcome message.
	    printf("\n");
	    printf("Welcome to Gramado Operating System.\n");
	    printf("\n");
	

		
	    printf("username:\n");
	    gets(username);
		
	    printf("password:\n");
	    gets(password);
	
#ifdef SHELL_VERBOSE	
        //@todo colocar o ponteiro na variável no início do arquivo.	
	    printf("username={%s} password={%s}",
		    username, password);
		printf("\n");
#endif
		
		char *c = (char*) &user_stream->_base[0];		
		
		int i;
		
		//procura user name.
		while(*c && *c != 'U')
		{			
			c++;
		};
		
		if( c[0] == 'U' &&
            c[1] == 'S' &&
            c[2] == 'E' &&
            c[3] == 'R' &&
            c[4] == 'N' &&
            c[5] == 'A' &&
            c[6] == 'M' && 			
		    c[7] == 'E' )
		{
		    //USERNAME={fred}
            c = c+10; 
			
		    
		    for( i=0; i<4; i++ )
		    {
				//Move apenas 'fred'
			    buffer[i] = c[i];
		    }			
			
			//printf("\n");
			//printf("%c", c[0]);
			//printf("%c", c[1]);
			//printf("%c", c[2]);
			//printf("%c", c[3]);
			//printf("\n");
			
			//printf("\n");
			//printf("%c", buffer[0]);
			//printf("%c", buffer[1]);
			//printf("%c", buffer[2]);
			//printf("%c", buffer[3]);
			//printf("\n");
			
#ifdef SHELL_VERBOSE			
			printf(">>%s\n", username);
			printf(">>%s\n", buffer);
#endif
			
            if( strncmp( username, buffer, 4 ) == 0 )
            {
#ifdef SHELL_VERBOSE				
				printf("  ## USERNAME OK  ##\n");
#endif				
				login_status = 1;
			}else{
				printf("  ## USERNAME FAIL  ##\n");
				login_status = 0;
			}				

        }else{
			
			printf("USERNAME={ fail\n");
			login_status = 0;
		};



		while(*c && *c != 'P')
		{			
			c++;
		};
		
		if( c[0] == 'P' &&
            c[1] == 'A' &&
            c[2] == 'S' &&
            c[3] == 'S' &&
            c[4] == 'W' &&
            c[5] == 'O' &&
            c[6] == 'R' && 			
		    c[7] == 'D' )
		{
		    //PASSWORD={1234}
            c = c+10; 
			
		    
		    for( i=0; i<4; i++ )
		    {
				//Move apenas '1234'
			    buffer[i] = c[i];
		    }

#ifdef SHELL_VERBOSE				
			printf(">>%s\n", password);
			printf(">>%s\n", buffer);
#endif			
			
            if( strncmp( password, buffer, 4 ) == 0 )
            {
#ifdef SHELL_VERBOSE								
				printf("  ## PASSWORD OK  ##\n");
#endif
				login_status = 1;
			}else{
				printf("  ## PASSWORD FAIL  ##\n");
				login_status = 0;
			}					
			
			
		}else{
		    printf("PASSWORD={ fail\n");
            login_status = 0; 			
		};
		
#ifdef SHELL_VERBOSE
		printf("Login done!\n");
#endif
    
	};
	
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
	
	
	if( interactive == 1 ){
	    shellPrompt();
	}
	
	
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
	
	printf("\n");
	printf("$\n");
	printf("$$\n");
	printf("$$$\n");
    printf(" ############## This is a thread #############\n");
	printf("$$$\n");
	printf("$$\n");
	printf("$\n");
    printf("\n");
	
    refresh_screen();
	
	while(1){}
    while(1)
	{	
	    //printf("$");
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
    }	
};


//help message
void 
shellHelp()
{
    printf(help_banner);	
};

//drawing a tree
void 
shellTree()
{
    printf(tree_banner);	
};


/*
 **************************************************
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicialização de stdio, 
 * prompt foi definido como stdin->_base.
 *
 */
void 
shellPrompt()
{	
	int i;
	
	//Linpando o buffer de entrada.
	for( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
		prompt[i] = (char) '\0';
	}
	
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_status = 0;
	prompt_max = PROMPT_MAX_DEFAULT;  

    printf("\n");
    printf("[%s]",current_workingdiretory_string);	
	printf("%s",SHELL_PROMPT );
	//return;
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



/*
 * shellShowScreenBuffer:
 *     Quando for efeturar o refresh da tela
 * é o conteúdo desse buffer que deve ser pintado 
 * no retãngulo que é a área de cliente do shell.  
 */
//mostra o buffer screen buffer, onde ficam 
//armazenados os caracteres e atributos datela
//do terminal virtual.
//Isso é só um teste.
void shellShowScreenBuffer()
{
	int i;
	int j = 0;
	
	//#teste 
	//screen_buffer[0] = 'd';
	//screen_buffer[2] = 'u';
	//screen_buffer[4] = 'r';
	//screen_buffer[6] = 't';
	
	//shellClearScreen();
    shellSetCursor(0,0);
	
	// Shell buffer.
	for( i=0; i<(DEFAULT_BUFFER_MAX_COLUMNS*DEFAULT_BUFFER_MAX_ROWS); i++ )
	{
		
	    printf( "%c", screen_buffer[j] );
		j++; //ignora o atributo.
		j++;
	};	

    //screen_buffer_pos = 0; 
};


/*
 * shellTestLoadFile:
 *     Carrega um arquivo de texto no buffer e mostra na tela.
 */
void shellTestLoadFile()
{
	FILE *f;
	int Ret;
	int i=0;
	int ch_test;
	
	int pos;
	
	//#importante:
	//precisa ser arquivo pequeno.
	f = fopen("init.txt","rb");  
    if( f == NULL )
	{
		printf("fopen fail\n");
	}else{
		printf("fopen ok\n");
	};	
	
	
	//#test 
	//testando com um arquivo com texto pequeno.
	

	while(1)
	{
		ch_test = (int) getc(f); 
		if( ch_test == EOF )
		{
			printf("\n");
			printf("EOF reached :)\n");
			goto done;
		}else{
		    			
		    //movendo.
			pos = 2*i;	

            if( pos >= SCREEN_BUFFER_SIZE ) 
            {
				printf("shellTestLoadFile: screen_buffer[] limits\n");
				goto fail;
			}				
			
	        screen_buffer[pos] = (char) ch_test; //char	
		    screen_buffer[pos +1] = (char) 0x09; //atributo	
            i++;
 		
	    };
	};	
	
	

	
	//
	// *Testando carregar um arquivo.
	// Ok, isso funcionou.
	//
	
	
	
 

	
	//A QUESTÃO DO TAMANHO PODE SER UM PROBLEMAS 
	// #BUGBUG ;... SUJANDO ALGUMA ÁREA DO SHELL
	
	//Ret = (int) system_call( SYSTEMCALL_READ_FILE, 
	//                         (unsigned long) init_file_name, 
	//  			             (unsigned long) &screen_buffer[0], 
	//						 (unsigned long) &screen_buffer[0] );

	//#test colocando no stdout para depois copiar 
	//no screenbuffer considerando os atributos do caractere.
	//Ret = (int) system_call( SYSTEMCALL_READ_FILE, 
	//                         (unsigned long) init_file_name, 
	//  			             (unsigned long) stdout->_base, 
	//						 (unsigned long) stdout->_base );
							 
	//printf("ret={%d}\n",Ret);
	
    
	

	


	//printf("...\n\n");
	//printf(&screen_buffer[0]);

done:
	//Limpa a tela e reposiciona o cursor.
	//shellClearScreen();
    shellSetCursor(0,0);
	// Mostra na tela o conteúdo do screen buffer.
	//shellRefreshScreen();
	shellShowScreenBuffer();
//
fail:
    return;	
};


/*
 *************************************************************
 * shellTestThreads:
 *     Cria um thread e executa.
 *     #bugbug ...já funcionou uma vez, mas agora está com problemas.
 *     @todo: na hora de criar a thread precisamos passar o PID desse processo.
 */
void shellTestThreads()
{
    void *T;	
	
	//
	// Obs: 
	// As threads criadas aqui são atribuídas ao processo PID=0.
	// @todo: 
	// No kernel, quando criar uma thread ela deve ser atribuída
    // ao processo que chamou a rotina de criação.	
	//
	
	printf("Creating threads...\n");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread1");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread2");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread3");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread4");
	//...
	
	//
	// # Criar e executar #
	//
	
	// Tentando executar um thread.
	// *******************************
    // OBS: 
	// ISSO JÁ FUNCIONOU. 
	// ESTAMOS SUSPENDENDO PORQUE PRECISAMOS AUMENTAR O 
	// TAMANHO DO HEAP USADO PELO PROCESSO PARA 
	// ALOCAÇÃO DINÂMICA, ELE NÃO TÁ DANDO CONTA 
    // DE TODA A DEMANDA POR MEMÓRIA.		  
	//
	
	//>>Dessa vez pegaremos o retorno, 
	// que deve ser o ponteiro para a estrutura da thread.
	// Obs: Não podemos usar a estrutura porque ela está 
	// em ring0.
	//>>Chamaremos a system_call que executa essa thread 
	// que temos o ponteiro da estrutura.
    
	void* ThreadTest1;	
	
	//#bugbug: 
	// Não temos mais espaço no heap do preocesso 
	// para alocar memória pois gastamos o heap com 
	// a imagem bmp. (isso aconteceu kkk).

	unsigned long *threadstack1;
	
	
	enterCriticalSection();
	// #importante:
	// Como a torina de thread é bem pequena e o 
	// alocador tem pouquíssimo heap, vamos alocar o mínimo.
	// Isso é apenas um teste, vamos var se a thread funciona 
	// com um a pilha bem pequena. 2KB.
	threadstack1 = (unsigned long *) malloc(2*1024);
	
	//Ajuste para o início da pilha.
	//threadstack1 = ( threadstack1 + (2*1024) - 4 ); 
	
	//
	// # Criando a thread #
	//
//creating:	
	
	ThreadTest1  = (void*) apiCreateThread( (unsigned long) &shellThread, 
	                                        (unsigned long) (&threadstack1[0] + (2*1024) - 4), 
										    "ThreadTest1" );
										   
	
	printf("shell: Tentando executar um thread ...\n");
	
	if( (void*) ThreadTest1 == NULL )
	{
	    printf("shell-shellTestThreads: apiCreateThread fail \n");	
	    die("ThreadTest1");
	}
	
	//
	// # executando #
	//
	
	
	//Obs:
	//Lá no kernel, isso deve selecionar a thread para 
	//execussão colocando ela no estado standby.
	
	apiStartThread(ThreadTest1);
	exitCriticalSection();
	
	//
	// #bugbug:
	// NÃO ESTÁ RETORNANDO !!
	//
	printf("shell: Tentando executar um thread [ok]...\n");
	//while(1){
	//	
	//	asm( "pause" );
	//}
	//refresh_screen();
	
	//while(1){}
	// **************************
	
	//permitir que o shell continue.
	return;	
};


/*
 *************************************
 * shellClearScreen:
 *     Limpar a tela do shell.
 *     usada pelo comando 'cls'.
 */
void shellClearScreen()
{
	int i;
	
#ifdef SHELL_VERBOSE	
	//#debug
	printf("shellClearScreen:\n");
#endif	
	
	//
	// Limpamos o screen buffer.
	//
	
	// Shell buffer.
	for( i=0; i<(SCREEN_BUFFER_SIZE/2); i++ )
	{
	    screen_buffer[ 2*i ] = ' ';    //char 
		screen_buffer[ 2*i +1] = 0x7;  //atributo 
	};
	
	//
	// Copiamos o conteúdo do screenbuffer para 
	// a área de cliente do shell.
	//

    shellRefreshScreen();
};


/*
 *******************************************
 * shellRefreshScreen:
 *     Copia o conteúdo do (screen_buffer) buffer de output 
 * para a tela. (dentro da janela). 
 * ## Acho que se trata de stdout.
 * É uma memória VGA virtual com caractere e atributo.
 * na hora de efetuar refresh precisamos considerar o atributo 
 * para sabermos a cor do caractere e de seu background.
 */
void shellRefreshScreen()
{
    int lin, col;  
	int Offset; //Deslocamento dentro do screen buffer.
	
#ifdef SHELL_VERBOSE		
	//#debug
	printf("shellRefreshScreen:\n");
#endif 

	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	shellSetCursor(0,0);
	
	//linhas.
	for( lin=0; lin < 25; lin++)
	{
		col = 0;
		shellSetCursor(col,lin);
		
		//colunas.
		for( col=0; col < 80; col++)
		{
		    //Mostra um char do screen buffer.
			printf( "%c", screen_buffer[Offset] );
		    
			Offset++; //ignora o atributo.
		    Offset++;
	    }
	};
	
    //shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};


/*
 ********************************************
 * shellScroll:
 *     @todo: Efetuar um scroll somente dentro 
 * da VGA virtual.
 * #importante: isso não deveria estar aqui,
 * deve ser uma rotina de automação, presente 
 * em alguma biblioteca, servidor ou kernel.
 */
void shellScroll()
{
	int index = 0;
	int next_line_index = 0;
	
	//screen buffer.
	//atualiza o terminal buffer dentro do limite visivel.
	
	int i;
	int j;
	
	//copiaremos 24 linhas
	for( i=0; i < (25 -1); i++) 
	{
		//copiar uma linha de caracteres e atributos.
		//Copia uma linha na linha anterior.
		for( j=0; j < (80*2); j++) 
		{
			//(linha)+offset
			//o deslocamento máximo é 80*2.
			index = (i * (80*2)) + j;
			
			//temos que começar da linha 1 e não da linha 0.
			next_line_index = index + (80*2);
			
			screen_buffer[index] = screen_buffer[next_line_index];
		}
	};
	
	
	//nesse momento copiamos 24 linhas,
	//então vamos limpara a linha 24, que é a última linha,
	//essa é a vigésima quinta linha.
	int up_count = ((25 -1) * (80*2));
	
	//deslocamento dentro da linha.
	//80 deslocamentos.
	for( j=0; j < 80; i++) 
	{
		//base referente ao início da última linha,
		//mais o deslocamento.
		index = up_count + j;
		
		//pinta espaço na última linha.		
	    screen_buffer[ 2*index ] = ' ';    //char 
		screen_buffer[ 2*index +1] = 0x7;  //atributo 
	}


    //
    // ## Refresh ##
    //
	
	//depois de atualizado o conteúdo do buffer 
	//é necessário efetuar refresh e mostrar na tela.
	//shellRefreshScreen();
	shellShowScreenBuffer();
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
void 
shellInsertCharXY( unsigned long x, 
                   unsigned long y, 
				   char c )
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
	screen_buffer_pos++;
	if( screen_buffer_pos >= (80*25*2) )
	{
	    //#fim do buffer
        printf("shellInsertNextChar: limit");		
	}
	screen_buffer[ screen_buffer_pos*2 ] = (char) c;
	screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;
};


void shellInsertCR()
{
	screen_buffer_pos++;
	if( screen_buffer_pos >= (80*25*2) )
	{
	    //#fim do buffer
        printf("shellInsertCR: limit");		
	}
	
   screen_buffer[screen_buffer_pos*2 ] = (char) '\r';
   screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;   
};


void shellInsertLF()
{
	screen_buffer_pos++;
	if( screen_buffer_pos >= (80*25*2) )
	{
	    //#fim do buffer
        printf("shellInsertLF: limit");		
	}
	
    screen_buffer[ screen_buffer_pos*2 ] = (char) '\n';
    screen_buffer[ (screen_buffer_pos*2)+1 ] = 7;	
};


void shellInsertNullTerminator()
{
	screen_buffer_pos++;
	if( screen_buffer_pos >= (80*25*2) )
	{
	    //#fim do buffer
        printf("shellInsertNullTerminator: limit");		
	}
	
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
	//return;
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
	//return;
};


//show shell info
void shellShowInfo()
{
	int PID, PPID;
	
    printf(" ## shellShowInfo:  ##\n");
	
	
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
	//...
};


//metrics
void 
shellShowMetrics()
{
	unsigned long screen_width;
	unsigned long screen_height;
	unsigned long cursor_width;
	unsigned long cursor_height;
	//unsigned long mouse_pointer_width;
	//unsigned long mouse_pointer_height;
	unsigned long char_width;
	unsigned long char_height;	
	//...

	screen_width = apiGetSystemMetrics(1);
	screen_height = apiGetSystemMetrics(2);
	
	cursor_width = apiGetSystemMetrics(3);
	cursor_height = apiGetSystemMetrics(4);
	
	//mouse_pointer_width = apiGetSystemMetrics(5);
	//mouse_pointer_height = apiGetSystemMetrics(6);
	
	char_width = apiGetSystemMetrics(7);
	char_height = apiGetSystemMetrics(8);
	//...
	
	printf("\n");  
	printf("  ##  shellShowMetrics:  ##\n");
	printf("screenWidth={%d} screenHeight={%d}\n",screen_width, screen_height );
		
	printf("cursorWidth={%d} cursorHeight={%d}\n", cursor_width, cursor_height );
		
	//printf("mousepointerWidth={%d} mousepointerHeight={%d}\n", 
	//    mouse_pointer_width, mouse_pointer_height );
	
	printf("charWidth={%d} charHeight={%d}\n",char_width, char_height );	
	//...
	
    printf("Done\n");	
	//return;
};

//show system info
void shellShowSystemInfo()
{
	int ActiveWindowId;
	int WindowWithFocusId;
	
	printf("  ##  shellShowSystemInfo:  ##\n");
	
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
    int wID;	
	//
	// #bugbug.
	// Testando a estrutura de janela.
	// A janela foi criada pelo kernel e copiamos o ponteiro 
	// da estrutura para um ponteiro em user mode.
	// Podemos ter erros de memória com essas operações.
		
	printf("\n");	
	printf("  ##  shellShowWindowInfo  ##\n");
	
	printf("mainWindow={%x}", shell_info.main_window );
		
	//#bugbug 
	//temos um problema aqui.
	// provavelmente o erro é por acessar um endereço que está 
	// em kernel mode.
	//if( shell_info.main_window->left > 0 && shell_info.main_window->top > 0  )
	//{
	//    shellSetCursor( (shell_info.main_window->left/8), (shell_info.main_window->top/8) );
	//}
		
		
	//obs: Isso é uma estrutura interna, não reflete 
    //a informação usada pelo kernel.	
	printf("\n");		
	printf("terminal_rect: \n");	
    printf("l={%d} t={%d} w={%d} h={%d}\n", terminal_rect.left,
		                                    terminal_rect.top,
									  	    terminal_rect.width,
											terminal_rect.height );

													  
	//Obs: isso funcionou. setando o cursor.
	//if( terminal_rect.left > 0 && terminal_rect.top > 0 )
	//{											  
    //    shellSetCursor( (terminal_rect.left/8), (terminal_rect.top/8) );													  
	//};
		
		
	wID = (int) system_call( SYSTEMCALL_GETTERMINALWINDOW, 0, 0, 0); 
	
	printf("\n current terminal: \n");
	printf("Windows ID for current terminal = {%d} \n", wID);
	
	//...
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

 
//@todo: Criar rotina de saída do shell.
void shellExit(int code)
{
	//@todo ...
	exit(code);
};
 

/*
 *****************************************
 * shellUpdateWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */
void 
shellUpdateWorkingDiretoryString( char *string )
{
	if( pwd_initialized == 0 ){
		goto fail;
	}else{
		
        if( (void*) string == NULL )
	    {
		    goto fail;
	    }else{
	    
	        // ## separador ##
		    //strcat( current_workingdiretory_string, 
			//    SHELL_PATHNAME_SEPARATOR );		
		
		    //
	        // ## separador ##		
		    strcat( current_workingdiretory_string, 
			    string );	

		    strcat( current_workingdiretory_string, 
			    SHELL_PATHNAME_SEPARATOR );				
		
            //Atualizar no gerenciamento feito pelo kernel.
	        system_call( 175,
	            (unsigned long) string,
		        (unsigned long) string, 
		        (unsigned long) string );		
		};
	};
	//...
fail:	
done:
    return;
};


/*
 *****************************************
 * shellInitializeWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */
void 
shellInitializeWorkingDiretoryString()
{
	
	//get info
	
	//test: get current volume id.
	current_volume_id = (int) system_call(171,0,0,0);
	
	//global usada para string do nome do volume.
	current_volume_string = (char *) SHELL_VOLUME1_STRING;
	
	
    //
    //  ## volume list ##
    //	
	
	//root:
    //primeiro colocamos a string que indica 
	//a lista de volumes.
    sprintf( current_workingdiretory_string, 
             SHELL_VOLUMELIST_STRING ); 
	
	
	//
	// ## separador ##
	//

	//root:/
	strcat( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
	//
	//  ## volume root dir ##
	//
	
	//root:/volumex
	strcat( current_workingdiretory_string, current_volume_string );

	//
	// ## separador ##
	//

	//root:/volumex/
	strcat( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
done:
    pwd_initialized = 1;
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
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
	                                                 id, 0, 0);
	
	printf("Current Process heap pointer address %x\n", 
	    (unsigned long) heap_pointer);
};


void shellShowKernelHeapPointer()
{
	int id = 0;  //Id do processo kernel. 
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
	                                                 id, 0, 0);
	
	printf("Current Process heap pointer address %x\n", 
	    (unsigned long) heap_pointer );
};


//mostra informações sobre o disco atual.
void shellShowDiskInfo()
{
	//@todo: atualizar api.h
	system_call( 251, 0, 0, 0);
};

//mostra informações sobre o volume atual.
void shellShowVolumeInfo()
{
	//@todo: atualizar api.h
	system_call( 252, 0, 0, 0);
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
// Credits: Luiz Felipe
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
 *     ## executa arquivos do tipo ">test.bin"
 *
 *     #importante; E caso o arquivo não tenha extensão?
 *     # Devemos presumir que ele seja .bin ?? 
 *       Ou não tenha ponto nem extensão. ?? Certamente o 
 * carregamento irá falhar.
 *     #@todo: caso seja .bin mas começe com "/"
 *     Devemos suprimir a barra. 
 *     
 */									 
int shell_gramado_core_init_execve( const char *arg1,  //nome
                                    const char *arg2,  //arg
                                    const char *arg3 ) //env
{
	//erro.
	int Status = 1;
	
	//unsigned long arg_address = (unsigned long) &argv[0];

	// suprimindo dot-slash
	// The dot is the current directory and the 
	// slash is a path delimiter.
	//if( filename[0] == '.' && filename[1] == '/' )
	//{ 
	//    filename++;
    //    filename++; 
    //    goto translate;	
	//};
	
	
	//suprimindo a barra.
	//if( *arg1 == '/' || 
	//    *arg1 == '\\' )
	//{ 
	//    arg1++; 
	//};
	
	
	
translate:	
	
	//
	// ## BUG BUG
	//
	// Talvez nesse momento, ao transformar a string ele 
	// corrompa o espaço reservado para o argumento seguinte.
	// vamos fazer um teste no quan a rotina não precise 
	// acrescentar zeros.
	//
	
	//
	// correto é isso mesmo,
	// para não corromper o espaço dos argumentos no vetor,
	// teremos que transformar somente lá no kernel, pouco antes 
	// de carregarmos o arquivo.
	//
	
	//Isso faz uma conversão de 'test.bin' em 'TEST    BIN'.
	//Ok funcionou.
	//shell_fntos( (char *) arg1);
	
	//const char* isso não foi testado.
	//shell_fntos(filename);


	// #importante:
	// Isso deve chamar gramado_core_init_execve() na api.
								
								


   	
 //isso chamará uma rotina especial de execve, somente 
//usada no ambiente gramado core. 
execve:

//
// #importante
// Nesse momento o shell pode atuar com outro procedimento de janela 
// que ficaria responsável por conduzir essas mensgens ató o processo 
// filho, que ate mesmo ser um aplicativo que não use  recursos gráficos.
// Esse processo filho a janela do shell como output e o shell como input.
// Ex: um aplicativo chamado pelo shell pode chamar a função getch() para 
// obter input ... como o shell tem a janela com o foco de entrada, então 
// o shell precisa enviar a mensagem para esse aplicativo. Como ?
// Uma opção seria fazer uma chamada ao kernel enviando essa mensagem 
// para o lugar padrão onde os aplicativos pegam mensagens do tipo caractere.
// Ou seja, getch() solicita um caractere ao kernel, e quem enviou esse caractere 
// ao kernel foi o shell no qual o aplicativo está rodando.
// Se esse aplicativo pertence a um terminal específico, então o caractere 
// pode ser enviado para a estrutura desse terminal específico. Pode uasr 
// descritores de terminal.
// teminalFeed(teminal_id,ch) poderia enviar o caratere para um terminal específico,
// de onde o aplicativo pegará o caractere.
//	

    //
    // O retorno significa que o aplicativo foi colocado
	// para rodar e em breve receberá tempo de processamento.
	// '0' significa que funcionou e '1' que falhou.
    //	
	
	//
	// Obs: Se retornar o número do processo então podemos esperar por ele 
	// chamadno wait(ret);
	//
	
	Status = (int) system_call( 167, 
	                          (unsigned long) arg1,    //Nome
				              (unsigned long) arg2,    //arg
				              (unsigned long) arg3 );  //env
							  
							  
    if( Status == 0 )
	{
		//Não houve erro. O aplicativo irá executar.
		
		//
		// Nesse momento devemos usar um novo procedimento de janela.
		// Que vai enviar as mensagens de caractere para um terminal 
		// específico, para que aplicativos que user aquele terminal 
		// possam pegar essas mensgens de caractere.
		//
		
#ifdef SHELL_VERBOSE		
		printf("shell: aplicativo inicializado.\n"); 
#endif
		
		//
		// ## teste ##
		//
		// saindo do shell.
		//
		
		// getpid...
		// waitforpid(?);
		
		//die("Exiting shell.bin\n");
		
		//Saindo sem erro.
		//exit(0);
		
		//Saída elegante, retornando para o crt0.
		ShellFlag = SHELLFLAG_EXIT;
		
		//ShellFlag = SHELLFLAG_FEEDTERMINAL;		
		goto done;
	}else{
		
		// Se estamos aqui é porque ouve erro 
		// ainda não sabemos o tipo de erro. 
		// Status indica o tipo de erro.
		// Se falhou significa que o aplicativo não vai executar,
		// então não mais o que fazer.
		
		//#importante: Error message.
		printf("shell: aplicativo nao foi inicializado.\n");
		
		ShellFlag = SHELLFLAG_COMMANDLINE;
		goto fail;
	};
	
	
	//fail.
	
	//
    // Retornaremos. 
	// Quem chamou essa rotina que tome a decisão 
	// se entra em wait ou não.
    //

	
fail:
    //#importante: Error message.
    //status = 1.
    printf("shell_gramado_core_init_execve: \n fail retornando ao interpretador\n");
done:
    return (int) Status;						  
};



/*
 * feedterminalDialog:
 *     Para alimentar um terminal com caracteres.
 */					  
int feedterminalDialog( struct window_d *window, 
                      int msg, 
				      unsigned long long1, 
				      unsigned long long2 )
{
	int q;
	
	switch(msg)
	{
	
	
	    //para alimentar o terminal
		case MSG_KEYDOWN:
			//para todas as teclas.
			//feed terminal system call.
			system_call( 135,  // número do serviço 
			             0,    // número do terminal
						 long1,    // o caractere
						 long1 );  // o caractere

			break;
			
		//para sair do diálogo.	
		case MSG_SYSKEYDOWN:
		    switch(long1)
			{

                //
                // ?? #importante:
				// ?? Quando parar de alimentar o terminal ??
                // ## [CONTROL + C]  ou [ESC]  ## 
				// >>> F12 POR ENQUANTO PARA TESTES.
				//
				//help
				case VK_F1:
				    //APISetFocus(i1Window);
					//APIredraw_window(i1Window);
					MessageBox( 1, "feedterminalDialog","F1: HELP");
					break;
				
                //full screen
                //colocar em full screen somente a área de cliente. 				
		        case VK_F2:
				    //APISetFocus(i2Window);
					//APIredraw_window(i2Window);				
				    MessageBox( 1, "feedterminalDialog","F2: ");
					//ShellFlag = SHELLFLAG_COMMANDLINE;
					break;
					
				case VK_F3:
				    printf("F3: Saindo do aplicativo e voltando ao shell...\n");
				    ShellFlag = SHELLFLAG_COMMANDLINE;
				    break;
					
					
			};
		    break;
			
		default:  
		    break;
	
    };
	
done:
    return (int) 0;
};


void die(char *str)
{
	printf("die: %s",str);
	//@todo
	fprintf(stderr,"%s\n",str);
	exit(1);
};


void *
xmalloc( int size)
{
    register int value = (int) malloc(size);
    if(value == 0)
        die("xmalloc fail.\n");
	    //fatal("Virtual memory full.");
done:  
    return (void *) value;
};


char *
concat( char *s1, char *s2, char *s3 )
{
  int len1 = (int) strlen(s1);
  int len2 = (int) strlen(s2);
  int len3 = (int) strlen(s3);
  
  char *result = (char *) xmalloc( len1 +len2 +len3 +1 );

  strcpy( result, s1);
  strcpy( result +len1, s2 );
  strcpy( result +len1 +len2, s3 );
  
  *( result +len1 +len2 +len3 ) = 0;

done:  
  return (void *) result;
};




void error( char *msg, 
            char *arg1, 
	        char *arg2 )
{
    //fprintf(stderr, "cc: ");
    fprintf(stderr,"%s %s %s", msg, arg1, arg2);
    fprintf(stderr, "\n");
};


/*
void 
reader_loop()
{
	while( !EOF_Reached )
	{
		//...
		
		
		
		
	};
	
};
*/

 

/*
 **********************************************************
 * shellExecuteThisScript:
 *     Aqui temos que carregar o arquivo de script indicado 
 * nos argumentos.
 * #importante:
 * Apenas colocaremos o arquivo em stdin, que é o pormpt[]
 * e retornaremos ao incio da função que compara, para 
 * comparar agora o que estava escrito no arquivo de script.
 */
int 
shellExecuteThisScript( char* script_name )
{
    FILE *script_file;	
	int i;
	
    //
	// Aqui temos que carregar o arquivo de script indicado 
	// nos argumentos.
	//
	
	printf("shellExecuteThisScript:\n");	
	printf("Initializing script ...\n");
    printf("CurrentFile={%s}\n",script_name);

    script_file = fopen(script_name,"rw");
	
	if( (void*) script_file == NULL )
	{
		printf("skip_input: Can't open script file!\n");
		die("*");
	}
	
	
	//atualizando a linha de comandos no prompt[], stdin.
	

	for( i=0; i< 128; i++ )
	{
		stdin->_base[i] = script_file->_base[i];
	}
	
	
	//EOF_Reached = EOF;

done:	
    return (int) 0;		
};


/*
char **
array_of_strings()
{
	char **a;
	
	a[0] = "test0";
	a[1] = "test1";
	a[2] = NULL;
	
	return (a);
};
*/


/*
//retorna o pool de strings contendo os nomes dos arquivos
//em um diretório que está no buffer.
char **
get_dir_files( char *buffer )
{
    char **poll;	
	
	// ...
	
	
    return (poll);	
}
*/

/*
//coloca no pool de strings passado por argumento 
//as strings que correspondem  aos nomes 
// dos arquivos encontrados no diretório 
//indicado pelo buffer.
int set_dir_files( char **poll, char *buffer )
{
	
	//...
	
    return (0);
};
*/


/*
 **************************************
 * absolute_pathname:
 * Retorna 1 nos seguintes casos:
 *
 * >/
 * >.
 * >./
 * >..
 * >../
 *
 * Credits: bash 1.05
 */
int
absolute_pathname( char *string )
{
    if( !string || !strlen(string))
        return (0);

    if( *string == '/' )
        return (1);

	//.
    if( *string++ == '.' )
    {
        // ./
		if( (!*string) || *string == '/' )
	        return (1);

        // ..
		if( *string++ == '.' )
	        if(!*string || *string == '/')  //../
	        return (1);
    }
    return (0);
};



//inicializaremos o supporte a pathname
int shellInitPathname()
{
	int i;
	
	if(pathname_initilized == 1){
		goto done;
	}
	
	for( i=0; i<PATHNAME_LENGHT; i++ )
	{
		pathname_buffer[i] = (char) '\0';
	}
	
	pathname_lenght = 0;
	
    	
	//...
	
done:	
    pathname_initilized = 1;
	return (int) 0;
};




 
//inicializaremos o supporte a filename
int shellInitFilename()
{
	int i;
	
	if(filename_initilized == 1){
		goto done;
	}
	
	for( i=0; i<FILENAME_LENGHT; i++ )
	{
		filename_buffer[i] = (char) '\0';
	}
	
	filename_lenght = 0;
	
    	
	//...
	
done:	
    filename_initilized = 1;
	return (int) 0;
};


/* 
 Remove the last N directories from PATH.  
 Do not leave a blank path.
 PATH must contain enough space for MAXPATHLEN characters. 
 Credits: bash 1.05
 */
void 
shell_pathname_backup( char *path, int n )
{
    register char *p = path + strlen(path);
	
	unsigned long saveN = (unsigned long) n;

    //#debug 
	//printf("%s", path);
	
	if(*path)
       p--;

    while(n--)
    {
        while(*p == '/')
	        p--;

        while(*p != '/')
	        p--;

        *++p = '\0';
    };
	
//
//
	//@todo: Criar em kernelmode uma roptina que 
	//que faça o mesmo que a shell_pathname_backup 	
            //Atualizar no gerenciamento feito pelo kernel.
	        system_call( 176,
	            (unsigned long) saveN,
		        (unsigned long) saveN, 
		        (unsigned long) saveN );			
    	
};





//isso vai ser usado pelo echo.
void
shell_print_tokenList(char *token_list[], char *separator)
{ 
	char *token;
	
	token = (char *) token_list[0];
	
	if( token == NULL )
	    goto fail;
	
	
	//token = (char *) tokenList[i];
		
	//	if( token == NULL ){
			
    int i;
	for( i=0; i,128; i++ )
    {
		token = (char *) token_list[i];

	    if( token == NULL )
	        goto done;
		
		if( strncmp( (char*) token_list[i], "echo", 4 ) == 0 )
		    continue;	
		
		printf("%s", token_list[i]);
		printf("%s", separator);
    }
	
	
fail:
done:
    return;	
}


/* 
This way I don't have to know whether fclose is a function or a macro. 
Credits: bash 1.05.
 */
/*
int
stream_close( FILE *file );
int
stream_close( FILE *file )
{
     return ( fclose(file) );
};
*/

/* 
 Return the octal number parsed from STRING, or -1 to indicate
 that the string contained a bad number. 
 Credits: bash 1.05.
 */
/* 
int
read_octal( char *string );
int
read_octal( char *string )
{
    int result = 0;
    int digits = 0;
    
	while( *string && 
	       *string >= '0' && 
		   *string < '8' )
    {
        digits++;
        result = (result * 8) + *string++ - '0';
    };

    if(!digits || result > 0777 || *string)
        result = -1;

    
done:	
	return (result);
};
*/

/*  Credits: bash 1.05. */
/*
void 
decrement_variable( int *var );
void 
decrement_variable( int *var )
{
    *var = *var - 1;
};
*/




/* Check if it's a .bin file */
int
is_bin( char *cmd )
{
    char *p;
	
	p = cmd;
	
	int len = strlen(p);
    
	if( len <= 4 ) 
		return 0;
	
    p += len - 4;
    
	if( *p++ != '.' ) 
		return 0;
	
    if( strncmp( (char*) p, "bin", 3 ) == 0 )
    {
	    return 1;	
	}

fail:	
    return 0;
};


/* Check if it's a .sh1 file */
int
is_sh1( char *cmd )
{
    char *p;
	
	p = cmd;
	
	int len = strlen(p);
    
	if( len <= 4 ) 
		return 0;
	
    p += len - 4;
    
	if( *p++ != '.' ) 
		return 0;
	
    if( strncmp( (char*) p, "sh1", 3 ) == 0 )
    {
	    return 1;	
	}

fail:	
    return 0;
};



