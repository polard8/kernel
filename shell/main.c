/*
 * File: main.c @todo: Criar a janela shell help.
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


/*
    Fluxo padrão:
	
    FILE *stdin; 
    FILE *stdout; 
    FILE *stderr; 
    
	#include <stdio.h>
*/

 
 


//
// Definindo mensagens..@todo: Mover para a API.
//

#define CMD_ABOUT 1000
//#define CMD_ABOUT 1001
//#define CMD_ABOUT 1002
//#define CMD_ABOUT 1003
//...

//
// Variáveis internas.
//

int shellStatus;
int shellError;
int shellMaxColumns;
int shellMaxRows;
int shellScreenWidth;
int shellScreenHeight;
//...


//
// Buffer:
// Esse buffer pode ser usado para algum log ou pra testar função que escreve
// em arquivo.
//

//#define SHELL_BUFFER_SIZE 512
#define SHELL_BUFFER_SIZE 1024 //tests

char shell_buffer[SHELL_BUFFER_SIZE]; 
unsigned long shell_buffer_pos; 
unsigned long shell_buffer_width;  //Largura dada em número de caracteres.
unsigned long shell_buffer_height; //Altura dada em número de caracteres.
//...

//
// Window position.
//

//unsigned long shell_window_x;
//unsigned long shell_window_y;


//
// Window size.
//

//unsigned long shell_window_width;
//unsigned long shell_window_height;


//
// font support.
//

//FILE *font_file;


//
// Testes
//
int test_operators();

//
// Funções internas.
//


void shellSetCursor(unsigned long x, unsigned long y);
void shellThread();
void shellPrompt();
void shellHelp();
unsigned long shellCompare();    //Compare command.
void shellWaitCmd();             //Wait for command.
int shellInit();                 //Init.
void shellShell();               //Constructor. 
unsigned long shellProcedure( struct window_d *window, 
                              int msg, 
							  unsigned long long1, 
							  unsigned long long2 );
 
 
 
/*
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
 */
void *GramadoMain( int argc, char *argv[], unsigned long address, int view )
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
	struct window_d *hWindow;
    
	//struct message_d *m;

	
	int Status = 0;
	int ShellFlag = 0;
	char *s;    //String	

	//...
	
	
	
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
        sprintf( shell_buffer,"Starting Shell with no arguments...\n");	 //Test.	
	    goto noArgs; 
	};
	
	//if (argc <= 1){
    //    fprintf( stderr, "%s\n", usage ); //File??
    //    exit(1);
    //}
	
	//
	// Filtra o primeiro argumento no formato 'palavra'.
	//
	
    if (!strcmp( argv[1], "-help" )){
        printf( "%s\n", usage );
        refresh_screen();
		exit(0);
    }
    
	if (!strcmp( argv[1], "-version" )){
        //printf( "%s\n", shellGetVersion() );
        refresh_screen();
		exit(0);
    }	
	
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
                    case 'h':
                        //if (!strcmp( argv[argc], "help" )){ ... };
						//if (!strcmp( argv[argc], "HELP" )){ ... };
						//...
						ShellFlag = 0;
                        break;

                    case 'v':
					    //if (!strcmp( argv[argc], "version" )){ ... };
						//if (!strcmp( argv[argc], "VERSION" )){ ... };
						//...
                        ShellFlag = 0;
                        break;

                    case 'r':
					    //if (!strcmp( argv[argc], "XXX" )){ ... };
					    ShellFlag = 0;
                        break;

                    case 'f':
					    //if (!strcmp( argv[argc], "XXX" )){ ... };
						ShellFlag = 0;
                        break;

                    default:    
					    //usage();
						break;
                };
            };
        }
        else 
		{
			goto noArgs; 
            //usage();
        }
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
	
	apiBeginPaint();
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1," // SHELL.BIN ",     
                                       10, 10, 200, 200,    
                                       0, 0, 0 , COLOR_BLACK );	   
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
	apiEndPaint();
	
	//
	// Funcionou setar o foco, e a mensagem foi para a janela certa.
	//
	
    //Registrar.
    APIRegisterWindow(hWindow);
	
    //Configurar como ativa.
    APISetActiveWindow(hWindow);
	
    //Setar foco.
	//*IMPORTANTE: É FUNDAMENTAL SETAR O FOCO, POIS O KERNEL DEPENDE DELE
	//PARA RETORNAR A MENSAGEM DA JANELA COM O FOCO DE ENTRADA.
    APISetFocus(hWindow);
		
	
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
	Status = (int) shellInit(); 
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
	
	//system_call( SYSTEMCALL_DRAWTEXT, shell_cursor_x,  shell_cursor_y, (unsigned long) "Starting SHELL.BIN ... \n");		
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
	
	int msgTest;
	void *long1;
	void *long2;
	

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
		msgTest = (int) system_call( SYSTEMCALL_GET_KEYBOARD_MESSAGE, 
		                              (unsigned long) hWindow, //isso passa um endereço virtual que o kernel não conheçe.
									  (unsigned long) hWindow, 
									  (unsigned long) hWindow );
									  
		long1 = (void*) system_call( SYSTEMCALL_GET_LONG1, 
		                             (unsigned long) hWindow, 
									 (unsigned long) hWindow, 
									 (unsigned long) hWindow );
									 
		long2 = (void*) system_call( SYSTEMCALL_GET_LONG2, 
		                             (unsigned long) hWindow, 
									 (unsigned long) hWindow, 
									 (unsigned long) hWindow );		
		
		// Send Message to procedure.
		if( (int) msgTest != 0)
		{
			//Obs: Chamado diretamente, sem interface nenhuma.
			//     Mas não deve ser assim.
		    shellProcedure( NULL, 
			                (int) msgTest, 
							(unsigned long) long1, 
							(unsigned long) long2 );
			
			//printf("Y-DEBUG: hwindow NULL\n"); //Deletar isso depois.
			//printf("Y-DEBUG: msg={%d}\n",msgTest); 
			//printf("Y-DEBUG: long1={%c}\n",long1); 
			//printf("Y-DEBUG: long2={%c}\n",long2); 
		};
		
		//Nothing.
	};
	

	//
	// @todo: Rotinas de comparação e execução do comando.
	//

	
    while(1)
	{
        //shellInit(); 
		// shellCompare();
	};
	
	
	//
	// Exit process.
	//
	
