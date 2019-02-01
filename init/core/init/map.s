
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               crt0.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
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
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
BufferInfo          0x4               crt0.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
mmblockCount        0x4               stdlib.o
dialogbox_button1   0x4               api.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
prompt_status       0x4               crt0.o
prompt_err          0x400             crt0.o
CursorInfo          0x4               crt0.o
heap_end            0x4               stdlib.o
stderr              0x4               crt0.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
idleStatus          0x4               main.o
rect                0x4               crt0.o
g_cursor_y          0x4               crt0.o
ClientAreaInfo      0x4               crt0.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
current_semaphore   0x4               crt0.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               stdlib.o
HEAP_START          0x4               stdlib.o

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
 .text          0x0000000000401058      0x115 main.o
                0x0000000000401068                idleLoop
                0x0000000000401086                initMain
                0x00000000004010a3                driverInitialize
                0x00000000004010c6                driverUninitialize
                0x00000000004010e9                idleServices
                0x000000000040114f                idleInit
 .text          0x000000000040116d     0x1e31 api.o
                0x000000000040116d                system_call
                0x0000000000401195                apiSystem
                0x000000000040159d                system1
                0x00000000004015be                system2
                0x00000000004015df                system3
                0x0000000000401600                system4
                0x0000000000401621                system5
                0x0000000000401642                system6
                0x0000000000401663                system7
                0x0000000000401684                system8
                0x00000000004016a5                system9
                0x00000000004016c6                system10
                0x00000000004016e7                system11
                0x0000000000401708                system12
                0x0000000000401729                system13
                0x000000000040174a                system14
                0x000000000040176b                system15
                0x000000000040178c                refresh_buffer
                0x000000000040186a                print_string
                0x0000000000401870                vsync
                0x000000000040188a                edit_box
                0x00000000004018a6                chama_procedimento
                0x00000000004018c1                SetNextWindowProcedure
                0x00000000004018dc                set_cursor
                0x00000000004018f8                put_char
                0x00000000004018fe                carrega_bitmap_16x16
                0x0000000000401917                apiShutDown
                0x000000000040192e                apiInitBackground
                0x0000000000401934                MessageBox
                0x0000000000401cae                mbProcedure
                0x0000000000401d1c                DialogBox
                0x0000000000402096                dbProcedure
                0x0000000000402104                call_kernel
                0x000000000040227f                call_gui
                0x000000000040230b                APICreateWindow
                0x0000000000402385                APIRegisterWindow
                0x00000000004023b2                APICloseWindow
                0x00000000004023df                APISetFocus
                0x000000000040240c                APIGetFocus
                0x0000000000402421                APIKillFocus
                0x000000000040244e                APISetActiveWindow
                0x000000000040247b                APIGetActiveWindow
                0x0000000000402490                APIShowCurrentProcessInfo
                0x00000000004024a6                APIresize_window
                0x00000000004024c0                APIredraw_window
                0x00000000004024da                APIreplace_window
                0x00000000004024f4                APImaximize_window
                0x0000000000402510                APIminimize_window
                0x000000000040252c                APIupdate_window
                0x0000000000402548                APIget_foregroung_window
                0x000000000040255e                APIset_foregroung_window
                0x000000000040257a                apiExit
                0x0000000000402597                kill
                0x000000000040259d                dead_thread_collector
                0x00000000004025b3                api_strncmp
                0x0000000000402616                refresh_screen
                0x000000000040262c                api_refresh_screen
                0x0000000000402637                apiReboot
                0x000000000040264d                apiSetCursor
                0x0000000000402665                apiGetCursorX
                0x000000000040267d                apiGetCursorY
                0x0000000000402695                apiGetClientAreaRect
                0x00000000004026ad                apiSetClientAreaRect
                0x00000000004026cc                apiCreateProcess
                0x00000000004026e5                apiCreateThread
                0x00000000004026fe                apiStartThread
                0x000000000040271a                apiFOpen
                0x0000000000402746                apiSaveFile
                0x0000000000402799                apiDown
                0x00000000004027ec                apiUp
                0x000000000040283f                enterCriticalSection
                0x000000000040287a                exitCriticalSection
                0x0000000000402893                initializeCriticalSection
                0x00000000004028ac                apiBeginPaint
                0x00000000004028b7                apiEndPaint
                0x00000000004028c2                apiPutChar
                0x00000000004028de                apiDefDialog
                0x00000000004028e8                apiGetSystemMetrics
                0x0000000000402906                api_set_current_keyboard_responder
                0x0000000000402925                api_get_current_keyboard_responder
                0x000000000040293d                api_set_current_mouse_responder
                0x000000000040295c                api_get_current_mouse_responder
                0x0000000000402974                api_set_window_with_text_input
                0x00000000004029b6                api_get_window_with_text_input
                0x00000000004029ce                gramadocore_init_execve
                0x00000000004029d8                fork
                0x00000000004029ed                execve
                0x00000000004029f7                apiDialog
                0x0000000000402a83                api_getchar
                0x0000000000402a9b                apiDisplayBMP
                0x0000000000402ea2                apiSendMessage
                0x0000000000402ed8                apiDrawText
                0x0000000000402f17                apiGetWSScreenWindow
                0x0000000000402f2f                apiGetWSMainWindow
                0x0000000000402f47                apiCreateTimer
                0x0000000000402f64                apiGetSysTimeInfo
                0x0000000000402f82                apiShowWindow
 .text          0x0000000000402f9e        0x0 ctype.o
 .text          0x0000000000402f9e     0x275a stdio.o
                0x0000000000402fc9                stdio_atoi
                0x0000000000403090                stdio_fntos
                0x00000000004031ba                fclose
                0x0000000000403220                fopen
                0x0000000000403352                scroll
                0x0000000000403420                puts
                0x00000000004037fc                printf3
                0x0000000000403819                printf_atoi
                0x0000000000403909                printf_i2hex
                0x000000000040396b                printf2
                0x0000000000403af0                sprintf
                0x0000000000403b45                putchar
                0x0000000000403b66                outbyte
                0x0000000000403d24                _outbyte
                0x0000000000403d53                input
                0x0000000000403ea7                stdio_system_call
                0x0000000000403ecf                getchar
                0x0000000000403ee7                stdioInitialize
                0x00000000004040d4                fflush
                0x0000000000404167                fprintf
                0x00000000004041d8                fputs
                0x0000000000404249                gets
                0x00000000004042d4                ungetc
                0x000000000040430b                ftell
                0x000000000040432c                fileno
                0x0000000000404344                fgetc
                0x00000000004043b2                feof
                0x00000000004043e7                ferror
                0x0000000000404402                fseek
                0x000000000040446e                fputc
                0x00000000004044bd                stdioSetCursor
                0x00000000004044d5                stdioGetCursorX
                0x00000000004044ed                stdioGetCursorY
                0x0000000000404505                scanf
                0x0000000000404745                kvprintf
                0x00000000004055af                printf
                0x00000000004055d9                vfprintf
                0x000000000040564e                stdout_printf
                0x000000000040567a                stderr_printf
                0x00000000004056a6                perror
                0x00000000004056bd                rewind
 .text          0x00000000004056f8      0xc2d stdlib.o
                0x00000000004056f8                stdlib_system_call
                0x0000000000405720                rtGetHeapStart
                0x000000000040572a                rtGetHeapEnd
                0x0000000000405734                rtGetHeapPointer
                0x000000000040573e                rtGetAvailableHeap
                0x0000000000405748                heapSetLibcHeap
                0x00000000004057fb                AllocateHeap
                0x0000000000405a0b                AllocateHeapEx
                0x0000000000405a21                FreeHeap
                0x0000000000405a2b                heapInit
                0x0000000000405bbe                stdlibInitMM
                0x0000000000405c21                libcInitRT
                0x0000000000405c43                rand
                0x0000000000405c60                srand
                0x0000000000405c6e                xmalloc
                0x0000000000405ca0                stdlib_die
                0x0000000000405ce2                malloc
                0x0000000000405d1e                free
                0x0000000000405d24                system
                0x00000000004060e5                stdlib_strncmp
                0x0000000000406149                exit
                0x0000000000406166                __findenv
                0x0000000000406231                getenv
                0x000000000040625e                atoi
 .text          0x0000000000406325      0x446 string.o
                0x0000000000406325                strcmp
                0x000000000040638a                strncmp
                0x00000000004063ed                memoryZeroMemory
                0x0000000000406414                memcpy
                0x0000000000406451                strcpy
                0x0000000000406485                strcat
                0x00000000004064b4                bcopy
                0x00000000004064e0                bzero
                0x0000000000406500                strlen
                0x000000000040652e                strcspn
                0x00000000004065cd                strspn
                0x000000000040666c                strtok_r
                0x0000000000406753                strtok
 .text          0x000000000040676b       0x89 conio.o
                0x000000000040676b                putch
                0x000000000040678f                cputs
                0x00000000004067c4                getch
                0x00000000004067dc                getche
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x00000000004067f4      0x80c 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 conio.o

