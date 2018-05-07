
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

.text           0x00451000     0x7000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x2cc0 main.o
                0x00452cdd                shellPrompt
                0x00453609                shellSendMessage
                0x00452e99                shellTestThreads
                0x004536e7                shellTaskList
                0x004513b7                shellProcedure
                0x00452672                shellShell
                0x00452c0b                test_operators
                0x004539b6                shellShowProcessHeapPointer
                0x00452bca                shellThread
                0x004527b7                shellInit
                0x0045384e                shellShowPPID
                0x00453a1e                shellShowKernelHeapPointer
                0x004515a1                shellWaitCmd
                0x00452d96                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x0045397a                shellShowDesktopID
                0x0045312a                shellInsertCharXY
                0x00453174                shellInsertCharPos
                0x00453a92                shellShowPCIInfo
                0x004515b9                shellCompare
                0x00452d54                shellClearBuffer
                0x00452fae                shellRefreshScreen
                0x00453c57                feedterminalDialog
                0x00452f29                shellClearScreen
                0x00453492                shellShowSystemInfo
                0x004531ac                shellInsertNextChar
                0x00453aea                shell_fntos
                0x00453a66                shellShowMemoryInfo
                0x00452e04                shellTestLoadFile
                0x004532a3                move_to
                0x004531d8                shellInsertCR
                0x00453392                shellShowMetrics
                0x004535ab                shellASCII
                0x004538c6                shellShowGID
                0x00452ffe                shellScroll
                0x00453abe                shellShowKernelInfo
                0x0045365a                shellUpdateWorkingDiretoryString
                0x00453216                shellInsertNullTerminator
                0x0045388a                shellShowUID
                0x004531f7                shellInsertLF
                0x004536da                shellUpdateCurrentDirectoryID
                0x00453631                shell_memcpy_bytes
                0x00452ba0                shellSetCursor
                0x00453bd9                shell_gramado_core_init_execve
                0x004532c8                shellShowInfo
                0x00453500                shellShowWindowInfo
                0x00453812                shellShowPID
                0x00453902                shellShowUserSessionID
                0x0045393e                shellShowWindowStationID
                0x00452bf7                shellTree
                0x00452be3                shellHelp
                0x00453235                shellTestMBR
 .text          0x00453d18      0x5a0 shellui.o
                0x00454110                shellTestDisplayBMP
                0x00453e85                shellCreateEditBox
                0x00453d18                shellTopbarProcedure
                0x00454186                bmpDisplayBMP
                0x00453f33                shellCreateTopBar
 .text          0x004542b8     0x1470 api.o
                0x0045506b                APIShowCurrentProcessInfo
                0x00454858                system11
                0x004548fd                refresh_buffer
                0x00454f4d                APISetFocus
                0x004548bb                system14
                0x00454be2                apiInitBackground
                0x00454e21                APICreateWindow
                0x00455598                apiBeginPaint
                0x00454be7                MessageBox
                0x004550e9                APIreplace_window
                0x004555df                apiGetSystemMetrics
                0x0045489a                system13
                0x0045544f                apiDown
                0x004554e7                enterCriticalSection
                0x00455425                apiFOpen
                0x0045470e                system1
                0x00454792                system5
                0x0045529d                api_refresh_screen
                0x00455329                apiGetCursorY
                0x00454b8d                carrega_bitmap_16x16
                0x00455540                exitCriticalSection
                0x004542b8                system_call
                0x0045549b                apiUp
                0x004542e0                apiSystem
                0x004556f8                api_get_window_with_text_input
                0x004548dc                system15
                0x00454ffd                APISetActiveWindow
                0x00455381                apiSetClientAreaRect
                0x004550c0                APIredraw_window
                0x004553d3                apiCreateThread
                0x00454b29                SetNextWindowProcedure
                0x004552fd                apiGetCursorX
                0x00454af9                chama_procedimento
                0x00454c10                call_kernel
                0x00454ec9                APIRegisterWindow
                0x00455213                api_strncmp
                0x0045513b                APIminimize_window
                0x0045472f                system2
                0x00454750                system3
                0x00455631                api_get_current_keyboard_responder
                0x004553aa                apiCreateProcess
                0x00454f8f                APIGetFocus
                0x004547d4                system7
                0x004547b3                system6
                0x004555d5                apiDefDialog
                0x00454f0b                APICloseWindow
                0x0045556c                initializeCriticalSection
                0x00454837                system10
                0x00454b59                set_cursor
                0x00455112                APImaximize_window
                0x00455271                refresh_screen
                0x00454d90                call_gui
                0x00454816                system9
                0x00455608                api_set_current_keyboard_responder
                0x00455097                APIresize_window
                0x004555a2                apiEndPaint
                0x00454b88                put_char
                0x00454a94                print_string
                0x00455355                apiGetClientAreaRect
                0x00454aca                edit_box
                0x004551e2                kill
                0x004552a7                apiReboot
                0x00454bb6                apiShutDown
                0x0045565d                api_set_current_mouse_responder
                0x004551b9                exit
                0x00455164                APIget_foregroung_window
                0x00454771                system4
                0x004552d3                apiSetCursor
                0x00454879                system12
                0x00454a99                vsync
                0x004547f5                system8
                0x004556b2                api_set_window_with_text_input
                0x0045503f                APIGetActiveWindow
                0x00455686                api_get_current_mouse_responder
                0x004551e7                dead_thread_collector
                0x004553fc                apiStartThread
                0x00454fbb                APIKillFocus
                0x00455190                APIset_foregroung_window
                0x004555ac                apiPutChar
 .text          0x00455728      0xbf0 stdio.o
                0x00455ee7                putchar
                0x00455ea3                sprintf
                0x004560d3                input
                0x0045578d                scroll
                0x004560c9                printf_main
                0x00455f13                outbyte
                0x00455937                app_print
                0x004561ca                stdio_system_call
                0x0045573f                fopen
                0x004561f2                stdioInitialize
                0x00455728                fclose
                0x00456096                _outbyte
                0x00455e88                printf
                0x004558cb                app_clear
 .text          0x00456318      0x960 stdlib.o
                0x004565d3                FreeHeap
                0x00456318                rtGetHeapStart
                0x0045681a                free
                0x004567bc                rand
                0x00456733                stdlibInitMM
                0x004565dd                heapInit
                0x0045632c                rtGetHeapPointer
                0x00456336                rtGetAvailableHeap
                0x00456793                libcInitRT
                0x00456340                heapSetLibcHeap
                0x004567d9                malloc
                0x004565c0                AllocateHeapEx
                0x004563e7                AllocateHeap
                0x00456c11                stdlib_strncmp
                0x00456322                rtGetHeapEnd
                0x0045681f                system
 .text          0x00456c78      0x4a0 string.o
                0x00456edf                strcspn
                0x00456e42                strcat
                0x00456c78                strcmp
                0x00456e99                bzero
                0x0045701f                strtok_r
                0x00456dd5                memcpy
                0x00456dac                memoryZeroMemory
                0x00456e72                bcopy
                0x00456e12                strcpy
                0x00456f7f                strspn
                0x004570f4                strtok
                0x00456d31                str_cmp
                0x00456cd3                strncmp
                0x00456eb4                strlen
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457118      0xee8 00

