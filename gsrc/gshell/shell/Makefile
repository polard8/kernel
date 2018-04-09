all: shell

shell: head.o crt0.o main.o api.o stdio.o stdlib.o string.o
	ld -T link.ld -o SHELL.BIN head.o crt0.o main.o api.o stdio.o stdlib.o string.o -Map shell_map.s
	
head.o: head.s
	nasm  head.s  -felf -o head.o
	
crt0.o: crt0.c
	gcc  -c  crt0.c -o crt0.o 	

main.o: main.c 
	gcc   -c  main.c  -o main.o  