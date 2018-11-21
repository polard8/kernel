
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
 .text          0x004014c0     0x13f0 stdio.o
                0x00401d66                putchar
                0x004014c0                stdio_fntos
                0x00401d22                sprintf
                0x00402494                feof
                0x004025ba                stdioSetCursor
                0x004023f6                ungetc
                0x00401820                puts
                0x00402572                fputc
                0x00402610                stdioGetCursorY
                0x004026f1                scanf
                0x0040230c                fputs
                0x004024d2                ferror
                0x00401f48                input
                0x0040175e                scroll
                0x00402381                gets
                0x00401d92                outbyte
                0x00402228                fflush
                0x00402297                fprintf
                0x004020b0                stdio_system_call
                0x00401625                fopen
                0x004025e4                stdioGetCursorX
                0x004020d8                getchar
                0x0040263c                stdio_atoi
                0x00402104                stdioInitialize
                0x00402433                fgetc
                0x004015bf                fclose
                0x004024f8                fseek
                0x00401f15                _outbyte
                0x00401d07                printf
 .text          0x004028b0      0xb40 stdlib.o
                0x00402ba6                FreeHeap
                0x004028d8                rtGetHeapStart
                0x00402e47                free
                0x004028b0                stdlib_system_call
                0x00402ddc                rand
                0x00402d53                stdlibInitMM
                0x00402bb0                heapInit
                0x004032e1                __findenv
                0x004028ec                rtGetHeapPointer
                0x004028f6                rtGetAvailableHeap
                0x00402df9                srand
                0x00402db3                libcInitRT
                0x00402900                heapSetLibcHeap
                0x004033ac                getenv
                0x00402e06                malloc
                0x00402b93                AllocateHeapEx
                0x004029a7                AllocateHeap
                0x00403258                stdlib_strncmp
                0x004032b6                exit
                0x004028e2                rtGetHeapEnd
                0x00402e4c                system
 .text          0x004033f0      0x430 string.o
                0x004035dc                strcspn
                0x0040353f                strcat
                0x004033f0                strcmp
                0x00403596                bzero
                0x0040371c                strtok_r
                0x004034d2                memcpy
                0x004034a9                memoryZeroMemory
                0x0040356f                bcopy
                0x0040350f                strcpy
                0x0040367c                strspn
                0x004037f1                strtok
                0x0040344b                strncmp
                0x004035b1                strlen
 .text          0x00403820       0x70 time.o
                0x0040385a                time_system_call
                0x00403820                time
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403890      0x770 00

.rdata          0x00404000      0x7c0
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0xd0 stdio.o
 .rdata         0x00404530      0x290 main.o

.data           0x004047c0      0x840
                0x004047c0                data = .
                0x004047c0                _data = .
                0x004047c0                __data = .
 *(.data)
 .data          0x004047c0        0x0 main.o
 .data          0x004047c0      0x120 ctype.o
                0x004047c0                _ctype_
 .data          0x004048e0        0x0 stdio.o
 .data          0x004048e0        0x0 stdlib.o
 .data          0x004048e0        0x0 string.o
 .data          0x004048e0        0x0 time.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x004048e0      0x720 00

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
