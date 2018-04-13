
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
shell_info          0x20              main.o
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
terminal_rect       0x10              main.o
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
 .text          0x00451058     0x1c10 main.o
                0x00452587                shellPrompt
                0x004526be                shellTestThreads
                0x00451314                shellProcedure
                0x00451f71                shellShell
                0x004524b5                test_operators
                0x00452474                shellThread
                0x00452056                shellInit
                0x00451458                shellWaitCmd
                0x00451058                GramadoMain
                0x0045291a                shellInsertCharXY
                0x0045295a                shellInsertCharPos
                0x00451470                shellCompare
                0x004525ee                shellClearBuffer
                0x004527a9                shellRefreshScreen
                0x0045274e                shellClearScreen
                0x00452c01                shellShowSystemInfo
                0x00452988                shellInsertNextChar
                0x00452629                shellTestLoadFile
                0x00452a1e                move_to
                0x004529a8                shellInsertCR
                0x00452b01                shellShowMetrics
                0x004527f9                shellScroll
                0x004529cc                shellInsertNullTerminator
                0x004529ba                shellInsertLF
                0x0045244a                shellSetCursor
                0x00452a43                shellShowInfo
                0x004524a1                shellTree
                0x0045248d                shellHelp
                0x004529de                shellTestMBR
 .text          0x00452c68      0x380 shellui.o
                0x00452e3b                shellTestDisplayBMP
                0x00452eb1                bmpDisplayBMP
                0x00452c68                shellCreateTopBar
 .text          0x00452fe8     0x1470 api.o
                0x00453d9b                APIShowCurrentProcessInfo
                0x00453588                system11
                0x0045362d                refresh_buffer
                0x00453c7d                APISetFocus
                0x004535eb                system14
                0x00453912                apiInitBackground
                0x00453b51                APICreateWindow
                0x004542c8                apiBeginPaint
                0x00453917                MessageBox
                0x00453e19                APIreplace_window
                0x0045430f                apiGetSystemMetrics
                0x004535ca                system13
                0x0045417f                apiDown
                0x00454217                enterCriticalSection
                0x00454155                apiFOpen
                0x0045343e                system1
                0x004534c2                system5
                0x00453fcd                api_refresh_screen
                0x00454059                apiGetCursorY
                0x004538bd                carrega_bitmap_16x16
                0x00454270                exitCriticalSection
                0x00452fe8                system_call
                0x004541cb                apiUp
                0x00453010                apiSystem
                0x00454428                api_get_window_with_text_input
                0x0045360c                system15
                0x00453d2d                APISetActiveWindow
                0x004540b1                apiSetClientAreaRect
                0x00453df0                APIredraw_window
                0x00454103                apiCreateThread
                0x00453859                SetNextWindowProcedure
                0x0045402d                apiGetCursorX
                0x00453829                chama_procedimento
                0x00453940                call_kernel
                0x00453bf9                APIRegisterWindow
                0x00453f43                api_strncmp
                0x00453e6b                APIminimize_window
                0x0045345f                system2
                0x00453480                system3
                0x00454361                api_get_current_keyboard_responder
                0x004540da                apiCreateProcess
                0x00453cbf                APIGetFocus
                0x00453504                system7
                0x004534e3                system6
                0x00454305                apiDefDialog
                0x00453c3b                APICloseWindow
                0x0045429c                initializeCriticalSection
                0x00453567                system10
                0x00453889                set_cursor
                0x00453e42                APImaximize_window
                0x00453fa1                refresh_screen
                0x00453ac0                call_gui
                0x00453546                system9
                0x00454338                api_set_current_keyboard_responder
                0x00453dc7                APIresize_window
                0x004542d2                apiEndPaint
                0x004538b8                put_char
                0x004537c4                print_string
                0x00454085                apiGetClientAreaRect
                0x004537fa                edit_box
                0x00453f12                kill
                0x00453fd7                apiReboot
                0x004538e6                apiShutDown
                0x0045438d                api_set_current_mouse_responder
                0x00453ee9                exit
                0x00453e94                APIget_foregroung_window
                0x004534a1                system4
                0x00454003                apiSetCursor
                0x004535a9                system12
                0x004537c9                vsync
                0x00453525                system8
                0x004543e2                api_set_window_with_text_input
                0x00453d6f                APIGetActiveWindow
                0x004543b6                api_get_current_mouse_responder
                0x00453f17                dead_thread_collector
                0x0045412c                apiStartThread
                0x00453ceb                APIKillFocus
                0x00453ec0                APIset_foregroung_window
                0x004542dc                apiPutChar
 .text          0x00454458      0xc00 stdio.o
                0x00454c17                putchar
                0x00454bd3                sprintf
                0x00454e03                input
                0x004544bd                scroll
                0x00454df9                printf_main
                0x00454c43                outbyte
                0x00454667                app_print
                0x00454efa                stdio_system_call
                0x0045446f                fopen
                0x00454f22                stdioInitialize
                0x00454458                fclose
                0x00454dc6                _outbyte
                0x00454bb8                printf
                0x004545fb                app_clear
 .text          0x00455058      0x960 stdlib.o
                0x00455313                FreeHeap
                0x00455058                rtGetHeapStart
                0x0045555a                free
                0x004554fc                rand
                0x00455473                stdlibInitMM
                0x0045531d                heapInit
                0x0045506c                rtGetHeapPointer
                0x00455076                rtGetAvailableHeap
                0x004554d3                libcInitRT
                0x00455080                heapSetLibcHeap
                0x00455519                malloc
                0x00455300                AllocateHeapEx
                0x00455127                AllocateHeap
                0x00455951                stdlib_strncmp
                0x00455062                rtGetHeapEnd
                0x0045555f                system
 .text          0x004559b8      0x4a0 string.o
                0x00455c1f                strcspn
                0x00455b82                strcat
                0x004559b8                strcmp
                0x00455bd9                bzero
                0x00455d5f                strtok_r
                0x00455b15                memcpy
                0x00455aec                memoryZeroMemory
                0x00455bb2                bcopy
                0x00455b52                strcpy
                0x00455cbf                strspn
                0x00455e34                strtok
                0x00455a71                str_cmp
                0x00455a13                strncmp
                0x00455bf4                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455e58      0x1a8 00

