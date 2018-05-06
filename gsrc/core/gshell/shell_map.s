
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
 .text          0x00451058     0x2ba0 main.o
                0x00452cab                shellPrompt
                0x004535d7                shellSendMessage
                0x00452e67                shellTestThreads
                0x004536b5                shellTaskList
                0x00451385                shellProcedure
                0x00452640                shellShell
                0x00452bd9                test_operators
                0x00453984                shellShowProcessHeapPointer
                0x00452b98                shellThread
                0x00452785                shellInit
                0x0045381c                shellShowPPID
                0x004539ec                shellShowKernelHeapPointer
                0x0045156f                shellWaitCmd
                0x00452d64                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00453948                shellShowDesktopID
                0x004530f8                shellInsertCharXY
                0x00453142                shellInsertCharPos
                0x00453a60                shellShowPCIInfo
                0x00451587                shellCompare
                0x00452d22                shellClearBuffer
                0x00452f7c                shellRefreshScreen
                0x00452ef7                shellClearScreen
                0x00453460                shellShowSystemInfo
                0x0045317a                shellInsertNextChar
                0x00453ab8                shell_fntos
                0x00453a34                shellShowMemoryInfo
                0x00452dd2                shellTestLoadFile
                0x00453271                move_to
                0x004531a6                shellInsertCR
                0x00453360                shellShowMetrics
                0x00453579                shellASCII
                0x00453894                shellShowGID
                0x00452fcc                shellScroll
                0x00453a8c                shellShowKernelInfo
                0x00453628                shellUpdateWorkingDiretoryString
                0x004531e4                shellInsertNullTerminator
                0x00453858                shellShowUID
                0x004531c5                shellInsertLF
                0x004536a8                shellUpdateCurrentDirectoryID
                0x004535ff                shell_memcpy_bytes
                0x00452b6e                shellSetCursor
                0x00453ba7                shell_gramado_core_init_execve
                0x00453296                shellShowInfo
                0x004534ce                shellShowWindowInfo
                0x004537e0                shellShowPID
                0x004538d0                shellShowUserSessionID
                0x0045390c                shellShowWindowStationID
                0x00452bc5                shellTree
                0x00452bb1                shellHelp
                0x00453203                shellTestMBR
 .text          0x00453bf8      0x5a0 shellui.o
                0x00453fe4                shellTestDisplayBMP
                0x00453d59                shellCreateEditBox
                0x00453bf8                shellTopbarProcedure
                0x0045405a                bmpDisplayBMP
                0x00453e07                shellCreateTopBar
 .text          0x00454198     0x1470 api.o
                0x00454f4b                APIShowCurrentProcessInfo
                0x00454738                system11
                0x004547dd                refresh_buffer
                0x00454e2d                APISetFocus
                0x0045479b                system14
                0x00454ac2                apiInitBackground
                0x00454d01                APICreateWindow
                0x00455478                apiBeginPaint
                0x00454ac7                MessageBox
                0x00454fc9                APIreplace_window
                0x004554bf                apiGetSystemMetrics
                0x0045477a                system13
                0x0045532f                apiDown
                0x004553c7                enterCriticalSection
                0x00455305                apiFOpen
                0x004545ee                system1
                0x00454672                system5
                0x0045517d                api_refresh_screen
                0x00455209                apiGetCursorY
                0x00454a6d                carrega_bitmap_16x16
                0x00455420                exitCriticalSection
                0x00454198                system_call
                0x0045537b                apiUp
                0x004541c0                apiSystem
                0x004555d8                api_get_window_with_text_input
                0x004547bc                system15
                0x00454edd                APISetActiveWindow
                0x00455261                apiSetClientAreaRect
                0x00454fa0                APIredraw_window
                0x004552b3                apiCreateThread
                0x00454a09                SetNextWindowProcedure
                0x004551dd                apiGetCursorX
                0x004549d9                chama_procedimento
                0x00454af0                call_kernel
                0x00454da9                APIRegisterWindow
                0x004550f3                api_strncmp
                0x0045501b                APIminimize_window
                0x0045460f                system2
                0x00454630                system3
                0x00455511                api_get_current_keyboard_responder
                0x0045528a                apiCreateProcess
                0x00454e6f                APIGetFocus
                0x004546b4                system7
                0x00454693                system6
                0x004554b5                apiDefDialog
                0x00454deb                APICloseWindow
                0x0045544c                initializeCriticalSection
                0x00454717                system10
                0x00454a39                set_cursor
                0x00454ff2                APImaximize_window
                0x00455151                refresh_screen
                0x00454c70                call_gui
                0x004546f6                system9
                0x004554e8                api_set_current_keyboard_responder
                0x00454f77                APIresize_window
                0x00455482                apiEndPaint
                0x00454a68                put_char
                0x00454974                print_string
                0x00455235                apiGetClientAreaRect
                0x004549aa                edit_box
                0x004550c2                kill
                0x00455187                apiReboot
                0x00454a96                apiShutDown
                0x0045553d                api_set_current_mouse_responder
                0x00455099                exit
                0x00455044                APIget_foregroung_window
                0x00454651                system4
                0x004551b3                apiSetCursor
                0x00454759                system12
                0x00454979                vsync
                0x004546d5                system8
                0x00455592                api_set_window_with_text_input
                0x00454f1f                APIGetActiveWindow
                0x00455566                api_get_current_mouse_responder
                0x004550c7                dead_thread_collector
                0x004552dc                apiStartThread
                0x00454e9b                APIKillFocus
                0x00455070                APIset_foregroung_window
                0x0045548c                apiPutChar
 .text          0x00455608      0xbf0 stdio.o
                0x00455dc7                putchar
                0x00455d83                sprintf
                0x00455fb3                input
                0x0045566d                scroll
                0x00455fa9                printf_main
                0x00455df3                outbyte
                0x00455817                app_print
                0x004560aa                stdio_system_call
                0x0045561f                fopen
                0x004560d2                stdioInitialize
                0x00455608                fclose
                0x00455f76                _outbyte
                0x00455d68                printf
                0x004557ab                app_clear
 .text          0x004561f8      0x960 stdlib.o
                0x004564b3                FreeHeap
                0x004561f8                rtGetHeapStart
                0x004566fa                free
                0x0045669c                rand
                0x00456613                stdlibInitMM
                0x004564bd                heapInit
                0x0045620c                rtGetHeapPointer
                0x00456216                rtGetAvailableHeap
                0x00456673                libcInitRT
                0x00456220                heapSetLibcHeap
                0x004566b9                malloc
                0x004564a0                AllocateHeapEx
                0x004562c7                AllocateHeap
                0x00456af1                stdlib_strncmp
                0x00456202                rtGetHeapEnd
                0x004566ff                system
 .text          0x00456b58      0x4a0 string.o
                0x00456dbf                strcspn
                0x00456d22                strcat
                0x00456b58                strcmp
                0x00456d79                bzero
                0x00456eff                strtok_r
                0x00456cb5                memcpy
                0x00456c8c                memoryZeroMemory
                0x00456d52                bcopy
                0x00456cf2                strcpy
                0x00456e5f                strspn
                0x00456fd4                strtok
                0x00456c11                str_cmp
                0x00456bb3                strncmp
                0x00456d94                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456ff8        0x8 00

