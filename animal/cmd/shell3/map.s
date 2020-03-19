
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
pid                 0x4               main.o
mmblockList         0x400             stdlib.o
__libc_tty_id       0x4               crt0.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
errno               0x4               unistd.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
Streams             0x80              crt0.o
command_pipe        0x8               main.o
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
 .text          0x00000000004010e8      0x35d main.o
                0x000000000040120f                main
 .text          0x0000000000401445        0x0 ctype.o
 .text          0x0000000000401445     0x354a stdio.o
                0x000000000040148d                stdio_atoi
                0x0000000000401554                stdio_fntos
                0x000000000040167e                remove
                0x0000000000401688                fclose
                0x00000000004016b6                fopen
                0x00000000004016e3                creat
                0x000000000040170a                scroll
                0x00000000004017d7                puts
                0x00000000004017f2                clearerr
                0x0000000000401814                fread
                0x00000000004018b4                fwrite
                0x00000000004018be                prompt_putchar
                0x000000000040190e                prompt_put_string
                0x000000000040193b                prompt_strcat
                0x0000000000401968                prompt_flush
                0x00000000004019cc                prompt_clean
                0x0000000000401ddc                printf3
                0x0000000000401df9                printf_atoi
                0x0000000000401eea                printf_i2hex
                0x0000000000401f4c                printf2
                0x00000000004020d1                stdio_nextline
                0x000000000040210f                nlsprintf
                0x000000000040214d                sprintf
                0x00000000004021a2                putchar
                0x00000000004021be                libc_set_output_mode
                0x0000000000402202                outbyte
                0x00000000004023c0                _outbyte
                0x00000000004023ef                input
                0x000000000040254c                getchar
                0x000000000040257a                fflush
                0x0000000000402584                fprintf
                0x00000000004025b7                fputs
                0x0000000000402607                nputs
                0x0000000000402642                __gets
                0x0000000000402673                fgets
                0x00000000004026f7                gets
                0x0000000000402786                ungetc
                0x00000000004027e1                ftell
                0x00000000004027eb                fileno
                0x0000000000402805                __gramado__getc
                0x00000000004028b0                fgetc
                0x00000000004028d3                getc
                0x00000000004028e9                putc
                0x0000000000402902                feof
                0x000000000040291a                ferror
                0x0000000000402932                fseek
                0x000000000040293c                __gramado__putc
                0x00000000004029e7                debug_print
                0x0000000000402a09                __serenity_fflush
                0x0000000000402aaa                __serenity_fputc
                0x0000000000402b4f                __serenity_putc
                0x0000000000402b68                fputc
                0x0000000000402b8e                stdioSetCursor
                0x0000000000402ba9                stdioGetCursorX
                0x0000000000402bc4                stdioGetCursorY
                0x0000000000402bdf                scanf
                0x0000000000402d80                sscanf
                0x0000000000402f3b                kvprintf
                0x0000000000403da5                printf
                0x0000000000403dd3                printf_draw
                0x0000000000403e1b                vfprintf
                0x0000000000403e93                vprintf
                0x0000000000403ec2                stdout_printf
                0x0000000000403efe                stderr_printf
                0x0000000000403f3a                perror
                0x0000000000403f51                rewind
                0x0000000000403f57                snprintf
                0x0000000000403f6b                stdio_initialize_standard_streams
                0x0000000000403f96                libcStartTerminal
                0x000000000040400a                setbuf
                0x0000000000404010                setbuffer
                0x000000000040403a                setlinebuf
                0x0000000000404040                setvbuf
                0x000000000040404a                filesize
                0x000000000040408a                fileread
                0x00000000004040d5                dprintf
                0x00000000004040df                vdprintf
                0x0000000000404368                Wirzenius_Torvalds_vsprintf
                0x000000000040473d                Torvalds_printf
                0x000000000040477d                vsnprintf
                0x0000000000404787                vscanf
                0x0000000000404791                vsscanf
                0x000000000040479b                vfscanf
                0x00000000004047b2                tmpnam
                0x00000000004047bc                tmpnam_r
                0x00000000004047c6                tempnam
                0x00000000004047d0                tmpfile
                0x00000000004047da                fdopen
                0x00000000004047e4                freopen
                0x00000000004047fb                open_memstream
                0x0000000000404805                open_wmemstream
                0x000000000040480f                fmemopen
                0x0000000000404819                fgetpos
                0x0000000000404850                fsetpos
                0x0000000000404867                fpurge
                0x000000000040487e                __fpurge
                0x0000000000404887                ctermid
                0x0000000000404891                stdioInitialize
 .text          0x000000000040498f     0x1118 stdlib.o
                0x00000000004049ac                rtGetHeapStart
                0x00000000004049b6                rtGetHeapEnd
                0x00000000004049c0                rtGetHeapPointer
                0x00000000004049ca                rtGetAvailableHeap
                0x00000000004049d4                heapSetLibcHeap
                0x0000000000404a87                heapAllocateMemory
                0x0000000000404cb9                FreeHeap
                0x0000000000404cc3                heapInit
                0x0000000000404e56                stdlibInitMM
                0x0000000000404eb9                libcInitRT
                0x0000000000404ee2                mktemp
                0x0000000000404eec                rand
                0x0000000000404f09                srand
                0x0000000000404f17                xmalloc
                0x0000000000404f49                stdlib_die
                0x0000000000404f7f                malloc
                0x0000000000404fbb                realloc
                0x0000000000404ff8                free
                0x0000000000404ffe                calloc
                0x0000000000405044                zmalloc
                0x0000000000405080                system
                0x0000000000405444                stdlib_strncmp
                0x00000000004054a7                __findenv
                0x0000000000405572                getenv
                0x000000000040559f                setenv
                0x00000000004055a9                unsetenv
                0x00000000004055b3                atoi
                0x000000000040567a                reverse
                0x00000000004056e2                itoa
                0x0000000000405790                abs
                0x00000000004057a0                strtod
                0x00000000004059d1                strtof
                0x00000000004059ed                strtold
                0x0000000000405a00                atof
                0x0000000000405a12                labs
                0x0000000000405a22                mkstemp
                0x0000000000405a2c                mkostemp
                0x0000000000405a36                mkstemps
                0x0000000000405a40                mkostemps
                0x0000000000405a4a                ptsname
                0x0000000000405a54                ptsname_r
                0x0000000000405a5e                posix_openpt
                0x0000000000405a79                grantpt
                0x0000000000405a83                getpt
                0x0000000000405a8d                unlockpt
                0x0000000000405a97                getprogname
                0x0000000000405aa1                setprogname
 .text          0x0000000000405aa7      0xc19 string.o
                0x0000000000405ad2                strcoll
                0x0000000000405aeb                memsetw
                0x0000000000405b17                memcmp
                0x0000000000405b7c                strdup
                0x0000000000405bce                strndup
                0x0000000000405c2f                strnchr
                0x0000000000405c68                strrchr
                0x0000000000405ca3                strtoimax
                0x0000000000405cad                strtoumax
                0x0000000000405cb7                strcasecmp
                0x0000000000405d1f                strncpy
                0x0000000000405d75                strcmp
                0x0000000000405dda                strncmp
                0x0000000000405e3d                memset
                0x0000000000405e84                memoryZeroMemory
                0x0000000000405eab                memcpy
                0x0000000000405ee8                strcpy
                0x0000000000405f1c                strlcpy
                0x0000000000405f7b                strcat
                0x0000000000405faa                strchrnul
                0x0000000000405fcf                strlcat
                0x000000000040605f                strncat
                0x00000000004060c1                bcopy
                0x00000000004060ee                bzero
                0x000000000040610f                strlen
                0x000000000040613d                strnlen
                0x0000000000406178                strpbrk
                0x00000000004061c6                strsep
                0x0000000000406244                strreplace
                0x000000000040627f                strcspn
                0x000000000040631e                strspn
                0x00000000004063bd                strtok_r
                0x00000000004064a4                strtok
                0x00000000004064bc                strchr
                0x00000000004064e8                memmove
                0x0000000000406569                memscan
                0x000000000040659d                strstr
                0x00000000004065fd                rindex
                0x0000000000406610                strxfrm
                0x0000000000406662                strerror
                0x000000000040666c                strerror_r
                0x0000000000406676                strsignal
                0x0000000000406680                strtoupper
 .text          0x00000000004066c0       0x33 time.o
                0x00000000004066c0                time
                0x00000000004066e9                gettimeofday
 .text          0x00000000004066f3      0x6e1 unistd.o
                0x00000000004066f3                execv
                0x0000000000406711                execve
                0x0000000000406770                read_ttyList
                0x000000000040679e                write_ttyList
                0x00000000004067cc                read_VC
                0x00000000004067fa                write_VC
                0x0000000000406828                read
                0x0000000000406856                write
                0x0000000000406884                exit
                0x00000000004068a4                fast_fork
                0x00000000004068cc                fork
                0x0000000000406902                sys_fork
                0x0000000000406938                setuid
                0x0000000000406953                getuid
                0x000000000040696e                geteuid
                0x0000000000406978                getpid
                0x0000000000406990                getppid
                0x00000000004069a8                getgid
                0x00000000004069c3                dup
                0x00000000004069dd                dup2
                0x00000000004069f9                dup3
                0x0000000000406a17                fcntl
                0x0000000000406a21                getpriority
                0x0000000000406a2b                setpriority
                0x0000000000406a35                nice
                0x0000000000406a3f                pause
                0x0000000000406a49                mkdir
                0x0000000000406a5d                rmdir
                0x0000000000406a67                link
                0x0000000000406a71                unlink
                0x0000000000406a7b                mlock
                0x0000000000406a85                munlock
                0x0000000000406a8f                mlockall
                0x0000000000406a99                munlockall
                0x0000000000406aa3                sysconf
                0x0000000000406aad                fsync
                0x0000000000406ab7                fdatasync
                0x0000000000406ac1                sync
                0x0000000000406ac7                syncfs
                0x0000000000406ad1                open
                0x0000000000406af7                close
                0x0000000000406b15                pipe
                0x0000000000406b36                fpathconf
                0x0000000000406b40                pathconf
                0x0000000000406b4a                __gethostname
                0x0000000000406b76                gethostname
                0x0000000000406b9d                sethostname
                0x0000000000406bbe                getlogin
                0x0000000000406bea                setlogin
                0x0000000000406c10                getusername
                0x0000000000406c8d                setusername
                0x0000000000406d04                ttyname
                0x0000000000406d41                ttyname_r
                0x0000000000406d4b                isatty
                0x0000000000406d6e                getopt
                0x0000000000406d78                alarm
                0x0000000000406d82                brk
                0x0000000000406d8c                execvp
                0x0000000000406d96                execvpe
                0x0000000000406da0                chdir
                0x0000000000406daa                fchdir
                0x0000000000406db4                sleep
                0x0000000000406dbe                _exit
 .text          0x0000000000406dd4      0x165 termios.o
                0x0000000000406dd4                tcgetattr
                0x0000000000406df2                tcsetattr
                0x0000000000406e6b                tcsendbreak
                0x0000000000406e75                tcdrain
                0x0000000000406e7f                tcflush
                0x0000000000406e89                tcflow
                0x0000000000406e93                cfmakeraw
                0x0000000000406f05                cfgetispeed
                0x0000000000406f10                cfgetospeed
                0x0000000000406f1b                cfsetispeed
                0x0000000000406f25                cfsetospeed
                0x0000000000406f2f                cfsetspeed
 .text          0x0000000000406f39       0x3d ioctl.o
                0x0000000000406f39                ioctl
 .text          0x0000000000406f76       0x49 wait.o
                0x0000000000406f76                wait
                0x0000000000406f90                waitpid
 .text          0x0000000000406fbf       0x28 stubs.o
                0x0000000000406fbf                gramado_system_call
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x0000000000406fe7       0x19 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 crt0.o

