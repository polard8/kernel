:SetUp
    @echo off

:Mounting	
echo -{ ...
echo -{ head
	nasm head.s -felf -o head.o

:Compiling	
echo -{ ...
echo -{ Compiling TASKMAN.BIN.
	gcc -c main.c -o main.o  
	
:Objects	
set myObjects=head.o ^
main.o ^
api.o ^
stdio.o 


:Linking
echo -{ ...
echo -{ Linking objects ... 
    ld -T link.ld -o TASKMAN.BIN %myObjects% -Map app_map.s
   
    rem
    rem :Cleaning   
    rem      Não pode deletar os objetos.
    rem
   
:Moving   
    move TASKMAN.BIN bin\TASKMAN.BIN
    
:End	
echo End.
	pause
	
	
