
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               main.o
g8x16fontAddress    0x4               main.o
stdout              0x4               crt0.o
SavedX              0x4               main.o
SavedBootBlock      0x4               main.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
__libc_tty_id       0x4               crt0.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
errno               0x4               unistd.o
__desktop           0x4               main.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
Streams             0x80              crt0.o
optarg              0x4               unistd.o
messagebox_button1  0x4               api.o
g_using_gui         0x4               crt0.o
opterr              0x4               unistd.o
SavedLFB            0x4               main.o
ApplicationInfo     0x4               main.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
gws_currentfont_address
                    0x4               main.o
BufferInfo          0x4               main.o
__mywindow          0x4               main.o
SavedY              0x4               main.o
__ws_pid            0x4               main.o
gcharHeight         0x4               main.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
my__p               0x4               unistd.o
HEAP_SIZE           0x4               stdlib.o
gui                 0x4               main.o
optind              0x4               unistd.o
dialogbox_button1   0x4               api.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
active_window       0x4               main.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
__Hostname_buffer   0x40              unistd.o
SavedBPP            0x4               main.o
prompt_status       0x4               crt0.o
first_responder     0x4               api.o
g8x8fontAddress     0x4               main.o
__ptsname_buffer    0x40              stdlib.o
__Login_buffer      0x40              unistd.o
prompt_err          0x400             crt0.o
____BACKBUFFER_VA   0x4               main.o
CursorInfo          0x4               main.o
g8x14fontAddress    0x4               main.o
heap_end            0x4               stdlib.o
g9x14fontAddress    0x4               main.o
stderr              0x4               crt0.o
__mb_current_button
                    0x4               api.o
