/*
 * File: link.ld
 *    This file is used by ld.
 *    It's a common file for all the commands in this folder.
 *    
 *    2019 - Created by Fred Nora.
 */

OUTPUT_FORMAT("elf64-x86-64")
ENTRY(main)

/* 0x00200000 = image base */
/* 0x00201000 = The entry point */

SECTIONS
{ 

    /* The entry point. It's not the base of the image. */

    . = 0x00201000;
    .text 0x00201000: 
    {
        _app_begin = .;
    
        _code_begin = .;
        *(.text)
        _code_end = .; 
    }

    . = ALIGN(4096);
    .rodata :
    {
        _rodata_begin = .;
        *(.rdata)  *(.rodata) 
        _rodata_end = .;
    }

    . = ALIGN(4096);
    .data :  
    { 
        _data_begin = .; 
        *(.data) 
        _data_end = .; 
    }

    . = ALIGN(4096);
    .bss : 
    { 
        _bss_begin = .; 
        *(COMMON)  *(.bss)
        _bss_end = .; 
    
        _app_end = .; 
    }
}



