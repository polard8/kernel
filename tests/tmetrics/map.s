
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
current_semaphore   0x10              main.o
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
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
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
 .text          0x00401000      0x130 main.o
                0x00401000                app_test
 .text          0x00401130     0x1a10 api.o
                0x00401ecb                APIShowCurrentProcessInfo
                0x004026fe                api_getchar
                0x004016d2                system11
                0x00401777                refresh_buffer
                0x00401dad                APISetFocus
                0x00401735                system14
                0x00401a5e                apiInitBackground
                0x00401c9d                APICreateWindow
                0x004024ad                apiBeginPaint
                0x00401a63                MessageBox
                0x00401f49                APIreplace_window
                0x004024f4                apiGetSystemMetrics
                0x00401714                system13
                0x00402348                apiDown
                0x00402042                apiExit
                0x004023fc                enterCriticalSection
                0x00402639                gramadocore_init_execve
                0x004022b0                apiFOpen
                0x00401588                system1
                0x0040160c                system5
                0x00402128                api_refresh_screen
                0x00402679                apiDialog
                0x004021b4                apiGetCursorY
                0x00401a07                carrega_bitmap_16x16
                0x00402455                exitCriticalSection
                0x00401130                system_call
                0x004023a2                apiUp
                0x00401158                apiSystem
                0x0040260d                api_get_window_with_text_input
                0x00401756                system15
                0x00401e5d                APISetActiveWindow
                0x0040220c                apiSetClientAreaRect
                0x00401f20                APIredraw_window
                0x0040225e                apiCreateThread
                0x004019a3                SetNextWindowProcedure
                0x00402188                apiGetCursorX
                0x00401973                chama_procedimento
                0x00401a8c                call_kernel
                0x00401d29                APIRegisterWindow
                0x0040209e                api_strncmp
                0x00401f9b                APIminimize_window
                0x004015a9                system2
                0x004015ca                system3
                0x00402546                api_get_current_keyboard_responder
                0x00402235                apiCreateProcess
                0x00401def                APIGetFocus
                0x0040164e                system7
                0x0040162d                system6
                0x004024ea                apiDefDialog
                0x00401d6b                APICloseWindow
                0x00402afa                apiSendMessage
                0x00402481                initializeCriticalSection
                0x004016b1                system10
                0x004019d3                set_cursor
                0x00401f72                APImaximize_window
                0x0040266f                execve
                0x004020fc                refresh_screen
                0x0040272a                apiDisplayBMP
                0x00401c0c                call_gui
                0x00401690                system9
                0x00402643                fork
                0x0040251d                api_set_current_keyboard_responder
                0x00401ef7                APIresize_window
                0x004024b7                apiEndPaint
                0x00401a02                put_char
                0x0040190e                print_string
                0x004021e0                apiGetClientAreaRect
                0x00401944                edit_box
                0x0040206d                kill
                0x00402132                apiReboot
                0x00401a30                apiShutDown
                0x00402572                api_set_current_mouse_responder
                0x00401fed                APIget_foregroung_window
                0x004015eb                system4
                0x004022ea                apiSaveFile
                0x0040215e                apiSetCursor
                0x004016f3                system12
                0x00401913                vsync
                0x0040166f                system8
                0x004025c7                api_set_window_with_text_input
                0x00401e9f                APIGetActiveWindow
                0x00401fc4                APIupdate_window
                0x0040259b                api_get_current_mouse_responder
                0x00402072                dead_thread_collector
                0x00402287                apiStartThread
                0x00401e1b                APIKillFocus
                0x00402019                APIset_foregroung_window
                0x004024c1                apiPutChar
 .text          0x00402b40     0x1360 stdio.o
                0x00403356                putchar
                0x00402b40                stdio_fntos
                0x00403312                sprintf
                0x00403a84                feof
                0x00403baa                stdioSetCursor
                0x004039e6                ungetc
                0x00402e10                puts
                0x00403b62                fputc
                0x00403c00                stdioGetCursorY
                0x00403ce1                scanf
                0x004038fc                fputs
                0x00403ac2                ferror
                0x00403538                input
                0x00402d4e                scroll
                0x00403971                gets
                0x00403382                outbyte
                0x00403818                fflush
                0x00403887                fprintf
                0x004036a0                stdio_system_call
                0x00402c95                fopen
                0x00403bd4                stdioGetCursorX
                0x004036c8                getchar
                0x00403c2c                stdio_atoi
                0x004036f4                stdioInitialize
                0x00403a23                fgetc
                0x00402c2f                fclose
                0x00403ae8                fseek
                0x00403505                _outbyte
                0x004032f7                printf
 .text          0x00403ea0      0xaf0 stdlib.o
                0x00404196                FreeHeap
                0x00403ec8                rtGetHeapStart
                0x004043ea                free
                0x00403ea0                stdlib_system_call
                0x0040437f                rand
                0x004042f6                stdlibInitMM
                0x004041a0                heapInit
                0x00404884                __findenv
                0x00403edc                rtGetHeapPointer
                0x00403ee6                rtGetAvailableHeap
                0x0040439c                srand
                0x00404356                libcInitRT
                0x00403ef0                heapSetLibcHeap
                0x0040494f                getenv
                0x004043a9                malloc
                0x00404183                AllocateHeapEx
                0x00403f97                AllocateHeap
                0x004047fb                stdlib_strncmp
                0x00404859                exit
                0x00403ed2                rtGetHeapEnd
                0x004043ef                system
 .text          0x00404990      0x430 string.o
                0x00404b7c                strcspn
                0x00404adf                strcat
                0x00404990                strcmp
                0x00404b36                bzero
                0x00404cbc                strtok_r
                0x00404a72                memcpy
                0x00404a49                memoryZeroMemory
                0x00404b0f                bcopy
                0x00404aaf                strcpy
                0x00404c1c                strspn
                0x00404d91                strtok
                0x004049eb                strncmp
                0x00404b51                strlen
 .text          0x00404dc0       0xe0 ctype.o
                0x00404e5a                isspace
                0x00404e80                isxdigit
                0x00404e6d                isupper
                0x00404dd3                isalpha
                0x00404e1f                islower
                0x00404dc0                isalnum
                0x00404e32                isprint
                0x00404e0c                isgraph
                0x00404df9                isdigit
                0x00404de6                iscntrl
                0x00404e47                ispunct
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404ea0      0x160 00

