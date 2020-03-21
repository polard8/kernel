
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
__libc_tty_id       0x4               crt0.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
errno               0x4               unistd.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
Streams             0x80              crt0.o
optarg              0x4               unistd.o
g_using_gui         0x4               crt0.o
opterr              0x4               unistd.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
environ             0x4               stdio.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
optind              0x4               unistd.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
__Hostname_buffer   0x40              unistd.o
prompt_status       0x4               crt0.o
__Login_buffer      0x40              unistd.o
prompt_err          0x400             crt0.o
heap_end            0x4               stdlib.o
stderr              0x4               crt0.o
optopt              0x4               unistd.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
g_cursor_y          0x4               crt0.o
Heap                0x4               stdlib.o
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
 .text          0x0000000000401000       0xf2 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010f2      0xdc4 main.o
                0x0000000000401256                cons
                0x000000000040128c                proc
                0x000000000040130e                intern
                0x00000000004013ad                getobj
                0x000000000040147e                getlist
                0x00000000004014f6                print_obj
                0x000000000040165c                assoc
                0x0000000000401695                evlist
                0x00000000004016eb                eval
                0x0000000000401ae0                add
                0x0000000000401b28                sub
                0x0000000000401b70                mul
                0x0000000000401bc0                main
 .text          0x0000000000401eb6        0x0 ctype.o
 .text          0x0000000000401eb6     0x39a3 stdio.o
                0x0000000000401efe                stdio_atoi
                0x0000000000401fc5                stdio_fntos
                0x00000000004020ef                remove
                0x00000000004020f9                fclose
                0x0000000000402153                fopen
                0x00000000004021dc                fopen2
                0x0000000000402333                scroll
                0x0000000000402400                clearerr
                0x0000000000402422                fread
                0x00000000004024c2                fwrite
                0x00000000004024cc                prompt_putchar
                0x000000000040251c                prompt_put_string
                0x0000000000402549                prompt_strcat
                0x0000000000402576                prompt_flush
                0x00000000004025da                prompt_clean
                0x00000000004029ea                printf3
                0x0000000000402a07                printf_atoi
                0x0000000000402af8                printf_i2hex
                0x0000000000402b5a                printf2
                0x0000000000402cdf                stdio_nextline
                0x0000000000402d1d                nlsprintf
                0x0000000000402d5b                sprintf
                0x0000000000402db0                libc_set_output_mode
                0x0000000000402df4                outbyte
                0x0000000000402fb2                _outbyte
                0x0000000000402fe1                input
                0x000000000040313e                fprintf
                0x0000000000403171                nputs
                0x00000000004031ac                __gets
                0x00000000004031dd                ungetc
                0x000000000040322f                ftell
                0x0000000000403270                fileno
                0x000000000040328a                fflush
                0x00000000004032a0                __fflush
                0x0000000000403362                __getc
                0x000000000040340d                __putc
                0x00000000004034b2                getc
                0x00000000004034c8                putc
                0x00000000004034e1                fgetc
                0x00000000004034f7                fputc
                0x0000000000403510                getchar
                0x0000000000403529                putchar
                0x0000000000403545                gets
                0x0000000000403587                puts
                0x00000000004035c1                fgets
                0x000000000040361c                fputs
                0x0000000000403650                getw
                0x0000000000403691                putw
                0x00000000004036c0                fgets2
                0x0000000000403744                fputs2
                0x0000000000403794                gets2
                0x0000000000403823                puts2
                0x000000000040383e                getchar2
                0x000000000040386c                feof
                0x0000000000403884                ferror
                0x000000000040389c                fseek
                0x00000000004038a6                __gramado__putc
                0x0000000000403951                debug_print
                0x0000000000403973                __serenity_fputc
                0x000000000040398c                stdioSetCursor
                0x00000000004039a7                stdioGetCursorX
                0x00000000004039c2                stdioGetCursorY
                0x00000000004039dd                scanf
                0x0000000000403b7e                sscanf
                0x0000000000403d39                kvprintf
                0x0000000000404ba3                printf
                0x0000000000404bd1                printf_draw
                0x0000000000404c19                vfprintf
                0x0000000000404c91                vprintf
                0x0000000000404cc0                stdout_printf
                0x0000000000404cfc                stderr_printf
                0x0000000000404d38                perror
                0x0000000000404d4f                rewind
                0x0000000000404d55                snprintf
                0x0000000000404d69                stdio_initialize_standard_streams
                0x0000000000404d94                libcStartTerminal
                0x0000000000404e08                setbuf
                0x0000000000404e0e                setbuffer
                0x0000000000404e38                setlinebuf
                0x0000000000404e3e                setvbuf
                0x0000000000404ebd                filesize
                0x0000000000404f03                fileread
                0x0000000000404f51                dprintf
                0x0000000000404f5b                vdprintf
                0x00000000004051e4                Wirzenius_Torvalds_vsprintf
                0x00000000004055b9                Torvalds_printf
                0x00000000004055f9                vsnprintf
                0x0000000000405603                vscanf
                0x000000000040560d                vsscanf
                0x0000000000405617                vfscanf
                0x000000000040562e                tmpnam
                0x0000000000405638                tmpnam_r
                0x0000000000405642                tempnam
                0x000000000040564c                tmpfile
                0x0000000000405656                fdopen
                0x0000000000405660                freopen
                0x0000000000405677                open_memstream
                0x0000000000405681                open_wmemstream
                0x000000000040568b                fmemopen
                0x0000000000405695                fgetpos
                0x00000000004056d2                fsetpos
                0x00000000004056e9                fpurge
                0x0000000000405700                __fpurge
                0x0000000000405709                ctermid
                0x0000000000405713                stdioInitialize
 .text          0x0000000000405859     0x11ff stdlib.o
                0x0000000000405876                rtGetHeapStart
                0x0000000000405880                rtGetHeapEnd
                0x000000000040588a                rtGetHeapPointer
                0x0000000000405894                rtGetAvailableHeap
                0x000000000040589e                heapSetLibcHeap
                0x0000000000405951                heapAllocateMemory
                0x0000000000405b83                FreeHeap
                0x0000000000405b8d                heapInit
                0x0000000000405d20                stdlibInitMM
                0x0000000000405d83                libcInitRT
                0x0000000000405dac                mktemp
                0x0000000000405db6                rand
                0x0000000000405dd3                srand
                0x0000000000405de1                xmalloc
                0x0000000000405e13                stdlib_die
                0x0000000000405e49                malloc
                0x0000000000405e85                realloc
                0x0000000000405ec2                free
                0x0000000000405ec8                calloc
                0x0000000000405f0e                zmalloc
                0x0000000000405f4a                system
                0x000000000040630e                stdlib_strncmp
                0x00000000004063c4                v7_getenv
                0x0000000000406400                __findenv
                0x0000000000406521                getenv
                0x000000000040654e                setenv
                0x0000000000406558                unsetenv
                0x0000000000406562                atoi
                0x0000000000406629                reverse
                0x0000000000406691                itoa
                0x000000000040673f                abs
                0x000000000040674f                strtod
                0x0000000000406980                strtof
                0x000000000040699c                strtold
                0x00000000004069af                atof
                0x00000000004069c1                labs
                0x00000000004069d1                mkstemp
                0x00000000004069db                mkostemp
                0x00000000004069e5                mkstemps
                0x00000000004069ef                mkostemps
                0x00000000004069f9                ptsname
                0x0000000000406a03                ptsname_r
                0x0000000000406a0d                posix_openpt
                0x0000000000406a2a                grantpt
                0x0000000000406a34                unlockpt
                0x0000000000406a3e                getpt
                0x0000000000406a48                getprogname
                0x0000000000406a52                setprogname
 .text          0x0000000000406a58      0xc44 string.o
                0x0000000000406a83                strcoll
                0x0000000000406a9c                memsetw
                0x0000000000406ac8                memcmp
                0x0000000000406b2d                strdup
                0x0000000000406b7f                strndup
                0x0000000000406be0                strnchr
                0x0000000000406c19                strrchr
                0x0000000000406c54                strtoimax
                0x0000000000406c5e                strtoumax
                0x0000000000406c68                strcasecmp
                0x0000000000406cd0                strncpy
                0x0000000000406d26                strcmp
                0x0000000000406d92                strncmp
                0x0000000000406dec                memset
                0x0000000000406e33                memoryZeroMemory
                0x0000000000406e5a                memcpy
                0x0000000000406e97                strcpy
                0x0000000000406ecb                strlcpy
                0x0000000000406f2a                strcat
                0x0000000000406f59                strchrnul
                0x0000000000406f7e                strlcat
                0x000000000040700e                strncat
                0x0000000000407070                bcopy
                0x000000000040709d                bzero
                0x00000000004070be                strlen
                0x00000000004070ec                strnlen
                0x0000000000407127                strpbrk
                0x0000000000407175                strsep
                0x00000000004071f3                strreplace
                0x000000000040722e                strcspn
                0x00000000004072cd                strspn
                0x000000000040736c                strtok_r
                0x0000000000407453                strtok
                0x000000000040746b                strchr
                0x0000000000407497                memmove
                0x0000000000407518                memscan
                0x000000000040754c                strstr
                0x00000000004075ac                index
                0x00000000004075d9                rindex
                0x00000000004075ec                strxfrm
                0x000000000040763e                strerror
                0x0000000000407648                strerror_r
                0x0000000000407652                strsignal
                0x000000000040765c                strtoupper
 .text          0x000000000040769c       0x33 time.o
                0x000000000040769c                time
                0x00000000004076c5                gettimeofday
 .text          0x00000000004076cf      0x798 unistd.o
                0x00000000004076cf                execv
                0x00000000004076ed                execve
                0x000000000040774c                read_ttyList
                0x000000000040777a                write_ttyList
                0x00000000004077a8                read_tty
                0x00000000004077d6                write_tty
                0x0000000000407804                read_VC
                0x0000000000407832                write_VC
                0x0000000000407860                read
                0x000000000040788b                write
                0x00000000004078b6                exit
                0x00000000004078d6                fast_fork
                0x00000000004078fe                fork
                0x0000000000407934                sys_fork
                0x000000000040796a                setuid
                0x0000000000407985                getuid
                0x00000000004079a0                geteuid
                0x00000000004079aa                getpid
                0x00000000004079c2                getppid
                0x00000000004079da                getgid
                0x00000000004079f5                dup
                0x0000000000407a0f                dup2
                0x0000000000407a2b                dup3
                0x0000000000407a49                getpriority
                0x0000000000407a53                setpriority
                0x0000000000407a5d                nice
                0x0000000000407a67                pause
                0x0000000000407a71                mkdir
                0x0000000000407a85                rmdir
                0x0000000000407a8f                link
                0x0000000000407a99                unlink
                0x0000000000407aa3                mlock
                0x0000000000407aad                munlock
                0x0000000000407ab7                mlockall
                0x0000000000407ac1                munlockall
                0x0000000000407acb                sysconf
                0x0000000000407ad5                fsync
                0x0000000000407adf                fdatasync
                0x0000000000407ae9                sync
                0x0000000000407aef                syncfs
                0x0000000000407af9                close
                0x0000000000407b17                pipe
                0x0000000000407b38                fpathconf
                0x0000000000407b42                pathconf
                0x0000000000407b4c                __gethostname
                0x0000000000407b78                gethostname
                0x0000000000407b9c                sethostname
                0x0000000000407bba                getlogin
                0x0000000000407be6                setlogin
                0x0000000000407c0c                getusername
                0x0000000000407c86                setusername
                0x0000000000407cfa                ttyname
                0x0000000000407d37                ttyname_r
                0x0000000000407d41                isatty
                0x0000000000407d64                getopt
                0x0000000000407d6e                alarm
                0x0000000000407d78                brk
                0x0000000000407d82                execvp
                0x0000000000407d8c                execvpe
                0x0000000000407d96                chown
                0x0000000000407da0                fchown
                0x0000000000407daa                lchown
                0x0000000000407db4                chdir
                0x0000000000407dbe                fchdir
                0x0000000000407dc8                sleep
                0x0000000000407dd2                _exit
                0x0000000000407de8                swab_w
                0x0000000000407e28                swab
                0x0000000000407e3f                lseek
                0x0000000000407e49                tell
                0x0000000000407e5d                access
 .text          0x0000000000407e67      0x213 termios.o
                0x0000000000407e67                tcgetpgrp
                0x0000000000407e94                tcsetpgrp
                0x0000000000407eb9                tcgetattr
                0x0000000000407ed7                tcsetattr
                0x0000000000407f50                tcsendbreak
                0x0000000000407f5a                tcdrain
                0x0000000000407f77                tcflush
                0x0000000000407f81                tcflow
                0x0000000000407f8b                cfmakeraw
                0x0000000000408005                cfgetispeed
                0x000000000040801d                cfgetospeed
                0x0000000000408035                cfsetispeed
                0x000000000040804c                cfsetospeed
                0x0000000000408063                cfsetspeed
 .text          0x000000000040807a      0x11f fcntl.o
                0x000000000040807a                fcntl
                0x0000000000408091                openat
                0x00000000004080cc                open
                0x0000000000408168                creat
                0x000000000040818f                flock
 .text          0x0000000000408199       0x3d ioctl.o
                0x0000000000408199                ioctl
 .text          0x00000000004081d6       0x28 stubs.o
                0x00000000004081d6                gramado_system_call
                0x0000000000409000                . = ALIGN (0x1000)
 *fill*         0x00000000004081fe      0xe02 

