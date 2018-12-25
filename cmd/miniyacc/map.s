
Allocating common symbols
Common symbol       size              file

ini                 0x10              main.o
prompt              0x400             main.o
idleStatus          0x10              main.o
st                  0x10              main.o
rrconf              0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
ntk                 0x10              main.o
driverInitialized   0x10              main.o
gdsp                0x10              main.o
nsy                 0x10              main.o
stderr              0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
srca                0x10              main.o
mm_prev_pointer     0x10              stdlib.o
messagebox_button2  0x10              api.o
g_using_gui         0x10              main.o
srconf              0x10              main.o
stdin               0x10              main.o
heap_end            0x10              stdlib.o
is                  0x31ce0           main.o
doty                0x10              main.o
rect                0x10              main.o
g_available_heap    0x10              stdlib.o
nst                 0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
HEAP_START          0x10              stdlib.o
prompt_max          0x10              main.o
CurrentWindow       0x10              main.o
g_heap_pointer      0x10              stdlib.o
heapList            0x400             stdlib.o
prompt_err          0x400             main.o
randseed            0x10              stdlib.o
fgrm                0x10              main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
as                  0x10              main.o
fhdr                0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stdout              0x10              main.o
idnt                0x40              main.o
Streams             0x80              main.o
adsp                0x10              main.o
act                 0x10              main.o
last_size           0x10              stdlib.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
fin                 0x10              main.o
prompt_out          0x400             main.o
mmblockList         0x400             stdlib.o
dialogbox_button1   0x10              api.o
i0                  0x11950           main.o
nrl                 0x10              main.o
rs                  0x1c200           main.o
libcHeap            0x10              stdlib.o
fout                0x10              main.o
chk                 0x10              main.o
sstart              0x10              main.o
g_cursor_y          0x10              main.o
messagebox_button1  0x10              api.o
Heap                0x10              stdlib.o
dialogbox_button2   0x10              api.o
CursorInfo          0x10              main.o
gs                  0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
actsz               0x10              main.o
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