.rdata          0x00458000     0x20b0
 .rdata         0x00458000      0x430 stdlib.o
 .rdata         0x00458430       0x30 stdio.o
 .rdata         0x00458460      0x310 api.o
 .rdata         0x00458770      0x6c0 shellui.o
 .rdata         0x00458e30     0x1280 main.o

.data           0x0045a0b0      0xf50
                0x0045a0b0                data = .
                0x0045a0b0                _data = .
                0x0045a0b0                __data = .
 *(.data)
 .data          0x0045a0b0        0x0 crt0.o
 .data          0x0045a0b0       0x20 main.o
 .data          0x0045a0d0       0x20 shellui.o
 .data          0x0045a0f0        0x0 api.o
 .data          0x0045a0f0        0x0 stdio.o
 .data          0x0045a0f0       0x10 stdlib.o
 .data          0x0045a100        0x0 string.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a100      0xf00 00

.bss            0x0045b000     0xd8c0
                0x0045b000                bss = .
                0x0045b000                _bss = .
                0x0045b000                __bss = .
 *(.bss)
 .bss           0x0045b000        0x0 crt0.o
 .bss           0x0045b000       0xe0 main.o
                0x0045b000                ShellFlag
 .bss           0x0045b0e0       0xd0 shellui.o
 .bss           0x0045b1b0       0x30 api.o
 .bss           0x0045b1e0       0x10 stdio.o
 .bss           0x0045b1f0     0x8000 stdlib.o
 .bss           0x004631f0       0x10 string.o
                0x00464000                . = ALIGN (0x1000)
 *fill*         0x00463200      0xe00 00
 COMMON         0x00464000      0xd10 crt0.o
                0x00464000                prompt
                0x00464400                _io_table
                0x00464450                stderr
                0x00464460                prompt_pos
                0x00464470                g_using_gui
                0x00464480                stdin
                0x00464490                prompt_max
                0x004644a0                prompt_err
                0x004648a0                g_columns
                0x004648b0                stdout
                0x004648c0                g_rows
                0x004648d0                prompt_out
                0x00464cd0                g_cursor_y
                0x00464ce0                prompt_status
                0x00464cf0                g_char_attrib
                0x00464d00                g_cursor_x
 COMMON         0x00464d10     0x32c0 main.o
                0x00464d10                ShellMetrics
                0x00464d20                shellStatus
                0x00464d30                CommandHistory
                0x00464d40                shellWindowWidth
                0x00464d50                ClientAreaInfo
                0x00464d60                g_current_disk_id
                0x00464d70                BufferInfo
                0x00464d80                shellError
                0x00464d90                shellWindowHeight
                0x00464da0                lineList
                0x00466da0                root
                0x00466db0                CurrentCommand
                0x00466dc0                shell_info
                0x00466de0                shellScreenBufferMaxColumns
                0x00466df0                g_current_workingdirectory_id
                0x00466e00                shell_window_x
                0x00466e10                i2Window
                0x00466e20                rect
                0x00466e30                backgroung_color
                0x00466e40                shellMaxRows
                0x00466e50                screenbufferList
                0x00466e70                foregroung_color
                0x00466e80                pwd
                0x00466e90                CurrentWindow
                0x00466ea0                topbar_scrollbarWindow
                0x00466eb0                current_semaphore
                0x00466ec0                g_current_volume_id
                0x00466ed0                ShellHook
                0x00466ee0                topbar_checkboxWindow
                0x00466ef0                shellScreenBufferMaxRows
                0x00466f00                shellScreenWidth
                0x00466f10                screen_buffer_pos
                0x00466f20                shellScreenHeight
                0x00466f30                editboxWindow
                0x00466f40                username
                0x00466f50                screen_buffer_x
                0x00466f60                screen_buffer
                0x00467f10                shell_window_y
                0x00467f20                terminal_rect
                0x00467f30                password
                0x00467f40                CursorInfo
                0x00467f50                shellMaxColumns
                0x00467f60                i1Window
                0x00467f70                screen_buffer_y
                0x00467f80                topbar_editboxWindow
                0x00467f90                topbarWindow
                0x00467fa0                ApplicationInfo
                0x00467fb0                current_workingdiretory_string
 COMMON         0x00467fd0      0x8f0 stdlib.o
                0x00467fd0                current_mmblock
                0x00467fe0                mm_prev_pointer
                0x00467ff0                heap_end
                0x00468000                g_available_heap
                0x00468010                heap_start
                0x00468020                heapCount
                0x00468030                HEAP_START
                0x00468040                g_heap_pointer
                0x00468050                heapList
                0x00468450                HEAP_SIZE
                0x00468460                last_size
                0x00468470                last_valid
                0x00468480                mmblockList
                0x00468880                libcHeap
                0x00468890                Heap
                0x004688a0                mmblockCount
                0x004688b0                HEAP_END
                0x004688c0                end = .
                0x004688c0                _end = .
                0x004688c0                __end = .
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
