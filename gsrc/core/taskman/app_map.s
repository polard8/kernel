
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
 .text          0x004a1048      0x390 main.o
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
 .text          0x004a13d8     0x1320 api.o
                0x004a218b                APIShowCurrentProcessInfo
                0x004a1978                system11
                0x004a1a1d                refresh_buffer
                0x004a206d                APISetFocus
                0x004a19db                system14
                0x004a1d02                apiInitBackground
                0x004a1f41                APICreateWindow
                0x004a26b8                apiBeginPaint
                0x004a1d07                MessageBox
                0x004a2209                APIreplace_window
                0x004a19ba                system13
                0x004a256f                apiDown
                0x004a2607                enterCriticalSection
                0x004a2545                apiFOpen
                0x004a182e                system1
                0x004a18b2                system5
                0x004a23bd                api_refresh_screen
                0x004a2449                apiGetCursorY
                0x004a1cad                carrega_bitmap_16x16
                0x004a2660                exitCriticalSection
                0x004a13d8                system_call
                0x004a25bb                apiUp
                0x004a1400                apiSystem
                0x004a19fc                system15
                0x004a211d                APISetActiveWindow
                0x004a24a1                apiSetClientAreaRect
                0x004a21e0                APIredraw_window
                0x004a24f3                apiCreateThread
                0x004a1c49                SetNextWindowProcedure
                0x004a241d                apiGetCursorX
                0x004a1c19                chama_procedimento
                0x004a1d30                call_kernel
                0x004a1fe9                APIRegisterWindow
                0x004a2333                api_strncmp
                0x004a225b                APIminimize_window
                0x004a184f                system2
                0x004a1870                system3
                0x004a24ca                apiCreateProcess
                0x004a20af                APIGetFocus
                0x004a18f4                system7
                0x004a18d3                system6
                0x004a202b                APICloseWindow
                0x004a268c                initializeCriticalSection
                0x004a1957                system10
                0x004a1c79                set_cursor
                0x004a2232                APImaximize_window
                0x004a2391                refresh_screen
                0x004a1eb0                call_gui
                0x004a1936                system9
                0x004a21b7                APIresize_window
                0x004a26c2                apiEndPaint
                0x004a1ca8                put_char
                0x004a1bb4                print_string
                0x004a2475                apiGetClientAreaRect
                0x004a1bea                edit_box
                0x004a2302                kill
                0x004a23c7                apiReboot
                0x004a1cd6                apiShutDown
                0x004a22d9                exit
                0x004a2284                APIget_foregroung_window
                0x004a1891                system4
                0x004a23f3                apiSetCursor
                0x004a1999                system12
                0x004a1bb9                vsync
                0x004a1915                system8
                0x004a215f                APIGetActiveWindow
                0x004a2307                dead_thread_collector
                0x004a251c                apiStartThread
                0x004a20db                APIKillFocus
                0x004a22b0                APIset_foregroung_window
                0x004a26cc                apiPutChar
 .text          0x004a26f8      0xbf0 stdio.o
                0x004a2eb7                putchar
                0x004a2e73                sprintf
                0x004a30a3                input
                0x004a275d                scroll
                0x004a3099                printf_main
                0x004a2ee3                outbyte
                0x004a2907                app_print
                0x004a3185                stdio_system_call
                0x004a270f                fopen
                0x004a31ad                stdioInitialize
                0x004a26f8                fclose
                0x004a3066                _outbyte
                0x004a2e58                printf
                0x004a289b                app_clear
 .text          0x004a32e8      0x960 stdlib.o
                0x004a35a3                FreeHeap
                0x004a32e8                rtGetHeapStart
                0x004a37ea                free
                0x004a378c                rand
                0x004a3703                stdlibInitMM
                0x004a35ad                heapInit
                0x004a32fc                rtGetHeapPointer
                0x004a3306                rtGetAvailableHeap
                0x004a3763                libcInitRT
                0x004a3310                heapSetLibcHeap
                0x004a37a9                malloc
                0x004a3590                AllocateHeapEx
                0x004a33b7                AllocateHeap
                0x004a3be1                stdlib_strncmp
                0x004a32f2                rtGetHeapEnd
                0x004a37ef                system
 .text          0x004a3c48      0x270 string.o
                0x004a3e12                strcat
                0x004a3c48                strcmp
                0x004a3e69                bzero
                0x004a3da5                memcpy
                0x004a3d7c                memoryZeroMemory
                0x004a3e42                bcopy
                0x004a3de2                strcpy
                0x004a3d01                str_cmp
                0x004a3ca3                strncmp
                0x004a3e84                strlen
                0x004a4000                . = ALIGN (0x1000)
 *fill*         0x004a3eb8      0x148 00

.rdata          0x004a4000      0x800
 .rdata         0x004a4000      0x420 stdlib.o
 .rdata         0x004a4420       0x40 stdio.o
 .rdata         0x004a4460      0x310 api.o
 .rdata         0x004a4770       0x90 main.o

.data           0x004a4800      0x800
                0x004a4800                data = .
                0x004a4800                _data = .
                0x004a4800                __data = .
 *(.data)
 .data          0x004a4800        0x0 crt0.o
 .data          0x004a4800        0x0 main.o
 .data          0x004a4800        0x0 api.o
 .data          0x004a4800        0x0 stdio.o
 .data          0x004a4800       0x10 stdlib.o
 .data          0x004a4810        0x0 string.o
                0x004a5000                . = ALIGN (0x1000)
 *fill*         0x004a4810      0x7f0 00

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
