
Allocating common symbols
Common symbol       size              file

g_cursor_x          0x4               crt0.o
modifier_found      0x4               main.o
peekSymbol          0x4               main.o
CurrentWindow       0x4               main.o
lexer_lastline      0x4               main.o
current_keyword     0x4               main.o
stack_count         0x4               main.o
stdout              0x4               crt0.o
next_index          0x4               main.o
DATA                0x200             main.o
program_bss_address
                    0x4               main.o
brace_count         0x4               main.o
brace_end           0x4               main.o
mm_prev_pointer     0x4               stdlib.o
program             0x10              main.o
mmblockList         0x400             stdlib.o
last_valid          0x4               stdlib.o
heapList            0x400             main.o
string_flag         0x4               main.o
libcHeap            0x4               main.o
lexer_token_count   0x4               main.o
errno               0x4               unistd.o
type_found          0x4               main.o
parentheses_start   0x4               main.o
separator_count     0x4               main.o
g_char_attrib       0x4               crt0.o
g_rows              0x4               crt0.o
dialogbox_button2   0x4               api.o
return_info         0x20              main.o
stack_flag          0x4               main.o
Streams             0x80              crt0.o
lexer_lineno        0x4               main.o
current_constant    0x4               main.o
temp_filename_length
                    0x4               main.o
lexer_code          0x4               main.o
messagebox_button1  0x4               api.o
constant_base_found
                    0x4               main.o
g_using_gui         0x4               crt0.o
constant_aftes      0x2               main.o
peekChar            0x4               main.o
lexer_firstline     0x4               main.o
ApplicationInfo     0x4               main.o
qualifier_found     0x4               main.o
randseed            0x4               stdlib.o
infile_size         0x4               main.o
stack               0x200             main.o
file_s              0x200             main.o
current_identifier  0x4               main.o
heap_start          0x4               main.o
STRINGLIST          0x140             main.o
asm_flag            0x4               main.o
prompt_out          0x400             crt0.o
id                  0x20              main.o
return_found        0x4               main.o
BufferInfo          0x4               main.o
BSS                 0x200             main.o
special_count       0x4               main.o
keyword_count       0x4               main.o
current_special     0x4               main.o
file_i              0x200             main.o
g_available_heap    0x4               main.o
g_heap_pointer      0x4               main.o
current_separator   0x4               main.o
current_string      0x4               main.o
current_token       0x4               main.o
parentheses_count   0x4               main.o
g_columns           0x4               crt0.o
HEAP_SIZE           0x4               main.o
outfile_size        0x4               main.o
dialogbox_button1   0x4               api.o
mmblockCount        0x4               stdlib.o
prompt_pos          0x4               crt0.o
stdin               0x4               crt0.o
no_output           0x4               main.o
last_size           0x4               stdlib.o
prompt_status       0x4               crt0.o
outfile             0x200             main.o
string_count        0x4               main.o
POS_BUFFER          0x80              tree.o
constant            0x20              main.o
constant_word       0x4               main.o
parentheses_end     0x4               main.o
prompt_err          0x400             crt0.o
function_main_buffer
                    0x200             main.o
current_type        0x4               main.o
IDENTIFIERLIST      0x140             main.o
identifier_count    0x4               main.o
main_return_type    0x4               main.o
KEYWORDLIST         0x140             main.o
constant_byte       0x2               main.o
TOKENLIST           0x140             main.o
CursorInfo          0x4               main.o
keyword_found       0x4               main.o
number_of_tokens    0x4               main.o
brace_start         0x4               main.o
heap_end            0x4               main.o
eofno               0x4               main.o
CONSTANTLIST        0x140             main.o
temp_file_queue     0x4               main.o
SPECIALLIST         0x140             main.o
SEPARATORLIST       0x140             main.o
function_main       0x4               main.o
program_data_address
                    0x4               main.o
stderr              0x4               crt0.o
infile              0x200             main.o
current_index       0x4               main.o
finput              0x4               main.o
prompt              0x400             crt0.o
HEAP_END            0x4               main.o
functionList        0x80              main.o
rect                0x4               main.o
compiler_name       0x4               main.o
directive_fould     0x4               main.o
g_cursor_y          0x4               crt0.o
exp_buffer          0x80              tree.o
stack_index         0x4               main.o
main_found          0x4               main.o
TEXT                0x200             main.o
ClientAreaInfo      0x4               main.o
messagebox_button2  0x4               api.o
function_return_type
                    0x4               main.o
