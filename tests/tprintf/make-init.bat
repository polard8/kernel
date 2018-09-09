:SetUp
@echo off  


:Monting
echo -{ ...
echo -{ Creating application PRINTF1.BIN ...
echo -{ head
    rem head.s
	nasm head.s -felf -o head.o

	
:Compiling	
echo -{ ...
echo -{ app1 (init task)
	gcc  -c  main.c  -o main.o  
 
 
:Objects	
set myObjects=head.o ^
main.o ^
stdio.o ^
api.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T link.ld -o PRINTF1.BIN %myObjects%  -Map  testtest_map.s
   
   rem Não deletar os objetos.
 
 
:Moving   
   move PRINTF1.BIN bin\PRINTF1.BIN

   
:End   
echo End!
	pause