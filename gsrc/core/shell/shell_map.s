
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
 .text          0x004510a4     0x3310 main.o
                0x004530e1                shellPrompt
                0x004539ed                shellSendMessage
                0x00453274                shellTestThreads
                0x00453acb                shellTaskList
                0x004513c3                shellProcedure
                0x00452ade                shellShell
                0x00453d9a                shellShowProcessHeapPointer
                0x004530a0                shellThread
                0x004541a7                concat
                0x00452be3                shellInit
                0x00453c32                shellShowPPID
                0x00453e02                shellShowKernelHeapPointer
                0x004515d8                shellWaitCmd
                0x0045319a                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00453d5e                shellShowDesktopID
                0x004534ec                shellInsertCharXY
                0x00453536                shellInsertCharPos
                0x0045413b                die
                0x00453ece                shellShowPCIInfo
                0x004515f0                shellCompare
                0x00453158                shellClearBuffer
                0x00454321                absolute_pathname
                0x0045333e                shellRefreshScreen
                0x0045407f                feedterminalDialog
                0x00454286                shellExecuteThisScript
                0x00453304                shellClearScreen
                0x004538c8                shellShowSystemInfo
                0x0045356e                shellInsertNextChar
                0x00453f26                shell_fntos
                0x00453ea2                shellShowMemoryInfo
                0x004531f9                shellTestLoadFile
                0x004536e5                move_to
                0x004535b7                shellInsertCR
                0x004537d4                shellShowMetrics
                0x00453caa                shellShowGID
                0x004533c0                shellScroll
                0x00453efa                shellShowKernelInfo
                0x00453a3e                shellUpdateWorkingDiretoryString
                0x00453637                shellInsertNullTerminator
                0x00453c6e                shellShowUID
                0x004535f7                shellInsertLF
                0x00453abe                shellUpdateCurrentDirectoryID
                0x00453a15                shell_memcpy_bytes
                0x00453076                shellSetCursor
                0x00454015                shell_gramado_core_init_execve
                0x0045370a                shellShowInfo
                0x00453e76                shellShowVolumeInfo
                0x00453936                shellShowWindowInfo
                0x004510a4                quit
                0x00453bf6                shellShowPID
                0x0045423f                error
                0x00453ce6                shellShowUserSessionID
                0x00453d22                shellShowWindowStationID
                0x0045417c                xmalloc
                0x00453e4a                shellShowDiskInfo
                0x004530cd                shellTree
                0x004530b9                shellHelp
                0x00453677                shellTestMBR
 .text          0x004543b4      0x7b0 shellui.o
                0x004549b0                shellTestDisplayBMP
                0x00454610                shellCreateEditBox
                0x0045493b                shellDisplayBMP
                0x004544a3                shellTopbarProcedure
                0x00454a26                bmpDisplayBMP
                0x004546be                shellCreateTopBar
                0x004543b4                shellui_fntos
 .text          0x00454b64     0x1980 api.o
                0x00455919                APIShowCurrentProcessInfo
                0x004560dd                api_getchar
                0x00455106                system11
                0x004551ab                refresh_buffer
                0x004557fb                APISetFocus
                0x00455169                system14
                0x00455490                apiInitBackground
                0x004556cf                APICreateWindow
                0x00455e98                apiBeginPaint
                0x00455495                MessageBox
                0x00455997                APIreplace_window
                0x00455edf                apiGetSystemMetrics
                0x00455148                system13
                0x00455d4f                apiDown
                0x00455a67                apiExit
                0x00455de7                enterCriticalSection
                0x00456024                gramadocore_init_execve
                0x00455cd5                apiFOpen
                0x00454fbc                system1
                0x00455040                system5
                0x00455b4d                api_refresh_screen
                0x00456064                apiDialog
                0x00455bd9                apiGetCursorY
                0x0045543b                carrega_bitmap_16x16
                0x00455e40                exitCriticalSection
                0x00454b64                system_call
                0x00455d9b                apiUp
                0x00454b8c                apiSystem
                0x00455ff8                api_get_window_with_text_input
                0x0045518a                system15
                0x004558ab                APISetActiveWindow
                0x00455c31                apiSetClientAreaRect
                0x0045596e                APIredraw_window
                0x00455c83                apiCreateThread
                0x004553d7                SetNextWindowProcedure
                0x00455bad                apiGetCursorX
                0x004553a7                chama_procedimento
                0x004554be                call_kernel
                0x00455777                APIRegisterWindow
                0x00455ac3                api_strncmp
                0x004559e9                APIminimize_window
                0x00454fdd                system2
                0x00454ffe                system3
                0x00455f31                api_get_current_keyboard_responder
                0x00455c5a                apiCreateProcess
                0x0045583d                APIGetFocus
                0x00455082                system7
                0x00455061                system6
                0x00455ed5                apiDefDialog
                0x004557b9                APICloseWindow
                0x00455e6c                initializeCriticalSection
                0x004550e5                system10
                0x00455407                set_cursor
                0x004559c0                APImaximize_window
                0x0045605a                execve
                0x00455b21                refresh_screen
                0x00456109                apiDisplayBMP
                0x0045563e                call_gui
                0x004550c4                system9
                0x0045602e                fork
                0x00455f08                api_set_current_keyboard_responder
                0x00455945                APIresize_window
                0x00455ea2                apiEndPaint
                0x00455436                put_char
                0x00455342                print_string
                0x00455c05                apiGetClientAreaRect
                0x00455378                edit_box
                0x00455a92                kill
                0x00455b57                apiReboot
                0x00455464                apiShutDown
                0x00455f5d                api_set_current_mouse_responder
                0x00455a12                APIget_foregroung_window
                0x0045501f                system4
                0x00455d0f                apiSaveFile
                0x00455b83                apiSetCursor
                0x00455127                system12
                0x00455347                vsync
                0x004550a3                system8
                0x00455fb2                api_set_window_with_text_input
                0x004558ed                APIGetActiveWindow
                0x00455f86                api_get_current_mouse_responder
                0x00455a97                dead_thread_collector
                0x00455cac                apiStartThread
                0x00455869                APIKillFocus
                0x00455a3e                APIset_foregroung_window
                0x00455eac                apiPutChar
 .text          0x004564e4     0x1110 stdio.o
                0x00456e2b                putchar
                0x004564e4                stdio_fntos
                0x00456de7                sprintf
                0x004574bc                feof
                0x0045759a                fputc
                0x00457371                fputs
                0x004574fa                ferror
                0x00457017                input
                0x004566d1                scroll
                0x0045700d                printf_main
                0x004573e6                gets
                0x00456e57                outbyte
                0x0045687b                app_print
                0x0045728c                fflush
                0x004572fc                fprintf
                0x0045710e                stdio_system_call
                0x00456639                fopen
                0x00457136                getchar
                0x00457168                stdioInitialize
                0x0045745b                fgetc
                0x004565d3                fclose
                0x00457520                fseek
                0x00456fda                _outbyte
                0x00456dcc                printf
                0x0045680f                app_clear
 .text          0x004575f4      0x9b0 stdlib.o
                0x004578d7                FreeHeap
                0x0045761c                rtGetHeapStart
                0x00457b1e                free
                0x004575f4                stdlib_system_call
                0x00457ac0                rand
                0x00457a37                stdlibInitMM
                0x004578e1                heapInit
                0x00457630                rtGetHeapPointer
                0x0045763a                rtGetAvailableHeap
                0x00457a97                libcInitRT
                0x00457644                heapSetLibcHeap
                0x00457add                malloc
                0x004578c4                AllocateHeapEx
                0x004576eb                AllocateHeap
                0x00457f15                stdlib_strncmp
                0x00457f73                exit
                0x00457626                rtGetHeapEnd
                0x00457b23                system
 .text          0x00457fa4      0x4a0 string.o
                0x0045820b                strcspn
                0x0045816e                strcat
                0x00457fa4                strcmp
                0x004581c5                bzero
                0x0045834b                strtok_r
                0x00458101                memcpy
                0x004580d8                memoryZeroMemory
                0x0045819e                bcopy
                0x0045813e                strcpy
                0x004582ab                strspn
                0x00458420                strtok
                0x0045805d                str_cmp
                0x00457fff                strncmp
                0x004581e0                strlen
 .text          0x00458444       0x90 conio.o
                0x004584b2                getche
                0x00458444                putch
                0x00458467                cputs
                0x0045849b                getch
 .text          0x004584d4      0x1a0 builtins.o
                0x00458639                pwd_builtins
                0x004585d3                getuid_builtins
                0x004585e5                getgid_builtins
                0x0045855c                echo_builtins
                0x00458518                dir_builtins
                0x0045858f                exit_builtins
                0x004585af                getpid_builtins
                0x00458509                copy_builtins
                0x004585c1                getppid_builtins
                0x0045857b                exec_builtins
                0x004584e8                cls_builtins
                0x0045850e                date_builtins
                0x00458513                del_builtins
                0x004584d4                cd_buitins
                0x004585f7                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458674      0x98c 00

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
