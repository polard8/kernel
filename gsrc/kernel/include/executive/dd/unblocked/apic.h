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
 * Versão 1.0, 2015.
 */


/*
 * apic stuffs for x86.
 */
static inline void imcr_pic_to_apic(void);
static inline void imcr_apic_to_pic(void);


//
// End.
//

