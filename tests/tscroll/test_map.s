
Allocating common symbols
Common symbol       size              file

prompt              0x100             main.o
_io_table           0x50              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
prompt_max          0x10              main.o
prompt_err          0x100             main.o
g_columns           0x10              main.o
stdout              0x10              main.o
g_rows              0x10              main.o
prompt_out          0x100             main.o
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
 .text          0x00401000       0x70 main.o
                0x00401000                _tMain
 .text          0x00401070      0xbf0 stdio.o
                0x0040182f                putchar
                0x004017eb                sprintf
                0x00401a1b                input
                0x004010d5                scroll
                0x00401a11                printf_main
                0x0040185b                outbyte
                0x0040127f                app_print
                0x00401afd                stdio_system_call
                0x00401087                fopen
                0x00401b25                stdioInitialize
                0x00401070                fclose
                0x004019de                _outbyte
                0x004017d0                printf
                0x00401213                app_clear
                0x00402000                . = ALIGN (0x1000)
 *fill*         0x00401c60      0x3a0 00

.rdata          0x00402000       0x70
 .rdata         0x00402000       0x40 stdio.o
 .rdata         0x00402040       0x30 main.o

.data           0x00402070      0xf90
                0x00402070                data = .
                0x00402070                _data = .
                0x00402070                __data = .
 *(.data)
 .data          0x00402070        0x0 main.o
 .data          0x00402070        0x0 stdio.o
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x00402070      0xf90 00

.bss            0x00403000     0x1410
                0x00403000                bss = .
                0x00403000                _bss = .
                0x00403000                __bss = .
 *(.bss)
 .bss           0x00403000        0x0 main.o
 .bss           0x00403000       0x10 stdio.o
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403010      0xff0 00
 COMMON         0x00404000      0x410 main.o
                0x00404000                prompt
                0x00404100                _io_table
                0x00404150                stderr
                0x00404160                prompt_pos
                0x00404170                g_using_gui
                0x00404180                stdin
                0x00404190                prompt_max
                0x004041a0                prompt_err
                0x004042a0                g_columns
                0x004042b0                stdout
                0x004042c0                g_rows
                0x004042d0                prompt_out
                0x004043d0                g_cursor_y
                0x004043e0                prompt_status
                0x004043f0                g_char_attrib
                0x00404400                g_cursor_x
                0x00404410                end = .
                0x00404410                _end = .
                0x00404410                __end = .
LOAD main.o
LOAD stdio.o
OUTPUT(TSCROLL.BIN pe-i386)
