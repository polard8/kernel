
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
 .text          0x00401160     0x13f0 stdio.o
                0x00401a06                putchar
                0x00401160                stdio_fntos
                0x004019c2                sprintf
                0x00402134                feof
                0x0040225a                stdioSetCursor
                0x00402096                ungetc
                0x004014c0                puts
                0x00402212                fputc
                0x004022b0                stdioGetCursorY
                0x00402391                scanf
                0x00401fac                fputs
                0x00402172                ferror
                0x00401be8                input
                0x004013fe                scroll
                0x00402021                gets
                0x00401a32                outbyte
                0x00401ec8                fflush
                0x00401f37                fprintf
                0x00401d50                stdio_system_call
                0x004012c5                fopen
                0x00402284                stdioGetCursorX
                0x00401d78                getchar
                0x004022dc                stdio_atoi
                0x00401da4                stdioInitialize
                0x004020d3                fgetc
                0x0040125f                fclose
                0x00402198                fseek
                0x00401bb5                _outbyte
                0x004019a7                printf
 .text          0x00402550      0x430 string.o
                0x0040273c                strcspn
                0x0040269f                strcat
                0x00402550                strcmp
                0x004026f6                bzero
                0x0040287c                strtok_r
                0x00402632                memcpy
                0x00402609                memoryZeroMemory
                0x004026cf                bcopy
                0x0040266f                strcpy
                0x004027dc                strspn
                0x00402951                strtok
                0x004025ab                strncmp
                0x00402711                strlen
 .text          0x00402980       0xe0 ctype.o
                0x00402a1a                isspace
                0x00402a40                isxdigit
                0x00402a2d                isupper
                0x00402993                isalpha
                0x004029df                islower
                0x00402980                isalnum
                0x004029f2                isprint
                0x004029cc                isgraph
                0x004029b9                isdigit
                0x004029a6                iscntrl
                0x00402a07                ispunct
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x00402a60      0x5a0 00

.rdata          0x00403000      0x140
 .rdata         0x00403000       0xd0 stdio.o
 .rdata         0x004030d0       0x70 main.o

.data           0x00403140      0xec0
                0x00403140                data = .
                0x00403140                _data = .
                0x00403140                __data = .
 *(.data)
 .data          0x00403140        0x0 main.o
 .data          0x00403140        0x0 stdio.o
 .data          0x00403140        0x0 string.o
 .data          0x00403140      0x120 ctype.o
                0x00403140                _ctype_
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403260      0xda0 00

.bss            0x00404000     0x1d40
                0x00404000                bss = .
                0x00404000                _bss = .
                0x00404000                __bss = .
 *(.bss)
 .bss           0x00404000        0x0 main.o
 .bss           0x00404000       0x10 stdio.o
 .bss           0x00404010       0x10 string.o
 .bss           0x00404020        0x0 ctype.o
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
LOAD ctype.o
OUTPUT(LONGEST1.BIN pe-i386)
