
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
 .text          0x000000000040115a     0x2017 api.o
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
                0x0000000000401855                print_string
                0x000000000040185b                vsync
                0x0000000000401875                edit_box
                0x0000000000401891                chama_procedimento
                0x000000000040189b                SetNextWindowProcedure
                0x00000000004018a5                set_cursor
                0x00000000004018bc                put_char
                0x00000000004018c2                carrega_bitmap_16x16
                0x00000000004018db                apiShutDown
                0x00000000004018f2                apiInitBackground
                0x00000000004018f8                MessageBox
                0x0000000000401e84                mbProcedure
                0x0000000000401ef2                DialogBox
                0x00000000004022a2                dbProcedure
                0x0000000000402310                call_kernel
                0x000000000040248b                call_gui
                0x0000000000402517                APICreateWindow
                0x0000000000402590                APIRegisterWindow
                0x00000000004025b8                APICloseWindow
                0x00000000004025e0                APISetFocus
                0x0000000000402608                APIGetFocus
                0x000000000040261d                APIKillFocus
                0x0000000000402645                APISetActiveWindow
                0x000000000040266d                APIGetActiveWindow
                0x0000000000402682                APIShowCurrentProcessInfo
                0x0000000000402698                APIresize_window
                0x00000000004026b2                APIredraw_window
                0x00000000004026cc                APIreplace_window
                0x00000000004026e6                APImaximize_window
                0x0000000000402702                APIminimize_window
                0x000000000040271e                APIupdate_window
                0x000000000040273a                APIget_foregroung_window
                0x0000000000402750                APIset_foregroung_window
                0x000000000040276c                apiExit
                0x0000000000402789                kill
                0x000000000040278f                dead_thread_collector
                0x00000000004027a5                api_strncmp
                0x0000000000402808                refresh_screen
                0x000000000040281e                api_refresh_screen
                0x0000000000402829                apiReboot
                0x000000000040283f                apiSetCursor
                0x0000000000402857                apiGetCursorX
                0x000000000040286f                apiGetCursorY
                0x0000000000402887                apiGetClientAreaRect
                0x000000000040289f                apiSetClientAreaRect
                0x00000000004028be                apiCreateProcess
                0x00000000004028d7                apiCreateThread
                0x00000000004028f0                apiStartThread
                0x000000000040290c                apiFOpen
                0x0000000000402938                apiSaveFile
                0x000000000040298b                apiDown
                0x00000000004029de                apiUp
                0x0000000000402a31                enterCriticalSection
                0x0000000000402a6c                exitCriticalSection
                0x0000000000402a85                initializeCriticalSection
                0x0000000000402a9e                apiBeginPaint
                0x0000000000402aa9                apiEndPaint
                0x0000000000402ab4                apiPutChar
                0x0000000000402ad0                apiDefDialog
                0x0000000000402ada                apiGetSystemMetrics
                0x0000000000402af8                api_set_current_keyboard_responder
                0x0000000000402b17                api_get_current_keyboard_responder
                0x0000000000402b2f                api_set_current_mouse_responder
                0x0000000000402b4e                api_get_current_mouse_responder
                0x0000000000402b66                api_set_window_with_text_input
                0x0000000000402ba8                api_get_window_with_text_input
                0x0000000000402bc0                gramadocore_init_execve
                0x0000000000402bca                apiDialog
                0x0000000000402c56                api_getchar
                0x0000000000402c6e                apiDisplayBMP
                0x0000000000403075                apiSendMessage
                0x00000000004030ab                apiDrawText
                0x00000000004030ea                apiGetWSScreenWindow
                0x0000000000403102                apiGetWSMainWindow
                0x000000000040311a                apiCreateTimer
                0x0000000000403137                apiGetSysTimeInfo
                0x0000000000403155                apiShowWindow
 .text          0x0000000000403171        0x0 ctype.o
 .text          0x0000000000403171     0x2782 stdio.o
                0x000000000040319c                stdio_atoi
                0x0000000000403263                stdio_fntos
                0x000000000040338d                fclose
                0x00000000004033f3                fopen
                0x0000000000403525                scroll
                0x00000000004035f3                puts
                0x000000000040360e                fread
                0x0000000000403618                fwrite
                0x00000000004039e3                printf3
                0x0000000000403a00                printf_atoi
                0x0000000000403af0                printf_i2hex
                0x0000000000403b52                printf2
                0x0000000000403cd7                sprintf
                0x0000000000403d2c                putchar
                0x0000000000403d4d                outbyte
                0x0000000000403f0b                _outbyte
                0x0000000000403f3a                input
                0x000000000040408e                stdio_system_call
                0x00000000004040b6                getchar
                0x00000000004040ce                stdioInitialize
                0x00000000004042bb                fflush
                0x000000000040434e                fprintf
                0x00000000004043bf                fputs
                0x0000000000404430                gets
                0x00000000004044bb                ungetc
                0x00000000004044f2                ftell
                0x0000000000404513                fileno
                0x000000000040452b                fgetc
                0x0000000000404599                feof
                0x00000000004045ce                ferror
                0x00000000004045e9                fseek
                0x0000000000404655                fputc
                0x00000000004046a4                stdioSetCursor
                0x00000000004046bc                stdioGetCursorX
                0x00000000004046d4                stdioGetCursorY
                0x00000000004046ec                scanf
                0x000000000040492c                kvprintf
                0x0000000000405796                printf
                0x00000000004057c0                vfprintf
                0x0000000000405835                stdout_printf
                0x0000000000405861                stderr_printf
                0x000000000040588d                perror
                0x00000000004058a4                rewind
                0x00000000004058df                snprintf
 .text          0x00000000004058f3      0xda7 stdlib.o
                0x00000000004058f3                stdlib_system_call
                0x000000000040591b                rtGetHeapStart
                0x0000000000405925                rtGetHeapEnd
                0x000000000040592f                rtGetHeapPointer
                0x0000000000405939                rtGetAvailableHeap
                0x0000000000405943                heapSetLibcHeap
                0x00000000004059f6                AllocateHeap
                0x0000000000405c38                AllocateHeapEx
                0x0000000000405c4e                FreeHeap
                0x0000000000405c58                heapInit
                0x0000000000405deb                stdlibInitMM
                0x0000000000405e4e                libcInitRT
                0x0000000000405e70                rand
                0x0000000000405e8d                srand
                0x0000000000405e9b                xmalloc
                0x0000000000405ecd                stdlib_die
                0x0000000000405f03                malloc
                0x0000000000405f3f                realloc
                0x0000000000405f49                free
                0x0000000000405f4f                calloc
                0x0000000000405f8e                system
                0x0000000000406352                stdlib_strncmp
                0x00000000004063b6                __findenv
                0x0000000000406481                getenv
                0x00000000004064ae                atoi
                0x0000000000406575                reverse
                0x00000000004065dc                itoa
                0x000000000040668a                abs
 .text          0x000000000040669a      0x658 string.o
                0x000000000040669a                memcmp
                0x00000000004066ff                strtold
                0x0000000000406706                strdup
                0x0000000000406758                strrchr
                0x0000000000406793                strtoimax
                0x000000000040679d                strtoumax
                0x00000000004067a7                strcasecmp
                0x000000000040680f                strncpy
                0x0000000000406865                strcmp
                0x00000000004068ca                strncmp
                0x000000000040692d                memset
                0x0000000000406974                memoryZeroMemory
                0x000000000040699b                memcpy
                0x00000000004069d8                strcpy
                0x0000000000406a0c                strcat
                0x0000000000406a3b                bcopy
                0x0000000000406a67                bzero
                0x0000000000406a87                strlen
                0x0000000000406ab5                strcspn
                0x0000000000406b54                strspn
                0x0000000000406bf3                strtok_r
                0x0000000000406cda                strtok
 .text          0x0000000000406cf2       0x89 conio.o
                0x0000000000406cf2                putch
                0x0000000000406d16                cputs
                0x0000000000406d4b                getch
                0x0000000000406d63                getche
 .text          0x0000000000406d7b       0x67 unistd.o
                0x0000000000406d7b                unistd_system_call
                0x0000000000406da3                execve
                0x0000000000406dad                exit
                0x0000000000406dcd                fork
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x0000000000406de2      0x21e 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 unistd.o

