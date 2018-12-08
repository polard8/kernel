
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
 .text          0x00401038      0x9e0 main.o
                0x0040133e                idleInit
                0x00401038                newNode
                0x004010ad                exibirEmOrdem
                0x004010ec                exibirPreOrdem
                0x0040116a                insert
                0x0040176d                TEST_PRINTF3
                0x0040135c                idleServices
                0x004012f8                driverInitialize
                0x004013c6                testtest_main
                0x0040140b                TEST_PRINTF
                0x004012f3                idleLoop
                0x0040106e                inorder
                0x004016b2                TEST_PRINTF2
                0x0040131b                driverUninitialize
                0x004011e2                bst_main
                0x0040112b                exibirPosOrdem
 .text          0x00401a18     0x2a00 stdio.o
                0x00402425                printf_i2hex
                0x00402657                putchar
                0x00401acd                stdio_fntos
                0x00402613                sprintf
                0x00402eb8                feof
                0x00402493                printf2
                0x00402fde                stdioSetCursor
                0x00402dcd                ungetc
                0x004043d4                rewind
                0x00401e36                puts
                0x00402f96                fputc
                0x00403034                stdioGetCursorY
                0x00403060                scanf
                0x00402ce3                fputs
                0x00402ef6                ferror
                0x00402839                input
                0x00401d74                scroll
                0x00402d58                gets
                0x00402683                outbyte
                0x00402e34                fileno
                0x00402bdc                fflush
                0x00402c6e                fprintf
                0x00404392                stderr_printf
                0x004029a1                stdio_system_call
                0x00401c32                fopen
                0x00403008                stdioGetCursorX
                0x004029c9                getchar
                0x00402338                printf_atoi
                0x00401a18                stdio_atoi
                0x00403310                kvprintf
                0x00404363                stdout_printf
                0x004029f5                stdioInitialize
                0x00402e57                fgetc
                0x00401bcc                fclose
                0x00402f1c                fseek
                0x004043c1                perror
                0x00402806                _outbyte
                0x00402e0a                ftell
                0x0040429f                printf
                0x0040231d                printf3
                0x004042d7                vfprintf
 .text          0x00404418      0xc60 stdlib.o
                0x0040470e                FreeHeap
                0x00404440                rtGetHeapStart
                0x00404a1b                free
                0x00404418                stdlib_system_call
                0x00404944                rand
                0x004048bb                stdlibInitMM
                0x00404718                heapInit
                0x00404eb5                __findenv
                0x00404454                rtGetHeapPointer
                0x0040445e                rtGetAvailableHeap
                0x00404961                srand
                0x00404fb5                atoi
                0x0040491b                libcInitRT
                0x00404468                heapSetLibcHeap
                0x00404999                stdlib_die
                0x00404f80                getenv
                0x004049da                malloc
                0x004046fb                AllocateHeapEx
                0x0040450f                AllocateHeap
                0x00404e2c                stdlib_strncmp
                0x0040496e                xmalloc
                0x00404e8a                exit
                0x0040444a                rtGetHeapEnd
                0x00404a20                system
 .text          0x00405078        0x0 ctype.o
 .text          0x00405078      0x430 string.o
                0x00405264                strcspn
                0x004051c7                strcat
                0x00405078                strcmp
                0x0040521e                bzero
                0x004053a4                strtok_r
                0x0040515a                memcpy
                0x00405131                memoryZeroMemory
                0x004051f7                bcopy
                0x00405197                strcpy
                0x00405304                strspn
                0x00405479                strtok
                0x004050d3                strncmp
                0x00405239                strlen
 .text          0x004054a8     0x2600 api.o
                0x00406d18                APIShowCurrentProcessInfo
                0x0040754b                api_getchar
                0x00405a4a                system11
                0x00405aef                refresh_buffer
                0x00406bfa                APISetFocus
                0x00405aad                system14
                0x00405dd6                apiInitBackground
                0x00406aea                APICreateWindow
                0x004072fa                apiBeginPaint
                0x00405ddb                MessageBox
                0x00406d96                APIreplace_window
                0x00407341                apiGetSystemMetrics
                0x00405a8c                system13
                0x00407195                apiDown
                0x0040684c                dbProcedure
                0x00406e8f                apiExit
                0x00407249                enterCriticalSection
                0x00407486                gramadocore_init_execve
                0x004070fd                apiFOpen
                0x00407a79                apiShowWindow
                0x00405900                system1
                0x00405984                system5
                0x00406f75                api_refresh_screen
                0x004074c6                apiDialog
                0x00407001                apiGetCursorY
                0x00405d7f                carrega_bitmap_16x16
                0x004072a2                exitCriticalSection
                0x004054a8                system_call
                0x004071ef                apiUp
                0x004054d0                apiSystem
                0x0040745a                api_get_window_with_text_input
                0x004079cf                apiGetWSScreenWindow
                0x00405ace                system15
                0x00406caa                APISetActiveWindow
                0x00407059                apiSetClientAreaRect
                0x00407988                apiDrawText
                0x00406d6d                APIredraw_window
                0x004070ab                apiCreateThread
                0x00405d1b                SetNextWindowProcedure
                0x00407a27                apiCreateTimer
                0x00406fd5                apiGetCursorX
                0x00405ceb                chama_procedimento
                0x004068d9                call_kernel
                0x00406b76                APIRegisterWindow
                0x004079fb                apiGetWSMainWindow
                0x00406eeb                api_strncmp
                0x00406de8                APIminimize_window
                0x00405921                system2
                0x00405942                system3
                0x0040635a                DialogBox
                0x00407393                api_get_current_keyboard_responder
                0x00407082                apiCreateProcess
                0x00406c3c                APIGetFocus
                0x004059c6                system7
                0x004059a5                system6
                0x00407337                apiDefDialog
                0x004062cd                mbProcedure
                0x00406bb8                APICloseWindow
                0x00407947                apiSendMessage
                0x004072ce                initializeCriticalSection
                0x00405a29                system10
                0x00405d4b                set_cursor
                0x00406dbf                APImaximize_window
                0x004074bc                execve
                0x00406f49                refresh_screen
                0x00407577                apiDisplayBMP
                0x00406a59                call_gui
                0x00405a08                system9
                0x00407490                fork
                0x0040736a                api_set_current_keyboard_responder
                0x00406d44                APIresize_window
                0x00407304                apiEndPaint
                0x00405d7a                put_char
                0x00405c86                print_string
                0x00407a50                apiGetSysTimeInfo
                0x0040702d                apiGetClientAreaRect
                0x00405cbc                edit_box
                0x00406eba                kill
                0x00406f7f                apiReboot
                0x00405da8                apiShutDown
                0x004073bf                api_set_current_mouse_responder
                0x00406e3a                APIget_foregroung_window
                0x00405963                system4
                0x00407137                apiSaveFile
                0x00406fab                apiSetCursor
                0x00405a6b                system12
                0x00405c8b                vsync
                0x004059e7                system8
                0x00407414                api_set_window_with_text_input
                0x00406cec                APIGetActiveWindow
                0x00406e11                APIupdate_window
                0x004073e8                api_get_current_mouse_responder
                0x00406ebf                dead_thread_collector
                0x004070d4                apiStartThread
                0x00406c68                APIKillFocus
                0x00406e66                APIset_foregroung_window
                0x0040730e                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407aa8      0x558 00

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
OUTPUT(TBST.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
