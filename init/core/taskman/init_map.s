
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
heap_end            0x10              api.o
rect                0x10              api.o
g_available_heap    0x10              api.o
heap_start          0x10              api.o
heapCount           0x10              api.o
HEAP_START          0x10              api.o
prompt_max          0x10              stdio.o
CurrentWindow       0x10              api.o
g_heap_pointer      0x10              api.o
heapList            0x400             api.o
prompt_err          0x400             crt0.o
randseed            0x10              stdlib.o
current_semaphore   0x10              api.o
g_columns           0x10              stdio.o
HEAP_SIZE           0x10              api.o
stdout              0x10              stdio.o
taskmanagerStatus   0x4               main.o
Streams             0x80              crt0.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              stdio.o
prompt_out          0x400             crt0.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
libcHeap            0x10              api.o
g_cursor_y          0x10              stdio.o
messagebox_button1  0x10              api.o
Heap                0x10              api.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              stdio.o
taskmanTest1        0x4               crt0.o
taskmanagerError    0x4               main.o
g_char_attrib       0x10              stdio.o
ApplicationInfo     0x10              api.o
g_cursor_x          0x10              stdio.o
HEAP_END            0x10              api.o

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
 .text          0x00000000004a1584     0x25d0 api.o
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
                0x00000000004a356c                apiDialog
                0x00000000004a35f1                api_getchar
                0x00000000004a361d                apiDisplayBMP
                0x00000000004a39ed                apiSendMessage
                0x00000000004a3a2e                apiDrawText
                0x00000000004a3a75                apiGetWSScreenWindow
                0x00000000004a3aa1                apiGetWSMainWindow
                0x00000000004a3acd                apiCreateTimer
                0x00000000004a3af6                apiGetSysTimeInfo
                0x00000000004a3b1f                apiShowWindow
 .text          0x00000000004a3b54        0x0 ctype.o
 .text          0x00000000004a3b54     0x2a10 stdio.o
                0x00000000004a3b54                stdio_atoi
                0x00000000004a3c09                stdio_fntos
                0x00000000004a3d08                fclose
                0x00000000004a3d6e                fopen
                0x00000000004a3eb0                scroll
                0x00000000004a3f72                puts
                0x00000000004a4459                printf3
                0x00000000004a4474                printf_atoi
                0x00000000004a4561                printf_i2hex
                0x00000000004a45cf                printf2
                0x00000000004a474f                sprintf
                0x00000000004a4793                putchar
                0x00000000004a47bf                outbyte
                0x00000000004a4942                _outbyte
                0x00000000004a4975                input
                0x00000000004a4add                stdio_system_call
                0x00000000004a4b05                getchar
                0x00000000004a4b31                stdioInitialize
                0x00000000004a4d18                fflush
                0x00000000004a4daa                fprintf
                0x00000000004a4e1f                fputs
                0x00000000004a4e94                gets
                0x00000000004a4f21                ungetc
                0x00000000004a4f5e                ftell
                0x00000000004a4f88                fileno
                0x00000000004a4fab                fgetc
                0x00000000004a500c                feof
                0x00000000004a504a                ferror
                0x00000000004a5070                fseek
                0x00000000004a50ea                fputc
                0x00000000004a5132                stdioSetCursor
                0x00000000004a515c                stdioGetCursorX
                0x00000000004a5188                stdioGetCursorY
                0x00000000004a51b4                scanf
                0x00000000004a5464                kvprintf
                0x00000000004a63f3                printf
                0x00000000004a642b                vfprintf
                0x00000000004a64b7                stdout_printf
                0x00000000004a64e6                stderr_printf
                0x00000000004a6515                perror
                0x00000000004a6528                rewind
 .text          0x00000000004a6564      0xda0 stdlib.o
                0x00000000004a6564                stdlib_system_call
                0x00000000004a658c                rtGetHeapStart
                0x00000000004a6596                rtGetHeapEnd
                0x00000000004a65a0                rtGetHeapPointer
                0x00000000004a65aa                rtGetAvailableHeap
                0x00000000004a65b4                heapSetLibcHeap
                0x00000000004a665b                AllocateHeap
                0x00000000004a687a                AllocateHeapEx
                0x00000000004a688d                FreeHeap
                0x00000000004a6897                heapInit
                0x00000000004a6a3a                stdlibInitMM
                0x00000000004a6aa4                libcInitRT
                0x00000000004a6acd                rand
                0x00000000004a6aea                srand
                0x00000000004a6af7                xmalloc
                0x00000000004a6b22                stdlib_die
                0x00000000004a6b63                malloc
                0x00000000004a6ba4                free
                0x00000000004a6ba9                calloc
                0x00000000004a6bec                system
                0x00000000004a6ff8                stdlib_strncmp
                0x00000000004a7056                __findenv
                0x00000000004a7121                getenv
                0x00000000004a7156                atoi
                0x00000000004a720b                reverse
                0x00000000004a726a                itoa
 .text          0x00000000004a7304       0x90 unistd.o
                0x00000000004a7304                unistd_system_call
                0x00000000004a732c                execve
                0x00000000004a7336                exit
                0x00000000004a7361                fork
 .text          0x00000000004a7394      0x470 string.o
                0x00000000004a7394                strcmp
                0x00000000004a73ef                strncmp
                0x00000000004a744d                memset
                0x00000000004a7496                memoryZeroMemory
                0x00000000004a74bf                memcpy
                0x00000000004a74fc                strcpy
                0x00000000004a752c                strcat
                0x00000000004a755c                bcopy
                0x00000000004a7583                bzero
                0x00000000004a759e                strlen
                0x00000000004a75c9                strcspn
                0x00000000004a7669                strspn
                0x00000000004a7709                strtok_r
                0x00000000004a77de                strtok
                0x00000000004a8000                . = ALIGN (0x1000)
 *fill*         0x00000000004a7804      0x7fc 

