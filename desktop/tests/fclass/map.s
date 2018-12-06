
Allocating common symbols
Common symbol       size              file

prompt              0x400             crt0.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              crt0.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              crt0.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             crt0.o
randseed            0x10              stdlib.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
Streams             0x80              crt0.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x400             crt0.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              crt0.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
g_char_attrib       0x10              crt0.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              crt0.o
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
 .text          0x00401000       0x60 crt0.o
                0x00401000                _main
 .text          0x00401060      0x240 main.o
                0x0040109a                Add
                0x00401060                get_a
                0x004010b1                app_main
                0x004010a5                Multi
                0x00401087                do_print_string
 .text          0x004012a0        0x0 ctype.o
 .text          0x004012a0     0x2a00 stdio.o
                0x00401cad                printf_i2hex
                0x00401edf                putchar
                0x00401355                stdio_fntos
                0x00401e9b                sprintf
                0x00402740                feof
                0x00401d1b                printf2
                0x00402866                stdioSetCursor
                0x00402655                ungetc
                0x00403c5c                rewind
                0x004016be                puts
                0x0040281e                fputc
                0x004028bc                stdioGetCursorY
                0x004028e8                scanf
                0x0040256b                fputs
                0x0040277e                ferror
                0x004020c1                input
                0x004015fc                scroll
                0x004025e0                gets
                0x00401f0b                outbyte
                0x004026bc                fileno
                0x00402464                fflush
                0x004024f6                fprintf
                0x00403c1a                stderr_printf
                0x00402229                stdio_system_call
                0x004014ba                fopen
                0x00402890                stdioGetCursorX
                0x00402251                getchar
                0x00401bc0                printf_atoi
                0x004012a0                stdio_atoi
                0x00402b98                kvprintf
                0x00403beb                stdout_printf
                0x0040227d                stdioInitialize
                0x004026df                fgetc
                0x00401454                fclose
                0x004027a4                fseek
                0x00403c49                perror
                0x0040208e                _outbyte
                0x00402692                ftell
                0x00403b27                printf
                0x00401ba5                printf3
                0x00403b5f                vfprintf
 .text          0x00403ca0      0xc60 stdlib.o
                0x00403f96                FreeHeap
                0x00403cc8                rtGetHeapStart
                0x004042a3                free
                0x00403ca0                stdlib_system_call
                0x004041cc                rand
                0x00404143                stdlibInitMM
                0x00403fa0                heapInit
                0x0040473d                __findenv
                0x00403cdc                rtGetHeapPointer
                0x00403ce6                rtGetAvailableHeap
                0x004041e9                srand
                0x0040483d                atoi
                0x004041a3                libcInitRT
                0x00403cf0                heapSetLibcHeap
                0x00404221                stdlib_die
                0x00404808                getenv
                0x00404262                malloc
                0x00403f83                AllocateHeapEx
                0x00403d97                AllocateHeap
                0x004046b4                stdlib_strncmp
                0x004041f6                xmalloc
                0x00404712                exit
                0x00403cd2                rtGetHeapEnd
                0x004042a8                system
 .text          0x00404900      0x430 string.o
                0x00404aec                strcspn
                0x00404a4f                strcat
                0x00404900                strcmp
                0x00404aa6                bzero
                0x00404c2c                strtok_r
                0x004049e2                memcpy
                0x004049b9                memoryZeroMemory
                0x00404a7f                bcopy
                0x00404a1f                strcpy
                0x00404b8c                strspn
                0x00404d01                strtok
                0x0040495b                strncmp
                0x00404ac1                strlen
 .text          0x00404d30     0x2600 api.o
                0x004065a0                APIShowCurrentProcessInfo
                0x00406dd3                api_getchar
                0x004052d2                system11
                0x00405377                refresh_buffer
                0x00406482                APISetFocus
                0x00405335                system14
                0x0040565e                apiInitBackground
                0x00406372                APICreateWindow
                0x00406b82                apiBeginPaint
                0x00405663                MessageBox
                0x0040661e                APIreplace_window
                0x00406bc9                apiGetSystemMetrics
                0x00405314                system13
                0x00406a1d                apiDown
                0x004060d4                dbProcedure
                0x00406717                apiExit
                0x00406ad1                enterCriticalSection
                0x00406d0e                gramadocore_init_execve
                0x00406985                apiFOpen
                0x00407301                apiShowWindow
                0x00405188                system1
                0x0040520c                system5
                0x004067fd                api_refresh_screen
                0x00406d4e                apiDialog
                0x00406889                apiGetCursorY
                0x00405607                carrega_bitmap_16x16
                0x00406b2a                exitCriticalSection
                0x00404d30                system_call
                0x00406a77                apiUp
                0x00404d58                apiSystem
                0x00406ce2                api_get_window_with_text_input
                0x00407257                apiGetWSScreenWindow
                0x00405356                system15
                0x00406532                APISetActiveWindow
                0x004068e1                apiSetClientAreaRect
                0x00407210                apiDrawText
                0x004065f5                APIredraw_window
                0x00406933                apiCreateThread
                0x004055a3                SetNextWindowProcedure
                0x004072af                apiCreateTimer
                0x0040685d                apiGetCursorX
                0x00405573                chama_procedimento
                0x00406161                call_kernel
                0x004063fe                APIRegisterWindow
                0x00407283                apiGetWSMainWindow
                0x00406773                api_strncmp
                0x00406670                APIminimize_window
                0x004051a9                system2
                0x004051ca                system3
                0x00405be2                DialogBox
                0x00406c1b                api_get_current_keyboard_responder
                0x0040690a                apiCreateProcess
                0x004064c4                APIGetFocus
                0x0040524e                system7
                0x0040522d                system6
                0x00406bbf                apiDefDialog
                0x00405b55                mbProcedure
                0x00406440                APICloseWindow
                0x004071cf                apiSendMessage
                0x00406b56                initializeCriticalSection
                0x004052b1                system10
                0x004055d3                set_cursor
                0x00406647                APImaximize_window
                0x00406d44                execve
                0x004067d1                refresh_screen
                0x00406dff                apiDisplayBMP
                0x004062e1                call_gui
                0x00405290                system9
                0x00406d18                fork
                0x00406bf2                api_set_current_keyboard_responder
                0x004065cc                APIresize_window
                0x00406b8c                apiEndPaint
                0x00405602                put_char
                0x0040550e                print_string
                0x004072d8                apiGetSysTimeInfo
                0x004068b5                apiGetClientAreaRect
                0x00405544                edit_box
                0x00406742                kill
                0x00406807                apiReboot
                0x00405630                apiShutDown
                0x00406c47                api_set_current_mouse_responder
                0x004066c2                APIget_foregroung_window
                0x004051eb                system4
                0x004069bf                apiSaveFile
                0x00406833                apiSetCursor
                0x004052f3                system12
                0x00405513                vsync
                0x0040526f                system8
                0x00406c9c                api_set_window_with_text_input
                0x00406574                APIGetActiveWindow
                0x00406699                APIupdate_window
                0x00406c70                api_get_current_mouse_responder
                0x00406747                dead_thread_collector
                0x0040695c                apiStartThread
                0x004064f0                APIKillFocus
                0x004066ee                APIset_foregroung_window
                0x00406b96                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407330      0xcd0 00