.rdata          0x00405000      0x860
 .rdata         0x00405000      0x460 stdlib.o
 .rdata         0x00405460       0x70 stdio.o
 .rdata         0x004054d0      0x330 api.o
 .rdata         0x00405800       0x60 main.o

.data           0x00405860     0x17a0
                0x00405860                data = .
                0x00405860                _data = .
                0x00405860                __data = .
 *(.data)
 .data          0x00405860      0x440 main.o
 .data          0x00405ca0      0x440 api.o
 .data          0x004060e0        0x0 stdio.o
 .data          0x004060e0        0x0 stdlib.o
 .data          0x004060e0        0x0 string.o
 .data          0x004060e0      0x120 ctype.o
                0x004060e0                _ctype_
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x00406200      0xe00 00

.bss            0x00407000     0xa6b0
                0x00407000                bss = .
                0x00407000                _bss = .
                0x00407000                __bss = .
 *(.bss)
 .bss           0x00407000        0x0 main.o
 .bss           0x00407000       0x40 api.o
 .bss           0x00407040       0x10 stdio.o
 .bss           0x00407050     0x8010 stdlib.o
                0x00407050                environ
 .bss           0x0040f060       0x10 string.o
 .bss           0x0040f070        0x0 ctype.o
                0x00410000                . = ALIGN (0x1000)
 *fill*         0x0040f070      0xf90 00
 COMMON         0x00410000      0xdb0 main.o
                0x00410000                prompt
                0x00410400                ClientAreaInfo
                0x00410410                BufferInfo
                0x00410420                stderr
                0x00410430                prompt_pos
                0x00410440                g_using_gui
                0x00410450                stdin
                0x00410460                rect
                0x00410470                prompt_max
                0x00410480                CurrentWindow
                0x00410490                prompt_err
                0x00410890                current_semaphore
                0x004108a0                g_columns
                0x004108b0                stdout
                0x004108c0                Streams
                0x00410940                g_rows
                0x00410950                prompt_out
                0x00410d50                g_cursor_y
                0x00410d60                CursorInfo
                0x00410d70                prompt_status
                0x00410d80                g_char_attrib
                0x00410d90                ApplicationInfo
                0x00410da0                g_cursor_x
 COMMON         0x00410db0      0x900 stdlib.o
                0x00410db0                current_mmblock
                0x00410dc0                mm_prev_pointer
                0x00410dd0                heap_end
                0x00410de0                g_available_heap
                0x00410df0                heap_start
                0x00410e00                heapCount
                0x00410e10                HEAP_START
                0x00410e20                g_heap_pointer
                0x00410e30                heapList
                0x00411230                randseed
                0x00411240                HEAP_SIZE
                0x00411250                last_size
                0x00411260                last_valid
                0x00411270                mmblockList
                0x00411670                libcHeap
                0x00411680                Heap
                0x00411690                mmblockCount
                0x004116a0                HEAP_END
                0x004116b0                end = .
                0x004116b0                _end = .
                0x004116b0                __end = .
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD ctype.o
OUTPUT(TMETRICS.BIN pe-i386)
