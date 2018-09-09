
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
TOPBAR              0x20              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
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
STATUSBAR           0x20              main.o
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
 .text          0x00401000        0xc crt0.o
                0x00401000                _crt0Main
 .text          0x0040100c      0x3e0 main.o
                0x00401134                mainTextEditor
                0x0040100c                mainGetMessage
                0x0040135d                editorClearScreen
 .text          0x004013ec      0x960 stdlib.o
                0x004016a7                FreeHeap
                0x004013ec                rtGetHeapStart
                0x004018ee                free
                0x00401890                rand
                0x00401807                stdlibInitMM
                0x004016b1                heapInit
                0x00401400                rtGetHeapPointer
                0x0040140a                rtGetAvailableHeap
                0x00401867                libcInitRT
                0x00401414                heapSetLibcHeap
                0x004018ad                malloc
                0x00401694                AllocateHeapEx
                0x004014bb                AllocateHeap
                0x00401ce5                stdlib_strncmp
                0x004013f6                rtGetHeapEnd
                0x004018f3                system
 .text          0x00401d4c     0x10e0 stdio.o
                0x00402695                putchar
                0x00401d4c                stdio_fntos
                0x00402651                sprintf
                0x00402cf2                feof
                0x00402dd2                fputc
                0x00402bd5                fputs
                0x00402d30                ferror
                0x00402881                input
                0x00401f3b                scroll
                0x00402877                printf_main
                0x00402c4a                gets
                0x004026c1                outbyte
                0x004020e5                app_print
                0x00402af0                fflush
                0x00402b60                fprintf
                0x00402978                stdio_system_call
                0x00401ea1                fopen
                0x004029a0                getchar
                0x004029cc                stdioInitialize
                0x00402cbf                fgetc
                0x00401e3b                fclose
                0x00402d58                fseek
                0x00402844                _outbyte
                0x00402636                printf
                0x00402079                app_clear
 .text          0x00402e2c      0x4a0 string.o
                0x00403093                strcspn
                0x00402ff6                strcat
                0x00402e2c                strcmp
                0x0040304d                bzero
                0x004031d3                strtok_r
                0x00402f89                memcpy
                0x00402f60                memoryZeroMemory
                0x00403026                bcopy
                0x00402fc6                strcpy
                0x00403133                strspn
                0x004032a8                strtok
                0x00402ee5                str_cmp
                0x00402e87                strncmp
                0x00403068                strlen
 .text          0x004032cc     0x1530 api.o
                0x0040407f                APIShowCurrentProcessInfo
                0x004047cf                api_getchar
                0x0040386c                system11
                0x00403911                refresh_buffer
                0x00403f61                APISetFocus
                0x004038cf                system14
                0x00403bf6                apiInitBackground
                0x00403e35                APICreateWindow
                0x004045ac                apiBeginPaint
                0x00403bfb                MessageBox
                0x004040fd                APIreplace_window
                0x004045f3                apiGetSystemMetrics
                0x004038ae                system13
                0x00404463                apiDown
                0x004044fb                enterCriticalSection
                0x00404738                gramadocore_init_execve
                0x00404439                apiFOpen
                0x00403722                system1
                0x004037a6                system5
                0x004042b1                api_refresh_screen
                0x00404756                apiDialog
                0x0040433d                apiGetCursorY
                0x00403ba1                carrega_bitmap_16x16
                0x00404554                exitCriticalSection
                0x004032cc                system_call
                0x004044af                apiUp
                0x004032f4                apiSystem
                0x0040470c                api_get_window_with_text_input
                0x004038f0                system15
                0x00404011                APISetActiveWindow
                0x00404395                apiSetClientAreaRect
                0x004040d4                APIredraw_window
                0x004043e7                apiCreateThread
                0x00403b3d                SetNextWindowProcedure
                0x00404311                apiGetCursorX
                0x00403b0d                chama_procedimento
                0x00403c24                call_kernel
                0x00403edd                APIRegisterWindow
                0x00404227                api_strncmp
                0x0040414f                APIminimize_window
                0x00403743                system2
                0x00403764                system3
                0x00404645                api_get_current_keyboard_responder
                0x004043be                apiCreateProcess
                0x00403fa3                APIGetFocus
                0x004037e8                system7
                0x004037c7                system6
                0x004045e9                apiDefDialog
                0x00403f1f                APICloseWindow
                0x00404580                initializeCriticalSection
                0x0040384b                system10
                0x00403b6d                set_cursor
                0x00404126                APImaximize_window
                0x0040474c                execve
                0x00404285                refresh_screen
                0x00403da4                call_gui
                0x0040382a                system9
                0x00404742                fork
                0x0040461c                api_set_current_keyboard_responder
                0x004040ab                APIresize_window
                0x004045b6                apiEndPaint
                0x00403b9c                put_char
                0x00403aa8                print_string
                0x00404369                apiGetClientAreaRect
                0x00403ade                edit_box
                0x004041f6                kill
                0x004042bb                apiReboot
                0x00403bca                apiShutDown
                0x00404671                api_set_current_mouse_responder
                0x004041cd                exit
                0x00404178                APIget_foregroung_window
                0x00403785                system4
                0x004042e7                apiSetCursor
                0x0040388d                system12
                0x00403aad                vsync
                0x00403809                system8
                0x004046c6                api_set_window_with_text_input
                0x00404053                APIGetActiveWindow
                0x0040469a                api_get_current_mouse_responder
                0x004041fb                dead_thread_collector
                0x00404410                apiStartThread
                0x00403fcf                APIKillFocus
                0x004041a4                APIset_foregroung_window
                0x004045c0                apiPutChar
 .text          0x004047fc      0x140 status.o
                0x0040489a                update_statuts_bar
                0x004047fc                statusInitializeStatusBar
 .text          0x0040493c       0xa0 topbar.o
                0x0040493c                topbarInitializeTopBar
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x004049dc      0x624 00

