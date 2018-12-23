
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
POS_BUFFER          0x80              main.o
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
 .text          0x00401038      0xca0 main.o
                0x00401360                idleInit
                0x00401038                newNode
                0x004010ad                exibirEmOrdem
                0x004010ec                exibirPreOrdem
                0x004011a6                insert
                0x00401a22                TEST_PRINTF3
                0x00401417                pop
                0x004014e3                my_isdigit
                0x0040137e                idleServices
                0x0040131a                driverInitialize
                0x004013e8                push
                0x004015f1                testtest_main
                0x004016c0                TEST_PRINTF
                0x0040150e                eval
                0x00401315                idleLoop
                0x0040106e                inorder
                0x00401967                TEST_PRINTF2
                0x0040133d                driverUninitialize
                0x00401450                oper
                0x0040121e                bst_main
                0x0040112b                exibirPosOrdem
 .text          0x00401cd8     0x2a10 stdio.o
                0x004026e5                printf_i2hex
                0x00402917                putchar
                0x00401d8d                stdio_fntos
                0x004028d3                sprintf
                0x00403190                feof
                0x00402753                printf2
                0x004032b6                stdioSetCursor
                0x004030a5                ungetc
                0x004046ac                rewind
                0x004020f6                puts
                0x0040326e                fputc
                0x0040330c                stdioGetCursorY
                0x00403338                scanf
                0x00402fa3                fputs
                0x004031ce                ferror
                0x00402af9                input
                0x00402034                scroll
                0x00403018                gets
                0x00402943                outbyte
                0x0040310c                fileno
                0x00402e9c                fflush
                0x00402f2e                fprintf
                0x0040466a                stderr_printf
                0x00402c61                stdio_system_call
                0x00401ef2                fopen
                0x004032e0                stdioGetCursorX
                0x00402c89                getchar
                0x004025f8                printf_atoi
                0x00401cd8                stdio_atoi
                0x004035e8                kvprintf
                0x0040463b                stdout_printf
                0x00402cb5                stdioInitialize
                0x0040312f                fgetc
                0x00401e8c                fclose
                0x004031f4                fseek
                0x00404699                perror
                0x00402ac6                _outbyte
                0x004030e2                ftell
                0x00404577                printf
                0x004025dd                printf3
                0x004045af                vfprintf
 .text          0x004046e8      0xc60 stdlib.o
                0x004049de                FreeHeap
                0x00404710                rtGetHeapStart
                0x00404ceb                free
                0x004046e8                stdlib_system_call
                0x00404c14                rand
                0x00404b8b                stdlibInitMM
                0x004049e8                heapInit
                0x00405185                __findenv
                0x00404724                rtGetHeapPointer
                0x0040472e                rtGetAvailableHeap
                0x00404c31                srand
                0x00405285                atoi
                0x00404beb                libcInitRT
                0x00404738                heapSetLibcHeap
                0x00404c69                stdlib_die
                0x00405250                getenv
                0x00404caa                malloc
                0x004049cb                AllocateHeapEx
                0x004047df                AllocateHeap
                0x004050fc                stdlib_strncmp
                0x00404c3e                xmalloc
                0x0040515a                exit
                0x0040471a                rtGetHeapEnd
                0x00404cf0                system
 .text          0x00405348        0x0 ctype.o
 .text          0x00405348      0x430 string.o
                0x00405534                strcspn
                0x00405497                strcat
                0x00405348                strcmp
                0x004054ee                bzero
                0x00405674                strtok_r
                0x0040542a                memcpy
                0x00405401                memoryZeroMemory
                0x004054c7                bcopy
                0x00405467                strcpy
                0x004055d4                strspn
                0x00405749                strtok
                0x004053a3                strncmp
                0x00405509                strlen
 .text          0x00405778     0x2600 api.o
                0x00406fe8                APIShowCurrentProcessInfo
                0x0040781b                api_getchar
                0x00405d1a                system11
                0x00405dbf                refresh_buffer
                0x00406eca                APISetFocus
                0x00405d7d                system14
                0x004060a6                apiInitBackground
                0x00406dba                APICreateWindow
                0x004075ca                apiBeginPaint
                0x004060ab                MessageBox
                0x00407066                APIreplace_window
                0x00407611                apiGetSystemMetrics
                0x00405d5c                system13
                0x00407465                apiDown
                0x00406b1c                dbProcedure
                0x0040715f                apiExit
                0x00407519                enterCriticalSection
                0x00407756                gramadocore_init_execve
                0x004073cd                apiFOpen
                0x00407d49                apiShowWindow
                0x00405bd0                system1
                0x00405c54                system5
                0x00407245                api_refresh_screen
                0x00407796                apiDialog
                0x004072d1                apiGetCursorY
                0x0040604f                carrega_bitmap_16x16
                0x00407572                exitCriticalSection
                0x00405778                system_call
                0x004074bf                apiUp
                0x004057a0                apiSystem
                0x0040772a                api_get_window_with_text_input
                0x00407c9f                apiGetWSScreenWindow
                0x00405d9e                system15
                0x00406f7a                APISetActiveWindow
                0x00407329                apiSetClientAreaRect
                0x00407c58                apiDrawText
                0x0040703d                APIredraw_window
                0x0040737b                apiCreateThread
                0x00405feb                SetNextWindowProcedure
                0x00407cf7                apiCreateTimer
                0x004072a5                apiGetCursorX
                0x00405fbb                chama_procedimento
                0x00406ba9                call_kernel
                0x00406e46                APIRegisterWindow
                0x00407ccb                apiGetWSMainWindow
                0x004071bb                api_strncmp
                0x004070b8                APIminimize_window
                0x00405bf1                system2
                0x00405c12                system3
                0x0040662a                DialogBox
                0x00407663                api_get_current_keyboard_responder
                0x00407352                apiCreateProcess
                0x00406f0c                APIGetFocus
                0x00405c96                system7
                0x00405c75                system6
                0x00407607                apiDefDialog
                0x0040659d                mbProcedure
                0x00406e88                APICloseWindow
                0x00407c17                apiSendMessage
                0x0040759e                initializeCriticalSection
                0x00405cf9                system10
                0x0040601b                set_cursor
                0x0040708f                APImaximize_window
                0x0040778c                execve
                0x00407219                refresh_screen
                0x00407847                apiDisplayBMP
                0x00406d29                call_gui
                0x00405cd8                system9
                0x00407760                fork
                0x0040763a                api_set_current_keyboard_responder
                0x00407014                APIresize_window
                0x004075d4                apiEndPaint
                0x0040604a                put_char
                0x00405f56                print_string
                0x00407d20                apiGetSysTimeInfo
                0x004072fd                apiGetClientAreaRect
                0x00405f8c                edit_box
                0x0040718a                kill
                0x0040724f                apiReboot
                0x00406078                apiShutDown
                0x0040768f                api_set_current_mouse_responder
                0x0040710a                APIget_foregroung_window
                0x00405c33                system4
                0x00407407                apiSaveFile
                0x0040727b                apiSetCursor
                0x00405d3b                system12
                0x00405f5b                vsync
                0x00405cb7                system8
                0x004076e4                api_set_window_with_text_input
                0x00406fbc                APIGetActiveWindow
                0x004070e1                APIupdate_window
                0x004076b8                api_get_current_mouse_responder
                0x0040718f                dead_thread_collector
                0x004073a4                apiStartThread
                0x00406f38                APIKillFocus
                0x00407136                APIset_foregroung_window
                0x004075de                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407d78      0x288 00

