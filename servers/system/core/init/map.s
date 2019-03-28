
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
 .text          0x0000000000401195     0x2050 api.o
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
                0x00000000004018cc                gde_call_procedure
                0x00000000004018d6                SetNextWindowProcedure
                0x00000000004018e0                set_cursor
                0x00000000004018f7                put_char
                0x00000000004018fd                gde_load_bitmap_16x16
                0x0000000000401916                apiShutDown
                0x000000000040192d                apiInitBackground
                0x0000000000401933                MessageBox
                0x0000000000401ebf                mbProcedure
                0x0000000000401f2d                DialogBox
                0x00000000004022dd                dbProcedure
                0x000000000040234b                call_kernel
                0x00000000004024c6                call_gui
                0x0000000000402552                gde_create_window
                0x00000000004025cb                gde_register_window
                0x00000000004025f3                gde_close_window
                0x000000000040261b                gde_set_focus
                0x0000000000402643                gde_get_focus
                0x0000000000402658                APIKillFocus
                0x0000000000402680                APISetActiveWindow
                0x00000000004026a8                APIGetActiveWindow
                0x00000000004026bd                APIShowCurrentProcessInfo
                0x00000000004026d3                APIresize_window
                0x00000000004026ed                APIredraw_window
                0x0000000000402707                APIreplace_window
                0x0000000000402721                APImaximize_window
                0x000000000040273d                APIminimize_window
                0x0000000000402759                APIupdate_window
                0x0000000000402775                APIget_foregroung_window
                0x000000000040278b                APIset_foregroung_window
                0x00000000004027a7                apiExit
                0x00000000004027c4                kill
                0x00000000004027ca                dead_thread_collector
                0x00000000004027e0                api_strncmp
                0x0000000000402843                refresh_screen
                0x0000000000402859                api_refresh_screen
                0x0000000000402864                apiReboot
                0x000000000040287a                apiSetCursor
                0x0000000000402892                apiGetCursorX
                0x00000000004028aa                apiGetCursorY
                0x00000000004028c2                apiGetClientAreaRect
                0x00000000004028da                apiSetClientAreaRect
                0x00000000004028f9                gde_create_process
                0x0000000000402912                gde_create_thread
                0x000000000040292b                apiStartThread
                0x0000000000402947                apiFOpen
                0x0000000000402973                gde_save_file
                0x00000000004029c6                apiDown
                0x0000000000402a19                apiUp
                0x0000000000402a6c                enterCriticalSection
                0x0000000000402aa7                exitCriticalSection
                0x0000000000402ac0                initializeCriticalSection
                0x0000000000402ad9                gde_begin_paint
                0x0000000000402ae4                gde_end_paint
                0x0000000000402aef                apiPutChar
                0x0000000000402b0b                apiDefDialog
                0x0000000000402b15                apiGetSystemMetrics
                0x0000000000402b33                api_set_current_keyboard_responder
                0x0000000000402b52                api_get_current_keyboard_responder
                0x0000000000402b6a                api_set_current_mouse_responder
                0x0000000000402b89                api_get_current_mouse_responder
                0x0000000000402ba1                api_set_window_with_text_input
                0x0000000000402be3                api_get_window_with_text_input
                0x0000000000402bfb                gramadocore_init_execve
                0x0000000000402c05                apiDialog
                0x0000000000402c94                api_getchar
                0x0000000000402cac                apiDisplayBMP
                0x00000000004030b3                apiSendMessageToProcess
                0x00000000004030e9                apiSendMessage
                0x000000000040311f                apiDrawText
                0x000000000040315e                apiGetWSScreenWindow
                0x0000000000403176                apiGetWSMainWindow
                0x000000000040318e                apiCreateTimer
                0x00000000004031ab                apiGetSysTimeInfo
                0x00000000004031c9                apiShowWindow
 .text          0x00000000004031e5        0x0 ctype.o
 .text          0x00000000004031e5     0x2529 stdio.o
                0x000000000040322d                stdio_atoi
                0x00000000004032f4                stdio_fntos
                0x000000000040341e                fclose
                0x000000000040343f                fopen
                0x0000000000403460                scroll
                0x000000000040352e                puts
                0x0000000000403549                fread
                0x0000000000403553                fwrite
                0x000000000040391e                printf3
                0x000000000040393b                printf_atoi
                0x0000000000403a2b                printf_i2hex
                0x0000000000403a8d                printf2
                0x0000000000403c12                sprintf
                0x0000000000403c67                putchar
                0x0000000000403c88                outbyte
                0x0000000000403e46                _outbyte
                0x0000000000403e75                input
                0x0000000000403fc9                getchar
                0x0000000000403fe4                stdioInitialize
                0x00000000004041d1                fflush
                0x00000000004041f2                fprintf
                0x0000000000404213                fputs
                0x0000000000404234                gets
                0x00000000004042bf                ungetc
                0x00000000004042c9                ftell
                0x00000000004042d3                fileno
                0x00000000004042dd                fgetc
                0x00000000004042fe                feof
                0x000000000040431f                ferror
                0x0000000000404340                fseek
                0x0000000000404361                fputc
                0x0000000000404382                stdioSetCursor
                0x000000000040439d                stdioGetCursorX
                0x00000000004043b8                stdioGetCursorY
                0x00000000004043d3                scanf
                0x000000000040456d                sscanf
                0x0000000000404728                kvprintf
                0x0000000000405592                printf
                0x00000000004055bc                vfprintf
                0x0000000000405631                vprintf
                0x0000000000405650                stdout_printf
                0x000000000040567c                stderr_printf
                0x00000000004056a8                perror
                0x00000000004056bf                rewind
                0x00000000004056fa                snprintf
 .text          0x000000000040570e     0x105e stdlib.o
                0x000000000040572b                rtGetHeapStart
                0x0000000000405735                rtGetHeapEnd
                0x000000000040573f                rtGetHeapPointer
                0x0000000000405749                rtGetAvailableHeap
                0x0000000000405753                heapSetLibcHeap
                0x0000000000405806                heapAllocateMemory
                0x0000000000405a38                FreeHeap
                0x0000000000405a42                heapInit
                0x0000000000405bd5                stdlibInitMM
                0x0000000000405c38                libcInitRT
                0x0000000000405c5a                rand
                0x0000000000405c77                srand
                0x0000000000405c85                xmalloc
                0x0000000000405cb7                stdlib_die
                0x0000000000405ced                malloc
                0x0000000000405d29                realloc
                0x0000000000405d66                free
                0x0000000000405d6c                calloc
                0x0000000000405db2                zmalloc
                0x0000000000405dee                system
                0x00000000004061b2                stdlib_strncmp
                0x0000000000406215                __findenv
                0x00000000004062e0                getenv
                0x000000000040630d                atoi
                0x00000000004063d4                reverse
                0x000000000040643b                itoa
                0x00000000004064e9                abs
                0x00000000004064f9                strtod
                0x000000000040672b                strtof
                0x0000000000406747                strtold
                0x000000000040675a                atof
 .text          0x000000000040676c      0x772 string.o
                0x000000000040676c                memcmp
                0x00000000004067d1                strdup
                0x0000000000406823                strndup
                0x0000000000406884                strrchr
                0x00000000004068bf                strtoimax
                0x00000000004068c9                strtoumax
                0x00000000004068d3                strcasecmp
                0x000000000040693b                strncpy
                0x0000000000406991                strcmp
                0x00000000004069f6                strncmp
                0x0000000000406a59                memset
                0x0000000000406aa0                memoryZeroMemory
                0x0000000000406ac7                memcpy
                0x0000000000406b04                strcpy
                0x0000000000406b38                strcat
                0x0000000000406b67                bcopy
                0x0000000000406b93                bzero
                0x0000000000406bb3                strlen
                0x0000000000406be1                strnlen
                0x0000000000406c15                strcspn
                0x0000000000406cb4                strspn
                0x0000000000406d53                strtok_r
                0x0000000000406e3a                strtok
                0x0000000000406e52                strchr
                0x0000000000406e7e                strstr
 .text          0x0000000000406ede       0x89 conio.o
                0x0000000000406ede                putch
                0x0000000000406f02                cputs
                0x0000000000406f37                getch
                0x0000000000406f4f                getche
 .text          0x0000000000406f67      0x1b3 unistd.o
                0x0000000000406f67                execve
                0x0000000000406f71                exit
                0x0000000000406f91                fork
                0x0000000000406fa9                setuid
                0x0000000000406fb3                getpid
                0x0000000000406fcb                getppid
                0x0000000000406fe3                getgid
                0x0000000000406fed                dup
                0x0000000000406ff7                dup2
                0x0000000000407001                dup3
                0x000000000040700b                fcntl
                0x0000000000407015                nice
                0x000000000040701f                pause
                0x0000000000407029                mkdir
                0x000000000040703d                rmdir
                0x0000000000407047                link
                0x0000000000407051                mlock
                0x000000000040705b                munlock
                0x0000000000407065                mlockall
                0x000000000040706f                munlockall
                0x0000000000407079                sysconf
                0x0000000000407083                fsync
                0x000000000040708d                fdatasync
                0x0000000000407097                fpathconf
                0x00000000004070a1                pathconf
                0x00000000004070ab                ioctl
                0x00000000004070b5                open
                0x00000000004070db                close
                0x00000000004070f9                pipe
 .text          0x000000000040711a       0x28 stubs.o
                0x000000000040711a                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x0000000000407142      0xebe 

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

