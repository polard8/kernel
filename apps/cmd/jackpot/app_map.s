
Allocating common symbols
Common symbol       size              file

j                   0x4               main.o
prompt              0x400             main.o
number              0x10              main.o
i                   0x4               main.o
ClientAreaInfo      0x10              api.o
BufferInfo          0x10              api.o
stderr              0x10              stdio.o
prompt_pos          0x10              stdio.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              stdio.o
stdin               0x10              stdio.o
heap_end            0x10              stdlib.o
rect                0x10              api.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              stdio.o
CurrentWindow       0x10              api.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
maxrand             0x4               main.o
current_semaphore   0x10              api.o
g_columns           0x10              stdio.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              stdio.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              stdio.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
c                   0x4               main.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              stdio.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
life                0x4               main.o
CursorInfo          0x10              api.o
dialogbox_button2   0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              stdio.o
g_char_attrib       0x10              stdio.o
ApplicationInfo     0x10              api.o
g_cursor_x          0x10              stdio.o
HEAP_END            0x10              stdlib.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

                0x0000000000400000                __image_base__ = 0x400000
                0x0000000000000000                __dll__ = 0x0
                0x0000000000400000                ___ImageBase = 0x400000
                0x0000000000001000                __section_alignment__ = 0x1000
                0x0000000000000200                __file_alignment__ = 0x200
                0x0000000000000004                __major_os_version__ = 0x4
                0x0000000000000000                __minor_os_version__ = 0x0
                0x0000000000000001                __major_image_version__ = 0x1
                0x0000000000000000                __minor_image_version__ = 0x0
                0x0000000000000004                __major_subsystem_version__ = 0x4
                0x0000000000000000                __minor_subsystem_version__ = 0x0
                0x0000000000000003                __subsystem__ = 0x3
                0x0000000000200000                __size_of_stack_reserve__ = 0x200000
                0x0000000000001000                __size_of_stack_commit__ = 0x1000
                0x0000000000100000                __size_of_heap_reserve__ = 0x100000
                0x0000000000001000                __size_of_heap_commit__ = 0x1000
                0x0000000000000000                __loader_flags__ = 0x0
                0x0000000000000000                __dll_characteristics__ = 0x0

