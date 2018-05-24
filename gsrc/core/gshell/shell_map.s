
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
 .text          0x004510a4     0x2bd0 main.o
                0x00452a7e                shellPrompt
                0x0045338a                shellSendMessage
                0x00452c11                shellTestThreads
                0x00453468                shellTaskList
                0x004513cb                shellProcedure
                0x0045271d                shellShell
                0x00453737                shellShowProcessHeapPointer
                0x00452a3d                shellThread
                0x00453aec                concat
                0x00452822                shellInit
                0x004535cf                shellShowPPID
                0x0045379f                shellShowKernelHeapPointer
                0x004515e0                shellWaitCmd
                0x00452b37                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x004536fb                shellShowDesktopID
                0x00452e89                shellInsertCharXY
                0x00452ed3                shellInsertCharPos
                0x00453a80                die
                0x00453813                shellShowPCIInfo
                0x004515f8                shellCompare
                0x00452af5                shellClearBuffer
                0x00452cdb                shellRefreshScreen
                0x004539c4                feedterminalDialog
                0x00453bcb                shellExecuteThisScript
                0x00452ca1                shellClearScreen
                0x00453265                shellShowSystemInfo
                0x00452f0b                shellInsertNextChar
                0x0045386b                shell_fntos
                0x004537e7                shellShowMemoryInfo
                0x00452b96                shellTestLoadFile
                0x00453082                move_to
                0x00452f54                shellInsertCR
                0x00453171                shellShowMetrics
                0x00453647                shellShowGID
                0x00452d5d                shellScroll
                0x0045383f                shellShowKernelInfo
                0x004533db                shellUpdateWorkingDiretoryString
                0x00452fd4                shellInsertNullTerminator
                0x0045360b                shellShowUID
                0x00452f94                shellInsertLF
                0x0045345b                shellUpdateCurrentDirectoryID
                0x004533b2                shell_memcpy_bytes
                0x00452a13                shellSetCursor
                0x0045395a                shell_gramado_core_init_execve
                0x004530a7                shellShowInfo
                0x004532d3                shellShowWindowInfo
                0x004510a4                quit
                0x00453593                shellShowPID
                0x00453b84                error
                0x00453683                shellShowUserSessionID
                0x004536bf                shellShowWindowStationID
                0x00453ac1                xmalloc
                0x00452a6a                shellTree
                0x00452a56                shellHelp
                0x00453014                shellTestMBR
 .text          0x00453c74      0x7b0 shellui.o
                0x00454270                shellTestDisplayBMP
                0x00453ed0                shellCreateEditBox
                0x004541fb                shellDisplayBMP
                0x00453d63                shellTopbarProcedure
                0x004542e6                bmpDisplayBMP
                0x00453f7e                shellCreateTopBar
                0x00453c74                shellui_fntos
 .text          0x00454424     0x1910 api.o
                0x004551d9                APIShowCurrentProcessInfo
                0x0045592b                api_getchar
                0x004549c6                system11
                0x00454a6b                refresh_buffer
                0x004550bb                APISetFocus
                0x00454a29                system14
                0x00454d50                apiInitBackground
                0x00454f8f                APICreateWindow
                0x00455708                apiBeginPaint
                0x00454d55                MessageBox
                0x00455257                APIreplace_window
                0x0045574f                apiGetSystemMetrics
                0x00454a08                system13
                0x004555bf                apiDown
                0x00455327                apiExit
                0x00455657                enterCriticalSection
                0x00455894                gramadocore_init_execve
                0x00455595                apiFOpen
                0x0045487c                system1
                0x00454900                system5
                0x0045540d                api_refresh_screen
                0x004558b2                apiDialog
                0x00455499                apiGetCursorY
                0x00454cfb                carrega_bitmap_16x16
                0x004556b0                exitCriticalSection
                0x00454424                system_call
                0x0045560b                apiUp
                0x0045444c                apiSystem
                0x00455868                api_get_window_with_text_input
                0x00454a4a                system15
                0x0045516b                APISetActiveWindow
                0x004554f1                apiSetClientAreaRect
                0x0045522e                APIredraw_window
                0x00455543                apiCreateThread
                0x00454c97                SetNextWindowProcedure
                0x0045546d                apiGetCursorX
                0x00454c67                chama_procedimento
                0x00454d7e                call_kernel
                0x00455037                APIRegisterWindow
                0x00455383                api_strncmp
                0x004552a9                APIminimize_window
                0x0045489d                system2
                0x004548be                system3
                0x004557a1                api_get_current_keyboard_responder
                0x0045551a                apiCreateProcess
                0x004550fd                APIGetFocus
                0x00454942                system7
                0x00454921                system6
                0x00455745                apiDefDialog
                0x00455079                APICloseWindow
                0x004556dc                initializeCriticalSection
                0x004549a5                system10
                0x00454cc7                set_cursor
                0x00455280                APImaximize_window
                0x004558a8                execve
                0x004553e1                refresh_screen
                0x00455957                apiDisplayBMP
                0x00454efe                call_gui
                0x00454984                system9
                0x0045589e                fork
                0x00455778                api_set_current_keyboard_responder
                0x00455205                APIresize_window
                0x00455712                apiEndPaint
                0x00454cf6                put_char
                0x00454c02                print_string
                0x004554c5                apiGetClientAreaRect
                0x00454c38                edit_box
                0x00455352                kill
                0x00455417                apiReboot
                0x00454d24                apiShutDown
                0x004557cd                api_set_current_mouse_responder
                0x004552d2                APIget_foregroung_window
                0x004548df                system4
                0x00455443                apiSetCursor
                0x004549e7                system12
                0x00454c07                vsync
                0x00454963                system8
                0x00455822                api_set_window_with_text_input
                0x004551ad                APIGetActiveWindow
                0x004557f6                api_get_current_mouse_responder
                0x00455357                dead_thread_collector
                0x0045556c                apiStartThread
                0x00455129                APIKillFocus
                0x004552fe                APIset_foregroung_window
                0x0045571c                apiPutChar
 .text          0x00455d34     0x1110 stdio.o
                0x0045667b                putchar
                0x00455d34                stdio_fntos
                0x00456637                sprintf
                0x00456d0c                feof
                0x00456dea                fputc
                0x00456bc1                fputs
                0x00456d4a                ferror
                0x00456867                input
                0x00455f21                scroll
                0x0045685d                printf_main
                0x00456c36                gets
                0x004566a7                outbyte
                0x004560cb                app_print
                0x00456adc                fflush
                0x00456b4c                fprintf
                0x0045695e                stdio_system_call
                0x00455e89                fopen
                0x00456986                getchar
                0x004569b8                stdioInitialize
                0x00456cab                fgetc
                0x00455e23                fclose
                0x00456d70                fseek
                0x0045682a                _outbyte
                0x0045661c                printf
                0x0045605f                app_clear
 .text          0x00456e44      0x9b0 stdlib.o
                0x00457127                FreeHeap
                0x00456e6c                rtGetHeapStart
                0x0045736e                free
                0x00456e44                stdlib_system_call
                0x00457310                rand
                0x00457287                stdlibInitMM
                0x00457131                heapInit
                0x00456e80                rtGetHeapPointer
                0x00456e8a                rtGetAvailableHeap
                0x004572e7                libcInitRT
                0x00456e94                heapSetLibcHeap
                0x0045732d                malloc
                0x00457114                AllocateHeapEx
                0x00456f3b                AllocateHeap
                0x00457765                stdlib_strncmp
                0x004577c3                exit
                0x00456e76                rtGetHeapEnd
                0x00457373                system
 .text          0x004577f4      0x4a0 string.o
                0x00457a5b                strcspn
                0x004579be                strcat
                0x004577f4                strcmp
                0x00457a15                bzero
                0x00457b9b                strtok_r
                0x00457951                memcpy
                0x00457928                memoryZeroMemory
                0x004579ee                bcopy
                0x0045798e                strcpy
                0x00457afb                strspn
                0x00457c70                strtok
                0x004578ad                str_cmp
                0x0045784f                strncmp
                0x00457a30                strlen
 .text          0x00457c94       0x90 conio.o
                0x00457d02                getche
                0x00457c94                putch
                0x00457cb7                cputs
                0x00457ceb                getch
 .text          0x00457d24      0x1b0 builtins.o
                0x00457e8e                pwd_builtins
                0x00457e28                getuid_builtins
                0x00457e3a                getgid_builtins
                0x00457db1                echo_builtins
                0x00457d6d                dir_builtins
                0x00457de4                exit_builtins
                0x00457e04                getpid_builtins
                0x00457d5e                copy_builtins
                0x00457e16                getppid_builtins
                0x00457dd0                exec_builtins
                0x00457d38                cls_builtins
                0x00457d63                date_builtins
                0x00457d68                del_builtins
                0x00457d24                cd_buitins
                0x00457e4c                help_builtins
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457ed4      0x12c 00

