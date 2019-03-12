
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
taskmanagerBuffer   0x200             main.o
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
taskmanagerStatus   0x4               main.o
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
rect                0x4               crt0.o
g_cursor_y          0x4               crt0.o
taskmanagerBufferPos
                    0x4               main.o
ClientAreaInfo      0x4               crt0.o
messagebox_button2  0x4               api.o
Heap                0x4               api.o
current_semaphore   0x4               crt0.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
taskmanTest1        0x4               crt0.o
heapCount           0x4               api.o
HEAP_START          0x4               api.o
taskmanagerError    0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x00000000004a1000     0x7000
                0x00000000004a1000                code = .
                0x00000000004a1000                _code = .
                0x00000000004a1000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00000000004a1000       0x34 crt0.o
                0x00000000004a1000                crt0
 .text          0x00000000004a1034      0x53f main.o
                0x00000000004a1044                tmSleep
                0x00000000004a1060                tmProbeProcessList
                0x00000000004a107e                tmCreateTaskBar
                0x00000000004a10e9                tmProc
                0x00000000004a116e                tmUpdateStatus
                0x00000000004a11ab                tmDrawBar
                0x00000000004a1200                tmSetCursor
                0x00000000004a1216                tmstrlen
                0x00000000004a1244                DoProgress
                0x00000000004a12eb                DoSome
                0x00000000004a1343                progress_bar_test
                0x00000000004a1351                tmInit
                0x00000000004a1379                appMain
 .text          0x00000000004a1573     0x2017 api.o
                0x00000000004a1573                system_call
                0x00000000004a159b                apiSystem
                0x00000000004a19a3                system1
                0x00000000004a19c4                system2
                0x00000000004a19e5                system3
                0x00000000004a1a06                system4
                0x00000000004a1a27                system5
                0x00000000004a1a48                system6
                0x00000000004a1a69                system7
                0x00000000004a1a8a                system8
                0x00000000004a1aab                system9
                0x00000000004a1acc                system10
                0x00000000004a1aed                system11
                0x00000000004a1b0e                system12
                0x00000000004a1b2f                system13
                0x00000000004a1b50                system14
                0x00000000004a1b71                system15
                0x00000000004a1b92                refresh_buffer
                0x00000000004a1c6e                print_string
                0x00000000004a1c74                vsync
                0x00000000004a1c8e                edit_box
                0x00000000004a1caa                chama_procedimento
                0x00000000004a1cb4                SetNextWindowProcedure
                0x00000000004a1cbe                set_cursor
                0x00000000004a1cd5                put_char
                0x00000000004a1cdb                carrega_bitmap_16x16
                0x00000000004a1cf4                apiShutDown
                0x00000000004a1d0b                apiInitBackground
                0x00000000004a1d11                MessageBox
                0x00000000004a229d                mbProcedure
                0x00000000004a230b                DialogBox
                0x00000000004a26bb                dbProcedure
                0x00000000004a2729                call_kernel
                0x00000000004a28a4                call_gui
                0x00000000004a2930                APICreateWindow
                0x00000000004a29a9                APIRegisterWindow
                0x00000000004a29d1                APICloseWindow
                0x00000000004a29f9                APISetFocus
                0x00000000004a2a21                APIGetFocus
                0x00000000004a2a36                APIKillFocus
                0x00000000004a2a5e                APISetActiveWindow
                0x00000000004a2a86                APIGetActiveWindow
                0x00000000004a2a9b                APIShowCurrentProcessInfo
                0x00000000004a2ab1                APIresize_window
                0x00000000004a2acb                APIredraw_window
                0x00000000004a2ae5                APIreplace_window
                0x00000000004a2aff                APImaximize_window
                0x00000000004a2b1b                APIminimize_window
                0x00000000004a2b37                APIupdate_window
                0x00000000004a2b53                APIget_foregroung_window
                0x00000000004a2b69                APIset_foregroung_window
                0x00000000004a2b85                apiExit
                0x00000000004a2ba2                kill
                0x00000000004a2ba8                dead_thread_collector
                0x00000000004a2bbe                api_strncmp
                0x00000000004a2c21                refresh_screen
                0x00000000004a2c37                api_refresh_screen
                0x00000000004a2c42                apiReboot
                0x00000000004a2c58                apiSetCursor
                0x00000000004a2c70                apiGetCursorX
                0x00000000004a2c88                apiGetCursorY
                0x00000000004a2ca0                apiGetClientAreaRect
                0x00000000004a2cb8                apiSetClientAreaRect
                0x00000000004a2cd7                apiCreateProcess
                0x00000000004a2cf0                apiCreateThread
                0x00000000004a2d09                apiStartThread
                0x00000000004a2d25                apiFOpen
                0x00000000004a2d51                apiSaveFile
                0x00000000004a2da4                apiDown
                0x00000000004a2df7                apiUp
                0x00000000004a2e4a                enterCriticalSection
                0x00000000004a2e85                exitCriticalSection
                0x00000000004a2e9e                initializeCriticalSection
                0x00000000004a2eb7                apiBeginPaint
                0x00000000004a2ec2                apiEndPaint
                0x00000000004a2ecd                apiPutChar
                0x00000000004a2ee9                apiDefDialog
                0x00000000004a2ef3                apiGetSystemMetrics
                0x00000000004a2f11                api_set_current_keyboard_responder
                0x00000000004a2f30                api_get_current_keyboard_responder
                0x00000000004a2f48                api_set_current_mouse_responder
                0x00000000004a2f67                api_get_current_mouse_responder
                0x00000000004a2f7f                api_set_window_with_text_input
                0x00000000004a2fc1                api_get_window_with_text_input
                0x00000000004a2fd9                gramadocore_init_execve
                0x00000000004a2fe3                apiDialog
                0x00000000004a306f                api_getchar
                0x00000000004a3087                apiDisplayBMP
                0x00000000004a348e                apiSendMessage
                0x00000000004a34c4                apiDrawText
                0x00000000004a3503                apiGetWSScreenWindow
                0x00000000004a351b                apiGetWSMainWindow
                0x00000000004a3533                apiCreateTimer
                0x00000000004a3550                apiGetSysTimeInfo
                0x00000000004a356e                apiShowWindow
 .text          0x00000000004a358a        0x0 ctype.o
 .text          0x00000000004a358a     0x2546 stdio.o
                0x00000000004a35d2                stdio_atoi
                0x00000000004a3699                stdio_fntos
                0x00000000004a37c3                fclose
                0x00000000004a37e4                fopen
                0x00000000004a3805                scroll
                0x00000000004a38d3                puts
                0x00000000004a38ee                fread
                0x00000000004a38f8                fwrite
                0x00000000004a3cc3                printf3
                0x00000000004a3ce0                printf_atoi
                0x00000000004a3dd0                printf_i2hex
                0x00000000004a3e32                printf2
                0x00000000004a3fb7                sprintf
                0x00000000004a400c                putchar
                0x00000000004a402d                outbyte
                0x00000000004a41eb                _outbyte
                0x00000000004a421a                input
                0x00000000004a436e                getchar
                0x00000000004a4389                stdioInitialize
                0x00000000004a4576                fflush
                0x00000000004a4597                fprintf
                0x00000000004a45b8                fputs
                0x00000000004a45d9                gets
                0x00000000004a4664                ungetc
                0x00000000004a466e                ftell
                0x00000000004a4678                fileno
                0x00000000004a4682                fgetc
                0x00000000004a46a3                feof
                0x00000000004a46c4                ferror
                0x00000000004a46e5                fseek
                0x00000000004a4706                fputc
                0x00000000004a4727                stdioSetCursor
                0x00000000004a4742                stdioGetCursorX
                0x00000000004a475d                stdioGetCursorY
                0x00000000004a4778                scanf
                0x00000000004a4912                fscanf
                0x00000000004a492f                sscanf
                0x00000000004a4aea                kvprintf
                0x00000000004a5954                printf
                0x00000000004a597e                vfprintf
                0x00000000004a59f3                vprintf
                0x00000000004a5a12                stdout_printf
                0x00000000004a5a3e                stderr_printf
                0x00000000004a5a6a                perror
                0x00000000004a5a81                rewind
                0x00000000004a5abc                snprintf
 .text          0x00000000004a5ad0     0x105e stdlib.o
                0x00000000004a5aed                rtGetHeapStart
                0x00000000004a5af7                rtGetHeapEnd
                0x00000000004a5b01                rtGetHeapPointer
                0x00000000004a5b0b                rtGetAvailableHeap
                0x00000000004a5b15                heapSetLibcHeap
                0x00000000004a5bc8                heapAllocateMemory
                0x00000000004a5dfa                FreeHeap
                0x00000000004a5e04                heapInit
                0x00000000004a5f97                stdlibInitMM
                0x00000000004a5ffa                libcInitRT
                0x00000000004a601c                rand
                0x00000000004a6039                srand
                0x00000000004a6047                xmalloc
                0x00000000004a6079                stdlib_die
                0x00000000004a60af                malloc
                0x00000000004a60eb                realloc
                0x00000000004a6128                free
                0x00000000004a612e                calloc
                0x00000000004a6174                zmalloc
                0x00000000004a61b0                system
                0x00000000004a6574                stdlib_strncmp
                0x00000000004a65d7                __findenv
                0x00000000004a66a2                getenv
                0x00000000004a66cf                atoi
                0x00000000004a6796                reverse
                0x00000000004a67fd                itoa
                0x00000000004a68ab                abs
                0x00000000004a68bb                strtod
                0x00000000004a6aed                strtof
                0x00000000004a6b09                strtold
                0x00000000004a6b1c                atof
 .text          0x00000000004a6b2e      0x772 string.o
                0x00000000004a6b2e                memcmp
                0x00000000004a6b93                strdup
                0x00000000004a6be5                strndup
                0x00000000004a6c46                strrchr
                0x00000000004a6c81                strtoimax
                0x00000000004a6c8b                strtoumax
                0x00000000004a6c95                strcasecmp
                0x00000000004a6cfd                strncpy
                0x00000000004a6d53                strcmp
                0x00000000004a6db8                strncmp
                0x00000000004a6e1b                memset
                0x00000000004a6e62                memoryZeroMemory
                0x00000000004a6e89                memcpy
                0x00000000004a6ec6                strcpy
                0x00000000004a6efa                strcat
                0x00000000004a6f29                bcopy
                0x00000000004a6f55                bzero
                0x00000000004a6f75                strlen
                0x00000000004a6fa3                strnlen
                0x00000000004a6fd7                strcspn
                0x00000000004a7076                strspn
                0x00000000004a7115                strtok_r
                0x00000000004a71fc                strtok
                0x00000000004a7214                strchr
                0x00000000004a7240                strstr
 .text          0x00000000004a72a0       0x89 conio.o
                0x00000000004a72a0                putch
                0x00000000004a72c4                cputs
                0x00000000004a72f9                getch
                0x00000000004a7311                getche
 .text          0x00000000004a7329      0x192 unistd.o
                0x00000000004a7329                execve
                0x00000000004a7333                exit
                0x00000000004a7353                fork
                0x00000000004a736b                setuid
                0x00000000004a7375                getpid
                0x00000000004a738d                getppid
                0x00000000004a73a5                getgid
                0x00000000004a73af                dup
                0x00000000004a73b9                dup2
                0x00000000004a73c3                dup3
                0x00000000004a73cd                fcntl
                0x00000000004a73d7                nice
                0x00000000004a73e1                pause
                0x00000000004a73eb                mkdir
                0x00000000004a73ff                rmdir
                0x00000000004a7409                link
                0x00000000004a7413                mlock
                0x00000000004a741d                munlock
                0x00000000004a7427                mlockall
                0x00000000004a7431                munlockall
                0x00000000004a743b                sysconf
                0x00000000004a7445                fsync
                0x00000000004a744f                fdatasync
                0x00000000004a7459                fpathconf
                0x00000000004a7463                pathconf
                0x00000000004a746d                ioctl
                0x00000000004a7477                open
                0x00000000004a749d                close
 .text          0x00000000004a74bb       0x28 stubs.o
                0x00000000004a74bb                gramado_system_call
                0x00000000004a8000                . = ALIGN (0x1000)
 *fill*         0x00000000004a74e3      0xb1d 

