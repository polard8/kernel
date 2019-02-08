
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
 .text          0x0000000000401058      0x115 main.o
                0x0000000000401068                idleLoop
                0x0000000000401086                initMain
                0x00000000004010a3                driverInitialize
                0x00000000004010c6                driverUninitialize
                0x00000000004010e9                idleServices
                0x000000000040114f                idleInit
 .text          0x000000000040116d     0x1fee api.o
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
                0x0000000000401e8a                mbProcedure
                0x0000000000401ef8                DialogBox
                0x0000000000402272                dbProcedure
                0x00000000004022e0                call_kernel
                0x000000000040245b                call_gui
                0x00000000004024e7                APICreateWindow
                0x0000000000402561                APIRegisterWindow
                0x000000000040258e                APICloseWindow
                0x00000000004025bb                APISetFocus
                0x00000000004025e8                APIGetFocus
                0x00000000004025fd                APIKillFocus
                0x000000000040262a                APISetActiveWindow
                0x0000000000402657                APIGetActiveWindow
                0x000000000040266c                APIShowCurrentProcessInfo
                0x0000000000402682                APIresize_window
                0x000000000040269c                APIredraw_window
                0x00000000004026b6                APIreplace_window
                0x00000000004026d0                APImaximize_window
                0x00000000004026ec                APIminimize_window
                0x0000000000402708                APIupdate_window
                0x0000000000402724                APIget_foregroung_window
                0x000000000040273a                APIset_foregroung_window
                0x0000000000402756                apiExit
                0x0000000000402773                kill
                0x0000000000402779                dead_thread_collector
                0x000000000040278f                api_strncmp
                0x00000000004027f2                refresh_screen
                0x0000000000402808                api_refresh_screen
                0x0000000000402813                apiReboot
                0x0000000000402829                apiSetCursor
                0x0000000000402841                apiGetCursorX
                0x0000000000402859                apiGetCursorY
                0x0000000000402871                apiGetClientAreaRect
                0x0000000000402889                apiSetClientAreaRect
                0x00000000004028a8                apiCreateProcess
                0x00000000004028c1                apiCreateThread
                0x00000000004028da                apiStartThread
                0x00000000004028f6                apiFOpen
                0x0000000000402922                apiSaveFile
                0x0000000000402975                apiDown
                0x00000000004029c8                apiUp
                0x0000000000402a1b                enterCriticalSection
                0x0000000000402a56                exitCriticalSection
                0x0000000000402a6f                initializeCriticalSection
                0x0000000000402a88                apiBeginPaint
                0x0000000000402a93                apiEndPaint
                0x0000000000402a9e                apiPutChar
                0x0000000000402aba                apiDefDialog
                0x0000000000402ac4                apiGetSystemMetrics
                0x0000000000402ae2                api_set_current_keyboard_responder
                0x0000000000402b01                api_get_current_keyboard_responder
                0x0000000000402b19                api_set_current_mouse_responder
                0x0000000000402b38                api_get_current_mouse_responder
                0x0000000000402b50                api_set_window_with_text_input
                0x0000000000402b92                api_get_window_with_text_input
                0x0000000000402baa                gramadocore_init_execve
                0x0000000000402bb4                apiDialog
                0x0000000000402c40                api_getchar
                0x0000000000402c58                apiDisplayBMP
                0x000000000040305f                apiSendMessage
                0x0000000000403095                apiDrawText
                0x00000000004030d4                apiGetWSScreenWindow
                0x00000000004030ec                apiGetWSMainWindow
                0x0000000000403104                apiCreateTimer
                0x0000000000403121                apiGetSysTimeInfo
                0x000000000040313f                apiShowWindow
 .text          0x000000000040315b        0x0 ctype.o
 .text          0x000000000040315b     0x2782 stdio.o
                0x0000000000403186                stdio_atoi
                0x000000000040324d                stdio_fntos
                0x0000000000403377                fclose
                0x00000000004033dd                fopen
                0x000000000040350f                scroll
                0x00000000004035dd                puts
                0x00000000004035f8                fread
                0x0000000000403602                fwrite
                0x00000000004039cd                printf3
                0x00000000004039ea                printf_atoi
                0x0000000000403ada                printf_i2hex
                0x0000000000403b3c                printf2
                0x0000000000403cc1                sprintf
                0x0000000000403d16                putchar
                0x0000000000403d37                outbyte
                0x0000000000403ef5                _outbyte
                0x0000000000403f24                input
                0x0000000000404078                stdio_system_call
                0x00000000004040a0                getchar
                0x00000000004040b8                stdioInitialize
                0x00000000004042a5                fflush
                0x0000000000404338                fprintf
                0x00000000004043a9                fputs
                0x000000000040441a                gets
                0x00000000004044a5                ungetc
                0x00000000004044dc                ftell
                0x00000000004044fd                fileno
                0x0000000000404515                fgetc
                0x0000000000404583                feof
                0x00000000004045b8                ferror
                0x00000000004045d3                fseek
                0x000000000040463f                fputc
                0x000000000040468e                stdioSetCursor
                0x00000000004046a6                stdioGetCursorX
                0x00000000004046be                stdioGetCursorY
                0x00000000004046d6                scanf
                0x0000000000404916                kvprintf
                0x0000000000405780                printf
                0x00000000004057aa                vfprintf
                0x000000000040581f                stdout_printf
                0x000000000040584b                stderr_printf
                0x0000000000405877                perror
                0x000000000040588e                rewind
                0x00000000004058c9                snprintf
 .text          0x00000000004058dd      0xda7 stdlib.o
                0x00000000004058dd                stdlib_system_call
                0x0000000000405905                rtGetHeapStart
                0x000000000040590f                rtGetHeapEnd
                0x0000000000405919                rtGetHeapPointer
                0x0000000000405923                rtGetAvailableHeap
                0x000000000040592d                heapSetLibcHeap
                0x00000000004059e0                AllocateHeap
                0x0000000000405c22                AllocateHeapEx
                0x0000000000405c38                FreeHeap
                0x0000000000405c42                heapInit
                0x0000000000405dd5                stdlibInitMM
                0x0000000000405e38                libcInitRT
                0x0000000000405e5a                rand
                0x0000000000405e77                srand
                0x0000000000405e85                xmalloc
                0x0000000000405eb7                stdlib_die
                0x0000000000405eed                malloc
                0x0000000000405f29                realloc
                0x0000000000405f33                free
                0x0000000000405f39                calloc
                0x0000000000405f78                system
                0x000000000040633c                stdlib_strncmp
                0x00000000004063a0                __findenv
                0x000000000040646b                getenv
                0x0000000000406498                atoi
                0x000000000040655f                reverse
                0x00000000004065c6                itoa
                0x0000000000406674                abs
 .text          0x0000000000406684      0x5f3 string.o
                0x0000000000406684                strtold
                0x000000000040668b                strdup
                0x00000000004066dd                strrchr
                0x0000000000406718                strtoimax
                0x0000000000406722                strtoumax
                0x000000000040672c                strcasecmp
                0x0000000000406794                strncpy
                0x00000000004067ea                strcmp
                0x000000000040684f                strncmp
                0x00000000004068b2                memset
                0x00000000004068f9                memoryZeroMemory
                0x0000000000406920                memcpy
                0x000000000040695d                strcpy
                0x0000000000406991                strcat
                0x00000000004069c0                bcopy
                0x00000000004069ec                bzero
                0x0000000000406a0c                strlen
                0x0000000000406a3a                strcspn
                0x0000000000406ad9                strspn
                0x0000000000406b78                strtok_r
                0x0000000000406c5f                strtok
 .text          0x0000000000406c77       0x89 conio.o
                0x0000000000406c77                putch
                0x0000000000406c9b                cputs
                0x0000000000406cd0                getch
                0x0000000000406ce8                getche
 .text          0x0000000000406d00       0x67 unistd.o
                0x0000000000406d00                unistd_system_call
                0x0000000000406d28                execve
                0x0000000000406d32                exit
                0x0000000000406d52                fork
                0x0000000000407000                . = ALIGN (0x1000)
 *fill*         0x0000000000406d67      0x299 

