
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
CurrentWindow       0x4               api.o
stdout              0x4               crt0.o
mm_prev_pointer     0x4               stdlib.o
mmblockList         0x400             stdlib.o
last_valid          0x4               stdlib.o
heapList            0x400             stdlib.o
libcHeap            0x4               stdlib.o
errno               0x4               unistd.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
Streams             0x80              crt0.o
messagebox_button1  0x4               api.o
g_using_gui         0x4               crt0.o
ApplicationInfo     0x4               api.o
randseed            0x4               stdlib.o
heap_start          0x4               stdlib.o
prompt_out          0x400             crt0.o
BufferInfo          0x4               api.o
g_available_heap    0x4               stdlib.o
g_heap_pointer      0x4               stdlib.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               stdlib.o
dialogbox_button1   0x4               api.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
last_size           0x4               stdlib.o
prompt_status       0x4               crt0.o
prompt_err          0x400             crt0.o
CursorInfo          0x4               api.o
heap_end            0x4               stdlib.o
stderr              0x4               crt0.o
prompt              0x400             crt0.o
HEAP_END            0x4               stdlib.o
rect                0x4               api.o
g_cursor_y          0x4               crt0.o
ClientAreaInfo      0x4               api.o
messagebox_button2  0x4               api.o
Heap                0x4               stdlib.o
current_semaphore   0x4               api.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
heapCount           0x4               stdlib.o
HEAP_START          0x4               stdlib.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000401000     0x7000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000      0x128 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401128        0x0 ctype.o
 .text          0x0000000000401128      0x38b main.o
                0x0000000000401128                usage
                0x000000000040114e                handle_args
                0x000000000040145a                main
 .text          0x00000000004014b3      0x205 dumpit.o
                0x00000000004014b3                dumpfile
 .text          0x00000000004016b8     0x2830 stdio.o
                0x0000000000401700                stdio_atoi
                0x00000000004017c7                stdio_fntos
                0x00000000004018f1                fclose
                0x0000000000401912                fopen
                0x0000000000401933                scroll
                0x0000000000401a00                puts
                0x0000000000401a1b                fread
                0x0000000000401a3c                fwrite
                0x0000000000401e1e                printf3
                0x0000000000401e3b                printf_atoi
                0x0000000000401f2c                printf_i2hex
                0x0000000000401f8e                printf2
                0x0000000000402113                sprintf
                0x0000000000402168                putchar
                0x00000000004021b3                libc_set_output_mode
                0x00000000004021f7                outbyte
                0x00000000004023b5                _outbyte
                0x00000000004023e4                input
                0x0000000000402541                getchar
                0x000000000040256f                stdioInitialize
                0x0000000000402711                fflush
                0x0000000000402732                fprintf
                0x00000000004027c0                fputs
                0x00000000004027e1                gets
                0x0000000000402870                ungetc
                0x0000000000402891                ftell
                0x00000000004028b2                fileno
                0x00000000004028d3                fgetc
                0x00000000004028f4                feof
                0x0000000000402915                ferror
                0x0000000000402936                fseek
                0x0000000000402957                fputc
                0x00000000004029f2                stdioSetCursor
                0x0000000000402a0d                stdioGetCursorX
                0x0000000000402a28                stdioGetCursorY
                0x0000000000402a43                scanf
                0x0000000000402be4                sscanf
                0x0000000000402d9f                kvprintf
                0x0000000000403c09                printf
                0x0000000000403c37                printf_draw
                0x0000000000403c7f                vfprintf
                0x0000000000403cf7                vprintf
                0x0000000000403d16                stdout_printf
                0x0000000000403d42                stderr_printf
                0x0000000000403d6e                perror
                0x0000000000403d85                rewind
                0x0000000000403daf                snprintf
                0x0000000000403dc3                stdio_initialize_standard_streams
                0x0000000000403dee                libcStartTerminal
                0x0000000000403e61                setbuf
                0x0000000000403e83                setbuffer
                0x0000000000403ea5                setlinebuf
                0x0000000000403ec7                setvbuf
 .text          0x0000000000403ee8     0x105e stdlib.o
                0x0000000000403f05                rtGetHeapStart
                0x0000000000403f0f                rtGetHeapEnd
                0x0000000000403f19                rtGetHeapPointer
                0x0000000000403f23                rtGetAvailableHeap
                0x0000000000403f2d                heapSetLibcHeap
                0x0000000000403fe0                heapAllocateMemory
                0x0000000000404212                FreeHeap
                0x000000000040421c                heapInit
                0x00000000004043af                stdlibInitMM
                0x0000000000404412                libcInitRT
                0x0000000000404434                rand
                0x0000000000404451                srand
                0x000000000040445f                xmalloc
                0x0000000000404491                stdlib_die
                0x00000000004044c7                malloc
                0x0000000000404503                realloc
                0x0000000000404540                free
                0x0000000000404546                calloc
                0x000000000040458c                zmalloc
                0x00000000004045c8                system
                0x000000000040498c                stdlib_strncmp
                0x00000000004049ef                __findenv
                0x0000000000404aba                getenv
                0x0000000000404ae7                atoi
                0x0000000000404bae                reverse
                0x0000000000404c16                itoa
                0x0000000000404cc4                abs
                0x0000000000404cd4                strtod
                0x0000000000404f05                strtof
                0x0000000000404f21                strtold
                0x0000000000404f34                atof
 .text          0x0000000000404f46      0x8d9 string.o
                0x0000000000404f46                memcmp
                0x0000000000404fab                strdup
                0x0000000000404ffd                strndup
                0x000000000040505e                strrchr
                0x0000000000405099                strtoimax
                0x00000000004050a3                strtoumax
                0x00000000004050ad                strcasecmp
                0x0000000000405115                strncpy
                0x000000000040516b                strcmp
                0x00000000004051d0                strncmp
                0x0000000000405233                memset
                0x000000000040527a                memoryZeroMemory
                0x00000000004052a1                memcpy
                0x00000000004052de                strcpy
                0x0000000000405312                strcat
                0x0000000000405341                strncat
                0x00000000004053a3                bcopy
                0x00000000004053d0                bzero
                0x00000000004053f1                strlen
                0x000000000040541f                strnlen
                0x0000000000405453                strpbrk
                0x00000000004054a1                strcspn
                0x0000000000405540                strspn
                0x00000000004055df                strtok_r
                0x00000000004056c6                strtok
                0x00000000004056de                strchr
                0x000000000040570a                memmove
                0x000000000040578b                memscan
                0x00000000004057bf                strstr
 .text          0x000000000040581f       0x29 time.o
                0x000000000040581f                time
 .text          0x0000000000405848     0x213a api.o
                0x0000000000405848                system_call
                0x0000000000405870                apiSystem
                0x0000000000405c78                system1
                0x0000000000405c99                system2
                0x0000000000405cba                system3
                0x0000000000405cdb                system4
                0x0000000000405cfc                system5
                0x0000000000405d1d                system6
                0x0000000000405d3e                system7
                0x0000000000405d5f                system8
                0x0000000000405d80                system9
                0x0000000000405da1                system10
                0x0000000000405dc2                system11
                0x0000000000405de3                system12
                0x0000000000405e04                system13
                0x0000000000405e25                system14
                0x0000000000405e46                system15
                0x0000000000405e67                refresh_buffer
                0x0000000000405f3f                print_string
                0x0000000000405f45                vsync
                0x0000000000405f5a                edit_box
                0x0000000000405f71                gde_system_procedure
                0x0000000000405fa7                SetNextWindowProcedure
                0x0000000000405fb1                set_cursor
                0x0000000000405fc8                put_char
                0x0000000000405fce                gde_load_bitmap_16x16
                0x0000000000405fe7                apiShutDown
                0x0000000000405ffe                apiInitBackground
                0x0000000000406004                MessageBox
                0x000000000040659b                mbProcedure
                0x0000000000406611                DialogBox
                0x00000000004069cc                dbProcedure
                0x0000000000406a42                call_kernel
                0x0000000000406b6a                call_gui
                0x0000000000406bff                gde_create_window
                0x0000000000406c78                gde_register_window
                0x0000000000406ca0                gde_close_window
                0x0000000000406cc8                gde_set_focus
                0x0000000000406cf0                gde_get_focus
                0x0000000000406d05                APIKillFocus
                0x0000000000406d2d                APISetActiveWindow
                0x0000000000406d55                APIGetActiveWindow
                0x0000000000406d6a                APIShowCurrentProcessInfo
                0x0000000000406d80                APIresize_window
                0x0000000000406d9a                APIredraw_window
                0x0000000000406db4                APIreplace_window
                0x0000000000406dce                APImaximize_window
                0x0000000000406dea                APIminimize_window
                0x0000000000406e06                APIupdate_window
                0x0000000000406e22                APIget_foregroung_window
                0x0000000000406e38                APIset_foregroung_window
                0x0000000000406e54                apiExit
                0x0000000000406e71                kill
                0x0000000000406e77                dead_thread_collector
                0x0000000000406e8d                api_strncmp
                0x0000000000406ef0                refresh_screen
                0x0000000000406f06                api_refresh_screen
                0x0000000000406f11                apiReboot
                0x0000000000406f27                apiSetCursor
                0x0000000000406f3f                apiGetCursorX
                0x0000000000406f57                apiGetCursorY
                0x0000000000406f6f                apiGetClientAreaRect
                0x0000000000406f87                apiSetClientAreaRect
                0x0000000000406fa6                gde_create_process
                0x0000000000406fbf                gde_create_thread
                0x0000000000406fd8                apiStartThread
                0x0000000000406ff4                apiFOpen
                0x0000000000407020                gde_save_file
                0x0000000000407073                apiDown
                0x00000000004070c8                apiUp
                0x000000000040711d                enterCriticalSection
                0x0000000000407158                exitCriticalSection
                0x0000000000407171                initializeCriticalSection
                0x000000000040718a                gde_begin_paint
                0x0000000000407195                gde_end_paint
                0x00000000004071a0                apiPutChar
                0x00000000004071bc                apiDefDialog
                0x00000000004071c6                apiGetSystemMetrics
                0x00000000004071e4                api_set_current_keyboard_responder
                0x0000000000407203                api_get_current_keyboard_responder
                0x000000000040721b                api_set_current_mouse_responder
                0x000000000040723a                api_get_current_mouse_responder
                0x0000000000407252                api_set_window_with_text_input
                0x0000000000407294                api_get_window_with_text_input
                0x00000000004072ac                gramadocore_init_execve
                0x00000000004072b6                apiDialog
                0x000000000040734f                api_getchar
                0x0000000000407367                apiDisplayBMP
                0x000000000040776e                apiSendMessageToProcess
                0x00000000004077b1                apiSendMessageToThread
                0x00000000004077f4                apiSendMessage
                0x000000000040782a                apiDrawText
                0x0000000000407869                apiGetWSScreenWindow
                0x0000000000407881                apiGetWSMainWindow
                0x0000000000407899                apiCreateTimer
                0x00000000004078b6                apiGetSysTimeInfo
                0x00000000004078d4                apiShowWindow
                0x00000000004078f0                apiStartTerminal
                0x0000000000407964                apiUpdateStatusBar
 .text          0x0000000000407982      0x31f unistd.o
                0x0000000000407982                execv
                0x00000000004079a0                execve
                0x00000000004079ff                exit
                0x0000000000407a1f                fork
                0x0000000000407a55                sys_fork
                0x0000000000407a8b                fast_fork
                0x0000000000407ab3                setuid
                0x0000000000407ace                getuid
                0x0000000000407ae9                geteuid
                0x0000000000407af3                getpid
                0x0000000000407b0b                getppid
                0x0000000000407b23                getgid
                0x0000000000407b3e                dup
                0x0000000000407b58                dup2
                0x0000000000407b74                dup3
                0x0000000000407b92                fcntl
                0x0000000000407b9c                nice
                0x0000000000407ba6                pause
                0x0000000000407bb0                mkdir
                0x0000000000407bc4                rmdir
                0x0000000000407bce                link
                0x0000000000407bd8                mlock
                0x0000000000407be2                munlock
                0x0000000000407bec                mlockall
                0x0000000000407bf6                munlockall
                0x0000000000407c00                sysconf
                0x0000000000407c0a                fsync
                0x0000000000407c14                fdatasync
                0x0000000000407c1e                ioctl
                0x0000000000407c28                open
                0x0000000000407c4e                close
                0x0000000000407c6c                pipe
                0x0000000000407c8d                fpathconf
                0x0000000000407c97                pathconf
 .text          0x0000000000407ca1       0x28 stubs.o
                0x0000000000407ca1                gramado_system_call
                0x0000000000408000                . = ALIGN (0x1000)
 *fill*         0x0000000000407cc9      0x337 

