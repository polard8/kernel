
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
 .text          0x004510a4     0x35f0 main.o
                0x00453197                shellPrompt
                0x00453b40                shellSendMessage
                0x0045337b                shellTestThreads
                0x00453d22                shellTaskList
                0x004513c7                shellProcedure
                0x00452b90                shellShell
                0x00453ff1                shellShowProcessHeapPointer
                0x00453156                shellThread
                0x004543fe                concat
                0x00452ced                shellInit
                0x00453e89                shellShowPPID
                0x00454059                shellShowKernelHeapPointer
                0x00453c9d                shellInitializeWorkingDiretoryString
                0x004515dc                shellWaitCmd
                0x00453250                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00454649                shellInitFilename
                0x00453fb5                shellShowDesktopID
                0x00453653                shellInsertCharXY
                0x004545fe                shellInitPathname
                0x0045369d                shellInsertCharPos
                0x00454392                die
                0x00454125                shellShowPCIInfo
                0x00453b91                shellExit
                0x004515f4                shellCompare
                0x0045320e                shellClearBuffer
                0x00454578                absolute_pathname
                0x00453445                shellRefreshScreen
                0x004542d6                feedterminalDialog
                0x004544dd                shellExecuteThisScript
                0x0045340b                shellClearScreen
                0x00453a0f                shellShowSystemInfo
                0x004536d5                shellInsertNextChar
                0x0045417d                shell_fntos
                0x004540f9                shellShowMemoryInfo
                0x004532af                shellTestLoadFile
                0x0045384c                move_to
                0x0045371e                shellInsertCR
                0x0045393b                shellShowMetrics
                0x00453f01                shellShowGID
                0x004534c7                shellScroll
                0x00454151                shellShowKernelInfo
                0x00453ba2                shellUpdateWorkingDiretoryString
                0x0045379e                shellInsertNullTerminator
                0x00453ec5                shellShowUID
                0x0045375e                shellInsertLF
                0x00453d15                shellUpdateCurrentDirectoryID
                0x00453b68                shell_memcpy_bytes
                0x0045312c                shellSetCursor
                0x0045426c                shell_gramado_core_init_execve
                0x00453871                shellShowInfo
                0x004540cd                shellShowVolumeInfo
                0x00453a7d                shellShowWindowInfo
                0x004510a4                quit
                0x00453e4d                shellShowPID
                0x00454496                error
                0x00453f3d                shellShowUserSessionID
                0x00453f79                shellShowWindowStationID
                0x004543d3                xmalloc
                0x004540a1                shellShowDiskInfo
                0x00453183                shellTree
                0x0045316f                shellHelp
                0x004537de                shellTestMBR
 .text          0x00454694      0x7b0 shellui.o
                0x00454c90                shellTestDisplayBMP
                0x004548f0                shellCreateEditBox
                0x00454c1b                shellDisplayBMP
                0x00454783                shellTopbarProcedure
                0x00454d06                bmpDisplayBMP
                0x0045499e                shellCreateTopBar
                0x00454694                shellui_fntos
 .text          0x00454e44     0x1980 api.o
                0x00455bf9                APIShowCurrentProcessInfo
                0x004563bd                api_getchar
                0x004553e6                system11
                0x0045548b                refresh_buffer
                0x00455adb                APISetFocus
                0x00455449                system14
                0x00455770                apiInitBackground
                0x004559af                APICreateWindow
                0x00456178                apiBeginPaint
                0x00455775                MessageBox
                0x00455c77                APIreplace_window
                0x004561bf                apiGetSystemMetrics
                0x00455428                system13
                0x0045602f                apiDown
                0x00455d47                apiExit
                0x004560c7                enterCriticalSection
                0x00456304                gramadocore_init_execve
                0x00455fb5                apiFOpen
                0x0045529c                system1
                0x00455320                system5
                0x00455e2d                api_refresh_screen
                0x00456344                apiDialog
                0x00455eb9                apiGetCursorY
                0x0045571b                carrega_bitmap_16x16
                0x00456120                exitCriticalSection
                0x00454e44                system_call
                0x0045607b                apiUp
                0x00454e6c                apiSystem
                0x004562d8                api_get_window_with_text_input
                0x0045546a                system15
                0x00455b8b                APISetActiveWindow
                0x00455f11                apiSetClientAreaRect
                0x00455c4e                APIredraw_window
                0x00455f63                apiCreateThread
                0x004556b7                SetNextWindowProcedure
                0x00455e8d                apiGetCursorX
                0x00455687                chama_procedimento
                0x0045579e                call_kernel
                0x00455a57                APIRegisterWindow
                0x00455da3                api_strncmp
                0x00455cc9                APIminimize_window
                0x004552bd                system2
                0x004552de                system3
                0x00456211                api_get_current_keyboard_responder
                0x00455f3a                apiCreateProcess
                0x00455b1d                APIGetFocus
                0x00455362                system7
                0x00455341                system6
                0x004561b5                apiDefDialog
                0x00455a99                APICloseWindow
                0x0045614c                initializeCriticalSection
                0x004553c5                system10
                0x004556e7                set_cursor
                0x00455ca0                APImaximize_window
                0x0045633a                execve
                0x00455e01                refresh_screen
                0x004563e9                apiDisplayBMP
                0x0045591e                call_gui
                0x004553a4                system9
                0x0045630e                fork
                0x004561e8                api_set_current_keyboard_responder
                0x00455c25                APIresize_window
                0x00456182                apiEndPaint
                0x00455716                put_char
                0x00455622                print_string
                0x00455ee5                apiGetClientAreaRect
                0x00455658                edit_box
                0x00455d72                kill
                0x00455e37                apiReboot
                0x00455744                apiShutDown
                0x0045623d                api_set_current_mouse_responder
                0x00455cf2                APIget_foregroung_window
                0x004552ff                system4
                0x00455fef                apiSaveFile
                0x00455e63                apiSetCursor
                0x00455407                system12
                0x00455627                vsync
                0x00455383                system8
                0x00456292                api_set_window_with_text_input
                0x00455bcd                APIGetActiveWindow
                0x00456266                api_get_current_mouse_responder
                0x00455d77                dead_thread_collector
                0x00455f8c                apiStartThread
                0x00455b49                APIKillFocus
                0x00455d1e                APIset_foregroung_window
                0x0045618c                apiPutChar
 .text          0x004567c4     0x1110 stdio.o
                0x0045710b                putchar
                0x004567c4                stdio_fntos
                0x004570c7                sprintf
                0x0045779c                feof
                0x0045787a                fputc
                0x00457651                fputs
                0x004577da                ferror
                0x004572f7                input
                0x004569b1                scroll
                0x004572ed                printf_main
                0x004576c6                gets
                0x00457137                outbyte
                0x00456b5b                app_print
                0x0045756c                fflush
                0x004575dc                fprintf
                0x004573ee                stdio_system_call
                0x00456919                fopen
                0x00457416                getchar
                0x00457448                stdioInitialize
                0x0045773b                fgetc
                0x004568b3                fclose
                0x00457800                fseek
                0x004572ba                _outbyte
                0x004570ac                printf
                0x00456aef                app_clear
 .text          0x004578d4      0x9b0 stdlib.o
                0x00457bb7                FreeHeap
                0x004578fc                rtGetHeapStart
                0x00457dfe                free
                0x004578d4                stdlib_system_call
                0x00457da0                rand
                0x00457d17                stdlibInitMM
                0x00457bc1                heapInit
                0x00457910                rtGetHeapPointer
                0x0045791a                rtGetAvailableHeap
                0x00457d77                libcInitRT
                0x00457924                heapSetLibcHeap
                0x00457dbd                malloc
                0x00457ba4                AllocateHeapEx
                0x004579cb                AllocateHeap
                0x004581f5                stdlib_strncmp
                0x00458253                exit
                0x00457906                rtGetHeapEnd
                0x00457e03                system
 .text          0x00458284      0x4a0 string.o
                0x004584eb                strcspn
                0x0045844e                strcat
                0x00458284                strcmp
                0x004584a5                bzero
                0x0045862b                strtok_r
                0x004583e1                memcpy
                0x004583b8                memoryZeroMemory
                0x0045847e                bcopy
                0x0045841e                strcpy
                0x0045858b                strspn
                0x00458700                strtok
                0x0045833d                str_cmp
                0x004582df                strncmp
                0x004584c0                strlen
 .text          0x00458724       0x90 conio.o
                0x00458792                getche
                0x00458724                putch
                0x00458747                cputs
                0x0045877b                getch
 .text          0x004587b4      0x1a0 builtins.o
                0x00458919                pwd_builtins
                0x004588b3                getuid_builtins
                0x004588c5                getgid_builtins
                0x0045883c                echo_builtins
                0x004587f8                dir_builtins
                0x0045886f                exit_builtins
                0x0045888f                getpid_builtins
                0x004587e9                copy_builtins
                0x004588a1                getppid_builtins
                0x0045885b                exec_builtins
                0x004587c8                cls_builtins
                0x004587ee                date_builtins
                0x004587f3                del_builtins
                0x004587b4                cd_buitins
                0x004588d7                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458954      0x6ac 00