.eh_frame       0x00000000004a8000      0x228
 .eh_frame      0x00000000004a8000       0x34 crt0.o
 .eh_frame      0x00000000004a8034      0x1f4 main.o

.rodata         0x00000000004a9000      0x1e0
 .rodata        0x00000000004a9000      0x1dd main.o

.rdata          0x00000000004aa000      0xd20
 .rdata         0x00000000004aa000      0x3a0 api.o
 .rdata         0x00000000004aa3a0      0x100 ctype.o
                0x00000000004aa3a0                _ctype
 .rdata         0x00000000004aa4a0      0x380 stdio.o
                0x00000000004aa680                hex2ascii_data
 .rdata         0x00000000004aa820      0x4f0 stdlib.o

.data           0x00000000004aad20     0x12e0
                0x00000000004aad20                data = .
                0x00000000004aad20                _data = .
                0x00000000004aad20                __data = .
 *(.data)
 .data          0x00000000004aad20      0x440 crt0.o
 .data          0x00000000004ab160      0x444 main.o
                0x00000000004ab5a0                listening
 .data          0x00000000004ab5a4      0x440 api.o
 .data          0x00000000004ab9e4        0x0 ctype.o
 .data          0x00000000004ab9e4        0x0 stdio.o
 .data          0x00000000004ab9e4        0x0 stdlib.o
 .data          0x00000000004ab9e4        0x0 unistd.o
 .data          0x00000000004ab9e4        0x0 string.o
                0x00000000004ac000                . = ALIGN (0x1000)
 *fill*         0x00000000004ab9e4      0x61c 

.bss            0x00000000004ac000    0x12938
                0x00000000004ac000                bss = .
                0x00000000004ac000                _bss = .
                0x00000000004ac000                __bss = .
 *(.bss)
 .bss           0x00000000004ac000        0x0 crt0.o
 .bss           0x00000000004ac000        0x0 main.o
 .bss           0x00000000004ac000     0x8010 api.o
 .bss           0x00000000004b4010        0x0 ctype.o
 .bss           0x00000000004b4010       0x10 stdio.o
 .bss           0x00000000004b4020     0x8010 stdlib.o
                0x00000000004b4020                environ
 .bss           0x00000000004bc030        0x0 unistd.o
 .bss           0x00000000004bc030       0x10 string.o
                0x00000000004bd000                . = ALIGN (0x1000)
 *fill*         0x00000000004bc040      0xfc0 
 COMMON         0x00000000004bd000      0xc84 crt0.o
                0x00000000004bd000                prompt
                0x00000000004bd400                prompt_err
                0x00000000004bd800                Streams
                0x00000000004bd880                prompt_out
                0x00000000004bdc80                taskmanTest1
 *fill*         0x00000000004bdc84       0x1c 
 COMMON         0x00000000004bdca0      0x228 main.o
                0x00000000004bdca0                taskmanagerBufferPos
                0x00000000004bdcc0                taskmanagerBuffer
                0x00000000004bdec0                taskmanagerStatus
                0x00000000004bdec4                taskmanagerError
 COMMON         0x00000000004bdec8      0x550 api.o
                0x00000000004bdec8                ClientAreaInfo
                0x00000000004bded8                BufferInfo
                0x00000000004bdee8                messagebox_button2
                0x00000000004bdef8                heap_end
                0x00000000004bdf08                rect
                0x00000000004bdf18                g_available_heap
                0x00000000004bdf28                heap_start
                0x00000000004bdf38                heapCount
                0x00000000004bdf48                HEAP_START
                0x00000000004bdf58                CurrentWindow
                0x00000000004bdf68                g_heap_pointer
                0x00000000004bdf78                heapList
                0x00000000004be378                current_semaphore
                0x00000000004be388                HEAP_SIZE
                0x00000000004be398                dialogbox_button1
                0x00000000004be3a8                libcHeap
                0x00000000004be3b8                messagebox_button1
                0x00000000004be3c8                Heap
                0x00000000004be3d8                dialogbox_button2
                0x00000000004be3e8                CursorInfo
                0x00000000004be3f8                ApplicationInfo
                0x00000000004be408                HEAP_END
 COMMON         0x00000000004be418       0xc0 stdio.o
                0x00000000004be418                stderr
                0x00000000004be428                prompt_pos
                0x00000000004be438                g_using_gui
                0x00000000004be448                stdin
                0x00000000004be458                prompt_max
                0x00000000004be468                g_columns
                0x00000000004be478                stdout
                0x00000000004be488                g_rows
                0x00000000004be498                g_cursor_y
                0x00000000004be4a8                prompt_status
                0x00000000004be4b8                g_char_attrib
                0x00000000004be4c8                g_cursor_x
 COMMON         0x00000000004be4d8      0x460 stdlib.o
                0x00000000004be4d8                current_mmblock
                0x00000000004be4e8                mm_prev_pointer
                0x00000000004be4f8                randseed
                0x00000000004be508                last_size
                0x00000000004be518                last_valid
                0x00000000004be528                mmblockList
                0x00000000004be928                mmblockCount
                0x00000000004be938                end = .
                0x00000000004be938                _end = .
                0x00000000004be938                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD unistd.o
LOAD string.o
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
