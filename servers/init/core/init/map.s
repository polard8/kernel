
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


.text           0x0000000000401000     0x6000
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
 .text          0x0000000000403148     0x252b stdio.o
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
                0x0000000000403f2c                stdio_system_call
                0x0000000000403f54                getchar
                0x0000000000403f6c                stdioInitialize
                0x0000000000404159                fflush
                0x0000000000404177                fprintf
                0x0000000000404195                fputs
                0x00000000004041b3                gets
                0x000000000040423e                ungetc
                0x0000000000404248                ftell
                0x0000000000404252                fileno
                0x000000000040425c                fgetc
                0x000000000040427a                feof
                0x0000000000404298                ferror
                0x00000000004042b6                fseek
                0x00000000004042d4                fputc
                0x00000000004042f2                stdioSetCursor
                0x000000000040430a                stdioGetCursorX
                0x0000000000404322                stdioGetCursorY
                0x000000000040433a                scanf
                0x00000000004044d4                fscanf
                0x00000000004044f1                sscanf
                0x00000000004046ac                kvprintf
                0x0000000000405516                printf
                0x0000000000405540                vfprintf
                0x00000000004055b5                stdout_printf
                0x00000000004055e1                stderr_printf
                0x000000000040560d                perror
                0x0000000000405624                rewind
                0x000000000040565f                snprintf
 .text          0x0000000000405673     0x10ac stdlib.o
                0x0000000000405690                stdlib_system_call
                0x00000000004056b8                rtGetHeapStart
                0x00000000004056c2                rtGetHeapEnd
                0x00000000004056cc                rtGetHeapPointer
                0x00000000004056d6                rtGetAvailableHeap
                0x00000000004056e0                heapSetLibcHeap
                0x0000000000405793                AllocateHeap
                0x00000000004059d5                AllocateHeapEx
                0x00000000004059eb                FreeHeap
                0x00000000004059f5                heapInit
                0x0000000000405b88                stdlibInitMM
                0x0000000000405beb                libcInitRT
                0x0000000000405c0d                rand
                0x0000000000405c2a                srand
                0x0000000000405c38                xmalloc
                0x0000000000405c6a                stdlib_die
                0x0000000000405ca0                malloc
                0x0000000000405cdc                realloc
                0x0000000000405d19                free
                0x0000000000405d1f                calloc
                0x0000000000405d65                zmalloc
                0x0000000000405da1                system
                0x0000000000406165                stdlib_strncmp
                0x00000000004061c8                __findenv
                0x0000000000406293                getenv
                0x00000000004062c0                atoi
                0x0000000000406387                reverse
                0x00000000004063ee                itoa
                0x000000000040649c                abs
                0x00000000004064ac                strtod
                0x00000000004066de                strtof
                0x00000000004066fa                strtold
                0x000000000040670d                atof
 .text          0x000000000040671f      0x772 string.o
                0x000000000040671f                memcmp
                0x0000000000406784                strdup
                0x00000000004067d6                strndup
                0x0000000000406837                strrchr
                0x0000000000406872                strtoimax
                0x000000000040687c                strtoumax
                0x0000000000406886                strcasecmp
                0x00000000004068ee                strncpy
                0x0000000000406944                strcmp
                0x00000000004069a9                strncmp
                0x0000000000406a0c                memset
                0x0000000000406a53                memoryZeroMemory
                0x0000000000406a7a                memcpy
                0x0000000000406ab7                strcpy
                0x0000000000406aeb                strcat
                0x0000000000406b1a                bcopy
                0x0000000000406b46                bzero
                0x0000000000406b66                strlen
                0x0000000000406b94                strnlen
                0x0000000000406bc8                strcspn
                0x0000000000406c67                strspn
                0x0000000000406d06                strtok_r
                0x0000000000406ded                strtok
                0x0000000000406e05                strchr
                0x0000000000406e31                strstr
 .text          0x0000000000406e91       0x89 conio.o
                0x0000000000406e91                putch
                0x0000000000406eb5                cputs
                0x0000000000406eea                getch
                0x0000000000406f02                getche
 .text          0x0000000000406f1a       0x67 unistd.o
                0x0000000000406f1a                unistd_system_call
                0x0000000000406f42                execve
                0x0000000000406f4c                exit
                0x0000000000406f6c                fork
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x0000000000406f81       0x7f 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 unistd.o

.rodata         0x0000000000407000      0xdfe
 .rodata        0x0000000000407000       0xa5 crt0.o
 *fill*         0x00000000004070a5        0x3 
 .rodata        0x00000000004070a8       0x9f main.o
 *fill*         0x0000000000407147        0x1 
 .rodata        0x0000000000407148      0x39d api.o
 *fill*         0x00000000004074e5       0x1b 
 .rodata        0x0000000000407500      0x100 ctype.o
                0x0000000000407500                _ctype
 .rodata        0x0000000000407600      0x2f4 stdio.o
                0x0000000000407760                hex2ascii_data
 *fill*         0x00000000004078f4        0x4 
 .rodata        0x00000000004078f8      0x500 stdlib.o
 .rodata        0x0000000000407df8        0x6 conio.o

