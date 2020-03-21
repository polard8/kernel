
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
errno               0x4               unistd.o
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


.text           0x0000000000401000     0xd000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000       0x6f crt0.o
                0x0000000000401000                crt0
 .text          0x000000000040106f     0x4e5b main.o
                0x000000000040106f                __SendMessageToProcess
                0x00000000004010b2                updateObject
                0x000000000040119a                quit
                0x00000000004011aa                shellProcedure
                0x0000000000401559                shellWaitCmd
                0x0000000000401572                shellCompare
                0x0000000000403438                shellInitSystemMetrics
                0x00000000004034d1                shellInitWindowLimits
                0x000000000040358f                shellInitWindowSizes
                0x00000000004035db                shellInitWindowPosition
                0x00000000004035f5                shellShell
                0x000000000040377c                shellInit
                0x000000000040386c                shellCheckPassword
                0x0000000000403b8d                shellSetCursor
                0x0000000000403bc8                shellThread
                0x0000000000403c45                shellHelp
                0x0000000000403c5e                shellTree
                0x0000000000403c77                shellPrompt
                0x0000000000403d17                shellClearBuffer
                0x0000000000403dc1                shellShowScreenBuffer
                0x0000000000403dcf                shellTestLoadFile
                0x0000000000403e3b                shellTestThreads
                0x0000000000403ee9                shellClearScreen
                0x0000000000403f62                shellRefreshScreen
                0x0000000000404004                shellRefreshLine
                0x000000000040407a                shellRefreshChar
                0x00000000004040d6                shellRefreshCurrentChar
                0x000000000040410e                shellScroll
                0x00000000004041cb                shellInsertCharXY
                0x0000000000404220                shellGetCharXY
                0x0000000000404253                testScrollChar
                0x0000000000404289                shellInsertNextChar
                0x000000000040432d                shellInsertCR
                0x0000000000404343                shellInsertLF
                0x0000000000404359                shellInsertNullTerminator
                0x000000000040436f                shellTestMBR
                0x00000000004043ca                move_to
                0x00000000004043f6                shellShowInfo
                0x0000000000404461                shellShowMetrics
                0x0000000000404513                shellShowSystemInfo
                0x000000000040458e                shellShowWindowInfo
                0x0000000000404655                shellSendMessage
                0x0000000000404671                shell_memcpy_bytes
                0x000000000040469e                shellExit
                0x00000000004046b5                shellUpdateWorkingDiretoryString
                0x0000000000404714                shellInitializeWorkingDiretoryString
                0x000000000040479e                shellUpdateCurrentDirectoryID
                0x00000000004047ac                shellTaskList
                0x00000000004048cf                shellShowPID
                0x00000000004048ee                shellShowPPID
                0x000000000040490d                shellShowUID
                0x000000000040492c                shellShowGID
                0x000000000040494b                shellShowUserSessionID
                0x0000000000404978                shellShowWindowStationID
                0x00000000004049a5                shellShowDesktopID
                0x00000000004049d2                shellShowProcessHeapPointer
                0x0000000000404a0e                shellShowKernelHeapPointer
                0x0000000000404a49                shellShowDiskInfo
                0x0000000000404a65                shellShowVolumeInfo
                0x0000000000404a81                shellShowMemoryInfo
                0x0000000000404a9d                shellShowPCIInfo
                0x0000000000404ab9                shellShowKernelInfo
                0x0000000000404ad5                shell_fntos
                0x0000000000404bef                shell_gramado_core_init_execve
                0x0000000000404c5a                feedterminalDialog
                0x0000000000404cf4                die
                0x0000000000404d36                concat
                0x0000000000404dec                error
                0x0000000000404e40                fatal
                0x0000000000404e6a                save_string
                0x0000000000404ea6                shellExecuteThisScript
                0x0000000000404f53                absolute_pathname
                0x00000000004050b9                shellInitPathname
                0x0000000000405109                shellInitFilename
                0x0000000000405159                shell_pathname_backup
                0x00000000004051d0                shell_print_tokenList
                0x0000000000405274                is_bin
                0x00000000004052e5                is_sh1
                0x0000000000405356                show_shell_version
                0x0000000000405380                shell_save_file
                0x00000000004054f5                textSetTopRow
                0x0000000000405503                textGetTopRow
                0x000000000040550d                textSetBottomRow
                0x000000000040551b                textGetBottomRow
                0x0000000000405525                clearLine
                0x000000000040558d                testShowLines
                0x000000000040562a                shellRefreshVisibleArea
                0x0000000000405702                testChangeVisibleArea
                0x000000000040572c                updateVisibleArea
                0x000000000040578f                shellSocketTest
                0x00000000004058fa                main
 .text          0x0000000000405eca      0x767 shellui.o
                0x0000000000405eca                shellui_fntos
                0x0000000000405fe4                shellTopbarProcedure
                0x0000000000406148                shellCreateEditBox
                0x00000000004061b6                shellCreateMainWindow
                0x000000000040629b                testCreateWindow
                0x0000000000406324                shellDisplayBMP
                0x0000000000406398                shellDisplayBMPEx
                0x0000000000406424                shellTestDisplayBMP
                0x0000000000406486                bmpDisplayBMP
                0x00000000004064a3                shellTestButtons
 .text          0x0000000000406631     0x213a api.o
                0x0000000000406631                system_call
                0x0000000000406659                apiSystem
                0x0000000000406a61                system1
                0x0000000000406a82                system2
                0x0000000000406aa3                system3
                0x0000000000406ac4                system4
                0x0000000000406ae5                system5
                0x0000000000406b06                system6
                0x0000000000406b27                system7
                0x0000000000406b48                system8
                0x0000000000406b69                system9
                0x0000000000406b8a                system10
                0x0000000000406bab                system11
                0x0000000000406bcc                system12
                0x0000000000406bed                system13
                0x0000000000406c0e                system14
                0x0000000000406c2f                system15
                0x0000000000406c50                refresh_buffer
                0x0000000000406d28                print_string
                0x0000000000406d2e                vsync
                0x0000000000406d43                edit_box
                0x0000000000406d5a                gde_system_procedure
                0x0000000000406d90                SetNextWindowProcedure
                0x0000000000406d9a                set_cursor
                0x0000000000406db1                put_char
                0x0000000000406db7                gde_load_bitmap_16x16
                0x0000000000406dd0                apiShutDown
                0x0000000000406de7                apiInitBackground
                0x0000000000406ded                MessageBox
                0x0000000000407384                mbProcedure
                0x00000000004073fa                DialogBox
                0x00000000004077b5                dbProcedure
                0x000000000040782b                call_kernel
                0x0000000000407953                call_gui
                0x00000000004079e8                gde_create_window
                0x0000000000407a61                gde_register_window
                0x0000000000407a89                gde_close_window
                0x0000000000407ab1                gde_set_focus
                0x0000000000407ad9                gde_get_focus
                0x0000000000407aee                APIKillFocus
                0x0000000000407b16                APISetActiveWindow
                0x0000000000407b3e                APIGetActiveWindow
                0x0000000000407b53                APIShowCurrentProcessInfo
                0x0000000000407b69                APIresize_window
                0x0000000000407b83                APIredraw_window
                0x0000000000407b9d                APIreplace_window
                0x0000000000407bb7                APImaximize_window
                0x0000000000407bd3                APIminimize_window
                0x0000000000407bef                APIupdate_window
                0x0000000000407c0b                APIget_foregroung_window
                0x0000000000407c21                APIset_foregroung_window
                0x0000000000407c3d                apiExit
                0x0000000000407c5a                kill
                0x0000000000407c60                dead_thread_collector
                0x0000000000407c76                api_strncmp
                0x0000000000407cd9                refresh_screen
                0x0000000000407cef                api_refresh_screen
                0x0000000000407cfa                apiReboot
                0x0000000000407d10                apiSetCursor
                0x0000000000407d28                apiGetCursorX
                0x0000000000407d40                apiGetCursorY
                0x0000000000407d58                apiGetClientAreaRect
                0x0000000000407d70                apiSetClientAreaRect
                0x0000000000407d8f                gde_create_process
                0x0000000000407da8                gde_create_thread
                0x0000000000407dc1                apiStartThread
                0x0000000000407ddd                apiFOpen
                0x0000000000407e09                gde_save_file
                0x0000000000407e5c                apiDown
                0x0000000000407eb1                apiUp
                0x0000000000407f06                enterCriticalSection
                0x0000000000407f41                exitCriticalSection
                0x0000000000407f5a                initializeCriticalSection
                0x0000000000407f73                gde_begin_paint
                0x0000000000407f7e                gde_end_paint
                0x0000000000407f89                apiPutChar
                0x0000000000407fa5                apiDefDialog
                0x0000000000407faf                apiGetSystemMetrics
                0x0000000000407fcd                api_set_current_keyboard_responder
                0x0000000000407fec                api_get_current_keyboard_responder
                0x0000000000408004                api_set_current_mouse_responder
                0x0000000000408023                api_get_current_mouse_responder
                0x000000000040803b                api_set_window_with_text_input
                0x000000000040807d                api_get_window_with_text_input
                0x0000000000408095                gramadocore_init_execve
                0x000000000040809f                apiDialog
                0x0000000000408138                api_getchar
                0x0000000000408150                apiDisplayBMP
                0x0000000000408557                apiSendMessageToProcess
                0x000000000040859a                apiSendMessageToThread
                0x00000000004085dd                apiSendMessage
                0x0000000000408613                apiDrawText
                0x0000000000408652                apiGetWSScreenWindow
                0x000000000040866a                apiGetWSMainWindow
                0x0000000000408682                apiCreateTimer
                0x000000000040869f                apiGetSysTimeInfo
                0x00000000004086bd                apiShowWindow
                0x00000000004086d9                apiStartTerminal
                0x000000000040874d                apiUpdateStatusBar
 .text          0x000000000040876b        0x0 ctype.o
 .text          0x000000000040876b     0x2830 stdio.o
                0x00000000004087b3                stdio_atoi
                0x000000000040887a                stdio_fntos
                0x00000000004089a4                fclose
                0x00000000004089c5                fopen
                0x00000000004089e6                scroll
                0x0000000000408ab3                puts
                0x0000000000408ace                fread
                0x0000000000408aef                fwrite
                0x0000000000408ed1                printf3
                0x0000000000408eee                printf_atoi
                0x0000000000408fdf                printf_i2hex
                0x0000000000409041                printf2
                0x00000000004091c6                sprintf
                0x000000000040921b                putchar
                0x0000000000409266                libc_set_output_mode
                0x00000000004092aa                outbyte
                0x0000000000409468                _outbyte
                0x0000000000409497                input
                0x00000000004095f4                getchar
                0x0000000000409622                stdioInitialize
                0x00000000004097c4                fflush
                0x00000000004097e5                fprintf
                0x0000000000409873                fputs
                0x0000000000409894                gets
                0x0000000000409923                ungetc
                0x0000000000409944                ftell
                0x0000000000409965                fileno
                0x0000000000409986                fgetc
                0x00000000004099a7                feof
                0x00000000004099c8                ferror
                0x00000000004099e9                fseek
                0x0000000000409a0a                fputc
                0x0000000000409aa5                stdioSetCursor
                0x0000000000409ac0                stdioGetCursorX
                0x0000000000409adb                stdioGetCursorY
                0x0000000000409af6                scanf
                0x0000000000409c97                sscanf
                0x0000000000409e52                kvprintf
                0x000000000040acbc                printf
                0x000000000040acea                printf_draw
                0x000000000040ad32                vfprintf
                0x000000000040adaa                vprintf
                0x000000000040adc9                stdout_printf
                0x000000000040adf5                stderr_printf
                0x000000000040ae21                perror
                0x000000000040ae38                rewind
                0x000000000040ae62                snprintf
                0x000000000040ae76                stdio_initialize_standard_streams
                0x000000000040aea1                libcStartTerminal
                0x000000000040af14                setbuf
                0x000000000040af36                setbuffer
                0x000000000040af58                setlinebuf
                0x000000000040af7a                setvbuf
 .text          0x000000000040af9b     0x105e stdlib.o
                0x000000000040afb8                rtGetHeapStart
                0x000000000040afc2                rtGetHeapEnd
                0x000000000040afcc                rtGetHeapPointer
                0x000000000040afd6                rtGetAvailableHeap
                0x000000000040afe0                heapSetLibcHeap
                0x000000000040b093                heapAllocateMemory
                0x000000000040b2c5                FreeHeap
                0x000000000040b2cf                heapInit
                0x000000000040b462                stdlibInitMM
                0x000000000040b4c5                libcInitRT
                0x000000000040b4e7                rand
                0x000000000040b504                srand
                0x000000000040b512                xmalloc
                0x000000000040b544                stdlib_die
                0x000000000040b57a                malloc
                0x000000000040b5b6                realloc
                0x000000000040b5f3                free
                0x000000000040b5f9                calloc
                0x000000000040b63f                zmalloc
                0x000000000040b67b                system
                0x000000000040ba3f                stdlib_strncmp
                0x000000000040baa2                __findenv
                0x000000000040bb6d                getenv
                0x000000000040bb9a                atoi
                0x000000000040bc61                reverse
                0x000000000040bcc9                itoa
                0x000000000040bd77                abs
                0x000000000040bd87                strtod
                0x000000000040bfb8                strtof
                0x000000000040bfd4                strtold
                0x000000000040bfe7                atof
 .text          0x000000000040bff9      0xb2b string.o
                0x000000000040bff9                strcoll
                0x000000000040c012                memsetw
                0x000000000040c03e                memcmp
                0x000000000040c0a3                strdup
                0x000000000040c0f5                strndup
                0x000000000040c156                strnchr
                0x000000000040c18f                strrchr
                0x000000000040c1ca                strtoimax
                0x000000000040c1d4                strtoumax
                0x000000000040c1de                strcasecmp
                0x000000000040c246                strncpy
                0x000000000040c29c                strcmp
                0x000000000040c301                strncmp
                0x000000000040c364                memset
                0x000000000040c3ab                memoryZeroMemory
                0x000000000040c3d2                memcpy
                0x000000000040c40f                strcpy
                0x000000000040c443                strlcpy
                0x000000000040c4a2                strcat
                0x000000000040c4d1                strchrnul
                0x000000000040c4f6                strlcat
                0x000000000040c586                strncat
                0x000000000040c5e8                bcopy
                0x000000000040c615                bzero
                0x000000000040c636                strlen
                0x000000000040c664                strnlen
                0x000000000040c69f                strpbrk
                0x000000000040c6ed                strsep
                0x000000000040c76b                strreplace
                0x000000000040c7a6                strcspn
                0x000000000040c845                strspn
                0x000000000040c8e4                strtok_r
                0x000000000040c9cb                strtok
                0x000000000040c9e3                strchr
                0x000000000040ca0f                memmove
                0x000000000040ca90                memscan
                0x000000000040cac4                strstr
 .text          0x000000000040cb24       0x89 conio.o
                0x000000000040cb24                putch
                0x000000000040cb48                cputs
                0x000000000040cb7d                getch
                0x000000000040cb95                getche
 .text          0x000000000040cbad      0x18a builtins.o
                0x000000000040cbad                cd_buitins
                0x000000000040cbc6                cls_builtins
                0x000000000040cbd4                copy_builtins
                0x000000000040cbda                date_builtins
                0x000000000040cbe0                del_builtins
                0x000000000040cbe6                dir_builtins
                0x000000000040cc22                echo_builtins
                0x000000000040cc3e                exec_builtins
                0x000000000040cc57                exit_builtins
                0x000000000040cc7d                getpid_builtins
                0x000000000040cc8f                getppid_builtins
                0x000000000040cca1                getuid_builtins
                0x000000000040ccb3                getgid_builtins
                0x000000000040ccc5                help_builtins
                0x000000000040cd1b                pwd_builtins
 .text          0x000000000040cd37       0x49 desktop.o
                0x000000000040cd37                desktopInitialize
 .text          0x000000000040cd80      0x31f unistd.o
                0x000000000040cd80                execv
                0x000000000040cd9e                execve
                0x000000000040cdfd                exit
                0x000000000040ce1d                fork
                0x000000000040ce53                sys_fork
                0x000000000040ce89                fast_fork
                0x000000000040ceb1                setuid
                0x000000000040cecc                getuid
                0x000000000040cee7                geteuid
                0x000000000040cef1                getpid
                0x000000000040cf09                getppid
                0x000000000040cf21                getgid
                0x000000000040cf3c                dup
                0x000000000040cf56                dup2
                0x000000000040cf72                dup3
                0x000000000040cf90                fcntl
                0x000000000040cf9a                nice
                0x000000000040cfa4                pause
                0x000000000040cfae                mkdir
                0x000000000040cfc2                rmdir
                0x000000000040cfcc                link
                0x000000000040cfd6                mlock
                0x000000000040cfe0                munlock
                0x000000000040cfea                mlockall
                0x000000000040cff4                munlockall
                0x000000000040cffe                sysconf
                0x000000000040d008                fsync
                0x000000000040d012                fdatasync
                0x000000000040d01c                ioctl
                0x000000000040d026                open
                0x000000000040d04c                close
                0x000000000040d06a                pipe
                0x000000000040d08b                fpathconf
                0x000000000040d095                pathconf
 .text          0x000000000040d09f       0x28 stubs.o
                0x000000000040d09f                gramado_system_call
                0x000000000040e000                . = ALIGN (0x1000)
 *fill*         0x000000000040d0c7      0xf39 

