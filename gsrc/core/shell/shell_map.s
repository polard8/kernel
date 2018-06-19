
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
 .text          0x004510a4     0x37a0 main.o
                0x00453286                shellPrompt
                0x00454794                shell_print_tokenList
                0x00453c3c                shellSendMessage
                0x00453476                shellTestThreads
                0x00453da4                shellTaskList
                0x004512f4                shellProcedure
                0x00452c1b                shellShell
                0x00454073                shellShowProcessHeapPointer
                0x004531e5                shellThread
                0x00454480                concat
                0x00452d78                shellInit
                0x00453f0b                shellShowPPID
                0x004540db                shellShowKernelHeapPointer
                0x00453d01                shellInitializeWorkingDiretoryString
                0x004515b7                shellWaitCmd
                0x0045334b                shellShowScreenBuffer
                0x00454716                shell_pathname_backup
                0x004510b3                GramadoMain
                0x004546cb                shellInitFilename
                0x00454037                shellShowDesktopID
                0x0045374f                shellInsertCharXY
                0x00454680                shellInitPathname
                0x00453799                shellInsertCharPos
                0x00454414                die
                0x004541a7                shellShowPCIInfo
                0x00453c8d                shellExit
                0x004515cf                shellCompare
                0x00453309                shellClearBuffer
                0x004545fa                absolute_pathname
                0x00453541                shellRefreshScreen
                0x00454358                feedterminalDialog
                0x0045455f                shellExecuteThisScript
                0x00453507                shellClearScreen
                0x00453b0b                shellShowSystemInfo
                0x004537d1                shellInsertNextChar
                0x004541ff                shell_fntos
                0x0045417b                shellShowMemoryInfo
                0x004533aa                shellTestLoadFile
                0x00453948                move_to
                0x0045381a                shellInsertCR
                0x00453a37                shellShowMetrics
                0x00453f83                shellShowGID
                0x004535c3                shellScroll
                0x004541d3                shellShowKernelInfo
                0x00453c9e                shellUpdateWorkingDiretoryString
                0x0045389a                shellInsertNullTerminator
                0x00453f47                shellShowUID
                0x0045385a                shellInsertLF
                0x00453d97                shellUpdateCurrentDirectoryID
                0x00453c64                shell_memcpy_bytes
                0x004531bb                shellSetCursor
                0x004542ee                shell_gramado_core_init_execve
                0x0045396d                shellShowInfo
                0x0045414f                shellShowVolumeInfo
                0x00453b79                shellShowWindowInfo
                0x004510a4                quit
                0x00453ecf                shellShowPID
                0x00454518                error
                0x00453fbf                shellShowUserSessionID
                0x00453ffb                shellShowWindowStationID
                0x00454455                xmalloc
                0x00454123                shellShowDiskInfo
                0x00453272                shellTree
                0x0045325e                shellHelp
                0x004538da                shellTestMBR
 .text          0x00454844      0x7b0 shellui.o
                0x00454e40                shellTestDisplayBMP
                0x00454aa0                shellCreateEditBox
                0x00454dcb                shellDisplayBMP
                0x00454933                shellTopbarProcedure
                0x00454eb6                bmpDisplayBMP
                0x00454b4e                shellCreateTopBar
                0x00454844                shellui_fntos
 .text          0x00454ff4     0x19a0 api.o
                0x00455da9                APIShowCurrentProcessInfo
                0x00456596                api_getchar
                0x00455596                system11
                0x0045563b                refresh_buffer
                0x00455c8b                APISetFocus
                0x004555f9                system14
                0x00455920                apiInitBackground
                0x00455b5f                APICreateWindow
                0x00456351                apiBeginPaint
                0x00455925                MessageBox
                0x00455e27                APIreplace_window
                0x00456398                apiGetSystemMetrics
                0x004555d8                system13
                0x00456208                apiDown
                0x00455f20                apiExit
                0x004562a0                enterCriticalSection
                0x004564dd                gramadocore_init_execve
                0x0045618e                apiFOpen
                0x0045544c                system1
                0x004554d0                system5
                0x00456006                api_refresh_screen
                0x0045651d                apiDialog
                0x00456092                apiGetCursorY
                0x004558cb                carrega_bitmap_16x16
                0x004562f9                exitCriticalSection
                0x00454ff4                system_call
                0x00456254                apiUp
                0x0045501c                apiSystem
                0x004564b1                api_get_window_with_text_input
                0x0045561a                system15
                0x00455d3b                APISetActiveWindow
                0x004560ea                apiSetClientAreaRect
                0x00455dfe                APIredraw_window
                0x0045613c                apiCreateThread
                0x00455867                SetNextWindowProcedure
                0x00456066                apiGetCursorX
                0x00455837                chama_procedimento
                0x0045594e                call_kernel
                0x00455c07                APIRegisterWindow
                0x00455f7c                api_strncmp
                0x00455e79                APIminimize_window
                0x0045546d                system2
                0x0045548e                system3
                0x004563ea                api_get_current_keyboard_responder
                0x00456113                apiCreateProcess
                0x00455ccd                APIGetFocus
                0x00455512                system7
                0x004554f1                system6
                0x0045638e                apiDefDialog
                0x00455c49                APICloseWindow
                0x00456325                initializeCriticalSection
                0x00455575                system10
                0x00455897                set_cursor
                0x00455e50                APImaximize_window
                0x00456513                execve
                0x00455fda                refresh_screen
                0x004565c2                apiDisplayBMP
                0x00455ace                call_gui
                0x00455554                system9
                0x004564e7                fork
                0x004563c1                api_set_current_keyboard_responder
                0x00455dd5                APIresize_window
                0x0045635b                apiEndPaint
                0x004558c6                put_char
                0x004557d2                print_string
                0x004560be                apiGetClientAreaRect
                0x00455808                edit_box
                0x00455f4b                kill
                0x00456010                apiReboot
                0x004558f4                apiShutDown
                0x00456416                api_set_current_mouse_responder
                0x00455ecb                APIget_foregroung_window
                0x004554af                system4
                0x004561c8                apiSaveFile
                0x0045603c                apiSetCursor
                0x004555b7                system12
                0x004557d7                vsync
                0x00455533                system8
                0x0045646b                api_set_window_with_text_input
                0x00455d7d                APIGetActiveWindow
                0x00455ea2                APIupdate_window
                0x0045643f                api_get_current_mouse_responder
                0x00455f50                dead_thread_collector
                0x00456165                apiStartThread
                0x00455cf9                APIKillFocus
                0x00455ef7                APIset_foregroung_window
                0x00456365                apiPutChar
 .text          0x00456994     0x1110 stdio.o
                0x004572db                putchar
                0x00456994                stdio_fntos
                0x00457297                sprintf
                0x0045796c                feof
                0x00457a4a                fputc
                0x00457821                fputs
                0x004579aa                ferror
                0x004574c7                input
                0x00456b81                scroll
                0x004574bd                printf_main
                0x00457896                gets
                0x00457307                outbyte
                0x00456d2b                app_print
                0x0045773c                fflush
                0x004577ac                fprintf
                0x004575be                stdio_system_call
                0x00456ae9                fopen
                0x004575e6                getchar
                0x00457618                stdioInitialize
                0x0045790b                fgetc
                0x00456a83                fclose
                0x004579d0                fseek
                0x0045748a                _outbyte
                0x0045727c                printf
                0x00456cbf                app_clear
 .text          0x00457aa4      0xae0 stdlib.o
                0x00457d9a                FreeHeap
                0x00457acc                rtGetHeapStart
                0x00457fe1                free
                0x00457aa4                stdlib_system_call
                0x00457f83                rand
                0x00457efa                stdlibInitMM
                0x00457da4                heapInit
                0x00458479                __findenv
                0x00457ae0                rtGetHeapPointer
                0x00457aea                rtGetAvailableHeap
                0x00457f5a                libcInitRT
                0x00457af4                heapSetLibcHeap
                0x00458544                getenv
                0x00457fa0                malloc
                0x00457d87                AllocateHeapEx
                0x00457b9b                AllocateHeap
                0x004583f2                stdlib_strncmp
                0x00458450                exit
                0x00457ad6                rtGetHeapEnd
                0x00457fe6                system
 .text          0x00458584      0x4a0 string.o
                0x004587eb                strcspn
                0x0045874e                strcat
                0x00458584                strcmp
                0x004587a5                bzero
                0x0045892b                strtok_r
                0x004586e1                memcpy
                0x004586b8                memoryZeroMemory
                0x0045877e                bcopy
                0x0045871e                strcpy
                0x0045888b                strspn
                0x00458a00                strtok
                0x0045863d                str_cmp
                0x004585df                strncmp
                0x004587c0                strlen
 .text          0x00458a24       0x90 conio.o
                0x00458a92                getche
                0x00458a24                putch
                0x00458a47                cputs
                0x00458a7b                getch
 .text          0x00458ab4      0x1a0 builtins.o
                0x00458c1f                pwd_builtins
                0x00458bb9                getuid_builtins
                0x00458bcb                getgid_builtins
                0x00458b3c                echo_builtins
                0x00458af8                dir_builtins
                0x00458b6b                exit_builtins
                0x00458b95                getpid_builtins
                0x00458ae9                copy_builtins
                0x00458ba7                getppid_builtins
                0x00458b57                exec_builtins
                0x00458ac8                cls_builtins
                0x00458aee                date_builtins
                0x00458af3                del_builtins
                0x00458ab4                cd_buitins
                0x00458bdd                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458c54      0x3ac 00

.rdata          0x00459000     0x2940
 .rdata         0x00459000      0x4c0 builtins.o
 .rdata         0x004594c0       0x10 conio.o
 .rdata         0x004594d0      0x460 stdlib.o
 .rdata         0x00459930       0x40 stdio.o
 .rdata         0x00459970      0x320 api.o
 .rdata         0x00459c90      0x720 shellui.o
 .rdata         0x0045a3b0     0x14e0 main.o
 .rdata         0x0045b890       0xb0 crt0.o

.data           0x0045b940     0x16c0
                0x0045b940                data = .
                0x0045b940                _data = .
                0x0045b940                __data = .
 *(.data)
 .data          0x0045b940       0x30 crt0.o
 .data          0x0045b970      0x4e0 main.o
                0x0045be30                running
                0x0045be34                primary_prompt
                0x0045be3c                shell_config_file
                0x0045be38                secondary_prompt
 .data          0x0045be50      0x4c0 shellui.o
 .data          0x0045c310      0x440 api.o
 .data          0x0045c750        0x0 stdio.o
 .data          0x0045c750       0x10 stdlib.o
 .data          0x0045c760        0x0 string.o
 .data          0x0045c760        0x0 conio.o
 .data          0x0045c760      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cc20      0x3e0 00

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
