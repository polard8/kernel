
Allocating common symbols
Common symbol       size              file

j                   0x10              main.o
prompt              0x400             main.o
number              0x10              main.o
i                   0x10              main.o
ClientAreaInfo      0x10              api.o
BufferInfo          0x10              api.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
rect                0x10              api.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
CurrentWindow       0x10              api.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
maxrand             0x10              main.o
current_semaphore   0x10              api.o
g_columns           0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
c                   0x10              main.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
life                0x10              main.o
CursorInfo          0x10              api.o
dialogbox_button2   0x10              api.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              api.o
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

.text           0x00401000     0x7000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000      0x3e0 main.o
                0x0040119b                GetResults
                0x00401391                jackpot_main
                0x00401000                app_main
                0x004012dc                jackpot_atoi
                0x00401075                Start
 .text          0x004013e0        0x0 ctype.o
 .text          0x004013e0     0x2a10 stdio.o
                0x00401ded                printf_i2hex
                0x0040201f                putchar
                0x00401495                stdio_fntos
                0x00401fdb                sprintf
                0x00402898                feof
                0x00401e5b                printf2
                0x004029be                stdioSetCursor
                0x004027ad                ungetc
                0x00403db4                rewind
                0x004017fe                puts
                0x00402976                fputc
                0x00402a14                stdioGetCursorY
                0x00402a40                scanf
                0x004026ab                fputs
                0x004028d6                ferror
                0x00402201                input
                0x0040173c                scroll
                0x00402720                gets
                0x0040204b                outbyte
                0x00402814                fileno
                0x004025a4                fflush
                0x00402636                fprintf
                0x00403d72                stderr_printf
                0x00402369                stdio_system_call
                0x004015fa                fopen
                0x004029e8                stdioGetCursorX
                0x00402391                getchar
                0x00401d00                printf_atoi
                0x004013e0                stdio_atoi
                0x00402cf0                kvprintf
                0x00403d43                stdout_printf
                0x004023bd                stdioInitialize
                0x00402837                fgetc
                0x00401594                fclose
                0x004028fc                fseek
                0x00403da1                perror
                0x004021ce                _outbyte
                0x004027ea                ftell
                0x00403c7f                printf
                0x00401ce5                printf3
                0x00403cb7                vfprintf
 .text          0x00403df0      0xc60 stdlib.o
                0x004040e6                FreeHeap
                0x00403e18                rtGetHeapStart
                0x004043f3                free
                0x00403df0                stdlib_system_call
                0x0040431c                rand
                0x00404293                stdlibInitMM
                0x004040f0                heapInit
                0x0040488d                __findenv
                0x00403e2c                rtGetHeapPointer
                0x00403e36                rtGetAvailableHeap
                0x00404339                srand
                0x0040498d                atoi
                0x004042f3                libcInitRT
                0x00403e40                heapSetLibcHeap
                0x00404371                stdlib_die
                0x00404958                getenv
                0x004043b2                malloc
                0x004040d3                AllocateHeapEx
                0x00403ee7                AllocateHeap
                0x00404804                stdlib_strncmp
                0x00404346                xmalloc
                0x00404862                exit
                0x00403e22                rtGetHeapEnd
                0x004043f8                system
 .text          0x00404a50      0x430 string.o
                0x00404c3c                strcspn
                0x00404b9f                strcat
                0x00404a50                strcmp
                0x00404bf6                bzero
                0x00404d7c                strtok_r
                0x00404b32                memcpy
                0x00404b09                memoryZeroMemory
                0x00404bcf                bcopy
                0x00404b6f                strcpy
                0x00404cdc                strspn
                0x00404e51                strtok
                0x00404aab                strncmp
                0x00404c11                strlen
 .text          0x00404e80       0x70 time.o
                0x00404eba                time_system_call
                0x00404e80                time
 .text          0x00404ef0     0x2600 api.o
                0x00406760                APIShowCurrentProcessInfo
                0x00406f93                api_getchar
                0x00405492                system11
                0x00405537                refresh_buffer
                0x00406642                APISetFocus
                0x004054f5                system14
                0x0040581e                apiInitBackground
                0x00406532                APICreateWindow
                0x00406d42                apiBeginPaint
                0x00405823                MessageBox
                0x004067de                APIreplace_window
                0x00406d89                apiGetSystemMetrics
                0x004054d4                system13
                0x00406bdd                apiDown
                0x00406294                dbProcedure
                0x004068d7                apiExit
                0x00406c91                enterCriticalSection
                0x00406ece                gramadocore_init_execve
                0x00406b45                apiFOpen
                0x004074c1                apiShowWindow
                0x00405348                system1
                0x004053cc                system5
                0x004069bd                api_refresh_screen
                0x00406f0e                apiDialog
                0x00406a49                apiGetCursorY
                0x004057c7                carrega_bitmap_16x16
                0x00406cea                exitCriticalSection
                0x00404ef0                system_call
                0x00406c37                apiUp
                0x00404f18                apiSystem
                0x00406ea2                api_get_window_with_text_input
                0x00407417                apiGetWSScreenWindow
                0x00405516                system15
                0x004066f2                APISetActiveWindow
                0x00406aa1                apiSetClientAreaRect
                0x004073d0                apiDrawText
                0x004067b5                APIredraw_window
                0x00406af3                apiCreateThread
                0x00405763                SetNextWindowProcedure
                0x0040746f                apiCreateTimer
                0x00406a1d                apiGetCursorX
                0x00405733                chama_procedimento
                0x00406321                call_kernel
                0x004065be                APIRegisterWindow
                0x00407443                apiGetWSMainWindow
                0x00406933                api_strncmp
                0x00406830                APIminimize_window
                0x00405369                system2
                0x0040538a                system3
                0x00405da2                DialogBox
                0x00406ddb                api_get_current_keyboard_responder
                0x00406aca                apiCreateProcess
                0x00406684                APIGetFocus
                0x0040540e                system7
                0x004053ed                system6
                0x00406d7f                apiDefDialog
                0x00405d15                mbProcedure
                0x00406600                APICloseWindow
                0x0040738f                apiSendMessage
                0x00406d16                initializeCriticalSection
                0x00405471                system10
                0x00405793                set_cursor
                0x00406807                APImaximize_window
                0x00406f04                execve
                0x00406991                refresh_screen
                0x00406fbf                apiDisplayBMP
                0x004064a1                call_gui
                0x00405450                system9
                0x00406ed8                fork
                0x00406db2                api_set_current_keyboard_responder
                0x0040678c                APIresize_window
                0x00406d4c                apiEndPaint
                0x004057c2                put_char
                0x004056ce                print_string
                0x00407498                apiGetSysTimeInfo
                0x00406a75                apiGetClientAreaRect
                0x00405704                edit_box
                0x00406902                kill
                0x004069c7                apiReboot
                0x004057f0                apiShutDown
                0x00406e07                api_set_current_mouse_responder
                0x00406882                APIget_foregroung_window
                0x004053ab                system4
                0x00406b7f                apiSaveFile
                0x004069f3                apiSetCursor
                0x004054b3                system12
                0x004056d3                vsync
                0x0040542f                system8
                0x00406e5c                api_set_window_with_text_input
                0x00406734                APIGetActiveWindow
                0x00406859                APIupdate_window
                0x00406e30                api_get_current_mouse_responder
                0x00406907                dead_thread_collector
                0x00406b1c                apiStartThread
                0x004066b0                APIKillFocus
                0x004068ae                APIset_foregroung_window
                0x00406d56                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004074f0      0xb10 00

