
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
 .text          0x00401140     0x2770 stdio.o
                0x00401b44                printf_i2hex
                0x00401d76                putchar
                0x004011f5                stdio_fntos
                0x00401d32                sprintf
                0x004024a4                feof
                0x00401bb2                printf2
                0x004025ca                stdioSetCursor
                0x00402406                ungetc
                0x00401555                puts
                0x00402582                fputc
                0x00402620                stdioGetCursorY
                0x0040264c                scanf
                0x0040231c                fputs
                0x004024e2                ferror
                0x00401f58                input
                0x00401493                scroll
                0x00402391                gets
                0x00401da2                outbyte
                0x00402238                fflush
                0x004022a7                fprintf
                0x004020c0                stdio_system_call
                0x0040135a                fopen
                0x004025f4                stdioGetCursorX
                0x004020e8                getchar
                0x00401a57                printf_atoi
                0x00401140                stdio_atoi
                0x004028e2                kvprintf
                0x00402114                stdioInitialize
                0x00402443                fgetc
                0x004012f4                fclose
                0x00402508                fseek
                0x00401f25                _outbyte
                0x00403871                printf
                0x00401a3c                printf3
 .text          0x004038b0       0xe0 ctype.o
                0x0040394a                isspace
                0x00403970                isxdigit
                0x0040395d                isupper
                0x004038c3                isalpha
                0x0040390f                islower
                0x004038b0                isalnum
                0x00403922                isprint
                0x004038fc                isgraph
                0x004038e9                isdigit
                0x004038d6                iscntrl
                0x00403937                ispunct
 .text          0x00403990      0x430 string.o
                0x00403b7c                strcspn
                0x00403adf                strcat
                0x00403990                strcmp
                0x00403b36                bzero
                0x00403cbc                strtok_r
                0x00403a72                memcpy
                0x00403a49                memoryZeroMemory
                0x00403b0f                bcopy
                0x00403aaf                strcpy
                0x00403c1c                strspn
                0x00403d91                strtok
                0x004039eb                strncmp
                0x00403b51                strlen
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403dc0      0x240 00

.rdata          0x00404000      0x400
 .rdata         0x00404000      0x340 stdio.o
                0x004041a0                hex2ascii_data
 .rdata         0x00404340       0xc0 main.o

.data           0x00404400      0xc00
                0x00404400                data = .
                0x00404400                _data = .
                0x00404400                __data = .
 *(.data)
 .data          0x00404400        0x0 main.o
 .data          0x00404400        0x0 stdio.o
 .data          0x00404400      0x120 ctype.o
                0x00404400                _ctype_
 .data          0x00404520        0x0 string.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404520      0xae0 00

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