.iplt           0x0000000000409000        0x0
 .iplt          0x0000000000409000        0x0 crt0.o

.rodata         0x0000000000409000      0xd88
 .rodata        0x0000000000409000       0x8a crt0.o
 .rodata        0x000000000040908a       0xaf main.o
 *fill*         0x0000000000409139        0x7 
 .rodata        0x0000000000409140      0x100 ctype.o
                0x0000000000409140                _ctype
 .rodata        0x0000000000409240      0x524 stdio.o
                0x0000000000409480                hex2ascii_data
 *fill*         0x0000000000409764        0x4 
 .rodata        0x0000000000409768      0x560 stdlib.o
 .rodata        0x0000000000409cc8       0x89 unistd.o
 *fill*         0x0000000000409d51        0x3 
 .rodata        0x0000000000409d54       0x34 fcntl.o

.eh_frame       0x0000000000409d88     0x292c
 .eh_frame      0x0000000000409d88       0x34 crt0.o
 .eh_frame      0x0000000000409dbc      0x244 main.o
                                        0x25c (size before relaxing)
 .eh_frame      0x000000000040a000      0xee8 stdio.o
                                        0xf00 (size before relaxing)
 .eh_frame      0x000000000040aee8      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x000000000040b530      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040baf0       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040bb30      0x8e0 unistd.o
                                        0x8f8 (size before relaxing)
 .eh_frame      0x000000000040c410      0x1c0 termios.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x000000000040c5d0       0xa0 fcntl.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040c670       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040c690       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040c6b4        0x0
 .rel.got       0x000000000040c6b4        0x0 crt0.o
 .rel.iplt      0x000000000040c6b4        0x0 crt0.o
 .rel.text      0x000000000040c6b4        0x0 crt0.o