optopt              0x4               unistd.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
gcharWidth          0x4               main.o
g_cursor_y          0x4               crt0.o
g9x16fontAddress    0x4               main.o
ClientAreaInfo      0x4               main.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
current_semaphore   0x4               main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               stdlib.o
HEAP_START          0x4               stdlib.o
gfontSize           0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000401000     0x9000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000       0xe8 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010e8      0x22a main.o
                0x00000000004010e8                gwsProcedure
                0x00000000004011db                main
 .text          0x0000000000401312       0x28 stubs.o
                0x0000000000401312                gramado_system_call
 .text          0x000000000040133a        0x0 ctype.o
 .text          0x000000000040133a     0x3231 stdio.o
                0x0000000000401382                stdio_atoi
                0x0000000000401449                stdio_fntos
                0x0000000000401573                debug_print
                0x0000000000401595                remove
                0x000000000040159f                fclose
                0x00000000004015cd                fopen
                0x00000000004016e5                creat
                0x000000000040170c                scroll
                0x00000000004017d9                fread
                0x00000000004017fa                fwrite
                0x000000000040181b                prompt_putchar
                0x000000000040186b                prompt_put_string
                0x0000000000401898                prompt_strcat
                0x00000000004018c5                prompt_flush
                0x0000000000401929                prompt_clean
                0x0000000000401d39                printf3
                0x0000000000401d56                printf_atoi
                0x0000000000401e47                printf_i2hex
                0x0000000000401ea9                printf2
                0x000000000040202e                stdio_nextline
                0x000000000040206c                nlsprintf
                0x00000000004020aa                sprintf
                0x00000000004020ff                libc_set_output_mode
                0x0000000000402143                outbyte
                0x0000000000402337                _outbyte
                0x0000000000402366                input
                0x00000000004024c6                stdioInitialize
                0x000000000040260c                fflush
                0x0000000000402622                __fflush
                0x00000000004026e4                __getc
                0x000000000040278f                __putc
                0x0000000000402834                getc
                0x000000000040284a                putc
                0x0000000000402863                fgetc
                0x0000000000402879                fputc
                0x0000000000402892                getchar
                0x00000000004028ab                putchar
                0x00000000004028c7                gets
                0x0000000000402909                puts
                0x0000000000402943                fgets
                0x000000000040299e                fputs
                0x00000000004029d2                getw
                0x0000000000402a13                putw
                0x0000000000402a42                fprintf
                0x0000000000402ae0                nputs
                0x0000000000402b1b                ungetc
                0x0000000000402b49                ftell
                0x0000000000402b77                fileno
                0x0000000000402ba5                __gramado__getc
                0x0000000000402c50                feof
                0x0000000000402c7e                ferror
                0x0000000000402cac                fseek
                0x0000000000402cda                __serenity_fflush
                0x0000000000402d7b                __serenity_fputc
                0x0000000000402e20                __serenity_putc
                0x0000000000402e39                stdioSetCursor
                0x0000000000402e54                stdioGetCursorX
                0x0000000000402e6f                stdioGetCursorY
                0x0000000000402e8a                scanf
                0x000000000040302b                sscanf
                0x00000000004031e6                kvprintf
                0x0000000000404050                printf
                0x000000000040407e                printf_draw
                0x00000000004040c6                vfprintf
                0x000000000040413e                vprintf
                0x000000000040416d                stdout_printf
                0x00000000004041a9                stderr_printf
                0x00000000004041e5                perror
                0x00000000004041fc                rewind
                0x0000000000404226                snprintf
                0x000000000040423a                stdio_initialize_standard_streams
                0x0000000000404295                libcStartTerminal
                0x0000000000404309                setbuf
                0x0000000000404333                setbuffer
                0x000000000040435d                setlinebuf
                0x0000000000404387                setvbuf
                0x00000000004043b5                filesize
                0x00000000004043fe                fileread
                0x000000000040444c                dprintf
                0x0000000000404463                vdprintf
                0x000000000040446d                vsprintf
                0x0000000000404477                vsnprintf
                0x0000000000404481                vscanf
                0x000000000040448b                vsscanf
                0x0000000000404495                vfscanf
                0x00000000004044ac                tmpnam
                0x00000000004044b6                tmpnam_r
                0x00000000004044c0                tempnam
                0x00000000004044ca                tmpfile
                0x00000000004044d4                fdopen
                0x00000000004044de                freopen
                0x00000000004044f5                open_memstream
                0x00000000004044ff                open_wmemstream
                0x0000000000404509                fmemopen
                0x0000000000404513                fgetpos
                0x000000000040452a                fsetpos
                0x0000000000404541                fpurge
                0x0000000000404558                __fpurge
                0x0000000000404561                ctermid
 .text          0x000000000040456b     0x114a stdlib.o
                0x0000000000404588                rtGetHeapStart
                0x0000000000404592                rtGetHeapEnd
                0x000000000040459c                rtGetHeapPointer
                0x00000000004045a6                rtGetAvailableHeap
                0x00000000004045b0                heapSetLibcHeap
                0x0000000000404663                heapAllocateMemory
                0x0000000000404895                FreeHeap
                0x000000000040489f                heapInit
                0x0000000000404a32                stdlibInitMM
                0x0000000000404a95                libcInitRT
                0x0000000000404ab7                mktemp
                0x0000000000404ac1                rand
                0x0000000000404ade                srand
                0x0000000000404aec                xmalloc
                0x0000000000404b1e                stdlib_die
                0x0000000000404b54                malloc
                0x0000000000404b90                realloc
                0x0000000000404bcd                free
                0x0000000000404bd3                calloc
                0x0000000000404c19                zmalloc
                0x0000000000404c55                system
                0x0000000000405019                stdlib_strncmp
                0x000000000040507c                __findenv
                0x0000000000405147                getenv
                0x0000000000405174                setenv
                0x000000000040517e                unsetenv
                0x0000000000405188                atoi
                0x000000000040524f                reverse
                0x00000000004052b7                itoa
                0x0000000000405365                abs
                0x0000000000405375                strtod
                0x00000000004055a6                strtof
                0x00000000004055c2                strtold
                0x00000000004055d5                atof
                0x00000000004055e7                labs
                0x00000000004055f7                mkstemp
                0x0000000000405601                mkostemp
                0x000000000040560b                mkstemps
                0x0000000000405615                mkostemps
                0x000000000040561f                ptsname
                0x0000000000405645                ptsname_r
                0x000000000040566c                posix_openpt
                0x0000000000405687                grantpt
                0x0000000000405691                getpt
                0x000000000040569b                unlockpt
                0x00000000004056a5                getprogname
                0x00000000004056af                setprogname
 .text          0x00000000004056b5      0xb2b string.o
                0x00000000004056b5                strcoll
                0x00000000004056ce                memsetw
                0x00000000004056fa                memcmp
                0x000000000040575f                strdup
                0x00000000004057b1                strndup
                0x0000000000405812                strnchr
                0x000000000040584b                strrchr
                0x0000000000405886                strtoimax
                0x0000000000405890                strtoumax
                0x000000000040589a                strcasecmp
                0x0000000000405902                strncpy
                0x0000000000405958                strcmp
                0x00000000004059bd                strncmp
                0x0000000000405a20                memset
                0x0000000000405a67                memoryZeroMemory
                0x0000000000405a8e                memcpy
                0x0000000000405acb                strcpy
                0x0000000000405aff                strlcpy
                0x0000000000405b5e                strcat
                0x0000000000405b8d                strchrnul
                0x0000000000405bb2                strlcat
                0x0000000000405c42                strncat
                0x0000000000405ca4                bcopy
                0x0000000000405cd1                bzero
                0x0000000000405cf2                strlen
                0x0000000000405d20                strnlen
                0x0000000000405d5b                strpbrk
                0x0000000000405da9                strsep
                0x0000000000405e27                strreplace
                0x0000000000405e62                strcspn
                0x0000000000405f01                strspn
                0x0000000000405fa0                strtok_r
                0x0000000000406087                strtok
                0x000000000040609f                strchr
                0x00000000004060cb                memmove
                0x000000000040614c                memscan
                0x0000000000406180                strstr
 .text          0x00000000004061e0       0x89 conio.o
                0x00000000004061e0                putch
                0x0000000000406204                cputs
                0x0000000000406239                getch
                0x0000000000406251                getche
 .text          0x0000000000406269       0xe0 socket.o
                0x0000000000406269                listen
                0x0000000000406273                recv
                0x000000000040627d                send
                0x0000000000406287                shutdown
                0x0000000000406291                socket
                0x00000000004062b2                socket_pipe
                0x00000000004062d3                socketpair
 .text          0x0000000000406349      0x142 signal.o
                0x0000000000406349                signal
                0x0000000000406351                sigaction
                0x000000000040635b                kill
                0x0000000000406365                raise
                0x0000000000406381                sigismember
                0x00000000004063cd                killpg
                0x00000000004063d7                sigemptyset
                0x00000000004063ea                sigfillset
                0x00000000004063fd                sigaddset
                0x0000000000406443                sigdelset
 .text          0x000000000040648b      0x663 unistd.o
                0x000000000040648b                execv
                0x00000000004064a9                execve
                0x0000000000406508                read_ttyList
                0x0000000000406536                write_ttyList
                0x0000000000406564                read_VC
                0x0000000000406592                write_VC
                0x00000000004065c0                read
                0x00000000004065eb                write
                0x0000000000406616                exit
                0x0000000000406636                fast_fork
                0x000000000040665e                fork
                0x0000000000406694                sys_fork
                0x00000000004066ca                setuid
                0x00000000004066e5                getuid
                0x0000000000406700                geteuid
                0x000000000040670a                getpid
                0x0000000000406722                getppid
                0x000000000040673a                getgid
                0x0000000000406755                dup
                0x000000000040676f                dup2
                0x000000000040678b                dup3
                0x00000000004067a9                fcntl
                0x00000000004067b3                getpriority
                0x00000000004067bd                setpriority
                0x00000000004067c7                nice
                0x00000000004067d1                pause
                0x00000000004067db                mkdir
                0x00000000004067ef                rmdir
                0x00000000004067f9                link
                0x0000000000406803                unlink
                0x000000000040680d                mlock
                0x0000000000406817                munlock
                0x0000000000406821                mlockall
                0x000000000040682b                munlockall
                0x0000000000406835                sysconf
                0x000000000040683f                fsync
                0x0000000000406849                fdatasync
                0x0000000000406853                open
                0x0000000000406879                close
                0x0000000000406897                pipe
                0x00000000004068b8                fpathconf
                0x00000000004068c2                pathconf
                0x00000000004068cc                __gethostname
                0x00000000004068f8                gethostname
                0x000000000040691c                sethostname
                0x000000000040693a                getlogin
                0x0000000000406966                setlogin
                0x000000000040698c                getusername
                0x0000000000406a06                setusername
                0x0000000000406a7a                ttyname
                0x0000000000406ab7                ttyname_r
                0x0000000000406ac1                isatty
                0x0000000000406ae4                getopt
 .text          0x0000000000406aee     0x21c6 api.o
                0x0000000000406aee                system_call
                0x0000000000406b16                gde_system
                0x0000000000406f1e                system1
                0x0000000000406f3f                system2
                0x0000000000406f60                system3
                0x0000000000406f81                system4
                0x0000000000406fa2                system5
                0x0000000000406fc3                system6
                0x0000000000406fe4                system7
                0x0000000000407005                system8
                0x0000000000407026                system9
                0x0000000000407047                system10
                0x0000000000407068                system11
                0x0000000000407089                system12
                0x00000000004070aa                system13
                0x00000000004070cb                system14
                0x00000000004070ec                system15
                0x000000000040710d                gde_refresh_buffer
                0x00000000004071e5                gde_print_string
                0x00000000004071eb                gde_vsync
                0x0000000000407203                gws_vsync
                0x0000000000407210                gde_system_procedure
                0x0000000000407253                __gde_set_cursor
                0x000000000040726d                __gde_put_char
                0x0000000000407273                gde_load_bitmap_16x16
                0x000000000040728c                gde_shutdown
                0x0000000000407293                gde_init_background
                0x0000000000407299                gde_message_box
                0x000000000040759e                mbProcedure
                0x000000000040775a                gde_dialog_box
                0x0000000000407b15                dbProcedure
                0x0000000000407b8b                call_kernel
                0x0000000000407cb3                call_gui
                0x0000000000407d48                gde_create_window
                0x0000000000407dc1                gde_register_window
                0x0000000000407de9                gde_close_window
                0x0000000000407e11                gde_set_focus
                0x0000000000407e39                gde_get_focus
                0x0000000000407e4e                gde_kill_focus
                0x0000000000407e76                gde_set_active_window
                0x0000000000407e9e                gde_get_active_window
                0x0000000000407eb3                gde_show_current_process_info
                0x0000000000407ec9                gde_resize_window
                0x0000000000407ee6                gde_redraw_window
                0x0000000000407f03                gde_replace_window
                0x0000000000407f1d                gde_maximize_window
                0x0000000000407f3c                gde_minimize_window
                0x0000000000407f5b                gde_update_window
                0x0000000000407f7d                gde_get_foregroung_window
                0x0000000000407f93                gde_set_foregroung_window
                0x0000000000407faf                gde_exit
                0x0000000000407fcc                gde_kill
                0x0000000000407fd2                gde_dead_thread_collector
                0x0000000000407fe8                gde_strncmp
                0x000000000040804b                gde_show_backbuffer
                0x0000000000408061                gde_reboot
                0x000000000040807a                gde_set_cursor
                0x0000000000408092                gde_get_cursor
                0x0000000000408098                gde_get_cursor_x
                0x00000000004080b3                gde_get_cursor_y
                0x00000000004080ce                gde_get_client_area_rect
                0x00000000004080e6                gde_set_client_area_rect
                0x0000000000408105                gde_create_process
                0x000000000040811e                gde_create_thread
                0x0000000000408137                gde_start_thread
                0x0000000000408153                gde_fopen
                0x000000000040817f                gde_save_file
                0x00000000004081d2                gde_create_empty_file
                0x00000000004081fc                gde_create_empty_directory
                0x0000000000408226                gde_down
                0x000000000040827b                gde_up
                0x00000000004082d0                gde_enter_critical_section
                0x000000000040830b                gde_exit_critical_section
                0x0000000000408324                gde_p
                0x000000000040832a                gde_v
                0x0000000000408330                gde_initialize_critical_section
                0x0000000000408349                gde_begin_paint
                0x0000000000408354                gde_end_paint
                0x000000000040835f                gde_put_char
                0x000000000040837b                gde_def_dialog
                0x0000000000408385                gde_get_system_metrics
                0x00000000004083a3                gde_dialog
                0x000000000040843c                gde_getchar
                0x0000000000408457                gde_display_bmp
                0x000000000040885e                gde_send_message_to_process
                0x00000000004088a1                gde_send_message_to_thread
                0x00000000004088e4                gde_send_message
                0x000000000040891a                gde_draw_text
                0x0000000000408959                gde_get_ws_screen_window
                0x0000000000408971                gde_get_ws_main_window
                0x0000000000408989                gde_create_timer
                0x00000000004089a9                gde_get_systime_info
                0x00000000004089ca                gde_show_window
                0x00000000004089e9                gde_start_terminal
                0x0000000000408a5d                gde_update_statusbar
                0x0000000000408a7b                gde_get_pid
                0x0000000000408aa6                gde_get_screen_window
                0x0000000000408ac1                gde_get_background_window
                0x0000000000408adc                gde_get_main_window
                0x0000000000408af7                gde_getprocessname
                0x0000000000408b74                gde_getthreadname
                0x0000000000408bf1                gde_get_process_stats
                0x0000000000408c0f                gde_get_thread_stats
                0x0000000000408c2d                gde_debug_print
                0x0000000000408c4f                gde_clone_and_execute
                0x0000000000408c6c                gde_setup_net_buffer
                0x0000000000408c93                execute_new_process
 .text          0x0000000000408cb4       0xf5 pixel.o
                0x0000000000408cb4                pixelBackBufferPutpixel2
                0x0000000000408ccf                pixelBackBufferPutpixel
 .text          0x0000000000408da9       0x2c line.o
                0x0000000000408da9                lineBackbufferDrawHorizontalLine
 .text          0x0000000000408dd5       0x87 rect.o
                0x0000000000408dd5                rectBackbufferDrawRectangle
 .text          0x0000000000408e5c      0x1c9 char.o
                0x0000000000408e5c                charBackbufferCharBlt
                0x0000000000408e79                charSetCharWidth
                0x0000000000408e87                charSetCharHeight
                0x0000000000408e95                charGetCharWidth
                0x0000000000408e9f                charGetCharHeight
                0x0000000000408ea9                charBackbufferDrawcharTransparent
                0x0000000000408f64                charBackbufferDrawchar
 .text          0x0000000000409025       0xdf dtext.o
                0x0000000000409025                dtextDrawString
                0x000000000040909e                dtextDrawText
 .text          0x0000000000409104      0x9d6 createw.o
                0x0000000000409104                createwDrawTitleBar
                0x0000000000409192                createwDrawFrame
                0x00000000004093a9                createwCreateWindow2
                0x00000000004099f2                createwCreateWindow
 .text          0x0000000000409ada      0x104 gws.o
                0x0000000000409ada                gwsInit
                0x0000000000409bc1                serverInit
 .text          0x0000000000409bde        0x6 comp.o
                0x0000000000409bde                compositor_loop
 .text          0x0000000000409be4      0x165 termios.o
                0x0000000000409be4                tcgetattr
                0x0000000000409c02                tcsetattr
                0x0000000000409c7b                tcsendbreak
                0x0000000000409c85                tcdrain
                0x0000000000409c8f                tcflush
                0x0000000000409c99                tcflow
                0x0000000000409ca3                cfmakeraw
                0x0000000000409d15                cfgetispeed
                0x0000000000409d20                cfgetospeed
                0x0000000000409d2b                cfsetispeed
                0x0000000000409d35                cfsetospeed
                0x0000000000409d3f                cfsetspeed
 .text          0x0000000000409d49       0x3d ioctl.o
                0x0000000000409d49                ioctl
                0x000000000040a000                . = ALIGN (0x1000)
 *fill*         0x0000000000409d86      0x27a 