.rodata         0x0000000000407000      0xc31
 .rodata        0x0000000000407000       0x22 crt0.o
 *fill*         0x0000000000407022        0x2 
 .rodata        0x0000000000407024       0x39 main.o
 *fill*         0x000000000040705d        0x3 
 .rodata        0x0000000000407060      0x100 ctype.o
                0x0000000000407060                _ctype
 .rodata        0x0000000000407160      0x524 stdio.o
                0x00000000004073a0                hex2ascii_data
 *fill*         0x0000000000407684        0x4 
 .rodata        0x0000000000407688      0x520 stdlib.o
 .rodata        0x0000000000407ba8       0x89 unistd.o

.eh_frame       0x0000000000407c34     0x249c
 .eh_frame      0x0000000000407c34       0x34 crt0.o
 .eh_frame      0x0000000000407c68       0xc4 main.o
                                         0xdc (size before relaxing)
 .eh_frame      0x0000000000407d2c      0xde0 stdio.o
                                        0xdf8 (size before relaxing)
 .eh_frame      0x0000000000408b0c      0x600 stdlib.o
                                        0x618 (size before relaxing)
 .eh_frame      0x000000000040910c      0x5a0 string.o
                                        0x5b8 (size before relaxing)
 .eh_frame      0x00000000004096ac       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x00000000004096ec      0x7e0 unistd.o
                                        0x7f8 (size before relaxing)
 .eh_frame      0x0000000000409ecc      0x180 termios.o
                                        0x198 (size before relaxing)
 .eh_frame      0x000000000040a04c       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040a06c       0x40 wait.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040a0ac       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040a0d0        0x0
 .rel.got       0x000000000040a0d0        0x0 crt0.o
 .rel.iplt      0x000000000040a0d0        0x0 crt0.o
 .rel.text      0x000000000040a0d0        0x0 crt0.o

