
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
shell_buffer        0x7d0             main.o
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
 .text          0x00451058     0x1820 main.o
                0x00452039                shellPrompt
                0x00452170                shellTestThreads
                0x004525c1                shellTestDisplayBMP
                0x00451325                shellProcedure
                0x00451a41                shellShell
                0x00451f67                test_operators
                0x00451f26                shellThread
                0x00451b26                shellInit
                0x00451455                shellWaitCmd
                0x00451058                GramadoMain
                0x004523cc                shellInsertCharXY
                0x0045240c                shellInsertCharPos
                0x0045146d                shellCompare
                0x004520a0                shellClearBuffer
                0x0045225b                shellRefreshScreen
                0x0045243a                shellInsertNextChar
                0x004520db                shellTestLoadFile
                0x0045284a                move_to
                0x0045245a                shellInsertCR
                0x004522ab                shellScroll
                0x0045247e                shellInsertNullTerminator
                0x00452490                bmpDisplayBMP
                0x0045246c                shellInsertLF
                0x00452200                shellClearscreen
                0x00451f11                shellSetCursor
                0x00452677                shellCreateTopBar
                0x00451f53                shellTree
                0x00451f3f                shellHelp
                0x00452637                shellTestMBR
 .text          0x00452878     0x1320 api.o
                0x0045362b                APIShowCurrentProcessInfo
                0x00452e18                system11
                0x00452ebd                refresh_buffer
                0x0045350d                APISetFocus
                0x00452e7b                system14
                0x004531a2                apiInitBackground
                0x004533e1                APICreateWindow
                0x00453b58                apiBeginPaint
                0x004531a7                MessageBox
                0x004536a9                APIreplace_window
                0x00452e5a                system13
                0x00453a0f                apiDown
                0x00453aa7                enterCriticalSection
                0x004539e5                apiFOpen
                0x00452cce                system1
                0x00452d52                system5
                0x0045385d                api_refresh_screen
                0x004538e9                apiGetCursorY
                0x0045314d                carrega_bitmap_16x16
                0x00453b00                exitCriticalSection
                0x00452878                system_call
                0x00453a5b                apiUp
                0x004528a0                apiSystem
                0x00452e9c                system15
                0x004535bd                APISetActiveWindow
                0x00453941                apiSetClientAreaRect
                0x00453680                APIredraw_window
                0x00453993                apiCreateThread
                0x004530e9                SetNextWindowProcedure
                0x004538bd                apiGetCursorX
                0x004530b9                chama_procedimento
                0x004531d0                call_kernel
                0x00453489                APIRegisterWindow
                0x004537d3                api_strncmp
                0x004536fb                APIminimize_window
                0x00452cef                system2
                0x00452d10                system3
                0x0045396a                apiCreateProcess
                0x0045354f                APIGetFocus
                0x00452d94                system7
                0x00452d73                system6
                0x004534cb                APICloseWindow
                0x00453b2c                initializeCriticalSection
                0x00452df7                system10
                0x00453119                set_cursor
                0x004536d2                APImaximize_window
                0x00453831                refresh_screen
                0x00453350                call_gui
                0x00452dd6                system9
                0x00453657                APIresize_window
                0x00453b62                apiEndPaint
                0x00453148                put_char
                0x00453054                print_string
                0x00453915                apiGetClientAreaRect
                0x0045308a                edit_box
                0x004537a2                kill
                0x00453867                apiReboot
                0x00453176                apiShutDown
                0x00453779                exit
                0x00453724                APIget_foregroung_window
                0x00452d31                system4
                0x00453893                apiSetCursor
                0x00452e39                system12
                0x00453059                vsync
                0x00452db5                system8
                0x004535ff                APIGetActiveWindow
                0x004537a7                dead_thread_collector
                0x004539bc                apiStartThread
                0x0045357b                APIKillFocus
                0x00453750                APIset_foregroung_window
                0x00453b6c                apiPutChar
 .text          0x00453b98      0xbf0 stdio.o
                0x00454357                putchar
                0x00454313                sprintf
                0x00454543                input
                0x00453bfd                scroll
                0x00454539                printf_main
                0x00454383                outbyte
                0x00453da7                app_print
                0x00454625                stdio_system_call
                0x00453baf                fopen
                0x0045464d                stdioInitialize
                0x00453b98                fclose
                0x00454506                _outbyte
                0x004542f8                printf
                0x00453d3b                app_clear
 .text          0x00454788      0x960 stdlib.o
                0x00454a43                FreeHeap
                0x00454788                rtGetHeapStart
                0x00454c8a                free
                0x00454c2c                rand
                0x00454ba3                stdlibInitMM
                0x00454a4d                heapInit
                0x0045479c                rtGetHeapPointer
                0x004547a6                rtGetAvailableHeap
                0x00454c03                libcInitRT
                0x004547b0                heapSetLibcHeap
                0x00454c49                malloc
                0x00454a30                AllocateHeapEx
                0x00454857                AllocateHeap
                0x00455081                stdlib_strncmp
                0x00454792                rtGetHeapEnd
                0x00454c8f                system
 .text          0x004550e8      0x270 string.o
                0x004552b2                strcat
                0x004550e8                strcmp
                0x00455309                bzero
                0x00455245                memcpy
                0x0045521c                memoryZeroMemory
                0x004552e2                bcopy
                0x00455282                strcpy
                0x004551a1                str_cmp
                0x00455143                strncmp
                0x00455324                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455358      0xca8 00

