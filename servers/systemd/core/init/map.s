
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
 .text          0x0000000000401058       0xfd main.o
                0x0000000000401068                idleLoop
                0x0000000000401086                initMain
                0x000000000040108b                driverInitialize
                0x00000000004010ae                driverUninitialize
                0x00000000004010d1                idleServices
                0x0000000000401137                idleInit
 .text          0x0000000000401155     0x2017 api.o
                0x0000000000401155                system_call
                0x000000000040117d                apiSystem
                0x0000000000401585                system1
                0x00000000004015a6                system2
                0x00000000004015c7                system3
                0x00000000004015e8                system4
                0x0000000000401609                system5
                0x000000000040162a                system6
                0x000000000040164b                system7
                0x000000000040166c                system8
                0x000000000040168d                system9
                0x00000000004016ae                system10
                0x00000000004016cf                system11
                0x00000000004016f0                system12
                0x0000000000401711                system13
                0x0000000000401732                system14
                0x0000000000401753                system15
                0x0000000000401774                refresh_buffer
                0x0000000000401850                print_string
                0x0000000000401856                vsync
                0x0000000000401870                edit_box
                0x000000000040188c                chama_procedimento
                0x0000000000401896                SetNextWindowProcedure
                0x00000000004018a0                set_cursor
                0x00000000004018b7                put_char
                0x00000000004018bd                carrega_bitmap_16x16
                0x00000000004018d6                apiShutDown
                0x00000000004018ed                apiInitBackground
                0x00000000004018f3                MessageBox
                0x0000000000401e7f                mbProcedure
                0x0000000000401eed                DialogBox
                0x000000000040229d                dbProcedure
                0x000000000040230b                call_kernel
                0x0000000000402486                call_gui
                0x0000000000402512                APICreateWindow
                0x000000000040258b                APIRegisterWindow
                0x00000000004025b3                APICloseWindow
                0x00000000004025db                APISetFocus
                0x0000000000402603                APIGetFocus
                0x0000000000402618                APIKillFocus
                0x0000000000402640                APISetActiveWindow
                0x0000000000402668                APIGetActiveWindow
                0x000000000040267d                APIShowCurrentProcessInfo
                0x0000000000402693                APIresize_window
                0x00000000004026ad                APIredraw_window
                0x00000000004026c7                APIreplace_window
                0x00000000004026e1                APImaximize_window
                0x00000000004026fd                APIminimize_window
                0x0000000000402719                APIupdate_window
                0x0000000000402735                APIget_foregroung_window
                0x000000000040274b                APIset_foregroung_window
                0x0000000000402767                apiExit
                0x0000000000402784                kill
                0x000000000040278a                dead_thread_collector
                0x00000000004027a0                api_strncmp
                0x0000000000402803                refresh_screen
                0x0000000000402819                api_refresh_screen
                0x0000000000402824                apiReboot
                0x000000000040283a                apiSetCursor
                0x0000000000402852                apiGetCursorX
                0x000000000040286a                apiGetCursorY
                0x0000000000402882                apiGetClientAreaRect
                0x000000000040289a                apiSetClientAreaRect
                0x00000000004028b9                apiCreateProcess
                0x00000000004028d2                apiCreateThread
                0x00000000004028eb                apiStartThread
                0x0000000000402907                apiFOpen
                0x0000000000402933                apiSaveFile
                0x0000000000402986                apiDown
                0x00000000004029d9                apiUp
                0x0000000000402a2c                enterCriticalSection
                0x0000000000402a67                exitCriticalSection
                0x0000000000402a80                initializeCriticalSection
                0x0000000000402a99                apiBeginPaint
                0x0000000000402aa4                apiEndPaint
                0x0000000000402aaf                apiPutChar
                0x0000000000402acb                apiDefDialog
                0x0000000000402ad5                apiGetSystemMetrics
                0x0000000000402af3                api_set_current_keyboard_responder
                0x0000000000402b12                api_get_current_keyboard_responder
                0x0000000000402b2a                api_set_current_mouse_responder
                0x0000000000402b49                api_get_current_mouse_responder
                0x0000000000402b61                api_set_window_with_text_input
                0x0000000000402ba3                api_get_window_with_text_input
                0x0000000000402bbb                gramadocore_init_execve
                0x0000000000402bc5                apiDialog
                0x0000000000402c51                api_getchar
                0x0000000000402c69                apiDisplayBMP
                0x0000000000403070                apiSendMessage
                0x00000000004030a6                apiDrawText
                0x00000000004030e5                apiGetWSScreenWindow
                0x00000000004030fd                apiGetWSMainWindow
                0x0000000000403115                apiCreateTimer
                0x0000000000403132                apiGetSysTimeInfo
                0x0000000000403150                apiShowWindow
 .text          0x000000000040316c        0x0 ctype.o
 .text          0x000000000040316c     0x2546 stdio.o
                0x00000000004031b4                stdio_atoi
                0x000000000040327b                stdio_fntos
                0x00000000004033a5                fclose
                0x00000000004033c6                fopen
                0x00000000004033e7                scroll
                0x00000000004034b5                puts
                0x00000000004034d0                fread
                0x00000000004034da                fwrite
                0x00000000004038a5                printf3
                0x00000000004038c2                printf_atoi
                0x00000000004039b2                printf_i2hex
                0x0000000000403a14                printf2
                0x0000000000403b99                sprintf
                0x0000000000403bee                putchar
                0x0000000000403c0f                outbyte
                0x0000000000403dcd                _outbyte
                0x0000000000403dfc                input
                0x0000000000403f50                getchar
                0x0000000000403f6b                stdioInitialize
                0x0000000000404158                fflush
                0x0000000000404179                fprintf
                0x000000000040419a                fputs
                0x00000000004041bb                gets
                0x0000000000404246                ungetc
                0x0000000000404250                ftell
                0x000000000040425a                fileno
                0x0000000000404264                fgetc
                0x0000000000404285                feof
                0x00000000004042a6                ferror
                0x00000000004042c7                fseek
                0x00000000004042e8                fputc
                0x0000000000404309                stdioSetCursor
                0x0000000000404324                stdioGetCursorX
                0x000000000040433f                stdioGetCursorY
                0x000000000040435a                scanf
                0x00000000004044f4                fscanf
                0x0000000000404511                sscanf
                0x00000000004046cc                kvprintf
                0x0000000000405536                printf
                0x0000000000405560                vfprintf
                0x00000000004055d5                vprintf
                0x00000000004055f4                stdout_printf
                0x0000000000405620                stderr_printf
                0x000000000040564c                perror
                0x0000000000405663                rewind
                0x000000000040569e                snprintf
 .text          0x00000000004056b2     0x105e stdlib.o
                0x00000000004056cf                rtGetHeapStart
                0x00000000004056d9                rtGetHeapEnd
                0x00000000004056e3                rtGetHeapPointer
                0x00000000004056ed                rtGetAvailableHeap
                0x00000000004056f7                heapSetLibcHeap
                0x00000000004057aa                heapAllocateMemory
                0x00000000004059dc                FreeHeap
                0x00000000004059e6                heapInit
                0x0000000000405b79                stdlibInitMM
                0x0000000000405bdc                libcInitRT
                0x0000000000405bfe                rand
                0x0000000000405c1b                srand
                0x0000000000405c29                xmalloc
                0x0000000000405c5b                stdlib_die
                0x0000000000405c91                malloc
                0x0000000000405ccd                realloc
                0x0000000000405d0a                free
                0x0000000000405d10                calloc
                0x0000000000405d56                zmalloc
                0x0000000000405d92                system
                0x0000000000406156                stdlib_strncmp
                0x00000000004061b9                __findenv
                0x0000000000406284                getenv
                0x00000000004062b1                atoi
                0x0000000000406378                reverse
                0x00000000004063df                itoa
                0x000000000040648d                abs
                0x000000000040649d                strtod
                0x00000000004066cf                strtof
                0x00000000004066eb                strtold
                0x00000000004066fe                atof
 .text          0x0000000000406710      0x772 string.o
                0x0000000000406710                memcmp
                0x0000000000406775                strdup
                0x00000000004067c7                strndup
                0x0000000000406828                strrchr
                0x0000000000406863                strtoimax
                0x000000000040686d                strtoumax
                0x0000000000406877                strcasecmp
                0x00000000004068df                strncpy
                0x0000000000406935                strcmp
                0x000000000040699a                strncmp
                0x00000000004069fd                memset
                0x0000000000406a44                memoryZeroMemory
                0x0000000000406a6b                memcpy
                0x0000000000406aa8                strcpy
                0x0000000000406adc                strcat
                0x0000000000406b0b                bcopy
                0x0000000000406b37                bzero
                0x0000000000406b57                strlen
                0x0000000000406b85                strnlen
                0x0000000000406bb9                strcspn
                0x0000000000406c58                strspn
                0x0000000000406cf7                strtok_r
                0x0000000000406dde                strtok
                0x0000000000406df6                strchr
                0x0000000000406e22                strstr
 .text          0x0000000000406e82       0x89 conio.o
                0x0000000000406e82                putch
                0x0000000000406ea6                cputs
                0x0000000000406edb                getch
                0x0000000000406ef3                getche
 .text          0x0000000000406f0b      0x192 unistd.o
                0x0000000000406f0b                execve
                0x0000000000406f15                exit
                0x0000000000406f35                fork
                0x0000000000406f4d                setuid
                0x0000000000406f57                getpid
                0x0000000000406f6f                getppid
                0x0000000000406f87                getgid
                0x0000000000406f91                dup
                0x0000000000406f9b                dup2
                0x0000000000406fa5                dup3
                0x0000000000406faf                fcntl
                0x0000000000406fb9                nice
                0x0000000000406fc3                pause
                0x0000000000406fcd                mkdir
                0x0000000000406fe1                rmdir
                0x0000000000406feb                link
                0x0000000000406ff5                mlock
                0x0000000000406fff                munlock
                0x0000000000407009                mlockall
                0x0000000000407013                munlockall
                0x000000000040701d                sysconf
                0x0000000000407027                fsync
                0x0000000000407031                fdatasync
                0x000000000040703b                fpathconf
                0x0000000000407045                pathconf
                0x000000000040704f                ioctl
                0x0000000000407059                open
                0x000000000040707f                close
 .text          0x000000000040709d       0x28 stubs.o
                0x000000000040709d                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004070c5      0xf3b 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 stubs.o

