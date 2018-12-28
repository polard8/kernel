
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
 .text          0x0040100c      0x730 main.o
                0x00401037                newNode
                0x004010ac                exibirEmOrdem
                0x004010eb                exibirPreOrdem
                0x004011a5                insert
                0x004014c2                pop
                0x0040100c                my_isdigit
                0x00401493                push
                0x00401668                testtest_main
                0x0040158e                eval
                0x0040106d                inorder
                0x004014fb                oper
                0x0040121d                bst_main
                0x0040112a                exibirPosOrdem
 .text          0x0040173c     0x2a10 stdio.o
                0x00402149                printf_i2hex
                0x0040237b                putchar
                0x004017f1                stdio_fntos
                0x00402337                sprintf
                0x00402bf4                feof
                0x004021b7                printf2
                0x00402d1a                stdioSetCursor
                0x00402b09                ungetc
                0x00404110                rewind
                0x00401b5a                puts
                0x00402cd2                fputc
                0x00402d70                stdioGetCursorY
                0x00402d9c                scanf
                0x00402a07                fputs
                0x00402c32                ferror
                0x0040255d                input
                0x00401a98                scroll
                0x00402a7c                gets
                0x004023a7                outbyte
                0x00402b70                fileno
                0x00402900                fflush
                0x00402992                fprintf
                0x004040ce                stderr_printf
                0x004026c5                stdio_system_call
                0x00401956                fopen
                0x00402d44                stdioGetCursorX
                0x004026ed                getchar
                0x0040205c                printf_atoi
                0x0040173c                stdio_atoi
                0x0040304c                kvprintf
                0x0040409f                stdout_printf
                0x00402719                stdioInitialize
                0x00402b93                fgetc
                0x004018f0                fclose
                0x00402c58                fseek
                0x004040fd                perror
                0x0040252a                _outbyte
                0x00402b46                ftell
                0x00403fdb                printf
                0x00402041                printf3
                0x00404013                vfprintf
 .text          0x0040414c      0xd70 stdlib.o
                0x00404442                FreeHeap
                0x00404174                rtGetHeapStart
                0x0040474f                free
                0x0040414c                stdlib_system_call
                0x00404678                rand
                0x004045ef                stdlibInitMM
                0x0040444c                heapInit
                0x00404c01                __findenv
                0x00404188                rtGetHeapPointer
                0x00404192                rtGetAvailableHeap
                0x00404695                srand
                0x00404d01                atoi
                0x0040464f                libcInitRT
                0x00404e15                itoa
                0x0040419c                heapSetLibcHeap
                0x00404754                calloc
                0x00404db6                reverse
                0x004046cd                stdlib_die
                0x00404ccc                getenv
                0x0040470e                malloc
                0x0040442f                AllocateHeapEx
                0x00404243                AllocateHeap
                0x00404ba3                stdlib_strncmp
                0x004046a2                xmalloc
                0x0040417e                rtGetHeapEnd
                0x00404797                system
 .text          0x00404ebc        0x0 ctype.o
 .text          0x00404ebc      0x470 string.o
                0x004050f1                strcspn
                0x00405054                strcat
                0x00404ebc                strcmp
                0x004050ab                bzero
                0x00405231                strtok_r
                0x00404fe7                memcpy
                0x00404f75                memset
                0x00404fbe                memoryZeroMemory
                0x00405084                bcopy
                0x00405024                strcpy
                0x00405191                strspn
                0x00405306                strtok
                0x00404f17                strncmp
                0x004050c6                strlen
 .text          0x0040532c       0x90 unistd.o
                0x0040532c                unistd_system_call
                0x00405354                execve
                0x00405389                fork
                0x0040535e                exit
 .text          0x004053bc     0x25d0 api.o
                0x00406c2c                APIShowCurrentProcessInfo
                0x00407429                api_getchar
                0x0040595e                system11
                0x00405a03                refresh_buffer
                0x00406b0e                APISetFocus
                0x004059c1                system14
                0x00405cea                apiInitBackground
                0x004069fe                APICreateWindow
                0x0040720e                apiBeginPaint
                0x00405cef                MessageBox
                0x00406caa                APIreplace_window
                0x00407255                apiGetSystemMetrics
                0x004059a0                system13
                0x004070a9                apiDown
                0x00406760                dbProcedure
                0x00406da3                apiExit
                0x0040715d                enterCriticalSection
                0x0040739a                gramadocore_init_execve
                0x00407011                apiFOpen
                0x00407957                apiShowWindow
                0x00405814                system1
                0x00405898                system5
                0x00406e89                api_refresh_screen
                0x004073a4                apiDialog
                0x00406f15                apiGetCursorY
                0x00405c93                carrega_bitmap_16x16
                0x004071b6                exitCriticalSection
                0x004053bc                system_call
                0x00407103                apiUp
                0x004053e4                apiSystem
                0x0040736e                api_get_window_with_text_input
                0x004078ad                apiGetWSScreenWindow
                0x004059e2                system15
                0x00406bbe                APISetActiveWindow
                0x00406f6d                apiSetClientAreaRect
                0x00407866                apiDrawText
                0x00406c81                APIredraw_window
                0x00406fbf                apiCreateThread
                0x00405c2f                SetNextWindowProcedure
                0x00407905                apiCreateTimer
                0x00406ee9                apiGetCursorX
                0x00405bff                chama_procedimento
                0x004067ed                call_kernel
                0x00406a8a                APIRegisterWindow
                0x004078d9                apiGetWSMainWindow
                0x00406dff                api_strncmp
                0x00406cfc                APIminimize_window
                0x00405835                system2
                0x00405856                system3
                0x0040626e                DialogBox
                0x004072a7                api_get_current_keyboard_responder
                0x00406f96                apiCreateProcess
                0x00406b50                APIGetFocus
                0x004058da                system7
                0x004058b9                system6
                0x0040724b                apiDefDialog
                0x004061e1                mbProcedure
                0x00406acc                APICloseWindow
                0x00407825                apiSendMessage
                0x004071e2                initializeCriticalSection
                0x0040593d                system10
                0x00405c5f                set_cursor
                0x00406cd3                APImaximize_window
                0x00406e5d                refresh_screen
                0x00407455                apiDisplayBMP
                0x0040696d                call_gui
                0x0040591c                system9
                0x0040727e                api_set_current_keyboard_responder
                0x00406c58                APIresize_window
                0x00407218                apiEndPaint
                0x00405c8e                put_char
                0x00405b9a                print_string
                0x0040792e                apiGetSysTimeInfo
                0x00406f41                apiGetClientAreaRect
                0x00405bd0                edit_box
                0x00406dce                kill
                0x00406e93                apiReboot
                0x00405cbc                apiShutDown
                0x004072d3                api_set_current_mouse_responder
                0x00406d4e                APIget_foregroung_window
                0x00405877                system4
                0x0040704b                apiSaveFile
                0x00406ebf                apiSetCursor
                0x0040597f                system12
                0x00405b9f                vsync
                0x004058fb                system8
                0x00407328                api_set_window_with_text_input
                0x00406c00                APIGetActiveWindow
                0x00406d25                APIupdate_window
                0x004072fc                api_get_current_mouse_responder
                0x00406dd3                dead_thread_collector
                0x00406fe8                apiStartThread
                0x00406b7c                APIKillFocus
                0x00406d7a                APIset_foregroung_window
                0x00407222                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x0040798c      0x674 00

