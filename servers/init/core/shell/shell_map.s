
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
xxxpassword         0xb               login.o
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
xxxusername         0xb               login.o
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
 .text          0x0000000000451075     0x4602 main.o
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
                0x0000000000453773                shellCheckPassword
                0x000000000045377d                shellSetCursor
                0x00000000004537b8                shellThread
                0x0000000000453835                shellShowExperienceMenu
                0x000000000045384e                shellShowTestsMenu
                0x0000000000453867                shellTree
                0x0000000000453880                shellPrompt
                0x0000000000453909                shellClearBuffer
                0x00000000004539b2                shellShowScreenBuffer
                0x00000000004539c0                shellTestLoadFile
                0x0000000000453a2c                shellTestThreads
                0x0000000000453ada                shellClearScreen
                0x0000000000453b53                shellRefreshScreen
                0x0000000000453bf5                shellRefreshLine
                0x0000000000453c6b                shellRefreshChar
                0x0000000000453cc7                shellRefreshCurrentChar
                0x0000000000453cff                shellScroll
                0x0000000000453dbc                shellInsertCharXY
                0x0000000000453e11                shellGetCharXY
                0x0000000000453e44                testScrollChar
                0x0000000000453e79                shellInsertNextChar
                0x0000000000453f1d                shellInsertCR
                0x0000000000453f33                shellInsertLF
                0x0000000000453f49                shellInsertNullTerminator
                0x0000000000453f5f                shellTestMBR
                0x0000000000453fba                move_to
                0x0000000000453fe6                shellShowInfo
                0x0000000000454093                shellShowMetrics
                0x0000000000454145                shellShowSystemInfo
                0x00000000004541c0                shellShowWindowInfo
                0x0000000000454287                shellSendMessage
                0x00000000004542a3                shell_memcpy_bytes
                0x00000000004542cf                shellExit
                0x00000000004542e6                shellUpdateWorkingDiretoryString
                0x0000000000454345                shellInitializeWorkingDiretoryString
                0x00000000004543cf                shellUpdateCurrentDirectoryID
                0x00000000004543dd                shellTaskList
                0x0000000000454500                shellShowPID
                0x000000000045452a                shellShowPPID
                0x0000000000454554                shellShowUID
                0x0000000000454581                shellShowGID
                0x00000000004545ae                shellShowUserSessionID
                0x00000000004545db                shellShowWindowStationID
                0x0000000000454608                shellShowDesktopID
                0x0000000000454635                shellShowProcessHeapPointer
                0x000000000045467c                shellShowKernelHeapPointer
                0x00000000004546b7                shellShowDiskInfo
                0x00000000004546d3                shellShowVolumeInfo
                0x00000000004546ef                shellShowMemoryInfo
                0x000000000045470b                shellShowPCIInfo
                0x0000000000454727                shellShowKernelInfo
                0x0000000000454743                shell_fntos
                0x000000000045485d                shell_gramado_core_init_execve
                0x00000000004548c8                feedterminalDialog
                0x000000000045495a                die
                0x000000000045499c                concat
                0x0000000000454a52                error
                0x0000000000454aa6                fatal
                0x0000000000454ad0                save_string
                0x0000000000454b0c                shellExecuteThisScript
                0x0000000000454bb9                absolute_pathname
                0x0000000000454d1f                shellInitPathname
                0x0000000000454d6f                shellInitFilename
                0x0000000000454dbf                shell_pathname_backup
                0x0000000000454e36                shell_print_tokenList
                0x0000000000454eda                is_bin
                0x0000000000454f4b                is_sh1
                0x0000000000454fbc                show_shell_version
                0x0000000000454fe6                shell_save_file
                0x000000000045515b                save_string2
                0x000000000045526c                textSetTopRow
                0x000000000045527a                textGetTopRow
                0x0000000000455284                textSetBottomRow
                0x0000000000455292                textGetBottomRow
                0x000000000045529c                clearLine
                0x000000000045530a                testShowLines
                0x00000000004553a7                shellRefreshVisibleArea
                0x000000000045547f                testChangeVisibleArea
                0x00000000004554a9                updateVisibleArea
                0x000000000045550c                shellSocketTest
 .text          0x0000000000455677      0x73c shellui.o
                0x0000000000455677                shellui_fntos
                0x0000000000455791                shellTopbarProcedure
                0x00000000004558ea                shellCreateEditBox
                0x0000000000455958                shellCreateMainWindow
                0x0000000000455a14                testCreateWindow
                0x0000000000455aa6                shellDisplayBMP
                0x0000000000455b1a                shellDisplayBMPEx
                0x0000000000455ba6                shellTestDisplayBMP
                0x0000000000455c08                bmpDisplayBMP
                0x0000000000455c25                shellTestButtons
 .text          0x0000000000455db3     0x1fee api.o
                0x0000000000455db3                system_call
                0x0000000000455ddb                apiSystem
                0x00000000004561e3                system1
                0x0000000000456204                system2
                0x0000000000456225                system3
                0x0000000000456246                system4
                0x0000000000456267                system5
                0x0000000000456288                system6
                0x00000000004562a9                system7
                0x00000000004562ca                system8
                0x00000000004562eb                system9
                0x000000000045630c                system10
                0x000000000045632d                system11
                0x000000000045634e                system12
                0x000000000045636f                system13
                0x0000000000456390                system14
                0x00000000004563b1                system15
                0x00000000004563d2                refresh_buffer
                0x00000000004564b0                print_string
                0x00000000004564b6                vsync
                0x00000000004564d0                edit_box
                0x00000000004564ec                chama_procedimento
                0x0000000000456507                SetNextWindowProcedure
                0x0000000000456522                set_cursor
                0x000000000045653e                put_char
                0x0000000000456544                carrega_bitmap_16x16
                0x000000000045655d                apiShutDown
                0x0000000000456574                apiInitBackground
                0x000000000045657a                MessageBox
                0x0000000000456ad0                mbProcedure
                0x0000000000456b3e                DialogBox
                0x0000000000456eb8                dbProcedure
                0x0000000000456f26                call_kernel
                0x00000000004570a1                call_gui
                0x000000000045712d                APICreateWindow
                0x00000000004571a7                APIRegisterWindow
                0x00000000004571d4                APICloseWindow
                0x0000000000457201                APISetFocus
                0x000000000045722e                APIGetFocus
                0x0000000000457243                APIKillFocus
                0x0000000000457270                APISetActiveWindow
                0x000000000045729d                APIGetActiveWindow
                0x00000000004572b2                APIShowCurrentProcessInfo
                0x00000000004572c8                APIresize_window
                0x00000000004572e2                APIredraw_window
                0x00000000004572fc                APIreplace_window
                0x0000000000457316                APImaximize_window
                0x0000000000457332                APIminimize_window
                0x000000000045734e                APIupdate_window
                0x000000000045736a                APIget_foregroung_window
                0x0000000000457380                APIset_foregroung_window
                0x000000000045739c                apiExit
                0x00000000004573b9                kill
                0x00000000004573bf                dead_thread_collector
                0x00000000004573d5                api_strncmp
                0x0000000000457438                refresh_screen
                0x000000000045744e                api_refresh_screen
                0x0000000000457459                apiReboot
                0x000000000045746f                apiSetCursor
                0x0000000000457487                apiGetCursorX
                0x000000000045749f                apiGetCursorY
                0x00000000004574b7                apiGetClientAreaRect
                0x00000000004574cf                apiSetClientAreaRect
                0x00000000004574ee                apiCreateProcess
                0x0000000000457507                apiCreateThread
                0x0000000000457520                apiStartThread
                0x000000000045753c                apiFOpen
                0x0000000000457568                apiSaveFile
                0x00000000004575bb                apiDown
                0x000000000045760e                apiUp
                0x0000000000457661                enterCriticalSection
                0x000000000045769c                exitCriticalSection
                0x00000000004576b5                initializeCriticalSection
                0x00000000004576ce                apiBeginPaint
                0x00000000004576d9                apiEndPaint
                0x00000000004576e4                apiPutChar
                0x0000000000457700                apiDefDialog
                0x000000000045770a                apiGetSystemMetrics
                0x0000000000457728                api_set_current_keyboard_responder
                0x0000000000457747                api_get_current_keyboard_responder
                0x000000000045775f                api_set_current_mouse_responder
                0x000000000045777e                api_get_current_mouse_responder
                0x0000000000457796                api_set_window_with_text_input
                0x00000000004577d8                api_get_window_with_text_input
                0x00000000004577f0                gramadocore_init_execve
                0x00000000004577fa                apiDialog
                0x0000000000457886                api_getchar
                0x000000000045789e                apiDisplayBMP
                0x0000000000457ca5                apiSendMessage
                0x0000000000457cdb                apiDrawText
                0x0000000000457d1a                apiGetWSScreenWindow
                0x0000000000457d32                apiGetWSMainWindow
                0x0000000000457d4a                apiCreateTimer
                0x0000000000457d67                apiGetSysTimeInfo
                0x0000000000457d85                apiShowWindow
 .text          0x0000000000457da1        0x0 ctype.o
 .text          0x0000000000457da1     0x252b stdio.o
                0x0000000000457de9                stdio_atoi
                0x0000000000457eb0                stdio_fntos
                0x0000000000457fda                fclose
                0x0000000000457ffb                fopen
                0x000000000045801c                scroll
                0x00000000004580ea                puts
                0x0000000000458105                fread
                0x000000000045810f                fwrite
                0x00000000004584da                printf3
                0x00000000004584f7                printf_atoi
                0x00000000004585e7                printf_i2hex
                0x0000000000458649                printf2
                0x00000000004587ce                sprintf
                0x0000000000458823                putchar
                0x0000000000458844                outbyte
                0x0000000000458a02                _outbyte
                0x0000000000458a31                input
                0x0000000000458b85                stdio_system_call
                0x0000000000458bad                getchar
                0x0000000000458bc5                stdioInitialize
                0x0000000000458db2                fflush
                0x0000000000458dd0                fprintf
                0x0000000000458dee                fputs
                0x0000000000458e0c                gets
                0x0000000000458e97                ungetc
                0x0000000000458ea1                ftell
                0x0000000000458eab                fileno
                0x0000000000458eb5                fgetc
                0x0000000000458ed3                feof
                0x0000000000458ef1                ferror
                0x0000000000458f0f                fseek
                0x0000000000458f2d                fputc
                0x0000000000458f4b                stdioSetCursor
                0x0000000000458f63                stdioGetCursorX
                0x0000000000458f7b                stdioGetCursorY
                0x0000000000458f93                scanf
                0x000000000045912d                fscanf
                0x000000000045914a                sscanf
                0x0000000000459305                kvprintf
                0x000000000045a16f                printf
                0x000000000045a199                vfprintf
                0x000000000045a20e                stdout_printf
                0x000000000045a23a                stderr_printf
                0x000000000045a266                perror
                0x000000000045a27d                rewind
                0x000000000045a2b8                snprintf
 .text          0x000000000045a2cc     0x10ac stdlib.o
                0x000000000045a2e9                stdlib_system_call
                0x000000000045a311                rtGetHeapStart
                0x000000000045a31b                rtGetHeapEnd
                0x000000000045a325                rtGetHeapPointer
                0x000000000045a32f                rtGetAvailableHeap
                0x000000000045a339                heapSetLibcHeap
                0x000000000045a3ec                AllocateHeap
                0x000000000045a62e                AllocateHeapEx
                0x000000000045a644                FreeHeap
                0x000000000045a64e                heapInit
                0x000000000045a7e1                stdlibInitMM
                0x000000000045a844                libcInitRT
                0x000000000045a866                rand
                0x000000000045a883                srand
                0x000000000045a891                xmalloc
                0x000000000045a8c3                stdlib_die
                0x000000000045a8f9                malloc
                0x000000000045a935                realloc
                0x000000000045a972                free
                0x000000000045a978                calloc
                0x000000000045a9be                zmalloc
                0x000000000045a9fa                system
                0x000000000045adbe                stdlib_strncmp
                0x000000000045ae21                __findenv
                0x000000000045aeec                getenv
                0x000000000045af19                atoi
                0x000000000045afe0                reverse
                0x000000000045b047                itoa
                0x000000000045b0f5                abs
                0x000000000045b105                strtod
                0x000000000045b337                strtof
                0x000000000045b353                strtold
                0x000000000045b366                atof
 .text          0x000000000045b378      0x772 string.o
                0x000000000045b378                memcmp
                0x000000000045b3dd                strdup
                0x000000000045b42f                strndup
                0x000000000045b490                strrchr
                0x000000000045b4cb                strtoimax
                0x000000000045b4d5                strtoumax
                0x000000000045b4df                strcasecmp
                0x000000000045b547                strncpy
                0x000000000045b59d                strcmp
                0x000000000045b602                strncmp
                0x000000000045b665                memset
                0x000000000045b6ac                memoryZeroMemory
                0x000000000045b6d3                memcpy
                0x000000000045b710                strcpy
                0x000000000045b744                strcat
                0x000000000045b773                bcopy
                0x000000000045b79f                bzero
                0x000000000045b7bf                strlen
                0x000000000045b7ed                strnlen
                0x000000000045b821                strcspn
                0x000000000045b8c0                strspn
                0x000000000045b95f                strtok_r
                0x000000000045ba46                strtok
                0x000000000045ba5e                strchr
                0x000000000045ba8a                strstr
 .text          0x000000000045baea       0x89 conio.o
                0x000000000045baea                putch
                0x000000000045bb0e                cputs
                0x000000000045bb43                getch
                0x000000000045bb5b                getche
 .text          0x000000000045bb73      0x16f builtins.o
                0x000000000045bb73                cd_buitins
                0x000000000045bb8c                cls_builtins
                0x000000000045bb9a                copy_builtins
                0x000000000045bba0                date_builtins
                0x000000000045bba6                del_builtins
                0x000000000045bbac                dir_builtins
                0x000000000045bbe8                echo_builtins
                0x000000000045bc04                exec_builtins
                0x000000000045bc1d                exit_builtins
                0x000000000045bc43                getpid_builtins
                0x000000000045bc55                getppid_builtins
                0x000000000045bc67                getuid_builtins
                0x000000000045bc79                getgid_builtins
                0x000000000045bc8b                help_builtins
                0x000000000045bcc6                pwd_builtins
 .text          0x000000000045bce2       0x49 desktop.o
                0x000000000045bce2                desktopInitialize
 .text          0x000000000045bd2b       0x67 unistd.o
                0x000000000045bd2b                unistd_system_call
                0x000000000045bd53                execve
                0x000000000045bd5d                exit
                0x000000000045bd7d                fork
 .text          0x000000000045bd92       0x10 login.o
                0x000000000045bd92                loginCheckPassword
                0x000000000045c000                . = ALIGN (0x1000)
 *fill*         0x000000000045bda2      0x25e 