.iplt           0x000000000040a000        0x0
 .iplt          0x000000000040a000        0x0 crt0.o

.rodata         0x000000000040a000     0x147d
 .rodata        0x000000000040a000       0x22 crt0.o
 *fill*         0x000000000040a022        0x2 
 .rodata        0x000000000040a024       0xe1 main.o
 *fill*         0x000000000040a105       0x1b 
 .rodata        0x000000000040a120      0x100 ctype.o
                0x000000000040a120                _ctype
 .rodata        0x000000000040a220      0x489 stdio.o
                0x000000000040a4e0                hex2ascii_data
 *fill*         0x000000000040a6a9        0x7 
 .rodata        0x000000000040a6b0      0x520 stdlib.o
 .rodata        0x000000000040abd0        0x6 conio.o
 .rodata        0x000000000040abd6       0x12 socket.o
 .rodata        0x000000000040abe8      0x1d4 signal.o
 .rodata        0x000000000040adbc       0x89 unistd.o
 *fill*         0x000000000040ae45        0x3 
 .rodata        0x000000000040ae48      0x505 api.o
 .rodata        0x000000000040b34d       0x22 pixel.o
 *fill*         0x000000000040b36f        0x1 
 .rodata        0x000000000040b370       0x54 char.o
 .rodata        0x000000000040b3c4       0x1e dtext.o
 *fill*         0x000000000040b3e2        0x2 
 .rodata        0x000000000040b3e4       0x60 createw.o
 .rodata        0x000000000040b444       0x39 gws.o

