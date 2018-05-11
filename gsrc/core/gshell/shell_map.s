
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
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x2c30 main.o
                0x00452cac                shellPrompt
                0x0045357a                shellSendMessage
                0x00452e68                shellTestThreads
                0x00453658                shellTaskList
                0x004513b7                shellProcedure
                0x00452713                shellShell
                0x00453927                shellShowProcessHeapPointer
                0x00452c6b                shellThread
                0x00452858                shellInit
                0x004537bf                shellShowPPID
                0x0045398f                shellShowKernelHeapPointer
                0x004515cc                shellWaitCmd
                0x00452d65                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x004538eb                shellShowDesktopID
                0x004530f9                shellInsertCharXY
                0x00453143                shellInsertCharPos
                0x00453a03                shellShowPCIInfo
                0x004515e4                shellCompare
                0x00452d23                shellClearBuffer
                0x00452f7d                shellRefreshScreen
                0x00453bc8                feedterminalDialog
                0x00452ef8                shellClearScreen
                0x00453461                shellShowSystemInfo
                0x0045317b                shellInsertNextChar
                0x00453a5b                shell_fntos
                0x004539d7                shellShowMemoryInfo
                0x00452dd3                shellTestLoadFile
                0x00453272                move_to
                0x004531a7                shellInsertCR
                0x00453361                shellShowMetrics
                0x00453837                shellShowGID
                0x00452fcd                shellScroll
                0x00453a2f                shellShowKernelInfo
                0x004535cb                shellUpdateWorkingDiretoryString
                0x004531e5                shellInsertNullTerminator
                0x004537fb                shellShowUID
                0x004531c6                shellInsertLF
                0x0045364b                shellUpdateCurrentDirectoryID
                0x004535a2                shell_memcpy_bytes
                0x00452c41                shellSetCursor
                0x00453b4a                shell_gramado_core_init_execve
                0x00453297                shellShowInfo
                0x004534cf                shellShowWindowInfo
                0x00453783                shellShowPID
                0x00453873                shellShowUserSessionID
                0x004538af                shellShowWindowStationID
                0x00452c98                shellTree
                0x00452c84                shellHelp
                0x00453204                shellTestMBR
 .text          0x00453c88      0x5a0 shellui.o
                0x00454080                shellTestDisplayBMP
                0x00453df5                shellCreateEditBox
                0x00453c88                shellTopbarProcedure
                0x004540f6                bmpDisplayBMP
                0x00453ea3                shellCreateTopBar
 .text          0x00454228     0x1530 api.o
                0x00454fdb                APIShowCurrentProcessInfo
                0x0045572b                api_getchar
                0x004547c8                system11
                0x0045486d                refresh_buffer
                0x00454ebd                APISetFocus
                0x0045482b                system14
                0x00454b52                apiInitBackground
                0x00454d91                APICreateWindow
                0x00455508                apiBeginPaint
                0x00454b57                MessageBox
                0x00455059                APIreplace_window
                0x0045554f                apiGetSystemMetrics
                0x0045480a                system13
                0x004553bf                apiDown
                0x00455457                enterCriticalSection
                0x00455694                gramadocore_init_execve
                0x00455395                apiFOpen
                0x0045467e                system1
                0x00454702                system5
                0x0045520d                api_refresh_screen
                0x004556b2                apiDialog
                0x00455299                apiGetCursorY
                0x00454afd                carrega_bitmap_16x16
                0x004554b0                exitCriticalSection
                0x00454228                system_call
                0x0045540b                apiUp
                0x00454250                apiSystem
                0x00455668                api_get_window_with_text_input
                0x0045484c                system15
                0x00454f6d                APISetActiveWindow
                0x004552f1                apiSetClientAreaRect
                0x00455030                APIredraw_window
                0x00455343                apiCreateThread
                0x00454a99                SetNextWindowProcedure
                0x0045526d                apiGetCursorX
                0x00454a69                chama_procedimento
                0x00454b80                call_kernel
                0x00454e39                APIRegisterWindow
                0x00455183                api_strncmp
                0x004550ab                APIminimize_window
                0x0045469f                system2
                0x004546c0                system3
                0x004555a1                api_get_current_keyboard_responder
                0x0045531a                apiCreateProcess
                0x00454eff                APIGetFocus
                0x00454744                system7
                0x00454723                system6
                0x00455545                apiDefDialog
                0x00454e7b                APICloseWindow
                0x004554dc                initializeCriticalSection
                0x004547a7                system10
                0x00454ac9                set_cursor
                0x00455082                APImaximize_window
                0x004556a8                execve
                0x004551e1                refresh_screen
                0x00454d00                call_gui
                0x00454786                system9
                0x0045569e                fork
                0x00455578                api_set_current_keyboard_responder
                0x00455007                APIresize_window
                0x00455512                apiEndPaint
                0x00454af8                put_char
                0x00454a04                print_string
                0x004552c5                apiGetClientAreaRect
                0x00454a3a                edit_box
                0x00455152                kill
                0x00455217                apiReboot
                0x00454b26                apiShutDown
                0x004555cd                api_set_current_mouse_responder
                0x00455129                exit
                0x004550d4                APIget_foregroung_window
                0x004546e1                system4
                0x00455243                apiSetCursor
                0x004547e9                system12
                0x00454a09                vsync
                0x00454765                system8
                0x00455622                api_set_window_with_text_input
                0x00454faf                APIGetActiveWindow
                0x004555f6                api_get_current_mouse_responder
                0x00455157                dead_thread_collector
                0x0045536c                apiStartThread
                0x00454f2b                APIKillFocus
                0x00455100                APIset_foregroung_window
                0x0045551c                apiPutChar
 .text          0x00455758     0x10e0 stdio.o
                0x004560a1                putchar
                0x00455758                stdio_fntos
                0x0045605d                sprintf
                0x00456706                feof
                0x004567e6                fputc
                0x004565e1                fputs
                0x00456744                ferror
                0x0045628d                input
                0x00455947                scroll
                0x00456283                printf_main
                0x00456656                gets
                0x004560cd                outbyte
                0x00455af1                app_print
                0x004564fc                fflush
                0x0045656c                fprintf
                0x00456384                stdio_system_call
                0x004558ad                fopen
                0x004563ac                getchar
                0x004563d8                stdioInitialize
                0x004566d3                fgetc
                0x00455847                fclose
                0x0045676c                fseek
                0x00456250                _outbyte
                0x00456042                printf
                0x00455a85                app_clear
 .text          0x00456838      0x960 stdlib.o
                0x00456af3                FreeHeap
                0x00456838                rtGetHeapStart
                0x00456d3a                free
                0x00456cdc                rand
                0x00456c53                stdlibInitMM
                0x00456afd                heapInit
                0x0045684c                rtGetHeapPointer
                0x00456856                rtGetAvailableHeap
                0x00456cb3                libcInitRT
                0x00456860                heapSetLibcHeap
                0x00456cf9                malloc
                0x00456ae0                AllocateHeapEx
                0x00456907                AllocateHeap
                0x00457131                stdlib_strncmp
                0x00456842                rtGetHeapEnd
                0x00456d3f                system
 .text          0x00457198      0x4a0 string.o
                0x004573ff                strcspn
                0x00457362                strcat
                0x00457198                strcmp
                0x004573b9                bzero
                0x0045753f                strtok_r
                0x004572f5                memcpy
                0x004572cc                memoryZeroMemory
                0x00457392                bcopy
                0x00457332                strcpy
                0x0045749f                strspn
                0x00457614                strtok
                0x00457251                str_cmp
                0x004571f3                strncmp
                0x004573d4                strlen
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457638      0x9c8 00

