
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               api.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
errno               0x4               unistd.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
Streams             0x80              crt0.o
optarg              0x4               unistd.o
messagebox_button1  0x4               api.o
g_using_gui         0x4               crt0.o
opterr              0x4               unistd.o
ApplicationInfo     0x4               api.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
BufferInfo          0x4               api.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
my__p               0x4               unistd.o
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
CursorInfo          0x4               api.o
heap_end            0x4               stdlib.o
stderr              0x4               crt0.o
__mb_current_button
                    0x4               api.o
optopt              0x4               unistd.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
rect                0x4               api.o
g_cursor_y          0x4               crt0.o
ClientAreaInfo      0x4               api.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
current_semaphore   0x4               api.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               stdlib.o
HEAP_START          0x4               stdlib.o

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
 .text          0x0000000000401000      0x128 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401128       0x23 main.o
                0x0000000000401128                main
 .text          0x000000000040114b        0x0 ctype.o
 .text          0x000000000040114b     0x2a7e stdio.o
                0x0000000000401193                stdio_atoi
                0x000000000040125a                stdio_fntos
                0x0000000000401384                remove
                0x000000000040138e                fclose
                0x00000000004013af                fopen
                0x00000000004013d0                creat
                0x00000000004013f7                scroll
                0x00000000004014c4                puts
                0x00000000004014df                fread
                0x0000000000401500                fwrite
                0x00000000004018e2                printf3
                0x00000000004018ff                printf_atoi
                0x00000000004019f0                printf_i2hex
                0x0000000000401a52                printf2
                0x0000000000401bd7                stdio_nextline
                0x0000000000401c15                nlsprintf
                0x0000000000401c53                sprintf
                0x0000000000401ca8                putchar
                0x0000000000401cf3                libc_set_output_mode
                0x0000000000401d37                outbyte
                0x0000000000401ef5                _outbyte
                0x0000000000401f24                input
                0x0000000000402081                getchar
                0x00000000004020af                stdioInitialize
                0x0000000000402251                fflush
                0x0000000000402272                fprintf
                0x0000000000402300                fputs
                0x0000000000402321                nputs
                0x000000000040235c                gets
                0x00000000004023eb                ungetc
                0x000000000040240c                ftell
                0x000000000040242d                fileno
                0x000000000040244e                fgetc
                0x000000000040246f                feof
                0x0000000000402490                ferror
                0x00000000004024b1                fseek
                0x00000000004024d2                fputc
                0x000000000040256d                stdioSetCursor
                0x0000000000402588                stdioGetCursorX
                0x00000000004025a3                stdioGetCursorY
                0x00000000004025be                scanf
                0x000000000040275f                sscanf
                0x000000000040291a                kvprintf
                0x0000000000403784                printf
                0x00000000004037b2                printf_draw
                0x00000000004037fa                vfprintf
                0x0000000000403872                vprintf
                0x0000000000403891                stdout_printf
                0x00000000004038bd                stderr_printf
                0x00000000004038e9                perror
                0x0000000000403900                rewind
                0x000000000040392a                snprintf
                0x000000000040393e                stdio_initialize_standard_streams
                0x0000000000403969                libcStartTerminal
                0x00000000004039dd                setbuf
                0x00000000004039ff                setbuffer
                0x0000000000403a21                setlinebuf
                0x0000000000403a43                setvbuf
                0x0000000000403a64                filesize
                0x0000000000403aad                fileread
                0x0000000000403afb                dprintf
                0x0000000000403b05                vdprintf
                0x0000000000403b0f                vsprintf
                0x0000000000403b19                vsnprintf
                0x0000000000403b23                vscanf
                0x0000000000403b2d                vsscanf
                0x0000000000403b37                vfscanf
                0x0000000000403b41                tmpnam
                0x0000000000403b4b                tmpnam_r
                0x0000000000403b55                tempnam
                0x0000000000403b5f                tmpfile
                0x0000000000403b69                fdopen
                0x0000000000403b73                freopen
                0x0000000000403b7d                open_memstream
                0x0000000000403b87                open_wmemstream
                0x0000000000403b91                fmemopen
                0x0000000000403b9b                fgetpos
                0x0000000000403ba5                fsetpos
                0x0000000000403baf                fpurge
                0x0000000000403bb9                __fpurge
                0x0000000000403bbf                ctermid
 .text          0x0000000000403bc9     0x1111 stdlib.o
                0x0000000000403be6                rtGetHeapStart
                0x0000000000403bf0                rtGetHeapEnd
                0x0000000000403bfa                rtGetHeapPointer
                0x0000000000403c04                rtGetAvailableHeap
                0x0000000000403c0e                heapSetLibcHeap
                0x0000000000403cc1                heapAllocateMemory
                0x0000000000403ef3                FreeHeap
                0x0000000000403efd                heapInit
                0x0000000000404090                stdlibInitMM
                0x00000000004040f3                libcInitRT
                0x0000000000404115                mktemp
                0x000000000040411f                rand
                0x000000000040413c                srand
                0x000000000040414a                xmalloc
                0x000000000040417c                stdlib_die
                0x00000000004041b2                malloc
                0x00000000004041ee                realloc
                0x000000000040422b                free
                0x0000000000404231                calloc
                0x0000000000404277                zmalloc
                0x00000000004042b3                system
                0x0000000000404677                stdlib_strncmp
                0x00000000004046da                __findenv
                0x00000000004047a5                getenv
                0x00000000004047d2                setenv
                0x00000000004047dc                unsetenv
                0x00000000004047e6                atoi
                0x00000000004048ad                reverse
                0x0000000000404915                itoa
                0x00000000004049c3                abs
                0x00000000004049d3                strtod
                0x0000000000404c04                strtof
                0x0000000000404c20                strtold
                0x0000000000404c33                atof
                0x0000000000404c45                labs
                0x0000000000404c55                mkstemp
                0x0000000000404c5f                mkostemp
                0x0000000000404c69                mkstemps
                0x0000000000404c73                mkostemps
                0x0000000000404c7d                ptsname
                0x0000000000404c87                ptsname_r
                0x0000000000404c91                posix_openpt
                0x0000000000404cac                grantpt
                0x0000000000404cb6                getpt
                0x0000000000404cc0                unlockpt
                0x0000000000404cca                getprogname
                0x0000000000404cd4                setprogname
 .text          0x0000000000404cda      0xb2b string.o
                0x0000000000404cda                strcoll
                0x0000000000404cf3                memsetw
                0x0000000000404d1f                memcmp
                0x0000000000404d84                strdup
                0x0000000000404dd6                strndup
                0x0000000000404e37                strnchr
                0x0000000000404e70                strrchr
                0x0000000000404eab                strtoimax
                0x0000000000404eb5                strtoumax
                0x0000000000404ebf                strcasecmp
                0x0000000000404f27                strncpy
                0x0000000000404f7d                strcmp
                0x0000000000404fe2                strncmp
                0x0000000000405045                memset
                0x000000000040508c                memoryZeroMemory
                0x00000000004050b3                memcpy
                0x00000000004050f0                strcpy
                0x0000000000405124                strlcpy
                0x0000000000405183                strcat
                0x00000000004051b2                strchrnul
                0x00000000004051d7                strlcat
                0x0000000000405267                strncat
                0x00000000004052c9                bcopy
                0x00000000004052f6                bzero
                0x0000000000405317                strlen
                0x0000000000405345                strnlen
                0x0000000000405380                strpbrk
                0x00000000004053ce                strsep
                0x000000000040544c                strreplace
                0x0000000000405487                strcspn
                0x0000000000405526                strspn
                0x00000000004055c5                strtok_r
                0x00000000004056ac                strtok
                0x00000000004056c4                strchr
                0x00000000004056f0                memmove
                0x0000000000405771                memscan
                0x00000000004057a5                strstr
 .text          0x0000000000405805       0x33 time.o
                0x0000000000405805                time
                0x000000000040582e                gettimeofday
 .text          0x0000000000405838      0x5a9 unistd.o
                0x0000000000405838                execv
                0x0000000000405856                execve
                0x00000000004058b5                write
                0x00000000004058fd                exit
                0x000000000040591d                fast_fork
                0x0000000000405945                fork
                0x000000000040597b                sys_fork
                0x00000000004059b1                setuid
                0x00000000004059cc                getuid
                0x00000000004059e7                geteuid
                0x00000000004059f1                getpid
                0x0000000000405a09                getppid
                0x0000000000405a21                getgid
                0x0000000000405a3c                dup
                0x0000000000405a56                dup2
                0x0000000000405a72                dup3
                0x0000000000405a90                fcntl
                0x0000000000405a9a                getpriority
                0x0000000000405aa4                setpriority
                0x0000000000405aae                nice
                0x0000000000405ab8                pause
                0x0000000000405ac2                mkdir
                0x0000000000405ad6                rmdir
                0x0000000000405ae0                link
                0x0000000000405aea                unlink
                0x0000000000405af4                mlock
                0x0000000000405afe                munlock
                0x0000000000405b08                mlockall
                0x0000000000405b12                munlockall
                0x0000000000405b1c                sysconf
                0x0000000000405b26                fsync
                0x0000000000405b30                fdatasync
                0x0000000000405b3a                open
                0x0000000000405b60                close
                0x0000000000405b7e                pipe
                0x0000000000405b9f                fpathconf
                0x0000000000405ba9                pathconf
                0x0000000000405bb3                __gethostname
                0x0000000000405bdf                gethostname
                0x0000000000405c06                sethostname
                0x0000000000405c27                getlogin
                0x0000000000405c53                setlogin
                0x0000000000405c79                getusername
                0x0000000000405cf6                setusername
                0x0000000000405d6d                ttyname
                0x0000000000405daa                ttyname_r
                0x0000000000405db4                isatty
                0x0000000000405dd7                getopt
 .text          0x0000000000405de1      0x165 termios.o
                0x0000000000405de1                tcgetattr
                0x0000000000405dff                tcsetattr
                0x0000000000405e78                tcsendbreak
                0x0000000000405e82                tcdrain
                0x0000000000405e8c                tcflush
                0x0000000000405e96                tcflow
                0x0000000000405ea0                cfmakeraw
                0x0000000000405f12                cfgetispeed
                0x0000000000405f1d                cfgetospeed
                0x0000000000405f28                cfsetispeed
                0x0000000000405f32                cfsetospeed
                0x0000000000405f3c                cfsetspeed
 .text          0x0000000000405f46       0x3d ioctl.o
                0x0000000000405f46                ioctl
 .text          0x0000000000405f83     0x212d api.o
                0x0000000000405f83                system_call
                0x0000000000405fab                gde_system
                0x00000000004063b3                system1
                0x00000000004063d4                system2
                0x00000000004063f5                system3
                0x0000000000406416                system4
                0x0000000000406437                system5
                0x0000000000406458                system6
                0x0000000000406479                system7
                0x000000000040649a                system8
                0x00000000004064bb                system9
                0x00000000004064dc                system10
                0x00000000004064fd                system11
                0x000000000040651e                system12
                0x000000000040653f                system13
                0x0000000000406560                system14
                0x0000000000406581                system15
                0x00000000004065a2                gde_refresh_buffer
                0x000000000040667a                gde_print_string
                0x0000000000406680                gde_vsync
                0x0000000000406698                gde_system_procedure
                0x00000000004066db                __gde_set_cursor
                0x00000000004066f5                __gde_put_char
                0x00000000004066fb                gde_load_bitmap_16x16
                0x0000000000406714                gde_shutdown
                0x000000000040672e                gde_init_background
                0x0000000000406734                gde_message_box
                0x0000000000406a39                mbProcedure
                0x0000000000406bf5                gde_dialog_box
                0x0000000000406fb0                dbProcedure
                0x0000000000407026                call_kernel
                0x000000000040714e                call_gui
                0x00000000004071e3                gde_create_window
                0x000000000040725c                gde_register_window
                0x0000000000407284                gde_close_window
                0x00000000004072ac                gde_set_focus
                0x00000000004072d4                gde_get_focus
                0x00000000004072e9                gde_kill_focus
                0x0000000000407311                gde_set_active_window
                0x0000000000407339                gde_get_active_window
                0x000000000040734e                gde_show_current_process_info
                0x0000000000407364                gde_resize_window
                0x0000000000407381                gde_redraw_window
                0x000000000040739e                gde_replace_window
                0x00000000004073b8                gde_maximize_window
                0x00000000004073d7                gde_minimize_window
                0x00000000004073f6                gde_update_window
                0x0000000000407415                gde_get_foregroung_window
                0x000000000040742b                gde_set_foregroung_window
                0x0000000000407447                gde_exit
                0x0000000000407464                gde_kill
                0x000000000040746a                gde_dead_thread_collector
                0x0000000000407480                gde_strncmp
                0x00000000004074e3                gde_show_backbuffer
                0x00000000004074f9                gde_reboot
                0x0000000000407512                gde_set_cursor
                0x000000000040752a                gde_get_cursor
                0x0000000000407530                gde_get_cursor_x
                0x000000000040754b                gde_get_cursor_y
                0x0000000000407566                gde_get_client_area_rect
                0x000000000040757e                gde_set_client_area_rect
                0x000000000040759d                gde_create_process
                0x00000000004075b6                gde_create_thread
                0x00000000004075cf                gde_start_thread
                0x00000000004075eb                gde_fopen
                0x0000000000407617                gde_save_file
                0x000000000040766a                gde_down
                0x00000000004076bf                gde_up
                0x0000000000407714                gde_enter_critical_section
                0x000000000040774f                gde_exit_critical_section
                0x0000000000407768                gde_p
                0x000000000040776e                gde_v
                0x0000000000407774                gde_initialize_critical_section
                0x000000000040778d                gde_begin_paint
                0x0000000000407798                gde_end_paint
                0x00000000004077a3                gde_put_char
                0x00000000004077bf                gde_def_dialog
                0x00000000004077c9                gde_get_system_metrics
                0x00000000004077e7                gde_dialog
                0x0000000000407880                gde_getchar
                0x000000000040789b                gde_display_bmp
                0x0000000000407ca2                gde_send_message_to_process
                0x0000000000407ce5                gde_send_message_to_thread
                0x0000000000407d28                gde_send_message
                0x0000000000407d5e                gde_draw_text
                0x0000000000407d9d                gde_get_ws_screen_window
                0x0000000000407db5                gde_get_ws_main_window
                0x0000000000407dcd                gde_create_timer
                0x0000000000407ded                gde_get_systime_info
                0x0000000000407e0e                gde_show_window
                0x0000000000407e2d                gde_start_terminal
                0x0000000000407ea1                gde_update_statusbar
                0x0000000000407ebf                gde_get_pid
                0x0000000000407eea                gde_get_screen_window
                0x0000000000407f05                gde_get_background_window
                0x0000000000407f20                gde_get_main_window
                0x0000000000407f3b                gde_getprocessname
                0x0000000000407fb8                gde_getthreadname
                0x0000000000408035                gde_get_process_stats
                0x0000000000408053                gde_get_thread_stats
                0x0000000000408071                gde_debug_print
                0x0000000000408093                gde_clone_and_execute
 .text          0x00000000004080b0       0x28 stubs.o
                0x00000000004080b0                gramado_system_call
                0x0000000000409000                . = ALIGN (0x1000)
 *fill*         0x00000000004080d8      0xf28 

