

x:
	nasm -I kernel/entry/x86/head/ kernel/entry/x86/head/head.s -f elf -o head.o