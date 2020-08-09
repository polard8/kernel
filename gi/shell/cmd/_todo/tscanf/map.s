
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

.text           0x00401000     0x4000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x110 main.o
                0x00401000                _main
 .text          0x00401110     0x2a10 stdio.o
                0x00401b1d                printf_i2hex
                0x00401d4f                putchar
                0x004011c5                stdio_fntos
                0x00401d0b                sprintf
                0x004025c8                feof
                0x00401b8b                printf2
                0x004026ee                stdioSetCursor
                0x004024dd                ungetc
                0x00403ae4                rewind
                0x0040152e                puts
                0x004026a6                fputc
                0x00402744                stdioGetCursorY
                0x00402770                scanf
                0x004023db                fputs
                0x00402606                ferror
                0x00401f31                input
                0x0040146c                scroll
                0x00402450                gets
                0x00401d7b                outbyte
                0x00402544                fileno
                0x004022d4                fflush
                0x00402366                fprintf
                0x00403aa2                stderr_printf
                0x00402099                stdio_system_call
                0x0040132a                fopen
                0x00402718                stdioGetCursorX
                0x004020c1                getchar
                0x00401a30                printf_atoi
                0x00401110                stdio_atoi
                0x00402a20                kvprintf
                0x00403a73                stdout_printf
                0x004020ed                stdioInitialize
                0x00402567                fgetc
                0x004012c4                fclose
                0x0040262c                fseek
                0x00403ad1                perror
                0x00401efe                _outbyte
                0x0040251a                ftell
                0x004039af                printf
                0x00401a15                printf3
                0x004039e7                vfprintf
 .text          0x00403b20      0xc60 stdlib.o
                0x00403e16                FreeHeap
                0x00403b48                rtGetHeapStart
                0x00404123                free
                0x00403b20                stdlib_system_call
                0x0040404c                rand
                0x00403fc3                stdlibInitMM
                0x00403e20                heapInit
                0x004045bd                __findenv
                0x00403b5c                rtGetHeapPointer
                0x00403b66                rtGetAvailableHeap
                0x00404069                srand
                0x004046bd                atoi
                0x00404023                libcInitRT
                0x00403b70                heapSetLibcHeap
                0x004040a1                stdlib_die
                0x00404688                getenv
                0x004040e2                malloc
                0x00403e03                AllocateHeapEx
                0x00403c17                AllocateHeap
                0x00404534                stdlib_strncmp
                0x00404076                xmalloc
                0x00404592                exit
                0x00403b52                rtGetHeapEnd
                0x00404128                system
 .text          0x00404780      0x430 string.o
                0x0040496c                strcspn
                0x004048cf                strcat
                0x00404780                strcmp
                0x00404926                bzero
                0x00404aac                strtok_r
                0x00404862                memcpy
                0x00404839                memoryZeroMemory
                0x004048ff                bcopy
                0x0040489f                strcpy
                0x00404a0c                strspn
                0x00404b81                strtok
                0x004047db                strncmp
                0x00404941                strlen
 .text          0x00404bb0        0x0 ctype.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404bb0      0x450 00

.rdata          0x00405000      0x9c0
 .rdata         0x00405000      0x100 ctype.o
                0x00405000                _ctype
 .rdata         0x00405100      0x480 stdlib.o
 .rdata         0x00405580      0x380 stdio.o
                0x00405760                hex2ascii_data
 .rdata         0x00405900       0xc0 main.o

.data           0x004059c0      0x640
                0x004059c0                data = .
                0x004059c0                _data = .
                0x004059c0                __data = .
 *(.data)
 .data          0x004059c0        0x0 main.o
 .data          0x004059c0        0x0 stdio.o
 .data          0x004059c0        0x0 stdlib.o
 .data          0x004059c0        0x0 string.o
 .data          0x004059c0        0x0 ctype.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x004059c0      0x640 00

.bss            0x00406000     0xa640
                0x00406000                bss = .
                0x00406000                _bss = .
                0x00406000                __bss = .
 *(.bss)
 .bss           0x00406000        0x0 main.o
 .bss           0x00406000       0x10 stdio.o
 .bss           0x00406010     0x8010 stdlib.o
                0x00406010                environ
 .bss           0x0040e020       0x10 string.o
 .bss           0x0040e030        0x0 ctype.o
                0x0040f000                . = ALIGN (0x1000)
 *fill*         0x0040e030      0xfd0 00
 COMMON         0x0040f000      0xd40 main.o
                0x0040f000                prompt
                0x0040f400                stderr
                0x0040f410                prompt_pos
                0x0040f420                g_using_gui
                0x0040f430                stdin
                0x0040f440                prompt_max
                0x0040f450                prompt_err
                0x0040f850                g_columns
                0x0040f860                stdout
                0x0040f870                Streams
                0x0040f8f0                g_rows
                0x0040f900                prompt_out
                0x0040fd00                g_cursor_y
                0x0040fd10                prompt_status
                0x0040fd20                g_char_attrib
                0x0040fd30                g_cursor_x
 COMMON         0x0040fd40      0x900 stdlib.o
                0x0040fd40                current_mmblock
                0x0040fd50                mm_prev_pointer
                0x0040fd60                heap_end
                0x0040fd70                g_available_heap
                0x0040fd80                heap_start
                0x0040fd90                heapCount
                0x0040fda0                HEAP_START
                0x0040fdb0                g_heap_pointer
                0x0040fdc0                heapList
                0x004101c0                randseed
                0x004101d0                HEAP_SIZE
                0x004101e0                last_size
                0x004101f0                last_valid
                0x00410200                mmblockList
                0x00410600                libcHeap
                0x00410610                Heap
                0x00410620                mmblockCount
                0x00410630                HEAP_END
                0x00410640                end = .
                0x00410640                _end = .
                0x00410640                __end = .
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD ctype.o
OUTPUT(TSCANF.BIN pe-i386)
