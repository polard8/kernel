
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               api.o
stdout              0x4               crt0.o
p                   0x4               c4.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
__libc_tty_id       0x4               crt0.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
lp                  0x4               c4.o
tk                  0x4               c4.o
dialogbox_button2   0x4               api.o
le                  0x4               c4.o
Streams             0x80              crt0.o
optarg              0x4               unistd.o
messagebox_button1  0x4               api.o
g_using_gui         0x4               crt0.o
opterr              0x4               unistd.o
line                0x4               c4.o
ApplicationInfo     0x4               api.o
debug               0x4               c4.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
id                  0x4               c4.o
BufferInfo          0x4               api.o
environ             0x4               stdio.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
optind              0x4               unistd.o
dialogbox_button1   0x4               api.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
__Hostname_buffer   0x40              unistd.o
prompt_status       0x4               crt0.o
first_responder     0x4               api.o
__Login_buffer      0x40              unistd.o
prompt_err          0x400             crt0.o
loc                 0x4               c4.o
CursorInfo          0x4               api.o
heap_end            0x4               stdlib.o
stderr              0x4               crt0.o
__mb_current_button
                    0x4               api.o
optopt              0x4               unistd.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
ty                  0x4               c4.o
src                 0x4               c4.o
g_cursor_y          0x4               crt0.o
ClientAreaInfo      0x4               api.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
e                   0x4               c4.o
ival                0x4               c4.o
current_semaphore   0x4               api.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               stdlib.o
sym                 0x4               c4.o
HEAP_START          0x4               stdlib.o

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
 .text          0x0000000000401000       0xf2 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010f2     0x33c7 c4.o
                0x00000000004010f2                next
                0x00000000004019db                expr
                0x00000000004031a7                stmt
                0x00000000004034da                main
 .text          0x00000000004044b9        0x0 ctype.o
 .text          0x00000000004044b9     0x3fbd stdio.o
                0x0000000000404501                stdio_atoi
                0x00000000004045c8                stdio_fntos
                0x00000000004046f0                remove
                0x000000000040470d                _strout
                0x00000000004047ac                fflush
                0x00000000004047c2                __fflush
                0x0000000000404884                __(bool, float, int, long, long)
                0x0000000000404993                __getc
                0x0000000000404ad8                __putc
                0x0000000000404b7d                getc
                0x0000000000404b93                putc
                0x0000000000404bac                fgetc
                0x0000000000404bc2                fputc
                0x0000000000404bdb                getchar
                0x0000000000404bf4                putchar
                0x0000000000404c10                gets
                0x0000000000404c52                puts
                0x0000000000404c8c                fgets
                0x0000000000404ce7                fputs
                0x0000000000404d1b                getw
                0x0000000000404d5c                putw
                0x0000000000404d8f                fclose
                0x0000000000404de9                fopen
                0x0000000000404f0a                fopen2
                0x0000000000405061                scroll
                0x000000000040512e                clearerr
                0x0000000000405150                fread
                0x00000000004051f8                fwrite
                0x00000000004052a0                prompt_putchar
                0x00000000004052f5                prompt_put_string
                0x0000000000405322                prompt_strcat
                0x000000000040534f                prompt_flush
                0x00000000004053b3                prompt_clean
                0x00000000004057ca                printf3
                0x00000000004057e7                printf_atoi
                0x00000000004058d7                printf_i2hex
                0x0000000000405939                printf2
                0x0000000000405abe                stdio_nextline
                0x0000000000405afc                nlsprintf
                0x0000000000405b3a                sprintf
                0x0000000000405b8f                libc_set_output_mode
                0x0000000000405bd4                outbyte
                0x0000000000405d92                _outbyte
                0x0000000000405dc1                input
                0x0000000000405f15                fprintf
                0x0000000000405f3f                nputs
                0x0000000000405f79                uclib_gets
                0x0000000000405faa                ungetc
                0x0000000000405ffc                ftell
                0x000000000040603d                fileno
                0x0000000000406057                linux_fgetc
                0x0000000000406096                fgets2
                0x0000000000406121                fputs2
                0x0000000000406171                gets2
                0x00000000004061fe                puts2
                0x0000000000406219                getchar2
                0x0000000000406247                feof
                0x000000000040625f                ferror
                0x0000000000406277                fseek
                0x0000000000406294                linux_fputc
                0x00000000004062d5                debug_print
                0x00000000004062f7                stdioSetCursor
                0x0000000000406312                stdioGetCursorX
                0x000000000040632d                stdioGetCursorY
                0x0000000000406348                scanf
                0x00000000004064e9                sscanf
                0x00000000004066a8                kvprintf
                0x0000000000407512                printf
                0x0000000000407540                printf_draw
                0x0000000000407588                vfprintf
                0x0000000000407600                vprintf
                0x000000000040762f                stdout_printf
                0x000000000040766b                stderr_printf
                0x00000000004076ae                perror
                0x00000000004076d5                rewind
                0x00000000004076ef                snprintf
                0x0000000000407703                stdio_initialize_standard_streams
                0x000000000040772e                libcStartTerminal
                0x00000000004077a2                setbuf
                0x00000000004077bb                setbuffer
                0x00000000004077e5                setlinebuf
                0x00000000004077fe                setvbuf
                0x00000000004078ce                filesize
                0x0000000000407917                fileread
                0x0000000000407965                dprintf
                0x0000000000407982                vdprintf
                0x0000000000407c25                Wirzenius_Torvalds_vsprintf
                0x0000000000407ffe                Torvalds_printf
                0x0000000000408045                vsnprintf
                0x0000000000408062                vscanf
                0x000000000040807f                vsscanf
                0x000000000040809c                vfscanf
                0x00000000004080c6                tmpfile
                0x00000000004080e3                tmpnam
                0x0000000000408100                tmpnam_r
                0x000000000040811d                tempnam
                0x000000000040813a                stdio_make_file
                0x00000000004081b5                fdopen
                0x00000000004081db                freopen
                0x0000000000408205                open_memstream
                0x0000000000408222                open_wmemstream
                0x000000000040823f                fmemopen
                0x000000000040825c                fgetpos
                0x000000000040829b                fsetpos
                0x00000000004082c6                fpurge
                0x00000000004082f0                __fpurge
                0x000000000040830c                ctermid
                0x0000000000408329                stdioInitialize
 .text          0x0000000000408476     0x1201 stdlib.o
                0x0000000000408493                rtGetHeapStart
                0x000000000040849d                rtGetHeapEnd
                0x00000000004084a7                rtGetHeapPointer
                0x00000000004084b1                rtGetAvailableHeap
                0x00000000004084bb                heapSetLibcHeap
                0x000000000040856e                heapAllocateMemory
                0x00000000004087a0                FreeHeap
                0x00000000004087aa                heapInit
                0x000000000040893d                stdlibInitMM
                0x00000000004089a0                libcInitRT
                0x00000000004089c9                mktemp
                0x00000000004089d3                rand
                0x00000000004089f0                srand
                0x00000000004089fe                xmalloc
                0x0000000000408a30                stdlib_die
                0x0000000000408a66                malloc
                0x0000000000408aa2                realloc
                0x0000000000408adf                free
                0x0000000000408ae5                calloc
                0x0000000000408b2b                zmalloc
                0x0000000000408b67                system
                0x0000000000408f2b                stdlib_strncmp
                0x0000000000408fe1                v7_getenv
                0x000000000040901d                __findenv
                0x0000000000409140                getenv
                0x000000000040916d                setenv
                0x0000000000409177                unsetenv
                0x0000000000409181                atoi
                0x0000000000409248                reverse
                0x00000000004092af                itoa
                0x000000000040935d                abs
                0x000000000040936d                strtod
                0x000000000040959f                strtof
                0x00000000004095bb                strtold
                0x00000000004095ce                atof
                0x00000000004095e0                labs
                0x00000000004095f0                mkstemp
                0x00000000004095fa                mkostemp
                0x0000000000409604                mkstemps
                0x000000000040960e                mkostemps
                0x0000000000409618                ptsname
                0x0000000000409622                ptsname_r
                0x000000000040962c                posix_openpt
                0x0000000000409649                grantpt
                0x0000000000409653                unlockpt
                0x000000000040965d                getpt
                0x0000000000409667                getprogname
                0x0000000000409671                setprogname
 .text          0x0000000000409677      0xccf string.o
                0x00000000004096a2                strcoll
                0x00000000004096bb                memsetw
                0x00000000004096e7                memcmp
                0x000000000040974c                strdup
                0x000000000040979e                strndup
                0x00000000004097ff                strnchr
                0x0000000000409838                strrchr
                0x0000000000409873                strtoimax
                0x0000000000409890                strtoumax
                0x00000000004098ad                strcasecmp
                0x0000000000409915                strncpy
                0x000000000040996b                strcmp
                0x00000000004099d7                strncmp
                0x0000000000409a31                memset
                0x0000000000409a78                memoryZeroMemory
                0x0000000000409a9f                memcpy
                0x0000000000409adc                strcpy
                0x0000000000409b10                strlcpy
                0x0000000000409b6f                strcat
                0x0000000000409b9e                strchrnul
                0x0000000000409bc3                strlcat
                0x0000000000409c55                strncat
                0x0000000000409cb7                bcopy
                0x0000000000409ce3                bzero
                0x0000000000409d03                strlen
                0x0000000000409d31                strnlen
                0x0000000000409d6c                strpbrk
                0x0000000000409dba                strsep
                0x0000000000409e38                strreplace
                0x0000000000409e73                strcspn
                0x0000000000409f12                strspn
                0x0000000000409fb1                strtok_r
                0x000000000040a098                strtok
                0x000000000040a0b0                strchr
                0x000000000040a0dc                memmove
                0x000000000040a15d                memscan
                0x000000000040a191                strstr
                0x000000000040a1f1                index
                0x000000000040a21e                rindex
                0x000000000040a231                strxfrm
                0x000000000040a283                strerror
                0x000000000040a2a0                strerror_r
                0x000000000040a2e9                strsignal
                0x000000000040a306                strtoupper
 .text          0x000000000040a346       0x33 time.o
                0x000000000040a346                time
                0x000000000040a36f                gettimeofday
 .text          0x000000000040a379     0x1a15 api.o
                0x000000000040a379                system_call
                0x000000000040a3a1                gde_system
                0x000000000040a3ab                gde_refresh_buffer
                0x000000000040a487                gde_print_string
                0x000000000040a48d                gde_vsync
                0x000000000040a4a5                gde_system_procedure
                0x000000000040a4e8                __gde_set_cursor
                0x000000000040a502                __gde_put_char
                0x000000000040a508                gde_load_bitmap_16x16
                0x000000000040a521                gde_shutdown
                0x000000000040a528                gde_init_background
                0x000000000040a52e                gde_message_box
                0x000000000040a831                mbProcedure
                0x000000000040a9ee                gde_dialog_box
                0x000000000040ad9e                dbProcedure
                0x000000000040ae00                gde_create_window
                0x000000000040ae79                gde_register_window
                0x000000000040aea1                gde_close_window
                0x000000000040aec9                gde_set_focus
                0x000000000040aef1                gde_get_focus
                0x000000000040af06                gde_kill_focus
                0x000000000040af2e                gde_set_active_window
                0x000000000040af56                gde_get_active_window
                0x000000000040af6b                gde_show_current_process_info
                0x000000000040af81                gde_resize_window
                0x000000000040af9e                gde_redraw_window
                0x000000000040afbb                gde_replace_window
                0x000000000040afd5                gde_maximize_window
                0x000000000040aff4                gde_minimize_window
                0x000000000040b013                gde_update_window
                0x000000000040b035                gde_get_foregroung_window
                0x000000000040b04b                gde_set_foregroung_window
                0x000000000040b067                gde_exit
                0x000000000040b084                gde_kill
                0x000000000040b08a                gde_dead_thread_collector
                0x000000000040b0a0                gde_strncmp
                0x000000000040b103                gde_show_backbuffer
                0x000000000040b119                gde_reboot
                0x000000000040b132                gde_set_cursor
                0x000000000040b14a                gde_get_cursor
                0x000000000040b150                gde_get_cursor_x
                0x000000000040b16b                gde_get_cursor_y
                0x000000000040b186                gde_get_client_area_rect
                0x000000000040b19e                gde_set_client_area_rect
                0x000000000040b1bd                gde_create_process
                0x000000000040b1d6                gde_create_thread
                0x000000000040b1ef                gde_start_thread
                0x000000000040b20b                gde_fopen
                0x000000000040b237                gde_save_file
                0x000000000040b291                gde_create_empty_file
                0x000000000040b2c2                gde_create_empty_directory
                0x000000000040b2f3                gde_down
                0x000000000040b348                gde_up
                0x000000000040b39d                gde_enter_critical_section
                0x000000000040b3d8                gde_exit_critical_section
                0x000000000040b3f1                gde_p
                0x000000000040b3f7                gde_v
                0x000000000040b3fd                gde_initialize_critical_section
                0x000000000040b416                gde_begin_paint
                0x000000000040b421                gde_end_paint
                0x000000000040b42c                gde_put_char
                0x000000000040b448                gde_def_dialog
                0x000000000040b452                gde_get_system_metrics
                0x000000000040b470                gde_dialog
                0x000000000040b501                gde_getchar
                0x000000000040b51c                gde_display_bmp
                0x000000000040b923                gde_send_message_to_process
                0x000000000040b966                gde_send_message_to_thread
                0x000000000040b9a9                gde_send_message
                0x000000000040b9df                gde_draw_text
                0x000000000040ba1e                gde_get_ws_screen_window
                0x000000000040ba36                gde_get_ws_main_window
                0x000000000040ba4e                gde_create_timer
                0x000000000040ba6e                gde_get_systime_info
                0x000000000040ba8f                gde_show_window
                0x000000000040baae                gde_start_terminal
                0x000000000040bb22                gde_update_statusbar
                0x000000000040bb40                gde_get_pid
                0x000000000040bb6b                gde_get_screen_window
                0x000000000040bb86                gde_get_background_window
                0x000000000040bba1                gde_get_main_window
                0x000000000040bbbc                gde_getprocessname
                0x000000000040bc40                gde_getthreadname
                0x000000000040bcc4                gde_get_process_stats
                0x000000000040bce2                gde_get_thread_stats
                0x000000000040bd00                gde_debug_print
                0x000000000040bd22                gde_clone_and_execute
                0x000000000040bd3f                gde_setup_net_buffer
                0x000000000040bd6d                execute_new_process
 .text          0x000000000040bd8e      0xb4c unistd.o
                0x000000000040bd8e                execv
                0x000000000040bdac                execve
                0x000000000040bde7                read_ttyList
                0x000000000040be15                write_ttyList
                0x000000000040be43                read_tty
                0x000000000040be71                write_tty
                0x000000000040be9f                read_VC
                0x000000000040becd                write_VC
                0x000000000040befb                read
                0x000000000040bf26                write
                0x000000000040bf51                exit
                0x000000000040bf71                fork
                0x000000000040bfa3                setuid
                0x000000000040bfbe                getuid
                0x000000000040bfd9                geteuid
                0x000000000040bff6                getpid
                0x000000000040c00e                getppid
                0x000000000040c026                getgid
                0x000000000040c041                dup
                0x000000000040c05b                dup2
                0x000000000040c077                dup3
                0x000000000040c095                getpriority
                0x000000000040c0b2                setpriority
                0x000000000040c0cf                nice
                0x000000000040c0ec                pause
                0x000000000040c109                mkdir
                0x000000000040c12d                rmdir
                0x000000000040c14a                link
                0x000000000040c167                unlink
                0x000000000040c184                mlock
                0x000000000040c1a1                munlock
                0x000000000040c1be                mlockall
                0x000000000040c1db                munlockall
                0x000000000040c1f8                sysconf
                0x000000000040c215                fsync
                0x000000000040c232                fdatasync
                0x000000000040c24f                sync
                0x000000000040c268                syncfs
                0x000000000040c285                close
                0x000000000040c2a3                pipe2
                0x000000000040c2c2                pipe
                0x000000000040c2da                fpathconf
                0x000000000040c2f7                pathconf
                0x000000000040c314                __gethostname
                0x000000000040c340                gethostname
                0x000000000040c36b                sethostname
                0x000000000040c389                getlogin
                0x000000000040c3b5                setlogin
                0x000000000040c3db                getusername
                0x000000000040c455                setusername
                0x000000000040c4c9                ttyname
                0x000000000040c50d                ttyname_r
                0x000000000040c52a                isatty
                0x000000000040c54d                getopt
                0x000000000040c56a                alarm
                0x000000000040c587                brk
                0x000000000040c5a4                execvp
                0x000000000040c5c1                execvpe
                0x000000000040c5de                chown
                0x000000000040c5fb                fchown
                0x000000000040c618                lchown
                0x000000000040c635                chdir
                0x000000000040c652                fchdir
                0x000000000040c66f                sleep
                0x000000000040c68c                _exit
                0x000000000040c6a2                swab_w
                0x000000000040c6e1                swab
                0x000000000040c6f8                lseek
                0x000000000040c715                tell
                0x000000000040c72f                access
                0x000000000040c74c                uname
                0x000000000040c779                eq
                0x000000000040c7c5                getlin
                0x000000000040c856                compar
                0x000000000040c8b2                xxx_todo_int133
 .text          0x000000000040c8da       0xe8 math.o
                0x000000000040c8da                pow
                0x000000000040c8fc                sqrt
                0x000000000040c912                floor
                0x000000000040c928                ceil
                0x000000000040c93e                atan
                0x000000000040c954                acos
                0x000000000040c96a                asin
                0x000000000040c980                tan
                0x000000000040c996                cos
                0x000000000040c9ac                sin
 .text          0x000000000040c9c2      0x282 strtol.o
                0x000000000040c9df                strtol
 .text          0x000000000040cc44      0x1ce strtoul.o
                0x000000000040cc61                strtoul
 .text          0x000000000040ce12      0xcd3 fscanf.o
                0x000000000040d1f7                _doscan
                0x000000000040dab9                fscanf
 .text          0x000000000040dae5      0x145 fcntl.o
                0x000000000040dae5                fcntl
                0x000000000040db0f                openat
                0x000000000040db4a                open
                0x000000000040dbe6                creat
                0x000000000040dc0d                flock
 .text          0x000000000040dc2a      0x20b termios.o
                0x000000000040dc2a                tcgetpgrp
                0x000000000040dc57                tcsetpgrp
                0x000000000040dc7c                tcgetattr
                0x000000000040dc9a                tcsetattr
                0x000000000040dd0b                tcsendbreak
                0x000000000040dd15                tcdrain
                0x000000000040dd32                tcflush
                0x000000000040dd3c                tcflow
                0x000000000040dd46                cfmakeraw
                0x000000000040ddc0                cfgetispeed
                0x000000000040ddd8                cfgetospeed
                0x000000000040ddf0                cfsetispeed
                0x000000000040de07                cfsetospeed
                0x000000000040de1e                cfsetspeed
 .text          0x000000000040de35       0x52 ioctl.o
                0x000000000040de35                ioctl
 .text          0x000000000040de87       0x28 stubs.o
                0x000000000040de87                gramado_system_call
                0x000000000040e000                . = ALIGN (0x1000)
 *fill*         0x000000000040deaf      0x151 

