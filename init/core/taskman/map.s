
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
taskmanagerBuffer   0x200             main.o
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
taskmanagerStatus   0x4               main.o
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
rect                0x4               crt0.o
g_cursor_y          0x4               crt0.o
taskmanagerBufferPos
                    0x4               main.o
ClientAreaInfo      0x4               crt0.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
current_semaphore   0x4               crt0.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
taskmanTest1        0x4               crt0.o
heapCount           0x4               stdlib.o
HEAP_START          0x4               stdlib.o
taskmanagerError    0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x00000000004a1000     0x6000
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
 .text          0x00000000004a1573     0x1e31 api.o
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
                0x00000000004a20b4                mbProcedure
                0x00000000004a2122                DialogBox
                0x00000000004a249c                dbProcedure
                0x00000000004a250a                call_kernel
                0x00000000004a2685                call_gui
                0x00000000004a2711                APICreateWindow
                0x00000000004a278b                APIRegisterWindow
                0x00000000004a27b8                APICloseWindow
                0x00000000004a27e5                APISetFocus
                0x00000000004a2812                APIGetFocus
                0x00000000004a2827                APIKillFocus
                0x00000000004a2854                APISetActiveWindow
                0x00000000004a2881                APIGetActiveWindow
                0x00000000004a2896                APIShowCurrentProcessInfo
                0x00000000004a28ac                APIresize_window
                0x00000000004a28c6                APIredraw_window
                0x00000000004a28e0                APIreplace_window
                0x00000000004a28fa                APImaximize_window
                0x00000000004a2916                APIminimize_window
                0x00000000004a2932                APIupdate_window
                0x00000000004a294e                APIget_foregroung_window
                0x00000000004a2964                APIset_foregroung_window
                0x00000000004a2980                apiExit
                0x00000000004a299d                kill
                0x00000000004a29a3                dead_thread_collector
                0x00000000004a29b9                api_strncmp
                0x00000000004a2a1c                refresh_screen
                0x00000000004a2a32                api_refresh_screen
                0x00000000004a2a3d                apiReboot
                0x00000000004a2a53                apiSetCursor
                0x00000000004a2a6b                apiGetCursorX
                0x00000000004a2a83                apiGetCursorY
                0x00000000004a2a9b                apiGetClientAreaRect
                0x00000000004a2ab3                apiSetClientAreaRect
                0x00000000004a2ad2                apiCreateProcess
                0x00000000004a2aeb                apiCreateThread
                0x00000000004a2b04                apiStartThread
                0x00000000004a2b20                apiFOpen
                0x00000000004a2b4c                apiSaveFile
                0x00000000004a2b9f                apiDown
                0x00000000004a2bf2                apiUp
                0x00000000004a2c45                enterCriticalSection
                0x00000000004a2c80                exitCriticalSection
                0x00000000004a2c99                initializeCriticalSection
                0x00000000004a2cb2                apiBeginPaint
                0x00000000004a2cbd                apiEndPaint
                0x00000000004a2cc8                apiPutChar
                0x00000000004a2ce4                apiDefDialog
                0x00000000004a2cee                apiGetSystemMetrics
                0x00000000004a2d0c                api_set_current_keyboard_responder
                0x00000000004a2d2b                api_get_current_keyboard_responder
                0x00000000004a2d43                api_set_current_mouse_responder
                0x00000000004a2d62                api_get_current_mouse_responder
                0x00000000004a2d7a                api_set_window_with_text_input
                0x00000000004a2dbc                api_get_window_with_text_input
                0x00000000004a2dd4                gramadocore_init_execve
                0x00000000004a2dde                fork
                0x00000000004a2df3                execve
                0x00000000004a2dfd                apiDialog
                0x00000000004a2e89                api_getchar
                0x00000000004a2ea1                apiDisplayBMP
                0x00000000004a32a8                apiSendMessage
                0x00000000004a32de                apiDrawText
                0x00000000004a331d                apiGetWSScreenWindow
                0x00000000004a3335                apiGetWSMainWindow
                0x00000000004a334d                apiCreateTimer
                0x00000000004a336a                apiGetSysTimeInfo
                0x00000000004a3388                apiShowWindow
 .text          0x00000000004a33a4        0x0 ctype.o
 .text          0x00000000004a33a4     0x275a stdio.o
                0x00000000004a33cf                stdio_atoi
                0x00000000004a3496                stdio_fntos
                0x00000000004a35c0                fclose
                0x00000000004a3626                fopen
                0x00000000004a3758                scroll
                0x00000000004a3826                puts
                0x00000000004a3c02                printf3
                0x00000000004a3c1f                printf_atoi
                0x00000000004a3d0f                printf_i2hex
                0x00000000004a3d71                printf2
                0x00000000004a3ef6                sprintf
                0x00000000004a3f4b                putchar
                0x00000000004a3f6c                outbyte
                0x00000000004a412a                _outbyte
                0x00000000004a4159                input
                0x00000000004a42ad                stdio_system_call
                0x00000000004a42d5                getchar
                0x00000000004a42ed                stdioInitialize
                0x00000000004a44da                fflush
                0x00000000004a456d                fprintf
                0x00000000004a45de                fputs
                0x00000000004a464f                gets
                0x00000000004a46da                ungetc
                0x00000000004a4711                ftell
                0x00000000004a4732                fileno
                0x00000000004a474a                fgetc
                0x00000000004a47b8                feof
                0x00000000004a47ed                ferror
                0x00000000004a4808                fseek
                0x00000000004a4874                fputc
                0x00000000004a48c3                stdioSetCursor
                0x00000000004a48db                stdioGetCursorX
                0x00000000004a48f3                stdioGetCursorY
                0x00000000004a490b                scanf
                0x00000000004a4b4b                kvprintf
                0x00000000004a59b5                printf
                0x00000000004a59df                vfprintf
                0x00000000004a5a54                stdout_printf
                0x00000000004a5a80                stderr_printf
                0x00000000004a5aac                perror
                0x00000000004a5ac3                rewind
 .text          0x00000000004a5afe      0xc2d stdlib.o
                0x00000000004a5afe                stdlib_system_call
                0x00000000004a5b26                rtGetHeapStart
                0x00000000004a5b30                rtGetHeapEnd
                0x00000000004a5b3a                rtGetHeapPointer
                0x00000000004a5b44                rtGetAvailableHeap
                0x00000000004a5b4e                heapSetLibcHeap
                0x00000000004a5c01                AllocateHeap
                0x00000000004a5e11                AllocateHeapEx
                0x00000000004a5e27                FreeHeap
                0x00000000004a5e31                heapInit
                0x00000000004a5fc4                stdlibInitMM
                0x00000000004a6027                libcInitRT
                0x00000000004a6049                rand
                0x00000000004a6066                srand
                0x00000000004a6074                xmalloc
                0x00000000004a60a6                stdlib_die
                0x00000000004a60e8                malloc
                0x00000000004a6124                free
                0x00000000004a612a                system
                0x00000000004a64eb                stdlib_strncmp
                0x00000000004a654f                exit
                0x00000000004a656c                __findenv
                0x00000000004a6637                getenv
                0x00000000004a6664                atoi
 .text          0x00000000004a672b      0x446 string.o
                0x00000000004a672b                strcmp
                0x00000000004a6790                strncmp
                0x00000000004a67f3                memoryZeroMemory
                0x00000000004a681a                memcpy
                0x00000000004a6857                strcpy
                0x00000000004a688b                strcat
                0x00000000004a68ba                bcopy
                0x00000000004a68e6                bzero
                0x00000000004a6906                strlen
                0x00000000004a6934                strcspn
                0x00000000004a69d3                strspn
                0x00000000004a6a72                strtok_r
                0x00000000004a6b59                strtok
 .text          0x00000000004a6b71       0x89 conio.o
                0x00000000004a6b71                putch
                0x00000000004a6b95                cputs
                0x00000000004a6bca                getch
                0x00000000004a6be2                getche
                0x00000000004a7000                . = ALIGN (0x1000)
 *fill*         0x00000000004a6bfa      0x406 

