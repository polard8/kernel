
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
gdsp                0x4               main.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
chk                 0x4               main.o
idnt                0x40              main.o
Streams             0x80              crt0.o
nst                 0x4               main.o
optarg              0x4               unistd.o
fout                0x4               main.o
g_using_gui         0x4               crt0.o
gs                  0x4               main.o
opterr              0x4               unistd.o
randseed            0x4               stdlib.o
rs                  0x1c200           main.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
fin                 0x4               main.o
adsp                0x4               main.o
environ             0x4               stdio.o
fhdr                0x4               main.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
srca                0x4               main.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
optind              0x4               unistd.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
rrconf              0x4               main.o
ntk                 0x4               main.o
__Hostname_buffer   0x40              unistd.o
prompt_status       0x4               crt0.o
as                  0x4               main.o
__Login_buffer      0x40              unistd.o
prompt_err          0x400             crt0.o
srconf              0x4               main.o
fgrm                0x4               main.o
heap_end            0x4               stdlib.o
i0                  0x11950           main.o
stderr              0x4               crt0.o
optopt              0x4               unistd.o
act                 0x4               main.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
nsy                 0x4               main.o
doty                0x4               main.o
g_cursor_y          0x4               crt0.o
sstart              0x4               main.o
Heap                0x4               stdlib.o
nrl                 0x4               main.o
st                  0x4               main.o
is                  0x31ce0           main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               stdlib.o
HEAP_START          0x4               stdlib.o
actsz               0x4               main.o
ini                 0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000401000     0xa000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000       0xf2 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010f2     0x34bb main.o
                0x000000000040110f                die
                0x0000000000401142                yalloc
                0x0000000000401177                rcmp
                0x000000000040118a                rfind
                0x00000000004011f2                slen
                0x0000000000401218                tszero
                0x0000000000401233                tsunion
                0x00000000004012ad                first
                0x000000000040137b                ginit
                0x0000000000401467                tcmp
                0x00000000004014a5                tcmpv
                0x00000000004014b8                iclose
                0x000000000040175d                igoto
                0x0000000000401816                icmp
                0x00000000004018fa                stadd
                0x0000000000401b75                stgen
                0x0000000000401cfd                resolve
                0x0000000000401dde                tblset
                0x0000000000402044                setdef
                0x0000000000402160                tblgen
                0x0000000000402372                prcmp
                0x000000000040238b                actgen
                0x000000000040287f                aout
                0x0000000000402959                tblout
                0x0000000000402e0d                stdump
                0x000000000040319f                istok
                0x00000000004031d3                nexttk
                0x00000000004033fd                cpycode
                0x0000000000403539                gettype
                0x00000000004035a5                findsy
                0x00000000004036c2                getdecls
                0x0000000000403b80                getgram
                0x0000000000403e45                actout
                0x000000000040417d                codeout
                0x00000000004042c5                init
                0x00000000004044fb                main
 .text          0x00000000004045ad        0x0 ctype.o
 .text          0x00000000004045ad     0x39a3 stdio.o
                0x00000000004045f5                stdio_atoi
                0x00000000004046bc                stdio_fntos
                0x00000000004047e6                remove
                0x00000000004047f0                fclose
                0x000000000040484a                fopen
                0x00000000004048d3                fopen2
                0x0000000000404a2a                scroll
                0x0000000000404af7                clearerr
                0x0000000000404b19                fread
                0x0000000000404bb9                fwrite
                0x0000000000404bc3                prompt_putchar
                0x0000000000404c13                prompt_put_string
                0x0000000000404c40                prompt_strcat
                0x0000000000404c6d                prompt_flush
                0x0000000000404cd1                prompt_clean
                0x00000000004050e1                printf3
                0x00000000004050fe                printf_atoi
                0x00000000004051ef                printf_i2hex
                0x0000000000405251                printf2
                0x00000000004053d6                stdio_nextline
                0x0000000000405414                nlsprintf
                0x0000000000405452                sprintf
                0x00000000004054a7                libc_set_output_mode
                0x00000000004054eb                outbyte
                0x00000000004056a9                _outbyte
                0x00000000004056d8                input
                0x0000000000405835                fprintf
                0x0000000000405868                nputs
                0x00000000004058a3                __gets
                0x00000000004058d4                ungetc
                0x0000000000405926                ftell
                0x0000000000405967                fileno
                0x0000000000405981                fflush
                0x0000000000405997                __fflush
                0x0000000000405a59                __getc
                0x0000000000405b04                __putc
                0x0000000000405ba9                getc
                0x0000000000405bbf                putc
                0x0000000000405bd8                fgetc
                0x0000000000405bee                fputc
                0x0000000000405c07                getchar
                0x0000000000405c20                putchar
                0x0000000000405c3c                gets
                0x0000000000405c7e                puts
                0x0000000000405cb8                fgets
                0x0000000000405d13                fputs
                0x0000000000405d47                getw
                0x0000000000405d88                putw
                0x0000000000405db7                fgets2
                0x0000000000405e3b                fputs2
                0x0000000000405e8b                gets2
                0x0000000000405f1a                puts2
                0x0000000000405f35                getchar2
                0x0000000000405f63                feof
                0x0000000000405f7b                ferror
                0x0000000000405f93                fseek
                0x0000000000405f9d                __gramado__putc
                0x0000000000406048                debug_print
                0x000000000040606a                __serenity_fputc
                0x0000000000406083                stdioSetCursor
                0x000000000040609e                stdioGetCursorX
                0x00000000004060b9                stdioGetCursorY
                0x00000000004060d4                scanf
                0x0000000000406275                sscanf
                0x0000000000406430                kvprintf
                0x000000000040729a                printf
                0x00000000004072c8                printf_draw
                0x0000000000407310                vfprintf
                0x0000000000407388                vprintf
                0x00000000004073b7                stdout_printf
                0x00000000004073f3                stderr_printf
                0x000000000040742f                perror
                0x0000000000407446                rewind
                0x000000000040744c                snprintf
                0x0000000000407460                stdio_initialize_standard_streams
                0x000000000040748b                libcStartTerminal
                0x00000000004074ff                setbuf
                0x0000000000407505                setbuffer
                0x000000000040752f                setlinebuf
                0x0000000000407535                setvbuf
                0x00000000004075b4                filesize
                0x00000000004075fa                fileread
                0x0000000000407648                dprintf
                0x0000000000407652                vdprintf
                0x00000000004078db                Wirzenius_Torvalds_vsprintf
                0x0000000000407cb0                Torvalds_printf
                0x0000000000407cf0                vsnprintf
                0x0000000000407cfa                vscanf
                0x0000000000407d04                vsscanf
                0x0000000000407d0e                vfscanf
                0x0000000000407d25                tmpnam
                0x0000000000407d2f                tmpnam_r
                0x0000000000407d39                tempnam
                0x0000000000407d43                tmpfile
                0x0000000000407d4d                fdopen
                0x0000000000407d57                freopen
                0x0000000000407d6e                open_memstream
                0x0000000000407d78                open_wmemstream
                0x0000000000407d82                fmemopen
                0x0000000000407d8c                fgetpos
                0x0000000000407dc9                fsetpos
                0x0000000000407de0                fpurge
                0x0000000000407df7                __fpurge
                0x0000000000407e00                ctermid
                0x0000000000407e0a                stdioInitialize
 .text          0x0000000000407f50     0x11ff stdlib.o
                0x0000000000407f6d                rtGetHeapStart
                0x0000000000407f77                rtGetHeapEnd
                0x0000000000407f81                rtGetHeapPointer
                0x0000000000407f8b                rtGetAvailableHeap
                0x0000000000407f95                heapSetLibcHeap
                0x0000000000408048                heapAllocateMemory
                0x000000000040827a                FreeHeap
                0x0000000000408284                heapInit
                0x0000000000408417                stdlibInitMM
                0x000000000040847a                libcInitRT
                0x00000000004084a3                mktemp
                0x00000000004084ad                rand
                0x00000000004084ca                srand
                0x00000000004084d8                xmalloc
                0x000000000040850a                stdlib_die
                0x0000000000408540                malloc
                0x000000000040857c                realloc
                0x00000000004085b9                free
                0x00000000004085bf                calloc
                0x0000000000408605                zmalloc
                0x0000000000408641                system
                0x0000000000408a05                stdlib_strncmp
                0x0000000000408abb                v7_getenv
                0x0000000000408af7                __findenv
                0x0000000000408c18                getenv
                0x0000000000408c45                setenv
                0x0000000000408c4f                unsetenv
                0x0000000000408c59                atoi
                0x0000000000408d20                reverse
                0x0000000000408d88                itoa
                0x0000000000408e36                abs
                0x0000000000408e46                strtod
                0x0000000000409077                strtof
                0x0000000000409093                strtold
                0x00000000004090a6                atof
                0x00000000004090b8                labs
                0x00000000004090c8                mkstemp
                0x00000000004090d2                mkostemp
                0x00000000004090dc                mkstemps
                0x00000000004090e6                mkostemps
                0x00000000004090f0                ptsname
                0x00000000004090fa                ptsname_r
                0x0000000000409104                posix_openpt
                0x0000000000409121                grantpt
                0x000000000040912b                unlockpt
                0x0000000000409135                getpt
                0x000000000040913f                getprogname
                0x0000000000409149                setprogname
 .text          0x000000000040914f      0xc44 string.o
                0x000000000040917a                strcoll
                0x0000000000409193                memsetw
                0x00000000004091bf                memcmp
                0x0000000000409224                strdup
                0x0000000000409276                strndup
                0x00000000004092d7                strnchr
                0x0000000000409310                strrchr
                0x000000000040934b                strtoimax
                0x0000000000409355                strtoumax
                0x000000000040935f                strcasecmp
                0x00000000004093c7                strncpy
                0x000000000040941d                strcmp
                0x0000000000409489                strncmp
                0x00000000004094e3                memset
                0x000000000040952a                memoryZeroMemory
                0x0000000000409551                memcpy
                0x000000000040958e                strcpy
                0x00000000004095c2                strlcpy
                0x0000000000409621                strcat
                0x0000000000409650                strchrnul
                0x0000000000409675                strlcat
                0x0000000000409705                strncat
                0x0000000000409767                bcopy
                0x0000000000409794                bzero
                0x00000000004097b5                strlen
                0x00000000004097e3                strnlen
                0x000000000040981e                strpbrk
                0x000000000040986c                strsep
                0x00000000004098ea                strreplace
                0x0000000000409925                strcspn
                0x00000000004099c4                strspn
                0x0000000000409a63                strtok_r
                0x0000000000409b4a                strtok
                0x0000000000409b62                strchr
                0x0000000000409b8e                memmove
                0x0000000000409c0f                memscan
                0x0000000000409c43                strstr
                0x0000000000409ca3                index
                0x0000000000409cd0                rindex
                0x0000000000409ce3                strxfrm
                0x0000000000409d35                strerror
                0x0000000000409d3f                strerror_r
                0x0000000000409d49                strsignal
                0x0000000000409d53                strtoupper
 .text          0x0000000000409d93       0x33 time.o
                0x0000000000409d93                time
                0x0000000000409dbc                gettimeofday
 .text          0x0000000000409dc6      0x798 unistd.o
                0x0000000000409dc6                execv
                0x0000000000409de4                execve
                0x0000000000409e43                read_ttyList
                0x0000000000409e71                write_ttyList
                0x0000000000409e9f                read_tty
                0x0000000000409ecd                write_tty
                0x0000000000409efb                read_VC
                0x0000000000409f29                write_VC
                0x0000000000409f57                read
                0x0000000000409f82                write
                0x0000000000409fad                exit
                0x0000000000409fcd                fast_fork
                0x0000000000409ff5                fork
                0x000000000040a02b                sys_fork
                0x000000000040a061                setuid
                0x000000000040a07c                getuid
                0x000000000040a097                geteuid
                0x000000000040a0a1                getpid
                0x000000000040a0b9                getppid
                0x000000000040a0d1                getgid
                0x000000000040a0ec                dup
                0x000000000040a106                dup2
                0x000000000040a122                dup3
                0x000000000040a140                getpriority
                0x000000000040a14a                setpriority
                0x000000000040a154                nice
                0x000000000040a15e                pause
                0x000000000040a168                mkdir
                0x000000000040a17c                rmdir
                0x000000000040a186                link
                0x000000000040a190                unlink
                0x000000000040a19a                mlock
                0x000000000040a1a4                munlock
                0x000000000040a1ae                mlockall
                0x000000000040a1b8                munlockall
                0x000000000040a1c2                sysconf
                0x000000000040a1cc                fsync
                0x000000000040a1d6                fdatasync
                0x000000000040a1e0                sync
                0x000000000040a1e6                syncfs
                0x000000000040a1f0                close
                0x000000000040a20e                pipe
                0x000000000040a22f                fpathconf
                0x000000000040a239                pathconf
                0x000000000040a243                __gethostname
                0x000000000040a26f                gethostname
                0x000000000040a293                sethostname
                0x000000000040a2b1                getlogin
                0x000000000040a2dd                setlogin
                0x000000000040a303                getusername
                0x000000000040a37d                setusername
                0x000000000040a3f1                ttyname
                0x000000000040a42e                ttyname_r
                0x000000000040a438                isatty
                0x000000000040a45b                getopt
                0x000000000040a465                alarm
                0x000000000040a46f                brk
                0x000000000040a479                execvp
                0x000000000040a483                execvpe
                0x000000000040a48d                chown
                0x000000000040a497                fchown
                0x000000000040a4a1                lchown
                0x000000000040a4ab                chdir
                0x000000000040a4b5                fchdir
                0x000000000040a4bf                sleep
                0x000000000040a4c9                _exit
                0x000000000040a4df                swab_w
                0x000000000040a51f                swab
                0x000000000040a536                lseek
                0x000000000040a540                tell
                0x000000000040a554                access
 .text          0x000000000040a55e      0x213 termios.o
                0x000000000040a55e                tcgetpgrp
                0x000000000040a58b                tcsetpgrp
                0x000000000040a5b0                tcgetattr
                0x000000000040a5ce                tcsetattr
                0x000000000040a647                tcsendbreak
                0x000000000040a651                tcdrain
                0x000000000040a66e                tcflush
                0x000000000040a678                tcflow
                0x000000000040a682                cfmakeraw
                0x000000000040a6fc                cfgetispeed
                0x000000000040a714                cfgetospeed
                0x000000000040a72c                cfsetispeed
                0x000000000040a743                cfsetospeed
                0x000000000040a75a                cfsetspeed
 .text          0x000000000040a771       0x3d ioctl.o
                0x000000000040a771                ioctl
 .text          0x000000000040a7ae      0x11f fcntl.o
                0x000000000040a7ae                fcntl
                0x000000000040a7c5                openat
                0x000000000040a800                open
                0x000000000040a89c                creat
                0x000000000040a8c3                flock
 .text          0x000000000040a8cd       0x28 stubs.o
                0x000000000040a8cd                gramado_system_call
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a8f5      0x70b 