.rdata          0x00458000     0x2550
 .rdata         0x00458000      0x480 builtins.o
 .rdata         0x00458480       0x10 conio.o
 .rdata         0x00458490      0x430 stdlib.o
 .rdata         0x004588c0       0x40 stdio.o
 .rdata         0x00458900      0x320 api.o
 .rdata         0x00458c20      0x6c0 shellui.o
 .rdata         0x004592e0     0x11c0 main.o
 .rdata         0x0045a4a0       0xb0 crt0.o

.data           0x0045a550     0x1ab0
                0x0045a550                data = .
                0x0045a550                _data = .
                0x0045a550                __data = .
 *(.data)
 .data          0x0045a550       0x30 crt0.o
 .data          0x0045a580      0x480 main.o
                0x0045a9e0                running
                0x0045a9e4                shell_config_file
 .data          0x0045aa00      0x460 shellui.o
 .data          0x0045ae60      0x440 api.o
 .data          0x0045b2a0        0x0 stdio.o
 .data          0x0045b2a0       0x10 stdlib.o
 .data          0x0045b2b0        0x0 string.o
 .data          0x0045b2b0        0x0 conio.o
 .data          0x0045b2b0      0x460 builtins.o
                0x0045c000                . = ALIGN (0x1000)
 *fill*         0x0045b710      0x8f0 00

