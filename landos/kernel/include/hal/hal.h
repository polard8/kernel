

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



// Estrutura para informações sobre a placa mãe.  
struct motherboard_d
{
	int mobodummy;
    //...	
};  


//Estrutura de disco. @todo: Colocar em outro arquivo.  
struct drive_context_d 
{
    unsigned long Drive;

    unsigned long Cylinders;
    unsigned long Heads;
    unsigned long Sectors;
};
struct drive_context_d *DriveContext;  

//Firmware:
//Estrutura para todos os componentes de firmware presentes.
struct firmware_d
{
	int dummy;
	//bios
	//...	
};  
struct firmware_d *Firmware;



// Hardware:
// Estrutura para todos os componentes de hardware presentes.

struct hardware_d
{
    //#todo


	// MainBoard info.
	struct motherboard_d *MotherBoard;

	// Processor info.
	//struct processor_d *Processor;   //@todo: mudar para processo_d
	int ProcessorArchitecture;
	int NumberOfProcessors;
	
	// ...

	// RTC CMOS info.

	struct rtc_d *Rtc;

    // ...

};

struct hardware_d  *Hardware;  



//
// == prototypes =================
//

void hal_set_machine_type ( unsigned long type );
unsigned long hal_get_machine_type (void);


void hal_reboot (void);
void hal_shutdown (void);

void hal_vsync (void);

//
// Speaker support.
//

//OUT - Play sound using built in speaker
void hal_speaker_on (void);

//IN - make it shutup
void hal_speaker_off (void);

// Testando o beep;
void hal_test_speaker (void);

int init_hal (void);

int hal_hardware_detect (void);
void init_cpu (void);

#endif    



