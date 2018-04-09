
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
_io_table           0x50              crt0.o
shellError          0x10              main.o
shell_buffer_y      0x10              main.o
stderr              0x10              crt0.o
shell_buffer        0x7e0             main.o
shellWindowHeight   0x10              main.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
root                0x10              main.o
mm_prev_pointer     0x10              stdlib.o
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
shell_buffer_pos    0x10              main.o
pwd                 0x10              main.o
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
i1Window            0x10              main.o
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
 .text          0x00451058     0x17c0 main.o
                0x00452257                shellPrompt
                0x0045238e                shellTestThreads
                0x00451352                shellProcedure
                0x00451c41                shellShell
                0x00452185                test_operators
                0x00452144                shellThread
                0x00451d26                shellInit
                0x004514b8                shellWaitCmd
                0x00451058                GramadoMain
                0x004525ea                shellInsertCharXY
                0x0045262a                shellInsertCharPos
                0x004514d0                shellCompare
                0x004522be                shellClearBuffer
                0x00452479                shellRefreshScreen
                0x00452658                shellInsertNextChar
                0x004522f9                shellTestLoadFile
                0x004526ee                move_to
                0x00452678                shellInsertCR
                0x00452713                shellShowMetrics
                0x004524c9                shellScroll
                0x0045269c                shellInsertNullTerminator
                0x0045268a                shellInsertLF
                0x0045241e                shellClearscreen
                0x0045211a                shellSetCursor
                0x00452171                shellTree
                0x0045215d                shellHelp
                0x004526ae                shellTestMBR
 .text          0x00452818      0x380 shellui.o
                0x004529eb                shellTestDisplayBMP
                0x00452a61                bmpDisplayBMP
                0x00452818                shellCreateTopBar
 .text          0x00452b98     0x1470 api.o
                0x0045394b                APIShowCurrentProcessInfo
                0x00453138                system11
                0x004531dd                refresh_buffer
                0x0045382d                APISetFocus
                0x0045319b                system14
                0x004534c2                apiInitBackground
                0x00453701                APICreateWindow
                0x00453e78                apiBeginPaint
                0x004534c7                MessageBox
                0x004539c9                APIreplace_window
                0x00453ebf                apiGetSystemMetrics
                0x0045317a                system13
                0x00453d2f                apiDown
                0x00453dc7                enterCriticalSection
                0x00453d05                apiFOpen
                0x00452fee                system1
                0x00453072                system5
                0x00453b7d                api_refresh_screen
                0x00453c09                apiGetCursorY
                0x0045346d                carrega_bitmap_16x16
                0x00453e20                exitCriticalSection
                0x00452b98                system_call
                0x00453d7b                apiUp
                0x00452bc0                apiSystem
                0x00453fd8                api_get_window_with_text_input
                0x004531bc                system15
                0x004538dd                APISetActiveWindow
                0x00453c61                apiSetClientAreaRect
                0x004539a0                APIredraw_window
                0x00453cb3                apiCreateThread
                0x00453409                SetNextWindowProcedure
                0x00453bdd                apiGetCursorX
                0x004533d9                chama_procedimento
                0x004534f0                call_kernel
                0x004537a9                APIRegisterWindow
                0x00453af3                api_strncmp
                0x00453a1b                APIminimize_window
                0x0045300f                system2
                0x00453030                system3
                0x00453f11                api_get_current_keyboard_responder
                0x00453c8a                apiCreateProcess
                0x0045386f                APIGetFocus
                0x004530b4                system7
                0x00453093                system6
                0x00453eb5                apiDefDialog
                0x004537eb                APICloseWindow
                0x00453e4c                initializeCriticalSection
                0x00453117                system10
                0x00453439                set_cursor
                0x004539f2                APImaximize_window
                0x00453b51                refresh_screen
                0x00453670                call_gui
                0x004530f6                system9
                0x00453ee8                api_set_current_keyboard_responder
                0x00453977                APIresize_window
                0x00453e82                apiEndPaint
                0x00453468                put_char
                0x00453374                print_string
                0x00453c35                apiGetClientAreaRect
                0x004533aa                edit_box
                0x00453ac2                kill
                0x00453b87                apiReboot
                0x00453496                apiShutDown
                0x00453f3d                api_set_current_mouse_responder
                0x00453a99                exit
                0x00453a44                APIget_foregroung_window
                0x00453051                system4
                0x00453bb3                apiSetCursor
                0x00453159                system12
                0x00453379                vsync
                0x004530d5                system8
                0x00453f92                api_set_window_with_text_input
                0x0045391f                APIGetActiveWindow
                0x00453f66                api_get_current_mouse_responder
                0x00453ac7                dead_thread_collector
                0x00453cdc                apiStartThread
                0x0045389b                APIKillFocus
                0x00453a70                APIset_foregroung_window
                0x00453e8c                apiPutChar
 .text          0x00454008      0xc00 stdio.o
                0x004547c7                putchar
                0x00454783                sprintf
                0x004549b3                input
                0x0045406d                scroll
                0x004549a9                printf_main
                0x004547f3                outbyte
                0x00454217                app_print
                0x00454aaa                stdio_system_call
                0x0045401f                fopen
                0x00454ad2                stdioInitialize
                0x00454008                fclose
                0x00454976                _outbyte
                0x00454768                printf
                0x004541ab                app_clear
 .text          0x00454c08      0x960 stdlib.o
                0x00454ec3                FreeHeap
                0x00454c08                rtGetHeapStart
                0x0045510a                free
                0x004550ac                rand
                0x00455023                stdlibInitMM
                0x00454ecd                heapInit
                0x00454c1c                rtGetHeapPointer
                0x00454c26                rtGetAvailableHeap
                0x00455083                libcInitRT
                0x00454c30                heapSetLibcHeap
                0x004550c9                malloc
                0x00454eb0                AllocateHeapEx
                0x00454cd7                AllocateHeap
                0x00455501                stdlib_strncmp
                0x00454c12                rtGetHeapEnd
                0x0045510f                system
 .text          0x00455568      0x4a0 string.o
                0x004557cf                strcspn
                0x00455732                strcat
                0x00455568                strcmp
                0x00455789                bzero
                0x0045590f                strtok_r
                0x004556c5                memcpy
                0x0045569c                memoryZeroMemory
                0x00455762                bcopy
                0x00455702                strcpy
                0x0045586f                strspn
                0x004559e4                strtok
                0x00455621                str_cmp
                0x004555c3                strncmp
                0x004557a4                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455a08      0x5f8 00

