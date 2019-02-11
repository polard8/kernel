
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
 .text          0x00000000004a358a     0x2782 stdio.o
                0x00000000004a35b5                stdio_atoi
                0x00000000004a367c                stdio_fntos
                0x00000000004a37a6                fclose
                0x00000000004a380c                fopen
                0x00000000004a393e                scroll
                0x00000000004a3a0c                puts
                0x00000000004a3a27                fread
                0x00000000004a3a31                fwrite
                0x00000000004a3dfc                printf3
                0x00000000004a3e19                printf_atoi
                0x00000000004a3f09                printf_i2hex
                0x00000000004a3f6b                printf2
                0x00000000004a40f0                sprintf
                0x00000000004a4145                putchar
                0x00000000004a4166                outbyte
                0x00000000004a4324                _outbyte
                0x00000000004a4353                input
                0x00000000004a44a7                stdio_system_call
                0x00000000004a44cf                getchar
                0x00000000004a44e7                stdioInitialize
                0x00000000004a46d4                fflush
                0x00000000004a4767                fprintf
                0x00000000004a47d8                fputs
                0x00000000004a4849                gets
                0x00000000004a48d4                ungetc
                0x00000000004a490b                ftell
                0x00000000004a492c                fileno
                0x00000000004a4944                fgetc
                0x00000000004a49b2                feof
                0x00000000004a49e7                ferror
                0x00000000004a4a02                fseek
                0x00000000004a4a6e                fputc
                0x00000000004a4abd                stdioSetCursor
                0x00000000004a4ad5                stdioGetCursorX
                0x00000000004a4aed                stdioGetCursorY
                0x00000000004a4b05                scanf
                0x00000000004a4d45                kvprintf
                0x00000000004a5baf                printf
                0x00000000004a5bd9                vfprintf
                0x00000000004a5c4e                stdout_printf
                0x00000000004a5c7a                stderr_printf
                0x00000000004a5ca6                perror
                0x00000000004a5cbd                rewind
                0x00000000004a5cf8                snprintf
 .text          0x00000000004a5d0c      0xda7 stdlib.o
                0x00000000004a5d0c                stdlib_system_call
                0x00000000004a5d34                rtGetHeapStart
                0x00000000004a5d3e                rtGetHeapEnd
                0x00000000004a5d48                rtGetHeapPointer
                0x00000000004a5d52                rtGetAvailableHeap
                0x00000000004a5d5c                heapSetLibcHeap
                0x00000000004a5e0f                AllocateHeap
                0x00000000004a6051                AllocateHeapEx
                0x00000000004a6067                FreeHeap
                0x00000000004a6071                heapInit
                0x00000000004a6204                stdlibInitMM
                0x00000000004a6267                libcInitRT
                0x00000000004a6289                rand
                0x00000000004a62a6                srand
                0x00000000004a62b4                xmalloc
                0x00000000004a62e6                stdlib_die
                0x00000000004a631c                malloc
                0x00000000004a6358                realloc
                0x00000000004a6362                free
                0x00000000004a6368                calloc
                0x00000000004a63a7                system
                0x00000000004a676b                stdlib_strncmp
                0x00000000004a67cf                __findenv
                0x00000000004a689a                getenv
                0x00000000004a68c7                atoi
                0x00000000004a698e                reverse
                0x00000000004a69f5                itoa
                0x00000000004a6aa3                abs
 .text          0x00000000004a6ab3      0x658 string.o
                0x00000000004a6ab3                memcmp
                0x00000000004a6b18                strtold
                0x00000000004a6b1f                strdup
                0x00000000004a6b71                strrchr
                0x00000000004a6bac                strtoimax
                0x00000000004a6bb6                strtoumax
                0x00000000004a6bc0                strcasecmp
                0x00000000004a6c28                strncpy
                0x00000000004a6c7e                strcmp
                0x00000000004a6ce3                strncmp
                0x00000000004a6d46                memset
                0x00000000004a6d8d                memoryZeroMemory
                0x00000000004a6db4                memcpy
                0x00000000004a6df1                strcpy
                0x00000000004a6e25                strcat
                0x00000000004a6e54                bcopy
                0x00000000004a6e80                bzero
                0x00000000004a6ea0                strlen
                0x00000000004a6ece                strcspn
                0x00000000004a6f6d                strspn
                0x00000000004a700c                strtok_r
                0x00000000004a70f3                strtok
 .text          0x00000000004a710b       0x89 conio.o
                0x00000000004a710b                putch
                0x00000000004a712f                cputs
                0x00000000004a7164                getch
                0x00000000004a717c                getche
 .text          0x00000000004a7194       0x67 unistd.o
                0x00000000004a7194                unistd_system_call
                0x00000000004a71bc                execve
                0x00000000004a71c6                exit
                0x00000000004a71e6                fork
                0x00000000004a8000                . = ALIGN (0x1000)
 *fill*         0x00000000004a71fb      0xe05 

