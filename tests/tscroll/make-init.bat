:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application TSCROLL.BIN ...
	
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
   ld -T link.ld -o TSCROLL.BIN %myObjects% -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
   rem move ASCII.BIN bin\ASCII.BIN
   
:End   
echo End!
	pause