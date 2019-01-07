:SetUp
    @echo off
	
	cd c:\sdk\bin

:Mounting	
echo -{ ...
echo -{ head
	
	nasm c:\norax\init\core\taskman\head.s -felf -o head.o

:Compiling	
echo -{ ...
echo -{ Compiling TASKMAN.BIN.
    
	gcc -c c:\norax\init\core\taskman\crt0.c -I c:\norax\include\libc -o crt0.o  
	gcc -c c:\norax\init\core\taskman\main.c -I c:\norax\include\libc -o main.o  
	
	
	copy c:\norax\lib\api\api.o c:\sdk\bin\api.o
	
	copy c:\norax\lib\stdio.o  c:\sdk\bin\stdio.o
	copy c:\norax\lib\stdlib.o c:\sdk\bin\stdlib.o
	copy c:\norax\lib\string.o c:\sdk\bin\string.o
	copy c:\norax\lib\ctype.o  c:\sdk\bin\ctype.o	
	
	
:Objects	
set myObjects=head.o ^
crt0.o ^
main.o ^
api.o ^
ctype.o ^
stdio.o ^
stdlib.o ^
string.o 




:Linking
echo -{ ...
echo -{ Linking objects ... 
    ld -T c:\norax\init\core\taskman\link.ld -o TASKMAN.BIN %myObjects% -Map tm_map.s
   
    rem
    rem :Cleaning   
    rem      Não pode deletar os objetos.
    rem
   
:Moving   
    move TASKMAN.BIN c:\norax\bin\TASKMAN.BIN
    
:End	
echo End.
	pause
	
	