.eh_frame       0x000000000040b480     0x3494
 .eh_frame      0x000000000040b480       0x34 crt0.o
 .eh_frame      0x000000000040b4b4       0x48 main.o
                                         0x60 (size before relaxing)
 .eh_frame      0x000000000040b4fc       0x24 stubs.o
                                         0x3c (size before relaxing)
 .eh_frame      0x000000000040b520      0xde8 stdio.o
                                        0xe00 (size before relaxing)
 .eh_frame      0x000000000040c308      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040c908      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000040cdc8       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040ce68       0xe0 socket.o
                                         0xf8 (size before relaxing)
 .eh_frame      0x000000000040cf48      0x14c signal.o
                                        0x164 (size before relaxing)
 .eh_frame      0x000000000040d094      0x6a0 unistd.o
                                        0x6b8 (size before relaxing)
 .eh_frame      0x000000000040d734      0xdac api.o
                                        0xdc4 (size before relaxing)
 .eh_frame      0x000000000040e4e0       0x40 pixel.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040e520       0x20 line.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040e540       0x20 rect.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040e560       0xe0 char.o
                                         0xf8 (size before relaxing)
 .eh_frame      0x000000000040e640       0x40 dtext.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040e680       0x90 createw.o
                                         0xa8 (size before relaxing)
 .eh_frame      0x000000000040e710       0x44 gws.o
                                         0x5c (size before relaxing)
 .eh_frame      0x000000000040e754       0x20 comp.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040e774      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x000000000040e8f4       0x20 ioctl.o
                                         0x38 (size before relaxing)

