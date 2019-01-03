:SetUp
@echo off  

    cd c:\sdk\bin 

:Monting
echo -{ ...
echo -{ Creating INIT.BIN ...
echo -{ head
    rem head.s
	nasm c:\gramado\init\core\init\head.s -felf -o head.o

	
:Compiling	
echo -{ ...
echo -{ main
	gcc  -c  c:\gramado\init\core\init\main.c  -I c:\gramado\include\libc -o main.o  
 
 
    copy c:\gramado\lib\stdio.o c:\sdk\bin\stdio.o
    copy c:\gramado\lib\string.o c:\sdk\bin\string.o
    copy c:\gramado\lib\ctype.o c:\sdk\bin\ctype.o	
    copy c:\gramado\lib\stdlib.o c:\sdk\bin\stdlib.o
    copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o
	copy c:\gramado\lib\unistd.o c:\sdk\bin\unistd.o
 
:Objects	
set myObjects=head.o ^
main.o ^
stdio.o ^
ctype.o ^
string.o ^
stdlib.o ^
unistd.o ^
api.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T c:\gramado\init\core\init\link.ld -o INIT.BIN %myObjects%  -Map  init_map.s
   
   rem Não deletar os objetos.
 
 
:Moving   
   move INIT.BIN c:\gramado\bin\INIT.BIN

   
:End   
echo End!
	pause