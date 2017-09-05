/*
 * File: ide.h
 *
 * Descrição:
 *     Header para rotinas de hardware para drivers de ide. hdd.
 *
 * //@todo ide struct 
 * 
 * Versão 1.0, 2015.
 */

 
//#define HDD1_IRQ 14 
//#define HDD2_IRQ 15 
 
unsigned long ide_handler_address;
 

typedef struct ide_d ide_t;
struct ide_d
{
	//...
	int dummy;
	//unsigned long ide_handler_address;
};
//ide_t *Ide;



typedef struct hdd_d hdd_t;
struct hdd_d
{
	//...
	int dummy;
	//unsigned long hdd_handler_address;
};
//hdd_t *Hdd;
 

 
void write_lba( unsigned long address, unsigned long lba);    //ide.
void read_lba( unsigned long address, unsigned long lba);     //ide.

void my_read_hd_sector( unsigned long ax, 
                        unsigned long bx, 
						unsigned long cx, 
						unsigned long dx );    //exec.
						
void my_write_hd_sector( unsigned long ax, 
                         unsigned long bx, 
						 unsigned long cx, 
						 unsigned long dx );    //exec.
				
/* 
 * init_hdd:
 *     Inicializa o módulo.
 */				
int init_hdd();

//
// End.
//
