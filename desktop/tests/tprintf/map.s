
Allocating common symbols
Common symbol       size              file

prompt              0x400             main.o
idleStatus          0x10              main.o
ClientAreaInfo      0x10              main.o
BufferInfo          0x10              main.o
driverInitialized   0x10              main.o
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

.text           0x00401000     0x6000
                0x00401000                code = .
                0x00401000                _code = .
                0x00401000                __code = .
 *(.head_x86)
 .head_x86      0x00401000       0x35 head.o
                0x00401000                idle_entry_point
 *(.text)
 *fill*         0x00401035        0x3 00
 .text          0x00401038      0x660 main.o
                0x00401083                idleInit
                0x004010a1                idleServices
                0x0040103d                driverInitialize
                0x0040110b                testtest_main
                0x00401146                TEST_PRINTF
                0x00401038                idleLoop
                0x004013ed                TEST_PRINTF2
                0x00401060                driverUninitialize
 .text          0x00401698     0x16e0 stdio.o
                0x00401fe7                printf_i2hex
                0x00402231                putchar
                0x00401698                stdio_fntos
                0x004021ed                sprintf
                0x0040295f                feof
                0x00402055                printf2
                0x00402a85                stdioSetCursor
                0x004028c1                ungetc
                0x004019f8                puts
                0x00402a3d                fputc
                0x00402adb                stdioGetCursorY
                0x00402bbc                scanf
                0x004027d7                fputs
                0x0040299d                ferror
                0x00402413                input
                0x00401936                scroll
                0x0040284c                gets
                0x0040225d                outbyte
                0x004026f3                fflush
                0x00402762                fprintf
                0x0040257b                stdio_system_call
                0x004017fd                fopen
                0x00402aaf                stdioGetCursorX
                0x004025a3                getchar
                0x00401efa                printf_atoi
                0x00402b07                stdio_atoi
                0x004025cf                stdioInitialize
                0x004028fe                fgetc
                0x00401797                fclose
                0x004029c3                fseek
                0x004023e0                _outbyte
                0x00401edf                printf
 .text          0x00402d78      0xb40 stdlib.o
                0x0040306e                FreeHeap
                0x00402da0                rtGetHeapStart
                0x0040330f                free
                0x00402d78                stdlib_system_call
                0x004032a4                rand
                0x0040321b                stdlibInitMM
                0x00403078                heapInit
                0x004037a9                __findenv
                0x00402db4                rtGetHeapPointer
                0x00402dbe                rtGetAvailableHeap
                0x004032c1                srand
                0x0040327b                libcInitRT
                0x00402dc8                heapSetLibcHeap
                0x00403874                getenv
                0x004032ce                malloc
                0x0040305b                AllocateHeapEx
                0x00402e6f                AllocateHeap
                0x00403720                stdlib_strncmp
                0x0040377e                exit
                0x00402daa                rtGetHeapEnd
                0x00403314                system
 .text          0x004038b8       0xe0 ctype.o
                0x00403952                isspace
                0x00403978                isxdigit
                0x00403965                isupper
                0x004038cb                isalpha
                0x00403917                islower
                0x004038b8                isalnum
                0x0040392a                isprint
                0x00403904                isgraph
                0x004038f1                isdigit
                0x004038de                iscntrl
                0x0040393f                ispunct
 .text          0x00403998      0x430 string.o
                0x00403b84                strcspn
                0x00403ae7                strcat
                0x00403998                strcmp
                0x00403b3e                bzero
                0x00403cc4                strtok_r
                0x00403a7a                memcpy
                0x00403a51                memoryZeroMemory
                0x00403b17                bcopy
                0x00403ab7                strcpy
                0x00403c24                strspn
                0x00403d99                strtok
                0x004039f3                strncmp
                0x00403b59                strlen
 .text          0x00403dc8     0x25f0 api.o
                0x00405652                APIShowCurrentProcessInfo
                0x00405e85                api_getchar
                0x0040436a                system11
                0x0040440f                refresh_buffer
                0x00405534                APISetFocus
                0x004043cd                system14
                0x004046f6                apiInitBackground
                0x00405424                APICreateWindow
                0x00405c34                apiBeginPaint
                0x004046fb                MessageBox
                0x004056d0                APIreplace_window
                0x00405c7b                apiGetSystemMetrics
                0x004043ac                system13
                0x00405acf                apiDown
                0x00405186                dbProcedure
                0x004057c9                apiExit
                0x00405b83                enterCriticalSection
                0x00405dc0                gramadocore_init_execve
                0x00405a37                apiFOpen
                0x00404220                system1
                0x004042a4                system5
                0x004058af                api_refresh_screen
                0x00405e00                apiDialog
                0x0040593b                apiGetCursorY
                0x0040469f                carrega_bitmap_16x16
                0x00405bdc                exitCriticalSection
                0x00403dc8                system_call
                0x00405b29                apiUp
                0x00403df0                apiSystem
                0x00405d94                api_get_window_with_text_input
                0x00406309                apiGetWSScreenWindow
                0x004043ee                system15
                0x004055e4                APISetActiveWindow
                0x00405993                apiSetClientAreaRect
                0x004062c2                apiDrawText
                0x004056a7                APIredraw_window
                0x004059e5                apiCreateThread
                0x0040463b                SetNextWindowProcedure
                0x00406361                apiCreateTimer
                0x0040590f                apiGetCursorX
                0x0040460b                chama_procedimento
                0x00405213                call_kernel
                0x004054b0                APIRegisterWindow
                0x00406335                apiGetWSMainWindow
                0x00405825                api_strncmp
                0x00405722                APIminimize_window
                0x00404241                system2
                0x00404262                system3
                0x00404c87                DialogBox
                0x00405ccd                api_get_current_keyboard_responder
                0x004059bc                apiCreateProcess
                0x00405576                APIGetFocus
                0x004042e6                system7
                0x004042c5                system6
                0x00405c71                apiDefDialog
                0x00404bfa                mbProcedure
                0x004054f2                APICloseWindow
                0x00406281                apiSendMessage
                0x00405c08                initializeCriticalSection
                0x00404349                system10
                0x0040466b                set_cursor
                0x004056f9                APImaximize_window
                0x00405df6                execve
                0x00405883                refresh_screen
                0x00405eb1                apiDisplayBMP
                0x00405393                call_gui
                0x00404328                system9
                0x00405dca                fork
                0x00405ca4                api_set_current_keyboard_responder
                0x0040567e                APIresize_window
                0x00405c3e                apiEndPaint
                0x0040469a                put_char
                0x004045a6                print_string
                0x0040638a                apiGetSysTimeInfo
                0x00405967                apiGetClientAreaRect
                0x004045dc                edit_box
                0x004057f4                kill
                0x004058b9                apiReboot
                0x004046c8                apiShutDown
                0x00405cf9                api_set_current_mouse_responder
                0x00405774                APIget_foregroung_window
                0x00404283                system4
                0x00405a71                apiSaveFile
                0x004058e5                apiSetCursor
                0x0040438b                system12
                0x004045ab                vsync
                0x00404307                system8
                0x00405d4e                api_set_window_with_text_input
                0x00405626                APIGetActiveWindow
                0x0040574b                APIupdate_window
                0x00405d22                api_get_current_mouse_responder
                0x004057f9                dead_thread_collector
                0x00405a0e                apiStartThread
                0x004055a2                APIKillFocus
                0x004057a0                APIset_foregroung_window
                0x00405c48                apiPutChar
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x004063b8      0xc48 00

