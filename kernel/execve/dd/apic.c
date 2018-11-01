/*
 * File: apic.c
 *
 *    Controlador APIC.
 *    Arquivo principal do módulo interno do kernel de 32bit. 
 *
 *    APIC - Advanced Programmable Interrupt Controller.
 *
 *   Stuffs:
 *       +Discrete APIC.
 *       +Integrated local APICs.
 *       +APIC timer.
 *       +I/O APICs.
 *
 * Versão 1.0, 2015.
 */
 

#include <kernel.h>


//@todo: definir porta 70h usada nesse arquivo.




//
// Variáveis internas.
//

//int apicStatus;
//int apicError;
//...



/*
 * imcr_pic_to_apic:
 *
 * Handle interrupt mode configuration register (IMCR).
 *
 * This register controls whether the interrupt signals that reach 
 * the BSP come from the master PIC or from the local APIC. 
 *
 * Before entering Symmetric I/O Mode, either the BIOS or 
 * the operating system must switch out of PIC Mode by changing the IMCR.
 *
 */
static inline void imcr_pic_to_apic(void)
{
	//Select IMCR register.
    outb(0x70, 0x22);
	
	//NMI and 8259 INTR go through APIC. 
    outb(0x01, 0x23);
	
	//Nothing.
};

 
static inline void imcr_apic_to_pic(void)
{
	//Select IMCR register.
    outb(0x70, 0x22);
     
	//NMI and 8259 INTR go directly to BSP.
    outb(0x00, 0x23);
	
	//Nothing.
};


/*
int init_apic();
int init_apic()
{
    
 
done:
    g_driver_apic_initialized = 0;
    return (int) 0;
};
*/


/*
 * Constructor.
int apicApic()
{};
*/

/*
int apicInit()
{};
*/

//
// End.
//
