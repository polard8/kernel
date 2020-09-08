
/*
 * gobject.h
 * 
 *     It's used for the file structure.
 *
 *     2018 - Created by Fred Nora.
 */


#ifndef ____GOBJECT_H
#define ____GOBJECT_H 1



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

//#importante: Isso faz parte do módulo de segurança
//e deve estar associado ao sistema de arquivos ...
//Pois estamos lidando com concessões de permissões 
//de acessoa objetos ... que pode ser 'arquivos' ou 
// dispositivos. 
//talvez isso devesse ir para object.h

typedef enum {

    //Precisamos de um pouco de ordem nisso.
    //separar por grupos.
    //Talvez usarmos os prefixos e as pastas do kernel.

    ObjectTypeNull,               //0 Null. (Free)
    
    // fs/
    ObjectTypeDirectory,          // diretório de arquivos
    ObjectTypeFile,               // (Regular file)
    ObjectTypePipe,               //
    ObjectTypeFileSystem,  
    ObjectTypeMetafile, 

    // hwi/
    ObjectTypeDevice,         // device ??
    ObjectTypeDisk,           //
    ObjectTypeDiskInfo,       // disk info,
    ObjectTypeDiskPartition,  // info struct    
    ObjectTypeVolume,         // disk volume 
    ObjectTypeTerminal,       // 
    ObjectTypeLine,           //  
    ObjectTypeTTY,            //
    ObjectTypePTY,            //
    ObjectTypeVirtualConsole, //
    ObjectTypeCharDev,        //
    ObjectTypeBlockDev,       //
    ObjectTypeNetworkDev,     //
    ObjectTypeVideo,          // video
    ObjectTypeCpu,           
    ObjectTypeDma,  
    ObjectTypeProcessor,      // processor
    ObjectTypeProcessorBlock, // processor block 
    ObjectTypeMemory,         // memory card info.
    ObjectTypePIC,            // pic controller.
    ObjectTypeTimer,          // PIT timer
    ObjectTypeRTC,            // rtc controller, clock
    ObjectTypeKeyboard,       // keyboard device.
    ObjectTypeMouse,          // mouse device.
    ObjectTypeComputer,       //
    ObjectTypeCpuRegister,    //
    ObjectTypeGDT,            //
    ObjectTypeLDT,            //
    ObjectTypeIDT,            //
    ObjectTypeTSS,            //
    ObjectTypePort,           // (i/o port) generic
    ObjectTypeController,     //
    ObjectTypePciDevice,        // PCI device info generic
    ObjectTypePciDeviceDriver,  // PCI device driver info.
    ObjectTypeScreen,           // Screen.

    // klib/
    ObjectTypeSignal,     // unix signal object ??

    // net/
    ObjectTypeHostInfo,     // HostInfo. 
    ObjectTypeProtocol,     // protocol
    ObjectTypeSocket,       // sockets.
    ObjectTypeIpAddress,    // IP address.
    ObjectTypeMacAddress,   // MAC Address.
    ObjectTypeChannel,      // channel = two sockets.

    // ps/ 
    ObjectTypeProcess,            // Process.
    ObjectTypeThread,             // Thread.
    ObjectTypePageDirectory,      // page directory
    ObjectTypePageTable,          // page table
    ObjectTypePageFrame,          // page frame
    ObjectTypeFramePool,          // frame pool
    ObjectTypeASpace,             // Address Space. (memory address)
    ObjectTypeDSpace,             // Disk Space.
    ObjectTypeBank,               // Bank. (banco de dados).
    ObjectTypeHeap,               // heap
    ObjectTypeIoBuffer,           // i/o buffer
    ObjectTypeProcessMemoryInfo,  // process memory info
    ObjectTypePhysicalMemoryInfo, // physical memory info
    ObjectTypeMemoryInfo,         // memory info
    ObjectTypeMemoryBlock,        // memory block. Usado para swap.
    ObjectTypeSemaphore,          // Semaphore
    ObjectTypeMutex, 

    // security/
    ObjectTypeUser,               // user ??
    ObjectTypeUserInfo,           // userinfo ??
    ObjectTypeGroup,              // user group
    ObjectTypeUserSession,        // User session
    ObjectTypeRoom,               // room = (window station), desktop pool.
    ObjectTypeDesktop,            // desktop.
    ObjectTypeToken,              // Token de acesso à objetos. (access token)

    // ws/
    ObjectTypeWindow,             // window 
    ObjectTypeRectangle,          // rectangle
    ObjectTypeMenu,               // menu
    ObjectTypeMenuItem,           // menuitem
    ObjectTypeButton,    
    ObjectTypeGrid,     
    ObjectTypeColorScheme,  
    ObjectTypeFont,  
    ObjectTypeIcon,  
    ObjectTypeRGBA,               // rgba 
    ObjectTypeWindowProcedure,    // window procedure
    ObjectTypeCursor, 
    ObjectTypeMessage,            // system message

    //kernel/
    ObjectTypeRequest,        // request de kernel.
    ObjectTypeKM,             // ??
    ObjectTypeUM,             // ??

    ObjectTypeGeneric       

	// todo: 
	// precisamos criar um tipo genérico
	// para validação de objetos não especificados 
	// ou até nulos, talvez. :)

}object_type_t;




//
// Enumerando classes de objetos. (categorias)
//

//talvez isso devesse ir para object.h
typedef enum {
	
	ObjectClassKernelObjects,  // Kernel Objects.
	ObjectClassUserObjects,    // User Objects.
	ObjectClassGuiObjects,     // Graphical User Interface Objects.
	ObjectClassCliObjects,     // Command Line Interface Objects.
    
    //...	

}object_class_t;



#endif    