.rdata          0x00408000      0xdd0
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x130 main.o

.data           0x00408dd0     0x1230
                0x00408dd0                data = .
                0x00408dd0                _data = .
                0x00408dd0                __data = .
 *(.data)
 .data          0x00408dd0      0x440 main.o
 .data          0x00409210        0x0 stdio.o
 .data          0x00409210        0x0 stdlib.o
 .data          0x00409210        0x0 ctype.o
 .data          0x00409210        0x0 string.o
 .data          0x00409210        0x0 unistd.o
 .data          0x00409210      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409650      0x9b0 00

.bss            0x0040a000    0x12770
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
 .bss           0x00412040        0x0 unistd.o
 .bss           0x00412040     0x8010 api.o
                0x0041b000                . = ALIGN (0x1000)
 *fill*         0x0041a050      0xfb0 00
 COMMON         0x0041b000      0xe30 main.o
                0x0041b000                prompt
                0x0041b400                ClientAreaInfo
                0x0041b410                BufferInfo
                0x0041b420                stderr
                0x0041b430                prompt_pos
                0x0041b440                g_using_gui
                0x0041b450                stdin
                0x0041b460                rect
                0x0041b470                prompt_max
                0x0041b480                CurrentWindow
                0x0041b490                prompt_err
                0x0041b890                current_semaphore
                0x0041b8a0                g_columns
                0x0041b8b0                stdout
                0x0041b8c0                Streams
                0x0041b940                g_rows
                0x0041b950                prompt_out
                0x0041bd50                POS_BUFFER
                0x0041bdd0                g_cursor_y
                0x0041bde0                CursorInfo
                0x0041bdf0                prompt_status
                0x0041be00                g_char_attrib
                0x0041be10                ApplicationInfo
                0x0041be20                g_cursor_x
 COMMON         0x0041be30      0x900 stdlib.o
                0x0041be30                current_mmblock
                0x0041be40                mm_prev_pointer
                0x0041be50                heap_end
                0x0041be60                g_available_heap
                0x0041be70                heap_start
                0x0041be80                heapCount
                0x0041be90                HEAP_START
                0x0041bea0                g_heap_pointer
                0x0041beb0                heapList
                0x0041c2b0                randseed
                0x0041c2c0                HEAP_SIZE
                0x0041c2d0                last_size
                0x0041c2e0                last_valid
                0x0041c2f0                mmblockList
                0x0041c6f0                libcHeap
                0x0041c700                Heap
                0x0041c710                mmblockCount
                0x0041c720                HEAP_END
 COMMON         0x0041c730       0x40 api.o
                0x0041c730                messagebox_button2
                0x0041c740                dialogbox_button1
                0x0041c750                messagebox_button1
                0x0041c760                dialogbox_button2
                0x0041c770                end = .
                0x0041c770                _end = .
                0x0041c770                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD unistd.o
LOAD api.o
OUTPUT(TBST.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
