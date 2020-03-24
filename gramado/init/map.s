
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               main.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
__libc_tty_id       0x4               crt0.o
last_valid          0x4               stdlib.o
heapList            0x400             api.o
libcHeap            0x4               api.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
idleError           0x4               main.o
ServerStatus        0x4               main.o
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
environ             0x4               stdio.o
g_available_heap    0x4               api.o
g_heap_pointer      0x4               api.o
g_columns           0x4               crt0.o
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
idleStatus          0x4               main.o
g_cursor_y          0x4               crt0.o
__current_runlevel  0x4               main.o
ClientAreaInfo      0x4               main.o
messagebox_button2  0x4               api.o
Heap                0x4               api.o
current_semaphore   0x4               main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               api.o
HEAP_START          0x4               api.o

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
 .text          0x0000000000401000       0xf2 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010f2       0xe0 main.o
                0x00000000004010f2                enable_maskable_interrupts
                0x00000000004010fa                main
 .text          0x00000000004011d2     0x1a15 api.o
                0x00000000004011d2                system_call
                0x00000000004011fa                gde_system
                0x0000000000401204                gde_refresh_buffer
                0x00000000004012e0                gde_print_string
                0x00000000004012e6                gde_vsync
                0x00000000004012fe                gde_system_procedure
                0x0000000000401341                __gde_set_cursor
                0x000000000040135b                __gde_put_char
                0x0000000000401361                gde_load_bitmap_16x16
                0x000000000040137a                gde_shutdown
                0x0000000000401381                gde_init_background
                0x0000000000401387                gde_message_box
                0x000000000040168a                mbProcedure
                0x0000000000401847                gde_dialog_box
                0x0000000000401bf7                dbProcedure
                0x0000000000401c59                gde_create_window
                0x0000000000401cd2                gde_register_window
                0x0000000000401cfa                gde_close_window
                0x0000000000401d22                gde_set_focus
                0x0000000000401d4a                gde_get_focus
                0x0000000000401d5f                gde_kill_focus
                0x0000000000401d87                gde_set_active_window
                0x0000000000401daf                gde_get_active_window
                0x0000000000401dc4                gde_show_current_process_info
                0x0000000000401dda                gde_resize_window
                0x0000000000401df7                gde_redraw_window
                0x0000000000401e14                gde_replace_window
                0x0000000000401e2e                gde_maximize_window
                0x0000000000401e4d                gde_minimize_window
                0x0000000000401e6c                gde_update_window
                0x0000000000401e8e                gde_get_foregroung_window
                0x0000000000401ea4                gde_set_foregroung_window
                0x0000000000401ec0                gde_exit
                0x0000000000401edd                gde_kill
                0x0000000000401ee3                gde_dead_thread_collector
                0x0000000000401ef9                gde_strncmp
                0x0000000000401f5c                gde_show_backbuffer
                0x0000000000401f72                gde_reboot
                0x0000000000401f8b                gde_set_cursor
                0x0000000000401fa3                gde_get_cursor
                0x0000000000401fa9                gde_get_cursor_x
                0x0000000000401fc4                gde_get_cursor_y
                0x0000000000401fdf                gde_get_client_area_rect
                0x0000000000401ff7                gde_set_client_area_rect
                0x0000000000402016                gde_create_process
                0x000000000040202f                gde_create_thread
                0x0000000000402048                gde_start_thread
                0x0000000000402064                gde_fopen
                0x0000000000402090                gde_save_file
                0x00000000004020ea                gde_create_empty_file
                0x000000000040211b                gde_create_empty_directory
                0x000000000040214c                gde_down
                0x00000000004021a1                gde_up
                0x00000000004021f6                gde_enter_critical_section
                0x0000000000402231                gde_exit_critical_section
                0x000000000040224a                gde_p
                0x0000000000402250                gde_v
                0x0000000000402256                gde_initialize_critical_section
                0x000000000040226f                gde_begin_paint
                0x000000000040227a                gde_end_paint
                0x0000000000402285                gde_put_char
                0x00000000004022a1                gde_def_dialog
                0x00000000004022ab                gde_get_system_metrics
                0x00000000004022c9                gde_dialog
                0x000000000040235a                gde_getchar
                0x0000000000402375                gde_display_bmp
                0x000000000040277c                gde_send_message_to_process
                0x00000000004027bf                gde_send_message_to_thread
                0x0000000000402802                gde_send_message
                0x0000000000402838                gde_draw_text
                0x0000000000402877                gde_get_ws_screen_window
                0x000000000040288f                gde_get_ws_main_window
                0x00000000004028a7                gde_create_timer
                0x00000000004028c7                gde_get_systime_info
                0x00000000004028e8                gde_show_window
                0x0000000000402907                gde_start_terminal
                0x000000000040297b                gde_update_statusbar
                0x0000000000402999                gde_get_pid
                0x00000000004029c4                gde_get_screen_window
                0x00000000004029df                gde_get_background_window
                0x00000000004029fa                gde_get_main_window
                0x0000000000402a15                gde_getprocessname
                0x0000000000402a99                gde_getthreadname
                0x0000000000402b1d                gde_get_process_stats
                0x0000000000402b3b                gde_get_thread_stats
                0x0000000000402b59                gde_debug_print
                0x0000000000402b7b                gde_clone_and_execute
                0x0000000000402b98                gde_setup_net_buffer
                0x0000000000402bc6                execute_new_process
 .text          0x0000000000402be7        0x0 ctype.o
 .text          0x0000000000402be7     0x3fbd stdio.o
                0x0000000000402c2f                stdio_atoi
                0x0000000000402cf6                stdio_fntos
                0x0000000000402e1e                remove
                0x0000000000402e3b                _strout
                0x0000000000402eda                fflush
                0x0000000000402ef0                __fflush
                0x0000000000402fb2                __(bool, float, int, long, long)
                0x00000000004030c1                __getc
                0x0000000000403206                __putc
                0x00000000004032ab                getc
                0x00000000004032c1                putc
                0x00000000004032da                fgetc
                0x00000000004032f0                fputc
                0x0000000000403309                getchar
                0x0000000000403322                putchar
                0x000000000040333e                gets
                0x0000000000403380                puts
                0x00000000004033ba                fgets
                0x0000000000403415                fputs
                0x0000000000403449                getw
                0x000000000040348a                putw
                0x00000000004034bd                fclose
                0x0000000000403517                fopen
                0x0000000000403638                fopen2
                0x000000000040378f                scroll
                0x000000000040385c                clearerr
                0x000000000040387e                fread
                0x0000000000403926                fwrite
                0x00000000004039ce                prompt_putchar
                0x0000000000403a23                prompt_put_string
                0x0000000000403a50                prompt_strcat
                0x0000000000403a7d                prompt_flush
                0x0000000000403ae1                prompt_clean
                0x0000000000403ef8                printf3
                0x0000000000403f15                printf_atoi
                0x0000000000404005                printf_i2hex
                0x0000000000404067                printf2
                0x00000000004041ec                stdio_nextline
                0x000000000040422a                nlsprintf
                0x0000000000404268                sprintf
                0x00000000004042bd                libc_set_output_mode
                0x0000000000404302                outbyte
                0x00000000004044c0                _outbyte
                0x00000000004044ef                input
                0x0000000000404643                fprintf
                0x000000000040466d                nputs
                0x00000000004046a7                uclib_gets
                0x00000000004046d8                ungetc
                0x000000000040472a                ftell
                0x000000000040476b                fileno
                0x0000000000404785                linux_fgetc
                0x00000000004047c4                fgets2
                0x000000000040484f                fputs2
                0x000000000040489f                gets2
                0x000000000040492c                puts2
                0x0000000000404947                getchar2
                0x0000000000404975                feof
                0x000000000040498d                ferror
                0x00000000004049a5                fseek
                0x00000000004049c2                linux_fputc
                0x0000000000404a03                debug_print
                0x0000000000404a25                stdioSetCursor
                0x0000000000404a40                stdioGetCursorX
                0x0000000000404a5b                stdioGetCursorY
                0x0000000000404a76                scanf
                0x0000000000404c17                sscanf
                0x0000000000404dd6                kvprintf
                0x0000000000405c40                printf
                0x0000000000405c6e                printf_draw
                0x0000000000405cb6                vfprintf
                0x0000000000405d2e                vprintf
                0x0000000000405d5d                stdout_printf
                0x0000000000405d99                stderr_printf
                0x0000000000405ddc                perror
                0x0000000000405e03                rewind
                0x0000000000405e1d                snprintf
                0x0000000000405e31                stdio_initialize_standard_streams
                0x0000000000405e5c                libcStartTerminal
                0x0000000000405ed0                setbuf
                0x0000000000405ee9                setbuffer
                0x0000000000405f13                setlinebuf
                0x0000000000405f2c                setvbuf
                0x0000000000405ffc                filesize
                0x0000000000406045                fileread
                0x0000000000406093                dprintf
                0x00000000004060b0                vdprintf
                0x0000000000406353                Wirzenius_Torvalds_vsprintf
                0x000000000040672c                Torvalds_printf
                0x0000000000406773                vsnprintf
                0x0000000000406790                vscanf
                0x00000000004067ad                vsscanf
                0x00000000004067ca                vfscanf
                0x00000000004067f4                tmpfile
                0x0000000000406811                tmpnam
                0x000000000040682e                tmpnam_r
                0x000000000040684b                tempnam
                0x0000000000406868                stdio_make_file
                0x00000000004068e3                fdopen
                0x0000000000406909                freopen
                0x0000000000406933                open_memstream
                0x0000000000406950                open_wmemstream
                0x000000000040696d                fmemopen
                0x000000000040698a                fgetpos
                0x00000000004069c9                fsetpos
                0x00000000004069f4                fpurge
                0x0000000000406a1e                __fpurge
                0x0000000000406a3a                ctermid
                0x0000000000406a57                stdioInitialize
 .text          0x0000000000406ba4     0x1201 stdlib.o
                0x0000000000406bc1                rtGetHeapStart
                0x0000000000406bcb                rtGetHeapEnd
                0x0000000000406bd5                rtGetHeapPointer
                0x0000000000406bdf                rtGetAvailableHeap
                0x0000000000406be9                heapSetLibcHeap
                0x0000000000406c9c                heapAllocateMemory
                0x0000000000406ece                FreeHeap
                0x0000000000406ed8                heapInit
                0x000000000040706b                stdlibInitMM
                0x00000000004070ce                libcInitRT
                0x00000000004070f7                mktemp
                0x0000000000407101                rand
                0x000000000040711e                srand
                0x000000000040712c                xmalloc
                0x000000000040715e                stdlib_die
                0x0000000000407194                malloc
                0x00000000004071d0                realloc
                0x000000000040720d                free
                0x0000000000407213                calloc
                0x0000000000407259                zmalloc
                0x0000000000407295                system
                0x0000000000407659                stdlib_strncmp
                0x000000000040770f                v7_getenv
                0x000000000040774b                __findenv
                0x000000000040786e                getenv
                0x000000000040789b                setenv
                0x00000000004078a5                unsetenv
                0x00000000004078af                atoi
                0x0000000000407976                reverse
                0x00000000004079dd                itoa
                0x0000000000407a8b                abs
                0x0000000000407a9b                strtod
                0x0000000000407ccd                strtof
                0x0000000000407ce9                strtold
                0x0000000000407cfc                atof
                0x0000000000407d0e                labs
                0x0000000000407d1e                mkstemp
                0x0000000000407d28                mkostemp
                0x0000000000407d32                mkstemps
                0x0000000000407d3c                mkostemps
                0x0000000000407d46                ptsname
                0x0000000000407d50                ptsname_r
                0x0000000000407d5a                posix_openpt
                0x0000000000407d77                grantpt
                0x0000000000407d81                unlockpt
                0x0000000000407d8b                getpt
                0x0000000000407d95                getprogname
                0x0000000000407d9f                setprogname
 .text          0x0000000000407da5      0xccf string.o
                0x0000000000407dd0                strcoll
                0x0000000000407de9                memsetw
                0x0000000000407e15                memcmp
                0x0000000000407e7a                strdup
                0x0000000000407ecc                strndup
                0x0000000000407f2d                strnchr
                0x0000000000407f66                strrchr
                0x0000000000407fa1                strtoimax
                0x0000000000407fbe                strtoumax
                0x0000000000407fdb                strcasecmp
                0x0000000000408043                strncpy
                0x0000000000408099                strcmp
                0x0000000000408105                strncmp
                0x000000000040815f                memset
                0x00000000004081a6                memoryZeroMemory
                0x00000000004081cd                memcpy
                0x000000000040820a                strcpy
                0x000000000040823e                strlcpy
                0x000000000040829d                strcat
                0x00000000004082cc                strchrnul
                0x00000000004082f1                strlcat
                0x0000000000408383                strncat
                0x00000000004083e5                bcopy
                0x0000000000408411                bzero
                0x0000000000408431                strlen
                0x000000000040845f                strnlen
                0x000000000040849a                strpbrk
                0x00000000004084e8                strsep
                0x0000000000408566                strreplace
                0x00000000004085a1                strcspn
                0x0000000000408640                strspn
                0x00000000004086df                strtok_r
                0x00000000004087c6                strtok
                0x00000000004087de                strchr
                0x000000000040880a                memmove
                0x000000000040888b                memscan
                0x00000000004088bf                strstr
                0x000000000040891f                index
                0x000000000040894c                rindex
                0x000000000040895f                strxfrm
                0x00000000004089b1                strerror
                0x00000000004089ce                strerror_r
                0x0000000000408a17                strsignal
                0x0000000000408a34                strtoupper
 .text          0x0000000000408a74       0x89 conio.o
                0x0000000000408a74                putch
                0x0000000000408a98                cputs
                0x0000000000408acd                getch
                0x0000000000408ae5                getche
 .text          0x0000000000408afd      0xb4c unistd.o
                0x0000000000408afd                execv
                0x0000000000408b1b                execve
                0x0000000000408b56                read_ttyList
                0x0000000000408b84                write_ttyList
                0x0000000000408bb2                read_tty
                0x0000000000408be0                write_tty
                0x0000000000408c0e                read_VC
                0x0000000000408c3c                write_VC
                0x0000000000408c6a                read
                0x0000000000408c95                write
                0x0000000000408cc0                exit
                0x0000000000408ce0                fork
                0x0000000000408d12                setuid
                0x0000000000408d2d                getuid
                0x0000000000408d48                geteuid
                0x0000000000408d65                getpid
                0x0000000000408d7d                getppid
                0x0000000000408d95                getgid
                0x0000000000408db0                dup
                0x0000000000408dca                dup2
                0x0000000000408de6                dup3
                0x0000000000408e04                getpriority
                0x0000000000408e21                setpriority
                0x0000000000408e3e                nice
                0x0000000000408e5b                pause
                0x0000000000408e78                mkdir
                0x0000000000408e9c                rmdir
                0x0000000000408eb9                link
                0x0000000000408ed6                unlink
                0x0000000000408ef3                mlock
                0x0000000000408f10                munlock
                0x0000000000408f2d                mlockall
                0x0000000000408f4a                munlockall
                0x0000000000408f67                sysconf
                0x0000000000408f84                fsync
                0x0000000000408fa1                fdatasync
                0x0000000000408fbe                sync
                0x0000000000408fd7                syncfs
                0x0000000000408ff4                close
                0x0000000000409012                pipe2
                0x0000000000409031                pipe
                0x0000000000409049                fpathconf
                0x0000000000409066                pathconf
                0x0000000000409083                __gethostname
                0x00000000004090af                gethostname
                0x00000000004090da                sethostname
                0x00000000004090f8                getlogin
                0x0000000000409124                setlogin
                0x000000000040914a                getusername
                0x00000000004091c4                setusername
                0x0000000000409238                ttyname
                0x000000000040927c                ttyname_r
                0x0000000000409299                isatty
                0x00000000004092bc                getopt
                0x00000000004092d9                alarm
                0x00000000004092f6                brk
                0x0000000000409313                execvp
                0x0000000000409330                execvpe
                0x000000000040934d                chown
                0x000000000040936a                fchown
                0x0000000000409387                lchown
                0x00000000004093a4                chdir
                0x00000000004093c1                fchdir
                0x00000000004093de                sleep
                0x00000000004093fb                _exit
                0x0000000000409411                swab_w
                0x0000000000409450                swab
                0x0000000000409467                lseek
                0x0000000000409484                tell
                0x000000000040949e                access
                0x00000000004094bb                uname
                0x00000000004094e8                eq
                0x0000000000409534                getlin
                0x00000000004095c5                compar
                0x0000000000409621                xxx_todo_int133
 .text          0x0000000000409649      0x20b termios.o
                0x0000000000409649                tcgetpgrp
                0x0000000000409676                tcsetpgrp
                0x000000000040969b                tcgetattr
                0x00000000004096b9                tcsetattr
                0x000000000040972a                tcsendbreak
                0x0000000000409734                tcdrain
                0x0000000000409751                tcflush
                0x000000000040975b                tcflow
                0x0000000000409765                cfmakeraw
                0x00000000004097df                cfgetispeed
                0x00000000004097f7                cfgetospeed
                0x000000000040980f                cfsetispeed
                0x0000000000409826                cfsetospeed
                0x000000000040983d                cfsetspeed
 .text          0x0000000000409854       0x52 ioctl.o
                0x0000000000409854                ioctl
 .text          0x00000000004098a6      0x145 fcntl.o
                0x00000000004098a6                fcntl
                0x00000000004098d0                openat
                0x000000000040990b                open
                0x00000000004099a7                creat
                0x00000000004099ce                flock
 .text          0x00000000004099eb       0x28 stubs.o
                0x00000000004099eb                gramado_system_call
                0x000000000040a000                . = ALIGN (0x1000)
 *fill*         0x0000000000409a13      0x5ed 

