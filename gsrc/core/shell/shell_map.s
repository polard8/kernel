
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
 .text          0x004510a4     0x3660 main.o
                0x004531f2                shellPrompt
                0x00453ba7                shellSendMessage
                0x004533e2                shellTestThreads
                0x00453d0f                shellTaskList
                0x004513c7                shellProcedure
                0x00452be7                shellShell
                0x00453fde                shellShowProcessHeapPointer
                0x004531b1                shellThread
                0x004543eb                concat
                0x00452d44                shellInit
                0x00453e76                shellShowPPID
                0x00454046                shellShowKernelHeapPointer
                0x00453c6c                shellInitializeWorkingDiretoryString
                0x004515ed                shellWaitCmd
                0x004532b7                shellShowScreenBuffer
                0x00454681                shell_pathname_backup
                0x004510b3                GramadoMain
                0x00454636                shellInitFilename
                0x00453fa2                shellShowDesktopID
                0x004536ba                shellInsertCharXY
                0x004545eb                shellInitPathname
                0x00453704                shellInsertCharPos
                0x0045437f                die
                0x00454112                shellShowPCIInfo
                0x00453bf8                shellExit
                0x00451605                shellCompare
                0x00453275                shellClearBuffer
                0x00454565                absolute_pathname
                0x004534ac                shellRefreshScreen
                0x004542c3                feedterminalDialog
                0x004544ca                shellExecuteThisScript
                0x00453472                shellClearScreen
                0x00453a76                shellShowSystemInfo
                0x0045373c                shellInsertNextChar
                0x0045416a                shell_fntos
                0x004540e6                shellShowMemoryInfo
                0x00453316                shellTestLoadFile
                0x004538b3                move_to
                0x00453785                shellInsertCR
                0x004539a2                shellShowMetrics
                0x00453eee                shellShowGID
                0x0045352e                shellScroll
                0x0045413e                shellShowKernelInfo
                0x00453c09                shellUpdateWorkingDiretoryString
                0x00453805                shellInsertNullTerminator
                0x00453eb2                shellShowUID
                0x004537c5                shellInsertLF
                0x00453d02                shellUpdateCurrentDirectoryID
                0x00453bcf                shell_memcpy_bytes
                0x00453187                shellSetCursor
                0x00454259                shell_gramado_core_init_execve
                0x004538d8                shellShowInfo
                0x004540ba                shellShowVolumeInfo
                0x00453ae4                shellShowWindowInfo
                0x004510a4                quit
                0x00453e3a                shellShowPID
                0x00454483                error
                0x00453f2a                shellShowUserSessionID
                0x00453f66                shellShowWindowStationID
                0x004543c0                xmalloc
                0x0045408e                shellShowDiskInfo
                0x004531de                shellTree
                0x004531ca                shellHelp
                0x00453845                shellTestMBR
 .text          0x00454704      0x7b0 shellui.o
                0x00454d00                shellTestDisplayBMP
                0x00454960                shellCreateEditBox
                0x00454c8b                shellDisplayBMP
                0x004547f3                shellTopbarProcedure
                0x00454d76                bmpDisplayBMP
                0x00454a0e                shellCreateTopBar
                0x00454704                shellui_fntos
 .text          0x00454eb4     0x1980 api.o
                0x00455c69                APIShowCurrentProcessInfo
                0x0045642d                api_getchar
                0x00455456                system11
                0x004554fb                refresh_buffer
                0x00455b4b                APISetFocus
                0x004554b9                system14
                0x004557e0                apiInitBackground
                0x00455a1f                APICreateWindow
                0x004561e8                apiBeginPaint
                0x004557e5                MessageBox
                0x00455ce7                APIreplace_window
                0x0045622f                apiGetSystemMetrics
                0x00455498                system13
                0x0045609f                apiDown
                0x00455db7                apiExit
                0x00456137                enterCriticalSection
                0x00456374                gramadocore_init_execve
                0x00456025                apiFOpen
                0x0045530c                system1
                0x00455390                system5
                0x00455e9d                api_refresh_screen
                0x004563b4                apiDialog
                0x00455f29                apiGetCursorY
                0x0045578b                carrega_bitmap_16x16
                0x00456190                exitCriticalSection
                0x00454eb4                system_call
                0x004560eb                apiUp
                0x00454edc                apiSystem
                0x00456348                api_get_window_with_text_input
                0x004554da                system15
                0x00455bfb                APISetActiveWindow
                0x00455f81                apiSetClientAreaRect
                0x00455cbe                APIredraw_window
                0x00455fd3                apiCreateThread
                0x00455727                SetNextWindowProcedure
                0x00455efd                apiGetCursorX
                0x004556f7                chama_procedimento
                0x0045580e                call_kernel
                0x00455ac7                APIRegisterWindow
                0x00455e13                api_strncmp
                0x00455d39                APIminimize_window
                0x0045532d                system2
                0x0045534e                system3
                0x00456281                api_get_current_keyboard_responder
                0x00455faa                apiCreateProcess
                0x00455b8d                APIGetFocus
                0x004553d2                system7
                0x004553b1                system6
                0x00456225                apiDefDialog
                0x00455b09                APICloseWindow
                0x004561bc                initializeCriticalSection
                0x00455435                system10
                0x00455757                set_cursor
                0x00455d10                APImaximize_window
                0x004563aa                execve
                0x00455e71                refresh_screen
                0x00456459                apiDisplayBMP
                0x0045598e                call_gui
                0x00455414                system9
                0x0045637e                fork
                0x00456258                api_set_current_keyboard_responder
                0x00455c95                APIresize_window
                0x004561f2                apiEndPaint
                0x00455786                put_char
                0x00455692                print_string
                0x00455f55                apiGetClientAreaRect
                0x004556c8                edit_box
                0x00455de2                kill
                0x00455ea7                apiReboot
                0x004557b4                apiShutDown
                0x004562ad                api_set_current_mouse_responder
                0x00455d62                APIget_foregroung_window
                0x0045536f                system4
                0x0045605f                apiSaveFile
                0x00455ed3                apiSetCursor
                0x00455477                system12
                0x00455697                vsync
                0x004553f3                system8
                0x00456302                api_set_window_with_text_input
                0x00455c3d                APIGetActiveWindow
                0x004562d6                api_get_current_mouse_responder
                0x00455de7                dead_thread_collector
                0x00455ffc                apiStartThread
                0x00455bb9                APIKillFocus
                0x00455d8e                APIset_foregroung_window
                0x004561fc                apiPutChar
 .text          0x00456834     0x1110 stdio.o
                0x0045717b                putchar
                0x00456834                stdio_fntos
                0x00457137                sprintf
                0x0045780c                feof
                0x004578ea                fputc
                0x004576c1                fputs
                0x0045784a                ferror
                0x00457367                input
                0x00456a21                scroll
                0x0045735d                printf_main
                0x00457736                gets
                0x004571a7                outbyte
                0x00456bcb                app_print
                0x004575dc                fflush
                0x0045764c                fprintf
                0x0045745e                stdio_system_call
                0x00456989                fopen
                0x00457486                getchar
                0x004574b8                stdioInitialize
                0x004577ab                fgetc
                0x00456923                fclose
                0x00457870                fseek
                0x0045732a                _outbyte
                0x0045711c                printf
                0x00456b5f                app_clear
 .text          0x00457944      0xae0 stdlib.o
                0x00457c3a                FreeHeap
                0x0045796c                rtGetHeapStart
                0x00457e81                free
                0x00457944                stdlib_system_call
                0x00457e23                rand
                0x00457d9a                stdlibInitMM
                0x00457c44                heapInit
                0x00458319                __findenv
                0x00457980                rtGetHeapPointer
                0x0045798a                rtGetAvailableHeap
                0x00457dfa                libcInitRT
                0x00457994                heapSetLibcHeap
                0x004583e4                getenv
                0x00457e40                malloc
                0x00457c27                AllocateHeapEx
                0x00457a3b                AllocateHeap
                0x00458292                stdlib_strncmp
                0x004582f0                exit
                0x00457976                rtGetHeapEnd
                0x00457e86                system
 .text          0x00458424      0x4a0 string.o
                0x0045868b                strcspn
                0x004585ee                strcat
                0x00458424                strcmp
                0x00458645                bzero
                0x004587cb                strtok_r
                0x00458581                memcpy
                0x00458558                memoryZeroMemory
                0x0045861e                bcopy
                0x004585be                strcpy
                0x0045872b                strspn
                0x004588a0                strtok
                0x004584dd                str_cmp
                0x0045847f                strncmp
                0x00458660                strlen
 .text          0x004588c4       0x90 conio.o
                0x00458932                getche
                0x004588c4                putch
                0x004588e7                cputs
                0x0045891b                getch
 .text          0x00458954      0x1a0 builtins.o
                0x00458ab9                pwd_builtins
                0x00458a53                getuid_builtins
                0x00458a65                getgid_builtins
                0x004589dc                echo_builtins
                0x00458998                dir_builtins
                0x00458a0f                exit_builtins
                0x00458a2f                getpid_builtins
                0x00458989                copy_builtins
                0x00458a41                getppid_builtins
                0x004589fb                exec_builtins
                0x00458968                cls_builtins
                0x0045898e                date_builtins
                0x00458993                del_builtins
                0x00458954                cd_buitins
                0x00458a77                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458af4      0x50c 00

