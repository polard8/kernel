
Allocating common symbols
Common symbol       size              file

j                   0x10              main.o
prompt              0x400             main.o
number              0x10              main.o
i                   0x10              main.o
ClientAreaInfo      0x10              api.o
BufferInfo          0x10              api.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
rect                0x10              api.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
CurrentWindow       0x10              api.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
maxrand             0x10              main.o
current_semaphore   0x10              api.o
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
c                   0x10              main.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
life                0x10              main.o
CursorInfo          0x10              api.o
dialogbox_button2   0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              api.o
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
 .text          0x00401000      0x3e0 main.o
                0x0040119b                GetResults
                0x00401391                jackpot_main
                0x00401000                app_main
                0x004012dc                jackpot_atoi
                0x00401075                Start
 .text          0x004013e0       0xe0 ctype.o
                0x0040147a                isspace
                0x004014a0                isxdigit
                0x0040148d                isupper
                0x004013f3                isalpha
                0x0040143f                islower
                0x004013e0                isalnum
                0x00401452                isprint
                0x0040142c                isgraph
                0x00401419                isdigit
                0x00401406                iscntrl
                0x00401467                ispunct
 .text          0x004014c0     0x2770 stdio.o
                0x00401ec4                printf_i2hex
                0x004020f6                putchar
                0x00401575                stdio_fntos
                0x004020b2                sprintf
                0x00402824                feof
                0x00401f32                printf2
                0x0040294a                stdioSetCursor
                0x00402786                ungetc
                0x004018d5                puts
                0x00402902                fputc
                0x004029a0                stdioGetCursorY
                0x004029cc                scanf
                0x0040269c                fputs
                0x00402862                ferror
                0x004022d8                input
                0x00401813                scroll
                0x00402711                gets
                0x00402122                outbyte
                0x004025b8                fflush
                0x00402627                fprintf
                0x00402440                stdio_system_call
                0x004016da                fopen
                0x00402974                stdioGetCursorX
                0x00402468                getchar
                0x00401dd7                printf_atoi
                0x004014c0                stdio_atoi
                0x00402c62                kvprintf
                0x00402494                stdioInitialize
                0x004027c3                fgetc
                0x00401674                fclose
                0x00402888                fseek
                0x004022a5                _outbyte
                0x00403bf1                printf
                0x00401dbc                printf3
 .text          0x00403c30      0xb40 stdlib.o
                0x00403f26                FreeHeap
                0x00403c58                rtGetHeapStart
                0x004041c7                free
                0x00403c30                stdlib_system_call
                0x0040415c                rand
                0x004040d3                stdlibInitMM
                0x00403f30                heapInit
                0x00404661                __findenv
                0x00403c6c                rtGetHeapPointer
                0x00403c76                rtGetAvailableHeap
                0x00404179                srand
                0x00404133                libcInitRT
                0x00403c80                heapSetLibcHeap
                0x0040472c                getenv
                0x00404186                malloc
                0x00403f13                AllocateHeapEx
                0x00403d27                AllocateHeap
                0x004045d8                stdlib_strncmp
                0x00404636                exit
                0x00403c62                rtGetHeapEnd
                0x004041cc                system
 .text          0x00404770      0x430 string.o
                0x0040495c                strcspn
                0x004048bf                strcat
                0x00404770                strcmp
                0x00404916                bzero
                0x00404a9c                strtok_r
                0x00404852                memcpy
                0x00404829                memoryZeroMemory
                0x004048ef                bcopy
                0x0040488f                strcpy
                0x004049fc                strspn
                0x00404b71                strtok
                0x004047cb                strncmp
                0x00404931                strlen
 .text          0x00404ba0       0x70 time.o
                0x00404bda                time_system_call
                0x00404ba0                time
 .text          0x00404c10     0x25f0 api.o
                0x0040649a                APIShowCurrentProcessInfo
                0x00406ccd                api_getchar
                0x004051b2                system11
                0x00405257                refresh_buffer
                0x0040637c                APISetFocus
                0x00405215                system14
                0x0040553e                apiInitBackground
                0x0040626c                APICreateWindow
                0x00406a7c                apiBeginPaint
                0x00405543                MessageBox
                0x00406518                APIreplace_window
                0x00406ac3                apiGetSystemMetrics
                0x004051f4                system13
                0x00406917                apiDown
                0x00405fce                dbProcedure
                0x00406611                apiExit
                0x004069cb                enterCriticalSection
                0x00406c08                gramadocore_init_execve
                0x0040687f                apiFOpen
                0x00405068                system1
                0x004050ec                system5
                0x004066f7                api_refresh_screen
                0x00406c48                apiDialog
                0x00406783                apiGetCursorY
                0x004054e7                carrega_bitmap_16x16
                0x00406a24                exitCriticalSection
                0x00404c10                system_call
                0x00406971                apiUp
                0x00404c38                apiSystem
                0x00406bdc                api_get_window_with_text_input
                0x00407151                apiGetWSScreenWindow
                0x00405236                system15
                0x0040642c                APISetActiveWindow
                0x004067db                apiSetClientAreaRect
                0x0040710a                apiDrawText
                0x004064ef                APIredraw_window
                0x0040682d                apiCreateThread
                0x00405483                SetNextWindowProcedure
                0x004071a9                apiCreateTimer
                0x00406757                apiGetCursorX
                0x00405453                chama_procedimento
                0x0040605b                call_kernel
                0x004062f8                APIRegisterWindow
                0x0040717d                apiGetWSMainWindow
                0x0040666d                api_strncmp
                0x0040656a                APIminimize_window
                0x00405089                system2
                0x004050aa                system3
                0x00405acf                DialogBox
                0x00406b15                api_get_current_keyboard_responder
                0x00406804                apiCreateProcess
                0x004063be                APIGetFocus
                0x0040512e                system7
                0x0040510d                system6
                0x00406ab9                apiDefDialog
                0x00405a42                mbProcedure
                0x0040633a                APICloseWindow
                0x004070c9                apiSendMessage
                0x00406a50                initializeCriticalSection
                0x00405191                system10
                0x004054b3                set_cursor
                0x00406541                APImaximize_window
                0x00406c3e                execve
                0x004066cb                refresh_screen
                0x00406cf9                apiDisplayBMP
                0x004061db                call_gui
                0x00405170                system9
                0x00406c12                fork
                0x00406aec                api_set_current_keyboard_responder
                0x004064c6                APIresize_window
                0x00406a86                apiEndPaint
                0x004054e2                put_char
                0x004053ee                print_string
                0x004071d2                apiGetSysTimeInfo
                0x004067af                apiGetClientAreaRect
                0x00405424                edit_box
                0x0040663c                kill
                0x00406701                apiReboot
                0x00405510                apiShutDown
                0x00406b41                api_set_current_mouse_responder
                0x004065bc                APIget_foregroung_window
                0x004050cb                system4
                0x004068b9                apiSaveFile
                0x0040672d                apiSetCursor
                0x004051d3                system12
                0x004053f3                vsync
                0x0040514f                system8
                0x00406b96                api_set_window_with_text_input
                0x0040646e                APIGetActiveWindow
                0x00406593                APIupdate_window
                0x00406b6a                api_get_current_mouse_responder
                0x00406641                dead_thread_collector
                0x00406856                apiStartThread
                0x004063ea                APIKillFocus
                0x004065e8                APIset_foregroung_window
                0x00406a90                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407200      0xe00 00

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
 .data          0x00408e10      0x120 ctype.o
                0x00408e10                _ctype_
 .data          0x00408f30        0x0 stdio.o
 .data          0x00408f30        0x0 stdlib.o
 .data          0x00408f30        0x0 string.o
 .data          0x00408f30        0x0 time.o
 .data          0x00408f30      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409370      0xc90 00

