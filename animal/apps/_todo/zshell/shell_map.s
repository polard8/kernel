
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
password            0xb               main.o
objectY             0x4               main.o
CurrentWindow       0x4               main.o
backgroung_color    0x4               main.o
wsWindowHeight      0x4               main.o
stdout              0x4               crt0.o
menu_button         0x4               main.o
screen_buffer_y     0x4               main.o
wlFullScreenLeft    0x4               main.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
username            0xb               main.o
last_valid          0x4               stdlib.o
heapList            0x400             api.o
close_button        0x4               main.o
libcHeap            0x4               api.o
smCursorHeight      0x4               main.o
pathname_buffer     0x40              main.o
deltaY              0x4               main.o
errno               0x4               unistd.o
textCurrentRow      0x4               main.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
app4_button         0x4               main.o
shellStatus         0x4               main.o
dialogbox_button2   0x4               api.o
smMousePointerWidth
                    0x4               main.o
smMousePointerHeight
                    0x4               main.o
filename_buffer     0xb               main.o
Streams             0x80              crt0.o
optarg              0x4               unistd.o
messagebox_button1  0x4               api.o
textWheelDelta      0x4               main.o
app1_button         0x4               main.o
g_using_gui         0x4               crt0.o
opterr              0x4               unistd.o
wlMinRows           0x4               main.o
current_volume_string
                    0x4               main.o
ShellMetrics        0x4               main.o
smCharHeight        0x4               main.o
ApplicationInfo     0x4               main.o
randseed            0x4               stdlib.o
heap_start          0x4               api.o
foregroung_color    0x4               main.o
prompt_out          0x400             crt0.o
shell_info          0x18              main.o
BufferInfo          0x4               main.o
ShellHook           0x4               main.o
lineList            0x2000            main.o
wlMaxWindowHeight   0x4               main.o
wlMaxRows           0x4               main.o
textCurrentCol      0x4               main.o
shell_environment   0x4               main.o
textSavedCol        0x4               main.o
current_volume_id   0x4               main.o
smCharWidth         0x4               main.o
g_current_workingdirectory_id
                    0x4               main.o
g_available_heap    0x4               api.o
wlFullScreenHeight  0x4               main.o
textTopRow          0x4               main.o
g_heap_pointer      0x4               api.o
textMinWheelDelta   0x4               main.o
g_columns           0x4               crt0.o
my__p               0x4               unistd.o
HEAP_SIZE           0x4               api.o
optind              0x4               unistd.o
mmblockCount        0x4               stdlib.o
dialogbox_button1   0x4               api.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
pathname_lenght     0x4               main.o
last_size           0x4               stdlib.o
wlMinWindowHeight   0x4               main.o
textBottomRow       0x4               main.o
wlMinColumns        0x4               main.o
__Hostname_buffer   0x40              unistd.o
prompt_status       0x4               crt0.o
first_responder     0x4               api.o
__ptsname_buffer    0x40              stdlib.o
objectX             0x4               main.o
pwd_initialized     0x4               main.o
root                0x4               main.o
CurrentCommand      0x4               main.o
shell_name          0x4               main.o
__Login_buffer      0x40              unistd.o
screen_buffer_x     0x4               main.o
wlMinWindowWidth    0x4               main.o
CommandHistory      0x4               main.o
app3_button         0x4               main.o
prompt_err          0x400             crt0.o
pwd                 0x4               main.o
screen_buffer       0xfa1             main.o
reboot_button       0x4               main.o
dummycompiler       0x4               main.o
smScreenWidth       0x4               main.o
textMaxWheelDelta   0x4               main.o
CursorInfo          0x4               main.o
app2_button         0x4               main.o
smScreenHeight      0x4               main.o
wlMaxWindowWidth    0x4               main.o
heap_end            0x4               api.o
screen_buffer_pos   0x4               main.o
build_version       0x4               main.o
smCursorWidth       0x4               main.o
wpWindowLeft        0x4               main.o
terminal_rect       0x10              main.o
stderr              0x4               crt0.o
__mb_current_button
                    0x4               api.o
wlFullScreenTop     0x4               main.o
wsWindowWidth       0x4               main.o
g_current_disk_id   0x4               main.o
editboxWindow       0x4               main.o
optopt              0x4               unistd.o
hWindow             0x4               main.o
deltaX              0x4               main.o
prompt              0x400             crt0.o
HEAP_END            0x4               api.o
taskbarWindow       0x4               main.o
EOF_Reached         0x4               main.o
g_cursor_y          0x4               crt0.o
screenbufferList    0x20              main.o
ClientAreaInfo      0x4               main.o
messagebox_button2  0x4               api.o
Heap                0x4               api.o
pathname_initilized
                    0x4               main.o
wpWindowTop         0x4               main.o
filename_lenght     0x4               main.o
current_semaphore   0x4               main.o
wlFullScreenWidth   0x4               main.o
shellError          0x4               main.o
dist_version        0x4               main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
wlMaxColumns        0x4               main.o
textSavedRow        0x4               main.o
heapCount           0x4               api.o
filename_initilized
                    0x4               main.o
LINES               0x1580            main.o
HEAP_START          0x4               api.o
g_current_volume_id
                    0x4               main.o
