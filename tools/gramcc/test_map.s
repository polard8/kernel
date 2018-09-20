
Allocating common symbols
Common symbol       size              file

constant_is_hexa    0x10              main.o
STRINGLIST          0x140             main.o
lexer_lineno        0x10              main.o
current_separator   0x10              main.o
prompt              0x400             main.o
CONSTANTLIST        0x140             main.o
ClientAreaInfo      0x10              main.o
outfile_size        0x10              main.o
identifier_count    0x10              main.o
BufferInfo          0x10              main.o
program_text_address
                    0x10              main.o
return_index        0x10              main.o
main_return_type    0x10              main.o
no_output           0x10              main.o
main_found          0x10              main.o
lexer_firstline     0x10              main.o
stderr              0x10              main.o
SPECIALLIST         0x140             main.o
file_i              0x200             main.o
function_main       0x10              main.o
parentheses_count   0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
return_found        0x10              main.o
compiler_name       0x10              main.o
id                  0x20              main.o
finput              0x10              main.o
mm_prev_pointer     0x10              stdlib.o
special_count       0x10              main.o
asm_flag            0x10              main.o
g_using_gui         0x10              main.o
lexer_lastline      0x10              main.o
stdin               0x10              main.o
functionList        0x80              main.o
file_s              0x200             main.o
brace_start         0x10              main.o
stack_flag          0x10              main.o
heap_end            0x10              stdlib.o
SEPARATORLIST       0x140             main.o
current_special     0x10              main.o
parentheses_start   0x10              main.o
rect                0x10              main.o
type_found          0x10              main.o
g_available_heap    0x10              stdlib.o
current_index       0x10              main.o
lineno              0x10              main.o
brace_count         0x10              main.o
heap_start          0x10              stdlib.o
IDENTIFIERLIST      0x140             main.o
current_type        0x10              main.o
heapCount           0x10              stdlib.o
infile              0x200             main.o
HEAP_START          0x10              stdlib.o
keyword_count       0x10              main.o
prompt_max          0x10              main.o
program_data_address
                    0x10              main.o
next_index          0x10              main.o
temp_filename_length
                    0x10              main.o
program_header_address
                    0x10              main.o
current_keyword     0x10              main.o
CurrentWindow       0x10              main.o
string_count        0x10              main.o
g_heap_pointer      0x10              stdlib.o
parentheses_end     0x10              main.o
heapList            0x400             stdlib.o
keyword_found       0x10              main.o
prompt_err          0x400             main.o
program             0x10              main.o
KEYWORDLIST         0x140             main.o
current_semaphore   0x10              main.o
g_columns           0x10              main.o
current_constant    0x10              main.o
HEAP_SIZE           0x10              stdlib.o
stack_count         0x10              main.o
stdout              0x10              main.o
Streams             0x80              main.o
TOKENLIST           0x140             main.o
last_size           0x10              stdlib.o
directive_fould     0x10              main.o
last_valid          0x10              stdlib.o
g_rows              0x10              main.o
function_main_buffer
                    0x200             main.o
current_identifier  0x10              main.o
temp_filename       0x10              main.o
prompt_out          0x400             main.o
current_string      0x10              main.o
mmblockList         0x400             stdlib.o
program_bss_address
                    0x10              main.o
lexer_token_count   0x10              main.o
outfile             0x200             main.o
lexer_code          0x10              main.o
libcHeap            0x10              stdlib.o
function_return_type
                    0x10              main.o
