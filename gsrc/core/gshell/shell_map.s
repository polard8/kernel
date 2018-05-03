
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x400             crt0.o
CommandHistory      0x10              main.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
g_current_disk_id   0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              crt0.o
shellError          0x10              main.o
stderr              0x10              crt0.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
lineList            0x2000            main.o
root                0x10              main.o
CurrentCommand      0x10              main.o
mm_prev_pointer     0x10              stdlib.o
shell_info          0x20              main.o
shellScreenBufferMaxColumns
                    0x10              main.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
g_current_workingdirectory_id
                    0x10              main.o
shell_window_x      0x10              main.o
i2Window            0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
screenbufferList    0x20              main.o
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
prompt_err          0x400             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
g_current_volume_id
                    0x10              main.o
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
prompt_out          0x400             crt0.o
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
current_workingdiretory_string
                    0x20              main.o
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
 .text          0x00451058     0x2870 main.o
                0x00452b87                shellPrompt
                0x004534b3                shellSendMessage
                0x00452d43                shellTestThreads
                0x00453591                shellTaskList
                0x00451380                shellProcedure
                0x0045251c                shellShell
                0x00452ab5                test_operators
                0x00453860                shellShowProcessHeapPointer
                0x00452a74                shellThread
                0x00452661                shellInit
                0x004536f8                shellShowPPID
                0x0045156a                shellWaitCmd
                0x00452c40                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00453824                shellShowDesktopID
                0x00452fd4                shellInsertCharXY
                0x0045301e                shellInsertCharPos
                0x00451582                shellCompare
                0x00452bfe                shellClearBuffer
                0x00452e58                shellRefreshScreen
                0x00452dd3                shellClearScreen
                0x0045333c                shellShowSystemInfo
                0x00453056                shellInsertNextChar
                0x00452cae                shellTestLoadFile
                0x0045314d                move_to
                0x00453082                shellInsertCR
                0x0045323c                shellShowMetrics
                0x00453455                shellASCII
                0x00453770                shellShowGID
                0x00452ea8                shellScroll
                0x00453504                shellUpdateWorkingDiretoryString
                0x004530c0                shellInsertNullTerminator
                0x00453734                shellShowUID
                0x004530a1                shellInsertLF
                0x00453584                shellUpdateCurrentDirectoryID
                0x004534db                shell_memcpy_bytes
                0x00452a4a                shellSetCursor
                0x00453172                shellShowInfo
                0x004533aa                shellShowWindowInfo
                0x004536bc                shellShowPID
                0x004537ac                shellShowUserSessionID
                0x004537e8                shellShowWindowStationID
                0x00452aa1                shellTree
                0x00452a8d                shellHelp
                0x004530df                shellTestMBR
 .text          0x004538c8      0x5a0 shellui.o
                0x00453cb4                shellTestDisplayBMP
                0x00453a29                shellCreateEditBox
                0x004538c8                shellTopbarProcedure
                0x00453d2a                bmpDisplayBMP
                0x00453ad7                shellCreateTopBar
 .text          0x00453e68     0x1470 api.o
                0x00454c1b                APIShowCurrentProcessInfo
                0x00454408                system11
                0x004544ad                refresh_buffer
                0x00454afd                APISetFocus
                0x0045446b                system14
                0x00454792                apiInitBackground
                0x004549d1                APICreateWindow
                0x00455148                apiBeginPaint
                0x00454797                MessageBox
                0x00454c99                APIreplace_window
                0x0045518f                apiGetSystemMetrics
                0x0045444a                system13
                0x00454fff                apiDown
                0x00455097                enterCriticalSection
                0x00454fd5                apiFOpen
                0x004542be                system1
                0x00454342                system5
                0x00454e4d                api_refresh_screen
                0x00454ed9                apiGetCursorY
                0x0045473d                carrega_bitmap_16x16
                0x004550f0                exitCriticalSection
                0x00453e68                system_call
                0x0045504b                apiUp
                0x00453e90                apiSystem
                0x004552a8                api_get_window_with_text_input
                0x0045448c                system15
                0x00454bad                APISetActiveWindow
                0x00454f31                apiSetClientAreaRect
                0x00454c70                APIredraw_window
                0x00454f83                apiCreateThread
                0x004546d9                SetNextWindowProcedure
                0x00454ead                apiGetCursorX
                0x004546a9                chama_procedimento
                0x004547c0                call_kernel
                0x00454a79                APIRegisterWindow
                0x00454dc3                api_strncmp
                0x00454ceb                APIminimize_window
                0x004542df                system2
                0x00454300                system3
                0x004551e1                api_get_current_keyboard_responder
                0x00454f5a                apiCreateProcess
                0x00454b3f                APIGetFocus
                0x00454384                system7
                0x00454363                system6
                0x00455185                apiDefDialog
                0x00454abb                APICloseWindow
                0x0045511c                initializeCriticalSection
                0x004543e7                system10
                0x00454709                set_cursor
                0x00454cc2                APImaximize_window
                0x00454e21                refresh_screen
                0x00454940                call_gui
                0x004543c6                system9
                0x004551b8                api_set_current_keyboard_responder
                0x00454c47                APIresize_window
                0x00455152                apiEndPaint
                0x00454738                put_char
                0x00454644                print_string
                0x00454f05                apiGetClientAreaRect
                0x0045467a                edit_box
                0x00454d92                kill
                0x00454e57                apiReboot
                0x00454766                apiShutDown
                0x0045520d                api_set_current_mouse_responder
                0x00454d69                exit
                0x00454d14                APIget_foregroung_window
                0x00454321                system4
                0x00454e83                apiSetCursor
                0x00454429                system12
                0x00454649                vsync
                0x004543a5                system8
                0x00455262                api_set_window_with_text_input
                0x00454bef                APIGetActiveWindow
                0x00455236                api_get_current_mouse_responder
                0x00454d97                dead_thread_collector
                0x00454fac                apiStartThread
                0x00454b6b                APIKillFocus
                0x00454d40                APIset_foregroung_window
                0x0045515c                apiPutChar
 .text          0x004552d8      0xbf0 stdio.o
                0x00455a97                putchar
                0x00455a53                sprintf
                0x00455c83                input
                0x0045533d                scroll
                0x00455c79                printf_main
                0x00455ac3                outbyte
                0x004554e7                app_print
                0x00455d7a                stdio_system_call
                0x004552ef                fopen
                0x00455da2                stdioInitialize
                0x004552d8                fclose
                0x00455c46                _outbyte
                0x00455a38                printf
                0x0045547b                app_clear
 .text          0x00455ec8      0x960 stdlib.o
                0x00456183                FreeHeap
                0x00455ec8                rtGetHeapStart
                0x004563ca                free
                0x0045636c                rand
                0x004562e3                stdlibInitMM
                0x0045618d                heapInit
                0x00455edc                rtGetHeapPointer
                0x00455ee6                rtGetAvailableHeap
                0x00456343                libcInitRT
                0x00455ef0                heapSetLibcHeap
                0x00456389                malloc
                0x00456170                AllocateHeapEx
                0x00455f97                AllocateHeap
                0x004567c1                stdlib_strncmp
                0x00455ed2                rtGetHeapEnd
                0x004563cf                system
 .text          0x00456828      0x4a0 string.o
                0x00456a8f                strcspn
                0x004569f2                strcat
                0x00456828                strcmp
                0x00456a49                bzero
                0x00456bcf                strtok_r
                0x00456985                memcpy
                0x0045695c                memoryZeroMemory
                0x00456a22                bcopy
                0x004569c2                strcpy
                0x00456b2f                strspn
                0x00456ca4                strtok
                0x004568e1                str_cmp
                0x00456883                strncmp
                0x00456a64                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456cc8      0x338 00

