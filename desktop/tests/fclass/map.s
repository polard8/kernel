
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

.text           0x00401000     0x5000
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
 .text          0x00401380     0x13f0 stdio.o
                0x00401c26                putchar
                0x00401380                stdio_fntos
                0x00401be2                sprintf
                0x00402354                feof
                0x0040247a                stdioSetCursor
                0x004022b6                ungetc
                0x004016e0                puts
                0x00402432                fputc
                0x004024d0                stdioGetCursorY
                0x004025b1                scanf
                0x004021cc                fputs
                0x00402392                ferror
                0x00401e08                input
                0x0040161e                scroll
                0x00402241                gets
                0x00401c52                outbyte
                0x004020e8                fflush
                0x00402157                fprintf
                0x00401f70                stdio_system_call
                0x004014e5                fopen
                0x004024a4                stdioGetCursorX
                0x00401f98                getchar
                0x004024fc                stdio_atoi
                0x00401fc4                stdioInitialize
                0x004022f3                fgetc
                0x0040147f                fclose
                0x004023b8                fseek
                0x00401dd5                _outbyte
                0x00401bc7                printf
 .text          0x00402770      0xb40 stdlib.o
                0x00402a66                FreeHeap
                0x00402798                rtGetHeapStart
                0x00402d07                free
                0x00402770                stdlib_system_call
                0x00402c9c                rand
                0x00402c13                stdlibInitMM
                0x00402a70                heapInit
                0x004031a1                __findenv
                0x004027ac                rtGetHeapPointer
                0x004027b6                rtGetAvailableHeap
                0x00402cb9                srand
                0x00402c73                libcInitRT
                0x004027c0                heapSetLibcHeap
                0x0040326c                getenv
                0x00402cc6                malloc
                0x00402a53                AllocateHeapEx
                0x00402867                AllocateHeap
                0x00403118                stdlib_strncmp
                0x00403176                exit
                0x004027a2                rtGetHeapEnd
                0x00402d0c                system
 .text          0x004032b0      0x430 string.o
                0x0040349c                strcspn
                0x004033ff                strcat
                0x004032b0                strcmp
                0x00403456                bzero
                0x004035dc                strtok_r
                0x00403392                memcpy
                0x00403369                memoryZeroMemory
                0x0040342f                bcopy
                0x004033cf                strcpy
                0x0040353c                strspn
                0x004036b1                strtok
                0x0040330b                strncmp
                0x00403471                strlen
 .text          0x004036e0     0x25f0 api.o
                0x00404f6a                APIShowCurrentProcessInfo
                0x0040579d                api_getchar
                0x00403c82                system11
                0x00403d27                refresh_buffer
                0x00404e4c                APISetFocus
                0x00403ce5                system14
                0x0040400e                apiInitBackground
                0x00404d3c                APICreateWindow
                0x0040554c                apiBeginPaint
                0x00404013                MessageBox
                0x00404fe8                APIreplace_window
                0x00405593                apiGetSystemMetrics
                0x00403cc4                system13
                0x004053e7                apiDown
                0x00404a9e                dbProcedure
                0x004050e1                apiExit
                0x0040549b                enterCriticalSection
                0x004056d8                gramadocore_init_execve
                0x0040534f                apiFOpen
                0x00403b38                system1
                0x00403bbc                system5
                0x004051c7                api_refresh_screen
                0x00405718                apiDialog
                0x00405253                apiGetCursorY
                0x00403fb7                carrega_bitmap_16x16
                0x004054f4                exitCriticalSection
                0x004036e0                system_call
                0x00405441                apiUp
                0x00403708                apiSystem
                0x004056ac                api_get_window_with_text_input
                0x00405c21                apiGetWSScreenWindow
                0x00403d06                system15
                0x00404efc                APISetActiveWindow
                0x004052ab                apiSetClientAreaRect
                0x00405bda                apiDrawText
                0x00404fbf                APIredraw_window
                0x004052fd                apiCreateThread
                0x00403f53                SetNextWindowProcedure
                0x00405c79                apiCreateTimer
                0x00405227                apiGetCursorX
                0x00403f23                chama_procedimento
                0x00404b2b                call_kernel
                0x00404dc8                APIRegisterWindow
                0x00405c4d                apiGetWSMainWindow
                0x0040513d                api_strncmp
                0x0040503a                APIminimize_window
                0x00403b59                system2
                0x00403b7a                system3
                0x0040459f                DialogBox
                0x004055e5                api_get_current_keyboard_responder
                0x004052d4                apiCreateProcess
                0x00404e8e                APIGetFocus
                0x00403bfe                system7
                0x00403bdd                system6
                0x00405589                apiDefDialog
                0x00404512                mbProcedure
                0x00404e0a                APICloseWindow
                0x00405b99                apiSendMessage
                0x00405520                initializeCriticalSection
                0x00403c61                system10
                0x00403f83                set_cursor
                0x00405011                APImaximize_window
                0x0040570e                execve
                0x0040519b                refresh_screen
                0x004057c9                apiDisplayBMP
                0x00404cab                call_gui
                0x00403c40                system9
                0x004056e2                fork
                0x004055bc                api_set_current_keyboard_responder
                0x00404f96                APIresize_window
                0x00405556                apiEndPaint
                0x00403fb2                put_char
                0x00403ebe                print_string
                0x00405ca2                apiGetSysTimeInfo
                0x0040527f                apiGetClientAreaRect
                0x00403ef4                edit_box
                0x0040510c                kill
                0x004051d1                apiReboot
                0x00403fe0                apiShutDown
                0x00405611                api_set_current_mouse_responder
                0x0040508c                APIget_foregroung_window
                0x00403b9b                system4
                0x00405389                apiSaveFile
                0x004051fd                apiSetCursor
                0x00403ca3                system12
                0x00403ec3                vsync
                0x00403c1f                system8
                0x00405666                api_set_window_with_text_input
                0x00404f3e                APIGetActiveWindow
                0x00405063                APIupdate_window
                0x0040563a                api_get_current_mouse_responder
                0x00405111                dead_thread_collector
                0x00405326                apiStartThread
                0x00404eba                APIKillFocus
                0x004050b8                APIset_foregroung_window
                0x00405560                apiPutChar
                0x00406000                . = ALIGN (0x1000)
 *fill*         0x00405cd0      0x330 00

