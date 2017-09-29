
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
 .head_x86      0x00401000       0x48 head.o
                0x00401000                idle_entry_point
 *(.text)
 .text          0x00401048       0xe0 main.o
                0x00401093                idleInit
                0x004010b1                idleServices
                0x0040104d                driverInitialize
                0x00401048                idleLoop
                0x00401070                driverUninitialize
 .text          0x00401128      0xad0 stdio.o
                0x004018cf                putchar
                0x0040188b                sprintf
                0x00401a9b                input
                0x00401175                scroll
                0x00401a91                printf_main
                0x004018e5                outbyte
                0x0040131f                app_print
                0x00401bcf                stdio_system_call
                0x0040113f                fopen
                0x00401128                fclose
                0x00401a5e                _outbyte
                0x00401870                printf
                0x004012b3                app_clear
 .text          0x00401bf8     0x1000 api.o
                0x004028be                APIShowCurrentProcessInfo
                0x0040210f                system11
                0x004021b4                refresh_buffer
                0x004027a0                APISetFocus
                0x00402172                system14
                0x00402499                apiInitBackground
                0x004026d8                APICreateWindow
                0x0040249e                MessageBox
                0x00402151                system13
                0x00402b57                apiDown
                0x00402b2d                apiFOpen
                0x00401fc5                system1
                0x00402049                system5
                0x004029ce                api_refresh_screen
                0x00402a5a                apiGetCursorY
                0x00402444                carrega_bitmap_16x16
                0x00401bf8                system_call
                0x00402ba3                apiUp
                0x00402193                system15
                0x00402850                APISetActiveWindow
                0x00402ab2                apiSetClientAreaRect
                0x00402b04                apiCreateThread
                0x004023e0                SetNextWindowProcedure
                0x00402a2e                apiGetCursorX
                0x004023b0                chama_procedimento
                0x004024c7                call_kernel
                0x0040271c                APIRegisterWindow
                0x00402944                api_strncmp
                0x00401fe6                system2
                0x00402007                system3
                0x00402adb                apiCreateProcess
                0x004027e2                APIGetFocus
                0x0040208b                system7
                0x0040206a                system6
                0x0040275e                APICloseWindow
                0x004020ee                system10
                0x00402410                set_cursor
                0x004029a2                refresh_screen
                0x00402647                call_gui
                0x004020cd                system9
                0x0040243f                put_char
                0x0040234b                print_string
                0x00402a86                apiGetClientAreaRect
                0x00402381                edit_box
                0x00402913                kill
                0x004029d8                apiReboot
                0x0040246d                apiShutDown
                0x004028ea                exit
                0x00402028                system4
                0x00402a04                apiSetCursor
                0x00402130                system12
                0x00402350                vsync
                0x004020ac                system8
                0x00402892                APIGetActiveWindow
                0x00401c20                system
                0x00402918                dead_thread_collector
                0x0040280e                APIKillFocus
                0x00403000                . = ALIGN (0x1000)
 *fill*         0x00402bf8      0x408 00

.rdata          0x00403000      0x250
 .rdata         0x00403000      0x1a0 api.o
 .rdata         0x004031a0       0x20 stdio.o
 .rdata         0x004031c0       0x90 main.o

.data           0x00403250      0xdb0
                0x00403250                data = .
                0x00403250                _data = .
                0x00403250                __data = .
 *(.data)
 .data          0x00403250        0x0 main.o
 .data          0x00403250        0x0 stdio.o
 .data          0x00403250        0x0 api.o
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403250      0xdb0 00

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
