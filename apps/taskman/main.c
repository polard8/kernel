/*
 * TASKMAN - Task manager application for Gramado 0.3.
 * (c) Copyright 2015-2017 - Fred Nora.
 *
 * File: main.c 
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
 
 
/* api */ 
#include "api.h"

/* libc */
#include <stdio.h>
#include <stddef.h>

/* taskman */
#include "taskman.h"


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
	
	do{
	    --t;
	}while(t > 0);

};


/*
 * tmProbeProcessList:
 *     Sonda para ver se o processo está presente e é válido.
 *     Se retornar 1234 (MAGIC) é um processo válido.
 *
 */
int tmProbeProcessList (int pid){
	
	//if(pid < 1){
	//    return (int) -1; //error.	
	//};
	
	return (int) system_call ( SYSTEMCALL_88, pid, pid, pid );
};

 
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
	
	return (int) 0;
};


/*
 *****************************************************************
 * tmProc:
 *     Procedimento de janela do Task Manager.
 *     O procedimento intercepta algumas mensagens e as mensagens de sistema
 * são passadas para o procedimento do sistema na opção default.
 */
int tmProc ( int junk, 
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
	
//done:

    return (int) 0;
};


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
	
//done:	
	//return;
};


/*
 * tmDrawBar:
 *     Desenhar uma barra em modo texto.
 *    #bugbug Não é esse o ambiente que estamos. @todo
 */
int tmDrawBar (int color){
	
    unsigned int i = 0;	
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
	
//done:	
    return (int) 0; 
};


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
	
	//return;
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
	
	return ( (size_t) i );
};


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
	
    //return;	
};


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
};


void progress_bar_test (){
    
	DoSome();
};



/*
 * tmInit:
 *     Inicializações.
 */
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

    return (int) 0;
};



/*
 **********************************************
 * appMain:
 *     Função principal do Task Manager.
 * 
 * @todo:
 *     +... 
 */
int appMain ( int argc, char *argv[] ){
	
	//int Status;	
	int Flag;
	void *P;
    struct window_d *hWindow;
	
	// #importante
	// buffer de mensagens	
	unsigned long buffer[5];
	
    int PID;
	
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
	printf("appMain: Initializing taskman server..\n");
#endif	
	
	//o kernel deverá associar o PID a um magic.
	
	
    PID = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0 );
	
	enterCriticalSection(); 
	system_call ( 115,                 
	    (unsigned long) &buffer[0], //ponteiro para o vetor de mensagem.  
		(unsigned long) 1234,       //acoplar taskman.  
		(unsigned long) PID );      //magic para taskman.
	exitCriticalSection(); 	

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
	// ## LOOP ##
	//
	
	while (listening)
	{
		
		//pega uma mensagem com 4 elementos.
		enterCriticalSection(); 
		system_call ( 115,                 //Número do serviço invocado pelo servidor
		    (unsigned long) &buffer[0],        
			(unsigned long) 12345678,    //magic para pegar mensagens.          
			(unsigned long) PID );       //PID do taskman.      
		exitCriticalSection(); 
			
			
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
		//pause();
		//pause();
		//pause();
		//pause();
		//pause();
		//pause();
		//asm("pause");
		//exit(0);
	};
	
	
	//
	// #todo:
	// Nesse momento o servidor parou de ouvir por mensagens,
	// devemos então efetuarmos uma rotina de finalização.
	//

    //
	// Opção: Tratar os argumentos recebidos.
	//
	
	
	//#debug
//debugStuff:

    // Uma mensagem de sinal de vida.
	apiBeginPaint();
	    //(type, string1, string2)
	    MessageBox( 1, "TASKMAN.BIN:", "Initializing..");
	apiEndPaint();
	
	
	
	//Debug breakpoint.
	//while(1){}
	
	
	// Obs:
	//  **** O message box apresenta mensagens corretamente. ****
	// O desafio agora é enviar mensagens para a área de cliente 
	// do utilitário TaskMan.
	// mensagens de erro serão apresentadas via MessageBox.
	
    //Initializing ...	
