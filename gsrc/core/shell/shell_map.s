
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
current_connection  0x10              main.o
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
 .text          0x004510a4     0x33c0 main.o
                0x00453195                shellPrompt
                0x00453aa1                shellSendMessage
                0x00453328                shellTestThreads
                0x00453b7f                shellTaskList
                0x004513c3                shellProcedure
                0x00452b92                shellShell
                0x00453e4e                shellShowProcessHeapPointer
                0x00453154                shellThread
                0x0045425b                concat
                0x00452c97                shellInit
                0x00453ce6                shellShowPPID
                0x00453eb6                shellShowKernelHeapPointer
                0x004515d8                shellWaitCmd
                0x0045324e                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00453e12                shellShowDesktopID
                0x004535a0                shellInsertCharXY
                0x004535ea                shellInsertCharPos
                0x004541ef                die
                0x00453f82                shellShowPCIInfo
                0x004515f0                shellCompare
                0x0045320c                shellClearBuffer
                0x004543d5                absolute_pathname
                0x004533f2                shellRefreshScreen
                0x00454133                feedterminalDialog
                0x0045433a                shellExecuteThisScript
                0x004533b8                shellClearScreen
                0x0045397c                shellShowSystemInfo
                0x00453622                shellInsertNextChar
                0x00453fda                shell_fntos
                0x00453f56                shellShowMemoryInfo
                0x004532ad                shellTestLoadFile
                0x00453799                move_to
                0x0045366b                shellInsertCR
                0x00453888                shellShowMetrics
                0x00453d5e                shellShowGID
                0x00453474                shellScroll
                0x00453fae                shellShowKernelInfo
                0x00453af2                shellUpdateWorkingDiretoryString
                0x004536eb                shellInsertNullTerminator
                0x00453d22                shellShowUID
                0x004536ab                shellInsertLF
                0x00453b72                shellUpdateCurrentDirectoryID
                0x00453ac9                shell_memcpy_bytes
                0x0045312a                shellSetCursor
                0x004540c9                shell_gramado_core_init_execve
                0x004537be                shellShowInfo
                0x00453f2a                shellShowVolumeInfo
                0x004539ea                shellShowWindowInfo
                0x004510a4                quit
                0x00453caa                shellShowPID
                0x004542f3                error
                0x00453d9a                shellShowUserSessionID
                0x00453dd6                shellShowWindowStationID
                0x00454230                xmalloc
                0x00453efe                shellShowDiskInfo
                0x00453181                shellTree
                0x0045316d                shellHelp
                0x0045372b                shellTestMBR
 .text          0x00454464      0x7b0 shellui.o
                0x00454a60                shellTestDisplayBMP
                0x004546c0                shellCreateEditBox
                0x004549eb                shellDisplayBMP
                0x00454553                shellTopbarProcedure
                0x00454ad6                bmpDisplayBMP
                0x0045476e                shellCreateTopBar
                0x00454464                shellui_fntos
 .text          0x00454c14     0x1980 api.o
                0x004559c9                APIShowCurrentProcessInfo
                0x0045618d                api_getchar
                0x004551b6                system11
                0x0045525b                refresh_buffer
                0x004558ab                APISetFocus
                0x00455219                system14
                0x00455540                apiInitBackground
                0x0045577f                APICreateWindow
                0x00455f48                apiBeginPaint
                0x00455545                MessageBox
                0x00455a47                APIreplace_window
                0x00455f8f                apiGetSystemMetrics
                0x004551f8                system13
                0x00455dff                apiDown
                0x00455b17                apiExit
                0x00455e97                enterCriticalSection
                0x004560d4                gramadocore_init_execve
                0x00455d85                apiFOpen
                0x0045506c                system1
                0x004550f0                system5
                0x00455bfd                api_refresh_screen
                0x00456114                apiDialog
                0x00455c89                apiGetCursorY
                0x004554eb                carrega_bitmap_16x16
                0x00455ef0                exitCriticalSection
                0x00454c14                system_call
                0x00455e4b                apiUp
                0x00454c3c                apiSystem
                0x004560a8                api_get_window_with_text_input
                0x0045523a                system15
                0x0045595b                APISetActiveWindow
                0x00455ce1                apiSetClientAreaRect
                0x00455a1e                APIredraw_window
                0x00455d33                apiCreateThread
                0x00455487                SetNextWindowProcedure
                0x00455c5d                apiGetCursorX
                0x00455457                chama_procedimento
                0x0045556e                call_kernel
                0x00455827                APIRegisterWindow
                0x00455b73                api_strncmp
                0x00455a99                APIminimize_window
                0x0045508d                system2
                0x004550ae                system3
                0x00455fe1                api_get_current_keyboard_responder
                0x00455d0a                apiCreateProcess
                0x004558ed                APIGetFocus
                0x00455132                system7
                0x00455111                system6
                0x00455f85                apiDefDialog
                0x00455869                APICloseWindow
                0x00455f1c                initializeCriticalSection
                0x00455195                system10
                0x004554b7                set_cursor
                0x00455a70                APImaximize_window
                0x0045610a                execve
                0x00455bd1                refresh_screen
                0x004561b9                apiDisplayBMP
                0x004556ee                call_gui
                0x00455174                system9
                0x004560de                fork
                0x00455fb8                api_set_current_keyboard_responder
                0x004559f5                APIresize_window
                0x00455f52                apiEndPaint
                0x004554e6                put_char
                0x004553f2                print_string
                0x00455cb5                apiGetClientAreaRect
                0x00455428                edit_box
                0x00455b42                kill
                0x00455c07                apiReboot
                0x00455514                apiShutDown
                0x0045600d                api_set_current_mouse_responder
                0x00455ac2                APIget_foregroung_window
                0x004550cf                system4
                0x00455dbf                apiSaveFile
                0x00455c33                apiSetCursor
                0x004551d7                system12
                0x004553f7                vsync
                0x00455153                system8
                0x00456062                api_set_window_with_text_input
                0x0045599d                APIGetActiveWindow
                0x00456036                api_get_current_mouse_responder
                0x00455b47                dead_thread_collector
                0x00455d5c                apiStartThread
                0x00455919                APIKillFocus
                0x00455aee                APIset_foregroung_window
                0x00455f5c                apiPutChar
 .text          0x00456594     0x1110 stdio.o
                0x00456edb                putchar
                0x00456594                stdio_fntos
                0x00456e97                sprintf
                0x0045756c                feof
                0x0045764a                fputc
                0x00457421                fputs
                0x004575aa                ferror
                0x004570c7                input
                0x00456781                scroll
                0x004570bd                printf_main
                0x00457496                gets
                0x00456f07                outbyte
                0x0045692b                app_print
                0x0045733c                fflush
                0x004573ac                fprintf
                0x004571be                stdio_system_call
                0x004566e9                fopen
                0x004571e6                getchar
                0x00457218                stdioInitialize
                0x0045750b                fgetc
                0x00456683                fclose
                0x004575d0                fseek
                0x0045708a                _outbyte
                0x00456e7c                printf
                0x004568bf                app_clear
 .text          0x004576a4      0x9b0 stdlib.o
                0x00457987                FreeHeap
                0x004576cc                rtGetHeapStart
                0x00457bce                free
                0x004576a4                stdlib_system_call
                0x00457b70                rand
                0x00457ae7                stdlibInitMM
                0x00457991                heapInit
                0x004576e0                rtGetHeapPointer
                0x004576ea                rtGetAvailableHeap
                0x00457b47                libcInitRT
                0x004576f4                heapSetLibcHeap
                0x00457b8d                malloc
                0x00457974                AllocateHeapEx
                0x0045779b                AllocateHeap
                0x00457fc5                stdlib_strncmp
                0x00458023                exit
                0x004576d6                rtGetHeapEnd
                0x00457bd3                system
 .text          0x00458054      0x4a0 string.o
                0x004582bb                strcspn
                0x0045821e                strcat
                0x00458054                strcmp
                0x00458275                bzero
                0x004583fb                strtok_r
                0x004581b1                memcpy
                0x00458188                memoryZeroMemory
                0x0045824e                bcopy
                0x004581ee                strcpy
                0x0045835b                strspn
                0x004584d0                strtok
                0x0045810d                str_cmp
                0x004580af                strncmp
                0x00458290                strlen
 .text          0x004584f4       0x90 conio.o
                0x00458562                getche
                0x004584f4                putch
                0x00458517                cputs
                0x0045854b                getch
 .text          0x00458584      0x1a0 builtins.o
                0x004586e9                pwd_builtins
                0x00458683                getuid_builtins
                0x00458695                getgid_builtins
                0x0045860c                echo_builtins
                0x004585c8                dir_builtins
                0x0045863f                exit_builtins
                0x0045865f                getpid_builtins
                0x004585b9                copy_builtins
                0x00458671                getppid_builtins
                0x0045862b                exec_builtins
                0x00458598                cls_builtins
                0x004585be                date_builtins
                0x004585c3                del_builtins
                0x00458584                cd_buitins
                0x004586a7                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458724      0x8dc 00

