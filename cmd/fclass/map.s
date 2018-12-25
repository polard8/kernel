
Allocating common symbols
Common symbol       size              file

prompt              0x400             crt0.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
stderr              0x10              crt0.o
prompt_pos          0x10              crt0.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              crt0.o
stdin               0x10              crt0.o
heap_end            0x10              stdlib.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              crt0.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             crt0.o
randseed            0x10              stdlib.o
current_semaphore   0x10              main.o
g_columns           0x10              crt0.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              crt0.o
Streams             0x80              crt0.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              crt0.o
prompt_out          0x400             crt0.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              crt0.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              crt0.o
g_char_attrib       0x10              crt0.o
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

.text           0x00401000     0x7000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x00401000       0x60 crt0.o
                0x00401000                _main
 .text          0x00401060      0x240 main.o
                0x0040109a                Add
                0x00401060                get_a
                0x004010b1                app_main
                0x004010a5                Multi
                0x00401087                do_print_string
 .text          0x004012a0        0x0 ctype.o
 .text          0x004012a0     0x2a10 stdio.o
                0x00401cad                printf_i2hex
                0x00401edf                putchar
                0x00401355                stdio_fntos
                0x00401e9b                sprintf
                0x00402758                feof
                0x00401d1b                printf2
                0x0040287e                stdioSetCursor
                0x0040266d                ungetc
                0x00403c74                rewind
                0x004016be                puts
                0x00402836                fputc
                0x004028d4                stdioGetCursorY
                0x00402900                scanf
                0x0040256b                fputs
                0x00402796                ferror
                0x004020c1                input
                0x004015fc                scroll
                0x004025e0                gets
                0x00401f0b                outbyte
                0x004026d4                fileno
                0x00402464                fflush
                0x004024f6                fprintf
                0x00403c32                stderr_printf
                0x00402229                stdio_system_call
                0x004014ba                fopen
                0x004028a8                stdioGetCursorX
                0x00402251                getchar
                0x00401bc0                printf_atoi
                0x004012a0                stdio_atoi
                0x00402bb0                kvprintf
                0x00403c03                stdout_printf
                0x0040227d                stdioInitialize
                0x004026f7                fgetc
                0x00401454                fclose
                0x004027bc                fseek
                0x00403c61                perror
                0x0040208e                _outbyte
                0x004026aa                ftell
                0x00403b3f                printf
                0x00401ba5                printf3
                0x00403b77                vfprintf
 .text          0x00403cb0      0xc60 stdlib.o
                0x00403fa6                FreeHeap
                0x00403cd8                rtGetHeapStart
                0x004042b3                free
                0x00403cb0                stdlib_system_call
                0x004041dc                rand
                0x00404153                stdlibInitMM
                0x00403fb0                heapInit
                0x0040474d                __findenv
                0x00403cec                rtGetHeapPointer
                0x00403cf6                rtGetAvailableHeap
                0x004041f9                srand
                0x0040484d                atoi
                0x004041b3                libcInitRT
                0x00403d00                heapSetLibcHeap
                0x00404231                stdlib_die
                0x00404818                getenv
                0x00404272                malloc
                0x00403f93                AllocateHeapEx
                0x00403da7                AllocateHeap
                0x004046c4                stdlib_strncmp
                0x00404206                xmalloc
                0x00404722                exit
                0x00403ce2                rtGetHeapEnd
                0x004042b8                system
 .text          0x00404910      0x430 string.o
                0x00404afc                strcspn
                0x00404a5f                strcat
                0x00404910                strcmp
                0x00404ab6                bzero
                0x00404c3c                strtok_r
                0x004049f2                memcpy
                0x004049c9                memoryZeroMemory
                0x00404a8f                bcopy
                0x00404a2f                strcpy
                0x00404b9c                strspn
                0x00404d11                strtok
                0x0040496b                strncmp
                0x00404ad1                strlen
 .text          0x00404d40     0x2600 api.o
                0x004065b0                APIShowCurrentProcessInfo
                0x00406de3                api_getchar
                0x004052e2                system11
                0x00405387                refresh_buffer
                0x00406492                APISetFocus
                0x00405345                system14
                0x0040566e                apiInitBackground
                0x00406382                APICreateWindow
                0x00406b92                apiBeginPaint
                0x00405673                MessageBox
                0x0040662e                APIreplace_window
                0x00406bd9                apiGetSystemMetrics
                0x00405324                system13
                0x00406a2d                apiDown
                0x004060e4                dbProcedure
                0x00406727                apiExit
                0x00406ae1                enterCriticalSection
                0x00406d1e                gramadocore_init_execve
                0x00406995                apiFOpen
                0x00407311                apiShowWindow
                0x00405198                system1
                0x0040521c                system5
                0x0040680d                api_refresh_screen
                0x00406d5e                apiDialog
                0x00406899                apiGetCursorY
                0x00405617                carrega_bitmap_16x16
                0x00406b3a                exitCriticalSection
                0x00404d40                system_call
                0x00406a87                apiUp
                0x00404d68                apiSystem
                0x00406cf2                api_get_window_with_text_input
                0x00407267                apiGetWSScreenWindow
                0x00405366                system15
                0x00406542                APISetActiveWindow
                0x004068f1                apiSetClientAreaRect
                0x00407220                apiDrawText
                0x00406605                APIredraw_window
                0x00406943                apiCreateThread
                0x004055b3                SetNextWindowProcedure
                0x004072bf                apiCreateTimer
                0x0040686d                apiGetCursorX
                0x00405583                chama_procedimento
                0x00406171                call_kernel
                0x0040640e                APIRegisterWindow
                0x00407293                apiGetWSMainWindow
                0x00406783                api_strncmp
                0x00406680                APIminimize_window
                0x004051b9                system2
                0x004051da                system3
                0x00405bf2                DialogBox
                0x00406c2b                api_get_current_keyboard_responder
                0x0040691a                apiCreateProcess
                0x004064d4                APIGetFocus
                0x0040525e                system7
                0x0040523d                system6
                0x00406bcf                apiDefDialog
                0x00405b65                mbProcedure
                0x00406450                APICloseWindow
                0x004071df                apiSendMessage
                0x00406b66                initializeCriticalSection
                0x004052c1                system10
                0x004055e3                set_cursor
                0x00406657                APImaximize_window
                0x00406d54                execve
                0x004067e1                refresh_screen
                0x00406e0f                apiDisplayBMP
                0x004062f1                call_gui
                0x004052a0                system9
                0x00406d28                fork
                0x00406c02                api_set_current_keyboard_responder
                0x004065dc                APIresize_window
                0x00406b9c                apiEndPaint
                0x00405612                put_char
                0x0040551e                print_string
                0x004072e8                apiGetSysTimeInfo
                0x004068c5                apiGetClientAreaRect
                0x00405554                edit_box
                0x00406752                kill
                0x00406817                apiReboot
                0x00405640                apiShutDown
                0x00406c57                api_set_current_mouse_responder
                0x004066d2                APIget_foregroung_window
                0x004051fb                system4
                0x004069cf                apiSaveFile
                0x00406843                apiSetCursor
                0x00405303                system12
                0x00405523                vsync
                0x0040527f                system8
                0x00406cac                api_set_window_with_text_input
                0x00406584                APIGetActiveWindow
                0x004066a9                APIupdate_window
                0x00406c80                api_get_current_mouse_responder
                0x00406757                dead_thread_collector
                0x0040696c                apiStartThread
                0x00406500                APIKillFocus
                0x004066fe                APIset_foregroung_window
                0x00406ba6                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407340      0xcc0 00

