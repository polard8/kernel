
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
 .text          0x00000000004a1000       0x37 crt0.o
                0x00000000004a1000                crt0
 .text          0x00000000004a1037      0x56a main.o
                0x00000000004a1047                tmSleep
                0x00000000004a1063                tmProbeProcessList
                0x00000000004a1081                tmCreateTaskBar
                0x00000000004a10ec                tmProc
                0x00000000004a1171                tmUpdateStatus
                0x00000000004a11ae                tmDrawBar
                0x00000000004a1203                tmSetCursor
                0x00000000004a1219                tmstrlen
                0x00000000004a1247                DoProgress
                0x00000000004a12ee                DoSome
                0x00000000004a1346                progress_bar_test
                0x00000000004a1354                tmInit
                0x00000000004a137c                main
 .text          0x00000000004a15a1     0x2017 api.o
                0x00000000004a15a1                system_call
                0x00000000004a15c9                apiSystem
                0x00000000004a19d1                system1
                0x00000000004a19f2                system2
                0x00000000004a1a13                system3
                0x00000000004a1a34                system4
                0x00000000004a1a55                system5
                0x00000000004a1a76                system6
                0x00000000004a1a97                system7
                0x00000000004a1ab8                system8
                0x00000000004a1ad9                system9
                0x00000000004a1afa                system10
                0x00000000004a1b1b                system11
                0x00000000004a1b3c                system12
                0x00000000004a1b5d                system13
                0x00000000004a1b7e                system14
                0x00000000004a1b9f                system15
                0x00000000004a1bc0                refresh_buffer
                0x00000000004a1c9c                print_string
                0x00000000004a1ca2                vsync
                0x00000000004a1cbc                edit_box
                0x00000000004a1cd8                chama_procedimento
                0x00000000004a1ce2                SetNextWindowProcedure
                0x00000000004a1cec                set_cursor
                0x00000000004a1d03                put_char
                0x00000000004a1d09                carrega_bitmap_16x16
                0x00000000004a1d22                apiShutDown
                0x00000000004a1d39                apiInitBackground
                0x00000000004a1d3f                MessageBox
                0x00000000004a22cb                mbProcedure
                0x00000000004a2339                DialogBox
                0x00000000004a26e9                dbProcedure
                0x00000000004a2757                call_kernel
                0x00000000004a28d2                call_gui
                0x00000000004a295e                APICreateWindow
                0x00000000004a29d7                APIRegisterWindow
                0x00000000004a29ff                APICloseWindow
                0x00000000004a2a27                APISetFocus
                0x00000000004a2a4f                APIGetFocus
                0x00000000004a2a64                APIKillFocus
                0x00000000004a2a8c                APISetActiveWindow
                0x00000000004a2ab4                APIGetActiveWindow
                0x00000000004a2ac9                APIShowCurrentProcessInfo
                0x00000000004a2adf                APIresize_window
                0x00000000004a2af9                APIredraw_window
                0x00000000004a2b13                APIreplace_window
                0x00000000004a2b2d                APImaximize_window
                0x00000000004a2b49                APIminimize_window
                0x00000000004a2b65                APIupdate_window
                0x00000000004a2b81                APIget_foregroung_window
                0x00000000004a2b97                APIset_foregroung_window
                0x00000000004a2bb3                apiExit
                0x00000000004a2bd0                kill
                0x00000000004a2bd6                dead_thread_collector
                0x00000000004a2bec                api_strncmp
                0x00000000004a2c4f                refresh_screen
                0x00000000004a2c65                api_refresh_screen
                0x00000000004a2c70                apiReboot
                0x00000000004a2c86                apiSetCursor
                0x00000000004a2c9e                apiGetCursorX
                0x00000000004a2cb6                apiGetCursorY
                0x00000000004a2cce                apiGetClientAreaRect
                0x00000000004a2ce6                apiSetClientAreaRect
                0x00000000004a2d05                apiCreateProcess
                0x00000000004a2d1e                apiCreateThread
                0x00000000004a2d37                apiStartThread
                0x00000000004a2d53                apiFOpen
                0x00000000004a2d7f                apiSaveFile
                0x00000000004a2dd2                apiDown
                0x00000000004a2e25                apiUp
                0x00000000004a2e78                enterCriticalSection
                0x00000000004a2eb3                exitCriticalSection
                0x00000000004a2ecc                initializeCriticalSection
                0x00000000004a2ee5                apiBeginPaint
                0x00000000004a2ef0                apiEndPaint
                0x00000000004a2efb                apiPutChar
                0x00000000004a2f17                apiDefDialog
                0x00000000004a2f21                apiGetSystemMetrics
                0x00000000004a2f3f                api_set_current_keyboard_responder
                0x00000000004a2f5e                api_get_current_keyboard_responder
                0x00000000004a2f76                api_set_current_mouse_responder
                0x00000000004a2f95                api_get_current_mouse_responder
                0x00000000004a2fad                api_set_window_with_text_input
                0x00000000004a2fef                api_get_window_with_text_input
                0x00000000004a3007                gramadocore_init_execve
                0x00000000004a3011                apiDialog
                0x00000000004a309d                api_getchar
                0x00000000004a30b5                apiDisplayBMP
                0x00000000004a34bc                apiSendMessage
                0x00000000004a34f2                apiDrawText
                0x00000000004a3531                apiGetWSScreenWindow
                0x00000000004a3549                apiGetWSMainWindow
                0x00000000004a3561                apiCreateTimer
                0x00000000004a357e                apiGetSysTimeInfo
                0x00000000004a359c                apiShowWindow
 .text          0x00000000004a35b8        0x0 ctype.o
 .text          0x00000000004a35b8     0x2529 stdio.o
                0x00000000004a3600                stdio_atoi
                0x00000000004a36c7                stdio_fntos
                0x00000000004a37f1                fclose
                0x00000000004a3812                fopen
                0x00000000004a3833                scroll
                0x00000000004a3901                puts
                0x00000000004a391c                fread
                0x00000000004a3926                fwrite
                0x00000000004a3cf1                printf3
                0x00000000004a3d0e                printf_atoi
                0x00000000004a3dfe                printf_i2hex
                0x00000000004a3e60                printf2
                0x00000000004a3fe5                sprintf
                0x00000000004a403a                putchar
                0x00000000004a405b                outbyte
                0x00000000004a4219                _outbyte
                0x00000000004a4248                input
                0x00000000004a439c                getchar
                0x00000000004a43b7                stdioInitialize
                0x00000000004a45a4                fflush
                0x00000000004a45c5                fprintf
                0x00000000004a45e6                fputs
                0x00000000004a4607                gets
                0x00000000004a4692                ungetc
                0x00000000004a469c                ftell
                0x00000000004a46a6                fileno
                0x00000000004a46b0                fgetc
                0x00000000004a46d1                feof
                0x00000000004a46f2                ferror
                0x00000000004a4713                fseek
                0x00000000004a4734                fputc
                0x00000000004a4755                stdioSetCursor
                0x00000000004a4770                stdioGetCursorX
                0x00000000004a478b                stdioGetCursorY
                0x00000000004a47a6                scanf
                0x00000000004a4940                sscanf
                0x00000000004a4afb                kvprintf
                0x00000000004a5965                printf
                0x00000000004a598f                vfprintf
                0x00000000004a5a04                vprintf
                0x00000000004a5a23                stdout_printf
                0x00000000004a5a4f                stderr_printf
                0x00000000004a5a7b                perror
                0x00000000004a5a92                rewind
                0x00000000004a5acd                snprintf
 .text          0x00000000004a5ae1     0x105e stdlib.o
                0x00000000004a5afe                rtGetHeapStart
                0x00000000004a5b08                rtGetHeapEnd
                0x00000000004a5b12                rtGetHeapPointer
                0x00000000004a5b1c                rtGetAvailableHeap
                0x00000000004a5b26                heapSetLibcHeap
                0x00000000004a5bd9                heapAllocateMemory
                0x00000000004a5e0b                FreeHeap
                0x00000000004a5e15                heapInit
                0x00000000004a5fa8                stdlibInitMM
                0x00000000004a600b                libcInitRT
                0x00000000004a602d                rand
                0x00000000004a604a                srand
                0x00000000004a6058                xmalloc
                0x00000000004a608a                stdlib_die
                0x00000000004a60c0                malloc
                0x00000000004a60fc                realloc
                0x00000000004a6139                free
                0x00000000004a613f                calloc
                0x00000000004a6185                zmalloc
                0x00000000004a61c1                system
                0x00000000004a6585                stdlib_strncmp
                0x00000000004a65e8                __findenv
                0x00000000004a66b3                getenv
                0x00000000004a66e0                atoi
                0x00000000004a67a7                reverse
                0x00000000004a680e                itoa
                0x00000000004a68bc                abs
                0x00000000004a68cc                strtod
                0x00000000004a6afe                strtof
                0x00000000004a6b1a                strtold
                0x00000000004a6b2d                atof
 .text          0x00000000004a6b3f      0x772 string.o
                0x00000000004a6b3f                memcmp
                0x00000000004a6ba4                strdup
                0x00000000004a6bf6                strndup
                0x00000000004a6c57                strrchr
                0x00000000004a6c92                strtoimax
                0x00000000004a6c9c                strtoumax
                0x00000000004a6ca6                strcasecmp
                0x00000000004a6d0e                strncpy
                0x00000000004a6d64                strcmp
                0x00000000004a6dc9                strncmp
                0x00000000004a6e2c                memset
                0x00000000004a6e73                memoryZeroMemory
                0x00000000004a6e9a                memcpy
                0x00000000004a6ed7                strcpy
                0x00000000004a6f0b                strcat
                0x00000000004a6f3a                bcopy
                0x00000000004a6f66                bzero
                0x00000000004a6f86                strlen
                0x00000000004a6fb4                strnlen
                0x00000000004a6fe8                strcspn
                0x00000000004a7087                strspn
                0x00000000004a7126                strtok_r
                0x00000000004a720d                strtok
                0x00000000004a7225                strchr
                0x00000000004a7251                strstr
 .text          0x00000000004a72b1       0x89 conio.o
                0x00000000004a72b1                putch
                0x00000000004a72d5                cputs
                0x00000000004a730a                getch
                0x00000000004a7322                getche
 .text          0x00000000004a733a      0x1b3 unistd.o
                0x00000000004a733a                execve
                0x00000000004a7344                exit
                0x00000000004a7364                fork
                0x00000000004a737c                setuid
                0x00000000004a7386                getpid
                0x00000000004a739e                getppid
                0x00000000004a73b6                getgid
                0x00000000004a73c0                dup
                0x00000000004a73ca                dup2
                0x00000000004a73d4                dup3
                0x00000000004a73de                fcntl
                0x00000000004a73e8                nice
                0x00000000004a73f2                pause
                0x00000000004a73fc                mkdir
                0x00000000004a7410                rmdir
                0x00000000004a741a                link
                0x00000000004a7424                mlock
                0x00000000004a742e                munlock
                0x00000000004a7438                mlockall
                0x00000000004a7442                munlockall
                0x00000000004a744c                sysconf
                0x00000000004a7456                fsync
                0x00000000004a7460                fdatasync
                0x00000000004a746a                fpathconf
                0x00000000004a7474                pathconf
                0x00000000004a747e                ioctl
                0x00000000004a7488                open
                0x00000000004a74ae                close
                0x00000000004a74cc                pipe
 .text          0x00000000004a74ed       0x28 stubs.o
                0x00000000004a74ed                gramado_system_call
                0x00000000004a8000                . = ALIGN (0x1000)
 *fill*         0x00000000004a7515      0xaeb 

