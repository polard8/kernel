
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


.text           0x0000000000401000     0x7000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000       0xe8 crt0.o
                0x0000000000401000                crt0
 .text          0x00000000004010e8      0x4f2 main.o
                0x0000000000401105                main
 .text          0x00000000004015da        0x0 ctype.o
 .text          0x00000000004015da     0x3917 stdio.o
                0x0000000000401622                stdio_atoi
                0x00000000004016e9                stdio_fntos
                0x0000000000401813                remove
                0x000000000040181d                fclose
                0x0000000000401877                fopen
                0x00000000004019cb                scroll
                0x0000000000401a98                clearerr
                0x0000000000401aba                fread
                0x0000000000401b5a                fwrite
                0x0000000000401b64                prompt_putchar
                0x0000000000401bb4                prompt_put_string
                0x0000000000401be1                prompt_strcat
                0x0000000000401c0e                prompt_flush
                0x0000000000401c72                prompt_clean
                0x0000000000402082                printf3
                0x000000000040209f                printf_atoi
                0x0000000000402190                printf_i2hex
                0x00000000004021f2                printf2
                0x0000000000402377                stdio_nextline
                0x00000000004023b5                nlsprintf
                0x00000000004023f3                sprintf
                0x0000000000402448                libc_set_output_mode
                0x000000000040248c                outbyte
                0x000000000040264a                _outbyte
                0x0000000000402679                input
                0x00000000004027d6                fprintf
                0x0000000000402809                nputs
                0x0000000000402844                __gets
                0x0000000000402875                ungetc
                0x00000000004028c7                ftell
                0x0000000000402908                fileno
                0x0000000000402922                fflush
                0x0000000000402938                __fflush
                0x00000000004029fa                __getc
                0x0000000000402aa5                __putc
                0x0000000000402b4a                getc
                0x0000000000402b60                putc
                0x0000000000402b79                fgetc
                0x0000000000402b8f                fputc
                0x0000000000402ba8                getchar
                0x0000000000402bc1                putchar
                0x0000000000402bdd                gets
                0x0000000000402c1f                puts
                0x0000000000402c59                fgets
                0x0000000000402cb4                fputs
                0x0000000000402ce8                getw
                0x0000000000402d29                putw
                0x0000000000402d58                fgets2
                0x0000000000402ddc                fputs2
                0x0000000000402e2c                gets2
                0x0000000000402ebb                puts2
                0x0000000000402ed6                getchar2
                0x0000000000402f04                feof
                0x0000000000402f1c                ferror
                0x0000000000402f34                fseek
                0x0000000000402f3e                __gramado__putc
                0x0000000000402fe9                debug_print
                0x000000000040300b                __serenity_fputc
                0x0000000000403024                stdioSetCursor
                0x000000000040303f                stdioGetCursorX
                0x000000000040305a                stdioGetCursorY
                0x0000000000403075                scanf
                0x0000000000403216                sscanf
                0x00000000004033d1                kvprintf
                0x000000000040423b                printf
                0x0000000000404269                printf_draw
                0x00000000004042b1                vfprintf
                0x0000000000404329                vprintf
                0x0000000000404358                stdout_printf
                0x0000000000404394                stderr_printf
                0x00000000004043d0                perror
                0x00000000004043e7                rewind
                0x00000000004043ed                snprintf
                0x0000000000404401                stdio_initialize_standard_streams
                0x000000000040442c                libcStartTerminal
                0x00000000004044a0                setbuf
                0x00000000004044a6                setbuffer
                0x00000000004044d0                setlinebuf
                0x00000000004044d6                setvbuf
                0x0000000000404555                filesize
                0x000000000040459b                fileread
                0x00000000004045e9                dprintf
                0x00000000004045f3                vdprintf
                0x000000000040487c                Wirzenius_Torvalds_vsprintf
                0x0000000000404c51                Torvalds_printf
                0x0000000000404c91                vsnprintf
                0x0000000000404c9b                vscanf
                0x0000000000404ca5                vsscanf
                0x0000000000404caf                vfscanf
                0x0000000000404cc6                tmpnam
                0x0000000000404cd0                tmpnam_r
                0x0000000000404cda                tempnam
                0x0000000000404ce4                tmpfile
                0x0000000000404cee                fdopen
                0x0000000000404cf8                freopen
                0x0000000000404d0f                open_memstream
                0x0000000000404d19                open_wmemstream
                0x0000000000404d23                fmemopen
                0x0000000000404d2d                fgetpos
                0x0000000000404d6a                fsetpos
                0x0000000000404d81                fpurge
                0x0000000000404d98                __fpurge
                0x0000000000404da1                ctermid
                0x0000000000404dab                stdioInitialize
 .text          0x0000000000404ef1     0x11ac stdlib.o
                0x0000000000404f0e                rtGetHeapStart
                0x0000000000404f18                rtGetHeapEnd
                0x0000000000404f22                rtGetHeapPointer
                0x0000000000404f2c                rtGetAvailableHeap
                0x0000000000404f36                heapSetLibcHeap
                0x0000000000404fe9                heapAllocateMemory
                0x000000000040521b                FreeHeap
                0x0000000000405225                heapInit
                0x00000000004053b8                stdlibInitMM
                0x000000000040541b                libcInitRT
                0x0000000000405444                mktemp
                0x000000000040544e                rand
                0x000000000040546b                srand
                0x0000000000405479                xmalloc
                0x00000000004054ab                stdlib_die
                0x00000000004054e1                malloc
                0x000000000040551d                realloc
                0x000000000040555a                free
                0x0000000000405560                calloc
                0x00000000004055a6                zmalloc
                0x00000000004055e2                system
                0x00000000004059a6                stdlib_strncmp
                0x0000000000405a09                __findenv
                0x0000000000405ad4                getenv2
                0x0000000000405b01                getenv
                0x0000000000405b93                setenv
                0x0000000000405b9d                unsetenv
                0x0000000000405ba7                atoi
                0x0000000000405c6e                reverse
                0x0000000000405cd6                itoa
                0x0000000000405d84                abs
                0x0000000000405d94                strtod
                0x0000000000405fc5                strtof
                0x0000000000405fe1                strtold
                0x0000000000405ff4                atof
                0x0000000000406006                labs
                0x0000000000406016                mkstemp
                0x0000000000406020                mkostemp
                0x000000000040602a                mkstemps
                0x0000000000406034                mkostemps
                0x000000000040603e                ptsname
                0x0000000000406048                ptsname_r
                0x0000000000406052                posix_openpt
                0x000000000040606f                grantpt
                0x0000000000406079                getpt
                0x0000000000406083                unlockpt
                0x000000000040608d                getprogname
                0x0000000000406097                setprogname
 .text          0x000000000040609d      0xc46 string.o
                0x00000000004060c8                strcoll
                0x00000000004060e1                memsetw
                0x000000000040610d                memcmp
                0x0000000000406172                strdup
                0x00000000004061c4                strndup
                0x0000000000406225                strnchr
                0x000000000040625e                strrchr
                0x0000000000406299                strtoimax
                0x00000000004062a3                strtoumax
                0x00000000004062ad                strcasecmp
                0x0000000000406315                strncpy
                0x000000000040636b                strcmp
                0x00000000004063d0                strncmp
                0x0000000000406433                memset
                0x000000000040647a                memoryZeroMemory
                0x00000000004064a1                memcpy
                0x00000000004064de                strcpy
                0x0000000000406512                strlcpy
                0x0000000000406571                strcat
                0x00000000004065a0                strchrnul
                0x00000000004065c5                strlcat
                0x0000000000406655                strncat
                0x00000000004066b7                bcopy
                0x00000000004066e4                bzero
                0x0000000000406705                strlen
                0x0000000000406733                strnlen
                0x000000000040676e                strpbrk
                0x00000000004067bc                strsep
                0x000000000040683a                strreplace
                0x0000000000406875                strcspn
                0x0000000000406914                strspn
                0x00000000004069b3                strtok_r
                0x0000000000406a9a                strtok
                0x0000000000406ab2                strchr
                0x0000000000406ade                memmove
                0x0000000000406b5f                memscan
                0x0000000000406b93                strstr
                0x0000000000406bf3                index
                0x0000000000406c20                rindex
                0x0000000000406c33                strxfrm
                0x0000000000406c85                strerror
                0x0000000000406c8f                strerror_r
                0x0000000000406c99                strsignal
                0x0000000000406ca3                strtoupper
 .text          0x0000000000406ce3       0x33 time.o
                0x0000000000406ce3                time
                0x0000000000406d0c                gettimeofday
 .text          0x0000000000406d16      0x73c unistd.o
                0x0000000000406d16                execv
                0x0000000000406d34                execve
                0x0000000000406d93                read_ttyList
                0x0000000000406dc1                write_ttyList
                0x0000000000406def                read_VC
                0x0000000000406e1d                write_VC
                0x0000000000406e4b                read
                0x0000000000406e76                write
                0x0000000000406ea1                exit
                0x0000000000406ec1                fast_fork
                0x0000000000406ee9                fork
                0x0000000000406f1f                sys_fork
                0x0000000000406f55                setuid
                0x0000000000406f70                getuid
                0x0000000000406f8b                geteuid
                0x0000000000406f95                getpid
                0x0000000000406fad                getppid
                0x0000000000406fc5                getgid
                0x0000000000406fe0                dup
                0x0000000000406ffa                dup2
                0x0000000000407016                dup3
                0x0000000000407034                getpriority
                0x000000000040703e                setpriority
                0x0000000000407048                nice
                0x0000000000407052                pause
                0x000000000040705c                mkdir
                0x0000000000407070                rmdir
                0x000000000040707a                link
                0x0000000000407084                unlink
                0x000000000040708e                mlock
                0x0000000000407098                munlock
                0x00000000004070a2                mlockall
                0x00000000004070ac                munlockall
                0x00000000004070b6                sysconf
                0x00000000004070c0                fsync
                0x00000000004070ca                fdatasync
                0x00000000004070d4                sync
                0x00000000004070da                syncfs
                0x00000000004070e4                close
                0x0000000000407102                pipe
                0x0000000000407123                fpathconf
                0x000000000040712d                pathconf
                0x0000000000407137                __gethostname
                0x0000000000407163                gethostname
                0x0000000000407187                sethostname
                0x00000000004071a5                getlogin
                0x00000000004071d1                setlogin
                0x00000000004071f7                getusername
                0x0000000000407271                setusername
                0x00000000004072e5                ttyname
                0x0000000000407322                ttyname_r
                0x000000000040732c                isatty
                0x000000000040734f                getopt
                0x0000000000407359                alarm
                0x0000000000407363                brk
                0x000000000040736d                execvp
                0x0000000000407377                execvpe
                0x0000000000407381                chown
                0x000000000040738b                fchown
                0x0000000000407395                lchown
                0x000000000040739f                chdir
                0x00000000004073a9                fchdir
                0x00000000004073b3                sleep
                0x00000000004073bd                _exit
                0x00000000004073d3                swab_w
                0x0000000000407413                swab
                0x000000000040742a                lseek
                0x0000000000407434                tell
                0x0000000000407448                access
 .text          0x0000000000407452       0x30 err.o
                0x0000000000407452                err
                0x0000000000407458                errx
                0x000000000040745e                warn
                0x0000000000407464                warnx
                0x000000000040746a                verr
                0x0000000000407470                verrx
                0x0000000000407476                vwarn
                0x000000000040747c                vwarnx
 .text          0x0000000000407482        0xa locale.o
                0x0000000000407482                setlocale
 .text          0x000000000040748c       0x28 stubs.o
                0x000000000040748c                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004074b4      0xb4c 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 crt0.o

