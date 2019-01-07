
Allocating common symbols
Common symbol       size              file

prompt              0x400             crt0.o
taskmanagerBufferPos
                    0x4               main.o
ClientAreaInfo      0x10              api.o
BufferInfo          0x10              api.o
stderr              0x10              stdio.o
prompt_pos          0x10              stdio.o
current_mmblock     0x10              stdlib.o
taskmanagerBuffer   0x200             main.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              stdio.o
stdin               0x10              stdio.o
heap_end            0x10              stdlib.o
rect                0x10              api.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              stdio.o
CurrentWindow       0x10              api.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             crt0.o
randseed            0x10              stdlib.o
current_semaphore   0x10              api.o
g_columns           0x10              stdio.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              stdio.o
taskmanagerStatus   0x4               main.o
Streams             0x80              crt0.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              stdio.o
prompt_out          0x400             crt0.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              stdio.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              stdio.o
taskmanTest1        0x4               crt0.o
taskmanagerError    0x4               main.o
g_char_attrib       0x10              stdio.o
ApplicationInfo     0x10              api.o
g_cursor_x          0x10              stdio.o
HEAP_END            0x10              stdlib.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

                0x0000000000400000                __image_base__ = 0x400000
                0x0000000000000000                __dll__ = 0x0
                0x0000000000400000                ___ImageBase = 0x400000
                0x0000000000001000                __section_alignment__ = 0x1000
                0x0000000000000200                __file_alignment__ = 0x200
                0x0000000000000004                __major_os_version__ = 0x4
                0x0000000000000000                __minor_os_version__ = 0x0
                0x0000000000000001                __major_image_version__ = 0x1
                0x0000000000000000                __minor_image_version__ = 0x0
                0x0000000000000004                __major_subsystem_version__ = 0x4
                0x0000000000000000                __minor_subsystem_version__ = 0x0
                0x0000000000000003                __subsystem__ = 0x3
                0x0000000000200000                __size_of_stack_reserve__ = 0x200000
                0x0000000000001000                __size_of_stack_commit__ = 0x1000
                0x0000000000100000                __size_of_heap_reserve__ = 0x100000
                0x0000000000001000                __size_of_heap_commit__ = 0x1000
                0x0000000000000000                __loader_flags__ = 0x0
                0x0000000000000000                __dll_characteristics__ = 0x0

