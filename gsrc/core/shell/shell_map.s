
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
 .text          0x004510a4     0x3970 main.o
                0x00453355                shellPrompt
                0x00454863                shell_print_tokenList
                0x00453d0b                shellSendMessage
                0x00453545                shellTestThreads
                0x00453e73                shellTaskList
                0x00451300                shellProcedure
                0x00452cea                shellShell
                0x00454142                shellShowProcessHeapPointer
                0x004532b4                shellThread
                0x0045454f                concat
                0x00452e47                shellInit
                0x00453fda                shellShowPPID
                0x004541aa                shellShowKernelHeapPointer
                0x00453dd0                shellInitializeWorkingDiretoryString
                0x004515c3                shellWaitCmd
                0x0045341a                shellShowScreenBuffer
                0x004547e5                shell_pathname_backup
                0x004510b3                GramadoMain
                0x0045479a                shellInitFilename
                0x00454106                shellShowDesktopID
                0x0045490b                is_bin
                0x0045381e                shellInsertCharXY
                0x0045474f                shellInitPathname
                0x00453868                shellInsertCharPos
                0x004544e3                die
                0x00454276                shellShowPCIInfo
                0x00453d5c                shellExit
                0x004515db                shellCompare
                0x004533d8                shellClearBuffer
                0x004546c9                absolute_pathname
                0x00453610                shellRefreshScreen
                0x00454427                feedterminalDialog
                0x0045462e                shellExecuteThisScript
                0x004535d6                shellClearScreen
                0x00453bda                shellShowSystemInfo
                0x004538a0                shellInsertNextChar
                0x004542ce                shell_fntos
                0x0045424a                shellShowMemoryInfo
                0x00453479                shellTestLoadFile
                0x00453a17                move_to
                0x004538e9                shellInsertCR
                0x00453b06                shellShowMetrics
                0x00454052                shellShowGID
                0x00453692                shellScroll
                0x004542a2                shellShowKernelInfo
                0x00453d6d                shellUpdateWorkingDiretoryString
                0x00453969                shellInsertNullTerminator
                0x00454016                shellShowUID
                0x00453929                shellInsertLF
                0x00453e66                shellUpdateCurrentDirectoryID
                0x00453d33                shell_memcpy_bytes
                0x0045328a                shellSetCursor
                0x004543bd                shell_gramado_core_init_execve
                0x0045498c                is_sh1
                0x00453a3c                shellShowInfo
                0x0045421e                shellShowVolumeInfo
                0x00453c48                shellShowWindowInfo
                0x004510a4                quit
                0x00453f9e                shellShowPID
                0x004545e7                error
                0x0045408e                shellShowUserSessionID
                0x004540ca                shellShowWindowStationID
                0x00454524                xmalloc
                0x004541f2                shellShowDiskInfo
                0x00453341                shellTree
                0x0045332d                shellHelp
                0x004539a9                shellTestMBR
 .text          0x00454a14      0x7b0 shellui.o
                0x00455010                shellTestDisplayBMP
                0x00454c70                shellCreateEditBox
                0x00454f9b                shellDisplayBMP
                0x00454b03                shellTopbarProcedure
                0x00455086                bmpDisplayBMP
                0x00454d1e                shellCreateTopBar
                0x00454a14                shellui_fntos
 .text          0x004551c4     0x1990 api.o
                0x00455f5d                APIShowCurrentProcessInfo
                0x0045674a                api_getchar
                0x00455766                system11
                0x0045580b                refresh_buffer
                0x00455e3f                APISetFocus
                0x004557c9                system14
                0x00455af0                apiInitBackground
                0x00455d2f                APICreateWindow
                0x00456505                apiBeginPaint
                0x00455af5                MessageBox
                0x00455fdb                APIreplace_window
                0x0045654c                apiGetSystemMetrics
                0x004557a8                system13
                0x004563bc                apiDown
                0x004560d4                apiExit
                0x00456454                enterCriticalSection
                0x00456691                gramadocore_init_execve
                0x00456342                apiFOpen
                0x0045561c                system1
                0x004556a0                system5
                0x004561ba                api_refresh_screen
                0x004566d1                apiDialog
                0x00456246                apiGetCursorY
                0x00455a9b                carrega_bitmap_16x16
                0x004564ad                exitCriticalSection
                0x004551c4                system_call
                0x00456408                apiUp
                0x004551ec                apiSystem
                0x00456665                api_get_window_with_text_input
                0x004557ea                system15
                0x00455eef                APISetActiveWindow
                0x0045629e                apiSetClientAreaRect
                0x00455fb2                APIredraw_window
                0x004562f0                apiCreateThread
                0x00455a37                SetNextWindowProcedure
                0x0045621a                apiGetCursorX
                0x00455a07                chama_procedimento
                0x00455b1e                call_kernel
                0x00455dbb                APIRegisterWindow
                0x00456130                api_strncmp
                0x0045602d                APIminimize_window
                0x0045563d                system2
                0x0045565e                system3
                0x0045659e                api_get_current_keyboard_responder
                0x004562c7                apiCreateProcess
                0x00455e81                APIGetFocus
                0x004556e2                system7
                0x004556c1                system6
                0x00456542                apiDefDialog
                0x00455dfd                APICloseWindow
                0x004564d9                initializeCriticalSection
                0x00455745                system10
                0x00455a67                set_cursor
                0x00456004                APImaximize_window
                0x004566c7                execve
                0x0045618e                refresh_screen
                0x00456776                apiDisplayBMP
                0x00455c9e                call_gui
                0x00455724                system9
                0x0045669b                fork
                0x00456575                api_set_current_keyboard_responder
                0x00455f89                APIresize_window
                0x0045650f                apiEndPaint
                0x00455a96                put_char
                0x004559a2                print_string
                0x00456272                apiGetClientAreaRect
                0x004559d8                edit_box
                0x004560ff                kill
                0x004561c4                apiReboot
                0x00455ac4                apiShutDown
                0x004565ca                api_set_current_mouse_responder
                0x0045607f                APIget_foregroung_window
                0x0045567f                system4
                0x0045637c                apiSaveFile
                0x004561f0                apiSetCursor
                0x00455787                system12
                0x004559a7                vsync
                0x00455703                system8
                0x0045661f                api_set_window_with_text_input
                0x00455f31                APIGetActiveWindow
                0x00456056                APIupdate_window
                0x004565f3                api_get_current_mouse_responder
                0x00456104                dead_thread_collector
                0x00456319                apiStartThread
                0x00455ead                APIKillFocus
                0x004560ab                APIset_foregroung_window
                0x00456519                apiPutChar
 .text          0x00456b54     0x1110 stdio.o
                0x0045749b                putchar
                0x00456b54                stdio_fntos
                0x00457457                sprintf
                0x00457b2c                feof
                0x00457c0a                fputc
                0x004579e1                fputs
                0x00457b6a                ferror
                0x00457687                input
                0x00456d41                scroll
                0x0045767d                printf_main
                0x00457a56                gets
                0x004574c7                outbyte
                0x00456eeb                app_print
                0x004578fc                fflush
                0x0045796c                fprintf
                0x0045777e                stdio_system_call
                0x00456ca9                fopen
                0x004577a6                getchar
                0x004577d8                stdioInitialize
                0x00457acb                fgetc
                0x00456c43                fclose
                0x00457b90                fseek
                0x0045764a                _outbyte
                0x0045743c                printf
                0x00456e7f                app_clear
 .text          0x00457c64      0xae0 stdlib.o
                0x00457f5a                FreeHeap
                0x00457c8c                rtGetHeapStart
                0x004581a1                free
                0x00457c64                stdlib_system_call
                0x00458143                rand
                0x004580ba                stdlibInitMM
                0x00457f64                heapInit
                0x00458639                __findenv
                0x00457ca0                rtGetHeapPointer
                0x00457caa                rtGetAvailableHeap
                0x0045811a                libcInitRT
                0x00457cb4                heapSetLibcHeap
                0x00458704                getenv
                0x00458160                malloc
                0x00457f47                AllocateHeapEx
                0x00457d5b                AllocateHeap
                0x004585b2                stdlib_strncmp
                0x00458610                exit
                0x00457c96                rtGetHeapEnd
                0x004581a6                system
 .text          0x00458744      0x4a0 string.o
                0x004589ab                strcspn
                0x0045890e                strcat
                0x00458744                strcmp
                0x00458965                bzero
                0x00458aeb                strtok_r
                0x004588a1                memcpy
                0x00458878                memoryZeroMemory
                0x0045893e                bcopy
                0x004588de                strcpy
                0x00458a4b                strspn
                0x00458bc0                strtok
                0x004587fd                str_cmp
                0x0045879f                strncmp
                0x00458980                strlen
 .text          0x00458be4       0x90 conio.o
                0x00458c52                getche
                0x00458be4                putch
                0x00458c07                cputs
                0x00458c3b                getch
 .text          0x00458c74      0x1a0 builtins.o
                0x00458ddf                pwd_builtins
                0x00458d79                getuid_builtins
                0x00458d8b                getgid_builtins
                0x00458cfc                echo_builtins
                0x00458cb8                dir_builtins
                0x00458d2b                exit_builtins
                0x00458d55                getpid_builtins
                0x00458ca9                copy_builtins
                0x00458d67                getppid_builtins
                0x00458d17                exec_builtins
                0x00458c88                cls_builtins
                0x00458cae                date_builtins
                0x00458cb3                del_builtins
                0x00458c74                cd_buitins
                0x00458d9d                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458e14      0x1ec 00

