:SetUp
@echo off  

    cd c:\sdk\bin
	
:Monting
echo -{ ...
echo -{ Creating application TBST.BIN ...
echo -{ head
    
	rem head.s
	nasm c:\gramado\cmd\tbst\head.s -felf -o head.o

	
:Compiling	
echo -{ ...
echo -{ app1 (init task)

	gcc  -c c:\gramado\cmd\tbst\main.c -I c:\gramado\include\libc -o main.o  
 
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
   ld -T  c:\gramado\cmd\tbst\link.ld -o TBST.BIN %myObjects%  -Map   c:\gramado\cmd\tbst\map.s
   
   rem Não deletar os objetos.
 
 
:Moving   
   move TBST.BIN c:\gramado\bin\TBST.BIN

   
:End   
echo End!
	pause