.eh_frame       0x0000000000408d70     0x200c
 .eh_frame      0x0000000000408d70       0x34 crt0.o
 .eh_frame      0x0000000000408da4      0x11c main.o
                                        0x134 (size before relaxing)
 .eh_frame      0x0000000000408ec0      0xc4c api.o
                                        0xc64 (size before relaxing)
 .eh_frame      0x0000000000409b0c      0x6f0 stdio.o
                                        0x708 (size before relaxing)
 .eh_frame      0x000000000040a1fc      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x000000000040a5fc      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x000000000040a91c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040a9bc      0x39c unistd.o
                                        0x3b4 (size before relaxing)
 .eh_frame      0x000000000040ad58       0x24 stubs.o
                                         0x3c (size before relaxing)

.note.gnu.property
                0x000000000040ad7c       0x1c
 .note.gnu.property
                0x000000000040ad7c       0x1c stubs.o

.rel.dyn        0x000000000040ad98        0x0
 .rel.got       0x000000000040ad98        0x0 stubs.o
 .rel.iplt      0x000000000040ad98        0x0 stubs.o
 .rel.text      0x000000000040ad98        0x0 stubs.o

.data           0x000000000040ada0     0x1260
                0x000000000040ada0                data = .
                0x000000000040ada0                _data = .
                0x000000000040ada0                __data = .
 *(.data)
 .data          0x000000000040ada0      0x448 crt0.o
 *fill*         0x000000000040b1e8       0x18 
 .data          0x000000000040b200      0x440 main.o
 .data          0x000000000040b640      0x440 api.o
 .data          0x000000000040ba80        0x0 ctype.o
 .data          0x000000000040ba80        0x0 stdio.o
 .data          0x000000000040ba80        0x8 stdlib.o
                0x000000000040ba80                _infinity
 .data          0x000000000040ba88        0x0 string.o
 .data          0x000000000040ba88        0x0 conio.o
 .data          0x000000000040ba88        0x0 unistd.o
 .data          0x000000000040ba88        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040ba88      0x578 

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