.data           0x000000000040a0d0      0xf30
                0x000000000040a0d0                data = .
                0x000000000040a0d0                _data = .
                0x000000000040a0d0                __data = .
 *(.data)
 .data          0x000000000040a0d0       0x14 crt0.o
 .data          0x000000000040a0e4        0x0 main.o
 .data          0x000000000040a0e4        0x0 ctype.o
 .data          0x000000000040a0e4        0x0 stdio.o
 *fill*         0x000000000040a0e4        0x4 
 .data          0x000000000040a0e8        0x8 stdlib.o
                0x000000000040a0e8                _infinity
 .data          0x000000000040a0f0        0x0 string.o
 .data          0x000000000040a0f0        0x0 time.o
 .data          0x000000000040a0f0        0x0 unistd.o
 .data          0x000000000040a0f0        0x0 termios.o
 .data          0x000000000040a0f0        0x0 ioctl.o
 .data          0x000000000040a0f0        0x0 wait.o
 .data          0x000000000040a0f0        0x0 stubs.o
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a0f0      0xf10 

.got            0x000000000040b000        0x0
 .got           0x000000000040b000        0x0 crt0.o

.got.plt        0x000000000040b000        0x0
 .got.plt       0x000000000040b000        0x0 crt0.o

.igot.plt       0x000000000040b000        0x0
 .igot.plt      0x000000000040b000        0x0 crt0.o

