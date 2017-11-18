/*
 * File: gdef.h
*
* Descrição:
*     Definições globais. 
*     Será utilizado por todos os módulos. Deve ficar no início.
*     Quando uma definição deve ser acessada por todos os módulos
*     do kernel base ela deve ficar aqui.
*
* @todo: FAZER O MÁXIMO DE COISAS SISTEMICAMENTE NÃO-IMPORTANTES PRIMEIRO.
         que não comprometam o sistema. como gui.
*/

/*
 * Sobre a GUI:
 * ============
 *     Um grid flutuante de janelas quadradas, 4 janelas.
 *     O message box pode ser um retângulo abaixo do grid.
 *     Uma janela de terminal virtual igual à um celular. 
 * Desse modo, enquanto essas 6 janelas não são flutuantes, dá pra
 * ir usando elas desenha das no backbuffer mesmo.
 *
 *
 * divisão da tela:   
 * quatro quadrantes de 10.
 * divide por vinte e multiplica pela quantidade desejada.
 *         (multiplicador*(total/20)) 
 */

/*
 Sobre o banco de dados:
 =======================
 
Tipos de contas:
    aspace e dspace, pessoais e conjuntas.
	
aspace:
    Um Address Space é uma conta de banco de dados em memória. Uma conta 
pode ser do tipo conjunta(Shared) ou  pessoal(Personal). 

dspace:
    Um Disk Space é uma conta de banco de dados em disco. Uma conta pode 
ser do tipo conjunta(Shared) ou  pessoal(Personal). 

Donos das contas:
    Os processos são os clientes dos bancos de dados e são os donos das 
contas de bancos de dados.

Tipos de bancos:
    Kernel Data Base, Global Data Base e Local Data Base.

KDB:	
    Banco de dados do tipo kernel. É o banco de maior privilégio, poucos
processos poderão usar esse banco e as contas presentes nele.

GDB:
    Bancos de dados do tipo global. É o banco das contas conjuntas, para
que os processos possam compartilhar as contas e os dados que elas acessam.

LDB:
    Bancos de dados do tipo pessoal. É o banco das contas pessoais. Um 
processo pode ser dono de uma conta dessas para proteger seus dados
e revogar qualquer tipo de acesso e somente ele terá acesso aos dados
dessa conta.
	
*/


#define FRONTBUFFER_ADDRESS 0xC0400000
#define BACKBUFFER_ADDRESS  0xC0800000

//#define FRONTBUFFER_VA 0xC0400000
//#define BACKBUFFER_VA  0xC0800000


//#define BIOS_FONT8X8 0x000FFA6E

//using gui flags.
#define GUI_ON   1
#define GUI_OFF  0

/*
 * Os Type:
 *     O sistema operacional pode ser usado como servidor.
 * Radando em uma máquina real e acessado por um terminal
 * via rede LAN, ou porta serial. TTY.
 *     Qualquer sistema operacional em uma máquina cliente pode
 * acessar o sistema operacional na maquina servidora. Pra isso
 * tem que ter um programa na máquina cliente que envie comandos 
 * para a máquina servidora através da placa de rede ou da porta 
 * serial.
 *     O sistema pode atuar como cliente.
 */
typedef enum {
	OsTypeClient,
	OsTypeServer,
	OsTypeHeadlessServer,  //Headless Server. ??	
}os_type_t;

//
// Enumerando os tipos de objetos.
// Obs: Deve ser o mesmo que as definições acima.
// As estruturas indicam o tipo de objeto que se pode criar.
// o primeiro ítem de uma estrutura deve ser a indicação do tipo
// de objeto que ela representa.
// @todo: A ORDEM AQUI SEGUIRÁ A ORDEM DAS CLASSES DO SISTEMA.
//        COMEÇANDO DA CLASSE RAM.
//
// Precisa ser uma definição global. pois todas estruturas vão usar.
//
// Obs: Essa lista deve estar sincronizada com alista de fefinições em object.h
//

