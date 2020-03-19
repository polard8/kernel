
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
taskmanagerBuffer   0x200             main.o
CurrentWindow       0x4               main.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
last_valid          0x4               stdlib.o
heapList            0x400             api.o
libcHeap            0x4               api.o
errno               0x4               unistd.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
Streams             0x80              crt0.o
optarg              0x4               unistd.o
messagebox_button1  0x4               api.o
g_using_gui         0x4               crt0.o
opterr              0x4               unistd.o
ApplicationInfo     0x4               main.o
randseed            0x4               stdlib.o
heap_start          0x4               api.o
prompt_out          0x400             crt0.o
BufferInfo          0x4               main.o
g_available_heap    0x4               api.o
g_heap_pointer      0x4               api.o
taskmanagerStatus   0x4               main.o
g_columns           0x4               crt0.o
my__p               0x4               unistd.o
HEAP_SIZE           0x4               api.o
optind              0x4               unistd.o
mmblockCount        0x4               stdlib.o
dialogbox_button1   0x4               api.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
__Hostname_buffer   0x40              unistd.o
prompt_status       0x4               crt0.o
first_responder     0x4               api.o
__ptsname_buffer    0x40              stdlib.o
__Login_buffer      0x40              unistd.o
prompt_err          0x400             crt0.o
CursorInfo          0x4               main.o
heap_end            0x4               api.o
stderr              0x4               crt0.o
__mb_current_button
                    0x4               api.o
optopt              0x4               unistd.o
prompt              0x400             crt0.o
HEAP_END            0x4               api.o
rect                0x4               main.o
g_cursor_y          0x4               crt0.o
taskmanagerBufferPos
                    0x4               main.o