.rel.dyn        0x000000000040e914        0x0
 .rel.got       0x000000000040e914        0x0 crt0.o
 .rel.iplt      0x000000000040e914        0x0 crt0.o
 .rel.text      0x000000000040e914        0x0 crt0.o

.data           0x000000000040e920     0x36e0
                0x000000000040e920                data = .
                0x000000000040e920                _data = .
                0x000000000040e920                __data = .
 *(.data)
 .data          0x000000000040e920       0x14 crt0.o
 *fill*         0x000000000040e934        0xc 
 .data          0x000000000040e940      0x440 main.o
 .data          0x000000000040ed80        0x0 stubs.o
 .data          0x000000000040ed80        0x0 ctype.o
 .data          0x000000000040ed80        0x0 stdio.o
 .data          0x000000000040ed80        0x8 stdlib.o
                0x000000000040ed80                _infinity
 .data          0x000000000040ed88        0x0 string.o
 .data          0x000000000040ed88        0x0 conio.o
 .data          0x000000000040ed88        0x0 socket.o
 *fill*         0x000000000040ed88       0x18 
 .data          0x000000000040eda0       0x80 signal.o
                0x000000000040eda0                sys_siglist
 .data          0x000000000040ee20        0x0 unistd.o
 .data          0x000000000040ee20      0x440 api.o
 .data          0x000000000040f260      0x440 pixel.o
 .data          0x000000000040f6a0      0x440 line.o
 .data          0x000000000040fae0      0x440 rect.o
 .data          0x000000000040ff20      0x440 char.o
 .data          0x0000000000410360      0x440 dtext.o
 .data          0x00000000004107a0      0x440 createw.o
 .data          0x0000000000410be0      0x840 gws.o
 .data          0x0000000000411420      0x840 comp.o
 .data          0x0000000000411c60        0x0 termios.o
 .data          0x0000000000411c60        0x0 ioctl.o
                0x0000000000412000                . = ALIGN (0x1000)
 *fill*         0x0000000000411c60      0x3a0 

