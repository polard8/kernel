
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
prompt_max          0x10              main.o
prompt_err          0x400             main.o
g_columns           0x10              main.o
stdout              0x10              main.o
Streams             0x80              main.o
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

.text           0x00401000     0x2000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x160 main.o
                0x0040112b                copy
                0x0040109e                getlinelength
                0x00401000                app_test
 .text          0x00401160     0x10e0 stdio.o
                0x00401aa9                putchar
                0x00401160                stdio_fntos
                0x00401a65                sprintf
                0x00402106                feof
                0x004021e6                fputc
                0x00401fe9                fputs
                0x00402144                ferror
                0x00401c95                input
                0x0040134f                scroll
                0x00401c8b                printf_main
                0x0040205e                gets
                0x00401ad5                outbyte
                0x004014f9                app_print
                0x00401f04                fflush
                0x00401f74                fprintf
                0x00401d8c                stdio_system_call
                0x004012b5                fopen
                0x00401db4                getchar
                0x00401de0                stdioInitialize
                0x004020d3                fgetc
                0x0040124f                fclose
                0x0040216c                fseek
                0x00401c58                _outbyte
                0x00401a4a                printf
                0x0040148d                app_clear
 .text          0x00402240      0x4a0 string.o
                0x004024a7                strcspn
                0x0040240a                strcat
                0x00402240                strcmp
                0x00402461                bzero
                0x004025e7                strtok_r
                0x0040239d                memcpy
                0x00402374                memoryZeroMemory
                0x0040243a                bcopy
                0x004023da                strcpy
                0x00402547                strspn
                0x004026bc                strtok
                0x004022f9                str_cmp
                0x0040229b                strncmp
                0x0040247c                strlen
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x004026e0      0x920 00

.rdata          0x00403000       0xb0
 .rdata         0x00403000       0x40 stdio.o
 .rdata         0x00403040       0x70 main.o

.data           0x004030b0      0xf50
                0x004030b0                data = .
                0x004030b0                _data = .
                0x004030b0                __data = .
 *(.data)
 .data          0x004030b0        0x0 main.o
 .data          0x004030b0        0x0 stdio.o
 .data          0x004030b0        0x0 string.o
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x004030b0      0xf50 00

.bss            0x00404000     0x1d40
                0x00404000                bss = .
                0x00404000                _bss = .
                0x00404000                __bss = .
 *(.bss)
 .bss           0x00404000        0x0 main.o
 .bss           0x00404000       0x10 stdio.o
 .bss           0x00404010       0x10 string.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404020      0xfe0 00
 COMMON         0x00405000      0xd40 main.o
                0x00405000                prompt
                0x00405400                stderr
                0x00405410                prompt_pos
                0x00405420                g_using_gui
                0x00405430                stdin
                0x00405440                prompt_max
                0x00405450                prompt_err
                0x00405850                g_columns
                0x00405860                stdout
                0x00405870                Streams
                0x004058f0                g_rows
                0x00405900                prompt_out
                0x00405d00                g_cursor_y
                0x00405d10                prompt_status
                0x00405d20                g_char_attrib
                0x00405d30                g_cursor_x
                0x00405d40                end = .
                0x00405d40                _end = .
                0x00405d40                __end = .
LOAD main.o
LOAD stdio.o
LOAD string.o
OUTPUT(LONGEST1.BIN pe-i386)
