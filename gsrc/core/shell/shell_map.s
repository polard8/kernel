
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
 .text          0x004510a4     0x35d0 main.o
                0x00453160                shellPrompt
                0x00453b15                shellSendMessage
                0x00453350                shellTestThreads
                0x00453c7d                shellTaskList
                0x004512f4                shellProcedure
                0x00452b55                shellShell
                0x00453f4c                shellShowProcessHeapPointer
                0x0045311f                shellThread
                0x00454359                concat
                0x00452cb2                shellInit
                0x00453de4                shellShowPPID
                0x00453fb4                shellShowKernelHeapPointer
                0x00453bda                shellInitializeWorkingDiretoryString
                0x0045151a                shellWaitCmd
                0x00453225                shellShowScreenBuffer
                0x004545ef                shell_pathname_backup
                0x004510b3                GramadoMain
                0x004545a4                shellInitFilename
                0x00453f10                shellShowDesktopID
                0x00453628                shellInsertCharXY
                0x00454559                shellInitPathname
                0x00453672                shellInsertCharPos
                0x004542ed                die
                0x00454080                shellShowPCIInfo
                0x00453b66                shellExit
                0x00451532                shellCompare
                0x004531e3                shellClearBuffer
                0x004544d3                absolute_pathname
                0x0045341a                shellRefreshScreen
                0x00454231                feedterminalDialog
                0x00454438                shellExecuteThisScript
                0x004533e0                shellClearScreen
                0x004539e4                shellShowSystemInfo
                0x004536aa                shellInsertNextChar
                0x004540d8                shell_fntos
                0x00454054                shellShowMemoryInfo
                0x00453284                shellTestLoadFile
                0x00453821                move_to
                0x004536f3                shellInsertCR
                0x00453910                shellShowMetrics
                0x00453e5c                shellShowGID
                0x0045349c                shellScroll
                0x004540ac                shellShowKernelInfo
                0x00453b77                shellUpdateWorkingDiretoryString
                0x00453773                shellInsertNullTerminator
                0x00453e20                shellShowUID
                0x00453733                shellInsertLF
                0x00453c70                shellUpdateCurrentDirectoryID
                0x00453b3d                shell_memcpy_bytes
                0x004530f5                shellSetCursor
                0x004541c7                shell_gramado_core_init_execve
                0x00453846                shellShowInfo
                0x00454028                shellShowVolumeInfo
                0x00453a52                shellShowWindowInfo
                0x004510a4                quit
                0x00453da8                shellShowPID
                0x004543f1                error
                0x00453e98                shellShowUserSessionID
                0x00453ed4                shellShowWindowStationID
                0x0045432e                xmalloc
                0x00453ffc                shellShowDiskInfo
                0x0045314c                shellTree
                0x00453138                shellHelp
                0x004537b3                shellTestMBR
 .text          0x00454674      0x7b0 shellui.o
                0x00454c70                shellTestDisplayBMP
                0x004548d0                shellCreateEditBox
                0x00454bfb                shellDisplayBMP
                0x00454763                shellTopbarProcedure
                0x00454ce6                bmpDisplayBMP
                0x0045497e                shellCreateTopBar
                0x00454674                shellui_fntos
 .text          0x00454e24     0x1980 api.o
                0x00455bd9                APIShowCurrentProcessInfo
                0x0045639d                api_getchar
                0x004553c6                system11
                0x0045546b                refresh_buffer
                0x00455abb                APISetFocus
                0x00455429                system14
                0x00455750                apiInitBackground
                0x0045598f                APICreateWindow
                0x00456158                apiBeginPaint
                0x00455755                MessageBox
                0x00455c57                APIreplace_window
                0x0045619f                apiGetSystemMetrics
                0x00455408                system13
                0x0045600f                apiDown
                0x00455d27                apiExit
                0x004560a7                enterCriticalSection
                0x004562e4                gramadocore_init_execve
                0x00455f95                apiFOpen
                0x0045527c                system1
                0x00455300                system5
                0x00455e0d                api_refresh_screen
                0x00456324                apiDialog
                0x00455e99                apiGetCursorY
                0x004556fb                carrega_bitmap_16x16
                0x00456100                exitCriticalSection
                0x00454e24                system_call
                0x0045605b                apiUp
                0x00454e4c                apiSystem
                0x004562b8                api_get_window_with_text_input
                0x0045544a                system15
                0x00455b6b                APISetActiveWindow
                0x00455ef1                apiSetClientAreaRect
                0x00455c2e                APIredraw_window
                0x00455f43                apiCreateThread
                0x00455697                SetNextWindowProcedure
                0x00455e6d                apiGetCursorX
                0x00455667                chama_procedimento
                0x0045577e                call_kernel
                0x00455a37                APIRegisterWindow
                0x00455d83                api_strncmp
                0x00455ca9                APIminimize_window
                0x0045529d                system2
                0x004552be                system3
                0x004561f1                api_get_current_keyboard_responder
                0x00455f1a                apiCreateProcess
                0x00455afd                APIGetFocus
                0x00455342                system7
                0x00455321                system6
                0x00456195                apiDefDialog
                0x00455a79                APICloseWindow
                0x0045612c                initializeCriticalSection
                0x004553a5                system10
                0x004556c7                set_cursor
                0x00455c80                APImaximize_window
                0x0045631a                execve
                0x00455de1                refresh_screen
                0x004563c9                apiDisplayBMP
                0x004558fe                call_gui
                0x00455384                system9
                0x004562ee                fork
                0x004561c8                api_set_current_keyboard_responder
                0x00455c05                APIresize_window
                0x00456162                apiEndPaint
                0x004556f6                put_char
                0x00455602                print_string
                0x00455ec5                apiGetClientAreaRect
                0x00455638                edit_box
                0x00455d52                kill
                0x00455e17                apiReboot
                0x00455724                apiShutDown
                0x0045621d                api_set_current_mouse_responder
                0x00455cd2                APIget_foregroung_window
                0x004552df                system4
                0x00455fcf                apiSaveFile
                0x00455e43                apiSetCursor
                0x004553e7                system12
                0x00455607                vsync
                0x00455363                system8
                0x00456272                api_set_window_with_text_input
                0x00455bad                APIGetActiveWindow
                0x00456246                api_get_current_mouse_responder
                0x00455d57                dead_thread_collector
                0x00455f6c                apiStartThread
                0x00455b29                APIKillFocus
                0x00455cfe                APIset_foregroung_window
                0x0045616c                apiPutChar
 .text          0x004567a4     0x1110 stdio.o
                0x004570eb                putchar
                0x004567a4                stdio_fntos
                0x004570a7                sprintf
                0x0045777c                feof
                0x0045785a                fputc
                0x00457631                fputs
                0x004577ba                ferror
                0x004572d7                input
                0x00456991                scroll
                0x004572cd                printf_main
                0x004576a6                gets
                0x00457117                outbyte
                0x00456b3b                app_print
                0x0045754c                fflush
                0x004575bc                fprintf
                0x004573ce                stdio_system_call
                0x004568f9                fopen
                0x004573f6                getchar
                0x00457428                stdioInitialize
                0x0045771b                fgetc
                0x00456893                fclose
                0x004577e0                fseek
                0x0045729a                _outbyte
                0x0045708c                printf
                0x00456acf                app_clear
 .text          0x004578b4      0xae0 stdlib.o
                0x00457baa                FreeHeap
                0x004578dc                rtGetHeapStart
                0x00457df1                free
                0x004578b4                stdlib_system_call
                0x00457d93                rand
                0x00457d0a                stdlibInitMM
                0x00457bb4                heapInit
                0x00458289                __findenv
                0x004578f0                rtGetHeapPointer
                0x004578fa                rtGetAvailableHeap
                0x00457d6a                libcInitRT
                0x00457904                heapSetLibcHeap
                0x00458354                getenv
                0x00457db0                malloc
                0x00457b97                AllocateHeapEx
                0x004579ab                AllocateHeap
                0x00458202                stdlib_strncmp
                0x00458260                exit
                0x004578e6                rtGetHeapEnd
                0x00457df6                system
 .text          0x00458394      0x4a0 string.o
                0x004585fb                strcspn
                0x0045855e                strcat
                0x00458394                strcmp
                0x004585b5                bzero
                0x0045873b                strtok_r
                0x004584f1                memcpy
                0x004584c8                memoryZeroMemory
                0x0045858e                bcopy
                0x0045852e                strcpy
                0x0045869b                strspn
                0x00458810                strtok
                0x0045844d                str_cmp
                0x004583ef                strncmp
                0x004585d0                strlen
 .text          0x00458834       0x90 conio.o
                0x004588a2                getche
                0x00458834                putch
                0x00458857                cputs
                0x0045888b                getch
 .text          0x004588c4      0x1a0 builtins.o
                0x00458a29                pwd_builtins
                0x004589c3                getuid_builtins
                0x004589d5                getgid_builtins
                0x0045894c                echo_builtins
                0x00458908                dir_builtins
                0x0045897f                exit_builtins
                0x0045899f                getpid_builtins
                0x004588f9                copy_builtins
                0x004589b1                getppid_builtins
                0x0045896b                exec_builtins
                0x004588d8                cls_builtins
                0x004588fe                date_builtins
                0x00458903                del_builtins
                0x004588c4                cd_buitins
                0x004589e7                help_builtins
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458a64      0x59c 00

