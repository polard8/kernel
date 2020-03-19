
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


.text           0x0000000000401000     0x6000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000       0xe8 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010e8      0x11c main.o
                0x00000000004010e8                main
 .text          0x0000000000401204        0x0 ctype.o
 .text          0x0000000000401204     0x354a stdio.o
                0x000000000040124c                stdio_atoi
                0x0000000000401313                stdio_fntos
                0x000000000040143d                remove
                0x0000000000401447                fclose
                0x0000000000401475                fopen
                0x00000000004014a2                creat
                0x00000000004014c9                scroll
                0x0000000000401596                puts
                0x00000000004015b1                clearerr
                0x00000000004015d3                fread
                0x0000000000401673                fwrite
                0x000000000040167d                prompt_putchar
                0x00000000004016cd                prompt_put_string
                0x00000000004016fa                prompt_strcat
                0x0000000000401727                prompt_flush
                0x000000000040178b                prompt_clean
                0x0000000000401b9b                printf3
                0x0000000000401bb8                printf_atoi
                0x0000000000401ca9                printf_i2hex
                0x0000000000401d0b                printf2
                0x0000000000401e90                stdio_nextline
                0x0000000000401ece                nlsprintf
                0x0000000000401f0c                sprintf
                0x0000000000401f61                putchar
                0x0000000000401f7d                libc_set_output_mode
                0x0000000000401fc1                outbyte
                0x000000000040217f                _outbyte
                0x00000000004021ae                input
                0x000000000040230b                getchar
                0x0000000000402339                fflush
                0x0000000000402343                fprintf
                0x0000000000402376                fputs
                0x00000000004023c6                nputs
                0x0000000000402401                __gets
                0x0000000000402432                fgets
                0x00000000004024b6                gets
                0x0000000000402545                ungetc
                0x00000000004025a0                ftell
                0x00000000004025aa                fileno
                0x00000000004025c4                __gramado__getc
                0x000000000040266f                fgetc
                0x0000000000402692                getc
                0x00000000004026a8                putc
                0x00000000004026c1                feof
                0x00000000004026d9                ferror
                0x00000000004026f1                fseek
                0x00000000004026fb                __gramado__putc
                0x00000000004027a6                debug_print
                0x00000000004027c8                __serenity_fflush
                0x0000000000402869                __serenity_fputc
                0x000000000040290e                __serenity_putc
                0x0000000000402927                fputc
                0x000000000040294d                stdioSetCursor
                0x0000000000402968                stdioGetCursorX
                0x0000000000402983                stdioGetCursorY
                0x000000000040299e                scanf
                0x0000000000402b3f                sscanf
                0x0000000000402cfa                kvprintf
                0x0000000000403b64                printf
                0x0000000000403b92                printf_draw
                0x0000000000403bda                vfprintf
                0x0000000000403c52                vprintf
                0x0000000000403c81                stdout_printf
                0x0000000000403cbd                stderr_printf
                0x0000000000403cf9                perror
                0x0000000000403d10                rewind
                0x0000000000403d16                snprintf
                0x0000000000403d2a                stdio_initialize_standard_streams
                0x0000000000403d55                libcStartTerminal
                0x0000000000403dc9                setbuf
                0x0000000000403dcf                setbuffer
                0x0000000000403df9                setlinebuf
                0x0000000000403dff                setvbuf
                0x0000000000403e09                filesize
                0x0000000000403e49                fileread
                0x0000000000403e94                dprintf
                0x0000000000403e9e                vdprintf
                0x0000000000404127                Wirzenius_Torvalds_vsprintf
                0x00000000004044fc                Torvalds_printf
                0x000000000040453c                vsnprintf
                0x0000000000404546                vscanf
                0x0000000000404550                vsscanf
                0x000000000040455a                vfscanf
                0x0000000000404571                tmpnam
                0x000000000040457b                tmpnam_r
                0x0000000000404585                tempnam
                0x000000000040458f                tmpfile
                0x0000000000404599                fdopen
                0x00000000004045a3                freopen
                0x00000000004045ba                open_memstream
                0x00000000004045c4                open_wmemstream
                0x00000000004045ce                fmemopen
                0x00000000004045d8                fgetpos
                0x000000000040460f                fsetpos
                0x0000000000404626                fpurge
                0x000000000040463d                __fpurge
                0x0000000000404646                ctermid
                0x0000000000404650                stdioInitialize
 .text          0x000000000040474e     0x1118 stdlib.o
                0x000000000040476b                rtGetHeapStart
                0x0000000000404775                rtGetHeapEnd
                0x000000000040477f                rtGetHeapPointer
                0x0000000000404789                rtGetAvailableHeap
                0x0000000000404793                heapSetLibcHeap
                0x0000000000404846                heapAllocateMemory
                0x0000000000404a78                FreeHeap
                0x0000000000404a82                heapInit
                0x0000000000404c15                stdlibInitMM
                0x0000000000404c78                libcInitRT
                0x0000000000404ca1                mktemp
                0x0000000000404cab                rand
                0x0000000000404cc8                srand
                0x0000000000404cd6                xmalloc
                0x0000000000404d08                stdlib_die
                0x0000000000404d3e                malloc
                0x0000000000404d7a                realloc
                0x0000000000404db7                free
                0x0000000000404dbd                calloc
                0x0000000000404e03                zmalloc
                0x0000000000404e3f                system
                0x0000000000405203                stdlib_strncmp
                0x0000000000405266                __findenv
                0x0000000000405331                getenv
                0x000000000040535e                setenv
                0x0000000000405368                unsetenv
                0x0000000000405372                atoi
                0x0000000000405439                reverse
                0x00000000004054a1                itoa
                0x000000000040554f                abs
                0x000000000040555f                strtod
                0x0000000000405790                strtof
                0x00000000004057ac                strtold
                0x00000000004057bf                atof
                0x00000000004057d1                labs
                0x00000000004057e1                mkstemp
                0x00000000004057eb                mkostemp
                0x00000000004057f5                mkstemps
                0x00000000004057ff                mkostemps
                0x0000000000405809                ptsname
                0x0000000000405813                ptsname_r
                0x000000000040581d                posix_openpt
                0x0000000000405838                grantpt
                0x0000000000405842                getpt
                0x000000000040584c                unlockpt
                0x0000000000405856                getprogname
                0x0000000000405860                setprogname
 .text          0x0000000000405866      0xc19 string.o
                0x0000000000405891                strcoll
                0x00000000004058aa                memsetw
                0x00000000004058d6                memcmp
                0x000000000040593b                strdup
                0x000000000040598d                strndup
                0x00000000004059ee                strnchr
                0x0000000000405a27                strrchr
                0x0000000000405a62                strtoimax
                0x0000000000405a6c                strtoumax
                0x0000000000405a76                strcasecmp
                0x0000000000405ade                strncpy
                0x0000000000405b34                strcmp
                0x0000000000405b99                strncmp
                0x0000000000405bfc                memset
                0x0000000000405c43                memoryZeroMemory
                0x0000000000405c6a                memcpy
                0x0000000000405ca7                strcpy
                0x0000000000405cdb                strlcpy
                0x0000000000405d3a                strcat
                0x0000000000405d69                strchrnul
                0x0000000000405d8e                strlcat
                0x0000000000405e1e                strncat
                0x0000000000405e80                bcopy
                0x0000000000405ead                bzero
                0x0000000000405ece                strlen
                0x0000000000405efc                strnlen
                0x0000000000405f37                strpbrk
                0x0000000000405f85                strsep
                0x0000000000406003                strreplace
                0x000000000040603e                strcspn
                0x00000000004060dd                strspn
                0x000000000040617c                strtok_r
                0x0000000000406263                strtok
                0x000000000040627b                strchr
                0x00000000004062a7                memmove
                0x0000000000406328                memscan
                0x000000000040635c                strstr
                0x00000000004063bc                rindex
                0x00000000004063cf                strxfrm
                0x0000000000406421                strerror
                0x000000000040642b                strerror_r
                0x0000000000406435                strsignal
                0x000000000040643f                strtoupper
 .text          0x000000000040647f       0x33 time.o
                0x000000000040647f                time
                0x00000000004064a8                gettimeofday
 .text          0x00000000004064b2      0x6e1 unistd.o
                0x00000000004064b2                execv
                0x00000000004064d0                execve
                0x000000000040652f                read_ttyList
                0x000000000040655d                write_ttyList
                0x000000000040658b                read_VC
                0x00000000004065b9                write_VC
                0x00000000004065e7                read
                0x0000000000406615                write
                0x0000000000406643                exit
                0x0000000000406663                fast_fork
                0x000000000040668b                fork
                0x00000000004066c1                sys_fork
                0x00000000004066f7                setuid
                0x0000000000406712                getuid
                0x000000000040672d                geteuid
                0x0000000000406737                getpid
                0x000000000040674f                getppid
                0x0000000000406767                getgid
                0x0000000000406782                dup
                0x000000000040679c                dup2
                0x00000000004067b8                dup3
                0x00000000004067d6                fcntl
                0x00000000004067e0                getpriority
                0x00000000004067ea                setpriority
                0x00000000004067f4                nice
                0x00000000004067fe                pause
                0x0000000000406808                mkdir
                0x000000000040681c                rmdir
                0x0000000000406826                link
                0x0000000000406830                unlink
                0x000000000040683a                mlock
                0x0000000000406844                munlock
                0x000000000040684e                mlockall
                0x0000000000406858                munlockall
                0x0000000000406862                sysconf
                0x000000000040686c                fsync
                0x0000000000406876                fdatasync
                0x0000000000406880                sync
                0x0000000000406886                syncfs
                0x0000000000406890                open
                0x00000000004068b6                close
                0x00000000004068d4                pipe
                0x00000000004068f5                fpathconf
                0x00000000004068ff                pathconf
                0x0000000000406909                __gethostname
                0x0000000000406935                gethostname
                0x000000000040695c                sethostname
                0x000000000040697d                getlogin
                0x00000000004069a9                setlogin
                0x00000000004069cf                getusername
                0x0000000000406a4c                setusername
                0x0000000000406ac3                ttyname
                0x0000000000406b00                ttyname_r
                0x0000000000406b0a                isatty
                0x0000000000406b2d                getopt
                0x0000000000406b37                alarm
                0x0000000000406b41                brk
                0x0000000000406b4b                execvp
                0x0000000000406b55                execvpe
                0x0000000000406b5f                chdir
                0x0000000000406b69                fchdir
                0x0000000000406b73                sleep
                0x0000000000406b7d                _exit
 .text          0x0000000000406b93      0x165 termios.o
                0x0000000000406b93                tcgetattr
                0x0000000000406bb1                tcsetattr
                0x0000000000406c2a                tcsendbreak
                0x0000000000406c34                tcdrain
                0x0000000000406c3e                tcflush
                0x0000000000406c48                tcflow
                0x0000000000406c52                cfmakeraw
                0x0000000000406cc4                cfgetispeed
                0x0000000000406ccf                cfgetospeed
                0x0000000000406cda                cfsetispeed
                0x0000000000406ce4                cfsetospeed
                0x0000000000406cee                cfsetspeed
 .text          0x0000000000406cf8       0x3d ioctl.o
                0x0000000000406cf8                ioctl
 .text          0x0000000000406d35       0x28 stubs.o
                0x0000000000406d35                gramado_system_call
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x0000000000406d5d      0x2a3 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 crt0.o