.iplt           0x000000000040b000        0x0
 .iplt          0x000000000040b000        0x0 crt0.o

.rodata         0x000000000040b000     0x17c8
 .rodata        0x000000000040b000       0x8a crt0.o
 *fill*         0x000000000040b08a        0x2 
 .rodata        0x000000000040b08c      0xae2 main.o
 *fill*         0x000000000040bb6e       0x12 
 .rodata        0x000000000040bb80      0x100 ctype.o
                0x000000000040bb80                _ctype
 .rodata        0x000000000040bc80      0x524 stdio.o
                0x000000000040bec0                hex2ascii_data
 *fill*         0x000000000040c1a4        0x4 
 .rodata        0x000000000040c1a8      0x560 stdlib.o
 .rodata        0x000000000040c708       0x89 unistd.o
 *fill*         0x000000000040c791        0x3 
 .rodata        0x000000000040c794       0x34 fcntl.o

.eh_frame       0x000000000040c7c8     0x2bd8
 .eh_frame      0x000000000040c7c8       0x34 crt0.o
 .eh_frame      0x000000000040c7fc      0x4f0 main.o
                                        0x508 (size before relaxing)
 .eh_frame      0x000000000040ccec      0xee8 stdio.o
                                        0xf00 (size before relaxing)
 .eh_frame      0x000000000040dbd4      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x000000000040e21c      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040e7dc       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040e81c      0x8e0 unistd.o
                                        0x8f8 (size before relaxing)
 .eh_frame      0x000000000040f0fc      0x1c0 termios.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x000000000040f2bc       0x20 ioctl.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040f2dc       0xa0 fcntl.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040f37c       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040f3a0        0x0
 .rel.got       0x000000000040f3a0        0x0 crt0.o
 .rel.iplt      0x000000000040f3a0        0x0 crt0.o
 .rel.text      0x000000000040f3a0        0x0 crt0.o

