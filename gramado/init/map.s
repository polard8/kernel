
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
 .text          0x0000000000402be7     0x3fa2 stdio.o
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
                0x0000000000405fe1                filesize
                0x000000000040602a                fileread
                0x0000000000406078                dprintf
                0x0000000000406095                vdprintf
                0x0000000000406338                Wirzenius_Torvalds_vsprintf
                0x0000000000406711                Torvalds_printf
                0x0000000000406758                vsnprintf
                0x0000000000406775                vscanf
                0x0000000000406792                vsscanf
                0x00000000004067af                vfscanf
                0x00000000004067d9                tmpfile
                0x00000000004067f6                tmpnam
                0x0000000000406813                tmpnam_r
                0x0000000000406830                tempnam
                0x000000000040684d                stdio_make_file
                0x00000000004068c8                fdopen
                0x00000000004068ee                freopen
                0x0000000000406918                open_memstream
                0x0000000000406935                open_wmemstream
                0x0000000000406952                fmemopen
                0x000000000040696f                fgetpos
                0x00000000004069ae                fsetpos
                0x00000000004069d9                fpurge
                0x0000000000406a03                __fpurge
                0x0000000000406a1f                ctermid
                0x0000000000406a3c                stdioInitialize
 .text          0x0000000000406b89     0x1201 stdlib.o
                0x0000000000406ba6                rtGetHeapStart
                0x0000000000406bb0                rtGetHeapEnd
                0x0000000000406bba                rtGetHeapPointer
                0x0000000000406bc4                rtGetAvailableHeap
                0x0000000000406bce                heapSetLibcHeap
                0x0000000000406c81                heapAllocateMemory
                0x0000000000406eb3                FreeHeap
                0x0000000000406ebd                heapInit
                0x0000000000407050                stdlibInitMM
                0x00000000004070b3                libcInitRT
                0x00000000004070dc                mktemp
                0x00000000004070e6                rand
                0x0000000000407103                srand
                0x0000000000407111                xmalloc
                0x0000000000407143                stdlib_die
                0x0000000000407179                malloc
                0x00000000004071b5                realloc
                0x00000000004071f2                free
                0x00000000004071f8                calloc
                0x000000000040723e                zmalloc
                0x000000000040727a                system
                0x000000000040763e                stdlib_strncmp
                0x00000000004076f4                v7_getenv
                0x0000000000407730                __findenv
                0x0000000000407853                getenv
                0x0000000000407880                setenv
                0x000000000040788a                unsetenv
                0x0000000000407894                atoi
                0x000000000040795b                reverse
                0x00000000004079c2                itoa
                0x0000000000407a70                abs
                0x0000000000407a80                strtod
                0x0000000000407cb2                strtof
                0x0000000000407cce                strtold
                0x0000000000407ce1                atof
                0x0000000000407cf3                labs
                0x0000000000407d03                mkstemp
                0x0000000000407d0d                mkostemp
                0x0000000000407d17                mkstemps
                0x0000000000407d21                mkostemps
                0x0000000000407d2b                ptsname
                0x0000000000407d35                ptsname_r
                0x0000000000407d3f                posix_openpt
                0x0000000000407d5c                grantpt
                0x0000000000407d66                unlockpt
                0x0000000000407d70                getpt
                0x0000000000407d7a                getprogname
                0x0000000000407d84                setprogname
 .text          0x0000000000407d8a      0xc44 string.o
                0x0000000000407db5                strcoll
                0x0000000000407dce                memsetw
                0x0000000000407dfa                memcmp
                0x0000000000407e5f                strdup
                0x0000000000407eb1                strndup
                0x0000000000407f12                strnchr
                0x0000000000407f4b                strrchr
                0x0000000000407f86                strtoimax
                0x0000000000407f90                strtoumax
                0x0000000000407f9a                strcasecmp
                0x0000000000408002                strncpy
                0x0000000000408058                strcmp
                0x00000000004080c4                strncmp
                0x000000000040811e                memset
                0x0000000000408165                memoryZeroMemory
                0x000000000040818c                memcpy
                0x00000000004081c9                strcpy
                0x00000000004081fd                strlcpy
                0x000000000040825c                strcat
                0x000000000040828b                strchrnul
                0x00000000004082b0                strlcat
                0x0000000000408342                strncat
                0x00000000004083a4                bcopy
                0x00000000004083d0                bzero
                0x00000000004083f0                strlen
                0x000000000040841e                strnlen
                0x0000000000408459                strpbrk
                0x00000000004084a7                strsep
                0x0000000000408525                strreplace
                0x0000000000408560                strcspn
                0x00000000004085ff                strspn
                0x000000000040869e                strtok_r
                0x0000000000408785                strtok
                0x000000000040879d                strchr
                0x00000000004087c9                memmove
                0x000000000040884a                memscan
                0x000000000040887e                strstr
                0x00000000004088de                index
                0x000000000040890b                rindex
                0x000000000040891e                strxfrm
                0x0000000000408970                strerror
                0x000000000040897a                strerror_r
                0x0000000000408984                strsignal
                0x000000000040898e                strtoupper
 .text          0x00000000004089ce       0x89 conio.o
                0x00000000004089ce                putch
                0x00000000004089f2                cputs
                0x0000000000408a27                getch
                0x0000000000408a3f                getche
 .text          0x0000000000408a57      0x879 unistd.o
                0x0000000000408a57                execv
                0x0000000000408a75                execve
                0x0000000000408ab0                read_ttyList
                0x0000000000408ade                write_ttyList
                0x0000000000408b0c                read_tty
                0x0000000000408b3a                write_tty
                0x0000000000408b68                read_VC
                0x0000000000408b96                write_VC
                0x0000000000408bc4                read
                0x0000000000408bef                write
                0x0000000000408c1a                exit
                0x0000000000408c3a                fork
                0x0000000000408c6c                setuid
                0x0000000000408c87                getuid
                0x0000000000408ca2                geteuid
                0x0000000000408cac                getpid
                0x0000000000408cc4                getppid
                0x0000000000408cdc                getgid
                0x0000000000408cf7                dup
                0x0000000000408d11                dup2
                0x0000000000408d2d                dup3
                0x0000000000408d4b                getpriority
                0x0000000000408d55                setpriority
                0x0000000000408d5f                nice
                0x0000000000408d69                pause
                0x0000000000408d73                mkdir
                0x0000000000408d87                rmdir
                0x0000000000408d91                link
                0x0000000000408d9b                unlink
                0x0000000000408da5                mlock
                0x0000000000408daf                munlock
                0x0000000000408db9                mlockall
                0x0000000000408dc3                munlockall
                0x0000000000408dcd                sysconf
                0x0000000000408dd7                fsync
                0x0000000000408de1                fdatasync
                0x0000000000408deb                sync
                0x0000000000408df1                syncfs
                0x0000000000408dfb                close
                0x0000000000408e19                pipe
                0x0000000000408e3a                fpathconf
                0x0000000000408e44                pathconf
                0x0000000000408e4e                __gethostname
                0x0000000000408e7a                gethostname
                0x0000000000408ea5                sethostname
                0x0000000000408ec3                getlogin
                0x0000000000408eef                setlogin
                0x0000000000408f15                getusername
                0x0000000000408f8f                setusername
                0x0000000000409003                ttyname
                0x0000000000409040                ttyname_r
                0x000000000040904a                isatty
                0x000000000040906d                getopt
                0x0000000000409077                alarm
                0x0000000000409081                brk
                0x000000000040908b                execvp
                0x0000000000409095                execvpe
                0x000000000040909f                chown
                0x00000000004090a9                fchown
                0x00000000004090b3                lchown
                0x00000000004090bd                chdir
                0x00000000004090c7                fchdir
                0x00000000004090d1                sleep
                0x00000000004090db                _exit
                0x00000000004090f1                swab_w
                0x0000000000409130                swab
                0x0000000000409147                lseek
                0x0000000000409151                tell
                0x0000000000409165                access
                0x000000000040916f                eq
                0x00000000004091bb                getlin
                0x000000000040924c                compar
                0x00000000004092a8                xxx_todo_int133
 .text          0x00000000004092d0      0x20b termios.o
                0x00000000004092d0                tcgetpgrp
                0x00000000004092fd                tcsetpgrp
                0x0000000000409322                tcgetattr
                0x0000000000409340                tcsetattr
                0x00000000004093b1                tcsendbreak
                0x00000000004093bb                tcdrain
                0x00000000004093d8                tcflush
                0x00000000004093e2                tcflow
                0x00000000004093ec                cfmakeraw
                0x0000000000409466                cfgetispeed
                0x000000000040947e                cfgetospeed
                0x0000000000409496                cfsetispeed
                0x00000000004094ad                cfsetospeed
                0x00000000004094c4                cfsetspeed
 .text          0x00000000004094db       0x52 ioctl.o
                0x00000000004094db                ioctl
 .text          0x000000000040952d      0x11f fcntl.o
                0x000000000040952d                fcntl
                0x0000000000409544                openat
                0x000000000040957f                open
                0x000000000040961b                creat
                0x0000000000409642                flock
 .text          0x000000000040964c       0x28 stubs.o
                0x000000000040964c                gramado_system_call
                0x000000000040a000                . = ALIGN (0x1000)
 *fill*         0x0000000000409674      0x98c 

