/*
 * File: pic.h
 *
 * Descrição:
 *     Header para o driver do controlador PIC.
 *     Programmable Interrupt Controller.
 *
 *   Exemplo: 8259A.
 *
 * Versão 1.0, 2015.
 */
 
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
	
	//callback
	
	///	
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
pic_t *Pic;


//
// End.
//