.data           0x000000000040f3a0      0xc60
                0x000000000040f3a0                data = .
                0x000000000040f3a0                _data = .
                0x000000000040f3a0                __data = .
 *(.data)
 .data          0x000000000040f3a0       0x50 crt0.o
 *fill*         0x000000000040f3f0       0x10 
 .data          0x000000000040f400      0x1e8 main.o
                0x000000000040f400                srs
                0x000000000040f440                rrs
                0x000000000040f46c                lineno
                0x000000000040f480                words
                0x000000000040f4d0                retcode
                0x000000000040f4e0                code0
                0x000000000040f5d8                code1
 .data          0x000000000040f5e8        0x0 ctype.o
 .data          0x000000000040f5e8        0x0 stdio.o
 .data          0x000000000040f5e8        0x8 stdlib.o
                0x000000000040f5e8                _infinity
 .data          0x000000000040f5f0        0x0 string.o
 .data          0x000000000040f5f0        0x0 time.o
 .data          0x000000000040f5f0        0x0 unistd.o
 .data          0x000000000040f5f0        0x0 termios.o
 .data          0x000000000040f5f0        0x0 ioctl.o
 .data          0x000000000040f5f0        0x0 fcntl.o
 .data          0x000000000040f5f0        0x0 stubs.o
                0x0000000000410000                . = ALIGN (0x1000)
 *fill*         0x000000000040f5f0      0xa10 

