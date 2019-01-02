
#todo:
#fazer um makefile pra compilar o shell 
#obs: #bugbug tem que arrumas as coisas aqui.


all: ead.o crt0.o main.o all-c shell-link

head.o:
	nasm  head.s  -felf -o head.o
	
crt0.o:
	gcc  -c  crt0.c -o crt0.o 

main.o:
	gcc  -c  main.c  -o main.o  
	
all-c:	
    #todo 
	
shell-link: 
	ld -T link.ld -o SHELL.BIN head.o crt0.o main.o api.o stdio.o stdlib.o string.o -Map shell_map.s	