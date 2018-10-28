
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
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038      0x130 main.o
                0x00401038                app_test
 .text          0x00401168     0x1360 stdio.o
                0x0040197e                putchar
                0x00401168                stdio_fntos
                0x0040193a                sprintf
                0x004020ac                feof
                0x004021d2                stdioSetCursor
                0x0040200e                ungetc
                0x00401438                puts
                0x0040218a                fputc
                0x00402228                stdioGetCursorY
                0x00402309                scanf
                0x00401f24                fputs
                0x004020ea                ferror
                0x00401b60                input
                0x00401376                scroll
                0x00401f99                gets
                0x004019aa                outbyte
                0x00401e40                fflush
                0x00401eaf                fprintf
                0x00401cc8                stdio_system_call
                0x004012bd                fopen
                0x004021fc                stdioGetCursorX
                0x00401cf0                getchar
                0x00402254                stdio_atoi
                0x00401d1c                stdioInitialize
                0x0040204b                fgetc
                0x00401257                fclose
                0x00402110                fseek
                0x00401b2d                _outbyte
                0x0040191f                printf
 .text          0x004024c8      0xaf0 stdlib.o
                0x004027be                FreeHeap
                0x004024f0                rtGetHeapStart
                0x00402a12                free
                0x004024c8                stdlib_system_call
                0x004029a7                rand
                0x0040291e                stdlibInitMM
                0x004027c8                heapInit
                0x00402eac                __findenv
                0x00402504                rtGetHeapPointer
                0x0040250e                rtGetAvailableHeap
                0x004029c4                srand
                0x0040297e                libcInitRT
                0x00402518                heapSetLibcHeap
                0x00402f77                getenv
                0x004029d1                malloc
                0x004027ab                AllocateHeapEx
                0x004025bf                AllocateHeap
                0x00402e23                stdlib_strncmp
                0x00402e81                exit
                0x004024fa                rtGetHeapEnd
                0x00402a17                system
 .text          0x00402fb8       0xe0 ctype.o
                0x00403052                isspace
                0x00403078                isxdigit
                0x00403065                isupper
                0x00402fcb                isalpha
                0x00403017                islower
                0x00402fb8                isalnum
                0x0040302a                isprint
                0x00403004                isgraph
                0x00402ff1                isdigit
                0x00402fde                iscntrl
                0x0040303f                ispunct
 .text          0x00403098      0x430 string.o
                0x00403284                strcspn
                0x004031e7                strcat
                0x00403098                strcmp
                0x0040323e                bzero
                0x004033c4                strtok_r
                0x0040317a                memcpy
                0x00403151                memoryZeroMemory
                0x00403217                bcopy
                0x004031b7                strcpy
                0x00403324                strspn
                0x00403499                strtok
                0x004030f3                strncmp
                0x00403259                strlen
 .text          0x004034c8     0x2550 api.o
                0x00404d52                APIShowCurrentProcessInfo
                0x00405585                api_getchar
                0x00403a6a                system11
                0x00403b0f                refresh_buffer
                0x00404c34                APISetFocus
                0x00403acd                system14
                0x00403df6                apiInitBackground
                0x00404b24                APICreateWindow
                0x00405334                apiBeginPaint
                0x00403dfb                MessageBox
                0x00404dd0                APIreplace_window
                0x0040537b                apiGetSystemMetrics
                0x00403aac                system13
                0x004051cf                apiDown
                0x00404886                dbProcedure
                0x00404ec9                apiExit
                0x00405283                enterCriticalSection
                0x004054c0                gramadocore_init_execve
                0x00405137                apiFOpen
                0x00403920                system1
                0x004039a4                system5
                0x00404faf                api_refresh_screen
                0x00405500                apiDialog
                0x0040503b                apiGetCursorY
                0x00403d9f                carrega_bitmap_16x16
                0x004052dc                exitCriticalSection
                0x004034c8                system_call
                0x00405229                apiUp
                0x004034f0                apiSystem
                0x00405494                api_get_window_with_text_input
                0x00403aee                system15
                0x00404ce4                APISetActiveWindow
                0x00405093                apiSetClientAreaRect
                0x004059c2                apiDrawText
                0x00404da7                APIredraw_window
                0x004050e5                apiCreateThread
                0x00403d3b                SetNextWindowProcedure
                0x0040500f                apiGetCursorX
                0x00403d0b                chama_procedimento
                0x00404913                call_kernel
                0x00404bb0                APIRegisterWindow
                0x00404f25                api_strncmp
                0x00404e22                APIminimize_window
                0x00403941                system2
                0x00403962                system3
                0x00404387                DialogBox
                0x004053cd                api_get_current_keyboard_responder
                0x004050bc                apiCreateProcess
                0x00404c76                APIGetFocus
                0x004039e6                system7
                0x004039c5                system6
                0x00405371                apiDefDialog
                0x004042fa                mbProcedure
                0x00404bf2                APICloseWindow
                0x00405981                apiSendMessage
                0x00405308                initializeCriticalSection
                0x00403a49                system10
                0x00403d6b                set_cursor
                0x00404df9                APImaximize_window
                0x004054f6                execve
                0x00404f83                refresh_screen
                0x004055b1                apiDisplayBMP
                0x00404a93                call_gui
                0x00403a28                system9
                0x004054ca                fork
                0x004053a4                api_set_current_keyboard_responder
                0x00404d7e                APIresize_window
                0x0040533e                apiEndPaint
                0x00403d9a                put_char
                0x00403ca6                print_string
                0x00405067                apiGetClientAreaRect
                0x00403cdc                edit_box
                0x00404ef4                kill
                0x00404fb9                apiReboot
                0x00403dc8                apiShutDown
                0x004053f9                api_set_current_mouse_responder
                0x00404e74                APIget_foregroung_window
                0x00403983                system4
                0x00405171                apiSaveFile
                0x00404fe5                apiSetCursor
                0x00403a8b                system12
                0x00403cab                vsync
                0x00403a07                system8
                0x0040544e                api_set_window_with_text_input
                0x00404d26                APIGetActiveWindow
                0x00404e4b                APIupdate_window
                0x00405422                api_get_current_mouse_responder
                0x00404ef9                dead_thread_collector
                0x0040510e                apiStartThread
                0x00404ca2                APIKillFocus
                0x00404ea0                APIset_foregroung_window
                0x00405348                apiPutChar
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405a18      0x5e8 00

