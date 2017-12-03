
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
shellBufferMaxColumns
                    0x10              main.o
shellError          0x10              main.o
shell_buffer_y      0x10              main.o
stderr              0x10              crt0.o
shell_buffer        0x7d0             main.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
shell_window_x      0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              crt0.o
shell_buffer_pos    0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
shellScreenWidth    0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
shellScreenHeight   0x10              main.o
shell_buffer_x      0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
shell_window_y      0x10              main.o
shellBufferMaxRows  0x10              main.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
g_char_attrib       0x10              crt0.o
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

.text           0x00451000     0x4000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x14b0 main.o
                0x00451ec4                shellPrompt
                0x00451ffb                shellTestThreads
                0x0045244c                shellTestDisplayBMP
                0x004512f5                shellProcedure
                0x004518e0                shellShell
                0x00451df2                test_operators
                0x00451dc5                shellThread
                0x004519c5                shellInit
                0x00451401                shellWaitCmd
                0x00451058                GramadoMain
                0x00452257                shellInsertCharXY
                0x00452297                shellInsertCharPos
                0x00451419                shellCompare
                0x00451f2b                shellClearBuffer
                0x004520e6                shellRefreshScreen
                0x004522c5                shellInsertNextChar
                0x00451f66                shellTestLoadFile
                0x004522e5                shellInsertCR
                0x00452136                shellScroll
                0x00452309                shellInsertNullTerminator
                0x0045231b                bmpDisplayBMP
                0x004522f7                shellInsertLF
                0x0045208b                shellClearscreen
                0x00451db0                shellSetCursor
                0x00451dde                shellHelp
                0x004524c2                shellTestMBR
 .text          0x00452508     0x1300 api.o
                0x004532bb                APIShowCurrentProcessInfo
                0x00452aa8                system11
                0x00452b4d                refresh_buffer
                0x0045319d                APISetFocus
                0x00452b0b                system14
                0x00452e32                apiInitBackground
                0x00453071                APICreateWindow
                0x004537e8                apiBeginPaint
                0x00452e37                MessageBox
                0x00453339                APIreplace_window
                0x00452aea                system13
                0x0045369f                apiDown
                0x00453737                enterCriticalSection
                0x00453675                apiFOpen
                0x0045295e                system1
                0x004529e2                system5
                0x004534ed                api_refresh_screen
                0x00453579                apiGetCursorY
                0x00452ddd                carrega_bitmap_16x16
                0x00453790                exitCriticalSection
                0x00452508                system_call
                0x004536eb                apiUp
                0x00452530                apiSystem
                0x00452b2c                system15
                0x0045324d                APISetActiveWindow
                0x004535d1                apiSetClientAreaRect
                0x00453310                APIredraw_window
                0x00453623                apiCreateThread
                0x00452d79                SetNextWindowProcedure
                0x0045354d                apiGetCursorX
                0x00452d49                chama_procedimento
                0x00452e60                call_kernel
                0x00453119                APIRegisterWindow
                0x00453463                api_strncmp
                0x0045338b                APIminimize_window
                0x0045297f                system2
                0x004529a0                system3
                0x004535fa                apiCreateProcess
                0x004531df                APIGetFocus
                0x00452a24                system7
                0x00452a03                system6
                0x0045315b                APICloseWindow
                0x004537bc                initializeCriticalSection
                0x00452a87                system10
                0x00452da9                set_cursor
                0x00453362                APImaximize_window
                0x004534c1                refresh_screen
                0x00452fe0                call_gui
                0x00452a66                system9
                0x004532e7                APIresize_window
                0x004537f2                apiEndPaint
                0x00452dd8                put_char
                0x00452ce4                print_string
                0x004535a5                apiGetClientAreaRect
                0x00452d1a                edit_box
                0x00453432                kill
                0x004534f7                apiReboot
                0x00452e06                apiShutDown
                0x00453409                exit
                0x004533b4                APIget_foregroung_window
                0x004529c1                system4
                0x00453523                apiSetCursor
                0x00452ac9                system12
                0x00452ce9                vsync
                0x00452a45                system8
                0x0045328f                APIGetActiveWindow
                0x00453437                dead_thread_collector
                0x0045364c                apiStartThread
                0x0045320b                APIKillFocus
                0x004533e0                APIset_foregroung_window
 .text          0x00453808      0xbe0 stdio.o
                0x00453fc7                putchar
                0x00453f83                sprintf
                0x0045419d                input
                0x0045386d                scroll
                0x00454193                printf_main
                0x00453fdd                outbyte
                0x00453a17                app_print
                0x0045427f                stdio_system_call
                0x0045381f                fopen
                0x004542a7                stdioInitialize
                0x00453808                fclose
                0x00454160                _outbyte
                0x00453f68                printf
                0x004539ab                app_clear
 .text          0x004543e8      0x960 stdlib.o
                0x004546a3                FreeHeap
                0x004543e8                rtGetHeapStart
                0x004548ea                free
                0x0045488c                rand
                0x00454803                stdlibInitMM
                0x004546ad                heapInit
                0x004543fc                rtGetHeapPointer
                0x00454406                rtGetAvailableHeap
                0x00454863                libcInitRT
                0x00454410                heapSetLibcHeap
                0x004548a9                malloc
                0x00454690                AllocateHeapEx
                0x004544b7                AllocateHeap
                0x00454ce1                stdlib_strncmp
                0x004543f2                rtGetHeapEnd
                0x004548ef                system
 .text          0x00454d48      0x270 string.o
                0x00454f12                strcat
                0x00454d48                strcmp
                0x00454f69                bzero
                0x00454ea5                memcpy
                0x00454e7c                memoryZeroMemory
                0x00454f42                bcopy
                0x00454ee2                strcpy
                0x00454e01                str_cmp
                0x00454da3                strncmp
                0x00454f84                strlen
                0x00455000                . = ALIGN (0x1000)
 *fill*         0x00454fb8       0x48 00