.iplt           0x000000000040e000        0x0
 .iplt          0x000000000040e000        0x0 crt0.o

.rodata         0x000000000040e000     0x1b9b
 .rodata        0x000000000040e000       0x8a crt0.o
 *fill*         0x000000000040e08a        0x2 
 .rodata        0x000000000040e08c      0x5c2 c4.o
 *fill*         0x000000000040e64e       0x12 
 .rodata        0x000000000040e660      0x100 ctype.o
                0x000000000040e660                _ctype
 .rodata        0x000000000040e760      0x878 stdio.o
                0x000000000040eb40                hex2ascii_data
 .rodata        0x000000000040efd8      0x560 stdlib.o
 .rodata        0x000000000040f538       0x4b string.o
 *fill*         0x000000000040f583        0x1 
 .rodata        0x000000000040f584      0x1e5 api.o
 .rodata        0x000000000040f769      0x289 unistd.o
 *fill*         0x000000000040f9f2        0x2 
 .rodata        0x000000000040f9f4      0x154 fscanf.o
 .rodata        0x000000000040fb48       0x53 fcntl.o

.eh_frame       0x000000000040fb9c     0x363c
 .eh_frame      0x000000000040fb9c       0x34 crt0.o
 .eh_frame      0x000000000040fbd0       0xa4 c4.o
                                         0xbc (size before relaxing)
 .eh_frame      0x000000000040fc74      0xf54 stdio.o
                                        0xf6c (size before relaxing)
 .eh_frame      0x0000000000410bc8      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x0000000000411210      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x00000000004117d0       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x0000000000411810      0xb24 api.o
                                        0xb3c (size before relaxing)
 .eh_frame      0x0000000000412334      0x960 unistd.o
                                        0x978 (size before relaxing)
 .eh_frame      0x0000000000412c94      0x140 math.o
                                        0x158 (size before relaxing)
 .eh_frame      0x0000000000412dd4       0x40 strtol.o
                                         0x58 (size before relaxing)
 .eh_frame      0x0000000000412e14       0x50 strtoul.o
                                         0x68 (size before relaxing)
 .eh_frame      0x0000000000412e64       0xd0 fscanf.o
                                         0xe8 (size before relaxing)
 .eh_frame      0x0000000000412f34       0xa0 fcntl.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000412fd4      0x1c0 termios.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x0000000000413194       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x00000000004131b4       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x00000000004131d8        0x0
 .rel.got       0x00000000004131d8        0x0 crt0.o
 .rel.iplt      0x00000000004131d8        0x0 crt0.o
 .rel.text      0x00000000004131d8        0x0 crt0.o

