
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
 .head_x86      0x00401000        0xc head.o
                0x00401000                idle_entry_point
 *(.text)
 .text          0x0040100c      0x5c0 main.o
                0x00401037                newNode
                0x004010ac                exibirEmOrdem
                0x004010eb                exibirPreOrdem
                0x004011a5                insert
                0x00401356                pop
                0x0040100c                my_isdigit
                0x00401327                push
                0x004014fc                testtest_main
                0x00401422                eval
                0x0040106d                inorder
                0x0040138f                oper
                0x0040121d                bst_main
                0x0040112a                exibirPosOrdem
 .text          0x004015cc     0x2a10 stdio.o
                0x00401fd9                printf_i2hex
                0x0040220b                putchar
                0x00401681                stdio_fntos
                0x004021c7                sprintf
                0x00402a84                feof
                0x00402047                printf2
                0x00402baa                stdioSetCursor
                0x00402999                ungetc
                0x00403fa0                rewind
                0x004019ea                puts
                0x00402b62                fputc
                0x00402c00                stdioGetCursorY
                0x00402c2c                scanf
                0x00402897                fputs
                0x00402ac2                ferror
                0x004023ed                input
                0x00401928                scroll
                0x0040290c                gets
                0x00402237                outbyte
                0x00402a00                fileno
                0x00402790                fflush
                0x00402822                fprintf
                0x00403f5e                stderr_printf
                0x00402555                stdio_system_call
                0x004017e6                fopen
                0x00402bd4                stdioGetCursorX
                0x0040257d                getchar
                0x00401eec                printf_atoi
                0x004015cc                stdio_atoi
                0x00402edc                kvprintf
                0x00403f2f                stdout_printf
                0x004025a9                stdioInitialize
                0x00402a23                fgetc
                0x00401780                fclose
                0x00402ae8                fseek
                0x00403f8d                perror
                0x004023ba                _outbyte
                0x004029d6                ftell
                0x00403e6b                printf
                0x00401ed1                printf3
                0x00403ea3                vfprintf
 .text          0x00403fdc      0xc60 stdlib.o
                0x004042d2                FreeHeap
                0x00404004                rtGetHeapStart
                0x004045df                free
                0x00403fdc                stdlib_system_call
                0x00404508                rand
                0x0040447f                stdlibInitMM
                0x004042dc                heapInit
                0x00404a79                __findenv
                0x00404018                rtGetHeapPointer
                0x00404022                rtGetAvailableHeap
                0x00404525                srand
                0x00404b79                atoi
                0x004044df                libcInitRT
                0x0040402c                heapSetLibcHeap
                0x0040455d                stdlib_die
                0x00404b44                getenv
                0x0040459e                malloc
                0x004042bf                AllocateHeapEx
                0x004040d3                AllocateHeap
                0x004049f0                stdlib_strncmp
                0x00404532                xmalloc
                0x00404a4e                exit
                0x0040400e                rtGetHeapEnd
                0x004045e4                system
 .text          0x00404c3c        0x0 ctype.o
 .text          0x00404c3c      0x430 string.o
                0x00404e28                strcspn
                0x00404d8b                strcat
                0x00404c3c                strcmp
                0x00404de2                bzero
                0x00404f68                strtok_r
                0x00404d1e                memcpy
                0x00404cf5                memoryZeroMemory
                0x00404dbb                bcopy
                0x00404d5b                strcpy
                0x00404ec8                strspn
                0x0040503d                strtok
                0x00404c97                strncmp
                0x00404dfd                strlen
 .text          0x0040506c     0x2600 api.o
                0x004068dc                APIShowCurrentProcessInfo
                0x0040710f                api_getchar
                0x0040560e                system11
                0x004056b3                refresh_buffer
                0x004067be                APISetFocus
                0x00405671                system14
                0x0040599a                apiInitBackground
                0x004066ae                APICreateWindow
                0x00406ebe                apiBeginPaint
                0x0040599f                MessageBox
                0x0040695a                APIreplace_window
                0x00406f05                apiGetSystemMetrics
                0x00405650                system13
                0x00406d59                apiDown
                0x00406410                dbProcedure
                0x00406a53                apiExit
                0x00406e0d                enterCriticalSection
                0x0040704a                gramadocore_init_execve
                0x00406cc1                apiFOpen
                0x0040763d                apiShowWindow
                0x004054c4                system1
                0x00405548                system5
                0x00406b39                api_refresh_screen
                0x0040708a                apiDialog
                0x00406bc5                apiGetCursorY
                0x00405943                carrega_bitmap_16x16
                0x00406e66                exitCriticalSection
                0x0040506c                system_call
                0x00406db3                apiUp
                0x00405094                apiSystem
                0x0040701e                api_get_window_with_text_input
                0x00407593                apiGetWSScreenWindow
                0x00405692                system15
                0x0040686e                APISetActiveWindow
                0x00406c1d                apiSetClientAreaRect
                0x0040754c                apiDrawText
                0x00406931                APIredraw_window
                0x00406c6f                apiCreateThread
                0x004058df                SetNextWindowProcedure
                0x004075eb                apiCreateTimer
                0x00406b99                apiGetCursorX
                0x004058af                chama_procedimento
                0x0040649d                call_kernel
                0x0040673a                APIRegisterWindow
                0x004075bf                apiGetWSMainWindow
                0x00406aaf                api_strncmp
                0x004069ac                APIminimize_window
                0x004054e5                system2
                0x00405506                system3
                0x00405f1e                DialogBox
                0x00406f57                api_get_current_keyboard_responder
                0x00406c46                apiCreateProcess
                0x00406800                APIGetFocus
                0x0040558a                system7
                0x00405569                system6
                0x00406efb                apiDefDialog
                0x00405e91                mbProcedure
                0x0040677c                APICloseWindow
                0x0040750b                apiSendMessage
                0x00406e92                initializeCriticalSection
                0x004055ed                system10
                0x0040590f                set_cursor
                0x00406983                APImaximize_window
                0x00407080                execve
                0x00406b0d                refresh_screen
                0x0040713b                apiDisplayBMP
                0x0040661d                call_gui
                0x004055cc                system9
                0x00407054                fork
                0x00406f2e                api_set_current_keyboard_responder
                0x00406908                APIresize_window
                0x00406ec8                apiEndPaint
                0x0040593e                put_char
                0x0040584a                print_string
                0x00407614                apiGetSysTimeInfo
                0x00406bf1                apiGetClientAreaRect
                0x00405880                edit_box
                0x00406a7e                kill
                0x00406b43                apiReboot
                0x0040596c                apiShutDown
                0x00406f83                api_set_current_mouse_responder
                0x004069fe                APIget_foregroung_window
                0x00405527                system4
                0x00406cfb                apiSaveFile
                0x00406b6f                apiSetCursor
                0x0040562f                system12
                0x0040584f                vsync
                0x004055ab                system8
                0x00406fd8                api_set_window_with_text_input
                0x004068b0                APIGetActiveWindow
                0x004069d5                APIupdate_window
                0x00406fac                api_get_current_mouse_responder
                0x00406a83                dead_thread_collector
                0x00406c98                apiStartThread
                0x0040682c                APIKillFocus
                0x00406a2a                APIset_foregroung_window
                0x00406ed2                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x0040766c      0x994 00

