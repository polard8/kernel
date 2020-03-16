
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
errno               0x4               unistd.o
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
my( *)              0x4               unistd.o
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


.text           0x0000000000401000     0x8000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000       0xf2 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010f2      0x20f main.o
                0x00000000004010f2                __debug_print
                0x0000000000401114                enable_maskable_interrupts
                0x000000000040111c                main3
                0x00000000004012a0                main
 .text          0x0000000000401301     0x21c6 api.o
                0x0000000000401301                system_call
                0x0000000000401329                gde_system
                0x0000000000401731                system1
                0x0000000000401752                system2
                0x0000000000401773                system3
                0x0000000000401794                system4
                0x00000000004017b5                system5
                0x00000000004017d6                system6
                0x00000000004017f7                system7
                0x0000000000401818                system8
                0x0000000000401839                system9
                0x000000000040185a                system10
                0x000000000040187b                system11
                0x000000000040189c                system12
                0x00000000004018bd                system13
                0x00000000004018de                system14
                0x00000000004018ff                system15
                0x0000000000401920                gde_refresh_buffer
                0x00000000004019f8                gde_print_string
                0x00000000004019fe                gde_vsync
                0x0000000000401a16                gws_vsync
                0x0000000000401a23                gde_system_procedure
                0x0000000000401a66                __gde_set_cursor
                0x0000000000401a80                __gde_put_char
                0x0000000000401a86                gde_load_bitmap_16x16
                0x0000000000401a9f                gde_shutdown
                0x0000000000401aa6                gde_init_background
                0x0000000000401aac                gde_message_box
                0x0000000000401db1                mbProcedure
                0x0000000000401f6d                gde_dialog_box
                0x0000000000402328                dbProcedure
                0x000000000040239e                call_kernel
                0x00000000004024c6                call_gui
                0x000000000040255b                gde_create_window
                0x00000000004025d4                gde_register_window
                0x00000000004025fc                gde_close_window
                0x0000000000402624                gde_set_focus
                0x000000000040264c                gde_get_focus
                0x0000000000402661                gde_kill_focus
                0x0000000000402689                gde_set_active_window
                0x00000000004026b1                gde_get_active_window
                0x00000000004026c6                gde_show_current_process_info
                0x00000000004026dc                gde_resize_window
                0x00000000004026f9                gde_redraw_window
                0x0000000000402716                gde_replace_window
                0x0000000000402730                gde_maximize_window
                0x000000000040274f                gde_minimize_window
                0x000000000040276e                gde_update_window
                0x0000000000402790                gde_get_foregroung_window
                0x00000000004027a6                gde_set_foregroung_window
                0x00000000004027c2                gde_exit
                0x00000000004027df                gde_kill
                0x00000000004027e5                gde_dead_thread_collector
                0x00000000004027fb                gde_strncmp
                0x000000000040285e                gde_show_backbuffer
                0x0000000000402874                gde_reboot
                0x000000000040288d                gde_set_cursor
                0x00000000004028a5                gde_get_cursor
                0x00000000004028ab                gde_get_cursor_x
                0x00000000004028c6                gde_get_cursor_y
                0x00000000004028e1                gde_get_client_area_rect
                0x00000000004028f9                gde_set_client_area_rect
                0x0000000000402918                gde_create_process
                0x0000000000402931                gde_create_thread
                0x000000000040294a                gde_start_thread
                0x0000000000402966                gde_fopen
                0x0000000000402992                gde_save_file
                0x00000000004029e5                gde_create_empty_file
                0x0000000000402a0f                gde_create_empty_directory
                0x0000000000402a39                gde_down
                0x0000000000402a8e                gde_up
                0x0000000000402ae3                gde_enter_critical_section
                0x0000000000402b1e                gde_exit_critical_section
                0x0000000000402b37                gde_p
                0x0000000000402b3d                gde_v
                0x0000000000402b43                gde_initialize_critical_section
                0x0000000000402b5c                gde_begin_paint
                0x0000000000402b67                gde_end_paint
                0x0000000000402b72                gde_put_char
                0x0000000000402b8e                gde_def_dialog
                0x0000000000402b98                gde_get_system_metrics
                0x0000000000402bb6                gde_dialog
                0x0000000000402c4f                gde_getchar
                0x0000000000402c6a                gde_display_bmp
                0x0000000000403071                gde_send_message_to_process
                0x00000000004030b4                gde_send_message_to_thread
                0x00000000004030f7                gde_send_message
                0x000000000040312d                gde_draw_text
                0x000000000040316c                gde_get_ws_screen_window
                0x0000000000403184                gde_get_ws_main_window
                0x000000000040319c                gde_create_timer
                0x00000000004031bc                gde_get_systime_info
                0x00000000004031dd                gde_show_window
                0x00000000004031fc                gde_start_terminal
                0x0000000000403270                gde_update_statusbar
                0x000000000040328e                gde_get_pid
                0x00000000004032b9                gde_get_screen_window
                0x00000000004032d4                gde_get_background_window
                0x00000000004032ef                gde_get_main_window
                0x000000000040330a                gde_getprocessname
                0x0000000000403387                gde_getthreadname
                0x0000000000403404                gde_get_process_stats
                0x0000000000403422                gde_get_thread_stats
                0x0000000000403440                gde_debug_print
                0x0000000000403462                gde_clone_and_execute
                0x000000000040347f                gde_setup_net_buffer
                0x00000000004034a6                execute_new_process
 .text          0x00000000004034c7        0x0 ctype.o
 .text          0x00000000004034c7     0x328b stdio.o
                0x000000000040350f                stdio_atoi
                0x00000000004035d6                stdio_fntos
                0x0000000000403700                debug_print
                0x0000000000403722                remove
                0x000000000040372c                fclose
                0x000000000040375a                fopen
                0x0000000000403872                creat
                0x0000000000403899                scroll
                0x0000000000403966                fread
                0x0000000000403987                fwrite
                0x00000000004039a8                prompt_putchar
                0x00000000004039f8                prompt_put_string
                0x0000000000403a25                prompt_strcat
                0x0000000000403a52                prompt_flush
                0x0000000000403ab6                prompt_clean
                0x0000000000403ec6                printf3
                0x0000000000403ee3                printf_atoi
                0x0000000000403fd4                printf_i2hex
                0x0000000000404036                printf2
                0x00000000004041bb                stdio_nextline
                0x00000000004041f9                nlsprintf
                0x0000000000404237                sprintf
                0x000000000040428c                libc_set_output_mode
                0x00000000004042d0                outbyte
                0x00000000004044c4                _outbyte
                0x00000000004044f3                input
                0x0000000000404653                stdioInitialize
                0x0000000000404799                fflush
                0x00000000004047d9                __fflush
                0x00000000004048c7                __getc
                0x0000000000404972                __putc
                0x0000000000404a17                getc
                0x0000000000404a2d                putc
                0x0000000000404a46                fgetc
                0x0000000000404a5c                fputc
                0x0000000000404a75                getchar
                0x0000000000404a8e                putchar
                0x0000000000404aaa                gets
                0x0000000000404aec                puts
                0x0000000000404b26                fgets
                0x0000000000404b81                fputs
                0x0000000000404bb5                getw
                0x0000000000404bf6                putw
                0x0000000000404c25                fprintf
                0x0000000000404cc3                nputs
                0x0000000000404cfe                ungetc
                0x0000000000404d2c                ftell
                0x0000000000404d5a                fileno
                0x0000000000404d88                __gramado__getc
                0x0000000000404e33                feof
                0x0000000000404e61                ferror
                0x0000000000404e8f                fseek
                0x0000000000404ebd                __serenity_fflush
                0x0000000000404f5e                __serenity_fputc
                0x0000000000405003                __serenity_putc
                0x000000000040501c                stdioSetCursor
                0x0000000000405037                stdioGetCursorX
                0x0000000000405052                stdioGetCursorY
                0x000000000040506d                scanf
                0x000000000040520e                sscanf
                0x00000000004053c9                kvprintf
                0x0000000000406233                printf
                0x0000000000406261                printf_draw
                0x00000000004062a9                vfprintf
                0x0000000000406321                vprintf
                0x0000000000406350                stdout_printf
                0x000000000040638c                stderr_printf
                0x00000000004063c8                perror
                0x00000000004063df                rewind
                0x000000000040640d                snprintf
                0x0000000000406421                stdio_initialize_standard_streams
                0x000000000040647c                libcStartTerminal
                0x00000000004064f0                setbuf
                0x000000000040651a                setbuffer
                0x0000000000406544                setlinebuf
                0x000000000040656e                setvbuf
                0x000000000040659c                filesize
                0x00000000004065e5                fileread
                0x0000000000406633                dprintf
                0x000000000040664a                vdprintf
                0x0000000000406654                vsprintf
                0x000000000040665e                vsnprintf
                0x0000000000406668                vscanf
                0x0000000000406672                vsscanf
                0x000000000040667c                vfscanf
                0x0000000000406693                tmpnam
                0x000000000040669d                tmpnam_r
                0x00000000004066a7                tempnam
                0x00000000004066b1                tmpfile
                0x00000000004066bb                fdopen
                0x00000000004066c5                freopen
                0x00000000004066dc                open_memstream
                0x00000000004066e6                open_wmemstream
                0x00000000004066f0                fmemopen
                0x00000000004066fa                fgetpos
                0x0000000000406711                fsetpos
                0x0000000000406728                fpurge
                0x000000000040673f                __fpurge
                0x0000000000406748                ctermid
 .text          0x0000000000406752     0x11a0 stdlib.o
                0x000000000040676f                rtGetHeapStart
                0x0000000000406779                rtGetHeapEnd
                0x0000000000406783                rtGetHeapPointer
                0x000000000040678d                rtGetAvailableHeap
                0x0000000000406797                heapSetLibcHeap
                0x000000000040684a                heapAllocateMemory
                0x0000000000406a7c                FreeHeap
                0x0000000000406a86                heapInit
                0x0000000000406c19                stdlibInitMM
                0x0000000000406c7c                libcInitRT
                0x0000000000406c9e                mktemp
                0x0000000000406ca8                rand
                0x0000000000406cc5                srand
                0x0000000000406cd3                xmalloc
                0x0000000000406d05                stdlib_die
                0x0000000000406d3b                malloc
                0x0000000000406d77                realloc
                0x0000000000406db4                free
                0x0000000000406dba                calloc
                0x0000000000406e00                zmalloc
                0x0000000000406e3c                system
                0x0000000000407200                stdlib_strncmp
                0x0000000000407263                __findenv
                0x0000000000407384                getenv
                0x00000000004073b1                setenv
                0x00000000004073bb                unsetenv
                0x00000000004073c5                atoi
                0x000000000040748c                reverse
                0x00000000004074f4                itoa
                0x00000000004075a2                abs
                0x00000000004075b2                strtod
                0x00000000004077e3                strtof
                0x00000000004077ff                strtold
                0x0000000000407812                atof
                0x0000000000407824                labs
                0x0000000000407834                mkstemp
                0x000000000040783e                mkostemp
                0x0000000000407848                mkstemps
                0x0000000000407852                mkostemps
                0x000000000040785c                ptsname
                0x0000000000407882                ptsname_r
                0x00000000004078a9                posix_openpt
                0x00000000004078c4                grantpt
                0x00000000004078ce                getpt
                0x00000000004078d8                unlockpt
                0x00000000004078e2                getprogname
                0x00000000004078ec                setprogname
 .text          0x00000000004078f2      0xb90 string.o
                0x00000000004078f2                strcoll
                0x000000000040790b                memsetw
                0x0000000000407937                memcmp
                0x000000000040799c                strdup
                0x00000000004079ee                strndup
                0x0000000000407a4f                strnchr
                0x0000000000407a88                strrchr
                0x0000000000407ac3                strtoimax
                0x0000000000407acd                strtoumax
                0x0000000000407ad7                strcasecmp
                0x0000000000407b3f                strncpy
                0x0000000000407b95                strcmp
                0x0000000000407bfa                strncmp
                0x0000000000407c5f                gramado_strncmp
                0x0000000000407cc2                memset
                0x0000000000407d09                memoryZeroMemory
                0x0000000000407d30                memcpy
                0x0000000000407d6d                strcpy
                0x0000000000407da1                strlcpy
                0x0000000000407e00                strcat
                0x0000000000407e2f                strchrnul
                0x0000000000407e54                strlcat
                0x0000000000407ee4                strncat
                0x0000000000407f46                bcopy
                0x0000000000407f73                bzero
                0x0000000000407f94                strlen
                0x0000000000407fc2                strnlen
                0x0000000000407ffd                strpbrk
                0x000000000040804b                strsep
                0x00000000004080c9                strreplace
                0x0000000000408104                strcspn
                0x00000000004081a3                strspn
                0x0000000000408242                strtok_r
                0x0000000000408329                strtok
                0x0000000000408341                strchr
                0x000000000040836d                memmove
                0x00000000004083ee                memscan
                0x0000000000408422                strstr
 .text          0x0000000000408482       0x89 conio.o
                0x0000000000408482                putch
                0x00000000004084a6                cputs
                0x00000000004084db                getch
                0x00000000004084f3                getche
 .text          0x000000000040850b      0x60f unistd.o
                0x000000000040850b                execv
                0x0000000000408529                execve
                0x0000000000408588                read_ttyList
                0x00000000004085b6                write_ttyList
                0x00000000004085e4                read_VC
                0x0000000000408612                write_VC
                0x0000000000408640                read
                0x000000000040866b                write
                0x0000000000408696                exit
                0x00000000004086b6                fork
                0x00000000004086ce                setuid
                0x00000000004086e9                getuid
                0x0000000000408704                geteuid
                0x000000000040870e                getpid
                0x0000000000408726                getppid
                0x000000000040873e                getgid
                0x0000000000408759                dup
                0x0000000000408773                dup2
                0x000000000040878f                dup3
                0x00000000004087ad                fcntl
                0x00000000004087b7                getpriority
                0x00000000004087c1                setpriority
                0x00000000004087cb                nice
                0x00000000004087d5                pause
                0x00000000004087df                mkdir
                0x00000000004087f3                rmdir
                0x00000000004087fd                link
                0x0000000000408807                unlink
                0x0000000000408811                mlock
                0x000000000040881b                munlock
                0x0000000000408825                mlockall
                0x000000000040882f                munlockall
                0x0000000000408839                sysconf
                0x0000000000408843                fsync
                0x000000000040884d                fdatasync
                0x0000000000408857                open
                0x000000000040887d                close
                0x000000000040889b                pipe
                0x00000000004088bc                fpathconf
                0x00000000004088c6                pathconf
                0x00000000004088d0                __gethostname
                0x00000000004088fc                gethostname
                0x0000000000408920                sethostname
                0x000000000040893e                getlogin
                0x000000000040896a                setlogin
                0x0000000000408990                getusername
                0x0000000000408a0a                setusername
                0x0000000000408a7e                ttyname
                0x0000000000408abb                ttyname_r
                0x0000000000408ac5                isatty
                0x0000000000408ae8                getopt
                0x0000000000408af2                xxx_todo_int133
 .text          0x0000000000408b1a      0x165 termios.o
                0x0000000000408b1a                tcgetattr
                0x0000000000408b38                tcsetattr
                0x0000000000408bb1                tcsendbreak
                0x0000000000408bbb                tcdrain
                0x0000000000408bc5                tcflush
                0x0000000000408bcf                tcflow
                0x0000000000408bd9                cfmakeraw
                0x0000000000408c4b                cfgetispeed
                0x0000000000408c56                cfgetospeed
                0x0000000000408c61                cfsetispeed
                0x0000000000408c6b                cfsetospeed
                0x0000000000408c75                cfsetspeed
 .text          0x0000000000408c7f       0x3d ioctl.o
                0x0000000000408c7f                ioctl
 .text          0x0000000000408cbc       0x28 stubs.o
                0x0000000000408cbc                gramado_system_call
                0x0000000000409000                . = ALIGN (0x1000)
 *fill*         0x0000000000408ce4      0x31c 