.got            0x0000000000412000        0x0
 .got           0x0000000000412000        0x0 crt0.o

.got.plt        0x0000000000412000        0x0
 .got.plt       0x0000000000412000        0x0 crt0.o

.igot.plt       0x0000000000412000        0x0
 .igot.plt      0x0000000000412000        0x0 crt0.o

.bss            0x0000000000412000    0x126fc
                0x0000000000412000                bss = .
                0x0000000000412000                _bss = .
                0x0000000000412000                __bss = .
 *(.bss)
 .bss           0x0000000000412000        0x0 crt0.o
 .bss           0x0000000000412000        0x0 main.o
 .bss           0x0000000000412000        0x0 stubs.o
 .bss           0x0000000000412000        0x0 ctype.o
 .bss           0x0000000000412000        0x9 stdio.o
 *fill*         0x0000000000412009       0x17 
 .bss           0x0000000000412020     0x8020 stdlib.o
                0x0000000000412020                environ
 .bss           0x000000000041a040        0x4 string.o
 .bss           0x000000000041a044        0x0 conio.o
 .bss           0x000000000041a044        0x0 socket.o
 .bss           0x000000000041a044        0x0 signal.o
 *fill*         0x000000000041a044       0x1c 
 .bss           0x000000000041a060      0x11f unistd.o
                0x000000000041a060                __execv_environ
 *fill*         0x000000000041a17f        0x1 
 .bss           0x000000000041a180     0x8004 api.o
 .bss           0x0000000000422184        0x0 pixel.o
 .bss           0x0000000000422184        0x0 line.o
 .bss           0x0000000000422184        0x0 rect.o
 .bss           0x0000000000422184        0x0 char.o
 .bss           0x0000000000422184        0x0 dtext.o
 .bss           0x0000000000422184        0x0 createw.o
 .bss           0x0000000000422184        0x0 gws.o
 .bss           0x0000000000422184        0x0 comp.o
 .bss           0x0000000000422184        0x0 termios.o
 .bss           0x0000000000422184        0x0 ioctl.o
                0x0000000000423000                . = ALIGN (0x1000)
 *fill*         0x0000000000422184      0xe7c 
 COMMON         0x0000000000423000      0xd08 crt0.o
                0x0000000000423000                g_cursor_x
                0x0000000000423004                stdout
                0x0000000000423008                __libc_tty_id
                0x000000000042300c                g_char_attrib
                0x0000000000423010                g_rows
                0x0000000000423020                Streams
                0x00000000004230a0                g_using_gui
                0x00000000004230c0                prompt_out
                0x00000000004234c0                g_columns
                0x00000000004234c4                prompt_pos
                0x00000000004234c8                stdin
                0x00000000004234cc                prompt_status
                0x00000000004234e0                prompt_err
                0x00000000004238e0                stderr
                0x0000000000423900                prompt
                0x0000000000423d00                g_cursor_y
                0x0000000000423d04                prompt_max
 COMMON         0x0000000000423d08       0x68 main.o
                0x0000000000423d08                CurrentWindow
                0x0000000000423d0c                g8x16fontAddress
                0x0000000000423d10                SavedX
                0x0000000000423d14                SavedBootBlock
                0x0000000000423d18                __desktop
                0x0000000000423d1c                SavedLFB
                0x0000000000423d20                ApplicationInfo
                0x0000000000423d24                gws_currentfont_address
                0x0000000000423d28                BufferInfo
                0x0000000000423d2c                __mywindow
                0x0000000000423d30                SavedY
                0x0000000000423d34                __ws_pid
                0x0000000000423d38                gcharHeight
                0x0000000000423d3c                gui
                0x0000000000423d40                active_window
                0x0000000000423d44                SavedBPP
                0x0000000000423d48                g8x8fontAddress
                0x0000000000423d4c                ____BACKBUFFER_VA
                0x0000000000423d50                CursorInfo
                0x0000000000423d54                g8x14fontAddress
                0x0000000000423d58                g9x14fontAddress
                0x0000000000423d5c                gcharWidth
                0x0000000000423d60                g9x16fontAddress
                0x0000000000423d64                ClientAreaInfo
                0x0000000000423d68                current_semaphore
                0x0000000000423d6c                gfontSize
 COMMON         0x0000000000423d70        0x0 stdio.o
 *fill*         0x0000000000423d70       0x10 
 COMMON         0x0000000000423d80      0x8b8 stdlib.o
                0x0000000000423d80                mm_prev_pointer
                0x0000000000423da0                mmblockList
                0x00000000004241a0                last_valid
                0x00000000004241c0                heapList
                0x00000000004245c0                libcHeap
                0x00000000004245c4                randseed
                0x00000000004245c8                heap_start
                0x00000000004245cc                g_available_heap
                0x00000000004245d0                g_heap_pointer
                0x00000000004245d4                HEAP_SIZE
                0x00000000004245d8                mmblockCount
                0x00000000004245dc                last_size
                0x00000000004245e0                __ptsname_buffer
                0x0000000000424620                heap_end
                0x0000000000424624                HEAP_END
                0x0000000000424628                Heap
                0x000000000042462c                current_mmblock
                0x0000000000424630                heapCount
                0x0000000000424634                HEAP_START
 *fill*         0x0000000000424638        0x8 
 COMMON         0x0000000000424640       0xa4 unistd.o
                0x0000000000424640                errno
                0x0000000000424644                optarg
                0x0000000000424648                opterr
                0x000000000042464c                my__p
                0x0000000000424650                optind
                0x0000000000424660                __Hostname_buffer
                0x00000000004246a0                __Login_buffer
                0x00000000004246e0                optopt
 COMMON         0x00000000004246e4       0x18 api.o
                0x00000000004246e4                dialogbox_button2
                0x00000000004246e8                messagebox_button1
                0x00000000004246ec                dialogbox_button1
                0x00000000004246f0                first_responder
                0x00000000004246f4                __mb_current_button
                0x00000000004246f8                messagebox_button2
                0x00000000004246fc                end = .
                0x00000000004246fc                _end = .
                0x00000000004246fc                __end = .
