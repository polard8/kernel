
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
heapList            0x400             api.o
close_button        0x4               crt0.o
libcHeap            0x4               api.o
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
heap_start          0x4               api.o
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
g_available_heap    0x4               api.o
wlFullScreenHeight  0x4               crt0.o
textTopRow          0x4               crt0.o
g_heap_pointer      0x4               api.o
textMinWheelDelta   0x4               crt0.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               api.o
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
heap_end            0x4               api.o
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
HEAP_END            0x4               api.o
rect                0x4               crt0.o
taskbarWindow       0x4               crt0.o
EOF_Reached         0x4               crt0.o
g_cursor_y          0x4               crt0.o
screenbufferList    0x20              crt0.o
ClientAreaInfo      0x4               crt0.o
messagebox_button2  0x4               api.o
Heap                0x4               api.o
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
heapCount           0x4               api.o
filename_initilized
                    0x4               crt0.o
LINES               0x1580            crt0.o
HEAP_START          0x4               api.o
g_current_volume_id
                    0x4               crt0.o
current_workingdiretory_string
                    0x20              crt0.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000451000     0xc000
                0x0000000000451000                code = .
                0x0000000000451000                _code = .
                0x0000000000451000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000451000       0x75 crt0.o
                0x0000000000451000                crt0
 .text          0x0000000000451075     0x4961 main.o
                0x0000000000451075                updateObject
                0x000000000045115d                quit
                0x000000000045116d                shmain
                0x00000000004514c6                shellProcedure
                0x0000000000451838                shellWaitCmd
                0x0000000000451852                shellCompare
                0x0000000000453357                shellInitSystemMetrics
                0x00000000004533f0                shellInitWindowLimits
                0x00000000004534ae                shellInitWindowSizes
                0x00000000004534fa                shellInitWindowPosition
                0x0000000000453514                shellShell
                0x000000000045369b                shellInit
                0x000000000045378b                shellCheckPassword
                0x0000000000453adc                shellSetCursor
                0x0000000000453b17                shellThread
                0x0000000000453b94                shellShowExperienceMenu
                0x0000000000453bad                shellShowTestsMenu
                0x0000000000453bc6                shellTree
                0x0000000000453bdf                shellPrompt
                0x0000000000453c68                shellClearBuffer
                0x0000000000453d11                shellShowScreenBuffer
                0x0000000000453d1f                shellTestLoadFile
                0x0000000000453d8b                shellTestThreads
                0x0000000000453e39                shellClearScreen
                0x0000000000453eb2                shellRefreshScreen
                0x0000000000453f54                shellRefreshLine
                0x0000000000453fca                shellRefreshChar
                0x0000000000454026                shellRefreshCurrentChar
                0x000000000045405e                shellScroll
                0x000000000045411b                shellInsertCharXY
                0x0000000000454170                shellGetCharXY
                0x00000000004541a3                testScrollChar
                0x00000000004541d8                shellInsertNextChar
                0x000000000045427c                shellInsertCR
                0x0000000000454292                shellInsertLF
                0x00000000004542a8                shellInsertNullTerminator
                0x00000000004542be                shellTestMBR
                0x0000000000454319                move_to
                0x0000000000454345                shellShowInfo
                0x00000000004543f2                shellShowMetrics
                0x00000000004544a4                shellShowSystemInfo
                0x000000000045451f                shellShowWindowInfo
                0x00000000004545e6                shellSendMessage
                0x0000000000454602                shell_memcpy_bytes
                0x000000000045462e                shellExit
                0x0000000000454645                shellUpdateWorkingDiretoryString
                0x00000000004546a4                shellInitializeWorkingDiretoryString
                0x000000000045472e                shellUpdateCurrentDirectoryID
                0x000000000045473c                shellTaskList
                0x000000000045485f                shellShowPID
                0x0000000000454889                shellShowPPID
                0x00000000004548b3                shellShowUID
                0x00000000004548e0                shellShowGID
                0x000000000045490d                shellShowUserSessionID
                0x000000000045493a                shellShowWindowStationID
                0x0000000000454967                shellShowDesktopID
                0x0000000000454994                shellShowProcessHeapPointer
                0x00000000004549db                shellShowKernelHeapPointer
                0x0000000000454a16                shellShowDiskInfo
                0x0000000000454a32                shellShowVolumeInfo
                0x0000000000454a4e                shellShowMemoryInfo
                0x0000000000454a6a                shellShowPCIInfo
                0x0000000000454a86                shellShowKernelInfo
                0x0000000000454aa2                shell_fntos
                0x0000000000454bbc                shell_gramado_core_init_execve
                0x0000000000454c27                feedterminalDialog
                0x0000000000454cb9                die
                0x0000000000454cfb                concat
                0x0000000000454db1                error
                0x0000000000454e05                fatal
                0x0000000000454e2f                save_string
                0x0000000000454e6b                shellExecuteThisScript
                0x0000000000454f18                absolute_pathname
                0x000000000045507e                shellInitPathname
                0x00000000004550ce                shellInitFilename
                0x000000000045511e                shell_pathname_backup
                0x0000000000455195                shell_print_tokenList
                0x0000000000455239                is_bin
                0x00000000004552aa                is_sh1
                0x000000000045531b                show_shell_version
                0x0000000000455345                shell_save_file
                0x00000000004554ba                save_string2
                0x00000000004555cb                textSetTopRow
                0x00000000004555d9                textGetTopRow
                0x00000000004555e3                textSetBottomRow
                0x00000000004555f1                textGetBottomRow
                0x00000000004555fb                clearLine
                0x0000000000455669                testShowLines
                0x0000000000455706                shellRefreshVisibleArea
                0x00000000004557de                testChangeVisibleArea
                0x0000000000455808                updateVisibleArea
                0x000000000045586b                shellSocketTest
 .text          0x00000000004559d6      0x73c shellui.o
                0x00000000004559d6                shellui_fntos
                0x0000000000455af0                shellTopbarProcedure
                0x0000000000455c49                shellCreateEditBox
                0x0000000000455cb7                shellCreateMainWindow
                0x0000000000455d73                testCreateWindow
                0x0000000000455e05                shellDisplayBMP
                0x0000000000455e79                shellDisplayBMPEx
                0x0000000000455f05                shellTestDisplayBMP
                0x0000000000455f67                bmpDisplayBMP
                0x0000000000455f84                shellTestButtons
 .text          0x0000000000456112     0x1fee api.o
                0x0000000000456112                system_call
                0x000000000045613a                apiSystem
                0x0000000000456542                system1
                0x0000000000456563                system2
                0x0000000000456584                system3
                0x00000000004565a5                system4
                0x00000000004565c6                system5
                0x00000000004565e7                system6
                0x0000000000456608                system7
                0x0000000000456629                system8
                0x000000000045664a                system9
                0x000000000045666b                system10
                0x000000000045668c                system11
                0x00000000004566ad                system12
                0x00000000004566ce                system13
                0x00000000004566ef                system14
                0x0000000000456710                system15
                0x0000000000456731                refresh_buffer
                0x000000000045680f                print_string
                0x0000000000456815                vsync
                0x000000000045682f                edit_box
                0x000000000045684b                chama_procedimento
                0x0000000000456866                SetNextWindowProcedure
                0x0000000000456881                set_cursor
                0x000000000045689d                put_char
                0x00000000004568a3                carrega_bitmap_16x16
                0x00000000004568bc                apiShutDown
                0x00000000004568d3                apiInitBackground
                0x00000000004568d9                MessageBox
                0x0000000000456e2f                mbProcedure
                0x0000000000456e9d                DialogBox
                0x0000000000457217                dbProcedure
                0x0000000000457285                call_kernel
                0x0000000000457400                call_gui
                0x000000000045748c                APICreateWindow
                0x0000000000457506                APIRegisterWindow
                0x0000000000457533                APICloseWindow
                0x0000000000457560                APISetFocus
                0x000000000045758d                APIGetFocus
                0x00000000004575a2                APIKillFocus
                0x00000000004575cf                APISetActiveWindow
                0x00000000004575fc                APIGetActiveWindow
                0x0000000000457611                APIShowCurrentProcessInfo
                0x0000000000457627                APIresize_window
                0x0000000000457641                APIredraw_window
                0x000000000045765b                APIreplace_window
                0x0000000000457675                APImaximize_window
                0x0000000000457691                APIminimize_window
                0x00000000004576ad                APIupdate_window
                0x00000000004576c9                APIget_foregroung_window
                0x00000000004576df                APIset_foregroung_window
                0x00000000004576fb                apiExit
                0x0000000000457718                kill
                0x000000000045771e                dead_thread_collector
                0x0000000000457734                api_strncmp
                0x0000000000457797                refresh_screen
                0x00000000004577ad                api_refresh_screen
                0x00000000004577b8                apiReboot
                0x00000000004577ce                apiSetCursor
                0x00000000004577e6                apiGetCursorX
                0x00000000004577fe                apiGetCursorY
                0x0000000000457816                apiGetClientAreaRect
                0x000000000045782e                apiSetClientAreaRect
                0x000000000045784d                apiCreateProcess
                0x0000000000457866                apiCreateThread
                0x000000000045787f                apiStartThread
                0x000000000045789b                apiFOpen
                0x00000000004578c7                apiSaveFile
                0x000000000045791a                apiDown
                0x000000000045796d                apiUp
                0x00000000004579c0                enterCriticalSection
                0x00000000004579fb                exitCriticalSection
                0x0000000000457a14                initializeCriticalSection
                0x0000000000457a2d                apiBeginPaint
                0x0000000000457a38                apiEndPaint
                0x0000000000457a43                apiPutChar
                0x0000000000457a5f                apiDefDialog
                0x0000000000457a69                apiGetSystemMetrics
                0x0000000000457a87                api_set_current_keyboard_responder
                0x0000000000457aa6                api_get_current_keyboard_responder
                0x0000000000457abe                api_set_current_mouse_responder
                0x0000000000457add                api_get_current_mouse_responder
                0x0000000000457af5                api_set_window_with_text_input
                0x0000000000457b37                api_get_window_with_text_input
                0x0000000000457b4f                gramadocore_init_execve
                0x0000000000457b59                apiDialog
                0x0000000000457be5                api_getchar
                0x0000000000457bfd                apiDisplayBMP
                0x0000000000458004                apiSendMessage
                0x000000000045803a                apiDrawText
                0x0000000000458079                apiGetWSScreenWindow
                0x0000000000458091                apiGetWSMainWindow
                0x00000000004580a9                apiCreateTimer
                0x00000000004580c6                apiGetSysTimeInfo
                0x00000000004580e4                apiShowWindow
 .text          0x0000000000458100        0x0 ctype.o
 .text          0x0000000000458100     0x2782 stdio.o
                0x000000000045812b                stdio_atoi
                0x00000000004581f2                stdio_fntos
                0x000000000045831c                fclose
                0x0000000000458382                fopen
                0x00000000004584b4                scroll
                0x0000000000458582                puts
                0x000000000045859d                fread
                0x00000000004585a7                fwrite
                0x0000000000458972                printf3
                0x000000000045898f                printf_atoi
                0x0000000000458a7f                printf_i2hex
                0x0000000000458ae1                printf2
                0x0000000000458c66                sprintf
                0x0000000000458cbb                putchar
                0x0000000000458cdc                outbyte
                0x0000000000458e9a                _outbyte
                0x0000000000458ec9                input
                0x000000000045901d                stdio_system_call
                0x0000000000459045                getchar
                0x000000000045905d                stdioInitialize
                0x000000000045924a                fflush
                0x00000000004592dd                fprintf
                0x000000000045934e                fputs
                0x00000000004593bf                gets
                0x000000000045944a                ungetc
                0x0000000000459481                ftell
                0x00000000004594a2                fileno
                0x00000000004594ba                fgetc
                0x0000000000459528                feof
                0x000000000045955d                ferror
                0x0000000000459578                fseek
                0x00000000004595e4                fputc
                0x0000000000459633                stdioSetCursor
                0x000000000045964b                stdioGetCursorX
                0x0000000000459663                stdioGetCursorY
                0x000000000045967b                scanf
                0x00000000004598bb                kvprintf
                0x000000000045a725                printf
                0x000000000045a74f                vfprintf
                0x000000000045a7c4                stdout_printf
                0x000000000045a7f0                stderr_printf
                0x000000000045a81c                perror
                0x000000000045a833                rewind
                0x000000000045a86e                snprintf
 .text          0x000000000045a882      0xe1c stdlib.o
                0x000000000045a882                stdlib_system_call
                0x000000000045a8aa                rtGetHeapStart
                0x000000000045a8b4                rtGetHeapEnd
                0x000000000045a8be                rtGetHeapPointer
                0x000000000045a8c8                rtGetAvailableHeap
                0x000000000045a8d2                heapSetLibcHeap
                0x000000000045a985                AllocateHeap
                0x000000000045abc7                AllocateHeapEx
                0x000000000045abdd                FreeHeap
                0x000000000045abe7                heapInit
                0x000000000045ad7a                stdlibInitMM
                0x000000000045addd                libcInitRT
                0x000000000045adff                rand
                0x000000000045ae1c                srand
                0x000000000045ae2a                xmalloc
                0x000000000045ae5c                stdlib_die
                0x000000000045ae92                malloc
                0x000000000045aece                realloc
                0x000000000045af0b                free
                0x000000000045af11                calloc
                0x000000000045af57                zmalloc
                0x000000000045af93                system
                0x000000000045b357                stdlib_strncmp
                0x000000000045b3ba                __findenv
                0x000000000045b485                getenv
                0x000000000045b4b2                atoi
                0x000000000045b579                reverse
                0x000000000045b5e0                itoa
                0x000000000045b68e                abs
 .text          0x000000000045b69e      0x779 string.o
                0x000000000045b69e                memcmp
                0x000000000045b703                strtold
                0x000000000045b70a                strdup
                0x000000000045b75c                strndup
                0x000000000045b7bd                strrchr
                0x000000000045b7f8                strtoimax
                0x000000000045b802                strtoumax
                0x000000000045b80c                strcasecmp
                0x000000000045b874                strncpy
                0x000000000045b8ca                strcmp
                0x000000000045b92f                strncmp
                0x000000000045b992                memset
                0x000000000045b9d9                memoryZeroMemory
                0x000000000045ba00                memcpy
                0x000000000045ba3d                strcpy
                0x000000000045ba71                strcat
                0x000000000045baa0                bcopy
                0x000000000045bacc                bzero
                0x000000000045baec                strlen
                0x000000000045bb1a                strnlen
                0x000000000045bb4e                strcspn
                0x000000000045bbed                strspn
                0x000000000045bc8c                strtok_r
                0x000000000045bd73                strtok
                0x000000000045bd8b                strchr
                0x000000000045bdb7                strstr
 .text          0x000000000045be17       0x89 conio.o
                0x000000000045be17                putch
                0x000000000045be3b                cputs
                0x000000000045be70                getch
                0x000000000045be88                getche
 .text          0x000000000045bea0      0x16f builtins.o
                0x000000000045bea0                cd_buitins
                0x000000000045beb9                cls_builtins
                0x000000000045bec7                copy_builtins
                0x000000000045becd                date_builtins
                0x000000000045bed3                del_builtins
                0x000000000045bed9                dir_builtins
                0x000000000045bf15                echo_builtins
                0x000000000045bf31                exec_builtins
                0x000000000045bf4a                exit_builtins
                0x000000000045bf70                getpid_builtins
                0x000000000045bf82                getppid_builtins
                0x000000000045bf94                getuid_builtins
                0x000000000045bfa6                getgid_builtins
                0x000000000045bfb8                help_builtins
                0x000000000045bff3                pwd_builtins
 .text          0x000000000045c00f       0x49 desktop.o
                0x000000000045c00f                desktopInitialize
 .text          0x000000000045c058       0x67 unistd.o
                0x000000000045c058                unistd_system_call
                0x000000000045c080                execve
                0x000000000045c08a                exit
                0x000000000045c0aa                fork
                0x000000000045d000                . = ALIGN (0x1000)
 *fill*         0x000000000045c0bf      0xf41 