.iplt           0x0000000000409000        0x0
 .iplt          0x0000000000409000        0x0 crt0.o

.rodata         0x0000000000409000     0x1201
 .rodata        0x0000000000409000       0x36 crt0.o
 *fill*         0x0000000000409036        0x2 
 .rodata        0x0000000000409038      0x10c main.o
 .rodata        0x0000000000409144      0x505 api.o
 *fill*         0x0000000000409649       0x17 
 .rodata        0x0000000000409660      0x100 ctype.o
                0x0000000000409660                _ctype
 .rodata        0x0000000000409760      0x4a9 stdio.o
                0x0000000000409a40                hex2ascii_data
 *fill*         0x0000000000409c09        0x7 
 .rodata        0x0000000000409c10      0x560 stdlib.o
 .rodata        0x000000000040a170        0x6 conio.o
 *fill*         0x000000000040a176        0x2 
 .rodata        0x000000000040a178       0x89 unistd.o

.eh_frame       0x000000000040a204     0x3010
 .eh_frame      0x000000000040a204       0x34 crt0.o
 .eh_frame      0x000000000040a238       0x84 main.o
                                         0x9c (size before relaxing)
 .eh_frame      0x000000000040a2bc      0xdac api.o
                                        0xdc4 (size before relaxing)
 .eh_frame      0x000000000040b068      0xde8 stdio.o
                                        0xe00 (size before relaxing)
 .eh_frame      0x000000000040be50      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040c450      0x4e0 string.o
                                        0x4f8 (size before relaxing)
 .eh_frame      0x000000000040c930       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040c9d0      0x680 unistd.o
                                        0x698 (size before relaxing)
 .eh_frame      0x000000000040d050      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x000000000040d1d0       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040d1f0       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040d214        0x0
 .rel.got       0x000000000040d214        0x0 crt0.o
 .rel.iplt      0x000000000040d214        0x0 crt0.o
 .rel.text      0x000000000040d214        0x0 crt0.o

