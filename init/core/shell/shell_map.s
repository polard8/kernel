
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
 .text          0x0000000000451075     0x493a main.o
                0x0000000000451075                updateObject
                0x000000000045115d                quit
                0x000000000045116d                shmain
                0x00000000004514c6                shellProcedure
                0x0000000000451838                shellWaitCmd
                0x0000000000451852                shellCompare
                0x0000000000453330                shellInitSystemMetrics
                0x00000000004533c9                shellInitWindowLimits
                0x0000000000453487                shellInitWindowSizes
                0x00000000004534d3                shellInitWindowPosition
                0x00000000004534ed                shellShell
                0x0000000000453674                shellInit
                0x0000000000453764                shellCheckPassword
                0x0000000000453ab5                shellSetCursor
                0x0000000000453af0                shellThread
                0x0000000000453b6d                shellShowExperienceMenu
                0x0000000000453b86                shellShowTestsMenu
                0x0000000000453b9f                shellTree
                0x0000000000453bb8                shellPrompt
                0x0000000000453c41                shellClearBuffer
                0x0000000000453cea                shellShowScreenBuffer
                0x0000000000453cf8                shellTestLoadFile
                0x0000000000453d64                shellTestThreads
                0x0000000000453e12                shellClearScreen
                0x0000000000453e8b                shellRefreshScreen
                0x0000000000453f2d                shellRefreshLine
                0x0000000000453fa3                shellRefreshChar
                0x0000000000453fff                shellRefreshCurrentChar
                0x0000000000454037                shellScroll
                0x00000000004540f4                shellInsertCharXY
                0x0000000000454149                shellGetCharXY
                0x000000000045417c                testScrollChar
                0x00000000004541b1                shellInsertNextChar
                0x0000000000454255                shellInsertCR
                0x000000000045426b                shellInsertLF
                0x0000000000454281                shellInsertNullTerminator
                0x0000000000454297                shellTestMBR
                0x00000000004542f2                move_to
                0x000000000045431e                shellShowInfo
                0x00000000004543cb                shellShowMetrics
                0x000000000045447d                shellShowSystemInfo
                0x00000000004544f8                shellShowWindowInfo
                0x00000000004545bf                shellSendMessage
                0x00000000004545db                shell_memcpy_bytes
                0x0000000000454607                shellExit
                0x000000000045461e                shellUpdateWorkingDiretoryString
                0x000000000045467d                shellInitializeWorkingDiretoryString
                0x0000000000454707                shellUpdateCurrentDirectoryID
                0x0000000000454715                shellTaskList
                0x0000000000454838                shellShowPID
                0x0000000000454862                shellShowPPID
                0x000000000045488c                shellShowUID
                0x00000000004548b9                shellShowGID
                0x00000000004548e6                shellShowUserSessionID
                0x0000000000454913                shellShowWindowStationID
                0x0000000000454940                shellShowDesktopID
                0x000000000045496d                shellShowProcessHeapPointer
                0x00000000004549b4                shellShowKernelHeapPointer
                0x00000000004549ef                shellShowDiskInfo
                0x0000000000454a0b                shellShowVolumeInfo
                0x0000000000454a27                shellShowMemoryInfo
                0x0000000000454a43                shellShowPCIInfo
                0x0000000000454a5f                shellShowKernelInfo
                0x0000000000454a7b                shell_fntos
                0x0000000000454b95                shell_gramado_core_init_execve
                0x0000000000454c00                feedterminalDialog
                0x0000000000454c92                die
                0x0000000000454cd4                concat
                0x0000000000454d8a                error
                0x0000000000454dde                fatal
                0x0000000000454e08                save_string
                0x0000000000454e44                shellExecuteThisScript
                0x0000000000454ef1                absolute_pathname
                0x0000000000455057                shellInitPathname
                0x00000000004550a7                shellInitFilename
                0x00000000004550f7                shell_pathname_backup
                0x000000000045516e                shell_print_tokenList
                0x0000000000455212                is_bin
                0x0000000000455283                is_sh1
                0x00000000004552f4                show_shell_version
                0x000000000045531e                shell_save_file
                0x0000000000455493                save_string2
                0x00000000004555a4                textSetTopRow
                0x00000000004555b2                textGetTopRow
                0x00000000004555bc                textSetBottomRow
                0x00000000004555ca                textGetBottomRow
                0x00000000004555d4                clearLine
                0x0000000000455642                testShowLines
                0x00000000004556df                shellRefreshVisibleArea
                0x00000000004557b7                testChangeVisibleArea
                0x00000000004557e1                updateVisibleArea
                0x0000000000455844                shellSocketTest
 .text          0x00000000004559af      0x73c shellui.o
                0x00000000004559af                shellui_fntos
                0x0000000000455ac9                shellTopbarProcedure
                0x0000000000455c22                shellCreateEditBox
                0x0000000000455c90                shellCreateMainWindow
                0x0000000000455d4c                testCreateWindow
                0x0000000000455dde                shellDisplayBMP
                0x0000000000455e52                shellDisplayBMPEx
                0x0000000000455ede                shellTestDisplayBMP
                0x0000000000455f40                bmpDisplayBMP
                0x0000000000455f5d                shellTestButtons
 .text          0x00000000004560eb     0x1fee api.o
                0x00000000004560eb                system_call
                0x0000000000456113                apiSystem
                0x000000000045651b                system1
                0x000000000045653c                system2
                0x000000000045655d                system3
                0x000000000045657e                system4
                0x000000000045659f                system5
                0x00000000004565c0                system6
                0x00000000004565e1                system7
                0x0000000000456602                system8
                0x0000000000456623                system9
                0x0000000000456644                system10
                0x0000000000456665                system11
                0x0000000000456686                system12
                0x00000000004566a7                system13
                0x00000000004566c8                system14
                0x00000000004566e9                system15
                0x000000000045670a                refresh_buffer
                0x00000000004567e8                print_string
                0x00000000004567ee                vsync
                0x0000000000456808                edit_box
                0x0000000000456824                chama_procedimento
                0x000000000045683f                SetNextWindowProcedure
                0x000000000045685a                set_cursor
                0x0000000000456876                put_char
                0x000000000045687c                carrega_bitmap_16x16
                0x0000000000456895                apiShutDown
                0x00000000004568ac                apiInitBackground
                0x00000000004568b2                MessageBox
                0x0000000000456e08                mbProcedure
                0x0000000000456e76                DialogBox
                0x00000000004571f0                dbProcedure
                0x000000000045725e                call_kernel
                0x00000000004573d9                call_gui
                0x0000000000457465                APICreateWindow
                0x00000000004574df                APIRegisterWindow
                0x000000000045750c                APICloseWindow
                0x0000000000457539                APISetFocus
                0x0000000000457566                APIGetFocus
                0x000000000045757b                APIKillFocus
                0x00000000004575a8                APISetActiveWindow
                0x00000000004575d5                APIGetActiveWindow
                0x00000000004575ea                APIShowCurrentProcessInfo
                0x0000000000457600                APIresize_window
                0x000000000045761a                APIredraw_window
                0x0000000000457634                APIreplace_window
                0x000000000045764e                APImaximize_window
                0x000000000045766a                APIminimize_window
                0x0000000000457686                APIupdate_window
                0x00000000004576a2                APIget_foregroung_window
                0x00000000004576b8                APIset_foregroung_window
                0x00000000004576d4                apiExit
                0x00000000004576f1                kill
                0x00000000004576f7                dead_thread_collector
                0x000000000045770d                api_strncmp
                0x0000000000457770                refresh_screen
                0x0000000000457786                api_refresh_screen
                0x0000000000457791                apiReboot
                0x00000000004577a7                apiSetCursor
                0x00000000004577bf                apiGetCursorX
                0x00000000004577d7                apiGetCursorY
                0x00000000004577ef                apiGetClientAreaRect
                0x0000000000457807                apiSetClientAreaRect
                0x0000000000457826                apiCreateProcess
                0x000000000045783f                apiCreateThread
                0x0000000000457858                apiStartThread
                0x0000000000457874                apiFOpen
                0x00000000004578a0                apiSaveFile
                0x00000000004578f3                apiDown
                0x0000000000457946                apiUp
                0x0000000000457999                enterCriticalSection
                0x00000000004579d4                exitCriticalSection
                0x00000000004579ed                initializeCriticalSection
                0x0000000000457a06                apiBeginPaint
                0x0000000000457a11                apiEndPaint
                0x0000000000457a1c                apiPutChar
                0x0000000000457a38                apiDefDialog
                0x0000000000457a42                apiGetSystemMetrics
                0x0000000000457a60                api_set_current_keyboard_responder
                0x0000000000457a7f                api_get_current_keyboard_responder
                0x0000000000457a97                api_set_current_mouse_responder
                0x0000000000457ab6                api_get_current_mouse_responder
                0x0000000000457ace                api_set_window_with_text_input
                0x0000000000457b10                api_get_window_with_text_input
                0x0000000000457b28                gramadocore_init_execve
                0x0000000000457b32                apiDialog
                0x0000000000457bbe                api_getchar
                0x0000000000457bd6                apiDisplayBMP
                0x0000000000457fdd                apiSendMessage
                0x0000000000458013                apiDrawText
                0x0000000000458052                apiGetWSScreenWindow
                0x000000000045806a                apiGetWSMainWindow
                0x0000000000458082                apiCreateTimer
                0x000000000045809f                apiGetSysTimeInfo
                0x00000000004580bd                apiShowWindow
 .text          0x00000000004580d9        0x0 ctype.o
 .text          0x00000000004580d9     0x28d1 stdio.o
                0x0000000000458121                stdio_atoi
                0x00000000004581e8                stdio_fntos
                0x0000000000458312                fclose
                0x0000000000458378                fopen
                0x00000000004584aa                scroll
                0x0000000000458578                puts
                0x0000000000458593                fread
                0x000000000045859d                fwrite
                0x0000000000458968                printf3
                0x0000000000458985                printf_atoi
                0x0000000000458a75                printf_i2hex
                0x0000000000458ad7                printf2
                0x0000000000458c5c                sprintf
                0x0000000000458cb1                putchar
                0x0000000000458cd2                outbyte
                0x0000000000458e90                _outbyte
                0x0000000000458ebf                input
                0x0000000000459013                stdio_system_call
                0x000000000045903b                getchar
                0x0000000000459053                stdioInitialize
                0x0000000000459240                fflush
                0x00000000004592d3                fprintf
                0x0000000000459344                fputs
                0x00000000004593b5                gets
                0x0000000000459440                ungetc
                0x0000000000459477                ftell
                0x0000000000459498                fileno
                0x00000000004594b0                fgetc
                0x000000000045951e                feof
                0x0000000000459553                ferror
                0x000000000045956e                fseek
                0x00000000004595da                fputc
                0x0000000000459629                stdioSetCursor
                0x0000000000459641                stdioGetCursorX
                0x0000000000459659                stdioGetCursorY
                0x0000000000459671                scanf
                0x000000000045980b                fscanf
                0x0000000000459828                sscanf
                0x00000000004599e3                kvprintf
                0x000000000045a84d                printf
                0x000000000045a877                vfprintf
                0x000000000045a8ec                stdout_printf
                0x000000000045a918                stderr_printf
                0x000000000045a944                perror
                0x000000000045a95b                rewind
                0x000000000045a996                snprintf
 .text          0x000000000045a9aa     0x10ac stdlib.o
                0x000000000045a9c7                stdlib_system_call
                0x000000000045a9ef                rtGetHeapStart
                0x000000000045a9f9                rtGetHeapEnd
                0x000000000045aa03                rtGetHeapPointer
                0x000000000045aa0d                rtGetAvailableHeap
                0x000000000045aa17                heapSetLibcHeap
                0x000000000045aaca                AllocateHeap
                0x000000000045ad0c                AllocateHeapEx
                0x000000000045ad22                FreeHeap
                0x000000000045ad2c                heapInit
                0x000000000045aebf                stdlibInitMM
                0x000000000045af22                libcInitRT
                0x000000000045af44                rand
                0x000000000045af61                srand
                0x000000000045af6f                xmalloc
                0x000000000045afa1                stdlib_die
                0x000000000045afd7                malloc
                0x000000000045b013                realloc
                0x000000000045b050                free
                0x000000000045b056                calloc
                0x000000000045b09c                zmalloc
                0x000000000045b0d8                system
                0x000000000045b49c                stdlib_strncmp
                0x000000000045b4ff                __findenv
                0x000000000045b5ca                getenv
                0x000000000045b5f7                atoi
                0x000000000045b6be                reverse
                0x000000000045b725                itoa
                0x000000000045b7d3                abs
                0x000000000045b7e3                strtod
                0x000000000045ba15                strtof
                0x000000000045ba31                strtold
                0x000000000045ba44                atof
 .text          0x000000000045ba56      0x772 string.o
                0x000000000045ba56                memcmp
                0x000000000045babb                strdup
                0x000000000045bb0d                strndup
                0x000000000045bb6e                strrchr
                0x000000000045bba9                strtoimax
                0x000000000045bbb3                strtoumax
                0x000000000045bbbd                strcasecmp
                0x000000000045bc25                strncpy
                0x000000000045bc7b                strcmp
                0x000000000045bce0                strncmp
                0x000000000045bd43                memset
                0x000000000045bd8a                memoryZeroMemory
                0x000000000045bdb1                memcpy
                0x000000000045bdee                strcpy
                0x000000000045be22                strcat
                0x000000000045be51                bcopy
                0x000000000045be7d                bzero
                0x000000000045be9d                strlen
                0x000000000045becb                strnlen
                0x000000000045beff                strcspn
                0x000000000045bf9e                strspn
                0x000000000045c03d                strtok_r
                0x000000000045c124                strtok
                0x000000000045c13c                strchr
                0x000000000045c168                strstr
 .text          0x000000000045c1c8       0x89 conio.o
                0x000000000045c1c8                putch
                0x000000000045c1ec                cputs
                0x000000000045c221                getch
                0x000000000045c239                getche
 .text          0x000000000045c251      0x16f builtins.o
                0x000000000045c251                cd_buitins
                0x000000000045c26a                cls_builtins
                0x000000000045c278                copy_builtins
                0x000000000045c27e                date_builtins
                0x000000000045c284                del_builtins
                0x000000000045c28a                dir_builtins
                0x000000000045c2c6                echo_builtins
                0x000000000045c2e2                exec_builtins
                0x000000000045c2fb                exit_builtins
                0x000000000045c321                getpid_builtins
                0x000000000045c333                getppid_builtins
                0x000000000045c345                getuid_builtins
                0x000000000045c357                getgid_builtins
                0x000000000045c369                help_builtins
                0x000000000045c3a4                pwd_builtins
 .text          0x000000000045c3c0       0x49 desktop.o
                0x000000000045c3c0                desktopInitialize
 .text          0x000000000045c409       0x67 unistd.o
                0x000000000045c409                unistd_system_call
                0x000000000045c431                execve
                0x000000000045c43b                exit
                0x000000000045c45b                fork
                0x000000000045d000                . = ALIGN (0x1000)
 *fill*         0x000000000045c470      0xb90 

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
 *fill*         0x0000000000460b14        0x4 
 .rodata        0x0000000000460b18      0x500 stdlib.o
 .rodata        0x0000000000461018        0x6 conio.o
 *fill*         0x000000000046101e        0x2 
 .rodata        0x0000000000461020      0x8fa builtins.o
 *fill*         0x000000000046191a        0x6 
 .rodata        0x0000000000461920      0x8ef desktop.o