.iplt           0x0000000000408000        0x0
 .iplt          0x0000000000408000        0x0 crt0.o

.rodata         0x0000000000408000      0xf1a
 .rodata        0x0000000000408000       0x74 crt0.o
 *fill*         0x0000000000408074        0xc 
 .rodata        0x0000000000408080      0x100 ctype.o
                0x0000000000408080                _ctype
 .rodata        0x0000000000408180       0xba main.o
 .rodata        0x000000000040823a       0x3d dumpit.o
 *fill*         0x0000000000408277        0x9 
 .rodata        0x0000000000408280      0x329 stdio.o
                0x00000000004083e0                hex2ascii_data
 *fill*         0x00000000004085a9        0x7 
 .rodata        0x00000000004085b0      0x510 stdlib.o
 .rodata        0x0000000000408ac0      0x41d api.o
 *fill*         0x0000000000408edd        0x3 
 .rodata        0x0000000000408ee0       0x3a unistd.o

.eh_frame       0x0000000000408f1c     0x2188
 .eh_frame      0x0000000000408f1c       0x34 crt0.o
 .eh_frame      0x0000000000408f50       0x74 main.o
                                         0x8c (size before relaxing)
 .eh_frame      0x0000000000408fc4       0x20 dumpit.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000408fe4      0x7f0 stdio.o
                                        0x808 (size before relaxing)
 .eh_frame      0x00000000004097d4      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x0000000000409bd4      0x3a0 string.o
                                        0x3b8 (size before relaxing)
 .eh_frame      0x0000000000409f74       0x20 time.o
                                         0x38 (size before relaxing)
 .eh_frame      0x0000000000409f94      0xcac api.o
                                        0xcc4 (size before relaxing)
 .eh_frame      0x000000000040ac40      0x440 unistd.o
                                        0x458 (size before relaxing)
 .eh_frame      0x000000000040b080       0x24 stubs.o
                                         0x3c (size before relaxing)