.rodata         0x0000000000407000      0xe6d
 .rodata        0x0000000000407000       0xa5 crt0.o
 *fill*         0x00000000004070a5        0x3 
 .rodata        0x00000000004070a8       0x9f main.o
 *fill*         0x0000000000407147        0x1 
 .rodata        0x0000000000407148      0x3ab api.o
 *fill*         0x00000000004074f3        0xd 
 .rodata        0x0000000000407500      0x100 ctype.o
                0x0000000000407500                _ctype
 .rodata        0x0000000000407600      0x374 stdio.o
                0x00000000004077e0                hex2ascii_data
 .rodata        0x0000000000407974      0x4f3 stdlib.o
 .rodata        0x0000000000407e67        0x6 conio.o

.eh_frame       0x0000000000407e70     0x1b78
 .eh_frame      0x0000000000407e70       0x34 crt0.o
 .eh_frame      0x0000000000407ea4       0xfc main.o
                                        0x114 (size before relaxing)
 .eh_frame      0x0000000000407fa0      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000408bcc      0x6b8 stdio.o
                                        0x6d0 (size before relaxing)
 .eh_frame      0x0000000000409284      0x384 stdlib.o
                                        0x39c (size before relaxing)
 .eh_frame      0x0000000000409608      0x2c0 string.o
                                        0x2d8 (size before relaxing)
 .eh_frame      0x00000000004098c8       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000409968       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x00000000004099e8       0x1c
 .note.gnu.property
                0x00000000004099e8       0x1c unistd.o

.rel.dyn        0x0000000000409a04        0x0
 .rel.got       0x0000000000409a04        0x0 unistd.o
 .rel.iplt      0x0000000000409a04        0x0 unistd.o
 .rel.text      0x0000000000409a04        0x0 unistd.o

.data           0x0000000000409a20     0x15e0
                0x0000000000409a20                data = .
                0x0000000000409a20                _data = .
                0x0000000000409a20                __data = .
 *(.data)
 .data          0x0000000000409a20      0x464 crt0.o
 *fill*         0x0000000000409e84       0x1c 
 .data          0x0000000000409ea0      0x450 main.o
 *fill*         0x000000000040a2f0       0x10 
 .data          0x000000000040a300      0x440 api.o
 .data          0x000000000040a740        0x0 ctype.o
 .data          0x000000000040a740        0x0 stdio.o
 .data          0x000000000040a740        0x0 stdlib.o
 .data          0x000000000040a740        0x0 string.o
 .data          0x000000000040a740        0x0 conio.o
 .data          0x000000000040a740        0x0 unistd.o
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a740      0x8c0 

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
