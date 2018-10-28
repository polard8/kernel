
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
 .text          0x00401000      0x3e0 main.o
                0x0040119b                GetResults
                0x00401391                jackpot_main
                0x00401000                app_main
                0x004012dc                jackpot_atoi
                0x00401075                Start
 .text          0x004013e0       0xe0 ctype.o
                0x0040147a                isspace
                0x004014a0                isxdigit
                0x0040148d                isupper
                0x004013f3                isalpha
                0x0040143f                islower
                0x004013e0                isalnum
                0x00401452                isprint
                0x0040142c                isgraph
                0x00401419                isdigit
                0x00401406                iscntrl
                0x00401467                ispunct
 .text          0x004014c0     0x1360 stdio.o
                0x00401cd6                putchar
                0x004014c0                stdio_fntos
                0x00401c92                sprintf
                0x00402404                feof
                0x0040252a                stdioSetCursor
                0x00402366                ungetc
                0x00401790                puts
                0x004024e2                fputc
                0x00402580                stdioGetCursorY
                0x00402661                scanf
                0x0040227c                fputs
                0x00402442                ferror
                0x00401eb8                input
                0x004016ce                scroll
                0x004022f1                gets
                0x00401d02                outbyte
                0x00402198                fflush
                0x00402207                fprintf
                0x00402020                stdio_system_call
                0x00401615                fopen
                0x00402554                stdioGetCursorX
                0x00402048                getchar
                0x004025ac                stdio_atoi
                0x00402074                stdioInitialize
                0x004023a3                fgetc
                0x004015af                fclose
                0x00402468                fseek
                0x00401e85                _outbyte
                0x00401c77                printf
 .text          0x00402820      0xaf0 stdlib.o
                0x00402b16                FreeHeap
                0x00402848                rtGetHeapStart
                0x00402d6a                free
                0x00402820                stdlib_system_call
                0x00402cff                rand
                0x00402c76                stdlibInitMM
                0x00402b20                heapInit
                0x00403204                __findenv
                0x0040285c                rtGetHeapPointer
                0x00402866                rtGetAvailableHeap
                0x00402d1c                srand
                0x00402cd6                libcInitRT
                0x00402870                heapSetLibcHeap
                0x004032cf                getenv
                0x00402d29                malloc
                0x00402b03                AllocateHeapEx
                0x00402917                AllocateHeap
                0x0040317b                stdlib_strncmp
                0x004031d9                exit
                0x00402852                rtGetHeapEnd
                0x00402d6f                system
 .text          0x00403310      0x430 string.o
                0x004034fc                strcspn
                0x0040345f                strcat
                0x00403310                strcmp
                0x004034b6                bzero
                0x0040363c                strtok_r
                0x004033f2                memcpy
                0x004033c9                memoryZeroMemory
                0x0040348f                bcopy
                0x0040342f                strcpy
                0x0040359c                strspn
                0x00403711                strtok
                0x0040336b                strncmp
                0x004034d1                strlen
 .text          0x00403740       0x70 time.o
                0x0040377a                time_system_call
                0x00403740                time
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x004037b0      0x850 00

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
