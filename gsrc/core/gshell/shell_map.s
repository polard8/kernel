
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
 .text          0x004510a4     0x2e20 main.o
                0x00452d35                shellPrompt
                0x00453603                shellSendMessage
                0x00452ef1                shellTestThreads
                0x004536e1                shellTaskList
                0x004513bf                shellProcedure
                0x00452742                shellShell
                0x004539b0                shellShowProcessHeapPointer
                0x00452cf4                shellThread
                0x00453d71                concat
                0x00452887                shellInit
                0x00453848                shellShowPPID
                0x00453a18                shellShowKernelHeapPointer
                0x004515d4                shellWaitCmd
                0x00452dee                shellShowScreenBuffer
                0x004510a4                GramadoMain
                0x00453974                shellShowDesktopID
                0x00453182                shellInsertCharXY
                0x004531cc                shellInsertCharPos
                0x00453d05                die
                0x00453a8c                shellShowPCIInfo
                0x004515ec                shellCompare
                0x00452dac                shellClearBuffer
                0x00453006                shellRefreshScreen
                0x00453c49                feedterminalDialog
                0x00453e50                shellExecuteThisScript
                0x00452f81                shellClearScreen
                0x004534ea                shellShowSystemInfo
                0x00453204                shellInsertNextChar
                0x00453ae4                shell_fntos
                0x00453a60                shellShowMemoryInfo
                0x00452e5c                shellTestLoadFile
                0x004532fb                move_to
                0x00453230                shellInsertCR
                0x004533ea                shellShowMetrics
                0x004538c0                shellShowGID
                0x00453056                shellScroll
                0x00453ab8                shellShowKernelInfo
                0x00453654                shellUpdateWorkingDiretoryString
                0x0045326e                shellInsertNullTerminator
                0x00453884                shellShowUID
                0x0045324f                shellInsertLF
                0x004536d4                shellUpdateCurrentDirectoryID
                0x0045362b                shell_memcpy_bytes
                0x00452cca                shellSetCursor
                0x00453bd3                shell_gramado_core_init_execve
                0x00453320                shellShowInfo
                0x00453558                shellShowWindowInfo
                0x0045380c                shellShowPID
                0x00453e09                error
                0x004538fc                shellShowUserSessionID
                0x00453938                shellShowWindowStationID
                0x00453d46                xmalloc
                0x00452d21                shellTree
                0x00452d0d                shellHelp
                0x0045328d                shellTestMBR
 .text          0x00453ec4      0x5a0 shellui.o
                0x004542bc                shellTestDisplayBMP
                0x00454031                shellCreateEditBox
                0x00453ec4                shellTopbarProcedure
                0x00454332                bmpDisplayBMP
                0x004540df                shellCreateTopBar
 .text          0x00454464     0x1530 api.o
                0x00455217                APIShowCurrentProcessInfo
                0x00455967                api_getchar
                0x00454a04                system11
                0x00454aa9                refresh_buffer
                0x004550f9                APISetFocus
                0x00454a67                system14
                0x00454d8e                apiInitBackground
                0x00454fcd                APICreateWindow
                0x00455744                apiBeginPaint
                0x00454d93                MessageBox
                0x00455295                APIreplace_window
                0x0045578b                apiGetSystemMetrics
                0x00454a46                system13
                0x004555fb                apiDown
                0x00455693                enterCriticalSection
                0x004558d0                gramadocore_init_execve
                0x004555d1                apiFOpen
                0x004548ba                system1
                0x0045493e                system5
                0x00455449                api_refresh_screen
                0x004558ee                apiDialog
                0x004554d5                apiGetCursorY
                0x00454d39                carrega_bitmap_16x16
                0x004556ec                exitCriticalSection
                0x00454464                system_call
                0x00455647                apiUp
                0x0045448c                apiSystem
                0x004558a4                api_get_window_with_text_input
                0x00454a88                system15
                0x004551a9                APISetActiveWindow
                0x0045552d                apiSetClientAreaRect
                0x0045526c                APIredraw_window
                0x0045557f                apiCreateThread
                0x00454cd5                SetNextWindowProcedure
                0x004554a9                apiGetCursorX
                0x00454ca5                chama_procedimento
                0x00454dbc                call_kernel
                0x00455075                APIRegisterWindow
                0x004553bf                api_strncmp
                0x004552e7                APIminimize_window
                0x004548db                system2
                0x004548fc                system3
                0x004557dd                api_get_current_keyboard_responder
                0x00455556                apiCreateProcess
                0x0045513b                APIGetFocus
                0x00454980                system7
                0x0045495f                system6
                0x00455781                apiDefDialog
                0x004550b7                APICloseWindow
                0x00455718                initializeCriticalSection
                0x004549e3                system10
                0x00454d05                set_cursor
                0x004552be                APImaximize_window
                0x004558e4                execve
                0x0045541d                refresh_screen
                0x00454f3c                call_gui
                0x004549c2                system9
                0x004558da                fork
                0x004557b4                api_set_current_keyboard_responder
                0x00455243                APIresize_window
                0x0045574e                apiEndPaint
                0x00454d34                put_char
                0x00454c40                print_string
                0x00455501                apiGetClientAreaRect
                0x00454c76                edit_box
                0x0045538e                kill
                0x00455453                apiReboot
                0x00454d62                apiShutDown
                0x00455809                api_set_current_mouse_responder
                0x00455365                exit
                0x00455310                APIget_foregroung_window
                0x0045491d                system4
                0x0045547f                apiSetCursor
                0x00454a25                system12
                0x00454c45                vsync
                0x004549a1                system8
                0x0045585e                api_set_window_with_text_input
                0x004551eb                APIGetActiveWindow
                0x00455832                api_get_current_mouse_responder
                0x00455393                dead_thread_collector
                0x004555a8                apiStartThread
                0x00455167                APIKillFocus
                0x0045533c                APIset_foregroung_window
                0x00455758                apiPutChar
 .text          0x00455994     0x1110 stdio.o
                0x004562db                putchar
                0x00455994                stdio_fntos
                0x00456297                sprintf
                0x0045696c                feof
                0x00456a4a                fputc
                0x00456821                fputs
                0x004569aa                ferror
                0x004564c7                input
                0x00455b81                scroll
                0x004564bd                printf_main
                0x00456896                gets
                0x00456307                outbyte
                0x00455d2b                app_print
                0x0045673c                fflush
                0x004567ac                fprintf
                0x004565be                stdio_system_call
                0x00455ae9                fopen
                0x004565e6                getchar
                0x00456618                stdioInitialize
                0x0045690b                fgetc
                0x00455a83                fclose
                0x004569d0                fseek
                0x0045648a                _outbyte
                0x0045627c                printf
                0x00455cbf                app_clear
 .text          0x00456aa4      0x960 stdlib.o
                0x00456d5f                FreeHeap
                0x00456aa4                rtGetHeapStart
                0x00456fa6                free
                0x00456f48                rand
                0x00456ebf                stdlibInitMM
                0x00456d69                heapInit
                0x00456ab8                rtGetHeapPointer
                0x00456ac2                rtGetAvailableHeap
                0x00456f1f                libcInitRT
                0x00456acc                heapSetLibcHeap
                0x00456f65                malloc
                0x00456d4c                AllocateHeapEx
                0x00456b73                AllocateHeap
                0x0045739d                stdlib_strncmp
                0x00456aae                rtGetHeapEnd
                0x00456fab                system
 .text          0x00457404      0x4a0 string.o
                0x0045766b                strcspn
                0x004575ce                strcat
                0x00457404                strcmp
                0x00457625                bzero
                0x004577ab                strtok_r
                0x00457561                memcpy
                0x00457538                memoryZeroMemory
                0x004575fe                bcopy
                0x0045759e                strcpy
                0x0045770b                strspn
                0x00457880                strtok
                0x004574bd                str_cmp
                0x0045745f                strncmp
                0x00457640                strlen
 .text          0x004578a4       0x90 conio.o
                0x00457912                getche
                0x004578a4                putch
                0x004578c7                cputs
                0x004578fb                getch
 .text          0x00457934      0x1a0 builtins.o
                0x00457a99                pwd_builtins
                0x00457a33                getuid_builtins
                0x00457a45                getgid_builtins
                0x004579bc                echo_builtins
                0x00457978                dir_builtins
                0x004579ef                exit_builtins
                0x00457a0f                getpid_builtins
                0x00457969                copy_builtins
                0x00457a21                getppid_builtins
                0x004579db                exec_builtins
                0x00457948                cls_builtins
                0x0045796e                date_builtins
                0x00457973                del_builtins
                0x00457934                cd_buitins
                0x00457a57                help_builtins
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457ad4      0x52c 00