.rdata          0x00459000     0x28c0
 .rdata         0x00459000      0x4e0 builtins.o
 .rdata         0x004594e0       0x10 conio.o
 .rdata         0x004594f0      0x460 stdlib.o
 .rdata         0x00459950       0x40 stdio.o
 .rdata         0x00459990      0x320 api.o
 .rdata         0x00459cb0      0x720 shellui.o
 .rdata         0x0045a3d0     0x1440 main.o
 .rdata         0x0045b810       0xb0 crt0.o

.data           0x0045b8c0     0x1740
                0x0045b8c0                data = .
                0x0045b8c0                _data = .
                0x0045b8c0                __data = .
 *(.data)
 .data          0x0045b8c0       0x30 crt0.o
 .data          0x0045b8f0      0x4e0 main.o
                0x0045bdb0                running
                0x0045bdb4                primary_prompt
                0x0045bdbc                shell_config_file
                0x0045bdb8                secondary_prompt
 .data          0x0045bdd0      0x4c0 shellui.o
 .data          0x0045c290      0x440 api.o
 .data          0x0045c6d0        0x0 stdio.o
 .data          0x0045c6d0       0x10 stdlib.o
 .data          0x0045c6e0        0x0 string.o
 .data          0x0045c6e0        0x0 conio.o
 .data          0x0045c6e0      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cba0      0x460 00

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
