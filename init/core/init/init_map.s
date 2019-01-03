
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x4               main.o
ClientAreaInfo      0x10              api.o
BufferInfo          0x10              api.o
stderr              0x10              stdio.o
prompt_pos          0x10              stdio.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              stdio.o
stdin               0x10              stdio.o
heap_end            0x10              stdlib.o
rect                0x10              api.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              stdio.o
CurrentWindow       0x10              api.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
current_semaphore   0x10              api.o
g_columns           0x10              stdio.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              stdio.o
Streams             0x80              main.o
ServerStatus        0x4               main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              stdio.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              stdio.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              stdio.o
g_char_attrib       0x10              stdio.o
ApplicationInfo     0x10              api.o
idleError           0x4               main.o
g_cursor_x          0x10              stdio.o
HEAP_END            0x10              stdlib.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

                0x0000000000400000                __image_base__ = 0x400000
                0x0000000000000000                __dll__ = 0x0
                0x0000000000400000                ___ImageBase = 0x400000
                0x0000000000001000                __section_alignment__ = 0x1000
                0x0000000000000200                __file_alignment__ = 0x200
                0x0000000000000004                __major_os_version__ = 0x4
                0x0000000000000000                __minor_os_version__ = 0x0
                0x0000000000000001                __major_image_version__ = 0x1
                0x0000000000000000                __minor_image_version__ = 0x0
                0x0000000000000004                __major_subsystem_version__ = 0x4
                0x0000000000000000                __minor_subsystem_version__ = 0x0
                0x0000000000000003                __subsystem__ = 0x3
                0x0000000000200000                __size_of_stack_reserve__ = 0x200000
                0x0000000000001000                __size_of_stack_commit__ = 0x1000
                0x0000000000100000                __size_of_heap_reserve__ = 0x100000
                0x0000000000001000                __size_of_heap_commit__ = 0x1000
                0x0000000000000000                __loader_flags__ = 0x0
                0x0000000000000000                __dll_characteristics__ = 0x0

