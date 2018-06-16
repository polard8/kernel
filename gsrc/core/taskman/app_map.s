
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
 .text          0x004a1048      0x410 main.o
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
 .text          0x004a1458     0x19a0 api.o
                0x004a220d                APIShowCurrentProcessInfo
                0x004a29fa                api_getchar
                0x004a19fa                system11
                0x004a1a9f                refresh_buffer
                0x004a20ef                APISetFocus
                0x004a1a5d                system14
                0x004a1d84                apiInitBackground
                0x004a1fc3                APICreateWindow
                0x004a27b5                apiBeginPaint
                0x004a1d89                MessageBox
                0x004a228b                APIreplace_window
                0x004a27fc                apiGetSystemMetrics
                0x004a1a3c                system13
                0x004a266c                apiDown
                0x004a2384                apiExit
                0x004a2704                enterCriticalSection
                0x004a2941                gramadocore_init_execve
                0x004a25f2                apiFOpen
                0x004a18b0                system1
                0x004a1934                system5
                0x004a246a                api_refresh_screen
                0x004a2981                apiDialog
                0x004a24f6                apiGetCursorY
                0x004a1d2f                carrega_bitmap_16x16
                0x004a275d                exitCriticalSection
                0x004a1458                system_call
                0x004a26b8                apiUp
                0x004a1480                apiSystem
                0x004a2915                api_get_window_with_text_input
                0x004a1a7e                system15
                0x004a219f                APISetActiveWindow
                0x004a254e                apiSetClientAreaRect
                0x004a2262                APIredraw_window
                0x004a25a0                apiCreateThread
                0x004a1ccb                SetNextWindowProcedure
                0x004a24ca                apiGetCursorX
                0x004a1c9b                chama_procedimento
                0x004a1db2                call_kernel
                0x004a206b                APIRegisterWindow
                0x004a23e0                api_strncmp
                0x004a22dd                APIminimize_window
                0x004a18d1                system2
                0x004a18f2                system3
                0x004a284e                api_get_current_keyboard_responder
                0x004a2577                apiCreateProcess
                0x004a2131                APIGetFocus
                0x004a1976                system7
                0x004a1955                system6
                0x004a27f2                apiDefDialog
                0x004a20ad                APICloseWindow
                0x004a2789                initializeCriticalSection
                0x004a19d9                system10
                0x004a1cfb                set_cursor
                0x004a22b4                APImaximize_window
                0x004a2977                execve
                0x004a243e                refresh_screen
                0x004a2a26                apiDisplayBMP
                0x004a1f32                call_gui
                0x004a19b8                system9
                0x004a294b                fork
                0x004a2825                api_set_current_keyboard_responder
                0x004a2239                APIresize_window
                0x004a27bf                apiEndPaint
                0x004a1d2a                put_char
                0x004a1c36                print_string
                0x004a2522                apiGetClientAreaRect
                0x004a1c6c                edit_box
                0x004a23af                kill
                0x004a2474                apiReboot
                0x004a1d58                apiShutDown
                0x004a287a                api_set_current_mouse_responder
                0x004a232f                APIget_foregroung_window
                0x004a1913                system4
                0x004a262c                apiSaveFile
                0x004a24a0                apiSetCursor
                0x004a1a1b                system12
                0x004a1c3b                vsync
                0x004a1997                system8
                0x004a28cf                api_set_window_with_text_input
                0x004a21e1                APIGetActiveWindow
                0x004a2306                APIupdate_window
                0x004a28a3                api_get_current_mouse_responder
                0x004a23b4                dead_thread_collector
                0x004a25c9                apiStartThread
                0x004a215d                APIKillFocus
                0x004a235b                APIset_foregroung_window
                0x004a27c9                apiPutChar
 .text          0x004a2df8     0x1110 stdio.o
                0x004a373f                putchar
                0x004a2df8                stdio_fntos
                0x004a36fb                sprintf
                0x004a3dd0                feof
                0x004a3eae                fputc
                0x004a3c85                fputs
                0x004a3e0e                ferror
                0x004a392b                input
                0x004a2fe5                scroll
                0x004a3921                printf_main
                0x004a3cfa                gets
                0x004a376b                outbyte
                0x004a318f                app_print
                0x004a3ba0                fflush
                0x004a3c10                fprintf
                0x004a3a22                stdio_system_call
                0x004a2f4d                fopen
                0x004a3a4a                getchar
                0x004a3a7c                stdioInitialize
                0x004a3d6f                fgetc
                0x004a2ee7                fclose
                0x004a3e34                fseek
                0x004a38ee                _outbyte
                0x004a36e0                printf
                0x004a3123                app_clear
 .text          0x004a3f08      0x9b0 stdlib.o
                0x004a41eb                FreeHeap
                0x004a3f30                rtGetHeapStart
                0x004a4432                free
                0x004a3f08                stdlib_system_call
                0x004a43d4                rand
                0x004a434b                stdlibInitMM
                0x004a41f5                heapInit
                0x004a3f44                rtGetHeapPointer
                0x004a3f4e                rtGetAvailableHeap
                0x004a43ab                libcInitRT
                0x004a3f58                heapSetLibcHeap
                0x004a43f1                malloc
                0x004a41d8                AllocateHeapEx
                0x004a3fff                AllocateHeap
                0x004a4829                stdlib_strncmp
                0x004a4887                exit
                0x004a3f3a                rtGetHeapEnd
                0x004a4437                system
 .text          0x004a48b8      0x4a0 string.o
                0x004a4b1f                strcspn
                0x004a4a82                strcat
                0x004a48b8                strcmp
                0x004a4ad9                bzero
                0x004a4c5f                strtok_r
                0x004a4a15                memcpy
                0x004a49ec                memoryZeroMemory
                0x004a4ab2                bcopy
                0x004a4a52                strcpy
                0x004a4bbf                strspn
                0x004a4d34                strtok
                0x004a4971                str_cmp
                0x004a4913                strncmp
                0x004a4af4                strlen
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4d58      0x2a8 00

.rdata          0x004a5000      0x820
 .rdata         0x004a5000      0x430 stdlib.o
 .rdata         0x004a5430       0x40 stdio.o
 .rdata         0x004a5470      0x320 api.o
 .rdata         0x004a5790       0x90 main.o

.data           0x004a5820     0x17e0
                0x004a5820                data = .
                0x004a5820                _data = .
                0x004a5820                __data = .
 *(.data)
 .data          0x004a5820        0x0 crt0.o
 .data          0x004a5820      0x440 main.o
 .data          0x004a5c60      0x440 api.o
 .data          0x004a60a0        0x0 stdio.o
 .data          0x004a60a0       0x10 stdlib.o
 .data          0x004a60b0        0x0 string.o
                0x004a7000                . = ALIGN (0x1000)
 *fill*         0x004a60b0      0xf50 00

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
