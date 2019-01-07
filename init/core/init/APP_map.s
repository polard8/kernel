
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x4               main.o
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
current_semaphore   0x10              api.o
g_columns           0x10              stdio.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              stdio.o
Streams             0x80              main.o
ServerStatus        0x4               main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              stdio.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              stdio.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              stdio.o
g_char_attrib       0x10              stdio.o
ApplicationInfo     0x10              api.o
idleError           0x4               main.o
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
 .head_x86      0x0000000000401000       0x5f head.o
                0x0000000000401000                idle_entry_point
 *(.text)
 .text          0x000000000040105f      0x120 main.o
                0x000000000040106f                idleLoop
                0x000000000040108d                initMain
                0x00000000004010b5                driverInitialize
                0x00000000004010d8                driverUninitialize
                0x00000000004010fb                idleServices
                0x0000000000401161                idleInit
 *fill*         0x000000000040117f        0x1 
 .text          0x0000000000401180     0x2600 api.o
                0x0000000000401180                system_call
                0x00000000004011a8                apiSystem
                0x00000000004015d8                system1
                0x00000000004015f9                system2
                0x000000000040161a                system3
                0x000000000040163b                system4
                0x000000000040165c                system5
                0x000000000040167d                system6
                0x000000000040169e                system7
                0x00000000004016bf                system8
                0x00000000004016e0                system9
                0x0000000000401701                system10
                0x0000000000401722                system11
                0x0000000000401743                system12
                0x0000000000401764                system13
                0x0000000000401785                system14
                0x00000000004017a6                system15
                0x00000000004017c7                refresh_buffer
                0x000000000040195e                print_string
                0x0000000000401963                vsync
                0x0000000000401994                edit_box
                0x00000000004019c3                chama_procedimento
                0x00000000004019f3                SetNextWindowProcedure
                0x0000000000401a23                set_cursor
                0x0000000000401a52                put_char
                0x0000000000401a57                carrega_bitmap_16x16
                0x0000000000401a80                apiShutDown
                0x0000000000401aae                apiInitBackground
                0x0000000000401ab3                MessageBox
                0x0000000000401fa5                mbProcedure
                0x0000000000402032                DialogBox
                0x0000000000402524                dbProcedure
                0x00000000004025b1                call_kernel
                0x0000000000402731                call_gui
                0x00000000004027c2                APICreateWindow
                0x000000000040284e                APIRegisterWindow
                0x0000000000402890                APICloseWindow
                0x00000000004028d2                APISetFocus
                0x0000000000402914                APIGetFocus
                0x0000000000402940                APIKillFocus
                0x0000000000402982                APISetActiveWindow
                0x00000000004029c4                APIGetActiveWindow
                0x00000000004029f0                APIShowCurrentProcessInfo
                0x0000000000402a1c                APIresize_window
                0x0000000000402a45                APIredraw_window
                0x0000000000402a6e                APIreplace_window
                0x0000000000402a97                APImaximize_window
                0x0000000000402ac0                APIminimize_window
                0x0000000000402ae9                APIupdate_window
                0x0000000000402b12                APIget_foregroung_window
                0x0000000000402b3e                APIset_foregroung_window
                0x0000000000402b67                apiExit
                0x0000000000402b92                kill
                0x0000000000402b97                dead_thread_collector
                0x0000000000402bc3                api_strncmp
                0x0000000000402c21                refresh_screen
                0x0000000000402c4d                api_refresh_screen
                0x0000000000402c57                apiReboot
                0x0000000000402c83                apiSetCursor
                0x0000000000402cad                apiGetCursorX
                0x0000000000402cd9                apiGetCursorY
                0x0000000000402d05                apiGetClientAreaRect
                0x0000000000402d31                apiSetClientAreaRect
                0x0000000000402d5a                apiCreateProcess
                0x0000000000402d83                apiCreateThread
                0x0000000000402dac                apiStartThread
                0x0000000000402dd5                apiFOpen
                0x0000000000402e0f                apiSaveFile
                0x0000000000402e6d                apiDown
                0x0000000000402ec7                apiUp
                0x0000000000402f21                enterCriticalSection
                0x0000000000402f7a                exitCriticalSection
                0x0000000000402fa6                initializeCriticalSection
                0x0000000000402fd2                apiBeginPaint
                0x0000000000402fdc                apiEndPaint
                0x0000000000402fe6                apiPutChar
                0x000000000040300f                apiDefDialog
                0x0000000000403019                apiGetSystemMetrics
                0x0000000000403042                api_set_current_keyboard_responder
                0x000000000040306b                api_get_current_keyboard_responder
                0x0000000000403097                api_set_current_mouse_responder
                0x00000000004030c0                api_get_current_mouse_responder
                0x00000000004030ec                api_set_window_with_text_input
                0x0000000000403132                api_get_window_with_text_input
                0x000000000040315e                gramadocore_init_execve
                0x0000000000403168                fork
                0x0000000000403194                execve
                0x000000000040319e                apiDialog
                0x0000000000403223                api_getchar
                0x000000000040324f                apiDisplayBMP
                0x000000000040361f                apiSendMessage
                0x0000000000403660                apiDrawText
                0x00000000004036a7                apiGetWSScreenWindow
                0x00000000004036d3                apiGetWSMainWindow
                0x00000000004036ff                apiCreateTimer
                0x0000000000403728                apiGetSysTimeInfo
                0x0000000000403751                apiShowWindow
 .text          0x0000000000403780        0x0 ctype.o
 .text          0x0000000000403780     0x2a10 stdio.o
                0x0000000000403780                stdio_atoi
                0x0000000000403835                stdio_fntos
                0x0000000000403934                fclose
                0x000000000040399a                fopen
                0x0000000000403adc                scroll
                0x0000000000403b9e                puts
                0x0000000000404085                printf3
                0x00000000004040a0                printf_atoi
                0x000000000040418d                printf_i2hex
                0x00000000004041fb                printf2
                0x000000000040437b                sprintf
                0x00000000004043bf                putchar
                0x00000000004043eb                outbyte
                0x000000000040456e                _outbyte
                0x00000000004045a1                input
                0x0000000000404709                stdio_system_call
                0x0000000000404731                getchar
                0x000000000040475d                stdioInitialize
                0x0000000000404944                fflush
                0x00000000004049d6                fprintf
                0x0000000000404a4b                fputs
                0x0000000000404ac0                gets
                0x0000000000404b4d                ungetc
                0x0000000000404b8a                ftell
                0x0000000000404bb4                fileno
                0x0000000000404bd7                fgetc
                0x0000000000404c38                feof
                0x0000000000404c76                ferror
                0x0000000000404c9c                fseek
                0x0000000000404d16                fputc
                0x0000000000404d5e                stdioSetCursor
                0x0000000000404d88                stdioGetCursorX
                0x0000000000404db4                stdioGetCursorY
                0x0000000000404de0                scanf
                0x0000000000405090                kvprintf
                0x000000000040601f                printf
                0x0000000000406057                vfprintf
                0x00000000004060e3                stdout_printf
                0x0000000000406112                stderr_printf
                0x0000000000406141                perror
                0x0000000000406154                rewind
 .text          0x0000000000406190      0xc60 stdlib.o
                0x0000000000406190                stdlib_system_call
                0x00000000004061b8                rtGetHeapStart
                0x00000000004061c2                rtGetHeapEnd
                0x00000000004061cc                rtGetHeapPointer
                0x00000000004061d6                rtGetAvailableHeap
                0x00000000004061e0                heapSetLibcHeap
                0x0000000000406287                AllocateHeap
                0x0000000000406473                AllocateHeapEx
                0x0000000000406486                FreeHeap
                0x0000000000406490                heapInit
                0x0000000000406633                stdlibInitMM
                0x000000000040669d                libcInitRT
                0x00000000004066c6                rand
                0x00000000004066e3                srand
                0x00000000004066f0                xmalloc
                0x000000000040671b                stdlib_die
                0x000000000040675c                malloc
                0x000000000040679d                free
                0x00000000004067a2                system
                0x0000000000406bae                stdlib_strncmp
                0x0000000000406c0c                exit
                0x0000000000406c37                __findenv
                0x0000000000406d02                getenv
                0x0000000000406d37                atoi
 .text          0x0000000000406df0      0x430 string.o
                0x0000000000406df0                strcmp
                0x0000000000406e4b                strncmp
                0x0000000000406ea9                memoryZeroMemory
                0x0000000000406ed2                memcpy
                0x0000000000406f0f                strcpy
                0x0000000000406f3f                strcat
                0x0000000000406f6f                bcopy
                0x0000000000406f96                bzero
                0x0000000000406fb1                strlen
                0x0000000000406fdc                strcspn
                0x000000000040707c                strspn
                0x000000000040711c                strtok_r
                0x00000000004071f1                strtok
 .text          0x0000000000407220       0x90 conio.o
                0x0000000000407220                putch
                0x0000000000407243                cputs
                0x0000000000407277                getch
                0x000000000040728e                getche
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004072b0      0xd50 

