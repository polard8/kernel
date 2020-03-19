
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
 .text          0x0000000000402be7     0x3e19 stdio.o
                0x0000000000402c2f                stdio_atoi
                0x0000000000402cf6                stdio_fntos
                0x0000000000402e1e                remove
                0x0000000000402e28                fclose
                0x0000000000402e82                fopen
                0x0000000000402fa3                fopen2
                0x00000000004030fa                scroll
                0x00000000004031c7                clearerr
                0x00000000004031e9                fread
                0x0000000000403291                fwrite
                0x0000000000403339                prompt_putchar
                0x0000000000403389                prompt_put_string
                0x00000000004033b6                prompt_strcat
                0x00000000004033e3                prompt_flush
                0x0000000000403447                prompt_clean
                0x0000000000403857                printf3
                0x0000000000403874                printf_atoi
                0x0000000000403964                printf_i2hex
                0x00000000004039c6                printf2
                0x0000000000403b4b                stdio_nextline
                0x0000000000403b89                nlsprintf
                0x0000000000403bc7                sprintf
                0x0000000000403c1c                libc_set_output_mode
                0x0000000000403c61                outbyte
                0x0000000000403e1f                _outbyte
                0x0000000000403e4e                input
                0x0000000000403fa2                fprintf
                0x0000000000403fcc                nputs
                0x0000000000404006                __gets
                0x0000000000404037                ungetc
                0x0000000000404089                ftell
                0x00000000004040ca                fileno
                0x00000000004040e4                __linux_fgetc
                0x000000000040411f                fflush
                0x0000000000404135                __fflush
                0x00000000004041f7                __(bool, float, int, long, long)
                0x0000000000404306                __getc
                0x000000000040444b                __putc
                0x00000000004044f0                getc
                0x0000000000404506                putc
                0x000000000040451f                fgetc
                0x0000000000404535                fputc
                0x000000000040454e                getchar
                0x0000000000404567                putchar
                0x0000000000404583                gets
                0x00000000004045c5                puts
                0x00000000004045ff                fgets
                0x000000000040465a                fputs
                0x000000000040468e                getw
                0x00000000004046cf                putw
                0x00000000004046fe                fgets2
                0x0000000000404782                fputs2
                0x00000000004047d2                gets2
                0x0000000000404858                puts2
                0x0000000000404873                getchar2
                0x00000000004048a1                feof
                0x00000000004048b9                ferror
                0x00000000004048d1                fseek
                0x00000000004048ee                __linux_fputc
                0x000000000040492f                __gramado__putc
                0x00000000004049da                debug_print
                0x00000000004049fc                __serenity_fputc
                0x0000000000404a15                stdioSetCursor
                0x0000000000404a30                stdioGetCursorX
                0x0000000000404a4b                stdioGetCursorY
                0x0000000000404a66                scanf
                0x0000000000404c00                sscanf
                0x0000000000404dbf                kvprintf
                0x0000000000405c29                printf
                0x0000000000405c57                printf_draw
                0x0000000000405c9f                vfprintf
                0x0000000000405d17                vprintf
                0x0000000000405d46                stdout_printf
                0x0000000000405d82                stderr_printf
                0x0000000000405dbe                perror
                0x0000000000405de5                rewind
                0x0000000000405dff                snprintf
                0x0000000000405e13                stdio_initialize_standard_streams
                0x0000000000405e3e                libcStartTerminal
                0x0000000000405eb2                setbuf
                0x0000000000405eb8                setbuffer
                0x0000000000405ee2                setlinebuf
                0x0000000000405ee8                setvbuf
                0x0000000000405f9d                filesize
                0x0000000000405fe6                fileread
                0x0000000000406034                dprintf
                0x000000000040603e                vdprintf
                0x00000000004062c7                Wirzenius_Torvalds_vsprintf
                0x00000000004066a0                Torvalds_printf
                0x00000000004066e0                vsnprintf
                0x00000000004066ea                vscanf
                0x00000000004066f4                vsscanf
                0x00000000004066fe                vfscanf
                0x0000000000406715                tmpfile
                0x000000000040671f                tmpnam
                0x0000000000406729                tmpnam_r
                0x0000000000406733                tempnam
                0x000000000040673d                stdio_make_file
                0x00000000004067b8                fdopen
                0x00000000004067de                freopen
                0x0000000000406808                open_memstream
                0x0000000000406812                open_wmemstream
                0x000000000040681c                fmemopen
                0x0000000000406826                fgetpos
                0x0000000000406865                fsetpos
                0x0000000000406890                fpurge
                0x00000000004068a7                __fpurge
                0x00000000004068b0                ctermid
                0x00000000004068ba                stdioInitialize
 .text          0x0000000000406a00     0x1201 stdlib.o
                0x0000000000406a1d                rtGetHeapStart
                0x0000000000406a27                rtGetHeapEnd
                0x0000000000406a31                rtGetHeapPointer
                0x0000000000406a3b                rtGetAvailableHeap
                0x0000000000406a45                heapSetLibcHeap
                0x0000000000406af8                heapAllocateMemory
                0x0000000000406d2a                FreeHeap
                0x0000000000406d34                heapInit
                0x0000000000406ec7                stdlibInitMM
                0x0000000000406f2a                libcInitRT
                0x0000000000406f53                mktemp
                0x0000000000406f5d                rand
                0x0000000000406f7a                srand
                0x0000000000406f88                xmalloc
                0x0000000000406fba                stdlib_die
                0x0000000000406ff0                malloc
                0x000000000040702c                realloc
                0x0000000000407069                free
                0x000000000040706f                calloc
                0x00000000004070b5                zmalloc
                0x00000000004070f1                system
                0x00000000004074b5                stdlib_strncmp
                0x000000000040756b                v7_getenv
                0x00000000004075a7                __findenv
                0x00000000004076ca                getenv
                0x00000000004076f7                setenv
                0x0000000000407701                unsetenv
                0x000000000040770b                atoi
                0x00000000004077d2                reverse
                0x0000000000407839                itoa
                0x00000000004078e7                abs
                0x00000000004078f7                strtod
                0x0000000000407b29                strtof
                0x0000000000407b45                strtold
                0x0000000000407b58                atof
                0x0000000000407b6a                labs
                0x0000000000407b7a                mkstemp
                0x0000000000407b84                mkostemp
                0x0000000000407b8e                mkstemps
                0x0000000000407b98                mkostemps
                0x0000000000407ba2                ptsname
                0x0000000000407bac                ptsname_r
                0x0000000000407bb6                posix_openpt
                0x0000000000407bd3                grantpt
                0x0000000000407bdd                unlockpt
                0x0000000000407be7                getpt
                0x0000000000407bf1                getprogname
                0x0000000000407bfb                setprogname
 .text          0x0000000000407c01      0xc44 string.o
                0x0000000000407c2c                strcoll
                0x0000000000407c45                memsetw
                0x0000000000407c71                memcmp
                0x0000000000407cd6                strdup
                0x0000000000407d28                strndup
                0x0000000000407d89                strnchr
                0x0000000000407dc2                strrchr
                0x0000000000407dfd                strtoimax
                0x0000000000407e07                strtoumax
                0x0000000000407e11                strcasecmp
                0x0000000000407e79                strncpy
                0x0000000000407ecf                strcmp
                0x0000000000407f3b                strncmp
                0x0000000000407f95                memset
                0x0000000000407fdc                memoryZeroMemory
                0x0000000000408003                memcpy
                0x0000000000408040                strcpy
                0x0000000000408074                strlcpy
                0x00000000004080d3                strcat
                0x0000000000408102                strchrnul
                0x0000000000408127                strlcat
                0x00000000004081b9                strncat
                0x000000000040821b                bcopy
                0x0000000000408247                bzero
                0x0000000000408267                strlen
                0x0000000000408295                strnlen
                0x00000000004082d0                strpbrk
                0x000000000040831e                strsep
                0x000000000040839c                strreplace
                0x00000000004083d7                strcspn
                0x0000000000408476                strspn
                0x0000000000408515                strtok_r
                0x00000000004085fc                strtok
                0x0000000000408614                strchr
                0x0000000000408640                memmove
                0x00000000004086c1                memscan
                0x00000000004086f5                strstr
                0x0000000000408755                index
                0x0000000000408782                rindex
                0x0000000000408795                strxfrm
                0x00000000004087e7                strerror
                0x00000000004087f1                strerror_r
                0x00000000004087fb                strsignal
                0x0000000000408805                strtoupper
 .text          0x0000000000408845       0x89 conio.o
                0x0000000000408845                putch
                0x0000000000408869                cputs
                0x000000000040889e                getch
                0x00000000004088b6                getche
 .text          0x00000000004088ce      0x879 unistd.o
                0x00000000004088ce                execv
                0x00000000004088ec                execve
                0x0000000000408927                read_ttyList
                0x0000000000408955                write_ttyList
                0x0000000000408983                read_tty
                0x00000000004089b1                write_tty
                0x00000000004089df                read_VC
                0x0000000000408a0d                write_VC
                0x0000000000408a3b                read
                0x0000000000408a66                write
                0x0000000000408a91                exit
                0x0000000000408ab1                fork
                0x0000000000408ae3                setuid
                0x0000000000408afe                getuid
                0x0000000000408b19                geteuid
                0x0000000000408b23                getpid
                0x0000000000408b3b                getppid
                0x0000000000408b53                getgid
                0x0000000000408b6e                dup
                0x0000000000408b88                dup2
                0x0000000000408ba4                dup3
                0x0000000000408bc2                getpriority
                0x0000000000408bcc                setpriority
                0x0000000000408bd6                nice
                0x0000000000408be0                pause
                0x0000000000408bea                mkdir
                0x0000000000408bfe                rmdir
                0x0000000000408c08                link
                0x0000000000408c12                unlink
                0x0000000000408c1c                mlock
                0x0000000000408c26                munlock
                0x0000000000408c30                mlockall
                0x0000000000408c3a                munlockall
                0x0000000000408c44                sysconf
                0x0000000000408c4e                fsync
                0x0000000000408c58                fdatasync
                0x0000000000408c62                sync
                0x0000000000408c68                syncfs
                0x0000000000408c72                close
                0x0000000000408c90                pipe
                0x0000000000408cb1                fpathconf
                0x0000000000408cbb                pathconf
                0x0000000000408cc5                __gethostname
                0x0000000000408cf1                gethostname
                0x0000000000408d1c                sethostname
                0x0000000000408d3a                getlogin
                0x0000000000408d66                setlogin
                0x0000000000408d8c                getusername
                0x0000000000408e06                setusername
                0x0000000000408e7a                ttyname
                0x0000000000408eb7                ttyname_r
                0x0000000000408ec1                isatty
                0x0000000000408ee4                getopt
                0x0000000000408eee                alarm
                0x0000000000408ef8                brk
                0x0000000000408f02                execvp
                0x0000000000408f0c                execvpe
                0x0000000000408f16                chown
                0x0000000000408f20                fchown
                0x0000000000408f2a                lchown
                0x0000000000408f34                chdir
                0x0000000000408f3e                fchdir
                0x0000000000408f48                sleep
                0x0000000000408f52                _exit
                0x0000000000408f68                swab_w
                0x0000000000408fa7                swab
                0x0000000000408fbe                lseek
                0x0000000000408fc8                tell
                0x0000000000408fdc                access
                0x0000000000408fe6                eq
                0x0000000000409032                getlin
                0x00000000004090c3                compar
                0x000000000040911f                xxx_todo_int133
 .text          0x0000000000409147      0x20b termios.o
                0x0000000000409147                tcgetpgrp
                0x0000000000409174                tcsetpgrp
                0x0000000000409199                tcgetattr
                0x00000000004091b7                tcsetattr
                0x0000000000409228                tcsendbreak
                0x0000000000409232                tcdrain
                0x000000000040924f                tcflush
                0x0000000000409259                tcflow
                0x0000000000409263                cfmakeraw
                0x00000000004092dd                cfgetispeed
                0x00000000004092f5                cfgetospeed
                0x000000000040930d                cfsetispeed
                0x0000000000409324                cfsetospeed
                0x000000000040933b                cfsetspeed
 .text          0x0000000000409352       0x52 ioctl.o
                0x0000000000409352                ioctl
 .text          0x00000000004093a4      0x11f fcntl.o
                0x00000000004093a4                fcntl
                0x00000000004093bb                openat
                0x00000000004093f6                open
                0x0000000000409492                creat
                0x00000000004094b9                flock
 .text          0x00000000004094c3       0x28 stubs.o
                0x00000000004094c3                gramado_system_call
                0x000000000040a000                . = ALIGN (0x1000)
 *fill*         0x00000000004094eb      0xb15 

