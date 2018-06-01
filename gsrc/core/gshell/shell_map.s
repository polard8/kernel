
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
dummycompiler       0x10              main.o
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

.text           0x00451000     0x8000
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
 .text          0x004510a4     0x3180 main.o
                0x00452fdf                shellPrompt
                0x004538eb                shellSendMessage
                0x00453172                shellTestThreads
                0x004539c9                shellTaskList
                0x004513c4                shellProcedure
                0x004529dc                shellShell
                0x00453c98                shellShowProcessHeapPointer
                0x00452f9e                shellThread
                0x004540a5                concat
                0x00452ae1                shellInit
                0x00453b30                shellShowPPID
                0x00453d00                shellShowKernelHeapPointer
                0x004515d9                shellWaitCmd
                0x00453098                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00453c5c                shellShowDesktopID
                0x004533ea                shellInsertCharXY
                0x00453434                shellInsertCharPos
                0x00454039                die
                0x00453dcc                shellShowPCIInfo
                0x004515f1                shellCompare
                0x00453056                shellClearBuffer
                0x0045323c                shellRefreshScreen
                0x00453f7d                feedterminalDialog
                0x00454184                shellExecuteThisScript
                0x00453202                shellClearScreen
                0x004537c6                shellShowSystemInfo
                0x0045346c                shellInsertNextChar
                0x00453e24                shell_fntos
                0x00453da0                shellShowMemoryInfo
                0x004530f7                shellTestLoadFile
                0x004535e3                move_to
                0x004534b5                shellInsertCR
                0x004536d2                shellShowMetrics
                0x00453ba8                shellShowGID
                0x004532be                shellScroll
                0x00453df8                shellShowKernelInfo
                0x0045393c                shellUpdateWorkingDiretoryString
                0x00453535                shellInsertNullTerminator
                0x00453b6c                shellShowUID
                0x004534f5                shellInsertLF
                0x004539bc                shellUpdateCurrentDirectoryID
                0x00453913                shell_memcpy_bytes
                0x00452f74                shellSetCursor
                0x00453f13                shell_gramado_core_init_execve
                0x00453608                shellShowInfo
                0x00453d74                shellShowVolumeInfo
                0x00453834                shellShowWindowInfo
                0x004510a4                quit
                0x00453af4                shellShowPID
                0x0045413d                error
                0x00453be4                shellShowUserSessionID
                0x00453c20                shellShowWindowStationID
                0x0045407a                xmalloc
                0x00453d48                shellShowDiskInfo
                0x00452fcb                shellTree
                0x00452fb7                shellHelp
                0x00453575                shellTestMBR
 .text          0x00454224      0x7b0 shellui.o
                0x00454820                shellTestDisplayBMP
                0x00454480                shellCreateEditBox
                0x004547ab                shellDisplayBMP
                0x00454313                shellTopbarProcedure
                0x00454896                bmpDisplayBMP
                0x0045452e                shellCreateTopBar
                0x00454224                shellui_fntos
 .text          0x004549d4     0x1960 api.o
                0x00455789                APIShowCurrentProcessInfo
                0x00455f2b                api_getchar
                0x00454f76                system11
                0x0045501b                refresh_buffer
                0x0045566b                APISetFocus
                0x00454fd9                system14
                0x00455300                apiInitBackground
                0x0045553f                APICreateWindow
                0x00455d08                apiBeginPaint
                0x00455305                MessageBox
                0x00455807                APIreplace_window
                0x00455d4f                apiGetSystemMetrics
                0x00454fb8                system13
                0x00455bbf                apiDown
                0x004558d7                apiExit
                0x00455c57                enterCriticalSection
                0x00455e94                gramadocore_init_execve
                0x00455b45                apiFOpen
                0x00454e2c                system1
                0x00454eb0                system5
                0x004559bd                api_refresh_screen
                0x00455eb2                apiDialog
                0x00455a49                apiGetCursorY
                0x004552ab                carrega_bitmap_16x16
                0x00455cb0                exitCriticalSection
                0x004549d4                system_call
                0x00455c0b                apiUp
                0x004549fc                apiSystem
                0x00455e68                api_get_window_with_text_input
                0x00454ffa                system15
                0x0045571b                APISetActiveWindow
                0x00455aa1                apiSetClientAreaRect
                0x004557de                APIredraw_window
                0x00455af3                apiCreateThread
                0x00455247                SetNextWindowProcedure
                0x00455a1d                apiGetCursorX
                0x00455217                chama_procedimento
                0x0045532e                call_kernel
                0x004555e7                APIRegisterWindow
                0x00455933                api_strncmp
                0x00455859                APIminimize_window
                0x00454e4d                system2
                0x00454e6e                system3
                0x00455da1                api_get_current_keyboard_responder
                0x00455aca                apiCreateProcess
                0x004556ad                APIGetFocus
                0x00454ef2                system7
                0x00454ed1                system6
                0x00455d45                apiDefDialog
                0x00455629                APICloseWindow
                0x00455cdc                initializeCriticalSection
                0x00454f55                system10
                0x00455277                set_cursor
                0x00455830                APImaximize_window
                0x00455ea8                execve
                0x00455991                refresh_screen
                0x00455f57                apiDisplayBMP
                0x004554ae                call_gui
                0x00454f34                system9
                0x00455e9e                fork
                0x00455d78                api_set_current_keyboard_responder
                0x004557b5                APIresize_window
                0x00455d12                apiEndPaint
                0x004552a6                put_char
                0x004551b2                print_string
                0x00455a75                apiGetClientAreaRect
                0x004551e8                edit_box
                0x00455902                kill
                0x004559c7                apiReboot
                0x004552d4                apiShutDown
                0x00455dcd                api_set_current_mouse_responder
                0x00455882                APIget_foregroung_window
                0x00454e8f                system4
                0x00455b7f                apiSaveFile
                0x004559f3                apiSetCursor
                0x00454f97                system12
                0x004551b7                vsync
                0x00454f13                system8
                0x00455e22                api_set_window_with_text_input
                0x0045575d                APIGetActiveWindow
                0x00455df6                api_get_current_mouse_responder
                0x00455907                dead_thread_collector
                0x00455b1c                apiStartThread
                0x004556d9                APIKillFocus
                0x004558ae                APIset_foregroung_window
                0x00455d1c                apiPutChar
 .text          0x00456334     0x1110 stdio.o
                0x00456c7b                putchar
                0x00456334                stdio_fntos
                0x00456c37                sprintf
                0x0045730c                feof
                0x004573ea                fputc
                0x004571c1                fputs
                0x0045734a                ferror
                0x00456e67                input
                0x00456521                scroll
                0x00456e5d                printf_main
                0x00457236                gets
                0x00456ca7                outbyte
                0x004566cb                app_print
                0x004570dc                fflush
                0x0045714c                fprintf
                0x00456f5e                stdio_system_call
                0x00456489                fopen
                0x00456f86                getchar
                0x00456fb8                stdioInitialize
                0x004572ab                fgetc
                0x00456423                fclose
                0x00457370                fseek
                0x00456e2a                _outbyte
                0x00456c1c                printf
                0x0045665f                app_clear
 .text          0x00457444      0x9b0 stdlib.o
                0x00457727                FreeHeap
                0x0045746c                rtGetHeapStart
                0x0045796e                free
                0x00457444                stdlib_system_call
                0x00457910                rand
                0x00457887                stdlibInitMM
                0x00457731                heapInit
                0x00457480                rtGetHeapPointer
                0x0045748a                rtGetAvailableHeap
                0x004578e7                libcInitRT
                0x00457494                heapSetLibcHeap
                0x0045792d                malloc
                0x00457714                AllocateHeapEx
                0x0045753b                AllocateHeap
                0x00457d65                stdlib_strncmp
                0x00457dc3                exit
                0x00457476                rtGetHeapEnd
                0x00457973                system
 .text          0x00457df4      0x4a0 string.o
                0x0045805b                strcspn
                0x00457fbe                strcat
                0x00457df4                strcmp
                0x00458015                bzero
                0x0045819b                strtok_r
                0x00457f51                memcpy
                0x00457f28                memoryZeroMemory
                0x00457fee                bcopy
                0x00457f8e                strcpy
                0x004580fb                strspn
                0x00458270                strtok
                0x00457ead                str_cmp
                0x00457e4f                strncmp
                0x00458030                strlen
 .text          0x00458294       0x90 conio.o
                0x00458302                getche
                0x00458294                putch
                0x004582b7                cputs
                0x004582eb                getch
 .text          0x00458324      0x1a0 builtins.o
                0x00458489                pwd_builtins
                0x00458423                getuid_builtins
                0x00458435                getgid_builtins
                0x004583ac                echo_builtins
                0x00458368                dir_builtins
                0x004583df                exit_builtins
                0x004583ff                getpid_builtins
                0x00458359                copy_builtins
                0x00458411                getppid_builtins
                0x004583cb                exec_builtins
                0x00458338                cls_builtins
                0x0045835e                date_builtins
                0x00458363                del_builtins
                0x00458324                cd_buitins
                0x00458447                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x004584c4      0xb3c 00

