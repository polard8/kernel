
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
TOPBAR              0x20              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
CursorInfo          0x10              main.o
STATUSBAR           0x20              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
g_cursor_x          0x10              main.o
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

.text           0x00401000     0x4000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000        0xc crt0.o
                0x00401000                _crt0Main
 .text          0x0040100c      0x380 main.o
                0x0040103c                mainTextEditor
                0x0040100c                mainGetMessage
                0x004012fd                editorClearScreen
 .text          0x0040138c      0x9b0 stdlib.o
                0x0040166f                FreeHeap
                0x004013b4                rtGetHeapStart
                0x004018b6                free
                0x0040138c                stdlib_system_call
                0x00401858                rand
                0x004017cf                stdlibInitMM
                0x00401679                heapInit
                0x004013c8                rtGetHeapPointer
                0x004013d2                rtGetAvailableHeap
                0x0040182f                libcInitRT
                0x004013dc                heapSetLibcHeap
                0x00401875                malloc
                0x0040165c                AllocateHeapEx
                0x00401483                AllocateHeap
                0x00401cad                stdlib_strncmp
                0x00401d0b                exit
                0x004013be                rtGetHeapEnd
                0x004018bb                system
 .text          0x00401d3c     0x1110 stdio.o
                0x00402683                putchar
                0x00401d3c                stdio_fntos
                0x0040263f                sprintf
                0x00402d14                feof
                0x00402df2                fputc
                0x00402bc9                fputs
                0x00402d52                ferror
                0x0040286f                input
                0x00401f29                scroll
                0x00402865                printf_main
                0x00402c3e                gets
                0x004026af                outbyte
                0x004020d3                app_print
                0x00402ae4                fflush
                0x00402b54                fprintf
                0x00402966                stdio_system_call
                0x00401e91                fopen
                0x0040298e                getchar
                0x004029c0                stdioInitialize
                0x00402cb3                fgetc
                0x00401e2b                fclose
                0x00402d78                fseek
                0x00402832                _outbyte
                0x00402624                printf
                0x00402067                app_clear
 .text          0x00402e4c      0x4a0 string.o
                0x004030b3                strcspn
                0x00403016                strcat
                0x00402e4c                strcmp
                0x0040306d                bzero
                0x004031f3                strtok_r
                0x00402fa9                memcpy
                0x00402f80                memoryZeroMemory
                0x00403046                bcopy
                0x00402fe6                strcpy
                0x00403153                strspn
                0x004032c8                strtok
                0x00402f05                str_cmp
                0x00402ea7                strncmp
                0x00403088                strlen
 .text          0x004032ec     0x1980 api.o
                0x004040a1                APIShowCurrentProcessInfo
                0x00404865                api_getchar
                0x0040388e                system11
                0x00403933                refresh_buffer
                0x00403f83                APISetFocus
                0x004038f1                system14
                0x00403c18                apiInitBackground
                0x00403e57                APICreateWindow
                0x00404620                apiBeginPaint
                0x00403c1d                MessageBox
                0x0040411f                APIreplace_window
                0x00404667                apiGetSystemMetrics
                0x004038d0                system13
                0x004044d7                apiDown
                0x004041ef                apiExit
                0x0040456f                enterCriticalSection
                0x004047ac                gramadocore_init_execve
                0x0040445d                apiFOpen
                0x00403744                system1
                0x004037c8                system5
                0x004042d5                api_refresh_screen
                0x004047ec                apiDialog
                0x00404361                apiGetCursorY
                0x00403bc3                carrega_bitmap_16x16
                0x004045c8                exitCriticalSection
                0x004032ec                system_call
                0x00404523                apiUp
                0x00403314                apiSystem
                0x00404780                api_get_window_with_text_input
                0x00403912                system15
                0x00404033                APISetActiveWindow
                0x004043b9                apiSetClientAreaRect
                0x004040f6                APIredraw_window
                0x0040440b                apiCreateThread
                0x00403b5f                SetNextWindowProcedure
                0x00404335                apiGetCursorX
                0x00403b2f                chama_procedimento
                0x00403c46                call_kernel
                0x00403eff                APIRegisterWindow
                0x0040424b                api_strncmp
                0x00404171                APIminimize_window
                0x00403765                system2
                0x00403786                system3
                0x004046b9                api_get_current_keyboard_responder
                0x004043e2                apiCreateProcess
                0x00403fc5                APIGetFocus
                0x0040380a                system7
                0x004037e9                system6
                0x0040465d                apiDefDialog
                0x00403f41                APICloseWindow
                0x004045f4                initializeCriticalSection
                0x0040386d                system10
                0x00403b8f                set_cursor
                0x00404148                APImaximize_window
                0x004047e2                execve
                0x004042a9                refresh_screen
                0x00404891                apiDisplayBMP
                0x00403dc6                call_gui
                0x0040384c                system9
                0x004047b6                fork
                0x00404690                api_set_current_keyboard_responder
                0x004040cd                APIresize_window
                0x0040462a                apiEndPaint
                0x00403bbe                put_char
                0x00403aca                print_string
                0x0040438d                apiGetClientAreaRect
                0x00403b00                edit_box
                0x0040421a                kill
                0x004042df                apiReboot
                0x00403bec                apiShutDown
                0x004046e5                api_set_current_mouse_responder
                0x0040419a                APIget_foregroung_window
                0x004037a7                system4
                0x00404497                apiSaveFile
                0x0040430b                apiSetCursor
                0x004038af                system12
                0x00403acf                vsync
                0x0040382b                system8
                0x0040473a                api_set_window_with_text_input
                0x00404075                APIGetActiveWindow
                0x0040470e                api_get_current_mouse_responder
                0x0040421f                dead_thread_collector
                0x00404434                apiStartThread
                0x00403ff1                APIKillFocus
                0x004041c6                APIset_foregroung_window
                0x00404634                apiPutChar
 .text          0x00404c6c      0x140 status.o
                0x00404d0a                update_statuts_bar
                0x00404c6c                statusInitializeStatusBar
 .text          0x00404dac       0xa0 topbar.o
                0x00404dac                topbarInitializeTopBar
                0x00405000                . = ALIGN (0x1000)
 *fill*         0x00404e4c      0x1b4 00

