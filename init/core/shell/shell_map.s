
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
password            0xb               main.o
objectY             0x4               main.o
CurrentWindow       0x4               crt0.o
backgroung_color    0x4               crt0.o
wsWindowHeight      0x4               crt0.o
stdout              0x4               crt0.o
menu_button         0x4               crt0.o
screen_buffer_y     0x4               crt0.o
wlFullScreenLeft    0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
username            0xb               main.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
close_button        0x4               crt0.o
libcHeap            0x4               stdlib.o
smCursorHeight      0x4               crt0.o
pathname_buffer     0x40              crt0.o
deltaY              0x4               main.o
textCurrentRow      0x4               crt0.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
app4_button         0x4               crt0.o
shellStatus         0x4               main.o
dialogbox_button2   0x4               api.o
smMousePointerWidth
                    0x4               crt0.o
smMousePointerHeight
                    0x4               crt0.o
filename_buffer     0xb               crt0.o
Streams             0x80              crt0.o
messagebox_button1  0x4               api.o
textWheelDelta      0x4               crt0.o
app1_button         0x4               crt0.o
g_using_gui         0x4               crt0.o
wlMinRows           0x4               crt0.o
current_volume_string
                    0x4               crt0.o
ShellMetrics        0x4               crt0.o
smCharHeight        0x4               crt0.o
ApplicationInfo     0x4               crt0.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
foregroung_color    0x4               crt0.o
prompt_out          0x400             crt0.o
shell_info          0x18              crt0.o
BufferInfo          0x4               crt0.o
ShellHook           0x4               crt0.o
lineList            0x2000            crt0.o
wlMaxWindowHeight   0x4               crt0.o
wlMaxRows           0x4               crt0.o
textCurrentCol      0x4               crt0.o
shell_environment   0x4               main.o
textSavedCol        0x4               crt0.o
current_volume_id   0x4               crt0.o
smCharWidth         0x4               crt0.o
g_current_workingdirectory_id
                    0x4               crt0.o
g_available_heap    0x4               stdlib.o
wlFullScreenHeight  0x4               crt0.o
textTopRow          0x4               crt0.o
g_heap_pointer      0x4               stdlib.o
textMinWheelDelta   0x4               crt0.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
mmblockCount        0x4               stdlib.o
dialogbox_button1   0x4               api.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
pathname_lenght     0x4               crt0.o
last_size           0x4               stdlib.o
wlMinWindowHeight   0x4               crt0.o
textBottomRow       0x4               crt0.o
wlMinColumns        0x4               crt0.o
prompt_status       0x4               crt0.o
objectX             0x4               main.o
pwd_initialized     0x4               crt0.o
root                0x4               crt0.o
CurrentCommand      0x4               crt0.o
shell_name          0x4               main.o
screen_buffer_x     0x4               crt0.o
wlMinWindowWidth    0x4               crt0.o
CommandHistory      0x4               crt0.o
app3_button         0x4               crt0.o
prompt_err          0x400             crt0.o
pwd                 0x4               crt0.o
screen_buffer       0xfa1             crt0.o
reboot_button       0x4               crt0.o
dummycompiler       0x4               crt0.o
smScreenWidth       0x4               crt0.o
textMaxWheelDelta   0x4               crt0.o
CursorInfo          0x4               crt0.o
app2_button         0x4               crt0.o
smScreenHeight      0x4               crt0.o
wlMaxWindowWidth    0x4               crt0.o
heap_end            0x4               stdlib.o
screen_buffer_pos   0x4               crt0.o
build_version       0x4               main.o
smCursorWidth       0x4               crt0.o
wpWindowLeft        0x4               crt0.o
terminal_rect       0x10              crt0.o
stderr              0x4               crt0.o
wlFullScreenTop     0x4               crt0.o
wsWindowWidth       0x4               crt0.o
g_current_disk_id   0x4               crt0.o
editboxWindow       0x4               crt0.o
deltaX              0x4               main.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
rect                0x4               crt0.o
taskbarWindow       0x4               crt0.o
EOF_Reached         0x4               crt0.o
g_cursor_y          0x4               crt0.o
screenbufferList    0x20              crt0.o
ClientAreaInfo      0x4               crt0.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
pathname_initilized
                    0x4               crt0.o
