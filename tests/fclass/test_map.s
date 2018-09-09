
Allocating common symbols
Common symbol       size              file

prompt              0x400             crt0.o
stderr              0x10              crt0.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              crt0.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             crt0.o
randseed            0x10              stdlib.o
g_columns           0x10              crt0.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
Streams             0x80              crt0.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x400             crt0.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
g_char_attrib       0x10              crt0.o
g_cursor_x          0x10              crt0.o
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
 .text          0x00401000       0x60 crt0.o
                0x00401000                _main
 .text          0x00401060      0x230 main.o
                0x0040109a                Add
                0x00401060                get_a
                0x004010b1                app_main
                0x004010a5                Multi
                0x00401087                do_print_string
 .text          0x00401290       0xe0 ctype.o
                0x0040132a                isspace
                0x00401350                isxdigit
                0x0040133d                isupper
                0x004012a3                isalpha
                0x004012ef                islower
                0x00401290                isalnum
                0x00401302                isprint
                0x004012dc                isgraph
                0x004012c9                isdigit
                0x004012b6                iscntrl
                0x00401317                ispunct
 .text          0x00401370     0x1380 stdio.o
                0x00401b9d                putchar
                0x00401370                stdio_fntos
                0x00401b59                sprintf
                0x004022d1                feof
                0x004023fb                stdioSetCursor
                0x00402233                ungetc
                0x00401657                puts
                0x004023af                fputc
                0x00402451                stdioGetCursorY
                0x00402532                scanf
                0x00402149                fputs
                0x0040230f                ferror
                0x00401d7f                input
                0x0040155d                scroll
                0x004021be                gets
                0x00401bc9                outbyte
                0x00402065                fflush
                0x004020d4                fprintf
                0x00401ee7                stdio_system_call
                0x004014c5                fopen
                0x00402425                stdioGetCursorX
                0x00401f0f                getchar
                0x0040247d                stdio_atoi
                0x00401f41                stdioInitialize
                0x00402270                fgetc
                0x0040145f                fclose
                0x00402335                fseek
                0x00401d4c                _outbyte
                0x00401b3e                printf
                0x0040161f                app_clear
 .text          0x004026f0      0xaf0 stdlib.o
                0x004029e6                FreeHeap
                0x00402718                rtGetHeapStart
                0x00402c3a                free
                0x004026f0                stdlib_system_call
                0x00402bcf                rand
                0x00402b46                stdlibInitMM
                0x004029f0                heapInit
                0x004030d4                __findenv
                0x0040272c                rtGetHeapPointer
                0x00402736                rtGetAvailableHeap
                0x00402bec                srand
                0x00402ba6                libcInitRT
                0x00402740                heapSetLibcHeap
                0x0040319f                getenv
                0x00402bf9                malloc
                0x004029d3                AllocateHeapEx
                0x004027e7                AllocateHeap
                0x0040304b                stdlib_strncmp
                0x004030a9                exit
                0x00402722                rtGetHeapEnd
                0x00402c3f                system
 .text          0x004031e0      0x4a0 string.o
                0x00403447                strcspn
                0x004033aa                strcat
                0x004031e0                strcmp
                0x00403401                bzero
                0x00403587                strtok_r
                0x0040333d                memcpy
                0x00403314                memoryZeroMemory
                0x004033da                bcopy
                0x0040337a                strcpy
                0x004034e7                strspn
                0x0040365c                strtok
                0x00403299                str_cmp
                0x0040323b                strncmp
                0x0040341c                strlen
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403680      0x980 00

.rdata          0x00404000      0x5e0
 .rdata         0x00404000      0x460 stdlib.o
 .rdata         0x00404460       0x70 stdio.o
 .rdata         0x004044d0       0xe0 main.o
 .rdata         0x004045b0       0x30 crt0.o

.data           0x004045e0      0xa20
                0x004045e0                data = .
                0x004045e0                _data = .
                0x004045e0                __data = .
 *(.data)
 .data          0x004045e0        0x0 crt0.o
 .data          0x004045e0        0x0 main.o
 .data          0x004045e0      0x120 ctype.o
                0x004045e0                _ctype_
 .data          0x00404700        0x0 stdio.o
 .data          0x00404700        0x0 stdlib.o
 .data          0x00404700        0x0 string.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404700      0x900 00

.bss            0x00405000     0xa640
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 crt0.o
 .bss           0x00405000        0x0 main.o
 .bss           0x00405000        0x0 ctype.o
 .bss           0x00405000       0x10 stdio.o
 .bss           0x00405010     0x8010 stdlib.o
                0x00405010                environ
 .bss           0x0040d020       0x10 string.o
                0x0040e000                . = ALIGN (0x1000)
 *fill*         0x0040d030      0xfd0 00
 COMMON         0x0040e000      0xd40 crt0.o
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
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(FCLASS.BIN pe-i386)
