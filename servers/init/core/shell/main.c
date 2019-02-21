/*
 * File: main.c 
 *
 * Essa é uma versão do shell apenas par ao kernel norax,
 * deve ser full screens sem frames. Só o suficiente para digitar
 * linhas de comando.
 *
 * Gramado Core Shell.
 * A shell to run only on Gramado Core environment. 
 *
 * GWM - Gramado Window Manager.
 * deve se comunicar com o GWS, Gramado Window Server. /gramado
 * General purpose application.
 *
 * #importante 
 * Observar o conceito de fluxo padrão e o fato de printf enviar conteúdo 
 * para o buffer stdout. Depois é só imprimir o que está em stdout.
 * Talvez isso implique em midanças na libc pra ficar parecido com a 
 * implementação UNIX de output. E o refresh do buffer de saída?
 * O lado bom é que o buffer de saída poderá ser usado no PIPE.
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

//# usado para teste 
//divisível por 4 é mais lento.

#define WINDOW_WIDTH     800    //750 
#define WINDOW_HEIGHT    600    //400
#define WINDOW_LEFT      0      //10
#define WINDOW_TOP       0      //10

 
#include "shell.h" 


// Input flags.
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

 //para ficar igual a do Nelson;

struct shell_command {
	
    char *name;
    void *fun;
    char *help;
	
};

//extern struct command cmd_table[];
struct shell_command cmd_table[];

struct command cmd_table[] = {
    {"?",           cmd_help,           "This help"                                     },
    {"cd",          cmd_cd,             "Change current directory"                      },
    {"cls",         cmd_cls,            "Clear screen"                                  },
    {"copy",        cmd_copy,           "Copy file or directory"                        },
    {"date",        cmd_date,           "Date"                                          },
    {"del",         cmd_del,            "Delete file or directory"                      },
    {"dir",         cmd_dir,            "List directory"                                },
    {"echo",        cmd_echo,           "This ---"                                      },
    {"exit",        cmd_exit,           "Exit shell"                                    },
    {"help",        cmd_help,           "This help"                                     },
    {"mov",         cmd_mov,            "Move file or directory"                        },
    {"new",         cmd_new,            "New file or directory"                         },
    {"reboot",      cmd_reboot,         "Reboot system"                                 },
    {"rename",      cmd_rename,         "Rename file or directory"                      },
    {"shutdown",    cmd_shutdown,       "Shutdown your computer locally or remotely"    },
    {"time",        cmd_time,           "Time"                                          },
    {"version",     cmd_version,        "Shell version"                                 },
};

*/

 
 

//#define MIN(x,y) ((x < y) ? x : y)

int ShellFlag = 0;


//O shell está rodadndo.
int running = 1;

/* Non-zero when we are executing a top-level command. */
//o shell está executando um comando que 
//está emprimeiro plando.
int executing = 0;

int login_status = 0;

// #todo: 
// Nesse modo o servidor shell.bin não abrirá janelas,
// apanas inicializará os recursos do gws.

int headless;

//Sendo assim, o shell poderia abrir no ambiente de logon.

char username[11];
char password[11];
//char sUsername[11];
//char sPassword[11];
//char *username;
//char *password; 

//#define DEFAULT_WINDOW_TITLE "Shell"
	

#ifndef PPROMPT
#define PPROMPT "shell\\$ "
#endif
char *primary_prompt = PPROMPT;

#ifndef SPROMPT
#define SPROMPT "shell> "
#endif
char *secondary_prompt = SPROMPT;



COMMAND *global_command = (COMMAND *) NULL;


/* Non-zero after SIGINT. */
int interrupt_state = 0;

/* The current user's name. */
char *current_user_name = (char *) NULL;

/* The current host's name. */
char *current_host_name = (char *) NULL;




/* Non-zero means that this shell is a login shell.
   Specifically:
   0 = not login shell.
   1 = login shell from getty (or equivalent fake out)
  -1 = login shell from "-login" flag.
  -2 = both from getty, and from flag.
 */
//Se o shell vai ser usado para login.
//Obs: Uma variável no kernel guardo o id do processo 
//que fez login. 
int login_shell = 0;

/* Non-zero means this shell is running interactively. */
//Se for diferente de zero então esse shell é interativo.
//Se for zero ele pode apenas estar executando um script.
int interactive = 0;


/* Non-zero means to remember lines typed to the shell on the history
   list.  This is different than the user-controlled behaviour; this
   becomes zero when we read lines from a file, for example. */
int remember_on_history = 1;


/* Non-zero means this shell is restricted. */
int restricted = 0;

/* Special debugging helper. */
int debugging_login_shell = 0;


/* The environment that the shell passes to other commands. */
//O ambiente que o shell passa para 
//o comando que ele executou.
char **shell_environment;


/* The number of commands executed so far. */
int current_command_number = 1;


/* Non-zero is the recursion depth for commands. */
int indirection_level = 0;


/* The number of times BASH has been executed.  This is set
   by initialize_variables () in variables.c. */
int shell_level = 0;



/* The name of this shell, as taken from argv[2]. */
char *shell_name;

char *dist_version;
char *build_version; /*revision*/


/* The name of the .(shell)rc file. */
char *bashrc_file = "~/.bashrc";

/*nome do arquivo de configuração*/
char *shell_config_file = "./shellcnf.txt";


/* Non-zero means to act more like the Bourne shell on startup. */
int act_like_sh = 0;



/* Values for the long-winded argument names. */
int debugging = 0;		/* Do debugging things. */
int no_rc = 0;			/* Don't execute ~/.bashrc */
int no_profile = 0;		/* Don't execute .profile */
int do_version = 0;		/* Display interesting version info. */
/* Be quiet when starting up. */
//inicialização silenciosa. Suprime alguns verboses.
int quiet = 0;	
int make_login_shell = 0;	/* Make this shell be a `-bash' shell. */
int no_line_editing = 0;	/* Don't do fancy line editing. */
int no_brace_expansion = 0;	/* Non-zero means no foo{a,b} -> fooa fooa. */



//
// ## timer ##
//

int objectX;
int objectY;
int deltaX;
int deltaY;
//int deltaValue = 4;
int deltaValue = 1;

//usdo para testar o timer.
void updateObject ()
{
   //RECT rc;
   //GetClientRect(hwnd, &rc);

   objectX += deltaX;
   objectY += deltaY;

   if ( objectX < 2 )
   {
      objectX = 2;
      deltaX = deltaValue;
   }
   else if ( objectX > 78 ) {
	   
      objectX = 78; 
      deltaX = -deltaValue;  //muda a direção.
   }
   
   
   if (objectY < 2){
      objectY = 2;
      deltaY = deltaValue;
   }
   else if ( objectY > 24 ){
      objectY = 24; 
      deltaY = -deltaValue;
   }

    
	//
	// ## test ##
	//
	
	//update.
	//textCurrentRow = objectX;
    //textCurrentCol = objectY;
   
    //putchar.
	//shellInsertNextChar ( (char) 'T' );  
	
	shellSetCursor ( objectX, objectY );	
	
	printf("%c",(char) 'X');
	
};

/*
struct {
	
  char *word;
  int token;
  
} token_word_alist[] = {
  {"if", IF},
  {"then", THEN},
  {"else", ELSE},
  {"elif", ELIF},
  {"fi", FI},
  {"case", CASE},
  {"esac", ESAC},
  {"for", FOR},
  {"while", WHILE},
  {"until", UNTIL},
  {"do", DO},
  {"done", DONE},
  {"in", IN},
  {"function", FUNCTION},
  {"{", '{'},
  {"}", '}'},
  { (char *) NULL, 0 }
};
*/

//
// ## Arguments support ##
//

// ??
//é semelhante à estrutura acima.
/* Some long-winded argument names.  These are obviously new. */
// Argumentos.
#define Int 1
#define Charp 2
struct 
{
    char *name;
    int *value;
    int type;
	
} long_args[] = {
	
    { 
        "debug", 
        &debugging, 
		Int 
	},
    
	{ 
	    "norc", 
		&no_rc, 
		Int 
	},
	
    { 
	    "noprofile", 
		&no_profile, 
		Int 
	},
	
    { 
	    "rcfile", 
		(int *) &bashrc_file, 
		Charp
	},
	
    { 
	    "version", 
		&do_version, 
		Int
	},
	
    { 
	    "quiet", 
		&quiet, 
		Int
	},
	
    { 
	    "login", 
		&make_login_shell, 
		Int
	},
    
	{ 
	    "nolineediting", 
		&no_line_editing, 
		Int
	},
	
    { 
	    "nobraceexpansion", 
		&no_brace_expansion, 
		Int
	},
	
    { 
	    (char *) NULL, 
		(int *) 0x0, 
		0 
	}
  
};



int shellStatus;
int shellError;


//... 

/*
//argument buffer
char **argbuf;
int argbuf_length;
int argbuf_index;
*/


// Protótipos
void die (char * str);
void error( char *msg, char *arg1, char *arg2 );
void fatal( char *msg, char *arg1, char *arg2 );

//isso foi para stdlib.c
//void *xmalloc( int size);

char *concat( char *s1, char *s2, char *s3 );
char *save_string ( char *s, int len );

int shell_save_file ();
int save_string2 ( char string[], char file_name[] );

void shellInitSystemMetrics();
void shellInitWindowLimits();
void shellInitWindowSizes();
void shellInitWindowPosition();

//
// testes de scroll.
//
void testScrollChar();

//row support
void textSetTopRow ( int number );
void textSetBottomRow ( int number );
int textGetTopRow ();
int textGetBottomRow ();


void clearLine ( int line_number );


void testShowLines();
void testChangeVisibleArea();
void updateVisibleArea( int direction );


void shellRefreshVisibleArea();

void shellSocketTest();

//
// Internas.
//

static inline void pause (void){
	
    asm volatile ("pause" ::: "memory"); 
}; 


/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static inline void rep_nop (void){
	
    __asm__ __volatile__ ("rep;nop": : :"memory");
};


#define cpu_relax()  rep_nop()


//
// Protótipos para funções internas.
//

