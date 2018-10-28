
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mWindow             0x10              main.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
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
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
gWindow             0x10              main.o
dialogbox_button2   0x10              api.o
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

.text           0x00401000     0x5000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000        0xc crt0.o
                0x00401000                _crt0Main
 .text          0x0040100c      0x460 main.o
                0x0040103c                mainTextEditor
                0x0040100c                mainGetMessage
                0x00401411                tgfeProcedure
                0x0040138c                editorClearScreen
 .text          0x0040146c       0xe0 ctype.o
                0x00401506                isspace
                0x0040152c                isxdigit
                0x00401519                isupper
                0x0040147f                isalpha
                0x004014cb                islower
                0x0040146c                isalnum
                0x004014de                isprint
                0x004014b8                isgraph
                0x004014a5                isdigit
                0x00401492                iscntrl
                0x004014f3                ispunct
 .text          0x0040154c      0xaf0 stdlib.o
                0x00401842                FreeHeap
                0x00401574                rtGetHeapStart
                0x00401a96                free
                0x0040154c                stdlib_system_call
                0x00401a2b                rand
                0x004019a2                stdlibInitMM
                0x0040184c                heapInit
                0x00401f30                __findenv
                0x00401588                rtGetHeapPointer
                0x00401592                rtGetAvailableHeap
                0x00401a48                srand
                0x00401a02                libcInitRT
                0x0040159c                heapSetLibcHeap
                0x00401ffb                getenv
                0x00401a55                malloc
                0x0040182f                AllocateHeapEx
                0x00401643                AllocateHeap
                0x00401ea7                stdlib_strncmp
                0x00401f05                exit
                0x0040157e                rtGetHeapEnd
                0x00401a9b                system
 .text          0x0040203c     0x1360 stdio.o
                0x00402852                putchar
                0x0040203c                stdio_fntos
                0x0040280e                sprintf
                0x00402f80                feof
                0x004030a6                stdioSetCursor
                0x00402ee2                ungetc
                0x0040230c                puts
                0x0040305e                fputc
                0x004030fc                stdioGetCursorY
                0x004031dd                scanf
                0x00402df8                fputs
                0x00402fbe                ferror
                0x00402a34                input
                0x0040224a                scroll
                0x00402e6d                gets
                0x0040287e                outbyte
                0x00402d14                fflush
                0x00402d83                fprintf
                0x00402b9c                stdio_system_call
                0x00402191                fopen
                0x004030d0                stdioGetCursorX
                0x00402bc4                getchar
                0x00403128                stdio_atoi
                0x00402bf0                stdioInitialize
                0x00402f1f                fgetc
                0x0040212b                fclose
                0x00402fe4                fseek
                0x00402a01                _outbyte
                0x004027f3                printf
 .text          0x0040339c      0x430 string.o
                0x00403588                strcspn
                0x004034eb                strcat
                0x0040339c                strcmp
                0x00403542                bzero
                0x004036c8                strtok_r
                0x0040347e                memcpy
                0x00403455                memoryZeroMemory
                0x0040351b                bcopy
                0x004034bb                strcpy
                0x00403628                strspn
                0x0040379d                strtok
                0x004033f7                strncmp
                0x0040355d                strlen
 .text          0x004037cc     0x2550 api.o
                0x00405056                APIShowCurrentProcessInfo
                0x00405889                api_getchar
                0x00403d6e                system11
                0x00403e13                refresh_buffer
                0x00404f38                APISetFocus
                0x00403dd1                system14
                0x004040fa                apiInitBackground
                0x00404e28                APICreateWindow
                0x00405638                apiBeginPaint
                0x004040ff                MessageBox
                0x004050d4                APIreplace_window
                0x0040567f                apiGetSystemMetrics
                0x00403db0                system13
                0x004054d3                apiDown
                0x00404b8a                dbProcedure
                0x004051cd                apiExit
                0x00405587                enterCriticalSection
                0x004057c4                gramadocore_init_execve
                0x0040543b                apiFOpen
                0x00403c24                system1
                0x00403ca8                system5
                0x004052b3                api_refresh_screen
                0x00405804                apiDialog
                0x0040533f                apiGetCursorY
                0x004040a3                carrega_bitmap_16x16
                0x004055e0                exitCriticalSection
                0x004037cc                system_call
                0x0040552d                apiUp
                0x004037f4                apiSystem
                0x00405798                api_get_window_with_text_input
                0x00403df2                system15
                0x00404fe8                APISetActiveWindow
                0x00405397                apiSetClientAreaRect
                0x00405cc6                apiDrawText
                0x004050ab                APIredraw_window
                0x004053e9                apiCreateThread
                0x0040403f                SetNextWindowProcedure
                0x00405313                apiGetCursorX
                0x0040400f                chama_procedimento
                0x00404c17                call_kernel
                0x00404eb4                APIRegisterWindow
                0x00405229                api_strncmp
                0x00405126                APIminimize_window
                0x00403c45                system2
                0x00403c66                system3
                0x0040468b                DialogBox
                0x004056d1                api_get_current_keyboard_responder
                0x004053c0                apiCreateProcess
                0x00404f7a                APIGetFocus
                0x00403cea                system7
                0x00403cc9                system6
                0x00405675                apiDefDialog
                0x004045fe                mbProcedure
                0x00404ef6                APICloseWindow
                0x00405c85                apiSendMessage
                0x0040560c                initializeCriticalSection
                0x00403d4d                system10
                0x0040406f                set_cursor
                0x004050fd                APImaximize_window
                0x004057fa                execve
                0x00405287                refresh_screen
                0x004058b5                apiDisplayBMP
                0x00404d97                call_gui
                0x00403d2c                system9
                0x004057ce                fork
                0x004056a8                api_set_current_keyboard_responder
                0x00405082                APIresize_window
                0x00405642                apiEndPaint
                0x0040409e                put_char
                0x00403faa                print_string
                0x0040536b                apiGetClientAreaRect
                0x00403fe0                edit_box
                0x004051f8                kill
                0x004052bd                apiReboot
                0x004040cc                apiShutDown
                0x004056fd                api_set_current_mouse_responder
                0x00405178                APIget_foregroung_window
                0x00403c87                system4
                0x00405475                apiSaveFile
                0x004052e9                apiSetCursor
                0x00403d8f                system12
                0x00403faf                vsync
                0x00403d0b                system8
                0x00405752                api_set_window_with_text_input
                0x0040502a                APIGetActiveWindow
                0x0040514f                APIupdate_window
                0x00405726                api_get_current_mouse_responder
                0x004051fd                dead_thread_collector
                0x00405412                apiStartThread
                0x00404fa6                APIKillFocus
                0x004051a4                APIset_foregroung_window
                0x0040564c                apiPutChar
 .text          0x00405d1c      0x140 status.o
                0x00405dba                update_statuts_bar
                0x00405d1c                statusInitializeStatusBar
 .text          0x00405e5c       0xa0 addrbar.o
                0x00405e5c                topbarInitializeTopBar
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405efc      0x104 00

