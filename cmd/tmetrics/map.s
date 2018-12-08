
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

.text           0x00401000     0x5000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x130 main.o
                0x00401000                app_test
 .text          0x00401130     0x2550 api.o
                0x004029ba                APIShowCurrentProcessInfo
                0x004031ed                api_getchar
                0x004016d2                system11
                0x00401777                refresh_buffer
                0x0040289c                APISetFocus
                0x00401735                system14
                0x00401a5e                apiInitBackground
                0x0040278c                APICreateWindow
                0x00402f9c                apiBeginPaint
                0x00401a63                MessageBox
                0x00402a38                APIreplace_window
                0x00402fe3                apiGetSystemMetrics
                0x00401714                system13
                0x00402e37                apiDown
                0x004024ee                dbProcedure
                0x00402b31                apiExit
                0x00402eeb                enterCriticalSection
                0x00403128                gramadocore_init_execve
                0x00402d9f                apiFOpen
                0x00401588                system1
                0x0040160c                system5
                0x00402c17                api_refresh_screen
                0x00403168                apiDialog
                0x00402ca3                apiGetCursorY
                0x00401a07                carrega_bitmap_16x16
                0x00402f44                exitCriticalSection
                0x00401130                system_call
                0x00402e91                apiUp
                0x00401158                apiSystem
                0x004030fc                api_get_window_with_text_input
                0x00401756                system15
                0x0040294c                APISetActiveWindow
                0x00402cfb                apiSetClientAreaRect
                0x0040362a                apiDrawText
                0x00402a0f                APIredraw_window
                0x00402d4d                apiCreateThread
                0x004019a3                SetNextWindowProcedure
                0x00402c77                apiGetCursorX
                0x00401973                chama_procedimento
                0x0040257b                call_kernel
                0x00402818                APIRegisterWindow
                0x00402b8d                api_strncmp
                0x00402a8a                APIminimize_window
                0x004015a9                system2
                0x004015ca                system3
                0x00401fef                DialogBox
                0x00403035                api_get_current_keyboard_responder
                0x00402d24                apiCreateProcess
                0x004028de                APIGetFocus
                0x0040164e                system7
                0x0040162d                system6
                0x00402fd9                apiDefDialog
                0x00401f62                mbProcedure
                0x0040285a                APICloseWindow
                0x004035e9                apiSendMessage
                0x00402f70                initializeCriticalSection
                0x004016b1                system10
                0x004019d3                set_cursor
                0x00402a61                APImaximize_window
                0x0040315e                execve
                0x00402beb                refresh_screen
                0x00403219                apiDisplayBMP
                0x004026fb                call_gui
                0x00401690                system9
                0x00403132                fork
                0x0040300c                api_set_current_keyboard_responder
                0x004029e6                APIresize_window
                0x00402fa6                apiEndPaint
                0x00401a02                put_char
                0x0040190e                print_string
                0x00402ccf                apiGetClientAreaRect
                0x00401944                edit_box
                0x00402b5c                kill
                0x00402c21                apiReboot
                0x00401a30                apiShutDown
                0x00403061                api_set_current_mouse_responder
                0x00402adc                APIget_foregroung_window
                0x004015eb                system4
                0x00402dd9                apiSaveFile
                0x00402c4d                apiSetCursor
                0x004016f3                system12
                0x00401913                vsync
                0x0040166f                system8
                0x004030b6                api_set_window_with_text_input
                0x0040298e                APIGetActiveWindow
                0x00402ab3                APIupdate_window
                0x0040308a                api_get_current_mouse_responder
                0x00402b61                dead_thread_collector
                0x00402d76                apiStartThread
                0x0040290a                APIKillFocus
                0x00402b08                APIset_foregroung_window
                0x00402fb0                apiPutChar
 .text          0x00403680     0x1360 stdio.o
                0x00403e96                putchar
                0x00403680                stdio_fntos
                0x00403e52                sprintf
                0x004045c4                feof
                0x004046ea                stdioSetCursor
                0x00404526                ungetc
                0x00403950                puts
                0x004046a2                fputc
                0x00404740                stdioGetCursorY
                0x00404821                scanf
                0x0040443c                fputs
                0x00404602                ferror
                0x00404078                input
                0x0040388e                scroll
                0x004044b1                gets
                0x00403ec2                outbyte
                0x00404358                fflush
                0x004043c7                fprintf
                0x004041e0                stdio_system_call
                0x004037d5                fopen
                0x00404714                stdioGetCursorX
                0x00404208                getchar
                0x0040476c                stdio_atoi
                0x00404234                stdioInitialize
                0x00404563                fgetc
                0x0040376f                fclose
                0x00404628                fseek
                0x00404045                _outbyte
                0x00403e37                printf
 .text          0x004049e0      0xaf0 stdlib.o
                0x00404cd6                FreeHeap
                0x00404a08                rtGetHeapStart
                0x00404f2a                free
                0x004049e0                stdlib_system_call
                0x00404ebf                rand
                0x00404e36                stdlibInitMM
                0x00404ce0                heapInit
                0x004053c4                __findenv
                0x00404a1c                rtGetHeapPointer
                0x00404a26                rtGetAvailableHeap
                0x00404edc                srand
                0x00404e96                libcInitRT
                0x00404a30                heapSetLibcHeap
                0x0040548f                getenv
                0x00404ee9                malloc
                0x00404cc3                AllocateHeapEx
                0x00404ad7                AllocateHeap
                0x0040533b                stdlib_strncmp
                0x00405399                exit
                0x00404a12                rtGetHeapEnd
                0x00404f2f                system
 .text          0x004054d0      0x430 string.o
                0x004056bc                strcspn
                0x0040561f                strcat
                0x004054d0                strcmp
                0x00405676                bzero
                0x004057fc                strtok_r
                0x004055b2                memcpy
                0x00405589                memoryZeroMemory
                0x0040564f                bcopy
                0x004055ef                strcpy
                0x0040575c                strspn
                0x004058d1                strtok
                0x0040552b                strncmp
                0x00405691                strlen
 .text          0x00405900       0xe0 ctype.o
                0x0040599a                isspace
                0x004059c0                isxdigit
                0x004059ad                isupper
                0x00405913                isalpha
                0x0040595f                islower
                0x00405900                isalnum
                0x00405972                isprint
                0x0040594c                isgraph
                0x00405939                isdigit
                0x00405926                iscntrl
                0x00405987                ispunct
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x004059e0      0x620 00

