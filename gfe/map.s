
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

.text           0x00401000     0x7000
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
 .text          0x0040146c        0x0 ctype.o
 .text          0x0040146c      0xc60 stdlib.o
                0x00401762                FreeHeap
                0x00401494                rtGetHeapStart
                0x00401a6f                free
                0x0040146c                stdlib_system_call
                0x00401998                rand
                0x0040190f                stdlibInitMM
                0x0040176c                heapInit
                0x00401f09                __findenv
                0x004014a8                rtGetHeapPointer
                0x004014b2                rtGetAvailableHeap
                0x004019b5                srand
                0x00402009                atoi
                0x0040196f                libcInitRT
                0x004014bc                heapSetLibcHeap
                0x004019ed                stdlib_die
                0x00401fd4                getenv
                0x00401a2e                malloc
                0x0040174f                AllocateHeapEx
                0x00401563                AllocateHeap
                0x00401e80                stdlib_strncmp
                0x004019c2                xmalloc
                0x00401ede                exit
                0x0040149e                rtGetHeapEnd
                0x00401a74                system
 .text          0x004020cc     0x2a10 stdio.o
                0x00402ad9                printf_i2hex
                0x00402d0b                putchar
                0x00402181                stdio_fntos
                0x00402cc7                sprintf
                0x00403584                feof
                0x00402b47                printf2
                0x004036aa                stdioSetCursor
                0x00403499                ungetc
                0x00404aa0                rewind
                0x004024ea                puts
                0x00403662                fputc
                0x00403700                stdioGetCursorY
                0x0040372c                scanf
                0x00403397                fputs
                0x004035c2                ferror
                0x00402eed                input
                0x00402428                scroll
                0x0040340c                gets
                0x00402d37                outbyte
                0x00403500                fileno
                0x00403290                fflush
                0x00403322                fprintf
                0x00404a5e                stderr_printf
                0x00403055                stdio_system_call
                0x004022e6                fopen
                0x004036d4                stdioGetCursorX
                0x0040307d                getchar
                0x004029ec                printf_atoi
                0x004020cc                stdio_atoi
                0x004039dc                kvprintf
                0x00404a2f                stdout_printf
                0x004030a9                stdioInitialize
                0x00403523                fgetc
                0x00402280                fclose
                0x004035e8                fseek
                0x00404a8d                perror
                0x00402eba                _outbyte
                0x004034d6                ftell
                0x0040496b                printf
                0x004029d1                printf3
                0x004049a3                vfprintf
 .text          0x00404adc      0x430 string.o
                0x00404cc8                strcspn
                0x00404c2b                strcat
                0x00404adc                strcmp
                0x00404c82                bzero
                0x00404e08                strtok_r
                0x00404bbe                memcpy
                0x00404b95                memoryZeroMemory
                0x00404c5b                bcopy
                0x00404bfb                strcpy
                0x00404d68                strspn
                0x00404edd                strtok
                0x00404b37                strncmp
                0x00404c9d                strlen
 .text          0x00404f0c     0x2600 api.o
                0x0040677c                APIShowCurrentProcessInfo
                0x00406faf                api_getchar
                0x004054ae                system11
                0x00405553                refresh_buffer
                0x0040665e                APISetFocus
                0x00405511                system14
                0x0040583a                apiInitBackground
                0x0040654e                APICreateWindow
                0x00406d5e                apiBeginPaint
                0x0040583f                MessageBox
                0x004067fa                APIreplace_window
                0x00406da5                apiGetSystemMetrics
                0x004054f0                system13
                0x00406bf9                apiDown
                0x004062b0                dbProcedure
                0x004068f3                apiExit
                0x00406cad                enterCriticalSection
                0x00406eea                gramadocore_init_execve
                0x00406b61                apiFOpen
                0x004074dd                apiShowWindow
                0x00405364                system1
                0x004053e8                system5
                0x004069d9                api_refresh_screen
                0x00406f2a                apiDialog
                0x00406a65                apiGetCursorY
                0x004057e3                carrega_bitmap_16x16
                0x00406d06                exitCriticalSection
                0x00404f0c                system_call
                0x00406c53                apiUp
                0x00404f34                apiSystem
                0x00406ebe                api_get_window_with_text_input
                0x00407433                apiGetWSScreenWindow
                0x00405532                system15
                0x0040670e                APISetActiveWindow
                0x00406abd                apiSetClientAreaRect
                0x004073ec                apiDrawText
                0x004067d1                APIredraw_window
                0x00406b0f                apiCreateThread
                0x0040577f                SetNextWindowProcedure
                0x0040748b                apiCreateTimer
                0x00406a39                apiGetCursorX
                0x0040574f                chama_procedimento
                0x0040633d                call_kernel
                0x0040745f                apiGetWSMainWindow
                0x004065da                APIRegisterWindow
                0x0040694f                api_strncmp
                0x0040684c                APIminimize_window
                0x00405385                system2
                0x004053a6                system3
                0x00405dbe                DialogBox
                0x00406df7                api_get_current_keyboard_responder
                0x00406ae6                apiCreateProcess
                0x004066a0                APIGetFocus
                0x0040542a                system7
                0x00405409                system6
                0x00406d9b                apiDefDialog
                0x00405d31                mbProcedure
                0x0040661c                APICloseWindow
                0x004073ab                apiSendMessage
                0x00406d32                initializeCriticalSection
                0x0040548d                system10
                0x004057af                set_cursor
                0x00406823                APImaximize_window
                0x00406f20                execve
                0x004069ad                refresh_screen
                0x00406fdb                apiDisplayBMP
                0x004064bd                call_gui
                0x0040546c                system9
                0x00406ef4                fork
                0x00406dce                api_set_current_keyboard_responder
                0x004067a8                APIresize_window
                0x00406d68                apiEndPaint
                0x004057de                put_char
                0x004056ea                print_string
                0x004074b4                apiGetSysTimeInfo
                0x00406a91                apiGetClientAreaRect
                0x00405720                edit_box
                0x0040691e                kill
                0x004069e3                apiReboot
                0x0040580c                apiShutDown
                0x00406e23                api_set_current_mouse_responder
                0x0040689e                APIget_foregroung_window
                0x004053c7                system4
                0x00406b9b                apiSaveFile
                0x00406a0f                apiSetCursor
                0x004054cf                system12
                0x004056ef                vsync
                0x0040544b                system8
                0x00406e78                api_set_window_with_text_input
                0x00406750                APIGetActiveWindow
                0x00406875                APIupdate_window
                0x00406e4c                api_get_current_mouse_responder
                0x00406923                dead_thread_collector
                0x00406b38                apiStartThread
                0x004066cc                APIKillFocus
                0x004068ca                APIset_foregroung_window
                0x00406d72                apiPutChar
 .text          0x0040750c      0x140 status.o
                0x004075aa                update_statuts_bar
                0x0040750c                statusInitializeStatusBar
 .text          0x0040764c       0xa0 addrbar.o
                0x0040764c                topbarInitializeTopBar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004076ec      0x914 00

