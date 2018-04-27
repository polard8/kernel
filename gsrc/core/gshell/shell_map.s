
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x400             crt0.o
CommandHistory      0x10              main.o
shellWindowWidth    0x10              main.o
ClientAreaInfo      0x10              main.o
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
 .text          0x00451058     0x2150 main.o
                0x00452853                shellPrompt
                0x0045314d                shellSendMessage
                0x004529ff                shellTestThreads
                0x00451357                shellProcedure
                0x004522ba                shellShell
                0x00452781                test_operators
                0x00452740                shellThread
                0x00452386                shellInit
                0x00451541                shellWaitCmd
                0x004528fc                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00452c90                shellInsertCharXY
                0x00452cda                shellInsertCharPos
                0x00451559                shellCompare
                0x004528ba                shellClearBuffer
                0x00452b14                shellRefreshScreen
                0x00452a8f                shellClearScreen
                0x00452fd6                shellShowSystemInfo
                0x00452d12                shellInsertNextChar
                0x0045296a                shellTestLoadFile
                0x00452de7                move_to
                0x00452d3e                shellInsertCR
                0x00452ed6                shellShowMetrics
                0x004530ef                shellASCII
                0x00452b64                shellScroll
                0x00452d7c                shellInsertNullTerminator
                0x00452d5d                shellInsertLF
                0x00453175                shell_memcpy_bytes
                0x00452716                shellSetCursor
                0x00452e0c                shellShowInfo
                0x00453044                shellShowWindowInfo
                0x0045276d                shellTree
                0x00452759                shellHelp
                0x00452d9b                shellTestMBR
 .text          0x004531a8      0x5f0 shellui.o
                0x004535e3                shellTestDisplayBMP
                0x004531a8                shellCreateEditBox
                0x00453659                bmpDisplayBMP
                0x00453256                shellCreateTopBar
 .text          0x00453798     0x1470 api.o
                0x0045454b                APIShowCurrentProcessInfo
                0x00453d38                system11
                0x00453ddd                refresh_buffer
                0x0045442d                APISetFocus
                0x00453d9b                system14
                0x004540c2                apiInitBackground
                0x00454301                APICreateWindow
                0x00454a78                apiBeginPaint
                0x004540c7                MessageBox
                0x004545c9                APIreplace_window
                0x00454abf                apiGetSystemMetrics
                0x00453d7a                system13
                0x0045492f                apiDown
                0x004549c7                enterCriticalSection
                0x00454905                apiFOpen
                0x00453bee                system1
                0x00453c72                system5
                0x0045477d                api_refresh_screen
                0x00454809                apiGetCursorY
                0x0045406d                carrega_bitmap_16x16
                0x00454a20                exitCriticalSection
                0x00453798                system_call
                0x0045497b                apiUp
                0x004537c0                apiSystem
                0x00454bd8                api_get_window_with_text_input
                0x00453dbc                system15
                0x004544dd                APISetActiveWindow
                0x00454861                apiSetClientAreaRect
                0x004545a0                APIredraw_window
                0x004548b3                apiCreateThread
                0x00454009                SetNextWindowProcedure
                0x004547dd                apiGetCursorX
                0x00453fd9                chama_procedimento
                0x004540f0                call_kernel
                0x004543a9                APIRegisterWindow
                0x004546f3                api_strncmp
                0x0045461b                APIminimize_window
                0x00453c0f                system2
                0x00453c30                system3
                0x00454b11                api_get_current_keyboard_responder
                0x0045488a                apiCreateProcess
                0x0045446f                APIGetFocus
                0x00453cb4                system7
                0x00453c93                system6
                0x00454ab5                apiDefDialog
                0x004543eb                APICloseWindow
                0x00454a4c                initializeCriticalSection
                0x00453d17                system10
                0x00454039                set_cursor
                0x004545f2                APImaximize_window
                0x00454751                refresh_screen
                0x00454270                call_gui
                0x00453cf6                system9
                0x00454ae8                api_set_current_keyboard_responder
                0x00454577                APIresize_window
                0x00454a82                apiEndPaint
                0x00454068                put_char
                0x00453f74                print_string
                0x00454835                apiGetClientAreaRect
                0x00453faa                edit_box
                0x004546c2                kill
                0x00454787                apiReboot
                0x00454096                apiShutDown
                0x00454b3d                api_set_current_mouse_responder
                0x00454699                exit
                0x00454644                APIget_foregroung_window
                0x00453c51                system4
                0x004547b3                apiSetCursor
                0x00453d59                system12
                0x00453f79                vsync
                0x00453cd5                system8
                0x00454b92                api_set_window_with_text_input
                0x0045451f                APIGetActiveWindow
                0x00454b66                api_get_current_mouse_responder
                0x004546c7                dead_thread_collector
                0x004548dc                apiStartThread
                0x0045449b                APIKillFocus
                0x00454670                APIset_foregroung_window
                0x00454a8c                apiPutChar
 .text          0x00454c08      0xbf0 stdio.o
                0x004553c7                putchar
                0x00455383                sprintf
                0x004555b3                input
                0x00454c6d                scroll
                0x004555a9                printf_main
                0x004553f3                outbyte
                0x00454e17                app_print
                0x004556aa                stdio_system_call
                0x00454c1f                fopen
                0x004556d2                stdioInitialize
                0x00454c08                fclose
                0x00455576                _outbyte
                0x00455368                printf
                0x00454dab                app_clear
 .text          0x004557f8      0x960 stdlib.o
                0x00455ab3                FreeHeap
                0x004557f8                rtGetHeapStart
                0x00455cfa                free
                0x00455c9c                rand
                0x00455c13                stdlibInitMM
                0x00455abd                heapInit
                0x0045580c                rtGetHeapPointer
                0x00455816                rtGetAvailableHeap
                0x00455c73                libcInitRT
                0x00455820                heapSetLibcHeap
                0x00455cb9                malloc
                0x00455aa0                AllocateHeapEx
                0x004558c7                AllocateHeap
                0x004560f1                stdlib_strncmp
                0x00455802                rtGetHeapEnd
                0x00455cff                system
 .text          0x00456158      0x4a0 string.o
                0x004563bf                strcspn
                0x00456322                strcat
                0x00456158                strcmp
                0x00456379                bzero
                0x004564ff                strtok_r
                0x004562b5                memcpy
                0x0045628c                memoryZeroMemory
                0x00456352                bcopy
                0x004562f2                strcpy
                0x0045645f                strspn
                0x004565d4                strtok
                0x00456211                str_cmp
                0x004561b3                strncmp
                0x00456394                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x004565f8      0xa08 00

