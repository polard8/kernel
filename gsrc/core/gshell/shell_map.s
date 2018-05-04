
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
 .text          0x00451058     0x2ae0 main.o
                0x00452c07                shellPrompt
                0x00453533                shellSendMessage
                0x00452dc3                shellTestThreads
                0x00453611                shellTaskList
                0x00451380                shellProcedure
                0x0045259c                shellShell
                0x00452b35                test_operators
                0x004538e0                shellShowProcessHeapPointer
                0x00452af4                shellThread
                0x004526e1                shellInit
                0x00453778                shellShowPPID
                0x00453948                shellShowKernelHeapPointer
                0x0045156a                shellWaitCmd
                0x00452cc0                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x004538a4                shellShowDesktopID
                0x00453054                shellInsertCharXY
                0x0045309e                shellInsertCharPos
                0x004539bc                shellShowPCIInfo
                0x00451582                shellCompare
                0x00452c7e                shellClearBuffer
                0x00452ed8                shellRefreshScreen
                0x00452e53                shellClearScreen
                0x004533bc                shellShowSystemInfo
                0x004530d6                shellInsertNextChar
                0x00453a14                shell_fntos
                0x00453990                shellShowMemoryInfo
                0x00452d2e                shellTestLoadFile
                0x004531cd                move_to
                0x00453102                shellInsertCR
                0x004532bc                shellShowMetrics
                0x004534d5                shellASCII
                0x004537f0                shellShowGID
                0x00452f28                shellScroll
                0x004539e8                shellShowKernelInfo
                0x00453584                shellUpdateWorkingDiretoryString
                0x00453140                shellInsertNullTerminator
                0x004537b4                shellShowUID
                0x00453121                shellInsertLF
                0x00453604                shellUpdateCurrentDirectoryID
                0x0045355b                shell_memcpy_bytes
                0x00452aca                shellSetCursor
                0x00453b03                shell_gramado_core_init_execve
                0x004531f2                shellShowInfo
                0x0045342a                shellShowWindowInfo
                0x0045373c                shellShowPID
                0x0045382c                shellShowUserSessionID
                0x00453868                shellShowWindowStationID
                0x00452b21                shellTree
                0x00452b0d                shellHelp
                0x0045315f                shellTestMBR
 .text          0x00453b38      0x5a0 shellui.o
                0x00453f24                shellTestDisplayBMP
                0x00453c99                shellCreateEditBox
                0x00453b38                shellTopbarProcedure
                0x00453f9a                bmpDisplayBMP
                0x00453d47                shellCreateTopBar
 .text          0x004540d8     0x1470 api.o
                0x00454e8b                APIShowCurrentProcessInfo
                0x00454678                system11
                0x0045471d                refresh_buffer
                0x00454d6d                APISetFocus
                0x004546db                system14
                0x00454a02                apiInitBackground
                0x00454c41                APICreateWindow
                0x004553b8                apiBeginPaint
                0x00454a07                MessageBox
                0x00454f09                APIreplace_window
                0x004553ff                apiGetSystemMetrics
                0x004546ba                system13
                0x0045526f                apiDown
                0x00455307                enterCriticalSection
                0x00455245                apiFOpen
                0x0045452e                system1
                0x004545b2                system5
                0x004550bd                api_refresh_screen
                0x00455149                apiGetCursorY
                0x004549ad                carrega_bitmap_16x16
                0x00455360                exitCriticalSection
                0x004540d8                system_call
                0x004552bb                apiUp
                0x00454100                apiSystem
                0x00455518                api_get_window_with_text_input
                0x004546fc                system15
                0x00454e1d                APISetActiveWindow
                0x004551a1                apiSetClientAreaRect
                0x00454ee0                APIredraw_window
                0x004551f3                apiCreateThread
                0x00454949                SetNextWindowProcedure
                0x0045511d                apiGetCursorX
                0x00454919                chama_procedimento
                0x00454a30                call_kernel
                0x00454ce9                APIRegisterWindow
                0x00455033                api_strncmp
                0x00454f5b                APIminimize_window
                0x0045454f                system2
                0x00454570                system3
                0x00455451                api_get_current_keyboard_responder
                0x004551ca                apiCreateProcess
                0x00454daf                APIGetFocus
                0x004545f4                system7
                0x004545d3                system6
                0x004553f5                apiDefDialog
                0x00454d2b                APICloseWindow
                0x0045538c                initializeCriticalSection
                0x00454657                system10
                0x00454979                set_cursor
                0x00454f32                APImaximize_window
                0x00455091                refresh_screen
                0x00454bb0                call_gui
                0x00454636                system9
                0x00455428                api_set_current_keyboard_responder
                0x00454eb7                APIresize_window
                0x004553c2                apiEndPaint
                0x004549a8                put_char
                0x004548b4                print_string
                0x00455175                apiGetClientAreaRect
                0x004548ea                edit_box
                0x00455002                kill
                0x004550c7                apiReboot
                0x004549d6                apiShutDown
                0x0045547d                api_set_current_mouse_responder
                0x00454fd9                exit
                0x00454f84                APIget_foregroung_window
                0x00454591                system4
                0x004550f3                apiSetCursor
                0x00454699                system12
                0x004548b9                vsync
                0x00454615                system8
                0x004554d2                api_set_window_with_text_input
                0x00454e5f                APIGetActiveWindow
                0x004554a6                api_get_current_mouse_responder
                0x00455007                dead_thread_collector
                0x0045521c                apiStartThread
                0x00454ddb                APIKillFocus
                0x00454fb0                APIset_foregroung_window
                0x004553cc                apiPutChar
 .text          0x00455548      0xbf0 stdio.o
                0x00455d07                putchar
                0x00455cc3                sprintf
                0x00455ef3                input
                0x004555ad                scroll
                0x00455ee9                printf_main
                0x00455d33                outbyte
                0x00455757                app_print
                0x00455fea                stdio_system_call
                0x0045555f                fopen
                0x00456012                stdioInitialize
                0x00455548                fclose
                0x00455eb6                _outbyte
                0x00455ca8                printf
                0x004556eb                app_clear
 .text          0x00456138      0x960 stdlib.o
                0x004563f3                FreeHeap
                0x00456138                rtGetHeapStart
                0x0045663a                free
                0x004565dc                rand
                0x00456553                stdlibInitMM
                0x004563fd                heapInit
                0x0045614c                rtGetHeapPointer
                0x00456156                rtGetAvailableHeap
                0x004565b3                libcInitRT
                0x00456160                heapSetLibcHeap
                0x004565f9                malloc
                0x004563e0                AllocateHeapEx
                0x00456207                AllocateHeap
                0x00456a31                stdlib_strncmp
                0x00456142                rtGetHeapEnd
                0x0045663f                system
 .text          0x00456a98      0x4a0 string.o
                0x00456cff                strcspn
                0x00456c62                strcat
                0x00456a98                strcmp
                0x00456cb9                bzero
                0x00456e3f                strtok_r
                0x00456bf5                memcpy
                0x00456bcc                memoryZeroMemory
                0x00456c92                bcopy
                0x00456c32                strcpy
                0x00456d9f                strspn
                0x00456f14                strtok
                0x00456b51                str_cmp
                0x00456af3                strncmp
                0x00456cd4                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456f38       0xc8 00

.rdata          0x00457000     0x1fb0
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x680 shellui.o
 .rdata         0x00457df0     0x11c0 main.o

.data           0x00458fb0       0x50
                0x00458fb0                data = .
                0x00458fb0                _data = .
                0x00458fb0                __data = .
 *(.data)
 .data          0x00458fb0        0x0 crt0.o
 .data          0x00458fb0       0x20 main.o
 .data          0x00458fd0       0x20 shellui.o
 .data          0x00458ff0        0x0 api.o
 .data          0x00458ff0        0x0 stdio.o
 .data          0x00458ff0       0x10 stdlib.o
 .data          0x00459000        0x0 string.o
                0x00459000                . = ALIGN (0x1000)

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