.rdata          0x00406000      0xa20
 .rdata         0x00406000      0x3e0 api.o
 .rdata         0x004063e0      0x460 stdlib.o
 .rdata         0x00406840       0xd0 stdio.o
 .rdata         0x00406910       0xe0 main.o
 .rdata         0x004069f0       0x30 crt0.o

.data           0x00406a20     0x15e0
                0x00406a20                data = .
                0x00406a20                _data = .
                0x00406a20                __data = .
 *(.data)
 .data          0x00406a20        0x0 crt0.o
 .data          0x00406a20      0x440 main.o
 .data          0x00406e60      0x120 ctype.o
                0x00406e60                _ctype_
 .data          0x00406f80        0x0 stdio.o
 .data          0x00406f80        0x0 stdlib.o
 .data          0x00406f80        0x0 string.o
 .data          0x00406f80      0x440 api.o
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004073c0      0xc40 00

.bss            0x00408000     0xa6f0
                0x00408000                bss = .
                0x00408000                _bss = .
                0x00408000                __bss = .
 *(.bss)
 .bss           0x00408000        0x0 crt0.o
 .bss           0x00408000        0x0 main.o
 .bss           0x00408000        0x0 ctype.o
 .bss           0x00408000       0x10 stdio.o
 .bss           0x00408010     0x8010 stdlib.o
                0x00408010                environ
 .bss           0x00410020       0x10 string.o
 .bss           0x00410030       0x40 api.o
                0x00411000                . = ALIGN (0x1000)
 *fill*         0x00410070      0xf90 00
 COMMON         0x00411000      0xd40 crt0.o
                0x00411000                prompt
                0x00411400                stderr
                0x00411410                prompt_pos
                0x00411420                g_using_gui
                0x00411430                stdin
                0x00411440                prompt_max
                0x00411450                prompt_err
                0x00411850                g_columns
                0x00411860                stdout
                0x00411870                Streams
                0x004118f0                g_rows
                0x00411900                prompt_out
                0x00411d00                g_cursor_y
                0x00411d10                prompt_status
                0x00411d20                g_char_attrib
                0x00411d30                g_cursor_x
 COMMON         0x00411d40       0x70 main.o
                0x00411d40                ClientAreaInfo
                0x00411d50                BufferInfo
                0x00411d60                rect
                0x00411d70                CurrentWindow
                0x00411d80                current_semaphore
                0x00411d90                CursorInfo
                0x00411da0                ApplicationInfo
 COMMON         0x00411db0      0x900 stdlib.o
                0x00411db0                current_mmblock
                0x00411dc0                mm_prev_pointer
                0x00411dd0                heap_end
                0x00411de0                g_available_heap
                0x00411df0                heap_start
                0x00411e00                heapCount
                0x00411e10                HEAP_START
                0x00411e20                g_heap_pointer
                0x00411e30                heapList
                0x00412230                randseed
                0x00412240                HEAP_SIZE
                0x00412250                last_size
                0x00412260                last_valid
                0x00412270                mmblockList
                0x00412670                libcHeap
                0x00412680                Heap
                0x00412690                mmblockCount
                0x004126a0                HEAP_END
 COMMON         0x004126b0       0x40 api.o
                0x004126b0                messagebox_button2
                0x004126c0                dialogbox_button1
                0x004126d0                messagebox_button1
                0x004126e0                dialogbox_button2
                0x004126f0                end = .
                0x004126f0                _end = .
                0x004126f0                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD api.o
OUTPUT(FCLASS.BIN pe-i386)
