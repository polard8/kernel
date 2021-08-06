/*
 * gobject.h
 * 
 *     It's used for the file structure.
 *     2018 - Created by Fred Nora.
 */

#ifndef ____GOBJECT_H
#define ____GOBJECT_H  1


typedef enum {

    //Precisamos de um pouco de ordem nisso.
    //separar por grupos.
    //Talvez usarmos os prefixos e as pastas do kernel.

    ObjectTypeNull,               //0 Null. (Free)
    
    // fs/
    ObjectTypeDirectory,          // diretório de arquivos
    ObjectTypeFile,               // (Regular file)
    ObjectTypePipe,               //
    ObjectTypeFileSystem,         // <<<< This file represents a 'File System'.
    
    // metafile just like GRAMADO or BRAMADO.
    // or even a hidden lba with no entry in the directory
    ObjectTypeMetafile,           

    // hwi/
    ObjectTypeDevice,         // device ??
    ObjectTypeDisk,           //
    ObjectTypeDiskInfo,       // disk info,
    ObjectTypeDiskPartition,  // info struct    
    ObjectTypeVolume,         // disk volume 
    ObjectTypeTerminal,       // 
    ObjectTypeLine,           //
    ObjectTypePTMX,           // <<<< This file represents a pty multiplexer.  
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


typedef enum {
	
	ObjectClassKernelObjects,  // Kernel Objects.
	ObjectClassUserObjects,    // User Objects.
	ObjectClassGuiObjects,     // Graphical User Interface Objects.
	ObjectClassCliObjects,     // Command Line Interface Objects.
    
    //...	

}object_class_t;



#endif    



















