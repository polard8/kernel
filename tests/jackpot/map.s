
Allocating common symbols
Common symbol       size              file

j                   0x10              main.o
prompt              0x400             main.o
number              0x10              main.o
i                   0x10              main.o
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
maxrand             0x10              main.o
g_columns           0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
c                   0x10              main.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
life                0x10              main.o
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

.text           0x00401000     0x3000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x3b0 main.o
                0x00401171                GetResults
                0x0040135b                jackpot_main
                0x00401000                app_main
                0x004012a6                jackpot_atoi
                0x0040104b                Start
 .text          0x004013b0       0xe0 ctype.o
                0x0040144a                isspace
                0x00401470                isxdigit
                0x0040145d                isupper
                0x004013c3                isalpha
                0x0040140f                islower
                0x004013b0                isalnum
                0x00401422                isprint
                0x004013fc                isgraph
                0x004013e9                isdigit
                0x004013d6                iscntrl
                0x00401437                ispunct
 .text          0x00401490     0x1360 stdio.o
                0x00401ca6                putchar
                0x00401490                stdio_fntos
                0x00401c62                sprintf
                0x004023d4                feof
                0x004024fa                stdioSetCursor
                0x00402336                ungetc
                0x00401760                puts
                0x004024b2                fputc
                0x00402550                stdioGetCursorY
                0x00402631                scanf
                0x0040224c                fputs
                0x00402412                ferror
                0x00401e88                input
                0x0040169e                scroll
                0x004022c1                gets
                0x00401cd2                outbyte
                0x00402168                fflush
                0x004021d7                fprintf
                0x00401ff0                stdio_system_call
                0x004015e5                fopen
                0x00402524                stdioGetCursorX
                0x00402018                getchar
                0x0040257c                stdio_atoi
                0x00402044                stdioInitialize
                0x00402373                fgetc
                0x0040157f                fclose
                0x00402438                fseek
                0x00401e55                _outbyte
                0x00401c47                printf
 .text          0x004027f0      0xaf0 stdlib.o
                0x00402ae6                FreeHeap
                0x00402818                rtGetHeapStart
                0x00402d3a                free
                0x004027f0                stdlib_system_call
                0x00402ccf                rand
                0x00402c46                stdlibInitMM
                0x00402af0                heapInit
                0x004031d4                __findenv
                0x0040282c                rtGetHeapPointer
                0x00402836                rtGetAvailableHeap
                0x00402cec                srand
                0x00402ca6                libcInitRT
                0x00402840                heapSetLibcHeap
                0x0040329f                getenv
                0x00402cf9                malloc
                0x00402ad3                AllocateHeapEx
                0x004028e7                AllocateHeap
                0x0040314b                stdlib_strncmp
                0x004031a9                exit
                0x00402822                rtGetHeapEnd
                0x00402d3f                system
 .text          0x004032e0      0x430 string.o
                0x004034cc                strcspn
                0x0040342f                strcat
                0x004032e0                strcmp
                0x00403486                bzero
                0x0040360c                strtok_r
                0x004033c2                memcpy
                0x00403399                memoryZeroMemory
                0x0040345f                bcopy
                0x004033ff                strcpy
                0x0040356c                strspn
                0x004036e1                strtok
                0x0040333b                strncmp
                0x004034a1                strlen
 .text          0x00403710       0x70 time.o
                0x0040374a                time_system_call
                0x00403710                time
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403780      0x880 00

.rdata          0x00404000      0x760
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0x70 stdio.o
 .rdata         0x004044d0      0x290 main.o

.data           0x00404760      0x8a0
                0x00404760                data = .
                0x00404760                _data = .
                0x00404760                __data = .
 *(.data)
 .data          0x00404760        0x0 main.o
 .data          0x00404760      0x120 ctype.o
                0x00404760                _ctype_
 .data          0x00404880        0x0 stdio.o
 .data          0x00404880        0x0 stdlib.o
 .data          0x00404880        0x0 string.o
 .data          0x00404880        0x0 time.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404880      0x780 00

.bss            0x00405000     0xa6a0
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
 .bss           0x00405000        0x0 ctype.o
 .bss           0x00405000       0x10 stdio.o
 .bss           0x00405010     0x8010 stdlib.o
                0x00405010                environ
 .bss           0x0040d020       0x10 string.o
 .bss           0x0040d030        0x0 time.o
                0x0040e000                . = ALIGN (0x1000)
 *fill*         0x0040d030      0xfd0 00
 COMMON         0x0040e000      0xda0 main.o
                0x0040e000                j
                0x0040e010                prompt
                0x0040e410                number
                0x0040e420                i
                0x0040e430                stderr
                0x0040e440                prompt_pos
                0x0040e450                g_using_gui
                0x0040e460                stdin
                0x0040e470                prompt_max
                0x0040e480                prompt_err
                0x0040e880                maxrand
                0x0040e890                g_columns
                0x0040e8a0                stdout
                0x0040e8b0                Streams
                0x0040e930                g_rows
                0x0040e940                prompt_out
                0x0040ed40                c
                0x0040ed50                g_cursor_y
                0x0040ed60                life
                0x0040ed70                prompt_status
                0x0040ed80                g_char_attrib
                0x0040ed90                g_cursor_x
 COMMON         0x0040eda0      0x900 stdlib.o
                0x0040eda0                current_mmblock
                0x0040edb0                mm_prev_pointer
                0x0040edc0                heap_end
                0x0040edd0                g_available_heap
                0x0040ede0                heap_start
                0x0040edf0                heapCount
                0x0040ee00                HEAP_START
                0x0040ee10                g_heap_pointer
                0x0040ee20                heapList
                0x0040f220                randseed
                0x0040f230                HEAP_SIZE
                0x0040f240                last_size
                0x0040f250                last_valid
                0x0040f260                mmblockList
                0x0040f660                libcHeap
                0x0040f670                Heap
                0x0040f680                mmblockCount
                0x0040f690                HEAP_END
                0x0040f6a0                end = .
                0x0040f6a0                _end = .
                0x0040f6a0                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
OUTPUT(JACKPOT.BIN pe-i386)
