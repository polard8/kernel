/*
 * File: include\object.h
 *
 * Descrição:
 *    Header do gerenciador de objetos.
 *    Observe que esse header deve ficar em /include.
 *
 * Obs: Se cada objeto tem um Handle é porque todos objetos
 *      estão em gavetas. O desktop é uma mesa com muitas gavetas
 *      e cada gaveta tem um puxador e dentro de cada gaveta tem um objeto.
 *
 * Obs: Teremos um vetor que é uma lista de tipos de objetos.
 *      Aplicações em user mode solicitam um objeto através de um Índice, 
 * que seleciona um ponteiro armazenado em algum índice do vetor. Cada índice
 * representa um tipo de objeto. Esse índice é chamado de descritor de objeto.
 * A estrutura também é considerada descritor. 
 *
 * Histórico:
 *     Versão 1.0, 2016 - Criado por Fred Nora.
 *     //... 
 */

 
//
// Índices para o vetor de objetos. (provisório).
//
//@todo: Essa lista será revisada e modificada.
//       Selecioar e organizar... 
// Obs: Uma forma boa de organizar é colocar em ordem alfabética
//      Incluir um objeto na lista será fácil.         
// @todo: Uma liste enumerada, com descrição.
//


//
// ****   CADA ÍNDICE DESCREVE UM TIPO DE OBJETO   ****
//

//
// Obs: Essa lista deve estar sincronizada com a da 'enum' em gdef.h.
//

//Null.
#define OBJECT_NULL      0

#define OBJECT_ASPACE 1
#define OBJECT_DSPACE 2
#define OBJECT_BANK   3

#define OBJECT_CHANNEL       4
#define OBJECT_DIRECTORY     5       //DIRETÓRIO DE ARQUIVOS.
#define OBJECT_MEMORY_HEAP   6
#define OBJECT_IOBUFFER  7
#define OBJECT_IPADDRESS 8
#define OBJECT_PROCESS_MEMORY_INFO 9
#define OBJECT_PHYSICAL_MEMORY_INFO 10
#define OBJECT_MEMORY_INFO         11
#define OBJECT_MEMORY_BLOCK   12
#define OBJECT_PAGEDIRECTORY 13
#define OBJECT_PAGETABLE 14
#define OBJECT_PAGEFRAME 15
#define OBJECT_FRAMEPOOL 16
#define OBJECT_SOCKET 17
#define OBJECT_USERINFO 18

#define OBJECT_DESKTOP    19    //Desktop. STRUCT
#define OBJECT_MENUITEM   20    //Menu ITEM
#define OBJECT_MENU 21
#define OBJECT_USESSION   22    //User Session.
#define OBJECT_WIN_PROCEDURE  23
#define OBJECT_RECTANGLE 24
#define OBJECT_RGBA 25
#define OBJECT_WINDOW     26    //Window.
#define OBJECT_WSTATION   27    //Window Station.(DESKTOP POOL)
#define OBJECT_CONSOLE 28
#define OBJECT_LINE 29
#define OBJECT_TERMINAL 30

// \microkernel
#define OBJECT_PROCESS   31
#define OBJECT_SEMAPHORE   32
#define OBJECT_THREAD    33
// \microkernel.cpu
#define OBJECT_CPU 34
// \microkernel.dma
#define OBJECT_DMA 35

// \hal
#define OBJECT_PROCESSOR 36

//DEVICE
#define OBJECT_DEVICE    37 
#define OBJECT_DISK_INFO 38
#define OBJECT_PROCESSOR_BLOCK 39
#define OBJECT_HOST_INFO 40
#define OBJECT_KEYBOARD 41
#define OBJECT_MAC_ADDRESS 42
#define OBJECT_MEMORY      43  //HARDWARE, CARD.
#define OBJECT_PCIDEVICE 44
#define OBJECT_PCIDEVICEDRIVER 45
#define OBJECT_PIC   46
#define OBJECT_RTC 47
#define OBJECT_SCREEN 48
#define OBJECT_TIMER 49
#define OBJECT_VIDEO 50
#define OBJECT_VOLUME  51

//THINGS
//...

//OUTROS...
#define OBJECT_CURSOR    52
#define OBJECT_REQUEST   53 //KERNEL REQUEST.
#define OBJECT_SIGNAL    54
#define OBJECT_FILE      55
#define OBJECT_METAFILE  56
#define OBJECT_MUTEX 57
#define OBJECT_TOKEN 58
#define OBJECT_FONT 59
#define OBJECT_ICON 60
#define OBJECT_PIPE 61


