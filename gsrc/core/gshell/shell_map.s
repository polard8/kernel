
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x400             crt0.o
CommandHistory      0x10              main.o
EOF_Reached         0x10              main.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
g_current_disk_id   0x10              main.o
BufferInfo          0x10              main.o
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
shell_name          0x10              main.o
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
Streams             0x80              crt0.o
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
 .head_x86      0x00451000       0x24 head.o
                0x00451000                shell_entry_point
                0x00451018                VECTOR
 *(.text)
 .text          0x00451024       0x80 crt0.o
                0x00451024                crt0
 .text          0x004510a4     0x2da0 main.o
                0x00452d10                shellPrompt
                0x004535de                shellSendMessage
                0x00452ecc                shellTestThreads
                0x004536bc                shellTaskList
                0x0045140c                shellProcedure
                0x0045271d                shellShell
                0x0045398b                shellShowProcessHeapPointer
                0x00452ccf                shellThread
                0x00453d4c                concat
                0x00452862                shellInit
                0x00453823                shellShowPPID
                0x004539f3                shellShowKernelHeapPointer
                0x00451621                shellWaitCmd
                0x00452dc9                shellShowScreenBuffer
                0x00453e2b                reader_loop
                0x004510a4                GramadoMain
                0x0045394f                shellShowDesktopID
                0x0045315d                shellInsertCharXY
                0x004531a7                shellInsertCharPos
                0x00453ce0                die
                0x00453a67                shellShowPCIInfo
                0x00451639                shellCompare
                0x00452d87                shellClearBuffer
                0x00452fe1                shellRefreshScreen
                0x00453c24                feedterminalDialog
                0x00452f5c                shellClearScreen
                0x004534c5                shellShowSystemInfo
                0x004531df                shellInsertNextChar
                0x00453abf                shell_fntos
                0x00453a3b                shellShowMemoryInfo
                0x00452e37                shellTestLoadFile
                0x004532d6                move_to
                0x0045320b                shellInsertCR
                0x004533c5                shellShowMetrics
                0x0045389b                shellShowGID
                0x00453031                shellScroll
                0x00453a93                shellShowKernelInfo
                0x0045362f                shellUpdateWorkingDiretoryString
                0x00453249                shellInsertNullTerminator
                0x0045385f                shellShowUID
                0x0045322a                shellInsertLF
                0x004536af                shellUpdateCurrentDirectoryID
                0x00453606                shell_memcpy_bytes
                0x00452ca5                shellSetCursor
                0x00453bae                shell_gramado_core_init_execve
                0x004532fb                shellShowInfo
                0x00453533                shellShowWindowInfo
                0x004537e7                shellShowPID
                0x00453de4                error
                0x004538d7                shellShowUserSessionID
                0x00453913                shellShowWindowStationID
                0x00453d21                xmalloc
                0x00452cfc                shellTree
                0x00452ce8                shellHelp
                0x00453268                shellTestMBR
 .text          0x00453e44      0x5a0 shellui.o
                0x0045423c                shellTestDisplayBMP
                0x00453fb1                shellCreateEditBox
                0x00453e44                shellTopbarProcedure
                0x004542b2                bmpDisplayBMP
                0x0045405f                shellCreateTopBar
 .text          0x004543e4     0x1530 api.o
                0x00455197                APIShowCurrentProcessInfo
                0x004558e7                api_getchar
                0x00454984                system11
                0x00454a29                refresh_buffer
                0x00455079                APISetFocus
                0x004549e7                system14
                0x00454d0e                apiInitBackground
                0x00454f4d                APICreateWindow
                0x004556c4                apiBeginPaint
                0x00454d13                MessageBox
                0x00455215                APIreplace_window
                0x0045570b                apiGetSystemMetrics
                0x004549c6                system13
                0x0045557b                apiDown
                0x00455613                enterCriticalSection
                0x00455850                gramadocore_init_execve
                0x00455551                apiFOpen
                0x0045483a                system1
                0x004548be                system5
                0x004553c9                api_refresh_screen
                0x0045586e                apiDialog
                0x00455455                apiGetCursorY
                0x00454cb9                carrega_bitmap_16x16
                0x0045566c                exitCriticalSection
                0x004543e4                system_call
                0x004555c7                apiUp
                0x0045440c                apiSystem
                0x00455824                api_get_window_with_text_input
                0x00454a08                system15
                0x00455129                APISetActiveWindow
                0x004554ad                apiSetClientAreaRect
                0x004551ec                APIredraw_window
                0x004554ff                apiCreateThread
                0x00454c55                SetNextWindowProcedure
                0x00455429                apiGetCursorX
                0x00454c25                chama_procedimento
                0x00454d3c                call_kernel
                0x00454ff5                APIRegisterWindow
                0x0045533f                api_strncmp
                0x00455267                APIminimize_window
                0x0045485b                system2
                0x0045487c                system3
                0x0045575d                api_get_current_keyboard_responder
                0x004554d6                apiCreateProcess
                0x004550bb                APIGetFocus
                0x00454900                system7
                0x004548df                system6
                0x00455701                apiDefDialog
                0x00455037                APICloseWindow
                0x00455698                initializeCriticalSection
                0x00454963                system10
                0x00454c85                set_cursor
                0x0045523e                APImaximize_window
                0x00455864                execve
                0x0045539d                refresh_screen
                0x00454ebc                call_gui
                0x00454942                system9
                0x0045585a                fork
                0x00455734                api_set_current_keyboard_responder
                0x004551c3                APIresize_window
                0x004556ce                apiEndPaint
                0x00454cb4                put_char
                0x00454bc0                print_string
                0x00455481                apiGetClientAreaRect
                0x00454bf6                edit_box
                0x0045530e                kill
                0x004553d3                apiReboot
                0x00454ce2                apiShutDown
                0x00455789                api_set_current_mouse_responder
                0x004552e5                exit
                0x00455290                APIget_foregroung_window
                0x0045489d                system4
                0x004553ff                apiSetCursor
                0x004549a5                system12
                0x00454bc5                vsync
                0x00454921                system8
                0x004557de                api_set_window_with_text_input
                0x0045516b                APIGetActiveWindow
                0x004557b2                api_get_current_mouse_responder
                0x00455313                dead_thread_collector
                0x00455528                apiStartThread
                0x004550e7                APIKillFocus
                0x004552bc                APIset_foregroung_window
                0x004556d8                apiPutChar
 .text          0x00455914     0x1110 stdio.o
                0x0045625b                putchar
                0x00455914                stdio_fntos
                0x00456217                sprintf
                0x004568ee                feof
                0x004569ce                fputc
                0x004567a1                fputs
                0x0045692c                ferror
                0x00456447                input
                0x00455b01                scroll
                0x0045643d                printf_main
                0x00456816                gets
                0x00456287                outbyte
                0x00455cab                app_print
                0x004566bc                fflush
                0x0045672c                fprintf
                0x0045653e                stdio_system_call
                0x00455a69                fopen
                0x00456566                getchar
                0x00456598                stdioInitialize
                0x0045688b                fgetc
                0x00455a03                fclose
                0x00456954                fseek
                0x0045640a                _outbyte
                0x004561fc                printf
                0x00455c3f                app_clear
 .text          0x00456a24      0x960 stdlib.o
                0x00456cdf                FreeHeap
                0x00456a24                rtGetHeapStart
                0x00456f26                free
                0x00456ec8                rand
                0x00456e3f                stdlibInitMM
                0x00456ce9                heapInit
                0x00456a38                rtGetHeapPointer
                0x00456a42                rtGetAvailableHeap
                0x00456e9f                libcInitRT
                0x00456a4c                heapSetLibcHeap
                0x00456ee5                malloc
                0x00456ccc                AllocateHeapEx
                0x00456af3                AllocateHeap
                0x0045731d                stdlib_strncmp
                0x00456a2e                rtGetHeapEnd
                0x00456f2b                system
 .text          0x00457384      0x4a0 string.o
                0x004575eb                strcspn
                0x0045754e                strcat
                0x00457384                strcmp
                0x004575a5                bzero
                0x0045772b                strtok_r
                0x004574e1                memcpy
                0x004574b8                memoryZeroMemory
                0x0045757e                bcopy
                0x0045751e                strcpy
                0x0045768b                strspn
                0x00457800                strtok
                0x0045743d                str_cmp
                0x004573df                strncmp
                0x004575c0                strlen
 .text          0x00457824       0x90 conio.o
                0x00457892                getche
                0x00457824                putch
                0x00457847                cputs
                0x0045787b                getch
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x004578b4      0x74c 00