.rdata          0x00459000     0x29e0
 .rdata         0x00459000      0x4c0 builtins.o
 .rdata         0x004594c0       0x10 conio.o
 .rdata         0x004594d0      0x460 stdlib.o
 .rdata         0x00459930       0x40 stdio.o
 .rdata         0x00459970      0x320 api.o
 .rdata         0x00459c90      0x720 shellui.o
 .rdata         0x0045a3b0     0x1580 main.o
 .rdata         0x0045b930       0xb0 crt0.o

.data           0x0045b9e0     0x1620
                0x0045b9e0                data = .
                0x0045b9e0                _data = .
                0x0045b9e0                __data = .
 *(.data)
 .data          0x0045b9e0       0x30 crt0.o
 .data          0x0045ba10      0x4e0 main.o
                0x0045bed0                running
                0x0045bed4                primary_prompt
                0x0045bedc                shell_config_file
                0x0045bed8                secondary_prompt
 .data          0x0045bef0      0x4c0 shellui.o
 .data          0x0045c3b0      0x440 api.o
 .data          0x0045c7f0        0x0 stdio.o
 .data          0x0045c7f0       0x10 stdlib.o
 .data          0x0045c800        0x0 string.o
 .data          0x0045c800        0x0 conio.o
 .data          0x0045c800      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045ccc0      0x340 00

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