.text           0x00401000     0xb000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038     0x3f80 main.o
                0x00401e07                tblset
                0x00401423                iclose
                0x004048d5                idleInit
                0x004045cf                newNode
                0x0040208b                setdef
                0x004023dd                prcmp
                0x00404644                exibirEmOrdem
                0x00404683                exibirPreOrdem
                0x00404701                insert
                0x00404d04                TEST_PRINTF3
                0x004021a1                tblgen
                0x00401149                tszero
                0x00404530                miniyacc_main
                0x00401038                die
                0x004048f3                idleServices
                0x00401baa                stgen
                0x00402e9d                stdump
                0x0040116c                tsunion
                0x0040175b                igoto
                0x004042cf                init
                0x0040488f                driverInitialize
                0x0040495d                testtest_main
                0x004011f1                first
                0x00401812                icmp
                0x00403619                findsy
                0x004049a2                TEST_PRINTF
                0x004013cf                tcmp
                0x00403e4f                actout
                0x0040488a                idleLoop
                0x004010b2                rfind
                0x00404605                inorder
                0x00404c49                TEST_PRINTF2
                0x004023f4                actgen
                0x004048b2                driverUninitialize
                0x004029ed                tblout
                0x00402916                aout
                0x0040106f                yalloc
                0x00401d2c                resolve
                0x00401124                slen
                0x0040417e                codeout
                0x00401409                tcmpv
                0x0040348a                cpycode
                0x00404779                bst_main
                0x004018ff                stadd
                0x00403b96                getgram
                0x00403723                getdecls
                0x00403234                istok
                0x004046c2                exibirPosOrdem
                0x004035ac                gettype
                0x004010a1                rcmp
                0x004012e2                ginit
                0x0040326f                nexttk
 .text          0x00404fb8     0x2a10 stdio.o
                0x004059c5                printf_i2hex
                0x00405bf7                putchar
                0x0040506d                stdio_fntos
                0x00405bb3                sprintf
                0x00406470                feof
                0x00405a33                printf2
                0x00406596                stdioSetCursor
                0x00406385                ungetc
                0x0040798c                rewind
                0x004053d6                puts
                0x0040654e                fputc
                0x004065ec                stdioGetCursorY
                0x00406618                scanf
                0x00406283                fputs
                0x004064ae                ferror
                0x00405dd9                input
                0x00405314                scroll
                0x004062f8                gets
                0x00405c23                outbyte
                0x004063ec                fileno
                0x0040617c                fflush
                0x0040620e                fprintf
                0x0040794a                stderr_printf
                0x00405f41                stdio_system_call
                0x004051d2                fopen
                0x004065c0                stdioGetCursorX
                0x00405f69                getchar
                0x004058d8                printf_atoi
                0x00404fb8                stdio_atoi
                0x004068c8                kvprintf
                0x0040791b                stdout_printf
                0x00405f95                stdioInitialize
                0x0040640f                fgetc
                0x0040516c                fclose
                0x004064d4                fseek
                0x00407979                perror
                0x00405da6                _outbyte
                0x004063c2                ftell
                0x00407857                printf
                0x004058bd                printf3
                0x0040788f                vfprintf
 .text          0x004079c8      0xc60 stdlib.o
                0x00407cbe                FreeHeap
                0x004079f0                rtGetHeapStart
                0x00407fcb                free
                0x004079c8                stdlib_system_call
                0x00407ef4                rand
                0x00407e6b                stdlibInitMM
                0x00407cc8                heapInit
                0x00408465                __findenv
                0x00407a04                rtGetHeapPointer
                0x00407a0e                rtGetAvailableHeap
                0x00407f11                srand
                0x00408565                atoi
                0x00407ecb                libcInitRT
                0x00407a18                heapSetLibcHeap
                0x00407f49                stdlib_die
                0x00408530                getenv
                0x00407f8a                malloc
                0x00407cab                AllocateHeapEx
                0x00407abf                AllocateHeap
                0x004083dc                stdlib_strncmp
                0x00407f1e                xmalloc
                0x0040843a                exit
                0x004079fa                rtGetHeapEnd
                0x00407fd0                system
 .text          0x00408628        0x0 ctype.o
 .text          0x00408628      0x430 string.o
                0x00408814                strcspn
                0x00408777                strcat
                0x00408628                strcmp
                0x004087ce                bzero
                0x00408954                strtok_r
                0x0040870a                memcpy
                0x004086e1                memoryZeroMemory
                0x004087a7                bcopy
                0x00408747                strcpy
                0x004088b4                strspn
                0x00408a29                strtok
                0x00408683                strncmp
                0x004087e9                strlen
 .text          0x00408a58     0x2600 api.o
                0x0040a2c8                APIShowCurrentProcessInfo
                0x0040aafb                api_getchar
                0x00408ffa                system11
                0x0040909f                refresh_buffer
                0x0040a1aa                APISetFocus
                0x0040905d                system14
                0x00409386                apiInitBackground
                0x0040a09a                APICreateWindow
                0x0040a8aa                apiBeginPaint
                0x0040938b                MessageBox
                0x0040a346                APIreplace_window
                0x0040a8f1                apiGetSystemMetrics
                0x0040903c                system13
                0x0040a745                apiDown
                0x00409dfc                dbProcedure
                0x0040a43f                apiExit
                0x0040a7f9                enterCriticalSection
                0x0040aa36                gramadocore_init_execve
                0x0040a6ad                apiFOpen
                0x0040b029                apiShowWindow
                0x00408eb0                system1
                0x00408f34                system5
                0x0040a525                api_refresh_screen
                0x0040aa76                apiDialog
                0x0040a5b1                apiGetCursorY
                0x0040932f                carrega_bitmap_16x16
                0x0040a852                exitCriticalSection
                0x00408a58                system_call
                0x0040a79f                apiUp
                0x00408a80                apiSystem
                0x0040aa0a                api_get_window_with_text_input
                0x0040af7f                apiGetWSScreenWindow
                0x0040907e                system15
                0x0040a25a                APISetActiveWindow
                0x0040a609                apiSetClientAreaRect
                0x0040af38                apiDrawText
                0x0040a31d                APIredraw_window
                0x0040a65b                apiCreateThread
                0x004092cb                SetNextWindowProcedure
                0x0040afd7                apiCreateTimer
                0x0040a585                apiGetCursorX
                0x0040929b                chama_procedimento
                0x00409e89                call_kernel
                0x0040a126                APIRegisterWindow
                0x0040afab                apiGetWSMainWindow
                0x0040a49b                api_strncmp
                0x0040a398                APIminimize_window
                0x00408ed1                system2
                0x00408ef2                system3
                0x0040990a                DialogBox
                0x0040a943                api_get_current_keyboard_responder
                0x0040a632                apiCreateProcess
                0x0040a1ec                APIGetFocus
                0x00408f76                system7
                0x00408f55                system6
                0x0040a8e7                apiDefDialog
                0x0040987d                mbProcedure
                0x0040a168                APICloseWindow
                0x0040aef7                apiSendMessage
                0x0040a87e                initializeCriticalSection
                0x00408fd9                system10
                0x004092fb                set_cursor
                0x0040a36f                APImaximize_window
                0x0040aa6c                execve
                0x0040a4f9                refresh_screen
                0x0040ab27                apiDisplayBMP
                0x0040a009                call_gui
                0x00408fb8                system9
                0x0040aa40                fork
                0x0040a91a                api_set_current_keyboard_responder
                0x0040a2f4                APIresize_window
                0x0040a8b4                apiEndPaint
                0x0040932a                put_char
                0x00409236                print_string
                0x0040b000                apiGetSysTimeInfo
                0x0040a5dd                apiGetClientAreaRect
                0x0040926c                edit_box
                0x0040a46a                kill
                0x0040a52f                apiReboot
                0x00409358                apiShutDown
                0x0040a96f                api_set_current_mouse_responder
                0x0040a3ea                APIget_foregroung_window
                0x00408f13                system4
                0x0040a6e7                apiSaveFile
                0x0040a55b                apiSetCursor
                0x0040901b                system12
                0x0040923b                vsync
                0x00408f97                system8
                0x0040a9c4                api_set_window_with_text_input
                0x0040a29c                APIGetActiveWindow
                0x0040a3c1                APIupdate_window
                0x0040a998                api_get_current_mouse_responder
                0x0040a46f                dead_thread_collector
                0x0040a684                apiStartThread
                0x0040a218                APIKillFocus
                0x0040a416                APIset_foregroung_window
                0x0040a8be                apiPutChar
                0x0040c000                . = ALIGN (0x1000)
 *fill*         0x0040b058      0xfa8 00