// Procedimento de janela principal do aplicativo.
unsigned long 
shellProcedure ( struct window_d *window, 
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
shellTopbarProcedure ( struct window_d *window, 
                       int msg, 
			           unsigned long long1, 
					   unsigned long long2 );
					  
 
void quit ( int status ){
	
	running = 0;
}
 
 
/*
 **************
 * shmain: 
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
 *    +Testar as chamadas para pegar informções sobre o processo.
 *    +...
 *
 *  
 *  ## O SHELL É UM APLICATIVO DO TIPO JANELA, DEVE TER UM MAIN 
 *     DO TIPO JANELA ##
 *
 * Obs: Esses argumentos podem ser um padrão.
 */
 
int main ( int argc, char *argv[] ){
	
	//int arg_index = 1;
	
    FILE *default_input = stdin;
    char *local_pending_command = (char *) NULL;	
	
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

	//JANELA CRIADA NA ÁREA DE CLIENTE DA JANELA PRINCIPAL.
    struct window_d *hWindow2;       
	
	//struct message_d *m;

	
	int Status = 0;
	//char *s;    //String	
	
	
	
    /* Wait forever if we are debugging a login shell. */
    //while(debugging_login_shell);	

	
    //if(shell_initialized)
    //{
        //reinitialize();
    //};
	
	
    //shell_environment = env;
    //shell_name = argv[0];
	
	//
	// ## ARGS ##
	//
	
	//
	// ## Command Switch ##
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
	if (argc < 1)
	{
		//printf("No args !\n");
		//#Test.
        //fprintf( stderr,"Starting Shell with no arguments...\n");	 	
		die("No args");
		
		goto noArgs; 
	}else{
		
		//argv[0] = Tipo de shell: interativo ou não
		//argv[1] = Tipo de uso: login ... outros ?? 
		
		//printf("Testing args ...\n");
		
		//#todo: (possibilidades)
		//As flags poderia começar com f. Ex: fInteractive, fLoginShell,
		
	    if ( strncmp ( (char *) argv[0], "-interactive", 12 ) == 0 ){
			
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
		
	    if ( strncmp ( (char *) argv[1], "-login", 6 ) == 0 ){
			
			login_shell = 1;
			
			//printf("Initializing login ...\n");
            //printf("arg[1]={%s}\n",argv[1]);    
        };	
		
		//#headless
		//aqui o shell não criará janelas, apenas inicializará o gws.
		
		if ( strncmp ( (char *) argv[1], "--headless", 10 ) == 0 ){
			
			headless = 1;
			
		}
		
		
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
	
	
	// Isso configura alguns padrões do aplicativo.
	// Os argumentos tratados abaixo podem modificar esses padrões
	// Ex: Um argumento de entrada pode solicitar a troca de cor de fonte.
	
	shellShell (); 	
	
	//Apenas inicialize. Continuaremos com o procedimento 
	//do shell e não o da barra,	
	
    
//again:	
	enterCriticalSection ();    
    hWindow = shellCreateMainWindow (1);
	exitCriticalSection ();
	//goto again;
	
	//#bugbug
	//falha quando chamamos a rotina de pintura da janela.
		
	//
	// @todo: Usar essa rotina para fazer testes de modo gráfico.
	//	
	
	//Debug:
	//while(1){};
	
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
	// ...
	
	
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
		
	
    // Não é necessário passar todos os argumentos de uma vez só.
	// Podemos realizar 3 ou 4 chamadas para construírmos a janela.
	// Essa rotina tem 12 argumentos mas ela poderá realizar 3 chamadas
	// ao sistema para passar todos os argumentos.
	
	
	// *Importante:
	//      A janela do shell será uma aba dentro da janela do navegador,
	// essa janela do navegador é gerenciada pelo kernel, mas não passa de uma moldura 
	// com abas.
	// >> o kernel ja sabe que o processo tem uma aba, então quando o processo 
	//tenta criar uma janela, a sua janela será criada dentro de sua aba.
	
	//General purpose appplication  -  {} Developer version
	
	//@todo:
	//Criar essas funções na API.
	//unsigned long ScreenWidth = (unsigned long) APIGetScreenWidth();
	//unsigned long ScreenHeight = (unsigned long) APIGetScreenheight();
	
	
	//
	// Configurando o retângulo que deve ser usado pelo terminal.
	//
	
	//#bugbug 
	// esses valores são usados para construir a janela principal.
	// o que desejamos são os valores do retângulo da área de cliente 
	// da janela principal.
	
	//terminal_rect.left = wpWindowLeft;
	//terminal_rect.top = wpWindowTop;
	//terminal_rect.width = wsWindowWidth;
	//terminal_rect.height = wsWindowHeight;
	
	//#debug
	//printf("terminal_rect: 1\n");	
    //printf("l={%d} t={%d} w={%d} h={%d}\n", 
	//    terminal_rect.left, terminal_rect.top,
	//	terminal_rect.width, terminal_rect.height );
	//while(1){}
	
	
	
	// # ??
	// Pegando a janela principal para usarmos como janela mãe.
	
	/*
	
	struct window_d *pW;

	pW = (struct window_d *) apiGetWSScreenWindow ();
	
	if ( (void *) pW == NULL )
	{
	    printf("Screen Window fail\n ");
	    
		while (1){
			asm ("pause");
			//exit (1);
		}
	}
	*/
    
    //
    // #todo: Pegar o desktop atual.
    //
    
    
	//
	// Criando a janela WT_OVERLAPPED.
	// 
	
	// Com base nas informações obtidas no sistema.
	// verde 0x83FCFF
	// preto COLOR_BLACK
						
    //para flat os dois poem ser a mesma cor.
    //não completamente preto.	
	//apiBeginPaint ();
	
	//hWindow = (void *) APICreateWindow ( WT_OVERLAPPED, 1, 1, "SHELL",
	//                    wpWindowLeft, wpWindowTop, 
	//				    wsWindowWidth, wsWindowHeight,    
    //                    pW, 0, 0x35475F, xCOLOR_GRAY1 ); //pW, 0, xCOLOR_GRAY3, xCOLOR_GRAY1 ); //#35475F	

	//hWindow = (void *) APICreateWindow ( WT_OVERLAPPED, 1, 1, "SHELL",
	//                    10, 10, 200, 200,    
    //                    pW, 0, 0x35475F, xCOLOR_GRAY1 ); 	
	
	//hWindow = (void *) APICreateWindow ( 1, 1, 1, "XXX",     
    //                            10, 10, 200, 200,
    //                            0, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );


	//if ( (void *) hWindow == NULL )
	//{
	//	printf ("FAIL!");
	//	while(1){}
	//	
	//	die ("shell.bin: hWindow fail");
	//}
	
	
	//printf("HOLAMBRA KERNEL SHELL\n");	
    //printf("#debug breakpoint");	
	//while(1){} 
	
	/*
	 Imprimindo o ponteiro para a estrutura da janela criada 
	 Estamos testando se o retorno está funcionando nesse caso.
	 */
	/* isso funcionou
	printf("Testing handle {%x}\n",hWindow);
	
	printf("Testing resize window\n");
	APIresize_window( hWindow, 640, 480);
	*/
 
	
	//apiEndPaint();
	
	//hWindow = shellCreatemainWindow ();
	
	//printf("OK FUNCIONOU");
	//while(1){}
	
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
	
    //APIRegisterWindow (hWindow);
    //APISetActiveWindow (hWindow);	
    //APISetFocus (hWindow);
	
	//#test
	//vamos mostrar a janela do shell antes de criarmos a janela 
	//da área de cliente
	//apiShowWindow (hWindow);
	
	//#test 
	//Criando um timer.
	
	//printf("shmain: Creating timer\n");
					
		//janela, 100 ms, tipo 2= intermitente.
	//system_call ( 222, (unsigned long) hWindow, 100, 2);		

	
	//printf("HOLAMBRA KERNEL SHELL\n");	
    //printf("#debug breakpoint");
    //while(1){} 	
	
	//#importante
	//VAMOS EFETUAR ESSE REFRESH DEPOIS DE CRIARMOS OUTRA JANELA.
	//refresh_screen ();
	
	

	// #importante:
	// +pegamos o retângulo referente à area de cliente da janela registrada. 
	// +atualizamos as variáveis que precisam dessa informação. 
	// reposicionamos o cursor.
	// reabilitamos a piscagem de cursor.
	
 
	//#bugbug
	//Isso falhou. Vamos deixar pra depois.
	// +pegamos o retângulo referente à area de cliente da janela registrada. 
	//unsigned long xbuffer[8];	
	//system_call ( 134, (unsigned long) hWindow, 
	//    (unsigned long) &xbuffer[0], (unsigned long) &xbuffer[0] );	
	//terminal_rect.left = xbuffer[0];
	//terminal_rect.top = xbuffer[1];
	//terminal_rect.width = xbuffer[2];
	//terminal_rect.height = xbuffer[3];	
	
	

	
	terminal_rect.left = wpWindowLeft;
	terminal_rect.top = wpWindowTop;
	terminal_rect.width = wsWindowWidth;
	terminal_rect.height = wsWindowHeight;


	//
	// ## Se der problema no tamanho da área de cliente ##
	//
	
	if ( terminal_rect.left < wpWindowLeft ||
         terminal_rect.top < wpWindowTop ||	
	     terminal_rect.width > wsWindowWidth ||
		 terminal_rect.height > wsWindowHeight )
	{
        //#debug
		printf("## fail ## \n");
	    printf("terminal_rect: 2\n");	
        printf("l={%d} t={%d} w={%d} h={%d}\n", 
	        terminal_rect.left, 
			terminal_rect.top,
		    terminal_rect.width, 
			terminal_rect.height );
        while (1){
			asm ("pause");
		}			
	}
	
	
    //#debug
	//#todo: 
	//#debug mostrar as informações obtidas antes de começar a usar
	//...	

		/*
	    printf("## debug ## \n");
	    printf("terminal_rect: 2\n");	
        printf("l={%d} t={%d} w={%d} h={%d}\n", 
	        terminal_rect.left, 
			terminal_rect.top,
		    terminal_rect.width, 
			terminal_rect.height );	
	   */
	
    //printf("#debug breakpoint");
    //while(1){} 	
	
	//===============================
	
    //
	// ## Janela para texto ##
	//
	
  
    //apiBeginPaint();
	
	//mudando as dimensões a janela dentro da área de cliente.
	
	//terminal_rect.left = terminal_rect.left +2;
	//terminal_rect.top = terminal_rect.top +2;
	//terminal_rect.width = terminal_rect.width -4 -40;  //8 * 80;
	//terminal_rect.height = terminal_rect.height -4;    //8 * 32;

	//área de cliente fake.
	terminal_rect.left   = terminal_rect.left  +4;
	terminal_rect.top    = terminal_rect.top   +60;
	terminal_rect.width  = terminal_rect.width  -60;  //8 * 80;
	terminal_rect.height = terminal_rect.height -100;  //8 * 32;


	
	
	hWindow2 = (void *) APICreateWindow ( WT_SIMPLE, 1, 1, "SHELL-CLIENT",
	                        terminal_rect.left, terminal_rect.top, 
					        terminal_rect.width, terminal_rect.height,    
                            0, 0, COLOR_TERMINAL2, COLOR_TERMINAL2);	   

						
	if ( (void *) hWindow2 == NULL )
	{	
		die ("shell.bin: hWindow2 fail");
	}	
	
	
	
    APIRegisterWindow (hWindow2);
    //APISetActiveWindow (hWindow2);	
    APISetFocus (hWindow2);	 
	
	//#importante
	//refresh_screen ();	
	
	//#test 
	//substituindo refresh screen por show window.
	//vamos mostrar a janela da área do cliente, depois de 
	//termos mostrado a janela mãe.
	apiShowWindow (hWindow2);

	//apiEndPaint();
	
	
	//===========================================================

	
	//
	// Habilitando o cursor piscante de textos.
	//
	
	shellSetCursor ( (terminal_rect.left / 8) , ( terminal_rect.top/8) );	
	
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 );
	
    //Mensagem ...
	//printf("Starting SHELL.BIN in Holambra Kernel ...\n");	
	
    //printf("#debug breakpoint");
    //while(1){} 	
	
	
	//printf("HOLAMBRA KERNEL SHELL\n");	
   // printf("#debug breakpoint");
   // while(1){} 		
	
	//#bugbug
	//janela usada para input de textos ...
	//o input de texto pode vir de várias fontes.
	//api_set_window_with_text_input(hWindow);
	
	//
	// ++ terminal ++
	//
	
	// #importante
	// Definindo a janela como sendo uma janela de terminal.
	// Isso faz com que as digitações tenham acesso ao procedimento de janela de terminal 
	// para essa janela e não apenas ao procedimento de janela do sistema.
	// # provavelmente isso marca os limites para a impressão de caractere em modo terminal 

	system_call ( SYSTEMCALL_SETTERMINALWINDOW, (unsigned long) hWindow2, 
		(unsigned long) hWindow2, (unsigned long) hWindow2 );
		
				 
	//salva ponteiro da janela principal e da janela do terminal. 
	shell_info.main_window = ( struct window_d * ) hWindow;			 
	shell_info.terminal_window = ( struct window_d * ) hWindow2;		
	
	//
	// @todo: Apenas registrar o procedimento dessa janela na sua estrutura no kernel..
    // 			
	
	//===========================
	
	
	// Init Shell:
	//     Inicializa variáveis, buffers e estruturas. Atualiza a tela.
	
	enterCriticalSection();

    //#BUGBUG
    //Estamos passando um ponteiro que é uma variável local.	

	Status = (int) shellInit (hWindow2); 
	
	if ( Status != 0 ){
		die ("SHELL.BIN: app_main: shellInit fail");
	};
	exitCriticalSection();     		
	
	//printf("HOLAMBRA KERNEL SHELL\n");	
    //printf("#debug breakpoint");
    //while(1){} 			

	
	//
	//#importante:
	//Agora é a hora de pegar mensagens de input de teclado.
	//Mas se o shell não for interativo, então não pegaremos 
	//mensagens de input de teclado.
	//
	
	if ( interactive != 1 ){
		
		//#debug
        printf("shell is not interactive\n");
		
		goto skip_input;
	};
	
	
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
	
 
	
	//
	// **** Mensagens  ****
	//
	
	//printf("Tentando pegar mensagem enviada para o procedimento de janela.");
	//refresh_screen();
	
	//isso é um teste pegar um valor por vez não é a melhor opção.
	
	//struct window_d *msg_Window;
	int msg_Message;
	void *msg_Long1;
	void *msg_Long2;
	
	//struct shell_message_d *msg;
	

	// Get Message: 
	// Systemcall get message
	// Enviamos um ponteiro de estrutura de janela para que o Kernel possa 
	// pegar a mensagem que esta dentro da estrutura. Essa estrtura fica 
	// protegida no Kernel.
		
	// #bugbug: ??
	// Na verdade essa rotina está pegando a mensagem na janela 
	// com o foco de entrada. Esse argumento foi passado mas não foi usado.
		
	unsigned long message_buffer[32];	
	
	//vamos testar se a mensagem esta no range padrao de servidores
	//9000 ~  9999
	int msgtest;
	
	
	//
	//   ## main loop ##
	//
		
//Mainloop:
    
	/* Nesse teste vamos enviar um ponteiro de array, pegarmos os quatro 
	   elementos da mensagem e depois zerar o buffer */
	
	while (running)
	{
		//#obs: O retorno será 1 se tiver mensagem e 0 se não tiver.
		enterCriticalSection(); 
		system_call ( 111,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		exitCriticalSection(); 
			
		if ( message_buffer[1] != 0 )
        {
            //printf(".");			
		}	
		
		if ( message_buffer[1] != 0 )
		{
			
	        //Vamos testar se a mensagem esta no range padrao de servidores
	        //9000 ~  9999
			if ( message_buffer[1] >= 9000 && message_buffer[1] <= 9999  )
			{
				//Passamos o endereço do buffer contendo os argumentos.
                serverDialog ((unsigned long) &message_buffer[0] );
			
			}else{
				
	            shellProcedure ( (struct window_d *) message_buffer[0], 
		            (int) message_buffer[1], 
		            (unsigned long) message_buffer[2], 
		            (unsigned long) message_buffer[3] );
			};
			
			message_buffer[0] = 0;  //window
            message_buffer[1] = 0;  //msg
            message_buffer[3] = 0;  //long1
            message_buffer[4] = 0;	//long2
        };				
	};
	
	//
	// Entramos aqui se running for igual a 0.
	//
	
	switch (ShellFlag)
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

    shellExecuteThisScript ( argv[3] );

	// Exit process.
end:

    // Desabilitando o cursor de texto.
    // Quando outro aplicativo precisar ele clica em uma janela, 
	// ela ganha o foco e habilita o cursor piscante.	
	
    system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);

#ifdef SHELL_VERBOSE		
    printf("SHELL.BIN: exiting code '0' ...\n");
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
	
	
	//#importante
	//Temos um ponteiro para o nosso buffer de argumentos
	//para as mensagens atendidas pelo servidor. 
	

	
	//if( msg == COMMAND_INITIALIZE_SHELL ){
		//...
	//}
	
    switch (msg)
    {
		//Faz algumas inicializações de posicionamento e dimensões.
        //case MSG_INITDIALOG:
        //    break;

		//Torna a janela visível.
        //case MSG_SHOWWINDOW:
		//    break; 
		 
		case MSG_KEYDOWN:
            switch (long1)
            {
				//EOF
				//case -1:
				//    #todo
				//    break;
				
				// Null key.
				case 0:
				    pause();
					pause();
					//pause();
					//pause();
					cpu_relax();
				    return (unsigned long) 0;
				    break;
				
				// Enter.
				// Finaliza a string e compara.
				case VK_RETURN:
				    
					//#test
					printf("\r");
					printf("\n");
				
				    input('\0'); 
					
					//#obs: 
					//#importante 
					//Se essa janela for a janela do shell, 
					//então a rotina de comparação poderá fazer um refresh dessa janela. 
					//#obs: talvez esse refresh nem seja necessário.
					//cada rotina chamada que faça seu próprio refresh se conseguir.
					shellCompare (window);
					goto done;
                    break; 

				//#test	
                case VK_TAB:					
					printf("\t");
					goto done;
				    break;	

				//#todo
				case VK_BACK:
				    
					//#test
					//o cursor do ldisc no kernel precisa ser atualizado tambem.
					//textCurrentCol--;
					//apiSetCursor (textCurrentCol,textCurrentRow);
					//shellSetCursor (textCurrentCol,textCurrentRow);
					//shellInsertNextChar ( (char) ' ' ); 
					goto done;
                    break;					
                              
                // Mensagens de digitação.
				// Texto. Envia o caractere.
                // Imprime os caracteres normais na janela com o foco de 
				// entrada.
				// Enfilera os caracteres na string 'prompt[]' para depois 
				// ser comparada com outras strings.
				// prompt[] é o stdin.
                default:			   
				    
					// Coloca no stdin, prompt[].
					input ( (unsigned long) long1 );      
                    
					// Coloca na memória de video virtual,
					// Que é semelhante a vga, contendo char e atributo.
					shellInsertNextChar ( (char) long1 );  
					
					// #importante:   
					// IMPRIMINDO.
					// Funcionando bem.
					// Ok, no caso de backspace não deve imprimir nada,
					// mas talvez avançe.
					//obs: tem que olhar o que a rotina no kernel faz no caso do backspace.
					
					//#importante: A ROTINA QUE INSERE O CHAR TEM QUE EFETUAR O REFRESH 
					//ASSIM ELA PODE CHAMAR O SCROLL SE PRECISAR.
					
					//shellRefreshCurrentChar();
					//printf ("%c", (char) long1 ); 	//deletar.				
					
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
		    switch (long1)
			{
		        
				case VK_F1:
                    

					//shellTestLoadFile ();
					
					//inicializa a área visível.
					//textTopRow = 0;
	                //textBottomRow = 0 + 24;
						
					break;
					
				case VK_F2:
				    //testChangeVisibleArea();
					break;
					
				case VK_F3:
				    //shellRefreshVisibleArea();
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
            switch (long1)
			{
				
				//O MENU APPLICATION É O CONTEXT MENU.
				//
				case VK_APPS:
				    MessageBox ( 1, "Gramado Core Shell:", "VK_APPS Context Menu" );
					break;
			}		
		    break;
		

        // Commands.		
		case MSG_COMMAND:
            switch (long1)
			{
				// Null.
				case 0:
				    MessageBox( 1, "Shell test", "Testing MSG_COMMAND.NULL." );
				    break;
				
				// About.
				// Abre uma janela e oferece informações sobre o aplicativo.
				case CMD_ABOUT:
				    // Test.
				    MessageBox( 1, "Shell test", "Testing MSG_COMMAND.CMD_ABOUT." );
				    break;
				
				//clicaram no botão
				case BN_CLICKED:
				    //if(window == i1Window){
					     //@todo: abre o menu de aplicativos
					//}
				    //if(window == i2Window){
					   //@todo: abre o interpretador de comandos.
					//}
					//#debug
					printf(" * BN_CLICKED * \n");
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
		case 30:
		    switch (long1)
			{
				case 1:
				
				    //#obs: No keydown a gente só abaixa o botão.
					
				    //#debug
					//printf("button 1\n");     
					
                    //cima
					if ( window == app1_button )
                    {
						updateVisibleArea( 0 );
						shellRefreshVisibleArea(); 
                        //shellScroll();
						break;
					}

					//baixo
					if ( window == app2_button )
                    {
                        updateVisibleArea( 1 );
						shellRefreshVisibleArea();
					    break;
					}
					
					if ( window == editboxWindow )
					{
					    APISetFocus (editboxWindow);
					    //APIredraw_window (editboxWindow,1);
						break;
					}					
					
					APISetActiveWindow (window);
					//APIredraw_window ( window, 1 );
					
					//botão de close
					//if ( window == close_button )
				    //{
					    //APIresize_window ( window, 200, 200 );
					    //APIredraw_window ( window, 1 );
					    //refresh_screen (); //não precisa isso	

					//	running = 0;
                    //    ShellFlag = SHELLFLAG_EXIT;						
					//}    
					break;
					
				case 2:
				    //#debug
				    printf("button 2\n");
				    break;
					
				case 3:
				    //#debug
				    printf("button 3\n");
				    break;
			};			
            break;

		// MSG_MOUSEKEYUP	
		case 31:
		    switch (long1)
			{		
				case 1:
				    //printf("up button 1\n");
					if (window == menu_button)
					{
	                    shellTestButtons ();	
		                refresh_screen ();						
					}
					
					
					//botão de reboot;
					if ( window == reboot_button )
                    {
					    printf("Rebooting...\n");
		                system("reboot"); 	
					}
					
					//botão de close
					if ( window == close_button )
				    {
					    //APIresize_window ( window, 200, 200 );
					    //APIredraw_window ( window, 1 );
					    //refresh_screen (); //não precisa isso	

						running = 0;
                        ShellFlag = SHELLFLAG_EXIT;						
					}  
					
					break;
					
				case 2:
				    printf("up button 2\n");
				    break;
					
				case 3:
				    printf("up button 3\n");
				    break;
			};		
            break;	

		// MSG_MOUSEMOVE	
		case 32:
            //APISetFocus(window);
			//printf("m");
            break;	

		// MSG_MOUSEOVER	
		case 33:
		    
			//se tiver passando em cima do botão de close.
			if ( window == close_button )
			{
				//printf(".");
			    //APIresize_window ( window, 200, 200 );
				//APIredraw_window ( window, 1 );	
			}
            
		    break;

		//entered	
        case 38:
		    if ( window == close_button )
			{
			    //printf("entered\n");	
			}
            break;		

		//exited	
        case 39:
		    if ( window == close_button )
		    {
			    //printf("exited\n");
		    }
            break;
			
		//Quando a aplicativo em user mode chama o kernel para 
		//que o kernel crie uma janela, depois que o kernel criar a janela,
		//ele faz uma chamada ao procedimento de janela do aplicativo com a mensagem 
        //MSG_CREATE, se o aplicativo retornar -1, então a rotina em kernel mode que 
        //esta criando a janela, cancela a janela que está criando e retorn NULL.		
		case MSG_CREATE:
		    printf("SHELL.BIN: MSG_CREATE\n");
		    break;
			
		//MSG_TIMER ;;#TODO INCLUIR ISS0 NA API.	
		case 53:
		    //printf("shell tick\n");
			updateObject(); //interna
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
			
			




		//...
			
			
		//Mensagem desconhecida.
		default:
		    //printf("shell procedure: mensagem desconhecida\n");
		    goto done;
		    break;	  
    };

    // Nothing for now !
done:
	return (unsigned long) apiDefDialog ( window, msg, long1, long2 );
}


/*
 ******************************
 * shellWaitCmd:
 *     Espera completar o comando 
 * com um [ENTER]. ##suspensa
 */
void shellWaitCmd (){
		
	// @todo: Cuidado com loop infinito.

	
	// Obs: Quem muda o status é o procedimento,
	//      quando recebe o retorno da função input:
	

	// Uma interrupção de teclado aciona o procedimento
	// do shell que atualiza o status.
	
	
	// BUG BUG :
    //
    //    Pra esse shell funcionar teria que habilita
    //    agora a interrupção de teclado e somente ela
    //    para que a interrupção de timer não bagunçe as
    //    coisas fazendo troca de contexto.

	
	//asm("sti");    //@todo; Não habilitar!
	
    //Loop.  
	
    do{	 
		if ( prompt_status == 1 )
		{
			prompt_status = 0;     
			return;
	    };
	
	} while (1);

    prompt_status = 0;	
};


/*
 ****************
 * shellCompare:
 *     Compara comandos digitados com palavras chave.
 *     Compara a palavra em 'prompt[]' com outras e chama o serviço.
 * o enter foi o caractere digitado, vamos comparar palavras.
 *
 * Credits:
 * + Stephen Brennan - https://brennan.io/2015/01/16/write-a-shell-in-c/
 * + Frederico Martins Nora (frednora)
 */
 
//#TEST 
//#define LSH_TOK_DELIM " \t\r\n\a+!:=/.<>;|&" 
 
#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80
 
unsigned long shellCompare (struct window_d *window){
	
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
	
	//#importante:
	//Transferir toda alinha de comando para a memória 
	//compartilhada.
	//obs: Possivelmente isso não continuaá assim, pas por enquanto tá bom.

	unsigned char *shared_memory = (unsigned char *) (0xC0800000 -0x100);
	
	//linha de 80 chars no máx.
	for ( i=0; i<80; i++ ){
		shared_memory[i] = prompt[i];
	}
	
	
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
	if ( *c == '\0' ){
	    goto exit_cmp;	
	}
	
	//>' '
	//Só faz o tratamento com while se for igual a ' '.
    if ( *c == ' ' || *c == '\t' )
	{
        int j;		
        //#importante:
		//Aqui estamos tratando uma linha de comando inteira.
		
	    //enquanto c[] for diverente de ' ' c avança.
	    //isso elimina os espaços para c[]
	    j=0;
		while ( *c == ' ' || *c == '\t' )
		{ 
	        
			//Limits
		    j++;
			if ( j > wlMaxColumns )
			{
			   //#debug
               //Isso significa que uma string 
			   //construida em prompt[] não foi 
			   //corretamente finalizada.
			   //ou algum problema no while anterior.
			   //printf("#debug \n");				
			   printf("shellCompare: *hang while1\n");	
			   while (1){
				   asm ("pause");
			   }
			}
			
			//desrepeitamos o limite imposto pelo fim da string.
			//por isso temos que fazer a marcação exata do início 
			//da linha de comando e do fim da linha de comando.
			// |            |.......|        |
			// start       left   right     end
			
			c++; 
		};
		
		//se depois de eliminarmos os espaços encontrarmos
		//um '\0' de fim de string.
		//significa que o usuário digitou um monte de espaços
		//depois apertou enter.
		//não há mais o que fazer.
	    if ( *c == '\0' ){
	        goto exit_cmp;	
	    }		
	    
		int line_rest = (wlMaxColumns-j);
		
		//copia todo o resto da linha para o inpicio da linha.
        for ( j=0; j<line_rest; j++ )
		{
			prompt[j] = c[j];
			
			//se enquanto estamos copiando,
			//ja copiamos o finalizador de string,
			//não precisamos copiar mais nada.
			if ( *c == '\0' ){
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
	
	// #importante:
	// Vamos checar se o pathname é absoluto ou relativo.
	// +Se tiver barra, significa que o pathname é absoluto e 
	// começa no diretório raiz do volume do sistema. root:/volume1/
	// +Se começar por root:/ também é absoluto.
	// +Pathname relativo é somente aquele que é apenas um nome 
	// de arquivo dentro do diretório atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	// $/ é o diretório raiz do volume do sistema.
	// $v/ é o diretório raiz do vfs.	
 

    absolute = absolute_pathname ( (char *) prompt );
	
    switch (absolute)
	{
		//Não é absoluto ou falhar
		case 0:
		    goto this_directory;
		    break;
			
		//é absoluto	
		case 1:
		    goto check_directory; 
			break;
		//falha	
		case 2:
		default:
		    goto this_directory;
			break;
	};

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
    while ( token != NULL )
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

    if ( strncmp( (char *) tokenList[0], "dobin", 5 ) == 0 ){
	    goto dobin;	
	}

    if ( strncmp( (char *) tokenList[0], "dotry", 5 ) == 0 ){
		goto dotry;
	} 
	
	//um comando no shell pede para executar um script
    if ( strncmp( (char *) tokenList[0], "dosh", 4 ) == 0 ){
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
	if ( strncmp( prompt, "token", 5 ) == 0 )
    {
		printf("\nTesting tokenList ...\n");
		printf("\nTotal={%d}\n",token_count);
		printf("\n Comand = %s \n",tokenList[i]);
		refresh_screen();
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL ){
			goto exit_cmp;
		}else{
			
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i] );	
            
			if ( strncmp( (char*) tokenList[i], "-a", 2 ) == 0 ){
			    printf("[OK] argumento %s selecionado.\n", tokenList[i]);
		    }
			//...
		};
		
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL ){
			goto exit_cmp;
		}else{
			
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i] );	
            
			if ( strncmp( (char*) tokenList[i], "-b", 2 ) == 0 ){
			    printf("[OK] argumento %s selecionado.\n", tokenList[i] );
		    }
			//...
		};		
		
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL ){
			goto exit_cmp;
		}else{
			
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i] );	
            
			if ( strncmp( (char *) tokenList[i], "-c", 2 ) == 0 ){
			    printf("[OK] argumento %s selecionado.\n", tokenList[i] );
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
	if ( strncmp( prompt, "about", 5 ) == 0 )
	{
		shellSendMessage ( NULL, MSG_COMMAND, CMD_ABOUT, 0);
		
        //chama message box com mensagem about.
        //apiSendMessage ( (struct window_d *) 0, 
		//                 (int) MSG_COMMAND, 
		//				 (unsigned long) CMD_ABOUT, 
		//				 (unsigned long) 0 );
						 
	    goto exit_cmp;
	};

	// Imprime a tabela ascii usando a fonte atual.
    // 128 chars.	
    //if( strncmp( prompt, "ascii", 5 ) == 0 )
    //{
		//shellASCII();
	//	goto exit_cmp;
	//}


	//bmp exemplo.bmp
    if ( strncmp( prompt, "bmp", 3 ) == 0 )
	{
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("Error: No name!\n");
		}else{
			
			//@todo: podemos checar se o pathname é absoluto,
			//e onde se encontra o arquivo que queremos.
			//shellDisplayBMP ( (char *) tokenList[i] );
		
		   //test 2MB
		   //o argumento tamanho é dado  em kb.
		   //printf("test 2mb\n");
		   //shellDisplayBMPEx ( (char *) tokenList[i], (int) (1024*2) );
		   
		   //test 200kb
		   printf("test 200kb\n");
		   shellDisplayBMPEx ( (char *) tokenList[i], (int) (200) );
		};
		goto exit_cmp;
    };	
	
	// boot
	// ?? Boot info talvez.
	// ?? Talvez informações de boot ou configuração.
	if ( strncmp( prompt, "boot", 4 ) == 0 )
	{
	    printf("~boot\n");
		//boot();
        goto exit_cmp;
    };
	


	// cd - Change dir.
	if ( strncmp( prompt, "cd", 2 ) == 0 )
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
			    shell_pathname_backup ( current_workingdiretory_string, 1 ); 
                goto exit_cmp;				
		    }			
			
	        // updating the current working directory string.
	        shellUpdateWorkingDiretoryString ( (char *) tokenList[i] );
			
			//@todo: podemos checar se o pathname é absoluto,
			//e onde se encontra o arquivo que queremos.
			//shellDisplayBMP( (char*) tokenList[i] );
		};		
		
		
		// o que segue o comando cd é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
		//cd_buitins();
	    goto exit_cmp;
	};	

	// clear-screen-buffer
	if ( strncmp( prompt, "clear-screen-buffer", 19 ) == 0 )
	{
		shellClearBuffer();
		goto exit_cmp;
	}	
	
	//close
	if ( strncmp( prompt, "close", 5 ) == 0 )
	{
		shellSendMessage( NULL, MSG_CLOSE, 0, 0);
	    goto exit_cmp;
	}		

    // cls - Clear the screen.
	if ( strncmp( prompt, "CLS", 3 ) == 0 || 
	     strncmp( prompt, "cls", 3 ) == 0 )
	{
        cls_builtins();
        goto exit_cmp;
	};
	
	
	// color
	// color-scheme
	// Seleciona um dos 2 modos de cores padrão do sistema.
    if ( strncmp( prompt, "color", 5 ) == 0 || 
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
			if( strncmp( (char*) tokenList[i], "--humility", 10 ) == 0 )
			{ 
		        printf("Selecting Humility color scheme\n"); 
                system_call(119, (unsigned long)1, (unsigned long)1, (unsigned long)1);
				printf("done\n");
                goto exit_cmp;				
			}
			
			//pride
			if( strncmp( (char*) tokenList[i], "--pride", 7 ) == 0 )
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
	if ( strncmp( prompt, "copy", 4 ) == 0 )
	{
		// o que segue o comando copy são dois pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		copy_builtins();
	    goto exit_cmp;
	}
	
			
	// date
	if ( strncmp( prompt, "date", 4 ) == 0 ){
		date_builtins();
        goto exit_cmp;
    };	

	// del
	if ( strncmp( prompt, "del", 3 ) == 0 )
	{
		// o que segue o comando del é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		del_builtins();
	    goto exit_cmp;
	};	

    // desktop.
	if ( strncmp( prompt, "desktop", 7 ) == 0 ){
        desktopInitialize();
        goto exit_cmp;
	};	
	

    // dialog-box
	//Testing dialog box.
	if ( strncmp( prompt, "dialog-box", 10 ) == 0 )
	{
		//@todo:testar os 4 tipos 
	    MessageBox( 1, "Shell dialog box","Testing dialog box...");
        goto exit_cmp;
    };		
	
	// dir - Lista os arquivos no estilo DOS.
	if ( strncmp ( prompt, "dir", 3 ) == 0 )
	{
		//char dir_name[] = "volume1";
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL )
		{
			
		    //listar os arquivos em um diretório dado o nome do diretório.
			enterCriticalSection();
		    system_call( 177,
		             (unsigned long) 0,   //nome do diretório.
                     (unsigned long) 0,   
                     (unsigned long) 0 ); 			
		    //system_call( 177,
		    //         (unsigned long) dir_name,   //nome do diretório.
            //         (unsigned long) dir_name,   
            //         (unsigned long) dir_name ); 
		    exitCriticalSection();		
			
			
		}else{

		    //listar os arquivos em um diretório dado o nome do diretório.
			enterCriticalSection();
		    system_call( 177,
		             (unsigned long) tokenList[i],   //nome do diretório.
                     (unsigned long) tokenList[i],   
                     (unsigned long) tokenList[i] ); 
		    exitCriticalSection();		
			
			//...
		};		
				
		// o que segue o comando dir é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
        //se o pathname for null então o comando atua sobre o pwd		
		//dir_builtins();
        goto exit_cmp;
    };
	
    // disk-info
	if ( strncmp( prompt, "disk-info", 9 ) == 0 )
	{
	    shellShowDiskInfo();
        goto exit_cmp;
    };	
	
	
	// echo - Echo de terminal.
    if ( strncmp( prompt, "echo", 4 ) == 0 )
	{
		echo_builtins(tokenList);
		goto exit_cmp;
    };

	
	// editbox
	// Cria uma edibox.
    // #teste: deletar.
	if ( strncmp( prompt, "edit-box", 8 ) == 0 )
	{
	    enterCriticalSection();    
	    shellCreateEditBox();
	    exitCriticalSection();    
		
		goto exit_cmp;
    };		
	
	// exec - Executa um programa fechando o shell.
    if ( strncmp( prompt, "exec", 4 ) == 0 )
	{
		// o que segue o comando exec é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		exec_builtins();
		ShellFlag = SHELLFLAG_EXIT;
		goto exit_cmp;
    };	
	
	// exit - Exit the application.
    if ( strncmp( prompt, "exit", 4 ) == 0 )
	{
		exit_builtins();
		ShellFlag = SHELLFLAG_EXIT;
		goto exit_cmp;
    };
	
    // fork - Testando a função fork.
	// Apenas obtendo o retorno na rotina de clonagem.
	if ( strncmp ( prompt, "fork", 4 ) == 0 )
	{
		printf("fork: Tentando clonar o processo atual ...\n");
		
		int pidFORK = (int) fork ();

 		//Mostra o ID do processo clone.
		printf("Clone PID={%d}\n", pidFORK );
		
		//mostra o id do processo atual.
		shellShowPID ();
		
		printf("fork: done\n");
        
		goto exit_cmp;
	};		
	
	
    // getpid
	if ( strncmp( prompt, "getpid", 6 ) == 0 ){
	    getpid_builtins();
        goto exit_cmp;
    };
	
    // getppid
	if ( strncmp( prompt, "getppid", 7 ) == 0 ){
	    getppid_builtins();
        goto exit_cmp;
    };
	
	
    // getuid - get user id
	if ( strncmp( prompt, "getuid", 6 ) == 0 ){
	    getuid_builtins();
        goto exit_cmp;
    };
	
	
    // getgid - get group id
	if ( strncmp( prompt, "getgid", 6 ) == 0 ){
	    getgid_builtins();
        goto exit_cmp;
    };
	
    //get-usersession
	if ( strncmp( prompt, "get-usersession", 15 ) == 0 )
	{
	    shellShowUserSessionID();
        goto exit_cmp;
    };
	
	
    //get-room (windowstation)
	if ( strncmp( prompt, "get-room", 8 ) == 0 )
	{
		//#todo change name.
	    shellShowWindowStationID();
        goto exit_cmp;
    };
	
    //get-desktop
	if ( strncmp( prompt, "get-desktop", 11 ) == 0 )
	{
	    shellShowDesktopID();
        goto exit_cmp;
    };

	
	//unsigned char *hBuffer = (unsigned char *) 0xC1000000;
	void *hBuffer;
	
	//int thisprocess_id = (int) system_call ( 85, 0, 0, 0); 
	//unsigned char *heaptest = (unsigned char *) system_call ( 184, thisprocess_id, 0, 0 );		
	
    // heap
	if ( strncmp( prompt, "heap", 4 ) == 0 )
	{
		
		printf("testando heap\n");
		
		//printf("%x\n", &heaptest[0]);
		
		//heaptest[0] = 'x';
		
		//printf("%c\n", heaptest[0]);
		//hBuffer[0] = 88;
	    //hBuffer[1] = 99;
		//printf("%d %d \n",hBuffer[0],hBuffer[1]);
		
		hBuffer = (void *) malloc ( 1024*100 ); //100kb
        //hBuffer = (void *) malloc ( 1024*1024*3 ); //3mb		
		if ( (void *) hBuffer == NULL )
		{
			printf("malloc fail 100kb\n");
		}else{
			printf("malloc ok 100kb\n");
		}
		
		printf("done\n");
        goto exit_cmp;
    };		
	
	// hd ??
	// hd info maybe.
    if ( strncmp( prompt, "hd", 2 ) == 0 )
	{
	    printf("~hd\n");
        goto exit_cmp;
    };	
	
	
	// help
	// ?
	// Mostra ajuda.
	// Menu. for gramado virtual machine experience.
    if ( strncmp( prompt, "HELP", 4 ) == 0 ||  
	     strncmp( prompt, "help", 4 ) == 0 || 
	     strncmp( prompt, "?", 1 ) == 0 )
	{

		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			help_builtins (1);
			
		}else{
            
			//if ( strncmp( (char*) tokenList[i], "--experience", 12 ) == 0 )
			//{ 
            //    help_builtins (1); 		
			//}
			
			if ( strncmp( (char*) tokenList[i], "--tests", 7 ) == 0 )
			{
                help_builtins (2);				
			}
			
			//...
		};
		goto exit_cmp;
    };	
		
	
	// install	
    // ?? 
	if ( strncmp( prompt, "install", 7 ) == 0 )
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
	if ( strncmp( prompt, "kernel-info", 11 ) == 0 )
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
	// Testing message box.
	// #todo: Testar os quatro tipos. 
	if ( strncmp( prompt, "message-box", 11 ) == 0 )
	{	
	    //MessageBox ( 1, "Type 1","Testing message box ... Press F1 to exit." );
		//MessageBox ( 2, "Type 2","Testing message box ... Press F1 to exit." );
	    MessageBox ( 3, "Type 3","Testing message box ... Press F1 to exit." );
	    //MessageBox ( 4, "Type 4","Testing message box ... Press F1 to exit." );
        goto exit_cmp;
    }
	

    // mm-info
	if ( strncmp( prompt, "mm-info", 7 ) == 0 )
	{
	    shellShowMemoryInfo();
        goto exit_cmp;
    };	
	
	
    // mm-kernelheap
	if ( strncmp( prompt, "mm-kernelheap", 13 ) == 0 )
	{
	    shellShowKernelHeapPointer();
        goto exit_cmp;
    };

    // mm-processheap
	if ( strncmp( prompt, "mm-processheap", 14 ) == 0 )
	{
	    shellShowProcessHeapPointer();
        goto exit_cmp;
    };

	// mov
	if ( strncmp( prompt, "mov", 3 ) == 0 )
	{
		// o que segue o comando mov são dois pathnames.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
	    goto exit_cmp;
	}		


    // metrics
	// Mostra algumas informações de métrica do sistema.
	if ( strncmp( prompt, "metrics", 7 ) == 0 )
	{
		shellShowMetrics();
        goto exit_cmp;
	};	

	// new
	if ( strncmp( prompt, "new", 3 ) == 0 )
	{		
	    printf("~new - New file or directory\n");		
	    goto exit_cmp;
	}		
	
    
	// mbr
	// ?? Talvez mostrar informações sobre o mbr ou realizar testes.
    if ( strncmp( prompt, "mbr", 3 ) == 0 )
	{
	    printf("~mbr\n");
		
		//#bugbug pagefault
		
		shellTestMBR();
		printf("done\n");
		goto exit_cmp;
    }; 
	
    // pci-info
	if ( strncmp( prompt, "pci-info", 8 ) == 0 )
	{
	    shellShowPCIInfo();
        goto exit_cmp;
    };	
	
	
    // puts - testing puts, from libc.
	if ( strncmp( prompt, "puts", 4 ) == 0 )
	{
        //@todo: Ainda não existe na libc.
		//puts(" # puts Ok# \n");
        goto exit_cmp;
	};	
	
	if ( strncmp ( prompt, "current-process", 15 ) == 0 )
	{
		system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
		goto exit_cmp; 
	}
	
	// pwd - print working directory
	if ( strncmp( prompt, "pwd", 3 ) == 0 ){
		pwd_builtins();
	    goto exit_cmp;
	};		

	
    // reboot
    // @todo: Isso será um aplicativo. reboot.bin	
    if ( strncmp( prompt, "REBOOT", 6 ) == 0 || 
	     strncmp( prompt, "reboot", 6 ) == 0 )
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
	if ( strncmp( prompt, "rename", 6 ) == 0 )
	{
		// o que segue o comando rename são dois pathnames.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
        goto exit_cmp;
    };	
	
	
    // root
	// ??
    if ( strncmp( prompt, "root", 4 ) == 0 )
	{
	    printf("~/root\n");
		//testa_root();
		goto exit_cmp;
    }; 

	
    // save
	if ( strncmp( prompt, "save", 4 ) == 0 )
	{
		// o que segue o comando save é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
	    printf("~save root\n");
        goto exit_cmp;
    };
	
	
	//scroll1
	if ( strncmp( prompt, "scroll1", 7 ) == 0 )
	{
	    testScrollChar((int) '1');
        goto exit_cmp;		
	}
	
	
	//scroll2
	if ( strncmp( prompt, "scroll2", 7 ) == 0 )
	{
	     testScrollChar((int) '2');
        goto exit_cmp;		
	}	
	
	
	
	// service
	//podemos tertar serviços do kernel 
	//enviando argumentos nulos.
	if ( strncmp( prompt, "service", 7 ) == 0 )
	{
	    printf("~service - testa servicos do kernel:\n");
		//test_services();
        goto exit_cmp;
    };
	
	
	// show-screen-buffer
	if ( strncmp( prompt, "show-screen-buffer", 18 ) == 0 )
	{
		shellShowScreenBuffer();
		goto exit_cmp;
	}

	

	
    // shellinfo
	// informações sobre o aplicativo.
	if ( strncmp( prompt, "shell-info", 10 ) == 0 )
	{
		
	    printf("~@todo: shell info.\n");
		shellShowInfo();
        goto exit_cmp;
    };	
	
	//socket-test
	//rotina de teste de soquetes.
	if ( strncmp( prompt, "socket-test", 11 ) == 0 )
	{
		//printf("~socket \n");        
		shellSocketTest();
		goto exit_cmp;
    };		
	
	
    // shutdown - isso será um programa. shutdown.bin
	if ( strncmp( prompt, "shutdown", 8 ) == 0 )
	{
	    printf("~shutdown \n");
        goto exit_cmp;
    };	

	// slots
	if ( strncmp( prompt, "slots", 5 ) == 0 )
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
    if ( strncmp( prompt, "start", 5 ) == 0 )
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
	if ( strncmp( prompt, "system-info", 11 ) == 0 )
	{
	    printf("~@todo: system info.\n");
		shellShowSystemInfo();
        goto exit_cmp;
    };	
	
	
    // t1 - Test file
	// Carrega um arquivo no buffer de words 
	// depois exibe todo o buffer mantendo o posicionamento 
	//no cursor. Isso força um scroll.
	if ( strncmp( prompt, "t1", 2 ) == 0 )
	{	
		shellTestLoadFile();		
        goto exit_cmp;
    };
	
	
	// t2 - Test bmp
	if ( strncmp( prompt, "t2", 2 ) == 0 )
	{
		shellTestDisplayBMP();
        goto exit_cmp;
    };	
	
	
	// t3 - Test thread
	if ( strncmp( prompt, "t3", 2 ) == 0 ||
        strncmp( prompt, "test-thread", 11 ) == 0	)
	{
	    shellTestThreads();
        goto exit_cmp;
    };
	
	//@todo: Colocar no início dessa função.
	FILE *f1;
	int ch_test;
	
	// t4 - testando fopen
	if ( strncmp( prompt, "t4", 2 ) == 0 )
	{
		printf("\n t4: Open init.txt \n");
        
		f1 = (FILE *) fopen ("init.txt","rb");
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
			//#bugbug: page fault quando chamamos fgetc.
			//printf("1");
			ch_test = (int) fgetc (f1);
			//ch_test = (int) getc (f1); 
			
			if( ch_test == EOF )
			{
				printf("\n\n");
				printf("EOF reached :)\n\n");
				goto exit_cmp;
				
			}else{
				//printf("2");
			    printf("%c", ch_test);	
			};
		};
		
		//fail.
		goto exit_cmp;
    };

	// t5 - ( save file )
	// Ok isso funcionou.
	if ( strncmp( prompt, "t5", 2 ) == 0 )
	{
		printf("t5: save file\n");
		save_string2 ( "t5: Salvando esse texto em test1234.txt", "TEST1234TXT" );
		//shell_save_file ();
		printf("t5: done\n");
        goto exit_cmp;
    };	


	// t6 - testando a api. rotina que salva arquivo. 
	// ok, isso funcionou.
	if ( strncmp( prompt, "t6", 2 ) == 0 )	
	{
        printf("t6: todo\n");
        goto exit_cmp;					 
	};
	
	//t7
	//#test
	//testando estado das teclas.
	if ( strncmp( prompt, "KEYS", 4 ) == 0 ||
         strncmp( prompt, "keys", 4 ) == 0 || 
         strncmp( prompt, "T7", 2 ) == 0 || 		 
	     strncmp( prompt, "t7", 2 ) == 0 )	
	{
		printf("VK_CAPITAL %d \n", system_call ( 138, VK_CAPITAL, VK_CAPITAL, VK_CAPITAL ) );				
	    printf("VK_LSHIFT %d \n", system_call ( 138, VK_LSHIFT, VK_LSHIFT, VK_LSHIFT ) );
		printf("VK_RSHIFT %d \n", system_call ( 138, VK_RSHIFT, VK_RSHIFT, VK_RSHIFT ) );
		printf("VK_CONTROL %d \n", system_call ( 138, VK_CONTROL, VK_CONTROL, VK_CONTROL ) );
		printf("VK_WINKEY %d \n", system_call ( 138, VK_WINKEY, VK_WINKEY, VK_WINKEY ) );
		printf("VK_LMENU %d \n", system_call ( 138, VK_LMENU, VK_LMENU, VK_LMENU ) );
		//...
		goto exit_cmp;
	};
	
	//testando a criação de botão e a interação com ele através do mouse.
	if ( strncmp( prompt, "t8", 2 ) == 0 )
    {
	    shellTestButtons ();	
		refresh_screen ();
		goto exit_cmp;
	};	

	if ( strncmp( prompt, "t9", 2 ) == 0 )
    {    
        testShowLines();	
		goto exit_cmp;
	};
	

	if ( strncmp( prompt, "t10", 3 ) == 0 )
    {    
	    testChangeVisibleArea();

		goto exit_cmp;
	};
	
	//t11 - testando o envio de mensagens para o procedimento,
	//usando o kernel.
	if ( strncmp( prompt, "t11", 3 ) == 0 )
    {    
        //chama message box com mensagem about.
        apiSendMessage ( (struct window_d *) 0, (int) MSG_COMMAND, 
		    (unsigned long) CMD_ABOUT, (unsigned long) 0 );
		
		goto exit_cmp;
	};
	
	//buffer de test;
	unsigned long message_buffer[11];
	
	// t12
	// testando mudar um retângulo de lugar.
	// + salva o retângulo num buffer 
	// + copia do buffer para o backbuffer 
	if ( strncmp( prompt, "t12", 3 ) == 0 )	
	{
        printf("t12: test rect \n");
		
		enterCriticalSection(); 
		message_buffer[0] = 100;
		message_buffer[1] = 100;
		message_buffer[2] = 100;
		message_buffer[3] = 100;
		system_call ( 132,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		message_buffer[0] = 50;
		message_buffer[1] = 50;
		message_buffer[2] = 100;
		message_buffer[3] = 100;			
		system_call ( 133,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		exitCriticalSection(); 
		
        goto exit_cmp;					 
	};	
	
	// escrevendo em stdout e mostrando.
	if ( strncmp( prompt, "t13", 3 ) == 0 )
    {    
        //#obs 
        //#lembrando: podemos ter problemas com o buffer do arquivo.		

	    //coloca no stdout.
		stdout_printf("Escrevendo no stdout com stdout_printf \n");
		
		//mostra o arquivo desde o começo.
		printf(stdout->_base);

		goto exit_cmp;
	};	
	
	if ( strncmp( prompt, "t14", 3 ) == 0 )
	{
		
		printf("t14:\n");
	    testCreateWindow ();
		printf("t14: debug *hang");
		while(1){}
		
		goto exit_cmp;
	}
	
	//testando open()
	//precisa incluir fcntl.h
	int ooofd;
	if ( strncmp( prompt, "t15", 3 ) == 0 )
	{
		printf ("t15: open() Opening file init.txt\n");
		ooofd = open ( "init.txt", 0, 0 );
		
		printf ("descriptor=%d \n", ooofd );
		goto exit_cmp;
	}
	
	
	//testando open()
	//precisa incluir fcntl.h
	int cccRet;
	if ( strncmp( prompt, "t16", 3 ) == 0 )
	{
		printf ("t16: close() Closing file '0' \n");
		cccRet = close (0);
		
		printf ("ret=%d \n", cccRet );
		goto exit_cmp;
	}	
	
	//#gws - testando funcionalidades do gws
	if ( strncmp ( prompt, "gws", 3 ) == 0 )
	{
		gws_init();
		
		gws_backbuffer_putpixel ( COLOR_RED,   100, 250 );
		gws_backbuffer_putpixel ( COLOR_GREEN, 105, 250 );
		gws_backbuffer_putpixel ( COLOR_BLUE,  110, 250 );
		
		gws_drawchar_transparent ( 250,       250, COLOR_RED,   (unsigned long) 'R');
		gws_drawchar_transparent ( 250 +8,    250, COLOR_GREEN, (unsigned long) 'G');
		gws_drawchar_transparent ( 250 +8 +8, 250, COLOR_BLUE,  (unsigned long) 'B');
		
		
		gws_draw_char ( 300, 300, (unsigned long) 'X', COLOR_YELLOW, COLOR_RED );
		
		my_buffer_horizontal_line( 400, 88, 500, COLOR_PINK );
		
		drawDataRectangle ( 200, 400, 100, 60, COLOR_YELLOW );

		refresh_screen();
		goto exit_cmp;
	}
	
	//flush stdout
	if ( strncmp( prompt, "flush-stdout", 12 ) == 0 )
	{
		fflush (stdout);
		goto exit_cmp;
	}

	
	// tasklist - Lista informações sobre os processos.
	//isso será um programa tasklist.bin
	if ( strncmp( prompt, "tasklist", 8 ) == 0 ){
		shellTaskList();
        goto exit_cmp;
    };	
	
	
    //test-taskman-server - testando servidor taskman
	if ( strncmp( prompt, "test-taskman-server", 19 ) == 0 )
	{
		//só podemos enviar a próxima mensagem depois que a primeira for atendida.
		//pois ainda não temos fila de mensagens e o servidor demora para receber 
		//tempo de processamento.
        system_call ( 116, 123, 0, 0 );
		//system_call ( 116, 1000, 0, 0 );
		//system_call ( 116, 2000, 0, 0 );
		//system_call ( 116, 3000, 0, 0 );
		//system_call ( 116, 4000, 0, 0 );
        goto exit_cmp;
	};	
	
	// time
	if ( strncmp( prompt, "time", 4 ) == 0 ){
        goto exit_cmp;
    };
	
	// timer-test
	// Essa rotina cria um objeto timer que gera um interrupção 
	// de tempos em tempos e é tratado pelo procedimento de janelas.
	if ( strncmp( prompt, "timer-test", 10 ) == 0 ){

		printf("timer-test: Creating timer\n");
		
	    printf("%d Hz | sys time %d ms | ticks %d \n", 
		    apiGetSysTimeInfo(1), 
			apiGetSysTimeInfo(2), 
			apiGetSysTimeInfo(3) );		
					
		//janela, 100 ms, tipo 2= intermitente.
		//system_call ( 222, (unsigned long) window, 100, 2);	
			
        apiCreateTimer ( (struct window_d *) window, 
            (unsigned long) 50, (int) 2 );			
		
		//inicializando.
        objectX = 0;
        objectY = 0;
        deltaX = deltaValue;
        deltaY = deltaValue;
          
        printf("timer-test: done\n");		  
					
        goto exit_cmp;
    };
	


	
	
	// taskbar
	// Cria uma top bar.
    if ( strncmp( prompt, "taskbar", 7 ) == 0 )
	{
	    enterCriticalSection();    
	    
		//Apenas inicialize. Continuaremos com o procedimento 
		//do shell e não o da barra,
		//shellCreateTaskBar (1);
	    
		exitCriticalSection();    
		
		goto exit_cmp;
    };			
	
	
	// tree
	// Desenha uma pequena árvore.
    if ( strncmp( prompt, "tree", 4 ) == 0 )
	{
		shellTree();
		goto exit_cmp;
    };			
	
	
	// version
	//?? isso pode ser um programa
    if ( strncmp( prompt, "version", 7 ) == 0 )
	{
		show_shell_version();
	    //printf("\n Gramado version %s \n", OS_VERSION );
        goto exit_cmp;
    };
	
    // volume-info
	if ( strncmp( prompt, "volume-info", 11 ) == 0 )
	{
	    shellShowVolumeInfo();
        goto exit_cmp;
    };	
	

	// window
    if ( strncmp( prompt, "window", 6 ) == 0 )
	{
		shellShowWindowInfo();
        goto exit_cmp;
    };


    // Se apertamos o enter e não encontramos um comando válido
    // então damos um aviso de comando inválido e reiniciamos o prompt 
    // na próxima linha.
	
	//fail.
	int Execve_Ret = 1;
	
    //unsigned long a1 = (unsigned long) tokenList[0];
	
	//char *a1 = tokenList[1];
	//char *a1 = tokenList[2];
	
	
doexec_first_command:

    //
	// ## TEST ##
	//

	// #importante:
	// Se estamos aqui é porque o comando não corresponde a nenhuma das 
	// palavras reservadas acima, então executaremos, presumindo ser um nome 
	// de aplicativo no formato 'test.bin'. 
	
	// #importante:
	// Vamos checar se o pathname é absoluto ou relativo.
	// +Se tiver barra, significa que o pathname é absoluto e 
	// começa no diretório raiz do volume do sistema.
	// root:/volume1/
	// +Se começar por root:/ também é absoluto.
	// +Pathname relativo é somente aquele que é apenas um nome 
	// de arquivo dentro do diretório atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	
    absolute = absolute_pathname ( (char *) tokenList[0] );
	
    switch (absolute)
	{
		//Não é absoluto ou falhar
		case 0:
		    //printf("doexec_first_command: not absolute pathname\n");
		    break;
			
		//é absoluto	
		case 1:
		    printf("doexec_first_command: absolute pathname\n");
			
			break;
			
		//falha	
		case 2:
		default:
		    printf("doexec_first_command: pathname fail\n");
			break;
	};   

    // Trata no caso de ser absoluto.
	// + Eliminar ./ pois se trata de arquivo no diretório atual.
	if (absolute == 1)
	{
		//#bugbug: Essa definição não deve ficar aqui.
		char *t = (char *) tokenList[0];
		
		if ( *t == '.' )
		{
			t++;
			
		    if ( *t == '/' )
			{	
				t++;
				tokenList[0] = (char *) t;
			}
	    };	
	};
		
	
	
	//
	// ## Executando um programa no formato ">test.bin"
	//
	
	//char *tmp[] = { tokenList[1], tokenList[2], tokenList[3], NULL };
	//char *tmp2[] = { tokenList[1], tokenList[2], tokenList[3], NULL };
	
    //Presumindo ser um nome de aplicativo no formato 'test.bin'.
    //o token 0 é o nome do programa e o os próximos são argumenteos ..
	//dessa forma podemos enviar um comando e dois argumentos ...
	//?? Talvez devessemos enviar um ponteiro para um array de strings 
	// no último argumento. (argv) ou ainda um env
						 

    //Execve_Ret = (int) shell_gramado_core_init_execve( 
	//                       (const char*) tokenList[0], //nome
	//                       (const char*) tokenList[1], 
	//					   (const char*) tokenList[2] ); //env ...deve ser null
	
	//#bugbug: e sem argumento.
	/*
	char *p = ( char * ) &prompt[0];
	
	while( *p && *p != ' ' && *p != '\0' )
	{
		p++;
	}
	
	while( *p && *p == ' ' && *p != '\0' )
	{
		p++;
	}
	*/
	
	
	//#todo: Colocar isso no início dessa função.
	unsigned long buffer[5];
	int z;
	
	// Colocamos todos os ponteiros no array.
	for ( z=0; z<token_count; z++ ){
	    buffer[z] = (unsigned long) tokenList[z];	
	}						 

	// ## ISSO DEU CERTO ## 	
    // Passamos anteriormente a linha de comandos via memória compartilhada,
    // agora então precisamos passar somente o nome do arquivo.	
    Execve_Ret = (int) shell_gramado_core_init_execve ( 
	                       (const char *) tokenList[0], //nome
	                       (const char *) 0,            //NULL
						   (const char *) 0);           //NULL
						 
	
	
    //Execve_Ret = (int) shell_gramado_core_init_execve( 
	//                       (const char*) tokenList[0], //nome
	//                       (const char*) tokenList[1], 
	//					   (const char*) tokenList[2]); //env ...deve ser null
	
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
	
	//Vamos executar um programa .bin.
	//.bin é a extensão padrão.
	//Executaremos o segundo comando, pois o primeiro é ~$dobin.
	//
dobin:

    if( is_bin( (char *) tokenList[1] ) != 1 )
	{
		printf("dobin: it's not a .bin filename.\n");
		printf("dobin: fail\n");
		//@todo: back ...
	};

	//Precisamos passar somente o nome pois a linah de comando 
	//já foi enviada através de memória compartilhada.
    Execve_Ret = (int) shell_gramado_core_init_execve( 
	                       (const char*) tokenList[1],   // Nome
	                       (const char*) 0,              // Null
						   (const char*) 0 );            // Null
						 
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
	
	
	
// Tente executar um aplicativo com outra extensão.
// Checaremos se é uma extensão das suportadas.	
dotry:
    	
    //Precisamos passar somente o nome pois já passamos 
	//a linha de comandos através de memória compartilhada.
    Execve_Ret = (int) shell_gramado_core_init_execve( 
	                       (const char*) tokenList[1], //Name
	                       (const char*) 0,            //Null
						   (const char*) 0 );          //Null
						 
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
	
	//Um comando no shell invoca a execussão de um script 
	//dado o nome via tokenList.
	
dosh:

    //
	// Vamos tentar colocar o arquivo de script no stdin 
	// que é onde fica o prompt. Então retornaremos no 
	// início dessa rotina mas agora com uma nova linha de comando.
	//
    //nothing for now.
	//o comando [0] é o 'dosh' o [1] é o nome do script.

    if ( is_sh1( (char *) tokenList[1] ) != 1 )
	{
		printf("dosh: it's not a .sh1 filename.\n");
		printf("dosh: fail\n");
	};

    // #ok
	// Estamos passando o nome do arquivo.
	
	//#todo:
	//Essa função deve chamar o interpretador de script
	shellExecuteThisScript ( tokenList[1] );	
	
	//#todo 
	//Podemos apenas sair já a função acima executou o script
	//goto exit_cmp;
	
	goto NewCmdLine;
	
	
//
//  ## Fail ##
//	
	
fail:	
    printf(" Unknown command!\n");
    ret_value=1;
	goto done;
	
	
   //====================
   //    ## EXIT CMP ##
   //====================	

exit_cmp:

    ret_value = 0;	
	
done:

	// Limpando a lista de argumentos.
	// Um array de ponteiros.
	
	for ( i=0; i<TOKENLIST_MAX_DEFAULT; i++ ){
		tokenList[i] = NULL;
	};
	
	shellPrompt ();
	
	
	//#bugbug:
	//queremos dar refresh apenas da janela.
	//Mostrando as strings da rotina de comparação.	
	
	//refresh_screen();
	
    return (unsigned long) ret_value;
};



void shellInitSystemMetrics()
{
	//pegaremos todas as metricas de uma vez só,
	//se uma falhar, então pegaremos tudo novamente.
	
	// Tamanho da tela.	
	smScreenWidth = apiGetSystemMetrics(1);
    smScreenHeight = apiGetSystemMetrics(2); 
	smCursorWidth = apiGetSystemMetrics(3);
	smCursorHeight = apiGetSystemMetrics(4);
	smMousePointerWidth = apiGetSystemMetrics(5);
	smMousePointerHeight = apiGetSystemMetrics(6);
	smCharWidth = apiGetSystemMetrics(7);
	smCharHeight = apiGetSystemMetrics(8);	
	//...
} 

void shellInitWindowLimits(){
	
    //
    // ## Window limits ##
    //

    //full screen support
    wlFullScreenLeft = 0;
    wlFullScreenTop = 0;
    wlFullScreenWidth = smScreenWidth;
    wlFullScreenHeight = smScreenHeight;
	
    //limite de tamanho da janela.
    wlMinWindowWidth = smCharWidth * 80;
    wlMinWindowHeight = smCharWidth * 25;
    wlMaxWindowWidth = wlFullScreenWidth;
    wlMaxWindowHeight = wlFullScreenHeight;	
	
    //quantidade de linhas e colunas na área de cliente.
    wlMinColumns = 80;
    wlMinRows = 1;
    wlMaxColumns = (wlFullScreenWidth / 8);
    wlMaxRows = (wlFullScreenHeight / 8);
	
	//dado em quantidade de linhas.
    textMinWheelDelta = 1;  //mínimo que se pode rolar o texto
    textMaxWheelDelta = 4;  //máximo que se pode rolar o texto	
	textWheelDelta = textMinWheelDelta;
	//...
}


void shellInitWindowSizes()
{
	
//
//  ## Window size ##
//

    //wsWindowWidth = wlMinWindowWidth;
    //wsWindowHeight = wlMinWindowHeight;	
	
	//Tamanho da janela do shell com base nos limites 
    //que ja foram configurados.	
	
	wsWindowWidth =  WINDOW_WIDTH;
	wsWindowHeight = WINDOW_HEIGHT;
	
	
	if ( wsWindowWidth < wlMinWindowWidth )
	{
		wsWindowWidth = wlMinWindowWidth;
	}
	
	if ( wsWindowHeight < wlMinWindowHeight )
	{
	    wsWindowHeight = wlMinWindowHeight;	
	}


};


void shellInitWindowPosition()
{
	
	//window position
	wpWindowLeft = WINDOW_LEFT;
	wpWindowTop = WINDOW_TOP;
	
	//wpWindowLeft = (unsigned long) ( (smScreenWidth - wsWindowWidth)/2 );
	//wpWindowTop = (unsigned long) ( (smScreenHeight - wsWindowHeight)/2 );  	
}

/*
 ******************************************
 * shellShell:
 *     Constructor.
 *     Não emite mensagens.
 */
void shellShell (){
	
	int i=0;
	int j=0;
	
	// Internas.
	
    shellStatus = 0;
    shellError = 0;
	
	
	//
	// ## Inicializando as estruturas de linha ##
	//
	
	//inicializamos com espaços.
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		LINES[i].pos = 0;
	};
	
	
	
	// Deve ser pequena, clara e centralizada.
	// Para ficar mais rápido.
	
	// #importante:
	// O aplicativo tem que confiar nas informações 
	// retornadas pelo sistema.
		
	// Usar o get system metrics para pegar o 
	// tamanho da tela.
	
	//inicializa as metricas do sistema.
	shellInitSystemMetrics ();
	
    //inicializa os limites da janela.
	shellInitWindowLimits();
	
	//inicia o tamanho da janela.
	shellInitWindowSizes();
	
	//inicializar a posição da janela.
	shellInitWindowPosition();
 
 
    //
	// initi visible area.
	// #todo: criar função para isso
	
	textTopRow = 0;
	textBottomRow = 24;
	
	//limits.
	//quantidade de linhas de colunas da janela.
	//na verdade deve ser da área de cliente.
    wlMaxColumns = (wsWindowWidth/8);    
    wlMaxRows = (wsWindowHeight/8);         
 
    if ( wlMaxColumns < wlMinColumns )
	{
	    wlMaxColumns = wlMinColumns;	
	}
		
	if ( wlMaxRows < wlMinRows )
	{
		wlMaxRows = wlMinRows;
	}
	
	//...	

	//
	// Setup buffers.
	//
	

	// #inportante:
	// #bugbug: Não podemos deixar o stdout como screenbuffer 
	// pois no screen buffer os caracteres tem atributos ...
	// e no stdout podemos ter um arquivo normal ...
	//ou saída normal que servirá de entrada para  
	//outro processo.
    // reiniciando as variáveis na estrutura do output
	
	//obs: Ao cancelarmos isso o std volta a ser 
	//o antigo e já configurado stdout.
	//stdout->_base = &screen_buffer[0];
	//stdout->_ptr = stdout->_base;
	//stdout->_cnt = PROMPT_MAX_DEFAULT;
	//stdout->_file = 1;
	//stdout->_tmpfname = "shell_stdout";
	
	//...	
	
	// Obs:
	// prompt[] - Aqui ficam as digitações. 

	shellClearBuffer();

	
	//shellBufferMaxColumns = DEFAULT_BUFFER_MAX_COLUMNS;
	//shellBufferMaxRows    = DEFAULT_BUFFER_MAX_ROWS;
	
	//buffersize = (shellBufferMaxColumns * shellBufferMaxRows);
	

	
	//
	// @todo: E o fluxo padrão. Quem configurou os arquivos ???
	//        o kernel configuroru???
	//
	
	// Número máximo de colunas e linhas.
	g_columns = wlMaxColumns;  // 80;
	g_rows = wlMaxRows;        // 25;
    //...
	
	
	for ( i=0; i<WORKINGDIRECTORY_STRING_MAX; i++ ){
		current_workingdiretory_string[i] = (char) '\0';
	};
	
    sprintf ( current_workingdiretory_string, 
	    SHELL_UNKNOWNWORKINGDIRECTORY_STRING );    
	
	//...
	
//done:

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
};


