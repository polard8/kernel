/*
 * File: system.h
 *
 * Descrição:
 *     Header para rotinas de gerenciamento do sistema dentro do módulo 
 * executive do kernel.
 *     O subsistema recebe as chamadas dos programas que estão em use mode. 
 * É a porta de entrada para o kernel.
 *
 * Obs:
 *     Lembrando que o sistema compreende o Boot, Kernel e User.
 *
 * @todo:
 *     todos os serviços oferecidos estão nos 
 *     arquivos principais dos módulos hal microkernel e executive
 *     e começam com 'sys_'.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */ 
 

//@todo:
//Esse é padrão de versão. 
//Não mudar, apenas fazer as atualizações. 
#define SYSTEM_VERSIONMAJOR 1 
#define SYSTEM_VERSIONMINOR 0
#define SYSTEM_VERSIONBUILT 0
#define SYSTEM_VERSIONREVISION 1   //++


/*
 * default user name.
 */
 
#define DEFAULT_USERNAME "default-[USER]"


/*
 * Abaixo temos uma lista de variaveis de ambiente usadas
 * pelo sistema, começadas com SYSTEM_.
 *
 */ 


/*
 * Variáveis de ambiente. (em ordem).
 * Obs: @todo: Variáveis de ambiente serão salvas
 * em banco de dados. Em arquivos de configuração.            
 */ 


//Diretories. 
#define SYSTEM_ROOT        "/root"                  //Diretório raiz.
#define SYSTEM_ROOTDIR     "/root"                  //Diretório raiz.
#define SYSTEM_BOOTDIR     "/root/boot"             //Arquivos de inicialização.
#define SYSTEM_USERSDIR    "/root/users"            //Diretório de usuários.
#define SYSTEM_TMPDIR      "/root/tmp"              //Temporary files.
#define SYSTEM_TRASHDIR    "/root/trash"            //Trash dir.
#define SYSTEM_DEVICESDIR  "/root/devices"          //Devices,(as entradas representam dispositivos).
#define SYSTEM_SYSTEMDIR   "/root/os/system"           //Arquivos do sistema.
#define SYSTEM_DRIVERSDIR  "/root/os/system/drivers"   //Drivers de dispositivos.
//... 
 
//Computer.
#define SYSTEM_COMPUTER    "COMPUTER=$"

//Hadware.
//...

//User.
#define SYSTEM_USER        "USER=/$"
#define SYSTEM_USERNAME    "USERNAME="
//...

//Media.
#define SYSTEM_MEDIADISK    "MEDIA=/disk(0000)"
#define SYSTEM_MEDIAVOLUME  "MEDIA=/volume(0000)"    //Partição.
//...
 
//

//devices.
#define SYSTEM_DEVICE          "DEVICE=/$"
#define SYSTEM_DEVICECPU       "DEVICE=/cpu"
#define SYSTEM_DEVICEMEMORY    "DEVICE=/memory"
#define SYSTEM_DEVICENIC       "DEVICE=/nic"     //NIC (placa de rede).
#define SYSTEM_DEVICEKEYBOARD  "DEVICE=/keyboard"
#define SYSTEM_DEVICEMOUSE     "DEVICE=/mouse"
//...


//
// @todo: Continuar criando variáveis de ambiente.
//


/*
 * Test.
typedef struct active_environment_d active_environment_t;
struct active_environment_d
{
	unsigned long disk_number;
	unsigned long volume_number;
    unsigned long directory_number;

    const char* disk_string;
    const char* volume_string;
    const char* directory_string;	
} 
struct active_environment_d *CurrentEnvironment;
*/ 
 
//
// Globals.
// 
static char *default_user_name = "default-[USER]";
//static char *systemDefaultUserName = "default-[USER]";

/*
 * VERSION:
 *     Estrutura para versão do sistema.    
 *     O que determina a versão do sistema é a versão do Kernel.
 *
 * @todo: 
 *     Usar apenas esses 4 elementos.
 *     Dados complementares sobre a versão devem ficar 
 *     na estrutura versioninfo.
 *
 * Obs: Talvez usar um header. version.h.
 * #bugbug já tem version_t tefinida em algum lugar.
 *         Aparentemente não deu mais problema. 
 */
typedef struct version_d version_t;
struct version_d
{
    unsigned long Major;
    unsigned long Minor;	
	unsigned long Built;
	unsigned long Revision;
};
struct version_d *Version;
//...


/*
 * Version Info:
 *     Dados complemetares sobre a versão.
 */
typedef struct version_info_d version_info_t;
struct version_info_d
{
    struct version_d *version;    	
	char *string;             //String para o nome da versão "VERSION..."
	//char *string2;
	char *copyright_string;   //"ex: (c) Copyright Nora Code"
	//...
	
	//@todo:
	//Data,
	//
	
	//...
	
};
struct version_info_d *VersionInfo;

 