.data           0x000000000040d220      0xde0
                0x000000000040d220                data = .
                0x000000000040d220                _data = .
                0x000000000040d220                __data = .
 *(.data)
 .data          0x000000000040d220       0x24 crt0.o
 *fill*         0x000000000040d244       0x1c 
 .data          0x000000000040d260      0x440 main.o
 .data          0x000000000040d6a0      0x440 api.o
 .data          0x000000000040dae0        0x0 ctype.o
 .data          0x000000000040dae0        0x0 stdio.o
 .data          0x000000000040dae0        0x8 stdlib.o
                0x000000000040dae0                _infinity
 .data          0x000000000040dae8        0x0 string.o
 .data          0x000000000040dae8        0x0 conio.o
 .data          0x000000000040dae8        0x0 unistd.o
 .data          0x000000000040dae8        0x0 termios.o
 .data          0x000000000040dae8        0x0 ioctl.o
 .data          0x000000000040dae8        0x0 stubs.o
                0x000000000040e000                . = ALIGN (0x1000)
 *fill*         0x000000000040dae8      0x518 

.got            0x000000000040e000        0x0
 .got           0x000000000040e000        0x0 crt0.o

.got.plt        0x000000000040e000        0x0
 .got.plt       0x000000000040e000        0x0 crt0.o