.iplt           0x000000000040e000        0x0
 .iplt          0x000000000040e000        0x0 crt0.o

.rodata         0x000000000040e000     0x3dea
 .rodata        0x000000000040e000      0x4e5 crt0.o
 *fill*         0x000000000040e4e5       0x1b 
 .rodata        0x000000000040e500     0x1ae5 main.o
 *fill*         0x000000000040ffe5       0x1b 
 .rodata        0x0000000000410000      0x6c7 shellui.o
 *fill*         0x00000000004106c7        0x1 
 .rodata        0x00000000004106c8      0x41d api.o
 *fill*         0x0000000000410ae5       0x1b 
 .rodata        0x0000000000410b00      0x100 ctype.o
                0x0000000000410b00                _ctype
 .rodata        0x0000000000410c00      0x329 stdio.o
                0x0000000000410d60                hex2ascii_data
 *fill*         0x0000000000410f29        0x7 
 .rodata        0x0000000000410f30      0x510 stdlib.o
 .rodata        0x0000000000411440        0x6 conio.o
 *fill*         0x0000000000411446       0x1a 
 .rodata        0x0000000000411460      0x4b2 builtins.o
 *fill*         0x0000000000411912        0xe 
 .rodata        0x0000000000411920      0x48f desktop.o
 *fill*         0x0000000000411daf        0x1 
 .rodata        0x0000000000411db0       0x3a unistd.o