current_workingdiretory_string
                    0x20              main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000401000     0xc000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000      0x108 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401108     0x43ec main.o
                0x0000000000401108                __debug_print
                0x000000000040112a                updateObject
                0x0000000000401212                quit
                0x0000000000401222                main
                0x0000000000401819                shellProcedure
                0x00000000004019c8                shellWaitCmd
                0x00000000004019e1                shellCompare
                0x0000000000403010                shellInitSystemMetrics
                0x00000000004030a9                shellInitWindowLimits
                0x0000000000403167                shellInitWindowSizes
                0x00000000004031b3                shellInitWindowPosition
                0x00000000004031cd                shellShell
                0x0000000000403363                shellInit
                0x00000000004033c6                shellCheckPassword
                0x00000000004036e7                shellSetCursor
                0x0000000000403722                shellThread
                0x00000000004037a1                shellHelp
                0x00000000004037ba                shellTree
                0x00000000004037d3                shellPrompt
                0x0000000000403873                shellClearBuffer
                0x000000000040391d                shellShowScreenBuffer
                0x000000000040392b                shellTestLoadFile
                0x0000000000403997                shellTestThreads
                0x0000000000403a45                shellClearScreen
                0x0000000000403abe                shellRefreshScreen
                0x0000000000403b60                shellRefreshLine
                0x0000000000403bd6                shellRefreshChar
                0x0000000000403c32                shellRefreshCurrentChar
                0x0000000000403c6a                shellScroll
                0x0000000000403d27                shellInsertCharXY
                0x0000000000403d7c                shellGetCharXY
                0x0000000000403daf                testScrollChar
                0x0000000000403de5                shellInsertNextChar
                0x0000000000403e89                shellInsertCR
                0x0000000000403e9f                shellInsertLF
                0x0000000000403eb5                shellInsertNullTerminator
                0x0000000000403ecb                shellTestMBR
                0x0000000000403f26                move_to
                0x0000000000403f52                shellShowInfo
                0x0000000000403fff                shellShowMetrics
                0x00000000004040b1                shellShowSystemInfo
                0x000000000040412c                shellShowWindowInfo
                0x00000000004041f3                shellSendMessage
                0x000000000040420f                shell_memcpy_bytes
                0x000000000040423c                shellExit
                0x0000000000404253                shellUpdateWorkingDiretoryString
                0x00000000004042b2                shellInitializeWorkingDiretoryString
                0x000000000040433c                shellUpdateCurrentDirectoryID
                0x000000000040434a                shellTaskList
                0x000000000040446d                shellShowPID
                0x000000000040448c                shellShowPPID
                0x00000000004044ab                shellShowUID
                0x00000000004044b1                shellShowGID
                0x00000000004044d0                shellShowUserSessionID
                0x00000000004044fd                shellShowWindowStationID
                0x000000000040452a                shellShowDesktopID
                0x0000000000404557                shellShowProcessHeapPointer
                0x000000000040459e                shellShowKernelHeapPointer
                0x00000000004045d9                shellShowDiskInfo
                0x00000000004045f5                shellShowVolumeInfo
                0x0000000000404611                shellShowMemoryInfo
                0x000000000040462d                shellShowPCIInfo
                0x0000000000404649                shellShowKernelInfo
                0x0000000000404665                shell_fntos
                0x000000000040477f                shell_gramado_core_init_execve
                0x00000000004047ea                shell_gramado_core_init_execve2
                0x0000000000404855                feedterminalDialog
                0x00000000004048ef                die
                0x0000000000404931                concat
                0x00000000004049e7                error
                0x0000000000404a3b                fatal
                0x0000000000404a65                save_string
                0x0000000000404aa1                shellExecuteThisScript
                0x0000000000404b4e                absolute_pathname
                0x0000000000404cb4                shellInitPathname
                0x0000000000404d04                shellInitFilename
                0x0000000000404d54                shell_pathname_backup
                0x0000000000404dcb                shell_print_tokenList
                0x0000000000404e6f                is_bin
                0x0000000000404ee0                is_sh1
                0x0000000000404f51                show_shell_version
                0x0000000000404f7b                shell_save_file
                0x00000000004050ef                textSetTopRow
                0x00000000004050fd                textGetTopRow
                0x0000000000405107                textSetBottomRow
                0x0000000000405115                textGetBottomRow
                0x000000000040511f                clearLine
                0x0000000000405187                testShowLines
                0x0000000000405224                shellRefreshVisibleArea
                0x00000000004052fc                testChangeVisibleArea
                0x0000000000405326                updateVisibleArea
                0x0000000000405389                shellSocketTest
 .text          0x00000000004054f4      0x73b shellui.o
                0x00000000004054f4                shellui_fntos
                0x000000000040560e                shellTopbarProcedure
                0x0000000000405772                shellCreateEditBox
                0x00000000004057e0                shellCreateMainWindow
                0x0000000000405899                testCreateWindow
                0x0000000000405922                shellDisplayBMP
                0x0000000000405996                shellDisplayBMPEx
                0x0000000000405a22                shellTestDisplayBMP
                0x0000000000405a84                bmpDisplayBMP
                0x0000000000405aa1                shellTestButtons
 .text          0x0000000000405c2f     0x2164 api.o
                0x0000000000405c2f                system_call
                0x0000000000405c57                gde_system
                0x000000000040605f                system1
                0x0000000000406080                system2
                0x00000000004060a1                system3
                0x00000000004060c2                system4
                0x00000000004060e3                system5
                0x0000000000406104                system6
                0x0000000000406125                system7
                0x0000000000406146                system8
                0x0000000000406167                system9
                0x0000000000406188                system10
                0x00000000004061a9                system11
                0x00000000004061ca                system12
                0x00000000004061eb                system13
                0x000000000040620c                system14
                0x000000000040622d                system15
                0x000000000040624e                gde_refresh_buffer
                0x0000000000406326                gde_print_string
                0x000000000040632c                gde_vsync
                0x0000000000406344                gws_vsync
                0x0000000000406351                gde_system_procedure
                0x0000000000406394                __gde_set_cursor
                0x00000000004063ae                __gde_put_char
                0x00000000004063b4                gde_load_bitmap_16x16
                0x00000000004063cd                gde_shutdown
                0x00000000004063e7                gde_init_background
                0x00000000004063ed                gde_message_box
                0x00000000004066f2                mbProcedure
                0x00000000004068ae                gde_dialog_box
                0x0000000000406c69                dbProcedure
                0x0000000000406cdf                call_kernel
                0x0000000000406e07                call_gui
                0x0000000000406e9c                gde_create_window
                0x0000000000406f15                gde_register_window
                0x0000000000406f3d                gde_close_window
                0x0000000000406f65                gde_set_focus
                0x0000000000406f8d                gde_get_focus
                0x0000000000406fa2                gde_kill_focus
                0x0000000000406fca                gde_set_active_window
                0x0000000000406ff2                gde_get_active_window
                0x0000000000407007                gde_show_current_process_info
                0x000000000040701d                gde_resize_window
                0x000000000040703a                gde_redraw_window
                0x0000000000407057                gde_replace_window
                0x0000000000407071                gde_maximize_window
                0x0000000000407090                gde_minimize_window
                0x00000000004070af                gde_update_window
                0x00000000004070d1                gde_get_foregroung_window
                0x00000000004070e7                gde_set_foregroung_window
                0x0000000000407103                gde_exit
                0x0000000000407120                gde_kill
                0x0000000000407126                gde_dead_thread_collector
                0x000000000040713c                gde_strncmp
                0x000000000040719f                gde_show_backbuffer
                0x00000000004071b5                gde_reboot
                0x00000000004071ce                gde_set_cursor
                0x00000000004071e6                gde_get_cursor
                0x00000000004071ec                gde_get_cursor_x
                0x0000000000407207                gde_get_cursor_y
                0x0000000000407222                gde_get_client_area_rect
                0x000000000040723a                gde_set_client_area_rect
                0x0000000000407259                gde_create_process
                0x0000000000407272                gde_create_thread
                0x000000000040728b                gde_start_thread
                0x00000000004072a7                gde_fopen
                0x00000000004072d3                gde_save_file
                0x0000000000407326                gde_down
                0x000000000040737b                gde_up
                0x00000000004073d0                gde_enter_critical_section
                0x000000000040740b                gde_exit_critical_section
                0x0000000000407424                gde_p
                0x000000000040742a                gde_v
                0x0000000000407430                gde_initialize_critical_section
                0x0000000000407449                gde_begin_paint
                0x0000000000407454                gde_end_paint
                0x000000000040745f                gde_put_char
                0x000000000040747b                gde_def_dialog
                0x0000000000407485                gde_get_system_metrics
                0x00000000004074a3                gde_dialog
                0x000000000040753c                gde_getchar
                0x0000000000407557                gde_display_bmp
                0x000000000040795e                gde_send_message_to_process
                0x00000000004079a1                gde_send_message_to_thread
                0x00000000004079e4                gde_send_message
                0x0000000000407a1a                gde_draw_text
                0x0000000000407a59                gde_get_ws_screen_window
                0x0000000000407a71                gde_get_ws_main_window
                0x0000000000407a89                gde_create_timer
                0x0000000000407aa9                gde_get_systime_info
                0x0000000000407aca                gde_show_window
                0x0000000000407ae9                gde_start_terminal
                0x0000000000407b5d                gde_update_statusbar
                0x0000000000407b7b                gde_get_pid
                0x0000000000407ba6                gde_get_screen_window
                0x0000000000407bc1                gde_get_background_window
                0x0000000000407bdc                gde_get_main_window
                0x0000000000407bf7                gde_getprocessname
                0x0000000000407c74                gde_getthreadname
                0x0000000000407cf1                gde_get_process_stats
                0x0000000000407d0f                gde_get_thread_stats
                0x0000000000407d2d                gde_debug_print
                0x0000000000407d4f                gde_clone_and_execute
                0x0000000000407d6c                gde_setup_net_buffer
 .text          0x0000000000407d93        0x0 ctype.o
 .text          0x0000000000407d93     0x2ab7 stdio.o
                0x0000000000407ddb                stdio_atoi
                0x0000000000407ea2                stdio_fntos
                0x0000000000407fcc                remove
                0x0000000000407fd6                fclose
                0x0000000000407ff7                fopen
                0x0000000000408018                creat
                0x000000000040803f                scroll
                0x000000000040810c                puts
                0x0000000000408127                fread
                0x0000000000408148                fwrite
                0x000000000040852a                printf3
                0x0000000000408547                printf_atoi
                0x0000000000408638                printf_i2hex
                0x000000000040869a                printf2
                0x000000000040881f                stdio_nextline
                0x000000000040885d                nlsprintf
                0x000000000040889b                sprintf
                0x00000000004088f0                putchar
                0x000000000040893b                libc_set_output_mode
                0x000000000040897f                outbyte
                0x0000000000408b73                _outbyte
                0x0000000000408ba2                input
                0x0000000000408d02                getchar
                0x0000000000408d30                stdioInitialize
                0x0000000000408ed2                fflush
                0x0000000000408ef3                fprintf
                0x0000000000408f81                fputs
                0x0000000000408fa2                nputs
                0x0000000000408fdd                gets
                0x000000000040906c                ungetc
                0x000000000040908d                ftell
                0x00000000004090ae                fileno
                0x00000000004090cf                fgetc
                0x00000000004090f0                feof
                0x0000000000409111                ferror
                0x0000000000409132                fseek
                0x0000000000409153                fputc
                0x00000000004091ee                stdioSetCursor
                0x0000000000409209                stdioGetCursorX
                0x0000000000409224                stdioGetCursorY
                0x000000000040923f                scanf
                0x00000000004093e0                sscanf
                0x000000000040959b                kvprintf
                0x000000000040a405                printf
                0x000000000040a433                printf_draw
                0x000000000040a47b                vfprintf
                0x000000000040a4f3                vprintf
                0x000000000040a512                stdout_printf
                0x000000000040a53e                stderr_printf
                0x000000000040a56a                perror
                0x000000000040a581                rewind
                0x000000000040a5ab                snprintf
                0x000000000040a5bf                stdio_initialize_standard_streams
                0x000000000040a5ea                libcStartTerminal
                0x000000000040a65e                setbuf
                0x000000000040a680                setbuffer
                0x000000000040a6a2                setlinebuf
                0x000000000040a6c4                setvbuf
                0x000000000040a6e5                filesize
                0x000000000040a72e                fileread
                0x000000000040a77c                dprintf
                0x000000000040a786                vdprintf
                0x000000000040a790                vsprintf
                0x000000000040a79a                vsnprintf
                0x000000000040a7a4                vscanf
                0x000000000040a7ae                vsscanf
                0x000000000040a7b8                vfscanf
                0x000000000040a7c2                tmpnam
                0x000000000040a7cc                tmpnam_r
                0x000000000040a7d6                tempnam
                0x000000000040a7e0                tmpfile
                0x000000000040a7ea                fdopen
                0x000000000040a7f4                freopen
                0x000000000040a7fe                open_memstream
                0x000000000040a808                open_wmemstream
                0x000000000040a812                fmemopen
                0x000000000040a81c                fgetpos
                0x000000000040a826                fsetpos
                0x000000000040a830                fpurge
                0x000000000040a83a                __fpurge
                0x000000000040a840                ctermid
 .text          0x000000000040a84a     0x114a stdlib.o
                0x000000000040a867                rtGetHeapStart
                0x000000000040a871                rtGetHeapEnd
                0x000000000040a87b                rtGetHeapPointer
                0x000000000040a885                rtGetAvailableHeap
                0x000000000040a88f                heapSetLibcHeap
                0x000000000040a942                heapAllocateMemory
                0x000000000040ab74                FreeHeap
                0x000000000040ab7e                heapInit
                0x000000000040ad11                stdlibInitMM
                0x000000000040ad74                libcInitRT
                0x000000000040ad96                mktemp
                0x000000000040ada0                rand
                0x000000000040adbd                srand
                0x000000000040adcb                xmalloc
                0x000000000040adfd                stdlib_die
                0x000000000040ae33                malloc
                0x000000000040ae6f                realloc
                0x000000000040aeac                free
                0x000000000040aeb2                calloc
                0x000000000040aef8                zmalloc
                0x000000000040af34                system
                0x000000000040b2f8                stdlib_strncmp
                0x000000000040b35b                __findenv
                0x000000000040b426                getenv
                0x000000000040b453                setenv
                0x000000000040b45d                unsetenv
                0x000000000040b467                atoi
                0x000000000040b52e                reverse
                0x000000000040b596                itoa
                0x000000000040b644                abs
                0x000000000040b654                strtod
                0x000000000040b885                strtof
                0x000000000040b8a1                strtold
                0x000000000040b8b4                atof
                0x000000000040b8c6                labs
                0x000000000040b8d6                mkstemp
                0x000000000040b8e0                mkostemp
                0x000000000040b8ea                mkstemps
                0x000000000040b8f4                mkostemps
                0x000000000040b8fe                ptsname
                0x000000000040b924                ptsname_r
                0x000000000040b94b                posix_openpt
                0x000000000040b966                grantpt
                0x000000000040b970                getpt
                0x000000000040b97a                unlockpt
                0x000000000040b984                getprogname
                0x000000000040b98e                setprogname
 .text          0x000000000040b994      0xb2b string.o
                0x000000000040b994                strcoll
                0x000000000040b9ad                memsetw
                0x000000000040b9d9                memcmp
                0x000000000040ba3e                strdup
                0x000000000040ba90                strndup
                0x000000000040baf1                strnchr
                0x000000000040bb2a                strrchr
                0x000000000040bb65                strtoimax
                0x000000000040bb6f                strtoumax
                0x000000000040bb79                strcasecmp
                0x000000000040bbe1                strncpy
                0x000000000040bc37                strcmp
                0x000000000040bc9c                strncmp
                0x000000000040bcff                memset
                0x000000000040bd46                memoryZeroMemory
                0x000000000040bd6d                memcpy
                0x000000000040bdaa                strcpy
                0x000000000040bdde                strlcpy
                0x000000000040be3d                strcat
                0x000000000040be6c                strchrnul
                0x000000000040be91                strlcat
                0x000000000040bf21                strncat
                0x000000000040bf83                bcopy
                0x000000000040bfb0                bzero
                0x000000000040bfd1                strlen
                0x000000000040bfff                strnlen
                0x000000000040c03a                strpbrk
                0x000000000040c088                strsep
                0x000000000040c106                strreplace
                0x000000000040c141                strcspn
                0x000000000040c1e0                strspn
                0x000000000040c27f                strtok_r
                0x000000000040c366                strtok
                0x000000000040c37e                strchr
                0x000000000040c3aa                memmove
                0x000000000040c42b                memscan
                0x000000000040c45f                strstr
 .text          0x000000000040c4bf       0x89 conio.o
                0x000000000040c4bf                putch
                0x000000000040c4e3                cputs
                0x000000000040c518                getch
                0x000000000040c530                getche
 .text          0x000000000040c548      0x18a builtins.o
                0x000000000040c548                cd_buitins
                0x000000000040c561                cls_builtins
                0x000000000040c56f                copy_builtins
                0x000000000040c575                date_builtins
                0x000000000040c57b                del_builtins
                0x000000000040c581                dir_builtins
                0x000000000040c5bd                echo_builtins
                0x000000000040c5d9                exec_builtins
                0x000000000040c5f2                exit_builtins
                0x000000000040c618                getpid_builtins
                0x000000000040c62a                getppid_builtins
                0x000000000040c63c                getuid_builtins
                0x000000000040c64e                getgid_builtins
                0x000000000040c660                help_builtins
                0x000000000040c6b6                pwd_builtins
 .text          0x000000000040c6d2       0x49 desktop.o
                0x000000000040c6d2                desktopInitialize
 .text          0x000000000040c71b      0x5a9 unistd.o
                0x000000000040c71b                execv
                0x000000000040c739                execve
                0x000000000040c798                write
                0x000000000040c7e0                exit
                0x000000000040c800                fast_fork
                0x000000000040c828                fork
                0x000000000040c85e                sys_fork
                0x000000000040c894                setuid
                0x000000000040c8af                getuid
                0x000000000040c8ca                geteuid
                0x000000000040c8d4                getpid
                0x000000000040c8ec                getppid
                0x000000000040c904                getgid
                0x000000000040c91f                dup
                0x000000000040c939                dup2
                0x000000000040c955                dup3
                0x000000000040c973                fcntl
                0x000000000040c97d                getpriority
                0x000000000040c987                setpriority
                0x000000000040c991                nice
                0x000000000040c99b                pause
                0x000000000040c9a5                mkdir
                0x000000000040c9b9                rmdir
                0x000000000040c9c3                link
                0x000000000040c9cd                unlink
                0x000000000040c9d7                mlock
                0x000000000040c9e1                munlock
                0x000000000040c9eb                mlockall
                0x000000000040c9f5                munlockall
                0x000000000040c9ff                sysconf
                0x000000000040ca09                fsync
                0x000000000040ca13                fdatasync
                0x000000000040ca1d                open
                0x000000000040ca43                close
                0x000000000040ca61                pipe
                0x000000000040ca82                fpathconf
                0x000000000040ca8c                pathconf
                0x000000000040ca96                __gethostname
                0x000000000040cac2                gethostname
                0x000000000040cae9                sethostname
                0x000000000040cb0a                getlogin
                0x000000000040cb36                setlogin
                0x000000000040cb5c                getusername
                0x000000000040cbd9                setusername
                0x000000000040cc50                ttyname
                0x000000000040cc8d                ttyname_r
                0x000000000040cc97                isatty
                0x000000000040ccba                getopt
 .text          0x000000000040ccc4      0x165 termios.o
                0x000000000040ccc4                tcgetattr
                0x000000000040cce2                tcsetattr
                0x000000000040cd5b                tcsendbreak
                0x000000000040cd65                tcdrain
                0x000000000040cd6f                tcflush
                0x000000000040cd79                tcflow
                0x000000000040cd83                cfmakeraw
                0x000000000040cdf5                cfgetispeed
                0x000000000040ce00                cfgetospeed
                0x000000000040ce0b                cfsetispeed
                0x000000000040ce15                cfsetospeed
                0x000000000040ce1f                cfsetspeed
 .text          0x000000000040ce29       0x3d ioctl.o
                0x000000000040ce29                ioctl
 .text          0x000000000040ce66       0x28 stubs.o
                0x000000000040ce66                gramado_system_call
                0x000000000040d000                . = ALIGN (0x1000)
 *fill*         0x000000000040ce8e      0x172 