.rodata         0x0000000000407000      0xe14
 .rodata        0x0000000000407000       0xa5 crt0.o
 *fill*         0x00000000004070a5        0x3 
 .rodata        0x00000000004070a8       0xbb main.o
 *fill*         0x0000000000407163        0x1 
 .rodata        0x0000000000407164      0x39d api.o
 *fill*         0x0000000000407501       0x1f 
 .rodata        0x0000000000407520      0x100 ctype.o
                0x0000000000407520                _ctype
 .rodata        0x0000000000407620      0x374 stdio.o
                0x0000000000407800                hex2ascii_data
 .rodata        0x0000000000407994      0x47a stdlib.o
 .rodata        0x0000000000407e0e        0x6 conio.o

.eh_frame       0x0000000000407e14     0x1934
 .eh_frame      0x0000000000407e14       0x34 crt0.o
 .eh_frame      0x0000000000407e48       0xf8 main.o
                                        0x110 (size before relaxing)
 .eh_frame      0x0000000000407f40      0xc6c api.o
                                        0xc84 (size before relaxing)
 .eh_frame      0x0000000000408bac      0x658 stdio.o
                                        0x670 (size before relaxing)
 .eh_frame      0x0000000000409204      0x304 stdlib.o
                                        0x31c (size before relaxing)
 .eh_frame      0x0000000000409508      0x1a0 string.o
                                        0x1b8 (size before relaxing)
 .eh_frame      0x00000000004096a8       0xa0 conio.o
                                         0xb8 (size before relaxing)