end:
    while(1){}    //Hang.
    //MessageBox(...);	
	exit(0);  
	return (int) 0;
};


/*
 ***********************************************
 * shellProcedure:
 *     Procedimento de janela.
 */
unsigned long 
shellProcedure( struct window_d *window, 
                int msg, 
				unsigned long long1, 
				unsigned long long2 )
{
    unsigned long input_ret;
    unsigned long compare_return;	
	
    switch(msg)
    { 
		case MSG_KEYDOWN:
            switch(long1)
            {
				//reset prompt.
				case '8':
				    shellPrompt();
				    goto done;
					break;
				    
				//test return
				case '9':
				case VK_RETURN:
				    input('\0'); //finaliza a string
					shellCompare();
					goto done;
                    break;
                //Mostrar o buffer
                //case '1':
                   // printf("%s\n",&prompt[0]);
				//    break; 

				//Mostrar o buffer	
               // case '2':
                //    printf("%s\n",prompt);
				//    break; 

				//	
                //case '#':
				//case '3':
				//    printf("Shell procedure case 3\n");
                //    break;
					
                //case '9':
                //    MessageBox( 1, "Shell","Test 9");
                //    break; 					
                              
                //Texto - Envia o caractere.
                   //Imprime os caracteres normais na janela com o foco de entrada.
				//enfilera os caracteres na string 'prompt[]'.
				   //para depois ser comparada com outras strings.
                default:  
				    printf("%c", (char) long1); 			   
				    input( (unsigned long) long1);				  
					goto done;
                    break;               
            };
        break;
		
		case MSG_KEYUP: 
		    //printf("%c", (char) 'u');
           // printf("%c", (char) long1);  			
		    break;
		
		//Não intercptaremos mensagens do sistema por enquanto.
		//As mensagens do sistema são interceptadas primeiro pelo procedimento 
		//do sistema.
		//case MSG_SYSKEYDOWN:
		//    switch(long1)
		//    {
		//		case VK_ESCAPE: printf("shell procedure Esc\n");
		//	};
		//break;
		
		case MSG_SYSKEYUP: 
		    //printf("%c", (char) 'U');
            //printf("%c", (char) long1);			
		    break;
          
		case MSG_COMMAND:
            switch(long1)
			{
				case 0:
				    MessageBox( 1, "Shell","Testing MSG_COMMAND.NULL.");
				    break;
				
				//About
				case CMD_ABOUT:
				    MessageBox( 1, "Shell","Testing MSG_COMMAND.CMD_ABOUT.");
				    break;
				
				//...
				
				//default:
				//break;
			}
		break; 		
		
		//Essa mensagem pode ser acionada clidando um botão.
		//case MSG_CLOSE:
		//break;
		
		//Essa mensagem pode ser acionada clidando um botão.
		//case MSG_DESTROY:
		//break;
		
		//Quando a aplicativo em user mode chama o kernel para 
		//que o kernel crie uma janela, depois que o kernel criar a janela,
		//ele faz uma chamada ao procedimento de janela do aplicativo com a mensagem 
        //MSG_CREATE, se o aplicativo retornar -1, então a rotina em kernel mode que 
        //esta criando a janela, cancela a janela que está criando e retorn NULL.
        //		
		//case MSG_CREATE:
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
		refresh_screen();
	//};	
    return (unsigned long) 0;	
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
 */
unsigned long shellCompare()
{
    unsigned long ret_value;
	
	
	//shellWaitCmd();  //cancelada.

    //conferir se o enter foi o último caractere digitado.
    //if( prompt_status != 1 ){
	//	return (unsigned long) 1;  //erro.
	//}	
	
    //
    // o enter foi o caractere digitado, vamos comparar palavras.
    //	
	
palavra_reservada:
	
	//cria arquivos e diretorios principais..
	if( strncmp( prompt, "makeboot", 8 ) == 0 )
	{
	    printf("~makeboot\n");
		
		//ret_value = fs_makeboot();
		//if(ret_value != 0){
		//    printf("shell: makeboot fail!");
		//};
        goto exit_cmp;
    };
	
	
	if( strncmp( prompt, "format", 6 ) == 0 )
	{
	    printf("~format\n");
		//fs_format(); 
        goto exit_cmp;
    };	
	
	if( strncmp( prompt, "debug", 5 ) == 0 )
	{
	    printf("~debug\n");
		//debug();
        goto exit_cmp;
    };
		
 
	if( strncmp( prompt, "dir", 3 ) == 0 )
	{
	    printf("~dir\n");
		//fs_show_dir(0); 
        goto exit_cmp;
    };


	// newfile
	if( strncmp( prompt, "newfile", 7 ) == 0 )
	{
	    printf("~newfile - create empty file.\n");
		//fs_create_file( "novo    txt", 0);
        goto exit_cmp;
    };
	
	// newdir
	if( strncmp( prompt, "newdir", 7 ) == 0 )
	{
	    printf("~newdir - create empty folder.\n");
		//fs_create_dir( "novo    dir", 0);
        goto exit_cmp;
    };
	
    //testa mbr
    if( strncmp( prompt, "mbr", 3 ) == 0 )
	{
	    printf("~mbr\n");
		//testa_mbr();
		goto exit_cmp;
    }; 
	
    //testa /root
    if( strncmp( prompt, "root", 4 ) == 0 )
	{
	    printf("~/root\n");
		//testa_root();
		goto exit_cmp;
    }; 

	
    if( strncmp( prompt, "start", 5 ) == 0 )
	{
	    printf("~start\n");
		goto exit_cmp;
    }; 
	
    if( strncmp( prompt, "help", 4 ) == 0 ){
		shellHelp();
		goto exit_cmp;
    };
	
    if( strncmp( prompt, "cls", 3 ) == 0 )
	{
	    //black
	    //kclear(0);
        goto exit_cmp;
	};
 	  	
    if( strncmp( prompt, "reboot", 6 ) == 0 )
	{
	    printf("~reboot\n");
		//reboot();
        //KiReboot();
		goto exit_cmp;
    };
	
    if( strncmp( prompt, "exit", 4 ) == 0 ){
        printf("~exit\n");
		exit(0);
		goto exit_cmp;
    };
	
    if( strncmp( prompt, "hd", 2 ) == 0 )
	{
	    printf("~hd\n");
        goto exit_cmp;
    };
	
	if( strncmp( prompt, "save", 4 ) == 0 )
	{
	    printf("~save root\n");
        goto exit_cmp;
    };
	
	//muda um arquivo da area de transferencia para 
	//o sistema de arquivos...
	if( strncmp( prompt, "install", 7 ) == 0 )
	{
	    printf("~install\n");
		//fs_install();
        goto exit_cmp;
    };
	
	
	//boot - inicia o sistema carregado
	if( strncmp( prompt, "boot", 4 ) == 0 )
	{
	    printf("~boot\n");
		//boot();
        goto exit_cmp;
    };

	//service
	if( strncmp( prompt, "service", 7 ) == 0 )
	{
	    printf("~service - testa servicos do kernel:\n");
		//test_services();
        goto exit_cmp;
    };

	//slots
	if( strncmp( prompt, "slots", 5 ) == 0 )
	{
	    printf("~slots - mostra slots \n");
		//mostra_slots();
        goto exit_cmp;
    };
	
	
    if( strncmp( prompt, "version", 7 ) == 0 ){
	    printf("%s\n",SHELL_VERSION);
        goto exit_cmp;
    };	
 
palavra_nao_reservada:
    printf("Unknown command!\n");
	return (unsigned long) 1;
	
exit_cmp: 
    return (unsigned long) 0;
};


/*
 * shellShell:
 *     Constructor.
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
    shellMaxColumns = (320/8);  //30;    //80
    shellMaxRows    = (480/8);  //20;    //25
    shellScreenWidth = shellMaxColumns;
    shellScreenHeight = shellMaxRows;
    //...	

	//
	// Em stdio.h.
	//
	
    //Prompt.
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_max = 250;  //??	PROMPT_MAX_DEFAULT
    prompt_status = 0;	
	
	
	//
	// Shell buffer.
	//

	for( i=0; i<SHELL_BUFFER_SIZE; i++){
		shell_buffer[i] = 0;
	}
	shell_buffer[0] = (char) '\0';
	
	//
	// @todo: E o fluxo padrão. Quem configurou os arquivos ???
	//        o kernel configuroru???
	//
	
	//Número máximo de colunas e linhas.
	g_columns = shellMaxColumns; //30;
	g_rows = shellMaxRows;       //20;
    //...
	
	
	//...
	
done:	
	shellSetCursor(0,4); //cursor.
    return;	
};


/*
 * shellInit:
 *     Inicializa o Shell.  
 *     #bugbug: Essa rotina começa escrever na janela com o foco de entrada.
 * um outro aplicativo solicitou o foco de entrada e essa rotina esta terminando 
 * de escrever mas agora na janela do outro aplicativo.
 * ?? o que fazer ?? sincronização?? 
 */
int shellInit()
{
	int PID;
	int ActiveWindowId = 0;
	int WindowWithFocusId = 0;
	void *P;
	void *T;
	
	//
	// @todo: Usar essa rotina para fazer testes de modo texto.
	//
	
	//Constructor.
	shellShell(); 


	// ...Testing strings on Client Area 
    printf("shellInit: Running tests ...\n");		
	
	//
	// @todo: Essa mensagem está aparecendo fora da área de trabalho do shell
	//        pois ainda não temos um ponteiro para a memória que representa essa área.
	//        Talvez as mensagens devessem ir para um buffer de linha antes de irem 
	//        para a memória de vídeo.
	//
	
	//
	// @todo: O que tevemos fazer aqui é pegar informações sobre o processo Shell
	//        e colocálas na tela.
	//
	
	//
	// @todo: Criar na API uma rotina de inteface que use essa chamada.
	// ex: APIGetPID().
	//
	
	//PID = (int) APIGetPID();
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	
	//valor de erro
	if( PID == (-1)){
	    printf("ERROR getting PID\n");	
	}
    printf("Starting Shell... PID={%d} \n", PID);
	
	printf("ScreenWidth={%d}  \n",shellMaxColumns);
	printf("ScreenHeight={%d} \n",shellMaxRows);
	
	//
	//Active
	ActiveWindowId = (int) APIGetActiveWindow();
	
	//valor de erro
	if( ActiveWindowId == (-1)){
	    printf("ERROR getting Active window ID\n");	
	}	
	printf("ActiveWindowId={%d}\n",ActiveWindowId);


	//
	// Focus.
	WindowWithFocusId = (int) APIGetFocus();
	
	//valor de erro
	if( WindowWithFocusId == (-1)){
	    printf("ERROR getting Window With Focus ID\n");	
	}	
	printf("WindowWithFocusId={%d}\n",WindowWithFocusId);
	
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
	// Obs: As threads criadas aqui etão sendo atribuídas ao processo PID=0.
	//      @todo: No kernel, quando criar uma thread ela deve ser atribuída
    //      ao processo que chamou a rotina de criação.	
	//
	printf("Creating threads...\n");
	apiCreateThread((unsigned long)&shellThread, 1,"TestShellThread1");
	apiCreateThread((unsigned long)&shellThread, 1,"TestShellThread2");
	apiCreateThread((unsigned long)&shellThread, 1,"TestShellThread3");
	apiCreateThread((unsigned long)&shellThread, 1,"TestShellThread4");
	//...
	
	//printf("Initializing a thread...\n");
	//...
	
	//Testando bibliotecas.
	printf("Testing libraries:\n");	
	
	//stdio.h
	printf("Testing stdio:\n");
	//app_clear(0);  //Não fez nada.
    //...

	//stdlib.h
	printf("Testing stdlib:\n");
	
	//Testando inicializar a rt do stdio para usar alocação dinâmica.
	libcInitRT(); //(@todo: isso pode ir para shellInit)
	
	//Obs: Sempre inicia com o mesmo número.
	int rand_value;
	rand_value = (int) rand();
	printf("RandValue1={%d}\n", rand_value);
	rand_value = (int) rand();
	printf("RandValue2={%d}\n", rand_value);
    rand_value = (int) rand();
	printf("RandValue3={%d}\n", rand_value);
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
	// Window test.
	//
	
	int w;
	
	w = (int) APIGetActiveWindow();
	//valor de erro
	if( w == (-1)){
	    printf("ERROR getting Active window ID\n");	
	}
	printf("ActiveWindow={%d}\n", w);
	
	w = (int) APIGetFocus();	
	//valor de erro
	if( WindowWithFocusId == (-1)){
	    printf("ERROR getting Window With Focus ID\n");	
	}		
	printf("Focus={%d}\n", w);
	//...
	
	//
	// Testing commands.
	//

	//Lib C.
	system("test");       //libC. (stdlib.c)
	system("ls");
	system("start");
	system("xxfailxx");
	//...
	
	//API.
	apiSystem("test");    //api.
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
	

	
done:
    //
	// Testing welcome message.
	//
	
	printf("...\n");
	test_operators();
	
	printf("...\n");
	printf("Welcome to Gramado Operating System.\n");
	//printf("...\n");
	//printf("TAKE A SAD O.S. AND MAKE IT BETTER!\n");
	//printf("...\n");
	//printf("Done!");
	
	//
	// *Testando carregar um arquivo.
	// Ok, isso funcionou.
	//
	
	int fRet;
	printf("...\n");
	printf("Testing ... Loading file...\n");
	
	/*A QUESTÃO DO TAMANHO PODE SER UM PROBLEMAS #BUGBUG ;... SUAJNDO ALGUMA ÁREA DO SHELL*/
	fRet = (int) system_call( SYSTEMCALL_READ_FILE, 
	                          (unsigned long) init_file_name, 
					          (unsigned long) &shell_buffer[0], 
							  (unsigned long) &shell_buffer[0] );
							  
	printf("ret={%d}\n",fRet);
	
	printf("...\n");
	printf(&shell_buffer[0]);	
	
	
 
  //system_call( , , , );
	
	
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
 * Temos que atualizar o cursor da janela com foco de entrada se quizermos escrever corretamente dentro dela.
 * e isso se faz através de uma chamada ao kernel.
 */
void shellSetCursor(unsigned long x, unsigned long y)
{
	//
	// #BUGBUG: Aconteceu uma pagefault depois de incluir essa função. 
	// Vou testar sem ela.
	//
	
    //Atualizamos as variáveis dentro da estrutura da janela com o foco de entrada.
    //system_call( SYSTEMCALL_SETCURSOR, x, y, 0);	
	

//Atualizando as variáveis globais usadas somente aqui no shell.
setGlobals:	
    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;	
	return;
};


/*
 * shellThread:
 *     Um thread dentro para testes.
 */
void shellThread(){
	printf("Shell: This is a thread for test!");
	refresh_screen();
	while(1){}
};


/*
 * @todo: Criar rotina de saída do shell.
void shellExit(int code);
void shellExit(int code){
	exit(code);
}
*/

//help message
void shellHelp(){
    printf(help_banner);	
	return;
}

/*
 * shellPrompt:
 *     Inicializa o prompt.
 */
void shellPrompt()
{	
	int i;
	for(i=0; i<PROMPT_MAX_DEFAULT;i++){
		prompt[i] = (char) '\0';
	}
	
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_status = 0;

    printf("\n");	
	//printf("\n %s", ++ user name  ++);
	printf(SHELL_PROMPT);
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
}
/*
void die(char * str);
void die(char * str)
{
	fprintf(stderr,"%s\n",str);
	exit(1);
}
*/


//
// End.
//

