
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
 .text          0x004510a4     0x2e50 main.o
                0x00452d1c                shellPrompt
                0x004535fe                shellSendMessage
                0x00452eed                shellTestThreads
                0x004536dc                shellTaskList
                0x004513d7                shellProcedure
                0x00452729                shellShell
                0x004539ab                shellShowProcessHeapPointer
                0x00452cdb                shellThread
                0x00453d6c                concat
                0x0045286e                shellInit
                0x00453843                shellShowPPID
                0x00453a13                shellShowKernelHeapPointer
                0x004515ec                shellWaitCmd
                0x00452dd5                shellShowScreenBuffer
                0x004510b3                GramadoMain
                0x0045396f                shellShowDesktopID
                0x0045317d                shellInsertCharXY
                0x004531c7                shellInsertCharPos
                0x00453d00                die
                0x00453a87                shellShowPCIInfo
                0x00451604                shellCompare
                0x00452d93                shellClearBuffer
                0x00452fc3                shellRefreshScreen
                0x00453c44                feedterminalDialog
                0x00453e4b                shellExecuteThisScript
                0x00452f7d                shellClearScreen
                0x004534e5                shellShowSystemInfo
                0x004531ff                shellInsertNextChar
                0x00453adf                shell_fntos
                0x00453a5b                shellShowMemoryInfo
                0x00452e5a                shellTestLoadFile
                0x004532f6                move_to
                0x0045322b                shellInsertCR
                0x004533e5                shellShowMetrics
                0x004538bb                shellShowGID
                0x00453051                shellScroll
                0x00453ab3                shellShowKernelInfo
                0x0045364f                shellUpdateWorkingDiretoryString
                0x00453269                shellInsertNullTerminator
                0x0045387f                shellShowUID
                0x0045324a                shellInsertLF
                0x004536cf                shellUpdateCurrentDirectoryID
                0x00453626                shell_memcpy_bytes
                0x00452cb1                shellSetCursor
                0x00453bce                shell_gramado_core_init_execve
                0x0045331b                shellShowInfo
                0x00453553                shellShowWindowInfo
                0x004510a4                quit
                0x00453807                shellShowPID
                0x00453e04                error
                0x004538f7                shellShowUserSessionID
                0x00453933                shellShowWindowStationID
                0x00453d41                xmalloc
                0x00452d08                shellTree
                0x00452cf4                shellHelp
                0x00453288                shellTestMBR
 .text          0x00453ef4      0x7b0 shellui.o
                0x004544f0                shellTestDisplayBMP
                0x00454150                shellCreateEditBox
                0x0045447b                shellDisplayBMP
                0x00453fe3                shellTopbarProcedure
                0x00454566                bmpDisplayBMP
                0x004541fe                shellCreateTopBar
                0x00453ef4                shellui_fntos
 .text          0x004546a4     0x1910 api.o
                0x00455459                APIShowCurrentProcessInfo
                0x00455bab                api_getchar
                0x00454c46                system11
                0x00454ceb                refresh_buffer
                0x0045533b                APISetFocus
                0x00454ca9                system14
                0x00454fd0                apiInitBackground
                0x0045520f                APICreateWindow
                0x00455988                apiBeginPaint
                0x00454fd5                MessageBox
                0x004554d7                APIreplace_window
                0x004559cf                apiGetSystemMetrics
                0x00454c88                system13
                0x0045583f                apiDown
                0x004555a7                apiExit
                0x004558d7                enterCriticalSection
                0x00455b14                gramadocore_init_execve
                0x00455815                apiFOpen
                0x00454afc                system1
                0x00454b80                system5
                0x0045568d                api_refresh_screen
                0x00455b32                apiDialog
                0x00455719                apiGetCursorY
                0x00454f7b                carrega_bitmap_16x16
                0x00455930                exitCriticalSection
                0x004546a4                system_call
                0x0045588b                apiUp
                0x004546cc                apiSystem
                0x00455ae8                api_get_window_with_text_input
                0x00454cca                system15
                0x004553eb                APISetActiveWindow
                0x00455771                apiSetClientAreaRect
                0x004554ae                APIredraw_window
                0x004557c3                apiCreateThread
                0x00454f17                SetNextWindowProcedure
                0x004556ed                apiGetCursorX
                0x00454ee7                chama_procedimento
                0x00454ffe                call_kernel
                0x004552b7                APIRegisterWindow
                0x00455603                api_strncmp
                0x00455529                APIminimize_window
                0x00454b1d                system2
                0x00454b3e                system3
                0x00455a21                api_get_current_keyboard_responder
                0x0045579a                apiCreateProcess
                0x0045537d                APIGetFocus
                0x00454bc2                system7
                0x00454ba1                system6
                0x004559c5                apiDefDialog
                0x004552f9                APICloseWindow
                0x0045595c                initializeCriticalSection
                0x00454c25                system10
                0x00454f47                set_cursor
                0x00455500                APImaximize_window
                0x00455b28                execve
                0x00455661                refresh_screen
                0x00455bd7                apiDisplayBMP
                0x0045517e                call_gui
                0x00454c04                system9
                0x00455b1e                fork
                0x004559f8                api_set_current_keyboard_responder
                0x00455485                APIresize_window
                0x00455992                apiEndPaint
                0x00454f76                put_char
                0x00454e82                print_string
                0x00455745                apiGetClientAreaRect
                0x00454eb8                edit_box
                0x004555d2                kill
                0x00455697                apiReboot
                0x00454fa4                apiShutDown
                0x00455a4d                api_set_current_mouse_responder
                0x00455552                APIget_foregroung_window
                0x00454b5f                system4
                0x004556c3                apiSetCursor
                0x00454c67                system12
                0x00454e87                vsync
                0x00454be3                system8
                0x00455aa2                api_set_window_with_text_input
                0x0045542d                APIGetActiveWindow
                0x00455a76                api_get_current_mouse_responder
                0x004555d7                dead_thread_collector
                0x004557ec                apiStartThread
                0x004553a9                APIKillFocus
                0x0045557e                APIset_foregroung_window
                0x0045599c                apiPutChar
 .text          0x00455fb4     0x1110 stdio.o
                0x004568fb                putchar
                0x00455fb4                stdio_fntos
                0x004568b7                sprintf
                0x00456f8c                feof
                0x0045706a                fputc
                0x00456e41                fputs
                0x00456fca                ferror
                0x00456ae7                input
                0x004561a1                scroll
                0x00456add                printf_main
                0x00456eb6                gets
                0x00456927                outbyte
                0x0045634b                app_print
                0x00456d5c                fflush
                0x00456dcc                fprintf
                0x00456bde                stdio_system_call
                0x00456109                fopen
                0x00456c06                getchar
                0x00456c38                stdioInitialize
                0x00456f2b                fgetc
                0x004560a3                fclose
                0x00456ff0                fseek
                0x00456aaa                _outbyte
                0x0045689c                printf
                0x004562df                app_clear
 .text          0x004570c4      0x9b0 stdlib.o
                0x004573a7                FreeHeap
                0x004570ec                rtGetHeapStart
                0x004575ee                free
                0x004570c4                stdlib_system_call
                0x00457590                rand
                0x00457507                stdlibInitMM
                0x004573b1                heapInit
                0x00457100                rtGetHeapPointer
                0x0045710a                rtGetAvailableHeap
                0x00457567                libcInitRT
                0x00457114                heapSetLibcHeap
                0x004575ad                malloc
                0x00457394                AllocateHeapEx
                0x004571bb                AllocateHeap
                0x004579e5                stdlib_strncmp
                0x00457a43                exit
                0x004570f6                rtGetHeapEnd
                0x004575f3                system
 .text          0x00457a74      0x4a0 string.o
                0x00457cdb                strcspn
                0x00457c3e                strcat
                0x00457a74                strcmp
                0x00457c95                bzero
                0x00457e1b                strtok_r
                0x00457bd1                memcpy
                0x00457ba8                memoryZeroMemory
                0x00457c6e                bcopy
                0x00457c0e                strcpy
                0x00457d7b                strspn
                0x00457ef0                strtok
                0x00457b2d                str_cmp
                0x00457acf                strncmp
                0x00457cb0                strlen
 .text          0x00457f14       0x90 conio.o
                0x00457f82                getche
                0x00457f14                putch
                0x00457f37                cputs
                0x00457f6b                getch
 .text          0x00457fa4      0x1b0 builtins.o
                0x0045810e                pwd_builtins
                0x004580a8                getuid_builtins
                0x004580ba                getgid_builtins
                0x00458031                echo_builtins
                0x00457fed                dir_builtins
                0x00458064                exit_builtins
                0x00458084                getpid_builtins
                0x00457fde                copy_builtins
                0x00458096                getppid_builtins
                0x00458050                exec_builtins
                0x00457fb8                cls_builtins
                0x00457fe3                date_builtins
                0x00457fe8                del_builtins
                0x00457fa4                cd_buitins
                0x004580cc                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458154      0xeac 00

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