.rodata         0x0000000000408000      0xe0e
 .rodata        0x0000000000408000       0xa5 crt0.o
 *fill*         0x00000000004080a5        0x3 
 .rodata        0x00000000004080a8       0x9f main.o
 *fill*         0x0000000000408147        0x1 
 .rodata        0x0000000000408148      0x3ab api.o
 *fill*         0x00000000004084f3        0xd 
 .rodata        0x0000000000408500      0x100 ctype.o
                0x0000000000408500                _ctype
 .rodata        0x0000000000408600      0x2f4 stdio.o
                0x0000000000408760                hex2ascii_data
 *fill*         0x00000000004088f4        0x4 
 .rodata        0x00000000004088f8      0x510 stdlib.o
 .rodata        0x0000000000408e08        0x6 conio.o

.eh_frame       0x0000000000408e10     0x1fc8
 .eh_frame      0x0000000000408e10       0x34 crt0.o
 .eh_frame      0x0000000000408e44       0xf8 main.o
                                        0x110 (size before relaxing)
 .eh_frame      0x0000000000408f3c      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000409b68      0x710 stdio.o
                                        0x728 (size before relaxing)
 .eh_frame      0x000000000040a278      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x000000000040a678      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x000000000040a998       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040aa38      0x37c unistd.o
                                        0x394 (size before relaxing)
 .eh_frame      0x000000000040adb4       0x24 stubs.o
                                         0x3c (size before relaxing)

