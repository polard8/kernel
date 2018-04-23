
Allocating common symbols
Common symbol       size              file

prompt              0x100             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              main.o
driverInitialized   0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
rect                0x10              main.o
prompt_max          0x10              main.o
CurrentWindow       0x10              main.o
prompt_err          0x100             main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
stdout              0x10              main.o
g_rows              0x10              main.o
prompt_out          0x100             main.o
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

.text           0x00401000     0x3000
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
 .text          0x00401128      0xbf0 stdio.o
                0x004018e7                putchar
                0x004018a3                sprintf
                0x00401ad3                input
                0x0040118d                scroll
                0x00401ac9                printf_main
                0x00401913                outbyte
                0x00401337                app_print
                0x00401bb5                stdio_system_call
                0x0040113f                fopen
                0x00401bdd                stdioInitialize
                0x00401128                fclose
                0x00401a96                _outbyte
                0x00401888                printf
                0x004012cb                app_clear
 .text          0x00401d18     0x1320 api.o
                0x00402acb                APIShowCurrentProcessInfo
                0x004022b8                system11
                0x0040235d                refresh_buffer
                0x004029ad                APISetFocus
                0x0040231b                system14
                0x00402642                apiInitBackground
                0x00402881                APICreateWindow
                0x00402ff8                apiBeginPaint
                0x00402647                MessageBox
                0x00402b49                APIreplace_window
                0x004022fa                system13
                0x00402eaf                apiDown
                0x00402f47                enterCriticalSection
                0x00402e85                apiFOpen
                0x0040216e                system1
                0x004021f2                system5
                0x00402cfd                api_refresh_screen
                0x00402d89                apiGetCursorY
                0x004025ed                carrega_bitmap_16x16
                0x00402fa0                exitCriticalSection
                0x00401d18                system_call
                0x00402efb                apiUp
                0x00401d40                apiSystem
                0x0040233c                system15
                0x00402a5d                APISetActiveWindow
                0x00402de1                apiSetClientAreaRect
                0x00402b20                APIredraw_window
                0x00402e33                apiCreateThread
                0x00402589                SetNextWindowProcedure
                0x00402d5d                apiGetCursorX
                0x00402559                chama_procedimento
                0x00402670                call_kernel
                0x00402929                APIRegisterWindow
                0x00402c73                api_strncmp
                0x00402b9b                APIminimize_window
                0x0040218f                system2
                0x004021b0                system3
                0x00402e0a                apiCreateProcess
                0x004029ef                APIGetFocus
                0x00402234                system7
                0x00402213                system6
                0x0040296b                APICloseWindow
                0x00402fcc                initializeCriticalSection
                0x00402297                system10
                0x004025b9                set_cursor
                0x00402b72                APImaximize_window
                0x00402cd1                refresh_screen
                0x004027f0                call_gui
                0x00402276                system9
                0x00402af7                APIresize_window
                0x00403002                apiEndPaint
                0x004025e8                put_char
                0x004024f4                print_string
                0x00402db5                apiGetClientAreaRect
                0x0040252a                edit_box
                0x00402c42                kill
                0x00402d07                apiReboot
                0x00402616                apiShutDown
                0x00402c19                exit
                0x00402bc4                APIget_foregroung_window
                0x004021d1                system4
                0x00402d33                apiSetCursor
                0x004022d9                system12
                0x004024f9                vsync
                0x00402255                system8
                0x00402a9f                APIGetActiveWindow
                0x00402c47                dead_thread_collector
                0x00402e5c                apiStartThread
                0x00402a1b                APIKillFocus
                0x00402bf0                APIset_foregroung_window
                0x0040300c                apiPutChar
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403038      0xfc8 00

.rdata          0x00404000      0x3e0
 .rdata         0x00404000      0x310 api.o
 .rdata         0x00404310       0x40 stdio.o
 .rdata         0x00404350       0x90 main.o

.data           0x004043e0      0xc20
                0x004043e0                data = .
                0x004043e0                _data = .
                0x004043e0                __data = .
 *(.data)
 .data          0x004043e0        0x0 main.o
 .data          0x004043e0        0x0 stdio.o
 .data          0x004043e0        0x0 api.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x004043e0      0xc20 00

.bss            0x00405000     0x14b0
                0x00405000                bss = .
                0x00405000                _bss = .
                0x00405000                __bss = .
 *(.bss)
 .bss           0x00405000        0x0 main.o
 .bss           0x00405000       0x10 stdio.o
 .bss           0x00405010       0x30 api.o
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405040      0xfc0 00
 COMMON         0x00406000      0x4b0 main.o
                0x00406000                prompt
                0x00406100                idleStatus
                0x00406110                ClientAreaInfo
                0x00406120                BufferInfo
                0x00406130                _io_table
                0x00406180                driverInitialized
                0x00406190                stderr
                0x004061a0                prompt_pos
                0x004061b0                g_using_gui
                0x004061c0                stdin
                0x004061d0                rect
                0x004061e0                prompt_max
                0x004061f0                CurrentWindow
                0x00406200                prompt_err
                0x00406300                current_semaphore
                0x00406310                g_columns
                0x00406320                stdout
                0x00406330                g_rows
                0x00406340                prompt_out
                0x00406440                g_cursor_y
                0x00406450                CursorInfo
                0x00406460                prompt_status
                0x00406470                g_char_attrib
                0x00406480                ApplicationInfo
                0x00406490                idleError
                0x004064a0                g_cursor_x
                0x004064b0                end = .
                0x004064b0                _end = .
                0x004064b0                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD api.o
OUTPUT(INIT.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