.rodata         0x0000000000408000       0xbc
 .rodata        0x0000000000408000       0xbb main.o

.eh_frame       0x0000000000409000      0x114
 .eh_frame      0x0000000000409000      0x114 main.o

.rdata          0x000000000040a000      0xcc0
 .rdata         0x000000000040a000      0x3a0 api.o
 .rdata         0x000000000040a3a0      0x100 ctype.o
                0x000000000040a3a0                _ctype
 .rdata         0x000000000040a4a0      0x380 stdio.o
                0x000000000040a680                hex2ascii_data
 .rdata         0x000000000040a820      0x480 stdlib.o
 .rdata         0x000000000040aca0       0x10 conio.o

.data           0x000000000040acc0     0x1340
                0x000000000040acc0                data = .
                0x000000000040acc0                _data = .
                0x000000000040acc0                __data = .
 *(.data)
 .data          0x000000000040acc0      0x450 main.o
 .data          0x000000000040b110      0x440 api.o
 .data          0x000000000040b550        0x0 ctype.o
 .data          0x000000000040b550        0x0 stdio.o
 .data          0x000000000040b550        0x0 stdlib.o
 .data          0x000000000040b550        0x0 string.o
 .data          0x000000000040b550        0x0 conio.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040b550      0xab0 

.bss            0x000000000040c000     0xa6fc
                0x000000000040c000                bss = .
                0x000000000040c000                _bss = .
                0x000000000040c000                __bss = .
 *(.bss)
 .bss           0x000000000040c000        0x0 main.o
 .bss           0x000000000040c000       0x40 api.o
 .bss           0x000000000040c040        0x0 ctype.o
 .bss           0x000000000040c040       0x10 stdio.o
 .bss           0x000000000040c050     0x8010 stdlib.o
                0x000000000040c050                environ
 .bss           0x0000000000414060       0x10 string.o
 .bss           0x0000000000414070        0x0 conio.o
                0x0000000000415000                . = ALIGN (0x1000)
 *fill*         0x0000000000414070      0xf90 
 COMMON         0x0000000000415000      0xc8c main.o
                0x0000000000415000                prompt
                0x0000000000415400                idleStatus
                0x0000000000415404                prompt_err
                0x0000000000415804                Streams
                0x0000000000415884                ServerStatus
                0x0000000000415888                prompt_out
                0x0000000000415c88                idleError
 COMMON         0x0000000000415c8c       0xb0 api.o
                0x0000000000415c8c                ClientAreaInfo
                0x0000000000415c9c                BufferInfo
                0x0000000000415cac                messagebox_button2
                0x0000000000415cbc                rect
                0x0000000000415ccc                CurrentWindow
                0x0000000000415cdc                current_semaphore
                0x0000000000415cec                dialogbox_button1
                0x0000000000415cfc                messagebox_button1
                0x0000000000415d0c                dialogbox_button2
                0x0000000000415d1c                CursorInfo
                0x0000000000415d2c                ApplicationInfo
 COMMON         0x0000000000415d3c       0xc0 stdio.o
                0x0000000000415d3c                stderr
                0x0000000000415d4c                prompt_pos
                0x0000000000415d5c                g_using_gui
                0x0000000000415d6c                stdin
                0x0000000000415d7c                prompt_max
                0x0000000000415d8c                g_columns
                0x0000000000415d9c                stdout
                0x0000000000415dac                g_rows
                0x0000000000415dbc                g_cursor_y
                0x0000000000415dcc                prompt_status
                0x0000000000415ddc                g_char_attrib
                0x0000000000415dec                g_cursor_x
 COMMON         0x0000000000415dfc      0x900 stdlib.o
                0x0000000000415dfc                current_mmblock
                0x0000000000415e0c                mm_prev_pointer
                0x0000000000415e1c                heap_end
                0x0000000000415e2c                g_available_heap
                0x0000000000415e3c                heap_start
                0x0000000000415e4c                heapCount
                0x0000000000415e5c                HEAP_START
                0x0000000000415e6c                g_heap_pointer
                0x0000000000415e7c                heapList
                0x000000000041627c                randseed
                0x000000000041628c                HEAP_SIZE
                0x000000000041629c                last_size
                0x00000000004162ac                last_valid
                0x00000000004162bc                mmblockList
                0x00000000004166bc                libcHeap
                0x00000000004166cc                Heap
                0x00000000004166dc                mmblockCount
                0x00000000004166ec                HEAP_END
                0x00000000004166fc                end = .
                0x00000000004166fc                _end = .
                0x00000000004166fc                __end = .
LOAD head.o
LOAD main.o
LOAD api.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD conio.o
OUTPUT(INIT.BIN pe-i386)

.comment        0x0000000000000000       0x1c
 .comment       0x0000000000000000       0x1b main.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
