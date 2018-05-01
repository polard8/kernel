
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x400             crt0.o
CommandHistory      0x10              main.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
g_current_disk_id   0x10              main.o
BufferInfo          0x10              main.o
_io_table           0x50              crt0.o
shellError          0x10              main.o
stderr              0x10              crt0.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
lineList            0x2000            main.o
root                0x10              main.o
CurrentCommand      0x10              main.o
mm_prev_pointer     0x10              stdlib.o
shell_info          0x20              main.o
shellScreenBufferMaxColumns
                    0x10              main.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
g_current_workingdirectory_id
                    0x10              main.o
shell_window_x      0x10              main.o
i2Window            0x10              main.o
rect                0x10              main.o
backgroung_color    0x10              main.o
g_available_heap    0x10              stdlib.o
shellMaxRows        0x10              main.o
heap_start          0x10              stdlib.o
screenbufferList    0x20              main.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
foregroung_color    0x10              main.o
prompt_max          0x10              crt0.o
pwd                 0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
topbar_scrollbarWindow
                    0x10              main.o
heapList            0x400             stdlib.o
prompt_err          0x400             crt0.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
g_current_volume_id
                    0x10              main.o
ShellHook           0x10              main.o
topbar_checkboxWindow
                    0x10              main.o
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
prompt_out          0x400             crt0.o
editboxWindow       0x10              main.o
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
topbar_editboxWindow
                    0x10              main.o
g_char_attrib       0x10              crt0.o
topbarWindow        0x10              main.o
ApplicationInfo     0x10              main.o
current_workingdiretory_string
                    0x20              main.o
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