.rdata          0x00459000     0x2890
 .rdata         0x00459000      0x4e0 builtins.o
 .rdata         0x004594e0       0x10 conio.o
 .rdata         0x004594f0      0x430 stdlib.o
 .rdata         0x00459920       0x40 stdio.o
 .rdata         0x00459960      0x320 api.o
 .rdata         0x00459c80      0x720 shellui.o
 .rdata         0x0045a3a0     0x1440 main.o
 .rdata         0x0045b7e0       0xb0 crt0.o

.data           0x0045b890     0x1770
                0x0045b890                data = .
                0x0045b890                _data = .
                0x0045b890                __data = .
 *(.data)
 .data          0x0045b890       0x30 crt0.o
 .data          0x0045b8c0      0x4e0 main.o
                0x0045bd80                running
                0x0045bd84                primary_prompt
                0x0045bd8c                shell_config_file
                0x0045bd88                secondary_prompt
 .data          0x0045bda0      0x4c0 shellui.o
 .data          0x0045c260      0x440 api.o
 .data          0x0045c6a0        0x0 stdio.o
 .data          0x0045c6a0       0x10 stdlib.o
 .data          0x0045c6b0        0x0 string.o
 .data          0x0045c6b0        0x0 conio.o
 .data          0x0045c6b0      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cb70      0x490 00