.rdata          0x00456000     0x1440
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x30 stdio.o
 .rdata         0x00456450      0x310 api.o
 .rdata         0x00456760      0x2c0 shellui.o
 .rdata         0x00456a20      0xa20 main.o

.data           0x00457440      0xbc0
                0x00457440                data = .
                0x00457440                _data = .
                0x00457440                __data = .
 *(.data)
 .data          0x00457440        0x0 crt0.o
 .data          0x00457440       0x20 main.o
 .data          0x00457460       0x20 shellui.o
 .data          0x00457480        0x0 api.o
 .data          0x00457480        0x0 stdio.o
 .data          0x00457480       0x10 stdlib.o
 .data          0x00457490        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x00457490      0xb70 00

.bss            0x00458000     0xa6d0
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
 COMMON         0x00461410      0x9d0 main.o
                0x00461410                ShellMetrics
                0x00461420                shellStatus
                0x00461430                shellWindowWidth
                0x00461440                ClientAreaInfo
                0x00461450                BufferInfo
                0x00461460                shellBufferMaxColumns
                0x00461470                shellError
                0x00461480                shell_buffer_y
                0x00461490                shell_buffer
                0x00461c70                shellWindowHeight
                0x00461c80                root
                0x00461c90                shell_window_x
                0x00461ca0                i2Window
                0x00461cb0                rect
                0x00461cc0                backgroung_color
                0x00461cd0                shellMaxRows
                0x00461ce0                foregroung_color
                0x00461cf0                shell_buffer_pos
                0x00461d00                pwd
                0x00461d10                CurrentWindow
                0x00461d20                current_semaphore
                0x00461d30                ShellHook
                0x00461d40                shellScreenWidth
                0x00461d50                shellScreenHeight
                0x00461d60                shell_buffer_x
                0x00461d70                shell_window_y
                0x00461d80                shellBufferMaxRows
                0x00461d90                CursorInfo
                0x00461da0                shellMaxColumns
                0x00461db0                i1Window
                0x00461dc0                topbarWindow
                0x00461dd0                ApplicationInfo
 COMMON         0x00461de0      0x8f0 stdlib.o
                0x00461de0                current_mmblock
                0x00461df0                mm_prev_pointer
                0x00461e00                heap_end
                0x00461e10                g_available_heap
                0x00461e20                heap_start
                0x00461e30                heapCount
                0x00461e40                HEAP_START
                0x00461e50                g_heap_pointer
                0x00461e60                heapList
                0x00462260                HEAP_SIZE
                0x00462270                last_size
                0x00462280                last_valid
                0x00462290                mmblockList
                0x00462690                libcHeap
                0x004626a0                Heap
                0x004626b0                mmblockCount
                0x004626c0                HEAP_END
                0x004626d0                end = .
                0x004626d0                _end = .
                0x004626d0                __end = .
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
