:SetUp
@echo off  

    cd c:\sdk\bin

:Monting
echo -{ ...
echo -{ Creating application TASCII.BIN ...
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc  -c c:\gramado\tests\tascii\main.c -I c:\gramado\include\libc -o main.o  
 

    copy c:\gramado\lib\ctype.o c:\sdk\bin\ctype.o	 
    copy c:\gramado\lib\stdio.o c:\sdk\bin\stdio.o
    copy c:\gramado\lib\stdlib.o c:\sdk\bin\stdlib.o
    copy c:\gramado\lib\string.o c:\sdk\bin\string.o

	
:Objects	
set myObjects=main.o ^
ctype.o ^
stdio.o ^
stdlib.o ^
string.o  




:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T c:\gramado\tests\tascii\link.ld -o TASCII.BIN %myObjects% -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
   move TASCII.BIN c:\gramado\bin\TASCII.BIN
   
:End   
echo End!
	pause