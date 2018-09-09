
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              main.o
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

.text           0x00401000     0x4000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x130 main.o
                0x00401000                app_test
 .text          0x00401130     0x1980 api.o
                0x00401ee5                APIShowCurrentProcessInfo
                0x004026a9                api_getchar
                0x004016d2                system11
                0x00401777                refresh_buffer
                0x00401dc7                APISetFocus
                0x00401735                system14
                0x00401a5c                apiInitBackground
                0x00401c9b                APICreateWindow
                0x00402464                apiBeginPaint
                0x00401a61                MessageBox
                0x00401f63                APIreplace_window
                0x004024ab                apiGetSystemMetrics
                0x00401714                system13
                0x0040231b                apiDown
                0x00402033                apiExit
                0x004023b3                enterCriticalSection
                0x004025f0                gramadocore_init_execve
                0x004022a1                apiFOpen
                0x00401588                system1
                0x0040160c                system5
                0x00402119                api_refresh_screen
                0x00402630                apiDialog
                0x004021a5                apiGetCursorY
                0x00401a07                carrega_bitmap_16x16
                0x0040240c                exitCriticalSection
                0x00401130                system_call
                0x00402367                apiUp
                0x00401158                apiSystem
                0x004025c4                api_get_window_with_text_input
                0x00401756                system15
                0x00401e77                APISetActiveWindow
                0x004021fd                apiSetClientAreaRect
                0x00401f3a                APIredraw_window
                0x0040224f                apiCreateThread
                0x004019a3                SetNextWindowProcedure
                0x00402179                apiGetCursorX
                0x00401973                chama_procedimento
                0x00401a8a                call_kernel
                0x00401d43                APIRegisterWindow
                0x0040208f                api_strncmp
                0x00401fb5                APIminimize_window
                0x004015a9                system2
                0x004015ca                system3
                0x004024fd                api_get_current_keyboard_responder
                0x00402226                apiCreateProcess
                0x00401e09                APIGetFocus
                0x0040164e                system7
                0x0040162d                system6
                0x004024a1                apiDefDialog
                0x00401d85                APICloseWindow
                0x00402438                initializeCriticalSection
                0x004016b1                system10
                0x004019d3                set_cursor
                0x00401f8c                APImaximize_window
                0x00402626                execve
                0x004020ed                refresh_screen
                0x004026d5                apiDisplayBMP
                0x00401c0a                call_gui
                0x00401690                system9
                0x004025fa                fork
                0x004024d4                api_set_current_keyboard_responder
                0x00401f11                APIresize_window
                0x0040246e                apiEndPaint
                0x00401a02                put_char
                0x0040190e                print_string
                0x004021d1                apiGetClientAreaRect
                0x00401944                edit_box
                0x0040205e                kill
                0x00402123                apiReboot
                0x00401a30                apiShutDown
                0x00402529                api_set_current_mouse_responder
                0x00401fde                APIget_foregroung_window
                0x004015eb                system4
                0x004022db                apiSaveFile
                0x0040214f                apiSetCursor
                0x004016f3                system12
                0x00401913                vsync
                0x0040166f                system8
                0x0040257e                api_set_window_with_text_input
                0x00401eb9                APIGetActiveWindow
                0x00402552                api_get_current_mouse_responder
                0x00402063                dead_thread_collector
                0x00402278                apiStartThread
                0x00401e35                APIKillFocus
                0x0040200a                APIset_foregroung_window
                0x00402478                apiPutChar
 .text          0x00402ab0     0x1110 stdio.o
                0x004033f7                putchar
                0x00402ab0                stdio_fntos
                0x004033b3                sprintf
                0x00403a88                feof
                0x00403b66                fputc
                0x0040393d                fputs
                0x00403ac6                ferror
                0x004035e3                input
                0x00402c9d                scroll
                0x004035d9                printf_main
                0x004039b2                gets
                0x00403423                outbyte
                0x00402e47                app_print
                0x00403858                fflush
                0x004038c8                fprintf
                0x004036da                stdio_system_call
                0x00402c05                fopen
                0x00403702                getchar
                0x00403734                stdioInitialize
                0x00403a27                fgetc
                0x00402b9f                fclose
                0x00403aec                fseek
                0x004035a6                _outbyte
                0x00403398                printf
                0x00402ddb                app_clear
 .text          0x00403bc0      0x9b0 stdlib.o
                0x00403ea3                FreeHeap
                0x00403be8                rtGetHeapStart
                0x004040ea                free
                0x00403bc0                stdlib_system_call
                0x0040408c                rand
                0x00404003                stdlibInitMM
                0x00403ead                heapInit
                0x00403bfc                rtGetHeapPointer
                0x00403c06                rtGetAvailableHeap
                0x00404063                libcInitRT
                0x00403c10                heapSetLibcHeap
                0x004040a9                malloc
                0x00403e90                AllocateHeapEx
                0x00403cb7                AllocateHeap
                0x004044e1                stdlib_strncmp
                0x0040453f                exit
                0x00403bf2                rtGetHeapEnd
                0x004040ef                system
 .text          0x00404570      0x4a0 string.o
                0x004047d7                strcspn
                0x0040473a                strcat
                0x00404570                strcmp
                0x00404791                bzero
                0x00404917                strtok_r
                0x004046cd                memcpy
                0x004046a4                memoryZeroMemory
                0x0040476a                bcopy
                0x0040470a                strcpy
                0x00404877                strspn
                0x004049ec                strtok
                0x00404629                str_cmp
                0x004045cb                strncmp
                0x004047ac                strlen
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404a10      0x5f0 00

