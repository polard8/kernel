/*
 * File: pic.c
 *
 *    Controlador PIC.
 *    Arquivo principal do módulo interno do kernel de 32bit. 
 *    PIC - Programmable Interrupt Controller
 *
 * Versão 1.0, 2016.
 */
 

#include <kernel.h>
  

//
//  PIC - Programmable Interrupt Controller register addresses.
//
 
//Ninguém além do driver precisa dessas constantes. 
// master PIC.
#define PIC1_PORT0 0x20  
#define PIC1_PORT1 0x21
// slave PIC.
#define PIC2_PORT0 0x0A0 
#define PIC2_PORT1 0x0A1
 
 
//
// Variáveis internas.
// 

int picStatus;
int picError;
//... 
 
 

 
/* 
int picInit();
int picInit()
{
    picStatus;
    picError;

    return (int) 0;	
} 
*/
 
//
// Fim.
//