/*
 *************
 * shellInit:
 *     Inicializa o Shell.  
 *
 *     #bugbug: 
 *     Essa rotina começa escrever na janela com o foco de entrada. 
 * Mas um outro aplicativo solicitou o foco de entrada e essa rotina 
 * esta terminando de escrever mas agora na janela do outro aplicativo.
 *
 * @todo: Inicializar globais e estruturas.
 */
 
int shellInit ( struct window_d *window ){
	
	//#bugbug 
	//o ponteiro do argumento pode ser inválido, pois 
	//é uma variáveç local.
	
	int PID;
	int PPID;
	int ActiveWindowId = 0;
	int WindowWithFocusId = 0;
	void *P;
	//int CurrentVolumeID = 0;
		
	char buffer[512];
	
	
	// #bugbug:
    //     Esse ponteiro de estrutura está em kernel mode. 
	//     Não podemos usá-lo.
	
	//??
	//stream status
	shell_info.stream_status = 0;
	
		
	//
	// ## buffer support ##
	//
	
	
    /* 
	Line buffer output for stderr. 
    If your machine doesn't have either of setlinebuf or setvbuf,
    you can just comment out the buffering commands, and the shell
    will still work.  It will take more cycles, though. 
	*/
	
/*++ HAVE_SETLINEBUF */	
/*
#if defined (HAVE_SETLINEBUF)
    setlinebuf(stderr);
    setlinebuf(stdout);
#else
# if defined (_IOLBF)
    setvbuf( stderr, (char *) NULL, _IOLBF, BUFSIZ );
    setvbuf( stdout, (char *) NULL, _IOLBF, BUFSIZ );
# endif
#endif
*/ 
/*-- HAVE_SETLINEBUF */
	
	
	// Antes dessa função ser chamada, o foco foi setado 
	// na janela do aplicativo.
	// Test: Não mechemos no cursor nesse momento, deicharemos 
	// a função SetFocus configurar o curso.
	// Não mostraremos o prompt, somente depois dos testes de inicialização.
	
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
	
	if ( (void *) window == NULL )
	{
	    printf("shellInit: window fail.\n"); 
		
	} else {
		
		// Nesse momento temos um ponteiro válido,
		// mas infelismente não podemos testar outros elementos 
		// da estrutura.
		
		APISetFocus ( window );
		
		// mensagens !!
		
#ifdef SHELL_VERBOSE		
		printf("shellInit: Starting shell.bin ...\n");
		printf("shellInit: Running tests ...\n");
#endif
		
	};
	
	
	//
	// Obtendo informações sobre a janela ativa.
	//
	
	//Active window
	ActiveWindowId = (int) APIGetActiveWindow ();
	
	//valor de erro
	if ( ActiveWindowId == (-1) ){
		
	    printf("shellInit: ERROR getting Active window ID\n");	
	}	
	
#ifdef SHELL_VERBOSE			
	printf("ActiveWindowId={%d}\n", ActiveWindowId );
#endif
	
	// Obtendo informações sobre a janela com o foco de entrada.

	// Focus.
	WindowWithFocusId = (int) APIGetFocus();
	
	//valor de erro
	if ( WindowWithFocusId == (-1) ){
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
	printf("wlMaxColumns={%d} \n", wlMaxColumns );
	printf("wlMaxRows={%d} \n", wlMaxRows );	
#endif
	
	
	//
	// Process support.
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
	

	// @todo: 
	// O que tevemos fazer aqui é pegar informações sobre o processo Shell
	// e coloca-las na tela.
	

	// @todo: Criar na API uma rotina de inteface que use essa chamada.
	// ex: APIGetPID().

	
	//PID = (int) APIGetPID();
	
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0 );
	if ( PID == (-1) ){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0 );
	if ( PPID == (-1) ){
	    printf("ERROR getting PPID\n");	
	}
  
    //Mensagem ...
	//printf("Starting SHELL.BIN ... PID={%d} PPID={%d} \n", PID, PPID );
	
	
	// @todo: Criar processos processos:
	//     E.BIN, F.BIN, G.BIN, A.BIN, B.BIN, C.BIN, D.BIN
 	//     (Mermaids) Usados para testes.

//#ifdef SHELL_VERBOSE			
//	printf("Creating processes ...\n");
//#endif

/*
    printf("Creating process ...\n");	
	//D.:)
	P = (void *) apiCreateProcess ( 0x400000, PRIORITY_HIGH, "NEW-PROCESS");
	if ( (void *) P==NULL )
	{
		printf ("Fail creating process D :)\n");
	};
*/	
	
	
#ifdef SHELL_VERBOSE
    
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
	//system("xxfailxx");
	//...
#endif
	
	
#ifdef SHELL_VERBOSE			
	//API.
	apiSystem("test");    
    apiSystem("ls");
	apiSystem("start");
	//apiSystem("xxfailxx");
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
	
	
	// ## prompt string support ##
	shellInitializeWorkingDiretoryString ();

	
// Done.
	
done:
		
	if (interactive == 1)
	    loginCheckPassword ();


	// @todo:
	// Gerenciamento do heap do processo. ??
	
	// @todo:
	// Chamar rotinas da biblioteca que ofereçam informações sobre 
	// o heap oferecido pela biblioteca.
	// Obs: A rt foi inicializada logo acima.
	
	
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
	*/
	
	
	if ( interactive == 1 )
	    shellPrompt ();
	
	
	
	// #bugbug 
	// Vamos retornar sem mostrarmos a janela 
	// ou podemos confiar no ponteiro passado via argumento 
	// e efetuarmos o refresh da janela.
	
    //refresh_screen ();
	
	//isso deve mostrar as string
	//Se é que isso é preciso, pois 
	//a rotina de printf mostra as strings.
	//>>vamos tentar sem isso e confiarmos na função printf.
	//apiShowWindow(window);
	
    return (int) 0;
};