.iplt           0x000000000045c000        0x0
 .iplt          0x000000000045c000        0x0 login.o

.rodata         0x000000000045c000     0x5980
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
 .rodata        0x000000000045f6e0      0x2f4 stdio.o
                0x000000000045f840                hex2ascii_data
 *fill*         0x000000000045f9d4        0x4 
 .rodata        0x000000000045f9d8      0x500 stdlib.o
 .rodata        0x000000000045fed8        0x6 conio.o
 *fill*         0x000000000045fede        0x2 
 .rodata        0x000000000045fee0      0x8fa builtins.o
 *fill*         0x00000000004607da        0x6 
 .rodata        0x00000000004607e0      0x8ef desktop.o
 *fill*         0x00000000004610cf       0x11 
 .rodata        0x00000000004610e0      0x8a0 login.o

.eh_frame       0x0000000000461980     0x2bf4
 .eh_frame      0x0000000000461980       0x34 crt0.o
 .eh_frame      0x00000000004619b4      0xc9c main.o
                                        0xcb4 (size before relaxing)
 .eh_frame      0x0000000000462650      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000462790      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x00000000004633bc      0x714 stdio.o
                                        0x72c (size before relaxing)
 .eh_frame      0x0000000000463ad0      0x444 stdlib.o
                                        0x45c (size before relaxing)
 .eh_frame      0x0000000000463f14      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x0000000000464234       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x00000000004642d4      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x00000000004644b4       0x20 desktop.o
                                         0x38 (size before relaxing)
 .eh_frame      0x00000000004644d4       0x80 unistd.o
                                         0x98 (size before relaxing)
 .eh_frame      0x0000000000464554       0x20 login.o
                                         0x38 (size before relaxing)

.note.gnu.property
                0x0000000000464574       0x1c
 .note.gnu.property
                0x0000000000464574       0x1c login.o

.rel.dyn        0x0000000000464590        0x0
 .rel.got       0x0000000000464590        0x0 login.o
 .rel.iplt      0x0000000000464590        0x0 login.o
 .rel.text      0x0000000000464590        0x0 login.o

.data           0x00000000004645a0     0x2a60
                0x00000000004645a0                data = .
                0x00000000004645a0                _data = .
                0x00000000004645a0                __data = .
 *(.data)
 .data          0x00000000004645a0      0x4c4 crt0.o
 *fill*         0x0000000000464a64       0x1c 
 .data          0x0000000000464a80      0x538 main.o
                0x0000000000464f20                running
                0x0000000000464f24                primary_prompt
                0x0000000000464f28                secondary_prompt
                0x0000000000464f2c                remember_on_history
                0x0000000000464f30                current_command_number
                0x0000000000464f34                bashrc_file
                0x0000000000464f38                shell_config_file
                0x0000000000464f3c                deltaValue
                0x0000000000464f40                long_args
 *fill*         0x0000000000464fb8        0x8 
 .data          0x0000000000464fc0      0x4a0 shellui.o
 .data          0x0000000000465460      0x440 api.o
 .data          0x00000000004658a0        0x0 ctype.o
 .data          0x00000000004658a0        0x0 stdio.o
 .data          0x00000000004658a0        0x8 stdlib.o
                0x00000000004658a0                _infinity
 .data          0x00000000004658a8        0x0 string.o
 .data          0x00000000004658a8        0x0 conio.o
 *fill*         0x00000000004658a8       0x18 
 .data          0x00000000004658c0      0x4a0 builtins.o
 .data          0x0000000000465d60      0x4a8 desktop.o
                0x0000000000466200                primary_desktop_folder
                0x0000000000466204                secondary_desktop_folder
 .data          0x0000000000466208        0x0 unistd.o
 *fill*         0x0000000000466208       0x18 
 .data          0x0000000000466220      0x4a0 login.o
                0x0000000000467000                . = ALIGN (0x1000)
 *fill*         0x00000000004666c0      0x940 

.got            0x0000000000467000        0x0
 .got           0x0000000000467000        0x0 login.o

.got.plt        0x0000000000467000        0x0
 .got.plt       0x0000000000467000        0x0 login.o

.igot.plt       0x0000000000467000        0x0
 .igot.plt      0x0000000000467000        0x0 login.o

.bss            0x0000000000467000    0x16d4b
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
 .bss           0x00000000004770d4        0x8 login.o
                0x0000000000478000                . = ALIGN (0x1000)
 *fill*         0x00000000004770dc      0xf24 
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
 COMMON         0x000000000047dd34       0x17 login.o
                0x000000000047dd34                xxxpassword
                0x000000000047dd40                xxxusername
                0x000000000047dd4b                end = .
                0x000000000047dd4b                _end = .
                0x000000000047dd4b                __end = .
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
LOAD login.o
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
 .comment       0x000000000000001a       0x1b login.o

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
 .note.GNU-stack
                0x0000000000000000        0x0 login.o
