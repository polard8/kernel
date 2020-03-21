
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
g_using_gui         0x4               crt0.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
prompt_status       0x4               crt0.o
prompt_err          0x400             crt0.o
heap_end            0x4               stdlib.o
stderr              0x4               crt0.o
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


.text           0x0000000000401000     0x5000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000      0x128 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401128       0xd3 main.o
                0x0000000000401128                main
 .text          0x00000000004011fb        0x0 ctype.o
 .text          0x00000000004011fb     0x2a7e stdio.o
                0x0000000000401243                stdio_atoi
                0x000000000040130a                stdio_fntos
                0x0000000000401434                remove
                0x000000000040143e                fclose
                0x000000000040145f                fopen
                0x0000000000401480                creat
                0x00000000004014a7                scroll
                0x0000000000401574                puts
                0x000000000040158f                fread
                0x00000000004015b0                fwrite
                0x0000000000401992                printf3
                0x00000000004019af                printf_atoi
                0x0000000000401aa0                printf_i2hex
                0x0000000000401b02                printf2
                0x0000000000401c87                stdio_nextline
                0x0000000000401cc5                nlsprintf
                0x0000000000401d03                sprintf
                0x0000000000401d58                putchar
                0x0000000000401da3                libc_set_output_mode
                0x0000000000401de7                outbyte
                0x0000000000401fa5                _outbyte
                0x0000000000401fd4                input
                0x0000000000402131                getchar
                0x000000000040215f                stdioInitialize
                0x0000000000402301                fflush
                0x0000000000402322                fprintf
                0x00000000004023b0                fputs
                0x00000000004023d1                nputs
                0x000000000040240c                gets
                0x000000000040249b                ungetc
                0x00000000004024bc                ftell
                0x00000000004024dd                fileno
                0x00000000004024fe                fgetc
                0x000000000040251f                feof
                0x0000000000402540                ferror
                0x0000000000402561                fseek
                0x0000000000402582                fputc
                0x000000000040261d                stdioSetCursor
                0x0000000000402638                stdioGetCursorX
                0x0000000000402653                stdioGetCursorY
                0x000000000040266e                scanf
                0x000000000040280f                sscanf
                0x00000000004029ca                kvprintf
                0x0000000000403834                printf
                0x0000000000403862                printf_draw
                0x00000000004038aa                vfprintf
                0x0000000000403922                vprintf
                0x0000000000403941                stdout_printf
                0x000000000040396d                stderr_printf
                0x0000000000403999                perror
                0x00000000004039b0                rewind
                0x00000000004039da                snprintf
                0x00000000004039ee                stdio_initialize_standard_streams
                0x0000000000403a19                libcStartTerminal
                0x0000000000403a8d                setbuf
                0x0000000000403aaf                setbuffer
                0x0000000000403ad1                setlinebuf
                0x0000000000403af3                setvbuf
                0x0000000000403b14                filesize
                0x0000000000403b5d                fileread
                0x0000000000403bab                dprintf
                0x0000000000403bb5                vdprintf
                0x0000000000403bbf                vsprintf
                0x0000000000403bc9                vsnprintf
                0x0000000000403bd3                vscanf
                0x0000000000403bdd                vsscanf
                0x0000000000403be7                vfscanf
                0x0000000000403bf1                tmpnam
                0x0000000000403bfb                tmpnam_r
                0x0000000000403c05                tempnam
                0x0000000000403c0f                tmpfile
                0x0000000000403c19                fdopen
                0x0000000000403c23                freopen
                0x0000000000403c2d                open_memstream
                0x0000000000403c37                open_wmemstream
                0x0000000000403c41                fmemopen
                0x0000000000403c4b                fgetpos
                0x0000000000403c55                fsetpos
                0x0000000000403c5f                fpurge
                0x0000000000403c69                __fpurge
                0x0000000000403c6f                ctermid
 .text          0x0000000000403c79     0x1101 stdlib.o
                0x0000000000403c96                rtGetHeapStart
                0x0000000000403ca0                rtGetHeapEnd
                0x0000000000403caa                rtGetHeapPointer
                0x0000000000403cb4                rtGetAvailableHeap
                0x0000000000403cbe                heapSetLibcHeap
                0x0000000000403d71                heapAllocateMemory
                0x0000000000403fa3                FreeHeap
                0x0000000000403fad                heapInit
                0x0000000000404140                stdlibInitMM
                0x00000000004041a3                libcInitRT
                0x00000000004041c5                mktemp
                0x00000000004041cf                rand
                0x00000000004041ec                srand
                0x00000000004041fa                xmalloc
                0x000000000040422c                stdlib_die
                0x0000000000404262                malloc
                0x000000000040429e                realloc
                0x00000000004042db                free
                0x00000000004042e1                calloc
                0x0000000000404327                zmalloc
                0x0000000000404363                system
                0x0000000000404727                stdlib_strncmp
                0x000000000040478a                __findenv
                0x0000000000404855                getenv
                0x0000000000404882                setenv
                0x000000000040488c                unsetenv
                0x0000000000404896                atoi
                0x000000000040495d                reverse
                0x00000000004049c5                itoa
                0x0000000000404a73                abs
                0x0000000000404a83                strtod
                0x0000000000404cb4                strtof
                0x0000000000404cd0                strtold
                0x0000000000404ce3                atof
                0x0000000000404cf5                labs
                0x0000000000404d05                mkstemp
                0x0000000000404d0f                mkostemp
                0x0000000000404d19                mkstemps
                0x0000000000404d23                mkostemps
                0x0000000000404d2d                ptsname
                0x0000000000404d37                ptsname_r
                0x0000000000404d41                posix_openpt
                0x0000000000404d5c                grantpt
                0x0000000000404d66                getpt
                0x0000000000404d70                unlockpt
 .text          0x0000000000404d7a      0xb2b string.o
                0x0000000000404d7a                strcoll
                0x0000000000404d93                memsetw
                0x0000000000404dbf                memcmp
                0x0000000000404e24                strdup
                0x0000000000404e76                strndup
                0x0000000000404ed7                strnchr
                0x0000000000404f10                strrchr
                0x0000000000404f4b                strtoimax
                0x0000000000404f55                strtoumax
                0x0000000000404f5f                strcasecmp
                0x0000000000404fc7                strncpy
                0x000000000040501d                strcmp
                0x0000000000405082                strncmp
                0x00000000004050e5                memset
                0x000000000040512c                memoryZeroMemory
                0x0000000000405153                memcpy
                0x0000000000405190                strcpy
                0x00000000004051c4                strlcpy
                0x0000000000405223                strcat
                0x0000000000405252                strchrnul
                0x0000000000405277                strlcat
                0x0000000000405307                strncat
                0x0000000000405369                bcopy
                0x0000000000405396                bzero
                0x00000000004053b7                strlen
                0x00000000004053e5                strnlen
                0x0000000000405420                strpbrk
                0x000000000040546e                strsep
                0x00000000004054ec                strreplace
                0x0000000000405527                strcspn
                0x00000000004055c6                strspn
                0x0000000000405665                strtok_r
                0x000000000040574c                strtok
                0x0000000000405764                strchr
                0x0000000000405790                memmove
                0x0000000000405811                memscan
                0x0000000000405845                strstr
 .text          0x00000000004058a5       0x33 time.o
                0x00000000004058a5                time
                0x00000000004058ce                gettimeofday
 .text          0x00000000004058d8      0x5e7 unistd.o
                0x00000000004058d8                execv
                0x00000000004058f6                execve
                0x0000000000405955                write
                0x000000000040599d                exit
                0x00000000004059bd                fast_fork
                0x00000000004059e5                fork
                0x0000000000405a1b                sys_fork
                0x0000000000405a51                setuid
                0x0000000000405a6c                getuid
                0x0000000000405a87                geteuid
                0x0000000000405a91                getpid
                0x0000000000405aa9                getppid
                0x0000000000405ac1                getgid
                0x0000000000405adc                dup
                0x0000000000405af6                dup2
                0x0000000000405b12                dup3
                0x0000000000405b30                fcntl
                0x0000000000405b3a                nice
                0x0000000000405b44                pause
                0x0000000000405b4e                mkdir
                0x0000000000405b62                rmdir
                0x0000000000405b6c                link
                0x0000000000405b76                unlink
                0x0000000000405b80                mlock
                0x0000000000405b8a                munlock
                0x0000000000405b94                mlockall
                0x0000000000405b9e                munlockall
                0x0000000000405ba8                sysconf
                0x0000000000405bb2                fsync
                0x0000000000405bbc                fdatasync
                0x0000000000405bc6                open
                0x0000000000405bec                close
                0x0000000000405c0a                pipe
                0x0000000000405c2b                fpathconf
                0x0000000000405c35                pathconf
                0x0000000000405c3f                gethostname
                0x0000000000405ce5                sethostname
                0x0000000000405d5c                getusername
                0x0000000000405e02                setusername
                0x0000000000405e79                ttyname
                0x0000000000405e83                ttyname_r
                0x0000000000405e8d                isatty
                0x0000000000405e97                openpty
                0x0000000000405ea1                forkpty
                0x0000000000405eab                login_tty
                0x0000000000405eb5                getopt
 .text          0x0000000000405ebf       0x28 stubs.o
                0x0000000000405ebf                gramado_system_call
                0x0000000000406000                . = ALIGN (0x1000)
 *fill*         0x0000000000405ee7      0x119 

