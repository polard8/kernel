
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
 .text          0x0000000000401075      0x130 main.o
                0x0000000000401085                idleLoop
                0x00000000004010a3                initMain
                0x00000000004010a8                driverInitialize
                0x00000000004010cb                driverUninitialize
                0x00000000004010ee                idleServices
                0x0000000000401154                idleInit
                0x0000000000401172                main
 .text          0x00000000004011a5     0x20cc api.o
                0x00000000004011a5                system_call
                0x00000000004011cd                apiSystem
                0x00000000004015d5                system1
                0x00000000004015f6                system2
                0x0000000000401617                system3
                0x0000000000401638                system4
                0x0000000000401659                system5
                0x000000000040167a                system6
                0x000000000040169b                system7
                0x00000000004016bc                system8
                0x00000000004016dd                system9
                0x00000000004016fe                system10
                0x000000000040171f                system11
                0x0000000000401740                system12
                0x0000000000401761                system13
                0x0000000000401782                system14
                0x00000000004017a3                system15
                0x00000000004017c4                refresh_buffer
                0x00000000004018a0                print_string
                0x00000000004018a6                vsync
                0x00000000004018c0                edit_box
                0x00000000004018dc                gde_system_procedure
                0x0000000000401912                SetNextWindowProcedure
                0x000000000040191c                set_cursor
                0x0000000000401933                put_char
                0x0000000000401939                gde_load_bitmap_16x16
                0x0000000000401952                apiShutDown
                0x0000000000401969                apiInitBackground
                0x000000000040196f                MessageBox
                0x0000000000401efb                mbProcedure
                0x0000000000401f69                DialogBox
                0x0000000000402319                dbProcedure
                0x0000000000402387                call_kernel
                0x0000000000402502                call_gui
                0x000000000040258e                gde_create_window
                0x0000000000402607                gde_register_window
                0x000000000040262f                gde_close_window
                0x0000000000402657                gde_set_focus
                0x000000000040267f                gde_get_focus
                0x0000000000402694                APIKillFocus
                0x00000000004026bc                APISetActiveWindow
                0x00000000004026e4                APIGetActiveWindow
                0x00000000004026f9                APIShowCurrentProcessInfo
                0x000000000040270f                APIresize_window
                0x0000000000402729                APIredraw_window
                0x0000000000402743                APIreplace_window
                0x000000000040275d                APImaximize_window
                0x0000000000402779                APIminimize_window
                0x0000000000402795                APIupdate_window
                0x00000000004027b1                APIget_foregroung_window
                0x00000000004027c7                APIset_foregroung_window
                0x00000000004027e3                apiExit
                0x0000000000402800                kill
                0x0000000000402806                dead_thread_collector
                0x000000000040281c                api_strncmp
                0x000000000040287f                refresh_screen
                0x0000000000402895                api_refresh_screen
                0x00000000004028a0                apiReboot
                0x00000000004028b6                apiSetCursor
                0x00000000004028ce                apiGetCursorX
                0x00000000004028e6                apiGetCursorY
                0x00000000004028fe                apiGetClientAreaRect
                0x0000000000402916                apiSetClientAreaRect
                0x0000000000402935                gde_create_process
                0x000000000040294e                gde_create_thread
                0x0000000000402967                apiStartThread
                0x0000000000402983                apiFOpen
                0x00000000004029af                gde_save_file
                0x0000000000402a02                apiDown
                0x0000000000402a55                apiUp
                0x0000000000402aa8                enterCriticalSection
                0x0000000000402ae3                exitCriticalSection
                0x0000000000402afc                initializeCriticalSection
                0x0000000000402b15                gde_begin_paint
                0x0000000000402b20                gde_end_paint
                0x0000000000402b2b                apiPutChar
                0x0000000000402b47                apiDefDialog
                0x0000000000402b51                apiGetSystemMetrics
                0x0000000000402b6f                api_set_current_keyboard_responder
                0x0000000000402b8e                api_get_current_keyboard_responder
                0x0000000000402ba6                api_set_current_mouse_responder
                0x0000000000402bc5                api_get_current_mouse_responder
                0x0000000000402bdd                api_set_window_with_text_input
                0x0000000000402c1f                api_get_window_with_text_input
                0x0000000000402c37                gramadocore_init_execve
                0x0000000000402c41                apiDialog
                0x0000000000402cd0                api_getchar
                0x0000000000402ce8                apiDisplayBMP
                0x00000000004030ef                apiSendMessageToProcess
                0x0000000000403132                apiSendMessageToThread
                0x0000000000403175                apiSendMessage
                0x00000000004031ab                apiDrawText
                0x00000000004031ea                apiGetWSScreenWindow
                0x0000000000403202                apiGetWSMainWindow
                0x000000000040321a                apiCreateTimer
                0x0000000000403237                apiGetSysTimeInfo
                0x0000000000403255                apiShowWindow
 .text          0x0000000000403271        0x0 ctype.o
 .text          0x0000000000403271     0x2529 stdio.o
                0x00000000004032b9                stdio_atoi
                0x0000000000403380                stdio_fntos
                0x00000000004034aa                fclose
                0x00000000004034cb                fopen
                0x00000000004034ec                scroll
                0x00000000004035ba                puts
                0x00000000004035d5                fread
                0x00000000004035df                fwrite
                0x00000000004039aa                printf3
                0x00000000004039c7                printf_atoi
                0x0000000000403ab7                printf_i2hex
                0x0000000000403b19                printf2
                0x0000000000403c9e                sprintf
                0x0000000000403cf3                putchar
                0x0000000000403d14                outbyte
                0x0000000000403ed2                _outbyte
                0x0000000000403f01                input
                0x0000000000404055                getchar
                0x0000000000404070                stdioInitialize
                0x000000000040425d                fflush
                0x000000000040427e                fprintf
                0x000000000040429f                fputs
                0x00000000004042c0                gets
                0x000000000040434b                ungetc
                0x0000000000404355                ftell
                0x000000000040435f                fileno
                0x0000000000404369                fgetc
                0x000000000040438a                feof
                0x00000000004043ab                ferror
                0x00000000004043cc                fseek
                0x00000000004043ed                fputc
                0x000000000040440e                stdioSetCursor
                0x0000000000404429                stdioGetCursorX
                0x0000000000404444                stdioGetCursorY
                0x000000000040445f                scanf
                0x00000000004045f9                sscanf
                0x00000000004047b4                kvprintf
                0x000000000040561e                printf
                0x0000000000405648                vfprintf
                0x00000000004056bd                vprintf
                0x00000000004056dc                stdout_printf
                0x0000000000405708                stderr_printf
                0x0000000000405734                perror
                0x000000000040574b                rewind
                0x0000000000405786                snprintf
 .text          0x000000000040579a     0x105e stdlib.o
                0x00000000004057b7                rtGetHeapStart
                0x00000000004057c1                rtGetHeapEnd
                0x00000000004057cb                rtGetHeapPointer
                0x00000000004057d5                rtGetAvailableHeap
                0x00000000004057df                heapSetLibcHeap
                0x0000000000405892                heapAllocateMemory
                0x0000000000405ac4                FreeHeap
                0x0000000000405ace                heapInit
                0x0000000000405c61                stdlibInitMM
                0x0000000000405cc4                libcInitRT
                0x0000000000405ce6                rand
                0x0000000000405d03                srand
                0x0000000000405d11                xmalloc
                0x0000000000405d43                stdlib_die
                0x0000000000405d79                malloc
                0x0000000000405db5                realloc
                0x0000000000405df2                free
                0x0000000000405df8                calloc
                0x0000000000405e3e                zmalloc
                0x0000000000405e7a                system
                0x000000000040623e                stdlib_strncmp
                0x00000000004062a1                __findenv
                0x000000000040636c                getenv
                0x0000000000406399                atoi
                0x0000000000406460                reverse
                0x00000000004064c7                itoa
                0x0000000000406575                abs
                0x0000000000406585                strtod
                0x00000000004067b7                strtof
                0x00000000004067d3                strtold
                0x00000000004067e6                atof
 .text          0x00000000004067f8      0x772 string.o
                0x00000000004067f8                memcmp
                0x000000000040685d                strdup
                0x00000000004068af                strndup
                0x0000000000406910                strrchr
                0x000000000040694b                strtoimax
                0x0000000000406955                strtoumax
                0x000000000040695f                strcasecmp
                0x00000000004069c7                strncpy
                0x0000000000406a1d                strcmp
                0x0000000000406a82                strncmp
                0x0000000000406ae5                memset
                0x0000000000406b2c                memoryZeroMemory
                0x0000000000406b53                memcpy
                0x0000000000406b90                strcpy
                0x0000000000406bc4                strcat
                0x0000000000406bf3                bcopy
                0x0000000000406c1f                bzero
                0x0000000000406c3f                strlen
                0x0000000000406c6d                strnlen
                0x0000000000406ca1                strcspn
                0x0000000000406d40                strspn
                0x0000000000406ddf                strtok_r
                0x0000000000406ec6                strtok
                0x0000000000406ede                strchr
                0x0000000000406f0a                strstr
 .text          0x0000000000406f6a       0x89 conio.o
                0x0000000000406f6a                putch
                0x0000000000406f8e                cputs
                0x0000000000406fc3                getch
                0x0000000000406fdb                getche
 .text          0x0000000000406ff3      0x1b3 unistd.o
                0x0000000000406ff3                execve
                0x0000000000406ffd                exit
                0x000000000040701d                fork
                0x0000000000407035                setuid
                0x000000000040703f                getpid
                0x0000000000407057                getppid
                0x000000000040706f                getgid
                0x0000000000407079                dup
                0x0000000000407083                dup2
                0x000000000040708d                dup3
                0x0000000000407097                fcntl
                0x00000000004070a1                nice
                0x00000000004070ab                pause
                0x00000000004070b5                mkdir
                0x00000000004070c9                rmdir
                0x00000000004070d3                link
                0x00000000004070dd                mlock
                0x00000000004070e7                munlock
                0x00000000004070f1                mlockall
                0x00000000004070fb                munlockall
                0x0000000000407105                sysconf
                0x000000000040710f                fsync
                0x0000000000407119                fdatasync
                0x0000000000407123                fpathconf
                0x000000000040712d                pathconf
                0x0000000000407137                ioctl
                0x0000000000407141                open
                0x0000000000407167                close
                0x0000000000407185                pipe
 .text          0x00000000004071a6       0x28 stubs.o
                0x00000000004071a6                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004071ce      0xe32 

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
