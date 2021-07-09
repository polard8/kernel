/* 
 * File: link.ld
 * 
 * Linker script for kernel image.
 *
 * Base:
 *     0x30000000
 *
 * Entry point: 
 *     0x30001000
 *     Kernel entry point in 1pump/arch/x86/boot.asm. 
 */

OUTPUT_FORMAT("elf64-x86-64")
ENTRY(_kernel_begin)

SECTIONS 
{
 
    /* >> This is the base */
    /* 0x30000000: The ELF header starts at this address */
     /*. = 0x30000000;*/
     /*. = 0x30000000;*/

    . = 0x30001000;

    _kernel_begin = .;

    /* _kernel_begin  = .; it belong to .head_x86 segment */
    /* See: head_32.asm */

    /* >> This is the entry point */
    /* kernel text segment. Executable code of the program */
    /*.text 0x30001000:*/
    .text 0x30001000:
    {
        _code_begin = .;
        *(.head_x86_64)  *(.text)
        . = ALIGN(4096);
        _code_end = .; 
    }


    /* >> kernel read-only data. */
    .rodata :
    {
        _rodata_begin = .;
        *(.rdata)  *(.rodata) 
        . = ALIGN(4096);
        _rodata_end = .;
    }

    /* >> kernel data segment*/
    /* Read-write data (initialized) */
    /* data = Contains initialized global variables which are not constants */
    .data :  
    { 
        _data_begin = .; 
        *(.data)
        . = ALIGN(4096);
        _data_end = .; 
    }


    /* >> kernel bss segment, contains all the static uninitalized data */  
    /* Read-write data (uninitialized) and stack */
    /*COMMON ?? Contains the un-initialized global variables (not static). ??*/
    .bss : 
    { 
        _bss_begin = .; 
        *(COMMON)  *(.bss)
        . = ALIGN(4096);
        _bss_end = .; 
    }


    /* EOF - Fim do kernel */
    _kernel_end = .; 
}



