
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
 .text          0x00451058     0x17b0 main.o
                0x0045223d                shellPrompt
                0x00452374                shellTestThreads
                0x00451348                shellProcedure
                0x00451c0c                shellShell
                0x0045216b                test_operators
                0x0045212a                shellThread
                0x00451cf1                shellInit
                0x00451494                shellWaitCmd
                0x00451058                GramadoMain
                0x004525d0                shellInsertCharXY
                0x00452610                shellInsertCharPos
                0x004514ac                shellCompare
                0x004522a4                shellClearBuffer
                0x0045245f                shellRefreshScreen
                0x0045263e                shellInsertNextChar
                0x004522df                shellTestLoadFile
                0x004526d4                move_to
                0x0045265e                shellInsertCR
                0x004526f9                shellShowMetrics
                0x004524af                shellScroll
                0x00452682                shellInsertNullTerminator
                0x00452670                shellInsertLF
                0x00452404                shellClearscreen
                0x00452100                shellSetCursor
                0x00452157                shellTree
                0x00452143                shellHelp
                0x00452694                shellTestMBR
 .text          0x00452808      0x380 shellui.o
                0x004529db                shellTestDisplayBMP
                0x00452a51                bmpDisplayBMP
                0x00452808                shellCreateTopBar
 .text          0x00452b88     0x1400 api.o
                0x0045393b                APIShowCurrentProcessInfo
                0x00453128                system11
                0x004531cd                refresh_buffer
                0x0045381d                APISetFocus
                0x0045318b                system14
                0x004534b2                apiInitBackground
                0x004536f1                APICreateWindow
                0x00453e68                apiBeginPaint
                0x004534b7                MessageBox
                0x004539b9                APIreplace_window
                0x00453eaf                apiGetSystemMetrics
                0x0045316a                system13
                0x00453d1f                apiDown
                0x00453db7                enterCriticalSection
                0x00453cf5                apiFOpen
                0x00452fde                system1
                0x00453062                system5
                0x00453b6d                api_refresh_screen
                0x00453bf9                apiGetCursorY
                0x0045345d                carrega_bitmap_16x16
                0x00453e10                exitCriticalSection
                0x00452b88                system_call
                0x00453d6b                apiUp
                0x00452bb0                apiSystem
                0x004531ac                system15
                0x004538cd                APISetActiveWindow
                0x00453c51                apiSetClientAreaRect
                0x00453990                APIredraw_window
                0x00453ca3                apiCreateThread
                0x004533f9                SetNextWindowProcedure
                0x00453bcd                apiGetCursorX
                0x004533c9                chama_procedimento
                0x004534e0                call_kernel
                0x00453799                APIRegisterWindow
                0x00453ae3                api_strncmp
                0x00453a0b                APIminimize_window
                0x00452fff                system2
                0x00453020                system3
                0x00453f01                api_get_current_keyboard_responder
                0x00453c7a                apiCreateProcess
                0x0045385f                APIGetFocus
                0x004530a4                system7
                0x00453083                system6
                0x00453ea5                apiDefDialog
                0x004537db                APICloseWindow
                0x00453e3c                initializeCriticalSection
                0x00453107                system10
                0x00453429                set_cursor
                0x004539e2                APImaximize_window
                0x00453b41                refresh_screen
                0x00453660                call_gui
                0x004530e6                system9
                0x00453ed8                api_set_current_keyboard_responder
                0x00453967                APIresize_window
                0x00453e72                apiEndPaint
                0x00453458                put_char
                0x00453364                print_string
                0x00453c25                apiGetClientAreaRect
                0x0045339a                edit_box
                0x00453ab2                kill
                0x00453b77                apiReboot
                0x00453486                apiShutDown
                0x00453f2d                api_set_current_mouse_responder
                0x00453a89                exit
                0x00453a34                APIget_foregroung_window
                0x00453041                system4
                0x00453ba3                apiSetCursor
                0x00453149                system12
                0x00453369                vsync
                0x004530c5                system8
                0x0045390f                APIGetActiveWindow
                0x00453f56                api_get_current_mouse_responder
                0x00453ab7                dead_thread_collector
                0x00453ccc                apiStartThread
                0x0045388b                APIKillFocus
                0x00453a60                APIset_foregroung_window
                0x00453e7c                apiPutChar
 .text          0x00453f88      0xc00 stdio.o
                0x00454747                putchar
                0x00454703                sprintf
                0x00454933                input
                0x00453fed                scroll
                0x00454929                printf_main
                0x00454773                outbyte
                0x00454197                app_print
                0x00454a2a                stdio_system_call
                0x00453f9f                fopen
                0x00454a52                stdioInitialize
                0x00453f88                fclose
                0x004548f6                _outbyte
                0x004546e8                printf
                0x0045412b                app_clear
 .text          0x00454b88      0x960 stdlib.o
                0x00454e43                FreeHeap
                0x00454b88                rtGetHeapStart
                0x0045508a                free
                0x0045502c                rand
                0x00454fa3                stdlibInitMM
                0x00454e4d                heapInit
                0x00454b9c                rtGetHeapPointer
                0x00454ba6                rtGetAvailableHeap
                0x00455003                libcInitRT
                0x00454bb0                heapSetLibcHeap
                0x00455049                malloc
                0x00454e30                AllocateHeapEx
                0x00454c57                AllocateHeap
                0x00455481                stdlib_strncmp
                0x00454b92                rtGetHeapEnd
                0x0045508f                system
 .text          0x004554e8      0x4a0 string.o
                0x0045574f                strcspn
                0x004556b2                strcat
                0x004554e8                strcmp
                0x00455709                bzero
                0x0045588f                strtok_r
                0x00455645                memcpy
                0x0045561c                memoryZeroMemory
                0x004556e2                bcopy
                0x00455682                strcpy
                0x004557ef                strspn
                0x00455964                strtok
                0x004555a1                str_cmp
                0x00455543                strncmp
                0x00455724                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x00455988      0x678 00

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