.note.gnu.property
                0x000000000040add8       0x1c
 .note.gnu.property
                0x000000000040add8       0x1c stubs.o

.rel.dyn        0x000000000040adf4        0x0
 .rel.got       0x000000000040adf4        0x0 stubs.o
 .rel.iplt      0x000000000040adf4        0x0 stubs.o
 .rel.text      0x000000000040adf4        0x0 stubs.o

.data           0x000000000040ae00     0x1200
                0x000000000040ae00                data = .
                0x000000000040ae00                _data = .
                0x000000000040ae00                __data = .
 *(.data)
 .data          0x000000000040ae00      0x464 crt0.o
 *fill*         0x000000000040b264       0x1c 
 .data          0x000000000040b280      0x450 main.o
 *fill*         0x000000000040b6d0       0x10 
 .data          0x000000000040b6e0      0x440 api.o
 .data          0x000000000040bb20        0x0 ctype.o
 .data          0x000000000040bb20        0x0 stdio.o
 .data          0x000000000040bb20        0x8 stdlib.o
                0x000000000040bb20                _infinity
 .data          0x000000000040bb28        0x0 string.o
 .data          0x000000000040bb28        0x0 conio.o
 .data          0x000000000040bb28        0x0 unistd.o
 .data          0x000000000040bb28        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040bb28      0x4d8 

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
