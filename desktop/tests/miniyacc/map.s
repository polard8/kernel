
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
 .text          0x00404fb8     0x2a00 stdio.o
                0x004059c5                printf_i2hex
                0x00405bf7                putchar
                0x0040506d                stdio_fntos
                0x00405bb3                sprintf
                0x00406458                feof
                0x00405a33                printf2
                0x0040657e                stdioSetCursor
                0x0040636d                ungetc
                0x00407974                rewind
                0x004053d6                puts
                0x00406536                fputc
                0x004065d4                stdioGetCursorY
                0x00406600                scanf
                0x00406283                fputs
                0x00406496                ferror
                0x00405dd9                input
                0x00405314                scroll
                0x004062f8                gets
                0x00405c23                outbyte
                0x004063d4                fileno
                0x0040617c                fflush
                0x0040620e                fprintf
                0x00407932                stderr_printf
                0x00405f41                stdio_system_call
                0x004051d2                fopen
                0x004065a8                stdioGetCursorX
                0x00405f69                getchar
                0x004058d8                printf_atoi
                0x00404fb8                stdio_atoi
                0x004068b0                kvprintf
                0x00407903                stdout_printf
                0x00405f95                stdioInitialize
                0x004063f7                fgetc
                0x0040516c                fclose
                0x004064bc                fseek
                0x00407961                perror
                0x00405da6                _outbyte
                0x004063aa                ftell
                0x0040783f                printf
                0x004058bd                printf3
                0x00407877                vfprintf
 .text          0x004079b8      0xc60 stdlib.o
                0x00407cae                FreeHeap
                0x004079e0                rtGetHeapStart
                0x00407fbb                free
                0x004079b8                stdlib_system_call
                0x00407ee4                rand
                0x00407e5b                stdlibInitMM
                0x00407cb8                heapInit
                0x00408455                __findenv
                0x004079f4                rtGetHeapPointer
                0x004079fe                rtGetAvailableHeap
                0x00407f01                srand
                0x00408555                atoi
                0x00407ebb                libcInitRT
                0x00407a08                heapSetLibcHeap
                0x00407f39                stdlib_die
                0x00408520                getenv
                0x00407f7a                malloc
                0x00407c9b                AllocateHeapEx
                0x00407aaf                AllocateHeap
                0x004083cc                stdlib_strncmp
                0x00407f0e                xmalloc
                0x0040842a                exit
                0x004079ea                rtGetHeapEnd
                0x00407fc0                system
 .text          0x00408618        0x0 ctype.o
 .text          0x00408618      0x430 string.o
                0x00408804                strcspn
                0x00408767                strcat
                0x00408618                strcmp
                0x004087be                bzero
                0x00408944                strtok_r
                0x004086fa                memcpy
                0x004086d1                memoryZeroMemory
                0x00408797                bcopy
                0x00408737                strcpy
                0x004088a4                strspn
                0x00408a19                strtok
                0x00408673                strncmp
                0x004087d9                strlen
 .text          0x00408a48     0x2600 api.o
                0x0040a2b8                APIShowCurrentProcessInfo
                0x0040aaeb                api_getchar
                0x00408fea                system11
                0x0040908f                refresh_buffer
                0x0040a19a                APISetFocus
                0x0040904d                system14
                0x00409376                apiInitBackground
                0x0040a08a                APICreateWindow
                0x0040a89a                apiBeginPaint
                0x0040937b                MessageBox
                0x0040a336                APIreplace_window
                0x0040a8e1                apiGetSystemMetrics
                0x0040902c                system13
                0x0040a735                apiDown
                0x00409dec                dbProcedure
                0x0040a42f                apiExit
                0x0040a7e9                enterCriticalSection
                0x0040aa26                gramadocore_init_execve
                0x0040a69d                apiFOpen
                0x0040b019                apiShowWindow
                0x00408ea0                system1
                0x00408f24                system5
                0x0040a515                api_refresh_screen
                0x0040aa66                apiDialog
                0x0040a5a1                apiGetCursorY
                0x0040931f                carrega_bitmap_16x16
                0x0040a842                exitCriticalSection
                0x00408a48                system_call
                0x0040a78f                apiUp
                0x00408a70                apiSystem
                0x0040a9fa                api_get_window_with_text_input
                0x0040af6f                apiGetWSScreenWindow
                0x0040906e                system15
                0x0040a24a                APISetActiveWindow
                0x0040a5f9                apiSetClientAreaRect
                0x0040af28                apiDrawText
                0x0040a30d                APIredraw_window
                0x0040a64b                apiCreateThread
                0x004092bb                SetNextWindowProcedure
                0x0040afc7                apiCreateTimer
                0x0040a575                apiGetCursorX
                0x0040928b                chama_procedimento
                0x00409e79                call_kernel
                0x0040a116                APIRegisterWindow
                0x0040af9b                apiGetWSMainWindow
                0x0040a48b                api_strncmp
                0x0040a388                APIminimize_window
                0x00408ec1                system2
                0x00408ee2                system3
                0x004098fa                DialogBox
                0x0040a933                api_get_current_keyboard_responder
                0x0040a622                apiCreateProcess
                0x0040a1dc                APIGetFocus
                0x00408f66                system7
                0x00408f45                system6
                0x0040a8d7                apiDefDialog
                0x0040986d                mbProcedure
                0x0040a158                APICloseWindow
                0x0040aee7                apiSendMessage
                0x0040a86e                initializeCriticalSection
                0x00408fc9                system10
                0x004092eb                set_cursor
                0x0040a35f                APImaximize_window
                0x0040aa5c                execve
                0x0040a4e9                refresh_screen
                0x0040ab17                apiDisplayBMP
                0x00409ff9                call_gui
                0x00408fa8                system9
                0x0040aa30                fork
                0x0040a90a                api_set_current_keyboard_responder
                0x0040a2e4                APIresize_window
                0x0040a8a4                apiEndPaint
                0x0040931a                put_char
                0x00409226                print_string
                0x0040aff0                apiGetSysTimeInfo
                0x0040a5cd                apiGetClientAreaRect
                0x0040925c                edit_box
                0x0040a45a                kill
                0x0040a51f                apiReboot
                0x00409348                apiShutDown
                0x0040a95f                api_set_current_mouse_responder
                0x0040a3da                APIget_foregroung_window
                0x00408f03                system4
                0x0040a6d7                apiSaveFile
                0x0040a54b                apiSetCursor
                0x0040900b                system12
                0x0040922b                vsync
                0x00408f87                system8
                0x0040a9b4                api_set_window_with_text_input
                0x0040a28c                APIGetActiveWindow
                0x0040a3b1                APIupdate_window
                0x0040a988                api_get_current_mouse_responder
                0x0040a45f                dead_thread_collector
                0x0040a674                apiStartThread
                0x0040a208                APIKillFocus
                0x0040a406                APIset_foregroung_window
                0x0040a8ae                apiPutChar
                0x0040c000                . = ALIGN (0x1000)
 *fill*         0x0040b048      0xfb8 00

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