Heap                0x4               main.o
constant_dword      0x8               main.o
real_token_buffer   0x100             main.o
current_semaphore   0x4               main.o
constant_type_found
                    0x4               main.o
return_index        0x4               main.o
temp_filename       0x4               main.o
prompt_max          0x4               crt0.o
current_mmblock     0x4               stdlib.o
program_text_address
                    0x4               main.o
heapCount           0x4               main.o
program_header_address
                    0x4               main.o
constant_before     0x2               main.o
HEAP_START          0x4               main.o
constant_count      0x4               main.o
lineno              0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map


.text           0x0000000000401000     0xa000
                0x0000000000401000                code = .
                0x0000000000401000                _code = .
                0x0000000000401000                __code = .
 *(.head_x86)
 *(.text)
 .text          0x0000000000401000      0x128 crt0.o
                0x0000000000401000                crt0
 .text          0x0000000000401128      0x8f1 main.o
                0x0000000000401128                gramc_main
                0x000000000040112e                mainTextEditor
                0x0000000000401330                editorClearScreen
                0x00000000004013a9                create_tokenlist
                0x0000000000401438                fncc_print_tokenList
                0x00000000004014ae                gramcInitialize
                0x00000000004016ef                debugShowStat
                0x0000000000401803                main
 .text          0x0000000000401a19        0x0 ctype.o
 .text          0x0000000000401a19     0x105e stdlib.o
                0x0000000000401a36                rtGetHeapStart
                0x0000000000401a40                rtGetHeapEnd
                0x0000000000401a4a                rtGetHeapPointer
                0x0000000000401a54                rtGetAvailableHeap
                0x0000000000401a5e                heapSetLibcHeap
                0x0000000000401b11                heapAllocateMemory
                0x0000000000401d43                FreeHeap
                0x0000000000401d4d                heapInit
                0x0000000000401ee0                stdlibInitMM
                0x0000000000401f43                libcInitRT
                0x0000000000401f65                rand
                0x0000000000401f82                srand
                0x0000000000401f90                xmalloc
                0x0000000000401fc2                stdlib_die
                0x0000000000401ff8                malloc
                0x0000000000402034                realloc
                0x0000000000402071                free
                0x0000000000402077                calloc
                0x00000000004020bd                zmalloc
                0x00000000004020f9                system
                0x00000000004024bd                stdlib_strncmp
                0x0000000000402520                __findenv
                0x00000000004025eb                getenv
                0x0000000000402618                atoi
                0x00000000004026df                reverse
                0x0000000000402747                itoa
                0x00000000004027f5                abs
                0x0000000000402805                strtod
                0x0000000000402a36                strtof
                0x0000000000402a52                strtold
                0x0000000000402a65                atof
 .text          0x0000000000402a77     0x2830 stdio.o
                0x0000000000402abf                stdio_atoi
                0x0000000000402b86                stdio_fntos
                0x0000000000402cb0                fclose
                0x0000000000402cd1                fopen
                0x0000000000402cf2                scroll
                0x0000000000402dbf                puts
                0x0000000000402dda                fread
                0x0000000000402dfb                fwrite
                0x00000000004031dd                printf3
                0x00000000004031fa                printf_atoi
                0x00000000004032eb                printf_i2hex
                0x000000000040334d                printf2
                0x00000000004034d2                sprintf
                0x0000000000403527                putchar
                0x0000000000403572                libc_set_output_mode
                0x00000000004035b6                outbyte
                0x0000000000403774                _outbyte
                0x00000000004037a3                input
                0x0000000000403900                getchar
                0x000000000040392e                stdioInitialize
                0x0000000000403ad0                fflush
                0x0000000000403af1                fprintf
                0x0000000000403b7f                fputs
                0x0000000000403ba0                gets
                0x0000000000403c2f                ungetc
                0x0000000000403c50                ftell
                0x0000000000403c71                fileno
                0x0000000000403c92                fgetc
                0x0000000000403cb3                feof
                0x0000000000403cd4                ferror
                0x0000000000403cf5                fseek
                0x0000000000403d16                fputc
                0x0000000000403db1                stdioSetCursor
                0x0000000000403dcc                stdioGetCursorX
                0x0000000000403de7                stdioGetCursorY
                0x0000000000403e02                scanf
                0x0000000000403fa3                sscanf
                0x000000000040415e                kvprintf
                0x0000000000404fc8                printf
                0x0000000000404ff6                printf_draw
                0x000000000040503e                vfprintf
                0x00000000004050b6                vprintf
                0x00000000004050d5                stdout_printf
                0x0000000000405101                stderr_printf
                0x000000000040512d                perror
                0x0000000000405144                rewind
                0x000000000040516e                snprintf
                0x0000000000405182                stdio_initialize_standard_streams
                0x00000000004051ad                libcStartTerminal
                0x0000000000405220                setbuf
                0x0000000000405242                setbuffer
                0x0000000000405264                setlinebuf
                0x0000000000405286                setvbuf
 .text          0x00000000004052a7      0xb2b string.o
                0x00000000004052a7                strcoll
                0x00000000004052c0                memsetw
                0x00000000004052ec                memcmp
                0x0000000000405351                strdup
                0x00000000004053a3                strndup
                0x0000000000405404                strnchr
                0x000000000040543d                strrchr
                0x0000000000405478                strtoimax
                0x0000000000405482                strtoumax
                0x000000000040548c                strcasecmp
                0x00000000004054f4                strncpy
                0x000000000040554a                strcmp
                0x00000000004055af                strncmp
                0x0000000000405612                memset
                0x0000000000405659                memoryZeroMemory
                0x0000000000405680                memcpy
                0x00000000004056bd                strcpy
                0x00000000004056f1                strlcpy
                0x0000000000405750                strcat
                0x000000000040577f                strchrnul
                0x00000000004057a4                strlcat
                0x0000000000405834                strncat
                0x0000000000405896                bcopy
                0x00000000004058c3                bzero
                0x00000000004058e4                strlen
                0x0000000000405912                strnlen
                0x000000000040594d                strpbrk
                0x000000000040599b                strsep
                0x0000000000405a19                strreplace
                0x0000000000405a54                strcspn
                0x0000000000405af3                strspn
                0x0000000000405b92                strtok_r
                0x0000000000405c79                strtok
                0x0000000000405c91                strchr
                0x0000000000405cbd                memmove
                0x0000000000405d3e                memscan
                0x0000000000405d72                strstr
 .text          0x0000000000405dd2      0x31f unistd.o
                0x0000000000405dd2                execv
                0x0000000000405df0                execve
                0x0000000000405e4f                exit
                0x0000000000405e6f                fork
                0x0000000000405ea5                sys_fork
                0x0000000000405edb                fast_fork
                0x0000000000405f03                setuid
                0x0000000000405f1e                getuid
                0x0000000000405f39                geteuid
                0x0000000000405f43                getpid
                0x0000000000405f5b                getppid
                0x0000000000405f73                getgid
                0x0000000000405f8e                dup
                0x0000000000405fa8                dup2
                0x0000000000405fc4                dup3
                0x0000000000405fe2                fcntl
                0x0000000000405fec                nice
                0x0000000000405ff6                pause
                0x0000000000406000                mkdir
                0x0000000000406014                rmdir
                0x000000000040601e                link
                0x0000000000406028                mlock
                0x0000000000406032                munlock
                0x000000000040603c                mlockall
                0x0000000000406046                munlockall
                0x0000000000406050                sysconf
                0x000000000040605a                fsync
                0x0000000000406064                fdatasync
                0x000000000040606e                ioctl
                0x0000000000406078                open
                0x000000000040609e                close
                0x00000000004060bc                pipe
                0x00000000004060dd                fpathconf
                0x00000000004060e7                pathconf
 .text          0x00000000004060f1     0x213a api.o
                0x00000000004060f1                system_call
                0x0000000000406119                apiSystem
                0x0000000000406521                system1
                0x0000000000406542                system2
                0x0000000000406563                system3
                0x0000000000406584                system4
                0x00000000004065a5                system5
                0x00000000004065c6                system6
                0x00000000004065e7                system7
                0x0000000000406608                system8
                0x0000000000406629                system9
                0x000000000040664a                system10
                0x000000000040666b                system11
                0x000000000040668c                system12
                0x00000000004066ad                system13
                0x00000000004066ce                system14
                0x00000000004066ef                system15
                0x0000000000406710                refresh_buffer
                0x00000000004067e8                print_string
                0x00000000004067ee                vsync
                0x0000000000406803                edit_box
                0x000000000040681a                gde_system_procedure
                0x0000000000406850                SetNextWindowProcedure
                0x000000000040685a                set_cursor
                0x0000000000406871                put_char
                0x0000000000406877                gde_load_bitmap_16x16
                0x0000000000406890                apiShutDown
                0x00000000004068a7                apiInitBackground
                0x00000000004068ad                MessageBox
                0x0000000000406e44                mbProcedure
                0x0000000000406eba                DialogBox
                0x0000000000407275                dbProcedure
                0x00000000004072eb                call_kernel
                0x0000000000407413                call_gui
                0x00000000004074a8                gde_create_window
                0x0000000000407521                gde_register_window
                0x0000000000407549                gde_close_window
                0x0000000000407571                gde_set_focus
                0x0000000000407599                gde_get_focus
                0x00000000004075ae                APIKillFocus
                0x00000000004075d6                APISetActiveWindow
                0x00000000004075fe                APIGetActiveWindow
                0x0000000000407613                APIShowCurrentProcessInfo
                0x0000000000407629                APIresize_window
                0x0000000000407643                APIredraw_window
                0x000000000040765d                APIreplace_window
                0x0000000000407677                APImaximize_window
                0x0000000000407693                APIminimize_window
                0x00000000004076af                APIupdate_window
                0x00000000004076cb                APIget_foregroung_window
                0x00000000004076e1                APIset_foregroung_window
                0x00000000004076fd                apiExit
                0x000000000040771a                kill
                0x0000000000407720                dead_thread_collector
                0x0000000000407736                api_strncmp
                0x0000000000407799                refresh_screen
                0x00000000004077af                api_refresh_screen
                0x00000000004077ba                apiReboot
                0x00000000004077d0                apiSetCursor
                0x00000000004077e8                apiGetCursorX
                0x0000000000407800                apiGetCursorY
                0x0000000000407818                apiGetClientAreaRect
                0x0000000000407830                apiSetClientAreaRect
                0x000000000040784f                gde_create_process
                0x0000000000407868                gde_create_thread
                0x0000000000407881                apiStartThread
                0x000000000040789d                apiFOpen
                0x00000000004078c9                gde_save_file
                0x000000000040791c                apiDown
                0x0000000000407971                apiUp
                0x00000000004079c6                enterCriticalSection
                0x0000000000407a01                exitCriticalSection
                0x0000000000407a1a                initializeCriticalSection
                0x0000000000407a33                gde_begin_paint
                0x0000000000407a3e                gde_end_paint
                0x0000000000407a49                apiPutChar
                0x0000000000407a65                apiDefDialog
                0x0000000000407a6f                apiGetSystemMetrics
                0x0000000000407a8d                api_set_current_keyboard_responder
                0x0000000000407aac                api_get_current_keyboard_responder
                0x0000000000407ac4                api_set_current_mouse_responder
                0x0000000000407ae3                api_get_current_mouse_responder
                0x0000000000407afb                api_set_window_with_text_input
                0x0000000000407b3d                api_get_window_with_text_input
                0x0000000000407b55                gramadocore_init_execve
                0x0000000000407b5f                apiDialog
                0x0000000000407bf8                api_getchar
                0x0000000000407c10                apiDisplayBMP
                0x0000000000408017                apiSendMessageToProcess
                0x000000000040805a                apiSendMessageToThread
                0x000000000040809d                apiSendMessage
                0x00000000004080d3                apiDrawText
                0x0000000000408112                apiGetWSScreenWindow
                0x000000000040812a                apiGetWSMainWindow
                0x0000000000408142                apiCreateTimer
                0x000000000040815f                apiGetSysTimeInfo
                0x000000000040817d                apiShowWindow
                0x0000000000408199                apiStartTerminal
                0x000000000040820d                apiUpdateStatusBar
 .text          0x000000000040822b      0xbb6 lexer.o
                0x0000000000408248                skip_white_space
                0x00000000004083df                yylex
                0x0000000000408d1c                lexerInit
                0x0000000000408dab                lexer
                0x0000000000408dc5                error
 .text          0x0000000000408de1     0x1626 parser.o
                0x0000000000408de1                parse_function
                0x0000000000408f89                parse_asm
                0x0000000000409121                parse_string
                0x00000000004092ce                parse_run
                0x000000000040947d                parse_do
                0x00000000004094ad                parse_for
                0x00000000004094dd                parse_if
                0x00000000004095e2                parse_return
                0x00000000004096ce                parse_sizeof
                0x0000000000409891                parse_while
                0x0000000000409996                parse_expression
                0x00000000004099eb                parse
                0x000000000040a310                parserInit
                0x000000000040a3e3                parser
 .text          0x000000000040a407      0x8b1 tree.o
                0x000000000040a407                my_isdigit
                0x000000000040a42d                newNode
                0x000000000040a466                inorder
                0x000000000040a4af                exibirEmOrdem
                0x000000000040a4f8                exibirPreOrdem
                0x000000000040a541                exibirPosOrdem
                0x000000000040a5d3                insert
                0x000000000040a640                bst_main
                0x000000000040a844                push
                0x000000000040a884                pop
                0x000000000040a8c1                oper
                0x000000000040a929                eval
                0x000000000040aa0e                testtest_main
                0x000000000040aa26                tree_eval
 .text          0x000000000040acb8       0x28 stubs.o
                0x000000000040acb8                gramado_system_call
 .text          0x000000000040ace0       0x50 compiler.o
                0x000000000040ace0                compiler
                0x000000000040b000                . = ALIGN (0x1000)
 *fill*         0x000000000040ad30      0x2d0 