#define OBJECT_GROUP     62 //Grupo de usuários.
#define OBJECT_USER      63 //usuário

#define OBJECT_COMPUTER      64  //computador (host em rede)
#define OBJECT_CPU_REGISTER  65  //REGISTRADORES DA CPU. cr0, cr1 ...

#define OBJECT_DISK          66 
#define OBJECT_DISK_PARTITION  67
#define OBJECT_GDT      68       //LIKE GDT, IDT ...
#define OBJECT_LDT 69
#define OBJECT_IDT 70
#define OBJECT_TSS 71 

#define OBJECT_PORT       72      //Porta de controlador de dispositivo
#define OBJECT_CONTROLLER  73     //Controlador de dispositivo.
#define OBJECTS_KM         74 //Kernel mode??
#define OBJECTS_UM       75  //Use mode ??
#define OBJECTS_COLOR_SCHEME 76   //ObjectTypeColorScheme
//...

//
// #BUGBUG:  @todo: é preciso conferir e fazer coincidir os valores em gdef.h e object.h.
//




/*

#define OBJECT_JOB     35  //Job de processos.
//#define OBJECT_PROFILE 36  
//...(30~39)

//ipc - inter process comunication.

#define OBJECT_MSG            42
#define OBJECT_EVENT          43


#define OBJECT_TOKEN  46
//...(40~49)

//Memory 

#define OBJECT_MEMORY_STACK   52

#define OBJECT_MEMORY_FRAME   54
#define OBJECT_MEMORY_PAGE    55
#define OBJECT_MEMORY_VIEW    56
#define OBJECT_MEMORY_BUFFER  57
#define OBJECT_MEMORY_CACH    58
//... (50~59)

//GUI.
#define OBJECTS_GUI            60
#define OBJECT_IMAGE           61
#define OBJECT_MENU_PROCEDURE  62
//... (60~69)

//grupo 7x
#define OBJECT_7x 70
//...(70~79)

//grupo 8x
#define OBJECT_8x 80
//...(80~89)

//Outros
#define OBJECT_LIST       90
#define OBJECT_REQUEST    91
//...(90~99)

//  *** (100~Max) ***
//Extendida (Novos objetos são incluídos).
//...
#define OBJECT_AMBIENTE  100 //boot, kernel mode, user mode.
//...(100~Max)

*/


/*
 * struct object_d:
 *     Estrutura para objetos.
 */
//typedef struct object_d object_t;
typedef struct object_d object_descriptor_t;
struct object_d 
{
	//@todo: 
    //?? Não sei se isso é necessário para essa estrutura em particular. ?? 
	object_type_t objectType;
	object_class_t objectClass;	
    
	//@todo: fazer isso para todas as estrututras.
	//medir quantos bytes tem cada estrutura.
	//int object_size;  	
	
   //identificadores
   int id;            // Id do objeto.
   unsigned long name_address;
   char name[16];	  // Nome do objeto com 16 chars. @todo: usar ponteiro para nome.
   int used;          // Se o slot esta sendo usado.
   int magic;         // Número mágico pra ver se o slot não esta corrompido.
   
	
   //endereços
   unsigned long obj_address;
   unsigned long obj_procedure;
   
    /*
	 * Status do objeto.
	 */   
	 
	int token; //algum processo 'pegou' o objeto e esta usando.
    
	int task_id; //id da tarefa que pegou o processo.
	
    
	//int signaled;
	//struct process_d *waitListHead;
	
	//channel	
    //process
	//thread
	//window
	
	//continua...
};
object_descriptor_t *object;  //object
//...


//
// @todo: Essas listas ocupam muito espaço, precisa ser alocado dinamicamente.
//        Porém é certo que manipularemos muitos objetos.  
//

//@todo: Usar array dinâmico.
object_descriptor_t objects_km[256+1];  //objetos em kernel mode.
object_descriptor_t objects_um[256+1];  //objetos em user mode. 
object_descriptor_t objects_gui[256+1]; //objetos gráficos. 





/*
 * Se o gerenciador de recursos foi inicializado.
 */
int g_object_manager_status;

//id do objeto atual
int g_current_object;

//id da lista ao qual o objeto atual pertence.
// object_km, object_um, object_gui. 
int g_current_list;

					   
int init_object_manager();



//
//fim.
//