.note.gnu.property
                0x0000000000409748       0x1c
 .note.gnu.property
                0x0000000000409748       0x1c conio.o

.rel.dyn        0x0000000000409764        0x0
 .rel.got       0x0000000000409764        0x0 conio.o
 .rel.iplt      0x0000000000409764        0x0 conio.o
 .rel.text      0x0000000000409764        0x0 conio.o

.data           0x0000000000409780     0x1880
                0x0000000000409780                data = .
                0x0000000000409780                _data = .
                0x0000000000409780                __data = .
 *(.data)
 .data          0x0000000000409780      0x464 crt0.o
 *fill*         0x0000000000409be4       0x1c 
 .data          0x0000000000409c00      0x450 main.o
 *fill*         0x000000000040a050       0x10 
 .data          0x000000000040a060      0x440 api.o
 .data          0x000000000040a4a0        0x0 ctype.o
 .data          0x000000000040a4a0        0x0 stdio.o
 .data          0x000000000040a4a0        0x0 stdlib.o
 .data          0x000000000040a4a0        0x0 string.o
 .data          0x000000000040a4a0        0x0 conio.o
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a4a0      0xb60 

.got            0x000000000040b000        0x0
 .got           0x000000000040b000        0x0 conio.o

.got.plt        0x000000000040b000        0x0
 .got.plt       0x000000000040b000        0x0 conio.o

