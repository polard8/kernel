/*
 * File: apic.h
 *
 * Descrição:
 *     Header para o driver do controlador APIC.
 *     Advanced Programmable Interrupt Controller
 *
 *     Exemplo:
 *     82489DX.
 *     82093AA for PIIX3-based systems.
 *         
 * Variantes:
 *    xAPIC, x2APIC.
 *
 * 2015 - Created by Fred Nora.
 */


#ifndef ____APIC_H
#define ____APIC_H


// Check presence of apic.
int check_apic (void);

void cpu_set_apic_base(unsigned long apic);
unsigned long cpu_get_apic_base(void); 



// apic stuffs for x86.
static inline void imcr_pic_to_apic (void);
static inline void imcr_apic_to_pic (void);


#endif    //____APIC_H


//
// End.
//

