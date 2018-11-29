
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
driverInitialized   0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
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
dialogbox_button2   0x10              api.o
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
idleError           0x10              main.o
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

.text           0x00401000     0x7000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038      0x770 main.o
                0x00401083                idleInit
                0x004014f5                TEST_PRINTF3
                0x004010a1                idleServices
                0x0040103d                driverInitialize
                0x0040110b                testtest_main
                0x00401193                TEST_PRINTF
                0x00401038                idleLoop
                0x0040143a                TEST_PRINTF2
                0x00401060                driverUninitialize
 .text          0x004017a8     0x2770 stdio.o
                0x004021ac                printf_i2hex
                0x004023de                putchar
                0x0040185d                stdio_fntos
                0x0040239a                sprintf
                0x00402b0c                feof
                0x0040221a                printf2
                0x00402c32                stdioSetCursor
                0x00402a6e                ungetc
                0x00401bbd                puts
                0x00402bea                fputc
                0x00402c88                stdioGetCursorY
                0x00402cb4                scanf
                0x00402984                fputs
                0x00402b4a                ferror
                0x004025c0                input
                0x00401afb                scroll
                0x004029f9                gets
                0x0040240a                outbyte
                0x004028a0                fflush
                0x0040290f                fprintf
                0x00402728                stdio_system_call
                0x004019c2                fopen
                0x00402c5c                stdioGetCursorX
                0x00402750                getchar
                0x004020bf                printf_atoi
                0x004017a8                stdio_atoi
                0x00402f4a                kvprintf
                0x0040277c                stdioInitialize
                0x00402aab                fgetc
                0x0040195c                fclose
                0x00402b70                fseek
                0x0040258d                _outbyte
                0x00403ed9                printf
                0x004020a4                printf3
 .text          0x00403f18      0xb40 stdlib.o
                0x0040420e                FreeHeap
                0x00403f40                rtGetHeapStart
                0x004044af                free
                0x00403f18                stdlib_system_call
                0x00404444                rand
                0x004043bb                stdlibInitMM
                0x00404218                heapInit
                0x00404949                __findenv
                0x00403f54                rtGetHeapPointer
                0x00403f5e                rtGetAvailableHeap
                0x00404461                srand
                0x0040441b                libcInitRT
                0x00403f68                heapSetLibcHeap
                0x00404a14                getenv
                0x0040446e                malloc
                0x004041fb                AllocateHeapEx
                0x0040400f                AllocateHeap
                0x004048c0                stdlib_strncmp
                0x0040491e                exit
                0x00403f4a                rtGetHeapEnd
                0x004044b4                system
 .text          0x00404a58       0xe0 ctype.o
                0x00404af2                isspace
                0x00404b18                isxdigit
                0x00404b05                isupper
                0x00404a6b                isalpha
                0x00404ab7                islower
                0x00404a58                isalnum
                0x00404aca                isprint
                0x00404aa4                isgraph
                0x00404a91                isdigit
                0x00404a7e                iscntrl
                0x00404adf                ispunct
 .text          0x00404b38      0x430 string.o
                0x00404d24                strcspn
                0x00404c87                strcat
                0x00404b38                strcmp
                0x00404cde                bzero
                0x00404e64                strtok_r
                0x00404c1a                memcpy
                0x00404bf1                memoryZeroMemory
                0x00404cb7                bcopy
                0x00404c57                strcpy
                0x00404dc4                strspn
                0x00404f39                strtok
                0x00404b93                strncmp
                0x00404cf9                strlen
 .text          0x00404f68     0x25f0 api.o
                0x004067f2                APIShowCurrentProcessInfo
                0x00407025                api_getchar
                0x0040550a                system11
                0x004055af                refresh_buffer
                0x004066d4                APISetFocus
                0x0040556d                system14
                0x00405896                apiInitBackground
                0x004065c4                APICreateWindow
                0x00406dd4                apiBeginPaint
                0x0040589b                MessageBox
                0x00406870                APIreplace_window
                0x00406e1b                apiGetSystemMetrics
                0x0040554c                system13
                0x00406c6f                apiDown
                0x00406326                dbProcedure
                0x00406969                apiExit
                0x00406d23                enterCriticalSection
                0x00406f60                gramadocore_init_execve
                0x00406bd7                apiFOpen
                0x004053c0                system1
                0x00405444                system5
                0x00406a4f                api_refresh_screen
                0x00406fa0                apiDialog
                0x00406adb                apiGetCursorY
                0x0040583f                carrega_bitmap_16x16
                0x00406d7c                exitCriticalSection
                0x00404f68                system_call
                0x00406cc9                apiUp
                0x00404f90                apiSystem
                0x00406f34                api_get_window_with_text_input
                0x004074a9                apiGetWSScreenWindow
                0x0040558e                system15
                0x00406784                APISetActiveWindow
                0x00406b33                apiSetClientAreaRect
                0x00407462                apiDrawText
                0x00406847                APIredraw_window
                0x00406b85                apiCreateThread
                0x004057db                SetNextWindowProcedure
                0x00407501                apiCreateTimer
                0x00406aaf                apiGetCursorX
                0x004057ab                chama_procedimento
                0x004063b3                call_kernel
                0x00406650                APIRegisterWindow
                0x004074d5                apiGetWSMainWindow
                0x004069c5                api_strncmp
                0x004068c2                APIminimize_window
                0x004053e1                system2
                0x00405402                system3
                0x00405e27                DialogBox
                0x00406e6d                api_get_current_keyboard_responder
                0x00406b5c                apiCreateProcess
                0x00406716                APIGetFocus
                0x00405486                system7
                0x00405465                system6
                0x00406e11                apiDefDialog
                0x00405d9a                mbProcedure
                0x00406692                APICloseWindow
                0x00407421                apiSendMessage
                0x00406da8                initializeCriticalSection
                0x004054e9                system10
                0x0040580b                set_cursor
                0x00406899                APImaximize_window
                0x00406f96                execve
                0x00406a23                refresh_screen
                0x00407051                apiDisplayBMP
                0x00406533                call_gui
                0x004054c8                system9
                0x00406f6a                fork
                0x00406e44                api_set_current_keyboard_responder
                0x0040681e                APIresize_window
                0x00406dde                apiEndPaint
                0x0040583a                put_char
                0x00405746                print_string
                0x0040752a                apiGetSysTimeInfo
                0x00406b07                apiGetClientAreaRect
                0x0040577c                edit_box
                0x00406994                kill
                0x00406a59                apiReboot
                0x00405868                apiShutDown
                0x00406e99                api_set_current_mouse_responder
                0x00406914                APIget_foregroung_window
                0x00405423                system4
                0x00406c11                apiSaveFile
                0x00406a85                apiSetCursor
                0x0040552b                system12
                0x0040574b                vsync
                0x004054a7                system8
                0x00406eee                api_set_window_with_text_input
                0x004067c6                APIGetActiveWindow
                0x004068eb                APIupdate_window
                0x00406ec2                api_get_current_mouse_responder
                0x00406999                dead_thread_collector
                0x00406bae                apiStartThread
                0x00406742                APIKillFocus
                0x00406940                APIset_foregroung_window
                0x00406de8                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407558      0xaa8 00