.rdata          0x00406000      0x910
 .rdata         0x00406000      0x460 stdlib.o
 .rdata         0x00406460       0x70 stdio.o
 .rdata         0x004064d0      0x3e0 api.o
 .rdata         0x004068b0       0x60 main.o

.data           0x00406910     0x16f0
                0x00406910                data = .
                0x00406910                _data = .
                0x00406910                __data = .
 *(.data)
 .data          0x00406910      0x440 main.o
 .data          0x00406d50      0x440 api.o
 .data          0x00407190        0x0 stdio.o
 .data          0x00407190        0x0 stdlib.o
 .data          0x00407190        0x0 string.o
 .data          0x00407190      0x120 ctype.o
                0x00407190                _ctype_
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004072b0      0xd50 00

.bss            0x00408000     0xa6f0
                0x00408000                bss = .
                0x00408000                _bss = .
                0x00408000                __bss = .
 *(.bss)
 .bss           0x00408000        0x0 main.o
 .bss           0x00408000       0x40 api.o
 .bss           0x00408040       0x10 stdio.o
 .bss           0x00408050     0x8010 stdlib.o
                0x00408050                environ
 .bss           0x00410060       0x10 string.o
 .bss           0x00410070        0x0 ctype.o
                0x00411000                . = ALIGN (0x1000)
 *fill*         0x00410070      0xf90 00
 COMMON         0x00411000      0xdb0 main.o
                0x00411000                prompt
                0x00411400                ClientAreaInfo
                0x00411410                BufferInfo
                0x00411420                stderr
                0x00411430                prompt_pos
                0x00411440                g_using_gui
                0x00411450                stdin
                0x00411460                rect
                0x00411470                prompt_max
                0x00411480                CurrentWindow
                0x00411490                prompt_err
                0x00411890                current_semaphore
                0x004118a0                g_columns
                0x004118b0                stdout
                0x004118c0                Streams
                0x00411940                g_rows
                0x00411950                prompt_out
                0x00411d50                g_cursor_y
                0x00411d60                CursorInfo
                0x00411d70                prompt_status
                0x00411d80                g_char_attrib
                0x00411d90                ApplicationInfo
                0x00411da0                g_cursor_x
 COMMON         0x00411db0       0x40 api.o
                0x00411db0                messagebox_button2
                0x00411dc0                dialogbox_button1
                0x00411dd0                messagebox_button1
                0x00411de0                dialogbox_button2
 COMMON         0x00411df0      0x900 stdlib.o
                0x00411df0                current_mmblock
                0x00411e00                mm_prev_pointer
                0x00411e10                heap_end
                0x00411e20                g_available_heap
                0x00411e30                heap_start
                0x00411e40                heapCount
                0x00411e50                HEAP_START
                0x00411e60                g_heap_pointer
                0x00411e70                heapList
                0x00412270                randseed
                0x00412280                HEAP_SIZE
                0x00412290                last_size
                0x004122a0                last_valid
                0x004122b0                mmblockList
                0x004126b0                libcHeap
                0x004126c0                Heap
                0x004126d0                mmblockCount
                0x004126e0                HEAP_END
                0x004126f0                end = .
                0x004126f0                _end = .
                0x004126f0                __end = .
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD ctype.o
OUTPUT(TMETRICS.BIN pe-i386)
