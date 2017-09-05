/*
 * File: main.c 
 *
 * Descrição: 
 *     Arquivo principal de IDLE.BIN.
 *     IDLE.BIN é um processo com apenas uma thread.
 *     IDLE.BIN é um aplicativo de 32bit em user mode. 
 *
 *     Esse programa deverá ser chamado sempre que o sistema estiver ocioso,
 * ou com falta de opções viáveis. Então esse programa deve ficar responsável 
 * por alguma rotina de manutenção do equilíbrio de sitema, ou por gerência de 
 * energia, com o objetivo de poupar energia nesse momento de ociosidade.
 *
 * O processo idle pode solicitar que processos de gerencia de energia entrem em
 * atuação. Pois a chamada do processo idle em si já é um indicativo de ociosidade
 * do sistema. Pode-se também organizar bancos de dados, registros, memória, buffer,
 * cache etc.
 *
 *     O sistema pode configurar o que esse processo faz quando a máquina 
 * está em idle mode. Quando não há nenhum processo pra rodar ou a cpu se 
 * encontra ociosa, pode-se usar alguma rotina otimizada presente neste 
 * programa. Parece que a intel oferece sujestões pra esse caso, não sei.
 * 
 * Obs: O entry point está em head.s
 *      Agora idle pode fazer systemcalls. 
 *
 * @todo: Criar argumento de entrada.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */
 
 
//
// Includes.
// 
 
#include "api.h"      //api.
#include "stdio.h"    //libC em user mode.
#include "stddef.h"   //libC em user mode. 


//
// Variáveis internas.
//

//Idle application support.
int idleStatus;
int idleError;
//...

//Idle driver support.
int driverInitialized;
//...

/*
struct idle
{
	struct thread_d *current_idle_thread;
	//int
}
*/


//Idle process.
int idleInit(); //processo sendo consideredo cliente.

//Idle as a driver.
void driverInitialize(); //processo sendo considerado um driver servidor.
void driverUninitialize(); // desinicializa.


/*

// System Library - SL - Essa é a classe principla que será colocada na biblioteca SL.BIN
// em user mode, por enquanto está aqui do programa IDLE. Isso porque, esse padrão pode se
// repetir em outros processos servidores acessados pelo kernel.

//Prototypes.
void *slSystemRam(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemIoCpu(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemIoDma(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemDevicesUnblocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemDevicesBlocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
void *slSystemThings(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4);
//Functions.
void *slSystemRam(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL;}; //switch
void *slSystemIoCpu(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemIoDma(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemDevicesUnblocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemDevicesBlocked(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
void *slSystemThings(unsigned long arg1,unsigned long arg2,unsigned long arg3,unsigned long arg4){ return NULL; };//switch
*/


/*
 * appMain:
 *     Função principal de IDLE.BIN.
 *     Obs: O entry poit está em head.s.
 * @todo: Criar argumento de entrada.
 *
 * Como teste, o processo Idle cumpre dois papéis: É o processo que contém a 
 * thread Idle, que será usada quando o sistema ficar ocioso, mas também é um 
 * processo servidor que será chamado por outro processo em user mode. O 
 * processo cliente chama o kernel, que chama o processo servidor.
 *
 * Obs: Quando for chamado por um processo e selecionar uma razão, então 
 * devemos retornar. Dependendo da razão, não precisa retornar, porque 
 * foi o kernel quem chamou e atribuiu tempo de cpu para o processo servidor.
 * Se o processo servidor ficar preso em um loop não há problemas. O scheduler
 * seleciona outra thread pra execussão após o fim do quantum.
 */
int appMain(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4) 
{	
    int Status;
	void *P;
	
	
	//
	// Checando a razão.
	//     No momento todos argumentos devem conter a razão,
	// no futuro será apenas um.
	//     Obs: Se a razão for 1,2,3 ou 4 então foi uma
	//          chamada de um processo cliente.
    //          caso contrário, a chamada veio do kernel	
	// através de um iretd.
	//
	// @todo: Esse código de razão precisa ser melhorado.
	//        colocar um unsigned long diferente como:0xDEADBEEF.
	//
	
/*
	
	switch(arg1)
	{
		//Processo cliente chamou usado razão 1.
		case 1:
	
		//Processo cliente chamou usado razão 2.
		case 2:

		//Processo cliente chamou usado razão 3.
		case 3:

		//Processo cliente chamou usado razão 4.
		case 4:

		//
		// #bugbug: Se um cliente chamar com outa razão,
		//          seleciona o kernel.
		//          Analisar melhor essa qustão das razões.
		//
		
		//Kernel chamou.
        default:
		    kernelChamouIdle
            break;		
	};
*/
   
    //Nothing
	
kernelChamouIdle:
	
	idleInit();
	
	
	//
	// @todo: 
	// Criar o processo Logoff. (LOGOFF.BIN).
	// 

	//Logoff.
	P = (void*) apiCreateProcess( 0x400000, PRIORITY_HIGH,"LOGOFF");
	if( (void*) P == NULL  ){
		printf("Fail creating process LOGOFF :)\n");
	};	
	
    //...
	
	while(1){
        // Idle não sai.
        // Aqui poderia ficar o acionador de uma rotina
        // que só funcione quando o processador estiver ocioso.
	};		
    //Nothing		
done:	
	//exit(0);
	return (int) 0;  //Status
};


/*
 * idleInit:
 *     Inicializando a aplicação Idle.
 */
int idleInit()
{
	idleStatus = 0;
	idleError = 0;
	
	printf("Idle: Initializing idle application ..\n");
	refresh_screen();
	//...
	return (int) 0;
};


/*
 * driverInitialize:
 *     O Kernel solicitou a rotina de inicialização do processo Idle na forma 
 * de driver. Faremos uma chamada ao Kernel dizendo que o driver está 
 * inicializado. Na chamada passaremos alguns parâmetros, como: O número do 
 * serviço, 129 e o código de confirmação, 1234. 4321.
 *
 */
void driverInitialize()
{
	printf("Idle: Initializing driver ...\n");
	refresh_screen();

	driverInitialized = 1;	
	system_call( 129, 4321, 4321, 4321 );	
	
	printf("Idle: Initialized.\n");
	refresh_screen();
	
	//
	// Aqui não podemos retornar ao Kernel pois o Kernel chamou
	// via iret.
	//
	
hang:
	while(1){}
	return;
};


/*
 * driverUninitialize:
 *     This method is called to uninitialize the driver object. In a real 
 * driver, this is where the driver would clean up any resources held by 
 * this driver. (m$)
 */
void driverUninitialize()
{
	//
	// Dúvidas??
	// Devemos nos preparar para desinicializar o driver.
	// Desalocaremos os recursos usadados pelo driver, como memória, 
	// arquivos abertos ...
	// Obs: Não sei se atribuição do próprio driver liberar os recursos.
	// Mas de toda forma, no mínimo devemos avisar o Kernel que os recursos 
	// não são mais necessários.
	// @todo: Podemos enviar um comando para o kernel pedindo pra que ele não 
	// link esse driver ao sistema, ou que deixe ele não inicializado.
	//

	printf("Idle: Unitializing driver ...\n");
	refresh_screen();

	driverInitialized = 0;	
	
	//Faremos uma chamada para o Kernel 'deslinkar' o driver.
	//talvez 128. 127 126..???
	//system_call( ?? , 4321, 4321, 4321 ); 		
	
	printf("Idle: Uninitialized.\n");
	refresh_screen();
	
	//
	// Aqui não podemos retornar ao Kernel pois o Kernel chamou
	// via iret.
	//
	
hang:
	while(1){}
	return;
};

//
// End.
//