.rdata          0x00405000      0x7f0
 .rdata         0x00405000      0x430 stdlib.o
 .rdata         0x00405430       0x40 stdio.o
 .rdata         0x00405470      0x320 api.o
 .rdata         0x00405790       0x60 main.o

.data           0x004057f0     0x1810
                0x004057f0                data = .
                0x004057f0                _data = .
                0x004057f0                __data = .
 *(.data)
 .data          0x004057f0      0x440 main.o
 .data          0x00405c30      0x440 api.o
 .data          0x00406070        0x0 stdio.o
 .data          0x00406070       0x10 stdlib.o
 .data          0x00406080        0x0 string.o
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x00406080      0xf80 00

.bss            0x00407000     0xa6a0
                0x00407000                bss = .
                0x00407000                _bss = .
                0x00407000                __bss = .
 *(.bss)
 .bss           0x00407000        0x0 main.o
 .bss           0x00407000       0x40 api.o
 .bss           0x00407040       0x10 stdio.o
 .bss           0x00407050     0x8000 stdlib.o
 .bss           0x0040f050       0x10 string.o
                0x00410000                . = ALIGN (0x1000)
 *fill*         0x0040f060      0xfa0 00
 COMMON         0x00410000      0xdb0 main.o
                0x00410000                prompt
                0x00410400                ClientAreaInfo
                0x00410410                BufferInfo
                0x00410420                stderr
                0x00410430                prompt_pos
                0x00410440                g_using_gui
                0x00410450                stdin
                0x00410460                rect
                0x00410470                prompt_max
                0x00410480                CurrentWindow
                0x00410490                prompt_err
                0x00410890                current_semaphore
                0x004108a0                g_columns
                0x004108b0                stdout
                0x004108c0                Streams
                0x00410940                g_rows
                0x00410950                prompt_out
                0x00410d50                g_cursor_y
                0x00410d60                CursorInfo
                0x00410d70                prompt_status
                0x00410d80                g_char_attrib
                0x00410d90                ApplicationInfo
                0x00410da0                g_cursor_x
 COMMON         0x00410db0      0x8f0 stdlib.o
                0x00410db0                current_mmblock
                0x00410dc0                mm_prev_pointer
                0x00410dd0                heap_end
                0x00410de0                g_available_heap
                0x00410df0                heap_start
                0x00410e00                heapCount
                0x00410e10                HEAP_START
                0x00410e20                g_heap_pointer
                0x00410e30                heapList
                0x00411230                HEAP_SIZE
                0x00411240                last_size
                0x00411250                last_valid
                0x00411260                mmblockList
                0x00411660                libcHeap
                0x00411670                Heap
                0x00411680                mmblockCount
                0x00411690                HEAP_END
                0x004116a0                end = .
                0x004116a0                _end = .
                0x004116a0                __end = .
LOAD main.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(TMETRICS.BIN pe-i386)
