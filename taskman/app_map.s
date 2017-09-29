
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
 .text          0x004a1018      0x4f0 main.o
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
 .text          0x004a1508     0x1040 api.o
                0x004a2208                APIShowCurrentProcessInfo
                0x004a1a4f                system11
                0x004a1af4                refresh_buffer
                0x004a20ea                APISetFocus
                0x004a1ab2                system14
                0x004a1dd9                apiInitBackground
                0x004a2022                APICreateWindow
                0x004a1dde                MessageBox
                0x004a1a91                system13
                0x004a24a1                apiDown
                0x004a2477                apiFOpen
                0x004a2018                APIFastCreateWindow
                0x004a1905                system1
                0x004a1989                system5
                0x004a2318                api_refresh_screen
                0x004a23a4                apiGetCursorY
                0x004a1d84                carrega_bitmap_16x16
                0x004a1508                system_call
                0x004a24ed                apiUp
                0x004a1ad3                system15
                0x004a219a                APISetActiveWindow
                0x004a23fc                apiSetClientAreaRect
                0x004a244e                apiCreateThread
                0x004a1d20                SetNextWindowProcedure
                0x004a2378                apiGetCursorX
                0x004a1cf0                chama_procedimento
                0x004a1e07                call_kernel
                0x004a2066                APIRegisterWindow
                0x004a228e                api_strncmp
                0x004a1926                system2
                0x004a1947                system3
                0x004a2425                apiCreateProcess
                0x004a212c                APIGetFocus
                0x004a19cb                system7
                0x004a19aa                system6
                0x004a20a8                APICloseWindow
                0x004a1a2e                system10
                0x004a1d50                set_cursor
                0x004a22ec                refresh_screen
                0x004a1f87                call_gui
                0x004a1a0d                system9
                0x004a1d7f                put_char
                0x004a1c8b                print_string
                0x004a23d0                apiGetClientAreaRect
                0x004a1cc1                edit_box
                0x004a225d                kill
                0x004a2322                apiReboot
                0x004a1dad                apiShutDown
                0x004a2234                exit
                0x004a1968                system4
                0x004a234e                apiSetCursor
                0x004a1a70                system12
                0x004a1c90                vsync
                0x004a19ec                system8
                0x004a21dc                APIGetActiveWindow
                0x004a1530                system
                0x004a2262                dead_thread_collector
                0x004a2158                APIKillFocus
 .text          0x004a2548      0xad0 stdio.o
                0x004a2cef                putchar
                0x004a2cab                sprintf
                0x004a2ebb                input
                0x004a2595                scroll
                0x004a2eb1                printf_main
                0x004a2d05                outbyte
                0x004a273f                app_print
                0x004a2fef                stdio_system_call
                0x004a255f                fopen
                0x004a2548                fclose
                0x004a2e7e                _outbyte
                0x004a2c90                printf
                0x004a26d3                app_clear
                0x004a4000                . = ALIGN (0x1000)
 *fill*         0x004a3018      0xfe8 00

.rdata          0x004a4000      0x370
 .rdata         0x004a4000       0x20 stdio.o
 .rdata         0x004a4020      0x210 api.o
 .rdata         0x004a4230      0x140 main.o

.data           0x004a4370      0xc90
                0x004a4370                data = .
                0x004a4370                _data = .
                0x004a4370                __data = .
 *(.data)
 .data          0x004a4370        0x0 main.o
 .data          0x004a4370        0x0 api.o
 .data          0x004a4370        0x0 stdio.o
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4370      0xc90 00

.bss            0x004a5000     0x1460
                0x004a5000                bss = .
                0x004a5000                _bss = .
                0x004a5000                __bss = .
 *(.bss)
 .bss           0x004a5000        0x0 main.o
 .bss           0x004a5000       0x30 api.o
 .bss           0x004a5030       0x10 stdio.o
                0x004a6000                . = ALIGN (0x1000)
 *fill*         0x004a5040      0xfc0 00
 COMMON         0x004a6000      0x460 main.o
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
                0x004a6420                taskmanagerError
                0x004a6430                g_char_attrib
                0x004a6440                ApplicationInfo
                0x004a6450                g_cursor_x
                0x004a6460                end = .
                0x004a6460                _end = .
                0x004a6460                __end = .
LOAD head.o
LOAD main.o
LOAD api.o
LOAD stdio.o
OUTPUT(TASKMAN.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