.iplt           0x000000000040b000        0x0
 .iplt          0x000000000040b000        0x0 crt0.o

.rodata         0x000000000040b000     0x27e4
 .rodata        0x000000000040b000       0x74 crt0.o
 .rodata        0x000000000040b074      0x46e main.o
 *fill*         0x000000000040b4e2       0x1e 
 .rodata        0x000000000040b500      0x100 ctype.o
                0x000000000040b500                _ctype
 .rodata        0x000000000040b600      0x510 stdlib.o
 *fill*         0x000000000040bb10       0x10 
 .rodata        0x000000000040bb20      0x329 stdio.o
                0x000000000040bc80                hex2ascii_data
 *fill*         0x000000000040be49        0x3 
 .rodata        0x000000000040be4c       0x3a unistd.o
 *fill*         0x000000000040be86        0x2 
 .rodata        0x000000000040be88      0x41d api.o
 *fill*         0x000000000040c2a5        0x3 
 .rodata        0x000000000040c2a8      0x5cf lexer.o
 *fill*         0x000000000040c877        0x1 
 .rodata        0x000000000040c878      0xafa parser.o
 *fill*         0x000000000040d372        0x2 
 .rodata        0x000000000040d374      0x378 tree.o
 .rodata        0x000000000040d6ec       0xf8 compiler.o