.rdata          0x00408000      0xf30
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x480 stdlib.o
 .rdata         0x00408820      0x380 stdio.o
                0x00408a00                hex2ascii_data
 .rdata         0x00408ba0      0x100 ctype.o
                0x00408ba0                _ctype
 .rdata         0x00408ca0      0x290 main.o

.data           0x00408f30     0x10d0
                0x00408f30                data = .
                0x00408f30                _data = .
                0x00408f30                __data = .
 *(.data)
 .data          0x00408f30        0x0 main.o
 .data          0x00408f30        0x0 ctype.o
 .data          0x00408f30        0x0 stdio.o
 .data          0x00408f30        0x0 stdlib.o
 .data          0x00408f30        0x0 string.o
 .data          0x00408f30        0x0 time.o
 .data          0x00408f30      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409370      0xc90 00

.bss            0x0040a000    0x12750
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000        0x0 ctype.o
 .bss           0x0040a000       0x10 stdio.o
 .bss           0x0040a010     0x8010 stdlib.o
                0x0040a010                environ
 .bss           0x00412020       0x10 string.o
 .bss           0x00412030        0x0 time.o
 .bss           0x00412030     0x8010 api.o
                0x0041b000                . = ALIGN (0x1000)
 *fill*         0x0041a040      0xfc0 00
 COMMON         0x0041b000      0xda0 main.o
                0x0041b000                j
                0x0041b010                prompt
                0x0041b410                number
                0x0041b420                i
                0x0041b430                stderr
                0x0041b440                prompt_pos
                0x0041b450                g_using_gui
                0x0041b460                stdin
                0x0041b470                prompt_max
                0x0041b480                prompt_err
                0x0041b880                maxrand
                0x0041b890                g_columns
                0x0041b8a0                stdout
                0x0041b8b0                Streams
                0x0041b930                g_rows
                0x0041b940                prompt_out
                0x0041bd40                c
                0x0041bd50                g_cursor_y
                0x0041bd60                life
                0x0041bd70                prompt_status
                0x0041bd80                g_char_attrib
                0x0041bd90                g_cursor_x
 COMMON         0x0041bda0      0x900 stdlib.o
                0x0041bda0                current_mmblock
                0x0041bdb0                mm_prev_pointer
                0x0041bdc0                heap_end
                0x0041bdd0                g_available_heap
                0x0041bde0                heap_start
                0x0041bdf0                heapCount
                0x0041be00                HEAP_START
                0x0041be10                g_heap_pointer
                0x0041be20                heapList
                0x0041c220                randseed
                0x0041c230                HEAP_SIZE
                0x0041c240                last_size
                0x0041c250                last_valid
                0x0041c260                mmblockList
                0x0041c660                libcHeap
                0x0041c670                Heap
                0x0041c680                mmblockCount
                0x0041c690                HEAP_END
 COMMON         0x0041c6a0       0xb0 api.o
                0x0041c6a0                ClientAreaInfo
                0x0041c6b0                BufferInfo
                0x0041c6c0                messagebox_button2
                0x0041c6d0                rect
                0x0041c6e0                CurrentWindow
                0x0041c6f0                current_semaphore
                0x0041c700                dialogbox_button1
                0x0041c710                messagebox_button1
                0x0041c720                CursorInfo
                0x0041c730                dialogbox_button2
                0x0041c740                ApplicationInfo
                0x0041c750                end = .
                0x0041c750                _end = .
                0x0041c750                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
OUTPUT(JACKPOT.BIN pe-i386)
