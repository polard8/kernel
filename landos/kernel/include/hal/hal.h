/*
 * File: hal.h
 *
 *  HAL header file.
 */

#ifndef ____HAL_H
#define ____HAL_H    1


//#todo: This is a fs thing.
#define PARTITION_BOOT_FLAG  0x80
//#define PARTITION_ 

//#define BOOT_RECORD_SIGNATURE          (0xaa55)


/*
 * Microcontrollers support. 
 * #todo: Criar arquivo para isso.
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


//  VECTORS 
//  (isr and irq address)

// Endereços das rotinas básicas chamadas pelos vetores de interrupções.
// Essas rotinas devem chamar seus handlers específicos.
// 256 interrupções
unsigned long VECTORS[256];


//
// HANDLERS 
// (callbacks??) 
//


// Endereços para as rotinas em C que tratam as interrupções.
// Essas rotinas rodam depois da rotina básica em assembly.
// 256 interrupções
// 8 extras para handlers default.

unsigned long HANDLERS[256+8];


// Hardware:
// Estrutura para todos os componentes de hardware presentes.

struct hardware_d
{
	// MainBoard info.
	struct motherboard_d *MotherBoard;

	// Processor info.
	struct processor_d *Processor;   //@todo: mudar para processo_d
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
	//struct tagTerminal
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
	

	// RTC CMOS info.

	struct rtc_d *Rtc;
	

	// Discos info.

	struct diskinfo_d *Disk;
	

	// Volumes dos discos.
    //ponteiro para array de estruturas de volumes.
	
    struct volumeinfo_d *Volumes; 


    //ps2 support.
    struct ps2_keyboard_d *ps2_keyboard;
    struct ps2_mouse_d    *ps2_mouse;



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

struct hardware_d  *Hardware;  



//Firmware:
//Estrutura para todos os componentes de firmware presentes.
struct firmware_d
{
	int dummy;
	//bios
	//...	
};  
struct firmware_d *Firmware;

//
//....
//


//Estrutura de disco. @todo: Colocar em outro arquivo.  
struct drive_context_d 
{
    unsigned long Drive;

    unsigned long Cylinders;
    unsigned long Heads;
    unsigned long Sectors;
};
struct drive_context_d *DriveContext;  


// Estrutura para informações sobre a placa mãe.  
struct motherboard_d
{
	int mobodummy;
    //...	
};  



//
// == prototypes =======================================
//


//
// Speaker support.
//

//OUT - Play sound using built in speaker
void hal_speaker_on (void);

//IN - make it shutup
void hal_speaker_off (void);

// Testando o beep;
void hal_test_speaker (void);




//
// GUI support.
// 
 
void 
hal_backbuffer_putpixel ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx ); 


void 
hal_lfb_putpixel ( 
    unsigned long ax, 
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

int init_hal (void);

int init_amd (void);
// ...

void x86_info (void);

int hal_init_machine (void); 

void hal_set_machine_type (unsigned long type);

// ?
unsigned long hal_get_machine_type (void);	

int hal_hardware_detect (void);	

int hal_showpciinfo (void);

void hal_vsync (void);


//
// reboot and shutdown
//

void hal_reboot (void);
void hal_shutdown (void);


//
// gdt and idt
//


unsigned long getGdt(void);
unsigned long getIdt(void);



void 
hal_setup_new_vectors_table_entry ( 
    int number, 
    unsigned long address 
);


// Vetores legados.
// Inicializando a tabela de vetores com os endereços das rotinas 
// usadas pelo assembler na inicialização de alguns 
// vetores de interrupção.
void hal_init_vectors_table (void);


void 
hal_idt_register_interrupt ( 
    unsigned long idt_location, 
    unsigned char i, 
    unsigned long callback );


void hal_default_handler (void);

void hal_init_handlers_table (void);

void hal_setup_new_handler ( int number, unsigned long callback );
void hal_invalidate_handler (int number);

#endif   



//
// End.
//

