:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application LONGEST1.BIN ...
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc  -c  main.c  -o main.o  
 
:Objects	
set myObjects=main.o ^
stdio.o ^
string.o  



:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T link.ld -o LONGEST1.BIN %myObjects% -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
   REM move ASCII.BIN bin\ASCII.BIN
   
:End   
echo End!
	pause