.iplt           0x00000000004a8000        0x0
 .iplt          0x00000000004a8000        0x0 unistd.o

.eh_frame       0x00000000004a8000     0x1c58
 .eh_frame      0x00000000004a8000       0x34 crt0.o
 .eh_frame      0x00000000004a8034      0x1dc main.o
                                        0x1f4 (size before relaxing)
 .eh_frame      0x00000000004a8210      0xc2c api.o
                                        0xc44 (size before relaxing)
 .eh_frame      0x00000000004a8e3c      0x6b8 stdio.o
                                        0x6d0 (size before relaxing)
 .eh_frame      0x00000000004a94f4      0x384 stdlib.o
                                        0x39c (size before relaxing)
 .eh_frame      0x00000000004a9878      0x2c0 string.o
                                        0x2d8 (size before relaxing)
 .eh_frame      0x00000000004a9b38       0xa0 conio.o
                                         0xb8 (size before relaxing)
 .eh_frame      0x00000000004a9bd8       0x80 unistd.o
                                         0x98 (size before relaxing)

.rodata         0x00000000004a9c60      0xf0d
 .rodata        0x00000000004a9c60      0x1dd main.o
 *fill*         0x00000000004a9e3d        0x3 
 .rodata        0x00000000004a9e40      0x3ab api.o
 *fill*         0x00000000004aa1eb       0x15 
 .rodata        0x00000000004aa200      0x100 ctype.o
                0x00000000004aa200                _ctype
 .rodata        0x00000000004aa300      0x374 stdio.o
                0x00000000004aa4e0                hex2ascii_data
 .rodata        0x00000000004aa674      0x4f3 stdlib.o
 .rodata        0x00000000004aab67        0x6 conio.o

.note.gnu.property
                0x00000000004aab70       0x1c
 .note.gnu.property
                0x00000000004aab70       0x1c unistd.o

.rel.dyn        0x00000000004aab8c        0x0
 .rel.got       0x00000000004aab8c        0x0 unistd.o
 .rel.iplt      0x00000000004aab8c        0x0 unistd.o
 .rel.text      0x00000000004aab8c        0x0 unistd.o

.data           0x00000000004aaba0     0x1460
                0x00000000004aaba0                data = .
                0x00000000004aaba0                _data = .
                0x00000000004aaba0                __data = .
 *(.data)
 .data          0x00000000004aaba0      0x440 crt0.o
 .data          0x00000000004aafe0      0x444 main.o
                0x00000000004ab420                listening
 *fill*         0x00000000004ab424       0x1c 
 .data          0x00000000004ab440      0x440 api.o
 .data          0x00000000004ab880        0x0 ctype.o
 .data          0x00000000004ab880        0x0 stdio.o
 .data          0x00000000004ab880        0x0 stdlib.o
 .data          0x00000000004ab880        0x0 string.o
 .data          0x00000000004ab880        0x0 conio.o
 .data          0x00000000004ab880        0x0 unistd.o
                0x00000000004ac000                . = ALIGN (0x1000)
 *fill*         0x00000000004ab880      0x780 

.got            0x00000000004ac000        0x0
 .got           0x00000000004ac000        0x0 unistd.o

.got.plt        0x00000000004ac000        0x0
 .got.plt       0x00000000004ac000        0x0 unistd.o

.igot.plt       0x00000000004ac000        0x0
 .igot.plt      0x00000000004ac000        0x0 unistd.o

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
