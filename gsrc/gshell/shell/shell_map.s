
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
 .text          0x00451058     0x1930 main.o
                0x004522a1                shellPrompt
                0x004523d8                shellTestThreads
                0x00451352                shellProcedure
                0x00451c8b                shellShell
                0x004521cf                test_operators
                0x0045218e                shellThread
                0x00451d70                shellInit
                0x00451496                shellWaitCmd
                0x00451058                GramadoMain
                0x00452634                shellInsertCharXY
                0x00452674                shellInsertCharPos
                0x004514ae                shellCompare
                0x00452308                shellClearBuffer
                0x004524c3                shellRefreshScreen
                0x00452468                shellClearScreen
                0x0045291b                shellShowSystemInfo
                0x004526a2                shellInsertNextChar
                0x00452343                shellTestLoadFile
                0x00452738                move_to
                0x004526c2                shellInsertCR
                0x0045281b                shellShowMetrics
                0x00452513                shellScroll
                0x004526e6                shellInsertNullTerminator
                0x004526d4                shellInsertLF
                0x00452164                shellSetCursor
                0x0045275d                shellShowInfo
                0x004521bb                shellTree
                0x004521a7                shellHelp
                0x004526f8                shellTestMBR
 .text          0x00452988      0x380 shellui.o
                0x00452b5b                shellTestDisplayBMP
                0x00452bd1                bmpDisplayBMP
                0x00452988                shellCreateTopBar
 .text          0x00452d08     0x1470 api.o
                0x00453abb                APIShowCurrentProcessInfo
                0x004532a8                system11
                0x0045334d                refresh_buffer
                0x0045399d                APISetFocus
                0x0045330b                system14
                0x00453632                apiInitBackground
                0x00453871                APICreateWindow
                0x00453fe8                apiBeginPaint
                0x00453637                MessageBox
                0x00453b39                APIreplace_window
                0x0045402f                apiGetSystemMetrics
                0x004532ea                system13
                0x00453e9f                apiDown
                0x00453f37                enterCriticalSection
                0x00453e75                apiFOpen
                0x0045315e                system1
                0x004531e2                system5
                0x00453ced                api_refresh_screen
                0x00453d79                apiGetCursorY
                0x004535dd                carrega_bitmap_16x16
                0x00453f90                exitCriticalSection
                0x00452d08                system_call
                0x00453eeb                apiUp
                0x00452d30                apiSystem
                0x00454148                api_get_window_with_text_input
                0x0045332c                system15
                0x00453a4d                APISetActiveWindow
                0x00453dd1                apiSetClientAreaRect
                0x00453b10                APIredraw_window
                0x00453e23                apiCreateThread
                0x00453579                SetNextWindowProcedure
                0x00453d4d                apiGetCursorX
                0x00453549                chama_procedimento
                0x00453660                call_kernel
                0x00453919                APIRegisterWindow
                0x00453c63                api_strncmp
                0x00453b8b                APIminimize_window
                0x0045317f                system2
                0x004531a0                system3
                0x00454081                api_get_current_keyboard_responder
                0x00453dfa                apiCreateProcess
                0x004539df                APIGetFocus
                0x00453224                system7
                0x00453203                system6
                0x00454025                apiDefDialog
                0x0045395b                APICloseWindow
                0x00453fbc                initializeCriticalSection
                0x00453287                system10
                0x004535a9                set_cursor
                0x00453b62                APImaximize_window
                0x00453cc1                refresh_screen
                0x004537e0                call_gui
                0x00453266                system9
                0x00454058                api_set_current_keyboard_responder
                0x00453ae7                APIresize_window
                0x00453ff2                apiEndPaint
                0x004535d8                put_char
                0x004534e4                print_string
                0x00453da5                apiGetClientAreaRect
                0x0045351a                edit_box
                0x00453c32                kill
                0x00453cf7                apiReboot
                0x00453606                apiShutDown
                0x004540ad                api_set_current_mouse_responder
                0x00453c09                exit
                0x00453bb4                APIget_foregroung_window
                0x004531c1                system4
                0x00453d23                apiSetCursor
                0x004532c9                system12
                0x004534e9                vsync
                0x00453245                system8
                0x00454102                api_set_window_with_text_input
                0x00453a8f                APIGetActiveWindow
                0x004540d6                api_get_current_mouse_responder
                0x00453c37                dead_thread_collector
                0x00453e4c                apiStartThread
                0x00453a0b                APIKillFocus
                0x00453be0                APIset_foregroung_window
                0x00453ffc                apiPutChar
 .text          0x00454178      0xc00 stdio.o
                0x00454937                putchar
                0x004548f3                sprintf
                0x00454b23                input
                0x004541dd                scroll
                0x00454b19                printf_main
                0x00454963                outbyte
                0x00454387                app_print
                0x00454c1a                stdio_system_call
                0x0045418f                fopen
                0x00454c42                stdioInitialize
                0x00454178                fclose
                0x00454ae6                _outbyte
                0x004548d8                printf
                0x0045431b                app_clear
 .text          0x00454d78      0x960 stdlib.o
                0x00455033                FreeHeap
                0x00454d78                rtGetHeapStart
                0x0045527a                free
                0x0045521c                rand
                0x00455193                stdlibInitMM
                0x0045503d                heapInit
                0x00454d8c                rtGetHeapPointer
                0x00454d96                rtGetAvailableHeap
                0x004551f3                libcInitRT
                0x00454da0                heapSetLibcHeap
                0x00455239                malloc
                0x00455020                AllocateHeapEx
                0x00454e47                AllocateHeap
                0x00455671                stdlib_strncmp
                0x00454d82                rtGetHeapEnd
                0x0045527f                system
 .text          0x004556d8      0x4a0 string.o
                0x0045593f                strcspn
                0x004558a2                strcat
                0x004556d8                strcmp
                0x004558f9                bzero
                0x00455a7f                strtok_r
                0x00455835                memcpy
                0x0045580c                memoryZeroMemory
                0x004558d2                bcopy
                0x00455872                strcpy
                0x004559df                strspn
                0x00455b54                strtok
                0x00455791                str_cmp
                0x00455733                strncmp
                0x00455914                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455b78      0x488 00

.rdata          0x00456000     0x14c0
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xaa0 main.o

.data           0x004574c0      0xb40
                0x004574c0                data = .
                0x004574c0                _data = .
                0x004574c0                __data = .
 *(.data)
 .data          0x004574c0        0x0 crt0.o
 .data          0x004574c0       0x20 main.o
 .data          0x004574e0       0x20 shellui.o
 .data          0x00457500        0x0 api.o
 .data          0x00457500        0x0 stdio.o
 .data          0x00457500       0x10 stdlib.o
 .data          0x00457510        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457510      0xaf0 00

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
