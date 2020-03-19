
/*
 * gobject.h
 * 
 *      It's used for the file structure.
 * 
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
	
	// **** EXECUTIVE  ****

	//Nothing for now.	
    ObjectTypeNull,               //0 Null. (Free)
	ObjectTypeASpace,             //1 Address Space. (memory address)
	ObjectTypeDSpace,             //2 Disk Space.
	ObjectTypeBank,               //3 Bank. (banco de dados).
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
	ObjectTypeDesktop,            //19 desktop, executive,uigm.	
	ObjectTypeMenuItem,           //20 menuitem, executive uigm.
	ObjectTypeMenu,               //21 menu, executive uigm.	
	ObjectTypeUserSession,        //22 User session, executive, uigm.	
	ObjectTypeWindowProcedure,    //23 window procedure, executive, uigm.	
	ObjectTypeRectangle,          //24 rectangle, executive, uigm. 	
	ObjectTypeRGBA,               //25 rgba, executive, uigm. 
	ObjectTypeWindow,             //26 window, executive ,uigm.
	ObjectTypeRoom,               //27 desktop pool. room window station, executive, uigm.
	ObjectTypeTerminal,           //28 console, executive, uitm.
    ObjectTypeLine,               //29 console line, executive, uitm.
	ObjectTypeTerminal2,          //30 Terminal, executive, uitm. //TODO MUDAR
	
    // **** MICROKERNEL  ****
	
	//microkernel
	ObjectTypeProcess,    //31 Process, microkernel.
	ObjectTypeSemaphore,  //32 semaphore, microkernel.	
	ObjectTypeThread,     //33 thread, microkernel.
	
	//io 
	//@todo: isso deverá ser criado aqui.
	ObjectTypeCpu,  //34
	ObjectTypeDma,  //35
	
	// **** HAL  ****
	
	ObjectTypeProcessor,  //36 processor, hal (talvez isso devesse ir para io de microkernel.)
	
	//device(unblocked e blocked).
	ObjectTypeDevice,         //37 device, hal
	ObjectTypeDiskInfo,       //38 disk info, hal.
	ObjectTypeProcessorBlock, //39 processor block hal...(pode ir para io,microkernel)
    ObjectTypeHostInfo,    // 40 HostInfo, hal. 
	ObjectTypeKeyboard,    // 41 keyboard, hal.
	ObjectTypeMacAddress,  // 42 MAC Address, hal.
	ObjectTypeMemory,      // 43 memory card info, hal.
	ObjectTypePciDevice,   // 44 PCI device info, hal.
	ObjectTypePciDeviceDriver,   //45 PCI device driver info, hal.
	ObjectTypePIC,       //46 pic controller, hal.
	ObjectTypeRTC,       //47 rtc controller, hal.
	ObjectTypeScreen,    //48 Screen, hal.
	ObjectTypeTimer,     //49 ?? timer ,hal.	
	ObjectTypeVideo,     //50 video ,hal.
	ObjectTypeVolume,    //51 disk volume ,hal.
	
	//things
	//@todo:
	
	// **** OUTROS  ****
	ObjectTypeCursor,    //52 /include.
	ObjectTypeRequest,   //53 request de kernel /include.
	ObjectTypeSignal,    //54
	ObjectTypeFile,      //55 file, /include. stdio.
	ObjectTypeMetafile,  //56 
	ObjectTypeMutex,     //57
	ObjectTypeToken,     //58 Token de acesso à objetos. (access token)
	ObjectTypeFont,      //59
	ObjectTypeIcon,      //60
	ObjectTypePipe,      //61
	
	ObjectTypeGroup,     //62
	ObjectTypeUser,      //63
	
	ObjectTypeComputer,       //64
	ObjectTypeCpuRegister,    //65
	
	
	ObjectTypeDisk,           //66
	ObjectTypeDiskPartition,  //67 //info struct
	ObjectTypeGDT,            //68
	ObjectTypeLDT,            //69
	ObjectTypeIDT,            //70
	ObjectTypeTSS,            //71
	
	ObjectTypePort,           //72 (i/o port)
	ObjectTypeController,     //73
	ObjectTypeKM,             //74
	ObjectTypeUM,             //75
	ObjectTypeColorScheme,    //76
	ObjectTypeButton,         //77
	ObjectTypeGrid,           //78
	ObjectTypeMessage,        //79
	//...
	
    ObjectTypeTTY,
    ObjectTypeVirtualConsole,
    ObjectTypeCharDev,
    ObjectTypeBlockDev,
    ObjectTypeNetworkDev,
    ObjectTypeFileSystem


	// todo: 
	// precisamos criar um tipo genérico
	// para validação de objetos não especificados 
	// ou até nulos, talvez. :)
	// ObjectTypeGeneric, //80
	
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






