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
 
    /* >> This is the base */
    /* 0xc0000000: The ELF header starts at this address */
     . = 0xC0000000;

    /* _kernel_begin  = .; it belong to .head_x86 segment */
    /* See: head_32.asm */

    /* >> This is the entry point */
    /* kernel text segment. Executable code of the program */
    .text 0xC0001000:
    {
        _code_begin = .;
        *(.head_x86)  *(.text)
        _code_end = .; 
        . = ALIGN(4096);
    }


    /* >> kernel read-only data. */
    .rodata :
    {
        _rodata_begin = .;
        *(.rdata)  *(.rodata) 
        _rodata_end = .;
        . = ALIGN(4096);
    }

    /* >> kernel data segment*/
    /* Read-write data (initialized) */
    /* data = Contains initialized global variables which are not constants */
    .data :  
    { 
        _data_begin = .; 
        *(.data)
        _data_end = .; 
        . = ALIGN(4096);
    }


    /* >> kernel bss segment, contains all the static uninitalized data */  
    /* Read-write data (uninitialized) and stack */
    /*COMMON ?? Contains the un-initialized global variables (not static). ??*/
    .bss : 
    { 
        _bss_begin = .; 
        *(COMMON)  *(.bss)
        _bss_end = .; 
        . = ALIGN(4096);
    }


    /* EOF - Fim do kernel */
    _kernel_end = .; 
}