.rdata          0x0040c000     0x19b0
 .rdata         0x0040c000      0x3a0 api.o
 .rdata         0x0040c3a0      0x100 ctype.o
                0x0040c3a0                _ctype
 .rdata         0x0040c4a0      0x480 stdlib.o
 .rdata         0x0040c920      0x380 stdio.o
                0x0040cb00                hex2ascii_data
 .rdata         0x0040cca0      0xd10 main.o

.data           0x0040d9b0      0x650
                0x0040d9b0                data = .
                0x0040d9b0                _data = .
                0x0040d9b0                __data = .
 *(.data)
 .data          0x0040d9b0      0x200 main.o
                0x0040d9b0                srs
                0x0040da80                retcode
                0x0040da90                code0
                0x0040d9f0                rrs
                0x0040da1c                lineno
                0x0040da30                words
                0x0040db88                code1
 .data          0x0040dbb0        0x0 stdio.o
 .data          0x0040dbb0        0x0 stdlib.o
 .data          0x0040dbb0        0x0 ctype.o
 .data          0x0040dbb0        0x0 string.o
 .data          0x0040dbb0      0x440 api.o
                0x0040e000                . = ALIGN (0x1000)
 *fill*         0x0040dff0       0x10 00

.bss            0x0040e000    0x720f0
                0x0040e000                bss = .
                0x0040e000                _bss = .
                0x0040e000                __bss = .
 *(.bss)
 .bss           0x0040e000        0x0 main.o
 .bss           0x0040e000       0x10 stdio.o
 .bss           0x0040e010     0x8010 stdlib.o
                0x0040e010                environ
 .bss           0x00416020        0x0 ctype.o
 .bss           0x00416020       0x10 string.o
 .bss           0x00416030     0x8010 api.o
                0x0041f000                . = ALIGN (0x1000)
 *fill*         0x0041e040      0xfc0 00
 COMMON         0x0041f000    0x607b0 main.o
                0x0041f000                ini
                0x0041f010                prompt
                0x0041f410                idleStatus
                0x0041f420                st
                0x0041f430                rrconf
                0x0041f440                ClientAreaInfo
                0x0041f450                BufferInfo
                0x0041f460                ntk
                0x0041f470                driverInitialized
                0x0041f480                gdsp
                0x0041f490                nsy
                0x0041f4a0                stderr
                0x0041f4b0                prompt_pos
                0x0041f4c0                srca
                0x0041f4d0                g_using_gui
                0x0041f4e0                srconf
                0x0041f4f0                stdin
                0x0041f500                is
                0x004511e0                doty
                0x004511f0                rect
                0x00451200                nst
                0x00451210                prompt_max
                0x00451220                CurrentWindow
                0x00451230                prompt_err
                0x00451630                fgrm
                0x00451640                current_semaphore
                0x00451650                g_columns
                0x00451660                as
                0x00451670                fhdr
                0x00451680                stdout
                0x00451690                idnt
                0x004516d0                Streams
                0x00451750                adsp
                0x00451760                act
                0x00451770                g_rows
                0x00451780                fin
                0x00451790                prompt_out
                0x00451b90                i0
                0x004634e0                nrl
                0x004634f0                rs
                0x0047f6f0                fout
                0x0047f700                chk
                0x0047f710                sstart
                0x0047f720                g_cursor_y
                0x0047f730                CursorInfo
                0x0047f740                gs
                0x0047f750                prompt_status
                0x0047f760                actsz
                0x0047f770                g_char_attrib
                0x0047f780                ApplicationInfo
                0x0047f790                idleError
                0x0047f7a0                g_cursor_x
 COMMON         0x0047f7b0      0x900 stdlib.o
                0x0047f7b0                current_mmblock
                0x0047f7c0                mm_prev_pointer
                0x0047f7d0                heap_end
                0x0047f7e0                g_available_heap
                0x0047f7f0                heap_start
                0x0047f800                heapCount
                0x0047f810                HEAP_START
                0x0047f820                g_heap_pointer
                0x0047f830                heapList
                0x0047fc30                randseed
                0x0047fc40                HEAP_SIZE
                0x0047fc50                last_size
                0x0047fc60                last_valid
                0x0047fc70                mmblockList
                0x00480070                libcHeap
                0x00480080                Heap
                0x00480090                mmblockCount
                0x004800a0                HEAP_END
 COMMON         0x004800b0       0x40 api.o
                0x004800b0                messagebox_button2
                0x004800c0                dialogbox_button1
                0x004800d0                messagebox_button1
                0x004800e0                dialogbox_button2
                0x004800f0                end = .
                0x004800f0                _end = .
                0x004800f0                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(MINIYACC.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