.iplt           0x0000000000409000        0x0
 .iplt          0x0000000000409000        0x0 crt0.o

.rodata         0x0000000000409000      0xf81
 .rodata        0x0000000000409000       0x74 crt0.o
 .rodata        0x0000000000409074       0x1c main.o
 *fill*         0x0000000000409090       0x10 
 .rodata        0x00000000004090a0      0x100 ctype.o
                0x00000000004090a0                _ctype
 .rodata        0x00000000004091a0      0x329 stdio.o
                0x0000000000409300                hex2ascii_data
 *fill*         0x00000000004094c9        0x7 
 .rodata        0x00000000004094d0      0x520 stdlib.o
 .rodata        0x00000000004099f0       0x89 unistd.o
 *fill*         0x0000000000409a79        0x3 
 .rodata        0x0000000000409a7c      0x505 api.o

.eh_frame       0x0000000000409f84     0x2b9c
 .eh_frame      0x0000000000409f84       0x34 crt0.o
 .eh_frame      0x0000000000409fb8       0x24 main.o
                                         0x3c (size before relaxing)
 .eh_frame      0x0000000000409fdc      0xb74 stdio.o
                                        0xb8c (size before relaxing)
 .eh_frame      0x000000000040ab50      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040b150      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000040b610       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040b650      0x600 unistd.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040bc50      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x000000000040bdd0       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040bdf0      0xd0c api.o
                                        0xd24 (size before relaxing)
 .eh_frame      0x000000000040cafc       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040cb20        0x0
 .rel.got       0x000000000040cb20        0x0 crt0.o
 .rel.iplt      0x000000000040cb20        0x0 crt0.o
 .rel.text      0x000000000040cb20        0x0 crt0.o