wpWindowTop         0x4               crt0.o
filename_lenght     0x4               crt0.o
current_semaphore   0x4               crt0.o
wlFullScreenWidth   0x4               crt0.o
shellError          0x4               main.o
dist_version        0x4               main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
wlMaxColumns        0x4               crt0.o
textSavedRow        0x4               crt0.o
heapCount           0x4               stdlib.o
filename_initilized
                    0x4               crt0.o
LINES               0x1580            crt0.o
HEAP_START          0x4               stdlib.o
g_current_volume_id
                    0x4               crt0.o
current_workingdiretory_string
                    0x20              crt0.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000451000     0xb000
                0x0000000000451000                code = .
                0x0000000000451000                _code = .
                0x0000000000451000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000451000       0x75 crt0.o
                0x0000000000451000                crt0
 .text          0x0000000000451075     0x4840 main.o
                0x0000000000451075                updateObject
                0x000000000045115d                quit
                0x000000000045116d                shmain
                0x00000000004514c6                shellProcedure
                0x0000000000451838                shellWaitCmd
                0x0000000000451852                shellCompare
                0x0000000000453347                shellInitSystemMetrics
                0x00000000004533e0                shellInitWindowLimits
                0x000000000045349e                shellInitWindowSizes
                0x00000000004534ea                shellInitWindowPosition
                0x0000000000453504                shellShell
                0x000000000045368b                shellInit
                0x000000000045377b                shellCheckPassword
                0x0000000000453acc                shellSetCursor
                0x0000000000453b07                shellThread
                0x0000000000453b84                shellShowExperienceMenu
                0x0000000000453b9d                shellShowTestsMenu
                0x0000000000453bb6                shellTree
                0x0000000000453bcf                shellPrompt
                0x0000000000453c58                shellClearBuffer
                0x0000000000453d01                shellShowScreenBuffer
                0x0000000000453d0f                shellTestLoadFile
                0x0000000000453d7b                shellTestThreads
                0x0000000000453e29                shellClearScreen
                0x0000000000453ea2                shellRefreshScreen
                0x0000000000453f44                shellRefreshLine
                0x0000000000453fba                shellRefreshChar
                0x0000000000454016                shellRefreshCurrentChar
                0x000000000045404e                shellScroll
                0x000000000045410b                shellInsertCharXY
                0x0000000000454160                shellGetCharXY
                0x0000000000454193                testScrollChar
                0x00000000004541c8                shellInsertNextChar
                0x000000000045426c                shellInsertCR
                0x0000000000454282                shellInsertLF
                0x0000000000454298                shellInsertNullTerminator
                0x00000000004542ae                shellTestMBR
                0x0000000000454309                move_to
                0x0000000000454335                shellShowInfo
                0x00000000004543e2                shellShowMetrics
                0x0000000000454494                shellShowSystemInfo
                0x000000000045450f                shellShowWindowInfo
                0x00000000004545d6                shellSendMessage
                0x00000000004545f2                shell_memcpy_bytes
                0x000000000045461e                shellExit
                0x0000000000454635                shellUpdateWorkingDiretoryString
                0x0000000000454694                shellInitializeWorkingDiretoryString
                0x000000000045471e                shellUpdateCurrentDirectoryID
                0x000000000045472c                shellTaskList
                0x000000000045484f                shellShowPID
                0x0000000000454879                shellShowPPID
                0x00000000004548a3                shellShowUID
                0x00000000004548d0                shellShowGID
                0x00000000004548fd                shellShowUserSessionID
                0x000000000045492a                shellShowWindowStationID
                0x0000000000454957                shellShowDesktopID
                0x0000000000454984                shellShowProcessHeapPointer
                0x00000000004549cb                shellShowKernelHeapPointer
                0x0000000000454a06                shellShowDiskInfo
                0x0000000000454a22                shellShowVolumeInfo
                0x0000000000454a3e                shellShowMemoryInfo
                0x0000000000454a5a                shellShowPCIInfo
                0x0000000000454a76                shellShowKernelInfo
                0x0000000000454a92                shell_fntos
                0x0000000000454bac                shell_gramado_core_init_execve
                0x0000000000454c17                feedterminalDialog
                0x0000000000454ca9                die
                0x0000000000454ceb                concat
                0x0000000000454da1                error
                0x0000000000454df5                fatal
                0x0000000000454e1f                save_string
                0x0000000000454e5b                shellExecuteThisScript
                0x0000000000454f08                absolute_pathname
                0x000000000045506e                shellInitPathname
                0x00000000004550be                shellInitFilename
                0x000000000045510e                shell_pathname_backup
                0x0000000000455185                shell_print_tokenList
                0x0000000000455229                is_bin
                0x000000000045529a                is_sh1
                0x000000000045530b                show_shell_version
                0x0000000000455335                shell_save_file
                0x00000000004554aa                textSetTopRow
                0x00000000004554b8                textGetTopRow
                0x00000000004554c2                textSetBottomRow
                0x00000000004554d0                textGetBottomRow
                0x00000000004554da                clearLine
                0x0000000000455548                testShowLines
                0x00000000004555e5                shellRefreshVisibleArea
                0x00000000004556bd                testChangeVisibleArea
                0x00000000004556e7                updateVisibleArea
                0x000000000045574a                shellSocketTest
 .text          0x00000000004558b5      0x73c shellui.o
                0x00000000004558b5                shellui_fntos
                0x00000000004559cf                shellTopbarProcedure
                0x0000000000455b28                shellCreateEditBox
                0x0000000000455b96                shellCreateMainWindow
                0x0000000000455c52                testCreateWindow
                0x0000000000455ce4                shellDisplayBMP
                0x0000000000455d58                shellDisplayBMPEx
                0x0000000000455de4                shellTestDisplayBMP
                0x0000000000455e46                bmpDisplayBMP
                0x0000000000455e63                shellTestButtons
 .text          0x0000000000455ff1     0x1e31 api.o
                0x0000000000455ff1                system_call
                0x0000000000456019                apiSystem
                0x0000000000456421                system1
                0x0000000000456442                system2
                0x0000000000456463                system3
                0x0000000000456484                system4
                0x00000000004564a5                system5
                0x00000000004564c6                system6
                0x00000000004564e7                system7
                0x0000000000456508                system8
                0x0000000000456529                system9
                0x000000000045654a                system10
                0x000000000045656b                system11
                0x000000000045658c                system12
                0x00000000004565ad                system13
                0x00000000004565ce                system14
                0x00000000004565ef                system15
                0x0000000000456610                refresh_buffer
                0x00000000004566ee                print_string
                0x00000000004566f4                vsync
                0x000000000045670e                edit_box
                0x000000000045672a                chama_procedimento
                0x0000000000456745                SetNextWindowProcedure
                0x0000000000456760                set_cursor
                0x000000000045677c                put_char
                0x0000000000456782                carrega_bitmap_16x16
                0x000000000045679b                apiShutDown
                0x00000000004567b2                apiInitBackground
                0x00000000004567b8                MessageBox
                0x0000000000456b32                mbProcedure
                0x0000000000456ba0                DialogBox
                0x0000000000456f1a                dbProcedure
                0x0000000000456f88                call_kernel
                0x0000000000457103                call_gui
                0x000000000045718f                APICreateWindow
                0x0000000000457209                APIRegisterWindow
                0x0000000000457236                APICloseWindow
                0x0000000000457263                APISetFocus
                0x0000000000457290                APIGetFocus
                0x00000000004572a5                APIKillFocus
                0x00000000004572d2                APISetActiveWindow
                0x00000000004572ff                APIGetActiveWindow
                0x0000000000457314                APIShowCurrentProcessInfo
                0x000000000045732a                APIresize_window
                0x0000000000457344                APIredraw_window
                0x000000000045735e                APIreplace_window
                0x0000000000457378                APImaximize_window
                0x0000000000457394                APIminimize_window
                0x00000000004573b0                APIupdate_window
                0x00000000004573cc                APIget_foregroung_window
                0x00000000004573e2                APIset_foregroung_window
                0x00000000004573fe                apiExit
                0x000000000045741b                kill
                0x0000000000457421                dead_thread_collector
                0x0000000000457437                api_strncmp
                0x000000000045749a                refresh_screen
                0x00000000004574b0                api_refresh_screen
                0x00000000004574bb                apiReboot
                0x00000000004574d1                apiSetCursor
                0x00000000004574e9                apiGetCursorX
                0x0000000000457501                apiGetCursorY
                0x0000000000457519                apiGetClientAreaRect
                0x0000000000457531                apiSetClientAreaRect
                0x0000000000457550                apiCreateProcess
                0x0000000000457569                apiCreateThread
                0x0000000000457582                apiStartThread
                0x000000000045759e                apiFOpen
                0x00000000004575ca                apiSaveFile
                0x000000000045761d                apiDown
                0x0000000000457670                apiUp
                0x00000000004576c3                enterCriticalSection
                0x00000000004576fe                exitCriticalSection
                0x0000000000457717                initializeCriticalSection
                0x0000000000457730                apiBeginPaint
                0x000000000045773b                apiEndPaint
                0x0000000000457746                apiPutChar
                0x0000000000457762                apiDefDialog
                0x000000000045776c                apiGetSystemMetrics
                0x000000000045778a                api_set_current_keyboard_responder
                0x00000000004577a9                api_get_current_keyboard_responder
                0x00000000004577c1                api_set_current_mouse_responder
                0x00000000004577e0                api_get_current_mouse_responder
                0x00000000004577f8                api_set_window_with_text_input
                0x000000000045783a                api_get_window_with_text_input
                0x0000000000457852                gramadocore_init_execve
                0x000000000045785c                fork
                0x0000000000457871                execve
                0x000000000045787b                apiDialog
                0x0000000000457907                api_getchar
                0x000000000045791f                apiDisplayBMP
                0x0000000000457d26                apiSendMessage
                0x0000000000457d5c                apiDrawText
                0x0000000000457d9b                apiGetWSScreenWindow
                0x0000000000457db3                apiGetWSMainWindow
                0x0000000000457dcb                apiCreateTimer
                0x0000000000457de8                apiGetSysTimeInfo
                0x0000000000457e06                apiShowWindow
 .text          0x0000000000457e22        0x0 ctype.o
 .text          0x0000000000457e22     0x275a stdio.o
                0x0000000000457e4d                stdio_atoi
                0x0000000000457f14                stdio_fntos
                0x000000000045803e                fclose
                0x00000000004580a4                fopen
                0x00000000004581d6                scroll
                0x00000000004582a4                puts
                0x0000000000458680                printf3
                0x000000000045869d                printf_atoi
                0x000000000045878d                printf_i2hex
                0x00000000004587ef                printf2
                0x0000000000458974                sprintf
                0x00000000004589c9                putchar
                0x00000000004589ea                outbyte
                0x0000000000458ba8                _outbyte
                0x0000000000458bd7                input
                0x0000000000458d2b                stdio_system_call
                0x0000000000458d53                getchar
                0x0000000000458d6b                stdioInitialize
                0x0000000000458f58                fflush
                0x0000000000458feb                fprintf
                0x000000000045905c                fputs
                0x00000000004590cd                gets
                0x0000000000459158                ungetc
                0x000000000045918f                ftell
                0x00000000004591b0                fileno
                0x00000000004591c8                fgetc
                0x0000000000459236                feof
                0x000000000045926b                ferror
                0x0000000000459286                fseek
                0x00000000004592f2                fputc
                0x0000000000459341                stdioSetCursor
                0x0000000000459359                stdioGetCursorX
                0x0000000000459371                stdioGetCursorY
                0x0000000000459389                scanf
                0x00000000004595c9                kvprintf
                0x000000000045a433                printf
                0x000000000045a45d                vfprintf
                0x000000000045a4d2                stdout_printf
                0x000000000045a4fe                stderr_printf
                0x000000000045a52a                perror
                0x000000000045a541                rewind
 .text          0x000000000045a57c      0xc2d stdlib.o
                0x000000000045a57c                stdlib_system_call
                0x000000000045a5a4                rtGetHeapStart
                0x000000000045a5ae                rtGetHeapEnd
                0x000000000045a5b8                rtGetHeapPointer
                0x000000000045a5c2                rtGetAvailableHeap
                0x000000000045a5cc                heapSetLibcHeap
                0x000000000045a67f                AllocateHeap
                0x000000000045a88f                AllocateHeapEx
                0x000000000045a8a5                FreeHeap
                0x000000000045a8af                heapInit
                0x000000000045aa42                stdlibInitMM
                0x000000000045aaa5                libcInitRT
                0x000000000045aac7                rand
                0x000000000045aae4                srand
                0x000000000045aaf2                xmalloc
                0x000000000045ab24                stdlib_die
                0x000000000045ab66                malloc
                0x000000000045aba2                free
                0x000000000045aba8                system
                0x000000000045af69                stdlib_strncmp
                0x000000000045afcd                exit
                0x000000000045afea                __findenv
                0x000000000045b0b5                getenv
                0x000000000045b0e2                atoi
 .text          0x000000000045b1a9      0x446 string.o
                0x000000000045b1a9                strcmp
                0x000000000045b20e                strncmp
                0x000000000045b271                memoryZeroMemory
                0x000000000045b298                memcpy
                0x000000000045b2d5                strcpy
                0x000000000045b309                strcat
                0x000000000045b338                bcopy
                0x000000000045b364                bzero
                0x000000000045b384                strlen
                0x000000000045b3b2                strcspn
                0x000000000045b451                strspn
                0x000000000045b4f0                strtok_r
                0x000000000045b5d7                strtok
 .text          0x000000000045b5ef       0x89 conio.o
                0x000000000045b5ef                putch
                0x000000000045b613                cputs
                0x000000000045b648                getch
                0x000000000045b660                getche
 .text          0x000000000045b678      0x16f builtins.o
                0x000000000045b678                cd_buitins
                0x000000000045b691                cls_builtins
                0x000000000045b69f                copy_builtins
                0x000000000045b6a5                date_builtins
                0x000000000045b6ab                del_builtins
                0x000000000045b6b1                dir_builtins
                0x000000000045b6ed                echo_builtins
                0x000000000045b709                exec_builtins
                0x000000000045b722                exit_builtins
                0x000000000045b748                getpid_builtins
                0x000000000045b75a                getppid_builtins
                0x000000000045b76c                getuid_builtins
                0x000000000045b77e                getgid_builtins
                0x000000000045b790                help_builtins
                0x000000000045b7cb                pwd_builtins
 .text          0x000000000045b7e7       0x49 desktop.o
                0x000000000045b7e7                desktopInitialize
                0x000000000045c000                . = ALIGN (0x1000)
 *fill*         0x000000000045b830      0x7d0 

