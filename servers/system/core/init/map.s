
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
errno               0x4               unistd.o
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
 .text          0x0000000000401000       0x65 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401065      0x130 main.o
                0x0000000000401075                idleLoop
                0x0000000000401093                initMain
                0x0000000000401098                driverInitialize
                0x00000000004010bb                driverUninitialize
                0x00000000004010de                idleServices
                0x0000000000401144                idleInit
                0x0000000000401162                main
 .text          0x0000000000401195     0x20cc api.o
                0x0000000000401195                system_call
                0x00000000004011bd                apiSystem
                0x00000000004015c5                system1
                0x00000000004015e6                system2
                0x0000000000401607                system3
                0x0000000000401628                system4
                0x0000000000401649                system5
                0x000000000040166a                system6
                0x000000000040168b                system7
                0x00000000004016ac                system8
                0x00000000004016cd                system9
                0x00000000004016ee                system10
                0x000000000040170f                system11
                0x0000000000401730                system12
                0x0000000000401751                system13
                0x0000000000401772                system14
                0x0000000000401793                system15
                0x00000000004017b4                refresh_buffer
                0x0000000000401890                print_string
                0x0000000000401896                vsync
                0x00000000004018b0                edit_box
                0x00000000004018cc                gde_system_procedure
                0x0000000000401902                SetNextWindowProcedure
                0x000000000040190c                set_cursor
                0x0000000000401923                put_char
                0x0000000000401929                gde_load_bitmap_16x16
                0x0000000000401942                apiShutDown
                0x0000000000401959                apiInitBackground
                0x000000000040195f                MessageBox
                0x0000000000401eeb                mbProcedure
                0x0000000000401f59                DialogBox
                0x0000000000402309                dbProcedure
                0x0000000000402377                call_kernel
                0x00000000004024f2                call_gui
                0x000000000040257e                gde_create_window
                0x00000000004025f7                gde_register_window
                0x000000000040261f                gde_close_window
                0x0000000000402647                gde_set_focus
                0x000000000040266f                gde_get_focus
                0x0000000000402684                APIKillFocus
                0x00000000004026ac                APISetActiveWindow
                0x00000000004026d4                APIGetActiveWindow
                0x00000000004026e9                APIShowCurrentProcessInfo
                0x00000000004026ff                APIresize_window
                0x0000000000402719                APIredraw_window
                0x0000000000402733                APIreplace_window
                0x000000000040274d                APImaximize_window
                0x0000000000402769                APIminimize_window
                0x0000000000402785                APIupdate_window
                0x00000000004027a1                APIget_foregroung_window
                0x00000000004027b7                APIset_foregroung_window
                0x00000000004027d3                apiExit
                0x00000000004027f0                kill
                0x00000000004027f6                dead_thread_collector
                0x000000000040280c                api_strncmp
                0x000000000040286f                refresh_screen
                0x0000000000402885                api_refresh_screen
                0x0000000000402890                apiReboot
                0x00000000004028a6                apiSetCursor
                0x00000000004028be                apiGetCursorX
                0x00000000004028d6                apiGetCursorY
                0x00000000004028ee                apiGetClientAreaRect
                0x0000000000402906                apiSetClientAreaRect
                0x0000000000402925                gde_create_process
                0x000000000040293e                gde_create_thread
                0x0000000000402957                apiStartThread
                0x0000000000402973                apiFOpen
                0x000000000040299f                gde_save_file
                0x00000000004029f2                apiDown
                0x0000000000402a45                apiUp
                0x0000000000402a98                enterCriticalSection
                0x0000000000402ad3                exitCriticalSection
                0x0000000000402aec                initializeCriticalSection
                0x0000000000402b05                gde_begin_paint
                0x0000000000402b10                gde_end_paint
                0x0000000000402b1b                apiPutChar
                0x0000000000402b37                apiDefDialog
                0x0000000000402b41                apiGetSystemMetrics
                0x0000000000402b5f                api_set_current_keyboard_responder
                0x0000000000402b7e                api_get_current_keyboard_responder
                0x0000000000402b96                api_set_current_mouse_responder
                0x0000000000402bb5                api_get_current_mouse_responder
                0x0000000000402bcd                api_set_window_with_text_input
                0x0000000000402c0f                api_get_window_with_text_input
                0x0000000000402c27                gramadocore_init_execve
                0x0000000000402c31                apiDialog
                0x0000000000402cc0                api_getchar
                0x0000000000402cd8                apiDisplayBMP
                0x00000000004030df                apiSendMessageToProcess
                0x0000000000403122                apiSendMessageToThread
                0x0000000000403165                apiSendMessage
                0x000000000040319b                apiDrawText
                0x00000000004031da                apiGetWSScreenWindow
                0x00000000004031f2                apiGetWSMainWindow
                0x000000000040320a                apiCreateTimer
                0x0000000000403227                apiGetSysTimeInfo
                0x0000000000403245                apiShowWindow
 .text          0x0000000000403261        0x0 ctype.o
 .text          0x0000000000403261     0x2529 stdio.o
                0x00000000004032a9                stdio_atoi
                0x0000000000403370                stdio_fntos
                0x000000000040349a                fclose
                0x00000000004034bb                fopen
                0x00000000004034dc                scroll
                0x00000000004035aa                puts
                0x00000000004035c5                fread
                0x00000000004035cf                fwrite
                0x000000000040399a                printf3
                0x00000000004039b7                printf_atoi
                0x0000000000403aa7                printf_i2hex
                0x0000000000403b09                printf2
                0x0000000000403c8e                sprintf
                0x0000000000403ce3                putchar
                0x0000000000403d04                outbyte
                0x0000000000403ec2                _outbyte
                0x0000000000403ef1                input
                0x0000000000404045                getchar
                0x0000000000404060                stdioInitialize
                0x000000000040424d                fflush
                0x000000000040426e                fprintf
                0x000000000040428f                fputs
                0x00000000004042b0                gets
                0x000000000040433b                ungetc
                0x0000000000404345                ftell
                0x000000000040434f                fileno
                0x0000000000404359                fgetc
                0x000000000040437a                feof
                0x000000000040439b                ferror
                0x00000000004043bc                fseek
                0x00000000004043dd                fputc
                0x00000000004043fe                stdioSetCursor
                0x0000000000404419                stdioGetCursorX
                0x0000000000404434                stdioGetCursorY
                0x000000000040444f                scanf
                0x00000000004045e9                sscanf
                0x00000000004047a4                kvprintf
                0x000000000040560e                printf
                0x0000000000405638                vfprintf
                0x00000000004056ad                vprintf
                0x00000000004056cc                stdout_printf
                0x00000000004056f8                stderr_printf
                0x0000000000405724                perror
                0x000000000040573b                rewind
                0x0000000000405776                snprintf
 .text          0x000000000040578a     0x105e stdlib.o
                0x00000000004057a7                rtGetHeapStart
                0x00000000004057b1                rtGetHeapEnd
                0x00000000004057bb                rtGetHeapPointer
                0x00000000004057c5                rtGetAvailableHeap
                0x00000000004057cf                heapSetLibcHeap
                0x0000000000405882                heapAllocateMemory
                0x0000000000405ab4                FreeHeap
                0x0000000000405abe                heapInit
                0x0000000000405c51                stdlibInitMM
                0x0000000000405cb4                libcInitRT
                0x0000000000405cd6                rand
                0x0000000000405cf3                srand
                0x0000000000405d01                xmalloc
                0x0000000000405d33                stdlib_die
                0x0000000000405d69                malloc
                0x0000000000405da5                realloc
                0x0000000000405de2                free
                0x0000000000405de8                calloc
                0x0000000000405e2e                zmalloc
                0x0000000000405e6a                system
                0x000000000040622e                stdlib_strncmp
                0x0000000000406291                __findenv
                0x000000000040635c                getenv
                0x0000000000406389                atoi
                0x0000000000406450                reverse
                0x00000000004064b7                itoa
                0x0000000000406565                abs
                0x0000000000406575                strtod
                0x00000000004067a7                strtof
                0x00000000004067c3                strtold
                0x00000000004067d6                atof
 .text          0x00000000004067e8      0x772 string.o
                0x00000000004067e8                memcmp
                0x000000000040684d                strdup
                0x000000000040689f                strndup
                0x0000000000406900                strrchr
                0x000000000040693b                strtoimax
                0x0000000000406945                strtoumax
                0x000000000040694f                strcasecmp
                0x00000000004069b7                strncpy
                0x0000000000406a0d                strcmp
                0x0000000000406a72                strncmp
                0x0000000000406ad5                memset
                0x0000000000406b1c                memoryZeroMemory
                0x0000000000406b43                memcpy
                0x0000000000406b80                strcpy
                0x0000000000406bb4                strcat
                0x0000000000406be3                bcopy
                0x0000000000406c0f                bzero
                0x0000000000406c2f                strlen
                0x0000000000406c5d                strnlen
                0x0000000000406c91                strcspn
                0x0000000000406d30                strspn
                0x0000000000406dcf                strtok_r
                0x0000000000406eb6                strtok
                0x0000000000406ece                strchr
                0x0000000000406efa                strstr
 .text          0x0000000000406f5a       0x89 conio.o
                0x0000000000406f5a                putch
                0x0000000000406f7e                cputs
                0x0000000000406fb3                getch
                0x0000000000406fcb                getche
 .text          0x0000000000406fe3      0x1b3 unistd.o
                0x0000000000406fe3                execve
                0x0000000000406fed                exit
                0x000000000040700d                fork
                0x0000000000407025                setuid
                0x000000000040702f                getpid
                0x0000000000407047                getppid
                0x000000000040705f                getgid
                0x0000000000407069                dup
                0x0000000000407073                dup2
                0x000000000040707d                dup3
                0x0000000000407087                fcntl
                0x0000000000407091                nice
                0x000000000040709b                pause
                0x00000000004070a5                mkdir
                0x00000000004070b9                rmdir
                0x00000000004070c3                link
                0x00000000004070cd                mlock
                0x00000000004070d7                munlock
                0x00000000004070e1                mlockall
                0x00000000004070eb                munlockall
                0x00000000004070f5                sysconf
                0x00000000004070ff                fsync
                0x0000000000407109                fdatasync
                0x0000000000407113                fpathconf
                0x000000000040711d                pathconf
                0x0000000000407127                ioctl
                0x0000000000407131                open
                0x0000000000407157                close
                0x0000000000407175                pipe
 .text          0x0000000000407196       0x28 stubs.o
                0x0000000000407196                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004071be      0xe42 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 stubs.o

