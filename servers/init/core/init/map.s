
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
 .text          0x0000000000401155     0x1fee api.o
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
                0x0000000000401852                print_string
                0x0000000000401858                vsync
                0x0000000000401872                edit_box
                0x000000000040188e                chama_procedimento
                0x00000000004018a9                SetNextWindowProcedure
                0x00000000004018c4                set_cursor
                0x00000000004018e0                put_char
                0x00000000004018e6                carrega_bitmap_16x16
                0x00000000004018ff                apiShutDown
                0x0000000000401916                apiInitBackground
                0x000000000040191c                MessageBox
                0x0000000000401e72                mbProcedure
                0x0000000000401ee0                DialogBox
                0x000000000040225a                dbProcedure
                0x00000000004022c8                call_kernel
                0x0000000000402443                call_gui
                0x00000000004024cf                APICreateWindow
                0x0000000000402549                APIRegisterWindow
                0x0000000000402576                APICloseWindow
                0x00000000004025a3                APISetFocus
                0x00000000004025d0                APIGetFocus
                0x00000000004025e5                APIKillFocus
                0x0000000000402612                APISetActiveWindow
                0x000000000040263f                APIGetActiveWindow
                0x0000000000402654                APIShowCurrentProcessInfo
                0x000000000040266a                APIresize_window
                0x0000000000402684                APIredraw_window
                0x000000000040269e                APIreplace_window
                0x00000000004026b8                APImaximize_window
                0x00000000004026d4                APIminimize_window
                0x00000000004026f0                APIupdate_window
                0x000000000040270c                APIget_foregroung_window
                0x0000000000402722                APIset_foregroung_window
                0x000000000040273e                apiExit
                0x000000000040275b                kill
                0x0000000000402761                dead_thread_collector
                0x0000000000402777                api_strncmp
                0x00000000004027da                refresh_screen
                0x00000000004027f0                api_refresh_screen
                0x00000000004027fb                apiReboot
                0x0000000000402811                apiSetCursor
                0x0000000000402829                apiGetCursorX
                0x0000000000402841                apiGetCursorY
                0x0000000000402859                apiGetClientAreaRect
                0x0000000000402871                apiSetClientAreaRect
                0x0000000000402890                apiCreateProcess
                0x00000000004028a9                apiCreateThread
                0x00000000004028c2                apiStartThread
                0x00000000004028de                apiFOpen
                0x000000000040290a                apiSaveFile
                0x000000000040295d                apiDown
                0x00000000004029b0                apiUp
                0x0000000000402a03                enterCriticalSection
                0x0000000000402a3e                exitCriticalSection
                0x0000000000402a57                initializeCriticalSection
                0x0000000000402a70                apiBeginPaint
                0x0000000000402a7b                apiEndPaint
                0x0000000000402a86                apiPutChar
                0x0000000000402aa2                apiDefDialog
                0x0000000000402aac                apiGetSystemMetrics
                0x0000000000402aca                api_set_current_keyboard_responder
                0x0000000000402ae9                api_get_current_keyboard_responder
                0x0000000000402b01                api_set_current_mouse_responder
                0x0000000000402b20                api_get_current_mouse_responder
                0x0000000000402b38                api_set_window_with_text_input
                0x0000000000402b7a                api_get_window_with_text_input
                0x0000000000402b92                gramadocore_init_execve
                0x0000000000402b9c                apiDialog
                0x0000000000402c28                api_getchar
                0x0000000000402c40                apiDisplayBMP
                0x0000000000403047                apiSendMessage
                0x000000000040307d                apiDrawText
                0x00000000004030bc                apiGetWSScreenWindow
                0x00000000004030d4                apiGetWSMainWindow
                0x00000000004030ec                apiCreateTimer
                0x0000000000403109                apiGetSysTimeInfo
                0x0000000000403127                apiShowWindow
 .text          0x0000000000403143        0x0 ctype.o
 .text          0x0000000000403143     0x2546 stdio.o
                0x000000000040318b                stdio_atoi
                0x0000000000403252                stdio_fntos
                0x000000000040337c                fclose
                0x000000000040339d                fopen
                0x00000000004033be                scroll
                0x000000000040348c                puts
                0x00000000004034a7                fread
                0x00000000004034b1                fwrite
                0x000000000040387c                printf3
                0x0000000000403899                printf_atoi
                0x0000000000403989                printf_i2hex
                0x00000000004039eb                printf2
                0x0000000000403b70                sprintf
                0x0000000000403bc5                putchar
                0x0000000000403be6                outbyte
                0x0000000000403da4                _outbyte
                0x0000000000403dd3                input
                0x0000000000403f27                getchar
                0x0000000000403f42                stdioInitialize
                0x000000000040412f                fflush
                0x0000000000404150                fprintf
                0x0000000000404171                fputs
                0x0000000000404192                gets
                0x000000000040421d                ungetc
                0x0000000000404227                ftell
                0x0000000000404231                fileno
                0x000000000040423b                fgetc
                0x000000000040425c                feof
                0x000000000040427d                ferror
                0x000000000040429e                fseek
                0x00000000004042bf                fputc
                0x00000000004042e0                stdioSetCursor
                0x00000000004042fb                stdioGetCursorX
                0x0000000000404316                stdioGetCursorY
                0x0000000000404331                scanf
                0x00000000004044cb                fscanf
                0x00000000004044e8                sscanf
                0x00000000004046a3                kvprintf
                0x000000000040550d                printf
                0x0000000000405537                vfprintf
                0x00000000004055ac                vprintf
                0x00000000004055cb                stdout_printf
                0x00000000004055f7                stderr_printf
                0x0000000000405623                perror
                0x000000000040563a                rewind
                0x0000000000405675                snprintf
 .text          0x0000000000405689     0x105e stdlib.o
                0x00000000004056a6                rtGetHeapStart
                0x00000000004056b0                rtGetHeapEnd
                0x00000000004056ba                rtGetHeapPointer
                0x00000000004056c4                rtGetAvailableHeap
                0x00000000004056ce                heapSetLibcHeap
                0x0000000000405781                heapAllocateMemory
                0x00000000004059b3                FreeHeap
                0x00000000004059bd                heapInit
                0x0000000000405b50                stdlibInitMM
                0x0000000000405bb3                libcInitRT
                0x0000000000405bd5                rand
                0x0000000000405bf2                srand
                0x0000000000405c00                xmalloc
                0x0000000000405c32                stdlib_die
                0x0000000000405c68                malloc
                0x0000000000405ca4                realloc
                0x0000000000405ce1                free
                0x0000000000405ce7                calloc
                0x0000000000405d2d                zmalloc
                0x0000000000405d69                system
                0x000000000040612d                stdlib_strncmp
                0x0000000000406190                __findenv
                0x000000000040625b                getenv
                0x0000000000406288                atoi
                0x000000000040634f                reverse
                0x00000000004063b6                itoa
                0x0000000000406464                abs
                0x0000000000406474                strtod
                0x00000000004066a6                strtof
                0x00000000004066c2                strtold
                0x00000000004066d5                atof
 .text          0x00000000004066e7      0x772 string.o
                0x00000000004066e7                memcmp
                0x000000000040674c                strdup
                0x000000000040679e                strndup
                0x00000000004067ff                strrchr
                0x000000000040683a                strtoimax
                0x0000000000406844                strtoumax
                0x000000000040684e                strcasecmp
                0x00000000004068b6                strncpy
                0x000000000040690c                strcmp
                0x0000000000406971                strncmp
                0x00000000004069d4                memset
                0x0000000000406a1b                memoryZeroMemory
                0x0000000000406a42                memcpy
                0x0000000000406a7f                strcpy
                0x0000000000406ab3                strcat
                0x0000000000406ae2                bcopy
                0x0000000000406b0e                bzero
                0x0000000000406b2e                strlen
                0x0000000000406b5c                strnlen
                0x0000000000406b90                strcspn
                0x0000000000406c2f                strspn
                0x0000000000406cce                strtok_r
                0x0000000000406db5                strtok
                0x0000000000406dcd                strchr
                0x0000000000406df9                strstr
 .text          0x0000000000406e59       0x89 conio.o
                0x0000000000406e59                putch
                0x0000000000406e7d                cputs
                0x0000000000406eb2                getch
                0x0000000000406eca                getche
 .text          0x0000000000406ee2      0x1ba unistd.o
                0x0000000000406ee2                execve
                0x0000000000406eec                exit
                0x0000000000406f0c                fork
                0x0000000000406f24                setuid
                0x0000000000406f2e                getpid
                0x0000000000406f46                getppid
                0x0000000000406f5e                getgid
                0x0000000000406f68                dup
                0x0000000000406f72                dup2
                0x0000000000406f7c                dup3
                0x0000000000406f86                fcntl
                0x0000000000406f90                nice
                0x0000000000406f9a                shutdown
                0x0000000000406fa4                send
                0x0000000000406fae                pause
                0x0000000000406fb8                mkdir
                0x0000000000406fcc                rmdir
                0x0000000000406fd6                link
                0x0000000000406fe0                socket
                0x0000000000406fea                recv
                0x0000000000406ff4                mlock
                0x0000000000406ffe                munlock
                0x0000000000407008                mlockall
                0x0000000000407012                munlockall
                0x000000000040701c                sysconf
                0x0000000000407026                fsync
                0x0000000000407030                fdatasync
                0x000000000040703a                fpathconf
                0x0000000000407044                pathconf
                0x000000000040704e                ioctl
                0x0000000000407058                open
                0x000000000040707e                close
 .text          0x000000000040709c       0x28 stubs.o
                0x000000000040709c                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004070c4      0xf3c 

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