.data           0x000000000040c6c0      0x940
                0x000000000040c6c0                data = .
                0x000000000040c6c0                _data = .
                0x000000000040c6c0                __data = .
 *(.data)
 .data          0x000000000040c6c0       0x50 crt0.o
 .data          0x000000000040c710        0x0 main.o
 .data          0x000000000040c710        0x0 ctype.o
 .data          0x000000000040c710        0x0 stdio.o
 .data          0x000000000040c710        0x8 stdlib.o
                0x000000000040c710                _infinity
 .data          0x000000000040c718        0x0 string.o
 .data          0x000000000040c718        0x0 time.o
 .data          0x000000000040c718        0x0 unistd.o
 .data          0x000000000040c718        0x0 termios.o
 .data          0x000000000040c718        0x0 fcntl.o
 .data          0x000000000040c718        0x0 ioctl.o
 .data          0x000000000040c718        0x0 stubs.o
                0x000000000040d000                . = ALIGN (0x1000)
 *fill*         0x000000000040c718      0x8e8 

.got            0x000000000040d000        0x0
 .got           0x000000000040d000        0x0 crt0.o

.got.plt        0x000000000040d000        0x0
 .got.plt       0x000000000040d000        0x0 crt0.o

.igot.plt       0x000000000040d000        0x0
 .igot.plt      0x000000000040d000        0x0 crt0.o