.iplt           0x000000000045c000        0x0
 .iplt          0x000000000045c000        0x0 desktop.o

.rodata         0x000000000045c000     0x504f
 .rodata        0x000000000045c000      0x945 crt0.o
 *fill*         0x000000000045c945       0x1b 
 .rodata        0x000000000045c960     0x1cff main.o
 *fill*         0x000000000045e65f        0x1 
 .rodata        0x000000000045e660      0xb43 shellui.o
 *fill*         0x000000000045f1a3        0x1 
 .rodata        0x000000000045f1a4      0x39d api.o
 *fill*         0x000000000045f541       0x1f 
 .rodata        0x000000000045f560      0x100 ctype.o
                0x000000000045f560                _ctype
 .rodata        0x000000000045f660      0x374 stdio.o
                0x000000000045f840                hex2ascii_data
 .rodata        0x000000000045f9d4      0x47a stdlib.o
 .rodata        0x000000000045fe4e        0x6 conio.o
 *fill*         0x000000000045fe54        0xc 
 .rodata        0x000000000045fe60      0x8fa builtins.o
 *fill*         0x000000000046075a        0x6 
 .rodata        0x0000000000460760      0x8ef desktop.o

.eh_frame       0x0000000000461050     0x27f8
 .eh_frame      0x0000000000461050       0x34 crt0.o
 .eh_frame      0x0000000000461084      0xc7c main.o
                                        0xc94 (size before relaxing)
 .eh_frame      0x0000000000461d00      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000461e40      0xc6c api.o
                                        0xc84 (size before relaxing)
 .eh_frame      0x0000000000462aac      0x658 stdio.o
                                        0x670 (size before relaxing)
 .eh_frame      0x0000000000463104      0x304 stdlib.o
                                        0x31c (size before relaxing)
 .eh_frame      0x0000000000463408      0x1a0 string.o
                                        0x1b8 (size before relaxing)
 .eh_frame      0x00000000004635a8       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000463648      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x0000000000463828       0x20 desktop.o
                                         0x38 (size before relaxing)

