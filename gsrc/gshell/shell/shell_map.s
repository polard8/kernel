
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              crt0.o
shellError          0x10              main.o
stderr              0x10              crt0.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
root                0x10              main.o
mm_prev_pointer     0x10              stdlib.o
shell_info          0x20              main.o
shellScreenBufferMaxColumns
                    0x10              main.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
shell_window_x      0x10              main.o
i2Window            0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              crt0.o
pwd                 0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
shellScreenBufferMaxRows
                    0x10              main.o
shellScreenWidth    0x10              main.o
screen_buffer_pos   0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
shellScreenHeight   0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
mmblockList         0x400             stdlib.o
screen_buffer_x     0x10              main.o
screen_buffer       0xfb0             main.o
libcHeap            0x10              stdlib.o
shell_window_y      0x10              main.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
terminal_rect       0x10              main.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
i1Window            0x10              main.o
screen_buffer_y     0x10              main.o
g_char_attrib       0x10              crt0.o
topbarWindow        0x10              main.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              crt0.o
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

.text           0x00451000     0x5000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x1bc0 main.o
                0x00452531                shellPrompt
                0x0045266f                shellTestThreads
                0x00451300                shellProcedure
                0x00451f72                shellShell
                0x0045245f                test_operators
                0x0045241e                shellThread
                0x00452057                shellInit
                0x00451444                shellWaitCmd
                0x00451058                GramadoMain
                0x004528cb                shellInsertCharXY
                0x0045290b                shellInsertCharPos
                0x0045145c                shellCompare
                0x00452598                shellClearBuffer
                0x0045275a                shellRefreshScreen
                0x004526ff                shellClearScreen
                0x00452bb2                shellShowSystemInfo
                0x00452939                shellInsertNextChar
                0x004525da                shellTestLoadFile
                0x004529cf                move_to
                0x00452959                shellInsertCR
                0x00452ab2                shellShowMetrics
                0x004527aa                shellScroll
                0x0045297d                shellInsertNullTerminator
                0x0045296b                shellInsertLF
                0x004523f4                shellSetCursor
                0x004529f4                shellShowInfo
                0x0045244b                shellTree
                0x00452437                shellHelp
                0x0045298f                shellTestMBR
 .text          0x00452c18      0x380 shellui.o
                0x00452deb                shellTestDisplayBMP
                0x00452e61                bmpDisplayBMP
                0x00452c18                shellCreateTopBar
 .text          0x00452f98     0x1470 api.o
                0x00453d4b                APIShowCurrentProcessInfo
                0x00453538                system11
                0x004535dd                refresh_buffer
                0x00453c2d                APISetFocus
                0x0045359b                system14
                0x004538c2                apiInitBackground
                0x00453b01                APICreateWindow
                0x00454278                apiBeginPaint
                0x004538c7                MessageBox
                0x00453dc9                APIreplace_window
                0x004542bf                apiGetSystemMetrics
                0x0045357a                system13
                0x0045412f                apiDown
                0x004541c7                enterCriticalSection
                0x00454105                apiFOpen
                0x004533ee                system1
                0x00453472                system5
                0x00453f7d                api_refresh_screen
                0x00454009                apiGetCursorY
                0x0045386d                carrega_bitmap_16x16
                0x00454220                exitCriticalSection
                0x00452f98                system_call
                0x0045417b                apiUp
                0x00452fc0                apiSystem
                0x004543d8                api_get_window_with_text_input
                0x004535bc                system15
                0x00453cdd                APISetActiveWindow
                0x00454061                apiSetClientAreaRect
                0x00453da0                APIredraw_window
                0x004540b3                apiCreateThread
                0x00453809                SetNextWindowProcedure
                0x00453fdd                apiGetCursorX
                0x004537d9                chama_procedimento
                0x004538f0                call_kernel
                0x00453ba9                APIRegisterWindow
                0x00453ef3                api_strncmp
                0x00453e1b                APIminimize_window
                0x0045340f                system2
                0x00453430                system3
                0x00454311                api_get_current_keyboard_responder
                0x0045408a                apiCreateProcess
                0x00453c6f                APIGetFocus
                0x004534b4                system7
                0x00453493                system6
                0x004542b5                apiDefDialog
                0x00453beb                APICloseWindow
                0x0045424c                initializeCriticalSection
                0x00453517                system10
                0x00453839                set_cursor
                0x00453df2                APImaximize_window
                0x00453f51                refresh_screen
                0x00453a70                call_gui
                0x004534f6                system9
                0x004542e8                api_set_current_keyboard_responder
                0x00453d77                APIresize_window
                0x00454282                apiEndPaint
                0x00453868                put_char
                0x00453774                print_string
                0x00454035                apiGetClientAreaRect
                0x004537aa                edit_box
                0x00453ec2                kill
                0x00453f87                apiReboot
                0x00453896                apiShutDown
                0x0045433d                api_set_current_mouse_responder
                0x00453e99                exit
                0x00453e44                APIget_foregroung_window
                0x00453451                system4
                0x00453fb3                apiSetCursor
                0x00453559                system12
                0x00453779                vsync
                0x004534d5                system8
                0x00454392                api_set_window_with_text_input
                0x00453d1f                APIGetActiveWindow
                0x00454366                api_get_current_mouse_responder
                0x00453ec7                dead_thread_collector
                0x004540dc                apiStartThread
                0x00453c9b                APIKillFocus
                0x00453e70                APIset_foregroung_window
                0x0045428c                apiPutChar
 .text          0x00454408      0xc00 stdio.o
                0x00454bc7                putchar
                0x00454b83                sprintf
                0x00454db3                input
                0x0045446d                scroll
                0x00454da9                printf_main
                0x00454bf3                outbyte
                0x00454617                app_print
                0x00454eaa                stdio_system_call
                0x0045441f                fopen
                0x00454ed2                stdioInitialize
                0x00454408                fclose
                0x00454d76                _outbyte
                0x00454b68                printf
                0x004545ab                app_clear
 .text          0x00455008      0x960 stdlib.o
                0x004552c3                FreeHeap
                0x00455008                rtGetHeapStart
                0x0045550a                free
                0x004554ac                rand
                0x00455423                stdlibInitMM
                0x004552cd                heapInit
                0x0045501c                rtGetHeapPointer
                0x00455026                rtGetAvailableHeap
                0x00455483                libcInitRT
                0x00455030                heapSetLibcHeap
                0x004554c9                malloc
                0x004552b0                AllocateHeapEx
                0x004550d7                AllocateHeap
                0x00455901                stdlib_strncmp
                0x00455012                rtGetHeapEnd
                0x0045550f                system
 .text          0x00455968      0x4a0 string.o
                0x00455bcf                strcspn
                0x00455b32                strcat
                0x00455968                strcmp
                0x00455b89                bzero
                0x00455d0f                strtok_r
                0x00455ac5                memcpy
                0x00455a9c                memoryZeroMemory
                0x00455b62                bcopy
                0x00455b02                strcpy
                0x00455c6f                strspn
                0x00455de4                strtok
                0x00455a21                str_cmp
                0x004559c3                strncmp
                0x00455ba4                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455e08      0x1f8 00