.text           0x0000000000401000     0x7000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000      0x478 main.o
                0x0000000000401000                app_main
                0x000000000040108e                Start
                0x00000000004011cd                GetResults
                0x0000000000401355                jackpot_atoi
                0x000000000040141c                jackpot_main
 .text          0x0000000000401478        0x0 ctype.o
 .text          0x0000000000401478     0x2a10 stdio.o
                0x0000000000401478                stdio_atoi
                0x000000000040152d                stdio_fntos
                0x000000000040162c                fclose
                0x0000000000401692                fopen
                0x00000000004017d4                scroll
                0x0000000000401896                puts
                0x0000000000401d7d                printf3
                0x0000000000401d98                printf_atoi
                0x0000000000401e85                printf_i2hex
                0x0000000000401ef3                printf2
                0x0000000000402073                sprintf
                0x00000000004020b7                putchar
                0x00000000004020e3                outbyte
                0x0000000000402266                _outbyte
                0x0000000000402299                input
                0x0000000000402401                stdio_system_call
                0x0000000000402429                getchar
                0x0000000000402455                stdioInitialize
                0x000000000040263c                fflush
                0x00000000004026ce                fprintf
                0x0000000000402743                fputs
                0x00000000004027b8                gets
                0x0000000000402845                ungetc
                0x0000000000402882                ftell
                0x00000000004028ac                fileno
                0x00000000004028cf                fgetc
                0x0000000000402930                feof
                0x000000000040296e                ferror
                0x0000000000402994                fseek
                0x0000000000402a0e                fputc
                0x0000000000402a56                stdioSetCursor
                0x0000000000402a80                stdioGetCursorX
                0x0000000000402aac                stdioGetCursorY
                0x0000000000402ad8                scanf
                0x0000000000402d88                kvprintf
                0x0000000000403d17                printf
                0x0000000000403d4f                vfprintf
                0x0000000000403ddb                stdout_printf
                0x0000000000403e0a                stderr_printf
                0x0000000000403e39                perror
                0x0000000000403e4c                rewind
 .text          0x0000000000403e88      0xda0 stdlib.o
                0x0000000000403e88                stdlib_system_call
                0x0000000000403eb0                rtGetHeapStart
                0x0000000000403eba                rtGetHeapEnd
                0x0000000000403ec4                rtGetHeapPointer
                0x0000000000403ece                rtGetAvailableHeap
                0x0000000000403ed8                heapSetLibcHeap
                0x0000000000403f7f                AllocateHeap
                0x000000000040419e                AllocateHeapEx
                0x00000000004041b1                FreeHeap
                0x00000000004041bb                heapInit
                0x000000000040435e                stdlibInitMM
                0x00000000004043c8                libcInitRT
                0x00000000004043f1                rand
                0x000000000040440e                srand
                0x000000000040441b                xmalloc
                0x0000000000404446                stdlib_die
                0x0000000000404487                malloc
                0x00000000004044c8                free
                0x00000000004044cd                calloc
                0x0000000000404510                system
                0x000000000040491c                stdlib_strncmp
                0x000000000040497a                __findenv
                0x0000000000404a45                getenv
                0x0000000000404a7a                atoi
                0x0000000000404b2f                reverse
                0x0000000000404b8e                itoa
 .text          0x0000000000404c28      0x470 string.o
                0x0000000000404c28                strcmp
                0x0000000000404c83                strncmp
                0x0000000000404ce1                memset
                0x0000000000404d2a                memoryZeroMemory
                0x0000000000404d53                memcpy
                0x0000000000404d90                strcpy
                0x0000000000404dc0                strcat
                0x0000000000404df0                bcopy
                0x0000000000404e17                bzero
                0x0000000000404e32                strlen
                0x0000000000404e5d                strcspn
                0x0000000000404efd                strspn
                0x0000000000404f9d                strtok_r
                0x0000000000405072                strtok
 .text          0x0000000000405098       0x70 time.o
                0x0000000000405098                time
                0x00000000004050d2                time_system_call
 .text          0x0000000000405108     0x25d0 api.o
                0x0000000000405108                system_call
                0x0000000000405130                apiSystem
                0x0000000000405560                system1
                0x0000000000405581                system2
                0x00000000004055a2                system3
                0x00000000004055c3                system4
                0x00000000004055e4                system5
                0x0000000000405605                system6
                0x0000000000405626                system7
                0x0000000000405647                system8
                0x0000000000405668                system9
                0x0000000000405689                system10
                0x00000000004056aa                system11
                0x00000000004056cb                system12
                0x00000000004056ec                system13
                0x000000000040570d                system14
                0x000000000040572e                system15
                0x000000000040574f                refresh_buffer
                0x00000000004058e6                print_string
                0x00000000004058eb                vsync
                0x000000000040591c                edit_box
                0x000000000040594b                chama_procedimento
                0x000000000040597b                SetNextWindowProcedure
                0x00000000004059ab                set_cursor
                0x00000000004059da                put_char
                0x00000000004059df                carrega_bitmap_16x16
                0x0000000000405a08                apiShutDown
                0x0000000000405a36                apiInitBackground
                0x0000000000405a3b                MessageBox
                0x0000000000405f2d                mbProcedure
                0x0000000000405fba                DialogBox
                0x00000000004064ac                dbProcedure
                0x0000000000406539                call_kernel
                0x00000000004066b9                call_gui
                0x000000000040674a                APICreateWindow
                0x00000000004067d6                APIRegisterWindow
                0x0000000000406818                APICloseWindow
                0x000000000040685a                APISetFocus
                0x000000000040689c                APIGetFocus
                0x00000000004068c8                APIKillFocus
                0x000000000040690a                APISetActiveWindow
                0x000000000040694c                APIGetActiveWindow
                0x0000000000406978                APIShowCurrentProcessInfo
                0x00000000004069a4                APIresize_window
                0x00000000004069cd                APIredraw_window
                0x00000000004069f6                APIreplace_window
                0x0000000000406a1f                APImaximize_window
                0x0000000000406a48                APIminimize_window
                0x0000000000406a71                APIupdate_window
                0x0000000000406a9a                APIget_foregroung_window
                0x0000000000406ac6                APIset_foregroung_window
                0x0000000000406aef                apiExit
                0x0000000000406b1a                kill
                0x0000000000406b1f                dead_thread_collector
                0x0000000000406b4b                api_strncmp
                0x0000000000406ba9                refresh_screen
                0x0000000000406bd5                api_refresh_screen
                0x0000000000406bdf                apiReboot
                0x0000000000406c0b                apiSetCursor
                0x0000000000406c35                apiGetCursorX
                0x0000000000406c61                apiGetCursorY
                0x0000000000406c8d                apiGetClientAreaRect
                0x0000000000406cb9                apiSetClientAreaRect
                0x0000000000406ce2                apiCreateProcess
                0x0000000000406d0b                apiCreateThread
                0x0000000000406d34                apiStartThread
                0x0000000000406d5d                apiFOpen
                0x0000000000406d97                apiSaveFile
                0x0000000000406df5                apiDown
                0x0000000000406e4f                apiUp
                0x0000000000406ea9                enterCriticalSection
                0x0000000000406f02                exitCriticalSection
                0x0000000000406f2e                initializeCriticalSection
                0x0000000000406f5a                apiBeginPaint
                0x0000000000406f64                apiEndPaint
                0x0000000000406f6e                apiPutChar
                0x0000000000406f97                apiDefDialog
                0x0000000000406fa1                apiGetSystemMetrics
                0x0000000000406fca                api_set_current_keyboard_responder
                0x0000000000406ff3                api_get_current_keyboard_responder
                0x000000000040701f                api_set_current_mouse_responder
                0x0000000000407048                api_get_current_mouse_responder
                0x0000000000407074                api_set_window_with_text_input
                0x00000000004070ba                api_get_window_with_text_input
                0x00000000004070e6                gramadocore_init_execve
                0x00000000004070f0                apiDialog
                0x0000000000407175                api_getchar
                0x00000000004071a1                apiDisplayBMP
                0x0000000000407571                apiSendMessage
                0x00000000004075b2                apiDrawText
                0x00000000004075f9                apiGetWSScreenWindow
                0x0000000000407625                apiGetWSMainWindow
                0x0000000000407651                apiCreateTimer
                0x000000000040767a                apiGetSysTimeInfo
                0x00000000004076a3                apiShowWindow
 .text          0x00000000004076d8       0x90 unistd.o
                0x00000000004076d8                unistd_system_call
                0x0000000000407700                execve
                0x000000000040770a                exit
                0x0000000000407735                fork
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x0000000000407768      0x898 