.eh_frame       0x0000000000462210     0x2bd8
 .eh_frame      0x0000000000462210       0x34 crt0.o
 .eh_frame      0x0000000000462244      0xc9c main.o
                                        0xcb4 (size before relaxing)
 .eh_frame      0x0000000000462ee0      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000463020      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000463c4c      0x718 stdio.o
                                        0x730 (size before relaxing)
 .eh_frame      0x0000000000464364      0x444 stdlib.o
                                        0x45c (size before relaxing)
 .eh_frame      0x00000000004647a8      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x0000000000464ac8       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000464b68      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x0000000000464d48       0x20 desktop.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000464d68       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x0000000000464de8       0x1c
 .note.gnu.property
                0x0000000000464de8       0x1c unistd.o

.rel.dyn        0x0000000000464e04        0x0
 .rel.got       0x0000000000464e04        0x0 unistd.o
 .rel.iplt      0x0000000000464e04        0x0 unistd.o
 .rel.text      0x0000000000464e04        0x0 unistd.o

.data           0x0000000000464e20     0x21e0
                0x0000000000464e20                data = .
                0x0000000000464e20                _data = .
                0x0000000000464e20                __data = .
 *(.data)
 .data          0x0000000000464e20      0x4c4 crt0.o
 *fill*         0x00000000004652e4       0x1c 
 .data          0x0000000000465300      0x538 main.o
                0x00000000004657a0                running
                0x00000000004657a4                primary_prompt
                0x00000000004657a8                secondary_prompt
                0x00000000004657ac                remember_on_history
                0x00000000004657b0                current_command_number
                0x00000000004657b4                bashrc_file
                0x00000000004657b8                shell_config_file
                0x00000000004657bc                deltaValue
                0x00000000004657c0                long_args
 *fill*         0x0000000000465838        0x8 
 .data          0x0000000000465840      0x4a0 shellui.o
 .data          0x0000000000465ce0      0x440 api.o
 .data          0x0000000000466120        0x0 ctype.o
 .data          0x0000000000466120        0x0 stdio.o
 .data          0x0000000000466120        0x8 stdlib.o
                0x0000000000466120                _infinity
 .data          0x0000000000466128        0x0 string.o
 .data          0x0000000000466128        0x0 conio.o
 *fill*         0x0000000000466128       0x18 
 .data          0x0000000000466140      0x4a0 builtins.o
 .data          0x00000000004665e0      0x4a8 desktop.o
                0x0000000000466a80                primary_desktop_folder
                0x0000000000466a84                secondary_desktop_folder
 .data          0x0000000000466a88        0x0 unistd.o
                0x0000000000467000                . = ALIGN (0x1000)
 *fill*         0x0000000000466a88      0x578 

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
