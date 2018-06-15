
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x400             crt0.o
CommandHistory      0x10              main.o
filename_buffer     0x10              main.o
EOF_Reached         0x10              main.o
pathname_lenght     0x10              main.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
g_current_disk_id   0x10              main.o
BufferInfo          0x10              main.o
current_volume_string
                    0x10              main.o
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
pwd_initialized     0x10              main.o
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
current_connection  0x10              main.o
filename_lenght     0x10              main.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
g_current_volume_id
                    0x10              main.o
ShellHook           0x10              main.o
current_command     0x10              main.o
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
current_volume_id   0x10              main.o
pathname_buffer     0x40              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
filename_initilized
                    0x10              main.o
prompt_out          0x400             crt0.o
pathname_initilized
                    0x10              main.o
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
shell_environment   0x10              main.o
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
 .text          0x004510a4     0x35e0 main.o
                0x0045316b                shellPrompt
                0x00453b20                shellSendMessage
                0x0045335b                shellTestThreads
                0x00453c88                shellTaskList
                0x004512f4                shellProcedure
                0x00452b60                shellShell
                0x00453f57                shellShowProcessHeapPointer
                0x0045312a                shellThread
                0x00454364                concat
                0x00452cbd                shellInit
                0x00453def                shellShowPPID
                0x00453fbf                shellShowKernelHeapPointer
                0x00453be5                shellInitializeWorkingDiretoryString
                0x00451525                shellWaitCmd
                0x00453230                shellShowScreenBuffer
                0x004545fa                shell_pathname_backup
                0x004510b3                GramadoMain
                0x004545af                shellInitFilename
                0x00453f1b                shellShowDesktopID
                0x00453633                shellInsertCharXY
                0x00454564                shellInitPathname
                0x0045367d                shellInsertCharPos
                0x004542f8                die
                0x0045408b                shellShowPCIInfo
                0x00453b71                shellExit
                0x0045153d                shellCompare
                0x004531ee                shellClearBuffer
                0x004544de                absolute_pathname
                0x00453425                shellRefreshScreen
                0x0045423c                feedterminalDialog
                0x00454443                shellExecuteThisScript
                0x004533eb                shellClearScreen
                0x004539ef                shellShowSystemInfo
                0x004536b5                shellInsertNextChar
                0x004540e3                shell_fntos
                0x0045405f                shellShowMemoryInfo
                0x0045328f                shellTestLoadFile
                0x0045382c                move_to
                0x004536fe                shellInsertCR
                0x0045391b                shellShowMetrics
                0x00453e67                shellShowGID
                0x004534a7                shellScroll
                0x004540b7                shellShowKernelInfo
                0x00453b82                shellUpdateWorkingDiretoryString
                0x0045377e                shellInsertNullTerminator
                0x00453e2b                shellShowUID
                0x0045373e                shellInsertLF
                0x00453c7b                shellUpdateCurrentDirectoryID
                0x00453b48                shell_memcpy_bytes
                0x00453100                shellSetCursor
                0x004541d2                shell_gramado_core_init_execve
                0x00453851                shellShowInfo
                0x00454033                shellShowVolumeInfo
                0x00453a5d                shellShowWindowInfo
                0x004510a4                quit
                0x00453db3                shellShowPID
                0x004543fc                error
                0x00453ea3                shellShowUserSessionID
                0x00453edf                shellShowWindowStationID
                0x00454339                xmalloc
                0x00454007                shellShowDiskInfo
                0x00453157                shellTree
                0x00453143                shellHelp
                0x004537be                shellTestMBR
 .text          0x00454684      0x7b0 shellui.o
                0x00454c80                shellTestDisplayBMP
                0x004548e0                shellCreateEditBox
                0x00454c0b                shellDisplayBMP
                0x00454773                shellTopbarProcedure
                0x00454cf6                bmpDisplayBMP
                0x0045498e                shellCreateTopBar
                0x00454684                shellui_fntos
 .text          0x00454e34     0x1980 api.o
                0x00455be9                APIShowCurrentProcessInfo
                0x004563ad                api_getchar
                0x004553d6                system11
                0x0045547b                refresh_buffer
                0x00455acb                APISetFocus
                0x00455439                system14
                0x00455760                apiInitBackground
                0x0045599f                APICreateWindow
                0x00456168                apiBeginPaint
                0x00455765                MessageBox
                0x00455c67                APIreplace_window
                0x004561af                apiGetSystemMetrics
                0x00455418                system13
                0x0045601f                apiDown
                0x00455d37                apiExit
                0x004560b7                enterCriticalSection
                0x004562f4                gramadocore_init_execve
                0x00455fa5                apiFOpen
                0x0045528c                system1
                0x00455310                system5
                0x00455e1d                api_refresh_screen
                0x00456334                apiDialog
                0x00455ea9                apiGetCursorY
                0x0045570b                carrega_bitmap_16x16
                0x00456110                exitCriticalSection
                0x00454e34                system_call
                0x0045606b                apiUp
                0x00454e5c                apiSystem
                0x004562c8                api_get_window_with_text_input
                0x0045545a                system15
                0x00455b7b                APISetActiveWindow
                0x00455f01                apiSetClientAreaRect
                0x00455c3e                APIredraw_window
                0x00455f53                apiCreateThread
                0x004556a7                SetNextWindowProcedure
                0x00455e7d                apiGetCursorX
                0x00455677                chama_procedimento
                0x0045578e                call_kernel
                0x00455a47                APIRegisterWindow
                0x00455d93                api_strncmp
                0x00455cb9                APIminimize_window
                0x004552ad                system2
                0x004552ce                system3
                0x00456201                api_get_current_keyboard_responder
                0x00455f2a                apiCreateProcess
                0x00455b0d                APIGetFocus
                0x00455352                system7
                0x00455331                system6
                0x004561a5                apiDefDialog
                0x00455a89                APICloseWindow
                0x0045613c                initializeCriticalSection
                0x004553b5                system10
                0x004556d7                set_cursor
                0x00455c90                APImaximize_window
                0x0045632a                execve
                0x00455df1                refresh_screen
                0x004563d9                apiDisplayBMP
                0x0045590e                call_gui
                0x00455394                system9
                0x004562fe                fork
                0x004561d8                api_set_current_keyboard_responder
                0x00455c15                APIresize_window
                0x00456172                apiEndPaint
                0x00455706                put_char
                0x00455612                print_string
                0x00455ed5                apiGetClientAreaRect
                0x00455648                edit_box
                0x00455d62                kill
                0x00455e27                apiReboot
                0x00455734                apiShutDown
                0x0045622d                api_set_current_mouse_responder
                0x00455ce2                APIget_foregroung_window
                0x004552ef                system4
                0x00455fdf                apiSaveFile
                0x00455e53                apiSetCursor
                0x004553f7                system12
                0x00455617                vsync
                0x00455373                system8
                0x00456282                api_set_window_with_text_input
                0x00455bbd                APIGetActiveWindow
                0x00456256                api_get_current_mouse_responder
                0x00455d67                dead_thread_collector
                0x00455f7c                apiStartThread
                0x00455b39                APIKillFocus
                0x00455d0e                APIset_foregroung_window
                0x0045617c                apiPutChar
 .text          0x004567b4     0x1110 stdio.o
                0x004570fb                putchar
                0x004567b4                stdio_fntos
                0x004570b7                sprintf
                0x0045778c                feof
                0x0045786a                fputc
                0x00457641                fputs
                0x004577ca                ferror
                0x004572e7                input
                0x004569a1                scroll
                0x004572dd                printf_main
                0x004576b6                gets
                0x00457127                outbyte
                0x00456b4b                app_print
                0x0045755c                fflush
                0x004575cc                fprintf
                0x004573de                stdio_system_call
                0x00456909                fopen
                0x00457406                getchar
                0x00457438                stdioInitialize
                0x0045772b                fgetc
                0x004568a3                fclose
                0x004577f0                fseek
                0x004572aa                _outbyte
                0x0045709c                printf
                0x00456adf                app_clear
 .text          0x004578c4      0xae0 stdlib.o
                0x00457bba                FreeHeap
                0x004578ec                rtGetHeapStart
                0x00457e01                free
                0x004578c4                stdlib_system_call
                0x00457da3                rand
                0x00457d1a                stdlibInitMM
                0x00457bc4                heapInit
                0x00458299                __findenv
                0x00457900                rtGetHeapPointer
                0x0045790a                rtGetAvailableHeap
                0x00457d7a                libcInitRT
                0x00457914                heapSetLibcHeap
                0x00458364                getenv
                0x00457dc0                malloc
                0x00457ba7                AllocateHeapEx
                0x004579bb                AllocateHeap
                0x00458212                stdlib_strncmp
                0x00458270                exit
                0x004578f6                rtGetHeapEnd
                0x00457e06                system
 .text          0x004583a4      0x4a0 string.o
                0x0045860b                strcspn
                0x0045856e                strcat
                0x004583a4                strcmp
                0x004585c5                bzero
                0x0045874b                strtok_r
                0x00458501                memcpy
                0x004584d8                memoryZeroMemory
                0x0045859e                bcopy
                0x0045853e                strcpy
                0x004586ab                strspn
                0x00458820                strtok
                0x0045845d                str_cmp
                0x004583ff                strncmp
                0x004585e0                strlen
 .text          0x00458844       0x90 conio.o
                0x004588b2                getche
                0x00458844                putch
                0x00458867                cputs
                0x0045889b                getch
 .text          0x004588d4      0x1a0 builtins.o
                0x00458a39                pwd_builtins
                0x004589d3                getuid_builtins
                0x004589e5                getgid_builtins
                0x0045895c                echo_builtins
                0x00458918                dir_builtins
                0x0045898f                exit_builtins
                0x004589af                getpid_builtins
                0x00458909                copy_builtins
                0x004589c1                getppid_builtins
                0x0045897b                exec_builtins
                0x004588e8                cls_builtins
                0x0045890e                date_builtins
                0x00458913                del_builtins
                0x004588d4                cd_buitins
                0x004589f7                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458a74      0x58c 00

