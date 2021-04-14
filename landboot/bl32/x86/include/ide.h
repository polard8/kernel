/*
 * File: ide.h
 *
 * Descrição:
 *     Header para rotinas de hardware para drivers de ide. hdd.
 *
 * #todo 
 * ide struct 
 * 
 * History:
 *     2015
 */


//
// IDE ports.
//


int g_current_ide_channel;
int g_current_ide_device;



// 0 primary master 
// 1 primary slave 
// 2 secondary master 
// 3 secondary slave.

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

    idedevicetypesPATA,    // 0
    idedevicetypesSATA,    // 1
    idedevicetypesPATAPI,  // 2
    idedevicetypesSATAPI   // 3

}ide_device_types_t;


//
// IDE ports support
//

struct ide_ports_d 
{
    uint8_t id;

    int used;
    int magic;

    // PATA, SATA, PATAPI, SATAPI
    int type;

    unsigned short base_port;

    char *name;

    //...

    // Dá pra colocar aqui mais informações sobre 
    // o dispositivo conectado a porta.
    // podemos usar ponteiros para estruturas.
};

struct ide_ports_d ide_ports[4];


#define IDE_ATA    0
#define IDE_ATAPI  1

#define ATA_MASTER  0
#define ATA_SLAVE   1 


//#define HDD1_IRQ 14 
//#define HDD2_IRQ 15 


#define IDE_CMD_READ    0x20
#define IDE_CMD_WRITE   0x30
#define IDE_CMD_RDMUL   0xC4
#define IDE_CMD_WRMUL   0xC5
 
unsigned long ide_handler_address;
 

//estrutura para canais da controladora IDE. 
typedef struct ide_channel_d ide_channel_t; 
struct ide_channel_d
{
    int id;

    int used;
    int magic;

    char name[8];

    // Cada canal vai ter uma porta diferente.
    // ex: canal 0, maste e canal 0 slave tem portas diferentes.	

    unsigned short port_base;
    unsigned char interrupt_number;

	//@todo: lock stuff.
	
	//@todo: semaphore
	
	//...
};

struct ide_channel_d idechannelList[8];



//estrutura para discos controlados pela controladora ide.
typedef struct ide_disk_d ide_disk_t;
struct ide_disk_d
{
	//id do disco ide.
	int id;
	
	int used;
	int magic;
	
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


 
 
/*
 * ide_d:
 *
 * #IMPORTANTE
 * Estrutura para configurar a interface IDE. 
 * Essa será a estrutura raiz para gerenciamento do controlador de IDE.
 */

typedef struct ide_d ide_t;
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
struct ide_d IDE;



typedef struct hdd_d hdd_t;
struct hdd_d
{
	//...
	int dummy;
	//unsigned long hdd_handler_address;
};
//hdd_t *Hdd;
 

//
// lba
//

// white lba on ide device.
void 
write_lba( 
    unsigned long address, 
    unsigned long lba );

// read lba on ide device.
void 
read_lba ( 
    unsigned long address, 
    unsigned long lba );


//
// read or write a sector using PIO mode.
//

int 
pio_rw_sector ( 
    unsigned long buffer, 
    unsigned long lba, 
    int rw, 
    int port,
    int slave ); 


void 
my_read_hd_sector ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx ); 

void 
my_write_hd_sector ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx ); 


/* 
 * init_hdd:
 *     Inicializa o módulo.
 */

int init_hdd(void);

//
// End.
//