.eh_frame       0x0000000000407e00     0x1cf4
 .eh_frame      0x0000000000407e00       0x34 crt0.o
 .eh_frame      0x0000000000407e34       0xfc main.o
                                        0x114 (size before relaxing)
 .eh_frame      0x0000000000407f30      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000408b5c      0x714 stdio.o
                                        0x72c (size before relaxing)
 .eh_frame      0x0000000000409270      0x444 stdlib.o
                                        0x45c (size before relaxing)
 .eh_frame      0x00000000004096b4      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x00000000004099d4       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000409a74       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x0000000000409af4       0x1c
 .note.gnu.property
                0x0000000000409af4       0x1c unistd.o

.rel.dyn        0x0000000000409b10        0x0
 .rel.got       0x0000000000409b10        0x0 unistd.o
 .rel.iplt      0x0000000000409b10        0x0 unistd.o
 .rel.text      0x0000000000409b10        0x0 unistd.o

.data           0x0000000000409b20     0x14e0
                0x0000000000409b20                data = .
                0x0000000000409b20                _data = .
                0x0000000000409b20                __data = .
 *(.data)
 .data          0x0000000000409b20      0x464 crt0.o
 *fill*         0x0000000000409f84       0x1c 
 .data          0x0000000000409fa0      0x450 main.o
 *fill*         0x000000000040a3f0       0x10 
 .data          0x000000000040a400      0x440 api.o
 .data          0x000000000040a840        0x0 ctype.o
 .data          0x000000000040a840        0x0 stdio.o
 .data          0x000000000040a840        0x8 stdlib.o
                0x000000000040a840                _infinity
 .data          0x000000000040a848        0x0 string.o
 .data          0x000000000040a848        0x0 conio.o
 .data          0x000000000040a848        0x0 unistd.o
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a848      0x7b8 

.got            0x000000000040b000        0x0
 .got           0x000000000040b000        0x0 unistd.o

.got.plt        0x000000000040b000        0x0
 .got.plt       0x000000000040b000        0x0 unistd.o

.igot.plt       0x000000000040b000        0x0
 .igot.plt      0x000000000040b000        0x0 unistd.o

.bss            0x000000000040b000    0x12594
                0x000000000040b000                bss = .
                0x000000000040b000                _bss = .
                0x000000000040b000                __bss = .
 *(.bss)
 .bss           0x000000000040b000        0x0 crt0.o
 .bss           0x000000000040b000        0x0 main.o
 .bss           0x000000000040b000     0x8004 api.o
 .bss           0x0000000000413004        0x0 ctype.o
 .bss           0x0000000000413004        0x1 stdio.o
 *fill*         0x0000000000413005       0x1b 
 .bss           0x0000000000413020     0x8020 stdlib.o
                0x0000000000413020                environ
 .bss           0x000000000041b040        0x4 string.o
 .bss           0x000000000041b044        0x0 conio.o
 .bss           0x000000000041b044        0x0 unistd.o
                0x000000000041c000                . = ALIGN (0x1000)
 *fill*         0x000000000041b044      0xfbc 
 COMMON         0x000000000041c000      0xd14 crt0.o
                0x000000000041c000                g_cursor_x
                0x000000000041c004                CurrentWindow
                0x000000000041c008                stdout
                0x000000000041c00c                g_char_attrib
                0x000000000041c010                g_rows
                0x000000000041c020                Streams
                0x000000000041c0a0                g_using_gui
                0x000000000041c0a4                ApplicationInfo
                0x000000000041c0c0                prompt_out
                0x000000000041c4c0                BufferInfo
                0x000000000041c4c4                g_columns
                0x000000000041c4c8                prompt_pos
                0x000000000041c4cc                stdin
                0x000000000041c4d0                prompt_status
                0x000000000041c4e0                prompt_err
                0x000000000041c8e0                CursorInfo
                0x000000000041c8e4                stderr
                0x000000000041c900                prompt
                0x000000000041cd00                rect
                0x000000000041cd04                g_cursor_y
                0x000000000041cd08                ClientAreaInfo
                0x000000000041cd0c                current_semaphore
                0x000000000041cd10                prompt_max
 COMMON         0x000000000041cd14        0xc main.o
                0x000000000041cd14                idleError
                0x000000000041cd18                ServerStatus
                0x000000000041cd1c                idleStatus
 COMMON         0x000000000041cd20      0x438 api.o
                0x000000000041cd20                heapList
                0x000000000041d120                libcHeap
                0x000000000041d124                dialogbox_button2
                0x000000000041d128                messagebox_button1
                0x000000000041d12c                heap_start
                0x000000000041d130                g_available_heap
                0x000000000041d134                g_heap_pointer
                0x000000000041d138                HEAP_SIZE
                0x000000000041d13c                dialogbox_button1
                0x000000000041d140                heap_end
                0x000000000041d144                HEAP_END
                0x000000000041d148                messagebox_button2
                0x000000000041d14c                Heap
                0x000000000041d150                heapCount
                0x000000000041d154                HEAP_START
 *fill*         0x000000000041d158        0x8 
 COMMON         0x000000000041d160      0x434 stdlib.o
                0x000000000041d160                mm_prev_pointer
                0x000000000041d180                mmblockList
                0x000000000041d580                last_valid
                0x000000000041d584                randseed
                0x000000000041d588                mmblockCount
                0x000000000041d58c                last_size
                0x000000000041d590                current_mmblock
                0x000000000041d594                end = .
                0x000000000041d594                _end = .
                0x000000000041d594                __end = .
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
LOAD unistd.o
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