.rdata          0x00408000      0xfd0
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x330 main.o

.data           0x00408fd0     0x1030
                0x00408fd0                data = .
                0x00408fd0                _data = .
                0x00408fd0                __data = .
 *(.data)
 .data          0x00408fd0        0x0 main.o
 .data          0x00408fd0        0x0 stdio.o
 .data          0x00408fd0        0x0 stdlib.o
 .data          0x00408fd0        0x0 ctype.o
 .data          0x00408fd0        0x0 string.o
 .data          0x00408fd0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409410      0xbf0 00

.bss            0x0040a000     0xa7a0
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000       0x10 main.o
                0x0040a000                buffer_offset
 .bss           0x0040a010       0x10 stdio.o
 .bss           0x0040a020     0x8010 stdlib.o
                0x0040a020                environ
 .bss           0x00412030        0x0 ctype.o
 .bss           0x00412030       0x10 string.o
 .bss           0x00412040       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412080      0xf80 00
 COMMON         0x00413000      0xe60 main.o
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
                0x00413d70                POS_BUFFER
                0x00413df0                g_cursor_y
                0x00413e00                CursorInfo
                0x00413e10                prompt_status
                0x00413e20                g_char_attrib
                0x00413e30                ApplicationInfo
                0x00413e40                idleError
                0x00413e50                g_cursor_x
 COMMON         0x00413e60      0x900 stdlib.o
                0x00413e60                current_mmblock
                0x00413e70                mm_prev_pointer
                0x00413e80                heap_end
                0x00413e90                g_available_heap
                0x00413ea0                heap_start
                0x00413eb0                heapCount
                0x00413ec0                HEAP_START
                0x00413ed0                g_heap_pointer
                0x00413ee0                heapList
                0x004142e0                randseed
                0x004142f0                HEAP_SIZE
                0x00414300                last_size
                0x00414310                last_valid
                0x00414320                mmblockList
                0x00414720                libcHeap
                0x00414730                Heap
                0x00414740                mmblockCount
                0x00414750                HEAP_END
 COMMON         0x00414760       0x40 api.o
                0x00414760                messagebox_button2
                0x00414770                dialogbox_button1
                0x00414780                messagebox_button1
                0x00414790                dialogbox_button2
                0x004147a0                end = .
                0x004147a0                _end = .
                0x004147a0                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TBST.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
