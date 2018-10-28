
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
 .text          0x00401000      0x140 main.o
                0x00401000                app_test
 .text          0x00401140     0x1360 stdio.o
                0x00401956                putchar
                0x00401140                stdio_fntos
                0x00401912                sprintf
                0x00402084                feof
                0x004021aa                stdioSetCursor
                0x00401fe6                ungetc
                0x00401410                puts
                0x00402162                fputc
                0x00402200                stdioGetCursorY
                0x004022e1                scanf
                0x00401efc                fputs
                0x004020c2                ferror
                0x00401b38                input
                0x0040134e                scroll
                0x00401f71                gets
                0x00401982                outbyte
                0x00401e18                fflush
                0x00401e87                fprintf
                0x00401ca0                stdio_system_call
                0x00401295                fopen
                0x004021d4                stdioGetCursorX
                0x00401cc8                getchar
                0x0040222c                stdio_atoi
                0x00401cf4                stdioInitialize
                0x00402023                fgetc
                0x0040122f                fclose
                0x004020e8                fseek
                0x00401b05                _outbyte
                0x004018f7                printf
 .text          0x004024a0       0xe0 ctype.o
                0x0040253a                isspace
                0x00402560                isxdigit
                0x0040254d                isupper
                0x004024b3                isalpha
                0x004024ff                islower
                0x004024a0                isalnum
                0x00402512                isprint
                0x004024ec                isgraph
                0x004024d9                isdigit
                0x004024c6                iscntrl
                0x00402527                ispunct
 .text          0x00402580      0x430 string.o
                0x0040276c                strcspn
                0x004026cf                strcat
                0x00402580                strcmp
                0x00402726                bzero
                0x004028ac                strtok_r
                0x00402662                memcpy
                0x00402639                memoryZeroMemory
                0x004026ff                bcopy
                0x0040269f                strcpy
                0x0040280c                strspn
                0x00402981                strtok
                0x004025db                strncmp
                0x00402741                strlen
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x004029b0      0x650 00

.rdata          0x00403000      0x130
 .rdata         0x00403000       0x70 stdio.o
 .rdata         0x00403070       0xc0 main.o

.data           0x00403130      0xed0
                0x00403130                data = .
                0x00403130                _data = .
                0x00403130                __data = .
 *(.data)
 .data          0x00403130        0x0 main.o
 .data          0x00403130        0x0 stdio.o
 .data          0x00403130      0x120 ctype.o
                0x00403130                _ctype_
 .data          0x00403250        0x0 string.o
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403250      0xdb0 00

.bss            0x00404000     0x1d40
                0x00404000                bss = .
                0x00404000                _bss = .
                0x00404000                __bss = .
 *(.bss)
 .bss           0x00404000        0x0 main.o
 .bss           0x00404000       0x10 stdio.o
 .bss           0x00404010        0x0 ctype.o
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
LOAD ctype.o
LOAD string.o
OUTPUT(OPER1.BIN pe-i386)
