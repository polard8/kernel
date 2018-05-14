
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
 .text          0x00451064     0x2d80 main.o
                0x00452cb7                shellPrompt
                0x00453585                shellSendMessage
                0x00452e73                shellTestThreads
                0x00453663                shellTaskList
                0x004513c3                shellProcedure
                0x004526d6                shellShell
                0x00453932                shellShowProcessHeapPointer
                0x00452c76                shellThread
                0x00453cff                concat
                0x0045281b                shellInit
                0x004537ca                shellShowPPID
                0x0045399a                shellShowKernelHeapPointer
                0x004515d8                shellWaitCmd
                0x00452d70                shellShowScreenBuffer
                0x00451064                GramadoMain
                0x004538f6                shellShowDesktopID
                0x00453104                shellInsertCharXY
                0x0045314e                shellInsertCharPos
                0x00453c93                die
                0x00453a0e                shellShowPCIInfo
                0x004515f0                shellCompare
                0x00452d2e                shellClearBuffer
                0x00452f88                shellRefreshScreen
                0x00453bd7                feedterminalDialog
                0x00452f03                shellClearScreen
                0x0045346c                shellShowSystemInfo
                0x00453186                shellInsertNextChar
                0x00453a66                shell_fntos
                0x004539e2                shellShowMemoryInfo
                0x00452dde                shellTestLoadFile
                0x0045327d                move_to
                0x004531b2                shellInsertCR
                0x0045336c                shellShowMetrics
                0x00453842                shellShowGID
                0x00452fd8                shellScroll
                0x00453a3a                shellShowKernelInfo
                0x004535d6                shellUpdateWorkingDiretoryString
                0x004531f0                shellInsertNullTerminator
                0x00453806                shellShowUID
                0x004531d1                shellInsertLF
                0x00453656                shellUpdateCurrentDirectoryID
                0x004535ad                shell_memcpy_bytes
                0x00452c4c                shellSetCursor
                0x00453b55                shell_gramado_core_init_execve
                0x004532a2                shellShowInfo
                0x004534da                shellShowWindowInfo
                0x0045378e                shellShowPID
                0x00453d97                error
                0x0045387e                shellShowUserSessionID
                0x004538ba                shellShowWindowStationID
                0x00453cd4                xmalloc
                0x00452ca3                shellTree
                0x00452c8f                shellHelp
                0x0045320f                shellTestMBR
 .text          0x00453de4      0x5a0 shellui.o
                0x004541dc                shellTestDisplayBMP
                0x00453f51                shellCreateEditBox
                0x00453de4                shellTopbarProcedure
                0x00454252                bmpDisplayBMP
                0x00453fff                shellCreateTopBar
 .text          0x00454384     0x1530 api.o
                0x00455137                APIShowCurrentProcessInfo
                0x00455887                api_getchar
                0x00454924                system11
                0x004549c9                refresh_buffer
                0x00455019                APISetFocus
                0x00454987                system14
                0x00454cae                apiInitBackground
                0x00454eed                APICreateWindow
                0x00455664                apiBeginPaint
                0x00454cb3                MessageBox
                0x004551b5                APIreplace_window
                0x004556ab                apiGetSystemMetrics
                0x00454966                system13
                0x0045551b                apiDown
                0x004555b3                enterCriticalSection
                0x004557f0                gramadocore_init_execve
                0x004554f1                apiFOpen
                0x004547da                system1
                0x0045485e                system5
                0x00455369                api_refresh_screen
                0x0045580e                apiDialog
                0x004553f5                apiGetCursorY
                0x00454c59                carrega_bitmap_16x16
                0x0045560c                exitCriticalSection
                0x00454384                system_call
                0x00455567                apiUp
                0x004543ac                apiSystem
                0x004557c4                api_get_window_with_text_input
                0x004549a8                system15
                0x004550c9                APISetActiveWindow
                0x0045544d                apiSetClientAreaRect
                0x0045518c                APIredraw_window
                0x0045549f                apiCreateThread
                0x00454bf5                SetNextWindowProcedure
                0x004553c9                apiGetCursorX
                0x00454bc5                chama_procedimento
                0x00454cdc                call_kernel
                0x00454f95                APIRegisterWindow
                0x004552df                api_strncmp
                0x00455207                APIminimize_window
                0x004547fb                system2
                0x0045481c                system3
                0x004556fd                api_get_current_keyboard_responder
                0x00455476                apiCreateProcess
                0x0045505b                APIGetFocus
                0x004548a0                system7
                0x0045487f                system6
                0x004556a1                apiDefDialog
                0x00454fd7                APICloseWindow
                0x00455638                initializeCriticalSection
                0x00454903                system10
                0x00454c25                set_cursor
                0x004551de                APImaximize_window
                0x00455804                execve
                0x0045533d                refresh_screen
                0x00454e5c                call_gui
                0x004548e2                system9
                0x004557fa                fork
                0x004556d4                api_set_current_keyboard_responder
                0x00455163                APIresize_window
                0x0045566e                apiEndPaint
                0x00454c54                put_char
                0x00454b60                print_string
                0x00455421                apiGetClientAreaRect
                0x00454b96                edit_box
                0x004552ae                kill
                0x00455373                apiReboot
                0x00454c82                apiShutDown
                0x00455729                api_set_current_mouse_responder
                0x00455285                exit
                0x00455230                APIget_foregroung_window
                0x0045483d                system4
                0x0045539f                apiSetCursor
                0x00454945                system12
                0x00454b65                vsync
                0x004548c1                system8
                0x0045577e                api_set_window_with_text_input
                0x0045510b                APIGetActiveWindow
                0x00455752                api_get_current_mouse_responder
                0x004552b3                dead_thread_collector
                0x004554c8                apiStartThread
                0x00455087                APIKillFocus
                0x0045525c                APIset_foregroung_window
                0x00455678                apiPutChar
 .text          0x004558b4     0x1110 stdio.o
                0x004561fb                putchar
                0x004558b4                stdio_fntos
                0x004561b7                sprintf
                0x0045688e                feof
                0x0045696e                fputc
                0x00456741                fputs
                0x004568cc                ferror
                0x004563e7                input
                0x00455aa1                scroll
                0x004563dd                printf_main
                0x004567b6                gets
                0x00456227                outbyte
                0x00455c4b                app_print
                0x0045665c                fflush
                0x004566cc                fprintf
                0x004564de                stdio_system_call
                0x00455a09                fopen
                0x00456506                getchar
                0x00456538                stdioInitialize
                0x0045682b                fgetc
                0x004559a3                fclose
                0x004568f4                fseek
                0x004563aa                _outbyte
                0x0045619c                printf
                0x00455bdf                app_clear
 .text          0x004569c4      0x960 stdlib.o
                0x00456c7f                FreeHeap
                0x004569c4                rtGetHeapStart
                0x00456ec6                free
                0x00456e68                rand
                0x00456ddf                stdlibInitMM
                0x00456c89                heapInit
                0x004569d8                rtGetHeapPointer
                0x004569e2                rtGetAvailableHeap
                0x00456e3f                libcInitRT
                0x004569ec                heapSetLibcHeap
                0x00456e85                malloc
                0x00456c6c                AllocateHeapEx
                0x00456a93                AllocateHeap
                0x004572bd                stdlib_strncmp
                0x004569ce                rtGetHeapEnd
                0x00456ecb                system
 .text          0x00457324      0x4a0 string.o
                0x0045758b                strcspn
                0x004574ee                strcat
                0x00457324                strcmp
                0x00457545                bzero
                0x004576cb                strtok_r
                0x00457481                memcpy
                0x00457458                memoryZeroMemory
                0x0045751e                bcopy
                0x004574be                strcpy
                0x0045762b                strspn
                0x004577a0                strtok
                0x004573dd                str_cmp
                0x0045737f                strncmp
                0x00457560                strlen
 .text          0x004577c4       0x90 conio.o
                0x00457832                getche
                0x004577c4                putch
                0x004577e7                cputs
                0x0045781b                getch
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457854      0x7ac 00

.rdata          0x00458000     0x2160
 .rdata         0x00458000       0x10 conio.o
 .rdata         0x00458010      0x430 stdlib.o
 .rdata         0x00458440       0x40 stdio.o
 .rdata         0x00458480      0x320 api.o
 .rdata         0x004587a0      0x6c0 shellui.o
 .rdata         0x00458e60     0x1300 main.o

.data           0x0045a160      0xea0
                0x0045a160                data = .
                0x0045a160                _data = .
                0x0045a160                __data = .
 *(.data)
 .data          0x0045a160        0x0 crt0.o
 .data          0x0045a160       0x20 main.o
 .data          0x0045a180       0x20 shellui.o
 .data          0x0045a1a0        0x0 api.o
 .data          0x0045a1a0        0x0 stdio.o
 .data          0x0045a1a0       0x10 stdlib.o
 .data          0x0045a1b0        0x0 string.o
 .data          0x0045a1b0        0x0 conio.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a1b0      0xe50 00

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
LOAD conio.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