.rdata          0x00408000      0xde0
 .rdata         0x00408000       0x40 addrbar.o
 .rdata         0x00408040       0x40 status.o
 .rdata         0x00408080      0x3a0 api.o
 .rdata         0x00408420      0x380 stdio.o
                0x00408600                hex2ascii_data
 .rdata         0x004087a0      0x480 stdlib.o
 .rdata         0x00408c20      0x100 ctype.o
                0x00408c20                _ctype
 .rdata         0x00408d20       0xc0 main.o

.data           0x00408de0     0x1220
                0x00408de0                data = .
                0x00408de0                _data = .
                0x00408de0                __data = .
 *(.data)
 .data          0x00408de0      0x460 main.o
                0x00409220                running
 .data          0x00409240        0x0 ctype.o
 .data          0x00409240        0x0 stdlib.o
 .data          0x00409240        0x0 stdio.o
 .data          0x00409240        0x0 string.o
 .data          0x00409240      0x440 api.o
 .data          0x00409680      0x440 status.o
 .data          0x00409ac0      0x440 addrbar.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409f00      0x100 00

.bss            0x0040a000     0xa750
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000       0x30 main.o
 .bss           0x0040a030        0x0 ctype.o
 .bss           0x0040a030     0x8010 stdlib.o
                0x0040a030                environ
 .bss           0x00412040       0x10 stdio.o
 .bss           0x00412050       0x10 string.o
 .bss           0x00412060       0x40 api.o
 .bss           0x004120a0       0x30 status.o
 .bss           0x004120d0       0x30 addrbar.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412100      0xf00 00
 COMMON         0x00413000      0xe10 main.o
                0x00413000                prompt
                0x00413400                ClientAreaInfo
                0x00413410                BufferInfo
                0x00413420                stderr
                0x00413430                prompt_pos
                0x00413440                mWindow
                0x00413450                g_using_gui
                0x00413460                stdin
                0x00413470                rect
                0x00413480                prompt_max
                0x00413490                TOPBAR
                0x004134b0                CurrentWindow
                0x004134c0                prompt_err
                0x004138c0                current_semaphore
                0x004138d0                g_columns
                0x004138e0                stdout
                0x004138f0                Streams
                0x00413970                g_rows
                0x00413980                prompt_out
                0x00413d80                g_cursor_y
                0x00413d90                gWindow
                0x00413da0                CursorInfo
                0x00413db0                STATUSBAR
                0x00413dd0                prompt_status
                0x00413de0                g_char_attrib
                0x00413df0                ApplicationInfo
                0x00413e00                g_cursor_x
 COMMON         0x00413e10      0x900 stdlib.o
                0x00413e10                current_mmblock
                0x00413e20                mm_prev_pointer
                0x00413e30                heap_end
                0x00413e40                g_available_heap
                0x00413e50                heap_start
                0x00413e60                heapCount
                0x00413e70                HEAP_START
                0x00413e80                g_heap_pointer
                0x00413e90                heapList
                0x00414290                randseed
                0x004142a0                HEAP_SIZE
                0x004142b0                last_size
                0x004142c0                last_valid
                0x004142d0                mmblockList
                0x004146d0                libcHeap
                0x004146e0                Heap
                0x004146f0                mmblockCount
                0x00414700                HEAP_END
 COMMON         0x00414710       0x40 api.o
                0x00414710                messagebox_button2
                0x00414720                dialogbox_button1
                0x00414730                messagebox_button1
                0x00414740                dialogbox_button2
                0x00414750                end = .
                0x00414750                _end = .
                0x00414750                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdlib.o
LOAD stdio.o
LOAD string.o
LOAD api.o
LOAD status.o
LOAD addrbar.o
OUTPUT(GFE.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f crt0.o
