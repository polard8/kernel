
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
driverInitialized   0x10              main.o
key_saved           0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
STACK_PRE           0x80              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
STACK_OPERAND       0x80              main.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
pre_offset          0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
STACK_OPERATOR      0x80              main.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
operand_offset      0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
operator_offset     0x10              main.o
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
 .text          0x00401038      0xe50 main.o
                0x004017a7                idleInit
                0x00401038                newNode
                0x004010c0                exibirEmOrdem
                0x00401109                exibirPreOrdem
                0x0040126c                insert
                0x00401bd6                TEST_PRINTF3
                0x004017c5                idleServices
                0x00401761                driverInitialize
                0x0040182f                testtest_main
                0x00401874                TEST_PRINTF
                0x00401376                resolve_expressao
                0x0040175c                idleLoop
                0x00401080                inorder
                0x00401b1b                TEST_PRINTF2
                0x00401784                driverUninitialize
                0x00401469                bst_main
                0x00401220                imprimeEmNotacaoPolonesa
                0x00401310                height
                0x004011d7                exibirPosOrdem
 .text          0x00401e88     0x2a00 stdio.o
                0x00402895                printf_i2hex
                0x00402ac7                putchar
                0x00401f3d                stdio_fntos
                0x00402a83                sprintf
                0x00403328                feof
                0x00402903                printf2
                0x0040344e                stdioSetCursor
                0x0040323d                ungetc
                0x00404844                rewind
                0x004022a6                puts
                0x00403406                fputc
                0x004034a4                stdioGetCursorY
                0x004034d0                scanf
                0x00403153                fputs
                0x00403366                ferror
                0x00402ca9                input
                0x004021e4                scroll
                0x004031c8                gets
                0x00402af3                outbyte
                0x004032a4                fileno
                0x0040304c                fflush
                0x004030de                fprintf
                0x00404802                stderr_printf
                0x00402e11                stdio_system_call
                0x004020a2                fopen
                0x00403478                stdioGetCursorX
                0x00402e39                getchar
                0x004027a8                printf_atoi
                0x00401e88                stdio_atoi
                0x00403780                kvprintf
                0x004047d3                stdout_printf
                0x00402e65                stdioInitialize
                0x004032c7                fgetc
                0x0040203c                fclose
                0x0040338c                fseek
                0x00404831                perror
                0x00402c76                _outbyte
                0x0040327a                ftell
                0x0040470f                printf
                0x0040278d                printf3
                0x00404747                vfprintf
 .text          0x00404888      0xc60 stdlib.o
                0x00404b7e                FreeHeap
                0x004048b0                rtGetHeapStart
                0x00404e8b                free
                0x00404888                stdlib_system_call
                0x00404db4                rand
                0x00404d2b                stdlibInitMM
                0x00404b88                heapInit
                0x00405325                __findenv
                0x004048c4                rtGetHeapPointer
                0x004048ce                rtGetAvailableHeap
                0x00404dd1                srand
                0x00405425                atoi
                0x00404d8b                libcInitRT
                0x004048d8                heapSetLibcHeap
                0x00404e09                stdlib_die
                0x004053f0                getenv
                0x00404e4a                malloc
                0x00404b6b                AllocateHeapEx
                0x0040497f                AllocateHeap
                0x0040529c                stdlib_strncmp
                0x00404dde                xmalloc
                0x004052fa                exit
                0x004048ba                rtGetHeapEnd
                0x00404e90                system
 .text          0x004054e8        0x0 ctype.o
 .text          0x004054e8      0x430 string.o
                0x004056d4                strcspn
                0x00405637                strcat
                0x004054e8                strcmp
                0x0040568e                bzero
                0x00405814                strtok_r
                0x004055ca                memcpy
                0x004055a1                memoryZeroMemory
                0x00405667                bcopy
                0x00405607                strcpy
                0x00405774                strspn
                0x004058e9                strtok
                0x00405543                strncmp
                0x004056a9                strlen
 .text          0x00405918     0x2600 api.o
                0x00407188                APIShowCurrentProcessInfo
                0x004079bb                api_getchar
                0x00405eba                system11
                0x00405f5f                refresh_buffer
                0x0040706a                APISetFocus
                0x00405f1d                system14
                0x00406246                apiInitBackground
                0x00406f5a                APICreateWindow
                0x0040776a                apiBeginPaint
                0x0040624b                MessageBox
                0x00407206                APIreplace_window
                0x004077b1                apiGetSystemMetrics
                0x00405efc                system13
                0x00407605                apiDown
                0x00406cbc                dbProcedure
                0x004072ff                apiExit
                0x004076b9                enterCriticalSection
                0x004078f6                gramadocore_init_execve
                0x0040756d                apiFOpen
                0x00407ee9                apiShowWindow
                0x00405d70                system1
                0x00405df4                system5
                0x004073e5                api_refresh_screen
                0x00407936                apiDialog
                0x00407471                apiGetCursorY
                0x004061ef                carrega_bitmap_16x16
                0x00407712                exitCriticalSection
                0x00405918                system_call
                0x0040765f                apiUp
                0x00405940                apiSystem
                0x004078ca                api_get_window_with_text_input
                0x00407e3f                apiGetWSScreenWindow
                0x00405f3e                system15
                0x0040711a                APISetActiveWindow
                0x004074c9                apiSetClientAreaRect
                0x00407df8                apiDrawText
                0x004071dd                APIredraw_window
                0x0040751b                apiCreateThread
                0x0040618b                SetNextWindowProcedure
                0x00407e97                apiCreateTimer
                0x00407445                apiGetCursorX
                0x0040615b                chama_procedimento
                0x00406d49                call_kernel
                0x00406fe6                APIRegisterWindow
                0x00407e6b                apiGetWSMainWindow
                0x0040735b                api_strncmp
                0x00407258                APIminimize_window
                0x00405d91                system2
                0x00405db2                system3
                0x004067ca                DialogBox
                0x00407803                api_get_current_keyboard_responder
                0x004074f2                apiCreateProcess
                0x004070ac                APIGetFocus
                0x00405e36                system7
                0x00405e15                system6
                0x004077a7                apiDefDialog
                0x0040673d                mbProcedure
                0x00407028                APICloseWindow
                0x00407db7                apiSendMessage
                0x0040773e                initializeCriticalSection
                0x00405e99                system10
                0x004061bb                set_cursor
                0x0040722f                APImaximize_window
                0x0040792c                execve
                0x004073b9                refresh_screen
                0x004079e7                apiDisplayBMP
                0x00406ec9                call_gui
                0x00405e78                system9
                0x00407900                fork
                0x004077da                api_set_current_keyboard_responder
                0x004071b4                APIresize_window
                0x00407774                apiEndPaint
                0x004061ea                put_char
                0x004060f6                print_string
                0x00407ec0                apiGetSysTimeInfo
                0x0040749d                apiGetClientAreaRect
                0x0040612c                edit_box
                0x0040732a                kill
                0x004073ef                apiReboot
                0x00406218                apiShutDown
                0x0040782f                api_set_current_mouse_responder
                0x004072aa                APIget_foregroung_window
                0x00405dd3                system4
                0x004075a7                apiSaveFile
                0x0040741b                apiSetCursor
                0x00405edb                system12
                0x004060fb                vsync
                0x00405e57                system8
                0x00407884                api_set_window_with_text_input
                0x0040715c                APIGetActiveWindow
                0x00407281                APIupdate_window
                0x00407858                api_get_current_mouse_responder
                0x0040732f                dead_thread_collector
                0x00407544                apiStartThread
                0x004070d8                APIKillFocus
                0x004072d6                APIset_foregroung_window
                0x0040777e                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407f18       0xe8 00

