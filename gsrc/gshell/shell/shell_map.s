
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
topbar_scrollbarWindow
                    0x10              main.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
topbar_checkboxWindow
                    0x10              main.o
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
editboxWindow       0x10              main.o
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
topbar_editboxWindow
                    0x10              main.o
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

.text           0x00451000     0x6000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x1e90 main.o
                0x00452637                shellPrompt
                0x00452eb6                shellSendMessage
                0x00452775                shellTestThreads
                0x00451357                shellProcedure
                0x00452078                shellShell
                0x00452565                test_operators
                0x00452524                shellThread
                0x0045215d                shellInit
                0x004514ba                shellWaitCmd
                0x00451058                GramadoMain
                0x004529f9                shellInsertCharXY
                0x00452a43                shellInsertCharPos
                0x004514d2                shellCompare
                0x0045269e                shellClearBuffer
                0x0045288a                shellRefreshScreen
                0x00452805                shellClearScreen
                0x00452d3f                shellShowSystemInfo
                0x00452a7b                shellInsertNextChar
                0x004526e0                shellTestLoadFile
                0x00452b50                move_to
                0x00452aa7                shellInsertCR
                0x00452c3f                shellShowMetrics
                0x00452e58                shellASCII
                0x004528da                shellScroll
                0x00452ae5                shellInsertNullTerminator
                0x00452ac6                shellInsertLF
                0x004524fa                shellSetCursor
                0x00452b75                shellShowInfo
                0x00452dad                shellShowWindowInfo
                0x00452551                shellTree
                0x0045253d                shellHelp
                0x00452b04                shellTestMBR
 .text          0x00452ee8      0x5e0 shellui.o
                0x00453318                shellTestDisplayBMP
                0x00452ee8                shellCreateEditBox
                0x0045338e                bmpDisplayBMP
                0x00452f82                shellCreateTopBar
 .text          0x004534c8     0x1470 api.o
                0x0045427b                APIShowCurrentProcessInfo
                0x00453a68                system11
                0x00453b0d                refresh_buffer
                0x0045415d                APISetFocus
                0x00453acb                system14
                0x00453df2                apiInitBackground
                0x00454031                APICreateWindow
                0x004547a8                apiBeginPaint
                0x00453df7                MessageBox
                0x004542f9                APIreplace_window
                0x004547ef                apiGetSystemMetrics
                0x00453aaa                system13
                0x0045465f                apiDown
                0x004546f7                enterCriticalSection
                0x00454635                apiFOpen
                0x0045391e                system1
                0x004539a2                system5
                0x004544ad                api_refresh_screen
                0x00454539                apiGetCursorY
                0x00453d9d                carrega_bitmap_16x16
                0x00454750                exitCriticalSection
                0x004534c8                system_call
                0x004546ab                apiUp
                0x004534f0                apiSystem
                0x00454908                api_get_window_with_text_input
                0x00453aec                system15
                0x0045420d                APISetActiveWindow
                0x00454591                apiSetClientAreaRect
                0x004542d0                APIredraw_window
                0x004545e3                apiCreateThread
                0x00453d39                SetNextWindowProcedure
                0x0045450d                apiGetCursorX
                0x00453d09                chama_procedimento
                0x00453e20                call_kernel
                0x004540d9                APIRegisterWindow
                0x00454423                api_strncmp
                0x0045434b                APIminimize_window
                0x0045393f                system2
                0x00453960                system3
                0x00454841                api_get_current_keyboard_responder
                0x004545ba                apiCreateProcess
                0x0045419f                APIGetFocus
                0x004539e4                system7
                0x004539c3                system6
                0x004547e5                apiDefDialog
                0x0045411b                APICloseWindow
                0x0045477c                initializeCriticalSection
                0x00453a47                system10
                0x00453d69                set_cursor
                0x00454322                APImaximize_window
                0x00454481                refresh_screen
                0x00453fa0                call_gui
                0x00453a26                system9
                0x00454818                api_set_current_keyboard_responder
                0x004542a7                APIresize_window
                0x004547b2                apiEndPaint
                0x00453d98                put_char
                0x00453ca4                print_string
                0x00454565                apiGetClientAreaRect
                0x00453cda                edit_box
                0x004543f2                kill
                0x004544b7                apiReboot
                0x00453dc6                apiShutDown
                0x0045486d                api_set_current_mouse_responder
                0x004543c9                exit
                0x00454374                APIget_foregroung_window
                0x00453981                system4
                0x004544e3                apiSetCursor
                0x00453a89                system12
                0x00453ca9                vsync
                0x00453a05                system8
                0x004548c2                api_set_window_with_text_input
                0x0045424f                APIGetActiveWindow
                0x00454896                api_get_current_mouse_responder
                0x004543f7                dead_thread_collector
                0x0045460c                apiStartThread
                0x004541cb                APIKillFocus
                0x004543a0                APIset_foregroung_window
                0x004547bc                apiPutChar
 .text          0x00454938      0xbf0 stdio.o
                0x004550f7                putchar
                0x004550b3                sprintf
                0x004552e3                input
                0x0045499d                scroll
                0x004552d9                printf_main
                0x00455123                outbyte
                0x00454b47                app_print
                0x004553da                stdio_system_call
                0x0045494f                fopen
                0x00455402                stdioInitialize
                0x00454938                fclose
                0x004552a6                _outbyte
                0x00455098                printf
                0x00454adb                app_clear
 .text          0x00455528      0x960 stdlib.o
                0x004557e3                FreeHeap
                0x00455528                rtGetHeapStart
                0x00455a2a                free
                0x004559cc                rand
                0x00455943                stdlibInitMM
                0x004557ed                heapInit
                0x0045553c                rtGetHeapPointer
                0x00455546                rtGetAvailableHeap
                0x004559a3                libcInitRT
                0x00455550                heapSetLibcHeap
                0x004559e9                malloc
                0x004557d0                AllocateHeapEx
                0x004555f7                AllocateHeap
                0x00455e21                stdlib_strncmp
                0x00455532                rtGetHeapEnd
                0x00455a2f                system
 .text          0x00455e88      0x4a0 string.o
                0x004560ef                strcspn
                0x00456052                strcat
                0x00455e88                strcmp
                0x004560a9                bzero
                0x0045622f                strtok_r
                0x00455fe5                memcpy
                0x00455fbc                memoryZeroMemory
                0x00456082                bcopy
                0x00456022                strcpy
                0x0045618f                strspn
                0x00456304                strtok
                0x00455f41                str_cmp
                0x00455ee3                strncmp
                0x004560c4                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456328      0xcd8 00

