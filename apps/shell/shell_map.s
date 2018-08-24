
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
build_version       0x10              main.o
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
dist_version        0x10              main.o
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
randseed            0x10              stdlib.o
filename_lenght     0x10              main.o
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

.text           0x00451000     0x9000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x24 head.o
                0x00451000                shell_entry_point
                0x00451018                VECTOR
 *(.text)
 .text          0x00451024       0x70 crt0.o
                0x00451024                crt0
 .text          0x00451094     0x3ba0 main.o
                0x004534ba                shellPrompt
                0x00454a58                shell_print_tokenList
                0x00453e86                shellSendMessage
                0x004536be                shellTestThreads
                0x00453fee                shellTaskList
                0x00451302                shellProcedure
                0x00452e53                shellShell
                0x004542bd                shellShowProcessHeapPointer
                0x004547be                fatal
                0x00453431                shellThread
                0x004546ca                concat
                0x00452fb0                shellInit
                0x00454155                shellShowPPID
                0x00454325                shellShowKernelHeapPointer
                0x00453f4b                shellInitializeWorkingDiretoryString
                0x004515c5                shellWaitCmd
                0x00453593                shellShowScreenBuffer
                0x004549da                shell_pathname_backup
                0x004547e9                save_string
                0x0045498f                shellInitFilename
                0x00454281                shellShowDesktopID
                0x00454b00                is_bin
                0x00453997                shellInsertCharXY
                0x00454944                shellInitPathname
                0x004539e3                shellInsertCharPos
                0x0045465e                die
                0x004543f1                shellShowPCIInfo
                0x00454c02                show_shell_version
                0x00453ed7                shellExit
                0x004515dd                shellCompare
                0x0045353d                shellClearBuffer
                0x004548be                absolute_pathname
                0x00453789                shellRefreshScreen
                0x004545a2                feedterminalDialog
                0x00454823                shellExecuteThisScript
                0x0045374f                shellClearScreen
                0x00453d55                shellShowSystemInfo
                0x00453a1b                shellInsertNextChar
                0x00454449                shell_fntos
                0x004543c5                shellShowMemoryInfo
                0x004535f2                shellTestLoadFile
                0x00453b92                move_to
                0x00453a64                shellInsertCR
                0x00453c81                shellShowMetrics
                0x004541cd                shellShowGID
                0x0045380b                shellScroll
                0x0045441d                shellShowKernelInfo
                0x00453ee8                shellUpdateWorkingDiretoryString
                0x00453ae4                shellInsertNullTerminator
                0x00454191                shellShowUID
                0x00453aa4                shellInsertLF
                0x00453fe1                shellUpdateCurrentDirectoryID
                0x00453eae                shell_memcpy_bytes
                0x00453407                shellSetCursor
                0x00454538                shell_gramado_core_init_execve
                0x00454b81                is_sh1
                0x004510a3                shmain
                0x00453bb7                shellShowInfo
                0x00454399                shellShowVolumeInfo
                0x00453dc3                shellShowWindowInfo
                0x00451094                quit
                0x00454119                shellShowPID
                0x00454762                error
                0x00454209                shellShowUserSessionID
                0x00454245                shellShowWindowStationID
                0x0045469f                xmalloc
                0x0045436d                shellShowDiskInfo
                0x004534a6                shellTree
                0x00453492                shellHelp
                0x00453b24                shellTestMBR
 .text          0x00454c34      0x7b0 shellui.o
                0x00455230                shellTestDisplayBMP
                0x00454e90                shellCreateEditBox
                0x004551bb                shellDisplayBMP
                0x00454d23                shellTopbarProcedure
                0x004552a6                bmpDisplayBMP
                0x00454f3e                shellCreateTopBar
                0x00454c34                shellui_fntos
 .text          0x004553e4     0x1990 api.o
                0x0045617d                APIShowCurrentProcessInfo
                0x0045696a                api_getchar
                0x00455986                system11
                0x00455a2b                refresh_buffer
                0x0045605f                APISetFocus
                0x004559e9                system14
                0x00455d10                apiInitBackground
                0x00455f4f                APICreateWindow
                0x00456725                apiBeginPaint
                0x00455d15                MessageBox
                0x004561fb                APIreplace_window
                0x0045676c                apiGetSystemMetrics
                0x004559c8                system13
                0x004565dc                apiDown
                0x004562f4                apiExit
                0x00456674                enterCriticalSection
                0x004568b1                gramadocore_init_execve
                0x00456562                apiFOpen
                0x0045583c                system1
                0x004558c0                system5
                0x004563da                api_refresh_screen
                0x004568f1                apiDialog
                0x00456466                apiGetCursorY
                0x00455cbb                carrega_bitmap_16x16
                0x004566cd                exitCriticalSection
                0x004553e4                system_call
                0x00456628                apiUp
                0x0045540c                apiSystem
                0x00456885                api_get_window_with_text_input
                0x00455a0a                system15
                0x0045610f                APISetActiveWindow
                0x004564be                apiSetClientAreaRect
                0x004561d2                APIredraw_window
                0x00456510                apiCreateThread
                0x00455c57                SetNextWindowProcedure
                0x0045643a                apiGetCursorX
                0x00455c27                chama_procedimento
                0x00455d3e                call_kernel
                0x00455fdb                APIRegisterWindow
                0x00456350                api_strncmp
                0x0045624d                APIminimize_window
                0x0045585d                system2
                0x0045587e                system3
                0x004567be                api_get_current_keyboard_responder
                0x004564e7                apiCreateProcess
                0x004560a1                APIGetFocus
                0x00455902                system7
                0x004558e1                system6
                0x00456762                apiDefDialog
                0x0045601d                APICloseWindow
                0x004566f9                initializeCriticalSection
                0x00455965                system10
                0x00455c87                set_cursor
                0x00456224                APImaximize_window
                0x004568e7                execve
                0x004563ae                refresh_screen
                0x00456996                apiDisplayBMP
                0x00455ebe                call_gui
                0x00455944                system9
                0x004568bb                fork
                0x00456795                api_set_current_keyboard_responder
                0x004561a9                APIresize_window
                0x0045672f                apiEndPaint
                0x00455cb6                put_char
                0x00455bc2                print_string
                0x00456492                apiGetClientAreaRect
                0x00455bf8                edit_box
                0x0045631f                kill
                0x004563e4                apiReboot
                0x00455ce4                apiShutDown
                0x004567ea                api_set_current_mouse_responder
                0x0045629f                APIget_foregroung_window
                0x0045589f                system4
                0x0045659c                apiSaveFile
                0x00456410                apiSetCursor
                0x004559a7                system12
                0x00455bc7                vsync
                0x00455923                system8
                0x0045683f                api_set_window_with_text_input
                0x00456151                APIGetActiveWindow
                0x00456276                APIupdate_window
                0x00456813                api_get_current_mouse_responder
                0x00456324                dead_thread_collector
                0x00456539                apiStartThread
                0x004560cd                APIKillFocus
                0x004562cb                APIset_foregroung_window
                0x00456739                apiPutChar
 .text          0x00456d74       0xe0 ctype.o
                0x00456e0e                isspace
                0x00456e34                isxdigit
                0x00456e21                isupper
                0x00456d87                isalpha
                0x00456dd3                islower
                0x00456d74                isalnum
                0x00456de6                isprint
                0x00456dc0                isgraph
                0x00456dad                isdigit
                0x00456d9a                iscntrl
                0x00456dfb                ispunct
 .text          0x00456e54     0x1380 stdio.o
                0x00457681                putchar
                0x00456e54                stdio_fntos
                0x0045763d                sprintf
                0x00457db5                feof
                0x00457edf                stdioSetCursor
                0x00457d17                ungetc
                0x0045713b                puts
                0x00457e93                fputc
                0x00457f35                stdioGetCursorY
                0x00458016                scanf
                0x00457c2d                fputs
                0x00457df3                ferror
                0x00457863                input
                0x00457041                scroll
                0x00457ca2                gets
                0x004576ad                outbyte
                0x00457b49                fflush
                0x00457bb8                fprintf
                0x004579cb                stdio_system_call
                0x00456fa9                fopen
                0x00457f09                stdioGetCursorX
                0x004579f3                getchar
                0x00457f61                stdio_atoi
                0x00457a25                stdioInitialize
                0x00457d54                fgetc
                0x00456f43                fclose
                0x00457e19                fseek
                0x00457830                _outbyte
                0x00457622                printf
                0x00457103                app_clear
 .text          0x004581d4      0xaf0 stdlib.o
                0x004584ca                FreeHeap
                0x004581fc                rtGetHeapStart
                0x0045871e                free
                0x004581d4                stdlib_system_call
                0x004586b3                rand
                0x0045862a                stdlibInitMM
                0x004584d4                heapInit
                0x00458bb8                __findenv
                0x00458210                rtGetHeapPointer
                0x0045821a                rtGetAvailableHeap
                0x004586d0                srand
                0x0045868a                libcInitRT
                0x00458224                heapSetLibcHeap
                0x00458c83                getenv
                0x004586dd                malloc
                0x004584b7                AllocateHeapEx
                0x004582cb                AllocateHeap
                0x00458b2f                stdlib_strncmp
                0x00458b8d                exit
                0x00458206                rtGetHeapEnd
                0x00458723                system
 .text          0x00458cc4      0x4a0 string.o
                0x00458f2b                strcspn
                0x00458e8e                strcat
                0x00458cc4                strcmp
                0x00458ee5                bzero
                0x0045906b                strtok_r
                0x00458e21                memcpy
                0x00458df8                memoryZeroMemory
                0x00458ebe                bcopy
                0x00458e5e                strcpy
                0x00458fcb                strspn
                0x00459140                strtok
                0x00458d7d                str_cmp
                0x00458d1f                strncmp
                0x00458f00                strlen
 .text          0x00459164       0x90 conio.o
                0x004591d2                getche
                0x00459164                putch
                0x00459187                cputs
                0x004591bb                getch
 .text          0x004591f4      0x1a0 builtins.o
                0x0045935f                pwd_builtins
                0x004592f9                getuid_builtins
                0x0045930b                getgid_builtins
                0x0045927c                echo_builtins
                0x00459238                dir_builtins
                0x004592ab                exit_builtins
                0x004592d5                getpid_builtins
                0x00459229                copy_builtins
                0x004592e7                getppid_builtins
                0x00459297                exec_builtins
                0x00459208                cls_builtins
                0x0045922e                date_builtins
                0x00459233                del_builtins
                0x004591f4                cd_buitins
                0x0045931d                help_builtins
 .text          0x00459394       0x50 desktop.o
                0x00459394                desktopInitialize
                0x0045a000                . = ALIGN (0x1000)
 *fill*         0x004593e4      0xc1c 00

