
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
 .text          0x004510a4     0x3920 main.o
                0x0045330c                shellPrompt
                0x0045481a                shell_print_tokenList
                0x00453cc2                shellSendMessage
                0x004534fc                shellTestThreads
                0x00453e2a                shellTaskList
                0x00451300                shellProcedure
                0x00452ca1                shellShell
                0x004540f9                shellShowProcessHeapPointer
                0x0045326b                shellThread
                0x00454506                concat
                0x00452dfe                shellInit
                0x00453f91                shellShowPPID
                0x00454161                shellShowKernelHeapPointer
                0x00453d87                shellInitializeWorkingDiretoryString
                0x004515c3                shellWaitCmd
                0x004533d1                shellShowScreenBuffer
                0x0045479c                shell_pathname_backup
                0x004510b3                GramadoMain
                0x00454751                shellInitFilename
                0x004540bd                shellShowDesktopID
                0x004548c2                is_bin
                0x004537d5                shellInsertCharXY
                0x00454706                shellInitPathname
                0x0045381f                shellInsertCharPos
                0x0045449a                die
                0x0045422d                shellShowPCIInfo
                0x00453d13                shellExit
                0x004515db                shellCompare
                0x0045338f                shellClearBuffer
                0x00454680                absolute_pathname
                0x004535c7                shellRefreshScreen
                0x004543de                feedterminalDialog
                0x004545e5                shellExecuteThisScript
                0x0045358d                shellClearScreen
                0x00453b91                shellShowSystemInfo
                0x00453857                shellInsertNextChar
                0x00454285                shell_fntos
                0x00454201                shellShowMemoryInfo
                0x00453430                shellTestLoadFile
                0x004539ce                move_to
                0x004538a0                shellInsertCR
                0x00453abd                shellShowMetrics
                0x00454009                shellShowGID
                0x00453649                shellScroll
                0x00454259                shellShowKernelInfo
                0x00453d24                shellUpdateWorkingDiretoryString
                0x00453920                shellInsertNullTerminator
                0x00453fcd                shellShowUID
                0x004538e0                shellInsertLF
                0x00453e1d                shellUpdateCurrentDirectoryID
                0x00453cea                shell_memcpy_bytes
                0x00453241                shellSetCursor
                0x00454374                shell_gramado_core_init_execve
                0x00454943                is_sh1
                0x004539f3                shellShowInfo
                0x004541d5                shellShowVolumeInfo
                0x00453bff                shellShowWindowInfo
                0x004510a4                quit
                0x00453f55                shellShowPID
                0x0045459e                error
                0x00454045                shellShowUserSessionID
                0x00454081                shellShowWindowStationID
                0x004544db                xmalloc
                0x004541a9                shellShowDiskInfo
                0x004532f8                shellTree
                0x004532e4                shellHelp
                0x00453960                shellTestMBR
 .text          0x004549c4      0x7b0 shellui.o
                0x00454fc0                shellTestDisplayBMP
                0x00454c20                shellCreateEditBox
                0x00454f4b                shellDisplayBMP
                0x00454ab3                shellTopbarProcedure
                0x00455036                bmpDisplayBMP
                0x00454cce                shellCreateTopBar
                0x004549c4                shellui_fntos
 .text          0x00455174     0x1990 api.o
                0x00455f0d                APIShowCurrentProcessInfo
                0x004566fa                api_getchar
                0x00455716                system11
                0x004557bb                refresh_buffer
                0x00455def                APISetFocus
                0x00455779                system14
                0x00455aa0                apiInitBackground
                0x00455cdf                APICreateWindow
                0x004564b5                apiBeginPaint
                0x00455aa5                MessageBox
                0x00455f8b                APIreplace_window
                0x004564fc                apiGetSystemMetrics
                0x00455758                system13
                0x0045636c                apiDown
                0x00456084                apiExit
                0x00456404                enterCriticalSection
                0x00456641                gramadocore_init_execve
                0x004562f2                apiFOpen
                0x004555cc                system1
                0x00455650                system5
                0x0045616a                api_refresh_screen
                0x00456681                apiDialog
                0x004561f6                apiGetCursorY
                0x00455a4b                carrega_bitmap_16x16
                0x0045645d                exitCriticalSection
                0x00455174                system_call
                0x004563b8                apiUp
                0x0045519c                apiSystem
                0x00456615                api_get_window_with_text_input
                0x0045579a                system15
                0x00455e9f                APISetActiveWindow
                0x0045624e                apiSetClientAreaRect
                0x00455f62                APIredraw_window
                0x004562a0                apiCreateThread
                0x004559e7                SetNextWindowProcedure
                0x004561ca                apiGetCursorX
                0x004559b7                chama_procedimento
                0x00455ace                call_kernel
                0x00455d6b                APIRegisterWindow
                0x004560e0                api_strncmp
                0x00455fdd                APIminimize_window
                0x004555ed                system2
                0x0045560e                system3
                0x0045654e                api_get_current_keyboard_responder
                0x00456277                apiCreateProcess
                0x00455e31                APIGetFocus
                0x00455692                system7
                0x00455671                system6
                0x004564f2                apiDefDialog
                0x00455dad                APICloseWindow
                0x00456489                initializeCriticalSection
                0x004556f5                system10
                0x00455a17                set_cursor
                0x00455fb4                APImaximize_window
                0x00456677                execve
                0x0045613e                refresh_screen
                0x00456726                apiDisplayBMP
                0x00455c4e                call_gui
                0x004556d4                system9
                0x0045664b                fork
                0x00456525                api_set_current_keyboard_responder
                0x00455f39                APIresize_window
                0x004564bf                apiEndPaint
                0x00455a46                put_char
                0x00455952                print_string
                0x00456222                apiGetClientAreaRect
                0x00455988                edit_box
                0x004560af                kill
                0x00456174                apiReboot
                0x00455a74                apiShutDown
                0x0045657a                api_set_current_mouse_responder
                0x0045602f                APIget_foregroung_window
                0x0045562f                system4
                0x0045632c                apiSaveFile
                0x004561a0                apiSetCursor
                0x00455737                system12
                0x00455957                vsync
                0x004556b3                system8
                0x004565cf                api_set_window_with_text_input
                0x00455ee1                APIGetActiveWindow
                0x00456006                APIupdate_window
                0x004565a3                api_get_current_mouse_responder
                0x004560b4                dead_thread_collector
                0x004562c9                apiStartThread
                0x00455e5d                APIKillFocus
                0x0045605b                APIset_foregroung_window
                0x004564c9                apiPutChar
 .text          0x00456b04     0x1110 stdio.o
                0x0045744b                putchar
                0x00456b04                stdio_fntos
                0x00457407                sprintf
                0x00457adc                feof
                0x00457bba                fputc
                0x00457991                fputs
                0x00457b1a                ferror
                0x00457637                input
                0x00456cf1                scroll
                0x0045762d                printf_main
                0x00457a06                gets
                0x00457477                outbyte
                0x00456e9b                app_print
                0x004578ac                fflush
                0x0045791c                fprintf
                0x0045772e                stdio_system_call
                0x00456c59                fopen
                0x00457756                getchar
                0x00457788                stdioInitialize
                0x00457a7b                fgetc
                0x00456bf3                fclose
                0x00457b40                fseek
                0x004575fa                _outbyte
                0x004573ec                printf
                0x00456e2f                app_clear
 .text          0x00457c14      0xae0 stdlib.o
                0x00457f0a                FreeHeap
                0x00457c3c                rtGetHeapStart
                0x00458151                free
                0x00457c14                stdlib_system_call
                0x004580f3                rand
                0x0045806a                stdlibInitMM
                0x00457f14                heapInit
                0x004585e9                __findenv
                0x00457c50                rtGetHeapPointer
                0x00457c5a                rtGetAvailableHeap
                0x004580ca                libcInitRT
                0x00457c64                heapSetLibcHeap
                0x004586b4                getenv
                0x00458110                malloc
                0x00457ef7                AllocateHeapEx
                0x00457d0b                AllocateHeap
                0x00458562                stdlib_strncmp
                0x004585c0                exit
                0x00457c46                rtGetHeapEnd
                0x00458156                system
 .text          0x004586f4      0x4a0 string.o
                0x0045895b                strcspn
                0x004588be                strcat
                0x004586f4                strcmp
                0x00458915                bzero
                0x00458a9b                strtok_r
                0x00458851                memcpy
                0x00458828                memoryZeroMemory
                0x004588ee                bcopy
                0x0045888e                strcpy
                0x004589fb                strspn
                0x00458b70                strtok
                0x004587ad                str_cmp
                0x0045874f                strncmp
                0x00458930                strlen
 .text          0x00458b94       0x90 conio.o
                0x00458c02                getche
                0x00458b94                putch
                0x00458bb7                cputs
                0x00458beb                getch
 .text          0x00458c24      0x1a0 builtins.o
                0x00458d8f                pwd_builtins
                0x00458d29                getuid_builtins
                0x00458d3b                getgid_builtins
                0x00458cac                echo_builtins
                0x00458c68                dir_builtins
                0x00458cdb                exit_builtins
                0x00458d05                getpid_builtins
                0x00458c59                copy_builtins
                0x00458d17                getppid_builtins
                0x00458cc7                exec_builtins
                0x00458c38                cls_builtins
                0x00458c5e                date_builtins
                0x00458c63                del_builtins
                0x00458c24                cd_buitins
                0x00458d4d                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458dc4      0x23c 00