.rodata         0x0000000000408000      0x290
 .rodata        0x0000000000408000      0x28e main.o

.eh_frame       0x0000000000409000       0xb4
 .eh_frame      0x0000000000409000       0xb4 main.o

.rdata          0x000000000040a000      0xd10
 .rdata         0x000000000040a000      0x100 ctype.o
                0x000000000040a000                _ctype
 .rdata         0x000000000040a100      0x380 stdio.o
                0x000000000040a2e0                hex2ascii_data
 .rdata         0x000000000040a480      0x4f0 stdlib.o
 .rdata         0x000000000040a970      0x3a0 api.o

.data           0x000000000040ad10     0x12f0
                0x000000000040ad10                data = .
                0x000000000040ad10                _data = .
                0x000000000040ad10                __data = .
 *(.data)
 .data          0x000000000040ad10        0x0 main.o
 .data          0x000000000040ad10        0x0 ctype.o
 .data          0x000000000040ad10        0x0 stdio.o
 .data          0x000000000040ad10        0x0 stdlib.o
 .data          0x000000000040ad10        0x0 string.o
 .data          0x000000000040ad10        0x0 time.o
 .data          0x000000000040ad10      0x440 api.o
 .data          0x000000000040b150        0x0 unistd.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040b150      0xeb0 