.rdata          0x00455000      0xf90
 .rdata         0x00455000      0x420 stdlib.o
 .rdata         0x00455420       0x40 stdio.o
 .rdata         0x00455460      0x310 api.o
 .rdata         0x00455770      0x820 main.o

.data           0x00455f90       0x70
                0x00455f90                data = .
                0x00455f90                _data = .
                0x00455f90                __data = .
 *(.data)
 .data          0x00455f90        0x0 crt0.o
 .data          0x00455f90       0x20 main.o
 .data          0x00455fb0        0x0 api.o
 .data          0x00455fb0        0x0 stdio.o
 .data          0x00455fb0       0x10 stdlib.o
 .data          0x00455fc0        0x0 string.o
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455fc0       0x40 00

.bss            0x00456000     0xa620
                0x00456000                bss = .
                0x00456000                _bss = .
                0x00456000                __bss = .
 *(.bss)
 .bss           0x00456000        0x0 crt0.o
 .bss           0x00456000       0xd0 main.o
 .bss           0x004560d0       0x30 api.o
 .bss           0x00456100       0x10 stdio.o
 .bss           0x00456110     0x8000 stdlib.o
 .bss           0x0045e110        0x0 string.o
                0x0045f000                . = ALIGN (0x1000)
 *fill*         0x0045e110      0xef0 00
 COMMON         0x0045f000      0x3c0 crt0.o
                0x0045f000                prompt
                0x0045f100                stderr
                0x0045f110                prompt_pos
                0x0045f120                g_using_gui
                0x0045f130                stdin
                0x0045f140                prompt_max
                0x0045f150                prompt_err
                0x0045f250                g_columns
                0x0045f260                stdout
                0x0045f270                g_rows
                0x0045f280                prompt_out
                0x0045f380                g_cursor_y
                0x0045f390                prompt_status
                0x0045f3a0                g_char_attrib
                0x0045f3b0                g_cursor_x
 COMMON         0x0045f3c0      0x970 main.o
                0x0045f3c0                ShellMetrics
                0x0045f3d0                shellStatus
                0x0045f3e0                shellWindowWidth
                0x0045f3f0                ClientAreaInfo
                0x0045f400                BufferInfo
                0x0045f410                shellBufferMaxColumns
                0x0045f420                shellError
                0x0045f430                shell_buffer_y
                0x0045f440                shell_buffer
                0x0045fc10                shellWindowHeight
                0x0045fc20                shell_window_x
                0x0045fc30                rect
                0x0045fc40                backgroung_color
                0x0045fc50                shellMaxRows
                0x0045fc60                foregroung_color
                0x0045fc70                shell_buffer_pos
                0x0045fc80                CurrentWindow
                0x0045fc90                current_semaphore
                0x0045fca0                ShellHook
                0x0045fcb0                shellScreenWidth
                0x0045fcc0                shellScreenHeight
                0x0045fcd0                shell_buffer_x
                0x0045fce0                shell_window_y
                0x0045fcf0                shellBufferMaxRows
                0x0045fd00                CursorInfo
                0x0045fd10                shellMaxColumns
                0x0045fd20                ApplicationInfo
 COMMON         0x0045fd30      0x8f0 stdlib.o
                0x0045fd30                current_mmblock
                0x0045fd40                mm_prev_pointer
                0x0045fd50                heap_end
                0x0045fd60                g_available_heap
                0x0045fd70                heap_start
                0x0045fd80                heapCount
                0x0045fd90                HEAP_START
                0x0045fda0                g_heap_pointer
                0x0045fdb0                heapList
                0x004601b0                HEAP_SIZE
                0x004601c0                last_size
                0x004601d0                last_valid
                0x004601e0                mmblockList
                0x004605e0                libcHeap
                0x004605f0                Heap
                0x00460600                mmblockCount
                0x00460610                HEAP_END
                0x00460620                end = .
                0x00460620                _end = .
                0x00460620                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
