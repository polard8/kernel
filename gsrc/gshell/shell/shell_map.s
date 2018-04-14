
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              crt0.o
shellError          0x10              main.o
stderr              0x10              crt0.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
root                0x10              main.o
mm_prev_pointer     0x10              stdlib.o
shell_info          0x20              main.o
shellScreenBufferMaxColumns
                    0x10              main.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
shell_window_x      0x10              main.o
i2Window            0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              crt0.o
pwd                 0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x100             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
ShellHook           0x10              main.o
shellScreenBufferMaxRows
                    0x10              main.o
shellScreenWidth    0x10              main.o
screen_buffer_pos   0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
shellScreenHeight   0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x100             crt0.o
username            0x10              main.o
mmblockList         0x400             stdlib.o
screen_buffer_x     0x10              main.o
screen_buffer       0xfb0             main.o
libcHeap            0x10              stdlib.o
shell_window_y      0x10              main.o
g_cursor_y          0x10              crt0.o
Heap                0x10              stdlib.o
terminal_rect       0x10              main.o
password            0x10              main.o
CursorInfo          0x10              main.o
shellMaxColumns     0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
i1Window            0x10              main.o
screen_buffer_y     0x10              main.o
g_char_attrib       0x10              crt0.o
topbarWindow        0x10              main.o
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
 .text          0x00451058     0x1c30 main.o
                0x00452524                shellPrompt
                0x00452662                shellTestThreads
                0x00451300                shellProcedure
                0x00451f65                shellShell
                0x00452452                test_operators
                0x00452411                shellThread
                0x0045204a                shellInit
                0x00451444                shellWaitCmd
                0x00451058                GramadoMain
                0x004528e6                shellInsertCharXY
                0x00452926                shellInsertCharPos
                0x0045145c                shellCompare
                0x0045258b                shellClearBuffer
                0x00452777                shellRefreshScreen
                0x004526f2                shellClearScreen
                0x00452bcd                shellShowSystemInfo
                0x00452954                shellInsertNextChar
                0x004525cd                shellTestLoadFile
                0x004529ea                move_to
                0x00452974                shellInsertCR
                0x00452acd                shellShowMetrics
                0x00452c2f                shellASCII
                0x004527c7                shellScroll
                0x00452998                shellInsertNullTerminator
                0x00452986                shellInsertLF
                0x004523e7                shellSetCursor
                0x00452a0f                shellShowInfo
                0x0045243e                shellTree
                0x0045242a                shellHelp
                0x004529aa                shellTestMBR
 .text          0x00452c88      0x380 shellui.o
                0x00452e5b                shellTestDisplayBMP
                0x00452ed1                bmpDisplayBMP
                0x00452c88                shellCreateTopBar
 .text          0x00453008     0x1470 api.o
                0x00453dbb                APIShowCurrentProcessInfo
                0x004535a8                system11
                0x0045364d                refresh_buffer
                0x00453c9d                APISetFocus
                0x0045360b                system14
                0x00453932                apiInitBackground
                0x00453b71                APICreateWindow
                0x004542e8                apiBeginPaint
                0x00453937                MessageBox
                0x00453e39                APIreplace_window
                0x0045432f                apiGetSystemMetrics
                0x004535ea                system13
                0x0045419f                apiDown
                0x00454237                enterCriticalSection
                0x00454175                apiFOpen
                0x0045345e                system1
                0x004534e2                system5
                0x00453fed                api_refresh_screen
                0x00454079                apiGetCursorY
                0x004538dd                carrega_bitmap_16x16
                0x00454290                exitCriticalSection
                0x00453008                system_call
                0x004541eb                apiUp
                0x00453030                apiSystem
                0x00454448                api_get_window_with_text_input
                0x0045362c                system15
                0x00453d4d                APISetActiveWindow
                0x004540d1                apiSetClientAreaRect
                0x00453e10                APIredraw_window
                0x00454123                apiCreateThread
                0x00453879                SetNextWindowProcedure
                0x0045404d                apiGetCursorX
                0x00453849                chama_procedimento
                0x00453960                call_kernel
                0x00453c19                APIRegisterWindow
                0x00453f63                api_strncmp
                0x00453e8b                APIminimize_window
                0x0045347f                system2
                0x004534a0                system3
                0x00454381                api_get_current_keyboard_responder
                0x004540fa                apiCreateProcess
                0x00453cdf                APIGetFocus
                0x00453524                system7
                0x00453503                system6
                0x00454325                apiDefDialog
                0x00453c5b                APICloseWindow
                0x004542bc                initializeCriticalSection
                0x00453587                system10
                0x004538a9                set_cursor
                0x00453e62                APImaximize_window
                0x00453fc1                refresh_screen
                0x00453ae0                call_gui
                0x00453566                system9
                0x00454358                api_set_current_keyboard_responder
                0x00453de7                APIresize_window
                0x004542f2                apiEndPaint
                0x004538d8                put_char
                0x004537e4                print_string
                0x004540a5                apiGetClientAreaRect
                0x0045381a                edit_box
                0x00453f32                kill
                0x00453ff7                apiReboot
                0x00453906                apiShutDown
                0x004543ad                api_set_current_mouse_responder
                0x00453f09                exit
                0x00453eb4                APIget_foregroung_window
                0x004534c1                system4
                0x00454023                apiSetCursor
                0x004535c9                system12
                0x004537e9                vsync
                0x00453545                system8
                0x00454402                api_set_window_with_text_input
                0x00453d8f                APIGetActiveWindow
                0x004543d6                api_get_current_mouse_responder
                0x00453f37                dead_thread_collector
                0x0045414c                apiStartThread
                0x00453d0b                APIKillFocus
                0x00453ee0                APIset_foregroung_window
                0x004542fc                apiPutChar
 .text          0x00454478      0xc00 stdio.o
                0x00454c37                putchar
                0x00454bf3                sprintf
                0x00454e23                input
                0x004544dd                scroll
                0x00454e19                printf_main
                0x00454c63                outbyte
                0x00454687                app_print
                0x00454f1a                stdio_system_call
                0x0045448f                fopen
                0x00454f42                stdioInitialize
                0x00454478                fclose
                0x00454de6                _outbyte
                0x00454bd8                printf
                0x0045461b                app_clear
 .text          0x00455078      0x960 stdlib.o
                0x00455333                FreeHeap
                0x00455078                rtGetHeapStart
                0x0045557a                free
                0x0045551c                rand
                0x00455493                stdlibInitMM
                0x0045533d                heapInit
                0x0045508c                rtGetHeapPointer
                0x00455096                rtGetAvailableHeap
                0x004554f3                libcInitRT
                0x004550a0                heapSetLibcHeap
                0x00455539                malloc
                0x00455320                AllocateHeapEx
                0x00455147                AllocateHeap
                0x00455971                stdlib_strncmp
                0x00455082                rtGetHeapEnd
                0x0045557f                system
 .text          0x004559d8      0x4a0 string.o
                0x00455c3f                strcspn
                0x00455ba2                strcat
                0x004559d8                strcmp
                0x00455bf9                bzero
                0x00455d7f                strtok_r
                0x00455b35                memcpy
                0x00455b0c                memoryZeroMemory
                0x00455bd2                bcopy
                0x00455b72                strcpy
                0x00455cdf                strspn
                0x00455e54                strtok
                0x00455a91                str_cmp
                0x00455a33                strncmp
                0x00455c14                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455e78      0x188 00

