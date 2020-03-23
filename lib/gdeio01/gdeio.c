/*
 * File: gdeio.c
 * 
 * 2019 - Created by Fred Nora.
 */



// Acesso a portas para processos em user mode.
// Será usado pelos servidores e drivers.
// O privilégio será baseado em 'usuário' e 'desktop'.

//# todo
//+ usar system_call para acessar o kernel
//+ criar lá no kernel as rotinas que atendem essa system call.


// #todo
// Essa bibliorteca poderia ter uma parte relativa
// a autorizações.

// #todo
// Precisamos checar essas chamadas ao kernel.


#include <gdeio.h>


// Protótipo da system call.

void *
__gdeio_system_call ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx );

/*
 ********************************
 * __gdeio_system_call:
 *     system call usada pelo gdeio para acessar as portas.
 */

void *
__gdeio_system_call ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{
    int Ret = 0;

    // System interrupt.

    asm volatile ( " int %1 \n"
        : "=a"(Ret)
        : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );


    return (void *) Ret; 
}



// #bugbug: return size
//retorna o valor.
unsigned char gde_inport8 (unsigned short port)
{
    return (unsigned char) __gdeio_system_call ( 126, 
                               (unsigned long) 8, 
                               (unsigned long) port, 
                               (unsigned long) port );
}


// #bugbug: return size
//retorna o valor.
unsigned short gde_inport16 (unsigned short port)
{
    return (unsigned short) __gdeio_system_call ( 126, 
                                (unsigned long) 16, 
                                (unsigned long) port, 
                                (unsigned long) port );
}


//retorna o valor.
unsigned long gde_inport32 (unsigned short port)
{
    return (unsigned long) __gdeio_system_call ( 126, 
                               (unsigned long) 32, 
                               (unsigned long) port, 
                               (unsigned long) port );
}


void gde_outport8 ( unsigned short port, unsigned char value)
{
    __gdeio_system_call ( 127, 
         (unsigned long) 8, 
         (unsigned long) port, 
         (unsigned long) value );
}


void gde_outport16 ( unsigned short port, unsigned short value)
{
    __gdeio_system_call ( 127, 
        (unsigned long) 16, 
        (unsigned long) port, 
        (unsigned long) value );
}


void gde_outport32 ( unsigned short port, unsigned long value)
{
    __gdeio_system_call ( 127, 
        (unsigned long) 32, 
        (unsigned long) port, 
        (unsigned long) value );
}


//
// End.
//