.iplt           0x00000000004a8000        0x0
 .iplt          0x00000000004a8000        0x0 stubs.o

.eh_frame       0x00000000004a8000     0x20ac
 .eh_frame      0x00000000004a8000       0x34 crt0.o
 .eh_frame      0x00000000004a8034      0x1dc main.o
                                        0x1f4 (size before relaxing)
 .eh_frame      0x00000000004a8210      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x00000000004a8e3c      0x710 stdio.o
                                        0x728 (size before relaxing)
 .eh_frame      0x00000000004a954c      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x00000000004a994c      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x00000000004a9c6c       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x00000000004a9d0c      0x37c unistd.o
                                        0x394 (size before relaxing)
 .eh_frame      0x00000000004aa088       0x24 stubs.o
                                         0x3c (size before relaxing)

.rodata         0x00000000004aa0c0      0xeae
 .rodata        0x00000000004aa0c0      0x1dd main.o
 *fill*         0x00000000004aa29d        0x3 
 .rodata        0x00000000004aa2a0      0x3ab api.o
 *fill*         0x00000000004aa64b       0x15 
 .rodata        0x00000000004aa660      0x100 ctype.o
                0x00000000004aa660                _ctype
 .rodata        0x00000000004aa760      0x2f4 stdio.o
                0x00000000004aa8c0                hex2ascii_data
 *fill*         0x00000000004aaa54        0x4 
 .rodata        0x00000000004aaa58      0x510 stdlib.o
 .rodata        0x00000000004aaf68        0x6 conio.o