.igot.plt       0x000000000040b000        0x0
 .igot.plt      0x000000000040b000        0x0 conio.o

.bss            0x000000000040b000     0xa5b8
                0x000000000040b000                bss = .
                0x000000000040b000                _bss = .
                0x000000000040b000                __bss = .
 *(.bss)
 .bss           0x000000000040b000        0x0 crt0.o
 .bss           0x000000000040b000        0x0 main.o
 .bss           0x000000000040b000       0x10 api.o
 .bss           0x000000000040b010        0x0 ctype.o
 .bss           0x000000000040b010        0x1 stdio.o
 *fill*         0x000000000040b011        0xf 
 .bss           0x000000000040b020     0x8020 stdlib.o
                0x000000000040b020                environ
 .bss           0x0000000000413040        0x4 string.o
 .bss           0x0000000000413044        0x0 conio.o
                0x0000000000414000                . = ALIGN (0x1000)
 *fill*         0x0000000000413044      0xfbc 
 COMMON         0x0000000000414000      0xd14 crt0.o
                0x0000000000414000                g_cursor_x
                0x0000000000414004                CurrentWindow
                0x0000000000414008                stdout
                0x000000000041400c                g_char_attrib
                0x0000000000414010                g_rows
                0x0000000000414020                Streams
                0x00000000004140a0                g_using_gui
                0x00000000004140a4                ApplicationInfo
                0x00000000004140c0                prompt_out
                0x00000000004144c0                BufferInfo
                0x00000000004144c4                g_columns
                0x00000000004144c8                prompt_pos
                0x00000000004144cc                stdin
                0x00000000004144d0                prompt_status
                0x00000000004144e0                prompt_err
                0x00000000004148e0                CursorInfo
                0x00000000004148e4                stderr
                0x0000000000414900                prompt
                0x0000000000414d00                rect
                0x0000000000414d04                g_cursor_y
                0x0000000000414d08                ClientAreaInfo
                0x0000000000414d0c                current_semaphore
                0x0000000000414d10                prompt_max
 COMMON         0x0000000000414d14        0xc main.o
                0x0000000000414d14                idleError
                0x0000000000414d18                ServerStatus
                0x0000000000414d1c                idleStatus
 COMMON         0x0000000000414d20       0x10 api.o
                0x0000000000414d20                dialogbox_button2
                0x0000000000414d24                messagebox_button1
                0x0000000000414d28                dialogbox_button1
                0x0000000000414d2c                messagebox_button2
 *fill*         0x0000000000414d30       0x10 
 COMMON         0x0000000000414d40      0x878 stdlib.o
                0x0000000000414d40                mm_prev_pointer
                0x0000000000414d60                mmblockList
                0x0000000000415160                last_valid
                0x0000000000415180                heapList
                0x0000000000415580                libcHeap
                0x0000000000415584                randseed
                0x0000000000415588                heap_start
                0x000000000041558c                g_available_heap
                0x0000000000415590                g_heap_pointer
                0x0000000000415594                HEAP_SIZE
                0x0000000000415598                mmblockCount
                0x000000000041559c                last_size
                0x00000000004155a0                heap_end
                0x00000000004155a4                HEAP_END
                0x00000000004155a8                Heap
                0x00000000004155ac                current_mmblock
                0x00000000004155b0                heapCount
                0x00000000004155b4                HEAP_START
                0x00000000004155b8                end = .
                0x00000000004155b8                _end = .
                0x00000000004155b8                __end = .
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
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
