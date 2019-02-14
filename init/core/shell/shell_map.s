
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


.text           0x0000000000451000     0xb000
                0x0000000000451000                code = .
                0x0000000000451000                _code = .
                0x0000000000451000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000451000       0x75 crt0.o
                0x0000000000451000                crt0
 .text          0x0000000000451075     0x45f3 main.o
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
                0x000000000045376e                shellSetCursor
                0x00000000004537a9                shellThread
                0x0000000000453826                shellShowExperienceMenu
                0x000000000045383f                shellShowTestsMenu
                0x0000000000453858                shellTree
                0x0000000000453871                shellPrompt
                0x00000000004538fa                shellClearBuffer
                0x00000000004539a3                shellShowScreenBuffer
                0x00000000004539b1                shellTestLoadFile
                0x0000000000453a1d                shellTestThreads
                0x0000000000453acb                shellClearScreen
                0x0000000000453b44                shellRefreshScreen
                0x0000000000453be6                shellRefreshLine
                0x0000000000453c5c                shellRefreshChar
                0x0000000000453cb8                shellRefreshCurrentChar
                0x0000000000453cf0                shellScroll
                0x0000000000453dad                shellInsertCharXY
                0x0000000000453e02                shellGetCharXY
                0x0000000000453e35                testScrollChar
                0x0000000000453e6a                shellInsertNextChar
                0x0000000000453f0e                shellInsertCR
                0x0000000000453f24                shellInsertLF
                0x0000000000453f3a                shellInsertNullTerminator
                0x0000000000453f50                shellTestMBR
                0x0000000000453fab                move_to
                0x0000000000453fd7                shellShowInfo
                0x0000000000454084                shellShowMetrics
                0x0000000000454136                shellShowSystemInfo
                0x00000000004541b1                shellShowWindowInfo
                0x0000000000454278                shellSendMessage
                0x0000000000454294                shell_memcpy_bytes
                0x00000000004542c0                shellExit
                0x00000000004542d7                shellUpdateWorkingDiretoryString
                0x0000000000454336                shellInitializeWorkingDiretoryString
                0x00000000004543c0                shellUpdateCurrentDirectoryID
                0x00000000004543ce                shellTaskList
                0x00000000004544f1                shellShowPID
                0x000000000045451b                shellShowPPID
                0x0000000000454545                shellShowUID
                0x0000000000454572                shellShowGID
                0x000000000045459f                shellShowUserSessionID
                0x00000000004545cc                shellShowWindowStationID
                0x00000000004545f9                shellShowDesktopID
                0x0000000000454626                shellShowProcessHeapPointer
                0x000000000045466d                shellShowKernelHeapPointer
                0x00000000004546a8                shellShowDiskInfo
                0x00000000004546c4                shellShowVolumeInfo
                0x00000000004546e0                shellShowMemoryInfo
                0x00000000004546fc                shellShowPCIInfo
                0x0000000000454718                shellShowKernelInfo
                0x0000000000454734                shell_fntos
                0x000000000045484e                shell_gramado_core_init_execve
                0x00000000004548b9                feedterminalDialog
                0x000000000045494b                die
                0x000000000045498d                concat
                0x0000000000454a43                error
                0x0000000000454a97                fatal
                0x0000000000454ac1                save_string
                0x0000000000454afd                shellExecuteThisScript
                0x0000000000454baa                absolute_pathname
                0x0000000000454d10                shellInitPathname
                0x0000000000454d60                shellInitFilename
                0x0000000000454db0                shell_pathname_backup
                0x0000000000454e27                shell_print_tokenList
                0x0000000000454ecb                is_bin
                0x0000000000454f3c                is_sh1
                0x0000000000454fad                show_shell_version
                0x0000000000454fd7                shell_save_file
                0x000000000045514c                save_string2
                0x000000000045525d                textSetTopRow
                0x000000000045526b                textGetTopRow
                0x0000000000455275                textSetBottomRow
                0x0000000000455283                textGetBottomRow
                0x000000000045528d                clearLine
                0x00000000004552fb                testShowLines
                0x0000000000455398                shellRefreshVisibleArea
                0x0000000000455470                testChangeVisibleArea
                0x000000000045549a                updateVisibleArea
                0x00000000004554fd                shellSocketTest
 .text          0x0000000000455668      0x73c shellui.o
                0x0000000000455668                shellui_fntos
                0x0000000000455782                shellTopbarProcedure
                0x00000000004558db                shellCreateEditBox
                0x0000000000455949                shellCreateMainWindow
                0x0000000000455a05                testCreateWindow
                0x0000000000455a97                shellDisplayBMP
                0x0000000000455b0b                shellDisplayBMPEx
                0x0000000000455b97                shellTestDisplayBMP
                0x0000000000455bf9                bmpDisplayBMP
                0x0000000000455c16                shellTestButtons
 .text          0x0000000000455da4     0x1fee api.o
                0x0000000000455da4                system_call
                0x0000000000455dcc                apiSystem
                0x00000000004561d4                system1
                0x00000000004561f5                system2
                0x0000000000456216                system3
                0x0000000000456237                system4
                0x0000000000456258                system5
                0x0000000000456279                system6
                0x000000000045629a                system7
                0x00000000004562bb                system8
                0x00000000004562dc                system9
                0x00000000004562fd                system10
                0x000000000045631e                system11
                0x000000000045633f                system12
                0x0000000000456360                system13
                0x0000000000456381                system14
                0x00000000004563a2                system15
                0x00000000004563c3                refresh_buffer
                0x00000000004564a1                print_string
                0x00000000004564a7                vsync
                0x00000000004564c1                edit_box
                0x00000000004564dd                chama_procedimento
                0x00000000004564f8                SetNextWindowProcedure
                0x0000000000456513                set_cursor
                0x000000000045652f                put_char
                0x0000000000456535                carrega_bitmap_16x16
                0x000000000045654e                apiShutDown
                0x0000000000456565                apiInitBackground
                0x000000000045656b                MessageBox
                0x0000000000456ac1                mbProcedure
                0x0000000000456b2f                DialogBox
                0x0000000000456ea9                dbProcedure
                0x0000000000456f17                call_kernel
                0x0000000000457092                call_gui
                0x000000000045711e                APICreateWindow
                0x0000000000457198                APIRegisterWindow
                0x00000000004571c5                APICloseWindow
                0x00000000004571f2                APISetFocus
                0x000000000045721f                APIGetFocus
                0x0000000000457234                APIKillFocus
                0x0000000000457261                APISetActiveWindow
                0x000000000045728e                APIGetActiveWindow
                0x00000000004572a3                APIShowCurrentProcessInfo
                0x00000000004572b9                APIresize_window
                0x00000000004572d3                APIredraw_window
                0x00000000004572ed                APIreplace_window
                0x0000000000457307                APImaximize_window
                0x0000000000457323                APIminimize_window
                0x000000000045733f                APIupdate_window
                0x000000000045735b                APIget_foregroung_window
                0x0000000000457371                APIset_foregroung_window
                0x000000000045738d                apiExit
                0x00000000004573aa                kill
                0x00000000004573b0                dead_thread_collector
                0x00000000004573c6                api_strncmp
                0x0000000000457429                refresh_screen
                0x000000000045743f                api_refresh_screen
                0x000000000045744a                apiReboot
                0x0000000000457460                apiSetCursor
                0x0000000000457478                apiGetCursorX
                0x0000000000457490                apiGetCursorY
                0x00000000004574a8                apiGetClientAreaRect
                0x00000000004574c0                apiSetClientAreaRect
                0x00000000004574df                apiCreateProcess
                0x00000000004574f8                apiCreateThread
                0x0000000000457511                apiStartThread
                0x000000000045752d                apiFOpen
                0x0000000000457559                apiSaveFile
                0x00000000004575ac                apiDown
                0x00000000004575ff                apiUp
                0x0000000000457652                enterCriticalSection
                0x000000000045768d                exitCriticalSection
                0x00000000004576a6                initializeCriticalSection
                0x00000000004576bf                apiBeginPaint
                0x00000000004576ca                apiEndPaint
                0x00000000004576d5                apiPutChar
                0x00000000004576f1                apiDefDialog
                0x00000000004576fb                apiGetSystemMetrics
                0x0000000000457719                api_set_current_keyboard_responder
                0x0000000000457738                api_get_current_keyboard_responder
                0x0000000000457750                api_set_current_mouse_responder
                0x000000000045776f                api_get_current_mouse_responder
                0x0000000000457787                api_set_window_with_text_input
                0x00000000004577c9                api_get_window_with_text_input
                0x00000000004577e1                gramadocore_init_execve
                0x00000000004577eb                apiDialog
                0x0000000000457877                api_getchar
                0x000000000045788f                apiDisplayBMP
                0x0000000000457c96                apiSendMessage
                0x0000000000457ccc                apiDrawText
                0x0000000000457d0b                apiGetWSScreenWindow
                0x0000000000457d23                apiGetWSMainWindow
                0x0000000000457d3b                apiCreateTimer
                0x0000000000457d58                apiGetSysTimeInfo
                0x0000000000457d76                apiShowWindow
 .text          0x0000000000457d92        0x0 ctype.o
 .text          0x0000000000457d92     0x2763 stdio.o
                0x0000000000457dda                stdio_atoi
                0x0000000000457ea1                stdio_fntos
                0x0000000000457fcb                fclose
                0x0000000000458031                fopen
                0x00000000004580d8                scroll
                0x00000000004581a6                puts
                0x00000000004581c1                fread
                0x00000000004581cb                fwrite
                0x0000000000458596                printf3
                0x00000000004585b3                printf_atoi
                0x00000000004586a3                printf_i2hex
                0x0000000000458705                printf2
                0x000000000045888a                sprintf
                0x00000000004588df                putchar
                0x0000000000458900                outbyte
                0x0000000000458abe                _outbyte
                0x0000000000458aed                input
                0x0000000000458c41                stdio_system_call
                0x0000000000458c69                getchar
                0x0000000000458c81                stdioInitialize
                0x0000000000458e6e                fflush
                0x0000000000458f01                fprintf
                0x0000000000458f72                fputs
                0x0000000000458fe3                gets
                0x000000000045906e                ungetc
                0x00000000004590a5                ftell
                0x00000000004590c6                fileno
                0x00000000004590de                fgetc
                0x00000000004590fc                feof
                0x000000000045911a                ferror
                0x0000000000459138                fseek
                0x0000000000459156                fputc
                0x0000000000459174                stdioSetCursor
                0x000000000045918c                stdioGetCursorX
                0x00000000004591a4                stdioGetCursorY
                0x00000000004591bc                scanf
                0x0000000000459356                fscanf
                0x0000000000459373                sscanf
                0x000000000045952e                kvprintf
                0x000000000045a398                printf
                0x000000000045a3c2                vfprintf
                0x000000000045a437                stdout_printf
                0x000000000045a463                stderr_printf
                0x000000000045a48f                perror
                0x000000000045a4a6                rewind
                0x000000000045a4e1                snprintf
 .text          0x000000000045a4f5     0x10ac stdlib.o
                0x000000000045a512                stdlib_system_call
                0x000000000045a53a                rtGetHeapStart
                0x000000000045a544                rtGetHeapEnd
                0x000000000045a54e                rtGetHeapPointer
                0x000000000045a558                rtGetAvailableHeap
                0x000000000045a562                heapSetLibcHeap
                0x000000000045a615                AllocateHeap
                0x000000000045a857                AllocateHeapEx
                0x000000000045a86d                FreeHeap
                0x000000000045a877                heapInit
                0x000000000045aa0a                stdlibInitMM
                0x000000000045aa6d                libcInitRT
                0x000000000045aa8f                rand
                0x000000000045aaac                srand
                0x000000000045aaba                xmalloc
                0x000000000045aaec                stdlib_die
                0x000000000045ab22                malloc
                0x000000000045ab5e                realloc
                0x000000000045ab9b                free
                0x000000000045aba1                calloc
                0x000000000045abe7                zmalloc
                0x000000000045ac23                system
                0x000000000045afe7                stdlib_strncmp
                0x000000000045b04a                __findenv
                0x000000000045b115                getenv
                0x000000000045b142                atoi
                0x000000000045b209                reverse
                0x000000000045b270                itoa
                0x000000000045b31e                abs
                0x000000000045b32e                strtod
                0x000000000045b560                strtof
                0x000000000045b57c                strtold
                0x000000000045b58f                atof
 .text          0x000000000045b5a1      0x772 string.o
                0x000000000045b5a1                memcmp
                0x000000000045b606                strdup
                0x000000000045b658                strndup
                0x000000000045b6b9                strrchr
                0x000000000045b6f4                strtoimax
                0x000000000045b6fe                strtoumax
                0x000000000045b708                strcasecmp
                0x000000000045b770                strncpy
                0x000000000045b7c6                strcmp
                0x000000000045b82b                strncmp
                0x000000000045b88e                memset
                0x000000000045b8d5                memoryZeroMemory
                0x000000000045b8fc                memcpy
                0x000000000045b939                strcpy
                0x000000000045b96d                strcat
                0x000000000045b99c                bcopy
                0x000000000045b9c8                bzero
                0x000000000045b9e8                strlen
                0x000000000045ba16                strnlen
                0x000000000045ba4a                strcspn
                0x000000000045bae9                strspn
                0x000000000045bb88                strtok_r
                0x000000000045bc6f                strtok
                0x000000000045bc87                strchr
                0x000000000045bcb3                strstr
 .text          0x000000000045bd13       0x89 conio.o
                0x000000000045bd13                putch
                0x000000000045bd37                cputs
                0x000000000045bd6c                getch
                0x000000000045bd84                getche
 .text          0x000000000045bd9c      0x16f builtins.o
                0x000000000045bd9c                cd_buitins
                0x000000000045bdb5                cls_builtins
                0x000000000045bdc3                copy_builtins
                0x000000000045bdc9                date_builtins
                0x000000000045bdcf                del_builtins
                0x000000000045bdd5                dir_builtins
                0x000000000045be11                echo_builtins
                0x000000000045be2d                exec_builtins
                0x000000000045be46                exit_builtins
                0x000000000045be6c                getpid_builtins
                0x000000000045be7e                getppid_builtins
                0x000000000045be90                getuid_builtins
                0x000000000045bea2                getgid_builtins
                0x000000000045beb4                help_builtins
                0x000000000045beef                pwd_builtins
 .text          0x000000000045bf0b       0x49 desktop.o
                0x000000000045bf0b                desktopInitialize
 .text          0x000000000045bf54       0x67 unistd.o
                0x000000000045bf54                unistd_system_call
                0x000000000045bf7c                execve
                0x000000000045bf86                exit
                0x000000000045bfa6                fork
                0x000000000045c000                . = ALIGN (0x1000)
 *fill*         0x000000000045bfbb       0x45 

