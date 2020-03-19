
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
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
g_available_heap    0x4               api.o
g_heap_pointer      0x4               api.o
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
 .text          0x0000000000401000      0x108 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401108      0x282 main.o
                0x0000000000401108                __debug_print
                0x000000000040113a                idleLoop
                0x0000000000401158                initMain
                0x000000000040115d                driverInitialize
                0x0000000000401180                driverUninitialize
                0x00000000004011a3                idleServices
                0x0000000000401209                idleInit
                0x0000000000401227                enable_maskable_interrupts
                0x000000000040122f                main
 .text          0x000000000040138a     0x2164 api.o
                0x000000000040138a                system_call
                0x00000000004013b2                gde_system
                0x00000000004017ba                system1
                0x00000000004017db                system2
                0x00000000004017fc                system3
                0x000000000040181d                system4
                0x000000000040183e                system5
                0x000000000040185f                system6
                0x0000000000401880                system7
                0x00000000004018a1                system8
                0x00000000004018c2                system9
                0x00000000004018e3                system10
                0x0000000000401904                system11
                0x0000000000401925                system12
                0x0000000000401946                system13
                0x0000000000401967                system14
                0x0000000000401988                system15
                0x00000000004019a9                gde_refresh_buffer
                0x0000000000401a81                gde_print_string
                0x0000000000401a87                gde_vsync
                0x0000000000401a9f                gws_vsync
                0x0000000000401aac                gde_system_procedure
                0x0000000000401aef                __gde_set_cursor
                0x0000000000401b09                __gde_put_char
                0x0000000000401b0f                gde_load_bitmap_16x16
                0x0000000000401b28                gde_shutdown
                0x0000000000401b42                gde_init_background
                0x0000000000401b48                gde_message_box
                0x0000000000401e4d                mbProcedure
                0x0000000000402009                gde_dialog_box
                0x00000000004023c4                dbProcedure
                0x000000000040243a                call_kernel
                0x0000000000402562                call_gui
                0x00000000004025f7                gde_create_window
                0x0000000000402670                gde_register_window
                0x0000000000402698                gde_close_window
                0x00000000004026c0                gde_set_focus
                0x00000000004026e8                gde_get_focus
                0x00000000004026fd                gde_kill_focus
                0x0000000000402725                gde_set_active_window
                0x000000000040274d                gde_get_active_window
                0x0000000000402762                gde_show_current_process_info
                0x0000000000402778                gde_resize_window
                0x0000000000402795                gde_redraw_window
                0x00000000004027b2                gde_replace_window
                0x00000000004027cc                gde_maximize_window
                0x00000000004027eb                gde_minimize_window
                0x000000000040280a                gde_update_window
                0x000000000040282c                gde_get_foregroung_window
                0x0000000000402842                gde_set_foregroung_window
                0x000000000040285e                gde_exit
                0x000000000040287b                gde_kill
                0x0000000000402881                gde_dead_thread_collector
                0x0000000000402897                gde_strncmp
                0x00000000004028fa                gde_show_backbuffer
                0x0000000000402910                gde_reboot
                0x0000000000402929                gde_set_cursor
                0x0000000000402941                gde_get_cursor
                0x0000000000402947                gde_get_cursor_x
                0x0000000000402962                gde_get_cursor_y
                0x000000000040297d                gde_get_client_area_rect
                0x0000000000402995                gde_set_client_area_rect
                0x00000000004029b4                gde_create_process
                0x00000000004029cd                gde_create_thread
                0x00000000004029e6                gde_start_thread
                0x0000000000402a02                gde_fopen
                0x0000000000402a2e                gde_save_file
                0x0000000000402a81                gde_down
                0x0000000000402ad6                gde_up
                0x0000000000402b2b                gde_enter_critical_section
                0x0000000000402b66                gde_exit_critical_section
                0x0000000000402b7f                gde_p
                0x0000000000402b85                gde_v
                0x0000000000402b8b                gde_initialize_critical_section
                0x0000000000402ba4                gde_begin_paint
                0x0000000000402baf                gde_end_paint
                0x0000000000402bba                gde_put_char
                0x0000000000402bd6                gde_def_dialog
                0x0000000000402be0                gde_get_system_metrics
                0x0000000000402bfe                gde_dialog
                0x0000000000402c97                gde_getchar
                0x0000000000402cb2                gde_display_bmp
                0x00000000004030b9                gde_send_message_to_process
                0x00000000004030fc                gde_send_message_to_thread
                0x000000000040313f                gde_send_message
                0x0000000000403175                gde_draw_text
                0x00000000004031b4                gde_get_ws_screen_window
                0x00000000004031cc                gde_get_ws_main_window
                0x00000000004031e4                gde_create_timer
                0x0000000000403204                gde_get_systime_info
                0x0000000000403225                gde_show_window
                0x0000000000403244                gde_start_terminal
                0x00000000004032b8                gde_update_statusbar
                0x00000000004032d6                gde_get_pid
                0x0000000000403301                gde_get_screen_window
                0x000000000040331c                gde_get_background_window
                0x0000000000403337                gde_get_main_window
                0x0000000000403352                gde_getprocessname
                0x00000000004033cf                gde_getthreadname
                0x000000000040344c                gde_get_process_stats
                0x000000000040346a                gde_get_thread_stats
                0x0000000000403488                gde_debug_print
                0x00000000004034aa                gde_clone_and_execute
                0x00000000004034c7                gde_setup_net_buffer
 .text          0x00000000004034ee        0x0 ctype.o
 .text          0x00000000004034ee     0x2ab7 stdio.o
                0x0000000000403536                stdio_atoi
                0x00000000004035fd                stdio_fntos
                0x0000000000403727                remove
                0x0000000000403731                fclose
                0x0000000000403752                fopen
                0x0000000000403773                creat
                0x000000000040379a                scroll
                0x0000000000403867                puts
                0x0000000000403882                fread
                0x00000000004038a3                fwrite
                0x0000000000403c85                printf3
                0x0000000000403ca2                printf_atoi
                0x0000000000403d93                printf_i2hex
                0x0000000000403df5                printf2
                0x0000000000403f7a                stdio_nextline
                0x0000000000403fb8                nlsprintf
                0x0000000000403ff6                sprintf
                0x000000000040404b                putchar
                0x0000000000404096                libc_set_output_mode
                0x00000000004040da                outbyte
                0x00000000004042ce                _outbyte
                0x00000000004042fd                input
                0x000000000040445d                getchar
                0x000000000040448b                stdioInitialize
                0x000000000040462d                fflush
                0x000000000040464e                fprintf
                0x00000000004046dc                fputs
                0x00000000004046fd                nputs
                0x0000000000404738                gets
                0x00000000004047c7                ungetc
                0x00000000004047e8                ftell
                0x0000000000404809                fileno
                0x000000000040482a                fgetc
                0x000000000040484b                feof
                0x000000000040486c                ferror
                0x000000000040488d                fseek
                0x00000000004048ae                fputc
                0x0000000000404949                stdioSetCursor
                0x0000000000404964                stdioGetCursorX
                0x000000000040497f                stdioGetCursorY
                0x000000000040499a                scanf
                0x0000000000404b3b                sscanf
                0x0000000000404cf6                kvprintf
                0x0000000000405b60                printf
                0x0000000000405b8e                printf_draw
                0x0000000000405bd6                vfprintf
                0x0000000000405c4e                vprintf
                0x0000000000405c6d                stdout_printf
                0x0000000000405c99                stderr_printf
                0x0000000000405cc5                perror
                0x0000000000405cdc                rewind
                0x0000000000405d06                snprintf
                0x0000000000405d1a                stdio_initialize_standard_streams
                0x0000000000405d45                libcStartTerminal
                0x0000000000405db9                setbuf
                0x0000000000405ddb                setbuffer
                0x0000000000405dfd                setlinebuf
                0x0000000000405e1f                setvbuf
                0x0000000000405e40                filesize
                0x0000000000405e89                fileread
                0x0000000000405ed7                dprintf
                0x0000000000405ee1                vdprintf
                0x0000000000405eeb                vsprintf
                0x0000000000405ef5                vsnprintf
                0x0000000000405eff                vscanf
                0x0000000000405f09                vsscanf
                0x0000000000405f13                vfscanf
                0x0000000000405f1d                tmpnam
                0x0000000000405f27                tmpnam_r
                0x0000000000405f31                tempnam
                0x0000000000405f3b                tmpfile
                0x0000000000405f45                fdopen
                0x0000000000405f4f                freopen
                0x0000000000405f59                open_memstream
                0x0000000000405f63                open_wmemstream
                0x0000000000405f6d                fmemopen
                0x0000000000405f77                fgetpos
                0x0000000000405f81                fsetpos
                0x0000000000405f8b                fpurge
                0x0000000000405f95                __fpurge
                0x0000000000405f9b                ctermid
 .text          0x0000000000405fa5     0x114a stdlib.o
                0x0000000000405fc2                rtGetHeapStart
                0x0000000000405fcc                rtGetHeapEnd
                0x0000000000405fd6                rtGetHeapPointer
                0x0000000000405fe0                rtGetAvailableHeap
                0x0000000000405fea                heapSetLibcHeap
                0x000000000040609d                heapAllocateMemory
                0x00000000004062cf                FreeHeap
                0x00000000004062d9                heapInit
                0x000000000040646c                stdlibInitMM
                0x00000000004064cf                libcInitRT
                0x00000000004064f1                mktemp
                0x00000000004064fb                rand
                0x0000000000406518                srand
                0x0000000000406526                xmalloc
                0x0000000000406558                stdlib_die
                0x000000000040658e                malloc
                0x00000000004065ca                realloc
                0x0000000000406607                free
                0x000000000040660d                calloc
                0x0000000000406653                zmalloc
                0x000000000040668f                system
                0x0000000000406a53                stdlib_strncmp
                0x0000000000406ab6                __findenv
                0x0000000000406b81                getenv
                0x0000000000406bae                setenv
                0x0000000000406bb8                unsetenv
                0x0000000000406bc2                atoi
                0x0000000000406c89                reverse
                0x0000000000406cf1                itoa
                0x0000000000406d9f                abs
                0x0000000000406daf                strtod
                0x0000000000406fe0                strtof
                0x0000000000406ffc                strtold
                0x000000000040700f                atof
                0x0000000000407021                labs
                0x0000000000407031                mkstemp
                0x000000000040703b                mkostemp
                0x0000000000407045                mkstemps
                0x000000000040704f                mkostemps
                0x0000000000407059                ptsname
                0x000000000040707f                ptsname_r
                0x00000000004070a6                posix_openpt
                0x00000000004070c1                grantpt
                0x00000000004070cb                getpt
                0x00000000004070d5                unlockpt
                0x00000000004070df                getprogname
                0x00000000004070e9                setprogname
 .text          0x00000000004070ef      0xb2b string.o
                0x00000000004070ef                strcoll
                0x0000000000407108                memsetw
                0x0000000000407134                memcmp
                0x0000000000407199                strdup
                0x00000000004071eb                strndup
                0x000000000040724c                strnchr
                0x0000000000407285                strrchr
                0x00000000004072c0                strtoimax
                0x00000000004072ca                strtoumax
                0x00000000004072d4                strcasecmp
                0x000000000040733c                strncpy
                0x0000000000407392                strcmp
                0x00000000004073f7                strncmp
                0x000000000040745a                memset
                0x00000000004074a1                memoryZeroMemory
                0x00000000004074c8                memcpy
                0x0000000000407505                strcpy
                0x0000000000407539                strlcpy
                0x0000000000407598                strcat
                0x00000000004075c7                strchrnul
                0x00000000004075ec                strlcat
                0x000000000040767c                strncat
                0x00000000004076de                bcopy
                0x000000000040770b                bzero
                0x000000000040772c                strlen
                0x000000000040775a                strnlen
                0x0000000000407795                strpbrk
                0x00000000004077e3                strsep
                0x0000000000407861                strreplace
                0x000000000040789c                strcspn
                0x000000000040793b                strspn
                0x00000000004079da                strtok_r
                0x0000000000407ac1                strtok
                0x0000000000407ad9                strchr
                0x0000000000407b05                memmove
                0x0000000000407b86                memscan
                0x0000000000407bba                strstr
 .text          0x0000000000407c1a       0x89 conio.o
                0x0000000000407c1a                putch
                0x0000000000407c3e                cputs
                0x0000000000407c73                getch
                0x0000000000407c8b                getche
 .text          0x0000000000407ca3      0x5a9 unistd.o
                0x0000000000407ca3                execv
                0x0000000000407cc1                execve
                0x0000000000407d20                write
                0x0000000000407d68                exit
                0x0000000000407d88                fast_fork
                0x0000000000407db0                fork
                0x0000000000407de6                sys_fork
                0x0000000000407e1c                setuid
                0x0000000000407e37                getuid
                0x0000000000407e52                geteuid
                0x0000000000407e5c                getpid
                0x0000000000407e74                getppid
                0x0000000000407e8c                getgid
                0x0000000000407ea7                dup
                0x0000000000407ec1                dup2
                0x0000000000407edd                dup3
                0x0000000000407efb                fcntl
                0x0000000000407f05                getpriority
                0x0000000000407f0f                setpriority
                0x0000000000407f19                nice
                0x0000000000407f23                pause
                0x0000000000407f2d                mkdir
                0x0000000000407f41                rmdir
                0x0000000000407f4b                link
                0x0000000000407f55                unlink
                0x0000000000407f5f                mlock
                0x0000000000407f69                munlock
                0x0000000000407f73                mlockall
                0x0000000000407f7d                munlockall
                0x0000000000407f87                sysconf
                0x0000000000407f91                fsync
                0x0000000000407f9b                fdatasync
                0x0000000000407fa5                open
                0x0000000000407fcb                close
                0x0000000000407fe9                pipe
                0x000000000040800a                fpathconf
                0x0000000000408014                pathconf
                0x000000000040801e                __gethostname
                0x000000000040804a                gethostname
                0x0000000000408071                sethostname
                0x0000000000408092                getlogin
                0x00000000004080be                setlogin
                0x00000000004080e4                getusername
                0x0000000000408161                setusername
                0x00000000004081d8                ttyname
                0x0000000000408215                ttyname_r
                0x000000000040821f                isatty
                0x0000000000408242                getopt
 .text          0x000000000040824c      0x165 termios.o
                0x000000000040824c                tcgetattr
                0x000000000040826a                tcsetattr
                0x00000000004082e3                tcsendbreak
                0x00000000004082ed                tcdrain
                0x00000000004082f7                tcflush
                0x0000000000408301                tcflow
                0x000000000040830b                cfmakeraw
                0x000000000040837d                cfgetispeed
                0x0000000000408388                cfgetospeed
                0x0000000000408393                cfsetispeed
                0x000000000040839d                cfsetospeed
                0x00000000004083a7                cfsetspeed
 .text          0x00000000004083b1       0x3d ioctl.o
                0x00000000004083b1                ioctl
 .text          0x00000000004083ee       0x28 stubs.o
                0x00000000004083ee                gramado_system_call
                0x0000000000409000                . = ALIGN (0x1000)
 *fill*         0x0000000000408416      0xbea 

