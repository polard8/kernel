
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
 .text          0x00451058     0x2540 main.o
                0x00452a25                shellPrompt
                0x00453351                shellSendMessage
                0x00452be1                shellTestThreads
                0x0045342f                shellTaskList
                0x00451380                shellProcedure
                0x004523f6                shellShell
                0x00452953                test_operators
                0x00452912                shellThread
                0x004524ff                shellInit
                0x0045355a                shellShowCurrentPID
                0x0045156a                shellWaitCmd
                0x00452ade                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00452e72                shellInsertCharXY
                0x00452ebc                shellInsertCharPos
                0x00451582                shellCompare
                0x00452a9c                shellClearBuffer
                0x00452cf6                shellRefreshScreen
                0x00452c71                shellClearScreen
                0x004531da                shellShowSystemInfo
                0x00452ef4                shellInsertNextChar
                0x00452b4c                shellTestLoadFile
                0x00452feb                move_to
                0x00452f20                shellInsertCR
                0x004530da                shellShowMetrics
                0x004532f3                shellASCII
                0x00452d46                shellScroll
                0x004533a2                shellUpdateWorkingDiretoryString
                0x00452f5e                shellInsertNullTerminator
                0x00452f3f                shellInsertLF
                0x00453422                shellUpdateCurrentDirectoryID
                0x00453379                shell_memcpy_bytes
                0x004528e8                shellSetCursor
                0x00453010                shellShowInfo
                0x00453248                shellShowWindowInfo
                0x0045293f                shellTree
                0x0045292b                shellHelp
                0x00452f7d                shellTestMBR
 .text          0x00453598      0x5a0 shellui.o
                0x00453984                shellTestDisplayBMP
                0x004536f9                shellCreateEditBox
                0x00453598                shellTopbarProcedure
                0x004539fa                bmpDisplayBMP
                0x004537a7                shellCreateTopBar
 .text          0x00453b38     0x1470 api.o
                0x004548eb                APIShowCurrentProcessInfo
                0x004540d8                system11
                0x0045417d                refresh_buffer
                0x004547cd                APISetFocus
                0x0045413b                system14
                0x00454462                apiInitBackground
                0x004546a1                APICreateWindow
                0x00454e18                apiBeginPaint
                0x00454467                MessageBox
                0x00454969                APIreplace_window
                0x00454e5f                apiGetSystemMetrics
                0x0045411a                system13
                0x00454ccf                apiDown
                0x00454d67                enterCriticalSection
                0x00454ca5                apiFOpen
                0x00453f8e                system1
                0x00454012                system5
                0x00454b1d                api_refresh_screen
                0x00454ba9                apiGetCursorY
                0x0045440d                carrega_bitmap_16x16
                0x00454dc0                exitCriticalSection
                0x00453b38                system_call
                0x00454d1b                apiUp
                0x00453b60                apiSystem
                0x00454f78                api_get_window_with_text_input
                0x0045415c                system15
                0x0045487d                APISetActiveWindow
                0x00454c01                apiSetClientAreaRect
                0x00454940                APIredraw_window
                0x00454c53                apiCreateThread
                0x004543a9                SetNextWindowProcedure
                0x00454b7d                apiGetCursorX
                0x00454379                chama_procedimento
                0x00454490                call_kernel
                0x00454749                APIRegisterWindow
                0x00454a93                api_strncmp
                0x004549bb                APIminimize_window
                0x00453faf                system2
                0x00453fd0                system3
                0x00454eb1                api_get_current_keyboard_responder
                0x00454c2a                apiCreateProcess
                0x0045480f                APIGetFocus
                0x00454054                system7
                0x00454033                system6
                0x00454e55                apiDefDialog
                0x0045478b                APICloseWindow
                0x00454dec                initializeCriticalSection
                0x004540b7                system10
                0x004543d9                set_cursor
                0x00454992                APImaximize_window
                0x00454af1                refresh_screen
                0x00454610                call_gui
                0x00454096                system9
                0x00454e88                api_set_current_keyboard_responder
                0x00454917                APIresize_window
                0x00454e22                apiEndPaint
                0x00454408                put_char
                0x00454314                print_string
                0x00454bd5                apiGetClientAreaRect
                0x0045434a                edit_box
                0x00454a62                kill
                0x00454b27                apiReboot
                0x00454436                apiShutDown
                0x00454edd                api_set_current_mouse_responder
                0x00454a39                exit
                0x004549e4                APIget_foregroung_window
                0x00453ff1                system4
                0x00454b53                apiSetCursor
                0x004540f9                system12
                0x00454319                vsync
                0x00454075                system8
                0x00454f32                api_set_window_with_text_input
                0x004548bf                APIGetActiveWindow
                0x00454f06                api_get_current_mouse_responder
                0x00454a67                dead_thread_collector
                0x00454c7c                apiStartThread
                0x0045483b                APIKillFocus
                0x00454a10                APIset_foregroung_window
                0x00454e2c                apiPutChar
 .text          0x00454fa8      0xbf0 stdio.o
                0x00455767                putchar
                0x00455723                sprintf
                0x00455953                input
                0x0045500d                scroll
                0x00455949                printf_main
                0x00455793                outbyte
                0x004551b7                app_print
                0x00455a4a                stdio_system_call
                0x00454fbf                fopen
                0x00455a72                stdioInitialize
                0x00454fa8                fclose
                0x00455916                _outbyte
                0x00455708                printf
                0x0045514b                app_clear
 .text          0x00455b98      0x960 stdlib.o
                0x00455e53                FreeHeap
                0x00455b98                rtGetHeapStart
                0x0045609a                free
                0x0045603c                rand
                0x00455fb3                stdlibInitMM
                0x00455e5d                heapInit
                0x00455bac                rtGetHeapPointer
                0x00455bb6                rtGetAvailableHeap
                0x00456013                libcInitRT
                0x00455bc0                heapSetLibcHeap
                0x00456059                malloc
                0x00455e40                AllocateHeapEx
                0x00455c67                AllocateHeap
                0x00456491                stdlib_strncmp
                0x00455ba2                rtGetHeapEnd
                0x0045609f                system
 .text          0x004564f8      0x4a0 string.o
                0x0045675f                strcspn
                0x004566c2                strcat
                0x004564f8                strcmp
                0x00456719                bzero
                0x0045689f                strtok_r
                0x00456655                memcpy
                0x0045662c                memoryZeroMemory
                0x004566f2                bcopy
                0x00456692                strcpy
                0x004567ff                strspn
                0x00456974                strtok
                0x004565b1                str_cmp
                0x00456553                strncmp
                0x00456734                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456998      0x668 00

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