.eh_frame       0x000000000040d7e4     0x2794
 .eh_frame      0x000000000040d7e4       0x34 crt0.o
 .eh_frame      0x000000000040d818      0x11c main.o
                                        0x134 (size before relaxing)
 .eh_frame      0x000000000040d934      0x400 stdlib.o
                                        0x418 (size before relaxing)
 .eh_frame      0x000000000040dd34      0x7f0 stdio.o
                                        0x808 (size before relaxing)
 .eh_frame      0x000000000040e524      0x4c0 string.o
                                        0x4d8 (size before relaxing)
 .eh_frame      0x000000000040e9e4      0x440 unistd.o
                                        0x458 (size before relaxing)
 .eh_frame      0x000000000040ee24      0xcac api.o
                                        0xcc4 (size before relaxing)
 .eh_frame      0x000000000040fad0       0xdc lexer.o
                                         0xf4 (size before relaxing)
 .eh_frame      0x000000000040fbac      0x1c8 parser.o
                                        0x1e0 (size before relaxing)
 .eh_frame      0x000000000040fd74      0x1c0 tree.o
                                        0x1d8 (size before relaxing)
 .eh_frame      0x000000000040ff34       0x24 stubs.o
                                         0x3c (size before relaxing)
 .eh_frame      0x000000000040ff58       0x20 compiler.o
                                         0x38 (size before relaxing)

