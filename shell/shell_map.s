
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
shellError          0x10              main.o
stderr              0x10              main.o
shell_buffer        0x200             main.o
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
 .head_x86      0x00451000       0x46 head.o
                0x00451000                shell_entry_point
 *(.text)
 *fill*         0x00451046        0x2 00
 .text          0x00451048      0xc50 main.o
                0x00451c52                shellPrompt
                0x004512f1                shellProcedure
                0x00451813                shellShell
                0x00451c39                shellThread
                0x004518d4                shellInit
                0x00451459                shellWaitCmd
                0x00451471                shellCompare
                0x00451048                app_main
                0x00451c24                shellSetCursor
 .text          0x00451c98     0x1030 api.o
                0x0045298e                APIShowCurrentProcessInfo
                0x004521df                system11
                0x00452284                refresh_buffer
                0x00452870                APISetFocus
                0x00452242                system14
                0x00452569                apiInitBackground
                0x004527a8                APICreateWindow
                0x0045256e                MessageBox
                0x00452221                system13
                0x00452c27                apiDown
                0x00452bfd                apiFOpen
                0x00452095                system1
                0x00452119                system5
                0x00452a9e                api_refresh_screen
                0x00452b2a                apiGetCursorY
                0x00452514                carrega_bitmap_16x16
                0x00451c98                system_call
                0x00452c73                apiUp
                0x00451cc0                apiSystem
                0x00452263                system15
                0x00452920                APISetActiveWindow
                0x00452b82                apiSetClientAreaRect
                0x00452bd4                apiCreateThread
                0x004524b0                SetNextWindowProcedure
                0x00452afe                apiGetCursorX
                0x00452480                chama_procedimento
                0x00452597                call_kernel
                0x004527ec                APIRegisterWindow
                0x00452a14                api_strncmp
                0x004520b6                system2
                0x004520d7                system3
                0x00452bab                apiCreateProcess
                0x004528b2                APIGetFocus
                0x0045215b                system7
                0x0045213a                system6
                0x0045282e                APICloseWindow
                0x004521be                system10
                0x004524e0                set_cursor
                0x00452a72                refresh_screen
                0x00452717                call_gui
                0x0045219d                system9
                0x0045250f                put_char
                0x0045241b                print_string
                0x00452b56                apiGetClientAreaRect
                0x00452451                edit_box
                0x004529e3                kill
                0x00452aa8                apiReboot
                0x0045253d                apiShutDown
                0x004529ba                exit
                0x004520f8                system4
                0x00452ad4                apiSetCursor
                0x00452200                system12
                0x00452420                vsync
                0x0045217c                system8
                0x00452962                APIGetActiveWindow
                0x004529e8                dead_thread_collector
                0x004528de                APIKillFocus
 .text          0x00452cc8      0xa80 stdio.o
                0x0045346f                putchar
                0x0045342b                sprintf
                0x0045363b                input
                0x00452d15                scroll
                0x00453631                printf_main
                0x00453485                outbyte
                0x00452ebf                app_print
                0x0045371d                stdio_system_call
                0x00452cdf                fopen
                0x00452cc8                fclose
                0x004535fe                _outbyte
                0x00453410                printf
                0x00452e53                app_clear
 .text          0x00453748      0x930 stdlib.o
                0x004539db                FreeHeap
                0x00453c31                free
                0x00453bd3                rand
                0x00453b4a                stdlibInitMM
                0x004539e5                heapInit
                0x00453baa                libcInitRT
                0x00453748                heapSetLibcHeap
                0x00453bf0                malloc
                0x004539c8                AllocateHeapEx
                0x004537ef                AllocateHeap
                0x0045400b                stdlib_strncmp
                0x00453c36                system
 .text          0x00454078      0x270 string.o
                0x00454242                strcat
                0x00454078                strcmp
                0x00454299                bzero
                0x004541d5                memcpy
                0x004541ac                memoryZeroMemory
                0x00454272                bcopy
                0x00454212                strcpy
                0x00454131                str_cmp
                0x004540d3                strncmp
                0x004542b4                strlen
                0x00455000                . = ALIGN (0x1000)
 *fill*         0x004542e8      0xd18 00

.rdata          0x00455000      0xb70
 .rdata         0x00455000      0x3b0 stdlib.o
 .rdata         0x004553b0       0x20 stdio.o
 .rdata         0x004553d0      0x220 api.o
 .rdata         0x004555f0      0x580 main.o

.data           0x00455b70      0x490
                0x00455b70                data = .
                0x00455b70                _data = .
                0x00455b70                __data = .
 *(.data)
 .data          0x00455b70        0x0 main.o
 .data          0x00455b70        0x0 api.o
 .data          0x00455b70        0x0 stdio.o
 .data          0x00455b70       0x10 stdlib.o
 .data          0x00455b80        0x0 string.o
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455b80      0x480 00

.bss            0x00456000     0x9df0
                0x00456000                bss = .
                0x00456000                _bss = .
                0x00456000                __bss = .
 *(.bss)
 .bss           0x00456000        0x0 main.o
 .bss           0x00456000       0x30 api.o
 .bss           0x00456030       0x10 stdio.o
 .bss           0x00456040     0x8000 stdlib.o
 .bss           0x0045e040        0x0 string.o
                0x0045f000                . = ALIGN (0x1000)
 *fill*         0x0045e040      0xfc0 00
 COMMON         0x0045f000      0x500 main.o
                0x0045f000                ShellMetrics
                0x0045f010                shellStatus
                0x0045f020                prompt
                0x0045f120                ClientAreaInfo
                0x0045f130                BufferInfo
                0x0045f140                shellError
                0x0045f150                stderr
                0x0045f160                shell_buffer
                0x0045f360                prompt_pos
                0x0045f370                g_using_gui
                0x0045f380                stdin
                0x0045f390                rect
                0x0045f3a0                backgroung_color
                0x0045f3b0                shellMaxRows
                0x0045f3c0                foregroung_color
                0x0045f3d0                prompt_max
                0x0045f3e0                shell_buffer_pos
                0x0045f3f0                CurrentWindow
                0x0045f400                current_semaphore
                0x0045f410                g_columns
                0x0045f420                ShellHook
                0x0045f430                shellScreenWidth
                0x0045f440                stdout
                0x0045f450                shellScreenHeight
                0x0045f460                g_rows
                0x0045f470                g_cursor_y
                0x0045f480                CursorInfo
                0x0045f490                shellMaxColumns
                0x0045f4a0                prompt_status
                0x0045f4b0                g_char_attrib
                0x0045f4c0                shell_buffer_height
                0x0045f4d0                ApplicationInfo
                0x0045f4e0                shell_buffer_width
                0x0045f4f0                g_cursor_x
 COMMON         0x0045f500      0x8f0 stdlib.o
                0x0045f500                current_mmblock
                0x0045f510                mm_prev_pointer
                0x0045f520                heap_end
                0x0045f530                g_available_heap
                0x0045f540                heap_start
                0x0045f550                heapCount
                0x0045f560                HEAP_START
                0x0045f570                g_heap_pointer
                0x0045f580                heapList
                0x0045f980                HEAP_SIZE
                0x0045f990                last_size
                0x0045f9a0                last_valid
                0x0045f9b0                mmblockList
                0x0045fdb0                libcHeap
                0x0045fdc0                Heap
                0x0045fdd0                mmblockCount
                0x0045fde0                HEAP_END
                0x0045fdf0                end = .
                0x0045fdf0                _end = .
                0x0045fdf0                __end = .
LOAD head.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