.iplt           0x0000000000409000        0x0
 .iplt          0x0000000000409000        0x0 crt0.o

.rodata         0x0000000000409000     0x10e1
 .rodata        0x0000000000409000       0x5a crt0.o
 *fill*         0x000000000040905a        0x2 
 .rodata        0x000000000040905c      0x184 main.o
 .rodata        0x00000000004091e0      0x505 api.o
 *fill*         0x00000000004096e5       0x1b 
 .rodata        0x0000000000409700      0x100 ctype.o
                0x0000000000409700                _ctype
 .rodata        0x0000000000409800      0x329 stdio.o
                0x0000000000409960                hex2ascii_data
 *fill*         0x0000000000409b29        0x7 
 .rodata        0x0000000000409b30      0x520 stdlib.o
 .rodata        0x000000000040a050        0x6 conio.o
 *fill*         0x000000000040a056        0x2 
 .rodata        0x000000000040a058       0x89 unistd.o

.eh_frame       0x000000000040a0e4     0x2d74
 .eh_frame      0x000000000040a0e4       0x34 crt0.o
 .eh_frame      0x000000000040a118      0x15c main.o
                                        0x174 (size before relaxing)
 .eh_frame      0x000000000040a274      0xd4c api.o
                                        0xd64 (size before relaxing)
 .eh_frame      0x000000000040afc0      0xb74 stdio.o
                                        0xb8c (size before relaxing)
 .eh_frame      0x000000000040bb34      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040c134      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000040c5f4       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040c694      0x600 unistd.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040cc94      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x000000000040ce14       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040ce34       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040ce58        0x0
 .rel.got       0x000000000040ce58        0x0 crt0.o
 .rel.iplt      0x000000000040ce58        0x0 crt0.o
 .rel.text      0x000000000040ce58        0x0 crt0.o