.note.gnu.property
                0x0000000000463848       0x1c
 .note.gnu.property
                0x0000000000463848       0x1c desktop.o

.rel.dyn        0x0000000000463864        0x0
 .rel.got       0x0000000000463864        0x0 desktop.o
 .rel.iplt      0x0000000000463864        0x0 desktop.o
 .rel.text      0x0000000000463864        0x0 desktop.o

.data           0x0000000000463880     0x2780
                0x0000000000463880                data = .
                0x0000000000463880                _data = .
                0x0000000000463880                __data = .
 *(.data)
 .data          0x0000000000463880      0x4c4 crt0.o
 *fill*         0x0000000000463d44       0x1c 
 .data          0x0000000000463d60      0x538 main.o
                0x0000000000464200                running
                0x0000000000464204                primary_prompt
                0x0000000000464208                secondary_prompt
                0x000000000046420c                remember_on_history
                0x0000000000464210                current_command_number
                0x0000000000464214                bashrc_file
                0x0000000000464218                shell_config_file
                0x000000000046421c                deltaValue
                0x0000000000464220                long_args
 *fill*         0x0000000000464298        0x8 
 .data          0x00000000004642a0      0x4a0 shellui.o
 .data          0x0000000000464740      0x440 api.o
 .data          0x0000000000464b80        0x0 ctype.o
 .data          0x0000000000464b80        0x0 stdio.o
 .data          0x0000000000464b80        0x0 stdlib.o
 .data          0x0000000000464b80        0x0 string.o
 .data          0x0000000000464b80        0x0 conio.o
 .data          0x0000000000464b80      0x4a0 builtins.o
 .data          0x0000000000465020      0x4a8 desktop.o
                0x00000000004654c0                primary_desktop_folder
                0x00000000004654c4                secondary_desktop_folder
                0x0000000000466000                . = ALIGN (0x1000)
 *fill*         0x00000000004654c8      0xb38 