.rdata          0x00408000      0xdb0
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x480 stdlib.o
 .rdata         0x00408820      0x380 stdio.o
                0x00408a00                hex2ascii_data
 .rdata         0x00408ba0      0x100 ctype.o
                0x00408ba0                _ctype
 .rdata         0x00408ca0       0xe0 main.o
 .rdata         0x00408d80       0x30 crt0.o

.data           0x00408db0     0x1250
                0x00408db0                data = .
                0x00408db0                _data = .
                0x00408db0                __data = .
 *(.data)
 .data          0x00408db0        0x0 crt0.o
 .data          0x00408db0      0x440 main.o
 .data          0x004091f0        0x0 ctype.o
 .data          0x004091f0        0x0 stdio.o
 .data          0x004091f0        0x0 stdlib.o
 .data          0x004091f0        0x0 string.o
 .data          0x004091f0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409630      0x9d0 00

.bss            0x0040a000     0xa6f0
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 crt0.o
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000        0x0 ctype.o
 .bss           0x0040a000       0x10 stdio.o
 .bss           0x0040a010     0x8010 stdlib.o
                0x0040a010                environ
 .bss           0x00412020       0x10 string.o
 .bss           0x00412030       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xd40 crt0.o
                0x00413000                prompt
                0x00413400                stderr
                0x00413410                prompt_pos
                0x00413420                g_using_gui
                0x00413430                stdin
                0x00413440                prompt_max
                0x00413450                prompt_err
                0x00413850                g_columns
                0x00413860                stdout
                0x00413870                Streams
                0x004138f0                g_rows
                0x00413900                prompt_out
                0x00413d00                g_cursor_y
                0x00413d10                prompt_status
                0x00413d20                g_char_attrib
                0x00413d30                g_cursor_x
 COMMON         0x00413d40       0x70 main.o
                0x00413d40                ClientAreaInfo
                0x00413d50                BufferInfo
                0x00413d60                rect
                0x00413d70                CurrentWindow
                0x00413d80                current_semaphore
                0x00413d90                CursorInfo
                0x00413da0                ApplicationInfo
 COMMON         0x00413db0      0x900 stdlib.o
                0x00413db0                current_mmblock
                0x00413dc0                mm_prev_pointer
                0x00413dd0                heap_end
                0x00413de0                g_available_heap
                0x00413df0                heap_start
                0x00413e00                heapCount
                0x00413e10                HEAP_START
                0x00413e20                g_heap_pointer
                0x00413e30                heapList
                0x00414230                randseed
                0x00414240                HEAP_SIZE
                0x00414250                last_size
                0x00414260                last_valid
                0x00414270                mmblockList
                0x00414670                libcHeap
                0x00414680                Heap
                0x00414690                mmblockCount
                0x004146a0                HEAP_END
 COMMON         0x004146b0       0x40 api.o
                0x004146b0                messagebox_button2
                0x004146c0                dialogbox_button1
                0x004146d0                messagebox_button1
                0x004146e0                dialogbox_button2
                0x004146f0                end = .
                0x004146f0                _end = .
                0x004146f0                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD api.o
OUTPUT(FCLASS.BIN pe-i386)
