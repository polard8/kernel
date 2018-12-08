
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
 .text          0x00401000       0xa0 main.o
                0x00401000                _main
 .text          0x004010a0        0x0 ctype.o
 .text          0x004010a0     0x2a10 stdio.o
                0x00401aad                printf_i2hex
                0x00401cdf                putchar
                0x00401155                stdio_fntos
                0x00401c9b                sprintf
                0x00402558                feof
                0x00401b1b                printf2
                0x0040267e                stdioSetCursor
                0x0040246d                ungetc
                0x00403a74                rewind
                0x004014be                puts
                0x00402636                fputc
                0x004026d4                stdioGetCursorY
                0x00402700                scanf
                0x0040236b                fputs
                0x00402596                ferror
                0x00401ec1                input
                0x004013fc                scroll
                0x004023e0                gets
                0x00401d0b                outbyte
                0x004024d4                fileno
                0x00402264                fflush
                0x004022f6                fprintf
                0x00403a32                stderr_printf
                0x00402029                stdio_system_call
                0x004012ba                fopen
                0x004026a8                stdioGetCursorX
                0x00402051                getchar
                0x004019c0                printf_atoi
                0x004010a0                stdio_atoi
                0x004029b0                kvprintf
                0x00403a03                stdout_printf
                0x0040207d                stdioInitialize
                0x004024f7                fgetc
                0x00401254                fclose
                0x004025bc                fseek
                0x00403a61                perror
                0x00401e8e                _outbyte
                0x004024aa                ftell
                0x0040393f                printf
                0x004019a5                printf3
                0x00403977                vfprintf
 .text          0x00403ab0      0xc60 stdlib.o
                0x00403da6                FreeHeap
                0x00403ad8                rtGetHeapStart
                0x004040b3                free
                0x00403ab0                stdlib_system_call
                0x00403fdc                rand
                0x00403f53                stdlibInitMM
                0x00403db0                heapInit
                0x0040454d                __findenv
                0x00403aec                rtGetHeapPointer
                0x00403af6                rtGetAvailableHeap
                0x00403ff9                srand
                0x0040464d                atoi
                0x00403fb3                libcInitRT
                0x00403b00                heapSetLibcHeap
                0x00404031                stdlib_die
                0x00404618                getenv
                0x00404072                malloc
                0x00403d93                AllocateHeapEx
                0x00403ba7                AllocateHeap
                0x004044c4                stdlib_strncmp
                0x00404006                xmalloc
                0x00404522                exit
                0x00403ae2                rtGetHeapEnd
                0x004040b8                system
 .text          0x00404710      0x430 string.o
                0x004048fc                strcspn
                0x0040485f                strcat
                0x00404710                strcmp
                0x004048b6                bzero
                0x00404a3c                strtok_r
                0x004047f2                memcpy
                0x004047c9                memoryZeroMemory
                0x0040488f                bcopy
                0x0040482f                strcpy
                0x0040499c                strspn
                0x00404b11                strtok
                0x0040476b                strncmp
                0x004048d1                strlen
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404b40      0x4c0 00

.rdata          0x00405000      0x940
 .rdata         0x00405000      0x480 stdlib.o
 .rdata         0x00405480      0x380 stdio.o
                0x00405660                hex2ascii_data
 .rdata         0x00405800      0x100 ctype.o
                0x00405800                _ctype
 .rdata         0x00405900       0x40 main.o

.data           0x00405940      0x6c0
                0x00405940                data = .
                0x00405940                _data = .
                0x00405940                __data = .
 *(.data)
 .data          0x00405940        0x0 main.o
 .data          0x00405940        0x0 ctype.o
 .data          0x00405940        0x0 stdio.o
 .data          0x00405940        0x0 stdlib.o
 .data          0x00405940        0x0 string.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405940      0x6c0 00

.bss            0x00406000     0xa640
                0x00406000                bss = .
                0x00406000                _bss = .
                0x00406000                __bss = .
 *(.bss)
 .bss           0x00406000        0x0 main.o
 .bss           0x00406000        0x0 ctype.o
 .bss           0x00406000       0x10 stdio.o
 .bss           0x00406010     0x8010 stdlib.o
                0x00406010                environ
 .bss           0x0040e020       0x10 string.o
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
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(TASCII.BIN pe-i386)
