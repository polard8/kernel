:SetUp
    @echo off
	
	cd c:\sdk\bin

:Mounting	
echo -{ ...
echo -{ head
	
	nasm c:\gramado\apps\taskman\head.s -felf -o head.o

:Compiling	
echo -{ ...
echo -{ Compiling TASKMAN.BIN.
    
	gcc -c c:\gramado\apps\taskman\crt0.c -I c:\gramado\include\libc -o crt0.o  
	gcc -c c:\gramado\apps\taskman\main.c -I c:\gramado\include\libc -o main.o  
	
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o
	
	copy c:\gramado\lib\stdio.o c:\sdk\bin\stdio.o
	copy c:\gramado\lib\stdlib.o c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\string.o c:\sdk\bin\string.o
	copy c:\gramado\lib\ctype.o c:\sdk\bin\ctype.o	
	
	
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
    ld -T c:\gramado\apps\taskman\link.ld -o TASKMAN.BIN %myObjects% -Map app_map.s
   
    rem
    rem :Cleaning   
    rem      Não pode deletar os objetos.
    rem
   
:Moving   
    move TASKMAN.BIN c:\gramado\bin\TASKMAN.BIN
    
:End	
echo End.
	pause
	
	
