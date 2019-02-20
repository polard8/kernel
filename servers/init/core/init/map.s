
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               crt0.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
last_valid          0x4               stdlib.o
heapList            0x400             api.o
libcHeap            0x4               api.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
idleError           0x4               main.o
ServerStatus        0x4               main.o
Streams             0x80              crt0.o
messagebox_button1  0x4               api.o
g_using_gui         0x4               crt0.o
ApplicationInfo     0x4               crt0.o
randseed            0x4               stdlib.o
heap_start          0x4               api.o
prompt_out          0x400             crt0.o
BufferInfo          0x4               crt0.o
g_available_heap    0x4               api.o
g_heap_pointer      0x4               api.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               api.o
mmblockCount        0x4               stdlib.o
dialogbox_button1   0x4               api.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
prompt_status       0x4               crt0.o
prompt_err          0x400             crt0.o
CursorInfo          0x4               crt0.o
heap_end            0x4               api.o
stderr              0x4               crt0.o
prompt              0x400             crt0.o
HEAP_END            0x4               api.o
idleStatus          0x4               main.o
rect                0x4               crt0.o
g_cursor_y          0x4               crt0.o
ClientAreaInfo      0x4               crt0.o
messagebox_button2  0x4               api.o
Heap                0x4               api.o
current_semaphore   0x4               crt0.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               api.o
HEAP_START          0x4               api.o

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
 .text          0x0000000000401000       0x58 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401058      0x102 main.o
                0x0000000000401068                idleLoop
                0x0000000000401086                initMain
                0x0000000000401090                driverInitialize
                0x00000000004010b3                driverUninitialize
                0x00000000004010d6                idleServices
                0x000000000040113c                idleInit
 .text          0x000000000040115a     0x1fee api.o
                0x000000000040115a                system_call
                0x0000000000401182                apiSystem
                0x000000000040158a                system1
                0x00000000004015ab                system2
                0x00000000004015cc                system3
                0x00000000004015ed                system4
                0x000000000040160e                system5
                0x000000000040162f                system6
                0x0000000000401650                system7
                0x0000000000401671                system8
                0x0000000000401692                system9
                0x00000000004016b3                system10
                0x00000000004016d4                system11
                0x00000000004016f5                system12
                0x0000000000401716                system13
                0x0000000000401737                system14
                0x0000000000401758                system15
                0x0000000000401779                refresh_buffer
                0x0000000000401857                print_string
                0x000000000040185d                vsync
                0x0000000000401877                edit_box
                0x0000000000401893                chama_procedimento
                0x00000000004018ae                SetNextWindowProcedure
                0x00000000004018c9                set_cursor
                0x00000000004018e5                put_char
                0x00000000004018eb                carrega_bitmap_16x16
                0x0000000000401904                apiShutDown
                0x000000000040191b                apiInitBackground
                0x0000000000401921                MessageBox
                0x0000000000401e77                mbProcedure
                0x0000000000401ee5                DialogBox
                0x000000000040225f                dbProcedure
                0x00000000004022cd                call_kernel
                0x0000000000402448                call_gui
                0x00000000004024d4                APICreateWindow
                0x000000000040254e                APIRegisterWindow
                0x000000000040257b                APICloseWindow
                0x00000000004025a8                APISetFocus
                0x00000000004025d5                APIGetFocus
                0x00000000004025ea                APIKillFocus
                0x0000000000402617                APISetActiveWindow
                0x0000000000402644                APIGetActiveWindow
                0x0000000000402659                APIShowCurrentProcessInfo
                0x000000000040266f                APIresize_window
                0x0000000000402689                APIredraw_window
                0x00000000004026a3                APIreplace_window
                0x00000000004026bd                APImaximize_window
                0x00000000004026d9                APIminimize_window
                0x00000000004026f5                APIupdate_window
                0x0000000000402711                APIget_foregroung_window
                0x0000000000402727                APIset_foregroung_window
                0x0000000000402743                apiExit
                0x0000000000402760                kill
                0x0000000000402766                dead_thread_collector
                0x000000000040277c                api_strncmp
                0x00000000004027df                refresh_screen
                0x00000000004027f5                api_refresh_screen
                0x0000000000402800                apiReboot
                0x0000000000402816                apiSetCursor
                0x000000000040282e                apiGetCursorX
                0x0000000000402846                apiGetCursorY
                0x000000000040285e                apiGetClientAreaRect
                0x0000000000402876                apiSetClientAreaRect
                0x0000000000402895                apiCreateProcess
                0x00000000004028ae                apiCreateThread
                0x00000000004028c7                apiStartThread
                0x00000000004028e3                apiFOpen
                0x000000000040290f                apiSaveFile
                0x0000000000402962                apiDown
                0x00000000004029b5                apiUp
                0x0000000000402a08                enterCriticalSection
                0x0000000000402a43                exitCriticalSection
                0x0000000000402a5c                initializeCriticalSection
                0x0000000000402a75                apiBeginPaint
                0x0000000000402a80                apiEndPaint
                0x0000000000402a8b                apiPutChar
                0x0000000000402aa7                apiDefDialog
                0x0000000000402ab1                apiGetSystemMetrics
                0x0000000000402acf                api_set_current_keyboard_responder
                0x0000000000402aee                api_get_current_keyboard_responder
                0x0000000000402b06                api_set_current_mouse_responder
                0x0000000000402b25                api_get_current_mouse_responder
                0x0000000000402b3d                api_set_window_with_text_input
                0x0000000000402b7f                api_get_window_with_text_input
                0x0000000000402b97                gramadocore_init_execve
                0x0000000000402ba1                apiDialog
                0x0000000000402c2d                api_getchar
                0x0000000000402c45                apiDisplayBMP
                0x000000000040304c                apiSendMessage
                0x0000000000403082                apiDrawText
                0x00000000004030c1                apiGetWSScreenWindow
                0x00000000004030d9                apiGetWSMainWindow
                0x00000000004030f1                apiCreateTimer
                0x000000000040310e                apiGetSysTimeInfo
                0x000000000040312c                apiShowWindow
 .text          0x0000000000403148        0x0 ctype.o
 .text          0x0000000000403148     0x2546 stdio.o
                0x0000000000403190                stdio_atoi
                0x0000000000403257                stdio_fntos
                0x0000000000403381                fclose
                0x00000000004033a2                fopen
                0x00000000004033c3                scroll
                0x0000000000403491                puts
                0x00000000004034ac                fread
                0x00000000004034b6                fwrite
                0x0000000000403881                printf3
                0x000000000040389e                printf_atoi
                0x000000000040398e                printf_i2hex
                0x00000000004039f0                printf2
                0x0000000000403b75                sprintf
                0x0000000000403bca                putchar
                0x0000000000403beb                outbyte
                0x0000000000403da9                _outbyte
                0x0000000000403dd8                input
                0x0000000000403f2c                getchar
                0x0000000000403f47                stdioInitialize
                0x0000000000404134                fflush
                0x0000000000404155                fprintf
                0x0000000000404176                fputs
                0x0000000000404197                gets
                0x0000000000404222                ungetc
                0x000000000040422c                ftell
                0x0000000000404236                fileno
                0x0000000000404240                fgetc
                0x0000000000404261                feof
                0x0000000000404282                ferror
                0x00000000004042a3                fseek
                0x00000000004042c4                fputc
                0x00000000004042e5                stdioSetCursor
                0x0000000000404300                stdioGetCursorX
                0x000000000040431b                stdioGetCursorY
                0x0000000000404336                scanf
                0x00000000004044d0                fscanf
                0x00000000004044ed                sscanf
                0x00000000004046a8                kvprintf
                0x0000000000405512                printf
                0x000000000040553c                vfprintf
                0x00000000004055b1                vprintf
                0x00000000004055d0                stdout_printf
                0x00000000004055fc                stderr_printf
                0x0000000000405628                perror
                0x000000000040563f                rewind
                0x000000000040567a                snprintf
 .text          0x000000000040568e     0x105e stdlib.o
                0x00000000004056ab                rtGetHeapStart
                0x00000000004056b5                rtGetHeapEnd
                0x00000000004056bf                rtGetHeapPointer
                0x00000000004056c9                rtGetAvailableHeap
                0x00000000004056d3                heapSetLibcHeap
                0x0000000000405786                heapAllocateMemory
                0x00000000004059b8                FreeHeap
                0x00000000004059c2                heapInit
                0x0000000000405b55                stdlibInitMM
                0x0000000000405bb8                libcInitRT
                0x0000000000405bda                rand
                0x0000000000405bf7                srand
                0x0000000000405c05                xmalloc
                0x0000000000405c37                stdlib_die
                0x0000000000405c6d                malloc
                0x0000000000405ca9                realloc
                0x0000000000405ce6                free
                0x0000000000405cec                calloc
                0x0000000000405d32                zmalloc
                0x0000000000405d6e                system
                0x0000000000406132                stdlib_strncmp
                0x0000000000406195                __findenv
                0x0000000000406260                getenv
                0x000000000040628d                atoi
                0x0000000000406354                reverse
                0x00000000004063bb                itoa
                0x0000000000406469                abs
                0x0000000000406479                strtod
                0x00000000004066ab                strtof
                0x00000000004066c7                strtold
                0x00000000004066da                atof
 .text          0x00000000004066ec      0x772 string.o
                0x00000000004066ec                memcmp
                0x0000000000406751                strdup
                0x00000000004067a3                strndup
                0x0000000000406804                strrchr
                0x000000000040683f                strtoimax
                0x0000000000406849                strtoumax
                0x0000000000406853                strcasecmp
                0x00000000004068bb                strncpy
                0x0000000000406911                strcmp
                0x0000000000406976                strncmp
                0x00000000004069d9                memset
                0x0000000000406a20                memoryZeroMemory
                0x0000000000406a47                memcpy
                0x0000000000406a84                strcpy
                0x0000000000406ab8                strcat
                0x0000000000406ae7                bcopy
                0x0000000000406b13                bzero
                0x0000000000406b33                strlen
                0x0000000000406b61                strnlen
                0x0000000000406b95                strcspn
                0x0000000000406c34                strspn
                0x0000000000406cd3                strtok_r
                0x0000000000406dba                strtok
                0x0000000000406dd2                strchr
                0x0000000000406dfe                strstr
 .text          0x0000000000406e5e       0x89 conio.o
                0x0000000000406e5e                putch
                0x0000000000406e82                cputs
                0x0000000000406eb7                getch
                0x0000000000406ecf                getche
 .text          0x0000000000406ee7      0x176 unistd.o
                0x0000000000406ee7                execve
                0x0000000000406ef1                exit
                0x0000000000406f11                fork
                0x0000000000406f29                setuid
                0x0000000000406f33                getpid
                0x0000000000406f4b                getppid
                0x0000000000406f63                getgid
                0x0000000000406f6d                dup
                0x0000000000406f77                dup2
                0x0000000000406f81                dup3
                0x0000000000406f8b                fcntl
                0x0000000000406f95                nice
                0x0000000000406f9f                shutdown
                0x0000000000406fa9                send
                0x0000000000406fb3                pause
                0x0000000000406fbd                mkdir
                0x0000000000406fd1                rmdir
                0x0000000000406fdb                link
                0x0000000000406fe5                socket
                0x0000000000406fef                recv
                0x0000000000406ff9                mlock
                0x0000000000407003                munlock
                0x000000000040700d                mlockall
                0x0000000000407017                munlockall
                0x0000000000407021                sysconf
                0x000000000040702b                fsync
                0x0000000000407035                fdatasync
                0x000000000040703f                fpathconf
                0x0000000000407049                pathconf
                0x0000000000407053                ioctl
 .text          0x000000000040705d       0x28 stubs.o
                0x000000000040705d                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x0000000000407085      0xf7b 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 stubs.o

