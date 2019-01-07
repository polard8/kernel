:SetUp
@echo off  

    rem 
    rem gramc.bin - Compilador de linguagem C para o sistema operacional Gramado.
    rem 2018 - Criado por Fred Nora.	
	rem 
	
:fasm_object
    rem ==================================================================
    rem isso está nesse diretório mesmo 
	
    rem #importante
	rem Esse arquivo foi compilado com build.bin em outra pasta. Em /fasm
    rem copy c:\gramado\fasm\FASM.O c:\sdk\bin\FASM.O
	
	rem colocamos FASM.EXE NA SDK para fazermos isso.
    FASM.EXE c:\gt\fasm\SOURCE\LIBC\FASM.ASM FASM.O
	copy FASM.O c:\sdk\bin\FASM.O
	
	rem pause
	rem ==================================================================	
	
	
    cd c:\sdk\bin

	
:Monting
echo -{ ...
echo -{ Creating application FASM.BIN ...
    
	nasm c:\gt\fasm\SOURCE\LIBC\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling ...

    rem incluimos a libc do gramado.
	gcc -c c:\gt\fasm\SOURCE\LIBC\main.c   -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gt\fasm\SOURCE\LIBC\lexer.c  -I c:\gramado\include\libc -o lexer.o
	gcc -c c:\gt\fasm\SOURCE\LIBC\parser.c -I c:\gramado\include\libc -o parser.o 	
 
    rem 
	rem  ## lib do gramado ##
	rem 
 
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
api.o ^
unistd.o ^
lexer.o ^
parser.o ^
FASM.O   



  
:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   ld -T c:\gt\fasm\SOURCE\LIBC\link.ld -o FASM.BIN %myObjects% 
   
   rem Não deletar os objetos.
 
:Moving   
    move FASM.BIN c:\gramado\bin\FASM.BIN
   
:End   
echo End!
	pause