
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
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
my__p               0x4               unistd.o
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
 .text          0x0000000000401000      0x128 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401128       0x91 main.o
                0x0000000000401128                main
 .text          0x00000000004011b9        0x0 ctype.o
 .text          0x00000000004011b9     0x2a7e stdio.o
                0x0000000000401201                stdio_atoi
                0x00000000004012c8                stdio_fntos
                0x00000000004013f2                remove
                0x00000000004013fc                fclose
                0x000000000040141d                fopen
                0x000000000040143e                creat
                0x0000000000401465                scroll
                0x0000000000401532                puts
                0x000000000040154d                fread
                0x000000000040156e                fwrite
                0x0000000000401950                printf3
                0x000000000040196d                printf_atoi
                0x0000000000401a5e                printf_i2hex
                0x0000000000401ac0                printf2
                0x0000000000401c45                stdio_nextline
                0x0000000000401c83                nlsprintf
                0x0000000000401cc1                sprintf
                0x0000000000401d16                putchar
                0x0000000000401d61                libc_set_output_mode
                0x0000000000401da5                outbyte
                0x0000000000401f63                _outbyte
                0x0000000000401f92                input
                0x00000000004020ef                getchar
                0x000000000040211d                stdioInitialize
                0x00000000004022bf                fflush
                0x00000000004022e0                fprintf
                0x000000000040236e                fputs
                0x000000000040238f                nputs
                0x00000000004023ca                gets
                0x0000000000402459                ungetc
                0x000000000040247a                ftell
                0x000000000040249b                fileno
                0x00000000004024bc                fgetc
                0x00000000004024dd                feof
                0x00000000004024fe                ferror
                0x000000000040251f                fseek
                0x0000000000402540                fputc
                0x00000000004025db                stdioSetCursor
                0x00000000004025f6                stdioGetCursorX
                0x0000000000402611                stdioGetCursorY
                0x000000000040262c                scanf
                0x00000000004027cd                sscanf
                0x0000000000402988                kvprintf
                0x00000000004037f2                printf
                0x0000000000403820                printf_draw
                0x0000000000403868                vfprintf
                0x00000000004038e0                vprintf
                0x00000000004038ff                stdout_printf
                0x000000000040392b                stderr_printf
                0x0000000000403957                perror
                0x000000000040396e                rewind
                0x0000000000403998                snprintf
                0x00000000004039ac                stdio_initialize_standard_streams
                0x00000000004039d7                libcStartTerminal
                0x0000000000403a4b                setbuf
                0x0000000000403a6d                setbuffer
                0x0000000000403a8f                setlinebuf
                0x0000000000403ab1                setvbuf
                0x0000000000403ad2                filesize
                0x0000000000403b1b                fileread
                0x0000000000403b69                dprintf
                0x0000000000403b73                vdprintf
                0x0000000000403b7d                vsprintf
                0x0000000000403b87                vsnprintf
                0x0000000000403b91                vscanf
                0x0000000000403b9b                vsscanf
                0x0000000000403ba5                vfscanf
                0x0000000000403baf                tmpnam
                0x0000000000403bb9                tmpnam_r
                0x0000000000403bc3                tempnam
                0x0000000000403bcd                tmpfile
                0x0000000000403bd7                fdopen
                0x0000000000403be1                freopen
                0x0000000000403beb                open_memstream
                0x0000000000403bf5                open_wmemstream
                0x0000000000403bff                fmemopen
                0x0000000000403c09                fgetpos
                0x0000000000403c13                fsetpos
                0x0000000000403c1d                fpurge
                0x0000000000403c27                __fpurge
                0x0000000000403c2d                ctermid
 .text          0x0000000000403c37     0x1111 stdlib.o
                0x0000000000403c54                rtGetHeapStart
                0x0000000000403c5e                rtGetHeapEnd
                0x0000000000403c68                rtGetHeapPointer
                0x0000000000403c72                rtGetAvailableHeap
                0x0000000000403c7c                heapSetLibcHeap
                0x0000000000403d2f                heapAllocateMemory
                0x0000000000403f61                FreeHeap
                0x0000000000403f6b                heapInit
                0x00000000004040fe                stdlibInitMM
                0x0000000000404161                libcInitRT
                0x0000000000404183                mktemp
                0x000000000040418d                rand
                0x00000000004041aa                srand
                0x00000000004041b8                xmalloc
                0x00000000004041ea                stdlib_die
                0x0000000000404220                malloc
                0x000000000040425c                realloc
                0x0000000000404299                free
                0x000000000040429f                calloc
                0x00000000004042e5                zmalloc
                0x0000000000404321                system
                0x00000000004046e5                stdlib_strncmp
                0x0000000000404748                __findenv
                0x0000000000404813                getenv
                0x0000000000404840                setenv
                0x000000000040484a                unsetenv
                0x0000000000404854                atoi
                0x000000000040491b                reverse
                0x0000000000404983                itoa
                0x0000000000404a31                abs
                0x0000000000404a41                strtod
                0x0000000000404c72                strtof
                0x0000000000404c8e                strtold
                0x0000000000404ca1                atof
                0x0000000000404cb3                labs
                0x0000000000404cc3                mkstemp
                0x0000000000404ccd                mkostemp
                0x0000000000404cd7                mkstemps
                0x0000000000404ce1                mkostemps
                0x0000000000404ceb                ptsname
                0x0000000000404cf5                ptsname_r
                0x0000000000404cff                posix_openpt
                0x0000000000404d1a                grantpt
                0x0000000000404d24                getpt
                0x0000000000404d2e                unlockpt
                0x0000000000404d38                getprogname
                0x0000000000404d42                setprogname
 .text          0x0000000000404d48      0xb2b string.o
                0x0000000000404d48                strcoll
                0x0000000000404d61                memsetw
                0x0000000000404d8d                memcmp
                0x0000000000404df2                strdup
                0x0000000000404e44                strndup
                0x0000000000404ea5                strnchr
                0x0000000000404ede                strrchr
                0x0000000000404f19                strtoimax
                0x0000000000404f23                strtoumax
                0x0000000000404f2d                strcasecmp
                0x0000000000404f95                strncpy
                0x0000000000404feb                strcmp
                0x0000000000405050                strncmp
                0x00000000004050b3                memset
                0x00000000004050fa                memoryZeroMemory
                0x0000000000405121                memcpy
                0x000000000040515e                strcpy
                0x0000000000405192                strlcpy
                0x00000000004051f1                strcat
                0x0000000000405220                strchrnul
                0x0000000000405245                strlcat
                0x00000000004052d5                strncat
                0x0000000000405337                bcopy
                0x0000000000405364                bzero
                0x0000000000405385                strlen
                0x00000000004053b3                strnlen
                0x00000000004053ee                strpbrk
                0x000000000040543c                strsep
                0x00000000004054ba                strreplace
                0x00000000004054f5                strcspn
                0x0000000000405594                strspn
                0x0000000000405633                strtok_r
                0x000000000040571a                strtok
                0x0000000000405732                strchr
                0x000000000040575e                memmove
                0x00000000004057df                memscan
                0x0000000000405813                strstr
 .text          0x0000000000405873       0x33 time.o
                0x0000000000405873                time
                0x000000000040589c                gettimeofday
 .text          0x00000000004058a6      0x5a9 unistd.o
                0x00000000004058a6                execv
                0x00000000004058c4                execve
                0x0000000000405923                write
                0x000000000040596b                exit
                0x000000000040598b                fast_fork
                0x00000000004059b3                fork
                0x00000000004059e9                sys_fork
                0x0000000000405a1f                setuid
                0x0000000000405a3a                getuid
                0x0000000000405a55                geteuid
                0x0000000000405a5f                getpid
                0x0000000000405a77                getppid
                0x0000000000405a8f                getgid
                0x0000000000405aaa                dup
                0x0000000000405ac4                dup2
                0x0000000000405ae0                dup3
                0x0000000000405afe                fcntl
                0x0000000000405b08                getpriority
                0x0000000000405b12                setpriority
                0x0000000000405b1c                nice
                0x0000000000405b26                pause
                0x0000000000405b30                mkdir
                0x0000000000405b44                rmdir
                0x0000000000405b4e                link
                0x0000000000405b58                unlink
                0x0000000000405b62                mlock
                0x0000000000405b6c                munlock
                0x0000000000405b76                mlockall
                0x0000000000405b80                munlockall
                0x0000000000405b8a                sysconf
                0x0000000000405b94                fsync
                0x0000000000405b9e                fdatasync
                0x0000000000405ba8                open
                0x0000000000405bce                close
                0x0000000000405bec                pipe
                0x0000000000405c0d                fpathconf
                0x0000000000405c17                pathconf
                0x0000000000405c21                __gethostname
                0x0000000000405c4d                gethostname
                0x0000000000405c74                sethostname
                0x0000000000405c95                getlogin
                0x0000000000405cc1                setlogin
                0x0000000000405ce7                getusername
                0x0000000000405d64                setusername
                0x0000000000405ddb                ttyname
                0x0000000000405e18                ttyname_r
                0x0000000000405e22                isatty
                0x0000000000405e45                getopt
 .text          0x0000000000405e4f      0x165 termios.o
                0x0000000000405e4f                tcgetattr
                0x0000000000405e6d                tcsetattr
                0x0000000000405ee6                tcsendbreak
                0x0000000000405ef0                tcdrain
                0x0000000000405efa                tcflush
                0x0000000000405f04                tcflow
                0x0000000000405f0e                cfmakeraw
                0x0000000000405f80                cfgetispeed
                0x0000000000405f8b                cfgetospeed
                0x0000000000405f96                cfsetispeed
                0x0000000000405fa0                cfsetospeed
                0x0000000000405faa                cfsetspeed
 .text          0x0000000000405fb4       0x3d ioctl.o
                0x0000000000405fb4                ioctl
 .text          0x0000000000405ff1       0x28 stubs.o
                0x0000000000405ff1                gramado_system_call
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x0000000000406019      0xfe7 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 crt0.o

