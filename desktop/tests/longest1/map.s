
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

.text           0x00401000     0x3000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x160 main.o
                0x0040112b                copy
                0x0040109e                getlinelength
                0x00401000                app_test
 .text          0x00401160     0x2770 stdio.o
                0x00401b64                printf_i2hex
                0x00401d96                putchar
                0x00401215                stdio_fntos
                0x00401d52                sprintf
                0x004024c4                feof
                0x00401bd2                printf2
                0x004025ea                stdioSetCursor
                0x00402426                ungetc
                0x00401575                puts
                0x004025a2                fputc
                0x00402640                stdioGetCursorY
                0x0040266c                scanf
                0x0040233c                fputs
                0x00402502                ferror
                0x00401f78                input
                0x004014b3                scroll
                0x004023b1                gets
                0x00401dc2                outbyte
                0x00402258                fflush
                0x004022c7                fprintf
                0x004020e0                stdio_system_call
                0x0040137a                fopen
                0x00402614                stdioGetCursorX
                0x00402108                getchar
                0x00401a77                printf_atoi
                0x00401160                stdio_atoi
                0x00402902                kvprintf
                0x00402134                stdioInitialize
                0x00402463                fgetc
                0x00401314                fclose
                0x00402528                fseek
                0x00401f45                _outbyte
                0x00403891                printf
                0x00401a5c                printf3
 .text          0x004038d0      0x430 string.o
                0x00403abc                strcspn
                0x00403a1f                strcat
                0x004038d0                strcmp
                0x00403a76                bzero
                0x00403bfc                strtok_r
                0x004039b2                memcpy
                0x00403989                memoryZeroMemory
                0x00403a4f                bcopy
                0x004039ef                strcpy
                0x00403b5c                strspn
                0x00403cd1                strtok
                0x0040392b                strncmp
                0x00403a91                strlen
 .text          0x00403d00       0xe0 ctype.o
                0x00403d9a                isspace
                0x00403dc0                isxdigit
                0x00403dad                isupper
                0x00403d13                isalpha
                0x00403d5f                islower
                0x00403d00                isalnum
                0x00403d72                isprint
                0x00403d4c                isgraph
                0x00403d39                isdigit
                0x00403d26                iscntrl
                0x00403d87                ispunct
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403de0      0x220 00

.rdata          0x00404000      0x3b0
 .rdata         0x00404000      0x340 stdio.o
                0x004041a0                hex2ascii_data
 .rdata         0x00404340       0x70 main.o

.data           0x004043b0      0xc50
                0x004043b0                data = .
                0x004043b0                _data = .
                0x004043b0                __data = .
 *(.data)
 .data          0x004043b0        0x0 main.o
 .data          0x004043b0        0x0 stdio.o
 .data          0x004043b0        0x0 string.o
 .data          0x004043b0      0x120 ctype.o
                0x004043b0                _ctype_
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x004044d0      0xb30 00

.bss            0x00405000     0x1d40
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
 .bss           0x00405000       0x10 stdio.o
 .bss           0x00405010       0x10 string.o
 .bss           0x00405020        0x0 ctype.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405020      0xfe0 00
 COMMON         0x00406000      0xd40 main.o
                0x00406000                prompt
                0x00406400                stderr
                0x00406410                prompt_pos
                0x00406420                g_using_gui
                0x00406430                stdin
                0x00406440                prompt_max
                0x00406450                prompt_err
                0x00406850                g_columns
                0x00406860                stdout
                0x00406870                Streams
                0x004068f0                g_rows
                0x00406900                prompt_out
                0x00406d00                g_cursor_y
                0x00406d10                prompt_status
                0x00406d20                g_char_attrib
                0x00406d30                g_cursor_x
                0x00406d40                end = .
                0x00406d40                _end = .
                0x00406d40                __end = .
LOAD main.o
LOAD stdio.o
LOAD string.o
LOAD ctype.o
OUTPUT(LONGEST1.BIN pe-i386)