ClientAreaInfo      0x4               main.o
messagebox_button2  0x4               api.o
Heap                0x4               api.o
current_semaphore   0x4               main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
taskmanTest1        0x4               main.o
heapCount           0x4               api.o
HEAP_START          0x4               api.o
taskmanagerError    0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000401000     0x8000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000      0x108 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401108      0x486 main.o
                0x0000000000401108                __debug_print
                0x000000000040113a                tmSleep
                0x0000000000401157                tmProbeProcessList
                0x0000000000401175                tmCreateTaskBar
                0x00000000004011e0                tmProc
                0x000000000040126c                tmUpdateStatus
                0x00000000004012a9                tmDrawBar
                0x00000000004012fe                tmSetCursor
                0x0000000000401314                tmstrlen
                0x0000000000401342                DoProgress
                0x00000000004013e9                DoSome
                0x0000000000401441                progress_bar_test
                0x000000000040144f                tmInit
                0x0000000000401477                main
 .text          0x000000000040158e     0x2164 api.o
                0x000000000040158e                system_call
                0x00000000004015b6                gde_system
                0x00000000004019be                system1
                0x00000000004019df                system2
                0x0000000000401a00                system3
                0x0000000000401a21                system4
                0x0000000000401a42                system5
                0x0000000000401a63                system6
                0x0000000000401a84                system7
                0x0000000000401aa5                system8
                0x0000000000401ac6                system9
                0x0000000000401ae7                system10
                0x0000000000401b08                system11
                0x0000000000401b29                system12
                0x0000000000401b4a                system13
                0x0000000000401b6b                system14
                0x0000000000401b8c                system15
                0x0000000000401bad                gde_refresh_buffer
                0x0000000000401c85                gde_print_string
                0x0000000000401c8b                gde_vsync
                0x0000000000401ca3                gws_vsync
                0x0000000000401cb0                gde_system_procedure
                0x0000000000401cf3                __gde_set_cursor
                0x0000000000401d0d                __gde_put_char
                0x0000000000401d13                gde_load_bitmap_16x16
                0x0000000000401d2c                gde_shutdown
                0x0000000000401d46                gde_init_background
                0x0000000000401d4c                gde_message_box
                0x0000000000402051                mbProcedure
                0x000000000040220d                gde_dialog_box
                0x00000000004025c8                dbProcedure
                0x000000000040263e                call_kernel
                0x0000000000402766                call_gui
                0x00000000004027fb                gde_create_window
                0x0000000000402874                gde_register_window
                0x000000000040289c                gde_close_window
                0x00000000004028c4                gde_set_focus
                0x00000000004028ec                gde_get_focus
                0x0000000000402901                gde_kill_focus
                0x0000000000402929                gde_set_active_window
                0x0000000000402951                gde_get_active_window
                0x0000000000402966                gde_show_current_process_info
                0x000000000040297c                gde_resize_window
                0x0000000000402999                gde_redraw_window
                0x00000000004029b6                gde_replace_window
                0x00000000004029d0                gde_maximize_window
                0x00000000004029ef                gde_minimize_window
                0x0000000000402a0e                gde_update_window
                0x0000000000402a30                gde_get_foregroung_window
                0x0000000000402a46                gde_set_foregroung_window
                0x0000000000402a62                gde_exit
                0x0000000000402a7f                gde_kill
                0x0000000000402a85                gde_dead_thread_collector
                0x0000000000402a9b                gde_strncmp
                0x0000000000402afe                gde_show_backbuffer
                0x0000000000402b14                gde_reboot
                0x0000000000402b2d                gde_set_cursor
                0x0000000000402b45                gde_get_cursor
                0x0000000000402b4b                gde_get_cursor_x
                0x0000000000402b66                gde_get_cursor_y
                0x0000000000402b81                gde_get_client_area_rect
                0x0000000000402b99                gde_set_client_area_rect
                0x0000000000402bb8                gde_create_process
                0x0000000000402bd1                gde_create_thread
                0x0000000000402bea                gde_start_thread
                0x0000000000402c06                gde_fopen
                0x0000000000402c32                gde_save_file
                0x0000000000402c85                gde_down
                0x0000000000402cda                gde_up
                0x0000000000402d2f                gde_enter_critical_section
                0x0000000000402d6a                gde_exit_critical_section
                0x0000000000402d83                gde_p
                0x0000000000402d89                gde_v
                0x0000000000402d8f                gde_initialize_critical_section
                0x0000000000402da8                gde_begin_paint
                0x0000000000402db3                gde_end_paint
                0x0000000000402dbe                gde_put_char
                0x0000000000402dda                gde_def_dialog
                0x0000000000402de4                gde_get_system_metrics
                0x0000000000402e02                gde_dialog
                0x0000000000402e9b                gde_getchar
                0x0000000000402eb6                gde_display_bmp
                0x00000000004032bd                gde_send_message_to_process
                0x0000000000403300                gde_send_message_to_thread
                0x0000000000403343                gde_send_message
                0x0000000000403379                gde_draw_text
                0x00000000004033b8                gde_get_ws_screen_window
                0x00000000004033d0                gde_get_ws_main_window
                0x00000000004033e8                gde_create_timer
                0x0000000000403408                gde_get_systime_info
                0x0000000000403429                gde_show_window
                0x0000000000403448                gde_start_terminal
                0x00000000004034bc                gde_update_statusbar
                0x00000000004034da                gde_get_pid
                0x0000000000403505                gde_get_screen_window
                0x0000000000403520                gde_get_background_window
                0x000000000040353b                gde_get_main_window
                0x0000000000403556                gde_getprocessname
                0x00000000004035d3                gde_getthreadname
                0x0000000000403650                gde_get_process_stats
                0x000000000040366e                gde_get_thread_stats
                0x000000000040368c                gde_debug_print
                0x00000000004036ae                gde_clone_and_execute
                0x00000000004036cb                gde_setup_net_buffer
 .text          0x00000000004036f2        0x0 ctype.o
 .text          0x00000000004036f2     0x2ab7 stdio.o
                0x000000000040373a                stdio_atoi
                0x0000000000403801                stdio_fntos
                0x000000000040392b                remove
                0x0000000000403935                fclose
                0x0000000000403956                fopen
                0x0000000000403977                creat
                0x000000000040399e                scroll
                0x0000000000403a6b                puts
                0x0000000000403a86                fread
                0x0000000000403aa7                fwrite
                0x0000000000403e89                printf3
                0x0000000000403ea6                printf_atoi
                0x0000000000403f97                printf_i2hex
                0x0000000000403ff9                printf2
                0x000000000040417e                stdio_nextline
                0x00000000004041bc                nlsprintf
                0x00000000004041fa                sprintf
                0x000000000040424f                putchar
                0x000000000040429a                libc_set_output_mode
                0x00000000004042de                outbyte
                0x00000000004044d2                _outbyte
                0x0000000000404501                input
                0x0000000000404661                getchar
                0x000000000040468f                stdioInitialize
                0x0000000000404831                fflush
                0x0000000000404852                fprintf
                0x00000000004048e0                fputs
                0x0000000000404901                nputs
                0x000000000040493c                gets
                0x00000000004049cb                ungetc
                0x00000000004049ec                ftell
                0x0000000000404a0d                fileno
                0x0000000000404a2e                fgetc
                0x0000000000404a4f                feof
                0x0000000000404a70                ferror
                0x0000000000404a91                fseek
                0x0000000000404ab2                fputc
                0x0000000000404b4d                stdioSetCursor
                0x0000000000404b68                stdioGetCursorX
                0x0000000000404b83                stdioGetCursorY
                0x0000000000404b9e                scanf
                0x0000000000404d3f                sscanf
                0x0000000000404efa                kvprintf
                0x0000000000405d64                printf
                0x0000000000405d92                printf_draw
                0x0000000000405dda                vfprintf
                0x0000000000405e52                vprintf
                0x0000000000405e71                stdout_printf
                0x0000000000405e9d                stderr_printf
                0x0000000000405ec9                perror
                0x0000000000405ee0                rewind
                0x0000000000405f0a                snprintf
                0x0000000000405f1e                stdio_initialize_standard_streams
                0x0000000000405f49                libcStartTerminal
                0x0000000000405fbd                setbuf
                0x0000000000405fdf                setbuffer
                0x0000000000406001                setlinebuf
                0x0000000000406023                setvbuf
                0x0000000000406044                filesize
                0x000000000040608d                fileread
                0x00000000004060db                dprintf
                0x00000000004060e5                vdprintf
                0x00000000004060ef                vsprintf
                0x00000000004060f9                vsnprintf
                0x0000000000406103                vscanf
                0x000000000040610d                vsscanf
                0x0000000000406117                vfscanf
                0x0000000000406121                tmpnam
                0x000000000040612b                tmpnam_r
                0x0000000000406135                tempnam
                0x000000000040613f                tmpfile
                0x0000000000406149                fdopen
                0x0000000000406153                freopen
                0x000000000040615d                open_memstream
                0x0000000000406167                open_wmemstream
                0x0000000000406171                fmemopen
                0x000000000040617b                fgetpos
                0x0000000000406185                fsetpos
                0x000000000040618f                fpurge
                0x0000000000406199                __fpurge
                0x000000000040619f                ctermid
 .text          0x00000000004061a9     0x114a stdlib.o
                0x00000000004061c6                rtGetHeapStart
                0x00000000004061d0                rtGetHeapEnd
                0x00000000004061da                rtGetHeapPointer
                0x00000000004061e4                rtGetAvailableHeap
                0x00000000004061ee                heapSetLibcHeap
                0x00000000004062a1                heapAllocateMemory
                0x00000000004064d3                FreeHeap
                0x00000000004064dd                heapInit
                0x0000000000406670                stdlibInitMM
                0x00000000004066d3                libcInitRT
                0x00000000004066f5                mktemp
                0x00000000004066ff                rand
                0x000000000040671c                srand
                0x000000000040672a                xmalloc
                0x000000000040675c                stdlib_die
                0x0000000000406792                malloc
                0x00000000004067ce                realloc
                0x000000000040680b                free
                0x0000000000406811                calloc
                0x0000000000406857                zmalloc
                0x0000000000406893                system
                0x0000000000406c57                stdlib_strncmp
                0x0000000000406cba                __findenv
                0x0000000000406d85                getenv
                0x0000000000406db2                setenv
                0x0000000000406dbc                unsetenv
                0x0000000000406dc6                atoi
                0x0000000000406e8d                reverse
                0x0000000000406ef5                itoa
                0x0000000000406fa3                abs
                0x0000000000406fb3                strtod
                0x00000000004071e4                strtof
                0x0000000000407200                strtold
                0x0000000000407213                atof
                0x0000000000407225                labs
                0x0000000000407235                mkstemp
                0x000000000040723f                mkostemp
                0x0000000000407249                mkstemps
                0x0000000000407253                mkostemps
                0x000000000040725d                ptsname
                0x0000000000407283                ptsname_r
                0x00000000004072aa                posix_openpt
                0x00000000004072c5                grantpt
                0x00000000004072cf                getpt
                0x00000000004072d9                unlockpt
                0x00000000004072e3                getprogname
                0x00000000004072ed                setprogname
 .text          0x00000000004072f3      0xb2b string.o
                0x00000000004072f3                strcoll
                0x000000000040730c                memsetw
                0x0000000000407338                memcmp
                0x000000000040739d                strdup
                0x00000000004073ef                strndup
                0x0000000000407450                strnchr
                0x0000000000407489                strrchr
                0x00000000004074c4                strtoimax
                0x00000000004074ce                strtoumax
                0x00000000004074d8                strcasecmp
                0x0000000000407540                strncpy
                0x0000000000407596                strcmp
                0x00000000004075fb                strncmp
                0x000000000040765e                memset
                0x00000000004076a5                memoryZeroMemory
                0x00000000004076cc                memcpy
                0x0000000000407709                strcpy
                0x000000000040773d                strlcpy
                0x000000000040779c                strcat
                0x00000000004077cb                strchrnul
                0x00000000004077f0                strlcat
                0x0000000000407880                strncat
                0x00000000004078e2                bcopy
                0x000000000040790f                bzero
                0x0000000000407930                strlen
                0x000000000040795e                strnlen
                0x0000000000407999                strpbrk
                0x00000000004079e7                strsep
                0x0000000000407a65                strreplace
                0x0000000000407aa0                strcspn
                0x0000000000407b3f                strspn
                0x0000000000407bde                strtok_r
                0x0000000000407cc5                strtok
                0x0000000000407cdd                strchr
                0x0000000000407d09                memmove
                0x0000000000407d8a                memscan
                0x0000000000407dbe                strstr
 .text          0x0000000000407e1e       0x89 conio.o
                0x0000000000407e1e                putch
                0x0000000000407e42                cputs
                0x0000000000407e77                getch
                0x0000000000407e8f                getche
 .text          0x0000000000407ea7      0x5a9 unistd.o
                0x0000000000407ea7                execv
                0x0000000000407ec5                execve
                0x0000000000407f24                write
                0x0000000000407f6c                exit
                0x0000000000407f8c                fast_fork
                0x0000000000407fb4                fork
                0x0000000000407fea                sys_fork
                0x0000000000408020                setuid
                0x000000000040803b                getuid
                0x0000000000408056                geteuid
                0x0000000000408060                getpid
                0x0000000000408078                getppid
                0x0000000000408090                getgid
                0x00000000004080ab                dup
                0x00000000004080c5                dup2
                0x00000000004080e1                dup3
                0x00000000004080ff                fcntl
                0x0000000000408109                getpriority
                0x0000000000408113                setpriority
                0x000000000040811d                nice
                0x0000000000408127                pause
                0x0000000000408131                mkdir
                0x0000000000408145                rmdir
                0x000000000040814f                link
                0x0000000000408159                unlink
                0x0000000000408163                mlock
                0x000000000040816d                munlock
                0x0000000000408177                mlockall
                0x0000000000408181                munlockall
                0x000000000040818b                sysconf
                0x0000000000408195                fsync
                0x000000000040819f                fdatasync
                0x00000000004081a9                open
                0x00000000004081cf                close
                0x00000000004081ed                pipe
                0x000000000040820e                fpathconf
                0x0000000000408218                pathconf
                0x0000000000408222                __gethostname
                0x000000000040824e                gethostname
                0x0000000000408275                sethostname
                0x0000000000408296                getlogin
                0x00000000004082c2                setlogin
                0x00000000004082e8                getusername
                0x0000000000408365                setusername
                0x00000000004083dc                ttyname
                0x0000000000408419                ttyname_r
                0x0000000000408423                isatty
                0x0000000000408446                getopt
 .text          0x0000000000408450      0x165 termios.o
                0x0000000000408450                tcgetattr
                0x000000000040846e                tcsetattr
                0x00000000004084e7                tcsendbreak
                0x00000000004084f1                tcdrain
                0x00000000004084fb                tcflush
                0x0000000000408505                tcflow
                0x000000000040850f                cfmakeraw
                0x0000000000408581                cfgetispeed
                0x000000000040858c                cfgetospeed
                0x0000000000408597                cfsetispeed
                0x00000000004085a1                cfsetospeed
                0x00000000004085ab                cfsetspeed
 .text          0x00000000004085b5       0x3d ioctl.o
                0x00000000004085b5                ioctl
 .text          0x00000000004085f2       0x28 stubs.o
                0x00000000004085f2                gramado_system_call
                0x0000000000409000                . = ALIGN (0x1000)
 *fill*         0x000000000040861a      0x9e6 