.rodata         0x0000000000408000      0xd6e
 .rodata        0x0000000000408000       0x28 crt0.o
 .rodata        0x0000000000408028       0x9a main.o
 *fill*         0x00000000004080c2        0x2 
 .rodata        0x00000000004080c4      0x3ab api.o
 *fill*         0x000000000040846f       0x11 
 .rodata        0x0000000000408480      0x100 ctype.o
                0x0000000000408480                _ctype
 .rodata        0x0000000000408580      0x2d4 stdio.o
                0x00000000004086c0                hex2ascii_data
 *fill*         0x0000000000408854        0x4 
 .rodata        0x0000000000408858      0x510 stdlib.o
 .rodata        0x0000000000408d68        0x6 conio.o

.eh_frame       0x0000000000408d70     0x202c
 .eh_frame      0x0000000000408d70       0x34 crt0.o
 .eh_frame      0x0000000000408da4      0x11c main.o
                                        0x134 (size before relaxing)
 .eh_frame      0x0000000000408ec0      0xc6c api.o
                                        0xc84 (size before relaxing)
 .eh_frame      0x0000000000409b2c      0x6f0 stdio.o
                                        0x708 (size before relaxing)
 .eh_frame      0x000000000040a21c      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x000000000040a61c      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x000000000040a93c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040a9dc      0x39c unistd.o
                                        0x3b4 (size before relaxing)
 .eh_frame      0x000000000040ad78       0x24 stubs.o
                                         0x3c (size before relaxing)