.rdata          0x00457000     0x1810
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x340 shellui.o
 .rdata         0x00457ab0      0xd60 main.o

.data           0x00458810      0x7f0
                0x00458810                data = .
                0x00458810                _data = .
                0x00458810                __data = .
 *(.data)
 .data          0x00458810        0x0 crt0.o
 .data          0x00458810       0x20 main.o
 .data          0x00458830       0x20 shellui.o
 .data          0x00458850        0x0 api.o
 .data          0x00458850        0x0 stdio.o
 .data          0x00458850       0x10 stdlib.o
 .data          0x00458860        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458860      0x7a0 00

.bss            0x00459000     0xaf50
                0x00459000                bss = .
                0x00459000                _bss = .
                0x00459000                __bss = .
 *(.bss)
 .bss           0x00459000        0x0 crt0.o
 .bss           0x00459000       0xe0 main.o
                0x00459000                ShellFlag
 .bss           0x004590e0       0xd0 shellui.o
 .bss           0x004591b0       0x30 api.o
 .bss           0x004591e0       0x10 stdio.o
 .bss           0x004591f0     0x8000 stdlib.o
 .bss           0x004611f0       0x10 string.o
                0x00462000                . = ALIGN (0x1000)
 *fill*         0x00461200      0xe00 00
 COMMON         0x00462000      0x410 crt0.o
                0x00462000                prompt
                0x00462100                _io_table
                0x00462150                stderr
                0x00462160                prompt_pos
                0x00462170                g_using_gui
                0x00462180                stdin
                0x00462190                prompt_max
                0x004621a0                prompt_err
                0x004622a0                g_columns
                0x004622b0                stdout
                0x004622c0                g_rows
                0x004622d0                prompt_out
                0x004623d0                g_cursor_y
                0x004623e0                prompt_status
                0x004623f0                g_char_attrib
                0x00462400                g_cursor_x
 COMMON         0x00462410     0x1250 main.o
                0x00462410                ShellMetrics
                0x00462420                shellStatus
                0x00462430                CommandHistory
                0x00462440                shellWindowWidth
                0x00462450                ClientAreaInfo
                0x00462460                BufferInfo
                0x00462470                shellError
                0x00462480                shellWindowHeight
                0x00462490                root
                0x004624a0                CurrentCommand
                0x004624b0                shell_info
                0x004624d0                shellScreenBufferMaxColumns
                0x004624e0                shell_window_x
                0x004624f0                i2Window
                0x00462500                rect
                0x00462510                backgroung_color
                0x00462520                shellMaxRows
                0x00462530                foregroung_color
                0x00462540                pwd
                0x00462550                CurrentWindow
                0x00462560                topbar_scrollbarWindow
                0x00462570                current_semaphore
                0x00462580                ShellHook
                0x00462590                topbar_checkboxWindow
                0x004625a0                shellScreenBufferMaxRows
                0x004625b0                shellScreenWidth
                0x004625c0                screen_buffer_pos
                0x004625d0                shellScreenHeight
                0x004625e0                editboxWindow
                0x004625f0                username
                0x00462600                screen_buffer_x
                0x00462610                screen_buffer
                0x004635c0                shell_window_y
                0x004635d0                terminal_rect
                0x004635e0                password
                0x004635f0                CursorInfo
                0x00463600                shellMaxColumns
                0x00463610                i1Window
                0x00463620                screen_buffer_y
                0x00463630                topbar_editboxWindow
                0x00463640                topbarWindow
                0x00463650                ApplicationInfo
 COMMON         0x00463660      0x8f0 stdlib.o
                0x00463660                current_mmblock
                0x00463670                mm_prev_pointer
                0x00463680                heap_end
                0x00463690                g_available_heap
                0x004636a0                heap_start
                0x004636b0                heapCount
                0x004636c0                HEAP_START
                0x004636d0                g_heap_pointer
                0x004636e0                heapList
                0x00463ae0                HEAP_SIZE
                0x00463af0                last_size
                0x00463b00                last_valid
                0x00463b10                mmblockList
                0x00463f10                libcHeap
                0x00463f20                Heap
                0x00463f30                mmblockCount
                0x00463f40                HEAP_END
                0x00463f50                end = .
                0x00463f50                _end = .
                0x00463f50                __end = .
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