.igot.plt       0x000000000040e000        0x0
 .igot.plt      0x000000000040e000        0x0 crt0.o

.bss            0x000000000040e000    0x126e4
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
 .bss           0x0000000000416020     0x8000 stdlib.o
 .bss           0x000000000041e020        0x4 string.o
 .bss           0x000000000041e024        0x0 conio.o
 *fill*         0x000000000041e024       0x1c 
 .bss           0x000000000041e040      0x11f unistd.o
                0x000000000041e040                __execv_environ
 .bss           0x000000000041e15f        0x0 termios.o
 .bss           0x000000000041e15f        0x0 ioctl.o
 .bss           0x000000000041e15f        0x0 stubs.o
                0x000000000041f000                . = ALIGN (0x1000)
 *fill*         0x000000000041e15f      0xea1 
 COMMON         0x000000000041f000      0xd08 crt0.o
                0x000000000041f000                g_cursor_x
                0x000000000041f004                stdout
                0x000000000041f008                __libc_tty_id
                0x000000000041f00c                g_char_attrib
                0x000000000041f010                g_rows
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
 COMMON         0x000000000041fd08       0x28 main.o
                0x000000000041fd08                CurrentWindow
                0x000000000041fd0c                idleError
                0x000000000041fd10                ServerStatus
                0x000000000041fd14                ApplicationInfo
                0x000000000041fd18                BufferInfo
                0x000000000041fd1c                CursorInfo
                0x000000000041fd20                idleStatus
                0x000000000041fd24                __current_runlevel
                0x000000000041fd28                ClientAreaInfo
                0x000000000041fd2c                current_semaphore
 *fill*         0x000000000041fd30       0x10 
 COMMON         0x000000000041fd40      0x440 api.o
                0x000000000041fd40                heapList
                0x0000000000420140                libcHeap
                0x0000000000420144                dialogbox_button2
                0x0000000000420148                messagebox_button1
                0x000000000042014c                heap_start
                0x0000000000420150                g_available_heap
                0x0000000000420154                g_heap_pointer
                0x0000000000420158                HEAP_SIZE
                0x000000000042015c                dialogbox_button1
                0x0000000000420160                first_responder
                0x0000000000420164                heap_end
                0x0000000000420168                __mb_current_button
                0x000000000042016c                HEAP_END
                0x0000000000420170                messagebox_button2
                0x0000000000420174                Heap
                0x0000000000420178                heapCount
                0x000000000042017c                HEAP_START
 COMMON         0x0000000000420180        0x4 stdio.o
                0x0000000000420180                environ
 *fill*         0x0000000000420184       0x1c 
 COMMON         0x00000000004201a0      0x484 stdlib.o
                0x00000000004201a0                mm_prev_pointer
                0x00000000004201c0                mmblockList
                0x00000000004205c0                last_valid
                0x00000000004205c4                randseed
                0x00000000004205c8                mmblockCount
                0x00000000004205cc                last_size
                0x00000000004205e0                __ptsname_buffer
                0x0000000000420620                current_mmblock
 *fill*         0x0000000000420624       0x1c 
 COMMON         0x0000000000420640       0xa4 unistd.o
                0x0000000000420640                errno
                0x0000000000420644                optarg
                0x0000000000420648                opterr
                0x000000000042064c                my( *)
                0x0000000000420650                optind
                0x0000000000420660                __Hostname_buffer
                0x00000000004206a0                __Login_buffer
                0x00000000004206e0                optopt
                0x00000000004206e4                end = .
                0x00000000004206e4                _end = .
                0x00000000004206e4                __end = .
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
OUTPUT(INIT2.BIN elf32-i386)

.comment        0x0000000000000000       0x3a
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x29 main.o
                                         0x2a (size before relaxing)
 .comment       0x000000000000003a       0x12 api.o
 .comment       0x000000000000003a       0x12 ctype.o
 .comment       0x000000000000003a       0x12 stdio.o
 .comment       0x000000000000003a       0x12 stdlib.o
 .comment       0x000000000000003a       0x12 string.o
 .comment       0x000000000000003a       0x12 conio.o
 .comment       0x000000000000003a       0x12 unistd.o
 .comment       0x000000000000003a       0x12 termios.o
 .comment       0x000000000000003a       0x12 ioctl.o
 .comment       0x000000000000003a       0x12 stubs.o

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
