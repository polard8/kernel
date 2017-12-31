
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
 .text          0x00451058     0x1850 main.o
                0x0045206a                shellPrompt
                0x004521a1                shellTestThreads
                0x004525f2                shellTestDisplayBMP
                0x00451325                shellProcedure
                0x00451a72                shellShell
                0x00451f98                test_operators
                0x00451f57                shellThread
                0x00451b57                shellInit
                0x00451455                shellWaitCmd
                0x00451058                GramadoMain
                0x004523fd                shellInsertCharXY
                0x0045243d                shellInsertCharPos
                0x0045146d                shellCompare
                0x004520d1                shellClearBuffer
                0x0045228c                shellRefreshScreen
                0x0045246b                shellInsertNextChar
                0x0045210c                shellTestLoadFile
                0x0045287b                move_to
                0x0045248b                shellInsertCR
                0x004522dc                shellScroll
                0x004524af                shellInsertNullTerminator
                0x004524c1                bmpDisplayBMP
                0x0045249d                shellInsertLF
                0x00452231                shellClearscreen
                0x00451f42                shellSetCursor
                0x004526a8                shellCreateTopBar
                0x00451f84                shellTree
                0x00451f70                shellHelp
                0x00452668                shellTestMBR
 .text          0x004528a8     0x1320 api.o
                0x0045365b                APIShowCurrentProcessInfo
                0x00452e48                system11
                0x00452eed                refresh_buffer
                0x0045353d                APISetFocus
                0x00452eab                system14
                0x004531d2                apiInitBackground
                0x00453411                APICreateWindow
                0x00453b88                apiBeginPaint
                0x004531d7                MessageBox
                0x004536d9                APIreplace_window
                0x00452e8a                system13
                0x00453a3f                apiDown
                0x00453ad7                enterCriticalSection
                0x00453a15                apiFOpen
                0x00452cfe                system1
                0x00452d82                system5
                0x0045388d                api_refresh_screen
                0x00453919                apiGetCursorY
                0x0045317d                carrega_bitmap_16x16
                0x00453b30                exitCriticalSection
                0x004528a8                system_call
                0x00453a8b                apiUp
                0x004528d0                apiSystem
                0x00452ecc                system15
                0x004535ed                APISetActiveWindow
                0x00453971                apiSetClientAreaRect
                0x004536b0                APIredraw_window
                0x004539c3                apiCreateThread
                0x00453119                SetNextWindowProcedure
                0x004538ed                apiGetCursorX
                0x004530e9                chama_procedimento
                0x00453200                call_kernel
                0x004534b9                APIRegisterWindow
                0x00453803                api_strncmp
                0x0045372b                APIminimize_window
                0x00452d1f                system2
                0x00452d40                system3
                0x0045399a                apiCreateProcess
                0x0045357f                APIGetFocus
                0x00452dc4                system7
                0x00452da3                system6
                0x004534fb                APICloseWindow
                0x00453b5c                initializeCriticalSection
                0x00452e27                system10
                0x00453149                set_cursor
                0x00453702                APImaximize_window
                0x00453861                refresh_screen
                0x00453380                call_gui
                0x00452e06                system9
                0x00453687                APIresize_window
                0x00453b92                apiEndPaint
                0x00453178                put_char
                0x00453084                print_string
                0x00453945                apiGetClientAreaRect
                0x004530ba                edit_box
                0x004537d2                kill
                0x00453897                apiReboot
                0x004531a6                apiShutDown
                0x004537a9                exit
                0x00453754                APIget_foregroung_window
                0x00452d61                system4
                0x004538c3                apiSetCursor
                0x00452e69                system12
                0x00453089                vsync
                0x00452de5                system8
                0x0045362f                APIGetActiveWindow
                0x004537d7                dead_thread_collector
                0x004539ec                apiStartThread
                0x004535ab                APIKillFocus
                0x00453780                APIset_foregroung_window
                0x00453b9c                apiPutChar
 .text          0x00453bc8      0xbf0 stdio.o
                0x00454387                putchar
                0x00454343                sprintf
                0x00454573                input
                0x00453c2d                scroll
                0x00454569                printf_main
                0x004543b3                outbyte
                0x00453dd7                app_print
                0x00454655                stdio_system_call
                0x00453bdf                fopen
                0x0045467d                stdioInitialize
                0x00453bc8                fclose
                0x00454536                _outbyte
                0x00454328                printf
                0x00453d6b                app_clear
 .text          0x004547b8      0x960 stdlib.o
                0x00454a73                FreeHeap
                0x004547b8                rtGetHeapStart
                0x00454cba                free
                0x00454c5c                rand
                0x00454bd3                stdlibInitMM
                0x00454a7d                heapInit
                0x004547cc                rtGetHeapPointer
                0x004547d6                rtGetAvailableHeap
                0x00454c33                libcInitRT
                0x004547e0                heapSetLibcHeap
                0x00454c79                malloc
                0x00454a60                AllocateHeapEx
                0x00454887                AllocateHeap
                0x004550b1                stdlib_strncmp
                0x004547c2                rtGetHeapEnd
                0x00454cbf                system
 .text          0x00455118      0x270 string.o
                0x004552e2                strcat
                0x00455118                strcmp
                0x00455339                bzero
                0x00455275                memcpy
                0x0045524c                memoryZeroMemory
                0x00455312                bcopy
                0x004552b2                strcpy
                0x004551d1                str_cmp
                0x00455173                strncmp
                0x00455354                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455388      0xc78 00

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
