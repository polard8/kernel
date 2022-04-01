
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
 .text          0x00401000      0x170 main.o
                0x00401135                copy
                0x004010a8                getlinelength
                0x00401000                app_test
 .text          0x00401170     0x2a10 stdio.o
                0x00401b7d                printf_i2hex
                0x00401daf                putchar
                0x00401225                stdio_fntos
                0x00401d6b                sprintf
                0x00402628                feof
                0x00401beb                printf2
                0x0040274e                stdioSetCursor
                0x0040253d                ungetc
                0x00403b44                rewind
                0x0040158e                puts
                0x00402706                fputc
                0x004027a4                stdioGetCursorY
                0x004027d0                scanf
                0x0040243b                fputs
                0x00402666                ferror
                0x00401f91                input
                0x004014cc                scroll
                0x004024b0                gets
                0x00401ddb                outbyte
                0x004025a4                fileno
                0x00402334                fflush
                0x004023c6                fprintf
                0x00403b02                stderr_printf
                0x004020f9                stdio_system_call
                0x0040138a                fopen
                0x00402778                stdioGetCursorX
                0x00402121                getchar
                0x00401a90                printf_atoi
                0x00401170                stdio_atoi
                0x00402a80                kvprintf
                0x00403ad3                stdout_printf
                0x0040214d                stdioInitialize
                0x004025c7                fgetc
                0x00401324                fclose
                0x0040268c                fseek
                0x00403b31                perror
                0x00401f5e                _outbyte
                0x0040257a                ftell
                0x00403a0f                printf
                0x00401a75                printf3
                0x00403a47                vfprintf
 .text          0x00403b80      0xc60 stdlib.o
                0x00403e76                FreeHeap
                0x00403ba8                rtGetHeapStart
                0x00404183                free
                0x00403b80                stdlib_system_call
                0x004040ac                rand
                0x00404023                stdlibInitMM
                0x00403e80                heapInit
                0x0040461d                __findenv
                0x00403bbc                rtGetHeapPointer
                0x00403bc6                rtGetAvailableHeap
                0x004040c9                srand
                0x0040471d                atoi
                0x00404083                libcInitRT
                0x00403bd0                heapSetLibcHeap
                0x00404101                stdlib_die
                0x004046e8                getenv
                0x00404142                malloc
                0x00403e63                AllocateHeapEx
                0x00403c77                AllocateHeap
                0x00404594                stdlib_strncmp
                0x004040d6                xmalloc
                0x004045f2                exit
                0x00403bb2                rtGetHeapEnd
                0x00404188                system
 .text          0x004047e0      0x430 string.o
                0x004049cc                strcspn
                0x0040492f                strcat
                0x004047e0                strcmp
                0x00404986                bzero
                0x00404b0c                strtok_r
                0x004048c2                memcpy
                0x00404899                memoryZeroMemory
                0x0040495f                bcopy
                0x004048ff                strcpy
                0x00404a6c                strspn
                0x00404be1                strtok
                0x0040483b                strncmp
                0x004049a1                strlen
 .text          0x00404c10        0x0 ctype.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404c10      0x3f0 00

.rdata          0x00405000      0x970
 .rdata         0x00405000      0x100 ctype.o
                0x00405000                _ctype
 .rdata         0x00405100      0x480 stdlib.o
 .rdata         0x00405580      0x380 stdio.o
                0x00405760                hex2ascii_data
 .rdata         0x00405900       0x70 main.o

.data           0x00405970      0x690
                0x00405970                data = .
                0x00405970                _data = .
                0x00405970                __data = .
 *(.data)
 .data          0x00405970        0x0 main.o
 .data          0x00405970        0x0 stdio.o
 .data          0x00405970        0x0 stdlib.o
 .data          0x00405970        0x0 string.o
 .data          0x00405970        0x0 ctype.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405970      0x690 00

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
OUTPUT(LONGEST1.BIN pe-i386)