.iplt           0x000000000045c000        0x0
 .iplt          0x000000000045c000        0x0 unistd.o

.rodata         0x000000000045c000     0x510f
 .rodata        0x000000000045c000      0x945 crt0.o
 *fill*         0x000000000045c945       0x1b 
 .rodata        0x000000000045c960     0x1d7b main.o
 *fill*         0x000000000045e6db        0x5 
 .rodata        0x000000000045e6e0      0xb43 shellui.o
 *fill*         0x000000000045f223        0x1 
 .rodata        0x000000000045f224      0x39d api.o
 *fill*         0x000000000045f5c1       0x1f 
 .rodata        0x000000000045f5e0      0x100 ctype.o
                0x000000000045f5e0                _ctype
 .rodata        0x000000000045f6e0      0x334 stdio.o
                0x000000000045f880                hex2ascii_data
 *fill*         0x000000000045fa14        0x4 
 .rodata        0x000000000045fa18      0x500 stdlib.o
 .rodata        0x000000000045ff18        0x6 conio.o
 *fill*         0x000000000045ff1e        0x2 
 .rodata        0x000000000045ff20      0x8fa builtins.o
 *fill*         0x000000000046081a        0x6 
 .rodata        0x0000000000460820      0x8ef desktop.o

.eh_frame       0x0000000000461110     0x2bd8
 .eh_frame      0x0000000000461110       0x34 crt0.o
 .eh_frame      0x0000000000461144      0xc9c main.o
                                        0xcb4 (size before relaxing)
 .eh_frame      0x0000000000461de0      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000461f20      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000462b4c      0x718 stdio.o
                                        0x730 (size before relaxing)
 .eh_frame      0x0000000000463264      0x444 stdlib.o
                                        0x45c (size before relaxing)
 .eh_frame      0x00000000004636a8      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x00000000004639c8       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000463a68      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x0000000000463c48       0x20 desktop.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000463c68       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x0000000000463ce8       0x1c
 .note.gnu.property
                0x0000000000463ce8       0x1c unistd.o

