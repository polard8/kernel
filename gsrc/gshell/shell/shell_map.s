
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
CommandHistory      0x10              main.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              crt0.o
shellError          0x10              main.o
stderr              0x10              crt0.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
root                0x10              main.o
CurrentCommand      0x10              main.o
mm_prev_pointer     0x10              stdlib.o
shell_info          0x20              main.o
shellScreenBufferMaxColumns
                    0x10              main.o
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
pwd                 0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
shellScreenBufferMaxRows
                    0x10              main.o
shellScreenWidth    0x10              main.o
screen_buffer_pos   0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
shellScreenHeight   0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
username            0x10              main.o
mmblockList         0x400             stdlib.o
screen_buffer_x     0x10              main.o
screen_buffer       0xfb0             main.o
libcHeap            0x10              stdlib.o
shell_window_y      0x10              main.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
terminal_rect       0x10              main.o
password            0x10              main.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
i1Window            0x10              main.o
screen_buffer_y     0x10              main.o
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
 .text          0x00451058     0x1c70 main.o
                0x00452569                shellPrompt
                0x004526a7                shellTestThreads
                0x00451300                shellProcedure
                0x00451faa                shellShell
                0x00452497                test_operators
                0x00452456                shellThread
                0x0045208f                shellInit
                0x00451463                shellWaitCmd
                0x00451058                GramadoMain
                0x0045292b                shellInsertCharXY
                0x0045296b                shellInsertCharPos
                0x0045147b                shellCompare
                0x004525d0                shellClearBuffer
                0x004527bc                shellRefreshScreen
                0x00452737                shellClearScreen
                0x00452c12                shellShowSystemInfo
                0x00452999                shellInsertNextChar
                0x00452612                shellTestLoadFile
                0x00452a2f                move_to
                0x004529b9                shellInsertCR
                0x00452b12                shellShowMetrics
                0x00452c74                shellASCII
                0x0045280c                shellScroll
                0x004529dd                shellInsertNullTerminator
                0x004529cb                shellInsertLF
                0x0045242c                shellSetCursor
                0x00452a54                shellShowInfo
                0x00452483                shellTree
                0x0045246f                shellHelp
                0x004529ef                shellTestMBR
 .text          0x00452cc8      0x380 shellui.o
                0x00452e9b                shellTestDisplayBMP
                0x00452f11                bmpDisplayBMP
                0x00452cc8                shellCreateTopBar
 .text          0x00453048     0x1470 api.o
                0x00453dfb                APIShowCurrentProcessInfo
                0x004535e8                system11
                0x0045368d                refresh_buffer
                0x00453cdd                APISetFocus
                0x0045364b                system14
                0x00453972                apiInitBackground
                0x00453bb1                APICreateWindow
                0x00454328                apiBeginPaint
                0x00453977                MessageBox
                0x00453e79                APIreplace_window
                0x0045436f                apiGetSystemMetrics
                0x0045362a                system13
                0x004541df                apiDown
                0x00454277                enterCriticalSection
                0x004541b5                apiFOpen
                0x0045349e                system1
                0x00453522                system5
                0x0045402d                api_refresh_screen
                0x004540b9                apiGetCursorY
                0x0045391d                carrega_bitmap_16x16
                0x004542d0                exitCriticalSection
                0x00453048                system_call
                0x0045422b                apiUp
                0x00453070                apiSystem
                0x00454488                api_get_window_with_text_input
                0x0045366c                system15
                0x00453d8d                APISetActiveWindow
                0x00454111                apiSetClientAreaRect
                0x00453e50                APIredraw_window
                0x00454163                apiCreateThread
                0x004538b9                SetNextWindowProcedure
                0x0045408d                apiGetCursorX
                0x00453889                chama_procedimento
                0x004539a0                call_kernel
                0x00453c59                APIRegisterWindow
                0x00453fa3                api_strncmp
                0x00453ecb                APIminimize_window
                0x004534bf                system2
                0x004534e0                system3
                0x004543c1                api_get_current_keyboard_responder
                0x0045413a                apiCreateProcess
                0x00453d1f                APIGetFocus
                0x00453564                system7
                0x00453543                system6
                0x00454365                apiDefDialog
                0x00453c9b                APICloseWindow
                0x004542fc                initializeCriticalSection
                0x004535c7                system10
                0x004538e9                set_cursor
                0x00453ea2                APImaximize_window
                0x00454001                refresh_screen
                0x00453b20                call_gui
                0x004535a6                system9
                0x00454398                api_set_current_keyboard_responder
                0x00453e27                APIresize_window
                0x00454332                apiEndPaint
                0x00453918                put_char
                0x00453824                print_string
                0x004540e5                apiGetClientAreaRect
                0x0045385a                edit_box
                0x00453f72                kill
                0x00454037                apiReboot
                0x00453946                apiShutDown
                0x004543ed                api_set_current_mouse_responder
                0x00453f49                exit
                0x00453ef4                APIget_foregroung_window
                0x00453501                system4
                0x00454063                apiSetCursor
                0x00453609                system12
                0x00453829                vsync
                0x00453585                system8
                0x00454442                api_set_window_with_text_input
                0x00453dcf                APIGetActiveWindow
                0x00454416                api_get_current_mouse_responder
                0x00453f77                dead_thread_collector
                0x0045418c                apiStartThread
                0x00453d4b                APIKillFocus
                0x00453f20                APIset_foregroung_window
                0x0045433c                apiPutChar
 .text          0x004544b8      0xc00 stdio.o
                0x00454c77                putchar
                0x00454c33                sprintf
                0x00454e63                input
                0x0045451d                scroll
                0x00454e59                printf_main
                0x00454ca3                outbyte
                0x004546c7                app_print
                0x00454f5a                stdio_system_call
                0x004544cf                fopen
                0x00454f82                stdioInitialize
                0x004544b8                fclose
                0x00454e26                _outbyte
                0x00454c18                printf
                0x0045465b                app_clear
 .text          0x004550b8      0x960 stdlib.o
                0x00455373                FreeHeap
                0x004550b8                rtGetHeapStart
                0x004555ba                free
                0x0045555c                rand
                0x004554d3                stdlibInitMM
                0x0045537d                heapInit
                0x004550cc                rtGetHeapPointer
                0x004550d6                rtGetAvailableHeap
                0x00455533                libcInitRT
                0x004550e0                heapSetLibcHeap
                0x00455579                malloc
                0x00455360                AllocateHeapEx
                0x00455187                AllocateHeap
                0x004559b1                stdlib_strncmp
                0x004550c2                rtGetHeapEnd
                0x004555bf                system
 .text          0x00455a18      0x4a0 string.o
                0x00455c7f                strcspn
                0x00455be2                strcat
                0x00455a18                strcmp
                0x00455c39                bzero
                0x00455dbf                strtok_r
                0x00455b75                memcpy
                0x00455b4c                memoryZeroMemory
                0x00455c12                bcopy
                0x00455bb2                strcpy
                0x00455d1f                strspn
                0x00455e94                strtok
                0x00455ad1                str_cmp
                0x00455a73                strncmp
                0x00455c54                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455eb8      0x148 00