.iplt           0x0000000000407000        0x0
 .iplt          0x0000000000407000        0x0 unistd.o

.rodata         0x0000000000407000      0xe8d
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
 .rodata        0x0000000000407994      0x4f3 stdlib.o
 .rodata        0x0000000000407e87        0x6 conio.o

.eh_frame       0x0000000000407e90     0x1b54
 .eh_frame      0x0000000000407e90       0x34 crt0.o
 .eh_frame      0x0000000000407ec4       0xf8 main.o
                                        0x110 (size before relaxing)
 .eh_frame      0x0000000000407fbc      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x0000000000408be8      0x6b8 stdio.o
                                        0x6d0 (size before relaxing)
 .eh_frame      0x00000000004092a0      0x384 stdlib.o
                                        0x39c (size before relaxing)
 .eh_frame      0x0000000000409624      0x2a0 string.o
                                        0x2b8 (size before relaxing)
 .eh_frame      0x00000000004098c4       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x0000000000409964       0x80 unistd.o
                                         0x98 (size before relaxing)

.note.gnu.property
                0x00000000004099e4       0x1c
 .note.gnu.property
                0x00000000004099e4       0x1c unistd.o

.rel.dyn        0x0000000000409a00        0x0
 .rel.got       0x0000000000409a00        0x0 unistd.o
 .rel.iplt      0x0000000000409a00        0x0 unistd.o
 .rel.text      0x0000000000409a00        0x0 unistd.o

.data           0x0000000000409a00     0x1600
                0x0000000000409a00                data = .
                0x0000000000409a00                _data = .
                0x0000000000409a00                __data = .
 *(.data)
 .data          0x0000000000409a00      0x464 crt0.o
 *fill*         0x0000000000409e64       0x1c 
 .data          0x0000000000409e80      0x450 main.o
 *fill*         0x000000000040a2d0       0x10 
 .data          0x000000000040a2e0      0x440 api.o
 .data          0x000000000040a720        0x0 ctype.o
 .data          0x000000000040a720        0x0 stdio.o
 .data          0x000000000040a720        0x0 stdlib.o
 .data          0x000000000040a720        0x0 string.o
 .data          0x000000000040a720        0x0 conio.o
 .data          0x000000000040a720        0x0 unistd.o
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040a720      0x8e0 

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
