
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
STACK_PRE           0x80              main.o
current_mmblock     0x10              stdlib.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
STACK_OPERAND       0x80              main.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
pre_offset          0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
STACK_OPERATOR      0x80              main.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
operand_offset      0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
Streams             0x80              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
operator_offset     0x10              main.o
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

.text           0x00401000     0x8000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038     0x1050 main.o
                0x004019aa                idleInit
                0x00401038                newNode
                0x004010c0                exibirEmOrdem
                0x00401109                exibirPreOrdem
                0x0040126c                insert
                0x00401dd9                TEST_PRINTF3
                0x004019c8                idleServices
                0x00401964                driverInitialize
                0x00401a32                testtest_main
                0x00401a77                TEST_PRINTF
                0x00401376                resolve_expressao
                0x0040195f                idleLoop
                0x00401080                inorder
                0x00401d1e                TEST_PRINTF2
                0x00401987                driverUninitialize
                0x0040166c                bst_main
                0x00401220                imprimeEmNotacaoPolonesa
                0x00401310                height
                0x004011d7                exibirPosOrdem
 .text          0x00402088     0x2a00 stdio.o
                0x00402a95                printf_i2hex
                0x00402cc7                putchar
                0x0040213d                stdio_fntos
                0x00402c83                sprintf
                0x00403528                feof
                0x00402b03                printf2
                0x0040364e                stdioSetCursor
                0x0040343d                ungetc
                0x00404a44                rewind
                0x004024a6                puts
                0x00403606                fputc
                0x004036a4                stdioGetCursorY
                0x004036d0                scanf
                0x00403353                fputs
                0x00403566                ferror
                0x00402ea9                input
                0x004023e4                scroll
                0x004033c8                gets
                0x00402cf3                outbyte
                0x004034a4                fileno
                0x0040324c                fflush
                0x004032de                fprintf
                0x00404a02                stderr_printf
                0x00403011                stdio_system_call
                0x004022a2                fopen
                0x00403678                stdioGetCursorX
                0x00403039                getchar
                0x004029a8                printf_atoi
                0x00402088                stdio_atoi
                0x00403980                kvprintf
                0x004049d3                stdout_printf
                0x00403065                stdioInitialize
                0x004034c7                fgetc
                0x0040223c                fclose
                0x0040358c                fseek
                0x00404a31                perror
                0x00402e76                _outbyte
                0x0040347a                ftell
                0x0040490f                printf
                0x0040298d                printf3
                0x00404947                vfprintf
 .text          0x00404a88      0xc60 stdlib.o
                0x00404d7e                FreeHeap
                0x00404ab0                rtGetHeapStart
                0x0040508b                free
                0x00404a88                stdlib_system_call
                0x00404fb4                rand
                0x00404f2b                stdlibInitMM
                0x00404d88                heapInit
                0x00405525                __findenv
                0x00404ac4                rtGetHeapPointer
                0x00404ace                rtGetAvailableHeap
                0x00404fd1                srand
                0x00405625                atoi
                0x00404f8b                libcInitRT
                0x00404ad8                heapSetLibcHeap
                0x00405009                stdlib_die
                0x004055f0                getenv
                0x0040504a                malloc
                0x00404d6b                AllocateHeapEx
                0x00404b7f                AllocateHeap
                0x0040549c                stdlib_strncmp
                0x00404fde                xmalloc
                0x004054fa                exit
                0x00404aba                rtGetHeapEnd
                0x00405090                system
 .text          0x004056e8        0x0 ctype.o
 .text          0x004056e8      0x430 string.o
                0x004058d4                strcspn
                0x00405837                strcat
                0x004056e8                strcmp
                0x0040588e                bzero
                0x00405a14                strtok_r
                0x004057ca                memcpy
                0x004057a1                memoryZeroMemory
                0x00405867                bcopy
                0x00405807                strcpy
                0x00405974                strspn
                0x00405ae9                strtok
                0x00405743                strncmp
                0x004058a9                strlen
 .text          0x00405b18     0x2600 api.o
                0x00407388                APIShowCurrentProcessInfo
                0x00407bbb                api_getchar
                0x004060ba                system11
                0x0040615f                refresh_buffer
                0x0040726a                APISetFocus
                0x0040611d                system14
                0x00406446                apiInitBackground
                0x0040715a                APICreateWindow
                0x0040796a                apiBeginPaint
                0x0040644b                MessageBox
                0x00407406                APIreplace_window
                0x004079b1                apiGetSystemMetrics
                0x004060fc                system13
                0x00407805                apiDown
                0x00406ebc                dbProcedure
                0x004074ff                apiExit
                0x004078b9                enterCriticalSection
                0x00407af6                gramadocore_init_execve
                0x0040776d                apiFOpen
                0x004080e9                apiShowWindow
                0x00405f70                system1
                0x00405ff4                system5
                0x004075e5                api_refresh_screen
                0x00407b36                apiDialog
                0x00407671                apiGetCursorY
                0x004063ef                carrega_bitmap_16x16
                0x00407912                exitCriticalSection
                0x00405b18                system_call
                0x0040785f                apiUp
                0x00405b40                apiSystem
                0x00407aca                api_get_window_with_text_input
                0x0040803f                apiGetWSScreenWindow
                0x0040613e                system15
                0x0040731a                APISetActiveWindow
                0x004076c9                apiSetClientAreaRect
                0x00407ff8                apiDrawText
                0x004073dd                APIredraw_window
                0x0040771b                apiCreateThread
                0x0040638b                SetNextWindowProcedure
                0x00408097                apiCreateTimer
                0x00407645                apiGetCursorX
                0x0040635b                chama_procedimento
                0x00406f49                call_kernel
                0x004071e6                APIRegisterWindow
                0x0040806b                apiGetWSMainWindow
                0x0040755b                api_strncmp
                0x00407458                APIminimize_window
                0x00405f91                system2
                0x00405fb2                system3
                0x004069ca                DialogBox
                0x00407a03                api_get_current_keyboard_responder
                0x004076f2                apiCreateProcess
                0x004072ac                APIGetFocus
                0x00406036                system7
                0x00406015                system6
                0x004079a7                apiDefDialog
                0x0040693d                mbProcedure
                0x00407228                APICloseWindow
                0x00407fb7                apiSendMessage
                0x0040793e                initializeCriticalSection
                0x00406099                system10
                0x004063bb                set_cursor
                0x0040742f                APImaximize_window
                0x00407b2c                execve
                0x004075b9                refresh_screen
                0x00407be7                apiDisplayBMP
                0x004070c9                call_gui
                0x00406078                system9
                0x00407b00                fork
                0x004079da                api_set_current_keyboard_responder
                0x004073b4                APIresize_window
                0x00407974                apiEndPaint
                0x004063ea                put_char
                0x004062f6                print_string
                0x004080c0                apiGetSysTimeInfo
                0x0040769d                apiGetClientAreaRect
                0x0040632c                edit_box
                0x0040752a                kill
                0x004075ef                apiReboot
                0x00406418                apiShutDown
                0x00407a2f                api_set_current_mouse_responder
                0x004074aa                APIget_foregroung_window
                0x00405fd3                system4
                0x004077a7                apiSaveFile
                0x0040761b                apiSetCursor
                0x004060db                system12
                0x004062fb                vsync
                0x00406057                system8
                0x00407a84                api_set_window_with_text_input
                0x0040735c                APIGetActiveWindow
                0x00407481                APIupdate_window
                0x00407a58                api_get_current_mouse_responder
                0x0040752f                dead_thread_collector
                0x00407744                apiStartThread
                0x004072d8                APIKillFocus
                0x004074d6                APIset_foregroung_window
                0x0040797e                apiPutChar
                0x00409000                . = ALIGN (0x1000)
 *fill*         0x00408118      0xee8 00

