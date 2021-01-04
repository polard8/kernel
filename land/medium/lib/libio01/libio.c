/*
 * File: libio.c
 * 
 * Ring 3 i/o library.
 * It's very dangerous.
 * But it helps to implement drivers in ring3 to port it 
 * to kernel in the future.
 * 
 * 2019 - Created by Fred Nora.
 */

// [ libio ]
// I just created a ring3 i/o library, 
// given to the ring3 processes full access to the i/o ports. Why not?!
// This way i can build new drivers in ring 3, 
// with no risk for the system. So I will only port to ring0 the well tested drivers.  


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


#include <libio.h>


// Protótipo da system call.

unsigned long
__libio_system_call ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx );

/*
 ********************************
 * __libio_system_call:
 *     system call usada pelo gdeio para acessar as portas.
 */

unsigned long
__libio_system_call ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{
    unsigned long Ret = 0;

    // System interrupt.

    asm volatile ( " int %1 \n"
        : "=a"(Ret)
        : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );


    return (unsigned long) Ret; 
}


//
// == IN ======================================================
//

// #bugbug: return size
// retorna o valor.
unsigned char libio_inport8 (unsigned int port)
{
    unsigned char _Ret=0;


    _Ret = (unsigned char) __libio_system_call ( 126, 
                               (unsigned long) 8, 
                               (unsigned long) port, 
                               (unsigned long) port );

    return (unsigned char) _Ret;
}


// #bugbug: return size
//retorna o valor.
unsigned short libio_inport16 (unsigned int port)
{
    unsigned short _Ret=0;
    
    _Ret = (unsigned short) __libio_system_call ( 126, 
                                (unsigned long) 16, 
                                (unsigned long) port, 
                                (unsigned long) port );
    return (unsigned short) _Ret;
}


//retorna o valor.
unsigned long libio_inport32 (unsigned int port)
{
    unsigned long _Ret=0;
    
    _Ret = (unsigned long) __libio_system_call ( 126, 
                               (unsigned long) 32, 
                               (unsigned long) port, 
                               (unsigned long) port );
    return (unsigned long) _Ret;
}


//
// == OUT ======================================================
//

void libio_outport8 ( unsigned int port, unsigned char value)
{
    __libio_system_call ( 127, 
         (unsigned long) 8, 
         (unsigned long) port, 
         (unsigned long) value );
}


void libio_outport16 ( unsigned int port, unsigned short value)
{
    __libio_system_call ( 127, 
        (unsigned long) 16, 
        (unsigned long) port, 
        (unsigned long) value );
}


void libio_outport32 ( unsigned int port, unsigned long value)
{
    __libio_system_call ( 127, 
        (unsigned long) 32, 
        (unsigned long) port, 
        (unsigned long) value );
}


//
// End.
//