.rdata          0x00408000      0xdb0
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x110 main.o

.data           0x00408db0     0x1250
                0x00408db0                data = .
                0x00408db0                _data = .
                0x00408db0                __data = .
 *(.data)
 .data          0x00408db0        0x0 main.o
 .data          0x00408db0        0x0 stdio.o
 .data          0x00408db0        0x0 stdlib.o
 .data          0x00408db0        0x0 ctype.o
 .data          0x00408db0        0x0 string.o
 .data          0x00408db0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x004091f0      0xe10 00

.bss            0x0040a000     0xa770
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
 COMMON         0x00413000      0xe30 main.o
                0x00413000                prompt
                0x00413400                ClientAreaInfo
                0x00413410                BufferInfo
                0x00413420                stderr
                0x00413430                prompt_pos
                0x00413440                g_using_gui
                0x00413450                stdin
                0x00413460                rect
                0x00413470                prompt_max
                0x00413480                CurrentWindow
                0x00413490                prompt_err
                0x00413890                current_semaphore
                0x004138a0                g_columns
                0x004138b0                stdout
                0x004138c0                Streams
                0x00413940                g_rows
                0x00413950                prompt_out
                0x00413d50                POS_BUFFER
                0x00413dd0                g_cursor_y
                0x00413de0                CursorInfo
                0x00413df0                prompt_status
                0x00413e00                g_char_attrib
                0x00413e10                ApplicationInfo
                0x00413e20                g_cursor_x
 COMMON         0x00413e30      0x900 stdlib.o
                0x00413e30                current_mmblock
                0x00413e40                mm_prev_pointer
                0x00413e50                heap_end
                0x00413e60                g_available_heap
                0x00413e70                heap_start
                0x00413e80                heapCount
                0x00413e90                HEAP_START
                0x00413ea0                g_heap_pointer
                0x00413eb0                heapList
                0x004142b0                randseed
                0x004142c0                HEAP_SIZE
                0x004142d0                last_size
                0x004142e0                last_valid
                0x004142f0                mmblockList
                0x004146f0                libcHeap
                0x00414700                Heap
                0x00414710                mmblockCount
                0x00414720                HEAP_END
 COMMON         0x00414730       0x40 api.o
                0x00414730                messagebox_button2
                0x00414740                dialogbox_button1
                0x00414750                messagebox_button1
                0x00414760                dialogbox_button2
                0x00414770                end = .
                0x00414770                _end = .
                0x00414770                __end = .
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