.rodata         0x0000000000407000      0xc51
 .rodata        0x0000000000407000       0x22 crt0.o
 .rodata        0x0000000000407022       0x40 main.o
 *fill*         0x0000000000407062       0x1e 
 .rodata        0x0000000000407080      0x100 ctype.o
                0x0000000000407080                _ctype
 .rodata        0x0000000000407180      0x524 stdio.o
                0x00000000004073c0                hex2ascii_data
 *fill*         0x00000000004076a4        0x4 
 .rodata        0x00000000004076a8      0x520 stdlib.o
 .rodata        0x0000000000407bc8       0x89 unistd.o

.eh_frame       0x0000000000407c54     0x23c0
 .eh_frame      0x0000000000407c54       0x34 crt0.o
 .eh_frame      0x0000000000407c88       0x28 main.o
                                         0x40 (size before relaxing)
 .eh_frame      0x0000000000407cb0      0xde0 stdio.o
                                        0xdf8 (size before relaxing)
 .eh_frame      0x0000000000408a90      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x0000000000409090      0x5a0 string.o
                                        0x5b8 (size before relaxing)
 .eh_frame      0x0000000000409630       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x0000000000409670      0x7e0 unistd.o
                                        0x7f8 (size before relaxing)
 .eh_frame      0x0000000000409e50      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x0000000000409fd0       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000409ff0       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040a014        0x0
 .rel.got       0x000000000040a014        0x0 crt0.o
 .rel.iplt      0x000000000040a014        0x0 crt0.o
 .rel.text      0x000000000040a014        0x0 crt0.o

