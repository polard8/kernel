
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
 .head_x86      0x00451000       0x24 head.o
                0x00451000                shell_entry_point
                0x00451018                VECTOR
 *(.text)
 .text          0x00451024       0x40 crt0.o
                0x00451024                crt0
 .text          0x00451064     0x2c00 main.o
                0x00452c67                shellPrompt
                0x00453535                shellSendMessage
                0x00452e23                shellTestThreads
                0x00453613                shellTaskList
                0x004513c3                shellProcedure
                0x00452686                shellShell
                0x004538e2                shellShowProcessHeapPointer
                0x00452c26                shellThread
                0x004527cb                shellInit
                0x0045377a                shellShowPPID
                0x0045394a                shellShowKernelHeapPointer
                0x004515d8                shellWaitCmd
                0x00452d20                shellShowScreenBuffer
                0x00451064                GramadoMain
                0x004538a6                shellShowDesktopID
                0x004530b4                shellInsertCharXY
                0x004530fe                shellInsertCharPos
                0x00453c43                die
                0x004539be                shellShowPCIInfo
                0x004515f0                shellCompare
                0x00452cde                shellClearBuffer
                0x00452f38                shellRefreshScreen
                0x00453b87                feedterminalDialog
                0x00452eb3                shellClearScreen
                0x0045341c                shellShowSystemInfo
                0x00453136                shellInsertNextChar
                0x00453a16                shell_fntos
                0x00453992                shellShowMemoryInfo
                0x00452d8e                shellTestLoadFile
                0x0045322d                move_to
                0x00453162                shellInsertCR
                0x0045331c                shellShowMetrics
                0x004537f2                shellShowGID
                0x00452f88                shellScroll
                0x004539ea                shellShowKernelInfo
                0x00453586                shellUpdateWorkingDiretoryString
                0x004531a0                shellInsertNullTerminator
                0x004537b6                shellShowUID
                0x00453181                shellInsertLF
                0x00453606                shellUpdateCurrentDirectoryID
                0x0045355d                shell_memcpy_bytes
                0x00452bfc                shellSetCursor
                0x00453b05                shell_gramado_core_init_execve
                0x00453252                shellShowInfo
                0x0045348a                shellShowWindowInfo
                0x0045373e                shellShowPID
                0x0045382e                shellShowUserSessionID
                0x0045386a                shellShowWindowStationID
                0x00452c53                shellTree
                0x00452c3f                shellHelp
                0x004531bf                shellTestMBR
 .text          0x00453c64      0x5a0 shellui.o
                0x0045405c                shellTestDisplayBMP
                0x00453dd1                shellCreateEditBox
                0x00453c64                shellTopbarProcedure
                0x004540d2                bmpDisplayBMP
                0x00453e7f                shellCreateTopBar
 .text          0x00454204     0x1530 api.o
                0x00454fb7                APIShowCurrentProcessInfo
                0x00455707                api_getchar
                0x004547a4                system11
                0x00454849                refresh_buffer
                0x00454e99                APISetFocus
                0x00454807                system14
                0x00454b2e                apiInitBackground
                0x00454d6d                APICreateWindow
                0x004554e4                apiBeginPaint
                0x00454b33                MessageBox
                0x00455035                APIreplace_window
                0x0045552b                apiGetSystemMetrics
                0x004547e6                system13
                0x0045539b                apiDown
                0x00455433                enterCriticalSection
                0x00455670                gramadocore_init_execve
                0x00455371                apiFOpen
                0x0045465a                system1
                0x004546de                system5
                0x004551e9                api_refresh_screen
                0x0045568e                apiDialog
                0x00455275                apiGetCursorY
                0x00454ad9                carrega_bitmap_16x16
                0x0045548c                exitCriticalSection
                0x00454204                system_call
                0x004553e7                apiUp
                0x0045422c                apiSystem
                0x00455644                api_get_window_with_text_input
                0x00454828                system15
                0x00454f49                APISetActiveWindow
                0x004552cd                apiSetClientAreaRect
                0x0045500c                APIredraw_window
                0x0045531f                apiCreateThread
                0x00454a75                SetNextWindowProcedure
                0x00455249                apiGetCursorX
                0x00454a45                chama_procedimento
                0x00454b5c                call_kernel
                0x00454e15                APIRegisterWindow
                0x0045515f                api_strncmp
                0x00455087                APIminimize_window
                0x0045467b                system2
                0x0045469c                system3
                0x0045557d                api_get_current_keyboard_responder
                0x004552f6                apiCreateProcess
                0x00454edb                APIGetFocus
                0x00454720                system7
                0x004546ff                system6
                0x00455521                apiDefDialog
                0x00454e57                APICloseWindow
                0x004554b8                initializeCriticalSection
                0x00454783                system10
                0x00454aa5                set_cursor
                0x0045505e                APImaximize_window
                0x00455684                execve
                0x004551bd                refresh_screen
                0x00454cdc                call_gui
                0x00454762                system9
                0x0045567a                fork
                0x00455554                api_set_current_keyboard_responder
                0x00454fe3                APIresize_window
                0x004554ee                apiEndPaint
                0x00454ad4                put_char
                0x004549e0                print_string
                0x004552a1                apiGetClientAreaRect
                0x00454a16                edit_box
                0x0045512e                kill
                0x004551f3                apiReboot
                0x00454b02                apiShutDown
                0x004555a9                api_set_current_mouse_responder
                0x00455105                exit
                0x004550b0                APIget_foregroung_window
                0x004546bd                system4
                0x0045521f                apiSetCursor
                0x004547c5                system12
                0x004549e5                vsync
                0x00454741                system8
                0x004555fe                api_set_window_with_text_input
                0x00454f8b                APIGetActiveWindow
                0x004555d2                api_get_current_mouse_responder
                0x00455133                dead_thread_collector
                0x00455348                apiStartThread
                0x00454f07                APIKillFocus
                0x004550dc                APIset_foregroung_window
                0x004554f8                apiPutChar
 .text          0x00455734     0x10e0 stdio.o
                0x0045607d                putchar
                0x00455734                stdio_fntos
                0x00456039                sprintf
                0x004566da                feof
                0x004567ba                fputc
                0x004565bd                fputs
                0x00456718                ferror
                0x00456269                input
                0x00455923                scroll
                0x0045625f                printf_main
                0x00456632                gets
                0x004560a9                outbyte
                0x00455acd                app_print
                0x004564d8                fflush
                0x00456548                fprintf
                0x00456360                stdio_system_call
                0x00455889                fopen
                0x00456388                getchar
                0x004563b4                stdioInitialize
                0x004566a7                fgetc
                0x00455823                fclose
                0x00456740                fseek
                0x0045622c                _outbyte
                0x0045601e                printf
                0x00455a61                app_clear
 .text          0x00456814      0x960 stdlib.o
                0x00456acf                FreeHeap
                0x00456814                rtGetHeapStart
                0x00456d16                free
                0x00456cb8                rand
                0x00456c2f                stdlibInitMM
                0x00456ad9                heapInit
                0x00456828                rtGetHeapPointer
                0x00456832                rtGetAvailableHeap
                0x00456c8f                libcInitRT
                0x0045683c                heapSetLibcHeap
                0x00456cd5                malloc
                0x00456abc                AllocateHeapEx
                0x004568e3                AllocateHeap
                0x0045710d                stdlib_strncmp
                0x0045681e                rtGetHeapEnd
                0x00456d1b                system
 .text          0x00457174      0x4a0 string.o
                0x004573db                strcspn
                0x0045733e                strcat
                0x00457174                strcmp
                0x00457395                bzero
                0x0045751b                strtok_r
                0x004572d1                memcpy
                0x004572a8                memoryZeroMemory
                0x0045736e                bcopy
                0x0045730e                strcpy
                0x0045747b                strspn
                0x004575f0                strtok
                0x0045722d                str_cmp
                0x004571cf                strncmp
                0x004573b0                strlen
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457614      0x9ec 00

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