.iplt           0x000000000040a000        0x0
 .iplt          0x000000000040a000        0x0 crt0.o

.rodata         0x000000000040a000     0x1144
 .rodata        0x000000000040a000       0x8a crt0.o
 *fill*         0x000000000040a08a        0x2 
 .rodata        0x000000000040a08c       0x8f main.o
 *fill*         0x000000000040a11b        0x1 
 .rodata        0x000000000040a11c      0x1e5 api.o
 *fill*         0x000000000040a301       0x1f 
 .rodata        0x000000000040a320      0x100 ctype.o
                0x000000000040a320                _ctype
 .rodata        0x000000000040a420      0x731 stdio.o
                0x000000000040a800                hex2ascii_data
 *fill*         0x000000000040ab51        0x7 
 .rodata        0x000000000040ab58      0x560 stdlib.o
 .rodata        0x000000000040b0b8        0x6 conio.o
 .rodata        0x000000000040b0be       0x4f unistd.o
 *fill*         0x000000000040b10d        0x3 
 .rodata        0x000000000040b110       0x34 fcntl.o

.eh_frame       0x000000000040b144     0x337c
 .eh_frame      0x000000000040b144       0x34 crt0.o
 .eh_frame      0x000000000040b178       0x44 main.o
                                         0x5c (size before relaxing)
 .eh_frame      0x000000000040b1bc      0xb24 api.o
                                        0xb3c (size before relaxing)
 .eh_frame      0x000000000040bce0      0xf74 stdio.o
                                        0xf8c (size before relaxing)
 .eh_frame      0x000000000040cc54      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x000000000040d29c      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040d85c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040d8fc      0x920 unistd.o
                                        0x938 (size before relaxing)
 .eh_frame      0x000000000040e21c      0x1c0 termios.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x000000000040e3dc       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040e3fc       0xa0 fcntl.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040e49c       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040e4c0        0x0
 .rel.got       0x000000000040e4c0        0x0 crt0.o
 .rel.iplt      0x000000000040e4c0        0x0 crt0.o
 .rel.text      0x000000000040e4c0        0x0 crt0.o

