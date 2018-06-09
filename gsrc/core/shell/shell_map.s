
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
 .text          0x004510a4     0x3570 main.o
                0x00453197                shellPrompt
                0x00453b40                shellSendMessage
                0x0045337b                shellTestThreads
                0x00453c94                shellTaskList
                0x004513c7                shellProcedure
                0x00452b90                shellShell
                0x00453f63                shellShowProcessHeapPointer
                0x00453156                shellThread
                0x00454370                concat
                0x00452ced                shellInit
                0x00453dfb                shellShowPPID
                0x00453fcb                shellShowKernelHeapPointer
                0x00453c05                shellInitializeWorkingDiretoryString
                0x004515dc                shellWaitCmd
                0x00453250                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x004545bb                shellInitFilename
                0x00453f27                shellShowDesktopID
                0x00453653                shellInsertCharXY
                0x00454570                shellInitPathname
                0x0045369d                shellInsertCharPos
                0x00454304                die
                0x00454097                shellShowPCIInfo
                0x00453b91                shellExit
                0x004515f4                shellCompare
                0x0045320e                shellClearBuffer
                0x004544ea                absolute_pathname
                0x00453445                shellRefreshScreen
                0x00454248                feedterminalDialog
                0x0045444f                shellExecuteThisScript
                0x0045340b                shellClearScreen
                0x00453a0f                shellShowSystemInfo
                0x004536d5                shellInsertNextChar
                0x004540ef                shell_fntos
                0x0045406b                shellShowMemoryInfo
                0x004532af                shellTestLoadFile
                0x0045384c                move_to
                0x0045371e                shellInsertCR
                0x0045393b                shellShowMetrics
                0x00453e73                shellShowGID
                0x004534c7                shellScroll
                0x004540c3                shellShowKernelInfo
                0x00453ba2                shellUpdateWorkingDiretoryString
                0x0045379e                shellInsertNullTerminator
                0x00453e37                shellShowUID
                0x0045375e                shellInsertLF
                0x00453c87                shellUpdateCurrentDirectoryID
                0x00453b68                shell_memcpy_bytes
                0x0045312c                shellSetCursor
                0x004541de                shell_gramado_core_init_execve
                0x00453871                shellShowInfo
                0x0045403f                shellShowVolumeInfo
                0x00453a7d                shellShowWindowInfo
                0x004510a4                quit
                0x00453dbf                shellShowPID
                0x00454408                error
                0x00453eaf                shellShowUserSessionID
                0x00453eeb                shellShowWindowStationID
                0x00454345                xmalloc
                0x00454013                shellShowDiskInfo
                0x00453183                shellTree
                0x0045316f                shellHelp
                0x004537de                shellTestMBR
 .text          0x00454614      0x7b0 shellui.o
                0x00454c10                shellTestDisplayBMP
                0x00454870                shellCreateEditBox
                0x00454b9b                shellDisplayBMP
                0x00454703                shellTopbarProcedure
                0x00454c86                bmpDisplayBMP
                0x0045491e                shellCreateTopBar
                0x00454614                shellui_fntos
 .text          0x00454dc4     0x1980 api.o
                0x00455b79                APIShowCurrentProcessInfo
                0x0045633d                api_getchar
                0x00455366                system11
                0x0045540b                refresh_buffer
                0x00455a5b                APISetFocus
                0x004553c9                system14
                0x004556f0                apiInitBackground
                0x0045592f                APICreateWindow
                0x004560f8                apiBeginPaint
                0x004556f5                MessageBox
                0x00455bf7                APIreplace_window
                0x0045613f                apiGetSystemMetrics
                0x004553a8                system13
                0x00455faf                apiDown
                0x00455cc7                apiExit
                0x00456047                enterCriticalSection
                0x00456284                gramadocore_init_execve
                0x00455f35                apiFOpen
                0x0045521c                system1
                0x004552a0                system5
                0x00455dad                api_refresh_screen
                0x004562c4                apiDialog
                0x00455e39                apiGetCursorY
                0x0045569b                carrega_bitmap_16x16
                0x004560a0                exitCriticalSection
                0x00454dc4                system_call
                0x00455ffb                apiUp
                0x00454dec                apiSystem
                0x00456258                api_get_window_with_text_input
                0x004553ea                system15
                0x00455b0b                APISetActiveWindow
                0x00455e91                apiSetClientAreaRect
                0x00455bce                APIredraw_window
                0x00455ee3                apiCreateThread
                0x00455637                SetNextWindowProcedure
                0x00455e0d                apiGetCursorX
                0x00455607                chama_procedimento
                0x0045571e                call_kernel
                0x004559d7                APIRegisterWindow
                0x00455d23                api_strncmp
                0x00455c49                APIminimize_window
                0x0045523d                system2
                0x0045525e                system3
                0x00456191                api_get_current_keyboard_responder
                0x00455eba                apiCreateProcess
                0x00455a9d                APIGetFocus
                0x004552e2                system7
                0x004552c1                system6
                0x00456135                apiDefDialog
                0x00455a19                APICloseWindow
                0x004560cc                initializeCriticalSection
                0x00455345                system10
                0x00455667                set_cursor
                0x00455c20                APImaximize_window
                0x004562ba                execve
                0x00455d81                refresh_screen
                0x00456369                apiDisplayBMP
                0x0045589e                call_gui
                0x00455324                system9
                0x0045628e                fork
                0x00456168                api_set_current_keyboard_responder
                0x00455ba5                APIresize_window
                0x00456102                apiEndPaint
                0x00455696                put_char
                0x004555a2                print_string
                0x00455e65                apiGetClientAreaRect
                0x004555d8                edit_box
                0x00455cf2                kill
                0x00455db7                apiReboot
                0x004556c4                apiShutDown
                0x004561bd                api_set_current_mouse_responder
                0x00455c72                APIget_foregroung_window
                0x0045527f                system4
                0x00455f6f                apiSaveFile
                0x00455de3                apiSetCursor
                0x00455387                system12
                0x004555a7                vsync
                0x00455303                system8
                0x00456212                api_set_window_with_text_input
                0x00455b4d                APIGetActiveWindow
                0x004561e6                api_get_current_mouse_responder
                0x00455cf7                dead_thread_collector
                0x00455f0c                apiStartThread
                0x00455ac9                APIKillFocus
                0x00455c9e                APIset_foregroung_window
                0x0045610c                apiPutChar
 .text          0x00456744     0x1110 stdio.o
                0x0045708b                putchar
                0x00456744                stdio_fntos
                0x00457047                sprintf
                0x0045771c                feof
                0x004577fa                fputc
                0x004575d1                fputs
                0x0045775a                ferror
                0x00457277                input
                0x00456931                scroll
                0x0045726d                printf_main
                0x00457646                gets
                0x004570b7                outbyte
                0x00456adb                app_print
                0x004574ec                fflush
                0x0045755c                fprintf
                0x0045736e                stdio_system_call
                0x00456899                fopen
                0x00457396                getchar
                0x004573c8                stdioInitialize
                0x004576bb                fgetc
                0x00456833                fclose
                0x00457780                fseek
                0x0045723a                _outbyte
                0x0045702c                printf
                0x00456a6f                app_clear
 .text          0x00457854      0x9b0 stdlib.o
                0x00457b37                FreeHeap
                0x0045787c                rtGetHeapStart
                0x00457d7e                free
                0x00457854                stdlib_system_call
                0x00457d20                rand
                0x00457c97                stdlibInitMM
                0x00457b41                heapInit
                0x00457890                rtGetHeapPointer
                0x0045789a                rtGetAvailableHeap
                0x00457cf7                libcInitRT
                0x004578a4                heapSetLibcHeap
                0x00457d3d                malloc
                0x00457b24                AllocateHeapEx
                0x0045794b                AllocateHeap
                0x00458175                stdlib_strncmp
                0x004581d3                exit
                0x00457886                rtGetHeapEnd
                0x00457d83                system
 .text          0x00458204      0x4a0 string.o
                0x0045846b                strcspn
                0x004583ce                strcat
                0x00458204                strcmp
                0x00458425                bzero
                0x004585ab                strtok_r
                0x00458361                memcpy
                0x00458338                memoryZeroMemory
                0x004583fe                bcopy
                0x0045839e                strcpy
                0x0045850b                strspn
                0x00458680                strtok
                0x004582bd                str_cmp
                0x0045825f                strncmp
                0x00458440                strlen
 .text          0x004586a4       0x90 conio.o
                0x00458712                getche
                0x004586a4                putch
                0x004586c7                cputs
                0x004586fb                getch
 .text          0x00458734      0x1a0 builtins.o
                0x00458899                pwd_builtins
                0x00458833                getuid_builtins
                0x00458845                getgid_builtins
                0x004587bc                echo_builtins
                0x00458778                dir_builtins
                0x004587ef                exit_builtins
                0x0045880f                getpid_builtins
                0x00458769                copy_builtins
                0x00458821                getppid_builtins
                0x004587db                exec_builtins
                0x00458748                cls_builtins
                0x0045876e                date_builtins
                0x00458773                del_builtins
                0x00458734                cd_buitins
                0x00458857                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x004588d4      0x72c 00

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