.got            0x0000000000466000        0x0
 .got           0x0000000000466000        0x0 desktop.o

.got.plt        0x0000000000466000        0x0
 .got.plt       0x0000000000466000        0x0 desktop.o

.igot.plt       0x0000000000466000        0x0
 .igot.plt      0x0000000000466000        0x0 desktop.o

.bss            0x0000000000466000     0xed58
                0x0000000000466000                bss = .
                0x0000000000466000                _bss = .
                0x0000000000466000                __bss = .
 *(.bss)
 .bss           0x0000000000466000        0x8 crt0.o
 .bss           0x0000000000466008       0x60 main.o
                0x0000000000466008                ShellFlag
                0x000000000046600c                executing
                0x0000000000466010                login_status
                0x0000000000466014                global_command
                0x0000000000466018                interrupt_state
                0x000000000046601c                current_user_name
                0x0000000000466020                current_host_name
                0x0000000000466024                login_shell
                0x0000000000466028                interactive
                0x000000000046602c                restricted
                0x0000000000466030                debugging_login_shell
                0x0000000000466034                indirection_level
                0x0000000000466038                shell_level
                0x000000000046603c                act_like_sh
                0x0000000000466040                debugging
                0x0000000000466044                no_rc
                0x0000000000466048                no_profile
                0x000000000046604c                do_version
                0x0000000000466050                quiet
                0x0000000000466054                make_login_shell
                0x0000000000466058                no_line_editing
                0x000000000046605c                no_brace_expansion
 .bss           0x0000000000466068        0x8 shellui.o
 .bss           0x0000000000466070       0x10 api.o
 .bss           0x0000000000466080        0x0 ctype.o
 .bss           0x0000000000466080        0x1 stdio.o
 *fill*         0x0000000000466081       0x1f 
 .bss           0x00000000004660a0     0x8020 stdlib.o
                0x00000000004660a0                environ
 .bss           0x000000000046e0c0        0x4 string.o
 .bss           0x000000000046e0c4        0x0 conio.o
 .bss           0x000000000046e0c4        0x8 builtins.o
 .bss           0x000000000046e0cc        0x8 desktop.o
                0x000000000046f000                . = ALIGN (0x1000)
 *fill*         0x000000000046e0d4      0xf2c 
 COMMON         0x000000000046f000     0x5480 crt0.o
                0x000000000046f000                g_cursor_x
                0x000000000046f004                CurrentWindow
                0x000000000046f008                backgroung_color
                0x000000000046f00c                wsWindowHeight
                0x000000000046f010                stdout
                0x000000000046f014                menu_button
                0x000000000046f018                screen_buffer_y
                0x000000000046f01c                wlFullScreenLeft
                0x000000000046f020                close_button
                0x000000000046f024                smCursorHeight
                0x000000000046f040                pathname_buffer
                0x000000000046f080                textCurrentRow
                0x000000000046f084                g_char_attrib
                0x000000000046f088                g_rows
                0x000000000046f08c                app4_button
                0x000000000046f090                smMousePointerWidth
                0x000000000046f094                smMousePointerHeight
                0x000000000046f098                filename_buffer
                0x000000000046f0c0                Streams
                0x000000000046f140                textWheelDelta
                0x000000000046f144                app1_button
                0x000000000046f148                g_using_gui
                0x000000000046f14c                wlMinRows
                0x000000000046f150                current_volume_string
                0x000000000046f154                ShellMetrics
                0x000000000046f158                smCharHeight
                0x000000000046f15c                ApplicationInfo
                0x000000000046f160                foregroung_color
                0x000000000046f180                prompt_out
                0x000000000046f580                shell_info
                0x000000000046f598                BufferInfo
                0x000000000046f59c                ShellHook
                0x000000000046f5a0                lineList
                0x00000000004715a0                wlMaxWindowHeight
                0x00000000004715a4                wlMaxRows
                0x00000000004715a8                textCurrentCol
                0x00000000004715ac                textSavedCol
                0x00000000004715b0                current_volume_id
                0x00000000004715b4                smCharWidth
                0x00000000004715b8                g_current_workingdirectory_id
                0x00000000004715bc                wlFullScreenHeight
                0x00000000004715c0                textTopRow
                0x00000000004715c4                textMinWheelDelta
                0x00000000004715c8                g_columns
                0x00000000004715cc                prompt_pos
                0x00000000004715d0                stdin
                0x00000000004715d4                pathname_lenght
                0x00000000004715d8                wlMinWindowHeight
                0x00000000004715dc                textBottomRow
                0x00000000004715e0                wlMinColumns
                0x00000000004715e4                prompt_status
                0x00000000004715e8                pwd_initialized
                0x00000000004715ec                root
                0x00000000004715f0                CurrentCommand
                0x00000000004715f4                screen_buffer_x
                0x00000000004715f8                wlMinWindowWidth
                0x00000000004715fc                CommandHistory
                0x0000000000471600                app3_button
                0x0000000000471620                prompt_err
                0x0000000000471a20                pwd
                0x0000000000471a40                screen_buffer
                0x00000000004729e4                reboot_button
                0x00000000004729e8                dummycompiler
                0x00000000004729ec                smScreenWidth
                0x00000000004729f0                textMaxWheelDelta
                0x00000000004729f4                CursorInfo
                0x00000000004729f8                app2_button
                0x00000000004729fc                smScreenHeight
                0x0000000000472a00                wlMaxWindowWidth
                0x0000000000472a04                screen_buffer_pos
                0x0000000000472a08                smCursorWidth
                0x0000000000472a0c                wpWindowLeft
                0x0000000000472a10                terminal_rect
                0x0000000000472a20                stderr
                0x0000000000472a24                wlFullScreenTop
                0x0000000000472a28                wsWindowWidth
                0x0000000000472a2c                g_current_disk_id
                0x0000000000472a30                editboxWindow
                0x0000000000472a40                prompt
                0x0000000000472e40                rect
                0x0000000000472e44                taskbarWindow
                0x0000000000472e48                EOF_Reached
                0x0000000000472e4c                g_cursor_y
                0x0000000000472e60                screenbufferList
                0x0000000000472e80                ClientAreaInfo
                0x0000000000472e84                pathname_initilized
                0x0000000000472e88                wpWindowTop
                0x0000000000472e8c                filename_lenght
                0x0000000000472e90                current_semaphore
                0x0000000000472e94                wlFullScreenWidth
                0x0000000000472e98                prompt_max
                0x0000000000472e9c                wlMaxColumns
                0x0000000000472ea0                textSavedRow
                0x0000000000472ea4                filename_initilized
                0x0000000000472ec0                LINES
                0x0000000000474440                g_current_volume_id
                0x0000000000474460                current_workingdiretory_string
 COMMON         0x0000000000474480       0x40 main.o
                0x0000000000474480                password
                0x000000000047448c                objectY
                0x0000000000474490                username
                0x000000000047449c                deltaY
                0x00000000004744a0                shellStatus
                0x00000000004744a4                shell_environment
                0x00000000004744a8                objectX
                0x00000000004744ac                shell_name
                0x00000000004744b0                build_version
                0x00000000004744b4                deltaX
                0x00000000004744b8                shellError
                0x00000000004744bc                dist_version
 COMMON         0x00000000004744c0       0x10 api.o
                0x00000000004744c0                dialogbox_button2
                0x00000000004744c4                messagebox_button1
                0x00000000004744c8                dialogbox_button1
                0x00000000004744cc                messagebox_button2
 *fill*         0x00000000004744d0       0x10 
 COMMON         0x00000000004744e0      0x878 stdlib.o
                0x00000000004744e0                mm_prev_pointer
                0x0000000000474500                mmblockList
                0x0000000000474900                last_valid
                0x0000000000474920                heapList
                0x0000000000474d20                libcHeap
                0x0000000000474d24                randseed
                0x0000000000474d28                heap_start
                0x0000000000474d2c                g_available_heap
                0x0000000000474d30                g_heap_pointer
                0x0000000000474d34                HEAP_SIZE
                0x0000000000474d38                mmblockCount
                0x0000000000474d3c                last_size
                0x0000000000474d40                heap_end
                0x0000000000474d44                HEAP_END
                0x0000000000474d48                Heap
                0x0000000000474d4c                current_mmblock
                0x0000000000474d50                heapCount
                0x0000000000474d54                HEAP_START
                0x0000000000474d58                end = .
                0x0000000000474d58                _end = .
                0x0000000000474d58                __end = .