.iplt           0x000000000045d000        0x0
 .iplt          0x000000000045d000        0x0 unistd.o

.rodata         0x000000000045d000     0x520f
 .rodata        0x000000000045d000      0x945 crt0.o
 *fill*         0x000000000045d945       0x1b 
 .rodata        0x000000000045d960     0x1e3b main.o
 *fill*         0x000000000045f79b        0x5 
 .rodata        0x000000000045f7a0      0xb43 shellui.o
 *fill*         0x00000000004602e3        0x1 
 .rodata        0x00000000004602e4      0x39d api.o
 *fill*         0x0000000000460681       0x1f 
 .rodata        0x00000000004606a0      0x100 ctype.o
                0x00000000004606a0                _ctype
 .rodata        0x00000000004607a0      0x374 stdio.o
                0x0000000000460980                hex2ascii_data
 .rodata        0x0000000000460b14      0x4f3 stdlib.o
 .rodata        0x0000000000461007        0x6 conio.o
 *fill*         0x000000000046100d       0x13 
 .rodata        0x0000000000461020      0x8fa builtins.o
 *fill*         0x000000000046191a        0x6 
 .rodata        0x0000000000461920      0x8ef desktop.o

.eh_frame       0x0000000000462210     0x2af8
 .eh_frame      0x0000000000462210       0x34 crt0.o
 .eh_frame      0x0000000000462244      0xc9c main.o
                                        0xcb4 (size before relaxing)
 .eh_frame      0x0000000000462ee0      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000463020      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000463c4c      0x6b8 stdio.o
                                        0x6d0 (size before relaxing)
 .eh_frame      0x0000000000464304      0x3a4 stdlib.o
                                        0x3bc (size before relaxing)
 .eh_frame      0x00000000004646a8      0x340 string.o
                                        0x358 (size before relaxing)
 .eh_frame      0x00000000004649e8       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000464a88      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x0000000000464c68       0x20 desktop.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000464c88       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x0000000000464d08       0x1c
 .note.gnu.property
                0x0000000000464d08       0x1c unistd.o