.rel.dyn        0x000000000040ff78        0x0
 .rel.got       0x000000000040ff78        0x0 crt0.o
 .rel.iplt      0x000000000040ff78        0x0 crt0.o
 .rel.text      0x000000000040ff78        0x0 crt0.o

.data           0x000000000040ff80     0x2080
                0x000000000040ff80                data = .
                0x000000000040ff80                _data = .
                0x000000000040ff80                __data = .
 *(.data)
 .data          0x000000000040ff80       0x14 crt0.o
 *fill*         0x000000000040ff94        0xc 
 .data          0x000000000040ffa0      0x558 main.o
                0x00000000004104a0                copyright
                0x00000000004104d8                program_name
                0x00000000004104f0                standard_spec
                0x00000000004104f4                running
 .data          0x00000000004104f8        0x0 ctype.o
 .data          0x00000000004104f8        0x8 stdlib.o
                0x00000000004104f8                _infinity
 .data          0x0000000000410500        0x0 stdio.o
 .data          0x0000000000410500        0x0 string.o
 .data          0x0000000000410500        0x0 unistd.o
 .data          0x0000000000410500      0x440 api.o
 .data          0x0000000000410940      0x4e4 lexer.o
 *fill*         0x0000000000410e24       0x1c 
 .data          0x0000000000410e40      0x4e4 parser.o
 *fill*         0x0000000000411324       0x1c 
 .data          0x0000000000411340      0x4e4 tree.o
 .data          0x0000000000411824        0x0 stubs.o
 *fill*         0x0000000000411824       0x1c 
 .data          0x0000000000411840      0x4e4 compiler.o
                0x0000000000412000                . = ALIGN (0x1000)
 *fill*         0x0000000000411d24      0x2dc 

