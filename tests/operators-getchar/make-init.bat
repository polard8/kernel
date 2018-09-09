:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application OPER1.BIN ...
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc  -c  main.c  -o main.o  
 
:Objects	
set myObjects=main.o ^
stdio.o 


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T link.ld -o OPER1.BIN %myObjects%  -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
   move OPER1.BIN bin\OPER1.BIN
   
:End   
echo End!
	pause