.data           0x000000000040cb20      0x4e0
                0x000000000040cb20                data = .
                0x000000000040cb20                _data = .
                0x000000000040cb20                __data = .
 *(.data)
 .data          0x000000000040cb20       0x14 crt0.o
 .data          0x000000000040cb34        0x0 main.o
 .data          0x000000000040cb34        0x0 ctype.o
 .data          0x000000000040cb34        0x0 stdio.o
 *fill*         0x000000000040cb34        0x4 
 .data          0x000000000040cb38        0x8 stdlib.o
                0x000000000040cb38                _infinity
 .data          0x000000000040cb40        0x0 string.o
 .data          0x000000000040cb40        0x0 time.o
 .data          0x000000000040cb40        0x0 unistd.o
 .data          0x000000000040cb40        0x0 termios.o
 .data          0x000000000040cb40        0x0 ioctl.o
 .data          0x000000000040cb40      0x440 api.o
 .data          0x000000000040cf80        0x0 stubs.o
                0x000000000040d000                . = ALIGN (0x1000)
 *fill*         0x000000000040cf80       0x80 

.got            0x000000000040d000        0x0
 .got           0x000000000040d000        0x0 crt0.o

.got.plt        0x000000000040d000        0x0
 .got.plt       0x000000000040d000        0x0 crt0.o

