
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
shellError          0x10              main.o
stderr              0x10              main.o
shell_buffer        0x400             main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              main.o
shell_buffer_pos    0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
ShellHook           0x10              main.o
shellScreenWidth    0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
shellScreenHeight   0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
shell_buffer_height
                    0x10              main.o
ApplicationInfo     0x10              main.o
shell_buffer_width  0x10              main.o
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

.text           0x00451000     0x4000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018      0xe80 main.o
                0x00451d5c                shellPrompt
                0x004512ac                shellProcedure
                0x004517ad                shellShell
                0x00451db9                test_operators
                0x00451d2f                shellThread
                0x0045186e                shellInit
                0x004513a7                shellWaitCmd
                0x00451018                GramadoMain
                0x004513bf                shellCompare
                0x00451d1a                shellSetCursor
                0x00451d48                shellHelp
 .text          0x00451e98     0x1270 api.o
                0x00452be7                APIShowCurrentProcessInfo
                0x00452438                system11
                0x004524dd                refresh_buffer
                0x00452ac9                APISetFocus
                0x0045249b                system14
                0x004527c2                apiInitBackground
                0x00452a01                APICreateWindow
                0x004530eb                apiBeginPaint
                0x004527c7                MessageBox
                0x00452c65                APIreplace_window
                0x0045247a                system13
                0x00452fa2                apiDown
                0x0045303a                enterCriticalSection
                0x00452f78                apiFOpen
                0x004522ee                system1
                0x00452372                system5
                0x00452e19                api_refresh_screen
                0x00452ea5                apiGetCursorY
                0x0045276d                carrega_bitmap_16x16
                0x00453093                exitCriticalSection
                0x00451e98                system_call
                0x00452fee                apiUp
                0x00451ec0                apiSystem
                0x004524bc                system15
                0x00452b79                APISetActiveWindow
                0x00452efd                apiSetClientAreaRect
                0x00452c3c                APIredraw_window
                0x00452f4f                apiCreateThread
                0x00452709                SetNextWindowProcedure
                0x00452e79                apiGetCursorX
                0x004526d9                chama_procedimento
                0x004527f0                call_kernel
                0x00452a45                APIRegisterWindow
                0x00452d8f                api_strncmp
                0x00452cb7                APIminimize_window
                0x0045230f                system2
                0x00452330                system3
                0x00452f26                apiCreateProcess
                0x00452b0b                APIGetFocus
                0x004523b4                system7
                0x00452393                system6
                0x00452a87                APICloseWindow
                0x004530bf                initializeCriticalSection
                0x00452417                system10
                0x00452739                set_cursor
                0x00452c8e                APImaximize_window
                0x00452ded                refresh_screen
                0x00452970                call_gui
                0x004523f6                system9
                0x00452c13                APIresize_window
                0x004530f5                apiEndPaint
                0x00452768                put_char
                0x00452674                print_string
                0x00452ed1                apiGetClientAreaRect
                0x004526aa                edit_box
                0x00452d5e                kill
                0x00452e23                apiReboot
                0x00452796                apiShutDown
                0x00452d35                exit
                0x00452ce0                APIget_foregroung_window
                0x00452351                system4
                0x00452e4f                apiSetCursor
                0x00452459                system12
                0x00452679                vsync
                0x004523d5                system8
                0x00452bbb                APIGetActiveWindow
                0x00452d63                dead_thread_collector
                0x00452b37                APIKillFocus
                0x00452d0c                APIset_foregroung_window
 .text          0x00453108      0xa80 stdio.o
                0x004538af                putchar
                0x0045386b                sprintf
                0x00453a7b                input
                0x00453155                scroll
                0x00453a71                printf_main
                0x004538c5                outbyte
                0x004532ff                app_print
                0x00453b5d                stdio_system_call
                0x0045311f                fopen
                0x00453108                fclose
                0x00453a3e                _outbyte
                0x00453850                printf
                0x00453293                app_clear
 .text          0x00453b88      0x940 stdlib.o
                0x00453e1b                FreeHeap
                0x00454071                free
                0x00454013                rand
                0x00453f8a                stdlibInitMM
                0x00453e25                heapInit
                0x00453fea                libcInitRT
                0x00453b88                heapSetLibcHeap
                0x00454030                malloc
                0x00453e08                AllocateHeapEx
                0x00453c2f                AllocateHeap
                0x00454468                stdlib_strncmp
                0x00454076                system
 .text          0x004544c8      0x270 string.o
                0x00454692                strcat
                0x004544c8                strcmp
                0x004546e9                bzero
                0x00454625                memcpy
                0x004545fc                memoryZeroMemory
                0x004546c2                bcopy
                0x00454662                strcpy
                0x00454581                str_cmp
                0x00454523                strncmp
                0x00454704                strlen
                0x00455000                . = ALIGN (0x1000)
 *fill*         0x00454738      0x8c8 00