.rel.dyn        0x0000000000463d04        0x0
 .rel.got       0x0000000000463d04        0x0 unistd.o
 .rel.iplt      0x0000000000463d04        0x0 unistd.o
 .rel.text      0x0000000000463d04        0x0 unistd.o

.data           0x0000000000463d20     0x22e0
                0x0000000000463d20                data = .
                0x0000000000463d20                _data = .
                0x0000000000463d20                __data = .
 *(.data)
 .data          0x0000000000463d20      0x4c4 crt0.o
 *fill*         0x00000000004641e4       0x1c 
 .data          0x0000000000464200      0x538 main.o
                0x00000000004646a0                running
                0x00000000004646a4                primary_prompt
                0x00000000004646a8                secondary_prompt
                0x00000000004646ac                remember_on_history
                0x00000000004646b0                current_command_number
                0x00000000004646b4                bashrc_file
                0x00000000004646b8                shell_config_file
                0x00000000004646bc                deltaValue
                0x00000000004646c0                long_args
 *fill*         0x0000000000464738        0x8 
 .data          0x0000000000464740      0x4a0 shellui.o
 .data          0x0000000000464be0      0x440 api.o
 .data          0x0000000000465020        0x0 ctype.o
 .data          0x0000000000465020        0x0 stdio.o
 .data          0x0000000000465020        0x8 stdlib.o
                0x0000000000465020                _infinity
 .data          0x0000000000465028        0x0 string.o
 .data          0x0000000000465028        0x0 conio.o
 *fill*         0x0000000000465028       0x18 
 .data          0x0000000000465040      0x4a0 builtins.o
 .data          0x00000000004654e0      0x4a8 desktop.o
                0x0000000000465980                primary_desktop_folder
                0x0000000000465984                secondary_desktop_folder
 .data          0x0000000000465988        0x0 unistd.o
                0x0000000000466000                . = ALIGN (0x1000)
 *fill*         0x0000000000465988      0x678 