//initializing:	

	tmInit();  
	
	//
	// Criando os processos que compoem o Security Control:
	// ===================================================
	//
	// LOGON  - Logon. 
	// LOGOFF - Logoff
	// OM     - Object Manager. 
	// SS     - System Security.
	//

//	
// Obs: O object manager controlará algumas permissões iniciais
// que habilitam os usuários a utilizarem recursos do sistema.
// Quem controla na verdade os objetos é o kernel base, que consede
// acesso aos objetos. Permitindo que grupos, usuários, processos e 
// e threads denham acesso aos recursos do sistema. 
//	
//creatingSecurityControl:	
	
	//Logon.
	P = (void *) apiCreateProcess( 0x400000, PRIORITY_HIGH,"LOGON");
	if ( (void *) P == NULL  ){
	    MessageBox( 1, "TASKMAN.BIN:", "Fail creating process LOGON");		
		while(1){}
	};

	//Logoff.
	P = (void *) apiCreateProcess( 0x400000, PRIORITY_HIGH,"LOGOFF");
	if( (void *) P == NULL  ){
	    MessageBox( 1, "TASKMAN.BIN:", "Fail creating process LOGOFF");		
		while(1){}
	};
	
	//Object Manager. 
	//(Pertence ao Security Control).
	P = (void *) apiCreateProcess( 0x400000, PRIORITY_HIGH,"OM");
	if( (void *) P == NULL  ){
	    MessageBox( 1, "TASKMAN.BIN:", "Fail creating process OM");		
		while(1){}
	};

	//System Security.
	//(Pertence ao Security Control).
	P = (void *) apiCreateProcess( 0x400000, PRIORITY_HIGH,"SS");
    if( (void *) P == NULL ){ 
	    MessageBox( 1, "TASKMAN.BIN:", "Fail creating process SS");		
		while(1){}
	};
	
	// Obs:
	// Os processos criados qui ainda são um conjunto de testes.
	// Estamos criando os processos que compoem o security control,
	// mas não estamos associando nenhuma imagens à eles.
	// @todo: Podemos testar a qui a criação de algumas threads
	// associadas à esses processos.
	// Obs: Quando criamos um processo, uma thread inicial deve ser criada.
	
    /*
     * @todo: 
	 *     O recurso de criar janelas está razoavelmente funcionando. 
	 * Mas não criaremos janelas ainda. Pois o recurso de janelas está 
	 * sendo testado e aprimorado no utilitário shell. 
	 * Na verdade convém testar tudo no shell.
	 * Obs: No futuro, criaremos aqui a janela principal do utilitário TaskMan.
	 *
	 */
	 
	 
	// 
    // Create window.
	//
	
	/*
	
	//Tentando enviar strings pra propria janela.
	
	//@todo: Obter o ponteiro para a janela que repressenta a área de trabalho.
	//Ou deveria ter uma flag que indicasse, que a janela deve ter como janela mae a área
	//de trabalho...
	
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1,"TaskMan Window",     
                                       2, 2, 128, 64,    
                                       0, 0, 0 , COLOR_WINDOW );
	
	if( (void*) hWindow != NULL )
	{
        //Registrar.
	    APIRegisterWindow(hWindow);
	
	    //Configurar como ativa.
	    //APISetActiveWindow(hWindow);
	
	    //Setar foco.
	    //APISetFocus(hWindow);
		
		//Sondando processos. criando ícones.
	    //@todo #bugbug esta pintando na area de cliente de outro processo.
		//tmCreateTaskBar();
	    
        
        //...		
	};	
	*/

	
    //
	// @todo: 
	//     Fazer alguns testes de chamadas ao sistema.
	// Logo após os teste, pararemos num loop que funcionará 
	// como pegador de mensagens na fila de mensagens da janela 
	// do processo.
	//
    
	
	//Show info: 
	// As chamadas ao sistema que servem para mostrar informações
	// são consideradas seguras, perfeitas para essa fase de desenvolvimento
	// do sistem. Apesar de ainda termos problemas com exibição das mensagens 
	// na janela correta.
	
	
	//PCI info
    //system_call( SYSTEMCALL_SHOW_PCI_INFORMATION, 0, 0, 0 );
				   
	//kernel info			   
    //system_call( SYSTEMCALL_SHOW_KERNEL_INFORMATION, 0, 0, 0 );	
		
	
	//Testing String
    // ?? do que se trata isso ??
    // Me parece um bom teste.	
	//system_call( SYSTEMCALL_DRAWTEXT, 0,  0, (unsigned long) "/TASKMAN.BIN Testing strings...");
		
		
	//Refresh screen
	//system_call( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0);
	
	
	
   	//
	// * Hang.
	//
	