.data           0x000000000040e4c0      0xb40
                0x000000000040e4c0                data = .
                0x000000000040e4c0                _data = .
                0x000000000040e4c0                __data = .
 *(.data)
 .data          0x000000000040e4c0       0x50 crt0.o
 *fill*         0x000000000040e510       0x10 
 .data          0x000000000040e520      0x440 main.o
 .data          0x000000000040e960      0x440 api.o
 .data          0x000000000040eda0        0x0 ctype.o
 .data          0x000000000040eda0        0x0 stdio.o
 .data          0x000000000040eda0        0x8 stdlib.o
                0x000000000040eda0                _infinity
 .data          0x000000000040eda8        0x0 string.o
 .data          0x000000000040eda8        0x0 conio.o
 .data          0x000000000040eda8        0x0 unistd.o
 .data          0x000000000040eda8        0x0 termios.o
 .data          0x000000000040eda8        0x0 ioctl.o
 .data          0x000000000040eda8        0x0 fcntl.o
 .data          0x000000000040eda8        0x0 stubs.o
                0x000000000040f000                . = ALIGN (0x1000)
 *fill*         0x000000000040eda8      0x258 

.got            0x000000000040f000        0x0
 .got           0x000000000040f000        0x0 crt0.o

.got.plt        0x000000000040f000        0x0
 .got.plt       0x000000000040f000        0x0 crt0.o