.rodata         0x0000000000408000      0xcb1
 .rodata        0x0000000000408000       0x22 crt0.o
 *fill*         0x0000000000408022        0x2 
 .rodata        0x0000000000408024       0xa1 main.o
 *fill*         0x00000000004080c5       0x1b 
 .rodata        0x00000000004080e0      0x100 ctype.o
                0x00000000004080e0                _ctype
 .rodata        0x00000000004081e0      0x524 stdio.o
                0x0000000000408420                hex2ascii_data
 *fill*         0x0000000000408704        0x4 
 .rodata        0x0000000000408708      0x520 stdlib.o
 .rodata        0x0000000000408c28       0x89 unistd.o

.eh_frame       0x0000000000408cb4     0x25e0
 .eh_frame      0x0000000000408cb4       0x34 crt0.o
 .eh_frame      0x0000000000408ce8       0xb8 main.o
                                         0xd0 (size before relaxing)
 .eh_frame      0x0000000000408da0      0xec8 stdio.o
                                        0xee0 (size before relaxing)
 .eh_frame      0x0000000000409c68      0x648 stdlib.o
                                        0x660 (size before relaxing)
 .eh_frame      0x000000000040a2b0      0x5c0 string.o
                                        0x5d8 (size before relaxing)
 .eh_frame      0x000000000040a870       0x40 time.o
                                         0x58 (size before relaxing)
 .eh_frame      0x000000000040a8b0      0x8a0 unistd.o
                                        0x8b8 (size before relaxing)
 .eh_frame      0x000000000040b150      0x100 err.o
                                        0x118 (size before relaxing)
 .eh_frame      0x000000000040b250       0x20 locale.o
                                         0x38 (size before relaxing)
 .eh_frame      0x000000000040b270       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040b294        0x0
 .rel.got       0x000000000040b294        0x0 crt0.o
 .rel.iplt      0x000000000040b294        0x0 crt0.o
 .rel.text      0x000000000040b294        0x0 crt0.o