//getmessageLoop:	
	
	// Debug:
	
	apiBeginPaint();
	    //(type, string1, string2)
	    MessageBox( 1, "TASKMAN:", "Get message loop");	
	apiEndPaint();
    
	while (1)
	{
        //
        // Test: 		
        // Aproveitando para testar chamadas.		
		// Usando o loop para cauasr um pouco de stress, com muitas chamadas.
		//
		
		//system_call( SYSTEMCALL_NULL, 0, 0, 0 );
        //system_call( SYSTEMCALL_DEAD_THREAD_COLLECTOR, 0, 0, 0 );
		//...
		
		//
		// Sinal de vida.
		// Pintando caracteres no canto superior esquerdo da janela.
		//
		
		//#bugbug ... isso impediu do procedimento de janela do kernel 
		//receber mensagens do teclado. Talvez outro procesimento foi acionado.
		//#bugbug: Cria tantas janelas assim pode nos causa problemas...
		//pois as janelas ainda não são delatadas...
		//MessageBox( 1, "Message", "Testing TASKMAN application.");
		
		
	    //tmSetCursor(0,0);		
		//printf("\\");
		//tmSleep(12345);

	    //tmSetCursor(0,0);		
		//printf(" "); 
		//tmSleep(12345); 		

	    //tmSetCursor(0,0);	
		//printf("|");
		//tmSleep(12345);

	    //tmSetCursor(0,0);		
		//printf(" "); 
		//tmSleep(12345); 		

	    //tmSetCursor(0,0);	
		//printf("/");
		//tmSleep(12345);

	    //tmSetCursor(0,0);		
		//printf(" "); 
		//tmSleep(12345); 		

	    //tmSetCursor(0,0);	
		//printf("-"); 
		//tmSleep(12345);

	    //tmSetCursor(0,0);		
		//printf(" "); 
		//tmSleep(12345); 		

	    //tmSetCursor(0,0);	
		//printf("|"); 
		//tmSleep(12345);

	    //tmSetCursor(0,0);		
		//printf(" "); 
		//tmSleep(12345); 		

	    //tmSetCursor(0,0);	
		//printf("-");
		//tmSleep(12345);

	    //tmSetCursor(0,0);		
		//printf(" "); 
		//tmSleep(12345); 

        //progress_bar_test();	

		//
		//taskmanagerStatus
		//
		
		//if(Flag == 1234){
		//	goto done;
		//}
		
		//if(Flag == 1234){}
		//if(Flag == 1234){}
		//if(Flag == 1234){}
		//...
	};	
	
   
    //
    // Obs: 
	// O exit(0) funcionou corretamente no teste.
    // Mas não usaremos exit(0) ainda pois temos poucas threads no sistema.
	//
	
done:   
   //exit(0);         //Obs: Não usar por enquanto. 
   return (int) 0;    //Obs: Retornar com um valor para cr0.s ou head.s.
};



//
// End.
//

