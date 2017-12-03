
Allocating common symbols
Common symbol       size              file

prompt              0x100             crt0.o
taskmanagerBufferPos
                    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              crt0.o
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
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
taskmanagerStatus   0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
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

.text           0x004a1000     0x3000
                0x004a1000                code = .
                0x004a1000                _code = .
                0x004a1000                __code = .
 *(.head_x86)
 .head_x86      0x004a1000       0x18 head.o
                0x004a1000                taskmanager_entry_point
 *(.text)
 .text          0x004a1018       0x30 crt0.o
                0x004a1018                crt0
 .text          0x004a1048      0x510 main.o
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
 .text          0x004a1558     0x1270 api.o
                0x004a22a7                APIShowCurrentProcessInfo
                0x004a1af8                system11
                0x004a1b9d                refresh_buffer
                0x004a2189                APISetFocus
                0x004a1b5b                system14
                0x004a1e82                apiInitBackground
                0x004a20c1                APICreateWindow
                0x004a27ab                apiBeginPaint
                0x004a1e87                MessageBox
                0x004a2325                APIreplace_window
                0x004a1b3a                system13
                0x004a2662                apiDown
                0x004a26fa                enterCriticalSection
                0x004a2638                apiFOpen
                0x004a19ae                system1
                0x004a1a32                system5
                0x004a24d9                api_refresh_screen
                0x004a2565                apiGetCursorY
                0x004a1e2d                carrega_bitmap_16x16
                0x004a2753                exitCriticalSection
                0x004a1558                system_call
                0x004a26ae                apiUp
                0x004a1580                apiSystem
                0x004a1b7c                system15
                0x004a2239                APISetActiveWindow
                0x004a25bd                apiSetClientAreaRect
                0x004a22fc                APIredraw_window
                0x004a260f                apiCreateThread
                0x004a1dc9                SetNextWindowProcedure
                0x004a2539                apiGetCursorX
                0x004a1d99                chama_procedimento
                0x004a1eb0                call_kernel
                0x004a2105                APIRegisterWindow
                0x004a244f                api_strncmp
                0x004a2377                APIminimize_window
                0x004a19cf                system2
                0x004a19f0                system3
                0x004a25e6                apiCreateProcess
                0x004a21cb                APIGetFocus
                0x004a1a74                system7
                0x004a1a53                system6
                0x004a2147                APICloseWindow
                0x004a277f                initializeCriticalSection
                0x004a1ad7                system10
                0x004a1df9                set_cursor
                0x004a234e                APImaximize_window
                0x004a24ad                refresh_screen
                0x004a2030                call_gui
                0x004a1ab6                system9
                0x004a22d3                APIresize_window
                0x004a27b5                apiEndPaint
                0x004a1e28                put_char
                0x004a1d34                print_string
                0x004a2591                apiGetClientAreaRect
                0x004a1d6a                edit_box
                0x004a241e                kill
                0x004a24e3                apiReboot
                0x004a1e56                apiShutDown
                0x004a23f5                exit
                0x004a23a0                APIget_foregroung_window
                0x004a1a11                system4
                0x004a250f                apiSetCursor
                0x004a1b19                system12
                0x004a1d39                vsync
                0x004a1a95                system8
                0x004a227b                APIGetActiveWindow
                0x004a2423                dead_thread_collector
                0x004a21f7                APIKillFocus
                0x004a23cc                APIset_foregroung_window
 .text          0x004a27c8      0xbe0 stdio.o
                0x004a2f87                putchar
                0x004a2f43                sprintf
                0x004a315d                input
                0x004a282d                scroll
                0x004a3153                printf_main
                0x004a2f9d                outbyte
                0x004a29d7                app_print
                0x004a323f                stdio_system_call
                0x004a27df                fopen
                0x004a3267                stdioInitialize
                0x004a27c8                fclose
                0x004a3120                _outbyte
                0x004a2f28                printf
                0x004a296b                app_clear
 .text          0x004a33a8      0x960 stdlib.o
                0x004a3663                FreeHeap
                0x004a33a8                rtGetHeapStart
                0x004a38aa                free
                0x004a384c                rand
                0x004a37c3                stdlibInitMM
                0x004a366d                heapInit
                0x004a33bc                rtGetHeapPointer
                0x004a33c6                rtGetAvailableHeap
                0x004a3823                libcInitRT
                0x004a33d0                heapSetLibcHeap
                0x004a3869                malloc
                0x004a3650                AllocateHeapEx
                0x004a3477                AllocateHeap
                0x004a3ca1                stdlib_strncmp
                0x004a33b2                rtGetHeapEnd
                0x004a38af                system
 .text          0x004a3d08      0x270 string.o
                0x004a3ed2                strcat
                0x004a3d08                strcmp
                0x004a3f29                bzero
                0x004a3e65                memcpy
                0x004a3e3c                memoryZeroMemory
                0x004a3f02                bcopy
                0x004a3ea2                strcpy
                0x004a3dc1                str_cmp
                0x004a3d63                strncmp
                0x004a3f44                strlen
                0x004a4000                . = ALIGN (0x1000)
 *fill*         0x004a3f78       0x88 00

