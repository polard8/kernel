
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

.text           0x00401000     0x6000
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
 .text          0x0040154c      0xb40 stdlib.o
                0x00401842                FreeHeap
                0x00401574                rtGetHeapStart
                0x00401ae3                free
                0x0040154c                stdlib_system_call
                0x00401a78                rand
                0x004019ef                stdlibInitMM
                0x0040184c                heapInit
                0x00401f7d                __findenv
                0x00401588                rtGetHeapPointer
                0x00401592                rtGetAvailableHeap
                0x00401a95                srand
                0x00401a4f                libcInitRT
                0x0040159c                heapSetLibcHeap
                0x00402048                getenv
                0x00401aa2                malloc
                0x0040182f                AllocateHeapEx
                0x00401643                AllocateHeap
                0x00401ef4                stdlib_strncmp
                0x00401f52                exit
                0x0040157e                rtGetHeapEnd
                0x00401ae8                system
 .text          0x0040208c     0x13f0 stdio.o
                0x00402932                putchar
                0x0040208c                stdio_fntos
                0x004028ee                sprintf
                0x00403060                feof
                0x00403186                stdioSetCursor
                0x00402fc2                ungetc
                0x004023ec                puts
                0x0040313e                fputc
                0x004031dc                stdioGetCursorY
                0x004032bd                scanf
                0x00402ed8                fputs
                0x0040309e                ferror
                0x00402b14                input
                0x0040232a                scroll
                0x00402f4d                gets
                0x0040295e                outbyte
                0x00402df4                fflush
                0x00402e63                fprintf
                0x00402c7c                stdio_system_call
                0x004021f1                fopen
                0x004031b0                stdioGetCursorX
                0x00402ca4                getchar
                0x00403208                stdio_atoi
                0x00402cd0                stdioInitialize
                0x00402fff                fgetc
                0x0040218b                fclose
                0x004030c4                fseek
                0x00402ae1                _outbyte
                0x004028d3                printf
 .text          0x0040347c      0x430 string.o
                0x00403668                strcspn
                0x004035cb                strcat
                0x0040347c                strcmp
                0x00403622                bzero
                0x004037a8                strtok_r
                0x0040355e                memcpy
                0x00403535                memoryZeroMemory
                0x004035fb                bcopy
                0x0040359b                strcpy
                0x00403708                strspn
                0x0040387d                strtok
                0x004034d7                strncmp
                0x0040363d                strlen
 .text          0x004038ac     0x2630 api.o
                0x0040516f                APIShowCurrentProcessInfo
                0x004059a2                api_getchar
                0x00403e4e                system11
                0x00403ef3                refresh_buffer
                0x00405018                APISetFocus
                0x00403eb1                system14
                0x004041da                apiInitBackground
                0x00404f08                APICreateWindow
                0x00405751                apiBeginPaint
                0x004041df                MessageBox
                0x004051ed                APIreplace_window
                0x00405798                apiGetSystemMetrics
                0x00403e90                system13
                0x004055ec                apiDown
                0x00404c6a                dbProcedure
                0x004052e6                apiExit
                0x004056a0                enterCriticalSection
                0x004058dd                gramadocore_init_execve
                0x00405554                apiFOpen
                0x00403d04                system1
                0x00403d88                system5
                0x004053cc                api_refresh_screen
                0x0040591d                apiDialog
                0x00405458                apiGetCursorY
                0x00404183                carrega_bitmap_16x16
                0x004056f9                exitCriticalSection
                0x004038ac                system_call
                0x00405646                apiUp
                0x004038d4                apiSystem
                0x004058b1                api_get_window_with_text_input
                0x00405e26                apiGetWSScreenWindow
                0x00403ed2                system15
                0x004050ee                APISetActiveWindow
                0x004054b0                apiSetClientAreaRect
                0x00405ddf                apiDrawText
                0x004051c4                APIredraw_window
                0x00405502                apiCreateThread
                0x0040411f                SetNextWindowProcedure
                0x00405e7e                apiCreateTimer
                0x0040542c                apiGetCursorX
                0x004040ef                chama_procedimento
                0x00404cf7                call_kernel
                0x00405e52                apiGetWSMainWindow
                0x00404f94                APIRegisterWindow
                0x00405342                api_strncmp
                0x0040523f                APIminimize_window
                0x00403d25                system2
                0x00403d46                system3
                0x0040476b                DialogBox
                0x004057ea                api_get_current_keyboard_responder
                0x004054d9                apiCreateProcess
                0x0040506d                APIGetFocus
                0x00403dca                system7
                0x00403da9                system6
                0x0040578e                apiDefDialog
                0x004046de                mbProcedure
                0x00404fd6                APICloseWindow
                0x00405d9e                apiSendMessage
                0x00405725                initializeCriticalSection
                0x00403e2d                system10
                0x0040414f                set_cursor
                0x00405216                APImaximize_window
                0x00405913                execve
                0x004053a0                refresh_screen
                0x004059ce                apiDisplayBMP
                0x00404e77                call_gui
                0x00403e0c                system9
                0x004058e7                fork
                0x004057c1                api_set_current_keyboard_responder
                0x0040519b                APIresize_window
                0x0040575b                apiEndPaint
                0x0040417e                put_char
                0x0040408a                print_string
                0x00405ea7                apiGetSysTimeInfo
                0x00405484                apiGetClientAreaRect
                0x004040c0                edit_box
                0x00405311                kill
                0x004053d6                apiReboot
                0x004041ac                apiShutDown
                0x00405816                api_set_current_mouse_responder
                0x00405291                APIget_foregroung_window
                0x00403d67                system4
                0x0040558e                apiSaveFile
                0x00405402                apiSetCursor
                0x00403e6f                system12
                0x0040408f                vsync
                0x00403deb                system8
                0x0040586b                api_set_window_with_text_input
                0x00405143                APIGetActiveWindow
                0x00405268                APIupdate_window
                0x0040583f                api_get_current_mouse_responder
                0x00405316                dead_thread_collector
                0x0040552b                apiStartThread
                0x00405099                APIKillFocus
                0x004052bd                APIset_foregroung_window
                0x00405765                apiPutChar
 .text          0x00405edc      0x140 status.o
                0x00405f7a                update_statuts_bar
                0x00405edc                statusInitializeStatusBar
 .text          0x0040601c       0xa0 addrbar.o
                0x0040601c                topbarInitializeTopBar
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x004060bc      0xf44 00

