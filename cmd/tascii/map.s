
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
g_columns           0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
g_cursor_x          0x10              main.o
HEAP_END            0x10              stdlib.o

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

.text           0x00401000     0x4000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000       0xb0 main.o
                0x00401000                _main
 .text          0x004010b0        0x0 ctype.o
 .text          0x004010b0     0x2a10 stdio.o
                0x00401abd                printf_i2hex
                0x00401cef                putchar
                0x00401165                stdio_fntos
                0x00401cab                sprintf
                0x00402568                feof
                0x00401b2b                printf2
                0x0040268e                stdioSetCursor
                0x0040247d                ungetc
                0x00403a84                rewind
                0x004014ce                puts
                0x00402646                fputc
                0x004026e4                stdioGetCursorY
                0x00402710                scanf
                0x0040237b                fputs
                0x004025a6                ferror
                0x00401ed1                input
                0x0040140c                scroll
                0x004023f0                gets
                0x00401d1b                outbyte
                0x004024e4                fileno
                0x00402274                fflush
                0x00402306                fprintf
                0x00403a42                stderr_printf
                0x00402039                stdio_system_call
                0x004012ca                fopen
                0x004026b8                stdioGetCursorX
                0x00402061                getchar
                0x004019d0                printf_atoi
                0x004010b0                stdio_atoi
                0x004029c0                kvprintf
                0x00403a13                stdout_printf
                0x0040208d                stdioInitialize
                0x00402507                fgetc
                0x00401264                fclose
                0x004025cc                fseek
                0x00403a71                perror
                0x00401e9e                _outbyte
                0x004024ba                ftell
                0x0040394f                printf
                0x004019b5                printf3
                0x00403987                vfprintf
 .text          0x00403ac0      0xc60 stdlib.o
                0x00403db6                FreeHeap
                0x00403ae8                rtGetHeapStart
                0x004040c3                free
                0x00403ac0                stdlib_system_call
                0x00403fec                rand
                0x00403f63                stdlibInitMM
                0x00403dc0                heapInit
                0x0040455d                __findenv
                0x00403afc                rtGetHeapPointer
                0x00403b06                rtGetAvailableHeap
                0x00404009                srand
                0x0040465d                atoi
                0x00403fc3                libcInitRT
                0x00403b10                heapSetLibcHeap
                0x00404041                stdlib_die
                0x00404628                getenv
                0x00404082                malloc
                0x00403da3                AllocateHeapEx
                0x00403bb7                AllocateHeap
                0x004044d4                stdlib_strncmp
                0x00404016                xmalloc
                0x00404532                exit
                0x00403af2                rtGetHeapEnd
                0x004040c8                system
 .text          0x00404720      0x430 string.o
                0x0040490c                strcspn
                0x0040486f                strcat
                0x00404720                strcmp
                0x004048c6                bzero
                0x00404a4c                strtok_r
                0x00404802                memcpy
                0x004047d9                memoryZeroMemory
                0x0040489f                bcopy
                0x0040483f                strcpy
                0x004049ac                strspn
                0x00404b21                strtok
                0x0040477b                strncmp
                0x004048e1                strlen
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404b50      0x4b0 00

.rdata          0x00405000      0x940
 .rdata         0x00405000      0x480 stdlib.o
 .rdata         0x00405480      0x380 stdio.o
                0x00405660                hex2ascii_data
 .rdata         0x00405800      0x100 ctype.o
                0x00405800                _ctype
 .rdata         0x00405900       0x40 main.o

.data           0x00405940      0x6c0
                0x00405940                data = .
                0x00405940                _data = .
                0x00405940                __data = .
 *(.data)
 .data          0x00405940        0x0 main.o
 .data          0x00405940        0x0 ctype.o
 .data          0x00405940        0x0 stdio.o
 .data          0x00405940        0x0 stdlib.o
 .data          0x00405940        0x0 string.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405940      0x6c0 00

.bss            0x00406000     0xa640
                0x00406000                bss = .
                0x00406000                _bss = .
                0x00406000                __bss = .
 *(.bss)
 .bss           0x00406000        0x0 main.o
 .bss           0x00406000        0x0 ctype.o
 .bss           0x00406000       0x10 stdio.o
 .bss           0x00406010     0x8010 stdlib.o
                0x00406010                environ
 .bss           0x0040e020       0x10 string.o
                0x0040f000                . = ALIGN (0x1000)
 *fill*         0x0040e030      0xfd0 00
 COMMON         0x0040f000      0xd40 main.o
                0x0040f000                prompt
                0x0040f400                stderr
                0x0040f410                prompt_pos
                0x0040f420                g_using_gui
                0x0040f430                stdin
                0x0040f440                prompt_max
                0x0040f450                prompt_err
                0x0040f850                g_columns
                0x0040f860                stdout
                0x0040f870                Streams
                0x0040f8f0                g_rows
                0x0040f900                prompt_out
                0x0040fd00                g_cursor_y
                0x0040fd10                prompt_status
                0x0040fd20                g_char_attrib
                0x0040fd30                g_cursor_x
 COMMON         0x0040fd40      0x900 stdlib.o
                0x0040fd40                current_mmblock
                0x0040fd50                mm_prev_pointer
                0x0040fd60                heap_end
                0x0040fd70                g_available_heap
                0x0040fd80                heap_start
                0x0040fd90                heapCount
                0x0040fda0                HEAP_START
                0x0040fdb0                g_heap_pointer
                0x0040fdc0                heapList
                0x004101c0                randseed
                0x004101d0                HEAP_SIZE
                0x004101e0                last_size
                0x004101f0                last_valid
                0x00410200                mmblockList
                0x00410600                libcHeap
                0x00410610                Heap
                0x00410620                mmblockCount
                0x00410630                HEAP_END
                0x00410640                end = .
                0x00410640                _end = .
                0x00410640                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(TASCII.BIN pe-i386)