.iplt           0x00000000004a7000        0x0
 .iplt          0x00000000004a7000        0x0 conio.o

.eh_frame       0x00000000004a7000     0x1a18
 .eh_frame      0x00000000004a7000       0x34 crt0.o
 .eh_frame      0x00000000004a7034      0x1dc main.o
                                        0x1f4 (size before relaxing)
 .eh_frame      0x00000000004a7210      0xc6c api.o
                                        0xc84 (size before relaxing)
 .eh_frame      0x00000000004a7e7c      0x658 stdio.o
                                        0x670 (size before relaxing)
 .eh_frame      0x00000000004a84d4      0x304 stdlib.o
                                        0x31c (size before relaxing)
 .eh_frame      0x00000000004a87d8      0x1a0 string.o
                                        0x1b8 (size before relaxing)
 .eh_frame      0x00000000004a8978       0xa0 conio.o
                                         0xb8 (size before relaxing)

.rodata         0x00000000004a8a20      0xe74
 .rodata        0x00000000004a8a20      0x1dd main.o
 *fill*         0x00000000004a8bfd        0x3 
 .rodata        0x00000000004a8c00      0x39d api.o
 *fill*         0x00000000004a8f9d        0x3 
 .rodata        0x00000000004a8fa0      0x100 ctype.o
                0x00000000004a8fa0                _ctype
 .rodata        0x00000000004a90a0      0x374 stdio.o
                0x00000000004a9280                hex2ascii_data
 .rodata        0x00000000004a9414      0x47a stdlib.o
 .rodata        0x00000000004a988e        0x6 conio.o

.note.gnu.property
                0x00000000004a9894       0x1c
 .note.gnu.property
                0x00000000004a9894       0x1c conio.o

.rel.dyn        0x00000000004a98b0        0x0
 .rel.got       0x00000000004a98b0        0x0 conio.o
 .rel.iplt      0x00000000004a98b0        0x0 conio.o
 .rel.text      0x00000000004a98b0        0x0 conio.o