LOAD crt0.o
LOAD main.o
LOAD stubs.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
LOAD socket.o
LOAD signal.o
LOAD unistd.o
LOAD api.o
LOAD pixel.o
LOAD line.o
LOAD rect.o
LOAD char.o
LOAD dtext.o
LOAD createw.o
LOAD gws.o
LOAD comp.o
LOAD termios.o
LOAD ioctl.o
OUTPUT(GWS.BIN elf32-i386)

.comment        0x0000000000000000       0x11
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 stubs.o
 .comment       0x0000000000000011       0x12 ctype.o
 .comment       0x0000000000000011       0x12 stdio.o
 .comment       0x0000000000000011       0x12 stdlib.o
 .comment       0x0000000000000011       0x12 string.o
 .comment       0x0000000000000011       0x12 conio.o
 .comment       0x0000000000000011       0x12 socket.o
 .comment       0x0000000000000011       0x12 signal.o
 .comment       0x0000000000000011       0x12 unistd.o
 .comment       0x0000000000000011       0x12 api.o
 .comment       0x0000000000000011       0x12 pixel.o
 .comment       0x0000000000000011       0x12 line.o
 .comment       0x0000000000000011       0x12 rect.o
 .comment       0x0000000000000011       0x12 char.o
 .comment       0x0000000000000011       0x12 dtext.o
 .comment       0x0000000000000011       0x12 createw.o
 .comment       0x0000000000000011       0x12 gws.o
 .comment       0x0000000000000011       0x12 comp.o
 .comment       0x0000000000000011       0x12 termios.o
 .comment       0x0000000000000011       0x12 ioctl.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
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
                0x0000000000000000        0x0 socket.o
 .note.GNU-stack
                0x0000000000000000        0x0 signal.o
 .note.GNU-stack
                0x0000000000000000        0x0 unistd.o
 .note.GNU-stack
                0x0000000000000000        0x0 api.o
 .note.GNU-stack
                0x0000000000000000        0x0 pixel.o
 .note.GNU-stack
                0x0000000000000000        0x0 line.o
 .note.GNU-stack
                0x0000000000000000        0x0 rect.o
 .note.GNU-stack
                0x0000000000000000        0x0 char.o
 .note.GNU-stack
                0x0000000000000000        0x0 dtext.o
 .note.GNU-stack
                0x0000000000000000        0x0 createw.o
 .note.GNU-stack
                0x0000000000000000        0x0 gws.o
 .note.GNU-stack
                0x0000000000000000        0x0 comp.o
 .note.GNU-stack
                0x0000000000000000        0x0 termios.o
 .note.GNU-stack
                0x0000000000000000        0x0 ioctl.o
