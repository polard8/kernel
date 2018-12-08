
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
 .text          0x00401038     0x1230 main.o
                0x0040114a                insertnum
                0x00401b92                idleInit
                0x00401423                newNode
                0x004010ea                insertsign
                0x004014ab                exibirEmOrdem
                0x004014f4                exibirPreOrdem
                0x00401657                insert
                0x00401fc1                TEST_PRINTF3
                0x00401bb0                idleServices
                0x00401b4c                driverInitialize
                0x00401c1a                testtest_main
                0x00401c5f                TEST_PRINTF
                0x00401761                resolve_expressao
                0x00401b47                idleLoop
                0x0040146b                inorder
                0x00401f06                TEST_PRINTF2
                0x00401b6f                driverUninitialize
                0x004010ad                posordem
                0x00401854                bst_main
                0x0040160b                imprimeEmNotacaoPolonesa
                0x00401038                emordem
                0x004016fb                height
                0x0040122f                main2
                0x004015c2                exibirPosOrdem
 .text          0x00402268     0x2a10 stdio.o
                0x00402c75                printf_i2hex
                0x00402ea7                putchar
                0x0040231d                stdio_fntos
                0x00402e63                sprintf
                0x00403720                feof
                0x00402ce3                printf2
                0x00403846                stdioSetCursor
                0x00403635                ungetc
                0x00404c3c                rewind
                0x00402686                puts
                0x004037fe                fputc
                0x0040389c                stdioGetCursorY
                0x004038c8                scanf
                0x00403533                fputs
                0x0040375e                ferror
                0x00403089                input
                0x004025c4                scroll
                0x004035a8                gets
                0x00402ed3                outbyte
                0x0040369c                fileno
                0x0040342c                fflush
                0x004034be                fprintf
                0x00404bfa                stderr_printf
                0x004031f1                stdio_system_call
                0x00402482                fopen
                0x00403870                stdioGetCursorX
                0x00403219                getchar
                0x00402b88                printf_atoi
                0x00402268                stdio_atoi
                0x00403b78                kvprintf
                0x00404bcb                stdout_printf
                0x00403245                stdioInitialize
                0x004036bf                fgetc
                0x0040241c                fclose
                0x00403784                fseek
                0x00404c29                perror
                0x00403056                _outbyte
                0x00403672                ftell
                0x00404b07                printf
                0x00402b6d                printf3
                0x00404b3f                vfprintf
 .text          0x00404c78      0xc60 stdlib.o
                0x00404f6e                FreeHeap
                0x00404ca0                rtGetHeapStart
                0x0040527b                free
                0x00404c78                stdlib_system_call
                0x004051a4                rand
                0x0040511b                stdlibInitMM
                0x00404f78                heapInit
                0x00405715                __findenv
                0x00404cb4                rtGetHeapPointer
                0x00404cbe                rtGetAvailableHeap
                0x004051c1                srand
                0x00405815                atoi
                0x0040517b                libcInitRT
                0x00404cc8                heapSetLibcHeap
                0x004051f9                stdlib_die
                0x004057e0                getenv
                0x0040523a                malloc
                0x00404f5b                AllocateHeapEx
                0x00404d6f                AllocateHeap
                0x0040568c                stdlib_strncmp
                0x004051ce                xmalloc
                0x004056ea                exit
                0x00404caa                rtGetHeapEnd
                0x00405280                system
 .text          0x004058d8        0x0 ctype.o
 .text          0x004058d8      0x430 string.o
                0x00405ac4                strcspn
                0x00405a27                strcat
                0x004058d8                strcmp
                0x00405a7e                bzero
                0x00405c04                strtok_r
                0x004059ba                memcpy
                0x00405991                memoryZeroMemory
                0x00405a57                bcopy
                0x004059f7                strcpy
                0x00405b64                strspn
                0x00405cd9                strtok
                0x00405933                strncmp
                0x00405a99                strlen
 .text          0x00405d08     0x2600 api.o
                0x00407578                APIShowCurrentProcessInfo
                0x00407dab                api_getchar
                0x004062aa                system11
                0x0040634f                refresh_buffer
                0x0040745a                APISetFocus
                0x0040630d                system14
                0x00406636                apiInitBackground
                0x0040734a                APICreateWindow
                0x00407b5a                apiBeginPaint
                0x0040663b                MessageBox
                0x004075f6                APIreplace_window
                0x00407ba1                apiGetSystemMetrics
                0x004062ec                system13
                0x004079f5                apiDown
                0x004070ac                dbProcedure
                0x004076ef                apiExit
                0x00407aa9                enterCriticalSection
                0x00407ce6                gramadocore_init_execve
                0x0040795d                apiFOpen
                0x004082d9                apiShowWindow
                0x00406160                system1
                0x004061e4                system5
                0x004077d5                api_refresh_screen
                0x00407d26                apiDialog
                0x00407861                apiGetCursorY
                0x004065df                carrega_bitmap_16x16
                0x00407b02                exitCriticalSection
                0x00405d08                system_call
                0x00407a4f                apiUp
                0x00405d30                apiSystem
                0x00407cba                api_get_window_with_text_input
                0x0040822f                apiGetWSScreenWindow
                0x0040632e                system15
                0x0040750a                APISetActiveWindow
                0x004078b9                apiSetClientAreaRect
                0x004081e8                apiDrawText
                0x004075cd                APIredraw_window
                0x0040790b                apiCreateThread
                0x0040657b                SetNextWindowProcedure
                0x00408287                apiCreateTimer
                0x00407835                apiGetCursorX
                0x0040654b                chama_procedimento
                0x00407139                call_kernel
                0x004073d6                APIRegisterWindow
                0x0040825b                apiGetWSMainWindow
                0x0040774b                api_strncmp
                0x00407648                APIminimize_window
                0x00406181                system2
                0x004061a2                system3
                0x00406bba                DialogBox
                0x00407bf3                api_get_current_keyboard_responder
                0x004078e2                apiCreateProcess
                0x0040749c                APIGetFocus
                0x00406226                system7
                0x00406205                system6
                0x00407b97                apiDefDialog
                0x00406b2d                mbProcedure
                0x00407418                APICloseWindow
                0x004081a7                apiSendMessage
                0x00407b2e                initializeCriticalSection
                0x00406289                system10
                0x004065ab                set_cursor
                0x0040761f                APImaximize_window
                0x00407d1c                execve
                0x004077a9                refresh_screen
                0x00407dd7                apiDisplayBMP
                0x004072b9                call_gui
                0x00406268                system9
                0x00407cf0                fork
                0x00407bca                api_set_current_keyboard_responder
                0x004075a4                APIresize_window
                0x00407b64                apiEndPaint
                0x004065da                put_char
                0x004064e6                print_string
                0x004082b0                apiGetSysTimeInfo
                0x0040788d                apiGetClientAreaRect
                0x0040651c                edit_box
                0x0040771a                kill
                0x004077df                apiReboot
                0x00406608                apiShutDown
                0x00407c1f                api_set_current_mouse_responder
                0x0040769a                APIget_foregroung_window
                0x004061c3                system4
                0x00407997                apiSaveFile
                0x0040780b                apiSetCursor
                0x004062cb                system12
                0x004064eb                vsync
                0x00406247                system8
                0x00407c74                api_set_window_with_text_input
                0x0040754c                APIGetActiveWindow
                0x00407671                APIupdate_window
                0x00407c48                api_get_current_mouse_responder
                0x0040771f                dead_thread_collector
                0x00407934                apiStartThread
                0x004074c8                APIKillFocus
                0x004076c6                APIset_foregroung_window
                0x00407b6e                apiPutChar
                0x00409000                . = ALIGN (0x1000)
 *fill*         0x00408308      0xcf8 00

.rdata          0x00409000     0x11a0
 .rdata         0x00409000      0x3a0 api.o
 .rdata         0x004093a0      0x100 ctype.o
                0x004093a0                _ctype
 .rdata         0x004094a0      0x480 stdlib.o
 .rdata         0x00409920      0x380 stdio.o
                0x00409b00                hex2ascii_data
 .rdata         0x00409ca0      0x500 main.o

.data           0x0040a1a0      0xe60
                0x0040a1a0                data = .
                0x0040a1a0                _data = .
                0x0040a1a0                __data = .
 *(.data)
 .data          0x0040a1a0        0x0 main.o
 .data          0x0040a1a0        0x0 stdio.o
 .data          0x0040a1a0        0x0 stdlib.o
 .data          0x0040a1a0        0x0 ctype.o
 .data          0x0040a1a0        0x0 string.o
 .data          0x0040a1a0      0x440 api.o
                0x0040b000                . = ALIGN (0x1000)
 *fill*         0x0040a5e0      0xa20 00

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
OUTPUT(TBST3.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
