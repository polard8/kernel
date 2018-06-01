
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
 .text          0x004510a4     0x3210 main.o
                0x0045306e                shellPrompt
                0x0045397a                shellSendMessage
                0x00453201                shellTestThreads
                0x00453a58                shellTaskList
                0x004513cb                shellProcedure
                0x004529e3                shellShell
                0x00453d27                shellShowProcessHeapPointer
                0x0045302d                shellThread
                0x00454134                concat
                0x00452ae8                shellInit
                0x00453bbf                shellShowPPID
                0x00453d8f                shellShowKernelHeapPointer
                0x004515e0                shellWaitCmd
                0x00453127                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00453ceb                shellShowDesktopID
                0x00453479                shellInsertCharXY
                0x004534c3                shellInsertCharPos
                0x004540c8                die
                0x00453e5b                shellShowPCIInfo
                0x004515f8                shellCompare
                0x004530e5                shellClearBuffer
                0x004532cb                shellRefreshScreen
                0x0045400c                feedterminalDialog
                0x00454213                shellExecuteThisScript
                0x00453291                shellClearScreen
                0x00453855                shellShowSystemInfo
                0x004534fb                shellInsertNextChar
                0x00453eb3                shell_fntos
                0x00453e2f                shellShowMemoryInfo
                0x00453186                shellTestLoadFile
                0x00453672                move_to
                0x00453544                shellInsertCR
                0x00453761                shellShowMetrics
                0x00453c37                shellShowGID
                0x0045334d                shellScroll
                0x00453e87                shellShowKernelInfo
                0x004539cb                shellUpdateWorkingDiretoryString
                0x004535c4                shellInsertNullTerminator
                0x00453bfb                shellShowUID
                0x00453584                shellInsertLF
                0x00453a4b                shellUpdateCurrentDirectoryID
                0x004539a2                shell_memcpy_bytes
                0x00453003                shellSetCursor
                0x00453fa2                shell_gramado_core_init_execve
                0x00453697                shellShowInfo
                0x00453e03                shellShowVolumeInfo
                0x004538c3                shellShowWindowInfo
                0x004510a4                quit
                0x00453b83                shellShowPID
                0x004541cc                error
                0x00453c73                shellShowUserSessionID
                0x00453caf                shellShowWindowStationID
                0x00454109                xmalloc
                0x00453dd7                shellShowDiskInfo
                0x0045305a                shellTree
                0x00453046                shellHelp
                0x00453604                shellTestMBR
 .text          0x004542b4      0x7b0 shellui.o
                0x004548b0                shellTestDisplayBMP
                0x00454510                shellCreateEditBox
                0x0045483b                shellDisplayBMP
                0x004543a3                shellTopbarProcedure
                0x00454926                bmpDisplayBMP
                0x004545be                shellCreateTopBar
                0x004542b4                shellui_fntos
 .text          0x00454a64     0x1960 api.o
                0x00455819                APIShowCurrentProcessInfo
                0x00455fbb                api_getchar
                0x00455006                system11
                0x004550ab                refresh_buffer
                0x004556fb                APISetFocus
                0x00455069                system14
                0x00455390                apiInitBackground
                0x004555cf                APICreateWindow
                0x00455d98                apiBeginPaint
                0x00455395                MessageBox
                0x00455897                APIreplace_window
                0x00455ddf                apiGetSystemMetrics
                0x00455048                system13
                0x00455c4f                apiDown
                0x00455967                apiExit
                0x00455ce7                enterCriticalSection
                0x00455f24                gramadocore_init_execve
                0x00455bd5                apiFOpen
                0x00454ebc                system1
                0x00454f40                system5
                0x00455a4d                api_refresh_screen
                0x00455f42                apiDialog
                0x00455ad9                apiGetCursorY
                0x0045533b                carrega_bitmap_16x16
                0x00455d40                exitCriticalSection
                0x00454a64                system_call
                0x00455c9b                apiUp
                0x00454a8c                apiSystem
                0x00455ef8                api_get_window_with_text_input
                0x0045508a                system15
                0x004557ab                APISetActiveWindow
                0x00455b31                apiSetClientAreaRect
                0x0045586e                APIredraw_window
                0x00455b83                apiCreateThread
                0x004552d7                SetNextWindowProcedure
                0x00455aad                apiGetCursorX
                0x004552a7                chama_procedimento
                0x004553be                call_kernel
                0x00455677                APIRegisterWindow
                0x004559c3                api_strncmp
                0x004558e9                APIminimize_window
                0x00454edd                system2
                0x00454efe                system3
                0x00455e31                api_get_current_keyboard_responder
                0x00455b5a                apiCreateProcess
                0x0045573d                APIGetFocus
                0x00454f82                system7
                0x00454f61                system6
                0x00455dd5                apiDefDialog
                0x004556b9                APICloseWindow
                0x00455d6c                initializeCriticalSection
                0x00454fe5                system10
                0x00455307                set_cursor
                0x004558c0                APImaximize_window
                0x00455f38                execve
                0x00455a21                refresh_screen
                0x00455fe7                apiDisplayBMP
                0x0045553e                call_gui
                0x00454fc4                system9
                0x00455f2e                fork
                0x00455e08                api_set_current_keyboard_responder
                0x00455845                APIresize_window
                0x00455da2                apiEndPaint
                0x00455336                put_char
                0x00455242                print_string
                0x00455b05                apiGetClientAreaRect
                0x00455278                edit_box
                0x00455992                kill
                0x00455a57                apiReboot
                0x00455364                apiShutDown
                0x00455e5d                api_set_current_mouse_responder
                0x00455912                APIget_foregroung_window
                0x00454f1f                system4
                0x00455c0f                apiSaveFile
                0x00455a83                apiSetCursor
                0x00455027                system12
                0x00455247                vsync
                0x00454fa3                system8
                0x00455eb2                api_set_window_with_text_input
                0x004557ed                APIGetActiveWindow
                0x00455e86                api_get_current_mouse_responder
                0x00455997                dead_thread_collector
                0x00455bac                apiStartThread
                0x00455769                APIKillFocus
                0x0045593e                APIset_foregroung_window
                0x00455dac                apiPutChar
 .text          0x004563c4     0x1110 stdio.o
                0x00456d0b                putchar
                0x004563c4                stdio_fntos
                0x00456cc7                sprintf
                0x0045739c                feof
                0x0045747a                fputc
                0x00457251                fputs
                0x004573da                ferror
                0x00456ef7                input
                0x004565b1                scroll
                0x00456eed                printf_main
                0x004572c6                gets
                0x00456d37                outbyte
                0x0045675b                app_print
                0x0045716c                fflush
                0x004571dc                fprintf
                0x00456fee                stdio_system_call
                0x00456519                fopen
                0x00457016                getchar
                0x00457048                stdioInitialize
                0x0045733b                fgetc
                0x004564b3                fclose
                0x00457400                fseek
                0x00456eba                _outbyte
                0x00456cac                printf
                0x004566ef                app_clear
 .text          0x004574d4      0x9b0 stdlib.o
                0x004577b7                FreeHeap
                0x004574fc                rtGetHeapStart
                0x004579fe                free
                0x004574d4                stdlib_system_call
                0x004579a0                rand
                0x00457917                stdlibInitMM
                0x004577c1                heapInit
                0x00457510                rtGetHeapPointer
                0x0045751a                rtGetAvailableHeap
                0x00457977                libcInitRT
                0x00457524                heapSetLibcHeap
                0x004579bd                malloc
                0x004577a4                AllocateHeapEx
                0x004575cb                AllocateHeap
                0x00457df5                stdlib_strncmp
                0x00457e53                exit
                0x00457506                rtGetHeapEnd
                0x00457a03                system
 .text          0x00457e84      0x4a0 string.o
                0x004580eb                strcspn
                0x0045804e                strcat
                0x00457e84                strcmp
                0x004580a5                bzero
                0x0045822b                strtok_r
                0x00457fe1                memcpy
                0x00457fb8                memoryZeroMemory
                0x0045807e                bcopy
                0x0045801e                strcpy
                0x0045818b                strspn
                0x00458300                strtok
                0x00457f3d                str_cmp
                0x00457edf                strncmp
                0x004580c0                strlen
 .text          0x00458324       0x90 conio.o
                0x00458392                getche
                0x00458324                putch
                0x00458347                cputs
                0x0045837b                getch
 .text          0x004583b4      0x1b0 builtins.o
                0x0045851e                pwd_builtins
                0x004584b8                getuid_builtins
                0x004584ca                getgid_builtins
                0x00458441                echo_builtins
                0x004583fd                dir_builtins
                0x00458474                exit_builtins
                0x00458494                getpid_builtins
                0x004583ee                copy_builtins
                0x004584a6                getppid_builtins
                0x00458460                exec_builtins
                0x004583c8                cls_builtins
                0x004583f3                date_builtins
                0x004583f8                del_builtins
                0x004583b4                cd_buitins
                0x004584dc                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458564      0xa9c 00

.rdata          0x00459000     0x2730
 .rdata         0x00459000      0x480 builtins.o
 .rdata         0x00459480       0x10 conio.o
 .rdata         0x00459490      0x430 stdlib.o
 .rdata         0x004598c0       0x40 stdio.o
 .rdata         0x00459900      0x320 api.o
 .rdata         0x00459c20      0x6c0 shellui.o
 .rdata         0x0045a2e0     0x13a0 main.o
 .rdata         0x0045b680       0xb0 crt0.o

.data           0x0045b730     0x18d0
                0x0045b730                data = .
                0x0045b730                _data = .
                0x0045b730                __data = .
 *(.data)
 .data          0x0045b730       0x30 crt0.o
 .data          0x0045b760      0x480 main.o
                0x0045bbc0                running
                0x0045bbc4                shell_config_file
 .data          0x0045bbe0      0x460 shellui.o
 .data          0x0045c040      0x440 api.o
 .data          0x0045c480        0x0 stdio.o
 .data          0x0045c480       0x10 stdlib.o
 .data          0x0045c490        0x0 string.o
 .data          0x0045c490        0x0 conio.o
 .data          0x0045c490      0x460 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045c8f0      0x710 00

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