.note.gnu.property
                0x00000000004aaf70       0x1c
 .note.gnu.property
                0x00000000004aaf70       0x1c stubs.o

.rel.dyn        0x00000000004aaf8c        0x0
 .rel.got       0x00000000004aaf8c        0x0 stubs.o
 .rel.iplt      0x00000000004aaf8c        0x0 stubs.o
 .rel.text      0x00000000004aaf8c        0x0 stubs.o

.data           0x00000000004aafa0     0x1060
                0x00000000004aafa0                data = .
                0x00000000004aafa0                _data = .
                0x00000000004aafa0                __data = .
 *(.data)
 .data          0x00000000004aafa0      0x440 crt0.o
 .data          0x00000000004ab3e0      0x444 main.o
                0x00000000004ab820                listening
 *fill*         0x00000000004ab824       0x1c 
 .data          0x00000000004ab840      0x440 api.o
 .data          0x00000000004abc80        0x0 ctype.o
 .data          0x00000000004abc80        0x0 stdio.o
 .data          0x00000000004abc80        0x8 stdlib.o
                0x00000000004abc80                _infinity
 .data          0x00000000004abc88        0x0 string.o
 .data          0x00000000004abc88        0x0 conio.o
 .data          0x00000000004abc88        0x0 unistd.o
 .data          0x00000000004abc88        0x0 stubs.o
                0x00000000004ac000                . = ALIGN (0x1000)
 *fill*         0x00000000004abc88      0x378 

