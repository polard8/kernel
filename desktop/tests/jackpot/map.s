
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
 .text          0x004013e0     0x2a00 stdio.o
                0x00401ded                printf_i2hex
                0x0040201f                putchar
                0x00401495                stdio_fntos
                0x00401fdb                sprintf
                0x00402880                feof
                0x00401e5b                printf2
                0x004029a6                stdioSetCursor
                0x00402795                ungetc
                0x00403d9c                rewind
                0x004017fe                puts
                0x0040295e                fputc
                0x004029fc                stdioGetCursorY
                0x00402a28                scanf
                0x004026ab                fputs
                0x004028be                ferror
                0x00402201                input
                0x0040173c                scroll
                0x00402720                gets
                0x0040204b                outbyte
                0x004027fc                fileno
                0x004025a4                fflush
                0x00402636                fprintf
                0x00403d5a                stderr_printf
                0x00402369                stdio_system_call
                0x004015fa                fopen
                0x004029d0                stdioGetCursorX
                0x00402391                getchar
                0x00401d00                printf_atoi
                0x004013e0                stdio_atoi
                0x00402cd8                kvprintf
                0x00403d2b                stdout_printf
                0x004023bd                stdioInitialize
                0x0040281f                fgetc
                0x00401594                fclose
                0x004028e4                fseek
                0x00403d89                perror
                0x004021ce                _outbyte
                0x004027d2                ftell
                0x00403c67                printf
                0x00401ce5                printf3
                0x00403c9f                vfprintf
 .text          0x00403de0      0xc60 stdlib.o
                0x004040d6                FreeHeap
                0x00403e08                rtGetHeapStart
                0x004043e3                free
                0x00403de0                stdlib_system_call
                0x0040430c                rand
                0x00404283                stdlibInitMM
                0x004040e0                heapInit
                0x0040487d                __findenv
                0x00403e1c                rtGetHeapPointer
                0x00403e26                rtGetAvailableHeap
                0x00404329                srand
                0x0040497d                atoi
                0x004042e3                libcInitRT
                0x00403e30                heapSetLibcHeap
                0x00404361                stdlib_die
                0x00404948                getenv
                0x004043a2                malloc
                0x004040c3                AllocateHeapEx
                0x00403ed7                AllocateHeap
                0x004047f4                stdlib_strncmp
                0x00404336                xmalloc
                0x00404852                exit
                0x00403e12                rtGetHeapEnd
                0x004043e8                system
 .text          0x00404a40      0x430 string.o
                0x00404c2c                strcspn
                0x00404b8f                strcat
                0x00404a40                strcmp
                0x00404be6                bzero
                0x00404d6c                strtok_r
                0x00404b22                memcpy
                0x00404af9                memoryZeroMemory
                0x00404bbf                bcopy
                0x00404b5f                strcpy
                0x00404ccc                strspn
                0x00404e41                strtok
                0x00404a9b                strncmp
                0x00404c01                strlen
 .text          0x00404e70       0x70 time.o
                0x00404eaa                time_system_call
                0x00404e70                time
 .text          0x00404ee0     0x2600 api.o
                0x00406750                APIShowCurrentProcessInfo
                0x00406f83                api_getchar
                0x00405482                system11
                0x00405527                refresh_buffer
                0x00406632                APISetFocus
                0x004054e5                system14
                0x0040580e                apiInitBackground
                0x00406522                APICreateWindow
                0x00406d32                apiBeginPaint
                0x00405813                MessageBox
                0x004067ce                APIreplace_window
                0x00406d79                apiGetSystemMetrics
                0x004054c4                system13
                0x00406bcd                apiDown
                0x00406284                dbProcedure
                0x004068c7                apiExit
                0x00406c81                enterCriticalSection
                0x00406ebe                gramadocore_init_execve
                0x00406b35                apiFOpen
                0x004074b1                apiShowWindow
                0x00405338                system1
                0x004053bc                system5
                0x004069ad                api_refresh_screen
                0x00406efe                apiDialog
                0x00406a39                apiGetCursorY
                0x004057b7                carrega_bitmap_16x16
                0x00406cda                exitCriticalSection
                0x00404ee0                system_call
                0x00406c27                apiUp
                0x00404f08                apiSystem
                0x00406e92                api_get_window_with_text_input
                0x00407407                apiGetWSScreenWindow
                0x00405506                system15
                0x004066e2                APISetActiveWindow
                0x00406a91                apiSetClientAreaRect
                0x004073c0                apiDrawText
                0x004067a5                APIredraw_window
                0x00406ae3                apiCreateThread
                0x00405753                SetNextWindowProcedure
                0x0040745f                apiCreateTimer
                0x00406a0d                apiGetCursorX
                0x00405723                chama_procedimento
                0x00406311                call_kernel
                0x004065ae                APIRegisterWindow
                0x00407433                apiGetWSMainWindow
                0x00406923                api_strncmp
                0x00406820                APIminimize_window
                0x00405359                system2
                0x0040537a                system3
                0x00405d92                DialogBox
                0x00406dcb                api_get_current_keyboard_responder
                0x00406aba                apiCreateProcess
                0x00406674                APIGetFocus
                0x004053fe                system7
                0x004053dd                system6
                0x00406d6f                apiDefDialog
                0x00405d05                mbProcedure
                0x004065f0                APICloseWindow
                0x0040737f                apiSendMessage
                0x00406d06                initializeCriticalSection
                0x00405461                system10
                0x00405783                set_cursor
                0x004067f7                APImaximize_window
                0x00406ef4                execve
                0x00406981                refresh_screen
                0x00406faf                apiDisplayBMP
                0x00406491                call_gui
                0x00405440                system9
                0x00406ec8                fork
                0x00406da2                api_set_current_keyboard_responder
                0x0040677c                APIresize_window
                0x00406d3c                apiEndPaint
                0x004057b2                put_char
                0x004056be                print_string
                0x00407488                apiGetSysTimeInfo
                0x00406a65                apiGetClientAreaRect
                0x004056f4                edit_box
                0x004068f2                kill
                0x004069b7                apiReboot
                0x004057e0                apiShutDown
                0x00406df7                api_set_current_mouse_responder
                0x00406872                APIget_foregroung_window
                0x0040539b                system4
                0x00406b6f                apiSaveFile
                0x004069e3                apiSetCursor
                0x004054a3                system12
                0x004056c3                vsync
                0x0040541f                system8
                0x00406e4c                api_set_window_with_text_input
                0x00406724                APIGetActiveWindow
                0x00406849                APIupdate_window
                0x00406e20                api_get_current_mouse_responder
                0x004068f7                dead_thread_collector
                0x00406b0c                apiStartThread
                0x004066a0                APIKillFocus
                0x0040689e                APIset_foregroung_window
                0x00406d46                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x004074e0      0xb20 00

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

