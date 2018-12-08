
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
 .text          0x00401038      0x780 main.o
                0x00401083                idleInit
                0x0040150b                TEST_PRINTF3
                0x004010a1                idleServices
                0x0040103d                driverInitialize
                0x0040110b                testtest_main
                0x004011a9                TEST_PRINTF
                0x00401038                idleLoop
                0x00401450                TEST_PRINTF2
                0x00401060                driverUninitialize
 .text          0x004017b8     0x2a10 stdio.o
                0x004021c5                printf_i2hex
                0x004023f7                putchar
                0x0040186d                stdio_fntos
                0x004023b3                sprintf
                0x00402c70                feof
                0x00402233                printf2
                0x00402d96                stdioSetCursor
                0x00402b85                ungetc
                0x0040418c                rewind
                0x00401bd6                puts
                0x00402d4e                fputc
                0x00402dec                stdioGetCursorY
                0x00402e18                scanf
                0x00402a83                fputs
                0x00402cae                ferror
                0x004025d9                input
                0x00401b14                scroll
                0x00402af8                gets
                0x00402423                outbyte
                0x00402bec                fileno
                0x0040297c                fflush
                0x00402a0e                fprintf
                0x0040414a                stderr_printf
                0x00402741                stdio_system_call
                0x004019d2                fopen
                0x00402dc0                stdioGetCursorX
                0x00402769                getchar
                0x004020d8                printf_atoi
                0x004017b8                stdio_atoi
                0x004030c8                kvprintf
                0x0040411b                stdout_printf
                0x00402795                stdioInitialize
                0x00402c0f                fgetc
                0x0040196c                fclose
                0x00402cd4                fseek
                0x00404179                perror
                0x004025a6                _outbyte
                0x00402bc2                ftell
                0x00404057                printf
                0x004020bd                printf3
                0x0040408f                vfprintf
 .text          0x004041c8      0xc60 stdlib.o
                0x004044be                FreeHeap
                0x004041f0                rtGetHeapStart
                0x004047cb                free
                0x004041c8                stdlib_system_call
                0x004046f4                rand
                0x0040466b                stdlibInitMM
                0x004044c8                heapInit
                0x00404c65                __findenv
                0x00404204                rtGetHeapPointer
                0x0040420e                rtGetAvailableHeap
                0x00404711                srand
                0x00404d65                atoi
                0x004046cb                libcInitRT
                0x00404218                heapSetLibcHeap
                0x00404749                stdlib_die
                0x00404d30                getenv
                0x0040478a                malloc
                0x004044ab                AllocateHeapEx
                0x004042bf                AllocateHeap
                0x00404bdc                stdlib_strncmp
                0x0040471e                xmalloc
                0x00404c3a                exit
                0x004041fa                rtGetHeapEnd
                0x004047d0                system
 .text          0x00404e28        0x0 ctype.o
 .text          0x00404e28      0x430 string.o
                0x00405014                strcspn
                0x00404f77                strcat
                0x00404e28                strcmp
                0x00404fce                bzero
                0x00405154                strtok_r
                0x00404f0a                memcpy
                0x00404ee1                memoryZeroMemory
                0x00404fa7                bcopy
                0x00404f47                strcpy
                0x004050b4                strspn
                0x00405229                strtok
                0x00404e83                strncmp
                0x00404fe9                strlen
 .text          0x00405258     0x2600 api.o
                0x00406ac8                APIShowCurrentProcessInfo
                0x004072fb                api_getchar
                0x004057fa                system11
                0x0040589f                refresh_buffer
                0x004069aa                APISetFocus
                0x0040585d                system14
                0x00405b86                apiInitBackground
                0x0040689a                APICreateWindow
                0x004070aa                apiBeginPaint
                0x00405b8b                MessageBox
                0x00406b46                APIreplace_window
                0x004070f1                apiGetSystemMetrics
                0x0040583c                system13
                0x00406f45                apiDown
                0x004065fc                dbProcedure
                0x00406c3f                apiExit
                0x00406ff9                enterCriticalSection
                0x00407236                gramadocore_init_execve
                0x00406ead                apiFOpen
                0x00407829                apiShowWindow
                0x004056b0                system1
                0x00405734                system5
                0x00406d25                api_refresh_screen
                0x00407276                apiDialog
                0x00406db1                apiGetCursorY
                0x00405b2f                carrega_bitmap_16x16
                0x00407052                exitCriticalSection
                0x00405258                system_call
                0x00406f9f                apiUp
                0x00405280                apiSystem
                0x0040720a                api_get_window_with_text_input
                0x0040777f                apiGetWSScreenWindow
                0x0040587e                system15
                0x00406a5a                APISetActiveWindow
                0x00406e09                apiSetClientAreaRect
                0x00407738                apiDrawText
                0x00406b1d                APIredraw_window
                0x00406e5b                apiCreateThread
                0x00405acb                SetNextWindowProcedure
                0x004077d7                apiCreateTimer
                0x00406d85                apiGetCursorX
                0x00405a9b                chama_procedimento
                0x00406689                call_kernel
                0x00406926                APIRegisterWindow
                0x004077ab                apiGetWSMainWindow
                0x00406c9b                api_strncmp
                0x00406b98                APIminimize_window
                0x004056d1                system2
                0x004056f2                system3
                0x0040610a                DialogBox
                0x00407143                api_get_current_keyboard_responder
                0x00406e32                apiCreateProcess
                0x004069ec                APIGetFocus
                0x00405776                system7
                0x00405755                system6
                0x004070e7                apiDefDialog
                0x0040607d                mbProcedure
                0x00406968                APICloseWindow
                0x004076f7                apiSendMessage
                0x0040707e                initializeCriticalSection
                0x004057d9                system10
                0x00405afb                set_cursor
                0x00406b6f                APImaximize_window
                0x0040726c                execve
                0x00406cf9                refresh_screen
                0x00407327                apiDisplayBMP
                0x00406809                call_gui
                0x004057b8                system9
                0x00407240                fork
                0x0040711a                api_set_current_keyboard_responder
                0x00406af4                APIresize_window
                0x004070b4                apiEndPaint
                0x00405b2a                put_char
                0x00405a36                print_string
                0x00407800                apiGetSysTimeInfo
                0x00406ddd                apiGetClientAreaRect
                0x00405a6c                edit_box
                0x00406c6a                kill
                0x00406d2f                apiReboot
                0x00405b58                apiShutDown
                0x0040716f                api_set_current_mouse_responder
                0x00406bea                APIget_foregroung_window
                0x00405713                system4
                0x00406ee7                apiSaveFile
                0x00406d5b                apiSetCursor
                0x0040581b                system12
                0x00405a3b                vsync
                0x00405797                system8
                0x004071c4                api_set_window_with_text_input
                0x00406a9c                APIGetActiveWindow
                0x00406bc1                APIupdate_window
                0x00407198                api_get_current_mouse_responder
                0x00406c6f                dead_thread_collector
                0x00406e84                apiStartThread
                0x00406a18                APIKillFocus
                0x00406c16                APIset_foregroung_window
                0x004070be                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407858      0x7a8 00

.rdata          0x00408000      0xf10
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x270 main.o

.data           0x00408f10     0x10f0
                0x00408f10                data = .
                0x00408f10                _data = .
                0x00408f10                __data = .
 *(.data)
 .data          0x00408f10        0x0 main.o
 .data          0x00408f10        0x0 stdio.o
 .data          0x00408f10        0x0 stdlib.o
 .data          0x00408f10        0x0 ctype.o
 .data          0x00408f10        0x0 string.o
 .data          0x00408f10      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409350      0xcb0 00

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
OUTPUT(TCTYPE.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