.got            0x0000000000466000        0x0
 .got           0x0000000000466000        0x0 unistd.o

.got.plt        0x0000000000466000        0x0
 .got.plt       0x0000000000466000        0x0 unistd.o

.igot.plt       0x0000000000466000        0x0
 .igot.plt      0x0000000000466000        0x0 unistd.o

.bss            0x0000000000466000    0x16d34
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
 *fill*         0x0000000000466070       0x10 
 .bss           0x0000000000466080     0x8004 api.o
 .bss           0x000000000046e084        0x0 ctype.o
 .bss           0x000000000046e084        0x1 stdio.o
 *fill*         0x000000000046e085       0x1b 
 .bss           0x000000000046e0a0     0x8020 stdlib.o
                0x000000000046e0a0                environ
 .bss           0x00000000004760c0        0x4 string.o
 .bss           0x00000000004760c4        0x0 conio.o
 .bss           0x00000000004760c4        0x8 builtins.o
 .bss           0x00000000004760cc        0x8 desktop.o
 .bss           0x00000000004760d4        0x0 unistd.o
                0x0000000000477000                . = ALIGN (0x1000)
 *fill*         0x00000000004760d4      0xf2c 
 COMMON         0x0000000000477000     0x5480 crt0.o
                0x0000000000477000                g_cursor_x
                0x0000000000477004                CurrentWindow
                0x0000000000477008                backgroung_color
                0x000000000047700c                wsWindowHeight
                0x0000000000477010                stdout
                0x0000000000477014                menu_button
                0x0000000000477018                screen_buffer_y
                0x000000000047701c                wlFullScreenLeft
                0x0000000000477020                close_button
                0x0000000000477024                smCursorHeight
                0x0000000000477040                pathname_buffer
                0x0000000000477080                textCurrentRow
                0x0000000000477084                g_char_attrib
                0x0000000000477088                g_rows
                0x000000000047708c                app4_button
                0x0000000000477090                smMousePointerWidth
                0x0000000000477094                smMousePointerHeight
                0x0000000000477098                filename_buffer
                0x00000000004770c0                Streams
                0x0000000000477140                textWheelDelta
                0x0000000000477144                app1_button
                0x0000000000477148                g_using_gui
                0x000000000047714c                wlMinRows
                0x0000000000477150                current_volume_string
                0x0000000000477154                ShellMetrics
                0x0000000000477158                smCharHeight
                0x000000000047715c                ApplicationInfo
                0x0000000000477160                foregroung_color
                0x0000000000477180                prompt_out
                0x0000000000477580                shell_info
                0x0000000000477598                BufferInfo
                0x000000000047759c                ShellHook
                0x00000000004775a0                lineList
                0x00000000004795a0                wlMaxWindowHeight
                0x00000000004795a4                wlMaxRows
                0x00000000004795a8                textCurrentCol
                0x00000000004795ac                textSavedCol
                0x00000000004795b0                current_volume_id
                0x00000000004795b4                smCharWidth
                0x00000000004795b8                g_current_workingdirectory_id
                0x00000000004795bc                wlFullScreenHeight
                0x00000000004795c0                textTopRow
                0x00000000004795c4                textMinWheelDelta
                0x00000000004795c8                g_columns
                0x00000000004795cc                prompt_pos
                0x00000000004795d0                stdin
                0x00000000004795d4                pathname_lenght
                0x00000000004795d8                wlMinWindowHeight
                0x00000000004795dc                textBottomRow
                0x00000000004795e0                wlMinColumns
                0x00000000004795e4                prompt_status
                0x00000000004795e8                pwd_initialized
                0x00000000004795ec                root
                0x00000000004795f0                CurrentCommand
                0x00000000004795f4                screen_buffer_x
                0x00000000004795f8                wlMinWindowWidth
                0x00000000004795fc                CommandHistory
                0x0000000000479600                app3_button
                0x0000000000479620                prompt_err
                0x0000000000479a20                pwd
                0x0000000000479a40                screen_buffer
                0x000000000047a9e4                reboot_button
                0x000000000047a9e8                dummycompiler
                0x000000000047a9ec                smScreenWidth
                0x000000000047a9f0                textMaxWheelDelta
                0x000000000047a9f4                CursorInfo
                0x000000000047a9f8                app2_button
                0x000000000047a9fc                smScreenHeight
                0x000000000047aa00                wlMaxWindowWidth
                0x000000000047aa04                screen_buffer_pos
                0x000000000047aa08                smCursorWidth
                0x000000000047aa0c                wpWindowLeft
                0x000000000047aa10                terminal_rect
                0x000000000047aa20                stderr
                0x000000000047aa24                wlFullScreenTop
                0x000000000047aa28                wsWindowWidth
                0x000000000047aa2c                g_current_disk_id
                0x000000000047aa30                editboxWindow
                0x000000000047aa40                prompt
                0x000000000047ae40                rect
                0x000000000047ae44                taskbarWindow
                0x000000000047ae48                EOF_Reached
                0x000000000047ae4c                g_cursor_y
                0x000000000047ae60                screenbufferList
                0x000000000047ae80                ClientAreaInfo
                0x000000000047ae84                pathname_initilized
                0x000000000047ae88                wpWindowTop
                0x000000000047ae8c                filename_lenght
                0x000000000047ae90                current_semaphore
                0x000000000047ae94                wlFullScreenWidth
                0x000000000047ae98                prompt_max
                0x000000000047ae9c                wlMaxColumns
                0x000000000047aea0                textSavedRow
                0x000000000047aea4                filename_initilized
                0x000000000047aec0                LINES
                0x000000000047c440                g_current_volume_id
                0x000000000047c460                current_workingdiretory_string
 COMMON         0x000000000047c480       0x40 main.o
                0x000000000047c480                password
                0x000000000047c48c                objectY
                0x000000000047c490                username
                0x000000000047c49c                deltaY
                0x000000000047c4a0                shellStatus
                0x000000000047c4a4                shell_environment
                0x000000000047c4a8                objectX
                0x000000000047c4ac                shell_name
                0x000000000047c4b0                build_version
                0x000000000047c4b4                deltaX
                0x000000000047c4b8                shellError
                0x000000000047c4bc                dist_version
 COMMON         0x000000000047c4c0      0x438 api.o
                0x000000000047c4c0                heapList
                0x000000000047c8c0                libcHeap
                0x000000000047c8c4                dialogbox_button2
                0x000000000047c8c8                messagebox_button1
                0x000000000047c8cc                heap_start
                0x000000000047c8d0                g_available_heap
                0x000000000047c8d4                g_heap_pointer
                0x000000000047c8d8                HEAP_SIZE
                0x000000000047c8dc                dialogbox_button1
                0x000000000047c8e0                heap_end
                0x000000000047c8e4                HEAP_END
                0x000000000047c8e8                messagebox_button2
                0x000000000047c8ec                Heap
                0x000000000047c8f0                heapCount
                0x000000000047c8f4                HEAP_START
 *fill*         0x000000000047c8f8        0x8 
 COMMON         0x000000000047c900      0x434 stdlib.o
                0x000000000047c900                mm_prev_pointer
                0x000000000047c920                mmblockList
                0x000000000047cd20                last_valid
                0x000000000047cd24                randseed
                0x000000000047cd28                mmblockCount
                0x000000000047cd2c                last_size
                0x000000000047cd30                current_mmblock
                0x000000000047cd34                end = .
                0x000000000047cd34                _end = .
                0x000000000047cd34                __end = .
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