.data           0x000000000040a018      0xfe8
                0x000000000040a018                data = .
                0x000000000040a018                _data = .
                0x000000000040a018                __data = .
 *(.data)
 .data          0x000000000040a018       0x14 crt0.o
 .data          0x000000000040a02c        0x4 main.o
                0x000000000040a02c                the_prompt
 .data          0x000000000040a030        0x0 ctype.o
 .data          0x000000000040a030        0x0 stdio.o
 .data          0x000000000040a030        0x8 stdlib.o
                0x000000000040a030                _infinity
 .data          0x000000000040a038        0x0 string.o
 .data          0x000000000040a038        0x0 time.o
 .data          0x000000000040a038        0x0 unistd.o
 .data          0x000000000040a038        0x0 termios.o
 .data          0x000000000040a038        0x0 ioctl.o
 .data          0x000000000040a038        0x0 stubs.o
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a038      0xfc8 

.got            0x000000000040b000        0x0
 .got           0x000000000040b000        0x0 crt0.o

.got.plt        0x000000000040b000        0x0
 .got.plt       0x000000000040b000        0x0 crt0.o

.igot.plt       0x000000000040b000        0x0
 .igot.plt      0x000000000040b000        0x0 crt0.o

.bss            0x000000000040b000     0xa644
                0x000000000040b000                bss = .
                0x000000000040b000                _bss = .
                0x000000000040b000                __bss = .
 *(.bss)
 .bss           0x000000000040b000        0x0 crt0.o
 .bss           0x000000000040b000        0x0 main.o
 .bss           0x000000000040b000        0x0 ctype.o
 .bss           0x000000000040b000      0x421 stdio.o
 *fill*         0x000000000040b421       0x1f 
 .bss           0x000000000040b440     0x8020 stdlib.o
                0x000000000040b440                environ
 .bss           0x0000000000413460        0x4 string.o
 .bss           0x0000000000413464        0x0 time.o
 *fill*         0x0000000000413464       0x1c 
 .bss           0x0000000000413480      0x19f unistd.o
                0x0000000000413480                __execv_environ
 .bss           0x000000000041361f        0x0 termios.o
 .bss           0x000000000041361f        0x0 ioctl.o
 .bss           0x000000000041361f        0x0 stubs.o
                0x0000000000414000                . = ALIGN (0x1000)
 *fill*         0x000000000041361f      0x9e1 
 COMMON         0x0000000000414000      0xd08 crt0.o
                0x0000000000414000                g_cursor_x
                0x0000000000414004                stdout
                0x0000000000414008                __libc_tty_id
                0x000000000041400c                g_char_attrib
                0x0000000000414010                g_rows
                0x0000000000414020                Streams
                0x00000000004140a0                g_using_gui
                0x00000000004140c0                prompt_out
                0x00000000004144c0                g_columns
                0x00000000004144c4                prompt_pos
                0x00000000004144c8                stdin
                0x00000000004144cc                prompt_status
                0x00000000004144e0                prompt_err
                0x00000000004148e0                stderr
                0x0000000000414900                prompt
                0x0000000000414d00                g_cursor_y
                0x0000000000414d04                prompt_max
 COMMON         0x0000000000414d08        0x0 stdio.o
 *fill*         0x0000000000414d08       0x18 
 COMMON         0x0000000000414d20      0x878 stdlib.o
                0x0000000000414d20                mm_prev_pointer
                0x0000000000414d40                mmblockList
                0x0000000000415140                last_valid
                0x0000000000415160                heapList
                0x0000000000415560                libcHeap
                0x0000000000415564                randseed
                0x0000000000415568                heap_start
                0x000000000041556c                g_available_heap
                0x0000000000415570                g_heap_pointer
                0x0000000000415574                HEAP_SIZE
                0x0000000000415578                mmblockCount
                0x000000000041557c                last_size
                0x0000000000415580                heap_end
                0x0000000000415584                HEAP_END
                0x0000000000415588                Heap
                0x000000000041558c                current_mmblock
                0x0000000000415590                heapCount
                0x0000000000415594                HEAP_START
 *fill*         0x0000000000415598        0x8 
 COMMON         0x00000000004155a0       0xa4 unistd.o
                0x00000000004155a0                errno
                0x00000000004155a4                optarg
                0x00000000004155a8                opterr
                0x00000000004155ac                optind
                0x00000000004155c0                __Hostname_buffer
                0x0000000000415600                __Login_buffer
                0x0000000000415640                optopt
                0x0000000000415644                end = .
                0x0000000000415644                _end = .
                0x0000000000415644                __end = .
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
LOAD stubs.o
OUTPUT(SH7.BIN elf32-i386)

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
                0x0000000000000000        0x0 stubs.o
