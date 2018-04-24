
Allocating common symbols
Common symbol       size              file

ShellMetrics        0x10              main.o
shellStatus         0x10              main.o
prompt              0x100             crt0.o
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
prompt_err          0x100             crt0.o
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
prompt_out          0x100             crt0.o
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
 .text          0x00451058     0x1fc0 main.o
                0x004526e7                shellPrompt
                0x00452fe1                shellSendMessage
                0x00452893                shellTestThreads
                0x00451357                shellProcedure
                0x0045214e                shellShell
                0x00452615                test_operators
                0x004525d4                shellThread
                0x0045221a                shellInit
                0x00451541                shellWaitCmd
                0x00452790                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00452b24                shellInsertCharXY
                0x00452b6e                shellInsertCharPos
                0x00451559                shellCompare
                0x0045274e                shellClearBuffer
                0x004529a8                shellRefreshScreen
                0x00452923                shellClearScreen
                0x00452e6a                shellShowSystemInfo
                0x00452ba6                shellInsertNextChar
                0x004527fe                shellTestLoadFile
                0x00452c7b                move_to
                0x00452bd2                shellInsertCR
                0x00452d6a                shellShowMetrics
                0x00452f83                shellASCII
                0x004529f8                shellScroll
                0x00452c10                shellInsertNullTerminator
                0x00452bf1                shellInsertLF
                0x004525aa                shellSetCursor
                0x00452ca0                shellShowInfo
                0x00452ed8                shellShowWindowInfo
                0x00452601                shellTree
                0x004525ed                shellHelp
                0x00452c2f                shellTestMBR
 .text          0x00453018      0x5f0 shellui.o
                0x0045345c                shellTestDisplayBMP
                0x00453018                shellCreateEditBox
                0x004534d2                bmpDisplayBMP
                0x004530c6                shellCreateTopBar
 .text          0x00453608     0x1470 api.o
                0x004543bb                APIShowCurrentProcessInfo
                0x00453ba8                system11
                0x00453c4d                refresh_buffer
                0x0045429d                APISetFocus
                0x00453c0b                system14
                0x00453f32                apiInitBackground
                0x00454171                APICreateWindow
                0x004548e8                apiBeginPaint
                0x00453f37                MessageBox
                0x00454439                APIreplace_window
                0x0045492f                apiGetSystemMetrics
                0x00453bea                system13
                0x0045479f                apiDown
                0x00454837                enterCriticalSection
                0x00454775                apiFOpen
                0x00453a5e                system1
                0x00453ae2                system5
                0x004545ed                api_refresh_screen
                0x00454679                apiGetCursorY
                0x00453edd                carrega_bitmap_16x16
                0x00454890                exitCriticalSection
                0x00453608                system_call
                0x004547eb                apiUp
                0x00453630                apiSystem
                0x00454a48                api_get_window_with_text_input
                0x00453c2c                system15
                0x0045434d                APISetActiveWindow
                0x004546d1                apiSetClientAreaRect
                0x00454410                APIredraw_window
                0x00454723                apiCreateThread
                0x00453e79                SetNextWindowProcedure
                0x0045464d                apiGetCursorX
                0x00453e49                chama_procedimento
                0x00453f60                call_kernel
                0x00454219                APIRegisterWindow
                0x00454563                api_strncmp
                0x0045448b                APIminimize_window
                0x00453a7f                system2
                0x00453aa0                system3
                0x00454981                api_get_current_keyboard_responder
                0x004546fa                apiCreateProcess
                0x004542df                APIGetFocus
                0x00453b24                system7
                0x00453b03                system6
                0x00454925                apiDefDialog
                0x0045425b                APICloseWindow
                0x004548bc                initializeCriticalSection
                0x00453b87                system10
                0x00453ea9                set_cursor
                0x00454462                APImaximize_window
                0x004545c1                refresh_screen
                0x004540e0                call_gui
                0x00453b66                system9
                0x00454958                api_set_current_keyboard_responder
                0x004543e7                APIresize_window
                0x004548f2                apiEndPaint
                0x00453ed8                put_char
                0x00453de4                print_string
                0x004546a5                apiGetClientAreaRect
                0x00453e1a                edit_box
                0x00454532                kill
                0x004545f7                apiReboot
                0x00453f06                apiShutDown
                0x004549ad                api_set_current_mouse_responder
                0x00454509                exit
                0x004544b4                APIget_foregroung_window
                0x00453ac1                system4
                0x00454623                apiSetCursor
                0x00453bc9                system12
                0x00453de9                vsync
                0x00453b45                system8
                0x00454a02                api_set_window_with_text_input
                0x0045438f                APIGetActiveWindow
                0x004549d6                api_get_current_mouse_responder
                0x00454537                dead_thread_collector
                0x0045474c                apiStartThread
                0x0045430b                APIKillFocus
                0x004544e0                APIset_foregroung_window
                0x004548fc                apiPutChar
 .text          0x00454a78      0xbf0 stdio.o
                0x00455237                putchar
                0x004551f3                sprintf
                0x00455423                input
                0x00454add                scroll
                0x00455419                printf_main
                0x00455263                outbyte
                0x00454c87                app_print
                0x0045551a                stdio_system_call
                0x00454a8f                fopen
                0x00455542                stdioInitialize
                0x00454a78                fclose
                0x004553e6                _outbyte
                0x004551d8                printf
                0x00454c1b                app_clear
 .text          0x00455668      0x960 stdlib.o
                0x00455923                FreeHeap
                0x00455668                rtGetHeapStart
                0x00455b6a                free
                0x00455b0c                rand
                0x00455a83                stdlibInitMM
                0x0045592d                heapInit
                0x0045567c                rtGetHeapPointer
                0x00455686                rtGetAvailableHeap
                0x00455ae3                libcInitRT
                0x00455690                heapSetLibcHeap
                0x00455b29                malloc
                0x00455910                AllocateHeapEx
                0x00455737                AllocateHeap
                0x00455f61                stdlib_strncmp
                0x00455672                rtGetHeapEnd
                0x00455b6f                system
 .text          0x00455fc8      0x4a0 string.o
                0x0045622f                strcspn
                0x00456192                strcat
                0x00455fc8                strcmp
                0x004561e9                bzero
                0x0045636f                strtok_r
                0x00456125                memcpy
                0x004560fc                memoryZeroMemory
                0x004561c2                bcopy
                0x00456162                strcpy
                0x004562cf                strspn
                0x00456444                strtok
                0x00456081                str_cmp
                0x00456023                strncmp
                0x00456204                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456468      0xb98 00