.rdata          0x004a4000      0x8b0
 .rdata         0x004a4000      0x420 stdlib.o
 .rdata         0x004a4420       0x40 stdio.o
 .rdata         0x004a4460      0x310 api.o
 .rdata         0x004a4770      0x140 main.o

.data           0x004a48b0      0x750
                0x004a48b0                data = .
                0x004a48b0                _data = .
                0x004a48b0                __data = .
 *(.data)
 .data          0x004a48b0        0x0 crt0.o
 .data          0x004a48b0        0x0 main.o
 .data          0x004a48b0        0x0 api.o
 .data          0x004a48b0        0x0 stdio.o
 .data          0x004a48b0       0x10 stdlib.o
 .data          0x004a48c0        0x0 string.o
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a48c0      0x740 00

.bss            0x004a5000     0x9fb0
                0x004a5000                bss = .
                0x004a5000                _bss = .
                0x004a5000                __bss = .
 *(.bss)
 .bss           0x004a5000        0x0 crt0.o
 .bss           0x004a5000        0x0 main.o
 .bss           0x004a5000       0x30 api.o
 .bss           0x004a5030       0x10 stdio.o
 .bss           0x004a5040     0x8000 stdlib.o
 .bss           0x004ad040        0x0 string.o
                0x004ae000                . = ALIGN (0x1000)
 *fill*         0x004ad040      0xfc0 00
 COMMON         0x004ae000      0x410 crt0.o
                0x004ae000                prompt
                0x004ae100                _io_table
                0x004ae150                stderr
                0x004ae160                prompt_pos
                0x004ae170                g_using_gui
                0x004ae180                stdin
                0x004ae190                prompt_max
                0x004ae1a0                prompt_err
                0x004ae2a0                g_columns
                0x004ae2b0                stdout
                0x004ae2c0                g_rows
                0x004ae2d0                prompt_out
                0x004ae3d0                g_cursor_y
                0x004ae3e0                prompt_status
                0x004ae3f0                g_char_attrib
                0x004ae400                g_cursor_x
 COMMON         0x004ae410      0x2b0 main.o
                0x004ae410                taskmanagerBufferPos
                0x004ae420                ClientAreaInfo
                0x004ae430                BufferInfo
                0x004ae440                taskmanagerBuffer
                0x004ae640                rect
                0x004ae650                CurrentWindow
                0x004ae660                current_semaphore
                0x004ae670                taskmanagerStatus
                0x004ae680                CursorInfo
                0x004ae690                taskmanTest1
                0x004ae6a0                taskmanagerError
                0x004ae6b0                ApplicationInfo
 COMMON         0x004ae6c0      0x8f0 stdlib.o
                0x004ae6c0                current_mmblock
                0x004ae6d0                mm_prev_pointer
                0x004ae6e0                heap_end
                0x004ae6f0                g_available_heap
                0x004ae700                heap_start
                0x004ae710                heapCount
                0x004ae720                HEAP_START
                0x004ae730                g_heap_pointer
                0x004ae740                heapList
                0x004aeb40                HEAP_SIZE
                0x004aeb50                last_size
                0x004aeb60                last_valid
                0x004aeb70                mmblockList
                0x004aef70                libcHeap
                0x004aef80                Heap
                0x004aef90                mmblockCount
                0x004aefa0                HEAP_END
                0x004aefb0                end = .
                0x004aefb0                _end = .
                0x004aefb0                __end = .
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
