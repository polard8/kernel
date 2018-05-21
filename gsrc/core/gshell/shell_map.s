
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
 .text          0x004510a4     0x2e10 main.o
                0x00452d19                shellPrompt
                0x004535fb                shellSendMessage
                0x00452eea                shellTestThreads
                0x004536d9                shellTaskList
                0x004513d7                shellProcedure
                0x00452726                shellShell
                0x004539a8                shellShowProcessHeapPointer
                0x00452cd8                shellThread
                0x00453d69                concat
                0x0045286b                shellInit
                0x00453840                shellShowPPID
                0x00453a10                shellShowKernelHeapPointer
                0x004515ec                shellWaitCmd
                0x00452dd2                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x0045396c                shellShowDesktopID
                0x0045317a                shellInsertCharXY
                0x004531c4                shellInsertCharPos
                0x00453cfd                die
                0x00453a84                shellShowPCIInfo
                0x00451604                shellCompare
                0x00452d90                shellClearBuffer
                0x00452fc0                shellRefreshScreen
                0x00453c41                feedterminalDialog
                0x00453e48                shellExecuteThisScript
                0x00452f7a                shellClearScreen
                0x004534e2                shellShowSystemInfo
                0x004531fc                shellInsertNextChar
                0x00453adc                shell_fntos
                0x00453a58                shellShowMemoryInfo
                0x00452e57                shellTestLoadFile
                0x004532f3                move_to
                0x00453228                shellInsertCR
                0x004533e2                shellShowMetrics
                0x004538b8                shellShowGID
                0x0045304e                shellScroll
                0x00453ab0                shellShowKernelInfo
                0x0045364c                shellUpdateWorkingDiretoryString
                0x00453266                shellInsertNullTerminator
                0x0045387c                shellShowUID
                0x00453247                shellInsertLF
                0x004536cc                shellUpdateCurrentDirectoryID
                0x00453623                shell_memcpy_bytes
                0x00452cae                shellSetCursor
                0x00453bcb                shell_gramado_core_init_execve
                0x00453318                shellShowInfo
                0x00453550                shellShowWindowInfo
                0x004510a4                quit
                0x00453804                shellShowPID
                0x00453e01                error
                0x004538f4                shellShowUserSessionID
                0x00453930                shellShowWindowStationID
                0x00453d3e                xmalloc
                0x00452d05                shellTree
                0x00452cf1                shellHelp
                0x00453285                shellTestMBR
 .text          0x00453eb4      0x7b0 shellui.o
                0x004544b0                shellTestDisplayBMP
                0x00454110                shellCreateEditBox
                0x0045443b                shellDisplayBMP
                0x00453fa3                shellTopbarProcedure
                0x00454526                bmpDisplayBMP
                0x004541be                shellCreateTopBar
                0x00453eb4                shellui_fntos
 .text          0x00454664     0x1910 api.o
                0x00455419                APIShowCurrentProcessInfo
                0x00455b6b                api_getchar
                0x00454c06                system11
                0x00454cab                refresh_buffer
                0x004552fb                APISetFocus
                0x00454c69                system14
                0x00454f90                apiInitBackground
                0x004551cf                APICreateWindow
                0x00455948                apiBeginPaint
                0x00454f95                MessageBox
                0x00455497                APIreplace_window
                0x0045598f                apiGetSystemMetrics
                0x00454c48                system13
                0x004557ff                apiDown
                0x00455567                apiExit
                0x00455897                enterCriticalSection
                0x00455ad4                gramadocore_init_execve
                0x004557d5                apiFOpen
                0x00454abc                system1
                0x00454b40                system5
                0x0045564d                api_refresh_screen
                0x00455af2                apiDialog
                0x004556d9                apiGetCursorY
                0x00454f3b                carrega_bitmap_16x16
                0x004558f0                exitCriticalSection
                0x00454664                system_call
                0x0045584b                apiUp
                0x0045468c                apiSystem
                0x00455aa8                api_get_window_with_text_input
                0x00454c8a                system15
                0x004553ab                APISetActiveWindow
                0x00455731                apiSetClientAreaRect
                0x0045546e                APIredraw_window
                0x00455783                apiCreateThread
                0x00454ed7                SetNextWindowProcedure
                0x004556ad                apiGetCursorX
                0x00454ea7                chama_procedimento
                0x00454fbe                call_kernel
                0x00455277                APIRegisterWindow
                0x004555c3                api_strncmp
                0x004554e9                APIminimize_window
                0x00454add                system2
                0x00454afe                system3
                0x004559e1                api_get_current_keyboard_responder
                0x0045575a                apiCreateProcess
                0x0045533d                APIGetFocus
                0x00454b82                system7
                0x00454b61                system6
                0x00455985                apiDefDialog
                0x004552b9                APICloseWindow
                0x0045591c                initializeCriticalSection
                0x00454be5                system10
                0x00454f07                set_cursor
                0x004554c0                APImaximize_window
                0x00455ae8                execve
                0x00455621                refresh_screen
                0x00455b97                apiDisplayBMP
                0x0045513e                call_gui
                0x00454bc4                system9
                0x00455ade                fork
                0x004559b8                api_set_current_keyboard_responder
                0x00455445                APIresize_window
                0x00455952                apiEndPaint
                0x00454f36                put_char
                0x00454e42                print_string
                0x00455705                apiGetClientAreaRect
                0x00454e78                edit_box
                0x00455592                kill
                0x00455657                apiReboot
                0x00454f64                apiShutDown
                0x00455a0d                api_set_current_mouse_responder
                0x00455512                APIget_foregroung_window
                0x00454b1f                system4
                0x00455683                apiSetCursor
                0x00454c27                system12
                0x00454e47                vsync
                0x00454ba3                system8
                0x00455a62                api_set_window_with_text_input
                0x004553ed                APIGetActiveWindow
                0x00455a36                api_get_current_mouse_responder
                0x00455597                dead_thread_collector
                0x004557ac                apiStartThread
                0x00455369                APIKillFocus
                0x0045553e                APIset_foregroung_window
                0x0045595c                apiPutChar
 .text          0x00455f74     0x1110 stdio.o
                0x004568bb                putchar
                0x00455f74                stdio_fntos
                0x00456877                sprintf
                0x00456f4c                feof
                0x0045702a                fputc
                0x00456e01                fputs
                0x00456f8a                ferror
                0x00456aa7                input
                0x00456161                scroll
                0x00456a9d                printf_main
                0x00456e76                gets
                0x004568e7                outbyte
                0x0045630b                app_print
                0x00456d1c                fflush
                0x00456d8c                fprintf
                0x00456b9e                stdio_system_call
                0x004560c9                fopen
                0x00456bc6                getchar
                0x00456bf8                stdioInitialize
                0x00456eeb                fgetc
                0x00456063                fclose
                0x00456fb0                fseek
                0x00456a6a                _outbyte
                0x0045685c                printf
                0x0045629f                app_clear
 .text          0x00457084      0x9b0 stdlib.o
                0x00457367                FreeHeap
                0x004570ac                rtGetHeapStart
                0x004575ae                free
                0x00457084                stdlib_system_call
                0x00457550                rand
                0x004574c7                stdlibInitMM
                0x00457371                heapInit
                0x004570c0                rtGetHeapPointer
                0x004570ca                rtGetAvailableHeap
                0x00457527                libcInitRT
                0x004570d4                heapSetLibcHeap
                0x0045756d                malloc
                0x00457354                AllocateHeapEx
                0x0045717b                AllocateHeap
                0x004579a5                stdlib_strncmp
                0x00457a03                exit
                0x004570b6                rtGetHeapEnd
                0x004575b3                system
 .text          0x00457a34      0x4a0 string.o
                0x00457c9b                strcspn
                0x00457bfe                strcat
                0x00457a34                strcmp
                0x00457c55                bzero
                0x00457ddb                strtok_r
                0x00457b91                memcpy
                0x00457b68                memoryZeroMemory
                0x00457c2e                bcopy
                0x00457bce                strcpy
                0x00457d3b                strspn
                0x00457eb0                strtok
                0x00457aed                str_cmp
                0x00457a8f                strncmp
                0x00457c70                strlen
 .text          0x00457ed4       0x90 conio.o
                0x00457f42                getche
                0x00457ed4                putch
                0x00457ef7                cputs
                0x00457f2b                getch
 .text          0x00457f64      0x1b0 builtins.o
                0x004580ce                pwd_builtins
                0x00458068                getuid_builtins
                0x0045807a                getgid_builtins
                0x00457ff1                echo_builtins
                0x00457fad                dir_builtins
                0x00458024                exit_builtins
                0x00458044                getpid_builtins
                0x00457f9e                copy_builtins
                0x00458056                getppid_builtins
                0x00458010                exec_builtins
                0x00457f78                cls_builtins
                0x00457fa3                date_builtins
                0x00457fa8                del_builtins
                0x00457f64                cd_buitins
                0x0045808c                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458114      0xeec 00

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
 .data          0x0045b700      0x460 main.o
                0x0045bb58                running
                0x0045bb5c                shell_config_file
 .data          0x0045bb60      0x460 shellui.o
 .data          0x0045bfc0      0x440 api.o
 .data          0x0045c400        0x0 stdio.o
 .data          0x0045c400       0x10 stdlib.o
 .data          0x0045c410        0x0 string.o
 .data          0x0045c410        0x0 conio.o
 .data          0x0045c410      0x460 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045c870      0x790 00

