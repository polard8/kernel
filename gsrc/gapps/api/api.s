	.file	"api.c"
	.text
.globl _system_call
	.def	_system_call;	.scl	2;	.type	32;	.endef
_system_call:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	$0, -8(%ebp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $200 

/NO_APP
	movl	%eax, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC0:
	.ascii "test\0"
	.align 4
LC1:
	.ascii "apiSystem: Testing commands ...\12\0"
LC2:
	.ascii "ls\0"
LC3:
	.ascii "apiSystem: @todo: ls ...\12\0"
LC4:
	.ascii "makeboot\0"
	.align 4
LC5:
	.ascii "apiSystem: @todo: makeboot ...\12\0"
LC6:
	.ascii "format\0"
LC7:
	.ascii "apiSystem: @todo: format ...\12\0"
LC8:
	.ascii "debug\0"
LC9:
	.ascii "apiSystem: @todo: debug ...\12\0"
LC10:
	.ascii "dir\0"
LC11:
	.ascii "apiSystem: @todo: dir ...\12\0"
LC12:
	.ascii "newfile\0"
	.align 4
LC13:
	.ascii "apiSystem: ~newfile - Create empty file.\12\0"
LC14:
	.ascii "newdir\0"
	.align 4
LC15:
	.ascii "apiSystem: ~newdir - Create empty folder.\12\0"
LC16:
	.ascii "mbr\0"
LC17:
	.ascii "apiSystem: ~mbr\12\0"
LC18:
	.ascii "root\0"
LC19:
	.ascii "apiSystem: ~/root\12\0"
LC20:
	.ascii "start\0"
LC21:
	.ascii "apiSystem: ~start\12\0"
LC22:
	.ascii "help\0"
LC23:
	.ascii "apiSystem: help stuff\12\0"
LC24:
	.ascii "cls\0"
LC25:
	.ascii "apiSystem: cls\12\0"
LC26:
	.ascii "save\0"
LC27:
	.ascii "apiSystem: ~save\12\0"
LC28:
	.ascii "install\0"
LC29:
	.ascii "apiSystem: ~install\12\0"
LC30:
	.ascii "boot\0"
LC31:
	.ascii "apiSystem: ~boot\12\0"
LC32:
	.ascii "service\0"
	.align 4
LC33:
	.ascii "apiSystem: ~service - rotina de servicos do kernel base\12\0"
LC34:
	.ascii "slots\0"
	.align 4
LC35:
	.ascii "apiSystem: ~slots - mostra slots \12\0"
LC36:
	.ascii "exit\0"
LC37:
	.ascii "apiSystem: exit\12\0"
LC38:
	.ascii "reboot\0"
LC39:
	.ascii "apiSystem: reboot\12\0"
LC40:
	.ascii "shutdown\0"
LC41:
	.ascii "apiSystem: shutdown\12\0"
LC42:
	.ascii "apiSystem: Unknown command!\12\0"
LC43:
	.ascii "apiSystem: FAIL\12\0"
	.text
.globl _apiSystem
	.def	_apiSystem;	.scl	2;	.type	32;	.endef
_apiSystem:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$4, 8(%esp)
	movl	$LC0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L4
	movl	$LC1, (%esp)
	call	_printf
	jmp	L5
L4:
	movl	$2, 8(%esp)
	movl	$LC2, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L6
	movl	$LC3, (%esp)
	call	_printf
	jmp	L5
L6:
	movl	$8, 8(%esp)
	movl	$LC4, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L7
	movl	$LC5, (%esp)
	call	_printf
	jmp	L5
L7:
	movl	$6, 8(%esp)
	movl	$LC6, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L8
	movl	$LC7, (%esp)
	call	_printf
	jmp	L5
L8:
	movl	$5, 8(%esp)
	movl	$LC8, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L9
	movl	$LC9, (%esp)
	call	_printf
	jmp	L5
L9:
	movl	$3, 8(%esp)
	movl	$LC10, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L10
	movl	$LC11, (%esp)
	call	_printf
	jmp	L5
L10:
	movl	$7, 8(%esp)
	movl	$LC12, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L11
	movl	$LC13, (%esp)
	call	_printf
	jmp	L5
L11:
	movl	$7, 8(%esp)
	movl	$LC14, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L12
	movl	$LC15, (%esp)
	call	_printf
	jmp	L5
L12:
	movl	$3, 8(%esp)
	movl	$LC16, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L13
	movl	$LC17, (%esp)
	call	_printf
	jmp	L5
L13:
	movl	$4, 8(%esp)
	movl	$LC18, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L14
	movl	$LC19, (%esp)
	call	_printf
	jmp	L5
L14:
	movl	$5, 8(%esp)
	movl	$LC20, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L15
	movl	$LC21, (%esp)
	call	_printf
	jmp	L5
L15:
	movl	$4, 8(%esp)
	movl	$LC22, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L16
	movl	$LC23, (%esp)
	call	_printf
	jmp	L5
L16:
	movl	$3, 8(%esp)
	movl	$LC24, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L17
	movl	$LC25, (%esp)
	call	_printf
	jmp	L5
L17:
	movl	$4, 8(%esp)
	movl	$LC26, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L18
	movl	$LC27, (%esp)
	call	_printf
	jmp	L5
L18:
	movl	$7, 8(%esp)
	movl	$LC28, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L19
	movl	$LC29, (%esp)
	call	_printf
	jmp	L5
L19:
	movl	$4, 8(%esp)
	movl	$LC30, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L20
	movl	$LC31, (%esp)
	call	_printf
	jmp	L5
L20:
	movl	$7, 8(%esp)
	movl	$LC32, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L21
	movl	$LC33, (%esp)
	call	_printf
	jmp	L5
L21:
	movl	$5, 8(%esp)
	movl	$LC34, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L22
	movl	$LC35, (%esp)
	call	_printf
	jmp	L5
L22:
	movl	$4, 8(%esp)
	movl	$LC36, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L23
	movl	$LC37, (%esp)
	call	_printf
	movl	$0, (%esp)
	call	_exit
L23:
	movl	$6, 8(%esp)
	movl	$LC38, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L25
	movl	$LC39, (%esp)
	call	_printf
	call	_apiReboot
	jmp	L24
L25:
	movl	$8, 8(%esp)
	movl	$LC40, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_api_strncmp
	testl	%eax, %eax
	jne	L26
	movl	$LC41, (%esp)
	call	_printf
	call	_apiShutDown
	jmp	L24
L26:
	movl	$LC42, (%esp)
	call	_printf
L24:
	movl	$LC43, (%esp)
	call	_printf
	movl	$1, -4(%ebp)
	jmp	L3
L5:
	movl	$0, -4(%ebp)
L3:
	movl	-4(%ebp), %eax
	leave
	ret
.globl _system1
	.def	_system1;	.scl	2;	.type	32;	.endef
_system1:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	 int $201 

/NO_APP
	movl	%eax, -8(%ebp)
L28:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system2
	.def	_system2;	.scl	2;	.type	32;	.endef
_system2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	 int $202 

/NO_APP
	movl	%eax, -8(%ebp)
L30:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system3
	.def	_system3;	.scl	2;	.type	32;	.endef
_system3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $203

/NO_APP
	movl	%eax, -8(%ebp)
L32:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system4
	.def	_system4;	.scl	2;	.type	32;	.endef
_system4:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $204

/NO_APP
	movl	%eax, -8(%ebp)
L34:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system5
	.def	_system5;	.scl	2;	.type	32;	.endef
_system5:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $205

/NO_APP
	movl	%eax, -8(%ebp)
L36:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system6
	.def	_system6;	.scl	2;	.type	32;	.endef
_system6:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $206

/NO_APP
	movl	%eax, -8(%ebp)
L38:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system7
	.def	_system7;	.scl	2;	.type	32;	.endef
_system7:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $207

/NO_APP
	movl	%eax, -8(%ebp)
L40:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system8
	.def	_system8;	.scl	2;	.type	32;	.endef
_system8:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $208

/NO_APP
	movl	%eax, -8(%ebp)
L42:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system9
	.def	_system9;	.scl	2;	.type	32;	.endef
_system9:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $209

/NO_APP
	movl	%eax, -8(%ebp)
L44:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system10
	.def	_system10;	.scl	2;	.type	32;	.endef
_system10:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $210

/NO_APP
	movl	%eax, -8(%ebp)
L46:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system11
	.def	_system11;	.scl	2;	.type	32;	.endef
_system11:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $211

/NO_APP
	movl	%eax, -8(%ebp)
L48:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system12
	.def	_system12;	.scl	2;	.type	32;	.endef
_system12:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $212

/NO_APP
	movl	%eax, -8(%ebp)
L50:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system13
	.def	_system13;	.scl	2;	.type	32;	.endef
_system13:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	 int $213 

/NO_APP
	movl	%eax, -8(%ebp)
L52:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system14
	.def	_system14;	.scl	2;	.type	32;	.endef
_system14:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	 int $214 
 
/NO_APP
	movl	%eax, -8(%ebp)
L54:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _system15
	.def	_system15;	.scl	2;	.type	32;	.endef
_system15:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
/APP
	int $215

/NO_APP
	movl	%eax, -8(%ebp)
L56:
	movl	-8(%ebp), %eax
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _refresh_buffer
	.def	_refresh_buffer;	.scl	2;	.type	32;	.endef
_refresh_buffer:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	cmpl	$0, 8(%ebp)
	je	L57
	cmpl	$9, 8(%ebp)
	ja	L57
	cmpl	$9, 8(%ebp)
	ja	L57
	movl	8(%ebp), %eax
	sall	$2, %eax
	movl	L71(%eax), %eax
	jmp	*%eax
	.section .rdata,"dr"
	.align 4
L71:
	.long	L57
	.long	L61
	.long	L62
	.long	L63
	.long	L64
	.long	L65
	.long	L66
	.long	L67
	.long	L68
	.long	L69
	.text
L61:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1, (%esp)
	call	_system_call
	jmp	L57
L62:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$2, (%esp)
	call	_system_call
	jmp	L57
L63:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	_system_call
	jmp	L57
L64:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$4, (%esp)
	call	_system_call
	jmp	L57
L65:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$5, (%esp)
	call	_system_call
	jmp	L57
L66:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$6, (%esp)
	call	_system_call
	jmp	L57
L67:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$7, (%esp)
	call	_system_call
	jmp	L57
L68:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$8, (%esp)
	call	_system_call
	jmp	L57
L69:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$9, (%esp)
	call	_system_call
L72:
L57:
	leave
	ret
.globl _print_string
	.def	_print_string;	.scl	2;	.type	32;	.endef
_print_string:
L74:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _vsync
	.def	_vsync;	.scl	2;	.type	32;	.endef
_vsync:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$5, (%esp)
	call	_system_call
	movl	$0, %eax
	leave
	ret
.globl _edit_box
	.def	_edit_box;	.scl	2;	.type	32;	.endef
_edit_box:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$33, (%esp)
	call	_system_call
	movl	$0, %eax
	leave
	ret
.globl _chama_procedimento
	.def	_chama_procedimento;	.scl	2;	.type	32;	.endef
_chama_procedimento:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$37, (%esp)
	call	_system_call
	movl	$0, %eax
	leave
	ret
.globl _SetNextWindowProcedure
	.def	_SetNextWindowProcedure;	.scl	2;	.type	32;	.endef
_SetNextWindowProcedure:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$35, (%esp)
	call	_system_call
	movl	$0, %eax
	leave
	ret
.globl _set_cursor
	.def	_set_cursor;	.scl	2;	.type	32;	.endef
_set_cursor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$34, (%esp)
	call	_system_call
	movl	$0, %eax
	leave
	ret
.globl _put_char
	.def	_put_char;	.scl	2;	.type	32;	.endef
_put_char:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _carrega_bitmap_16x16
	.def	_carrega_bitmap_16x16;	.scl	2;	.type	32;	.endef
_carrega_bitmap_16x16:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$42, (%esp)
	call	_system_call
	leave
	ret
.globl _apiShutDown
	.def	_apiShutDown;	.scl	2;	.type	32;	.endef
_apiShutDown:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$40, (%esp)
	call	_system_call
L83:
	jmp	L83
.globl _apiInitBackground
	.def	_apiInitBackground;	.scl	2;	.type	32;	.endef
_apiInitBackground:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _MessageBox
	.def	_MessageBox;	.scl	2;	.type	32;	.endef
_MessageBox:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$45, (%esp)
	call	_system_call
	leave
	ret
.globl _call_kernel
	.def	_call_kernel;	.scl	2;	.type	32;	.endef
_call_kernel:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	cmpl	$53, -12(%ebp)
	je	L94
	cmpl	$53, -12(%ebp)
	ja	L101
	cmpl	$50, -12(%ebp)
	je	L91
	cmpl	$50, -12(%ebp)
	ja	L102
	cmpl	$48, -12(%ebp)
	je	L89
	cmpl	$49, -12(%ebp)
	je	L90
	jmp	L104
L102:
	cmpl	$51, -12(%ebp)
	je	L92
	cmpl	$52, -12(%ebp)
	je	L93
	jmp	L104
L101:
	cmpl	$56, -12(%ebp)
	je	L97
	cmpl	$56, -12(%ebp)
	ja	L103
	cmpl	$54, -12(%ebp)
	je	L95
	cmpl	$55, -12(%ebp)
	je	L96
	jmp	L104
L103:
	cmpl	$57, -12(%ebp)
	je	L98
	cmpl	$199, -12(%ebp)
	je	L99
	jmp	L104
L89:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $48 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L90:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $49 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L91:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $50 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L92:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $51 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L93:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $52 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L94:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $53 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L95:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $54 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L96:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $55 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L97:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $56 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L98:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $57 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L104
L99:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $199 

/NO_APP
	movl	%eax, -8(%ebp)
L104:
	movl	-8(%ebp), %eax
	addl	$8, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _call_gui
	.def	_call_gui;	.scl	2;	.type	32;	.endef
_call_gui:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	cmpl	$217, -12(%ebp)
	je	L108
	cmpl	$217, -12(%ebp)
	ja	L112
	cmpl	$216, -12(%ebp)
	je	L107
	jmp	L113
L112:
	cmpl	$218, -12(%ebp)
	je	L109
	cmpl	$219, -12(%ebp)
	je	L110
	jmp	L113
L107:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	 int $216 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L113
L108:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $217 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L113
L109:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $218 

/NO_APP
	movl	%eax, -8(%ebp)
	jmp	L113
L110:
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	24(%ebp), %ecx
	movl	28(%ebp), %edx
/APP
	int $219 

/NO_APP
	movl	%eax, -8(%ebp)
L113:
	movl	-8(%ebp), %eax
	addl	$8, %esp
	popl	%ebx
	popl	%ebp
	ret
.globl _APICreateWindow
	.def	_APICreateWindow;	.scl	2;	.type	32;	.endef
_APICreateWindow:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	52(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$47, (%esp)
	call	_system_call
	movl	40(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	28(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$48, (%esp)
	call	_system_call
	movl	$0, 12(%esp)
	movl	36(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$49, (%esp)
	call	_system_call
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$10, (%esp)
	call	_system_call
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	jne	L117
	movl	$0, -8(%ebp)
	jmp	L114
L117:
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
L114:
	movl	-8(%ebp), %eax
	leave
	ret
.globl _APIRegisterWindow
	.def	_APIRegisterWindow;	.scl	2;	.type	32;	.endef
_APIRegisterWindow:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	cmpl	$0, 8(%ebp)
	jne	L119
	movl	$1, -4(%ebp)
	jmp	L118
L119:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$57, (%esp)
	call	_system_call
	movl	$0, -4(%ebp)
L118:
	movl	-4(%ebp), %eax
	leave
	ret
.globl _APICloseWindow
	.def	_APICloseWindow;	.scl	2;	.type	32;	.endef
_APICloseWindow:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	cmpl	$0, 8(%ebp)
	jne	L121
	movl	$1, -4(%ebp)
	jmp	L120
L121:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$58, (%esp)
	call	_system_call
	movl	$0, -4(%ebp)
L120:
	movl	-4(%ebp), %eax
	leave
	ret
.globl _APISetFocus
	.def	_APISetFocus;	.scl	2;	.type	32;	.endef
_APISetFocus:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	cmpl	$0, 8(%ebp)
	jne	L123
	movl	$1, -4(%ebp)
	jmp	L122
L123:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$62, (%esp)
	call	_system_call
	movl	$0, -4(%ebp)
L122:
	movl	-4(%ebp), %eax
	leave
	ret
.globl _APIGetFocus
	.def	_APIGetFocus;	.scl	2;	.type	32;	.endef
_APIGetFocus:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$63, (%esp)
	call	_system_call
	leave
	ret
.globl _APIKillFocus
	.def	_APIKillFocus;	.scl	2;	.type	32;	.endef
_APIKillFocus:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	cmpl	$0, 8(%ebp)
	jne	L126
	movl	$1, -4(%ebp)
	jmp	L125
L126:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$64, (%esp)
	call	_system_call
	movl	$0, -4(%ebp)
L125:
	movl	-4(%ebp), %eax
	leave
	ret
.globl _APISetActiveWindow
	.def	_APISetActiveWindow;	.scl	2;	.type	32;	.endef
_APISetActiveWindow:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	cmpl	$0, 8(%ebp)
	jne	L128
	movl	$1, -4(%ebp)
	jmp	L127
L128:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$60, (%esp)
	call	_system_call
	movl	$0, -4(%ebp)
L127:
	movl	-4(%ebp), %eax
	leave
	ret
.globl _APIGetActiveWindow
	.def	_APIGetActiveWindow;	.scl	2;	.type	32;	.endef
_APIGetActiveWindow:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$61, (%esp)
	call	_system_call
	leave
	ret
.globl _APIShowCurrentProcessInfo
	.def	_APIShowCurrentProcessInfo;	.scl	2;	.type	32;	.endef
_APIShowCurrentProcessInfo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$80, (%esp)
	call	_system_call
	leave
	ret
.globl _APIresize_window
	.def	_APIresize_window;	.scl	2;	.type	32;	.endef
_APIresize_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$50, (%esp)
	call	_system_call
	leave
	ret
.globl _APIredraw_window
	.def	_APIredraw_window;	.scl	2;	.type	32;	.endef
_APIredraw_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$51, (%esp)
	call	_system_call
	leave
	ret
.globl _APIreplace_window
	.def	_APIreplace_window;	.scl	2;	.type	32;	.endef
_APIreplace_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$52, (%esp)
	call	_system_call
	leave
	ret
.globl _APImaximize_window
	.def	_APImaximize_window;	.scl	2;	.type	32;	.endef
_APImaximize_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$53, (%esp)
	call	_system_call
	leave
	ret
.globl _APIminimize_window
	.def	_APIminimize_window;	.scl	2;	.type	32;	.endef
_APIminimize_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$54, (%esp)
	call	_system_call
	leave
	ret
.globl _APIget_foregroung_window
	.def	_APIget_foregroung_window;	.scl	2;	.type	32;	.endef
_APIget_foregroung_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$55, (%esp)
	call	_system_call
	leave
	ret
.globl _APIset_foregroung_window
	.def	_APIset_foregroung_window;	.scl	2;	.type	32;	.endef
_APIset_foregroung_window:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$56, (%esp)
	call	_system_call
	leave
	ret
.globl _exit
	.def	_exit;	.scl	2;	.type	32;	.endef
_exit:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$70, (%esp)
	call	_system_call
L139:
L140:
	jmp	L140
.globl _kill
	.def	_kill;	.scl	2;	.type	32;	.endef
_kill:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
.globl _dead_thread_collector
	.def	_dead_thread_collector;	.scl	2;	.type	32;	.endef
_dead_thread_collector:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$90, (%esp)
	call	_system_call
	leave
	ret
L144:
.globl _api_strncmp
	.def	_api_strncmp;	.scl	2;	.type	32;	.endef
_api_strncmp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	16(%ebp), %eax
	movl	%eax, -4(%ebp)
L146:
	cmpl	$0, -4(%ebp)
	jle	L147
	leal	-4(%ebp), %eax
	decl	(%eax)
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movzbl	(%eax), %eax
	cmpb	(%edx), %al
	je	L148
	movl	$1, -8(%ebp)
	jmp	L145
L148:
	incl	8(%ebp)
	leal	12(%ebp), %eax
	incl	(%eax)
	jmp	L146
L147:
	movl	8(%ebp), %eax
	cmpb	$0, (%eax)
	jne	L150
	movl	12(%ebp), %eax
	cmpb	$0, (%eax)
	jne	L150
	jmp	L151
L150:
	movl	$2, -8(%ebp)
	jmp	L145
L151:
	movl	$0, -8(%ebp)
L145:
	movl	-8(%ebp), %eax
	leave
	ret
.globl _refresh_screen
	.def	_refresh_screen;	.scl	2;	.type	32;	.endef
_refresh_screen:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$11, (%esp)
	call	_system_call
	leave
	ret
.globl _api_refresh_screen
	.def	_api_refresh_screen;	.scl	2;	.type	32;	.endef
_api_refresh_screen:
	pushl	%ebp
	movl	%esp, %ebp
	call	_refresh_screen
	popl	%ebp
	ret
.globl _apiReboot
	.def	_apiReboot;	.scl	2;	.type	32;	.endef
_apiReboot:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$110, (%esp)
	call	_system_call
	leave
	ret
.globl _apiSetCursor
	.def	_apiSetCursor;	.scl	2;	.type	32;	.endef
_apiSetCursor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$34, (%esp)
	call	_system_call
	leave
	ret
.globl _apiGetCursorX
	.def	_apiGetCursorX;	.scl	2;	.type	32;	.endef
_apiGetCursorX:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$240, (%esp)
	call	_system_call
	leave
	ret
.globl _apiGetCursorY
	.def	_apiGetCursorY;	.scl	2;	.type	32;	.endef
_apiGetCursorY:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$241, (%esp)
	call	_system_call
	leave
	ret
.globl _apiGetClientAreaRect
	.def	_apiGetClientAreaRect;	.scl	2;	.type	32;	.endef
_apiGetClientAreaRect:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$144, (%esp)
	call	_system_call
	leave
	ret
.globl _apiSetClientAreaRect
	.def	_apiSetClientAreaRect;	.scl	2;	.type	32;	.endef
_apiSetClientAreaRect:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$145, (%esp)
	call	_system_call
	leave
	ret
.globl _apiCreateProcess
	.def	_apiCreateProcess;	.scl	2;	.type	32;	.endef
_apiCreateProcess:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$73, (%esp)
	call	_system_call
	leave
	ret
.globl _apiCreateThread
	.def	_apiCreateThread;	.scl	2;	.type	32;	.endef
_apiCreateThread:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$72, (%esp)
	call	_system_call
	leave
	ret
.globl _apiStartThread
	.def	_apiStartThread;	.scl	2;	.type	32;	.endef
_apiStartThread:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$94, (%esp)
	call	_system_call
	leave
	ret
.globl _apiFOpen
	.def	_apiFOpen;	.scl	2;	.type	32;	.endef
_apiFOpen:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$3, (%esp)
	call	_system_call
	leave
	ret
.globl _apiDown
	.def	_apiDown;	.scl	2;	.type	32;	.endef
_apiDown:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	$1, -4(%ebp)
	cmpl	$0, 8(%ebp)
	jne	L168
L166:
	jmp	L166
L168:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$87, (%esp)
	call	_system_call
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	jne	L169
	jmp	L164
L169:
	movl	$1, -4(%ebp)
	jmp	L168
L171:
L164:
	leave
	ret
.globl _apiUp
	.def	_apiUp;	.scl	2;	.type	32;	.endef
_apiUp:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	$1, -4(%ebp)
	cmpl	$0, 8(%ebp)
	jne	L176
L174:
	jmp	L174
L176:
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$89, (%esp)
	call	_system_call
	movl	%eax, -4(%ebp)
	cmpl	$0, -4(%ebp)
	jne	L177
	jmp	L172
L177:
	movl	$1, -4(%ebp)
	jmp	L176
L179:
L172:
	leave
	ret
.globl _enterCriticalSection
	.def	_enterCriticalSection;	.scl	2;	.type	32;	.endef
_enterCriticalSection:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
L181:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$226, (%esp)
	call	_system_call
	movl	%eax, -4(%ebp)
	cmpl	$1, -4(%ebp)
	jne	L181
L184:
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$227, (%esp)
	call	_system_call
	leave
	ret
.globl _exitCriticalSection
	.def	_exitCriticalSection;	.scl	2;	.type	32;	.endef
_exitCriticalSection:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$228, (%esp)
	call	_system_call
	leave
	ret
.globl _initializeCriticalSection
	.def	_initializeCriticalSection;	.scl	2;	.type	32;	.endef
_initializeCriticalSection:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$228, (%esp)
	call	_system_call
	leave
	ret
.globl _apiBeginPaint
	.def	_apiBeginPaint;	.scl	2;	.type	32;	.endef
_apiBeginPaint:
	pushl	%ebp
	movl	%esp, %ebp
	call	_enterCriticalSection
	popl	%ebp
	ret
.globl _apiEndPaint
	.def	_apiEndPaint;	.scl	2;	.type	32;	.endef
_apiEndPaint:
	pushl	%ebp
	movl	%esp, %ebp
	call	_exitCriticalSection
	popl	%ebp
	ret
.globl _apiPutChar
	.def	_apiPutChar;	.scl	2;	.type	32;	.endef
_apiPutChar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$65, (%esp)
	call	_system_call
	leave
	ret
.globl _apiDefDialog
	.def	_apiDefDialog;	.scl	2;	.type	32;	.endef
_apiDefDialog:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret
.globl _apiGetSystemMetrics
	.def	_apiGetSystemMetrics;	.scl	2;	.type	32;	.endef
_apiGetSystemMetrics:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$250, (%esp)
	call	_system_call
	leave
	ret
.globl _api_set_current_keyboard_responder
	.def	_api_set_current_keyboard_responder;	.scl	2;	.type	32;	.endef
_api_set_current_keyboard_responder:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$140, (%esp)
	call	_system_call
	leave
	ret
.globl _api_get_current_keyboard_responder
	.def	_api_get_current_keyboard_responder;	.scl	2;	.type	32;	.endef
_api_get_current_keyboard_responder:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$141, (%esp)
	call	_system_call
	leave
	ret
.globl _api_set_current_mouse_responder
	.def	_api_set_current_mouse_responder;	.scl	2;	.type	32;	.endef
_api_set_current_mouse_responder:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$142, (%esp)
	call	_system_call
	leave
	ret
.globl _api_get_current_mouse_responder
	.def	_api_get_current_mouse_responder;	.scl	2;	.type	32;	.endef
_api_get_current_mouse_responder:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$143, (%esp)
	call	_system_call
	leave
	ret
.globl _api_set_window_with_text_input
	.def	_api_set_window_with_text_input;	.scl	2;	.type	32;	.endef
_api_set_window_with_text_input:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	cmpl	$0, 8(%ebp)
	jne	L197
	jmp	L196
L197:
	movl	8(%ebp), %eax
	cmpl	$1, 20(%eax)
	jne	L196
	movl	8(%ebp), %eax
	cmpl	$1234, 24(%eax)
	jne	L196
	movl	8(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$133, (%esp)
	call	_system_call
L196:
	leave
	ret
.globl _api_get_window_with_text_input
	.def	_api_get_window_with_text_input;	.scl	2;	.type	32;	.endef
_api_get_window_with_text_input:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$134, (%esp)
	call	_system_call
	leave
	ret
.lcomm _Heap,16
.lcomm _ProcessHeap,16
.lcomm _DesktopHeap,16
	.comm	_ApplicationInfo, 16	 # 4
	.comm	_BufferInfo, 16	 # 4
	.comm	_ClientAreaInfo, 16	 # 4
	.comm	_CursorInfo, 16	 # 4
	.comm	_rect, 16	 # 4
	.comm	_CurrentWindow, 16	 # 4
	.comm	_current_semaphore, 16	 # 4
	.def	_apiShutDown;	.scl	3;	.type	32;	.endef
	.def	_apiReboot;	.scl	3;	.type	32;	.endef
	.def	_exit;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_api_strncmp;	.scl	3;	.type	32;	.endef
