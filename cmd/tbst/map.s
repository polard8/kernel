
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
 .text          0x0040414c      0xc60 stdlib.o
                0x00404442                FreeHeap
                0x00404174                rtGetHeapStart
                0x0040474f                free
                0x0040414c                stdlib_system_call
                0x00404678                rand
                0x004045ef                stdlibInitMM
                0x0040444c                heapInit
                0x00404be9                __findenv
                0x00404188                rtGetHeapPointer
                0x00404192                rtGetAvailableHeap
                0x00404695                srand
                0x00404ce9                atoi
                0x0040464f                libcInitRT
                0x0040419c                heapSetLibcHeap
                0x004046cd                stdlib_die
                0x00404cb4                getenv
                0x0040470e                malloc
                0x0040442f                AllocateHeapEx
                0x00404243                AllocateHeap
                0x00404b60                stdlib_strncmp
                0x004046a2                xmalloc
                0x00404bbe                exit
                0x0040417e                rtGetHeapEnd
                0x00404754                system
 .text          0x00404dac        0x0 ctype.o
 .text          0x00404dac      0x430 string.o
                0x00404f98                strcspn
                0x00404efb                strcat
                0x00404dac                strcmp
                0x00404f52                bzero
                0x004050d8                strtok_r
                0x00404e8e                memcpy
                0x00404e65                memoryZeroMemory
                0x00404f2b                bcopy
                0x00404ecb                strcpy
                0x00405038                strspn
                0x004051ad                strtok
                0x00404e07                strncmp
                0x00404f6d                strlen
 .text          0x004051dc     0x2600 api.o
                0x00406a4c                APIShowCurrentProcessInfo
                0x0040727f                api_getchar
                0x0040577e                system11
                0x00405823                refresh_buffer
                0x0040692e                APISetFocus
                0x004057e1                system14
                0x00405b0a                apiInitBackground
                0x0040681e                APICreateWindow
                0x0040702e                apiBeginPaint
                0x00405b0f                MessageBox
                0x00406aca                APIreplace_window
                0x00407075                apiGetSystemMetrics
                0x004057c0                system13
                0x00406ec9                apiDown
                0x00406580                dbProcedure
                0x00406bc3                apiExit
                0x00406f7d                enterCriticalSection
                0x004071ba                gramadocore_init_execve
                0x00406e31                apiFOpen
                0x004077ad                apiShowWindow
                0x00405634                system1
                0x004056b8                system5
                0x00406ca9                api_refresh_screen
                0x004071fa                apiDialog
                0x00406d35                apiGetCursorY
                0x00405ab3                carrega_bitmap_16x16
                0x00406fd6                exitCriticalSection
                0x004051dc                system_call
                0x00406f23                apiUp
                0x00405204                apiSystem
                0x0040718e                api_get_window_with_text_input
                0x00407703                apiGetWSScreenWindow
                0x00405802                system15
                0x004069de                APISetActiveWindow
                0x00406d8d                apiSetClientAreaRect
                0x004076bc                apiDrawText
                0x00406aa1                APIredraw_window
                0x00406ddf                apiCreateThread
                0x00405a4f                SetNextWindowProcedure
                0x0040775b                apiCreateTimer
                0x00406d09                apiGetCursorX
                0x00405a1f                chama_procedimento
                0x0040660d                call_kernel
                0x004068aa                APIRegisterWindow
                0x0040772f                apiGetWSMainWindow
                0x00406c1f                api_strncmp
                0x00406b1c                APIminimize_window
                0x00405655                system2
                0x00405676                system3
                0x0040608e                DialogBox
                0x004070c7                api_get_current_keyboard_responder
                0x00406db6                apiCreateProcess
                0x00406970                APIGetFocus
                0x004056fa                system7
                0x004056d9                system6
                0x0040706b                apiDefDialog
                0x00406001                mbProcedure
                0x004068ec                APICloseWindow
                0x0040767b                apiSendMessage
                0x00407002                initializeCriticalSection
                0x0040575d                system10
                0x00405a7f                set_cursor
                0x00406af3                APImaximize_window
                0x004071f0                execve
                0x00406c7d                refresh_screen
                0x004072ab                apiDisplayBMP
                0x0040678d                call_gui
                0x0040573c                system9
                0x004071c4                fork
                0x0040709e                api_set_current_keyboard_responder
                0x00406a78                APIresize_window
                0x00407038                apiEndPaint
                0x00405aae                put_char
                0x004059ba                print_string
                0x00407784                apiGetSysTimeInfo
                0x00406d61                apiGetClientAreaRect
                0x004059f0                edit_box
                0x00406bee                kill
                0x00406cb3                apiReboot
                0x00405adc                apiShutDown
                0x004070f3                api_set_current_mouse_responder
                0x00406b6e                APIget_foregroung_window
                0x00405697                system4
                0x00406e6b                apiSaveFile
                0x00406cdf                apiSetCursor
                0x0040579f                system12
                0x004059bf                vsync
                0x0040571b                system8
                0x00407148                api_set_window_with_text_input
                0x00406a20                APIGetActiveWindow
                0x00406b45                APIupdate_window
                0x0040711c                api_get_current_mouse_responder
                0x00406bf3                dead_thread_collector
                0x00406e08                apiStartThread
                0x0040699c                APIKillFocus
                0x00406b9a                APIset_foregroung_window
                0x00407042                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004077dc      0x824 00

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
 .data          0x00408dd0        0x0 main.o
 .data          0x00408dd0        0x0 stdio.o
 .data          0x00408dd0        0x0 stdlib.o
 .data          0x00408dd0        0x0 ctype.o
 .data          0x00408dd0        0x0 string.o
 .data          0x00408dd0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409210      0xdf0 00

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
LOAD api.o
OUTPUT(TBST.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