.iplt           0x0000000000406000        0x0
 .iplt          0x0000000000406000        0x0 crt0.o

.rodata         0x0000000000406000      0xa9e
 .rodata        0x0000000000406000       0x74 crt0.o
 .rodata        0x0000000000406074       0x1d main.o
 *fill*         0x0000000000406091        0xf 
 .rodata        0x00000000004060a0      0x100 ctype.o
                0x00000000004060a0                _ctype
 .rodata        0x00000000004061a0      0x329 stdio.o
                0x0000000000406300                hex2ascii_data
 *fill*         0x00000000004064c9        0x7 
 .rodata        0x00000000004064d0      0x520 stdlib.o
 .rodata        0x00000000004069f0       0xae unistd.o

.eh_frame       0x0000000000406aa0     0x1ca0
 .eh_frame      0x0000000000406aa0       0x34 crt0.o
 .eh_frame      0x0000000000406ad4       0x54 main.o
                                         0x6c (size before relaxing)
 .eh_frame      0x0000000000406b28      0xb74 stdio.o
                                        0xb8c (size before relaxing)
 .eh_frame      0x000000000040769c      0x5c0 stdlib.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x0000000000407c5c      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000040811c       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040815c      0x5c0 unistd.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040871c       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x0000000000408740        0x0
 .rel.got       0x0000000000408740        0x0 crt0.o
 .rel.iplt      0x0000000000408740        0x0 crt0.o
 .rel.text      0x0000000000408740        0x0 crt0.o