.iplt           0x00000000004a8000        0x0
 .iplt          0x00000000004a8000        0x0 stubs.o

.rodata         0x00000000004a8000      0xeae
 .rodata        0x00000000004a8000        0x6 crt0.o
 *fill*         0x00000000004a8006        0x2 
 .rodata        0x00000000004a8008      0x1f1 main.o
 *fill*         0x00000000004a81f9        0x3 
 .rodata        0x00000000004a81fc      0x3ab api.o
 *fill*         0x00000000004a85a7       0x19 
 .rodata        0x00000000004a85c0      0x100 ctype.o
                0x00000000004a85c0                _ctype
 .rodata        0x00000000004a86c0      0x2d4 stdio.o
                0x00000000004a8800                hex2ascii_data
 *fill*         0x00000000004a8994        0x4 
 .rodata        0x00000000004a8998      0x510 stdlib.o
 .rodata        0x00000000004a8ea8        0x6 conio.o

.eh_frame       0x00000000004a8eb0     0x20b8
 .eh_frame      0x00000000004a8eb0       0x34 crt0.o
 .eh_frame      0x00000000004a8ee4      0x1e8 main.o
                                        0x200 (size before relaxing)
 .eh_frame      0x00000000004a90cc      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x00000000004a9cf8      0x6f0 stdio.o
                                        0x708 (size before relaxing)
 .eh_frame      0x00000000004aa3e8      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x00000000004aa7e8      0x320 string.o
                                        0x338 (size before relaxing)
 .eh_frame      0x00000000004aab08       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x00000000004aaba8      0x39c unistd.o
                                        0x3b4 (size before relaxing)
 .eh_frame      0x00000000004aaf44       0x24 stubs.o
                                         0x3c (size before relaxing)