.bss            0x000000000040b000     0xb644
                0x000000000040b000                bss = .
                0x000000000040b000                _bss = .
                0x000000000040b000                __bss = .
 *(.bss)
 .bss           0x000000000040b000        0x0 crt0.o
 .bss           0x000000000040b000      0xc04 main.o
 .bss           0x000000000040bc04        0x0 ctype.o
 *fill*         0x000000000040bc04       0x1c 
 .bss           0x000000000040bc20      0x421 stdio.o
 *fill*         0x000000000040c041       0x1f 
 .bss           0x000000000040c060     0x8020 stdlib.o
                0x000000000040c060                environ
 .bss           0x0000000000414080        0x4 string.o
 .bss           0x0000000000414084        0x0 time.o
 *fill*         0x0000000000414084       0x1c 
 .bss           0x00000000004140a0      0x19f unistd.o
                0x00000000004140a0                __execv_environ
 .bss           0x000000000041423f        0x0 termios.o
 .bss           0x000000000041423f        0x0 ioctl.o
 .bss           0x000000000041423f        0x0 wait.o
 .bss           0x000000000041423f        0x0 stubs.o
                0x0000000000415000                . = ALIGN (0x1000)
 *fill*         0x000000000041423f      0xdc1 
 COMMON         0x0000000000415000      0xd08 crt0.o
                0x0000000000415000                g_cursor_x
                0x0000000000415004                stdout
                0x0000000000415008                __libc_tty_id
                0x000000000041500c                g_char_attrib
                0x0000000000415010                g_rows
                0x0000000000415020                Streams
                0x00000000004150a0                g_using_gui
                0x00000000004150c0                prompt_out
                0x00000000004154c0                g_columns
                0x00000000004154c4                prompt_pos
                0x00000000004154c8                stdin
                0x00000000004154cc                prompt_status
                0x00000000004154e0                prompt_err
                0x00000000004158e0                stderr
                0x0000000000415900                prompt
                0x0000000000415d00                g_cursor_y
                0x0000000000415d04                prompt_max
 COMMON         0x0000000000415d08        0xc main.o
                0x0000000000415d08                pid
                0x0000000000415d0c                command_pipe
 COMMON         0x0000000000415d14        0x0 stdio.o
 *fill*         0x0000000000415d14        0xc 
 COMMON         0x0000000000415d20      0x878 stdlib.o
                0x0000000000415d20                mm_prev_pointer
                0x0000000000415d40                mmblockList
                0x0000000000416140                last_valid
                0x0000000000416160                heapList
                0x0000000000416560                libcHeap
                0x0000000000416564                randseed
                0x0000000000416568                heap_start
                0x000000000041656c                g_available_heap
                0x0000000000416570                g_heap_pointer
                0x0000000000416574                HEAP_SIZE
                0x0000000000416578                mmblockCount
                0x000000000041657c                last_size
                0x0000000000416580                heap_end
                0x0000000000416584                HEAP_END
                0x0000000000416588                Heap
                0x000000000041658c                current_mmblock
                0x0000000000416590                heapCount
                0x0000000000416594                HEAP_START
 *fill*         0x0000000000416598        0x8 
 COMMON         0x00000000004165a0       0xa4 unistd.o
                0x00000000004165a0                errno
                0x00000000004165a4                optarg
                0x00000000004165a8                opterr
                0x00000000004165ac                optind
                0x00000000004165c0                __Hostname_buffer
                0x0000000000416600                __Login_buffer
                0x0000000000416640                optopt
                0x0000000000416644                end = .
                0x0000000000416644                _end = .
                0x0000000000416644                __end = .
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
LOAD wait.o
LOAD stubs.o
OUTPUT(SHELL3.BIN elf32-i386)

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
 .comment       0x0000000000000011       0x12 wait.o
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
                0x0000000000000000        0x0 wait.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