.rdata          0x00457000     0x1fd0
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x680 shellui.o
 .rdata         0x00457df0     0x11e0 main.o

.data           0x00458fd0     0x1030
                0x00458fd0                data = .
                0x00458fd0                _data = .
                0x00458fd0                __data = .
 *(.data)
 .data          0x00458fd0        0x0 crt0.o
 .data          0x00458fd0       0x20 main.o
 .data          0x00458ff0       0x20 shellui.o
 .data          0x00459010        0x0 api.o
 .data          0x00459010        0x0 stdio.o
 .data          0x00459010       0x10 stdlib.o
 .data          0x00459020        0x0 string.o
                0x0045a000                . = ALIGN (0x1000)
 *fill*         0x00459020      0xfe0 00

.bss            0x0045a000     0xd8c0
                0x0045a000                bss = .
                0x0045a000                _bss = .
                0x0045a000                __bss = .
 *(.bss)
 .bss           0x0045a000        0x0 crt0.o
 .bss           0x0045a000       0xe0 main.o
                0x0045a000                ShellFlag
 .bss           0x0045a0e0       0xd0 shellui.o
 .bss           0x0045a1b0       0x30 api.o
 .bss           0x0045a1e0       0x10 stdio.o
 .bss           0x0045a1f0     0x8000 stdlib.o
 .bss           0x004621f0       0x10 string.o
                0x00463000                . = ALIGN (0x1000)
 *fill*         0x00462200      0xe00 00
 COMMON         0x00463000      0xd10 crt0.o
                0x00463000                prompt
                0x00463400                _io_table
                0x00463450                stderr
                0x00463460                prompt_pos
                0x00463470                g_using_gui
                0x00463480                stdin
                0x00463490                prompt_max
                0x004634a0                prompt_err
                0x004638a0                g_columns
                0x004638b0                stdout
                0x004638c0                g_rows
                0x004638d0                prompt_out
                0x00463cd0                g_cursor_y
                0x00463ce0                prompt_status
                0x00463cf0                g_char_attrib
                0x00463d00                g_cursor_x
 COMMON         0x00463d10     0x32c0 main.o
                0x00463d10                ShellMetrics
                0x00463d20                shellStatus
                0x00463d30                CommandHistory
                0x00463d40                shellWindowWidth
                0x00463d50                ClientAreaInfo
                0x00463d60                g_current_disk_id
                0x00463d70                BufferInfo
                0x00463d80                shellError
                0x00463d90                shellWindowHeight
                0x00463da0                lineList
                0x00465da0                root
                0x00465db0                CurrentCommand
                0x00465dc0                shell_info
                0x00465de0                shellScreenBufferMaxColumns
                0x00465df0                g_current_workingdirectory_id
                0x00465e00                shell_window_x
                0x00465e10                i2Window
                0x00465e20                rect
                0x00465e30                backgroung_color
                0x00465e40                shellMaxRows
                0x00465e50                screenbufferList
                0x00465e70                foregroung_color
                0x00465e80                pwd
                0x00465e90                CurrentWindow
                0x00465ea0                topbar_scrollbarWindow
                0x00465eb0                current_semaphore
                0x00465ec0                g_current_volume_id
                0x00465ed0                ShellHook
                0x00465ee0                topbar_checkboxWindow
                0x00465ef0                shellScreenBufferMaxRows
                0x00465f00                shellScreenWidth
                0x00465f10                screen_buffer_pos
                0x00465f20                shellScreenHeight
                0x00465f30                editboxWindow
                0x00465f40                username
                0x00465f50                screen_buffer_x
                0x00465f60                screen_buffer
                0x00466f10                shell_window_y
                0x00466f20                terminal_rect
                0x00466f30                password
                0x00466f40                CursorInfo
                0x00466f50                shellMaxColumns
                0x00466f60                i1Window
                0x00466f70                screen_buffer_y
                0x00466f80                topbar_editboxWindow
                0x00466f90                topbarWindow
                0x00466fa0                ApplicationInfo
                0x00466fb0                current_workingdiretory_string
 COMMON         0x00466fd0      0x8f0 stdlib.o
                0x00466fd0                current_mmblock
                0x00466fe0                mm_prev_pointer
                0x00466ff0                heap_end
                0x00467000                g_available_heap
                0x00467010                heap_start
                0x00467020                heapCount
                0x00467030                HEAP_START
                0x00467040                g_heap_pointer
                0x00467050                heapList
                0x00467450                HEAP_SIZE
                0x00467460                last_size
                0x00467470                last_valid
                0x00467480                mmblockList
                0x00467880                libcHeap
                0x00467890                Heap
                0x004678a0                mmblockCount
                0x004678b0                HEAP_END
                0x004678c0                end = .
                0x004678c0                _end = .
                0x004678c0                __end = .
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