.rel.dyn        0x000000000040b0a4        0x0
 .rel.got       0x000000000040b0a4        0x0 crt0.o
 .rel.iplt      0x000000000040b0a4        0x0 crt0.o
 .rel.text      0x000000000040b0a4        0x0 crt0.o

.data           0x000000000040b0c0      0xf40
                0x000000000040b0c0                data = .
                0x000000000040b0c0                _data = .
                0x000000000040b0c0                __data = .
 *(.data)
 .data          0x000000000040b0c0       0x14 crt0.o
 .data          0x000000000040b0d4        0x0 ctype.o
 .data          0x000000000040b0d4        0x0 main.o
 .data          0x000000000040b0d4        0x0 dumpit.o
 .data          0x000000000040b0d4        0x0 stdio.o
 *fill*         0x000000000040b0d4        0x4 
 .data          0x000000000040b0d8        0x8 stdlib.o
                0x000000000040b0d8                _infinity
 .data          0x000000000040b0e0        0x0 string.o
 .data          0x000000000040b0e0        0x0 time.o
 .data          0x000000000040b0e0      0x440 api.o
 .data          0x000000000040b520        0x0 unistd.o
 .data          0x000000000040b520        0x0 stubs.o
                0x000000000040c000                . = ALIGN (0x1000)
 *fill*         0x000000000040b520      0xae0 