.rdata          0x00406000      0x910
 .rdata         0x00406000      0x3e0 api.o
 .rdata         0x004063e0      0x460 stdlib.o
 .rdata         0x00406840       0x70 stdio.o
 .rdata         0x004068b0       0x60 main.o

.data           0x00406910     0x16f0
                0x00406910                data = .
                0x00406910                _data = .
                0x00406910                __data = .
 *(.data)
 .data          0x00406910      0x440 main.o
 .data          0x00406d50        0x0 stdio.o
 .data          0x00406d50        0x0 stdlib.o
 .data          0x00406d50      0x120 ctype.o
                0x00406d50                _ctype_
 .data          0x00406e70        0x0 string.o
 .data          0x00406e70      0x440 api.o
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004072b0      0xd50 00

.bss            0x00408000     0xa6f0
                0x00408000                bss = .
                0x00408000                _bss = .
                0x00408000                __bss = .
 *(.bss)
 .bss           0x00408000        0x0 main.o
 .bss           0x00408000       0x10 stdio.o
 .bss           0x00408010     0x8010 stdlib.o
                0x00408010                environ
 .bss           0x00410020        0x0 ctype.o
 .bss           0x00410020       0x10 string.o
 .bss           0x00410030       0x40 api.o
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
 COMMON         0x00411db0      0x900 stdlib.o
                0x00411db0                current_mmblock
                0x00411dc0                mm_prev_pointer
                0x00411dd0                heap_end
                0x00411de0                g_available_heap
                0x00411df0                heap_start
                0x00411e00                heapCount
                0x00411e10                HEAP_START
                0x00411e20                g_heap_pointer
                0x00411e30                heapList
                0x00412230                randseed
                0x00412240                HEAP_SIZE
                0x00412250                last_size
                0x00412260                last_valid
                0x00412270                mmblockList
                0x00412670                libcHeap
                0x00412680                Heap
                0x00412690                mmblockCount
                0x004126a0                HEAP_END
 COMMON         0x004126b0       0x40 api.o
                0x004126b0                messagebox_button2
                0x004126c0                dialogbox_button1
                0x004126d0                messagebox_button1
                0x004126e0                dialogbox_button2
                0x004126f0                end = .
                0x004126f0                _end = .
                0x004126f0                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TPRINTF.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
