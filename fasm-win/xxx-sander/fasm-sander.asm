
; flat assembler interface for Linux
; Copyright (c) 1999-2018, Tomasz Grysztar.
; All rights reserved.

	format	ELF executable 3
	entry	start

segment readable executable

start:

	mov	[con_handle],1
	mov	esi,_logo
	call	display_string

	mov	ebx,omgevingsvoorbeeld
	mov	[command_line],ebx
	mov	ecx,[esp]
	mov	ebx,[esp+4+ecx*4+4]
	mov	ebx,omgevingsvoorbeeld
	mov	[environment],ebx
	call	get_params
	jc	information

	call	init_memory

	mov	esi,_memory_prefix
	call	display_string
	mov	eax,[memory_end]
	sub	eax,[memory_start]
	add	eax,[additional_memory_end]
	sub	eax,[additional_memory]
	shr	eax,10
	call	display_number
	mov	esi,_memory_suffix
	call	display_string

	mov	eax,78
	mov	ebx,buffer
	xor	ecx,ecx
	int	0x80
	mov	eax,dword [buffer]
	mov	ecx,1000
	mul	ecx
	mov	ebx,eax
	mov	eax,dword [buffer+4]
	div	ecx
	add	eax,ebx
	mov	[start_time],eax

	and	[preprocessing_done],0
	call	preprocessor
	or	[preprocessing_done],-1
	call	parser
	call	assembler
	call	formatter

	call	display_user_messages
	movzx	eax,[current_pass]
	inc	eax
	call	display_number
	mov	esi,_passes_suffix
	call	display_string
	mov	eax,78
	mov	ebx,buffer
	xor	ecx,ecx
	int	0x80
	mov	eax,dword [buffer]
	mov	ecx,1000
	mul	ecx
	mov	ebx,eax
	mov	eax,dword [buffer+4]
	div	ecx
	add	eax,ebx
	sub	eax,[start_time]
	jnc	time_ok
	add	eax,3600000
      time_ok:
	xor	edx,edx
	mov	ebx,100
	div	ebx
	or	eax,eax
	jz	display_bytes_count
	xor	edx,edx
	mov	ebx,10
	div	ebx
	push	edx
	call	display_number
	mov	dl,'.'
	call	display_character
	pop	eax
	call	display_number
	mov	esi,_seconds_suffix
	call	display_string
      display_bytes_count:
	mov	eax,[written_size]
	call	display_number
	mov	esi,_bytes_suffix
	call	display_string
	xor	al,al
	jmp	exit_program

information:
	mov	esi,_usage
	call	display_string
	mov	al,1
	jmp	exit_program

get_params:
	mov	esi,stdinput
	mov	[input_file],esi
	mov	esi,stdoutput
	mov	[output_file],esi
	mov	[symbols_file],0
	mov	[memory_setting],0
	mov	[passes_limit],100
	mov	[definitions_pointer],predefinitions
	ret

include 'system.inc'

include '..\version.inc'

_copyright db 'Copyright (c) 1999-2018, Tomasz Grysztar',0xA,0

_logo db 'flat assembler ported for SoS version ',VERSION_STRING,0
_usage db 0xA
       db 'usage: fasm <source> [output]',0xA
       db 'optional settings:',0xA
       db ' -m <limit>         set the limit in kilobytes for the available memory',0xA
       db ' -p <limit>         set the maximum allowed number of passes',0xA
       db ' -d <name>=<value>  define symbolic variable',0xA
       db ' -s <file>          dump symbolic information for debugging',0xA
       db 0
_memory_prefix db '  (',0
_memory_suffix db ' kilobytes memory)',0xA,0
_passes_suffix db ' passes, ',0
_seconds_suffix db ' seconds, ',0
_bytes_suffix db ' bytes.',0xA,0


include '..\errors.inc'
include '..\symbdump.inc'
include '..\preproce.inc'
include '..\parser.inc'
include '..\exprpars.inc'
include '..\assemble.inc'
include '..\exprcalc.inc'
include '..\formats.inc'
include '..\x86_64.inc'
include '..\avx.inc'

include '..\tables.inc'
include '..\messages.inc'

segment readable writeable

align 4

include '..\variable.inc'

command_line dd ?
memory_setting dd ?
definitions_pointer dd ?
environment dd ?
timestamp dq ?
start_time dd ?
con_handle dd ?
displayed_count dd ?
last_displayed db ?
character db ?
preprocessing_done db ?

predefinitions rb 1000h
buffer rb 1000h
omgevingsvoorbeeld db "",0x00
stdinput db "input.asm",0x00
stdoutput db "output.elf",0x00
defmempnt rb 200000
defmemend:
defmempnt2 rb 200000
defmemend2:
