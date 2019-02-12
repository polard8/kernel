
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
 .text          0x0000000000458100     0x28d1 stdio.o
                0x0000000000458148                stdio_atoi
                0x000000000045820f                stdio_fntos
                0x0000000000458339                fclose
                0x000000000045839f                fopen
                0x00000000004584d1                scroll
                0x000000000045859f                puts
                0x00000000004585ba                fread
                0x00000000004585c4                fwrite
                0x000000000045898f                printf3
                0x00000000004589ac                printf_atoi
                0x0000000000458a9c                printf_i2hex
                0x0000000000458afe                printf2
                0x0000000000458c83                sprintf
                0x0000000000458cd8                putchar
                0x0000000000458cf9                outbyte
                0x0000000000458eb7                _outbyte
                0x0000000000458ee6                input
                0x000000000045903a                stdio_system_call
                0x0000000000459062                getchar
                0x000000000045907a                stdioInitialize
                0x0000000000459267                fflush
                0x00000000004592fa                fprintf
                0x000000000045936b                fputs
                0x00000000004593dc                gets
                0x0000000000459467                ungetc
                0x000000000045949e                ftell
                0x00000000004594bf                fileno
                0x00000000004594d7                fgetc
                0x0000000000459545                feof
                0x000000000045957a                ferror
                0x0000000000459595                fseek
                0x0000000000459601                fputc
                0x0000000000459650                stdioSetCursor
                0x0000000000459668                stdioGetCursorX
                0x0000000000459680                stdioGetCursorY
                0x0000000000459698                scanf
                0x0000000000459832                fscanf
                0x000000000045984f                sscanf
                0x0000000000459a0a                kvprintf
                0x000000000045a874                printf
                0x000000000045a89e                vfprintf
                0x000000000045a913                stdout_printf
                0x000000000045a93f                stderr_printf
                0x000000000045a96b                perror
                0x000000000045a982                rewind
                0x000000000045a9bd                snprintf
 .text          0x000000000045a9d1     0x10ac stdlib.o
                0x000000000045a9ee                stdlib_system_call
                0x000000000045aa16                rtGetHeapStart
                0x000000000045aa20                rtGetHeapEnd
                0x000000000045aa2a                rtGetHeapPointer
                0x000000000045aa34                rtGetAvailableHeap
                0x000000000045aa3e                heapSetLibcHeap
                0x000000000045aaf1                AllocateHeap
                0x000000000045ad33                AllocateHeapEx
                0x000000000045ad49                FreeHeap
                0x000000000045ad53                heapInit
                0x000000000045aee6                stdlibInitMM
                0x000000000045af49                libcInitRT
                0x000000000045af6b                rand
                0x000000000045af88                srand
                0x000000000045af96                xmalloc
                0x000000000045afc8                stdlib_die
                0x000000000045affe                malloc
                0x000000000045b03a                realloc
                0x000000000045b077                free
                0x000000000045b07d                calloc
                0x000000000045b0c3                zmalloc
                0x000000000045b0ff                system
                0x000000000045b4c3                stdlib_strncmp
                0x000000000045b526                __findenv
                0x000000000045b5f1                getenv
                0x000000000045b61e                atoi
                0x000000000045b6e5                reverse
                0x000000000045b74c                itoa
                0x000000000045b7fa                abs
                0x000000000045b80a                strtod
                0x000000000045ba3c                strtof
                0x000000000045ba58                strtold
                0x000000000045ba6b                atof
 .text          0x000000000045ba7d      0x772 string.o
                0x000000000045ba7d                memcmp
                0x000000000045bae2                strdup
                0x000000000045bb34                strndup
                0x000000000045bb95                strrchr
                0x000000000045bbd0                strtoimax
                0x000000000045bbda                strtoumax
                0x000000000045bbe4                strcasecmp
                0x000000000045bc4c                strncpy
                0x000000000045bca2                strcmp
                0x000000000045bd07                strncmp
                0x000000000045bd6a                memset
                0x000000000045bdb1                memoryZeroMemory
                0x000000000045bdd8                memcpy
                0x000000000045be15                strcpy
                0x000000000045be49                strcat
                0x000000000045be78                bcopy
                0x000000000045bea4                bzero
                0x000000000045bec4                strlen
                0x000000000045bef2                strnlen
                0x000000000045bf26                strcspn
                0x000000000045bfc5                strspn
                0x000000000045c064                strtok_r
                0x000000000045c14b                strtok
                0x000000000045c163                strchr
                0x000000000045c18f                strstr
 .text          0x000000000045c1ef       0x89 conio.o
                0x000000000045c1ef                putch
                0x000000000045c213                cputs
                0x000000000045c248                getch
                0x000000000045c260                getche
 .text          0x000000000045c278      0x16f builtins.o
                0x000000000045c278                cd_buitins
                0x000000000045c291                cls_builtins
                0x000000000045c29f                copy_builtins
                0x000000000045c2a5                date_builtins
                0x000000000045c2ab                del_builtins
                0x000000000045c2b1                dir_builtins
                0x000000000045c2ed                echo_builtins
                0x000000000045c309                exec_builtins
                0x000000000045c322                exit_builtins
                0x000000000045c348                getpid_builtins
                0x000000000045c35a                getppid_builtins
                0x000000000045c36c                getuid_builtins
                0x000000000045c37e                getgid_builtins
                0x000000000045c390                help_builtins
                0x000000000045c3cb                pwd_builtins
 .text          0x000000000045c3e7       0x49 desktop.o
                0x000000000045c3e7                desktopInitialize
 .text          0x000000000045c430       0x67 unistd.o
                0x000000000045c430                unistd_system_call
                0x000000000045c458                execve
                0x000000000045c462                exit
                0x000000000045c482                fork
                0x000000000045d000                . = ALIGN (0x1000)
 *fill*         0x000000000045c497      0xb69 

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
