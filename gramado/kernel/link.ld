OUTPUT_FORMAT("elf32-i386")
ENTRY(_kernel_begin)       /* Kernel entry point. (head.s) */
SECTIONS
{ 
    
    /*Opção??:  _kernel_begin  = .;  */

    /* 0xc0001000 = .text = _kernel_begin =  _code_begin =  .head_x86 */

    .text 0xC0001000:      /* kernel text segment. Executable code of the program */
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

