
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
shellBufferMaxColumns
                    0x10              main.o
_io_table           0x50              crt0.o
shellError          0x10              main.o
shell_buffer_y      0x10              main.o
stderr              0x10              crt0.o
shell_buffer        0x7e0             main.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
root                0x10              main.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
shell_window_x      0x10              main.o
i2Window            0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              crt0.o
shell_buffer_pos    0x10              main.o
pwd                 0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
shellScreenWidth    0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
shellScreenHeight   0x10              main.o
shell_buffer_x      0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
shell_window_y      0x10              main.o
shellBufferMaxRows  0x10              main.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
i1Window            0x10              main.o
g_char_attrib       0x10              crt0.o
topbarWindow        0x10              main.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              crt0.o
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

.text           0x00451000     0x5000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x1780 main.o
                0x00452216                shellPrompt
                0x0045234d                shellTestThreads
                0x00451321                shellProcedure
                0x00451be5                shellShell
                0x00452144                test_operators
                0x00452103                shellThread
                0x00451cca                shellInit
                0x0045146d                shellWaitCmd
                0x00451058                GramadoMain
                0x004525a9                shellInsertCharXY
                0x004525e9                shellInsertCharPos
                0x00451485                shellCompare
                0x0045227d                shellClearBuffer
                0x00452438                shellRefreshScreen
                0x00452617                shellInsertNextChar
                0x004522b8                shellTestLoadFile
                0x004526ad                move_to
                0x00452637                shellInsertCR
                0x004526d2                shellShowMetrics
                0x00452488                shellScroll
                0x0045265b                shellInsertNullTerminator
                0x00452649                shellInsertLF
                0x004523dd                shellClearscreen
                0x004520d9                shellSetCursor
                0x00452130                shellTree
                0x0045211c                shellHelp
                0x0045266d                shellTestMBR
 .text          0x004527d8      0x380 shellui.o
                0x004529ab                shellTestDisplayBMP
                0x00452a21                bmpDisplayBMP
                0x004527d8                shellCreateTopBar
 .text          0x00452b58     0x1350 api.o
                0x0045390b                APIShowCurrentProcessInfo
                0x004530f8                system11
                0x0045319d                refresh_buffer
                0x004537ed                APISetFocus
                0x0045315b                system14
                0x00453482                apiInitBackground
                0x004536c1                APICreateWindow
                0x00453e38                apiBeginPaint
                0x00453487                MessageBox
                0x00453989                APIreplace_window
                0x00453e7f                apiGetSystemMetrics
                0x0045313a                system13
                0x00453cef                apiDown
                0x00453d87                enterCriticalSection
                0x00453cc5                apiFOpen
                0x00452fae                system1
                0x00453032                system5
                0x00453b3d                api_refresh_screen
                0x00453bc9                apiGetCursorY
                0x0045342d                carrega_bitmap_16x16
                0x00453de0                exitCriticalSection
                0x00452b58                system_call
                0x00453d3b                apiUp
                0x00452b80                apiSystem
                0x0045317c                system15
                0x0045389d                APISetActiveWindow
                0x00453c21                apiSetClientAreaRect
                0x00453960                APIredraw_window
                0x00453c73                apiCreateThread
                0x004533c9                SetNextWindowProcedure
                0x00453b9d                apiGetCursorX
                0x00453399                chama_procedimento
                0x004534b0                call_kernel
                0x00453769                APIRegisterWindow
                0x00453ab3                api_strncmp
                0x004539db                APIminimize_window
                0x00452fcf                system2
                0x00452ff0                system3
                0x00453c4a                apiCreateProcess
                0x0045382f                APIGetFocus
                0x00453074                system7
                0x00453053                system6
                0x00453e75                apiDefDialog
                0x004537ab                APICloseWindow
                0x00453e0c                initializeCriticalSection
                0x004530d7                system10
                0x004533f9                set_cursor
                0x004539b2                APImaximize_window
                0x00453b11                refresh_screen
                0x00453630                call_gui
                0x004530b6                system9
                0x00453937                APIresize_window
                0x00453e42                apiEndPaint
                0x00453428                put_char
                0x00453334                print_string
                0x00453bf5                apiGetClientAreaRect
                0x0045336a                edit_box
                0x00453a82                kill
                0x00453b47                apiReboot
                0x00453456                apiShutDown
                0x00453a59                exit
                0x00453a04                APIget_foregroung_window
                0x00453011                system4
                0x00453b73                apiSetCursor
                0x00453119                system12
                0x00453339                vsync
                0x00453095                system8
                0x004538df                APIGetActiveWindow
                0x00453a87                dead_thread_collector
                0x00453c9c                apiStartThread
                0x0045385b                APIKillFocus
                0x00453a30                APIset_foregroung_window
                0x00453e4c                apiPutChar
 .text          0x00453ea8      0xc00 stdio.o
                0x00454667                putchar
                0x00454623                sprintf
                0x00454853                input
                0x00453f0d                scroll
                0x00454849                printf_main
                0x00454693                outbyte
                0x004540b7                app_print
                0x0045494a                stdio_system_call
                0x00453ebf                fopen
                0x00454972                stdioInitialize
                0x00453ea8                fclose
                0x00454816                _outbyte
                0x00454608                printf
                0x0045404b                app_clear
 .text          0x00454aa8      0x960 stdlib.o
                0x00454d63                FreeHeap
                0x00454aa8                rtGetHeapStart
                0x00454faa                free
                0x00454f4c                rand
                0x00454ec3                stdlibInitMM
                0x00454d6d                heapInit
                0x00454abc                rtGetHeapPointer
                0x00454ac6                rtGetAvailableHeap
                0x00454f23                libcInitRT
                0x00454ad0                heapSetLibcHeap
                0x00454f69                malloc
                0x00454d50                AllocateHeapEx
                0x00454b77                AllocateHeap
                0x004553a1                stdlib_strncmp
                0x00454ab2                rtGetHeapEnd
                0x00454faf                system
 .text          0x00455408      0x4a0 string.o
                0x0045566f                strcspn
                0x004555d2                strcat
                0x00455408                strcmp
                0x00455629                bzero
                0x004557af                strtok_r
                0x00455565                memcpy
                0x0045553c                memoryZeroMemory
                0x00455602                bcopy
                0x004555a2                strcpy
                0x0045570f                strspn
                0x00455884                strtok
                0x004554c1                str_cmp
                0x00455463                strncmp
                0x00455644                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x004558a8      0x758 00