.eh_frame       0x0000000000411dec     0x3264
 .eh_frame      0x0000000000411dec       0x34 crt0.o
 .eh_frame      0x0000000000411e20      0xc90 main.o
                                        0xca8 (size before relaxing)
 .eh_frame      0x0000000000412ab0      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000412bf0      0xcac api.o
                                        0xcc4 (size before relaxing)
 .eh_frame      0x000000000041389c      0x7f0 stdio.o
                                        0x808 (size before relaxing)
 .eh_frame      0x000000000041408c      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x000000000041448c      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000041494c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x00000000004149ec      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x0000000000414bcc       0x20 desktop.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000414bec      0x440 unistd.o
                                        0x458 (size before relaxing)
 .eh_frame      0x000000000041502c       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x0000000000415050        0x0
 .rel.got       0x0000000000415050        0x0 crt0.o
 .rel.iplt      0x0000000000415050        0x0 crt0.o
 .rel.text      0x0000000000415050        0x0 crt0.o

.data           0x0000000000415060     0x1fa0
                0x0000000000415060                data = .
                0x0000000000415060                _data = .
                0x0000000000415060                __data = .
 *(.data)
 .data          0x0000000000415060      0x4b8 crt0.o
 *fill*         0x0000000000415518        0x8 
 .data          0x0000000000415520      0x53c main.o
                0x00000000004159b4                _running
                0x00000000004159b8                the_current_maintainer
                0x00000000004159bc                primary_prompt
                0x00000000004159c0                secondary_prompt
                0x00000000004159c4                current_user_name
                0x00000000004159c8                current_host_name
                0x00000000004159cc                remember_on_history
                0x00000000004159d0                current_command_number
                0x00000000004159d4                bashrc_file
                0x00000000004159d8                shell_config_file
                0x00000000004159e0                long_args
                0x0000000000415a58                deltaValue
 *fill*         0x0000000000415a5c        0x4 
 .data          0x0000000000415a60      0x492 shellui.o
 *fill*         0x0000000000415ef2        0xe 
 .data          0x0000000000415f00      0x440 api.o
 .data          0x0000000000416340        0x0 ctype.o
 .data          0x0000000000416340        0x0 stdio.o
 .data          0x0000000000416340        0x8 stdlib.o
                0x0000000000416340                _infinity
 .data          0x0000000000416348        0x0 string.o
 .data          0x0000000000416348        0x0 conio.o
 *fill*         0x0000000000416348       0x18 
 .data          0x0000000000416360      0x492 builtins.o
 *fill*         0x00000000004167f2        0xe 
 .data          0x0000000000416800      0x49c desktop.o
                0x0000000000416c94                primary_desktop_folder
                0x0000000000416c98                secondary_desktop_folder
 .data          0x0000000000416c9c        0x0 unistd.o
 .data          0x0000000000416c9c        0x0 stubs.o
                0x0000000000417000                . = ALIGN (0x1000)
 *fill*         0x0000000000416c9c      0x364 

