
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

.text           0x00451000     0x7000
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
                0x00452d27                shellPrompt
                0x004535f5                shellSendMessage
                0x00452ee3                shellTestThreads
                0x004536d3                shellTaskList
                0x004513bf                shellProcedure
                0x00452734                shellShell
                0x004539a2                shellShowProcessHeapPointer
                0x00452ce6                shellThread
                0x00453d63                concat
                0x00452879                shellInit
                0x0045383a                shellShowPPID
                0x00453a0a                shellShowKernelHeapPointer
                0x004515d4                shellWaitCmd
                0x00452de0                shellShowScreenBuffer
                0x004510a4                GramadoMain
                0x00453966                shellShowDesktopID
                0x00453174                shellInsertCharXY
                0x004531be                shellInsertCharPos
                0x00453cf7                die
                0x00453a7e                shellShowPCIInfo
                0x004515ec                shellCompare
                0x00452d9e                shellClearBuffer
                0x00452ff8                shellRefreshScreen
                0x00453c3b                feedterminalDialog
                0x00453e42                shellExecuteThisScript
                0x00452f73                shellClearScreen
                0x004534dc                shellShowSystemInfo
                0x004531f6                shellInsertNextChar
                0x00453ad6                shell_fntos
                0x00453a52                shellShowMemoryInfo
                0x00452e4e                shellTestLoadFile
                0x004532ed                move_to
                0x00453222                shellInsertCR
                0x004533dc                shellShowMetrics
                0x004538b2                shellShowGID
                0x00453048                shellScroll
                0x00453aaa                shellShowKernelInfo
                0x00453646                shellUpdateWorkingDiretoryString
                0x00453260                shellInsertNullTerminator
                0x00453876                shellShowUID
                0x00453241                shellInsertLF
                0x004536c6                shellUpdateCurrentDirectoryID
                0x0045361d                shell_memcpy_bytes
                0x00452cbc                shellSetCursor
                0x00453bc5                shell_gramado_core_init_execve
                0x00453312                shellShowInfo
                0x0045354a                shellShowWindowInfo
                0x004537fe                shellShowPID
                0x00453dfb                error
                0x004538ee                shellShowUserSessionID
                0x0045392a                shellShowWindowStationID
                0x00453d38                xmalloc
                0x00452d13                shellTree
                0x00452cff                shellHelp
                0x0045327f                shellTestMBR
 .text          0x00453eb4      0x5a0 shellui.o
                0x004542ac                shellTestDisplayBMP
                0x00454021                shellCreateEditBox
                0x00453eb4                shellTopbarProcedure
                0x00454322                bmpDisplayBMP
                0x004540cf                shellCreateTopBar
 .text          0x00454454     0x1530 api.o
                0x00455207                APIShowCurrentProcessInfo
                0x00455957                api_getchar
                0x004549f4                system11
                0x00454a99                refresh_buffer
                0x004550e9                APISetFocus
                0x00454a57                system14
                0x00454d7e                apiInitBackground
                0x00454fbd                APICreateWindow
                0x00455734                apiBeginPaint
                0x00454d83                MessageBox
                0x00455285                APIreplace_window
                0x0045577b                apiGetSystemMetrics
                0x00454a36                system13
                0x004555eb                apiDown
                0x00455683                enterCriticalSection
                0x004558c0                gramadocore_init_execve
                0x004555c1                apiFOpen
                0x004548aa                system1
                0x0045492e                system5
                0x00455439                api_refresh_screen
                0x004558de                apiDialog
                0x004554c5                apiGetCursorY
                0x00454d29                carrega_bitmap_16x16
                0x004556dc                exitCriticalSection
                0x00454454                system_call
                0x00455637                apiUp
                0x0045447c                apiSystem
                0x00455894                api_get_window_with_text_input
                0x00454a78                system15
                0x00455199                APISetActiveWindow
                0x0045551d                apiSetClientAreaRect
                0x0045525c                APIredraw_window
                0x0045556f                apiCreateThread
                0x00454cc5                SetNextWindowProcedure
                0x00455499                apiGetCursorX
                0x00454c95                chama_procedimento
                0x00454dac                call_kernel
                0x00455065                APIRegisterWindow
                0x004553af                api_strncmp
                0x004552d7                APIminimize_window
                0x004548cb                system2
                0x004548ec                system3
                0x004557cd                api_get_current_keyboard_responder
                0x00455546                apiCreateProcess
                0x0045512b                APIGetFocus
                0x00454970                system7
                0x0045494f                system6
                0x00455771                apiDefDialog
                0x004550a7                APICloseWindow
                0x00455708                initializeCriticalSection
                0x004549d3                system10
                0x00454cf5                set_cursor
                0x004552ae                APImaximize_window
                0x004558d4                execve
                0x0045540d                refresh_screen
                0x00454f2c                call_gui
                0x004549b2                system9
                0x004558ca                fork
                0x004557a4                api_set_current_keyboard_responder
                0x00455233                APIresize_window
                0x0045573e                apiEndPaint
                0x00454d24                put_char
                0x00454c30                print_string
                0x004554f1                apiGetClientAreaRect
                0x00454c66                edit_box
                0x0045537e                kill
                0x00455443                apiReboot
                0x00454d52                apiShutDown
                0x004557f9                api_set_current_mouse_responder
                0x00455355                exit
                0x00455300                APIget_foregroung_window
                0x0045490d                system4
                0x0045546f                apiSetCursor
                0x00454a15                system12
                0x00454c35                vsync
                0x00454991                system8
                0x0045584e                api_set_window_with_text_input
                0x004551db                APIGetActiveWindow
                0x00455822                api_get_current_mouse_responder
                0x00455383                dead_thread_collector
                0x00455598                apiStartThread
                0x00455157                APIKillFocus
                0x0045532c                APIset_foregroung_window
                0x00455748                apiPutChar
 .text          0x00455984     0x1110 stdio.o
                0x004562cb                putchar
                0x00455984                stdio_fntos
                0x00456287                sprintf
                0x0045695e                feof
                0x00456a3e                fputc
                0x00456811                fputs
                0x0045699c                ferror
                0x004564b7                input
                0x00455b71                scroll
                0x004564ad                printf_main
                0x00456886                gets
                0x004562f7                outbyte
                0x00455d1b                app_print
                0x0045672c                fflush
                0x0045679c                fprintf
                0x004565ae                stdio_system_call
                0x00455ad9                fopen
                0x004565d6                getchar
                0x00456608                stdioInitialize
                0x004568fb                fgetc
                0x00455a73                fclose
                0x004569c4                fseek
                0x0045647a                _outbyte
                0x0045626c                printf
                0x00455caf                app_clear
 .text          0x00456a94      0x960 stdlib.o
                0x00456d4f                FreeHeap
                0x00456a94                rtGetHeapStart
                0x00456f96                free
                0x00456f38                rand
                0x00456eaf                stdlibInitMM
                0x00456d59                heapInit
                0x00456aa8                rtGetHeapPointer
                0x00456ab2                rtGetAvailableHeap
                0x00456f0f                libcInitRT
                0x00456abc                heapSetLibcHeap
                0x00456f55                malloc
                0x00456d3c                AllocateHeapEx
                0x00456b63                AllocateHeap
                0x0045738d                stdlib_strncmp
                0x00456a9e                rtGetHeapEnd
                0x00456f9b                system
 .text          0x004573f4      0x4a0 string.o
                0x0045765b                strcspn
                0x004575be                strcat
                0x004573f4                strcmp
                0x00457615                bzero
                0x0045779b                strtok_r
                0x00457551                memcpy
                0x00457528                memoryZeroMemory
                0x004575ee                bcopy
                0x0045758e                strcpy
                0x004576fb                strspn
                0x00457870                strtok
                0x004574ad                str_cmp
                0x0045744f                strncmp
                0x00457630                strlen
 .text          0x00457894       0x90 conio.o
                0x00457902                getche
                0x00457894                putch
                0x004578b7                cputs
                0x004578eb                getch
 .text          0x00457924      0x1a0 builtins.o
                0x00457a89                pwd_builtins
                0x00457a23                getuid_builtins
                0x00457a35                getgid_builtins
                0x004579ac                echo_builtins
                0x00457968                dir_builtins
                0x004579df                exit_builtins
                0x004579ff                getpid_builtins
                0x00457959                copy_builtins
                0x00457a11                getppid_builtins
                0x004579cb                exec_builtins
                0x00457938                cls_builtins
                0x0045795e                date_builtins
                0x00457963                del_builtins
                0x00457924                cd_buitins
                0x00457a47                help_builtins
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457ac4      0x53c 00

