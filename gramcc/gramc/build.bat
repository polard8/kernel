:SetUp
@echo off  

    rem 
    rem gramc.bin - Compilador de linguagem C para o sistema operacional Gramado.
    rem 2018 - Criado por Fred Nora.	
	rem 
	
    cd c:\sdk\bin	
	
:Monting
echo -{ ...
echo -{ Creating application GRAMC.BIN ...
    
	nasm c:\gramado\gramcc\gramc\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc -c c:\gramado\gramcc\gramc\main.c   -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gramado\gramcc\gramc\lexer.c  -I c:\gramado\include\libc -o lexer.o
	gcc -c c:\gramado\gramcc\gramc\parser.c -I c:\gramado\include\libc -o parser.o 	
 
 	gcc -c c:\gramado\gramcc\gramc\tree.c   -I c:\gramado\include\libc -o tree.o  
	
	rem #todo
	rem gcc -c c:\gramado\gramcc\gramc\compiler.c   -I c:\gramado\include\libc -o compiler.o  
	
    copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
    copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o
	
	copy c:\gramado\lib\unistd.o  c:\sdk\bin\unistd.o
	
	
 
:Objects	
set myObjects=crt0.o ^
main.o ^
ctype.o ^
stdlib.o ^
stdio.o ^
string.o ^
unistd.o ^
api.o ^
lexer.o ^
parser.o ^
tree.o  





  
:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   ld -T c:\gramado\gramcc\gramc\link.ld -o GRAMC.BIN %myObjects% 
   
   rem Não deletar os objetos.
 
:Moving   
    move GRAMC.BIN c:\gramado\bin\GRAMC.BIN
   
:End   
echo End!
	pause