.iplt           0x0000000000409000        0x0
 .iplt          0x0000000000409000        0x0 crt0.o

.rodata         0x0000000000409000     0x10c1
 .rodata        0x0000000000409000       0x5a crt0.o
 *fill*         0x000000000040905a        0x2 
 .rodata        0x000000000040905c      0x179 main.o
 *fill*         0x00000000004091d5        0x3 
 .rodata        0x00000000004091d8      0x505 api.o
 *fill*         0x00000000004096dd        0x3 
 .rodata        0x00000000004096e0      0x100 ctype.o
                0x00000000004096e0                _ctype
 .rodata        0x00000000004097e0      0x329 stdio.o
                0x0000000000409940                hex2ascii_data
 *fill*         0x0000000000409b09        0x7 
 .rodata        0x0000000000409b10      0x520 stdlib.o
 .rodata        0x000000000040a030        0x6 conio.o
 *fill*         0x000000000040a036        0x2 
 .rodata        0x000000000040a038       0x89 unistd.o

.eh_frame       0x000000000040a0c4     0x2e30
 .eh_frame      0x000000000040a0c4       0x34 crt0.o
 .eh_frame      0x000000000040a0f8      0x218 main.o
                                        0x230 (size before relaxing)
 .eh_frame      0x000000000040a310      0xd4c api.o
                                        0xd64 (size before relaxing)
 .eh_frame      0x000000000040b05c      0xb74 stdio.o
                                        0xb8c (size before relaxing)
 .eh_frame      0x000000000040bbd0      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040c1d0      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000040c690       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040c730      0x600 unistd.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040cd30      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x000000000040ceb0       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040ced0       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040cef4        0x0
 .rel.got       0x000000000040cef4        0x0 crt0.o
 .rel.iplt      0x000000000040cef4        0x0 crt0.o
 .rel.text      0x000000000040cef4        0x0 crt0.o