.rdata          0x00457000     0x1c70
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x520 shellui.o
 .rdata         0x00457c90      0xfe0 main.o

.data           0x00458c70      0x390
                0x00458c70                data = .
                0x00458c70                _data = .
                0x00458c70                __data = .
 *(.data)
 .data          0x00458c70        0x0 crt0.o
 .data          0x00458c70       0x20 main.o
 .data          0x00458c90       0x20 shellui.o
 .data          0x00458cb0        0x0 api.o
 .data          0x00458cb0        0x0 stdio.o
 .data          0x00458cb0       0x10 stdlib.o
 .data          0x00458cc0        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458cc0      0x340 00

.bss            0x00459000     0xd870
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
 COMMON         0x00462d10     0x3270 main.o
                0x00462d10                ShellMetrics
                0x00462d20                shellStatus
                0x00462d30                CommandHistory
                0x00462d40                shellWindowWidth
                0x00462d50                ClientAreaInfo
                0x00462d60                BufferInfo
                0x00462d70                shellError
                0x00462d80                shellWindowHeight
                0x00462d90                lineList
                0x00464d90                root
                0x00464da0                CurrentCommand
                0x00464db0                shell_info
                0x00464dd0                shellScreenBufferMaxColumns
                0x00464de0                shell_window_x
                0x00464df0                i2Window
                0x00464e00                rect
                0x00464e10                backgroung_color
                0x00464e20                shellMaxRows
                0x00464e30                screenbufferList
                0x00464e50                foregroung_color
                0x00464e60                pwd
                0x00464e70                CurrentWindow
                0x00464e80                topbar_scrollbarWindow
                0x00464e90                current_semaphore
                0x00464ea0                ShellHook
                0x00464eb0                topbar_checkboxWindow
                0x00464ec0                shellScreenBufferMaxRows
                0x00464ed0                shellScreenWidth
                0x00464ee0                screen_buffer_pos
                0x00464ef0                shellScreenHeight
                0x00464f00                editboxWindow
                0x00464f10                username
                0x00464f20                screen_buffer_x
                0x00464f30                screen_buffer
                0x00465ee0                shell_window_y
                0x00465ef0                terminal_rect
                0x00465f00                password
                0x00465f10                CursorInfo
                0x00465f20                shellMaxColumns
                0x00465f30                i1Window
                0x00465f40                screen_buffer_y
                0x00465f50                topbar_editboxWindow
                0x00465f60                topbarWindow
                0x00465f70                ApplicationInfo
 COMMON         0x00465f80      0x8f0 stdlib.o
                0x00465f80                current_mmblock
                0x00465f90                mm_prev_pointer
                0x00465fa0                heap_end
                0x00465fb0                g_available_heap
                0x00465fc0                heap_start
                0x00465fd0                heapCount
                0x00465fe0                HEAP_START
                0x00465ff0                g_heap_pointer
                0x00466000                heapList
                0x00466400                HEAP_SIZE
                0x00466410                last_size
                0x00466420                last_valid
                0x00466430                mmblockList
                0x00466830                libcHeap
                0x00466840                Heap
                0x00466850                mmblockCount
                0x00466860                HEAP_END
                0x00466870                end = .
                0x00466870                _end = .
                0x00466870                __end = .
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
