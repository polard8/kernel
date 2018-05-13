:SetUp
@echo off  


:Monting
echo -{ ...
echo -{ Creating INIT.BIN ...
echo -{ head
    rem head.s
	nasm head.s -felf -o head.o

	
:Compiling	
echo -{ ...
echo -{ main
	gcc  -c  main.c  -o main.o  
 
 
:Objects	
set myObjects=head.o ^
main.o ^
stdio.o ^
api.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T link.ld -o INIT.BIN %myObjects%  -Map  init_map.s
   
   rem Não deletar os objetos.
 
 
:Moving   
   move INIT.BIN bin\INIT.BIN

   
:End   
echo End!
	pause