.rdata          0x00408000      0xfc0
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x320 main.o

.data           0x00408fc0     0x1040
                0x00408fc0                data = .
                0x00408fc0                _data = .
                0x00408fc0                __data = .
 *(.data)
 .data          0x00408fc0        0x0 main.o
 .data          0x00408fc0        0x0 stdio.o
 .data          0x00408fc0        0x0 stdlib.o
 .data          0x00408fc0        0x0 ctype.o
 .data          0x00408fc0        0x0 string.o
 .data          0x00408fc0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409400      0xc00 00

.bss            0x0040a000     0xa8e0
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
 COMMON         0x00413000      0xfa0 main.o
                0x00413000                prompt
                0x00413400                idleStatus
                0x00413410                ClientAreaInfo
                0x00413420                BufferInfo
                0x00413430                driverInitialized
                0x00413440                key_saved
                0x00413450                stderr
                0x00413460                prompt_pos
                0x00413470                STACK_PRE
                0x004134f0                g_using_gui
                0x00413500                stdin
                0x00413510                STACK_OPERAND
                0x00413590                rect
                0x004135a0                prompt_max
                0x004135b0                pre_offset
                0x004135c0                CurrentWindow
                0x004135d0                STACK_OPERATOR
                0x00413650                prompt_err
                0x00413a50                current_semaphore
                0x00413a60                g_columns
                0x00413a70                operand_offset
                0x00413a80                stdout
                0x00413a90                Streams
                0x00413b10                g_rows
                0x00413b20                operator_offset
                0x00413b30                prompt_out
                0x00413f30                g_cursor_y
                0x00413f40                CursorInfo
                0x00413f50                prompt_status
                0x00413f60                g_char_attrib
                0x00413f70                ApplicationInfo
                0x00413f80                idleError
                0x00413f90                g_cursor_x
 COMMON         0x00413fa0      0x900 stdlib.o
                0x00413fa0                current_mmblock
                0x00413fb0                mm_prev_pointer
                0x00413fc0                heap_end
                0x00413fd0                g_available_heap
                0x00413fe0                heap_start
                0x00413ff0                heapCount
                0x00414000                HEAP_START
                0x00414010                g_heap_pointer
                0x00414020                heapList
                0x00414420                randseed
                0x00414430                HEAP_SIZE
                0x00414440                last_size
                0x00414450                last_valid
                0x00414460                mmblockList
                0x00414860                libcHeap
                0x00414870                Heap
                0x00414880                mmblockCount
                0x00414890                HEAP_END
 COMMON         0x004148a0       0x40 api.o
                0x004148a0                messagebox_button2
                0x004148b0                dialogbox_button1
                0x004148c0                messagebox_button1
                0x004148d0                dialogbox_button2
                0x004148e0                end = .
                0x004148e0                _end = .
                0x004148e0                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TBST2.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