.data           0x000000000040cf00     0x1100
                0x000000000040cf00                data = .
                0x000000000040cf00                _data = .
                0x000000000040cf00                __data = .
 *(.data)
 .data          0x000000000040cf00       0x14 crt0.o
 *fill*         0x000000000040cf14        0xc 
 .data          0x000000000040cf20      0x444 main.o
                0x000000000040d360                listening
 *fill*         0x000000000040d364       0x1c 
 .data          0x000000000040d380      0x440 api.o
 .data          0x000000000040d7c0        0x0 ctype.o
 .data          0x000000000040d7c0        0x0 stdio.o
 .data          0x000000000040d7c0        0x8 stdlib.o
                0x000000000040d7c0                _infinity
 .data          0x000000000040d7c8        0x0 string.o
 .data          0x000000000040d7c8        0x0 conio.o
 .data          0x000000000040d7c8        0x0 unistd.o
 .data          0x000000000040d7c8        0x0 termios.o
 .data          0x000000000040d7c8        0x0 ioctl.o
 .data          0x000000000040d7c8        0x0 stubs.o
                0x000000000040e000                . = ALIGN (0x1000)
 *fill*         0x000000000040d7c8      0x838 

.got            0x000000000040e000        0x0
 .got           0x000000000040e000        0x0 crt0.o