.rodata         0x0000000000408000      0xe0e
 .rodata        0x0000000000408000       0xa5 crt0.o
 *fill*         0x00000000004080a5        0x3 
 .rodata        0x00000000004080a8       0x9f main.o
 *fill*         0x0000000000408147        0x1 
 .rodata        0x0000000000408148      0x39d api.o
 *fill*         0x00000000004084e5       0x1b 
 .rodata        0x0000000000408500      0x100 ctype.o
                0x0000000000408500                _ctype
 .rodata        0x0000000000408600      0x2f4 stdio.o
                0x0000000000408760                hex2ascii_data
 *fill*         0x00000000004088f4        0x4 
 .rodata        0x00000000004088f8      0x510 stdlib.o
 .rodata        0x0000000000408e08        0x6 conio.o

.eh_frame       0x0000000000408e10     0x200c
 .eh_frame      0x0000000000408e10       0x34 crt0.o
 .eh_frame      0x0000000000408e44       0xfc main.o
                                        0x114 (size before relaxing)
 .eh_frame      0x0000000000408f40      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000409b6c      0x710 stdio.o
                                        0x728 (size before relaxing)
 .eh_frame      0x000000000040a27c      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x000000000040a67c      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x000000000040a99c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040aa3c      0x3bc unistd.o
                                        0x3d4 (size before relaxing)
 .eh_frame      0x000000000040adf8       0x24 stubs.o
                                         0x3c (size before relaxing)