.data           0x00000000004131e0      0xe20
                0x00000000004131e0                data = .
                0x00000000004131e0                _data = .
                0x00000000004131e0                __data = .
 *(.data)
 .data          0x00000000004131e0       0x50 crt0.o
 .data          0x0000000000413230        0x0 c4.o
 .data          0x0000000000413230        0x0 ctype.o
 .data          0x0000000000413230        0x0 stdio.o
 .data          0x0000000000413230        0x8 stdlib.o
                0x0000000000413230                _infinity
 .data          0x0000000000413238        0x0 string.o
 .data          0x0000000000413238        0x0 time.o
 *fill*         0x0000000000413238        0x8 
 .data          0x0000000000413240      0x440 api.o
 .data          0x0000000000413680        0x0 unistd.o
 .data          0x0000000000413680        0x0 math.o
 .data          0x0000000000413680        0x0 strtol.o
 .data          0x0000000000413680        0x0 strtoul.o
 .data          0x0000000000413680        0x0 fscanf.o
 .data          0x0000000000413680        0x0 fcntl.o
 .data          0x0000000000413680        0x0 termios.o
 .data          0x0000000000413680        0x0 ioctl.o
 .data          0x0000000000413680        0x0 stubs.o
                0x0000000000414000                . = ALIGN (0x1000)
 *fill*         0x0000000000413680      0x980 