.rdata          0x00458000     0x20f0
 .rdata         0x00458000      0x430 stdlib.o
 .rdata         0x00458430       0x40 stdio.o
 .rdata         0x00458470      0x320 api.o
 .rdata         0x00458790      0x6c0 shellui.o
 .rdata         0x00458e50     0x12a0 main.o

.data           0x0045a0f0      0xf10
                0x0045a0f0                data = .
                0x0045a0f0                _data = .
                0x0045a0f0                __data = .
 *(.data)
 .data          0x0045a0f0        0x0 crt0.o
 .data          0x0045a0f0       0x20 main.o
 .data          0x0045a110       0x20 shellui.o
 .data          0x0045a130        0x0 api.o
 .data          0x0045a130        0x0 stdio.o
 .data          0x0045a130       0x10 stdlib.o
 .data          0x0045a140        0x0 string.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a140      0xec0 00

.bss            0x0045b000     0xd8f0
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
 COMMON         0x00464d40     0x32c0 main.o
                0x00464d40                ShellMetrics
                0x00464d50                shellStatus
                0x00464d60                CommandHistory
                0x00464d70                shellWindowWidth
                0x00464d80                ClientAreaInfo
                0x00464d90                g_current_disk_id
                0x00464da0                BufferInfo
                0x00464db0                shellError
                0x00464dc0                shellWindowHeight
                0x00464dd0                lineList
                0x00466dd0                root
                0x00466de0                CurrentCommand
                0x00466df0                shell_info
                0x00466e10                shellScreenBufferMaxColumns
                0x00466e20                g_current_workingdirectory_id
                0x00466e30                shell_window_x
                0x00466e40                i2Window
                0x00466e50                rect
                0x00466e60                backgroung_color
                0x00466e70                shellMaxRows
                0x00466e80                screenbufferList
                0x00466ea0                foregroung_color
                0x00466eb0                pwd
                0x00466ec0                CurrentWindow
                0x00466ed0                topbar_scrollbarWindow
                0x00466ee0                current_semaphore
                0x00466ef0                g_current_volume_id
                0x00466f00                ShellHook
                0x00466f10                topbar_checkboxWindow
                0x00466f20                shellScreenBufferMaxRows
                0x00466f30                shellScreenWidth
                0x00466f40                screen_buffer_pos
                0x00466f50                shellScreenHeight
                0x00466f60                editboxWindow
                0x00466f70                username
                0x00466f80                screen_buffer_x
                0x00466f90                screen_buffer
                0x00467f40                shell_window_y
                0x00467f50                terminal_rect
                0x00467f60                password
                0x00467f70                CursorInfo
                0x00467f80                shellMaxColumns
                0x00467f90                i1Window
                0x00467fa0                screen_buffer_y
                0x00467fb0                topbar_editboxWindow
                0x00467fc0                topbarWindow
                0x00467fd0                ApplicationInfo
                0x00467fe0                current_workingdiretory_string
 COMMON         0x00468000      0x8f0 stdlib.o
                0x00468000                current_mmblock
                0x00468010                mm_prev_pointer
                0x00468020                heap_end
                0x00468030                g_available_heap
                0x00468040                heap_start
                0x00468050                heapCount
                0x00468060                HEAP_START
                0x00468070                g_heap_pointer
                0x00468080                heapList
                0x00468480                HEAP_SIZE
                0x00468490                last_size
                0x004684a0                last_valid
                0x004684b0                mmblockList
                0x004688b0                libcHeap
                0x004688c0                Heap
                0x004688d0                mmblockCount
                0x004688e0                HEAP_END
                0x004688f0                end = .
                0x004688f0                _end = .
                0x004688f0                __end = .
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