.rdata          0x00458000     0x26b0
 .rdata         0x00458000      0x480 builtins.o
 .rdata         0x00458480       0x10 conio.o
 .rdata         0x00458490      0x430 stdlib.o
 .rdata         0x004588c0       0x40 stdio.o
 .rdata         0x00458900      0x320 api.o
 .rdata         0x00458c20      0x6c0 shellui.o
 .rdata         0x004592e0     0x1320 main.o
 .rdata         0x0045a600       0xb0 crt0.o

.data           0x0045a6b0      0x950
                0x0045a6b0                data = .
                0x0045a6b0                _data = .
                0x0045a6b0                __data = .
 *(.data)
 .data          0x0045a6b0       0x30 crt0.o
 .data          0x0045a6e0       0x20 main.o
                0x0045a6f8                shell_config_file
 .data          0x0045a700       0x20 shellui.o
 .data          0x0045a720        0x0 api.o
 .data          0x0045a720        0x0 stdio.o
 .data          0x0045a720       0x10 stdlib.o
 .data          0x0045a730        0x0 string.o
 .data          0x0045a730        0x0 conio.o
 .data          0x0045a730       0x20 builtins.o
                0x0045b000                . = ALIGN (0x1000)
 *fill*         0x0045a750      0x8b0 00

.bss            0x0045b000     0xd910
                0x0045b000                bss = .
                0x0045b000                _bss = .
                0x0045b000                __bss = .
 *(.bss)
 .bss           0x0045b000        0x0 crt0.o
 .bss           0x0045b000       0xe0 main.o
                0x0045b008                interactive
                0x0045b004                login_shell
                0x0045b000                quiet
                0x0045b00c                ShellFlag
 .bss           0x0045b0e0       0xd0 shellui.o
 .bss           0x0045b1b0       0x30 api.o
 .bss           0x0045b1e0       0x10 stdio.o
 .bss           0x0045b1f0     0x8000 stdlib.o
 .bss           0x004631f0       0x10 string.o
 .bss           0x00463200        0x0 conio.o
 .bss           0x00463200       0xd0 builtins.o
                0x00464000                . = ALIGN (0x1000)
 *fill*         0x004632d0      0xd30 00
 COMMON         0x00464000      0xd40 crt0.o
                0x00464000                prompt
                0x00464400                stderr
                0x00464410                prompt_pos
                0x00464420                g_using_gui
                0x00464430                stdin
                0x00464440                prompt_max
                0x00464450                prompt_err
                0x00464850                g_columns
                0x00464860                stdout
                0x00464870                Streams
                0x004648f0                g_rows
                0x00464900                prompt_out
                0x00464d00                g_cursor_y
                0x00464d10                prompt_status
                0x00464d20                g_char_attrib
                0x00464d30                g_cursor_x
 COMMON         0x00464d40     0x32e0 main.o
                0x00464d40                ShellMetrics
                0x00464d50                shellStatus
                0x00464d60                CommandHistory
                0x00464d70                EOF_Reached
                0x00464d80                shellWindowWidth
                0x00464d90                ClientAreaInfo
                0x00464da0                g_current_disk_id
                0x00464db0                BufferInfo
                0x00464dc0                shellError
                0x00464dd0                shellWindowHeight
                0x00464de0                lineList
                0x00466de0                root
                0x00466df0                CurrentCommand
                0x00466e00                shell_info
                0x00466e20                shellScreenBufferMaxColumns
                0x00466e30                g_current_workingdirectory_id
                0x00466e40                shell_window_x
                0x00466e50                i2Window
                0x00466e60                rect
                0x00466e70                backgroung_color
                0x00466e80                shell_name
                0x00466e90                shellMaxRows
                0x00466ea0                screenbufferList
                0x00466ec0                foregroung_color
                0x00466ed0                pwd
                0x00466ee0                CurrentWindow
                0x00466ef0                topbar_scrollbarWindow
                0x00466f00                current_semaphore
                0x00466f10                g_current_volume_id
                0x00466f20                ShellHook
                0x00466f30                topbar_checkboxWindow
                0x00466f40                shellScreenBufferMaxRows
                0x00466f50                shellScreenWidth
                0x00466f60                screen_buffer_pos
                0x00466f70                shellScreenHeight
                0x00466f80                editboxWindow
                0x00466f90                username
                0x00466fa0                screen_buffer_x
                0x00466fb0                screen_buffer
                0x00467f60                shell_window_y
                0x00467f70                terminal_rect
                0x00467f80                password
                0x00467f90                CursorInfo
                0x00467fa0                shellMaxColumns
                0x00467fb0                i1Window
                0x00467fc0                screen_buffer_y
                0x00467fd0                topbar_editboxWindow
                0x00467fe0                topbarWindow
                0x00467ff0                ApplicationInfo
                0x00468000                current_workingdiretory_string
 COMMON         0x00468020      0x8f0 stdlib.o
                0x00468020                current_mmblock
                0x00468030                mm_prev_pointer
                0x00468040                heap_end
                0x00468050                g_available_heap
                0x00468060                heap_start
                0x00468070                heapCount
                0x00468080                HEAP_START
                0x00468090                g_heap_pointer
                0x004680a0                heapList
                0x004684a0                HEAP_SIZE
                0x004684b0                last_size
                0x004684c0                last_valid
                0x004684d0                mmblockList
                0x004688d0                libcHeap
                0x004688e0                Heap
                0x004688f0                mmblockCount
                0x00468900                HEAP_END
                0x00468910                end = .
                0x00468910                _end = .
                0x00468910                __end = .
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