.rdata          0x0045a000     0x2ef0
 .rdata         0x0045a000      0x4a0 desktop.o
 .rdata         0x0045a4a0      0x4c0 builtins.o
 .rdata         0x0045a960       0x10 conio.o
 .rdata         0x0045a970      0x460 stdlib.o
 .rdata         0x0045add0       0x70 stdio.o
 .rdata         0x0045ae40      0x320 api.o
 .rdata         0x0045b160      0x720 shellui.o
 .rdata         0x0045b880     0x15c0 main.o
 .rdata         0x0045ce40       0xb0 crt0.o

.data           0x0045cef0     0x2110
                0x0045cef0                data = .
                0x0045cef0                _data = .
                0x0045cef0                __data = .
 *(.data)
 .data          0x0045cef0       0x30 crt0.o
 .data          0x0045cf20      0x560 main.o
                0x0045d3f0                current_command_number
                0x0045d3ec                remember_on_history
                0x0045d3e0                running
                0x0045d3e4                primary_prompt
                0x0045d400                long_args
                0x0045d3f4                bashrc_file
                0x0045d3f8                shell_config_file
                0x0045d3e8                secondary_prompt
 .data          0x0045d480      0x4c0 shellui.o
 .data          0x0045d940      0x440 api.o
 .data          0x0045dd80      0x120 ctype.o
                0x0045dd80                _ctype_
 .data          0x0045dea0        0x0 stdio.o
 .data          0x0045dea0        0x0 stdlib.o
 .data          0x0045dea0        0x0 string.o
 .data          0x0045dea0        0x0 conio.o
 .data          0x0045dea0      0x4c0 builtins.o
 .data          0x0045e360      0x4c0 desktop.o
                0x0045e808                primary_desktop_folder
                0x0045e80c                secondary_desktop_folder
                0x0045f000                . = ALIGN (0x1000)
 *fill*         0x0045e820      0x7e0 00