.got            0x00000000004ac000        0x0
 .got           0x00000000004ac000        0x0 stubs.o

.got.plt        0x00000000004ac000        0x0
 .got.plt       0x00000000004ac000        0x0 stubs.o

.igot.plt       0x00000000004ac000        0x0
 .igot.plt      0x00000000004ac000        0x0 stubs.o

.bss            0x00000000004ac000    0x127b4
                0x00000000004ac000                bss = .
                0x00000000004ac000                _bss = .
                0x00000000004ac000                __bss = .
 *(.bss)
 .bss           0x00000000004ac000        0x0 crt0.o
 .bss           0x00000000004ac000        0x0 main.o
 .bss           0x00000000004ac000     0x8004 api.o
 .bss           0x00000000004b4004        0x0 ctype.o
 .bss           0x00000000004b4004        0x1 stdio.o
 *fill*         0x00000000004b4005       0x1b 
 .bss           0x00000000004b4020     0x8020 stdlib.o
                0x00000000004b4020                environ
 .bss           0x00000000004bc040        0x4 string.o
 .bss           0x00000000004bc044        0x0 conio.o
 .bss           0x00000000004bc044        0x0 unistd.o
 .bss           0x00000000004bc044        0x0 stubs.o
                0x00000000004bd000                . = ALIGN (0x1000)
 *fill*         0x00000000004bc044      0xfbc 
 COMMON         0x00000000004bd000      0xd18 crt0.o
                0x00000000004bd000                g_cursor_x
                0x00000000004bd004                CurrentWindow
                0x00000000004bd008                stdout
                0x00000000004bd00c                g_char_attrib
                0x00000000004bd010                g_rows
                0x00000000004bd020                Streams
                0x00000000004bd0a0                g_using_gui
                0x00000000004bd0a4                ApplicationInfo
                0x00000000004bd0c0                prompt_out
                0x00000000004bd4c0                BufferInfo
                0x00000000004bd4c4                g_columns
                0x00000000004bd4c8                prompt_pos
                0x00000000004bd4cc                stdin
                0x00000000004bd4d0                prompt_status
                0x00000000004bd4e0                prompt_err
                0x00000000004bd8e0                CursorInfo
                0x00000000004bd8e4                stderr
                0x00000000004bd900                prompt
                0x00000000004bdd00                rect
                0x00000000004bdd04                g_cursor_y
                0x00000000004bdd08                ClientAreaInfo
                0x00000000004bdd0c                current_semaphore
                0x00000000004bdd10                prompt_max
                0x00000000004bdd14                taskmanTest1
 *fill*         0x00000000004bdd18        0x8 
 COMMON         0x00000000004bdd20      0x20c main.o
                0x00000000004bdd20                taskmanagerBuffer
                0x00000000004bdf20                taskmanagerStatus
                0x00000000004bdf24                taskmanagerBufferPos
                0x00000000004bdf28                taskmanagerError
 *fill*         0x00000000004bdf2c       0x14 
 COMMON         0x00000000004bdf40      0x438 api.o
                0x00000000004bdf40                heapList
                0x00000000004be340                libcHeap
                0x00000000004be344                dialogbox_button2
                0x00000000004be348                messagebox_button1
                0x00000000004be34c                heap_start
                0x00000000004be350                g_available_heap
                0x00000000004be354                g_heap_pointer
                0x00000000004be358                HEAP_SIZE
                0x00000000004be35c                dialogbox_button1
                0x00000000004be360                heap_end
                0x00000000004be364                HEAP_END
                0x00000000004be368                messagebox_button2
                0x00000000004be36c                Heap
                0x00000000004be370                heapCount
                0x00000000004be374                HEAP_START
 *fill*         0x00000000004be378        0x8 
 COMMON         0x00000000004be380      0x434 stdlib.o
                0x00000000004be380                mm_prev_pointer
                0x00000000004be3a0                mmblockList
                0x00000000004be7a0                last_valid
                0x00000000004be7a4                randseed
                0x00000000004be7a8                mmblockCount
                0x00000000004be7ac                last_size
                0x00000000004be7b0                current_mmblock
                0x00000000004be7b4                end = .
                0x00000000004be7b4                _end = .
                0x00000000004be7b4                __end = .
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
OUTPUT(TASKMAN.BIN elf32-i386)

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