.iplt           0x000000000040d000        0x0
 .iplt          0x000000000040d000        0x0 crt0.o

.rodata         0x000000000040d000     0x3799
 .rodata        0x000000000040d000       0x5a crt0.o
 *fill*         0x000000000040d05a        0x6 
 .rodata        0x000000000040d060     0x1807 main.o
 *fill*         0x000000000040e867       0x19 
 .rodata        0x000000000040e880      0x6cf shellui.o
 *fill*         0x000000000040ef4f        0x1 
 .rodata        0x000000000040ef50      0x505 api.o
 *fill*         0x000000000040f455        0xb 
 .rodata        0x000000000040f460      0x100 ctype.o
                0x000000000040f460                _ctype
 .rodata        0x000000000040f560      0x329 stdio.o
                0x000000000040f6c0                hex2ascii_data
 *fill*         0x000000000040f889        0x7 
 .rodata        0x000000000040f890      0x520 stdlib.o
 .rodata        0x000000000040fdb0        0x6 conio.o
 *fill*         0x000000000040fdb6        0xa 
 .rodata        0x000000000040fdc0      0x4bc builtins.o
 *fill*         0x000000000041027c        0x4 
 .rodata        0x0000000000410280      0x48f desktop.o
 *fill*         0x000000000041070f        0x1 
 .rodata        0x0000000000410710       0x89 unistd.o

