
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
 .text          0x0000000000401000       0x75 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401075      0x132 main.o
                0x0000000000401085                idleLoop
                0x00000000004010a3                initMain
                0x00000000004010a8                driverInitialize
                0x00000000004010cb                driverUninitialize
                0x00000000004010ee                idleServices
                0x0000000000401154                idleInit
                0x0000000000401172                main
 .text          0x00000000004011a7     0x20cc api.o
                0x00000000004011a7                system_call
                0x00000000004011cf                apiSystem
                0x00000000004015d7                system1
                0x00000000004015f8                system2
                0x0000000000401619                system3
                0x000000000040163a                system4
                0x000000000040165b                system5
                0x000000000040167c                system6
                0x000000000040169d                system7
                0x00000000004016be                system8
                0x00000000004016df                system9
                0x0000000000401700                system10
                0x0000000000401721                system11
                0x0000000000401742                system12
                0x0000000000401763                system13
                0x0000000000401784                system14
                0x00000000004017a5                system15
                0x00000000004017c6                refresh_buffer
                0x00000000004018a2                print_string
                0x00000000004018a8                vsync
                0x00000000004018c2                edit_box
                0x00000000004018de                gde_system_procedure
                0x0000000000401914                SetNextWindowProcedure
                0x000000000040191e                set_cursor
                0x0000000000401935                put_char
                0x000000000040193b                gde_load_bitmap_16x16
                0x0000000000401954                apiShutDown
                0x000000000040196b                apiInitBackground
                0x0000000000401971                MessageBox
                0x0000000000401efd                mbProcedure
                0x0000000000401f6b                DialogBox
                0x000000000040231b                dbProcedure
                0x0000000000402389                call_kernel
                0x0000000000402504                call_gui
                0x0000000000402590                gde_create_window
                0x0000000000402609                gde_register_window
                0x0000000000402631                gde_close_window
                0x0000000000402659                gde_set_focus
                0x0000000000402681                gde_get_focus
                0x0000000000402696                APIKillFocus
                0x00000000004026be                APISetActiveWindow
                0x00000000004026e6                APIGetActiveWindow
                0x00000000004026fb                APIShowCurrentProcessInfo
                0x0000000000402711                APIresize_window
                0x000000000040272b                APIredraw_window
                0x0000000000402745                APIreplace_window
                0x000000000040275f                APImaximize_window
                0x000000000040277b                APIminimize_window
                0x0000000000402797                APIupdate_window
                0x00000000004027b3                APIget_foregroung_window
                0x00000000004027c9                APIset_foregroung_window
                0x00000000004027e5                apiExit
                0x0000000000402802                kill
                0x0000000000402808                dead_thread_collector
                0x000000000040281e                api_strncmp
                0x0000000000402881                refresh_screen
                0x0000000000402897                api_refresh_screen
                0x00000000004028a2                apiReboot
                0x00000000004028b8                apiSetCursor
                0x00000000004028d0                apiGetCursorX
                0x00000000004028e8                apiGetCursorY
                0x0000000000402900                apiGetClientAreaRect
                0x0000000000402918                apiSetClientAreaRect
                0x0000000000402937                gde_create_process
                0x0000000000402950                gde_create_thread
                0x0000000000402969                apiStartThread
                0x0000000000402985                apiFOpen
                0x00000000004029b1                gde_save_file
                0x0000000000402a04                apiDown
                0x0000000000402a57                apiUp
                0x0000000000402aaa                enterCriticalSection
                0x0000000000402ae5                exitCriticalSection
                0x0000000000402afe                initializeCriticalSection
                0x0000000000402b17                gde_begin_paint
                0x0000000000402b22                gde_end_paint
                0x0000000000402b2d                apiPutChar
                0x0000000000402b49                apiDefDialog
                0x0000000000402b53                apiGetSystemMetrics
                0x0000000000402b71                api_set_current_keyboard_responder
                0x0000000000402b90                api_get_current_keyboard_responder
                0x0000000000402ba8                api_set_current_mouse_responder
                0x0000000000402bc7                api_get_current_mouse_responder
                0x0000000000402bdf                api_set_window_with_text_input
                0x0000000000402c21                api_get_window_with_text_input
                0x0000000000402c39                gramadocore_init_execve
                0x0000000000402c43                apiDialog
                0x0000000000402cd2                api_getchar
                0x0000000000402cea                apiDisplayBMP
                0x00000000004030f1                apiSendMessageToProcess
                0x0000000000403134                apiSendMessageToThread
                0x0000000000403177                apiSendMessage
                0x00000000004031ad                apiDrawText
                0x00000000004031ec                apiGetWSScreenWindow
                0x0000000000403204                apiGetWSMainWindow
                0x000000000040321c                apiCreateTimer
                0x0000000000403239                apiGetSysTimeInfo
                0x0000000000403257                apiShowWindow
 .text          0x0000000000403273        0x0 ctype.o
 .text          0x0000000000403273     0x2529 stdio.o
                0x00000000004032bb                stdio_atoi
                0x0000000000403382                stdio_fntos
                0x00000000004034ac                fclose
                0x00000000004034cd                fopen
                0x00000000004034ee                scroll
                0x00000000004035bc                puts
                0x00000000004035d7                fread
                0x00000000004035e1                fwrite
                0x00000000004039ac                printf3
                0x00000000004039c9                printf_atoi
                0x0000000000403ab9                printf_i2hex
                0x0000000000403b1b                printf2
                0x0000000000403ca0                sprintf
                0x0000000000403cf5                putchar
                0x0000000000403d16                outbyte
                0x0000000000403ed4                _outbyte
                0x0000000000403f03                input
                0x0000000000404057                getchar
                0x0000000000404072                stdioInitialize
                0x000000000040425f                fflush
                0x0000000000404280                fprintf
                0x00000000004042a1                fputs
                0x00000000004042c2                gets
                0x000000000040434d                ungetc
                0x0000000000404357                ftell
                0x0000000000404361                fileno
                0x000000000040436b                fgetc
                0x000000000040438c                feof
                0x00000000004043ad                ferror
                0x00000000004043ce                fseek
                0x00000000004043ef                fputc
                0x0000000000404410                stdioSetCursor
                0x000000000040442b                stdioGetCursorX
                0x0000000000404446                stdioGetCursorY
                0x0000000000404461                scanf
                0x00000000004045fb                sscanf
                0x00000000004047b6                kvprintf
                0x0000000000405620                printf
                0x000000000040564a                vfprintf
                0x00000000004056bf                vprintf
                0x00000000004056de                stdout_printf
                0x000000000040570a                stderr_printf
                0x0000000000405736                perror
                0x000000000040574d                rewind
                0x0000000000405788                snprintf
 .text          0x000000000040579c     0x105e stdlib.o
                0x00000000004057b9                rtGetHeapStart
                0x00000000004057c3                rtGetHeapEnd
                0x00000000004057cd                rtGetHeapPointer
                0x00000000004057d7                rtGetAvailableHeap
                0x00000000004057e1                heapSetLibcHeap
                0x0000000000405894                heapAllocateMemory
                0x0000000000405ac6                FreeHeap
                0x0000000000405ad0                heapInit
                0x0000000000405c63                stdlibInitMM
                0x0000000000405cc6                libcInitRT
                0x0000000000405ce8                rand
                0x0000000000405d05                srand
                0x0000000000405d13                xmalloc
                0x0000000000405d45                stdlib_die
                0x0000000000405d7b                malloc
                0x0000000000405db7                realloc
                0x0000000000405df4                free
                0x0000000000405dfa                calloc
                0x0000000000405e40                zmalloc
                0x0000000000405e7c                system
                0x0000000000406240                stdlib_strncmp
                0x00000000004062a3                __findenv
                0x000000000040636e                getenv
                0x000000000040639b                atoi
                0x0000000000406462                reverse
                0x00000000004064c9                itoa
                0x0000000000406577                abs
                0x0000000000406587                strtod
                0x00000000004067b9                strtof
                0x00000000004067d5                strtold
                0x00000000004067e8                atof
 .text          0x00000000004067fa      0x772 string.o
                0x00000000004067fa                memcmp
                0x000000000040685f                strdup
                0x00000000004068b1                strndup
                0x0000000000406912                strrchr
                0x000000000040694d                strtoimax
                0x0000000000406957                strtoumax
                0x0000000000406961                strcasecmp
                0x00000000004069c9                strncpy
                0x0000000000406a1f                strcmp
                0x0000000000406a84                strncmp
                0x0000000000406ae7                memset
                0x0000000000406b2e                memoryZeroMemory
                0x0000000000406b55                memcpy
                0x0000000000406b92                strcpy
                0x0000000000406bc6                strcat
                0x0000000000406bf5                bcopy
                0x0000000000406c21                bzero
                0x0000000000406c41                strlen
                0x0000000000406c6f                strnlen
                0x0000000000406ca3                strcspn
                0x0000000000406d42                strspn
                0x0000000000406de1                strtok_r
                0x0000000000406ec8                strtok
                0x0000000000406ee0                strchr
                0x0000000000406f0c                strstr
 .text          0x0000000000406f6c       0x89 conio.o
                0x0000000000406f6c                putch
                0x0000000000406f90                cputs
                0x0000000000406fc5                getch
                0x0000000000406fdd                getche
 .text          0x0000000000406ff5      0x1b3 unistd.o
                0x0000000000406ff5                execve
                0x0000000000406fff                exit
                0x000000000040701f                fork
                0x0000000000407037                setuid
                0x0000000000407041                getpid
                0x0000000000407059                getppid
                0x0000000000407071                getgid
                0x000000000040707b                dup
                0x0000000000407085                dup2
                0x000000000040708f                dup3
                0x0000000000407099                fcntl
                0x00000000004070a3                nice
                0x00000000004070ad                pause
                0x00000000004070b7                mkdir
                0x00000000004070cb                rmdir
                0x00000000004070d5                link
                0x00000000004070df                mlock
                0x00000000004070e9                munlock
                0x00000000004070f3                mlockall
                0x00000000004070fd                munlockall
                0x0000000000407107                sysconf
                0x0000000000407111                fsync
                0x000000000040711b                fdatasync
                0x0000000000407125                fpathconf
                0x000000000040712f                pathconf
                0x0000000000407139                ioctl
                0x0000000000407143                open
                0x0000000000407169                close
                0x0000000000407187                pipe
 .text          0x00000000004071a8       0x28 stubs.o
                0x00000000004071a8                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004071d0      0xe30 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 stubs.o

.rodata         0x0000000000408000      0xd6e
 .rodata        0x0000000000408000       0x28 crt0.o
 .rodata        0x0000000000408028       0xa2 main.o
 *fill*         0x00000000004080ca        0x2 
 .rodata        0x00000000004080cc      0x3ab api.o
 *fill*         0x0000000000408477        0x9 
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
