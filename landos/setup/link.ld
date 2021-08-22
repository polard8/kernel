/*
 * File: link.ld
 * 
 *    This file is used by ld.
 *    It's a common file for all the apps in this folder.
 *
 *    2018 - Created by Fred Nora.
 */


OUTPUT_FORMAT("elf32-i386")
ENTRY(__user_app__)

/* 0x00400000 = image base */
/* 0x00401000 = The entry point */

SECTIONS
{
    .text 0x00401000: 
    {
        code = .; 
        _code = .; 
        __code = .;
        *(.head_x86)  *(.text)
       . = ALIGN(4096);
    }

    /* .rodata  ?? */

    .data :
    {
        data = .; 
        _data = .; 
        __data = .;
        *(.data)
        . = ALIGN(4096);
    }


    .bss :
    {
        bss = .; 
        _bss = .; 
        __bss = .;
        *(.bss)
        . = ALIGN(4096);
    }


    end = .; 
    _end = .; 
    __end = .;
}