.got.plt        0x000000000040e000        0x0
 .got.plt       0x000000000040e000        0x0 crt0.o

.igot.plt       0x000000000040e000        0x0
 .igot.plt      0x000000000040e000        0x0 crt0.o

.bss            0x000000000040e000    0x128e4
                0x000000000040e000                bss = .
                0x000000000040e000                _bss = .
                0x000000000040e000                __bss = .
 *(.bss)
 .bss           0x000000000040e000        0x0 crt0.o
 .bss           0x000000000040e000        0x0 main.o
 .bss           0x000000000040e000     0x8004 api.o
 .bss           0x0000000000416004        0x0 ctype.o
 .bss           0x0000000000416004        0x9 stdio.o
 *fill*         0x000000000041600d       0x13 
 .bss           0x0000000000416020     0x8020 stdlib.o
                0x0000000000416020                environ
 .bss           0x000000000041e040        0x4 string.o
 .bss           0x000000000041e044        0x0 conio.o
 *fill*         0x000000000041e044       0x1c 
 .bss           0x000000000041e060      0x19f unistd.o
                0x000000000041e060                __execv_environ
 .bss           0x000000000041e1ff        0x0 termios.o
 .bss           0x000000000041e1ff        0x0 ioctl.o
 .bss           0x000000000041e1ff        0x0 stubs.o
                0x000000000041f000                . = ALIGN (0x1000)
 *fill*         0x000000000041e1ff      0xe01 
 COMMON         0x000000000041f000      0xd08 crt0.o
                0x000000000041f000                g_cursor_x
                0x000000000041f004                stdout
                0x000000000041f008                g_char_attrib
                0x000000000041f00c                g_rows
                0x000000000041f020                Streams
                0x000000000041f0a0                g_using_gui
                0x000000000041f0c0                prompt_out
                0x000000000041f4c0                g_columns
                0x000000000041f4c4                prompt_pos
                0x000000000041f4c8                stdin
                0x000000000041f4cc                prompt_status
                0x000000000041f4e0                prompt_err
                0x000000000041f8e0                stderr
                0x000000000041f900                prompt
                0x000000000041fd00                g_cursor_y
                0x000000000041fd04                prompt_max
 *fill*         0x000000000041fd08       0x18 
 COMMON         0x000000000041fd20      0x22c main.o
                0x000000000041fd20                taskmanagerBuffer
                0x000000000041ff20                CurrentWindow
                0x000000000041ff24                ApplicationInfo
                0x000000000041ff28                BufferInfo
                0x000000000041ff2c                taskmanagerStatus
                0x000000000041ff30                CursorInfo
                0x000000000041ff34                rect
                0x000000000041ff38                taskmanagerBufferPos
                0x000000000041ff3c                ClientAreaInfo
                0x000000000041ff40                current_semaphore
                0x000000000041ff44                taskmanTest1
                0x000000000041ff48                taskmanagerError
 *fill*         0x000000000041ff4c       0x14 
 COMMON         0x000000000041ff60      0x440 api.o
                0x000000000041ff60                heapList
                0x0000000000420360                libcHeap
                0x0000000000420364                dialogbox_button2
                0x0000000000420368                messagebox_button1
                0x000000000042036c                heap_start
                0x0000000000420370                g_available_heap
                0x0000000000420374                g_heap_pointer
                0x0000000000420378                HEAP_SIZE
                0x000000000042037c                dialogbox_button1
                0x0000000000420380                first_responder
                0x0000000000420384                heap_end
                0x0000000000420388                __mb_current_button
                0x000000000042038c                HEAP_END
                0x0000000000420390                messagebox_button2
                0x0000000000420394                Heap
                0x0000000000420398                heapCount
                0x000000000042039c                HEAP_START
 COMMON         0x00000000004203a0        0x0 stdio.o
 COMMON         0x00000000004203a0      0x484 stdlib.o
                0x00000000004203a0                mm_prev_pointer
                0x00000000004203c0                mmblockList
                0x00000000004207c0                last_valid
                0x00000000004207c4                randseed
                0x00000000004207c8                mmblockCount
                0x00000000004207cc                last_size
                0x00000000004207e0                __ptsname_buffer
                0x0000000000420820                current_mmblock
 *fill*         0x0000000000420824       0x1c 
 COMMON         0x0000000000420840       0xa4 unistd.o
                0x0000000000420840                errno
                0x0000000000420844                optarg
                0x0000000000420848                opterr
                0x000000000042084c                my__p
                0x0000000000420850                optind
                0x0000000000420860                __Hostname_buffer
                0x00000000004208a0                __Login_buffer
                0x00000000004208e0                optopt
                0x00000000004208e4                end = .
                0x00000000004208e4                _end = .
                0x00000000004208e4                __end = .
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
LOAD unistd.o
LOAD termios.o
LOAD ioctl.o
LOAD stubs.o
OUTPUT(ZTASKMAN.BIN elf32-i386)

.comment        0x0000000000000000       0x11
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 api.o
 .comment       0x0000000000000011       0x12 ctype.o
 .comment       0x0000000000000011       0x12 stdio.o
 .comment       0x0000000000000011       0x12 stdlib.o
 .comment       0x0000000000000011       0x12 string.o
 .comment       0x0000000000000011       0x12 conio.o
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
                0x0000000000000000        0x0 unistd.o
 .note.GNU-stack
                0x0000000000000000        0x0 termios.o
 .note.GNU-stack
                0x0000000000000000        0x0 ioctl.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