.rdata          0x00409000     0x1040
 .rdata         0x00409000      0x3a0 api.o
 .rdata         0x004093a0      0x100 ctype.o
                0x004093a0                _ctype
 .rdata         0x004094a0      0x480 stdlib.o
 .rdata         0x00409920      0x380 stdio.o
                0x00409b00                hex2ascii_data
 .rdata         0x00409ca0      0x3a0 main.o

.data           0x0040a040      0xfc0
                0x0040a040                data = .
                0x0040a040                _data = .
                0x0040a040                __data = .
 *(.data)
 .data          0x0040a040        0x0 main.o
 .data          0x0040a040        0x0 stdio.o
 .data          0x0040a040        0x0 stdlib.o
 .data          0x0040a040        0x0 ctype.o
 .data          0x0040a040        0x0 string.o
 .data          0x0040a040      0x440 api.o
                0x0040b000                . = ALIGN (0x1000)
 *fill*         0x0040a480      0xb80 00

.bss            0x0040b000     0xa8e0
                0x0040b000                bss = .
                0x0040b000                _bss = .
                0x0040b000                __bss = .
 *(.bss)
 .bss           0x0040b000        0x0 main.o
 .bss           0x0040b000       0x10 stdio.o
 .bss           0x0040b010     0x8010 stdlib.o
                0x0040b010                environ
 .bss           0x00413020        0x0 ctype.o
 .bss           0x00413020       0x10 string.o
 .bss           0x00413030       0x40 api.o
                0x00414000                . = ALIGN (0x1000)
 *fill*         0x00413070      0xf90 00
 COMMON         0x00414000      0xfa0 main.o
                0x00414000                prompt
                0x00414400                idleStatus
                0x00414410                ClientAreaInfo
                0x00414420                BufferInfo
                0x00414430                driverInitialized
                0x00414440                key_saved
                0x00414450                stderr
                0x00414460                prompt_pos
                0x00414470                STACK_PRE
                0x004144f0                g_using_gui
                0x00414500                stdin
                0x00414510                STACK_OPERAND
                0x00414590                rect
                0x004145a0                prompt_max
                0x004145b0                pre_offset
                0x004145c0                CurrentWindow
                0x004145d0                STACK_OPERATOR
                0x00414650                prompt_err
                0x00414a50                current_semaphore
                0x00414a60                g_columns
                0x00414a70                operand_offset
                0x00414a80                stdout
                0x00414a90                Streams
                0x00414b10                g_rows
                0x00414b20                operator_offset
                0x00414b30                prompt_out
                0x00414f30                g_cursor_y
                0x00414f40                CursorInfo
                0x00414f50                prompt_status
                0x00414f60                g_char_attrib
                0x00414f70                ApplicationInfo
                0x00414f80                idleError
                0x00414f90                g_cursor_x
 COMMON         0x00414fa0      0x900 stdlib.o
                0x00414fa0                current_mmblock
                0x00414fb0                mm_prev_pointer
                0x00414fc0                heap_end
                0x00414fd0                g_available_heap
                0x00414fe0                heap_start
                0x00414ff0                heapCount
                0x00415000                HEAP_START
                0x00415010                g_heap_pointer
                0x00415020                heapList
                0x00415420                randseed
                0x00415430                HEAP_SIZE
                0x00415440                last_size
                0x00415450                last_valid
                0x00415460                mmblockList
                0x00415860                libcHeap
                0x00415870                Heap
                0x00415880                mmblockCount
                0x00415890                HEAP_END
 COMMON         0x004158a0       0x40 api.o
                0x004158a0                messagebox_button2
                0x004158b0                dialogbox_button1
                0x004158c0                messagebox_button1
                0x004158d0                dialogbox_button2
                0x004158e0                end = .
                0x004158e0                _end = .
                0x004158e0                __end = .
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
