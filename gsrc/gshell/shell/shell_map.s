
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
 .text          0x00451058     0x1f60 main.o
                0x0045268e                shellPrompt
                0x00452f88                shellSendMessage
                0x0045283a                shellTestThreads
                0x00451357                shellProcedure
                0x004520f5                shellShell
                0x004525bc                test_operators
                0x0045257b                shellThread
                0x004521c1                shellInit
                0x004514e8                shellWaitCmd
                0x00452737                shellShowScreenBuffer
                0x00451058                GramadoMain
                0x00452acb                shellInsertCharXY
                0x00452b15                shellInsertCharPos
                0x00451500                shellCompare
                0x004526f5                shellClearBuffer
                0x0045294f                shellRefreshScreen
                0x004528ca                shellClearScreen
                0x00452e11                shellShowSystemInfo
                0x00452b4d                shellInsertNextChar
                0x004527a5                shellTestLoadFile
                0x00452c22                move_to
                0x00452b79                shellInsertCR
                0x00452d11                shellShowMetrics
                0x00452f2a                shellASCII
                0x0045299f                shellScroll
                0x00452bb7                shellInsertNullTerminator
                0x00452b98                shellInsertLF
                0x00452551                shellSetCursor
                0x00452c47                shellShowInfo
                0x00452e7f                shellShowWindowInfo
                0x004525a8                shellTree
                0x00452594                shellHelp
                0x00452bd6                shellTestMBR
 .text          0x00452fb8      0x5f0 shellui.o
                0x004533fc                shellTestDisplayBMP
                0x00452fb8                shellCreateEditBox
                0x00453472                bmpDisplayBMP
                0x00453066                shellCreateTopBar
 .text          0x004535a8     0x1470 api.o
                0x0045435b                APIShowCurrentProcessInfo
                0x00453b48                system11
                0x00453bed                refresh_buffer
                0x0045423d                APISetFocus
                0x00453bab                system14
                0x00453ed2                apiInitBackground
                0x00454111                APICreateWindow
                0x00454888                apiBeginPaint
                0x00453ed7                MessageBox
                0x004543d9                APIreplace_window
                0x004548cf                apiGetSystemMetrics
                0x00453b8a                system13
                0x0045473f                apiDown
                0x004547d7                enterCriticalSection
                0x00454715                apiFOpen
                0x004539fe                system1
                0x00453a82                system5
                0x0045458d                api_refresh_screen
                0x00454619                apiGetCursorY
                0x00453e7d                carrega_bitmap_16x16
                0x00454830                exitCriticalSection
                0x004535a8                system_call
                0x0045478b                apiUp
                0x004535d0                apiSystem
                0x004549e8                api_get_window_with_text_input
                0x00453bcc                system15
                0x004542ed                APISetActiveWindow
                0x00454671                apiSetClientAreaRect
                0x004543b0                APIredraw_window
                0x004546c3                apiCreateThread
                0x00453e19                SetNextWindowProcedure
                0x004545ed                apiGetCursorX
                0x00453de9                chama_procedimento
                0x00453f00                call_kernel
                0x004541b9                APIRegisterWindow
                0x00454503                api_strncmp
                0x0045442b                APIminimize_window
                0x00453a1f                system2
                0x00453a40                system3
                0x00454921                api_get_current_keyboard_responder
                0x0045469a                apiCreateProcess
                0x0045427f                APIGetFocus
                0x00453ac4                system7
                0x00453aa3                system6
                0x004548c5                apiDefDialog
                0x004541fb                APICloseWindow
                0x0045485c                initializeCriticalSection
                0x00453b27                system10
                0x00453e49                set_cursor
                0x00454402                APImaximize_window
                0x00454561                refresh_screen
                0x00454080                call_gui
                0x00453b06                system9
                0x004548f8                api_set_current_keyboard_responder
                0x00454387                APIresize_window
                0x00454892                apiEndPaint
                0x00453e78                put_char
                0x00453d84                print_string
                0x00454645                apiGetClientAreaRect
                0x00453dba                edit_box
                0x004544d2                kill
                0x00454597                apiReboot
                0x00453ea6                apiShutDown
                0x0045494d                api_set_current_mouse_responder
                0x004544a9                exit
                0x00454454                APIget_foregroung_window
                0x00453a61                system4
                0x004545c3                apiSetCursor
                0x00453b69                system12
                0x00453d89                vsync
                0x00453ae5                system8
                0x004549a2                api_set_window_with_text_input
                0x0045432f                APIGetActiveWindow
                0x00454976                api_get_current_mouse_responder
                0x004544d7                dead_thread_collector
                0x004546ec                apiStartThread
                0x004542ab                APIKillFocus
                0x00454480                APIset_foregroung_window
                0x0045489c                apiPutChar
 .text          0x00454a18      0xbf0 stdio.o
                0x004551d7                putchar
                0x00455193                sprintf
                0x004553c3                input
                0x00454a7d                scroll
                0x004553b9                printf_main
                0x00455203                outbyte
                0x00454c27                app_print
                0x004554ba                stdio_system_call
                0x00454a2f                fopen
                0x004554e2                stdioInitialize
                0x00454a18                fclose
                0x00455386                _outbyte
                0x00455178                printf
                0x00454bbb                app_clear
 .text          0x00455608      0x960 stdlib.o
                0x004558c3                FreeHeap
                0x00455608                rtGetHeapStart
                0x00455b0a                free
                0x00455aac                rand
                0x00455a23                stdlibInitMM
                0x004558cd                heapInit
                0x0045561c                rtGetHeapPointer
                0x00455626                rtGetAvailableHeap
                0x00455a83                libcInitRT
                0x00455630                heapSetLibcHeap
                0x00455ac9                malloc
                0x004558b0                AllocateHeapEx
                0x004556d7                AllocateHeap
                0x00455f01                stdlib_strncmp
                0x00455612                rtGetHeapEnd
                0x00455b0f                system
 .text          0x00455f68      0x4a0 string.o
                0x004561cf                strcspn
                0x00456132                strcat
                0x00455f68                strcmp
                0x00456189                bzero
                0x0045630f                strtok_r
                0x004560c5                memcpy
                0x0045609c                memoryZeroMemory
                0x00456162                bcopy
                0x00456102                strcpy
                0x0045626f                strspn
                0x004563e4                strtok
                0x00456021                str_cmp
                0x00455fc3                strncmp
                0x004561a4                strlen
                0x00457000                . = ALIGN (0x1000)
 *fill*         0x00456408      0xbf8 00

.rdata          0x00457000     0x1890
 .rdata         0x00457000      0x430 stdlib.o
 .rdata         0x00457430       0x30 stdio.o
 .rdata         0x00457460      0x310 api.o
 .rdata         0x00457770      0x340 shellui.o
 .rdata         0x00457ab0      0xde0 main.o

.data           0x00458890      0x770
                0x00458890                data = .
                0x00458890                _data = .
                0x00458890                __data = .
 *(.data)
 .data          0x00458890        0x0 crt0.o
 .data          0x00458890       0x20 main.o
 .data          0x004588b0       0x20 shellui.o
 .data          0x004588d0        0x0 api.o
 .data          0x004588d0        0x0 stdio.o
 .data          0x004588d0       0x10 stdlib.o
 .data          0x004588e0        0x0 string.o
                0x00459000                . = ALIGN (0x1000)
 *fill*         0x004588e0      0x720 00

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