.got            0x0000000000410000        0x0
 .got           0x0000000000410000        0x0 crt0.o

.got.plt        0x0000000000410000        0x0
 .got.plt       0x0000000000410000        0x0 crt0.o

.igot.plt       0x0000000000410000        0x0
 .igot.plt      0x0000000000410000        0x0 crt0.o

.bss            0x0000000000410000    0x69f84
                0x0000000000410000                bss = .
                0x0000000000410000                _bss = .
                0x0000000000410000                __bss = .
 *(.bss)
 .bss           0x0000000000410000        0x0 crt0.o
 .bss           0x0000000000410000        0x0 main.o
 .bss           0x0000000000410000        0x0 ctype.o
 .bss           0x0000000000410000      0x421 stdio.o
 *fill*         0x0000000000410421       0x1f 
 .bss           0x0000000000410440     0x8000 stdlib.o
 .bss           0x0000000000418440        0x4 string.o
 .bss           0x0000000000418444        0x0 time.o
 *fill*         0x0000000000418444       0x1c 
 .bss           0x0000000000418460      0x19f unistd.o
                0x0000000000418460                __execv_environ
 .bss           0x00000000004185ff        0x0 termios.o
 .bss           0x00000000004185ff        0x0 ioctl.o
 .bss           0x00000000004185ff        0x0 fcntl.o
 .bss           0x00000000004185ff        0x0 stubs.o
                0x0000000000419000                . = ALIGN (0x1000)
 *fill*         0x00000000004185ff      0xa01 
 COMMON         0x0000000000419000      0xd08 crt0.o
                0x0000000000419000                g_cursor_x
                0x0000000000419004                stdout
                0x0000000000419008                __libc_tty_id
                0x000000000041900c                g_char_attrib
                0x0000000000419010                g_rows
                0x0000000000419020                Streams
                0x00000000004190a0                g_using_gui
                0x00000000004190c0                prompt_out
                0x00000000004194c0                g_columns
                0x00000000004194c4                prompt_pos
                0x00000000004194c8                stdin
                0x00000000004194cc                prompt_status
                0x00000000004194e0                prompt_err
                0x00000000004198e0                stderr
                0x0000000000419900                prompt
                0x0000000000419d00                g_cursor_y
                0x0000000000419d04                prompt_max
 *fill*         0x0000000000419d08       0x18 
 COMMON         0x0000000000419d20    0x5f928 main.o
                0x0000000000419d20                gdsp
                0x0000000000419d24                chk
                0x0000000000419d40                idnt
                0x0000000000419d80                nst
                0x0000000000419d84                fout
                0x0000000000419d88                gs
                0x0000000000419da0                rs
                0x0000000000435fa0                fin
                0x0000000000435fa4                adsp
                0x0000000000435fa8                fhdr
                0x0000000000435fac                srca
                0x0000000000435fb0                rrconf
                0x0000000000435fb4                ntk
                0x0000000000435fb8                as
                0x0000000000435fbc                srconf
                0x0000000000435fc0                fgrm
                0x0000000000435fe0                i0
                0x0000000000447930                act
                0x0000000000447934                nsy
                0x0000000000447938                doty
                0x000000000044793c                sstart
                0x0000000000447940                nrl
                0x0000000000447944                st
                0x0000000000447960                is
                0x0000000000479640                actsz
                0x0000000000479644                ini
 COMMON         0x0000000000479648        0x4 stdio.o
                0x0000000000479648                environ
 *fill*         0x000000000047964c       0x14 
 COMMON         0x0000000000479660      0x878 stdlib.o
                0x0000000000479660                mm_prev_pointer
                0x0000000000479680                mmblockList
                0x0000000000479a80                last_valid
                0x0000000000479aa0                heapList
                0x0000000000479ea0                libcHeap
                0x0000000000479ea4                randseed
                0x0000000000479ea8                heap_start
                0x0000000000479eac                g_available_heap
                0x0000000000479eb0                g_heap_pointer
                0x0000000000479eb4                HEAP_SIZE
                0x0000000000479eb8                mmblockCount
                0x0000000000479ebc                last_size
                0x0000000000479ec0                heap_end
                0x0000000000479ec4                HEAP_END
                0x0000000000479ec8                Heap
                0x0000000000479ecc                current_mmblock
                0x0000000000479ed0                heapCount
                0x0000000000479ed4                HEAP_START
 *fill*         0x0000000000479ed8        0x8 
 COMMON         0x0000000000479ee0       0xa4 unistd.o
                0x0000000000479ee0                errno
                0x0000000000479ee4                optarg
                0x0000000000479ee8                opterr
                0x0000000000479eec                optind
                0x0000000000479f00                __Hostname_buffer
                0x0000000000479f40                __Login_buffer
                0x0000000000479f80                optopt
                0x0000000000479f84                end = .
                0x0000000000479f84                _end = .
                0x0000000000479f84                __end = .
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
LOAD fcntl.o
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
 .comment       0x0000000000000011       0x12 fcntl.o
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
                0x0000000000000000        0x0 fcntl.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
