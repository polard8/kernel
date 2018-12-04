
Allocating common symbols
Common symbol       size              file

prompt              0x400             crt0.o
taskmanagerBufferPos
                    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              crt0.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
taskmanagerBuffer   0x200             main.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              crt0.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
taskmanagerStatus   0x10              main.o
Streams             0x80              crt0.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x400             crt0.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
taskmanTest1        0x10              main.o
taskmanagerError    0x10              main.o
g_char_attrib       0x10              crt0.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              crt0.o
HEAP_END            0x10              stdlib.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x00000000         0xffffffff

Linker script and memory map

                0x00400000                __image_base__ = 0x400000
                0x00000000                __dll__ = 0x0
                0x00400000                ___ImageBase = 0x400000
                0x00001000                __section_alignment__ = 0x1000
                0x00000200                __file_alignment__ = 0x200
                0x00000004                __major_os_version__ = 0x4
                0x00000000                __minor_os_version__ = 0x0
                0x00000001                __major_image_version__ = 0x1
                0x00000000                __minor_image_version__ = 0x0
                0x00000004                __major_subsystem_version__ = 0x4
                0x00000000                __minor_subsystem_version__ = 0x0
                0x00000003                __subsystem__ = 0x3
                0x00200000                __size_of_stack_reserve__ = 0x200000
                0x00001000                __size_of_stack_commit__ = 0x1000
                0x00100000                __size_of_heap_reserve__ = 0x100000
                0x00001000                __size_of_heap_commit__ = 0x1000
                0x00000000                __loader_flags__ = 0x0