.text           0x0000000000401000     0x7000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 .head_x86      0x0000000000401000       0x5f head.o
                0x0000000000401000                idle_entry_point
 *(.text)
 .text          0x000000000040105f       0xfe main.o
                0x000000000040106f                idleLoop
                0x000000000040108d                initMain
                0x0000000000401093                driverInitialize
                0x00000000004010b6                driverUninitialize
                0x00000000004010d9                idleServices
                0x000000000040113f                idleInit
 *fill*         0x000000000040115d        0x3 
 .text          0x0000000000401160     0x2a10 stdio.o
                0x0000000000401160                stdio_atoi
                0x0000000000401215                stdio_fntos
                0x0000000000401314                fclose
                0x000000000040137a                fopen
                0x00000000004014bc                scroll
                0x000000000040157e                puts
                0x0000000000401a65                printf3
                0x0000000000401a80                printf_atoi
                0x0000000000401b6d                printf_i2hex
                0x0000000000401bdb                printf2
                0x0000000000401d5b                sprintf
                0x0000000000401d9f                putchar
                0x0000000000401dcb                outbyte
                0x0000000000401f4e                _outbyte
                0x0000000000401f81                input
                0x00000000004020e9                stdio_system_call
                0x0000000000402111                getchar
                0x000000000040213d                stdioInitialize
                0x0000000000402324                fflush
                0x00000000004023b6                fprintf
                0x000000000040242b                fputs
                0x00000000004024a0                gets
                0x000000000040252d                ungetc
                0x000000000040256a                ftell
                0x0000000000402594                fileno
                0x00000000004025b7                fgetc
                0x0000000000402618                feof
                0x0000000000402656                ferror
                0x000000000040267c                fseek
                0x00000000004026f6                fputc
                0x000000000040273e                stdioSetCursor
                0x0000000000402768                stdioGetCursorX
                0x0000000000402794                stdioGetCursorY
                0x00000000004027c0                scanf
                0x0000000000402a70                kvprintf
                0x00000000004039ff                printf
                0x0000000000403a37                vfprintf
                0x0000000000403ac3                stdout_printf
                0x0000000000403af2                stderr_printf
                0x0000000000403b21                perror
                0x0000000000403b34                rewind
 .text          0x0000000000403b70        0x0 ctype.o
 .text          0x0000000000403b70      0x470 string.o
                0x0000000000403b70                strcmp
                0x0000000000403bcb                strncmp
                0x0000000000403c29                memset
                0x0000000000403c72                memoryZeroMemory
                0x0000000000403c9b                memcpy
                0x0000000000403cd8                strcpy
                0x0000000000403d08                strcat
                0x0000000000403d38                bcopy
                0x0000000000403d5f                bzero
                0x0000000000403d7a                strlen
                0x0000000000403da5                strcspn
                0x0000000000403e45                strspn
                0x0000000000403ee5                strtok_r
                0x0000000000403fba                strtok
 .text          0x0000000000403fe0      0xda0 stdlib.o
                0x0000000000403fe0                stdlib_system_call
                0x0000000000404008                rtGetHeapStart
                0x0000000000404012                rtGetHeapEnd
                0x000000000040401c                rtGetHeapPointer
                0x0000000000404026                rtGetAvailableHeap
                0x0000000000404030                heapSetLibcHeap
                0x00000000004040d7                AllocateHeap
                0x00000000004042f6                AllocateHeapEx
                0x0000000000404309                FreeHeap
                0x0000000000404313                heapInit
                0x00000000004044b6                stdlibInitMM
                0x0000000000404520                libcInitRT
                0x0000000000404549                rand
                0x0000000000404566                srand
                0x0000000000404573                xmalloc
                0x000000000040459e                stdlib_die
                0x00000000004045df                malloc
                0x0000000000404620                free
                0x0000000000404625                calloc
                0x0000000000404668                system
                0x0000000000404a74                stdlib_strncmp
                0x0000000000404ad2                __findenv
                0x0000000000404b9d                getenv
                0x0000000000404bd2                atoi
                0x0000000000404c87                reverse
                0x0000000000404ce6                itoa
 .text          0x0000000000404d80       0x90 unistd.o
                0x0000000000404d80                unistd_system_call
                0x0000000000404da8                execve
                0x0000000000404db2                exit
                0x0000000000404ddd                fork
 .text          0x0000000000404e10     0x25d0 api.o
                0x0000000000404e10                system_call
                0x0000000000404e38                apiSystem
                0x0000000000405268                system1
                0x0000000000405289                system2
                0x00000000004052aa                system3
                0x00000000004052cb                system4
                0x00000000004052ec                system5
                0x000000000040530d                system6
                0x000000000040532e                system7
                0x000000000040534f                system8
                0x0000000000405370                system9
                0x0000000000405391                system10
                0x00000000004053b2                system11
                0x00000000004053d3                system12
                0x00000000004053f4                system13
                0x0000000000405415                system14
                0x0000000000405436                system15
                0x0000000000405457                refresh_buffer
                0x00000000004055ee                print_string
                0x00000000004055f3                vsync
                0x0000000000405624                edit_box
                0x0000000000405653                chama_procedimento
                0x0000000000405683                SetNextWindowProcedure
                0x00000000004056b3                set_cursor
                0x00000000004056e2                put_char
                0x00000000004056e7                carrega_bitmap_16x16
                0x0000000000405710                apiShutDown
                0x000000000040573e                apiInitBackground
                0x0000000000405743                MessageBox
                0x0000000000405c35                mbProcedure
                0x0000000000405cc2                DialogBox
                0x00000000004061b4                dbProcedure
                0x0000000000406241                call_kernel
                0x00000000004063c1                call_gui
                0x0000000000406452                APICreateWindow
                0x00000000004064de                APIRegisterWindow
                0x0000000000406520                APICloseWindow
                0x0000000000406562                APISetFocus
                0x00000000004065a4                APIGetFocus
                0x00000000004065d0                APIKillFocus
                0x0000000000406612                APISetActiveWindow
                0x0000000000406654                APIGetActiveWindow
                0x0000000000406680                APIShowCurrentProcessInfo
                0x00000000004066ac                APIresize_window
                0x00000000004066d5                APIredraw_window
                0x00000000004066fe                APIreplace_window
                0x0000000000406727                APImaximize_window
                0x0000000000406750                APIminimize_window
                0x0000000000406779                APIupdate_window
                0x00000000004067a2                APIget_foregroung_window
                0x00000000004067ce                APIset_foregroung_window
                0x00000000004067f7                apiExit
                0x0000000000406822                kill
                0x0000000000406827                dead_thread_collector
                0x0000000000406853                api_strncmp
                0x00000000004068b1                refresh_screen
                0x00000000004068dd                api_refresh_screen
                0x00000000004068e7                apiReboot
                0x0000000000406913                apiSetCursor
                0x000000000040693d                apiGetCursorX
                0x0000000000406969                apiGetCursorY
                0x0000000000406995                apiGetClientAreaRect
                0x00000000004069c1                apiSetClientAreaRect
                0x00000000004069ea                apiCreateProcess
                0x0000000000406a13                apiCreateThread
                0x0000000000406a3c                apiStartThread
                0x0000000000406a65                apiFOpen
                0x0000000000406a9f                apiSaveFile
                0x0000000000406afd                apiDown
                0x0000000000406b57                apiUp
                0x0000000000406bb1                enterCriticalSection
                0x0000000000406c0a                exitCriticalSection
                0x0000000000406c36                initializeCriticalSection
                0x0000000000406c62                apiBeginPaint
                0x0000000000406c6c                apiEndPaint
                0x0000000000406c76                apiPutChar
                0x0000000000406c9f                apiDefDialog
                0x0000000000406ca9                apiGetSystemMetrics
                0x0000000000406cd2                api_set_current_keyboard_responder
                0x0000000000406cfb                api_get_current_keyboard_responder
                0x0000000000406d27                api_set_current_mouse_responder
                0x0000000000406d50                api_get_current_mouse_responder
                0x0000000000406d7c                api_set_window_with_text_input
                0x0000000000406dc2                api_get_window_with_text_input
                0x0000000000406dee                gramadocore_init_execve
                0x0000000000406df8                apiDialog
                0x0000000000406e7d                api_getchar
                0x0000000000406ea9                apiDisplayBMP
                0x0000000000407279                apiSendMessage
                0x00000000004072ba                apiDrawText
                0x0000000000407301                apiGetWSScreenWindow
                0x000000000040732d                apiGetWSMainWindow
                0x0000000000407359                apiCreateTimer
                0x0000000000407382                apiGetSysTimeInfo
                0x00000000004073ab                apiShowWindow
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004073e0      0xc20 

