/*
 * File: main.c 
 *
 * Environment:
 *     Gramado Core - TASKMAN
 *     ring 3.
 * 
 * Purpose:  
 *     It's a taskman process for Gramado Core environment.
 *
 * Descrição:
 *     Arquivo principal do aplicativo Task Manager em user mode. 
 *     O nome do utilitário é TASKMAN.BIN.
 *     É um aplicativo de 32bit, em user mode, para gerenciar o sistema.
 *     
 * Atribuições:
 *     Mostrar estatísticas e status sobre processos e threads, realizar
 * operações em processos e threads como criar fechar, etc ...
 *    
 * *IMPORTANTE: ESSE É O GERENCIADOR DE TAREFAS , ELE PODE SOLICITAR
 * MUITAS INFORMAÇÕES AO KERNEL AJUDANDO O DESENVOLVEDOR A TRABALHAR
 * ESSAS CHAMADAS. É IDEAL PARA TESTES.
 *
 *     Tipo: P3 - Processos em ring3, User Mode.	
 *          
 * Obs:
 *     +O entry point está em head.s.
 *     +...
 * @todo: + Incluir bibliotecas disponíveis.
 *        + Dar algum sinal de vida na tela.
 *
 * WIN23
 * #define COLOR_LITBUTTON  0x00E0E0E0
 * #define COLOR_LTGRAY     0x00C0C0C0
 * #define COLOR_GRAY       0x00808080
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016~2018 - Updates.
 *     ...
 */


//
// # Includes #
//
 
 
 
#include "tm.h"
 
/* 
//api 
#include "api.h"

//libc 
#include <stdio.h>
#include <stddef.h>

//taskman 
#include "taskman.h"
*/

/* defines */
#define MAGIC (1234)
#define TASKMANAGER_BUFFER_SIZE 512


//
// Variáveis internas.
//

int listening = 1;

int taskmanagerStatus;
int taskmanagerError;

//
// Buffer support.
//

char taskmanagerBuffer[TASKMANAGER_BUFFER_SIZE];  
int taskmanagerBufferPos;
//...


//FILE *taskmanOutput;



//interna
void __debug_print (char *string)
{
    gramado_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}




static inline void pause (void){
	
    asm volatile ("pause" ::: "memory"); 
}; 


/* REP NOP (PAUSE) is a good thing to insert into busy-wait loops. */
static inline void rep_nop (void){
	
	__asm__ __volatile__ ("rep;nop": : :"memory");
};


#define cpu_relax()  rep_nop()


//
// Protótipos de funções internas.
//
 
 
//Protótipo do procedimento de janela.
int 
tmProc( int junk, 
        int message, 
        unsigned long long1, 
        unsigned long long2 );


//Protótipos de funções internas.
void tmUpdateStatus();

void tmSetCursor(unsigned long x, unsigned long y);


/*
tmCreateTaskBar: 
    Barra para mostrar informações.
	
Atribuições:
    +Cria uma barra em baixo na tela com ícones que representam os processos 
da lista de processos, ou que indique atividade de processos.
    +Sondar se o processo existe na lista de processos lá no kernel.
    +Para cada processo encontrado na lista, cria uma janelinha onde ficará um 
    ícone que representa o processo.
    +...
	
Obs: 
    No futuro, pegaremos essa lista inteira de uma vez só, atravéz de área 
compartilhada e usaremos a lista aqui em user mode.
    
 */
int tmCreateTaskBar(); 
 
int tmProbeProcessList(int pid);

void tmSleep(unsigned long ms); 

void progress_bar_test();

//Inicializações.
int tmInit();



/*
 * sleep:
 *     Apenas uma espera, um delay.
 */

void tmSleep (unsigned long ms){

    unsigned long t = (ms*512);


    do {
       --t;
    } while(t > 0);

}


/*
 * tmProbeProcessList:
 *     Sonda para ver se o processo está presente e é válido.
 *     Se retornar 1234 (MAGIC) é um processo válido.
 */

int tmProbeProcessList (int pid){
	
	//if(pid < 1){
	//    return (int) -1; //error.	
	//};
	
	return (int) system_call ( SYSTEMCALL_88, pid, pid, pid );
}

 
/*
 * tmCreateTaskBar:
 *     ??
 */