.note.gnu.property
                0x000000000040ae1c       0x1c
 .note.gnu.property
                0x000000000040ae1c       0x1c stubs.o

.rel.dyn        0x000000000040ae38        0x0
 .rel.got       0x000000000040ae38        0x0 stubs.o
 .rel.iplt      0x000000000040ae38        0x0 stubs.o
 .rel.text      0x000000000040ae38        0x0 stubs.o

.data           0x000000000040ae40     0x11c0
                0x000000000040ae40                data = .
                0x000000000040ae40                _data = .
                0x000000000040ae40                __data = .
 *(.data)
 .data          0x000000000040ae40      0x464 crt0.o
 *fill*         0x000000000040b2a4       0x1c 
 .data          0x000000000040b2c0      0x450 main.o
 *fill*         0x000000000040b710       0x10 
 .data          0x000000000040b720      0x440 api.o
 .data          0x000000000040bb60        0x0 ctype.o
 .data          0x000000000040bb60        0x0 stdio.o
 .data          0x000000000040bb60        0x8 stdlib.o
                0x000000000040bb60                _infinity
 .data          0x000000000040bb68        0x0 string.o
 .data          0x000000000040bb68        0x0 conio.o
 .data          0x000000000040bb68        0x0 unistd.o
 .data          0x000000000040bb68        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040bb68      0x498 