.rdata          0x00408000      0xe10
 .rdata         0x00408000      0x3e0 api.o
 .rdata         0x004083e0      0x460 stdlib.o
 .rdata         0x00408840      0x340 stdio.o
                0x004089e0                hex2ascii_data
 .rdata         0x00408b80      0x290 main.o

.data           0x00408e10     0x11f0
                0x00408e10                data = .
                0x00408e10                _data = .
                0x00408e10                __data = .
 *(.data)
 .data          0x00408e10        0x0 main.o
 .data          0x00408e10        0x0 stdio.o
 .data          0x00408e10        0x0 stdlib.o
 .data          0x00408e10      0x120 ctype.o
                0x00408e10                _ctype_
 .data          0x00408f30        0x0 string.o
 .data          0x00408f30      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409370      0xc90 00

.bss            0x0040a000     0xa720
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000       0x10 stdio.o
 .bss           0x0040a010     0x8010 stdlib.o
                0x0040a010                environ
 .bss           0x00412020        0x0 ctype.o
 .bss           0x00412020       0x10 string.o
 .bss           0x00412030       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xde0 main.o
                0x00413000                prompt
                0x00413400                idleStatus
                0x00413410                ClientAreaInfo
                0x00413420                BufferInfo
                0x00413430                driverInitialized
                0x00413440                stderr
                0x00413450                prompt_pos
                0x00413460                g_using_gui
                0x00413470                stdin
                0x00413480                rect
                0x00413490                prompt_max
                0x004134a0                CurrentWindow
                0x004134b0                prompt_err
                0x004138b0                current_semaphore
                0x004138c0                g_columns
                0x004138d0                stdout
                0x004138e0                Streams
                0x00413960                g_rows
                0x00413970                prompt_out
                0x00413d70                g_cursor_y
                0x00413d80                CursorInfo
                0x00413d90                prompt_status
                0x00413da0                g_char_attrib
                0x00413db0                ApplicationInfo
                0x00413dc0                idleError
                0x00413dd0                g_cursor_x
 COMMON         0x00413de0      0x900 stdlib.o
                0x00413de0                current_mmblock
                0x00413df0                mm_prev_pointer
                0x00413e00                heap_end
                0x00413e10                g_available_heap
                0x00413e20                heap_start
                0x00413e30                heapCount
                0x00413e40                HEAP_START
                0x00413e50                g_heap_pointer
                0x00413e60                heapList
                0x00414260                randseed
                0x00414270                HEAP_SIZE
                0x00414280                last_size
                0x00414290                last_valid
                0x004142a0                mmblockList
                0x004146a0                libcHeap
                0x004146b0                Heap
                0x004146c0                mmblockCount
                0x004146d0                HEAP_END
 COMMON         0x004146e0       0x40 api.o
                0x004146e0                messagebox_button2
                0x004146f0                dialogbox_button1
                0x00414700                messagebox_button1
                0x00414710                dialogbox_button2
                0x00414720                end = .
                0x00414720                _end = .
                0x00414720                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TPRINTF.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
