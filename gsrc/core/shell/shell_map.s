
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
 .text          0x004510a4     0x31d0 main.o
                0x00453025                shellPrompt
                0x00453931                shellSendMessage
                0x004531b8                shellTestThreads
                0x00453a0f                shellTaskList
                0x004513c4                shellProcedure
                0x00452a22                shellShell
                0x00453cde                shellShowProcessHeapPointer
                0x00452fe4                shellThread
                0x004540eb                concat
                0x00452b27                shellInit
                0x00453b76                shellShowPPID
                0x00453d46                shellShowKernelHeapPointer
                0x004515d9                shellWaitCmd
                0x004530de                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x00453ca2                shellShowDesktopID
                0x00453430                shellInsertCharXY
                0x0045347a                shellInsertCharPos
                0x0045407f                die
                0x00453e12                shellShowPCIInfo
                0x004515f1                shellCompare
                0x0045309c                shellClearBuffer
                0x00453282                shellRefreshScreen
                0x00453fc3                feedterminalDialog
                0x004541ca                shellExecuteThisScript
                0x00453248                shellClearScreen
                0x0045380c                shellShowSystemInfo
                0x004534b2                shellInsertNextChar
                0x00453e6a                shell_fntos
                0x00453de6                shellShowMemoryInfo
                0x0045313d                shellTestLoadFile
                0x00453629                move_to
                0x004534fb                shellInsertCR
                0x00453718                shellShowMetrics
                0x00453bee                shellShowGID
                0x00453304                shellScroll
                0x00453e3e                shellShowKernelInfo
                0x00453982                shellUpdateWorkingDiretoryString
                0x0045357b                shellInsertNullTerminator
                0x00453bb2                shellShowUID
                0x0045353b                shellInsertLF
                0x00453a02                shellUpdateCurrentDirectoryID
                0x00453959                shell_memcpy_bytes
                0x00452fba                shellSetCursor
                0x00453f59                shell_gramado_core_init_execve
                0x0045364e                shellShowInfo
                0x00453dba                shellShowVolumeInfo
                0x0045387a                shellShowWindowInfo
                0x004510a4                quit
                0x00453b3a                shellShowPID
                0x00454183                error
                0x00453c2a                shellShowUserSessionID
                0x00453c66                shellShowWindowStationID
                0x004540c0                xmalloc
                0x00453d8e                shellShowDiskInfo
                0x00453011                shellTree
                0x00452ffd                shellHelp
                0x004535bb                shellTestMBR
 .text          0x00454274      0x7b0 shellui.o
                0x00454870                shellTestDisplayBMP
                0x004544d0                shellCreateEditBox
                0x004547fb                shellDisplayBMP
                0x00454363                shellTopbarProcedure
                0x004548e6                bmpDisplayBMP
                0x0045457e                shellCreateTopBar
                0x00454274                shellui_fntos
 .text          0x00454a24     0x1980 api.o
                0x004557d9                APIShowCurrentProcessInfo
                0x00455f9d                api_getchar
                0x00454fc6                system11
                0x0045506b                refresh_buffer
                0x004556bb                APISetFocus
                0x00455029                system14
                0x00455350                apiInitBackground
                0x0045558f                APICreateWindow
                0x00455d58                apiBeginPaint
                0x00455355                MessageBox
                0x00455857                APIreplace_window
                0x00455d9f                apiGetSystemMetrics
                0x00455008                system13
                0x00455c0f                apiDown
                0x00455927                apiExit
                0x00455ca7                enterCriticalSection
                0x00455ee4                gramadocore_init_execve
                0x00455b95                apiFOpen
                0x00454e7c                system1
                0x00454f00                system5
                0x00455a0d                api_refresh_screen
                0x00455f24                apiDialog
                0x00455a99                apiGetCursorY
                0x004552fb                carrega_bitmap_16x16
                0x00455d00                exitCriticalSection
                0x00454a24                system_call
                0x00455c5b                apiUp
                0x00454a4c                apiSystem
                0x00455eb8                api_get_window_with_text_input
                0x0045504a                system15
                0x0045576b                APISetActiveWindow
                0x00455af1                apiSetClientAreaRect
                0x0045582e                APIredraw_window
                0x00455b43                apiCreateThread
                0x00455297                SetNextWindowProcedure
                0x00455a6d                apiGetCursorX
                0x00455267                chama_procedimento
                0x0045537e                call_kernel
                0x00455637                APIRegisterWindow
                0x00455983                api_strncmp
                0x004558a9                APIminimize_window
                0x00454e9d                system2
                0x00454ebe                system3
                0x00455df1                api_get_current_keyboard_responder
                0x00455b1a                apiCreateProcess
                0x004556fd                APIGetFocus
                0x00454f42                system7
                0x00454f21                system6
                0x00455d95                apiDefDialog
                0x00455679                APICloseWindow
                0x00455d2c                initializeCriticalSection
                0x00454fa5                system10
                0x004552c7                set_cursor
                0x00455880                APImaximize_window
                0x00455f1a                execve
                0x004559e1                refresh_screen
                0x00455fc9                apiDisplayBMP
                0x004554fe                call_gui
                0x00454f84                system9
                0x00455eee                fork
                0x00455dc8                api_set_current_keyboard_responder
                0x00455805                APIresize_window
                0x00455d62                apiEndPaint
                0x004552f6                put_char
                0x00455202                print_string
                0x00455ac5                apiGetClientAreaRect
                0x00455238                edit_box
                0x00455952                kill
                0x00455a17                apiReboot
                0x00455324                apiShutDown
                0x00455e1d                api_set_current_mouse_responder
                0x004558d2                APIget_foregroung_window
                0x00454edf                system4
                0x00455bcf                apiSaveFile
                0x00455a43                apiSetCursor
                0x00454fe7                system12
                0x00455207                vsync
                0x00454f63                system8
                0x00455e72                api_set_window_with_text_input
                0x004557ad                APIGetActiveWindow
                0x00455e46                api_get_current_mouse_responder
                0x00455957                dead_thread_collector
                0x00455b6c                apiStartThread
                0x00455729                APIKillFocus
                0x004558fe                APIset_foregroung_window
                0x00455d6c                apiPutChar
 .text          0x004563a4     0x1110 stdio.o
                0x00456ceb                putchar
                0x004563a4                stdio_fntos
                0x00456ca7                sprintf
                0x0045737c                feof
                0x0045745a                fputc
                0x00457231                fputs
                0x004573ba                ferror
                0x00456ed7                input
                0x00456591                scroll
                0x00456ecd                printf_main
                0x004572a6                gets
                0x00456d17                outbyte
                0x0045673b                app_print
                0x0045714c                fflush
                0x004571bc                fprintf
                0x00456fce                stdio_system_call
                0x004564f9                fopen
                0x00456ff6                getchar
                0x00457028                stdioInitialize
                0x0045731b                fgetc
                0x00456493                fclose
                0x004573e0                fseek
                0x00456e9a                _outbyte
                0x00456c8c                printf
                0x004566cf                app_clear
 .text          0x004574b4      0x9b0 stdlib.o
                0x00457797                FreeHeap
                0x004574dc                rtGetHeapStart
                0x004579de                free
                0x004574b4                stdlib_system_call
                0x00457980                rand
                0x004578f7                stdlibInitMM
                0x004577a1                heapInit
                0x004574f0                rtGetHeapPointer
                0x004574fa                rtGetAvailableHeap
                0x00457957                libcInitRT
                0x00457504                heapSetLibcHeap
                0x0045799d                malloc
                0x00457784                AllocateHeapEx
                0x004575ab                AllocateHeap
                0x00457dd5                stdlib_strncmp
                0x00457e33                exit
                0x004574e6                rtGetHeapEnd
                0x004579e3                system
 .text          0x00457e64      0x4a0 string.o
                0x004580cb                strcspn
                0x0045802e                strcat
                0x00457e64                strcmp
                0x00458085                bzero
                0x0045820b                strtok_r
                0x00457fc1                memcpy
                0x00457f98                memoryZeroMemory
                0x0045805e                bcopy
                0x00457ffe                strcpy
                0x0045816b                strspn
                0x004582e0                strtok
                0x00457f1d                str_cmp
                0x00457ebf                strncmp
                0x004580a0                strlen
 .text          0x00458304       0x90 conio.o
                0x00458372                getche
                0x00458304                putch
                0x00458327                cputs
                0x0045835b                getch
 .text          0x00458394      0x1a0 builtins.o
                0x004584f9                pwd_builtins
                0x00458493                getuid_builtins
                0x004584a5                getgid_builtins
                0x0045841c                echo_builtins
                0x004583d8                dir_builtins
                0x0045844f                exit_builtins
                0x0045846f                getpid_builtins
                0x004583c9                copy_builtins
                0x00458481                getppid_builtins
                0x0045843b                exec_builtins
                0x004583a8                cls_builtins
                0x004583ce                date_builtins
                0x004583d3                del_builtins
                0x00458394                cd_buitins
                0x004584b7                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458534      0xacc 00

.rdata          0x00459000     0x26f0
 .rdata         0x00459000      0x480 builtins.o
 .rdata         0x00459480       0x10 conio.o
 .rdata         0x00459490      0x430 stdlib.o
 .rdata         0x004598c0       0x40 stdio.o
 .rdata         0x00459900      0x320 api.o
 .rdata         0x00459c20      0x6c0 shellui.o
 .rdata         0x0045a2e0     0x1360 main.o
 .rdata         0x0045b640       0xb0 crt0.o

.data           0x0045b6f0     0x1910
                0x0045b6f0                data = .
                0x0045b6f0                _data = .
                0x0045b6f0                __data = .
 *(.data)
 .data          0x0045b6f0       0x30 crt0.o
 .data          0x0045b720      0x480 main.o
                0x0045bb80                running
                0x0045bb84                shell_config_file
 .data          0x0045bba0      0x460 shellui.o
 .data          0x0045c000      0x440 api.o
 .data          0x0045c440        0x0 stdio.o
 .data          0x0045c440       0x10 stdlib.o
 .data          0x0045c450        0x0 string.o
 .data          0x0045c450        0x0 conio.o
 .data          0x0045c450      0x460 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045c8b0      0x750 00

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