.iplt           0x000000000040a000        0x0
 .iplt          0x000000000040a000        0x0 crt0.o

.rodata         0x000000000040a000     0x1527
 .rodata        0x000000000040a000       0x8a crt0.o
 *fill*         0x000000000040a08a        0x2 
 .rodata        0x000000000040a08c       0x8f main.o
 *fill*         0x000000000040a11b        0x1 
 .rodata        0x000000000040a11c      0x1e5 api.o
 *fill*         0x000000000040a301       0x1f 
 .rodata        0x000000000040a320      0x100 ctype.o
                0x000000000040a320                _ctype
 .rodata        0x000000000040a420      0x878 stdio.o
                0x000000000040a800                hex2ascii_data
 .rodata        0x000000000040ac98      0x560 stdlib.o
 .rodata        0x000000000040b1f8       0x4b string.o
 .rodata        0x000000000040b243        0x6 conio.o
 .rodata        0x000000000040b249      0x289 unistd.o
 *fill*         0x000000000040b4d2        0x2 
 .rodata        0x000000000040b4d4       0x53 fcntl.o

.eh_frame       0x000000000040b528     0x339c
 .eh_frame      0x000000000040b528       0x34 crt0.o
 .eh_frame      0x000000000040b55c       0x44 main.o
                                         0x5c (size before relaxing)
 .eh_frame      0x000000000040b5a0      0xb24 api.o
                                        0xb3c (size before relaxing)
 .eh_frame      0x000000000040c0c4      0xf54 stdio.o
                                        0xf6c (size before relaxing)
 .eh_frame      0x000000000040d018      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x000000000040d660      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040dc20       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040dcc0      0x960 unistd.o
                                        0x978 (size before relaxing)
 .eh_frame      0x000000000040e620      0x1c0 termios.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x000000000040e7e0       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040e800       0xa0 fcntl.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040e8a0       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040e8c4        0x0
 .rel.got       0x000000000040e8c4        0x0 crt0.o
 .rel.iplt      0x000000000040e8c4        0x0 crt0.o
 .rel.text      0x000000000040e8c4        0x0 crt0.o