.bss            0x0040a000     0xa750
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000        0x0 ctype.o
 .bss           0x0040a000       0x10 stdio.o
 .bss           0x0040a010     0x8010 stdlib.o
                0x0040a010                environ
 .bss           0x00412020       0x10 string.o
 .bss           0x00412030        0x0 time.o
 .bss           0x00412030       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xda0 main.o
                0x00413000                j
                0x00413010                prompt
                0x00413410                number
                0x00413420                i
                0x00413430                stderr
                0x00413440                prompt_pos
                0x00413450                g_using_gui
                0x00413460                stdin
                0x00413470                prompt_max
                0x00413480                prompt_err
                0x00413880                maxrand
                0x00413890                g_columns
                0x004138a0                stdout
                0x004138b0                Streams
                0x00413930                g_rows
                0x00413940                prompt_out
                0x00413d40                c
                0x00413d50                g_cursor_y
                0x00413d60                life
                0x00413d70                prompt_status
                0x00413d80                g_char_attrib
                0x00413d90                g_cursor_x
 COMMON         0x00413da0      0x900 stdlib.o
                0x00413da0                current_mmblock
                0x00413db0                mm_prev_pointer
                0x00413dc0                heap_end
                0x00413dd0                g_available_heap
                0x00413de0                heap_start
                0x00413df0                heapCount
                0x00413e00                HEAP_START
                0x00413e10                g_heap_pointer
                0x00413e20                heapList
                0x00414220                randseed
                0x00414230                HEAP_SIZE
                0x00414240                last_size
                0x00414250                last_valid
                0x00414260                mmblockList
                0x00414660                libcHeap
                0x00414670                Heap
                0x00414680                mmblockCount
                0x00414690                HEAP_END
 COMMON         0x004146a0       0xb0 api.o
                0x004146a0                ClientAreaInfo
                0x004146b0                BufferInfo
                0x004146c0                messagebox_button2
                0x004146d0                rect
                0x004146e0                CurrentWindow
                0x004146f0                current_semaphore
                0x00414700                dialogbox_button1
                0x00414710                messagebox_button1
                0x00414720                CursorInfo
                0x00414730                dialogbox_button2
                0x00414740                ApplicationInfo
                0x00414750                end = .
                0x00414750                _end = .
                0x00414750                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
OUTPUT(JACKPOT.BIN pe-i386)
