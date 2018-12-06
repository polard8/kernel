
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
driverInitialized   0x10              main.o
key_saved           0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
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
dialogbox_button1   0x10              api.o
libcHeap            0x10              stdlib.o
g_cursor_y          0x10              main.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
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

.text           0x00401000     0x7000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038      0xcc0 main.o
                0x00401619                idleInit
                0x00401038                newNode
                0x004010c0                exibirEmOrdem
                0x00401109                exibirPreOrdem
                0x0040119b                insert
                0x00401a48                TEST_PRINTF3
                0x00401637                idleServices
                0x004015d3                driverInitialize
                0x004016a1                testtest_main
                0x004016e6                TEST_PRINTF
                0x00401293                resolve_expressao
                0x004015ce                idleLoop
                0x00401080                inorder
                0x0040198d                TEST_PRINTF2
                0x004015f6                driverUninitialize
                0x004013a9                bst_main
                0x0040123f                height
                0x00401152                exibirPosOrdem
 .text          0x00401cf8     0x2a00 stdio.o
                0x00402705                printf_i2hex
                0x00402937                putchar
                0x00401dad                stdio_fntos
                0x004028f3                sprintf
                0x00403198                feof
                0x00402773                printf2
                0x004032be                stdioSetCursor
                0x004030ad                ungetc
                0x004046b4                rewind
                0x00402116                puts
                0x00403276                fputc
                0x00403314                stdioGetCursorY
                0x00403340                scanf
                0x00402fc3                fputs
                0x004031d6                ferror
                0x00402b19                input
                0x00402054                scroll
                0x00403038                gets
                0x00402963                outbyte
                0x00403114                fileno
                0x00402ebc                fflush
                0x00402f4e                fprintf
                0x00404672                stderr_printf
                0x00402c81                stdio_system_call
                0x00401f12                fopen
                0x004032e8                stdioGetCursorX
                0x00402ca9                getchar
                0x00402618                printf_atoi
                0x00401cf8                stdio_atoi
                0x004035f0                kvprintf
                0x00404643                stdout_printf
                0x00402cd5                stdioInitialize
                0x00403137                fgetc
                0x00401eac                fclose
                0x004031fc                fseek
                0x004046a1                perror
                0x00402ae6                _outbyte
                0x004030ea                ftell
                0x0040457f                printf
                0x004025fd                printf3
                0x004045b7                vfprintf
 .text          0x004046f8      0xc60 stdlib.o
                0x004049ee                FreeHeap
                0x00404720                rtGetHeapStart
                0x00404cfb                free
                0x004046f8                stdlib_system_call
                0x00404c24                rand
                0x00404b9b                stdlibInitMM
                0x004049f8                heapInit
                0x00405195                __findenv
                0x00404734                rtGetHeapPointer
                0x0040473e                rtGetAvailableHeap
                0x00404c41                srand
                0x00405295                atoi
                0x00404bfb                libcInitRT
                0x00404748                heapSetLibcHeap
                0x00404c79                stdlib_die
                0x00405260                getenv
                0x00404cba                malloc
                0x004049db                AllocateHeapEx
                0x004047ef                AllocateHeap
                0x0040510c                stdlib_strncmp
                0x00404c4e                xmalloc
                0x0040516a                exit
                0x0040472a                rtGetHeapEnd
                0x00404d00                system
 .text          0x00405358        0x0 ctype.o
 .text          0x00405358      0x430 string.o
                0x00405544                strcspn
                0x004054a7                strcat
                0x00405358                strcmp
                0x004054fe                bzero
                0x00405684                strtok_r
                0x0040543a                memcpy
                0x00405411                memoryZeroMemory
                0x004054d7                bcopy
                0x00405477                strcpy
                0x004055e4                strspn
                0x00405759                strtok
                0x004053b3                strncmp
                0x00405519                strlen
 .text          0x00405788     0x2600 api.o
                0x00406ff8                APIShowCurrentProcessInfo
                0x0040782b                api_getchar
                0x00405d2a                system11
                0x00405dcf                refresh_buffer
                0x00406eda                APISetFocus
                0x00405d8d                system14
                0x004060b6                apiInitBackground
                0x00406dca                APICreateWindow
                0x004075da                apiBeginPaint
                0x004060bb                MessageBox
                0x00407076                APIreplace_window
                0x00407621                apiGetSystemMetrics
                0x00405d6c                system13
                0x00407475                apiDown
                0x00406b2c                dbProcedure
                0x0040716f                apiExit
                0x00407529                enterCriticalSection
                0x00407766                gramadocore_init_execve
                0x004073dd                apiFOpen
                0x00407d59                apiShowWindow
                0x00405be0                system1
                0x00405c64                system5
                0x00407255                api_refresh_screen
                0x004077a6                apiDialog
                0x004072e1                apiGetCursorY
                0x0040605f                carrega_bitmap_16x16
                0x00407582                exitCriticalSection
                0x00405788                system_call
                0x004074cf                apiUp
                0x004057b0                apiSystem
                0x0040773a                api_get_window_with_text_input
                0x00407caf                apiGetWSScreenWindow
                0x00405dae                system15
                0x00406f8a                APISetActiveWindow
                0x00407339                apiSetClientAreaRect
                0x00407c68                apiDrawText
                0x0040704d                APIredraw_window
                0x0040738b                apiCreateThread
                0x00405ffb                SetNextWindowProcedure
                0x00407d07                apiCreateTimer
                0x004072b5                apiGetCursorX
                0x00405fcb                chama_procedimento
                0x00406bb9                call_kernel
                0x00406e56                APIRegisterWindow
                0x00407cdb                apiGetWSMainWindow
                0x004071cb                api_strncmp
                0x004070c8                APIminimize_window
                0x00405c01                system2
                0x00405c22                system3
                0x0040663a                DialogBox
                0x00407673                api_get_current_keyboard_responder
                0x00407362                apiCreateProcess
                0x00406f1c                APIGetFocus
                0x00405ca6                system7
                0x00405c85                system6
                0x00407617                apiDefDialog
                0x004065ad                mbProcedure
                0x00406e98                APICloseWindow
                0x00407c27                apiSendMessage
                0x004075ae                initializeCriticalSection
                0x00405d09                system10
                0x0040602b                set_cursor
                0x0040709f                APImaximize_window
                0x0040779c                execve
                0x00407229                refresh_screen
                0x00407857                apiDisplayBMP
                0x00406d39                call_gui
                0x00405ce8                system9
                0x00407770                fork
                0x0040764a                api_set_current_keyboard_responder
                0x00407024                APIresize_window
                0x004075e4                apiEndPaint
                0x0040605a                put_char
                0x00405f66                print_string
                0x00407d30                apiGetSysTimeInfo
                0x0040730d                apiGetClientAreaRect
                0x00405f9c                edit_box
                0x0040719a                kill
                0x0040725f                apiReboot
                0x00406088                apiShutDown
                0x0040769f                api_set_current_mouse_responder
                0x0040711a                APIget_foregroung_window
                0x00405c43                system4
                0x00407417                apiSaveFile
                0x0040728b                apiSetCursor
                0x00405d4b                system12
                0x00405f6b                vsync
                0x00405cc7                system8
                0x004076f4                api_set_window_with_text_input
                0x00406fcc                APIGetActiveWindow
                0x004070f1                APIupdate_window
                0x004076c8                api_get_current_mouse_responder
                0x0040719f                dead_thread_collector
                0x004073b4                apiStartThread
                0x00406f48                APIKillFocus
                0x00407146                APIset_foregroung_window
                0x004075ee                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407d88      0x278 00