.rodata         0x0000000000407000      0xa79
 .rodata        0x0000000000407000       0x74 crt0.o
 .rodata        0x0000000000407074       0x29 main.o
 *fill*         0x000000000040709d        0x3 
 .rodata        0x00000000004070a0      0x100 ctype.o
                0x00000000004070a0                _ctype
 .rodata        0x00000000004071a0      0x329 stdio.o
                0x0000000000407300                hex2ascii_data
 *fill*         0x00000000004074c9        0x7 
 .rodata        0x00000000004074d0      0x520 stdlib.o
 .rodata        0x00000000004079f0       0x89 unistd.o

.eh_frame       0x0000000000407a7c     0x1ea0
 .eh_frame      0x0000000000407a7c       0x34 crt0.o
 .eh_frame      0x0000000000407ab0       0x34 main.o
                                         0x4c (size before relaxing)
 .eh_frame      0x0000000000407ae4      0xb74 stdio.o
                                        0xb8c (size before relaxing)
 .eh_frame      0x0000000000408658      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x0000000000408c58      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x0000000000409118       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x0000000000409158      0x600 unistd.o
                                        0x618 (size before relaxing)
 .eh_frame      0x0000000000409758      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x00000000004098d8       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x00000000004098f8       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040991c        0x0
 .rel.got       0x000000000040991c        0x0 crt0.o
 .rel.iplt      0x000000000040991c        0x0 crt0.o
 .rel.text      0x000000000040991c        0x0 crt0.o

