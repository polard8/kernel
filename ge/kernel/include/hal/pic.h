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
#define ____PIC_H
 

//Estrutura para gerenciar as irqs do PIC.
typedef struct irq_d irq_t;
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
	
    struct irq_d *next;
};
//Master.
irq_t *Irq0;    //system timer.
irq_t *Irq1;    //ps/2 keyboard.
irq_t *Irq2;
irq_t *Irq3;
irq_t *Irq4;
irq_t *Irq5;
irq_t *Irq6;    //floppy.
irq_t *Irq7;
//Slave.
irq_t *Irq8;    //cmos/rtc
irq_t *Irq9;
irq_t *Irq10;    //compartilhado.
irq_t *Irq11;
irq_t *Irq12;    //ps/2 mouse.
irq_t *Irq13;
irq_t *Irq14;    //primary IDE.
irq_t *Irq15;    //secondary IDE.
//


typedef struct pic_d pic_t;
struct pic_d
{
	object_type_t objectType;
	object_class_t objectClass;

    int dummy;
	
	//int master;
	//int slave;
	
    //Master.
    //irq_t *Irq0;    //system timer.
    //irq_t *Irq1;    //ps/2 keyboard.
    //irq_t *Irq2;
    //irq_t *Irq3;
    //irq_t *Irq4;
    //irq_t *Irq5;
    //irq_t *Irq6;    //floppy.
    //irq_t *Irq7;
    //Slave.
    //irq_t *Irq8;    //cmos/rtc
    //irq_t *Irq9;
    //irq_t *Irq10;    //compartilhado.
    //irq_t *Irq11;
    //irq_t *Irq12;    //ps/2 mouse.
    //irq_t *Irq13;
    //irq_t *Irq14;    //primary IDE.
    //irq_t *Irq15;    //secondary IDE.
	
};
struct pic_d *Pic;


//
// == IRQ Handlers =======================================
//

// See: pit.c
void irq0_TIMER (void);

// See: keyboard.c
void irq1_KEYBOARD (void);

// See: rtc.c
void irq8_RTC (void); 

// See: nicintel.c
void irq_E1000 (void);

// See: mouse.c
void irq12_MOUSE (void);

// See: pci.c
// Each one will be shared by up to 4 devices.
void irq_SHARED0 (void);
void irq_SHARED1 (void);
void irq_SHARED2 (void);
void irq_SHARED3 (void);

// See: atairq.c
void irq14_PRIMARY_IDE (void);
void irq15_SECONDARY_IDE (void);



#endif   



//
// End.
//