.bss            0x0045f000     0xda20
                0x0045f000                bss = .
                0x0045f000                _bss = .
                0x0045f000                __bss = .
 *(.bss)
 .bss           0x0045f000        0x0 crt0.o
 .bss           0x0045f000      0x130 main.o
                0x0045f04c                make_login_shell
                0x0045f040                no_profile
                0x0045f050                no_line_editing
                0x0045f018                current_host_name
                0x0045f044                do_version
                0x0045f034                act_like_sh
                0x0045f010                interrupt_state
                0x0045f008                login_status
                0x0045f004                executing
                0x0045f020                interactive
                0x0045f038                debugging
                0x0045f054                no_brace_expansion
                0x0045f01c                login_shell
                0x0045f03c                no_rc
                0x0045f014                current_user_name
                0x0045f048                quiet
                0x0045f000                ShellFlag
                0x0045f024                restricted
                0x0045f02c                indirection_level
                0x0045f00c                global_command
                0x0045f030                shell_level
                0x0045f028                debugging_login_shell
 .bss           0x0045f130       0xd0 shellui.o
 .bss           0x0045f200       0x40 api.o
 .bss           0x0045f240        0x0 ctype.o
 .bss           0x0045f240       0x10 stdio.o
 .bss           0x0045f250     0x8010 stdlib.o
                0x0045f250                environ
 .bss           0x00467260       0x10 string.o
 .bss           0x00467270        0x0 conio.o
 .bss           0x00467270       0xd0 builtins.o
 .bss           0x00467340       0xd0 desktop.o
                0x00468000                . = ALIGN (0x1000)
 *fill*         0x00467410      0xbf0 00
 COMMON         0x00468000      0xd40 crt0.o
                0x00468000                prompt
                0x00468400                stderr
                0x00468410                prompt_pos
                0x00468420                g_using_gui
                0x00468430                stdin
                0x00468440                prompt_max
                0x00468450                prompt_err
                0x00468850                g_columns
                0x00468860                stdout
                0x00468870                Streams
                0x004688f0                g_rows
                0x00468900                prompt_out
                0x00468d00                g_cursor_y
                0x00468d10                prompt_status
                0x00468d20                g_char_attrib
                0x00468d30                g_cursor_x
 COMMON         0x00468d40     0x33e0 main.o
                0x00468d40                ShellMetrics
                0x00468d50                shellStatus
                0x00468d60                CommandHistory
                0x00468d70                filename_buffer
                0x00468d80                EOF_Reached
                0x00468d90                pathname_lenght
                0x00468da0                shellWindowWidth
                0x00468db0                ClientAreaInfo
                0x00468dc0                g_current_disk_id
                0x00468dd0                BufferInfo
                0x00468de0                current_volume_string
                0x00468df0                shellError
                0x00468e00                build_version
                0x00468e10                shellWindowHeight
                0x00468e20                lineList
                0x0046ae20                root
                0x0046ae30                CurrentCommand
                0x0046ae40                shell_info
                0x0046ae60                shellScreenBufferMaxColumns
                0x0046ae70                g_current_workingdirectory_id
                0x0046ae80                dist_version
                0x0046ae90                shell_window_x
                0x0046aea0                i2Window
                0x0046aeb0                rect
                0x0046aec0                backgroung_color
                0x0046aed0                pwd_initialized
                0x0046aee0                shell_name
                0x0046aef0                shellMaxRows
                0x0046af00                screenbufferList
                0x0046af20                foregroung_color
                0x0046af30                pwd
                0x0046af40                CurrentWindow
                0x0046af50                dummycompiler
                0x0046af60                topbar_scrollbarWindow
                0x0046af70                filename_lenght
                0x0046af80                current_semaphore
                0x0046af90                g_current_volume_id
                0x0046afa0                ShellHook
                0x0046afb0                topbar_checkboxWindow
                0x0046afc0                shellScreenBufferMaxRows
                0x0046afd0                shellScreenWidth
                0x0046afe0                screen_buffer_pos
                0x0046aff0                shellScreenHeight
                0x0046b000                current_volume_id
                0x0046b010                pathname_buffer
                0x0046b050                filename_initilized
                0x0046b060                pathname_initilized
                0x0046b070                editboxWindow
                0x0046b080                username
                0x0046b090                screen_buffer_x
                0x0046b0a0                screen_buffer
                0x0046c050                shell_window_y
                0x0046c060                terminal_rect
                0x0046c070                password
                0x0046c080                CursorInfo
                0x0046c090                shellMaxColumns
                0x0046c0a0                i1Window
                0x0046c0b0                screen_buffer_y
                0x0046c0c0                topbar_editboxWindow
                0x0046c0d0                topbarWindow
                0x0046c0e0                ApplicationInfo
                0x0046c0f0                shell_environment
                0x0046c100                current_workingdiretory_string
 COMMON         0x0046c120      0x900 stdlib.o
                0x0046c120                current_mmblock
                0x0046c130                mm_prev_pointer
                0x0046c140                heap_end
                0x0046c150                g_available_heap
                0x0046c160                heap_start
                0x0046c170                heapCount
                0x0046c180                HEAP_START
                0x0046c190                g_heap_pointer
                0x0046c1a0                heapList
                0x0046c5a0                randseed
                0x0046c5b0                HEAP_SIZE
                0x0046c5c0                last_size
                0x0046c5d0                last_valid
                0x0046c5e0                mmblockList
                0x0046c9e0                libcHeap
                0x0046c9f0                Heap
                0x0046ca00                mmblockCount
                0x0046ca10                HEAP_END
                0x0046ca20                end = .
                0x0046ca20                _end = .
                0x0046ca20                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD shellui.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
LOAD builtins.o
LOAD desktop.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