.bss            0x000000000040d000     0xa644
                0x000000000040d000                bss = .
                0x000000000040d000                _bss = .
                0x000000000040d000                __bss = .
 *(.bss)
 .bss           0x000000000040d000        0x0 crt0.o
 .bss           0x000000000040d000       0xd8 main.o
 .bss           0x000000000040d0d8        0x0 ctype.o
 *fill*         0x000000000040d0d8        0x8 
 .bss           0x000000000040d0e0      0x421 stdio.o
 *fill*         0x000000000040d501       0x1f 
 .bss           0x000000000040d520     0x8000 stdlib.o
 .bss           0x0000000000415520        0x4 string.o
 .bss           0x0000000000415524        0x0 time.o
 *fill*         0x0000000000415524       0x1c 
 .bss           0x0000000000415540      0x19f unistd.o
                0x0000000000415540                __execv_environ
 .bss           0x00000000004156df        0x0 termios.o
 .bss           0x00000000004156df        0x0 fcntl.o
 .bss           0x00000000004156df        0x0 ioctl.o
 .bss           0x00000000004156df        0x0 stubs.o
                0x0000000000416000                . = ALIGN (0x1000)
 *fill*         0x00000000004156df      0x921 
 COMMON         0x0000000000416000      0xd08 crt0.o
                0x0000000000416000                g_cursor_x
                0x0000000000416004                stdout
                0x0000000000416008                __libc_tty_id
                0x000000000041600c                g_char_attrib
                0x0000000000416010                g_rows
                0x0000000000416020                Streams
                0x00000000004160a0                g_using_gui
                0x00000000004160c0                prompt_out
                0x00000000004164c0                g_columns
                0x00000000004164c4                prompt_pos
                0x00000000004164c8                stdin
                0x00000000004164cc                prompt_status
                0x00000000004164e0                prompt_err
                0x00000000004168e0                stderr
                0x0000000000416900                prompt
                0x0000000000416d00                g_cursor_y
                0x0000000000416d04                prompt_max
 COMMON         0x0000000000416d08        0x4 stdio.o
                0x0000000000416d08                environ
 *fill*         0x0000000000416d0c       0x14 
 COMMON         0x0000000000416d20      0x878 stdlib.o
                0x0000000000416d20                mm_prev_pointer
                0x0000000000416d40                mmblockList
                0x0000000000417140                last_valid
                0x0000000000417160                heapList
                0x0000000000417560                libcHeap
                0x0000000000417564                randseed
                0x0000000000417568                heap_start
                0x000000000041756c                g_available_heap
                0x0000000000417570                g_heap_pointer
                0x0000000000417574                HEAP_SIZE
                0x0000000000417578                mmblockCount
                0x000000000041757c                last_size
                0x0000000000417580                heap_end
                0x0000000000417584                HEAP_END
                0x0000000000417588                Heap
                0x000000000041758c                current_mmblock
                0x0000000000417590                heapCount
                0x0000000000417594                HEAP_START
 *fill*         0x0000000000417598        0x8 
 COMMON         0x00000000004175a0       0xa4 unistd.o
                0x00000000004175a0                errno
                0x00000000004175a4                optarg
                0x00000000004175a8                opterr
                0x00000000004175ac                optind
                0x00000000004175c0                __Hostname_buffer
                0x0000000000417600                __Login_buffer
                0x0000000000417640                optopt
                0x0000000000417644                end = .
                0x0000000000417644                _end = .
                0x0000000000417644                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD unistd.o
LOAD termios.o
LOAD fcntl.o
LOAD ioctl.o
LOAD stubs.o
OUTPUT(LISP.BIN elf32-i386)

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
 .comment       0x0000000000000011       0x12 fcntl.o
 .comment       0x0000000000000011       0x12 ioctl.o
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
                0x0000000000000000        0x0 fcntl.o
 .note.GNU-stack
                0x0000000000000000        0x0 ioctl.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
