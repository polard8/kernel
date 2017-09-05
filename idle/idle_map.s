
Allocating common symbols
Common symbol       size              file

prompt              0x100             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
driverInitialized   0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
rect                0x10              main.o
prompt_max          0x10              main.o
CurrentWindow       0x10              main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
stdout              0x10              main.o
g_rows              0x10              main.o
g_cursor_y          0x10              main.o
CursorInfo          0x10              main.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
idleError           0x10              main.o
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

.text           0x00401000     0x2000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x81 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401081        0x3 00
 .text          0x00401084      0x100 main.o
                0x004010c2                idleInit
                0x004010f4                driverInitialize
                0x0040114c                driverUninitialize
                0x00401084                appMain
 .text          0x00401184      0xad0 stdio.o
                0x0040192b                putchar
                0x004018e7                sprintf
                0x00401af7                input
                0x004011d1                scroll
                0x00401aed                printf_main
                0x00401941                outbyte
                0x0040137b                app_print
                0x00401c2b                stdio_system_call
                0x0040119b                fopen
                0x00401184                fclose
                0x00401aba                _outbyte
                0x004018cc                printf
                0x0040130f                app_clear
 .text          0x00401c54     0x1000 api.o
                0x0040291a                APIShowCurrentProcessInfo
                0x0040216b                system11
                0x00402210                refresh_buffer
                0x004027fc                APISetFocus
                0x004021ce                system14
                0x004024f5                apiInitBackground
                0x00402734                APICreateWindow
                0x004024fa                MessageBox
                0x004021ad                system13
                0x00402bb3                apiDown
                0x00402b89                apiFOpen
                0x00402021                system1
                0x004020a5                system5
                0x00402a2a                api_refresh_screen
                0x00402ab6                apiGetCursorY
                0x004024a0                carrega_bitmap_16x16
                0x00401c54                system_call
                0x00402bff                apiUp
                0x004021ef                system15
                0x004028ac                APISetActiveWindow
                0x00402b0e                apiSetClientAreaRect
                0x00402b60                apiCreateThread
                0x0040243c                SetNextWindowProcedure
                0x00402a8a                apiGetCursorX
                0x0040240c                chama_procedimento
                0x00402523                call_kernel
                0x00402778                APIRegisterWindow
                0x004029a0                api_strncmp
                0x00402042                system2
                0x00402063                system3
                0x00402b37                apiCreateProcess
                0x0040283e                APIGetFocus
                0x004020e7                system7
                0x004020c6                system6
                0x004027ba                APICloseWindow
                0x0040214a                system10
                0x0040246c                set_cursor
                0x004029fe                refresh_screen
                0x004026a3                call_gui
                0x00402129                system9
                0x0040249b                put_char
                0x004023a7                print_string
                0x00402ae2                apiGetClientAreaRect
                0x004023dd                edit_box
                0x0040296f                kill
                0x00402a34                apiReboot
                0x004024c9                apiShutDown
                0x00402946                exit
                0x00402084                system4
                0x00402a60                apiSetCursor
                0x0040218c                system12
                0x004023ac                vsync
                0x00402108                system8
                0x004028ee                APIGetActiveWindow
                0x00401c7c                system
                0x00402974                dead_thread_collector
                0x0040286a                APIKillFocus
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x00402c54      0x3ac 00

.rdata          0x00403000      0x280
 .rdata         0x00403000      0x1a0 api.o
 .rdata         0x004031a0       0x20 stdio.o
 .rdata         0x004031c0       0xc0 main.o

.data           0x00403280      0xd80
                0x00403280                data = .
                0x00403280                _data = .
                0x00403280                __data = .
 *(.data)
 .data          0x00403280        0x0 main.o
 .data          0x00403280        0x0 stdio.o
 .data          0x00403280        0x0 api.o
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403280      0xd80 00

.bss            0x00404000     0x1260
                0x00404000                bss = .
                0x00404000                _bss = .
                0x00404000                __bss = .
 *(.bss)
 .bss           0x00404000        0x0 main.o
 .bss           0x00404000       0x10 stdio.o
 .bss           0x00404010       0x30 api.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404040      0xfc0 00
 COMMON         0x00405000      0x260 main.o
                0x00405000                prompt
                0x00405100                idleStatus
                0x00405110                ClientAreaInfo
                0x00405120                BufferInfo
                0x00405130                driverInitialized
                0x00405140                stderr
                0x00405150                prompt_pos
                0x00405160                g_using_gui
                0x00405170                stdin
                0x00405180                rect
                0x00405190                prompt_max
                0x004051a0                CurrentWindow
                0x004051b0                current_semaphore
                0x004051c0                g_columns
                0x004051d0                stdout
                0x004051e0                g_rows
                0x004051f0                g_cursor_y
                0x00405200                CursorInfo
                0x00405210                prompt_status
                0x00405220                g_char_attrib
                0x00405230                ApplicationInfo
                0x00405240                idleError
                0x00405250                g_cursor_x
                0x00405260                end = .
                0x00405260                _end = .
                0x00405260                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD api.o
OUTPUT(IDLE.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