.rdata          0x00459000     0x26d0
 .rdata         0x00459000      0x480 builtins.o
 .rdata         0x00459480       0x10 conio.o
 .rdata         0x00459490      0x430 stdlib.o
 .rdata         0x004598c0       0x40 stdio.o
 .rdata         0x00459900      0x320 api.o
 .rdata         0x00459c20      0x6c0 shellui.o
 .rdata         0x0045a2e0     0x1340 main.o
 .rdata         0x0045b620       0xb0 crt0.o

.data           0x0045b6d0     0x1930
                0x0045b6d0                data = .
                0x0045b6d0                _data = .
                0x0045b6d0                __data = .
 *(.data)
 .data          0x0045b6d0       0x30 crt0.o
 .data          0x0045b700      0x480 main.o
                0x0045bb60                running
                0x0045bb64                shell_config_file
 .data          0x0045bb80      0x460 shellui.o
 .data          0x0045bfe0      0x440 api.o
 .data          0x0045c420        0x0 stdio.o
 .data          0x0045c420       0x10 stdlib.o
 .data          0x0045c430        0x0 string.o
 .data          0x0045c430        0x0 conio.o
 .data          0x0045c430      0x460 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045c890      0x770 00

.bss            0x0045d000     0xd920
                0x0045d000                bss = .
                0x0045d000                _bss = .
                0x0045d000                __bss = .
 *(.bss)
 .bss           0x0045d000        0x0 crt0.o
 .bss           0x0045d000       0xf0 main.o
                0x0045d004                login_status
                0x0045d00c                interactive
                0x0045d008                login_shell
                0x0045d000                quiet
                0x0045d010                ShellFlag
 .bss           0x0045d0f0       0xd0 shellui.o
 .bss           0x0045d1c0       0x40 api.o
 .bss           0x0045d200       0x10 stdio.o
 .bss           0x0045d210     0x8000 stdlib.o
 .bss           0x00465210       0x10 string.o
 .bss           0x00465220        0x0 conio.o
 .bss           0x00465220       0xd0 builtins.o
                0x00466000                . = ALIGN (0x1000)
 *fill*         0x004652f0      0xd10 00
 COMMON         0x00466000      0xd40 crt0.o
                0x00466000                prompt
                0x00466400                stderr
                0x00466410                prompt_pos
                0x00466420                g_using_gui
                0x00466430                stdin
                0x00466440                prompt_max
                0x00466450                prompt_err
                0x00466850                g_columns
                0x00466860                stdout
                0x00466870                Streams
                0x004668f0                g_rows
                0x00466900                prompt_out
                0x00466d00                g_cursor_y
                0x00466d10                prompt_status
                0x00466d20                g_char_attrib
                0x00466d30                g_cursor_x
 COMMON         0x00466d40     0x32f0 main.o
                0x00466d40                ShellMetrics
                0x00466d50                shellStatus
                0x00466d60                CommandHistory
                0x00466d70                EOF_Reached
                0x00466d80                shellWindowWidth
                0x00466d90                ClientAreaInfo
                0x00466da0                g_current_disk_id
                0x00466db0                BufferInfo
                0x00466dc0                shellError
                0x00466dd0                shellWindowHeight
                0x00466de0                lineList
                0x00468de0                root
                0x00468df0                CurrentCommand
                0x00468e00                shell_info
                0x00468e20                shellScreenBufferMaxColumns
                0x00468e30                g_current_workingdirectory_id
                0x00468e40                shell_window_x
                0x00468e50                i2Window
                0x00468e60                rect
                0x00468e70                backgroung_color
                0x00468e80                shell_name
                0x00468e90                shellMaxRows
                0x00468ea0                screenbufferList
                0x00468ec0                foregroung_color
                0x00468ed0                pwd
                0x00468ee0                CurrentWindow
                0x00468ef0                dummycompiler
                0x00468f00                topbar_scrollbarWindow
                0x00468f10                current_semaphore
                0x00468f20                g_current_volume_id
                0x00468f30                ShellHook
                0x00468f40                topbar_checkboxWindow
                0x00468f50                shellScreenBufferMaxRows
                0x00468f60                shellScreenWidth
                0x00468f70                screen_buffer_pos
                0x00468f80                shellScreenHeight
                0x00468f90                editboxWindow
                0x00468fa0                username
                0x00468fb0                screen_buffer_x
                0x00468fc0                screen_buffer
                0x00469f70                shell_window_y
                0x00469f80                terminal_rect
                0x00469f90                password
                0x00469fa0                CursorInfo
                0x00469fb0                shellMaxColumns
                0x00469fc0                i1Window
                0x00469fd0                screen_buffer_y
                0x00469fe0                topbar_editboxWindow
                0x00469ff0                topbarWindow
                0x0046a000                ApplicationInfo
                0x0046a010                current_workingdiretory_string
 COMMON         0x0046a030      0x8f0 stdlib.o
                0x0046a030                current_mmblock
                0x0046a040                mm_prev_pointer
                0x0046a050                heap_end
                0x0046a060                g_available_heap
                0x0046a070                heap_start
                0x0046a080                heapCount
                0x0046a090                HEAP_START
                0x0046a0a0                g_heap_pointer
                0x0046a0b0                heapList
                0x0046a4b0                HEAP_SIZE
                0x0046a4c0                last_size
                0x0046a4d0                last_valid
                0x0046a4e0                mmblockList
                0x0046a8e0                libcHeap
                0x0046a8f0                Heap
                0x0046a900                mmblockCount
                0x0046a910                HEAP_END
                0x0046a920                end = .
                0x0046a920                _end = .
                0x0046a920                __end = .
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
