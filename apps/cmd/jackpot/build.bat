:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application JACKPOT.BIN ...

    cd c:\sdk\bin
	
:Compiling	
echo -{ ...
echo -{ Compiling ...

	gcc  -c c:\gramado\cmd\jackpot\main.c -I c:\gramado\include\libc -o main.o  
 
    copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
    copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
    copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
    copy c:\gramado\lib\time.o	  c:\sdk\bin\time.o
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o	
 
:Objects	
set myObjects=main.o ^
ctype.o ^
stdio.o ^
stdlib.o ^
string.o ^
time.o ^
api.o   


    



:Linking  
echo -{ ...
echo -{ Linking objects ... 

   ld -T c:\gramado\cmd\jackpot\link.ld -o JACKPOT.BIN %myObjects% -Map c:\gramado\cmd\jackpot\map.s
   
   rem Não deletar os objetos.
 
:Moving   

   move JACKPOT.BIN c:\gramado\bin\JACKPOT.BIN
   
:End   
echo End!
	
	pause