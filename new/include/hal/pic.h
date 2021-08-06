/*
 * File: pic.h
 *
 * Descrição:
 *     Header para o driver do controlador PIC.
 *     Programmable Interrupt Controller.
 *
 *   Exemplo: 8259A.
 *
 * 2015 - Created by Fred Nora.
 */
 
 
#ifndef ____PIC_H
#define ____PIC_H    1

// Estrutura para gerenciar as irqs do PIC.
struct irq_d
{
	//object_type_t objectType;
	//object_class_t objectClass;

    int id;
    int used;
    int magic;

    unsigned long irq_address;      //(hardware.s)
    unsigned long handler_address;  
	//...

    char *name; //description.

    struct irq_d  *next;
};

struct pic_d
{
	object_type_t objectType;
	object_class_t objectClass;

    int dummy;

    // 8 entries for pic controller.
};
struct pic_d *Pic;



//
// == IRQ Handlers =======================================
//

// See: x86/pit.c
__VOID_IRQ 
irq0_TIMER (void);


// See: keyboard.c
__VOID_IRQ 
irq1_KEYBOARD (void);


// See: x86/rtc.c
__VOID_IRQ 
irq8_RTC (void); 


// See: e1000.c
//__VOID_IRQ 
//irq_E1000 (void);


// See: mouse.c
__VOID_IRQ 
irq12_MOUSE (void);

// See: pci.c
// Each one will be shared by up to 4 devices.
__VOID_IRQ 
irq_SHARED0 (void);
__VOID_IRQ 
irq_SHARED1 (void);
__VOID_IRQ 
irq_SHARED2 (void);
__VOID_IRQ 
irq_SHARED3 (void);

// See: atairq.c
__VOID_IRQ 
irq14_PRIMARY_IDE (void);
__VOID_IRQ 
irq15_SECONDARY_IDE (void);


#endif    