.data           0x00000000004a98c0     0x1740
                0x00000000004a98c0                data = .
                0x00000000004a98c0                _data = .
                0x00000000004a98c0                __data = .
 *(.data)
 .data          0x00000000004a98c0      0x440 crt0.o
 .data          0x00000000004a9d00      0x444 main.o
                0x00000000004aa140                listening
 *fill*         0x00000000004aa144       0x1c 
 .data          0x00000000004aa160      0x440 api.o
 .data          0x00000000004aa5a0        0x0 ctype.o
 .data          0x00000000004aa5a0        0x0 stdio.o
 .data          0x00000000004aa5a0        0x0 stdlib.o
 .data          0x00000000004aa5a0        0x0 string.o
 .data          0x00000000004aa5a0        0x0 conio.o
                0x00000000004ab000                . = ALIGN (0x1000)
 *fill*         0x00000000004aa5a0      0xa60 

.got            0x00000000004ab000        0x0
 .got           0x00000000004ab000        0x0 conio.o

.got.plt        0x00000000004ab000        0x0
 .got.plt       0x00000000004ab000        0x0 conio.o

.igot.plt       0x00000000004ab000        0x0
 .igot.plt      0x00000000004ab000        0x0 conio.o

.bss            0x00000000004ab000     0xa7b8
                0x00000000004ab000                bss = .
                0x00000000004ab000                _bss = .
                0x00000000004ab000                __bss = .
 *(.bss)
 .bss           0x00000000004ab000        0x0 crt0.o
 .bss           0x00000000004ab000        0x0 main.o
 .bss           0x00000000004ab000       0x10 api.o
 .bss           0x00000000004ab010        0x0 ctype.o
 .bss           0x00000000004ab010        0x1 stdio.o
 *fill*         0x00000000004ab011        0xf 
 .bss           0x00000000004ab020     0x8020 stdlib.o
                0x00000000004ab020                environ
 .bss           0x00000000004b3040        0x4 string.o
 .bss           0x00000000004b3044        0x0 conio.o
                0x00000000004b4000                . = ALIGN (0x1000)
 *fill*         0x00000000004b3044      0xfbc 
 COMMON         0x00000000004b4000      0xd18 crt0.o
                0x00000000004b4000                g_cursor_x
                0x00000000004b4004                CurrentWindow
                0x00000000004b4008                stdout
                0x00000000004b400c                g_char_attrib
                0x00000000004b4010                g_rows
                0x00000000004b4020                Streams
                0x00000000004b40a0                g_using_gui
                0x00000000004b40a4                ApplicationInfo
                0x00000000004b40c0                prompt_out
                0x00000000004b44c0                BufferInfo
                0x00000000004b44c4                g_columns
                0x00000000004b44c8                prompt_pos
                0x00000000004b44cc                stdin
                0x00000000004b44d0                prompt_status
                0x00000000004b44e0                prompt_err
                0x00000000004b48e0                CursorInfo
                0x00000000004b48e4                stderr
                0x00000000004b4900                prompt
                0x00000000004b4d00                rect
                0x00000000004b4d04                g_cursor_y
                0x00000000004b4d08                ClientAreaInfo
                0x00000000004b4d0c                current_semaphore
                0x00000000004b4d10                prompt_max
                0x00000000004b4d14                taskmanTest1
 *fill*         0x00000000004b4d18        0x8 
 COMMON         0x00000000004b4d20      0x20c main.o
                0x00000000004b4d20                taskmanagerBuffer
                0x00000000004b4f20                taskmanagerStatus
                0x00000000004b4f24                taskmanagerBufferPos
                0x00000000004b4f28                taskmanagerError
 COMMON         0x00000000004b4f2c       0x10 api.o
                0x00000000004b4f2c                dialogbox_button2
                0x00000000004b4f30                messagebox_button1
                0x00000000004b4f34                dialogbox_button1
                0x00000000004b4f38                messagebox_button2
 *fill*         0x00000000004b4f3c        0x4 
 COMMON         0x00000000004b4f40      0x878 stdlib.o
                0x00000000004b4f40                mm_prev_pointer
                0x00000000004b4f60                mmblockList
                0x00000000004b5360                last_valid
                0x00000000004b5380                heapList
                0x00000000004b5780                libcHeap
                0x00000000004b5784                randseed
                0x00000000004b5788                heap_start
                0x00000000004b578c                g_available_heap
                0x00000000004b5790                g_heap_pointer
                0x00000000004b5794                HEAP_SIZE
                0x00000000004b5798                mmblockCount
                0x00000000004b579c                last_size
                0x00000000004b57a0                heap_end
                0x00000000004b57a4                HEAP_END
                0x00000000004b57a8                Heap
                0x00000000004b57ac                current_mmblock
                0x00000000004b57b0                heapCount
                0x00000000004b57b4                HEAP_START
                0x00000000004b57b8                end = .
                0x00000000004b57b8                _end = .
                0x00000000004b57b8                __end = .
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
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
