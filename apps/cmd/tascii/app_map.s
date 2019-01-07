
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
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
 .text          0x0000000000401000       0xc8 main.o
                0x0000000000401000                _main
 .text          0x00000000004010c8        0x0 ctype.o
 .text          0x00000000004010c8     0x2a10 stdio.o
                0x00000000004010c8                stdio_atoi
                0x000000000040117d                stdio_fntos
                0x000000000040127c                fclose
                0x00000000004012e2                fopen
                0x0000000000401424                scroll
                0x00000000004014e6                puts
                0x00000000004019cd                printf3
                0x00000000004019e8                printf_atoi
                0x0000000000401ad5                printf_i2hex
                0x0000000000401b43                printf2
                0x0000000000401cc3                sprintf
                0x0000000000401d07                putchar
                0x0000000000401d33                outbyte
                0x0000000000401eb6                _outbyte
                0x0000000000401ee9                input
                0x0000000000402051                stdio_system_call
                0x0000000000402079                getchar
                0x00000000004020a5                stdioInitialize
                0x000000000040228c                fflush
                0x000000000040231e                fprintf
                0x0000000000402393                fputs
                0x0000000000402408                gets
                0x0000000000402495                ungetc
                0x00000000004024d2                ftell
                0x00000000004024fc                fileno
                0x000000000040251f                fgetc
                0x0000000000402580                feof
                0x00000000004025be                ferror
                0x00000000004025e4                fseek
                0x000000000040265e                fputc
                0x00000000004026a6                stdioSetCursor
                0x00000000004026d0                stdioGetCursorX
                0x00000000004026fc                stdioGetCursorY
                0x0000000000402728                scanf
                0x00000000004029d8                kvprintf
                0x0000000000403967                printf
                0x000000000040399f                vfprintf
                0x0000000000403a2b                stdout_printf
                0x0000000000403a5a                stderr_printf
                0x0000000000403a89                perror
                0x0000000000403a9c                rewind
 .text          0x0000000000403ad8      0xda0 stdlib.o
                0x0000000000403ad8                stdlib_system_call
                0x0000000000403b00                rtGetHeapStart
                0x0000000000403b0a                rtGetHeapEnd
                0x0000000000403b14                rtGetHeapPointer
                0x0000000000403b1e                rtGetAvailableHeap
                0x0000000000403b28                heapSetLibcHeap
                0x0000000000403bcf                AllocateHeap
                0x0000000000403dee                AllocateHeapEx
                0x0000000000403e01                FreeHeap
                0x0000000000403e0b                heapInit
                0x0000000000403fae                stdlibInitMM
                0x0000000000404018                libcInitRT
                0x0000000000404041                rand
                0x000000000040405e                srand
                0x000000000040406b                xmalloc
                0x0000000000404096                stdlib_die
                0x00000000004040d7                malloc
                0x0000000000404118                free
                0x000000000040411d                calloc
                0x0000000000404160                system
                0x000000000040456c                stdlib_strncmp
                0x00000000004045ca                __findenv
                0x0000000000404695                getenv
                0x00000000004046ca                atoi
                0x000000000040477f                reverse
                0x00000000004047de                itoa
 .text          0x0000000000404878      0x470 string.o
                0x0000000000404878                strcmp
                0x00000000004048d3                strncmp
                0x0000000000404931                memset
                0x000000000040497a                memoryZeroMemory
                0x00000000004049a3                memcpy
                0x00000000004049e0                strcpy
                0x0000000000404a10                strcat
                0x0000000000404a40                bcopy
                0x0000000000404a67                bzero
                0x0000000000404a82                strlen
                0x0000000000404aad                strcspn
                0x0000000000404b4d                strspn
                0x0000000000404bed                strtok_r
                0x0000000000404cc2                strtok
 .text          0x0000000000404ce8       0x70 time.o
                0x0000000000404ce8                time
                0x0000000000404d22                time_system_call
 .text          0x0000000000404d58     0x25d0 api.o
                0x0000000000404d58                system_call
                0x0000000000404d80                apiSystem
                0x00000000004051b0                system1
                0x00000000004051d1                system2
                0x00000000004051f2                system3
                0x0000000000405213                system4
                0x0000000000405234                system5
                0x0000000000405255                system6
                0x0000000000405276                system7
                0x0000000000405297                system8
                0x00000000004052b8                system9
                0x00000000004052d9                system10
                0x00000000004052fa                system11
                0x000000000040531b                system12
                0x000000000040533c                system13
                0x000000000040535d                system14
                0x000000000040537e                system15
                0x000000000040539f                refresh_buffer
                0x0000000000405536                print_string
                0x000000000040553b                vsync
                0x000000000040556c                edit_box
                0x000000000040559b                chama_procedimento
                0x00000000004055cb                SetNextWindowProcedure
                0x00000000004055fb                set_cursor
                0x000000000040562a                put_char
                0x000000000040562f                carrega_bitmap_16x16
                0x0000000000405658                apiShutDown
                0x0000000000405686                apiInitBackground
                0x000000000040568b                MessageBox
                0x0000000000405b7d                mbProcedure
                0x0000000000405c0a                DialogBox
                0x00000000004060fc                dbProcedure
                0x0000000000406189                call_kernel
                0x0000000000406309                call_gui
                0x000000000040639a                APICreateWindow
                0x0000000000406426                APIRegisterWindow
                0x0000000000406468                APICloseWindow
                0x00000000004064aa                APISetFocus
                0x00000000004064ec                APIGetFocus
                0x0000000000406518                APIKillFocus
                0x000000000040655a                APISetActiveWindow
                0x000000000040659c                APIGetActiveWindow
                0x00000000004065c8                APIShowCurrentProcessInfo
                0x00000000004065f4                APIresize_window
                0x000000000040661d                APIredraw_window
                0x0000000000406646                APIreplace_window
                0x000000000040666f                APImaximize_window
                0x0000000000406698                APIminimize_window
                0x00000000004066c1                APIupdate_window
                0x00000000004066ea                APIget_foregroung_window
                0x0000000000406716                APIset_foregroung_window
                0x000000000040673f                apiExit
                0x000000000040676a                kill
                0x000000000040676f                dead_thread_collector
                0x000000000040679b                api_strncmp
                0x00000000004067f9                refresh_screen
                0x0000000000406825                api_refresh_screen
                0x000000000040682f                apiReboot
                0x000000000040685b                apiSetCursor
                0x0000000000406885                apiGetCursorX
                0x00000000004068b1                apiGetCursorY
                0x00000000004068dd                apiGetClientAreaRect
                0x0000000000406909                apiSetClientAreaRect
                0x0000000000406932                apiCreateProcess
                0x000000000040695b                apiCreateThread
                0x0000000000406984                apiStartThread
                0x00000000004069ad                apiFOpen
                0x00000000004069e7                apiSaveFile
                0x0000000000406a45                apiDown
                0x0000000000406a9f                apiUp
                0x0000000000406af9                enterCriticalSection
                0x0000000000406b52                exitCriticalSection
                0x0000000000406b7e                initializeCriticalSection
                0x0000000000406baa                apiBeginPaint
                0x0000000000406bb4                apiEndPaint
                0x0000000000406bbe                apiPutChar
                0x0000000000406be7                apiDefDialog
                0x0000000000406bf1                apiGetSystemMetrics
                0x0000000000406c1a                api_set_current_keyboard_responder
                0x0000000000406c43                api_get_current_keyboard_responder
                0x0000000000406c6f                api_set_current_mouse_responder
                0x0000000000406c98                api_get_current_mouse_responder
                0x0000000000406cc4                api_set_window_with_text_input
                0x0000000000406d0a                api_get_window_with_text_input
                0x0000000000406d36                gramadocore_init_execve
                0x0000000000406d40                apiDialog
                0x0000000000406dc5                api_getchar
                0x0000000000406df1                apiDisplayBMP
                0x00000000004071c1                apiSendMessage
                0x0000000000407202                apiDrawText
                0x0000000000407249                apiGetWSScreenWindow
                0x0000000000407275                apiGetWSMainWindow
                0x00000000004072a1                apiCreateTimer
                0x00000000004072ca                apiGetSysTimeInfo
                0x00000000004072f3                apiShowWindow
 .text          0x0000000000407328       0x90 unistd.o
                0x0000000000407328                unistd_system_call
                0x0000000000407350                execve
                0x000000000040735a                exit
                0x0000000000407385                fork
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x00000000004073b8      0xc48 