.got            0x000000000040c000        0x0
 .got           0x000000000040c000        0x0 stubs.o

.got.plt        0x000000000040c000        0x0
 .got.plt       0x000000000040c000        0x0 stubs.o

.igot.plt       0x000000000040c000        0x0
 .igot.plt      0x000000000040c000        0x0 stubs.o

.bss            0x000000000040c000    0x12594
                0x000000000040c000                bss = .
                0x000000000040c000                _bss = .
                0x000000000040c000                __bss = .
 *(.bss)
 .bss           0x000000000040c000        0x0 crt0.o
 .bss           0x000000000040c000        0x0 main.o
 .bss           0x000000000040c000     0x8004 api.o
 .bss           0x0000000000414004        0x0 ctype.o
 .bss           0x0000000000414004        0x1 stdio.o
 *fill*         0x0000000000414005       0x1b 
 .bss           0x0000000000414020     0x8020 stdlib.o
                0x0000000000414020                environ
 .bss           0x000000000041c040        0x4 string.o
 .bss           0x000000000041c044        0x0 conio.o
 .bss           0x000000000041c044        0x0 unistd.o
 .bss           0x000000000041c044        0x0 stubs.o
                0x000000000041d000                . = ALIGN (0x1000)
 *fill*         0x000000000041c044      0xfbc 
 COMMON         0x000000000041d000      0xd14 crt0.o
                0x000000000041d000                g_cursor_x
                0x000000000041d004                CurrentWindow
                0x000000000041d008                stdout
                0x000000000041d00c                g_char_attrib
                0x000000000041d010                g_rows
                0x000000000041d020                Streams
                0x000000000041d0a0                g_using_gui
                0x000000000041d0a4                ApplicationInfo
                0x000000000041d0c0                prompt_out
                0x000000000041d4c0                BufferInfo
                0x000000000041d4c4                g_columns
                0x000000000041d4c8                prompt_pos
                0x000000000041d4cc                stdin
                0x000000000041d4d0                prompt_status
                0x000000000041d4e0                prompt_err
                0x000000000041d8e0                CursorInfo
                0x000000000041d8e4                stderr
                0x000000000041d900                prompt
                0x000000000041dd00                rect
                0x000000000041dd04                g_cursor_y
                0x000000000041dd08                ClientAreaInfo
                0x000000000041dd0c                current_semaphore
                0x000000000041dd10                prompt_max
 COMMON         0x000000000041dd14        0xc main.o
                0x000000000041dd14                idleError
                0x000000000041dd18                ServerStatus
                0x000000000041dd1c                idleStatus
 COMMON         0x000000000041dd20      0x438 api.o
                0x000000000041dd20                heapList
                0x000000000041e120                libcHeap
                0x000000000041e124                dialogbox_button2
                0x000000000041e128                messagebox_button1
                0x000000000041e12c                heap_start
                0x000000000041e130                g_available_heap
                0x000000000041e134                g_heap_pointer
                0x000000000041e138                HEAP_SIZE
                0x000000000041e13c                dialogbox_button1
                0x000000000041e140                heap_end
                0x000000000041e144                HEAP_END
                0x000000000041e148                messagebox_button2
                0x000000000041e14c                Heap
                0x000000000041e150                heapCount
                0x000000000041e154                HEAP_START
 *fill*         0x000000000041e158        0x8 
 COMMON         0x000000000041e160      0x434 stdlib.o
                0x000000000041e160                mm_prev_pointer
                0x000000000041e180                mmblockList
                0x000000000041e580                last_valid
                0x000000000041e584                randseed
                0x000000000041e588                mmblockCount
                0x000000000041e58c                last_size
                0x000000000041e590                current_mmblock
                0x000000000041e594                end = .
                0x000000000041e594                _end = .
                0x000000000041e594                __end = .
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
LOAD unistd.o
LOAD stubs.o
OUTPUT(INIT.BIN elf32-i386)

.comment        0x0000000000000000       0x1a
 .comment       0x0000000000000000       0x1a crt0.o
                                         0x1b (size before relaxing)
 .comment       0x000000000000001a       0x1b main.o
 .comment       0x000000000000001a       0x1b api.o
 .comment       0x000000000000001a       0x1b ctype.o
 .comment       0x000000000000001a       0x1b stdio.o
 .comment       0x000000000000001a       0x1b stdlib.o
 .comment       0x000000000000001a       0x1b string.o
 .comment       0x000000000000001a       0x1b conio.o
 .comment       0x000000000000001a       0x1b unistd.o
 .comment       0x000000000000001a       0x1b stubs.o

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
                0x0000000000000000        0x0 stubs.o
