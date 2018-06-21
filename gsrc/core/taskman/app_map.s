
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
 .text          0x004a1018       0x30 crt0.o
                0x004a1018                crt0
 .text          0x004a1048      0x600 main.o
                0x004a10f8                tmProc
                0x004a1048                tmSleep
                0x004a108f                tmCreateTaskBar
                0x004a1174                tmUpdateStatus
                0x004a121f                tmSetCursor
                0x004a11c5                tmDrawBar
                0x004a125f                DoProgress
                0x004a1394                progress_bar_test
                0x004a1234                tmstrlen
                0x004a13c9                appMain
                0x004a1066                tmProbeProcessList
                0x004a13a1                tmInit
                0x004a133d                DoSome
 .text          0x004a1648     0x19a0 api.o
                0x004a23fd                APIShowCurrentProcessInfo
                0x004a2bea                api_getchar
                0x004a1bea                system11
                0x004a1c8f                refresh_buffer
                0x004a22df                APISetFocus
                0x004a1c4d                system14
                0x004a1f74                apiInitBackground
                0x004a21b3                APICreateWindow
                0x004a29a5                apiBeginPaint
                0x004a1f79                MessageBox
                0x004a247b                APIreplace_window
                0x004a29ec                apiGetSystemMetrics
                0x004a1c2c                system13
                0x004a285c                apiDown
                0x004a2574                apiExit
                0x004a28f4                enterCriticalSection
                0x004a2b31                gramadocore_init_execve
                0x004a27e2                apiFOpen
                0x004a1aa0                system1
                0x004a1b24                system5
                0x004a265a                api_refresh_screen
                0x004a2b71                apiDialog
                0x004a26e6                apiGetCursorY
                0x004a1f1f                carrega_bitmap_16x16
                0x004a294d                exitCriticalSection
                0x004a1648                system_call
                0x004a28a8                apiUp
                0x004a1670                apiSystem
                0x004a2b05                api_get_window_with_text_input
                0x004a1c6e                system15
                0x004a238f                APISetActiveWindow
                0x004a273e                apiSetClientAreaRect
                0x004a2452                APIredraw_window
                0x004a2790                apiCreateThread
                0x004a1ebb                SetNextWindowProcedure
                0x004a26ba                apiGetCursorX
                0x004a1e8b                chama_procedimento
                0x004a1fa2                call_kernel
                0x004a225b                APIRegisterWindow
                0x004a25d0                api_strncmp
                0x004a24cd                APIminimize_window
                0x004a1ac1                system2
                0x004a1ae2                system3
                0x004a2a3e                api_get_current_keyboard_responder
                0x004a2767                apiCreateProcess
                0x004a2321                APIGetFocus
                0x004a1b66                system7
                0x004a1b45                system6
                0x004a29e2                apiDefDialog
                0x004a229d                APICloseWindow
                0x004a2979                initializeCriticalSection
                0x004a1bc9                system10
                0x004a1eeb                set_cursor
                0x004a24a4                APImaximize_window
                0x004a2b67                execve
                0x004a262e                refresh_screen
                0x004a2c16                apiDisplayBMP
                0x004a2122                call_gui
                0x004a1ba8                system9
                0x004a2b3b                fork
                0x004a2a15                api_set_current_keyboard_responder
                0x004a2429                APIresize_window
                0x004a29af                apiEndPaint
                0x004a1f1a                put_char
                0x004a1e26                print_string
                0x004a2712                apiGetClientAreaRect
                0x004a1e5c                edit_box
                0x004a259f                kill
                0x004a2664                apiReboot
                0x004a1f48                apiShutDown
                0x004a2a6a                api_set_current_mouse_responder
                0x004a251f                APIget_foregroung_window
                0x004a1b03                system4
                0x004a281c                apiSaveFile
                0x004a2690                apiSetCursor
                0x004a1c0b                system12
                0x004a1e2b                vsync
                0x004a1b87                system8
                0x004a2abf                api_set_window_with_text_input
                0x004a23d1                APIGetActiveWindow
                0x004a24f6                APIupdate_window
                0x004a2a93                api_get_current_mouse_responder
                0x004a25a4                dead_thread_collector
                0x004a27b9                apiStartThread
                0x004a234d                APIKillFocus
                0x004a254b                APIset_foregroung_window
                0x004a29b9                apiPutChar
 .text          0x004a2fe8     0x1110 stdio.o
                0x004a392f                putchar
                0x004a2fe8                stdio_fntos
                0x004a38eb                sprintf
                0x004a3fc0                feof
                0x004a409e                fputc
                0x004a3e75                fputs
                0x004a3ffe                ferror
                0x004a3b1b                input
                0x004a31d5                scroll
                0x004a3b11                printf_main
                0x004a3eea                gets
                0x004a395b                outbyte
                0x004a337f                app_print
                0x004a3d90                fflush
                0x004a3e00                fprintf
                0x004a3c12                stdio_system_call
                0x004a313d                fopen
                0x004a3c3a                getchar
                0x004a3c6c                stdioInitialize
                0x004a3f5f                fgetc
                0x004a30d7                fclose
                0x004a4024                fseek
                0x004a3ade                _outbyte
                0x004a38d0                printf
                0x004a3313                app_clear
 .text          0x004a40f8      0x9b0 stdlib.o
                0x004a43db                FreeHeap
                0x004a4120                rtGetHeapStart
                0x004a4622                free
                0x004a40f8                stdlib_system_call
                0x004a45c4                rand
                0x004a453b                stdlibInitMM
                0x004a43e5                heapInit
                0x004a4134                rtGetHeapPointer
                0x004a413e                rtGetAvailableHeap
                0x004a459b                libcInitRT
                0x004a4148                heapSetLibcHeap
                0x004a45e1                malloc
                0x004a43c8                AllocateHeapEx
                0x004a41ef                AllocateHeap
                0x004a4a19                stdlib_strncmp
                0x004a4a77                exit
                0x004a412a                rtGetHeapEnd
                0x004a4627                system
 .text          0x004a4aa8      0x4a0 string.o
                0x004a4d0f                strcspn
                0x004a4c72                strcat
                0x004a4aa8                strcmp
                0x004a4cc9                bzero
                0x004a4e4f                strtok_r
                0x004a4c05                memcpy
                0x004a4bdc                memoryZeroMemory
                0x004a4ca2                bcopy
                0x004a4c42                strcpy
                0x004a4daf                strspn
                0x004a4f24                strtok
                0x004a4b61                str_cmp
                0x004a4b03                strncmp
                0x004a4ce4                strlen
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4f48       0xb8 00

.rdata          0x004a5000      0x910
 .rdata         0x004a5000      0x430 stdlib.o
 .rdata         0x004a5430       0x40 stdio.o
 .rdata         0x004a5470      0x320 api.o
 .rdata         0x004a5790      0x180 main.o

.data           0x004a5910     0x16f0
                0x004a5910                data = .
                0x004a5910                _data = .
                0x004a5910                __data = .
 *(.data)
 .data          0x004a5910        0x0 crt0.o
 .data          0x004a5910      0x460 main.o
                0x004a5d50                listening
 .data          0x004a5d70      0x440 api.o
 .data          0x004a61b0        0x0 stdio.o
 .data          0x004a61b0       0x10 stdlib.o
 .data          0x004a61c0        0x0 string.o
                0x004a7000                . = ALIGN (0x1000)
 *fill*         0x004a61c0      0xe40 00

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
