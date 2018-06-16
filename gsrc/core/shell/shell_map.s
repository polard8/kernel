
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
 .text          0x004510a4     0x3600 main.o
                0x0045318f                shellPrompt
                0x00453b44                shellSendMessage
                0x0045337f                shellTestThreads
                0x00453cac                shellTaskList
                0x004512f4                shellProcedure
                0x00452b84                shellShell
                0x00453f7b                shellShowProcessHeapPointer
                0x0045314e                shellThread
                0x00454388                concat
                0x00452ce1                shellInit
                0x00453e13                shellShowPPID
                0x00453fe3                shellShowKernelHeapPointer
                0x00453c09                shellInitializeWorkingDiretoryString
                0x00451549                shellWaitCmd
                0x00453254                shellShowScreenBuffer
                0x0045461e                shell_pathname_backup
                0x004510b3                GramadoMain
                0x004545d3                shellInitFilename
                0x00453f3f                shellShowDesktopID
                0x00453657                shellInsertCharXY
                0x00454588                shellInitPathname
                0x004536a1                shellInsertCharPos
                0x0045431c                die
                0x004540af                shellShowPCIInfo
                0x00453b95                shellExit
                0x00451561                shellCompare
                0x00453212                shellClearBuffer
                0x00454502                absolute_pathname
                0x00453449                shellRefreshScreen
                0x00454260                feedterminalDialog
                0x00454467                shellExecuteThisScript
                0x0045340f                shellClearScreen
                0x00453a13                shellShowSystemInfo
                0x004536d9                shellInsertNextChar
                0x00454107                shell_fntos
                0x00454083                shellShowMemoryInfo
                0x004532b3                shellTestLoadFile
                0x00453850                move_to
                0x00453722                shellInsertCR
                0x0045393f                shellShowMetrics
                0x00453e8b                shellShowGID
                0x004534cb                shellScroll
                0x004540db                shellShowKernelInfo
                0x00453ba6                shellUpdateWorkingDiretoryString
                0x004537a2                shellInsertNullTerminator
                0x00453e4f                shellShowUID
                0x00453762                shellInsertLF
                0x00453c9f                shellUpdateCurrentDirectoryID
                0x00453b6c                shell_memcpy_bytes
                0x00453124                shellSetCursor
                0x004541f6                shell_gramado_core_init_execve
                0x00453875                shellShowInfo
                0x00454057                shellShowVolumeInfo
                0x00453a81                shellShowWindowInfo
                0x004510a4                quit
                0x00453dd7                shellShowPID
                0x00454420                error
                0x00453ec7                shellShowUserSessionID
                0x00453f03                shellShowWindowStationID
                0x0045435d                xmalloc
                0x0045402b                shellShowDiskInfo
                0x0045317b                shellTree
                0x00453167                shellHelp
                0x004537e2                shellTestMBR
 .text          0x004546a4      0x7b0 shellui.o
                0x00454ca0                shellTestDisplayBMP
                0x00454900                shellCreateEditBox
                0x00454c2b                shellDisplayBMP
                0x00454793                shellTopbarProcedure
                0x00454d16                bmpDisplayBMP
                0x004549ae                shellCreateTopBar
                0x004546a4                shellui_fntos
 .text          0x00454e54     0x19a0 api.o
                0x00455c09                APIShowCurrentProcessInfo
                0x004563f6                api_getchar
                0x004553f6                system11
                0x0045549b                refresh_buffer
                0x00455aeb                APISetFocus
                0x00455459                system14
                0x00455780                apiInitBackground
                0x004559bf                APICreateWindow
                0x004561b1                apiBeginPaint
                0x00455785                MessageBox
                0x00455c87                APIreplace_window
                0x004561f8                apiGetSystemMetrics
                0x00455438                system13
                0x00456068                apiDown
                0x00455d80                apiExit
                0x00456100                enterCriticalSection
                0x0045633d                gramadocore_init_execve
                0x00455fee                apiFOpen
                0x004552ac                system1
                0x00455330                system5
                0x00455e66                api_refresh_screen
                0x0045637d                apiDialog
                0x00455ef2                apiGetCursorY
                0x0045572b                carrega_bitmap_16x16
                0x00456159                exitCriticalSection
                0x00454e54                system_call
                0x004560b4                apiUp
                0x00454e7c                apiSystem
                0x00456311                api_get_window_with_text_input
                0x0045547a                system15
                0x00455b9b                APISetActiveWindow
                0x00455f4a                apiSetClientAreaRect
                0x00455c5e                APIredraw_window
                0x00455f9c                apiCreateThread
                0x004556c7                SetNextWindowProcedure
                0x00455ec6                apiGetCursorX
                0x00455697                chama_procedimento
                0x004557ae                call_kernel
                0x00455a67                APIRegisterWindow
                0x00455ddc                api_strncmp
                0x00455cd9                APIminimize_window
                0x004552cd                system2
                0x004552ee                system3
                0x0045624a                api_get_current_keyboard_responder
                0x00455f73                apiCreateProcess
                0x00455b2d                APIGetFocus
                0x00455372                system7
                0x00455351                system6
                0x004561ee                apiDefDialog
                0x00455aa9                APICloseWindow
                0x00456185                initializeCriticalSection
                0x004553d5                system10
                0x004556f7                set_cursor
                0x00455cb0                APImaximize_window
                0x00456373                execve
                0x00455e3a                refresh_screen
                0x00456422                apiDisplayBMP
                0x0045592e                call_gui
                0x004553b4                system9
                0x00456347                fork
                0x00456221                api_set_current_keyboard_responder
                0x00455c35                APIresize_window
                0x004561bb                apiEndPaint
                0x00455726                put_char
                0x00455632                print_string
                0x00455f1e                apiGetClientAreaRect
                0x00455668                edit_box
                0x00455dab                kill
                0x00455e70                apiReboot
                0x00455754                apiShutDown
                0x00456276                api_set_current_mouse_responder
                0x00455d2b                APIget_foregroung_window
                0x0045530f                system4
                0x00456028                apiSaveFile
                0x00455e9c                apiSetCursor
                0x00455417                system12
                0x00455637                vsync
                0x00455393                system8
                0x004562cb                api_set_window_with_text_input
                0x00455bdd                APIGetActiveWindow
                0x00455d02                APIupdate_window
                0x0045629f                api_get_current_mouse_responder
                0x00455db0                dead_thread_collector
                0x00455fc5                apiStartThread
                0x00455b59                APIKillFocus
                0x00455d57                APIset_foregroung_window
                0x004561c5                apiPutChar
 .text          0x004567f4     0x1110 stdio.o
                0x0045713b                putchar
                0x004567f4                stdio_fntos
                0x004570f7                sprintf
                0x004577cc                feof
                0x004578aa                fputc
                0x00457681                fputs
                0x0045780a                ferror
                0x00457327                input
                0x004569e1                scroll
                0x0045731d                printf_main
                0x004576f6                gets
                0x00457167                outbyte
                0x00456b8b                app_print
                0x0045759c                fflush
                0x0045760c                fprintf
                0x0045741e                stdio_system_call
                0x00456949                fopen
                0x00457446                getchar
                0x00457478                stdioInitialize
                0x0045776b                fgetc
                0x004568e3                fclose
                0x00457830                fseek
                0x004572ea                _outbyte
                0x004570dc                printf
                0x00456b1f                app_clear
 .text          0x00457904      0xae0 stdlib.o
                0x00457bfa                FreeHeap
                0x0045792c                rtGetHeapStart
                0x00457e41                free
                0x00457904                stdlib_system_call
                0x00457de3                rand
                0x00457d5a                stdlibInitMM
                0x00457c04                heapInit
                0x004582d9                __findenv
                0x00457940                rtGetHeapPointer
                0x0045794a                rtGetAvailableHeap
                0x00457dba                libcInitRT
                0x00457954                heapSetLibcHeap
                0x004583a4                getenv
                0x00457e00                malloc
                0x00457be7                AllocateHeapEx
                0x004579fb                AllocateHeap
                0x00458252                stdlib_strncmp
                0x004582b0                exit
                0x00457936                rtGetHeapEnd
                0x00457e46                system
 .text          0x004583e4      0x4a0 string.o
                0x0045864b                strcspn
                0x004585ae                strcat
                0x004583e4                strcmp
                0x00458605                bzero
                0x0045878b                strtok_r
                0x00458541                memcpy
                0x00458518                memoryZeroMemory
                0x004585de                bcopy
                0x0045857e                strcpy
                0x004586eb                strspn
                0x00458860                strtok
                0x0045849d                str_cmp
                0x0045843f                strncmp
                0x00458620                strlen
 .text          0x00458884       0x90 conio.o
                0x004588f2                getche
                0x00458884                putch
                0x004588a7                cputs
                0x004588db                getch
 .text          0x00458914      0x1a0 builtins.o
                0x00458a79                pwd_builtins
                0x00458a13                getuid_builtins
                0x00458a25                getgid_builtins
                0x0045899c                echo_builtins
                0x00458958                dir_builtins
                0x004589cf                exit_builtins
                0x004589ef                getpid_builtins
                0x00458949                copy_builtins
                0x00458a01                getppid_builtins
                0x004589bb                exec_builtins
                0x00458928                cls_builtins
                0x0045894e                date_builtins
                0x00458953                del_builtins
                0x00458914                cd_buitins
                0x00458a37                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458ab4      0x54c 00