.rdata          0x00406000      0x9f0
 .rdata         0x00406000       0x40 addrbar.o
 .rdata         0x00406040       0x40 status.o
 .rdata         0x00406080      0x3e0 api.o
 .rdata         0x00406460       0x70 stdio.o
 .rdata         0x004064d0      0x460 stdlib.o
 .rdata         0x00406930       0xc0 main.o

.data           0x004069f0     0x1610
                0x004069f0                data = .
                0x004069f0                _data = .
                0x004069f0                __data = .
 *(.data)
 .data          0x004069f0      0x460 main.o
                0x00406e30                running
 .data          0x00406e50      0x120 ctype.o
                0x00406e50                _ctype_
 .data          0x00406f70        0x0 stdlib.o
 .data          0x00406f70        0x0 stdio.o
 .data          0x00406f70        0x0 string.o
 .data          0x00406f70      0x440 api.o
 .data          0x004073b0      0x440 status.o
 .data          0x004077f0      0x440 addrbar.o
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407c30      0x3d0 00

.bss            0x00408000     0xa750
                0x00408000                bss = .
                0x00408000                _bss = .
                0x00408000                __bss = .
 *(.bss)
 .bss           0x00408000       0x30 main.o
 .bss           0x00408030        0x0 ctype.o
 .bss           0x00408030     0x8010 stdlib.o
                0x00408030                environ
 .bss           0x00410040       0x10 stdio.o
 .bss           0x00410050       0x10 string.o
 .bss           0x00410060       0x40 api.o
 .bss           0x004100a0       0x30 status.o
 .bss           0x004100d0       0x30 addrbar.o
                0x00411000                . = ALIGN (0x1000)
 *fill*         0x00410100      0xf00 00
 COMMON         0x00411000      0xe10 main.o
                0x00411000                prompt
                0x00411400                ClientAreaInfo
                0x00411410                BufferInfo
                0x00411420                stderr
                0x00411430                prompt_pos
                0x00411440                mWindow
                0x00411450                g_using_gui
                0x00411460                stdin
                0x00411470                rect
                0x00411480                prompt_max
                0x00411490                TOPBAR
                0x004114b0                CurrentWindow
                0x004114c0                prompt_err
                0x004118c0                current_semaphore
                0x004118d0                g_columns
                0x004118e0                stdout
                0x004118f0                Streams
                0x00411970                g_rows
                0x00411980                prompt_out
                0x00411d80                g_cursor_y
                0x00411d90                gWindow
                0x00411da0                CursorInfo
                0x00411db0                STATUSBAR
                0x00411dd0                prompt_status
                0x00411de0                g_char_attrib
                0x00411df0                ApplicationInfo
                0x00411e00                g_cursor_x
 COMMON         0x00411e10      0x900 stdlib.o
                0x00411e10                current_mmblock
                0x00411e20                mm_prev_pointer
                0x00411e30                heap_end
                0x00411e40                g_available_heap
                0x00411e50                heap_start
                0x00411e60                heapCount
                0x00411e70                HEAP_START
                0x00411e80                g_heap_pointer
                0x00411e90                heapList
                0x00412290                randseed
                0x004122a0                HEAP_SIZE
                0x004122b0                last_size
                0x004122c0                last_valid
                0x004122d0                mmblockList
                0x004126d0                libcHeap
                0x004126e0                Heap
                0x004126f0                mmblockCount
                0x00412700                HEAP_END
 COMMON         0x00412710       0x40 api.o
                0x00412710                messagebox_button2
                0x00412720                dialogbox_button1
                0x00412730                messagebox_button1
                0x00412740                dialogbox_button2
                0x00412750                end = .
                0x00412750                _end = .
                0x00412750                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdlib.o
LOAD stdio.o
LOAD string.o
LOAD api.o
LOAD status.o
LOAD addrbar.o
OUTPUT(TGFE.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f crt0.o
