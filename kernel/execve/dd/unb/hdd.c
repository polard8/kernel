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

//suporte ao read sector. usado no assembly.
extern unsigned long read_port_drive_and_lba_24_27;
extern unsigned long read_port_nos;
extern unsigned long read_port_lba_0_7;
extern unsigned long read_port_lba_8_15;
extern unsigned long read_port_lba_16_23;
extern unsigned long read_port_cmd;
extern unsigned long read_port_data;

//Variáveis internas
int hddStatus;
int hddError;
//...


void initialize_ide_ports (){
	
	int i;
	
	for ( i=0; i<4; i++ )
	{
	    ide_ports[i].id = (int) i;
        
		//Só iremos habilitar quando o dispositivo for encontrado.
		ide_ports[i].used = 0;
        ide_ports[i].magic = 0;
        
		ide_ports[i].type = -1;	

        ide_ports[i].name = "NO NAME";		
		
		ide_ports[i].base_port = (unsigned short) 0;
		
		//...
		
	};
};
 

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
    // Passando os argumentos.	
	hd_buffer = (unsigned long) ax;    //arg1 = buffer. 
	hd_lba = (unsigned long) bx;       //arg2 = lba.
	
	
	// #importante:
	// O QUE INDICA EM QUAL DISCO SERÁ ESCRITO É O CONJUNTO DE PORTAS.
	// DISCO TEM SEU CONJUNTO DE PORTAS.
	
	//cada disco terá um conjunbto diferente de portas.
	//criar um argumento que seleciona o disco.
	
    //suporte ao read sector. usado no assembly.
    
	//0 primary master 
	//1 primary slave 
	//2 secondary master 
	//3 secondary slave.
	
	int current_port = 0;  
	
	//#importante:
	//Criar função getCurrentPost()
	
	//current_port = (int) IDE.current_port;
	current_port = (int) ideportsPrimaryMaster;
	
	
	if (current_port < 0 || current_port >= 4)
	{
		//fail 
		
		printf("my_read_hd_sector: current_port fail");
		die();
	}
	
	
	// #importante:
	// Se temos uma currente port válida.
	
	read_port_drive_and_lba_24_27 = ide_ports[current_port].base_port + 6;  // 0x01F6;  //; Port to send drive and bit 24 - 27 of LBA
    read_port_nos                 = ide_ports[current_port].base_port + 2;  // 0x01F2;  // ; Port to send number of sectors
    read_port_lba_0_7             = ide_ports[current_port].base_port + 3;  // 0x1F3;   //  ; Port to send bit 0 - 7 of LBA
    read_port_lba_8_15            = ide_ports[current_port].base_port + 4;  // 0x1F4;   // ; Port to send bit 8 - 15 of LBA
    read_port_lba_16_23           = ide_ports[current_port].base_port + 5;  // 0x1F5 ;  //  ; Port to send bit 16 - 23 of LBA
    read_port_cmd                 = ide_ports[current_port].base_port + 7;  // 0x1F7;   //  ; Command port  ; Data port
    read_port_data                = ide_ports[current_port].base_port + 0;  //0x1F0;
			
	
	
	
	//#importante
	//#todo: 
	// + o número da porta deve vir via argumento.
	// + os números das portas devem estar configurados em estrutura. 
	// o número da porta pode estar na estrutura também.
	
    /*	
	
	switch (current_port)
	{
		case ideportsPrimaryMaster:
	        
			//read_port_drive_and_lba_24_27 = ide_ports[current_port].base_port + 6;// 0x01F6;  //; Port to send drive and bit 24 - 27 of LBA
           // read_port_nos = ide_ports[current_port].base_port + 2; // 0x01F2;                  // ; Port to send number of sectors
            //read_port_lba_0_7 = ide_ports[current_port].base_port + 3; // 0x1F3;               //  ; Port to send bit 0 - 7 of LBA
           // read_port_lba_8_15 = ide_ports[current_port].base_port + 4; // 0x1F4;              // ; Port to send bit 8 - 15 of LBA
           // read_port_lba_16_23 = ide_ports[current_port].base_port + 5; // 0x1F5 ;            //  ; Port to send bit 16 - 23 of LBA
           // read_port_cmd = ide_ports[current_port].base_port + 7; // 0x1F7;                   //  ; Command port  ; Data port
           // read_port_data = ide_ports[current_port].base_port + 0;  //0x1F0;
		
	        read_port_drive_and_lba_24_27 = 0x01F6;  //; Port to send drive and bit 24 - 27 of LBA
            read_port_nos = 0x01F2;                  // ; Port to send number of sectors
            read_port_lba_0_7 = 0x1F3;               //  ; Port to send bit 0 - 7 of LBA
            read_port_lba_8_15 = 0x1F4;              // ; Port to send bit 8 - 15 of LBA
            read_port_lba_16_23 = 0x1F5 ;            //  ; Port to send bit 16 - 23 of LBA
            read_port_cmd = 0x1F7;                   //  ; Command port  ; Data port
            read_port_data = 0x1F0;
		    break;
		
		case ideportsPrimarySlave:
	        read_port_drive_and_lba_24_27 = 0x01F6;  //; Port to send drive and bit 24 - 27 of LBA
            read_port_nos = 0x01F2;                  // ; Port to send number of sectors
            read_port_lba_0_7 = 0x1F3;               //  ; Port to send bit 0 - 7 of LBA
            read_port_lba_8_15 = 0x1F4;              // ; Port to send bit 8 - 15 of LBA
            read_port_lba_16_23 = 0x1F5 ;            //  ; Port to send bit 16 - 23 of LBA
            read_port_cmd = 0x1F7;                   //  ; Command port  ; Data port
            read_port_data = 0x1F0;
		
		    break;

		case ideportsSecondaryMaster:
	        read_port_drive_and_lba_24_27 = 0x01F6;  //; Port to send drive and bit 24 - 27 of LBA
            read_port_nos = 0x01F2;                  // ; Port to send number of sectors
            read_port_lba_0_7 = 0x1F3;               //  ; Port to send bit 0 - 7 of LBA
            read_port_lba_8_15 = 0x1F4;              // ; Port to send bit 8 - 15 of LBA
            read_port_lba_16_23 = 0x1F5 ;            //  ; Port to send bit 16 - 23 of LBA
            read_port_cmd = 0x1F7;                   //  ; Command port  ; Data port
            read_port_data = 0x1F0;
		
		    break;

		case ideportsSecondarySlave:
	        read_port_drive_and_lba_24_27 = 0x01F6;  //; Port to send drive and bit 24 - 27 of LBA
            read_port_nos = 0x01F2;                  // ; Port to send number of sectors
            read_port_lba_0_7 = 0x1F3;               //  ; Port to send bit 0 - 7 of LBA
            read_port_lba_8_15 = 0x1F4;              // ; Port to send bit 8 - 15 of LBA
            read_port_lba_16_23 = 0x1F5 ;            //  ; Port to send bit 16 - 23 of LBA
            read_port_cmd = 0x1F7;                   //  ; Command port  ; Data port
            read_port_data = 0x1F0;
		
		    break;

	    //ERROR
	    default:
		    break;
	};
	
	*/
	
	// Read sector. (ASM)
	os_read_sector(); 	
    
	//#todo: deletar esse return.
	//testar sem ele antes.
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
	
	
	initialize_ide_ports ();


    //
    // IDE struct
    //	
	
	IDE.primary_master = NULL;
	IDE.primary_slave = NULL;
	IDE.secondary_master = NULL;
	IDE.secondary_slave = NULL;
	
	
	//
	// #importante:
	// Estamos determinando qual é a porta atual.
	// Mas precisamos de algum jeito de obter isso.
	// o boot loader deve passar essa informação.
	//
	
	IDE.current_port = ideportsPrimaryMaster;

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