.data           0x000000000040e8e0     0x1720
                0x000000000040e8e0                data = .
                0x000000000040e8e0                _data = .
                0x000000000040e8e0                __data = .
 *(.data)
 .data          0x000000000040e8e0       0x50 crt0.o
 *fill*         0x000000000040e930       0x10 
 .data          0x000000000040e940      0x440 main.o
 .data          0x000000000040ed80      0x440 api.o
 .data          0x000000000040f1c0        0x0 ctype.o
 .data          0x000000000040f1c0        0x0 stdio.o
 .data          0x000000000040f1c0        0x8 stdlib.o
                0x000000000040f1c0                _infinity
 .data          0x000000000040f1c8        0x0 string.o
 .data          0x000000000040f1c8        0x0 conio.o
 .data          0x000000000040f1c8        0x0 unistd.o
 .data          0x000000000040f1c8        0x0 termios.o
 .data          0x000000000040f1c8        0x0 ioctl.o
 .data          0x000000000040f1c8        0x0 fcntl.o
 .data          0x000000000040f1c8        0x0 stubs.o
                0x0000000000410000                . = ALIGN (0x1000)
 *fill*         0x000000000040f1c8      0xe38 

.got            0x0000000000410000        0x0
 .got           0x0000000000410000        0x0 crt0.o