.text           0x004a1000     0x4000
                0x004a1000                code = .
                0x004a1000                _code = .
                0x004a1000                __code = .
 *(.head_x86)
 .head_x86      0x004a1000       0x18 head.o
                0x004a1000                taskmanager_entry_point
 *(.text)
 .text          0x004a1018       0x40 crt0.o
                0x004a1018                crt0
 .text          0x004a1058      0x5d0 main.o
                0x004a1108                tmProc
                0x004a1058                tmSleep
                0x004a109f                tmCreateTaskBar
                0x004a1184                tmUpdateStatus
                0x004a122f                tmSetCursor
                0x004a11d5                tmDrawBar
                0x004a126f                DoProgress
                0x004a13a4                progress_bar_test
                0x004a1244                tmstrlen
                0x004a13d9                appMain
                0x004a1076                tmProbeProcessList
                0x004a13b1                tmInit
                0x004a134d                DoSome
 .text          0x004a1628     0x19a0 api.o
                0x004a23dd                APIShowCurrentProcessInfo
                0x004a2bca                api_getchar
                0x004a1bca                system11
                0x004a1c6f                refresh_buffer
                0x004a22bf                APISetFocus
                0x004a1c2d                system14
                0x004a1f54                apiInitBackground
                0x004a2193                APICreateWindow
                0x004a2985                apiBeginPaint
                0x004a1f59                MessageBox
                0x004a245b                APIreplace_window
                0x004a29cc                apiGetSystemMetrics
                0x004a1c0c                system13
                0x004a283c                apiDown
                0x004a2554                apiExit
                0x004a28d4                enterCriticalSection
                0x004a2b11                gramadocore_init_execve
                0x004a27c2                apiFOpen
                0x004a1a80                system1
                0x004a1b04                system5
                0x004a263a                api_refresh_screen
                0x004a2b51                apiDialog
                0x004a26c6                apiGetCursorY
                0x004a1eff                carrega_bitmap_16x16
                0x004a292d                exitCriticalSection
                0x004a1628                system_call
                0x004a2888                apiUp
                0x004a1650                apiSystem
                0x004a2ae5                api_get_window_with_text_input
                0x004a1c4e                system15
                0x004a236f                APISetActiveWindow
                0x004a271e                apiSetClientAreaRect
                0x004a2432                APIredraw_window
                0x004a2770                apiCreateThread
                0x004a1e9b                SetNextWindowProcedure
                0x004a269a                apiGetCursorX
                0x004a1e6b                chama_procedimento
                0x004a1f82                call_kernel
                0x004a223b                APIRegisterWindow
                0x004a25b0                api_strncmp
                0x004a24ad                APIminimize_window
                0x004a1aa1                system2
                0x004a1ac2                system3
                0x004a2a1e                api_get_current_keyboard_responder
                0x004a2747                apiCreateProcess
                0x004a2301                APIGetFocus
                0x004a1b46                system7
                0x004a1b25                system6
                0x004a29c2                apiDefDialog
                0x004a227d                APICloseWindow
                0x004a2959                initializeCriticalSection
                0x004a1ba9                system10
                0x004a1ecb                set_cursor
                0x004a2484                APImaximize_window
                0x004a2b47                execve
                0x004a260e                refresh_screen
                0x004a2bf6                apiDisplayBMP
                0x004a2102                call_gui
                0x004a1b88                system9
                0x004a2b1b                fork
                0x004a29f5                api_set_current_keyboard_responder
                0x004a2409                APIresize_window
                0x004a298f                apiEndPaint
                0x004a1efa                put_char
                0x004a1e06                print_string
                0x004a26f2                apiGetClientAreaRect
                0x004a1e3c                edit_box
                0x004a257f                kill
                0x004a2644                apiReboot
                0x004a1f28                apiShutDown
                0x004a2a4a                api_set_current_mouse_responder
                0x004a24ff                APIget_foregroung_window
                0x004a1ae3                system4
                0x004a27fc                apiSaveFile
                0x004a2670                apiSetCursor
                0x004a1beb                system12
                0x004a1e0b                vsync
                0x004a1b67                system8
                0x004a2a9f                api_set_window_with_text_input
                0x004a23b1                APIGetActiveWindow
                0x004a24d6                APIupdate_window
                0x004a2a73                api_get_current_mouse_responder
                0x004a2584                dead_thread_collector
                0x004a2799                apiStartThread
                0x004a232d                APIKillFocus
                0x004a252b                APIset_foregroung_window
                0x004a2999                apiPutChar
 .text          0x004a2fc8     0x1110 stdio.o
                0x004a390f                putchar
                0x004a2fc8                stdio_fntos
                0x004a38cb                sprintf
                0x004a3fa0                feof
                0x004a407e                fputc
                0x004a3e55                fputs
                0x004a3fde                ferror
                0x004a3afb                input
                0x004a31b5                scroll
                0x004a3af1                printf_main
                0x004a3eca                gets
                0x004a393b                outbyte
                0x004a335f                app_print
                0x004a3d70                fflush
                0x004a3de0                fprintf
                0x004a3bf2                stdio_system_call
                0x004a311d                fopen
                0x004a3c1a                getchar
                0x004a3c4c                stdioInitialize
                0x004a3f3f                fgetc
                0x004a30b7                fclose
                0x004a4004                fseek
                0x004a3abe                _outbyte
                0x004a38b0                printf
                0x004a32f3                app_clear
 .text          0x004a40d8      0x9b0 stdlib.o
                0x004a43bb                FreeHeap
                0x004a4100                rtGetHeapStart
                0x004a4602                free
                0x004a40d8                stdlib_system_call
                0x004a45a4                rand
                0x004a451b                stdlibInitMM
                0x004a43c5                heapInit
                0x004a4114                rtGetHeapPointer
                0x004a411e                rtGetAvailableHeap
                0x004a457b                libcInitRT
                0x004a4128                heapSetLibcHeap
                0x004a45c1                malloc
                0x004a43a8                AllocateHeapEx
                0x004a41cf                AllocateHeap
                0x004a49f9                stdlib_strncmp
                0x004a4a57                exit
                0x004a410a                rtGetHeapEnd
                0x004a4607                system
 .text          0x004a4a88      0x4a0 string.o
                0x004a4cef                strcspn
                0x004a4c52                strcat
                0x004a4a88                strcmp
                0x004a4ca9                bzero
                0x004a4e2f                strtok_r
                0x004a4be5                memcpy
                0x004a4bbc                memoryZeroMemory
                0x004a4c82                bcopy
                0x004a4c22                strcpy
                0x004a4d8f                strspn
                0x004a4f04                strtok
                0x004a4b41                str_cmp
                0x004a4ae3                strncmp
                0x004a4cc4                strlen
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4f28       0xd8 00

