
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
 .text          0x00401060      0x240 main.o
                0x0040109a                Add
                0x00401060                get_a
                0x004010b1                app_main
                0x004010a5                Multi
                0x00401087                do_print_string
 .text          0x004012a0       0xe0 ctype.o
                0x0040133a                isspace
                0x00401360                isxdigit
                0x0040134d                isupper
                0x004012b3                isalpha
                0x004012ff                islower
                0x004012a0                isalnum
                0x00401312                isprint
                0x004012ec                isgraph
                0x004012d9                isdigit
                0x004012c6                iscntrl
                0x00401327                ispunct
 .text          0x00401380     0x1360 stdio.o
                0x00401b96                putchar
                0x00401380                stdio_fntos
                0x00401b52                sprintf
                0x004022c4                feof
                0x004023ea                stdioSetCursor
                0x00402226                ungetc
                0x00401650                puts
                0x004023a2                fputc
                0x00402440                stdioGetCursorY
                0x00402521                scanf
                0x0040213c                fputs
                0x00402302                ferror
                0x00401d78                input
                0x0040158e                scroll
                0x004021b1                gets
                0x00401bc2                outbyte
                0x00402058                fflush
                0x004020c7                fprintf
                0x00401ee0                stdio_system_call
                0x004014d5                fopen
                0x00402414                stdioGetCursorX
                0x00401f08                getchar
                0x0040246c                stdio_atoi
                0x00401f34                stdioInitialize
                0x00402263                fgetc
                0x0040146f                fclose
                0x00402328                fseek
                0x00401d45                _outbyte
                0x00401b37                printf
 .text          0x004026e0      0xaf0 stdlib.o
                0x004029d6                FreeHeap
                0x00402708                rtGetHeapStart
                0x00402c2a                free
                0x004026e0                stdlib_system_call
                0x00402bbf                rand
                0x00402b36                stdlibInitMM
                0x004029e0                heapInit
                0x004030c4                __findenv
                0x0040271c                rtGetHeapPointer
                0x00402726                rtGetAvailableHeap
                0x00402bdc                srand
                0x00402b96                libcInitRT
                0x00402730                heapSetLibcHeap
                0x0040318f                getenv
                0x00402be9                malloc
                0x004029c3                AllocateHeapEx
                0x004027d7                AllocateHeap
                0x0040303b                stdlib_strncmp
                0x00403099                exit
                0x00402712                rtGetHeapEnd
                0x00402c2f                system
 .text          0x004031d0      0x430 string.o
                0x004033bc                strcspn
                0x0040331f                strcat
                0x004031d0                strcmp
                0x00403376                bzero
                0x004034fc                strtok_r
                0x004032b2                memcpy
                0x00403289                memoryZeroMemory
                0x0040334f                bcopy
                0x004032ef                strcpy
                0x0040345c                strspn
                0x004035d1                strtok
                0x0040322b                strncmp
                0x00403391                strlen
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403600      0xa00 00

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
