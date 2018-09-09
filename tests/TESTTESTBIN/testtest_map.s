
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
 .text          0x00401038      0x110 main.o
                0x00401085                idleInit
                0x004010a3                idleServices
                0x0040103f                driverInitialize
                0x0040110d                testtest_main
                0x00401038                idleLoop
                0x00401062                driverUninitialize
 .text          0x00401148      0xbf0 stdio.o
                0x00401907                putchar
                0x004018c3                sprintf
                0x00401af3                input
                0x004011ad                scroll
                0x00401ae9                printf_main
                0x00401933                outbyte
                0x00401357                app_print
                0x00401bd5                stdio_system_call
                0x0040115f                fopen
                0x00401bfd                stdioInitialize
                0x00401148                fclose
                0x00401ab6                _outbyte
                0x004018a8                printf
                0x004012eb                app_clear
 .text          0x00401d38     0x1320 api.o
                0x00402aeb                APIShowCurrentProcessInfo
                0x004022d8                system11
                0x0040237d                refresh_buffer
                0x004029cd                APISetFocus
                0x0040233b                system14
                0x00402662                apiInitBackground
                0x004028a1                APICreateWindow
                0x00403018                apiBeginPaint
                0x00402667                MessageBox
                0x00402b69                APIreplace_window
                0x0040231a                system13
                0x00402ecf                apiDown
                0x00402f67                enterCriticalSection
                0x00402ea5                apiFOpen
                0x0040218e                system1
                0x00402212                system5
                0x00402d1d                api_refresh_screen
                0x00402da9                apiGetCursorY
                0x0040260d                carrega_bitmap_16x16
                0x00402fc0                exitCriticalSection
                0x00401d38                system_call
                0x00402f1b                apiUp
                0x00401d60                apiSystem
                0x0040235c                system15
                0x00402a7d                APISetActiveWindow
                0x00402e01                apiSetClientAreaRect
                0x00402b40                APIredraw_window
                0x00402e53                apiCreateThread
                0x004025a9                SetNextWindowProcedure
                0x00402d7d                apiGetCursorX
                0x00402579                chama_procedimento
                0x00402690                call_kernel
                0x00402949                APIRegisterWindow
                0x00402c93                api_strncmp
                0x00402bbb                APIminimize_window
                0x004021af                system2
                0x004021d0                system3
                0x00402e2a                apiCreateProcess
                0x00402a0f                APIGetFocus
                0x00402254                system7
                0x00402233                system6
                0x0040298b                APICloseWindow
                0x00402fec                initializeCriticalSection
                0x004022b7                system10
                0x004025d9                set_cursor
                0x00402b92                APImaximize_window
                0x00402cf1                refresh_screen
                0x00402810                call_gui
                0x00402296                system9
                0x00402b17                APIresize_window
                0x00403022                apiEndPaint
                0x00402608                put_char
                0x00402514                print_string
                0x00402dd5                apiGetClientAreaRect
                0x0040254a                edit_box
                0x00402c62                kill
                0x00402d27                apiReboot
                0x00402636                apiShutDown
                0x00402c39                exit
                0x00402be4                APIget_foregroung_window
                0x004021f1                system4
                0x00402d53                apiSetCursor
                0x004022f9                system12
                0x00402519                vsync
                0x00402275                system8
                0x00402abf                APIGetActiveWindow
                0x00402c67                dead_thread_collector
                0x00402e7c                apiStartThread
                0x00402a3b                APIKillFocus
                0x00402c10                APIset_foregroung_window
                0x0040302c                apiPutChar
                0x00404000                . = ALIGN (0x1000)
 *fill*         0x00403058      0xfa8 00

.rdata          0x00404000      0x410
 .rdata         0x00404000      0x310 api.o
 .rdata         0x00404310       0x40 stdio.o
 .rdata         0x00404350       0xc0 main.o

.data           0x00404410      0xbf0
                0x00404410                data = .
                0x00404410                _data = .
                0x00404410                __data = .
 *(.data)
 .data          0x00404410        0x0 main.o
 .data          0x00404410        0x0 stdio.o
 .data          0x00404410        0x0 api.o
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404410      0xbf0 00

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
OUTPUT(TESTTEST.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