.rdata          0x00408000      0xdb0
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x480 stdlib.o
 .rdata         0x00408820      0x380 stdio.o
                0x00408a00                hex2ascii_data
 .rdata         0x00408ba0      0x100 ctype.o
                0x00408ba0                _ctype
 .rdata         0x00408ca0       0xe0 main.o
 .rdata         0x00408d80       0x30 crt0.o

.data           0x00408db0     0x1250
                0x00408db0                data = .
                0x00408db0                _data = .
                0x00408db0                __data = .
 *(.data)
 .data          0x00408db0        0x0 crt0.o
 .data          0x00408db0      0x440 main.o
 .data          0x004091f0        0x0 ctype.o
 .data          0x004091f0        0x0 stdio.o
 .data          0x004091f0        0x0 stdlib.o
 .data          0x004091f0        0x0 string.o
 .data          0x004091f0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409630      0x9d0 00

.bss            0x0040a000    0x126f0
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 crt0.o
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000        0x0 ctype.o
 .bss           0x0040a000       0x10 stdio.o
 .bss           0x0040a010     0x8010 stdlib.o
                0x0040a010                environ
 .bss           0x00412020       0x10 string.o
 .bss           0x00412030     0x8010 api.o
                0x0041b000                . = ALIGN (0x1000)
 *fill*         0x0041a040      0xfc0 00
 COMMON         0x0041b000      0xd40 crt0.o
                0x0041b000                prompt
                0x0041b400                stderr
                0x0041b410                prompt_pos
                0x0041b420                g_using_gui
                0x0041b430                stdin
                0x0041b440                prompt_max
                0x0041b450                prompt_err
                0x0041b850                g_columns
                0x0041b860                stdout
                0x0041b870                Streams
                0x0041b8f0                g_rows
                0x0041b900                prompt_out
                0x0041bd00                g_cursor_y
                0x0041bd10                prompt_status
                0x0041bd20                g_char_attrib
                0x0041bd30                g_cursor_x
 COMMON         0x0041bd40       0x70 main.o
                0x0041bd40                ClientAreaInfo
                0x0041bd50                BufferInfo
                0x0041bd60                rect
                0x0041bd70                CurrentWindow
                0x0041bd80                current_semaphore
                0x0041bd90                CursorInfo
                0x0041bda0                ApplicationInfo
 COMMON         0x0041bdb0      0x900 stdlib.o
                0x0041bdb0                current_mmblock
                0x0041bdc0                mm_prev_pointer
                0x0041bdd0                heap_end
                0x0041bde0                g_available_heap
                0x0041bdf0                heap_start
                0x0041be00                heapCount
                0x0041be10                HEAP_START
                0x0041be20                g_heap_pointer
                0x0041be30                heapList
                0x0041c230                randseed
                0x0041c240                HEAP_SIZE
                0x0041c250                last_size
                0x0041c260                last_valid
                0x0041c270                mmblockList
                0x0041c670                libcHeap
                0x0041c680                Heap
                0x0041c690                mmblockCount
                0x0041c6a0                HEAP_END
 COMMON         0x0041c6b0       0x40 api.o
                0x0041c6b0                messagebox_button2
                0x0041c6c0                dialogbox_button1
                0x0041c6d0                messagebox_button1
                0x0041c6e0                dialogbox_button2
                0x0041c6f0                end = .
                0x0041c6f0                _end = .
                0x0041c6f0                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD api.o
OUTPUT(FCLASS.BIN pe-i386)
