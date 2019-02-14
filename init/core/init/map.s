
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
 .text          0x0000000000403148     0x2763 stdio.o
                0x0000000000403190                stdio_atoi
                0x0000000000403257                stdio_fntos
                0x0000000000403381                fclose
                0x00000000004033e7                fopen
                0x000000000040348e                scroll
                0x000000000040355c                puts
                0x0000000000403577                fread
                0x0000000000403581                fwrite
                0x000000000040394c                printf3
                0x0000000000403969                printf_atoi
                0x0000000000403a59                printf_i2hex
                0x0000000000403abb                printf2
                0x0000000000403c40                sprintf
                0x0000000000403c95                putchar
                0x0000000000403cb6                outbyte
                0x0000000000403e74                _outbyte
                0x0000000000403ea3                input
                0x0000000000403ff7                stdio_system_call
                0x000000000040401f                getchar
                0x0000000000404037                stdioInitialize
                0x0000000000404224                fflush
                0x00000000004042b7                fprintf
                0x0000000000404328                fputs
                0x0000000000404399                gets
                0x0000000000404424                ungetc
                0x000000000040445b                ftell
                0x000000000040447c                fileno
                0x0000000000404494                fgetc
                0x00000000004044b2                feof
                0x00000000004044d0                ferror
                0x00000000004044ee                fseek
                0x000000000040450c                fputc
                0x000000000040452a                stdioSetCursor
                0x0000000000404542                stdioGetCursorX
                0x000000000040455a                stdioGetCursorY
                0x0000000000404572                scanf
                0x000000000040470c                fscanf
                0x0000000000404729                sscanf
                0x00000000004048e4                kvprintf
                0x000000000040574e                printf
                0x0000000000405778                vfprintf
                0x00000000004057ed                stdout_printf
                0x0000000000405819                stderr_printf
                0x0000000000405845                perror
                0x000000000040585c                rewind
                0x0000000000405897                snprintf
 .text          0x00000000004058ab     0x10ac stdlib.o
                0x00000000004058c8                stdlib_system_call
                0x00000000004058f0                rtGetHeapStart
                0x00000000004058fa                rtGetHeapEnd
                0x0000000000405904                rtGetHeapPointer
                0x000000000040590e                rtGetAvailableHeap
                0x0000000000405918                heapSetLibcHeap
                0x00000000004059cb                AllocateHeap
                0x0000000000405c0d                AllocateHeapEx
                0x0000000000405c23                FreeHeap
                0x0000000000405c2d                heapInit
                0x0000000000405dc0                stdlibInitMM
                0x0000000000405e23                libcInitRT
                0x0000000000405e45                rand
                0x0000000000405e62                srand
                0x0000000000405e70                xmalloc
                0x0000000000405ea2                stdlib_die
                0x0000000000405ed8                malloc
                0x0000000000405f14                realloc
                0x0000000000405f51                free
                0x0000000000405f57                calloc
                0x0000000000405f9d                zmalloc
                0x0000000000405fd9                system
                0x000000000040639d                stdlib_strncmp
                0x0000000000406400                __findenv
                0x00000000004064cb                getenv
                0x00000000004064f8                atoi
                0x00000000004065bf                reverse
                0x0000000000406626                itoa
                0x00000000004066d4                abs
                0x00000000004066e4                strtod
                0x0000000000406916                strtof
                0x0000000000406932                strtold
                0x0000000000406945                atof
 .text          0x0000000000406957      0x772 string.o
                0x0000000000406957                memcmp
                0x00000000004069bc                strdup
                0x0000000000406a0e                strndup
                0x0000000000406a6f                strrchr
                0x0000000000406aaa                strtoimax
                0x0000000000406ab4                strtoumax
                0x0000000000406abe                strcasecmp
                0x0000000000406b26                strncpy
                0x0000000000406b7c                strcmp
                0x0000000000406be1                strncmp
                0x0000000000406c44                memset
                0x0000000000406c8b                memoryZeroMemory
                0x0000000000406cb2                memcpy
                0x0000000000406cef                strcpy
                0x0000000000406d23                strcat
                0x0000000000406d52                bcopy
                0x0000000000406d7e                bzero
                0x0000000000406d9e                strlen
                0x0000000000406dcc                strnlen
                0x0000000000406e00                strcspn
                0x0000000000406e9f                strspn
                0x0000000000406f3e                strtok_r
                0x0000000000407025                strtok
                0x000000000040703d                strchr
                0x0000000000407069                strstr
 .text          0x00000000004070c9       0x89 conio.o
                0x00000000004070c9                putch
                0x00000000004070ed                cputs
                0x0000000000407122                getch
                0x000000000040713a                getche
 .text          0x0000000000407152       0x67 unistd.o
                0x0000000000407152                unistd_system_call
                0x000000000040717a                execve
                0x0000000000407184                exit
                0x00000000004071a4                fork
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004071b9      0xe47 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 unistd.o