.got            0x0000000000412000        0x0
 .got           0x0000000000412000        0x0 crt0.o

.got.plt        0x0000000000412000        0x0
 .got.plt       0x0000000000412000        0x0 crt0.o

.igot.plt       0x0000000000412000        0x0
 .igot.plt      0x0000000000412000        0x0 crt0.o

.bss            0x0000000000412000    0x3c620
                0x0000000000412000                bss = .
                0x0000000000412000                _bss = .
                0x0000000000412000                __bss = .
 *(.bss)
 .bss           0x0000000000412000        0x0 crt0.o
 .bss           0x0000000000412000     0x8008 main.o
 .bss           0x000000000041a008        0x0 ctype.o
 *fill*         0x000000000041a008       0x18 
 .bss           0x000000000041a020     0x8020 stdlib.o
                0x000000000041a020                environ
 .bss           0x0000000000422040        0x9 stdio.o
 *fill*         0x0000000000422049        0x3 
 .bss           0x000000000042204c        0x4 string.o
 .bss           0x0000000000422050        0xc unistd.o
                0x0000000000422050                __execv_environ
 *fill*         0x000000000042205c        0x4 
 .bss           0x0000000000422060     0x8004 api.o
 *fill*         0x000000000042a064       0x1c 
 .bss           0x000000000042a080     0x8008 lexer.o
 *fill*         0x0000000000432088       0x18 
 .bss           0x00000000004320a0     0x8008 parser.o
 *fill*         0x000000000043a0a8       0x18 
 .bss           0x000000000043a0c0     0x8028 tree.o
                0x000000000043a0c0                exp_offset
                0x000000000043a0c4                buffer_offset
 .bss           0x00000000004420e8        0x0 stubs.o
 *fill*         0x00000000004420e8       0x18 
 .bss           0x0000000000442100     0x8008 compiler.o
                0x000000000044b000                . = ALIGN (0x1000)
 *fill*         0x000000000044a108      0xef8 
 COMMON         0x000000000044b000      0xd08 crt0.o
                0x000000000044b000                g_cursor_x
                0x000000000044b004                stdout
                0x000000000044b008                g_char_attrib
                0x000000000044b00c                g_rows
                0x000000000044b020                Streams
                0x000000000044b0a0                g_using_gui
                0x000000000044b0c0                prompt_out
                0x000000000044b4c0                g_columns
                0x000000000044b4c4                prompt_pos
                0x000000000044b4c8                stdin
                0x000000000044b4cc                prompt_status
                0x000000000044b4e0                prompt_err
                0x000000000044b8e0                stderr
                0x000000000044b900                prompt
                0x000000000044bd00                g_cursor_y
                0x000000000044bd04                prompt_max
 *fill*         0x000000000044bd08       0x18 
 COMMON         0x000000000044bd20     0x238c main.o
                0x000000000044bd20                modifier_found
                0x000000000044bd24                peekSymbol
                0x000000000044bd28                CurrentWindow
                0x000000000044bd2c                lexer_lastline
                0x000000000044bd30                current_keyword
                0x000000000044bd34                stack_count
                0x000000000044bd38                next_index
                0x000000000044bd40                DATA
                0x000000000044bf40                program_bss_address
                0x000000000044bf44                brace_count
                0x000000000044bf48                brace_end
                0x000000000044bf4c                program
                0x000000000044bf60                heapList
                0x000000000044c360                string_flag
                0x000000000044c364                libcHeap
                0x000000000044c368                lexer_token_count
                0x000000000044c36c                type_found
                0x000000000044c370                parentheses_start
                0x000000000044c374                separator_count
                0x000000000044c380                return_info
                0x000000000044c3a0                stack_flag
                0x000000000044c3a4                lexer_lineno
                0x000000000044c3a8                current_constant
                0x000000000044c3ac                temp_filename_length
                0x000000000044c3b0                lexer_code
                0x000000000044c3b4                constant_base_found
                0x000000000044c3b8                constant_aftes
                0x000000000044c3bc                peekChar
                0x000000000044c3c0                lexer_firstline
                0x000000000044c3c4                ApplicationInfo
                0x000000000044c3c8                qualifier_found
                0x000000000044c3cc                infile_size
                0x000000000044c3e0                stack
                0x000000000044c5e0                file_s
                0x000000000044c7e0                current_identifier
                0x000000000044c7e4                heap_start
                0x000000000044c800                STRINGLIST
                0x000000000044c940                asm_flag
                0x000000000044c960                id
                0x000000000044c980                return_found
                0x000000000044c984                BufferInfo
                0x000000000044c9a0                BSS
                0x000000000044cba0                special_count
                0x000000000044cba4                keyword_count
                0x000000000044cba8                current_special
                0x000000000044cbc0                file_i
                0x000000000044cdc0                g_available_heap
                0x000000000044cdc4                g_heap_pointer
                0x000000000044cdc8                current_separator
                0x000000000044cdcc                current_string
                0x000000000044cdd0                current_token
                0x000000000044cdd4                parentheses_count
                0x000000000044cdd8                HEAP_SIZE
                0x000000000044cddc                outfile_size
                0x000000000044cde0                no_output
                0x000000000044ce00                outfile
                0x000000000044d000                string_count
                0x000000000044d020                constant
                0x000000000044d040                constant_word
                0x000000000044d044                parentheses_end
                0x000000000044d060                function_main_buffer
                0x000000000044d260                current_type
                0x000000000044d280                IDENTIFIERLIST
                0x000000000044d3c0                identifier_count
                0x000000000044d3c4                main_return_type
                0x000000000044d3e0                KEYWORDLIST
                0x000000000044d520                constant_byte
                0x000000000044d540                TOKENLIST
                0x000000000044d680                CursorInfo
                0x000000000044d684                keyword_found
                0x000000000044d688                number_of_tokens
                0x000000000044d68c                brace_start
                0x000000000044d690                heap_end
                0x000000000044d694                eofno
                0x000000000044d6a0                CONSTANTLIST
                0x000000000044d7e0                temp_file_queue
                0x000000000044d800                SPECIALLIST
                0x000000000044d940                SEPARATORLIST
                0x000000000044da80                function_main
                0x000000000044da84                program_data_address
                0x000000000044daa0                infile
                0x000000000044dca0                current_index
                0x000000000044dca4                finput
                0x000000000044dca8                HEAP_END
                0x000000000044dcc0                functionList
                0x000000000044dd40                rect
                0x000000000044dd44                compiler_name
                0x000000000044dd48                directive_fould
                0x000000000044dd4c                stack_index
                0x000000000044dd50                main_found
                0x000000000044dd60                TEXT
                0x000000000044df60                ClientAreaInfo
                0x000000000044df64                function_return_type
                0x000000000044df68                Heap
                0x000000000044df6c                constant_dword
                0x000000000044df80                real_token_buffer
                0x000000000044e080                current_semaphore
                0x000000000044e084                constant_type_found
                0x000000000044e088                return_index
                0x000000000044e08c                temp_filename
                0x000000000044e090                program_text_address
                0x000000000044e094                heapCount
                0x000000000044e098                program_header_address
                0x000000000044e09c                constant_before
                0x000000000044e0a0                HEAP_START
                0x000000000044e0a4                constant_count
                0x000000000044e0a8                lineno
 *fill*         0x000000000044e0ac       0x14 
 COMMON         0x000000000044e0c0      0x434 stdlib.o
                0x000000000044e0c0                mm_prev_pointer
                0x000000000044e0e0                mmblockList
                0x000000000044e4e0                last_valid
                0x000000000044e4e4                randseed
                0x000000000044e4e8                mmblockCount
                0x000000000044e4ec                last_size
                0x000000000044e4f0                current_mmblock
 COMMON         0x000000000044e4f4        0x4 unistd.o
                0x000000000044e4f4                errno
 COMMON         0x000000000044e4f8       0x10 api.o
                0x000000000044e4f8                dialogbox_button2
                0x000000000044e4fc                messagebox_button1
                0x000000000044e500                dialogbox_button1
                0x000000000044e504                messagebox_button2
 *fill*         0x000000000044e508       0x18 
 COMMON         0x000000000044e520      0x100 tree.o
                0x000000000044e520                POS_BUFFER
                0x000000000044e5a0                exp_buffer
                0x000000000044e620                end = .
                0x000000000044e620                _end = .
                0x000000000044e620                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdlib.o