.bss            0x0045d000     0xd910
                0x0045d000                bss = .
                0x0045d000                _bss = .
                0x0045d000                __bss = .
 *(.bss)
 .bss           0x0045d000        0x0 crt0.o
 .bss           0x0045d000       0xe0 main.o
                0x0045d008                interactive
                0x0045d004                login_shell
                0x0045d000                quiet
                0x0045d00c                ShellFlag
 .bss           0x0045d0e0       0xd0 shellui.o
 .bss           0x0045d1b0       0x40 api.o
 .bss           0x0045d1f0       0x10 stdio.o
 .bss           0x0045d200     0x8000 stdlib.o
 .bss           0x00465200       0x10 string.o
 .bss           0x00465210        0x0 conio.o
 .bss           0x00465210       0xd0 builtins.o
                0x00466000                . = ALIGN (0x1000)
 *fill*         0x004652e0      0xd20 00
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
 COMMON         0x00466d40     0x32e0 main.o
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
                0x00468ef0                topbar_scrollbarWindow
                0x00468f00                current_semaphore
                0x00468f10                g_current_volume_id
                0x00468f20                ShellHook
                0x00468f30                topbar_checkboxWindow
                0x00468f40                shellScreenBufferMaxRows
                0x00468f50                shellScreenWidth
                0x00468f60                screen_buffer_pos
                0x00468f70                shellScreenHeight
                0x00468f80                editboxWindow
                0x00468f90                username
                0x00468fa0                screen_buffer_x
                0x00468fb0                screen_buffer
                0x00469f60                shell_window_y
                0x00469f70                terminal_rect
                0x00469f80                password
                0x00469f90                CursorInfo
                0x00469fa0                shellMaxColumns
                0x00469fb0                i1Window
                0x00469fc0                screen_buffer_y
                0x00469fd0                topbar_editboxWindow
                0x00469fe0                topbarWindow
                0x00469ff0                ApplicationInfo
                0x0046a000                current_workingdiretory_string
 COMMON         0x0046a020      0x8f0 stdlib.o
                0x0046a020                current_mmblock
                0x0046a030                mm_prev_pointer
                0x0046a040                heap_end
                0x0046a050                g_available_heap
                0x0046a060                heap_start
                0x0046a070                heapCount
                0x0046a080                HEAP_START
                0x0046a090                g_heap_pointer
                0x0046a0a0                heapList
                0x0046a4a0                HEAP_SIZE
                0x0046a4b0                last_size
                0x0046a4c0                last_valid
                0x0046a4d0                mmblockList
                0x0046a8d0                libcHeap
                0x0046a8e0                Heap
                0x0046a8f0                mmblockCount
                0x0046a900                HEAP_END
                0x0046a910                end = .
                0x0046a910                _end = .
                0x0046a910                __end = .
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