.rdata          0x00459000     0x28d0
 .rdata         0x00459000      0x4e0 builtins.o
 .rdata         0x004594e0       0x10 conio.o
 .rdata         0x004594f0      0x430 stdlib.o
 .rdata         0x00459920       0x40 stdio.o
 .rdata         0x00459960      0x320 api.o
 .rdata         0x00459c80      0x720 shellui.o
 .rdata         0x0045a3a0     0x1480 main.o
 .rdata         0x0045b820       0xb0 crt0.o

.data           0x0045b8d0     0x1730
                0x0045b8d0                data = .
                0x0045b8d0                _data = .
                0x0045b8d0                __data = .
 *(.data)
 .data          0x0045b8d0       0x30 crt0.o
 .data          0x0045b900      0x4e0 main.o
                0x0045bdc0                running
                0x0045bdc4                primary_prompt
                0x0045bdcc                shell_config_file
                0x0045bdc8                secondary_prompt
 .data          0x0045bde0      0x4c0 shellui.o
 .data          0x0045c2a0      0x440 api.o
 .data          0x0045c6e0        0x0 stdio.o
 .data          0x0045c6e0       0x10 stdlib.o
 .data          0x0045c6f0        0x0 string.o
 .data          0x0045c6f0        0x0 conio.o
 .data          0x0045c6f0      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cbb0      0x450 00