.rodata         0x0000000000408000      0xe3e
 .rodata        0x0000000000408000       0xa5 crt0.o
 *fill*         0x00000000004080a5        0x3 
 .rodata        0x00000000004080a8       0x9f main.o
 *fill*         0x0000000000408147        0x1 
 .rodata        0x0000000000408148      0x39d api.o
 *fill*         0x00000000004084e5       0x1b 
 .rodata        0x0000000000408500      0x100 ctype.o
                0x0000000000408500                _ctype
 .rodata        0x0000000000408600      0x334 stdio.o
                0x00000000004087a0                hex2ascii_data
 *fill*         0x0000000000408934        0x4 
 .rodata        0x0000000000408938      0x500 stdlib.o
 .rodata        0x0000000000408e38        0x6 conio.o

.eh_frame       0x0000000000408e40     0x1cf8
 .eh_frame      0x0000000000408e40       0x34 crt0.o
 .eh_frame      0x0000000000408e74       0xfc main.o
                                        0x114 (size before relaxing)
 .eh_frame      0x0000000000408f70      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000409b9c      0x718 stdio.o
                                        0x730 (size before relaxing)
 .eh_frame      0x000000000040a2b4      0x444 stdlib.o
                                        0x45c (size before relaxing)
 .eh_frame      0x000000000040a6f8      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x000000000040aa18       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x000000000040aab8       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x000000000040ab38       0x1c
 .note.gnu.property
                0x000000000040ab38       0x1c unistd.o

.rel.dyn        0x000000000040ab54        0x0
 .rel.got       0x000000000040ab54        0x0 unistd.o
 .rel.iplt      0x000000000040ab54        0x0 unistd.o
 .rel.text      0x000000000040ab54        0x0 unistd.o

.data           0x000000000040ab60     0x14a0
                0x000000000040ab60                data = .
                0x000000000040ab60                _data = .
                0x000000000040ab60                __data = .
 *(.data)
 .data          0x000000000040ab60      0x464 crt0.o
 *fill*         0x000000000040afc4       0x1c 
 .data          0x000000000040afe0      0x450 main.o
 *fill*         0x000000000040b430       0x10 
 .data          0x000000000040b440      0x440 api.o
 .data          0x000000000040b880        0x0 ctype.o
 .data          0x000000000040b880        0x0 stdio.o
 .data          0x000000000040b880        0x8 stdlib.o
                0x000000000040b880                _infinity
 .data          0x000000000040b888        0x0 string.o
 .data          0x000000000040b888        0x0 conio.o
 .data          0x000000000040b888        0x0 unistd.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040b888      0x778 

.got            0x000000000040c000        0x0
 .got           0x000000000040c000        0x0 unistd.o

.got.plt        0x000000000040c000        0x0
 .got.plt       0x000000000040c000        0x0 unistd.o

.igot.plt       0x000000000040c000        0x0
 .igot.plt      0x000000000040c000        0x0 unistd.o

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