.data           0x0000000000409920      0x6e0
                0x0000000000409920                data = .
                0x0000000000409920                _data = .
                0x0000000000409920                __data = .
 *(.data)
 .data          0x0000000000409920       0x14 crt0.o
 .data          0x0000000000409934        0x0 main.o
 .data          0x0000000000409934        0x0 ctype.o
 .data          0x0000000000409934        0x0 stdio.o
 *fill*         0x0000000000409934        0x4 
 .data          0x0000000000409938        0x8 stdlib.o
                0x0000000000409938                _infinity
 .data          0x0000000000409940        0x0 string.o
 .data          0x0000000000409940        0x0 time.o
 .data          0x0000000000409940        0x0 unistd.o
 .data          0x0000000000409940        0x0 termios.o
 .data          0x0000000000409940        0x0 ioctl.o
 .data          0x0000000000409940        0x0 stubs.o
                0x000000000040a000                . = ALIGN (0x1000)
 *fill*         0x0000000000409940      0x6c0 

.got            0x000000000040a000        0x0
 .got           0x000000000040a000        0x0 crt0.o

.got.plt        0x000000000040a000        0x0
 .got.plt       0x000000000040a000        0x0 crt0.o

.igot.plt       0x000000000040a000        0x0
 .igot.plt      0x000000000040a000        0x0 crt0.o