//cancelado;
//agora esta el login.c
int shellCheckPassword ()
{
    return -1; //deletar
}


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
void shellSetCursor ( unsigned long x, unsigned long y ){
	
    //
	// Coisas do kernel.
	//
	
	//setando o cursor usado pelo kernel base.	
    apiSetCursor (x,y);
	
//Atualizando as variáveis globais usadas somente aqui no shell.
//setGlobals:	
    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;	
	
	
	//
	// Coisas do screen buffer.
	//
    
	move_to ( x, y);
};


/*
 *******************************************
 * shellThread:
 *     Um thread dentro para testes.
 */
void shellThread (){
	
	printf("\n");
	printf("$\n");
	printf("$$\n");
	//printf("$$$\n");
    printf("#### This is a thread ####\n");
	//printf("$$$\n");
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
void shellShowExperienceMenu (){

    printf (experience_banner);			
    //printf (help_banner);	
}

//help message
void shellShowTestsMenu (){

    printf (tests_banner);			
    //printf (help_banner);	
}


//drawing a tree
void shellTree (){
	
    printf (tree_banner);	
};


/*
 **************************************************
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicialização de stdio, 
 * prompt foi definido como stdin->_base.
 *
 */
void shellPrompt (){
	
	int i;
	
	//Linpando o buffer de entrada.
	for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
		prompt[i] = (char) '\0';
	}
	
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_status = 0;
	prompt_max = PROMPT_MAX_DEFAULT;  

    printf("\n");
    printf("[%s]", current_workingdiretory_string );	
	printf("%s", SHELL_PROMPT );
};