int tmCreateTaskBar (){
	
	int i;
	int j=0;
	
	int Magic;
	
	g_cursor_x = 0;
	g_cursor_y = 0;
	
	//@todo: Variável para número máximo.
	for ( i=0; i<256; i++ )
	{
	    Magic = (int) tmProbeProcessList(i);
	    
		if (Magic == MAGIC)
		{
			
			    //APICreateWindow( 1, 1, 1,"Process",     
                //                 0, j, 20, 20,    
                //                 0, 0, 0 , COLOR_WINDOW );
		        // j = j+22;
				
			
			//@TODO: #BUGBUG: Esta bagunçando tudo,
			//pintando strings na área de cliente de otro processo.
			printf ("process magic %d\n", i );	
		};
		//Nothing
	};
	
	
	//nothing
	
	return 0;
}




/*
 *****************************************************************
 * tmProc:
 *     Procedimento de janela do Task Manager.
 *     O procedimento intercepta algumas mensagens e 
 * as mensagens de sistema são passadas para o procedimento 
 * do sistema na opção default.
 */
 
int 
tmProc ( int junk, 
         int message, 
         unsigned long long1, 
         unsigned long long2 )
{
    //Filtrar mensagem.
	
	switch (message)
	{
		case 1000:
		    printf ("taskman server - message 1000 \n");
			break;
	
		case 2000:
		    printf ("taskman server - message 2000 \n");
			break;

		case 3000:
		    printf ("taskman server - message 3000 \n");
		    break;

		case 4000:
		    printf ("taskman server - message 4000 \n");
		    break;
			
	    //...
	};

	//Nothing.

    return 0;
}



/*
 * tmUpdateStatus:
 *
 */

void tmUpdateStatus (){

    int CpuStep;
    int ActiveWindow;
    int wFocus;


	//@todo: O número dos serviços estão desatualizados.
	
	//pega o valor do step do processador. quantas vezes ele rodou tarefa.
	//CpuStep = system_call(83,0,0,0);
	
	//pega a janela com o foco de entrada.
	//wFocus = system_call(47,0,0,0);
	
	//peaga o numero da janela ativa.
	//ActiveWindow = system_call(45,0,0,0);
	
	
	//tmDrawBar(0x7f);
	tmSetCursor (1,0);
		
	printf("Task Manager: wFocus[%d] | ActiveWindow[%d] | CpuStep[%d]",
	    wFocus, ActiveWindow, CpuStep );
		
	//Cursor.
	tmSetCursor(0,1);

	//...
}


/*
 * tmDrawBar:
 *     Desenhar uma barra em modo texto.
 *    #bugbug Não é esse o ambiente que estamos. @todo
 */
 
int tmDrawBar (int color){

    unsigned int i = 0;	
    
    // #bugbug
    // O que é isso ???
    // Memória compartilhada ?
    
    char *vm = (char *) 0x00800000;  //g_current_vm; //phis=0x000B8000; 


	// @todo: Usar alguma função de uma biblioteca GUI em user mode.
	
    while (i < ( SCREEN_WIDTH * 2) ) 
    { 
        vm[i] = 219; 
        i++; 
        
        vm[i] = color; 
        i++; 
    };
	
	//Cursor.
	tmSetCursor(0,0);



    return 0; 
}


/*
 * tmSetCursor:
 *     Configurando o cursor. (stdio.h).
 */
 
void tmSetCursor (unsigned long x, unsigned long y){
	
	// #BUGBUG: Aconteceu uma pagefault depois de incluir essa função. 
	// Vou testar sem ela.
	
    //Atualizamos as variáveis dentro da estrutura da janela com o foco de entrada.
    //system_call( SYSTEMCALL_SETCURSOR, x, y, 0);	
	

//Atualizando as variáveis globais usadas somente aqui no shell.
//setGlobals:	

    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;	
};


//
// strlen:
//     Tamanho de uma string.
// 

size_t tmstrlen (const char *s){
	
    size_t i = 0;
	
	for ( i=0; s[i] != '\0'; i++ ){ 
	    ; 
	};
	
	return (size_t) i;
}


//
// ================= funny progress bar ===================
//


//
// DoProgress:
//     Credits: Progress bar source code found on 
//     codeproject.com/Tips/537904/Console-simple-progress 
//
void DoProgress ( char label[], int step, int total ){
	
    //progress width
    const int pwidth = 72;

    //minus label len
    int width = pwidth - tmstrlen( label );
    int pos = ( step * width ) / total ;
   
    int percent = ( step * 100 ) / total;

    //set green text color, only on Windows
    //SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN );
    printf("%s[", label);

    //fill progress bar with =
	int i;
    
	for ( i=0; i < pos; i++ ){
		printf("%c", '=');
    };
	
    //fill progress bar with spaces
    printf("% *c", width - pos + 1);
    printf("] %3d%%\r", percent);

    //reset text color, only on Windows
    //SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), 0x08 );
}


