
Allocating common symbols
Common symbol       size              file

prompt              0x100             main.o
taskmanagerBufferPos
                    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
taskmanagerBuffer   0x20              main.o
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
 .head_x86      0x004a1000       0x46 head.o
                0x004a1000                taskmanager_entry_point
 *(.text)
 *fill*         0x004a1046        0x2 00
 .text          0x004a1048      0x500 main.o
                0x004a13bf                tmProc
                0x004a1048                tmSleep
                0x004a108f                tmCreateTaskBar
                0x004a143b                tmUpdateStatus
                0x004a14e6                tmSetCursor
                0x004a148c                tmDrawBar
                0x004a10f8                appMain
                0x004a1066                tmProbeProcessList
                0x004a14fb                tmInit
 .text          0x004a1548     0x1040 api.o
                0x004a2248                APIShowCurrentProcessInfo
                0x004a1a8f                system11
                0x004a1b34                refresh_buffer
                0x004a212a                APISetFocus
                0x004a1af2                system14
                0x004a1e19                apiInitBackground
                0x004a2062                APICreateWindow
                0x004a1e1e                MessageBox
                0x004a1ad1                system13
                0x004a24e1                apiDown
                0x004a24b7                apiFOpen
                0x004a2058                APIFastCreateWindow
                0x004a1945                system1
                0x004a19c9                system5
                0x004a2358                api_refresh_screen
                0x004a23e4                apiGetCursorY
                0x004a1dc4                carrega_bitmap_16x16
                0x004a1548                system_call
                0x004a252d                apiUp
                0x004a1b13                system15
                0x004a21da                APISetActiveWindow
                0x004a243c                apiSetClientAreaRect
                0x004a248e                apiCreateThread
                0x004a1d60                SetNextWindowProcedure
                0x004a23b8                apiGetCursorX
                0x004a1d30                chama_procedimento
                0x004a1e47                call_kernel
                0x004a20a6                APIRegisterWindow
                0x004a22ce                api_strncmp
                0x004a1966                system2
                0x004a1987                system3
                0x004a2465                apiCreateProcess
                0x004a216c                APIGetFocus
                0x004a1a0b                system7
                0x004a19ea                system6
                0x004a20e8                APICloseWindow
                0x004a1a6e                system10
                0x004a1d90                set_cursor
                0x004a232c                refresh_screen
                0x004a1fc7                call_gui
                0x004a1a4d                system9
                0x004a1dbf                put_char
                0x004a1ccb                print_string
                0x004a2410                apiGetClientAreaRect
                0x004a1d01                edit_box
                0x004a229d                kill
                0x004a2362                apiReboot
                0x004a1ded                apiShutDown
                0x004a2274                exit
                0x004a19a8                system4
                0x004a238e                apiSetCursor
                0x004a1ab0                system12
                0x004a1cd0                vsync
                0x004a1a2c                system8
                0x004a221c                APIGetActiveWindow
                0x004a1570                system
                0x004a22a2                dead_thread_collector
                0x004a2198                APIKillFocus
 .text          0x004a2588      0xad0 stdio.o
                0x004a2d2f                putchar
                0x004a2ceb                sprintf
                0x004a2efb                input
                0x004a25d5                scroll
                0x004a2ef1                printf_main
                0x004a2d45                outbyte
                0x004a277f                app_print
                0x004a302f                stdio_system_call
                0x004a259f                fopen
                0x004a2588                fclose
                0x004a2ebe                _outbyte
                0x004a2cd0                printf
                0x004a2713                app_clear
                0x004a4000                . = ALIGN (0x1000)
 *fill*         0x004a3058      0xfa8 00

.rdata          0x004a4000      0x310
 .rdata         0x004a4000       0x20 stdio.o
 .rdata         0x004a4020      0x210 api.o
 .rdata         0x004a4230       0xe0 main.o

.data           0x004a4310      0xcf0
                0x004a4310                data = .
                0x004a4310                _data = .
                0x004a4310                __data = .
 *(.data)
 .data          0x004a4310        0x0 main.o
 .data          0x004a4310        0x0 api.o
 .data          0x004a4310        0x0 stdio.o
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4310      0xcf0 00

.bss            0x004a5000     0x1280
                0x004a5000                bss = .
                0x004a5000                _bss = .
                0x004a5000                __bss = .
 *(.bss)
 .bss           0x004a5000        0x0 main.o
 .bss           0x004a5000       0x30 api.o
 .bss           0x004a5030       0x10 stdio.o
                0x004a6000                . = ALIGN (0x1000)
 *fill*         0x004a5040      0xfc0 00
 COMMON         0x004a6000      0x280 main.o
                0x004a6000                prompt
                0x004a6100                taskmanagerBufferPos
                0x004a6110                ClientAreaInfo
                0x004a6120                BufferInfo
                0x004a6130                stderr
                0x004a6140                prompt_pos
                0x004a6150                taskmanagerBuffer
                0x004a6170                g_using_gui
                0x004a6180                stdin
                0x004a6190                rect
                0x004a61a0                prompt_max
                0x004a61b0                CurrentWindow
                0x004a61c0                current_semaphore
                0x004a61d0                g_columns
                0x004a61e0                stdout
                0x004a61f0                taskmanagerStatus
                0x004a6200                g_rows
                0x004a6210                g_cursor_y
                0x004a6220                CursorInfo
                0x004a6230                prompt_status
                0x004a6240                taskmanagerError
                0x004a6250                g_char_attrib
                0x004a6260                ApplicationInfo
                0x004a6270                g_cursor_x
                0x004a6280                end = .
                0x004a6280                _end = .
                0x004a6280                __end = .
LOAD head.o
LOAD main.o
LOAD api.o
LOAD stdio.o
OUTPUT(TASKMAN.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