.note.gnu.property
                0x000000000040ad9c       0x1c
 .note.gnu.property
                0x000000000040ad9c       0x1c stubs.o

.rel.dyn        0x000000000040adb8        0x0
 .rel.got       0x000000000040adb8        0x0 stubs.o
 .rel.iplt      0x000000000040adb8        0x0 stubs.o
 .rel.text      0x000000000040adb8        0x0 stubs.o

.data           0x000000000040adc0     0x1240
                0x000000000040adc0                data = .
                0x000000000040adc0                _data = .
                0x000000000040adc0                __data = .
 *(.data)
 .data          0x000000000040adc0      0x448 crt0.o
 *fill*         0x000000000040b208       0x18 
 .data          0x000000000040b220      0x440 main.o
 .data          0x000000000040b660      0x440 api.o
 .data          0x000000000040baa0        0x0 ctype.o
 .data          0x000000000040baa0        0x0 stdio.o
 .data          0x000000000040baa0        0x8 stdlib.o
                0x000000000040baa0                _infinity
 .data          0x000000000040baa8        0x0 string.o
 .data          0x000000000040baa8        0x0 conio.o
 .data          0x000000000040baa8        0x0 unistd.o
 .data          0x000000000040baa8        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040baa8      0x558 

.got            0x000000000040c000        0x0
 .got           0x000000000040c000        0x0 stubs.o

.got.plt        0x000000000040c000        0x0
 .got.plt       0x000000000040c000        0x0 stubs.o

.igot.plt       0x000000000040c000        0x0
 .igot.plt      0x000000000040c000        0x0 stubs.o

.bss            0x000000000040c000    0x12598
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
 COMMON         0x000000000041e594        0x4 unistd.o
                0x000000000041e594                errno
                0x000000000041e598                end = .
                0x000000000041e598                _end = .
                0x000000000041e598                __end = .
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
