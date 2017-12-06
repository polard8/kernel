
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
shellBufferMaxColumns
                    0x10              main.o
shellError          0x10              main.o
shell_buffer_y      0x10              main.o
stderr              0x10              crt0.o
shell_buffer        0x7d0             main.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
shell_window_x      0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              crt0.o
shell_buffer_pos    0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
shellScreenWidth    0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
shellScreenHeight   0x10              main.o
shell_buffer_x      0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
shell_window_y      0x10              main.o
shellBufferMaxRows  0x10              main.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
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

.text           0x00451000     0x5000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x1760 main.o
                0x00451fb2                shellPrompt
                0x004520e9                shellTestThreads
                0x0045253a                shellTestDisplayBMP
                0x00451304                shellProcedure
                0x004519ce                shellShell
                0x00451ee0                test_operators
                0x00451eb3                shellThread
                0x00451ab3                shellInit
                0x0045142b                shellWaitCmd
                0x00451058                GramadoMain
                0x00452345                shellInsertCharXY
                0x00452385                shellInsertCharPos
                0x00451443                shellCompare
                0x00452019                shellClearBuffer
                0x004521d4                shellRefreshScreen
                0x004523b3                shellInsertNextChar
                0x00452054                shellTestLoadFile
                0x004523d3                shellInsertCR
                0x00452224                shellScroll
                0x004523f7                shellInsertNullTerminator
                0x00452409                bmpDisplayBMP
                0x004523e5                shellInsertLF
                0x00452179                shellClearscreen
                0x00451e9e                shellSetCursor
                0x004525f0                shellCreateTopBar
                0x00451ecc                shellHelp
                0x004525b0                shellTestMBR
 .text          0x004527b8     0x1300 api.o
                0x0045356b                APIShowCurrentProcessInfo
                0x00452d58                system11
                0x00452dfd                refresh_buffer
                0x0045344d                APISetFocus
                0x00452dbb                system14
                0x004530e2                apiInitBackground
                0x00453321                APICreateWindow
                0x00453a98                apiBeginPaint
                0x004530e7                MessageBox
                0x004535e9                APIreplace_window
                0x00452d9a                system13
                0x0045394f                apiDown
                0x004539e7                enterCriticalSection
                0x00453925                apiFOpen
                0x00452c0e                system1
                0x00452c92                system5
                0x0045379d                api_refresh_screen
                0x00453829                apiGetCursorY
                0x0045308d                carrega_bitmap_16x16
                0x00453a40                exitCriticalSection
                0x004527b8                system_call
                0x0045399b                apiUp
                0x004527e0                apiSystem
                0x00452ddc                system15
                0x004534fd                APISetActiveWindow
                0x00453881                apiSetClientAreaRect
                0x004535c0                APIredraw_window
                0x004538d3                apiCreateThread
                0x00453029                SetNextWindowProcedure
                0x004537fd                apiGetCursorX
                0x00452ff9                chama_procedimento
                0x00453110                call_kernel
                0x004533c9                APIRegisterWindow
                0x00453713                api_strncmp
                0x0045363b                APIminimize_window
                0x00452c2f                system2
                0x00452c50                system3
                0x004538aa                apiCreateProcess
                0x0045348f                APIGetFocus
                0x00452cd4                system7
                0x00452cb3                system6
                0x0045340b                APICloseWindow
                0x00453a6c                initializeCriticalSection
                0x00452d37                system10
                0x00453059                set_cursor
                0x00453612                APImaximize_window
                0x00453771                refresh_screen
                0x00453290                call_gui
                0x00452d16                system9
                0x00453597                APIresize_window
                0x00453aa2                apiEndPaint
                0x00453088                put_char
                0x00452f94                print_string
                0x00453855                apiGetClientAreaRect
                0x00452fca                edit_box
                0x004536e2                kill
                0x004537a7                apiReboot
                0x004530b6                apiShutDown
                0x004536b9                exit
                0x00453664                APIget_foregroung_window
                0x00452c71                system4
                0x004537d3                apiSetCursor
                0x00452d79                system12
                0x00452f99                vsync
                0x00452cf5                system8
                0x0045353f                APIGetActiveWindow
                0x004536e7                dead_thread_collector
                0x004538fc                apiStartThread
                0x004534bb                APIKillFocus
                0x00453690                APIset_foregroung_window
 .text          0x00453ab8      0xbe0 stdio.o
                0x00454277                putchar
                0x00454233                sprintf
                0x0045444d                input
                0x00453b1d                scroll
                0x00454443                printf_main
                0x0045428d                outbyte
                0x00453cc7                app_print
                0x0045452f                stdio_system_call
                0x00453acf                fopen
                0x00454557                stdioInitialize
                0x00453ab8                fclose
                0x00454410                _outbyte
                0x00454218                printf
                0x00453c5b                app_clear
 .text          0x00454698      0x960 stdlib.o
                0x00454953                FreeHeap
                0x00454698                rtGetHeapStart
                0x00454b9a                free
                0x00454b3c                rand
                0x00454ab3                stdlibInitMM
                0x0045495d                heapInit
                0x004546ac                rtGetHeapPointer
                0x004546b6                rtGetAvailableHeap
                0x00454b13                libcInitRT
                0x004546c0                heapSetLibcHeap
                0x00454b59                malloc
                0x00454940                AllocateHeapEx
                0x00454767                AllocateHeap
                0x00454f91                stdlib_strncmp
                0x004546a2                rtGetHeapEnd
                0x00454b9f                system
 .text          0x00454ff8      0x270 string.o
                0x004551c2                strcat
                0x00454ff8                strcmp
                0x00455219                bzero
                0x00455155                memcpy
                0x0045512c                memoryZeroMemory
                0x004551f2                bcopy
                0x00455192                strcpy
                0x004550b1                str_cmp
                0x00455053                strncmp
                0x00455234                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455268      0xd98 00