.eh_frame       0x0000000000408e10     0x2048
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
 .eh_frame      0x000000000040aa38      0x3fc unistd.o
                                        0x414 (size before relaxing)
 .eh_frame      0x000000000040ae34       0x24 stubs.o
                                         0x3c (size before relaxing)

.note.gnu.property
                0x000000000040ae58       0x1c
 .note.gnu.property
                0x000000000040ae58       0x1c stubs.o

.rel.dyn        0x000000000040ae74        0x0
 .rel.got       0x000000000040ae74        0x0 stubs.o
 .rel.iplt      0x000000000040ae74        0x0 stubs.o
 .rel.text      0x000000000040ae74        0x0 stubs.o

.data           0x000000000040ae80     0x1180
                0x000000000040ae80                data = .
                0x000000000040ae80                _data = .
                0x000000000040ae80                __data = .
 *(.data)
 .data          0x000000000040ae80      0x464 crt0.o
 *fill*         0x000000000040b2e4       0x1c 
 .data          0x000000000040b300      0x450 main.o
 *fill*         0x000000000040b750       0x10 
 .data          0x000000000040b760      0x440 api.o
 .data          0x000000000040bba0        0x0 ctype.o
 .data          0x000000000040bba0        0x0 stdio.o
 .data          0x000000000040bba0        0x8 stdlib.o
                0x000000000040bba0                _infinity
 .data          0x000000000040bba8        0x0 string.o
 .data          0x000000000040bba8        0x0 conio.o
 .data          0x000000000040bba8        0x0 unistd.o
 .data          0x000000000040bba8        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040bba8      0x458 

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