.rdata          0x00459000     0x28e0
 .rdata         0x00459000      0x4e0 builtins.o
 .rdata         0x004594e0       0x10 conio.o
 .rdata         0x004594f0      0x460 stdlib.o
 .rdata         0x00459950       0x40 stdio.o
 .rdata         0x00459990      0x320 api.o
 .rdata         0x00459cb0      0x720 shellui.o
 .rdata         0x0045a3d0     0x1460 main.o
 .rdata         0x0045b830       0xb0 crt0.o

.data           0x0045b8e0     0x1720
                0x0045b8e0                data = .
                0x0045b8e0                _data = .
                0x0045b8e0                __data = .
 *(.data)
 .data          0x0045b8e0       0x30 crt0.o
 .data          0x0045b910      0x4e0 main.o
                0x0045bdd0                running
                0x0045bdd4                primary_prompt
                0x0045bddc                shell_config_file
                0x0045bdd8                secondary_prompt
 .data          0x0045bdf0      0x4c0 shellui.o
 .data          0x0045c2b0      0x440 api.o
 .data          0x0045c6f0        0x0 stdio.o
 .data          0x0045c6f0       0x10 stdlib.o
 .data          0x0045c700        0x0 string.o
 .data          0x0045c700        0x0 conio.o
 .data          0x0045c700      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cbc0      0x440 00