.rdata          0x00456000     0x15c0
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xba0 main.o

.data           0x004575c0      0xa40
                0x004575c0                data = .
                0x004575c0                _data = .
                0x004575c0                __data = .
 *(.data)
 .data          0x004575c0        0x0 crt0.o
 .data          0x004575c0       0x20 main.o
 .data          0x004575e0       0x20 shellui.o
 .data          0x00457600        0x0 api.o
 .data          0x00457600        0x0 stdio.o
 .data          0x00457600       0x10 stdlib.o
 .data          0x00457610        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457610      0x9f0 00

.bss            0x00458000     0xaef0
                0x00458000                bss = .
                0x00458000                _bss = .
                0x00458000                __bss = .
 *(.bss)
 .bss           0x00458000        0x0 crt0.o
 .bss           0x00458000       0xd0 main.o
 .bss           0x004580d0       0xd0 shellui.o
 .bss           0x004581a0       0x30 api.o
 .bss           0x004581d0       0x10 stdio.o
 .bss           0x004581e0     0x8000 stdlib.o
 .bss           0x004601e0       0x10 string.o
                0x00461000                . = ALIGN (0x1000)
 *fill*         0x004601f0      0xe10 00
 COMMON         0x00461000      0x410 crt0.o
                0x00461000                prompt
                0x00461100                _io_table
                0x00461150                stderr
                0x00461160                prompt_pos
                0x00461170                g_using_gui
                0x00461180                stdin
                0x00461190                prompt_max
                0x004611a0                prompt_err
                0x004612a0                g_columns
                0x004612b0                stdout
                0x004612c0                g_rows
                0x004612d0                prompt_out
                0x004613d0                g_cursor_y
                0x004613e0                prompt_status
                0x004613f0                g_char_attrib
                0x00461400                g_cursor_x
 COMMON         0x00461410     0x11f0 main.o
                0x00461410                ShellMetrics
                0x00461420                shellStatus
                0x00461430                shellWindowWidth
                0x00461440                ClientAreaInfo
                0x00461450                BufferInfo
                0x00461460                shellError
                0x00461470                shellWindowHeight
                0x00461480                root
                0x00461490                shell_info
                0x004614b0                shellScreenBufferMaxColumns
                0x004614c0                shell_window_x
                0x004614d0                i2Window
                0x004614e0                rect
                0x004614f0                backgroung_color
                0x00461500                shellMaxRows
                0x00461510                foregroung_color
                0x00461520                pwd
                0x00461530                CurrentWindow
                0x00461540                current_semaphore
                0x00461550                ShellHook
                0x00461560                shellScreenBufferMaxRows
                0x00461570                shellScreenWidth
                0x00461580                screen_buffer_pos
                0x00461590                shellScreenHeight
                0x004615a0                username
                0x004615b0                screen_buffer_x
                0x004615c0                screen_buffer
                0x00462570                shell_window_y
                0x00462580                terminal_rect
                0x00462590                password
                0x004625a0                CursorInfo
                0x004625b0                shellMaxColumns
                0x004625c0                i1Window
                0x004625d0                screen_buffer_y
                0x004625e0                topbarWindow
                0x004625f0                ApplicationInfo
 COMMON         0x00462600      0x8f0 stdlib.o
                0x00462600                current_mmblock
                0x00462610                mm_prev_pointer
                0x00462620                heap_end
                0x00462630                g_available_heap
                0x00462640                heap_start
                0x00462650                heapCount
                0x00462660                HEAP_START
                0x00462670                g_heap_pointer
                0x00462680                heapList
                0x00462a80                HEAP_SIZE
                0x00462a90                last_size
                0x00462aa0                last_valid
                0x00462ab0                mmblockList
                0x00462eb0                libcHeap
                0x00462ec0                Heap
                0x00462ed0                mmblockCount
                0x00462ee0                HEAP_END
                0x00462ef0                end = .
                0x00462ef0                _end = .
                0x00462ef0                __end = .
LOAD head.o
LOAD crt0.o
LOAD main.o
LOAD shellui.o
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