.rdata          0x00405000      0x8d0
 .rdata         0x00405000       0x40 topbar.o
 .rdata         0x00405040       0x40 status.o
 .rdata         0x00405080      0x320 api.o
 .rdata         0x004053a0       0x40 stdio.o
 .rdata         0x004053e0      0x430 stdlib.o
 .rdata         0x00405810       0xc0 main.o

.data           0x004058d0     0x1730
                0x004058d0                data = .
                0x004058d0                _data = .
                0x004058d0                __data = .
 *(.data)
 .data          0x004058d0      0x460 main.o
                0x00405d10                running
 .data          0x00405d30       0x10 stdlib.o
 .data          0x00405d40        0x0 stdio.o
 .data          0x00405d40        0x0 string.o
 .data          0x00405d40      0x440 api.o
 .data          0x00406180      0x440 status.o
 .data          0x004065c0      0x440 topbar.o
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x00406a00      0x600 00

.bss            0x00407000     0xa6e0
                0x00407000                bss = .
                0x00407000                _bss = .
                0x00407000                __bss = .
 *(.bss)
 .bss           0x00407000       0x30 main.o
 .bss           0x00407030     0x8000 stdlib.o
 .bss           0x0040f030       0x10 stdio.o
 .bss           0x0040f040       0x10 string.o
 .bss           0x0040f050       0x40 api.o
 .bss           0x0040f090       0x30 status.o
 .bss           0x0040f0c0       0x30 topbar.o
                0x00410000                . = ALIGN (0x1000)
 *fill*         0x0040f0f0      0xf10 00
 COMMON         0x00410000      0xdf0 main.o
                0x00410000                prompt
                0x00410400                ClientAreaInfo
                0x00410410                BufferInfo
                0x00410420                stderr
                0x00410430                prompt_pos
                0x00410440                g_using_gui
                0x00410450                stdin
                0x00410460                rect
                0x00410470                prompt_max
                0x00410480                TOPBAR
                0x004104a0                CurrentWindow
                0x004104b0                prompt_err
                0x004108b0                current_semaphore
                0x004108c0                g_columns
                0x004108d0                stdout
                0x004108e0                Streams
                0x00410960                g_rows
                0x00410970                prompt_out
                0x00410d70                g_cursor_y
                0x00410d80                CursorInfo
                0x00410d90                STATUSBAR
                0x00410db0                prompt_status
                0x00410dc0                g_char_attrib
                0x00410dd0                ApplicationInfo
                0x00410de0                g_cursor_x
 COMMON         0x00410df0      0x8f0 stdlib.o
                0x00410df0                current_mmblock
                0x00410e00                mm_prev_pointer
                0x00410e10                heap_end
                0x00410e20                g_available_heap
                0x00410e30                heap_start
                0x00410e40                heapCount
                0x00410e50                HEAP_START
                0x00410e60                g_heap_pointer
                0x00410e70                heapList
                0x00411270                HEAP_SIZE
                0x00411280                last_size
                0x00411290                last_valid
                0x004112a0                mmblockList
                0x004116a0                libcHeap
                0x004116b0                Heap
                0x004116c0                mmblockCount
                0x004116d0                HEAP_END
                0x004116e0                end = .
                0x004116e0                _end = .
                0x004116e0                __end = .
LOAD crt0.o
LOAD main.o
LOAD stdlib.o
LOAD stdio.o
LOAD string.o
LOAD api.o
LOAD status.o
LOAD topbar.o
OUTPUT(TGFE.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f crt0.o