.rdata          0x00456000     0x15a0
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xb80 main.o

.data           0x004575a0      0xa60
                0x004575a0                data = .
                0x004575a0                _data = .
                0x004575a0                __data = .
 *(.data)
 .data          0x004575a0        0x0 crt0.o
 .data          0x004575a0       0x20 main.o
 .data          0x004575c0       0x20 shellui.o
 .data          0x004575e0        0x0 api.o
 .data          0x004575e0        0x0 stdio.o
 .data          0x004575e0       0x10 stdlib.o
 .data          0x004575f0        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x004575f0      0xa10 00

.bss            0x00458000     0xaed0
                0x00458000                bss = .
                0x00458000                _bss = .
                0x00458000                __bss = .
 *(.bss)
 .bss           0x00458000        0x0 crt0.o
 .bss           0x00458000       0xd0 main.o
 .bss           0x004580d0       0xd0 shellui.o
 .bss           0x004581a0       0x30 api.o
 .bss           0x004581d0       0x10 stdio.o
 .bss           0x004581e0     0x8000 stdlib.o
 .bss           0x004601e0       0x10 string.o
                0x00461000                . = ALIGN (0x1000)
 *fill*         0x004601f0      0xe10 00
 COMMON         0x00461000      0x410 crt0.o
                0x00461000                prompt
                0x00461100                _io_table
                0x00461150                stderr
                0x00461160                prompt_pos
                0x00461170                g_using_gui
                0x00461180                stdin
                0x00461190                prompt_max
                0x004611a0                prompt_err
                0x004612a0                g_columns
                0x004612b0                stdout
                0x004612c0                g_rows
                0x004612d0                prompt_out
                0x004613d0                g_cursor_y
                0x004613e0                prompt_status
                0x004613f0                g_char_attrib
                0x00461400                g_cursor_x
 COMMON         0x00461410     0x11d0 main.o
                0x00461410                ShellMetrics
                0x00461420                shellStatus
                0x00461430                shellWindowWidth
                0x00461440                ClientAreaInfo
                0x00461450                BufferInfo
                0x00461460                shellError
                0x00461470                shellWindowHeight
                0x00461480                root
                0x00461490                shell_info
                0x004614b0                shellScreenBufferMaxColumns
                0x004614c0                shell_window_x
                0x004614d0                i2Window
                0x004614e0                rect
                0x004614f0                backgroung_color
                0x00461500                shellMaxRows
                0x00461510                foregroung_color
                0x00461520                pwd
                0x00461530                CurrentWindow
                0x00461540                current_semaphore
                0x00461550                ShellHook
                0x00461560                shellScreenBufferMaxRows
                0x00461570                shellScreenWidth
                0x00461580                screen_buffer_pos
                0x00461590                shellScreenHeight
                0x004615a0                screen_buffer_x
                0x004615b0                screen_buffer
                0x00462560                shell_window_y
                0x00462570                terminal_rect
                0x00462580                CursorInfo
                0x00462590                shellMaxColumns
                0x004625a0                i1Window
                0x004625b0                screen_buffer_y
                0x004625c0                topbarWindow
                0x004625d0                ApplicationInfo
 COMMON         0x004625e0      0x8f0 stdlib.o
                0x004625e0                current_mmblock
                0x004625f0                mm_prev_pointer
                0x00462600                heap_end
                0x00462610                g_available_heap
                0x00462620                heap_start
                0x00462630                heapCount
                0x00462640                HEAP_START
                0x00462650                g_heap_pointer
                0x00462660                heapList
                0x00462a60                HEAP_SIZE
                0x00462a70                last_size
                0x00462a80                last_valid
                0x00462a90                mmblockList
                0x00462e90                libcHeap
                0x00462ea0                Heap
                0x00462eb0                mmblockCount
                0x00462ec0                HEAP_END
                0x00462ed0                end = .
                0x00462ed0                _end = .
                0x00462ed0                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD shellui.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