LOAD crt0.o
LOAD main.o
LOAD shellui.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
LOAD builtins.o
LOAD desktop.o
OUTPUT(SHELL.BIN elf32-i386)

.comment        0x0000000000000000       0x1a
 .comment       0x0000000000000000       0x1a crt0.o
                                         0x1b (size before relaxing)
 .comment       0x000000000000001a       0x1b main.o
 .comment       0x000000000000001a       0x1b shellui.o
 .comment       0x000000000000001a       0x1b api.o
 .comment       0x000000000000001a       0x1b ctype.o
 .comment       0x000000000000001a       0x1b stdio.o
 .comment       0x000000000000001a       0x1b stdlib.o
 .comment       0x000000000000001a       0x1b string.o
 .comment       0x000000000000001a       0x1b conio.o
 .comment       0x000000000000001a       0x1b builtins.o
 .comment       0x000000000000001a       0x1b desktop.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
 .note.GNU-stack
                0x0000000000000000        0x0 shellui.o
 .note.GNU-stack
                0x0000000000000000        0x0 api.o
 .note.GNU-stack
                0x0000000000000000        0x0 ctype.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdio.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdlib.o
 .note.GNU-stack
                0x0000000000000000        0x0 string.o
 .note.GNU-stack
                0x0000000000000000        0x0 conio.o
 .note.GNU-stack
                0x0000000000000000        0x0 builtins.o
 .note.GNU-stack
                0x0000000000000000        0x0 desktop.o
