
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
 .text          0x004012a0       0xe0 ctype.o
                0x0040133a                isspace
                0x00401360                isxdigit
                0x0040134d                isupper
                0x004012b3                isalpha
                0x004012ff                islower
                0x004012a0                isalnum
                0x00401312                isprint
                0x004012ec                isgraph
                0x004012d9                isdigit
                0x004012c6                iscntrl
                0x00401327                ispunct
 .text          0x00401380     0x2770 stdio.o
                0x00401d84                printf_i2hex
                0x00401fb6                putchar
                0x00401435                stdio_fntos
                0x00401f72                sprintf
                0x004026e4                feof
                0x00401df2                printf2
                0x0040280a                stdioSetCursor
                0x00402646                ungetc
                0x00401795                puts
                0x004027c2                fputc
                0x00402860                stdioGetCursorY
                0x0040288c                scanf
                0x0040255c                fputs
                0x00402722                ferror
                0x00402198                input
                0x004016d3                scroll
                0x004025d1                gets
                0x00401fe2                outbyte
                0x00402478                fflush
                0x004024e7                fprintf
                0x00402300                stdio_system_call
                0x0040159a                fopen
                0x00402834                stdioGetCursorX
                0x00402328                getchar
                0x00401c97                printf_atoi
                0x00401380                stdio_atoi
                0x00402b22                kvprintf
                0x00402354                stdioInitialize
                0x00402683                fgetc
                0x00401534                fclose
                0x00402748                fseek
                0x00402165                _outbyte
                0x00403ab1                printf
                0x00401c7c                printf3
 .text          0x00403af0      0xb40 stdlib.o
                0x00403de6                FreeHeap
                0x00403b18                rtGetHeapStart
                0x00404087                free
                0x00403af0                stdlib_system_call
                0x0040401c                rand
                0x00403f93                stdlibInitMM
                0x00403df0                heapInit
                0x00404521                __findenv
                0x00403b2c                rtGetHeapPointer
                0x00403b36                rtGetAvailableHeap
                0x00404039                srand
                0x00403ff3                libcInitRT
                0x00403b40                heapSetLibcHeap
                0x004045ec                getenv
                0x00404046                malloc
                0x00403dd3                AllocateHeapEx
                0x00403be7                AllocateHeap
                0x00404498                stdlib_strncmp
                0x004044f6                exit
                0x00403b22                rtGetHeapEnd
                0x0040408c                system
 .text          0x00404630      0x430 string.o
                0x0040481c                strcspn
                0x0040477f                strcat
                0x00404630                strcmp
                0x004047d6                bzero
                0x0040495c                strtok_r
                0x00404712                memcpy
                0x004046e9                memoryZeroMemory
                0x004047af                bcopy
                0x0040474f                strcpy
                0x004048bc                strspn
                0x00404a31                strtok
                0x0040468b                strncmp
                0x004047f1                strlen
 .text          0x00404a60     0x25f0 api.o
                0x004062ea                APIShowCurrentProcessInfo
                0x00406b1d                api_getchar
                0x00405002                system11
                0x004050a7                refresh_buffer
                0x004061cc                APISetFocus
                0x00405065                system14
                0x0040538e                apiInitBackground
                0x004060bc                APICreateWindow
                0x004068cc                apiBeginPaint
                0x00405393                MessageBox
                0x00406368                APIreplace_window
                0x00406913                apiGetSystemMetrics
                0x00405044                system13
                0x00406767                apiDown
                0x00405e1e                dbProcedure
                0x00406461                apiExit
                0x0040681b                enterCriticalSection
                0x00406a58                gramadocore_init_execve
                0x004066cf                apiFOpen
                0x00404eb8                system1
                0x00404f3c                system5
                0x00406547                api_refresh_screen
                0x00406a98                apiDialog
                0x004065d3                apiGetCursorY
                0x00405337                carrega_bitmap_16x16
                0x00406874                exitCriticalSection
                0x00404a60                system_call
                0x004067c1                apiUp
                0x00404a88                apiSystem
                0x00406a2c                api_get_window_with_text_input
                0x00406fa1                apiGetWSScreenWindow
                0x00405086                system15
                0x0040627c                APISetActiveWindow
                0x0040662b                apiSetClientAreaRect
                0x00406f5a                apiDrawText
                0x0040633f                APIredraw_window
                0x0040667d                apiCreateThread
                0x004052d3                SetNextWindowProcedure
                0x00406ff9                apiCreateTimer
                0x004065a7                apiGetCursorX
                0x004052a3                chama_procedimento
                0x00405eab                call_kernel
                0x00406148                APIRegisterWindow
                0x00406fcd                apiGetWSMainWindow
                0x004064bd                api_strncmp
                0x004063ba                APIminimize_window
                0x00404ed9                system2
                0x00404efa                system3
                0x0040591f                DialogBox
                0x00406965                api_get_current_keyboard_responder
                0x00406654                apiCreateProcess
                0x0040620e                APIGetFocus
                0x00404f7e                system7
                0x00404f5d                system6
                0x00406909                apiDefDialog
                0x00405892                mbProcedure
                0x0040618a                APICloseWindow
                0x00406f19                apiSendMessage
                0x004068a0                initializeCriticalSection
                0x00404fe1                system10
                0x00405303                set_cursor
                0x00406391                APImaximize_window
                0x00406a8e                execve
                0x0040651b                refresh_screen
                0x00406b49                apiDisplayBMP
                0x0040602b                call_gui
                0x00404fc0                system9
                0x00406a62                fork
                0x0040693c                api_set_current_keyboard_responder
                0x00406316                APIresize_window
                0x004068d6                apiEndPaint
                0x00405332                put_char
                0x0040523e                print_string
                0x00407022                apiGetSysTimeInfo
                0x004065ff                apiGetClientAreaRect
                0x00405274                edit_box
                0x0040648c                kill
                0x00406551                apiReboot
                0x00405360                apiShutDown
                0x00406991                api_set_current_mouse_responder
                0x0040640c                APIget_foregroung_window
                0x00404f1b                system4
                0x00406709                apiSaveFile
                0x0040657d                apiSetCursor
                0x00405023                system12
                0x00405243                vsync
                0x00404f9f                system8
                0x004069e6                api_set_window_with_text_input
                0x004062be                APIGetActiveWindow
                0x004063e3                APIupdate_window
                0x004069ba                api_get_current_mouse_responder
                0x00406491                dead_thread_collector
                0x004066a6                apiStartThread
                0x0040623a                APIKillFocus
                0x00406438                APIset_foregroung_window
                0x004068e0                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407050      0xfb0 00