.eh_frame       0x000000000041079c     0x3bfc
 .eh_frame      0x000000000041079c       0x34 crt0.o
 .eh_frame      0x00000000004107d0      0xca4 main.o
                                        0xcbc (size before relaxing)
 .eh_frame      0x0000000000411474      0x140 shellui.o
                                        0x158 (size before relaxing)
 .eh_frame      0x00000000004115b4      0xd4c api.o
                                        0xd64 (size before relaxing)
 .eh_frame      0x0000000000412300      0xb74 stdio.o
                                        0xb8c (size before relaxing)
 .eh_frame      0x0000000000412e74      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x0000000000413474      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x0000000000413934       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x00000000004139d4      0x1e0 builtins.o
                                        0x1f8 (size before relaxing)
 .eh_frame      0x0000000000413bb4       0x20 desktop.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000413bd4      0x600 unistd.o
                                        0x618 (size before relaxing)
 .eh_frame      0x00000000004141d4      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x0000000000414354       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000414374       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x0000000000414398        0x0
 .rel.got       0x0000000000414398        0x0 crt0.o
 .rel.iplt      0x0000000000414398        0x0 crt0.o
 .rel.text      0x0000000000414398        0x0 crt0.o

.data           0x00000000004143a0     0x1c60
                0x00000000004143a0                data = .
                0x00000000004143a0                _data = .
                0x00000000004143a0                __data = .
 *(.data)
 .data          0x00000000004143a0       0x14 crt0.o
 *fill*         0x00000000004143b4        0xc 
 .data          0x00000000004143c0      0x55c main.o
                0x0000000000414860                _running
                0x0000000000414864                the_current_maintainer
                0x0000000000414868                primary_prompt
                0x000000000041486c                secondary_prompt
                0x0000000000414870                current_user_name
                0x0000000000414874                current_host_name
                0x0000000000414878                remember_on_history
                0x000000000041487c                current_command_number
                0x0000000000414880                bashrc_file
                0x0000000000414884                shell_config_file
                0x00000000004148a0                long_args
                0x0000000000414918                deltaValue
 *fill*         0x000000000041491c        0x4 
 .data          0x0000000000414920      0x4a0 shellui.o
 .data          0x0000000000414dc0      0x440 api.o
 .data          0x0000000000415200        0x0 ctype.o
 .data          0x0000000000415200        0x0 stdio.o
 .data          0x0000000000415200        0x8 stdlib.o
                0x0000000000415200                _infinity
 .data          0x0000000000415208        0x0 string.o
 .data          0x0000000000415208        0x0 conio.o
 *fill*         0x0000000000415208       0x18 
 .data          0x0000000000415220      0x4a0 builtins.o
 .data          0x00000000004156c0      0x4a8 desktop.o
                0x0000000000415b60                primary_desktop_folder
                0x0000000000415b64                secondary_desktop_folder
 .data          0x0000000000415b68        0x0 unistd.o
 .data          0x0000000000415b68        0x0 termios.o
 .data          0x0000000000415b68        0x0 ioctl.o
 .data          0x0000000000415b68        0x0 stubs.o
                0x0000000000416000                . = ALIGN (0x1000)
 *fill*         0x0000000000415b68      0x498 