/*
 * shellClearBuffer:
 *     Limpa o buffer da tela.
 */
void shellClearBuffer (){
	
	int i = 0;
	int j = 0;
	
	//inicializamos com espaços.
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		LINES[i].pos = 0;
	};
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

//#importante: vamos mostrar todo o buffer de words, a partir 
//da posição atual do cursor, forçando um scroll

//Isso é só um teste.
void shellShowScreenBuffer (){
	
    shellRefreshVisibleArea();
};


/*
 * shellTestLoadFile:
 *     Carrega um arquivo de texto no buffer e mostra na tela.
 */
void shellTestLoadFile (){
	
	FILE *f;
	
	int Ret;
	int i=0;
	int ch_test;
	
	int pos;
	
	//#importante:
	//precisa ser arquivo pequeno.
	
	
	f = fopen ("gramado.txt","rb");  	
	
	//pequeno
	//f = fopen ("init.txt","rb");  
	
	//grande
	//f = fopen ("init.txt","rb");  	
	
    if( f == NULL )
	{
		printf("fopen fail\n");
		return;
	}else{
		//printf("fopen ok\n");
	};	
	
	
	//#test 
	//testando com um arquivo com texto pequeno.
	//enviando para o buffer de words, 
	//obs: agora tem rotinas de refresh.
	
	while (1)
	{
		ch_test = (int) getc (f); 
		
		if( ch_test == EOF )
		{
			//printf("\n");
			//printf("EOF reached :)\n");
			goto done;
		
		} else {   			
		    
			shellInsertNextChar ( (char) ch_test ); 		
	    };
	};	
	

 
done:
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
 
void shellTestThreads (){
	
    //void *T;	
	
	// Obs: 
	// As threads criadas aqui são atribuídas ao processo PID=0.
	// @todo: 
	// No kernel, quando criar uma thread ela deve ser atribuída
    // ao processo que chamou a rotina de criação.	
	
	printf("shellTestThreads: Creating threads..\n");
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
    
	void *ThreadTest1;	
	
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

    printf("shellTestThreads: Tentando executar uma thread..\n");	
	
	ThreadTest1  = (void *) apiCreateThread ( (unsigned long) &shellThread, 
	                        (unsigned long) (&threadstack1[0] + (2*1024) - 4), 
							"ThreadTest1" );
	
	if ( (void *) ThreadTest1 == NULL )
	{	
	    printf("shellTestThreads: apiCreateThread fail \n");	
	    die("ThreadTest1");
	}
	
	// # executando #
	
	// #importante:
	// Lá no kernel, isso deve selecionar a thread para 
	// execussão colocando ela no estado standby.
	// Logo em seguida a rotinad e taskswitch efetua o spawn.
	
	apiStartThread(ThreadTest1);
	exitCriticalSection();
	
	
	printf("shell: Tentando executar um thread [ok]..\n");
	
	//permitir que o shell continue.
};


/*
 *************************************
 * shellClearScreen:
 *     Limpar a tela do shell.
 *     usada pelo comando 'cls'.
 */
 
void shellClearScreen (){

	struct window_d *w;
	unsigned long left, top, right, bottom;
	
    //desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
	
	shellClearBuffer ();
	

	
	w = (void *) shell_info.terminal_window;
	
	if ( (void *) w != NULL )
	{
		//#bugbug
		//redraw está falhando. 
		
		//#BUGBUG
		//Isso está fazendo redraw da janela main inteira, com frame e tudo.
		//sendo que deveríamos estar trabalhando somente com a área de cliente.
		
		//Para issp precisamos antes criar mais uma janela dentro da janela main
		//como já fizemos antes.
		
		APIredraw_window ( w, 1 );
	};
	
	//printf("#breackpoint");
	//while(1){}

	
    left = (terminal_rect.left/8);
    top = (terminal_rect.top/8);
	
    shellSetCursor ( left, top );


	// Copiamos o conteúdo do screenbuffer para 
	// a área de cliente do shell.
	// obs: A outra opção seria repintarmos a janela.

    //shellRefreshScreen ();	
	
	//shellRefreshVisibleArea();
	
	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


/*
 *******************************************
 * shellRefreshScreen:
 * 
 *     #importante 
 *      
       #OBS
       NA VERDADE SE REFERE AO REFRESH DA ÁREA DE CLIENTE DO SHELL.
 *
 *     Copia o conteúdo do (screen_buffer) buffer de output 
 * para a tela. (dentro da janela). 
 * ## Acho que se trata de stdout.
 * É uma memória VGA virtual com caractere e atributo.
 * na hora de efetuar refresh precisamos considerar o atributo 
 * para sabermos a cor do caractere e de seu background.
 */
void shellRefreshScreen (){

	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	int i=0;
	int j=0;
	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    //LINES[i].CHARS[j] = (char) 'x';
		    //LINES[i].ATTRIBUTES[j] = (char) 7;
	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		printf ("\n");
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
	
};


// a intenção aqui é fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void shellRefreshLine ( int line_number ){
	
    
	if ( line_number > wlMaxRows )
		return;	
	
	int lin = (int) line_number; 
	int col = 0;  
	
	
#ifdef SHELL_VERBOSE		
	//#debug
	printf("shellRefreshScreen:\n");
#endif 

	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	
	shellSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf( "%c", LINES[lin].CHARS[col] );
	};
	
};


