
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
 .text          0x00451058     0x2ca0 main.o
                0x00452d19                shellPrompt
                0x004535e7                shellSendMessage
                0x00452ed5                shellTestThreads
                0x004536c5                shellTaskList
                0x004513b7                shellProcedure
                0x00452738                shellShell
                0x00453994                shellShowProcessHeapPointer
                0x00452cd8                shellThread
                0x0045287d                shellInit
                0x0045382c                shellShowPPID
                0x004539fc                shellShowKernelHeapPointer
                0x004515cc                shellWaitCmd
                0x00452dd2                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00453958                shellShowDesktopID
                0x00453166                shellInsertCharXY
                0x004531b0                shellInsertCharPos
                0x00453a70                shellShowPCIInfo
                0x004515e4                shellCompare
                0x00452d90                shellClearBuffer
                0x00452fea                shellRefreshScreen
                0x00453c35                feedterminalDialog
                0x00452f65                shellClearScreen
                0x004534ce                shellShowSystemInfo
                0x004531e8                shellInsertNextChar
                0x00453ac8                shell_fntos
                0x00453a44                shellShowMemoryInfo
                0x00452e40                shellTestLoadFile
                0x004532df                move_to
                0x00453214                shellInsertCR
                0x004533ce                shellShowMetrics
                0x004538a4                shellShowGID
                0x0045303a                shellScroll
                0x00453a9c                shellShowKernelInfo
                0x00453638                shellUpdateWorkingDiretoryString
                0x00453252                shellInsertNullTerminator
                0x00453868                shellShowUID
                0x00453233                shellInsertLF
                0x004536b8                shellUpdateCurrentDirectoryID
                0x0045360f                shell_memcpy_bytes
                0x00452cae                shellSetCursor
                0x00453bb7                shell_gramado_core_init_execve
                0x00453304                shellShowInfo
                0x0045353c                shellShowWindowInfo
                0x004537f0                shellShowPID
                0x004538e0                shellShowUserSessionID
                0x0045391c                shellShowWindowStationID
                0x00452d05                shellTree
                0x00452cf1                shellHelp
                0x00453271                shellTestMBR
 .text          0x00453cf8      0x5a0 shellui.o
                0x004540f0                shellTestDisplayBMP
                0x00453e65                shellCreateEditBox
                0x00453cf8                shellTopbarProcedure
                0x00454166                bmpDisplayBMP
                0x00453f13                shellCreateTopBar
 .text          0x00454298     0x1530 api.o
                0x0045504b                APIShowCurrentProcessInfo
                0x0045579b                api_getchar
                0x00454838                system11
                0x004548dd                refresh_buffer
                0x00454f2d                APISetFocus
                0x0045489b                system14
                0x00454bc2                apiInitBackground
                0x00454e01                APICreateWindow
                0x00455578                apiBeginPaint
                0x00454bc7                MessageBox
                0x004550c9                APIreplace_window
                0x004555bf                apiGetSystemMetrics
                0x0045487a                system13
                0x0045542f                apiDown
                0x004554c7                enterCriticalSection
                0x00455704                gramadocore_init_execve
                0x00455405                apiFOpen
                0x004546ee                system1
                0x00454772                system5
                0x0045527d                api_refresh_screen
                0x00455722                apiDialog
                0x00455309                apiGetCursorY
                0x00454b6d                carrega_bitmap_16x16
                0x00455520                exitCriticalSection
                0x00454298                system_call
                0x0045547b                apiUp
                0x004542c0                apiSystem
                0x004556d8                api_get_window_with_text_input
                0x004548bc                system15
                0x00454fdd                APISetActiveWindow
                0x00455361                apiSetClientAreaRect
                0x004550a0                APIredraw_window
                0x004553b3                apiCreateThread
                0x00454b09                SetNextWindowProcedure
                0x004552dd                apiGetCursorX
                0x00454ad9                chama_procedimento
                0x00454bf0                call_kernel
                0x00454ea9                APIRegisterWindow
                0x004551f3                api_strncmp
                0x0045511b                APIminimize_window
                0x0045470f                system2
                0x00454730                system3
                0x00455611                api_get_current_keyboard_responder
                0x0045538a                apiCreateProcess
                0x00454f6f                APIGetFocus
                0x004547b4                system7
                0x00454793                system6
                0x004555b5                apiDefDialog
                0x00454eeb                APICloseWindow
                0x0045554c                initializeCriticalSection
                0x00454817                system10
                0x00454b39                set_cursor
                0x004550f2                APImaximize_window
                0x00455718                execve
                0x00455251                refresh_screen
                0x00454d70                call_gui
                0x004547f6                system9
                0x0045570e                fork
                0x004555e8                api_set_current_keyboard_responder
                0x00455077                APIresize_window
                0x00455582                apiEndPaint
                0x00454b68                put_char
                0x00454a74                print_string
                0x00455335                apiGetClientAreaRect
                0x00454aaa                edit_box
                0x004551c2                kill
                0x00455287                apiReboot
                0x00454b96                apiShutDown
                0x0045563d                api_set_current_mouse_responder
                0x00455199                exit
                0x00455144                APIget_foregroung_window
                0x00454751                system4
                0x004552b3                apiSetCursor
                0x00454859                system12
                0x00454a79                vsync
                0x004547d5                system8
                0x00455692                api_set_window_with_text_input
                0x0045501f                APIGetActiveWindow
                0x00455666                api_get_current_mouse_responder
                0x004551c7                dead_thread_collector
                0x004553dc                apiStartThread
                0x00454f9b                APIKillFocus
                0x00455170                APIset_foregroung_window
                0x0045558c                apiPutChar
 .text          0x004557c8     0x10e0 stdio.o
                0x00456111                putchar
                0x004557c8                stdio_fntos
                0x004560cd                sprintf
                0x0045676e                feof
                0x0045684e                fputc
                0x00456651                fputs
                0x004567ac                ferror
                0x004562fd                input
                0x004559b7                scroll
                0x004562f3                printf_main
                0x004566c6                gets
                0x0045613d                outbyte
                0x00455b61                app_print
                0x0045656c                fflush
                0x004565dc                fprintf
                0x004563f4                stdio_system_call
                0x0045591d                fopen
                0x0045641c                getchar
                0x00456448                stdioInitialize
                0x0045673b                fgetc
                0x004558b7                fclose
                0x004567d4                fseek
                0x004562c0                _outbyte
                0x004560b2                printf
                0x00455af5                app_clear
 .text          0x004568a8      0x960 stdlib.o
                0x00456b63                FreeHeap
                0x004568a8                rtGetHeapStart
                0x00456daa                free
                0x00456d4c                rand
                0x00456cc3                stdlibInitMM
                0x00456b6d                heapInit
                0x004568bc                rtGetHeapPointer
                0x004568c6                rtGetAvailableHeap
                0x00456d23                libcInitRT
                0x004568d0                heapSetLibcHeap
                0x00456d69                malloc
                0x00456b50                AllocateHeapEx
                0x00456977                AllocateHeap
                0x004571a1                stdlib_strncmp
                0x004568b2                rtGetHeapEnd
                0x00456daf                system
 .text          0x00457208      0x4a0 string.o
                0x0045746f                strcspn
                0x004573d2                strcat
                0x00457208                strcmp
                0x00457429                bzero
                0x004575af                strtok_r
                0x00457365                memcpy
                0x0045733c                memoryZeroMemory
                0x00457402                bcopy
                0x004573a2                strcpy
                0x0045750f                strspn
                0x00457684                strtok
                0x004572c1                str_cmp
                0x00457263                strncmp
                0x00457444                strlen
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x004576a8      0x958 00

.rdata          0x00458000     0x2130
 .rdata         0x00458000      0x430 stdlib.o
 .rdata         0x00458430       0x40 stdio.o
 .rdata         0x00458470      0x320 api.o
 .rdata         0x00458790      0x6c0 shellui.o
 .rdata         0x00458e50     0x12e0 main.o

.data           0x0045a130      0xed0
                0x0045a130                data = .
                0x0045a130                _data = .
                0x0045a130                __data = .
 *(.data)
 .data          0x0045a130        0x0 crt0.o
 .data          0x0045a130       0x20 main.o
 .data          0x0045a150       0x20 shellui.o
 .data          0x0045a170        0x0 api.o
 .data          0x0045a170        0x0 stdio.o
 .data          0x0045a170       0x10 stdlib.o
 .data          0x0045a180        0x0 string.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a180      0xe80 00

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
