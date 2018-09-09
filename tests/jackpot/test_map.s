
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
 .text          0x004013b0     0x1120 stdio.o
                0x00401d12                putchar
                0x004013b0                stdio_fntos
                0x00401cce                sprintf
                0x004023a3                feof
                0x004017cc                puts
                0x00402481                fputc
                0x00402258                fputs
                0x004023e1                ferror
                0x00401efe                input
                0x0040159d                scroll
                0x00401ef4                printf_main
                0x004022cd                gets
                0x00401d3e                outbyte
                0x00401747                app_print
                0x00402173                fflush
                0x004021e3                fprintf
                0x00401ff5                stdio_system_call
                0x00401505                fopen
                0x0040201d                getchar
                0x0040204f                stdioInitialize
                0x00402342                fgetc
                0x0040149f                fclose
                0x00402407                fseek
                0x00401ec1                _outbyte
                0x00401cb3                printf
                0x004016db                app_clear
 .text          0x004024d0      0xaf0 stdlib.o
                0x004027c6                FreeHeap
                0x004024f8                rtGetHeapStart
                0x00402a1a                free
                0x004024d0                stdlib_system_call
                0x004029af                rand
                0x00402926                stdlibInitMM
                0x004027d0                heapInit
                0x00402eb4                __findenv
                0x0040250c                rtGetHeapPointer
                0x00402516                rtGetAvailableHeap
                0x004029cc                srand
                0x00402986                libcInitRT
                0x00402520                heapSetLibcHeap
                0x00402f7f                getenv
                0x004029d9                malloc
                0x004027b3                AllocateHeapEx
                0x004025c7                AllocateHeap
                0x00402e2b                stdlib_strncmp
                0x00402e89                exit
                0x00402502                rtGetHeapEnd
                0x00402a1f                system
 .text          0x00402fc0      0x4a0 string.o
                0x00403227                strcspn
                0x0040318a                strcat
                0x00402fc0                strcmp
                0x004031e1                bzero
                0x00403367                strtok_r
                0x0040311d                memcpy
                0x004030f4                memoryZeroMemory
                0x004031ba                bcopy
                0x0040315a                strcpy
                0x004032c7                strspn
                0x0040343c                strtok
                0x00403079                str_cmp
                0x0040301b                strncmp
                0x004031fc                strlen
 .text          0x00403460       0x70 time.o
                0x0040349a                time_system_call
                0x00403460                time
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x004034d0      0xb30 00

.rdata          0x00404000      0x730
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0x40 stdio.o
 .rdata         0x004044a0      0x290 main.o

.data           0x00404730      0x8d0
                0x00404730                data = .
                0x00404730                _data = .
                0x00404730                __data = .
 *(.data)
 .data          0x00404730        0x0 main.o
 .data          0x00404730        0x0 stdio.o
 .data          0x00404730        0x0 stdlib.o
 .data          0x00404730        0x0 string.o
 .data          0x00404730        0x0 time.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404730      0x8d0 00

.bss            0x00405000     0xa6a0
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
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
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
OUTPUT(JACKPOT.BIN pe-i386)