.rdata          0x00407000      0xa50
 .rdata         0x00407000       0x40 addrbar.o
 .rdata         0x00407040       0x40 status.o
 .rdata         0x00407080      0x3e0 api.o
 .rdata         0x00407460       0xd0 stdio.o
 .rdata         0x00407530      0x460 stdlib.o
 .rdata         0x00407990       0xc0 main.o

.data           0x00407a50     0x15b0
                0x00407a50                data = .
                0x00407a50                _data = .
                0x00407a50                __data = .
 *(.data)
 .data          0x00407a50      0x460 main.o
                0x00407e90                running
 .data          0x00407eb0      0x120 ctype.o
                0x00407eb0                _ctype_
 .data          0x00407fd0        0x0 stdlib.o
 .data          0x00407fd0        0x0 stdio.o
 .data          0x00407fd0        0x0 string.o
 .data          0x00407fd0      0x440 api.o
 .data          0x00408410      0x440 status.o
 .data          0x00408850      0x440 addrbar.o
                0x00409000                . = ALIGN (0x1000)
 *fill*         0x00408c90      0x370 00

.bss            0x00409000     0xa750
                0x00409000                bss = .
                0x00409000                _bss = .
                0x00409000                __bss = .
 *(.bss)
 .bss           0x00409000       0x30 main.o
 .bss           0x00409030        0x0 ctype.o
 .bss           0x00409030     0x8010 stdlib.o
                0x00409030                environ
 .bss           0x00411040       0x10 stdio.o
 .bss           0x00411050       0x10 string.o
 .bss           0x00411060       0x40 api.o
 .bss           0x004110a0       0x30 status.o
 .bss           0x004110d0       0x30 addrbar.o
                0x00412000                . = ALIGN (0x1000)
 *fill*         0x00411100      0xf00 00
 COMMON         0x00412000      0xe10 main.o
                0x00412000                prompt
                0x00412400                ClientAreaInfo
                0x00412410                BufferInfo
                0x00412420                stderr
                0x00412430                prompt_pos
                0x00412440                mWindow
                0x00412450                g_using_gui
                0x00412460                stdin
                0x00412470                rect
                0x00412480                prompt_max
                0x00412490                TOPBAR
                0x004124b0                CurrentWindow
                0x004124c0                prompt_err
                0x004128c0                current_semaphore
                0x004128d0                g_columns
                0x004128e0                stdout
                0x004128f0                Streams
                0x00412970                g_rows
                0x00412980                prompt_out
                0x00412d80                g_cursor_y
                0x00412d90                gWindow
                0x00412da0                CursorInfo
                0x00412db0                STATUSBAR
                0x00412dd0                prompt_status
                0x00412de0                g_char_attrib
                0x00412df0                ApplicationInfo
                0x00412e00                g_cursor_x
 COMMON         0x00412e10      0x900 stdlib.o
                0x00412e10                current_mmblock
                0x00412e20                mm_prev_pointer
                0x00412e30                heap_end
                0x00412e40                g_available_heap
                0x00412e50                heap_start
                0x00412e60                heapCount
                0x00412e70                HEAP_START
                0x00412e80                g_heap_pointer
                0x00412e90                heapList
                0x00413290                randseed
                0x004132a0                HEAP_SIZE
                0x004132b0                last_size
                0x004132c0                last_valid
                0x004132d0                mmblockList
                0x004136d0                libcHeap
                0x004136e0                Heap
                0x004136f0                mmblockCount
                0x00413700                HEAP_END
 COMMON         0x00413710       0x40 api.o
                0x00413710                messagebox_button2
                0x00413720                dialogbox_button1
                0x00413730                messagebox_button1
                0x00413740                dialogbox_button2
                0x00413750                end = .
                0x00413750                _end = .
                0x00413750                __end = .
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
