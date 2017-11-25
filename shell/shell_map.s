
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
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058      0xf30 main.o
                0x00451e57                shellPrompt
                0x004512ec                shellProcedure
                0x004517ed                shellShell
                0x00451eb4                test_operators
                0x00451e2a                shellThread
                0x004518ae                shellInit
                0x004513e7                shellWaitCmd
                0x00451058                GramadoMain
                0x004513ff                shellCompare
                0x00451e15                shellSetCursor
                0x00451e43                shellHelp
 .text          0x00451f88     0x1300 api.o
                0x00452d3b                APIShowCurrentProcessInfo
                0x00452528                system11
                0x004525cd                refresh_buffer
                0x00452c1d                APISetFocus
                0x0045258b                system14
                0x004528b2                apiInitBackground
                0x00452af1                APICreateWindow
                0x00453268                apiBeginPaint
                0x004528b7                MessageBox
                0x00452db9                APIreplace_window
                0x0045256a                system13
                0x0045311f                apiDown
                0x004531b7                enterCriticalSection
                0x004530f5                apiFOpen
                0x004523de                system1
                0x00452462                system5
                0x00452f6d                api_refresh_screen
                0x00452ff9                apiGetCursorY
                0x0045285d                carrega_bitmap_16x16
                0x00453210                exitCriticalSection
                0x00451f88                system_call
                0x0045316b                apiUp
                0x00451fb0                apiSystem
                0x004525ac                system15
                0x00452ccd                APISetActiveWindow
                0x00453051                apiSetClientAreaRect
                0x00452d90                APIredraw_window
                0x004530a3                apiCreateThread
                0x004527f9                SetNextWindowProcedure
                0x00452fcd                apiGetCursorX
                0x004527c9                chama_procedimento
                0x004528e0                call_kernel
                0x00452b99                APIRegisterWindow
                0x00452ee3                api_strncmp
                0x00452e0b                APIminimize_window
                0x004523ff                system2
                0x00452420                system3
                0x0045307a                apiCreateProcess
                0x00452c5f                APIGetFocus
                0x004524a4                system7
                0x00452483                system6
                0x00452bdb                APICloseWindow
                0x0045323c                initializeCriticalSection
                0x00452507                system10
                0x00452829                set_cursor
                0x00452de2                APImaximize_window
                0x00452f41                refresh_screen
                0x00452a60                call_gui
                0x004524e6                system9
                0x00452d67                APIresize_window
                0x00453272                apiEndPaint
                0x00452858                put_char
                0x00452764                print_string
                0x00453025                apiGetClientAreaRect
                0x0045279a                edit_box
                0x00452eb2                kill
                0x00452f77                apiReboot
                0x00452886                apiShutDown
                0x00452e89                exit
                0x00452e34                APIget_foregroung_window
                0x00452441                system4
                0x00452fa3                apiSetCursor
                0x00452549                system12
                0x00452769                vsync
                0x004524c5                system8
                0x00452d0f                APIGetActiveWindow
                0x00452eb7                dead_thread_collector
                0x004530cc                apiStartThread
                0x00452c8b                APIKillFocus
                0x00452e60                APIset_foregroung_window
 .text          0x00453288      0xa90 stdio.o
                0x00453a2f                putchar
                0x004539eb                sprintf
                0x00453c05                input
                0x004532d5                scroll
                0x00453bfb                printf_main
                0x00453a45                outbyte
                0x0045347f                app_print
                0x00453ce7                stdio_system_call
                0x0045329f                fopen
                0x00453288                fclose
                0x00453bc8                _outbyte
                0x004539d0                printf
                0x00453413                app_clear
 .text          0x00453d18      0x960 stdlib.o
                0x00453fd3                FreeHeap
                0x00453d18                rtGetHeapStart
                0x0045421a                free
                0x004541bc                rand
                0x00454133                stdlibInitMM
                0x00453fdd                heapInit
                0x00453d2c                rtGetHeapPointer
                0x00453d36                rtGetAvailableHeap
                0x00454193                libcInitRT
                0x00453d40                heapSetLibcHeap
                0x004541d9                malloc
                0x00453fc0                AllocateHeapEx
                0x00453de7                AllocateHeap
                0x00454611                stdlib_strncmp
                0x00453d22                rtGetHeapEnd
                0x0045421f                system
 .text          0x00454678      0x270 string.o
                0x00454842                strcat
                0x00454678                strcmp
                0x00454899                bzero
                0x004547d5                memcpy
                0x004547ac                memoryZeroMemory
                0x00454872                bcopy
                0x00454812                strcpy
                0x00454731                str_cmp
                0x004546d3                strncmp
                0x004548b4                strlen
                0x00455000                . = ALIGN (0x1000)
 *fill*         0x004548e8      0x718 00

.rdata          0x00455000      0xec0
 .rdata         0x00455000      0x420 stdlib.o
 .rdata         0x00455420       0x30 stdio.o
 .rdata         0x00455450      0x310 api.o
 .rdata         0x00455760      0x760 main.o

.data           0x00455ec0      0x140
                0x00455ec0                data = .
                0x00455ec0                _data = .
                0x00455ec0                __data = .
 *(.data)
 .data          0x00455ec0        0x0 crt0.o
 .data          0x00455ec0        0x0 main.o
 .data          0x00455ec0        0x0 api.o
 .data          0x00455ec0        0x0 stdio.o
 .data          0x00455ec0       0x10 stdlib.o
 .data          0x00455ed0        0x0 string.o
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455ed0      0x130 00

.bss            0x00456000     0x9ff0
                0x00456000                bss = .
                0x00456000                _bss = .
                0x00456000                __bss = .
 *(.bss)
 .bss           0x00456000        0x0 crt0.o
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
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