.got            0x0000000000414000        0x0
 .got           0x0000000000414000        0x0 crt0.o

.got.plt        0x0000000000414000        0x0
 .got.plt       0x0000000000414000        0x0 crt0.o

.igot.plt       0x0000000000414000        0x0
 .igot.plt      0x0000000000414000        0x0 crt0.o

.bss            0x0000000000414000    0x126a4
                0x0000000000414000                bss = .
                0x0000000000414000                _bss = .
                0x0000000000414000                __bss = .
 *(.bss)
 .bss           0x0000000000414000        0x0 crt0.o
 .bss           0x0000000000414000        0x0 c4.o
 .bss           0x0000000000414000        0x0 ctype.o
 .bss           0x0000000000414000      0x421 stdio.o
 *fill*         0x0000000000414421       0x1f 
 .bss           0x0000000000414440     0x8000 stdlib.o
 .bss           0x000000000041c440        0x4 string.o
 .bss           0x000000000041c444        0x0 time.o
 *fill*         0x000000000041c444       0x1c 
 .bss           0x000000000041c460     0x8004 api.o
 *fill*         0x0000000000424464       0x1c 
 .bss           0x0000000000424480      0x11f unistd.o
                0x0000000000424480                errno
                0x0000000000424484                __execv_environ
 .bss           0x000000000042459f        0x0 math.o
 .bss           0x000000000042459f        0x0 strtol.o
 .bss           0x000000000042459f        0x0 strtoul.o
 *fill*         0x000000000042459f        0x1 
 .bss           0x00000000004245a0      0x300 fscanf.o
 .bss           0x00000000004248a0        0x0 fcntl.o
 .bss           0x00000000004248a0        0x0 termios.o
 .bss           0x00000000004248a0        0x0 ioctl.o
 .bss           0x00000000004248a0        0x0 stubs.o
                0x0000000000425000                . = ALIGN (0x1000)
 *fill*         0x00000000004248a0      0x760 
 COMMON         0x0000000000425000      0xd08 crt0.o
                0x0000000000425000                g_cursor_x
                0x0000000000425004                stdout
                0x0000000000425008                __libc_tty_id
                0x000000000042500c                g_char_attrib
                0x0000000000425010                g_rows
                0x0000000000425020                Streams
                0x00000000004250a0                g_using_gui
                0x00000000004250c0                prompt_out
                0x00000000004254c0                g_columns
                0x00000000004254c4                prompt_pos
                0x00000000004254c8                stdin
                0x00000000004254cc                prompt_status
                0x00000000004254e0                prompt_err
                0x00000000004258e0                stderr
                0x0000000000425900                prompt
                0x0000000000425d00                g_cursor_y
                0x0000000000425d04                prompt_max
 COMMON         0x0000000000425d08       0x34 c4.o
                0x0000000000425d08                p
                0x0000000000425d0c                lp
                0x0000000000425d10                tk
                0x0000000000425d14                le
                0x0000000000425d18                line
                0x0000000000425d1c                debug
                0x0000000000425d20                id
                0x0000000000425d24                loc
                0x0000000000425d28                ty
                0x0000000000425d2c                src
                0x0000000000425d30                e
                0x0000000000425d34                ival
                0x0000000000425d38                sym
 COMMON         0x0000000000425d3c        0x4 stdio.o
                0x0000000000425d3c                environ
 COMMON         0x0000000000425d40      0x878 stdlib.o
                0x0000000000425d40                mm_prev_pointer
                0x0000000000425d60                mmblockList
                0x0000000000426160                last_valid
                0x0000000000426180                heapList
                0x0000000000426580                libcHeap
                0x0000000000426584                randseed
                0x0000000000426588                heap_start
                0x000000000042658c                g_available_heap
                0x0000000000426590                g_heap_pointer
                0x0000000000426594                HEAP_SIZE
                0x0000000000426598                mmblockCount
                0x000000000042659c                last_size
                0x00000000004265a0                heap_end
                0x00000000004265a4                HEAP_END
                0x00000000004265a8                Heap
                0x00000000004265ac                current_mmblock
                0x00000000004265b0                heapCount
                0x00000000004265b4                HEAP_START
 COMMON         0x00000000004265b8       0x30 api.o
                0x00000000004265b8                CurrentWindow
                0x00000000004265bc                dialogbox_button2
                0x00000000004265c0                messagebox_button1
                0x00000000004265c4                ApplicationInfo
                0x00000000004265c8                BufferInfo
                0x00000000004265cc                dialogbox_button1
                0x00000000004265d0                first_responder
                0x00000000004265d4                CursorInfo
                0x00000000004265d8                __mb_current_button
                0x00000000004265dc                ClientAreaInfo
                0x00000000004265e0                messagebox_button2
                0x00000000004265e4                current_semaphore
 *fill*         0x00000000004265e8       0x18 
 COMMON         0x0000000000426600       0xa4 unistd.o
                0x0000000000426600                optarg
                0x0000000000426604                opterr
                0x0000000000426608                optind
                0x0000000000426620                __Hostname_buffer
                0x0000000000426660                __Login_buffer
                0x00000000004266a0                optopt
                0x00000000004266a4                end = .
                0x00000000004266a4                _end = .
                0x00000000004266a4                __end = .
