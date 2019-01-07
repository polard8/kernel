:SetUp
@echo off  

    cd c:\sdk\bin 

:Monting
echo -{ ...
echo -{ Creating INIT.BIN for Norax ...
echo -{ head
    rem head.s
	nasm c:\norax\init\core\init\head.s -felf -o head.o

	
:Compiling	
echo -{ ...
echo -{ main
	gcc  -c  c:\norax\init\core\init\main.c  -I c:\norax\include\libc -o main.o  
 
 
    copy c:\norax\lib\stdio.o c:\sdk\bin\stdio.o
    copy c:\norax\lib\string.o c:\sdk\bin\string.o
    copy c:\norax\lib\ctype.o c:\sdk\bin\ctype.o	
    copy c:\norax\lib\stdlib.o c:\sdk\bin\stdlib.o
	
    copy c:\norax\lib\api\api.o c:\sdk\bin\api.o
	
 
:Objects	
set myObjects=head.o ^
main.o ^
stdio.o ^
ctype.o ^
string.o ^
stdlib.o ^
api.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T c:\norax\init\core\init\link.ld -o INIT.BIN %myObjects%  -Map  init_map.s
   
   rem Não deletar os objetos.
 
 
:Moving   
   move INIT.BIN c:\norax\bin\INIT.BIN

   
:End   
echo End!
	pause