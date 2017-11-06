/*
 * File: hal.h
 *
 * Descrição:
 *     Rotinas exportadas pelo /hal para os outros 2 módulos do kernel base.
 *
 *     Header principal da abstração de hardware.
 *     OBS: Abstração para hardware fundamental.
 *         (placa mae, bus, processor, microcontroller, pci, ram).
 *     CPUs em Desktops: Intel, AMD.
 *     Arquiteturas de microcontroladores em sistemas embarcados:
 *          ARM, MIPS, Coldfire/68k, PowerPC, x86, PIC, 
 *          8051, Atmel AVR, Renesas H8, SH, V850, FR-V, M32R, Z80 e Z8. 
 *
 *    Exemplo de interface serial para microcontroladores:
 *     (Por exemplo RS 232, I2C).
 *
 * @todo: Os serviços oferecidos por esse módulo aparecerão aqui começando 
 *        por 'sys_'.
 *
 * Versão 1.0, 2015, 2016.
 */

 
 
#define PARTITION_BOOT_FLAG 0x80
//#define PARTITION_ 


//#define BOOT_RECORD_SIGNATURE          (0xaa55)



/*
 * Microcontrollers support. @todo: Criar arquivo para isso.
 */

 
//#define Microcontroller_PIC 1 
//#define Microcontroller_ 
//...


  
/*
 * variáveis usadas no hal.
 *
 */  
  
unsigned long g_machine_type;  
  
//
//....
//

//Hardware:
//Estrutura para todos os componentes de hardware presentes.
typedef struct hardware_d hardware_t;
struct hardware_d
{
	//
	// MainBoard info.
	//
	struct motherboard_d *MotherBoard;
	
	//
	// Processor info.
	//
	struct tagProcessor *Processor;   //@todo: mudar para processo_d
	int ProcessorArchitecture;
	int NumberOfProcessors;
	
	
	//
	// Chipset info. (north /south)
	//
	
    //@todo: struct
	unsigned long NorthBridge;  // North Bridge (Device number) word
	unsigned long SouthBridge; 	// South Bridge (Device number) word

    //
    // RAM memory cards info.
    //
	struct memory_d *Memory;
	
	//
	// Video card info. (graphics)
	//
	//struct tagConsole
	//struct tagGraphics
	//struct d_video
	//struct screen_d 
	
	//
	// PCI and PCIEX slots info.
	//
	struct pci_d *Pci;
	
	//
	// PIC.
	//
	struct pic_d *Pic;
	
	//
	// PIT, Timer info.
	//
	//struct pit_d *Pit; @todo.
	struct timer_d *Timer;
	
	
	//
	// RTC CMOS info.
	//
	struct rtc_d *Rtc;
	
	//
	// Discos info.
	//
	struct diskinfo_d *Disk;
	
	//
	// Volumes dos discos.
	//
	struct volumeinfo_d *Volumes; //ponteiro para array de estruturas de volumes.
	
	
	//
	// Keyboard info.
	//
	struct keyboard_d *Keyboard;
	
	//
	// Mouse info.
	//
	
	
	//floppy fdd
	struct fdd_d *Fdd;
	//struct floppy_d *Floppy;
	
	
	//ide hdd
	struct hdd_d *Hdd;
	//struct ide_d *Ide;
	
	//devices
	struct devices_d *Devices; //array de estruturas
	
	//continua ...
};  
hardware_t *Hardware;  


//Firmware:
//Estrutura para todos os componentes de firmware presentes.
typedef struct firmware_d firmware_t;
struct firmware_d
{
	int dummy;
	//bios
	//...	
};  
firmware_t *Firmware;  


//
//....
//


  
//Estrutura de disco. @todo: Colocar em outro arquivo.  
typedef struct tagDriveContext DriveContext_t;
struct tagDriveContext 
{
    ULONG Drive;
    ULONG Cylinders;
    ULONG Heads;
    ULONG Sectors;
};
DriveContext_t *DriveContext;
 
  
//Estrutura para informações sobre a placa mãe.  
typedef struct motherboard_d motherboard_t; 
struct motherboard_d
{
    //...	
};  
//motherboard_t *MotherBoard;  


/*
 * ProcessorBlock_d:
 *     Processor Block.
 *     Usado para task switch.
 *     Contém informações sobre o processador. 
 *     Que processo está nele.
 */
typedef struct ProcessorBlock_d ProcessorBlock_t; 
struct ProcessorBlock_d
{
    object_type_t objectType;
	object_class_t objectClass;	
	
    //
	// Processor Info. 
	//
	int Id;
	int Used;
	struct tagProcessor *processorInfo; //informações sobre o processador. 
	
	//
	// Process.
	//
	int running_processes;
	struct process_d *CurrentProcess;  
	struct process_d *KernelProcess;  
	//struct process_d *CurrentProcess;  
	
	//
	// Threads.
	//
	int running_tasks;    // (@todo: Mudar para running_threads.)
	//int running_threads;  //Número de threads rodando nesse processador.
    struct thread_d *CurrentThread;    
    struct thread_d *NextThread;
    struct thread_d *IdleThread;	
	//...	
	
    //Continua ...
};
ProcessorBlock_t ProcessorBlock;    //Obs: Não tem ponteiro.
  


//...
 



//
// GUI support.
// 
 
void hal_backbuffer_putpixel( unsigned long ax, 
                              unsigned long bx, 
						      unsigned long cx, 
						      unsigned long dx ); 
							  
							  
							  
							
		 
				 
/*
VOID
NSDumpMemory(
    PVOID Start,
    ULONG Length
    )
{
    ULONG cnt;

    BlPrint(" %lx:\n",(ULONG)Start);
    for (cnt=0; cnt<Length; cnt++) {
        BlPrint("%x ",*((PUSHORT)(Start)+cnt));
        if (((cnt+1)%16)==0) {
            BlPrint("\n");
        }
    }
}
*/
				
/*
 * @todo: unsigned long bios_call(unsigned long a, b c d edi esi ebp);
 */
 
/* @todo: partition. 
NTHALAPI
NTSTATUS
IoSetPartitionInformation(
    IN PDEVICE_OBJECT DeviceObject,
    IN ULONG SectorSize,
    IN ULONG PartitionNumber,
    IN ULONG PartitionType
    );

NTHALAPI
NTSTATUS
IoWritePartitionTable(
    IN PDEVICE_OBJECT DeviceObject,
    IN ULONG SectorSize,
    IN ULONG SectorsPerTrack,
    IN ULONG NumberOfHeads,
    IN struct _DRIVE_LAYOUT_INFORMATION *PartitionBuffer
    ); 
*/				
 
//Initialization support. 
int init_hal();
int init_intel();
int init_amd();


int jmp_address( unsigned long arg1, 
                 unsigned long arg2, 
				 unsigned long arg3 , 
				 unsigned long arg4); 
				 
				 
int hal_probe_processor_type();  //Sonda pra ver apenas qual é a empresa do processador.
int hal_probe_cpu();  
int hal_init_machine(); 
void hal_set_machine_type(unsigned long type);
unsigned long hal_get_machine_type();	
int hal_hardware_detect();	
int hal_showpciinfo();		
void hal_vsync();
void hal_reboot();
void hal_shutdown();

//
// End.
//