.got            0x000000000040c000        0x0
 .got           0x000000000040c000        0x0 crt0.o

.got.plt        0x000000000040c000        0x0
 .got.plt       0x000000000040c000        0x0 crt0.o

.igot.plt       0x000000000040c000        0x0
 .igot.plt      0x000000000040c000        0x0 crt0.o

.bss            0x000000000040c000    0x125c8
                0x000000000040c000                bss = .
                0x000000000040c000                _bss = .
                0x000000000040c000                __bss = .
 *(.bss)
 .bss           0x000000000040c000        0x0 crt0.o
 .bss           0x000000000040c000        0x0 ctype.o
 .bss           0x000000000040c000        0x0 main.o
 .bss           0x000000000040c000        0x0 dumpit.o
 .bss           0x000000000040c000        0x9 stdio.o
 *fill*         0x000000000040c009       0x17 
 .bss           0x000000000040c020     0x8020 stdlib.o
                0x000000000040c020                environ
 .bss           0x0000000000414040        0x4 string.o
 .bss           0x0000000000414044        0x0 time.o
 *fill*         0x0000000000414044       0x1c 
 .bss           0x0000000000414060     0x8004 api.o
 .bss           0x000000000041c064        0xc unistd.o
                0x000000000041c064                __execv_environ
 .bss           0x000000000041c070        0x0 stubs.o
                0x000000000041d000                . = ALIGN (0x1000)
 *fill*         0x000000000041c070      0xf90 
 COMMON         0x000000000041d000      0xd08 crt0.o
                0x000000000041d000                g_cursor_x
                0x000000000041d004                stdout
                0x000000000041d008                g_char_attrib
                0x000000000041d00c                g_rows
                0x000000000041d020                Streams
                0x000000000041d0a0                g_using_gui
                0x000000000041d0c0                prompt_out
                0x000000000041d4c0                g_columns
                0x000000000041d4c4                prompt_pos
                0x000000000041d4c8                stdin
                0x000000000041d4cc                prompt_status
                0x000000000041d4e0                prompt_err
                0x000000000041d8e0                stderr
                0x000000000041d900                prompt
                0x000000000041dd00                g_cursor_y
                0x000000000041dd04                prompt_max
 *fill*         0x000000000041dd08       0x18 
 COMMON         0x000000000041dd20      0x878 stdlib.o
                0x000000000041dd20                mm_prev_pointer
                0x000000000041dd40                mmblockList
                0x000000000041e140                last_valid
                0x000000000041e160                heapList
                0x000000000041e560                libcHeap
                0x000000000041e564                randseed
                0x000000000041e568                heap_start
                0x000000000041e56c                g_available_heap
                0x000000000041e570                g_heap_pointer
                0x000000000041e574                HEAP_SIZE
                0x000000000041e578                mmblockCount
                0x000000000041e57c                last_size
                0x000000000041e580                heap_end
                0x000000000041e584                HEAP_END
                0x000000000041e588                Heap
                0x000000000041e58c                current_mmblock
                0x000000000041e590                heapCount
                0x000000000041e594                HEAP_START
 COMMON         0x000000000041e598       0x2c api.o
                0x000000000041e598                CurrentWindow
                0x000000000041e59c                dialogbox_button2
                0x000000000041e5a0                messagebox_button1
                0x000000000041e5a4                ApplicationInfo
                0x000000000041e5a8                BufferInfo
                0x000000000041e5ac                dialogbox_button1
                0x000000000041e5b0                CursorInfo
                0x000000000041e5b4                rect
                0x000000000041e5b8                ClientAreaInfo
                0x000000000041e5bc                messagebox_button2
                0x000000000041e5c0                current_semaphore
 COMMON         0x000000000041e5c4        0x4 unistd.o
                0x000000000041e5c4                errno
                0x000000000041e5c8                end = .
                0x000000000041e5c8                _end = .
                0x000000000041e5c8                __end = .
LOAD crt0.o
LOAD ctype.o
LOAD main.o
LOAD dumpit.o
LOAD stdio.o
LOAD stdlib.o
LOAD string.o
LOAD time.o
LOAD api.o
LOAD unistd.o
LOAD stubs.o
OUTPUT(DUMPIT.BIN elf32-i386)

.comment        0x0000000000000000       0x11
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 ctype.o
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 dumpit.o
 .comment       0x0000000000000011       0x12 stdio.o
 .comment       0x0000000000000011       0x12 stdlib.o
 .comment       0x0000000000000011       0x12 string.o
 .comment       0x0000000000000011       0x12 time.o
 .comment       0x0000000000000011       0x12 api.o
 .comment       0x0000000000000011       0x12 unistd.o
 .comment       0x0000000000000011       0x12 stubs.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 ctype.o
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
 .note.GNU-stack
                0x0000000000000000        0x0 dumpit.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdio.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdlib.o
 .note.GNU-stack
                0x0000000000000000        0x0 string.o
 .note.GNU-stack
                0x0000000000000000        0x0 time.o
 .note.GNU-stack
                0x0000000000000000        0x0 api.o
 .note.GNU-stack
                0x0000000000000000        0x0 unistd.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