.iplt           0x000000000040a000        0x0
 .iplt          0x000000000040a000        0x0 crt0.o

.rodata         0x000000000040a000     0x1284
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
 .rodata        0x000000000040b1f8        0x6 conio.o
 .rodata        0x000000000040b1fe       0x4f unistd.o
 *fill*         0x000000000040b24d        0x3 
 .rodata        0x000000000040b250       0x34 fcntl.o

.eh_frame       0x000000000040b284     0x335c
 .eh_frame      0x000000000040b284       0x34 crt0.o
 .eh_frame      0x000000000040b2b8       0x44 main.o
                                         0x5c (size before relaxing)
 .eh_frame      0x000000000040b2fc      0xb24 api.o
                                        0xb3c (size before relaxing)
 .eh_frame      0x000000000040be20      0xf54 stdio.o
                                        0xf6c (size before relaxing)
 .eh_frame      0x000000000040cd74      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x000000000040d3bc      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040d97c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040da1c      0x920 unistd.o
                                        0x938 (size before relaxing)
 .eh_frame      0x000000000040e33c      0x1c0 termios.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x000000000040e4fc       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040e51c       0xa0 fcntl.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040e5bc       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040e5e0        0x0
 .rel.got       0x000000000040e5e0        0x0 crt0.o
 .rel.iplt      0x000000000040e5e0        0x0 crt0.o
 .rel.text      0x000000000040e5e0        0x0 crt0.o

.data           0x000000000040e5e0      0xa20
                0x000000000040e5e0                data = .
                0x000000000040e5e0                _data = .
                0x000000000040e5e0                __data = .
 *(.data)
 .data          0x000000000040e5e0       0x50 crt0.o
 *fill*         0x000000000040e630       0x10 
 .data          0x000000000040e640      0x440 main.o
 .data          0x000000000040ea80      0x440 api.o
 .data          0x000000000040eec0        0x0 ctype.o
 .data          0x000000000040eec0        0x0 stdio.o
 .data          0x000000000040eec0        0x8 stdlib.o
                0x000000000040eec0                _infinity
 .data          0x000000000040eec8        0x0 string.o
 .data          0x000000000040eec8        0x0 conio.o
 .data          0x000000000040eec8        0x0 unistd.o
 .data          0x000000000040eec8        0x0 termios.o
 .data          0x000000000040eec8        0x0 ioctl.o
 .data          0x000000000040eec8        0x0 fcntl.o
 .data          0x000000000040eec8        0x0 stubs.o
                0x000000000040f000                . = ALIGN (0x1000)
 *fill*         0x000000000040eec8      0x138 

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