.rdata          0x00456000     0x1580
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xb60 main.o

.data           0x00457580      0xa80
                0x00457580                data = .
                0x00457580                _data = .
                0x00457580                __data = .
 *(.data)
 .data          0x00457580        0x0 crt0.o
 .data          0x00457580       0x20 main.o
 .data          0x004575a0       0x20 shellui.o
 .data          0x004575c0        0x0 api.o
 .data          0x004575c0        0x0 stdio.o
 .data          0x004575c0       0x10 stdlib.o
 .data          0x004575d0        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x004575d0      0xa30 00

.bss            0x00458000     0xa700
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
 COMMON         0x00461410      0xa00 main.o
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
                0x00461c90                shell_info
                0x00461cb0                shell_window_x
                0x00461cc0                i2Window
                0x00461cd0                rect
                0x00461ce0                backgroung_color
                0x00461cf0                shellMaxRows
                0x00461d00                foregroung_color
                0x00461d10                shell_buffer_pos
                0x00461d20                pwd
                0x00461d30                CurrentWindow
                0x00461d40                current_semaphore
                0x00461d50                ShellHook
                0x00461d60                shellScreenWidth
                0x00461d70                shellScreenHeight
                0x00461d80                shell_buffer_x
                0x00461d90                shell_window_y
                0x00461da0                shellBufferMaxRows
                0x00461db0                terminal_rect
                0x00461dc0                CursorInfo
                0x00461dd0                shellMaxColumns
                0x00461de0                i1Window
                0x00461df0                topbarWindow
                0x00461e00                ApplicationInfo
 COMMON         0x00461e10      0x8f0 stdlib.o
                0x00461e10                current_mmblock
                0x00461e20                mm_prev_pointer
                0x00461e30                heap_end
                0x00461e40                g_available_heap
                0x00461e50                heap_start
                0x00461e60                heapCount
                0x00461e70                HEAP_START
                0x00461e80                g_heap_pointer
                0x00461e90                heapList
                0x00462290                HEAP_SIZE
                0x004622a0                last_size
                0x004622b0                last_valid
                0x004622c0                mmblockList
                0x004626c0                libcHeap
                0x004626d0                Heap
                0x004626e0                mmblockCount
                0x004626f0                HEAP_END
                0x00462700                end = .
                0x00462700                _end = .
                0x00462700                __end = .
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