.rdata          0x00458000     0x2290
 .rdata         0x00458000       0x10 conio.o
 .rdata         0x00458010      0x430 stdlib.o
 .rdata         0x00458440       0x40 stdio.o
 .rdata         0x00458480      0x320 api.o
 .rdata         0x004587a0      0x6c0 shellui.o
 .rdata         0x00458e60     0x1380 main.o
 .rdata         0x0045a1e0       0xb0 crt0.o

.data           0x0045a290      0xd70
                0x0045a290                data = .
                0x0045a290                _data = .
                0x0045a290                __data = .
 *(.data)
 .data          0x0045a290       0x30 crt0.o
 .data          0x0045a2c0       0x20 main.o
                0x0045a2d8                shell_config_file
 .data          0x0045a2e0       0x20 shellui.o
 .data          0x0045a300        0x0 api.o
 .data          0x0045a300        0x0 stdio.o
 .data          0x0045a300       0x10 stdlib.o
 .data          0x0045a310        0x0 string.o
 .data          0x0045a310        0x0 conio.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a310      0xcf0 00

.bss            0x0045b000     0xd910
                0x0045b000                bss = .
                0x0045b000                _bss = .
                0x0045b000                __bss = .
 *(.bss)
 .bss           0x0045b000        0x0 crt0.o
 .bss           0x0045b000       0xe0 main.o
                0x0045b008                interactive
                0x0045b004                login_shell
                0x0045b000                quiet
                0x0045b00c                ShellFlag
 .bss           0x0045b0e0       0xd0 shellui.o
 .bss           0x0045b1b0       0x30 api.o
 .bss           0x0045b1e0       0x10 stdio.o
 .bss           0x0045b1f0     0x8000 stdlib.o
 .bss           0x004631f0       0x10 string.o
 .bss           0x00463200        0x0 conio.o
                0x00464000                . = ALIGN (0x1000)
 *fill*         0x00463200      0xe00 00
 COMMON         0x00464000      0xd40 crt0.o
                0x00464000                prompt
                0x00464400                stderr
                0x00464410                prompt_pos
                0x00464420                g_using_gui
                0x00464430                stdin
                0x00464440                prompt_max
                0x00464450                prompt_err
                0x00464850                g_columns
                0x00464860                stdout
                0x00464870                Streams
                0x004648f0                g_rows
                0x00464900                prompt_out
                0x00464d00                g_cursor_y
                0x00464d10                prompt_status
                0x00464d20                g_char_attrib
                0x00464d30                g_cursor_x
 COMMON         0x00464d40     0x32e0 main.o
                0x00464d40                ShellMetrics
                0x00464d50                shellStatus
                0x00464d60                CommandHistory
                0x00464d70                EOF_Reached
                0x00464d80                shellWindowWidth
                0x00464d90                ClientAreaInfo
                0x00464da0                g_current_disk_id
                0x00464db0                BufferInfo
                0x00464dc0                shellError
                0x00464dd0                shellWindowHeight
                0x00464de0                lineList
                0x00466de0                root
                0x00466df0                CurrentCommand
                0x00466e00                shell_info
                0x00466e20                shellScreenBufferMaxColumns
                0x00466e30                g_current_workingdirectory_id
                0x00466e40                shell_window_x
                0x00466e50                i2Window
                0x00466e60                rect
                0x00466e70                backgroung_color
                0x00466e80                shell_name
                0x00466e90                shellMaxRows
                0x00466ea0                screenbufferList
                0x00466ec0                foregroung_color
                0x00466ed0                pwd
                0x00466ee0                CurrentWindow
                0x00466ef0                topbar_scrollbarWindow
                0x00466f00                current_semaphore
                0x00466f10                g_current_volume_id
                0x00466f20                ShellHook
                0x00466f30                topbar_checkboxWindow
                0x00466f40                shellScreenBufferMaxRows
                0x00466f50                shellScreenWidth
                0x00466f60                screen_buffer_pos
                0x00466f70                shellScreenHeight
                0x00466f80                editboxWindow
                0x00466f90                username
                0x00466fa0                screen_buffer_x
                0x00466fb0                screen_buffer
                0x00467f60                shell_window_y
                0x00467f70                terminal_rect
                0x00467f80                password
                0x00467f90                CursorInfo
                0x00467fa0                shellMaxColumns
                0x00467fb0                i1Window
                0x00467fc0                screen_buffer_y
                0x00467fd0                topbar_editboxWindow
                0x00467fe0                topbarWindow
                0x00467ff0                ApplicationInfo
                0x00468000                current_workingdiretory_string
 COMMON         0x00468020      0x8f0 stdlib.o
                0x00468020                current_mmblock
                0x00468030                mm_prev_pointer
                0x00468040                heap_end
                0x00468050                g_available_heap
                0x00468060                heap_start
                0x00468070                heapCount
                0x00468080                HEAP_START
                0x00468090                g_heap_pointer
                0x004680a0                heapList
                0x004684a0                HEAP_SIZE
                0x004684b0                last_size
                0x004684c0                last_valid
                0x004684d0                mmblockList
                0x004688d0                libcHeap
                0x004688e0                Heap
                0x004688f0                mmblockCount
                0x00468900                HEAP_END
                0x00468910                end = .
                0x00468910                _end = .
                0x00468910                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD shellui.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