.rdata          0x00456000     0x16c0
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xca0 main.o

.data           0x004576c0      0x940
                0x004576c0                data = .
                0x004576c0                _data = .
                0x004576c0                __data = .
 *(.data)
 .data          0x004576c0        0x0 crt0.o
 .data          0x004576c0       0x20 main.o
 .data          0x004576e0       0x20 shellui.o
 .data          0x00457700        0x0 api.o
 .data          0x00457700        0x0 stdio.o
 .data          0x00457700       0x10 stdlib.o
 .data          0x00457710        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457710      0x8f0 00

.bss            0x00458000     0xaf10
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
 COMMON         0x00461410     0x1210 main.o
                0x00461410                ShellMetrics
                0x00461420                shellStatus
                0x00461430                CommandHistory
                0x00461440                shellWindowWidth
                0x00461450                ClientAreaInfo
                0x00461460                BufferInfo
                0x00461470                shellError
                0x00461480                shellWindowHeight
                0x00461490                root
                0x004614a0                CurrentCommand
                0x004614b0                shell_info
                0x004614d0                shellScreenBufferMaxColumns
                0x004614e0                shell_window_x
                0x004614f0                i2Window
                0x00461500                rect
                0x00461510                backgroung_color
                0x00461520                shellMaxRows
                0x00461530                foregroung_color
                0x00461540                pwd
                0x00461550                CurrentWindow
                0x00461560                current_semaphore
                0x00461570                ShellHook
                0x00461580                shellScreenBufferMaxRows
                0x00461590                shellScreenWidth
                0x004615a0                screen_buffer_pos
                0x004615b0                shellScreenHeight
                0x004615c0                username
                0x004615d0                screen_buffer_x
                0x004615e0                screen_buffer
                0x00462590                shell_window_y
                0x004625a0                terminal_rect
                0x004625b0                password
                0x004625c0                CursorInfo
                0x004625d0                shellMaxColumns
                0x004625e0                i1Window
                0x004625f0                screen_buffer_y
                0x00462600                topbarWindow
                0x00462610                ApplicationInfo
 COMMON         0x00462620      0x8f0 stdlib.o
                0x00462620                current_mmblock
                0x00462630                mm_prev_pointer
                0x00462640                heap_end
                0x00462650                g_available_heap
                0x00462660                heap_start
                0x00462670                heapCount
                0x00462680                HEAP_START
                0x00462690                g_heap_pointer
                0x004626a0                heapList
                0x00462aa0                HEAP_SIZE
                0x00462ab0                last_size
                0x00462ac0                last_valid
                0x00462ad0                mmblockList
                0x00462ed0                libcHeap
                0x00462ee0                Heap
                0x00462ef0                mmblockCount
                0x00462f00                HEAP_END
                0x00462f10                end = .
                0x00462f10                _end = .
                0x00462f10                __end = .
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
