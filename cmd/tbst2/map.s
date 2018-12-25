
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
 .text          0x00401e88     0x2a10 stdio.o
                0x00402895                printf_i2hex
                0x00402ac7                putchar
                0x00401f3d                stdio_fntos
                0x00402a83                sprintf
                0x00403340                feof
                0x00402903                printf2
                0x00403466                stdioSetCursor
                0x00403255                ungetc
                0x0040485c                rewind
                0x004022a6                puts
                0x0040341e                fputc
                0x004034bc                stdioGetCursorY
                0x004034e8                scanf
                0x00403153                fputs
                0x0040337e                ferror
                0x00402ca9                input
                0x004021e4                scroll
                0x004031c8                gets
                0x00402af3                outbyte
                0x004032bc                fileno
                0x0040304c                fflush
                0x004030de                fprintf
                0x0040481a                stderr_printf
                0x00402e11                stdio_system_call
                0x004020a2                fopen
                0x00403490                stdioGetCursorX
                0x00402e39                getchar
                0x004027a8                printf_atoi
                0x00401e88                stdio_atoi
                0x00403798                kvprintf
                0x004047eb                stdout_printf
                0x00402e65                stdioInitialize
                0x004032df                fgetc
                0x0040203c                fclose
                0x004033a4                fseek
                0x00404849                perror
                0x00402c76                _outbyte
                0x00403292                ftell
                0x00404727                printf
                0x0040278d                printf3
                0x0040475f                vfprintf
 .text          0x00404898      0xc60 stdlib.o
                0x00404b8e                FreeHeap
                0x004048c0                rtGetHeapStart
                0x00404e9b                free
                0x00404898                stdlib_system_call
                0x00404dc4                rand
                0x00404d3b                stdlibInitMM
                0x00404b98                heapInit
                0x00405335                __findenv
                0x004048d4                rtGetHeapPointer
                0x004048de                rtGetAvailableHeap
                0x00404de1                srand
                0x00405435                atoi
                0x00404d9b                libcInitRT
                0x004048e8                heapSetLibcHeap
                0x00404e19                stdlib_die
                0x00405400                getenv
                0x00404e5a                malloc
                0x00404b7b                AllocateHeapEx
                0x0040498f                AllocateHeap
                0x004052ac                stdlib_strncmp
                0x00404dee                xmalloc
                0x0040530a                exit
                0x004048ca                rtGetHeapEnd
                0x00404ea0                system
 .text          0x004054f8        0x0 ctype.o
 .text          0x004054f8      0x430 string.o
                0x004056e4                strcspn
                0x00405647                strcat
                0x004054f8                strcmp
                0x0040569e                bzero
                0x00405824                strtok_r
                0x004055da                memcpy
                0x004055b1                memoryZeroMemory
                0x00405677                bcopy
                0x00405617                strcpy
                0x00405784                strspn
                0x004058f9                strtok
                0x00405553                strncmp
                0x004056b9                strlen
 .text          0x00405928     0x2600 api.o
                0x00407198                APIShowCurrentProcessInfo
                0x004079cb                api_getchar
                0x00405eca                system11
                0x00405f6f                refresh_buffer
                0x0040707a                APISetFocus
                0x00405f2d                system14
                0x00406256                apiInitBackground
                0x00406f6a                APICreateWindow
                0x0040777a                apiBeginPaint
                0x0040625b                MessageBox
                0x00407216                APIreplace_window
                0x004077c1                apiGetSystemMetrics
                0x00405f0c                system13
                0x00407615                apiDown
                0x00406ccc                dbProcedure
                0x0040730f                apiExit
                0x004076c9                enterCriticalSection
                0x00407906                gramadocore_init_execve
                0x0040757d                apiFOpen
                0x00407ef9                apiShowWindow
                0x00405d80                system1
                0x00405e04                system5
                0x004073f5                api_refresh_screen
                0x00407946                apiDialog
                0x00407481                apiGetCursorY
                0x004061ff                carrega_bitmap_16x16
                0x00407722                exitCriticalSection
                0x00405928                system_call
                0x0040766f                apiUp
                0x00405950                apiSystem
                0x004078da                api_get_window_with_text_input
                0x00407e4f                apiGetWSScreenWindow
                0x00405f4e                system15
                0x0040712a                APISetActiveWindow
                0x004074d9                apiSetClientAreaRect
                0x00407e08                apiDrawText
                0x004071ed                APIredraw_window
                0x0040752b                apiCreateThread
                0x0040619b                SetNextWindowProcedure
                0x00407ea7                apiCreateTimer
                0x00407455                apiGetCursorX
                0x0040616b                chama_procedimento
                0x00406d59                call_kernel
                0x00406ff6                APIRegisterWindow
                0x00407e7b                apiGetWSMainWindow
                0x0040736b                api_strncmp
                0x00407268                APIminimize_window
                0x00405da1                system2
                0x00405dc2                system3
                0x004067da                DialogBox
                0x00407813                api_get_current_keyboard_responder
                0x00407502                apiCreateProcess
                0x004070bc                APIGetFocus
                0x00405e46                system7
                0x00405e25                system6
                0x004077b7                apiDefDialog
                0x0040674d                mbProcedure
                0x00407038                APICloseWindow
                0x00407dc7                apiSendMessage
                0x0040774e                initializeCriticalSection
                0x00405ea9                system10
                0x004061cb                set_cursor
                0x0040723f                APImaximize_window
                0x0040793c                execve
                0x004073c9                refresh_screen
                0x004079f7                apiDisplayBMP
                0x00406ed9                call_gui
                0x00405e88                system9
                0x00407910                fork
                0x004077ea                api_set_current_keyboard_responder
                0x004071c4                APIresize_window
                0x00407784                apiEndPaint
                0x004061fa                put_char
                0x00406106                print_string
                0x00407ed0                apiGetSysTimeInfo
                0x004074ad                apiGetClientAreaRect
                0x0040613c                edit_box
                0x0040733a                kill
                0x004073ff                apiReboot
                0x00406228                apiShutDown
                0x0040783f                api_set_current_mouse_responder
                0x004072ba                APIget_foregroung_window
                0x00405de3                system4
                0x004075b7                apiSaveFile
                0x0040742b                apiSetCursor
                0x00405eeb                system12
                0x0040610b                vsync
                0x00405e67                system8
                0x00407894                api_set_window_with_text_input
                0x0040716c                APIGetActiveWindow
                0x00407291                APIupdate_window
                0x00407868                api_get_current_mouse_responder
                0x0040733f                dead_thread_collector
                0x00407554                apiStartThread
                0x004070e8                APIKillFocus
                0x004072e6                APIset_foregroung_window
                0x0040778e                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407f28       0xd8 00

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