// a intenção aqui é fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void shellRefreshChar ( int line_number, int col_number ){
	
	if ( col_number > wlMaxColumns || line_number > wlMaxRows )
		return;
	
	shellSetCursor ( col_number, line_number );

	//Mostra um char do screen buffer.
	printf( "%c", LINES[line_number].CHARS[col_number] );	
};


//refresh do char que está na posição usada pelo input.
void shellRefreshCurrentChar (){
	
	printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
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

void shellScroll (){
	
	//reajustando a área visível do buffer 
 

	//desliga o cursor
	//system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	

    testChangeVisibleArea();	//desloca a área visível usando delta.
	shellRefreshVisibleArea();
	
	//#todo:posicionar cursor
	
	//reabilita o cursor
	//system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


static void save_cur (void){
	
	textSavedCol = textCurrentCol;
	textSavedRow = textCurrentRow;
};


static void restore_cur (void){
	
	textCurrentCol = textSavedCol;
	textCurrentRow = textSavedRow;
};


//line feed
static void lf (void){
	
	//enquanto for menor que o limite de linhas, avança.
	if ( textCurrentRow+1 < wlMaxRows )
	{
		textCurrentRow++; 
		return;
	}
	
	//#todo: Scroll up;
	//scrup();
};


// ??
//voltando uma linha.
static void ri (void){
	
	//if ( screen_buffer_y > top ){
		
		// Volta uma linha.
	//	screen_buffer_y--;
	//	screen_buffer_pos = (screen_buffer_pos - columns); 
	//	return;
	//}
	
	//@todo:
	//scrdown();
};


//carriege return
static void cr (void){
	
    textCurrentCol = 0;
};


static void del (void){
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) '\0';
	LINES[textCurrentRow].ATTRIBUTES[textCurrentCol] = 7;
};


// Insere um caractere sentro do buffer.
void 
shellInsertCharXY ( unsigned long x, 
                    unsigned long y, 
				    char c )
{
	
	if ( x >= wlMaxColumns || y >= wlMaxRows ){
		
		return;
	}

	LINES[y].CHARS[x] = (char) c;
	LINES[y].ATTRIBUTES[x] = 7;
};


 // Insere um caractere sentro do buffer.
char 
shellGetCharXY ( unsigned long x, 
                 unsigned long y )
{
	
	if ( x >= wlMaxColumns || y >= wlMaxRows ){
		
		return;
	}

	return (char) LINES[y].CHARS[x];
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


//usado para teste de scroll.
//imprime varias vezes o char indicado.
void testScrollChar ( int c ){
	
    int i;
	
    for ( i=0; i < (wlMaxColumns*26); i++ )
	{
	    //se chegamos no limite do screen_buffer
		//...
		shellInsertNextChar ((char) c);	
	}		
};


/*
 ***************************************************
 * shellInsertNextChar:
 *     Coloca um char na próxima posição do buffer.
 *     Memória de vídeo virtual, semelhante a vga.
 */
void shellInsertNextChar (char c){
		
	//cursor da linha
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
	
	//refresh
	shellRefreshCurrentChar();
	
	//update
	textCurrentCol++;
	
	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			shellScroll ();
			while(1){}
		}
	}
	
	LINES[textCurrentRow].pos = textCurrentCol;
	LINES[textCurrentRow].right = textCurrentCol;
};