.rel.dyn        0x0000000000464d24        0x0
 .rel.got       0x0000000000464d24        0x0 unistd.o
 .rel.iplt      0x0000000000464d24        0x0 unistd.o
 .rel.text      0x0000000000464d24        0x0 unistd.o

.data           0x0000000000464d40     0x22c0
                0x0000000000464d40                data = .
                0x0000000000464d40                _data = .
                0x0000000000464d40                __data = .
 *(.data)
 .data          0x0000000000464d40      0x4c4 crt0.o
 *fill*         0x0000000000465204       0x1c 
 .data          0x0000000000465220      0x538 main.o
                0x00000000004656c0                running
                0x00000000004656c4                primary_prompt
                0x00000000004656c8                secondary_prompt
                0x00000000004656cc                remember_on_history
                0x00000000004656d0                current_command_number
                0x00000000004656d4                bashrc_file
                0x00000000004656d8                shell_config_file
                0x00000000004656dc                deltaValue
                0x00000000004656e0                long_args
 *fill*         0x0000000000465758        0x8 
 .data          0x0000000000465760      0x4a0 shellui.o
 .data          0x0000000000465c00      0x440 api.o
 .data          0x0000000000466040        0x0 ctype.o
 .data          0x0000000000466040        0x0 stdio.o
 .data          0x0000000000466040        0x0 stdlib.o
 .data          0x0000000000466040        0x0 string.o
 .data          0x0000000000466040        0x0 conio.o
 .data          0x0000000000466040      0x4a0 builtins.o
 .data          0x00000000004664e0      0x4a8 desktop.o
                0x0000000000466980                primary_desktop_folder
                0x0000000000466984                secondary_desktop_folder
 .data          0x0000000000466988        0x0 unistd.o
                0x0000000000467000                . = ALIGN (0x1000)
 *fill*         0x0000000000466988      0x678 

