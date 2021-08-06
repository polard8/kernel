

#ifndef ____IDE_H
#define ____IDE_H


#define IDE_ATA    0
#define IDE_ATAPI  1



//#define HDD1_IRQ 14 
//#define HDD2_IRQ 15 


#define IDE_CMD_READ    0x20
#define IDE_CMD_WRITE   0x30
#define IDE_CMD_RDMUL   0xC4
#define IDE_CMD_WRMUL   0xC5


//
// IDE ports.
//
 
//0 primary master 
//1 primary slave 
//2 secondary master 
//3 secondary slave.
	
typedef enum {
	
	ideportsPrimaryMaster,      // 0
	ideportsPrimarySlave,       // 1
	ideportsSecondaryMaster,    // 2
	ideportsSecondarySlave      // 3
	
}ide_ports_t;	


typedef enum {
	
	idetypesPrimaryMaster,      // 0
	idetypesPrimarySlave,       // 1
	idetypesSecondaryMaster,    // 2
	idetypesSecondarySlave      // 3
	
}ide_types_t;			
	
	
typedef enum {
	
	idedevicetypesPATA,      // 0
	idedevicetypesSATA,       // 1
	idedevicetypesPATAPI,    // 2
	idedevicetypesSATAPI      // 3
	
}ide_device_types_t;	




 //
 // IDE ports support
 //

// Structure for a ide port.

struct ide_port_d 
{

    // #todo
    // Obeject header ?

    // Structure validation.
    int used;
    int magic;


    // The port number.
    //int id;
    uint8_t id;

    // PATA, SATA, PATAPI, SATAPI
    int type;

    char *name;

    unsigned short base_port;

    //
    // #todo
    // Salvar aqui o canal usado pela porta
    // e se o dispositivo é master ou slave.
    //
  
    uint8_t channel;   // #bugbug: penso que seja para primary ou secondary.
    uint8_t dev_num;   // #bugbug: penso que seja para master e slave.


    // ...


    // Dá pra colocar aqui mais informações sobre 
    // o dispositivo conectado a porta.
    // podemos usar ponteiros para estruturas.
};

// Four ports.
struct ide_port_d  ide_ports[4];



unsigned long ide_handler_address;


//estrutura para canais da controladora IDE. 
typedef struct ide_channel_d ide_channel_t; 
struct ide_channel_d
{

    int used;
    int magic;

    int id;

    // #todo: bigger
    char name[8];

    //
    // Cada canal vai ter uma porta diferente.
    // ex: canal 0, maste e canal 0 slave tem portas diferentes.	
	
	unsigned short port_base;
	unsigned char interrupt_number;
	
	//@todo: lock stuff.
	
	//@todo: semaphore
	
	//...
};


//estrutura para discos controlados pela controladora ide.

struct ide_disk_d
{

    int used;
    int magic;

    //id do disco ide.
    int id;

    // #todo: bigger
    char name[8];

    unsigned short Type;        // 0: ATA, 1:ATAPI.	

	//O canal usado pelo disco.
	//pode ser 0 ou 1, master ou slave.
	//ou outroscanais.
    
    struct ide_channel_d *channel; 

    //@todo: estrutura para partições.

    //
	// Podemos ter muitos elementos aqui.
	//
};

typedef struct ide_disk_d ide_disk_t;



/*
 * ide_d:
 *
 * #IMPORTANTE
 * Estrutura para configurar a interface IDE. 
 * Essa será a estrutura raiz para gerenciamento do controlador de IDE.
 */

struct ide_d
{
    // devemos colocar aqui um ponteiro para estrutura de informações 
    // sobre o dispositivo controlador de ide.	
	
    int current_port;
	
    struct ide_ports_d *primary_master; 
    struct ide_ports_d *primary_slave; 
    struct ide_ports_d *secondary_master; 
    struct ide_ports_d *secondary_slave; 
};

typedef struct ide_d ide_t;

struct ide_d IDE;



struct hdd_d
{
	//...
	int dummy;
	//unsigned long hdd_handler_address;
};
typedef struct hdd_d hdd_t;

//
// == prototypes ========================================
//


#endif    



