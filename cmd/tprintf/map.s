
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
 .text          0x004017a8     0x2a00 stdio.o
                0x004021b5                printf_i2hex
                0x004023e7                putchar
                0x0040185d                stdio_fntos
                0x004023a3                sprintf
                0x00402c48                feof
                0x00402223                printf2
                0x00402d6e                stdioSetCursor
                0x00402b5d                ungetc
                0x00404164                rewind
                0x00401bc6                puts
                0x00402d26                fputc
                0x00402dc4                stdioGetCursorY
                0x00402df0                scanf
                0x00402a73                fputs
                0x00402c86                ferror
                0x004025c9                input
                0x00401b04                scroll
                0x00402ae8                gets
                0x00402413                outbyte
                0x00402bc4                fileno
                0x0040296c                fflush
                0x004029fe                fprintf
                0x00404122                stderr_printf
                0x00402731                stdio_system_call
                0x004019c2                fopen
                0x00402d98                stdioGetCursorX
                0x00402759                getchar
                0x004020c8                printf_atoi
                0x004017a8                stdio_atoi
                0x004030a0                kvprintf
                0x004040f3                stdout_printf
                0x00402785                stdioInitialize
                0x00402be7                fgetc
                0x0040195c                fclose
                0x00402cac                fseek
                0x00404151                perror
                0x00402596                _outbyte
                0x00402b9a                ftell
                0x0040402f                printf
                0x004020ad                printf3
                0x00404067                vfprintf
 .text          0x004041a8      0xc60 stdlib.o
                0x0040449e                FreeHeap
                0x004041d0                rtGetHeapStart
                0x004047ab                free
                0x004041a8                stdlib_system_call
                0x004046d4                rand
                0x0040464b                stdlibInitMM
                0x004044a8                heapInit
                0x00404c45                __findenv
                0x004041e4                rtGetHeapPointer
                0x004041ee                rtGetAvailableHeap
                0x004046f1                srand
                0x00404d45                atoi
                0x004046ab                libcInitRT
                0x004041f8                heapSetLibcHeap
                0x00404729                stdlib_die
                0x00404d10                getenv
                0x0040476a                malloc
                0x0040448b                AllocateHeapEx
                0x0040429f                AllocateHeap
                0x00404bbc                stdlib_strncmp
                0x004046fe                xmalloc
                0x00404c1a                exit
                0x004041da                rtGetHeapEnd
                0x004047b0                system
 .text          0x00404e08        0x0 ctype.o
 .text          0x00404e08      0x430 string.o
                0x00404ff4                strcspn
                0x00404f57                strcat
                0x00404e08                strcmp
                0x00404fae                bzero
                0x00405134                strtok_r
                0x00404eea                memcpy
                0x00404ec1                memoryZeroMemory
                0x00404f87                bcopy
                0x00404f27                strcpy
                0x00405094                strspn
                0x00405209                strtok
                0x00404e63                strncmp
                0x00404fc9                strlen
 .text          0x00405238     0x2600 api.o
                0x00406aa8                APIShowCurrentProcessInfo
                0x004072db                api_getchar
                0x004057da                system11
                0x0040587f                refresh_buffer
                0x0040698a                APISetFocus
                0x0040583d                system14
                0x00405b66                apiInitBackground
                0x0040687a                APICreateWindow
                0x0040708a                apiBeginPaint
                0x00405b6b                MessageBox
                0x00406b26                APIreplace_window
                0x004070d1                apiGetSystemMetrics
                0x0040581c                system13
                0x00406f25                apiDown
                0x004065dc                dbProcedure
                0x00406c1f                apiExit
                0x00406fd9                enterCriticalSection
                0x00407216                gramadocore_init_execve
                0x00406e8d                apiFOpen
                0x00407809                apiShowWindow
                0x00405690                system1
                0x00405714                system5
                0x00406d05                api_refresh_screen
                0x00407256                apiDialog
                0x00406d91                apiGetCursorY
                0x00405b0f                carrega_bitmap_16x16
                0x00407032                exitCriticalSection
                0x00405238                system_call
                0x00406f7f                apiUp
                0x00405260                apiSystem
                0x004071ea                api_get_window_with_text_input
                0x0040775f                apiGetWSScreenWindow
                0x0040585e                system15
                0x00406a3a                APISetActiveWindow
                0x00406de9                apiSetClientAreaRect
                0x00407718                apiDrawText
                0x00406afd                APIredraw_window
                0x00406e3b                apiCreateThread
                0x00405aab                SetNextWindowProcedure
                0x004077b7                apiCreateTimer
                0x00406d65                apiGetCursorX
                0x00405a7b                chama_procedimento
                0x00406669                call_kernel
                0x00406906                APIRegisterWindow
                0x0040778b                apiGetWSMainWindow
                0x00406c7b                api_strncmp
                0x00406b78                APIminimize_window
                0x004056b1                system2
                0x004056d2                system3
                0x004060ea                DialogBox
                0x00407123                api_get_current_keyboard_responder
                0x00406e12                apiCreateProcess
                0x004069cc                APIGetFocus
                0x00405756                system7
                0x00405735                system6
                0x004070c7                apiDefDialog
                0x0040605d                mbProcedure
                0x00406948                APICloseWindow
                0x004076d7                apiSendMessage
                0x0040705e                initializeCriticalSection
                0x004057b9                system10
                0x00405adb                set_cursor
                0x00406b4f                APImaximize_window
                0x0040724c                execve
                0x00406cd9                refresh_screen
                0x00407307                apiDisplayBMP
                0x004067e9                call_gui
                0x00405798                system9
                0x00407220                fork
                0x004070fa                api_set_current_keyboard_responder
                0x00406ad4                APIresize_window
                0x00407094                apiEndPaint
                0x00405b0a                put_char
                0x00405a16                print_string
                0x004077e0                apiGetSysTimeInfo
                0x00406dbd                apiGetClientAreaRect
                0x00405a4c                edit_box
                0x00406c4a                kill
                0x00406d0f                apiReboot
                0x00405b38                apiShutDown
                0x0040714f                api_set_current_mouse_responder
                0x00406bca                APIget_foregroung_window
                0x004056f3                system4
                0x00406ec7                apiSaveFile
                0x00406d3b                apiSetCursor
                0x004057fb                system12
                0x00405a1b                vsync
                0x00405777                system8
                0x004071a4                api_set_window_with_text_input
                0x00406a7c                APIGetActiveWindow
                0x00406ba1                APIupdate_window
                0x00407178                api_get_current_mouse_responder
                0x00406c4f                dead_thread_collector
                0x00406e64                apiStartThread
                0x004069f8                APIKillFocus
                0x00406bf6                APIset_foregroung_window
                0x0040709e                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407838      0x7c8 00

.rdata          0x00408000      0xf30
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x290 main.o

.data           0x00408f30     0x10d0
                0x00408f30                data = .
                0x00408f30                _data = .
                0x00408f30                __data = .
 *(.data)
 .data          0x00408f30        0x0 main.o
 .data          0x00408f30        0x0 stdio.o
 .data          0x00408f30        0x0 stdlib.o
 .data          0x00408f30        0x0 ctype.o
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