.bss            0x0045d000     0xd950
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
 COMMON         0x00466d40     0x3320 main.o
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
                0x00468f10                current_connection
                0x00468f20                current_semaphore
                0x00468f30                g_current_volume_id
                0x00468f40                ShellHook
                0x00468f50                current_command
                0x00468f60                topbar_checkboxWindow
                0x00468f70                shellScreenBufferMaxRows
                0x00468f80                shellScreenWidth
                0x00468f90                screen_buffer_pos
                0x00468fa0                shellScreenHeight
                0x00468fb0                editboxWindow
                0x00468fc0                username
                0x00468fd0                screen_buffer_x
                0x00468fe0                screen_buffer
                0x00469f90                shell_window_y
                0x00469fa0                terminal_rect
                0x00469fb0                password
                0x00469fc0                CursorInfo
                0x00469fd0                shellMaxColumns
                0x00469fe0                i1Window
                0x00469ff0                screen_buffer_y
                0x0046a000                topbar_editboxWindow
                0x0046a010                topbarWindow
                0x0046a020                ApplicationInfo
                0x0046a030                shell_environment
                0x0046a040                current_workingdiretory_string
 COMMON         0x0046a060      0x8f0 stdlib.o
                0x0046a060                current_mmblock
                0x0046a070                mm_prev_pointer
                0x0046a080                heap_end
                0x0046a090                g_available_heap
                0x0046a0a0                heap_start
                0x0046a0b0                heapCount
                0x0046a0c0                HEAP_START
                0x0046a0d0                g_heap_pointer
                0x0046a0e0                heapList
                0x0046a4e0                HEAP_SIZE
                0x0046a4f0                last_size
                0x0046a500                last_valid
                0x0046a510                mmblockList
                0x0046a910                libcHeap
                0x0046a920                Heap
                0x0046a930                mmblockCount
                0x0046a940                HEAP_END
                0x0046a950                end = .
                0x0046a950                _end = .
                0x0046a950                __end = .
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