.bss            0x0040a000     0xa750
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
 .bss           0x00412030       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xda0 main.o
                0x00413000                j
                0x00413010                prompt
                0x00413410                number
                0x00413420                i
                0x00413430                stderr
                0x00413440                prompt_pos
                0x00413450                g_using_gui
                0x00413460                stdin
                0x00413470                prompt_max
                0x00413480                prompt_err
                0x00413880                maxrand
                0x00413890                g_columns
                0x004138a0                stdout
                0x004138b0                Streams
                0x00413930                g_rows
                0x00413940                prompt_out
                0x00413d40                c
                0x00413d50                g_cursor_y
                0x00413d60                life
                0x00413d70                prompt_status
                0x00413d80                g_char_attrib
                0x00413d90                g_cursor_x
 COMMON         0x00413da0      0x900 stdlib.o
                0x00413da0                current_mmblock
                0x00413db0                mm_prev_pointer
                0x00413dc0                heap_end
                0x00413dd0                g_available_heap
                0x00413de0                heap_start
                0x00413df0                heapCount
                0x00413e00                HEAP_START
                0x00413e10                g_heap_pointer
                0x00413e20                heapList
                0x00414220                randseed
                0x00414230                HEAP_SIZE
                0x00414240                last_size
                0x00414250                last_valid
                0x00414260                mmblockList
                0x00414660                libcHeap
                0x00414670                Heap
                0x00414680                mmblockCount
                0x00414690                HEAP_END
 COMMON         0x004146a0       0xb0 api.o
                0x004146a0                ClientAreaInfo
                0x004146b0                BufferInfo
                0x004146c0                messagebox_button2
                0x004146d0                rect
                0x004146e0                CurrentWindow
                0x004146f0                current_semaphore
                0x00414700                dialogbox_button1
                0x00414710                messagebox_button1
                0x00414720                CursorInfo
                0x00414730                dialogbox_button2
                0x00414740                ApplicationInfo
                0x00414750                end = .
                0x00414750                _end = .
                0x00414750                __end = .
LOAD main.o
LOAD ctype.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
OUTPUT(JACKPOT.BIN pe-i386)