.rdata          0x00456000     0x1070
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x40 stdio.o
 .rdata         0x00456460      0x310 api.o
 .rdata         0x00456770      0x900 main.o

.data           0x00457070      0xf90
                0x00457070                data = .
                0x00457070                _data = .
                0x00457070                __data = .
 *(.data)
 .data          0x00457070        0x0 crt0.o
 .data          0x00457070       0x20 main.o
 .data          0x00457090        0x0 api.o
 .data          0x00457090        0x0 stdio.o
 .data          0x00457090       0x10 stdlib.o
 .data          0x004570a0        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x004570a0      0xf60 00

.bss            0x00458000     0xa620
                0x00458000                bss = .
                0x00458000                _bss = .
                0x00458000                __bss = .
 *(.bss)
 .bss           0x00458000        0x0 crt0.o
 .bss           0x00458000       0xd0 main.o
 .bss           0x004580d0       0x30 api.o
 .bss           0x00458100       0x10 stdio.o
 .bss           0x00458110     0x8000 stdlib.o
 .bss           0x00460110        0x0 string.o
                0x00461000                . = ALIGN (0x1000)
 *fill*         0x00460110      0xef0 00
 COMMON         0x00461000      0x3c0 crt0.o
                0x00461000                prompt
                0x00461100                stderr
                0x00461110                prompt_pos
                0x00461120                g_using_gui
                0x00461130                stdin
                0x00461140                prompt_max
                0x00461150                prompt_err
                0x00461250                g_columns
                0x00461260                stdout
                0x00461270                g_rows
                0x00461280                prompt_out
                0x00461380                g_cursor_y
                0x00461390                prompt_status
                0x004613a0                g_char_attrib
                0x004613b0                g_cursor_x
 COMMON         0x004613c0      0x970 main.o
                0x004613c0                ShellMetrics
                0x004613d0                shellStatus
                0x004613e0                shellWindowWidth
                0x004613f0                ClientAreaInfo
                0x00461400                BufferInfo
                0x00461410                shellBufferMaxColumns
                0x00461420                shellError
                0x00461430                shell_buffer_y
                0x00461440                shell_buffer
                0x00461c10                shellWindowHeight
                0x00461c20                shell_window_x
                0x00461c30                rect
                0x00461c40                backgroung_color
                0x00461c50                shellMaxRows
                0x00461c60                foregroung_color
                0x00461c70                shell_buffer_pos
                0x00461c80                CurrentWindow
                0x00461c90                current_semaphore
                0x00461ca0                ShellHook
                0x00461cb0                shellScreenWidth
                0x00461cc0                shellScreenHeight
                0x00461cd0                shell_buffer_x
                0x00461ce0                shell_window_y
                0x00461cf0                shellBufferMaxRows
                0x00461d00                CursorInfo
                0x00461d10                shellMaxColumns
                0x00461d20                ApplicationInfo
 COMMON         0x00461d30      0x8f0 stdlib.o
                0x00461d30                current_mmblock
                0x00461d40                mm_prev_pointer
                0x00461d50                heap_end
                0x00461d60                g_available_heap
                0x00461d70                heap_start
                0x00461d80                heapCount
                0x00461d90                HEAP_START
                0x00461da0                g_heap_pointer
                0x00461db0                heapList
                0x004621b0                HEAP_SIZE
                0x004621c0                last_size
                0x004621d0                last_valid
                0x004621e0                mmblockList
                0x004625e0                libcHeap
                0x004625f0                Heap
                0x00462600                mmblockCount
                0x00462610                HEAP_END
                0x00462620                end = .
                0x00462620                _end = .
                0x00462620                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