.rdata          0x004a5000      0x8f0
 .rdata         0x004a5000      0x430 stdlib.o
 .rdata         0x004a5430       0x40 stdio.o
 .rdata         0x004a5470      0x320 api.o
 .rdata         0x004a5790      0x160 main.o

.data           0x004a58f0     0x1710
                0x004a58f0                data = .
                0x004a58f0                _data = .
                0x004a58f0                __data = .
 *(.data)
 .data          0x004a58f0        0x0 crt0.o
 .data          0x004a58f0      0x460 main.o
                0x004a5d30                listening
 .data          0x004a5d50      0x440 api.o
 .data          0x004a6190        0x0 stdio.o
 .data          0x004a6190       0x10 stdlib.o
 .data          0x004a61a0        0x0 string.o
                0x004a7000                . = ALIGN (0x1000)
 *fill*         0x004a61a0      0xe60 00

.bss            0x004a7000     0xa8e0
                0x004a7000                bss = .
                0x004a7000                _bss = .
                0x004a7000                __bss = .
 *(.bss)
 .bss           0x004a7000        0x0 crt0.o
 .bss           0x004a7000        0x0 main.o
 .bss           0x004a7000       0x40 api.o
 .bss           0x004a7040       0x10 stdio.o
 .bss           0x004a7050     0x8000 stdlib.o
 .bss           0x004af050       0x10 string.o
                0x004b0000                . = ALIGN (0x1000)
 *fill*         0x004af060      0xfa0 00
 COMMON         0x004b0000      0xd40 crt0.o
                0x004b0000                prompt
                0x004b0400                stderr
                0x004b0410                prompt_pos
                0x004b0420                g_using_gui
                0x004b0430                stdin
                0x004b0440                prompt_max
                0x004b0450                prompt_err
                0x004b0850                g_columns
                0x004b0860                stdout
                0x004b0870                Streams
                0x004b08f0                g_rows
                0x004b0900                prompt_out
                0x004b0d00                g_cursor_y
                0x004b0d10                prompt_status
                0x004b0d20                g_char_attrib
                0x004b0d30                g_cursor_x
 COMMON         0x004b0d40      0x2b0 main.o
                0x004b0d40                taskmanagerBufferPos
                0x004b0d50                ClientAreaInfo
                0x004b0d60                BufferInfo
                0x004b0d70                taskmanagerBuffer
                0x004b0f70                rect
                0x004b0f80                CurrentWindow
                0x004b0f90                current_semaphore
                0x004b0fa0                taskmanagerStatus
                0x004b0fb0                CursorInfo
                0x004b0fc0                taskmanTest1
                0x004b0fd0                taskmanagerError
                0x004b0fe0                ApplicationInfo
 COMMON         0x004b0ff0      0x8f0 stdlib.o
                0x004b0ff0                current_mmblock
                0x004b1000                mm_prev_pointer
                0x004b1010                heap_end
                0x004b1020                g_available_heap
                0x004b1030                heap_start
                0x004b1040                heapCount
                0x004b1050                HEAP_START
                0x004b1060                g_heap_pointer
                0x004b1070                heapList
                0x004b1470                HEAP_SIZE
                0x004b1480                last_size
                0x004b1490                last_valid
                0x004b14a0                mmblockList
                0x004b18a0                libcHeap
                0x004b18b0                Heap
                0x004b18c0                mmblockCount
                0x004b18d0                HEAP_END
                0x004b18e0                end = .
                0x004b18e0                _end = .
                0x004b18e0                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(TASKMAN.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
