
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
 .text          0x00451058     0x1980 main.o
                0x004521a1                shellPrompt
                0x004522d8                shellTestThreads
                0x00452729                shellTestDisplayBMP
                0x00451316                shellProcedure
                0x00451b94                shellShell
                0x004520cf                test_operators
                0x0045208e                shellThread
                0x00451c79                shellInit
                0x00451446                shellWaitCmd
                0x00451058                GramadoMain
                0x00452534                shellInsertCharXY
                0x00452574                shellInsertCharPos
                0x0045145e                shellCompare
                0x00452208                shellClearBuffer
                0x004523c3                shellRefreshScreen
                0x004525a2                shellInsertNextChar
                0x00452243                shellTestLoadFile
                0x004529b2                move_to
                0x004525c2                shellInsertCR
                0x00452413                shellScroll
                0x004525e6                shellInsertNullTerminator
                0x004525f8                bmpDisplayBMP
                0x004525d4                shellInsertLF
                0x00452368                shellClearscreen
                0x00452064                shellSetCursor
                0x004527df                shellCreateTopBar
                0x004520bb                shellTree
                0x004520a7                shellHelp
                0x0045279f                shellTestMBR
 .text          0x004529d8     0x1320 api.o
                0x0045378b                APIShowCurrentProcessInfo
                0x00452f78                system11
                0x0045301d                refresh_buffer
                0x0045366d                APISetFocus
                0x00452fdb                system14
                0x00453302                apiInitBackground
                0x00453541                APICreateWindow
                0x00453cb8                apiBeginPaint
                0x00453307                MessageBox
                0x00453809                APIreplace_window
                0x00452fba                system13
                0x00453b6f                apiDown
                0x00453c07                enterCriticalSection
                0x00453b45                apiFOpen
                0x00452e2e                system1
                0x00452eb2                system5
                0x004539bd                api_refresh_screen
                0x00453a49                apiGetCursorY
                0x004532ad                carrega_bitmap_16x16
                0x00453c60                exitCriticalSection
                0x004529d8                system_call
                0x00453bbb                apiUp
                0x00452a00                apiSystem
                0x00452ffc                system15
                0x0045371d                APISetActiveWindow
                0x00453aa1                apiSetClientAreaRect
                0x004537e0                APIredraw_window
                0x00453af3                apiCreateThread
                0x00453249                SetNextWindowProcedure
                0x00453a1d                apiGetCursorX
                0x00453219                chama_procedimento
                0x00453330                call_kernel
                0x004535e9                APIRegisterWindow
                0x00453933                api_strncmp
                0x0045385b                APIminimize_window
                0x00452e4f                system2
                0x00452e70                system3
                0x00453aca                apiCreateProcess
                0x004536af                APIGetFocus
                0x00452ef4                system7
                0x00452ed3                system6
                0x0045362b                APICloseWindow
                0x00453c8c                initializeCriticalSection
                0x00452f57                system10
                0x00453279                set_cursor
                0x00453832                APImaximize_window
                0x00453991                refresh_screen
                0x004534b0                call_gui
                0x00452f36                system9
                0x004537b7                APIresize_window
                0x00453cc2                apiEndPaint
                0x004532a8                put_char
                0x004531b4                print_string
                0x00453a75                apiGetClientAreaRect
                0x004531ea                edit_box
                0x00453902                kill
                0x004539c7                apiReboot
                0x004532d6                apiShutDown
                0x004538d9                exit
                0x00453884                APIget_foregroung_window
                0x00452e91                system4
                0x004539f3                apiSetCursor
                0x00452f99                system12
                0x004531b9                vsync
                0x00452f15                system8
                0x0045375f                APIGetActiveWindow
                0x00453907                dead_thread_collector
                0x00453b1c                apiStartThread
                0x004536db                APIKillFocus
                0x004538b0                APIset_foregroung_window
                0x00453ccc                apiPutChar
 .text          0x00453cf8      0xbf0 stdio.o
                0x004544b7                putchar
                0x00454473                sprintf
                0x004546a3                input
                0x00453d5d                scroll
                0x00454699                printf_main
                0x004544e3                outbyte
                0x00453f07                app_print
                0x00454785                stdio_system_call
                0x00453d0f                fopen
                0x004547ad                stdioInitialize
                0x00453cf8                fclose
                0x00454666                _outbyte
                0x00454458                printf
                0x00453e9b                app_clear
 .text          0x004548e8      0x960 stdlib.o
                0x00454ba3                FreeHeap
                0x004548e8                rtGetHeapStart
                0x00454dea                free
                0x00454d8c                rand
                0x00454d03                stdlibInitMM
                0x00454bad                heapInit
                0x004548fc                rtGetHeapPointer
                0x00454906                rtGetAvailableHeap
                0x00454d63                libcInitRT
                0x00454910                heapSetLibcHeap
                0x00454da9                malloc
                0x00454b90                AllocateHeapEx
                0x004549b7                AllocateHeap
                0x004551e1                stdlib_strncmp
                0x004548f2                rtGetHeapEnd
                0x00454def                system
 .text          0x00455248      0x4a0 string.o
                0x004554af                strcspn
                0x00455412                strcat
                0x00455248                strcmp
                0x00455469                bzero
                0x004555ef                strtok_r
                0x004553a5                memcpy
                0x0045537c                memoryZeroMemory
                0x00455442                bcopy
                0x004553e2                strcpy
                0x0045554f                strspn
                0x004556c4                strtok
                0x00455301                str_cmp
                0x004552a3                strncmp
                0x00455484                strlen
                0x00456000                . = ALIGN (0x1000)
 *fill*         0x004556e8      0x918 00

.rdata          0x00456000     0x11b0
 .rdata         0x00456000      0x420 stdlib.o
 .rdata         0x00456420       0x40 stdio.o
 .rdata         0x00456460      0x310 api.o
 .rdata         0x00456770      0xa40 main.o

.data           0x004571b0      0xe50
                0x004571b0                data = .
                0x004571b0                _data = .
                0x004571b0                __data = .
 *(.data)
 .data          0x004571b0        0x0 crt0.o
 .data          0x004571b0       0x20 main.o
 .data          0x004571d0        0x0 api.o
 .data          0x004571d0        0x0 stdio.o
 .data          0x004571d0       0x10 stdlib.o
 .data          0x004571e0        0x0 string.o
                0x00458000                . = ALIGN (0x1000)
 *fill*         0x004571e0      0xe20 00

.bss            0x00458000     0xa6d0
                0x00458000                bss = .
                0x00458000                _bss = .
                0x00458000                __bss = .
 *(.bss)
 .bss           0x00458000        0x0 crt0.o
 .bss           0x00458000       0xd0 main.o
 .bss           0x004580d0       0x30 api.o
 .bss           0x00458100       0x10 stdio.o
 .bss           0x00458110     0x8000 stdlib.o
 .bss           0x00460110       0x10 string.o
                0x00461000                . = ALIGN (0x1000)
 *fill*         0x00460120      0xee0 00
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
LOAD api.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
OUTPUT(SHELL.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