.rdata          0x00407000      0xc20
 .rdata         0x00407000      0x3e0 api.o
 .rdata         0x004073e0      0x460 stdlib.o
 .rdata         0x00407840      0x1a0 stdio.o
 .rdata         0x004079e0      0x240 main.o

.data           0x00407c20     0x13e0
                0x00407c20                data = .
                0x00407c20                _data = .
                0x00407c20                __data = .
 *(.data)
 .data          0x00407c20        0x0 main.o
 .data          0x00407c20        0x0 stdio.o
 .data          0x00407c20        0x0 stdlib.o
 .data          0x00407c20      0x120 ctype.o
                0x00407c20                _ctype_
 .data          0x00407d40        0x0 string.o
 .data          0x00407d40      0x440 api.o
                0x00409000                . = ALIGN (0x1000)
 *fill*         0x00408180      0xe80 00

.bss            0x00409000     0xa720
                0x00409000                bss = .
                0x00409000                _bss = .
                0x00409000                __bss = .
 *(.bss)
 .bss           0x00409000        0x0 main.o
 .bss           0x00409000       0x10 stdio.o
 .bss           0x00409010     0x8010 stdlib.o
                0x00409010                environ
 .bss           0x00411020        0x0 ctype.o
 .bss           0x00411020       0x10 string.o
 .bss           0x00411030       0x40 api.o
                0x00412000                . = ALIGN (0x1000)
 *fill*         0x00411070      0xf90 00
 COMMON         0x00412000      0xde0 main.o
                0x00412000                prompt
                0x00412400                idleStatus
                0x00412410                ClientAreaInfo
                0x00412420                BufferInfo
                0x00412430                driverInitialized
                0x00412440                stderr
                0x00412450                prompt_pos
                0x00412460                g_using_gui
                0x00412470                stdin
                0x00412480                rect
                0x00412490                prompt_max
                0x004124a0                CurrentWindow
                0x004124b0                prompt_err
                0x004128b0                current_semaphore
                0x004128c0                g_columns
                0x004128d0                stdout
                0x004128e0                Streams
                0x00412960                g_rows
                0x00412970                prompt_out
                0x00412d70                g_cursor_y
                0x00412d80                CursorInfo
                0x00412d90                prompt_status
                0x00412da0                g_char_attrib
                0x00412db0                ApplicationInfo
                0x00412dc0                idleError
                0x00412dd0                g_cursor_x
 COMMON         0x00412de0      0x900 stdlib.o
                0x00412de0                current_mmblock
                0x00412df0                mm_prev_pointer
                0x00412e00                heap_end
                0x00412e10                g_available_heap
                0x00412e20                heap_start
                0x00412e30                heapCount
                0x00412e40                HEAP_START
                0x00412e50                g_heap_pointer
                0x00412e60                heapList
                0x00413260                randseed
                0x00413270                HEAP_SIZE
                0x00413280                last_size
                0x00413290                last_valid
                0x004132a0                mmblockList
                0x004136a0                libcHeap
                0x004136b0                Heap
                0x004136c0                mmblockCount
                0x004136d0                HEAP_END
 COMMON         0x004136e0       0x40 api.o
                0x004136e0                messagebox_button2
                0x004136f0                dialogbox_button1
                0x00413700                messagebox_button1
                0x00413710                dialogbox_button2
                0x00413720                end = .
                0x00413720                _end = .
                0x00413720                __end = .
LOAD head.o
LOAD main.o
LOAD stdio.o
LOAD stdlib.o
LOAD ctype.o
LOAD string.o
LOAD api.o
OUTPUT(TPRINTF.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
