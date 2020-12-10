/* 
 * File: link.ld
 * 
 * Linker script for i386 kernel image.
 *
 * Base:
 *     0xc0000000
 *
 * Entry point: 
 *     0xc0001000
 *     Kernel entry point in 1pump/arch/x86/boot.asm. 
 */


OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_kernel_begin)  

SECTIONS
{ 

    /* 0xc0000000: elf header.*/

    /* _kernel_begin  = .; */

    /* kernel text segment. Executable code of the program */
    .text 0xC0001000:      
    {
        _code_begin = .;            
        *(.head_x86)       /* x86 asm stuff */
        *(.text)
        _code_end = .; 
        . = ALIGN(4096);
    }


    /* Read-only data. */
    .rodata :
    {
        _rodata_begin = .;
        *(.rdata)          /*contains read-only data*/
        *(.rodata)         /*contains read-only data*/
        _rodata_end = .;
        . = ALIGN(4096);
    }


    /* Read-write data (initialized) */
    .data :                /* kernel data segment*/
    { 
        _data_begin = .;            
        *(.data)           /*contains initialized global variables which are not constants*/
        _data_end = .; 
        . = ALIGN(4096);
    }


    /* Read-write data (uninitialized) and stack */
    .bss :                 /* kernel bss segment, contains all the static uninitalized data */  
    { 
        _bss_begin = .; 
        *(COMMON)          /*?? Contains the un-initialized global variables (not static). ??*/
        *(.bss)
        _bss_end = .; 
        . = ALIGN(4096);
    }


    /* EOF - Fim do kernel */
    _kernel_end = .; 
}