.bss            0x0040a000    0x128e0
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
 .bss           0x00412030     0x8010 api.o
                0x0041b000                . = ALIGN (0x1000)
 *fill*         0x0041a040      0xfc0 00
 COMMON         0x0041b000      0xfa0 main.o
                0x0041b000                prompt
                0x0041b400                idleStatus
                0x0041b410                ClientAreaInfo
                0x0041b420                BufferInfo
                0x0041b430                driverInitialized
                0x0041b440                key_saved
                0x0041b450                stderr
                0x0041b460                prompt_pos
                0x0041b470                STACK_PRE
                0x0041b4f0                g_using_gui
                0x0041b500                stdin
                0x0041b510                STACK_OPERAND
                0x0041b590                rect
                0x0041b5a0                prompt_max
                0x0041b5b0                pre_offset
                0x0041b5c0                CurrentWindow
                0x0041b5d0                STACK_OPERATOR
                0x0041b650                prompt_err
                0x0041ba50                current_semaphore
                0x0041ba60                g_columns
                0x0041ba70                operand_offset
                0x0041ba80                stdout
                0x0041ba90                Streams
                0x0041bb10                g_rows
                0x0041bb20                operator_offset
                0x0041bb30                prompt_out
                0x0041bf30                g_cursor_y
                0x0041bf40                CursorInfo
                0x0041bf50                prompt_status
                0x0041bf60                g_char_attrib
                0x0041bf70                ApplicationInfo
                0x0041bf80                idleError
                0x0041bf90                g_cursor_x
 COMMON         0x0041bfa0      0x900 stdlib.o
                0x0041bfa0                current_mmblock
                0x0041bfb0                mm_prev_pointer
                0x0041bfc0                heap_end
                0x0041bfd0                g_available_heap
                0x0041bfe0                heap_start
                0x0041bff0                heapCount
                0x0041c000                HEAP_START
                0x0041c010                g_heap_pointer
                0x0041c020                heapList
                0x0041c420                randseed
                0x0041c430                HEAP_SIZE
                0x0041c440                last_size
                0x0041c450                last_valid
                0x0041c460                mmblockList
                0x0041c860                libcHeap
                0x0041c870                Heap
                0x0041c880                mmblockCount
                0x0041c890                HEAP_END
 COMMON         0x0041c8a0       0x40 api.o
                0x0041c8a0                messagebox_button2
                0x0041c8b0                dialogbox_button1
                0x0041c8c0                messagebox_button1
                0x0041c8d0                dialogbox_button2
                0x0041c8e0                end = .
                0x0041c8e0                _end = .
                0x0041c8e0                __end = .
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
