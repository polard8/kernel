/*
 * File: portsx86.c
 *
 * Descrição:
 *     Interface de abstração para acesso as portas.
 *     A idéia é que um módulo do kernel base possa acessar as portas sem se 
 * preocupar com o tipo de arquitetura. Mas por enquanto estamos apenas 
 * suportando a arquitetura intel.
 *
 *     O acesso as portas também será oferecido na forma de serviços, para
 * que processos servidores também possam configurar o hardware diretamente.
 * Logicamente algum tipo de filtro será criado, para conferir a permissão.
 *
 *     @todo: As rotinas aqui, desviarão a chamada para para a rotina da 
 * arquitetura atual.
 *
 *    Obs: O HAL deve chamar essas rotinas e não os programas.
 *
 *    Obs: Por enquanto a unica arquitetura suportada aqui
 *         é a arquitetura PC x86.
 *
 *    ??
 *    See: ports.h
 *
 *    2015 - Create by Fred Nora.
 *    2019 - New function names for i/o stuff.
 */

// goal:
//     in8  in16  in32
//     out8 out16 out32


// #bugbug
// Talvez o melhor seria usar 'unsigned long' ao inves de 'int'
// para as portas. Ou ainda 'unsigned int'.


#include <kernel.h>




unsigned char in8 (unsigned int port)
{
    unsigned char ret=0;
 
    asm volatile ("inb %%dx, %%al" : "=a"(ret): "d"(port) );

    return (unsigned char) ret;
}

unsigned short in16 (unsigned int port)
{
    unsigned short ret=0;

    asm volatile ("inw %%dx, %%ax" : "=a" (ret) : "d" (port) );

    return (unsigned short) ret;
}

unsigned long in32 (unsigned int port)
{
    unsigned long ret=0;

    asm volatile ("inl %%dx,%%eax" : "=a" (ret) : "d"(port) );

    return (unsigned long) ret;
}



void out8 ( unsigned int port, unsigned char data )
{
    asm volatile ("outb %%al, %%dx" :: "a" (data), "d" (port) );
}

void out16 (unsigned int port, unsigned short data)
{
    asm volatile ("outw %%ax, %%dx" :: "a" (data), "d" (port) );
}

void out32 ( unsigned int port, unsigned long data )
{
    asm volatile ("outl %%eax, %%dx" :: "a" (data), "d" (port) );
}


//
// --------------
//



void __x86_io_delay (void)
{
    asm ("xorl %%eax, %%eax" ::);
    asm ("outb %%al, $0x80" ::);
    return;
}



void wait_ns (int count)
{
    count /= 100; 

    while (--count)
        io_delay ();
}


unsigned long portsx86_IN ( int bits, unsigned long port ){

    switch (bits)
    {
        case 8:
            return (unsigned long) in8 ((int) port);
            break;

        case 16:
            return (unsigned long) in16 ( (int) port);
            break;

        case 32:
            return (unsigned long) in32 ( (int) port);
            break;

        default:
            debug_print ("portsx86_IN: FAIL\n");
            return 0;
            break;
    };
}


void 
portsx86_OUT ( 
    int bits, 
    unsigned long port, 
    unsigned long value )
{

    switch (bits)
    {
        case 8:
            out8 ( (int) port, (unsigned char) value );
            return;
            break;

        case 16:
            out16 ( (int) port, (unsigned short) value );
            return;
            break;

        case 32:
            out32 ( (int) port, (unsigned long) value );
            return;
            break;

        default:
            debug_print ("portsx86_OUT: FAIL\n");
            return;
            break;
    };
}


//
//  End.
//