.rdata          0x00459000     0x2900
 .rdata         0x00459000      0x4e0 builtins.o
 .rdata         0x004594e0       0x10 conio.o
 .rdata         0x004594f0      0x460 stdlib.o
 .rdata         0x00459950       0x40 stdio.o
 .rdata         0x00459990      0x320 api.o
 .rdata         0x00459cb0      0x720 shellui.o
 .rdata         0x0045a3d0     0x1480 main.o
 .rdata         0x0045b850       0xb0 crt0.o

.data           0x0045b900     0x1700
                0x0045b900                data = .
                0x0045b900                _data = .
                0x0045b900                __data = .
 *(.data)
 .data          0x0045b900       0x30 crt0.o
 .data          0x0045b930      0x4e0 main.o
                0x0045bdf0                running
                0x0045bdf4                primary_prompt
                0x0045bdfc                shell_config_file
                0x0045bdf8                secondary_prompt
 .data          0x0045be10      0x4c0 shellui.o
 .data          0x0045c2d0      0x440 api.o
 .data          0x0045c710        0x0 stdio.o
 .data          0x0045c710       0x10 stdlib.o
 .data          0x0045c720        0x0 string.o
 .data          0x0045c720        0x0 conio.o
 .data          0x0045c720      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cbe0      0x420 00

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
