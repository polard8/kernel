
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
 .text          0x00000000004a1573     0x1fee api.o
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
                0x00000000004a1c70                print_string
                0x00000000004a1c76                vsync
                0x00000000004a1c90                edit_box
                0x00000000004a1cac                chama_procedimento
                0x00000000004a1cc7                SetNextWindowProcedure
                0x00000000004a1ce2                set_cursor
                0x00000000004a1cfe                put_char
                0x00000000004a1d04                carrega_bitmap_16x16
                0x00000000004a1d1d                apiShutDown
                0x00000000004a1d34                apiInitBackground
                0x00000000004a1d3a                MessageBox
                0x00000000004a2290                mbProcedure
                0x00000000004a22fe                DialogBox
                0x00000000004a2678                dbProcedure
                0x00000000004a26e6                call_kernel
                0x00000000004a2861                call_gui
                0x00000000004a28ed                APICreateWindow
                0x00000000004a2967                APIRegisterWindow
                0x00000000004a2994                APICloseWindow
                0x00000000004a29c1                APISetFocus
                0x00000000004a29ee                APIGetFocus
                0x00000000004a2a03                APIKillFocus
                0x00000000004a2a30                APISetActiveWindow
                0x00000000004a2a5d                APIGetActiveWindow
                0x00000000004a2a72                APIShowCurrentProcessInfo
                0x00000000004a2a88                APIresize_window
                0x00000000004a2aa2                APIredraw_window
                0x00000000004a2abc                APIreplace_window
                0x00000000004a2ad6                APImaximize_window
                0x00000000004a2af2                APIminimize_window
                0x00000000004a2b0e                APIupdate_window
                0x00000000004a2b2a                APIget_foregroung_window
                0x00000000004a2b40                APIset_foregroung_window
                0x00000000004a2b5c                apiExit
                0x00000000004a2b79                kill
                0x00000000004a2b7f                dead_thread_collector
                0x00000000004a2b95                api_strncmp
                0x00000000004a2bf8                refresh_screen
                0x00000000004a2c0e                api_refresh_screen
                0x00000000004a2c19                apiReboot
                0x00000000004a2c2f                apiSetCursor
                0x00000000004a2c47                apiGetCursorX
                0x00000000004a2c5f                apiGetCursorY
                0x00000000004a2c77                apiGetClientAreaRect
                0x00000000004a2c8f                apiSetClientAreaRect
                0x00000000004a2cae                apiCreateProcess
                0x00000000004a2cc7                apiCreateThread
                0x00000000004a2ce0                apiStartThread
                0x00000000004a2cfc                apiFOpen
                0x00000000004a2d28                apiSaveFile
                0x00000000004a2d7b                apiDown
                0x00000000004a2dce                apiUp
                0x00000000004a2e21                enterCriticalSection
                0x00000000004a2e5c                exitCriticalSection
                0x00000000004a2e75                initializeCriticalSection
                0x00000000004a2e8e                apiBeginPaint
                0x00000000004a2e99                apiEndPaint
                0x00000000004a2ea4                apiPutChar
                0x00000000004a2ec0                apiDefDialog
                0x00000000004a2eca                apiGetSystemMetrics
                0x00000000004a2ee8                api_set_current_keyboard_responder
                0x00000000004a2f07                api_get_current_keyboard_responder
                0x00000000004a2f1f                api_set_current_mouse_responder
                0x00000000004a2f3e                api_get_current_mouse_responder
                0x00000000004a2f56                api_set_window_with_text_input
                0x00000000004a2f98                api_get_window_with_text_input
                0x00000000004a2fb0                gramadocore_init_execve
                0x00000000004a2fba                apiDialog
                0x00000000004a3046                api_getchar
                0x00000000004a305e                apiDisplayBMP
                0x00000000004a3465                apiSendMessage
                0x00000000004a349b                apiDrawText
                0x00000000004a34da                apiGetWSScreenWindow
                0x00000000004a34f2                apiGetWSMainWindow
                0x00000000004a350a                apiCreateTimer
                0x00000000004a3527                apiGetSysTimeInfo
                0x00000000004a3545                apiShowWindow
 .text          0x00000000004a3561        0x0 ctype.o
 .text          0x00000000004a3561     0x2546 stdio.o
                0x00000000004a35a9                stdio_atoi
                0x00000000004a3670                stdio_fntos
                0x00000000004a379a                fclose
                0x00000000004a37bb                fopen
                0x00000000004a37dc                scroll
                0x00000000004a38aa                puts
                0x00000000004a38c5                fread
                0x00000000004a38cf                fwrite
                0x00000000004a3c9a                printf3
                0x00000000004a3cb7                printf_atoi
                0x00000000004a3da7                printf_i2hex
                0x00000000004a3e09                printf2
                0x00000000004a3f8e                sprintf
                0x00000000004a3fe3                putchar
                0x00000000004a4004                outbyte
                0x00000000004a41c2                _outbyte
                0x00000000004a41f1                input
                0x00000000004a4345                getchar
                0x00000000004a4360                stdioInitialize
                0x00000000004a454d                fflush
                0x00000000004a456e                fprintf
                0x00000000004a458f                fputs
                0x00000000004a45b0                gets
                0x00000000004a463b                ungetc
                0x00000000004a4645                ftell
                0x00000000004a464f                fileno
                0x00000000004a4659                fgetc
                0x00000000004a467a                feof
                0x00000000004a469b                ferror
                0x00000000004a46bc                fseek
                0x00000000004a46dd                fputc
                0x00000000004a46fe                stdioSetCursor
                0x00000000004a4719                stdioGetCursorX
                0x00000000004a4734                stdioGetCursorY
                0x00000000004a474f                scanf
                0x00000000004a48e9                fscanf
                0x00000000004a4906                sscanf
                0x00000000004a4ac1                kvprintf
                0x00000000004a592b                printf
                0x00000000004a5955                vfprintf
                0x00000000004a59ca                vprintf
                0x00000000004a59e9                stdout_printf
                0x00000000004a5a15                stderr_printf
                0x00000000004a5a41                perror
                0x00000000004a5a58                rewind
                0x00000000004a5a93                snprintf
 .text          0x00000000004a5aa7     0x105e stdlib.o
                0x00000000004a5ac4                rtGetHeapStart
                0x00000000004a5ace                rtGetHeapEnd
                0x00000000004a5ad8                rtGetHeapPointer
                0x00000000004a5ae2                rtGetAvailableHeap
                0x00000000004a5aec                heapSetLibcHeap
                0x00000000004a5b9f                heapAllocateMemory
                0x00000000004a5dd1                FreeHeap
                0x00000000004a5ddb                heapInit
                0x00000000004a5f6e                stdlibInitMM
                0x00000000004a5fd1                libcInitRT
                0x00000000004a5ff3                rand
                0x00000000004a6010                srand
                0x00000000004a601e                xmalloc
                0x00000000004a6050                stdlib_die
                0x00000000004a6086                malloc
                0x00000000004a60c2                realloc
                0x00000000004a60ff                free
                0x00000000004a6105                calloc
                0x00000000004a614b                zmalloc
                0x00000000004a6187                system
                0x00000000004a654b                stdlib_strncmp
                0x00000000004a65ae                __findenv
                0x00000000004a6679                getenv
                0x00000000004a66a6                atoi
                0x00000000004a676d                reverse
                0x00000000004a67d4                itoa
                0x00000000004a6882                abs
                0x00000000004a6892                strtod
                0x00000000004a6ac4                strtof
                0x00000000004a6ae0                strtold
                0x00000000004a6af3                atof
 .text          0x00000000004a6b05      0x772 string.o
                0x00000000004a6b05                memcmp
                0x00000000004a6b6a                strdup
                0x00000000004a6bbc                strndup
                0x00000000004a6c1d                strrchr
                0x00000000004a6c58                strtoimax
                0x00000000004a6c62                strtoumax
                0x00000000004a6c6c                strcasecmp
                0x00000000004a6cd4                strncpy
                0x00000000004a6d2a                strcmp
                0x00000000004a6d8f                strncmp
                0x00000000004a6df2                memset
                0x00000000004a6e39                memoryZeroMemory
                0x00000000004a6e60                memcpy
                0x00000000004a6e9d                strcpy
                0x00000000004a6ed1                strcat
                0x00000000004a6f00                bcopy
                0x00000000004a6f2c                bzero
                0x00000000004a6f4c                strlen
                0x00000000004a6f7a                strnlen
                0x00000000004a6fae                strcspn
                0x00000000004a704d                strspn
                0x00000000004a70ec                strtok_r
                0x00000000004a71d3                strtok
                0x00000000004a71eb                strchr
                0x00000000004a7217                strstr
 .text          0x00000000004a7277       0x89 conio.o
                0x00000000004a7277                putch
                0x00000000004a729b                cputs
                0x00000000004a72d0                getch
                0x00000000004a72e8                getche
 .text          0x00000000004a7300      0x176 unistd.o
                0x00000000004a7300                execve
                0x00000000004a730a                exit
                0x00000000004a732a                fork
                0x00000000004a7342                setuid
                0x00000000004a734c                getpid
                0x00000000004a7364                getppid
                0x00000000004a737c                getgid
                0x00000000004a7386                dup
                0x00000000004a7390                dup2
                0x00000000004a739a                dup3
                0x00000000004a73a4                fcntl
                0x00000000004a73ae                nice
                0x00000000004a73b8                shutdown
                0x00000000004a73c2                send
                0x00000000004a73cc                pause
                0x00000000004a73d6                mkdir
                0x00000000004a73ea                rmdir
                0x00000000004a73f4                link
                0x00000000004a73fe                socket
                0x00000000004a7408                recv
                0x00000000004a7412                mlock
                0x00000000004a741c                munlock
                0x00000000004a7426                mlockall
                0x00000000004a7430                munlockall
                0x00000000004a743a                sysconf
                0x00000000004a7444                fsync
                0x00000000004a744e                fdatasync
                0x00000000004a7458                fpathconf
                0x00000000004a7462                pathconf
                0x00000000004a746c                ioctl
 .text          0x00000000004a7476       0x28 stubs.o
                0x00000000004a7476                gramado_system_call
                0x00000000004a8000                . = ALIGN (0x1000)
 *fill*         0x00000000004a749e      0xb62 