.data           0x000000000040b298      0xd68
                0x000000000040b298                data = .
                0x000000000040b298                _data = .
                0x000000000040b298                __data = .
 *(.data)
 .data          0x000000000040b298       0x14 crt0.o
 .data          0x000000000040b2ac        0x0 main.o
 .data          0x000000000040b2ac        0x0 ctype.o
 .data          0x000000000040b2ac        0x0 stdio.o
 *fill*         0x000000000040b2ac        0x4 
 .data          0x000000000040b2b0        0x8 stdlib.o
                0x000000000040b2b0                _infinity
 .data          0x000000000040b2b8        0x0 string.o
 .data          0x000000000040b2b8        0x0 time.o
 .data          0x000000000040b2b8        0x0 unistd.o
 .data          0x000000000040b2b8        0x0 err.o
 .data          0x000000000040b2b8        0x0 locale.o
 .data          0x000000000040b2b8        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040b2b8      0xd48 

.got            0x000000000040c000        0x0
 .got           0x000000000040c000        0x0 crt0.o

.got.plt        0x000000000040c000        0x0
 .got.plt       0x000000000040c000        0x0 crt0.o

.igot.plt       0x000000000040c000        0x0
 .igot.plt      0x000000000040c000        0x0 crt0.o

.bss            0x000000000040c000     0xa644
                0x000000000040c000                bss = .
                0x000000000040c000                _bss = .
                0x000000000040c000                __bss = .
 *(.bss)
 .bss           0x000000000040c000        0x0 crt0.o
 .bss           0x000000000040c000        0x0 main.o
 .bss           0x000000000040c000        0x0 ctype.o
 .bss           0x000000000040c000      0x421 stdio.o
 *fill*         0x000000000040c421       0x1f 
 .bss           0x000000000040c440     0x8020 stdlib.o
                0x000000000040c440                environ
 .bss           0x0000000000414460        0x4 string.o
 .bss           0x0000000000414464        0x0 time.o
 *fill*         0x0000000000414464       0x1c 
 .bss           0x0000000000414480      0x19f unistd.o
                0x0000000000414480                __execv_environ
 .bss           0x000000000041461f        0x0 err.o
 .bss           0x000000000041461f        0x0 locale.o
 .bss           0x000000000041461f        0x0 stubs.o
                0x0000000000415000                . = ALIGN (0x1000)
 *fill*         0x000000000041461f      0x9e1 
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
 COMMON         0x0000000000415d08        0x0 stdio.o
 *fill*         0x0000000000415d08       0x18 
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
LOAD err.o
LOAD locale.o
LOAD stubs.o
OUTPUT(HEAD.BIN elf32-i386)

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
 .comment       0x0000000000000011       0x12 err.o
 .comment       0x0000000000000011       0x12 locale.o
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
                0x0000000000000000        0x0 err.o
 .note.GNU-stack
                0x0000000000000000        0x0 locale.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