void DoSome (){
	
    int total = 1000;
    int step = 0;

    while ( step < total ){
		
		tmSleep(5000);    // Do some action.
        
		step+=1;
        
		DoProgress("Loading: ",step,total);
    };
	
    // Nothing.

    printf("\n");
}


void progress_bar_test ()
{
    DoSome();
}



/*
 * tmInit:
 *     Inicializações. */

int tmInit (){
	
	taskmanagerStatus = 0;
	taskmanagerError = 0;
	//taskmanagerBuffer = '\0'
	taskmanagerBufferPos = 0;
	
	//#DEBUG
	//printf("T");
	//printf("taskman: testing strings \n");
	//tmSetCursor(8,8); 
	//printf("taskman: and cursor. \n");
	
	//...

    return 0;
}



/*
 **********************************************
 * appMain:
 *     Função principal do Task Manager.
 * 
 * @todo:
 *     +... 
 */

int main ( int argc, char *argv[] ){


    int Flag;
    void *P;

    struct window_d *hWindow;

	// #importante
	// buffer de mensagens	
    unsigned long buffer[5];

    int PID;


    __debug_print ("Gramado Core: Initializing taskman process ...\n");

	//@todo:
    //+pegar o id do processo e chamar uma rotina 
    //para inicializar o processo como o 
    //servidor de gerenciamento de tarefas.
    //obs: o kernel registrará o servidor de grenciamento de 
    //de tarefas, e apenas um gerenciador de tarefas poderá existir.

	// ## IMPORTANTE ##
    //115
    //esse é o serviço usado pelos servidores 
    //para dialogar com o kernel.


#ifdef TASKMAN_VERBOSE
    printf ("taskman is alive\n");
#endif

	//window, x, y, color, string.
    apiDrawText ( NULL, 
        0, 16, 
        COLOR_RED, "Gramado Core: Taskman is alive!" );
    refresh_screen ();


	// #bugbug
	// Essa conexão está obscura.
	// precisamos criar mecanismos mais transparentes.

	//o kernel deverá associar o PID a um magic.
	
    PID = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0 );

    //++
	enterCriticalSection(); 
	system_call ( 115,                 
	    (unsigned long) &buffer[0], //ponteiro para o vetor de mensagem.  
		(unsigned long) 1234,       //acoplar taskman.  
		(unsigned long) PID );      //magic para taskman.
	exitCriticalSection(); 	
    //--


    //reason?	
	//O servidor chamará o kernel para se acoplar 
	//e para se desacoplar..
	
	// #debug 
	// Não há problemas ao mostrar o message box, 
	// só estamos tirando ele para não incomodar
	// enquanto trabalhamos no outro aplicativo.
	
	//O servidor vai solicitar mensagens para o kernel 
	//e indicar o número do seu processo.
	//se o número do processo for um nómeo registrado na lista 
	//de servidores, então o kernel coloca a mensagem 
	//no vetor passado pelo servidor.
	
	//
	// # LOOP #
	//

    while (listening)
    {
		//++
		//pega uma mensagem com 4 elementos.
		enterCriticalSection(); 
		system_call ( 115,                 //Número do serviço invocado pelo servidor
		    (unsigned long) &buffer[0],        
			(unsigned long) 12345678,    //magic para pegar mensagens.          
			(unsigned long) PID );       //PID do taskman.      
		exitCriticalSection(); 
		//--


		//msg. Se existe uma mensagem válida.	
		if ( buffer[1] != 0  )
		{
			//isso funcionou.
			printf(".message={%d}\n", buffer[1]);

            //# mensagem de teste #
			if (  buffer[1] == 123  )
			{
				printf ("message 123: Hello from server PID={%d}\n", PID );
			};
			
			
			//#todo:
			// Chamar o procedimento de janelas. (diálogo)
			
            tmProc ( (int) buffer[0], 
			         (int) buffer[1], 
			         (unsigned long) buffer[2], 
			         (unsigned long) buffer[3] );
			
		};		
				
		cpu_relax();
		pause();
		pause();
	};

    //
    // Fail.
    //
    
    return -1;
}



//
// End.
//