.text           0x00451000     0x6000
                0x00451000                code = .
                0x00451000                _code = .
                0x00451000                __code = .
 *(.head_x86)
 .head_x86      0x00451000       0x18 head.o
                0x00451000                shell_entry_point
 *(.text)
 .text          0x00451018       0x40 crt0.o
                0x00451018                crt0
 .text          0x00451058     0x2300 main.o
                0x00452967                shellPrompt
                0x00453271                shellSendMessage
                0x00452b23                shellTestThreads
                0x00451380                shellProcedure
                0x00452338                shellShell
                0x00452895                test_operators
                0x00452854                shellThread
                0x00452441                shellInit
                0x0045156a                shellWaitCmd
                0x00452a20                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00452db4                shellInsertCharXY
                0x00452dfe                shellInsertCharPos
                0x00451582                shellCompare
                0x004529de                shellClearBuffer
                0x00452c38                shellRefreshScreen
                0x00452bb3                shellClearScreen
                0x004530fa                shellShowSystemInfo
                0x00452e36                shellInsertNextChar
                0x00452a8e                shellTestLoadFile
                0x00452f0b                move_to
                0x00452e62                shellInsertCR
                0x00452ffa                shellShowMetrics
                0x00453213                shellASCII
                0x00452c88                shellScroll
                0x004532c2                shellUpdateWorkingDiretoryString
                0x00452ea0                shellInsertNullTerminator
                0x00452e81                shellInsertLF
                0x00453342                shellUpdateCurrentDirectoryID
                0x00453299                shell_memcpy_bytes
                0x0045282a                shellSetCursor
                0x00452f30                shellShowInfo
                0x00453168                shellShowWindowInfo
                0x00452881                shellTree
                0x0045286d                shellHelp
                0x00452ebf                shellTestMBR
 .text          0x00453358      0x5a0 shellui.o
                0x00453744                shellTestDisplayBMP
                0x004534b9                shellCreateEditBox
                0x00453358                shellTopbarProcedure
                0x004537ba                bmpDisplayBMP
                0x00453567                shellCreateTopBar
 .text          0x004538f8     0x1470 api.o
                0x004546ab                APIShowCurrentProcessInfo
                0x00453e98                system11
                0x00453f3d                refresh_buffer
                0x0045458d                APISetFocus
                0x00453efb                system14
                0x00454222                apiInitBackground
                0x00454461                APICreateWindow
                0x00454bd8                apiBeginPaint
                0x00454227                MessageBox
                0x00454729                APIreplace_window
                0x00454c1f                apiGetSystemMetrics
                0x00453eda                system13
                0x00454a8f                apiDown
                0x00454b27                enterCriticalSection
                0x00454a65                apiFOpen
                0x00453d4e                system1
                0x00453dd2                system5
                0x004548dd                api_refresh_screen
                0x00454969                apiGetCursorY
                0x004541cd                carrega_bitmap_16x16
                0x00454b80                exitCriticalSection
                0x004538f8                system_call
                0x00454adb                apiUp
                0x00453920                apiSystem
                0x00454d38                api_get_window_with_text_input
                0x00453f1c                system15
                0x0045463d                APISetActiveWindow
                0x004549c1                apiSetClientAreaRect
                0x00454700                APIredraw_window
                0x00454a13                apiCreateThread
                0x00454169                SetNextWindowProcedure
                0x0045493d                apiGetCursorX
                0x00454139                chama_procedimento
                0x00454250                call_kernel
                0x00454509                APIRegisterWindow
                0x00454853                api_strncmp
                0x0045477b                APIminimize_window
                0x00453d6f                system2
                0x00453d90                system3
                0x00454c71                api_get_current_keyboard_responder
                0x004549ea                apiCreateProcess
                0x004545cf                APIGetFocus
                0x00453e14                system7
                0x00453df3                system6
                0x00454c15                apiDefDialog
                0x0045454b                APICloseWindow
                0x00454bac                initializeCriticalSection
                0x00453e77                system10
                0x00454199                set_cursor
                0x00454752                APImaximize_window
                0x004548b1                refresh_screen
                0x004543d0                call_gui
                0x00453e56                system9
                0x00454c48                api_set_current_keyboard_responder
                0x004546d7                APIresize_window
                0x00454be2                apiEndPaint
                0x004541c8                put_char
                0x004540d4                print_string
                0x00454995                apiGetClientAreaRect
                0x0045410a                edit_box
                0x00454822                kill
                0x004548e7                apiReboot
                0x004541f6                apiShutDown
                0x00454c9d                api_set_current_mouse_responder
                0x004547f9                exit
                0x004547a4                APIget_foregroung_window
                0x00453db1                system4
                0x00454913                apiSetCursor
                0x00453eb9                system12
                0x004540d9                vsync
                0x00453e35                system8
                0x00454cf2                api_set_window_with_text_input
                0x0045467f                APIGetActiveWindow
                0x00454cc6                api_get_current_mouse_responder
                0x00454827                dead_thread_collector
                0x00454a3c                apiStartThread
                0x004545fb                APIKillFocus
                0x004547d0                APIset_foregroung_window
                0x00454bec                apiPutChar
 .text          0x00454d68      0xbf0 stdio.o
                0x00455527                putchar
                0x004554e3                sprintf
                0x00455713                input
                0x00454dcd                scroll
                0x00455709                printf_main
                0x00455553                outbyte
                0x00454f77                app_print
                0x0045580a                stdio_system_call
                0x00454d7f                fopen
                0x00455832                stdioInitialize
                0x00454d68                fclose
                0x004556d6                _outbyte
                0x004554c8                printf
                0x00454f0b                app_clear
 .text          0x00455958      0x960 stdlib.o
                0x00455c13                FreeHeap
                0x00455958                rtGetHeapStart
                0x00455e5a                free
                0x00455dfc                rand
                0x00455d73                stdlibInitMM
                0x00455c1d                heapInit
                0x0045596c                rtGetHeapPointer
                0x00455976                rtGetAvailableHeap
                0x00455dd3                libcInitRT
                0x00455980                heapSetLibcHeap
                0x00455e19                malloc
                0x00455c00                AllocateHeapEx
                0x00455a27                AllocateHeap
                0x00456251                stdlib_strncmp
                0x00455962                rtGetHeapEnd
                0x00455e5f                system
 .text          0x004562b8      0x4a0 string.o
                0x0045651f                strcspn
                0x00456482                strcat
                0x004562b8                strcmp
                0x004564d9                bzero
                0x0045665f                strtok_r
                0x00456415                memcpy
                0x004563ec                memoryZeroMemory
                0x004564b2                bcopy
                0x00456452                strcpy
                0x004565bf                strspn
                0x00456734                strtok
                0x00456371                str_cmp
                0x00456313                strncmp
                0x004564f4                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456758      0x8a8 00

.rdata          0x00457000     0x1e70
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x680 shellui.o
 .rdata         0x00457df0     0x1080 main.o

