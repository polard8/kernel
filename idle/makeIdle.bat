:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application IDLE.BIN ...
echo -{ head
    rem head.s
	nasm head.s -felf -o head.o

:Compiling	
echo -{ ...
echo -{ app1 (idle task)
	gcc  -c  main.c  -o main.o  
 
:Objects	
set myObjects=head.o ^
main.o ^
stdio.o ^
api.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T link.ld -o IDLE.BIN %myObjects%  -Map  idle_map.s
   
   rem Não deletar os objetos.
   
:Moving   
   move IDLE.BIN bin\IDLE.BIN

:End   
echo End!
	pause