.rdata          0x00458000     0x26b0
 .rdata         0x00458000      0x480 builtins.o
 .rdata         0x00458480       0x10 conio.o
 .rdata         0x00458490      0x430 stdlib.o
 .rdata         0x004588c0       0x40 stdio.o
 .rdata         0x00458900      0x320 api.o
 .rdata         0x00458c20      0x6c0 shellui.o
 .rdata         0x004592e0     0x1320 main.o
 .rdata         0x0045a600       0xb0 crt0.o

.data           0x0045a6b0      0x950
                0x0045a6b0                data = .
                0x0045a6b0                _data = .
                0x0045a6b0                __data = .
 *(.data)
 .data          0x0045a6b0       0x30 crt0.o
 .data          0x0045a6e0       0x20 main.o
                0x0045a6f8                shell_config_file
 .data          0x0045a700       0x20 shellui.o
 .data          0x0045a720        0x0 api.o
 .data          0x0045a720        0x0 stdio.o
 .data          0x0045a720       0x10 stdlib.o
 .data          0x0045a730        0x0 string.o
 .data          0x0045a730        0x0 conio.o
 .data          0x0045a730       0x20 builtins.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a750      0x8b0 00

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
 .bss           0x00463200       0xd0 builtins.o
                0x00464000                . = ALIGN (0x1000)
 *fill*         0x004632d0      0xd30 00
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
LOAD builtins.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
