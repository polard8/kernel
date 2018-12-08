
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
 .text          0x00401000       0xa0 main.o
                0x00401000                _main
 .text          0x004010a0       0xe0 ctype.o
                0x0040113a                isspace
                0x00401160                isxdigit
                0x0040114d                isupper
                0x004010b3                isalpha
                0x004010ff                islower
                0x004010a0                isalnum
                0x00401112                isprint
                0x004010ec                isgraph
                0x004010d9                isdigit
                0x004010c6                iscntrl
                0x00401127                ispunct
 .text          0x00401180     0x1360 stdio.o
                0x00401996                putchar
                0x00401180                stdio_fntos
                0x00401952                sprintf
                0x004020c4                feof
                0x004021ea                stdioSetCursor
                0x00402026                ungetc
                0x00401450                puts
                0x004021a2                fputc
                0x00402240                stdioGetCursorY
                0x00402321                scanf
                0x00401f3c                fputs
                0x00402102                ferror
                0x00401b78                input
                0x0040138e                scroll
                0x00401fb1                gets
                0x004019c2                outbyte
                0x00401e58                fflush
                0x00401ec7                fprintf
                0x00401ce0                stdio_system_call
                0x004012d5                fopen
                0x00402214                stdioGetCursorX
                0x00401d08                getchar
                0x0040226c                stdio_atoi
                0x00401d34                stdioInitialize
                0x00402063                fgetc
                0x0040126f                fclose
                0x00402128                fseek
                0x00401b45                _outbyte
                0x00401937                printf
 .text          0x004024e0      0xaf0 stdlib.o
                0x004027d6                FreeHeap
                0x00402508                rtGetHeapStart
                0x00402a2a                free
                0x004024e0                stdlib_system_call
                0x004029bf                rand
                0x00402936                stdlibInitMM
                0x004027e0                heapInit
                0x00402ec4                __findenv
                0x0040251c                rtGetHeapPointer
                0x00402526                rtGetAvailableHeap
                0x004029dc                srand
                0x00402996                libcInitRT
                0x00402530                heapSetLibcHeap
                0x00402f8f                getenv
                0x004029e9                malloc
                0x004027c3                AllocateHeapEx
                0x004025d7                AllocateHeap
                0x00402e3b                stdlib_strncmp
                0x00402e99                exit
                0x00402512                rtGetHeapEnd
                0x00402a2f                system
 .text          0x00402fd0      0x430 string.o
                0x004031bc                strcspn
                0x0040311f                strcat
                0x00402fd0                strcmp
                0x00403176                bzero
                0x004032fc                strtok_r
                0x004030b2                memcpy
                0x00403089                memoryZeroMemory
                0x0040314f                bcopy
                0x004030ef                strcpy
                0x0040325c                strspn
                0x004033d1                strtok
                0x0040302b                strncmp
                0x00403191                strlen
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403400      0xc00 00

.rdata          0x00404000      0x510
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0x70 stdio.o
 .rdata         0x004044d0       0x40 main.o

.data           0x00404510      0xaf0
                0x00404510                data = .
                0x00404510                _data = .
                0x00404510                __data = .
 *(.data)
 .data          0x00404510        0x0 main.o
 .data          0x00404510      0x120 ctype.o
                0x00404510                _ctype_
 .data          0x00404630        0x0 stdio.o
 .data          0x00404630        0x0 stdlib.o
 .data          0x00404630        0x0 string.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404630      0x9d0 00

.bss            0x00405000     0xa640
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
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(TASCII.BIN pe-i386)