.bss            0x0045d000     0xda00
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
 COMMON         0x00466d40     0x33d0 main.o
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
                0x00468eb0                shell_name
                0x00468ec0                shellMaxRows
                0x00468ed0                screenbufferList
                0x00468ef0                foregroung_color
                0x00468f00                pwd
                0x00468f10                CurrentWindow
                0x00468f20                dummycompiler
                0x00468f30                topbar_scrollbarWindow
                0x00468f40                current_connection
                0x00468f50                filename_lenght
                0x00468f60                current_semaphore
                0x00468f70                g_current_volume_id
                0x00468f80                ShellHook
                0x00468f90                current_command
                0x00468fa0                topbar_checkboxWindow
                0x00468fb0                shellScreenBufferMaxRows
                0x00468fc0                shellScreenWidth
                0x00468fd0                screen_buffer_pos
                0x00468fe0                shellScreenHeight
                0x00468ff0                current_volume_id
                0x00469000                pathname_buffer
                0x00469040                filename_initilized
                0x00469050                pathname_initilized
                0x00469060                editboxWindow
                0x00469070                username
                0x00469080                screen_buffer_x
                0x00469090                screen_buffer
                0x0046a040                shell_window_y
                0x0046a050                terminal_rect
                0x0046a060                password
                0x0046a070                CursorInfo
                0x0046a080                shellMaxColumns
                0x0046a090                i1Window
                0x0046a0a0                screen_buffer_y
                0x0046a0b0                topbar_editboxWindow
                0x0046a0c0                topbarWindow
                0x0046a0d0                ApplicationInfo
                0x0046a0e0                shell_environment
                0x0046a0f0                current_workingdiretory_string
 COMMON         0x0046a110      0x8f0 stdlib.o
                0x0046a110                current_mmblock
                0x0046a120                mm_prev_pointer
                0x0046a130                heap_end
                0x0046a140                g_available_heap
                0x0046a150                heap_start
                0x0046a160                heapCount
                0x0046a170                HEAP_START
                0x0046a180                g_heap_pointer
                0x0046a190                heapList
                0x0046a590                HEAP_SIZE
                0x0046a5a0                last_size
                0x0046a5b0                last_valid
                0x0046a5c0                mmblockList
                0x0046a9c0                libcHeap
                0x0046a9d0                Heap
                0x0046a9e0                mmblockCount
                0x0046a9f0                HEAP_END
                0x0046aa00                end = .
                0x0046aa00                _end = .
                0x0046aa00                __end = .
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