.text           0x00000000004a1000     0x7000
                0x00000000004a1000                code = .
                0x00000000004a1000                _code = .
                0x00000000004a1000                __code = .
 *(.head_x86)
 .head_x86      0x00000000004a1000       0x10 head.o
                0x00000000004a1000                taskmanager_entry_point
 *(.text)
 .text          0x00000000004a1010       0x34 crt0.o
                0x00000000004a1010                crt0
 .text          0x00000000004a1044      0x53f main.o
                0x00000000004a1054                tmSleep
                0x00000000004a1070                tmProbeProcessList
                0x00000000004a108e                tmCreateTaskBar
                0x00000000004a10f9                tmProc
                0x00000000004a117e                tmUpdateStatus
                0x00000000004a11bb                tmDrawBar
                0x00000000004a1210                tmSetCursor
                0x00000000004a1226                tmstrlen
                0x00000000004a1254                DoProgress
                0x00000000004a12fb                DoSome
                0x00000000004a1353                progress_bar_test
                0x00000000004a1361                tmInit
                0x00000000004a1389                appMain
 *fill*         0x00000000004a1583        0x1 
 .text          0x00000000004a1584     0x2600 api.o
                0x00000000004a1584                system_call
                0x00000000004a15ac                apiSystem
                0x00000000004a19dc                system1
                0x00000000004a19fd                system2
                0x00000000004a1a1e                system3
                0x00000000004a1a3f                system4
                0x00000000004a1a60                system5
                0x00000000004a1a81                system6
                0x00000000004a1aa2                system7
                0x00000000004a1ac3                system8
                0x00000000004a1ae4                system9
                0x00000000004a1b05                system10
                0x00000000004a1b26                system11
                0x00000000004a1b47                system12
                0x00000000004a1b68                system13
                0x00000000004a1b89                system14
                0x00000000004a1baa                system15
                0x00000000004a1bcb                refresh_buffer
                0x00000000004a1d62                print_string
                0x00000000004a1d67                vsync
                0x00000000004a1d98                edit_box
                0x00000000004a1dc7                chama_procedimento
                0x00000000004a1df7                SetNextWindowProcedure
                0x00000000004a1e27                set_cursor
                0x00000000004a1e56                put_char
                0x00000000004a1e5b                carrega_bitmap_16x16
                0x00000000004a1e84                apiShutDown
                0x00000000004a1eb2                apiInitBackground
                0x00000000004a1eb7                MessageBox
                0x00000000004a23a9                mbProcedure
                0x00000000004a2436                DialogBox
                0x00000000004a2928                dbProcedure
                0x00000000004a29b5                call_kernel
                0x00000000004a2b35                call_gui
                0x00000000004a2bc6                APICreateWindow
                0x00000000004a2c52                APIRegisterWindow
                0x00000000004a2c94                APICloseWindow
                0x00000000004a2cd6                APISetFocus
                0x00000000004a2d18                APIGetFocus
                0x00000000004a2d44                APIKillFocus
                0x00000000004a2d86                APISetActiveWindow
                0x00000000004a2dc8                APIGetActiveWindow
                0x00000000004a2df4                APIShowCurrentProcessInfo
                0x00000000004a2e20                APIresize_window
                0x00000000004a2e49                APIredraw_window
                0x00000000004a2e72                APIreplace_window
                0x00000000004a2e9b                APImaximize_window
                0x00000000004a2ec4                APIminimize_window
                0x00000000004a2eed                APIupdate_window
                0x00000000004a2f16                APIget_foregroung_window
                0x00000000004a2f42                APIset_foregroung_window
                0x00000000004a2f6b                apiExit
                0x00000000004a2f96                kill
                0x00000000004a2f9b                dead_thread_collector
                0x00000000004a2fc7                api_strncmp
                0x00000000004a3025                refresh_screen
                0x00000000004a3051                api_refresh_screen
                0x00000000004a305b                apiReboot
                0x00000000004a3087                apiSetCursor
                0x00000000004a30b1                apiGetCursorX
                0x00000000004a30dd                apiGetCursorY
                0x00000000004a3109                apiGetClientAreaRect
                0x00000000004a3135                apiSetClientAreaRect
                0x00000000004a315e                apiCreateProcess
                0x00000000004a3187                apiCreateThread
                0x00000000004a31b0                apiStartThread
                0x00000000004a31d9                apiFOpen
                0x00000000004a3213                apiSaveFile
                0x00000000004a3271                apiDown
                0x00000000004a32cb                apiUp
                0x00000000004a3325                enterCriticalSection
                0x00000000004a337e                exitCriticalSection
                0x00000000004a33aa                initializeCriticalSection
                0x00000000004a33d6                apiBeginPaint
                0x00000000004a33e0                apiEndPaint
                0x00000000004a33ea                apiPutChar
                0x00000000004a3413                apiDefDialog
                0x00000000004a341d                apiGetSystemMetrics
                0x00000000004a3446                api_set_current_keyboard_responder
                0x00000000004a346f                api_get_current_keyboard_responder
                0x00000000004a349b                api_set_current_mouse_responder
                0x00000000004a34c4                api_get_current_mouse_responder
                0x00000000004a34f0                api_set_window_with_text_input
                0x00000000004a3536                api_get_window_with_text_input
                0x00000000004a3562                gramadocore_init_execve
                0x00000000004a356c                fork
                0x00000000004a3598                execve
                0x00000000004a35a2                apiDialog
                0x00000000004a3627                api_getchar
                0x00000000004a3653                apiDisplayBMP
                0x00000000004a3a23                apiSendMessage
                0x00000000004a3a64                apiDrawText
                0x00000000004a3aab                apiGetWSScreenWindow
                0x00000000004a3ad7                apiGetWSMainWindow
                0x00000000004a3b03                apiCreateTimer
                0x00000000004a3b2c                apiGetSysTimeInfo
                0x00000000004a3b55                apiShowWindow
 .text          0x00000000004a3b84        0x0 ctype.o
 .text          0x00000000004a3b84     0x2a10 stdio.o
                0x00000000004a3b84                stdio_atoi
                0x00000000004a3c39                stdio_fntos
                0x00000000004a3d38                fclose
                0x00000000004a3d9e                fopen
                0x00000000004a3ee0                scroll
                0x00000000004a3fa2                puts
                0x00000000004a4489                printf3
                0x00000000004a44a4                printf_atoi
                0x00000000004a4591                printf_i2hex
                0x00000000004a45ff                printf2
                0x00000000004a477f                sprintf
                0x00000000004a47c3                putchar
                0x00000000004a47ef                outbyte
                0x00000000004a4972                _outbyte
                0x00000000004a49a5                input
                0x00000000004a4b0d                stdio_system_call
                0x00000000004a4b35                getchar
                0x00000000004a4b61                stdioInitialize
                0x00000000004a4d48                fflush
                0x00000000004a4dda                fprintf
                0x00000000004a4e4f                fputs
                0x00000000004a4ec4                gets
                0x00000000004a4f51                ungetc
                0x00000000004a4f8e                ftell
                0x00000000004a4fb8                fileno
                0x00000000004a4fdb                fgetc
                0x00000000004a503c                feof
                0x00000000004a507a                ferror
                0x00000000004a50a0                fseek
                0x00000000004a511a                fputc
                0x00000000004a5162                stdioSetCursor
                0x00000000004a518c                stdioGetCursorX
                0x00000000004a51b8                stdioGetCursorY
                0x00000000004a51e4                scanf
                0x00000000004a5494                kvprintf
                0x00000000004a6423                printf
                0x00000000004a645b                vfprintf
                0x00000000004a64e7                stdout_printf
                0x00000000004a6516                stderr_printf
                0x00000000004a6545                perror
                0x00000000004a6558                rewind
 .text          0x00000000004a6594      0xc60 stdlib.o
                0x00000000004a6594                stdlib_system_call
                0x00000000004a65bc                rtGetHeapStart
                0x00000000004a65c6                rtGetHeapEnd
                0x00000000004a65d0                rtGetHeapPointer
                0x00000000004a65da                rtGetAvailableHeap
                0x00000000004a65e4                heapSetLibcHeap
                0x00000000004a668b                AllocateHeap
                0x00000000004a6877                AllocateHeapEx
                0x00000000004a688a                FreeHeap
                0x00000000004a6894                heapInit
                0x00000000004a6a37                stdlibInitMM
                0x00000000004a6aa1                libcInitRT
                0x00000000004a6aca                rand
                0x00000000004a6ae7                srand
                0x00000000004a6af4                xmalloc
                0x00000000004a6b1f                stdlib_die
                0x00000000004a6b60                malloc
                0x00000000004a6ba1                free
                0x00000000004a6ba6                system
                0x00000000004a6fb2                stdlib_strncmp
                0x00000000004a7010                exit
                0x00000000004a703b                __findenv
                0x00000000004a7106                getenv
                0x00000000004a713b                atoi
 .text          0x00000000004a71f4      0x430 string.o
                0x00000000004a71f4                strcmp
                0x00000000004a724f                strncmp
                0x00000000004a72ad                memoryZeroMemory
                0x00000000004a72d6                memcpy
                0x00000000004a7313                strcpy
                0x00000000004a7343                strcat
                0x00000000004a7373                bcopy
                0x00000000004a739a                bzero
                0x00000000004a73b5                strlen
                0x00000000004a73e0                strcspn
                0x00000000004a7480                strspn
                0x00000000004a7520                strtok_r
                0x00000000004a75f5                strtok
 .text          0x00000000004a7624       0x90 conio.o
                0x00000000004a7624                putch
                0x00000000004a7647                cputs
                0x00000000004a767b                getch
                0x00000000004a7692                getche
                0x00000000004a8000                . = ALIGN (0x1000)
 *fill*         0x00000000004a76b4      0x94c 