void shellInsertCR (){
    
	shellInsertNextChar ( (char) '\r' );		
};


void shellInsertLF (){
	
	shellInsertNextChar ( (char) '\n' );
};


void shellInsertNullTerminator (){
	
	shellInsertNextChar ( (char) '\0' );	
};



/*
 ***************************************************
 * shellTestMBR:
 *     Testar a leitura de um setor do disco.
 *     Testaremos o setor do mbr.
 *
 */
void shellTestMBR (){
	
	unsigned char buffer[512];
	
	enterCriticalSection(); 
	
	//message 
	printf("shellTestMBR: Initializing MBR test ...\n");
	
	//read sector
	system_call ( SYSTEMCALL_READ_LBA, 
	              (unsigned long) &buffer[0],  //address 
				  (unsigned long) 0,           //lba
				  (unsigned long) 0);
				 
	
	exitCriticalSection();   
	
	//
	// exibe o conteúdo carregado.
	//
	
	//?? address #bugbug
	printf("Signature: [ %x %x ] \n" , buffer[0x1FE], buffer[0x1FF] );
	
	
	//
	// @todo: Sondar cada elemento do MBR para 
	// confirmar a presença.
	//
	
//done:
	//printf("done");
	//refresh_screen(); //??deletar.
	//return;
};



/*
 * move_to:
 *    Move o cursor de posição.
 *    Assim o próximo char será em outro lugar da janela.
 */
void move_to ( unsigned long x, unsigned long y )
{	
	if ( x > wlMaxColumns || y > wlMaxRows )
		return;
	
	//screen_buffer_x = x;
	//screen_buffer_y = y;
	
	textCurrentCol = x;
	textCurrentRow = y;
	
	//screen_buffer_pos = ( screen_buffer_y * wlMaxColumns + screen_buffer_x ) ;
};


