
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
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038      0x3b0 main.o
                0x00401083                idleInit
                0x004010a1                idleServices
                0x0040103d                driverInitialize
                0x0040110b                testtest_main
                0x0040113a                TEST_PRINTF
                0x00401038                idleLoop
                0x00401060                driverUninitialize
 .text          0x004013e8      0xbf0 stdio.o
                0x00401ba7                putchar
                0x00401b63                sprintf
                0x00401d93                input
                0x0040144d                scroll
                0x00401d89                printf_main
                0x00401bd3                outbyte
                0x004015f7                app_print
                0x00401e75                stdio_system_call
                0x004013ff                fopen
                0x00401e9d                stdioInitialize
                0x004013e8                fclose
                0x00401d56                _outbyte
                0x00401b48                printf
                0x0040158b                app_clear
 .text          0x00401fd8     0x1320 api.o
                0x00402d8b                APIShowCurrentProcessInfo
                0x00402578                system11
                0x0040261d                refresh_buffer
                0x00402c6d                APISetFocus
                0x004025db                system14
                0x00402902                apiInitBackground
                0x00402b41                APICreateWindow
                0x004032b8                apiBeginPaint
                0x00402907                MessageBox
                0x00402e09                APIreplace_window
                0x004025ba                system13
                0x0040316f                apiDown
                0x00403207                enterCriticalSection
                0x00403145                apiFOpen
                0x0040242e                system1
                0x004024b2                system5
                0x00402fbd                api_refresh_screen
                0x00403049                apiGetCursorY
                0x004028ad                carrega_bitmap_16x16
                0x00403260                exitCriticalSection
                0x00401fd8                system_call
                0x004031bb                apiUp
                0x00402000                apiSystem
                0x004025fc                system15
                0x00402d1d                APISetActiveWindow
                0x004030a1                apiSetClientAreaRect
                0x00402de0                APIredraw_window
                0x004030f3                apiCreateThread
                0x00402849                SetNextWindowProcedure
                0x0040301d                apiGetCursorX
                0x00402819                chama_procedimento
                0x00402930                call_kernel
                0x00402be9                APIRegisterWindow
                0x00402f33                api_strncmp
                0x00402e5b                APIminimize_window
                0x0040244f                system2
                0x00402470                system3
                0x004030ca                apiCreateProcess
                0x00402caf                APIGetFocus
                0x004024f4                system7
                0x004024d3                system6
                0x00402c2b                APICloseWindow
                0x0040328c                initializeCriticalSection
                0x00402557                system10
                0x00402879                set_cursor
                0x00402e32                APImaximize_window
                0x00402f91                refresh_screen
                0x00402ab0                call_gui
                0x00402536                system9
                0x00402db7                APIresize_window
                0x004032c2                apiEndPaint
                0x004028a8                put_char
                0x004027b4                print_string
                0x00403075                apiGetClientAreaRect
                0x004027ea                edit_box
                0x00402f02                kill
                0x00402fc7                apiReboot
                0x004028d6                apiShutDown
                0x00402ed9                exit
                0x00402e84                APIget_foregroung_window
                0x00402491                system4
                0x00402ff3                apiSetCursor
                0x00402599                system12
                0x004027b9                vsync
                0x00402515                system8
                0x00402d5f                APIGetActiveWindow
                0x00402f07                dead_thread_collector
                0x0040311c                apiStartThread
                0x00402cdb                APIKillFocus
                0x00402eb0                APIset_foregroung_window
                0x004032cc                apiPutChar
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x004032f8      0xd08 00

.rdata          0x00404000      0x580
 .rdata         0x00404000      0x310 api.o
 .rdata         0x00404310       0x40 stdio.o
 .rdata         0x00404350      0x230 main.o

.data           0x00404580      0xa80
                0x00404580                data = .
                0x00404580                _data = .
                0x00404580                __data = .
 *(.data)
 .data          0x00404580        0x0 main.o
 .data          0x00404580        0x0 stdio.o
 .data          0x00404580        0x0 api.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404580      0xa80 00

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
OUTPUT(PRINTF1.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