.rdata          0x00455000      0xeb0
 .rdata         0x00455000      0x420 stdlib.o
 .rdata         0x00455420       0x20 stdio.o
 .rdata         0x00455440      0x310 api.o
 .rdata         0x00455750      0x760 main.o

.data           0x00455eb0      0x150
                0x00455eb0                data = .
                0x00455eb0                _data = .
                0x00455eb0                __data = .
 *(.data)
 .data          0x00455eb0        0x0 main.o
 .data          0x00455eb0        0x0 api.o
 .data          0x00455eb0        0x0 stdio.o
 .data          0x00455eb0       0x10 stdlib.o
 .data          0x00455ec0        0x0 string.o
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455ec0      0x140 00

.bss            0x00456000     0x9ff0
                0x00456000                bss = .
                0x00456000                _bss = .
                0x00456000                __bss = .
 *(.bss)
 .bss           0x00456000        0x0 main.o
 .bss           0x00456000       0x30 api.o
 .bss           0x00456030       0x10 stdio.o
 .bss           0x00456040     0x8000 stdlib.o
 .bss           0x0045e040        0x0 string.o
                0x0045f000                . = ALIGN (0x1000)
 *fill*         0x0045e040      0xfc0 00
 COMMON         0x0045f000      0x700 main.o
                0x0045f000                ShellMetrics
                0x0045f010                shellStatus
                0x0045f020                prompt
                0x0045f120                ClientAreaInfo
                0x0045f130                BufferInfo
                0x0045f140                shellError
                0x0045f150                stderr
                0x0045f160                shell_buffer
                0x0045f560                prompt_pos
                0x0045f570                g_using_gui
                0x0045f580                stdin
                0x0045f590                rect
                0x0045f5a0                backgroung_color
                0x0045f5b0                shellMaxRows
                0x0045f5c0                foregroung_color
                0x0045f5d0                prompt_max
                0x0045f5e0                shell_buffer_pos
                0x0045f5f0                CurrentWindow
                0x0045f600                current_semaphore
                0x0045f610                g_columns
                0x0045f620                ShellHook
                0x0045f630                shellScreenWidth
                0x0045f640                stdout
                0x0045f650                shellScreenHeight
                0x0045f660                g_rows
                0x0045f670                g_cursor_y
                0x0045f680                CursorInfo
                0x0045f690                shellMaxColumns
                0x0045f6a0                prompt_status
                0x0045f6b0                g_char_attrib
                0x0045f6c0                shell_buffer_height
                0x0045f6d0                ApplicationInfo
                0x0045f6e0                shell_buffer_width
                0x0045f6f0                g_cursor_x
 COMMON         0x0045f700      0x8f0 stdlib.o
                0x0045f700                current_mmblock
                0x0045f710                mm_prev_pointer
                0x0045f720                heap_end
                0x0045f730                g_available_heap
                0x0045f740                heap_start
                0x0045f750                heapCount
                0x0045f760                HEAP_START
                0x0045f770                g_heap_pointer
                0x0045f780                heapList
                0x0045fb80                HEAP_SIZE
                0x0045fb90                last_size
                0x0045fba0                last_valid
                0x0045fbb0                mmblockList
                0x0045ffb0                libcHeap
                0x0045ffc0                Heap
                0x0045ffd0                mmblockCount
                0x0045ffe0                HEAP_END
                0x0045fff0                end = .
                0x0045fff0                _end = .
                0x0045fff0                __end = .
LOAD head.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