.got            0x0000000000467000        0x0
 .got           0x0000000000467000        0x0 unistd.o

.got.plt        0x0000000000467000        0x0
 .got.plt       0x0000000000467000        0x0 unistd.o

.igot.plt       0x0000000000467000        0x0
 .igot.plt      0x0000000000467000        0x0 unistd.o

.bss            0x0000000000467000    0x16d34
                0x0000000000467000                bss = .
                0x0000000000467000                _bss = .
                0x0000000000467000                __bss = .
 *(.bss)
 .bss           0x0000000000467000        0x8 crt0.o
 .bss           0x0000000000467008       0x60 main.o
                0x0000000000467008                ShellFlag
                0x000000000046700c                executing
                0x0000000000467010                login_status
                0x0000000000467014                global_command
                0x0000000000467018                interrupt_state
                0x000000000046701c                current_user_name
                0x0000000000467020                current_host_name
                0x0000000000467024                login_shell
                0x0000000000467028                interactive
                0x000000000046702c                restricted
                0x0000000000467030                debugging_login_shell
                0x0000000000467034                indirection_level
                0x0000000000467038                shell_level
                0x000000000046703c                act_like_sh
                0x0000000000467040                debugging
                0x0000000000467044                no_rc
                0x0000000000467048                no_profile
                0x000000000046704c                do_version
                0x0000000000467050                quiet
                0x0000000000467054                make_login_shell
                0x0000000000467058                no_line_editing
                0x000000000046705c                no_brace_expansion
 .bss           0x0000000000467068        0x8 shellui.o
 *fill*         0x0000000000467070       0x10 
 .bss           0x0000000000467080     0x8004 api.o
 .bss           0x000000000046f084        0x0 ctype.o
 .bss           0x000000000046f084        0x1 stdio.o
 *fill*         0x000000000046f085       0x1b 
 .bss           0x000000000046f0a0     0x8020 stdlib.o
                0x000000000046f0a0                environ
 .bss           0x00000000004770c0        0x4 string.o
 .bss           0x00000000004770c4        0x0 conio.o
 .bss           0x00000000004770c4        0x8 builtins.o
 .bss           0x00000000004770cc        0x8 desktop.o
 .bss           0x00000000004770d4        0x0 unistd.o
                0x0000000000478000                . = ALIGN (0x1000)
 *fill*         0x00000000004770d4      0xf2c 
 COMMON         0x0000000000478000     0x5480 crt0.o
                0x0000000000478000                g_cursor_x
                0x0000000000478004                CurrentWindow
                0x0000000000478008                backgroung_color
                0x000000000047800c                wsWindowHeight
                0x0000000000478010                stdout
                0x0000000000478014                menu_button
                0x0000000000478018                screen_buffer_y
                0x000000000047801c                wlFullScreenLeft
                0x0000000000478020                close_button
                0x0000000000478024                smCursorHeight
                0x0000000000478040                pathname_buffer
                0x0000000000478080                textCurrentRow
                0x0000000000478084                g_char_attrib
                0x0000000000478088                g_rows
                0x000000000047808c                app4_button
                0x0000000000478090                smMousePointerWidth
                0x0000000000478094                smMousePointerHeight
                0x0000000000478098                filename_buffer
                0x00000000004780c0                Streams
                0x0000000000478140                textWheelDelta
                0x0000000000478144                app1_button
                0x0000000000478148                g_using_gui
                0x000000000047814c                wlMinRows
                0x0000000000478150                current_volume_string
                0x0000000000478154                ShellMetrics
                0x0000000000478158                smCharHeight
                0x000000000047815c                ApplicationInfo
                0x0000000000478160                foregroung_color
                0x0000000000478180                prompt_out
                0x0000000000478580                shell_info
                0x0000000000478598                BufferInfo
                0x000000000047859c                ShellHook
                0x00000000004785a0                lineList
                0x000000000047a5a0                wlMaxWindowHeight
                0x000000000047a5a4                wlMaxRows
                0x000000000047a5a8                textCurrentCol
                0x000000000047a5ac                textSavedCol
                0x000000000047a5b0                current_volume_id
                0x000000000047a5b4                smCharWidth
                0x000000000047a5b8                g_current_workingdirectory_id
                0x000000000047a5bc                wlFullScreenHeight
                0x000000000047a5c0                textTopRow
                0x000000000047a5c4                textMinWheelDelta
                0x000000000047a5c8                g_columns
                0x000000000047a5cc                prompt_pos
                0x000000000047a5d0                stdin
                0x000000000047a5d4                pathname_lenght
                0x000000000047a5d8                wlMinWindowHeight
                0x000000000047a5dc                textBottomRow
                0x000000000047a5e0                wlMinColumns
                0x000000000047a5e4                prompt_status
                0x000000000047a5e8                pwd_initialized
                0x000000000047a5ec                root
                0x000000000047a5f0                CurrentCommand
                0x000000000047a5f4                screen_buffer_x
                0x000000000047a5f8                wlMinWindowWidth
                0x000000000047a5fc                CommandHistory
                0x000000000047a600                app3_button
                0x000000000047a620                prompt_err
                0x000000000047aa20                pwd
                0x000000000047aa40                screen_buffer
                0x000000000047b9e4                reboot_button
                0x000000000047b9e8                dummycompiler
                0x000000000047b9ec                smScreenWidth
                0x000000000047b9f0                textMaxWheelDelta
                0x000000000047b9f4                CursorInfo
                0x000000000047b9f8                app2_button
                0x000000000047b9fc                smScreenHeight
                0x000000000047ba00                wlMaxWindowWidth
                0x000000000047ba04                screen_buffer_pos
                0x000000000047ba08                smCursorWidth
                0x000000000047ba0c                wpWindowLeft
                0x000000000047ba10                terminal_rect
                0x000000000047ba20                stderr
                0x000000000047ba24                wlFullScreenTop
                0x000000000047ba28                wsWindowWidth
                0x000000000047ba2c                g_current_disk_id
                0x000000000047ba30                editboxWindow
                0x000000000047ba40                prompt
                0x000000000047be40                rect
                0x000000000047be44                taskbarWindow
                0x000000000047be48                EOF_Reached
                0x000000000047be4c                g_cursor_y
                0x000000000047be60                screenbufferList
                0x000000000047be80                ClientAreaInfo
                0x000000000047be84                pathname_initilized
                0x000000000047be88                wpWindowTop
                0x000000000047be8c                filename_lenght
                0x000000000047be90                current_semaphore
                0x000000000047be94                wlFullScreenWidth
                0x000000000047be98                prompt_max
                0x000000000047be9c                wlMaxColumns
                0x000000000047bea0                textSavedRow
                0x000000000047bea4                filename_initilized
                0x000000000047bec0                LINES
                0x000000000047d440                g_current_volume_id
                0x000000000047d460                current_workingdiretory_string
 COMMON         0x000000000047d480       0x40 main.o
                0x000000000047d480                password
                0x000000000047d48c                objectY
                0x000000000047d490                username
                0x000000000047d49c                deltaY
                0x000000000047d4a0                shellStatus
                0x000000000047d4a4                shell_environment
                0x000000000047d4a8                objectX
                0x000000000047d4ac                shell_name
                0x000000000047d4b0                build_version
                0x000000000047d4b4                deltaX
                0x000000000047d4b8                shellError
                0x000000000047d4bc                dist_version
 COMMON         0x000000000047d4c0      0x438 api.o
                0x000000000047d4c0                heapList
                0x000000000047d8c0                libcHeap
                0x000000000047d8c4                dialogbox_button2
                0x000000000047d8c8                messagebox_button1
                0x000000000047d8cc                heap_start
                0x000000000047d8d0                g_available_heap
                0x000000000047d8d4                g_heap_pointer
                0x000000000047d8d8                HEAP_SIZE
                0x000000000047d8dc                dialogbox_button1
                0x000000000047d8e0                heap_end
                0x000000000047d8e4                HEAP_END
                0x000000000047d8e8                messagebox_button2
                0x000000000047d8ec                Heap
                0x000000000047d8f0                heapCount
                0x000000000047d8f4                HEAP_START
 *fill*         0x000000000047d8f8        0x8 
 COMMON         0x000000000047d900      0x434 stdlib.o
                0x000000000047d900                mm_prev_pointer
                0x000000000047d920                mmblockList
                0x000000000047dd20                last_valid
                0x000000000047dd24                randseed
                0x000000000047dd28                mmblockCount
                0x000000000047dd2c                last_size
                0x000000000047dd30                current_mmblock
                0x000000000047dd34                end = .
                0x000000000047dd34                _end = .
                0x000000000047dd34                __end = .
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
LOAD unistd.o
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
 .comment       0x000000000000001a       0x1b unistd.o

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
 .note.GNU-stack
                0x0000000000000000        0x0 unistd.o