.bss            0x0045d000     0xda10
                0x0045d000                bss = .
                0x0045d000                _bss = .
                0x0045d000                __bss = .
 *(.bss)
 .bss           0x0045d000        0x0 crt0.o
 .bss           0x0045d000       0xf0 main.o
                0x0045d008                login_status
                0x0045d004                executing
                0x0045d010                interactive
                0x0045d00c                login_shell
                0x0045d000                quiet
                0x0045d014                ShellFlag
 .bss           0x0045d0f0       0xd0 shellui.o
 .bss           0x0045d1c0       0x40 api.o
 .bss           0x0045d200       0x10 stdio.o
 .bss           0x0045d210     0x8010 stdlib.o
                0x0045d210                environ
 .bss           0x00465220       0x10 string.o
 .bss           0x00465230        0x0 conio.o
 .bss           0x00465230       0xd0 builtins.o
                0x00466000                . = ALIGN (0x1000)
 *fill*         0x00465300      0xd00 00
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
 COMMON         0x00466d40     0x33e0 main.o
                0x00466d40                ShellMetrics
                0x00466d50                shellStatus
                0x00466d60                CommandHistory
                0x00466d70                filename_buffer
                0x00466d80                EOF_Reached
                0x00466d90                pathname_lenght
                0x00466da0                shellWindowWidth
                0x00466db0                ClientAreaInfo
                0x00466dc0                g_current_disk_id
                0x00466dd0                BufferInfo
                0x00466de0                current_volume_string
                0x00466df0                shellError
                0x00466e00                shellWindowHeight
                0x00466e10                lineList
                0x00468e10                root
                0x00468e20                CurrentCommand
                0x00468e30                shell_info
                0x00468e50                shellScreenBufferMaxColumns
                0x00468e60                g_current_workingdirectory_id
                0x00468e70                shell_window_x
                0x00468e80                i2Window
                0x00468e90                rect
                0x00468ea0                backgroung_color
                0x00468eb0                pwd_initialized
                0x00468ec0                shell_name
                0x00468ed0                shellMaxRows
                0x00468ee0                screenbufferList
                0x00468f00                foregroung_color
                0x00468f10                pwd
                0x00468f20                CurrentWindow
                0x00468f30                dummycompiler
                0x00468f40                topbar_scrollbarWindow
                0x00468f50                current_connection
                0x00468f60                filename_lenght
                0x00468f70                current_semaphore
                0x00468f80                g_current_volume_id
                0x00468f90                ShellHook
                0x00468fa0                current_command
                0x00468fb0                topbar_checkboxWindow
                0x00468fc0                shellScreenBufferMaxRows
                0x00468fd0                shellScreenWidth
                0x00468fe0                screen_buffer_pos
                0x00468ff0                shellScreenHeight
                0x00469000                current_volume_id
                0x00469010                pathname_buffer
                0x00469050                filename_initilized
                0x00469060                pathname_initilized
                0x00469070                editboxWindow
                0x00469080                username
                0x00469090                screen_buffer_x
                0x004690a0                screen_buffer
                0x0046a050                shell_window_y
                0x0046a060                terminal_rect
                0x0046a070                password
                0x0046a080                CursorInfo
                0x0046a090                shellMaxColumns
                0x0046a0a0                i1Window
                0x0046a0b0                screen_buffer_y
                0x0046a0c0                topbar_editboxWindow
                0x0046a0d0                topbarWindow
                0x0046a0e0                ApplicationInfo
                0x0046a0f0                shell_environment
                0x0046a100                current_workingdiretory_string
 COMMON         0x0046a120      0x8f0 stdlib.o
                0x0046a120                current_mmblock
                0x0046a130                mm_prev_pointer
                0x0046a140                heap_end
                0x0046a150                g_available_heap
                0x0046a160                heap_start
                0x0046a170                heapCount
                0x0046a180                HEAP_START
                0x0046a190                g_heap_pointer
                0x0046a1a0                heapList
                0x0046a5a0                HEAP_SIZE
                0x0046a5b0                last_size
                0x0046a5c0                last_valid
                0x0046a5d0                mmblockList
                0x0046a9d0                libcHeap
                0x0046a9e0                Heap
                0x0046a9f0                mmblockCount
                0x0046aa00                HEAP_END
                0x0046aa10                end = .
                0x0046aa10                _end = .
                0x0046aa10                __end = .
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
