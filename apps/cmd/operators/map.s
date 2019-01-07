
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
 .text          0x00401000      0x140 main.o
                0x00401000                app_test
 .text          0x00401140     0x2a10 stdio.o
                0x00401b4d                printf_i2hex
                0x00401d7f                putchar
                0x004011f5                stdio_fntos
                0x00401d3b                sprintf
                0x004025f8                feof
                0x00401bbb                printf2
                0x0040271e                stdioSetCursor
                0x0040250d                ungetc
                0x00403b14                rewind
                0x0040155e                puts
                0x004026d6                fputc
                0x00402774                stdioGetCursorY
                0x004027a0                scanf
                0x0040240b                fputs
                0x00402636                ferror
                0x00401f61                input
                0x0040149c                scroll
                0x00402480                gets
                0x00401dab                outbyte
                0x00402574                fileno
                0x00402304                fflush
                0x00402396                fprintf
                0x00403ad2                stderr_printf
                0x004020c9                stdio_system_call
                0x0040135a                fopen
                0x00402748                stdioGetCursorX
                0x004020f1                getchar
                0x00401a60                printf_atoi
                0x00401140                stdio_atoi
                0x00402a50                kvprintf
                0x00403aa3                stdout_printf
                0x0040211d                stdioInitialize
                0x00402597                fgetc
                0x004012f4                fclose
                0x0040265c                fseek
                0x00403b01                perror
                0x00401f2e                _outbyte
                0x0040254a                ftell
                0x004039df                printf
                0x00401a45                printf3
                0x00403a17                vfprintf
 .text          0x00403b50        0x0 ctype.o
 .text          0x00403b50      0x430 string.o
                0x00403d3c                strcspn
                0x00403c9f                strcat
                0x00403b50                strcmp
                0x00403cf6                bzero
                0x00403e7c                strtok_r
                0x00403c32                memcpy
                0x00403c09                memoryZeroMemory
                0x00403ccf                bcopy
                0x00403c6f                strcpy
                0x00403ddc                strspn
                0x00403f51                strtok
                0x00403bab                strncmp
                0x00403d11                strlen
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403f80       0x80 00

.rdata          0x00404000      0x540
 .rdata         0x00404000      0x100 ctype.o
                0x00404000                _ctype
 .rdata         0x00404100      0x380 stdio.o
                0x004042e0                hex2ascii_data
 .rdata         0x00404480       0xc0 main.o

.data           0x00404540      0xac0
                0x00404540                data = .
                0x00404540                _data = .
                0x00404540                __data = .
 *(.data)
 .data          0x00404540        0x0 main.o
 .data          0x00404540        0x0 stdio.o
 .data          0x00404540        0x0 ctype.o
 .data          0x00404540        0x0 string.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404540      0xac0 00

.bss            0x00405000     0x1d40
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
 .bss           0x00405000       0x10 stdio.o
 .bss           0x00405010        0x0 ctype.o
 .bss           0x00405010       0x10 string.o
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
LOAD ctype.o
LOAD string.o
OUTPUT(OPER1.BIN pe-i386)