.bss            0x0045c000     0xd920
                0x0045c000                bss = .
                0x0045c000                _bss = .
                0x0045c000                __bss = .
 *(.bss)
 .bss           0x0045c000        0x0 crt0.o
 .bss           0x0045c000       0xe0 main.o
                0x0045c008                interactive
                0x0045c004                login_shell
                0x0045c000                quiet
                0x0045c00c                ShellFlag
 .bss           0x0045c0e0       0xd0 shellui.o
 .bss           0x0045c1b0       0x40 api.o
 .bss           0x0045c1f0       0x10 stdio.o
 .bss           0x0045c200     0x8000 stdlib.o
 .bss           0x00464200       0x10 string.o
 .bss           0x00464210        0x0 conio.o
 .bss           0x00464210       0xd0 builtins.o
                0x00465000                . = ALIGN (0x1000)
 *fill*         0x004642e0      0xd20 00
 COMMON         0x00465000      0xd40 crt0.o
                0x00465000                prompt
                0x00465400                stderr
                0x00465410                prompt_pos
                0x00465420                g_using_gui
                0x00465430                stdin
                0x00465440                prompt_max
                0x00465450                prompt_err
                0x00465850                g_columns
                0x00465860                stdout
                0x00465870                Streams
                0x004658f0                g_rows
                0x00465900                prompt_out
                0x00465d00                g_cursor_y
                0x00465d10                prompt_status
                0x00465d20                g_char_attrib
                0x00465d30                g_cursor_x
 COMMON         0x00465d40     0x32f0 main.o
                0x00465d40                ShellMetrics
                0x00465d50                shellStatus
                0x00465d60                CommandHistory
                0x00465d70                EOF_Reached
                0x00465d80                shellWindowWidth
                0x00465d90                ClientAreaInfo
                0x00465da0                g_current_disk_id
                0x00465db0                BufferInfo
                0x00465dc0                shellError
                0x00465dd0                shellWindowHeight
                0x00465de0                lineList
                0x00467de0                root
                0x00467df0                CurrentCommand
                0x00467e00                shell_info
                0x00467e20                shellScreenBufferMaxColumns
                0x00467e30                g_current_workingdirectory_id
                0x00467e40                shell_window_x
                0x00467e50                i2Window
                0x00467e60                rect
                0x00467e70                backgroung_color
                0x00467e80                shell_name
                0x00467e90                shellMaxRows
                0x00467ea0                screenbufferList
                0x00467ec0                foregroung_color
                0x00467ed0                pwd
                0x00467ee0                CurrentWindow
                0x00467ef0                dummycompiler
                0x00467f00                topbar_scrollbarWindow
                0x00467f10                current_semaphore
                0x00467f20                g_current_volume_id
                0x00467f30                ShellHook
                0x00467f40                topbar_checkboxWindow
                0x00467f50                shellScreenBufferMaxRows
                0x00467f60                shellScreenWidth
                0x00467f70                screen_buffer_pos
                0x00467f80                shellScreenHeight
                0x00467f90                editboxWindow
                0x00467fa0                username
                0x00467fb0                screen_buffer_x
                0x00467fc0                screen_buffer
                0x00468f70                shell_window_y
                0x00468f80                terminal_rect
                0x00468f90                password
                0x00468fa0                CursorInfo
                0x00468fb0                shellMaxColumns
                0x00468fc0                i1Window
                0x00468fd0                screen_buffer_y
                0x00468fe0                topbar_editboxWindow
                0x00468ff0                topbarWindow
                0x00469000                ApplicationInfo
                0x00469010                current_workingdiretory_string
 COMMON         0x00469030      0x8f0 stdlib.o
                0x00469030                current_mmblock
                0x00469040                mm_prev_pointer
                0x00469050                heap_end
                0x00469060                g_available_heap
                0x00469070                heap_start
                0x00469080                heapCount
                0x00469090                HEAP_START
                0x004690a0                g_heap_pointer
                0x004690b0                heapList
                0x004694b0                HEAP_SIZE
                0x004694c0                last_size
                0x004694d0                last_valid
                0x004694e0                mmblockList
                0x004698e0                libcHeap
                0x004698f0                Heap
                0x00469900                mmblockCount
                0x00469910                HEAP_END
                0x00469920                end = .
                0x00469920                _end = .
                0x00469920                __end = .
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
