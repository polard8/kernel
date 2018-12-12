:SetUp
@echo off  

    rem 
    rem gramc.bin - Compilador de linguagem C para o sistema operacional Gramado.
    rem 2018 - Criado por Fred Nora.	
	rem 
	
    cd c:\sdk\bin	
	
:Monting
echo -{ ...
echo -{ Creating application GRAMAC.BIN ...
    
	nasm c:\gramado\gramcc\gramac\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc -c c:\gramado\gramcc\gramac\main.c   -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gramado\gramcc\gramac\lexer.c  -I c:\gramado\include\libc -o lexer.o
	gcc -c c:\gramado\gramcc\gramac\parser.c -I c:\gramado\include\libc -o parser.o 	
 
 
    copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
    copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o
 
 
    rem test
    copy c:\gramado\fasm\FASM.O c:\sdk\bin\FASM.O
	
 
:Objects	
set myObjects=crt0.o ^
main.o ^
ctype.o ^
stdlib.o ^
stdio.o ^
string.o ^
api.o ^
lexer.o ^
parser.o ^
FASM.O   





  
:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   ld -T c:\gramado\gramcc\gramac\link.ld -o GRAMAC.BIN %myObjects% 
   
   rem Não deletar os objetos.
 
:Moving   
    move GRAMAC.BIN c:\gramado\bin\GRAMAC.BIN
   
:End   
echo End!
	pause