.rdata          0x00456000     0x1440
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xa20 main.o

.data           0x00457440      0xbc0
                0x00457440                data = .
                0x00457440                _data = .
                0x00457440                __data = .
 *(.data)
 .data          0x00457440        0x0 crt0.o
 .data          0x00457440       0x20 main.o
 .data          0x00457460       0x20 shellui.o
 .data          0x00457480        0x0 api.o
 .data          0x00457480        0x0 stdio.o
 .data          0x00457480       0x10 stdlib.o
 .data          0x00457490        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457490      0xb70 00

.bss            0x00458000     0xa6d0
                0x00458000                bss = .
                0x00458000                _bss = .
                0x00458000                __bss = .
 *(.bss)
 .bss           0x00458000        0x0 crt0.o
 .bss           0x00458000       0xd0 main.o
 .bss           0x004580d0       0xd0 shellui.o
 .bss           0x004581a0       0x30 api.o
 .bss           0x004581d0       0x10 stdio.o
 .bss           0x004581e0     0x8000 stdlib.o
 .bss           0x004601e0       0x10 string.o
                0x00461000                . = ALIGN (0x1000)
 *fill*         0x004601f0      0xe10 00
 COMMON         0x00461000      0x410 crt0.o
                0x00461000                prompt
                0x00461100                _io_table
                0x00461150                stderr
                0x00461160                prompt_pos
                0x00461170                g_using_gui
                0x00461180                stdin
                0x00461190                prompt_max
                0x004611a0                prompt_err
                0x004612a0                g_columns
                0x004612b0                stdout
                0x004612c0                g_rows
                0x004612d0                prompt_out
                0x004613d0                g_cursor_y
                0x004613e0                prompt_status
                0x004613f0                g_char_attrib
                0x00461400                g_cursor_x
 COMMON         0x00461410      0x9d0 main.o
                0x00461410                ShellMetrics
                0x00461420                shellStatus
                0x00461430                shellWindowWidth
                0x00461440                ClientAreaInfo
                0x00461450                BufferInfo
                0x00461460                shellBufferMaxColumns
                0x00461470                shellError
                0x00461480                shell_buffer_y
                0x00461490                shell_buffer
                0x00461c70                shellWindowHeight
                0x00461c80                root
                0x00461c90                shell_window_x
                0x00461ca0                i2Window
                0x00461cb0                rect
                0x00461cc0                backgroung_color
                0x00461cd0                shellMaxRows
                0x00461ce0                foregroung_color
                0x00461cf0                shell_buffer_pos
                0x00461d00                pwd
                0x00461d10                CurrentWindow
                0x00461d20                current_semaphore
                0x00461d30                ShellHook
                0x00461d40                shellScreenWidth
                0x00461d50                shellScreenHeight
                0x00461d60                shell_buffer_x
                0x00461d70                shell_window_y
                0x00461d80                shellBufferMaxRows
                0x00461d90                CursorInfo
                0x00461da0                shellMaxColumns
                0x00461db0                i1Window
                0x00461dc0                topbarWindow
                0x00461dd0                ApplicationInfo
 COMMON         0x00461de0      0x8f0 stdlib.o
                0x00461de0                current_mmblock
                0x00461df0                mm_prev_pointer
                0x00461e00                heap_end
                0x00461e10                g_available_heap
                0x00461e20                heap_start
                0x00461e30                heapCount
                0x00461e40                HEAP_START
                0x00461e50                g_heap_pointer
                0x00461e60                heapList
                0x00462260                HEAP_SIZE
                0x00462270                last_size
                0x00462280                last_valid
                0x00462290                mmblockList
                0x00462690                libcHeap
                0x004626a0                Heap
                0x004626b0                mmblockCount
                0x004626c0                HEAP_END
                0x004626d0                end = .
                0x004626d0                _end = .
                0x004626d0                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD shellui.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