.bss            0x000000000040c000    0x12714
                0x000000000040c000                bss = .
                0x000000000040c000                _bss = .
                0x000000000040c000                __bss = .
 *(.bss)
 .bss           0x000000000040c000        0x0 main.o
 .bss           0x000000000040c000        0x0 ctype.o
 .bss           0x000000000040c000       0x10 stdio.o
 .bss           0x000000000040c010     0x8010 stdlib.o
                0x000000000040c010                environ
 .bss           0x0000000000414020       0x10 string.o
 .bss           0x0000000000414030        0x0 time.o
 .bss           0x0000000000414030     0x8010 api.o
 .bss           0x000000000041c040        0x0 unistd.o
                0x000000000041d000                . = ALIGN (0x1000)
 *fill*         0x000000000041c040      0xfc0 
 COMMON         0x000000000041d000      0xca4 main.o
                0x000000000041d000                j
                0x000000000041d004                prompt
                0x000000000041d404                number
                0x000000000041d414                i
                0x000000000041d418                prompt_err
                0x000000000041d818                maxrand
                0x000000000041d81c                Streams
                0x000000000041d89c                prompt_out
                0x000000000041dc9c                c
                0x000000000041dca0                life
 COMMON         0x000000000041dca4       0xc0 stdio.o
                0x000000000041dca4                stderr
                0x000000000041dcb4                prompt_pos
                0x000000000041dcc4                g_using_gui
                0x000000000041dcd4                stdin
                0x000000000041dce4                prompt_max
                0x000000000041dcf4                g_columns
                0x000000000041dd04                stdout
                0x000000000041dd14                g_rows
                0x000000000041dd24                g_cursor_y
                0x000000000041dd34                prompt_status
                0x000000000041dd44                g_char_attrib
                0x000000000041dd54                g_cursor_x
 COMMON         0x000000000041dd64      0x900 stdlib.o
                0x000000000041dd64                current_mmblock
                0x000000000041dd74                mm_prev_pointer
                0x000000000041dd84                heap_end
                0x000000000041dd94                g_available_heap
                0x000000000041dda4                heap_start
                0x000000000041ddb4                heapCount
                0x000000000041ddc4                HEAP_START
                0x000000000041ddd4                g_heap_pointer
                0x000000000041dde4                heapList
                0x000000000041e1e4                randseed
                0x000000000041e1f4                HEAP_SIZE
                0x000000000041e204                last_size
                0x000000000041e214                last_valid
                0x000000000041e224                mmblockList
                0x000000000041e624                libcHeap
                0x000000000041e634                Heap
                0x000000000041e644                mmblockCount
                0x000000000041e654                HEAP_END
 COMMON         0x000000000041e664       0xb0 api.o
                0x000000000041e664                ClientAreaInfo
                0x000000000041e674                BufferInfo
                0x000000000041e684                messagebox_button2
                0x000000000041e694                rect
                0x000000000041e6a4                CurrentWindow
                0x000000000041e6b4                current_semaphore
                0x000000000041e6c4                dialogbox_button1
                0x000000000041e6d4                messagebox_button1
                0x000000000041e6e4                CursorInfo
                0x000000000041e6f4                dialogbox_button2
                0x000000000041e704                ApplicationInfo
                0x000000000041e714                end = .
                0x000000000041e714                _end = .
                0x000000000041e714                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
LOAD unistd.o
OUTPUT(JACKPOT.BIN pe-i386)

.comment        0x0000000000000000       0x1c
 .comment       0x0000000000000000       0x1b main.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
