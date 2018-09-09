
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
 .text          0x00401110     0x14c0 stdio.o
                0x00401a72                putchar
                0x00401110                stdio_fntos
                0x00401a2e                sprintf
                0x004021b1                feof
                0x004022db                stdioSetCursor
                0x00402113                ungetc
                0x0040152c                puts
                0x0040228f                fputc
                0x00402331                stdioGetCursorY
                0x00402412                scanf
                0x00402029                fputs
                0x004021ef                ferror
                0x00401c5e                input
                0x004012fd                scroll
                0x00401c54                printf_main
                0x0040209e                gets
                0x00401a9e                outbyte
                0x004014a7                app_print
                0x00401f44                fflush
                0x00401fb4                fprintf
                0x00401dc6                stdio_system_call
                0x00401265                fopen
                0x00402305                stdioGetCursorX
                0x00401dee                getchar
                0x0040235d                stdio_atoi
                0x00401e20                stdioInitialize
                0x00402150                fgetc
                0x004011ff                fclose
                0x00402215                fseek
                0x00401c21                _outbyte
                0x00401a13                printf
                0x0040143b                app_clear
 .text          0x004025d0      0xaf0 stdlib.o
                0x004028c6                FreeHeap
                0x004025f8                rtGetHeapStart
                0x00402b1a                free
                0x004025d0                stdlib_system_call
                0x00402aaf                rand
                0x00402a26                stdlibInitMM
                0x004028d0                heapInit
                0x00402fb4                __findenv
                0x0040260c                rtGetHeapPointer
                0x00402616                rtGetAvailableHeap
                0x00402acc                srand
                0x00402a86                libcInitRT
                0x00402620                heapSetLibcHeap
                0x0040307f                getenv
                0x00402ad9                malloc
                0x004028b3                AllocateHeapEx
                0x004026c7                AllocateHeap
                0x00402f2b                stdlib_strncmp
                0x00402f89                exit
                0x00402602                rtGetHeapEnd
                0x00402b1f                system
 .text          0x004030c0      0x4a0 string.o
                0x00403327                strcspn
                0x0040328a                strcat
                0x004030c0                strcmp
                0x004032e1                bzero
                0x00403467                strtok_r
                0x0040321d                memcpy
                0x004031f4                memoryZeroMemory
                0x004032ba                bcopy
                0x0040325a                strcpy
                0x004033c7                strspn
                0x0040353c                strtok
                0x00403179                str_cmp
                0x0040311b                strncmp
                0x004032fc                strlen
 .text          0x00403560       0xe0 ctype.o
                0x004035fa                isspace
                0x00403620                isxdigit
                0x0040360d                isupper
                0x00403573                isalpha
                0x004035bf                islower
                0x00403560                isalnum
                0x004035d2                isprint
                0x004035ac                isgraph
                0x00403599                isdigit
                0x00403586                iscntrl
                0x004035e7                ispunct
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403640      0x9c0 00

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