.data           0x00458e70      0x190
                0x00458e70                data = .
                0x00458e70                _data = .
                0x00458e70                __data = .
 *(.data)
 .data          0x00458e70        0x0 crt0.o
 .data          0x00458e70       0x20 main.o
 .data          0x00458e90       0x20 shellui.o
 .data          0x00458eb0        0x0 api.o
 .data          0x00458eb0        0x0 stdio.o
 .data          0x00458eb0       0x10 stdlib.o
 .data          0x00458ec0        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458ec0      0x140 00

.bss            0x00459000     0xd8c0
                0x00459000                bss = .
                0x00459000                _bss = .
                0x00459000                __bss = .
 *(.bss)
 .bss           0x00459000        0x0 crt0.o
 .bss           0x00459000       0xe0 main.o
                0x00459000                ShellFlag
 .bss           0x004590e0       0xd0 shellui.o
 .bss           0x004591b0       0x30 api.o
 .bss           0x004591e0       0x10 stdio.o
 .bss           0x004591f0     0x8000 stdlib.o
 .bss           0x004611f0       0x10 string.o
                0x00462000                . = ALIGN (0x1000)
 *fill*         0x00461200      0xe00 00
 COMMON         0x00462000      0xd10 crt0.o
                0x00462000                prompt
                0x00462400                _io_table
                0x00462450                stderr
                0x00462460                prompt_pos
                0x00462470                g_using_gui
                0x00462480                stdin
                0x00462490                prompt_max
                0x004624a0                prompt_err
                0x004628a0                g_columns
                0x004628b0                stdout
                0x004628c0                g_rows
                0x004628d0                prompt_out
                0x00462cd0                g_cursor_y
                0x00462ce0                prompt_status
                0x00462cf0                g_char_attrib
                0x00462d00                g_cursor_x
 COMMON         0x00462d10     0x32c0 main.o
                0x00462d10                ShellMetrics
                0x00462d20                shellStatus
                0x00462d30                CommandHistory
                0x00462d40                shellWindowWidth
                0x00462d50                ClientAreaInfo
                0x00462d60                g_current_disk_id
                0x00462d70                BufferInfo
                0x00462d80                shellError
                0x00462d90                shellWindowHeight
                0x00462da0                lineList
                0x00464da0                root
                0x00464db0                CurrentCommand
                0x00464dc0                shell_info
                0x00464de0                shellScreenBufferMaxColumns
                0x00464df0                g_current_workingdirectory_id
                0x00464e00                shell_window_x
                0x00464e10                i2Window
                0x00464e20                rect
                0x00464e30                backgroung_color
                0x00464e40                shellMaxRows
                0x00464e50                screenbufferList
                0x00464e70                foregroung_color
                0x00464e80                pwd
                0x00464e90                CurrentWindow
                0x00464ea0                topbar_scrollbarWindow
                0x00464eb0                current_semaphore
                0x00464ec0                g_current_volume_id
                0x00464ed0                ShellHook
                0x00464ee0                topbar_checkboxWindow
                0x00464ef0                shellScreenBufferMaxRows
                0x00464f00                shellScreenWidth
                0x00464f10                screen_buffer_pos
                0x00464f20                shellScreenHeight
                0x00464f30                editboxWindow
                0x00464f40                username
                0x00464f50                screen_buffer_x
                0x00464f60                screen_buffer
                0x00465f10                shell_window_y
                0x00465f20                terminal_rect
                0x00465f30                password
                0x00465f40                CursorInfo
                0x00465f50                shellMaxColumns
                0x00465f60                i1Window
                0x00465f70                screen_buffer_y
                0x00465f80                topbar_editboxWindow
                0x00465f90                topbarWindow
                0x00465fa0                ApplicationInfo
                0x00465fb0                current_workingdiretory_string
 COMMON         0x00465fd0      0x8f0 stdlib.o
                0x00465fd0                current_mmblock
                0x00465fe0                mm_prev_pointer
                0x00465ff0                heap_end
                0x00466000                g_available_heap
                0x00466010                heap_start
                0x00466020                heapCount
                0x00466030                HEAP_START
                0x00466040                g_heap_pointer
                0x00466050                heapList
                0x00466450                HEAP_SIZE
                0x00466460                last_size
                0x00466470                last_valid
                0x00466480                mmblockList
                0x00466880                libcHeap
                0x00466890                Heap
                0x004668a0                mmblockCount
                0x004668b0                HEAP_END
                0x004668c0                end = .
                0x004668c0                _end = .
                0x004668c0                __end = .
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