.got            0x0000000000416000        0x0
 .got           0x0000000000416000        0x0 crt0.o

.got.plt        0x0000000000416000        0x0
 .got.plt       0x0000000000416000        0x0 crt0.o

.igot.plt       0x0000000000416000        0x0
 .igot.plt      0x0000000000416000        0x0 crt0.o

.bss            0x0000000000416000    0x16e64
                0x0000000000416000                bss = .
                0x0000000000416000                _bss = .
                0x0000000000416000                __bss = .
 *(.bss)
 .bss           0x0000000000416000        0x0 crt0.o
 .bss           0x0000000000416000       0x5c main.o
                0x0000000000416000                ShellFlag
                0x0000000000416004                executing
                0x0000000000416008                login_status
                0x000000000041600c                shell_initialized
                0x0000000000416010                global_command
                0x0000000000416014                interrupt_state
                0x0000000000416018                login_shell
                0x000000000041601c                interactive
                0x0000000000416020                restricted
                0x0000000000416024                debugging_login_shell
                0x0000000000416028                indirection_level
                0x000000000041602c                shell_level
                0x0000000000416030                act_like_sh
                0x0000000000416034                debugging
                0x0000000000416038                no_rc
                0x000000000041603c                no_profile
                0x0000000000416040                do_version
                0x0000000000416044                quiet
                0x0000000000416048                make_login_shell
                0x000000000041604c                no_line_editing
                0x0000000000416050                no_brace_expansion
 .bss           0x000000000041605c        0x8 shellui.o
 *fill*         0x0000000000416064       0x1c 
 .bss           0x0000000000416080     0x8004 api.o
 .bss           0x000000000041e084        0x0 ctype.o
 .bss           0x000000000041e084        0x9 stdio.o
 *fill*         0x000000000041e08d       0x13 
 .bss           0x000000000041e0a0     0x8020 stdlib.o
                0x000000000041e0a0                environ
 .bss           0x00000000004260c0        0x4 string.o
 .bss           0x00000000004260c4        0x0 conio.o
 .bss           0x00000000004260c4        0x8 builtins.o
 .bss           0x00000000004260cc        0x8 desktop.o
 *fill*         0x00000000004260d4        0xc 
 .bss           0x00000000004260e0      0x19f unistd.o
                0x00000000004260e0                __execv_environ
 .bss           0x000000000042627f        0x0 termios.o
 .bss           0x000000000042627f        0x0 ioctl.o
 .bss           0x000000000042627f        0x0 stubs.o
                0x0000000000427000                . = ALIGN (0x1000)
 *fill*         0x000000000042627f      0xd81 
 COMMON         0x0000000000427000      0xd08 crt0.o
                0x0000000000427000                g_cursor_x
                0x0000000000427004                stdout
                0x0000000000427008                g_char_attrib
                0x000000000042700c                g_rows
                0x0000000000427020                Streams
                0x00000000004270a0                g_using_gui
                0x00000000004270c0                prompt_out
                0x00000000004274c0                g_columns
                0x00000000004274c4                prompt_pos
                0x00000000004274c8                stdin
                0x00000000004274cc                prompt_status
                0x00000000004274e0                prompt_err
                0x00000000004278e0                stderr
                0x0000000000427900                prompt
                0x0000000000427d00                g_cursor_y
                0x0000000000427d04                prompt_max
 *fill*         0x0000000000427d08       0x18 
 COMMON         0x0000000000427d20     0x47c0 main.o
                0x0000000000427d20                password
                0x0000000000427d2c                objectY
                0x0000000000427d30                CurrentWindow
                0x0000000000427d34                backgroung_color
                0x0000000000427d38                wsWindowHeight
                0x0000000000427d3c                menu_button
                0x0000000000427d40                screen_buffer_y
                0x0000000000427d44                wlFullScreenLeft
                0x0000000000427d48                username
                0x0000000000427d54                close_button
                0x0000000000427d58                smCursorHeight
                0x0000000000427d60                pathname_buffer
                0x0000000000427da0                deltaY
                0x0000000000427da4                textCurrentRow
                0x0000000000427da8                app4_button
                0x0000000000427dac                shellStatus
                0x0000000000427db0                smMousePointerWidth
                0x0000000000427db4                smMousePointerHeight
                0x0000000000427db8                filename_buffer
                0x0000000000427dc4                textWheelDelta
                0x0000000000427dc8                app1_button
                0x0000000000427dcc                wlMinRows
                0x0000000000427dd0                current_volume_string
                0x0000000000427dd4                ShellMetrics
                0x0000000000427dd8                smCharHeight
                0x0000000000427ddc                ApplicationInfo
                0x0000000000427de0                foregroung_color
                0x0000000000427de4                shell_info
                0x0000000000427dfc                BufferInfo
                0x0000000000427e00                ShellHook
                0x0000000000427e20                lineList
                0x0000000000429e20                wlMaxWindowHeight
                0x0000000000429e24                wlMaxRows
                0x0000000000429e28                textCurrentCol
                0x0000000000429e2c                shell_environment
                0x0000000000429e30                textSavedCol
                0x0000000000429e34                current_volume_id
                0x0000000000429e38                smCharWidth
                0x0000000000429e3c                g_current_workingdirectory_id
                0x0000000000429e40                wlFullScreenHeight
                0x0000000000429e44                textTopRow
                0x0000000000429e48                textMinWheelDelta
                0x0000000000429e4c                pathname_lenght
                0x0000000000429e50                wlMinWindowHeight
                0x0000000000429e54                textBottomRow
                0x0000000000429e58                wlMinColumns
                0x0000000000429e5c                objectX
                0x0000000000429e60                pwd_initialized
                0x0000000000429e64                root
                0x0000000000429e68                CurrentCommand
                0x0000000000429e6c                shell_name
                0x0000000000429e70                screen_buffer_x
                0x0000000000429e74                wlMinWindowWidth
                0x0000000000429e78                CommandHistory
                0x0000000000429e7c                app3_button
                0x0000000000429e80                pwd
                0x0000000000429ea0                screen_buffer
                0x000000000042ae44                reboot_button
                0x000000000042ae48                dummycompiler
                0x000000000042ae4c                smScreenWidth
                0x000000000042ae50                textMaxWheelDelta
                0x000000000042ae54                CursorInfo
                0x000000000042ae58                app2_button
                0x000000000042ae5c                smScreenHeight
                0x000000000042ae60                wlMaxWindowWidth
                0x000000000042ae64                screen_buffer_pos
                0x000000000042ae68                build_version
                0x000000000042ae6c                smCursorWidth
                0x000000000042ae70                wpWindowLeft
                0x000000000042ae74                terminal_rect
                0x000000000042ae84                wlFullScreenTop
                0x000000000042ae88                wsWindowWidth
                0x000000000042ae8c                g_current_disk_id
                0x000000000042ae90                editboxWindow
                0x000000000042ae94                hWindow
                0x000000000042ae98                deltaX
                0x000000000042ae9c                taskbarWindow
                0x000000000042aea0                EOF_Reached
                0x000000000042aec0                screenbufferList
                0x000000000042aee0                ClientAreaInfo
                0x000000000042aee4                pathname_initilized
                0x000000000042aee8                wpWindowTop
                0x000000000042aeec                filename_lenght
                0x000000000042aef0                current_semaphore
                0x000000000042aef4                wlFullScreenWidth
                0x000000000042aef8                shellError
                0x000000000042aefc                dist_version
                0x000000000042af00                wlMaxColumns
                0x000000000042af04                textSavedRow
                0x000000000042af08                filename_initilized
                0x000000000042af20                LINES
                0x000000000042c4a0                g_current_volume_id
                0x000000000042c4c0                current_workingdiretory_string
 COMMON         0x000000000042c4e0      0x440 api.o
                0x000000000042c4e0                heapList
                0x000000000042c8e0                libcHeap
                0x000000000042c8e4                dialogbox_button2
                0x000000000042c8e8                messagebox_button1
                0x000000000042c8ec                heap_start
                0x000000000042c8f0                g_available_heap
                0x000000000042c8f4                g_heap_pointer
                0x000000000042c8f8                HEAP_SIZE
                0x000000000042c8fc                dialogbox_button1
                0x000000000042c900                first_responder
                0x000000000042c904                heap_end
                0x000000000042c908                __mb_current_button
                0x000000000042c90c                HEAP_END
                0x000000000042c910                messagebox_button2
                0x000000000042c914                Heap
                0x000000000042c918                heapCount
                0x000000000042c91c                HEAP_START
 COMMON         0x000000000042c920        0x0 stdio.o
 COMMON         0x000000000042c920      0x484 stdlib.o
                0x000000000042c920                mm_prev_pointer
                0x000000000042c940                mmblockList
                0x000000000042cd40                last_valid
                0x000000000042cd44                randseed
                0x000000000042cd48                mmblockCount
                0x000000000042cd4c                last_size
                0x000000000042cd60                __ptsname_buffer
                0x000000000042cda0                current_mmblock
 *fill*         0x000000000042cda4       0x1c 
 COMMON         0x000000000042cdc0       0xa4 unistd.o
                0x000000000042cdc0                errno
                0x000000000042cdc4                optarg
                0x000000000042cdc8                opterr
                0x000000000042cdcc                my__p
                0x000000000042cdd0                optind
                0x000000000042cde0                __Hostname_buffer
                0x000000000042ce20                __Login_buffer
                0x000000000042ce60                optopt
                0x000000000042ce64                end = .
                0x000000000042ce64                _end = .
                0x000000000042ce64                __end = .
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
LOAD termios.o
LOAD ioctl.o
LOAD stubs.o
OUTPUT(ZSHELL.BIN elf32-i386)

.comment        0x0000000000000000       0x11
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 shellui.o
 .comment       0x0000000000000011       0x12 api.o
 .comment       0x0000000000000011       0x12 ctype.o
 .comment       0x0000000000000011       0x12 stdio.o
 .comment       0x0000000000000011       0x12 stdlib.o
 .comment       0x0000000000000011       0x12 string.o
 .comment       0x0000000000000011       0x12 conio.o
 .comment       0x0000000000000011       0x12 builtins.o
 .comment       0x0000000000000011       0x12 desktop.o
 .comment       0x0000000000000011       0x12 unistd.o
 .comment       0x0000000000000011       0x12 termios.o
 .comment       0x0000000000000011       0x12 ioctl.o
 .comment       0x0000000000000011       0x12 stubs.o

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
                0x0000000000000000        0x0 termios.o
 .note.GNU-stack
                0x0000000000000000        0x0 ioctl.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
