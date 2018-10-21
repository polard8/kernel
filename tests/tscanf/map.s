
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

.text           0x00401000     0x3000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x110 main.o
                0x00401000                _main
 .text          0x00401110     0x1360 stdio.o
                0x00401926                putchar
                0x00401110                stdio_fntos
                0x004018e2                sprintf
                0x00402054                feof
                0x0040217a                stdioSetCursor
                0x00401fb6                ungetc
                0x004013e0                puts
                0x00402132                fputc
                0x004021d0                stdioGetCursorY
                0x004022b1                scanf
                0x00401ecc                fputs
                0x00402092                ferror
                0x00401b08                input
                0x0040131e                scroll
                0x00401f41                gets
                0x00401952                outbyte
                0x00401de8                fflush
                0x00401e57                fprintf
                0x00401c70                stdio_system_call
                0x00401265                fopen
                0x004021a4                stdioGetCursorX
                0x00401c98                getchar
                0x004021fc                stdio_atoi
                0x00401cc4                stdioInitialize
                0x00401ff3                fgetc
                0x004011ff                fclose
                0x004020b8                fseek
                0x00401ad5                _outbyte
                0x004018c7                printf
 .text          0x00402470      0xaf0 stdlib.o
                0x00402766                FreeHeap
                0x00402498                rtGetHeapStart
                0x004029ba                free
                0x00402470                stdlib_system_call
                0x0040294f                rand
                0x004028c6                stdlibInitMM
                0x00402770                heapInit
                0x00402e54                __findenv
                0x004024ac                rtGetHeapPointer
                0x004024b6                rtGetAvailableHeap
                0x0040296c                srand
                0x00402926                libcInitRT
                0x004024c0                heapSetLibcHeap
                0x00402f1f                getenv
                0x00402979                malloc
                0x00402753                AllocateHeapEx
                0x00402567                AllocateHeap
                0x00402dcb                stdlib_strncmp
                0x00402e29                exit
                0x004024a2                rtGetHeapEnd
                0x004029bf                system
 .text          0x00402f60      0x430 string.o
                0x0040314c                strcspn
                0x004030af                strcat
                0x00402f60                strcmp
                0x00403106                bzero
                0x0040328c                strtok_r
                0x00403042                memcpy
                0x00403019                memoryZeroMemory
                0x004030df                bcopy
                0x0040307f                strcpy
                0x004031ec                strspn
                0x00403361                strtok
                0x00402fbb                strncmp
                0x00403121                strlen
 .text          0x00403390       0xe0 ctype.o
                0x0040342a                isspace
                0x00403450                isxdigit
                0x0040343d                isupper
                0x004033a3                isalpha
                0x004033ef                islower
                0x00403390                isalnum
                0x00403402                isprint
                0x004033dc                isgraph
                0x004033c9                isdigit
                0x004033b6                iscntrl
                0x00403417                ispunct
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403470      0xb90 00

.rdata          0x00404000      0x590
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0x70 stdio.o
 .rdata         0x004044d0       0xc0 main.o

.data           0x00404590      0xa70
                0x00404590                data = .
                0x00404590                _data = .
                0x00404590                __data = .
 *(.data)
 .data          0x00404590        0x0 main.o
 .data          0x00404590        0x0 stdio.o
 .data          0x00404590        0x0 stdlib.o
 .data          0x00404590        0x0 string.o
 .data          0x00404590      0x120 ctype.o
                0x00404590                _ctype_
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x004046b0      0x950 00

.bss            0x00405000     0xa640
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
 .bss           0x00405000       0x10 stdio.o
 .bss           0x00405010     0x8010 stdlib.o
                0x00405010                environ
 .bss           0x0040d020       0x10 string.o
 .bss           0x0040d030        0x0 ctype.o
                0x0040e000                . = ALIGN (0x1000)
 *fill*         0x0040d030      0xfd0 00
 COMMON         0x0040e000      0xd40 main.o
                0x0040e000                prompt
                0x0040e400                stderr
                0x0040e410                prompt_pos
                0x0040e420                g_using_gui
                0x0040e430                stdin
                0x0040e440                prompt_max
                0x0040e450                prompt_err
                0x0040e850                g_columns
                0x0040e860                stdout
                0x0040e870                Streams
                0x0040e8f0                g_rows
                0x0040e900                prompt_out
                0x0040ed00                g_cursor_y
                0x0040ed10                prompt_status
                0x0040ed20                g_char_attrib
                0x0040ed30                g_cursor_x
 COMMON         0x0040ed40      0x900 stdlib.o
                0x0040ed40                current_mmblock
                0x0040ed50                mm_prev_pointer
                0x0040ed60                heap_end
                0x0040ed70                g_available_heap
                0x0040ed80                heap_start
                0x0040ed90                heapCount
                0x0040eda0                HEAP_START
                0x0040edb0                g_heap_pointer
                0x0040edc0                heapList
                0x0040f1c0                randseed
                0x0040f1d0                HEAP_SIZE
                0x0040f1e0                last_size
                0x0040f1f0                last_valid
                0x0040f200                mmblockList
                0x0040f600                libcHeap
                0x0040f610                Heap
                0x0040f620                mmblockCount
                0x0040f630                HEAP_END
                0x0040f640                end = .
                0x0040f640                _end = .
                0x0040f640                __end = .
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD ctype.o
OUTPUT(TSCANF.BIN pe-i386)