.data           0x000000000040ce60     0x11a0
                0x000000000040ce60                data = .
                0x000000000040ce60                _data = .
                0x000000000040ce60                __data = .
 *(.data)
 .data          0x000000000040ce60       0x14 crt0.o
 *fill*         0x000000000040ce74        0xc 
 .data          0x000000000040ce80      0x440 main.o
 .data          0x000000000040d2c0      0x440 api.o
 .data          0x000000000040d700        0x0 ctype.o
 .data          0x000000000040d700        0x0 stdio.o
 .data          0x000000000040d700        0x8 stdlib.o
                0x000000000040d700                _infinity
 .data          0x000000000040d708        0x0 string.o
 .data          0x000000000040d708        0x0 conio.o
 .data          0x000000000040d708        0x0 unistd.o
 .data          0x000000000040d708        0x0 termios.o
 .data          0x000000000040d708        0x0 ioctl.o
 .data          0x000000000040d708        0x0 stubs.o
                0x000000000040e000                . = ALIGN (0x1000)
 *fill*         0x000000000040d708      0x8f8 

.got            0x000000000040e000        0x0
 .got           0x000000000040e000        0x0 crt0.o

.got.plt        0x000000000040e000        0x0
 .got.plt       0x000000000040e000        0x0 crt0.o

.igot.plt       0x000000000040e000        0x0
 .igot.plt      0x000000000040e000        0x0 crt0.o

.bss            0x000000000040e000    0x126c4
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
 COMMON         0x0000000000420180        0x0 stdio.o
 COMMON         0x0000000000420180      0x484 stdlib.o
                0x0000000000420180                mm_prev_pointer
                0x00000000004201a0                mmblockList
                0x00000000004205a0                last_valid
                0x00000000004205a4                randseed
                0x00000000004205a8                mmblockCount
                0x00000000004205ac                last_size
                0x00000000004205c0                __ptsname_buffer
                0x0000000000420600                current_mmblock
 *fill*         0x0000000000420604       0x1c 
 COMMON         0x0000000000420620       0xa4 unistd.o
                0x0000000000420620                errno
                0x0000000000420624                optarg
                0x0000000000420628                opterr
                0x000000000042062c                my__p
                0x0000000000420630                optind
                0x0000000000420640                __Hostname_buffer
                0x0000000000420680                __Login_buffer
                0x00000000004206c0                optopt
                0x00000000004206c4                end = .
                0x00000000004206c4                _end = .
                0x00000000004206c4                __end = .
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
OUTPUT(ZINIT.BIN elf32-i386)

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