.got.plt        0x0000000000410000        0x0
 .got.plt       0x0000000000410000        0x0 crt0.o

.igot.plt       0x0000000000410000        0x0
 .igot.plt      0x0000000000410000        0x0 crt0.o

.bss            0x0000000000410000    0x12684
                0x0000000000410000                bss = .
                0x0000000000410000                _bss = .
                0x0000000000410000                __bss = .
 *(.bss)
 .bss           0x0000000000410000        0x0 crt0.o
 .bss           0x0000000000410000        0x0 main.o
 .bss           0x0000000000410000     0x8004 api.o
 .bss           0x0000000000418004        0x0 ctype.o
 *fill*         0x0000000000418004       0x1c 
 .bss           0x0000000000418020      0x421 stdio.o
 *fill*         0x0000000000418441       0x1f 
 .bss           0x0000000000418460     0x8000 stdlib.o
 .bss           0x0000000000420460        0x4 string.o
 .bss           0x0000000000420464        0x0 conio.o
 *fill*         0x0000000000420464       0x1c 
 .bss           0x0000000000420480      0x11f unistd.o
                0x0000000000420480                errno
                0x0000000000420484                __execv_environ
 .bss           0x000000000042059f        0x0 termios.o
 .bss           0x000000000042059f        0x0 ioctl.o
 .bss           0x000000000042059f        0x0 fcntl.o
 .bss           0x000000000042059f        0x0 stubs.o
                0x0000000000421000                . = ALIGN (0x1000)
 *fill*         0x000000000042059f      0xa61 
 COMMON         0x0000000000421000      0xd08 crt0.o
                0x0000000000421000                g_cursor_x
                0x0000000000421004                stdout
                0x0000000000421008                __libc_tty_id
                0x000000000042100c                g_char_attrib
                0x0000000000421010                g_rows
                0x0000000000421020                Streams
                0x00000000004210a0                g_using_gui
                0x00000000004210c0                prompt_out
                0x00000000004214c0                g_columns
                0x00000000004214c4                prompt_pos
                0x00000000004214c8                stdin
                0x00000000004214cc                prompt_status
                0x00000000004214e0                prompt_err
                0x00000000004218e0                stderr
                0x0000000000421900                prompt
                0x0000000000421d00                g_cursor_y
                0x0000000000421d04                prompt_max
 COMMON         0x0000000000421d08       0x28 main.o
                0x0000000000421d08                CurrentWindow
                0x0000000000421d0c                idleError
                0x0000000000421d10                ServerStatus
                0x0000000000421d14                ApplicationInfo
                0x0000000000421d18                BufferInfo
                0x0000000000421d1c                CursorInfo
                0x0000000000421d20                idleStatus
                0x0000000000421d24                __current_runlevel
                0x0000000000421d28                ClientAreaInfo
                0x0000000000421d2c                current_semaphore
 *fill*         0x0000000000421d30       0x10 
 COMMON         0x0000000000421d40      0x440 api.o
                0x0000000000421d40                heapList
                0x0000000000422140                libcHeap
                0x0000000000422144                dialogbox_button2
                0x0000000000422148                messagebox_button1
                0x000000000042214c                heap_start
                0x0000000000422150                g_available_heap
                0x0000000000422154                g_heap_pointer
                0x0000000000422158                HEAP_SIZE
                0x000000000042215c                dialogbox_button1
                0x0000000000422160                first_responder
                0x0000000000422164                heap_end
                0x0000000000422168                __mb_current_button
                0x000000000042216c                HEAP_END
                0x0000000000422170                messagebox_button2
                0x0000000000422174                Heap
                0x0000000000422178                heapCount
                0x000000000042217c                HEAP_START
 COMMON         0x0000000000422180        0x4 stdio.o
                0x0000000000422180                environ
 *fill*         0x0000000000422184       0x1c 
 COMMON         0x00000000004221a0      0x434 stdlib.o
                0x00000000004221a0                mm_prev_pointer
                0x00000000004221c0                mmblockList
                0x00000000004225c0                last_valid
                0x00000000004225c4                randseed
                0x00000000004225c8                mmblockCount
                0x00000000004225cc                last_size
                0x00000000004225d0                current_mmblock
 *fill*         0x00000000004225d4        0xc 
 COMMON         0x00000000004225e0       0xa4 unistd.o
                0x00000000004225e0                optarg
                0x00000000004225e4                opterr
                0x00000000004225e8                optind
                0x0000000000422600                __Hostname_buffer
                0x0000000000422640                __Login_buffer
                0x0000000000422680                optopt
                0x0000000000422684                end = .
                0x0000000000422684                _end = .
                0x0000000000422684                __end = .
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
LOAD fcntl.o
LOAD stubs.o
OUTPUT(INIT.BIN elf32-i386)

.comment        0x0000000000000000       0x29
 .comment       0x0000000000000000       0x29 crt0.o
                                         0x2a (size before relaxing)
 .comment       0x0000000000000029       0x2a main.o
 .comment       0x0000000000000029       0x2a api.o
 .comment       0x0000000000000029       0x2a ctype.o
 .comment       0x0000000000000029       0x2a stdio.o
 .comment       0x0000000000000029       0x2a stdlib.o
 .comment       0x0000000000000029       0x2a string.o
 .comment       0x0000000000000029       0x2a conio.o
 .comment       0x0000000000000029       0x2a unistd.o
 .comment       0x0000000000000029       0x2a termios.o
 .comment       0x0000000000000029       0x2a ioctl.o
 .comment       0x0000000000000029       0x2a fcntl.o
 .comment       0x0000000000000029       0x2a stubs.o

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
                0x0000000000000000        0x0 fcntl.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