.rdata          0x00457000     0x18b0
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x340 shellui.o
 .rdata         0x00457ab0      0xe00 main.o

.data           0x004588b0      0x750
                0x004588b0                data = .
                0x004588b0                _data = .
                0x004588b0                __data = .
 *(.data)
 .data          0x004588b0        0x0 crt0.o
 .data          0x004588b0       0x20 main.o
 .data          0x004588d0       0x20 shellui.o
 .data          0x004588f0        0x0 api.o
 .data          0x004588f0        0x0 stdio.o
 .data          0x004588f0       0x10 stdlib.o
 .data          0x00458900        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x00458900      0x700 00

.bss            0x00459000     0xcf70
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
 COMMON         0x00462000      0x410 crt0.o
                0x00462000                prompt
                0x00462100                _io_table
                0x00462150                stderr
                0x00462160                prompt_pos
                0x00462170                g_using_gui
                0x00462180                stdin
                0x00462190                prompt_max
                0x004621a0                prompt_err
                0x004622a0                g_columns
                0x004622b0                stdout
                0x004622c0                g_rows
                0x004622d0                prompt_out
                0x004623d0                g_cursor_y
                0x004623e0                prompt_status
                0x004623f0                g_char_attrib
                0x00462400                g_cursor_x
 COMMON         0x00462410     0x3270 main.o
                0x00462410                ShellMetrics
                0x00462420                shellStatus
                0x00462430                CommandHistory
                0x00462440                shellWindowWidth
                0x00462450                ClientAreaInfo
                0x00462460                BufferInfo
                0x00462470                shellError
                0x00462480                shellWindowHeight
                0x00462490                lineList
                0x00464490                root
                0x004644a0                CurrentCommand
                0x004644b0                shell_info
                0x004644d0                shellScreenBufferMaxColumns
                0x004644e0                shell_window_x
                0x004644f0                i2Window
                0x00464500                rect
                0x00464510                backgroung_color
                0x00464520                shellMaxRows
                0x00464530                screenbufferList
                0x00464550                foregroung_color
                0x00464560                pwd
                0x00464570                CurrentWindow
                0x00464580                topbar_scrollbarWindow
                0x00464590                current_semaphore
                0x004645a0                ShellHook
                0x004645b0                topbar_checkboxWindow
                0x004645c0                shellScreenBufferMaxRows
                0x004645d0                shellScreenWidth
                0x004645e0                screen_buffer_pos
                0x004645f0                shellScreenHeight
                0x00464600                editboxWindow
                0x00464610                username
                0x00464620                screen_buffer_x
                0x00464630                screen_buffer
                0x004655e0                shell_window_y
                0x004655f0                terminal_rect
                0x00465600                password
                0x00465610                CursorInfo
                0x00465620                shellMaxColumns
                0x00465630                i1Window
                0x00465640                screen_buffer_y
                0x00465650                topbar_editboxWindow
                0x00465660                topbarWindow
                0x00465670                ApplicationInfo
 COMMON         0x00465680      0x8f0 stdlib.o
                0x00465680                current_mmblock
                0x00465690                mm_prev_pointer
                0x004656a0                heap_end
                0x004656b0                g_available_heap
                0x004656c0                heap_start
                0x004656d0                heapCount
                0x004656e0                HEAP_START
                0x004656f0                g_heap_pointer
                0x00465700                heapList
                0x00465b00                HEAP_SIZE
                0x00465b10                last_size
                0x00465b20                last_valid
                0x00465b30                mmblockList
                0x00465f30                libcHeap
                0x00465f40                Heap
                0x00465f50                mmblockCount
                0x00465f60                HEAP_END
                0x00465f70                end = .
                0x00465f70                _end = .
                0x00465f70                __end = .
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