//show shell info
void shellShowInfo (){
	
	int PID, PPID;
	
    printf(" # shellShowInfo: #\n");
	
	
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	if( PID == (-1)){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
	if( PPID == (-1)){
	    printf("ERROR getting PPID\n");	
	}
  
	printf("Process info: PID={%d} PPID={%d} \n", PID, PPID );
	printf("wlMaxColumns={%d} \n", wlMaxColumns );
	printf("wlMaxRows={%d} \n", wlMaxRows );	
	//...
};


//metrics
void shellShowMetrics (){
	
    //reinicializa as metricas do sistema.
	//isso pega os valores e coloca nas variáveis globais.
	
	shellInitSystemMetrics();
	
	
	printf("\n");  
	printf(" # shellShowMetrics: # \n");
	
	printf("screenWidth={%d} screenHeight={%d}\n",smScreenWidth, smScreenHeight );
	printf("cursorWidth={%d} cursorHeight={%d}\n", smCursorWidth, smCursorHeight );
	printf("mousepointerWidth={%d} mousepointerHeight={%d}\n", 
	    smMousePointerWidth, smMousePointerHeight );
	printf("charWidth={%d} charHeight={%d}\n", smCharWidth, smCharHeight );	
	//...
	
    printf("Done\n");	
};

//show system info
void shellShowSystemInfo (){
	
	int ActiveWindowId;
	int WindowWithFocusId;
	
	printf(" # shellShowSystemInfo: #\n");
	
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
void shellShowWindowInfo (){
	
    int wID;	
	//
	// #bugbug.
	// Testando a estrutura de janela.
	// A janela foi criada pelo kernel e copiamos o ponteiro 
	// da estrutura para um ponteiro em user mode.
	// Podemos ter erros de memória com essas operações.
		
	printf("\n");	
	printf(" # shellShowWindowInfo #\n");
	
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
	printf("Window info: \n");	
    printf("l={%d} t={%d} w={%d} h={%d}\n", 
	    wpWindowLeft, wpWindowTop,
		wsWindowWidth, wsWindowHeight );

													  
	//Obs: isso funcionou. setando o cursor.
	//if( terminal_rect.left > 0 && terminal_rect.top > 0 )
	//{											  
    //    shellSetCursor( (terminal_rect.left/8), (terminal_rect.top/8) );													  
	//};
		
		
	wID = (int) system_call ( SYSTEMCALL_GETTERMINALWINDOW, 0, 0, 0 ); 
	
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
shellSendMessage ( struct window_d *window, 
                   int msg, 
				   unsigned long long1, 
				   unsigned long long2 )
{
	return (unsigned long) shellProcedure ( window, msg, long1, long2 );
};


//copia bytes	
void shell_memcpy_bytes( unsigned char *Dest, 
                         unsigned char *Source,
                         unsigned long Length )
{
    while (Length--)
        *Dest++ = *Source++;
};


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
void shellExit (int code){
	
	//@todo ...
	exit (code);
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
void shellUpdateWorkingDiretoryString ( char *string ){
	
	if ( pwd_initialized == 0 )
	{
		goto fail;
	}else{
		
        if( (void *) string == NULL )
	    {
		    goto fail;
	    }else{
	    
	        // ## separador ##
		    //strcat( current_workingdiretory_string, 
			//    SHELL_PATHNAME_SEPARATOR );		
		
	        // ## separador ##		
		    strcat ( current_workingdiretory_string, string );	

		    strcat( current_workingdiretory_string, 
			    SHELL_PATHNAME_SEPARATOR );				
		
            //Atualizar no gerenciamento feito pelo kernel.
	        system_call( 175, (unsigned long) string,
		        (unsigned long) string, (unsigned long) string );		
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
void shellInitializeWorkingDiretoryString (){
	
	//get info
	
	//test: get current volume id.
	current_volume_id = (int) system_call ( 171, 0, 0, 0 );
	
	//global usada para string do nome do volume.
	current_volume_string = (char *) SHELL_VOLUME1_STRING;
	
	
    //  ## volume list ##
	
	//root:
    //primeiro colocamos a string que indica 
	//a lista de volumes.
    sprintf( current_workingdiretory_string, SHELL_VOLUMELIST_STRING ); 
	
	
	// ## separador ##

	//root:/
	strcat( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
	
	//  ## volume root dir ##
	
	//root:/volumex
	strcat( current_workingdiretory_string, current_volume_string );

	
	// ## separador ##

	//root:/volumex/
	strcat( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
    pwd_initialized = 1;
};





// atualiza a variável global para id de diretório atual de trabalho.
void shellUpdateCurrentDirectoryID ( int id ){
	
	g_current_workingdirectory_id = (id);
};


//lista informações sobre os processos.
void shellTaskList (){
	
	// opções:
	// +podemos pedir para o kernel listar as informações.
	// +podemos solicitar as informações uma a uma.
	// Obs: A segunda opção é a mais trabalhosa, mas 
	// da oportunidade para testarmos as chamadas ao kernel e 
	// explorarmos as possibilidades que cada informação traz 
	// individualmente.
	
	
	// testando posicionamento de strings
	
	unsigned long X, Y;
	int PID;

	//Pega o PID do processo atual.
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0 );
	
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
	
};


void shellShowPID (){
	
	printf("Current PID %d\n", 
	    (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0) );
};


void shellShowPPID (){
	
	printf("Current PID %d\n", 
	    (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0) );
};


void shellShowUID (){
	
	printf("Current UID %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTUSERID, 0, 0, 0) );
};


void shellShowGID (){
	
	printf("Current GID %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTGROUPID, 0, 0, 0) );
};


void shellShowUserSessionID (){
	
	printf("Current user session %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTUSERSESSION, 0, 0, 0) );
};


void shellShowWindowStationID (){
	
	printf("Current window station %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTWINDOWSTATION, 0, 0, 0) );
};


void shellShowDesktopID (){
	
	printf("Current desktop %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTDESKTOP, 0, 0, 0) );
};

void shellShowProcessHeapPointer (){
	
	int id = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0); 
	
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
	                                                id, 0, 0 );
	
	printf("Current Process heap pointer address %x\n", 
	    (unsigned long) heap_pointer );
};


void shellShowKernelHeapPointer (){
	
	int id = 0;  //Id do processo kernel. 
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
	                                                id, 0, 0 );
	
	printf("Current Process heap pointer address %x\n", 
	    (unsigned long) heap_pointer );
};


//mostra informações sobre o disco atual.
void shellShowDiskInfo (){
	
	//@todo: atualizar api.h
	system_call ( 251, 0, 0, 0 );
};

//mostra informações sobre o volume atual.
void shellShowVolumeInfo (){
	
	//@todo: atualizar api.h
	system_call ( 252, 0, 0, 0 );
};

//mostrar informações gerais sobre a memória.
void shellShowMemoryInfo (){
	
	system_call ( SYSTEMCALL_MEMORYINFO, 0, 0, 0 );
};

//mostrar informações gerais sobre a memória.
void shellShowPCIInfo (){
	
    system_call ( SYSTEMCALL_SHOWPCIINFO, 0, 0, 0 );	
};

//mostrar informações gerais sobre a memória.
void shellShowKernelInfo (){
	
	system_call ( SYSTEMCALL_SHOWKERNELINFO, 0, 0, 0 );
};



/*
 ***************************************************
 * shell_fntos:
 *     Rotina interna de support.
 * isso deve ir para bibliotecas depois.
 * não tem protótipo ainda.
 * Credits: Luiz Felipe
 */
void shell_fntos (char *name){
	
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];
	
    //transforma em maiúscula
	while ( *name && *name != '.' )
	{
        if(*name >= 'a' && *name <= 'z')
            *name -= 0x20;

        name++;
        ns++;
    }

    // aqui name[0] é o ponto.
	// então constroi a extensão.
	for ( i=0; i < 3 && name[i+1]; i++ )
	{
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    };

    while (ns < 8)
	{
        *name++ = ' ';
        ns++;
    };

    for ( i=0; i < 3; i++ )
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
                                    const char *arg2,  //arg(endereço da linha de comando)
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
				              (unsigned long) arg2,    //arg(endereço da linha de comando)
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
	//int q;
	
	switch (msg)
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
	
//done:

    return (int) 0;
};


void die (char *str){
	
	printf("die: %s",str);
	//@todo
	fprintf(stderr,"%s\n",str);
	exit(1);
};



/*
//isso foi para stdlib.c
void *xmalloc( int size){
	
    register int value = (int) malloc(size);
    if(value == 0)
        die ("xmalloc fail.\n");
//done:  
    return (void *) value;
};
*/

char *concat( char *s1, char *s2, char *s3 ){
	
    int len1 = (int) strlen(s1);
    int len2 = (int) strlen(s2);
    int len3 = (int) strlen(s3);
  
    char *result = (char *) xmalloc( len1 +len2 +len3 +1 );

    strcpy( result, s1);
    strcpy( result +len1, s2 );
    strcpy( result +len1 +len2, s3 );
  
    *( result +len1 +len2 +len3 ) = 0;

//done:  
  return (void *) result;
};


/* error */
void error ( char *msg, char *arg1, char *arg2 ){
	
    fprintf(stderr, "shell: ");
    fprintf(stderr,"%s %s %s", msg, arg1, arg2);
    fprintf(stderr, "\n");
};


void fatal ( char *msg, char *arg1, char *arg2 ){
	
  error(msg, arg1, arg2);
  //delete_temp_files ();
  exit(1);
};


char *save_string ( char *s, int len )
{
  register char *result = (char *) xmalloc (len + 1);

  bcopy (s, result, len);
  result[len] = 0;
  
  return result;
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
 * 
 * 	#todo:
 *	Essa função deve chamar o interpretador de script
 *
 * IN: Nome do arquivo.
 */
 
int shellExecuteThisScript ( char *script_name ){
	
    
 	//#todo:
	//Essa função deve chamar o interpretador de script	
	
	FILE *script_file;	
	int i;
	
	// Aqui temos que carregar o arquivo de script indicado 
	// nos argumentos.
	
	printf("shellExecuteThisScript:\n");	
	printf("Initializing script ...\n");
    printf("CurrentFile={%s}\n",script_name);
	
	
	// #ok 
    // Carregaremos o arquivo com o nome passado por argumento.	
	
    script_file = fopen (script_name,"rw");
	
	if ( (void *) script_file == NULL )
	{	
		printf ("shellExecuteThisScript: Can't open script file!\n");
		die("*");
	};
	
	//#Ok
	//atualizando a linha de comandos no prompt[], stdin.
	
	//#obs 
	//Talvez não precise copiar o conteúdo, e sim apenas 
    //mudar os ponteiros.
    
    //#todo 	
	//Fazer isso ao invés de copiar.
	//stdin = script_file;
	
	for ( i=0; i< 128; i++ )
	{	
		stdin->_base[i] = script_file->_base[i];
	}
	
	
	//
	// ## parser ##
	//
	
	//#todo
	//Chamaremos o parser, que num loop chamará o lexer yylex()
	
	//parser();
	
	
	//EOF_Reached = EOF;

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
	
	// #importante:
	// Vamos checar se o pathname é absoluto ou relativo.
	// +Se tiver barra, significa que o pathname é absoluto e 
	// começa no diretório raiz do volume do sistema. root:/volume1/
	// +Se começar por root:/ também é absoluto.
	// +Pathname relativo é somente aquele que é apenas um nome 
	// de arquivo dentro do diretório atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	// $/ é o diretório raiz do volume do sistema.
	// $v/ é o diretório raiz do vfs.
	
int absolute_pathname ( char *string ){
	
	// Checar nulidade.
    if( !string || !strlen(string) )
        return (0);

	//Começa por barra.
	//Então essa barra significa o diretório raiz do 
	//volume do sistema. Ex: root:/volume1/
    if( *string == '/' )
        return (1);

	
	// .
    // É absoluto, pois estamos determinando o diretório.
	// Se for ponto, avança em seguida.
	if( *string++ == '.' )
    {
        // ./
		// Significa que se trata do diretório atual
		if( (!*string) || *string == '/' )
	        return (1);

        // ..
		// ../
		// Significa que se trata do diretório pai.
		// Se for ponto, avança em seguida.
		// se for barra ou nada é absoluto.
		//obs: o nada nesse caso significa que foi digitado apenas '..'
		if( *string++ == '.' )
	        if( !*string || *string == '/' )  
	            return (1);
		
		// ?? Continua ...
		// Se estamos aqui, significa que é um ponto que não é seguido 
		// de outro ponto ou barra.
		//?? deveríamos falhar com a opção 2. 
		return (2);
    }
	
	// root:/
	if ( *string == 'r' )
	{
	    if ( string[0] == 'r' &&
             string[1] == 'o' &&
             string[2] == 'o' &&
             string[3] == 't' &&
             string[4] == ':' &&
             string[5] == '/' )
	    {
		    return (1);		 
		}


        return (2);		
	};
	
	// #teste:
	// invendando esquema.
	// Volume do sistema.
	// O número do volume do sistema é um padrão.
	if ( *string == '$' )
	{
		
	    // root:/volume1/ = $/ (volume do sistema)	    
		if ( string[0] == '$' && 		
		     string[1] == '/' )
	    {
		    return (1);		 
		}
		
	    // root:/volume1/ = $v/ (vfs)
		if ( string[0] == '$' &&
             string[1] == 'v' && 		
		     string[2] == '/' )
	    {
		    return (1);		 
		}

        return (2);		
	};	
	
//fail:
//Não é absoluto.
	
    return (int) 0;
};



//inicializaremos o supporte a pathname
int shellInitPathname (){
	
	int i;
	
	if (pathname_initilized == 1)
	{
		return (int) 0;
		//goto done;
	}
	
	for ( i=0; i<PATHNAME_LENGHT; i++ ){
		
		pathname_buffer[i] = (char) '\0';
	}
	
	pathname_lenght = 0;
	
	//...
	
//done:	

    pathname_initilized = 1;
	return (int) 0;
};




 
//inicializaremos o supporte a filename
int shellInitFilename (){
	
	int i;
	
	if (filename_initilized == 1)
	{	
		return (int) 0;
		//goto done;
	}
	
	for ( i=0; i<FILENAME_LENGHT; i++ )
	{
		filename_buffer[i] = (char) '\0';
	}
	
	filename_lenght = 0;
	
    	
	//...
	
//done:
	
    filename_initilized = 1;
	return (int) 0;
};


/* 
 Remove the last N directories from PATH.  
 Do not leave a blank path.
 PATH must contain enough space for MAXPATHLEN characters. 
 Credits: bash 1.05
 */
void shell_pathname_backup ( char *path, int n ){
	
    register char *p = path + strlen(path);
	
	unsigned long saveN = (unsigned long) n;

    //#debug 
	//printf("%s", path);
	
	if (*path)
        p--;

    while (n--)
    {
        while(*p == '/')
	        p--;

        while(*p != '/')
	        p--;

        *++p = '\0';
    };
	
	//@todo: Criar em kernelmode uma roptina que 
	//que faça o mesmo que a shell_pathname_backup 	
    //Atualizar no gerenciamento feito pelo kernel.
	
	system_call ( 176, (unsigned long) saveN, (unsigned long) saveN, 
        (unsigned long) saveN );			
    	
};



// Imprime todas as strings de um vetor de ponteiros.
// Isso vai ser usado pelo echo.

void shell_print_tokenList ( char *token_list[], char *separator ){
	
	int i;
	char *token;
	
	token = (char *) token_list[0];
	
	if ( token == NULL )
	    return;
	    //goto fail;
	
	
	//token = (char *) tokenList[i];
		
	//	if( token == NULL ){
		
    //#todo: Limits.		
    
	for ( i=0; i,128; i++ )
    {
		token = (char *) token_list[i];

	    if ( token == NULL )
	        return;
		
		if ( strncmp ( (char *) token_list[i], "echo", 4 ) == 0 )
		    continue;	
		
		printf ("%s", token_list[i] );
		printf ("%s", separator );
    };
};


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
int is_bin ( char *cmd ){
	
    char *p;
	
	p = cmd;
	
	int len = strlen (p);
    
	if( len <= 4 ) 
		return 0;
	
    p += len - 4;
    
	if ( *p++ != '.' ) 
		return 0;
	
    if ( strncmp ( (char *) p, "bin", 3 ) == 0 ){
	    return 1;	
	}

    return 0;
};


/* Check if it's a .sh1 file */
int is_sh1 ( char *cmd ){
	
    char *p;
	
	p = cmd;
	
	int len = strlen (p);
    
	if ( len <= 4 ) 
		return 0;
	
    p += len - 4;
    
	if ( *p++ != '.' ) 
		return 0;
	
    if ( strncmp ( (char *) p, "sh1", 3 ) == 0 ){
	    return 1;	
	}
	
    return 0;
};


/* 
 * Give version information about this shell.  */

void show_shell_version (){
	
    printf ("%s, version %s.%s \n", shell_name, dist_version, build_version );
}


//testando a rotina de salvar um arquivo.
//estamos usando a API.
int shell_save_file (){
	
	//
	// #importante:
	// Não podemos chamar a API sem que todos os argumentos estejam corretos.
	//
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	int Ret;
	
	char file_1[] = "t5: Arquivo \n escrito \n em \n user mode. \n";
	
	char file_1_name[] = "FILE1UM TXT";
	//char file_1_name[] = "TESTSAVETXT";
	
	printf("shell_save_file: Salvando um arquivo ...\n");
	
	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
	
	//
	// Lenght in bytes.
	//
	
	len = (size_t) strlen (file_1);

	if (len <= 0)
	{
	    printf ("shell_save_file:  Fail. Empty file.\n");
        return (int) 1;		
	}
	
	if (len > 2048)
	{
	    printf ("shell_save_file:  Limit Fail. The  file is too long.\n");
        return (int) 1;		
	}
	
    //
    // Number os sectors.
    //
	
	number_of_sectors = (unsigned long) ( len / 512 );
	
	if ( len > 0 && len < 512 ){
	    number_of_sectors = 1; 
    }		
	
	if ( number_of_sectors == 0 )
	{
	    printf ("shell_save_file:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;				
	}
	
	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
	if ( number_of_sectors > 4 )
	{
	    printf ("shell_save_file:  Limit Fail. (%d) sectors so save.\n",
		    number_of_sectors );
        return (int) 1;				
	}
	
	/*
	 ## test
    Ret = (int) apiSaveFile ( file_1_name,        //name 
                              number_of_sectors,  //number of sectors.
                              len,                //size in bytes			
                              stdin->_base,      //address
                              0x20 );             //flag
	*/
	
	
    Ret = (int) apiSaveFile ( file_1_name,  //name 
                              number_of_sectors,            //number of sectors.
                              len,            //size in bytes			
                              file_1,       //address
                              0x20 );       //flag		
				
	//if (Ret == 0)
	
	printf("shell_save_file: done\n");	
	
	return (int) Ret;
};


//salvando uma string.
int save_string2 ( char string[], char file_name[] ){
	
	// #importante:
	// Não podemos chamar a API sem que todos os argumentos estejam corretos.
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	int Ret;
	
	//char file_1[] = "t5: Arquivo \n escrito \n em \n user mode. \n";
	
	//char file_1_name[] = "FILE1UM TXT";
	//char file_1_name[] = "TESTSAVETXT";
	
	printf ("save_string2: Salvando um arquivo ...\n");
	
	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
	
	//
	// Lenght in bytes.
	//
	
	len = (size_t) strlen (string);

	if (len <= 0)
	{
	    printf ("save_string2:  Fail. Empty file.\n");
        return (int) 1;		
	}
	
	if (len > 2048)
	{
	    printf ("save_string2:  Limit Fail. The  file is too long.\n");
        return (int) 1;		
	}
	
    //
    // Number os sectors.
    //
	
	number_of_sectors = (unsigned long) ( len / 512 );
	
	if ( len > 0 && len < 512 ){
	    number_of_sectors = 1; 
    }		
	
	if ( number_of_sectors == 0 )
	{
	    printf ("save_string2:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;				
	}
	
	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
	if ( number_of_sectors > 4 )
	{
	    printf ("save_string2:  Limit Fail. (%d) sectors so save.\n",
		    number_of_sectors );
        return (int) 1;				
	}
	
	/*
	 ## test
    Ret = (int) apiSaveFile ( file_1_name,        //name 
                              number_of_sectors,  //number of sectors.
                              len,                //size in bytes			
                              stdin->_base,      //address
                              0x20 );             //flag
	*/
	
	
    Ret = (int) apiSaveFile ( file_name,  //name 
                              number_of_sectors,            //number of sectors.
                              len,            //size in bytes			
                              string,       //address
                              0x20 );       //flag		
				
	//if (Ret == 0)
	
	printf("save_string2: done\n");	
	
	return (int) Ret;
};



/*
 Credits: gcc 0.9 
 Read chars from INFILE until a non-whitespace char
 and return that.  
 
 Comments, both Lisp style and C style, are treated 
 as whitespace.
 
 Tools such as genflags use this function.  
 */
/* 
int
read_skip_spaces (infile)
    FILE *infile;
{
    register int c;
    while (c = getc (infile))
    {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\f')
	    ;
            else if (c == ';')
	             {
	                 while ((c = getc (infile)) && c != '\n') ;
	             }
                 else if (c == '/')
	                  {
	                      register int prevc;
	                      c = getc (infile);
	                      //if (c != '*')
	                          //dump_and_abort ('*', c, infile);
	  
	                      prevc = 0;
	                      while (c = getc (infile))
	                      {
	                          if (prevc == '*' && c == '/')
		                      break;
	                          prevc = c;
	                      }
	                  }
                      else break;
    }
    return c;
};
*/

/* 
 Credits: gcc 0.9
 Read an rtx code name into the buffer STR[].
 It is terminated by any of the punctuation chars 
 of rtx printed syntax.  
 */
/*
static void
read_name (str, infile)
     char *str;
     FILE *infile;
{
  register char *p;
  register int c;

  c = read_skip_spaces(infile);

  p = str;
  while (1)
    {
      if (c == ' ' || c == '\n' || c == '\t' || c == '\f')
	break;
      if (c == ':' || c == ')' || c == ']' || c == '"' || c == '/'
	  || c == '(' || c == '[')
	{
	  ungetc (c, infile);
	  break;
	}
      *p++ = c;
      c = getc (infile);
    }
  *p = NULL;
}
*/

//Qual será a linha que estará no topo da janela.
void textSetTopRow ( int number )
{
    textTopRow = (int) number; 	
};

int textGetTopRow ()
{
    return (int) textTopRow; 	
};

//Qual será a linha que estará na parte de baixo da janela.
void textSetBottomRow ( int number )
{
    textBottomRow = (int) number; 	
};

int textGetBottomRow ()
{
    return (int) textBottomRow; 	
};



void clearLine ( int line_number )
{
    int lin = (int) line_number; 
	int col = 0;  
	
	int Offset = 0; //Deslocamento dentro do screen buffer.
	
	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	
	shellSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf( "%c", screen_buffer[Offset] );
		    
		Offset++; //ignora o atributo.
	    Offset++;
	};
	
    //shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};


//um teste mostrando todas as linhas do boffer de linhas.
void testShowLines()
{
	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	int i=0;
	int j=0;
	
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    //LINES[i].CHARS[j] = (char) 'x';
		    //LINES[i].ATTRIBUTES[j] = (char) 7;
	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		printf ("\n");
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


//mostra a área visível dentro do buffer de linhas.
void shellRefreshVisibleArea (){
	
	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	
	//
	//seta o cursor no início da janela.
	//
	
	unsigned long left, top, right, bottom;
 
    left = (terminal_rect.left/8);
    top = (terminal_rect.top/8);
	
    shellSetCursor ( left, top );
	

	//
	// efetua o refresh do char atual, que agora é o primeiro 
	// depois os outros consecutivos.
	//
	
	int i=0;
	int j=0;
	
	//textTopRow = 3;
	//textBottomRow = 3 + 25;
	
	if ( textTopRow > textBottomRow )
	{
		printf("shellRefreshVisibleArea: textTopRow fail");
	}
	
	//toda a área visível.
	//for ( i=0; i<25; i++ )	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{	
	        //refresh
            printf ("%c", LINES[i].CHARS[j] );						
		}
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


void testChangeVisibleArea()
{
	textTopRow += textWheelDelta;
	textBottomRow += textWheelDelta;	
}


void updateVisibleArea( int direction )
{
    switch (direction)
    {
	    case 0:
	        textTopRow += textWheelDelta;
	        textBottomRow += textWheelDelta;			
            break; 		
			
	    case 1:
	        textTopRow -= textWheelDelta;
	        textBottomRow -= textWheelDelta;					
            break; 		
	}	
}



//rotina de testes de socket
void shellSocketTest()
{
	//#todo: isso precisa ser um porteiro de estrutura.
	void *socketHandle;
	
	unsigned long iplong;
	unsigned long port; //short
	
	unsigned char ip[4];
	
    printf("\n");
    printf("shellSocketTest: Testing socket stuff ...\n");

	
	//
	// Creating socket
	//
	
	printf("Creating socket ...\n");
	socketHandle = (void *) system_call ( 160, (unsigned long) 0xC0A80164, (unsigned long) 0, (unsigned long) 0x22C3 );
	
	printf("Updating socket ...\n");
	system_call ( 163, (unsigned long) socketHandle, (unsigned long) 0xC0A80165, (unsigned long) 0x22C2 );
	
	printf("Getting ip from socket ...\n");
	iplong = (unsigned long) system_call ( 161, (unsigned long) socketHandle, (unsigned long) socketHandle, (unsigned long) socketHandle);
	
	printf("Getting port from socket ...\n");
	port = (unsigned long) system_call ( 162, (unsigned long) socketHandle, (unsigned long) socketHandle, (unsigned long) socketHandle);
	
	//
	// output
	//
	unsigned long tmp;
	
	tmp = iplong;
	ip[3] = (char) ( tmp & 0x000000FF ); 
	
	tmp = iplong;
	tmp = (tmp >> 8);
	ip[2] = (char) ( tmp & 0x000000FF );
	
	tmp = iplong;
	tmp = (tmp >> 16);
	ip[1] = (char) ( tmp & 0x000000FF );
	
	tmp = iplong;
	tmp = (tmp >> 24);
	ip[0] = (char) ( tmp & 0x000000FF );
	
	printf("\n");
	//printf("iplong=%x\n",iplong);
	printf ("Socket: ( %d.%d.%d.%d:%d )\n", 
		ip[0], ip[1], ip[2], ip[3], port );
	
	printf("done\n");
};