.rdata          0x00408000      0xf20
 .rdata         0x00408000      0x3a0 api.o
 .rdata         0x004083a0      0x100 ctype.o
                0x004083a0                _ctype
 .rdata         0x004084a0      0x480 stdlib.o
 .rdata         0x00408920      0x380 stdio.o
                0x00408b00                hex2ascii_data
 .rdata         0x00408ca0      0x280 main.o

.data           0x00408f20     0x10e0
                0x00408f20                data = .
                0x00408f20                _data = .
                0x00408f20                __data = .
 *(.data)
 .data          0x00408f20        0x0 main.o
 .data          0x00408f20        0x0 stdio.o
 .data          0x00408f20        0x0 stdlib.o
 .data          0x00408f20        0x0 ctype.o
 .data          0x00408f20        0x0 string.o
 .data          0x00408f20      0x440 api.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409360      0xca0 00

.bss            0x0040a000     0xa730
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000        0x0 main.o
 .bss           0x0040a000       0x10 stdio.o
 .bss           0x0040a010     0x8010 stdlib.o
                0x0040a010                environ
 .bss           0x00412020        0x0 ctype.o
 .bss           0x00412020       0x10 string.o
 .bss           0x00412030       0x40 api.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412070      0xf90 00
 COMMON         0x00413000      0xdf0 main.o
                0x00413000                prompt
                0x00413400                idleStatus
                0x00413410                ClientAreaInfo
                0x00413420                BufferInfo
                0x00413430                driverInitialized
                0x00413440                key_saved
                0x00413450                stderr
                0x00413460                prompt_pos
                0x00413470                g_using_gui
                0x00413480                stdin
                0x00413490                rect
                0x004134a0                prompt_max
                0x004134b0                CurrentWindow
                0x004134c0                prompt_err
                0x004138c0                current_semaphore
                0x004138d0                g_columns
                0x004138e0                stdout
                0x004138f0                Streams
                0x00413970                g_rows
                0x00413980                prompt_out
                0x00413d80                g_cursor_y
                0x00413d90                CursorInfo
                0x00413da0                prompt_status
                0x00413db0                g_char_attrib
                0x00413dc0                ApplicationInfo
                0x00413dd0                idleError
                0x00413de0                g_cursor_x
 COMMON         0x00413df0      0x900 stdlib.o
                0x00413df0                current_mmblock
                0x00413e00                mm_prev_pointer
                0x00413e10                heap_end
                0x00413e20                g_available_heap
                0x00413e30                heap_start
                0x00413e40                heapCount
                0x00413e50                HEAP_START
                0x00413e60                g_heap_pointer
                0x00413e70                heapList
                0x00414270                randseed
                0x00414280                HEAP_SIZE
                0x00414290                last_size
                0x004142a0                last_valid
                0x004142b0                mmblockList
                0x004146b0                libcHeap
                0x004146c0                Heap
                0x004146d0                mmblockCount
                0x004146e0                HEAP_END
 COMMON         0x004146f0       0x40 api.o
                0x004146f0                messagebox_button2
                0x00414700                dialogbox_button1
                0x00414710                messagebox_button1
                0x00414720                dialogbox_button2
                0x00414730                end = .
                0x00414730                _end = .
                0x00414730                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TBST2.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