LOAD stdio.o
LOAD string.o
LOAD unistd.o
LOAD api.o
LOAD lexer.o
LOAD parser.o
LOAD tree.o
LOAD stubs.o
LOAD compiler.o
OUTPUT(GRAM.BIN elf32-i386)

.comment        0x0000000000000000       0x11
 .comment       0x0000000000000000       0x11 crt0.o
                                         0x12 (size before relaxing)
 .comment       0x0000000000000011       0x12 main.o
 .comment       0x0000000000000011       0x12 ctype.o
 .comment       0x0000000000000011       0x12 stdlib.o
 .comment       0x0000000000000011       0x12 stdio.o
 .comment       0x0000000000000011       0x12 string.o
 .comment       0x0000000000000011       0x12 unistd.o
 .comment       0x0000000000000011       0x12 api.o
 .comment       0x0000000000000011       0x12 lexer.o
 .comment       0x0000000000000011       0x12 parser.o
 .comment       0x0000000000000011       0x12 tree.o
 .comment       0x0000000000000011       0x12 stubs.o
 .comment       0x0000000000000011       0x12 compiler.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 crt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
 .note.GNU-stack
                0x0000000000000000        0x0 ctype.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdlib.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdio.o
 .note.GNU-stack
                0x0000000000000000        0x0 string.o
 .note.GNU-stack
                0x0000000000000000        0x0 unistd.o
 .note.GNU-stack
                0x0000000000000000        0x0 api.o
 .note.GNU-stack
                0x0000000000000000        0x0 lexer.o
 .note.GNU-stack
                0x0000000000000000        0x0 parser.o
 .note.GNU-stack
                0x0000000000000000        0x0 tree.o
 .note.GNU-stack
                0x0000000000000000        0x0 stubs.o
 .note.GNU-stack
                0x0000000000000000        0x0 compiler.o