.bss            0x0040e000    0x6a0f0
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
 .bss           0x00416030       0x40 api.o
                0x00417000                . = ALIGN (0x1000)
 *fill*         0x00416070      0xf90 00
 COMMON         0x00417000    0x607b0 main.o
                0x00417000                ini
                0x00417010                prompt
                0x00417410                idleStatus
                0x00417420                st
                0x00417430                rrconf
                0x00417440                ClientAreaInfo
                0x00417450                BufferInfo
                0x00417460                ntk
                0x00417470                driverInitialized
                0x00417480                gdsp
                0x00417490                nsy
                0x004174a0                stderr
                0x004174b0                prompt_pos
                0x004174c0                srca
                0x004174d0                g_using_gui
                0x004174e0                srconf
                0x004174f0                stdin
                0x00417500                is
                0x004491e0                doty
                0x004491f0                rect
                0x00449200                nst
                0x00449210                prompt_max
                0x00449220                CurrentWindow
                0x00449230                prompt_err
                0x00449630                fgrm
                0x00449640                current_semaphore
                0x00449650                g_columns
                0x00449660                as
                0x00449670                fhdr
                0x00449680                stdout
                0x00449690                idnt
                0x004496d0                Streams
                0x00449750                adsp
                0x00449760                act
                0x00449770                g_rows
                0x00449780                fin
                0x00449790                prompt_out
                0x00449b90                i0
                0x0045b4e0                nrl
                0x0045b4f0                rs
                0x004776f0                fout
                0x00477700                chk
                0x00477710                sstart
                0x00477720                g_cursor_y
                0x00477730                CursorInfo
                0x00477740                gs
                0x00477750                prompt_status
                0x00477760                actsz
                0x00477770                g_char_attrib
                0x00477780                ApplicationInfo
                0x00477790                idleError
                0x004777a0                g_cursor_x
 COMMON         0x004777b0      0x900 stdlib.o
                0x004777b0                current_mmblock
                0x004777c0                mm_prev_pointer
                0x004777d0                heap_end
                0x004777e0                g_available_heap
                0x004777f0                heap_start
                0x00477800                heapCount
                0x00477810                HEAP_START
                0x00477820                g_heap_pointer
                0x00477830                heapList
                0x00477c30                randseed
                0x00477c40                HEAP_SIZE
                0x00477c50                last_size
                0x00477c60                last_valid
                0x00477c70                mmblockList
                0x00478070                libcHeap
                0x00478080                Heap
                0x00478090                mmblockCount
                0x004780a0                HEAP_END
 COMMON         0x004780b0       0x40 api.o
                0x004780b0                messagebox_button2
                0x004780c0                dialogbox_button1
                0x004780d0                messagebox_button1
                0x004780e0                dialogbox_button2
                0x004780f0                end = .
                0x004780f0                _end = .
                0x004780f0                __end = .
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