separator_count     0x10              main.o
real_token_buffer   0x100             main.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
brace_end           0x10              main.o
infile_size         0x10              main.o
CursorInfo          0x10              main.o
mmblockCount        0x10              stdlib.o
prompt_status       0x10              main.o
stack               0x200             main.o
constant_count      0x10              main.o
current_token       0x10              main.o
string_flag         0x10              main.o
stack_index         0x10              main.o
number_of_tokens    0x10              main.o
temp_file_queue     0x10              main.o
g_char_attrib       0x10              main.o
ApplicationInfo     0x10              main.o
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
 *(.text)
 .text          0x00401000        0xc crt0.o
                0x00401000                _crt0Main
 .text          0x0040100c      0x880 main.o
                0x004010ff                fnccmain
                0x00401314                mainTextEditor
                0x00401704                debugShowStat
                0x0040100c                mainGetMessage
                0x0040154e                fncc_print_tokenList
                0x004015c2                fnccInitialize
                0x00401410                editorClearScreen
                0x00401495                create_tokenlist
 .text          0x0040188c       0xe0 ctype.o
                0x00401926                isspace
                0x0040194c                isxdigit
                0x00401939                isupper
                0x0040189f                isalpha
                0x004018eb                islower
                0x0040188c                isalnum
                0x004018fe                isprint
                0x004018d8                isgraph
                0x004018c5                isdigit
                0x004018b2                iscntrl
                0x00401913                ispunct
 .text          0x0040196c      0xae0 stdlib.o
                0x00401c62                FreeHeap
                0x00401994                rtGetHeapStart
                0x00401ea9                free
                0x0040196c                stdlib_system_call
                0x00401e4b                rand
                0x00401dc2                stdlibInitMM
                0x00401c6c                heapInit
                0x00402341                __findenv
                0x004019a8                rtGetHeapPointer
                0x004019b2                rtGetAvailableHeap
                0x00401e22                libcInitRT
                0x004019bc                heapSetLibcHeap
                0x0040240c                getenv
                0x00401e68                malloc
                0x00401c4f                AllocateHeapEx
                0x00401a63                AllocateHeap
                0x004022ba                stdlib_strncmp
                0x00402318                exit
                0x0040199e                rtGetHeapEnd
                0x00401eae                system
 .text          0x0040244c     0x1250 stdio.o
                0x00402dae                putchar
                0x0040244c                stdio_fntos
                0x00402d6a                sprintf
                0x004034ed                feof
                0x00403617                stdioSetCursor
                0x0040344f                ungetc
                0x00402868                puts
                0x004035cb                fputc
                0x0040366d                stdioGetCursorY
                0x00403365                fputs
                0x0040352b                ferror
                0x00402f9a                input
                0x00402639                scroll
                0x00402f90                printf_main
                0x004033da                gets
                0x00402dda                outbyte
                0x004027e3                app_print
                0x00403280                fflush
                0x004032f0                fprintf
                0x00403102                stdio_system_call
                0x004025a1                fopen
                0x00403641                stdioGetCursorX
                0x0040312a                getchar
                0x0040315c                stdioInitialize
                0x0040348c                fgetc
                0x0040253b                fclose
                0x00403551                fseek
                0x00402f5d                _outbyte
                0x00402d4f                printf
                0x00402777                app_clear
 .text          0x0040369c      0x4a0 string.o
                0x00403903                strcspn
                0x00403866                strcat
                0x0040369c                strcmp
                0x004038bd                bzero
                0x00403a43                strtok_r
                0x004037f9                memcpy
                0x004037d0                memoryZeroMemory
                0x00403896                bcopy
                0x00403836                strcpy
                0x004039a3                strspn
                0x00403b18                strtok
                0x00403755                str_cmp
                0x004036f7                strncmp
                0x004038d8                strlen
 .text          0x00403b3c     0x1990 api.o
                0x004048d5                APIShowCurrentProcessInfo
                0x004050c2                api_getchar
                0x004040de                system11
                0x00404183                refresh_buffer
                0x004047b7                APISetFocus
                0x00404141                system14
                0x00404468                apiInitBackground
                0x004046a7                APICreateWindow
                0x00404e7d                apiBeginPaint
                0x0040446d                MessageBox
                0x00404953                APIreplace_window
                0x00404ec4                apiGetSystemMetrics
                0x00404120                system13
                0x00404d34                apiDown
                0x00404a4c                apiExit
                0x00404dcc                enterCriticalSection
                0x00405009                gramadocore_init_execve
                0x00404cba                apiFOpen
                0x00403f94                system1
                0x00404018                system5
                0x00404b32                api_refresh_screen
                0x00405049                apiDialog
                0x00404bbe                apiGetCursorY
                0x00404413                carrega_bitmap_16x16
                0x00404e25                exitCriticalSection
                0x00403b3c                system_call
                0x00404d80                apiUp
                0x00403b64                apiSystem
                0x00404fdd                api_get_window_with_text_input
                0x00404162                system15
                0x00404867                APISetActiveWindow
                0x00404c16                apiSetClientAreaRect
                0x0040492a                APIredraw_window
                0x00404c68                apiCreateThread
                0x004043af                SetNextWindowProcedure
                0x00404b92                apiGetCursorX
                0x0040437f                chama_procedimento
                0x00404496                call_kernel
                0x00404733                APIRegisterWindow
                0x00404aa8                api_strncmp
                0x004049a5                APIminimize_window
                0x00403fb5                system2
                0x00403fd6                system3
                0x00404f16                api_get_current_keyboard_responder
                0x00404c3f                apiCreateProcess
                0x004047f9                APIGetFocus
                0x0040405a                system7
                0x00404039                system6
                0x00404eba                apiDefDialog
                0x00404775                APICloseWindow
                0x00404e51                initializeCriticalSection
                0x004040bd                system10
                0x004043df                set_cursor
                0x0040497c                APImaximize_window
                0x0040503f                execve
                0x00404b06                refresh_screen
                0x004050ee                apiDisplayBMP
                0x00404616                call_gui
                0x0040409c                system9
                0x00405013                fork
                0x00404eed                api_set_current_keyboard_responder
                0x00404901                APIresize_window
                0x00404e87                apiEndPaint
                0x0040440e                put_char
                0x0040431a                print_string
                0x00404bea                apiGetClientAreaRect
                0x00404350                edit_box
                0x00404a77                kill
                0x00404b3c                apiReboot
                0x0040443c                apiShutDown
                0x00404f42                api_set_current_mouse_responder
                0x004049f7                APIget_foregroung_window
                0x00403ff7                system4
                0x00404cf4                apiSaveFile
                0x00404b68                apiSetCursor
                0x004040ff                system12
                0x0040431f                vsync
                0x0040407b                system8
                0x00404f97                api_set_window_with_text_input
                0x004048a9                APIGetActiveWindow
                0x004049ce                APIupdate_window
                0x00404f6b                api_get_current_mouse_responder
                0x00404a7c                dead_thread_collector
                0x00404c91                apiStartThread
                0x00404825                APIKillFocus
                0x00404a23                APIset_foregroung_window
                0x00404e91                apiPutChar
 .text          0x004054cc      0xbf0 lexer.o
                0x00405562                skip_white_space
                0x0040604d                lexerInit
                0x004054cc                check_newline
                0x00406096                error
                0x0040570d                yylex
 .text          0x004060bc      0x600 parser.o
                0x004060bc                parse_def
                0x00406388                parse
                0x004062f6                parse_return
                0x00406625                parserInit
                0x004061d2                parse_var
                0x00407000                . = ALIGN (0x1000)
 *fill*         0x004066bc      0x944 00

