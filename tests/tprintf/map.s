
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
driverInitialized   0x10              main.o
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
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
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
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
idleError           0x10              main.o
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

.text           0x00401000     0x5000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038      0x3b0 main.o
                0x00401083                idleInit
                0x004010a1                idleServices
                0x0040103d                driverInitialize
                0x0040110b                testtest_main
                0x0040113a                TEST_PRINTF
                0x00401038                idleLoop
                0x00401060                driverUninitialize
 .text          0x004013e8     0x1360 stdio.o
                0x00401bfe                putchar
                0x004013e8                stdio_fntos
                0x00401bba                sprintf
                0x0040232c                feof
                0x00402452                stdioSetCursor
                0x0040228e                ungetc
                0x004016b8                puts
                0x0040240a                fputc
                0x004024a8                stdioGetCursorY
                0x00402589                scanf
                0x004021a4                fputs
                0x0040236a                ferror
                0x00401de0                input
                0x004015f6                scroll
                0x00402219                gets
                0x00401c2a                outbyte
                0x004020c0                fflush
                0x0040212f                fprintf
                0x00401f48                stdio_system_call
                0x0040153d                fopen
                0x0040247c                stdioGetCursorX
                0x00401f70                getchar
                0x004024d4                stdio_atoi
                0x00401f9c                stdioInitialize
                0x004022cb                fgetc
                0x004014d7                fclose
                0x00402390                fseek
                0x00401dad                _outbyte
                0x00401b9f                printf
 .text          0x00402748      0xaf0 stdlib.o
                0x00402a3e                FreeHeap
                0x00402770                rtGetHeapStart
                0x00402c92                free
                0x00402748                stdlib_system_call
                0x00402c27                rand
                0x00402b9e                stdlibInitMM
                0x00402a48                heapInit
                0x0040312c                __findenv
                0x00402784                rtGetHeapPointer
                0x0040278e                rtGetAvailableHeap
                0x00402c44                srand
                0x00402bfe                libcInitRT
                0x00402798                heapSetLibcHeap
                0x004031f7                getenv
                0x00402c51                malloc
                0x00402a2b                AllocateHeapEx
                0x0040283f                AllocateHeap
                0x004030a3                stdlib_strncmp
                0x00403101                exit
                0x0040277a                rtGetHeapEnd
                0x00402c97                system
 .text          0x00403238       0xe0 ctype.o
                0x004032d2                isspace
                0x004032f8                isxdigit
                0x004032e5                isupper
                0x0040324b                isalpha
                0x00403297                islower
                0x00403238                isalnum
                0x004032aa                isprint
                0x00403284                isgraph
                0x00403271                isdigit
                0x0040325e                iscntrl
                0x004032bf                ispunct
 .text          0x00403318      0x430 string.o
                0x00403504                strcspn
                0x00403467                strcat
                0x00403318                strcmp
                0x004034be                bzero
                0x00403644                strtok_r
                0x004033fa                memcpy
                0x004033d1                memoryZeroMemory
                0x00403497                bcopy
                0x00403437                strcpy
                0x004035a4                strspn
                0x00403719                strtok
                0x00403373                strncmp
                0x004034d9                strlen
 .text          0x00403748     0x1a10 api.o
                0x004044e3                APIShowCurrentProcessInfo
                0x00404d16                api_getchar
                0x00403cea                system11
                0x00403d8f                refresh_buffer
                0x004043c5                APISetFocus
                0x00403d4d                system14
                0x00404076                apiInitBackground
                0x004042b5                APICreateWindow
                0x00404ac5                apiBeginPaint
                0x0040407b                MessageBox
                0x00404561                APIreplace_window
                0x00404b0c                apiGetSystemMetrics
                0x00403d2c                system13
                0x00404960                apiDown
                0x0040465a                apiExit
                0x00404a14                enterCriticalSection
                0x00404c51                gramadocore_init_execve
                0x004048c8                apiFOpen
                0x00403ba0                system1
                0x00403c24                system5
                0x00404740                api_refresh_screen
                0x00404c91                apiDialog
                0x004047cc                apiGetCursorY
                0x0040401f                carrega_bitmap_16x16
                0x00404a6d                exitCriticalSection
                0x00403748                system_call
                0x004049ba                apiUp
                0x00403770                apiSystem
                0x00404c25                api_get_window_with_text_input
                0x00403d6e                system15
                0x00404475                APISetActiveWindow
                0x00404824                apiSetClientAreaRect
                0x00404538                APIredraw_window
                0x00404876                apiCreateThread
                0x00403fbb                SetNextWindowProcedure
                0x004047a0                apiGetCursorX
                0x00403f8b                chama_procedimento
                0x004040a4                call_kernel
                0x00404341                APIRegisterWindow
                0x004046b6                api_strncmp
                0x004045b3                APIminimize_window
                0x00403bc1                system2
                0x00403be2                system3
                0x00404b5e                api_get_current_keyboard_responder
                0x0040484d                apiCreateProcess
                0x00404407                APIGetFocus
                0x00403c66                system7
                0x00403c45                system6
                0x00404b02                apiDefDialog
                0x00404383                APICloseWindow
                0x00405112                apiSendMessage
                0x00404a99                initializeCriticalSection
                0x00403cc9                system10
                0x00403feb                set_cursor
                0x0040458a                APImaximize_window
                0x00404c87                execve
                0x00404714                refresh_screen
                0x00404d42                apiDisplayBMP
                0x00404224                call_gui
                0x00403ca8                system9
                0x00404c5b                fork
                0x00404b35                api_set_current_keyboard_responder
                0x0040450f                APIresize_window
                0x00404acf                apiEndPaint
                0x0040401a                put_char
                0x00403f26                print_string
                0x004047f8                apiGetClientAreaRect
                0x00403f5c                edit_box
                0x00404685                kill
                0x0040474a                apiReboot
                0x00404048                apiShutDown
                0x00404b8a                api_set_current_mouse_responder
                0x00404605                APIget_foregroung_window
                0x00403c03                system4
                0x00404902                apiSaveFile
                0x00404776                apiSetCursor
                0x00403d0b                system12
                0x00403f2b                vsync
                0x00403c87                system8
                0x00404bdf                api_set_window_with_text_input
                0x004044b7                APIGetActiveWindow
                0x004045dc                APIupdate_window
                0x00404bb3                api_get_current_mouse_responder
                0x0040468a                dead_thread_collector
                0x0040489f                apiStartThread
                0x00404433                APIKillFocus
                0x00404631                APIset_foregroung_window
                0x00404ad9                apiPutChar
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405158      0xea8 00

