/*
 * File: unb\hdd.c 
 * 
 * Descrição:
 *     Interface de acesso a discos do tipo HDD.
 *     Deve haver um driver para cada marca suportada.
 *     Driver IDE presente dentro do kernel.
 *
 *     Rotinas de hardware. Não são operações no
 *     sistema de arquivos.
 *
 *     O sistema de arquivos chama essas rotinas.
 *     O gerenciamento de discos chama essas rotinas.
 *
 * Obs: Esse módulo é um gerenciador de controlador de hard disk
 *      Aqui não importa se é ATA ou Serial ATA. Rotinas específicas
 * serão executadas pela classe apropriada de interface, aqui é ais geral.
 * Por exemplo: Sondagem por tipos de dispositivos de armazenamento.
 * Há muitos tipos de hard drive. Esse módulo é somente para hard drives.
 *
 *     Ambiente: (RING 0).
 *
 * #obs: Vamos montar dispositivos em /DEV
 *
 *    2013 - Created by Fred Nora.
 *    2016 - Revision.
 */

 
 
/*
 hd info:
 =======
 PIIX3 ATA: LUN#0: disk, PCHS=963/4/17, total number of sectors 65536. (Oracle Virtualbox)
 estatística de hoje:
 (apenas leitura, usando PIO mode)
00:01:59.902737 /Devices/IDE0/ATA0/Unit0/AtapiDMA            0 times
00:01:59.902742 /Devices/IDE0/ATA0/Unit0/AtapiPIO            0 times
00:01:59.902747 /Devices/IDE0/ATA0/Unit0/DMA                 0 times
00:01:59.902753 /Devices/IDE0/ATA0/Unit0/PIO              1699 times  ***
00:01:59.902760 /Devices/IDE0/ATA0/Unit0/ReadBytes      869376 bytes  ***
00:01:59.902766 /Devices/IDE0/ATA0/Unit0/WrittenBytes        0 bytes
 */ 
 
 
#include <kernel.h>


/*
 * Externs.
 */
 
extern void os_read_sector();
extern void os_write_sector();
extern void reset_ide0();	


//Usadas por read e write.
extern unsigned long hd_buffer;
extern unsigned long hd_lba;



//Variáveis internas
int hddStatus;
int hddError;
//...



//interna
static void hdd_ata_pio_read ( int p, void *buffer, int bytes ){
	
    __asm__ __volatile__ (\
                "cld;\
                rep; insw":: "D" (buffer),\
                "d" ( ide_ports[p].base_port + 0 ),\
                "c" (bytes/2));
};

/*
 rw_sector
 
 IN:
    buffer - Buffer address
	lba - LBA number 
    rw - Flag read or write.	

    //inline unsigned char inportb (int port)
    //outportb ( int port, int data )
	
 */
int pio_rw_sector ( unsigned long buffer, unsigned long lba, int rw, int port ) 
{
	
	unsigned long tmplba = (unsigned long) lba;
	
	
	if ( port < 0 || port >= 4 )
		return -1;
	
	
	//0x01F6 ; Port to send drive and bit 24 - 27 of LBA
	tmplba = tmplba >> 24;	
	tmplba = tmplba | 0x000000E0; //1110 0000b;
	outportb ( (int) ide_ports[port].base_port + 6 , (int) tmplba );
	
	//0x01F2 ; Port to send number of sectors
	outportb ( (int) ide_ports[port].base_port + 2 , (int) 1 );
	
	
	//0x1F3  ; Port to send bit 0 - 7 of LBA
	tmplba = lba;
    tmplba = tmplba & 0x000000FF;	
	outportb ( (int) ide_ports[port].base_port + 3 , (int) tmplba );
	
	
	//0x1F4  ; Port to send bit 8 - 15 of LBA
	tmplba = lba;
	tmplba = tmplba >> 8;	
    tmplba = tmplba & 0x000000FF;	
	outportb ( (int) ide_ports[port].base_port + 4 , (int) tmplba );
	

	//0x1F5  ; Port to send bit 16 - 23 of LBA
	tmplba = lba;
	tmplba = tmplba >> 16;	
    tmplba = tmplba & 0x000000FF;	
	outportb ( (int) ide_ports[port].base_port + 5 , (int) tmplba );
	
	
	// 0x1F7       ; Command port
	//rw
	rw = rw & 0x000000FF;	
	outportb ( (int) ide_ports[port].base_port + 7 , (int) rw );
	
	
	//
	//
	//
	
	unsigned char c; 
	
again:
	
	c = (unsigned char) inportb ( (int) ide_ports[port].base_port + 7);
	
	c = ( c & 8 );
	
	if ( c == 0 )
	{
	   goto again;	
	}
    
	
	//
	// ler
	//
	
	hdd_ata_pio_read ( (int) port, (void *) buffer, (int) 512 );
	
    return 0;	
} ;
 

/*
 *****************************************
 * my_read_hd_sector:
 * eax - buffer
 * ebx - lba
 * ecx - null
 * edx - null
 * Opção: void hddReadSector(....)
 */
 
void my_read_hd_sector ( unsigned long ax, 
                         unsigned long bx, 
						 unsigned long cx, 
						 unsigned long dx )
{
	
	// #IMPORTANTE:
	//
	// Ok, isso funcionou, mas teve que chamar a rotina de inicialização
	// do IDE num momento específico da inicialização do sistema.
	
 
	// read test (buffer, lba, rw flag, port number )
     pio_rw_sector ( (unsigned long) ax, (unsigned long) bx, (int) 0x20, (int) 0 );		
 
	
	/*
	
    // Passando os argumentos.	
	hd_buffer = (unsigned long) ax;    //arg1 = buffer. 
	hd_lba = (unsigned long) bx;       //arg2 = lba.
	
	// Read sector. (ASM)
	os_read_sector(); 	
    
	//#todo: deletar esse return.
	//testar sem ele antes.
	
	*/
	return;
};


/*
 *************************************
 * my_write_hd_sector:
 * eax - buffer
 * ebx - lba
 * ecx - null
 * edx - null
 * Opção: void hddWriteSector(....)
 */
void my_write_hd_sector ( unsigned long ax, 
                          unsigned long bx, 
						  unsigned long cx, 
						  unsigned long dx )
{
    // Passando os argumentos.	
	hd_buffer = (unsigned long) ax;    //arg1 = buffer. 
	hd_lba = (unsigned long) bx;       //arg2 = lba.
	
	// Write sector. (ASM)	
    // entry/x86/head/hwlib.inc
	
	os_write_sector(); 
	
	//#todo: deletar esse return.
	//testar sem ele antes.	
	return;
};   


/*
 ***************************************
 * init_hdd:
 *     Inicializa o driver de hd.
 *     @todo: Mudar para hddInit().
 */
int init_hdd (){
	
    //
    // @todo: We need to do something here.
    //	

//done:

    g_driver_hdd_initialized = (int) 1;
    
	return (int) 0;
};


/*
int hddInit();
int hddInit()
{
    hddStatus = 0;
    hddError = 0;
    //...

	init_hdd();
    return (int) 0;	
};
*/

//
// End.
//