.rdata          0x00407000     0x15d0
 .rdata         0x00407000      0x3e0 parser.o
 .rdata         0x004073e0      0x630 lexer.o
 .rdata         0x00407a10      0x320 api.o
 .rdata         0x00407d30       0x40 stdio.o
 .rdata         0x00407d70      0x460 stdlib.o
 .rdata         0x004081d0      0x400 main.o

.data           0x004085d0     0x1a30
                0x004085d0                data = .
                0x004085d0                _data = .
                0x004085d0                __data = .
 *(.data)
 .data          0x004085d0      0x560 main.o
                0x00408b05                program_name
                0x00408b1c                standard_spec
                0x00408b20                running
                0x00408ad0                copyright
 .data          0x00408b30      0x120 ctype.o
                0x00408b30                _ctype_
 .data          0x00408c50       0x10 stdlib.o
 .data          0x00408c60        0x0 stdio.o
 .data          0x00408c60        0x0 string.o
 .data          0x00408c60      0x440 api.o
 .data          0x004090a0      0x500 lexer.o
 .data          0x004095a0      0x500 parser.o
                0x0040a000                . = ALIGN (0x1000)
 *fill*         0x00409aa0      0x560 00

.bss            0x0040a000     0xc090
                0x0040a000                bss = .
                0x0040a000                _bss = .
                0x0040a000                __bss = .
 *(.bss)
 .bss           0x0040a000       0x50 main.o
 .bss           0x0040a050        0x0 ctype.o
 .bss           0x0040a050     0x8010 stdlib.o
                0x0040a050                environ
 .bss           0x00412060       0x10 stdio.o
 .bss           0x00412070       0x10 string.o
 .bss           0x00412080       0x40 api.o
 .bss           0x004120c0       0x50 lexer.o
 .bss           0x00412110       0x50 parser.o
                0x00413000                . = ALIGN (0x1000)
 *fill*         0x00412160      0xea0 00
 COMMON         0x00413000     0x27a0 main.o
                0x00413000                constant_is_hexa
                0x00413010                STRINGLIST
                0x00413150                lexer_lineno
                0x00413160                current_separator
                0x00413170                prompt
                0x00413570                CONSTANTLIST
                0x004136b0                ClientAreaInfo
                0x004136c0                outfile_size
                0x004136d0                identifier_count
                0x004136e0                BufferInfo
                0x004136f0                program_text_address
                0x00413700                return_index
                0x00413710                main_return_type
                0x00413720                no_output
                0x00413730                main_found
                0x00413740                lexer_firstline
                0x00413750                stderr
                0x00413760                SPECIALLIST
                0x004138a0                file_i
                0x00413aa0                function_main
                0x00413ab0                parentheses_count
                0x00413ac0                prompt_pos
                0x00413ad0                return_found
                0x00413ae0                compiler_name
                0x00413af0                id
                0x00413b10                finput
                0x00413b20                special_count
                0x00413b30                asm_flag
                0x00413b40                g_using_gui
                0x00413b50                lexer_lastline
                0x00413b60                stdin
                0x00413b70                functionList
                0x00413bf0                file_s
                0x00413df0                brace_start
                0x00413e00                stack_flag
                0x00413e10                SEPARATORLIST
                0x00413f50                current_special
                0x00413f60                parentheses_start
                0x00413f70                rect
                0x00413f80                type_found
                0x00413f90                current_index
                0x00413fa0                lineno
                0x00413fb0                brace_count
                0x00413fc0                IDENTIFIERLIST
                0x00414100                current_type
                0x00414110                infile
                0x00414310                keyword_count
                0x00414320                prompt_max
                0x00414330                program_data_address
                0x00414340                next_index
                0x00414350                temp_filename_length
                0x00414360                program_header_address
                0x00414370                current_keyword
                0x00414380                CurrentWindow
                0x00414390                string_count
                0x004143a0                parentheses_end
                0x004143b0                keyword_found
                0x004143c0                prompt_err
                0x004147c0                program
                0x004147d0                KEYWORDLIST
                0x00414910                current_semaphore
                0x00414920                g_columns
                0x00414930                current_constant
                0x00414940                stack_count
                0x00414950                stdout
                0x00414960                Streams
                0x004149e0                TOKENLIST
                0x00414b20                directive_fould
                0x00414b30                g_rows
                0x00414b40                function_main_buffer
                0x00414d40                current_identifier
                0x00414d50                temp_filename
                0x00414d60                prompt_out
                0x00415160                current_string
                0x00415170                program_bss_address
                0x00415180                lexer_token_count
                0x00415190                outfile
                0x00415390                lexer_code
                0x004153a0                function_return_type
                0x004153b0                separator_count
                0x004153c0                real_token_buffer
                0x004154c0                g_cursor_y
                0x004154d0                brace_end
                0x004154e0                infile_size
                0x004154f0                CursorInfo
                0x00415500                prompt_status
                0x00415510                stack
                0x00415710                constant_count
                0x00415720                current_token
                0x00415730                string_flag
                0x00415740                stack_index
                0x00415750                number_of_tokens
                0x00415760                temp_file_queue
                0x00415770                g_char_attrib
                0x00415780                ApplicationInfo
                0x00415790                g_cursor_x
 COMMON         0x004157a0      0x8f0 stdlib.o
                0x004157a0                current_mmblock
                0x004157b0                mm_prev_pointer
                0x004157c0                heap_end
                0x004157d0                g_available_heap
                0x004157e0                heap_start
                0x004157f0                heapCount
                0x00415800                HEAP_START
                0x00415810                g_heap_pointer
                0x00415820                heapList
                0x00415c20                HEAP_SIZE
                0x00415c30                last_size
                0x00415c40                last_valid
                0x00415c50                mmblockList
                0x00416050                libcHeap
                0x00416060                Heap
                0x00416070                mmblockCount
                0x00416080                HEAP_END
                0x00416090                end = .
                0x00416090                _end = .
                0x00416090                __end = .
LOAD crt0.o
LOAD main.o
LOAD ctype.o
LOAD stdlib.o
LOAD stdio.o
LOAD string.o
LOAD api.o
LOAD lexer.o
LOAD parser.o
OUTPUT(GRAMCC.BIN pe-i386)

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f crt0.o