LOAD crt0.o
LOAD c4.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
LOAD unistd.o
LOAD math.o
LOAD strtol.o
LOAD strtoul.o
LOAD fscanf.o
LOAD fcntl.o
LOAD termios.o
LOAD ioctl.o
LOAD stubs.o
OUTPUT(C4.BIN elf32-i386)

.comment        0x0000000000000000       0x29
 .comment       0x0000000000000000       0x29 crt0.o
                                         0x2a (size before relaxing)
 .comment       0x0000000000000029       0x2a c4.o
 .comment       0x0000000000000029       0x2a ctype.o
 .comment       0x0000000000000029       0x2a stdio.o
 .comment       0x0000000000000029       0x2a stdlib.o
 .comment       0x0000000000000029       0x2a string.o
 .comment       0x0000000000000029       0x2a time.o
 .comment       0x0000000000000029       0x2a api.o
 .comment       0x0000000000000029       0x2a unistd.o
 .comment       0x0000000000000029       0x2a math.o
 .comment       0x0000000000000029       0x2a strtol.o
 .comment       0x0000000000000029       0x2a strtoul.o
 .comment       0x0000000000000029       0x2a fscanf.o
 .comment       0x0000000000000029       0x2a fcntl.o
 .comment       0x0000000000000029       0x2a termios.o
 .comment       0x0000000000000029       0x2a ioctl.o
 .comment       0x0000000000000029       0x2a stubs.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 c4.o
 .note.GNU-stack
                0x0000000000000000        0x0 ctype.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdio.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdlib.o
 .note.GNU-stack
                0x0000000000000000        0x0 string.o
 .note.GNU-stack
                0x0000000000000000        0x0 time.o
 .note.GNU-stack
                0x0000000000000000        0x0 api.o
 .note.GNU-stack
                0x0000000000000000        0x0 unistd.o
 .note.GNU-stack
                0x0000000000000000        0x0 math.o
 .note.GNU-stack
                0x0000000000000000        0x0 strtol.o
 .note.GNU-stack
                0x0000000000000000        0x0 strtoul.o
 .note.GNU-stack
                0x0000000000000000        0x0 fscanf.o
 .note.GNU-stack
                0x0000000000000000        0x0 fcntl.o
 .note.GNU-stack
                0x0000000000000000        0x0 termios.o
 .note.GNU-stack
                0x0000000000000000        0x0 ioctl.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