.got            0x0000000000417000        0x0
 .got           0x0000000000417000        0x0 crt0.o

.got.plt        0x0000000000417000        0x0
 .got.plt       0x0000000000417000        0x0 crt0.o

.igot.plt       0x0000000000417000        0x0
 .igot.plt      0x0000000000417000        0x0 crt0.o

.bss            0x0000000000417000    0x16d38
                0x0000000000417000                bss = .
                0x0000000000417000                _bss = .
                0x0000000000417000                __bss = .
 *(.bss)
 .bss           0x0000000000417000        0x8 crt0.o
 .bss           0x0000000000417008       0x5c main.o
                0x0000000000417008                ShellFlag
                0x000000000041700c                executing
                0x0000000000417010                login_status
                0x0000000000417014                shell_initialized
                0x0000000000417018                global_command
                0x000000000041701c                interrupt_state
                0x0000000000417020                login_shell
                0x0000000000417024                interactive
                0x0000000000417028                restricted
                0x000000000041702c                debugging_login_shell
                0x0000000000417030                indirection_level
                0x0000000000417034                shell_level
                0x0000000000417038                act_like_sh
                0x000000000041703c                debugging
                0x0000000000417040                no_rc
                0x0000000000417044                no_profile
                0x0000000000417048                do_version
                0x000000000041704c                quiet
                0x0000000000417050                make_login_shell
                0x0000000000417054                no_line_editing
                0x0000000000417058                no_brace_expansion
 .bss           0x0000000000417064        0x8 shellui.o
 *fill*         0x000000000041706c       0x14 
 .bss           0x0000000000417080     0x8004 api.o
 .bss           0x000000000041f084        0x0 ctype.o
 .bss           0x000000000041f084        0x9 stdio.o
 *fill*         0x000000000041f08d       0x13 
 .bss           0x000000000041f0a0     0x8020 stdlib.o
                0x000000000041f0a0                environ
 .bss           0x00000000004270c0        0x4 string.o
 .bss           0x00000000004270c4        0x0 conio.o
 .bss           0x00000000004270c4        0x8 builtins.o
 .bss           0x00000000004270cc        0x8 desktop.o
 .bss           0x00000000004270d4        0xc unistd.o
                0x00000000004270d4                __execv_environ
 .bss           0x00000000004270e0        0x0 stubs.o
                0x0000000000428000                . = ALIGN (0x1000)
 *fill*         0x00000000004270e0      0xf20 
 COMMON         0x0000000000428000     0x5480 crt0.o
                0x0000000000428000                g_cursor_x
                0x0000000000428004                CurrentWindow
                0x0000000000428008                backgroung_color
                0x000000000042800c                wsWindowHeight
                0x0000000000428010                stdout
                0x0000000000428014                menu_button
                0x0000000000428018                screen_buffer_y
                0x000000000042801c                wlFullScreenLeft
                0x0000000000428020                close_button
                0x0000000000428024                smCursorHeight
                0x0000000000428040                pathname_buffer
                0x0000000000428080                textCurrentRow
                0x0000000000428084                g_char_attrib
                0x0000000000428088                g_rows
                0x000000000042808c                app4_button
                0x0000000000428090                smMousePointerWidth
                0x0000000000428094                smMousePointerHeight
                0x0000000000428098                filename_buffer
                0x00000000004280c0                Streams
                0x0000000000428140                textWheelDelta
                0x0000000000428144                app1_button
                0x0000000000428148                g_using_gui
                0x000000000042814c                wlMinRows
                0x0000000000428150                current_volume_string
                0x0000000000428154                ShellMetrics
                0x0000000000428158                smCharHeight
                0x000000000042815c                ApplicationInfo
                0x0000000000428160                foregroung_color
                0x0000000000428180                prompt_out
                0x0000000000428580                shell_info
                0x0000000000428598                BufferInfo
                0x000000000042859c                ShellHook
                0x00000000004285a0                lineList
                0x000000000042a5a0                wlMaxWindowHeight
                0x000000000042a5a4                wlMaxRows
                0x000000000042a5a8                textCurrentCol
                0x000000000042a5ac                textSavedCol
                0x000000000042a5b0                current_volume_id
                0x000000000042a5b4                smCharWidth
                0x000000000042a5b8                g_current_workingdirectory_id
                0x000000000042a5bc                wlFullScreenHeight
                0x000000000042a5c0                textTopRow
                0x000000000042a5c4                textMinWheelDelta
                0x000000000042a5c8                g_columns
                0x000000000042a5cc                prompt_pos
                0x000000000042a5d0                stdin
                0x000000000042a5d4                pathname_lenght
                0x000000000042a5d8                wlMinWindowHeight
                0x000000000042a5dc                textBottomRow
                0x000000000042a5e0                wlMinColumns
                0x000000000042a5e4                prompt_status
                0x000000000042a5e8                pwd_initialized
                0x000000000042a5ec                root
                0x000000000042a5f0                CurrentCommand
                0x000000000042a5f4                screen_buffer_x
                0x000000000042a5f8                wlMinWindowWidth
                0x000000000042a5fc                CommandHistory
                0x000000000042a600                app3_button
                0x000000000042a620                prompt_err
                0x000000000042aa20                pwd
                0x000000000042aa40                screen_buffer
                0x000000000042b9e4                reboot_button
                0x000000000042b9e8                dummycompiler
                0x000000000042b9ec                smScreenWidth
                0x000000000042b9f0                textMaxWheelDelta
                0x000000000042b9f4                CursorInfo
                0x000000000042b9f8                app2_button
                0x000000000042b9fc                smScreenHeight
                0x000000000042ba00                wlMaxWindowWidth
                0x000000000042ba04                screen_buffer_pos
                0x000000000042ba08                smCursorWidth
                0x000000000042ba0c                wpWindowLeft
                0x000000000042ba10                terminal_rect
                0x000000000042ba20                stderr
                0x000000000042ba24                wlFullScreenTop
                0x000000000042ba28                wsWindowWidth
                0x000000000042ba2c                g_current_disk_id
                0x000000000042ba30                editboxWindow
                0x000000000042ba40                prompt
                0x000000000042be40                rect
                0x000000000042be44                taskbarWindow
                0x000000000042be48                EOF_Reached
                0x000000000042be4c                g_cursor_y
                0x000000000042be60                screenbufferList
                0x000000000042be80                ClientAreaInfo
                0x000000000042be84                pathname_initilized
                0x000000000042be88                wpWindowTop
                0x000000000042be8c                filename_lenght
                0x000000000042be90                current_semaphore
                0x000000000042be94                wlFullScreenWidth
                0x000000000042be98                prompt_max
                0x000000000042be9c                wlMaxColumns
                0x000000000042bea0                textSavedRow
                0x000000000042bea4                filename_initilized
                0x000000000042bec0                LINES
                0x000000000042d440                g_current_volume_id
                0x000000000042d460                current_workingdiretory_string
 COMMON         0x000000000042d480       0x40 main.o
                0x000000000042d480                password
                0x000000000042d48c                objectY
                0x000000000042d490                username
                0x000000000042d49c                deltaY
                0x000000000042d4a0                shellStatus
                0x000000000042d4a4                shell_environment
                0x000000000042d4a8                objectX
                0x000000000042d4ac                shell_name
                0x000000000042d4b0                build_version
                0x000000000042d4b4                deltaX
                0x000000000042d4b8                shellError
                0x000000000042d4bc                dist_version
 COMMON         0x000000000042d4c0      0x438 api.o
                0x000000000042d4c0                heapList
                0x000000000042d8c0                libcHeap
                0x000000000042d8c4                dialogbox_button2
                0x000000000042d8c8                messagebox_button1
                0x000000000042d8cc                heap_start
                0x000000000042d8d0                g_available_heap
                0x000000000042d8d4                g_heap_pointer
                0x000000000042d8d8                HEAP_SIZE
                0x000000000042d8dc                dialogbox_button1
                0x000000000042d8e0                heap_end
                0x000000000042d8e4                HEAP_END
                0x000000000042d8e8                messagebox_button2
                0x000000000042d8ec                Heap
                0x000000000042d8f0                heapCount
                0x000000000042d8f4                HEAP_START
 *fill*         0x000000000042d8f8        0x8 
 COMMON         0x000000000042d900      0x434 stdlib.o
                0x000000000042d900                mm_prev_pointer
                0x000000000042d920                mmblockList
                0x000000000042dd20                last_valid
                0x000000000042dd24                randseed
                0x000000000042dd28                mmblockCount
                0x000000000042dd2c                last_size
                0x000000000042dd30                current_mmblock
 COMMON         0x000000000042dd34        0x4 unistd.o
                0x000000000042dd34                errno
                0x000000000042dd38                end = .
                0x000000000042dd38                _end = .
                0x000000000042dd38                __end = .
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
LOAD stubs.o
OUTPUT(SHELL2.BIN elf32-i386)

.comment        0x0000000000000000       0x22
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 shellui.o
 .comment       0x0000000000000011       0x11 api.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000022       0x12 ctype.o
 .comment       0x0000000000000022       0x12 stdio.o
 .comment       0x0000000000000022       0x12 stdlib.o
 .comment       0x0000000000000022       0x12 string.o
 .comment       0x0000000000000022       0x12 conio.o
 .comment       0x0000000000000022       0x12 builtins.o
 .comment       0x0000000000000022       0x12 desktop.o
 .comment       0x0000000000000022       0x12 unistd.o
 .comment       0x0000000000000022       0x12 stubs.o

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
                0x0000000000000000        0x0 stubs.o