.rdata          0x00456000     0x1150
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x40 stdio.o
 .rdata         0x00456460      0x310 api.o
 .rdata         0x00456770      0x9e0 main.o

.data           0x00457150      0xeb0
                0x00457150                data = .
                0x00457150                _data = .
                0x00457150                __data = .
 *(.data)
 .data          0x00457150        0x0 crt0.o
 .data          0x00457150       0x20 main.o
 .data          0x00457170        0x0 api.o
 .data          0x00457170        0x0 stdio.o
 .data          0x00457170       0x10 stdlib.o
 .data          0x00457180        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457180      0xe80 00

.bss            0x00458000     0xa6c0
                0x00458000                bss = .
                0x00458000                _bss = .
                0x00458000                __bss = .
 *(.bss)
 .bss           0x00458000        0x0 crt0.o
 .bss           0x00458000       0xd0 main.o
 .bss           0x004580d0       0x30 api.o
 .bss           0x00458100       0x10 stdio.o
 .bss           0x00458110     0x8000 stdlib.o
 .bss           0x00460110        0x0 string.o
                0x00461000                . = ALIGN (0x1000)
 *fill*         0x00460110      0xef0 00
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
 COMMON         0x00461410      0x9c0 main.o
                0x00461410                ShellMetrics
                0x00461420                shellStatus
                0x00461430                shellWindowWidth
                0x00461440                ClientAreaInfo
                0x00461450                BufferInfo
                0x00461460                shellBufferMaxColumns
                0x00461470                shellError
                0x00461480                shell_buffer_y
                0x00461490                shell_buffer
                0x00461c60                shellWindowHeight
                0x00461c70                root
                0x00461c80                shell_window_x
                0x00461c90                i2Window
                0x00461ca0                rect
                0x00461cb0                backgroung_color
                0x00461cc0                shellMaxRows
                0x00461cd0                foregroung_color
                0x00461ce0                shell_buffer_pos
                0x00461cf0                pwd
                0x00461d00                CurrentWindow
                0x00461d10                current_semaphore
                0x00461d20                ShellHook
                0x00461d30                shellScreenWidth
                0x00461d40                shellScreenHeight
                0x00461d50                shell_buffer_x
                0x00461d60                shell_window_y
                0x00461d70                shellBufferMaxRows
                0x00461d80                CursorInfo
                0x00461d90                shellMaxColumns
                0x00461da0                i1Window
                0x00461db0                topbarWindow
                0x00461dc0                ApplicationInfo
 COMMON         0x00461dd0      0x8f0 stdlib.o
                0x00461dd0                current_mmblock
                0x00461de0                mm_prev_pointer
                0x00461df0                heap_end
                0x00461e00                g_available_heap
                0x00461e10                heap_start
                0x00461e20                heapCount
                0x00461e30                HEAP_START
                0x00461e40                g_heap_pointer
                0x00461e50                heapList
                0x00462250                HEAP_SIZE
                0x00462260                last_size
                0x00462270                last_valid
                0x00462280                mmblockList
                0x00462680                libcHeap
                0x00462690                Heap
                0x004626a0                mmblockCount
                0x004626b0                HEAP_END
                0x004626c0                end = .
                0x004626c0                _end = .
                0x004626c0                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