.rdata          0x00406000      0xa30
 .rdata         0x00406000      0x330 api.o
 .rdata         0x00406330      0x460 stdlib.o
 .rdata         0x00406790       0x70 stdio.o
 .rdata         0x00406800      0x230 main.o

.data           0x00406a30      0x5d0
                0x00406a30                data = .
                0x00406a30                _data = .
                0x00406a30                __data = .
 *(.data)
 .data          0x00406a30        0x0 main.o
 .data          0x00406a30        0x0 stdio.o
 .data          0x00406a30        0x0 stdlib.o
 .data          0x00406a30      0x120 ctype.o
                0x00406a30                _ctype_
 .data          0x00406b50        0x0 string.o
 .data          0x00406b50      0x440 api.o
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x00406f90       0x70 00

.bss            0x00407000     0xa6e0
                0x00407000                bss = .
                0x00407000                _bss = .
                0x00407000                __bss = .
 *(.bss)
 .bss           0x00407000        0x0 main.o
 .bss           0x00407000       0x10 stdio.o
 .bss           0x00407010     0x8010 stdlib.o
                0x00407010                environ
 .bss           0x0040f020        0x0 ctype.o
 .bss           0x0040f020       0x10 string.o
 .bss           0x0040f030       0x40 api.o
                0x00410000                . = ALIGN (0x1000)
 *fill*         0x0040f070      0xf90 00
 COMMON         0x00410000      0xde0 main.o
                0x00410000                prompt
                0x00410400                idleStatus
                0x00410410                ClientAreaInfo
                0x00410420                BufferInfo
                0x00410430                driverInitialized
                0x00410440                stderr
                0x00410450                prompt_pos
                0x00410460                g_using_gui
                0x00410470                stdin
                0x00410480                rect
                0x00410490                prompt_max
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
                0x00410d90                prompt_status
                0x00410da0                g_char_attrib
                0x00410db0                ApplicationInfo
                0x00410dc0                idleError
                0x00410dd0                g_cursor_x
 COMMON         0x00410de0      0x900 stdlib.o
                0x00410de0                current_mmblock
                0x00410df0                mm_prev_pointer
                0x00410e00                heap_end
                0x00410e10                g_available_heap
                0x00410e20                heap_start
                0x00410e30                heapCount
                0x00410e40                HEAP_START
                0x00410e50                g_heap_pointer
                0x00410e60                heapList
                0x00411260                randseed
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
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TPRINTF.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
