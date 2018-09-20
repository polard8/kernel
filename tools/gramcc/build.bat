:SetUp
@echo off  

    rem 
    rem gramcc.bin - Compilador de linguagem C para o sistema operacional Gramado.
    rem 2018 - Criado por Fred Nora.	
	rem 
	
    cd c:\sdk\bin	
	
:Monting
echo -{ ...
echo -{ Creating application GRAMCC.BIN ...
    
	nasm c:\gramado\tools\gramcc\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc -c c:\gramado\tools\gramcc\main.c   -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gramado\tools\gramcc\lexer.c  -I c:\gramado\include\libc -o lexer.o
	gcc -c c:\gramado\tools\gramcc\parser.c -I c:\gramado\include\libc -o parser.o 	
 
 
    copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
    copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o
 
:Objects	
set myObjects=crt0.o ^
main.o ^
ctype.o ^
stdlib.o ^
stdio.o ^
string.o ^
api.o ^
lexer.o ^
parser.o   


  
:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   ld -T c:\gramado\tools\gramcc\link.ld -o GRAMCC.BIN %myObjects% -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
    move GRAMCC.BIN c:\gramado\bin\GRAMCC.BIN
   
:End   
echo End!
	pause