
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
_io_table           0x50              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
prompt_max          0x10              main.o
prompt_err          0x400             main.o
g_columns           0x10              main.o
stdout              0x10              main.o
g_rows              0x10              main.o
prompt_out          0x400             main.o
g_cursor_y          0x10              main.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
g_cursor_x          0x10              main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x00000000         0xffffffff

Linker script and memory map

                0x00400000                __image_base__ = 0x400000
                0x00000000                __dll__ = 0x0
                0x00400000                ___ImageBase = 0x400000
                0x00001000                __section_alignment__ = 0x1000
                0x00000200                __file_alignment__ = 0x200
                0x00000004                __major_os_version__ = 0x4
                0x00000000                __minor_os_version__ = 0x0
                0x00000001                __major_image_version__ = 0x1
                0x00000000                __minor_image_version__ = 0x0
                0x00000004                __major_subsystem_version__ = 0x4
                0x00000000                __minor_subsystem_version__ = 0x0
                0x00000003                __subsystem__ = 0x3
                0x00200000                __size_of_stack_reserve__ = 0x200000
                0x00001000                __size_of_stack_commit__ = 0x1000
                0x00100000                __size_of_heap_reserve__ = 0x100000
                0x00001000                __size_of_heap_commit__ = 0x1000
                0x00000000                __loader_flags__ = 0x0

.text           0x00401000     0x1000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x140 main.o
                0x00401000                app_test
 .text          0x00401140      0xc20 stdio.o
                0x004018ff                putchar
                0x004018bb                sprintf
                0x00401aeb                input
                0x004011a5                scroll
                0x00401ae1                printf_main
                0x0040192b                outbyte
                0x0040134f                app_print
                0x00401be2                stdio_system_call
                0x00401157                fopen
                0x00401c0a                getchar
                0x00401c36                stdioInitialize
                0x00401140                fclose
                0x00401aae                _outbyte
                0x004018a0                printf
                0x004012e3                app_clear
                0x00402000                . = ALIGN (0x1000)
 *fill*         0x00401d60      0x2a0 00

.rdata          0x00402000       0xf0
 .rdata         0x00402000       0x30 stdio.o
 .rdata         0x00402030       0xc0 main.o

.data           0x004020f0      0xf10
                0x004020f0                data = .
                0x004020f0                _data = .
                0x004020f0                __data = .
 *(.data)
 .data          0x004020f0        0x0 main.o
 .data          0x004020f0        0x0 stdio.o
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x004020f0      0xf10 00

.bss            0x00403000     0x1d10
                0x00403000                bss = .
                0x00403000                _bss = .
                0x00403000                __bss = .
 *(.bss)
 .bss           0x00403000        0x0 main.o
 .bss           0x00403000       0x10 stdio.o
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403010      0xff0 00
 COMMON         0x00404000      0xd10 main.o
                0x00404000                prompt
                0x00404400                _io_table
                0x00404450                stderr
                0x00404460                prompt_pos
                0x00404470                g_using_gui
                0x00404480                stdin
                0x00404490                prompt_max
                0x004044a0                prompt_err
                0x004048a0                g_columns
                0x004048b0                stdout
                0x004048c0                g_rows
                0x004048d0                prompt_out
                0x00404cd0                g_cursor_y
                0x00404ce0                prompt_status
                0x00404cf0                g_char_attrib
                0x00404d00                g_cursor_x
                0x00404d10                end = .
                0x00404d10                _end = .
                0x00404d10                __end = .
LOAD main.o
LOAD stdio.o
OUTPUT(OPER1.BIN pe-i386)