.igot.plt       0x000000000040d000        0x0
 .igot.plt      0x000000000040d000        0x0 crt0.o

.bss            0x000000000040d000    0x12678
                0x000000000040d000                bss = .
                0x000000000040d000                _bss = .
                0x000000000040d000                __bss = .
 *(.bss)
 .bss           0x000000000040d000        0x0 crt0.o
 .bss           0x000000000040d000        0x0 main.o
 .bss           0x000000000040d000        0x0 ctype.o
 .bss           0x000000000040d000        0x9 stdio.o
 *fill*         0x000000000040d009       0x17 
 .bss           0x000000000040d020     0x8020 stdlib.o
                0x000000000040d020                environ
 .bss           0x0000000000415040        0x4 string.o
 .bss           0x0000000000415044        0x0 time.o
 *fill*         0x0000000000415044       0x1c 
 .bss           0x0000000000415060      0x19f unistd.o
                0x0000000000415060                __execv_environ
 .bss           0x00000000004151ff        0x0 termios.o
 .bss           0x00000000004151ff        0x0 ioctl.o
 *fill*         0x00000000004151ff        0x1 
 .bss           0x0000000000415200     0x8004 api.o
 .bss           0x000000000041d204        0x0 stubs.o
                0x000000000041e000                . = ALIGN (0x1000)
 *fill*         0x000000000041d204      0xdfc 
 COMMON         0x000000000041e000      0xd08 crt0.o
                0x000000000041e000                g_cursor_x
                0x000000000041e004                stdout
                0x000000000041e008                g_char_attrib
                0x000000000041e00c                g_rows
                0x000000000041e020                Streams
                0x000000000041e0a0                g_using_gui
                0x000000000041e0c0                prompt_out
                0x000000000041e4c0                g_columns
                0x000000000041e4c4                prompt_pos
                0x000000000041e4c8                stdin
                0x000000000041e4cc                prompt_status
                0x000000000041e4e0                prompt_err
                0x000000000041e8e0                stderr
                0x000000000041e900                prompt
                0x000000000041ed00                g_cursor_y
                0x000000000041ed04                prompt_max
 COMMON         0x000000000041ed08        0x0 stdio.o
 *fill*         0x000000000041ed08       0x18 
 COMMON         0x000000000041ed20      0x878 stdlib.o
                0x000000000041ed20                mm_prev_pointer
                0x000000000041ed40                mmblockList
                0x000000000041f140                last_valid
                0x000000000041f160                heapList
                0x000000000041f560                libcHeap
                0x000000000041f564                randseed
                0x000000000041f568                heap_start
                0x000000000041f56c                g_available_heap
                0x000000000041f570                g_heap_pointer
                0x000000000041f574                HEAP_SIZE
                0x000000000041f578                mmblockCount
                0x000000000041f57c                last_size
                0x000000000041f580                heap_end
                0x000000000041f584                HEAP_END
                0x000000000041f588                Heap
                0x000000000041f58c                current_mmblock
                0x000000000041f590                heapCount
                0x000000000041f594                HEAP_START
 *fill*         0x000000000041f598        0x8 
 COMMON         0x000000000041f5a0       0xa4 unistd.o
                0x000000000041f5a0                errno
                0x000000000041f5a4                optarg
                0x000000000041f5a8                opterr
                0x000000000041f5ac                my__p
                0x000000000041f5b0                optind
                0x000000000041f5c0                __Hostname_buffer
                0x000000000041f600                __Login_buffer
                0x000000000041f640                optopt
 COMMON         0x000000000041f644       0x34 api.o
                0x000000000041f644                CurrentWindow
                0x000000000041f648                dialogbox_button2
                0x000000000041f64c                messagebox_button1
                0x000000000041f650                ApplicationInfo
                0x000000000041f654                BufferInfo
                0x000000000041f658                dialogbox_button1
                0x000000000041f65c                first_responder
                0x000000000041f660                CursorInfo
                0x000000000041f664                __mb_current_button
                0x000000000041f668                rect
                0x000000000041f66c                ClientAreaInfo
                0x000000000041f670                messagebox_button2
                0x000000000041f674                current_semaphore
                0x000000000041f678                end = .
                0x000000000041f678                _end = .
                0x000000000041f678                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD unistd.o
LOAD termios.o
LOAD ioctl.o
LOAD api.o
LOAD stubs.o
OUTPUT(GWS.BIN elf32-i386)

.comment        0x0000000000000000       0x11
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 ctype.o
 .comment       0x0000000000000011       0x12 stdio.o
 .comment       0x0000000000000011       0x12 stdlib.o
 .comment       0x0000000000000011       0x12 string.o
 .comment       0x0000000000000011       0x12 time.o
 .comment       0x0000000000000011       0x12 unistd.o
 .comment       0x0000000000000011       0x12 termios.o
 .comment       0x0000000000000011       0x12 ioctl.o
 .comment       0x0000000000000011       0x12 api.o
 .comment       0x0000000000000011       0x12 stubs.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
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
                0x0000000000000000        0x0 unistd.o
 .note.GNU-stack
                0x0000000000000000        0x0 termios.o
 .note.GNU-stack
                0x0000000000000000        0x0 ioctl.o
 .note.GNU-stack
                0x0000000000000000        0x0 api.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