.rodata         0x0000000000408000       0x34
 .rodata        0x0000000000408000       0x34 main.o

.eh_frame       0x0000000000409000       0x38
 .eh_frame      0x0000000000409000       0x38 main.o

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

.bss            0x000000000040c000    0x126f0
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
 COMMON         0x000000000041d000      0xc80 main.o
                0x000000000041d000                prompt
                0x000000000041d400                prompt_err
                0x000000000041d800                Streams
                0x000000000041d880                prompt_out
 COMMON         0x000000000041dc80       0xc0 stdio.o
                0x000000000041dc80                stderr
                0x000000000041dc90                prompt_pos
                0x000000000041dca0                g_using_gui
                0x000000000041dcb0                stdin
                0x000000000041dcc0                prompt_max
                0x000000000041dcd0                g_columns
                0x000000000041dce0                stdout
                0x000000000041dcf0                g_rows
                0x000000000041dd00                g_cursor_y
                0x000000000041dd10                prompt_status
                0x000000000041dd20                g_char_attrib
                0x000000000041dd30                g_cursor_x
 COMMON         0x000000000041dd40      0x900 stdlib.o
                0x000000000041dd40                current_mmblock
                0x000000000041dd50                mm_prev_pointer
                0x000000000041dd60                heap_end
                0x000000000041dd70                g_available_heap
                0x000000000041dd80                heap_start
                0x000000000041dd90                heapCount
                0x000000000041dda0                HEAP_START
                0x000000000041ddb0                g_heap_pointer
                0x000000000041ddc0                heapList
                0x000000000041e1c0                randseed
                0x000000000041e1d0                HEAP_SIZE
                0x000000000041e1e0                last_size
                0x000000000041e1f0                last_valid
                0x000000000041e200                mmblockList
                0x000000000041e600                libcHeap
                0x000000000041e610                Heap
                0x000000000041e620                mmblockCount
                0x000000000041e630                HEAP_END
 COMMON         0x000000000041e640       0xb0 api.o
                0x000000000041e640                ClientAreaInfo
                0x000000000041e650                BufferInfo
                0x000000000041e660                messagebox_button2
                0x000000000041e670                rect
                0x000000000041e680                CurrentWindow
                0x000000000041e690                current_semaphore
                0x000000000041e6a0                dialogbox_button1
                0x000000000041e6b0                messagebox_button1
                0x000000000041e6c0                CursorInfo
                0x000000000041e6d0                dialogbox_button2
                0x000000000041e6e0                ApplicationInfo
                0x000000000041e6f0                end = .
                0x000000000041e6f0                _end = .
                0x000000000041e6f0                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
LOAD unistd.o
OUTPUT(TASCII.BIN pe-i386)

.comment        0x0000000000000000       0x1c
 .comment       0x0000000000000000       0x1b main.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