.rdata          0x00457000     0x1f90
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x680 shellui.o
 .rdata         0x00457df0     0x11a0 main.o

.data           0x00458f90       0x70
                0x00458f90                data = .
                0x00458f90                _data = .
                0x00458f90                __data = .
 *(.data)
 .data          0x00458f90        0x0 crt0.o
 .data          0x00458f90       0x20 main.o
 .data          0x00458fb0       0x20 shellui.o
 .data          0x00458fd0        0x0 api.o
 .data          0x00458fd0        0x0 stdio.o
 .data          0x00458fd0       0x10 stdlib.o
 .data          0x00458fe0        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458fe0       0x20 00

.bss            0x00459000     0xd8c0
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
 COMMON         0x00462000      0xd10 crt0.o
                0x00462000                prompt
                0x00462400                _io_table
                0x00462450                stderr
                0x00462460                prompt_pos
                0x00462470                g_using_gui
                0x00462480                stdin
                0x00462490                prompt_max
                0x004624a0                prompt_err
                0x004628a0                g_columns
                0x004628b0                stdout
                0x004628c0                g_rows
                0x004628d0                prompt_out
                0x00462cd0                g_cursor_y
                0x00462ce0                prompt_status
                0x00462cf0                g_char_attrib
                0x00462d00                g_cursor_x
 COMMON         0x00462d10     0x32c0 main.o
                0x00462d10                ShellMetrics
                0x00462d20                shellStatus
                0x00462d30                CommandHistory
                0x00462d40                shellWindowWidth
                0x00462d50                ClientAreaInfo
                0x00462d60                g_current_disk_id
                0x00462d70                BufferInfo
                0x00462d80                shellError
                0x00462d90                shellWindowHeight
                0x00462da0                lineList
                0x00464da0                root
                0x00464db0                CurrentCommand
                0x00464dc0                shell_info
                0x00464de0                shellScreenBufferMaxColumns
                0x00464df0                g_current_workingdirectory_id
                0x00464e00                shell_window_x
                0x00464e10                i2Window
                0x00464e20                rect
                0x00464e30                backgroung_color
                0x00464e40                shellMaxRows
                0x00464e50                screenbufferList
                0x00464e70                foregroung_color
                0x00464e80                pwd
                0x00464e90                CurrentWindow
                0x00464ea0                topbar_scrollbarWindow
                0x00464eb0                current_semaphore
                0x00464ec0                g_current_volume_id
                0x00464ed0                ShellHook
                0x00464ee0                topbar_checkboxWindow
                0x00464ef0                shellScreenBufferMaxRows
                0x00464f00                shellScreenWidth
                0x00464f10                screen_buffer_pos
                0x00464f20                shellScreenHeight
                0x00464f30                editboxWindow
                0x00464f40                username
                0x00464f50                screen_buffer_x
                0x00464f60                screen_buffer
                0x00465f10                shell_window_y
                0x00465f20                terminal_rect
                0x00465f30                password
                0x00465f40                CursorInfo
                0x00465f50                shellMaxColumns
                0x00465f60                i1Window
                0x00465f70                screen_buffer_y
                0x00465f80                topbar_editboxWindow
                0x00465f90                topbarWindow
                0x00465fa0                ApplicationInfo
                0x00465fb0                current_workingdiretory_string
 COMMON         0x00465fd0      0x8f0 stdlib.o
                0x00465fd0                current_mmblock
                0x00465fe0                mm_prev_pointer
                0x00465ff0                heap_end
                0x00466000                g_available_heap
                0x00466010                heap_start
                0x00466020                heapCount
                0x00466030                HEAP_START
                0x00466040                g_heap_pointer
                0x00466050                heapList
                0x00466450                HEAP_SIZE
                0x00466460                last_size
                0x00466470                last_valid
                0x00466480                mmblockList
                0x00466880                libcHeap
                0x00466890                Heap
                0x004668a0                mmblockCount
                0x004668b0                HEAP_END
                0x004668c0                end = .
                0x004668c0                _end = .
                0x004668c0                __end = .
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
