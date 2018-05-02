
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
 .text          0x00451058     0x2510 main.o
                0x004529f5                shellPrompt
                0x00453321                shellSendMessage
                0x00452bb1                shellTestThreads
                0x004533ff                shellTaskList
                0x00451380                shellProcedure
                0x004523c6                shellShell
                0x00452923                test_operators
                0x004528e2                shellThread
                0x004524cf                shellInit
                0x0045352a                shellShowCurrentPID
                0x0045156a                shellWaitCmd
                0x00452aae                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00452e42                shellInsertCharXY
                0x00452e8c                shellInsertCharPos
                0x00451582                shellCompare
                0x00452a6c                shellClearBuffer
                0x00452cc6                shellRefreshScreen
                0x00452c41                shellClearScreen
                0x004531aa                shellShowSystemInfo
                0x00452ec4                shellInsertNextChar
                0x00452b1c                shellTestLoadFile
                0x00452fbb                move_to
                0x00452ef0                shellInsertCR
                0x004530aa                shellShowMetrics
                0x004532c3                shellASCII
                0x00452d16                shellScroll
                0x00453372                shellUpdateWorkingDiretoryString
                0x00452f2e                shellInsertNullTerminator
                0x00452f0f                shellInsertLF
                0x004533f2                shellUpdateCurrentDirectoryID
                0x00453349                shell_memcpy_bytes
                0x004528b8                shellSetCursor
                0x00452fe0                shellShowInfo
                0x00453218                shellShowWindowInfo
                0x0045290f                shellTree
                0x004528fb                shellHelp
                0x00452f4d                shellTestMBR
 .text          0x00453568      0x5a0 shellui.o
                0x00453954                shellTestDisplayBMP
                0x004536c9                shellCreateEditBox
                0x00453568                shellTopbarProcedure
                0x004539ca                bmpDisplayBMP
                0x00453777                shellCreateTopBar
 .text          0x00453b08     0x1470 api.o
                0x004548bb                APIShowCurrentProcessInfo
                0x004540a8                system11
                0x0045414d                refresh_buffer
                0x0045479d                APISetFocus
                0x0045410b                system14
                0x00454432                apiInitBackground
                0x00454671                APICreateWindow
                0x00454de8                apiBeginPaint
                0x00454437                MessageBox
                0x00454939                APIreplace_window
                0x00454e2f                apiGetSystemMetrics
                0x004540ea                system13
                0x00454c9f                apiDown
                0x00454d37                enterCriticalSection
                0x00454c75                apiFOpen
                0x00453f5e                system1
                0x00453fe2                system5
                0x00454aed                api_refresh_screen
                0x00454b79                apiGetCursorY
                0x004543dd                carrega_bitmap_16x16
                0x00454d90                exitCriticalSection
                0x00453b08                system_call
                0x00454ceb                apiUp
                0x00453b30                apiSystem
                0x00454f48                api_get_window_with_text_input
                0x0045412c                system15
                0x0045484d                APISetActiveWindow
                0x00454bd1                apiSetClientAreaRect
                0x00454910                APIredraw_window
                0x00454c23                apiCreateThread
                0x00454379                SetNextWindowProcedure
                0x00454b4d                apiGetCursorX
                0x00454349                chama_procedimento
                0x00454460                call_kernel
                0x00454719                APIRegisterWindow
                0x00454a63                api_strncmp
                0x0045498b                APIminimize_window
                0x00453f7f                system2
                0x00453fa0                system3
                0x00454e81                api_get_current_keyboard_responder
                0x00454bfa                apiCreateProcess
                0x004547df                APIGetFocus
                0x00454024                system7
                0x00454003                system6
                0x00454e25                apiDefDialog
                0x0045475b                APICloseWindow
                0x00454dbc                initializeCriticalSection
                0x00454087                system10
                0x004543a9                set_cursor
                0x00454962                APImaximize_window
                0x00454ac1                refresh_screen
                0x004545e0                call_gui
                0x00454066                system9
                0x00454e58                api_set_current_keyboard_responder
                0x004548e7                APIresize_window
                0x00454df2                apiEndPaint
                0x004543d8                put_char
                0x004542e4                print_string
                0x00454ba5                apiGetClientAreaRect
                0x0045431a                edit_box
                0x00454a32                kill
                0x00454af7                apiReboot
                0x00454406                apiShutDown
                0x00454ead                api_set_current_mouse_responder
                0x00454a09                exit
                0x004549b4                APIget_foregroung_window
                0x00453fc1                system4
                0x00454b23                apiSetCursor
                0x004540c9                system12
                0x004542e9                vsync
                0x00454045                system8
                0x00454f02                api_set_window_with_text_input
                0x0045488f                APIGetActiveWindow
                0x00454ed6                api_get_current_mouse_responder
                0x00454a37                dead_thread_collector
                0x00454c4c                apiStartThread
                0x0045480b                APIKillFocus
                0x004549e0                APIset_foregroung_window
                0x00454dfc                apiPutChar
 .text          0x00454f78      0xbf0 stdio.o
                0x00455737                putchar
                0x004556f3                sprintf
                0x00455923                input
                0x00454fdd                scroll
                0x00455919                printf_main
                0x00455763                outbyte
                0x00455187                app_print
                0x00455a1a                stdio_system_call
                0x00454f8f                fopen
                0x00455a42                stdioInitialize
                0x00454f78                fclose
                0x004558e6                _outbyte
                0x004556d8                printf
                0x0045511b                app_clear
 .text          0x00455b68      0x960 stdlib.o
                0x00455e23                FreeHeap
                0x00455b68                rtGetHeapStart
                0x0045606a                free
                0x0045600c                rand
                0x00455f83                stdlibInitMM
                0x00455e2d                heapInit
                0x00455b7c                rtGetHeapPointer
                0x00455b86                rtGetAvailableHeap
                0x00455fe3                libcInitRT
                0x00455b90                heapSetLibcHeap
                0x00456029                malloc
                0x00455e10                AllocateHeapEx
                0x00455c37                AllocateHeap
                0x00456461                stdlib_strncmp
                0x00455b72                rtGetHeapEnd
                0x0045606f                system
 .text          0x004564c8      0x4a0 string.o
                0x0045672f                strcspn
                0x00456692                strcat
                0x004564c8                strcmp
                0x004566e9                bzero
                0x0045686f                strtok_r
                0x00456625                memcpy
                0x004565fc                memoryZeroMemory
                0x004566c2                bcopy
                0x00456662                strcpy
                0x004567cf                strspn
                0x00456944                strtok
                0x00456581                str_cmp
                0x00456523                strncmp
                0x00456704                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456968      0x698 00

.rdata          0x00457000     0x1eb0
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x680 shellui.o
 .rdata         0x00457df0     0x10c0 main.o

.data           0x00458eb0      0x150
                0x00458eb0                data = .
                0x00458eb0                _data = .
                0x00458eb0                __data = .
 *(.data)
 .data          0x00458eb0        0x0 crt0.o
 .data          0x00458eb0       0x20 main.o
 .data          0x00458ed0       0x20 shellui.o
 .data          0x00458ef0        0x0 api.o
 .data          0x00458ef0        0x0 stdio.o
 .data          0x00458ef0       0x10 stdlib.o
 .data          0x00458f00        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458f00      0x100 00

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