.iplt           0x00000000004a8000        0x0
 .iplt          0x00000000004a8000        0x0 stubs.o

.eh_frame       0x00000000004a8000     0x20ec
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
 .eh_frame      0x00000000004a9d0c      0x3bc unistd.o
                                        0x3d4 (size before relaxing)
 .eh_frame      0x00000000004aa0c8       0x24 stubs.o
                                         0x3c (size before relaxing)

.rodata         0x00000000004aa100      0xe8e
 .rodata        0x00000000004aa100      0x1dd main.o
 *fill*         0x00000000004aa2dd        0x3 
 .rodata        0x00000000004aa2e0      0x39d api.o
 *fill*         0x00000000004aa67d        0x3 
 .rodata        0x00000000004aa680      0x100 ctype.o
                0x00000000004aa680                _ctype
 .rodata        0x00000000004aa780      0x2f4 stdio.o
                0x00000000004aa8e0                hex2ascii_data
 *fill*         0x00000000004aaa74        0x4 
 .rodata        0x00000000004aaa78      0x510 stdlib.o
 .rodata        0x00000000004aaf88        0x6 conio.o

.note.gnu.property
                0x00000000004aaf90       0x1c
 .note.gnu.property
                0x00000000004aaf90       0x1c stubs.o

.rel.dyn        0x00000000004aafac        0x0
 .rel.got       0x00000000004aafac        0x0 stubs.o
 .rel.iplt      0x00000000004aafac        0x0 stubs.o
 .rel.text      0x00000000004aafac        0x0 stubs.o

.data           0x00000000004aafc0     0x1040
                0x00000000004aafc0                data = .
                0x00000000004aafc0                _data = .
                0x00000000004aafc0                __data = .
 *(.data)
 .data          0x00000000004aafc0      0x440 crt0.o
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
