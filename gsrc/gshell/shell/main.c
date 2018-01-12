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
#include "globals.h"


//
// Variáveis internas.
//

int shellStatus;
int shellError;


//
// Protótipos para funções internas.
//


unsigned long shellProcedure( struct window_d *window, 
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
	
	
	struct window_d *hWindow;        //janela do aplicativo.

	
	//struct message_d *m;

	
	int Status = 0;
	int ShellFlag = 0;
	char *s;    //String	

	//...
	
	
	
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
	
	//@todo:
	//Criar essas funções na API.
	//unsigned long ScreenWidth = (unsigned long) APIGetScreenWidth();
	//unsigned long ScreenHeight = (unsigned long) APIGetScreenheight();
	
	
	apiBeginPaint();
	
	//hWindow = (void*) APICreateWindow( WT_EDITBOX, 1, 1," {} SHELL.BIN ",
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1," {} SHELL.BIN ",
	                                   shell_window_x, shell_window_y, shellWindowWidth, shellWindowHeight,    
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
	
	

	
	//
	// ** criando a top bar.
	//
	
	//#bug bug
	//enterCriticalSection();    // * Enter Critical Section.
	shellCreateTopBar();
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
	//*IMPORTANTE: É FUNDAMENTAL SETAR O FOCO, POIS O KERNEL DEPENDE DELE
	//PARA RETORNAR A MENSAGEM DA JANELA COM O FOCO DE ENTRADA.
    APISetFocus(hWindow);
	
	//definindo a janela como sendo uma janela de terminal.
	//isso faz com que as digitações tenham acesso ao procedimento de janela de terminal 
	//para essa janela e não apenas ao procedimento de janela do sistema.
	system_call( SYSTEMCALL_SETTERMINALWINDOW, (unsigned long) hWindow, (unsigned long) hWindow, (unsigned long) hWindow);
		
	
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

        //
        // + PEGAMOS A MENSAGEM NA FILA DA JANELA COM O FOCO DE ENTRADA.
        //   ?? COMO DECIDIREMOS QUAL JANELA SERÁ AFETADA PELO PROCEDIMENTO 
        //	    QUE CHAMAREMOS AGORA ??
        //		
		
		// Send Message to procedure.
		if( (int) msgTest != 0)
		{
            //
            // *IMPORTANTE:
			//  SE TEMOS UM HANDLE DE JANELA, SIGNIFICA QUE O PROCEDIMENTO PODE 
			//  AFETAR MAIS DE UMA JANELA. PORTANTO JANELAS FILHAS OU ATE MESMO JANELAS 
			//  CRIADAS PELO SISTEMA PODERÃO SER AFETADAS POR ESSE PROCEDIMENTO??
			//  @TODO: PASSAR O HANDLE DE JANELA PARA O PROCEDIMENTO.
            //			
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
	
    switch(msg)
    { 
		case MSG_KEYDOWN:
            switch(long1)
            {
				//Null key
				case 0:
				    return 0;
					//#BUGBUG esse null aqui dava problemas na digitação.
					//printf(" null ");
				    break;
				
				//reset prompt.
				case '8':
				    shellPrompt();
				    goto done;
					break;
				    
				//test return
				case '9':
				case VK_RETURN:
				    input('\0'); //finaliza a string.
					shellCompare(window);
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
				    input( (unsigned long) long1);      //Coloca no stdin
                    shellInsertNextChar((char) long1);  //Coloca no stdout
					//printf("%c", (char) long1); 					
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
          
		//
        //  *** Aqui o procedimento de janelas do kernel vai enviar uma mensagem notificando 
		//      que os botões de controle F1 ou F2 foram apertados ... 
		//      F1 significa que temos que abri o menu de aplicativos e F2 significa que temos 
		//     que abrir a janela do interpretador de comando ...
        //		
		  
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
		//case MSG_CLOSE:
		    //??
		    //isso deve fechar qualquer janela que esteja usando esse procedimento.
			//pode ser uma janela filha ou ainda uma janela de dialogo criada pelo sistema.
			//??
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
		//refresh_screen(); //Obs: #bugbug perceba que o procedimento de janela do sistema também tem um refresh screen.
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
 *
 */
 
#define LSH_TOK_DELIM " \t\r\n\a" 
 
unsigned long shellCompare(struct window_d *window)
{
    unsigned long ret_value;
	
	//
	// ?? E se tivermos várias palavras na linha de comando ??
	//
		
    // Returns first token 
    //char *token = strtok(prompt, " -");
	
	
    printf("shellCompare: Testing ...\n");
    refresh_screen();	
   
    char *tokenList[80];
    int i = 0;
   
    tokenList[0] = strtok( prompt, LSH_TOK_DELIM);    // first call returns pointer
                                         // to first part of user_input
	                                     // separated by delim  
	char *token;
	
	token = (char *) tokenList[0];
	
	i=0;                                  
    while( token != NULL )
	{

        //coloca na lista
        tokenList[i] = token;

		//#debug
		//Mostra
        printf("shellCompare: %s \n",tokenList[i]);
        refresh_screen();

		//incrementa o índice da lista
        i++;
		
		token = strtok(NULL, LSH_TOK_DELIM);
    }; 

	//Temos que finalizar a lista ??!!
    tokenList[i] = NULL;

    printf("shellCompare: %s \n",tokenList[i]);
    refresh_screen();	

    printf("shellCompare: Test done!\n");
    refresh_screen();		
   
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

    //L1 RAM /objetcs   (diretório raiz para os arquivos que são diretórios de objetos)
	//os objetos serão listador em um arquivo que nunca será salvo no disco.
	if( strncmp( prompt, "/objects", 6 ) == 0 ){
	    printf("Open object manager root dir ...\n");
        goto exit_cmp;
    };

	//L2 disk  /diretório raiz do sistema de arquivos
	if( strncmp( prompt, "/", 5 ) == 0 ){
	    printf("Open file system root dir ...\n");
        goto exit_cmp;
    };

	//L3 LAN  // acesso a arquivos da lan
	//os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	if( strncmp( prompt, "/lan", 6 ) == 0 ){
	    printf("Open lan root dir ...\n");
        goto exit_cmp;
    };
 
	//L4 WAN   //acesso a arquivos da wan
	//os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	if( strncmp( prompt, "/wan", 6 ) == 0 ){
	    printf("Open wan root dir ...\n");
        goto exit_cmp;
    };
	
    //
	// ordem alfabética.
	//
	
	
	//boot - ?? boot info ??
	if( strncmp( prompt, "boot", 4 ) == 0 )
	{
	    printf("~boot\n");
		//boot();
        goto exit_cmp;
    };

	

    //cls
	if( strncmp( prompt, "cls", 3 ) == 0 )
	{
        shellClearscreen();
        shellSetCursor(0,0);
	    shellPrompt();
        goto exit_cmp;
	};
	
	//dir
	if( strncmp( prompt, "dir", 3 ) == 0 )
	{
	    printf("~dir\n");
		//fs_show_dir(0); 
        goto exit_cmp;
    };
	
	//echo
    if( strncmp( prompt, "echo", 4 ) == 0 ){
		printf("~echo\n");
		goto exit_cmp;
    };	
	
	//exit
    if( strncmp( prompt, "exit", 4 ) == 0 ){
        printf("~exit\n");
		exit(0);
		goto exit_cmp;
    };

	//hd ??
    if( strncmp( prompt, "hd", 2 ) == 0 )
	{
	    printf("~hd\n");
        goto exit_cmp;
    };
	
	//help
    if( strncmp( prompt, "help", 4 ) == 0 ){
		shellHelp();
		goto exit_cmp;
    };	
	
	//install	
	//muda um arquivo da area de transferencia para 
	//o sistema de arquivos...
	if( strncmp( prompt, "install", 7 ) == 0 )
	{
	    printf("~install\n");
		//fs_install();
        goto exit_cmp;
    };
	
    //ls
	if( strncmp( prompt, "ls", 2 ) == 0 )
	{
        goto exit_cmp;
	};	


    //metrics
	if( strncmp( prompt, "metrics", 7 ) == 0 ){
		shellShowMetrics();
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

    //mbr
    if( strncmp( prompt, "mbr", 3 ) == 0 )
	{
	    printf("~mbr\n");
		//#bugbug pagefault
		shellTestMBR();
		printf("done\n");
		goto exit_cmp;
    }; 

    //reboot 	  	
    if( strncmp( prompt, "reboot", 6 ) == 0 )
	{
	    printf("~reboot\n");
		//reboot();
        //KiReboot();
		goto exit_cmp;
    };
	
    //root
    if( strncmp( prompt, "root", 4 ) == 0 )
	{
	    printf("~/root\n");
		//testa_root();
		goto exit_cmp;
    }; 

    //save
	if( strncmp( prompt, "save", 4 ) == 0 )
	{
	    printf("~save root\n");
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
	
	//start
    if( strncmp( prompt, "start", 5 ) == 0 )
	{
		//Isso deve setar o foco na janela do shell.
		//ao mesmo tempo que reinicia o input para digitação 
		//e ajusta as margens do cursor. :)
		//qualquer editbox precisa desse tipo de ajuste.
	    
		APISetFocus(window);
		shellPrompt();
		printf("~start\n");
		goto exit_cmp;
    }; 
	
	
    //t1 - Test file
	if( strncmp( prompt, "t1", 2 ) == 0 ){
		
		//carrega e exibe um arquivo.
		shellTestLoadFile();
		
		//escreve no buffer de saida e mostra o buffer de saida.
		shell_buffer[0] = (char) 'F';
        shell_buffer[1] = (char) 'N';	
        shell_buffer[2] = (char) '\0';			
		printf( (const char *) stdout->_base );
		
		printf("%s \n",stdout->_base);
		printf("%s \n",stdout->_tmpfname);
		printf("%d \n",stdout->_cnt);
		printf("%d \n",stdout->_bufsiz);
		printf("done \n");
		
        goto exit_cmp;
    };
	
	//t2 - test bmp
	if( strncmp( prompt, "t2", 2 ) == 0 ){
		shellTestDisplayBMP();
        goto exit_cmp;
    };	
	
	//t3 - test thread
	if( strncmp( prompt, "t3", 2 ) == 0 ){
	    shellTestThreads();
        goto exit_cmp;
    };
	
	//topbar
    if( strncmp( prompt, "topbar", 6 ) == 0 ){
	    enterCriticalSection();    
	    shellCreateTopBar();
	    exitCriticalSection();    
		goto exit_cmp;
    };			
	
		
	//tree
    if( strncmp( prompt, "tree", 4 ) == 0 ){
		shellTree();
		goto exit_cmp;
    };			
		
	//version
    if( strncmp( prompt, "version", 7 ) == 0 ){
	    printf("\n Gramado version %s \n",OS_VERSION);
        goto exit_cmp;
    };	
 
 
//
// Se apertamos o enter e não encontramos um comando válido
// então damops um aviso de comando inválido e reiniciamos o prompt 
// na próxima linha.
//
 
palavra_nao_reservada:
    printf(" Unknown command!\n");
	shellPrompt();
	//Mostrando as strings da rotina de comparação.
	refresh_screen(); 	
	return (unsigned long) 1;
	
exit_cmp:
	//Mostrando as strings da rotina de comparação.
	shellPrompt();
	refresh_screen(); 
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
	
	//window position
	//shell_window_x = DEFAULT_WINDOW_X;
	//shell_window_y = DEFAULT_WINDOW_Y;
	shell_window_x = (800/2);
	shell_window_y = (600/8);

	
	//screen sizes
	shellScreenWidth  = (800/2);
    shellScreenHeight = (600 - (600/8) );//600;
	
	//window height
	//shellWindowWidth = (DEFAULT_MAX_COLUMNS*8);
    //shellWindowHeight = (DEFAULT_MAX_ROWS*8);
	
	shellWindowWidth = (800/2);
	shellWindowHeight = (600 - (600/8) );
	
    shellMaxColumns = DEFAULT_MAX_COLUMNS; //80;
    shellMaxRows    = DEFAULT_MAX_ROWS; //25;

    //...	

	//
	// Setup buffers.
	//
	
    // reiniciando as variáveis na estrutura do output
	stdout->_base = &shell_buffer[0];
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
	
	//Número máximo de colunas e linhas.
	g_columns = shellMaxColumns; //80;
	g_rows = shellMaxRows;       //25;
    //...
	
	
	//...
	
done:	
    //Nossa referência é amoldura e não a área de cliente.
	//@todo:usar a área de cliente como referência
	//shellSetCursor(0,0);
    shellSetCursor(0,4);	
	shellPrompt();
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
int shellInit( struct window_d *window )
{
	int PID;
	int PPID;
	int ActiveWindowId = 0;
	int WindowWithFocusId = 0;
	void *P;

	
	APISetFocus( window );
	shellSetCursor(0,4);
	shellPrompt();
    
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
	if( PID == (-1)){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
	if( PPID == (-1)){
	    printf("ERROR getting PPID\n");	
	}
  
	printf("Starting SHELL.BIN ... PID={%d} PPID={%d} \n",PID ,PPID);
	
	printf("shellMaxColumns={%d} \n",shellMaxColumns);
	printf("shellMaxRows={%d} \n",shellMaxRows);
	
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
	
	int wID;
	
	wID = (int) APIGetActiveWindow();
	//valor de erro
	if( wID == (-1) ){
	    printf("ERROR getting Active window ID\n");	
	}
	printf("ActiveWindow={%d}\n", wID);
	
	wID = (int) APIGetFocus();	
	//valor de erro
	if( wID == (-1) ){
	    printf("ERROR getting Window With Focus ID\n");	
	}		
	printf("Focus={%d}\n", wID);
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
	
	/*
	printf("...\n");
	test_operators();
	*/
	
	printf("...\n");
	printf("Welcome to Gramado Operating System.\n");
	//printf("...\n");
	//printf("TAKE A SAD O.S. AND MAKE IT BETTER!\n");
	//printf("...\n");
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
	
	printf("heapStart{%x} heapEnd{%x} heapPointer{%x} heapAvailable={%x}\n",hStart, hEnd, hPointer, hAvail);
	
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
	
	/*
	printf("\nO melhor grupo do Facebook: \n");
	printf(">> https://www.facebook.com/groups/1078308252227836 \n");
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
 * Temos que atualizar o cursor da janela com foco de entrada se quizermos escrever corretamente dentro dela.
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
 * shellThread:
 *     Um thread dentro para testes.
 */
void shellThread()
{
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
}

//drawing a tree
void shellTree(){
    printf(tree_banner);	
	return;
}

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
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicialização de stdio, prompt foi definido como stdin->_base.
 */
void shellPrompt()
{	
	int i;
	for(i=0; i<PROMPT_MAX_DEFAULT;i++){
		prompt[i] = (char) '\0';
	};
	
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_status = 0;
	prompt_max = 250;  //??	PROMPT_MAX_DEFAULT

    printf("\n");	
	//printf("\n %s", ++ user name  ++);
	printf(SHELL_PROMPT);
	return;
};


/*
 * shellClearBuffer:
 *     Limpa o buffer do shell.
 */
void shellClearBuffer()
{
	int i;
	
	// Shell buffer.
	for( i=0; i<SHELL_BUFFER_SIZE; i++){
		shell_buffer[i] = 0;
	}
	shell_buffer[0] = (char) '\0';
    shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};


/*
 * shellTestLoadFile:
 *     Carrega um arquivo de texto no buffer e mostra na tela.
 */
void shellTestLoadFile()
{
	shellClearBuffer();
	shellClearscreen();
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
					          (unsigned long) &shell_buffer[0], 
							  (unsigned long) &shell_buffer[0] );
							  
	printf("ret={%d}\n",fRet);
	
	printf("...\n\n");
	printf(&shell_buffer[0]);		
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
	ThreadTest1 = (void*) apiCreateThread((unsigned long)&shellThread, (unsigned long) threadstack1,"ThreadTest1");
	
	
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
 * shellClearscreen:
 *     Limpar a tela do shell.
 */
void shellClearscreen()
{
	int i;
	
	shellSetCursor(0,0);
	
	// Shell buffer. (80*25) ??
	for( i=0; i<SHELL_BUFFER_SIZE; i++){
		printf("%c", ' '); //pinta um espaço.
	}
	shellSetCursor(0,0);
};


/*
 * shellRefreshScreen:
 *     Copia o conteúdo do buffer para a tela. (dentro da janela).
 *
 */
void shellRefreshScreen()
{
	int i;

	//cursor apontando par ao início da janela.
	shellSetCursor(0,0);
	
	// Shell buffer.
	for( i=0; i<SHELL_BUFFER_SIZE; i++){
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
    int end = (SHELL_BUFFER_SIZE+80);
	
	//cursor apontando par ao início da janela.
	shellSetCursor(0,0);
	
	// Shell buffer.
	for( i=80; i<end; i++){
		printf("%c", stdout->_ptr[i]);
	};
	
    //shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.		
};



static void save_cur(void)
{
	saved_x = shell_buffer_x;
	saved_y = shell_buffer_y;
};


static void restore_cur(void)
{
	x=saved_x;
	y=saved_y;
	//pos = origin + ( (y * columns + x) << 1 );
	shell_buffer_pos = origin + (shell_buffer_y * columns + shell_buffer_x);
};


static void lf(void)
{
	if (shell_buffer_y+1 < bottom) {
		shell_buffer_y++;
		shell_buffer_pos += columns;  //pos += columns<<1;
		return;
	}
	//scrup();
};


static void ri(void)
{
	if (shell_buffer_y>top) {
		shell_buffer_y--;
		shell_buffer_pos -= columns; //shell_buffer_pos -= columns<<1;
		return;
	}
	//scrdown();
};


static void cr(void)
{
	shell_buffer_pos -= shell_buffer_x; //pos -= x<<1;
	shell_buffer_x=0;
};


static void del(void)
{
	if (shell_buffer_x) {
		shell_buffer_pos -= 2;
		shell_buffer_x--;
		//*(unsigned short *) shell_buffer_pos = 0x0720;
		//@todo: printchar
	}
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

	shell_buffer[offset] = (char) c;
};


//insere um caractere entro do buffer
void shellInsertCharPos(unsigned long offset, char c)
{
	unsigned long offsetMax = (unsigned long)(80*25); 
		
	if(offset >= offsetMax){
		return;
	}
	
	shell_buffer[offset] = (char) c;
};


//coloca um char na próxima posição do buffer
void shellInsertNextChar(char c)
{
	shell_buffer[shell_buffer_pos] = (char) c;	
};


void shellInsertCR()
{
   shell_buffer[shell_buffer_pos] = (char) '\r';	
};


void shellInsertLF()
{
    shell_buffer[shell_buffer_pos] = (char) '\n';	
};


void shellInsertNullTerminator()
{
    shell_buffer[shell_buffer_pos] = (char) '\0';	
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
	
	//read sector
	system_call( SYSTEMCALL_READ_LBA, 
	             (unsigned long) &buffer[0],  //address 
				 (unsigned long) 0,           //lba
				 (unsigned long) 0);
				 
    shellRefreshScreen();	
	exitCriticalSection();   
}




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
	
	shell_buffer_x = x;
	shell_buffer_y = y;
	return;
};



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

	screen_width = apiGetSystemMetrics(1);
	screen_height = apiGetSystemMetrics(2);
	cursor_width = apiGetSystemMetrics(3);
	cursor_height = apiGetSystemMetrics(4);
	mouse_pointer_width = apiGetSystemMetrics(5);
	mouse_pointer_height = apiGetSystemMetrics(6);
	char_width = apiGetSystemMetrics(7);
	char_height = apiGetSystemMetrics(8);
	//...
	
	
	printf("shellShowMetrics:\n");
	printf("screenWidth={%d} screenHeight={%d}\n",screen_width,screen_height);
	printf("cursorWidth={%d} cursorHeight={%d}\n",cursor_width,cursor_height);
	printf("mousepointerWidth={%d} mousepointerHeight={%d}\n",mouse_pointer_width,mouse_pointer_height);
	printf("charWidth={%d} charHeight={%d}\n",char_width,char_height);	
	//...
	
printf("done\n");	
	return;
}


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