.igot.plt       0x000000000040f000        0x0
 .igot.plt      0x000000000040f000        0x0 crt0.o

.bss            0x000000000040f000    0x12684
                0x000000000040f000                bss = .
                0x000000000040f000                _bss = .
                0x000000000040f000                __bss = .
 *(.bss)
 .bss           0x000000000040f000        0x0 crt0.o
 .bss           0x000000000040f000        0x0 main.o
 .bss           0x000000000040f000     0x8004 api.o
 .bss           0x0000000000417004        0x0 ctype.o
 *fill*         0x0000000000417004       0x1c 
 .bss           0x0000000000417020      0x421 stdio.o
 *fill*         0x0000000000417441       0x1f 
 .bss           0x0000000000417460     0x8000 stdlib.o
 .bss           0x000000000041f460        0x4 string.o
 .bss           0x000000000041f464        0x0 conio.o
 *fill*         0x000000000041f464       0x1c 
 .bss           0x000000000041f480      0x11f unistd.o
                0x000000000041f480                errno
                0x000000000041f484                __execv_environ
 .bss           0x000000000041f59f        0x0 termios.o
 .bss           0x000000000041f59f        0x0 ioctl.o
 .bss           0x000000000041f59f        0x0 fcntl.o
 .bss           0x000000000041f59f        0x0 stubs.o
                0x0000000000420000                . = ALIGN (0x1000)
 *fill*         0x000000000041f59f      0xa61 
 COMMON         0x0000000000420000      0xd08 crt0.o
                0x0000000000420000                g_cursor_x
                0x0000000000420004                stdout
                0x0000000000420008                __libc_tty_id
                0x000000000042000c                g_char_attrib
                0x0000000000420010                g_rows
                0x0000000000420020                Streams
                0x00000000004200a0                g_using_gui
                0x00000000004200c0                prompt_out
                0x00000000004204c0                g_columns
                0x00000000004204c4                prompt_pos
                0x00000000004204c8                stdin
                0x00000000004204cc                prompt_status
                0x00000000004204e0                prompt_err
                0x00000000004208e0                stderr
                0x0000000000420900                prompt
                0x0000000000420d00                g_cursor_y
                0x0000000000420d04                prompt_max
 COMMON         0x0000000000420d08       0x28 main.o
                0x0000000000420d08                CurrentWindow
                0x0000000000420d0c                idleError
                0x0000000000420d10                ServerStatus
                0x0000000000420d14                ApplicationInfo
                0x0000000000420d18                BufferInfo
                0x0000000000420d1c                CursorInfo
                0x0000000000420d20                idleStatus
                0x0000000000420d24                __current_runlevel
                0x0000000000420d28                ClientAreaInfo
                0x0000000000420d2c                current_semaphore
 *fill*         0x0000000000420d30       0x10 
 COMMON         0x0000000000420d40      0x440 api.o
                0x0000000000420d40                heapList
                0x0000000000421140                libcHeap
                0x0000000000421144                dialogbox_button2
                0x0000000000421148                messagebox_button1
                0x000000000042114c                heap_start
                0x0000000000421150                g_available_heap
                0x0000000000421154                g_heap_pointer
                0x0000000000421158                HEAP_SIZE
                0x000000000042115c                dialogbox_button1
                0x0000000000421160                first_responder
                0x0000000000421164                heap_end
                0x0000000000421168                __mb_current_button
                0x000000000042116c                HEAP_END
                0x0000000000421170                messagebox_button2
                0x0000000000421174                Heap
                0x0000000000421178                heapCount
                0x000000000042117c                HEAP_START
 COMMON         0x0000000000421180        0x4 stdio.o
                0x0000000000421180                environ
 *fill*         0x0000000000421184       0x1c 
 COMMON         0x00000000004211a0      0x434 stdlib.o
                0x00000000004211a0                mm_prev_pointer
                0x00000000004211c0                mmblockList
                0x00000000004215c0                last_valid
                0x00000000004215c4                randseed
                0x00000000004215c8                mmblockCount
                0x00000000004215cc                last_size
                0x00000000004215d0                current_mmblock
 *fill*         0x00000000004215d4        0xc 
 COMMON         0x00000000004215e0       0xa4 unistd.o
                0x00000000004215e0                optarg
                0x00000000004215e4                opterr
                0x00000000004215e8                optind
                0x0000000000421600                __Hostname_buffer
                0x0000000000421640                __Login_buffer
                0x0000000000421680                optopt
                0x0000000000421684                end = .
                0x0000000000421684                _end = .
                0x0000000000421684                __end = .
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
