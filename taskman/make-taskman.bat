:SetUp
@echo off

:Mounting	
echo -{ ...
echo -{ head
	nasm head.s -felf -o head.o

:Compiling	
echo -{ ...
echo -{ Compiling app2 Task Manager.
	gcc -c main.c -o main.o  
	
:Objects	
set my_objects=head.o ^
main.o ^
api.o ^
stdio.o 


:Linking
echo -{ ...
echo -{ ligando objetos ... 
    ld -T link.ld -o TASKMAN.BIN %my_objects% -Map app_map.s
   
    rem
    rem :Cleaning   
    rem Não pode deletar os objetos.
    rem
   
:Moving   
    move TASKMAN.BIN bin\TASKMAN.BIN
    
:End	
echo End.
	pause
	
	