.eh_frame       0x00000000004a8000      0x228
 .eh_frame      0x00000000004a8000       0x34 crt0.o
 .eh_frame      0x00000000004a8034      0x1f4 main.o

.rodata         0x00000000004a9000      0x1e0
 .rodata        0x00000000004a9000      0x1dd main.o

.rdata          0x00000000004aa000      0xcc0
 .rdata         0x00000000004aa000      0x3a0 api.o
 .rdata         0x00000000004aa3a0      0x100 ctype.o
                0x00000000004aa3a0                _ctype
 .rdata         0x00000000004aa4a0      0x380 stdio.o
                0x00000000004aa680                hex2ascii_data
 .rdata         0x00000000004aa820      0x480 stdlib.o
 .rdata         0x00000000004aaca0       0x10 conio.o

.data           0x00000000004aacc0     0x1340
                0x00000000004aacc0                data = .
                0x00000000004aacc0                _data = .
                0x00000000004aacc0                __data = .
 *(.data)
 .data          0x00000000004aacc0      0x440 crt0.o
 .data          0x00000000004ab100      0x444 main.o
                0x00000000004ab540                listening
 .data          0x00000000004ab544      0x440 api.o
 .data          0x00000000004ab984        0x0 ctype.o
 .data          0x00000000004ab984        0x0 stdio.o
 .data          0x00000000004ab984        0x0 stdlib.o
 .data          0x00000000004ab984        0x0 string.o
 .data          0x00000000004ab984        0x0 conio.o
                0x00000000004ac000                . = ALIGN (0x1000)
 *fill*         0x00000000004ab984      0x67c 

