
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
 .text          0x00452ee8      0x4c0 shellui.o
                0x004531f4                shellTestDisplayBMP
                0x00452ee8                shellCreateEditBox
                0x0045326a                bmpDisplayBMP
                0x00452f82                shellCreateTopBar
 .text          0x004533a8     0x1470 api.o
                0x0045415b                APIShowCurrentProcessInfo
                0x00453948                system11
                0x004539ed                refresh_buffer
                0x0045403d                APISetFocus
                0x004539ab                system14
                0x00453cd2                apiInitBackground
                0x00453f11                APICreateWindow
                0x00454688                apiBeginPaint
                0x00453cd7                MessageBox
                0x004541d9                APIreplace_window
                0x004546cf                apiGetSystemMetrics
                0x0045398a                system13
                0x0045453f                apiDown
                0x004545d7                enterCriticalSection
                0x00454515                apiFOpen
                0x004537fe                system1
                0x00453882                system5
                0x0045438d                api_refresh_screen
                0x00454419                apiGetCursorY
                0x00453c7d                carrega_bitmap_16x16
                0x00454630                exitCriticalSection
                0x004533a8                system_call
                0x0045458b                apiUp
                0x004533d0                apiSystem
                0x004547e8                api_get_window_with_text_input
                0x004539cc                system15
                0x004540ed                APISetActiveWindow
                0x00454471                apiSetClientAreaRect
                0x004541b0                APIredraw_window
                0x004544c3                apiCreateThread
                0x00453c19                SetNextWindowProcedure
                0x004543ed                apiGetCursorX
                0x00453be9                chama_procedimento
                0x00453d00                call_kernel
                0x00453fb9                APIRegisterWindow
                0x00454303                api_strncmp
                0x0045422b                APIminimize_window
                0x0045381f                system2
                0x00453840                system3
                0x00454721                api_get_current_keyboard_responder
                0x0045449a                apiCreateProcess
                0x0045407f                APIGetFocus
                0x004538c4                system7
                0x004538a3                system6
                0x004546c5                apiDefDialog
                0x00453ffb                APICloseWindow
                0x0045465c                initializeCriticalSection
                0x00453927                system10
                0x00453c49                set_cursor
                0x00454202                APImaximize_window
                0x00454361                refresh_screen
                0x00453e80                call_gui
                0x00453906                system9
                0x004546f8                api_set_current_keyboard_responder
                0x00454187                APIresize_window
                0x00454692                apiEndPaint
                0x00453c78                put_char
                0x00453b84                print_string
                0x00454445                apiGetClientAreaRect
                0x00453bba                edit_box
                0x004542d2                kill
                0x00454397                apiReboot
                0x00453ca6                apiShutDown
                0x0045474d                api_set_current_mouse_responder
                0x004542a9                exit
                0x00454254                APIget_foregroung_window
                0x00453861                system4
                0x004543c3                apiSetCursor
                0x00453969                system12
                0x00453b89                vsync
                0x004538e5                system8
                0x004547a2                api_set_window_with_text_input
                0x0045412f                APIGetActiveWindow
                0x00454776                api_get_current_mouse_responder
                0x004542d7                dead_thread_collector
                0x004544ec                apiStartThread
                0x004540ab                APIKillFocus
                0x00454280                APIset_foregroung_window
                0x0045469c                apiPutChar
 .text          0x00454818      0xbf0 stdio.o
                0x00454fd7                putchar
                0x00454f93                sprintf
                0x004551c3                input
                0x0045487d                scroll
                0x004551b9                printf_main
                0x00455003                outbyte
                0x00454a27                app_print
                0x004552ba                stdio_system_call
                0x0045482f                fopen
                0x004552e2                stdioInitialize
                0x00454818                fclose
                0x00455186                _outbyte
                0x00454f78                printf
                0x004549bb                app_clear
 .text          0x00455408      0x960 stdlib.o
                0x004556c3                FreeHeap
                0x00455408                rtGetHeapStart
                0x0045590a                free
                0x004558ac                rand
                0x00455823                stdlibInitMM
                0x004556cd                heapInit
                0x0045541c                rtGetHeapPointer
                0x00455426                rtGetAvailableHeap
                0x00455883                libcInitRT
                0x00455430                heapSetLibcHeap
                0x004558c9                malloc
                0x004556b0                AllocateHeapEx
                0x004554d7                AllocateHeap
                0x00455d01                stdlib_strncmp
                0x00455412                rtGetHeapEnd
                0x0045590f                system
 .text          0x00455d68      0x4a0 string.o
                0x00455fcf                strcspn
                0x00455f32                strcat
                0x00455d68                strcmp
                0x00455f89                bzero
                0x0045610f                strtok_r
                0x00455ec5                memcpy
                0x00455e9c                memoryZeroMemory
                0x00455f62                bcopy
                0x00455f02                strcpy
                0x0045606f                strspn
                0x004561e4                strtok
                0x00455e21                str_cmp
                0x00455dc3                strncmp
                0x00455fa4                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456208      0xdf8 00

.rdata          0x00457000     0x17f0
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x320 shellui.o
 .rdata         0x00457a90      0xd60 main.o

.data           0x004587f0      0x810
                0x004587f0                data = .
                0x004587f0                _data = .
                0x004587f0                __data = .
 *(.data)
 .data          0x004587f0        0x0 crt0.o
 .data          0x004587f0       0x20 main.o
 .data          0x00458810       0x20 shellui.o
 .data          0x00458830        0x0 api.o
 .data          0x00458830        0x0 stdio.o
 .data          0x00458830       0x10 stdlib.o
 .data          0x00458840        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458840      0x7c0 00

.bss            0x00459000     0xaf30
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
 COMMON         0x00462410     0x1230 main.o
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
                0x00462560                current_semaphore
                0x00462570                ShellHook
                0x00462580                shellScreenBufferMaxRows
                0x00462590                shellScreenWidth
                0x004625a0                screen_buffer_pos
                0x004625b0                shellScreenHeight
                0x004625c0                editboxWindow
                0x004625d0                username
                0x004625e0                screen_buffer_x
                0x004625f0                screen_buffer
                0x004635a0                shell_window_y
                0x004635b0                terminal_rect
                0x004635c0                password
                0x004635d0                CursorInfo
                0x004635e0                shellMaxColumns
                0x004635f0                i1Window
                0x00463600                screen_buffer_y
                0x00463610                topbar_editboxWindow
                0x00463620                topbarWindow
                0x00463630                ApplicationInfo
 COMMON         0x00463640      0x8f0 stdlib.o
                0x00463640                current_mmblock
                0x00463650                mm_prev_pointer
                0x00463660                heap_end
                0x00463670                g_available_heap
                0x00463680                heap_start
                0x00463690                heapCount
                0x004636a0                HEAP_START
                0x004636b0                g_heap_pointer
                0x004636c0                heapList
                0x00463ac0                HEAP_SIZE
                0x00463ad0                last_size
                0x00463ae0                last_valid
                0x00463af0                mmblockList
                0x00463ef0                libcHeap
                0x00463f00                Heap
                0x00463f10                mmblockCount
                0x00463f20                HEAP_END
                0x00463f30                end = .
                0x00463f30                _end = .
                0x00463f30                __end = .
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