.rdata          0x00459000     0x2900
 .rdata         0x00459000      0x4e0 builtins.o
 .rdata         0x004594e0       0x10 conio.o
 .rdata         0x004594f0      0x460 stdlib.o
 .rdata         0x00459950       0x40 stdio.o
 .rdata         0x00459990      0x320 api.o
 .rdata         0x00459cb0      0x720 shellui.o
 .rdata         0x0045a3d0     0x1480 main.o
 .rdata         0x0045b850       0xb0 crt0.o

.data           0x0045b900     0x1700
                0x0045b900                data = .
                0x0045b900                _data = .
                0x0045b900                __data = .
 *(.data)
 .data          0x0045b900       0x30 crt0.o
 .data          0x0045b930      0x4e0 main.o
                0x0045bdf0                running
                0x0045bdf4                primary_prompt
                0x0045bdfc                shell_config_file
                0x0045bdf8                secondary_prompt
 .data          0x0045be10      0x4c0 shellui.o
 .data          0x0045c2d0      0x440 api.o
 .data          0x0045c710        0x0 stdio.o
 .data          0x0045c710       0x10 stdlib.o
 .data          0x0045c720        0x0 string.o
 .data          0x0045c720        0x0 conio.o
 .data          0x0045c720      0x4c0 builtins.o
                0x0045d000                . = ALIGN (0x1000)
 *fill*         0x0045cbe0      0x420 00

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
 .bss           0x0045d210     0x8010 stdlib.o
                0x0045d210                environ
 .bss           0x00465220       0x10 string.o
 .bss           0x00465230        0x0 conio.o
 .bss           0x00465230       0xd0 builtins.o
                0x00466000                . = ALIGN (0x1000)
 *fill*         0x00465300      0xd00 00
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