.rdata          0x00459000     0x29c0
 .rdata         0x00459000      0x4c0 builtins.o
 .rdata         0x004594c0       0x10 conio.o
 .rdata         0x004594d0      0x460 stdlib.o
 .rdata         0x00459930       0x40 stdio.o
 .rdata         0x00459970      0x320 api.o
 .rdata         0x00459c90      0x720 shellui.o
 .rdata         0x0045a3b0     0x1560 main.o
 .rdata         0x0045b910       0xb0 crt0.o

.data           0x0045b9c0     0x1640
                0x0045b9c0                data = .
                0x0045b9c0                _data = .
                0x0045b9c0                __data = .
 *(.data)
 .data          0x0045b9c0       0x30 crt0.o
 .data          0x0045b9f0      0x4e0 main.o
                0x0045beb0                running
                0x0045beb4                primary_prompt
                0x0045bebc                shell_config_file
                0x0045beb8                secondary_prompt
 .data          0x0045bed0      0x4c0 shellui.o
 .data          0x0045c390      0x440 api.o
 .data          0x0045c7d0        0x0 stdio.o
 .data          0x0045c7d0       0x10 stdlib.o
 .data          0x0045c7e0        0x0 string.o
 .data          0x0045c7e0        0x0 conio.o
 .data          0x0045c7e0      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cca0      0x360 00

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