.rdata          0x00408000      0xc90
 .rdata         0x00408000      0x3e0 api.o
 .rdata         0x004083e0      0x460 stdlib.o
 .rdata         0x00408840      0x340 stdio.o
                0x004089e0                hex2ascii_data
 .rdata         0x00408b80       0xe0 main.o
 .rdata         0x00408c60       0x30 crt0.o

.data           0x00408c90     0x1370
                0x00408c90                data = .
                0x00408c90                _data = .
                0x00408c90                __data = .
 *(.data)
 .data          0x00408c90        0x0 crt0.o
 .data          0x00408c90      0x440 main.o
 .data          0x004090d0      0x120 ctype.o
                0x004090d0                _ctype_
 .data          0x004091f0        0x0 stdio.o
 .data          0x004091f0        0x0 stdlib.o
 .data          0x004091f0        0x0 string.o
 .data          0x004091f0      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409630      0x9d0 00

.bss            0x0040a000     0xa6f0
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
 .bss           0x00412030       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xd40 crt0.o
                0x00413000                prompt
                0x00413400                stderr
                0x00413410                prompt_pos
                0x00413420                g_using_gui
                0x00413430                stdin
                0x00413440                prompt_max
                0x00413450                prompt_err
                0x00413850                g_columns
                0x00413860                stdout
                0x00413870                Streams
                0x004138f0                g_rows
                0x00413900                prompt_out
                0x00413d00                g_cursor_y
                0x00413d10                prompt_status
                0x00413d20                g_char_attrib
                0x00413d30                g_cursor_x
 COMMON         0x00413d40       0x70 main.o
                0x00413d40                ClientAreaInfo
                0x00413d50                BufferInfo
                0x00413d60                rect
                0x00413d70                CurrentWindow
                0x00413d80                current_semaphore
                0x00413d90                CursorInfo
                0x00413da0                ApplicationInfo
 COMMON         0x00413db0      0x900 stdlib.o
                0x00413db0                current_mmblock
                0x00413dc0                mm_prev_pointer
                0x00413dd0                heap_end
                0x00413de0                g_available_heap
                0x00413df0                heap_start
                0x00413e00                heapCount
                0x00413e10                HEAP_START
                0x00413e20                g_heap_pointer
                0x00413e30                heapList
                0x00414230                randseed
                0x00414240                HEAP_SIZE
                0x00414250                last_size
                0x00414260                last_valid
                0x00414270                mmblockList
                0x00414670                libcHeap
                0x00414680                Heap
                0x00414690                mmblockCount
                0x004146a0                HEAP_END
 COMMON         0x004146b0       0x40 api.o
                0x004146b0                messagebox_button2
                0x004146c0                dialogbox_button1
                0x004146d0                messagebox_button1
                0x004146e0                dialogbox_button2
                0x004146f0                end = .
                0x004146f0                _end = .
                0x004146f0                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD api.o
OUTPUT(FCLASS.BIN pe-i386)