//
//Obs: Esses poderiam ser os principais, e imutáveis
// deichando os vindouros como subsequentes à esses.
//

typedef enum {
	
	// **** EXECUTIVE  ****
	
	//ram
	//Nothing for now.	
    ObjectTypeNull,               //0 Null.
	ObjectTypeASpace,             //1 Address Space. (memory address)
	ObjectTypeDSpace,             //2 Disk Space.
	ObjectTypeBank,               //3 Bank. (banco de dados).
	//sm
	ObjectTypeChannel,            //4 executive sm.
	ObjectTypeDirectory,          //5 diretório de arquivos. executive sm.
	ObjectTypeHeap,               //6 heap executive sm
	ObjectTypeIoBuffer,           //7 i/o buffer executive sm
	ObjectTypeIpAddress,          //8 ip address executivesm.
	ObjectTypeProcessMemoryInfo,  //9 process memory info, executive sm.
	ObjectTypePhysicalMemoryInfo, //10 physical memory info, executive sm.
	ObjectTypeMemoryInfo,         //11 memory info, executive sm.
	ObjectTypeMemoryBlock,        //12 ????? @todo: Ver se esse pode ser Criado sem prejudicar a alocação dinâmica. executive sm mm.	
	ObjectTypePageDirectory,      //13 page directory. executive sm, mm.	
	ObjectTypePageTable,          //14 pagepool , page table, executive ,sm,mm.	
	ObjectTypePageFrame,          //15 page frame ,executive ,sm,mm.
	ObjectTypeFramePool,          //16
	ObjectTypeSocket,             //17 sockets, executive, sm.
    ObjectTypeUserInfo,           //18 userinfo, executive, sm.
	//uigm 
	ObjectTypeDesktop,     //19 desktop, executive,uigm.	
	ObjectTypeMenuItem,        //20 menuitem, executive uigm.
	ObjectTypeMenu,        //21 menu, executive uigm.	
	ObjectTypeUserSession, //22 User session, executive, uigm.	
	ObjectTypeWindowProcedure,  //23 window procedure, executive, uigm.	
	ObjectTypeRectangle,        //24 rectangle, executive, uigm. 	
	ObjectTypeRGBA,             //25 rgba, executive, uigm. 
	ObjectTypeWindow,           //26 window, executive ,uigm.
	ObjectTypeWindowStation,  //27 desktop pool. window station, executive, uigm.
	//uitm.
	ObjectTypeConsole,        //28 console, executive, uitm.
    ObjectTypeLine,           //29 console line, executive, uitm.
	ObjectTypeTerminal,       //30 Terminal, executive, uitm.
	
    // **** MICROKERNEL  ****
	
	//microkernel
	ObjectTypeProcess,  //31 Process, microkernel.
	ObjectTypeSemaphore,  //32 semaphore, microkernel.	
	ObjectTypeThread,     //33 thread, microkernel.
	
	//io 
	//@todo: isso deverá ser criado aqui.
	ObjectTypeCpu,  //34
	ObjectTypeDma,  //35
	
	// **** HAL  ****
	
	ObjectTypeProcessor,  //36 processor, hal (talvez isso devesse ir para io de microkernel.)
	
	//device(unblocked e blocked).
	ObjectTypeDevice,      //37 device, hal
	ObjectTypeDiskInfo,    //38 disk info, hal.
	ObjectTypeProcessorBlock, //39 processor block hal...(pode ir para io,microkernel)
    ObjectTypeHostInfo,  //40 HostInfo, hal. 
	ObjectTypeKeyboard,   //41 keyboard, hal.
	ObjectTypeMacAddress,  //42 MAC Address, hal.
	ObjectTypeMemory,      //43 memory card info, hal.
	ObjectTypePciDevice,   //44 PCI device info, hal.
	ObjectTypePciDeviceDriver,   //45 PCI device driver info, hal.
	ObjectTypePIC, //46 pic controller, hal.
	ObjectTypeRTC, //47 rtc controller, hal.
	ObjectTypeScreen, //48 Screen, hal.
	ObjectTypeTimer,    //49 ?? timer ,hal.	
	ObjectTypeVideo,    //50 video ,hal.
	ObjectTypeVolume,    //51 disk volume ,hal.
	
	//things
	//@todo:
	
	// **** OUTROS  ****
	ObjectTypeCursor,    //52 /include.
	ObjectTypeRequest,   //53 request de kernel /include.
	ObjectTypeSignal,    //54
	ObjectTypeFile,      //55 file, /include. stdio.
	ObjectTypeMetafile, //56 
	ObjectTypeMutex,    //57
	ObjectTypeToken,    //58 Token de acesso à objetos. (access token)
	ObjectTypeFont,    //59
	ObjectTypeIcon,     //60
	ObjectTypePipe,     //61
	
	ObjectTypeGroup,     //62
	ObjectTypeUser,      //63
	
	ObjectTypeComputer,      //64
	ObjectTypeCpuRegister,   //65
	
	
	ObjectTypeDisk,   //66
	ObjectTypeDiskPartition,   //67 //info struct
	ObjectTypeGDT,   //68
	ObjectTypeLDT,   //69
	ObjectTypeIDT,   //70
	ObjectTypeTSS,   //71
	
	ObjectTypePort,  //72 (i/o port)
	ObjectTypeController, //73
	ObjectTypeKM, //74
	ObjectTypeUM, //75
	ObjectTypeColorScheme,  //76
	ObjectTypeButton,       //77
	ObjectTypeGrid,       //78
	//...
}object_type_t;

