:SetUp
@echo off  

    cd c:\sdk\bin
	
:Monting
echo -{ ...
echo -{ Creating application TBST2.BIN ...
echo -{ head
    
	rem head.s
	nasm c:\gramado\desktop\tests\tbst2\head.s -felf -o head.o

	
:Compiling	
echo -{ ...
echo -{ app1 (init task)

	gcc  -c c:\gramado\desktop\tests\tbst2\main.c -I c:\gramado\include\libc -o main.o  
 
    copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
    copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
    copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
    copy c:\gramado\lib\time.o	  c:\sdk\bin\time.o
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o	
 
 
:Objects	
set myObjects=head.o ^
main.o ^
stdio.o ^
stdlib.o ^
ctype.o ^
string.o ^
api.o  

:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T  c:\gramado\desktop\tests\tbst2\link.ld -o TBST2.BIN %myObjects%  -Map   c:\gramado\desktop\tests\tbst2\map.s
   
   rem Não deletar os objetos.
 
 
:Moving   
   move TBST2.BIN c:\gramado\bin\TBST2.BIN

   
:End   
echo End!
	pause