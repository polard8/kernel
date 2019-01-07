
Allocating common symbols
Common symbol       size              file

prompt              0x100             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              main.o
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
ServerStatus        0x10              main.o
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
 .head_x86      0x00401000       0x6f head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x0040106f        0x1 00
 .text          0x00401070      0x110 main.o
                0x00401159                idleInit
                0x004010ef                idleServices
                0x004010a9                driverInitialize
                0x00401070                idleLoop
                0x004010cc                driverUninitialize
                0x004010a4                initMain
 .text          0x00401180      0xbf0 stdio.o
                0x0040193f                putchar
                0x004018fb                sprintf
                0x00401b2b                input
                0x004011e5                scroll
                0x00401b21                printf_main
                0x0040196b                outbyte
                0x0040138f                app_print
                0x00401c0d                stdio_system_call
                0x00401197                fopen
                0x00401c35                stdioInitialize
                0x00401180                fclose
                0x00401aee                _outbyte
                0x004018e0                printf
                0x00401323                app_clear
 .text          0x00401d70     0x1320 api.o
                0x00402b23                APIShowCurrentProcessInfo
                0x00402310                system11
                0x004023b5                refresh_buffer
                0x00402a05                APISetFocus
                0x00402373                system14
                0x0040269a                apiInitBackground
                0x004028d9                APICreateWindow
                0x00403050                apiBeginPaint
                0x0040269f                MessageBox
                0x00402ba1                APIreplace_window
                0x00402352                system13
                0x00402f07                apiDown
                0x00402f9f                enterCriticalSection
                0x00402edd                apiFOpen
                0x004021c6                system1
                0x0040224a                system5
                0x00402d55                api_refresh_screen
                0x00402de1                apiGetCursorY
                0x00402645                carrega_bitmap_16x16
                0x00402ff8                exitCriticalSection
                0x00401d70                system_call
                0x00402f53                apiUp
                0x00401d98                apiSystem
                0x00402394                system15
                0x00402ab5                APISetActiveWindow
                0x00402e39                apiSetClientAreaRect
                0x00402b78                APIredraw_window
                0x00402e8b                apiCreateThread
                0x004025e1                SetNextWindowProcedure
                0x00402db5                apiGetCursorX
                0x004025b1                chama_procedimento
                0x004026c8                call_kernel
                0x00402981                APIRegisterWindow
                0x00402ccb                api_strncmp
                0x00402bf3                APIminimize_window
                0x004021e7                system2
                0x00402208                system3
                0x00402e62                apiCreateProcess
                0x00402a47                APIGetFocus
                0x0040228c                system7
                0x0040226b                system6
                0x004029c3                APICloseWindow
                0x00403024                initializeCriticalSection
                0x004022ef                system10
                0x00402611                set_cursor
                0x00402bca                APImaximize_window
                0x00402d29                refresh_screen
                0x00402848                call_gui
                0x004022ce                system9
                0x00402b4f                APIresize_window
                0x0040305a                apiEndPaint
                0x00402640                put_char
                0x0040254c                print_string
                0x00402e0d                apiGetClientAreaRect
                0x00402582                edit_box
                0x00402c9a                kill
                0x00402d5f                apiReboot
                0x0040266e                apiShutDown
                0x00402c71                exit
                0x00402c1c                APIget_foregroung_window
                0x00402229                system4
                0x00402d8b                apiSetCursor
                0x00402331                system12
                0x00402551                vsync
                0x004022ad                system8
                0x00402af7                APIGetActiveWindow
                0x00402c9f                dead_thread_collector
                0x00402eb4                apiStartThread
                0x00402a73                APIKillFocus
                0x00402c48                APIset_foregroung_window
                0x00403064                apiPutChar
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403090      0xf70 00

.rdata          0x00404000      0x3f0
 .rdata         0x00404000      0x310 api.o
 .rdata         0x00404310       0x40 stdio.o
 .rdata         0x00404350       0xa0 main.o

.data           0x004043f0      0xc10
                0x004043f0                data = .
                0x004043f0                _data = .
                0x004043f0                __data = .
 *(.data)
 .data          0x004043f0       0x10 main.o
 .data          0x00404400        0x0 stdio.o
 .data          0x00404400        0x0 api.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404400      0xc00 00

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
                0x00406180                stderr
                0x00406190                prompt_pos
                0x004061a0                g_using_gui
                0x004061b0                stdin
                0x004061c0                rect
                0x004061d0                prompt_max
                0x004061e0                CurrentWindow
                0x004061f0                prompt_err
                0x004062f0                current_semaphore
                0x00406300                g_columns
                0x00406310                stdout
                0x00406320                ServerStatus
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
