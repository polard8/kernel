
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
 .text          0x004010a0     0x1110 stdio.o
                0x004019e7                putchar
                0x004010a0                stdio_fntos
                0x004019a3                sprintf
                0x00402078                feof
                0x00402156                fputc
                0x00401f2d                fputs
                0x004020b6                ferror
                0x00401bd3                input
                0x0040128d                scroll
                0x00401bc9                printf_main
                0x00401fa2                gets
                0x00401a13                outbyte
                0x00401437                app_print
                0x00401e48                fflush
                0x00401eb8                fprintf
                0x00401cca                stdio_system_call
                0x004011f5                fopen
                0x00401cf2                getchar
                0x00401d24                stdioInitialize
                0x00402017                fgetc
                0x0040118f                fclose
                0x004020dc                fseek
                0x00401b96                _outbyte
                0x00401988                printf
                0x004013cb                app_clear
 .text          0x004021b0      0xae0 stdlib.o
                0x004024a6                FreeHeap
                0x004021d8                rtGetHeapStart
                0x004026ed                free
                0x004021b0                stdlib_system_call
                0x0040268f                rand
                0x00402606                stdlibInitMM
                0x004024b0                heapInit
                0x00402b85                __findenv
                0x004021ec                rtGetHeapPointer
                0x004021f6                rtGetAvailableHeap
                0x00402666                libcInitRT
                0x00402200                heapSetLibcHeap
                0x00402c50                getenv
                0x004026ac                malloc
                0x00402493                AllocateHeapEx
                0x004022a7                AllocateHeap
                0x00402afe                stdlib_strncmp
                0x00402b5c                exit
                0x004021e2                rtGetHeapEnd
                0x004026f2                system
 .text          0x00402c90      0x4a0 string.o
                0x00402ef7                strcspn
                0x00402e5a                strcat
                0x00402c90                strcmp
                0x00402eb1                bzero
                0x00403037                strtok_r
                0x00402ded                memcpy
                0x00402dc4                memoryZeroMemory
                0x00402e8a                bcopy
                0x00402e2a                strcpy
                0x00402f97                strspn
                0x0040310c                strtok
                0x00402d49                str_cmp
                0x00402ceb                strncmp
                0x00402ecc                strlen
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403130      0xed0 00

.rdata          0x00404000      0x4e0
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0x40 stdio.o
 .rdata         0x004044a0       0x40 main.o

.data           0x004044e0      0xb20
                0x004044e0                data = .
                0x004044e0                _data = .
                0x004044e0                __data = .
 *(.data)
 .data          0x004044e0        0x0 main.o
 .data          0x004044e0        0x0 stdio.o
 .data          0x004044e0       0x10 stdlib.o
 .data          0x004044f0        0x0 string.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x004044f0      0xb10 00

.bss            0x00405000     0xa630
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
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
 COMMON         0x0040ed40      0x8f0 stdlib.o
                0x0040ed40                current_mmblock
                0x0040ed50                mm_prev_pointer
                0x0040ed60                heap_end
                0x0040ed70                g_available_heap
                0x0040ed80                heap_start
                0x0040ed90                heapCount
                0x0040eda0                HEAP_START
                0x0040edb0                g_heap_pointer
                0x0040edc0                heapList
                0x0040f1c0                HEAP_SIZE
                0x0040f1d0                last_size
                0x0040f1e0                last_valid
                0x0040f1f0                mmblockList
                0x0040f5f0                libcHeap
                0x0040f600                Heap
                0x0040f610                mmblockCount
                0x0040f620                HEAP_END
                0x0040f630                end = .
                0x0040f630                _end = .
                0x0040f630                __end = .
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(TASCII.BIN pe-i386)
