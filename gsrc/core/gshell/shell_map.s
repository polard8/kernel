
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
 .text          0x004510a4     0x30c0 main.o
                0x00452f1d                shellPrompt
                0x00453829                shellSendMessage
                0x004530b0                shellTestThreads
                0x00453907                shellTaskList
                0x004513cb                shellProcedure
                0x00452892                shellShell
                0x00453bd6                shellShowProcessHeapPointer
                0x00452edc                shellThread
                0x00453fe3                concat
                0x00452997                shellInit
                0x00453a6e                shellShowPPID
                0x00453c3e                shellShowKernelHeapPointer
                0x004515e0                shellWaitCmd
                0x00452fd6                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00453b9a                shellShowDesktopID
                0x00453328                shellInsertCharXY
                0x00453372                shellInsertCharPos
                0x00453f77                die
                0x00453d0a                shellShowPCIInfo
                0x004515f8                shellCompare
                0x00452f94                shellClearBuffer
                0x0045317a                shellRefreshScreen
                0x00453ebb                feedterminalDialog
                0x004540c2                shellExecuteThisScript
                0x00453140                shellClearScreen
                0x00453704                shellShowSystemInfo
                0x004533aa                shellInsertNextChar
                0x00453d62                shell_fntos
                0x00453cde                shellShowMemoryInfo
                0x00453035                shellTestLoadFile
                0x00453521                move_to
                0x004533f3                shellInsertCR
                0x00453610                shellShowMetrics
                0x00453ae6                shellShowGID
                0x004531fc                shellScroll
                0x00453d36                shellShowKernelInfo
                0x0045387a                shellUpdateWorkingDiretoryString
                0x00453473                shellInsertNullTerminator
                0x00453aaa                shellShowUID
                0x00453433                shellInsertLF
                0x004538fa                shellUpdateCurrentDirectoryID
                0x00453851                shell_memcpy_bytes
                0x00452eb2                shellSetCursor
                0x00453e51                shell_gramado_core_init_execve
                0x00453546                shellShowInfo
                0x00453cb2                shellShowVolumeInfo
                0x00453772                shellShowWindowInfo
                0x004510a4                quit
                0x00453a32                shellShowPID
                0x0045407b                error
                0x00453b22                shellShowUserSessionID
                0x00453b5e                shellShowWindowStationID
                0x00453fb8                xmalloc
                0x00453c86                shellShowDiskInfo
                0x00452f09                shellTree
                0x00452ef5                shellHelp
                0x004534b3                shellTestMBR
 .text          0x00454164      0x7b0 shellui.o
                0x00454760                shellTestDisplayBMP
                0x004543c0                shellCreateEditBox
                0x004546eb                shellDisplayBMP
                0x00454253                shellTopbarProcedure
                0x004547d6                bmpDisplayBMP
                0x0045446e                shellCreateTopBar
                0x00454164                shellui_fntos
 .text          0x00454914     0x1960 api.o
                0x004556c9                APIShowCurrentProcessInfo
                0x00455e6b                api_getchar
                0x00454eb6                system11
                0x00454f5b                refresh_buffer
                0x004555ab                APISetFocus
                0x00454f19                system14
                0x00455240                apiInitBackground
                0x0045547f                APICreateWindow
                0x00455c48                apiBeginPaint
                0x00455245                MessageBox
                0x00455747                APIreplace_window
                0x00455c8f                apiGetSystemMetrics
                0x00454ef8                system13
                0x00455aff                apiDown
                0x00455817                apiExit
                0x00455b97                enterCriticalSection
                0x00455dd4                gramadocore_init_execve
                0x00455a85                apiFOpen
                0x00454d6c                system1
                0x00454df0                system5
                0x004558fd                api_refresh_screen
                0x00455df2                apiDialog
                0x00455989                apiGetCursorY
                0x004551eb                carrega_bitmap_16x16
                0x00455bf0                exitCriticalSection
                0x00454914                system_call
                0x00455b4b                apiUp
                0x0045493c                apiSystem
                0x00455da8                api_get_window_with_text_input
                0x00454f3a                system15
                0x0045565b                APISetActiveWindow
                0x004559e1                apiSetClientAreaRect
                0x0045571e                APIredraw_window
                0x00455a33                apiCreateThread
                0x00455187                SetNextWindowProcedure
                0x0045595d                apiGetCursorX
                0x00455157                chama_procedimento
                0x0045526e                call_kernel
                0x00455527                APIRegisterWindow
                0x00455873                api_strncmp
                0x00455799                APIminimize_window
                0x00454d8d                system2
                0x00454dae                system3
                0x00455ce1                api_get_current_keyboard_responder
                0x00455a0a                apiCreateProcess
                0x004555ed                APIGetFocus
                0x00454e32                system7
                0x00454e11                system6
                0x00455c85                apiDefDialog
                0x00455569                APICloseWindow
                0x00455c1c                initializeCriticalSection
                0x00454e95                system10
                0x004551b7                set_cursor
                0x00455770                APImaximize_window
                0x00455de8                execve
                0x004558d1                refresh_screen
                0x00455e97                apiDisplayBMP
                0x004553ee                call_gui
                0x00454e74                system9
                0x00455dde                fork
                0x00455cb8                api_set_current_keyboard_responder
                0x004556f5                APIresize_window
                0x00455c52                apiEndPaint
                0x004551e6                put_char
                0x004550f2                print_string
                0x004559b5                apiGetClientAreaRect
                0x00455128                edit_box
                0x00455842                kill
                0x00455907                apiReboot
                0x00455214                apiShutDown
                0x00455d0d                api_set_current_mouse_responder
                0x004557c2                APIget_foregroung_window
                0x00454dcf                system4
                0x00455abf                apiSaveFile
                0x00455933                apiSetCursor
                0x00454ed7                system12
                0x004550f7                vsync
                0x00454e53                system8
                0x00455d62                api_set_window_with_text_input
                0x0045569d                APIGetActiveWindow
                0x00455d36                api_get_current_mouse_responder
                0x00455847                dead_thread_collector
                0x00455a5c                apiStartThread
                0x00455619                APIKillFocus
                0x004557ee                APIset_foregroung_window
                0x00455c5c                apiPutChar
 .text          0x00456274     0x1110 stdio.o
                0x00456bbb                putchar
                0x00456274                stdio_fntos
                0x00456b77                sprintf
                0x0045724c                feof
                0x0045732a                fputc
                0x00457101                fputs
                0x0045728a                ferror
                0x00456da7                input
                0x00456461                scroll
                0x00456d9d                printf_main
                0x00457176                gets
                0x00456be7                outbyte
                0x0045660b                app_print
                0x0045701c                fflush
                0x0045708c                fprintf
                0x00456e9e                stdio_system_call
                0x004563c9                fopen
                0x00456ec6                getchar
                0x00456ef8                stdioInitialize
                0x004571eb                fgetc
                0x00456363                fclose
                0x004572b0                fseek
                0x00456d6a                _outbyte
                0x00456b5c                printf
                0x0045659f                app_clear
 .text          0x00457384      0x9b0 stdlib.o
                0x00457667                FreeHeap
                0x004573ac                rtGetHeapStart
                0x004578ae                free
                0x00457384                stdlib_system_call
                0x00457850                rand
                0x004577c7                stdlibInitMM
                0x00457671                heapInit
                0x004573c0                rtGetHeapPointer
                0x004573ca                rtGetAvailableHeap
                0x00457827                libcInitRT
                0x004573d4                heapSetLibcHeap
                0x0045786d                malloc
                0x00457654                AllocateHeapEx
                0x0045747b                AllocateHeap
                0x00457ca5                stdlib_strncmp
                0x00457d03                exit
                0x004573b6                rtGetHeapEnd
                0x004578b3                system
 .text          0x00457d34      0x4a0 string.o
                0x00457f9b                strcspn
                0x00457efe                strcat
                0x00457d34                strcmp
                0x00457f55                bzero
                0x004580db                strtok_r
                0x00457e91                memcpy
                0x00457e68                memoryZeroMemory
                0x00457f2e                bcopy
                0x00457ece                strcpy
                0x0045803b                strspn
                0x004581b0                strtok
                0x00457ded                str_cmp
                0x00457d8f                strncmp
                0x00457f70                strlen
 .text          0x004581d4       0x90 conio.o
                0x00458242                getche
                0x004581d4                putch
                0x004581f7                cputs
                0x0045822b                getch
 .text          0x00458264      0x1b0 builtins.o
                0x004583ce                pwd_builtins
                0x00458368                getuid_builtins
                0x0045837a                getgid_builtins
                0x004582f1                echo_builtins
                0x004582ad                dir_builtins
                0x00458324                exit_builtins
                0x00458344                getpid_builtins
                0x0045829e                copy_builtins
                0x00458356                getppid_builtins
                0x00458310                exec_builtins
                0x00458278                cls_builtins
                0x004582a3                date_builtins
                0x004582a8                del_builtins
                0x00458264                cd_buitins
                0x0045838c                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458414      0xbec 00

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
