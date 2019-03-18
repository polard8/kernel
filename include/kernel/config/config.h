/*
 * File: config.h
 *     
 *      Setup compiling stuff.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

//
// ## IMPORNTANTE ##
//

// usaremos essa configuraçao provisoriamente
// ate que tenhamos a condiçao de selecionarmos corretamente
// o canal e o dispositivo.
// Inicializaremos essas variaveis ao inicializarmos
// o controlador de ata. ide. em ata.c diskATAInitialize.


// USE PRIMARY MASTER!!

// Portas bases encontradas nas BARs.
//BAR0 = base port 1F0   HD primário
//BAR1 = base port 3F6	
//BAR2 = base port 170   HD secundário
//BAR3 = base port 376
	
//#importante: Isso é BAR e naõ porta.
#define  __IDE_PORT __IDE_BAR
#define __IDE_BAR 0

#define __IDE_SLAVE  0  // 0=master 1=slave


// #tests:

// + Funcionou BAR=0 slave=0. primary master
// + Funcionou BAR=0 slave=1. primary slave

// + Funcionou BAR=2 slave=0. secondary master 
// + Funcionou BAR=2 slave=1. secondary slave


// #bugbug
// Ouve uma falha..
// Só temos o registro das portas 0 e 2.
// A porta 0 equivale ao canal primary.
// A porta 2 equivale ao canal secondary.
// Eram para as portas 0 e 1 representarem o canal primary.
// Eram para as portas 2 e 3 represerntarem o canal secondary.

// #importante:
// Na verdade só funcionam as portas 0 e 2 porque são 
// selecionadores das BARs 0 e 2, onde estão as portas de HD.
// #todo: rever o código nessa parte de configuração das BARs.


#define FRED_VHD_32MB

#if	defined(FRED_VHD_32MB)
#define VHD_32MB_CHS { 862, 4, 19,  0 }  
//#define VHD_32MB_CHS { 0x35E, 0x4, 0x13, 0 }  
#else 
#error "must define vhd"	
#endif


/* configuração de compilação */

// Algumas adaptações precisam ser feitas 
// para que as ferramentas de compilação 
// sejam usadas corretamente.


// gcc version:
// gcc 8 on manjaro

// #importante:
// O kernel tem três possíveis processos usados na inicialização.
// #obs: cada um deles tem sua própria estrutura de processo e suas 
// próprias threads, mas até o momento todos os três estão usando 
// o diretório de páginas do processo kernel.  
// Com essas flags podemos habilitar qual dos três processos 
// irão rodar na inicialização.
// Se a configuração não indicar nenhum processo então o kernel deve 
// falhar na inicialização, por enquanto. 


//=====================================================
//    ######## Creation flags ########
//

//Cria o processo shell e sua thread de controle.
#define ENTRY_CREATE_SHELL   

//Cria o processo taskman e sua thread de controle.
#define ENTRY_CREATE_TASKMAN 


//Cria uma thread para o processo kernel, que irá rodar em ring0.
#define ENTRY_CREATE_KERNELTHREAD_RING0    

//#bugbug: isso pode afetar a execução de aplicativos usando o processo init.
//testando carregar uma segunda thread no mesmo endereço virtual.
//dessa forma mais de uma thread rodará no mesmo endeereço virtual,
//mas em processos diferentes.
#define ENTRY_CREATE_THREAD_400000 


//====================================================
//    ######## Initialization flags ########
//

//#bugbug
//Se as três flags estiverem acionadas, 
//o kernel criará todos os três processos mas inicializará o init.

#define ENTRY_INITIALIZE_INIT   
//#define ENTRY_INITIALIZE_SHELL   
//#define ENTRY_INITIALIZE_TASKMAN 



//====================================================
//    ######## more ... ########
//




//Autoriza rotinas que usam varia'veis importadas 
//de makefiles e arquivos .ld.
#define IMPORTED_VARIABLES 1


//Essa flag aciona a rotina que vai checar o máximo de 
//configurações e inicializações válidas.

#define ENTRY_DEBUG_CHECK_VALIDATIONS 1




//
// Set up what kind of debug message we wanna see.
//

//Esse é usado para exibir somente os marcadores pprincipais,
//que são mesnagens escritas em maiúculas.
//fnciona como uma visão panorâmica, usa espinha dorsal, um esqueleto.
//#define KERNEL_VERBOSE 1
//Esse é usado para trabalhar a rotina de entrypoint da arquitetura alvo.
//#define ENTRY_VERBOSE 1
//Esses quatro são as camadas principais.
//#define HAL_VERBOSE 1
//#define MK_VERBOSE 1
//#define EXECVE_VERBOSE 1
//#define GWS_VERBOSE 1


//
// ## breack points ##
// Set up what what is the breakpoint.
//

//Seriam inicializações parciais programadas. 
 

//#todo
//Criar um breakpoint apo's a sondagem de dispositivos pci.

//#define BREAKPOINT_TARGET_AFTER_VIDEO 1
//#define BREAKPOINT_TARGET_AFTER_SYSTEM 1
//#define BREAKPOINT_TARGET_AFTER_RUNTIME 1
//#define BREAKPOINT_TARGET_AFTER_INIT 1
//#define BREAKPOINT_TARGET_AFTER_LOGON 1
//#define BREAKPOINT_TARGET_AFTER_LOGOFF 1
//#define BREAKPOINT_TARGET_AFTER_HAL 1
//#define BREAKPOINT_TARGET_AFTER_MK 1
//#define BREAKPOINT_TARGET_AFTER_ENTRY 1



//
// ## targets ##
//

//Também pretendo fazer a inicialização mudar de direção dependendo do alvo programado.

//Isso inicializa os três aplicativos do gramado core.
//#define TARGET_GRAMADOCORE_APPS 1

//Isso inicializa apenas o app init do gramado core.
//#define TARGET_GRAMADOCORE_INIT 1

// CONTINUA
//...


#endif 

