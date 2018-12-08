
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
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
 *(.text)
 .text          0x00401000      0x130 main.o
                0x00401000                app_test
 .text          0x00401130     0x2600 api.o
                0x004029a0                APIShowCurrentProcessInfo
                0x004031d3                api_getchar
                0x004016d2                system11
                0x00401777                refresh_buffer
                0x00402882                APISetFocus
                0x00401735                system14
                0x00401a5e                apiInitBackground
                0x00402772                APICreateWindow
                0x00402f82                apiBeginPaint
                0x00401a63                MessageBox
                0x00402a1e                APIreplace_window
                0x00402fc9                apiGetSystemMetrics
                0x00401714                system13
                0x00402e1d                apiDown
                0x004024d4                dbProcedure
                0x00402b17                apiExit
                0x00402ed1                enterCriticalSection
                0x0040310e                gramadocore_init_execve
                0x00402d85                apiFOpen
                0x00403701                apiShowWindow
                0x00401588                system1
                0x0040160c                system5
                0x00402bfd                api_refresh_screen
                0x0040314e                apiDialog
                0x00402c89                apiGetCursorY
                0x00401a07                carrega_bitmap_16x16
                0x00402f2a                exitCriticalSection
                0x00401130                system_call
                0x00402e77                apiUp
                0x00401158                apiSystem
                0x004030e2                api_get_window_with_text_input
                0x00403657                apiGetWSScreenWindow
                0x00401756                system15
                0x00402932                APISetActiveWindow
                0x00402ce1                apiSetClientAreaRect
                0x00403610                apiDrawText
                0x004029f5                APIredraw_window
                0x00402d33                apiCreateThread
                0x004019a3                SetNextWindowProcedure
                0x004036af                apiCreateTimer
                0x00402c5d                apiGetCursorX
                0x00401973                chama_procedimento
                0x00402561                call_kernel
                0x00403683                apiGetWSMainWindow
                0x004027fe                APIRegisterWindow
                0x00402b73                api_strncmp
                0x00402a70                APIminimize_window
                0x004015a9                system2
                0x004015ca                system3
                0x00401fe2                DialogBox
                0x0040301b                api_get_current_keyboard_responder
                0x00402d0a                apiCreateProcess
                0x004028c4                APIGetFocus
                0x0040164e                system7
                0x0040162d                system6
                0x00402fbf                apiDefDialog
                0x00401f55                mbProcedure
                0x00402840                APICloseWindow
                0x004035cf                apiSendMessage
                0x00402f56                initializeCriticalSection
                0x004016b1                system10
                0x004019d3                set_cursor
                0x00402a47                APImaximize_window
                0x00403144                execve
                0x00402bd1                refresh_screen
                0x004031ff                apiDisplayBMP
                0x004026e1                call_gui
                0x00401690                system9
                0x00403118                fork
                0x00402ff2                api_set_current_keyboard_responder
                0x004029cc                APIresize_window
                0x00402f8c                apiEndPaint
                0x00401a02                put_char
                0x0040190e                print_string
                0x004036d8                apiGetSysTimeInfo
                0x00402cb5                apiGetClientAreaRect
                0x00401944                edit_box
                0x00402b42                kill
                0x00402c07                apiReboot
                0x00401a30                apiShutDown
                0x00403047                api_set_current_mouse_responder
                0x00402ac2                APIget_foregroung_window
                0x004015eb                system4
                0x00402dbf                apiSaveFile
                0x00402c33                apiSetCursor
                0x004016f3                system12
                0x00401913                vsync
                0x0040166f                system8
                0x0040309c                api_set_window_with_text_input
                0x00402974                APIGetActiveWindow
                0x00402a99                APIupdate_window
                0x00403070                api_get_current_mouse_responder
                0x00402b47                dead_thread_collector
                0x00402d5c                apiStartThread
                0x004028f0                APIKillFocus
                0x00402aee                APIset_foregroung_window
                0x00402f96                apiPutChar
 .text          0x00403730     0x2a10 stdio.o
                0x0040413d                printf_i2hex
                0x0040436f                putchar
                0x004037e5                stdio_fntos
                0x0040432b                sprintf
                0x00404be8                feof
                0x004041ab                printf2
                0x00404d0e                stdioSetCursor
                0x00404afd                ungetc
                0x00406104                rewind
                0x00403b4e                puts
                0x00404cc6                fputc
                0x00404d64                stdioGetCursorY
                0x00404d90                scanf
                0x004049fb                fputs
                0x00404c26                ferror
                0x00404551                input
                0x00403a8c                scroll
                0x00404a70                gets
                0x0040439b                outbyte
                0x00404b64                fileno
                0x004048f4                fflush
                0x00404986                fprintf
                0x004060c2                stderr_printf
                0x004046b9                stdio_system_call
                0x0040394a                fopen
                0x00404d38                stdioGetCursorX
                0x004046e1                getchar
                0x00404050                printf_atoi
                0x00403730                stdio_atoi
                0x00405040                kvprintf
                0x00406093                stdout_printf
                0x0040470d                stdioInitialize
                0x00404b87                fgetc
                0x004038e4                fclose
                0x00404c4c                fseek
                0x004060f1                perror
                0x0040451e                _outbyte
                0x00404b3a                ftell
                0x00405fcf                printf
                0x00404035                printf3
                0x00406007                vfprintf
 .text          0x00406140      0xc60 stdlib.o
                0x00406436                FreeHeap
                0x00406168                rtGetHeapStart
                0x00406743                free
                0x00406140                stdlib_system_call
                0x0040666c                rand
                0x004065e3                stdlibInitMM
                0x00406440                heapInit
                0x00406bdd                __findenv
                0x0040617c                rtGetHeapPointer
                0x00406186                rtGetAvailableHeap
                0x00406689                srand
                0x00406cdd                atoi
                0x00406643                libcInitRT
                0x00406190                heapSetLibcHeap
                0x004066c1                stdlib_die
                0x00406ca8                getenv
                0x00406702                malloc
                0x00406423                AllocateHeapEx
                0x00406237                AllocateHeap
                0x00406b54                stdlib_strncmp
                0x00406696                xmalloc
                0x00406bb2                exit
                0x00406172                rtGetHeapEnd
                0x00406748                system
 .text          0x00406da0      0x430 string.o
                0x00406f8c                strcspn
                0x00406eef                strcat
                0x00406da0                strcmp
                0x00406f46                bzero
                0x004070cc                strtok_r
                0x00406e82                memcpy
                0x00406e59                memoryZeroMemory
                0x00406f1f                bcopy
                0x00406ebf                strcpy
                0x0040702c                strspn
                0x004071a1                strtok
                0x00406dfb                strncmp
                0x00406f61                strlen
 .text          0x004071d0        0x0 ctype.o
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004071d0      0xe30 00