//
// Enumerando classes de objetos. (categorias)
//
typedef enum {
	ObjectClassKernelObjects,  // Kernel Objects.
	ObjectClassUserObjects,    // User Objects.
	ObjectClassGuiObjects,     // Graphical User Interface Objects.
	ObjectClassCliObjects,     // Command Line Interface Objects.
    //...	
}object_class_t;


/*
 * PPL - (Process Permition Level).
 *
 * Determina as camadas de software que um processo terá acesso
 * irrestrito.
 *
 * + A permissão natural de um processo de usuário é K5. Podendo ele
 * utiliza somente os serviços oferecidos pela camada K5, que é 
 * a mais alta.
 * 
 * + A permissão natural dos módulos do kernel em user mode podem ser
 *   diferente, variando de K0 à K4. Mas nada impede dos módulos
 *   usarem a permissão K5. Um módulo em kernel mode fabricado por usuários
 *   poderiam receber apenas a permissão K5. As outras permissões
 *   seriam concedidas somente com licensa paga, ou para que fabrica
 * o sistema operacional.
 *
 * + Servidores em user mode poderão ter qualquer um dos níveis.
 *   Mas a permissão natural seria K5. As licensas para servidores
 * em user mode são mais baratas.
 *
 *   Obs: Categorizar os servidores de acordo com o nível de permissão
 * pode melhorar a organização do sistema, tendo em vista que as permissões
 * seguem o padrão de classes do sistema, que uma interconexão lógica
 * de dispositivos.
 */
typedef enum {
	pplK0, //executive, (ram),sm,uigm,uitm.
	pplK1, //microkernel,(io),cpu.
	pplK2, //microkernel,(io),dma.
	pplK3, //hal,(device),unblocked.
	pplK4, //hal,(device),blocked.
	pplK5, //hal,(things).
}process_permition_level_t; 





unsigned long g_backbuffer_address;            //0xC0800000
unsigned long g_frontbuffer_buffer_address;    //LFB. Endereço físico do frontbuffer(memória da placa de vídeo). 
unsigned long g_frontbuffer_buffer_va;    //endereço lógico do frontbuffer.





int gNextKeyboardMessage;

//
// End.
//

