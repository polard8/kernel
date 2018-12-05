
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
 .text          0x00401038      0xb30 main.o
                0x00401487                idleInit
                0x00401038                newNode
                0x004010c0                exibirEmOrdem
                0x00401109                exibirPreOrdem
                0x0040119b                insert
                0x004018b6                TEST_PRINTF3
                0x004014a5                idleServices
                0x00401441                driverInitialize
                0x0040150f                testtest_main
                0x00401554                TEST_PRINTF
                0x0040143c                idleLoop
                0x00401080                inorder
                0x004017fb                TEST_PRINTF2
                0x00401464                driverUninitialize
                0x004012a2                bst_main
                0x00401152                exibirPosOrdem
 .text          0x00401b68     0x2a00 stdio.o
                0x00402575                printf_i2hex
                0x004027a7                putchar
                0x00401c1d                stdio_fntos
                0x00402763                sprintf
                0x00403008                feof
                0x004025e3                printf2
                0x0040312e                stdioSetCursor
                0x00402f1d                ungetc
                0x00404524                rewind
                0x00401f86                puts
                0x004030e6                fputc
                0x00403184                stdioGetCursorY
                0x004031b0                scanf
                0x00402e33                fputs
                0x00403046                ferror
                0x00402989                input
                0x00401ec4                scroll
                0x00402ea8                gets
                0x004027d3                outbyte
                0x00402f84                fileno
                0x00402d2c                fflush
                0x00402dbe                fprintf
                0x004044e2                stderr_printf
                0x00402af1                stdio_system_call
                0x00401d82                fopen
                0x00403158                stdioGetCursorX
                0x00402b19                getchar
                0x00402488                printf_atoi
                0x00401b68                stdio_atoi
                0x00403460                kvprintf
                0x004044b3                stdout_printf
                0x00402b45                stdioInitialize
                0x00402fa7                fgetc
                0x00401d1c                fclose
                0x0040306c                fseek
                0x00404511                perror
                0x00402956                _outbyte
                0x00402f5a                ftell
                0x004043ef                printf
                0x0040246d                printf3
                0x00404427                vfprintf
 .text          0x00404568      0xc60 stdlib.o
                0x0040485e                FreeHeap
                0x00404590                rtGetHeapStart
                0x00404b6b                free
                0x00404568                stdlib_system_call
                0x00404a94                rand
                0x00404a0b                stdlibInitMM
                0x00404868                heapInit
                0x00405005                __findenv
                0x004045a4                rtGetHeapPointer
                0x004045ae                rtGetAvailableHeap
                0x00404ab1                srand
                0x00405105                atoi
                0x00404a6b                libcInitRT
                0x004045b8                heapSetLibcHeap
                0x00404ae9                stdlib_die
                0x004050d0                getenv
                0x00404b2a                malloc
                0x0040484b                AllocateHeapEx
                0x0040465f                AllocateHeap
                0x00404f7c                stdlib_strncmp
                0x00404abe                xmalloc
                0x00404fda                exit
                0x0040459a                rtGetHeapEnd
                0x00404b70                system
 .text          0x004051c8        0x0 ctype.o
 .text          0x004051c8      0x430 string.o
                0x004053b4                strcspn
                0x00405317                strcat
                0x004051c8                strcmp
                0x0040536e                bzero
                0x004054f4                strtok_r
                0x004052aa                memcpy
                0x00405281                memoryZeroMemory
                0x00405347                bcopy
                0x004052e7                strcpy
                0x00405454                strspn
                0x004055c9                strtok
                0x00405223                strncmp
                0x00405389                strlen
 .text          0x004055f8     0x2600 api.o
                0x00406e68                APIShowCurrentProcessInfo
                0x0040769b                api_getchar
                0x00405b9a                system11
                0x00405c3f                refresh_buffer
                0x00406d4a                APISetFocus
                0x00405bfd                system14
                0x00405f26                apiInitBackground
                0x00406c3a                APICreateWindow
                0x0040744a                apiBeginPaint
                0x00405f2b                MessageBox
                0x00406ee6                APIreplace_window
                0x00407491                apiGetSystemMetrics
                0x00405bdc                system13
                0x004072e5                apiDown
                0x0040699c                dbProcedure
                0x00406fdf                apiExit
                0x00407399                enterCriticalSection
                0x004075d6                gramadocore_init_execve
                0x0040724d                apiFOpen
                0x00407bc9                apiShowWindow
                0x00405a50                system1
                0x00405ad4                system5
                0x004070c5                api_refresh_screen
                0x00407616                apiDialog
                0x00407151                apiGetCursorY
                0x00405ecf                carrega_bitmap_16x16
                0x004073f2                exitCriticalSection
                0x004055f8                system_call
                0x0040733f                apiUp
                0x00405620                apiSystem
                0x004075aa                api_get_window_with_text_input
                0x00407b1f                apiGetWSScreenWindow
                0x00405c1e                system15
                0x00406dfa                APISetActiveWindow
                0x004071a9                apiSetClientAreaRect
                0x00407ad8                apiDrawText
                0x00406ebd                APIredraw_window
                0x004071fb                apiCreateThread
                0x00405e6b                SetNextWindowProcedure
                0x00407b77                apiCreateTimer
                0x00407125                apiGetCursorX
                0x00405e3b                chama_procedimento
                0x00406a29                call_kernel
                0x00406cc6                APIRegisterWindow
                0x00407b4b                apiGetWSMainWindow
                0x0040703b                api_strncmp
                0x00406f38                APIminimize_window
                0x00405a71                system2
                0x00405a92                system3
                0x004064aa                DialogBox
                0x004074e3                api_get_current_keyboard_responder
                0x004071d2                apiCreateProcess
                0x00406d8c                APIGetFocus
                0x00405b16                system7
                0x00405af5                system6
                0x00407487                apiDefDialog
                0x0040641d                mbProcedure
                0x00406d08                APICloseWindow
                0x00407a97                apiSendMessage
                0x0040741e                initializeCriticalSection
                0x00405b79                system10
                0x00405e9b                set_cursor
                0x00406f0f                APImaximize_window
                0x0040760c                execve
                0x00407099                refresh_screen
                0x004076c7                apiDisplayBMP
                0x00406ba9                call_gui
                0x00405b58                system9
                0x004075e0                fork
                0x004074ba                api_set_current_keyboard_responder
                0x00406e94                APIresize_window
                0x00407454                apiEndPaint
                0x00405eca                put_char
                0x00405dd6                print_string
                0x00407ba0                apiGetSysTimeInfo
                0x0040717d                apiGetClientAreaRect
                0x00405e0c                edit_box
                0x0040700a                kill
                0x004070cf                apiReboot
                0x00405ef8                apiShutDown
                0x0040750f                api_set_current_mouse_responder
                0x00406f8a                APIget_foregroung_window
                0x00405ab3                system4
                0x00407287                apiSaveFile
                0x004070fb                apiSetCursor
                0x00405bbb                system12
                0x00405ddb                vsync
                0x00405b37                system8
                0x00407564                api_set_window_with_text_input
                0x00406e3c                APIGetActiveWindow
                0x00406f61                APIupdate_window
                0x00407538                api_get_current_mouse_responder
                0x0040700f                dead_thread_collector
                0x00407224                apiStartThread
                0x00406db8                APIKillFocus
                0x00406fb6                APIset_foregroung_window
                0x0040745e                apiPutChar
                0x00408000                . = ALIGN (0x1000)
 *fill*         0x00407bf8      0x408 00

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