.rodata         0x0000000000408000       0xa0
 .rodata        0x0000000000408000       0x9f main.o

.eh_frame       0x0000000000409000      0x114
 .eh_frame      0x0000000000409000      0x114 main.o

.rdata          0x000000000040a000      0xd20
 .rdata         0x000000000040a000      0x380 stdio.o
                0x000000000040a1e0                hex2ascii_data
 .rdata         0x000000000040a380      0x100 ctype.o
                0x000000000040a380                _ctype
 .rdata         0x000000000040a480      0x4f0 stdlib.o
 .rdata         0x000000000040a970      0x3a0 api.o

.data           0x000000000040ad20     0x12e0
                0x000000000040ad20                data = .
                0x000000000040ad20                _data = .
                0x000000000040ad20                __data = .
 *(.data)
 .data          0x000000000040ad20      0x450 main.o
 .data          0x000000000040b170        0x0 stdio.o
 .data          0x000000000040b170        0x0 ctype.o
 .data          0x000000000040b170        0x0 string.o
 .data          0x000000000040b170        0x0 stdlib.o
 .data          0x000000000040b170        0x0 unistd.o
 .data          0x000000000040b170      0x440 api.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040b5b0      0xa50 

.bss            0x000000000040c000    0x126fc
                0x000000000040c000                bss = .
                0x000000000040c000                _bss = .
                0x000000000040c000                __bss = .
 *(.bss)
 .bss           0x000000000040c000        0x0 main.o
 .bss           0x000000000040c000       0x10 stdio.o
 .bss           0x000000000040c010        0x0 ctype.o
 .bss           0x000000000040c010       0x10 string.o
 .bss           0x000000000040c020     0x8010 stdlib.o
                0x000000000040c020                environ
 .bss           0x0000000000414030        0x0 unistd.o
 .bss           0x0000000000414030     0x8010 api.o
                0x000000000041d000                . = ALIGN (0x1000)
 *fill*         0x000000000041c040      0xfc0 
 COMMON         0x000000000041d000      0xc8c main.o
                0x000000000041d000                prompt
                0x000000000041d400                idleStatus
                0x000000000041d404                prompt_err
                0x000000000041d804                Streams
                0x000000000041d884                ServerStatus
                0x000000000041d888                prompt_out
                0x000000000041dc88                idleError
 COMMON         0x000000000041dc8c       0xc0 stdio.o
                0x000000000041dc8c                stderr
                0x000000000041dc9c                prompt_pos
                0x000000000041dcac                g_using_gui
                0x000000000041dcbc                stdin
                0x000000000041dccc                prompt_max
                0x000000000041dcdc                g_columns
                0x000000000041dcec                stdout
                0x000000000041dcfc                g_rows
                0x000000000041dd0c                g_cursor_y
                0x000000000041dd1c                prompt_status
                0x000000000041dd2c                g_char_attrib
                0x000000000041dd3c                g_cursor_x
 COMMON         0x000000000041dd4c      0x900 stdlib.o
                0x000000000041dd4c                current_mmblock
                0x000000000041dd5c                mm_prev_pointer
                0x000000000041dd6c                heap_end
                0x000000000041dd7c                g_available_heap
                0x000000000041dd8c                heap_start
                0x000000000041dd9c                heapCount
                0x000000000041ddac                HEAP_START
                0x000000000041ddbc                g_heap_pointer
                0x000000000041ddcc                heapList
                0x000000000041e1cc                randseed
                0x000000000041e1dc                HEAP_SIZE
                0x000000000041e1ec                last_size
                0x000000000041e1fc                last_valid
                0x000000000041e20c                mmblockList
                0x000000000041e60c                libcHeap
                0x000000000041e61c                Heap
                0x000000000041e62c                mmblockCount
                0x000000000041e63c                HEAP_END
 COMMON         0x000000000041e64c       0xb0 api.o
                0x000000000041e64c                ClientAreaInfo
                0x000000000041e65c                BufferInfo
                0x000000000041e66c                messagebox_button2
                0x000000000041e67c                rect
                0x000000000041e68c                CurrentWindow
                0x000000000041e69c                current_semaphore
                0x000000000041e6ac                dialogbox_button1
                0x000000000041e6bc                messagebox_button1
                0x000000000041e6cc                dialogbox_button2
                0x000000000041e6dc                CursorInfo
                0x000000000041e6ec                ApplicationInfo
                0x000000000041e6fc                end = .
                0x000000000041e6fc                _end = .
                0x000000000041e6fc                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD ctype.o
LOAD string.o
LOAD stdlib.o
LOAD unistd.o
LOAD api.o
OUTPUT(INIT.BIN pe-i386)

.comment        0x0000000000000000       0x1c
 .comment       0x0000000000000000       0x1b main.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
