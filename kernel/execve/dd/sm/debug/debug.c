/*
 * File: debug.c
 *
 * Modulo Debug.
 * MB - Módulos incluídos no Kernel Base.
 *	
 * Descrição:
 *     Kernel Debugger.
 *     Arquivo princial do módulo debug do executive do kernel.
 *     Checar se há falhas no sistema. 
 *     Como um dr watson.
 * 
 * Obs:
 *     As funções aqui são usadas pelo kernel.
 *     Mas pode haver um aplicativo que utilizem essas funções.
 *
 * Obs:
 *     @todo: Começar a análise pela estrutura 'platform' e todo
 * o que está dentro dela.
 *
 * This is a spiritual quote.
 *
 * Versão: 1.0, 2015, 2016.
 */

 
#include <kernel.h>


// Variáveis internas.
//int debugStatus;
//int debugError;
//...

//
// # This is a spiritual quote.
// Estruturas para fases de inicialização.
// De uso interno no debug.
// Just for fun. (user's mental model)
// ux4, ux3, ux2, ux1
// hal/microkernel/executive/gramado
// thinking, logic, creativity, action
//

typedef enum {
   MYTHIC,  	
   ROMANTIC,   
   REALIST,   
   NATURALIST,   
}MindType_t;


struct Mind_d
{
    unsigned long Mythic;
	unsigned long Romantic;
	unsigned long Realist;
	unsigned long Naturalist;	
};
struct Mind_d Mind;


//Internas.
void InitMind();
void SetMind(int Type);



/*
 teste de stress na criação de threads.
int debug_test_threads();
int debug_test_threads()
{
	//if( (void*) IdleThread == NULL ){
		//
	//};	
};
*/


/*
//Construtor.
void InitMind()
{
	//if((void*) Mind == NULL)
    //    return;     
			
    Mind.Mythic = 0;
	Mind.Romantic = 0;
	Mind.Realist = 0;
	Mind.Naturalist = 0;	
};
*/

/*
void SetMind(int Type)
{
	//if((void*) Mind == NULL)
    //    return;
		 
    switch(Type)
    {
    	case MYTHIC:     Mind.Mythic = 1;      break;
    	case ROMANTIC:   Mind.Romantic = 1;    break;
		case REALIST:    Mind.Realist = 1;     break;
		case NATURALIST: Mind.Naturalist = 1;  break;
    	
		default:
		    InitMind();
    		break;
	};
};
*/

/*
 * debug_check_inicialization:
 *     Checar se o kernel e os módulos foram inicializados.
 *     Checa o valor das flags.
 *     checar todos contextos de tarefas válidas.
 */
int debug_check_inicialization (){
	
    int Status = 0;
	
	// Check phase.
	if ( KeInitPhase != 3 ){
	   Status = 1;
	   
	   printf("sm-debug-debug_check_inicialization: KeInitPhase phase={%d}\n",
	       KeInitPhase);
	   
	   goto fail;
	};
	
    //
    // check personas
    //	

	// gramado.
	/*  @todo: Inda não implementado
	if(Initialization.gramado != 1){
	   Status = 1;
	   printf("debug_check_inicialization: gramado fail!\n");
	   goto fail;
	};
	*/
	
	
	//SetMind(NATURALIST);
	
	// Executive.
	if( Initialization.executive != 1 )
	{
	   Status = 1;
	   printf("sm-debug-debug_check_inicialization: executive\n");
	   goto fail;
	};
	//SetMind(REALIST);
	
	
	// Microkernel.
    if( Initialization.microkernel != 1 )
	{
	   Status = 1;
	   printf("sm-debug-debug_check_inicialization: microkernel\n");
	   goto fail;
	};
	//SetMind(ROMANTIC);
	
	// Hal.
    if( Initialization.hal != 1 )
	{
	   Status = 1;
	   printf("sm-debug-debug_check_inicialization: hal\n");
	   goto fail;
	};
	//SetMind(MYTHIC);
	
	
	//More?!
	
// Done! 
done:
    return (int) Status;
fail:
	die(); 
};




/*
 * debug_check_drivers:
 *    Checar se os drivers estão inicializados.
 */
int debug_check_drivers (){
	
	int Status = 0;
    
	if(g_driver_hdd_initialized != 1){
	    //erro
	};
	
	if(g_driver_keyboard_initialized != 1){
	    //erro
	};
	
    if(g_driver_pci_initialized != 1){
	    //erro
	};
	
    if(g_driver_rtc_initialized != 1){
	    //erro
	};
	
    if(g_driver_timer_initialized != 1){
	    //erro
	};
	
//done:

    return (int) Status;
};


/*
 ********************************************
 * debug_breakpoint:
 *     Para a execução do sistema.
 *     @todo: isso pode ir para o arquivo debug.c.
 */
void debug_breakpoint (){
	
    printf("sm-debug-debug_breakpoint:\n");
	die();
};


//retorna um checksum dado um buffer e um tamanho.
unsigned long debug_compute_checksum( unsigned char *Buffer, unsigned long Lenght)
{
    unsigned long CheckSum = 0;

    while(Lenght > 0){	
		CheckSum = CheckSum + (unsigned long) *Buffer++;
	    Lenght--;	
	};
	return (unsigned long) CheckSum;
};



/*
 * debug:
 *     Checa por falhas depois de cumpridas as três fases de inicialização.
 */
int debug (){
	
	int Status;
		
	//printf("debug: Starting..\n");
	
	//Contrutor.
	//InitMind();
	
	//
	// Checa inicialização. Fases, variáveis e estruturas.
	//
	
	Status = (int) debug_check_inicialization();
	if(Status == 1){
	   printf("sm-debug-debug: debug_check_inicialization\n");
	   die();
	};
	
    // 'processor' struct.	
	if( (void *) processor == NULL ){
	    printf("sm-debug-debug: processor\n");
		die();
	};

	//Check drivers status. 
	//( Ver se os principais drivers estão inicializados )
	debug_check_drivers();
	
	
	/*
	 * @todo: 
	 *     Checar se existe componentes do sistema como mbr, root, fat 
	 * e arquivos e programas básicos do sistema.
	 *
	 */
	 
	 
	/* 
	 * @todo: 
	 *     Checar por falhas no sistema de arquivos.
	 */
	 
	 
	 
	/*
     * @todo:	
	 *     Checar por falhas nas estruturas de tarefas.
	 */

    //
	// Antes do logon só tem a Thread idle. 
	// Checar a estrutura da PID 0.
	// 
	 
	//if( (void*) threadList[0] == NULL ){
	//    printf("debug fail: TID 0!\n");
	//	refresh_screen();
	//	while(1){}
	//};
	
	

	 
	//
    //
    //
	
	//...

//done:

    //printf("debug:OK!\n");
    //printf("debug: Done.\n");	
	
	return (int) 0; 
};


/*
int debugInit()
{}
*/

//
// End.
//