.bss            0x00000000004ac000     0xa938
                0x00000000004ac000                bss = .
                0x00000000004ac000                _bss = .
                0x00000000004ac000                __bss = .
 *(.bss)
 .bss           0x00000000004ac000        0x0 crt0.o
 .bss           0x00000000004ac000        0x0 main.o
 .bss           0x00000000004ac000       0x40 api.o
 .bss           0x00000000004ac040        0x0 ctype.o
 .bss           0x00000000004ac040       0x10 stdio.o
 .bss           0x00000000004ac050     0x8010 stdlib.o
                0x00000000004ac050                environ
 .bss           0x00000000004b4060       0x10 string.o
 .bss           0x00000000004b4070        0x0 conio.o
                0x00000000004b5000                . = ALIGN (0x1000)
 *fill*         0x00000000004b4070      0xf90 
 COMMON         0x00000000004b5000      0xc84 crt0.o
                0x00000000004b5000                prompt
                0x00000000004b5400                prompt_err
                0x00000000004b5800                Streams
                0x00000000004b5880                prompt_out
                0x00000000004b5c80                taskmanTest1
 *fill*         0x00000000004b5c84       0x1c 
 COMMON         0x00000000004b5ca0      0x228 main.o
                0x00000000004b5ca0                taskmanagerBufferPos
                0x00000000004b5cc0                taskmanagerBuffer
                0x00000000004b5ec0                taskmanagerStatus
                0x00000000004b5ec4                taskmanagerError
 COMMON         0x00000000004b5ec8       0xb0 api.o
                0x00000000004b5ec8                ClientAreaInfo
                0x00000000004b5ed8                BufferInfo
                0x00000000004b5ee8                messagebox_button2
                0x00000000004b5ef8                rect
                0x00000000004b5f08                CurrentWindow
                0x00000000004b5f18                current_semaphore
                0x00000000004b5f28                dialogbox_button1
                0x00000000004b5f38                messagebox_button1
                0x00000000004b5f48                dialogbox_button2
                0x00000000004b5f58                CursorInfo
                0x00000000004b5f68                ApplicationInfo
 COMMON         0x00000000004b5f78       0xc0 stdio.o
                0x00000000004b5f78                stderr
                0x00000000004b5f88                prompt_pos
                0x00000000004b5f98                g_using_gui
                0x00000000004b5fa8                stdin
                0x00000000004b5fb8                prompt_max
                0x00000000004b5fc8                g_columns
                0x00000000004b5fd8                stdout
                0x00000000004b5fe8                g_rows
                0x00000000004b5ff8                g_cursor_y
                0x00000000004b6008                prompt_status
                0x00000000004b6018                g_char_attrib
                0x00000000004b6028                g_cursor_x
 COMMON         0x00000000004b6038      0x900 stdlib.o
                0x00000000004b6038                current_mmblock
                0x00000000004b6048                mm_prev_pointer
                0x00000000004b6058                heap_end
                0x00000000004b6068                g_available_heap
                0x00000000004b6078                heap_start
                0x00000000004b6088                heapCount
                0x00000000004b6098                HEAP_START
                0x00000000004b60a8                g_heap_pointer
                0x00000000004b60b8                heapList
                0x00000000004b64b8                randseed
                0x00000000004b64c8                HEAP_SIZE
                0x00000000004b64d8                last_size
                0x00000000004b64e8                last_valid
                0x00000000004b64f8                mmblockList
                0x00000000004b68f8                libcHeap
                0x00000000004b6908                Heap
                0x00000000004b6918                mmblockCount
                0x00000000004b6928                HEAP_END
                0x00000000004b6938                end = .
                0x00000000004b6938                _end = .
                0x00000000004b6938                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
OUTPUT(TASKMAN.BIN pe-i386)

.comment        0x0000000000000000       0x38
 .comment       0x0000000000000000       0x1b crt0.o
 .comment       0x000000000000001b       0x1b main.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
