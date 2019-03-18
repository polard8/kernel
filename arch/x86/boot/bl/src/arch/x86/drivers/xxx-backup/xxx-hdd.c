// #funciona
// sem o suporte ao controlador ide feito pelo nelson.

/*
 * File: hdd.c 
 *
 * Descrição:
 *   Driver de HDD usado pelo Boot Loader.
 *
 * Objetivo:
 *    +Suporte a IDE legado.
 *    +Suporte a SATA via PCI.
 *
 * @todo: 
 * Criar rotina de identificação do hd, configuração e inicialização.
 *    
 * 2015 - Created by Fred Nora.
 */

 
// #todo:
// No kernel temos um esquema melhorado de read e write  
// em todos os canaid IDE. Devemos reproduzir isso aqui.
 
 
#include <bootloader.h>

extern void reset_ide0();	
extern void os_read_sector();
extern void os_write_sector();

//Usados por read e write.
extern unsigned long hd_buffer;
extern unsigned long hd_lba;


/*
 *************************************
 * my_read_hd_sector: 
 *     Lê um setor do hd IDE.
 *     isso poderia retornar int.
 *
 * eax - buffer
 * ebx - lba
 * ecx - null
 * edx - null
 */
 
void 
my_read_hd_sector ( unsigned long ax, 
                    unsigned long bx, 
					unsigned long cx, 
					unsigned long dx )
{	
    hd_buffer = (unsigned long) ax;   
    hd_lba = (unsigned long) bx;    		

	// Ler setor do hd. 
	// Usando rotina em assembly.
	// #obs: Essa rotina somente lê no canal primário master.
	
	// #todo
	// Precisamos usara a rotina que inicializa o controlador de IDE.
	
	os_read_sector();	
    return;
};


/*
 * my_write_hd_sector: 
 *     Grava um setor no hd IDE.
 *     isso poderia retornar int.
 *
 * eax - buffer
 * ebx - lba
 * ecx - null
 * edx - null
 */
 
void 
my_write_hd_sector ( unsigned long ax, 
                     unsigned long bx, 
					 unsigned long cx, 
					 unsigned long dx )
{	
    hd_buffer = (unsigned long) ax;    
    hd_lba = (unsigned long) bx;    

	//Gravar setor no hd.	
	os_write_sector(); 
    return;
};   




/*
 ******************************************************
 * limpa_root: 
 *     Zera o buffer e grava zeros no hd.
 *     #todo: Rever a validade dessas posições de memória.
 *     #todo isso deve ir para /fs
 */
 
void limpa_root (){
	
	
	//#CANCELADA.
	
	//#bugbug: ESSE VALOR DE MEMÓRIA É INACEITÁVEL.
	//O SISTEMA TEN QUE FUNCIONAR COM O MÍNIMO DE 16MB

/*	
	unsigned char *root = (unsigned char *) 0x04700000;
    unsigned long i;
    
    i = (512*4);
	
    while(i > 0){
        root[i] = 0;    
        i--;
    };
	
    //Salva um setor do o rootdir no setor 2.       
	write_lba(0x04700000, 2);
	
    //Nothing. 
done:
    return;
	
*/	
};



/*
 * limpa_fat: 
 *     Zera o buffer e grava zeros no hd.
 *     @todo: Rever a validade dessas posições de memória.
 *     #todo isso deve ir para /fs
 */
void limpa_fat (){
	
	//#CANCELADA.
	
	//#bugbug: ESSE VALOR DE MEMÓRIA É INACEITÁVEL.
	//O SISTEMA TEN QUE FUNCIONAR COM O MÍNIMO DE 16MB	
	
/*
	
    unsigned char *fat_base = (unsigned char *) 0x04500000;
    unsigned long i;
    
    i = (512*4);
     
    while(i > 0){
        fat_base[i] = 0;    
        i--;
    };
 
	 
    //Salva 4 setor da fat no hd. 
    //@todo: #bugbug ESSES VALORES ESTÃO ESTRANHOS. ???
	
	write_lba(0x04500000, 3);
    write_lba(0x04500200, 4);      
    write_lba(0x04500400, 5);
    write_lba(0x04500600, 6);
    
	//@todo: usar while.      
    
done:
	return; 
    */
};


//
// End.
//

