
Allocating common symbols
Common symbol       size              file

prompt              0x100             main.o
taskmanagerBufferPos
                    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
taskmanagerBuffer   0x200             main.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
rect                0x10              main.o
prompt_max          0x10              main.o
CurrentWindow       0x10              main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
stdout              0x10              main.o
taskmanagerStatus   0x10              main.o
g_rows              0x10              main.o
g_cursor_y          0x10              main.o
CursorInfo          0x10              main.o
prompt_status       0x10              main.o
taskmanTest1        0x10              main.o
taskmanagerError    0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              main.o

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

.text           0x004a1000     0x3000
                0x004a1000                code = .
                0x004a1000                _code = .
                0x004a1000                __code = .
 *(.head_x86)
 .head_x86      0x004a1000       0x18 head.o
                0x004a1000                taskmanager_entry_point
 *(.text)
 .text          0x004a1018      0x510 main.o
                0x004a10c8                tmProc
                0x004a1018                tmSleep
                0x004a105f                tmCreateTaskBar
                0x004a1144                tmUpdateStatus
                0x004a11ef                tmSetCursor
                0x004a1195                tmDrawBar
                0x004a122f                DoProgress
                0x004a1364                progress_bar_test
                0x004a1204                tmstrlen
                0x004a1399                appMain
                0x004a1036                tmProbeProcessList
                0x004a1371                tmInit
                0x004a130d                DoSome
 .text          0x004a1528     0x1270 api.o
                0x004a2277                APIShowCurrentProcessInfo
                0x004a1ac8                system11
                0x004a1b6d                refresh_buffer
                0x004a2159                APISetFocus
                0x004a1b2b                system14
                0x004a1e52                apiInitBackground
                0x004a2091                APICreateWindow
                0x004a277b                apiBeginPaint
                0x004a1e57                MessageBox
                0x004a22f5                APIreplace_window
                0x004a1b0a                system13
                0x004a2632                apiDown
                0x004a26ca                enterCriticalSection
                0x004a2608                apiFOpen
                0x004a197e                system1
                0x004a1a02                system5
                0x004a24a9                api_refresh_screen
                0x004a2535                apiGetCursorY
                0x004a1dfd                carrega_bitmap_16x16
                0x004a2723                exitCriticalSection
                0x004a1528                system_call
                0x004a267e                apiUp
                0x004a1550                apiSystem
                0x004a1b4c                system15
                0x004a2209                APISetActiveWindow
                0x004a258d                apiSetClientAreaRect
                0x004a22cc                APIredraw_window
                0x004a25df                apiCreateThread
                0x004a1d99                SetNextWindowProcedure
                0x004a2509                apiGetCursorX
                0x004a1d69                chama_procedimento
                0x004a1e80                call_kernel
                0x004a20d5                APIRegisterWindow
                0x004a241f                api_strncmp
                0x004a2347                APIminimize_window
                0x004a199f                system2
                0x004a19c0                system3
                0x004a25b6                apiCreateProcess
                0x004a219b                APIGetFocus
                0x004a1a44                system7
                0x004a1a23                system6
                0x004a2117                APICloseWindow
                0x004a274f                initializeCriticalSection
                0x004a1aa7                system10
                0x004a1dc9                set_cursor
                0x004a231e                APImaximize_window
                0x004a247d                refresh_screen
                0x004a2000                call_gui
                0x004a1a86                system9
                0x004a22a3                APIresize_window
                0x004a2785                apiEndPaint
                0x004a1df8                put_char
                0x004a1d04                print_string
                0x004a2561                apiGetClientAreaRect
                0x004a1d3a                edit_box
                0x004a23ee                kill
                0x004a24b3                apiReboot
                0x004a1e26                apiShutDown
                0x004a23c5                exit
                0x004a2370                APIget_foregroung_window
                0x004a19e1                system4
                0x004a24df                apiSetCursor
                0x004a1ae9                system12
                0x004a1d09                vsync
                0x004a1a65                system8
                0x004a224b                APIGetActiveWindow
                0x004a23f3                dead_thread_collector
                0x004a21c7                APIKillFocus
                0x004a239c                APIset_foregroung_window
 .text          0x004a2798      0xad0 stdio.o
                0x004a2f3f                putchar
                0x004a2efb                sprintf
                0x004a310b                input
                0x004a27e5                scroll
                0x004a3101                printf_main
                0x004a2f55                outbyte
                0x004a298f                app_print
                0x004a323f                stdio_system_call
                0x004a27af                fopen
                0x004a2798                fclose
                0x004a30ce                _outbyte
                0x004a2ee0                printf
                0x004a2923                app_clear
                0x004a4000                . = ALIGN (0x1000)
 *fill*         0x004a3268      0xd98 00

.rdata          0x004a4000      0x470
 .rdata         0x004a4000       0x20 stdio.o
 .rdata         0x004a4020      0x310 api.o
 .rdata         0x004a4330      0x140 main.o

.data           0x004a4470      0xb90
                0x004a4470                data = .
                0x004a4470                _data = .
                0x004a4470                __data = .
 *(.data)
 .data          0x004a4470        0x0 main.o
 .data          0x004a4470        0x0 api.o
 .data          0x004a4470        0x0 stdio.o
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4470      0xb90 00

.bss            0x004a5000     0x1470
                0x004a5000                bss = .
                0x004a5000                _bss = .
                0x004a5000                __bss = .
 *(.bss)
 .bss           0x004a5000        0x0 main.o
 .bss           0x004a5000       0x30 api.o
 .bss           0x004a5030       0x10 stdio.o
                0x004a6000                . = ALIGN (0x1000)
 *fill*         0x004a5040      0xfc0 00
 COMMON         0x004a6000      0x470 main.o
                0x004a6000                prompt
                0x004a6100                taskmanagerBufferPos
                0x004a6110                ClientAreaInfo
                0x004a6120                BufferInfo
                0x004a6130                stderr
                0x004a6140                prompt_pos
                0x004a6150                taskmanagerBuffer
                0x004a6350                g_using_gui
                0x004a6360                stdin
                0x004a6370                rect
                0x004a6380                prompt_max
                0x004a6390                CurrentWindow
                0x004a63a0                current_semaphore
                0x004a63b0                g_columns
                0x004a63c0                stdout
                0x004a63d0                taskmanagerStatus
                0x004a63e0                g_rows
                0x004a63f0                g_cursor_y
                0x004a6400                CursorInfo
                0x004a6410                prompt_status
                0x004a6420                taskmanTest1
                0x004a6430                taskmanagerError
                0x004a6440                g_char_attrib
                0x004a6450                ApplicationInfo
                0x004a6460                g_cursor_x
                0x004a6470                end = .
                0x004a6470                _end = .
                0x004a6470                __end = .
LOAD head.o
LOAD main.o
LOAD api.o
LOAD stdio.o
OUTPUT(TASKMAN.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
