:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application TSCANF.BIN ...
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc  -c  main.c  -o main.o  
 
:Objects	
set myObjects=main.o ^
stdio.o ^
stdlib.o ^
string.o ^
ctype.o  






:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T link.ld -o TSCANF.BIN %myObjects% -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
   rem move ASCII.BIN bin\ASCII.BIN
   
:End   
echo End!
	pause