.rdata          0x00408000      0xd00
 .rdata         0x00408000      0x100 ctype.o
                0x00408000                _ctype
 .rdata         0x00408100      0x480 stdlib.o
 .rdata         0x00408580      0x380 stdio.o
                0x00408760                hex2ascii_data
 .rdata         0x00408900      0x3a0 api.o
 .rdata         0x00408ca0       0x60 main.o

.data           0x00408d00     0x1300
                0x00408d00                data = .
                0x00408d00                _data = .
                0x00408d00                __data = .
 *(.data)
 .data          0x00408d00      0x440 main.o
 .data          0x00409140      0x440 api.o
 .data          0x00409580        0x0 stdio.o
 .data          0x00409580        0x0 stdlib.o
 .data          0x00409580        0x0 string.o
 .data          0x00409580        0x0 ctype.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409580      0xa80 00

.bss            0x0040a000     0xa6f0
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000       0x40 api.o
 .bss           0x0040a040       0x10 stdio.o
 .bss           0x0040a050     0x8010 stdlib.o
                0x0040a050                environ
 .bss           0x00412060       0x10 string.o
 .bss           0x00412070        0x0 ctype.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xdb0 main.o
                0x00413000                prompt
                0x00413400                ClientAreaInfo
                0x00413410                BufferInfo
                0x00413420                stderr
                0x00413430                prompt_pos
                0x00413440                g_using_gui
                0x00413450                stdin
                0x00413460                rect
                0x00413470                prompt_max
                0x00413480                CurrentWindow
                0x00413490                prompt_err
                0x00413890                current_semaphore
                0x004138a0                g_columns
                0x004138b0                stdout
                0x004138c0                Streams
                0x00413940                g_rows
                0x00413950                prompt_out
                0x00413d50                g_cursor_y
                0x00413d60                CursorInfo
                0x00413d70                prompt_status
                0x00413d80                g_char_attrib
                0x00413d90                ApplicationInfo
                0x00413da0                g_cursor_x
 COMMON         0x00413db0       0x40 api.o
                0x00413db0                messagebox_button2
                0x00413dc0                dialogbox_button1
                0x00413dd0                messagebox_button1
                0x00413de0                dialogbox_button2
 COMMON         0x00413df0      0x900 stdlib.o
                0x00413df0                current_mmblock
                0x00413e00                mm_prev_pointer
                0x00413e10                heap_end
                0x00413e20                g_available_heap
                0x00413e30                heap_start
                0x00413e40                heapCount
                0x00413e50                HEAP_START
                0x00413e60                g_heap_pointer
                0x00413e70                heapList
                0x00414270                randseed
                0x00414280                HEAP_SIZE
                0x00414290                last_size
                0x004142a0                last_valid
                0x004142b0                mmblockList
                0x004146b0                libcHeap
                0x004146c0                Heap
                0x004146d0                mmblockCount
                0x004146e0                HEAP_END
                0x004146f0                end = .
                0x004146f0                _end = .
                0x004146f0                __end = .
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD ctype.o
OUTPUT(TMETRICS.BIN pe-i386)