.rdata          0x00405000      0x980
 .rdata         0x00405000       0x40 topbar.o
 .rdata         0x00405040       0x40 status.o
 .rdata         0x00405080      0x320 api.o
 .rdata         0x004053a0       0x40 stdio.o
 .rdata         0x004053e0      0x430 stdlib.o
 .rdata         0x00405810      0x170 main.o

.data           0x00405980      0x680
                0x00405980                data = .
                0x00405980                _data = .
                0x00405980                __data = .
 *(.data)
 .data          0x00405980       0x10 main.o
                0x00405980                running
 .data          0x00405990       0x10 stdlib.o
 .data          0x004059a0        0x0 stdio.o
 .data          0x004059a0        0x0 string.o
 .data          0x004059a0        0x0 api.o
 .data          0x004059a0        0x0 status.o
 .data          0x004059a0        0x0 topbar.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x004059a0      0x660 00

.bss            0x00406000     0xa6e0
                0x00406000                bss = .
                0x00406000                _bss = .
                0x00406000                __bss = .
 *(.bss)
 .bss           0x00406000       0x30 main.o
 .bss           0x00406030     0x8000 stdlib.o
 .bss           0x0040e030       0x10 stdio.o
 .bss           0x0040e040       0x10 string.o
 .bss           0x0040e050       0x30 api.o
 .bss           0x0040e080       0x30 status.o
 .bss           0x0040e0b0       0x30 topbar.o
                0x0040f000                . = ALIGN (0x1000)
 *fill*         0x0040e0e0      0xf20 00
 COMMON         0x0040f000      0xdf0 main.o
                0x0040f000                prompt
                0x0040f400                ClientAreaInfo
                0x0040f410                BufferInfo
                0x0040f420                stderr
                0x0040f430                prompt_pos
                0x0040f440                g_using_gui
                0x0040f450                stdin
                0x0040f460                rect
                0x0040f470                prompt_max
                0x0040f480                TOPBAR
                0x0040f4a0                CurrentWindow
                0x0040f4b0                prompt_err
                0x0040f8b0                current_semaphore
                0x0040f8c0                g_columns
                0x0040f8d0                stdout
                0x0040f8e0                Streams
                0x0040f960                g_rows
                0x0040f970                prompt_out
                0x0040fd70                g_cursor_y
                0x0040fd80                CursorInfo
                0x0040fd90                STATUSBAR
                0x0040fdb0                prompt_status
                0x0040fdc0                g_char_attrib
                0x0040fdd0                ApplicationInfo
                0x0040fde0                g_cursor_x
 COMMON         0x0040fdf0      0x8f0 stdlib.o
                0x0040fdf0                current_mmblock
                0x0040fe00                mm_prev_pointer
                0x0040fe10                heap_end
                0x0040fe20                g_available_heap
                0x0040fe30                heap_start
                0x0040fe40                heapCount
                0x0040fe50                HEAP_START
                0x0040fe60                g_heap_pointer
                0x0040fe70                heapList
                0x00410270                HEAP_SIZE
                0x00410280                last_size
                0x00410290                last_valid
                0x004102a0                mmblockList
                0x004106a0                libcHeap
                0x004106b0                Heap
                0x004106c0                mmblockCount
                0x004106d0                HEAP_END
                0x004106e0                end = .
                0x004106e0                _end = .
                0x004106e0                __end = .
LOAD crt0.o
LOAD main.o
LOAD stdlib.o
LOAD stdio.o
LOAD string.o
LOAD api.o
LOAD status.o
LOAD topbar.o
OUTPUT(TEDITOR.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f crt0.o