.note.gnu.property
                0x00000000004aaf68       0x1c
 .note.gnu.property
                0x00000000004aaf68       0x1c stubs.o

.rel.dyn        0x00000000004aaf84        0x0
 .rel.got       0x00000000004aaf84        0x0 stubs.o
 .rel.iplt      0x00000000004aaf84        0x0 stubs.o
 .rel.text      0x00000000004aaf84        0x0 stubs.o

.data           0x00000000004aafa0     0x1060
                0x00000000004aafa0                data = .
                0x00000000004aafa0                _data = .
                0x00000000004aafa0                __data = .
 *(.data)
 .data          0x00000000004aafa0      0x448 crt0.o
 *fill*         0x00000000004ab3e8       0x18 
 .data          0x00000000004ab400      0x444 main.o
                0x00000000004ab840                listening
 *fill*         0x00000000004ab844       0x1c 
 .data          0x00000000004ab860      0x440 api.o
 .data          0x00000000004abca0        0x0 ctype.o
 .data          0x00000000004abca0        0x0 stdio.o
 .data          0x00000000004abca0        0x8 stdlib.o
                0x00000000004abca0                _infinity
 .data          0x00000000004abca8        0x0 string.o
 .data          0x00000000004abca8        0x0 conio.o
 .data          0x00000000004abca8        0x0 unistd.o
 .data          0x00000000004abca8        0x0 stubs.o
                0x00000000004ac000                . = ALIGN (0x1000)
 *fill*         0x00000000004abca8      0x358 

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