/*
 * system_d:
 *     System information structure:
 *     Essa estrutura guarda as informações gerais sobre o sistema.
 *     Guarda ponteiros para as principais estruturas do sistema, 
 * desde informações de boot, até informações seções de usuários.
 * 
 */
typedef struct system_d system_t;
struct system_d
{
	//Segurança, pra sertificar que a estrutura
	//alocada e esta em uso. e que não esta corrompida.
	int used;
	int magic;
	
	//version
	struct version_d *version;
	struct version_info_d *version_info;
	
	
	//
	// System Main Bar:
	//     Barra no topo da tela.    
	//     Essa é a ferramenta mais importante para ter acesso aos recursos do sistema.
	//     System | Applications | Window
	//
	//System Window (sw).
	//
	struct window_d * swBar;                //Barra.
	//Left: (Software).
	struct window_d * swItemSystem;         //Item (System).
	struct window_d * swItemApplications;   //Item (Applications).  
	struct window_d * swItemWindow;         //Item (Window).
	//Right: (Hardware)
	struct window_d * swItemMore;    //Abre uma bandeija ou menu com mais opções.(V).
	struct window_d * swItemClock;   //relógio.	
	
	//
	// @todo: Version info.
	//
	//struct version_d *version;
	
    //
    // System  info.
    //	
	int ProcessorArchitecture;
	int NumberOfProcessors;
	int PageSize;
	
	
	//
	// Observação: Recentemente a CPU assumiu funcionalidades que 
	//              antes eram da Ponte Norte.
	//
	
	//
	// North Bridge (Device number) word.
	//
	unsigned long NorthBridge;
	
	//
	// South Bridge (Device number) word.
	//
	unsigned long SouthBridge;
	
	//
	// Estruturas fundamentais do sistema.
	//
	
	//Ponteiro para 3 estruturas básicas de arquivos.
	struct bootmanager_d  *Boot;      //Boot Manager.
	struct bootloader_d   *Loader;    //Loader Manager.
	struct kernel_d       *Kernel;    //Kernel Manager.
	
	//Módulos e serviços.
	//struct bootmanager_d  *systemBoot;      //Boot Manager.
	//struct bootloader_d   *systemLoader;    //Loader Manager.
	//struct kernel_d       *systemKernel;    //Kernel Manager.
	
	//Recursos.
	//struct memory_info_d *systemMemoryInfo;
	//struct gui_d *systemGui;
	//struct usession_d *systemUserSession; //Essa estrutura tem muitas informações.
	//...
	
	//
	// Obs: A estrutura de user session terá muitas informações sobre recursos do sistema
	//      tem pool de diretórios de páginas, pool de objetos, pool de desktops(wstation).
	//
	
	//
	//Lista de ponteiros de estrutura usadas para gerenciamento do sistema.
	//
	//@todo: Isso nao precisa ser assim, pode ser um ponteiro para lista de estruturas
	// de dispositivos.
    unsigned long handleList[256];
	struct devices_d *deviceList;
	
    //@todo: criar uma lista de definições de indices para esses handles.	
	
	/*
     * ring0_exported_d:
     *     Ponteiros para tabelas de funções exportadas pelos
     *     programas do sistema em ring 0.
     *     São 3 processos: BM.BIN, BL.BIN. KERNEL.BIN.
     *
     */
	struct ring0_exported_d *ring0_exported;    //Funções exportadas.
	
	//...
};
system_t *System;



//Boot Manager.
typedef struct bootmanager_d bootmanager_t;
struct bootmanager_d
{
    //
	// Informações básicas (nome do arquivo e endereço na memória).
    //
	
	char *name;               //File name. (BM.BIN).
	unsigned long address;    //Endereço.
	
	//
	// Ponteiro para bloco de informações.
	//
	
	//struct boot_block_d *BootBlock;  
	
	//
	// Outras informações
	//
	
	
	//...
};
//bootmanager_t *BootManager;


//Boot Loader.
typedef struct bootloader_d bootloader_t;
struct bootloader_d
{
    //
	// Informações básicas (nome do arquivo e endereço na memória).
    //
	
    char *name;               //File name BL.BIN
	unsigned long address;    //Endereço.
	

	//
	// Ponteiro para bloco de informações.
	//
	
    //struct loader_block_d *LoaderBlock;  
	
	//
	// Outras informações
	//
	
	
	//...	
};
//bootloader_t *BootLoader; 




//
// Variáveis do sistema.
//



//
// Listas de cores para elemetos gráficos do sistema.
//

//@todo: Criar índices de cores.
//unsigned long system_colors[32];
//unsigned long kernel_colors[32];
//unsigned long window_colors[32];
//...
 
 
//
// Prototypes.
//


/*
 * Classes:
 *     O que segue são as funções principais do Kernel. São seis rotinas 
 * chamadoras de serviços.
 * 
 * @todo: Esse esquema de rotians de serviços organizadas em classe precisa 
 * ser replicado para outros sistemas, mesmo em user mode.
 *
 * 1) systemRam
 * 2) systemIoCpu
 * 2) systemIoDma
 * 3) systemDevicesUnblocked
 * 3) systemDevicesBlocked
 * 4) systemThings
 *
 */

