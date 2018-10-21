
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
 .text          0x00401160     0x1360 stdio.o
                0x00401976                putchar
                0x00401160                stdio_fntos
                0x00401932                sprintf
                0x004020a4                feof
                0x004021ca                stdioSetCursor
                0x00402006                ungetc
                0x00401430                puts
                0x00402182                fputc
                0x00402220                stdioGetCursorY
                0x00402301                scanf
                0x00401f1c                fputs
                0x004020e2                ferror
                0x00401b58                input
                0x0040136e                scroll
                0x00401f91                gets
                0x004019a2                outbyte
                0x00401e38                fflush
                0x00401ea7                fprintf
                0x00401cc0                stdio_system_call
                0x004012b5                fopen
                0x004021f4                stdioGetCursorX
                0x00401ce8                getchar
                0x0040224c                stdio_atoi
                0x00401d14                stdioInitialize
                0x00402043                fgetc
                0x0040124f                fclose
                0x00402108                fseek
                0x00401b25                _outbyte
                0x00401917                printf
 .text          0x004024c0      0x430 string.o
                0x004026ac                strcspn
                0x0040260f                strcat
                0x004024c0                strcmp
                0x00402666                bzero
                0x004027ec                strtok_r
                0x004025a2                memcpy
                0x00402579                memoryZeroMemory
                0x0040263f                bcopy
                0x004025df                strcpy
                0x0040274c                strspn
                0x004028c1                strtok
                0x0040251b                strncmp
                0x00402681                strlen
 .text          0x004028f0       0xe0 ctype.o
                0x0040298a                isspace
                0x004029b0                isxdigit
                0x0040299d                isupper
                0x00402903                isalpha
                0x0040294f                islower
                0x004028f0                isalnum
                0x00402962                isprint
                0x0040293c                isgraph
                0x00402929                isdigit
                0x00402916                iscntrl
                0x00402977                ispunct
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x004029d0      0x630 00

.rdata          0x00403000       0xe0
 .rdata         0x00403000       0x70 stdio.o
 .rdata         0x00403070       0x70 main.o

.data           0x004030e0      0xf20
                0x004030e0                data = .
                0x004030e0                _data = .
                0x004030e0                __data = .
 *(.data)
 .data          0x004030e0        0x0 main.o
 .data          0x004030e0        0x0 stdio.o
 .data          0x004030e0        0x0 string.o
 .data          0x004030e0      0x120 ctype.o
                0x004030e0                _ctype_
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403200      0xe00 00

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