.bss            0x000000000040a000     0xa644
                0x000000000040a000                bss = .
                0x000000000040a000                _bss = .
                0x000000000040a000                __bss = .
 *(.bss)
 .bss           0x000000000040a000        0x0 crt0.o
 .bss           0x000000000040a000        0x0 main.o
 .bss           0x000000000040a000        0x0 ctype.o
 .bss           0x000000000040a000        0x9 stdio.o
 *fill*         0x000000000040a009       0x17 
 .bss           0x000000000040a020     0x8020 stdlib.o
                0x000000000040a020                environ
 .bss           0x0000000000412040        0x4 string.o
 .bss           0x0000000000412044        0x0 time.o
 *fill*         0x0000000000412044       0x1c 
 .bss           0x0000000000412060      0x19f unistd.o
                0x0000000000412060                __execv_environ
 .bss           0x00000000004121ff        0x0 termios.o
 .bss           0x00000000004121ff        0x0 ioctl.o
 .bss           0x00000000004121ff        0x0 stubs.o
                0x0000000000413000                . = ALIGN (0x1000)
 *fill*         0x00000000004121ff      0xe01 
 COMMON         0x0000000000413000      0xd08 crt0.o
                0x0000000000413000                g_cursor_x
                0x0000000000413004                stdout
                0x0000000000413008                g_char_attrib
                0x000000000041300c                g_rows
                0x0000000000413020                Streams
                0x00000000004130a0                g_using_gui
                0x00000000004130c0                prompt_out
                0x00000000004134c0                g_columns
                0x00000000004134c4                prompt_pos
                0x00000000004134c8                stdin
                0x00000000004134cc                prompt_status
                0x00000000004134e0                prompt_err
                0x00000000004138e0                stderr
                0x0000000000413900                prompt
                0x0000000000413d00                g_cursor_y
                0x0000000000413d04                prompt_max
 COMMON         0x0000000000413d08        0x0 stdio.o
 *fill*         0x0000000000413d08       0x18 
 COMMON         0x0000000000413d20      0x878 stdlib.o
                0x0000000000413d20                mm_prev_pointer
                0x0000000000413d40                mmblockList
                0x0000000000414140                last_valid
                0x0000000000414160                heapList
                0x0000000000414560                libcHeap
                0x0000000000414564                randseed
                0x0000000000414568                heap_start
                0x000000000041456c                g_available_heap
                0x0000000000414570                g_heap_pointer
                0x0000000000414574                HEAP_SIZE
                0x0000000000414578                mmblockCount
                0x000000000041457c                last_size
                0x0000000000414580                heap_end
                0x0000000000414584                HEAP_END
                0x0000000000414588                Heap
                0x000000000041458c                current_mmblock
                0x0000000000414590                heapCount
                0x0000000000414594                HEAP_START
 *fill*         0x0000000000414598        0x8 
 COMMON         0x00000000004145a0       0xa4 unistd.o
                0x00000000004145a0                errno
                0x00000000004145a4                optarg
                0x00000000004145a8                opterr
                0x00000000004145ac                my__p
                0x00000000004145b0                optind
                0x00000000004145c0                __Hostname_buffer
                0x0000000000414600                __Login_buffer
                0x0000000000414640                optopt
                0x0000000000414644                end = .
                0x0000000000414644                _end = .
                0x0000000000414644                __end = .
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
OUTPUT(CAT.BIN elf32-i386)

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