void *systemRam( int number, 
                 unsigned long arg1,  
		         unsigned long arg2,  
		         unsigned long arg3,  
		         unsigned long arg4 );
void *systemIoCpu( int number, 
                   unsigned long arg1,  
		           unsigned long arg2,  
		           unsigned long arg3,  
		           unsigned long arg4 );
void *systemIoDma( int number, 
                  unsigned long arg1,  
		          unsigned long arg2,  
		          unsigned long arg3,  
		          unsigned long arg4 );
void *systemDevicesUnblocked( int number, 
                              unsigned long arg1,  
		                      unsigned long arg2,  
		                      unsigned long arg3,  
		                      unsigned long arg4 );
void *systemDevicesBlocked( int number, 
                            unsigned long arg1,  
		                    unsigned long arg2,  
		                    unsigned long arg3,  
		                    unsigned long arg4 ); 
void *systemThings( int number, 
                    unsigned long arg1,  
		            unsigned long arg2,  
		            unsigned long arg3,  
		            unsigned long arg4 );
					
	
/*
 * systemLinkDriver:
 *     Linkando um driver ao sistema operacional
 */

void *systemLinkDriver(unsigned long arg1, unsigned long arg2, unsigned long arg3);

	
/*
 * systemShowDevicesInfo:
 *     Mostrar informações sobre o sistema, seguindo a ordem de
 *     velocidade dos dispositivos e barramentos.
 *     Ex: CPU, Memória, PCIE (video), South Bridge, Super Io ...
 *     Apresentar em ordem alfabética.
 */
void systemShowDevicesInfo();

//Cria a barra de menu do sistema. 
void *systemCreateSystemMenuBar();

/*
 * systemStartUp:
 *     Inicialização do sistema.
 *
 */
int systemStartUp();

/*
 * systemCheck3TierArchitecture:
 *     Checa as serviços oferecids nas 3 camadas.
 */
void systemCheck3TierArchitecture();

//version
void systemSetupVersion();


/*
 * system_dispatch_to_procedure:
 *     Despacha uma mensagem para o procedimento de janela do sistema.
 *     Obs: Esse procedimento fica no kernel base em procedure.c
 */
int system_dispatch_to_procedure( struct window_d *window, 
                                int msg, 
								unsigned long long1, 
								unsigned long long2);
								
/*
 * SystemMenu: System Menu para manipular a janela ativa.
 * Interface que chama o control menu da janlea ativa.
 */
int SystemMenu();


/*
 * SystemMenuProcedure:
 *     O procedimento do Control Menu principal.
 *     Menu do sistema, manipula a janela ativa.
 */																
unsigned long SystemMenuProcedure( struct window_d *window, 
                                   int msg, 
								   unsigned long long1, 
								   unsigned long long2);

/*
 * systemReboot: Reboot stuffs.
 */
void systemReboot();							   

/*
 * systemShutdown: Shut down stuffs.
 */
void systemShutdown();
 
 
/*
 * services:
 *    Atende as chamadas das interrupções do sistema.
 *    É a int 200.
 *    Obs: Essa rotina está em service.c
 */
void *services( unsigned long number, 
                      unsigned long arg2, 
			 	      unsigned long arg3, 
					  unsigned long arg4 );
				

/*
 * system_procedure:
 *     O procedimento default do sistema.
 *     Obs: Essa rotina está em procedure.c.  
 */				
unsigned long system_procedure( struct window_d *window, 
                                int msg, 
								unsigned long long1, 
								unsigned long long2); 
													   

/*
 * systemcall:
 *     @todo: Essa função deve ser chamada via kernel request quando em kernel mode.
 * Obs:
 *     As chamadas ao sistema são feitas via interrupção, ou via kernel request.
 *     ??? @todo: Onde está essa rotina ???
 */
int systemcall( unsigned long numero, 
                unsigned long ax, 
				unsigned long bx, 
				unsigned long cx, 
				unsigned long dx ); 


/*
 * registra_procedimento:
 *     Registra um procedimento de janela.
 *
 */				
unsigned long registra_procedimento( unsigned long arg1, 
                                     unsigned long arg2, 
									 unsigned long arg3, 
									 unsigned long arg4);
									 
									 

/*
 * SendMessage:
 *     Envia mensagem para um procedimento de janela.
 */									 
void SendMessage( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 );





/*
 * procedureHelp:
 *     Help messages.
 *     Obs: Essa rotina está em procedure.c
 */
void procedureHelp();



/*
 * systemAbort:
 *     Abort system.
 */
void systemAbort();





/*
 * SetProcedure:
 *     Atualiza o procedimento atual.
 */
void SetProcedure(unsigned long proc);



//
// System Server support.
//

int init_systemserver();


								
//
// Fim.
//