.data           0x0000000000408740      0x8c0
                0x0000000000408740                data = .
                0x0000000000408740                _data = .
                0x0000000000408740                __data = .
 *(.data)
 .data          0x0000000000408740       0x14 crt0.o
 .data          0x0000000000408754        0x0 main.o
 .data          0x0000000000408754        0x0 ctype.o
 .data          0x0000000000408754        0x0 stdio.o
 *fill*         0x0000000000408754        0x4 
 .data          0x0000000000408758        0x8 stdlib.o
                0x0000000000408758                _infinity
 .data          0x0000000000408760        0x0 string.o
 .data          0x0000000000408760        0x0 time.o
 .data          0x0000000000408760        0x0 unistd.o
 .data          0x0000000000408760        0x0 stubs.o
                0x0000000000409000                . = ALIGN (0x1000)
 *fill*         0x0000000000408760      0x8a0 

.got            0x0000000000409000        0x0
 .got           0x0000000000409000        0x0 crt0.o

.got.plt        0x0000000000409000        0x0
 .got.plt       0x0000000000409000        0x0 crt0.o

.igot.plt       0x0000000000409000        0x0
 .igot.plt      0x0000000000409000        0x0 crt0.o

.bss            0x0000000000409000     0xa59c
                0x0000000000409000                bss = .
                0x0000000000409000                _bss = .
                0x0000000000409000                __bss = .
 *(.bss)
 .bss           0x0000000000409000        0x0 crt0.o
 .bss           0x0000000000409000        0x0 main.o
 .bss           0x0000000000409000        0x0 ctype.o
 .bss           0x0000000000409000        0x9 stdio.o
 *fill*         0x0000000000409009       0x17 
 .bss           0x0000000000409020     0x8020 stdlib.o
                0x0000000000409020                environ
 .bss           0x0000000000411040        0x4 string.o
 .bss           0x0000000000411044        0x0 time.o
 *fill*         0x0000000000411044       0x1c 
 .bss           0x0000000000411060       0xa0 unistd.o
                0x0000000000411060                __execv_environ
 .bss           0x0000000000411100        0x0 stubs.o
                0x0000000000412000                . = ALIGN (0x1000)
 *fill*         0x0000000000411100      0xf00 
 COMMON         0x0000000000412000      0xd08 crt0.o
                0x0000000000412000                g_cursor_x
                0x0000000000412004                stdout
                0x0000000000412008                g_char_attrib
                0x000000000041200c                g_rows
                0x0000000000412020                Streams
                0x00000000004120a0                g_using_gui
                0x00000000004120c0                prompt_out
                0x00000000004124c0                g_columns
                0x00000000004124c4                prompt_pos
                0x00000000004124c8                stdin
                0x00000000004124cc                prompt_status
                0x00000000004124e0                prompt_err
                0x00000000004128e0                stderr
                0x0000000000412900                prompt
                0x0000000000412d00                g_cursor_y
                0x0000000000412d04                prompt_max
 COMMON         0x0000000000412d08        0x0 stdio.o
 *fill*         0x0000000000412d08       0x18 
 COMMON         0x0000000000412d20      0x878 stdlib.o
                0x0000000000412d20                mm_prev_pointer
                0x0000000000412d40                mmblockList
                0x0000000000413140                last_valid
                0x0000000000413160                heapList
                0x0000000000413560                libcHeap
                0x0000000000413564                randseed
                0x0000000000413568                heap_start
                0x000000000041356c                g_available_heap
                0x0000000000413570                g_heap_pointer
                0x0000000000413574                HEAP_SIZE
                0x0000000000413578                mmblockCount
                0x000000000041357c                last_size
                0x0000000000413580                heap_end
                0x0000000000413584                HEAP_END
                0x0000000000413588                Heap
                0x000000000041358c                current_mmblock
                0x0000000000413590                heapCount
                0x0000000000413594                HEAP_START
 COMMON         0x0000000000413598        0x4 unistd.o
                0x0000000000413598                errno
                0x000000000041359c                end = .
                0x000000000041359c                _end = .
                0x000000000041359c                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD unistd.o
LOAD stubs.o
OUTPUT(TTY.BIN elf32-i386)

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
                0x0000000000000000        0x0 stubs.o
